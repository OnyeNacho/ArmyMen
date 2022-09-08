// MapEditor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "MapFrame.h"
#include "MapEditorDoc.h"
#include "MapEditorView.h"
#include "TileSetView.h"
#include "Splash.h"
#include "ObjectSet.h"
#include "ObjectSetView.h"
#include "ScenarioView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// Global Variables
BOOL g_bMapRepeat = FALSE;         
UINT g_nBitmapWidth = 256;
BOOL g_bUseBitmapWidth = TRUE;
BOOL g_bCompactOnSave = TRUE;
UINT g_nMapWidth = 16;
UINT g_nMapHeight = 16;
UINT g_nTileWidth = 16;
UINT g_nTileHeight = 16;
BOOL g_bOutlinePreview = FALSE;
BOOL g_bOldDataFormat = FALSE;
COLORREF g_rgbTransparent = RGB(0,0,0);
COLORREF g_rgbColors[16] = {0};
UINT g_nTileSetFormat = 0;
UINT g_nObjectLayerFormat = 0;
UINT g_nAttributeLayerFormat = 0;
BOOL g_bTemporaryPaste = FALSE;
BOOL g_bActivePreview = TRUE;
CString g_pszMapTileSet = _T("");
CString g_pszMapObjectSet = _T("");
CString g_pszInitTileData = _T("");
BOOL g_bShowFullObjectName = TRUE;
BOOL g_bUseOffScreenDibs = FALSE;
BOOL g_bDecimal = TRUE;
BOOL g_bPlaceWithAttributes = FALSE;
CFindReplaceDialog *g_pReplaceDlg = NULL;
UINT WM_FINDREPLACE = 0; 
CString g_pszScenarioResources = _T("Resources");
CString g_pszScenarioUnits = _T("Units");
CString g_pszMapScenarioSet = _T("");
CString g_pszArmyMenTriggers[8] =
{ 
  _T("Trigger1"),
  _T("Trigger2"),
  _T("Trigger3"),
  _T("Trigger4"),
  _T("Trigger5"),
  _T("Trigger6"),
  _T("Trigger7"),
  _T("Trigger8"),
};
COLORREF g_rgbMapColor = RGB(255,255,255);

/////////////////////////////////////////////////////////////////////////////
UINT GetSafeSchema(CArchive& ar, CRuntimeClass *pClass, UINT first_safe_schema)
{
	UINT schema;
	if (g_bOldDataFormat)
	{
		schema = first_safe_schema - 1;
	}
	else
	{
		ar.MapObject(NULL); 
		ar.SerializeClass(pClass);
		schema = ar.GetObjectSchema();
		ASSERT(schema >= first_safe_schema);
	}
	return schema;
}

void UserError(UINT nID, int iCondition/*=TRUE*/)
{
    if (iCondition)
	{
		AfxMessageBox(nID, MB_ICONEXCLAMATION);
		AfxThrowUserException();
	}
}

void UserError(LPCTSTR msg, int iCondition/*=TRUE*/)
{
	if (iCondition)
	{
		AfxMessageBox(msg, MB_ICONEXCLAMATION);
		AfxThrowUserException();
	}
}

void UserWarn(UINT nID, int iCondition/*=TRUE*/)
{
	if (iCondition)
	{
		if (AfxMessageBox(nID, MB_ICONQUESTION|MB_YESNO) == IDNO)
			AfxThrowUserException();
	}
}

void ShowStatus(LPCTSTR msg)
{
	TRY
	{
		CMainFrame *pFrame = STATIC_DOWNCAST(CMainFrame, AfxGetApp()->m_pMainWnd);
		pFrame->ShowStatus(msg);
	}
	END_TRY
}

