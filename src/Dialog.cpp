//========================================================================
//	FILE:			$Workfile: Dialog.cpp $
//
//	DESCRIPTION:	DIALOG type processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, August 20, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Dialog.cpp 88    4/13/98 11:48a Dmaynard $
//
//========================================================================
//                 COPYRIGHT(C)1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Dialog.cpp $
//  
//  88    4/13/98 11:48a Dmaynard
//  Disable Screen Savers when in Multi-Player MFC Dialogs
//  
//  87    4/05/98 3:51p Dmaynard
//  Fixed problem where Joiner could join without entering a name
//  
//  85    4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  84    3/30/98 3:43p Dmaynard
//  Don't kill the Enumeration Timer if the user hasn't really selected a
//  session yet in OnJoinSessionNext.
//  
//  83    3/28/98 8:30p Dmaynard
//  Fixed hitting Next on JoinSession to be a NO-OP if you don't have a
//  session selected.
//  
//  82    3/26/98 10:15a Nrobinso
//  init variables to join, not just button
//  
//  81    3/26/98 9:21a Nrobinso
//  default to join
//  
//  80    3/20/98 11:53a Aburgess
//  modifications made to correct VOICE and MUSIC cut offs. It apprears
//  that ALL Music and Voice streams need to be run with LOOP on.
//  
//  79    3/20/98 11:34a Dmaynard
//  Force User to Specify a non-null Session Name and Sarge Name
//  
//  78    3/18/98 12:51a Nrobinso
//  cleanup registry access
//  
//  77    3/16/98 12:22a Nrobinso
//  add a second failure dialog
//  
//  76    3/13/98 4:14p Dmaynard
//  Fixing Bug in OnJoinSessionBack  wasn't reinitializing the DPlayObject
//  Correctly.
//  
//  75    3/13/98 12:59p Dmaynard
//  JoinSession and stopping the Enumeration doesn't work.  Try not
//  stopping the enumeration.
//  
//  74    3/13/98 12:29p Dmaynard
//  Fixed Fatal Bug in JoinSession Dialog
//  
//  73    3/13/98 12:15p Dmaynard
//  Bug Fixes for JoinSession Dialog  on TCP/IP case.
//  
//  72    3/12/98 10:24p Dmaynard
//  Fixed bug: When user hits Cancel in Dplay's Locate Session Dialog box
//  JoinSession now cancels properly.
//  
//  71    3/12/98 6:00p Dmaynard
//  Asynchronous update of available ArmyMen Sessions in the Select Battle
//  screen of the JoinSession Dialog.
//  
//  70    3/11/98 8:46p Dmaynard
//  Framework Added for enabling Asynchronous JoinSession Session scanning.
//  Everything in but the timer set-up, and still needs testing.
//  
//  69    3/10/98 8:30p Dmaynard
//  Fixed what may have been a bug in GetNewSelectedItem in JoinSession
//  Dialog.  return failure was getting overwritten with a returrn success
//  
//  68    3/10/98 6:00p Dmaynard
//  Added ShowError if MultiPlayer Game can't find Direct X 5 or later.  
//  
//  67    3/10/98 10:53a Dmaynard
//  Error checking when loading DirectPlay via Com.
//  
//  66    3/09/98 5:24p Dmaynard
//  Fixing the storing and freeing of ServiceProvder Connection Buffers.
//  Also fixed bug in remembering the last used service provider in the
//  registry.
//  
//  65    3/09/98 11:43a Dmaynard
//  Changed DPlay to load via COM interface  CoCreateInstance.
//  
//  64    3/07/98 10:41p Nrobinso
//  add OnMove to prevent dialogs from leaving blackness behind; remove
//  unused dialog code
//  
//  63    3/06/98 6:07p Dmaynard
//  Resetting Connection on JoinSessionBack  so that if will ask for the IP
//  Address the second time around.
//  
//  62    3/06/98 3:53p Dmaynard
//  Added Call to gpComm->Release in OnSessionJoinBack.
//  Fixes bug #356  Enter IP Address was failing to appear.
//  
//  61    3/02/98 10:31a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  60    2/26/98 2:37p Nrobinso
//  do CD check for host
//  
//  59    2/20/98 4:25p Aburgess
//  cleaned up debug
//  
//  58    2/17/98 5:20p Nrobinso
//  remove unused code
//  
//  57    2/17/98 8:56a Aburgess
//  Game Session BACK now returns to Join/host session
//  
//  56    2/09/98 7:22p Nrobinso
//  remove unused code
//  
//  55    2/07/98 5:12p Nrobinso
//  move dead code out
//  
//  54    2/02/98 10:29a Nrobinso
//  game palette
//  
//  53    2/01/98 10:55p Nrobinso
//  use open session bitmap
//  
//  52    1/28/98 5:38p Dmaynard
//  Changed how and When CreateFlowQPLayer is called so that we can start
//  sending in the map selections screens (to eventualy measure and display
//  latency and packetloss)
//  
//  51    1/26/98 12:00p Nrobinso
//  new path defines; put campaign file in it's own folder
//  
//  50    1/23/98 9:33a Aburgess
//  noe uses new LEGAL title screen
//  
//  49    1/22/98 6:44p Nrobinso
//  use SetPath
//  
//  48    1/12/98 11:57a Aburgess
//  .AMM references were not using Maps Runtime directory
//  
//  47    1/12/98 11:12a Aburgess
//  made campaign.cpn accessed in RunTime
//  
//  46    1/05/98 4:52p Dmaynard
//  Added Initialization of gpGame->start_game   used by Comm to signify
//  that we are still in a game setup phase and not begin frame based
//  messaging yet.  This reduces net traffic during map select and map l
//  oading phase.
//  
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"
#include "comm.h"
#include "Armymen.h"
#include "MainFrm.h"
#include "GameFlow.h"
#include "gameproc.h"
#include "Dialog.h"
#include "Audio.h"
#include "Ai.h"
#include "comm.h"
#include "3DONetwork.h"
#include "Screen.h"
#include "miscfile.h"

#include "Snd.h"
#include "sounds.dat"
#include "streams.dat"
#include "voices.dat"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//================================================================
//			LOCAL prototypes
//================================================================
static	BOOL WINAPI DLGEnumCallback(LPGUID lpGuid, LPTSTR lptszDesc, DWORD dwMajorVersion,
									DWORD dwMinorVersion, LPVOID lpv);
static	BOOL WINAPI DLGEnumPlayer(DPID pidID, DWORD dwPlayerType, LPCDPNAME lpName,
								  DWORD dwFlags, LPVOID lpContext);
static	BOOL WINAPI DLGEnumSession(LPCDPSESSIONDESC2 lpDPSessionDesc, LPDWORD lpdwTimeOut, DWORD dwFlags, 
								   LPVOID lpContext);
static	BOOL WINAPI DPEnumConnCallback( LPCGUID lpguidSP, LPVOID	lpConnection,
	DWORD		dwConnectionSize,
    LPCDPNAME   lpName,
	DWORD 		dwFlags,
	LPVOID 		lpContext);
static	BOOL DLGEnumerateAudio( int buttonState, LPVOID lpv );
static	BOOL DLGEnumSound( ULONG nSndID, LPTSTR lptszDesc, LPVOID lpv, int nButton );
static	BOOL DLGInitTreeViewImageLists(HWND hwndTV);
static	HTREEITEM DLGAddItemToTree(HWND hwndTV, LPTSTR lptszItem, DWORD dwData, int nLevel);
static	BOOL DLGInitTreeLists(HWND hwndTV);
static	HTREEITEM DLGAddListItem(HWND hwndTV, LPTSTR lptszItem, DWORD dwData, int nLevel);
static	void DLGSetVolumeMember( CSliderCtrl* Cslider, int nCtrlID, int nPercent );
static	void DLGReleaseSessionData( void );
static	void DLGReleaseSPData( void );
static	void DLGReleaseAudioData( void );

//================================================================
//			GLOBAL prototypes
//================================================================
static	void SetupFonts( HDC hDC );
static	void CleanupFonts( void );

//================================================================
//			GLOBAL variables
//================================================================
		CWnd*		gCWnd;				// global CWnd pointer for HWND conversion
		HFONT		ghTitleFont;        // font for titles on setup wizard
		HFONT		ghHeadingFont;      // font for headings on setup wizard
static	HFONT		ghScaleFont;		// font for scales and other small text
static	int			gAMnSession,gAMnPlayer; // indexes for tree view images
static	HTREEITEM	gAMhtiVisible;		// points to a visible item in tree control
static	HTREEITEM	gAMhtiSession;		// points to a visible session item in tree control
static	HTREEITEM	gAMhtiCur;			// points to the current visible session item in tree control
static	GUID		gAMSPGuid;			// currently selected service provider guid
static  SPCONTEXT   gAMSPContext;
static	CWnd*		gCWndCtlSP;			// saved for later use during cleanup
static	CWnd*		gCWndCtlMaps;		// saved for later use during cleanup
static	CWnd*		gCWndCtlAudio;		// saved for later use during cleanup
static	CWnd*		gCWndOldFocus;		// window that previously had focus
static	TCHAR		gAMtszSessionName[MAX_SESSIONNAME+1];
static	TCHAR		gAMtszPlayerName[MAX_PLAYERNAME+1];
static	NM_TREEVIEW gAMnmtv;
static	TV_ITEM		gAMtvItem;
static	HANDLE		gAMdphEvent;
static	HTREEITEM	ghAMPrev; 
static	HTREEITEM	ghAMPrevRootItem; 
static	HTREEITEM	ghAMPrevLev2Item; 
static	HTREEITEM	ghAMPrevLev3Item;

