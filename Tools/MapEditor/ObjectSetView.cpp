// ObjectSetView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapFrame.h"
#include "MapEditorDoc.h"
#include "MapEditorView.h"
#include "ObjectSet.h"
#include "ObjectSetView.h"
#include "AttributeLayer.h"
#include "AttributeSheet.h"
#include "mogdlg.h"
#include "objectlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectSetView 
 

CObjectSetView::CObjectSetView(UINT nIDTemplate/*=CObjectSetView::IDD*/)
	: CFormView(nIDTemplate)
{
	m_iCategory = 0;  // no category
	//{{AFX_DATA_INIT(CObjectSetView)
	//}}AFX_DATA_INIT
	m_bMogsLoaded = FALSE;
}

CObjectSetView::~CObjectSetView()
{
	DeleteMogs();
}

void CObjectSetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectSetView)
	DDX_Control(pDX, IDC_OBJECTSET_CYLCE, m_cycleButton);
	DDX_Control(pDX, IDC_OBJECTSET_LIST, m_listCtrl);
	DDX_Control(pDX, IDC_OBJECTSET_TAB, m_tabCtrl);
	DDX_Control(pDX, IDC_OBJECTSET_ITEM, m_itemCtrl);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CObjectSetView, CFormView)
	//{{AFX_MSG_MAP(CObjectSetView)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_SIZE()
	ON_WM_DRAWITEM()
	ON_NOTIFY(TCN_SELCHANGE, IDC_OBJECTSET_TAB, OnSelchangeObjectCategory)
	ON_LBN_SELCHANGE(IDC_OBJECTSET_LIST, OnSelchangeObject)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_REMAP, OnUpdateObjectRemap)
	ON_COMMAND(ID_OBJECT_REMAP, OnObjectRemap)
	ON_COMMAND(ID_EDIT_ATTRIBUTES, OnEditAttributes)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ATTRIBUTES, OnUpdateEditAttributes)
	ON_COMMAND(ID_OBJECT_CREATEMOG, OnObjectCreateMOG)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_CREATEMOG, OnUpdateObjectCreateMOG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG

void CObjectSetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CObjectSetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CObjectSet* CObjectSetView::GetDocument() // this is slimy but it works...
{
   ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CObjectSet)));
   return (CObjectSet*)m_pDocument;
}

#endif

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CObjectSetView, CFormView)

/////////////////////////////////////////////////////////////////////////////

void CObjectSetView::AdjustControls()
{
	CRect wndRect,newRect,listRect;

	GetWindowRect(&wndRect);
	if (!m_itemCtrl.m_hWnd) return;

	// size m_tabCtrl to fill the rest of the view
	m_tabCtrl.GetWindowRect(&newRect);
	newRect.right = wndRect.right - 5;
	newRect.bottom = wndRect.bottom - 5;
    ScreenToClient(&newRect);
	m_tabCtrl.MoveWindow(&newRect,FALSE);

	// size m_listCtrl to fill the m_tabCtrl area
    m_tabCtrl.GetItemRect(0,&listRect);
	newRect.DeflateRect(5,listRect.Height()+5,5,5);
	m_listCtrl.MoveWindow(&newRect, FALSE);

	Invalidate();
}

