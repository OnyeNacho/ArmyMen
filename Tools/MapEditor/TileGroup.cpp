#include "stdafx.h" 
#include "MapEditor.h"
#include "TileGroup.h"
#include "mapframe.h"
#include "tilelayer.h"
#include "mapeditordoc.h"
#include "attributelayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////
// CTileGroup
//////////////////////////////////////////////////////
#ifdef _DEBUG
void CTileGroup::AssertValid() const
{
	CObject::AssertValid();
	if (m_piTiles)
	{
		size_t iTileCount = m_iGroupWidth * m_iGroupHeight;
		size_t size = _msize(m_piTiles);
		ASSERT(size >= iTileCount * sizeof(int));
	}
	else
	{
		ASSERT(m_iGroupWidth == 0);
		ASSERT(m_iGroupHeight == 0);
	}
}
#endif

CTileGroup::CTileGroup()
{
	m_piTiles = NULL;
	m_iGroupWidth = 0;
	m_iGroupHeight = 0;
	m_iSel = 0;
	m_bBase = TRUE;
	m_bMLayer = FALSE;
	m_bGroup2 = FALSE;
	m_iALayers = 0;
}


CTileGroup::CTileGroup(LPCTSTR lpszTitle, int iWidth, int iHeight)
{
	m_pszTitle = lpszTitle;
	m_piTiles = NULL;
	SetSize(iWidth,iHeight);
	m_bBase = TRUE;
	m_bMLayer = FALSE;
	m_iSel = 0;
	m_bGroup2 = FALSE;
	m_iALayers = 0;
}

CTileGroup::~CTileGroup()
{
	DeleteContents();
}

void CTileGroup::Copy(CTileGroup* pGroup)
{
	m_pszTitle = pGroup->m_pszTitle;
	int iTileCount = SetSize(pGroup->m_iGroupWidth, pGroup->m_iGroupHeight);
	if (iTileCount)
	{
		ASSERT(m_piTiles != NULL);
		memcpy(m_piTiles, pGroup->m_piTiles, iTileCount * sizeof(int));
	}
}

void CTileGroup::DeleteContents()
{
	if (m_piTiles)
	{
		delete [] m_piTiles;
		m_piTiles = NULL;
	}
	m_iGroupWidth = 0;
	m_iGroupHeight = 0;
	AttribGroup *pGroup = NULL;
	POSITION pPos = m_sALayers.GetHeadPosition();
	while (NULL != pPos)
	{
		pGroup = (AttribGroup*)m_sALayers.GetNext(pPos);
		if (NULL != pGroup)
			delete pGroup;
	}
}

IMPLEMENT_SERIAL(CTileGroup, CObject, VERSIONABLE_SCHEMA|3)

void CTileGroup::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		PUT_SAFE_SCHEMA(ar, CTileGroup);
		ar << m_pszTitle;
		ar << m_iGroupWidth;
		ar << m_iGroupHeight;
		int iTileCount = m_iGroupWidth * m_iGroupHeight;
		for (int i=0; i < iTileCount; i++)
		{
			ar << m_piTiles[i];
		}
		///////////////////////////////////////////////////////////////////
		// Code here for saving multi-layer group data
		///////////////////////////////////////////////////////////////////
		ar << m_bMLayer;
		if (m_bMLayer)
		{
			ar << m_bBase;
			ar << m_bGroup2;
			ar << m_iSel;
			int iCur=0;
			if (m_bGroup2)
			{
				ASSERT(m_iSel == m_sGroup2.GetSize());
				while (iCur < m_iSel)
				{
					ar << m_sGroup2[iCur];
					iCur++;
				}
			}
			ASSERT(m_iALayers == m_sALayers.GetCount());
			ar << m_iALayers;
			iCur = 0;
			AttribGroup *pGroup = NULL;
			POSITION pPos = m_sALayers.GetHeadPosition();
			int iCur2;
			while (iCur < m_iALayers)
			{
				pGroup = (AttribGroup*)m_sALayers.GetNext(pPos);
				ar << pGroup->sName;
				iCur2 = 0;
				while (iCur2 < m_iSel)
				{
					ar << pGroup->aList[iCur2];
					iCur2++;
				}
				iCur++;
			}
		}
		///////////////////////////////////////////////////////////////////
	}
	else 
	{
		UINT schema = GET_SAFE_SCHEMA(ar,CTileGroup,2);
		ar >> m_pszTitle;
		ar >> m_iGroupWidth;
		ar >> m_iGroupHeight;
		int iTileCount = SetSize(m_iGroupWidth,  m_iGroupHeight);
		for (int i=0; i < iTileCount; i++)
		{
			ar >> m_piTiles[i];
		}
		///////////////////////////////////////////////////////////////////
		// Code here for loading multi-layer group data if schema is 3
		///////////////////////////////////////////////////////////////////
		if (3 <= schema)
		{
			int iCur=0;
			ar >> m_bMLayer;
			if (m_bMLayer)
			{
				ar >> m_bBase;
				ar >> m_bGroup2;
				ar >> m_iSel;
				if (m_bGroup2)
				{
					int iTemp=0;
					while (iCur < m_iSel)
					{
						ar >> iTemp;
						m_sGroup2.Add(iTemp);
						iCur++;
					}
				}
				ar >> m_iALayers;
				iCur = 0;
				int iCur2;
				int iTemp=0;
				AttribGroup *pGroup = NULL;
				while (iCur < m_iALayers)
				{
					iCur2 = 0;
					pGroup = new AttribGroup;
					ar >> pGroup->sName;
					while (iCur2 < m_iSel)
					{
						ar >> iTemp;
						pGroup->aList.Add(iTemp);
						iCur2++;
					}
					m_sALayers.AddTail(pGroup);
					iCur++;
				}
			}
		}
		///////////////////////////////////////////////////////////////////
	}
}

