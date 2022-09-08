// NewGroupDlg.h : header file
//
#include "TileSet.h"

/////////////////////////////////////////////////////////////////////////////
// CNewGroupDlg dialog

class CNewGroupDlg : public CDialog
{
// Construction
public:
	CTileSet * m_pTileSet;
	CNewGroupDlg(CTileSet *pTileSet, CWnd* pParent = NULL);  

// Dialog Data
	//{{AFX_DATA(CNewGroupDlg)
	enum { IDD = IDD_NEWGROUP };
	CComboBox	m_listCtrl;
	CString	m_pszTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewGroupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewGroupDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
