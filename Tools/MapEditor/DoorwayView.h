// DoorwayView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoorwayView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ColorButton.h"
#include "DoorwayLayer.h"

class CDoorwayView : public CFormView
{
protected:
	CDoorwayLayer *m_pDoorwayLayer;
	CDoorwayView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoorwayView)

// Form Data
public:
	//{{AFX_DATA(CDoorwayView)
	enum { IDD = IDD_DOORWAYS };
	CColorButton	m_routeColorCtrl;
	CButton	m_clearButton;
	CButton	m_routeButton;
	CButton	m_doorwayButton;
	CButton	m_endButton;
	CButton	m_startButton;
	CCheckListBox	m_listCtrl;
	CColorButton	m_pointColorCtrl;
	CColorButton	m_lineColorCtrl;
	CString	m_pszEnd;
	CString	m_pszStart;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoorwayView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;

	void AdjustControls();
	void ResetList();
	void DelBitmap(CButton& button);
	void UpdateStartText();
	void UpdateEndText();

	virtual ~CDoorwayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoorwayView)
	afx_msg void OnDoorwayCompute();
	afx_msg void OnDoorwayLineColor();
	afx_msg void OnDoorwayPointColor();
	afx_msg void OnCheckDoorway();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnDoorwayRouteColor();
	afx_msg BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	afx_msg void OnDoorwayEnd();
	afx_msg void OnDoorwayStart();
	afx_msg void OnDoorwayClear();
	afx_msg void OnDoorwayRoute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
