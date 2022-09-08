/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: GameFlow.cpp $
//
//	DESCRIPTION:	Game flow control functions.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		Wednesday, December 4th, 1996
//
//	REVISION:		$Header: /ArmyMen/src/GameFlow.cpp 315   4/16/98 11:58p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//=========================================================================
//  HISTORY
//
//  $Log: /ArmyMen/src/GameFlow.cpp $
//  
//  315   4/16/98 11:58p Nrobinso
//  release script names at the same time as the map
//  
//  314   4/14/98 5:28a Aburgess
//  modifications to re-introduce the initial mission music
//  
//  313   4/14/98 12:59p Nrobinso
//  add MissionTime to game struct
//  
//  312   4/13/98 1:38p Nrobinso
//  start audio once briefing is drawn
//  
//  311   4/09/98 4:26p Nrobinso
//  turn off map at end of mission
//  
//  310   4/07/98 12:53p Nrobinso
//  simplify audio intensity
//  
//  309   4/06/98 12:40p Nrobinso
//  fix debug keys in setup
//  
//  308   4/05/98 5:56p Bwilcox
//  
//  306   4/03/98 4:18p Aburgess
//  modifications to fix next mission bug
//  
//  305   4/02/98 7:33p Nrobinso
//  fix win/lose cheat for mp
//  
//  304   4/02/98 3:06p Phu
//  
//  303   4/02/98 12:59p Nrobinso
//  commented out traces
//  
//  302   4/01/98 1:17p Aburgess
//  yet another fix to the New Player double-click bug
//  
//  301   4/01/98 10:27a Aburgess
//  check for our Window having focus before doing any display updates
//  
//  300   3/31/98 12:53p Bwilcox
//  dispell fog
//  
//  299   3/31/98 11:53a Bwilcox
//  stratmap overlay removal
//  
//  298   3/29/98 7:06p Dmaynard
//  Better reporting of Bandwidth Measurements.  Highwater mark for send
//  and receive bandwidth, and reporting Bandwidth at the end of each game.
//  
//  297   3/29/98 1:57p Nrobinso
//  if sarge dies, don't show lose video
//  
//  296   3/29/98 12:32p Nrobinso
//  remove unsued
//  
//  295   3/27/98 5:21p Dmaynard
//  Removing knowledge of who is the host
//  
//  294   3/27/98 2:18p Phu
//  quest item load from campaign file
//  
//  293   3/26/98 8:24p Nrobinso
//  fix firing when clicking thru in game screens; add MP music
//  
//  292   3/26/98 2:39p Bwilcox
//  vehicle in movement layer split into new layer
//  
//  291   3/26/98 11:56a Bwilcox
//  storing if it is a capture-the-flag type game
//  
//  290   3/25/98 8:11p Nrobinso
//  if no movie, do the final bitmap for a mission
//  
//  289   3/25/98 4:30p Nrobinso
//  put version on screen
//  
//  288   3/25/98 3:44p Nrobinso
//  don't load the mission brieinf now; don't start music
//  
//  287   3/25/98 3:26p Phu
//  allow esc from setup when paused
//  
//  286   3/24/98 7:23p Phu
//  set prepausekeytable for scrn options
//  
//  285   3/24/98 2:48p Phu
//  fix to pause stuff to remember previous key table
//  
//  284   3/24/98 2:28p Phu
//  change key table for pause state
//  
//  283   3/24/98 12:08p Nrobinso
//  remove unused
//  
//  282   3/23/98 6:41p Nrobinso
//  end mission right into movie if there is one
//  
//  281   3/23/98 12:15p Aburgess
//  new music setup routines
//  
//  280   3/23/98 12:27p Nrobinso
//  switch to loading the aai data every map load
//  
//  279   3/22/98 3:16p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  278   3/20/98 11:53a Aburgess
//  modifications made to correct VOICE and MUSIC cut offs. It apprears
//  that ALL Music and Voice streams need to be run with LOOP on.
//  
//  277   3/19/98 11:20p Nrobinso
//  disabel setup action until everybody is there
//  
//  276   3/19/98 8:47p Dmaynard
//  Put back call to BeginMission
//  
//  275   3/19/98 7:46p Nrobinso
//  return map pause if waiting for maps
//  
//  274   3/19/98 2:40p Nrobinso
//  make options work in mp setup
//  
//  273   3/19/98 1:27p Aburgess
//  removed commented out code
//  
//  272   3/19/98 1:46p Nrobinso
//  turn off vehicle sound at win/lose
//  
//  271   98/03/18 19:09 Dmaynard
//  Sending Unpause twice after map load.  I have seen this message get
//  dropped in IPX.  If this message is dropped game can't start. 
//  
//  270   3/17/98 10:45p Bwilcox
//  fix order carryover problem between units
//  
//  269   3/17/98 4:42p Dmaynard
//  Added PAUSE_MAPLOAD instead of piggy-backing on the normal PAUSE_LOCAL
//  flags.
//  
//  268   3/16/98 1:01p Nrobinso
//  put TraceTime under compiler flag
//  
//  267   3/12/98 6:30p Bwilcox
//  if !campaign data, don't look for music patch
//  
//  266   3/12/98 2:10p Aburgess
//  modifications made to support multiplayer campaign music
//  
//  265   3/11/98 1:49p Phu
//  cursor stuff
//  
//  264   3/10/98 11:20p Nrobinso
//  Read the mouse all the time for cursor movement
//  
//  263   3/09/98 1:46p Bwilcox
//  FIXING AIR DISPLAY MULTIPLAYER
//  
//  262   3/09/98 11:26a Nrobinso
//  remove mission statement screen state
//  
//  261   3/08/98 9:46p Nrobinso
//  getting cursor to always show where it needs to
//  
//  260   3/08/98 1:51a Nrobinso
//  remove old TADcrosshiar cursor
//  
//  259   3/06/98 4:14p Phu
//  loading bar
//  
//  258   3/06/98 2:38p Nrobinso
//  nPauseDelay varinat to lock out direct keyboard read
//  
//  257   3/02/98 5:50p Dmaynard
//  Moved Latency Display to GameFlow so it is no longer just in Debug
//  Builds. 
//  
//  256   3/02/98 10:31a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  255   3/01/98 11:03p Nrobinso
//  
//  254   2/27/98 7:06p Nrobinso
//  remove auido load
//  
//  253   2/27/98 12:53p Nrobinso
//  enable win/lose stream play
//  
//  252   2/26/98 6:26p Dmaynard
//  Fixing clearing of dbgDisplay surface and updating of allah mode debug
//  display.
//  
//  251   2/26/98 5:54p Nrobinso
//  add debug layer clear
//  
//  250   2/26/98 4:06p Phu
//  removed profiling/ old draw map into deadcode
//  
//  249   2/26/98 10:55a Aburgess
//  modifications made to support delayed User Input on info type screens
//  
//  248   2/25/98 10:14p Phu
//  ODF load flash, bodyparts, misc
//  
//  247   2/24/98 7:30p Phu
//  cursor load from data file, moved closedatafile
//  
//  246   2/24/98 2:08p Phu
//  timing loads
//  
//  245   2/24/98 1:41p Aburgess
//  corrected incorrect index error, use mission index rather than scenario
//  index in access of mission specific data
//  
//  244   2/24/98 11:46a Bwilcox
//  all pads now updated after movement completes to avoid bugs from
//  undeploy in script
//  
//  243   2/24/98 10:51a Aburgess
//  modifications made to correct no audio on continues bug
//  
//  242   2/23/98 3:55p Phu
//  debug objects
//  
//  241   2/21/98 5:50p Nrobinso
//  turn off yeah/boo
//  
//  240   2/20/98 4:26p Aburgess
//  added debug info routines
//  
//  239   2/20/98 4:32p Nrobinso
//  removed header info
//  
//  238   2/20/98 1:09p Phu
//  draw icons to front if paused
//  
//  237   2/20/98 12:53p Phu
//  game pause stuff
//  
//  236   2/20/98 1:17p Nrobinso
//  fix up sounds
//  
//  235   2/19/98 2:55p Aburgess
//  modifications made to support BAD Map detection in remote players.
//  Added checks for BootCamp game play mode.
//  
//  234   2/17/98 3:59p Nrobinso
//  remove reset cursor
//  
//  233   2/17/98 3:03p Nrobinso
//  put debug commands on final compile flag
//  
//  232   2/13/98 3:59p Nrobinso
//  remove avi player
//  
//  231   2/13/98 3:42p Nrobinso
//  cleanup some traces
//  
//  230   2/13/98 12:47p Phu
//  get rid of firing bar
//  
//  229   2/13/98 12:27p Nrobinso
//  change names of input capturing functions
//  
//  228   2/13/98 12:21p Nrobinso
//  joystick access added
//  
//  227   2/12/98 8:55p Phu
//  mortar screen scroll, better force of gravity
//  
//  226   2/12/98 4:17p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  225   2/10/98 1:11p Nrobinso
//  add joystick normalize
//  
//  224   2/09/98 1:54p Aburgess
//  modifications made to support IN GAME screens, Cursor control, and
//  Rules presentation
//  
//  223   2/06/98 11:27p Nrobinso
//  change mission and map function names
//  
//  222   2/05/98 9:49a Aburgess
//  modifications made to support the OPTIONS screens (config, abort
//  mission and audio) during game play mode.
//  
//  221   2/04/98 5:24p Bwilcox
//  
//  220   2/03/98 2:40p Aburgess
//  modifications made to correct music stream failures
//  
//  219   2/02/98 1:52p Nrobinso
//  move mission statement sprite
//  
//  218   2/02/98 1:01p Aburgess
//  modifications made to support new mission briefing references through
//  campaign.cpn
//  
//  217   2/02/98 11:42a Phu
//  implement ShowWindowsCursor()
//  
//  216   2/02/98 10:06a Dmaynard
//  put back multi-player Pause messages when your machine has loaded but
//  others haven't finished loading.
//  
//  215   2/01/98 10:56p Nrobinso
//  use PROFILING_ACTIVE flag for profiling
//  
//  214   2/01/98 8:12p Nrobinso
//  call trigger for keyboard win (only works on host)
//  
//  213   1/29/98 12:11p Aburgess
//  modifications made to support mission statement/pause/recall mission
//  processing
//  
//  212   1/29/98 10:51a Dmaynard
//  Moved Script and Event Initialization to happen before user ployment
//  (setup) phase.
//  
//  211   1/28/98 1:25p Bwilcox
//  fixed load/free stuff
//  
//  210   1/28/98 10:50a Bwilcox
//  removed call to aimapallocate
//  
//  209   1/28/98 10:13a Aburgess
//  modifications made to support game start MISSION recall. Support for
//  successive missions has not been implemented yet and will still display
//  the old MISSION STATEMENT interface. Additionally, access directly to
//  the HOST and REMOTE campaign select screens now occurs if in a lobby
//  session.
//  
//  208   1/27/98 12:18p Bwilcox
//  removeditems of army when army delete
//  
//  207   1/26/98 3:32p Phu
//  multiplayer frag counters
//  
//  206   1/26/98 1:58p Aburgess
//  modifications made to temporarily diable full screen maps in
//  multiplayer
//  
//  205   1/26/98 12:58p Aburgess
//  modifications made to support the new mission briefing screens
//  
//  204   1/25/98 5:02a Bwilcox
//  map allocate of ai data occurs as soon as sizing is known
//  
//  203   1/25/98 4:38a Bwilcox
//  separating ai map allocation from init
//  
//  202   1/26/98 12:00p Nrobinso
//  new path defines
//  
//  201   1/25/98 5:53p Nrobinso
//  turn on cursor for options menu
//  
//  200   1/24/98 3:35p Aburgess
//  modifications made to support Recall Mission and Full screen Map
//  
//  199   1/23/98 9:33a Aburgess
//  noe uses new LEGAL title screen
//  
//  198   1/22/98 6:44p Nrobinso
//  use SetPath
//  
//  197   1/22/98 2:45p Phu
//  draw airsupport before drawing dashboard
//  
//  196   1/22/98 1:20p Nrobinso
//  
//  195   1/21/98 12:49p Aburgess
//  gameNoisy must be turned on in special circumstances. More to follow
//  
//  194   1/21/98 11:58a Nrobinso
//  improve cursor visibility
//  
//  193   1/21/98 12:05p Aburgess
//  selective disabling of audio
//  
//  192   1/21/98 11:24a Aburgess
//  modifications made to support <RETURN>, <Y>, and <N> keys in stat
//  screens
//  
//  191   1/21/98 9:22a Aburgess
//  modifications made to shorten the STRM and VOICE monitor interrupts.
//  Also merged the audio ON/OFF switching. In addition, all audio is now
//  turned off during mission load as that routine has a large frame
//  overrun problem disallowing updates to audio.
//  
//  190   1/20/98 7:40p Phu
//  make the windows mouse disappear!
//  
//  189   1/20/98 3:54p Phu
//  test code for expanding ownership areas in mp
//
//  188   1/20/98 12:46a Aburgess
//  lastest working murder
//  
//  187   1/16/98 1:13p Dmaynard
//  Added DebugDisplay for tracing Comm Flow and Symmetric Protocol Flow.
//  
//  186   1/14/98 2:16p Aburgess
//  modifications made to support GAME_PLAY Options screens
//  
//  185   1/09/98 6:35p Nrobinso
//  call ArmyUpdatePads to replace all existing forces on pads
//  
//  184   1/09/98 9:52a Nrobinso
//  move forcefullscreen back to mainfrm
//  
//  183   1/09/98 9:33a Aburgess
//  forcefullscreen now called in New_GAME_PLAY_STATE and
//  New_INIT_GAME_PLAY_STATE
//  
//  182   1/08/98 6:29p Phu
//  
//  181   1/07/98 3:26p Phu
//  fix object owner numbering bug, undeploy unused objects
//  
//  180   1/05/98 2:35p Aburgess
//  disabled MissionMusic calls in Multiplayer mode
//  
//  179   1/05/98 2:31p Aburgess
//  corrected Voice deletions.
//  
//  178   1/05/98 10:32a Aburgess
//  latest attempt to resolve Streaming bug. Voice is now handled in a
//  seperate handler.
//
//	...
//
//  2     96-12-04 13:49 Ereich
//  This file was created as a result of the clean-up of MainFrm.cpp.  It
//  has all game flow functions as well as GraphicsLoad() and
//  GraphicsFree().  These graphics functions were moved because they are
//  highly dependant upon the game state as to what they do.
//
//  1     96-12-04 11:19 Ereich
//  First pass at seperating game flow functions from MainFrm.cpp to
//  clean-up CMainFrame class file.
//
//  $Nokeywords:$
//=========================================================================

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"						// required for pre-compiled headers...

