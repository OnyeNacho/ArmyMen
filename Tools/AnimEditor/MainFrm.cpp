// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "AnimEditor.h"

#include "MainFrm.h"
#include "AnimEditorDoc.h"
#include "AnimEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_SEQUENCE_NEW, OnUpdateSequenceNew)
	ON_UPDATE_COMMAND_UI(ID_SPECIAL_HSPOTCATALOGSAVE, OnUpdateSpecialHspotcatalogsave)
	ON_UPDATE_COMMAND_UI(ID_SPECIAL_HSPOTSEQCELTOCATALOG, OnUpdateSpecialHspotseqceltocatalog)
	ON_UPDATE_COMMAND_UI(ID_SPECIAL_HSPOTCATALOGTOSEQCELS, OnUpdateSpecialHspotcatalogsave)
	ON_UPDATE_COMMAND_UI(ID_SEQUENCE_DELETE, OnUpdateSequenceDelete)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
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
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
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

//-----------------------------------------------------------------------------------------------------------------
void CMainFrame::OnUpdateSequenceNew(CCmdUI* pCmdUI) 
{
	//	Indicate to user when they are about to create a new sequence that's a copy of the one they have selected.
	BOOL bCopy = FALSE;

	//	Copied largely from CAnimEditorDoc::OnSequenceNew()...
	CAnimEditorDoc* pDoc = (CAnimEditorDoc*)MDIGetActive()->GetActiveDocument();
	if( pDoc )
	{
		CView* pViewActive = MDIGetActive()->GetActiveView();
		POSITION posSeq = pDoc->lstSeqs.GetHeadPosition();
		CSequence* pSeq;
		while( posSeq )
		{
			pSeq = pDoc->lstSeqs.GetNext( posSeq );
			if( (CView*)pSeq->pSeqView == pViewActive )
			{
				//	Found a SequenceView that matches active view.
				bCopy = TRUE;
			}
		}
	}
	pCmdUI->SetText( bCopy ? "New Sequence (Info will follow that of currently selected sequence)" : "New Sequence" );	
}

//-----------------------------------------------------------------------------------------------------------------
void CMainFrame::OnUpdateSequenceDelete(CCmdUI* pCmdUI) 
{
	//	Ensure that a SequenceView has focus.
	//	Copied from OnUpdateSequenceNew()...
	BOOL bOk = FALSE;

	CAnimEditorDoc* pDoc = (CAnimEditorDoc*)MDIGetActive()->GetActiveDocument();
	if( pDoc )
	{
		CView* pViewActive = MDIGetActive()->GetActiveView();
		POSITION posSeq = pDoc->lstSeqs.GetHeadPosition();
		CSequence* pSeq;
		while( posSeq )
		{
			pSeq = pDoc->lstSeqs.GetNext( posSeq );
			if( (CView*)pSeq->pSeqView == pViewActive )
			{
				//	Found a SequenceView that matches active view.
				bOk = TRUE;
			}
		}
	}
	pCmdUI->Enable( bOk );
}

//-----------------------------------------------------------------------------------------------------------------
void CMainFrame::OnUpdateSpecialHspotseqceltocatalog(CCmdUI* pCmdUI) 
{
	//	 Option only valid if sitting on a seqcel(s) in an active sequenceview.
	pCmdUI->Enable( FALSE );
	CAnimEditorDoc* pDoc = (CAnimEditorDoc*)MDIGetActive()->GetActiveDocument();
	if( pDoc )
	{
		CView* pViewActive = MDIGetActive()->GetActiveView();
		POSITION posSeq = pDoc->lstSeqs.GetHeadPosition();
		CSequence* pSeq;
		while( posSeq )
		{
			pSeq = pDoc->lstSeqs.GetNext( posSeq );
			if( (CView*)pSeq->pSeqView == pViewActive )
			{
				//	Found a SequenceView that is active.
				if( pSeq->iCountSelected() )		//	There must be a seqcel selected.
				{
					pCmdUI->Enable( TRUE );
					break;
				}
			}
		}
	}	
}

//-----------------------------------------------------------------------------------------------------------------
void CMainFrame::OnUpdateSpecialHspotcatalogsave(CCmdUI* pCmdUI) 
{
	//	This also handles what would be called OnUpdateSpecialHspotcatalogtoseqcels().

	//	Option only valid if sitting on AnimEditorView and cel(s) selected.
	pCmdUI->Enable( FALSE );
	CAnimEditorDoc* pDoc = (CAnimEditorDoc*)MDIGetActive()->GetActiveDocument();
	if( pDoc )
	{
		CView* pViewActive = MDIGetActive()->GetActiveView();
		if( pViewActive->IsKindOf( RUNTIME_CLASS( CAnimEditorView ) ) && pDoc->iCountSelected() )
			pCmdUI->Enable( TRUE );
	}	
}

