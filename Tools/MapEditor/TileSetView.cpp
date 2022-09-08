// TileSetView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MainFrm.h"
#include "MapEditorDoc.h"
#include "TileSetView.h"
#include "ShowUsageDlg.h"
#include "NewTileSetDlg.h"   // this acts as a property sheet as well.
#include "AttributeSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTileSetView

IMPLEMENT_DYNCREATE(CTileSetView, CFormView)

CTileSetView::CTileSetView()
	: CFormView(CTileSetView::IDD)
{
	//{{AFX_DATA_INIT(CTileSetView)
	//}}AFX_DATA_INIT

	// CG: This line was added by the Clipboard Assistant component
	m_pnClipboardFormats[0] = g_nTileSetFormat;
	m_iCurrentView = TSV_TILES;
	m_iTileCategory = 0;
	m_iGroupCategory = 0;
}

CTileSetView::~CTileSetView()
{
}

void CTileSetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTileSetView)
	DDX_Control(pDX, IDC_TILESET_TAB, m_categoryCtrl);
	DDX_Control(pDX, IDC_TILESET_VIEW, m_viewCtrl);
	DDX_Control(pDX, IDC_TRANSPARENT_COLOR, m_transCtrl);
	DDX_Control(pDX, IDC_TILESET_LIST, m_listCtrl);
	DDX_Control(pDX, IDC_TILESET_ITEM, m_itemCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTileSetView, CFormView)
	//{{AFX_MSG_MAP(CTileSetView)
	ON_WM_SIZE()
    ON_WM_PALETTECHANGED()
    ON_WM_QUERYNEWPALETTE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TILESET_TAB, OnSelchangeTilesetTab)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_DRAWITEM()
	ON_LBN_SELCHANGE(IDC_TILESET_LIST, OnSelchangeTilesetList)
	ON_COMMAND(ID_TILESET_FINDDUP, OnTilesetFindDup)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_BN_CLICKED(IDC_TRANSPARENT_COLOR, OnTransparentColor)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_NONE, OnUpdateEditSelectNone)
	ON_UPDATE_COMMAND_UI(ID_TILESET_FINDDUP, OnUpdateTilesetFindDup)
	ON_UPDATE_COMMAND_UI(ID_TILESET_SHOWUSAGE, OnUpdateTilesetShowusage)
	ON_COMMAND(ID_TILESET_SHOWUSAGE, OnTilesetShowusage)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TILESET_VIEW, OnSelchangeTilesetView)
	ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ATTRIBUTES, OnUpdateEditAttributes)
	ON_COMMAND(ID_EDIT_ATTRIBUTES, OnEditAttributes)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTileSetView diagnostics

#ifdef _DEBUG
void CTileSetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTileSetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


CTileSet* CTileSetView::GetDocument() // this is slimy but it works...
{
   ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTileSet)));
   return (CTileSet*)m_pDocument;
}

#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CTileSetView message handlers

void CTileSetView::AdjustControls()
{
	CRect wndRect,newRect, itemRect;

	GetWindowRect(&wndRect);
	if (!m_categoryCtrl.m_hWnd) return;

	// size m_categoryCtrl to fill the bottom of the dialog window
	m_categoryCtrl.GetWindowRect(&newRect);
	newRect.left = wndRect.left + 5;
	newRect.right = newRect.left + wndRect.Width() - 10;
	newRect.bottom = wndRect.bottom - 5;
    ScreenToClient(&newRect);
	m_categoryCtrl.MoveWindow(&newRect,FALSE);
    m_categoryCtrl.GetItemRect(0,&itemRect);

	// size m_listCtrl to fill the m_categoryCtrl area
	newRect.DeflateRect(5,itemRect.Height()+5,5,5);
	m_listCtrl.MoveWindow(&newRect, FALSE);

	m_transCtrl.SetColor(GetDocument()->m_rgbTransparent);
	InvalidateRect(NULL);
}

void CTileSetView::OnSize(UINT nType, int cx, int cy) 
{
    if (m_hWnd == NULL) return;
	CFormView::OnSize(nType, cx, cy);

	// reset and turn any scroll bars off
	if (GetStyle() & (WS_HSCROLL|WS_VSCROLL))
	{
		SetScrollPos(SB_HORZ, 0);
		SetScrollPos(SB_VERT, 0);
		EnableScrollBarCtrl(SB_BOTH, FALSE);
		ASSERT((GetStyle() & (WS_HSCROLL|WS_VSCROLL)) == 0);
	}
    if (m_itemCtrl.m_hWnd == NULL) return; // no items to place
    AdjustControls();

}