#include "army.h"
#include "map.h"
#include "ui.h"
#include "scenario.h"
#include "Input.h"
#include "audio.h"
#include "GameFlow.h"
#include "comm.h"
#include "GameProc.h"
#include "DrawObject.h"
#include "MainFrm.h"
#include "miscfile.h"
#include "Tad.h"
#include "Disp.h"
#include "newdoor.h"
#include "explosions.h"
#include "aix.h"
#include "stratmap.h"
#include "vehicle.h"
#include "Movie.h"
#include "wobject.h"
#include "event.h"
#include "pad.h"
#include "scripts.h"
#include "States.h"
#include "Screen.h"
#include "Stats.h"
#include "air.h"
#include "Sarge.h"
#include "Audio.h"
#include "Commands.h"
#include "Debug.h"
#include "newdoor.h"
#include "fileio.h"
#include "Error.h"

void DrawBigMap();
extern SUserInterface UI_MOVIE_STATE ;
extern void AIDraw( void );
extern BOOL AiInControl( void );

void MissionInit();
void BeginMission(void);
void EndMission(void);
void GraphicsFree();
BOOL GraphicsLoad();
void	ClearAIPending();
// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//                  Defines
/////////////////////////////////////////////////////////////////////////////
#define MAX_BMS	300

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
CGame	gGame, *gpGame=&gGame;					// global game object and pointer
extern char Allah;
BOOL	DBGflag;								// runtime changeable Debug flag

