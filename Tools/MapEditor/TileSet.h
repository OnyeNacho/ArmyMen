///////////////
// CTileSet
///////////////
#ifndef _CTILESET_H_
#define _CTILESET_H_
#include "TileCategory.h"
#include "TileGroup.h"
#include "TileList.h"
#include "TileAttribute.h"

#include "dib.h"
#include "dibpal.h"
#include "dibdoc.h"
#include "ColorButton.h"

// predefined tileset views
#define TSV_TILES 0       
#define TSV_GROUPS 1      // for now this must be the index of the last built-in view

// tileset update hints/actions
#define TSV_UPDATE_PALETTE      0x0001
#define TSV_UPDATE_ITEM         0x0002
#define TSV_UPDATE_LIST         0x0004
#define TSV_UPDATE_TRANSPARENCY 0x0008

#define TSV_UPDATE_CATEGORY     0x0010  
#define TSV_UPDATE_GROUPS       0x0020  
#define TSV_ADD_GROUP           0x0040
#define TSV_ADD_TILE            0x0080

class CRemDupDlg;    // extern declaration
class CDupSearchDlg; // extern declaration
class CMapEditorDoc;

// Note: using transparency tables is way too slow when there are lots of overlay tiles
//#define USE_TRANSPARENCY_TABLES   

#ifdef USE_TRANSPARENCY_TABLES
#define MAPEDIT_VERSION_MODIFIER "t"
#else
// TBD: using transparency mask doesn't seem to work for all bitmap sizes
#define MAPEDIT_VERSION_MODIFIER ""
#endif

class CTileSet : public CDocument, public CAttributeTarget
{
protected:
	// attributes
    CTypedPtrList<CPtrList, CMapEditorDoc *> m_mapList; // list of open maps using this tileSet
	CCategoryList m_tileCategories;                // list of tile categories
	CCategoryList m_groupCategories;               // list of group categories
	CArray<CTileGroup, CTileGroup&> m_groups;
    DECLARE_SERIAL(CTileSet)
	BOOL m_bOldDataFormat;  // TBD: this is temporary!
    BOOL m_bCompactOnSave;
	BOOL m_bUseBitmapWidth;
	UINT m_nBitmapWidth;

	CDibDoc m_dib;	  	  // device independent data for this tileset
    CTileList m_tileMap;  // one entry per dib location  // TBD: replace with bitArray
	CTileList m_tileList; // list of currently used tile positions within the dib
	CTileList m_searchList;  // temporary tile list list used for find duplicates & show usage.
    int m_iMaxTiles;      // maximum number of tiles this dib can hold
	int m_iTilesWide;     // number of tiles that can fit horizontally in m_dib
	int m_iTolerance ;    // # of different pixels to tolerate for duplicate detection

	// bitmap and mask for displaying the current group. This has been
	// centralized here (for want of a better place) so multiple views 
	// can share the same group bitmap. This bitmap is only allocated
	// when current item is a group.
	HBITMAP m_hGroupBitmap;
	HBITMAP m_hGroupMask;

	CTypedPtrList<CObList, CTileAttribute *> m_attributeList; // added v2.8
    CTileGroup *m_pTemporaryGroup;

#ifdef USE_TRANSPARENCY_TABLES
	RGBQUAD *m_pRGBColors, *m_pRGBWhite, *m_pRGBBlack;
#endif

	CPoint GetTileLocation(int iTileIndex); // get location of tile in dib
	void InitContents();