void AFXAPI SerializeElements( CArchive& ar, CTileGroup* pGroup, int iCount)
{
    for ( int i = 0; i < iCount; i++, pGroup++ )
    {
        // Serialize each CPerson object
        pGroup->Serialize( ar );
    }
}

int CTileGroup::GetTile(int iRow, int iColumn)
{
	ASSERT(iColumn >= 0 && iColumn < m_iGroupWidth);
	ASSERT(iRow >= 0 && iRow < m_iGroupHeight);
	ASSERT(m_piTiles != NULL);
	return m_piTiles[iRow * m_iGroupWidth + iColumn];
}

void CTileGroup::SetTile(int iRow, int iColumn, int iTile)
{
	ASSERT(iColumn >= 0 && iColumn < m_iGroupWidth);
	ASSERT(iRow >= 0 && iRow < m_iGroupHeight);
	ASSERT(m_piTiles != NULL);
	m_piTiles[iRow * m_iGroupWidth + iColumn] = iTile;
}

int CTileGroup::SetSize(int iWidth, int iHeight)
{
	m_iGroupWidth = iWidth;
	m_iGroupHeight = iHeight;
	if (m_piTiles) 
	{ 
		delete [] m_piTiles;
		m_piTiles = NULL;
	}
	int iTileCount = m_iGroupWidth * m_iGroupHeight;
	if (iTileCount)
	{
		m_piTiles = new int[iTileCount];
		ASSERT_NEW(m_piTiles);
	}
	ASSERT_VALID(this);
	return iTileCount;
}



void CTileGroup::RemoveTile(int iTile)
{
	int *pTile = m_piTiles;
	int iTileCount = m_iGroupWidth * m_iGroupHeight;
	for (int i=0; i < iTileCount; i++,pTile++)
	{
		if (*pTile == iTile)
			*pTile = -1; // NO_TILE
		else if (*pTile > iTile)
			*pTile -= 1;
	}	
}

void CTileGroup::ReplaceTile(int iTile, int iReplacement)
{
	int *pTile = m_piTiles;
	int iTileCount = m_iGroupWidth * m_iGroupHeight;
	for (int i=0; i < iTileCount; i++,pTile++)
	{
		if (*pTile == iTile)
			*pTile = iReplacement;
	}
}

void CTileGroup::ReplaceTiles(CTileList& repList)
{
	int *pTile = m_piTiles;
	int iSize = repList.GetSize();
	int iTileCount = m_iGroupWidth * m_iGroupHeight;

	for (int i=0; i < iTileCount; i++,pTile++)
	{
		int iTile = *pTile;
		if (iTile >= 0 && iTile < iSize && repList[iTile] >= 0)
			*pTile = repList[iTile];
	}	
}

///////////////////////////////////////////////////////////////////
// Copys MLayer data from current group to specified group
///////////////////////////////////////////////////////////////////
BOOL CTileGroup::CopyMLayerToGroup(CTileGroup *pGroup)
{
	if (m_bMLayer)
	{
		pGroup->m_bMLayer = m_bMLayer;
		pGroup->m_bBase = m_bBase;
		pGroup->m_bGroup2 = m_bGroup2;
		pGroup->m_iSel = m_iSel;
		pGroup->m_iALayers = m_iALayers;
		int iCur=0;
		if (m_bGroup2)
		{
			while (iCur < m_iSel)
			{
				pGroup->m_sGroup2.Add(m_sGroup2[iCur]);
				iCur++;
			}
		}
		AttribGroup *pAGroup1 = NULL;
		AttribGroup *pAGroup2 = NULL;
		POSITION pPos = m_sALayers.GetHeadPosition();
		while (NULL != pPos)
		{
			pAGroup1 = (AttribGroup*)m_sALayers.GetNext(pPos);
			if (NULL != pAGroup1)
			{
				pAGroup2 = new AttribGroup;
				pAGroup2->sName = pAGroup1->sName;
				iCur=0;
				while (iCur < m_iSel)
				{
					pAGroup2->aList.Add(pAGroup1->aList[iCur]);
					iCur++;
				}
				pGroup->m_sALayers.AddTail(pAGroup2);
			}
		}
	}
	else
		return FALSE;
	return TRUE;
}

