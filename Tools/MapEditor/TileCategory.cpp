#include "stdafx.h" 
#include "MapEditor.h"
#include "TileCategory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////
// CTileCategory: note all methods in this file assume that a category may
// one contain one instance of a given tile.
/////////////////////////////////////////////////////////////////////////////////
CTileCategory::CTileCategory()
{
}

CTileCategory::~CTileCategory()
{
}

#ifdef _DEBUG
void CTileCategory::AssertValid() const
{
	CObject::AssertValid();
	int iCount = m_itemArray.GetSize();
	for (int i=0; i < iCount; i++)
	{
		int iTile = m_itemArray[i];
		ASSERT(iTile >= 0);
		// note: it is not ok to have tiles >= tileset tilecount 
		// but since we don't have a back pointer to the tileset
		// we can't check that here.  Besides map/tileset should
		// protect themselves from drawing illegal tiles (I hope).
		for (int j=i+1; j < iCount; j++)
			ASSERT(m_itemArray[j] != iTile);
	}
}
#endif

IMPLEMENT_SERIAL(CTileCategory, CObject, VERSIONABLE_SCHEMA | 2)

void CTileCategory::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		PUT_SAFE_SCHEMA(ar, CTileCategory); // for versioning
		ar << m_pszTitle;
		m_itemArray.Serialize(ar);
	}
	else 
	{
		UINT schema = GET_SAFE_SCHEMA(ar, CTileCategory, 2);
		ar >> m_pszTitle;
		m_itemArray.Serialize(ar);
	}
}

CTileCategory::CTileCategory(CTileCategory& src)
{
	m_pszTitle = src.m_pszTitle;
	int iItems = src.GetItemCount();
	m_itemArray.SetSize(iItems);
	for (int i=0; i < iItems; i++)
        m_itemArray.Add(src.GetItemAt(i));
}

void CTileCategory::operator=(CTileCategory& src)
{
	m_pszTitle = src.m_pszTitle;
	int iItems = src.GetItemCount();
	m_itemArray.SetSize(iItems);
	for (int i=0; i < iItems; i++)
        m_itemArray.Add(src.GetItemAt(i));
}

void CTileCategory::SetItemAt(int iIndex, int iItemIndex)
{
	ASSERT(iIndex >= 0);
	ASSERT(iIndex < GetItemCount());
	m_itemArray.SetAt(iIndex, iItemIndex);
}

int CTileCategory::GetItemAt(int iIndex)
{
	ASSERT(iIndex >= 0);
	ASSERT(iIndex < GetItemCount());
	return m_itemArray[iIndex];
}

int CTileCategory::FindItem(int iItemIndex)
{
    for (int i=0; i < GetItemCount(); i++)
	{
		if (m_itemArray[i] == iItemIndex)
			return i;
	}
	return -1;
}


void AFXAPI SerializeElements( CArchive& ar, CTileCategory* pCategory, int iCount)
{
    for ( int i = 0; i < iCount; i++, pCategory++ )
    {
        // Serialize each CPerson object
        pCategory->Serialize( ar );
    }
}

BOOL CTileCategory::AddItem(int iItemIndex)
{
	if (FindItem(iItemIndex) >= 0)
		return FALSE;
	m_itemArray.Add(iItemIndex);
	return TRUE;
}

void CTileCategory::RemoveItemAt(int iIndex)
{
	ASSERT(iIndex >= 0);
	ASSERT(iIndex < GetItemCount());
	m_itemArray.RemoveAt(iIndex);
}

// if iItemIndex is a member of this category, it is removed from
// this category. Call this function to remove one member of the 
// category. 
BOOL CTileCategory::RemoveItem(int iItemIndex)
{
	int iIndex = FindItem(iItemIndex);
	if (iIndex >= 0)
	{
		m_itemArray.RemoveAt(iIndex);
		return TRUE;
	}
	return FALSE;
}

// if iItemIndex is a member of this category, it is removed from
// this category AND all items whose indices are greater than 
// iItemIndex are decremented by 1.  Call this function when
// a tile is removed from the tileset.
void CTileCategory::RemovePermanent(int iItemIndex)
{
	int i=0;

	while (i < GetItemCount())
	{
	   if (m_itemArray[i] == iItemIndex)
		   m_itemArray.RemoveAt(i);
       else 
	   {  
		   if (m_itemArray[i] > iItemIndex)
			   m_itemArray[i] -= 1;
		   ++i;
	   }
	}
}

void CTileCategory::ReplaceItem(int iItemIndex, int iReplacement)
{
   int iIndex = FindItem(iItemIndex);
   if (iIndex >= 0)
   {
	   if (FindItem(iReplacement) >= 0)
		  m_itemArray.RemoveAt(iIndex);
	   else
		  m_itemArray[iIndex] = iReplacement;
   }
}

void CTileCategory::ReplaceItems(CTileList& repList)
{
	int iItem, iCount = GetItemCount();
	int iSize = repList.GetSize();
    int i = 0;

	while (i < GetItemCount())
	{
		iItem = m_itemArray[i];
		ASSERT(iItem >= 0);

		if (iItem < iSize)
		{
			int iReplacement = repList[iItem];
			if (iReplacement >= 0)
			{
				if (FindItem(iReplacement) >= 0)
					m_itemArray.RemoveAt(i--);  // decrement i so we do the next item
				else
					m_itemArray[i] = iReplacement;
			}
		}
		i++;
	}
	ASSERT_VALID(this);
}