BOOL	bDisplayRecall = FALSE;
BOOL	bAudioRecall   = FALSE;
BOOL	bMissionMusic  = FALSE;

long playCycle = 0;								// what cycle is this

SPRITE	PauseSprite;
SPRITE	RecallSprite;

int gameresult=GAMERESULT_NONE;

extern int	DispXObjectCount;
extern int gGlobalPlacement;


/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////
int	GFnRestore = 0;

#ifndef FINAL
	int bmnumber = 0;
	int bmindex = 0;
	char bmname[32];
	BOOL	save_series = FALSE;
	DWORD	save_time;


	HBITMAP gbmarray[MAX_BMS];
	BYTE *gbitarray[MAX_BMS];
#endif	//ndef FINAL

SGameState StateChanges[GAME_TOTAL] = {
// KEEP THIS IN SYNC WITH GAME_STATE enum...
	GAME_STATE_AUTO( GAME_NULL_STATE ),				// null or undefined state

	GAME_STATE_AUTO( GAME_INIT_STATE ),				// game initialization state
	GAME_STATE_AUTO( GAME_MOVIE_STATE ),			// AVI movie playing
	GAME_STATE_AUTO( GAME_TITLE_SCREEN_STATE ),		// title screen

	GAME_STATE_AUTO( GAME_INIT_PLAY_STATE ),		// play mode initialization processing
	GAME_STATE_AUTO( GAME_PLAY_STATE ),				// play mode game processing
	GAME_STATE_AUTO( GAME_EXIT_PLAY_STATE ),		// play mode initialization processing

	GAME_STATE_AUTO( GAME_TEST_STATE )				// DEBUG
};

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////
void DisplayGamePlay(BOOL draw_cursors);
void ActionGamePlay();
void ActionGameSetup();

/////////////////////////////////////////////////////////////////////////////
// Class construction/destruction

CGame::CGame() {
	ePrevState     = GAME_NULL_STATE;	// previous game state
	SetState(GAME_INIT_STATE);			// current game state

	Music       = TRUE;					// enable Music
	Voice       = TRUE;					// enable Voice
	Sfx         = TRUE;					// enable Sfx sounds
	HavePlayed  = FALSE;				// signify a free application

	m_PauseFlags = 0;					// disable all pause flags
	nPauseDelay  = 0;					// no initial pause delay
	m_DelayFunc  = 0;
	bNeedRestore = FALSE;				// display needs to be restored

	BootCamp   = FALSE;
    CaptureFlag = FALSE;
	MapName    = "ALPINE1.AMM";
	GameType   = GAMETYPE_ONEPLAYER;
	CampaignID = 0;
	ScenarioID = 0;
	MissionID  = 0;

	game_substate = NULL_SUB_STATE;

	// initialize the DBGflag
	DBGflag = FALSE;
}

CGame::~CGame() {
	// TODO: write the destructor...
}

/////////////////////////////////////////////////////////////////////////////
//					Global Functions

// FINAL indicates that you want to strip out anything which doesn't belong in
// the commercial version of the game.

#ifndef FINAL
// keep the screen save functions around until we ship it
void CGame::SaveSingle() {
	sprintf(bmname,"save%4.4d.bmp",bmnumber++);
	pBackBufferPL->PageLock(0);
	DDSaveBitmap(bmname, pBackBuffer);
	pBackBufferPL->PageUnlock(0);
}

void CGame::SaveSeriesOn()	{
	save_series = TRUE;
	bmindex = 0;
	save_time = dwAnimTime;
	DDSetSaveBitmap(pBackBuffer);
}

void CGame::SaveSeriesOff()	{
	HBITMAP *bm = gbmarray;
	BYTE **bit = gbitarray;

	for (int i=0; i<bmindex; i++)	{
		sprintf(bmname,"save%4.4d.bmp",bmnumber++);
		DDSaveBitmapArray(bmname, bm++, bit++);
	}
	save_series = FALSE;
}
#endif	//ndef FINAL

void CGame::MusicToggle( void ) {
	Music ^= 1;
	if ( Music )
		audioMusicOn();
	else
		audioMusicOff();
}

void CGame::VoiceToggle( void ) {
	Voice ^= 1;
	if ( Voice )
		audioVoiceOn();
	else
		audioVoiceOff();
}

void CGame::SfxToggle( void ) {
	Sfx ^= 1;
	if ( Sfx )
		audioSfxOn();
	else
		audioSfxOff();
}


DWORD CGame::PauseGame(DWORD mask) {
	m_PauseFlags |= mask;
	return(m_PauseFlags);
}

DWORD CGame::UnPauseGame(DWORD mask) {
	m_PauseFlags &= ~mask;
	return(m_PauseFlags);
}

