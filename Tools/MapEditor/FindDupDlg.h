// FindDupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindDupDlg dialog 
// Asks the user for the search tolerance value.
//

class CFindDupDlg : public CDialog
{
// Construction
public:
	CFindDupDlg(int iTolerance, int iMaxTol, CWnd* pParent = NULL);  

// Dialog Data
	//{{AFX_DATA(CFindDupDlg)
	enum { IDD = IDD_FINDDUPLICATES };
	CStatic	m_maxCtrl;
	int     m_iMaxTol;
	int		m_iTolerance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindDupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindDupDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
