//========================================================================
//	FILE:			$Workfile: ScreenBtn.cpp $
//
//	DESCRIPTION:	ArmyMen ScreenBtn processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, October 1, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ScreenBtn.cpp 88    4/14/98 9:08p Nrobinso $
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
//  $Log: /ArmyMen/src/ScreenBtn.cpp $
//  
//  88    4/14/98 9:08p Nrobinso
//  turn off delete in map select chat
//  
//  87    4/08/98 11:25p Nrobinso
//  fix keyboard save
//  
//  85    4/02/98 3:22p Phu
//  typecast to avoid warnings
//  
//  84    4/01/98 12:00p Aburgess
//  oops! didn't initialize the NEWPLAYER_BtnSize
//  
//  83    4/01/98 11:03a Aburgess
//  properly handle "New Player" callsigns
//  
//  82    3/30/98 10:08p Nrobinso
//  don't send empty message
//  
//  81    3/24/98 5:23p Nrobinso
//  limit player names in length
//  
//  80    3/23/98 7:10p Nrobinso
//  fix directory of colors
//  
//  79    3/23/98 4:47p Aburgess
//  fixed chat receive colors in MP
//  
//  78    3/22/98 11:56p Nrobinso
//  fix it so a custom key can be the same as the fixed key
//  
//  77    3/22/98 10:55p Nrobinso
//  remove default back button
//  
//  76    3/22/98 10:53p Nrobinso
//  look for null keyvode name
//  
//  75    3/19/98 1:25p Aburgess
//  attempt to fix player colors
//  
//  74    3/18/98 3:08p Aburgess
//  fix chat colors
//  
//  73    3/18/98 3:04p Nrobinso
//  switch to mp screen buttons coming from the root Screens
//  
//  72    3/17/98 7:21p Nrobinso
//  fix unsigned char bug involving keys; don't allow a bunch of keys that
//  don't register properly, like scroll Lock
//  
//  71    3/17/98 11:21a Aburgess
//  corrected UI processing in callsign screen buttons
//  
//  70    3/16/98 11:35a Aburgess
//  corrected bug 660, nameless player
//  
//  69    3/16/98 1:10a Nrobinso
//  fix cursor over icon button
//  
//  68    3/14/98 4:44p Nrobinso
//  fix double click, back while editing and nameless palyers
//  
//  67    3/11/98 3:21p Aburgess
//  modifications made to correct Disabled button colors
//  
//  66    3/11/98 1:17p Aburgess
//  removed debug
//  
//  65    3/11/98 11:27a Aburgess
//  modifications made to support new colorization of menus based on player
//  army color
//  
//  64    3/11/98 12:57a Nrobinso
//  only turn off cursor when needed
//  
//  63    3/09/98 9:56a Aburgess
//  narrowed edit button area
//  
//  62    3/08/98 8:52p Nrobinso
//  Esc works in joystick custom; Esc doesn't clear the custom key, it
//  leaves it alone
//  
//  61    3/05/98 4:57p Aburgess
//  correction of actions due to ESC in chat
//  
//  60    3/05/98 3:10p Aburgess
//  check for bSarge or !bSarge when accepting custom keys
//  
//  59    3/03/98 9:20a Aburgess
//  modified Chat to use ESC key to exit chat without sending message
//  
//  58    3/02/98 12:14p Aburgess
//  modifications made to support the ESC key in both non-gameplay and
//  gameplay modes.
//  
//  57    3/01/98 11:03p Nrobinso
//  put screens in system memory
//  
//  56    2/26/98 10:19a Aburgess
//  removed SCREENBTN memory leak
//  
//  55    2/25/98 3:19p Aburgess
//  corrected NEW PLAYER return-return assertion
//  
//  54    2/25/98 11:47a Aburgess
//  modifications made to correct user configuration bugs
//  
//  53    2/20/98 6:15p Nrobinso
//  remove static sfx calls
//  
//  52    2/20/98 10:43a Phu
//  changed a char to unsigned char for table-lookup
//  
//  51    2/19/98 11:31a Aburgess
//  modifications for screen layouts
//  
//  50    2/18/98 6:35p Aburgess
//  modifications made to support Joystick and Custom configurations.
//  Corrected BACKSPACE in edit keys. Added Double-Click, and Name-Return
//  advance to next mission. Corrected multiple Callsign select bug.
//  Corrected configuration offset problem.
//  
//  47    2/17/98 10:14a Nrobinso
//  swap joystick/keyboard test
//  
//  46    2/17/98 9:02a Aburgess
//  modifications made to support User Configuration
//  
//  45    2/16/98 6:28p Nrobinso
//  joystick configuration support
//  
//  44    2/13/98 12:22p Nrobinso
//  add joystick capture
//  
//  43    2/13/98 12:08p Aburgess
//  modifications to ApplyOffset
//  
//  42    2/13/98 11:24a Aburgess
//  removed application of offset to parent box data. Now need to refigure
//  dynamic application in configuration screens
//  
//  41    2/13/98 10:06a Aburgess
//  modifications made to further support keyboard configurations. Support
//  of Audio slider bar. implementation of all known buttons
//  
//  40    2/12/98 7:34p Nrobinso
//  removed unused code
//  
//  39    2/12/98 7:28p Nrobinso
//  fixes removed by merge restored
//  
//  38    2/12/98 4:17p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  37    2/09/98 7:24p Nrobinso
//  limit width of chat messages
//  
//  36    2/06/98 8:45a Aburgess
//  modifications made to translate keycodes
//  
//  35    2/06/98 7:20a Aburgess
//  modifications made to support the CUSTOM configuration screen
//  
//  34    2/01/98 4:31p Aburgess
//  modifications made to support new ART and maps files
//  
//  33    1/23/98 10:47a Aburgess
//  modification to increase chat message string length to allow player
//  name to be added without overrunning the buffer
//  
//  32    1/23/98 10:35a Aburgess
//  modifications made to add Player name to chat
//  
//  31    1/23/98 9:38a Aburgess
//  modifications made to support new multiplayer screens
//  
//  30    1/19/98 7:41p Aburgess
//  background color modifications and new color table
//  
//  29    1/14/98 2:16p Aburgess
//  modifications made to support GAME_PLAY Options screens
//  
//  28    1/07/98 3:26p Aburgess
//  correct chat in dashboard on NULL
//  
//  27    1/07/98 12:42p Aburgess
//  double RETURN keys on an empty player name now sets to "New Player" and
//  sets the button to FOCUSED
//  
//  26    1/06/98 1:38p Aburgess
//  modification of FOCUSED processing
//  
//  25    12/23/97 7:38p Nrobinso
//  if empty name, revert it to New Player
//  
//  24    12/22/97 11:33a Aburgess
//  lastest and greatest screen processing
//  
//  23    12/18/97 1:18p Aburgess
//  New Audio and User Configuration screens. New Scrolling buttons and
//  Slider bars
//  
//  22    12/15/97 1:12a Aburgess
//  corrected SBtnExit button delete problem
//  
//  21    12/11/97 10:20a Aburgess
//  updated keyhandlers
//  
//  20    12/09/97 12:49p Aburgess
//  debug changes
//  
//  19    12/09/97 12:12p Phu
//  
//  19    12/09/97 12:12p Phu
//  
//  18    12/08/97 7:15a Nrobinso
//  put a bunch of data under compile control
//  
//  17    12/07/97 6:27p Aburgess
//  changed to multiplayer chat send
//  
//  16    12/06/97 4:16p Aburgess
//  changes made to support chat in multiplayer screens
//  
//  15    12/02/97 4:39p Aburgess
//  handle clicked state better
//  
//  14    12/02/97 10:20a Aburgess
//  correction for point in button when button is an ICON type
//  
//  13    12/01/97 12:47p Aburgess
//  corrected NULL sprite reference
//  
//  12    12/01/97 11:58a Aburgess
//  corrected bad text string due to imagebaox on non-ICON buttons
//  
//  11    12/01/97 9:55a Aburgess
//  update of SCREEN processing
//  
//  10    11/26/97 2:27p Aburgess
//  modifications made to support MultiPlayer Campaign Select
//  
//  9     11/20/97 11:31a Nrobinso
//  change DrawRect to FillRect function
//  
//  8     11/16/97 2:20p Aburgess
//  clean up of screen, screenobj, and screenbtn
//  
//  7     11/12/97 10:26a Aburgess
//  added debug asserts and SBtnDump/SBtnColorName routines
//  
//  6     11/11/97 2:59p Aburgess
//  modification to safegaurd multiple occurrences of player names. Hooks
//  for Edit CARET.
//  
//  5     11/10/97 10:07a Nrobinso
//  clears input box if new player
//  
//  4     11/07/97 10:31a Aburgess
//  Button UI upgrades
//  
//  3     10/27/97 10:57a Aburgess
//  Pass 1 of the new FULL SCREEN UI interface and data
//  
//  2     10/16/97 7:29a Aburgess
//  lastest version of ScreenObj and ScreenBtn
//  
//  1     10/16/97 7:02a Aburgess
//  ScreenBtn: UI Full Screen button interface
//  
//  6     10/09/97 3:35p Aburgess
//  cleanup of button processing
//  
//  5     10/07/97 3:17p Aburgess
//  fixed screen offsets
//  
//  4     10/07/97 11:52a Aburgess
//  
//  3     10/07/97 11:12a Aburgess
//  latest changes for buttons
//  
//  2     10/07/97 8:02a Aburgess
//  lastest versions of button processing.
//  
//  1     10/05/97 12:06p Aburgess
//  New BUTTON processing for full screen UI
//  
//  $Nokeywords:$
//========================================================================
//========================================================================

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
#include "ui.h"
#include "comm.h"
#include "miscfile.h"
#include "bmptext.h"
#include "states.h"

#include "ScreenBtn.h"
#include "ScreenObj.h"
#include "Screen.h"
#include "stats.h"
#include "input.h"
#include "Commands.h"
#include "ScreenBtn.dat"

extern	void	SObjUpdateObject( SPOINT* pPoint );
extern	void	ScrnReceiveChatMessage(char *message);
extern	void	ScrnClearFocus( HSCREENBTN hScreenBtn );
extern	void	ScrnClearClicked( HSCREENBTN hScreenBtn );
extern	void	ScrnForceUpdate( void );
extern	SCRN_STATE	ScrnGetState( void );

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//================================================================
//			GLOBAL variables
//================================================================

//================================================================
//			GLOBAL prototypes
//================================================================

//================================================================
//			LOCAL prototypes
//================================================================
void	SBtnTurnOnKeys( HSCREENBTN hScreenBtn );
void	SBtnKeycodeTurnOnKeys( HSCREENBTN hScreenBtn );
void	SBtnJoystickTurnOnKeys( HSCREENBTN hScreenBtn );
unsigned char	SBtnPlayerColor( SHORT nPlayerIndex );

//================================================================
//			LOCAL variables
//================================================================
#define	BLACK				0x00000000
#define	WHITE				0x00ffffff

#define	SBTN_MAX_BTNS	256

typedef enum
{
	EDIT_CAPTURE = 1,
	KEYBOARD_CAPTURE,
	JOYSTICK_CAPTURE

} CAPTURE_STATES;

HSCREENBTN	SBTNallScreenBtns[ SBTN_MAX_BTNS ];
HSCREENBTN	SBTNspecialScreenBtns[ SBTN_MAX_SPCL_BTNS ];
int			SBTNnextScreenBtn;
HSCREENBTN	SBTNcurrentFocus;
HSCREENBTN	SBTNcurrentClicked;

COLORREF	SBTNcolorTable[ SBTN_LAST_COLOR ] =
{
	RGB_TRANSPARENT,
	RGB_DK_RED,
	RGB_DK_GREEN,
	RGB_BROWN,
	RGB_DK_BLUE,
	RGB_DK_MAGENTA,
	RGB_DK_CYAN,
	RGB_GRAY,
	RGB_DK_GRAY,
	RGB_RED,
	RGB_GREEN,
	RGB_YELLOW,
	RGB_BLUE,
	RGB_MAGENTA,
	RGB_CYAN,
	RGB_WHITE,
	RGB_BLACK,
	RGB_LT_GREEN,
	RGB_LT_TAN,
	RGB_LT_BLUE,
	RGB_LT_GRAY,
	RGB_DK_TAN
};

SBOX	SPCLBox = { 0,0,640,480 };


char *KeysText[] =
{
	NULL,	"ESC",	"1",	"2",	"3",	"4",	"5",	"6",				// 007
	"7",	"8",	"9",	"0",	"-",	"=",	"BACKSPACE", "TAB",			// 00f
	"Q",	"W",	"E",	"R",	"T",	"Y",	"U",	"I",				// 017
	"O",	"P",	"[",	"]",	"RETURN", "LCTRL", "A",	"S",				// 01f
	"D",	"F",	"G",	"H",	"J",	"K",	"L",	";",				// 027
	"APOSTR","~",	"LSHIFT","\\",	"Z",	"X",	"C",	"V",				// 02f
	"B",	"N",	"M",	"COMMA","PERIOD","SLASH","RSHIFT", "PAD *",			// 037
	"LALT",	"SPACE",NULL,	"F1",	"F2",	"F3",	"F4",	"F5",				// 03f
	"F6",	"F7",	"F8",	"F9",	"F10",	NULL,	NULL,	"PAD 7",			// 047
	"PAD 8","PAD 9","PAD -","PAD 4","PAD 5", "PAD 6", "PAD +", "PAD 1",			// 04f
	"PAD 2","PAD 3","PAD 0","DEL",	NULL,	NULL,	NULL,	"F11",				// 057
	"F12",	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 05f
	NULL,	NULL,	NULL,	NULL,	"F13",	"F14",	"F15",	NULL,				// 067
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 06f
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 077
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 07f
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 087
	NULL,	NULL,	NULL,	NULL,	NULL,	"PAD =", NULL,	NULL,				// 08f
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 097	
	NULL,	NULL,	NULL,	NULL,	"ENTER","RCTRL",NULL,	NULL,				// 09f
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 0a7
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 0af
	NULL,	NULL,	NULL,	"PAD ,", NULL,	"PAD /",NULL,	NULL,				// 0b7
	"RALT",	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 0bf
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	"HOME",				// 0c7
	"UP",	"PGUP",	NULL,	"LEFT",	NULL,	"RIGHT", NULL,	"END",				// 0cf
	"DOWN",	"PGDN",	"INSERT","DELETE",	NULL,	NULL,	NULL,	NULL,			// 0d7
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 0df
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 0e7
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 0ef
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,				// 0f7
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL				// 0ff
};

int	NEWPLAYER_BtnSize;

//================================================================
//			LOCAL prototypes
//================================================================
void	SBtnStore( HSCREENBTN hScreenBtn );
void	SBtnRemove( HSCREENBTN hScreenBtn );
BOOL	SBtnPointInScreenBtn( HSCREENBTN hScreenBtn, SPOINT* pPoint );
BOOL	SBtnPointOutOfScreenBtn( HSCREENBTN hScreenBtn, SPOINT* pPoint );
BOOL	SBtnUpdateCheck( HSCREENBTN hScreenBtn );
BOOL	SBtnSetReference( HSCREENBTN hScreenBtn, char* pScreenBtnRef, SBTN_STATE eSBtnState );
void	SBtnDisplayEditBtn( HSCREENBTN hScreenBtn );
void	SBtnDisplayKeycodeBtn( HSCREENBTN hScreenBtn );
BOOL	SBtnIsSpecial( HSCREENBTN hScreenBtn );
void	SBtnLoadTextDef( HSCREENBTN hScreenBtn, SCREENBTNDEF* pScreenBtnDef );
void	SBtnLoadIconDef( HSCREENBTN hScreenBtn, SCREENBTNDEF* pScreenBtnDef );
void	SBtnLoadEditDef( HSCREENBTN hScreenBtn, SCREENBTNDEF* pScreenBtnDef );

