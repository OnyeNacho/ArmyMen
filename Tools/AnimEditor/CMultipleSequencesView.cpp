// CMultipleSequencesView.cpp : implementation file
//

#include "stdafx.h"
#include "animeditor.h"
#include "CMultipleSequencesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMultipleSequencesView

IMPLEMENT_DYNCREATE(CMultipleSequencesView, CScrollView)

CMultipleSequencesView::CMultipleSequencesView()
{
	SetScrollSizes( MM_TEXT, CSize( 0, 0 ) );	//	Reset in Arrange(). This is just to set mapping mode.
}

CMultipleSequencesView::~CMultipleSequencesView()
{
	//	Delete dynamically created CSequenceViews (xxx? handled by framework???)  need an AddView()....
}


BEGIN_MESSAGE_MAP(CMultipleSequencesView, CScrollView)
	//{{AFX_MSG_MAP(CMultipleSequencesView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultipleSequencesView drawing

void CMultipleSequencesView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	Arrange();
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CMultipleSequencesView::OnEraseBkgnd(CDC* pDC) 
{
	RECT rcWindow;
	GetClientRect( (LPRECT)&rcWindow );
	CBrush brBack;

	brBack.CreateSolidBrush( theApp.colorDialog );
	pDC->FillRect( &rcWindow, &brBack );

//	return CScrollView::OnEraseBkgnd(pDC);
	return TRUE;
}

//-----------------------------------------------------------------------------------------------------------------
void CMultipleSequencesView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMultipleSequencesView diagnostics

#ifdef _DEBUG
void CMultipleSequencesView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMultipleSequencesView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultipleSequencesView message handlers

void CMultipleSequencesView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonDown(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CMultipleSequencesView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);

	Arrange();
}

//-----------------------------------------------------------------------------------------------------------------
CSequenceView* CMultipleSequencesView::AddNewSequence( CSequence* pSequenceNew )
{
	//	Create a new CSequenceView...
	CSequenceView* pSeqViewNew = new CSequenceView();

	int iCurSeqViewCount = lstSequenceViews.GetCount();

	CRect rcSeq( 0, 0, 0, 0 );
	//	[ Note: New window is sized in Arrange(). ]

	CCreateContext ccSeqView;
	ccSeqView.m_pCurrentDoc = GetDocument();

	VERIFY( pSeqViewNew->Create( NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, 
									rcSeq, this, (UINT)( iCurSeqViewCount+1 ), &ccSeqView ) );
	pSeqViewNew->Initialize( pSequenceNew );

	lstSequenceViews.AddTail( pSeqViewNew );

	Arrange();

	//	Record 'appearance order' in SequenceView.
	pSeqViewNew->csAppearance.Format( "%i", iCurSeqViewCount + 1 );

	return pSeqViewNew;
}

//-----------------------------------------------------------------------------------------------------------------
void CMultipleSequencesView::DeleteSequenceView( CSequenceView* pSeqViewVictim )
{
	POSITION posFound = lstSequenceViews.Find( pSeqViewVictim );
	ASSERT( posFound );

	//	Without this, errors occur when we drop back to windows. Unsure why.
	pSeqViewVictim->SendMessage( WM_DESTROY );

	//	(CWnd destructor calls DestroyWindow() for us.)
	pSeqViewVictim->m_dropTarget.Revoke();
	delete pSeqViewVictim;

	lstSequenceViews.RemoveAt( posFound );
	
	//	Reset 'appearance orders'.
	POSITION posSeqView = lstSequenceViews.GetHeadPosition();
	CSequenceView* pSeqView;
	int iCount = 0;
	while( posSeqView )
	{
		pSeqView = lstSequenceViews.GetNext( posSeqView );
		pSeqView->csAppearance.Format( "%i", ++iCount );
	}

	Arrange();
}

//-----------------------------------------------------------------------------------------------------------------
void CMultipleSequencesView::Arrange()
{
	//	Arranges all child windows and resets my own scroll size.

	//	The CSequenceViews within me are stretched to fit my width.
	//	Their heights are set to their current scroll size height.
	//	They determine for themselves their own "scroll sizes".

	int iYScrollSize = ::GetSystemMetrics( SM_CYHSCROLL );		//	Height of a horizontal scroll bar.
	int	iYEdgeSize = ::GetSystemMetrics( SM_CYEDGE );

	CRect rcThis;
	GetClientRect( &rcThis );
	int	iWidthNew = rcThis.right;		//	Yep, that's right. GetClientRect knows about CRect's insane implementation.

//	CRect rcThisInScreen;
//	GetWindowRect( &rcThisInScreen );

	CPoint ptOriginOffset = GetScrollPosition();

	POSITION posView = lstSequenceViews.GetHeadPosition();
	CSequenceView*	pSeqView;
	int				yPos = 0;
	CRect			rcView;
	while( posView )
	{
		pSeqView = lstSequenceViews.GetNext( posView );
		rcView.SetRect( 0, yPos, iWidthNew, yPos + pSeqView->iHeight + iYEdgeSize * 2 + iYScrollSize + 1 );
		//	[ Extra space added for edges and poss. scrollbar at bottom. ]
		rcView.OffsetRect( -ptOriginOffset );
		pSeqView->MoveWindow( &rcView );
		yPos += pSeqView->iHeight + iYEdgeSize * 2 + iYScrollSize + 1;
	}	
	SetScrollSizes( MM_TEXT, CSize( 0, yPos + 1 ), CSize( 0, 100 ), CSize( 0, 20 ) );
	InvalidateRect( NULL );
}

