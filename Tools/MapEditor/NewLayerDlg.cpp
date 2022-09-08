// NewLayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "NewLayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewLayerDlg dialog


CNewLayerDlg::CNewLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewLayerDlg::IDD, pParent)
{
	int m_layerType = 0;
	//{{AFX_DATA_INIT(CNewLayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNewLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewLayerDlg)
	DDX_Control(pDX, IDC_LAYER_TYPE, m_typeCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewLayerDlg, CDialog)
	//{{AFX_MSG_MAP(CNewLayerDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewLayerDlg message handlers

BOOL CNewLayerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString string;

	// TBD: set the item data to the function used to create map layer
	VERIFY(string.LoadString(IDS_BASE_LAYER));
	m_typeCtrl.AddString(string);
	
	VERIFY(string.LoadString(IDS_OVERLAY_LAYER));
	m_typeCtrl.AddString(string);

	VERIFY(string.LoadString(IDS_OBJECT_LAYER));
	m_typeCtrl.AddString(string);

	VERIFY(string.LoadString(IDS_ATTRIBUTE_LAYER));
	m_typeCtrl.AddString(string);

	VERIFY(string.LoadString(IDS_SCENARIO));
	m_typeCtrl.AddString(string);

	VERIFY(string.LoadString(IDS_DOORWAY));
    m_typeCtrl.AddString(string);  

	m_typeCtrl.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CNewLayerDlg::OnOK() 
{
	m_layerType = m_typeCtrl.GetCurSel();
	CDialog::OnOK();
}