// special screenBtns Load/Free routines
void	SBtnLoadOK( void );
void	SBtnLoadCANCEL( void );
void	SBtnLoadNEXT( void );
void	SBtnLoadBACK( void );
void	SBtnLoadFINISH( void );
void	SBtnFreeOK( void );
void	SBtnFreeCANCEL( void );
void	SBtnFreeNEXT( void );
void	SBtnFreeBACK( void );
void	SBtnFreeFINISH( void );
int		SBtnSpecialIndex( ULONG hScreenBtn );

//================================================================
//			SCREENBTN Routines
//================================================================

//========================================================================
//	Function:		SBtnInit()
//
//	Description:
//		Initalize the ScreenBtn processing.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

BOOL	SBtnInit( void )
{
	// clear the normal screenBtn list
	ZeroMemory( SBTNallScreenBtns, (SBTN_MAX_BTNS * sizeof(HSCREENBTN) ) );
	SBTNnextScreenBtn   = 0;
	SBTNcurrentFocus    = NULL;
	SBTNcurrentClicked  = NULL;

	// clear the special screenbtns list
	ZeroMemory( SBTNallScreenBtns, (SBTN_MAX_BTNS * sizeof(HSCREENBTN) ) );

	// initalize the "New Player" string size
	NEWPLAYER_BtnSize = strlen( NEWPLAYER_TextBtn );

	// build all the special buttons
	SBtnLoadOK();
	SBtnLoadCANCEL();
	SBtnLoadNEXT();
	SBtnLoadFINISH();
	return( FALSE );
}

//========================================================================
//	Function:		SBtnExit()
//
//	Description:
//		terminate and clear the ScreenBtn processing.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	SBtnExit( void )
{
	int			nScreenBtn;
	HSCREENBTN	hScreenBtn;


	// remove each of the special screenbtns build all the special buttons
	SBtnFreeFINISH();
	SBtnFreeBACK();
	SBtnFreeNEXT();
	SBtnFreeCANCEL();
	SBtnFreeOK();

	// remove any linering normal screenbtns
	for( nScreenBtn=0; nScreenBtn<SBTNnextScreenBtn; ++nScreenBtn )
	{
		hScreenBtn = SBTNallScreenBtns[ nScreenBtn ];
		if ( hScreenBtn )
		{
			if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
			{
				// first free all the sprites
				if ( hScreenBtn->pNullRef[0] )
				{
					FreeSprite( &(hScreenBtn->NullSprite) );
				}
				if ( hScreenBtn->pFocusedRef[0] )
				{
					FreeSprite( &(hScreenBtn->FocusedSprite) );
				}
				if ( hScreenBtn->pClickedRef[0] )
				{
					FreeSprite( &(hScreenBtn->ClickedSprite) );
				}
				if ( hScreenBtn->pDisabledRef[0] )
				{
					FreeSprite( &(hScreenBtn->DisabledSprite) );
				}
			}
#ifdef SBTN_DEBUG
TRACE( "SBtnExit:     FREE (%08x)\n", hScreenBtn );
#endif
			free( hScreenBtn );
		}
	}
}

//========================================================================
//	Function:		SBtnSpclFree()
//
//	Description:
//		free up all the special ScreenBtns.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	SBtnSpclFree( void )
{
	// remove each of the special screenbtns build all the special buttons
	SBtnFreeFINISH();
	SBtnFreeBACK();
	SBtnFreeNEXT();
	SBtnFreeCANCEL();
	SBtnFreeOK();
}

//========================================================================
//	Function:		SBtnCreate()
//
//	Description:
//		Create an instance of a Screen ScreenBtn.
//
//	Input:			pPoint			Upper Lefthand coordinate of the button to
//										be created.
//					bAttributes		Attributes to be applied to this new button.
//
//	Ouput:			TRUE			if button created successfully,
//										FALSE otherwise
//
//========================================================================

HSCREENBTN		SBtnCreate( SPOINT* pPoint, ULONG bAttributes, SBOX* pParentBox )
{
	int			nColorIndex   = 0;
	char*		pScreenPath   = NULL;
	SCREENBTN*	pScreenBtn    = NULL;
	HSCREENBTN	hNewScreenBtn = NULL;
	SCRN_STATE	eScrnState;

	// acquire the players army color and set to the appropriate color directory
	eScrnState = ScrnGetState();
	switch (eScrnState)	{
		case SCRN_MULTI_HOST_STATE:
		case SCRN_MULTI_REMOTE_STATE:
		case SCRN_STATS_STATE:
			nColorIndex = LAST_COLOR_ARMY;
			break;
		default:
			nColorIndex = PlayerColor(ARMY_PLAYER);
			break;
	}
	pScreenPath = ArmyInterfacePaths[ nColorIndex ];
	SetPath( pScreenPath );

	// now malloc a screen button
	pScreenBtn = (SCREENBTN*)malloc( sizeof ( SCREENBTN ) );
	if ( pScreenBtn == NULL )
	{
		// error malloc failed
		TRACE( "SBtnCreate(): malloc failure [%s : %d]\n", __FILE__, __LINE__ );
		goto exit;
	}
#ifdef SBTN_DEBUG
TRACE( "SBtnCreate: MALLOC (%08x)\n", pScreenBtn );
#endif
	ZeroMemory( (void*)pScreenBtn, sizeof( SCREENBTN ) );

	// initialize the buttons status structure elements
	pScreenBtn->bAttributes         = bAttributes;
	pScreenBtn->eScreenBtnState     = BUTTON_NULL;
	pScreenBtn->ePrevScreenBtnState = BUTTON_NULL;
	pScreenBtn->ParentBox.x         = pParentBox->x;
	pScreenBtn->ParentBox.y         = pParentBox->y;
	pScreenBtn->ParentBox.cx        = pParentBox->cx;
	pScreenBtn->ParentBox.cy        = pParentBox->cy;
	pScreenBtn->bUpdate             = TRUE;
	hNewScreenBtn                   = pScreenBtn;
	SBtnSetPosition( hNewScreenBtn, pPoint );

	// now store the button, if its not a special Button
	if ( SBtnIsSpecial( hNewScreenBtn ) == FALSE )
		SBtnStore( hNewScreenBtn );

exit:
	return( hNewScreenBtn );
}

//========================================================================
//	Function:		SBtnDelete()
//
//	Description:
//		Delete a ScreenBtn instance.
//
//	Input:			hScreenBtn			handle to button to be deleted
//
//	Ouput:			FALSE				if success, TRUE if an error
//
//========================================================================

BOOL		SBtnDelete( HSCREENBTN hScreenBtn )
{
	BOOL	bError = TRUE;			// assume an error

	// make sure this not one of the static special buttons
	if ( SBtnIsSpecial(hScreenBtn) )
	{
		// reset the position to 0,0
		hScreenBtn->position.x = 0;
		hScreenBtn->position.y = 0;

		bError = FALSE;
		goto exit;
	}

	if ( hScreenBtn )
	{
		// first free all the sprites
		if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
		{
			// first free all the sprites
			if ( hScreenBtn->pNullRef[0] )
			{
				FreeSprite( &(hScreenBtn->NullSprite) );
			}
			if ( hScreenBtn->pFocusedRef[0] )
			{
				FreeSprite( &(hScreenBtn->FocusedSprite) );
			}
			if ( hScreenBtn->pClickedRef[0] )
			{
				FreeSprite( &(hScreenBtn->ClickedSprite) );
			}
			if ( hScreenBtn->pDisabledRef[0] )
			{
				FreeSprite( &(hScreenBtn->DisabledSprite) );
			}
		}

		// now remove the button
		SBtnRemove( hScreenBtn );

	// now free the button
#ifdef SBTN_DEBUG
TRACE( "SBtnDelete:     FREE (%08x)\n", hScreenBtn );
#endif
		free( hScreenBtn );
	}

	bError = FALSE;

exit:
	return( bError );
}

//========================================================================
//	Function:		SBtnFree()
//
//	Description:
//		Free a ScreenBtn instance.
//
//	Input:			hScreenBtn			handle to button to be deleted
//
//	Ouput:			FALSE				if success, TRUE if an error
//
//========================================================================

void	SBtnFree( HSCREENBTN hScreenBtn )
{
	BOOL	bError = TRUE;			// assume an error

	if ( hScreenBtn )
	{
		// first free all the sprites
		if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
		{
			// first free all the sprites
			if ( hScreenBtn->pNullRef[0] )
			{
				FreeSprite( &(hScreenBtn->NullSprite) );
			}
			if ( hScreenBtn->pFocusedRef[0] )
			{
				FreeSprite( &(hScreenBtn->FocusedSprite) );
			}
			if ( hScreenBtn->pClickedRef[0] )
			{
				FreeSprite( &(hScreenBtn->ClickedSprite) );
			}
			if ( hScreenBtn->pDisabledRef[0] )
			{
				FreeSprite( &(hScreenBtn->DisabledSprite) );
			}
		}

		// now remove the button from the global list
		if ( SBtnIsSpecial( hScreenBtn ) == FALSE )
			SBtnRemove( hScreenBtn );

		// now free the button
#ifdef SBTN_DEBUG
TRACE( "SBtnFree:     FREE (%08x)\n", hScreenBtn );
#endif
		free( hScreenBtn );
	}
}

//========================================================================
//	Function:		SBtnDeleteAll()
//
//	Description:
//		delete all the screenbtns.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	SBtnDeleteAll( void )
{
	HSCREENBTN	hScreenBtn;

	while( SBTNnextScreenBtn )
	{
		hScreenBtn = SBTNallScreenBtns[ 0 ];
		if ( hScreenBtn )
			SBtnDelete( hScreenBtn );
	}
}

//========================================================================
//	Function:		SBtnResetGlobals()
//
//	Description:
//		reset global screenBtn data to a static state.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	SBtnResetGlobals( void )
{
	SBTNcurrentFocus    = NULL;
	SBTNcurrentClicked  = NULL;
}

//========================================================================
//				BUTTON ACCESS ROUTINES
//========================================================================

BOOL	SBtnSetState( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState )
{
	int					nIndex;
	int					nColorIndex;
	SBTN_SCRN_COLORS*	pArmyColors;
	HSCREENBTN			hClickedButton;

	ASSERT ( hScreenBtn );

	if ( (eSBtnState == hScreenBtn->eScreenBtnState) && (ScrnGetState() != SCRN_SELECT_CALLSIGN_STATE) )
		return(FALSE);

	// remember the current state
	if ( eSBtnState != hScreenBtn->eScreenBtnState)
		hScreenBtn->ePrevScreenBtnState = hScreenBtn->eScreenBtnState;
	hClickedButton = SBTNcurrentClicked;

	switch ( eSBtnState )
	{
	case BUTTON_CLICKED:
		// first remember the previously clicked button
		if ( SBTNcurrentClicked != hScreenBtn )
		{
			hScreenBtn->hPrevClicked = SBTNcurrentClicked;

			if ( SBTNcurrentClicked )
			{
				if ( (SBTNcurrentClicked->bAttributes & SBTN_EDIT_TYPE) == SBTN_EDIT_TYPE )
				{
#if 1
					// need to exit edit mode
					if ( ScrnTerminateEditMode( hScreenBtn ) )
						return(FALSE);
#else
					// is this an edit button
					SBtnTurnOffKeys( SBTNcurrentClicked );
					ScrnForceUpdate();

					// remove focus and selected status from other buttons
//					ScrnClearFocus( hScreenBtn );
//					ScrnClearClicked( hScreenBtn );

					return(FALSE);
#endif
				}
				else
				if ( (SBTNcurrentClicked->bAttributes & SBTN_CHAT_TYPE) == SBTN_CHAT_TYPE )
				{
					// is this a CHAT button
					memset(SBTNcurrentClicked->pText, '\0', SBTN_MAX_TEXT_LEN);
					SBtnChatTurnOffKeys( SBTNcurrentClicked );
					ScrnForceUpdate();

					// remove focus and selected status from other buttons
					ScrnClearFocus( hScreenBtn );
					ScrnClearClicked( hScreenBtn );

					return(FALSE);
				}
				else
				if ( (SBTNcurrentClicked->bAttributes & SBTN_KEY_TYPE) == SBTN_KEY_TYPE )
				{
					// is this a Configuration KEYCODE button
					SBtnKeycodeTurnOffKeys( SBTNcurrentClicked );
					ScrnForceUpdate();

					// remove focus and selected status from other buttons
					ScrnClearFocus( hScreenBtn );
					ScrnClearClicked( hScreenBtn );

					return(FALSE);
				}
			}

			// if this is an edit or chat button we'd better switch to the input mode
			if ( (hScreenBtn->bAttributes & SBTN_EDIT_TYPE) == SBTN_EDIT_TYPE )
			{
				// set the background color for edit mode
				nColorIndex = PlayerColor(ARMY_PLAYER);
				pArmyColors = ArmyInterfaceColors[ nColorIndex ];
				SBtnSetBGColor( hScreenBtn, pArmyColors->EditFillColor );

				// copy the current player name into the permanent set
				nIndex = hScreenBtn->dwData;
				StatSetPlayerNameIndex( nIndex );

				// copy the current player name into the permanent set
				nIndex = hScreenBtn->dwData;
				StatSetPlayerNameIndex( nIndex );
				strcpy( STATcurrentName, hScreenBtn->pText );
				strcpy( STATplayerNames[ nIndex ], STATcurrentName );
				StatUpdate( nIndex, STAT_UPDATE_PLAYER_NAME, TRUE );

				// is this an EDIT button
				if ( strncmp( hScreenBtn->pText, NEWPLAYER_TextBtn, NEWPLAYER_BtnSize ) == 0 )
				{
					memset(hScreenBtn->pText, '\0', SBTN_MAX_TEXT_LEN);
					SBtnTurnOnKeys( hScreenBtn );
					eSBtnState = BUTTON_EDIT;
				}
			}
			else
			if ( (hScreenBtn->bAttributes & SBTN_CHAT_TYPE) == SBTN_CHAT_TYPE )
			{
				// is this a CHAT button
				memset(hScreenBtn->pText, '\0', SBTN_MAX_TEXT_LEN);
				SBtnChatTurnOnKeys( hScreenBtn );
				eSBtnState = BUTTON_EDIT;
			}
			else
			if ( (hScreenBtn->bAttributes & SBTN_KEY_TYPE) == SBTN_KEY_TYPE )
			{
				// is this a Configuration KEYCODE button
//				memset(hScreenBtn->pText, '\0', SBTN_MAX_TEXT_LEN);
				if ( ScrnGetState() == SCRN_JOYSTICK_STATE )
					SBtnJoystickTurnOnKeys( hScreenBtn );
				else
					SBtnKeycodeTurnOnKeys( hScreenBtn );

				eSBtnState = BUTTON_EDIT;
			}

			SBTNcurrentClicked = hScreenBtn;

			// remove focus and selected status from other buttons
			ScrnClearFocus( hScreenBtn );
			ScrnClearClicked( hScreenBtn );
		}
		else
		{
			// check for double-click in callsign screen
			ScrnTerminateEditMode( (HSCREENBTN)NULL );
			return( FALSE );
		}

		if ( SBTNcurrentFocus )
		{
			if ( SBTNcurrentFocus != hScreenBtn )
				SBtnSetState( SBTNcurrentFocus, BUTTON_NULL );
			SBTNcurrentFocus = NULL;
		}

		audioPlay( BUTTONSPRINGIN, SND_SFX_FLAG | SND_DELETE_FLAG );
		break;

	case BUTTON_FOCUSED:
		if ( SBTNcurrentFocus )
		{
			if ( (hScreenBtn != SBTNcurrentFocus) && (hScreenBtn != SBTNcurrentClicked) )
			{
				SBtnSetState( SBTNcurrentFocus, BUTTON_NULL );
				SBTNcurrentFocus = hScreenBtn;
			}
		}

		if ( !SBTNcurrentFocus && (hScreenBtn != SBTNcurrentClicked) )
			SBTNcurrentFocus = hScreenBtn;
		break;

	case BUTTON_NULL:
		// make sure we clear any click by pass settings
		hScreenBtn->bAttributes &= ~SBTN_CLICK_BYPASS;
	default:
		if ( hScreenBtn == SBTNcurrentFocus )
			SBTNcurrentFocus = NULL;

		if ( hScreenBtn == SBTNcurrentClicked )
			SBTNcurrentClicked = NULL;
		break;
	}

	hScreenBtn->eScreenBtnState = eSBtnState;
	hScreenBtn->bUpdate         = TRUE;
	SBtnExecuteCallback( hScreenBtn, eSBtnState );

	return(FALSE);
}

