/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: ArmyMen.cpp $
//
//	DESCRIPTION:	Defines the class behaviors for the application.
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, May 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/ArmyMen.cpp 88    4/17/98 3:14p Nrobinso $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/ArmyMen.cpp $
//  
//  88    4/17/98 3:14p Nrobinso
//  command switch to turn off movies
//  
//  87    4/08/98 8:06p Nrobinso
//  force low memory/low performance on command line
//  
//  86    4/07/98 12:51p Nrobinso
//  remove no_cheats
//  
//  85    4/06/98 3:00p Nrobinso
//  look for cursor.bmp or refuse to run
//  
//  83    4/02/98 2:03p Phu
//  typecasting to prevent warnings
//  
//  82    4/01/98 11:59a Nrobinso
//  release mutex
//  
//  81    3/30/98 1:08p Nrobinso
//  if find a cpu speed of 0, consider it fast
//  
//  80    3/29/98 5:32p Nrobinso
//  mp cheat
//  
//  79    3/27/98 5:20p Nrobinso
//  turn off no cheats
//  
//  78    3/25/98 4:30p Nrobinso
//  remove unused; move version info
//  
//  77    3/23/98 6:40p Nrobinso
//  remove about box
//  
//  76    3/20/98 12:04a Nrobinso
//  version .85
//  
//  75    3/19/98 4:34p Dmaynard
//  Added a -Rule:   command line switch
//  
//  74    3/18/98 12:17p Nrobinso
//  version .80
//  
//  73    3/17/98 1:56p Nrobinso
//  
//  72    3/16/98 1:01p Nrobinso
//  turn off memory trace
//  
//  71    3/13/98 11:30a Nrobinso
//  version .70
//  
//  70    3/08/98 3:39p Nrobinso
//  create a mutex to prevent autorun & 2nd copies of armymen from running
//  
//  69    3/07/98 10:39p Nrobinso
//  add OnMove to prevent dialogs from leaving blackness behind
//  
//  68    3/07/98 12:19a Nrobinso
//  version .50
//  
//  67    3/06/98 2:53p Phu
//  library load as default,  faster animation loading
//  
//  66    3/03/98 3:18p Nrobinso
//  use Error call if can't find DLL
//  
//  65    3/03/98 10:08a Nrobinso
//  version .40
//  
//  64    2/27/98 5:21p Nrobinso
//  
//  63    2/26/98 4:06p Phu
//  removed profiling/ old draw map into deadcode
//  
//  62    2/26/98 3:22p Phu
//  
//  61    2/25/98 8:50p Nrobinso
//  version .31
//  
//  60    2/25/98 5:28p Nrobinso
//  version .30
//  
//  59    2/21/98 6:00p Nrobinso
//  version .25
//  
//  58    2/17/98 12:06p Phu
//  increment version number
//  
//  57    2/13/98 2:14p Nrobinso
//  version .20
//  
//  56    2/12/98 5:29p Phu
//  return TRUE when syskey press is processed
//  
//  55    2/01/98 10:53p Nrobinso
//  removed old dialog code
//  
//  54    1/30/98 5:24p Nrobinso
//  version .13
//  
//  53    1/30/98 9:19a Nrobinso
//  version .12
//  
//  52    1/29/98 11:27a Nrobinso
//  version .11
//  
//  51    1/27/98 5:12p Phu
//  move cpuid to better place
//  
//  50    1/27/98 4:13p Phu
//  measure memory + processor speed
//  
//  49    1/27/98 1:23p Phu
//  memory info
//  
//  48    1/26/98 11:59a Nrobinso
//  new path defines; put campaign file in it's own folder
//  
//  47    1/23/98 9:33a Aburgess
//  noe uses new LEGAL title screen
//  
//  46    1/22/98 6:43p Nrobinso
//  use SetPath
//  
//  45    1/22/98 11:57a Nrobinso
//  version 10
//  
//  44    1/21/98 1:17p Nrobinso
//  version .9
//  
//  43    1/21/98 10:35a Nrobinso
//  version .8
//  
//  42    1/21/98 10:33a Nrobinso
//  version .7
//  
//  41    1/18/98 1:03a Nrobinso
//  version .6
//  
//  40    1/16/98 11:08a Nrobinso
//  version .5
//  
//  39    1/15/98 9:25p Nrobinso
//  version .4
//  
//  38    1/15/98 11:14a Nrobinso
//  version .3
//  
//  37    1/14/98 5:46p Nrobinso
//  version .2
//  
//  36    1/14/98 11:33a Nrobinso
//  add development version info
//  
//  35    1/12/98 10:42a Aburgess
//  changes made to look in the RUNTIME/MAPS directory for map based
//  information
//  
//  34    1/09/98 9:51a Nrobinso
//  fix ability to run full screen as an option from title
//  
//	...
// 
// 5     6/25/96 9:53p Nrobins
// added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "ArmyMen.h"
#include "MainFrm.h"
#include "Army.h"
#include "Tad.h"
#include "Map.h"
#include "Scenario.h"
#include "GameFlow.h"
#include "Dialog.h"
#include "Ai.h"
#include "comm.h"
#include "3DONetwork.h"
#include "string.h"
#include "miscfile.h"		// miscellaneous file support functions
#include "Screen.h"			// UI Screen support functions
#include "Audio.h"			// AUDIO support functions
#include "fileio.h"