static	BOOL		DLGaudioLoaded;
static	unsigned char	DLGonOffFlags = 0;

extern char*	NoCD_Text;

#ifndef FINAL
	extern BOOL no_cd_ok;
#endif


	static void RemoveStaleSessions(void);
    static void ResetTreeRefresh(void);

//================================================================
//					CLASS FUNCTIONS
//================================================================

void	DLGinit( void )
{
	// initialize Global Static variables
	gCWndCtlSP    = NULL;	
	gCWndCtlMaps  = NULL;
	gCWndCtlAudio = NULL;	
	gCWndOldFocus = NULL;	

	ghAMPrev = (HTREEITEM) TVI_FIRST; 
	ghAMPrevRootItem = NULL; 
	ghAMPrevLev2Item = NULL; 
	ghAMPrevLev3Item = NULL; 

	// setup fonts
	HDC hdc = GetDC(ghWndMain);
	SetupFonts(hdc);
	ReleaseDC(ghWndMain, hdc);

}

void	DLGexit( void )
{
    // cleanup
    CleanupFonts();
}


/////////////////////////////////////////////////////////////////////////////
// CProviderDlg dialog

LRESULT CProviderDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)	{
		case WM_SYSCOMMAND:
			if( wParam == SC_SCREENSAVE )
				return TRUE;
			break;
	}
	return CDialog::WindowProc(message, wParam, lParam);

}

CProviderDlg::CProviderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProviderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProviderDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_ItemIndex = 0;
	//}}AFX_DATA_INIT
}


void CProviderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProviderDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProviderDlg, CDialog)
	//{{AFX_MSG_MAP(CProviderDlg)
	ON_BN_CLICKED(IDCANCEL, OnProviderSetupCancel)
	ON_BN_CLICKED(ID_BACK, OnProviderSetupBack)
	ON_BN_CLICKED(ID_NEXT, OnProviderSetupNext)
	ON_LBN_SELCHANGE(IDC_SERVICEPROVIDERS, OnProviderSetupSelChange)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProviderDlg message handlers

BOOL CProviderDlg::OnInitDialog() 
{
	BYTE    szSPGuid[GUIDSTR_MAX+1];
    WCHAR   wszSPGuid[GUIDSTR_MAX+1];
	DWORD   dwSize = sizeof(szSPGuid);
	int     i;
	CWnd*	CWndCtl;
	HRESULT hr;
	CDialog::OnInitDialog();
	LPVOID  lpConn = NULL;
	LPSPCONTEXT lpSPContext;
	// TODO: Add extra initialization here
    SendDlgItemMessage( IDC_SP_TITLE, WM_SETFONT, (WPARAM)ghTitleFont, MAKELPARAM(TRUE,0) );

    // remember the service provider control. used later in freeing sp information.
    CWndCtl = GetDlgItem( IDC_SERVICEPROVIDERS );
    if (CWndCtl == NULL)
		return(TRUE);
    gCWndCtlSP = CWndCtl;

	// acquire input focus for this dialog
    gCWndOldFocus = SetFocus();
	gAMSPContext.lpConnection = NULL;
	gAMSPContext.dwConnectionSize = 0;

	// now get the list of service providers
   // DirectPlayEnumerate( DLGEnumCallback, (LPVOID)CWndCtl );
	if ( (hr = gpComm->DPlayCreate(lpConn)) != DP_OK )
	{
		// Class Not available
		if ((hr == REGDB_E_CLASSNOTREG) || (hr == REGDB_E_IIDNOTREG))
			ShowError(IDS_DPERR_CLSID);
		else
			ShowError(IDS_DPLAY_ERROR_IDC);
		TRACE("DPLAY CREATE FAILED \n");
		return TRUE; //  ????	 or should this PostQuit Message.  Single player may still be playable


	}


	gpComm->EnumConnections(gpComm->m_pGuid,DPEnumConnCallback,(LPVOID)CWndCtl,(DWORD)NULL);

    // setup user's saved preferences
  	if (gpComm->RegGet(TEXT("ServiceProvider"), szSPGuid, &dwSize))
    {
        AnsiToWide(wszSPGuid, (char *)szSPGuid, sizeof(szSPGuid));
        GUIDFromString(wszSPGuid, &gAMSPContext.spGUID);

        for (i=0; i<CWndCtl->SendMessage( LB_GETCOUNT, 0, 0); i++)
        {
            lpSPContext = (LPSPCONTEXT) CWndCtl->SendMessage( LB_GETITEMDATA,i,0 );
			if (IsEqualGuid(&gAMSPContext.spGUID,&lpSPContext->spGUID))
            {
                m_ItemIndex = i;
                break;
            }
        }
    }

    CWndCtl->SendMessage( LB_SETCURSEL, m_ItemIndex, 0 );
    m_ItemIndex = CWndCtl->SendMessage( LB_GETCURSEL, 0, 0 );
	
	// set the cursor to the NEXT button
    SendDlgItemMessage( ID_NEXT, WM_SETCURSOR, 0, 0 );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CProviderDlg::OnProviderSetupBack() 
{
	// TODO: Add your control notification handler code here
	DLGReleaseSPData();
	CDialog::EndDialog( ID_BACK );		// return the ID_BACK value
}

void CProviderDlg::OnProviderSetupNext() 
{
 //   LPGUID  lpGuid;
    HRESULT hr;
	LPSPCONTEXT lpSPContext;
	// TODO: Add your control notification handler code here
	gpComm->Release();
    if (m_ItemIndex != LB_ERR)
    {
        lpSPContext = (LPSPCONTEXT) gCWndCtlSP->SendMessage( LB_GETITEMDATA, m_ItemIndex, 0 );
        if (lpSPContext)
        {
            // remember the selection
            gAMSPContext.spGUID = lpSPContext->spGUID;
			if(gAMSPContext.lpConnection) free(gAMSPContext.lpConnection );
			gAMSPContext.lpConnection = NULL;
			if (lpSPContext->dwConnectionSize) {
				gAMSPContext.lpConnection = (LPVOID) malloc(lpSPContext->dwConnectionSize);
				if( gAMSPContext.lpConnection == NULL) goto exit;
				memcpy(gAMSPContext.lpConnection,lpSPContext->lpConnection,lpSPContext->dwConnectionSize);
			}
            // create directplay object
            if ((hr = gpComm->DPlayCreate(gAMSPContext.lpConnection)) == DP_OK)
                goto exit;
            else
                ShowError( IDS_DPLAY_ERROR_IDC );
        }
    }
exit:
	DLGReleaseSPData();
	CDialog::EndDialog( ID_NEXT );		// return the ID_NEXT value
}

void CProviderDlg::OnProviderSetupCancel() 
{
	// TODO: Add your control notification handler code here
	DLGReleaseSPData();
	gpComm->Release();
 	if( gAMSPContext.lpConnection) free(gAMSPContext.lpConnection);
	gAMSPContext.lpConnection = NULL;

	CDialog::OnCancel();
}

void CProviderDlg::OnProviderSetupSelChange() 
{
	// TODO: Add your control notification handler code here
    m_ItemIndex = gCWndCtlSP->SendMessage( LB_GETCURSEL, 0, 0 );
}

void CProviderDlg::OnMove(int x, int y) 
{
	pMainFrame->UpdateView();
	CDialog::OnMove(x, y);
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME); 
}

/////////////////////////////////////////////////////////////////////////////
// CConnectStatusDlg dialog


LRESULT CConnectStatusDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)	{
		case WM_SYSCOMMAND:
			if( wParam == SC_SCREENSAVE )
				return TRUE;
			break;
	}
	return CDialog::WindowProc(message, wParam, lParam);

}


CConnectStatusDlg::CConnectStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectStatusDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConnectStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectStatusDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectStatusDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectStatusDlg message handlers


BOOL CConnectStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CGameSetupDlg dialog


LRESULT CGameSetupDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)	{
		case WM_SYSCOMMAND:
			if( wParam == SC_SCREENSAVE )
				return TRUE;
			break;
	}
	return CDialog::WindowProc(message, wParam, lParam);

}

CGameSetupDlg::CGameSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameSetupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGameSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameSetupDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGameSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CGameSetupDlg)
	ON_BN_CLICKED(IDCANCEL, OnGameSetupCancel)
	ON_BN_CLICKED(IDC_HOSTSESSION, OnGameSetupHostSession)
	ON_BN_CLICKED(IDC_JOINSESSION, OnGameSetupJoinSession)
	ON_BN_CLICKED(ID_NEXT, OnGameSetupNext)
	ON_BN_CLICKED(ID_BACK, OnGameSetupBack)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameSetupDlg message handlers

BOOL CGameSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    // setup title fonts
    SendDlgItemMessage( IDC_GAMESETUP_TITLE, WM_SETFONT, (WPARAM)ghTitleFont,   MAKELPARAM(TRUE,0) );
    SendDlgItemMessage( IDC_JOINSESSION,     WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0) );
    SendDlgItemMessage( IDC_HOSTSESSION,     WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0) );
    // host by default
    SendDlgItemMessage( IDC_HOSTSESSION,     BM_SETCHECK, 0, 0 );
    SendDlgItemMessage( IDC_JOINSESSION,     BM_SETCHECK, 1, 0 );

	m_SessionType = DLG_JOIN_SESSION;		// initialize to a host session
	m_HostButton  = DLG_BUTTON_OFF;			// initialize to a host session
	m_JoinButton  = DLG_BUTTON_ON;			// initialize join session

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CGameSetupDlg::OnGameSetupBack() 
{
	// TODO: Add your control notification handler code here

	CDialog::EndDialog( ID_BACK );		// return the ID_BACK value
}

