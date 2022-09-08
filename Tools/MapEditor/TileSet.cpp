#include "stdafx.h" 
#include "MapEditor.h"
#include "TileSet.h"
#include "TileLayer.h"
#include "NewCategoryDlg.h"
#include "NewTileSetDlg.h"
#include "MapEditorDoc.h"
#include "FindDupDlg.h"
#include "DupSearchDlg.h"
#include "RemDupDlg.h"
#include "NewGroupDlg.h"
#include "CategoriesDlg.h"
#include "IFFFile.h"

#define DEFAULT_TOLERANCE 1
#define U_BLIT_TRANSPARENT 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/* Implementation Notes:
**
** m_tileList is the list of currently used tile locations within the dib.
** m_tileMap simply keeps track of used/free dib locations and should
** be replaced by a bit array.
**
** Let's say we had a dib capable of storing 10 tiles and all 10 are used.
** Initially:
**     m_tileList = [0 1 2 3 4 5 6 7 8 9]
**     m_tileMap  = [x x x x x x x x x x]  (x = USED, _ = TS_EMPTY)
**
** but let say user deleted tiles 2,3,5,6, 7,and 9 from the tileset.  
** Now:
**     m_tileList = [0 1 4 8]
**     m_tileMap  = [x x _ _ x _ _ _ x _] 
**
** If the user then adds a new tile, the first unused dib location
** would be used:
**     m_tileList = [0 1 4 8 2]
**     m_tileMap  = [x x x _ x _ _ _ x _]
**
** When you compact the tileset, the used tile locations get 
** consecutively ordered in the dib (the image data gets rearranged).
**
**     m_tileList = [0 1 2 3 4]
**     m_tileMap  = [x x x x x _ _ _ _ _]
**
** m_nTilesWide tells how many tiles can fit in the dib horizontally.
**
** Note: the drawing code would be a faster if we could assume m_nTilesWide
** was 1 or if m_iTileWidth and m_iTileHeight were powers of two but we
** can't so...<sigh>...
*/
#define TS_EMPTY -1 
 
//////////////////////////////////////////////////////
// CTileSet
//////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CTileSet, CDocument)
	//{{AFX_MSG_MAP(CTileSet)
	ON_COMMAND(ID_TILESET_COMPACT, OnTilesetCompact)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_UPDATE_COMMAND_UI(ID_FILE_REVERT, OnUpdateFileRevert)
	ON_COMMAND(ID_FILE_REVERT, OnFileRevert)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMTYPE, OnUpdateItemType)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMID,	OnUpdateItemId)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMINFO, OnUpdateItemInfo)
	ON_COMMAND(ID_TILESET_TILECATEGORIES, OnTilesetTileCategories)
	ON_COMMAND(ID_TILESET_GROUPCATEGORIES, OnTilesetGroupCategories)
	ON_COMMAND(ID_TILESET_USEPALETTE, OnTilesetUsePalette)
	ON_UPDATE_COMMAND_UI(ID_TILESET_USEPALETTE, OnUpdateTilesetUsePalette)
	ON_COMMAND(ID_TILESET_REMAPTOPALETTE, OnTilesetRemapToPalette)
	ON_UPDATE_COMMAND_UI(ID_TILESET_REMAPTOPALETTE, OnUpdateTilesetRemapToPalette)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////

CTileSet::CTileSet() 
{
	InitContents();
}

CTileSet::~CTileSet()
{
	TRACE("TileSet \"%s\" has been destroyed\n", m_strTitle);
	m_mapList.RemoveAll();
}

void CTileSet::InitContents()
{
	m_iCurrentItem = 0;
	m_iCurrentType = TSV_TILES;
	m_iTileHeight =  0;
	m_iTileWidth = 0;
	m_iMaxTiles = 0;
	m_iTilesWide = 0;
	m_iTolerance = DEFAULT_TOLERANCE;
	m_bOldDataFormat = FALSE;
	m_rgbTransparent = g_rgbTransparent;
#ifdef USE_TRANSPARENCY_TABLES
	m_pRGBWhite = NULL;
	m_pRGBBlack = NULL;
	m_pRGBColors = NULL;
#endif
	m_hGroupBitmap = NULL;
	m_hGroupMask = NULL;
	m_pTemporaryGroup = NULL;
	m_bUseBitmapWidth = FALSE;
	m_bCompactOnSave = FALSE;
	m_nBitmapWidth = 0;
	m_sInitData = _T("");
	m_iInitTiles = 0;
}


void CTileSet::SetTransparencyColor(COLORREF color)
{
	m_rgbTransparent = color;
    UpdateTransparency();
}

void CTileSet::UpdateTransparency()
{
	CDIB *pDIB = m_dib.GetDIB();
	ASSERT(pDIB != NULL);

#ifdef USE_TRANSPARENCY_TABLES
	RGBQUAD white,black;

	black.rgbRed = 0;
	black.rgbGreen = 0; 
	black.rgbBlue = 0; 
	black.rgbReserved = 0;

	white.rgbRed = 255; 
	white.rgbGreen = 255; 
	white.rgbBlue = 255; 
	white.rgbReserved = 0;

	m_pRGBColors = pDIB->CopyColorTable(m_pRGBColors);

	// TBD: is there a better way?  this is pretty wasteful...
	// maybe we can get away with only two tables.
	m_pRGBWhite = pDIB->CreateMaskTable(m_pRGBWhite,m_rgbTransparent,white,black,FALSE);
	m_pRGBBlack = pDIB->CreateMaskTable(m_pRGBBlack,m_rgbTransparent,black,white,TRUE);
#else
	pDIB->CreateMask(m_rgbTransparent,GetHPalette());
#endif

	HPALETTE hPalette = GetHPalette();
	if (hPalette)
	{
		m_nTransparentColor = GetNearestPaletteIndex(hPalette, m_rgbTransparent);
	}
	else
		m_nTransparentColor = 0; // TBD:
}


void CTileSet::DeleteContents() 
{
	// Note: this method does not clear m_mapList because
	// presumably re-using the same document would mean 
	// re-using the same m_mapList.  Hopefully this will
	// not get us in trouble later on...
	CDocument::DeleteContents();

#ifdef USE_TRANSPARENCY_TABLES
	delete [] m_pRGBWhite ;
	delete [] m_pRGBBlack ;
	delete [] m_pRGBColors;
#endif

	delete m_pTemporaryGroup;

	m_searchList.RemoveAll();
	m_tileList.RemoveAll();
	m_tileMap.RemoveAll();
	m_dib.DeleteContents();
	DestroyGroupPreview();
	while (!m_tileCategories.IsEmpty())
	{
		CCategory *pCategory = m_tileCategories.RemoveHead();
		delete pCategory;
	}
	while (!m_groupCategories.IsEmpty())
	{
		CCategory *pCategory = m_groupCategories.RemoveHead();
		delete pCategory;
	}
	while (!m_attributeList.IsEmpty())
	{
		CTileAttribute *pAttribute = m_attributeList.RemoveHead();
		delete pAttribute;
	}
	InitContents(); // just in case
}

#ifdef _DEBUG
void CTileSet::AssertValid() const
{
	CDocument::AssertValid();
	int iTileCount = m_tileList.GetSize();
	ASSERT(iTileCount >= 0 && iTileCount <= m_iMaxTiles);
	ASSERT(m_tileMap.GetSize() >= m_iMaxTiles);
	if (iTileCount)
	{
		ASSERT(m_iTileWidth > 0);
		ASSERT(m_iTileHeight > 0);
		ASSERT(m_iTilesWide > 0);
		ASSERT_VALID(&m_dib);

#ifdef USE_TRANSPARENCY_TABLES
		CDIB *pDIB = m_dib.GetDIB();
		if (pDIB->GetNumClrEntries() > 0)
		{
			ASSERT(m_pRGBWhite != NULL);
			ASSERT(m_pRGBBlack != NULL);
			ASSERT(m_pRGBColors != NULL);
			// TBD: other assertions...
		}
#endif
	}
}
#endif

/*
** METHOD
**    CTileSet::Create
**
** PARAMETERS
**    int iTileWidth       -- width of each tile
**    int iTileHeight      -- height of each tile
**    int iTileDepth       -- depth of each tile
**    int iTolerance       -- tolerance value for this tileset
**    int nTiles           -- estimated number of tiles in this tileset
**    RGBQAUD *pRGB        -- optional pointer to color data 
**    UINT nBitmapWidth    -- the desired width of the tileset bitmap
**
** DESCRIPTION
**    Creates a new tileset with the given characteristics.  If lpszDataPath
**    is not empty, tries to load the tile data from given bitmap.  If no
**    bitmap is specified, a default 8-bit per pixel tileset will be created.
**
** RETURNS
**    TRUE if the tileset was successfully created.
**    FALSE if not created (does not issue an error message)
*/
BOOL CTileSet::Create(int iTileWidth, int iTileHeight, int iTileDepth, int iTolerance, 
					  int nTiles, RGBQUAD *pRGB, UINT nBitmapWidth)
{
	ASSERT(iTileWidth > 0);
	ASSERT(iTileHeight > 0);
	ASSERT(iTileDepth > 0);

	m_iTileWidth = iTileWidth;
	m_iTileHeight = iTileHeight;

	int iWidth = max(iTileWidth, (int)nBitmapWidth);
	m_iTilesWide = iWidth/m_iTileWidth; 
	m_iTolerance = iTolerance;

	int iTilesHigh = (nTiles + m_iTilesWide - 1)/m_iTilesWide;
    int iHeight = iTilesHigh * m_iTileHeight;

	if (!m_dib.OnNewDocument(iWidth, iHeight, iTileDepth, pRGB))
		return FALSE;

	CSize size = m_dib.GetSize();
	m_iTilesWide = size.cx / iTileWidth;  // in case large due to alignment restrictions
	m_iMaxTiles = m_iTilesWide * (size.cy / iTileHeight);
	m_tileMap.SetSize(m_iMaxTiles,10);
	m_tileList.SetSize(0,10);
	for (int i=0; i < m_iMaxTiles; i++)
	{
		m_tileMap[i] = TS_EMPTY; // no tiles present
	}
	UpdateTransparency();
	m_iInitTiles = GetTileCount();
	return TRUE;
}

