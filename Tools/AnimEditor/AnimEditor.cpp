// AnimEditor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AnimEditor.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "AnimEditorDoc.h"
#include "AnimEditorView.h"
#include "CCelView.h"
//#include "CCelViewFrame.h"
#include "CAnimEditorCommandLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorApp

BEGIN_MESSAGE_MAP(CAnimEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CAnimEditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_AUTOCROP, OnFileAutocrop)
	ON_UPDATE_COMMAND_UI(ID_FILE_AUTOCROP, OnUpdateFileAutocrop)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CAnimEditorApp object

CAnimEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorApp construction

CAnimEditorApp::CAnimEditorApp()
{
	// Place all significant initialization in InitInstance

	bAppQuit = FALSE;

	char szAppPath[ MAX_PATH ];
	::GetModuleFileName( m_hInstance, szAppPath, MAX_PATH );
	csAppPath = szAppPath;
	int iSlash = csAppPath.ReverseFind( '\\' );
	csAppPath = csAppPath.Left( iSlash + 1 );


	DWORD   dwVerInfoSize;			// Size of version information block
	DWORD   dwVerHnd=0;				// An 'ignored' parameter, always '0'

	dwVerInfoSize = GetFileVersionInfoSize(szAppPath, &dwVerHnd);
	if (dwVerInfoSize) {
		LPVOID	lpstrVffInfo;
		HANDLE	hMem;
		UINT    uVersionLen;
		VS_FIXEDFILEINFO   *lpVersion;	// pointer to basic info

		hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
		lpstrVffInfo  = GlobalLock(hMem);
		GetFileVersionInfo(szAppPath, dwVerHnd, dwVerInfoSize, lpstrVffInfo);

		if (VerQueryValue(lpstrVffInfo, "\\", (LPVOID *)&lpVersion, &uVersionLen))	{
			docVersion.major = lpVersion->dwFileVersionMS;
			docVersion.minor = lpVersion->dwFileVersionLS;
			appVersion.major = lpVersion->dwProductVersionMS;
			appVersion.minor = lpVersion->dwProductVersionLS;
		}
		
		GlobalUnlock(hMem);
		GlobalFree(hMem);
	}


	colorDialog = (COLORREF)GetSysColor( COLOR_3DFACE );
	colorWindow = (COLORREF)GetSysColor( COLOR_WINDOW );

	bAutoCrop = FALSE;

	//	Read in Directions.txt.
	CString csFileName = csAppPath;
	csFileName += "Directions.txt";
	TRY
	{
		CStdioFile	sfDirections( csFileName, CFile::modeRead | CFile::typeText );
		CString		csLine;
		CDirectionRecord*	parDirection;
//		int			iDir;
		while( sfDirections.ReadString( csLine ) )
		{
			if( csLine == "" || csLine.Left( 2 ) == "//" )
				continue;
			parDirection = new CDirectionRecord( csLine );
			lstDirections.AddTail( parDirection );
//			iDir = atoi( csLine );
//			if( !lstDirections.Find( iDir ) )
//				lstDirections.AddTail( iDir );
			if( !parDirection->bFileOk )
			{
				CString csError;
				csError.Format( "Incorrect format error in %s. Please use the format:\n1  \"Direction string 1\"\n2  \"Direction string 2\"\netc...", csFileName );
				AfxMessageBox( csError );
				bAppQuit = TRUE;
				return;
			}
		}
		if( lstDirections.GetCount() == 0 )
		{
			CString csError;
			csError.Format( "Error in %s: No direction records found.", csFileName );
			AfxMessageBox( csError );
			bAppQuit = TRUE;
			return;
		}
	}
	CATCH( CFileException, e )
	{
		CString csError;
		csError.Format( "Error reading %s.", csFileName );
		AfxMessageBox( csError );
		bAppQuit = TRUE;
		return;
	}
	END_CATCH

#ifdef USE_DATABASE
	//	Read in Action table.
	CActionRecord	arActionRec;
	CActionRecord*	parAction;

	CDaoDatabase DaoDatabase;
	DaoDatabase.Open( arActionRec.GetDefaultDBName(), FALSE, TRUE );	//	Open database read only.
	arActionRec.m_pDatabase = &DaoDatabase;								//	Attach recordset to database, so it's opened read only.
	arActionRec.Open();

	while( !arActionRec.IsEOF() )
	{
		parAction = new CActionRecord();
		*parAction = arActionRec;
		lstActions.AddTail( parAction );
		arActionRec.MoveNext();
	}
	arActionRec.Close();
	DaoDatabase.Close();
#else
	//	Read in Actions.txt.
	csFileName = csAppPath;
	csFileName += "Actions.txt";
	TRY
	{
		CStdioFile		sfActions( csFileName, CFile::modeRead | CFile::typeText );
		CString			csLine;
		CActionRecord*	parAction;
		while( sfActions.ReadString( csLine ) )
		{
			if( csLine == "" || csLine.Left( 2 ) == "//" )
				continue;
			parAction = new CActionRecord( csLine );
			lstActions.AddTail( parAction );
			if( !parAction->bFileOk )
			{
				CString csError;
				csError.Format( "Incorrect format error in %s. Please use the format:\n1  \"Action string 1\"\n2  \"Action string 2\"\netc...", csFileName );
				AfxMessageBox( csError );
				bAppQuit = TRUE;
				return;
			}
		}
		if( lstActions.GetCount() == 0 )
		{
			CString csError;
			csError.Format( "Error in %s: No action records found.", csFileName );
			AfxMessageBox( csError );
			bAppQuit = TRUE;
			return;
		}
	}
	CATCH( CFileException, e )
	{
		CString csError;
		csError.Format( "Error reading %s.", csFileName );
		AfxMessageBox( csError );
		bAppQuit = TRUE;
		return;
	}
	END_CATCH
#endif
}

