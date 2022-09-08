// ComputeLayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "ComputeLayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComputeLayerDlg dialog


CComputeLayerDlg::CComputeLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComputeLayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComputeLayerDlg)
	m_iValue = 0;
	//}}AFX_DATA_INIT
	m_pSourceLayer = NULL;
}


void CComputeLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComputeLayerDlg)
	DDX_Control(pDX, IDC_SOURCE_LAYER, m_layerCtrl);
	DDX_Text(pDX, IDC_INPUT_VALUE, m_iValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComputeLayerDlg, CDialog)
	//{{AFX_MSG_MAP(CComputeLayerDlg)
	ON_CBN_SELCHANGE(IDC_SOURCE_LAYER, OnSelchangeSourceLayer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComputeLayerDlg message handlers

BOOL CComputeLayerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	POSITION pos = m_attributeLayerList.GetHeadPosition();
	while (pos != NULL)
	{
		CAttributeLayer *pLayer = m_attributeLayerList.GetNext(pos);
		ASSERT(pLayer != NULL);

		int iIndex = m_layerCtrl.AddString(pLayer->GetTitle());
		ASSERT(iIndex >= 0);
		m_layerCtrl.SetItemData(iIndex, (unsigned long)pLayer);
	}
	m_layerCtrl.SetCurSel(0);
	m_pSourceLayer = m_attributeLayerList.GetHead();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CComputeLayerDlg::OnSelchangeSourceLayer() 
{
	int index = m_layerCtrl.GetCurSel();
	if (index >= 0)
	{
		m_pSourceLayer =  (CAttributeLayer *)m_layerCtrl.GetItemData(index);
	}
}