/////////////////////////////////////////////////////////////////////////////

#define CPUINFODLL "cpuinf32.dll"


// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Global Variables

CArmyMenApp theApp;
CMainFrame *pMainFrame;


extern BOOL  _LOAD_FROM_DATAFILE;
extern HFONT	ghTitleFont;        // font for titles on setup wizard
extern HFONT	ghHeadingFont;      // font for headings on setup wizard
extern BOOL		no_mp_cheats;
extern BOOL		noPlayMovies;

BOOL	START_FULL_SCREEN = TRUE;
BOOL	run_windowed  = FALSE;
HANDLE	hMutex = NULL;

void MeasureProcessorSpeed( void );


/////////////////////////////////////////////////////////////////////////////
// CArmyMenApp Message Map

BEGIN_MESSAGE_MAP(CArmyMenApp, CWinApp)
	//{{AFX_MSG_MAP(CArmyMenApp)
	ON_COMMAND(ID_AUDIO_DIAGNOSTIC, OnAudioDiagnosticDialog)
	//}}AFX_MSG_MAP
	// Standard file based document commands

//	ON_COMMAND(ID_FILE_SAVE, CWinApp::OnFileSave)
//	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)

	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
END_MESSAGE_MAP()

// CWinApp::DoPromptFileName
// CWinApp::OpenDocumentFile
// DoPromptFileName brings up the standard FileOpen dialog


/////////////////////////////////////////////////////////////////////////////
// CArmyMenApp construction/destruction

CArmyMenApp::CArmyMenApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	DLGinit();
}

CArmyMenApp::~CArmyMenApp()
{
	// TODO: add destruction code here,
	if (hMutex)
		ReleaseMutex(hMutex);	
	DLGexit();
}

/////////////////////////////////////////////////////////////////////////////
// Public Methods

/////////////////////////////////////////////////////////////////////////////

// CArmyMenApp initialization
BOOL CArmyMenApp::InitInstance()	{
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "ArmyMenMutex");

	if (hMutex)	// if mutex exists, this is a second incarnation, so die
		return FALSE;

	if ( !FileExist( "cursor.bmp" ) )
		return FALSE;

	// created so that we can find the process
	hMutex = CreateMutex(NULL, FALSE, "ArmyMenMutex"); 

