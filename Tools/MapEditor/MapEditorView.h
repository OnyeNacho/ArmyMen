// MapEditorView.h : interface of the CMapEditorView class
//
/////////////////////////////////////////////////////////////////////////////
#include "MapLayer.h"
#include "MapEditorDoc.h"

class CMapEditorView : public CScrollView
{
protected: 
	CMapLayerMode m_mode;      
	BOOL m_bSelect;       // TRUE when user is selecting tiles, FALSE when user is deselecting tiles
	BOOL m_bActive;       // TRUE when this is the active view
	CRect m_focusRect;
	CPoint m_anchor;      // starting tile position for cloning, selecting, repositioning view
	CPoint m_cloneLast;   // last tile position for cloning
	CPoint m_cloneHi;     // last tile highlighted (for cloning)
	BOOL m_bUseLast;
	CPoint m_lastold;
	CMapEditorView();     // create from serialization only
	DECLARE_DYNCREATE(CMapEditorView)

	virtual void OnUpdateSizes();
	void ErasePreview();
	void DoClone(CPoint point, int iRow, int iColumn);
	void SetClone(int iRow, int iColumn);
	void SetViewCursor(LPCSTR lpszCursorName);

// Attributes
public:
	CMapEditorDoc* GetDocument();
    CTileSet* GetTileSet() { return GetDocument()->GetTileSet(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL RealizePalette(BOOL bForceBkgnd);
	void OnButtonUp(UINT nFlags, CPoint point);
	void DoSelect();

// Generated message map functions
protected:
	//{{AFX_MSG(CMapEditorView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditProperties();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditSelect();
	afx_msg void OnUpdateEditSelect(CCmdUI* pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCancelOp();
	afx_msg void OnCancelMode();
	afx_msg void OnUpdateEditClone(CCmdUI* pCmdUI);
	afx_msg void OnEditClone();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnUpdateViewReposition(CCmdUI* pCmdUI);
	afx_msg void OnViewReposition();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEditScripts();
	afx_msg void OnSelectArea();
	afx_msg void OnEditViewable();
	afx_msg void OnEditExpand();
	afx_msg void OnEditRotate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MapEditorView.cpp
inline CMapEditorDoc* CMapEditorView::GetDocument()
   { return (CMapEditorDoc*)m_pDocument; }
#endif
