#ifndef _OBJECTLAYER_H_
#define _OBJECTLAYER_H_
#include "MapLayer.h"
#include "MapObject.h"
#include "Attribute.h"

class CObjectSetView;

class CObjectLayer : public CMapLayer, public CAttributeTarget
{
protected:
	CTypedPtrList<CObList,CMapObjectInst *> m_objects;
	UINT m_nSelected;

	CMapObjectInst * GetSelected();
	void MoveSelection(int dx, int dy);
	virtual void UpdateSelectedStatus();
	virtual void DoCutCopy(BOOL bCut);
	virtual void DoCutCopyPaste(CArchive& ar, BOOL bCut);
	virtual CMapObjectInst * AddObject(int ID, CPoint pt);
//	virtual void AddObject(CMapObjectInst *pObject) { m_objects.AddTail(pObject); }
	virtual void AddObject(CMapObjectInst *pObject);
	virtual void RemoveObjectAt(POSITION pos);
	CRect GetObjectRect(CMapObjectInst *pInstance);
	void InvalidateOb(CMapObjectInst *pObject);
	int GetCurrentItem();

// Attributes
public:
	virtual BOOL IsSelected()    { return m_nSelected > 0; }
	virtual BOOL IsTileBased()   { return FALSE; }
	virtual BOOL IsConstrained() { return FALSE; } // not constrained tile boundaries
	virtual BOOL IsTransparent() { return FALSE; } // does not use map transparency color
	virtual CRect GetSelection();

// Operations
public:
	int GetSelCount();
	UINT CountOccurrences(int iObjectID);
	int GetObjectCount() { return m_objects.GetCount(); }
	POSITION GetFirstObjectPosition() { return m_objects.GetHeadPosition(); }
	CMapObjectInst *GetNextObject(POSITION& pos) { return m_objects.GetNext(pos); }
	void OnReplace(CString pszFind,  CString pszReplace, BOOL bWholeWord, BOOL bSelectedOnly);
	void OnFindNext(CString lpszName, BOOL bSearchDown, BOOL bWholeWord);
	void CopyObjectAttributes(CObjectLayer *pNewLayer, CLayersList& rNewLayers, CRect rect, BOOL bSelectedOnly);
	CPoint GetHotSpot(CMapObjectInst *pObject);

	CObjectLayer(CMapEditorDoc *pMap, LPCSTR lpszTitle);
	virtual ~CObjectLayer();

	// operations on layer items,
	// the point passed in is always in map coordinates
	// the row column is always a map relative
	// the method generally returns true if the action was taken
	virtual CMapLayerMode PlaceItem(CPoint point, int iRow, int iColumn);
	virtual CMapLayerMode ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected);
	virtual CMapLayerMode SelectItem(CPoint point, int iRow, int iColumn, BOOL bSelected=TRUE);
	virtual CMapLayerMode GetItem(CPoint point, int iRow, int iColumn);
	virtual void MoveItem(CPoint point, int iRow, int iColumn);

#ifdef PREVIEW_OBJECT
	// don't use this until we figure out how to respond to keyboard input
	// while capturing mouse input.
	virtual BOOL PreviewItem(CPoint point, int iRow, int iColumn);
    virtual void DrawPreview(HDC hdc, CPoint offset, CDIB *pDIB);
#endif

	virtual CMapLayer *CropToSelection(CRect rect, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol, BOOL bSelectedOnly);
	virtual void Draw(HDC hdc, CPoint offset, CRect rect, HPALETTE hPalette, CDIB *pDst);
	virtual void SelectNone();
    virtual void Activate(BOOL bRefresh);
	virtual void Select(CRect rect, BOOL bSelected);
	virtual void SingleStep();

    virtual afx_msg LRESULT OnFindReplace(WPARAM wParam, LPARAM lParam);
	void ForceInside(CMapObjectInst *pInstance);

	// AttributeTarget
	virtual int GetAttributeCount();
	virtual POSITION GetFirstAttribute();
	virtual void GetNextAttribute(POSITION& pos, void *pTargetData, CAttributeInfo& rInfo);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectLayer)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL LoadDefaults(CMapObjectInst *pObj, CObjectSetView *pView);
	CMapObjectInst *m_pLastObject;
	CPoint m_lastPoint;
	virtual CMapObjectInst *FindObjectAt(CPoint point);
	virtual void DrawObjectOutline(HDC hdc, const CPoint& pt, const CSize& size, BOOL bDotted);
	virtual CMapLayer *FinishCrop(CObjectLayer *pLayer, int iExpandRow, int iExpandCol, CRect rect, BOOL bSelectedOnly);
	CMapLayerMode InitMove(CMapObjectInst *pObject, CPoint pt);
	BOOL GetLastSelected();
	CObjectLayer(); // for serialization
	DECLARE_SERIAL(CObjectLayer)

	// Generated message map functions
	//{{AFX_MSG(CObjectLayer)
	afx_msg void OnUpdateMultipleObjects(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSingleObject(CCmdUI* pCmdUI);
	afx_msg void OnObjectTop();
	afx_msg void OnObjectBottom();
	afx_msg void OnObjectForward();
	afx_msg void OnObjectBack();
	afx_msg void OnObjectLeft();
	afx_msg void OnObjectRight();
	afx_msg void OnObjectUp();
	afx_msg void OnObjectDown();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditReplace(CCmdUI* pCmdUI);
	afx_msg void OnEditReplace();
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnObjectAttributes();
	afx_msg void OnUpdateObjectAttributes(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjectSort(CCmdUI* pCmdUI);
	afx_msg void OnObjectSort();
	afx_msg void OnObjectFlipHorizontal();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
#endif
