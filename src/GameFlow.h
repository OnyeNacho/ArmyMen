//========================================================================
//	FILE:			$Workfile: GameFlow.h $
//
//	DESCRIPTION:	Game flow header file.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		Wednesday, December 4th, 1996
//
//	REVISION:		$Header: /ArmyMen/src/GameFlow.h 58    4/14/98 12:59p Nrobinso $
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
//  $Log: /ArmyMen/src/GameFlow.h $
//  
//  58    4/14/98 12:59p Nrobinso
//  add MissionTime to game struct
//  
//  57    4/13/98 1:38p Nrobinso
//  start audio once briefing is drawn
//  
//  56    4/09/98 4:32p Nrobinso
//  
//  54    3/30/98 11:45a Bwilcox
//  added oneplayermode
//  
//  53    3/26/98 1:35p Dmaynard
//  Added Checksumming of all Script files listed in the rule file
//  
//  52    3/26/98 11:56a Bwilcox
//  storing if it is a capture-the-flag type game
//  
//  51    3/24/98 12:11p Nrobinso
//  remove unused
//  
//  50    3/23/98 12:16p Aburgess
//  new music setup prototypes
//  
//  49    3/19/98 11:21p Nrobinso
//  
//  48    3/19/98 7:50p Nrobinso
//  change pause flags
//  
//  47    3/17/98 4:42p Dmaynard
//  Added PAUSE_MAPLOAD instead of piggy-backing on the normal PAUSE_LOCAL
//  flags.
//  
//  46    3/09/98 11:32a Nrobinso
//  remove statement state; add cdboot flag
//  
//  45    2/20/98 4:26p Aburgess
//  added debug info routines
//  
//  44    2/19/98 2:55p Aburgess
//  modifications made to support BAD Map detection in remote players.
//  Added checks for BootCamp game play mode.
//  
//  43    2/16/98 9:30a Nrobinso
//  make checksum unsigned longs
//  
//  42    2/10/98 2:58p Dmaynard
//  Split Pause flag PAUSE_REMOTEGONE into separate Pause flags for each
//  remote machine.
//  
//  41    2/07/98 6:07p Nrobinso
//  multiple maps may share a rule file for multiplayer; remote display bug
//  remains
//  
//  40    2/01/98 10:58p Nrobinso
//  removed old dialog code
//  
//  39    1/28/98 10:19a Aburgess
//  modifications made to support game start MISSION recall. Support for
//  successive missions has not been implemented yet and will still display
//  the old MISSION STATEMENT interface. Additionally, access directly to
//  the HOST and REMOTE campaign select screens now occurs if in a lobby
//  session.
//  
//  38    1/27/98 4:13p Phu
//  measure memory + processor speed
//  
//  37    1/26/98 12:58p Aburgess
//  modifications made to support the new mission briefing screens
//  
//  36    1/24/98 3:35p Aburgess
//  modifications made to support Recall Mission and Full screen Map
//  
//  35    1/22/98 12:01p Nrobinso
//  add map checksum
//  
//  34    1/21/98 12:05p Aburgess
//  selective disabling of audio
//  
//  33    12/10/97 9:45a Aburgess
//  changes made to incorporate first pass of PLAY_OPTIONS screen
//  
//  32    12/09/97 12:12p Phu
//  
//  31    12/07/97 6:22p Aburgess
//  added WinningArmy
//  
//  30    12/05/97 1:06p Nrobinso
//  add newMission
//  
//  29    12/04/97 6:52p Nrobinso
//  remove Bein & End Mission routines
//  
//  28    12/04/97 4:19p Nrobinso
//  add setup substate
//  
//  27    12/01/97 9:47a Aburgess
//  removed audiotest references. Added STATEMENT substate
//  
//  26    11/26/97 2:27p Aburgess
//  modifications made to support MultiPlayer Campaign Select
//  
//  25    11/21/97 9:11a Aburgess
//  added MissionMusic prototype
//  
//  24    11/20/97 11:47a Aburgess
//  rework of game states and substates
//  
//  23    11/17/97 4:46p Aburgess
//  added haveplayed class member
//  
//  22    11/14/97 11:18a Aburgess
//  added voice toggle
//  
//  21    11/14/97 10:34a Nrobinso
//  rearrange setup/cleanup code
//  
//  20    11/12/97 4:01p Dmaynard
//  Added Remote Pause mechanism for Multi-Payer mode
//  
//  19    11/11/97 8:46a Aburgess
//  added MissionStatement prototype
//  
//  18    11/07/97 10:40a Aburgess
//  substate prototypes and modifications
//  
//  17    10/28/97 10:09a Awerner
//  The chat toggle buttons should now work
//  
//  16    10/27/97 11:25a Aburgess
//  added mission data
//  
//  15    10/20/97 5:28p Nrobinso
//  add MissionDone
//  
//  14    10/20/97 4:27p Awerner
//  Fixed crashing bug on mission victory
//  
//  13    10/16/97 1:08p Nrobinso
//  removed StartGame
//  
//  12    10/07/97 8:23a Aburgess
//  Added test page flip freeze
//  
//  10    9/11/97 6:09p Awerner
//  Added an opening and closing gate (on playable10)
//  
//  9     8/19/97 2:42p Phu
//  Title Fix
//  
//  8     8/17/97 6:09p Nrobinso
//  cleanup pause code
//  
//  7     8/14/97 5:40p Nrobinso
//  audio updates
//  
//  6     8/06/97 2:07p Nrobinso
//  remove game levels
//  
//  5     7/25/97 2:35p Awerner
//  The game startup now works properly in one-player mode
//  
//  4     7/25/97 1:39p Nrobinso
//  have a start_game variable during which the strat map is displayed and
//  no action occurs
//  
//  3     7/17/97 9:04p Nrobinso
//  keep SysTime and AnimTime separate. AnimTime only allows a max time
//  differential between frames
//  
//  2     7/14/97 7:07p Nrobinso
//  removed mainbase
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  18    5/31/97 7:30p Bwilcox
//  added playCycle
//  
//  17    5/15/97 8:05p Nrobinso
//  add a delayed state set (SetNextState), clear screen when starting
//  game, start the music in connect state
//  
//  16    5/09/97 2:07p Dmaynard
//  Added B_PAUSEDREMOTEGONE to prevent us from sending msgs when we are
//  not receiving any messages from opposing player.
//  
//  15    5/08/97 7:30p Dbunch
//  Added Avi player code
//  
//  14    5/06/97 9:30a Bwilcox
//  added SendChatMessageTo
//  
//  13    4/25/97 3:38p Nrobinso
//  chat message hooks
//  
//  12    4/23/97 7:31p Nrobinso
//  added B_PAUSE_CONNECT pause state; go into this pause state in
//  CONNECT_STATE to turn off mouse being grabbed, and turn off page
//  flipping
//  
//  11    4/23/97 2:13p Nrobinso
//  remove error state, add connect state;  Load army graphics before
//  scenario load
//  
//  10    3/17/97 11:49a Nrobinso
//  added GAME_EXIT_PLAY state for take down of game state; put the game
//  play init code into GAME_INIT_PLAY_STATE; added display list display
//  
//  9     1/17/97 3:49p Aburgess
//  added bits and masks for Pause
//  
//  8     97-01-16 15:37 Ereich
//  Added SUserInterface support and I have test it for each of the states
//  for the mouse input.  Next is keyboard input.
//  
//  7     97-01-16 10:21 Ereich
//  Finally got the new state machine working.  Subtleties in the
//  transition from the old state to the new cost me many hours.
//  
//  6     97-01-14 9:54 Ereich
//  Next to last version before clean-up is complete.
//  
//  5     97-01-10 16:34 Ereich
//  A good check-in point for code clean-up...
//  
//  4     97-01-10 10:00 Ereich
//  Day 2 house cleaning done...
//  
//  3     97-01-09 9:45 Ereich
//  Clean-up day 2 is now complete on day 3...  I love meetings!
//  
//  2     97-01-07 16:02 Ereich
//  Cleaning house day 1.  I have made many changes to most of the files
//  and it seems to still work.  So I thought I would check-it in and
//  continue tomorrow.
//  
//  1     96-12-13 11:36 Ereich
//  Oops! Sorry I forgot to add this before...
//  
//  $Nokeywords:$
//=========================================================================