/*
** METHOD
**    CTileSet::Create
**
** PARAMETERS
**    CString lpszDataPath -- optional path to bitmap data for this tileset 
**    int iTileWidth       -- width of each tile
**    int iTileHeight      -- height of each tile
**    int iTolerance       -- tolerance value for this tileset
**    BOOL bUseBitmapWidth -- true if you want to specify a bitmap width
**    UINT nBitmapWidth    -- the desired width of the bitmap
**
** DESCRIPTION
**    Creates a new tileset with the given characteristics.  If lpszDataPath
**    is not empty, tries to load the tile data from given bitmap.  If no
**    bitmap is specified, a default 8-bit per pixel tileset will be created.
**
** RETURNS
**    TRUE if the tileset was successfully created.
**    FALSE (and issues an appropriate error message) if not created.
*/
BOOL CTileSet::Create(CString lpszDataPath, int iTileWidth, int iTileHeight, 
					  int iTolerance, BOOL bUseBitmapWidth, UINT nBitmapWidth)
{
	int nWide, nHigh;
	CSize size;

	m_iTolerance = iTolerance;
    m_iTileWidth = iTileWidth;
	m_iTileHeight = iTileHeight;
    m_bUseBitmapWidth = bUseBitmapWidth;
	m_nBitmapWidth = nBitmapWidth;

	ASSERT(iTileWidth > 0);
	ASSERT(iTileHeight > 0);

	m_sInitData = lpszDataPath;
	if (!lpszDataPath.IsEmpty())
	{
		if (!m_dib.OnOpenDocument(lpszDataPath)) 
		   return FALSE;

		BeginWaitCursor();
	    size = m_dib.GetSize();
		nWide = size.cx / iTileWidth;
		nHigh = size.cy / iTileHeight;
		if (nWide < 1 || nHigh < 1)
		{
			AfxMessageBox(IDS_DIB_TOO_SMALL, MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
			RestoreWaitCursor();
		}
		if (size.cx % iTileWidth || size.cy % iTileHeight)
		{
			if (AfxMessageBox(IDS_BAD_DIB_DIMENSIONS, MB_YESNO | MB_ICONQUESTION) != IDYES)
				return FALSE;
			RestoreWaitCursor();
		}
		CDIB *pDIB = m_dib.GetDIB();
	
		// copy bitmap tiles into image list
		m_iMaxTiles = nWide * nHigh;
		m_tileMap.SetSize(m_iMaxTiles);
		m_tileList.SetSize(m_iMaxTiles);
		m_iTilesWide = nWide;
		UpdateTransparency();

		for (int i=0; i < m_iMaxTiles; i++)
		{
			m_tileList[i] = i;
			m_tileMap[i] = i;
		}
		if (g_pTileLayer)
		{
			CSize size = g_pTileLayer->GetSize();
			int iRow, iCol, iTile, iRepRow, iRepCol;
			for (iRow = 0,iRepRow=0; iRow < size.cy; iRow++)
			{
				for (iCol = 0,iRepCol=0; iCol < size.cx; iCol++)
				{
					if (!g_bMapRepeat && ((iRow >= nHigh) || (iCol >= nWide)))
						iTile = 0; //default tile
					else 
						iTile = iRepRow * nWide + iRepCol;

					g_pTileLayer->SetTile(iRow, iCol, iTile); 
					if (++iRepCol == nWide) 
						iRepCol = 0;
				}
				if (++iRepRow == nHigh) 
					iRepRow = 0;
			}
			g_pTileLayer = NULL;
		}
        if (m_bUseBitmapWidth && m_nBitmapWidth != (UINT)size.cx)
           OnTilesetCompact();
		EndWaitCursor();
	}
	else if (!Create(iTileWidth,iTileHeight,8,iTolerance,m_nBitmapWidth))
		goto error;

	m_iInitTiles = GetTileCount();

	return TRUE;

error:
	AfxMessageBox(IDS_CANT_CREATE_TILESET, MB_OK | MB_ICONEXCLAMATION);
	return FALSE;
}

/*
** METHOD
**    CTileSet::OnNewDocument
**
** PARAMETERS
**    CTileSet* pSrcTileSet -- non-null pointer to source tileset for compatibility
**    int nTiles            -- number of estimated tiles in this tileset (> 0)
**
** DESCRIPTION
**    creates a new empty tileset that has the same tile characteristics
**    as pSrcTileSet.
*/
BOOL CTileSet::OnNewDocument(CTileSet *pSrcTileSet, int nTiles)
{
	if (CDocument::OnNewDocument())
	{
		if (Create(pSrcTileSet->m_iTileWidth, pSrcTileSet->m_iTileHeight,
			              pSrcTileSet->GetTileDepth(), pSrcTileSet->m_iTolerance, nTiles, 
				          pSrcTileSet->m_dib.GetDIB()->GetClrTabAddress(),
					      pSrcTileSet->m_dib.GetDIB()->GetWidth()))
		{
			m_bCompactOnSave = pSrcTileSet->m_bCompactOnSave;
			return TRUE;
		}

	}
	return FALSE;
}


BOOL CTileSet::OnNewDocument() 
{
	BOOL bCreated;
	if (CDocument::OnNewDocument()) // make sure old contents are deleted...
	{
		CNewTileSetDlg dlg;
		if (dlg.DoModal() != IDOK)
			return FALSE;

		bCreated = Create(dlg.m_pszData, dlg.m_nTileWidth, dlg.m_nTileHeight, 
			DEFAULT_TOLERANCE, dlg.m_bUseBitmapWidth, dlg.m_nBitmapWidth);

        // TBD: get default tile/group categories from the game
		return bCreated;
	}
	return FALSE;
}

IMPLEMENT_SERIAL(CTileSet, CDocument, VERSIONABLE_SCHEMA | 5)

// YUK...what a mess...
void CTileSet::Serialize(CArchive& ar) 
{
	CDocument::Serialize(ar);

	if (ar.IsStoring())
	{	
		PUT_SAFE_SCHEMA(ar, CTileSet);
		ar << m_iTileWidth;
		ar << m_iTileHeight;
		ar << m_iTolerance;
		ar << m_iMaxTiles;
		ar << m_iTilesWide;
		ar << m_rgbTransparent;          // schema >= 2
		ar << m_bCompactOnSave;          // schema >= 4
		ar << m_bUseBitmapWidth;         // schema >= 4
		ar << m_nBitmapWidth;            // schema >= 4
		m_tileList.Serialize(ar);
		m_tileMap.Serialize(ar);
		m_tileCategories.Serialize(ar);  // schema >= 3
		m_groupCategories.Serialize(ar); // schema >= 3
		m_groups.Serialize(ar);          
		m_attributeList.Serialize(ar);   // schema >= 5
		m_dib.Serialize(ar);             // THIS MUST BE THE LAST ITEM
		return;
	}
	
	UINT schema = GET_SAFE_SCHEMA(ar, CTileSet, 1);
	if (schema < 1) 
		m_bOldDataFormat = TRUE;
	ar >> m_iTileWidth;
	ar >> m_iTileHeight;
	ar >> m_iTolerance;
	ar >> m_iMaxTiles;
	ar >> m_iTilesWide;
	if (schema >= 2)
		ar >> m_rgbTransparent;
	if (schema >= 4)
	{
		ar >> m_bCompactOnSave;
		ar >> m_bUseBitmapWidth;
		ar >> m_nBitmapWidth;
	}
	else
	{
		m_bCompactOnSave = TRUE;
		m_bUseBitmapWidth = TRUE;
	}
	m_tileList.Serialize(ar);
	m_tileMap.Serialize(ar);
	if (schema >= 3) 
	{
		m_tileCategories.Serialize(ar); 
		m_groupCategories.Serialize(ar);
	}
	else
	{
		CArray<CTileCategory, CTileCategory*> categories;
		categories.Serialize(ar);
		int iCount = categories.GetSize();
		for (int i=0; i < iCount; i++)
		{
			CTileCategory *pCategory = new CTileCategory(categories[i]);
			ASSERT_NEW(pCategory);
			m_tileCategories.AddTail(pCategory);
		}
	}
	m_groups.Serialize(ar);
	if (schema >= 5)
		m_attributeList.Serialize(ar);

	m_dib.Serialize(ar); // THIS MUST BE THE LAST THING READ

	UpdateTransparency();
	if (schema < 4)
		m_nBitmapWidth = GetBitmapWidth(); // after loading dib
	m_iInitTiles = GetTileCount();
}


#if 0
BOOL CTileSet::CanCloseFrame(CFrameWnd* pFrame) 
{
	if (!m_mapList.IsEmpty())
	{
		STATIC_DOWNCAST(CMDIFrameWnd, pFrame->GetParentFrame())->MDINext();
		pFrame->ShowWindow(SW_HIDE);
		return FALSE;
	}
	return CDocument::CanCloseFrame(pFrame);
}
#endif

CFrameWnd * CTileSet::GetFrameWnd()
{
  POSITION pos = GetFirstViewPosition();
  if (pos)
	  return GetNextView(pos)->GetParentFrame();
  else
	  return NULL;
}

/*
** METHOD
**    CTileSet::ReplaceTile
**
** PARAMETERS
**    int iTileIndex -- index of tile you want to replace
**    int iReplacement -- index of tile you want to use as replacement
**                      
** DESCRIPTION
**    Replaces the tile at iTileIndex with iReplacement, 
**    in all the categories and all currently-open maps. Does
**    not delete the tile's image from the tileSet.
**
**    Warning: this is a highly destructive operation!
**    This may adversely effect un-opened maps using this tileset.
**
**    Note: caller is responsible for setting modified flag and
**    updating all views and maps.
*/
BOOL CTileSet::ReplaceTile(int iTileIndex, int iReplacement)
{
	if (iTileIndex >= 0 && iTileIndex < GetTileCount())
	{
		POSITION pos = m_tileCategories.GetHeadPosition();
		while (pos != NULL)
		{
			m_tileCategories.GetNext(pos)->ReplaceItem(iTileIndex, iReplacement);
		}
		int iCount = GetGroupCount();
		for (int i=0; i < iCount; i++)
		{
			GetGroupAt(i)->ReplaceTile(iTileIndex, iReplacement);
		}
		pos = m_mapList.GetHeadPosition();
		while (pos != NULL)
		{
			CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
			ASSERT(pDoc != NULL);
			pDoc->ReplaceTile(iTileIndex, iReplacement);
		}
		if (m_iCurrentType == TSV_TILES && m_iCurrentItem == iTileIndex)
			m_iCurrentItem = iReplacement; // reset the current item

		return TRUE;
	}
	return FALSE;
}

/*
** METHOD
**    CTileSet::RemoveTile
**
** PARAMETERS
**    int iTileIndex -- index of tile you want to remove
**                      
** DESCRIPTION
**    Removes the tile at iTileIndex from the current tileSet, its imageList
**    its categories and all currently-open maps.
**
**    Warning: this is a highly destructive operation!
**    This may adversely effect un-opened maps using this tileset.
**
**    Note: caller is responsible for setting modified flag and
**    updating all views and maps.
*/
BOOL CTileSet::RemoveTile(int iTileIndex)
{
	if (iTileIndex >= 0 && iTileIndex < GetTileCount())
	{
		CString msg;
		msg.Format(IDS_REMOVING_TILE,iTileIndex);
		ShowStatus(msg);

		int iDibIndex = m_tileList[iTileIndex];
		ASSERT(iDibIndex >= 0 && iDibIndex <= m_iMaxTiles);
		m_tileMap[iDibIndex] = TS_EMPTY;   // mark this dib location as unused
		m_tileList.RemoveAt(iTileIndex);
		POSITION pos = m_tileCategories.GetHeadPosition();
		while (pos != NULL)
		{
			m_tileCategories.GetNext(pos)->RemovePermanent(iTileIndex);
		}
		int iCount = GetGroupCount();
		for (int i=0; i < iCount; i++)
		{
			GetGroupAt(i)->RemoveTile(iTileIndex);
		}
		pos = m_mapList.GetHeadPosition();
		while (pos != NULL)
		{
			CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
			ASSERT(pDoc != NULL);
			pDoc->RemoveTile(iTileIndex);
		}
		pos = m_attributeList.GetHeadPosition();
		while (pos != NULL)
		{
			m_attributeList.GetNext(pos)->RemoveAt(iTileIndex);
		}
		if (m_iCurrentType == TSV_TILES && m_iCurrentItem == iTileIndex)
		{
			m_iCurrentItem = -1; // reset the current item
			UpdateAllViews(NULL,TSV_UPDATE_ITEM);
		}
		return TRUE;
	}
	return FALSE;
}

// Assumes that m_searchList has been created and initialized by 
// FindDuplicates and/or modified by RemDupList
BOOL CTileSet::RemoveDuplicates()
{
	int iTileCount = m_searchList.GetSize();
	int iDeleted = 0;
	int i,j,iRep,iNewIndex;
	CTileList repList;

	ASSERT(iTileCount == GetTileCount());

	// build the complete replacement list.
	for (i=0; i < iTileCount; i++)
	{
		iRep = m_searchList[i];
		iNewIndex = i - iDeleted;
		if (iRep >= 0)
		{
			// remove the tile i from the tileset
			int iDibIndex = m_tileList[iNewIndex];
			ASSERT(iDibIndex >= 0 && iDibIndex <= m_iMaxTiles);
			m_tileMap[iDibIndex] = TS_EMPTY;   // mark this dib location as unused
			m_tileList.RemoveAt(iNewIndex);

			// remove tile i's attributes from the tileset
			POSITION pos = m_attributeList.GetHeadPosition();
			while (pos != NULL)
			{
				m_attributeList.GetNext(pos)->RemoveAt(iNewIndex);
			}
			// decrement the index of all subsequent replacement tiles
			for (j=i+1; j < iTileCount; j++)
			{
				iRep = m_searchList[j];
				if (iRep > iNewIndex)
					m_searchList[j] -= 1;
			}
			++iDeleted;
		}
		else
			m_searchList[i] = -iNewIndex - 1;
    }
	if (iDeleted == 0) 
		return FALSE;

	for (i=0; i < iTileCount; i++)
	{
		iRep = m_searchList[i];
		if (iRep < 0)
			m_searchList[i] = -iRep - 1;
	}
	// replace all the duplicate tiles in all the categories
	POSITION pos = m_tileCategories.GetHeadPosition();
	while (pos != NULL)
	{
		m_tileCategories.GetNext(pos)->ReplaceItems(m_searchList);
	}
	// replace all the duplicate tiles in all the groups
	int iCount = GetGroupCount();
	for (i=0; i < iCount; i++)
	{
		GetGroupAt(i)->ReplaceTiles(m_searchList);
	}
	// replace all the duplicate tiles in all the maps
	pos = m_mapList.GetHeadPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
		ASSERT(pDoc != NULL);
		pDoc->ReplaceTiles(m_searchList);
	}
	if (m_iCurrentType == TSV_TILES && m_iCurrentItem >= 0 && m_searchList[m_iCurrentItem] >= 0)
		m_iCurrentItem = m_searchList[m_iCurrentItem];

	return TRUE;
}

