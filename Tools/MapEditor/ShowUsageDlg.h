// ShowUsageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowUsageDlg dialog

class CShowUsageDlg : public CDialog
{
// Construction
public:
	CShowUsageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowUsageDlg)
	enum { IDD = IDD_SHOWUSAGE };
	int		m_iUsageThreshold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowUsageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowUsageDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
