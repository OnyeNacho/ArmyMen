// AttributesDlg.h : header file
//
#include "Attribute.h"

struct DefAtr
{
	char rcName[100];
	int iValue;
	int iDefValue;
	int iBits;
	int iMax;
};

/////////////////////////////////////////////////////////////////////////////
// CAttributesDlg dialog

class CAttributesDlg : public CPropertyPage
{
public:
	BOOL SaveDefaults();
	// Construction
	CAttributesDlg(UINT nTitleID, CAttributeTarget *pTarget, void *pTargetData);   
	// Attributes
	CAttributeResult m_attributes;
	CMapEditorDoc * m_pDoc;
	CString *m_pObjs;
	CFile *m_pDefile;

// Dialog Data
	//{{AFX_DATA(CAttributesDlg)
	enum { IDD = IDD_ATTRIBUTES };
	CStatic	m_attributeLabel;
	CSpinButtonCtrl	m_valueCtrl;
	CStatic	m_maxCtrl;
	CListCtrl m_listCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL LoadDefaults();

	CAttributeInfo * GetAttribute(int iItem);
	BOOL m_bUpdate;
	int m_iSelected;
	void *m_pTargetData;
	CString m_valueHeader;
	CString m_attributeHeader;
	CAttributeTarget * m_pTarget;
    CImageList m_stateImageList; 
    CString m_pszTitle;

	void SetAttributeValue(int iAttribute, int iValue);
	void UpdateAttribute(int iAttribute);
	void UpdateAttributeValue(int iAttribute,int iValue);
	void UpdateState(int iItem,BOOL bRemoved);
	// Generated message map functions
	//{{AFX_MSG(CAttributesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedAttributeList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposAttributeValueUpdown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeAttributeValue();
	afx_msg void OnKillfocusAttributeValue();
	afx_msg void OnClickAttributeList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