void CObjectSetView::RenewListCtrl(BOOL bRepaint /* =TRUE */)
{
	// update the list control to display the correct set of objects
	CWaitCursor wait;
	CObjectSet *pObjectSet = GetDocument();
	m_listCtrl.UseObjectSet(pObjectSet, GetHPalette(), (m_iCategory == 0 && g_bShowFullObjectName)); // this does a ResetContent()

	TRY
	{
		if (m_iCategory == 0)
		{
			// fill the list with the complete set of objects
			int iCount = pObjectSet->GetObjectCount();
			for (int i=0; i < iCount; i++)
			{
				m_listCtrl.AddItem(i);
			}
		}
		else
		{
			// fill the list with only those objects in the current category
			CCategory *pCategory = pObjectSet->GetCategory(m_iCategory - 1);
			if (NULL == pCategory)
			{
				// MOG Mode
				if (!m_bMogsLoaded)
				{
					LoadMogs();
					m_bMogsLoaded = TRUE;
				}
				m_listCtrl.m_pView = this;
				m_listCtrl.SetMog(TRUE);
				int iCount = m_sMogList.GetSize();
				for (int i=0; i < iCount; i++)
				{
					m_listCtrl.AddItem(i);
				}
			}
			else
			{
				int iCount = pCategory->GetItemCount();
				for (int i=0; i < iCount; i++)
				{
					int iItem = pCategory->GetItemAt(i);
					m_listCtrl.AddItem(iItem);
				}
			}
		}
		if (bRepaint) 
			m_listCtrl.UpdateWindow();
	}
	END_TRY
}

void CObjectSetView::RenewItemCtrl(BOOL bRepaint /* =TRUE */)
{
	CObjectSet *pObjectSet = GetDocument();
    ASSERT(pObjectSet != NULL);

	m_itemCtrl.SetButtonStyle(m_itemCtrl.GetButtonStyle(), bRepaint);
	int iItem = pObjectSet->GetCurrentItem();
	if (bRepaint && iItem >= 0)
	{
		int iIndex = m_listCtrl.FindItem(iItem);
		if (m_iCategory != 0)
		{
			if (iIndex < 0)
			{
				m_iCategory = pObjectSet->GetObjectCategory(iItem) + 1;	
				// current object is not in this category
				// reset the list view to show the proper category.
				m_tabCtrl.SetCurSel(m_iCategory); 
				RenewListCtrl(TRUE); 
				iIndex = m_listCtrl.FindItem(iItem);
			}
		}
		m_listCtrl.ResetSelection(iIndex);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CObjectSetView message handlers

// Select and realize our palette.
BOOL CObjectSetView::RealizePalette(BOOL bForceBkgnd)
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

void CObjectSetView::OnPaletteChanged(CWnd* pFocusWnd)
{
    // See if the change was caused by us and ignore it if not.
    if ((pFocusWnd == this) || IsChild(pFocusWnd))
		return;

	RealizePalette(TRUE); // Realize in background.
}

BOOL CObjectSetView::OnQueryNewPalette()
{
    return RealizePalette(FALSE); // Realize in foreground.
}


void CObjectSetView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
    if (bActivate) 
	{
	//	TRACE("%s Activate %lx\n",GetDocument()->GetTitle(), this);
		GetParentFrame()->OnUpdateFrameTitle(TRUE);
		OnQueryNewPalette();
	}
  	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CObjectSetView::OnSize(UINT nType, int cx, int cy) 
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

void CObjectSetView::RenewTabCtrl(BOOL bRepaint/*=TRUE*/)
{
	m_tabCtrl.DeleteAllItems();

	TC_ITEM item;
	CString tab;
	item.mask = TCIF_TEXT;

	VERIFY(tab.LoadString(IDS_OBJECTS));
	item.pszText = (LPSTR)((LPCTSTR)tab);
    m_tabCtrl.InsertItem(0, &item);

	CObjectSet *pObjectSet = GetDocument();
	ASSERT(pObjectSet);

	int iCount = pObjectSet->GetCategoryCount();
	for (int i=0; i < iCount; i++)
	{
		item.pszText = (LPSTR)((LPCSTR)pObjectSet->GetCategory(i)->GetTitle());
		m_tabCtrl.InsertItem(i+1,&item);
	}
	tab.LoadString(IDS_MOG);
	item.pszText = (LPSTR)(LPCTSTR)tab;
	m_tabCtrl.InsertItem(i+1, &item);

	if (m_iCategory > iCount)
		m_iCategory = iCount;

	m_tabCtrl.SetCurSel(m_iCategory);
	if (bRepaint) m_tabCtrl.UpdateWindow();
}

void CObjectSetView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_cycleButton.LoadBitmaps(3, IDB_CYCLEN, IDB_CYCLEF, IDB_CYCLEB);
	m_cycleButton.SetCycleState(0);
    RenewTabCtrl(FALSE);
	RenewListCtrl(FALSE); 
	RenewItemCtrl(FALSE);
	AdjustControls();
}

void CObjectSetView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpdi) 
{
	if (nIDCtl == IDC_OBJECTSET_ITEM)
	{
		CObjectSet *pObjectSet = GetDocument();
		if (pObjectSet)
		{
			if (m_listCtrl.IsMogMode())
			{
				// Mog Mode, Draw each object relatively inside item window
				int iItem = m_listCtrl.GetLastItem();
				if (iItem > 0)
				{
					iItem = m_listCtrl.GetItemData(iItem);
					DrawMog(lpdi->hDC, iItem, lpdi->rcItem, GetHPalette());
				}

			}
			else
			{
				int iItem = pObjectSet->GetCurrentItem();
				if (iItem >= 0 && iItem < pObjectSet->GetObjectCount())
				{
					pObjectSet->DrawWithPalette(lpdi->hDC, iItem, lpdi->rcItem, GetHPalette());
				}
			}
		}
	}
	else
		CFormView::OnDrawItem(nIDCtl, lpdi);
}

