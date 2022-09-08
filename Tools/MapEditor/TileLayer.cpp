#include "stdafx.h"
#include "limits.h"
#include "MapEditor.h"
#include "MapFrame.h"
#include "MapEditorView.h"
#include "TileSetView.h"
#include "TileLayer.h"
#include "NumberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
class CTileUndo 
{
protected:
	CRect m_rect;
	CMap<int *, int *, int, int> m_data;

public:
	CTileUndo()
	{
		m_rect.SetRectEmpty();
		m_data.InitHashTable(31); // TBD
	}
	~CTileUndo()
	{
		m_data.RemoveAll();
	}
    BOOL IsSet(int *piTilePtr)
	{
		int iTile;
		return m_data.Lookup(piTilePtr,iTile);
	}
	void SetAt(int iRow, int iColumn, int *piTilePtr, int iTile)
	{
		CRect newRect = CRect(CPoint(iColumn,iRow),CPoint(iColumn+1,iRow+1));
		m_rect.UnionRect(m_rect,newRect);
		m_data.SetAt(piTilePtr, iTile);
	}
	void SetAt(int *piTilePtr, int iTile) 
	{	
		m_data.SetAt(piTilePtr, iTile); 
	}
	BOOL IsEmpty() const 
	{ 
		return m_data.IsEmpty(); 
	}
	POSITION GetStartPosition() const 
	{
		return m_data.GetStartPosition(); 
	}
	void GetNextAssoc( POSITION& rNextPosition, int *& rKey, int& rValue ) const
	{
		m_data.GetNextAssoc(rNextPosition, rKey, rValue);
	}
	CRect GetRect() const
	{
		return m_rect;
	}
	void SetRect(CRect rect)
	{
		m_rect = rect;
	}
};


/*
** Notes: 
**    1. Internally a TileLayer uses 0 to mean no tile, negative numbers to
**	     mean a selected tile, and positive numbers to mean a non-selected tile.
**       When the layer is serialized to disk, we just store the actual zero-based
**       tile index.
**
**    2. In memory a TileLayer is always the same size as the map.  
**       TBD: On disk we should only save the minimum tile area.
*/
#define NO_TILE 0

// TBD: does it matter that we associate clipboard with current
// task not with current view?


inline int *CTileLayer::GetTilePointer(int iRow, int iColumn)
{
   ASSERT(iRow >= 0 && iRow < m_size.cy);
   ASSERT(iColumn >= 0 && iColumn < m_size.cx);
   return &m_piTiles[iRow * m_size.cx + iColumn];
}

/////////////////////////////////////////////////////////////////////////////
// CTileLayer construction/destruction

CTileLayer::CTileLayer()
{
	m_nSelected = 0;
	m_nTileCount = 0;
	m_piTiles = NULL;
	m_location.x = 0;
	m_location.y = 0;
	m_size.cx = 0;
	m_size.cy = 0;
}

CTileLayer::~CTileLayer()
{
  ClearUndo();
  if (m_piTiles)
  {
	  TRACE("Deleting tiles %s\n",GetTitle());
	  delete [] m_piTiles;
  }
}


void CTileLayer::SetSize(int iWidth, int iHeight)
{
	ASSERT(m_piTiles == NULL);
	m_size.cy = iHeight;
	m_size.cx = iWidth;
	m_nTileCount = m_size.cx * m_size.cy;
	m_nSelected = 0;
	if (m_nTileCount > 0)
	{
		m_piTiles = new int[m_nTileCount];
		ASSERT_NEW(m_piTiles);
	}
	else
		m_piTiles = NULL;
}

CString CTileLayer::GetInfo()
{
	CString info;
	if (m_bTransparent) 
		VERIFY(info.LoadString(IDS_OVERLAY_LAYER));
	else
		VERIFY(info.LoadString(IDS_BASE_LAYER));
	return info;
}

void CTileLayer::FillLayer(int initTile)
{
	int *pTile = m_piTiles;
	for (UINT i=0; i < m_nTileCount; i++)
		*pTile++ = initTile;
}

CTileLayer::CTileLayer(CMapEditorDoc *pMap, LPCSTR lpszTitle,BOOL bTransparent, int initTile)
{
	m_piTiles = NULL;
	if (initTile < -1) 
		initTile = -1;
	initTile += 1;

    SetTitle(lpszTitle);
	SetLocation(0,0);
	SetSize(pMap->m_iMapWidth, pMap->m_iMapHeight);
	FillLayer(initTile);
	SetMap(pMap);
	m_bTransparent = bTransparent; 
}

/////////////////////////////////////////////////////////////////////////////
// CTileLayer Serialization

IMPLEMENT_SERIAL(CTileLayer, CMapLayer, VERSIONABLE_SCHEMA | 2)