BOOL CTileSet::ReadOnly()
{
	DWORD dwAttrib = GetFileAttributes(m_strPathName);
	if ((dwAttrib != ~0) && (dwAttrib & FILE_ATTRIBUTE_READONLY))
		return TRUE;
	return FALSE;
}


void CTileSet::SetCurrentItem(int iItemType, int iItem)
{
	DestroyGroupPreview();
	m_iCurrentType = iItemType;
	m_iCurrentItem = iItem;
	if (GetCurrentGroup())
	{
		if (m_iCurrentItem != -1)
			SetTemporaryGroup(NULL);
		CreateGroupPreview();
		POSITION pos = m_mapList.GetHeadPosition();
		while (pos != NULL)
		{
			CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
			ASSERT(pDoc != NULL);
			pDoc->ClearPreviewRect();
		}
	}
	else 
		SetTemporaryGroup(NULL);
	UpdateAllViews(NULL,TSV_UPDATE_ITEM);
}



/*
** METHOD
**    CTileSet::UpdateMaps
**
** DESCRIPTION
**    Updates all open maps that use this tileSet 
*/
void CTileSet::UpdateMaps(UINT lHint)
{
	POSITION pos = m_mapList.GetHeadPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
		ASSERT(pDoc != NULL);
		pDoc->UpdateAllViews(NULL,lHint);
	}	
}

// called after removing or replacing tiles...
void CTileSet::UpdateModifiedMaps()
{
	POSITION pos = m_mapList.GetHeadPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
		ASSERT(pDoc != NULL);
		if (pDoc->m_bNeedsUpdate)
		{
			pDoc->UpdateAllViews(NULL);
			pDoc->m_bNeedsUpdate = FALSE;
		}
	}
}
/*
** METHOD
**    CTileSet::UpdateMaps
**
** DESCRIPTION
**    Updates all open maps that use the tiles 
**    from iStartTile to iEndTile (inclusive) from the
**    the current map.
**  
**    Call this method, when a tile image is replaced
**    or new tiles are added to the tileset.
*/
void CTileSet::UpdateMaps(int iStartTile, int iEndTile)
{
	POSITION pos = m_mapList.GetHeadPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
		ASSERT(pDoc != NULL);
		pDoc->UpdateTiles(iStartTile, iEndTile);
	}
}

CString CTileSet::GetClipID()
{
	return GetTitle() + GetPathName(); // TBD: use GUID instead?
}


CPoint CTileSet::GetTileLocation(int nTile)
{
	ASSERT(nTile >= 0 && nTile < GetTileCount());
	ASSERT(m_iTilesWide > 0);

	int iDibTile = m_tileList[nTile];
	ASSERT(iDibTile >= 0);

	int row = iDibTile / m_iTilesWide;
	int col = iDibTile % m_iTilesWide;
	int sx = col * m_iTileWidth;
	int sy = row * m_iTileHeight;
	return CPoint(sx,sy);
}

/*
** METHOD
**    CTileSet::DrawWithPalette
** 
** PARAMETERS
**    HDC hdc       -- destination hardware device context
**    int nTile     -- index of tile you wish to draw
**    RECT& dstRect -- destination rectangle where you wish the tile to appear
**
** DESCRIPTION
**    This is a merely a convenience method.
**    Draws the tile into dstRect in the given hdc using the tileset's palette.
**    This method does all the setup work for you so you don't have to call
**    BeginDraw(), etc
**
**    Note: If you are drawing multiple tiles from the same tileset, it is
**    more efficient to:
**          oldPal = SelectPalette (hdc, GetHPalette(), TRUE)
**          if (BeginDraw(hdc))
**          {
**             for (i=....)
**                Draw(hdc, i, dstRect) // draw one or more tiles
**             EndDraw()
**          }
**          ...
*/
BOOL CTileSet::DrawWithPalette( HDC hdc, int nTile, RECT& dstRect)
{
    HPALETTE old = SelectPalette(hdc, GetHPalette(), TRUE);
	BOOL bDrawn = FALSE;
	if (BeginDraw(hdc))
	{
	   bDrawn = Draw(hdc, nTile, dstRect);
	   EndDraw();
	}
	SelectPalette(hdc, old, TRUE);
	return bDrawn;
}

/*
** METHOD
**    CTileSet::Draw
**
** PARAMETERS
**    HDC hdc       -- destination hardware device context
**    int nTile     -- index of tile you wish to draw
**    RECT& dstRect -- destination rectangle where you wish the tile to appear
**
** DESCRIPTION
**    draws the tile into dstRect in the given hdc. Assumes that
**    BeginDraw() has already been called and that the tileset's
**    palette has already been selected into the destination hdc
*/
BOOL CTileSet::Draw( HDC hdc, int nTile, RECT& dstRect)
{
	ASSERT(nTile >= 0 && nTile <= GetTileCount());
	ASSERT(m_dib.GetDIB() != NULL);

	CPoint src = GetTileLocation(nTile);
	return m_dib.GetDIB()->Draw(hdc, 
								dstRect.left, 
								dstRect.top, 
								dstRect.right - dstRect.left, 
								dstRect.bottom - dstRect.top,
								src.x, src.y, m_iTileWidth, m_iTileHeight);

}

BOOL CTileSet::Draw( HDC hdc, int nTile, POINT& pt, BOOL bTransparent, CDIB *pDst)
{
	ASSERT(nTile >= 0 && nTile <= GetTileCount());
	ASSERT(m_dib.GetDIB() != NULL);

	CPoint src = GetTileLocation(nTile);
    CDIB *pDIB = m_dib.GetDIB();
	ASSERT(pDIB != NULL);

	if (pDst)
	{
		// drawing into off-screen dib
		// convert logical coordinates to device/bitmap coordinates
		POINT points[2];
		points[0].x = pt.x; points[0].y = pt.y;
		points[1].x = pt.x + m_iTileWidth; points[1].y = pt.y + m_iTileHeight;
		VERIFY(LPtoDP(hdc,points,2));
		int w = points[1].x - points[0].x;
		int h = points[1].y - points[0].y;

		if (w > 0 && h > 0)
		{
			GdiFlush();
			if (bTransparent)
				pDIB->StretchOver(src.x,src.y,m_iTileWidth,m_iTileHeight,
								  pDst,points[0].x,points[0].y,w,h,m_nTransparentColor);
			else
				pDIB->Stretch(src.x,src.y,m_iTileWidth,m_iTileHeight,
							  pDst,points[0].x,points[0].y,w,h);
		}
	}
#ifdef USE_TRANSPARENCY_TABLES
	else if (bTransparent && m_pRGBColors)
		return pDIB->DrawTransparent(hdc, pt.x, pt.y, src.x, src.y, 
				m_iTileWidth, m_iTileHeight, m_pRGBColors, m_pRGBWhite, m_pRGBBlack,
				m_rgbTransparent);
#else
	else if (bTransparent)
	   pDIB->DrawTrueMask(hdc, pt.x, pt.y, pDIB->GetHDC(), src.x, src.y, m_iTileWidth, m_iTileHeight);
#endif
	else
	   VERIFY(pDIB->Draw(hdc, pt.x, pt.y, src.x, src.y, m_iTileWidth, m_iTileHeight));
	return TRUE;
}

