// CNewHotSpotDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewHotSpotDialog dialog

class CNewHotSpotDialog : public CDialog
{

public:
	static CString	csNameLast;

// Construction
public:
	CNewHotSpotDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewHotSpotDialog)
	enum { IDD = IDD_HOTSPOTNEW };
	CString	csHSpotName;
	CString	csSequenceName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewHotSpotDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewHotSpotDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
