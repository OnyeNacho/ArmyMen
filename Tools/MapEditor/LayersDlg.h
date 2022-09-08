// LayersDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLayersDlg dialog: allows the user to see and manipulate the current
// set of map layers.

class CMapEditorDoc; 
class CMapLayer;     

class CLayersDlg : public CDialog
{

// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CLayersDlg(CMapEditorDoc *pMap, CWnd* pParent = NULL);  

// Dialog Data
	//{{AFX_DATA(CLayersDlg)
	enum { IDD = IDD_LAYERS };
	CListCtrl	m_listCtrl;
	CButton	m_upButton;
	CButton	m_newButton;
	CButton	m_downButton;
	CButton	m_deleteButton;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iSelected;
	CString m_layerHeader;
	CString m_infoHeader;
	CImageList m_stateImageList; 
	CToolTipCtrl m_tooltip;
	CMapEditorDoc *m_pMap;
	void DelBitmap(CButton& button);
    int AddLayer(int iIndex, CMapLayer *pLayer, BOOL bSelected);
    void UpdateState(int iIndex, BOOL bVisible);
    void SelectItem(int iIndex);

	// Generated message map functions
	//{{AFX_MSG(CLayersDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnUpItem();
	afx_msg void OnDownItem();
	afx_msg void OnDeleteItem();
	afx_msg void OnSelchangeLayersList();
	afx_msg void OnNewItem();
	afx_msg void OnEndlabeleditLayerList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedLayerList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickLayerList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
