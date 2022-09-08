//========================================================================
//	FILE:			$Workfile: ScreenBtn.h $
//
//	DESCRIPTION:	ArmyMen Button Class definition.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, October 1, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ScreenBtn.h 36    3/24/98 5:23p Nrobinso $
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
//  $Log: /ArmyMen/src/ScreenBtn.h $
//  
//  36    3/24/98 5:23p Nrobinso
//  change player name length
//  
//  35    3/17/98 11:22a Aburgess
//  changed name of bit field mask
//  
//  34    3/11/98 11:27a Aburgess
//  modifications made to support new colorization of menus based on player
//  army color
//  
//  33    3/09/98 11:36a Nrobinso
//  remove statement
//  
//  32    3/09/98 10:03a Aburgess
//  new ABOUT states
//  
//  31    3/03/98 9:22a Aburgess
//  redefined CHAT key references
//  
//  30    2/26/98 10:19a Aburgess
//  removed SCREENBTN memory leak
//  
//  29    2/25/98 11:47a Aburgess
//  modifications made to correct user configuration bugs
//  
//  28    2/20/98 10:43a Phu
//  changed a char to unsigned char for table-lookup
//  
//  27    2/13/98 12:22p Nrobinso
//  add joystick capture
//  
//  26    2/13/98 10:06a Aburgess
//  modifications made to further support keyboard configurations. Support
//  of Audio slider bar. implementation of all known buttons
//  
//  25    2/12/98 7:34p Nrobinso
//  removed unused code
//  
//  24    2/12/98 4:17p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  23    2/09/98 7:24p Nrobinso
//  maintain a max chat width
//  
//  22    2/06/98 7:20a Aburgess
//  modifications made to support the CUSTOM configuration screen
//  
//  21    2/03/98 4:48p Aburgess
//  repaired Remote Load background display, reduced Multiplayer chat max
//  number of lines to 2 rather than 4. Ignore NULL map references.
//  
//  20    2/01/98 4:31p Aburgess
//  modifications made to support new ART and maps files
//  
//  19    1/23/98 10:47a Aburgess
//  modification to increase chat message string length to allow player
//  name to be added without overrunning the buffer
//  
//  18    1/23/98 10:35a Aburgess
//  modifications made to add Player name to chat
//  
//  17    1/23/98 9:38a Aburgess
//  modifications made to support new multiplayer screens
//  
//  16    1/19/98 7:43p Aburgess
//  color table modification
//  
//  15    1/14/98 2:16p Aburgess
//  modifications made to support GAME_PLAY Options screens
//  
//  14    12/22/97 11:33a Aburgess
//  lastest and greatest screen processing
//  
//  13    12/18/97 1:18p Aburgess
//  New Audio and User Configuration screens. New Scrolling buttons and
//  Slider bars
//  
//  12    12/10/97 9:45a Aburgess
//  changes made to incorporate first pass of PLAY_OPTIONS screen
//  
//  11    12/09/97 12:12p Phu
//  
//  10    12/08/97 7:15a Nrobinso
//  put a bunch of data under compile control
//  
//  9     12/06/97 4:16p Aburgess
//  changes made to support chat in multiplayer screens
//  
//  8     12/01/97 9:55a Aburgess
//  update of SCREEN processing
//  
//  7     11/26/97 2:27p Aburgess
//  modifications made to support MultiPlayer Campaign Select
//  
//  6     11/16/97 2:23p Aburgess
//  SBtnFree() added and miscellaneous debug prototypes
//  
//  5     11/12/97 10:29a Aburgess
//  added SBtn debug prototypes
//  
//  4     11/07/97 10:42a Aburgess
//  New Full Screen UI interfaces
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
//  2     10/09/97 3:35p Aburgess
//  cleanup of button processing
//  
//  1     10/05/97 12:06p Aburgess
//  BUTTON defines, structures, and prototypes
//  
//  $Nokeywords:$
//========================================================================


//========================================================================
// What is a SCREENBTN?
//
// A screen button is an object the user interacts within in order do
// respond to various questions the application may ask.
//
// All screen buttons have a number of basic attributes attached to them.
// These attributes act as controls for handling the presentation and
// response.
//
// A screen button comes in several flavors: a TEXTBUTTON, an ICONBUTTON,
// or an EDITBUTTON.
//
// A TEXTBUTTON is used when the application wants a string of text to act
// like a button.
//
// An ICONBUTTON is used when the application wants an icon type button.
//
// An EDITBUTTON is a special case button used by the application when
// it wants to receive text input from the user.
//
// All screen buttons have 3 possible states: NULL, FOCUSED, and CLICKED.
// The screen button is in NULL state when there is no interaction with the
// user. This is typically represented by plain text or a stagnant animation.
// A screen button enters FOCUSED state when it detects cursor movement
// within its bounding area. For a TEXTBUTTON this maybe either changing the
// color of the text or displaying it with non-transparent background color.
// For an ICONBUTTON, the button icon may change or even animate, though
// more often than not, this state will be disabled.
// This state is meaningless for an EDITBUTTON and thus disabled. 
//
//========================================================================

#ifndef __SCREENBTN_H__
#define __SCREENBTN_H__


//------------------------------------------------------------------------
//				GENERAL SCREENBTN DEFINES
//------------------------------------------------------------------------
#define	SBTN_MAX_PLAYER_NAME_LEN	17
#define	SBTN_MAX_TEXT_LEN			64
#define	SBTN_MAX_REF_LEN			64
#define	SBTN_TEXT_STRING_SIZE		128

#define SBTN_FOCUS_OUT				8			// 8 pixels off BTN before focus loss

#define	SBTN_STATE_CHANGE			1

#define	PANEL_MARGIN				22

#define	GAME_KEY_FLAG			0x80000000

//------------------------------------------------------------------------
//				CHAT DEFINES
//------------------------------------------------------------------------

#define CHAT_MAX_WIDTH			525				//maximum width in pixels of person-to-person chat messages
#define CHAT_MAX_LENGTH			80				//maximum length of person-to-person chat messages
#define CHAT_MAX_WITH_NAME		128				//maximum length of person-to-person chat messages
#define CHAT_MAX_MESSAGES		4
#define	CHAT_KEY_MAX_LEGAL		126

#define	CHAT_KEY_ESCAPE			VK_ESCAPE
#define	CHAT_KEY_BACKSPACE		VK_BACK
#define	CHAT_KEY_RETURN			VK_RETURN
#define	CHAT_KEY_SPACE			VK_SPACE
#define	CHAT_KEY_DEL			VK_DELETE

//------------------------------------------------------------------------
//				SCREENBTN ATTRIBUTES
//------------------------------------------------------------------------

#define	SBTN_CLEAR			(ULONG)(0x00000000)	// all attributes cleared
#define	SBTN_INVISIBLE		(ULONG)(0x00000001)	// button not displayed or processed
#define	SBTN_DISABLED		(ULONG)(0x00000002)	// button displayed but inactive and "grayed out"
#define	SBTN_NO_FOCUS		(ULONG)(0x00000004)	// ignore mouse move responses
#define	SBTN_PASSIVE		(ULONG)(0x00000008)	// ignore mouse move/click responses, display only
#define	SBTN_SPCL_OK		(ULONG)(0x00000010)	// use preallocated OK screenbtn
#define	SBTN_SPCL_CANCEL	(ULONG)(0x00000020)	// use preallocated CANCEL screenbtn
#define	SBTN_SPCL_NEXT		(ULONG)(0x00000040)	// use preallocated NEXT screenbtn
#define	SBTN_SPCL_BACK		(ULONG)(0x00000080)	// use preallocated BACK screenbtn
#define	SBTN_SPCL_FINISH	(ULONG)(0x00000100)	// use preallocated FINISH screenbtn
#define	SBTN_MORE			(ULONG)(0x00000200)	// button identified as a more btn
#define	SBTN_ALLOW_OFFSET	(ULONG)(0x00000400)	// button can have an offset applied to it
#define	SBTN_CLICK_BYPASS	(ULONG)(0x00000800)	// disables CLICK execution callback

#define	SBTN_KEY_TYPE		(ULONG)(0x00008000)	// KEYCODE configuration button

#define	SBTN_CHAT_TYPE		(ULONG)(0x00080000)	// CHATBUTTON: This is an chat send button

#define	SBTN_ICON_TRANS		(ULONG)(0x00400000)	// ICONBUTTON: use transparent mode for icon
#define	SBTN_ICON_TYPE		(ULONG)(0x00800000)	// ICONBUTTON: This is an icon button

#define	SBTN_TEXT_HILITE	(ULONG)(0x02000000)	// TEXTBUTTON: FOCUSED = non-tranparent bkg
#define	SBTN_TEXT_CENTER	(ULONG)(0x04000000)	// TEXTBUTTON: center text horizaontally within text box
#define	SBTN_TEXT_TYPE		(ULONG)(0x08000000)	// TEXTBUTTON: This is a text button

#define	SBTN_EDIT_BOX		(ULONG)(0x40000000)	// EDITBUTTON: This edit button has a visible box
#define	SBTN_EDIT_TYPE		(ULONG)(0x80000000)	// EDITBUTTON: This is an edit button

//------------------------------------------------------------------------
//				SCREEN STATES
//------------------------------------------------------------------------
typedef enum
{
	SCRN_NULL_STATE  = -1,
	SCRN_TITLE_STATE = 0,			// Title Screen state
	SCRN_GAME_START_STATE,			// One or Multi Player, Options, Quit
	SCRN_SELECT_CAMPAIGN_STATE,		// One Player campaign selection
	SCRN_SELECT_CALLSIGN_STATE,		// One Player player name selection
	SCRN_SELECT_MISSION_STATE,		// One Player mission selection

	SCRN_MULTI_HOST_STATE,			// Multi Player HOST campaign selection
	SCRN_MULTI_REMOTE_STATE,		// Multi Player HOST campaign selection

	SCRN_OPTIONS_STATE,				// Armymen options selection
	SCRN_CONTROLS_STATE,			// User control configuration
	SCRN_AUDIO_STATE,				// audio configuration
	SCRN_ABOUT_STATE,				// About Armymen configuration
	SCRN_PLAY_OPTIONS_STATE,		// Armymen options selection during game play
	SCRN_PLAY_CONTROLS_STATE,		// User control configuration during game play
	SCRN_PLAY_AUDIO_STATE,			// audio configuration during game play
	SCRN_PLAY_ABOUT_STATE,			// About Armymen configuration during game play

	SCRN_QUIT_STATE,				// Army quit

	SCRN_STATS_STATE,				// Army statistics

	SCRN_KEYPAD_STATE,				// User Keypad configuration
	SCRN_KEYBOARD_STATE,			// User KeyBoard configuration
	SCRN_CUSTOM_STATE,				// User Custom configuration
	SCRN_JOYSTICK_STATE,			// User Joystick configuration


	// NOTHING BELOW THIS LINE
	SCRN_LAST_STATE
} SCRN_STATE;

//------------------------------------------------------------------------
//				SCREENBTN STATES
//------------------------------------------------------------------------
typedef	enum
{
	BUTTON_NULL = 0,
	BUTTON_FOCUSED,
	BUTTON_CLICKED,
	BUTTON_EDIT,
	BUTTON_DISABLED,

	BUTTON_LAST_STATE
} SBTN_STATE;

typedef	enum
{
	SBTN_OK,			// OK screenbtn
	SBTN_CANCEL,		// CANCEL screenbtn
	SBTN_NEXT,			// NEXT screenbtn
	SBTN_BACK,			// BACK screenbtn
	SBTN_FINISH,		// FINISH screenbtn

	SBTN_MAX_SPCL_BTNS	// number of special screenBtns
}SBTN_SPCL;

typedef enum
{
	SBTN_TRANSPARENT = 0,
	SBTN_DK_RED,
	SBTN_DK_GREEN,
	SBTN_BROWN,
	SBTN_DK_BLUE,
	SBTN_DK_MAGENTA,
	SBTN_DK_CYAN,
	SBTN_GREY,
	SBTN_DK_GREY,
	SBTN_RED,
	SBTN_GREEN,
	SBTN_YELLOW,
	SBTN_BLUE,
	SBTN_MAGENTA,
	SBTN_CYAN,
	SBTN_WHITE,
	SBTN_BLACK,
	SBTN_LT_GREEN,
	SBTN_LT_TAN,
	SBTN_LT_BLUE,
	SBTN_LT_GREY,
	SBTN_DK_TAN,

	SBTN_LAST_COLOR
} SBTN_COLOR;

typedef struct screenColors
{
	SBTN_COLOR	TitleColor;			// Button/Object Title Text color
	SBTN_COLOR	NullColor;			// Button/Object NULL state color
	SBTN_COLOR	FocusColor;			// Button/Object FOCUS state color
	SBTN_COLOR	ClickedColor;		// Button/Object CLICKED state color
	SBTN_COLOR	DisabledColor;		// Button/Object DISABLED state color
	SBTN_COLOR	AlreadyPlayedColor;	// Button/Object Already Played hilight color
	SBTN_COLOR	EditFillColor;		// Button/Object Edit Fill color
} SBTN_SCRN_COLORS;

