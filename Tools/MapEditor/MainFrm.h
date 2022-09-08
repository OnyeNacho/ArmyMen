// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#include "LayerBar.h"

class CMainFrame : public CMDIFrameWnd
{
	void DockControlBarLeftOf(CControlBar* Bar,CControlBar* LeftOf);
	DECLARE_DYNAMIC(CMainFrame)
public:
	void ShowStatus(LPCTSTR status);
	void AddLayer(LPCTSTR lpszTitle, BOOL bVisible, BOOL bActive);
	void ResetLayersList();
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CLayerBar    m_wndLayerBar;
	CStatusBar   m_wndStatusBar;
	CToolBar     m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnViewOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