	// operations
	int FindEmptyTile();
	int FindDuplicate(int iTile, int iTileStart, int& iMinDiff, CDupSearchDlg *pDlg = NULL);
    int FindDuplicates(CWnd *pWnd = NULL);
	void EndSearch();
	void InitSearch(BOOL bCheckDepth, int iInitValue);
	BOOL Create(int iTileWidth, int iTileHeight, int iTileDepth, int iTolerance,int nTiles=20, RGBQUAD *pRGB = NULL,UINT nBitmapWidth = g_nBitmapWidth);
	BOOL Create(CString lpszDataPath, int iTileWidth, int iTileHeight, int iTolerance, BOOL bUseBitmapWidth, UINT nBitmapWidth);
    BOOL PreSaveDocument();
	void DestroyGroupPreview();
	void CreateGroupPreview();
	BOOL RemoveDuplicates();
	void ExportArmyMen(LPCSTR lpszPathName);

public:
	// attributes
	int m_iTileWidth;
	int m_iTileHeight;
    int m_iCurrentItem;     // currently selected tile, group, or category
	int m_iCurrentType;     // view type for currently selected item
	COLORREF m_rgbTransparent;
	UINT m_nTransparentColor;
	CString m_sInitData;
	int m_iInitTiles;
	void SetTransparencyColor(COLORREF color);

	BOOL ReadOnly();
	CFrameWnd * GetFrameWnd();
	CString GetClipID();

	CTileSet(); // for serialization only
	virtual ~CTileSet();

	// tile manipulation
	void MatchMap();
	int GetTileCount() const { return m_tileList.GetSize(); } 
    BOOL RemoveTile(int iTileIndex);
	int CopyTile(CTileSet *pSrc, int nIndex);
	void DoFindDuplicates(BOOL bInteractive = TRUE, CWnd *pWnd = NULL);
	CSize GetTileSize() const { return CSize(m_iTileWidth, m_iTileHeight); }
	int GetTileDepth() { return m_dib.GetDIB() ? m_dib.GetDIB()->GetDepth() : 0; }
	UINT GetBitmapWidth() { return m_dib.GetDIB() ? m_dib.GetDIB()->GetWidth() : 0; }
	BOOL ReplaceTile(int iTile, int iReplacement);
	void GetUsage(CTileList& usage);

	// tile category manipulation
	int GetTileCategoryCount() { return m_tileCategories.GetCount(); }
	CCategory *GetTileCategory(int iIndex) 
	{ 
		POSITION pos = m_tileCategories.FindIndex(iIndex);
		return m_tileCategories.GetAt(pos); 
	}

	// group category manipulation
	int GetGroupCategoryCount() { return m_groupCategories.GetCount(); }
	CCategory *GetGroupCategory(int iIndex)
	{
		POSITION pos = m_groupCategories.FindIndex(iIndex);
		return m_groupCategories.GetAt(pos);
	}
	// group manipulation
	int GetGroupCount() const { return m_groups.GetSize(); }
	int AddGroup(LPCTSTR lpszTitle=NULL, int iWidth=0, int iHeight=0, BOOL bInteractive=FALSE);
	CTileGroup *GetGroup(LPCTSTR lpszTitle);
    BOOL RemoveGroup(int iIndex);
    BOOL RemoveGroup(LPCTSTR lpszTitle) { return RemoveGroup(GetGroupIndex(lpszTitle)); }
	int GetGroupIndex(LPCTSTR lpszTitle);
	CTileGroup *GetGroupAt(int iIndex) { return &m_groups[iIndex]; }
	void DrawGroup(HDC hdc, CTileGroup *pGroup, CPoint pt, CSize tileSize);
	void DrawGroup(HDC hdc, CTileGroup *pGroup, CPoint pt, BOOL bTransparent, CDIB *pDIB);

	CSize GetGroupExtent(CTileGroup *pGroup);
	void DrawGroup(HDC hdc, CTileGroup *pGroup, CRect rect);
	CTileGroup * GetCurrentGroup();
	CTileGroup * SetTemporaryGroup(CTileGroup *pGroup);

	// mapList manipulation
	void AddMap(CMapEditorDoc *pMap);
    void RemoveMap(CMapEditorDoc *pMap);
    BOOL HasOpenMaps() { return (!m_mapList.IsEmpty()); }

	// dib && palette manipulation
	CDIB *GetDIB() { return m_dib.GetDIB(); }
	CPalette *GetPalette() { return m_dib.GetPalette(); }
	HPALETTE GetHPalette() { return m_dib.GetHPalette(); }
	void CopyPalette(CPalette *pPal) { m_dib.CopyPalette(pPal); }
	int ComparePalettesAndAsk(CPalette *pPal);