// RenewItemCtrl: renews the display of the current item 
void CTileSetView::RenewItemCtrl(BOOL bRepaint)
{
	if (m_itemCtrl.m_hWnd)
		m_itemCtrl.SetButtonStyle(m_itemCtrl.GetButtonStyle(), bRepaint);
}

void CTileSetView::RenewListCtrl(BOOL bRepaint)
{
	if (!m_listCtrl.m_hWnd)
		return;

	// create a new list control for the current tileSet
	CTileSet *pTileSet = GetDocument();
	m_listCtrl.UseTileSet(pTileSet, m_iCurrentView); // this does a ResetContent()
	CWaitCursor wait;
	TRY
	{
		if (m_iCurrentView == TSV_TILES && m_iTileCategory == 0)
			m_listCtrl.ModifyStyle(LBS_SORT,0); // everything is already sorted
		else
			m_listCtrl.ModifyStyle(0,LBS_SORT);
		if (m_iCurrentView == TSV_TILES)
			FillTileView();
		else
			FillGroupView();

		if (bRepaint) 
			m_listCtrl.UpdateWindow();
	}
	END_TRY
}

void CTileSetView::RenewTabCtrl(BOOL bRepaint)
{
	CTileSet *pTileSet = GetDocument();
	int i, iView = TSV_TILES;

	if (m_categoryCtrl.m_hWnd == NULL)
		return;

	m_categoryCtrl.DeleteAllItems();

	// add the category tabs to the tab control
	TC_ITEM item;
	CString tab1;
	item.mask = TCIF_TEXT;
	if (m_iCurrentView == TSV_TILES)
	{
		VERIFY(tab1.LoadString(IDS_TILES));
		item.pszText = (LPSTR)((LPCTSTR)tab1);
        m_categoryCtrl.InsertItem(0, &item);
		int iCount = pTileSet->GetTileCategoryCount();
		for (i=0; i < iCount; i++)
		{
			item.pszText = (LPSTR)((LPCTSTR)pTileSet->GetTileCategory(i)->GetTitle());
			m_categoryCtrl.InsertItem(i+1, &item);
		}
		m_iTileCategory = min(m_iTileCategory,iCount);
		m_categoryCtrl.SetCurSel(m_iTileCategory);
	}
	else
	{
		VERIFY(tab1.LoadString(IDS_GROUPS));
		item.pszText = (LPSTR)((LPCTSTR)tab1);
        m_categoryCtrl.InsertItem(0, &item);
		int iCount = pTileSet->GetGroupCategoryCount();
		for (i=0; i < iCount; i++)
		{
			item.pszText = (LPSTR)((LPCTSTR)pTileSet->GetGroupCategory(i)->GetTitle());
			m_categoryCtrl.InsertItem(i+1, &item);
		}
		m_iGroupCategory = min(m_iGroupCategory,iCount);
		m_categoryCtrl.SetCurSel(m_iGroupCategory);
	}
	if (bRepaint) m_categoryCtrl.UpdateWindow();
}

void CTileSetView::FillTileView()
{
	if (m_iTileCategory == 0)
	{
		// fill the current list will all the tiles
		int iItems = GetDocument()->GetTileCount();
		for (int i=0; i < iItems; i++)
		{
			m_listCtrl.AddItem(i);
		}
	}
	else 
	{
		// fill the current list will only those tiles in m_iTileCategory
		CCategory *pCategory = GetDocument()->GetTileCategory(m_iTileCategory-1);
		int iItems = pCategory->GetItemCount();
		int iImageIndex;

		for (int i=0; i < iItems; i++)
		{
			iImageIndex = pCategory->GetItemAt(i);
			m_listCtrl.AddItem(iImageIndex);
		}
	}
}


void CTileSetView::FillGroupView()
{
	if (m_iGroupCategory == 0)
	{
		// fill the current list with all the group icons
		int iItems = GetDocument()->GetGroupCount();
		for (int i=0; i < iItems; i++)
		{
			m_listCtrl.AddItem(i);
		}
	}
	else
	{
		// fill the current list with only those group icons
		// in m_iGroupCategory
		CCategory *pCategory = GetDocument()->GetGroupCategory(m_iGroupCategory-1);
		int iItems = pCategory->GetItemCount();
		int iGroupIndex;

		for (int i=0; i < iItems; i++)
		{
			iGroupIndex = pCategory->GetItemAt(i);
			m_listCtrl.AddItem(iGroupIndex);
		}
	}
}

void CTileSetView::OnSelchangeTilesetTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR) 
	{
		int iCategory = m_categoryCtrl.GetCurSel();
		if (m_iCurrentView == TSV_TILES)
			m_iTileCategory = iCategory;
		else
            m_iGroupCategory = iCategory;
		RenewListCtrl();
	}
	*pResult = 0;
}

