#if !defined(AFX_EXPANDDLG_H__9822658A_75B6_11D1_A755_006097A7C6BD__INCLUDED_)
#define AFX_EXPANDDLG_H__9822658A_75B6_11D1_A755_006097A7C6BD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ExpandDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExpandDlg dialog

class CExpandDlg : public CDialog
{
// Construction
public:
	CExpandDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExpandDlg)
	enum { IDD = IDD_EXPAND };
	int		m_iMove;
	int		m_iWidth;
	int		m_iHeight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpandDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExpandDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPANDDLG_H__9822658A_75B6_11D1_A755_006097A7C6BD__INCLUDED_)
