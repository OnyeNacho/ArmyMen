// MapFrame.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapFrame.h"
#include "MapEditorDoc.h"
#include "MapEditorView.h"
#include "MapOverview.h"
#include "TileSetView.h"
#include "EmptyView.h"
#include "rulerwnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_PANE_WIDTH 5
#define MIN_PANE_HEIGHT 5

/////////////////////////////////////////////////////////////////////////////
// CMapFrame
//
// Create frame which is capable of displaying a map
// its overview and an activeLayer-specific toolview all at once.
//
//       Map (MapEditorView) | Overview   |
//                           +------------+
//                           | ToolView   |
//                           
IMPLEMENT_DYNCREATE(CMapFrame, CMDIChildWnd)

CMapFrame::CMapFrame()
{
	m_pToolViewClass = NULL;
	m_pRuler1= NULL;
	m_pRuler2 = NULL;
	m_pRuler3 = NULL;
}

CMapFrame::~CMapFrame()
{
}


BEGIN_MESSAGE_MAP(CMapFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMapFrame)
	ON_COMMAND(ID_VIEW_OVERVIEW, OnViewOverview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OVERVIEW, OnUpdateViewOverview)
	ON_WM_MDIACTIVATE()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_OBJECT_ANIMATE, OnUpdateObjectAnimate)
	ON_COMMAND(ID_OBJECT_ANIMATE, OnObjectAnimate)
	ON_COMMAND(ID_VIEW_TOGGLERULER, OnViewToggleruler)
	//}}AFX_MSG_MAP
    ON_REGISTERED_MESSAGE( WM_FINDREPLACE, OnFindReplace )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapFrame message handlers

BOOL CMapFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// Most of this code was lifted from the MFC example "VIEWEX"
	// create a splitter with 1 row, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	m_wndSplitter.SetColumnInfo(0, (lpcs->cx/3)*2, 0);
	// add the second splitter pane - which is a nested splitter with 2 columns
	if (!m_wndSplitter3.CreateStatic(
		&m_wndSplitter,     // our parent window is the first splitter
		1, 2,               // the new splitter is 2 rows, 1 column
		WS_CHILD | WS_VISIBLE,  // style, WS_BORDER is needed
		m_wndSplitter.IdFromRowCol(0, 0)
			// new splitter is in the first row, 2nd column of first splitter
	   ))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}
	
	m_wndSplitter3.SetColumnInfo(0, 20, 20);
	// add the second splitter pane - which is a nested splitter with 2 rows
	if (!m_wndSplitter5.CreateStatic(
		&m_wndSplitter3,     // our parent window is the first splitter
		2, 1,               // the new splitter is 2 rows, 1 column
		WS_CHILD | WS_VISIBLE,  // style, WS_BORDER is needed
		m_wndSplitter3.IdFromRowCol(0, 0)
			// new splitter is in the first row, 2nd column of first splitter
	   ))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}

	m_wndSplitter5.SetColumnInfo(0, 20, 20);
	if (!m_wndSplitter5.CreateView(0, 0,
		RUNTIME_CLASS(CRulerWnd), CSize(20, 20), pContext))
	{
		TRACE0("Failed to create ruler pane\n");
		return FALSE;
	}
	m_wndSplitter5.SetRowInfo(1, 20, 20);
	if (!m_wndSplitter5.CreateView(1, 0,
		RUNTIME_CLASS(CRulerWnd), CSize(20, lpcs->cy-20), pContext))
	{
		TRACE0("Failed to create ruler pane\n");
		return FALSE;
	}
	CRulerWnd *pRuler = (CRulerWnd*)m_wndSplitter5.GetPane(0,0);
	if (NULL != pRuler)
		pRuler->SetType(2);

	m_pRuler1 = (CWnd*)pRuler;

	pRuler = (CRulerWnd*)m_wndSplitter5.GetPane(1, 0);
	if (NULL != pRuler)
		m_pRuler2 = (CWnd*)pRuler;
	
	// add the second splitter pane - which is a nested splitter with 2 rows
	if (!m_wndSplitter4.CreateStatic(
		&m_wndSplitter3,     // our parent window is the first splitter
		2, 1,               // the new splitter is 2 rows, 1 column
		WS_CHILD | WS_VISIBLE,  // style, WS_BORDER is needed
		m_wndSplitter3.IdFromRowCol(0, 1)
			// new splitter is in the first row, 2nd column of first splitter
	   ))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}
	
	m_wndSplitter4.SetRowInfo(0, 20, 20);
	if (!m_wndSplitter4.CreateView(0, 0,
		RUNTIME_CLASS(CRulerWnd), CSize(300, 20), pContext))
	{
		TRACE0("Failed to create ruler pane\n");
		return FALSE;
	}
	pRuler = (CRulerWnd*)m_wndSplitter4.GetPane(0,0);
	if (NULL != pRuler)
		pRuler->SetType(1);
	m_pRuler3 = (CWnd*)pRuler;

	if (!m_wndSplitter4.CreateView(1, 0,
		pContext->m_pNewViewClass, CSize(lpcs->cx, lpcs->cy), pContext))
	{
		TRACE0("Failed to create map pane\n");
		return FALSE;
	}
	SetActiveView((CView*)m_wndSplitter4.GetPane(1, 0), TRUE);

	// add the second splitter pane - which is a nested splitter with 2 rows
	if (!m_wndSplitter2.CreateStatic(
		&m_wndSplitter,     // our parent window is the first splitter
		2, 1,               // the new splitter is 2 rows, 1 column
		WS_CHILD | WS_VISIBLE | WS_BORDER,  // style, WS_BORDER is needed
		m_wndSplitter.IdFromRowCol(0, 1)
			// new splitter is in the first row, 2nd column of first splitter
	   ))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}

	// now create the two views inside the nested splitter
	if (!m_wndSplitter2.CreateView(0, 0,
		RUNTIME_CLASS(CMapOverview), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create overview pane\n");
		return FALSE;
	}

	// TBD: install an *empty* tool view class
	m_pToolViewClass = RUNTIME_CLASS(CEmptyView);
	if (!m_wndSplitter2.CreateView(1, 0, m_pToolViewClass, CSize(0, 0), pContext))
	{
		TRACE0("Failed to temporary tool pane\n");
		return FALSE;
	}
    
	// it all worked, we now have two splitter windows which contain
	//  three different views
	return TRUE;	
}


