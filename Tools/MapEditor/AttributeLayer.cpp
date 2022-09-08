#include "stdafx.h"
#include "MapEditor.h"
#include "MapFrame.h"
#include "MapEditorView.h"
#include "AttributeLayer.h"
#include "AttributeView.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "ComputeLayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////

#define ATTRIBUTE_HASH_SIZE 101

class CAttributeUndo
{
	protected:

	CRect m_rect;
	CMap<ATTRIBUTE_BASE_TYPE *, ATTRIBUTE_BASE_TYPE *, ATTRIBUTE_BASE_TYPE, ATTRIBUTE_BASE_TYPE> m_data;

public:
	CAttributeUndo()
	{
		m_rect.SetRectEmpty();
		m_data.InitHashTable(ATTRIBUTE_HASH_SIZE);
	}
	~CAttributeUndo()
	{
		m_data.RemoveAll();
	}
    BOOL IsSet(ATTRIBUTE_BASE_TYPE *pValuePtr)
	{
		ATTRIBUTE_BASE_TYPE value;
		return m_data.Lookup(pValuePtr,value);
	}
	void SetAt(int iRow, int iColumn, ATTRIBUTE_BASE_TYPE *pValuePtr, ATTRIBUTE_BASE_TYPE value)
	{
		CRect newRect = CRect(CPoint(iColumn,iRow),CPoint(iColumn+1,iRow+1));
		m_rect.UnionRect(m_rect,newRect);
		m_data.SetAt(pValuePtr, value);
	}
	void SetAt(ATTRIBUTE_BASE_TYPE *pValuePtr, ATTRIBUTE_BASE_TYPE value) 
	{	
		m_data.SetAt(pValuePtr, value); 
	}
	BOOL IsEmpty() const 
	{ 
		return m_data.IsEmpty(); 
	}
	POSITION GetStartPosition() const 
	{
		return m_data.GetStartPosition(); 
	}
	void GetNextAssoc( POSITION& rNextPosition, ATTRIBUTE_BASE_TYPE *& rKey, ATTRIBUTE_BASE_TYPE& rValue ) const
	{
		m_data.GetNextAssoc(rNextPosition, rKey, rValue);
	}
	CRect GetRect() const
	{
		return m_rect;
	}
};

/////////////////////////////////////////////////////////////////////////////

/*
** Notes: 
**    1. Internally a AttributeLayer uses 0 to mean no attribute, negative numbers to
**	     mean a selected attribute, and positive numbers to mean a non-selected attribute.
**       When the layer is serialized to disk, we just store the actual zero-based
**       attribute value.
**
**    2. In memory an AttributeLayer is always the same size as the map.  
*/
#define NO_ATTRIBUTE 0    

/////////////////////////////////////////////////////////////////////////////
// CAttributeLayer construction/destruction

#define ATTROBJ_HASH_SIZE 31  // some small prime number 

void CAttributeLayer::InitAttributeLayer(int nBitCount, int nDefaultValue, int iWidth, int iHeight)
{
	m_eColorType = EAttrSolid;
	m_pTileLayer = NULL;
	m_bUpdateTiles = FALSE;
	m_bUpdateDefault = FALSE;
	m_bShowObjectAttributes = FALSE;
   	m_color = RGB(0,0,0);

	SetBitCount(nBitCount);
	SetDefaultValue(nDefaultValue);
	m_currentValue = nDefaultValue;

	m_pData = NULL;
	SetSize(iWidth,iHeight);

	m_bValidObjectMap = TRUE; // false just after serialization
	m_objectMap.InitHashTable(ATTROBJ_HASH_SIZE);
	m_attrOverrides.InitHashTable(ATTROBJ_HASH_SIZE);
}

CAttributeLayer::CAttributeLayer() 
{
	InitAttributeLayer(0,0,0,0);
}


CAttributeLayer::~CAttributeLayer()
{
  TRACE("Deleting attribute layer %s\n",GetTitle());

  ClearUndo();
  delete [] m_pData;

  m_objectMap.RemoveAll();
}

 
void CAttributeLayer::SetSize(int iWidth, int iHeight)
{
	ASSERT(iWidth >= 0);
	ASSERT(iHeight >= 0);
	ASSERT(m_pData == NULL);
	ASSERT(m_nBitCount >= 0 && m_nBitCount <= MAX_ATTRIBUTE_BITS);

	m_size.cy = iHeight;
	m_size.cx = iWidth;
	m_nAttributeCount = iWidth * iHeight;
	m_nSelected = 0;

	if (m_nAttributeCount > 0)
	{
		m_pData = new ATTRIBUTE_BASE_TYPE[ m_nAttributeCount * sizeof(ATTRIBUTE_BASE_TYPE)];
		ASSERT_NEW(m_pData);
	}
}

void CAttributeLayer::FillLayer(int iValue)
{
	ASSERT(iValue >= (0-m_maxValue) && iValue <= m_maxValue);
	ATTRIBUTE_BASE_TYPE value = (ATTRIBUTE_BASE_TYPE)(iValue + 1);
	ATTRIBUTE_BASE_TYPE *pValue = m_pData;
	for (UINT n=0; n < m_nAttributeCount; n++)
	{
		*pValue++ = value;
	}
	m_nSelected = 0;
}

 
CAttributeLayer::CAttributeLayer(CMapEditorDoc *pMap, LPCSTR lpszTitle, UINT nBitCount, int defaultValue)
{
	InitAttributeLayer(nBitCount, defaultValue, pMap->m_iMapWidth, pMap->m_iMapHeight);
    SetTitle(lpszTitle);
	FillLayer(m_defaultValue);
	SetMap(pMap);
}