void CTileGroup::GetMLayer(int iCol, int iRow, CMapEditorDoc *pDoc)
{
	CMapEditorDoc *pMapDoc = pDoc;
	CAttributeLayer *pALayer=NULL;
	CTileLayer *pLayer=NULL;
	int iCur=0;
	int iALayers;

	if (NULL == pMapDoc)
		return;

	iALayers = pDoc->GetAttributeCount();

	// Determine current layer
	pLayer = (CTileLayer*)pDoc->GetActiveLayer();
	if (NULL == pLayer)
		return;

	if (0 == lstrcmp(pLayer->GetTitle(), _T("Base Tiles")))
	{
		// Copy overlay layer into group2 if visible
		pLayer = NULL;
		pLayer = (CTileLayer*)pDoc->FindLayer(_T("Overlay Tiles"));
		if (NULL == pLayer)
			return;
		if (pLayer->IsVisible() && (TRUE == CopyLayer(iCol, iRow, pLayer)))
		{
			m_bMLayer = TRUE;
			m_bBase = FALSE;
		}
	}
	else
	{
		// Copy base layer into group2
		pLayer = NULL;
		pLayer = (CTileLayer*)pDoc->FindLayer(_T("Base Tiles"));
		if (NULL == pLayer)
			return;
		if (pLayer->IsVisible() && (TRUE == CopyLayer(iCol, iRow, pLayer)))
		{
			m_bMLayer = TRUE;
			m_bBase = TRUE;
		}
	}

	// Copy all attribute layers
	if (0 >= iALayers)
		return;
	POSITION pPos = pDoc->GetFirstAttribute();
	while (iCur < iALayers)
	{
		pALayer = pDoc->GetNextAttribute(pPos);
		if (NULL != pALayer && (TRUE == AddALayer(iCol, iRow, pALayer)))
		{
			m_bMLayer = TRUE;
			m_iALayers++;
		}
		iCur++;
	}
}

BOOL CTileGroup::DoMLayer(int iCol, int iRow, int iMCol, int iMRow, CMapEditorDoc *pDoc)
{
	int iCur=0;

	if (!m_bMLayer)
		return FALSE;
	
	CMapEditorDoc *pMapDoc = pDoc;
	if (NULL == pMapDoc)
		return FALSE;

	if (m_bGroup2)
	{
		if (m_bBase)
		{
			CTileLayer *pLayer = (CTileLayer*)pDoc->FindLayer(_T("Overlay Tiles"));
			if (NULL == pLayer)
				return FALSE;
			CTileUndo *pUndo = pLayer->GetCurrentUndo();
			for (int row=iRow; row < iMRow; row++)
			{
				for (int col=iCol; col < iMCol; col++)
				{
					int iTile = GetTile(row - iRow, col - iCol);
					if (iTile >= 0)
						pLayer->SetTile(row, col, iTile, pUndo);
				}
			}
			pLayer = (CTileLayer*)pDoc->FindLayer(_T("Base Tiles"));
			if (NULL == pLayer)
				return FALSE;
			if (FALSE == DoLayer(iCol, iRow, iMCol, iMRow, pLayer))
				return FALSE;
		}
		else
		{
			CTileLayer *pLayer = (CTileLayer*)pDoc->FindLayer(_T("Base Tiles"));
			if (NULL == pLayer)
				return FALSE;
			CTileUndo *pUndo = pLayer->GetCurrentUndo();
			for (int row=iRow; row < iMRow; row++)
			{
				for (int col=iCol; col < iMCol; col++)
				{
					int iTile = GetTile(row - iRow, col - iCol);
					if (iTile >= 0)
						pLayer->SetTile(row, col, iTile, pUndo);
				}
			}
			pLayer = (CTileLayer*)pDoc->FindLayer(_T("Overlay Tiles"));
			if (NULL == pLayer)
				return FALSE;
			if (FALSE == DoLayer(iCol, iRow, iMCol, iMRow, pLayer))
				return FALSE;
		}
	}

	POSITION pPos = pDoc->GetFirstAttribute();
	CAttributeLayer *pALayer=NULL;
	while (iCur < m_iALayers)
	{
		if (NULL == pPos)
			return FALSE;
		pALayer = pDoc->GetNextAttribute(pPos);
		DoALayer(iCol, iRow, iMCol, iMRow, pALayer);
		iCur++;
	}

	return TRUE;
}

