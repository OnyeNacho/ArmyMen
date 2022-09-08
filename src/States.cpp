//========================================================================
//	FILE:			$Workfile: States.cpp $
//
//	DESCRIPTION:	Game State Routines and processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, September 30, 1997
//
//	REVISION:		$Header: /ArmyMen/src/States.cpp 100   4/17/98 11:19a Bwilcox $
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
//  $Log: /ArmyMen/src/States.cpp $
//  
//  100   4/17/98 11:19a Bwilcox
//  scrolling click on paper map takes you there
//  
//  99    4/17/98 12:53a Dmaynard
//  Added  turning on gpComm->debugComm with S key in  MainScreen
//  
//  98    4/16/98 9:56p Nrobinso
//  scripts trace on/off with s key
//  
//  97    4/08/98 11:25p Nrobinso
//  fix keyboard save
//  
//  96    4/08/98 12:17p Nrobinso
//  add a keyboard 'g' in map that turns units on & off
//  
//  95    4/08/98 10:45a Bwilcox
//  flip allah limited to on/off
//  
//  94    4/07/98 12:51p Nrobinso
//  remove no_cheats
//  
//  93    4/06/98 3:20p Nrobinso
//  encode cheats
//  
//  92    4/06/98 2:59p Nrobinso
//  move cheats text into usa.h
//  
//  91    4/05/98 1:59p Bwilcox
//  new cheat added
//  
//  90    4/04/98 9:13a Bwilcox
//  cheat fixes
//  
//  89    4/03/98 9:40p Bwilcox
//  cheat fixes
//  
//  87    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  86    3/31/98 5:55p Aburgess
//  copy sarge directional keys to setup keys for mp
//  
//  85    3/31/98 4:53p Aburgess
//  don't read jpystick during screen states, read captured joystick.
//  
//  84    3/30/98 10:10p Nrobinso
//  Enter deosn't enter chat mode
//  
//  83    3/29/98 5:34p Nrobinso
//  setup cheats
//  
//  82    3/27/98 5:20p Nrobinso
//  add cheats
//  
//  81    3/23/98 6:42p Nrobinso
//  remove about box
//  
//  80    3/20/98 6:07p Nrobinso
//  save right button and cursor color state to registry
//  
//  79    3/20/98 3:37p Dmaynard
//  Better State Changes for Lobby Start-up
//  
//  78    3/18/98 12:51a Nrobinso
//  cleanup registry access
//  
//  77    3/17/98 4:42p Dmaynard
//  Added PAUSE_MAPLOAD instead of piggy-backing on the normal PAUSE_LOCAL
//  flags.
//  
//  76    3/17/98 3:09p Aburgess
//  registry storage of Audio parameters and Config parameter
//  
//  75    3/17/98 11:26a Aburgess
//  modified parameter list for ScrnTerminateEditMode()
//  
//  74    3/14/98 4:44p Nrobinso
//  fix double click, back while editing and nameless palyers
//  
//  73    3/13/98 11:39a Nrobinso
//  simplify stats state processing
//  
//  72    3/11/98 3:14p Dmaynard
//  Removed Unneeded map name initialization iin Lobby Startup case.
//  
//  71    3/11/98 1:49p Phu
//  cursor stuff
//  
//  70    3/11/98 11:27a Aburgess
//  modifications made to support new colorization of menus based on player
//  army color
//  
//  69    3/10/98 11:23p Nrobinso
//  read mouse in title state
//  
//  67    3/09/98 9:41a Aburgess
//  added ESC key recognition
//  
//  66    3/06/98 5:18p Aburgess
//  turn audio on and off in ABOUT dialog
//  
//  65    3/06/98 2:40p Nrobinso
//  jave mission statment override not do anything
//  
//  64    3/05/98 4:57p Aburgess
//  correction of Arrow key disabling in chat mode
//  
//  63    3/05/98 3:05p Aburgess
//  removed anykey access for options screen in title screen mode
//  
//  62    3/03/98 5:46p Dmaynard
//  Bug Fix on Lobby Startup. 
//  
//  61    3/03/98 5:20p Dmaynard
//  Changes for Lobby Startup,  Setting GameState and UI properly when
//  launched froma lobby.
//  
//  60    3/03/98 9:24a Aburgess
//  disabled arrow keys in chat mode
//  
//  59    3/02/98 12:14p Aburgess
//  modifications made to support the ESC key in both non-gameplay and
//  gameplay modes.
//  
//  58    2/26/98 2:26p Aburgess
//  modifiations made to properly process the ESC key in mission recall and
//  map screens
//  
//  57    2/20/98 4:28p Aburgess
//  removed calls to update routines, now handled from within the init
//  routines
//  
//  56    2/17/98 9:00a Aburgess
//  added joystick normalization
//  
//  55    2/16/98 6:27p Nrobinso
//  joystick configuration support
//  
//  54    2/13/98 3:59p Nrobinso
//  remove avi player
//  
//  53    2/13/98 12:27p Nrobinso
//  change names of input capturing functions
//  
//  52    2/13/98 12:22p Nrobinso
//  add joystick capture
//  
//  51    2/13/98 10:06a Aburgess
//  modifications made to further support keyboard configurations. Support
//  of Audio slider bar. implementation of all known buttons
//  
//  50    2/12/98 4:18p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  49    2/11/98 7:52p Nrobinso
//  go to mutiplayer end scrren intead of yes/no
//  
//  48    2/10/98 1:19p Nrobinso
//  remove old code
//  
//  47    2/03/98 6:08p Aburgess
//  added check for ONEPLAYER vs MULTI???PLAYER for end game screens
//  
//  46    2/02/98 5:05p Aburgess
//  debounced mouse events
//  
//  45    2/02/98 8:43a Nrobinso
//  change default map name
//  
//  44    2/01/98 10:58p Nrobinso
//  removed old dialog code
//  
//  43    1/28/98 12:18p Dmaynard
//  Lobby Support.  Set default map to alpine_multi.amm as a temp hack
//  
//  42    1/28/98 11:46a Dmaynard
//  
//  41    1/28/98 11:31a Dmaynard
//  Lobby Start up stuff
//  
//  40    1/28/98 10:57a Aburgess
//  modifications made to support LOBBY sessions
//  
//  39    1/28/98 10:19a Aburgess
//  modifications made to support game start MISSION recall. Support for
//  successive missions has not been implemented yet and will still display
//  the old MISSION STATEMENT interface. Additionally, access directly to
//  the HOST and REMOTE campaign select screens now occurs if in a lobby
//  session.
//  
//  38    1/24/98 3:34p Aburgess
//  modification for chat receive
//  
//  37    1/23/98 9:38a Aburgess
//  modifications made to support new multiplayer screens
//  
//  36    1/21/98 12:49p Aburgess
//  gameNoisy must be turned on in special circumstances. More to follow
//  
//  35    1/21/98 11:50a Nrobinso
//  keyboard controls for yes\no in lose screen
//  
//  34    1/21/98 11:24a Aburgess
//  modifications made to support <RETURN>, <Y>, and <N> keys in stat
//  screens
//  
//  33    1/21/98 10:26a Nrobinso
//  adding keyboard overrides for stats screen
//  
//  32    1/20/98 8:36a Aburgess
//  Smacker now interruptable. Playback is currently 320 x 200, We are
//  unable to stretch the image.
//  
//  31    1/20/98 12:46a Aburgess
//  lastest working murder
//  
//  30    1/16/98 10:35a Aburgess
//  added check of ScrnInEditMode into keyhandler
//  
//  29    1/14/98 2:16p Aburgess
//  modifications made to support GAME_PLAY Options screens
//  
//  28    1/14/98 11:34a Nrobinso
//  display about box in title screen
//  
//  27    1/09/98 8:48a Aburgess
//  added 'A' recognition during screen states for initiating "All
//  Scenarios Visible"
//  
//  ...
//  
//  1     10/05/97 12:13p Aburgess
//  Game State processing
//  
//  $Nokeywords:$
//========================================================================
// State Routines
//
// New_<game states>:
//	Entry:
//		gameState = the previous game state.
//	Exit:
//		nothing.
//
// Old_<game states>:
//	Entry:
//		gameState = the next game state.
//	Exit:
//		nothing.
//
//	Notes:
//		The Old_<game state> for the previous state is called before the
//		New_<game state> for the new game state.
//
//
// GLd_<game states>:
//	Entry:
//		nothing.
//	Exit:
//		nothing.
//
//	Notes:
//		The appropriate GLd_<game state> is called when GraphicsLoad() is called.
//
//
// Dsp_<game states>:
//	Entry:
//		nothing.
//	Exit:
//		nothing.
//
// Notes:
//		The appropriate Dsp_<game state> is called when GameDisplay() is called.
//
//
// Act_<game states>:
//	Entry:
//		nothing.
//	Exit:
//		nothing.
//
// Notes:
//		The appropriate Act_<game state> is called when GameAction() is called.
//
//
// KeyOverride_<game states>:
//	Entry:
//		Key	- user keypress.
//		down - key down or up event.
//	Exit:
//		nothing.
//
// Notes:
//		The appropriate Act_<game state> is called when GameAction() is called.
//
// SAMPLES
//
//	void New_GAME_NULL_STATE(GAME_STATE gameState) {
//		pMainFrame->SetUI(NULL);					// disable user-interface...
//	}
//	void Old_GAME_NULL_STATE(GAME_STATE gameState) {
//		return;										// provided for debugging purposes
//	}
//	BOOL GLd_GAME_NULL_STATE() {
//		return TRUE;								// provided for debugging purposes
//	}
//	void Dsp_GAME_NULL_STATE() {
//		return;										// provided for debugging purposes
//	}
//	void Act_GAME_NULL_STATE() {
//		return;										// provided for debugging purposes
//	}
//	BOOL KeyOverride_GAME_NULL_STATE(UINT key, BOOL down)	{
//		return( TRUE );
//	}
//
//========================================================================

