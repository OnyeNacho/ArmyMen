// AttributeSheetPreview.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AttributeSheetPreview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributeSheetPreview

CAttributeSheetPreview::CAttributeSheetPreview()
{
}

CAttributeSheetPreview::~CAttributeSheetPreview()
{
}


BEGIN_MESSAGE_MAP(CAttributeSheetPreview, CWnd)
	//{{AFX_MSG_MAP(CAttributeSheetPreview)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAttributeSheetPreview message handlers

void CAttributeSheetPreview::OnPaint() 
{
#if 1
	// sample drawing code
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);

	CBrush brushNew(RGB(0,0,255));
	CBrush* pBrushOld = dc.SelectObject(&brushNew);
	dc.Ellipse(rect);
	dc.SelectObject(pBrushOld);
#else
	// TBD: draw my preview
#endif
}

BOOL CAttributeSheetPreview::OnEraseBkgnd(CDC* pDC) 
{
	// Use the same background color as that of the dialog
	//  (property sheet).

	CWnd* pParentWnd = GetParent();
	HBRUSH hBrush = (HBRUSH)pParentWnd->SendMessage(WM_CTLCOLORDLG,
		(WPARAM)pDC->m_hDC, (LPARAM)pParentWnd->m_hWnd);
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(&rect, CBrush::FromHandle(hBrush));
	return TRUE;
}
