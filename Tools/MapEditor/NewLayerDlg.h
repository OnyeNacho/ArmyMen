// NewLayerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewLayerDlg dialog
class CNewLayerDlg : public CDialog
{
// Construction
public:
	enum CLayerType 
	{ 
		eBaseLayer=0, 
		eOverlayLayer, 
		eObjectLayer, 
		eAttributeLayer, 
		eScenarioLayer, 
		eDoorwayLayer        
	};

	int m_layerType;
	CNewLayerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewLayerDlg)
	enum { IDD = IDD_NEWLAYER };
	CListBox	m_typeCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewLayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNewLayerDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
