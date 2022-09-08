#if !defined(AFX_MOGDLG_H__4F603E23_4509_11D1_9633_006097A7C6BD__INCLUDED_)
#define AFX_MOGDLG_H__4F603E23_4509_11D1_9633_006097A7C6BD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMogDlg dialog

class CMogDlg : public CDialog
{
// Construction
public:
	CMogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMogDlg)
	enum { IDD = IDD_NEWMOG };
	CString	m_sName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMogDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOGDLG_H__4F603E23_4509_11D1_9633_006097A7C6BD__INCLUDED_)