#ifndef __GAMEFLOW_H__
#define __GAMEFLOW_H__

#ifdef _DEBUG
#define ODS( a ) OutputDebugString( a )
#else
#define ODS( a )
#endif

//=========================================================================
//						GLOBAL DEFINES
//=========================================================================

#define	LOSER	0
#define	WINNER	1


//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================

#define GAMERESULT_NONE 0
#define GAMERESULT_YOUWIN 1
#define GAMERESULT_YOULOSE 2

#define	GAMETYPE_ONEPLAYER			0
#define	GAMETYPE_HOST_MULTIPLAYER	1
#define	GAMETYPE_REMOTE_MULTIPLAYER	2


// Game States
typedef	enum
{
// KEEP THIS IN SYNC WITH StateChanges[]...
	GAME_NULL_STATE = 0,		// null or undefined state

	GAME_INIT_STATE,			// game initialization state
	GAME_MOVIE_STATE,			// play into movie state
	GAME_TITLE_SCREEN_STATE,	// title screen state
	GAME_INIT_PLAY_STATE,		// play mode initialization state
	GAME_PLAY_STATE,			// play mode game processing
	GAME_EXIT_PLAY_STATE,			// play mode shutdown state

	GAME_TEST_STATE,			// DEBUG
	GAME_TOTAL					// total number of states
} GAME_STATE;

