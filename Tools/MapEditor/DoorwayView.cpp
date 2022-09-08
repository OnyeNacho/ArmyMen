// DoorwayView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "DoorwayView.h"
#include "MapFrame.h"
#include "MapEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoorwayView

IMPLEMENT_DYNCREATE(CDoorwayView, CFormView)

CDoorwayView::CDoorwayView()
	: CFormView(CDoorwayView::IDD)
{
	m_pDoorwayLayer = NULL;
	//{{AFX_DATA_INIT(CDoorwayView)
	m_pszEnd = _T("");
	m_pszStart = _T("");
	//}}AFX_DATA_INIT
}

CDoorwayView::~CDoorwayView()
{
}

void CDoorwayView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoorwayView)
	DDX_Control(pDX, IDC_DOORWAY_ROUTE_COLOR, m_routeColorCtrl);
	DDX_Control(pDX, IDC_DOORWAY_CLEAR, m_clearButton);
	DDX_Control(pDX, IDC_DOORWAY_ROUTE, m_routeButton);
	DDX_Control(pDX, IDC_DOORWAY_COMPUTE, m_doorwayButton);
	DDX_Control(pDX, IDC_DOORWAY_END, m_endButton);
	DDX_Control(pDX, IDC_DOORWAY_START, m_startButton);
	DDX_Control(pDX, IDC_DOORWAY_LIST, m_listCtrl);
	DDX_Control(pDX, IDC_DOORWAY_POINT_COLOR, m_pointColorCtrl);
	DDX_Control(pDX, IDC_DOORWAY_LINE_COLOR, m_lineColorCtrl);
	DDX_Text(pDX, IDC_DOORWAY_END_TEXT, m_pszEnd);
	DDX_Text(pDX, IDC_DOORWAY_START_TEXT, m_pszStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoorwayView, CFormView)
	//{{AFX_MSG_MAP(CDoorwayView)
	ON_BN_CLICKED(IDC_DOORWAY_COMPUTE, OnDoorwayCompute)
	ON_BN_CLICKED(IDC_DOORWAY_LINE_COLOR, OnDoorwayLineColor)
	ON_BN_CLICKED(IDC_DOORWAY_POINT_COLOR, OnDoorwayPointColor)
	ON_CONTROL(CLBN_CHKCHANGE, IDC_DOORWAY_LIST, OnCheckDoorway)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_DOORWAY_ROUTE_COLOR, OnDoorwayRouteColor)
	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
	ON_BN_CLICKED(IDC_DOORWAY_END, OnDoorwayEnd)
	ON_BN_CLICKED(IDC_DOORWAY_START, OnDoorwayStart)
	ON_BN_CLICKED(IDC_DOORWAY_CLEAR, OnDoorwayClear)
	ON_BN_CLICKED(IDC_DOORWAY_ROUTE, OnDoorwayRoute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoorwayView diagnostics

#ifdef _DEBUG
void CDoorwayView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoorwayView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void CDoorwayView::ResetList()
{
	m_listCtrl.ResetContent();
	int iCount = m_pDoorwayLayer->GetDoorwayCount();
	CString pszDoorway;
	CPoint left,right;
    BOOL bDisplayed;

	for (int i=0; i < iCount; i++)
	{
       VERIFY(m_pDoorwayLayer->GetDoorway(i,left,right,bDisplayed));
	   pszDoorway.Format("%05d, %05d  -> %05d, %05d",left.x,left.y,right.x,right.y);
	   int iItem = m_listCtrl.AddString(pszDoorway);
	   m_listCtrl.SetCheck(iItem, bDisplayed);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDoorwayView message handlers

void CDoorwayView::OnDoorwayCompute() 
{
	CWaitCursor();
	m_listCtrl.ResetContent();
	m_pDoorwayLayer->Compute();
	ResetList();
}

void CDoorwayView::OnInitialUpdate() 
{
	CMapFrame *pFrame = STATIC_DOWNCAST(CMapFrame,GetParentFrame());
	ASSERT(pFrame != NULL);

	CMapEditorDoc *pMap = pFrame->GetMap();
	ASSERT(pMap != NULL);

	m_pDoorwayLayer = STATIC_DOWNCAST(CDoorwayLayer, pMap->GetActiveLayer());
	ASSERT(m_pDoorwayLayer != NULL);

	CFormView::OnInitialUpdate();
	
	HINSTANCE hInstance = AfxGetInstanceHandle();
	m_doorwayButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DOORWAY)));
	m_routeButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ROUTE)));
	m_startButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_START)));
	m_endButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_END)));
	m_clearButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DELETE)));

	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);
		m_tooltip.AddTool(GetDlgItem(IDC_DOORWAY_COMPUTE), IDC_DOORWAY_COMPUTE);
		m_tooltip.AddTool(GetDlgItem(IDC_DOORWAY_ROUTE), IDC_DOORWAY_ROUTE);
		m_tooltip.AddTool(GetDlgItem(IDC_DOORWAY_START), IDC_DOORWAY_START);
		m_tooltip.AddTool(GetDlgItem(IDC_DOORWAY_END), IDC_DOORWAY_END);
		m_tooltip.AddTool(GetDlgItem(IDC_DOORWAY_CLEAR), IDC_DOORWAY_CLEAR);

		// since this view is not derived from CFrameWnd we have to
		// enable ToolTips manually.
		EnableToolTips(TRUE);
	}

	m_pointColorCtrl.SetColor(m_pDoorwayLayer->m_pointColor);
	m_lineColorCtrl.SetColor(m_pDoorwayLayer->m_lineColor);
	m_routeColorCtrl.SetColor(m_pDoorwayLayer->m_routeColor);
	AdjustControls();

	UpdateStartText();
	UpdateEndText();
	ResetList();
}