DWORD CGame::IsPaused() {
	return(m_PauseFlags);
}

void CGame::GameDisplay() {
	if(m_Display && (GetFocus() == pMainFrame->GetHwnd()) ) {
		(m_Display)();
	}

#ifndef FINAL
	if (save_series)	{
		DDCacheBitmap(pBackBuffer, gbmarray+bmindex, gbitarray+bmindex);
		bmindex++;
		if (bmindex >= MAX_BMS)
			SaveSeriesOff();
	}

	DisplayDBG();
#endif	//ndef FINAL
}


void CGame::GameAction() {
	if(m_Action) {
		(m_Action)();
	}
}


void CGame::ChatTimer(void) {
	if( gChatTimer ) {
		if( (gChatTimer -= dwDeltaTime) < 0 ) {
			gChatTimer = 0;
		}
	}
}


void	CGame::SetState(GAME_STATE gameState)
{
	SGameState *pGS;

	PauseGame( PAUSE_INIT );

	// Change the game state
	ePrevState = eGameState;
	eGameState = gameState;
	if ( eGameState>=GAME_TOTAL)
		eGameState = GAME_NULL_STATE;

	// handle clean-up of the old state
	pGS = &(StateChanges[ePrevState]);

	if( ePrevState<GAME_TOTAL ) {
#ifndef FINAL
        if (Allah == 1)	dbgWrite("GOD view");
        else if (Allah == 2) dbgWrite("FOE view");
        else dbgWrite( pGS->pName );
#endif	//ndef FINAL

		if(pGS->pOld) {
			(pGS->pOld)(eGameState);
		}
	} 
	else
	{
		ePrevState = GAME_NULL_STATE;		// force it to an error state
	}

	// handle state related changes which must occur before initialization of the new state
	pGS = &(StateChanges[eGameState]);

	m_GrLoad	= pGS->pGLd;
	m_Display	= pGS->pDsp;
	m_Action	= pGS->pAct;

	// handle initialization of the new state
	if( eGameState<GAME_TOTAL ) {
		if(pGS->pNew) {
			(pGS->pNew)(ePrevState);
		}
		gpGame->UnPauseGame( PAUSE_INIT );
		dbgWrite( pGS->pName );
	} 
	else 
	{
		eGameState = GAME_NULL_STATE;		// force it to an error state
	}
}

static char	GAME_NULL_state_name[]          = "GAME_NULL_STATE";
static char	GAME_INIT_state_name[]          = "GAME_INIT_STATE";
static char	GAME_MOVIE_state_name[]         = "GAME_MOVIE_STATE";
static char	GAME_TITLE_SCREEN_state_name[]  = "GAME_TITLE_SCREEN_STATE";
static char	GAME_INIT_PLAY_state_name[]     = "GAME_INIT_PLAY_STATE";
static char	GAME_PLAY_state_name[]          = "GAME_PLAY_STATE";
static char	GAME_EXIT_PLAY_state_name[]     = "GAME_EXIT_PLAY_STATE";
static char	GAME_TEST_state_name[]          = "GAME_TEST_STATE";

static char* GAMEstateNames[ GAME_TOTAL ] =
{
	GAME_NULL_state_name,
	GAME_INIT_state_name,
	GAME_MOVIE_state_name,
	GAME_TITLE_SCREEN_state_name,
	GAME_INIT_PLAY_state_name,
	GAME_PLAY_state_name,
	GAME_EXIT_PLAY_state_name,
	GAME_TEST_state_name
};

GAME_STATE	CGame::GetState(void)
{
	return(eGameState);
}

GAME_STATE	CGame::PrevState(void)
{
	return(ePrevState);
}

char*	GetStateName( GAME_STATE game_state )
{
	return( GAMEstateNames[ game_state ] );
}

static char	NULL_substate_name[]          = "NULL_SUB_STATE";
static char	PLAY_substate_name[]          = "PLAY_SUB_STATE";
static char	PLAY_SETUP_substate_name[]    = "PLAY_SETUP_SUB_STATE";
static char	PLAY_OPTIONS_substate_name[]  = "PLAY_OPTIONS_SUB_STATE";
static char	STAT_substate_name[]          = "STAT_SUB_STATE";
static char* SUBstateNames[ LAST_SUB_STATE ] =
{
	NULL_substate_name,
	PLAY_substate_name,
	PLAY_SETUP_substate_name,
	PLAY_OPTIONS_substate_name,
	STAT_substate_name
};


void	CGame::SetSubState(GAME_SUBSTATE subState)
{
	// clean-up of the old state
	switch(game_substate)	{
		case NULL_SUB_STATE:
			break;
		case PLAY_SETUP_SUB_STATE:
			UI_TurnOffStrategoMode();
			break;
		case PLAY_SUB_STATE:
			gpComm->ReportBWStats();
			EndMission();
			DisplayGamePlay(FALSE);
			DDCopyBackToFront();
			break;
		case PLAY_OPTIONS_SUB_STATE:
			ScrnOptionsEndSubstate();
			break;
		case STAT_SUB_STATE:
			ScrnStatEndSubstate();
			break;
	}

	// init the new state
	switch(subState)	{
		case NULL_SUB_STATE:
			break;
		case PLAY_SETUP_SUB_STATE:
			ShowTheCursor(FALSE);
			gGlobalPlacement = 4;
			pMainFrame->SetUI(&UI_GAME_SETUP_STATE);
			pKeyTable = SetupKeyTable;
			pPrePauseKeyTable = NULL;
			PlayerClearInput();
			MissionInit();
			UI_CurMode = UIMODE_SCROLLING;
			break;
		case PLAY_SUB_STATE:
			ShowTheCursor(FALSE);
			SetNormalizeJoystickInput();
			pMainFrame->SetUI(&UI_GAME_PLAY_STATE);
			pKeyTable = SargeKeyTable;
			pPrePauseKeyTable = NULL;
			UI_CurMode = UIMODE_LOOKINGATSARGE;
			NeedToJumpToSarge = 1;
			if ( gpGame->game_substate != PLAY_OPTIONS_SUB_STATE )
			{
				if (gpGame->GameType == GAMETYPE_ONEPLAYER)
					MissionInit();
				PlayerClearInput();
				BeginMission();
				if (gpGame->GameType == GAMETYPE_ONEPLAYER)
					SargePointer(ARMY_PLAYER)->questItem = GetMissionKey();
			}
			gpComm->ResetBWStats();
			break;
		case PLAY_OPTIONS_SUB_STATE:
			ScrnOptionsInitSubstate();
			break;
		case STAT_SUB_STATE:
			ScrnStatInitSubstate();
			break;
	}

	// Change the game state
	previous_game_substate = game_substate;
	game_substate = subState;
}


GAME_SUBSTATE	CGame::GetSubState(void)
{
	return(game_substate);
}

GAME_SUBSTATE	CGame::PrevSubState(void)
{
	return(previous_game_substate);
}