void CObjectSetView::OnSelchangeObjectCategory(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR) 
	{
		m_iCategory = m_tabCtrl.GetCurSel();
		RenewListCtrl();
	}
	*pResult = 0;
}

void CObjectSetView::OnSelchangeObject() 
{
	int iItem = m_listCtrl.GetLastItem(); // get the list item that was last selected
	if (iItem < 0)
		return;

    iItem = m_listCtrl.GetItemData(iItem); 

	// set the current item, which in turn will update all the views
	GetDocument()->SetCurrentItem(iItem);
}

void CObjectSetView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint & OSV_UPDATE_TAB)
		RenewTabCtrl();
	if ((lHint & OSV_UPDATE_LIST) ||
		((lHint & OSV_UPDATE_NAMES) && (m_iCategory == 0)))
		RenewListCtrl();
	if (lHint & OSV_UPDATE_ITEM)
		RenewItemCtrl();
 
	if (lHint) return;
	CFormView::OnUpdate(pSender, lHint, pHint);
}

CPalette * CObjectSetView::GetPalette()
{
	CMapFrame *pFrame = DYNAMIC_DOWNCAST(CMapFrame, GetParentFrame());
	if (pFrame)
		return pFrame->GetMap()->GetPalette();
	return NULL;
}

void CObjectSetView::OnUpdateObjectRemap(CCmdUI* pCmdUI) 
{
	CObjectSet *pObjectSet = GetDocument();
	pCmdUI->Enable(pObjectSet && pObjectSet->GetObjectCount());
	
}

void CObjectSetView::OnObjectRemap() 
{
   CPalette *pPalette = GetPalette();
   if (pPalette)
   {
      CObjectSet *pObjectSet = GetDocument();
	  ASSERT(pObjectSet != NULL);
	  pObjectSet->RemapObjects(pPalette);
   }
}


// gets called whenever an object from the current objectset is placed
void CObjectSetView::PlaceItem()
{
   CObjectSet *pObjectSet = GetDocument();
   ASSERT(pObjectSet != NULL);

   UINT nCycleState = m_cycleButton.GetCycleState();
   if (nCycleState != 0)
   {
	   int iItem = pObjectSet->GetCurrentItem();
	   ASSERT(iItem >= 0);

	   int iIndex = m_listCtrl.FindItem(iItem);
	   if (iIndex >= 0)
	   {
		   int iCount = m_listCtrl.GetCount();
		   if (nCycleState == 1) 
			   ++iIndex; // cycle forward
		   else  
			   --iIndex; // cycle backward
		   if (iIndex == iCount)
			   iIndex = 0;
		   else if (iIndex < 0)
			   iIndex = iCount-1;

		   iItem = m_listCtrl.GetItemData(iIndex);
           pObjectSet->SetCurrentItem(iItem);
	   }
   }
}

