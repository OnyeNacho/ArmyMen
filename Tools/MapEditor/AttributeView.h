// AttributeView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CAttributeView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "MapEditorDoc.h"
#include "AttributeLayer.h"
#include "ColorButton.h"

class CAttributeView : public CFormView
{
protected:
	void UpdateTileLayers();
	CTileLayer * GetTileLayer();
	void UpdateValueFormat();
	CAttributeLayer * m_pAttributeLayer;
	CAttributeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAttributeView)

// Form Data
public:
	//{{AFX_DATA(CAttributeView)
	enum { IDD = IDD_ATTRIBUTEVIEW };
	CComboBox	m_layerCtrl;
	CStatic	m_maxCtrl;
	CSpinButtonCtrl	m_valueCtrl;
	CSpinButtonCtrl	m_defaultCtrl;
	CColorButton	m_colorCtrl;
	int		m_iColorType;
	BOOL	m_bUpdateDefault;
	BOOL	m_bUpdateTiles;
	BOOL	m_bShowObjectAttributes;
	//}}AFX_DATA

	int m_iDefault;
	int m_iValue;

// Attributes
public:
	CMapEditorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAttributeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAttributeView)
	afx_msg void OnAttributeColor();
	afx_msg void OnDeltaposAttributeDefault(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposAttributeValue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeAttributeValue();
	afx_msg void OnChangeAttributeDefault();
	afx_msg void OnAttributeSolid();
	afx_msg void OnAttributeGreyscale();
	afx_msg void OnAttributeInvertedGrey();
	afx_msg void OnAttributeUpdateDefault();
	afx_msg void OnAttributeUpdateTiles();
	afx_msg void OnAttributeShowObjects();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MapEditorView.cpp
inline CMapEditorDoc* CAttributeView::GetDocument()
   { return (CMapEditorDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////