void CAttributeLayer::SetShowObjectAttributes(BOOL bShowThem)
{
	if (bShowThem != m_bShowObjectAttributes)
	{
		m_bShowObjectAttributes = bShowThem;
		if (m_objectMap.GetCount()) 
			Invalidate(NULL);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CAttributeLayer Serialization
IMPLEMENT_SERIAL(CAttributeLayer , CMapLayer, (VERSIONABLE_SCHEMA | 4))

void CAttributeLayer::Serialize(CArchive& ar) 
{
	// since attribute layers are used dynamically we can skip the
	// PUT_SAFE_SCHEMA/GET_SAFE_SCHEMA
    UINT nSchema;
	
	if (ar.IsLoading())
		nSchema = ar.GetObjectSchema();

	CMapLayer::Serialize(ar);
	CAttribute::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_color;
		ar << m_currentValue;
        ar << m_size.cx;
		ar << m_size.cy;
		ar.Write(m_pData,m_nAttributeCount * sizeof(ATTRIBUTE_BASE_TYPE));
		ar << (int)m_eColorType;  // schema >= 2

		// write out the object table by brute force: schema >= 3
		CMapEditorDoc *pDoc = GetMap();
		if (pDoc && m_bValidObjectMap)
		{
			int iCount = m_objectMap.GetCount();
			int iObject;
			ATTRIBUTE_BASE_TYPE iValue;
			CMapObjectInst *pInstance;

			ar << iCount;
			POSITION pos = m_objectMap.GetStartPosition();
			while (pos != NULL)
			{
				m_objectMap.GetNextAssoc(pos,pInstance,iValue);
				ASSERT(pInstance != NULL);
				iObject = pDoc->GetObjectIndex(pInstance);
                ASSERT(iObject >= 0);
                ar << iObject;
				ar << iValue;
				--iCount;
			}
			ASSERT(iCount == 0);
		}
		else
		{
			ar << (int)0;
		}

		ar << m_bShowObjectAttributes; // schema >= 4
	}
	else 
	{
		ar >> m_color;
		ar >> m_currentValue;
        ar >> m_size.cx;
		ar >> m_size.cy;
		SetSize(m_size.cx, m_size.cy);
		ar.Read(m_pData, m_nAttributeCount * sizeof(ATTRIBUTE_BASE_TYPE));
		if (nSchema >= 2)
		{   int iColorType;
		    ar >> iColorType;
			m_eColorType = (CAttrColorType)iColorType;
		}
		else
			m_eColorType = EAttrSolid;

		if (nSchema >= 3)
		{
			int iCount, iObject;
			ATTRIBUTE_BASE_TYPE iValue;
			ar >> iCount;
			m_objectMap.RemoveAll(); 
			m_bValidObjectMap = (iCount <= 0);

			for (int i=0; i < iCount; i++)
			{
                ar >> iObject;
				ASSERT(!m_objectMap.Lookup((CMapObjectInst *)iObject,iValue));
				ar >> iValue;
				m_objectMap.SetAt((CMapObjectInst *)iObject,iValue);
			}
		}

		if (nSchema >= 4)
		{
			ar >> m_bShowObjectAttributes;
		}
	}

}

/*
** METHOD
**   CAttributeLayer::ValidateObjectMap
**
** DESCRIPTION
**   if the current objectMap is not valid, replaces each object
**   id stored in m_objectMap with a pointer to the actual
**   CMapObjectInst.  This function must be called after all the 
**   layers have been loaded in from disk, all the CMapObjectInst
**   are allocated, and before any new CMapObjectInst are allocated.
*/
void CAttributeLayer::ValidateObjectMap() 
{
	if (!m_bValidObjectMap)
	{	
		POSITION pos = m_objectMap.GetStartPosition();
		CMapObjectInst *pObject,*pInstance;
		ATTRIBUTE_BASE_TYPE iValue;
		CMapEditorDoc *pMap = GetMap();
		ASSERT(pMap != NULL);
		CMap<CMapObjectInst *,CMapObjectInst *,ATTRIBUTE_BASE_TYPE,ATTRIBUTE_BASE_TYPE> newMap;
        newMap.InitHashTable(ATTROBJ_HASH_SIZE);
		while (pos != NULL)
		{
			m_objectMap.GetNextAssoc(pos,pObject,iValue);
			pInstance = pMap->GetObjectInstance((int)pObject);
			ASSERT(pInstance != NULL);
#ifdef _DEBUG
			ATTRIBUTE_BASE_TYPE iTemp;
            ASSERT(!newMap.Lookup(pInstance,iTemp));
#endif
			newMap.SetAt(pInstance,iValue);
		}
		m_objectMap.RemoveAll();
		m_objectMap.InitHashTable(ATTROBJ_HASH_SIZE);
		while (pos = newMap.GetStartPosition())
		{
			newMap.GetNextAssoc(pos,pInstance,iValue);
			m_objectMap.SetAt(pInstance,iValue);
			VERIFY(newMap.RemoveKey(pInstance));
		}
		m_bValidObjectMap = TRUE;
	}
}
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CAttributeLayer , CMapLayer)
	//{{AFX_MSG_MAP(CAttributeLayer)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCutCopy)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_DOWN, OnDecrementAttribute)
	ON_COMMAND(ID_UP, OnIncrementAttribute)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMTYPE, OnUpdateItemType)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMID,	OnUpdateItemId)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMINFO, OnUpdateItemInfo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCutCopy)
	ON_COMMAND(ID_LEFT, OnDecrementAttribute)
	ON_COMMAND(ID_RIGHT, OnIncrementAttribute)
	ON_COMMAND(ID_LAYERS_COMPUTE, OnLayersCompute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttribute diagnostics

#ifdef _DEBUG

void CAttributeLayer::AssertValid() const
{
	CMapLayer::AssertValid();
	CAttribute::AssertValid();

	if (m_pMap)
	{
		// for now we require that the layer fill the entire map but
		// this may not be necessary in the future.
		ASSERT(m_size.cx == m_pMap->m_iMapWidth);
		ASSERT(m_size.cy == m_pMap->m_iMapHeight);
	}
	//ASSERT(m_nSelected >= 0 && m_nSelected <= m_nAttributeCount);
	ASSERT(m_size.cx >= 0 && m_size.cy >= 0);
	ASSERT(m_nAttributeCount == ((UINT)m_size.cx * (UINT)m_size.cy));

	if (m_nAttributeCount)
		ASSERT(m_pData != NULL); // TBD: check size of allocation
	else
		ASSERT(m_pData == NULL);

	ASSERT(m_defaultValue >= (0-m_maxValue) && m_currentValue <= m_maxValue);

	UINT selectedCount = 0;
	ATTRIBUTE_BASE_TYPE *pValue = m_pData;
	for (UINT n=0; n < m_nAttributeCount; n++)
	{
		ASSERT(abs(*pValue) <= (m_maxValue + 1));
		if (*pValue++ < 0)
		{
			++selectedCount;
		}
	}
	//ASSERT(selectedCount == m_nSelected);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////
// Implementation
inline ATTRIBUTE_BASE_TYPE *CAttributeLayer::GetAttributePointer(int iRow,int iColumn)
{
    ASSERT(iRow >= 0 && iRow < m_size.cy);
    ASSERT(iColumn >= 0 && iColumn < m_size.cx);
	return &m_pData[iRow * m_size.cx + iColumn];
}

/*
** METHOD
**    CAttributeLayer::SetAttribute
**
** PARAMETERS
**     int iRow         -- row position of attribute within this layer
**     int iColumn      -- column position of attribute within this layer
**     int iValue       -- zero-based value of attribute
**     CAttributeUndo *pUndo -- optional pointer to current undo level
**
** DESCRIPTION:
**     stores the given attribute-value in the given row,column position
**     in this attribute layer.  If pUndo is non-NULL, records the
**     old attribute value if it wasn't already present.
*/
ATTRIBUTE_BASE_TYPE *CAttributeLayer::SetAttribute(int iRow, int iColumn, int iValue, CAttributeUndo *pUndo)
{
	ASSERT(iValue >= (0-m_maxValue) && iValue <= m_maxValue);
    ATTRIBUTE_BASE_TYPE *pValue = GetAttributePointer(iRow,iColumn);
	if (pUndo && !pUndo->IsSet(pValue))
	{
		pUndo->SetAt(iRow,iColumn,pValue,abs(*pValue));
	}
	// Note: update the m_nSelected and the attribute after recording the
	// undo in case the undo throws a memory exception.
	if (*pValue < 0) m_nSelected -= 1;
	*pValue = (ATTRIBUTE_BASE_TYPE)(iValue + 1); 
	return pValue;
}

/*
** METHOD
**    CAttributeLayer::GetAttribute
**
** PARAMETERS
**     int iRow     -- row position of attribute within this layer
**     int iColumn  -- column position of attribute within this layer
**
** DESCRIPTION:
**     returns the attribute stored at the given row,column position in
**     this layer. Doesn't use or return overridden attribute values.
**
*/
int CAttributeLayer::GetAttribute(int iRow, int iColumn)
{
	ATTRIBUTE_BASE_TYPE *pValue = GetAttributePointer(iRow,iColumn);
	return (int)abs(*pValue)-1;
}
 
/*
** METHOD
**    CAttributeLayer::GetAttribute
**
** PARAMETERS
**     int iRow                -- row position of attribute within this layer
**     int iColumn		       -- column position of attribute within this layer
**     ATTRIBUTE_FLAGS *pFlags      -- non-null pointer for attribute position flags 
**     BOOL bUseOverrides      -- TRUE to use the attribute overrides table
**
** DESCRIPTION:
**     returns the attribute stored at the given row,column position in
**     this layer.  If bUseOverrides is TRUE and the given position has
**     an overridden attribute value, returns the overridden value instead.
**      
*/
int CAttributeLayer::GetAttribute(int iRow, int iColumn, ATTRIBUTE_FLAGS *pFlags, BOOL bUseOverrides)
{
	ASSERT(pFlags != NULL);
	ATTRIBUTE_BASE_TYPE *pValue = GetAttributePointer(iRow,iColumn);
    ATTRIBUTE_BASE_TYPE iTmpValue, iValue = *pValue;
	if (iValue < 0)
	{
		*pFlags = ATTRIBUTE_SELECTED;
		iValue = -iValue;
	}
	else
		*pFlags = 0;
	iValue -= 1;

	if (bUseOverrides && m_attrOverrides.Lookup(pValue,iTmpValue))
	{
		iValue = iTmpValue;
		*pFlags |= ATTRIBUTE_OVERRIDDEN;
	}
	return iValue;
}


/*
** PARAMETERS
**     int iRow     -- row position of attribute within this layer
**     int iColumn  -- column position of attribute within this layer
*/
BOOL CAttributeLayer::SelectAttribute(int iRow, int iColumn, BOOL bSelected)
{
	ATTRIBUTE_BASE_TYPE *pValue = GetAttributePointer(iRow,iColumn);
	ATTRIBUTE_BASE_TYPE iValue = *pValue;
	if (bSelected)
	{
		if (iValue > 0)
		{
			*pValue = - iValue;
			m_nSelected += 1;
			return TRUE;
		}
	}
	else
	{
		if (iValue < 0)
		{
			*pValue = - iValue;
			m_nSelected -= 1;
			return TRUE;
		}
	}
	return FALSE;
}

/*
** METHOD
**    CAttributeLayer::CropToSelection
**
** PARAMETERS
**    CRect rect            -- normalized cropping area (in pixels)
**    BOOL bSelectedOnly    -- true if only selected items within area should be copied
**
** DESCRIPTION
**    creates and returns a NEW layer just large enough to cover the given
**    rectangle.  If bSelectedOnly, copies only those attributes in the cropped
**    area that are currently selected all other values are set to the default
**    attribute value for this layer. If bSelectedOnly is FALSE, copies all attributes 
**    in the cropped area.
**
**    NOTE: this function DOES NOT set the new layers' map 
**/
 
CMapLayer *CAttributeLayer::CropToSelection(CRect rect, int iStartRow, int iStartCol, int iEndRow, int iEndCol, BOOL bSelectedOnly)
{
	CTileSet *pTileSet = GetTileSet();
	if (pTileSet == NULL)
		return NULL;

	CSize tileSize = pTileSet->GetTileSize();

#ifdef _DEBUG
	CMapLayer::CropToSelection(rect,iStartRow,iStartCol,iEndRow,iEndCol,bSelectedOnly);  // verify pre-conditions
#endif

	CAttributeLayer *pLayer = new CAttributeLayer;
	ASSERT_NEW(pLayer);

	ATTRIBUTE_FLAGS flags;
	pLayer->SetSize(rect.Width() / tileSize.cx, rect.Height() / tileSize.cy);
	pLayer->SetTitle(m_pszTitle);
	pLayer->SetBitCount(m_nBitCount);
	VERIFY(pLayer->SetDefaultValue(m_defaultValue));
	VERIFY(pLayer->SetCurrentValue(m_currentValue));
	pLayer->FillLayer(m_defaultValue);
    pLayer->m_color = m_color;

	for (int iRow = iStartRow; iRow < iEndRow; iRow++)
	{
		for (int iCol = iStartCol; iCol < iEndCol; iCol++)
		{
			if (iEndRow > m_size.cy && iRow < (iEndRow-m_size.cy))
			{
				pLayer->SetAttribute(iRow-iStartRow,iCol-iStartCol,m_defaultValue);
				continue;
			}
			if (iEndCol > m_size.cx && iCol < (iEndCol-m_size.cy))
			{
				pLayer->SetAttribute(iRow-iStartRow,iCol-iStartCol,m_defaultValue);
				continue;
			}
			int iValue = GetAttribute((iEndRow > m_size.cy) ? iRow-(iEndRow-m_size.cy) : iRow, 
				(iEndCol > m_size.cx) ? iCol-(iEndCol-m_size.cx) : iCol, &flags, FALSE);
			if (bSelectedOnly && !(flags & ATTRIBUTE_SELECTED))
				iValue = (int)m_defaultValue;
			pLayer->SetAttribute(iRow-iStartRow,iCol-iStartCol,iValue);
		}
	}
	pLayer->m_bVisible = m_bVisible;
	return pLayer;
}

/*
** PARAMETERS
**     int iRow     -- row position of attribute within this layer
**     int iColumn  -- column position of attribute within this layer
*/
 
BOOL CAttributeLayer::ToggleAttribute(int iRow, int iColumn)
{
	ATTRIBUTE_BASE_TYPE *pValue = GetAttributePointer(iRow,iColumn);
	BOOL bSelected;

	*pValue = - (*pValue);
	if (*pValue < 0)
	{
		++m_nSelected;
		bSelected=TRUE;
	}
	else
	{
		--m_nSelected;
		bSelected=FALSE;
	}
	InvalidateLayer(iRow,iColumn); // after updating m_nSelected
	return bSelected;
}





//////////////////////////////////////////////////////////////////////
// Message handlers
 
void CAttributeLayer::SelectNone() 
{
   if (m_nSelected)
   {
	   ATTRIBUTE_BASE_TYPE *pValue = m_pData;

	   CRect rect = GetSelection();
	   for (UINT i=0; i < m_nAttributeCount; i++,pValue++)
	   {
		   if (*pValue < 0) 
			  *pValue = - *pValue;
	   }
	   m_nSelected = 0;
	   Invalidate(rect);
   }
}

 
void CAttributeLayer::OnEditSelectAll() 
{
   ATTRIBUTE_BASE_TYPE *pValue = m_pData;
   for (UINT i=0; i < m_nAttributeCount; i++,pValue++)
   {
	   if (*pValue > 0) 
		   *pValue = - (*pValue);
   }
   m_nSelected = m_nAttributeCount;
   Invalidate(NULL);
}	

 
void CAttributeLayer::OnUpdateEditCutCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsSelected());
}
 