//------------------------------------------------------------------------
//				SCREENBTN STRUCTURE
//------------------------------------------------------------------------
typedef struct	screenButton
{
	// Status structure
	ULONG		bAttributes;		// button attributes
	SBTN_STATE	eScreenBtnState;
	SBTN_STATE	ePrevScreenBtnState;
	LONG		nFontID;
	SBTN_COLOR	eBGColor;
	SBTN_COLOR	aFGColors[ BUTTON_LAST_STATE ];
	LONG		((*pNullCallback)(struct screenButton* pButton));		// optional routine to call when in NULL state
	LONG		((*pFocusedCallback)(struct screenButton* pButton));	// optional routine to call when in FOCUSED state
	LONG		((*pClickedCallback)(struct screenButton* pButton));	// optional routine to call when in CLICKED state
	LONG		((*pEditCallback)(struct screenButton* pButton));		// optional edit button callback routine
	DWORD		dwData;													// button user data
	BOOL		bUpdate;

	// Presentation structure
	SPOINT		position;
	char		pText[SBTN_TEXT_STRING_SIZE+1];
	char		pNullRef[SBTN_MAX_REF_LEN+1];
	char		pFocusedRef[SBTN_MAX_REF_LEN+1];
	char		pClickedRef[SBTN_MAX_REF_LEN+1];
	char		pDisabledRef[SBTN_MAX_REF_LEN+1];

	SPRITE		NullSprite;
	SPRITE		FocusedSprite;
	SPRITE		ClickedSprite;
	SPRITE		DisabledSprite;

	LPTSTR		NullResourceID;
	LPTSTR		FocusedResourceID;
	LPTSTR		ClickedResourceID;
	LPTSTR		DisabledResourceID;

	SBOX		ParentBox;
	SBOX		TextBox;
	SBOX		NullBox;
	SBOX		FocusedBox;
	SBOX		ClickedBox;

	BOOL		bTextHasArrived;
	int			bCapturingKeys;
	int			nMaxEditChars;
	int			nMaxEditWidth;

	struct	screenButton*	hPrevClicked;
} SCREENBTN;

typedef SCREENBTN*	HSCREENBTN;

typedef	struct	scrnBtnDef
{
	ULONG		bAttributes;					// screenBtn Attributes
	LONG		nFontID;						// screenBtn Font ID
	SBTN_COLOR	eBGColor;						// screenBtn Text Background color
	SBTN_COLOR	aFGColors[ BUTTON_LAST_STATE ];	// screenBtn Text Foreground colors
	SPOINT		position;						// screenBtn relative position
	int			nMaxEditChars;					// ScreenBtn EDIT max chars in Box
	char*		pText;							// screenBtn Text
	char		pNullRef[SBTN_MAX_REF_LEN+1];	// screenBtn NULL state icon
	char		pFocusedRef[SBTN_MAX_REF_LEN+1];// screenBtn FOCUSED state icon
	char		pClickedRef[SBTN_MAX_REF_LEN+1];// screenBtn CLICKED state icon
	char		pDisabledRef[SBTN_MAX_REF_LEN+1];// screenBtn DISABLED state icon
	SBOX		defaultBox;						// screenBtn default area box
	LONG		((*pCallback)(struct screenButton* pButton));// optional callback routine
	DWORD		dwData;							// button user data
} SCREENBTNDEF;

//------------------------------------------------------------------------
//				CHAT STRUCTURES
//------------------------------------------------------------------------

typedef struct
{
	BOOL	bUpdate;
	int		nCurrentTopString;
	char	*pStrings[CHAT_MAX_MESSAGES];
	char	strings[(CHAT_MAX_WITH_NAME+1)*CHAT_MAX_MESSAGES];
} CHAT_STRUCT_RECEIVE;

typedef	struct
{
	BOOL	bUpdate;
	BOOL	bCapturingKeys;
	BOOL	bTextHasArrived;
	int		nCurrentMessageLength;
	char	pCurrentMessage[CHAT_MAX_WITH_NAME+1];
} CHAT_STRUCT_SEND;

typedef	struct
{
	CHAT_STRUCT_SEND	chatSend;
	CHAT_STRUCT_RECEIVE	chatReceive;
} CHAT;

//========================================================================
//						GLOBAL DATA
//========================================================================
extern	COLORREF	SBTNcolorTable[ SBTN_LAST_COLOR ];
extern	HSCREENBTN	SBTNcurrentFocus;
extern	HSCREENBTN	SBTNcurrentClicked;

//========================================================================
//						PROTOTYPES
//========================================================================
extern	BOOL		SBtnInit( void );
extern	void		SBtnExit( void );
extern	void		SBtnSpclFree( void );
extern	HSCREENBTN	SBtnCreate( SPOINT* pPoint, ULONG bAttributes, SBOX* pParentBox );
extern	BOOL		SBtnDelete( HSCREENBTN hScreenBtn );
extern	void		SBtnFree( HSCREENBTN hScreenBtn );
extern	void		SBtnDeleteAll( void );

