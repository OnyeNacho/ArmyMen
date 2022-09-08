//========================================================================
//	FILE:			$Workfile: Screen.h $
//
//	DESCRIPTION:	ArmyMen Button Class definition.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Sunday, October 19, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Screen.h 45    4/14/98 2:53a Aburgess $
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
//  $Log: /ArmyMen/src/Screen.h $
//  
//  45    4/14/98 2:53a Aburgess
//  forcing proper date in checkin
//  
//  44    4/15/98 2:50a Aburgess
//  modified Bad Map notifications to init and Map selection.  Also reduced
//  number of sendplayermsg calls during scrolling of campaign selection
//  area in MULTIPLAYER
//  
//  43    4/09/98 12:31p Nrobinso
//  fix the cursor left behind in dialogs; make sure we are seeing the gdi
//  surface for dialogs
//  
//  42    4/03/98 6:05p Aburgess
//  modifications made to correct Joystick Configuration BACK/RESTORE bugs
//  
//  40    3/25/98 3:27p Aburgess
//  made ScrnPlayerName global
//  
//  39    3/17/98 11:20a Aburgess
//  added func parameter and return code
//  
//  38    3/16/98 12:31a Nrobinso
//  remove unused
//  
//  37    3/13/98 11:40a Nrobinso
//  simplify stats state
//  
//  36    3/13/98 10:39a Dmaynard
//  Added Windows Timer Messages to repaint Player names so that their
//  colors can reflect latency to that player. Green==low yellow==medium
//  red== high.
//  
//  35    3/11/98 11:26a Aburgess
//  modifications made to support new colorization of menus based on player
//  army color
//  
//  34    3/09/98 11:36a Nrobinso
//  remove statement state
//  
//  33    3/09/98 10:42a Aburgess
//  ABOUT screens and other modifications
//  
//  32    3/09/98 9:55a Aburgess
//  new about screens
//  
//  31    3/08/98 10:12p Nrobinso
//  more cleanup
//  
//  30    3/08/98 8:15p Nrobinso
//  collapse termiantion routines; diable joystick option if you don't have
//  one attached
//  
//  29    3/02/98 12:14p Aburgess
//  modifications made to support the ESC key in both non-gameplay and
//  gameplay modes.
//  
//  28    2/26/98 2:26p Aburgess
//  modifiations made to properly process the ESC key in mission recall and
//  map screens
//  
//  27    2/25/98 11:47a Aburgess
//  modifications made to correct user configuration bugs
//  
//  26    2/20/98 4:30p Aburgess
//  made ScrnGetStateName global for debug
//  
//  25    2/12/98 4:17p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  24    2/11/98 7:50p Nrobinso
//  remove yes/no; add end multiplayer screen
//  
//  23    2/06/98 7:20a Aburgess
//  modifications made to support the CUSTOM configuration screen
//  
//  22    2/05/98 9:49a Aburgess
//  modifications made to support the OPTIONS screens (config, abort
//  mission and audio) during game play mode.
//  
//  21    2/01/98 4:31p Aburgess
//  modifications made to support new ART and maps files
//  
//  20    1/26/98 12:58p Aburgess
//  modifications made to support the new mission briefing screens
//  
//  19    1/23/98 9:38a Aburgess
//  modifications made to support new multiplayer screens
//  
//  18    1/21/98 11:50a Nrobinso
//  extern replay yes/no functions
//  
//  17    1/21/98 11:24a Aburgess
//  modifications made to support <RETURN>, <Y>, and <N> keys in stat
//  screens
//  
//  16    1/14/98 2:16p Aburgess
//  modifications made to support GAME_PLAY Options screens
//  
//  15    1/09/98 8:42a Aburgess
//  added ScrnReload prototype
//  
//  14    12/23/97 11:31a Aburgess
//  title screen update prototype
//  
//  13    12/18/97 1:18p Aburgess
//  New Audio and User Configuration screens. New Scrolling buttons and
//  Slider bars
//  
//  12    12/10/97 9:46a Aburgess
//  changes made to centralize REGKEY access and incorporate first pass of
//  PLAY_OPTIONS screen
//  
//  11    12/09/97 1:06p Aburgess
//  corrected compile time errors
//  
//  10    12/09/97 12:52p Aburgess
//  ScrnEnd...,ScrnInit...,StatementEnd...,StatementInit...
//  changed to ScrnStat... and ScrnStatement
//  
//  9     12/09/97 12:12p Phu
//  
//  8     12/06/97 4:16p Aburgess
//  changes made to support chat in multiplayer screens
//  
//  7     12/01/97 4:49p Aburgess
//  applied max limit on number of multiplayer maps
//  
//  6     12/01/97 1:27p Aburgess
//  replaced prototypes
//  
//  5     12/01/97 9:55a Aburgess
//  update of SCREEN processing
//  
//  4     11/26/97 2:27p Aburgess
//  modifications made to support MultiPlayer Campaign Select
//  
//  3     11/07/97 10:42a Aburgess
//  New Full Screen UI interfaces
//  
//  2     10/27/97 10:57a Aburgess
//  Pass 1 of the new FULL SCREEN UI interface and data
//  
//  1     10/27/97 10:25a Aburgess
//  FullScreen UI Screen interface
//  
//  $Nokeywords:$
//========================================================================