void CGameSetupDlg::OnGameSetupNext() 
{
	BOOL done;

    switch (m_SessionType)
    {
    case DLG_HOST_SESSION:
		done = FALSE;

        if ( SendDlgItemMessage( IDC_HOSTSESSION, BM_GETCHECK, 1, 0 ) == 1)
		{

#ifndef FINAL
			if (!no_cd_ok)
#endif
			{
				while (!done)	{
					if (gPaths.LocateCdromDrive() != LCD_NO_ERROR )	{
						  
						// inactivate the dialog
						EnableWindow(FALSE);

						if (pMainFrame->OnErrorDialog(NoCD_Text, TRUE) != 0)	{
							done = TRUE;

							// reactivate the dialog
							EnableWindow();
							RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME); 
							return;
						}
					}
					else
						done = TRUE;
				}
			}

            gpComm->m_bHost  = TRUE;
			gpGame->GameType = GAMETYPE_HOST_MULTIPLAYER;
			gpGame->start_game = TRUE;   // still in start-up phase don't send game messages yet
		}
        break;
    case DLG_JOIN_SESSION:
        if ( SendDlgItemMessage( IDC_JOINSESSION, BM_GETCHECK, 1, 0 ) == 1)
		{
            gpComm->m_bHost  = FALSE;
			gpGame->GameType = GAMETYPE_REMOTE_MULTIPLAYER;
			gpGame->start_game = TRUE;   // still in start-up phase don't send game messages yet
		}
        break;
    }
	CDialog::OnOK();

	CDialog::EndDialog( ID_NEXT );		// return the ID_NEXT value
}

void CGameSetupDlg::OnGameSetupCancel() 
{
	// TODO: Add your control notification handler code here
	gpComm->Release();
	CDialog::OnCancel();
}

void CGameSetupDlg::OnGameSetupHostSession() 
{
	// TODO: Add your control notification handler code here
	m_SessionType = DLG_HOST_SESSION;

	// now turn on the radial button for this HOST and turn
	// off the button for Join
	m_HostButton = TRUE;
	SendDlgItemMessage( IDC_HOSTSESSION, BM_SETCHECK, 1, 0 );
	m_JoinButton = FALSE;
	SendDlgItemMessage( IDC_JOINSESSION, BM_SETCHECK, 0, 0 );
}

void CGameSetupDlg::OnGameSetupJoinSession() 
{
	// TODO: Add your control notification handler code here
	m_SessionType = DLG_JOIN_SESSION;
	
	// now turn on the radial button for this HOST and turn
	// off the button for Join
	m_HostButton = FALSE;
	SendDlgItemMessage( IDC_HOSTSESSION, BM_SETCHECK, 0, 0 );
	m_JoinButton = TRUE;
	SendDlgItemMessage( IDC_JOINSESSION, BM_SETCHECK, 1, 0 );
}

int CGameSetupDlg::OnSessionType() 
{
	int		result;

	if ( m_SessionType == DLG_HOST_SESSION )
		result = OnHostSessionDialog();	// try the next dialog box
	else
		result = OnJoinSessionDialog();	// try the next dialog box

	return( result );
}


int CGameSetupDlg::OnHostSessionDialog() 
{
	int				result  = IDCANCEL;
	BOOL			done    = FALSE;
	CHostSessionDlg hostSessionDlg;

	// TODO: Add your command handler code here
	while ( !done )
	{
		result = hostSessionDlg.DoModal();
			done = TRUE;
	}

	return( result );
}

int CGameSetupDlg::OnJoinSessionDialog() 
{
	int				result  = IDCANCEL;
	BOOL			done    = FALSE;
	CJoinSessionDlg joinSessionDlg;

	// TODO: Add your command handler code here
	while ( !done )
	{
		result  = joinSessionDlg.DoModal();
			done = TRUE;
	}

	return( result );
}


void CGameSetupDlg::OnMove(int x, int y) 
{
	pMainFrame->UpdateView();
	CDialog::OnMove(x, y);
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME); 
}


/////////////////////////////////////////////////////////////////////////////
// CHostSessionDlg dialog

LRESULT CHostSessionDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)	{
		case WM_SYSCOMMAND:
			if( wParam == SC_SCREENSAVE )
				return TRUE;
			break;
	}
	return CDialog::WindowProc(message, wParam, lParam);

}


CHostSessionDlg::CHostSessionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHostSessionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHostSessionDlg)
	//}}AFX_DATA_INIT
//	GetDlgItemText( IDC_HOST_SESSIONNAME, gAMtszSessionName, MAX_SESSIONNAME);
//	GetDlgItemText( IDC_HOST_PLAYERNAME, gAMtszPlayerName, MAX_PLAYERNAME);
}


void CHostSessionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHostSessionDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHostSessionDlg, CDialog)
	//{{AFX_MSG_MAP(CHostSessionDlg)
	ON_BN_CLICKED(IDD_GAMESETUP, OnHostSessionBack)
	ON_BN_CLICKED(ID_NEXT, OnHostSessionNext)
	ON_BN_CLICKED(IDCANCEL, OnHostSessionCancel)
	ON_EN_CHANGE(IDC_HOST_PLAYERNAME, OnHostSessionPlayerNameChange)
	ON_EN_CHANGE(IDC_HOST_SESSIONNAME, OnHostSessionSessionNameChange)
	ON_BN_CLICKED(ID_BACK, OnHostSessionBack)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHostSessionDlg message handlers

BOOL CHostSessionDlg::OnInitDialog() 
{
	DWORD   dwPNameSize;
	DWORD   dwSNameSize;

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// setup title font
	SendDlgItemMessage( IDC_HOST_TITLE,         WM_SETFONT, (WPARAM)ghTitleFont,   MAKELPARAM(TRUE,0) );
	SendDlgItemMessage( IDC_HOST_SESSION_TITLE, WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0) );
	SendDlgItemMessage( IDC_HOST_PLAYER_TITLE,  WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0) );

	dwPNameSize = MAX_PLAYERNAME+1;
	dwSNameSize = MAX_SESSIONNAME+1;
	gAMtszPlayerName[0]=0;
	gAMtszSessionName[0]=0;
  	if (gpComm->RegGet(TEXT("PlayerName"), (LPBYTE)gAMtszPlayerName, &dwPNameSize))
	{
		SetDlgItemText( IDC_HOST_PLAYERNAME, gAMtszPlayerName );
		strcpy( gpComm->m_PlayerName[0], gAMtszPlayerName );
	}
  	if (gpComm->RegGet(TEXT("SessionName"), (LPBYTE)gAMtszSessionName, &dwSNameSize))
		SetDlgItemText( IDC_HOST_SESSIONNAME, gAMtszSessionName );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHostSessionDlg::OnHostSessionBack() 
{
	// TODO: Add your control notification handler code here
	CDialog::EndDialog( ID_BACK );
}

void CHostSessionDlg::OnHostSessionNext() 
{
    HRESULT hr;
    WCHAR   wszSPGuid[GUIDSTR_MAX+1];
    BYTE    szSPGuid[GUIDSTR_MAX+1];
	int		result = IDCANCEL;

	// TODO: Add your control notification handler code here
    // add user selections to registry
	StringFromGUID( &gAMSPContext.spGUID, wszSPGuid );
    WideToAnsi((char *)szSPGuid, wszSPGuid, sizeof(wszSPGuid) );
	gpComm->RegSetA(TEXT("ServiceProvider"), (CONST BYTE *)szSPGuid, sizeof(szSPGuid));
	strcpy( gpComm->m_PlayerName[0], gAMtszPlayerName );
	if ( strlen( gAMtszSessionName) == 0 ) return;
 	if ( strlen( gAMtszPlayerName) == 0 )  return;
 	gpComm->RegSet(TEXT("PlayerName"), (CONST BYTE *)gAMtszPlayerName, sizeof(gAMtszPlayerName));
	gpComm->RegSet(TEXT("SessionName"), (CONST BYTE *)gAMtszSessionName, sizeof(gAMtszSessionName));

    // create session
    if ((hr = gpComm->CreateSession( gAMtszSessionName )) != DP_OK)
    {
        // fail finish
        ShowError( IDS_DPLAY_ERROR_CS );
        goto exit;
    }

    // create player
    if ((hr = gpComm->CreatePlayer( gAMtszPlayerName, NULL, NULL, 0)) != DP_OK)
    {
        ShowError( IDS_DPLAY_ERROR_CP );
        goto exit;
    }

    // everything went well, release allocated memory and finish
 	if( gAMSPContext.lpConnection) free(gAMSPContext.lpConnection);
	gAMSPContext.lpConnection = NULL;
	result = ID_NEXT;

exit:
	CDialog::EndDialog( result );		// return the ID_NEXT value
}

void CHostSessionDlg::OnHostSessionCancel() 
{
	// TODO: Add your control notification handler code here
	gpComm->Release();
 	if( gAMSPContext.lpConnection) free(gAMSPContext.lpConnection);
	gAMSPContext.lpConnection = NULL;

	CDialog::OnCancel();
}


void CHostSessionDlg::OnHostSessionPlayerNameChange() 
{
	// TODO: Add your control notification handler code here
    GetDlgItemText( IDC_HOST_PLAYERNAME,  gAMtszPlayerName, MAX_PLAYERNAME);
}

void CHostSessionDlg::OnHostSessionSessionNameChange() 
{
	// TODO: Add your control notification handler code here
    GetDlgItemText( IDC_HOST_SESSIONNAME, gAMtszSessionName, MAX_SESSIONNAME);
}