SBTN_STATE	SBtnGetState( HSCREENBTN hScreenBtn )
{
	ASSERT ( hScreenBtn );

	return( hScreenBtn->eScreenBtnState );
}

BOOL	SBtnSetAttributes( HSCREENBTN hScreenBtn, ULONG bAttributes )
{
	ASSERT ( hScreenBtn );

	if ( bAttributes )
		hScreenBtn->bAttributes |= bAttributes;
	else
		hScreenBtn->bAttributes = SBTN_CLEAR;

	return( FALSE );	// no error
}

BOOL	SBtnClearAttributes( HSCREENBTN hScreenBtn, ULONG bAttributes )
{
	ASSERT ( hScreenBtn );

	if ( bAttributes )
		hScreenBtn->bAttributes &= ~bAttributes;
	else
		hScreenBtn->bAttributes = SBTN_CLEAR;

	return( FALSE );	// no error
}

ULONG	SBtnGetAttributes( HSCREENBTN hScreenBtn )
{
	ASSERT ( hScreenBtn );

	return( hScreenBtn->bAttributes );
}

BOOL	SBtnHaveAttributes( HSCREENBTN hScreenBtn, ULONG bAttributesMask )
{
	BOOL	bHaveThem = FALSE;

	ASSERT ( hScreenBtn );

	if ( bAttributesMask )
	{
		if ( (hScreenBtn->bAttributes & bAttributesMask) == bAttributesMask )
			bHaveThem = TRUE;
	}
	else
	if ( hScreenBtn->bAttributes == SBTN_CLEAR )	// bAttributesMask = 0 = SBTN_CLEAR
		bHaveThem = TRUE;

	return( bHaveThem );
}

BOOL	SBtnSetFont( HSCREENBTN hScreenBtn, LONG nFontID )
{
	ASSERT ( hScreenBtn );

	hScreenBtn->nFontID = nFontID;

	return( FALSE );	// no error
}

LONG	SBtnGetFont( HSCREENBTN hScreenBtn )
{
	ASSERT ( hScreenBtn );

	return( hScreenBtn->nFontID );
}

BOOL	SBtnSetText( HSCREENBTN hScreenBtn, char* pText )
{
	SBOX	textBox;
	SBOX*	pImageBox;
	char*	pReference;
	int		len = 0;
	BOOL	bError = TRUE;

	ASSERT( hScreenBtn );

	if ( pText )
	{
		if ( IsResource( pText ) )
		{
			// now assign the resource ID
			hScreenBtn->NullResourceID = (LPTSTR)pText;

			if ( !LoadString( ghinst, (unsigned)(hScreenBtn->pNullRef), hScreenBtn->pText, SBTN_MAX_TEXT_LEN ) )
			{
				// error: failed to load button text
				TRACE( "ERROR: failed to load button text resource [%s : %d]\n"
						__FILE__, __LINE__ );
				goto exit;
			}
		}
		else
		{
			len = 0;
			if ( pText )
			{
				len = strlen( pText );
				if ( len > SBTN_MAX_TEXT_LEN )
					len = SBTN_MAX_TEXT_LEN;

				if ( len )
					strcpy(hScreenBtn->pText, pText);
//				else
//					ASSERT(0);
			}
			hScreenBtn->pText[len] = '\0';
		}
	}
	else
	{
		// the button text is empty
		hScreenBtn->pText[0] = '\0';

		// since there's no text use the default box which was placed into the NULLBOX
		textBox.x   = hScreenBtn->NullBox.x;
		textBox.y   = hScreenBtn->NullBox.y;
		textBox.cx  = hScreenBtn->NullBox.cx;
		textBox.cy  = hScreenBtn->NullBox.cy;

		// see if this text is within an ICON
		if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
		{
			// use the image box only.
			textBox.x   = 0;
			textBox.y   = 0;
			textBox.cx  = 0;
			textBox.cy  = 0;
		}
	}

	// see if this text is within an ICON
	if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
	{
		// get the image box
		pImageBox = SBtnGetBox( hScreenBtn );
	}

	// acquire the Text recquire area
	pReference = hScreenBtn->pText;
	if ( *pReference )
	{
		textBox.x  = 0;
		textBox.y  = 0;
		if ( TextBox( pReference, &textBox, hScreenBtn->nFontID ) )
		{
			// error: failed to acquire text box size
			TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
					__FILE__, __LINE__ );
			goto exit;
		}
	}

	// now see if this text screenBtn is centered or not
	if ( (hScreenBtn->bAttributes & SBTN_TEXT_CENTER) == SBTN_TEXT_CENTER )
	{
		// see if this text is within an ICON
		if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
		{
			// now center (horizontally) within the image box
			hScreenBtn->TextBox.x  = hScreenBtn->ParentBox.x + hScreenBtn->position.x +
									 pImageBox->x + ((pImageBox->cx - textBox.cx)>>1);
		}
		else
		{
			// now center (horizontally) the text box
			hScreenBtn->TextBox.x  = hScreenBtn->ParentBox.x + ((hScreenBtn->ParentBox.cx - textBox.cx)>>1);
			hScreenBtn->position.x = 0;
		}
	}
	else
	{
		// see if this text is within an ICON
		if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
		{
			// now center (horizontally) within the image box
			hScreenBtn->TextBox.x  = hScreenBtn->ParentBox.x + hScreenBtn->position.x +
									 pImageBox->x + ((pImageBox->cx - textBox.cx)>>1);
		}
		else
		{
			// now set the text box
			hScreenBtn->TextBox.x  = hScreenBtn->ParentBox.x + hScreenBtn->position.x;
		}
	}

	hScreenBtn->TextBox.y  = hScreenBtn->ParentBox.y + hScreenBtn->position.y;
	if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
		hScreenBtn->position.y = 0;
	hScreenBtn->TextBox.cx = textBox.cx;
	hScreenBtn->TextBox.cy = textBox.cy;


 	hScreenBtn->bUpdate = TRUE;
	bError              = FALSE;

exit:
	return( bError );	// no error
}

char*	SBtnGetText( HSCREENBTN hScreenBtn )
{
	ASSERT( hScreenBtn );

	return( hScreenBtn->pText );
}

BOOL	SBtnSetBGColor( HSCREENBTN hScreenBtn, SBTN_COLOR eColor )
{
	BOOL	bError = TRUE;

	ASSERT( hScreenBtn );

	hScreenBtn->eBGColor = eColor;
	bError            = FALSE;

	return( bError );
}

SBTN_COLOR	SBtnGetBGColor( HSCREENBTN hScreenBtn )
{
	ASSERT( hScreenBtn );

	return( hScreenBtn->eBGColor );
}

BOOL	SBtnSetFGColor( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState, SBTN_COLOR eColor )
{
	BOOL	bError = TRUE;

	ASSERT( hScreenBtn );

	hScreenBtn->aFGColors[ eSBtnState ] = eColor;
	bError                              = FALSE;

	return( bError );
}

SBTN_COLOR	SBtnGetFGColor( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState )
{
	ASSERT( hScreenBtn );

	return( hScreenBtn->aFGColors[ eSBtnState ] );
}