void CAttributeLayer::DoCutCopy(BOOL bCut)
{
	if (OpenClipboard())
	{
		EmptyClipboard();
		TRY
		{
			CSharedFile	memFile;
			CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);

			ASSERT(m_nSelected > 0);
			CRect group = GetSelectionGroup();
			ar << group.Width();
			ar << group.Height();
			CAttributeUndo *pUndo;

			if (bCut) 
			{
				BeginEdit();
				pUndo = GetCurrentUndo();
			}
			TRY
			{
				ATTRIBUTE_FLAGS flags;
				for (int iRow = group.top; iRow < group.bottom; iRow++)
				{
					for (int iCol = group.left; iCol < group.right; iCol++)
					{
						int iVal = GetAttribute(iRow,iCol,&flags);
						if (flags & ATTRIBUTE_SELECTED)
						{
							ar << iVal;
							if (bCut) SetAttribute(iRow, iCol, m_defaultValue, pUndo);
						}
						else
							ar << -1;
					}
				}
			}
			END_TRY
			if (bCut)
			{		
				EndEdit();
				Invalidate(group.top,group.left,group.bottom,group.right);
				SetModifiedFlag();
			}

			ar.Flush();

			HGLOBAL hData = memFile.Detach();
			::SetClipboardData(g_nAttributeLayerFormat, hData);
			CloseClipboard();
		}
		CATCH_ALL(E)
		{
			CloseClipboard();
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	else
		AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
}


void CAttributeLayer::OnEditCut()
{
	DoCutCopy(TRUE);
}

void CAttributeLayer::OnEditCopy()
{
	DoCutCopy(FALSE);
}
 
void CAttributeLayer::InvalidateLayer(int iRow, int iColumn)
{
	ASSERT(iRow >= 0 && iRow < m_size.cy);
	ASSERT(iColumn >= 0 && iColumn < m_size.cx);
	CMapLayer::Invalidate(iRow, iColumn);
}

///////////////////////////////////////////////////////////////////////////
/*
** METHOD
**   CAttributeLayer::GetSelectionGroup
**
** DESCRIPTION
**    returns the bounding box (in attribute rows/columns) of the current selection
**    Note: the bottom right corner of the box is the bottom right
**    corner of the bottom right attribute selected.  If no attributes are
**    selected, the rectangle returned will be empty.
**   
*/
CRect CAttributeLayer::GetSelectionGroup()
{
	int iMinRow = m_size.cy;
	int iMinCol = m_size.cx;
	int iMaxRow = -1;
	int iMaxCol = -1;
    ATTRIBUTE_BASE_TYPE *pValue = m_pData;
	CRect rect;

	if (m_nSelected > 0)
	{
		for (int iRow = 0; iRow < m_size.cy; iRow++)
		{
			for (int iCol = 0; iCol < m_size.cx; iCol++, pValue++)
			{
				if (*pValue < 0)
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
	}
	else
		rect.SetRectEmpty();
	return rect;
}

/*
** METHOD
**   CAttributeLayer::GetSelection
**
** DESCRIPTION
**    returns the bounding box (in map coordinates) of the current selection
**    Note: the bottom right corner of the box is the bottom right
**    corner of the bottom right attribute selected.  If no attributes are
**    selected, the rectangle returned will be empty.
**   
*/
CRect CAttributeLayer::GetSelection()
{
    CRect rect = GetSelectionGroup();
	if (m_pMap)
	   LayerToMapRect(rect);
	return rect;
}

 
void CAttributeLayer::Select(CRect rect, BOOL bSelected)
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
			bModified |= SelectAttribute(iRow, iCol, bSelected);
		}
	}
	if (bModified)
	{
		Invalidate(iStartRow,iStartCol,iEndRow,iEndCol);
	}
}