//------------------------------------------------------------------------
//				DEPENDENCIES
//------------------------------------------------------------------------
#include "ScreenObj.h"

//========================================================================
// What is a SCREEN?
//
//========================================================================

//------------------------------------------------------------------------
//				GENERAL SCREEN DEFINES
//------------------------------------------------------------------------
#define	SCRN_MAX_NAME_LEN	32
#define	SCRN_MAX_TEXT_LEN	64
#define	SCRN_MAX_REF_LEN	64

#define	SCRN_MAX_RULE_FILES	48
#define	SCRN_MAX_OBJS		72
#define	SCRN_MAX_SCENARIOS	4
#define	SCRN_PLAYER_NAMES	4
#define	SCRN_VALUE_SIZE		5

//------------------------------------------------------------------------
//				SCREEN ATTRIBUTES
//------------------------------------------------------------------------

#define	SCRN_CLEAR			(USHORT)(0x0000)	// all attributes cleared
#define	SCRN_BKG_TYPE		(USHORT)(0x0001)	// screen has a BLG image
#define	SCRN_AREA_TYPE		(USHORT)(0x0002)	// screen has a BLG image
#define	SCRN_TRANSPARENT	(USHORT)(0x0004)	// screen bkg is transparent
#define	SCRN_ISYESNO		(USHORT)(0x0008)	// screen has YES-NO buttons

// configuration values
#define	SARGE_KEY_START_INDEX		3
#define	JOYSTICK_BUTTON_START_INDEX	3
#define	SARGE_KEY_END_INDEX			34
#define	GAME_KEY_START_INDEX		35
#define	JOYSTICK_MAX_OBJS			37
#define	GAME_KEY_END_INDEX			66
#define	DEFAULT_LAST_KEY			68
#define	CUSTOM_LAST_KEY				69

//------------------------------------------------------------------------
//				TIMER defines for updating player names for latency
//------------------------------------------------------------------------
#define	NameUpdateTimer 7
#define NameUpdateTime 1000
//------------------------------------------------------------------------
//				SCREEN STRUCTURE
//------------------------------------------------------------------------
typedef	SOBJ_COLOR	SCRN_COLOR;

typedef	enum
{
	CONFIG_DEFAULT1 = 0,
	CONFIG_DEFAULT2,
	CONFIG_CUSTOM,
	CONFIG_JOYSTICK
} CONFIG;

typedef struct	fullScreen
{
	// Status structure
	USHORT		bAttributes;		// button attributes
	SCRN_STATE	eState;
	SCRN_STATE	ePrevState;
	SCRN_COLOR	eBGColor;
	BOOL		bUpdate;
	BOOL		dialog;

	// Presentation structure
	SPOINT		position;
	char		BkgRef[SCRN_MAX_REF_LEN+1];
	SPRITE*		pBkgSprite;
	SBOX		BkgBox;

	int			nNumberObjs;				// screen number of objects
	SCREENOBJ*	pScreenObjs[SCRN_MAX_OBJS+1];// screen list of pointers to screenObjs

} SCREEN;

