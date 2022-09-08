// ScenarioView.h : header file
//
#ifndef _SCENARIOVIEW_H_
#define _SCENARIOVIEW_H_
/////////////////////////////////////////////////////////////////////////////
// CScenarioView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ObjectSetView.h"

class CScenarioLayer;

class CScenarioView : public CObjectSetView
{
protected:
    CScenarioLayer *m_pScenario;
	CScenarioView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScenarioView)

// Form Data
public:
	//{{AFX_DATA(CScenarioView)
	enum { IDD = IDD_SCENARIO };
	CStatic	m_deployedCtrl;
	CButton	m_itemNameCtrl;
	CEdit	m_totalCtrl;
	CObjectListBox	m_resourceCtrl;
	UINT	m_nTotal;
	CString	m_pszDeployed;
	//}}AFX_DATA

// Attributes
public:
	CScenarioSet *GetDocument();

// Operations
public:

// Overrides
    virtual void AdjustControls();
    virtual void RenewListCtrl(BOOL bRepaint=TRUE);
	virtual void RenewItemCtrl(BOOL bRepaint=TRUE);
    virtual void RenewTabCtrl(BOOL bRepaint=TRUE);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScenarioView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScenarioView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CScenarioView)
	afx_msg void OnSelchangeResource();
	afx_msg void OnKillFocusScenarioTotal();
	afx_msg void OnSelchangeObject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif