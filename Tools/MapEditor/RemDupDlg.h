// RemDupDlg.h : header file
//
#include "TileListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CRemDupDlg dialog
//
// Shows the user a list of duplicate tiles and allows them to select
// one or more duplicate tiles to remove.
//
#define WM_ADD_DUPLICATE (WM_USER + 6000)
#define WM_DONE (WM_USER + 60001)

class CTileSet;

class CRemDupDlg : public CDialog
{
// Construction
public:
	void AddTile(int iTile);
	CTileSet* m_pTileSet;
	CRemDupDlg(CTileSet *pTileSet, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRemDupDlg)
	enum { IDD = IDD_REMOVEDUPLICATES };
	CStatic	m_foundCtrl;
	CDupListBox	m_listCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemDupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CRemDupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRemoveSome();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
