// ScenPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScenPropPage dialog

class CScenPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CScenPropPage)

// Construction
public:
	CScenPropPage();
	~CScenPropPage();

// Dialog Data
	//{{AFX_DATA(CScenPropPage)
	enum { IDD = IDD_PROP_SCENARIO };
	CString	m_pszResources;
	CString	m_pszUnits;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CScenPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CScenPropPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