void CTileSet::InitSearch(BOOL bCheckDepth, int iInitValue)
{
	CDIB *pDIB = m_dib.GetDIB();
	ASSERT(pDIB != NULL);

	UserError(IDS_NOT_8BIT_TILESET, bCheckDepth && !pDIB->IsSimpleDib());

	int iTileCount = GetTileCount();
	m_searchList.SetSize(iTileCount);
	for (int i=0; i < iTileCount; i++)
		m_searchList[i] = iInitValue; // no duplicate
}

void CTileSet::EndSearch()
{
	m_searchList.RemoveAll();
}

int CTileSet::FindDuplicate(int iTile, int iTileStart, int& iMinDiff, CDupSearchDlg *pDlg)
{
	int i, iDiff, row, col, iLineInc, iTileCount = GetTileCount();
	BYTE *pSrcLine,*pDstLine, *pSrc,*pDst, *pTarget;


	CDIB *pDIB = m_dib.GetDIB();
	ASSERT(pDIB != NULL);
    ASSERT(m_searchList.GetSize() >= iTileCount);
    ASSERT(pDIB->GetDepth() == 8);

	CPoint pt = GetTileLocation(iTile);
	iLineInc = pDIB->GetLineIncrement();
	pTarget = pDIB->GetBitsAddress(pt.x, pt.y);

	for (i = iTileStart; i < iTileCount; i++)
	{
		if ((i == iTile) || (m_searchList[i] >= 0))
			continue;

		if( m_searchList[i] == m_searchList[iTile] )
		{
			pSrcLine = pTarget;
			pt = GetTileLocation(i);
			pDstLine = pDIB->GetBitsAddress(pt.x, pt.y);

			iDiff = 0;
			for (row = 0; row < m_iTileHeight; row++)
			{
				pSrc = pSrcLine;
				pDst = pDstLine;
				for (col = 0; col < m_iTileWidth; col++)
				{
					if (*pSrc++ != *pDst++)
						++iDiff;
					if( iDiff > m_iTolerance )
						goto nomatch;
				}
				pSrcLine += iLineInc;
				pDstLine += iLineInc;

				if (pDlg && pDlg->CheckCancelButton())
					return -1;
			}
			if (pDlg && iDiff && iDiff < iMinDiff)
			{
				iMinDiff = iDiff;
				pDlg->UpdateMinDiff(iDiff);
			}
nomatch:
			if (iDiff <= m_iTolerance) 
				return i;
		}
	}
	return -1;
}


int CTileSet::FindDuplicates(CWnd *pWnd)
{
	CDupSearchDlg dlg, *pDlg = NULL;
	int iTileCount = GetTileCount();
	int iCount = 0;
    int i, j, iMinDiff = m_iTileWidth * m_iTileHeight;

	if (iTileCount <= 0)
		return 0;

	ASSERT(m_iTolerance >= 0);
	ASSERT(m_searchList.GetSize() >=  iTileCount);

	if (pWnd)
	{
		if (!dlg.Create(pWnd))
			AfxThrowMemoryException(); // TBD
		dlg.SetRange(0, iTileCount);
		dlg.SetStep(1);
		dlg.SetStatus(0, iMinDiff);
		pDlg = &dlg;
	}


	CDIB *pDIB = m_dib.GetDIB();
	ASSERT(pDIB != NULL);
    ASSERT(pDIB->GetDepth() == 8);
	
	int	iLineInc = pDIB->GetLineIncrement();

	// compute checksum of each tile & store in m_searchList as negative value
	for( i = 0; i < iTileCount; i++ )
	{
		int checksum = 0;
		int shift = 0;
		int row, col;
		BYTE *pSrcLine, *pSrc;
		CPoint pt;

        pt = GetTileLocation(i);
		pSrcLine = pDIB->GetBitsAddress(pt.x, pt.y);

		if( m_iTolerance == 0)
		{
			for (row = 0; row < m_iTileHeight; row++)
			{
				pSrc = pSrcLine;
				for (col = 0; col < m_iTileWidth; col++)
				{
					checksum += ((*pSrc) << shift);
					pSrc++;
					shift++;
					if( shift >= 8 )
						shift = 0;
				}
				pSrcLine += iLineInc;

				if (pDlg && pDlg->CheckCancelButton())
					return 0;
			}
		}
		if( checksum == 0 )
			m_searchList[i] = -1;
		else if( checksum < 0 )
			m_searchList[i] = checksum;
		else if( checksum > 0 )
			m_searchList[i] = -checksum;
		pDlg->UpdateMinDiff(i);
	}

	for (i=0; i < iTileCount; i++)
	{
		if (m_searchList[i] < 0)
		{
			j = i+1; // this is where we want to start the search
            while (j < iTileCount)
			{
				if (pWnd && dlg.CheckCancelButton())
					break;
				j = FindDuplicate(i,j,iMinDiff,pDlg);
				if (j < 0)
					break;
				m_searchList[j] = i;
				++j; // continue with next tile
				++iCount;
				if (pWnd)
					dlg.UpdateFound(iCount);
			}
		}
		if (pWnd)
		{
			dlg.StepIt();
			if (dlg.CheckCancelButton())
				break;
		}
	}

	for( i = 0; i < iTileCount; i++ )
	{
		if( m_searchList[i] < -1 )
			m_searchList[i] = -1;
	}

	return iCount;
}

/* METHOD
**    CTileSet::DoFindDuplicates
** 
** PARAMETERS
**    bInteractive -- TRUE when initialiated by the user via menu
**       or keyboard action (as opposed to creating a new tileSet)
**    pWnd -- where the action was invoked.
**                       
** DESCRIPTION
**    Searches for all duplicate tiles and puts up a dialog allowing
**    the user to view/choose the duplicates they want to remove.
**
**    If bInteractive is true, this function will give the user
**    the opportunity to modify the tileSet's tolerance value before
**    beginning the search.  Otherwise we just use the current 
**    tolerance value.
**
**    If bInteractive is true and NO duplicates are found, 
**    a message will be displayed to the user.
*/
void CTileSet::DoFindDuplicates(BOOL bInteractive, CWnd *pWnd)
{
	CFindDupDlg fdlg(m_iTolerance, m_iTileWidth * m_iTileHeight);
	CRemDupDlg rdlg(this);
    BOOL bModified = FALSE;

	BeginWaitCursor();
	TRY
	{
		InitSearch(TRUE,-1);
		if (!bInteractive || (fdlg.DoModal() == IDOK))
		{
			m_iTolerance = fdlg.m_iTolerance;
			RestoreWaitCursor();
			if (FindDuplicates(pWnd) > 0)
			{
				if (rdlg.DoModal() != IDCANCEL)
				{
					RestoreWaitCursor();
					bModified = RemoveDuplicates();
				}
			}
			else if (bInteractive)
				AfxMessageBox(IDS_NO_DUPLICATES);
		}
		if (bModified)
		{
			// update dependent maps.
			UpdateModifiedMaps();
			// update size
//			Resize(GetTileCount()+1);
//			Resize(GetTileCount()-1);
			Resize(GetTileCount());
			// update all views of this tileset
			SetModifiedFlag();
			UpdateAllViews(NULL,TSV_UPDATE_LIST|TSV_UPDATE_ITEM); 
		}
	}
	END_TRY
	EndSearch();
	EndWaitCursor();
}

//////////////////////////////////////////////////////////////////////////////////
// The following commands have been centeralized here so they can be used by 
// both CMapEditorView and CTileSetView
//////////////////////////////////////////////////////////////////////////////////

// TBD: rethink this or rename this to: AddTileFrom
int CTileSet::CopyTile(CTileSet *pSrc, int nIndex)
{
	int iNewTile = GetTileCount(); 
	int iMapIndex = -1;             
	BOOL bCopied = FALSE;

	ASSERT(pSrc != NULL);
	ASSERT(nIndex >= 0 && nIndex < pSrc->GetTileCount());

	TRY
	{
		iMapIndex = FindEmptyTile();
		if (iMapIndex < 0)
		{
			Resize(GetTileCount() + 10);	
			iMapIndex = FindEmptyTile();
			ASSERT(iMapIndex >= 0);
		}

		CDIB *pDIB = m_dib.GetDIB();
		ASSERT(pDIB != NULL);


		POSITION pos = pSrc->m_attributeList.GetHeadPosition();
		while (pos != NULL)
		{
			CTileAttribute *pSrcAttr = pSrc->m_attributeList.GetNext(pos);
			// TBD: if (!pSrcAttr->IsTransferable()) continue;
			CTileAttribute *pAttribute = AddAttribute(pSrcAttr);
			if (pAttribute) 
				pAttribute->SetValue(iNewTile,pSrcAttr->GetValue(nIndex));
		}

		int iTileIndex = m_tileList.Add(iMapIndex);
		ASSERT(iNewTile == iTileIndex);

		m_tileMap[iMapIndex] = iTileIndex;
		CPoint src = pSrc->GetTileLocation(nIndex);
		CPoint dst = GetTileLocation(iTileIndex);

		HDC hdc = BeginDraw();
		if (hdc != NULL)
		{
			if (pSrc == this)
			{
				bCopied = pDIB->Draw(hdc, dst.x, dst.y, src.x, src.y, m_iTileWidth, m_iTileHeight);
			}
			else if (pSrc->BeginDraw())
			{
				bCopied = pSrc->m_dib.GetDIB()->Draw(hdc, dst.x, dst.y, m_iTileWidth, m_iTileHeight,
				     src.x, src.y, pSrc->m_iTileWidth, pSrc->m_iTileHeight);
				pSrc->EndDraw();
			}
			EndDraw();                     
		}
	}
	END_TRY

	if (bCopied)
		return iNewTile;

	// tile may have been partially added...clean up
	int iNewSize = iNewTile+1;
	if (GetTileCount() == iNewSize)
		m_tileList.RemoveAt(iNewTile);

	if (iMapIndex >= 0)
		m_tileMap[iMapIndex] = TS_EMPTY;

	POSITION pos = m_attributeList.GetHeadPosition();
	while (pos != NULL)
	{
		CTileAttribute *pAttribute = m_attributeList.GetNext(pos);
		ASSERT(pAttribute);
		if (pAttribute->GetSize() >= iNewSize)
			pAttribute->RemoveAt(iNewTile);
	}

	return -1;
}

