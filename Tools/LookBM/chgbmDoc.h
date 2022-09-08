// chgbmDoc.h : interface of the CChgbmDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CChgbmDoc : public CDocument
{
protected: // create from serialization only
	CChgbmDoc();
	DECLARE_DYNCREATE(CChgbmDoc)

// Attributes
public:
	BITMAPFILEHEADER	bmFileHdr;
	BITMAPINFOHEADER	bmInfoHdr; 
	RGBQUAD				bmiColors[256];
	unsigned char		*dataptr;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChgbmDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChgbmDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChgbmDoc)
	afx_msg void OnChangeXppm();
	afx_msg void OnChangeYppm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
