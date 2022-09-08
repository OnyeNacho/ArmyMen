// NewTileSetDlg.h : header file
//
#include "ColorButton.h"

/////////////////////////////////////////////////////////////////////////////
// CNewTileSetDlg dialog

class CNewTileSetDlg : public CDialog
{
// Construction
public:
	CNewTileSetDlg(CWnd* pParent = NULL);   // standard constructor
	COLORREF m_rgbTransparent;
// Dialog Data
	//{{AFX_DATA(CNewTileSetDlg)
	enum { IDD = IDD_NEWTILESET };
	CButton	m_dataGroupCtrl;
	CColorButton	m_transCtrl;
	CEdit	m_dataCtrl;
	CString	m_pszData;
	UINT	m_nTileHeight;
	UINT	m_nTileWidth;
	UINT	m_nBitmapWidth;
	BOOL	m_bCompactOnSave;
	BOOL	m_bUseBitmapWidth;
	CString	m_sTileStat;
	int		m_iTiles;
	//}}AFX_DATA
	int m_iCurrent;
	int m_iInit;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewTileSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bPropertySheet; // TRUE if the dialog is being used as a property sheet.
	// Generated message map functions
	//{{AFX_MSG(CNewTileSetDlg)
	afx_msg void OnNewTileSetBrowse();
	afx_msg void OnTransparentColor();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
