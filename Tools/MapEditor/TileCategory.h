#ifndef _TILECATEGORY_H_
#define _TILECATEGORY_H_

#include "TileList.h"

//////////////////////////////////////////////////////////////////////////////////////
// CTileCategory: a named list of items from a larger set of items.
//  
// Note: this class is now somewhat misnamed.  It can be used to store
// list of items from a set of tiles, a set of groups or a set of objects.
//
// Note2: iIndex refers to the category item's index as returned by
// FindItem and iItemIndex refers to the item's index in tileset, or
// objectset.
//////////////////////////////////////////////////////////////////////////////////////
class CTileCategory : public CObject
{
protected:
	CString m_pszTitle;
    CArray<int, int> m_itemArray;
    DECLARE_SERIAL(CTileCategory)

public:
	virtual ~CTileCategory();

	// Construction
	CTileCategory();
	CTileCategory(LPCTSTR pszTitle) { m_pszTitle = pszTitle;}
    CTileCategory( CTileCategory& src );

	// Operations
    CString GetTitle() { return m_pszTitle; }  
	int GetItemCount() { return m_itemArray.GetSize(); }
	void SetTitle(LPCTSTR lpszTitle) { m_pszTitle = lpszTitle; }
	void SetItemAt(int iIndex, int iItemIndex); 
	void RemoveItemAt(int iIndex); 
	int GetItemAt(int iIndex);
	int FindItem(int iItemIndex); // returns index (-1 if not found)
	BOOL AddItem(int iItemIndex);  
    BOOL RemoveItem(int iItemIndex); 
	void RemovePermanent(int iItemIndex);
	void ReplaceItem(int iItemIndex, int iReplacement);
	void ReplaceItems(CTileList& repList);
	virtual void Serialize(CArchive& ar);

	// Operators
	void operator=(CTileCategory& src);
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

};

void AFXAPI SerializeElements( CArchive& ar, CTileCategory* pCategory, int iCount);

// Some new names...
// Note: I didn't rename the class because of a backward compatibility
// problem; ar.SerializeClass() actually stores and looks for the class
// name in the file.
typedef CTypedPtrList<CObList,CTileCategory*> CCategoryList;
typedef CTileCategory CCategory;

#endif