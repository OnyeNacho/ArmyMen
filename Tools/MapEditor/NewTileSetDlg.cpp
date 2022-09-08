// NewTileSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "NewTileSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewTileSetDlg dialog


CNewTileSetDlg::CNewTileSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewTileSetDlg::IDD, pParent)
{
	m_rgbTransparent = g_rgbTransparent;
	m_bPropertySheet = (pParent != NULL);

	//{{AFX_DATA_INIT(CNewTileSetDlg)
	m_pszData = m_bPropertySheet ? _T("") : g_pszInitTileData;
	m_nTileHeight = g_nTileHeight;
	m_nTileWidth = g_nTileWidth;
	m_nBitmapWidth = g_nBitmapWidth;
	m_bCompactOnSave = g_bCompactOnSave;
	m_bUseBitmapWidth = g_bUseBitmapWidth;
	m_sTileStat = _T("");
	m_iTiles = 0;
	//}}AFX_DATA_INIT
	m_iCurrent = 0;
	m_iInit = 0;
}


void CNewTileSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewTileSetDlg)
	DDX_Control(pDX, IDC_DATA_CTRL, m_dataGroupCtrl);
	DDX_Control(pDX, IDC_TRANSPARENT_COLOR, m_transCtrl);
	DDX_Control(pDX, IDC_TILESET_DATA, m_dataCtrl);
	DDX_Text(pDX, IDC_TILESET_DATA, m_pszData);
	DDX_Text(pDX, IDC_TILE_HEIGHT, m_nTileHeight);
	DDV_MinMaxUInt(pDX, m_nTileHeight, 1, MAX_TILE_HEIGHT);
	DDX_Text(pDX, IDC_TILE_WIDTH, m_nTileWidth);
	DDV_MinMaxUInt(pDX, m_nTileWidth, 1, MAX_TILE_WIDTH);
	DDX_Text(pDX, IDC_BITMAP_WIDTH, m_nBitmapWidth);
	DDV_MinMaxUInt(pDX, m_nBitmapWidth, 16, 65535);
	DDX_Check(pDX, IDC_COMPACT_ON_SAVE, m_bCompactOnSave);
	DDX_Check(pDX, IDC_USE_BITMAP_WIDTH, m_bUseBitmapWidth);
	DDX_Text(pDX, IDC_TILESTAT, m_sTileStat);
	DDX_Text(pDX, IDC_TILES, m_iTiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewTileSetDlg, CDialog)
	//{{AFX_MSG_MAP(CNewTileSetDlg)
	ON_BN_CLICKED(IDC_TILESET_BROWSE, OnNewTileSetBrowse)
	ON_BN_CLICKED(IDC_TRANSPARENT_COLOR, OnTransparentColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewTileSetDlg message handlers


void CNewTileSetDlg::OnNewTileSetBrowse() 
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for filename

	// Initialize OPENFILENAME
	memset(&ofn,0,sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = this->m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Image Files (*.bmp, *.dib)\0*.BMP;*.DIB\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrTitle = "Select Bitmap";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_LONGNAMES;
	szFile[0] = '\0';

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE) 
	{
		m_dataCtrl.SetSel(0,-1);
		m_dataCtrl.ReplaceSel(ofn.lpstrFile);
	}
	
}

void CNewTileSetDlg::OnTransparentColor() 
{
	if (DoChooseColor(this,m_rgbTransparent))
		m_transCtrl.SetColor(m_rgbTransparent);	
}

BOOL CNewTileSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_transCtrl.SetColor(m_rgbTransparent);

	if (m_bPropertySheet)
	{
		CWnd *pWnd = GetDlgItem(IDC_TILE_WIDTH);
		ASSERT(pWnd != NULL);
		pWnd->EnableWindow(FALSE);

		pWnd = GetDlgItem(IDC_TILE_HEIGHT);
		ASSERT(pWnd != NULL);
		pWnd->EnableWindow(FALSE);
	}
	if (m_iCurrent >= m_iInit)
	{
		m_iTiles = m_iCurrent-m_iInit;
		m_sTileStat.LoadString(IDS_TILESADDED);
	}
	else
	{
		m_iTiles = m_iInit-m_iCurrent;
		m_sTileStat.LoadString(IDS_TILESREM);
	}
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewTileSetDlg::OnOK() 
{
	CDialog::OnOK();
    if (!m_bPropertySheet)
	{
		// save the preferences for the next time around...
		g_rgbTransparent = m_rgbTransparent;
		g_pszInitTileData = m_pszData;
		g_nTileHeight = m_nTileHeight;
		g_nTileWidth = m_nTileWidth;
		g_nBitmapWidth = m_nBitmapWidth;
		g_bCompactOnSave = m_bCompactOnSave;
		g_bUseBitmapWidth = m_bUseBitmapWidth;
	}
}
