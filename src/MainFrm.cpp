/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: MainFrm.cpp $
//
//	DESCRIPTION:	implementation of the CMainFrame class
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, May 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/MainFrm.cpp 287   4/18/98 2:41p Dmaynard $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/MainFrm.cpp $
//  
//  287   4/18/98 2:41p Dmaynard
//  Added code to allow start game when host exits from setup when all
//  others have already hit start.
//  
//  286   4/16/98 11:58p Nrobinso
//  remove releasescriptnames
//  
//  285   4/15/98 4:40p Dmaynard
//  Fix Possible bug in leaving/joing remote race condition between players
//  leaving and joining.
//  
//  284   4/15/98 5:02p Phu
//  respond to SC_MONITORPOWER
//  
//  283   4/15/98 3:01p Dmaynard
//  Changed receive thread to post windows message on error instead of
//  calling ShowError Dialog from the interrupt thread.
//  
//  282   4/14/98 5:28a Aburgess
//  modifications to re-introduce the initial mission music
//  
//  281   4/14/98 2:05p Nrobinso
//  add missiontime
//  
//  280   4/14/98 10:31a Bwilcox
//  switch playcycle to elapsed time printout,
//  optimize trooper no routing when fail on victim
//  
//  279   4/13/98 2:42p Dmaynard
//  Generate BigTimeCommError when we are down to less than 10 free
//  messages rather than waiting till we are completely out.
//  
//  278   4/12/98 11:05a Nrobinso
//  reopen session if somebody leaves in map setup
//  
//  277   4/10/98 2:57a Dmaynard
//  Added BigTimeCommError  which does a ShowError and a
//  PostMessage(WMCLOSE) for fatally bad connections
//  
//  276   4/09/98 12:32p Nrobinso
//  turn windows cursor off when re-enter app
//  
//  275   4/08/98 9:08p Dmaynard
//  New Flow Control for case when connection is so bad we have run out of
//  message buffers
//  
//  274   4/08/98 12:18p Nrobinso
//  remove unused
//  
//  273   4/06/98 10:20p Dmaynard
//  Fixes a bug I introduced in RestoreGame.
//  
//  272   98/04/06 13:11 Dmaynard
//  Fix for alt-Tab restoration in Map Select Screens
//  
//  271   4/06/98 12:36p Dmaynard
//  Added Parameter to RestoreGame to ake sure my fixes for recovering from
//  Alt-Tab don't have any side effects in other cases of calling
//  restoregame.
//  
//  270   4/06/98 12:31p Dmaynard
//  
//  269   4/06/98 12:18p Dmaynard
//  Alt-Tab Restoration
//  
//  268   4/06/98 11:56a Dmaynard
//  Restore from Alt-Tab now calls proper ScrnInit routines.
//  
//  267   4/06/98 11:58a Nrobinso
//  remove unused
//  
//  266   4/04/98 8:39p Dmaynard
//  Changed the way Screen functions decide if a player is in the game.
//  Fixes bugs for players exiting and rejoining during map select.
//  
//  264   4/02/98 11:38p Aburgess
//  clear visible surface on alt-tab return
//  
//  263   4/02/98 7:34p Nrobinso
//  use dd surface 3
//  
//  262   4/02/98 3:07p Phu
//  typecast to avoid warnings
//  
//  261   4/01/98 3:20p Nrobinso
//  fix some memory release problems
//  
//  260   98/04/01 10:16 Dmaynard
//  Fix Race condition between NewHost and Destroy Player (which may arrive
//  in either order when a player leaves the dplay session.
//  
//  259   3/31/98 12:55p Bwilcox
//  dispell fog
//  
//  258   3/31/98 11:46a Dmaynard
//  Added call to ReceiveMessages in Mainloop. So we don't have to always
//  rely on Win Messages to let us know we have incoming messages in our
//  queue.
//  
//  257   3/30/98 10:10p Nrobinso
//  allow for pauses in animtime
//  
//  256   3/27/98 8:26p Dmaynard
//  Code to send events on DPSYS Messages
//  
//  255   3/23/98 7:38p Dmaynard
//  Fixing bug where sometime DPLAY neglects to tell us a player has left.
//  If Send gets an error we Assume the player is gone and destroy our
//  local structures for the player.
//  
//  254   3/23/98 6:25p Dmaynard
//  Changed Remove ActivePlayer to return a BOOL result.
//  
//  253   3/23/98 3:13p Phu
//  removed a dumb trace
//  
//  252   3/23/98 12:27p Nrobinso
//  switch to loading the aai data every map load
//  
//  251   3/22/98 6:08p Phu
//  fix parameter mismatch in rectintersect
//  
//  250   3/20/98 3:36p Dmaynard
//  Better State Changes for Lobby Start-up
//  
//  249   3/19/98 11:20p Nrobinso
//  
//  248   3/19/98 7:46p Nrobinso
//  do game display if waiting for map laod
//  
//  247   3/19/98 4:39p Phu
//  TRACES if surface doesn't fit into video memory
//  
//  246   3/19/98 2:36p Dmaynard
//  Added TIMEOUT for players in Release Builds ONLY.  If we don't hear
//  from a player for 30 seconds we remove the player.
//  
//  245   3/19/98 2:29p Aburgess
//  removed leftover cleanup reference
//  
//  244   3/19/98 1:47p Nrobinso
//  comment out game pause
//  
//  243   3/19/98 9:40a Aburgess
//  modifications made to present the 3DO logo Video
//  
//  242   3/18/98 8:20a Aburgess
//  modifications to AUDIOsounds compression
//  
//  241   3/17/98 4:42p Dmaynard
//  Added PAUSE_MAPLOAD instead of piggy-backing on the normal PAUSE_LOCAL
//  flags.
//  
//  240   3/17/98 11:15a Bwilcox
//  do an aix mission init
//  
//  239   3/16/98 6:24p Aburgess
//  quiet sounds before deletion to avoid frame overrun audio problem
//  
//  238   3/16/98 4:15p Dmaynard
//  Limiting number of resends done in interrupt(receive) thread.  Added
//  ProcessResendQueue to do the resends in the main loop when we get
//  around to it.   Flodding the comm channel from interrupt level is a bad
//  idea.
//  
//  237   3/16/98 1:55a Nrobinso
//  allow mouse input during mission recalls
//  
//  236   3/16/98 12:22a Nrobinso
//  add a second failure dialog
//  
//  235   3/14/98 10:04p Nrobinso
//  make absolutely sure we ar eon the same page as GDI before calling GDI
//  routines
//  
//  234   3/14/98 3:12p Nrobinso
//  load campaign file for remote players so they have access to music
//  
//  233   3/13/98 7:27p Bwilcox
//  
//  232   3/13/98 11:34a Nrobinso
//  remove resert menu items
//  
//  231   3/13/98 10:39a Dmaynard
//  Added Windows Timer Messages to repaint Player names so that their
//  colors can reflect latency to that player. Green==low yellow==medium
//  red== high.
//  
//  230   3/12/98 11:38a Aburgess
//  moved page flip release
//  
//  229   3/11/98 10:03p Nrobinso
//  dump SynchAcquire; set cursor pos properly at beginning
//  
//  228   3/11/98 4:22p Nrobinso
//  show windows cursor in error dialog
//  
//  227   98-03-11 12:31 Dmaynard
//  
//  226   98-03-11 8:23 Dmaynard
//  constant framerate when using non-randomize choice
//  
//  225   3/10/98 11:21p Nrobinso
//  load/free cutsor; switch to windows cursor for windows poup
//  
//  224   3/10/98 7:22p Nrobinso
//  release script names
//  
//  223   3/10/98 10:40a Dmaynard
//  Added call to CoUninitialize to unitialize the com system on system
//  exit.  Matches the CoInitialize call I added very early in CMainFrame.
//  
//  222   3/09/98 6:04p Bwilcox
//  rand now default on
//  
//  221   3/09/98 11:43a Dmaynard
//  Changed DPlay to load via COM interface  CoCreateInstance.
//  
//  220   3/07/98 11:52p Nrobinso
//  move .h file to stdafx
//  
//  219   3/07/98 10:42p Nrobinso
//  add error dialog and a call to update the screen view
//  
//  218   3/06/98 2:39p Nrobinso
//  nPauseDelay varinat to lock out direct keyboard read
//  
//  217   3/04/98 6:58p Dmaynard
//  Cleanup of m_ArmyRemote flags when a player leaves the game.
//  
//  216   3/04/98 3:59p Dmaynard
//  Handling Players leaving during Setup phase
//  
//  215   3/04/98 2:53p Dmaynard
//  Force an Unpause of any remote players that have left the game.
//  
//  214   3/02/98 11:23a Phu
//  restore after alt-tab for ODF
//  
//  213   3/01/98 11:17p Nrobinso
//  force screen update on restore
//  
//  212   3/01/98 10:01p Nrobinso
//  check for DDSurface3 interface to ensure version 5.0
//  
//  211   2/27/98 11:30a Aburgess
//  removed AllScenariosVisible from Menu options and corrected keybaord
//  access. Also disabled some trace information
//  
//  210   2/26/98 7:02p Phu
//  check in for andy
//  
//  209   2/26/98 6:01p Nrobinso
//  add AllScenariosVisible back
//  
//  208   2/26/98 4:06p Phu
//  removed profiling/ old draw map into deadcode
//  
//  207   2/26/98 2:42p Nrobinso
//  remove unused menu items
//  
//  206   2/26/98 2:26p Aburgess
//  modifiations made to properly process the ESC key in mission recall and
//  map screens
//  
//  205   2/26/98 10:55a Aburgess
//  modifications made to support delayed User Input on info type screens
//  
//  204   2/25/98 11:54p Dmaynard
//  Added Latency Simulation
//  
//  203   2/25/98 5:34p Dmaynard
//  Added return value to ArmyMessageFlush
//  
//  202   2/23/98 12:48p Phu
//  don't clear palette
//  
//  201   2/20/98 4:27p Aburgess
//  added cleanup of SFX
//  
//  200   2/19/98 2:31p Dmaynard
//  Good Map Bad Map Messages
//  
//  199   2/19/98 12:16p Dmaynard
//  check gpGame->GameType rather than old obsolete menu globals.
//  
//  198   2/17/98 8:58a Aburgess
//  corrected dialog transition in Join/Host
//  
//  197   2/16/98 9:22p Nrobinso
//  
//  196   2/13/98 4:07p Nrobinso
//  remove unused
//  
//  195   2/13/98 3:59p Nrobinso
//  remove avi player
//  
//  194   2/12/98 5:29p Phu
//  return TRUE when syskey press is processed
//  
//  193   2/11/98 10:44a Nrobinso
//  add joystick active menu item
//  
//  192   2/10/98 2:58p Dmaynard
//  Split Pause flag PAUSE_REMOTEGONE into separate Pause flags for each
//  remote machine.
//  
//  191   2/10/98 1:12p Nrobinso
//  remove absolute orientation
//  
//  190   2/09/98 6:13p Dmaynard
//  First Cut at handling a player leaving the game
//  
//  189   2/09/98 1:54p Aburgess
//  modifications made to support IN GAME screens, Cursor control, and
//  Rules presentation
//  
//  188   2/08/98 6:36p Dmaynard
//  Starting message flow during Map Selection Screens
//  
//  187   2/07/98 5:12p Nrobinso
//  remove dead code
//  
//  186   2/05/98 8:21a Bwilcox
//  added new debug menu choices immobilefoe and bw4
//  
//  185   2/03/98 4:47p Aburgess
//  repaired Remote Load background display, reduced Multiplayer chat max
//  number of lines to 2 rather than 4. Ignore NULL map references.
//  
//  184   2/02/98 10:28a Nrobinso
//  game palettte fro gray scale
//  
//  183   2/01/98 10:56p Nrobinso
//  removed old dialog code; use PROFILING_ACTIVE for profiling code
//  
//  182   2/01/98 5:45p Nrobinso
//  remove TESTPATH
//  
//  181   1/26/98 12:58p Aburgess
//  modifications made to support the new mission briefing screens
//  
//  180   1/26/98 12:00p Nrobinso
//  new path defines; put campaign file in it's own folder
//  
//  179   1/23/98 6:04p Dmaynard
//  Moved ARMYMEN GUID from Mainframe to Comm.  Still exits a copy in
//  guid.c   I don't understand GUIDs
//  
//  178   1/22/98 6:44p Nrobinso
//  use SetPath
//  
//  177   1/22/98 3:48p Dmaynard
//  Shouldn't ASSERT on getting a windows message UM_TDG_LAUNCH.  We may
//  not use this for anything currently but lets keep the sync message in
//  case we need it.
//  
//  176   1/22/98 11:59a Nrobinso
//  remove wizard
//  
//  175   1/21/98 11:32a Aburgess
//  call to shutdown sounds now occurs during close rather than destroy
//  
//  174   1/21/98 9:26a Aburgess
//  re-inserted update 172
//  
//  173   1/21/98 9:22a Aburgess
//  modifications made to shorten the STRM and VOICE monitor interrupts.
//  Also merged the audio ON/OFF switching. In addition, all audio is now
//  turned off during mission load as that routine has a large frame
//  overrun problem disallowing updates to audio.
//  
//  172   1/20/98 4:21p Phu
//  test code for expanding ownership areas in mp
//
//  171   1/20/98 11:15a Aburgess
//  changed palette initialization
//  
//  170   1/20/98 11:03a Aburgess
//  removed SMACKER directory dependency.
//  
//  169   1/20/98 12:46a Aburgess
//  lastest working murder
//  
//  168   1/19/98 7:39p Aburgess
//  comment line containing call for RES icon
//  
//  167   1/19/98 12:36p Nrobinso
//  get arrow cursor
//  
//  166   1/14/98 2:16p Aburgess
//  modifications made to support GAME_PLAY Options screens
//  
//  165   1/14/98 8:55a Bwilcox
//  
//  164   1/14/98 8:40a Bwilcox
//  
//  163   1/14/98 8:38a Bwilcox
//  FULL CHEAT VIEW added to debug menu
//  
//  162   1/13/98 4:22p Bwilcox
//  force labeling  shift-z  d  l
//  
//  161   1/13/98 8:36a Bwilcox
//  routingdraw now selects none, frnd, frnd.foe
//  
//  160   1/13/98 7:59a Bwilcox
//  put validation on the debug menu bar
//  
//  159   1/12/98 10:42a Aburgess
//  changes made to look in the RUNTIME/MAPS directory for map based
//  information
//  
//  158   1/09/98 9:52a Nrobinso
//  fix ability to run full screen as an option from title
//  
//  157   1/09/98 8:39a Aburgess
//  moved ForceFullScreen later in the processes
//  
//  156   1/06/98 1:30p Phu
//  restore dashboard/cursors after alt-tab
//  
//  155   1/06/98 10:03a Aburgess
//  added Disconnect button and reqorked session logic for MultiPlyaer mode
//  
//  154   1/05/98 2:31p Aburgess
//  corrected Voice deletions.
//  
//  153   12/24/97 12:29p Aburgess
//  added ability to toggle "All Scenarios Visible" using Shift A.
//  
//  152   12/23/97 6:40p Phu
//  fix start-in full screen mode window creation
//  
//  151   12/23/97 11:28a Aburgess
//  new AVI processing
//  
//  150   12/22/97 11:32a Aburgess
//  call to ScrnSetState to clear remaining button data
//  
//  149   12/19/97 8:50p Phu
//  system stuff
//  
//  148   12/19/97 6:45p Phu
//  don't fail on machines > 8 bit to full screen initial mode
//  
//  147   12/19/97 12:54p Phu
//  
//  146   12/19/97 10:22a Phu
//  
//  145   12/15/97 11:01a Bwilcox
//  moved SCRIPT_DEBUG stuff under debug menu control 
//  see TRACE Scripts
//  
//  144   12/15/97 1:05a Aburgess
//  removed StatStable() call
//  
//  143   12/12/97 12:24p Phu
//  
//  142   12/12/97 9:08a Bwilcox
//  removed dead code and choices from game menu.
//  
//  141   12/11/97 3:01p Bwilcox
//  esc ends tab mode
//  
//  140   12/11/97 12:53p Dmaynard
//  Fixed race condition where a map selection by host just as a new player
//  was joining caused the joining player to crash
//  
//  139   12/11/97 10:44a Aburgess
//  stats now saved even when" All Scenarios Visible" is on
//  
//  138   12/11/97 9:51a Phu
//  
//  137   12/11/97 8:54a Bwilcox
//  strong units now renamed bw1
//  
//  136   12/11/97 8:26a Bwilcox
//  relabelling bw1 and bw2 debug menu choices
//  
//  135   12/11/97 8:18a Bwilcox
//  
//  134   97/12/10 20:20 Dmaynard
//  
//  133   97/12/10 20:18 Dmaynard
//  
//  132   97/12/10 18:23 Dmaynard
//  
//  131   12/10/97 12:25p Dmaynard
//  
//  130   12/09/97 5:56p Phu
//  
//  129   12/09/97 12:12p Phu
//  
//  128   12/05/97 1:04p Nrobinso
//  
//  127   12/05/97 10:52a Dmaynard
//  Color  (m_Index)  now always being maintained for 4 players
//  
//  126   12/04/97 10:53p Nrobinso
//  removed unused code
//  
//  125   12/04/97 9:55p Aburgess
//  handling of army colors
//  
//  124   12/04/97 6:24p Bwilcox
//  removed all refs, including bad ones, to onePlayer variable
//  
//  123   12/04/97 5:52p Nrobinso
//  remove some old memory test stuff
//  
//  122   12/04/97 4:15p Nrobinso
//  turn sarge underline off; tuen debugging timing off
//  
//  121   12/03/97 9:13a Aburgess
//  using color enum rather than numeric constants
//  
//  120   12/02/97 5:24p Aburgess
//  changed check of "oneplayer" to "gpGame->GameType ==
//  GAMETYPE_ONEPLAYER"
//  
//  119   12/02/97 3:16p Bwilcox
//  added more debug menu choices
//  
//  118   12/02/97 10:45a Aburgess
//  modifications for Make All 1st Missions Visible
//  
//  117   97/12/02 9:41 Dmaynard
//  Don't call StartGame everytime you get a PLayerMessage
//  
//  116   12/01/97 9:21p Nrobinso
//  turn off traces
//  
//  115   12/01/97 5:18p Dmaynard
//  Temporary hack declared useMPUI to enable the new multi-Player UI
//  screens.  This is set to false when we go through the Multi-Player Menu
//  item (old UI)
//  
//  
//  114   12/01/97 4:47p Aburgess
//  added make all missions visible
//  
//  113   12/01/97 4:44p Dmaynard
//  Exchanging of player names
//  
//  112   12/01/97 10:02a Nrobinso
//  removed commented out stuff
//  
//  111   12/01/97 9:53a Aburgess
//  removed MissionStatement call (done elsewhere) and condensed
//  OnUpdateOnePlayer()
//  
//
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "MainFrm.h"
#include "Input.h"
#include "Army.h"
#include "Tad.h"
#include "Map.h"
#include "Text.h"
#include "newdoor.h"
#include "Armymen.h"
#include "Scenario.h"
#include "audio.h"			// AUDIO       defines, structures, and prototypes
#include "Movie.h"			// MOVIE       defines, structures, and prototypes
#include "gameflow.h"
#include "gameproc.h"
#include "DrawObject.h"
#include "comm.h"
#include "3DONetwork.h"
#include "unit.h"
#include "bmptext.h"
#include "aix.h"
#include "sarge.h"
#include "Dialog.h"
#include "Screen.h"
#include "Stats.h"
#include "commands.h"
#include "Ai.h"
#include "process.h"
#include "miscfile.h"
#include "ui.h"
#include "States.h"
#include "Smacker.h"
#include "fileio.h"

// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
long nSec,nMilliSec;
BOOL  bGameInitialized = FALSE;
extern char sargeImmune;
extern char Allah;
extern char scriptDebug;
extern TDGLIST freelist;
char bw1 = 0;
char immobileFoe = 0;
char bw4 = 0;
char bw2 = 0; 
LPDIRECTDRAW			pDirectDraw    = NULL;		// the DirectDraw object from which everything flows
LPDIRECTDRAW2			pDirectDraw2   = NULL;		// direct draw 2 object
LPDIRECTDRAWSURFACE		pFrontBuffer   = NULL;		// the front screen buffer
LPDIRECTDRAWSURFACE		pBackBuffer    = NULL;		// the off screen buffer (for creation/destruction only)
LPDIRECTDRAWSURFACE3	pBackBufferPL  = NULL;		// the off screen buffer (same as back buffer, but used for PageLocks)
LPDIRECTDRAWSURFACE		pDbgBuffer     = NULL;		// the debug info buffer


RECT					rcWindowScreen;			// Rectangle of window in screen coordinates
RECT					rcBackWindow;			// Rectangle of back window in window coordinates
RECT					rcGameWindow;			// Rectangle of back window in use in window coordinates
RECT					rcWindow;				// Rectangle of both windows in window coordinates


UINT					uiTimerID		= 0;		// user interrupt timer ID


