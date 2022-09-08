// CategoriesDlg.h : header file
//
#include "TileCategory.h"

/////////////////////////////////////////////////////////////////////////////
// CCategoriesDlg dialog

class CCategoriesDlg : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CCategoriesDlg(CCategoryList *pCategories, UINT nTitleID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCategoriesDlg)
	enum { IDD = IDD_CATEGORIES };
	CEdit	m_titleCtrl;
	CButton	m_upButton;
	CButton	m_newButton;
	CButton	m_downButton;
	CButton	m_deleteButton;
	CListBox m_listCtrl;
	CString	m_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategoriesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateTitle();
	void UpdateCategory(int iIndex, CCategory* pCategory);
	BOOL FindItem(LPCTSTR lpszTitle);

	CToolTipCtrl m_tooltip;
	CCategoryList *m_pCategories;
	UINT m_nTitleID;

	virtual BOOL OnInitDialog();
	void DelBitmap(CButton& button);

	// Generated message map functions
	//{{AFX_MSG(CCategoriesDlg)
	afx_msg void OnDestroy();
	afx_msg void OnNewItem();
	afx_msg void OnSelchangeCategoryList();
	afx_msg void OnChangeCategoryTitle();
	afx_msg void OnDeleteItem();
	afx_msg void OnUpItem();
	afx_msg void OnDownItem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