	// miscellaneous operations
	CDibDoc * CreateCompatibleDIB(UINT nWidth, UINT nHeight);
	HDC BeginDraw(HDC hdc = NULL) 
	{ 
		ASSERT(m_dib.GetDIB()); 
		return m_dib.GetDIB()->CreateHDC(hdc); 
	}
	void EndDraw()  
	{	
		ASSERT(m_dib.GetDIB()); 
		m_dib.GetDIB()->DeleteHDC(); 
	}

	BOOL Draw( HDC hdc, int nTile, RECT& dstRect);
	BOOL Draw( HDC hdc, int nTile, POINT& pt, BOOL bTransparent = FALSE, CDIB *pDst = NULL);
	BOOL Draw( CDC *pDC, int nTile, POINT& pt) { return Draw(pDC->GetSafeHdc(), nTile, pt); }
	BOOL DrawWithPalette( HDC hdc, int nTile, RECT& dstRect);
	BOOL OnNewDocument(CTileSet *pSrcTileSet, int nTiles);
	void Resize(int iTileCount); // grow the bitmap to store at least iTileCount tiles 
    BOOL ReLoadBitmap(LPCTSTR lpszBitmapPath, COLORREF rgbTransparent);

	void SetCurrentItem(int iItemType, int iItem);
	void UpdateMaps(int iStartTile, int iEndTile);
	void UpdateMaps(UINT lHint=0);
	void UpdateModifiedMaps();
	void UpdateTransparency();
	void PreviewCurrentGroup(HDC hdc, CPoint pt, BOOL bTransparent, CDIB *pDIB);

	// CAttributeTarget commands
	virtual POSITION GetFirstAttribute() { return m_attributeList.GetHeadPosition(); }
	virtual int GetAttributeCount() { return m_attributeList.GetCount(); }
	virtual void GetNextAttribute(POSITION& pos, void *pTargetData, CAttributeInfo& rInfo);
   
	// Additional attribute commands
    // TBD: we might want to roll some of these into CAttributeTarget
	CTileAttribute *FindAttribute(const CString& pszName);
    BOOL HasAttributes() { return !m_attributeList.IsEmpty(); }
	CTileAttribute *AddAttribute(CTileAttribute *pAttribute);
	CTileAttribute *AddAttribute(LPCTSTR pszName, int nBitCount, int nDefaultValue);
	CTileAttribute *GetAttribute(int iIndex);
	CTileAttribute *GetNextAttribute(POSITION& pos) { return m_attributeList.GetNext(pos); }

	BOOL GetAttribute(const CString& pszName, int iTile, int& iValue);
	BOOL SetAttribute(const CString& pszName, int iTile, int iValue);
    void AdjustAttributes(int iTile, const CAttributeResult &rAttributes);

    BOOL DeleteAttribute(CTileAttribute *pAttribute);

#ifdef _DEBUG
	void AssertValid() const;
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTileSet)
	public:
	virtual BOOL OnNewDocument();
	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnChangedViewList();
	//}}AFX_VIRTUAL

	// Generated message map functions
public:
	//{{AFX_MSG(CTileSet)
	afx_msg void OnTilesetCompact();
	afx_msg void OnFileExport();
	afx_msg void OnUpdateFileRevert(CCmdUI* pCmdUI);
	afx_msg void OnFileRevert();
	afx_msg void OnUpdateItemType(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemId(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemInfo(CCmdUI* pCmdUI);
	afx_msg void OnTilesetTileCategories();
	afx_msg void OnTilesetGroupCategories();
	afx_msg void OnTilesetUsePalette();
	afx_msg void OnUpdateTilesetUsePalette(CCmdUI* pCmdUI);
	afx_msg void OnTilesetRemapToPalette();
	afx_msg void OnUpdateTilesetRemapToPalette(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