// Includes
#include "stdafx.h"
#include "Army.h"
#include "map.h"
#include "comm.h"
#include "Armymen.h"
#include "MainFrm.h"
#include "GameFlow.h"
#include "gameproc.h"
#include "Dialog.h"
#include "Audio.h"
#include "Ai.h"
#include "ui.h"
#include "comm.h"
#include "3DONetwork.h"
#include "miscfile.h"
#include "States.h"
#include "Vehicle.h"
#include "Screen.h"
#include "Smacker.h"
#include "input.h"
#include "commands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//================================================================
//			GLOBAL variables
//================================================================
extern char	cheat1[];
extern char	cheat2[];
extern char	cheat3[];
extern char	cheat4[];
extern char	cheat5[];
extern char	cheat6[];
extern char	cheat7[];
extern char	cheat8[];
extern char	cheat9[];
extern char	cheat10[];
extern char	cheat11[];

//================================================================
//			GLOBAL prototypes
//================================================================
extern	void	LoadKeyBindings( int eConfigType );
extern	void	SBtnChatTurnOnKeys( HSCREENBTN hScreenBtn );
extern	void	ScrnReceiveChatMessage(char *message);

extern char sargeInvisible;
void Kbd_Debug_Invisible( BYTE nChar, UINT nFlags )
{
	sargeInvisible = !sargeInvisible;
}

//	Function prototypes used by key tables - Basic Debugging
void Kbd_Debug_LoseGameDirect( BYTE nChar, UINT nFlags );
void Kbd_Debug_WinGameDirect( BYTE nChar, UINT nFlags );
void Kbd_Debug_RunVehicle( BYTE nChar, UINT nFlags );
void Kbd_Debug_FindTrooper( BYTE nChar, UINT nFlags );
void Kbd_Debug_ViewRadius( BYTE nChar, UINT nFlags );
extern char Allah;		// controls visibility

void Kbd_Debug_FlipAllahX( BYTE nChar, UINT nFlags )
{
	Allah = !Allah;
}
void Kbd_Debug_BigCheat( BYTE nChar, UINT nFlags );
void Kbd_Debug_ClearDebug( BYTE nChar, UINT nFlags );
void Kbd_Debug_FireRadius( BYTE nChar, UINT nFlags );
void Kbd_Debug_StartAIControl( BYTE nChar, UINT nFlags );
void Kbd_Debug_MsgTest( BYTE nChar, UINT nFlags );
void Kbd_Debug_Clear( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_ChangeMode( BYTE nChar, UINT nFlags );
void Kbd_ChangeTrafficability( BYTE nChar, UINT nFlags );
void Kbd_Debug_BigCheat( BYTE nChar, UINT nFlags );

void Kbd_Debug_Display( BYTE nChar, UINT nFlags );
void Kbd_Debug_ClearDisplay( BYTE nChar, UINT nFlags );
void Kbd_Debug_FlipHotspots( BYTE nChar, UINT nFlags );
void Kbd_Debug_RouteDraw( BYTE nChar, UINT nFlags );
void Kbd_Debug_LabelDraw( BYTE nChar, UINT nFlags );

void Kbd_Debug_Cheat( BYTE nChar, UINT nFlags );
void Kbd_Debug_VehicleTrace( BYTE nChar, UINT nFlags );
void Kbd_Debug_Travel( BYTE nChar, UINT nFlags );
void Kbd_Debug_SargeInvulnerable( BYTE nChar, UINT nFlags );
void Kbd_Debug_SargeCane( BYTE nChar, UINT nFlags );
void Kbd_Debug_FoeImmobile( BYTE nChar, UINT nFlags );
void Kbd_Debug_AddAirstrikes( BYTE nChar, UINT nFlags );
void Kbd_Debug_Explosions_Cheat( BYTE nChar, UINT nFlags );
void Kbd_Debug_SargeQuestItem( BYTE nChar, UINT nFlags );
void Kbd_Debug_DeployJeep( BYTE nChar, UINT nFlags );
void Kbd_Debug_DeployHalftrack( BYTE nChar, UINT nFlags );
void Kbd_Debug_DeployTank( BYTE nChar, UINT nFlags );
void Kbd_Debug_Teleport( BYTE nChar, UINT nFlags );
void Kbd_Debug_MaxAmmo(  BYTE nChar, UINT nFlags );

void Kbd_Debug_Game( BYTE nChar, UINT nFlags );
void Kbd_Debug_AudioKill( BYTE nChar, UINT nFlags );
void Kbd_Debug_MusicToggle( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_SoundToggle( BYTE nChar, UINT nFlags );
void Kbd_Debug_LoseGame( BYTE nChar, UINT nFlags );
void Kbd_Debug_WinGame( BYTE nChar, UINT nFlags );

extern char blinkpaper;

//================================================================
//			GLOBAL variables
//================================================================

static	SPRITE	BackgroundSprite;
static	BOOL	BackgroundLoaded;

struct Cheat
{
	void	(*function)(BYTE nChar, UINT nFlags);		// cheat function
	char	*string;									// cheat code
};


//================================================================
//			LOCAL prototypes
//================================================================
static	void NoopKey(UINT nChar, UINT nFlags);

//================================================================
//					STATE FUNCTIONS
//================================================================

// key/mouse overrides

SKeyMsg	KDn_TitleScreenState[] = {

	END_KEY_LIST
};

SKeyMsg *KDn_TITLE_SCREEN_STATE[] = {
	KDn_TitleScreenState,

	NULL
};

SKeyMsg	KUp_TitleScreenState[] = {

	END_KEY_LIST
};

SKeyMsg *KUp_TITLE_SCREEN_STATE[] = {
	KUp_TitleScreenState,

	NULL
};

SUserInterface UI_TITLE_SCREEN_STATE = {
	InTitleScreenLButtonDn,	// Mouse left-button down events
	InTitleScreenLButtonUp,	// Mouse left-button up events
	NULL,					// Mouse right-button down events
	NULL,					// Mouse right-button up events
	InTitleScreenMouseMove,	// Mouse movement events

	KDn_TITLE_SCREEN_STATE,	// key down events
	KUp_TITLE_SCREEN_STATE	// key up events
};

//----------------------------------------------------------------
//	Game Title Screen State
//----------------------------------------------------------------
void New_GAME_TITLE_SCREEN_STATE( GAME_STATE gameState )
{
	ULONG	nSndID = SND_NULL_SND_ID;
	char	bData[12];
	DWORD	dwSize = sizeof(bData);
	CONFIG	UIregConfig;

	// right mouse button and cursor color3
	Get_GamePlay_AltGunsight();
	Get_GamePlay_AltMouse();

	// key configuration set
	if (gpComm->RegGet(TEXT("Config"), (LPBYTE)&bData, &dwSize))
	{
		if ( strcmp( bData, "Default1" ) == 0 )
			UIregConfig = CONFIG_DEFAULT1;
		else
		if ( strcmp( bData, "Default2" ) == 0 )
			UIregConfig = CONFIG_DEFAULT2;
		else
		if ( strcmp( bData, "Custom" ) == 0 )
			UIregConfig = CONFIG_CUSTOM;
		else
			UIregConfig = CONFIG_DEFAULT1;
	}
	else
		UIregConfig = CONFIG_DEFAULT1;

	SetNormalizeJoystickInput();
	LoadKeyBindings( CONFIG_JOYSTICK );

	LoadKeyBindings( CONFIG_DEFAULT1 );
	LoadKeyBindings( CONFIG_DEFAULT2 );
	LoadKeyBindings( CONFIG_CUSTOM );

	SelectKeyBindings( UIregConfig );
	CopyKeyBindingsToSetup();

	pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
	pMainFrame->SetUIOverride(KeyOverride_GAME_TITLE_SCREEN_STATE);
	pMainFrame->PausePageFlip();
	EraseVisibleSurface();
	// if (!gpComm->m_bTestedLobby ) gpComm->IsLobbyStart();
	// initialize the comm lobby connection
 	BackgroundLoaded = FALSE;
	ScrnSetState( SCRN_TITLE_STATE );

	FreeCursor();
	LoadCursor();
}

void Old_GAME_TITLE_SCREEN_STATE( GAME_STATE gameState )
{
	ScrnTerminate( SCRN_TITLE_STATE );

	pMainFrame->SetUI(NULL);									// disable user-interface...
	pMainFrame->SetUIOverride(NULL);

	if ( BackgroundLoaded )
		FreeSprite(&BackgroundSprite);

	if ( SCRNfullScreen )
	{
		ScrnDelete( SCRNfullScreen );
		SCRNfullScreen = NULL;
	}
	ScrnSetState( SCRN_NULL_STATE );

	pMainFrame->UnPausePageFlip();
}

BOOL GLd_GAME_TITLE_SCREEN_STATE( void )
{
	return (TRUE);
}


void Dsp_GAME_TITLE_SCREEN_STATE( void )
{
	ScrnDoDisplay();
	return;
}

void Act_GAME_TITLE_SCREEN_STATE( void )
{
	ReadMouse(TRUE);
	UseSargeKeyTable();
	ReadCapturedKeyboard();
	ReadCapturedJoystick();
	ScrnDoActions();
	return;
}

BOOL KeyOverride_GAME_TITLE_SCREEN_STATE(UINT key, BOOL down)
{
	SCRN_STATE	eState;
	GAME_STATE	eGameState;
	BOOL		bKeyUsed = FALSE;		// key ignored

	eState = ScrnGetState();
	if (down && !ScrnInEditMode())
	{
		if ( (eState == SCRN_ABOUT_STATE) || (eState == SCRN_PLAY_ABOUT_STATE) )
		{
			// Eject the credits movie
			SmackerEject();
			bKeyUsed = TRUE;
		}
		else
		{
			switch (key)
			{
				case 'A':		// All scenarios visible
					pMainFrame->OnAllScenariosVisible();	// toggle all 1st missions visible
					break;
				case 'S':		// All scenarios visible
					pMainFrame->OnScriptdebug();	// toggle all 1st missions visible
#ifdef _DEBUG
					gpComm->debugComm = TRUE;
#endif
					break;
				default:
					eGameState = gpGame->GetState();
					if ( eGameState == GAME_MOVIE_STATE )
						SmackerEject();
					else
					if ( eState == SCRN_TITLE_STATE )
					{
						bKeyUsed = TRUE;			// key used
					    if (gpComm->m_bStartedByLobby)
						{
							// host or join a battle
							gpGame->SetSubState(NULL_SUB_STATE);
							if ( gpComm->m_bHost )
							{
								// host a battle
								gpGame->GameType = GAMETYPE_HOST_MULTIPLAYER;
								ScrnSetState( SCRN_MULTI_HOST_STATE );
							}
							else
							{
								// join a battle
								gpGame->GameType = GAMETYPE_REMOTE_MULTIPLAYER;
								ScrnSetState( SCRN_MULTI_REMOTE_STATE );
							}
						}  else	 ScrnSetState( SCRN_GAME_START_STATE );

					}
					else
					if ( (key == VK_ESCAPE) && !ScrnOptionsVisible() && (gpGame->GetState() != GAME_PLAY_STATE) )
					{
						ScrnSetState( SCRN_OPTIONS_STATE );

						pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
						pMainFrame->SetUIOverride(KeyOverride_GAME_TITLE_SCREEN_STATE);
						pMainFrame->PausePageFlip();

						// set the local and remote pause
						gpGame->PauseGame( PAUSE_LOCAL );
						if ( gpGame->GameType != GAMETYPE_ONEPLAYER )
							SendGamePause(TRUE, PAUSE_LOCAL);

						ShowTheCursor( TRUE );
					}
					break;
			}
		}
	}

	return( bKeyUsed );
}


#define MAX_CHEAT	15
#define CHEATS		11

BOOL no_mp_cheats = TRUE;
char cheat = 0;
char cheat_str[MAX_CHEAT+1];

void ClearCheat()
{
	ZeroMemory(cheat_str, MAX_CHEAT);
	cheat = 0;
}

BOOL KeyOverride_CHEATS(UINT key, BOOL down)
{
	BOOL		bKeyUsed = FALSE;		// key ignored
	static mp = FALSE;
	int	i;
	char buf[200];
	static Cheat cheats[CHEATS] = {
		{Kbd_Debug_LoseGameDirect,		cheat1 },
		{Kbd_Debug_WinGameDirect,		cheat2 },
		{Kbd_Debug_FlipAllahX,			cheat3 },
		{Kbd_Debug_Explosions_Cheat,	cheat4 },
		{Kbd_Debug_AddAirstrikes,		cheat5 },
		{Kbd_Debug_SargeInvulnerable,	cheat6 },
		{Kbd_Debug_FoeImmobile,			cheat7 },
		{Kbd_Debug_Teleport,			cheat8 },
		{Kbd_Debug_MaxAmmo,				cheat9 },
		{Kbd_Debug_Invisible,			cheat10 },
		{Kbd_Debug_BigCheat,			cheat11 }
	};

	if (down)
	{
		if (!isalnum(key))
			return bKeyUsed;

		if (no_mp_cheats && gpGame->GameType != GAMETYPE_ONEPLAYER && !gpGame->oneplayerMode)
			return bKeyUsed;

		cheat_str[cheat] = key;
		if (++cheat >= MAX_CHEAT)
			ClearCheat();

		if (cheat == 10)
			TRACE("");

		strcpy(buf, cheat_str);
		for (i=0; i<MAX_CHEAT; i++)
		{
			if (buf[i])
				buf[i]++;
		}

		for (i=0; i<CHEATS; i++)
		{
			if (stricmp(cheats[i].string, buf) == 0)
			{
				sprintf(buf,"%s cheat enabled", cheat_str);
				TRACE("Cheating: %s\n", cheat_str);
				ReceiveDashMessage(buf, NULL);
				cheats[i].function(0,0);
				ClearCheat();
			}
		}
	}

	return( bKeyUsed );
}


//----------------------------------------------------------------
//	Game Recall, Mission Statement, and Mission Map UI
//----------------------------------------------------------------

SKeyMsg	KDn_RecallState[] = {

	END_KEY_LIST
};

SKeyMsg *KDn_Recall_State[] = {
	KDn_RecallState,

	NULL
};

SKeyMsg	KUp_RecallState[] = {

	END_KEY_LIST
};

SKeyMsg *KUp_Recall_State[] = {
	KUp_RecallState,

	NULL
};

void InRecallLButtonDn(UINT nFlags, CPoint point)
{
	releaserecalllfunc(point.x,point.y);
}

void InRecallLButtonUp(UINT nFlags, CPoint point)
{
}

SUserInterface UI_RECALL = {
	InRecallLButtonDn,		// Mouse left-button down events
	InRecallLButtonUp,		// Mouse left-button up events
	NULL,					// Mouse right-button down events
	NULL,					// Mouse right-button up events
	NULL,					// Mouse movement events

	KDn_Recall_State,		// key down events
	KUp_Recall_State		// key up events
};

BOOL KeyOverride_RECALL(UINT key, BOOL down)
{
	BOOL		bKeyUsed = FALSE;		// key ignored

	if (down)
	{
		releaserecalllfunc(0,0);
		bKeyUsed = TRUE;
	}

	return( bKeyUsed );
}

BOOL KeyOverride_RECALL_MAP(UINT key, BOOL down)
{
	BOOL		bKeyUsed = FALSE;		// key ignored

	if (down)
	{
		if (key == 'G')
			blinkpaper = !blinkpaper;
		else
			releaserecalllfunc(0,0);

		bKeyUsed = TRUE;
	}

	return( bKeyUsed );
}

//----------------------------------------------------------------
//	Game Start State
//----------------------------------------------------------------
void New_GAME_START_STATE( GAME_STATE gameState )
{
	pMainFrame->SetUI(NULL);						// disable user-interface...
}

void Old_GAME_START_STATE( GAME_STATE gameState )
{
	return;											// provided for debugging purposes
}

BOOL GLd_GAME_START_STATE( void )
{
	return TRUE;									// provided for debugging purposes
}

void Dsp_GAME_START_STATE( void )
{
	return;											// provided for debugging purposes
}
void Act_GAME_START_STATE( void )
{
	return;											// provided for debugging purposes
}


//----------------------------------------------------------------
//	Game Connect State
//----------------------------------------------------------------

SKeyMsg	KDn_MPUIScreenState[] = {

	END_KEY_LIST
};

SKeyMsg *KDn_MPUI_SCREEN_STATE[] = {
	KDn_MPUIScreenState,

	NULL
};

SKeyMsg	KUp_MPUIScreenState[] = {

	END_KEY_LIST
};

SKeyMsg *KUp_MPUI_SCREEN_STATE[] = {
	KUp_MPUIScreenState,

	NULL
};

SUserInterface UI_MPUI_SCREEN_STATE = {
	InTitleScreenLButtonDn,	// Mouse left-button down events
	InTitleScreenLButtonUp,	// Mouse left-button up events
	NULL,					// Mouse right-button down events
	NULL,					// Mouse right-button up events
	InTitleScreenMouseMove,	// Mouse movement events

	KDn_MPUI_SCREEN_STATE,	// key down events
	KUp_MPUI_SCREEN_STATE	// key up events
};

BOOL KeyOverride_MPUI_SCREEN_STATE(UINT key, BOOL down)
{
	BOOL		bKeyUsed = FALSE;		// key ignored

	if (down && !ScrnInEditMode())
	{
		switch( key )
		{
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_DOWN:
		case VK_NUMPAD2:
		case VK_NUMPAD4:
		case VK_NUMPAD6:
		case VK_NUMPAD8:
		case VK_RETURN:
			break;
		default:
			ScrnInitChat( key );
			bKeyUsed = TRUE;
			break;
		}
	}

	return( bKeyUsed );
}

//----------------------------------------------------------------
//	Game TEST State
//----------------------------------------------------------------
void New_GAME_TEST_STATE( GAME_STATE gameState )
{
	pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
	pMainFrame->SetUIOverride(NULL);
	pDirectDraw->FlipToGDISurface();
	EraseVisibleSurface();
	pMainFrame->PausePageFlip();

	// initialize the Screen test
	ScrnSetState( SCRN_TITLE_STATE );
}

void Old_GAME_TEST_STATE( GAME_STATE gameState )
{
	// terminate the ScreenObj test
	ScrnTerminate( SCRN_GAME_START_STATE );

	pMainFrame->UnPausePageFlip();

	return;											// provided for debugging purposes
}

BOOL GLd_GAME_TEST_STATE()
{
	return TRUE;									// provided for debugging purposes
}

void Dsp_GAME_TEST_STATE()
{
	// display any updated buttons
	ScrnDoDisplay();
	return;											// provided for debugging purposes
}

void Act_GAME_TEST_STATE()
{
	// update any buttons
	ScrnDoActions();
	return;											// provided for debugging purposes
}

//----------------------------------------------------------------
//	STATEMENT SubState UI definitions
//----------------------------------------------------------------
void InStatementScreenButtonDn(UINT nFlags, CPoint point)
{
	ScrnSetState( SCRN_NULL_STATE );

	if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
		gpGame->SetSubState( PLAY_SUB_STATE );
	else
		gpGame->SetSubState( PLAY_SETUP_SUB_STATE );

	if ( gpGame->GetState() != GAME_PLAY_STATE )
		gpGame->SetState( GAME_PLAY_STATE );

	ForceLoadIdentityPalette(the_map.terrain_name);

	gameNoisy();
}


SKeyMsg	KDn_StatmentScreenState[] = {

	END_KEY_LIST
};

SKeyMsg *KDn_STATMENT_SCREEN_STATE[] = {
	KDn_StatmentScreenState,

	NULL
};

SKeyMsg	KUp_StatmentScreenState[] = {

	END_KEY_LIST
};

SKeyMsg *KUp_STATMENT_SCREEN_STATE[] = {
	KUp_StatmentScreenState,

	NULL
};

SUserInterface UI_STATEMENT_SCREEN_STATE = {
	InStatementScreenButtonDn,	// Mouse left-button down events
	NULL,					// Mouse left-button up events
	InStatementScreenButtonDn,	// Mouse right-button down events
	NULL,					// Mouse right-button up events
	NULL,					// Mouse movement events

	KDn_STATMENT_SCREEN_STATE,	// key down events
	KUp_STATMENT_SCREEN_STATE	// key up events
};

BOOL KeyOverride_GAME_STATEMENT_SCREEN_STATE(UINT key, BOOL down)
{
	BOOL	bKeyUsed      = FALSE;		// key ignored

/*
	if (down && key == VK_RETURN)
	{
		ScrnSetState( SCRN_NULL_STATE );

		if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
			gpGame->SetSubState( PLAY_SUB_STATE );
		else
			gpGame->SetSubState( PLAY_SETUP_SUB_STATE );

		if ( gpGame->GetState() != GAME_PLAY_STATE )
			gpGame->SetState( GAME_PLAY_STATE );

		ForceLoadIdentityPalette(the_map.terrain_name);

		bKeyUsed = TRUE;			// key used
	}
*/

	return( bKeyUsed );
}

//----------------------------------------------------------------
//	STAT UI definitions
//----------------------------------------------------------------

SKeyMsg	KDn_StatScreenState[] = {

	END_KEY_LIST
};

SKeyMsg *KDn_STAT_SCREEN_STATE[] = {
	KDn_StatScreenState,

	NULL
};

SKeyMsg	KUp_StatScreenState[] = {

	END_KEY_LIST
};

SKeyMsg *KUp_STAT_SCREEN_STATE[] = {
	KUp_StatScreenState,

	NULL
};

SUserInterface UI_STAT_SCREEN_STATE = {
	InTitleScreenLButtonDn,	// Mouse left-button down events
	InTitleScreenLButtonUp,	// Mouse left-button up events
	NULL,					// Mouse right-button down events
	NULL,					// Mouse right-button up events
	InTitleScreenMouseMove,	// Mouse movement events

	KDn_STAT_SCREEN_STATE,	// key down events
	KUp_STAT_SCREEN_STATE	// key up events
};

BOOL KeyOverride_GAME_STAT_SCREEN_STATE(UINT key, BOOL down)
{
	BOOL		bKeyUsed  = FALSE;		// key ignored
	BOOL		bYesNo    = TRUE;
	HSCREEN		hScreen   = SCRNfullScreen;

	if (down && hScreen)
	{
		if ( ScrnGetState() == SCRN_STATS_STATE )
		{
			switch(key)
			{
			case VK_RETURN:
				if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
				{
					if (gpGame->winner)
						ScrnOnContinueStats();
					else
						ScrnOnYesPlayAgain((HSCREENBTN)NULL);
				}
				else
					ScrnOnContinueStats();

				bKeyUsed = TRUE;			// key used
				break;
			}
		}
	}

	return( bKeyUsed );
}

//----------------------------------------------------------------
//	Support Routines
//----------------------------------------------------------------

SPRITE*	LoadBackground( char* sBmp, BOOL bNewPalette )
{
	// load the Team image
	if ( *sBmp )
	{
		if ( BackgroundLoaded )
			FreeBackground();

		if( bNewPalette )
			MakeIdentityPalette( sBmp, &pMainFrame->GamePalette );
		LoadSprite( &BackgroundSprite, sBmp, BM_OPAQUE|BM_SYSTEMMEMORY );
		DisplaySpriteFront( &BackgroundSprite, 0 , 0 );
		BackgroundLoaded = TRUE;
	}

	return( &BackgroundSprite );
}

SPRITE*	BackgroundSize( SBOX* pBox )
{
	// acquire the area for this bkg
	if ( SpriteBox( &BackgroundSprite, pBox ) )
	{
		// error: failed to acquire bkg size
		TRACE( "ERROR: failed to acquire Bkg size [%s : %d]\n",
				__FILE__, __LINE__ );
		return( (SPRITE*)NULL );
	}

	return( &BackgroundSprite );
}

void	FreeBackground( void )
{
	FreeSprite(&BackgroundSprite);
	BackgroundLoaded = FALSE;
}

void InTitleScreenLButtonDn(UINT nFlags, CPoint point)
{
	SPOINT		sPoint;
	HSCREENBTN	hScreenBtn;

#if 0
	// check to see if this point is within a button
	if ( ScrnInEditMode() == FALSE )
	{
		sPoint.x = point.x;
		sPoint.y = point.y;

		hScreenBtn = SBtnIsInButton( &sPoint );
		if ( hScreenBtn )
			SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	else
	{
		// need to exit edit mode
		ScrnTerminateEditMode( (HSCREENBTN)NULL );
	}
#else
	sPoint.x = point.x;
	sPoint.y = point.y;

	hScreenBtn = SBtnIsInButton( &sPoint );
	if ( hScreenBtn )
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	else
	if ( ScrnInEditMode() )
		ScrnTerminateEditMode( (HSCREENBTN)NULL );	// need to exit edit mode
#endif
}

void InTitleScreenLButtonUp(UINT nFlags, CPoint point)
{
}

void InTitleScreenMouseMove(UINT nFlags, CPoint point)
{
	SPOINT		sPoint;
	HSCREENBTN	hScreenBtn;
	SBTN_STATE	eSBtnState;

	// only process if we're not in an active edit button
	if ( ScrnInEditMode() == FALSE )
	{
		// check to see if this point is within a button
		sPoint.x = point.x;
		sPoint.y = point.y;

		hScreenBtn = SBtnIsInButton( &sPoint );
		if ( hScreenBtn )
		{
			eSBtnState = SBtnGetState( hScreenBtn );
			if ( eSBtnState == BUTTON_NULL )
				SBtnSetState( hScreenBtn, BUTTON_FOCUSED );
		}
		else
			SBtnClearFocus(&sPoint);
	}
}

BOOL IsResource( LPTSTR id )
{
	DWORD	nResource;
	WORD	nUpperWord;
	WORD	nLowerWord;
	BOOL	bAnswer = FALSE;	// assume not a resource

	nResource  = (DWORD)id;
	nLowerWord = nResource;
	nUpperWord = nResource >> ((sizeof (WORD))<<3);

	if ( !nUpperWord && nLowerWord )
		bAnswer = TRUE;

	return( bAnswer );
}

static	void NoopKey(UINT nChar, UINT nFlags)
{
	// does nothing
}


//========================================================================
//							EOF
//========================================================================

