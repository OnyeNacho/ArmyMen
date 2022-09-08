// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MainFrm.h"
#include "MapEditorDoc.h"
#include "MapEditorView.h"
#include "ObjectSet.h"          // for OSV_UPDATE_NAMES
#include "MyPropertySheet.h"
#include "Splash.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef CBRS_BORDER_ALL
#define CBRS_BORDER_ALL (CBRS_BORDER_LEFT|CBRS_BORDER_TOP|CBRS_BORDER_RIGHT|CBRS_BORDER_BOTTOM)
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_COMMAND_EX(ID_VIEW_LAYERBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LAYERBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
    ON_WM_PALETTECHANGED()
    ON_WM_QUERYNEWPALETTE()
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_ITEMTYPE,
	ID_INDICATOR_ITEMID,
	ID_INDICATOR_ITEMINFO,
	ID_INDICATOR_ITEMPOS,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndLayerBar
		if (!m_wndLayerBar.Create(this, CG_IDD_LAYERBAR,
			CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED | CBRS_HIDE_INPLACE,
			ID_VIEW_LAYERBAR))
		{
			TRACE0("Failed to create dialog bar m_wndLayerBar\n");
			return -1;		// fail to create
		}

		m_wndLayerBar.EnableDocking(CBRS_ALIGN_TOP);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBarLeftOf(&m_wndLayerBar,&m_wndToolBar);
	}
#if U_SPLASH
	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
#endif
	return 0;
}


// Taken directly from the MFC DOCKTOOL example.
void CMainFrame::DockControlBarLeftOf(CControlBar* Bar,CControlBar* LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CMDIFrameWnd::PreCreateWindow(cs);
}



/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CMDIFrameWnd::OnPaletteChanged(pFocusWnd);

	// always realize the palette for the active view
	CMDIChildWnd* pMDIChildWnd = MDIGetActive();
	if (pMDIChildWnd == NULL)
		return; // no active MDI child frame
	CView* pView = pMDIChildWnd->GetActiveView();
	if (pView == NULL) return;

	// notify all child windows that the palette has changed
	//TRACE("Send WM_PALETTECHANGED pView =%lx, pFocusWnd=%lx\n", pView, pFocusWnd);
	SendMessageToDescendants(WM_PALETTECHANGED, (WPARAM)pView->GetSafeHwnd());
}

BOOL CMainFrame::OnQueryNewPalette() 
{
	// always realize the palette for the active view
	CMDIChildWnd* pMDIChildWnd = MDIGetActive();
	if (pMDIChildWnd == NULL)
		return FALSE; // no active MDI child frame (no new palette)
	CView* pView = pMDIChildWnd->GetActiveView();
    if (pView == NULL) return FALSE;

 // Tell the currently active view to realize in the foreground.
    int i = pView->SendMessage(WM_QUERYNEWPALETTE,(WPARAM)0,(LPARAM)0);

    // If the mapping didn't change tell all the other 
    // windows that they might want to repaint anyway.
    if (!i) 
	{
		//TRACE("Query Send WM_PALETTECHANGED pView =%lx\n", pView);
        SendMessageToDescendants(WM_PALETTECHANGED, (WPARAM)pView->GetSafeHwnd());
    }
    return (BOOL) i;
}