void CDoorwayView::OnDoorwayLineColor() 
{
	COLORREF color = m_pDoorwayLayer->m_lineColor;
	DoChooseColor(this,color);
	if (color != m_pDoorwayLayer->m_lineColor)
	{
		m_pDoorwayLayer->SetLineColor(color);
		m_lineColorCtrl.SetColor(m_pDoorwayLayer->m_lineColor);
	}

}

void CDoorwayView::OnDoorwayPointColor() 
{
	COLORREF color = m_pDoorwayLayer->m_pointColor;
	DoChooseColor(this,color);
	if (color != m_pDoorwayLayer->m_pointColor)
	{
		m_pDoorwayLayer->SetPointColor(color);
		m_pointColorCtrl.SetColor(m_pDoorwayLayer->m_pointColor);
	}
}

void CDoorwayView::OnDoorwayRouteColor() 
{
	COLORREF color = m_pDoorwayLayer->m_routeColor;
	DoChooseColor(this,color);
	if (color != m_pDoorwayLayer->m_routeColor)
	{
		m_pDoorwayLayer->SetRouteColor(color);
		m_routeColorCtrl.SetColor(m_pDoorwayLayer->m_routeColor);
	}
	
}
void CDoorwayView::AdjustControls()
{
	// resize the list control to fill the rest of the window
    if (m_listCtrl.m_hWnd == NULL) return; 
	CRect wndRect, newRect;
	GetWindowRect(&wndRect);

	m_listCtrl.GetWindowRect(&newRect);
	newRect.right = wndRect.right - 5;
	newRect.bottom = wndRect.bottom - 5;
    ScreenToClient(&newRect);
	m_listCtrl.MoveWindow(&newRect,TRUE);
}

void CDoorwayView::OnSize(UINT nType, int cx, int cy) 
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
	AdjustControls();
}


void CDoorwayView::OnCheckDoorway()
{
   int iIndex = m_listCtrl.GetCurSel();
   if (iIndex != LB_ERR)
   {
		m_pDoorwayLayer->DisplayDoorway(iIndex,m_listCtrl.GetCheck(iIndex));
   }
}

void CDoorwayView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint || pHint)
	{
		// doorway or map specific updates go here...
	}
	else
		CFormView::OnUpdate(pSender,lHint,pHint);
	
}

void CDoorwayView::OnDestroy() 
{
	DelBitmap(m_clearButton);
	DelBitmap(m_startButton);
	DelBitmap(m_endButton);
	DelBitmap(m_routeButton);
	DelBitmap(m_doorwayButton);
	CFormView::OnDestroy();
}

void CDoorwayView::DelBitmap(CButton& button)
{
	if (button.m_hWnd)
	{
		HBITMAP hBitmap = button.SetBitmap(NULL);
		if (hBitmap) DeleteObject(hBitmap);
	}
}


BOOL CDoorwayView::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	return CFormView::PreTranslateMessage(pMsg);
}

BOOL CDoorwayView::OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT nID =pNMHDR->idFrom;
    if (pTTT->uFlags & TTF_IDISHWND)
    {
        // idFrom is actually the HWND of the tool
        nID = ::GetDlgCtrlID((HWND)nID);
        if(nID)
		{
            pTTT->lpszText = MAKEINTRESOURCE(nID);
            pTTT->hinst = AfxGetResourceHandle();
            return(TRUE);
        }
    }
    return(FALSE);
}

void CDoorwayView::OnDoorwayEnd() 
{
	m_pDoorwayLayer->SetRouteEnd();
	UpdateEndText();                   
}

void CDoorwayView::UpdateEndText()
{
	m_pszEnd.Format(IDS_DOORWAY_END_TEXT,
		        m_pDoorwayLayer->m_routeEnd.y,
				m_pDoorwayLayer->m_routeEnd.x);
 	UpdateData(FALSE);
}

void CDoorwayView::UpdateStartText()
{
	m_pszStart.Format(IDS_DOORWAY_START_TEXT,
		        m_pDoorwayLayer->m_routeStart.y,
				m_pDoorwayLayer->m_routeStart.x);
	UpdateData(FALSE);
}

void CDoorwayView::OnDoorwayStart() 
{
	m_pDoorwayLayer->SetRouteStart();
	UpdateStartText();
}

void CDoorwayView::OnDoorwayClear() 
{
	m_pDoorwayLayer->Clear();
	ResetList();
}

void CDoorwayView::OnDoorwayRoute() 
{
	m_pDoorwayLayer->ComputeRoute();
}