void CHostSessionDlg::OnMove(int x, int y) 
{
	pMainFrame->UpdateView();
	CDialog::OnMove(x, y);
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME); 
}


/////////////////////////////////////////////////////////////////////////////
// CJoinSessionDlg dialog

LRESULT CJoinSessionDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)	{
		case WM_SYSCOMMAND:
			if( wParam == SC_SCREENSAVE )
				return TRUE;
			break;
	}
	return CDialog::WindowProc(message, wParam, lParam);

}


CJoinSessionDlg::CJoinSessionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJoinSessionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJoinSessionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CJoinSessionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJoinSessionDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJoinSessionDlg, CDialog)
	//{{AFX_MSG_MAP(CJoinSessionDlg)
	ON_BN_CLICKED(IDCANCEL, OnJoinSessionCancel)
	ON_BN_CLICKED(ID_BACK, OnJoinSessionBack)
	ON_BN_CLICKED(ID_NEXT, OnJoinSessionNext)
	ON_EN_UPDATE(IDC_JOIN_PLAYERNAME, OnJoinPlayernameUpdate)
	ON_NOTIFY(TVN_SELCHANGING, IDC_JOIN_SESSION, OnJoinSessionSelchanging)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJoinSessionDlg message handlers
static UINT EnumTimer;


BOOL CJoinSessionDlg::OnInitDialog() 
{
	HWND		hTreeCtl;
    DWORD		dwPNameSize;
	HTREEITEM	htiNext;
	HRESULT     hr;

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    // remember the session control. used later in freeing sp information.
	gCWndCtlMaps = GetDlgItem( IDC_JOIN_SESSION );
    hTreeCtl     = gCWndCtlMaps->m_hWnd;
	// setup title fonts
    SendDlgItemMessage( IDC_JOIN_SESSION_TITLE, WM_SETFONT, (WPARAM)ghTitleFont, MAKELPARAM(TRUE,0) );
    SendDlgItemMessage( IDC_JOIN_PLAYER_TITLE,  WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0) );

    // setup user's previous data
    dwPNameSize = MAX_PLAYERNAME+1;
    gAMtszPlayerName[0]=0;
	if (gpComm->RegGet(TEXT("PlayerName"), (LPBYTE)gAMtszPlayerName, &dwPNameSize))
	{
        SetDlgItemText( IDC_JOIN_PLAYERNAME, gAMtszPlayerName );
		strcpy( gpComm->m_PlayerName[0], gAMtszPlayerName );
	}

    if (hTreeCtl == NULL)
		goto exit;
	DLGInitTreeViewImageLists( hTreeCtl );
	TreeView_DeleteAllItems( hTreeCtl );

	// Enumerate once synchronously first 
		hr = gpComm->EnumSessions( 0, DLGEnumSession, (LPVOID) hTreeCtl, NULL );
		if (hr == DPERR_USERCANCEL) OnJoinSessionCancel();

	
	EnumTimer = SetTimer( ENUM_TIMER_EVENT, ENUM_TIMEOUT, NULL);
	
	// enum sessions and let dplay decide the timeout
    hr = gpComm->EnumSessions( 0, DLGEnumSession, (LPVOID) hTreeCtl, (EnumTimer ?  DPENUMSESSIONS_ASYNC : NULL) );
	if (hr == DPERR_USERCANCEL) OnJoinSessionCancel();

    // enumerate players for all sessions
    gAMhtiSession = TreeView_GetFirstVisible( hTreeCtl );

    while ( gAMhtiSession )
    {
        // delete previous players from display
        if ((htiNext = gAMhtiCur = TreeView_GetChild( hTreeCtl, gAMhtiSession )) 
            != (HTREEITEM)0)
        {
            do
            {
                htiNext = TreeView_GetNextSibling( hTreeCtl, gAMhtiCur );
                TreeView_DeleteItem( hTreeCtl, gAMhtiCur );
                gAMhtiCur = htiNext;
            } while (htiNext);
        }

        gAMtvItem.hItem = gAMhtiSession;
        gAMtvItem.pszText = gAMtszSessionName;
        gAMtvItem.cchTextMax = MAX_SESSIONNAME;
        TreeView_GetItem(hTreeCtl, &gAMtvItem);

        // enumerate players for selected session
        gpComm->EnumPlayers( (LPGUID)gAMtvItem.lParam, DLGEnumPlayer, (LPVOID) hTreeCtl, DPENUMPLAYERS_SESSION );
        gAMhtiSession = TreeView_GetNextItem( hTreeCtl, gAMhtiSession, TVGN_NEXTVISIBLE );
    }

	GetDlgItemText( IDC_JOIN_PLAYERNAME, gAMtszPlayerName, MAX_PLAYERNAME );
	gAMhtiCur = TreeView_GetSelection( hTreeCtl );

	// acquire the input focus for this dialog
	gCWndOldFocus = SetFocus();
exit:
	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}


void CJoinSessionDlg::OnJoinSessionSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW*	pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HWND			hWndCtl;

	// TODO: Add your control notification handler code here
    gAMnmtv = *pNMTreeView;
	hWndCtl = gCWndCtlMaps->m_hWnd;
	if ( hWndCtl )
	{
		GetDlgItemText( IDC_JOIN_PLAYERNAME, gAMtszPlayerName, MAX_PLAYERNAME );
		gAMhtiCur = TreeView_GetSelection(hWndCtl);
		*pResult = 0;
	}
	else
		*pResult = -1;
	
//	*pResult = 0;
}

void CJoinSessionDlg::OnJoinPlayernameUpdate() 
{
	HWND		hWndCtl;

	// TODO: Add your control notification handler code here
	hWndCtl = gCWndCtlMaps->m_hWnd;
	if ( hWndCtl )
	{
		GetDlgItemText( IDC_JOIN_PLAYERNAME, gAMtszPlayerName, MAX_PLAYERNAME );
		gAMhtiCur = TreeView_GetSelection(hWndCtl);
	}
}

void CJoinSessionDlg::OnTimer(UINT nTimerID)
{ 
 	HWND		hTreeCtl;
	HTREEITEM	htiNext;
	HRESULT		hr;

		TRACE("Entering JoinSession Timer %d \n",nTimerID );
		if ( nTimerID != EnumTimer ) return;
		if(!gCWndCtlMaps) return;
        hTreeCtl = gCWndCtlMaps->m_hWnd;
		ResetTreeRefresh();
		// enum sessions and let dplay decide the timeout
		hr = gpComm->EnumSessions(0, DLGEnumSession, (LPVOID) hTreeCtl, DPENUMSESSIONS_ASYNC);
		if( hr == DPERR_USERCANCEL) OnJoinSessionCancel();

		RemoveStaleSessions();
		
			// set Finish button highlite
//		if (GetDlgItemText(hDlg, IDC_JOIN_PLAYERNAME, tszPlayerName, MAX_PLAYERNAME) && 
//			(htiCur = TreeView_GetSelection(hWndCtl)))
//		{
//			PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_FINISH);
//		}
//		else
//		{
//			PropSheet_SetWizButtons(GetParent(hDlg),PSWIZB_BACK|PSWIZB_DISABLEDFINISH);
//		}
   gAMhtiSession = TreeView_GetFirstVisible( hTreeCtl );

    while ( gAMhtiSession )
    {
        // delete previous players from display
        if ((htiNext = gAMhtiCur = TreeView_GetChild( hTreeCtl, gAMhtiSession )) 
            != (HTREEITEM)0)
        {
            do
            {
                htiNext = TreeView_GetNextSibling( hTreeCtl, gAMhtiCur );
                TreeView_DeleteItem( hTreeCtl, gAMhtiCur );
                gAMhtiCur = htiNext;
            } while (htiNext);
        }

        gAMtvItem.hItem = gAMhtiSession;
        gAMtvItem.pszText = gAMtszSessionName;
        gAMtvItem.cchTextMax = MAX_SESSIONNAME;
        TreeView_GetItem(hTreeCtl, &gAMtvItem);

        // enumerate players for selected session
        gpComm->EnumPlayers( (LPGUID)gAMtvItem.lParam, DLGEnumPlayer, (LPVOID) hTreeCtl, DPENUMPLAYERS_SESSION );
        gAMhtiSession = TreeView_GetNextItem( hTreeCtl, gAMhtiSession, TVGN_NEXTVISIBLE );
    }

	GetDlgItemText( IDC_JOIN_PLAYERNAME, gAMtszPlayerName, MAX_PLAYERNAME );
	gAMhtiCur = TreeView_GetSelection( hTreeCtl );
		TRACE("Exiting JoinSession Timer%d \n",nTimerID);
}
		

void CJoinSessionDlg::OnJoinSessionBack() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr;
	DLGReleaseSessionData();
	if ( EnumTimer) { KillTimer ( EnumTimer); EnumTimer = 0;}
	gpComm->Release();
//    if(gAMSPContext.lpConnection ) free (gAMSPContext.lpConnection);
//	gAMSPContext.lpConnection = NULL ;
	if ((hr = gpComm->DPlayCreate(gAMSPContext.lpConnection)) != DP_OK)
                ShowError( IDS_DPLAY_ERROR_IDC );
	CDialog::EndDialog( ID_BACK );	// return the ID to go back to
}