void CTileSetView::OnSelchangeTilesetView(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR) 
	{
	    m_iCurrentView = m_viewCtrl.GetCurSel();
		RenewTabCtrl();
		RenewListCtrl();
	}
	*pResult = 0;
}

void CTileSetView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	// CG: This line was added by the Clipboard Assistant component
	pCmdUI->Enable(::IsClipboardFormatAvailable(g_nTileSetFormat));
}

void CTileSetView::OnEditCopy()
{
	if (OpenClipboard())
	{
		EmptyClipboard();

		TRY
		{
			CSharedFile	memFile;
			CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);

			DoCutCopy(ar, FALSE);
			ar.Flush();

			HGLOBAL hData = memFile.Detach();
			::SetClipboardData(g_nTileSetFormat, hData);
			CloseClipboard();
		}
		CATCH_ALL(e)
		{
			CloseClipboard();
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	else
		AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);

}

void CTileSetView::OnEditCut()
{
	if (OpenClipboard())
	{
		EmptyClipboard();
		TRY
		{
			CSharedFile	memFile;
			CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);

			DoCutCopy(ar, TRUE);
			ar.Flush();

			HGLOBAL hData = memFile.Detach();
			::SetClipboardData(g_nTileSetFormat, hData);
			CloseClipboard();
		}
		CATCH_ALL(e)
		{
			CloseClipboard();
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	else
		AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
}

void CTileSetView::OnEditPaste()
{
	// CG: This block was added by the Clipboard Assistant component
	int iFormat = GetPriorityClipboardFormat(m_pnClipboardFormats, N_TILESET_FORMATS);
    if (iFormat >= 0)
	{
  		if (OpenClipboard())
		{
			CSharedFile memFile;
			TRY
			{
				HANDLE hData = ::GetClipboardData((UINT)iFormat);
				if (hData != NULL)
				{
					memFile.SetHandle(hData,FALSE);
					CArchive ar(&memFile, CArchive::load|CArchive::bNoFlushOnDelete);
					DoPaste(ar, (UINT)iFormat);	
				}
				else
					AfxMessageBox(CG_IDS_CANNOT_GET_CLIPBOARD_DATA);
				CloseClipboard();
				memFile.Detach(); // so global ptr gets unlocked and doesn't get deallocated

			}
			CATCH_ALL(e)
			{
				CloseClipboard();
				memFile.Detach(); 
				THROW_LAST();
			}
			END_CATCH_ALL
		}
		else
			AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
	}
}

BOOL CTileSetView::IsSelected()
{
	// CG: This function was added by the Clipboard Assistant component

     return (m_listCtrl.m_hWnd && (m_listCtrl.GetSelCount() > 0));
}

// TBD: make this an all or nothing operation,  if we get a memory
// exception anywhere along the way, abort the cut/copy -- which means
// we delay any/all item removal until after data has been copied to
// the clipboard.
void CTileSetView::DoCutCopy(CArchive &ar, BOOL bCut)
{
  	// CG: This function was added by the Clipboard Assistant component
	CTileSet *pTileSet = GetDocument();
	int iSelected = m_listCtrl.GetSelCount();
	try
	{
		ASSERT(ar.IsStoring());
        CTileOp opType = bCut ? TSOP_CUT : TSOP_COPY;
		CTileSetOp op(opType, m_iCurrentView, iSelected, pTileSet);

		if (iSelected >= 0)
		{
			if (m_iCurrentView == TSV_TILES)
				DoCopyTiles(op);
			else
				DoCopyGroups(op);
		}
		op.Serialize(ar);
        if (bCut) DoCut(op);
	}
	catch(...)
	{
		TRACE0("Error while trying to cut/copy data to clipboard\n");
		throw;
	}
}

void CTileSetView::DoPaste(CArchive& ar, UINT nFormat)
{
	CTileSet *pTileSet = GetDocument();
	ASSERT(pTileSet != NULL);
	ASSERT(!ar.IsStoring());
	if (nFormat == g_nTileSetFormat)
	{	
		CTileSetOp op;
		op.Serialize(ar);
		DoPaste(op);
	}
	else
	{
		TRACE0("Unsupported clipboard format\n");
		AfxThrowNotSupportedException();
	}
}


void CTileSetView::DoCopyTiles(CTileSetOp& op)
{
    int itemCount = m_listCtrl.GetCount();
	CTileSet *pTileSet = GetDocument();

	for (int i=0; i < itemCount; i++)
	{
		if (m_listCtrl.GetSel(i))
		{
			op.AddTile(m_listCtrl.GetItemData(i));
		}
	}
}

void CTileSetView::DoCopyGroups(CTileSetOp& op)
{
	int itemCount = m_listCtrl.GetCount();
	CTileSet *pTileSet = GetDocument();

	for (int i=0; i < itemCount; i++)
	{
		if (m_listCtrl.GetSel(i))
		{
			op.AddGroup(m_listCtrl.GetItemData(i));
		}
	}
}

void CTileSetView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelected());
}