BOOL	SBtnSetIcon( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState, char* pIcon )
{
	BOOL	bError = TRUE;

	ASSERT( hScreenBtn );
	ASSERT( ((hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE) );

	bError = SBtnSetReference( hScreenBtn, pIcon, eSBtnState );

	return( bError );
}

SPRITE*	SBtnGetIcon( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState )
{
	SPRITE*	pSprite;

	ASSERT( hScreenBtn );

	switch( eSBtnState )
	{
	case BUTTON_NULL:
		pSprite    = &(hScreenBtn->NullSprite);
		break;
	case BUTTON_FOCUSED:
		pSprite    = &(hScreenBtn->FocusedSprite);
		break;
	case BUTTON_CLICKED:
	case BUTTON_EDIT:
		pSprite    = &(hScreenBtn->ClickedSprite);
		break;
	case BUTTON_DISABLED:
		pSprite    = &(hScreenBtn->DisabledSprite);
		break;
	}
	return( pSprite );
}

BOOL	SBtnSetPosition( HSCREENBTN hScreenBtn, SPOINT* pPosition )
{
	ASSERT( hScreenBtn );
	ASSERT( pPosition );

	hScreenBtn->position.x   = pPosition->x;
	hScreenBtn->position.y   = pPosition->y;

	return( FALSE );	// no error
}

SPOINT*	SBtnGetPosition( HSCREENBTN hScreenBtn )
{
	ASSERT( hScreenBtn );

	return( &(hScreenBtn->position) );
}

BOOL	SBtnSetBox( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState, SBOX* pBox )
{
	SBOX*	pSbtnBox;

	ASSERT( hScreenBtn );
	ASSERT( pBox );

	switch( eSBtnState )
	{
	case BUTTON_NULL:
	case BUTTON_DISABLED:
		pSbtnBox = &(hScreenBtn->NullBox);
		break;
	case BUTTON_FOCUSED:
		pSbtnBox = &(hScreenBtn->FocusedBox);
		break;
	case BUTTON_CLICKED:
	case BUTTON_EDIT:
		pSbtnBox = &(hScreenBtn->ClickedBox);
		break;
	}
	pSbtnBox->x   = pBox->x;
	pSbtnBox->y   = pBox->y;
	pSbtnBox->cx  = pBox->cx;
	pSbtnBox->cy  = pBox->cy;

	return( FALSE );	// no error
}

SBOX*	SBtnGetBox( HSCREENBTN hScreenBtn  )
{
	SBOX*	pSbtnBox;

	ASSERT( hScreenBtn );

	switch( hScreenBtn->eScreenBtnState )
	{
	case BUTTON_NULL:
	case BUTTON_DISABLED:
		pSbtnBox = &(hScreenBtn->NullBox);
		break;
	case BUTTON_FOCUSED:
		pSbtnBox = &(hScreenBtn->FocusedBox);
		break;
	case BUTTON_CLICKED:
	case BUTTON_EDIT:
		pSbtnBox = &(hScreenBtn->ClickedBox);
		break;
	}
	return( pSbtnBox );
}

BOOL	SBtnSetData( HSCREENBTN hScreenBtn, DWORD dwData )
{
	ASSERT( hScreenBtn );

	hScreenBtn->dwData   = dwData;

	return( FALSE );	// no error
}

DWORD	SBtnGetData( HSCREENBTN hScreenBtn )
{
	ASSERT( hScreenBtn );

	return( hScreenBtn->dwData );
}

void	SBtnSetCallback( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState, LPVOID pCallback )
{
	ASSERT( hScreenBtn );

	switch( eSBtnState )
	{
	case BUTTON_NULL:
		hScreenBtn->pNullCallback = (LONG (*)(struct screenButton*))pCallback;
		break;
	case BUTTON_FOCUSED:
		hScreenBtn->pFocusedCallback = (LONG (*)(struct screenButton*))pCallback;
		break;
	case BUTTON_CLICKED:
		hScreenBtn->pClickedCallback = (LONG (*)(struct screenButton*))pCallback;
		break;
	case BUTTON_EDIT:
		hScreenBtn->pEditCallback = (LONG (*)(struct screenButton*))pCallback;
		break;
	case BUTTON_DISABLED:
		break;
	default:
		ASSERT(0);
		break;
	}
}

LONG	SBtnExecuteCallback( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState )
{
	long	result;

	ASSERT( hScreenBtn );

	switch( eSBtnState )
	{
	case BUTTON_NULL:
		hScreenBtn->bAttributes &= ~SBTN_CLICK_BYPASS;
		if ( hScreenBtn->pNullCallback )
			return( hScreenBtn->pNullCallback( hScreenBtn ) );
		break;
	case BUTTON_FOCUSED:
		if ( hScreenBtn->pFocusedCallback )
			return( hScreenBtn->pFocusedCallback( hScreenBtn ) );
		break;
	case BUTTON_CLICKED:
		if ( hScreenBtn->pClickedCallback )
		{
//			if ( ((hScreenBtn->bAttributes & SBTN_CLICK_BYPASS) != SBTN_CLICK_BYPASS) && (hScreenBtn->hPrevClicked != hScreenBtn) )
			if ( (hScreenBtn->bAttributes & SBTN_CLICK_BYPASS) != SBTN_CLICK_BYPASS )
			{
				result = hScreenBtn->pClickedCallback( hScreenBtn );
//				hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;
				return( result );
			}
		}
		break;
	case BUTTON_EDIT:
		hScreenBtn->bAttributes &= ~SBTN_CLICK_BYPASS;
		if ( hScreenBtn->pEditCallback )
			return( hScreenBtn->pEditCallback( hScreenBtn ) );
		break;
	case BUTTON_DISABLED:
		hScreenBtn->bAttributes &= ~SBTN_CLICK_BYPASS;
		break;
	default:
		ASSERT(0);
	}

	return(0);
}

BOOL	SBtnSetReference( HSCREENBTN hScreenBtn, char* pScreenBtnRef, SBTN_STATE eSBtnState )
{
	SPRITE*	pSprite;
	LPTSTR*	pRefResource;
	SBOX*	pBox;
	LONG	bSpriteFlags;
	char*	pReference;
	int		len = 0;
	BOOL	bError = TRUE;

	ASSERT( hScreenBtn );
	ASSERT( pScreenBtnRef );
	ASSERT( ((hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE) );

	// first thing we need to do is acquire the proper SBTN_STATE based
	// structure elements
	switch( eSBtnState )
	{
	case BUTTON_NULL:
		pReference   = hScreenBtn->pNullRef;
		pRefResource = &(hScreenBtn->NullResourceID);
		pSprite      = &(hScreenBtn->NullSprite);
		pBox         = &(hScreenBtn->NullBox);
		break;
	case BUTTON_FOCUSED:
		pReference   = hScreenBtn->pFocusedRef;
		pRefResource = &(hScreenBtn->FocusedResourceID);
		pSprite      = &(hScreenBtn->FocusedSprite);
		pBox         = &(hScreenBtn->FocusedBox);
		break;
	case BUTTON_CLICKED:
	case BUTTON_EDIT:
		pReference   = hScreenBtn->pClickedRef;
		pRefResource = &(hScreenBtn->ClickedResourceID);
		pSprite      = &(hScreenBtn->ClickedSprite);
		pBox         = &(hScreenBtn->ClickedBox);
		break;
	case BUTTON_DISABLED:
		pReference   = hScreenBtn->pDisabledRef;
		pRefResource = &(hScreenBtn->DisabledResourceID);
		pSprite      = &(hScreenBtn->DisabledSprite);
		pBox         = &(hScreenBtn->NullBox);
		break;
	}

	// if this is an ICON button, free up the sprite
	if ( pReference && *pReference )
	{
		FreeSprite( pSprite );
		*pReference     = '\0';
	}

	if ( !pScreenBtnRef )	// asked to clear button reference
		goto success;

	len = strlen( pScreenBtnRef );
	if ( len > SBTN_MAX_TEXT_LEN )
		len = SBTN_MAX_TEXT_LEN;
	if ( len )
		strcpy(pReference, pScreenBtnRef);
	pReference[len] = '\0';

	if ( (hScreenBtn->bAttributes & SBTN_ICON_TRANS) == SBTN_ICON_TRANS )
		bSpriteFlags = BM_TRANSPARENT|BM_SYSTEMMEMORY;
	else
		bSpriteFlags = BM_OPAQUE|BM_SYSTEMMEMORY;

	if ( IsResource( (LPTSTR)pScreenBtnRef ) )
	{
		// clear the image filename reference
		pReference[len] = '\0';

		// now assign the resource ID
		*pRefResource = (LPTSTR)pScreenBtnRef;
		if ( !LoadSprite( pSprite, *pRefResource, bSpriteFlags ) )
		{
			// error: failed to load button icon
			TRACE( "ERROR: failed to load button icon resource [%s : %d]\n"
					__FILE__, __LINE__ );
			goto exit;
		}

		// acquire the area for this icon
		if ( SpriteBox( pSprite, pBox ) )
		{
			// error: failed to acquire icon size
			TRACE( "ERROR: failed to acquire icon size [%s : %d]\n",
					__FILE__, __LINE__ );
			goto exit;
		}
	}
	else
	{
		// clear the resource reference
		*pRefResource = NULL;
		if ( *pReference )
		{
			if ( !LoadSprite( pSprite, pReference, bSpriteFlags ) )
			{
				// error: failed to load button image
				TRACE( "ERROR: failed to load button image file [%s : %d]\n",
						__FILE__, __LINE__);
				goto exit;
			}

			// acquire the area for this icon
			if ( SpriteBox( pSprite, pBox ) )
			{
				// error: failed to acquire icon size
				TRACE( "ERROR: failed to acquire icon size [%s : %d]\n",
						__FILE__, __LINE__);
				goto exit;
			}
		}
	}

success:
	bError              = FALSE;
	hScreenBtn->bUpdate = TRUE;

exit:
	return( bError );	// no error
}

//========================================================================
//					BUTTON UTILITY ROUTINES
//========================================================================

BOOL	SBtnPointInScreenBtn( HSCREENBTN hScreenBtn, SPOINT* pPoint )
{
	SBTN_STATE	eSBtnState;
	SHORT		x,y;
	SHORT		x1,y1;
	SHORT		x2,y2;
	SBOX		iconBox;
	SBOX*		pTextBox = NULL;
	SBOX*		pBox     = NULL;
	BOOL		bInArea  = FALSE;

	ASSERT( hScreenBtn );
	ASSERT( pPoint );

	eSBtnState = SBtnGetState( hScreenBtn );
	if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
	{
		switch( eSBtnState )
		{
		case BUTTON_NULL:
		case BUTTON_DISABLED:
			pBox         = &(hScreenBtn->NullBox);
			break;
		case BUTTON_FOCUSED:
			pBox         = &(hScreenBtn->FocusedBox);
			break;
		case BUTTON_CLICKED:
		case BUTTON_EDIT:
			pBox         = &(hScreenBtn->ClickedBox);
			break;
		default:
			ASSERT(0);
		}
		// copy the icon box into the temp and add in the parent and
		// positional offset
		iconBox.x  = pBox->x + hScreenBtn->ParentBox.x + hScreenBtn->position.x;
		iconBox.y  = pBox->y + hScreenBtn->ParentBox.y + hScreenBtn->position.y;
		iconBox.cx = pBox->cx;
		iconBox.cy = pBox->cy;

		// now point to this newly adjusted icon box
		pBox = &iconBox;
	}

	if ( (hScreenBtn->bAttributes & SBTN_TEXT_TYPE) == SBTN_TEXT_TYPE )
	{
		if ( pBox && ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE ) )
		{
			// create a new box using the icon and text box
			pTextBox = &(hScreenBtn->TextBox);
			if ( pTextBox->x > pBox->x )
				x = pBox->x;
			else
				x = pTextBox->x;
			pBox->x = x;

			if ( pTextBox->y > pBox->y )
				y = pBox->y;
			else
				y = pTextBox->y;
			pBox->y = y;

			if ( pTextBox->cx < pBox->cx )
				x = pBox->cx;
			else
				x = pTextBox->cx;
			pBox->cx = x;

			if ( pTextBox->cy < pBox->cy )
				y = pBox->cy;
			else
				y = pTextBox->cy;
			pBox->cy = y;
		}
		else
			pBox = &(hScreenBtn->TextBox);
	}
	else
	if ( (hScreenBtn->bAttributes & SBTN_EDIT_TYPE) == SBTN_EDIT_TYPE )
		pBox = &(hScreenBtn->TextBox);
	else
	if ( (hScreenBtn->bAttributes & SBTN_CHAT_TYPE) == SBTN_CHAT_TYPE )
		pBox = &(hScreenBtn->TextBox);
	else
	if ( (hScreenBtn->bAttributes & SBTN_KEY_TYPE) == SBTN_KEY_TYPE )
		pBox = &(hScreenBtn->ParentBox);

	x = pPoint->x;
	y = pPoint->y;
	x1 = pBox->x;
	y1 = pBox->y;
	x2 = x1 + pBox->cx;
	y2 = y1 + pBox->cy;
	if ( (x >= x1) && (x < x2) )
		if ( (y >= y1) && (y < y2) )
			bInArea = TRUE;

	return( bInArea );
}

BOOL	SBtnPointOutOfScreenBtn( HSCREENBTN hScreenBtn, SPOINT* pPoint )
{
	SBTN_STATE	eSBtnState;
	SBOX*		pBox;
	SHORT		x1,y1,x2,y2;
	BOOL		bInArea = FALSE;

	ASSERT( hScreenBtn );
	ASSERT( pPoint );

	eSBtnState = SBtnGetState( hScreenBtn );
	switch( eSBtnState )
	{
	case BUTTON_NULL:
	case BUTTON_DISABLED:
		pBox         = &(hScreenBtn->NullBox);
		break;
	case BUTTON_FOCUSED:
		pBox         = &(hScreenBtn->FocusedBox);
		break;
	case BUTTON_CLICKED:
	case BUTTON_EDIT:
		pBox         = &(hScreenBtn->ClickedBox);
		break;
	default:
		ASSERT(0);
	}
	if ( (hScreenBtn->bAttributes & SBTN_TEXT_TYPE) == SBTN_TEXT_TYPE )
		pBox = &(hScreenBtn->TextBox);
	if ( (hScreenBtn->bAttributes & SBTN_EDIT_TYPE) == SBTN_EDIT_TYPE )
		pBox = &(hScreenBtn->TextBox);
	else
	if ( (hScreenBtn->bAttributes & SBTN_CHAT_TYPE) == SBTN_CHAT_TYPE )
		pBox = &(hScreenBtn->TextBox);
	else
	if ( (hScreenBtn->bAttributes & SBTN_KEY_TYPE) == SBTN_KEY_TYPE )
		pBox = &(hScreenBtn->ParentBox);

	x1 = (pBox->x - SBTN_FOCUS_OUT);
	y1 = (pBox->y - SBTN_FOCUS_OUT);
	x2 = (x1 + pBox->cx) + SBTN_FOCUS_OUT;
	y2 = (y1 + pBox->cy) + SBTN_FOCUS_OUT;
	if ( (pPoint->x >= x1) && (pPoint->x < x2) )
		if ( (pPoint->y >= y1) && (pPoint->y < y2) )
			bInArea = TRUE;

	return( !bInArea );
}

void	SBtnDisplay( HSCREENBTN hScreenBtn )
{
	COLORREF			refFGColor;
	COLORREF			refBGColor;
	SBTN_COLOR			eFGcolor;
	SBTN_COLOR			eBGcolor;
	RECT				rcScreenBtn;
	char*				pScreenBtnRef;
	SPRITE*				pScreenBtnIcon;
	SBOX*				pBox;
	SBTN_SCRN_COLORS*	pArmyColors;
	int					nColorIndex;

	ASSERT( hScreenBtn );

	if ( hScreenBtn->bUpdate == FALSE )
	{

#ifdef	SCREEN_DEBUG
TRACE( "SCREENBTN (%s): no UPDATE\n", hScreenBtn->pText );
#endif

		return;				// skip this button
	}

	if ( (hScreenBtn->bAttributes & SBTN_INVISIBLE) == SBTN_INVISIBLE )
	{

#ifdef	SCREEN_DEBUG
TRACE( "SCREENBTN (%s): INVISIBLE\n", hScreenBtn->pText );
#endif

		return;				// skip this button
	}

	// acquire the players army color
	nColorIndex = PlayerColor(ARMY_PLAYER);
	pArmyColors = ArmyInterfaceColors[ nColorIndex ];

	// Display the ScreenBtn Image
	if ( ((hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE) )
	{
		// create the button rectangle
		switch( hScreenBtn->eScreenBtnState )
		{
		case BUTTON_NULL:
			pScreenBtnRef  = hScreenBtn->pNullRef;
			pScreenBtnIcon = &(hScreenBtn->NullSprite);
			pBox           = &(hScreenBtn->NullBox);
			break;
		case BUTTON_FOCUSED:
			pScreenBtnRef  = hScreenBtn->pFocusedRef;
			pScreenBtnIcon = &(hScreenBtn->FocusedSprite);
			pBox           = &(hScreenBtn->FocusedBox);
			break;
		case BUTTON_CLICKED:
		case BUTTON_EDIT:
			pScreenBtnRef  = hScreenBtn->pClickedRef;
			pScreenBtnIcon = &(hScreenBtn->ClickedSprite);
			pBox           = &(hScreenBtn->ClickedBox);
			break;
		case BUTTON_DISABLED:
			pScreenBtnRef  = hScreenBtn->pDisabledRef;
			pScreenBtnIcon = &(hScreenBtn->DisabledSprite);
			pBox           = &(hScreenBtn->NullBox);
			break;
		default:
			ASSERT(0);
		}
		rcScreenBtn.left   = hScreenBtn->ParentBox.x + hScreenBtn->position.x + pBox->x;
		rcScreenBtn.top    = hScreenBtn->ParentBox.y + hScreenBtn->position.y + pBox->y;
		rcScreenBtn.right  = rcScreenBtn.left + pScreenBtnIcon->srect.right;
		rcScreenBtn.bottom = rcScreenBtn.top + pScreenBtnIcon->srect.bottom;

		CursorOff(&rcScreenBtn);

		if ( pScreenBtnIcon )
			DisplaySpriteFront( pScreenBtnIcon, rcScreenBtn.left, rcScreenBtn.top );
	}

	
	if ( ((hScreenBtn->bAttributes & SBTN_TEXT_TYPE) == SBTN_TEXT_TYPE) )
	{
		pScreenBtnRef = hScreenBtn->pText;
		if ( pScreenBtnRef[0] != '\0' )
		{

#ifdef	SCREEN_DEBUG
TRACE( "SCREENBTN (%s): position (%d,%d) TextBox (%d,%d,%d,%d ) ParentBox(%d,%d,%d,%d)\n",
	    pScreenBtnRef,
		hScreenBtn->position.x,   hScreenBtn->position.y,
		hScreenBtn->TextBox.x,    hScreenBtn->TextBox.y,
		hScreenBtn->TextBox.cx,   hScreenBtn->TextBox.cy,
		hScreenBtn->ParentBox.x,  hScreenBtn->ParentBox.y,
		hScreenBtn->ParentBox.cx, hScreenBtn->ParentBox.cy
	 );
#endif

			// create the button rectangle
			rcScreenBtn.left   = hScreenBtn->TextBox.x;
			rcScreenBtn.top    = hScreenBtn->TextBox.y;
			rcScreenBtn.right  = rcScreenBtn.left + hScreenBtn->TextBox.cx;
			rcScreenBtn.bottom = rcScreenBtn.top + hScreenBtn->TextBox.cy;

			CursorOff(&rcScreenBtn);


#ifdef	SCREEN_DEBUG
TRACE( "SCREENBTN (%s): rcScreenBtn (%d,%d,%d,%d)\n",
	   pScreenBtnRef,
	   rcScreenBtn.left,  rcScreenBtn.top,
	   rcScreenBtn.right, rcScreenBtn.bottom
	 );
#endif

			eBGcolor   = hScreenBtn->eBGColor;
			refBGColor = SBTNcolorTable[eBGcolor];

			eFGcolor   = hScreenBtn->aFGColors[ hScreenBtn->eScreenBtnState ];
			refFGColor = SBTNcolorTable[eFGcolor];

#ifdef	SCREEN_DEBUG
TRACE( "SCREENBTN (%s): colors (%d,%d)\n", pScreenBtnRef,eBGcolor,eFGcolor );
#endif

			// check for color overrides
			TextSetTransparent( TRUE );
			if ( (hScreenBtn->bAttributes & SBTN_DISABLED) == SBTN_DISABLED )
			{
				refFGColor = SBTNcolorTable[pArmyColors->DisabledColor];
				refBGColor = RGB_TRANSPARENT;
			}
			else
			if ( hScreenBtn->eScreenBtnState != BUTTON_FOCUSED )
			{
				refBGColor = RGB_TRANSPARENT;
			}
			TextSetColors( refFGColor, refBGColor );
#ifdef	SCREEN_DEBUG
TRACE( "SCREENBTN (%s): RGBs   (0x%lX,0x%lX)\n", pScreenBtnRef,refFGColor,refBGColor );
#endif
			TextWrite(	pFrontBuffer,
						rcScreenBtn.left + rcWindowScreen.left,
						rcScreenBtn.top + rcWindowScreen.top,
						pScreenBtnRef, hScreenBtn->nFontID, NULL );
		}
	}
	else	// display the EDITBUTTON
	if ( (hScreenBtn->bAttributes & SBTN_EDIT_TYPE) == SBTN_EDIT_TYPE )
	{
		SBtnDisplayEditBtn( hScreenBtn );
	}
	else	// display the CHATBUTTON
	if ( (hScreenBtn->bAttributes & SBTN_CHAT_TYPE) == SBTN_CHAT_TYPE )
	{
		SBtnDisplayEditBtn( hScreenBtn );
	}
	else	// display the KEYCODEBUTTON
	if ( (hScreenBtn->bAttributes & SBTN_KEY_TYPE) == SBTN_KEY_TYPE )
	{
		SBtnDisplayKeycodeBtn( hScreenBtn );
	}

	// clear the button update flag: button updated
	hScreenBtn->bUpdate = FALSE;
}

void	SBtnDisplayEditBtn( HSCREENBTN hScreenBtn )
{
	COLORREF			refFGColor;
	COLORREF			refBGColor;
	SBTN_COLOR			eFGcolor;
	SBTN_COLOR			eBGcolor;
	RECT				rcScreenBtn;
	char*				pScreenBtnRef;
	SBOX*				pBox;
	SBOX				textBox;
	LONG				xOffset;
	SBTN_SCRN_COLORS*	pArmyColors;
	int					nColorIndex;

	// acquire the players army color
	nColorIndex = PlayerColor(ARMY_PLAYER);
	pArmyColors = ArmyInterfaceColors[ nColorIndex ];

	// get the button text, box, and color data
	pScreenBtnRef = hScreenBtn->pText;
	eBGcolor      = hScreenBtn->eBGColor;
	refBGColor    = SBTNcolorTable[eBGcolor];

	eFGcolor      = hScreenBtn->aFGColors[ hScreenBtn->eScreenBtnState ];
	refFGColor    = SBTNcolorTable[eFGcolor];

	// see if we need to draw a box around the text
	// create the hilight button rectangle
	if ( (hScreenBtn->bAttributes & SBTN_CHAT_TYPE) == SBTN_CHAT_TYPE )	{
		rcScreenBtn.left   = hScreenBtn->ParentBox.x;
		rcScreenBtn.top    = hScreenBtn->TextBox.y - 2;
		rcScreenBtn.right  = rcScreenBtn.left + hScreenBtn->ParentBox.cx;
		rcScreenBtn.bottom = rcScreenBtn.top + hScreenBtn->TextBox.cy + 2;
		CursorOff(&rcScreenBtn);
		FillRectFront( &rcScreenBtn, refBGColor );
	}
	else	{
		rcScreenBtn.left   = hScreenBtn->ParentBox.x + PANEL_MARGIN;
		rcScreenBtn.top    = hScreenBtn->TextBox.y - 2;
		rcScreenBtn.right  = rcScreenBtn.left + hScreenBtn->ParentBox.cx - (PANEL_MARGIN<<1);
		rcScreenBtn.bottom = rcScreenBtn.top + hScreenBtn->TextBox.cy + 2;

		CursorOff(&rcScreenBtn);
		if ( hScreenBtn->bCapturingKeys || ((hScreenBtn->bAttributes & SBTN_EDIT_BOX) == SBTN_EDIT_BOX) )
//			                            || ((hScreenBtn->bAttributes & SBTN_KEY_TYPE) == SBTN_KEY_TYPE) )
		{
			FillRectFront( &rcScreenBtn, refBGColor );
		}
	}

	// now find the text rectangle
	xOffset = (hScreenBtn->TextBox.cx >> 1);
	if ( *hScreenBtn->pText )
	{
		if ( (hScreenBtn->bAttributes & SBTN_TEXT_CENTER) == SBTN_TEXT_CENTER )
		{
			textBox.x = 0;
			textBox.y = 0;
			if ( TextBox( hScreenBtn->pText, &textBox, hScreenBtn->nFontID ) )
			{
				// error: failed to acquire edit box size
				TRACE( "ERROR: failed to acquire edit box size [%s : %d]\n",
						__FILE__, __LINE__ );
				return;
			}
			xOffset = ((hScreenBtn->TextBox.cx - textBox.cx) >> 1);
		}
		else
			xOffset = 0;
	}
	else
	{
		if ( (hScreenBtn->bAttributes & SBTN_TEXT_CENTER) != SBTN_TEXT_CENTER )
			xOffset = 0;
	}

	rcScreenBtn.left   = hScreenBtn->TextBox.x + xOffset;
	rcScreenBtn.top    = hScreenBtn->TextBox.y;
	rcScreenBtn.right  = rcScreenBtn.left + hScreenBtn->TextBox.cx;
	rcScreenBtn.bottom = rcScreenBtn.top + hScreenBtn->TextBox.cy;

	// check for color overrides
	TextSetTransparent( FALSE );
	if ( (hScreenBtn->bAttributes & SBTN_DISABLED) == SBTN_DISABLED )
	{
		refFGColor = SBTNcolorTable[pArmyColors->DisabledColor];
		refBGColor = RGB_TRANSPARENT;
		TextSetTransparent( TRUE );
	}
	else
	if ( (hScreenBtn->eScreenBtnState != BUTTON_CLICKED) && (hScreenBtn->eScreenBtnState != BUTTON_EDIT) )
	{
		refBGColor = RGB_TRANSPARENT;
		TextSetTransparent( TRUE );
	}
	TextSetColors( refFGColor, refBGColor );

	// now draw the current text
	pScreenBtnRef = hScreenBtn->pText;
	pBox          = &(hScreenBtn->NullBox);
	if ( pScreenBtnRef[0] != '\0' )
	{
		TextWrite(	pFrontBuffer,
					rcScreenBtn.left + rcWindowScreen.left,
					rcScreenBtn.top + rcWindowScreen.top,
					pScreenBtnRef, hScreenBtn->nFontID, NULL );
	}
}

void	SBtnDisplayKeycodeBtn( HSCREENBTN hScreenBtn )
{
	COLORREF			refFGColor;
	COLORREF			refBGColor;
	SBTN_COLOR			eFGcolor;
	SBTN_COLOR			eBGcolor;
	RECT				rcScreenBtn;
	char*				pScreenBtnRef;
	SBTN_SCRN_COLORS*	pArmyColors;
	int					nColorIndex;

	// acquire the players army color
	nColorIndex = PlayerColor(ARMY_PLAYER);
	pArmyColors = ArmyInterfaceColors[ nColorIndex ];

	// get the button text, box, and color data
	pScreenBtnRef = hScreenBtn->pText;
	eBGcolor      = hScreenBtn->eBGColor;
	refBGColor    = SBTNcolorTable[eBGcolor];

	eFGcolor      = hScreenBtn->aFGColors[ hScreenBtn->eScreenBtnState ];
	refFGColor    = SBTNcolorTable[eFGcolor];

	// now find the text rectangle
//	xOffset = 0;
//	rcScreenBtn.left   = hScreenBtn->TextBox.x + xOffset;
	rcScreenBtn.left   = hScreenBtn->TextBox.x;
	rcScreenBtn.top    = hScreenBtn->TextBox.y;
	rcScreenBtn.right  = rcScreenBtn.left + hScreenBtn->TextBox.cx;
	rcScreenBtn.bottom = rcScreenBtn.top + hScreenBtn->TextBox.cy;

	CursorOff(&rcScreenBtn);

	// check for color overrides
	if ( eBGcolor == SBTN_TRANSPARENT )
		TextSetTransparent( TRUE );
	else
		TextSetTransparent( FALSE );

	if ( (hScreenBtn->bAttributes & SBTN_DISABLED) == SBTN_DISABLED )
	{
		refFGColor = SBTNcolorTable[pArmyColors->DisabledColor];
		refBGColor = RGB_TRANSPARENT;
	}
	else
	if ( hScreenBtn->eScreenBtnState != BUTTON_FOCUSED )
	{
		refBGColor = RGB_TRANSPARENT;
	}
	TextSetColors( refFGColor, refBGColor );

	// now draw the current text
	pScreenBtnRef = hScreenBtn->pText;
	if ( pScreenBtnRef[0] != '\0' )
	{
		TextWrite(	pFrontBuffer,
					rcScreenBtn.left + rcWindowScreen.left,
					rcScreenBtn.top + rcWindowScreen.top,
					pScreenBtnRef, hScreenBtn->nFontID, NULL );
	}

#ifdef	SCREEN_DEBUG
TRACE( "SCREENBTN (%s) Display Keycode: rcScreenBtn (%d,%d,%d,%d)\n",
	   pScreenBtnRef,
	   rcScreenBtn.left + rcWindowScreen.left,  rcScreenBtn.top + rcWindowScreen.top,
	   rcScreenBtn.right + rcWindowScreen.left, rcScreenBtn.bottom + rcWindowScreen.top
	 );
#endif
}

void	SBtnDoActions( void )
{
	int			nScreenBtn;
	SBTN_STATE	eSBtnState;
	HSCREENBTN		hScreenBtn;

	for( nScreenBtn=0; nScreenBtn<SBTNnextScreenBtn; ++nScreenBtn )
	{
		hScreenBtn = SBTNallScreenBtns[ nScreenBtn ];
		if ( hScreenBtn )
		{
			eSBtnState = SBtnGetState( hScreenBtn );
			SBtnExecuteCallback( hScreenBtn, eSBtnState );
		}
	}
}

BOOL	SBtnUpdate( HSCREENBTN hScreenBtn )
{
	SBTN_STATE	eSBtnState;
	BOOL		bStateChange;
	LONG		result;

	ASSERT ( hScreenBtn );

	eSBtnState = SBtnGetState( hScreenBtn );
	result     = SBtnExecuteCallback( hScreenBtn, eSBtnState );
	bStateChange = FALSE;
	if ( result == SBTN_STATE_CHANGE )
		bStateChange = TRUE;

	return( bStateChange );
}

BOOL	SBtnUpdateCheck( HSCREENBTN hScreenBtn )
{
	ASSERT( hScreenBtn );

	return( hScreenBtn->bUpdate );
}

HSCREENBTN	SBtnIsInButton( SPOINT* pPoint )
{
	int			nScreenBtn;
	BOOL		bFound;
	HSCREENBTN	hScreenBtn = NULL;

	// check all the buttons
	bFound  = FALSE;
	nScreenBtn = 0;
	while ( !bFound && ( nScreenBtn < SBTNnextScreenBtn ) )
	{
		hScreenBtn = SBTNallScreenBtns[ nScreenBtn ];
		if ( hScreenBtn->bAttributes &&
			((hScreenBtn->bAttributes & SBTN_INVISIBLE) != SBTN_INVISIBLE) &&
			((hScreenBtn->bAttributes & SBTN_DISABLED)  != SBTN_DISABLED) &&
			((hScreenBtn->bAttributes & SBTN_PASSIVE)   != SBTN_PASSIVE) &&
			((hScreenBtn->bAttributes & SBTN_NO_FOCUS)  != SBTN_NO_FOCUS)
		   )
		{
			if ( SBtnPointInScreenBtn( hScreenBtn, pPoint ) )
				bFound = TRUE;
			else
				++nScreenBtn;
		}
		else
			++nScreenBtn;
	}
	hScreenBtn = NULL;
	if ( bFound )
		hScreenBtn = SBTNallScreenBtns[ nScreenBtn ];

	return ( hScreenBtn );
}

void	SBtnResetAll( void )
{
	int		nScreenBtn;

	// check all the buttons
	for ( nScreenBtn=0; nScreenBtn<SBTNnextScreenBtn; ++nScreenBtn )
		SBtnSetState( SBTNallScreenBtns[ nScreenBtn ], BUTTON_NULL );
}

void	SBtnReset( HSCREENBTN hScreenBtn )
{
	SBtnSetState( hScreenBtn, BUTTON_NULL );
}

void	SBtnClearFocus( SPOINT* pPoint )
{
	if ( SBTNcurrentFocus && (SBTNcurrentFocus != SBTNcurrentClicked) )
	{
		if ( SBtnPointOutOfScreenBtn( SBTNcurrentFocus, pPoint ) )
			SBtnSetState( SBTNcurrentFocus, BUTTON_NULL );
	}
}

void	SBtnStore( HSCREENBTN hScreenBtn )
{
	if ( SBTNnextScreenBtn == SBTN_MAX_BTNS )
		ASSERT(0);
	SBTNallScreenBtns[ SBTNnextScreenBtn ] = hScreenBtn;
	++SBTNnextScreenBtn;

#ifdef SBTN_DEBUG
	SBtnDump( hScreenBtn );
#endif
}

void	SBtnRemove( HSCREENBTN hScreenBtn )
{
	BOOL	bFound;
	int		nScreenBtn;
	int		nScreenBtn2;

	bFound  = FALSE;
	nScreenBtn = 0;
	while( !bFound && (nScreenBtn<SBTNnextScreenBtn) )
	{
		if ( SBTNallScreenBtns[ nScreenBtn ] == hScreenBtn )
			bFound = TRUE;
		else
			++nScreenBtn;
	}
	if ( bFound )
	{
		// clear the entry
		SBTNallScreenBtns[ nScreenBtn ] = NULL;

		// Compress the list
		for( nScreenBtn2=nScreenBtn; nScreenBtn2<(SBTNnextScreenBtn-1); ++nScreenBtn2 )
			SBTNallScreenBtns[ nScreenBtn2 ] = SBTNallScreenBtns[ nScreenBtn2+1 ];

		// reduce the count
		--SBTNnextScreenBtn;
		SBTNallScreenBtns[ SBTNnextScreenBtn ] = NULL;
	}
}

BOOL	SBtnIsSpecial( HSCREENBTN hScreenBtn )
{
	BOOL	bIsSpecial = FALSE;		// assume not a special button

	if ( (hScreenBtn->bAttributes & SBTN_SPCL_OK) == SBTN_SPCL_OK )
		bIsSpecial = TRUE;
	else
	if ( (hScreenBtn->bAttributes & SBTN_SPCL_CANCEL) == SBTN_SPCL_CANCEL )
		bIsSpecial = TRUE;
	else
	if ( (hScreenBtn->bAttributes & SBTN_SPCL_NEXT) == SBTN_SPCL_NEXT )
		bIsSpecial = TRUE;
	else
	if ( (hScreenBtn->bAttributes & SBTN_SPCL_BACK) == SBTN_SPCL_BACK )
		bIsSpecial = TRUE;
	else
	if ( (hScreenBtn->bAttributes & SBTN_SPCL_FINISH) == SBTN_SPCL_FINISH )
		bIsSpecial = TRUE;

	return( bIsSpecial );
}

int	SBtnSpecialIndex( ULONG bAttributes )
{
	int	nSpclIndex = -1;		// assume not a special button

	if ( (bAttributes & SBTN_SPCL_OK) == SBTN_SPCL_OK )
		nSpclIndex = SBTN_OK;
	else
	if ( (bAttributes & SBTN_SPCL_CANCEL) == SBTN_SPCL_CANCEL )
		nSpclIndex = SBTN_CANCEL;
	else
	if ( (bAttributes & SBTN_SPCL_NEXT) == SBTN_SPCL_NEXT )
		nSpclIndex = SBTN_NEXT;
	else
	if ( (bAttributes & SBTN_SPCL_BACK) == SBTN_SPCL_BACK )
		nSpclIndex = SBTN_BACK;
	else
	if ( (bAttributes & SBTN_SPCL_FINISH) == SBTN_SPCL_FINISH )
		nSpclIndex = SBTN_FINISH;

	return( nSpclIndex );
}

HSCREENBTN	SBtnLoadDef( SCREENBTNDEF* pScreenBtnDef, SBOX* pParentBox )
{
	HSCREENBTN	hScreenBtn;
	int			nSpclIndex;

	if ( SBtnIsSpecial( (HSCREENBTN)pScreenBtnDef ) )
	{
		nSpclIndex = SBtnSpecialIndex( pScreenBtnDef->bAttributes );
		ASSERT( nSpclIndex >= 0 );
		hScreenBtn = SBTNspecialScreenBtns[ nSpclIndex ];
	}
	else
	{
		// start by allocating a screenBtn
		hScreenBtn = SBtnCreate( &(pScreenBtnDef->position),
								 pScreenBtnDef->bAttributes,
								 pParentBox
							   );
		if ( !hScreenBtn )
			goto exit;

		// determine what type of screenBtn this is from the attributes
		if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE) == SBTN_ICON_TYPE )
			SBtnLoadIconDef( hScreenBtn, pScreenBtnDef );

		if ( (hScreenBtn->bAttributes & SBTN_TEXT_TYPE) == SBTN_TEXT_TYPE )
			SBtnLoadTextDef( hScreenBtn, pScreenBtnDef );

		if ( (hScreenBtn->bAttributes & SBTN_EDIT_TYPE) == SBTN_EDIT_TYPE )
			SBtnLoadEditDef( hScreenBtn, pScreenBtnDef );
		else
		if ( (hScreenBtn->bAttributes & SBTN_CHAT_TYPE) == SBTN_CHAT_TYPE )
			SBtnLoadEditDef( hScreenBtn, pScreenBtnDef );
		else
		if ( (hScreenBtn->bAttributes & SBTN_KEY_TYPE) == SBTN_KEY_TYPE )
			SBtnLoadEditDef( hScreenBtn, pScreenBtnDef );

		SBtnSetData( hScreenBtn, pScreenBtnDef->dwData );

		SBtnSetCallback( hScreenBtn, BUTTON_CLICKED, (LPVOID)(pScreenBtnDef->pCallback) );
	}

exit:
	return( hScreenBtn);
}

