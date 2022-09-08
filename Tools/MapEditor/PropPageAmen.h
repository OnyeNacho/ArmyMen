// PropPageAmen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPageAmen dialog

class CPropPageAmen : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPageAmen)

// Construction
public:
	CPropPageAmen();
	~CPropPageAmen();

// Dialog Data
	//{{AFX_DATA(CPropPageAmen)
	enum { IDD = IDD_PROP_AMEN };
	CString	m_pszTrigger1;
	CString	m_pszTrigger2;
	CString	m_pszTrigger3;
	CString	m_pszTrigger4;
	CString	m_pszTrigger5;
	CString	m_pszTrigger6;
	CString	m_pszTrigger7;
	CString	m_pszTrigger8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPageAmen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPageAmen)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