char*	GetSubStateName( GAME_SUBSTATE game_sub_state )
{
	return( SUBstateNames[ game_sub_state ] );
}


BOOL CGame::GraphicsLoad()	{
	BOOL retval;

	// some state dependent loading
	if(m_GrLoad) {
		retval = (m_GrLoad)();
	}
	return retval;
}

void CGame::GraphicsFree()	{		// only frees surfaces
	BOOL temp = TRUE;
	// cleanup whatever other graphics (non-game play) there are
}


//
// LaunchGame
//
// Sets up the game layout and launches
//
void LaunchGame(void)
{
    HRESULT hr;

    // initialize global message buffers
    InitMessageBuffers();

    // get current session description (m_pSDesc is initialized in here)
    hr = gpComm->GetSessionDesc();
    if (FAILED(hr) || (!gpComm->m_pSDesc))
    {
        goto ABORT;
    }
    return;

ABORT:
    // something went wrong, terminate game?
	;
}

#ifdef TRACE_TIME
	long prevtimer, curtimer;
	void TraceTime( char *fname )
	{
		curtimer = GetTickCount();
		TRACE( "%s(): %ld\n", fname, curtimer-prevtimer );
		prevtimer = curtimer;
	}
#else
	#define TraceTime(foo)
#endif

//////////////////////////////////////////////////////////////////////////////
// GameFlow.cpp game states
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

void New_GAME_NULL_STATE(GAME_STATE gameState) {
	pMainFrame->SetUI(NULL);									// disable user-interface...
}
void Old_GAME_NULL_STATE(GAME_STATE gameState) {
	return;														// provided for debugging purposes
}
BOOL GLd_GAME_NULL_STATE() {
	return TRUE;														// provided for debugging purposes
}
void Dsp_GAME_NULL_STATE() {
	return;														// provided for debugging purposes
}
void Act_GAME_NULL_STATE() {
	return;														// provided for debugging purposes
}



void New_GAME_INIT_STATE(GAME_STATE gameState) {
	pMainFrame->SetUI(NULL);									// disable user-interface...

}

void Old_GAME_INIT_STATE(GAME_STATE gameState) {
	return;														// provided for debugging purposes
}
BOOL GLd_GAME_INIT_STATE() {
	return TRUE;												// provided for debugging purposes
}
void Dsp_GAME_INIT_STATE() {
	return;														// provided for debugging purposes
}
void Act_GAME_INIT_STATE() {
	return;
}

void New_GAME_PLAY_STATE(GAME_STATE gameState) {

	gpGame->start_game = TRUE;

	SetPalette(&pMainFrame->GamePalette);

	SetMapGameWindow();				// set the game window for the map
	UI_InitScreen();

	SM_UpdateStrategicMap(curstratmap);

	EraseSurfaces();

	// check to see if any audio needs to be restored
	gameNoisy();

	// We are now ready to start sending and receiving messages.
	// All units should be deployer on all machines
	if ( gpGame->GameType != GAMETYPE_ONEPLAYER )
	{
		gpGame->UnPauseGame(PAUSE_MAPLOAD);
// if this message gets dropped (Can happen on IPX (rarely)
// The game is frozen and locked out Send it twice to be sure
		SendGamePause(FALSE,PAUSE_MAPLOAD );
		SendGamePause(FALSE,PAUSE_MAPLOAD );
// In case we are pause  unpause here
		gpGame->UnPauseGame(PAUSE_LOCAL);
		SendGamePause(FALSE,PAUSE_LOCAL);
	}

	gpGame->start_game = FALSE;
}
void Old_GAME_PLAY_STATE(GAME_STATE gameState) {
	EndMission();
	ScrnExit();

 	KillAirSupport();					//	InitAirSupport();
	GraphicsFree();

	FreeExplosions();					//	InitExplosions();
//	FreeTileCycler();					//	InitTileCycler();
	killFiringBar();					//	initFiringBar();
	FreeDashboard();					//	DashboardInit();
	SM_FreeStrategicMap(curstratmap);	//	SM_InitStrategicMap();
	curstratmap = NULL;
	FreeLocalObjects();					//	InitLocalObjects();
	VehicleExit();						//	VehicleInit();
	ArmyExit();							//	ArmyCreate();
	TadFree();							//	TadInit();
	AiMapExit();						//	AiMapInit();
	MapFree();							//	MapLoad();
	ReleaseScriptNames();

	if( _LOAD_FROM_DATAFILE )			// close the data file if nec.
		CloseDataFile();

	SetBackGameWindow();				//	SetMapGameWindow();

	// the following do not have an end quivalent
		//	UI_InitScreen();
		//	AiDefaultLoad();
		//	InitObjects();		// allocated memory freed by MapFree()
		//	InitItemNames();
		//	PlayerColorMapping();
		//	ArmyInit();


	return;
}
BOOL GLd_GAME_PLAY_STATE() {
	return GraphicsLoad();
}

void Dsp_GAME_PLAY_STATE() 
{
	switch( gpGame->game_substate )
	{
	case NULL_SUB_STATE:
		break;
	case PLAY_SETUP_SUB_STATE:
	case PLAY_SUB_STATE:
//		TRACE("Entering DisplayGamePlay()\n");
		DisplayGamePlay(TRUE);
		if( ScrnOptionsVisible() )
			ScrnDoDisplay();
		break;
	case PLAY_OPTIONS_SUB_STATE:
	case STAT_SUB_STATE:
		ScrnDoDisplay();
		break;
	default:
		ASSERT(0);
	}
}
extern	int MouseDx;
extern	int MouseDy;

void Act_GAME_PLAY_STATE() {
	MouseDx = 0;
	MouseDy = 0;

	switch( gpGame->game_substate )
	{
	case NULL_SUB_STATE:
		break;
	case PLAY_SETUP_SUB_STATE:
//		TRACE("PLAY_SETUP_SUB_STATE\n");
		if( ScrnOptionsVisible() )
		{
			ReadMouse(TRUE);
			ReadCapturedKeyboard();
			ReadCapturedJoystick();
			ScrnDoActions();
		}
		else
		{
			ReadMouse();

			if( gpGame->IsPaused() )
			{
				if( pKeyTable != PauseKeyTable )
					pPrePauseKeyTable = pKeyTable;
				pKeyTable = PauseKeyTable;
			}
			else
			{
				if( pPrePauseKeyTable )
				{
					pKeyTable = pPrePauseKeyTable;
					pPrePauseKeyTable = NULL;
				}
			}

			ReadKeyboard();
			ReadJoystick();
			if (!gpGame->IsPaused())
				ActionGameSetup();
		}
		break;
	case PLAY_SUB_STATE:
		if( ScrnOptionsVisible() )
		{
			ReadMouse(TRUE);
			if( pKeyTable != PauseKeyTable )
				pPrePauseKeyTable = pKeyTable;
			pKeyTable = PauseKeyTable;
			ReadCapturedKeyboard();
			ReadCapturedJoystick();
			ScrnDoActions();
		}
		else
		{
			if( gpGame->IsPaused() )
			{
				if( pKeyTable != PauseKeyTable )
					pPrePauseKeyTable = pKeyTable;
				pKeyTable = PauseKeyTable;
			}
			else
			{
				if( pPrePauseKeyTable )
				{
					pKeyTable = pPrePauseKeyTable;
					pPrePauseKeyTable = NULL;
				}
			}
			ReadMouse();
			ReadKeyboard();
			ReadJoystick();
			ActionGamePlay();
		}
		break;
	case PLAY_OPTIONS_SUB_STATE:
	case STAT_SUB_STATE:
		ReadMouse();
		ScrnDoActions();
		break;
	default:
		ASSERT(0);
	}
}