void	SBtnLoadSpclDef( SCREENBTNDEF* pScreenBtnDef, int nSpclIndex )
{
	HSCREENBTN			hScreenBtn;
	SBTN_SCRN_COLORS*	pArmyColors;
	int					nColorIndex;

	// create an OK button from a static SCREENBTNDEF
	SBTNspecialScreenBtns[ nSpclIndex ] = SBtnCreate( &(pScreenBtnDef->position),
												   pScreenBtnDef->bAttributes,
												   &SPCLBox
												 );
	hScreenBtn                          = SBTNspecialScreenBtns[ nSpclIndex ];
	ASSERT( hScreenBtn );

	// acquire the players army color
	nColorIndex = PlayerColor(ARMY_PLAYER);
	pArmyColors = ArmyInterfaceColors[ nColorIndex ];

	SBtnSetFont( hScreenBtn, pScreenBtnDef->nFontID );
	SBtnSetBGColor( hScreenBtn, pScreenBtnDef->eBGColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_NULL,     pArmyColors->NullColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_FOCUSED,  pArmyColors->FocusColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_CLICKED,  pArmyColors->ClickedColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_EDIT,     pArmyColors->ClickedColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_DISABLED, pArmyColors->DisabledColor );
	SBtnSetBox( hScreenBtn, BUTTON_NULL,    &(pScreenBtnDef->defaultBox) );
	SBtnSetBox( hScreenBtn, BUTTON_FOCUSED, &(pScreenBtnDef->defaultBox) );
	SBtnSetBox( hScreenBtn, BUTTON_CLICKED, &(pScreenBtnDef->defaultBox) );
	SBtnSetText( hScreenBtn, pScreenBtnDef->pText );

#ifdef SBTN_DEBUG
	SBtnDump( hScreenBtn );
#endif
}