void CAttributeLayer::UpdateOverrides()
{
	m_attrOverrides.RemoveAll();
	if (m_pMap && m_bShowObjectAttributes)
	{
		CPoint hotSpot;
		ASSERT_VALID(m_pMap);
		POSITION pos = m_pMap->GetFirstLayer();
		ATTRIBUTE_BASE_TYPE iValue;
        while (pos != NULL)
		{
			CObjectLayer *pObjectLayer = DYNAMIC_DOWNCAST(CObjectLayer, m_pMap->GetNextLayer(pos));
			if (pObjectLayer)
			{
				POSITION opos = pObjectLayer->GetFirstObjectPosition();
				while (opos != NULL)
				{
					CMapObjectInst *pObject = pObjectLayer->GetNextObject(opos);
					if (m_objectMap.Lookup(pObject, iValue))
					{
						int iRow, iColumn;
						hotSpot = pObjectLayer->GetHotSpot(pObject);
						m_pMap->GetRowColumn(hotSpot,iRow,iColumn);
						m_attrOverrides.SetAt(GetAttributePointer(iRow,iColumn),iValue);
					}
				}
			}
		}
	}
}

void CAttributeLayer::Draw(HDC hdc, CPoint offset, int iStartRow, int iStartCol,
	int iEndRow, int iEndCol)
{

	CTileSet *pTileSet = GetTileSet();
	if (pTileSet == NULL || m_pData == NULL)
		return;

	int iTileWidth = pTileSet->m_iTileWidth;
	int iTileHeight = pTileSet->m_iTileHeight;
    CSize selSize(iTileWidth - 1, iTileHeight -1);

    // create an appropriately small font
	int maxChars = GetValueString(m_maxValue).GetLength();
	ASSERT(maxChars >= 1);
	int iFontWidth =  min ( max( ( min(iTileWidth,iTileHeight) - 2 ) / maxChars, 5), 8);

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	ASSERT(hFont != NULL);

	CFont *pFont = CFont::FromHandle(hFont);
	ASSERT(pFont != NULL);

	LOGFONT logfont;
	VERIFY(pFont->GetLogFont(&logfont));
	logfont.lfWidth = iFontWidth; 
    logfont.lfHeight = -MulDiv(iFontWidth, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logfont.lfWeight = FW_NORMAL;
	if (iFontWidth < 8)
		strcpy(logfont.lfFaceName,"Small Fonts");

	HFONT hCustomFont = ::CreateFontIndirect(&logfont);
	if (hCustomFont)
		hFont = (HFONT)SelectObject(hdc, hCustomFont);
    else
		hFont = (HFONT)SelectObject(hdc,hFont);

	UpdateOverrides();

	//TBD: perhaps we should scale the map so the text will always fit.
	HGDIOBJ brush = GetStockObject(NULL_BRUSH);
	HPEN hPen = CreatePen(PS_DOT,0,RGB(0,0,0)); // white is the secondary color when bkmode is opaque 
	HPEN hOverridePen = CreatePen(PS_SOLID,0,m_color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    COLORREF oldColor = GetTextColor(hdc);
	COLORREF overrideColor = m_color;
	int oldBkMode = SetBkMode(hdc, TRANSPARENT);
	if (m_eColorType == EAttrSolid) 
		SetTextColor(hdc, m_color);


	// TBD: if selsize is not even, pDC->Rectangle() will not 
	// draw right/bottom line segments.
	CPoint pt;
	ATTRIBUTE_BASE_TYPE iValue;
	ATTRIBUTE_FLAGS flags;

	pt.y = offset.y;
	for( int iRow = iStartRow; iRow < iEndRow; iRow++ )
	{
		pt.x = offset.x;
		for( int iColumn = iStartCol; iColumn < iEndCol; iColumn++ )
		{
			iValue = GetAttribute(iRow,iColumn,&flags);
			CRect srect(pt,selSize);
			ASSERT(iValue >= 0);
			CString sValueStr = GetValueString(iValue);
			if (m_eColorType != EAttrSolid) 
			{
				BYTE value = (iValue * 255)/max(m_maxValue,1);
				if (m_eColorType == EAttrInvertedGreyscale)
					value = 255 - value;
				COLORREF color = RGB(value,value,value);
				SetTextColor(hdc,color);
				if (color != overrideColor && m_bShowObjectAttributes)
				{
					DeleteObject(hOverridePen);
					hOverridePen = CreatePen(PS_SOLID,0,color);
					overrideColor = color;
				}
			}
			SetBkMode(hdc, TRANSPARENT);
			ExtTextOut(hdc,pt.x+1,pt.y,ETO_CLIPPED, srect, sValueStr, sValueStr.GetLength(), NULL);
			if (hOverridePen && (flags & ATTRIBUTE_OVERRIDDEN) && (iTileWidth > 4 && iTileHeight > 4))
			{
				HPEN oldPen = (HPEN)SelectObject(hdc,hOverridePen);
				MoveToEx(hdc,srect.left+2, srect.bottom-2,NULL);
				LineTo(hdc,srect.right-2,srect.bottom-2);
				SelectObject(hdc,oldPen);
			}
			if (flags & ATTRIBUTE_SELECTED)
			{
				HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
				SetBkMode(hdc, OPAQUE);
				Rectangle(hdc, srect.left, srect.top, srect.right, srect.bottom);
				SelectObject(hdc, oldPen);
			}
			pt.x += iTileWidth; 
		}
		pt.y += iTileHeight; 
	}
	SetBkMode(hdc, oldBkMode);
	SetTextColor(hdc, oldColor);
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, hFont);
	DeleteObject(hPen);
	DeleteObject(hCustomFont);
	DeleteObject(hOverridePen);
}


 
CMapLayerMode CAttributeLayer::GetItem(CPoint point, int iRow, int iColumn)
{
	ATTRIBUTE_FLAGS flags;
	m_currentValue = (ATTRIBUTE_BASE_TYPE) GetAttribute(iRow,iColumn,&flags);
	GetMap()->UpdateAllViews(NULL,MEV_UPDATE_ATTRIBUTE_VALUE);
	UpdateItemPos(iRow,iColumn);
	return none;	
}

 
CMapLayerMode CAttributeLayer::SelectItem(CPoint point, int iRow, int iColumn, BOOL bSelected)
{
	if (SelectAttribute(iRow,iColumn,bSelected))
	{
		UpdateItemPos(iRow,iColumn);
		InvalidateLayer(iRow,iColumn);
	}
	return selectItem; // so we will continue to select/deselect tiles
}

 
CMapLayerMode CAttributeLayer::ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected)
{
	bSelected = ToggleAttribute(iRow,iColumn);
	UpdateItemPos(iRow,iColumn);
	return selectItem; // so we will continue to select/deselect tiles
}

 
CMapLayerMode CAttributeLayer::PlaceItem(CPoint point, int iRow, int iColumn)
{
	CAttributeUndo *pUndo = GetCurrentUndo();
	SetAttribute(iRow, iColumn, m_currentValue, GetCurrentUndo());
	SetModifiedFlag();
	InvalidateLayer(iRow,iColumn);
	UpdateItemPos(iRow,iColumn);

	if (m_pTileLayer)
	{
        int iTile = m_pTileLayer->GetTile(iRow, iColumn);
		if (iTile >= 0)
		{
			if (m_bUpdateDefault)
				GetTileSet()->SetAttribute(GetTitle(), iTile, m_currentValue);
			if (m_bUpdateTiles)
			{
				for (int iRow = 0; iRow < m_size.cy; iRow++)
				{
					for (int iCol = 0; iCol < m_size.cx; iCol++)
					{
						if (m_pTileLayer->GetTile(iRow, iCol) == iTile)
						{
							SetAttribute(iRow, iCol, m_currentValue, pUndo);
							InvalidateLayer(iRow, iCol); // TBD: is this too slow?
						}
					}
				}
			}
		}
	}
	return placeItem;  // so we will continue to draw
}

 
void CAttributeLayer::GetRowColumn(CPoint pt, int& iRow, int& iColumn, BOOL bRoundUp)
{
	// converts the map point to the layer row column, clipping if needed
	GetMap()->GetRowColumn(pt,iRow,iColumn,bRoundUp,TRUE);
}


 
void CAttributeLayer::OnEditFind() 
{
	ATTRIBUTE_BASE_TYPE iValue = (ATTRIBUTE_BASE_TYPE)(m_currentValue + 1);
	SelectNone();

	ATTRIBUTE_BASE_TYPE *pValue = m_pData;
	for (UINT n = 0; n < m_nAttributeCount; n++,pValue++)
	{
		if (*pValue == iValue)
		{
			*pValue = -iValue;
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


 
void CAttributeLayer::SetMap(CMapEditorDoc *pMap)
{
	m_pMap = pMap;
	if (pMap)
	{
		// expand or shrink the layer to fit the map dimensions
		int iWidth = pMap->m_iMapWidth;
		int iHeight = pMap->m_iMapHeight;
		if (m_size.cx != iWidth || m_size.cy != iHeight)
		{
			UINT nMapSize = iWidth * iHeight;
			ATTRIBUTE_BASE_TYPE *pValues = new ATTRIBUTE_BASE_TYPE[nMapSize];
			ASSERT(pValues != NULL);
			
			int iStartCol = 0;
			int iStartRow = 0;
			int iMaxCol   = min(m_size.cx, iWidth);
			int iMaxRow   = min(m_size.cy, iHeight);

			ASSERT(iStartCol >= 0);
			ASSERT(iStartRow >= 0);

			ASSERT(m_maxValue == ((1 << m_nBitCount) - 1));
			ASSERT(m_defaultValue >= 0 && m_defaultValue <= m_maxValue);

			ATTRIBUTE_BASE_TYPE value = (ATTRIBUTE_BASE_TYPE)(m_defaultValue + 1);
			ATTRIBUTE_BASE_TYPE *pValue = pValues;
			for (UINT n = 0; n < nMapSize; n++)
				*pValue++ = value;

			m_nSelected = 0;
			for (int iRow = iStartRow; iRow < iMaxRow; iRow++)
			{
				UINT nSrcIndex = iRow * m_size.cx + iStartCol;
				UINT nDstIndex = iRow * iWidth + iStartCol;
				for (int iCol = iStartCol; iCol < iMaxCol; iCol++)
				{
					ATTRIBUTE_BASE_TYPE iValue = m_pData[nSrcIndex++];
					pValues[nDstIndex++] = iValue;
					if (iValue < 0) m_nSelected++;
				}
			}
			delete [] m_pData;
			m_nAttributeCount = nMapSize;
			m_pData = pValues;
			m_size.cx = iWidth;
			m_size.cy = iHeight;
		}
		ValidateObjectMap();
	}
}

 
void CAttributeLayer::ClearRedo()
{
	while (!m_redo.IsEmpty())
	{
		CAttributeUndo *pUndo = m_redo.RemoveHead();
		delete pUndo;
	}
}

 
void CAttributeLayer::ClearUndo()
{
	ClearRedo();
	while (!m_undo.IsEmpty())
	{
		CAttributeUndo *pUndo = m_undo.RemoveHead();
		delete pUndo;
	}	
}

// Note: this method assumes that all views of the map share the same active
// layer. This is kind of a shame; 
 
void CAttributeLayer::Activate(BOOL bRefresh)
{
	CMapFrame *pFrame = GetParentFrame();
    if (pFrame)	
		pFrame->InstallToolPane(RUNTIME_CLASS(CAttributeView), 
		                        theApp.m_pMapDocTemplate, GetMap(), TRUE);
}

CString CAttributeLayer::GetInfo()
{
	CString info;
	info.Format(IDS_ATTRIBUTE_INFO,m_nBitCount);
	return info;
}
 
BOOL CAttributeLayer::SetCurrentValue(int iValue) 
{ 
	if (iValue >= (0-m_maxValue) && iValue <= m_maxValue)
	{
		m_currentValue = iValue;
		UpdateItemPos();
		return TRUE;
	}
	return FALSE;
}
void CAttributeLayer::SetColor(COLORREF color) 
{
	if (color != m_color)
	{
		m_color = color;
		if (m_eColorType == EAttrSolid)
			Invalidate(NULL); // repaint everything
	}
}
void CAttributeLayer::SetColorType(CAttrColorType eColorType) 
{ 
	if (m_eColorType != eColorType)
	{
		m_eColorType = eColorType;
		Invalidate(NULL);
	}
}

void CAttributeLayer::BeginEdit()
{
	// create a new undo level -- for now, let's keep it unlimited.
	CAttributeUndo *pUndo = new CAttributeUndo;
	ASSERT_NEW(pUndo);
    m_undo.AddHead(pUndo);

	// get rid of the previous redo, 
	// can only use redo immediately after undo
	ClearRedo(); 
}

 
void CAttributeLayer::EndEdit()
{
  if (!m_undo.IsEmpty())
  {
	  CAttributeUndo *pUndo = m_undo.GetHead();
	  if (pUndo->IsEmpty())
	  {
		  m_undo.RemoveHead();
		  delete pUndo;
	  }
  }
}

 
void CAttributeLayer::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !m_undo.IsEmpty() && !m_undo.GetHead()->IsEmpty() );
}

 
void CAttributeLayer::DoUndoRedo(CAttributeUndoList& src, CAttributeUndoList& dst)
{
	ASSERT(!src.IsEmpty());
	CAttributeUndo *pUndo = src.RemoveHead();

	POSITION pos = pUndo->GetStartPosition();
	ATTRIBUTE_BASE_TYPE *pValue, iValue;

	SelectNone();
	while (pos != NULL)
	{
		pUndo->GetNextAssoc(pos,pValue,iValue);
		pUndo->SetAt(pValue,*pValue); // save for redo
		*pValue = iValue;
	}
	CRect rect = pUndo->GetRect();
	LayerToMapRect(rect);
	Invalidate(rect);
	dst.AddHead(pUndo);
}

 
void CAttributeLayer::OnEditUndo() 
{
	DoUndoRedo(m_undo, m_redo);
}

 
void CAttributeLayer::LayerToMapRect(CRect& rect) 
{
	CPoint p1 = m_pMap->GetTileOffset(rect.top, rect.left);
	CPoint p2 = m_pMap->GetTileOffset(rect.bottom, rect.right);
	rect.SetRect(p1.x,p1.y,p2.x,p2.y);
}

 
void CAttributeLayer::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !m_redo.IsEmpty() && !m_redo.GetHead()->IsEmpty() );
}

 
void CAttributeLayer::OnEditRedo() 
{
	DoUndoRedo(m_redo, m_undo);
}

