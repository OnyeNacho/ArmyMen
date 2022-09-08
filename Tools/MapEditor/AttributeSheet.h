// AttributeSheet.h : header file
//
// This class defines custom modal property sheet 
// CAttributeSheet.
 // CAttributeSheet has been customized to include
// a preview window.
 
#ifndef __ATTRIBUTESHEET_H__
#define __ATTRIBUTESHEET_H__

#include "AttributesDlg.h"
#include "AttributeSheetPreview.h"

/////////////////////////////////////////////////////////////////////////////
// CAttributeSheet

class CAnimMapObject;

class CAttributeSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAttributeSheet)

// Construction
public:
	CAttributeSheet(UINT nTitleID, CAttributeTarget *pTarget, void *pTargetData,CWnd* pParent = NULL);   

// Attributes
public:
	CAttributesDlg *m_pAttributePage;
	CAttributeSheetPreview m_wndPreview;
	CMapEditorDoc *m_pDoc;
	CString *m_pObjs;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAttributeSheet();
		 virtual BOOL OnInitDialog();

// Generated message map functions
protected:
	//{{AFX_MSG(CAttributeSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ATTRIBUTESHEET_H__