void	SBtnLoadTextDef( HSCREENBTN hScreenBtn, SCREENBTNDEF* pScreenBtnDef )
{
	SBTN_SCRN_COLORS*	pArmyColors;
	int					nColorIndex;
	SCRN_STATE			eScrnState;

	// create a TEXT button from a static SCREENBTNDEF
	ASSERT( hScreenBtn );

	// acquire the players army color
	eScrnState = ScrnGetState();
	if ( (eScrnState == SCRN_MULTI_HOST_STATE) || (eScrnState == SCRN_MULTI_REMOTE_STATE) )
		nColorIndex = LAST_COLOR_ARMY;
	else
		nColorIndex = PlayerColor(ARMY_PLAYER);
	pArmyColors = ArmyInterfaceColors[ nColorIndex ];

	SBtnSetFont( hScreenBtn, pScreenBtnDef->nFontID );
	SBtnSetBGColor( hScreenBtn, pScreenBtnDef->eBGColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_NULL,     pArmyColors->NullColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_FOCUSED,  pArmyColors->FocusColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_CLICKED,  pArmyColors->ClickedColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_EDIT,     pArmyColors->ClickedColor);
	SBtnSetFGColor( hScreenBtn, BUTTON_DISABLED, pArmyColors->DisabledColor );
	SBtnSetBox( hScreenBtn, BUTTON_NULL,    &(pScreenBtnDef->defaultBox) );
	SBtnSetBox( hScreenBtn, BUTTON_FOCUSED, &(pScreenBtnDef->defaultBox) );
	SBtnSetBox( hScreenBtn, BUTTON_CLICKED, &(pScreenBtnDef->defaultBox) );
	SBtnSetText( hScreenBtn, pScreenBtnDef->pText );
}

void	SBtnLoadIconDef( HSCREENBTN hScreenBtn, SCREENBTNDEF* pScreenBtnDef )
{
	// create an ICON button from a static SCREENBTNDEF
	ASSERT( hScreenBtn );

//	if ( (pScreenBtnDef->bAttributes & SBTN_ALLOW_OFFSET) == SBTN_ALLOW_OFFSET )
//		SBtnApplyOffset( hScreenBtn, &(pScreenBtnDef->position) ); 

	SBtnSetIcon( hScreenBtn, BUTTON_NULL,     pScreenBtnDef->pNullRef );
	SBtnSetIcon( hScreenBtn, BUTTON_FOCUSED,  pScreenBtnDef->pFocusedRef );
	SBtnSetIcon( hScreenBtn, BUTTON_CLICKED,  pScreenBtnDef->pClickedRef );
	SBtnSetIcon( hScreenBtn, BUTTON_DISABLED, pScreenBtnDef->pDisabledRef );
}

void	SBtnLoadEditDef( HSCREENBTN hScreenBtn, SCREENBTNDEF* pScreenBtnDef )
{
	LONG				xCenterBox;
	char				editText[ SBTN_TEXT_STRING_SIZE+1 ];
	SBOX				editBox;
	SBOX*				pBox;
	SBTN_SCRN_COLORS*	pArmyColors;
	int					nColorIndex;

	// create an EDIT button from a static SCREENBTNDEF

	// acquire the players army color
	nColorIndex = PlayerColor(ARMY_PLAYER);
	pArmyColors = ArmyInterfaceColors[ nColorIndex ];

	// start by creating a text button
	SBtnSetFont( hScreenBtn, pScreenBtnDef->nFontID );
	SBtnSetBGColor( hScreenBtn, pScreenBtnDef->eBGColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_NULL,     pArmyColors->NullColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_FOCUSED,  pArmyColors->FocusColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_CLICKED,  pArmyColors->ClickedColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_EDIT,     pArmyColors->ClickedColor);
	SBtnSetFGColor( hScreenBtn, BUTTON_DISABLED, pArmyColors->DisabledColor );
	SBtnSetBox( hScreenBtn, BUTTON_NULL,    &(pScreenBtnDef->defaultBox) );
	SBtnSetBox( hScreenBtn, BUTTON_FOCUSED, &(pScreenBtnDef->defaultBox) );
	SBtnSetBox( hScreenBtn, BUTTON_CLICKED, &(pScreenBtnDef->defaultBox) );
	hScreenBtn->nMaxEditChars = pScreenBtnDef->nMaxEditChars;
	SBtnSetText( hScreenBtn, pScreenBtnDef->pText );

	// now build in the edit specific data, fill a string with
	// capitol Ws and use this as the text box,
	if ( (hScreenBtn->bAttributes & SBTN_CHAT_TYPE) == SBTN_CHAT_TYPE )
	{
		if ( (hScreenBtn->nMaxEditChars == 0) || (hScreenBtn->nMaxEditChars > CHAT_MAX_WITH_NAME) )
			hScreenBtn->nMaxEditChars = CHAT_MAX_LENGTH;
	}
	else
	{
		if ( (hScreenBtn->nMaxEditChars == 0) || (hScreenBtn->nMaxEditChars > SBTN_MAX_PLAYER_NAME_LEN) )
			hScreenBtn->nMaxEditChars = SBTN_MAX_PLAYER_NAME_LEN;
	}
	memset( editText, 'W', hScreenBtn->nMaxEditChars-1 );
	editText[ hScreenBtn->nMaxEditChars ] = '\0';

	// acquire the area for this icon
	pBox      = &(hScreenBtn->ParentBox);
	editBox.x = 0;
	editBox.y = 0;
	if ( TextBox( editText, &editBox, hScreenBtn->nFontID ) )
	{
		// error: failed to acquire edit box size
		TRACE( "ERROR: failed to acquire edit box size [%s : %d]\n",
				__FILE__, __LINE__ );
		goto exit;
	}

	// now set the positional: center the text horizontally and
	// vertically about the center of the button box
	xCenterBox             = pBox->x + hScreenBtn->position.x +
							 ((pBox->cx - hScreenBtn->position.x)>>1);
	if ( (hScreenBtn->bAttributes & SBTN_TEXT_CENTER) == SBTN_TEXT_CENTER )
		hScreenBtn->TextBox.x  = xCenterBox - (editBox.cx>>1);
	else
		hScreenBtn->TextBox.x  = pBox->x + hScreenBtn->position.x;
	hScreenBtn->TextBox.y  = pBox->y + hScreenBtn->position.y;
	hScreenBtn->TextBox.cx = editBox.cx;
	hScreenBtn->TextBox.cy = editBox.cy;

#ifdef	SCREEN_DEBUG
TRACE( "SBtnLoadEditDef: TextBox (%d,%d,%d,%d )\n",
		hScreenBtn->TextBox.x,  hScreenBtn->TextBox.y,
		hScreenBtn->TextBox.cx, hScreenBtn->TextBox.cy
	 );
#endif

	hScreenBtn->pEditCallback = pScreenBtnDef->pCallback;

exit:
	ASSERT( hScreenBtn );
}

BOOL	SBtnInEditMode( HSCREENBTN hScreenBtn )
{
	return( hScreenBtn->bCapturingKeys );
}
	
void	SBtnApplyOffset( HSCREENBTN hScreenBtn, SPOINT* pOffset )
{
	if ( (hScreenBtn->bAttributes & SBTN_ALLOW_OFFSET) == SBTN_ALLOW_OFFSET )
	{
		// update the position and all the Box entries
		if ( (hScreenBtn->bAttributes & SBTN_KEY_TYPE) == SBTN_KEY_TYPE )
		{
			hScreenBtn->ParentBox.x  += pOffset->x;
			hScreenBtn->ParentBox.y  += pOffset->y;
		}
		else
		{
			hScreenBtn->position.x   += pOffset->x;
			hScreenBtn->position.y   += pOffset->y;
		}

		hScreenBtn->TextBox.x    += pOffset->x;
		hScreenBtn->TextBox.y    += pOffset->y;

		hScreenBtn->NullBox.x    += pOffset->x;
		hScreenBtn->NullBox.y    += pOffset->y;

		hScreenBtn->FocusedBox.x += pOffset->x;
		hScreenBtn->FocusedBox.y += pOffset->y;

		hScreenBtn->ClickedBox.x += pOffset->x;
		hScreenBtn->ClickedBox.y += pOffset->y;
	}
}

//================================================================
// ScreenBtns Load/Free routines
//================================================================
void	SBtnLoadOK( void )
{
	SBtnLoadSpclDef( &OK_ScreenBtn, SBTN_OK );
}

void	SBtnLoadCANCEL( void )
{
	SBtnLoadSpclDef( &CANCEL_ScreenBtn, SBTN_CANCEL );
}

void	SBtnLoadNEXT( void )
{
	SBtnLoadSpclDef( &NEXT_ScreenBtn, SBTN_NEXT );
}

void	SBtnLoadFINISH( void )
{
	SBtnLoadSpclDef( &FINISH_ScreenBtn, SBTN_FINISH );
}

void	SBtnFreeOK( void )
{
	SBtnFree( SBTNspecialScreenBtns[ SBTN_OK ] );
	SBTNspecialScreenBtns[ SBTN_OK ] = NULL;
}

void	SBtnFreeCANCEL( void )
{
	SBtnFree( SBTNspecialScreenBtns[ SBTN_CANCEL ] );
	SBTNspecialScreenBtns[ SBTN_CANCEL ] = NULL;
}

void	SBtnFreeNEXT( void )
{
	SBtnFree( SBTNspecialScreenBtns[ SBTN_NEXT ] );
	SBTNspecialScreenBtns[ SBTN_NEXT ] = NULL;
}

void	SBtnFreeBACK( void )
{
	SBtnFree( SBTNspecialScreenBtns[ SBTN_BACK ] );
	SBTNspecialScreenBtns[ SBTN_BACK ] = NULL;
}

void	SBtnFreeFINISH( void )
{
	SBtnFree( SBTNspecialScreenBtns[ SBTN_FINISH ] );
	SBTNspecialScreenBtns[ SBTN_FINISH ] = NULL;
}

//================================================================
//					EDIT BUTTON FUNCTIONS
//================================================================