void CTileSetView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelected());
}

void CTileSetView::DoPaste(CTileSetOp& op)
{
	CTileSet *pTileSet = GetDocument();
	int i, iCount;
	BOOL bModified = FALSE;
    BOOL bNewTile = FALSE;

	ASSERT(op.GetType() == TSOP_CUT || op.GetType() == TSOP_COPY);

	iCount = op.GetTileCount();
	BOOL bSameTileSet = op.IsSameTileSet(pTileSet);

	// see if we need to copy new tiles into the current tileset
	if ((iCount > 0) && ( !bSameTileSet || (!g_bTemporaryPaste && m_iCurrentView == TSV_TILES && m_iTileCategory == 0) ))
	{
		if (!bSameTileSet)
		{
			// if copying tiles into categories or if copying groups
			// ask the user if they want to copy image data or just the tile indices.
			if ((m_iCurrentView == TSV_TILES && m_iTileCategory != 0) ||
				(m_iCurrentView == TSV_GROUPS))
			{
				int res = AfxMessageBox(IDS_COPY_TILEDATA, MB_YESNOCANCEL);
				if (res == IDNO) 
					goto paste;
				else if (res == IDCANCEL) 
					return;
			}
			// TBD: why doesn't this work?
			if (pTileSet->GetTileCount() == 0)
				pTileSet->CopyPalette(op.m_tileSet.GetPalette());
			else if (pTileSet->ComparePalettesAndAsk(op.m_tileSet.GetPalette()) == IDCANCEL)
				return;
		}
		int oldCount = pTileSet->GetTileCount();
		pTileSet->Resize(oldCount + iCount); 
		ASSERT(iCount == op.m_tileIndex.GetSize());
		for (i=0; i < iCount; i++)
		{
			op.m_tileIndex[i] = pTileSet->CopyTile(&op.m_tileSet, i);
			pTileSet->UpdateAllViews(NULL,TSV_ADD_TILE,(CObject *)op.m_tileIndex[i]);
		}	
		pTileSet->UpdateMaps(oldCount, oldCount + iCount);
#ifndef USE_TRANSPARENCY_TABLES
		pTileSet->UpdateTransparency(); // we have to rebuild the mask to include the new tiles
#endif
		bModified = TRUE;
	}
paste:
	if (op.m_iTileView == TSV_GROUPS)
		bModified |= DoPasteGroups(bSameTileSet, op);
	else
		bModified |= DoPasteTiles(op);

	if (bModified)
		pTileSet->SetModifiedFlag();
}


void CTileSetView::DoCut(CTileSetOp& op)
{
	CTileSet *pTileSet = GetDocument();
	int i,iCount;
	BOOL bModified = FALSE;

	ASSERT(op.GetType() == TSOP_CUT);

	if (op.m_iTileView == TSV_TILES)
	{
		if (m_iTileCategory == 0)
		{
			// delete the tiles from the current tileset
			iCount = op.m_tileIndex.GetSize();
#ifdef _DEBUG
			// the tile list should always be sorted.
			int iLast = -1;
			for (i=0; i < iCount; i++)
			{
				ASSERT(op.m_tileIndex[i] > iLast);
				iLast = op.m_tileIndex[i];
			}
#endif
			for (i=iCount-1; i >= 0; i--)
			{
				if (pTileSet->RemoveTile(op.m_tileIndex[i]))
				{
					bModified = TRUE;
				}
			}
			if (bModified) 
			{
				pTileSet->UpdateAllViews(NULL,TSV_UPDATE_LIST);
				pTileSet->UpdateMaps();
			}
		}
		else 
		{
			// delete the tiles from the current tile category
			iCount = op.m_tileIndex.GetSize();
			CCategory *pCategory = pTileSet->GetTileCategory(m_iTileCategory-1);
			for (i=0; i < iCount; i++)
			{   
				 bModified |= pCategory->RemoveItem(op.m_tileIndex[i]);
			}
			if (bModified)
				pTileSet->UpdateAllViews(NULL,TSV_UPDATE_CATEGORY,pCategory);
		}
	}
	else
	{
		if (m_iGroupCategory == 0)
		{
			// delete the groups from the current tileset
			iCount = op.GetGroupCount();
			for (i=0; i < iCount; i++)
			{
				bModified |= pTileSet->RemoveGroup(op.GetGroupAt(i)->GetTitle());
			}
			if (bModified)
				pTileSet->UpdateAllViews(NULL,TSV_UPDATE_GROUPS);
		}
		else
		{
			// delete the groups from the current group category
			iCount = op.m_groupIndex.GetSize();
			CCategory *pCategory = pTileSet->GetGroupCategory(m_iGroupCategory-1);
			for (i=0; i < iCount; i++)
			{
				bModified = pCategory->RemoveItem(op.m_groupIndex[i]);
			}
			if (bModified)
				pTileSet->UpdateAllViews(NULL,TSV_UPDATE_CATEGORY,pCategory);
		}
	}
    if (bModified)
		pTileSet->SetModifiedFlag();
}

