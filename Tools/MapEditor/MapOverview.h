// MapOverview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapOverview dialog

class CMapOverview : public CMapEditorView
{
// Construction
protected:
	CRect m_updateRect;
	CMapOverview();   // standard constructor
    DECLARE_DYNCREATE(CMapOverview);
	virtual void OnUpdateSizes();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapOverview)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_updateHeight;
	BOOL OnIdleUpdate();
	CMapEditorDoc *GetDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual ~CMapOverview();
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapOverview)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MapEditorView.cpp
inline CMapEditorDoc* CMapOverview::GetDocument()
   { return (CMapEditorDoc*)m_pDocument; }
#endif