void CAttributeLayer::OnDecrementAttribute() 
{
   if (m_nSelected)
   {
	   BeginEdit();
	   CAttributeUndo *pUndo = GetCurrentUndo();
	   ATTRIBUTE_BASE_TYPE *pValue = m_pData;
	   CRect rect = GetSelection();
	   for (UINT i=0; i < m_nAttributeCount; i++,pValue++)
	   {
		   if (*pValue < -1) 
		   {
			   if (pUndo) pUndo->SetAt(pValue, -(*pValue));
			  *pValue += 1;
		   }
	   }
	   Invalidate(rect);
	   EndEdit();
   }
	
}

void CAttributeLayer::OnIncrementAttribute() 
{
   if (m_nSelected)
   {
	   BeginEdit();
	   CAttributeUndo *pUndo = GetCurrentUndo();
	   ATTRIBUTE_BASE_TYPE *pValue = m_pData;

	   CRect rect = GetSelection();
	   for (UINT i=0; i < m_nAttributeCount; i++,pValue++)
	   {
		   if ((*pValue < 0) && (*pValue > (- m_maxValue)))
		   {
			   if (pUndo) pUndo->SetAt(pValue, -(*pValue));
			  *pValue -= 1;
		   }
	   }
	   Invalidate(rect);
	   EndEdit();
   }
	
}