SBOX					DisplayBox;					// Area of world displayed


LPDIRECTDRAWSURFACE		pTileBuffer     = NULL;

#ifndef FINAL
LPDIRECTDRAWSURFACE		pDebugBuffer    = NULL;
#endif

HMENU	hMenu = NULL;

char randomize = 1;
int gGlobalPlacement;
extern BOOL IsPlaying(int army);

/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////

static LONG debug_time         = 0;
// MENU STATES
static char gameStarted        = FALSE;		// cannot change to tan once started
static char multiPlayer        = TRUE;		// select a multi player game
static char disableMultiPlayer = TRUE;		// disable the multiplier feature
static char disconnectPlayer   = TRUE;		// disconnect a mulit-player session

#define	NEW_GAME		0
#define	ONE_PLYR_GAME	1
#define	TWO_PLYR_GAME	2
#define	MULTI_PLYR_GAME	3

static int	gameChoice = NEW_GAME;
static char constant_time = FALSE;		// for frame-based timing for debugging
 
extern BOOL run_windowed;

extern char validate;
char routingDraw = 0;

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////
void DummyRoutine (void);
void	ResetGameMenuItems( void );
void	ResetDebugMenuItems( void ); 
extern	void	ScrnForceUpdate( void );

BOOL	bWaitForSurfaceRestore = FALSE;
BOOL	bDebugSingleStep = FALSE;
char labelForces = 0;

extern	BOOL	bMissionMusic;

extern BOOL		START_FULL_SCREEN;
extern char		unitBehavior;
void 			AIXMissionInit();

BOOL tracemain = FALSE;

/////////////////////////////////////////////////////////////////////////////
// Global functions used by CMainFrame
void MainLoop( void )	{
//	static int  nIter = 0;
//	static int nTimerCount = 0;
	DWORD dwTime;
	int nfree;
	if (!bGameInitialized)
		return;

	if (bDebugSingleStep)	{
		TRACE("Entered MainLoop while single stepping\n");
		return;
	}

	// clean up all the audio processing
	audioCleanUp();

	// Update any Smacker Playback
	SmackerUpdate();

	if( bWaitForSurfaceRestore )
	{
		pMainFrame->RestoreGame(FALSE);
		if( bWaitForSurfaceRestore )
			return;
	}


	// windows pauses keep anything from happening
	if ( ProcessPauses() )
		return;

 	gpDO->ReadyForDraw();

	if (tracemain)
		TRACE("Ready to Display\n");

	gpGame->GameDisplay();

	if (tracemain)
		TRACE("Ready to Flip\n");

	gpDO->PageFlip();

	// never makes it to here in Bounds Checker
	if (tracemain)
		TRACE("Drawn\n");

	if (constant_time){   // per frame time for debugging
 		if (!debug_time)
 			debug_time = GetTickCount();
		gpGame->dwDeltaTime = 16;
        debug_time += 16;
        gpGame->dwAnimTime = debug_time;
		gpGame->dwMissionTime = debug_time;
		nSec = gpGame->dwMissionTime / 1000;
		nMilliSec = gpGame->dwMissionTime % 1000;

		gpGame->dwSysTime = debug_time;
    }
    else	{ // pure realtime computation
		dwTime = GetTickCount();
		if ( gpGame->IsPaused() & PAUSE_LOCAL )
		{
			gpGame->dwSysTime = dwTime;
		}
		else
		{
			gpGame->dwDeltaTime = dwTime - gpGame->dwSysTime;
			gpGame->dwSysTime = dwTime;

			gpGame->dwDeltaTime = min(gpGame->dwDeltaTime, MAX_FRAME_TIME);
			gpGame->dwAnimTime += gpGame->dwDeltaTime;
			gpGame->dwMissionTime += gpGame->dwDeltaTime;
			nSec = gpGame->dwMissionTime / 1000;
			nMilliSec = gpGame->dwMissionTime % 1000;

		}
    }

	if( !gpGame->IsPaused() && gpComm->m_bActive)	{
		// Note Receive Messages is also called when receive thread
		// posts a Windows Message UM_TDG_DPLAY
		ReceiveMessages();
	}

	gpGame->GameAction();

	if( !gpGame->IsPaused() && gpComm->m_bActive)	{
		ArmyMessageFlush(0);
	}
	if(  gpComm->m_bActive)	{
		ProcessLatencyQueue();
		ProcessResendQueue();
		TimeOutPlayers();
		nfree = ListSize(&freelist);
		// save some messages for communicating the error exit
		if (nfree < 10 ) BigTimeCommError();
	}
//	if ((gpGame->IsPaused() & PAUSE_FLOW)) {
//		ProcessResendNacks (); 
//	}


	tracemain = FALSE;
}


// Handle key message tables.
//
// Entry:
//	pKeys = pointer to key message table.
//	nChar = character to match.
//	nFlags = key flags (ala Windows).
// Exit:
//	Returns TRUE if a key was found.
//
// Notes:
//	This function handles NOP and LNK entries correctly.

extern LONG    action;             /* Player input actions. */

BOOL CMainFrame::FindKeyMsg(SKeyMsg *pKeys, UINT nChar, UINT nFlags) {
//	TRACE( "pKeys = %08lX, nChar = %02X\n", pKeys, nChar );
//	TRACE( "nChar = %02X, nFlags = %X, action = %d\n", nChar, nFlags, action );
	for( ; (pKeys->min_match <= pKeys->max_match) && pKeys->dispatcher; pKeys++ ) {
		if( (nChar >= pKeys->min_match) && (nChar <= pKeys->max_match) ) {
			if (pKeys->modifier == (UINT)modifier_keys || pKeys->modifier == ANY_KEY)	{
				if( pKeys->dispatcher ) {
					(pKeys->dispatcher)(nChar, nFlags);
				}
				return(TRUE);
			}
		} else {
			if((pKeys->min_match > pKeys->max_match) && pKeys->dispatcher ) {		// if !NULL, then this is a LNK entry
				pKeys = (SKeyMsg *)pKeys->dispatcher;
			}
		}
	}
	return(FALSE);
}

void DefKeyDown_Close(UINT nChar, UINT nFlags) {

    if (ESC_Mode()) 
		 return; // scrolling mode turned off
	if( gpGame->GetState() == GAME_PLAY_STATE )
		return;

	pMainFrame->PostMessage(WM_CLOSE, 0, 0);
}

void KDn_MusicToggle(UINT nChar, UINT nFlags) {
	TRACE("Music Toggled\n");
	pMainFrame->OnMusicToggle();
}

void KDn_SfxToggle(UINT nChar, UINT nFlags) {
	TRACE("Sfx Toggled\n");
	pMainFrame->OnSfxToggle();
}

void KDn_ShowUntrafficable(UINT nChar, UINT nFlags) {
	pMainFrame->OnTemporary();
}
void KDn_ShowPads(UINT nChar, UINT nFlags) {
	pMainFrame->OnPads();
}
void KDn_ShowBitPads(UINT nChar, UINT nFlags) {
	pMainFrame->OnBitpads();
}
void KDn_ShowNone(UINT nChar, UINT nFlags) {
	pMainFrame->OnAvenue();
}

#ifndef FINAL
void KDn_Record_SaveSingle(UINT nChar, UINT nFlags) {
	gpGame->SaveSingle();
}


void KDn_Record_SaveSeriesOn(UINT nChar, UINT nFlags) {
	gpGame->SaveSeriesOn();
}


void KDn_Record_SaveSeriesOff(UINT nChar, UINT nFlags) {
	gpGame->SaveSeriesOff();
}
#endif	//ndef FINAL


///////////////////////////////////////////////////////////////////////////
// Default key tables used by OnKeyUp and OnKeyDown


SKeyMsg DefKeysUp[] = {
	END_KEY_LIST
};