BOOL DoChooseColor(CWnd *pWnd, COLORREF& color)
{
	CHOOSECOLOR dlg;
	dlg.lStructSize = sizeof(CHOOSECOLOR);
	dlg.hwndOwner = pWnd ? pWnd->m_hWnd : NULL;
	dlg.rgbResult = color;
	dlg.lpCustColors = g_rgbColors;
	dlg.Flags = CC_RGBINIT|CC_SHOWHELP;
	g_rgbColors[0] = color; // TBD: so the color is "available"
	if (ChooseColor(&dlg))
	{
		color = dlg.rgbResult;
		return TRUE;
	}
	else 
	{
		TRACE("Didn't choose color\n");
		return FALSE;
	}
}
// returns a rectangle that will fit within the given rect 
// proportional to the given size. if size is smaller, the
// rectangle returned will be a rectangle with the given size
// centered within the given rect.
CRect GetPropRect(CRect rect, CSize size)
{
	CRect tmpRect = rect;
	int rw = rect.Width();
	int rh = rect.Height();
	if (size.cx > rw || size.cy > rh)
	{
		if (size.cx > size.cy)
		{
			tmpRect.bottom = rect.top + rect.Width() * size.cy / max(size.cx, 1);
			tmpRect.OffsetRect(0, (rh - tmpRect.Height()) /2);
		}
		else 
		{
			tmpRect.right = rect.left + rect.Height() * size.cx / max(size.cy, 1);
			tmpRect.OffsetRect((rw - tmpRect.Width()) / 2, 0);
		}
	}
	else
	{
		tmpRect.OffsetRect((rw - size.cx)/2, (rh - size.cy)/2);
		tmpRect.right = tmpRect.left + size.cx;
		tmpRect.bottom = tmpRect.top + size.cy;
	}
	return tmpRect;
}

CString GetValueString(int value)
{
	CString sRet;
	itoa(value,sRet.GetBufferSetLength(20), (g_bDecimal) ? 10 : 16);
	sRet.ReleaseBuffer(-1);
	return sRet;
}

 CString GetFullValueString(int iValue)
{
	CString value;
	if (g_bDecimal)
		value.Format("%d",iValue);
	else
		value.Format("0x%04x",iValue); // so it looks like the CSpinButtonCtrl value
	return value;
}