void New_GAME_INIT_PLAY_STATE(GAME_STATE gameState) {

	// Start everyone paused until everyone is done with this init	
	if (gpComm->m_bActive) {
		gpGame->PauseGame(PAUSE_MAPLOAD);
		SendGamePause(TRUE, PAUSE_MAPLOAD);
		gpComm->m_ArmyReady[0] = FALSE;
		SendGameReadyMsg(FALSE);
	}

	// check to see if any audio is active, if so, turn off, and set
	// a restore flag
	gameQuiet();

	// disable the cursor
	ShowTheCursor( FALSE );

	// load the an image
	ScrnDisplayLoading();

#ifdef TRACE_TIME
	prevtimer = GetTickCount();
#endif

	ArmyInit();
	TraceTime( "ArmyInit" );

	MapLoad((LPCTSTR) gpGame->MapName);		// load the current map
	TraceTime( "MapLoad" );
	MissionLoading( 600, 20000 );

	AiDataLoad( the_map.terrain_name );	// load in the default AI data for this map
	TraceTime( "AiDefaultLoad" );
	MissionLoading( 1000, 20000 );

	VehicleInit();
	PlayerColorMapping();		// set up unit colors based on the colors players have selected
								// note that this is a default setup until players actually select
								// colors and we modify PlayerColorMapping() to look at this data
	TadInit();
	InitObjects();
	InitLocalObjects();
	ArmyCreate();
	MapAssetCreate();
	RemoveUnusedItems();
	InitItemNames();
	curstratmap = SM_InitStrategicMap();
	DashboardInit();
	initFiringBar();
//	InitTileCycler();
	InitExplosions();			// initialize the explosions
	MissionLoading( 1300, 20000 );

	GraphicsLoad();		//	GLd_GAME_INIT_PLAY_STATE();	// map movement is updated here
	InitAirSupport();
	TraceTime( "GraphicsLoad" );

    // make SURE this occurs after all objects etc are loaded since it
    // postprocesses the map (like putting an untrafficable border around it
    // It should be done even if AICommander not involved.
    AiMapInit();
	TraceTime( "AiMapInit" );
	MissionLoading( 17000, 20000 );

	// needs to happen after all things affecting movement, incl. boundary
    ProcessPadLayer();
	TraceTime( "ProcessPadLayer" );

	// signify that we're no longer a fresh application
	gpGame->HavePlayed = TRUE;
	MissionLoading( 19000, 20000 );

	// prepare to display a mission statement or multiplayer setup
	if (gpGame->GameType == GAMETYPE_ONEPLAYER)
		gpGame->SetSubState( PLAY_SUB_STATE );
	else
		gpGame->SetSubState( PLAY_SETUP_SUB_STATE );

	gpGame->SetState( GAME_PLAY_STATE );

	if (gpGame->GameType == GAMETYPE_ONEPLAYER)
	{
		// set a delay for PAUSE
		gpGame->nPauseDelay = 2;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
		gpGame->m_DelayFunc = UI_MissionRecall;
	}
	return;
}


void Old_GAME_INIT_PLAY_STATE(GAME_STATE gameState) {
	return;														// provided for debugging purposes
}
BOOL GLd_GAME_INIT_PLAY_STATE() {
	return TRUE;
}
// this routine is not included as one of the game state routines
void Free_GAME_INIT_PLAY_STATE() {
}
void Dsp_GAME_INIT_PLAY_STATE() {
}
void Act_GAME_INIT_PLAY_STATE() {
}


BOOL GraphicsLoad() {
	BOOL	retval = TRUE;

	MapGraphicsLoad();
	MissionLoading( 3300, 20000 );
	TraceTime( "MapGraphicsLoad" );

	LoadWorldObjectGraphics();
	TraceTime( "LoadWorldObjectGraphics" );
	MissionLoading( 3600, 20000 );

	ArmyGraphicsLoad();				// also sets up color tables
	TraceTime( "ArmyGraphicsLoad" );

	DashboardLoadGraphics();
	TraceTime( "DashboardLoadGraphics" );
	MissionLoading( 14900, 20000 );

	LoadExplosions();
	TraceTime( "LoadExplosions" );
	MissionLoading( 15500, 20000 );

	SM_LoadStrategicMapGraphics(curstratmap);
	AnimSetupDefault();
	UI_LoadCursors();
	MissionLoading( 16000, 20000 );

	return retval;
}

void GraphicsFree() {
	UI_FreeCursors();			//	UI_LoadCursors();
	FreeSprite( &RecallSprite );//	LoadSprite();
	UnloadExplosions();			//	LoadExplosions();
	AnimReleaseDefault();		//	AnimSetupDefault();
	SM_UnLoadStrategicMapGraphics(curstratmap);	//	SM_LoadStrategicMapGraphics();
	DashboardUnloadGraphics();	//	DashboardLoadGraphics();
	ArmyGraphicsFree();			//	ArmyGraphicsLoad();
	FreeWorldObjectGraphics();	//	LoadWorldObjectGraphics();
	MapGraphicsFree();			//	MapGraphicsLoad();
}


void New_GAME_EXIT_PLAY_STATE(GAME_STATE gameState) 
{
	pMainFrame->SetUI(NULL);									// disable user-interface...
}

void Old_GAME_EXIT_PLAY_STATE(GAME_STATE gameState) {
	return;														// provided for debugging purposes
}

BOOL GLd_GAME_EXIT_PLAY_STATE() {
	return TRUE;
}

void Dsp_GAME_EXIT_PLAY_STATE() {
}

void Act_GAME_EXIT_PLAY_STATE() {
}


//=============================================================================

void New_GAME_MOVIE_STATE(GAME_STATE gameState) {
	// pause the game and erase the visible surface
	gpGame->PauseGame( PAUSE_MOVIE );
	EraseVisibleSurface();

	// disable the windows cursor
	ShowTheCursor( FALSE );

	pMainFrame->SetUI(&UI_MOVIE_STATE);

	// complete the initialization
	MOVIEstateTable[ MovieGetState() ].pInitCallback();
}

void Old_GAME_MOVIE_STATE(GAME_STATE gameState) {
 	gpGame->UnPauseGame( PAUSE_MOVIE );

	pMainFrame->SetUI(NULL);									// disable user-interface...
}
BOOL GLd_GAME_MOVIE_STATE() {
	return (TRUE);
}
void Dsp_GAME_MOVIE_STATE() {
	return;
}
void Act_GAME_MOVIE_STATE() {
	return;														// provided for debugging purposes
}



