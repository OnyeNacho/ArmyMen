// AttributeSheetPreview.h : header file
//
// This file contains the preview window used by the 
// CAttributeSheet property sheet.

/////////////////////////////////////////////////////////////////////////////
// CAttributeSheetPreview window

#ifndef __ATTRIBUTESHEETPREVIEW_H__
#define __ATTRIBUTESHEETPREVIEW_H__

class CAttributeSheetPreview : public CWnd
{
// Construction
public:
	CAttributeSheetPreview();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeSheetPreview)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAttributeSheetPreview();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAttributeSheetPreview)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		// __ATTRIBUTESHEETPREVIEW_H__