/*
** METHOD
**    CTileSet::FindEmptyTile
**
** DESCRIPTION
**    searches for and returns the first available
**    empty tile location in the current DIB.
**
** RETURNS
**    index of empty tile location or -1 if no empty tiles.
*/
int CTileSet::FindEmptyTile()
{
#if (TS_EMPTY >= 0)
#error CTileSet::FindEmptyTile assumes TS_EMPTY is negative.
#endif

	if (GetTileCount() < m_iMaxTiles)
	{
		for (int i=0; i < m_iMaxTiles; i++)
		{
			if (m_tileMap[i] < 0)
				return i;
		}
	}
	return -1;
}


/* METHOD
**    CTileSet::ComparePalettesAndAsk
**
** PARAMETERS
**    CPalette *pSrc -- pointer to source palette for another tileset (may be null)
**
** DESCRIPTION
**    If pSrc is non-null and the this tileset also has a palette,
**    compares the two palettes.  If the common entries are not identical
**    asks the user if they want to copy the source palette to this tileset.
**    If the user says yes, copies the source palette to this tileset.
**
** RETURNS
**    IDYES     - if the source palette was copied
**    IDNO      - if the source palette was not copied but the user wishes to proceed
**    IDCANCEL  - if the source palette was not copied and the user wishes to abort
**                the operation in progress.
*/
int CTileSet::ComparePalettesAndAsk(CPalette *pSrc)
{
	CPalette *pDst = GetPalette();
	int result = IDNO;
	if (pDst && pSrc)
	{
		UINT nEntries = min(pSrc->GetEntryCount(),pDst->GetEntryCount());
		UINT i, nBytes = nEntries * sizeof(PALETTEENTRY);
		PALETTEENTRY *ps, *pSrcData = (PALETTEENTRY *)malloc(nBytes);
		PALETTEENTRY *pd, *pDstData = (PALETTEENTRY *)malloc(nBytes);
		if (pSrcData && pDstData)
		{
			pSrc->GetPaletteEntries(0,nEntries,pSrcData);
			pDst->GetPaletteEntries(0,nEntries,pDstData);
			ps = pSrcData; 
			pd = pDstData;
			for (i=0; i < nEntries; i++)
			{
				if (ps->peRed != pd->peRed || ps->peBlue != pd->peBlue || ps->peGreen != pd->peGreen)
				{
					result = AfxMessageBox(IDS_ASK_COPY_PALETTE, MB_YESNOCANCEL|MB_ICONQUESTION);
					if (result == IDOK)
					{
						pDst->SetPaletteEntries(0,nEntries,pSrcData);
						m_dib.GetDIB()->SetPalette(0,nEntries,pSrcData); 
						// TBD: allocate a new dib palette and change the palette pointer
						// in case the current palette is selected into some device 
						// context.
						UpdateTransparency();
						UpdateAllViews(NULL,TSV_UPDATE_PALETTE);
					}
					break;
				}
				++ps;
				++pd;
			}
		}
		if (pSrcData) free(pSrcData);
		if (pDstData) free(pDstData);
	}
	return result;
}

