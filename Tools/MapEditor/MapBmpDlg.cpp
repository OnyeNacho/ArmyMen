// MapBmpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "MapBmpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMapBmpDlg dialog


CMapBmpDlg::CMapBmpDlg(CWnd* pParent /*=NULL*/, UINT nWidth, UINT nHeight, UINT nDepth)
	: CDialog(CMapBmpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapBmpDlg)
	m_nHeight = nWidth;
	m_nWidth = nHeight;
	m_nExportWidth = nWidth;
	m_nExportHeight = nHeight;
	m_nExportDepth = nDepth;
	m_nPercentage = 100;
	m_iExportType = 0;
	m_iExportLayers = 0;
	//}}AFX_DATA_INIT
}


void CMapBmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapBmpDlg)
	DDX_Control(pDX, IDC_BITMAP_PROPERTIES, m_propCtrl);
	DDX_Control(pDX, IDC_BITMAP_DEPTH, m_depthCtrl);
	DDX_Text(pDX, IDC_BITMAP_WIDTH, m_nExportWidth);
	DDX_Text(pDX, IDC_BITMAP_HEIGHT, m_nExportHeight);
	DDX_Text(pDX, IDC_BITMAP_PERCENTAGE, m_nPercentage);
	DDV_MinMaxUInt(pDX, m_nPercentage, 1, 500);
	DDX_Radio(pDX, IDC_EXPORT_STANDARD, m_iExportType);
	DDX_Radio(pDX, IDC_EXPORT_ALL, m_iExportLayers);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapBmpDlg, CDialog)
	//{{AFX_MSG_MAP(CMapBmpDlg)
	ON_EN_KILLFOCUS(IDC_BITMAP_PERCENTAGE, OnKillfocusBitmapPercentage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapBmpDlg message handlers

BOOL CMapBmpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString depthString,propString;
	char pszWidth[20],pszHeight[20];
	int nIndex;

	switch(m_nExportDepth)
	{
		case 16:
			nIndex = 8;
			break;
		case 24:
			nIndex = 9;
			break;
		case 32:
			nIndex = 10;
			break;
		default:
			ASSERT(m_nExportDepth > 0 && m_nExportDepth <= 8);
			nIndex = m_nExportDepth - 1;
			break;
	}
	m_depthCtrl.SetCurSel(nIndex);

	m_depthCtrl.GetLBText(nIndex, depthString);
	AfxFormatString2(propString,IDS_BITMAP_PROPERTIES,
		itoa( m_nWidth, pszWidth, 10),
		itoa( m_nHeight, pszHeight, 10));

	propString += depthString;
	m_propCtrl.SetWindowText(propString);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CMapBmpDlg::OnOK() 
{
	int nIndex = m_depthCtrl.GetCurSel();
	switch(nIndex)
	{
		case 8:
			m_nExportDepth = 16;
			break;
		case 9:
			m_nExportDepth = 24;
			break;
		case 10:
			m_nExportDepth = 32;
		default:
			ASSERT(nIndex >= -1 && nIndex <= 7);
			if (nIndex == -1) 
			{
				nIndex = 0;
			}
			m_nExportDepth = nIndex + 1;
	}
	CDialog::OnOK();
}

void CMapBmpDlg::OnKillfocusBitmapPercentage() 
{
	UpdateData(TRUE);
	m_nExportWidth  = min(max((m_nPercentage * m_nWidth) / 100, 1), 65535);
	m_nExportHeight = min(max((m_nPercentage * m_nHeight) / 100, 1), 65535);
	UpdateData(FALSE);
}	

