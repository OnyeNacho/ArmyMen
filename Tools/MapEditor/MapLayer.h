#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

class CMapEditorDoc;
class CTileSet;
class CObjectSet;
class CMapFrame;
class CScenarioSet;
class CDIB;

/////////////////////////////////////////////////////////////////////////////
// CMapLayer command target

enum CMapLayerMode 
{
	none, 
	placeItem,
	selectItem, 
	selectArea, 
	selectAreaDone, 
	selectClone, 
	cloneItem, 
	moveItem,
	viewReposition,
};

class CMapLayer : public CCmdTarget
{
protected:
	BOOL OpenClipboard();
	CMapEditorDoc *m_pMap;
	CString m_pszTitle;
    BOOL m_bVisible;

// Attributes
public:
	CPoint m_last;         // last selected point or column/row
	CPoint m_movelast;
	CScenarioSet * GetScenarioSet();
	CMapFrame * GetParentFrame();
	CMapEditorDoc *GetMap();
	CTileSet *GetTileSet();
	CPalette *GetPalette();
	virtual CObjectSet *GetObjectSet();
	virtual LPCTSTR GetTitle() { return m_pszTitle; }
	virtual BOOL IsVisible() { return m_bVisible; }
	virtual BOOL IsSelected() { return FALSE; }
	virtual BOOL IsTileBased() { return TRUE; }
	virtual BOOL IsConstrained() { return TRUE; } // selection constrained to tile boundaries
	virtual BOOL IsTransparent() { return FALSE; }
	virtual CRect GetSelection();
    virtual CString GetInfo()  
    {
		CRuntimeClass *pClass = GetRuntimeClass();
		CString name = pClass->m_lpszClassName;
		return name.Right(name.GetLength()-1); // remove the leading "C"
	}

// Operations
public:
	virtual ~CMapLayer();
	virtual BOOL SetVisible(BOOL bVisible = TRUE);
	virtual void SetTitle(LPCTSTR lpszTitle) { m_pszTitle = lpszTitle; }
	virtual void Rename(const CString& pszName) { m_pszTitle = pszName; }
	virtual void SetMap(CMapEditorDoc *pMap) { m_pMap = pMap; }
	virtual void Select(CRect rect, BOOL bSelected){}
	virtual void SelectNone();
	virtual CMapLayer *CropToSelection(CRect rect, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol, BOOL bSelectedOnly);

	virtual void Draw(HDC hdc, CPoint offset, CRect rect, HPALETTE hPalette, CDIB *pDst)
	{
		Draw(hdc,offset,rect,hPalette);
	}
	virtual void Draw(HDC hdc, CPoint offset, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol, CDIB *pDst)
	{
		Draw(hdc,offset,iStartRow,iStartCol,iEndRow,iEndCol);
	}
	virtual void Activate(BOOL bRefresh=FALSE);  
	virtual void Deactivate();
    virtual void BeginEdit() {}   // begin a new edit
	virtual void EndEdit() {}     // must be safe to call when no matching BeginEdit
	virtual void ClearUndo() {}
    virtual void SingleStep() {}
	// operations on layer items,
	// the point passed in is always in map coordinates
	// the row column is always a map relative
	// the method generally returns true if the action was taken
	virtual CMapLayerMode PlaceItem(CPoint point, int iRow, int iColumn) { return none; }
	virtual CMapLayerMode ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected) { return none; }
	virtual CMapLayerMode SelectItem(CPoint point, int iRow, int iColumn, BOOL bSelected=TRUE) { return none; }
	virtual CMapLayerMode GetItem(CPoint point, int iRow, int iColumn) { return none; }
	virtual void MoveItem(CPoint point, int iRow, int iColumn) {}
	virtual BOOL PreviewItem(CPoint point, int iRow, int iColumn) { return FALSE; }
    virtual void DrawPreview(HDC hdc, CPoint offset, CDIB *pDIB) {}
    virtual afx_msg LRESULT OnFindReplace(WPARAM wParam, LPARAM lParam) { return 0; } // TBD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapLayer)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMapLayer();           // protected constructor used by dynamic creation
	DECLARE_SERIAL(CMapLayer)
	virtual void SetModifiedFlag();
	virtual void Invalidate(int iRow, int iColumn);
	virtual void Invalidate(LPRECT lpRect=NULL);
    virtual void Invalidate(int iStartRow, int iStartCol, int iEndRow, int iEndCol);
	virtual void NeedsUpdate();
    virtual void UpdateItemPos(int iRow=-1, int iColumn=-1); // negative values reset pos to empty
	virtual void UpdateItemPos(CPoint point);

	// basic drawing routines: these can go away when all the layers handle 
	// the extended drawing correctly
	virtual void Draw(HDC hdc, CPoint offset, CRect rect, HPALETTE hPalette);
	virtual void Draw(HDC hdc, CPoint offset, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol);
	// Generated message map functions
	//{{AFX_MSG(CMapLayer)
	afx_msg void OnUpdateEditSelectNone(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectNone();
	afx_msg void OnUpdateItemPos(CCmdUI *pCmdUI);
	afx_msg void OnUpdateItemNone(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


typedef CTypedPtrList<CObList,CMapLayer *> CLayersList;
/////////////////////////////////////////////////////////////////////////////

#endif
