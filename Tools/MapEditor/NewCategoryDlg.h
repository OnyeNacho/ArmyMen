// NewCategoryDlg.h : header file
//
#include "TileSet.h"

/////////////////////////////////////////////////////////////////////////////
// CNewCategoryDlg dialog
class CNewCategoryDlg : public CDialog
{
// Construction
public:
	CTileSet * m_pTileSet;
	CNewCategoryDlg(CTileSet *pTileSet, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewCategoryDlg)
	enum { IDD = IDD_NEWCATERGORY };
	CComboBox	m_listCtrl;
	CString	m_pszTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCategoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewCategoryDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