void CMapFrame::InstallToolPane(CRuntimeClass *pViewClass, CMultiDocTemplate *pTemplate, CDocument *pDoc, BOOL bUpdate)
{
	if (pDoc == NULL)
	{
		// TBD: install an empty tool pane instead
		pViewClass = RUNTIME_CLASS(CEmptyView);
		pTemplate = theApp.m_pMapDocTemplate;
		pDoc = GetMap();
	}

	if (m_pToolViewClass != pViewClass || bUpdate)
	{
		ASSERT(pTemplate != NULL);
		ASSERT(pViewClass != NULL);
		ASSERT(pDoc != NULL);  // TBD: if doc == NULL, install empty pane

		CCreateContext context;
		CRect rect(0,0,0,0);

		context.m_pNewViewClass	= pViewClass;
		context.m_pCurrentDoc = pDoc;
		context.m_pNewDocTemplate = pTemplate;
		context.m_pLastView	= NULL;
		CWnd *pWnd = m_wndSplitter2.GetPane(1,0);
		if (pWnd) pWnd->GetWindowRect(&rect);
		m_wndSplitter2.DeleteView(1,0);
		if (!m_wndSplitter2.CreateView(1, 0, pViewClass, rect.Size(), &context))
		{
			TRACE0("Failed to create tool pane\n");
			m_pToolViewClass = NULL;
			// TBD: raise an exception and install empty view!
		}
		else
		{
			m_wndSplitter2.RecalcLayout();
			CWnd *pWnd = m_wndSplitter2.GetPane(1,0);
			pWnd->SendMessage(WM_INITIALUPDATE); 
			m_pToolViewClass = pViewClass;
		}
	}
}

void CMapFrame::ReInstallToolPane(CRuntimeClass *pViewClass)
{
	if ((m_pToolViewClass == pViewClass) || (m_pToolViewClass == RUNTIME_CLASS(CEmptyView)))
	{
		CMapEditorDoc *pDoc = GetMap();
		CMapLayer *pMapLayer = pDoc->GetActiveLayer();
		if (pMapLayer)
			pMapLayer->Activate(TRUE);
	}
}

BOOL CMapFrame::PaneIsVisible(int iPane)
{
	CWnd *tilePane = m_wndSplitter2.GetPane(iPane,0);
	CRect rect;
	tilePane->GetClientRect(&rect);
	return (rect.Width() >= MIN_PANE_WIDTH && rect.Height() >= MIN_PANE_HEIGHT);
}

CView * CMapFrame::GetToolView()
{
   return DYNAMIC_DOWNCAST(CView, m_wndSplitter2.GetPane(1,0));
}

