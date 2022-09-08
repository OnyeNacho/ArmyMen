// DoorwayLayer.h : header file (for ArmyMen)
//
#ifndef _DOORWAYLAYER_H_
#define _DOORWAYLAYER_H_

#include "MapLayer.h"

/////////////////////////////////////////////////////////////////////////////
// CDoorwayLayer 

class CDoorwayLayer : public CMapLayer
{
// Attributes
public:
	void ComputeRoute();
	COLORREF m_lineColor;
	COLORREF m_pointColor;
	COLORREF m_routeColor;
    CPoint   m_routeStart;
	CPoint   m_routeEnd;
    int GetDoorwayCount() { return m_iDoorways; }
	BOOL GetDoorway(int iDoorway, CPoint& left, CPoint& right, BOOL& bDisplayed);
	void DisplayDoorway(int iDoorway,BOOL bDisplayIt);

// Operations
public:
	static CDoorwayLayer *Create(CMapEditorDoc *pMap);
	void SetPointColor(COLORREF color);
	void SetLineColor(COLORREF color);
	void SetRouteColor(COLORREF color);
	void SetRouteStart();
	void SetRouteEnd();
	void Compute();
	void Clear();

    BOOL IsSelected() { return m_bSelected; }

// Overrides
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

	virtual BOOL IsTileBased() { return FALSE; } // because we implement the following draw routine
	virtual void Draw(HDC hdc, CPoint offset, CRect rect, HPALETTE hPalette);
    virtual void Activate(BOOL bRefresh);
	virtual CMapLayer * CropToSelection(CRect rect, int iStartRow, int iStartCol, int iEndRow, int iEndCol, BOOL bSelectedOnly);
	virtual CMapLayerMode ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected);
	virtual CMapLayerMode PlaceItem(CPoint point, int iRow, int iColumn);
    virtual void SelectNone();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoorwayLayer)
		virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bSelected;
	int m_iDoorways;
	int m_iRoutePoints;
	struct Doorway *m_pDoorways;
    char *m_pBWDataC1; // bruce ai persistent data space
    char *m_pBWDataC2; // bruce ai persistent data space
    long *m_pBWDataL1; // bruce ai persistent data space
    long *m_pBWDataL2; // bruce ai persistent data space
    long *m_pBWDataL3; // bruce ai persistent data space
    long *m_pRoutePoints;
    CRect m_routeRect,m_doorwayRect;

	virtual ~CDoorwayLayer();
    void DeleteDoorways();
	void DeleteRoute();
	void SetPoint(CPoint& pt);
	CPoint LimitPoint(CPoint pt,int iStartRow,int iStartCol,int iEndRow, int iEndCol);

	void InvalidateRoute();
	void InvalidateDoorways();
	void DrawTile(HDC hdc, CPoint pos, CPoint offset, CRect rect, COLORREF color);
    CRect GetDoorwayRect(CPoint& left, CPoint& right);

	CDoorwayLayer();           // protected constructor used by dynamic creation
	DECLARE_SERIAL(CDoorwayLayer)

	// Generated message map functions
	//{{AFX_MSG(CDoorwayLayer)
	afx_msg void OnUpdateItemPos(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif