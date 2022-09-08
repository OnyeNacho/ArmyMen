// CMultipleSequencesView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultipleSequencesView view

#include "CSequenceView.h"

class CSequence;

class CMultipleSequencesView : public CScrollView
{
protected:
	CMultipleSequencesView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMultipleSequencesView)

// Attributes
protected:
	CTypedPtrList< CObList, CSequenceView* >	lstSequenceViews;

public:

// Operations
private:

public:
	CSequenceView*	AddNewSequence( CSequence* pSequenceNew );
	void			DeleteSequenceView( CSequenceView* pSeqViewVictim );
	void			Arrange();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultipleSequencesView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMultipleSequencesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMultipleSequencesView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