void CJoinSessionDlg::OnJoinSessionNext() 
{
	HWND		hWndCtl;
    WCHAR		wszSPGuid[GUIDSTR_MAX+1];
    BYTE		szSPGuid[GUIDSTR_MAX+1];
    LPGUID		lpGuid;
    HRESULT		hr;
	int			result = IDCANCEL;

	gCWnd   = GetDlgItem( IDC_JOIN_SESSION );
	hWndCtl = gCWnd->m_hWnd;
	if ( hWndCtl == NULL )
		goto exit;

	// TODO: Add your control notification handler code here
    if ( strlen( gAMtszPlayerName) == 0 )  return;

    // get the session guid
    if (gAMnmtv.itemNew.lParam)
    {
        // user selected a session item, so just grab its lParam
        lpGuid = (LPGUID)gAMnmtv.itemNew.lParam;
    }
    else
    {
        // user selected a player item, so grab its parent's (session) lParam
        gAMhtiCur = TreeView_GetParent(hWndCtl, gAMnmtv.itemNew.hItem);
        if (!gAMhtiCur)
        {
            return;
			// fail finish
            //ShowError(IDS_WIZARD_ERROR_GSG);
            //goto exit;
        }

        gAMtvItem.hItem = gAMhtiCur;
        gAMtvItem.pszText = gAMtszSessionName;
        gAMtvItem.cchTextMax = MAX_SESSIONNAME;
        TreeView_GetItem( hWndCtl, &gAMtvItem );                 
        lpGuid = (LPGUID)gAMtvItem.lParam;
    }

	if ( EnumTimer) {
		 KillTimer ( EnumTimer); 
		 EnumTimer = 0;
	}


    // open session
    if ((hr = gpComm->OpenSession(lpGuid)) != DP_OK)
    {
        // fail finish
        ShowError( IDS_DPLAY_ERROR_JS );
        goto exit;
    }

    // create player
    if ((hr = gpComm->CreatePlayer(gAMtszPlayerName, NULL, NULL, 0)) != DP_OK)
    {
        // fail finish
        ShowError( IDS_DPLAY_ERROR_CP );
        goto exit;
    }
    // everything went well, release allocated memory and finish
    // but first add user selections to registry
    StringFromGUID(&gAMSPContext.spGUID, wszSPGuid);
    WideToAnsi((char *)szSPGuid, wszSPGuid, sizeof(wszSPGuid));
 	gpComm->RegSetA(TEXT("ServiceProvider"), (CONST BYTE *)szSPGuid, sizeof(szSPGuid));
	strcpy( gpComm->m_PlayerName[0], gAMtszPlayerName );
	gpComm->RegSet(TEXT("PlayerName"), (CONST BYTE *)gAMtszPlayerName, sizeof(gAMtszPlayerName));
	result = ID_NEXT;				// success
	InitJoinSession();
exit:
	DLGReleaseSessionData();
 	if( gAMSPContext.lpConnection) free(gAMSPContext.lpConnection);
	gAMSPContext.lpConnection = NULL;
	CDialog::EndDialog( result );		// return the ID_NEXT value
}

void CJoinSessionDlg::OnJoinSessionCancel() 
{
	// TODO: Add your control notification handler code here
	DLGReleaseSessionData();
	if ( EnumTimer) { KillTimer ( EnumTimer); EnumTimer = 0;}
	gpComm->Release();

	CDialog::OnCancel();
}

void CJoinSessionDlg::OnMove(int x, int y) 
{
	pMainFrame->UpdateView();
	CDialog::OnMove(x, y);
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME); 
}


/////////////////////////////////////////////////////////////////////////////
// CAudioDiagnosticDlg dialog


CAudioDiagnosticDlg::CAudioDiagnosticDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioDiagnosticDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAudioDiagnosticDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_ItemIndex     = 0;
	m_OldItemIndex  = -1;
	m_Button        = DLG_SFX_BUTTON;			// which button selected
	//}}AFX_DATA_INIT

	audioDisable();
}


void CAudioDiagnosticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAudioDiagnosticDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAudioDiagnosticDlg, CDialog)
	//{{AFX_MSG_MAP(CAudioDiagnosticDlg)
	ON_BN_CLICKED(IDC_SFX_GROUP, OnAudioDiagnosticSfxGroup)
	ON_BN_CLICKED(IDC_STREAM_GROUP, OnAudioDiagnosticStreamGroup)
	ON_BN_CLICKED(IDC_PLAY_AUDIO_BUTTON, OnAudioDiagnosticPlayButton)
	ON_BN_CLICKED(IDC_STOP_AUDIO_BUTTON, OnAudioDiagnosticStopButton)
	ON_LBN_SELCHANGE(IDC_AUDIO_LIST, OnAudioDiagnosticSelchange)
	ON_BN_CLICKED(IDC_EXIT_AUDIO_BUTTON, OnAudioDiagnosticExitButton)
	ON_BN_CLICKED(IDC_VOICE_GROUP, OnAudioDiagnosticVoiceGroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioDiagnosticDlg message handlers


BOOL CAudioDiagnosticDlg::OnInitDialog() 
{
	BOOL	bSfxButton;
	BOOL	bStreamButton;
	BOOL	bVoiceButton;

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	audioEnable( pMainFrame->m_hWnd );
	audioSfxOff();
	audioMusicOff();
	audioVoiceOff();
	
    // setup title fonts
    SendDlgItemMessage( IDC_AUDIO_DIAG_TITLE, WM_SETFONT, (WPARAM)ghTitleFont, MAKELPARAM(TRUE,0) );
    SendDlgItemMessage( IDC_SFX_GROUP,  WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0) );
    SendDlgItemMessage( IDC_STREAM_GROUP, WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0) );
    SendDlgItemMessage( IDC_VOICE_GROUP, WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0) );

	// now set the radial button states
	bSfxButton = FALSE;
	if ( m_Button == DLG_SFX_BUTTON )
		bSfxButton = TRUE;
    SendDlgItemMessage( IDC_SFX_GROUP,  BM_SETCHECK, bSfxButton,  0 );

	bStreamButton = FALSE;
	if ( m_Button == DLG_STRM_BUTTON )
		bStreamButton = TRUE;
    SendDlgItemMessage( IDC_STREAM_GROUP,  BM_SETCHECK, bStreamButton,  0 );

	bVoiceButton = FALSE;
	if ( m_Button == DLG_VOICE_BUTTON )
		bVoiceButton = TRUE;
    SendDlgItemMessage( IDC_VOICE_GROUP,  BM_SETCHECK, bVoiceButton,  0 );

    // access the list box for the audio names.
	if (!gCWndCtlAudio)
	{
		gCWndCtlAudio = GetDlgItem( IDC_AUDIO_LIST );
		if (gCWndCtlAudio == NULL)
			return(TRUE);
	}

	// now get the list of audio sounds.
    DLGEnumerateAudio( DLG_SFX_BUTTON, gCWndCtlAudio );

	// initialize the current select item
	gCWndCtlAudio->SendMessage( LB_SETCURSEL, m_ItemIndex, 0 );
    m_ItemIndex = gCWndCtlAudio->SendMessage( LB_GETCURSEL, 0, 0 );

	// remember the current audio settings to restore later
	if ( gpGame->Sfx )
		DLGonOffFlags |= SND_SFX_FLAG;
	gpGame->Sfx = TRUE;
	audioSfxOn();
	if ( gpGame->Music )
		DLGonOffFlags |= SND_MUSIC_FLAG;
	gpGame->Music = TRUE;
	audioMusicOn();
	if ( gpGame->Voice )
		DLGonOffFlags |= SND_VOICE_FLAG;
	gpGame->Voice = TRUE;
	audioVoiceOn();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAudioDiagnosticDlg::OnAudioDiagnosticSfxGroup() 
{
	// TODO: Add your control notification handler code here

    // access the list box for the audio names.
	if (!gCWndCtlAudio)
	{
		gCWndCtlAudio = GetDlgItem( IDC_AUDIO_LIST );
		if (gCWndCtlAudio == NULL)
			return;
	}
	else
	{
		// release any existing data
		DLGReleaseAudioData();
	}

	// now get the list of audio sounds.
    DLGEnumerateAudio( DLG_SFX_BUTTON, gCWndCtlAudio );

	// initialize the current select item
	m_ItemIndex = 0;
	gCWndCtlAudio->SendMessage( LB_SETCURSEL, m_ItemIndex, 0 );
    m_ItemIndex = gCWndCtlAudio->SendMessage( LB_GETCURSEL, 0, 0 );
}

void CAudioDiagnosticDlg::OnAudioDiagnosticStreamGroup() 
{
	// TODO: Add your control notification handler code here

    // access the list box for the audio names.
	if (!gCWndCtlAudio)
	{
		gCWndCtlAudio = GetDlgItem( IDC_AUDIO_LIST );
		if (gCWndCtlAudio == NULL)
			return;
	}
	else
	{
		// release any existing data
		DLGReleaseAudioData();
	}

	// now get the list of audio sounds.
    DLGEnumerateAudio( DLG_STRM_BUTTON, gCWndCtlAudio );

	// initialize the current select item
	m_ItemIndex = 0;
	gCWndCtlAudio->SendMessage( LB_SETCURSEL, m_ItemIndex, 0 );
    m_ItemIndex = gCWndCtlAudio->SendMessage( LB_GETCURSEL, 0, 0 );
}

void CAudioDiagnosticDlg::OnAudioDiagnosticVoiceGroup() 
{
	// TODO: Add your control notification handler code here

    // access the list box for the audio names.
	if (!gCWndCtlAudio)
	{
		gCWndCtlAudio = GetDlgItem( IDC_AUDIO_LIST );
		if (gCWndCtlAudio == NULL)
			return;
	}
	else
	{
		// release any existing data
		DLGReleaseAudioData();
	}

	// now get the list of audio sounds.
    DLGEnumerateAudio( DLG_VOICE_BUTTON, gCWndCtlAudio );

	// initialize the current select item
	m_ItemIndex = 0;
	gCWndCtlAudio->SendMessage( LB_SETCURSEL, m_ItemIndex, 0 );
    m_ItemIndex = gCWndCtlAudio->SendMessage( LB_GETCURSEL, 0, 0 );
}

