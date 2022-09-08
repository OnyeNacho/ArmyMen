#ifndef _MAPEDITORDOC_H_
#define _MAPEDITORDOC_H_
/////////////////////////////////////////////////////////////////////////////
// MapEditorDoc.h : interface of the CMapEditorDoc class
/////////////////////////////////////////////////////////////////////////////
#include "TileSet.h"
#include "ObjectSet.h"
#include "MapLayer.h"
#include "ScenarioSet.h"

class CMapLayer; 
class CTileLayer;
class CObjectLayer;
class CScenarioLayer;
class CLayersDlg;
class CAttributeLayer;

// LParam codes with CMapEditorView::OnUpdate
//
// TBD: it might make more sense to have a global list of hints that can be
// passed to all views class instead of having a seperate set of hints for each
// view class..
#define MEV_UPDATE_SIZE			    0x0001      // map or tile dimensions resized.
#define MEV_UPDATE_PREVIEW		    0x0002      // current preview area changed
#define MEV_UPDATE_TRANSPARENT	    0x0004      // tileset transparency color changed
#define MEV_UPDATE_LAYER            0x0008      // active layer changed.
#define MEV_UPDATE_PALETTE          0x0010      // update the palette
#define MEV_UPDATE_ATTRIBUTE_FORMAT 0x0020      // update attribute hex/decimal format
#define MEV_UPDATE_ATTRIBUTE_VALUE  0x0040      // update current attribute value
#define MEV_UPDATE_POSITION         0x0080      // scroll the map to show selected point


#define MEV_TIMER_ID 5
#define MEV_TIMER_VAL 30

class CMapEditorDoc : public CDocument
{
	friend class CLayersDlg;

	DECLARE_SERIAL(CMapEditorDoc);

protected: 
	void InitContents();
	void ControlHideActiveLayer();
	CAttributeLayer * CreateAttributeLayer(LPCTSTR lpszName, int iBitCount, int iDefaultValue, BOOL bVisible);
	void GetArmyMenAttribute(char *pData, CAttributeLayer *pAttribute, int iMax, int iShift);
	void GetArmyMenShortAttribute(short *pData, CAttributeLayer *pAttribute);
	CLayersList m_layers;   
	CMapLayer *m_pActiveLayer;

	CString m_pszTileSetPath;        // path to this tileSet
    CTileSet* m_pTileSet;		     // tileSet to use for this map

	CString m_pszObjectSetPath;      // path to this objectSet
	CObjectSet *m_pObjectSet;        // objectSet to use for this map

	CString m_pszScenarioSetPath;    // path to this scenarioSet
	CScenarioSet *m_pScenarioSet;    // scenarioSet to use for this map

	CRect m_previewRect;             // preview area: for moving groups/objects around map
    BOOL m_bGrid;
    BOOL m_bAnimating;

public:
	CString NewLayerName(int iLayerNameID);
	void RedoAttributes();
	void UndoAttributes();
	void EndEditAttributes();
	void BeginEditAttributes();
	void SetAttributes(int iRow, int iColumn, int iTile);
	CString* GetObjectPath() {return &m_pszObjectSetPath;}

	int m_iMapWidth;        // width in tiles
	int m_iMapHeight;       // height in tiles
	BOOL m_bNeedsUpdate;    
    BOOL m_bOldDataFormat;  // TBD: this is temporary!
	COLORREF m_rgbBackground;
	CString m_pszDescription;
	CString m_sAFile;
	CString m_sPFile;
	CString m_sAText;
	CString m_sPText;
	int m_iBX;
	int m_iBY;
	int m_iEX;
	int m_iEY;

	BOOL UsingTransparency();
    BOOL HasPreview() { return !m_previewRect.IsRectEmpty(); }

    BOOL IsAnimating() { return m_bAnimating; }
    void SetAnimating(BOOL bAnimating) { m_bAnimating = bAnimating; }

	void SingleStep();
	void RemoveTile(int iTile);
	void ReplaceTile(int iTile, int iReplacement);
    void ReplaceTiles(CTileList& repList);
	void UpdateTileUsage(CTileList& usage);

