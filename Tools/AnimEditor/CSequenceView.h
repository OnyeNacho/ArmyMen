// CSequenceView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSequenceView view

#ifndef CSEQUENCEVIEW_H
#define CSEQUENCEVIEW_H

class CSequence;
class CCelView;

#define CSEQUENCEVIEW_DEFAULTWIDTH	400
#define CSEQUENCEVIEW_DEFAULTHEIGHT	20

class CSequenceView : public CScrollView
{
public:
	CSequenceView();			// protected constructor used by dynamic creation    xxx I made it public for CMultipleSequencesView
	virtual ~CSequenceView();	//													xxx same here
	DECLARE_DYNCREATE(CSequenceView)

// Attributes
private:
	CFont			fontSmall;
	CFont			fontLarge;

public:
	COleDropTarget	m_dropTarget;
	CString			csName;
	CSequence*		pSequence;
	int				iColumnWidth;
	int				iHeight;
	CString			csAppearance;		//	Index of view in list. Added late to help user differentiate them.

// Operations
private:
	BOOL			SelectAtPoint( BOOL bClickCaused, UINT nFlags, CPoint& point );

public:
	void			Initialize( CSequence* pSequence );
	void			CalcSizeChanges();
	CCelView*		GetCelView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSequenceView)
	public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSequenceView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopyOrCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdateSequenceHotspotnew(CCmdUI* pCmdUI);
	afx_msg void OnSequenceHotspotnew();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSpecialHspotseqceltocatalog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
