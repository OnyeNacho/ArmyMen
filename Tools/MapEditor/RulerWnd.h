#if !defined(AFX_RULERWND_H__3B11204C_7A3A_11D1_A75B_006097A7C6BD__INCLUDED_)
#define AFX_RULERWND_H__3B11204C_7A3A_11D1_A75B_006097A7C6BD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RulerWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRulerWnd window

class CRulerWnd : public CWnd
{
// Construction
public:
	DECLARE_DYNCREATE(CRulerWnd)
	CRulerWnd();

// Attributes
public:
	CTileSet *m_pSet;

// Operations
public:
	void SetType(int iType) {m_iType = iType;}
	void SetMode(int iMode);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulerWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ChangeMode();
	virtual ~CRulerWnd();

	// Generated message map functions
protected:
	int m_iMode;
	int m_iType;
	//{{AFX_MSG(CRulerWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULERWND_H__3B11204C_7A3A_11D1_A75B_006097A7C6BD__INCLUDED_)