void
SendChatMessage(char *msg)	{
	// send message to comm code
	if(strlen(msg)> CHAT_TEXT_MAX) msg[CHAT_TEXT_MAX-1] = 0;
	strcpy(gChatMsg.text,msg);
	SendGameMessage((LPGENERICMSG) &gChatMsg,DPID_ALLPLAYERS,0 /* Falgs*/);
}

void
SendChatMessageTo(char *msg,int whoTo)	{
	// send message to comm code
	if(strlen(msg)> CHAT_TEXT_MAX) msg[CHAT_TEXT_MAX-1] = 0;
	strcpy(gChatMsg.text,msg);
    // BUG--- need to convert specific players BW (TBD)
    // 1 == GREEN 2 = TAN 3 = GRAY 4 = BLUE
	SendGameMessage((LPGENERICMSG) &gChatMsg,DPID_ALLPLAYERS,0 /* Falgs*/);
}

void SendChatMessageToPlayer(char *msg, int whichplayer)
{
	if(strlen(msg)> CHAT_TEXT_MAX) msg[CHAT_TEXT_MAX-1] = 0;
	strcpy(gChatMsg.text,msg);
	SendGameMessage((LPGENERICMSG) &gChatMsg, gpComm->GetIDFromIndex(whichplayer), 0);
}


BOOL CheckForVideo();
void ContinueStatsToVideo();


void
GameOver( BOOL bWinner )	{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;

	ClearAIPending();

	// stop any mission music
	MissionMusic( TRUE );

	// stop any vehicle sound
	VehicleSoundOff();

	// stop all sounds
	audioStopAll();

	bDisplayRecall = bDisplayPaperMap = FALSE;

	// note if we were a winner and put up the stats
	gpGame->winner = bWinner;

	if ( gpGame->GameType == GAMETYPE_ONEPLAYER && 
		ArmyAtScenarioEnd() && 
		IsMovie(bWinner) &&
		GetSargeHealthPercentage() )
	{
		// don't forget to store off mission complete data
		pCampaign          = g_Campaigns[ g_CampaignIndex ];
		pScenario          = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
		pMission           = &(pScenario->pMissions[ g_MissionIndex ]);
		if ( bWinner )
			pMission->bVisible = STAT_PLAYED_FLAG;
		else
			pMission->bVisible = STAT_NEXT_FLAG;

		// now advance to the appropriate state
		gpGame->SetSubState(NULL_SUB_STATE);
		ScrnSetState( SCRN_NULL_STATE );

		audioEnable( pMainFrame->m_hWnd );

		if ( gpGame->winner == FALSE )
			MovieSetState( MOVIE_LOSE_STATE );
		else
			MovieSetState( MOVIE_WIN_STATE );

		gpGame->SetState( GAME_MOVIE_STATE );

		MouseDown0 = FALSE;
		gpGame->nPauseDelay = GetTickCount() + 25;
	}
	else
		gpGame->SetSubState(STAT_SUB_STATE);
}

extern void EventTriggerImmediate(EVENT_TYPE type, int num, long uid, int removeevent, int remote);


void
MissionDone( int eArmyWon )	{
	int uid = 0;
	int color = gpComm->ColorFromIndex(eArmyWon);

	switch (color)	{
		case 0:
			EventTriggerImmediate(EVENT_CONTROL, GetControlEventNum("greenwins"), uid, 0, 0);
			break;
		case 1:
			EventTriggerImmediate(EVENT_CONTROL, GetControlEventNum("tanwins"), uid, 0, 0);
			break;
		case 2:
			EventTriggerImmediate(EVENT_CONTROL, GetControlEventNum("bluewins"), uid, 0, 0);
			break;
		case 3:
			EventTriggerImmediate(EVENT_CONTROL, GetControlEventNum("graywins"), uid, 0, 0);
			break;
	}
}


void MissionInit()
{
	gameresult=GAMERESULT_NONE;
	
	// deploy units here
	ArmyGetMission();

	InitUndeployedUnitInfo();
	// now process scripts
	InitScripting(g_MissionIndex);
}

void BeginMission()
{
	StartScripting();
	ArmiesClearOldLocation(); // force all pads to update on next line
	ArmiesUpdatePads();
	SelectNextUnit();
	gpGame->dwMissionTime = 0;
}


void EndMission(void)
{
	KillScripting();
}

void TitleMusic( BOOL bStop )
{
	if ( !bStop )
		PlayStream( TITLE_MUSIC, (SND_MUSIC_FLAG|SND_LOOP_FLAG), FALSE );
	else
		StopStream( TITLE_MUSIC );
}

void CampaignMusic( BOOL bStop )
{
	CAMPAIGNREF*	pCampaign;
	int				nCampaignIndex;

	// acuire the current campaign index
	nCampaignIndex = AiCampaignIndex( gpGame->CampaignID );
	if (nCampaignIndex == -1) {TRACE("Invalid Campaign"); return; }
	pCampaign      = g_Campaigns[ nCampaignIndex ];
	if (pCampaign)	{
		if ( !bStop )
			PlayStream( pCampaign->nCampaignMusicID, (SND_MUSIC_FLAG|SND_LOOP_FLAG), FALSE );
		else
			StopStream( pCampaign->nCampaignMusicID );
	}
}

void MissionHelp( void ) {
}

void MissionMusic( BOOL bStop ) {
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	int				nCampaignIndex;
	int				nScenarioIndex;
	int				nMissionIndex;
	int				intensity;

	if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
	{
		// acuire the current campaign, scenario, and mission indecies
		nCampaignIndex = AiCampaignIndex( gpGame->CampaignID );
		if (nCampaignIndex == -1) {TRACE("Invalid Campaign"); return; }
		pCampaign      = g_Campaigns[ nCampaignIndex ];
		nScenarioIndex = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
		pScenario      = &(pCampaign->pScenarios[ nScenarioIndex ]);
		nMissionIndex  = AiMissionIndex( pScenario, gpGame->MissionID );
		pMission       = &(pScenario->pMissions[ nMissionIndex ]);

		intensity = audioGetIntensity();

		if ( bStop )
			StopStream( pMission->nMissionMusicID[intensity] );
		else
			PlayStream( pMission->nMissionMusicID[intensity], (SND_MUSIC_FLAG|SND_LOOP_FLAG), FALSE );
	}
	else
	{
		// acuire the current campaign index
		nCampaignIndex = AiMPCampaignIndex( );
		if (nCampaignIndex == -1) {TRACE("Invalid Campaign"); return; }
		pCampaign      = g_Campaigns[ nCampaignIndex ];
		if (pCampaign)	{
			if ( bStop )
				StopStream( pCampaign->nCampaignMusicID );
			else
				PlayStream( pCampaign->nCampaignMusicID, (SND_MUSIC_FLAG|SND_LOOP_FLAG), FALSE );
		}
	}
}


extern char bw2;