BOOL CTileSetView::DoPasteGroups(BOOL bSameTileSet, CTileSetOp& op)
{
	BOOL bModified = FALSE;
	CTileSet *pTileSet = GetDocument();
	int i,iRow,iCol,iCount = op.GetGroupCount();
	int iTileCount = pTileSet->GetTileCount();
	ASSERT_VALID(pTileSet);
	if (g_bTemporaryPaste)
	{
		// we're not really pasting the group into the tileset
		// we are creating a temporary group that the map will use
		// to paste the group into the map.

		// TBD: does this work when !bSameTileSet?
		CTileGroup *pGroup = pTileSet->SetTemporaryGroup(op.GetGroupAt(0));
		if (pGroup != NULL)
		{
			CSize size = pGroup->GetSize();
			for (iRow=0; iRow < size.cy; iRow++)
			{
				for (iCol=0; iCol < size.cx; iCol++)
				{
					int iTile = pGroup->GetTile(iRow,iCol);
					if (iTile >= 0) // we got a src tile 
						iTile = op.m_tileIndex[iTile]; // get dst index
					if (iTile < iTileCount) // validate index
						pGroup->SetTile(iRow,iCol,iTile);
				}
			}
			pTileSet->SetCurrentItem(TSV_GROUPS,-1);
		}
		return FALSE;
	}

	if (m_iCurrentView == TSV_TILES)
	{
		if (m_iTileCategory == 0)
		{
			// Assuming DoPaste() has already been called,
			// we're done; we've pasted all the tiles 
			// into the current tileset.
		}
		else
		{
			// paste the group tiles into the current category
			CCategory *pCategory = pTileSet->GetTileCategory(m_iTileCategory-1);
			for (i=0; i < iCount; i++)
			{
				CTileGroup *pGroup = op.GetGroupAt(i);
				CSize size = pGroup->GetSize();
				for (iRow = 0; iRow < size.cy; iRow++)
				{
					for (iCol = 0; iCol < size.cx; iCol++)
					{
						int iTile = pGroup->GetTile(iRow, iCol);
						if (iTile >= 0) // we got a src tile
						{
							iTile = op.m_tileIndex[iTile]; // grab dst index
							if (iTile < iTileCount) // validate index
							{
								pCategory->AddItem(iTile);
								bModified = TRUE;
							}
						}
					}
				}
			}
			if (bModified)
				pTileSet->UpdateAllViews(NULL,TSV_UPDATE_CATEGORY,pCategory);
		}
	}
	else 
	{
		BOOL bPasteFromMap = (iCount == 1 && op.m_groupIndex[0] == -1);
		if (bPasteFromMap || !bSameTileSet || m_iGroupCategory == 0)
		{
			// add all the groups to the tileset
			for (i=0; i < iCount; i++)
			{
				CTileGroup *ps = op.GetGroupAt(i); 
				CSize size = ps->GetSize();
				int iGroup = pTileSet->AddGroup(ps->GetTitle(), size.cx, size.cy, TRUE);
				if (iGroup < 0) 
				{
					iCount = i-1; // so we stop here..
					break;
                }
				op.m_groupIndex[i] = iGroup; // new index
				CTileGroup *pd = pTileSet->GetGroupAt(iGroup);
				if (pd != NULL)
				{
					bModified = TRUE;
					for (iRow=0; iRow < size.cy; iRow++)
					{
						for (iCol=0; iCol < size.cx; iCol++)
						{
							int iTile = ps->GetTile(iRow,iCol);
							if (iTile >= 0) // we got a src tile
								iTile = op.m_tileIndex[iTile]; // get dst index
							if (iTile < iTileCount) // validate index
								pd->SetTile(iRow,iCol,iTile);
						}
					}
					///////////////////////////////////////////////////////////////////
					// Code here for copying multi-layer group information
					// this function puts group in actual tileset
					// (CTileGroup)pd = dst
					// (CTileGroup)ps = src
					///////////////////////////////////////////////////////////////////
					ps->CopyMLayerToGroup(pd);
					///////////////////////////////////////////////////////////////////
				}
			}
			if (bModified)
				pTileSet->UpdateAllViews(NULL,TSV_UPDATE_GROUPS);
		}
		if (m_iGroupCategory > 0)
		{
			// add all the groups to the current category
			CCategory *pCategory = pTileSet->GetGroupCategory(m_iGroupCategory-1);
			for (int i=0; i < iCount; i++)
			{
				ASSERT(op.m_groupIndex[i] >= 0);
				bModified |= pCategory->AddItem(op.m_groupIndex[i]);
			}
			if (bModified)
				pTileSet->UpdateAllViews(NULL,TSV_UPDATE_CATEGORY,pCategory);
		}
	}
	return bModified;
}

