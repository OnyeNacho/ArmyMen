// MapBmpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapBmpDlg dialog

class CMapBmpDlg : public CDialog
{
// Construction
public:
	CMapBmpDlg(CWnd* pParent,UINT nWidth,UINT nHeight,UINT nDepth);   

	enum CMapBmpExportLayers { export_all = 0, export_visible, export_active };
	enum CMapBmpExportType { export_same = 0, export_custom };

// Dialog Data
	//{{AFX_DATA(CMapBmpDlg)
	enum { IDD = IDD_EXPORT_MAPBMP };
	CStatic	m_propCtrl;
	CComboBox	m_depthCtrl;
	UINT	m_nHeight;
	UINT	m_nWidth;
	UINT    m_nExportWidth;
	UINT    m_nExportHeight;
	UINT    m_nExportDepth;
	UINT	m_nPercentage;
	int		m_iExportType;
	int		m_iExportLayers;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapBmpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapBmpDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKillfocusBitmapPercentage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