BOOL CTileSet::ReLoadBitmap(LPCTSTR lpszBitmapPath, COLORREF rgbTransparent)
{
	CWaitCursor wait;
	CDibDoc newDib;

	if (!newDib.OnOpenDocument(lpszBitmapPath)) 
		return FALSE;

	ASSERT(m_iTileWidth != 0 && m_iTileHeight != 0);
	CSize size = newDib.GetSize();
	int nWide = size.cx / m_iTileWidth;
	int nHigh = size.cy / m_iTileHeight;
	int i;

	if (nWide < 1 || nHigh < 1)
	{
		AfxMessageBox(IDS_DIB_TOO_SMALL, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	if (size.cx % m_iTileWidth || size.cy % m_iTileHeight)
	{
		if (AfxMessageBox(IDS_BAD_DIB_DIMENSIONS, MB_YESNO | MB_ICONQUESTION) != IDYES)
		   return FALSE;
	}
	int iOldTileCount = GetTileCount();
	int iNewTileCount = nWide * nHigh;
	if (iNewTileCount < iOldTileCount)
	{
        if (AfxMessageBox(IDS_BITMAP_TOO_SMALL, MB_YESNO | MB_ICONQUESTION) != IDYES)
		   return FALSE;
		
		for (int i=iOldTileCount-1; i >= iNewTileCount; i--)
		{
			VERIFY(RemoveTile(i)); // handles attributes, tileList and tileMap
		}
	}
    else if (iNewTileCount > iOldTileCount)
	{
		TRY
		{
			// resize all the arrays to handle greater number of tiles
			m_tileList.SetSize(iNewTileCount);
			m_tileMap.SetSize(iNewTileCount);
			for (i=iOldTileCount; i < iNewTileCount; i++)
			{
				m_tileList[i] = i;
				m_tileMap[i] = i;
			}
			POSITION pos = GetFirstAttribute();
			while (pos != NULL)
			{
				CTileAttribute *pAttr = GetNextAttribute(pos);
				ASSERT(pAttr != NULL);
				pAttr->SetSize(iNewTileCount);
			}
		}
		CATCH_ALL(e)
		{
			TRACE("Error occurred while trying to resize tileset arrays\n");
			TRY
			{
				// restore the old sizes, presumably SetSize is 
				// smart enough to shrink without failing.
				m_tileList.SetSize(iOldTileCount); 
				m_tileMap.SetSize(m_iMaxTiles);
				POSITION pos = GetFirstAttribute();
				while (pos != NULL)
				{
					CTileAttribute *pAttr = GetNextAttribute(pos);
					ASSERT(pAttr != NULL);
					pAttr->SetSize(iOldTileCount);
				}
				newDib.DeleteContents();
			}
			END_TRY
			THROW_LAST();
		}
		END_CATCH_ALL
	}
 
	// at this point we should be pretty much home free
	m_rgbTransparent = rgbTransparent;
	int iMinCount = min(iNewTileCount,iOldTileCount);
    for (i=0; i < iMinCount; i++)
	{
		m_tileList[i] = i; // assume all tiles are consecutive.
		m_tileMap[i] = i;
	}
	m_dib.SetDIB(newDib.DetachDIB());
	m_dib.SetPal(newDib.DetachPal());
	m_iMaxTiles = iNewTileCount;
	m_iTilesWide = nWide;
	UpdateTransparency();
	return TRUE;
}

void CTileSet::Resize(int nTiles)
{
    if (nTiles <= 0) nTiles = 1;
	int iWidth, dibWidth = m_dib.GetSize().cx;
	if (m_bUseBitmapWidth)
		iWidth = max(m_iTileWidth, (int)m_nBitmapWidth);
    else
		iWidth = max(m_iTileWidth, dibWidth);

	ASSERT(nTiles >= GetTileCount());
	ASSERT(iWidth >= m_iTileWidth);
    int iTilesWide = iWidth/m_iTileWidth; 
	int iTilesHigh = (nTiles + iTilesWide - 1)/iTilesWide;

    CDibDoc newdib;
	RGBQUAD *pRGB = m_dib.GetDIB()->GetClrTabAddress();

	if (!newdib.OnNewDocument(iWidth, iTilesHigh * m_iTileHeight, GetTileDepth(), pRGB))
		AfxThrowMemoryException();

	CDIB *pSrcDIB = m_dib.GetDIB();
	CDIB *pDstDIB = newdib.GetDIB();
	HDC srcHDC = NULL, dstHDC = NULL;
	CPoint src,dst;

	ASSERT(pDstDIB != NULL);
	ASSERT(pSrcDIB != NULL);

	CSize newsize = newdib.GetSize();
	iTilesWide = newsize.cx / m_iTileWidth; // may be larger due to alignment restrictions
	iTilesHigh = newsize.cy / m_iTileHeight;
	int iMaxTiles = iTilesWide * iTilesHigh;
	int lastx = iTilesWide * m_iTileWidth;
    
	TRY
	{
		int iCount = GetTileCount();
		dst.x = 0;
		dst.y = 0;

		srcHDC = pSrcDIB->CreateHDC(NULL);
        if (srcHDC == NULL) 
			AfxThrowMemoryException();

		dstHDC = pDstDIB->CreateHDC(srcHDC);
		if (dstHDC == NULL)
			AfxThrowMemoryException();
        
		for (int i=0; i < iCount; i++)
		{
		    src = GetTileLocation(i); // use this because tile can be anywhere in tileset
			pSrcDIB->Draw(dstHDC, dst.x, dst.y, src.x, src.y, m_iTileWidth, m_iTileHeight);
			dst.x += m_iTileWidth;
			if (dst.x >= lastx)
			{
				dst.x = 0;
				dst.y += m_iTileHeight;
			}
		}
		// grow the attribute arrays; it won't hurt if only some of them are grown
		POSITION pos = m_attributeList.GetHeadPosition();
		while (pos != NULL)
		{
			m_attributeList.GetNext(pos)->SetSize(iCount);
		}
        // grow the tileList and tileMaps
		// TBD: it shouldn't be fatal if we hit an error at his point.
		m_tileList.SetSize(iCount);
		m_tileMap.SetSize(iMaxTiles);

		// At this point we should be home free...
		for (i=0; i < iCount; i++)
		{
			m_tileMap.SetAt(i,i);
			m_tileList.SetAt(i,i);
		}
		for (i=iCount; i < iMaxTiles; i++)
			m_tileMap.SetAt(i,TS_EMPTY);

		pSrcDIB->DeleteHDC(); srcHDC = NULL;
		pDstDIB->DeleteHDC(); dstHDC = NULL;
		m_dib.SetDIB(newdib.DetachDIB());
		m_dib.SetPal(newdib.DetachPal()); 
		m_iTilesWide = iTilesWide;
		m_iMaxTiles = iMaxTiles;
#ifndef USE_TRANSPARENCY_TABLES
		UpdateTransparency();  // bitmap has been reorganized we need to rebuild mask
#endif
	}
	CATCH_ALL(E)
	{
		TRACE0("PANIC! An error occurred while attempting to resize tileset\n");
		// CDIB's destructor will take care of deallocating the temporary dib
	}
	END_CATCH_ALL
	if (srcHDC) pSrcDIB->DeleteHDC(); 
	if (dstHDC) pDstDIB->DeleteHDC();
	SetModifiedFlag();
	UpdateAllViews(NULL, TSV_UPDATE_PALETTE); // re-select palette 
}

BOOL CTileSet::PreSaveDocument()
{
	TRY
	{
		if (g_bCompactOnSave)
			Resize(GetTileCount());
	}
	CATCH_ALL(e)
	{
		if (AfxMessageBox(IDS_CANT_COMPACT_ON_SAVE, MB_YESNO|MB_ICONQUESTION) == IDNO)
		   return FALSE;
	}
	END_CATCH_ALL
	return TRUE;
}

BOOL CTileSet::OnSaveDocument(LPCTSTR lpszPathName)
{
    if (!PreSaveDocument())
		return FALSE;
	return CDocument::OnSaveDocument(lpszPathName);        // success
}

void CTileSet::OnTilesetCompact() 
{
	TRY
	{
		Resize(GetTileCount());
	}
	CATCH_ALL(e)
	{
		AfxMessageBox(IDS_CANT_COMPACT_TILESET, MB_OK|MB_ICONINFORMATION);
	}
	END_CATCH_ALL
	
}

void CTileSet::ExportArmyMen(LPCSTR lpszPathName)
{
	CFileException fe;

    // check for basic army men violations before we write out file.
	CSize tileSize = GetTileSize();
	UserError(IDS_AMV_TILESIZE, tileSize.cx != 16 || tileSize.cy != 16);
	UserError(IDS_AMV_TILEDEPTH, GetTileDepth() != 8);
//    UserError(IDS_AMV_TILESETBM, m_dib.GetDIB()->GetWidth() != 256);

	CIFFFile iff;
	if (! iff.Open(lpszPathName, CIFFFile::modeCreate |
		           CIFFFile::modeReadWrite | CIFFFile::shareExclusive, &fe))
	{
		ReportSaveLoadException(lpszPathName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		return;
	}


	TRY
	{
		CWaitCursor wait;
		ULONG form = iff.PushChunk('F','O','R','M');
		iff.WriteLong(iff.MakeID('T','I','L','E'));

		ULONG vers = iff.PushChunk('V','E','R','S', 8L);
		iff.WriteLong(1);  // major
		iff.WriteLong(0);  // minor
        iff.PopChunk(vers);

		ULONG thdr = iff.PushChunk('T','H','D','R', 20);
		iff.WriteLong((long)m_iTileWidth);
		iff.WriteLong((long)m_iTileHeight);
		iff.WriteLong((long)m_iMaxTiles);
		iff.WriteLong((long)m_iTilesWide);
		iff.WriteLong((long)m_rgbTransparent);
        iff.PopChunk(thdr);


		ULONG dib = iff.PushChunk('D','I','B',' ');
		if (!m_dib.GetDIB()->Save(&iff))
			AfxThrowUserException(); // TBD
        iff.PopChunk(dib);

		iff.PopChunk(form);
	}
	CATCH_ALL(e)
	{
		iff.Abort();
		TRY
		{
			ReportSaveLoadException(lpszPathName, e,
				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		}
		END_TRY
	}
	END_CATCH_ALL
}



void CTileSet::OnFileExport() 
{
    CString lpszName;
	CString lpszFilter;

	int iPos = m_strTitle.ReverseFind('.');
	int iCount = (iPos > 0) ? iPos : m_strTitle.GetLength();
	lpszName = m_strTitle.Left(iCount) + ".";  
	lpszName += ARMYMEN_TILE_EXT; 
	lpszFilter.LoadString(IDS_TILESET_EXPORT_FILTER);
	CFileDialog dlg(NULL, NULL, lpszName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_LONGNAMES, lpszFilter);
	if (dlg.DoModal() == IDOK)
	{
		if (!PreSaveDocument())
			return; 
		CString pathName = dlg.GetPathName();
		CString ext = dlg.GetFileExt();

		if (ext.CompareNoCase(ARMYMEN_TILE_EXT) == 0)
			ExportArmyMen(pathName);
		else
			m_dib.OnSaveDocument(pathName);
	}
}

void CTileSet::AddMap(CMapEditorDoc *pMap)
{
	m_mapList.AddHead(pMap);
}

void CTileSet::RemoveMap(CMapEditorDoc *pMap)
{ 
	POSITION pos = m_mapList.Find(pMap);
	if (pos != NULL)
	{
		m_mapList.RemoveAt(pos); 
		OnChangedViewList();
	}
}

int CTileSet::AddGroup(LPCTSTR lpszTitle, int iWidth, int iHeight, BOOL bInteractive)
{
	CNewGroupDlg dlg(this);
	if ((lpszTitle == NULL || strlen(lpszTitle)==0) && bInteractive)
	{
		// if the group doesn't have a name, and the we're interactive
		// then ask the user for 
		int iCount = GetGroupCount();
		int iIndex = 1 + iCount;
		dlg.m_pszTitle.Format(IDS_GROUP_FORMAT,iIndex);
		 if (dlg.DoModal() == IDOK)
			lpszTitle = dlg.m_pszTitle;
		else
			return NULL;
	}
#if 0
	// check to see if the group name already exists...
	int iGroup = GetGroupIndex(lpszTitle);
	if (iGroup >= 0)
	{
		if (bInteractive)
		{
			CString msg;
			AfxFormatString1(msg, IDS_ASK_OVERWRITE_GROUP, lpszTitle);
			if (AfxMessageBox(msg, MB_YESNO|MB_ICONQUESTION) == IDYES)
				GetGroupAt(iGroup)->SetSize(iWidth,iHeight);
			else
				iGroup = -1;
		}
		return iGroup;
	}
    else
#endif
	return m_groups.Add(CTileGroup(lpszTitle, iWidth, iHeight));
}

CTileGroup *CTileSet::GetGroup(LPCTSTR lpszTitle)
{
	CTileGroup *pGroup;
	for (int i=0; i < GetGroupCount(); i++)
	{
		pGroup = &m_groups[i];
		if (pGroup->GetTitle().CompareNoCase(lpszTitle)==0)
		   return pGroup;
	}
	return NULL;
}

int CTileSet::GetGroupIndex(LPCTSTR lpszTitle)
{
	CTileGroup *pGroup;
	for (int i=0; i < GetGroupCount(); i++)
	{
		pGroup = &m_groups[i];
		if (pGroup->GetTitle().CompareNoCase(lpszTitle)==0)
		   return i;
	}
	return -1;
}


BOOL CTileSet::RemoveGroup(int iIndex) 
{
	if ((iIndex >= 0) && iIndex < GetGroupCount())
	{
		// remove the group from all the group categories
		POSITION pos = m_groupCategories.GetHeadPosition();
		while (pos != NULL)
		{
			m_groupCategories.GetNext(pos)->RemovePermanent(iIndex);
		}
		m_groups.RemoveAt(iIndex); 
		if (m_iCurrentType == TSV_GROUPS && m_iCurrentItem == iIndex)
			SetCurrentItem(TSV_GROUPS, -1); // reset the current item
		return TRUE;
	}
	return FALSE;
}


void CTileSet::DrawGroup(HDC hdc, CTileGroup *pGroup, CPoint pt, CSize tileSize)
{
   ASSERT_VALID(pGroup);
   CSize size = pGroup->GetSize();

   if (size.cx && size.cy)
   {
	   HPALETTE oldPal = SelectPalette (hdc, GetHPalette(), TRUE);
	   CPoint tp = pt;
	   if (BeginDraw(hdc))
	   {
		   for (int iRow = 0; iRow < size.cy; iRow++)
		   {
			   tp.x = pt.x;
			   for (int iCol = 0; iCol < size.cx; iCol++)
			   {
				   int iTile = pGroup->GetTile(iRow,iCol);
				   if (iTile >= 0)
					  Draw(hdc,iTile,CRect(tp,tileSize));
				   tp.x += tileSize.cx;
			   }
			   tp.y += tileSize.cy;
		   }
		   EndDraw();
	   }
	   SelectPalette(hdc,oldPal,TRUE); 
   }
}


void CTileSet::DrawGroup(HDC hdc, CTileGroup *pGroup, CPoint pt, BOOL bTransparent, CDIB *pDIB)
{
   ASSERT_VALID(pGroup);
   CSize size = pGroup->GetSize();

   if (size.cx && size.cy)
   {
	   HPALETTE oldPal = SelectPalette (hdc, GetHPalette(), TRUE);
	   CPoint tp = pt;
	   if (BeginDraw(hdc))
	   {
		   for (int iRow = 0; iRow < size.cy; iRow++)
		   {
			   tp.x = pt.x;
			   for (int iCol = 0; iCol < size.cx; iCol++)
			   {
				   int iTile = pGroup->GetTile(iRow,iCol);
				   if (iTile >= 0)
					  Draw(hdc,iTile,tp,bTransparent,pDIB);
				   tp.x += m_iTileWidth;
			   }
			   tp.y += m_iTileHeight;
		   }
		   EndDraw();
	   }
	   SelectPalette(hdc,oldPal,TRUE); 
   }
}

void CTileSet::DrawGroup(HDC hdc, CTileGroup *pGroup, CRect rect)
{
	ASSERT_VALID(pGroup);
	CSize size = pGroup->GetSize();
	size.cx *= m_iTileWidth;
	size.cy *= m_iTileHeight;
	ASSERT(size.cx && size.cy);
	HDC hTmpDC = CreateCompatibleDC(hdc);
	if (hTmpDC)
	{
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, size.cx, size.cy);
		if (hBitmap)
		{
			HPALETTE hOldPal= SelectPalette (hTmpDC, GetHPalette(), TRUE);
			HPALETTE hOldPal2 = SelectPalette (hdc, GetHPalette(), TRUE);
			HBITMAP hOldBitmap = SelectHBitmap(hTmpDC, hBitmap);

			BitBlt(hTmpDC,0,0,size.cx,size.cy,hTmpDC,0,0,WHITENESS);
			DrawGroup(hTmpDC,pGroup,CPoint(0,0),FALSE,NULL);

			StretchBlt(hdc, rect.left, rect.top, rect.Width(), rect.Height(), 
					   hTmpDC, 0, 0, size.cx, size.cy, SRCCOPY);
			
			SelectHBitmap(hTmpDC, hOldBitmap);
			SelectPalette(hTmpDC, hOldPal, TRUE);

			SelectPalette(hdc, hOldPal2, TRUE);
			DeleteObject(hBitmap);
		}
	}
	DeleteDC(hTmpDC);
}

CSize CTileSet::GetGroupExtent(CTileGroup *pGroup)
{
	ASSERT(pGroup != NULL);
	CSize size = pGroup->GetSize();
	size.cx *= m_iTileWidth;
	size.cy *= m_iTileHeight;
	return size;
}

void CTileSet::OnUpdateFileRevert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetPathName().IsEmpty());
}

void CTileSet::OnFileRevert() 
{
	if (IsModified())
	{
		CString msg;
		AfxFormatString1(msg, IDS_REVERT_MAY_LOSE_DATA, GetPathName());
		if (AfxMessageBox(msg, MB_ICONQUESTION|MB_YESNO) != IDYES)
			return;
	}

	g_bOldDataFormat = m_bOldDataFormat; // TBD: this is temporary!
    if (OnOpenDocument(GetPathName()))
	{
		UpdateAllViews(NULL, TSV_UPDATE_PALETTE);
	}
	else
	{
		// man we're in real trouble now! I don't think maps know
		// how to deal with empty tilesets.
		while (!m_mapList.IsEmpty())
		{
			CMapEditorDoc *pDoc = m_mapList.RemoveHead();
			ASSERT(pDoc != NULL);
			pDoc->OnCloseDocument();
		}
		OnCloseDocument(); 	
	}
}



// CreateGroupPreview:
//   creates a bitmap used to preview the current group as the user moves the
//   mouse around the map area.  It is faster to render the bitmap than it is
//   to draw the individual tiles each time.
//
//   TBD: this method doesn't work if drawing to an offscreen dib and
//   I am not quite sure why; probably because "BLACKNESS" and "WHITENESS"  
//   are not necessary the same for the dib as they are for the system palette.
void CTileSet::CreateGroupPreview()
{
	CTileGroup *pGroup = GetCurrentGroup();
	ASSERT(pGroup != NULL);

	CSize size = GetGroupExtent(pGroup);
	ASSERT(size.cx >= 0 && size.cy >= 0);

	DestroyGroupPreview();
	HDC hDisplayDC = CreateDC("DISPLAY",NULL,NULL,NULL);
	if (hDisplayDC)
	{
		HDC hTmpDC = CreateCompatibleDC(hDisplayDC);
		if (hTmpDC)
		{
			m_hGroupBitmap = CreateCompatibleBitmap(hDisplayDC, size.cx, size.cy);
			if (m_hGroupBitmap)
			{
				CSize tileSize = GetTileSize();
				HPALETTE hOldPal= SelectPalette (hTmpDC, GetHPalette(), TRUE);
				HBITMAP hOldBitmap = SelectHBitmap(hTmpDC, m_hGroupBitmap);
				BitBlt(hTmpDC,0,0,size.cx,size.cy,hTmpDC,0,0,BLACKNESS);
				DrawGroup(hTmpDC,pGroup,CPoint(0,0),FALSE,NULL);
				
				SelectHBitmap(hTmpDC, hOldBitmap);
				SelectPalette(hTmpDC, hOldPal, TRUE);
#ifdef U_BLIT_TRANSPARENT
				m_hGroupMask = CreateBitmap(size.cx, size.cy, 1, 1, NULL);
                
				if (m_hGroupMask)
				{
					HBITMAP hOldBitmap = SelectHBitmap(hTmpDC, m_hGroupMask);
					HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
					BitBlt(hTmpDC,0,0,size.cx,size.cy,hTmpDC,0,0,BLACKNESS);
					
					CPoint tp(0,0);
					size = pGroup->GetSize();
					for (int iRow = 0; iRow < size.cy; iRow++)
					{
					   tp.x = 0;
					   for (int iCol = 0; iCol < size.cx; iCol++)
					   {
						   int iTile = pGroup->GetTile(iRow,iCol);
						   if (iTile < 0)
							  FillRect(hTmpDC, CRect(tp,tileSize), whiteBrush);
						   tp.x += tileSize.cx;
					   }
					   tp.y += tileSize.cy;
					}
					SelectHBitmap(hTmpDC, hOldBitmap);
				}
				else
					TRACE0("Can't create group preview mask\n");
#endif
			}
			else
				TRACE0("Can't create group preview bitmap\n");
		DeleteDC(hTmpDC);
		}
		else
			TRACE0("Can't create dc for group preview\n");
		DeleteDC(hDisplayDC);
	}
	else
		TRACE0("Can't get display dc for group preview\n");
}

void CTileSet::DestroyGroupPreview()
{
	if (m_hGroupBitmap) 
	{
		DeleteObject(m_hGroupBitmap);
		m_hGroupBitmap = NULL;
	}
	if (m_hGroupMask)
	{
		DeleteObject(m_hGroupMask);
		m_hGroupMask = NULL;
	}
}

void CTileSet::PreviewCurrentGroup(HDC hdc, CPoint pt, BOOL bTransparent, CDIB *pDIB)
{
	CTileGroup *pGroup = GetCurrentGroup();
	if (pGroup == NULL)
		return;

	CSize size = GetGroupExtent(pGroup);
	ASSERT(size.cx >= 0 && size.cy >= 0);
    BOOL bDrawn = FALSE;
	if (pDIB)
	{
		DrawGroup(hdc,pGroup,pt,bTransparent,pDIB);
		bDrawn = TRUE;
	}
	else if (m_hGroupBitmap)
	{
		HDC srcDC = CreateCompatibleDC(hdc);
		if (srcDC)
		{
			HBITMAP hOldBitmap = SelectHBitmap(srcDC, m_hGroupBitmap);
			HPALETTE hOldPalette = SelectPalette(srcDC, GetHPalette(), TRUE);
			HPALETTE hOldPalette2 = SelectPalette(hdc, GetHPalette(), TRUE);

#ifdef U_BLIT_TRANSPARENT
			// TBD: create a dib with a BlackSourceMask and DrawBlackMask instead.
			// Note: large areas blitted with transparency will flicker way too
			// much so it is best to double-buffer; draw the group off-screen 
			// and blit the changed area on screen.
			if (m_hGroupMask)
			{
				// This method assumes mask is 1 where pixels are transparent
				// *AND* bitmap is 0 where pixels are transparent.
				COLORREF oldbk = SetBkColor(hdc, RGB(255, 255, 255));    // 1s --> 0xFFFFFF
				COLORREF oldtx = SetTextColor(hdc, RGB(0, 0, 0));        // 0s --> 0x000000

				HBITMAP hSrcBM = SelectHBitmap(srcDC, m_hGroupMask);
				bDrawn = BitBlt(hdc,pt.x,pt.y,size.cx,size.cy,srcDC,0,0,SRCAND);

			    if (bDrawn)
				{
					SelectHBitmap(srcDC, m_hGroupBitmap);
					bDrawn = BitBlt(hdc,pt.x,pt.y,size.cx,size.cy,srcDC,0,0,SRCPAINT);
				}
				SelectHBitmap(srcDC, hSrcBM);
				SetBkColor(hdc, oldbk);
				SetTextColor(hdc,oldtx);
			}
#endif
			if (!bDrawn) // draw it ignoring the transparency
				bDrawn = BitBlt(hdc,pt.x,pt.y,size.cx,size.cy,srcDC,0,0,SRCCOPY);
			if (!bDrawn)
				TRACE("Error drawing preview\n");
			SelectHBitmap(srcDC,hOldBitmap);
			SelectPalette(srcDC,hOldPalette,TRUE);
			SelectPalette(hdc,hOldPalette2,TRUE);
			DeleteDC(srcDC);
		}
		else
			TRACE0("Can't create preview srcDC\n");
	}
    if (g_bOutlinePreview || !bDrawn)
	{
		HPEN oldPen = (HPEN)SelectObject(hdc, GetStockObject(WHITE_PEN));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, pt.x, pt.y, pt.x + size.cx, pt.y + size.cy);
		SelectObject(hdc,oldPen);
		SelectObject(hdc,oldBrush);
	}
}

