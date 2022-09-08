#ifndef _TILELISTBOX_
#define _TILELISTBOX_
#include "TileSet.h"

// CTileListBox: scrollable/selectable list of tiles
//
// TBD: rather than having one listbox class that handles tiles, groups, 
// and categories we might want to have 3 different flavors of listbox
// and have CTileListView instantiate the correct flavor when needed.
//
class CTileListBox : public CListBox
{
protected:
	// Attributes
    CTileSet *m_pTileSet; // image data for this tileList
    int m_iItemWidth;
	int m_iItemHeight;
    int m_iInnerWidth;
	int m_iInnerHeight;
    int m_iFontHeight;
    int m_iLastItem;
    int m_iViewType;     // TSV_xxx : determines how items are drawn
    CSize m_groupTileSize;

public:
    void ClearSelection() { SetSel(-1,FALSE); }
	void ResetSelection(int iIndex);
	CTileListBox();
	void InitContent();
	void ResetContent();

	// Operations
	virtual int AddItem(int iItem);
	virtual void UseTileSet(CTileSet *pTileSet, int iViewType);
    int GetLastItem() { return m_iLastItem; }
    
	// Implementation
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCIS);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTileListBox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

// CDupListBox: scrollable/selectable list of tiles and their duplicates
class CDupListBox : public CTileListBox
{
public:
	CDupListBox();
	virtual ~CDupListBox();
	virtual void UseTileSet(CTileSet *pTileSet);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

protected:
	HBITMAP m_hCrossBitmap;
	HBITMAP m_hCheckBitmap;
	CSize m_indicatorSize;   // max size of cross/check

	//{{AFX_MSG(CDupListBox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
