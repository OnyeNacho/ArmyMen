// TileSetView.h : header file
//
#include "TileSet.h"
#include "TileSetOp.h"
#include "TileListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CTileSetView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


#define N_TILESET_FORMATS 1

class CTileSetView : public CFormView
{
protected:
	CCategory * GetCurrentCategory();
	// cut and paste operations...
	void DoCut(CTileSetOp& op);
	void DoPaste(CTileSetOp& op);
	void DoPaste(CArchive&ar, UINT nFormat);
    void DoCutCopy(CArchive& ar, BOOL bCut);
	void DoCopyGroups(CTileSetOp& op);
	void DoCopyTiles(CTileSetOp& op);
	BOOL DoPasteTiles(CTileSetOp& op);
	BOOL DoPasteGroups(BOOL bSameTileSet, CTileSetOp& op);
	UINT m_pnClipboardFormats[N_TILESET_FORMATS];  //priority list for clipboard formats

	CTileSetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTileSetView)

public:
	int m_iCurrentView;
	int m_iTileCategory;
	int m_iGroupCategory;
	// Form Data
	//{{AFX_DATA(CTileSetView) 
	enum { IDD = IDD_TILESET };
	CTabCtrl	m_categoryCtrl;
	CTabCtrl	m_viewCtrl;
	CColorButton m_transCtrl;
	CTileListBox m_listCtrl;
	CButton	m_itemCtrl;
	//}}AFX_DATA

public:
	// Attributes
	BOOL IsSelected();
	BOOL ReadOnly();

	// Operations
    CPalette *GetPalette() { return GetDocument()->GetPalette(); }
	BOOL RealizePalette(BOOL bForceBkgnd);

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTileSetView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTileSetView();
	void AdjustControls();
	void RenewListCtrl(BOOL bRepaint = TRUE);
	void RenewTabCtrl(BOOL bRepaint = TRUE);
	void RenewItemCtrl(BOOL bRepaint = TRUE);
	void FillGroupView();
	void FillTileView();
	CTileSet *GetDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTileSetView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
    afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnSelchangeTilesetTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSelchangeTilesetList();
	afx_msg void OnTilesetFindDup();
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnTransparentColor();
	afx_msg void OnUpdateEditSelectNone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTilesetFindDup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTilesetShowusage(CCmdUI* pCmdUI);
	afx_msg void OnTilesetShowusage();
	afx_msg void OnSelchangeTilesetView(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditProperties();
	afx_msg void OnUpdateEditAttributes(CCmdUI* pCmdUI);
	afx_msg void OnEditAttributes();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TileSetView.cpp
inline CTileSet* CTileSetView::GetDocument()
   { return (CTileSet*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