BOOL CTileSetView::DoPasteTiles(CTileSetOp& op)
{
	BOOL bModified = FALSE;
	CTileSet *pTileSet = GetDocument();
    int i, iCount = op.m_tileIndex.GetSize();
	int iTileCount = pTileSet->GetTileCount();
	CCategory *pCategory;

	if (m_iCurrentView == TSV_GROUPS)
	{
		// TBD: what does it mean to copy a bunch of tiles to a group window
		MessageBeep(MB_ICONQUESTION);
		return FALSE;
	}

	if (m_iTileCategory == 0)
	{
		// Assuming DoPaste() has already been called,
		// we're done; we've pasted all the tiles (or category items)
		// into the current tileset.
	}
	else
	{
		// add the selected tiles to the current category
		pCategory = pTileSet->GetTileCategory(m_iTileCategory-1);
		for (i=0; i < iCount; i++)
		{
			int iTile = op.m_tileIndex[i]; // get dst index
			ASSERT(iTile >= 0);
			if ((iTile < iTileCount) && pCategory->AddItem(iTile)) // verify index & add
				bModified = TRUE;
		}
		if (bModified) 
			pTileSet->UpdateAllViews(NULL,TSV_UPDATE_CATEGORY,pCategory);
	}
	return bModified;
}

void CTileSetView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint & TSV_UPDATE_PALETTE)
	{
		RealizePalette(FALSE); // TBD: what if this is the active view?
		GetDocument()->UpdateMaps(MEV_UPDATE_PALETTE);
		lHint &= ~TSV_UPDATE_PALETTE;
	}

	if (lHint & TSV_UPDATE_TRANSPARENCY)
	{
		m_transCtrl.SetColor(GetDocument()->m_rgbTransparent);
		lHint &= ~TSV_UPDATE_TRANSPARENCY;
	}

	if (lHint)
	{
		if (lHint & TSV_UPDATE_ITEM)
			RenewItemCtrl(TRUE);

		CCategory *pCategory = GetCurrentCategory();
		if ( ((lHint & TSV_UPDATE_CATEGORY) && (pHint == pCategory)) ||
			 ((lHint & TSV_UPDATE_GROUPS) && (m_iCurrentView == TSV_GROUPS)) ||
			 (lHint & TSV_UPDATE_LIST))
		   RenewListCtrl(TRUE);
		if ((lHint & TSV_ADD_TILE) && m_iCurrentView == TSV_TILES)
		{
		//	TRACE("Adding tile %d\n",(int)pHint);
			m_listCtrl.AddItem((int)pHint);
		}
		// TBD: lHint & TSV_DELETE_xxx
		return;
	}

	// TBD: again this is heavy handed but we can optimize it later
	RenewTabCtrl(FALSE); // always first because it may update the current category
	RenewItemCtrl(FALSE);
	RenewListCtrl(FALSE);
	AdjustControls();
}


// Select and realize our palette.
BOOL CTileSetView::RealizePalette(BOOL bForceBkgnd)
{
    // We are going active, so realize our palette.
	CPalette *pPal = GetPalette();
    if (pPal == NULL) 
		return FALSE;

	CDC *pDC = GetDC();
    CPalette *poldpal = pDC->SelectPalette(pPal, bForceBkgnd);
    UINT u = pDC->RealizePalette();

    // If any colors have changed or we are in the
    // background, repaint the lot.
    if (u || bForceBkgnd) 
	{
        InvalidateRect(NULL, TRUE); // Repaint
		UpdateWindow();
    }
    pDC->SelectPalette(poldpal, TRUE);
    ReleaseDC(pDC);
    return (BOOL) u; // TRUE if some colors changed
}

