#ifndef _TILELAYER_H_
#define _TILELAYER_H_

#include "MapLayer.h"
#include "TileSetOp.h"

class CTileUndo;

typedef CTypedPtrList<CPtrList,CTileUndo *> CTileUndoList;

class CTileLayer : public CMapLayer
{
protected:
	CTileUndoList m_undo;  
	CTileUndoList m_redo;
	UINT m_nSelected;			// number of selected tiles
	CPoint m_location;			// location of this layer on parent map
	CSize m_size;				// number of tiles cx=wide,cy=high
	BOOL m_bTransparent;		// does this layer use tileset's transparent color?
	UINT m_nTileCount;			// number of tiles.
    int *m_piTiles;				// array of m_nTileCount tiles
	int m_iOldWidth;
	int m_iOldHeight;

public:
	// Attributes
	CSize GetSize() { return m_size; }
	CPoint GetLocation() { return m_location; }
	CRect GetMinRect();
	virtual BOOL IsSelected() { return m_nSelected > 0; }
	virtual BOOL IsTransparent() { return m_bTransparent; }
	virtual int GetTile(int iRow, int iColumn);
	virtual int GetTile(int iRow, int iColumn, BOOL* pbSelected);
	
public: 
	// new public layer operations
	CTileLayer(CMapEditorDoc *pMap, LPCSTR lpszTitle,BOOL bTransparent=FALSE,int initTile=0);
	virtual void SetTile(int iRow, int iColumn, int iTile, CTileUndo *pUndo=NULL);  
	virtual void RemoveTile(int iTileIndex);
	virtual void ReplaceTile(int iTile, int iReplacement);
	virtual void UpdateTiles(int iStartTile, int iEndTile);
    virtual void ReplaceTiles(CTileList& repList);
	virtual void UpdateTileUsage(CTileList& usage);

	// Overrides
	virtual ~CTileLayer();
    virtual CString GetInfo();
	virtual void SetMap(CMapEditorDoc *pMap);
	virtual CRect GetSelection() { return GetSelectionGroup(NULL); }
	virtual CMapLayerMode PlaceItem(CPoint point, int iRow, int iColumn);
	virtual CMapLayerMode ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected);
	virtual CMapLayerMode SelectItem(CPoint point, int iRow, int iColumn, BOOL bSelected);
	virtual CMapLayerMode GetItem(CPoint point, int iRow, int iColumn);
	virtual void MoveItem(CPoint point, int iRow, int iColumn);
	virtual BOOL PreviewItem(CPoint point, int iRow, int iColumn);
	virtual void DrawPreview(HDC, CPoint offset, CDIB *pDIB);

	virtual void Draw(HDC hdc, CPoint offset, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol, CDIB *pDIB);
	virtual void Select(CRect rect, BOOL bSelected);
	virtual void SelectNone();
	virtual CMapLayer *CropToSelection(CRect rect, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol, BOOL bSelectedOnly);

	virtual void ClearUndo();
	virtual void EndEdit();
	virtual void BeginEdit();
    virtual void Activate(BOOL bRefresh);
	virtual CTileUndo *GetCurrentUndo() { return m_undo.IsEmpty() ? NULL : m_undo.GetHead(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTileLayer)
		virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

// Implementation
protected:
	inline int *GetTilePointer(int iRow, int iColumn);
	virtual void DoIncrementDecrement(BOOL bDecrement);
	virtual void ClearRedo();
	virtual void DoUndoRedo(CTileUndoList& src, CTileUndoList& dst);
	virtual void FillLayer(int initTile);
	virtual CRect GetSelectionGroup(CTileSetOp *op);
	virtual void SetSize(int iWidth, int iHeight); // size in tiles
	virtual void SetLocation(int iRow, int iColumn) { m_location.x = iColumn; m_location.y = iRow; } // in tiles
	virtual BOOL SelectTile(int iRow, int iColumn, BOOL bSelected);
	virtual BOOL ToggleTile(int iRow, int iColumn);
	virtual void InvalidateLayer(int iRow, int iColumn);
	virtual void GetRowColumn(CPoint pt, int& iRow, int& iColumn, BOOL bRoundUp);
	virtual void DoCutCopyPaste(CArchive& ar, BOOL bCut);
	virtual void RemoveSelection();
	virtual BOOL PlaceGroup(CTileGroup *pGroup, int iRow, int iColumn);
	virtual void LayerToMapRect(CRect&  rect);

	DECLARE_SERIAL(CTileLayer)
	CTileLayer(); 
	
	// Generated message map functions
	//{{AFX_MSG(CTileLayer)
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateSelection(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditUpdateAttributes(CCmdUI* pCmdUI);
	afx_msg void OnEditUpdateAttributes();
	afx_msg void OnIncrementSelection();
	afx_msg void OnDecrementSelection();
	afx_msg void OnEditRandomize();
	afx_msg void OnUpdateEditRandomize(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#endif
