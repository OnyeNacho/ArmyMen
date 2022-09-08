// NewMapDlg.h : header file
//
#ifndef _NEWMAPDLG_H_
#define _NEWMAPDLG_H_
/////////////////////////////////////////////////////////////////////////////
// CNewMapDlg dialog

#include "ColorButton.h"

class CNewMapDlg : public CDialog
{
// Construction
public:
	COLORREF m_rgbColor;
	CNewMapDlg(CWnd* pParent = NULL);   // standard constructor
    // Note: a non-null window signals that this dialog is being used as
	// a property sheet for an existing map..

// Dialog Data
	//{{AFX_DATA(CNewMapDlg)
	enum { IDD = IDD_NEWMAP };
	CColorButton	m_colorCtrl;
	CEdit	m_scenarioSetCtrl;
	CButton	m_repeatCtrl;
	CEdit	m_objectSetCtrl;
	CEdit	m_tileSetCtrl;
	int		m_iNewWidth;
	int		m_iNewHeight;
	CString	m_pszTileSet;
	BOOL	m_bMapRepeat;
	CString	m_pszObjectSet;
	CString	m_pszScenarioSet;
	CString	m_pszDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewMapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    LPMALLOC m_pMalloc;       
    BOOL m_bPropertySheet; // true when being used as a property sheet
	void BrowseDirectory(int iTitleID, CEdit& rControl);

	// Generated message map functions
	//{{AFX_MSG(CNewMapDlg)
	afx_msg void OnNewMapBrowse();
	afx_msg void OnMapFindObjectDir();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnMapScenBrowse();
	afx_msg void OnMapColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
