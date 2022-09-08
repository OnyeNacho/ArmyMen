#include "stdafx.h"
#include "MapEditor.h"
#include "TileSet.h"
#include "TileListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TLB_GAP 5

BEGIN_MESSAGE_MAP(CTileListBox, CListBox)
	//{{AFX_MSG_MAP(CTileListBox)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CTileListBox::CTileListBox()
{
   InitContent();
}

void CTileListBox::InitContent()
{
	m_iFontHeight = 0;
	m_iItemWidth = 0;
	m_iItemHeight = 0;
	m_iInnerWidth = 0;
	m_iInnerHeight = 0;
	m_iLastItem = -1;
	m_pTileSet = NULL;
	m_groupTileSize = CSize(1,1);
}

void CTileListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	ASSERT(m_pTileSet != NULL);
	lpMIS->itemWidth = m_iItemWidth + TLB_GAP;
	lpMIS->itemHeight = m_iItemHeight + TLB_GAP;
}

void CTileListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT((GetStyle() & (LBS_OWNERDRAWFIXED | LBS_HASSTRINGS)) == LBS_OWNERDRAWFIXED);

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CTileGroup *pGroup = NULL;
	int iTile = (int)lpDIS->itemData; 
	CString label;
    char str[20];

	CRect itemRect = lpDIS->rcItem;
	itemRect.right -= TLB_GAP;

	// center the item within the given rectangle, leave 1 pixel
	// border to show frame around the tile when it is selected.
	CRect rect;
    rect.left = itemRect.left + (itemRect.Width() - m_iInnerWidth) / 2 + 1;
	rect.top = itemRect.top + 1;
	rect.right = rect.left + m_iInnerWidth;
    rect.bottom = rect.top + m_iInnerHeight;

	switch (m_iViewType)
	{
		case TSV_GROUPS:
			if (iTile < 0 || iTile >= m_pTileSet->GetGroupCount())
				return;
			pGroup = m_pTileSet->GetGroupAt(iTile);
			if (!pGroup) return;
			label = pGroup->GetTitle();
			break;
		default:
			itoa(iTile,str,10);
			label = str;
	}

	CSize ext = pDC->GetTextExtent(label,strlen(label));
	int tx = itemRect.left + (itemRect.Width() - ext.cx) / 2 + 1;  // center text below tile
	int ty = rect.bottom;
 
	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
		if (pGroup) 
#ifdef SCALE_TO_FIT
			// draw the whole group so it fits in the given rect
			// this method has the advantage that small groups 
			// don't get lost (rendered tiny) when larger groups
			// are present
			m_pTileSet->DrawGroup(lpDIS->hDC, pGroup, rect);
#else
			// draw each group tile using m_groupTileSize
		    // this method has the advantage that the user can easily 
		    // determine which groups are larger/smaller.
			m_pTileSet->DrawGroup(lpDIS->hDC, pGroup, rect.TopLeft(), m_groupTileSize);
#endif
		else 
			m_pTileSet->DrawWithPalette(lpDIS->hDC, iTile, rect);
	}

	if (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE))
	{
		COLORREF frameColor, textColor;
		if (lpDIS->itemState & ODS_SELECTED)
		{
			frameColor = GetSysColor(COLOR_HIGHLIGHT);
			textColor = GetSysColor(COLOR_HIGHLIGHTTEXT);
		}
		else
		{
			frameColor = GetSysColor(COLOR_WINDOW);
			textColor = GetSysColor(COLOR_WINDOWTEXT);
		}
		CBrush br(frameColor);
		CPen pen(PS_SOLID, 1, frameColor);
		CPen *pOldPen = pDC->SelectObject(&pen);

		rect.InflateRect(1,1);
		pDC->FrameRect(&rect,&br);
		pDC->SetBkColor(frameColor);
		pDC->SetTextColor(textColor);
		CRect txRect(CPoint(tx,ty),ext);
		txRect.InflateRect(2,0,2,0);
		pDC->FillRect(&txRect,&br);
		pDC->TextOut(tx, ty, label);
		pDC->SelectObject(pOldPen);
	}
}

int CTileListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCIS)
{
	int iItem1 = (int)lpCIS->itemData1;
	int iItem2 = (int)lpCIS->itemData2;
	switch(m_iViewType)
	{
		case TSV_GROUPS:
			{
				CTileGroup *pItem1 = m_pTileSet->GetGroupAt(iItem1);
				CTileGroup *pItem2 = m_pTileSet->GetGroupAt(iItem2);
				ASSERT(pItem1 != NULL);
				ASSERT(pItem2 != NULL);
				return pItem1->GetTitle().CompareNoCase(pItem2->GetTitle());
			}
		default:
			if (iItem1 < iItem2)
				return -1;
			else if (iItem1 == iItem2)
				return 0;
			else 
				return 1;
	}
}

