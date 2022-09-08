// MapFrame.h : header file
//
class CMapEditorDoc;
class CTileSet;
class CMapEditorView;

/////////////////////////////////////////////////////////////////////////////
// CMapFrame frame : this is a frame capable of displaying a map, its
// overview and it tileSet. 

class CMapFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMapFrame)

protected:
	BOOL PaneIsVisible(int iPange);
	void TogglePane(int iPrimary, int iSecondary);
	CMapFrame();           // protected constructor used by dynamic creation

// Attributes
protected:
	CRuntimeClass* m_pToolViewClass;
	CSplitterWnd m_wndSplitter;   // vertical seperator
	CSplitterWnd m_wndSplitter2;  // horizontal seperator
	CSplitterWnd m_wndSplitter3; // Splitter for Rulers
	CSplitterWnd m_wndSplitter4; // Splitter for Rulers
	CSplitterWnd m_wndSplitter5; // Splitter for Rulers
	CWnd *m_pRuler1;
	CWnd *m_pRuler2;
	CWnd *m_pRuler3;
	void OnUpdateFrameTitle(BOOL bAddToTitle);

public:
	CMapEditorView * GetMapView();
	BOOL UpdateOverview();
	CView * GetToolView();
	void HideToolView();
	void ShowToolView();
	void InstallToolPane(CRuntimeClass *pViewClass, CMultiDocTemplate *pTemplate, 
		                 CDocument *pDoc, BOOL bUpdate = FALSE);
	void InstallToolPane(BOOL bUpdate=FALSE)
	{
		InstallToolPane(NULL,NULL,NULL,bUpdate);
	}
	void ReInstallToolPane(CRuntimeClass *pViewClass);

	CTileSet * GetTileSet();
	CMapEditorDoc *GetMap();
	void SetRulers(int iMode);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapFrame)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMapFrame();

	// Generated message map functions
	//{{AFX_MSG(CMapFrame)
	afx_msg void OnViewOverview();
	afx_msg void OnUpdateViewOverview(CCmdUI* pCmdUI);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateObjectAnimate(CCmdUI* pCmdUI);
	afx_msg void OnObjectAnimate();
	afx_msg void OnViewToggleruler();
	afx_msg LRESULT OnFindReplace(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
