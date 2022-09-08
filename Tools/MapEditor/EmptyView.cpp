// EmptyView.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "EmptyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmptyView

IMPLEMENT_DYNCREATE(CEmptyView, CFormView)

CEmptyView::CEmptyView()
	: CFormView(CEmptyView::IDD)
{
	//{{AFX_DATA_INIT(CEmptyView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CEmptyView::~CEmptyView()
{
}

void CEmptyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmptyView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmptyView, CFormView)
	//{{AFX_MSG_MAP(CEmptyView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmptyView diagnostics

#ifdef _DEBUG
void CEmptyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEmptyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEmptyView message handlers

void CEmptyView::OnSize(UINT nType, int cx, int cy) 
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
	
}