void CTileLayer::Serialize(CArchive& ar) 
{
	// Note: since TileLayers are only used dynamically we could
	// have lived without the PUT_SAFE_SCHEMA/GET_SAFE_SCHEMA; live and learn
	int iTile, *pTile;
	CMapLayer::Serialize(ar);

	if (ar.IsStoring())
	{
		PUT_SAFE_SCHEMA(ar, CTileLayer);
		CRect rect = GetMinRect();
		ar << rect.left;
		ar << rect.top;
		ar << rect.Width();
		ar << rect.Height();
		ar << m_bTransparent;
        for (int iRow = rect.top; iRow < rect.bottom; iRow++)
		{
			for (int iCol = rect.left; iCol < rect.right; iCol++)
			{
				ar << GetTile(iRow, iCol);
			}
		}
	}
	else 
	{
		UINT schema = GET_SAFE_SCHEMA(ar, CTileLayer, 1);
		if (schema < 2)
			ar >> m_pszTitle;
		ar >> m_location.x;
		ar >> m_location.y;
		ar >> m_size.cx;
		ar >> m_size.cy;
		ar >> m_bTransparent;
		SetSize(m_size.cx,m_size.cy);
		if (m_nTileCount)
		{
			ASSERT(m_piTiles != NULL);
			pTile = m_piTiles;
			for (UINT i = 0; i < m_nTileCount; i++,pTile++)
			{
				ar >> iTile;
				*pTile = iTile + 1;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CTileLayer, CMapLayer)
	//{{AFX_MSG_MAP(CTileLayer)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateSelection)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UPDATEATTRIBUTES, OnUpdateEditUpdateAttributes)
	ON_COMMAND(ID_EDIT_UPDATEATTRIBUTES, OnEditUpdateAttributes)
	ON_COMMAND(ID_UP, OnIncrementSelection)
	ON_COMMAND(ID_DOWN, OnDecrementSelection)
	ON_COMMAND(ID_EDIT_RANDOMIZE, OnEditRandomize)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateSelection)
	ON_UPDATE_COMMAND_UI(ID_DOWN, OnUpdateSelection)
	ON_UPDATE_COMMAND_UI(ID_UP, OnUpdateSelection)
	ON_UPDATE_COMMAND_UI(ID_LEFT, OnUpdateSelection)
	ON_COMMAND(ID_LEFT, OnDecrementSelection)
	ON_UPDATE_COMMAND_UI(ID_RIGHT, OnUpdateSelection)
	ON_COMMAND(ID_RIGHT, OnIncrementSelection)
	ON_UPDATE_COMMAND_UI(ID_EDIT_RANDOMIZE, OnUpdateEditRandomize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTileLayer diagnostics

#ifdef _DEBUG
void CTileLayer::AssertValid() const
{
	CMapLayer::AssertValid();
	if (m_pMap)
	{
		// for now we require that the layer fill the entire map but
		// this may not be necessary in the future.
		ASSERT(m_size.cx == m_pMap->m_iMapWidth);
		ASSERT(m_size.cy == m_pMap->m_iMapHeight);
		ASSERT(m_location.x == 0);
		ASSERT(m_location.y == 0);
	}
	ASSERT(m_nSelected >= 0 && m_nSelected <= m_nTileCount);
	ASSERT(m_size.cx >= 0 && m_size.cy >= 0);
	ASSERT(m_nTileCount == ((UINT)m_size.cx * (UINT)m_size.cy));
	if (m_nTileCount)
	{
		ASSERT(m_piTiles != NULL);
		// TBD: check the size of the allocation
	}
	else
	{
		ASSERT(m_piTiles == NULL);
	}

	UINT selectedCount = 0;
	int *pTile = m_piTiles;
	for (UINT i=0; i < m_nTileCount; i++)
	{
		if (*pTile++ < 0)
			selectedCount++;
	}
	ASSERT(selectedCount == m_nSelected);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////
// Implementation

/*
** METHOD
**    CTileLayer::SetTile
**
** PARAMETERS
**     int iRow         -- row position of tile within this layer
**     int iColumn      -- column position of tile within this layer
**     int iTile        -- zero-based index of tileset tile
**     CTileUndo *pUndo -- optional pointer to current undo level
**
** DESCRIPTION:
**     stores the given tile in the given row,column position
**     in this tile layer.  If pUndo is non-NULL, records the
**     old tile value if it wasn't already present.
*/
void CTileLayer::SetTile(int iRow, int iColumn, int iTile, CTileUndo *pUndo)
{
	ASSERT(iTile >= -1);
	int *pTile = GetTilePointer(iRow,iColumn);
	if (pUndo && !pUndo->IsSet(pTile))
	{
		pUndo->SetAt(iRow,iColumn,pTile,abs(*pTile));
	}
	// Note: update the m_nSelected and the tile after recording the
	// undo in case the undo throws a memory exception.
	if (*pTile < 0) m_nSelected -= 1;
	*pTile = iTile + 1; 

	if (g_bPlaceWithAttributes)
		GetMap()->SetAttributes(iRow,iColumn,iTile);
}

/*
** METHOD
**    CTileLayer::GetTile
**
** PARAMETERS
**     int iRow     -- row position of tile within this layer
**     int iColumn  -- column position of tile within this layer
**
** DESCRIPTION:
**     returns the tile stored at the given row,column position in
**     this layer.  Note: this function may return a tile number 
**     greater than the number of tiles in the current tileset if
**     this layer was originally created with a different tileset.
**
*/
int CTileLayer::GetTile(int iRow, int iColumn)
{
	return abs( *GetTilePointer(iRow,iColumn) ) - 1;
}

int CTileLayer::GetTile(int iRow, int iColumn, BOOL *pbSelected)
{
	ASSERT(pbSelected != NULL);
	int iTile = *GetTilePointer(iRow,iColumn);
	if (iTile < 0)
	{
		*pbSelected = TRUE;
		iTile = -iTile;
	}
	else
		*pbSelected = FALSE;
	return iTile - 1;
}

/*
** PARAMETERS
**     int iRow     -- row position of tile within this layer
**     int iColumn  -- column position of tile within this layer
*/
BOOL CTileLayer::SelectTile(int iRow, int iColumn, BOOL bSelected)
{
	int *pTile = GetTilePointer(iRow,iColumn);
	int iTile = *pTile;
	if (bSelected)
	{
		if (iTile > 0)
		{
			*pTile = - iTile;
			m_nSelected += 1;
			return TRUE;
		}
	}
	else
	{
		if (iTile < 0)
		{
			*pTile = - iTile;
			m_nSelected -= 1;
			return TRUE;
		}
	}
	return FALSE;
}

/*
** METHOD
**    CTileLayer::CropToSelection
**
** PARAMETERS
**    CRect rect            -- normalized cropping area (in pixels)
**    BOOL bSelectedOnly    -- true if only selected items within area should be copied
**
** DESCRIPTION
**    creates and returns a NEW layer just large enough to cover the given
**    rectangle.  If bSelectedOnly, copies only those tiles in the cropped
**    area that are currently selected.  If !bSelectedOnly, copies all
**    tiles in the cropped area.
**
**    NOTE: this function DOES NOT set the new layers' map 
**/
CMapLayer *CTileLayer::CropToSelection(CRect rect, int iStartRow, int iStartCol, int iEndRow, int iEndCol, BOOL bSelectedOnly)
{
	CSize tileSize = GetTileSet()->GetTileSize();

#ifdef _DEBUG
	CMapLayer::CropToSelection(rect,iStartRow,iStartCol,iEndRow,iEndCol,bSelectedOnly);  // verify pre-conditions
#endif

	CTileLayer *pLayer = new CTileLayer;
	ASSERT_NEW(pLayer);

	BOOL bSelected;
	pLayer->SetSize(rect.Width() / tileSize.cx, rect.Height() / tileSize.cy);
	pLayer->FillLayer(NO_TILE);
	pLayer->SetTitle(m_pszTitle);
	pLayer->m_bTransparent = m_bTransparent;


	// since all layers will be asked to crop to crop so we should
	// not reset the attributes here.

	// if endcol or endrow is greater than the tilelayer width or height then
	// all new tiles less than iEndCol-m_size.cx should be 0

	BOOL bSavePlaceWithAttributes = g_bPlaceWithAttributes;
	g_bPlaceWithAttributes = FALSE;
	for (int iRow = iStartRow; iRow < iEndRow; iRow++)
	{
		for (int iCol = iStartCol; iCol < iEndCol; iCol++)
		{
			if (iEndRow > m_size.cy && iRow < (iEndRow-m_size.cy))
			{
				pLayer->SetTile(iRow-iStartRow,iCol-iStartCol,0);
				continue;
			}
			if (iEndCol > m_size.cx && iCol < (iEndCol-m_size.cx))
			{
				pLayer->SetTile(iRow-iStartRow,iCol-iStartCol,0);
				continue;
			}
			int iTile = GetTile((iEndRow > m_size.cy) ? iRow-(iEndRow-m_size.cy) : iRow, 
				(iEndCol > m_size.cx) ? iCol-(iEndCol-m_size.cx) : iCol,&bSelected);
			if (bSelectedOnly && !bSelected)
				iTile = -1;
			pLayer->SetTile((iRow-iStartRow), 
				(iCol-iStartCol),iTile);
		}
	}
	g_bPlaceWithAttributes = bSavePlaceWithAttributes;
	pLayer->m_bVisible = m_bVisible;


	return pLayer;
}

/*
** PARAMETERS
**     int iRow     -- row position of tile within this layer
**     int iColumn  -- column position of tile within this layer
*/
BOOL CTileLayer::ToggleTile(int iRow, int iColumn)
{
	int *pTile = GetTilePointer(iRow,iColumn);
	BOOL bSelected = FALSE;

	*pTile = - (*pTile);
	if (*pTile < 0)
	{
		++m_nSelected;
		InvalidateLayer(iRow,iColumn); // after updating m_nSelected
		bSelected=TRUE;
	}
	else if (*pTile > 0)
	{
		--m_nSelected;
		InvalidateLayer(iRow,iColumn); // after updating m_nSelected
	}
	return bSelected;
}

/*
** METHOD
**   CTileLayer::RemoveTile
**
** PARAMETERS
**   int iTileIndex -- zero-based index of tile to remove from this layer
**
** DESCRIPTION
**    removes all occurrences of the given tile from this layer. 
**    Note: this function does NOT invalidate/update the map 
**    because it is too slow when removing lots and lots of tiles.
**    Instead it just marks the map as needing updating.
**/
void CTileLayer::RemoveTile(int iTileIndex)
{
	iTileIndex += 1;
	int *pTile = m_piTiles;
	int iTile;
    BOOL bModified = FALSE;
	BOOL bNeedsUpdate = FALSE;

	for (UINT n = 0; n < m_nTileCount; n++, pTile++)
    {
		iTile = abs(*pTile);
		if (iTile == iTileIndex)
		{
			if (*pTile < 0) 
				m_nSelected -= 1;
			*pTile = NO_TILE;
			bNeedsUpdate = TRUE;
			bModified = TRUE;
		}
		else if (iTile > iTileIndex)
		{
			*pTile -= 1; // all subsequent tiles get renumbered
			bModified = TRUE;
			
		}
	}
	if (bModified) SetModifiedFlag();
	if (bNeedsUpdate) NeedsUpdate();
}


/*
** METHOD
**    CTileLayer::ReplaceTile
**
** PARAMETERS
**    int iTile        -- zero-based index tile to be replaced
**    int iReplacement -- zero-based index of replacement tile
**
** DESCRIPTION
**    Replaces all occurrences of iTile with iReplacement in this map
**
** RETURNS
**    TRUE if any tiles were replaced. FALSE if iTile was
**    not used in the current layer.
*/
void CTileLayer::ReplaceTile(int iTile, int iReplacement)
{
    BOOL bModified = FALSE;
	iTile += 1;
	iReplacement += 1;

	int *pTile = m_piTiles;
	for (UINT n = 0; n < m_nTileCount; n++,pTile++)
	{
		if (abs(*pTile) == iTile)
		{
			if (*pTile < 0)
				m_nSelected -= 1;
			*pTile = iReplacement; 
			bModified = TRUE;
		}
    }
    if (bModified) 
	{
		NeedsUpdate();
		SetModifiedFlag();
	}
}

// goes through the entire layer and replaces every 
// occurrence of every tile in repList with the value 
// associated with that tile in repList if and only if
// that value is >= 0.  Call this method if you are 
// replacing many tiles.
void CTileLayer::ReplaceTiles(CTileList& repList)
{
    BOOL bModified = FALSE;
	int *pTile = m_piTiles;
	int iSize = repList.GetSize();
	if (iSize) for (UINT n = 0; n < m_nTileCount; n++,pTile++)
	{
		int iTile = abs(*pTile) - 1;
		if (iTile >= 0 && iTile < iSize && repList[iTile] >= 0)
		{
			if (*pTile < 0)
				m_nSelected -= 1;
			*pTile = repList[iTile] + 1;
			bModified = TRUE;
		}
    }
    if (bModified) 
	{
		NeedsUpdate();
		SetModifiedFlag();
	}
}
/*
** METHOD
**   CMapEditorDoc::UpdateTiles
**
** PARAMETERS
**    int iStartTile - zero-based index of starting tile to update
**    int iEndTile   - zero-based index of ending tile to update.
**
** DESCRIPTION
**    Invalidates all areas of this layer that use the tile indices from
**    iStartTile to iEndTile (inclusive). Call this method when
**    a tile image in the tileset has been replaced or additional
**    tiles have been added to the tileset.
*/
void CTileLayer::UpdateTiles(int iStartTile, int iEndTile)
{
    int *pTile = m_piTiles;
	int iTile;
    BOOL bNeedsUpdate = FALSE;

	for (int iRow = 0; iRow < m_size.cy; iRow++)
	{
		for (int iCol = 0; iCol < m_size.cx; iCol++, pTile++)
		{
			iTile = abs(*pTile)-1;
			if (iTile >= iStartTile && iTile <= iEndTile)
				bNeedsUpdate = TRUE;
		}
	}
	if (bNeedsUpdate)
		NeedsUpdate();
}


//////////////////////////////////////////////////////////////////////
// Message handlers
void CTileLayer::SelectNone() 
{
   if (m_nSelected)
   {
	   int *pTile = m_piTiles;

	   CRect rect = GetSelection();
	   for (UINT i=0; i < m_nTileCount; i++,pTile++)
	   {
		   if (*pTile < 0) 
			  *pTile = - *pTile;
	   }
	   m_nSelected = 0;
	   Invalidate(rect);
   }
}

void CTileLayer::OnEditSelectAll() 
{
   int *pTile = m_piTiles;
   for (UINT i=0; i < m_nTileCount; i++,pTile++)
   {
	   if (*pTile > 0) 
	   {
		   *pTile = - (*pTile);
		   m_nSelected += 1;
	   }
   }
   Invalidate(NULL);
}	

/*
** METHOD
**   CTileLayer::OnUpdateSelection
**
** PARAMETERS
**   CCmdUI *pCmdUI  -- target menu or toolbar item 
**
** DESCRIPTION
**   enables the given menu or toolbar item if one or more
**   tiles are selected.
**
**   For now, it disables the item if the user is using the
**   group preview feature because Windows will not process
**   keyboard actions when capturing some other window is
**   capturing the mouse.  This is a dumb restriction and as
**   soon as I can figure out a way around it, I will
**   remove the !GetMap()->HasPreview() test.
*/
void CTileLayer::OnUpdateSelection(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetTileSet() && IsSelected() && !GetMap()->HasPreview());
}




void CTileLayer::OnEditCopy()
{
	if (OpenClipboard())
	{
		EmptyClipboard();
		TRY
		{
			CSharedFile	memFile;
			CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);

			DoCutCopyPaste(ar, FALSE);
			ar.Flush();

			HGLOBAL hData = memFile.Detach();
			::SetClipboardData(g_nTileSetFormat, hData);
			CloseClipboard();
		}
		CATCH_ALL(e)
		{
			CloseClipboard();
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	else
		AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
}

void CTileLayer::OnEditCut()
{

	if (OpenClipboard())
	{
		EmptyClipboard();
		TRY
		{
			CSharedFile	memFile;
			CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);

			DoCutCopyPaste(ar, TRUE);
			ar.Flush();

			HGLOBAL hData = memFile.Detach();
			::SetClipboardData(g_nTileSetFormat, hData);
			CloseClipboard();
		}
		CATCH_ALL(e)
		{
			CloseClipboard();
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	else
		AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
	
}

void CTileLayer::DoCutCopyPaste(CArchive &ar, BOOL bCut)
{
	ASSERT(m_pMap);
    CTileOp opType = bCut ? TSOP_CUT : TSOP_COPY;
	CTileSetOp op(opType, TSV_GROUPS, m_nSelected, m_pMap->GetTileSet());

	CRect rect = GetSelectionGroup(&op); // returns bounding box of selection within map
    op.Serialize(ar);

	if (bCut)
	{
		ASSERT(ar.IsStoring());
  		RemoveSelection();
	}
	// updated view and flag as modified if cut or paste operation
	if (!(ar.IsStoring() && !bCut))
	{
	    Invalidate(rect); 
		SetModifiedFlag();
	}
}

void CTileLayer::InvalidateLayer(int iRow, int iColumn)
{
	ASSERT(iRow >= 0 && iRow < m_size.cy);
	ASSERT(iColumn >= 0 && iColumn < m_size.cx);
	CMapLayer::Invalidate(iRow + m_location.y, iColumn + m_location.x);
}

///////////////////////////////////////////////////////////////////////////

/*
** METHOD
**   CTileLayer::GetSelectionGroup
**
** PARAMETERS
**   CTileSetOp* op -- optional place to store the tile group
**
** DESCRIPTION
**    returns the tile-aligned bounding box of all the selected tiles.
**    Note: the bottom right corner of the box is the bottom right
**    corner of the bottom right tile selected.  If no tiles are
**    selected, the rectangle returned will be empty.
**   
*/
CRect CTileLayer::GetSelectionGroup(CTileSetOp* op)
{
	int iMinRow = m_size.cy;
	int iMinCol = m_size.cx;
	int iMaxRow = -1;
	int iMaxCol = -1;
    int *pTile = m_piTiles;
	CRect rect;

	if (m_nSelected > 0)
	{
		CTileGroup group;
		for (int iRow = 0; iRow < m_size.cy; iRow++)
		{
			for (int iCol = 0; iCol < m_size.cx; iCol++, pTile++)
			{
				if (*pTile < 0)
				{
					if (iRow < iMinRow)
						iMinRow = iRow;
					if (iCol < iMinCol)
						iMinCol = iCol;
					if (iRow > iMaxRow)
						iMaxRow = iRow;
					if (iCol > iMaxCol)
						iMaxCol = iCol;
				}
			}
		}
		ASSERT(iMinRow >= 0 && iMinRow <= iMaxRow);
		ASSERT(iMinCol >= 0 && iMinCol <= iMaxCol);
		rect.SetRect(iMinCol, iMinRow, iMaxCol+1, iMaxRow+1);

		if (op != NULL)
		{
			CTileGroup group;
			BOOL bSelected;
			group.SetSize(rect.Width(), rect.Height());

			for (int iRow = rect.top; iRow < rect.bottom; iRow++)
			{
				for (int iCol = rect.left; iCol < rect.right; iCol++)
				{
					int iTile = GetTile(iRow,iCol,&bSelected);
					if (!bSelected) iTile = -1;
					group.SetTile(iRow - rect.top, iCol - rect.left, iTile);
				}
			}
			
			/////////////////////////////////////////////////////////////////
			// Get Multi-Layer Group Data
			group.GetMLayer(iMinCol, iMinRow, GetMap());
			/////////////////////////////////////////////////////////////////
			op->AddGroup(&group);
		}
	}
	else
		rect.SetRectEmpty();

	if (m_pMap)
	{
		ASSERT(m_location == CPoint(0,0)); // TBD: this is temporary!!
		LayerToMapRect(rect);
	}
	return rect;
}

void CTileLayer::Select(CRect rect, BOOL bSelected)
{
	rect.NormalizeRect();
	int iStartCol, iEndCol, iStartRow, iEndRow;

	GetRowColumn(rect.TopLeft(),iStartRow, iStartCol,FALSE);
	GetRowColumn(rect.BottomRight(),iEndRow, iEndCol,TRUE);
    BOOL bModified = FALSE;

	for (int iRow = iStartRow; iRow < iEndRow; iRow++)
	{
		for (int iCol = iStartCol; iCol < iEndCol; iCol++)
		{
			bModified |= SelectTile(iRow, iCol, bSelected);
		}
	}
	if (bModified)
	{
		iStartRow += m_location.y;
		iStartCol += m_location.x;
		iEndRow += m_location.y;
		iEndCol += m_location.x;
		Invalidate(iStartRow,iStartCol,iEndRow,iEndCol);
	}
}

void CTileLayer::Draw(HDC hdc, CPoint offset, int iStartRow, int iStartCol,
	int iEndRow, int iEndCol, CDIB *pDst)
{
	CTileSet *pTileSet = GetTileSet();
	if (pTileSet == NULL || m_piTiles == NULL)
		return;

	int iTileWidth = pTileSet->m_iTileWidth;
	int iTileHeight = pTileSet->m_iTileHeight;
    int iTileCount = pTileSet->GetTileCount();
    CSize selSize(iTileWidth - 1, iTileHeight -1);

	// TBD: if selsize is not even, pDC->Rectangle() will not 
	// draw right/bottom line segments.
	CPoint pt;
	int iTile;
	BOOL bSelected; 

	pt.y = offset.y;
	if (pTileSet->BeginDraw(hdc))
	{			
	    HPEN hGridPen;
		BOOL bGrid = GetMap()->GetGrid();
        if (bGrid)
		{
			hGridPen = CreatePen(PS_DOT, 1, RGB(0,0,0));
			if (hGridPen == NULL) bGrid = FALSE;
		}
		HGDIOBJ brush = GetStockObject(NULL_BRUSH);
		HGDIOBJ hWhitePen = GetStockObject(WHITE_PEN);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
        HPEN oldPen = (HPEN)SelectObject(hdc, hWhitePen);
		// TBD: if selsize is not even, pDC->Rectangle() will not 
		// draw right/bottom line segments.
		for( int iRow = iStartRow; iRow < iEndRow; iRow++ )
		{
			pt.x = offset.x;
			for( int iColumn = iStartCol; iColumn < iEndCol; iColumn++ )
			{
				iTile = GetTile(iRow,iColumn,&bSelected);
				if (iTile >= 0 && iTile < iTileCount)
				{
					if (!pTileSet->Draw(hdc, iTile, pt, m_bTransparent, pDst)) 
						TRACE("Couldn't draw tile %d\n", iTile); 

					CRect srect(pt,selSize);
					if (bSelected)
					{
						SelectObject(hdc, hWhitePen);
						CPoint center = srect.CenterPoint();
						Rectangle(hdc, srect.left, srect.top, srect.right, srect.bottom);
						MoveToEx(hdc, center.x, center.y, NULL);
						LineTo(hdc, center.x+1, center.y+1);
					}
					else if (bGrid)
					{
						SelectObject(hdc,hGridPen);
						Rectangle(hdc, srect.left-1, srect.top-1, srect.right+1, srect.bottom+1);
					}
				}
				pt.x += iTileWidth; 
			}
			pt.y += iTileHeight; 
		}
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
    if (bGrid) DeleteObject(hGridPen);
	pTileSet->EndDraw();
	}
}

void CTileLayer::RemoveSelection()
{
   ASSERT_VALID(this);
   if (m_nSelected)
   {
	   int *pTile = m_piTiles;
	   BeginEdit();
	   CTileUndo *pUndo = GetCurrentUndo();
	   for (int iRow = 0; iRow < m_size.cy; iRow++)
	   {
		   for (int iCol = 0; iCol < m_size.cx; iCol++, pTile++)
		   {
			   if (*pTile < 0)
			   {
				   if (pUndo)
					   pUndo->SetAt(iRow, iCol, pTile, -(*pTile));
				   *pTile = NO_TILE;
				   if (!--m_nSelected)
					   goto done;
			   }
		   }
	   }
done:
	   EndEdit();
   }
}


BOOL CTileLayer::PlaceGroup(CTileGroup *pGroup, int iRow, int iColumn)
{
  CSize size = pGroup->GetSize();
  int iMaxRow = min(iRow+size.cy, m_size.cy);
  int iMaxCol = min(iColumn+size.cx, m_size.cx);
  BOOL bModified = FALSE;
  CTileUndo *pUndo = GetCurrentUndo();
  BeginWaitCursor();
  /////////////////////////////////////////////////////////////////
  // Process multi-layer group
  if (FALSE == pGroup->DoMLayer(iColumn, iRow, iMaxCol, iMaxRow, GetMap()))
  {
	  /////////////////////////////////////////////////////////////////
	  // If group is not multi-layer or DoMLayer fails in some way, then try
	  // to use the group as normal.
	  /////////////////////////////////////////////////////////////////
	  for (int row=iRow; row < iMaxRow; row++)
	  {
		  for (int col=iColumn; col < iMaxCol; col++)
		  {
			  int iTile = pGroup->GetTile(row - iRow, col - iColumn);
			  if (iTile >= 0)
			  {
				  SetTile(row, col, iTile, pUndo); // too slow to invalidate while painting
				  bModified = TRUE;
			  }
		  }
	  }
  }
  else
	  bModified = TRUE;
  /////////////////////////////////////////////////////////////////
  if (bModified)
  {
  	  SetModifiedFlag();
	  Invalidate(iRow, iColumn, iMaxRow, iMaxCol);
  }
  EndWaitCursor();
  return bModified;
}

CMapLayerMode CTileLayer::GetItem(CPoint point, int iRow, int iColumn)
{
	GetMap()->ClearPreviewRect();
	UpdateItemPos(iRow,iColumn);
	GetTileSet()->SetCurrentItem(TSV_TILES, GetTile(iRow,iColumn));
	return none;	
}

BOOL CTileLayer::PreviewItem(CPoint point, int iRow, int iColumn)
{
#if 1 
	CMapEditorDoc *pDoc = GetMap();
	CTileSet *pTileSet = GetTileSet();
	CTileGroup *pGroup = pTileSet->GetCurrentGroup();
	if (pGroup != NULL)
	{
		pDoc->SetPreviewRect(CRect(pDoc->GetTileOffset(iRow,iColumn),
							 pTileSet->GetGroupExtent(pGroup)));
		return TRUE;
	}
#endif
	return FALSE;
}

void CTileLayer::DrawPreview(HDC hdc, CPoint offset, CDIB *pDIB)
{
	CTileSet *pTileSet = GetTileSet();
	pTileSet->PreviewCurrentGroup(hdc, offset, m_bTransparent, pDIB);
}

CMapLayerMode CTileLayer::SelectItem(CPoint point, int iRow, int iColumn, BOOL bSelected)
{
	if (SelectTile(iRow,iColumn,bSelected))
	{
		UpdateItemPos(iRow,iColumn);
		InvalidateLayer(iRow,iColumn);
	}
	return selectItem; // so we will continue to select/deselect tiles
}

CMapLayerMode CTileLayer::ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected)
{
	bSelected = ToggleTile(iRow,iColumn);
	UpdateItemPos(iRow,iColumn);
	GetMap()->ClearPreviewRect();
	GetTileSet()->SetCurrentItem(TSV_TILES, GetTile(iRow,iColumn));
	return selectItem; // so we will continue to select/deselect tiles
}

CMapLayerMode CTileLayer::PlaceItem(CPoint point, int iRow, int iColumn)
{
	BOOL bPlaced = FALSE;
	CTileSet *pTileSet = GetTileSet();
	if (pTileSet)
	{
		switch(pTileSet->m_iCurrentType)
		{
			case TSV_GROUPS:
				{
					CTileGroup *pGroup = pTileSet->GetCurrentGroup();
					if (pGroup != NULL)
					{
						GetMap()->ClearPreviewRect();
						bPlaced = PlaceGroup(pGroup,iRow,iColumn);
					}
				}
				break;
			default: // TSV_TILES:
				if (pTileSet->m_iCurrentItem >= 0)
				{
					SetTile(iRow, iColumn, pTileSet->m_iCurrentItem, GetCurrentUndo());
					SetModifiedFlag();
					InvalidateLayer(iRow,iColumn);
					bPlaced = TRUE;
				}
		}
	}
	if (bPlaced)
	{
		UpdateItemPos(iRow,iColumn);
		return placeItem;  // so we will continue to draw
	}
	return none;
}

void CTileLayer::GetRowColumn(CPoint pt, int& iRow, int& iColumn, BOOL bRoundUp)
{
	// converts the map point to the layer row column, clipping if needed
	GetMap()->GetRowColumn(pt,iRow,iColumn,bRoundUp,TRUE);
}


void CTileLayer::UpdateTileUsage(CTileList& usage)
{
	int iTileMax = usage.GetSize();
	int *pTile = m_piTiles;

	ASSERT(iTileMax > 0);
    ASSERT(m_piTiles != NULL);

	for (UINT n = 0; n < m_nTileCount; n++,pTile++)
	{
		int iIndex = abs(*pTile)-1;
		if (iIndex >= 0 && iIndex < iTileMax && usage[iIndex] < INT_MAX)
			usage[iIndex] += 1; 
	}
}

void CTileLayer::OnUpdateEditFind(CCmdUI* pCmdUI) 
{
	CTileSet *pTileSet = GetTileSet();
	pCmdUI->Enable(pTileSet->m_iCurrentType == TSV_TILES && pTileSet->m_iCurrentItem >= 0);
}

void CTileLayer::OnEditFind() 
{
	SelectNone();
	int *pTile = m_piTiles;
    int iTile = GetTileSet()->m_iCurrentItem + 1;
	for (UINT n = 0; n < m_nTileCount; n++,pTile++)
	{
		int iIndex = *pTile;
		if (iIndex == iTile)
		{
			*pTile = -iTile;
			++m_nSelected;
		}
	}
	ASSERT_VALID(this);

	if (m_nSelected)
		Invalidate(GetSelection());

	CString status;
	status.Format(IDS_ITEMS_FOUND_FORMAT,m_nSelected);
	ShowStatus(status);
}



void CTileLayer::SetMap(CMapEditorDoc *pMap)
{
	if (pMap)
	{
		// expand or shrink the layer to fit the map dimensions
		int iWidth = pMap->m_iMapWidth;
		int iHeight = pMap->m_iMapHeight;
		if (m_size.cx != iWidth || m_size.cy != iHeight || m_location.x != 0 || m_location.y != 0)
		{
			UINT nMapSize = iWidth * iHeight;
			int *piTiles = new int[nMapSize];
			ASSERT(piTiles != NULL);
			
			int *pTile = piTiles;
			int iStartCol = min(m_location.x, iWidth);
			int iStartRow = min(m_location.y, iHeight);
			int iMaxCol   = min(m_location.x + m_size.cx, iWidth);
			int iMaxRow   = min(m_location.y + m_size.cy, iHeight);

			ASSERT(iStartCol >= 0);
			ASSERT(iStartRow >= 0);

			for (UINT n = 0; n < nMapSize; n++)
				*pTile++ = NO_TILE;

			pTile = piTiles;
			m_nSelected = 0;

			for (int iRow = iStartRow; iRow < iMaxRow; iRow++)
			{
				UINT nSrcIndex = (iRow - m_location.y) * m_size.cx + (iStartCol - m_location.x);
				UINT nDstIndex = iRow * iWidth + iStartCol;
				for (int iCol = iStartCol; iCol < iMaxCol; iCol++)
				{
					int iTile = m_piTiles[nSrcIndex++];
					pTile[nDstIndex++] = iTile;
					if (iTile < 0) m_nSelected++;
				}
			}
			delete [] m_piTiles;
			m_nTileCount = nMapSize;
			m_piTiles = piTiles;
			m_size.cx = iWidth;
			m_size.cy = iHeight;
			m_location.x = 0;
			m_location.y = 0;
		}
	}
	m_pMap = pMap;
}

CRect CTileLayer::GetMinRect()
{
	CRect rect(0,0,-1,-1);
	int *pTile = m_piTiles;

    for (int iRow = 0; iRow < m_size.cy; iRow++)
	{
		for (int iCol=0; iCol < m_size.cx; iCol++)
		{
			if (*pTile++)
			{
				if (rect.right < 0 || iCol < rect.left)
					rect.left = iCol;
				if (iCol > rect.right)
					rect.right = iCol;

				if (rect.bottom < 0) 
                    rect.top = iRow;
				rect.bottom = iRow;
			}
		}
	}
	if (rect.right > 0 && rect.bottom > 0)
	{
		rect.right += 1;
		rect.bottom += 1;
	}
	else
	{
		rect.right = rect.bottom = 0;
	}

	rect.top += m_location.y;
	rect.bottom += m_location.y;
	rect.left += m_location.x;
	rect.right += m_location.x;
	return rect;
}

void CTileLayer::ClearRedo()
{
	while (!m_redo.IsEmpty())
	{
		CTileUndo *pUndo = m_redo.RemoveHead();
		delete pUndo;
	}
}

void CTileLayer::ClearUndo()
{
	ClearRedo();
	while (!m_undo.IsEmpty())
	{
		CTileUndo *pUndo = m_undo.RemoveHead();
		delete pUndo;
	}	
}

// Note: this method assumes that all views of the map share the same active
// layer. This is kind of a shame; 
void CTileLayer::Activate(BOOL bRefresh)
{
	CMapFrame *pFrame = GetParentFrame();
	if (pFrame)
		pFrame->InstallToolPane(RUNTIME_CLASS(CTileSetView), 
		                        theApp.m_pTileSetTemplate, GetTileSet(), bRefresh);
}

void CTileLayer::BeginEdit()
{
	// create a new undo level -- for now, let's keep it unlimited.
	CTileUndo *pUndo = new CTileUndo;
	ASSERT_NEW(pUndo);
    m_undo.AddHead(pUndo);

	// get rid of the previous redo, 
	// can only use redo immediately after undo
	ClearRedo(); 
	if (g_bPlaceWithAttributes)
		GetMap()->BeginEditAttributes();
}

void CTileLayer::EndEdit()
{
  if (!m_undo.IsEmpty())
  {
	  CTileUndo *pUndo = m_undo.GetHead();
	  if (pUndo->IsEmpty())
	  {
		  m_undo.RemoveHead();
		  delete pUndo;
	  }
	  if (g_bPlaceWithAttributes)
		  GetMap()->EndEditAttributes();
  }
}

void CTileLayer::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !m_undo.IsEmpty() && !m_undo.GetHead()->IsEmpty() );
}

void CTileLayer::DoUndoRedo(CTileUndoList& src, CTileUndoList& dst)
{
	ASSERT(!src.IsEmpty());
	CTileUndo *pUndo = src.RemoveHead();

	POSITION pos = pUndo->GetStartPosition();
	int *pTile, iTile;

	SelectNone();
	while (pos != NULL)
	{
		pUndo->GetNextAssoc(pos,pTile,iTile);
		pUndo->SetAt(pTile,*pTile); // save for redo
		*pTile = iTile;
	}
	CRect rect = pUndo->GetRect();
	LayerToMapRect(rect);
	Invalidate(rect);
	dst.AddHead(pUndo);
}

void CTileLayer::OnEditUndo() 
{
	DoUndoRedo(m_undo, m_redo);
	if (g_bPlaceWithAttributes)
		GetMap()->UndoAttributes();
}

void CTileLayer::LayerToMapRect(CRect& rect) 
{
	CPoint p1 = m_pMap->GetTileOffset(rect.top + m_location.y, rect.left + m_location.x);
	CPoint p2 = m_pMap->GetTileOffset(rect.bottom + m_location.y, rect.right + m_location.x);
	rect.SetRect(p1.x,p1.y,p2.x,p2.y);
}

void CTileLayer::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !m_redo.IsEmpty() && !m_redo.GetHead()->IsEmpty() );
}