	CMapLayerMode GetItem(CPoint point, int iRow, int iColumn);
	CMapLayerMode PlaceItem(CPoint point, int iRow, int iColumn);
	CMapLayerMode SelectItem(CPoint point, int iRow, int iColumn, BOOL bSelected = TRUE);
	CMapLayerMode ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected);
    BOOL PreviewItem(CPoint point, int iRow, int iColumn);
    void MoveItem(CPoint point, int iRow, int iColumn);

	void UpdateTiles(int iStartTile, int iEndTile);
	void Invalidate(LPRECT lpRect);
	void Invalidate(int iRow, int iColumn);
	BOOL GetBoundingRect(CRect clip, CRect& bounds);
	void ClearPreviewRect();
	void SetPreviewRect(CRect rect);
	void DeleteContents();
	void DeleteLayers();
   
	CSize GetSize();
	BOOL GetGrid() { return m_bGrid; }
	CTileSet *GetTileSet() { return m_pTileSet; } 
    CPalette *GetPalette() { return m_pTileSet ? m_pTileSet->GetPalette() : NULL; }
	HPALETTE GetHPalette() { return m_pTileSet ? m_pTileSet->GetHPalette() : NULL; }
    CRect GetPreviewRect() { return m_previewRect; }
    CObjectSet *GetObjectSet() { return m_pObjectSet; }
    CScenarioSet *GetScenarioSet() { return m_pScenarioSet; }

    CMapLayer *GetActiveLayer() { return m_pActiveLayer; }
	POSITION GetFirstLayer()    { return m_layers.GetHeadPosition(); }
	CMapLayer *GetNextLayer(POSITION& rpos) { return m_layers.GetNext(rpos); }
	POSITION GetLayerPosition(int iIndex) { return m_layers.FindIndex(iIndex); }
    CMapLayer *GetLayerAt(POSITION pos) { return m_layers.GetAt(pos); }

	void UpdateObjects();
	void BuildObjectTable();
	void DeleteObjectTable();
	void UpdateScenarios();

	CMapObjectInst * GetObjectInstance(int iIndex);
	int GetObjectIndex(CMapObjectInst *pInstnace);
	int GetAttributeCount();
	POSITION GetFirstAttribute();
	CAttributeLayer *GetNextAttribute(POSITION& pos);

	void EndEdit();
	void BeginEdit();

	BOOL ResizeMap(int iNewWidth, int iNewHeight);
	BOOL UseTileSet(CString pszPathName);
	BOOL UseObjectSet(CString pszPathName);
    BOOL UseScenarioSet(CString pszPathName);

	CRect GetTileRect(int iRow, int iColumn);
    CPoint GetTileOffset(int iRow, int iColumn);
	BOOL GetRowColumn(CPoint point, int& iRow, int& iColumn);
    BOOL GetRowColumn(CPoint point, int& iRow, int& iColumn, BOOL bRoundUp, BOOL bClip = FALSE);
	void Select(CRect& rect, BOOL bSelected = TRUE);
	void Draw(HDC hdc, CRect rect, CDIB *pDst = NULL, HBITMAP hBitmap = NULL);
	BOOL SelectActiveLayer(int iLayerIndex, BOOL bHideCurrent);
	void SetGrid(BOOL bGrid) { m_bGrid = bGrid; }
	void SelectNone() { OnEditSelectNone(); }
	void InitFrameLayersList();
	CMapLayer *FindLayer(const CString& title);
    void AddLayer(CMapLayer *pLayer) 
	{
		m_layers.AddTail(pLayer);
		SetModifiedFlag();
		if (pLayer->IsVisible())
		{
			SetActiveLayer(pLayer); 
			UpdateAllViews(NULL);
		}
	}	
	void UpdateAttributeFormat();
	BOOL ResolveAttributeConflicts(CTileSet *pTileSet);
    CAttributeLayer *FindAttribute(CString pszName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Rotate(int iType, int iDir);
	BOOL Expand(int iMove, int iWidth, int iHeight);
	virtual ~CMapEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CTileLayer *CreateTileLayer(int iLayerNameID, BOOL bTransparent, int defaultTile);
	CTileLayer *CreateBaseLayer();
	CTileLayer *CreateOverlayLayer();
	CObjectLayer *CreateObjectLayer();
	CAttributeLayer * CreateAttributeLayer();
    CScenarioLayer *CreateScenario();
	void SetActiveLayer(CMapLayer *pLayer);
	CMapLayer  *SetActiveLayer(BOOL bNext=TRUE,POSITION startPos=NULL);
	CMap<int,int,CString,CString&> m_objectTable;

	void ExportBitmap(LPCSTR lpszPathName);
	void ExportArmyMen(LPCSTR lpszPathName);
	BOOL InitDocument();
	CMapEditorDoc();          // create from serialization only


// Generated message map functions
protected:
	//{{AFX_MSG(CMapEditorDoc)
	afx_msg void OnFileRevert();
	afx_msg void OnUpdateFileRevert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCrop(CCmdUI* pCmdUI);
	afx_msg void OnEditCrop();
	afx_msg void OnUpdateEditSelectNone(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectNone();
	afx_msg void OnFileExport();
	afx_msg void OnUpdateEditWithAttributes(CCmdUI* pCmdUI);
	afx_msg void OnEditWithAttributes();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateLayersActivate(CCmdUI* pCmdUI);
	afx_msg void OnLayersActivateTop();
	afx_msg void OnLayersActivateBottom();
	afx_msg void OnLayersActivateNext();
	afx_msg void OnLayersActivatePrevious();
	afx_msg void OnLayersArrange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CTileLayer *g_pTileLayer;
/////////////////////////////////////////////////////////////////////////////
#endif
