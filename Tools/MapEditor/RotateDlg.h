#if !defined(AFX_ROTATEDLG_H__8F08D4FB_7908_11D1_A75A_006097A7C6BD__INCLUDED_)
#define AFX_ROTATEDLG_H__8F08D4FB_7908_11D1_A75A_006097A7C6BD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RotateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg dialog

class CRotateDlg : public CDialog
{
// Construction
public:
	CRotateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRotateDlg)
	enum { IDD = IDD_ROTATE };
	int		m_iType;
	int		m_iRotDir;
	int		m_iFlipDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ChangeMode();

	// Generated message map functions
	//{{AFX_MSG(CRotateDlg)
	afx_msg void OnRotate();
	afx_msg void OnFlip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTATEDLG_H__8F08D4FB_7908_11D1_A75A_006097A7C6BD__INCLUDED_)
