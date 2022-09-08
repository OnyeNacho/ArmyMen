#ifndef _ATTRIBUTE_LAYER_H_
#define _ATTRIBUTE_LAYER_H_

#include "MapLayer.h"
#include "Attribute.h"
#include "MapObject.h"

class CTileLayer;
class CAttributeUndo;

typedef CTypedPtrList<CPtrList,CAttributeUndo *> CAttributeUndoList;

typedef enum
{
	EAttrSolid = 0,
	EAttrGreyscale,
	EAttrInvertedGreyscale,
} CAttrColorType;   // attribute color types

typedef unsigned short ATTRIBUTE_FLAGS;

#define ATTRIBUTE_SELECTED    0x0001
#define ATTRIBUTE_OVERRIDDEN  0x0002

/* For now, we just allocate a short per attribute but when I can figure out
** how to make this efficiently use BYTE, SHORT, or LONG based on the
** number of bits needed, I will. I'd love to use a template class but
** the MFC serialization and message map macros don't work with it.
*/

/*
** Note: the CTypedPtrList casting macros seems to require that
** the CMapLayer class be declared first in order for the casting
** mechanism to work correctly.  
**
** TBD: do I have to provide a cast operator for this class to 
** really avoid the dependency?
*/
class CAttributeLayer : public CMapLayer, public CAttribute
{
protected:  
	BOOL m_bShowObjectAttributes;// true to display object attributes 
	BOOL m_bUpdateDefault;       // true to update default value for corresponding tile
	BOOL m_bUpdateTiles;         // true to update all locations matching corresponding tile
	CTileLayer *m_pTileLayer;    // corresponding tile layer

	COLORREF m_color;            // color used for display
	CAttrColorType m_eColorType; // type of color used for display

	ATTRIBUTE_BASE_TYPE m_currentValue;     // [0..m_maxValue]

	UINT m_nSelected;		// number of selected attributes
	CSize m_size;			// number of attribute-tiles cx=wide,cy=high
	UINT m_nAttributeCount; // = m_size.cx * m_size.cy
	ATTRIBUTE_BASE_TYPE *m_pData;          

	CAttributeUndoList m_undo;  
	CAttributeUndoList m_redo;

	BOOL m_bValidObjectMap;
    CMap<CMapObjectInst *, CMapObjectInst *,ATTRIBUTE_BASE_TYPE,ATTRIBUTE_BASE_TYPE> m_objectMap; // map object ptr to attribute value
    CMap<ATTRIBUTE_BASE_TYPE*,ATTRIBUTE_BASE_TYPE*,ATTRIBUTE_BASE_TYPE,ATTRIBUTE_BASE_TYPE> m_attrOverrides;

public:
	// Construction
	CAttributeLayer(CMapEditorDoc *pMap, LPCSTR lpszTitle, UINT nBitCount, int defaultValue=0);

	// Attributes
	int GetCurrentValue() { return m_currentValue; }
    COLORREF GetColor()   { return m_color; }
	CSize GetSize() { return m_size; }
	virtual BOOL IsSelected() { return m_nSelected > 0; }
	virtual int GetAttribute(int iRow, int iColumn);
	virtual int GetAttribute(int iRow, int iColumn,  ATTRIBUTE_FLAGS* pFlags, BOOL bUseOverrides);
	virtual int GetAttribute(int iRow, int iColumn,  ATTRIBUTE_FLAGS* pFlags)
	{
		return GetAttribute(iRow,iColumn, pFlags, m_bShowObjectAttributes);
	}
	virtual CAttrColorType GetColorType() { return m_eColorType; }
    virtual BOOL GetShowObjectAttributes() { return m_bShowObjectAttributes; }
    virtual void UpdateOverrides();

    // Operations
	BOOL SetCurrentValue(int iValue);
	void SetColor(COLORREF color);
	void SetColorType(CAttrColorType eColorType);
    void SetUpdateDefault(BOOL bUpdate) { m_bUpdateDefault = bUpdate; }
	void SetUpdateTiles(BOOL bUpdate) { m_bUpdateTiles = bUpdate; }
	void SetTileLayer(CTileLayer *pLayer) { m_pTileLayer = pLayer; }
	virtual ATTRIBUTE_BASE_TYPE *SetAttribute(int iRow, int iColumn, int iValue, CAttributeUndo *pUndo=NULL);  
	void GetObjectAttribute(CMapObjectInst *pInstance, CPoint hotSpot, CAttributeInfo& rInfo);
    void AdjustObjectAttribute(CMapObjectInst *pInstance, const CAttributeInfo& rInfo);
	void RemoveObjectAttribute(CMapObjectInst *pInstance);
    void SetShowObjectAttributes(BOOL bShowThem); 

	// Overrides
	virtual ~CAttributeLayer();
	virtual void Deactivate();
	virtual CString GetInfo();
	virtual void SetMap(CMapEditorDoc *pMap);
	virtual CRect GetSelection();
	virtual CMapLayerMode PlaceItem(CPoint point, int iRow, int iColumn);
	virtual CMapLayerMode ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected);
	virtual CMapLayerMode SelectItem(CPoint point, int iRow, int iColumn, BOOL bSelected);
	virtual CMapLayerMode GetItem(CPoint point, int iRow, int iColumn);

	virtual void Draw(HDC hdc, CPoint offset, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol);
	virtual void Select(CRect rect, BOOL bSelected);
	virtual void SelectNone();
	virtual CMapLayer *CropToSelection(CRect rect, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol, BOOL bSelectedOnly);

	virtual void ClearUndo();
	virtual void EndEdit();
	virtual void BeginEdit();
    virtual void Activate(BOOL bRefresh);
    virtual void Rename(const CString& pszName);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeLayer)
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

// Implementation
protected:
	void InitAttributeLayer(int nBitCount, int nDefaultValue, int iWidth, int iHeight);
	void ValidateObjectMap();
    inline ATTRIBUTE_BASE_TYPE *GetAttributePointer(int iRow,int iColumn);
	virtual CRect GetSelectionGroup();
	virtual void DoCutCopy(BOOL bCut);
	virtual void ClearRedo();
	virtual void DoUndoRedo(CAttributeUndoList& src, CAttributeUndoList& dst);
	virtual CAttributeUndo *GetCurrentUndo() 
	{ 
			return m_undo.IsEmpty() ? NULL : m_undo.GetHead(); 
	}
	virtual void FillLayer(int iValue);
	virtual BOOL SelectAttribute(int iRow, int iColumn, BOOL bSelected);
	virtual BOOL ToggleAttribute(int iRow, int iColumn);
	virtual void SetSize(int iWidth, int iHeight); // size in tiles
	virtual void InvalidateLayer(int iRow, int iColumn);
	virtual void GetRowColumn(CPoint pt, int& iRow, int& iColumn, BOOL bRoundUp);
	virtual void LayerToMapRect(CRect&  rect);

	DECLARE_SERIAL(CAttributeLayer)
	CAttributeLayer(); 
	
	// Generated message map functions
	//{{AFX_MSG(CAttributeLayer)
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditCutCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnDecrementAttribute();
	afx_msg void OnIncrementAttribute();
	afx_msg void OnUpdateItemType(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemId(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemInfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnLayersCompute();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif
