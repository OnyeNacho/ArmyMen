// ObjectListBox.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "ObjectSet.h"
#include "ObjectListBox.h"
#include "attribute.h"
#include "objectsetview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OLB_GAP  5    // spacing between items 
#define OLB_MAXW 100
#define OLB_MAXH 100

/////////////////////////////////////////////////////////////////////////////
// CObjectListBox

CObjectListBox::CObjectListBox()
{
	m_pView = NULL;
	InitContent();
}


void CObjectListBox::InitContent()
{
	m_iFontHeight = 0;
	m_iItemWidth = 0;
	m_iItemHeight = 0;
	m_iLastItem = -1;
	m_pObjectSet = NULL;
	m_maxSize.cx = 1;
	m_maxSize.cy = 1;
	m_hPalette = NULL;
	m_bShowFullName = FALSE;
	m_bMogMode = FALSE;
}

BEGIN_MESSAGE_MAP(CObjectListBox, CListBox)
	//{{AFX_MSG_MAP(CObjectListBox)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectListBox message handlers



void CObjectListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	lpMIS->itemWidth = m_iItemWidth + OLB_GAP;
	lpMIS->itemHeight = m_iItemHeight + OLB_GAP;
}

void CObjectListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CString label;
	CMapObject *pObject=NULL;
	
	ASSERT((GetStyle() & (LBS_OWNERDRAWFIXED | LBS_HASSTRINGS)) == LBS_OWNERDRAWFIXED);

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	int iObject = (int)lpDIS->itemData;
	
	if (iObject < 0 || iObject >= m_pObjectSet->GetObjectCount())
		return; // avoid stupid listbox bug

	if (IsMogMode())
	{
		if (NULL != m_pView)
			label = m_pView->GetMogName(iObject);
	}
	else
	{
		pObject = m_pObjectSet->GetObject(iObject);
		label = m_bShowFullName ? pObject->GetKey() : pObject->GetName();
	}

	CRect itemRect = lpDIS->rcItem;
	itemRect.right -= OLB_GAP;

	// center the item within the given rectangle, leave 1 pixel
	// border to show frame around the object when it is selected.
	CRect rect;
    rect.left = itemRect.left + (itemRect.Width() - m_maxSize.cx) / 2 + 1;
	rect.top = itemRect.top + 1;
	rect.right = rect.left + m_maxSize.cx;
    rect.bottom = rect.top + m_maxSize.cy;

	CSize ext = pDC->GetTextExtent(label,strlen(label));

	int tx = itemRect.left + (itemRect.Width() - ext.cx) / 2 + 1;  // center text below tile
	int ty = rect.bottom;

	if (NULL == pObject)
	{
		rect = GetPropRect(rect, CSize(rect.Width(), rect.Height()));
	}
	else
	{
		rect = GetPropRect(rect, pObject->GetSize());
	}

	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
		// draw the item in a rect proportional to object dimensions

		if (IsMogMode() && NULL != m_pView)
			m_pView->DrawMog(lpDIS->hDC, iObject, rect, m_hPalette);
		else
			m_pObjectSet->DrawWithPalette(lpDIS->hDC, iObject, rect, m_hPalette);
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
		
	//	CRect txRect(CPoint(tx,ty),ext);
	//	txRect.InflateRect(2,0,2,0);
	//	pDC->FillRect(&txRect,&br);
		pDC->TextOut(tx, ty, label);

#if 1
		CPoint hotSpot;
		if (NULL != pObject)
			pObject->GetHotSpot();
		label.Format("%d,%d",hotSpot.x,hotSpot.y);
		ext = pDC->GetTextExtent(label,strlen(label));
		tx = itemRect.left + (itemRect.Width() - ext.cx) / 2 + 1;  // center text below tile
		ty += ext.cy;
		pDC->TextOut(tx,ty,label);
#endif
		pDC->SelectObject(pOldPen);
	}
}

int CObjectListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCIS)
{
	int iItem1 = (int)lpCIS->itemData1;
	int iItem2 = (int)lpCIS->itemData2;
	CMapObject *pObject=NULL;
	CString label1;
	CString label2;

	if (IsMogMode() && NULL != m_pView)
	{
		label1 = m_pView->GetMogName(iItem1);
		label2 = m_pView->GetMogName(iItem2);
	}
	else
	{
		pObject = m_pObjectSet->GetObject(iItem1);
		label1 = m_bShowFullName ? pObject->GetKey() : pObject->GetName();

		pObject = m_pObjectSet->GetObject(iItem2);
		label2 = m_bShowFullName ? pObject->GetKey() : pObject->GetName();
	}

	return label1.Compare(label2); // assumes labels are all one case
}

int CObjectListBox::AddItem(int iItem)
{
	// add a listbox item
	ASSERT(iItem >= 0);
	ASSERT(m_pObjectSet != NULL);
	ASSERT(iItem < m_pObjectSet->GetObjectCount());
	return AddString((LPCTSTR) iItem);
	// Listbox does not have the LBS_HASSTRINGS style, so the
	//  normal listbox string is used to store a object index
}

int CObjectListBox::FindItem(int iItem)
{
   // find the index of the string representing iItem
    int iCount = GetCount();
	for (int i=0; i < iCount; i++)
	{
		if (GetItem(i) == iItem)
			return i;
	}
	return - 1;
}

void CObjectListBox::UseObjectSet(CObjectSet *pObjectSet, HPALETTE hPalette, BOOL bShowFullName)
{
	int i, iLabelWidth, maxLen=0;
	CSize maxSize(1,1);
	ResetContent();

	ASSERT(pObjectSet != NULL);
	m_pObjectSet = pObjectSet;
    m_hPalette = hPalette;
    m_bShowFullName = bShowFullName;

	for (i=0; i < pObjectSet->GetObjectCount(); i++)
	{
		CMapObject *pObject = pObjectSet->GetObject(i);
		CSize size = pObject->GetSize();
		iLabelWidth = strlen(bShowFullName ? pObject->GetKey() : pObject->GetName());
		if (iLabelWidth > maxLen) 
			maxLen = iLabelWidth;
		if (size.cx > maxSize.cx)
			maxSize.cx = size.cx;
		if (size.cy > maxSize.cy)
			maxSize.cy = size.cy;

	}
    if (maxSize.cx >= OLB_MAXW)
		maxSize.cx = OLB_MAXW;
	if (maxSize.cy >= OLB_MAXH)
		maxSize.cy = OLB_MAXH;

	TEXTMETRIC tm;
	CDC *pDC = GetDC();
	::GetTextMetrics(pDC->m_hDC, &tm);
    ReleaseDC(pDC);

	m_maxSize = maxSize;
	m_iFontHeight = tm.tmHeight;   
	iLabelWidth = maxLen * tm.tmAveCharWidth; 
	m_iItemWidth = max(maxSize.cx, iLabelWidth) + OLB_GAP;
	m_iItemHeight = maxSize.cy + 2 * m_iFontHeight + OLB_GAP;
	SetColumnWidth(m_iItemWidth);
	SetItemHeight(0,m_iItemHeight); // sets the width of all items
}


void CObjectListBox::OnLButtonDown(UINT nFlags, CPoint point) 
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

void CObjectListBox::ResetSelection(int iIndex)
{
	SetSel(-1,FALSE); // remove current selection
	if (iIndex >= 0)
		SetSel(iIndex, TRUE);
}


void CObjectListBox::ResetContent()
{
	CListBox::ResetContent();
	InitContent();
}





void CObjectListBox::SetMog(BOOL bMog)
{
	m_bMogMode = bMog;
}

BOOL CObjectListBox::IsMogMode()
{
	return m_bMogMode;
}