typedef struct SGameState {
#ifndef FINAL
	GAME_STATE	identity;					// for debugging helps make sure StateChanges[] stays sync'd with GAME_STATE
	char	*pName;							// state's name as a character string
#endif	//ndef FINAL

	void	(*pNew)(GAME_STATE gameState);	// new state handler
	void	(*pOld)(GAME_STATE gameState);	// old state handler

	BOOL	(*pGLd)();						// graphics load handler
	void	(*pDsp)();						// display handler
	void	(*pAct)();						// action handler
} SGameState;

#ifndef FINAL
#define GAME_STATE_AUTO(s)				{ s, #s, New_##s, Old_##s, GLd_##s, Dsp_##s, Act_##s }
#define GAME_STATE_MAN(s,n,o,g,d,a)		{ s, #s, New_##n, Old_##o, GLd_##g, Dsp_##d, Act_##a }
#define GAME_STATE_MAN1(s,n,o,g,d,a)	{ s, #s, n, o, g, d, a }
#else	//ndef FINAL

#define GAME_STATE_AUTO(s)				{ New_##s, Old_##s, GLd_##s, Dsp_##s, Act_##s }
#define	GAME_STATE_MAN(s,n,o,g,d,a)		{ New_##n, Old_##o, GLd_##g, Dsp_##d, Act_##a }
#define GAME_STATE_MAN1(s,n,o,g,d,a)	{ n, o, g, d, a }
#endif	//ndef FINAL


typedef enum
{
	NULL_SUB_STATE = 0,
	PLAY_SUB_STATE,
	PLAY_SETUP_SUB_STATE,
	PLAY_OPTIONS_SUB_STATE,
	STAT_SUB_STATE,

	// nothing below this point
	LAST_SUB_STATE
} GAME_SUBSTATE;


// Pause flags
typedef enum
{
	B_PAUSE_INACTIVE,			// application is inactive
	B_PAUSE_MENU,				// game menu is pulled down
	B_PAUSE_DIALOG,				// a dialog box is active

	B_PAUSE_LOCAL,				// local user requests pause
	B_PAUSE_REMOTE1,				// remote machine 1 requests pause
	B_PAUSE_REMOTE2,				// remote machine 2 requests pause
	B_PAUSE_REMOTE3,				// remote machine 3 requests pause

	B_PAUSE_INIT,				// pause caused by initialization of a state

	B_PAUSE_TITLE,				// pause caused by being in title screen
	B_PAUSE_MOVIE,				// pause caused by being in title screen

	B_PAUSE_REMOTEGONE1,			// pause caused by receiving nothing from remote machine
	B_PAUSE_REMOTEGONE2,			// pause caused by receiving nothing from remote machine
	B_PAUSE_REMOTEGONE3,			// pause caused by receiving nothing from remote machine

	B_PAUSE_FLOW,					// FLOW CONTROL  invoked when free message pool runs low
	B_PAUSE_MAPLOAD,				// currently loading a Map
	B_PAUSE_MAPLOAD1,				// Army1 currently loading a Map
	B_PAUSE_MAPLOAD2,				// Army2 currently loading a Map
	B_PAUSE_MAPLOAD3,				// Army3 currently loading a Map

	B_PAUSE_TOTAL				// total number of pause flags
} PAUSE_FLAGS;