void DisplayGamePlay(BOOL draw_cursors)	{

	DisplayMapX();
//	if (bw2 && playCycle%16==0)
//		drawSargeTrafficability();

	DrawAirSupport();
	DrawFragCounters();
	DrawLatencyDisplay();
	Dashboard_Draw(curdashboard);
	DrawBigMap();
	SM_DrawStrategicMap(curstratmap);

	updateFiringBar();
	ShowDebugInfo();
	UI_DrawCursors();
	AIDraw();	/* handles easter eggs*/
#ifndef FINAL
	TadDrawLines();
	dbgClear();
	dbgAllah();
	dbgFrameRate();
	dbgVersion();
	dbgCommRate();
#endif	//ndef FINAL

  
}

    extern int unitdie;
void ActionGamePlay()	{

	if (!gpGame->IsPaused() && !gpGame->start_game)	{
		if (unitdie) TRACE("*start");

		 ++playCycle;	// counter for cycle-frame we are at
		//do any time-specific code
		UpdateTimer();
		if (unitdie) TRACE("PlayIn ..");
 
		// get input and update all army actions
		if (unitdie) TRACE("UpDate ");
		ArmyUpdate();

		// update World Objects
		if (unitdie) TRACE("Process ");
		ProcessLocalObjects();

		// update scrolling window
	    //	AdjustScrollWindow();

		//let the UI move the screen to where it thinks it should be

		if (unitdie) TRACE("ProcessUI ");
		UI_ProcessScreen();

		//update the map SCREEN location info
		ProcessMapPosition();

			//update the overlay layer of the strategic map
		if ((playCycle%12==0))
		{
			SM_UpdateStrategicMap(curstratmap);
		};
	}
 
	// update the user dashboard
	Dashboard_Update();
 
	switch(gameresult)
	{
	case GAMERESULT_YOUWIN:
		{
			if ( gpGame->BootCamp )
				GameOver(FALSE);
			else
				GameOver(TRUE);
		}
		break;

	case GAMERESULT_YOULOSE:
		{
			GameOver(FALSE);
		}
		break;
	}
			if (unitdie) TRACE("Out \n ");
}

void ActionGameSetup()	{

	if (!gpGame->IsPaused() && !gpGame->start_game)	{
		// get input and update all army actions
		ArmyUpdateInSetup();

		//let the UI move the screen to where it thinks it should be
		UI_ProcessScreen();

		//update the map SCREEN location info
		ProcessMapPosition();
	}

	// update the user dashboard
	Dashboard_Update();
}

void	gameQuiet( void )
{

#ifdef DBG_AUDIO
TRACE("gameQuiet()...\n" );
#endif

#if 0
TRACE("\n\ngameQuiet( Sfx:%d Music:%d Voice:%d )\n", sfxGetOn(), strmGetOn(), voiceGetOn() );
TRACE("    SFXenabled     = %d:%d\n", SFXenabled, audioSfxGetOn() );
TRACE("    STRMenabled    = %d:%d\n", STRMenabled, audioMusicGetOn() );
TRACE("    VOICEenabled   = %d:%d\n", VOICEenabled, audioVoiceGetOn() );
if ( audioSfxGetOn() )
	TRACE("     quiet SFX: yes\n" );
else
	TRACE("     quiet SFX: no\n" );
if ( audioMusicGetOn() )
	TRACE("     quiet MUSIC: yes\n" );
else
	TRACE("     quiet MUSIC: no\n" );
if ( audioVoiceGetOn() )
	TRACE("     quiet VOICE: yes\n\n\n" );
else
	TRACE("     quiet VOICE: no\n\n\n" );
#endif

	// check to see if any audio is active, if so, turn off, and set
	// a restore flag
	if ( sfxGetOn() )
	{
		GFnRestore |= SND_SFX_FLAG;
		audioSfxOff();
	}
	if ( strmGetOn() )
	{
		GFnRestore |= SND_MUSIC_FLAG;
		audioMusicOff();
	}
	if ( voiceGetOn() )
	{
		GFnRestore |= SND_VOICE_FLAG;
		audioVoiceOff();
	}
}

void	gameNoisy( void )
{

#ifdef DBG_AUDIO
TRACE("gameNoisy()...\n" );
#endif

#if 0
TRACE("\n\ngameNoisy( Sfx:%d Music:%d Voice:%d )\n", sfxGetOn(), strmGetOn(), voiceGetOn() );
TRACE("    SFXenabled     = %d:%d\n", SFXenabled, audioSfxGetOn() );
TRACE("    STRMenabled    = %d:%d\n", STRMenabled, audioMusicGetOn() );
TRACE("    VOICEenabled   = %d:%d\n", VOICEenabled, audioVoiceGetOn() );
if ( (GFnRestore & SND_SFX_FLAG) == SND_SFX_FLAG )
	TRACE("     noisy SFX: yes\n" );
else
	TRACE("     noisy SFX: no\n" );
if ( (GFnRestore & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
	TRACE("     noisy MUSIC: yes\n" );
else
	TRACE("     noisy MUSIC: no\n" );
if ( (GFnRestore & SND_VOICE_FLAG) == SND_VOICE_FLAG )
	TRACE("     noisy VOICE: yes\n\n\n" );
else
	TRACE("     noisy VOICE: no\n\n\n" );
#endif

	// start by making sure audio has been properly enabled
	audioEnable( pMainFrame->m_hWnd );

	// now set the proper audio status for SFX, MUSIC, and VOICE
	if ( (GFnRestore & SND_SFX_FLAG) == SND_SFX_FLAG )
	{
		GFnRestore &= ~SND_SFX_FLAG;
		audioSfxOn();
	}
	if ( (GFnRestore & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
	{
		GFnRestore &= ~SND_MUSIC_FLAG;
		audioMusicOn();
	}
	if ( (GFnRestore & SND_VOICE_FLAG) == SND_VOICE_FLAG )
	{
		GFnRestore &= ~SND_VOICE_FLAG;
		audioVoiceOn();
	}
}

int	ProcessPauses( void )
{
	BOOL	bPaused = FALSE;
	BOOL	temp;

	if ( gpGame->nPauseDelay )
	{
		if (gpGame->nPauseDelay == -1)
			temp = 0;
		else if ( gpGame->nPauseDelay < HALF_SECOND )
		{
			// small logical frame delay
			--(gpGame->nPauseDelay);
			if ( gpGame->nPauseDelay == 0 )
			{
				if ( gpGame->m_DelayFunc )
					gpGame->m_DelayFunc(0);
			}
		}
		else
		{
			// time delay
			if( GetTickCount() >= (DWORD)gpGame->nPauseDelay )
				gpGame->nPauseDelay = 0;
			else
				bPaused = TRUE;
		}
	}
	else
	{
		DWORD pauseflags = gpGame->IsPaused();

		//  is one of the players still loading a map? 
		if (pauseflags & ALL_PAUSE)
			bPaused = TRUE;
	}

	return( bPaused );
}

//=========================================================================
//								EOF
//=========================================================================