CAnimEditorApp::~CAnimEditorApp()
{
	if( pCelViewTemplate )
		delete pCelViewTemplate;

	//	Delete actions list members.
	POSITION posInList;
	CActionRecord* parAction;
	while( posInList = lstActions.GetHeadPosition() )
	{
		parAction = lstActions.GetAt( posInList );
		lstActions.RemoveAt( posInList );
		delete parAction;
	}

	CDirectionRecord* parDirection;
	while( posInList = lstDirections.GetHeadPosition() )
	{
		parDirection = lstDirections.GetAt( posInList );
		lstDirections.RemoveAt( posInList );
		delete parDirection;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorApp initialization

BOOL CAnimEditorApp::InitInstance()
{
	if( bAppQuit )
		return FALSE;

	//	Initialize OLD libraries
	if( !AfxOleInit() )
	{
		AfxMessageBox( IDP_OLE_INIT_FAILED );
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey( _T( "The 3DO Company" ) );

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_ANIMEDTYPE,
		RUNTIME_CLASS(CAnimEditorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAnimEditorView));
	AddDocTemplate(pDocTemplate);

//	//	Create a CelView template (a la KH's method for easily creating an additional view for a doc that has its own frame).
//	pCelViewTemplate = new CMultiDocTemplate(
//		IDR_ANIMEDTYPE,
//		RUNTIME_CLASS(CAnimEditorDoc),
//		RUNTIME_CLASS(CCelViewFrame),
//		RUNTIME_CLASS(CCelView));

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CAnimEditorCommandLine cmdInfo;
	ParseCommandLine( cmdInfo );

	if( cmdInfo.csAutoExportFile != "" )
	{
		//	If AFC file is specified on command line (with "-auto filename"), perform auto export on doc and quit app.
		m_nCmdShow = SW_HIDE;
		CAnimEditorDoc* pDoc = (CAnimEditorDoc*)OpenDocumentFile( cmdInfo.csAutoExportFile );
		if( !pDoc )
			TRACE( "AFC file not found: %s\n", cmdInfo.csAutoExportFile );
		else
		{
			if( pDoc->ExportRLEOutOfDate() )
				pDoc->Export( TRUE, TRUE );
		}
		return FALSE;		//	Exit app.
	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	csCelClipboardFormatName			= "AnimEditor_Cel";
	csSequenceCelClipboardFormatName	= "AnimEditor_SequenceCel";
	clipFormatCel			= RegisterClipboardFormat( csCelClipboardFormatName );
	clipFormatSequenceCel	= RegisterClipboardFormat( csSequenceCelClipboardFormatName );
	iSizeClipFormatCelBlock			= 12000;		//	Number of bytes in the block of memory used for this format. xxx
	iSizeClipFormatSequenceCelBlock	= 12000;		//	  "

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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	
	CWnd *pWnd = GetDlgItem(IDC_VERSION);
	if (pWnd)
	{
		CString title,version;
		pWnd->GetWindowText(title);
		version.Format(" %d.%d", theApp.appVersion.major, theApp.appVersion.minor);
		title += version;
		pWnd->SetWindowText(title);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// App command to run the dialog
void CAnimEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorApp commands

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorApp::OnUpdateFileAutocrop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( bAutoCrop ? 1 : 0 );
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorApp::OnFileAutocrop() 
{
	bAutoCrop = !bAutoCrop;		
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorApp::PreTranslateMessage(MSG* pMsg) 
{
	//	Check for rerouting left or right arrow key messages to the scrollbar on an active CCelView...
	switch( pMsg->message )
	{
	case WM_KEYDOWN:
		//	Make sure the target window is not an edit box (we want arrows to behave normally there).
		CWnd* pWnd = CWnd::FromHandle( pMsg->hwnd );
		if( pWnd->IsKindOf( RUNTIME_CLASS( CEdit ) ) || pWnd->IsKindOf( RUNTIME_CLASS( CRichEditCtrl ) ) )
			break;		//	xxx doesn't work - fix
		if( pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT )
		{
			//	Right or left arrow key pressed.
			CAnimEditorDoc* pDoc = (CAnimEditorDoc*)((CMDIFrameWnd*)AfxGetMainWnd())->MDIGetActive()->GetActiveDocument();
			if( pDoc )
			{
				//	Find CCelView.
				POSITION posView = pDoc->GetFirstViewPosition();
				CView* pView;
				while( posView != NULL )
				{
					pView = pDoc->GetNextView( posView );
					if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CCelView" ) == 0 )
					{
						CCelView* pCelView = (CCelView*)pView;
						if( pCelView->pSequence )
						{
							//	There is a sequence active in the CCelView.
							//	Redirect the message to the frame advance scrollbar within it.
							pMsg->hwnd = pCelView->scrollCel.GetSafeHwnd();
						}
					}
				}
			}
		} 
		else if( pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN || pMsg->wParam == VK_PRIOR || pMsg->wParam == VK_NEXT )
		{
			//	Up, down, pgup, pgdn key pressed.
			CAnimEditorDoc* pDoc = (CAnimEditorDoc*)((CMDIFrameWnd*)AfxGetMainWnd())->MDIGetActive()->GetActiveDocument();
			if( pDoc )
			{
				//	Find CMultipleSequencesView.
				POSITION posView = pDoc->GetFirstViewPosition();
				CView* pView;
				while( posView != NULL )
				{
					pView = pDoc->GetNextView( posView );
					if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CMultipleSequencesView" ) == 0 )
					{
						//	Post a new message to the scrollview.
						switch( pMsg->wParam )
						{
						case VK_UP:
							pView->PostMessage( WM_VSCROLL, SB_LINEUP );
							break;
						case VK_DOWN:
							pView->PostMessage( WM_VSCROLL, SB_LINEDOWN );
							break;
						case VK_PRIOR:
							pView->PostMessage( WM_VSCROLL, SB_PAGEUP );
							break;
						case VK_NEXT:
							pView->PostMessage( WM_VSCROLL, SB_PAGEDOWN );
							break;
						}
						return TRUE;	//	Don't process the original message.
					}
				}
			}
		}
		break;
	}


	return CWinApp::PreTranslateMessage(pMsg);
}