BOOL CTileSet::OnOpenDocument(LPCTSTR lpszPathName) 
{
	BOOL bOpened = CDocument::OnOpenDocument(lpszPathName);

	m_sInitData = lpszPathName;
	if (!bOpened && !g_bOldDataFormat)
	{
		g_bOldDataFormat = TRUE;
		bOpened = OnOpenDocument(lpszPathName);
    }    
	g_bOldDataFormat = FALSE; // reset for future opens
	return bOpened;
}


CTileGroup * CTileSet::SetTemporaryGroup(CTileGroup *pGroup)
{
	delete m_pTemporaryGroup;
	if (pGroup != NULL)
	{
		m_pTemporaryGroup = new CTileGroup;
		ASSERT_NEW(m_pTemporaryGroup);
	    m_pTemporaryGroup->Copy(pGroup);
	}
	else
		m_pTemporaryGroup = NULL;
	return m_pTemporaryGroup;
}


CTileGroup * CTileSet::GetCurrentGroup()
{
	if (m_iCurrentType == TSV_GROUPS)
	{
		if (m_iCurrentItem == -1)
			return m_pTemporaryGroup;
		else if (m_iCurrentItem >= 0 && m_iCurrentItem < GetGroupCount())
			return GetGroupAt(m_iCurrentItem);
	}
	return NULL;
}

CDibDoc * CTileSet::CreateCompatibleDIB(UINT nWidth, UINT nHeight)
{
	CDibDoc *pDoc = new CDibDoc;
	ASSERT_NEW(pDoc);

	CDIB *pDIB = m_dib.GetDIB();
	if (!pDoc->OnNewDocument(nWidth, nHeight, pDIB->GetDepth(), pDIB->GetClrTabAddress()))
	{
		delete pDoc;
		pDoc = NULL;
	}

	return pDoc;
}


void CTileSet::OnUpdateItemType(CCmdUI *pCmdUI)
{
#if 1
	// TBD: m_pActiveLayer->OnUpdateItemType(pCmdUI)
	CString string;
	pCmdUI->Enable(TRUE);
	if (m_iCurrentType == TSV_GROUPS)
		string.LoadString(IDS_GROUP);
	else
		string.LoadString(IDS_TILE);
	pCmdUI->SetText(string);
#endif
}

void CTileSet::OnUpdateItemId(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	CTileGroup *pGroup = GetCurrentGroup(); 
	if (pGroup) 
	{
		pCmdUI->SetText(pGroup->GetTitle());
	}
	else
	{
		// TBD: tile category?
		CString idstr;
		idstr.Format("%d",m_iCurrentItem);
		pCmdUI->SetText(idstr);
	}
}

