// MyPropertySheet.h : header file
//
// This class defines custom modal property sheet 
// CMyPropertySheet for the overall application.
 
#ifndef __MYPROPERTYSHEET_H__
#define __MYPROPERTYSHEET_H__
#include "AppPropPage.h"
#include "ScenPropPage.h"
#include "PropPageAmen.h" // sigh so much for consistency

/////////////////////////////////////////////////////////////////////////////
// CMyPropertySheet

class CMyPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropertySheet)

// Construction
public:
	CMyPropertySheet(CWnd* pParentWnd = NULL);

// Attributes
public:
    CAppPropPage m_appPage;
    CScenPropPage m_scenarioPage;
	CPropPageAmen m_armyMenPage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyPropertySheet();

// Generated message map functions
protected:
	//{{AFX_MSG(CMyPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __MYPROPERTYSHEET_H__