//	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	char szAppPath[ MAX_PATH ];
	GetModuleFileName( m_hInstance, szAppPath, MAX_PATH );

	DWORD   dwVerInfoSize;			// Size of version information block
	DWORD   dwVerHnd=0;				// An 'ignored' parameter, always '0'

	dwVerInfoSize = GetFileVersionInfoSize(szAppPath, &dwVerHnd);
	if (dwVerInfoSize) {
		LPVOID	lpstrVffInfo;
		UINT    uVersionLen;
		VS_FIXEDFILEINFO   *lpVersion;	// pointer to basic info

		lpstrVffInfo  = malloc(dwVerInfoSize);
		GetFileVersionInfo(szAppPath, dwVerHnd, dwVerInfoSize, lpstrVffInfo);

		if (VerQueryValue(lpstrVffInfo, "\\", (LPVOID *)&lpVersion, &uVersionLen))	{
			docVersion.major = lpVersion->dwFileVersionMS;
			docVersion.minor = lpVersion->dwFileVersionLS;
			appVersion.major = lpVersion->dwProductVersionMS;
			appVersion.minor = lpVersion->dwProductVersionLS;
		}
		
		free(lpstrVffInfo);
	}

	// process command line
	if ( m_lpCmdLine[0] != '\0' )
	{
		char *token;

		if (token = strtok( m_lpCmdLine, " " ))	{
			do	{
				if (strcmp(token,"-3") == 0)	{
					_LOAD_FROM_DATAFILE = FALSE;
				}
				else if (strncmp(token,"-Map:",5) == 0)	{
					gpGame->MapName = &token[5];
				}
				else if (strncmp(token,"-Rule:",6) == 0)	{
					gpGame->RuleName = &token[6];
					gpGame->RuleName += ".RUL";
				}
				else if (strncmp(token, "-w", 2) == 0 )
				{
					START_FULL_SCREEN = FALSE;
					run_windowed = TRUE;
				}
				else if (strncmp(token, "-xyz", 4) == 0 )
				{
					no_mp_cheats = FALSE;
				}
				else if (strncmp(token, "-nomovies", 9) == 0 )
				{
					noPlayMovies = TRUE;
				}
				else if (strncmp(token, "-f", 2) == 0 )
				{
					START_FULL_SCREEN = TRUE;
					run_windowed = FALSE;
				}
				else if (strncmp(token, "-slow", 2) == 0 )
				{
					gpGame->SlowMachine = TRUE;
				}
				else if (strncmp(token, "-low", 2) == 0 )
				{
					gpGame->LowMemoryMachine = TRUE;
				}
			}
			while (token = strtok( NULL, " " ));
		}
	}

	// Create main window
	m_pMainWnd = new CMainFrame;
	pMainFrame = (CMainFrame*) m_pMainWnd;
	ASSERT(m_pMainWnd);

	if (pMainFrame->Create(m_pszAppName))	{
		pMainFrame->WindowReset();
		pMainFrame->ShowWindow(m_nCmdShow);
		pMainFrame->UpdateWindow();

		if( START_FULL_SCREEN )
			pMainFrame->ForceFullScreen();

		// get memory information
		MEMORYSTATUS memstatus;
		memstatus.dwLength = sizeof(MEMORYSTATUS);
		GlobalMemoryStatus( &memstatus );
		if( memstatus.dwTotalPhys < 32000000 )
			gpGame->LowMemoryMachine = TRUE;
//		TRACE( "Physical Memory:  %d available, %d total\n", memstatus.dwAvailPhys, memstatus.dwTotalPhys );
//		TRACE( "Virtual Memory: %d available, %d total\n", memstatus.dwAvailVirtual, memstatus.dwTotalVirtual );

		// get processor type & speed
		MeasureProcessorSpeed();

		return TRUE;
	}

	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// Override Run() App to provide game handling