SKeyMsg DefKeysDown[] = {
	END_KEY_LIST
};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PALETTECHANGED()
	ON_WM_CLOSE()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_SET_FRAME_TIME, OnSetFrameTime)
	ON_UPDATE_COMMAND_UI(ID_SET_FRAME_TIME, OnUpdateSetFrameTime)
	ON_UPDATE_COMMAND_UI(ID_TEMPORARY, OnUpdateTemporary)
	ON_UPDATE_COMMAND_UI(ID_AVENUE, OnUpdateAvenue)
	ON_COMMAND(ID_CONTOUR, OnContour)
	ON_UPDATE_COMMAND_UI(ID_CONTOUR, OnUpdateContour)
	ON_COMMAND(ID_COMMANDER, OnCommander)
	ON_UPDATE_COMMAND_UI(ID_COMMANDER, OnUpdateCommander)
	ON_COMMAND(ID_FAKEUNITS, OnFakeunits)
	ON_UPDATE_COMMAND_UI(ID_FAKEUNITS, OnUpdateFakeunits)
	ON_WM_CHAR()
	ON_COMMAND(ID_RUN_WINDOWED, OnRunWindowed)
	ON_UPDATE_COMMAND_UI(ID_RUN_WINDOWED, OnUpdateRunWindowed)
	ON_COMMAND(ID_BOTHAI, OnBothai)
	ON_UPDATE_COMMAND_UI(ID_BOTHAI, OnUpdateBothai)
	ON_COMMAND(ID_ROUTING, OnRouting)
	ON_UPDATE_COMMAND_UI(ID_ROUTING, OnUpdateRouting)
	ON_COMMAND(ID_SINGLE, OnSingletrooper)
	ON_UPDATE_COMMAND_UI(ID_SINGLE, OnUpdateSingletrooper)
	ON_COMMAND(ID_RANDOM, OnRandom)
	ON_UPDATE_COMMAND_UI(ID_RANDOM, OnUpdateRandom)
	ON_UPDATE_COMMAND_UI(ID_PADS, OnUpdatePads)
	ON_COMMAND(ID_FOG, OnFog)
	ON_UPDATE_COMMAND_UI(ID_FOG, OnUpdateFog)
	ON_UPDATE_COMMAND_UI(ID_BITPADS, OnUpdateBitpads)
	ON_COMMAND(ID_BW01, OnBw01)
	ON_COMMAND(ID_BW02, OnBw02)
	ON_COMMAND(ID_SCRIPTDEBUG, OnScriptdebug)
	ON_UPDATE_COMMAND_UI(ID_SCRIPTDEBUG, OnUpdateScriptdebug)
	ON_COMMAND(ID_LABEL, OnLabel)
	ON_UPDATE_COMMAND_UI(ID_LABEL, OnUpdateLabel)
	ON_COMMAND(ID_BW1, OnBw1)
	ON_UPDATE_COMMAND_UI(ID_BW1, OnUpdateBw1)
	ON_COMMAND(ID_BW2, OnBw2)
	ON_UPDATE_COMMAND_UI(ID_BW2, OnUpdateBw2)
	ON_COMMAND(ID_BW3, OnBw3)
	ON_UPDATE_COMMAND_UI(ID_BW3, OnUpdateBw3)
	ON_COMMAND(ID_BW4, OnBw4)
	ON_UPDATE_COMMAND_UI(ID_BW4, OnUpdateBw4)
	ON_COMMAND(ID_NO_CD_OK, OnNoCdOk)
	ON_UPDATE_COMMAND_UI(ID_NO_CD_OK, OnUpdateNoCdOk)
	ON_COMMAND(ID_TEMPORARY, OnTemporary)
	ON_COMMAND(ID_AVENUE, OnAvenue)
	ON_COMMAND(ID_PADS, OnPads)
	ON_COMMAND(ID_BITPADS, OnBitpads)
	//}}AFX_MSG_MAP
  ON_WM_CREATE()
  ON_WM_DESTROY()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction


CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	nGameSize.cx = 640;
	nGameSize.cy = 480;
	nMaxSize = nGameSize;
	nGameBPP = 8;			// the bpp we want
	pClipper = NULL;		// window clipping structure

	// Needed for CoCreateInstance used to create DPlay Interfaces
	CoInitialize( NULL );

	// initialize palette information
	GamePalette.hpal = NULL;
	GamePalette.pDDPalette = NULL;

	AlternatePalette.hpal = NULL;
	AlternatePalette.pDDPalette = NULL;

	// disable the user-interface until a game state sets it.
	m_pMseLBtnDn = NULL;
	m_pMseLBtnUp = NULL;
	m_pMseRBtnDn = NULL;
	m_pMseRBtnUp = NULL;
	m_pMseMove = NULL;
	m_pKeyUp = NULL;
	m_pKeyDn = NULL;
	m_pKeyOverride = NULL;
	m_pCharHandler = NULL;
	m_EventTimerID = 0;
	modifier_keys = NO_KEY;

	m_bScenariosVisible = FALSE;

	// specify initial graphics mode
	gpDO->Init( FALSE );
}


CMainFrame::~CMainFrame()
{
	if (hMenu)	{
		DestroyMenu(hMenu);
		hMenu = NULL;
	}

	CoUninitialize();
}



/////////////////////////////////////////////////////////////////////////////
// Public Methods
//CMenu the_menu;


BOOL CMainFrame::Create(const CString& sTitle)
{
    CString  sClassName;
    ICONINFO tmpIcon;
    BITMAP   tmpBitmap;

    /* Load the cursor and find the hotspot */
//  CursorHandle = LoadCursor (AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_DEFAULT));
    CursorHandle = LoadCursor(NULL, IDC_ARROW);
    GetIconInfo(CursorHandle, &tmpIcon);
    GetObject(tmpIcon.hbmMask, sizeof(BITMAP), &tmpBitmap);

    if (tmpIcon.hbmMask)
        DeleteObject (tmpIcon.hbmMask);
    if (tmpIcon.hbmColor)
        DeleteObject (tmpIcon.hbmColor);

    CursorHotspot.x = tmpIcon.xHotspot;
    CursorHotspot.y = tmpIcon.yHotspot;
    CursorWidth = tmpBitmap.bmWidth;
    CursorHeight = tmpBitmap.bmHeight;

    sClassName = AfxRegisterWndClass (CS_HREDRAW | CS_VREDRAW,
        CursorHandle,
        (HBRUSH) (GetStockObject (BLACK_BRUSH)),
        LoadIcon (AfxGetInstanceHandle(), MAKEINTRESOURCE (IDI_APPICON)));

    return (CFrameWnd::Create (sClassName, sTitle,
        WS_OVERLAPPED,
        rectDefault,
        NULL,
        MAKEINTRESOURCE (IDR_MAINFRAME),
        WS_EX_TOPMOST));
}


RECT CMainFrame::SetupWindow()
{
	RECT rc;

	rc.left = 0;
	rc.top = 0;
	rc.right = nGameSize.cx;
	rc.bottom = nGameSize.cy;
	nMaxSize = nGameSize;
	rcBackWindow = rc;
	rcGameWindow = rc;

	if (!gpDO->bFullscreen)	{
		LONG dx,dy;

		// adjustment to overcome apparent bug in AdjustWindowRectEx
		rc.right += 4;
		rc.bottom += 4;

		AdjustWindowRectEx(&rc,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
			TRUE, 0);

		//  center window in the work area, make it smaller if necessary
		RECT rcWork;
		LONG dx2,dy2;

		SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0);
		dx = (rcWork.right - rcWork.left);
		dx2 = (rc.right - rc.left);
		dx -= dx2;
		dx /= 2;

		dy = (rcWork.bottom - rcWork.top);
		dy2 = (rc.bottom - rc.top);
		dy -= dy2;
		dy /= 2;

		if (dx < 0)	{
			rc.left = rcWork.left;
			rc.right = rcWork.right;
		}
		else	{
			rc.right += (dx + rcWork.left - rc.left);
			rc.left = dx + rcWork.left;
		}

		if (dy < 0)	{
			rc.bottom = rcWork.bottom;
			rc.top = rcWork.top;
		}
		else	{
			rc.bottom += (dy + rcWork.top - rc.top);
			rc.top = dy + rcWork.top;
		}


		nMaxSize.cx = rc.right - rc.left;
		nMaxSize.cy = rc.bottom - rc.top;

        CursorPos.x = pMainFrame->nMaxSize.cx / 2;
        CursorPos.y = pMainFrame->nMaxSize.cy / 2;
		ClientToScreen(&CursorPos);
		SetCursorPos(CursorPos.x, CursorPos.y); // set windows cursor to screen coords
    }

	return rc;
}


HWND CMainFrame::GetHwnd(void)	{
	return m_hWnd;
}


void CMainFrame::WindowReset()
{
	ResetWindow();
}

void
CMainFrame::ResetWindow()
{
	RECT rc;

	rc = SetupWindow();

	if (gpDO->bFullscreen)	{
		SetWindowPos(&wndTopMost, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
			SWP_NOACTIVATE);
		rcWindow = rcWindowScreen = rc;
	} else {
        // convert to a normal app window

		if (GetMenu() == NULL)	{
			CMenu	menu;

			if (hMenu)	{
				DestroyMenu(hMenu);
				hMenu = NULL;
			}

			menu.LoadMenu(MAKEINTRESOURCE(IDR_MAINFRAME));
			SetMenu( &menu );
			hMenu = menu.Detach();
		}

 		ModifyStyle(
			WS_POPUP,
			WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU);

        SetWindowPos(&wndNoTopMost, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
			SWP_NOACTIVATE);

		GetClientRect(&rcWindow);

		rcWindowScreen = rcWindow;
		ClientToScreen(&rcWindowScreen);
	}
}


UINT CMainFrame::GetBPP() {
	return(nGameBPP);
}


void CMainFrame::SetBPP(UINT bpp) {
	// TODO: add some error checking before setting...
	nGameBPP = bpp;
}