void CTileLayer::OnEditRedo() 
{
	DoUndoRedo(m_redo, m_undo);
	if (g_bPlaceWithAttributes)
		GetMap()->RedoAttributes();
}



void CTileLayer::OnUpdateEditUpdateAttributes(CCmdUI* pCmdUI) 
{
	CTileSet *pTileSet = GetTileSet();
	pCmdUI->Enable(pTileSet && pTileSet->HasAttributes() && IsSelected());
}

void CTileLayer::OnEditUpdateAttributes() 
{
	CMapEditorDoc *pMap = GetMap();

#if 1
	// TBD: this could get rather tiresome; presumably the user already
	// resolved the attribute conflicts when they first loaded/used the 
	// current tileset; on the other hand, simultaneously loading different
	// maps may have updated the tileset so we may need to resolve conflicts.
	if (!pMap->ResolveAttributeConflicts(GetTileSet())) 
		return;
#endif

    pMap->BeginEditAttributes();  // so this operation can be undone
    if (m_nSelected)
    {
	   int *pTile = m_piTiles;
	   for (int iRow = 0; iRow < m_size.cy; iRow++)
	   {
		   for (int iCol = 0; iCol < m_size.cx; iCol++,pTile++)
		   {
			   if (*pTile < 0) 
				   pMap->SetAttributes(iRow,iCol,-(*pTile)-1);
		   }
	   }
    }
	pMap->EndEditAttributes();
	SelectNone(); // so the user knows the attributes have been updated
}