void CAttributeLayer::OnUpdateItemType(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(GetTitle());
}

void CAttributeLayer::OnUpdateItemId(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(GetFullValueString(m_currentValue));
}

void CAttributeLayer::OnUpdateItemInfo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
	pCmdUI->SetText(NULL); // SetText("") may result in memory leak
}


void CAttributeLayer::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(::IsClipboardFormatAvailable(g_nAttributeLayerFormat) && m_last.x != -1 && m_last.y != -1);
}

void CAttributeLayer::OnEditPaste() 
{
	if (OpenClipboard())
	{
	  CSharedFile memFile;

	  TRY
	  {
		HANDLE hData = ::GetClipboardData(g_nAttributeLayerFormat);
		if (hData != NULL)
		{
			memFile.SetHandle(hData,FALSE);
			CArchive ar(&memFile, CArchive::load|CArchive::bNoFlushOnDelete);

			// serialize data to document
			SelectNone();
			int iWidth, iHeight,iVal;
			ATTRIBUTE_BASE_TYPE *pValue;
			ar >> iWidth;
			ar >> iHeight;
			BeginEdit();
			TRY
			{
				CAttributeUndo *pUndo = GetCurrentUndo();
				for (int iRow=0, iAttrRow = m_last.y; iRow < iHeight; iRow++,iAttrRow++)
					for (int iCol = 0, iAttrCol = m_last.x; iCol < iWidth; iCol++,iAttrCol++)
				{
					ar >> iVal;
					if ((iVal >= 0) && (iAttrRow < m_size.cy) && (iAttrCol < m_size.cx))
					{
						pValue = SetAttribute(iAttrRow, iAttrCol, min(iVal,m_maxValue), pUndo);
						*pValue = - (*pValue);
						m_nSelected += 1;
					}
				}
			}
			END_TRY
			EndEdit();
			if (m_nSelected)
			{
				Invalidate(GetSelection());
				SetModifiedFlag();
			}
		}
		else
			AfxMessageBox(CG_IDS_CANNOT_GET_CLIPBOARD_DATA);
		CloseClipboard();
		memFile.Detach(); // so global ptr gets unlocked and doesn't get deallocated
	}
	CATCH_ALL(e)
	{
		CloseClipboard();
		memFile.Detach(); 
		THROW_LAST();
	}
	END_CATCH_ALL
  }
  else
 	 AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
	
}

