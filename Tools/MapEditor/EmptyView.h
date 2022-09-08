// EmptyView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmptyView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CEmptyView : public CFormView
{
protected:
	CEmptyView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEmptyView)

// Form Data
public:
	//{{AFX_DATA(CEmptyView)
	enum { IDD = IDD_EMPTYVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmptyView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEmptyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEmptyView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