void CTileLayer::DoIncrementDecrement(BOOL bDecrement)
{
   ASSERT(GetTileSet() != NULL);
   int iAmount = 1;
   int iMaxTile = GetTileSet()->GetTileCount() -1;
   if ((iMaxTile > 1) && (GetAsyncKeyState(VK_CONTROL) & 0x8000))
   {
	   CString string;
	   VERIFY(string.LoadString(bDecrement ? IDS_GETDECREMENT : IDS_GETINCREMENT));
       CNumberDlg dlg(string,1,1,iMaxTile);
	   if (dlg.DoModal() == IDOK)
	   {
		   iAmount = dlg.m_iNumber;
	   }
   }
   if (bDecrement) 
	   iAmount = -iAmount;

   BeginEdit();
   CTileUndo *pUndo = GetCurrentUndo();
   int *pTile = m_piTiles;
   CRect rect = GetSelection();
   iMaxTile = -iMaxTile;  // because we're dealing with negative tile values

   for (int iRow = 0; iRow < m_size.cy; iRow++)
   {
	   for (int iCol = 0; iCol < m_size.cx; iCol++, pTile++)
	   {
		   if (*pTile < 0)
		   {
			  if (pUndo)
				  pUndo->SetAt(iRow, iCol, pTile, -(*pTile));
			  *pTile -= iAmount;  // subtract because we're dealing with negative tile values
			  if (*pTile < iMaxTile) 
				 *pTile = iMaxTile;
			  else if (*pTile >= 0)
				  *pTile = -1;
		   }
	   }
   }
   SetModifiedFlag();
   Invalidate(rect);
   EndEdit();
   
}