BOOL SBtnHandleKey( UINT character )  //returns true if the character was used
{
	HSCREENBTN	hScreenBtn;
	int			len;
	int			nIndex;
	char		c         = character;
	BOOL		bCharUsed = FALSE;

	if ( !SBTNcurrentClicked )
		return( bCharUsed );

	hScreenBtn = SBTNcurrentClicked;

	len = strlen( hScreenBtn->pText );
	if (((c==CHAT_KEY_BACKSPACE) || (c==CHAT_KEY_RETURN) || (c==CHAT_KEY_DEL) ||
		((c>=CHAT_KEY_SPACE) && (c<=CHAT_KEY_MAX_LEGAL) && (c!='#'))) )
	{
		hScreenBtn->bTextHasArrived=TRUE;

		/*
		if (c==CHAT_KEY_DEL)		// delete DEL (clear text)
		{
			hScreenBtn->pText[0] = '_';
			hScreenBtn->pText[1] = '\0';
			hScreenBtn->bUpdate  = TRUE;
		}
		else
		*/
		if (c==CHAT_KEY_BACKSPACE)
		{
			if ( len-1 )
				--len;		// backup a character
			hScreenBtn->pText[len-1] = '_';
			hScreenBtn->pText[len]   = 0;
			hScreenBtn->bUpdate      = TRUE;
		}
		else
		if (c==CHAT_KEY_RETURN)
		{
			BOOL	bDone;

			// make sure the name string isn't NULL
			bDone = TRUE;
			len = strlen( hScreenBtn->pText ) - 1;	// minus 1 for the underscore

			// strip the underscore cursor
			if ( len )
				hScreenBtn->pText[len] = '\0';

			if ( len <= 0 )
			{
				bDone = FALSE;
				strcpy( hScreenBtn->pText, NEWPLAYER_TextBtn );
				strcat( hScreenBtn->pText, "_" );
				hScreenBtn->bUpdate = TRUE;
			}
			else
			if ( strncmp( hScreenBtn->pText, NEWPLAYER_TextBtn, NEWPLAYER_BtnSize ) == 0 )
			{
				// turn off the user key input processing
				SBtnTurnOffKeys( hScreenBtn );

				// set the button to FOCUSED state
				if ( SBTNcurrentClicked )
					SBtnSetState( SBTNcurrentClicked, BUTTON_FOCUSED );
				SBTNcurrentClicked = NULL;

				goto finishIt;
			}
			else	// verify that this new name doesn't already exist
			if ( StatsHaveName( hScreenBtn->pText ) )
			{
				bDone = FALSE;
				strcpy( hScreenBtn->pText, "Exists_" );
				hScreenBtn->bUpdate = TRUE;
			}

			if ( bDone )
			{
				// copy the current player name into the permanent set
				nIndex = hScreenBtn->dwData;
				StatSetPlayerNameIndex( nIndex );
				strcpy( STATcurrentName, hScreenBtn->pText );
				strcpy( STATplayerNames[ nIndex ], STATcurrentName );
				StatUpdate( nIndex, STAT_UPDATE_PLAYER_NAME, TRUE );

				if ( hScreenBtn->pEditCallback )
					hScreenBtn->pEditCallback( hScreenBtn );

				// turn off the user key input processing
				SBtnTurnOffKeys( hScreenBtn );

				hScreenBtn->hPrevClicked = hScreenBtn;

				ScrnOnPlayerNameNext( hScreenBtn );

				ScrnForceUpdate();
			}
			hScreenBtn->bUpdate = TRUE;
		}
		else 
		{
			if (len<SBTN_MAX_PLAYER_NAME_LEN-1 && TextWidth(hScreenBtn->pText, hScreenBtn->nFontID) < hScreenBtn->nMaxEditWidth)
			{
				hScreenBtn->pText[len-1] = c;
				hScreenBtn->pText[len]   = '_';
				hScreenBtn->pText[len+1] = '\0';
			}
			hScreenBtn->bUpdate = TRUE;
		}

finishIt:
		bCharUsed = TRUE;

	}
#ifdef	SCREEN_DEBUG
	else
		TRACE( "edit char = %d\n", character );
#endif

	return( bCharUsed );
}


void SBtnTurnOffKeys( HSCREENBTN hScreenBtn )
{
	if (hScreenBtn->bCapturingKeys)
	{
		hScreenBtn->bCapturingKeys = FALSE;
		pMainFrame->SetUICharHandler(NULL);

		// now go pick a misson
		hScreenBtn->hPrevClicked = hScreenBtn;
		if ( strncmp( hScreenBtn->pText, NEWPLAYER_TextBtn, NEWPLAYER_BtnSize ) == 0 )
		{
			SBtnSetState( hScreenBtn, BUTTON_NULL );
//			ScrnForceUpdate();
		}
		else
		if ( strcmp( hScreenBtn->pText, "_" ) == 0 )
		{
			strcpy( hScreenBtn->pText, NEWPLAYER_TextBtn );
			SBtnSetState( hScreenBtn, BUTTON_NULL );
//			ScrnForceUpdate();
		}

		ScrnForceUpdate();
//		else
//		if ( *hScreenBtn->pText )
//		{
//			strcpy( hScreenBtn->pText, NEWPLAYER_TextBtn );
//			SBtnSetState( hScreenBtn, BUTTON_NULL );
//			ScrnForceUpdate();
//		}
//		else
//			ScrnOnPlayerNameNext( hScreenBtn );
	}
}

void SBtnTurnOnKeys( HSCREENBTN hScreenBtn )
{
	int	len;

	if (!hScreenBtn->bCapturingKeys)
	{
		len = strlen( hScreenBtn->pText );
		if ( len < SBTN_MAX_PLAYER_NAME_LEN )
		{
			hScreenBtn->pText[len]   = '_';
			hScreenBtn->pText[len+1] = '\0';
		}

		hScreenBtn->nMaxEditWidth = 200;
		hScreenBtn->bCapturingKeys = EDIT_CAPTURE;
		pMainFrame->SetUICharHandler(SBtnHandleKey);
		SBTNcurrentClicked         = hScreenBtn;

		// force an update of this button
		hScreenBtn->bUpdate = TRUE;
	}
}

void	SBtnSetCurrentClicked( HSCREENBTN hScreenBtn )
{
	SBTNcurrentClicked = hScreenBtn;
}

HSCREENBTN	SBtnGetCurrentClicked( void )
{
	return( SBTNcurrentClicked );
}

//================================================================
//					CHAT BUTTON FUNCTIONS
//================================================================


BOOL SBtnChatHandleKey(UINT character)  //returns true if the character was used
{
	HSCREENBTN			hScreenBtn;
	int					len;
	char				c=character;

	hScreenBtn = SBtnGetCurrentClicked();
	if ( !hScreenBtn )
		return FALSE;

	if ( c == CHAT_KEY_ESCAPE )
	{
		SBtnChatTurnOffKeys( hScreenBtn );
		ScrnForceUpdate();
		return( TRUE );
	}

	len = strlen( hScreenBtn->pText );
	if (((c==CHAT_KEY_BACKSPACE) || (c==CHAT_KEY_RETURN) || (c==CHAT_KEY_DEL) ||
		((c>=CHAT_KEY_SPACE) && (c<=CHAT_KEY_MAX_LEGAL) && (c!='#'))) )
	{
		hScreenBtn->bTextHasArrived=TRUE;

		/*
		if (c==CHAT_KEY_DEL)		// delete DEL (clear text)
		{
			hScreenBtn->pText[0] = '_';
			hScreenBtn->pText[1] = '\0';
			hScreenBtn->bUpdate  = TRUE;
		}
		else
		*/
		if (c==CHAT_KEY_BACKSPACE)
		{
			if ( len-1 ) --len;		// backup a character
			hScreenBtn->pText[len-1] = '_';
			hScreenBtn->pText[len]   = 0;
			hScreenBtn->bUpdate      = TRUE;
		}
		else
		if (c==CHAT_KEY_RETURN)
		{
			//send message
			hScreenBtn->pText[len-1] = '\0';	// remove the underscore
			if (hScreenBtn->pText[0])
				ScrnSendChatMessage( hScreenBtn, TRUE );
			hScreenBtn->pText[0] = '\0';
			hScreenBtn->bUpdate = TRUE;
		}
		else 
		{
			if (len<CHAT_MAX_LENGTH-1 && TextWidth(hScreenBtn->pText, hScreenBtn->nFontID) < hScreenBtn->nMaxEditWidth)
			{
				hScreenBtn->pText[len-1] = c;
				hScreenBtn->pText[len]   = '_';
				hScreenBtn->pText[len+1] = '\0';
			}
			else
			{
				//send message
				hScreenBtn->pText[len-1] = c;
				hScreenBtn->pText[len]   = '\0';
				ScrnSendChatMessage( hScreenBtn, FALSE );
			}
			hScreenBtn->bUpdate = TRUE;
		}
		return TRUE;
	}
	return FALSE;
}


void SBtnChatTurnOffKeys( HSCREENBTN hScreenBtn )
{
	int	len;
	if (hScreenBtn->bCapturingKeys)
	{
		hScreenBtn->bCapturingKeys=FALSE;
		pMainFrame->SetUICharHandler(NULL);
		if ( *hScreenBtn->pText )
		{
			len = strlen( hScreenBtn->pText );
			if ( len )		// clear the underscore
				hScreenBtn->pText[0] = '\0';
		}
	}
	SBtnSetState( SBTNcurrentClicked, BUTTON_NULL );
	SBTNcurrentClicked = NULL;
}

void SBtnChatTurnOnKeys( HSCREENBTN hScreenBtn )
{
	char tempbuffer[CHAT_MAX_LENGTH];
	int	len;

	if (!hScreenBtn->bCapturingKeys)
	{
		len = strlen( hScreenBtn->pText );
		if ( len < CHAT_MAX_LENGTH-1 )
		{
			hScreenBtn->pText[len]   = '_';
			hScreenBtn->pText[len+1] = '\0';
		}

		strcpy(tempbuffer, gpComm->m_PlayerName[ARMY_PLAYER]);
		strcat(tempbuffer, ": ");
		hScreenBtn->nMaxEditWidth = CHAT_MAX_WIDTH - TextWidth(tempbuffer, hScreenBtn->nFontID);

		hScreenBtn->bCapturingKeys=EDIT_CAPTURE;
		pMainFrame->SetUICharHandler(SBtnChatHandleKey);
	}
}

void	ScrnSendChatMessage( HSCREENBTN hScreenBtn, BOOL bTurnOff )
{
	char tempbuffer[CHAT_MAX_WITH_NAME+5];
	unsigned char		chatMask=0; //who you're sending chat messages to.

	//append the proper color header
	tempbuffer[0]=gpComm->GetArmyIndex(ARMY_PLAYER)+1;
//	tempbuffer[0]=SBtnPlayerColor( PlayerColor(ARMY_PLAYER) );
//	tempbuffer[0]=PlayerColor(ARMY_PLAYER) + 1;

	// now insert the players Name
	strcpy(tempbuffer+1, gpComm->m_PlayerName[ARMY_PLAYER]);
	strcat(tempbuffer+1, ": ");

	// pass the string to proper update mechanism
	strcat(tempbuffer+1, hScreenBtn->pText);
	ScrnReceiveChatMessage(tempbuffer);

	// turn off the user input processing
	if ( bTurnOff )
		SBtnChatTurnOffKeys( hScreenBtn );
	else
	{
		hScreenBtn->pText[0] = '_';
		hScreenBtn->pText[1] = '\0';
	}

	// finally, send the chat message out to all
	// the other players
	SendChatMessage( tempbuffer );	// broadcast to all players
}

//================================================================
//					KEYCODE CONFIG BUTTON FUNCTIONS
//================================================================

void SBtnKeycodeProcess(BYTE character)
{
	HSCREENOBJ		hScreenObj;
	HSCREENBTN		hScreenBtn;
	HSCREENBTN		hDuplicateBtn;
	char*			pKeycodeName;
	int				nKeyIndex;
	int				nIndex;
	DWORD			dwData;							// button user data
	BOOL			bSarge;
	BYTE			c = character;

	hScreenBtn = SBtnGetCurrentClicked();
	if ( !hScreenBtn )
		return;

	if ( hScreenBtn->bCapturingKeys == JOYSTICK_CAPTURE )
	{
		if ( c == DIK_ESCAPE )
			SBtnJoystickProcess(ESC_KEY);
		return;
	}
	else if ( hScreenBtn->bCapturingKeys == KEYBOARD_CAPTURE )
	{
		// determine which table we are effecting
		dwData = hScreenBtn->dwData;
		if ( (dwData & GAME_KEY_FLAG) )		// GamePlayKeycodes
			bSarge = FALSE;
		else
			bSarge = TRUE;
		nKeyIndex = (dwData & 0xFF);

		if ( c != DIK_ESCAPE )
		{
			// first look through the Sarge keys looking for Duplicates and Fixed keys
			nIndex    = 0;
			while ( GamePlayKeyDescs[nIndex].dispatcher )
			{
				if ( (nIndex != nKeyIndex) || bSarge )
				{
					if ( GamePlayKeyDescs[nIndex].FixedKey == c || !KeysText[c] )
					{
						audioPlay( BULLET_HIT_OBJECT, SND_SFX_FLAG | SND_DELETE_FLAG );
						return;
					}
					else if ( GamePlayKeyDescs[nIndex].CustomKey == c )
					{
						audioPlay( BULLET_HIT_OBJECT, SND_SFX_FLAG | SND_DELETE_FLAG );
						GamePlayKeyDescs[nIndex].CustomKey = 0;

						// find the screen button for this duplicate and force and update
						hScreenObj             = SCRNfullScreen->pScreenObjs[GAME_KEY_START_INDEX+nIndex];
						hScreenObj->bUpdate    = TRUE;
						hDuplicateBtn          = hScreenObj->hScreenBtns[1];

						pKeycodeName = "undefined";
						SBtnSetText( hDuplicateBtn, pKeycodeName );

						hDuplicateBtn->bUpdate = TRUE;
					}
				}
				++nIndex;
			}
			nIndex    = 0;
			while ( SargeKeyDescs[nIndex].dispatcher )
			{
				if ( (nIndex != nKeyIndex) || !bSarge )
				{
					if ( SargeKeyDescs[nIndex].FixedKey == c )
					{
						audioPlay( BULLET_HIT_OBJECT, SND_SFX_FLAG | SND_DELETE_FLAG );
						return;
					}
					else if ( SargeKeyDescs[nIndex].CustomKey == c )
					{
						audioPlay( BULLET_HIT_OBJECT, SND_SFX_FLAG | SND_DELETE_FLAG );
						SargeKeyDescs[nIndex].CustomKey = 0;

						// find the screen button for this duplicate and force an update
						hScreenObj             = SCRNfullScreen->pScreenObjs[SARGE_KEY_START_INDEX+nIndex];
						hScreenObj->bUpdate    = TRUE;
						hDuplicateBtn          = hScreenObj->hScreenBtns[1];

						// match the keycode to the text equivalent
						pKeycodeName = "undefined";
						SBtnSetText( hDuplicateBtn, pKeycodeName );

						hDuplicateBtn->bUpdate = TRUE;
					}
				}
				++nIndex;
			}

			if ( bSarge )
			{
				SargeKeyDescs[nKeyIndex].CustomKey = c;
			}
			else
			{
				GamePlayKeyDescs[nKeyIndex].CustomKey = c;
			}
		}
		else
		{
			if ( bSarge )
				c = SargeKeyDescs[nKeyIndex].CustomKey;
			else
				c = GamePlayKeyDescs[nKeyIndex].CustomKey;
		}

		// match the keycode to the text equivalent
		pKeycodeName = SBtnKeycodeName( c );
		SBtnSetText( hScreenBtn, pKeycodeName );
		hScreenBtn->bUpdate      = TRUE;

		// now turn off this handler
		SBtnKeycodeTurnOffKeys( hScreenBtn );
	}
}

