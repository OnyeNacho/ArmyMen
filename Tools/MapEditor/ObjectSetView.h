// ObjectSetView.h : header file
//
#ifndef _OBJECTSETVIEW_H_
#define _OBJECTSETVIEW_H_

/////////////////////////////////////////////////////////////////////////////
// CObjectSetView 

#include "ObjectListBox.h"
#include "CycleButton.h"

struct SMogObj
{
	CPoint m_sLoc;
	CString m_sID;
};

struct SMog
{
	CString m_sName;
	CPoint m_sBegin;
	CPoint m_sEnd;
	CArray<SMogObj*, SMogObj*> m_sObjs;
};

class CObjectSetView : public CFormView, public CAttributeTarget
{

// Construction
public:
	int GetMogCount();
	SMog* GetMog(int iIndex);
	void DrawMog(HDC hdc, int iIndex, RECT& dstRect, HPALETTE hPalette);
	CString GetMogName(int iIndex);
	void PlaceItem();

// Form Data
	//{{AFX_DATA(CObjectSetView)
	enum { IDD = IDD_OBJECTSET };
	CCycleButton	m_cycleButton;
	CObjectListBox	m_listCtrl;
	CTabCtrl	m_tabCtrl;
	CButton	m_itemCtrl;
	//}}AFX_DATA

	CObjectSetView(UINT nIDTemplate=CObjectSetView::IDD);   // standard constructor
	CObjectSetView::~CObjectSetView();

	// Operations
	CPalette * GetPalette();
	HPALETTE GetHPalette() 
	{ 
		CPalette *pal = GetPalette(); 
		return (pal ? (HPALETTE)pal->GetSafeHandle() : NULL);
	}
	BOOL RealizePalette(BOOL bForceBkgnd);
    CObjectSet *GetDocument();

	CPoint GetHotSpot(CMapObjectInst *pObject);
	CMapEditorDoc *GetMap();

	// AttributeTarget
	virtual int GetAttributeCount();
	virtual POSITION GetFirstAttribute();
	virtual void GetNextAttribute(POSITION& pos, void *pTargetData, CAttributeInfo& rInfo);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectSetView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL IsMog(CString &sTitle);
	void DeleteMogs();
	BOOL SaveMog(SMog *pMog, CString &sPath);
	SMog* LoadMog(CString &sPath);
	void LoadMogs();
	BOOL m_bMogsLoaded;
	CArray<SMog*, SMog*> m_sMogList;
	int m_iCategory;
    virtual void AdjustControls();
    virtual void RenewListCtrl(BOOL bRepaint=TRUE);
	virtual void RenewItemCtrl(BOOL bRepaint=TRUE);
    virtual void RenewTabCtrl(BOOL bRepaint=TRUE);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CObjectSetView)
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSelchangeObjectCategory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeObject();
	afx_msg void OnUpdateObjectRemap(CCmdUI* pCmdUI);
	afx_msg void OnObjectRemap();
	afx_msg void OnEditAttributes();
	afx_msg void OnUpdateEditAttributes(CCmdUI* pCmdUI);
	afx_msg void OnObjectCreateMOG();
	afx_msg void OnUpdateObjectCreateMOG(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CObjectSetView)
};

#ifndef _DEBUG  // debug version in ObjectSetView.cpp
inline CObjectSet* CObjectSetView::GetDocument()
   { return (CObjectSet*)m_pDocument; }
#endif

////////////////////////////////////////
#endif