BOOL StripComponent(CString& path, CString& tail, char cSeperator)
{
	int iSeperator = path.ReverseFind(cSeperator);
	if (iSeperator >= 0)
	{
		tail = path.Right( path.GetLength() - iSeperator - 1);
		path = path.Left( iSeperator ); // TBD: does this work when iSeperator = 0?
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp

BEGIN_MESSAGE_MAP(CMapEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CMapEditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_UPDATE_COMMAND_UI(ID_ATTRIBUTE_DECIMAL, OnUpdateAttributeDecimal)
	ON_COMMAND(ID_ATTRIBUTE_DECIMAL, OnAttributeDecimal)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp construction

CMapEditorApp::CMapEditorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMapEditorApp object

CMapEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp initialization

BOOL CMapEditorApp::InitInstance()
{
#if U_SPLASH
	// CG: The following block was added by the Splash Screen component.
	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	}
#endif

    SetRegistryKey(_T("The 3DO Company"));
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	InitCommonControls();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	g_nTileSetFormat = ::RegisterClipboardFormat(_T("METileSetFormat"));
	g_nObjectLayerFormat = ::RegisterClipboardFormat(_T("MEObjectLayerFormat"));
    g_nAttributeLayerFormat = ::RegisterClipboardFormat(_T("MEAttributeLayerFormat"));
	WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pMapDocTemplate = new CMyMultiDocTemplate(
		IDR_MAPTYPE,
		RUNTIME_CLASS(CMapEditorDoc),
		RUNTIME_CLASS(CMapFrame),   // custom MDI child frame
		RUNTIME_CLASS(CMapEditorView));

	ASSERT_NEW(m_pMapDocTemplate);
	AddDocTemplate(m_pMapDocTemplate);

	m_pTileSetTemplate = new CMyMultiDocTemplate(
		IDR_TILESETTYPE,
		RUNTIME_CLASS(CTileSet),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CTileSetView));

	ASSERT_NEW(m_pTileSetTemplate);
	AddDocTemplate(m_pTileSetTemplate);

	m_pObjectSetTemplate = new CMyMultiDocTemplate(
		IDR_OBJECTSET,
		RUNTIME_CLASS(CObjectSet),
		RUNTIME_CLASS(CChildFrame),      
		RUNTIME_CLASS(CObjectSetView)); 

	ASSERT_NEW(m_pObjectSetTemplate);
	AddDocTemplate(m_pObjectSetTemplate);


	m_pScenarioSetTemplate = new CMyMultiDocTemplate(
		IDR_SCENARIOSET,
		RUNTIME_CLASS(CScenarioSet),
		RUNTIME_CLASS(CChildFrame),      
		RUNTIME_CLASS(CScenarioView)); 

	ASSERT_NEW(m_pScenarioSetTemplate);
	AddDocTemplate(m_pScenarioSetTemplate);


	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	ASSERT_NEW(pMainFrame);

	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	
#if 1
	// DON'T display a new MDI child window during startup!!!
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
#endif

	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
#if U_SPLASH
	CSplashWnd::PreTranslateAppMessage(NULL); //kludge to hide splash, avoid crash
#endif

	pMainFrame->ShowWindow(SW_SHOW);
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so update it.
	pMainFrame->UpdateWindow();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CStatic	m_version;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_VERSION, m_version);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CWnd *pWnd = GetDlgItem(IDC_VERSION);
	if (pWnd)
	{
		CString title,version;
		pWnd->GetWindowText(title);
		version.Format(" %d.%d", MAPEDIT_MAJOR_VERSION, MAPEDIT_MINOR_VERSION);
		title += version + MAPEDIT_VERSION_MODIFIER;
		pWnd->SetWindowText(title);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
// App command to run the dialog
void CMapEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp commands
void CMapEditorApp::SerializeProfileInt(BOOL bSave, LPCTSTR section, LPCTSTR name, int& iValue)
{
	if (bSave) 
		WriteProfileInt(section,name,iValue);
	else
		iValue = GetProfileInt(section,name,iValue);
}
void CMapEditorApp::SerializeProfileUInt(BOOL bSave, LPCTSTR section, LPCTSTR name, UINT& nValue)
{
	//TBD: assuming these values are relatively small, the signed/unsigned
	//comparison shouldn't bite us.
	if (bSave) 
		WriteProfileInt(section,name,nValue);
	else
		nValue = GetProfileInt(section,name,nValue);
}
void CMapEditorApp::SerializeProfileColor(BOOL bSave, LPCTSTR section, LPCTSTR name, COLORREF& color)
{
	if (bSave) 
		WriteProfileInt(section,name,color);
	else
		color = GetProfileInt(section,name,color);
}
void CMapEditorApp::SerializeProfileBool(BOOL bSave, LPCTSTR section, LPCTSTR name, BOOL& bValue)
{
	if (bSave) 
		WriteProfileBool(section,name,bValue);
	else
		bValue = GetProfileBool(section,name,bValue);
}

void CMapEditorApp::SerializeProfileString(BOOL bSave, LPCTSTR section, LPCTSTR name, CString& pszValue)
{
	if (bSave) 
		WriteProfileString(section,name,pszValue);
	else
		pszValue = GetProfileString(section,name,pszValue);
}

void CMapEditorApp::SerializeSettings(BOOL bSave)
{
	// tileset properties
	CString section = "TileSet";
	SerializeProfileUInt(bSave,section,"BitmapWidth",g_nBitmapWidth);
	SerializeProfileBool(bSave,section,"UseBitmapWidth",g_bUseBitmapWidth);
	SerializeProfileBool(bSave,section,"CompactOnSave",g_bCompactOnSave);
	SerializeProfileUInt(bSave,section,"TileWidth",g_nTileWidth);
	SerializeProfileUInt(bSave,section,"TileHeight",g_nTileHeight);
    SerializeProfileColor(bSave,section,"TransparentColor",g_rgbTransparent);
	SerializeProfileString(bSave,section,"InitTileData",g_pszInitTileData);

	// map properties
	section = "Map";
	SerializeProfileUInt(bSave,section,"MapWidth",g_nMapWidth);
	SerializeProfileUInt(bSave,section,"MapHeight",g_nMapHeight);
    SerializeProfileString(bSave,section,"MapTileSet",g_pszMapTileSet);
	SerializeProfileString(bSave,section,"MapObjectSet",g_pszMapObjectSet);
    SerializeProfileBool(bSave,section,"MapRepeat",g_bMapRepeat);
    SerializeProfileString(bSave,section,"MapScenarioSet",g_pszMapScenarioSet);
    SerializeProfileColor(bSave,section,"MapBackgroundColor",g_rgbMapColor);

	// general properties
	section = "General";
    SerializeProfileBool(bSave,section,"OutlinePreview",g_bOutlinePreview);
	SerializeProfileBool(bSave,section,"ActivePreview",g_bActivePreview);
	SerializeProfileBool(bSave,section,"ShowFullObjectName", g_bShowFullObjectName);
    SerializeProfileBool(bSave,section,"UseOffScreenDibs", g_bUseOffScreenDibs);
    SerializeProfileBool(bSave,section,"AttributeFormat", g_bDecimal);

	// scenario properties
	section = "Scenario";
	SerializeProfileString(bSave,section,"Units",g_pszScenarioUnits);
	SerializeProfileString(bSave,section,"Resources",g_pszScenarioResources);

	// armymen properties -- they asked for it <sigh>
	section = "ArmyMen";
	SerializeProfileString(bSave,section,"Trigger1",g_pszArmyMenTriggers[0]);
	SerializeProfileString(bSave,section,"Trigger2",g_pszArmyMenTriggers[1]);
	SerializeProfileString(bSave,section,"Trigger3",g_pszArmyMenTriggers[2]);
	SerializeProfileString(bSave,section,"Trigger4",g_pszArmyMenTriggers[3]);
	SerializeProfileString(bSave,section,"Trigger5",g_pszArmyMenTriggers[4]);
	SerializeProfileString(bSave,section,"Trigger6",g_pszArmyMenTriggers[5]);
	SerializeProfileString(bSave,section,"Trigger7",g_pszArmyMenTriggers[6]);
	SerializeProfileString(bSave,section,"Trigger8",g_pszArmyMenTriggers[7]);
}

int CMapEditorApp::ExitInstance() 
{
    SerializeSettings(TRUE); //save
	return CWinApp::ExitInstance();
}


void CMapEditorApp::LoadStdProfileSettings(UINT nMaxMRU)
{
	CWinApp::LoadStdProfileSettings(nMaxMRU);
    SerializeSettings(FALSE); //load
}

BOOL CMapEditorApp::PreTranslateMessage(MSG* pMsg)
{
#if U_SPLASH
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;
#endif
	return CWinApp::PreTranslateMessage(pMsg);
}

void CMapEditorApp::OnUpdateAttributeDecimal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(g_bDecimal);
}

void CMapEditorApp::OnAttributeDecimal() 
{
	g_bDecimal = !g_bDecimal;
    POSITION pos = m_pMapDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pDoc = DYNAMIC_DOWNCAST(CMapEditorDoc, m_pMapDocTemplate->GetNextDoc(pos));
		if (pDoc)
			pDoc->UpdateAttributeFormat();
	}
}




BOOL CMapEditorApp::OnIdle(LONG lCount) 
{
	if (CWinApp::OnIdle(lCount))
		return TRUE;

	// if we have nothing better to do, update the
	// active frame's overview area.
	CMainFrame *pMainFrame = STATIC_DOWNCAST(CMainFrame,m_pMainWnd);
	if (pMainFrame)
	{		
		CMapFrame *pFrame = DYNAMIC_DOWNCAST(CMapFrame,pMainFrame->GetActiveFrame());
		if (pFrame)
			return pFrame->UpdateOverview();
	}
	return FALSE;
}
