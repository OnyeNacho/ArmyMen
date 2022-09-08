#ifndef _TILEGROUP_H_
#define _TILEGROUP_H_
#include "TileList.h"

class CMapEditorDoc;
class CTileLayer;
class CAttributeLayer;

struct AttribGroup
{
	CString sName;
	CArray<int, short> aList;
};

class CTileGroup : public CObject
{
DECLARE_SERIAL(CTileGroup)
protected:
	CString m_pszTitle;    // name of this tilegroup
    int *m_piTiles;        // array of tiles 
	int m_iGroupWidth;
	int m_iGroupHeight;
	int m_iSel;
	int m_iALayers;
	CArray<int, int> m_sGroup2;
	BOOL m_bBase;
	BOOL m_bMLayer;
	BOOL m_bGroup2;
	CPtrList m_sALayers;
    
	BOOL CopyLayer(int iCol, int iRow, CTileLayer *pLayer);
	BOOL AddALayer(int iCol, int iRow, CAttributeLayer *pLayer);
	BOOL DoLayer(int iCol, int iRow, int iMCol, int iMRow, CTileLayer *pLayer);
	BOOL DoALayer(int iCol, int iRow, int iMCol, int iMRow, CAttributeLayer *pLayer);

public:
	void ReplaceTiles(CTileList& repList);
	void ReplaceTile(int iTile, int iReplacement);
	void RemoveTile(int iTile);
	// Constructors
	CTileGroup(); 
	CTileGroup(LPCTSTR pszTitle, int iWidth = 0, int iHeight = 0);

	// Destructors
	virtual ~CTileGroup(); 
   	void DeleteContents();

	// Attributes
	CString GetTitle() { return m_pszTitle; } 
    CSize GetSize() { return CSize(m_iGroupWidth, m_iGroupHeight); }

	// Operations
	void SetTitle(LPCTSTR pszTitle) { m_pszTitle = pszTitle; }
    int GetTile(int iRow, int iColumn);
	void SetTile(int iRow, int iColumn, int iTile);
	int SetSize(int iWidth, int iHeight);
	void Copy(CTileGroup* pGroup);
	virtual void Serialize(CArchive& ar);

	void GetMLayer(int iCol, int iRow, CMapEditorDoc *pDoc);
	BOOL DoMLayer(int iCol, int iRow, int iMCol, int iMRow, CMapEditorDoc *pDoc);
	BOOL CopyMLayerToGroup(CTileGroup *pGroup);

	// Operators
	void operator=(CTileGroup& src) { Copy(&src);}

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif
};

void AFXAPI SerializeElements( CArchive& ar, CTileGroup* pGroup, int iCount);
#endif