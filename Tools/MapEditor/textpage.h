#if !defined(AFX_TEXTPAGE_H__65B67893_2ED6_11D1_9625_006097A7C6BD__INCLUDED_)
#define AFX_TEXTPAGE_H__65B67893_2ED6_11D1_9625_006097A7C6BD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TextPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextPage dialog

class CTextPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTextPage)

// Construction
public:
	CTextPage();
	~CTextPage();

// Dialog Data
	//{{AFX_DATA(CTextPage)
	enum { IDD = IDD_OBJTEXT };
	CString	m_sTextBlock;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTextPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTextPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTPAGE_H__65B67893_2ED6_11D1_9625_006097A7C6BD__INCLUDED_)