void CTileLayer::OnIncrementSelection() 
{
   DoIncrementDecrement(FALSE);
	
}

void CTileLayer::OnDecrementSelection() 
{
   DoIncrementDecrement(TRUE);
}

void CTileLayer::OnEditRandomize() 
{
   CWaitCursor wait;
   CTileSet *pTileSet = GetTileSet();
   BOOL bSelected = IsSelected();
   CSize size = m_size;
   CString sMsg;
   
   if (IDCANCEL == AfxMessageBox((bSelected) ? IDS_RANDSEL : IDS_RANDALL, 
	   MB_OKCANCEL|MB_ICONQUESTION, -1))
	   return;

   ASSERT(pTileSet != NULL);
   ASSERT(GetMap());
   
   srand( time(NULL) );
   BeginEdit();
   CTileUndo *pUndo = GetCurrentUndo();
   int *pTile = m_piTiles;
   int iTile,iCount;

   CTileGroup *pGroup = pTileSet->GetCurrentGroup();
   CCategory *pCategory = NULL;

   if (pGroup != NULL)
	   size = pGroup->GetSize();
   else 
   {
	   ASSERT(pTileSet->m_iCurrentType == TSV_TILES);
       CTileSetView *pView = DYNAMIC_DOWNCAST(CTileSetView, GetParentFrame()->GetToolView());
       if (pView && pView->m_iCurrentView == TSV_TILES && pView->m_iTileCategory) 
		   pCategory = pTileSet->GetTileCategory(pView->m_iTileCategory-1);
	   if (pCategory)
		   iCount = pCategory->GetItemCount();
	   else
		   iCount = pTileSet->GetTileCount();
   }
   for (int iRow=0; iRow < m_size.cy; iRow++)
   {
	   for (int iCol=0; iCol < m_size.cx; iCol++,pTile++)
	   {
		   if (bSelected && (*pTile > 0)) // if there are selected tiles
			   continue;  // don't change unselected tiles

		   if (pGroup)
		   {
			   int ic = rand() % size.cx;
			   int ir = rand() % size.cy;
			   iTile = pGroup->GetTile(ir,ic);
			   if (iTile < 0)  // if the random tile is vacant
				   continue; // don't change the current tile
		   }
		   else 
		   {
			   // choose a random item from the current category or tileset
			   iTile = rand() % iCount;
			   if (pCategory) 
					iTile = pCategory->GetItemAt(iTile);
		   }

		   if (pUndo)
			   pUndo->SetAt(iRow, iCol, pTile, abs(*pTile));

		   if (g_bPlaceWithAttributes)
				m_pMap->SetAttributes(iRow,iCol,iTile);

		   ++iTile;
		   if (bSelected)
		   {
			   iTile = -iTile; // so tile stays selected
			   if (*pTile == NO_TILE) 
				   m_nSelected += 1; // we're adding tiles
		   }
		   *pTile = iTile;
	   }
   }
   EndEdit();
   CRect rect;
   if (bSelected)
   {
	   rect = GetSelection();
   }
   else
   {
	   size = m_pMap->GetSize();
	   rect.SetRect(0,0,size.cx,size.cy);
   }
   Invalidate(rect);
   SetModifiedFlag();
}