void CObjectSetView::OnEditAttributes() 
{
	// TODO: Add your command handler code here
	TC_ITEM tcItem;
	char rcBuf[256];
	CAttributeSheet dlg(IDS_OBJECT, this, NULL, NULL);

	dlg.m_pDoc = GetMap();
	
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = (LPSTR)&rcBuf;
	tcItem.cchTextMax = sizeof(rcBuf);
	if (m_tabCtrl.GetItem(m_tabCtrl.GetCurSel(), &tcItem))
		if (0 != strlen(rcBuf))
		{
			dlg.m_pObjs = new CString;
			*dlg.m_pObjs = rcBuf;
		}

	if (IDOK == dlg.DoModal())
	{
		// Save Default Attributes
		dlg.m_pAttributePage->SaveDefaults();
	}
}

void CObjectSetView::OnUpdateEditAttributes(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

int CObjectSetView::GetAttributeCount()
{
	return GetMap()->GetAttributeCount();
}

POSITION CObjectSetView::GetFirstAttribute()
{
	return GetMap()->GetFirstAttribute();
}

void CObjectSetView::GetNextAttribute(POSITION& pos, void *pTargetData, CAttributeInfo& rInfo)
{
	CAttributeLayer *pLayer = GetMap()->GetNextAttribute(pos);
	ASSERT(pLayer != NULL);

	CMapObjectInst *pInstance = (CMapObjectInst *)pTargetData;
	pLayer->GetObjectAttribute(pInstance,GetHotSpot(pInstance),rInfo);
}

CPoint CObjectSetView::GetHotSpot(CMapObjectInst *pInstance)
{
    CObjectSet *pObjectSet = GetMap()->GetObjectSet();
	ASSERT(pObjectSet != NULL);
	if (!pInstance)
		return NULL;
    CMapObject *pObject = pObjectSet->GetObject(pInstance->m_ID);
	ASSERT(pObject != NULL);
	CPoint hotSpot = pObject->GetHotSpot(pInstance->m_iSequence, 
		pInstance->m_iFrame, pInstance->m_bFlipped);
	hotSpot += pInstance->m_location;
	return hotSpot;
}

CMapEditorDoc * CObjectSetView::GetMap()
{
	CSplitterWnd *pWnd = (CSplitterWnd*)GetParent();
	if (NULL == pWnd)
		return NULL;
	CWnd *pView = pWnd->GetPane(0,0);
	if ((pView != NULL) && pView->IsKindOf(RUNTIME_CLASS(CMapEditorView)))
		return STATIC_DOWNCAST(CMapEditorView, pView)->GetDocument();
	else
		return NULL;
}

void CObjectSetView::OnObjectCreateMOG() 
{
	CMogDlg dlg;
	CString sName;
	POSITION pPos;
	int iSel=0;
	int iCur=0;
	int iX=0;
	int iY=0;
	CObjectLayer *pLayer=NULL;
	CMapObjectInst *pInst=NULL;
	SMogObj *pObj=NULL;
	CMapObject *pMapObject=NULL;
	SMog *pMog=NULL;

	CMapEditorDoc *pDoc = GetMap();

	if (NULL == pDoc)
		return;

	pLayer = (CObjectLayer*)pDoc->GetActiveLayer();

	if (NULL == pLayer || FALSE == pLayer->IsKindOf(RUNTIME_CLASS(CObjectLayer)))
		return;

	iSel = pLayer->GetSelCount();
	if (1 >= iSel)
		return;

	if (IDOK == dlg.DoModal())
		sName = dlg.m_sName;
	else
		return;

	pMog = new SMog;
	
	pPos = pLayer->GetFirstObjectPosition();
	while (iCur < iSel && NULL != pPos)
	{
		pInst = pLayer->GetNextObject(pPos);
		if (NULL == pInst)
			continue;
		if (pInst->m_bSelected)
		{
			pMapObject = GetDocument()->GetObject(pInst->m_ID);
			if (NULL == pMapObject)
				continue;
			pObj = new SMogObj;
			pObj->m_sLoc = pInst->m_location;
			pObj->m_sID = pMapObject->GetName();
			pObj->m_sID += _T(".bmp");

			iX = (pMapObject->GetSize().cx + pObj->m_sLoc.x);
			iY = (pMapObject->GetSize().cy + pObj->m_sLoc.y);
			
			if (0 == iCur)
			{
				pMog->m_sBegin.x = pObj->m_sLoc.x;
				pMog->m_sBegin.y = pObj->m_sLoc.y;
				pMog->m_sEnd.x = iX;
				pMog->m_sEnd.y = iY;
			}
			else
			{
				if (pObj->m_sLoc.x < pMog->m_sBegin.x)
					pMog->m_sBegin.x = pObj->m_sLoc.x;
				if (pObj->m_sLoc.y < pMog->m_sBegin.y)
					pMog->m_sBegin.y = pObj->m_sLoc.y;
				
				if (pMog->m_sEnd.x < iX)
					pMog->m_sEnd.x = iX;

				if (pMog->m_sEnd.y < iY)
					pMog->m_sEnd.y = iY;
			}

			pMog->m_sObjs.Add(pObj);
			iCur++;
		}
	}
	CString sPath = *GetMap()->GetObjectPath();
	if (pMog->m_sObjs.GetSize() > 1)
	{
		pMog->m_sName = sName;
		m_sMogList.Add(pMog);
		SaveMog(pMog, sPath);
	}
	RenewListCtrl(TRUE);
}

void CObjectSetView::OnUpdateObjectCreateMOG(CCmdUI* pCmdUI) 
{
	int iSel=0;
	CObjectLayer *pLayer=NULL;
	
	CMapEditorDoc *pDoc = GetMap();
	if (NULL == pDoc)
		return;

	pLayer = (CObjectLayer*)pDoc->GetActiveLayer();
	if (NULL == pLayer || FALSE == pLayer->IsKindOf(RUNTIME_CLASS(CObjectLayer)))
		return;

	iSel = pLayer->GetSelCount();
	if (1 >= iSel)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CObjectSetView::LoadMogs()
{
	CFileFind sFind;
	CString sPath;
	CString sExt;
	SMog *pMog=NULL;
	BOOL bMore=TRUE;

	sPath = *GetMap()->GetObjectPath();
	sExt.LoadString(IDS_MOGEXT);
	sPath += sExt;

	if (FALSE == sFind.FindFile(sPath, 0))
		return;

	bMore = sFind.FindNextFile();

	while (TRUE)
	{
		pMog = LoadMog(sFind.GetFilePath());
		if (NULL != pMog)
			m_sMogList.Add(pMog);
		if (!bMore)
			break;
		bMore = sFind.FindNextFile();
	}
}

SMog* CObjectSetView::LoadMog(CString &sPath)
{
	CFile file;
	int iCount=0;
	int iCur=0;
	SMog *pMog=NULL;
	SMogObj *pObj=NULL;

	if (FALSE == file.Open(sPath, CFile::modeRead|CFile::shareDenyWrite, NULL))
		return NULL;

	CArchive ar(&file, CArchive::load, 4096, NULL);

	pMog = new SMog;
	ar >> pMog->m_sName;
	if (TRUE == IsMog(pMog->m_sName))
	{
		ar.Close();
		file.Close();
		delete pMog;
		return NULL;
	}
	ar >> pMog->m_sBegin;
	ar >> pMog->m_sEnd;
	ar >> iCount;
	if (0 < iCount)
	{
		while (iCur < iCount)
		{
			pObj = new SMogObj;
			ar >> pObj->m_sLoc;
			ar >> pObj->m_sID;
			pMog->m_sObjs.Add(pObj);
			iCur++;
		}
	}
	ar.Close();
	file.Close();

	return pMog;
}

BOOL CObjectSetView::SaveMog(SMog *pMog, CString &sPath)
{
	CFile file;
	CString sExt;
	int iCur=0, iCount=0;
	SMogObj *pObj=NULL;
	sPath += _T("\\");
	sPath += pMog->m_sName;
	sExt.LoadString(IDS_EXTMOG);
	sPath += sExt;

	iCount = pMog->m_sObjs.GetSize();
	if (0 >= iCount)
		return FALSE;
	if (FALSE == file.Open(sPath, CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyWrite, NULL))
		return FALSE;

	CArchive ar(&file, CArchive::store, 4096, NULL);

	ar << pMog->m_sName;
	ar << pMog->m_sBegin;
	ar << pMog->m_sEnd;
	ar << iCount;
	if (1 <= iCount)
	{
		while (iCur < iCount)
		{
			pObj = pMog->m_sObjs[iCur];
			if (NULL != pObj)
			{
				ar << pObj->m_sLoc;
				ar << pObj->m_sID;
			}
			iCur++;
		}
	}

	ar.Close();
	file.Close();
	
	return TRUE;
}

CString CObjectSetView::GetMogName(int iIndex)
{
	CString sRet;
	if (0 == m_sMogList.GetSize())
		return sRet;
	SMog *pMog = m_sMogList[iIndex];
	if (pMog != NULL)
		sRet = pMog->m_sName;

	return sRet;
}

void CObjectSetView::DrawMog(HDC hdc, int iIndex, RECT & dstRect, HPALETTE hPalette)
{
	int iCur=0;
	int iCount=0;
	int iItem=0;
	SMog *pMog=NULL;
	SMogObj *pObj=NULL;
	CObjectSet *pSet = GetDocument();

	pMog = m_sMogList[iIndex];

	if (NULL != pMog)
	{
		iCount = pMog->m_sObjs.GetSize();
		while (iCur < iCount)
		{
			pObj = pMog->m_sObjs[iCur];
			if (NULL != pObj)
			{
				iItem = pSet->FindObject(pObj->m_sID, FALSE);
				if (0 <= iItem)
				{
					pSet->DrawWithPalette(hdc, iItem, dstRect, hPalette);
				}
			}
			iCur++;
		}
	}
}

void CObjectSetView::DeleteMogs()
{
	int iCount = m_sMogList.GetSize();
	int iCur=0;
	int iCur2=0;
	int iCount2=0;
	SMog *pMog=NULL;
	SMogObj *pObj=NULL;

	while (iCur < iCount)
	{
		pMog = m_sMogList[iCur];
		if (NULL != pMog)
		{
			iCur2 = 0;
			iCount2 = pMog->m_sObjs.GetSize();
			while (iCur2 < iCount2)
			{
				pObj = pMog->m_sObjs[iCur2];
				if (NULL != pObj)
					delete pObj;
				iCur2++;
			}
			pMog->m_sObjs.RemoveAll();
			delete pMog;
		}
		iCur++;
	}
	m_sMogList.RemoveAll();
}

SMog* CObjectSetView::GetMog(int iIndex)
{
	return m_sMogList[iIndex];
}

int CObjectSetView::GetMogCount()
{
	return m_sMogList.GetSize();
}

BOOL CObjectSetView::IsMog(CString & sTitle)
{
	int iCur=0;
	int iCount = m_sMogList.GetSize();
	SMog *pMog=NULL;

	while (iCur < iCount)
	{
		pMog = m_sMogList[iCur];
		if (NULL != pMog)
		{
			if (0 == sTitle.CompareNoCase(pMog->m_sName))
				return TRUE;
		}
		iCur++;
	}
	
	return FALSE;
}