/////////////////////////////////////////////////////////////////////////////
// Protected Methods
BOOL
CMainFrame::DirectDrawInit()
{
	static  BOOL Flag_256WarningShown = FALSE;
	HRESULT	ddrval;
	HDC hDC;
	int caps;

	hDC = ::GetDC( m_hWnd );
	caps = GetDeviceCaps( hDC, BITSPIXEL );
	::ReleaseDC(m_hWnd, hDC);

	ResetWindow();

	// Create the main DD object
	if (!pDirectDraw)	{
		ddrval = ::DirectDrawCreate(NULL, &pDirectDraw, NULL);
		if( ddrval != DD_OK )	{
			return DDFail("DirectDrawCreate() failure", ddrval);
		}
	}

	//get directdraw2 com object
	ddrval = pDirectDraw->QueryInterface( IID_IDirectDraw2, (LPVOID *)&pDirectDraw2 );
	if ( ddrval != DD_OK )
		return DDFail("Unable to get Direct Draw 2 interface", ddrval);


	// Set the cooperation level for the DD object
	if(gpDO->bFullscreen)
		ddrval = pDirectDraw2->SetCooperativeLevel( m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
	else
		ddrval = pDirectDraw2->SetCooperativeLevel( m_hWnd, DDSCL_NORMAL );
	if( ddrval != DD_OK )
		return DDFail("SetCooperativeLevel() failure", ddrval);


	// Set the display mode to 640x480 256 color (8-bit) if full screen
	if(gpDO->bFullscreen)	
	{
		ddrval = pDirectDraw2->SetDisplayMode(nGameSize.cx, nGameSize.cy, 8, 0, 0 );
		if( ddrval != DD_OK )
			return DDFail("SetDisplayMode() failure for 640x480 256 color", ddrval);
		ddrval = pDirectDraw2->SetCooperativeLevel( m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
		if( ddrval != DD_OK )
			return DDFail("SetCooperativeLevel() failure", ddrval);
	}
	else
	{
		if( caps != 8 )
		{
			ddrval = pDirectDraw->SetCooperativeLevel( m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );

			if( ddrval != DD_OK )
				return DDFail("SetDisplayMode() failure for 256 color", ddrval);
			ddrval = pDirectDraw->SetDisplayMode(GetSystemMetrics(SM_CXSCREEN), 
				GetSystemMetrics(SM_CYSCREEN), 8);
			if( ddrval != DD_OK )
				return DDFail("SetDisplayMode() failure for 256 color", ddrval);
			ddrval = pDirectDraw->SetCooperativeLevel( m_hWnd, DDSCL_NORMAL );
			if( ddrval != DD_OK )
				return DDFail("SetDisplayMode() failure for 256 color", ddrval);
			else
				caps = 8;
		}
	}

	// Create the primary surface
	DDSURFACEDESC ddsd;
	memset( &ddsd, 0, sizeof( DDSURFACEDESC ) );
	ddsd.dwSize = sizeof(DDSURFACEDESC);

	if(gpDO->bFullscreen)							// full screen mode gets 1 back surface
	{	
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP
			| DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;
	}
	else	
	{
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	}
	ddrval = pDirectDraw2->CreateSurface(&ddsd, &pFrontBuffer, NULL);
	if( ddrval != DD_OK )
		return DDFail("CreateSurface() failure for primary", ddrval);

	// check for 256 color mode in windowed mode only
	if( !gpDO->bFullscreen )
	{
		if( caps != 8 )
		{
			char txt[] = "Warning: Not in 256 color mode, windowed operation won't work!";
			AfxMessageBox(txt);
			Flag_256WarningShown = TRUE;
		}
	}

	// set the text map mode for this surface
	TextSetMode( pFrontBuffer, MM_TEXT );

	DDPIXELFORMAT ddPFormat;

	INIT_DD_STRUCT(ddPFormat, DDPIXELFORMAT);
	ddrval = pFrontBuffer->GetPixelFormat(&ddPFormat);
	pMainFrame->SetBPP(ddPFormat.dwRGBBitCount);

	if(gpDO->bFullscreen)	
	{
		// Get a pointer to the offscreen surface
		DDSCAPS ddscCaps;
		ddscCaps.dwCaps = DDSCAPS_BACKBUFFER;
		ddrval = pFrontBuffer->GetAttachedSurface(&ddscCaps, &pBackBuffer);
		if( ddrval != DD_OK )	{
			return DDFail("GetAttachedSurface() failure for back buffer", ddrval);
		}
	}
	else											// if windowed,
	{	
		// create backbuffer in offscreen memory
		#ifndef BACK_BUFFER_SYSTEM
			pBackBuffer = CreateSurfaceOfSize( nGameSize.cx, nGameSize.cy, BM_DEFAULTMEMORY, RGB(0,0,0) );
		#else
			pBackBuffer = CreateSurfaceOfSize( nGameSize.cx, nGameSize.cy, BM_SYSTEMMEMORY, RGB(0,0,0) );
		#endif
		if( pBackBuffer == NULL )	
		{
			TRACE("CreateSurfaceOfSize() failure for back buffer\n");
			return FALSE;
		}

		// set the text map mode for this surface
		TextSetMode( pBackBuffer, MM_TEXT );

		ddrval = pBackBuffer->QueryInterface( IID_IDirectDrawSurface3, (LPVOID *)&pBackBufferPL);
		if( ddrval != DD_OK )	{
			return DDFail("Direct X is not at least version 5.0", ddrval);
		}

		// create clipper
		ddrval = pDirectDraw->CreateClipper(0, &pClipper, NULL);
		if( ddrval != DD_OK )	
			return DDFail("CreateClipper() failure", ddrval);

		ddrval = pClipper->SetHWnd(0, m_hWnd);
		if( ddrval != DD_OK )
			return DDFail("SetHWnd() failure for clipper", ddrval);

		ddrval = pFrontBuffer->SetClipper(pClipper);
		if( ddrval != DD_OK )
			return DDFail("SetClipper() failure for front buffer", ddrval);
	}


	//determine amount of video memory
	DWORD			dwTotalFreeMem, dwTotalAvailMem, dwPrevMem;
	DDSCAPS			ddsc;
	ddsc.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	pDirectDraw2->GetAvailableVidMem(&ddsc,	&dwTotalFreeMem, &dwTotalAvailMem);
	dwPrevMem = dwTotalAvailMem;
	#if !defined(_USESYSTEMMEMORY_)
		if (dwTotalAvailMem > (DWORD)(nGameSize.cx  * (nGameSize.cy-DASH_HEIGHT+16)))
			pTileBuffer = CreateSurfaceOfSize( nGameSize.cx, nGameSize.cy - DASH_HEIGHT + 16, BM_DEFAULTMEMORY, RGB(0,0,0) );
		if (pTileBuffer == NULL)
		{
			pTileBuffer = CreateSurfaceOfSize( nGameSize.cx, nGameSize.cy - DASH_HEIGHT + 16, BM_SYSTEMMEMORY, RGB(0,0,0) );
			if( pTileBuffer == NULL )	
			{
				TRACE("CreateSurfaceOfSize() failure for tile buffer\n");
				return FALSE;
			}
		}
		pDirectDraw2->GetAvailableVidMem( &ddsc, &dwTotalFreeMem, &dwTotalAvailMem );

#ifdef COMMENTED_OUT
		if ( dwTotalAvailMem < dwPrevMem )
			TRACE( "Created Tile Buffer in video memory (%d bytes : %d left).\n",
				dwPrevMem-dwTotalAvailMem, dwTotalAvailMem);
		else
			TRACE( "Created Tile Buffer in main memory (%d bytes).\n", nGameSize.cx *
				(nGameSize.cy - DASH_HEIGHT + 16));
#endif

	#else
		pTileBuffer = CreateSurfaceOfSize( nGameSize.cx, nGameSize.cy - DASH_HEIGHT + 16, BM_SYSTEMMEMORY, RGB(0,0,0) );
		if( pTileBuffer == NULL )	{
			TRACE("CreateSurfaceOfSize() failure for tile buffer\n");
			return FALSE;
		}
	#endif


#ifndef FINAL
	pDebugBuffer = CreateSurfaceOfSize( nGameSize.cx, nGameSize.cy - DASH_HEIGHT + 16, BM_SYSTEMMEMORY, RGB(0,0,0) );
	if( pDebugBuffer == NULL )	{
		TRACE("CreateSurfaceOfSize() failure for debug buffer\n");
		return FALSE;
	}

	DDSetColorKey(pDebugBuffer, 0);
#endif

	EraseSurfaces();

	// setup the default frontbuffer palette
	SetPath( MOVIE_PATH );
	MakeIdentityPalette( "greyscale.bmp", &pMainFrame->GamePalette );
	SetPalette( &pMainFrame->GamePalette );

	return TRUE;
}



void
CMainFrame::DirectDrawExit()
{
	DirectDrawFree();

	if (pDirectDraw)	{
		// Free the DD object
		pDirectDraw->Release();
		pDirectDraw = NULL;
	}
}


void
CMainFrame::DirectDrawFree()
{
  // Cleanup the DD object
	if (pDirectDraw2 != NULL)
	{
		pDirectDraw2->Release();
		pDirectDraw2 = NULL;
	}
	if (pDirectDraw)	{
		if(!gpDO->bFullscreen)	{
			// Free clipper
			if (pClipper)
				pClipper->Release();
			pClipper = NULL;


			// Free backbuffer
			if (pBackBuffer)
				pBackBuffer->Release();
		}
		pBackBuffer = NULL;
		pBackBufferPL = NULL;

		FreeIdentityPalette(&GamePalette);
		FreeIdentityPalette(&AlternatePalette);

		// Free front buffer
		if (pFrontBuffer)
			pFrontBuffer->Release();
		pFrontBuffer = NULL;


		// Free tile buffer
		if (pTileBuffer)
			pTileBuffer->Release();
		pTileBuffer = NULL;


#ifndef FINAL
		// Free map debug
		if (pDebugBuffer)
			pDebugBuffer->Release();
		pDebugBuffer = NULL;
#endif

		// Reset the display mode
		if(gpDO->bFullscreen)
			pDirectDraw->RestoreDisplayMode();
	}
}



//-----------------------------------------------------------------
// CMainFrame Message Handler Methods
//-----------------------------------------------------------------
int
CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//	DWORD  ThreadId;

	// Initialize DirectDraw
	if (!DirectDrawInit())
		return -1;

	if ( !InitDirectInput(m_hWnd) )
		return -1;

	// Initialize Text Processing
	if ( TextInit() )
		return -1;

	if ( spriteInit() )
		return -1;

	// initialize the audio
	if ( audioInit( m_hWnd ) )
		return -1;

	// setup the debugging message module
	dbgTextInit();

	// setup the AVI movie module
	if ( MovieInit() )
		return -1;

	// setup the AI processing NOTE: this may have to move to GAME_PLAY_INIT
//	if ( AiInit() )
//		return -1;

	// setup the Screen module
	if ( ScrnInit() )
		return -1;

	// setup the Stat module
	if ( StatInit() )
		return -1;

	MovementTableInit();	// no cleanup required

	LoadCursor();

	debug_time = 0;

	// Initialize globals need by Comm code (Wizard and IsLobbyStart)
	ghWndMain = GetHwnd();
	ghinst = AfxGetInstanceHandle();

	// Test for Lobby Start
	if (!gpComm->m_bTestedLobby ) gpComm->IsLobbyStart();
	
	if (gpComm->m_bStartedByLobby) {
		MovieSetState( MOVIE_NULL_STATE );
		gpGame->SetState( GAME_TITLE_SCREEN_STATE );
	}	else {
		// set the game state
		MovieSetState( MOVIE_3DO_STATE );
		gpGame->SetState( GAME_MOVIE_STATE );
	}

    bGameInitialized = TRUE;
	return 0;
}


void
CMainFrame::OnDestroy()
{
    bGameInitialized = FALSE;
	ScrnSetState( SCRN_NULL_STATE );
	gpGame->SetState(GAME_NULL_STATE);

	// Terminate the Stat module
	StatExit();

	// Terminate the Screen module
	ScrnExit();

	// Terminate the AI process
	AiExit();

	// terminate the debug text Module
	dbgTextExit();

	// terminate the AVI Movie Module
	MovieExit();

	// clean up and remove audio processing
	audioExit();

	TextExit();

	DirectInputExit();

	FreeCursor();
//	ReleaseScriptNames();	

	// cleanup and remove the draw window
	DirectDrawExit();

	CoUninitialize();
}

#define EXTENDED 0x100
UINT CMainFrame::TranslateKeypad(UINT nChar, UINT nFlags)
{
	static UINT xlat[] = {VK_NUMPAD9, VK_NUMPAD3, VK_NUMPAD1, VK_NUMPAD7, 
							VK_NUMPAD4, VK_NUMPAD8, VK_NUMPAD6, VK_NUMPAD2, 
							VK_SELECT, VK_PRINT, VK_EXECUTE, VK_SNAPSHOT,
							VK_NUMPAD0, VK_DECIMAL
	};

	if (nChar >= VK_PRIOR && nChar <= VK_DELETE)
	{
		if (nFlags & EXTENDED)
			return nChar;

		return xlat[nChar - VK_PRIOR];
	}
	return nChar;
}

void CMainFrame::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	SKeyMsg **pKU;
	BOOL bDefKeys = TRUE;

//	TRACE( "nChar = %02X Up\n", nChar );

	switch (nChar)	{
		case VK_SHIFT:
			modifier_keys &= ~SHIFT_KEY;
			break;
		case VK_CONTROL:
			modifier_keys &= ~CTRL_KEY;
			break;
	}

	nChar = TranslateKeypad(nChar, nFlags);
	
	if ( gpGame->nPauseDelay == 0 ) {
		if (m_pKeyOverride)	{
			if (m_pKeyOverride(nChar, KEY_UP))
				return;						// key dealt with by override function
		}

		if( m_pKeyUp ) {
			for( pKU=m_pKeyUp; *pKU && bDefKeys; pKU++ ) {
				bDefKeys = !FindKeyMsg(*pKU, nChar, nFlags);
			}
		}

		if( bDefKeys ) {
			FindKeyMsg(DefKeysUp, nChar, nFlags);
		}
	}
}

void CMainFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ( gpGame->nPauseDelay == 0 ) {
		if (m_pCharHandler)	{
			if (m_pCharHandler(nChar))
				return;						// key dealt with by override function
		}
	}	
//	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}


void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CArmyMenApp* pApp = (CArmyMenApp*)AfxGetApp();
	SKeyMsg **pKD;
	BOOL bDefKeys = TRUE;

//	TRACE( "nChar = %02X Down; Repeat %d; Flags %d; Previous %d\n", nChar, nRepCnt, nFlags, nFlags & PREVIOUS_KEY_FLAG );

	if( nRepCnt > 1 )
		return;

	switch (nChar)	{
		case VK_SHIFT:
			modifier_keys |= SHIFT_KEY;
			break;
		case VK_CONTROL:
			modifier_keys |= CTRL_KEY;
			break;
	}

	nChar = TranslateKeypad(nChar, nFlags);

	if ( gpGame->nPauseDelay == 0 || gpGame->nPauseDelay == -1) {
		if (m_pKeyOverride)	{
			if (m_pKeyOverride(nChar, nFlags))
				return;						// key dealt with by override function
		}

		if (!m_pCharHandler)	{
			if( m_pKeyDn ) {
				for( pKD=m_pKeyDn; *pKD && bDefKeys; pKD++ ) {
					bDefKeys = !FindKeyMsg(*pKD, nChar, nFlags);
				}
			}
		}

		if( bDefKeys ) {
			FindKeyMsg(DefKeysDown, nChar, nFlags);
		}
	}
}


void
CMainFrame::PauseFlip()	{
	gpGame->PauseGame( PAUSE_DIALOG );
	pDirectDraw->FlipToGDISurface();
}

void
CMainFrame::UnPauseFlip()	{
	gpGame->UnPauseGame( PAUSE_DIALOG );
	RestoreGame(FALSE);
}


void
CMainFrame::ForceFullScreen() {
	// force to full-screen mode at beginning and be done with it...
	if(!gpDO->bFullscreen) {
		dbgTextFree();
		DirectDrawFree();
		FreeBitmapFonts();
		gpDO->bFullscreen = !gpDO->bFullscreen;
		ModifyStyle(
			WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU,
			WS_BORDER
			);
		SetMenu(0);
		DirectDrawInit();
		InitBitmapFonts();
		dbgTextInit();
	}
}

void
CMainFrame::PausePageFlip()	{
	bPausePageFlip = TRUE;
	pDirectDraw->FlipToGDISurface();
}

void
CMainFrame::UnPausePageFlip()	{
	bPausePageFlip = FALSE;
	RestoreGame(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics


#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}


void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}


#endif //_DEBUG


// SetUI
//
// Entry:
//	pUI = pointer to the User-interface to use for a given game state.
// Exit:
//		Nothing.
// Notes:
//	If pUI == NULL then all of the user-interface vectors will be set to null which will
//	only allow the default user-interface messages to be processed.
SUserInterface* CMainFrame::SetUI(SUserInterface *pUI) {
    static SUserInterface* lastUI = NULL;
    SUserInterface* oldUI = lastUI;

	if(this) {									// make sure that CMainFrame has been defined first...
		if(pUI) {
			m_pMseLBtnDn	= pUI->m_pMLD;
			m_pMseLBtnUp	= pUI->m_pMLU;
			m_pMseRBtnDn	= pUI->m_pMRD;
			m_pMseRBtnUp	= pUI->m_pMRU;
			m_pMseMove		= pUI->m_pMMv;

			m_pKeyDn		= pUI->m_pKDn;
			m_pKeyUp		= pUI->m_pKUp;

			m_pKeyOverride	= pUI->m_pKOverride;
			m_pCharHandler	= pUI->m_pKChar;
		} else {
			m_pMseLBtnDn	= NULL;
			m_pMseLBtnUp	= NULL;
			m_pMseRBtnDn	= NULL;
			m_pMseRBtnUp	= NULL;
			m_pMseMove		= NULL;

			m_pKeyDn		= NULL;
			m_pKeyUp		= NULL;

			m_pKeyOverride	= NULL;
			m_pCharHandler	= NULL;
		}
	}


    lastUI = pUI;
    return oldUI;
}

void CMainFrame::SetUIKeyDn(SKeyMsg	**pKDn)	{
	m_pKeyDn = pKDn;
}

void CMainFrame::SetUIKeyUp(SKeyMsg	**pKUp)	{
	m_pKeyUp = pKUp;
}

void CMainFrame::SetUICharHandler(BOOL (*pCharHandler)(UINT character))	{
	m_pCharHandler = pCharHandler;
}

extern BOOL KeyOverride_RECALL(UINT key, BOOL down);

void CMainFrame::SetUIOverride(BOOL (*pOverride)(UINT key, BOOL down))	{
	m_pKeyOverride = pOverride;
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ( gpGame->nPauseDelay <= 0 ) {
		if(m_pMseLBtnDn) {
			(m_pMseLBtnDn)(nFlags, point);
		}
	}
}


void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	if ( gpGame->nPauseDelay <= 0 ) {
		if(m_pMseLBtnUp) {
			(m_pMseLBtnUp)(nFlags, point);
		}
	}
}


void CMainFrame::OnRButtonDown(UINT nFlags, CPoint point)
{
	if ( gpGame->nPauseDelay <= 0 ) {
		if(m_pMseRBtnDn) {
			(m_pMseRBtnDn)(nFlags, point);
		}
	}
}


void CMainFrame::OnRButtonUp(UINT nFlags, CPoint point)
{
	if ( gpGame->nPauseDelay <= 0 ) {
		if(m_pMseRBtnUp) {
			(m_pMseRBtnUp)(nFlags, point);
		}
	}
}


void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_pMseMove) {
		(m_pMseMove)(nFlags, point);
	}
}


#define FIXED_FULL_MENUS 0	// !0 == full-screen menus are working without borders on them...

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
#if FIXED_FULL_MENUS
	CRect crx, crw, crm, *crn;
	CDC *pdc, *pdcw;
	WINDOWPLACEMENT pwp;
	int height, width;