void CAudioDiagnosticDlg::OnAudioDiagnosticPlayButton() 
{
	char	pSoundName[ SND_MAX_NAME_LEN + 1 ];
	ULONG	nSndID;

	// TODO: Add your control notification handler code here
	if ( m_OldItemIndex != -1 )
	{
		// stop the exisiting audio
		gCWndCtlAudio->SendMessage( LB_GETTEXT, m_OldItemIndex, (LPARAM)(LPCTSTR)(pSoundName) );
		nSndID = (ULONG)(gCWndCtlAudio->SendMessage( LB_GETITEMDATA, m_OldItemIndex, 0 ));
		if ( nSndID != LB_ERR )
		{
			// now stop the audio
			audioStop( nSndID );
		}
		m_OldItemIndex = -1;
	}

	gCWndCtlAudio->SendMessage( LB_GETTEXT, m_ItemIndex, (LPARAM)(LPCTSTR)(pSoundName) );
	nSndID = (ULONG)(gCWndCtlAudio->SendMessage( LB_GETITEMDATA, m_ItemIndex, 0 ));
	if ( nSndID != LB_ERR )
	{
		// now play the audio
		sndPlay( nSndID );
	}
}

void CAudioDiagnosticDlg::OnAudioDiagnosticStopButton() 
{
	
	char	pSoundName[ SND_MAX_NAME_LEN + 1 ];
	ULONG	nSndID;

	// TODO: Add your control notification handler code here
	gCWndCtlAudio->SendMessage( LB_GETTEXT, m_ItemIndex, (LPARAM)(LPCTSTR)(pSoundName) );
	nSndID = (ULONG)(gCWndCtlAudio->SendMessage( LB_GETITEMDATA, m_ItemIndex, 0 ));
	if ( nSndID != LB_ERR )
	{
		// now stop the audio
		sndHalt( nSndID );
	}
	m_OldItemIndex = -1;
}