extern	void		SBtnSetCallback( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState, LPVOID pCallback );
extern	LONG		SBtnExecuteCallback( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState );

extern	BOOL		SBtnSetState( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState );
extern	SBTN_STATE	SBtnGetState( HSCREENBTN hScreenBtn );
extern	BOOL		SBtnSetAttributes( HSCREENBTN hScreenBtn, ULONG bAttributes );
extern	BOOL		SBtnClearAttributes( HSCREENBTN hScreenBtn, ULONG bAttributes );
extern	ULONG		SBtnGetAttributes( HSCREENBTN hScreenBtn );
extern	BOOL		SBtnHaveAttributes( HSCREENBTN hScreenBtn, ULONG bAttributesMask );
extern	BOOL		SBtnSetFont( HSCREENBTN hScreenBtn, LONG nFontID );
extern	LONG		SBtnGetFont( HSCREENBTN hScreenBtn );
extern	BOOL		SBtnSetText( HSCREENBTN hScreenBtn, char* pText );
extern	char*		SBtnGetText( HSCREENBTN hScreenBtn );
extern	BOOL		SBtnSetIcon( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState, char* pIcon );
extern	SPRITE*		SBtnGetIcon( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState );
extern	BOOL		SBtnSetPosition( HSCREENBTN hScreenBtn, SPOINT* pPosition );
extern	SPOINT*		SBtnGetPosition( HSCREENBTN hScreenBtn );
extern	BOOL		SBtnSetFGColor( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState, SBTN_COLOR eColor );
extern	SBTN_COLOR	SBtnGetFGColor( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState );
extern	BOOL		SBtnSetBGColor( HSCREENBTN hScreenBtn, SBTN_COLOR eColor );
extern	SBTN_COLOR	SBtnGetBGColor( HSCREENBTN hScreenBtn );
extern	BOOL		SBtnSetBox( HSCREENBTN hScreenBtn, SBTN_STATE eSBtnState, SBOX* pBox );
extern	SBOX*		SBtnGetBox( HSCREENBTN hScreenBtn );
extern	BOOL		SBtnSetData( HSCREENBTN hScreenBtn, DWORD pData );
extern	DWORD		SBtnGetData( HSCREENBTN hScreenBtn );

extern	void		SBtnDisplay( HSCREENBTN hScreenBtn );
extern	BOOL		SBtnUpdate( HSCREENBTN hScreenBtn );
extern	void		SBtnDoActions( void );
extern	HSCREENBTN	SBtnIsInButton( SPOINT* pPoint );
extern	HSCREENBTN	SBtnLoadDef( SCREENBTNDEF* pScreenBtnDef, SBOX* pParentBox );
extern	void		SBtnResetAll( void );
extern	void		SBtnReset( HSCREENBTN hScreenBtn );
extern	void		SBtnClearFocus( SPOINT* pPoint );
extern	BOOL		SBtnInEditMode( HSCREENBTN hScreenBtn );
extern	void		SBtnApplyOffset( HSCREENBTN hScreenBtn, SPOINT* pOffset );
extern	void		SBtnResetGlobals( void );
extern	void		SBtnSetCurrentClicked( HSCREENBTN hScreenBtn );
extern	HSCREENBTN	SBtnGetCurrentClicked( void );

extern	void		SBtnDumpAll( void );
extern	void		SBtnDump( HSCREENBTN hScreenBtn );
extern	char*		SBtnColorName( SBTN_COLOR eColor );

extern	BOOL	SBtnHandleKey( UINT character );
extern	void	SBtnTurnOffKeys( HSCREENBTN hScreenBtn );
extern	BOOL	SBtnChatHandleKey(UINT character);  //returns true if the character was used
extern	void	SBtnChatTurnOffKeys( HSCREENBTN hScreenBtn );
extern	void	SBtnChatTurnOnKeys( HSCREENBTN hScreenBtn );
extern	void	ScrnSendChatMessage( HSCREENBTN hScreenBtn, BOOL bTurnOff );
extern	void	SBtnKeycodeProcess(BYTE character);
extern	void	SBtnJoystickProcess(BYTE button);
extern	void	SBtnKeycodeTurnOffKeys( HSCREENBTN hScreenBtn );

extern	char*	SBtnKeycodeName( unsigned char keycode );

#endif
//========================================================================
//							EOF
//========================================================================