#endif	// FIXED_FULL_MENUS

	if (bDebugSingleStep)	{
		TRACE("Entered WindowProc while single stepping\n");
		return TRUE;
	}

	switch (message)	{
//		case WM_SETCURSOR:
//			break;

#if FIXED_FULL_MENUS
		case WM_NCPAINT:
			GetWindowPlacement(&pwp);
			TRACE("pwp.rect = %d, %d, %d, %d\n", pwp.rcNormalPosition.left, pwp.rcNormalPosition.top,
				pwp.rcNormalPosition.right, pwp.rcNormalPosition.bottom );


			crn = (CRect *)&pwp.rcNormalPosition;
			pdc = GetWindowDC();
			pdcw = GetDC();


			pdcw->GetClipBox(&crw);
			ClientToScreen(&crw);


			height =
				(crw.top-crn->top) +
				GetSystemMetrics(SM_CYCAPTION) +
				GetSystemMetrics(SM_CYMENU) +
				GetSystemMetrics(SM_CYBORDER) +
				GetSystemMetrics(SM_CYFRAME);


			width = GetSystemMetrics(SM_CXBORDER) + GetSystemMetrics(SM_CXFRAME);


			crx = crm = crn;
			crm.bottom = crn->top + height;
			crm.right += width;
			crx.top += height;
			crx.bottom += height;
			crx.right += width;


			TRACE("crn = %d, %d, %d, %d [w= %d, h= %d]\n", crn->left, crn->top, crn->right, crn->bottom, crn->right-crn->left, crn->bottom-crn->top);
			TRACE("crw = %d, %d, %d, %d [w= %d, h= %d]\n", crw.left, crw.top, crw.right, crw.bottom, crw.right-crw.left, crw.bottom-crw.top);
			TRACE("crx = %d, %d, %d, %d [w= %d, h= %d]\n", crx.left, crx.top, crx.right, crx.bottom, crx.right-crx.left, crx.bottom-crx.top);
			TRACE("crm = %d, %d, %d, %d [w= %d, h= %d]\n", crm.left, crm.top, crm.right, crm.bottom, crm.right-crm.left, crm.bottom-crm.top);
			ScreenToClient(&crx);
			ScreenToClient(&crm);


			pdc->ExcludeClipRect(&crx);
			pdc->FillSolidRect(&crx, RGB(255,0,0));
			pdc->FillSolidRect(&crm, RGB(0,255,0));

			CWnd::OnNcPaint();

			ReleaseDC(pdc);
			ReleaseDC(pdcw);
			return 0;
#endif	// FIXED_FULL_MENUS

		case WM_GETMINMAXINFO:
			// sent when the size or position of the window is about to change
			// can override default minimum or maximum tracking size.
			LPMINMAXINFO lpmmi;

			lpmmi = (LPMINMAXINFO) lParam; // address of structure
			lpmmi->ptMaxTrackSize.x = nMaxSize.cx;
			lpmmi->ptMaxTrackSize.y = nMaxSize.cy;

			lpmmi->ptMinTrackSize.x = nMaxSize.cx/2;
			lpmmi->ptMinTrackSize.y = nMaxSize.cy/2;
			return 0;

		case WM_SIZE:
		case WM_MOVE:
			if (!gpDO->bFullscreen)	{
				GetClientRect(&rcWindow);
				rcWindowScreen = rcWindow;
				ClientToScreen(&rcWindowScreen);
				ResetMapWindow();
			}
			return 0;

		case WM_ACTIVATEAPP:
			if (wParam)	{		// activated
				ShowWindowsCursor( FALSE );
				gpGame->UnPauseGame( PAUSE_INACTIVE );	// bActive = TRUE;
				if (gpGame->bNeedRestore)	{
					RestoreGame(TRUE);
				}
			}
			else	{			// inactivated
				gpGame->PauseGame( PAUSE_INACTIVE );	// bActive = FALSE;
				if (IsIconic())	{
					gpGame->bNeedRestore = TRUE;
				}
			}
			return 0;

		case WM_ENTERMENULOOP:
			gpGame->PauseGame( PAUSE_MENU );	// bMenuActive = TRUE;
			pMainFrame->PauseFlip();
			DrawMenuBar();
			return 0;

		case WM_EXITMENULOOP:
			gpGame->UnPauseGame( PAUSE_MENU );	// bMenuActive = FALSE;
			pMainFrame->UnPauseFlip();
			return 0;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			return TRUE;

		case WM_PALETTECHANGED:
			if( (HWND)(wParam) == m_hWnd )
				return 0;
			SetPalette(&GamePalette);
			return TRUE;

		case WM_QUERYNEWPALETTE:
			//  we are getting the palette focus, select our palette
			if (current_palette.pDDPalette && pFrontBuffer)	{
				HRESULT ddrval = pFrontBuffer->SetPalette(current_palette.pDDPalette);
				if( ddrval == DDERR_SURFACELOST )	{
					pFrontBuffer->Restore();
					ddrval= pFrontBuffer->SetPalette(current_palette.pDDPalette);
					if( ddrval == DDERR_SURFACELOST )	{
//						TRACE("Failed to restore palette after second try\n");
						bWaitForSurfaceRestore = TRUE;							
					}
				}
			}
			return TRUE;
			break;

		case AVIVID_NOT_STARTED:
		case AVIVID_EJECTED:
			// The AVI clip has been ejected and normal processing can resume
			EraseVisibleSurface();

			// check the current AVI state and see where to go
			MOVIEstateTable[ MovieGetState() ].pTerminateCallback();

//			pMainFrame->UnPauseFlip();
			break;

		case UM_TDG_CREATEPLAYER:
		//	SendPlayerMsg();
			return TRUE;
		
		case UM_TDG_COMM_ERROR:
			BigTimeCommError();
			return TRUE;
		case UM_TDG_NEWHOST:
			{
			int eventnum;
			gpComm->m_bHost  = TRUE;            
			gpGame->GameType = GAMETYPE_HOST_MULTIPLAYER;
 			// This should really probaby bee a call to something like 
			// BeginHostingEvents in Event.cpp  First cut try this:
			if(EventsActive == 1) EventsActive = 2;
			if (gpGame->GetState() == GAME_TITLE_SCREEN_STATE) {
				ScrnSetState( SCRN_MULTI_HOST_STATE );
			}
			gpGame->HostRuleSum =  gpGame->RuleSum;
			if (gpGame->GetSubState() == PLAY_SUB_STATE )
			{
				if (!IsPlaying(ARMY_GREEN)) 
				{
					eventnum=GetControlEventNum("greennotplaying");
					if (eventnum>0)
						EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
				}
				if (!IsPlaying(ARMY_TAN)) 
				{
					eventnum=GetControlEventNum("tannotplaying");
					if (eventnum>0)
						EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
				}
				if (!IsPlaying(ARMY_BLUE)) 
				{
					eventnum=GetControlEventNum("bluenotplaying");
					if (eventnum>0)
						EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
				}
				if (!IsPlaying(ARMY_GRAY)) 
				{
					eventnum=GetControlEventNum("graynotplaying");
					if (eventnum>0)
						EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
				}
			}
			if ( gpGame->GetSubState() == PLAY_SETUP_SUB_STATE) 
				 StartNow();	  //  See if we need to start the game
			return TRUE;
			}
		
		case UM_TDG_DESTROYPLAYER:
			int i,eventnum;
			BOOL weoffedhim;
			if (gpComm->debugComm) TRACE( "DESTROYPLAYER Win Message for player %x\n", wParam);
			if( wParam == 0 || wParam == 0xFFFFFFFF || gpComm->GetColorFromID(wParam) == ARMY_NO_COLOR) return true; // gone already;
			
			if (gpGame->GetState() == GAME_TITLE_SCREEN_STATE) {
				i = gpComm->GetIndexFromID(wParam);
				*(gpComm->m_PlayerName[i]) = '\0';
				weoffedhim = gpComm->RemovePlayer(wParam); 
				// Double check we killed the flowq
				DestroyFlow(wParam);
				if( weoffedhim && gpComm->m_bHost) {
					SendPlayerMsg(TRUE);
					ScrnUpdateHost();
				}
				else
					ScrnUpdateRemote();

				// open up the session
				if (gpComm->m_NumDPPlayers < 4 && gpComm->m_bHost) {
					gpComm->GetSessionDesc();
					LPDPSESSIONDESC2	lpSessionDesc = gpComm->m_pSDesc;
					if(lpSessionDesc ) {
						lpSessionDesc->dwFlags &= ~( DPSESSION_JOINDISABLED | DPSESSION_NEWPLAYERSDISABLED );
						HRESULT hr = gpComm->SetSessionDesc(lpSessionDesc,0);
						if ( FAILED( hr )  )   TRACE("Set Session Failed to reopen Session\n");
					}
				}

				return TRUE;
			}  else  {  // We are in a game  
				if (gpGame->GetSubState() == PLAY_SUB_STATE )
				{
					if (gpComm->GetColorFromID(wParam) == ARMY_GREEN ) {
						eventnum=GetControlEventNum("greennotplaying");
						if (eventnum>0)
							EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
					}
 					if (gpComm->GetColorFromID(wParam) == ARMY_BLUE ) {
						eventnum=GetControlEventNum("bluenotplaying");
						if (eventnum>0)
							EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
					}
 					if (gpComm->GetColorFromID(wParam) == ARMY_TAN ) {
						eventnum=GetControlEventNum("tannotplaying");
						if (eventnum>0)
							EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
					}
 					if (gpComm->GetColorFromID(wParam) == ARMY_GRAY ) {
						eventnum=GetControlEventNum("graynotplaying");
						if (eventnum>0)
							EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
					}
				}
				weoffedhim = gpComm->RemoveActivePlayer(wParam);
				if ( weoffedhim && gpGame->GetSubState() == PLAY_SETUP_SUB_STATE) 
					if (gpComm->m_bHost) StartNow();
			
			}
			return TRUE;

		case UM_TDG_MPSTART:
			if (gpComm->m_bHost ) {
				ASSERT(0);	// this shouldn't happen; this msg should only be recieved by remotes
//				SendGameStartMsg();
			}
			
			if (gpGame->GameType != GAMETYPE_ONEPLAYER ) {
				gpGame->start_game = FALSE;
				SetPath(CAMPAIGN_PATH);
				AiCampaignLoad( "campaign.cpn" );

				// clear the SCREEN state
				ScrnSetState( SCRN_NULL_STATE );

				// clear the front buffer
				EraseVisibleSurface();

				StartGame();
			}
			return TRUE;

		case UM_TDG_PLAYER:	   // RECEIVED notice from host with current players list
			if (gpGame->GameType != GAMETYPE_ONEPLAYER ) {
				SetPath(NULL);
			}
			TRACE("Mainframe received a UM_TDG_PLAYER Windows Message \n");
			return TRUE;

		case UM_TDG_DPLAY:			// One or more messages waiting
			ReceiveMessages();
			return TRUE;

		case WM_SYSCOMMAND:
			switch( wParam )
			{
			case SC_SCREENSAVE:
				return TRUE;
			case SC_MONITORPOWER:
				ShowWindowsCursor(FALSE);
				break;
			}
			break;
	}

	return CFrameWnd::WindowProc(message, wParam, lParam);
}


BOOL CMainFrame::RestoreGame(BOOL InitScreens)
{
	if( pFrontBuffer == NULL )
	{
//        TRACE( "Can't restore FrontBuffer\n" );
        return FALSE;
	}
	if( pFrontBuffer->IsLost() == DDERR_SURFACELOST )		// restores attached backbuffer
	{
		if( pFrontBuffer->Restore() != DD_OK )	
		{
//			TRACE("Can't restore FrontBuffer\n");
			bWaitForSurfaceRestore = TRUE;
			return FALSE;
		}
	}
	if( pTileBuffer == NULL )
	{
		TRACE("Can't restore TileBuffer\n" );
		return FALSE;
	}
	if( pTileBuffer->IsLost() == DDERR_SURFACELOST )
	{
		if( pTileBuffer->Restore() != DD_OK )	
		{
			TRACE("Can't restore TileBuffer\n");
			bWaitForSurfaceRestore = TRUE;
			return FALSE;
		}
	}

	EraseVisibleSurface();

	RestoreTileData();
	RecoverODFSurfaces();
	ScrnForceUpdate();

	if( !SetCurrentPalette() )
		return FALSE;

	gpGame->bNeedRestore = FALSE;
	the_map.redraw = REDRAW_FULL;
	bWaitForSurfaceRestore = FALSE;
	if (InitScreens ) {
		TRACE("RESTORE: \n");
		TRACE ( "gpGame State is %d \n",gpGame->GetState());
		TRACE ( "gpGame type is %d \n",gpGame->GameType);
		TRACE ( "ScrnState  is %d \n", ScrnGetState());
		if ( gpGame->GetState() == GAME_TITLE_SCREEN_STATE) {
			if( gpGame->GameType == GAMETYPE_HOST_MULTIPLAYER )
				ScrnSetState( SCRN_MULTI_HOST_STATE );
			if( gpGame->GameType == GAMETYPE_REMOTE_MULTIPLAYER )
		 		 ScrnSetState( SCRN_MULTI_REMOTE_STATE );
		}
	
	}

    return TRUE;
}