void	SBtnJoystickProcess(BYTE button)
{
	HSCREENOBJ			hScreenObj;
	HSCREENBTN			hScreenBtn;
	HSCREENBTN			hDuplicateBtn;
	char				b=button;
	char*				pKeycodeName;
	int					nIndex;
	DWORD				dwData;			// button user data
	int					nKeyIndex;

	hScreenBtn = SBtnGetCurrentClicked();
	if ( !hScreenBtn )
		return;

	dwData = hScreenBtn->dwData;			// button user data
	nKeyIndex = (dwData & 0xFF);

	if ( hScreenBtn->bCapturingKeys == JOYSTICK_CAPTURE )
	{
		if (b != ESC_KEY)
		{
			// change the data in the description table
			// first verify that this key is not a duplicate of another command
			nIndex    = 0;
			while (JoystickDescs[nIndex].dispatcher)
			{
				if ( nIndex != nKeyIndex )
				{
					if ( JoystickDescs[nIndex].CustomKey == b )
					{
						audioPlay( BULLET_HIT_OBJECT, SND_SFX_FLAG | SND_DELETE_FLAG );
						JoystickDescs[nIndex].CustomKey = 0;

						// find the screen button for this duplicate and force and update
						hScreenObj             = SCRNfullScreen->pScreenObjs[JOYSTICK_BUTTON_START_INDEX+nIndex];
						hScreenObj->bUpdate    = TRUE;
						hDuplicateBtn          = hScreenObj->hScreenBtns[1];

						pKeycodeName = "undefined";
						SBtnSetText( hDuplicateBtn, pKeycodeName );

						hDuplicateBtn->bUpdate = TRUE;
					}
				}
				++nIndex;
			}
			JoystickDescs[nKeyIndex].CustomKey = b;
		}
		else
			b = JoystickDescs[nKeyIndex].CustomKey;

		// match the button to the text equivalent
		pKeycodeName = GetJoystickButtonStr( b );
		SBtnSetText( hScreenBtn, pKeycodeName );
		hScreenBtn->bUpdate      = TRUE;

		// now turn off this handler
		SBtnKeycodeTurnOffKeys( hScreenBtn );
	}
}


void SBtnKeycodeTurnOffKeys( HSCREENBTN hScreenBtn )
{
	if (hScreenBtn->bCapturingKeys)
	{
		hScreenBtn->bCapturingKeys=FALSE;
		pMainFrame->SetUICharHandler(NULL);

		SObjSetConFigColor( hScreenBtn, TRUE );
	}
	SBtnSetState( SBTNcurrentClicked, BUTTON_NULL );
	SBTNcurrentClicked = NULL;

	// force an unpdate of the entire screen
	ScrnForceUpdate();
}

void SBtnKeycodeTurnOnKeys( HSCREENBTN hScreenBtn )
{
	if (!hScreenBtn->bCapturingKeys)
	{
		// set the capture mode
		hScreenBtn->bCapturingKeys=KEYBOARD_CAPTURE;
		pMainFrame->SetUICharHandler(NULL);

		SObjSetConFigColor( hScreenBtn, FALSE );
	}
}

void SBtnJoystickTurnOnKeys( HSCREENBTN hScreenBtn )
{
	if (!hScreenBtn->bCapturingKeys)
	{
		hScreenBtn->bCapturingKeys=JOYSTICK_CAPTURE;
		pMainFrame->SetUICharHandler(NULL);

		SObjSetConFigColor( hScreenBtn, FALSE );
	}
}

char	KeyBuffer[16];

char* SBtnKeycodeName( unsigned char c )
{
	char*	pKeycodeName = KeysText[ c ];
	if ( !pKeycodeName )
	{
		KeyBuffer[0] = c;
		KeyBuffer[1] = '\0';

		pKeycodeName = KeyBuffer;
	}

	if ( !pKeycodeName[0] )
		pKeycodeName = "undefined";

	return( pKeycodeName );
}

unsigned char SBTNplayerBmpTextLookUp[] =
{
	3,			// BROWN_IDX
	2,			// GREEN_IDX
	12,			// BLUE_IDX
	7,			// GREY_IDX
	2			// MULTIPLAYER
};

extern	int messageColorIndices[4];

unsigned char	SBtnPlayerColor( SHORT nPlayerIndex )
{
//	return( SBTNplayerBmpTextLookUp[ nPlayerIndex ] );
	return( messageColorIndices[ nPlayerIndex ] );
}

//========================================================================
//	Function:		SBtnDumpAll()
//
//	Description:
//		display all active button data.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	SBtnDumpAll( void )
{
	int			nScreenBtn;
	HSCREENBTN	hScreenBtn;

	// remove any linering normal screenbtns
	for( nScreenBtn=0; nScreenBtn<SBTNnextScreenBtn; ++nScreenBtn )
	{
		TRACE( "ScreenBtn %d:\n", nScreenBtn );

		hScreenBtn = SBTNallScreenBtns[ nScreenBtn ];
		SBtnDump( hScreenBtn );
	}
}

//========================================================================
//	Function:		SBtnDump()
//
//	Description:
//		terminate and clear the ScreenBtn processing.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	SBtnDump( HSCREENBTN hScreenBtn )
{

	if ( hScreenBtn )
	{
		// dump the attributes
		TRACE( "    Attributes:            " );
		if ( hScreenBtn->bAttributes                       == SBTN_CLEAR )
			TRACE( "SBTN_CLEAR " );
		if ( (hScreenBtn->bAttributes & SBTN_INVISIBLE)    == SBTN_INVISIBLE )
			TRACE( "SBTN_INVISIBLE " );
		if ( (hScreenBtn->bAttributes & SBTN_DISABLED)     == SBTN_DISABLED )
			TRACE( "SBTN_DISABLED " );
		if ( (hScreenBtn->bAttributes & SBTN_NO_FOCUS)     == SBTN_NO_FOCUS )
			TRACE( "SBTN_NO_FOCUS " );
		if ( (hScreenBtn->bAttributes & SBTN_PASSIVE)      == SBTN_PASSIVE )
			TRACE( "SBTN_PASSIVE " );
		if ( (hScreenBtn->bAttributes & SBTN_SPCL_OK)      == SBTN_SPCL_OK )
			TRACE( "SBTN_SPCL_OK " );
		if ( (hScreenBtn->bAttributes & SBTN_SPCL_CANCEL)  == SBTN_SPCL_CANCEL )
			TRACE( "SBTN_SPCL_CANCEL " );
		if ( (hScreenBtn->bAttributes & SBTN_SPCL_NEXT)    == SBTN_SPCL_NEXT )
			TRACE( "SBTN_SPCL_NEXT " );
		if ( (hScreenBtn->bAttributes & SBTN_SPCL_BACK)    == SBTN_SPCL_BACK )
			TRACE( "SBTN_SPCL_BACK " );
		if ( (hScreenBtn->bAttributes & SBTN_SPCL_FINISH)  == SBTN_SPCL_FINISH )
			TRACE( "SBTN_SPCL_FINISH " );
		if ( (hScreenBtn->bAttributes & SBTN_MORE)         == SBTN_MORE )
			TRACE( "SBTN_MORE " );
		if ( (hScreenBtn->bAttributes & SBTN_ALLOW_OFFSET) == SBTN_ALLOW_OFFSET )
			TRACE( "SBTN_ALLOW_OFFSET " );
		if ( (hScreenBtn->bAttributes & SBTN_ICON_TYPE)    == SBTN_ICON_TYPE )
			TRACE( "SBTN_ICON_TYPE " );
		if ( (hScreenBtn->bAttributes & SBTN_TEXT_HILITE)  == SBTN_TEXT_HILITE )
			TRACE( "SBTN_TEXT_HILITE " );
		if ( (hScreenBtn->bAttributes & SBTN_TEXT_CENTER)  == SBTN_TEXT_CENTER )
			TRACE( "SBTN_TEXT_CENTER " );
		if ( (hScreenBtn->bAttributes & SBTN_TEXT_TYPE)    == SBTN_TEXT_TYPE )
			TRACE( "SBTN_TEXT_TYPE " );
		if ( (hScreenBtn->bAttributes & SBTN_KEY_TYPE)    == SBTN_KEY_TYPE )
			TRACE( "SBTN_KEY_TYPE " );
		if ( (hScreenBtn->bAttributes & SBTN_EDIT_BOX)     == SBTN_EDIT_BOX )
			TRACE( "SBTN_EDIT_BOX " );
		if ( (hScreenBtn->bAttributes & SBTN_EDIT_TYPE)    == SBTN_EDIT_TYPE )
			TRACE( "SBTN_EDIT_TYPE " );
		if ( (hScreenBtn->bAttributes & SBTN_CHAT_TYPE)    == SBTN_CHAT_TYPE )
			TRACE( "SBTN_CHAT_TYPE " );
		TRACE( "\n" );

		if ( hScreenBtn->bAttributes &&
			 ((hScreenBtn->bAttributes & SBTN_INVISIBLE) != SBTN_INVISIBLE) )
		{
			// display the button current state
			TRACE( "    Button Current State:  " );
			if ( hScreenBtn->eScreenBtnState == BUTTON_NULL )
				TRACE( "BUTTON_NULL " );
			if ( hScreenBtn->eScreenBtnState == BUTTON_FOCUSED )
				TRACE( "BUTTON_FOCUSED " );
			if ( hScreenBtn->eScreenBtnState == BUTTON_CLICKED )
				TRACE( "BUTTON_CLICKED " );
			if ( hScreenBtn->eScreenBtnState == BUTTON_EDIT )
				TRACE( "BUTTON_EDIT " );
			if ( hScreenBtn->eScreenBtnState == BUTTON_DISABLED )
				TRACE( "BUTTON_DISABLED " );
			TRACE( "\n" );

			// display the button previous state
			TRACE( "    Button Previous State: " );
			if ( hScreenBtn->ePrevScreenBtnState == BUTTON_NULL )
				TRACE( "BUTTON_NULL " );
			if ( hScreenBtn->ePrevScreenBtnState == BUTTON_FOCUSED )
				TRACE( "BUTTON_FOCUSED " );
			if ( hScreenBtn->ePrevScreenBtnState == BUTTON_CLICKED )
				TRACE( "BUTTON_CLICKED " );
			if ( hScreenBtn->ePrevScreenBtnState == BUTTON_EDIT )
				TRACE( "BUTTON_EDIT " );
			if ( hScreenBtn->ePrevScreenBtnState == BUTTON_DISABLED )
				TRACE( "BUTTON_DISABLED " );
			TRACE( "\n" );

			// display the FontID, FG and BG color
			TRACE( "    FontID:                %d\n", hScreenBtn->nFontID );
			TRACE( "    BG Colors:             %s\n", SBtnColorName( hScreenBtn->eBGColor ) );
			TRACE( "    FG Color:              " );
			for( int i=0; i<BUTTON_LAST_STATE; ++i )
				TRACE( "%s ", SBtnColorName( hScreenBtn->aFGColors[i]) );
			TRACE( "\n" );

			// validate callbacks and dwData
			if ( hScreenBtn->pNullCallback )
				TRACE( "    NULL Callback:         %ld\n", hScreenBtn->pNullCallback );
			if ( hScreenBtn->pFocusedCallback )
				TRACE( "    FOCUSES Callback:      %ld\n", hScreenBtn->pFocusedCallback );
			if ( hScreenBtn->pClickedCallback )
				TRACE( "    CLICKED Callback:      %ld\n", hScreenBtn->pClickedCallback );
			if ( hScreenBtn->pEditCallback )
				TRACE( "    EDIT Callback:         %ld\n", hScreenBtn->pEditCallback );
			TRACE( "    Button Data:           %ld\n", hScreenBtn->dwData );

			// does it need an update
			TRACE( "    Button Update:         %s\n", ((hScreenBtn->bUpdate) ? "TRUE" : "FALSE") );

			// display the position, text, references, and Resource IDs
			TRACE( "    Button Position:       (%d,%d)\n", hScreenBtn->position.x, hScreenBtn->position.y );
			TRACE( "    Button Text:           [%s]\n", hScreenBtn->pText );
			TRACE( "    NULL Reference:        [%s]\n", hScreenBtn->pNullRef );
			TRACE( "    FOCUSED Reference:     [%s]\n", hScreenBtn->pFocusedRef );
			TRACE( "    CLICKED Reference:     [%s]\n", hScreenBtn->pClickedRef );
			TRACE( "    NULL Resource ID:      [%s]\n", hScreenBtn->NullResourceID );
			TRACE( "    FOCUSED Resource ID:   [%s]\n", hScreenBtn->FocusedResourceID );
			TRACE( "    CLICKED Resource ID:   [%s]\n", hScreenBtn->ClickedResourceID );

			TRACE( "    Parent Box:            (x:%d,y:%d,w:%d,h:%d)\n",
					hScreenBtn->ParentBox.x,  hScreenBtn->ParentBox.y,
					hScreenBtn->ParentBox.cx, hScreenBtn->ParentBox.cy );
			TRACE( "    Text Box:              (x:%d,y:%d,w:%d,h:%d)\n",
					hScreenBtn->TextBox.x,  hScreenBtn->TextBox.y,
					hScreenBtn->TextBox.cx, hScreenBtn->TextBox.cy );
			TRACE( "    NULL Box:              (x:%d,y:%d,w:%d,h:%d)\n",
					hScreenBtn->NullBox.x,  hScreenBtn->NullBox.y,
					hScreenBtn->NullBox.cx, hScreenBtn->NullBox.cy );
			TRACE( "    FOCUSED Box:           (x:%d,y:%d,w:%d,h:%d)\n",
					hScreenBtn->FocusedBox.x,  hScreenBtn->FocusedBox.y,
					hScreenBtn->FocusedBox.cx, hScreenBtn->FocusedBox.cy );
			TRACE( "    CLICKED Box:           (x:%d,y:%d,w:%d,h:%d)\n",
					hScreenBtn->ClickedBox.x,  hScreenBtn->ClickedBox.y,
					hScreenBtn->ClickedBox.cx, hScreenBtn->ClickedBox.cy );

			// display edit fields
			TRACE( "    Text Has Arrived:      %s\n", ((hScreenBtn->bTextHasArrived) ? "TRUE" : "FALSE") );
			TRACE( "    Capturing keys:        %s\n", ((hScreenBtn->bCapturingKeys) ? "TRUE" : "FALSE") );
			TRACE( "    Max Edit Chars:        %d\n\n", hScreenBtn->nMaxEditChars );
		}
	}
}

//========================================================================
//	Function:		SBtnColorName()
//
//	Description:
//		terminate and clear the ScreenBtn processing.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

char*	SBtnColorName( SBTN_COLOR eColor )
{
	switch( eColor )
	{
	case SBTN_TRANSPARENT: return( "SBTN_TRANSPARENT" );
	case SBTN_BLACK:       return( "SBTN_BLACK" );
	case SBTN_DK_RED:      return( "SBTN_DK_RED" );
	case SBTN_DK_GREEN:    return( "SBTN_DK_GREEN" );
	case SBTN_BROWN:       return( "SBTN_BROWN" );
	case SBTN_DK_BLUE:     return( "SBTN_DK_BLUE" );
	case SBTN_DK_MAGENTA:  return( "SBTN_DK_MAGENTA" );
	case SBTN_DK_CYAN:     return( "SBTN_DK_CYAN" );
	case SBTN_GREY:        return( "SBTN_GREY" );
	case SBTN_DK_GREY:     return( "SBTN_DK_GREY" );
	case SBTN_RED:         return( "SBTN_RED" );
	case SBTN_GREEN:       return( "SBTN_GREEN" );
	case SBTN_YELLOW:      return( "SBTN_YELLOW" );
	case SBTN_BLUE:        return( "SBTN_BLUE" );
	case SBTN_MAGENTA:     return( "SBTN_MAGENTA" );
	case SBTN_CYAN:        return( "SBTN_CYAN" );
	case SBTN_WHITE:       return( "SBTN_WHITE" );
	default:               return( "ILLEGAL" );
	}
}

//========================================================================
//							EOF
//========================================================================