typedef SCREEN*	HSCREEN;

typedef	struct	scrnDef
{
	ULONG			bAttributes;					// screen Attributes
	SPOINT			position;						// screen position of screenobj
	SCRN_COLOR		eBGColor;
	SBOX			bkgBox;							// screen bkg box and size
	char			bkgRef[SCRN_MAX_REF_LEN+1];		// screen bkg resource/filename reference
	int				nNumberObjs;					// screen number of objects
	SCREENOBJDEF*	pScreenObjDefs[SCRN_MAX_OBJS+1];// screen list of pointers to screenObjDefs

} SCREENDEF;

typedef	struct	scrnStateTable
{
	SCRN_STATE	eScrnState;
	LONG		((*pInitCallback)(struct fullScreen** pScreen));		// Screen state initialization callback
	LONG		((*pDisplayCallback)(struct fullScreen* pScreen));	// Screen state display callback
	LONG		((*pUpdateCallback)(struct fullScreen* pScreen));	// Screen state update callback
	LONG		((*pTerminateCallback)(struct fullScreen** pScreen));// Screen state termination callback
} SCREENSTATES;

//========================================================================
//						PROTOTYPES
//========================================================================
extern	CAMPAIGNREF*	SCRNcampaign;
extern	HSCREEN			SCRNfullScreen;

//========================================================================
//						PROTOTYPES
//========================================================================
extern	BOOL		ScrnInit( void );
extern	void		ScrnExit( void );
extern	void		ScrnSetState( SCRN_STATE eScreenState );
extern	SCRN_STATE	ScrnGetState( void );

extern	HSCREEN		ScrnCreate( SPOINT* pPoint, USHORT bAttributes );
extern	BOOL		ScrnDelete( HSCREEN hScreen );

extern	BOOL		ScrnSetAttributes( HSCREEN hScreen, USHORT bAttributes );
extern	USHORT		ScrnGetAttributes( HSCREEN hScreen );
extern	BOOL		ScrnHaveAttributes( HSCREEN hScreen, USHORT bAttributesMask );
extern	BOOL		ScrnSetBkg( HSCREEN hScreen, SCREENDEF* pScreenDef );
extern	SPRITE*		ScrnGetBkg( HSCREEN hScreen );
extern	BOOL		ScrnSetArea( HSCREEN hScreen, SCREENDEF* pScreenDef );
extern	SBOX*		ScrnGetArea( HSCREEN hScreen );
extern	BOOL		ScrnSetPosition( HSCREEN hScreen, SPOINT* pPosition );
extern	SPOINT*		ScrnGetPosition( HSCREEN hScreen );
extern	BOOL		ScrnSetBGColor( HSCREEN hScreen, SCRN_COLOR eColor );
extern	SCRN_COLOR	ScrnGetBGColor( HSCREEN hScreen );

extern	void		ScrnDoDisplay( void );
extern	void		ScrnDoActions( void );
extern	void		ScrnTerminate( SCRN_STATE eState );
extern	void		ScrnReload( void );
extern	LONG		ScrnDisplay( HSCREEN hScreen );
extern	LONG		ScrnUpdate( HSCREEN hScreen );
extern	BOOL		ScrnInEditMode( void );
extern	BOOL		ScrnTerminateEditMode( HSCREENBTN hNextBtn );

extern	LONG		ScrnNOOP( HSCREEN hScreen );

extern	LONG		ScrnTerminateScreen( HSCREEN* hScreen );
extern	LONG		ScrnInitTitleScreen( HSCREEN* hScreen );
extern	LONG		ScrnTitleUpdate( HSCREEN hScreen );
extern	LONG		ScrnTerminateTitleScreen( HSCREEN* hScreen );
extern	LONG		ScrnInitGameStart( HSCREEN* hScreen );
extern	LONG		ScrnNOOP( HSCREEN* hScreen );
extern	LONG		ScrnInitPlayerName( HSCREEN* hScreen );
extern	LONG		ScrnInitSelectCampaign( HSCREEN* hScreen );
extern	LONG		ScrnTerminateSelectCampaign( HSCREEN* hScreen );
extern	LONG		ScrnOnCampaignMore( HSCREENBTN hScreenBtn );
extern	LONG		ScrnInitSelectMission( HSCREEN* hScreen );
extern	LONG		ScrnTerminateSelectMission( HSCREEN* hScreen );
extern	LONG		ScrnOnScenarioMore( HSCREENBTN hScreenBtn );