void CAttributeLayer::Deactivate()
{
	CMapLayer::Deactivate();
	m_bUpdateTiles = FALSE;
	m_bUpdateDefault = FALSE;
	m_pTileLayer = NULL;
}


void CAttributeLayer::GetObjectAttribute(CMapObjectInst *pInstance, CPoint hotSpot, CAttributeInfo& rInfo)
{
	ASSERT(GetMap());
	ASSERT(m_bValidObjectMap);

	int iRow,iColumn;
	m_pMap->GetRowColumn(hotSpot,iRow,iColumn,FALSE /* roundup*/,TRUE /*clip*/);
    rInfo.SetDefaultValue(GetAttribute(iRow,iColumn));
    rInfo.m_pszName = GetTitle();
	rInfo.SetBitCount(GetBitCount());
	if (m_objectMap.Lookup(pInstance,rInfo.m_currentValue))
		rInfo.m_bRemoved = FALSE;
	else
	{
//      rInfo.m_currentValue = rInfo.GetDefaultValue();
        rInfo.m_currentValue = m_defaultValue;
//		m_currentValue = m_defaultValue;
		rInfo.m_bRemoved = TRUE;
	}
}


void CAttributeLayer::AdjustObjectAttribute(CMapObjectInst *pInstance, const CAttributeInfo& rInfo)
{
	ASSERT(pInstance != NULL);
	if (rInfo.m_bRemoved)
	{
		m_objectMap.RemoveKey(pInstance);
	}
	else
	{
		ASSERT(!m_pszTitle.CompareNoCase(rInfo.m_pszName));
		ASSERT(rInfo.GetBitCount() == GetBitCount());
		ASSERT(rInfo.m_currentValue >= 0 && rInfo.m_currentValue <= m_maxValue);
		m_objectMap.SetAt(pInstance,rInfo.m_currentValue);
		// TBD: resize the hash table if there are too many entries
	}	
}

