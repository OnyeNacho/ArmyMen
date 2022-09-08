// AnimEditorView.h : interface of the CAnimEditorView class
//
/////////////////////////////////////////////////////////////////////////////

class CAnimEditorDoc;

class CAnimEditorView : public CScrollView
{
	//	This view appears in the top half of the frame. It holds the "catalog" of cels for the doc.

protected: // create from serialization only
	CAnimEditorView();
	DECLARE_DYNCREATE(CAnimEditorView)

// Attributes
protected:
	int				iWndColumns, iWndRows, iWndColWidth, iWndRowHeight;
	CFont			fontSmall;
	HCURSOR			hcurQuestion;
	HCURSOR			hcurNormal;

public:
	CAnimEditorDoc* GetDocument();
	COleDropTarget	m_dropTarget;

// Operations
protected:

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnimEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAnimEditorView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopyOrCut(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditPaste();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdateSequenceHotspotnew(CCmdUI* pCmdUI);
	afx_msg void OnSpecialHspotcatalogsave();
	afx_msg void OnSpecialHspotcatalogtoseqcels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AnimEditorView.cpp
inline CAnimEditorDoc* CAnimEditorView::GetDocument()
   { return (CAnimEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