void CAudioDiagnosticDlg::OnAudioDiagnosticExitButton() 
{
	// TODO: Add your control notification handler code here
	DLGReleaseAudioData();

	// restore the audio settings
	if ( (DLGonOffFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
	{
		DLGonOffFlags &= ~SND_SFX_FLAG;
		gpGame->Sfx    = TRUE;
		audioSfxOn();
	}
	else
	{
		gpGame->Sfx = FALSE;
		audioSfxOff();
	}
	if ( (DLGonOffFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
	{
		DLGonOffFlags &= ~SND_MUSIC_FLAG;
		gpGame->Music  = TRUE;
		audioMusicOn();
	}
	else
	{
		gpGame->Music = FALSE;
		audioMusicOff();
	}
	if ( (DLGonOffFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
	{
		DLGonOffFlags &= ~SND_VOICE_FLAG;
		gpGame->Voice  = TRUE;
		audioVoiceOn();
	}
	else
	{
		gpGame->Voice = FALSE;
		audioVoiceOff();
	}

	gCWndCtlAudio  = NULL;

	CDialog::OnOK();
}

void CAudioDiagnosticDlg::OnAudioDiagnosticSelchange() 
{
	// TODO: Add your control notification handler code here
	// acquire the current select item
	m_OldItemIndex = m_ItemIndex;
    m_ItemIndex    = gCWndCtlAudio->SendMessage( LB_GETCURSEL, 0, 0 );
}

//================================================================
//			SUPPORT Routines
//================================================================
/*
 * DLGEnumCallback
 *
 * Stores the service provider information in the 
 * passed in list box control.
 */
static	BOOL WINAPI DLGEnumCallback(LPGUID lpGuid, LPTSTR lptszDesc, DWORD dwMajorVersion,
                   DWORD dwMinorVersion, LPVOID lpv)
{
    LONG iIndex;
    CWnd* CWndCtl = (CWnd*) lpv;
	LPSPCONTEXT lpSPContext;
    // insert service provider description in the list box item
    iIndex = CWndCtl->SendMessage( LB_ADDSTRING, 0, (LPARAM) lptszDesc );

    // allocate memory to remember the service provider guid
    
	lpSPContext = (LPSPCONTEXT) malloc(sizeof(SPCONTEXT));
    if (!lpSPContext) return FALSE;

    // copy guid
    lpSPContext->spGUID;
	lpSPContext->lpConnection = NULL;
 	lpSPContext->dwConnectionSize = 0;


    // store the service provider guid pointer as item data
    if (iIndex != LB_ERR)
        CWndCtl->SendMessage( LB_SETITEMDATA, iIndex, (LPARAM) lpSPContext );

    return(TRUE);
}

/*
 * DPEnumConnCallback
 *
 * creates SP list box entries and associates connection data with them
 */
static	BOOL WINAPI DPEnumConnCallback( LPCGUID lpguidSP, LPVOID	lpConnection,
	DWORD		dwConnectionSize,
    LPCDPNAME   lpName,
	DWORD 		dwFlags,
	LPVOID 		lpContext)   {
    LONG iIndex;
    CWnd* CWndCtl = (CWnd*) lpContext;
	LPSPCONTEXT lpSPContext;

	// store service provider name in combo box
    iIndex = CWndCtl->SendMessage( LB_ADDSTRING, 0, (LPARAM) lpName->lpszShortNameA);
	if (iIndex == CB_ERR)
		goto FAILURE;

	// make space for Connection Shortcut
	lpSPContext = (LPSPCONTEXT) malloc(sizeof(SPCONTEXT));
	if (lpSPContext == NULL)
		goto FAILURE;
	lpSPContext->spGUID = *lpguidSP;
	lpSPContext->lpConnection = NULL;
 	lpSPContext->dwConnectionSize = 0;
	lpSPContext->lpConnection = malloc(dwConnectionSize);
	if (lpSPContext->lpConnection == NULL)
		goto FAILURE;
	lpSPContext->dwConnectionSize = dwConnectionSize;
	// store pointer to GUID in combo box
	memcpy(lpSPContext->lpConnection, lpConnection, dwConnectionSize);

	if (iIndex != LB_ERR)
		CWndCtl->SendMessage(LB_SETITEMDATA, iIndex, (LPARAM) lpSPContext);

FAILURE:
    return (TRUE);
}


/*
 * DLGEnumPlayer
 *
 * Inserts player information into the passed in tree view control.
 */
BOOL WINAPI DLGEnumPlayer(DPID pidID, DWORD dwPlayerType, LPCDPNAME lpName,
    DWORD dwFlags, LPVOID lpContext)
{
    HWND hWnd = (HWND) lpContext;
    HTREEITEM hItem;

#ifdef UNICODE
    hItem = DLGAddItemToTree( hWnd, lpName->lpszShortName, 0, -1);
#else
    hItem = DLGAddItemToTree( hWnd, lpName->lpszShortNameA, 0, -1);
#endif

    return(TRUE);
}

/*
 * DLGEnumSession
 *
 * Inserts session description information in the passed in 
 * tree view control.
 */
BOOL WINAPI DLGEnumSession(LPCDPSESSIONDESC2 lpDPSessionDesc, LPDWORD lpdwTimeOut, DWORD dwFlags, 
                        LPVOID lpContext)
{
    HWND hWnd = (HWND) lpContext;
    HTREEITEM hItem;
	LPTREEDATA lpdata;
	HTREEITEM	hr;

    if(dwFlags & DPESC_TIMEDOUT) return FALSE;       // don't try again

    if (hWnd == NULL) return FALSE;

    // allocate memory to remember the guid
    lpdata = (LPTREEDATA) malloc(sizeof(TREEDATA));
    if (!lpdata) return FALSE;

   	lpdata->guid = lpDPSessionDesc->guidInstance;
	lpdata->dwRefresh = 1;
#ifdef UNICODE
    hItem = DLGAddItemToTree(hWnd, lpDPSessionDesc->lpszSessionName, (DWORD)lpdata, 1);
#else
    hItem = DLGAddItemToTree(hWnd, lpDPSessionDesc->lpszSessionNameA, (DWORD)lpdata, 1);
#endif
    if (hItem) {
		hr = TreeView_SelectItem(hWnd, hItem);
		if ( hr == NULL )
			TRACE( "WARNING: TreeView_SelectItem failed\n" );
	} else  // it was alredy in treeview
		free ( lpdata);

    return(TRUE);
}


/*
 * DLGEnumerateAudio
 *
 * Stores the Audio Name and nSndID values in the passed in list box control.
 */
static	BOOL DLGEnumerateAudio( int buttonState, LPVOID lpv )
{
	SND_NAMES*		pNameTable;
    CWnd*			CWndCtl = (CWnd*) lpv;

	// look to see which type of list to build
	pNameTable  = NULL;
	switch ( buttonState )
	{
	case DLG_SFX_BUTTON:
		// use the DLG_sounds_Names table
		pNameTable = SND_sounds_Names;
		break;
	case DLG_STRM_BUTTON:
		// use the DLG_sounds_Names table
		pNameTable = SND_streams_Names;
		break;
	case DLG_VOICE_BUTTON:
		// use the DLG_sounds_Names table
		pNameTable = SND_voices_Names;
		break;
	}

	if ( !gCWndCtlAudio )
			return( FALSE );

	// store this first file into the list box and then look for
	// others
	while ( pNameTable->nAudioID != SND_NULL_SND_ID )
	{
		DLGEnumSound( pNameTable->nAudioID, pNameTable->SndName, gCWndCtlAudio, buttonState );
		++pNameTable;
	}

	DLGaudioLoaded = TRUE;

    return(TRUE);
}

/*
 * DLGEnumSound
 *
 * Stores the Audio Sound information in the 
 * passed in list box control.
 */
//BOOL DLGEnumSound( LPGUID lpGuid, LPTSTR lptszDesc, LPVOID lpv )
static	BOOL DLGEnumSound( ULONG nAudioID, LPTSTR lptszDesc, LPVOID lpv, int nButton )
{
	unsigned	nFileID;
	USHORT		bFlags;
	LONG		iIndex;
	ULONG		nSndID = SND_NULL_SND_ID;
    CWnd*		CWndCtl = (CWnd*) lpv;

    // insert filename in the list box item
    iIndex = CWndCtl->SendMessage( LB_ADDSTRING, 0, (LPARAM) lptszDesc );

	if ( nButton == DLG_SFX_BUTTON )
	{
		nFileID = AUDIOsfxID;
		bFlags  = SND_SFX_FLAG;
	}
	else
	if ( nButton == DLG_STRM_BUTTON )
	{
		nFileID = AUDIOstreamID;
		bFlags  = SND_STREAM_FLAG|SND_MUSIC_FLAG|SND_LOOP_FLAG;
	}
	else
	if ( nButton == DLG_VOICE_BUTTON )
	{
		nFileID = AUDIOvoiceID;
		bFlags  = SND_STREAM_FLAG|SND_VOICE_FLAG|SND_LOOP_FLAG;
	}
	else
		return(TRUE);

    // store the filename guid pointer as item data
    if (iIndex != LB_ERR)
	{
		// acquire an audio snd id
		nSndID = audioCreateSnd( nFileID, nAudioID, 0, bFlags );
		if ( nSndID == SND_NULL_SND_ID )
		{
			// report an error
			TRACE("ERROR: failed to load sound. [%s:%d]\n", 
				__FILE__, __LINE__ );
			return( FALSE );
		}
		audioStoreSnd( nAudioID, nSndID, bFlags );
        CWndCtl->SendMessage( LB_SETITEMDATA, iIndex, (LPARAM) nSndID );
	}

    return(TRUE);
}

/*
 * DLGInitTreeViewImageLists - creates an image list, adds three bitmaps to 
 *     it, and associates the image list with a tree-view control. 
 * Returns TRUE if successful or FALSE otherwise. 
 * hwndTV - handle of the tree-view control 
 *
 * Global variables and constants 
 *     gAMnSession, and gAMnPlayer - integer variables for 
 *         indexes of the images 
 *     CX_BITMAP and CY_BITMAP - width and height of an icon 
 *     NUM_BITMAPS - number of bitmaps to add to the image list 
 */
static	BOOL DLGInitTreeViewImageLists(HWND hwndTV) 
{
	HIMAGELIST hImageList;
    HBITMAP hbmp;     // handle of bitmap 
 
	// Create the image list.
	ghAMPrev = (HTREEITEM) TVI_FIRST; 
	if ((hImageList = ImageList_Create(CX_BITMAP, CY_BITMAP, 
            FALSE, NUM_BITMAPS, 0)) == NULL) 
        return FALSE; 
 
    // Add the session and player bitmaps. 
    hbmp = LoadBitmap(ghinst, MAKEINTRESOURCE(IDB_OPEN_SESSION)); 
    gAMnSession = ImageList_Add(hImageList, hbmp, (HBITMAP) NULL);
	if ( gAMnSession == -1 )
		return(FALSE);
    DeleteObject(hbmp); 
 
    hbmp = LoadBitmap(ghinst, MAKEINTRESOURCE(IDB_PLAYER)); 
    gAMnPlayer = ImageList_Add(hImageList, hbmp, (HBITMAP) NULL); 
	if ( gAMnPlayer == -1 )
		return(FALSE);
    DeleteObject(hbmp); 
 
    // Fail if not all of the images were added. 
    if (ImageList_GetImageCount(hImageList) < 2) 
        return FALSE; 
 
    // Associate the image list with the tree-view control. 
    TreeView_SetImageList(hwndTV, hImageList, TVSIL_NORMAL);

    return TRUE; 
} 

HTREEITEM FindItemInTree(HWND hwndTV,LPTREEDATA pdata)
{
	TV_ITEM item;
    HTREEITEM hItem;
    LPTREEDATA psearchdata;
	if (!gCWndCtlMaps ) return  NULL;
	memset(&item,0,sizeof(item));
	hItem = TreeView_GetRoot(gCWndCtlMaps->m_hWnd);
    while (hItem)
    {
		// gets its data
    	item.mask = TVIF_PARAM;
    	item.hItem = hItem;
		TreeView_GetItem(gCWndCtlMaps->m_hWnd, &item);
		psearchdata = (LPTREEDATA)item.lParam;
		if (IsEqualGuid(&(psearchdata->guid),&(pdata->guid))) 
		{
			// mark the item as seen
			psearchdata->dwRefresh = 1;
			TreeView_SetItem(gCWndCtlMaps->m_hWnd, &item);
			return hItem;
		}
		hItem = TreeView_GetNextSibling( gCWndCtlMaps->m_hWnd, hItem );
	}
    return NULL;
} // FindItemInTree

  /*
 * DLGAddItemToTree - adds items to a tree-view control. 
 * Returns the handle of the newly added item. 
 * hwndTV - handle of the tree-view control 
 * lpszItem - text of the item to add 
 * nLevel - level at which to add the item 
 */
static	HTREEITEM DLGAddItemToTree(HWND hwndTV, LPTSTR lptszItem, DWORD dwData, int nLevel) 
{ 
    TV_ITEM tvi; 
    TV_INSERTSTRUCT tvins; 
	HTREEITEM hItem;

    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    
    // Set the state
  	if (1 == nLevel)
	{
		hItem = FindItemInTree(hwndTV,(LPTREEDATA)dwData);	
		if (hItem) return NULL;
	}
	if (nLevel == 1) 
    {
        tvi.mask |= TVIF_STATE; 
        tvi.state = TVIS_SELECTED;
    }

    // Set the text of the item. 
    tvi.pszText = lptszItem; 
 
   // Set the image
    if (nLevel == 1)
    {
        tvi.iImage = gAMnSession; 
        tvi.iSelectedImage = gAMnSession; 
    }
    else
    {
        tvi.iImage = gAMnPlayer; 
        tvi.iSelectedImage = gAMnPlayer; 
    }
 

    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM) dwData; 
 
    tvins.item = tvi; 
    tvins.hInsertAfter = ghAMPrev; 
 
    // Set the parent item based on the specified level. 
    if (nLevel == -1)
        tvins.hParent = gAMhtiSession;
    else if (nLevel == 1) 
        tvins.hParent = TVI_ROOT; 
    else if (nLevel == 2) 
        tvins.hParent = ghAMPrevRootItem; 
    else
        tvins.hParent = ghAMPrevLev2Item; 
 
    // Add the item to the tree-view control. 
    ghAMPrev = (HTREEITEM)SendMessage( hwndTV, TVM_INSERTITEM, 0, (LPARAM)(LPTV_INSERTSTRUCT)&tvins ); 
 
    // Save the handle of the item. 
    if (nLevel == 1) 
        ghAMPrevRootItem = ghAMPrev; 
    else if (nLevel == 2) 
        ghAMPrevLev2Item = ghAMPrev; 
 
    return ghAMPrev; 
} 
 
/*
 * DLGInitTreeLists - creates a list, and associates the image list with a tree-view control. 
 * Returns TRUE if successful or FALSE otherwise. 
 * hwndTV - handle of the tree-view control 
 *
 */
static	BOOL DLGInitTreeLists(HWND hwndTV) 
{
	// Create the image list.
	ghAMPrev = (HTREEITEM) TVI_FIRST; 
    return TRUE; 
} 

/*
 * DLGAddListItem - adds items to a tree-view control. 
 * Returns the handle of the newly added item. 
 * hwndTV - handle of the tree-view control 
 * lpszItem - text of the item to add 
 * nLevel - level at which to add the item 
 */
static	HTREEITEM DLGAddListItem(HWND hwndTV, LPTSTR lptszItem, DWORD dwData, int nLevel) 
{ 
    TV_ITEM tvi; 
    TV_INSERTSTRUCT tvins; 

	    tvi.mask = TVIF_TEXT | TVIF_PARAM;
    
    // Set the state
    if (nLevel == 1) 
    {
        tvi.mask |= TVIF_STATE; 
        tvi.state = TVIS_SELECTED;
    }

    // Set the text of the item. 
    tvi.pszText = lptszItem; 
 
    // Save the ID in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM) dwData; 
 
    tvins.item = tvi; 
    tvins.hInsertAfter = ghAMPrev; 
 
    // Set the parent item based on the specified level. 
    if (nLevel == -1)
        tvins.hParent = gAMhtiVisible;
    else if (nLevel == 1) 
        tvins.hParent = TVI_ROOT; 
    else if (nLevel == 2) 
        tvins.hParent = ghAMPrevRootItem; 
    else
        tvins.hParent = ghAMPrevLev2Item; 
 
    // Add the item to the tree-view control. 
    ghAMPrev = (HTREEITEM)SendMessage( hwndTV, TVM_INSERTITEM, 0, (LPARAM)(LPTV_INSERTSTRUCT)&tvins ); 
 
    // Save the handle of the item. 
    if (nLevel == 1) 
        ghAMPrevRootItem = ghAMPrev; 
    else if (nLevel == 2) 
        ghAMPrevLev2Item = ghAMPrev; 
 
    return ghAMPrev; 
} 
 
static void ResetTreeRefresh(void)
{
	TV_ITEM item;
    HTREEITEM hItem;
    LPTREEDATA psearchdata;
	if (!gCWndCtlMaps ) return;
	memset(&item,0,sizeof(item));
	hItem = TreeView_GetRoot(gCWndCtlMaps->m_hWnd);
    while (hItem)
    {
		// gets its data
    	item.mask =  TVIF_PARAM ;
    	item.hItem = hItem;
		TreeView_GetItem(gCWndCtlMaps->m_hWnd, &item);
		psearchdata = (LPTREEDATA)item.lParam;
		if (psearchdata) psearchdata->dwRefresh = 0;
		TreeView_SetItem(gCWndCtlMaps->m_hWnd, &item);
		hItem = TreeView_GetNextSibling( gCWndCtlMaps->m_hWnd, hItem );
	}
}

static void RemoveStaleSessions(void)
{
	TV_ITEM item;
    HTREEITEM hItem,hItemNext;
    LPTREEDATA psearchdata;
	if (!gCWndCtlMaps ) return;
	memset(&item,0,sizeof(item));
	hItem = TreeView_GetRoot(gCWndCtlMaps->m_hWnd);
	while (hItem)
	{
		// get the next one
    	hItemNext = TreeView_GetNextSibling( gCWndCtlMaps->m_hWnd, hItem );    
		// gets its data
    	item.mask = TVIF_PARAM;
    	item.hItem = hItem;
		TreeView_GetItem( gCWndCtlMaps->m_hWnd, &item );
		psearchdata = (LPTREEDATA)item.lParam;
		if (psearchdata && (0 == psearchdata->dwRefresh))
		{
			free(psearchdata);
            TreeView_DeleteItem( gCWndCtlMaps->m_hWnd, hItem );
		}

		hItem = hItemNext;
	}
}
/*
 * DLGReleaseSessionData
 *
 * Releases the memory allocated for session guids
 */
static	void DLGReleaseSessionData( void )
{
    HTREEITEM htiSession;

	if ( gCWndCtlMaps )
	{
		htiSession = TreeView_GetRoot(gCWndCtlMaps->m_hWnd);
		while (htiSession)
		{
			gAMtvItem.hItem      = htiSession;
			gAMtvItem.pszText    = gAMtszSessionName;
			gAMtvItem.cchTextMax = MAX_SESSIONNAME;
			TreeView_GetItem( gCWndCtlMaps->m_hWnd, &gAMtvItem );
			if ( gAMtvItem.lParam ) free( (LPVOID)gAMtvItem.lParam );
			htiSession         = TreeView_GetNextSibling( gCWndCtlMaps->m_hWnd, htiSession );
		}
	}
}

/*
 * DLGReleaseSPData
 *
 * Releases the memory allocated for service provider guids
 * depends on global variable ghWndSPControl
 */
static	void DLGReleaseSPData( void )
{
	LPSPCONTEXT lpSPContext;
    int count,index;

	if ( gCWndCtlSP )
	{
		count = gCWndCtlSP->SendMessage( LB_GETCOUNT, 0, 0 );
		for (index = 0; index < count; index++)
		{
			lpSPContext = (LPSPCONTEXT) gCWndCtlSP->SendMessage( LB_GETITEMDATA, index, 0 );
			if(lpSPContext) 
				if (lpSPContext->lpConnection) free(lpSPContext->lpConnection);
			free(lpSPContext);
		}

//		gCWndCtlSP = NULL;
	}
//	if( gAMSPContext.lpConnection) free(gAMSPContext.lpConnection);
//	gAMSPContext.lpConnection = NULL;
}

/*
 * DLGReleaseAudioData
 *
 * Releases the memory allocated for audio guids
 */
static	void DLGReleaseAudioData( void )
{
	ULONG	nSndID;
	int		count;
	int		index;

	if ( (gCWndCtlAudio == NULL) || !DLGaudioLoaded )
		return;

	count = gCWndCtlAudio->SendMessage( LB_GETCOUNT, 0, 0 );

	for ( index=0;index<count; ++index )
	{
		nSndID = (ULONG)gCWndCtlAudio->SendMessage( LB_GETITEMDATA, index, 0 );

		if ( nSndID != SND_NULL_SND_ID )
			audioDeleteSnd( nSndID );
	}
	count = gCWndCtlAudio->SendMessage( LB_RESETCONTENT, 0, 0 );
	audioSetTableIndex( 0 );
	DLGaudioLoaded  = FALSE;
}

/*
 * SetupFonts
 *
 * Initializes font structures (used for wizard controls)
 */

static	void SetupFonts(HDC hDC)
{
    LOGFONT lf;
    TCHAR tszFontName[MAX_FONTNAME];
	
    LoadString(ghinst, IDS_WIZARD_FONTNAME, tszFontName, MAX_FONTNAME);

	if ( ghTitleFont == NULL )
	{
		ZeroMemory(&lf,sizeof(lf));
		lf.lfHeight = -MulDiv(11,GetDeviceCaps(hDC, LOGPIXELSY),72);
		lf.lfWeight = 500;
		lf.lfItalic = TRUE;
		_tcscpy(lf.lfFaceName,tszFontName);
		ghTitleFont = CreateFontIndirect(&lf);
	}

	if ( ghHeadingFont == NULL )
	{
		ZeroMemory(&lf,sizeof(lf));
		lf.lfHeight = -MulDiv(11,GetDeviceCaps(hDC, LOGPIXELSY),72);
		lf.lfWeight = 500;
		_tcscpy(lf.lfFaceName,tszFontName);
		ghHeadingFont = CreateFontIndirect(&lf);
	}

    ZeroMemory(&lf,sizeof(lf));
    lf.lfHeight = -MulDiv(8,GetDeviceCaps(hDC, LOGPIXELSY),72);
    lf.lfWeight = 500;
    _tcscpy(lf.lfFaceName,tszFontName);
    ghScaleFont = CreateFontIndirect(&lf);
}


/*
 * CleanupFonts
 *
 * Cleans up font structures
 */

static	void CleanupFonts(void)
{
    if (ghTitleFont) DeleteObject(ghTitleFont);
    if (ghHeadingFont) DeleteObject(ghHeadingFont);
    if (ghScaleFont) DeleteObject(ghScaleFont);
}


/////////////////////////////////////////////////////////////////////////////
// CHostLobby dialog


CHostLobby::CHostLobby(CWnd* pParent /*=NULL*/)
	: CDialog(CHostLobby::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHostLobby)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHostLobby::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHostLobby)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHostLobby, CDialog)
	//{{AFX_MSG_MAP(CHostLobby)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHostLobby message handlers

/////////////////////////////////////////////////////////////////////////////

void CHostLobby::OnMove(int x, int y) 
{
	pMainFrame->UpdateView();
	CDialog::OnMove(x, y);
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME); 
}



// CJoinLobby dialog

CJoinLobby::CJoinLobby(CWnd* pParent /*=NULL*/)
	: CDialog(CJoinLobby::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJoinLobby)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CJoinLobby::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJoinLobby)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJoinLobby, CDialog)
	//{{AFX_MSG_MAP(CJoinLobby)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJoinLobby message handlers

