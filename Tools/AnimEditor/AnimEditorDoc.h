// AnimEditorDoc.h : interface of the CAnimEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "CCel.h"
#include "CSequence.h"

//class CCelView;
//class CSequenceView;
//class CAnimEditorView;

class CAnimEditorDoc : public CDocument
{
protected: // create from serialization only
	CAnimEditorDoc();
	DECLARE_DYNCREATE(CAnimEditorDoc)

// Attributes
protected:
	CString	csFileExport;		//	File last used as destination of export.
	CString csFileExportRLE;	//	File last used as destination of RLE export.
    LPMALLOC	m_pMalloc;       

public:
	CString	csName;			//	User-assigned name of catalog.
	CString	csFolder;		//	Folder used to load BMP's fram

	CTypedPtrList< CObList, CCel* >				lstCels;		//	List of cels included in catalog.
	CTypedPtrList< CObList, CSequence* >		lstSeqs;		//	List of cel sequences.

	CDIBitmap	docPalette;			//	Bitmap containing the correct palette, loaded first. Loaded from "palette.bmp".


// Operations
private:
	void	Reload(CString &folder);
	void	CheckForLoad();
	void	ResizeViews();

public:
	void	DocModified();
	CCel*	GetCelPtrByFileName( const CString& csFile );
	void	lstCels_Insert( CCel* pCelToInsert );
	void	CelSelect( POSITION posCel, UINT nFlags );
	int		iCountSelected();
	void	PutDataOnClipboard( COleDataSource* pData );
	BOOL	GetDataFromClipboard();
	BOOL	VerifyDeleteSelected();
	CString csUsedInWhatSequences( CCel* pCel );
	BOOL	DeleteSelected( BOOL bDragSelected, BOOL bDeleteLinkedCels );
	void	ConvertSelectedToDragSelected();
	void	ClearDragSelected();

	BOOL	SaveBitmap( const CString& csFile, CBitmap* pBMP, CPalette* pPal, int iWidth, int iHeight );
	BOOL	SaveBitmap( CFile* pfileBMP, CBitmap* pBMP, CPalette* pPal, int iWidth, int iHeight );

	BOOL	Export( BOOL bRLE, BOOL bAuto );
	BOOL	ExportRLEOutOfDate();

	BOOL	bActionsReport( const CString& csHeading );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnimEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
void SetupPalette();
BOOL LoadPalette(CString &csPalette, CString &path, CDC *pDC);
BOOL BrowseForFolder(CString &csPath);
void UpdateNames(CString &oldfolder, CString &newfolder);

// Generated message map functions
protected:
	//{{AFX_MSG(CAnimEditorDoc)
	afx_msg void OnCatalogAddbmp();
	afx_msg void OnUpdateCatalogAddbmp(CCmdUI* pCmdUI);
	afx_msg void OnSequenceNew();
	afx_msg void OnUpdateFileExport(CCmdUI* pCmdUI);
	afx_msg void OnFileExport();
	afx_msg void OnFileExportRle();
	afx_msg void OnCatalogBrowse();
	afx_msg void OnCatalogBrowseAll();
	afx_msg void OnSequenceDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