void CTileSetView::OnPaletteChanged(CWnd* pFocusWnd)
{
    // See if the change was caused by us and ignore it if not.
    if ((pFocusWnd == this) || IsChild(pFocusWnd))
		return;

    RealizePalette(TRUE); // Realize in background.
}

BOOL CTileSetView::OnQueryNewPalette()
{
    return RealizePalette(FALSE); // Realize in foreground.
}

void CTileSetView::OnActivateView(BOOL bActivate, CView* pAcView, CView* pDeacView)
{
    if (bActivate) 
	{
	//	TRACE("%s Activate %lx\n",GetDocument()->GetTitle(), this);
		GetParentFrame()->OnUpdateFrameTitle(TRUE);
		OnQueryNewPalette();
	}
	CFormView::OnActivateView(bActivate, pAcView, pDeacView);
}

void CTileSetView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate(); // allocate the windows/controls

	m_viewCtrl.DeleteAllItems();

	TC_ITEM item;
	CString tab;
	item.mask = TCIF_TEXT;

	VERIFY(tab.LoadString(IDS_TILES));
	item.pszText = (LPSTR)((LPCTSTR)tab);
    m_viewCtrl.InsertItem(TSV_TILES, &item);
 	
	VERIFY(tab.LoadString(IDS_GROUPS));
	item.pszText = (LPSTR)((LPCTSTR)tab);
    m_viewCtrl.InsertItem(TSV_GROUPS, &item);
 	
	m_viewCtrl.SetCurSel(m_iCurrentView);

	OnUpdate(NULL,NULL,NULL);	  // update everything
}

void CTileSetView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpdi) 
{
	CTileSet *pTileSet = GetDocument();
	int iItem = pTileSet->m_iCurrentItem;
    switch(nIDCtl)
	{
		case IDC_TILESET_ITEM:
			if (pTileSet->m_iCurrentType == TSV_GROUPS)
			{
				CTileGroup *pGroup = pTileSet->GetCurrentGroup();
				if (pGroup != NULL)
				{
					pTileSet->DrawGroup(lpdi->hDC, pGroup, CRect(lpdi->rcItem));
					iItem = -1;
				}
			}
			if (iItem >= 0 && iItem < pTileSet->GetTileCount())
			{
				pTileSet->DrawWithPalette(lpdi->hDC, iItem, lpdi->rcItem);
			}
			break;
		default:
			CFormView::OnDrawItem(nIDCtl, lpdi);
			break;
	}
}

void CTileSetView::OnSelchangeTilesetList() 
{
	int iItem = m_listCtrl.GetLastItem(); // get the list item that was last selected
	if (iItem < 0)
		return;

    iItem = m_listCtrl.GetItemData(iItem); // get the data associated with the item

	// set the current item which in turn will update all the views
	GetDocument()->SetCurrentItem(m_iCurrentView, iItem);
}

void CTileSetView::OnEditSelectAll() 
{
	ASSERT(m_listCtrl.GetCount());
	m_listCtrl.SelItemRange(TRUE, 0, m_listCtrl.GetCount()-1);
}

void CTileSetView::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_listCtrl.GetCount() > 0);	
}

void CTileSetView::OnUpdateTilesetFindDup(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetTileCount() > 0);
}

void CTileSetView::OnTilesetFindDup() 
{
	GetDocument()->DoFindDuplicates(TRUE, this);
}

void CTileSetView::OnTransparentColor() 
{
	COLORREF color = GetDocument()->m_rgbTransparent;
	if (DoChooseColor(this,color))
	{
		CWaitCursor wait;
		GetDocument()->SetTransparencyColor(color);
		GetDocument()->UpdateMaps(MEV_UPDATE_TRANSPARENT);
		m_transCtrl.SetColor(color);
	}
}

void CTileSetView::OnUpdateEditSelectNone(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelected());	
}




void CTileSetView::OnUpdateTilesetShowusage(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(GetDocument()->HasOpenMaps());
}

void CTileSetView::OnTilesetShowusage() 
{
	CShowUsageDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		CTileSet *pTileSet = GetDocument();
		CWaitCursor wait;
		CTileList usage;
	    pTileSet->GetUsage(usage);
		if (m_iCurrentView != TSV_TILES)
		{
			m_iCurrentView = TSV_TILES;
			m_iTileCategory = 0;
			RenewListCtrl(FALSE);
		}
		int iThreshold = dlg.m_iUsageThreshold;
		int iTileCount = pTileSet->GetTileCount();
		ASSERT(usage.GetSize() == iTileCount);
		for (int i=0; i < iTileCount; i++)
		{
			m_listCtrl.SetSel(i,usage[i] <= iThreshold);
		}
		m_listCtrl.UpdateWindow();
		GetParentFrame()->SetActiveView(this,TRUE);// so user can use Ctrl-X to remove these tiles.

	}		
}