void CJoinLobby::OnMove(int x, int y) 
{
	pMainFrame->UpdateView();
	CDialog::OnMove(x, y);
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME); 
}


/////////////////////////////////////////////////////////////////////////////
// CErrorDialog dialog


CErrorDialog::CErrorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CErrorDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CErrorDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CErrorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErrorDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CErrorDialog::SetString(const char *string) 
{
	errstr = string;
}

BEGIN_MESSAGE_MAP(CErrorDialog, CDialog)
	//{{AFX_MSG_MAP(CErrorDialog)
	ON_WM_MOVE()
	ON_BN_CLICKED(ID_RETRY, OnRetry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorDialog message handlers

BOOL CErrorDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CWnd *pWnd = GetDlgItem(IDC_ERROR_STRING);
	if (pWnd)
		pWnd->SetWindowText(errstr);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CErrorDialog::OnMove(int x, int y) 
{
	pMainFrame->UpdateView();
	if(bParent)
		GetOwner()->RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME);
	CDialog::OnMove(x, y);
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME); 
}

void CErrorDialog::OnRetry() 
{
	CDialog::EndDialog( 0 );
}


/////////////////////////////////////////////////////////////////////////////
// CErrorDialog2 dialog


CErrorDialog2::CErrorDialog2(CWnd* pParent /*=NULL*/)
	: CDialog(CErrorDialog2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CErrorDialog2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CErrorDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErrorDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CErrorDialog2::SetString(const char *string) 
{
	errstr = string;
}

BEGIN_MESSAGE_MAP(CErrorDialog2, CDialog)
	//{{AFX_MSG_MAP(CErrorDialog2)
	ON_WM_MOVE()
	ON_BN_CLICKED(ID_RETRY, OnRetry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorDialog2 message handlers

BOOL CErrorDialog2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CWnd *pWnd = GetDlgItem(IDC_ERROR_STRING);
	if (pWnd)
		pWnd->SetWindowText(errstr);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CErrorDialog2::OnMove(int x, int y) 
{
	pMainFrame->UpdateView();
	if(bParent)
		GetOwner()->RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME);
	CDialog::OnMove(x, y);
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME); 
}

void CErrorDialog2::OnRetry() 
{
	CDialog::EndDialog( 0 );
}


//========================================================================
//						EOF
//========================================================================
