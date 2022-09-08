// NumberDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumberDlg dialog

class CNumberDlg : public CDialog
{
// Construction
public:
	CNumberDlg(LPCTSTR lpszCaption, int iNumber, int iMin, int iMax, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNumberDlg)
	enum { IDD = IDD_GETNUMBER };
	int		m_iNumber;
	CString	m_pszCaption;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumberDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iMin;
	int m_iMax;

	// Generated message map functions
	//{{AFX_MSG(CNumberDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