void CTileLayer::OnUpdateEditRandomize(CCmdUI* pCmdUI) 
{
	CTileSet *pTileSet = GetTileSet();
	pCmdUI->Enable(pTileSet && (pTileSet->GetCurrentGroup() || pTileSet->m_iCurrentType == TSV_TILES));
}

void CTileLayer::MoveItem(CPoint point, int iRow, int iColumn)
{
	if (IsSelected() && m_movelast.x != -1)
	{
		CRect rectOld;
		CRect rectNew;
		CTileSet *pTileSet = GetTileSet();
		int iNewCol, iOldCol, iNewRow, iOldRow;
		GetRowColumn(point, iNewRow, iNewCol, TRUE);
		GetRowColumn(m_movelast, iOldRow, iOldCol, TRUE);
		if(iNewCol != iOldCol || iNewRow != iOldRow)
		{
			rectOld = GetSelection();
			int iX = iNewCol - iOldCol;
			int iY = iNewRow - iOldRow;
			rectNew = rectOld;
			rectNew.left += iX*pTileSet->m_iTileWidth;
			rectNew.right = m_iOldWidth + rectNew.left;
			rectNew.top += iY*pTileSet->m_iTileHeight;
			rectNew.bottom = m_iOldHeight + rectNew.top;
			SelectNone();
			Select(rectNew, TRUE);
		}
	}
	else
	{
		CRect old;
		old = GetSelection();
		m_iOldWidth = old.Width();
		m_iOldHeight = old.Height();
	}
	m_movelast = point;
}
