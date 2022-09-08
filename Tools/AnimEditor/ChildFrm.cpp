// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "AnimEditor.h"

#include "ChildFrm.h"

#include "AnimEditorView.h"
#include "CMultipleSequencesView.h"
#include "CCelView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	m_wndSplitter.CreateStatic( this, 2, 1,
								WS_CHILD | WS_VISIBLE | WS_BORDER,
								AFX_IDW_PANE_FIRST );
	m_wndSplitter2.CreateStatic( &m_wndSplitter, 1, 2,
								WS_CHILD | WS_VISIBLE | WS_BORDER,
								m_wndSplitter.IdFromRowCol( 0, 0 ) );

	CRect rcWindow;
	GetClientRect( &rcWindow );
	int iDesiredHeight = rcWindow.bottom - rcWindow.top + 1 - 50;
	m_wndSplitter.SetRowInfo( 0, iDesiredHeight, 0 );
	m_wndSplitter.SetRowInfo( 1, 100, 0 );
	m_wndSplitter2.SetColumnInfo( 0, 400, 300 );
	
	VERIFY( m_wndSplitter2.CreateView( 0, 0, RUNTIME_CLASS( CCelView ), CSize( 400, 300 ), pContext ) );
	VERIFY( m_wndSplitter2.CreateView( 0, 1, RUNTIME_CLASS( CAnimEditorView ), CSize( 0, iDesiredHeight ), pContext ) );
	VERIFY( m_wndSplitter.CreateView( 1, 0, RUNTIME_CLASS( CMultipleSequencesView ), CSize( 0, 100 ), pContext ) );

	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
/*	//	xxx
	TRACE( "PreCreateWindow:\n" );

	if( cs.style & WS_BORDER   )
		TRACE( "  WS_BORDER   Creates a window that has a border.\n" );
	if( cs.style & WS_CAPTION   )
		TRACE( "  WS_CAPTION   Creates a window that has a title bar (implies the WS_BORDER style). Cannot be used with the WS_DLGFRAME style.\n" );
	if( cs.style & WS_CHILD   )
		TRACE( "  WS_CHILD   Creates a child window. Cannot be used with the WS_POPUP style.\n" );
	if( cs.style & WS_CLIPCHILDREN   )
		TRACE( "  WS_CLIPCHILDREN   Excludes the area occupied by child windows when you draw within the parent window. Used when you create the parent window.\n" );
	if( cs.style & WS_CLIPSIBLINGS   )
		TRACE( "  WS_CLIPSIBLINGS   Clips child windows relative to each other; that is, when a particular child window receives a paint message, the WS_CLIPSIBLINGS style clips all other overlapped child windows out of the region of the child window to be updated. (If WS_CLIPSIBLINGS is not given and child windows overlap, when you draw within the client area of a child window, it is possible to draw within the client area of a neighboring child window.) For use with the WS_CHILD style only.\n" );
	if( cs.style & WS_DISABLED   )
		TRACE( "  WS_DISABLED   Creates a window that is initially disabled.\n" );
	if( cs.style & WS_DLGFRAME   )
		TRACE( "  WS_DLGFRAME   Creates a window with a double border but no title.\n" );
	if( cs.style & WS_GROUP   )
		TRACE( "  WS_GROUP   Specifies the first control of a group of controls in which the user can move from one control to the next with the arrow keys. All controls defined with the WS_GROUP style after the first control belong to the same group. The next control with the WS_GROUP style ends the style group and starts the next group (that is, one group ends where the next begins).\n" );
	if( cs.style & WS_HSCROLL   )
		TRACE( "  WS_HSCROLL   Creates a window that has a horizontal scroll bar.\n" );
	if( cs.style & WS_MAXIMIZE   )
		TRACE( "  WS_MAXIMIZE   Creates a window of maximum size.\n" );
	if( cs.style & WS_MAXIMIZEBOX   )
		TRACE( "  WS_MAXIMIZEBOX   Creates a window that has a Maximize button.\n" );
	if( cs.style & WS_MINIMIZE   )
		TRACE( "  WS_MINIMIZE   Creates a window that is initially minimized. For use with the WS_OVERLAPPED style only.\n" );
	if( cs.style & WS_MINIMIZEBOX   )
		TRACE( "  WS_MINIMIZEBOX   Creates a window that has a Minimize button.\n" );
	if( cs.style & WS_OVERLAPPED   )
		TRACE( "  WS_OVERLAPPED   Creates an overlapped window. An overlapped window usually has a caption and a border.\n" );
	if( cs.style & WS_OVERLAPPEDWINDOW   )
		TRACE( "  WS_OVERLAPPEDWINDOW   Creates an overlapped window with the WS_OVERLAPPED, WS_CAPTION, WS_SYSMENU, WS_THICKFRAME, WS_MINIMIZEBOX, and WS_MAXIMIZEBOX styles.\n" );
	if( cs.style & WS_POPUP   )
		TRACE( "  WS_POPUP   Creates a pop-up window. Cannot be used with the WS_CHILD style.\n" );
	if( cs.style & WS_POPUPWINDOW   )
		TRACE( "  WS_POPUPWINDOW   Creates a pop-up window with the WS_BORDER, WS_POPUP, and WS_SYSMENU styles. The WS_CAPTION style must be combined with the WS_POPUPWINDOW style to make the Control menu visible.\n" );
	if( cs.style & WS_SYSMENU   )
		TRACE( "  WS_SYSMENU   Creates a window that has a Control-menu box in its title bar. Used only for windows with title bars.\n" );
	if( cs.style & WS_TABSTOP   )
		TRACE( "  WS_TABSTOP   Specifies one of any number of controls through which the user can move by using the TAB key. The TAB key moves the user to the next control specified by the WS_TABSTOP style.\n" );
	if( cs.style & WS_THICKFRAME   )
		TRACE( "  WS_THICKFRAME   Creates a window with a thick frame that can be used to size the window.\n" );
	if( cs.style & WS_VISIBLE   )
		TRACE( "  WS_VISIBLE   Creates a window that is initially visible.\n" );
	if( cs.style & WS_VSCROLL   )
		TRACE( "  WS_VSCROLL   Creates a window that has a vertical scroll bar.\n" );
*/

	cs.style |= WS_MAXIMIZE;
	
	return CMDIChildWnd::PreCreateWindow(cs);

}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers



/////////////////////////////////////////////////////////////////////////////