void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	// The system palette has changed
	CFrameWnd::OnPaletteChanged(pFocusWnd);
}


void CMainFrame::OnClose()
{
	gameQuiet();								// turn off all audio as this is a long routine

	gpGame->SetState( GAME_EXIT_PLAY_STATE );	// this does a lot of cleanup
	ScrnSetState( SCRN_NULL_STATE );

	CleanupComm();					// clean-up communication stuff

	AiCampaignFree();

	// exit from fullscreen mode through windowed mode
	if (gpDO->bFullscreen)	{
		gpGame->GraphicsFree();
		dbgTextFree();
		DirectDrawFree();
		gpDO->bFullscreen = FALSE;
		DirectDrawInit();
	}
  
	CFrameWnd::OnClose();
}


void CMainFrame::OnSetFrameTime()
{
	constant_time ^= TRUE;
}

void CMainFrame::OnUpdateSetFrameTime(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(constant_time);
}

void CMainFrame::OnRunWindowed() 
{
	run_windowed ^= TRUE;
}

void CMainFrame::OnUpdateRunWindowed(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(run_windowed);
}

void CMainFrame::OnTemporary()
{
    SetAIMapDisplay(TEMPORARY_MAP);
}

void CMainFrame::OnUpdateTemporary(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(1);
}

//---------------------------------------------------------------------
void CMainFrame::StartGame()	{
	gameStarted = TRUE;

	if (!run_windowed)
		ForceFullScreen();

    UnitMissionInit();
    AIXMissionInit();

	// initialize mission music begin flag
	bMissionMusic = TRUE;
    
	if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
	{
		// is this an initial mission
		if ( ArmyIsFirstMission() || gpGame->newMission )
			gpGame->SetState( GAME_INIT_PLAY_STATE );
		else
		{
			ForceLoadIdentityPalette(the_map.terrain_name);
			gpGame->SetState( GAME_PLAY_STATE );
		}
	}
	else
		gpGame->SetState( GAME_INIT_PLAY_STATE );
//	tracemain = TRUE;
}

int CMainFrame::OnGameSetupDialog() 
{
	int				result  = IDCANCEL;
	BOOL			done    = FALSE;
	CGameSetupDlg	gameSetupDlg;

	ShowTheCursor(FALSE);
	ShowWindowsCursor(TRUE);

	while ( !done )
	{
		result = gameSetupDlg.DoModal();
		if ( result == ID_NEXT )
		{
			result = gameSetupDlg.OnSessionType();
			if ( (result != ID_BACK) && (result != IDD_GAMESETUP) )
				done = TRUE;
		}
		else
			done = TRUE;
	}

	return( result );
}

int CMainFrame::OnServiceProviderDialog() 
{
	int				result;
	BOOL			done = FALSE;
	CProviderDlg	providerDlg;

	ShowTheCursor(FALSE);
	ShowWindowsCursor(TRUE);

	while ( !done )
	{
		result = providerDlg.DoModal();
		if ( result == ID_NEXT )
		{
			result = OnGameSetupDialog();	// try the next dialog box
			if ( result != ID_BACK )
				done = TRUE;
		}
		else
			done = TRUE;
	}

	return( result );
}


int CMainFrame::OnErrorDialog(const char *string, BOOL parentDialog) 
{
	int				result;
	CErrorDialog	errDlg;

	if (!parentDialog)	{
		ShowTheCursor(FALSE);
		ShowWindowsCursor(TRUE);
	}

	errDlg.SetString(string);
	errDlg.Parent(parentDialog);
	result = errDlg.DoModal();

	if (!parentDialog)	{
		ShowTheCursor(TRUE);
		ShowWindowsCursor(FALSE);
	}

	return( result );
}

int CMainFrame::OnErrorDialog2(const char *string, BOOL parentDialog) 
{
	int				result;
	CErrorDialog2	errDlg;

	if (!parentDialog)	{
		ShowTheCursor(FALSE);
		ShowWindowsCursor(TRUE);
	}

	errDlg.SetString(string);
	errDlg.Parent(parentDialog);
	result = errDlg.DoModal();

	if (!parentDialog)	{
		ShowTheCursor(TRUE);
		ShowWindowsCursor(FALSE);
	}

	return( result );
}

void CMainFrame::OnTimer(UINT nTimerID)	 
{
	if( nTimerID != m_EventTimerID) return;
    ScrnRedoPlayerNames ( );
}






//---------------------------------------------------------------------

void CMainFrame::OnAvenue() 
{
    SetAIMapDisplay(NO_MAP);
}

void CMainFrame::OnUpdateAvenue(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(1);	
}

void CMainFrame::OnContour() 
{
    SetAIMapDisplay(CONTOUR_MAP);
}

void CMainFrame::OnUpdateContour(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(1);	
}

void CMainFrame::OnCommander() 
{
}

void CMainFrame::OnUpdateCommander(CCmdUI* pCmdUI) 
{
}

void CMainFrame::OnFakeunits() 
{
   validate = 1;
}

void CMainFrame::OnUpdateFakeunits(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(validate);
}

void CMainFrame::OnMusicToggle() 
{
	gpGame->MusicToggle();
}

void CMainFrame::OnSfxToggle() 
{
	gpGame->SfxToggle();
}

/*void CMainFrame::OnGamePauseToggle() 
{
	if ( gpGame->IsPaused() & PAUSE_LOCAL ) {
		SendGamePause(FALSE, PAUSE_LOCAL);  // Toggle Remote Pause 
		gpGame->UnPauseGame( PAUSE_LOCAL );
	}
	else
	{
		// set the local pause
		gpGame->PauseGame( PAUSE_LOCAL );

		// now send the remote pause
		SendGamePause(TRUE, PAUSE_LOCAL);
	}
}
*/

//---------------------------------------------------------------------
//	NEW Menu Choices
//---------------------------------------------------------------------

void CMainFrame::OnBothai() 
{
}

void CMainFrame::OnUpdateBothai(CCmdUI* pCmdUI) 
{
}

void CMainFrame::OnRouting() 
{
    ++routingDraw;
    if (routingDraw == 3) routingDraw = 0;
}

void CMainFrame::OnUpdateRouting(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(routingDraw);
}

void CMainFrame::OnSingletrooper() 
{
	unitBehavior = TRUE;
}

void CMainFrame::OnUpdateSingletrooper(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(1);
}

void CMainFrame::OnRandom() 
{
    randomize = !randomize;
	constant_time = !randomize;
}

void CMainFrame::OnUpdateRandom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(randomize);
	pCmdUI->Enable(!gameStarted);
}

BOOL CMainFrame::IsMultiPlayer() 
{
	return( gpGame->GameType != GAMETYPE_ONEPLAYER );
}

void CMainFrame::OnPads() 
{
    SetAIMapDisplay(PAD_MAP);	
}

void CMainFrame::OnUpdatePads(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(1);
}

void CMainFrame::OnBitpads() 
{
    SetAIMapDisplay(BIT_PAD_MAP);	
}

void CMainFrame::OnUpdateBitpads(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(1);
}

void CMainFrame::OnFog() 
{
}

void CMainFrame::OnUpdateFog(CCmdUI* pCmdUI) 
{
}

void CMainFrame::OnBw01() 
{
	SetAIMapDisplay(ELEVATION_MAP);
}

void CMainFrame::OnBw02() 
{
	SetAIMapDisplay(VIS_MAP);
}

void CMainFrame::OnScriptdebug() 
{
    scriptDebug = !scriptDebug;
}

void CMainFrame::OnUpdateScriptdebug(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(scriptDebug);
}

void CMainFrame::OnAllScenariosVisible() 
{
	if ( m_bScenariosVisible )
	{
		// turn off visibiliy
		m_bScenariosVisible = FALSE;

		// reset the visibility flags to those in the .ASF file
		StatLoadCompletedMissions();
	}
	else
	{
		// turn on the visibility of everything in the g_Campaigns data
		StatMakeAllVisible();

		// turn on visibiliy
		m_bScenariosVisible = TRUE;
	}
}

void CMainFrame::OnLabel() 
{
    ++labelForces;
    if (labelForces == 3) labelForces = 0;
}

void CMainFrame::OnUpdateLabel(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(labelForces);	
}

void CMainFrame::OnBw1() 
{
    bw1 = !bw1;
	sargeImmune = !sargeImmune;// safe
    routingDraw = (bw1) ? 2 : 0; // how they go
    labelForces =  (bw1) ? 1 : 0; // who is who internal
    Allah =  (bw1) ? 1 : 0; // god view
    SetAIMapDisplay(TEMPORARY_MAP); // what is the terrain
	pMainFrame->OnAllScenariosVisible();	// toggle all 1st missions visible
}

void CMainFrame::OnUpdateBw1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bw1);		
}

void CMainFrame::OnBw2() 
{
    bw2 = !bw2;	
}

void CMainFrame::OnUpdateBw2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bw2);	
}

void CMainFrame::OnBw3() 
{
    immobileFoe = !immobileFoe;	
}

void CMainFrame::OnUpdateBw3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(immobileFoe);		
}

void CMainFrame::OnBw4() 
{
    bw4 = !bw4;
}

void CMainFrame::OnUpdateBw4(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bw4);			
}

#ifndef FINAL
	extern BOOL no_cd_ok;
#endif

void CMainFrame::OnNoCdOk() 
{
#ifndef FINAL
   no_cd_ok = !no_cd_ok;
#endif
}

void CMainFrame::OnUpdateNoCdOk(CCmdUI* pCmdUI) 
{
#ifndef FINAL
	pCmdUI->SetCheck(no_cd_ok);				
#endif
}

void CMainFrame::UpdateView() 
{
	ScrnForceUpdate();
	ScrnDoDisplay();
}

//---------------------------------------------------------------------
//								EOF
//---------------------------------------------------------------------
