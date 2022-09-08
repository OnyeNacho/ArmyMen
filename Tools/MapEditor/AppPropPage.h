// AppPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppPropPage dialog

class CAppPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CAppPropPage)

// Construction
public:
	CAppPropPage();
	~CAppPropPage();

// Dialog Data
	//{{AFX_DATA(CAppPropPage)
	enum { IDD = IDD_PROP_GENERAL };
	BOOL	m_bOutlinePreview;
	BOOL	m_bActivePreview;
	BOOL	m_bShowFullObjectName;
	BOOL	m_bUseOffScreenDibs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAppPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAppPropPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