void CMapFrame::TogglePane(int iPrimary, int iSecondary)
{
	BOOL bShared = PaneIsVisible(iSecondary);
	CRect rect;
    int iHalf,iCurrent;

	if (PaneIsVisible(iPrimary))
	{
		if (bShared)
		{
			m_wndSplitter.GetRowInfo(0,iCurrent,iHalf);
			m_wndSplitter2.SetRowInfo(iPrimary,0,0);
			m_wndSplitter2.SetRowInfo(iSecondary,iCurrent,0);
		}
		else
		{
			GetClientRect(&rect);
			m_wndSplitter.SetColumnInfo(0,rect.Width(),0);
			m_wndSplitter.SetColumnInfo(1,0,0);
		}
	}
	else 
	{
		 GetClientRect(&rect);
		 if (bShared)
		 {
			iHalf = rect.Height()/2;
			m_wndSplitter2.SetRowInfo(0,iHalf,0);
			m_wndSplitter2.SetRowInfo(1,iHalf,0);
		 }
		else 
		{
			iHalf = rect.Width()/2;
			m_wndSplitter.SetColumnInfo(0,iHalf,0);
			m_wndSplitter.SetColumnInfo(1,iHalf,0);
			m_wndSplitter2.SetRowInfo(iPrimary, rect.Height(),0);
			m_wndSplitter2.SetRowInfo(iSecondary, 0, 0);
		}
	}
	m_wndSplitter2.RecalcLayout();
	m_wndSplitter.RecalcLayout();
	UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
void CMapFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{

	// update our parent window first
	GetMDIFrame()->OnUpdateFrameTitle(bAddToTitle);

	if ((GetStyle() & FWS_ADDTOTITLE) == 0)
		return;     // leave child window alone!

	CMapEditorDoc* pMap = GetMap();
	if (bAddToTitle && pMap != NULL)
	{
		CString title = pMap->GetTitle();
		if (m_nWindow > 0)
		{
			title.Format("%s:%d",title,m_nWindow); // multiple views
		}
        CView *pView = GetActiveView();
	    // Add the tool window's document name if it has one...
		if (pView && !pView->IsKindOf(RUNTIME_CLASS(CMapEditorView)))
		{
			CDocument *pDoc = pView->GetDocument();
			if (pDoc)
			{
				title += " - [" + pDoc->GetTitle() + "]";
			}
		}

		AfxSetWindowText(m_hWnd, title);
	}
}


CMapEditorDoc * CMapFrame::GetMap()
{
	CWnd *pView = m_wndSplitter4.GetPane(1,0);
	if ((pView != NULL) && pView->IsKindOf(RUNTIME_CLASS(CMapEditorView)))
		return STATIC_DOWNCAST(CMapEditorView, pView)->GetDocument();
	else
		return NULL;
}

CTileSet * CMapFrame::GetTileSet()
{
	CMapEditorDoc *pDoc = GetMap();
	if (pDoc != NULL)
		return pDoc->GetTileSet();
	else
		return NULL;
}

void CMapFrame::SetRulers(int iMode)
{
	CRulerWnd *pRuler = (CRulerWnd*)m_wndSplitter5.GetPane(1,0);
	if (NULL != pRuler)
	{
		pRuler->m_pSet = GetTileSet();
		pRuler->SetMode(iMode);
	}
	pRuler = (CRulerWnd*)m_wndSplitter4.GetPane(0, 0);
	if (NULL != pRuler)
	{
		pRuler->m_pSet = GetTileSet();
		pRuler->SetMode(iMode);
	}
}
/////////////////////////////////////////////////////////////////////////
// CMapFrame message handlers


void CMapFrame::OnViewOverview() 
{
	TogglePane(0,1);
}

void CMapFrame::OnUpdateViewOverview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(PaneIsVisible(0));
}

void CMapFrame::ShowToolView()
{
	if (!PaneIsVisible(1))	
		TogglePane(0,1);
}

void CMapFrame::HideToolView()
{
	if (PaneIsVisible(1))
		TogglePane(0,1);
}