BOOL CTileGroup::CopyLayer(int iCol, int iRow, CTileLayer *pLayer)
{
	int iTile,i=0;
	int iCurCol=0,iCurRow=0, iMCol=iCol;
	int *pTile = m_piTiles;
	int iTileCount = m_iGroupWidth * m_iGroupHeight;
	m_iSel = 0;

	while (i < iTileCount)
	{
		iTile = *pTile;
		if (0 <= iTile)
		{
			m_sGroup2.Add(pLayer->GetTile(iRow, iMCol));
			m_iSel++;
		}
		i++;
		pTile++;
		iCurCol++;
		iMCol++;
		if (iCurCol == m_iGroupWidth)
		{
			iCurCol = 0;
			iMCol = iCol;
			iCurRow++;
			iRow++;
		}
	}
	m_bGroup2 = TRUE;
	return TRUE;
}

BOOL CTileGroup::AddALayer(int iCol, int iRow, CAttributeLayer *pLayer)
{
	ATTRIBUTE_FLAGS sFlags;
	int iTile,i=0;
	int iCurCol=0,iCurRow=0, iMCol=iCol;
	int *pTile = m_piTiles;
	m_iSel = 0;
	AttribGroup *pGroup = new AttribGroup;
	if (NULL == pGroup)
		return FALSE;
	int iTileCount = m_iGroupWidth * m_iGroupHeight;

	while (i < iTileCount)
	{
		iTile = *pTile;
		if (0 <= iTile)
		{
			pGroup->aList.Add(pLayer->GetAttribute(iRow, iMCol, &sFlags, TRUE));
			m_iSel++;
		}
		i++;
		pTile++;
		iCurCol++;
		iMCol++;
		if (iCurCol == m_iGroupWidth)
		{
			iCurCol = 0;
			iMCol = iCol;
			iCurRow++;
			iRow++;
		}
	}
	pGroup->sName = pLayer->GetTitle();
	m_sALayers.AddTail(pGroup);
	return TRUE;
}

BOOL CTileGroup::DoLayer(int iCol, int iRow, int iMCol, int iMRow, CTileLayer *pLayer)
{
	int iTile,i=0,iL=0;
	int iCurCol=0,iCurRow=0, iCCol=iCol;
	int *pTile = m_piTiles;
	int iTileCount = m_iGroupWidth * m_iGroupHeight;

	while (i < iTileCount)
	{
		
		iTile = *pTile;
		if (0 <= iTile)
		{
			pLayer->SetTile(iRow, iCCol, m_sGroup2[iL], NULL);
			iL++;
		}
		i++;
		pTile++;
		iCurCol++;
		iCCol++;
		if (iCurCol == m_iGroupWidth)
		{
			iCurCol = 0;
			iCCol = iCol;
			iCurRow++;
			iRow++;
		}
		if (iCCol == iMCol)
		{
			iCCol = iCol;
			iRow++;
		}
		if (iRow == iMRow)
			break;
	}
	return TRUE;
}

BOOL CTileGroup::DoALayer(int iCol, int iRow, int iMCol, int iMRow, CAttributeLayer *pLayer)
{
	int iTile,i=0,iCur=0,iL=0;
	int iCurCol=0,iCurRow=0, iCCol=iCol;
	int *pTile = m_piTiles;
	AttribGroup *pGroup = NULL;
	int iTileCount = m_iGroupWidth * m_iGroupHeight;

	// Search for group with same name as attribute layer
	CString sTemp = pLayer->GetTitle();
	POSITION pPos = m_sALayers.GetHeadPosition();
	while (iCur < m_iALayers)
	{
		if (NULL == pPos)
			break;
		pGroup = (AttribGroup*)m_sALayers.GetNext(pPos);
		if (NULL != pGroup)
		{
			if (pGroup->sName == sTemp)
				break;
			pGroup = NULL;
		}
		iCur++;
	}
	if (NULL == pGroup)
		return FALSE;

	while (i < iTileCount)
	{
		iTile = *pTile;
		if (0 <= iTile)
		{
			pLayer->SetAttribute(iRow, iCCol, pGroup->aList[iL], NULL);
			iL++;
		}
		i++;
		pTile++;
		iCurCol++;
		iCCol++;
		if (iCurCol == m_iGroupWidth)
		{
			iCurCol = 0;
			iCCol = iCol;
			iCurRow++;
			iRow++;
		}
		if (iCCol == iMCol)
		{
			iCCol = iCol;
			iRow++;
		}
		if (iRow == iMRow)
			break;
	}
	return TRUE;
}
