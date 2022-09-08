// LayerBar.h : header file
//
#ifndef _LAYERBAR_H_
#define _LAYERBAR_H_

#include "BoldComboBox.h"

class CMapEditorDoc; // forward 

/////////////////////////////////////////////////////////////////////////////
// CLayerBar dialog

class CLayerBar : public CDialogBar
{
// Construction
public:
	CMapEditorDoc * GetActiveMap();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL Create( CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID );
	CLayerBar();   // standard constructor

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

// Dialog Data
	//{{AFX_DATA(CLayerBar)
	enum { IDD = CG_IDD_LAYERBAR };
	CBoldComboBox	m_layerCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayerBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;

	// Generated message map functions
	//{{AFX_MSG(CLayerBar)
	afx_msg void OnSelchangeActivateLayer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