BOOL CMapFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	CWnd *pView;

	// dispatch the command to the appropriate view
	switch(nID)
	{
		// let the toolview handle the following commands
		case ID_INDICATOR_ITEMTYPE:
		case ID_INDICATOR_ITEMID:
		case ID_INDICATOR_ITEMINFO:
			pView = m_wndSplitter2.GetPane(1,0);
			if (pView != NULL)
				return pView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

		// let the CTileSetView handle the following commands.
		case ID_TILESET_USEPALETTE:
		case ID_TILESET_REMAPTOPALETTE:
		case ID_TILESET_FINDDUP:
		case ID_TILESET_ADDGROUP:
		case ID_TILESET_TILECATEGORIES:
		case ID_TILESET_GROUPCATEGORIES:
		case ID_TILESET_SHOWUSAGE:
		case ID_TILESET_COMPACT:
		case ID_EDIT_PASTE:  // TBD: let the tool view handle this one too.
			pView = m_wndSplitter2.GetPane(1,0);
			if (pView != NULL && pView->IsKindOf(RUNTIME_CLASS(CTileSetView)))
			{
				g_bTemporaryPaste = (GetActiveView() != pView && nID == ID_EDIT_PASTE); // what a kludge!
				BOOL bHandled = pView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
				g_bTemporaryPaste = FALSE; 
				return bHandled;
			}
			break;

		// let the CMapEditorView handle the following commands
		case ID_LAYERS_ACTIVATENEXT:
		case ID_LAYERS_ACTIVATEPREVIOUS:
		case ID_LAYERS_ACTIVATETOP:
		case ID_LAYERS_ACTIVATEBOTTOM:
		case ID_LAYERS_ARRANGE:
		case ID_EDIT_SELECT: //TBD
		case ID_EDIT_FIND:   //TBD
		case ID_EDIT_CLONE:
		case ID_EDIT_WITHATTRIBUTES:
		case ID_EDIT_RANDOMIZE:
		case ID_INDICATOR_ITEMPOS:
		case ID_VIEW_GRID: 
			// pass the command to the CMapEditorView
			CWnd *pView = m_wndSplitter4.GetPane(1,0);
			if (pView != NULL)
				return pView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}

	// pass the command to the active view
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);				
}

void CMapFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	if (pActivateWnd == this)
	{
		GetMap()->InitFrameLayersList();
	}
	SetRulers(0);
}

afx_msg LRESULT CMapFrame::OnFindReplace(WPARAM wParam, LPARAM lParam)
{
	CMapLayer *pMapLayer = GetMap()->GetActiveLayer();
	if (pMapLayer) 
		return pMapLayer->OnFindReplace(wParam, lParam);
	return 0; // TBD
}


BOOL CMapFrame::UpdateOverview()
{
	if (PaneIsVisible(0))
	{
		CMapOverview *pOverview = STATIC_DOWNCAST(CMapOverview, m_wndSplitter2.GetPane(0,0));
		ASSERT(pOverview != NULL);
		return pOverview->OnIdleUpdate();
	}
	return FALSE;
}

CMapEditorView * CMapFrame::GetMapView()
{
	return STATIC_DOWNCAST(CMapEditorView, m_wndSplitter4.GetPane(1,0));
}

void CMapFrame::OnTimer(UINT nIDEvent) 
{
	CMapEditorDoc *pDoc = GetMap();
	if (pDoc->IsAnimating()) 
	{
		pDoc->SingleStep();
		SetTimer(MEV_TIMER_ID, MEV_TIMER_VAL, NULL);
	}
	CMDIChildWnd::OnTimer(nIDEvent);
}

void CMapFrame::OnUpdateObjectAnimate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetMap()->IsAnimating());
}

void CMapFrame::OnObjectAnimate() 
{
	CMapEditorDoc *pDoc = GetMap();
	if (pDoc->IsAnimating())
	{
		KillTimer(MEV_TIMER_ID);
		pDoc->SetAnimating(FALSE);
	}
	else if (SetTimer(MEV_TIMER_ID, MEV_TIMER_VAL, NULL))
	{
		pDoc->SetAnimating(TRUE);
	}
}

void CMapFrame::OnViewToggleruler() 
{
	// TODO: Add your command handler code here
	CRulerWnd * pWnd = (CRulerWnd*)m_wndSplitter5.GetPane(1,0);
	if (NULL != pWnd)
		pWnd->ChangeMode();

	pWnd = (CRulerWnd*)m_wndSplitter4.GetPane(0, 0);
	if (NULL != pWnd)
		pWnd->ChangeMode();
}

void CMapFrame::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (NULL != m_pRuler1)
		delete m_pRuler1;
	if (NULL != m_pRuler2)
		delete m_pRuler2;
	if (NULL != m_pRuler3)
		delete m_pRuler3;
	CMDIChildWnd::PostNcDestroy();
}
