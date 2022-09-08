#include "stdafx.h" 
#include "MapEditor.h"
#include "TileSet.h"
#include "TileSetOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////
// CTileSetOp
//////////////////////////////////////////////////////
CTileSetOp::CTileSetOp()
{
	m_opType = TSOP_NONE;
	m_pSrc = NULL;
	m_clipID = _T("");
	m_iTileView = TSV_TILES;
}

CTileSetOp::CTileSetOp(CTileOp opType, int iTileView, int nIndices, CTileSet *pSrcTileSet)
{
	m_opType = TSOP_NONE;
	m_pSrc = NULL;
	if (!Create(opType, iTileView, nIndices, pSrcTileSet))
		AfxThrowMemoryException();
}

CTileSetOp::~CTileSetOp()
{
    DeleteContents();
}

IMPLEMENT_SERIAL(CTileSetOp, CObject, VERSIONABLE_SCHEMA | 2)

void CTileSetOp::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	int opType = m_opType;

	if (ar.IsStoring())
	{
		// PUT_SAFE_SCHEMA(ar, CTileSetOp); // TBD: messes up pasting of tilegroups
		ar << m_clipID;
		ar << m_iTileView;
	    ar << opType;
	}
	else
	{
		// schema = GET_SAFE_SCHEMA(ar, CTileSetOp, 2); 
		ar >> m_clipID;
		ar >> m_iTileView;
		ar >> opType;
		m_opType = (CTileOp)opType;
	}

	m_tileIndex.Serialize(ar);
	m_groupIndex.Serialize(ar);
	m_tileSet.Serialize(ar); // TBD: why does this have to be last?
	ASSERT_VALID(this);
}

int CTileSetOp::FindTile(int nIndex)
{
	int iCount = m_tileIndex.GetSize();
	for (int i=0; i < iCount; i++)
	{
		if (m_tileIndex[i] == nIndex)
			return i;
	}
	return -1;
}

/*
** METHOD
**   CTileSetOp::AddTile
**
** PARAMETERS
**   int nIndex -- index of tile in the source tileset
**
** DESCRIPTION
**    adds the tile associated with nIndex in the source tileset to 
**    this tileset if it hasn't already been added. 
**
** RETURNS
**    the index of the tile's image in this tileset
*/
int CTileSetOp::AddTile(int nIndex)
{
	ASSERT(m_pSrc != NULL);
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < m_pSrc->GetTileCount());

	int iTileIndex = FindTile(nIndex);
	if (iTileIndex < 0)
	{
		int iIndex = m_tileSet.CopyTile(m_pSrc, nIndex);
		iTileIndex = m_tileIndex.Add(nIndex);
		ASSERT(iIndex == iTileIndex);
	}
	return iTileIndex;
}

BOOL CTileSetOp::Create(CTileOp opType, int iTileView, int nIndices, CTileSet *pSrcTileSet)
{
	ASSERT(m_opType == TSOP_NONE);
	m_pSrc = pSrcTileSet;
    m_opType = opType;
	m_iTileView = iTileView;
	m_tileIndex.SetSize(0, nIndices);
	m_clipID = pSrcTileSet->GetClipID();
	return m_tileSet.OnNewDocument(pSrcTileSet, nIndices);
}


#ifdef _DEBUG
void CTileSetOp::AssertValid() const
{
	ASSERT_VALID(&m_tileIndex);
	ASSERT_VALID(&m_tileSet);

	if (m_pSrc != NULL)
	{
        int iCount = m_tileIndex.GetSize();
		ASSERT(iCount == m_tileSet.GetTileCount());

		iCount = m_groupIndex.GetSize();
		ASSERT(iCount == m_tileSet.GetGroupCount());

		switch(m_opType)
		{
			case TSOP_NONE:
				ASSERT(iCount == 0);
				break;
			case TSOP_COPY:
			case TSOP_PASTE:
				break;
			default:
				ASSERT(m_opType == TSOP_CUT);
				break;
		}
	}
}
#endif

void CTileSetOp::SetType(CTileOp opType)
{
   if (opType != m_opType)
   {
	   if (opType == TSOP_NONE)
	      DeleteContents();
	   m_opType = opType;
   }
}

void CTileSetOp::DeleteContents()
{
    m_tileSet.DeleteContents();
	m_tileIndex.RemoveAll();
	m_groupIndex.RemoveAll();
	m_opType = TSOP_NONE;
}

BOOL CTileSetOp::IsSameTileSet(CTileSet* pTileSet)
{
	return (m_clipID.CompareNoCase(pTileSet->GetClipID()) == 0);		
}

void CTileSetOp::AddGroup(CTileGroup* pGroup,int iGroupIndex)
{
	ASSERT(m_pSrc != NULL);
	CSize size = pGroup->GetSize();

	m_groupIndex.Add(iGroupIndex);
	int iGroup = m_tileSet.AddGroup(pGroup->GetTitle(), size.cx, size.cy);
	ASSERT(iGroup >= 0);

	CTileGroup *pNewGroup = m_tileSet.GetGroupAt(iGroup);
	ASSERT(pNewGroup != NULL);

	for (int iRow = 0; iRow < size.cy; iRow++)
	{
		for (int iCol = 0; iCol < size.cx; iCol++)
		{
			
			int iTile = pGroup->GetTile(iRow,iCol);
			if (iTile >= 0) 
				iTile = AddTile(iTile);
			pNewGroup->SetTile(iRow,iCol,iTile);

		}
	}
	pGroup->CopyMLayerToGroup(pNewGroup);
}

void CTileSetOp::AddGroup(int iGroup)
{
	ASSERT(m_pSrc != NULL);
	AddGroup(m_pSrc->GetGroupAt(iGroup), iGroup);
}
