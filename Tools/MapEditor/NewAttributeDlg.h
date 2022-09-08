// NewAttributeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewAttributeDlg dialog

class CNewAttributeDlg : public CDialog
{
// Construction
public:
	CNewAttributeDlg(CWnd* pParent = NULL, LPCTSTR lpszName = NULL); 

// Dialog Data
	//{{AFX_DATA(CNewAttributeDlg)
	enum { IDD = IDD_NEWATTRIBUTE };
	CSpinButtonCtrl	m_bitCtrl;
	CSpinButtonCtrl	m_defaultCtrl;
	CString			m_maxString;
	CString			m_pszName;
	UINT			m_nBitCount;
	int				m_iDefaultValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewAttributeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewAttributeDlg)
	afx_msg void OnDeltaposAttributeBits(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
