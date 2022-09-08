// ComputeLayerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComputeLayerDlg dialog
#include "AttributeLayer.h"

class CComputeLayerDlg : public CDialog
{
// Construction
public:
	CAttributeLayer *m_pSourceLayer;
	CTypedPtrList<CObList,CAttributeLayer *>  m_attributeLayerList;
	CComputeLayerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComputeLayerDlg)
	enum { IDD = IDD_COMPUTE_LAYER };
	CComboBox	m_layerCtrl;
	int		m_iValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComputeLayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CComputeLayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSourceLayer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