void CAttributeLayer::RemoveObjectAttribute(CMapObjectInst *pInstance)
{
	m_objectMap.RemoveKey(pInstance);
}

void CAttributeLayer::Rename(const CString& pszName)
{
	CTileSet *pTileSet = GetTileSet();
	if (pTileSet)
	{
		CTileAttribute *pAttribute = pTileSet->FindAttribute(m_pszTitle);
		if (pAttribute)
		{
			pAttribute->SetName(pszName);
			pTileSet->SetModifiedFlag();
		}
	}
	CMapLayer::Rename(pszName);
}

// TBD: Move this out into a DLL
void CAttributeLayer::OnLayersCompute() 
{
	CMapEditorDoc *pDoc = GetMap();
	CComputeLayerDlg dlg;
	POSITION pos = pDoc->GetFirstLayer();
	while (pos != NULL)
	{
		CAttributeLayer *pLayer = DYNAMIC_DOWNCAST(CAttributeLayer, pDoc->GetNextLayer(pos));
		if (pLayer)
			dlg.m_attributeLayerList.AddTail(pLayer);
	}
	if (dlg.DoModal())
	{
		// SAMPLE ComputeLayer code
		BeginEdit();
		CSize size = GetSize();
        int iMax = GetMaxValue();
		for (int iRow = 0; iRow < size.cy; iRow++)
		{
			for (int iCol = 0; iCol < size.cx; iCol++)
			{
                // compute the new attribute value
				int iVal = dlg.m_pSourceLayer->GetAttribute(iRow,iCol) + dlg.m_iValue;
				if (iVal > iMax) iVal = iMax; // max sure it is a legal value
				SetAttribute(iRow,iCol,iVal);
			}
		}
		Invalidate(NULL); // invalidate the whole attribute layer to force complete redraw
		EndEdit();
	}
}
