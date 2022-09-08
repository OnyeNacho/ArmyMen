#if !defined(AFX_SCRIPTSDLG_H__65B67894_2ED6_11D1_9625_006097A7C6BD__INCLUDED_)
#define AFX_SCRIPTSDLG_H__65B67894_2ED6_11D1_9625_006097A7C6BD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScriptsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScriptsDlg dialog

class CScriptsDlg : public CDialog
{
// Construction
public:
	CScriptsDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_sAFile;
	CString m_sAText;
	CString m_sPFile;
	CString m_sPText;

// Dialog Data
	//{{AFX_DATA(CScriptsDlg)
	enum { IDD = IDD_SCRIPTS };
	CString	m_sFile;
	int		m_iScript;
	CString	m_sText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptsDlg)
	afx_msg void OnListChange();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTSDLG_H__65B67894_2ED6_11D1_9625_006097A7C6BD__INCLUDED_)