int CArmyMenApp::Run() {
	MSG msg;

	while (TRUE)
	{
		//process pending Windows messages
		if (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
/*
			switch( msg.message )
			{
			case WM_SYSKEYDOWN:
				switch( msg.wParam )
				{
				case VK_F10:
				case VK_RETURN:
				case VK_MENU:
					::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
					break;
				}
				break;
			case WM_SYSKEYUP:
				switch( msg.wParam )
				{
				case VK_F10:
				case VK_RETURN:
				case VK_MENU:
					::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
					break;
				}
				break;
			case WM_DISPLAYCHANGE:
				::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
				break;				
*/
/*
			case WM_SYSCOMMAND:
				switch( msg.wParam )
				{
				case SC_SCREENSAVE:
					::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
					break;
				}
				break;
*/
//			}
			if (!PumpMessage())
			{
				::PostQuitMessage(msg.wParam);
				break;
			}
		}
		//execute main game loop
		else 
		{
			MainLoop();
		}
	}
	return CWinApp::Run();
}


afx_msg void CArmyMenApp::OnFileOpen( )	{
	OPENFILENAME openfilename;
	char filename[256];

	pMainFrame->PauseFlip();
	SetPath(NULL);

	filename[0] = '\0';

	openfilename.lStructSize = sizeof(OPENFILENAME);
    openfilename.hwndOwner = pMainFrame->GetHwnd(); 
    openfilename.hInstance = NULL; 
    openfilename.lpstrFilter = "Map Files\0*.AMM\0\0"; 
    openfilename.lpstrCustomFilter = NULL; 
    openfilename.nMaxCustFilter = 0; 
    openfilename.nFilterIndex = 0; 
    openfilename.lpstrFile = filename; 
    openfilename.nMaxFile = sizeof(filename); 
    openfilename.lpstrFileTitle = NULL; 
    openfilename.nMaxFileTitle = 0; 
    openfilename.lpstrInitialDir = NULL; 
    openfilename.lpstrTitle = NULL; 
    openfilename.Flags = OFN_LONGNAMES; 
    openfilename.nFileOffset = 0; 
	openfilename.nFileExtension = 0; 
    openfilename.lpstrDefExt = "MAP"; 
    openfilename.lCustData = 0; 
    openfilename.lpfnHook = NULL; 
    openfilename.lpTemplateName = NULL;

	if ( GetOpenFileName(&openfilename))	{
		gpGame->MapName = openfilename.lpstrFile;
	}
	else	{
		DWORD error = CommDlgExtendedError();
		TRACE("CommDlgExtendedError = %X\n", error);
	}

	pMainFrame->UnPauseFlip();
}

//------------------------------------------------------------------------
//						DIALOG MENU ACCESS ROUTINES
//------------------------------------------------------------------------

WORD (FAR *lpfnwincpuid)();
long (FAR *lpfnwincpuspeed)(int);

void MeasureProcessorSpeed( void )
{
	HINSTANCE hLibrary;				//handle for cpuinf32 dll
	WORD	cpu_type   = 0;			// CPU Family variable
	long    cpu_speed = 0;

	hLibrary = LoadLibrary(CPUINFODLL);
	if( hLibrary == NULL )
	{
		Error("Missing %s", CPUINFODLL);
		return;
	}
	lpfnwincpuid = (WORD (FAR *)())GetProcAddress(hLibrary,"wincpuid");
	cpu_type = (*lpfnwincpuid)();

	lpfnwincpuspeed = (long (FAR *)(int))GetProcAddress( hLibrary, "cpunormspeed" );

	cpu_speed = (*lpfnwincpuspeed)(0);				

	if( (cpu_type < 5) || (cpu_speed < 130 && cpu_speed != 0))
		gpGame->SlowMachine = TRUE;

	FreeLibrary( hLibrary );
}

void CArmyMenApp::OnAudioDiagnosticDialog() 
{
	int					result;
	CAudioDiagnosticDlg audioDlg;

	// TODO: Add your command handler code here
	result = audioDlg.DoModal();
}

//========================================================================
//								EOF
//========================================================================