void CTileSet::OnUpdateItemInfo(CCmdUI *pCmdUI)
{
	CTileGroup *pGroup = GetCurrentGroup(); 
	CString dimensions;
    CSize size;

	if (pGroup) 
		size = pGroup->GetSize();
	else
	    size = GetTileSize();

	dimensions.Format("%dx%dx%d", size.cx, size.cy, GetTileDepth());
	pCmdUI->SetText(dimensions);
	pCmdUI->Enable(TRUE);
}


void CTileSet::GetUsage(CTileList& usage)
{
	CWaitCursor wait;
	usage.SetSize(GetTileCount());
    POSITION pos = m_mapList.GetHeadPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pMap = m_mapList.GetNext(pos);
		ASSERT(pMap != NULL);
		pMap->UpdateTileUsage(usage);
	}
}

void CTileSet::OnTilesetTileCategories() 
{
	CCategoriesDlg dlg(&m_tileCategories,IDS_TILECATEGORIES);
	dlg.DoModal();
	UpdateAllViews(NULL);
}


void CTileSet::OnTilesetGroupCategories() 
{
	CCategoriesDlg dlg(&m_groupCategories,IDS_GROUPCATEGORIES);
	dlg.DoModal();
	UpdateAllViews(NULL);
}

void CTileSet::OnChangedViewList() 
{
	// if no more views on the document, delete ourself
	// not called if directly closing the document or terminating the app
	if (m_viewList.IsEmpty() && m_bAutoDelete && !HasOpenMaps())
	{
		OnCloseDocument();
		return;
	}

	// update the frame counts as needed
	UpdateFrameCounts();
}

void CTileSet::OnUpdateTilesetRemapToPalette(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetTileDepth() <= 8);
}

void CTileSet::OnTilesetRemapToPalette() 
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for filename

	UserWarn(IDS_WARN_PALETTE_CHANGE);

	// Initialize OPENFILENAME
	memset(&ofn,0,sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Bitmaps Files (*.bmp, *.dib)\0*.BMP;*.DIB\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrTitle = "Select Palette";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_LONGNAMES;
	szFile[0] = '\0';

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE) 
	{
		CDibDoc dib,newdib;
		TRY
		{
			if (dib.OnOpenDocument(ofn.lpstrFile)) // TBD: read palette only
			{
				if (dib.GetPalette())
				{
					CDIB *pOld = m_dib.GetDIB();
					CDIB *pNew = dib.GetDIB();
                    int width = pOld->GetWidth();
					int height = pOld->GetHeight();
                    BOOL bCreated = FALSE;

					// YUK!!! I SHOULDN'T HAVE TO DO THIS!!! 
					// But UpdateColors() doesn't do a good job.
					if (!newdib.OnNewDocument(width, height, pNew->GetDepth(), pNew->GetClrTabAddress()))
						AfxThrowMemoryException();

					pNew = newdib.GetDIB();
					HDC hdcDst, hdcSrc;
					if (hdcSrc = pOld->CreateHDC())
					{
						hdcDst = pNew->CreateHDC(hdcSrc);
						if (hdcDst)
						{
							HPALETTE hSrcPal = SelectPalette(hdcSrc, GetHPalette(), TRUE);
							HPALETTE hDstPal = SelectPalette(hdcDst, newdib.GetHPalette(), TRUE);
							BitBlt(hdcDst, 0, 0, width, height, hdcSrc, 0, 0, SRCCOPY);
							SelectPalette(hdcSrc, hSrcPal, TRUE);
							SelectPalette(hdcDst, hDstPal, TRUE);
							pNew->DeleteHDC();
							bCreated = TRUE;
						}
						pOld->DeleteHDC();
					}
					if (!bCreated)
						AfxThrowMemoryException();

					m_dib.SetDIB(newdib.DetachDIB());
					m_dib.SetPal(newdib.DetachPal()); 
					UpdateTransparency();
					UpdateAllViews(NULL, TSV_UPDATE_PALETTE);
				}
				else
					UserError(IDS_NO_PALETTE);
			}
		}
		END_TRY
		dib.DeleteContents();
		newdib.DeleteContents();
	}
	
}

void CTileSet::OnUpdateTilesetUsePalette(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetTileDepth() <= 8);
}

void CTileSet::OnTilesetUsePalette() 
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for filename

	UserWarn(IDS_WARN_PALETTE_CHANGE);

	// Initialize OPENFILENAME
	memset(&ofn,0,sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Bitmaps Files (*.bmp, *.dib)\0*.BMP;*.DIB\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrTitle = "Select Palette";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_LONGNAMES;
	szFile[0] = '\0';

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE) 
	{
		CDibDoc dib;
		TRY
		{
			if (dib.OnOpenDocument(ofn.lpstrFile)) // TBD: read palette only
			{
				if (dib.GetPalette())
				{
					m_dib.CopyPalette(dib.GetPalette());

					// Note: we must change the palette pointer because the
					// system seems to cache its value and won't update the
					// palette entries if the palette is selected & realized
					// in the current display device context.
					//
					//  Note: calling UnrealizeObject on the old dib palette 
					//  before modifying the palette doesn't seem to help.
					m_dib.SetPal(dib.DetachPal()); 

					UpdateTransparency();
					UpdateAllViews(NULL, TSV_UPDATE_PALETTE);
				}
				else
					UserError(IDS_NO_PALETTE);
			}
		}
		END_TRY
		dib.DeleteContents();
	}
	
	
}

CTileAttribute * CTileSet::FindAttribute(const CString& pszName)
{
	POSITION pos = m_attributeList.GetHeadPosition();
	while (pos != NULL)
	{
		CTileAttribute *pAttribute = m_attributeList.GetNext(pos);
		ASSERT(pAttribute != NULL);
		if (pszName.CompareNoCase(pAttribute->GetName()) == 0)
			return pAttribute;
	}
	return NULL;
}

BOOL CTileSet::DeleteAttribute(CTileAttribute *pAttribute)
{
	ASSERT(pAttribute != NULL);

	POSITION pos = m_attributeList.Find(pAttribute);
	if (pos != NULL) 
	{
		m_attributeList.RemoveAt(pos);
		delete pAttribute;
		SetModifiedFlag();
		return TRUE;
	}
	return FALSE;
}

CTileAttribute *CTileSet::AddAttribute(LPCTSTR lpszName, int nBitCount, int nDefaultValue)
{
	CTileAttribute *pAttribute = FindAttribute(lpszName);

	if (pAttribute)
	{
		ASSERT(nBitCount >= 0 && nBitCount <= MAX_ATTRIBUTE_BITS);
		if (pAttribute->GetBitCount() != nBitCount)
		{
			TRY
			{
				CTileAttribute *pOld = pAttribute;
				pAttribute = NULL;
				CString msg;
				AfxFormatString2(msg,IDS_ADJUST_ATTRIBUTE,GetTitle(), lpszName);
				if (AfxMessageBox(msg, MB_ICONQUESTION|MB_YESNO) == IDYES)
					pAttribute = pOld;
			}
			END_TRY
			if (pAttribute)
			{
				pAttribute->SetBitCount(nBitCount);
				pAttribute->SetDefaultValue(nDefaultValue);
				SetModifiedFlag();
			}
		}
	}
	else
	{
		TRY
		{
			pAttribute = new CTileAttribute(lpszName,nBitCount,GetTileCount(),nDefaultValue);
			ASSERT_NEW(pAttribute);
			m_attributeList.AddTail(pAttribute);
			SetModifiedFlag();
		}
		CATCH_ALL(e)
		{
			delete pAttribute;
			pAttribute = NULL;
		}
		END_CATCH_ALL
	}
	return pAttribute;
}

CTileAttribute *CTileSet::AddAttribute(CTileAttribute *pAttribute)
{
	return AddAttribute(pAttribute->GetName(), pAttribute->GetBitCount(), pAttribute->GetDefaultValue());
}

CTileAttribute * CTileSet::GetAttribute(int iIndex)
{
	POSITION pos = m_attributeList.FindIndex(iIndex);
	if (pos != NULL)
		return m_attributeList.GetAt(pos);
	return NULL;
}

BOOL CTileSet::GetAttribute(const CString& pszName, int iTile, int& iValue)
{
	CTileAttribute *pAttribute = FindAttribute(pszName);
	if (pAttribute)
	{
		iValue = pAttribute->GetValue(iTile);
		return TRUE;
	}
	return FALSE;
}

BOOL CTileSet::SetAttribute(const CString& pszName, int iTile, int iValue)
{
	CTileAttribute *pAttribute = FindAttribute(pszName);
	if (pAttribute)
	{
	    pAttribute->SetValue(iTile, iValue);
		SetModifiedFlag();
		return TRUE;
	}
	return FALSE;
}

void CTileSet::AdjustAttributes(int iTile, const CAttributeResult &rAttributes)
{
	ASSERT(iTile >= 0 && iTile < GetTileCount());
	int iCount = min(GetAttributeCount(), rAttributes.GetSize());

	for (int i=0; i < iCount; i++)
	{
		int iValue = rAttributes[i].m_currentValue;
		CTileAttribute *pAttribute = GetAttribute(i);
		ASSERT(pAttribute != NULL);
		ASSERT(pAttribute->GetName() == rAttributes[i].m_pszName);
		pAttribute->SetValue(iTile,iValue);
		SetModifiedFlag();
		
	}
}

void CTileSet::GetNextAttribute(POSITION& pos, void *pTargetData, CAttributeInfo& rInfo)
{
	CTileAttribute *pAttribute = m_attributeList.GetNext(pos);
	ASSERT(pAttribute != NULL);

	// copy the CAttribute related information.
	rInfo.SetBitCount(pAttribute->GetBitCount()); 
	rInfo.SetDefaultValue(pAttribute->GetDefaultValue());

	// copy the CTileAttribute related information
	int iTile = (int)pTargetData;
	ASSERT(iTile >= 0 && iTile < GetTileCount());
    rInfo.m_pszName = pAttribute->GetName();
	rInfo.m_currentValue = pAttribute->GetValue(iTile);
    rInfo.m_bRemoved = FALSE;
}


void CTileSet::MatchMap()
{
	int iCur=0;
	int iSize = m_tileMap.GetSize();
	
	while (iCur < iSize)
	{
		m_tileMap.SetAt(iCur, iCur);
		m_tileList.SetAtGrow(iCur, iCur);
		iCur++;
	}
}
