// dibdoc.h : interface of the CDibDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CDibDoc : public CDocument
{
// Attributes
public:
	BOOL Copy(CDIB *pSrc, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh);
	void CopyPalette(CPalette *pPal);
	CSize GetSize();
    CDibDoc(); // create from serialization only
    DECLARE_DYNCREATE(CDibDoc)
	CDIB* GetDIB() const {return m_pDIB;}
    CDIBPal* GetPalette() {return m_pPal;}
    HPALETTE GetHPalette() { return m_pPal ? (HPALETTE)m_pPal->GetSafeHandle() : NULL; }
    void SetPaletteEntry(UINT i, PALETTEENTRY *pData);

// Operations
public:

// Implementation
public:
    virtual ~CDibDoc();
    virtual void Serialize(CArchive& ar);   // Overridden for document I/O.
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void DeleteContents();
	virtual BOOL OnNewDocument(int iWidth, int iHeight, int iTileDepth=8, RGBQUAD *pRGB = NULL);

	// some very dangerous functions...
	CDIBPal *DetachPal();
	CDIB	*DetachDIB();
	void SetPal(CDIBPal *pPal);
	void SetDIB(CDIB *pDIB);
  
protected:
	virtual BOOL OnNewDocument();

private:
    CDIB* m_pDIB;
    CDIBPal* m_pPal;

// Generated message map functions
protected:
    //{{AFX_MSG(CDibDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