CCategory * CTileSetView::GetCurrentCategory()
{
	if (m_iCurrentView == TSV_TILES)
	{
		if (m_iTileCategory > 0)
		   return GetDocument()->GetTileCategory(m_iTileCategory-1);
	}
	else if (m_iGroupCategory > 0)
	{
		return GetDocument()->GetGroupCategory(m_iGroupCategory-1);
	}
	return NULL;
}



void CTileSetView::OnEditProperties() 
{
   CNewTileSetDlg dlg(this);
   CTileSet *pDoc = GetDocument();
   dlg.m_nTileWidth = pDoc->m_iTileWidth;
   dlg.m_nTileHeight = pDoc->m_iTileHeight;

   dlg.m_bCompactOnSave = pDoc->m_bCompactOnSave;
   dlg.m_rgbTransparent = pDoc->m_rgbTransparent;
   dlg.m_bUseBitmapWidth = pDoc->m_bUseBitmapWidth;
   dlg.m_nBitmapWidth = pDoc->GetBitmapWidth();
   dlg.m_pszData = pDoc->m_sInitData;
   dlg.m_iCurrent = pDoc->GetTileCount();
   dlg.m_iInit = pDoc->m_iInitTiles;
   if (dlg.DoModal() == IDOK)
   {
       pDoc->m_bCompactOnSave = dlg.m_bCompactOnSave;
	   BOOL bUpdate = FALSE;
	   TRY
	   {
		   if (!dlg.m_pszData.IsEmpty())
		   {
			   bUpdate = pDoc->ReLoadBitmap(dlg.m_pszData,dlg.m_rgbTransparent);
			   pDoc->m_sInitData = dlg.m_pszData;
		   }
		   if (pDoc->m_rgbTransparent != dlg.m_rgbTransparent)
		   {
			   pDoc->SetTransparencyColor(dlg.m_rgbTransparent);
			   bUpdate = TRUE;
		   }
		   if (pDoc->m_bUseBitmapWidth != dlg.m_bUseBitmapWidth)
		   {
			   pDoc->m_bUseBitmapWidth = dlg.m_bUseBitmapWidth;
			   pDoc->SetModifiedFlag();
		   }
		   if (dlg.m_bUseBitmapWidth)
		   {
			   if (dlg.m_nBitmapWidth != pDoc->m_nBitmapWidth)
			   {		   
				   pDoc->m_nBitmapWidth = dlg.m_nBitmapWidth;
				   pDoc->OnTilesetCompact();
				   bUpdate = TRUE;
			   }
		   }
	   }
	   END_TRY
	   if (bUpdate)
	   {
		   pDoc->SetModifiedFlag();
		   pDoc->UpdateAllViews(NULL, TSV_UPDATE_TRANSPARENCY|TSV_UPDATE_PALETTE);
		   pDoc->UpdateAllViews(NULL);
	   }
   }
}


void CTileSetView::OnUpdateEditAttributes(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelected() && GetDocument()->HasAttributes() && m_iCurrentView == TSV_TILES);
}

void CTileSetView::OnEditAttributes() 
{
	// TBD: if no tiles are selected bring up the 'tileset' attributes dialog instead.
	// for now, bring up the 'tile' attributes dialog.
	ASSERT(IsSelected());
	int iLastItem = m_listCtrl.GetLastItem();
	if (iLastItem < 0) 
		iLastItem = m_listCtrl.GetCount()-1;
	iLastItem = m_listCtrl.GetItemData(iLastItem);
	CTileSet *pDoc = GetDocument();
	CAttributeSheet dlg(IDS_TILE, pDoc, (void *)iLastItem, this);
	if (dlg.DoModal() == IDOK)
	{
		CWaitCursor wait;
		int iCount = m_listCtrl.GetCount();
		if (m_listCtrl.GetSelCount() == 1)
			pDoc->AdjustAttributes(iLastItem, dlg.m_pAttributePage->m_attributes);
		else for (int i=0; i < iCount; i++)
		{
			if (m_listCtrl.GetSel(i))
			{
				int iTile = m_listCtrl.GetItemData(i);
				pDoc->AdjustAttributes(iTile, dlg.m_pAttributePage->m_attributes);
			}
		}
	}
}



void CTileSetView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	if (menu.LoadMenu(IDR_TILESETPOPUP))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	}
}