int CTileListBox::AddItem(int iItem)
{
	// add a listbox item
	ASSERT(iItem >= 0);
	ASSERT(m_pTileSet != NULL);
#ifdef _DEBUG
	switch(m_iViewType)
	{
		case TSV_GROUPS:
			ASSERT(iItem < m_pTileSet->GetGroupCount());
			break;
		default:
			ASSERT(iItem < m_pTileSet->GetTileCount());
			break;
	}
#endif
	return AddString((LPCTSTR) iItem);
	// Listbox does not have the LBS_HASSTRINGS style, so the
	//  normal listbox string is used to store a tile index
}

void CTileListBox::UseTileSet(CTileSet *pTileSet, int iViewType)
{
	int i, iLabelWidth, maxLen=0;
	CSize maxSize(1,1);
    char str[20];

	ResetContent();

	ASSERT(pTileSet != NULL);
	m_pTileSet = pTileSet;
    m_iViewType = iViewType;

    m_iInnerWidth = pTileSet->m_iTileWidth;
	m_iInnerHeight = pTileSet->m_iTileHeight;
	switch(iViewType)
	{
		case TSV_GROUPS:
			for (i=0; i < pTileSet->GetGroupCount(); i++)
			{
				CTileGroup *pGroup = pTileSet->GetGroupAt(i);
				CSize size = pGroup->GetSize();
				iLabelWidth = strlen(pGroup->GetTitle());
				if (iLabelWidth > maxLen) 
					maxLen = iLabelWidth;
				if (size.cx > maxSize.cx)
					maxSize.cx = size.cx;
				if (size.cy > maxSize.cy)
					maxSize.cy = size.cy;

			}
			m_groupTileSize.cx = max(m_iInnerWidth * 4 / maxSize.cx, 1);
			m_groupTileSize.cy = max(m_iInnerHeight * 4 / maxSize.cy, 1);
			m_iInnerWidth = maxSize.cx * m_groupTileSize.cx;
			m_iInnerHeight = maxSize.cy * m_groupTileSize.cy;
			break;
		default:
			maxLen = strlen(itoa(pTileSet->GetTileCount(),str,10));
			break;
	}
	TEXTMETRIC tm;
	CDC *pDC = GetDC();
	::GetTextMetrics(pDC->m_hDC, &tm);
    ReleaseDC(pDC);

	m_iFontHeight = tm.tmHeight;   
	iLabelWidth = maxLen * tm.tmAveCharWidth;  
	m_iItemWidth = max(m_iInnerWidth, iLabelWidth) + TLB_GAP;
	m_iItemHeight = m_iInnerHeight + m_iFontHeight + TLB_GAP;
	SetColumnWidth(m_iItemWidth);
	SetItemHeight(0,m_iItemHeight); // sets the width of all items
}


void CTileListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CListBox::OnLButtonDown(nFlags, point); 

	BOOL bOutside;
	int iIndex = (int)ItemFromPoint(point, bOutside);
	if (!bOutside)
	{
		if (!(nFlags & MK_CONTROL))
		{
			if (GetSelCount() > 1)
			   ResetSelection(iIndex);
		    else if (iIndex != m_iLastItem && m_iLastItem >= 0)
				SetSel(m_iLastItem, FALSE);
        }
		m_iLastItem = iIndex; 
	}
}

void CTileListBox::ResetSelection(int iIndex)
{
	ASSERT(iIndex >= 0);
	SetSel(-1,FALSE); // remove current selection
	if (iIndex >= 0)
		SetSel(iIndex, TRUE);
}


void CTileListBox::ResetContent()
{
	CListBox::ResetContent();
	InitContent();
}

//////////////////////////////////////////////////////////////////////////////
// CDupListBox
//

#define DLB_HGAP    m_pTileSet->m_iTileWidth
#define DLB_VGAP    4
#define DLB_ARROWX  m_indicatorSize.cx
#define DLB_ARROWY  m_indicatorSize.cy

