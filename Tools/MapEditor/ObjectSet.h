#ifndef _OBJECTSET_H_
#define _OBJECTSET_H_
// ObjectSet.h : header file
//
#include "TileCategory.h"  // generic category
#include "MapObject.h"

/////////////////////////////////////////////////////////////////////////////
// CObjectSet document
//
// Note: we don't store a pointer to a palette in the ObjectSet because the
// same object set may be used with multiple maps and their associated tileset
// palettes.  The ObjectSetView must be responsible for showing the objects
// with the correct palette.
//
class CMapEditorDoc;


#define OSV_UPDATE_ITEM  0x0001   // update the current item
#define OSV_UPDATE_LIST  0x0002   // update item lists
#define OSV_UPDATE_TAB   0x0004   // update categories
#define OSV_UPDATE_ALL (OSV_UPDATE_ITEM|OSV_UPDATE_LIST|OSV_UPDATE_TAB)

#define OSV_UPDATE_NAMES 0x0008   // update items names

class CObjectSet : public CDocument
{
protected:
	enum
	{
		eBmpObject, // static bmp or dib objects
		eAxrObject, // 3do axr compressed 8-bit animated objects
	};
    CTypedPtrList<CPtrList, CMapEditorDoc *> m_mapList; // list of open maps using this objectSet
    CTypedPtrArray<CPtrArray, CMapObject *> m_objects;
	CTypedPtrMap<CMapStringToPtr, CString, CMapObject *> m_objectMap;  // table mapping object names to ids
    CCategoryList m_categories;
	int m_iCurrentItem;

	CObjectSet();  // used by dynamic creation
	DECLARE_DYNCREATE(CObjectSet)

    CCategory *AddCategory(LPCTSTR title)
	{
		CCategory *pCategory = new CCategory(title);
		ASSERT_NEW(pCategory);
		m_categories.AddTail(pCategory);
		return pCategory;
	}
	int AddObject(LPCTSTR pathName, CCategory *pCategory, int eObjectType);
	void LoadMatchingFiles(const CString& pathName, const CString& ext, CCategory *pCategory, int eObjectType);
	virtual CString GetObjectID(LPCTSTR lpszPath, CCategory *pCategory);

// Attributes
public:
	int FindCategory(const CString& pszName);
	int GetObjectCategory(int iObject);
	void RemapObjects(CPalette *pPalette);
	CMapObject * GetCurrentObject();
	int GetCurrentItem() const { return m_iCurrentItem; }
	int GetCategoryCount() { return m_categories.GetCount(); }
	int GetObjectCount()   { return m_objects.GetSize(); }
	CCategory *GetCategory(int iIndex) 
	{ 
		ASSERT(iIndex >= 0);
		if (iIndex >= GetCategoryCount())
			return NULL;
		POSITION pos = m_categories.FindIndex(iIndex);
		ASSERT(pos != NULL);
		return m_categories.GetAt(pos); 
	}
	CMapObject *GetObject(int iIndex)
	{
		ASSERT(iIndex >= 0 && iIndex < GetObjectCount());
		ASSERT(m_objects[iIndex] != NULL);
		return m_objects[iIndex];
	}

// Operations
public:
    virtual int FindObject(LPCTSTR lpszID, BOOL bAddFake = FALSE);
	void DrawObject(HDC hdc, int iIndex, CPoint offset, HDC hdcTemp, CDIB *pDst = NULL,
		int iSequence = 0, int iFrame = 0, BOOL bFlipped = FALSE);
	void DrawWithPalette( HDC hdc, int nObject, RECT& dstRect, HPALETTE hPalette);
    virtual void SetCurrentItem(int iItem) 
	{
		m_iCurrentItem = iItem;
		UpdateAllViews(NULL, OSV_UPDATE_ITEM);
	}
	// mapList manipulation
	void AddMap(CMapEditorDoc *pMap);
    void RemoveMap(CMapEditorDoc *pMap);
    BOOL HasOpenMaps() { return (!m_mapList.IsEmpty()); }


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectSet)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnChangedViewList();
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CObjectSet();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CObjectSet)
	afx_msg void OnFileRevert();
	afx_msg void OnUpdateItemType(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemId(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemInfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