extern	LONG		ScrnInitOptions( HSCREEN* hScreen );
extern	LONG		ScrnControlsScreen( HSCREEN* hScreen );
extern	LONG		ScrnAudioScreen( HSCREEN* hScreen );
extern	LONG		ScrnTerminateAudioScreen( HSCREEN* hScreen );
extern	LONG		ScrnAboutScreen( HSCREEN* hScreen );
extern	LONG		ScrnTerminateAboutScreen( HSCREEN* hScreen );

extern	LONG		ScrnInitPlayOptions( HSCREEN* hScreen );
extern	LONG		ScrnPlayControlsScreen( HSCREEN* hScreen );
extern	LONG		ScrnPlayAudioScreen( HSCREEN* hScreen );
extern	LONG		ScrnPlayAboutScreen( HSCREEN* hScreen );
extern	LONG		ScrnTerminatePlayAboutScreen( HSCREEN* hScreen );

extern	LONG		ScrnInitStats( HSCREEN* hScreen );
extern	LONG		ScrnTerminateStats( HSCREEN* hScreen );

extern	void		ScrnOnContinueStats( void );
extern	LONG		ScrnOnQuitStats( HSCREENBTN hScreenBtn );

extern	LONG		ScrnOnYesPlayAgain( HSCREENBTN hScreenBtn );
extern	LONG		ScrnOnNoPlayAgain( HSCREENBTN hScreenBtn );
extern	LONG		ScrnOnEndMultiplayer( HSCREENBTN hScreenBtn );

extern	LONG		ScrnInitHost( HSCREEN* hScreen );
extern	LONG		ScrnTerminateHost( HSCREEN* hScreen );
extern	void		ScrnUpdateHost( void );
extern	LONG		ScrnInitRemote( HSCREEN* hScreen );
extern	LONG		ScrnTerminateRemote( HSCREEN* hScreen );
extern	int			ScrnUpdateRemote( void );

extern	void		ScrnStatInitSubstate( void );
extern	void		ScrnStatEndSubstate( void );extern	void		ScrnStatementEndSubstate( void );

extern	void		ScrnOptionsInitSubstate( void );
extern	void		ScrnOptionsEndSubstate( void );

extern	LONG		ScrnKeypadInitState( HSCREEN* hScreen );
extern	LONG		ScrnKeyboardInitState( HSCREEN* hScreen );
extern	LONG		ScrnCustomInitState( HSCREEN* hScreen );
extern	LONG		ScrnJoystickInitState( HSCREEN* hScreen );
extern	void		ScrnLoadConfiguration( HSCREEN hScreen, CONFIG eConfigType, BOOL bUseOffset );
extern	void		ScrnLoadJoystickConfiguration( HSCREEN hScreen, CONFIG eConfigType, BOOL bUseOffset );

extern	void		ScrnReceiveChatMessage(char *message);

extern	void		ScrnDeletePlayerFiles( char* pPlayerName );

extern	void		Scrn_KDn_Options( UINT nChar, UINT nFlags );

extern	HSCREENBTN	ScrnGetChatBtn( void );
extern	void		ScrnInitChat( UINT key );

extern	void		ScrnDisplayLoading( void );
extern	BOOL		ScrnOptionsVisible( void );
extern	LONG		ScrnOnPlayBack( HSCREENBTN hScreenBtn );
extern	LONG		ScrnOnBack( HSCREENBTN hScreenBtn );
extern	LONG		ScrnPlayerName( HSCREENBTN hScreenBtn );

extern	char*		ScrnGetStateName( SCRN_STATE eState );
extern	void		ScrnRedoPlayerNames (void );

//========================================================================
//						EOF
//========================================================================