#if 0
void CMainFrame::OnFileImport() 
{
	CString lpszFilter;
	lpszFilter.LoadString(IDS_TILESET_IMPORT_FILTER);
	CFileDialog dlg(TRUE, NULL, NULL, OFN_LONGNAMES|OFN_FILEMUSTEXIST, lpszFilter);
	if (dlg.DoModal() == IDOK)		
	{
		CTileSet *pTileSet = NULL;
        CMapEditorDoc *pMap = NULL;

		TRY
		{
			BeginWaitCursor();
			pTileSet = new CTileSet;
			ASSERT_NEW(pTileSet);
			if (tileSet.OnNewDocument(dlg.GetPathName())
			{
				RestoreWaitCursor();
				int iWidth = pTileSet->GetDIB()->GetWidth() / pTileSet->m_iTileWidth;
				int iHeight = pTileSet->GetDIB()->GetHeight() / pTileSet->m_iTileHeight;
				pMap = new CMapEditorDoc;
				ASSERT_NEW(pMap);
				if (pMap->OnNewDocument(iWidth,iHeight,pTileSet))
				{
					// add the documents to list of open documents
					// and create views
				}
				
			}
			EndWaitCursor();
		}
		CATCH_ALL(e)
		{
			if (pMap)
			{
				pMap->DeleteContents();
				delete pMap;
			}
			if (pTileSet)
			{
				pTileSet->DeleteContents(); 
				delete pTileSet;
			}
			THROW_LAST();
		}
		END_CATCH_ALL
	}
}
#endif



void CMainFrame::OnViewOptions() 
{
	CMyPropertySheet propSheet;
	if (propSheet.DoModal() == IDOK)
	{
		// general properties
		g_bOutlinePreview = propSheet.m_appPage.m_bOutlinePreview;
		g_bActivePreview = propSheet.m_appPage.m_bActivePreview;
		if (propSheet.m_appPage.m_bUseOffScreenDibs != g_bUseOffScreenDibs)
		{
			g_bUseOffScreenDibs = propSheet.m_appPage.m_bUseOffScreenDibs;
			POSITION pos = theApp.m_pMapDocTemplate->GetFirstDocPosition();
			while (pos != NULL)
			{
				CDocument *pDoc = theApp.m_pMapDocTemplate->GetNextDoc(pos);
				ASSERT(pDoc != NULL);
				pDoc->UpdateAllViews(NULL);
			}
		}
		if (propSheet.m_appPage.m_bShowFullObjectName != g_bShowFullObjectName)
		{
			g_bShowFullObjectName = propSheet.m_appPage.m_bShowFullObjectName;
			POSITION pos = theApp.m_pObjectSetTemplate->GetFirstDocPosition();
			while (pos != NULL)
			{
				CDocument *pDoc = theApp.m_pObjectSetTemplate->GetNextDoc(pos);
				ASSERT(pDoc != NULL);
				pDoc->UpdateAllViews(NULL, OSV_UPDATE_NAMES); 
			}
		}
		// scenario properties
		g_pszScenarioUnits = propSheet.m_scenarioPage.m_pszUnits;
		g_pszScenarioResources = propSheet.m_scenarioPage.m_pszResources;

		// armymen properties
		g_pszArmyMenTriggers[0] = propSheet.m_armyMenPage.m_pszTrigger1;
		g_pszArmyMenTriggers[1] = propSheet.m_armyMenPage.m_pszTrigger2;
		g_pszArmyMenTriggers[2] = propSheet.m_armyMenPage.m_pszTrigger3;
		g_pszArmyMenTriggers[3] = propSheet.m_armyMenPage.m_pszTrigger4;
		g_pszArmyMenTriggers[4] = propSheet.m_armyMenPage.m_pszTrigger5;
		g_pszArmyMenTriggers[5] = propSheet.m_armyMenPage.m_pszTrigger6;
		g_pszArmyMenTriggers[6] = propSheet.m_armyMenPage.m_pszTrigger7;
		g_pszArmyMenTriggers[7] = propSheet.m_armyMenPage.m_pszTrigger8;
	}
	
}

void CMainFrame::ResetLayersList()
{
	ASSERT_VALID(&m_wndLayerBar);
	m_wndLayerBar.m_layerCtrl.ResetContent();
}

void CMainFrame::AddLayer(LPCTSTR lpszTitle, BOOL bVisible, BOOL bActive)
{
	ASSERT_VALID(&m_wndLayerBar);
	int iIndex = m_wndLayerBar.m_layerCtrl.AddItem(lpszTitle, bVisible);
	if (bActive) 
	{
		m_wndLayerBar.m_layerCtrl.SetCurSel(iIndex);
	}
}

void CMainFrame::ShowStatus(LPCTSTR status)
{
	m_wndStatusBar.SetPaneText(0,status,TRUE);
	m_wndStatusBar.UpdateWindow();
}




