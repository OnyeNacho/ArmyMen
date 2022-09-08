// chgbmView.h : interface of the CChgbmView class
//
/////////////////////////////////////////////////////////////////////////////

class CChgbmView : public CView
{
protected: // create from serialization only
	CChgbmView();
	DECLARE_DYNCREATE(CChgbmView)

// Attributes
public:
	CChgbmDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChgbmView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChgbmView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChgbmView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in chgbmView.cpp
inline CChgbmDoc* CChgbmView::GetDocument()
   { return (CChgbmDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
