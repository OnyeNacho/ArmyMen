// NewMapDlg.cpp : implementation file 
//
// Note: this file doubles as the new map dialog 
//       AND the existing map property sheet.

#include "stdafx.h"
#include <winnetwk.h>
#include <shlobj.h>
#include "MapEditor.h"
#include "NewMapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewMapDlg dialog

CNewMapDlg::CNewMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewMapDlg::IDD, pParent)
{
	m_pMalloc = NULL;
	m_bPropertySheet = (pParent != NULL);
	m_rgbColor = g_rgbMapColor;
	//{{AFX_DATA_INIT(CNewMapDlg)
	m_iNewWidth = g_nMapWidth;
	m_iNewHeight = g_nMapHeight;
	m_pszTileSet = g_pszMapTileSet;
	m_bMapRepeat = g_bMapRepeat;
	m_pszObjectSet = g_pszMapObjectSet;
	m_pszScenarioSet = g_pszMapScenarioSet;
	m_pszDescription = _T("");
	//}}AFX_DATA_INIT
}

void CNewMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewMapDlg)
	DDX_Control(pDX, IDC_MAP_COLOR, m_colorCtrl);
	DDX_Control(pDX, IDC_MAP_SCENARIOSET, m_scenarioSetCtrl);
	DDX_Control(pDX, IDC_NEWMAP_REPEAT, m_repeatCtrl);
	DDX_Control(pDX, IDC_MAP_OBJECTSET, m_objectSetCtrl);
	DDX_Control(pDX, IDC_MAP_TILESET, m_tileSetCtrl);
	DDX_Text(pDX, IDC_MAP_WIDTH, m_iNewWidth);
	DDV_MinMaxInt(pDX, m_iNewWidth, 1, MAX_MAP_WIDTH);
	DDX_Text(pDX, IDC_MAP_HEIGHT, m_iNewHeight);
	DDV_MinMaxInt(pDX, m_iNewHeight, 1, MAX_MAP_HEIGHT);
	DDX_Text(pDX, IDC_MAP_TILESET, m_pszTileSet);
	DDX_Check(pDX, IDC_NEWMAP_REPEAT, m_bMapRepeat);
	DDX_Text(pDX, IDC_MAP_OBJECTSET, m_pszObjectSet);
	DDX_Text(pDX, IDC_MAP_SCENARIOSET, m_pszScenarioSet);
	DDX_Text(pDX, IDC_MAP_DESC, m_pszDescription);
	DDV_MaxChars(pDX, m_pszDescription, 1023);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewMapDlg, CDialog)
	//{{AFX_MSG_MAP(CNewMapDlg)
	ON_BN_CLICKED(IDC_MAP_BROWSE, OnNewMapBrowse)
	ON_BN_CLICKED(IDC_MAP_OBSBROWSE, OnMapFindObjectDir)
	ON_BN_CLICKED(IDC_MAP_SCENBROWSE, OnMapScenBrowse)
	ON_BN_CLICKED(IDC_MAP_COLOR, OnMapColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewMapDlg message handlers

void CNewMapDlg::OnNewMapBrowse() 
{
	CString title;
	VERIFY(title.LoadString(IDS_SELECT_TILESET));
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for filename

	// Initialize OPENFILENAME
	memset(&ofn,0,sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = this->m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "TileSet\0*.TLS\0All Files (*.*)\0*.*\0\0"; // TBD: localization
	ofn.lpstrTitle = title;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_LONGNAMES;
	szFile[0] = '\0';

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE) 
	{
		m_tileSetCtrl.SetSel(0,-1);
		m_tileSetCtrl.ReplaceSel(ofn.lpstrFile);
	}
			
}

void CNewMapDlg::BrowseDirectory(int iTitleID, CEdit& rControl)
{
	if (!m_pMalloc) return;

	CString title;
	VERIFY(title.LoadString(iTitleID));
	BROWSEINFO bi; 
    LPSTR lpBuffer; 
    LPITEMIDLIST pidlBrowse;    // PIDL selected by user 
    
    // Allocate a buffer to receive browse information. 
    if ((lpBuffer = (LPSTR)m_pMalloc->Alloc(MAX_PATH)) == NULL) 
        return; 
 
    // Fill in the BROWSEINFO structure. 
	memset(&bi,0,sizeof(BROWSEINFO));
    bi.hwndOwner = m_hWnd; 
    bi.pszDisplayName = lpBuffer; 
    bi.lpszTitle = title;  
 
    // Browse for a folder and return its PIDL. 
    pidlBrowse = SHBrowseForFolder(&bi); 
    if (pidlBrowse != NULL) 
	{ 
 
        if (SHGetPathFromIDList(pidlBrowse, lpBuffer)) 
		{
			rControl.SetSel(0,-1);
			rControl.ReplaceSel(lpBuffer);
		}
 
        // Free the PIDL returned by SHBrowseForFolder. 
        m_pMalloc->Free(pidlBrowse); 
    } 
 
    // Clean up. 
    m_pMalloc->Free(lpBuffer); 
}


void CNewMapDlg::OnMapFindObjectDir() 
{
	BrowseDirectory(IDS_SELECT_OBJECTSET, m_objectSetCtrl);
}

BOOL CNewMapDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_colorCtrl.SetColor(m_rgbColor);

    if (SHGetMalloc(&m_pMalloc) != NOERROR)
	{
		GetDlgItem(IDC_MAP_OBSBROWSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MAP_SCENBROWSE)->EnableWindow(FALSE);
	}

	if (m_bPropertySheet)
	{
		m_repeatCtrl.ShowWindow(SW_HIDE);
    }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewMapDlg::OnOK() 
{
	CDialog::OnOK();
	if (!m_bPropertySheet)
	{
		// save the global preferences...
		g_nMapWidth = m_iNewWidth;
		g_nMapHeight = m_iNewHeight;
		g_pszMapTileSet = m_pszTileSet;
		g_bMapRepeat = m_bMapRepeat;
		g_pszMapObjectSet = m_pszObjectSet;
		g_pszMapScenarioSet = m_pszScenarioSet;
		g_rgbMapColor = m_rgbColor;
	}
}

void CNewMapDlg::OnMapScenBrowse() 
{
	BrowseDirectory(IDS_SELECT_SCENARIOSET, m_scenarioSetCtrl);
}

void CNewMapDlg::OnMapColor() 
{
	if (DoChooseColor(this,m_rgbColor))
		m_colorCtrl.SetColor(m_rgbColor);	
}