#define PAUSE_INACTIVE		(1<<B_PAUSE_INACTIVE)
#define PAUSE_MENU			(1<<B_PAUSE_MENU)
#define PAUSE_DIALOG		(1<<B_PAUSE_DIALOG)
#define PAUSE_LOCAL			(1<<B_PAUSE_LOCAL)
#define PAUSE_REMOTE1		(1<<B_PAUSE_REMOTE1)
#define PAUSE_REMOTE2		(1<<B_PAUSE_REMOTE2)
#define PAUSE_REMOTE3		(1<<B_PAUSE_REMOTE3)
#define PAUSE_INIT			(1<<B_PAUSE_INIT)
#define PAUSE_TITLE			(1<<B_PAUSE_TITLE)
#define PAUSE_MOVIE			(1<<B_PAUSE_MOVIE)
#define PAUSE_REMOTEGONE1	(1<<B_PAUSE_REMOTEGONE1)
#define PAUSE_REMOTEGONE2	(1<<B_PAUSE_REMOTEGONE2)
#define PAUSE_REMOTEGONE3	(1<<B_PAUSE_REMOTEGONE3)
#define PAUSE_FLOW			(1<<B_PAUSE_FLOW)
#define PAUSE_MAPLOAD		(1<<B_PAUSE_MAPLOAD)
#define PAUSE_MAPLOAD1		(1<<B_PAUSE_MAPLOAD1)
#define PAUSE_MAPLOAD2		(1<<B_PAUSE_MAPLOAD2)
#define PAUSE_MAPLOAD3		(1<<B_PAUSE_MAPLOAD3)

#define ALL_PAUSE	( PAUSE_INACTIVE | PAUSE_MENU | PAUSE_DIALOG | PAUSE_MOVIE | PAUSE_TITLE )
#define MAP_PAUSE	( PAUSE_MAPLOAD | PAUSE_MAPLOAD1 | PAUSE_MAPLOAD2 | PAUSE_MAPLOAD3 )

class CGame {
	// private member variables
private:
	GAME_STATE	eGameState;		// current game state
	GAME_STATE	ePrevState;		// previous game state

	DWORD		m_PauseFlags;	// The pause flags

	BOOL		(*m_GrLoad)();	// state specific graphics loading function pointer
	void		(*m_Display)();	// state specific display function pointer
	void		(*m_Action)();	// state specific action function pointer


	// protected member variables
protected:
	// public member variables
public:
	BOOL bNeedRestore;						// display needs to be restored
	BOOL start_game;						// begin game mode, wait on other players
	BOOL winner;							// did player win the mission
	BOOL Music;								// Music Off/On
	BOOL Voice;								// Voice Off/On
	BOOL Sfx;								// Sfx Off/On
	BOOL HavePlayed;						// have played before
	int	 nPauseDelay;						// pause delay counter

	GAME_SUBSTATE game_substate;			// state within game play
	GAME_SUBSTATE previous_game_substate;	// previous state within game play

	DWORD dwSysTime;						// current system time
	DWORD dwAnimTime;						// current time, minus pauses
	DWORD dwMissionTime;					// time since beginning of mission
	DWORD dwDeltaTime;						// time since previous timer callback
	DWORD gChatTimer;						// Chat count-down timer...

	CString MapName;
	unsigned long	MapSum;					// checksum
	CString RuleName;
	DWORD			RuleSum;				// All scripts checksum
	DWORD			HostRuleSum;			// All scripts checksum from Host
	int		GameType;						// one or multi player
	int		CampaignID;						// current campaign ID for this map
	int		ScenarioID;						// current scenario ID for this map
	int		MissionID;						// current mission ID for this map
	BOOL	newMission;
	int		WinningArmy;					// index of winning player Army
	BOOL	BootCamp;						// is this a Boot Camp Mission
    BOOL	CaptureFlag;					// a capture multiplayer game?
    BOOL	oneplayerMode;					// a 1-user multiplayer game?

	BOOL	LowMemoryMachine;
	BOOL	SlowMachine;
	BOOL	cdBoot;

	// private methods
private:
	// protected methods
protected:
	// public methods
public:
	CGame(void);						// default constructor
	~CGame();							// destructor

#ifndef FINAL
	void SaveSingle();
	void SaveSeriesOn();
	void SaveSeriesOff();
#endif	//ndef FINAL

	// Music, Voice, and SFX
	void MusicToggle(void);
	void VoiceToggle(void);
	void SfxToggle(void);

	// m_PauseFlags access methods
	DWORD PauseGame(DWORD mask);		//	PauseGame = set pause bits with a 1 in each bit position to pause.
	DWORD UnPauseGame(DWORD mask);		//	UnPauseGame = clear pause bits with a 1 in each bit position to pause.
	DWORD IsPaused();					//	IsPaused = returns the pause flags.
	void  (*m_DelayFunc)(int nData);	// function to exectute when delay timer terminates

	void GameDisplay();
	void GameAction();

	void ChatTimer(void);

	void SetState(GAME_STATE gameState);
	GAME_STATE GetState(void);
	GAME_STATE PrevState(void);


	void			SetSubState(GAME_SUBSTATE subState);
	GAME_SUBSTATE	GetSubState(void);
	GAME_SUBSTATE	PrevSubState(void);


	void GraphicsFree();
	BOOL GraphicsLoad();
};