BEGIN_MESSAGE_MAP(CDupListBox, CTileListBox)
	//{{AFX_MSG_MAP(CDupListBox)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDupListBox::UseTileSet(CTileSet *pTileSet)
{
	ResetContent();

	ASSERT(pTileSet != NULL);
	m_pTileSet = pTileSet;

	int iWidth = pTileSet->m_iTileWidth;
	char str[20];
	
	itoa(pTileSet->GetTileCount(),str,10);

    TEXTMETRIC tm;
	CDC *pDC = GetDC();
	::GetTextMetrics(pDC->m_hDC, &tm);
    ReleaseDC(pDC);

	int iLabelWidth = strlen(str) * tm.tmAveCharWidth;
	m_iFontHeight = tm.tmHeight;           
	m_iItemWidth = 2 * max(iWidth,iLabelWidth) + DLB_ARROWX + DLB_HGAP;
	m_iItemHeight = max(pTileSet->m_iTileHeight + m_iFontHeight, DLB_ARROWY) + DLB_VGAP;
	SetColumnWidth(m_iItemWidth);
	SetItemHeight(0,m_iItemHeight); // sets the width of all items
}


void CDupListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	ASSERT(m_pTileSet != NULL);
	lpMIS->itemWidth = 2 * m_pTileSet->m_iTileWidth + DLB_ARROWX + DLB_HGAP;
	lpMIS->itemHeight = max(m_pTileSet->m_iTileHeight + m_iFontHeight, DLB_ARROWY) + DLB_VGAP;
}

void CDupListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	int iTile = (int)lpDIS->itemData; 
    char str[20];

	CRect itemRect = lpDIS->rcItem;
	itemRect.right -= DLB_HGAP;
    int iWidth = (itemRect.Width() - DLB_ARROWX) / 2;
	int iOffset = (iWidth - m_pTileSet->m_iTileWidth) / 2;
	
	// center the tiles within the given rectangle
	CRect rect = itemRect;
	rect.bottom -= m_iFontHeight + DLB_VGAP;
    rect.left += iOffset;
	rect.right = rect.left + m_pTileSet->m_iTileWidth;

	CRect rect2 = rect;
	rect2.left = itemRect.right - iWidth;
	rect2.right = rect2.left + m_pTileSet->m_iTileWidth;
   
	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
		// draw the first tile and the arrow
		m_pTileSet->DrawWithPalette(lpDIS->hDC, iTile, rect);
		itoa(iTile,str,10);

		CSize ext = pDC->GetTextExtent(str,strlen(str));
        int tx = itemRect.left + (iWidth - ext.cx) / 2;  // center text below tile
		pDC->TextOut(tx, rect.bottom, str); 

		// draw the second tile
		m_pTileSet->DrawWithPalette(lpDIS->hDC, m_pTileSet->m_searchList[iTile], rect2);
		itoa(m_pTileSet->m_searchList[iTile],str,10);

		ext = pDC->GetTextExtent(str,strlen(str));
        tx = rect2.left + (iWidth - ext.cx) / 2;  // center text below tile
		pDC->TextOut(tx, rect.bottom, str);
	}

    HBITMAP hBitmap;
	if (lpDIS->itemState & ODS_SELECTED) 
	{
	    hBitmap = m_hCheckBitmap;
	}
	else 
	{
	    hBitmap = m_hCrossBitmap;
	}	
	CDC bitmapDC;
	if (bitmapDC.CreateCompatibleDC(pDC))
	{
		HBITMAP old = (HBITMAP)bitmapDC.SelectObject(hBitmap);
		pDC->BitBlt(itemRect.left + iWidth, itemRect.top + (itemRect.Height() - DLB_ARROWY)/2,
				    DLB_ARROWX, DLB_ARROWY, &bitmapDC, 0, 0, SRCCOPY);
		bitmapDC.SelectObject(hBitmap);
	}	
}

CDupListBox::CDupListBox()
{
	CBitmap check,cross;

	VERIFY(check.LoadBitmap(IDB_CHECK));
    VERIFY(cross.LoadBitmap(IDB_CROSS));

	BITMAP bm;
	check.GetObject(sizeof (BITMAP), &bm);
	m_indicatorSize.cx = bm.bmWidth;
	m_indicatorSize.cy = bm.bmHeight;
	m_hCheckBitmap = (HBITMAP)check.Detach();

	cross.GetObject(sizeof (BITMAP), &bm);
	m_indicatorSize.cx = max(m_indicatorSize.cx, bm.bmWidth);
	m_indicatorSize.cy = max(m_indicatorSize.cy, bm.bmHeight);
	m_hCrossBitmap = (HBITMAP)cross.Detach();
	m_iViewType = TSV_TILES;
}


CDupListBox::~CDupListBox()
{
	if (m_hCheckBitmap) ::DeleteObject(m_hCheckBitmap);
	if (m_hCrossBitmap) ::DeleteObject(m_hCrossBitmap);
}

void CDupListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CListBox::OnLButtonDown(nFlags, point);
}