//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================

extern	int		gameresult;						// set this to make a player win or lose
extern	CGame	gGame, *gpGame;					// game object and pointer
extern	long	playCycle;						// which pass thru play loop
extern	BOOL	bDisplayRecall;
extern	BOOL	bAudioRecall;
extern	char	bDisplayPaperMap;

//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================

void LaunchGame(void);

extern void	New_GAME_NULL_STATE(GAME_STATE gameState);				// null or undefined state
extern void	Old_GAME_NULL_STATE(GAME_STATE gameState);				// null or undefined state
extern BOOL	GLd_GAME_NULL_STATE();									// null or undefined state
extern void	Dsp_GAME_NULL_STATE();									// null or undefined state
extern void	Act_GAME_NULL_STATE();									// null or undefined state

extern void New_GAME_INIT_STATE(GAME_STATE gameState);				// game initialization state
extern void Old_GAME_INIT_STATE(GAME_STATE gameState);				// game initialization state
extern BOOL GLd_GAME_INIT_STATE();									// game initialization state
extern void Dsp_GAME_INIT_STATE();									// game initialization state
extern void Act_GAME_INIT_STATE();									// game initialization state

extern void New_GAME_INIT_PLAY_STATE(GAME_STATE gameState);			// play mode initialization processing
extern void Old_GAME_INIT_PLAY_STATE(GAME_STATE gameState);			// play mode initialization processing
extern BOOL GLd_GAME_INIT_PLAY_STATE();								// play mode initialization processing
extern void Free_GAME_INIT_PLAY_STATE();
extern void Dsp_GAME_INIT_PLAY_STATE();								// play mode initialization processing
extern void Act_GAME_INIT_PLAY_STATE();								// play mode initialization processing

extern void New_GAME_EXIT_PLAY_STATE(GAME_STATE gameState);			// play mode exit processing
extern void Old_GAME_EXIT_PLAY_STATE(GAME_STATE gameState);			// play mode exit processing
extern BOOL GLd_GAME_EXIT_PLAY_STATE();								// play mode exit processing
extern void Dsp_GAME_EXIT_PLAY_STATE();								// play mode exit processing
extern void Act_GAME_EXIT_PLAY_STATE();								// play mode exit processing

extern void New_GAME_PLAY_STATE(GAME_STATE gameState);				// play mode game processing
extern void Old_GAME_PLAY_STATE(GAME_STATE gameState);				// play mode game processing
extern BOOL GLd_GAME_PLAY_STATE();									// play mode game processing
extern void Dsp_GAME_PLAY_STATE();									// play mode game processing
extern void Act_GAME_PLAY_STATE();									// play mode game processing

extern void New_GAME_AUDIO_TEST_STATE(GAME_STATE gameState);		// audio testing state
extern void Old_GAME_AUDIO_TEST_STATE(GAME_STATE gameState);		// audio testing state
extern BOOL GLd_GAME_AUDIO_TEST_STATE();							// audio testing state
extern void Dsp_GAME_AUDIO_TEST_STATE();							// audio testing state
extern void Act_GAME_AUDIO_TEST_STATE();							// audio testing state

extern void New_GAME_TOTAL(GAME_STATE gameState);					// total number of states
extern void Old_GAME_TOTAL(GAME_STATE gameState);					// total number of states
extern BOOL GLd_GAME_TOTAL();										// total number of states
extern void Dsp_GAME_TOTAL();										// total number of states
extern void Act_GAME_TOTAL();										// total number of states

extern void New_GAME_MOVIE_STATE(GAME_STATE gameState);
extern void Old_GAME_MOVIE_STATE(GAME_STATE gameState);
extern BOOL GLd_GAME_MOVIE_STATE();
extern void Dsp_GAME_MOVIE_STATE();
extern void Act_GAME_MOVIE_STATE();

extern void SendChatMessage(char *msg);
extern void SendChatMessageTo(char *msg,int whoTo);
extern void SendChatMessageToPlayer(char *msg, int whichplayer);

extern void	GameOver( BOOL bWinner );
extern void MissionDone( int eArmyWon );
extern void TitleMusic( BOOL bStop );
extern void CampaignMusic( BOOL bStop );
extern void MissionMusic( BOOL bStop );

extern void	gameQuiet( void );
extern void	gameNoisy( void );
extern int ProcessPauses( void );

extern char* GetStateName( GAME_STATE game_state );
extern char* GetSubStateName( GAME_SUBSTATE game_sub_state );

#endif		// __GAMEFLOW_H__
//=========================================================================
//								EOF
//=========================================================================
