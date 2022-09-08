/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Commands.cpp $
//
//	DESCRIPTION:	Game commands
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Friday, October 17, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Commands.cpp 142   4/16/98 4:53p Nrobinso $
//
//	Copyright (C) 1996-97 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Commands.cpp $
//  
//  142   4/16/98 4:53p Nrobinso
//  turn off right button in setup
//  
//  141   4/13/98 9:30a Phu
//  
//  140   4/12/98 11:19p Nrobinso
//  fix keyboard custom problems
//  
//  139   4/12/98 8:59p Nrobinso
//  check for command key being equal to fixed key
//  
//  138   4/08/98 11:24p Nrobinso
//  fix keyboard customization saving
//  
//  137   4/06/98 11:49a Nrobinso
//  add backspace and fir to setup keys
//  
//  136   4/03/98 6:04p Aburgess
//  modifications made to correct Joystick Configuration BACK/RESTORE bugs
//  
//  134   4/02/98 7:33p Nrobinso
//  swap roll left & right
//  
//  133   4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  132   4/01/98 12:02p Nrobinso
//  close file
//  
//  131   3/31/98 11:37p Aburgess
//  fix customization problems
//  
//  129   3/29/98 12:45a Nrobinso
//  trun off trace
//  
//  128   3/29/98 12:38a Nrobinso
//  fix problem with undefining and redefining a key
//  
//  127   3/27/98 2:57p Aburgess
//  null'd out duplicate keys in key table
//  
//  126   3/26/98 9:36p Nrobinso
//  remove unused
//  
//  125   3/26/98 1:51p Nrobinso
//  can't change weapons or enter vehicle while firing
//  
//  124   3/26/98 12:46p Bwilcox
//  mission->objective (o)  map->viewmap (v)
//  
//  123   3/25/98 3:43p Nrobinso
//  turn off the vehicle sound when bringing up the mission briefing
//  
//  122   3/25/98 3:26p Phu
//  allow esc from setup when paused
//  
//  121   3/24/98 4:11p Phu
//  clear firing bar info if user manually changes weapon
//  
//  120   3/24/98 2:28p Phu
//  change key table for pause state
//  
//  119   3/23/98 10:43a Nrobinso
//  don't save joystick options unless there is an active joystick
//  
//  118   3/22/98 4:38p Nrobinso
//  fix gunsight/mouse button saving
//  
//  117   3/22/98 3:16p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  116   3/22/98 2:50p Nrobinso
//  change around basic commands one more time
//  
//  115   3/20/98 6:07p Nrobinso
//  save right button and cursor color state to registry
//  
//  114   3/20/98 10:44a Bwilcox
//  
//  113   3/19/98 3:16p Nrobinso
//  make left shift a fixed command
//  
//  112   3/18/98 12:50a Nrobinso
//  cleanup registry access
//  
//  111   3/17/98 3:09p Aburgess
//  registry storage of Audio parameters and Config parameter
//  
//  110   3/15/98 7:35p Nrobinso
//  allow a joystick command to be cleared if no joystick button
//  
//  109   3/14/98 8:55p Nrobinso
//  allow gunsight & mouse button to be customized; add mouse button 2
//  vommand
//  
//  108   3/14/98 4:51p Bwilcox
//  G is alternate gunsight flip
//  
//  107   3/13/98 8:02p Nrobinso
//  ignore fixed key matches
//  
//  106   3/13/98 11:33a Nrobinso
//  compile switch for getting the joystick config file
//  
//  105   3/12/98 9:31a Aburgess
//  disabled DEBUG trace
//  
//  104   3/11/98 3:20p Aburgess
//  modifications to support non-overwriting key bindings
//  
//  103   3/08/98 4:40p Phu
//  don't allow switch to other weapons when in vehicle
//  
//  102   3/07/98 11:50p Nrobinso
//  debug keys are not in final
//  
//  101   3/06/98 4:57p Nrobinso
//  have up to 8 buttons pre-assigned for joystick; eliminate buttons which
//  your joystick doesn't have
//  
//  100   3/05/98 6:36p Nrobinso
//  swap enter & fire for executing orders
//  
//  99    3/05/98 2:47p Aburgess
//  added restoreJoystickBindings
//  
//  98    3/03/98 9:39p Nrobinso
//  sargedown no longer takes a pointer
//  
//  97    3/02/98 8:01p Phu
//  don't allow tab, command/scroll if no units to select
//  
//  96    3/02/98 6:51p Nrobinso
//  reorder commands
//  
//  95    3/02/98 2:37p Nrobinso
//  leave debug keys in final
//  
//  94    3/01/98 8:20p Nrobinso
//  remove pause, fixup command names
//  
//  93    2/27/98 2:54p Nrobinso
//  fix default slow command
//  
//  92    2/26/98 2:36p Nrobinso
//  change default joystick buttons
//  
//  91    2/25/98 1:11p Nrobinso
//  put load/save of key bindings here
//  
//  90    2/25/98 11:00a Nrobinso
//  new commands
//  
//  89    2/21/98 5:49p Nrobinso
//  
//  88    2/20/98 6:42p Nrobinso
//  fix default commands
//  
//  87    2/20/98 6:22p Nrobinso
//  fix defaults
//  
//  86    2/20/98 6:14p Nrobinso
//  swapped fixed and custom commands
//  
//  85    2/17/98 7:49p Nrobinso
//  cleanup commands
//  
//  84    2/17/98 5:16p Nrobinso
//  swap F5 & F6 back
//  
//  83    2/17/98 3:02p Nrobinso
//  
//  82    2/16/98 6:25p Nrobinso
//  cleanup tables
//  
//  81    2/13/98 12:20p Nrobinso
//  button3 now equivalent to Enter
//  
//  80    2/13/98 11:11a Nrobinso
//  moved joystick stuff to input
//  
//  79    2/13/98 9:49a Nrobinso
//  fix joystick commands
//  
//  78    2/12/98 9:42p Nrobinso
//  cleanup commands; add joystick commands
//  
//  77    2/12/98 4:17p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  76    2/10/98 1:25p Nrobinso
//  turn Esc key back on for menu
//  
//  75    2/09/98 12:29p Aburgess
//  modifications made to support IN GAME screens, Cursor control, and
//  Rules presentation
//  
//  74    2/09/98 11:49a Nrobinso
//  temp patch: esc loses
//  
//  73    2/07/98 12:27a Nrobinso
//  next weapon command
//  
//  72    2/06/98 11:27p Nrobinso
//  improve key comamnds
//  
//  71    2/04/98 3:09p Nrobinso
//  reverse air strike & paratrooper to match dash
//  
//  70    2/03/98 3:22p Bwilcox
//  sargegetactiveweapon now takes arg,
//  fixed avatar mine interactions
//  
//  69    2/02/98 5:27p Nrobinso
//  escape scroll mode without firing
//  
//  68    2/02/98 11:48a Nrobinso
//  setup for keyboard go to chat
//  
//  67    2/02/98 1:08a Nrobinso
//  change ui for multiplayer
//  
//  66    1/24/98 3:15p Aburgess
//  ESC now brings up the game options screen
//  
//  65    1/20/98 7:19p Phu
//  fix autofire stuff
//  
//  64    1/19/98 4:45p Phu
//  don't fire when fire is used for something else
//  
//  63    1/17/98 8:15p Nrobinso
//  add right button up routines; make reeturn do an order and exit out of
//  command mode
//  
//  62    1/16/98 11:08a Nrobinso
//  final function key commands
//  
//  61    1/08/98 5:28p Phu
//  chat keys don't control sarge now
//  
//  60    1/07/98 3:21p Nrobinso
//  add AvatarCurrentPose; changed AvatarPose to take only the avatar
//  pointer; AvatarPoseChange also takes an action
//  
//	...
//  
//  1     10/17/97 2:34p Nrobinso
//  game play commands
//  
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "input.h"
#include "Army.h"
#include "Vehicle.h"
#include "Sarge.h"
#include "ui.h"
#include "Screen.h"
#include "Map.h"
#include "Commands.h"
#include "debug.h"
#include "miscfile.h"
#include "fileio.h"
#include "gameproc.h"
#include "comm.h"


/////////////////////////////////////////////////////////////////////////////
// Debugging support
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
LONG    user_action = 0;        // Player input actions
unsigned char scrollReset = 0;	//1= flip view back to anim

CONFIG	UIcurrentConfig;

#ifndef FINAL
	BOOL full_joystick = FALSE;
#endif

extern TKeyBindingEntry DebugKeys[];
extern char MouseDxRotate;
extern char MouseTurret;
extern char joyButtons;

SUserInterface UI_GAME_PLAY_STATE = 
{
	InGameLButtonDn,		// Mouse left-button down events
	InGameLButtonUp,		// Mouse left-button up events
	InGameRButtonDn,		// Mouse right-button down events
	InGameRButtonUp,		// Mouse right-button up events
	NULL,					// Mouse movement events

	NULL,					// key down events
	NULL				// key up events
};


SUserInterface UI_GAME_SETUP_STATE = 
{
	InGameLButtonDn,		// Mouse left-button down events
	InGameLButtonUp,		// Mouse left-button up events
	NULL,					// Mouse right-button down events
	NULL,					// Mouse right-button up events
	NULL,					// Mouse movement events

	NULL,					// key down events
	NULL				// key up events
};


/*
	Function Prototypes used by Default Key Table
*/
void Kbd_GamePlay_Exit( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_Menu( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_Chat( BYTE nChar, UINT nFlags );

/*
	Default Key Table
*/
TKeyBindingEntry DefaultKeys[] =
{
	{DIK_ESCAPE,	Kbd_GamePlay_Menu,	    ETO_Pressed,	0},
	{0, NULL, 0, 0, 0, 0, 0}
};


/*
	Function Prototypes used by GamePlay Key Table
*/
void Kbd_GamePlay_Follow( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_Attack( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_Defend( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_AttackNow( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_DefendNow( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_Scroll( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_AirDrop( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_Recon( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_AirStrike( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_NextUnit( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_AltGunsight( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_AltMouse( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_Mission( BYTE nChar, UINT nFlags );
void Kbd_GamePlay_Map( BYTE nChar, UINT nFlags );

/*
	GamePlay Key Table
*/

TKeyBindingEntry GamePlayKeys[] =
{
	{0,				Kbd_GamePlay_Follow,	ETO_Pressed,	0,	0, "Follow"},
	{0,				Kbd_GamePlay_Attack,	ETO_Pressed,	0,	0, "Attack"},
	{0,				Kbd_GamePlay_Defend,	ETO_Pressed,	0,	0, "Defend"},
	{DIK_S,			Kbd_GamePlay_AirStrike, ETO_Pressed,	0,	0, "Air Strike"},
	{DIK_P,			Kbd_GamePlay_AirDrop,	ETO_Pressed,	0,	0, "Paratroop"},
	{DIK_R,			Kbd_GamePlay_Recon,		ETO_Pressed,	0,	0, "Recon"},
	{DIK_A,			Kbd_GamePlay_AttackNow,	ETO_Pressed,	0,	0, "Attack Now"},
	{DIK_F,			Kbd_GamePlay_DefendNow,	ETO_Pressed,	0,	0, "Defend Now"},
	{DIK_O,			Kbd_GamePlay_Mission,	ETO_Pressed,	0,	0, "Mission"},
	{DIK_V,			Kbd_GamePlay_Map,		ETO_Pressed,	0,	0, "Map"},

	{DIK_RETURN,	Kbd_GamePlay_Scroll,	ETO_Pressed,	0,	0, "Scroll"},
	{DIK_BACK,		Kbd_GamePlay_Chat,		ETO_Pressed,	0,	0, "Chat"},
	{DIK_TAB,		Kbd_GamePlay_NextUnit,	ETO_Pressed,	0,	0, "Next Unit"},

	{DIK_G,			Kbd_GamePlay_AltGunsight,ETO_Pressed,	0,	0, "GunSight"},
	{DIK_M,			Kbd_GamePlay_AltMouse,	ETO_Pressed,	0,	0, "Mouse Right"},

	{DIK_F1,		Kbd_GamePlay_Follow,	ETO_Pressed,	0,	0, "Follow F1"},
	{DIK_F2,		Kbd_GamePlay_Attack,	ETO_Pressed,	0,	0, "Attack F2"},
	{DIK_F3,		Kbd_GamePlay_Defend,	ETO_Pressed,	0,	0, "Defend F3"},
	{DIK_F5,		Kbd_GamePlay_AirStrike, ETO_Pressed,	0,	0, "Air Strike F5"},
	{DIK_F6,		Kbd_GamePlay_AirDrop,	ETO_Pressed,	0,	0, "Paratroop F6"},
	{DIK_F7,		Kbd_GamePlay_Recon,		ETO_Pressed,	0,	0, "Recon F7"},
	{DIK_F9,		Kbd_GamePlay_AttackNow,	ETO_Pressed,	0,	0, "Attack Now F9"},
	{DIK_F10,		Kbd_GamePlay_DefendNow,	ETO_Pressed,	0,	0, "Defend Now F10"},
	{DIK_F11,		Kbd_GamePlay_Mission,	ETO_Pressed,	0,	0, "Mission F11"},
	{DIK_F12,		Kbd_GamePlay_Map,		ETO_Pressed,	0,	0, "Map F12"},

	{0, NULL, 0, 0, 0, 0, 0}
};

TKeyDescriptors GamePlayKeyDescs[] =
{
	// DISPATCHER				DESCRIPTION		CUSTOM      FIXED       DEFAULT1	DEFAULT2
	{Kbd_GamePlay_Follow,		"Follow",		DIK_F1,		DIK_F1,		DIK_F1,		DIK_F },
	{Kbd_GamePlay_Attack,		"Attack",		DIK_F2,		DIK_F2,		DIK_F2,		DIK_A },
	{Kbd_GamePlay_Defend,		"Defend",		DIK_F3,		DIK_F3,		DIK_F3,		DIK_D },
	{Kbd_GamePlay_AttackNow,	"Attack Now",	DIK_A,		DIK_F9,		DIK_A,		DIK_Z },
	{Kbd_GamePlay_DefendNow,	"Defend Now",	DIK_F,		DIK_F10, 	DIK_F,		DIK_C },
	{Kbd_GamePlay_NextUnit,		"Next Unit",	DIK_TAB,	0,			DIK_TAB,	DIK_TAB },

	{Kbd_GamePlay_AirStrike,	"Air Strike",	DIK_S,		DIK_F5,		DIK_S,		DIK_S },
	{Kbd_GamePlay_AirDrop,		"Air Paratroop",DIK_P,		DIK_F6,		DIK_P,		DIK_P },
	{Kbd_GamePlay_Recon,		"Air Recon",	DIK_R,		DIK_F7,		DIK_R,		DIK_R },

	{Kbd_GamePlay_Scroll,		"Scroll",		DIK_RETURN,	0,			DIK_RETURN, DIK_RETURN },
	{Kbd_GamePlay_Chat,			"Chat",			DIK_BACK,	0,			DIK_BACK,	DIK_BACK },
	
	{Kbd_GamePlay_Mission,		"Objective",		DIK_O,		DIK_F11, 	DIK_O,		DIK_O },
	{Kbd_GamePlay_Map,			"View Map",			DIK_V,		DIK_F12, 	DIK_V,		DIK_V},

	{Kbd_GamePlay_AltGunsight,	"Change Gunsight",	DIK_G,		0,			DIK_G,		DIK_G },
	{Kbd_GamePlay_AltMouse,		"Mouse Button 2",	DIK_M,		0,			DIK_M,		DIK_M },

	{NULL, "", 0, 0, 0, 0 }
};


TKeyBindingEntry GameSetupKeys[] =
{
	{0, NULL, 0, 0, 0, 0, 0}
};

/*
	Function Prototypes used by Sarge / Vehicle Key Table
*/
void Kbd_Sarge_Right( BYTE nChar, UINT nFlags );
void Kbd_Sarge_Left( BYTE nChar, UINT nFlags );
void Kbd_Sarge_Up( BYTE nChar, UINT nFlags );
void Kbd_Sarge_Down( BYTE nChar, UINT nFlags );
void Kbd_Sarge_Slow( BYTE nChar, UINT nFlags );
void Kbd_Sarge_Fire( BYTE nChar, UINT nFlags );
void Kbd_Sarge_GunRight( BYTE nChar, UINT nFlags );
void Kbd_Sarge_GunLeft( BYTE nChar, UINT nFlags );
void Kbd_Vehicle_Down( BYTE nChar, UINT nFlags );
void Kbd_Vehicle_Stop( BYTE nChar, UINT nFlags );
void Kbd_Sarge_ForwLeft( BYTE nChar, UINT nFlags );
void Kbd_Sarge_ForwRight( BYTE nChar, UINT nFlags );
void Kbd_Sarge_Alt( BYTE nChar, UINT nFlags );
void Kbd_Sarge_RollRight( BYTE nChar, UINT nFlags );
void Kbd_Sarge_RollLeft( BYTE nChar, UINT nFlags );
void Kbd_Sarge_Dive( BYTE nChar, UINT nFlags );
void Kbd_Sarge_ChgWeapon1( BYTE nChar, UINT nFlags );
void Kbd_Sarge_ChgWeapon2( BYTE nChar, UINT nFlags );
void Kbd_Sarge_ChgWeapon3( BYTE nChar, UINT nFlags );
void Kbd_Sarge_ChgWeapon( BYTE nChar, UINT nFlags );
void Kbd_Sarge_Vehicle( BYTE nChar, UINT nFlags );
void Kbd_Sarge_DropItem( BYTE nChar, UINT nFlags );


void RestoreJoystickBindings( void );

/*
	Sarge Key Table
*/
TKeyBindingEntry SargeKeys[] =
{
	{DIK_NUMPAD8,	Kbd_Sarge_Up,			ETO_Down,		0,	0},
	{DIK_NUMPAD2,	Kbd_Vehicle_Down,		ETO_Down,		0,	0},
	{DIK_NUMPAD4,	Kbd_Sarge_Left,			ETO_Down,		0,	0},
	{DIK_NUMPAD6,	Kbd_Sarge_Right,		ETO_Down,		0,	0},

	{DIK_NUMPAD7,	Kbd_Sarge_RollLeft,		ETO_Down,		0,	0},
	{DIK_NUMPAD9,	Kbd_Sarge_RollRight,	ETO_Down,		0,	0},
	{DIK_DIVIDE,	Kbd_Sarge_Dive,			ETO_Down,		0,	0},

	{DIK_X,			Kbd_Sarge_GunRight,		ETO_Down,		0,	0},
	{DIK_Z,			Kbd_Sarge_GunLeft,		ETO_Down,		0,	0},

	{DIK_RCONTROL,	Kbd_Sarge_Fire,			ETO_Always,		0,	0},
	{DIK_NUMPAD5,	Kbd_Sarge_Down,			ETO_Pressed,	0,  0},
	{DIK_RSHIFT,	Kbd_Sarge_Slow,			ETO_Down,		0,	0},

	{DIK_1,			Kbd_Sarge_ChgWeapon1,	ETO_Pressed,	0,	0},
	{DIK_2,			Kbd_Sarge_ChgWeapon2,	ETO_Pressed,	0,	0},
	{DIK_3,			Kbd_Sarge_ChgWeapon3,	ETO_Pressed,	0,	0},

	{DIK_E,			Kbd_Sarge_Vehicle,		ETO_Pressed,	0,	0},
	{DIK_D,			Kbd_Sarge_DropItem,		ETO_Pressed,	0,	0},

	{DIK_F4,		Kbd_Sarge_Vehicle,		ETO_Pressed,	0,	0},
	{DIK_F8,		Kbd_Sarge_DropItem,		ETO_Pressed,	0,	0},
	{DIK_SPACE,		Kbd_Sarge_Fire,			ETO_Always,		0,	0},
	{DIK_LSHIFT,	Kbd_Sarge_Slow,			ETO_Down,		0,	0},

	{0, NULL, 0, 0, 0, 0, 0}
};

TKeyDescriptors SargeKeyDescs[] =
{
	// DISPATCHER           DESCRIPTION         CUSTOM          FIXED		DEFAULT1        DEFAULT2
	{Kbd_Sarge_Up,			"Forward",			DIK_NUMPAD8,	0,			DIK_NUMPAD8,	DIK_UP },
	{Kbd_Sarge_Left,		"Left",				DIK_NUMPAD4,	0,			DIK_NUMPAD4,	DIK_LEFT },
	{Kbd_Sarge_Right,		"Right",			DIK_NUMPAD6,	0,			DIK_NUMPAD6,	DIK_RIGHT },
	{Kbd_Vehicle_Down,		"Back",				DIK_NUMPAD2,	0,			DIK_NUMPAD2,	DIK_DOWN },

	{Kbd_Sarge_RollLeft,    "Roll Left",		DIK_NUMPAD7,	0,			DIK_NUMPAD7,	DIK_NUMPAD7 },
	{Kbd_Sarge_RollRight,   "Roll Right",		DIK_NUMPAD9,	0,			DIK_NUMPAD9,	DIK_NUMPAD9 },
	{Kbd_Sarge_Dive,		"Dive",				DIK_DIVIDE,		0,			DIK_DIVIDE,		DIK_NUMPAD8 },

	{Kbd_Sarge_Down,		"Kneel/Prone",		DIK_NUMPAD5,	0,			DIK_NUMPAD5,	DIK_NUMPAD5 },
	{Kbd_Sarge_Slow,		"Slow",				DIK_RSHIFT,		DIK_LSHIFT,	DIK_LSHIFT,		DIK_LSHIFT },

	{Kbd_Sarge_Fire,		"Fire",				DIK_RCONTROL,	DIK_SPACE,	DIK_RCONTROL,	DIK_RCONTROL },
	{Kbd_Sarge_GunLeft,     "Gun Left",			DIK_Z,			0,			DIK_Z,			DIK_NUMPAD4 },
	{Kbd_Sarge_GunRight,    "Gun Right",		DIK_X,			0,			DIK_X,			DIK_NUMPAD6 },

	{Kbd_Sarge_ChgWeapon1,  "Main Weapon",		DIK_1,			0,			DIK_1,			DIK_1 },
	{Kbd_Sarge_ChgWeapon2,  "Heavy Weapon",		DIK_2,			0,			DIK_2,			DIK_2 },
	{Kbd_Sarge_ChgWeapon3,	"Special Item",		DIK_3,			0,			DIK_3,			DIK_3 },

	{Kbd_Sarge_Vehicle,		"Enter Vehicle",	DIK_E,			DIK_F4,		DIK_E,			DIK_E },
	{Kbd_Sarge_DropItem,	"Drop Item",		DIK_D,			DIK_F8,		DIK_D,			DIK_X },
	
	{NULL, "", 0, 0, 0, 0 }
};


TKeyBindingEntry JoystickButtons[] =
{
	{8,			Kbd_GamePlay_Scroll,	ETO_Pressed,	0,	0},
	{4,			Kbd_GamePlay_NextUnit,	ETO_Pressed,	0,	0},

	{2,			Kbd_Sarge_ChgWeapon,	ETO_Pressed,	0,	0},
	{6,			Kbd_Sarge_DropItem,		ETO_Pressed,	0,	0},
	{7,			Kbd_Sarge_Vehicle,		ETO_Pressed,	0,	0},

	{0,			Kbd_Sarge_Slow,			ETO_Down,		0,	0},
	{3,			Kbd_Sarge_Alt,			ETO_Down,		0,	0},
	{1,			Kbd_Sarge_Fire,			ETO_Always,		0,	0},

	{DOWN_KEY,	Kbd_Vehicle_Down,		ETO_Down,		0,	0},
	{UP_KEY,	Kbd_Sarge_Up,			ETO_Down,		0,	0},

	{LEFT_KEY,	Kbd_Sarge_Left,			ETO_Down,		0,	0},
	{RIGHT_KEY,	Kbd_Sarge_Right,		ETO_Down,		0,	0},

	{5,			Kbd_Sarge_Down,			ETO_Down,		0,  0},

	{0, NULL, 0, 0, 0, 0, 0}
};

TKeyDescriptors JoystickDescs[] =
{
	// DISPATCHER           DESCRIPTION         CUSTOM          FIXED           DEFAULT1        DEFAULT2
	{Kbd_Sarge_Up,			"Forward",			UP_KEY,			0,				UP_KEY,			0 },
	{Kbd_Sarge_Left,		"Left",				LEFT_KEY,		0,				LEFT_KEY,		0 },
	{Kbd_Sarge_Right,		"Right",			RIGHT_KEY,		0,				RIGHT_KEY,		0 },
	{Kbd_Vehicle_Down,      "Back",				DOWN_KEY,		0,				DOWN_KEY,		0 },

	{Kbd_Sarge_Alt,			"Roll",				3,				0,				3,				0 },
	{Kbd_Sarge_Down,		"Kneel/Prone",		5,				0,				5,				0 },
	{Kbd_Sarge_Slow,		"Slow",				0,				0,				0,				0 },

	{Kbd_Sarge_Fire,		"Fire",				1,				0,				1,				0 },
	{Kbd_Sarge_GunRight,    "Gun Right",		0,				0,				0,				0 },
	{Kbd_Sarge_GunLeft,     "Gun Left",			0,				0,				0,				0 },
	{Kbd_Sarge_ChgWeapon,	"Change Weapon",	2,				0,				2,				0 },
	{Kbd_Sarge_DropItem,	"Drop Weapon",		6,				0,				6,				0 },

	{Kbd_Sarge_Vehicle,		"Enter Vehicle",	7,				0,				7,				0 },
	{Kbd_GamePlay_NextUnit,	"Next Unit",		4,				0,				4,				0 },
	{Kbd_GamePlay_Scroll,	"Scroll",			8,				0,				8,				0 },

	{NULL, "", 0, 0, 0, 0 }
};


char	CONFIGversion          = -1;

/*
	Setup Key Table
*/
TKeyBindingEntry SetupKeys[] =
{
	// fire
	{DIK_SPACE,		Kbd_Sarge_Fire,			ETO_Always,		0,	0},

		// from here, copy the custom keys
	{DIK_NUMPAD8,	Kbd_Sarge_Up,			ETO_Down,		0,	0},
	{DIK_NUMPAD2,	Kbd_Vehicle_Down,		ETO_Down,		0,	0},
	{DIK_NUMPAD4,	Kbd_Sarge_Left,			ETO_Down,		0,	0},
	{DIK_NUMPAD6,	Kbd_Sarge_Right,		ETO_Down,		0,	0},

	{DIK_SPACE,		Kbd_Sarge_Fire,			ETO_Always,		0,	0},
	{DIK_BACK,		Kbd_GamePlay_Chat,		ETO_Pressed,	0,	0, "Chat"},

	{0, NULL, 0, 0, 0, 0, 0}
};



TKeyBindingEntry *SetupKeyTable[] = 
{
	DefaultKeys,
#ifndef FINAL
	DebugKeys,
#endif
	SetupKeys,
	NULL
};


TKeyBindingEntry *SargeKeyTable[] = 
{
	DefaultKeys,
#ifndef FINAL
	DebugKeys,
#endif
	GamePlayKeys,
	SargeKeys,
	NULL
};


TKeyBindingEntry *PauseKeyTable[] = 
{
	DefaultKeys,
	NULL
};


TKeyBindingEntry ChatKeys[] =
{
	{0, NULL, 0, 0, 0, 0, 0}
};


TKeyBindingEntry *ChatKeyTable[] =
{
	NULL
};


/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//					     Code
/////////////////////////////////////////////////////////////////////////////

void Kbd_GamePlay_Exit( BYTE nChar, UINT nFlags )
{
    if (ESC_Mode()) 
		 return; // scrolling mode turned off

	pMainFrame->PostMessage(WM_CLOSE, 0, 0);
}


void Kbd_Sarge_Right( BYTE nChar, UINT nFlags )
{
	user_action |= DO_TURN_RIGHT;
}


void Kbd_Sarge_Left( BYTE nChar, UINT nFlags )
{
	user_action |= DO_TURN_LEFT;
}


void Kbd_Sarge_Dive( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge = SargePointer(ARMY_PLAYER);

	if( pSarge->pVehicle )
		user_action |= DO_ACCELERATE;
	else	{
		user_action |= DO_ACCELERATE;
		user_action |= DO_ALT;
	}
}


void Kbd_Sarge_RollRight( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge = SargePointer(ARMY_PLAYER);

	if( pSarge->pVehicle )
		user_action |= DO_GUN_RIGHT;
	else	{
		user_action |= DO_TURN_RIGHT;
		user_action |= DO_ALT;
	}
}


void Kbd_Sarge_RollLeft( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge = SargePointer(ARMY_PLAYER);

	if( pSarge->pVehicle )
		user_action |= DO_GUN_LEFT;
	else	{
		user_action |= DO_TURN_LEFT;
		user_action |= DO_ALT;
	}
}


void Kbd_Sarge_GunRight( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge = SargePointer(ARMY_PLAYER);

	if( pSarge->pVehicle )
		user_action |= DO_GUN_RIGHT;
	else
		user_action |= DO_TURN_RIGHT;
}


void Kbd_Sarge_GunLeft( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge = SargePointer(ARMY_PLAYER);

	if( pSarge->pVehicle )
		user_action |= DO_GUN_LEFT;
	else
		user_action |= DO_TURN_LEFT;
}


void Kbd_Sarge_Up( BYTE nChar, UINT nFlags )
{
	user_action |= DO_ACCELERATE;
}


void Kbd_Sarge_ForwLeft( BYTE nChar, UINT nFlags )
{
	user_action |= DO_ACCELERATE;
	user_action |= DO_TURN_LEFT;
}


void Kbd_Sarge_ForwRight( BYTE nChar, UINT nFlags )
{
	user_action |= DO_ACCELERATE;
	user_action |= DO_TURN_RIGHT;
}


void Kbd_Vehicle_Down( BYTE nChar, UINT nFlags )
{
	user_action |= DO_DECELERATE;
	if ( !(nFlags & Flag_KeyDelta) )
		user_action |= START_DECELERATE;
}

/*
void Kbd_Sarge_Down( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge = SargePointer(ARMY_PLAYER);

	if( pSarge->pVehicle )
	{
		Kbd_Vehicle_Down( nChar, nFlags );
		return;
	}
	else
	{
		if( UI_CurMode == UIMODE_LOOKINGATSARGE )	
		{
			SARGE*	pSarge = SargePointer(ARMY_PLAYER);
			if( !pSarge->pAvatar ) 
				return;								// sarge is pending resurrection
        
			ACTION	pose = AvatarPose(pSarge->pAvatar);
  			if (user_action & DO_SLOW)	
			{
				Kbd_Vehicle_Down( nChar, nFlags );
				return;
			}

			if( !((nFlags & Flag_KeyDelta) || (nFlags & Flag_KeyRepeat)) )
				return;

			switch (pose)	
			{
				case AVATAR_STAND:
					pSarge->pendingPose = AVATAR_KNEEL;
					break;
				case AVATAR_KNEEL:
					pSarge->pendingPose = AVATAR_PRONE;
					break;
			}
		}
		else
		{
			Kbd_Vehicle_Down( nChar, nFlags );
		}
	}
}
*/

void Kbd_Sarge_Down( BYTE nChar, UINT nFlags )
{
	if( !((nFlags & Flag_KeyDelta) || (nFlags & Flag_KeyRepeat)) )
		return;

	SargeDown();
}

void Kbd_Sarge_Slow( BYTE nChar, UINT nFlags )
{
	user_action |= DO_SLOW;
}

void Kbd_Sarge_Alt( BYTE nChar, UINT nFlags )
{
	user_action |= DO_ALT;
}


extern void PlacingItem();

void Kbd_Sarge_Fire( BYTE nChar, UINT nFlags )
{
	switch (UI_CurMode)
	{
		case UIMODE_LOOKINGATSARGE:
			if( nFlags & Flag_KeyDown )
			{
				if( nFlags & Flag_KeyDelta )
					user_action |= START_FIRE;
				user_action |= DO_FIRE;
			}
			break;
		case UIMODE_PLACINGITEM:
			if( nFlags & Flag_KeyDown )
			{
				if( nFlags & Flag_KeyDelta )
					PlacingItem();
			}
			break;
		default:
			if( !(nFlags & Flag_KeyDown) )	{
				if( nFlags & Flag_KeyDelta)
				{
					SargeEndTalk();
					UI_GiveOrder(TRUE);
				}
			}
			break;
	}
}


void Kbd_Sarge_ChgWeapon1( BYTE nChar, UINT nFlags )
{
	if (user_action & DO_FIRE)
		return;

	ActivateSargeWeapon(SargePointer(ARMY_PLAYER),0);
	clearFiringBar();
}

void Kbd_Sarge_ChgWeapon2( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pVehicle )
	{
		if (user_action & DO_FIRE)
			return;

		ActivateSargeWeapon( pSarge, 1 );
		clearFiringBar();
	}
}

void Kbd_Sarge_ChgWeapon3( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pVehicle )
	{
		if (user_action & DO_FIRE)
			return;

		ActivateSargeWeapon( pSarge, 2 );
		clearFiringBar();
	}
}

void Kbd_Sarge_ChgWeapon( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pVehicle )
	{
		if (user_action & DO_FIRE)
			return;

		ActivateNextSargeWeapon( pSarge );
		clearFiringBar();
	}
}

void Kbd_Vehicle_Stop( BYTE nChar, UINT nFlags )
{
	user_action |= DO_STOP;
}

void Kbd_GamePlay_Follow( BYTE nChar, UINT nFlags )
{
	UI_HitFollowKey();
}

extern UNIT* curselectedunit;


void Kbd_GamePlay_Attack( BYTE nChar, UINT nFlags )
{
	if( !curselectedunit )
		return;
	if (user_action & DO_SLOW)
		UI_HitAttackKey(IMMEDIATE);
	else
		UI_HitAttackKey(LATER);
}

void Kbd_GamePlay_Defend( BYTE nChar, UINT nFlags )
{
	if( !curselectedunit )
		return;
	if (user_action & DO_SLOW)
		UI_HitDefendKey(IMMEDIATE);
	else
		UI_HitDefendKey(LATER);
}

void Kbd_GamePlay_AttackNow( BYTE nChar, UINT nFlags )
{
	if( !curselectedunit )
		return;
	UI_HitAttackKey(IMMEDIATE);
}

void Kbd_GamePlay_DefendNow( BYTE nChar, UINT nFlags )
{
	if( !curselectedunit )
		return;
	UI_HitDefendKey(IMMEDIATE);
}

void Kbd_GamePlay_Mission( BYTE nChar, UINT nFlags )
{
	VehicleSoundOff();
	UI_MissionRecall();
}

void Kbd_GamePlay_Map( BYTE nChar, UINT nFlags )
{
	UI_MapRecall();
}

void Kbd_GamePlay_Scroll( BYTE nChar, UINT nFlags )
{
	UI_EnterKey();
}

void Kbd_GamePlay_Chat( BYTE nChar, UINT nFlags )
{
	UI_ChatKey();
}

extern UNIT* holdUnit;
static void NextSwitchUnit()
{
    // goto the next unit deployed or pre-deployable
    BOOL bFound = FALSE;
    UNIT* oldUnit = holdUnit;
    int eArmy;
    LEGION* pLegion;
    if (!holdUnit) bFound = TRUE; // started with sarge, now do any unit
    FOR_EACH_DEPLOYED_ARMY(eArmy)
    {
        pLegion = ArmyGetLegion(eArmy);
        FOR_EACH_UNIT(pLegion,holdUnit)
        {
            if (holdUnit == oldUnit) bFound = TRUE;
            else if (!bFound); // not cycled to current yet
            else if (UNIT_ON_MAP(holdUnit))
                return; // next one
            else if (UNIT_IN_HQ(holdUnit) && holdUnit->deployPosition.x > 1)
                return; // next one
        }
    }
    holdUnit = NULL; // switch to sarge at start of loop
}

void Kbd_GamePlay_AirDrop( BYTE nChar, UINT nFlags )
{
	UI_HitAirDropKey();
}


void Kbd_GamePlay_Recon( BYTE nChar, UINT nFlags )
{
	UI_HitReconKey();
}


void Kbd_GamePlay_AirStrike( BYTE nChar, UINT nFlags )
{
	UI_HitAirStrikeKey();
}


void Kbd_GamePlay_NextUnit( BYTE nChar, UINT nFlags )
{
	UI_NextUnitKey();
}

void Kbd_GamePlay_AltGunsight( BYTE nChar, UINT nFlags )
{
	UseAltGunsight = ! UseAltGunsight;
	Set_GamePlay_AltGunsight();
}

void Kbd_GamePlay_AltMouse( BYTE nChar, UINT nFlags )
{

	UseAltMouseButton = ! UseAltMouseButton;
	Set_GamePlay_AltMouse();
}


#define REG_SIZE 16

void Get_GamePlay_AltGunsight()
{
	char		bData[REG_SIZE];
	DWORD		dwSize = REG_SIZE;

	if (gpComm->RegGet(TEXT("Cursor"), (LPBYTE)&bData, &dwSize))
	{
		if ( strcmp( bData, "White" ) == 0 )
			UseAltGunsight = !(0);
	}
	else
		Set_GamePlay_AltGunsight();
}

void Get_GamePlay_AltMouse()
{
	char		bData[REG_SIZE];
	DWORD		dwSize = REG_SIZE;

	if (gpComm->RegGet(TEXT("MouseRight"), (LPBYTE)&bData, &dwSize))
	{
		if ( strcmp( bData, "Move" ) == 0 )
			UseAltMouseButton = !(0);
	}
	else
		Set_GamePlay_AltMouse();
}

void Set_GamePlay_AltGunsight()
{
	int					len;
	char*				pData;

	if (UseAltGunsight)
		pData     = "White";
	else
		pData     = "Red";
	len = strlen( pData ) + 1;
	gpComm->RegSet(TEXT("Cursor"), (CONST BYTE *)pData, len);
}

void Set_GamePlay_AltMouse()
{
	int					len;
	char*				pData;

	if (UseAltMouseButton)
		pData     = "Move";
	else
		pData     = "ChgWeapon";
	len = strlen( pData ) + 1;
	gpComm->RegSet(TEXT("MouseRight"), (CONST BYTE *)pData, len);
}


void Kbd_GamePlay_Menu( BYTE nChar, UINT nFlags )
{
	Scrn_KDn_Options( nChar, nFlags );
}

void Kbd_Sarge_DropItem( BYTE nChar, UINT nFlags )
{
    SARGE* pSarge = SargePointer(ARMY_PLAYER);
	
    SargeDropWeapon(pSarge,pSarge->common.position,(SARGE_WEAPON)SargeGetActiveWeapon(ARMY_PLAYER));
	clearFiringBar();
}


void Kbd_Sarge_Vehicle( BYTE nChar, UINT nFlags )
{
    if (user_action & DO_FIRE)
		return;
	VehicleSargeFlip();
}

void PlayerClearInput()
{
	user_action = NO_DO_ACTION;
}

void LoadKeyBindings( int eConfigType )
{
	FILE	*fp;
	int		i, j;
	BYTE*	pKey;
	BYTE*	pFixed;
	BYTE	cData;
	char	nVersionByte;
	char*	pFileName = NULL;
	BOOL	bInserted = FALSE;
	char	CONFIGgameKeyCount;
	char	CONFIGsargeKeyCount;
	char	CONFIGjoystickKeyCount;

	// store the current configuration type
	UIcurrentConfig = (CONFIG)eConfigType;

	// get to the proper directory and file
	SetPath(NULL);
	switch( eConfigType )
	{
		case CONFIG_DEFAULT1:
			pFileName = "Default1.cfg";
			break;
		case CONFIG_DEFAULT2:
			pFileName = "Default2.cfg";
			break;
		case CONFIG_CUSTOM:
			pFileName = "Custom.cfg";
			break;
		case CONFIG_JOYSTICK:
			pFileName = "Joystick.cfg";
			break;
		default:
			return;
	}


	fp = fopen( pFileName, "rb" );
	if (fp == NULL)
	{
		SaveKeyBindings(eConfigType);		// create the default settings
		return;
	}
	
	// now check to see if this a prior version of config
	fread( &nVersionByte, 1, 1, fp );
	if ( nVersionByte != CONFIGversion )
	{
		// close this file and overwrite with a current
		// key configuration. All custom data is lost.
		fclose(fp);

		// create the default settings
		SaveKeyBindings(eConfigType);
		return;
	}

	// read in each config key set
	if ( eConfigType != CONFIG_JOYSTICK )
	{
		// determine the number of Sarge Keys
		fread( &(CONFIGsargeKeyCount), 1, 1, fp );
		i = 0;								// load gameplay keys
		while( (SargeKeyDescs[i].dispatcher != NULL) && (i<CONFIGsargeKeyCount) )
		{
			switch( eConfigType )
			{
			case CONFIG_DEFAULT1:
				pKey   = &(SargeKeyDescs[i].DefaultKey1);
				break;
			case CONFIG_DEFAULT2:
				pKey   = &(SargeKeyDescs[i].DefaultKey2);
				break;
			case CONFIG_CUSTOM:
				pKey   = &(SargeKeyDescs[i].CustomKey);
				break;
			case CONFIG_JOYSTICK:
				ASSERT(0);
			default:
				return;
			}

			// now read in the key pair
			fread( pKey, 1, 1, fp );
			fread( &(cData), 1, 1, fp );
			pFixed = &(SargeKeyDescs[i].FixedKey);	// fixed in data

			i++;	// process the next SargeKeyDescs slot
		}

		// determine the number of Game Play Keys
		fread( &(CONFIGgameKeyCount), 1, 1, fp );
		i = 0;								// load gameplay keys
		while( (GamePlayKeyDescs[i].dispatcher != NULL) && (i<CONFIGgameKeyCount) )
		{
			switch( eConfigType )
			{
			case CONFIG_DEFAULT1:
				pKey   = &(GamePlayKeyDescs[i].DefaultKey1);
				break;
			case CONFIG_DEFAULT2:
				pKey   = &(GamePlayKeyDescs[i].DefaultKey2);
				break;
			case CONFIG_CUSTOM:
				pKey   = &(GamePlayKeyDescs[i].CustomKey);
				break;
			case CONFIG_JOYSTICK:
				ASSERT(0);
				break;
			default:
				return;
			}

			// now read in the key
			fread( pKey, 1, 1, fp );
			fread( &(cData), 1, 1, fp );
			pFixed = &(GamePlayKeyDescs[i].FixedKey);	// fixed in data

			i++;	// process the next GamePlayKeyDescs slot
		}

		// finally apply the mouse data
		fread( &MouseDxRotate, 1, 1, fp );
		fread( &MouseTurret, 1, 1, fp );
	}
	else
	if ( eConfigType == CONFIG_JOYSTICK )
	{
		// determine the number of Sarge Keys
		fread( &(CONFIGjoystickKeyCount), 1, 1, fp );
		i = 0;								// load gameplay keys
		while( (JoystickDescs[i].dispatcher != NULL) && (i<CONFIGjoystickKeyCount) )
		{
			pKey   = &(JoystickDescs[i].CustomKey);
			pFixed = &(JoystickDescs[i].FixedKey);

			// now read in the key pair
			fread( pKey, 1, 1, fp );
			fread( pFixed, 1, 1, fp );

#ifndef FINAL
			if (!full_joystick)
#endif			
			{
				if (*pKey > 0 && *pKey <= JOYSTICK_BUTTONS)	{
					if (*pKey > joyButtons)
						*pKey = 0;
				}
			}

			// apply this key to the Joystick UI
			bInserted = FALSE;
			j         = 0;
			while( !bInserted && (JoystickButtons[j].dispatcher != NULL) )
			{
				if( JoystickButtons[j].dispatcher == JoystickDescs[i].dispatcher )
				{
					JoystickButtons[j].key = *pKey;
					bInserted              = TRUE;
				}
				++j;		// try the next JoystickButtons slot
			}
			i++;	// process the next JoystickDescs slot
		}
	}
	fclose(fp);
}


void SaveKeyBindings( int eConfigType )
{
	FILE	*fp;
	FILE	*ap;
	BOOL	bOutputText = FALSE;
	int		i;
	char	CONFIGgameKeyCount;
	char	CONFIGsargeKeyCount;
	char	CONFIGjoystickKeyCount;

	// get to the proper directory
	SetPath(NULL);
	if ( eConfigType == CONFIG_JOYSTICK )
	{
		if (!JoystickActive())
			return;

		CONFIGjoystickKeyCount = 0;
		while( JoystickDescs[ CONFIGjoystickKeyCount ].dispatcher != NULL )
			(CONFIGjoystickKeyCount)++;

		fp = fopen( "joystick.cfg", "wb" );
		if (fp == NULL)
			return;

		ap = fopen( "joystick.txt", "w" );
		if (ap != NULL)
			bOutputText = TRUE;
	}
	else
	{
		// write out each config key set
		// determine the number of Sarge Keys and Game Keys
		CONFIGsargeKeyCount = 0;
		while( SargeKeyDescs[ CONFIGsargeKeyCount ].dispatcher != NULL )
			(CONFIGsargeKeyCount)++;

		CONFIGgameKeyCount = 0;
		while( GamePlayKeyDescs[ CONFIGgameKeyCount ].dispatcher != NULL )
			(CONFIGgameKeyCount)++;

		fp = fopen( "custom.cfg", "wb" );
		if (fp == NULL)
			return;

		ap = fopen( "custom.txt", "w" );
		if (ap != NULL)
			bOutputText = TRUE;
	}

	// write out the version byte
	fwrite( &CONFIGversion,1,1,fp );
	if ( bOutputText )
	{
		fprintf( ap, "Version = %d\n", CONFIGversion );
		fflush( ap );
	}

	if ( eConfigType == CONFIG_JOYSTICK )
	{
		// output the SARGE Keys
		if ( bOutputText )
		{
			fprintf( ap, "JOYSTICK BUTTONS:\n" );
			fflush( ap );
		}

		// write out the number of sarge keys
		fwrite( &(CONFIGjoystickKeyCount),1,1,fp );
		if ( bOutputText )
		{
			fprintf( ap, "Number of Joystick Buttons = %d\n", CONFIGjoystickKeyCount );
			fflush( ap );
		}

		// save off the Joystick Buttons
		i = 0;
		while( (JoystickDescs[i].dispatcher != NULL) && (i<CONFIGjoystickKeyCount) )
		{
			// write the JOYSTICK BUTTONS
			fwrite( &(JoystickDescs[i].CustomKey), 1, 1, fp );
			if ( bOutputText )
			{
				fprintf( ap, "Key %d: \"%s\" %d", i, JoystickDescs[i].desc, JoystickDescs[i].CustomKey );
				fflush( ap );
			}

			// write any FIXED key reference
			fwrite( &(JoystickDescs[i].FixedKey), 1, 1, fp );
			if ( bOutputText )
			{
				fprintf( ap, "Fixed %d\n", JoystickDescs[i].FixedKey );
				fflush( ap );
			}
			i++;
		}

	}
	else
	{
		// output the SARGE Keys
		if ( bOutputText )
		{
			fprintf( ap, "SARGE KEYS:\n" );
			fflush( ap );
		}

		// write out the number of sarge keys
		fwrite( &(CONFIGsargeKeyCount),1,1,fp );
		if ( bOutputText )
		{
			fprintf( ap, "Number of Sarge Keys = %d\n", CONFIGsargeKeyCount );
			fflush( ap );
		}

		// save off the Sarge Keys
		i = 0;
		while( (SargeKeyDescs[i].dispatcher != NULL) && (i<CONFIGsargeKeyCount) )
		{
			// write the CUSTOM key
			fwrite( &(SargeKeyDescs[i].CustomKey), 1, 1, fp );
			if ( bOutputText )
			{
				fprintf( ap, "Key %d: \"%s\" %d \"%s\"",
					i, SargeKeyDescs[i].desc, SargeKeyDescs[i].CustomKey,
					SBtnKeycodeName( SargeKeyDescs[i].CustomKey) );
				fflush( ap );
			}

			// write any FIXED key reference
			fwrite( &(SargeKeyDescs[i].FixedKey), 1, 1, fp );
			if ( bOutputText )
			{
				fprintf( ap, "Fixed %d \"%s\"\n", SargeKeyDescs[i].FixedKey,
					SBtnKeycodeName( SargeKeyDescs[i].FixedKey));
				fflush( ap );
			}
			i++;
		}

		// write out the number of Game keys
		if ( bOutputText )
		{
			fprintf( ap, "GAME PLAY KEYS:\n" );
			fflush( ap );
		}
		fwrite( &(CONFIGgameKeyCount),1,1,fp );
		if ( bOutputText )
		{
			fprintf( ap, "Number of Game Play Keys = %d\n", CONFIGgameKeyCount );
			fflush( ap );
		}

		// save off the Game Play Keys
		i = 0;
		while( (GamePlayKeyDescs[i].dispatcher != NULL) && (i<CONFIGgameKeyCount) )
		{
			// write the CUSTOM key
			fwrite( &(GamePlayKeyDescs[i].CustomKey), 1, 1, fp );
			if ( bOutputText )
			{
				fprintf( ap, "Key %d: \"%s\" %d \"%s\"",
					i, GamePlayKeyDescs[i].desc, GamePlayKeyDescs[i].CustomKey,
					SBtnKeycodeName( GamePlayKeyDescs[i].CustomKey ) );
				fflush( ap );
			}

			// write any FIXED key reference
			fwrite( &(GamePlayKeyDescs[i].FixedKey), 1, 1, fp );
			if ( bOutputText )
			{
				fprintf( ap, "Fixed %d \"%s\"\n",
					GamePlayKeyDescs[i].FixedKey, SBtnKeycodeName( GamePlayKeyDescs[i].CustomKey ) );
				fflush( ap );
			}
			i++;
		}
		if ( bOutputText )
		{
			fprintf( ap, "Mouse DX Rotate = %d\n", MouseDxRotate );
			fprintf( ap, "Mouse Turret    = %d\n", MouseTurret );
			fflush( ap );
		}
		fwrite( &MouseDxRotate, 1, 1, fp );
		fwrite( &MouseTurret, 1, 1, fp );
	}

	fclose(fp);
	if ( bOutputText )
	{
		bOutputText = FALSE;
		fclose(ap);
	}
}


void RestoreDefaultBindings( int eConfigType )
{
	int i=0;

	if ( eConfigType == CONFIG_JOYSTICK )
	{
		RestoreJoystickBindings();
		return;
	}

	// Must be a keyboard configuration restoration
	// restore Sarge
	i = 0;
	while( SargeKeyDescs[i].dispatcher != NULL )
	{
		switch( eConfigType )
		{
			case CONFIG_DEFAULT1:
				SargeKeyDescs[i].CustomKey = SargeKeyDescs[i].DefaultKey1;
				break;
			case CONFIG_DEFAULT2:
				SargeKeyDescs[i].CustomKey = SargeKeyDescs[i].DefaultKey2;
				break;
			default:
				return;
		}
		++i;
	}

	// restore GamePlay
	i = 0;
	while( GamePlayKeyDescs[i].dispatcher != NULL )
	{
		switch( eConfigType )
		{
			case CONFIG_DEFAULT1:
				GamePlayKeyDescs[i].CustomKey = GamePlayKeyDescs[i].DefaultKey1;
				break;
			case CONFIG_DEFAULT2:
				GamePlayKeyDescs[i].CustomKey = GamePlayKeyDescs[i].DefaultKey2;
				break;
			default:
				return;
		}
		++i;
	}

	// now go load up the configuration data
	ScrnLoadConfiguration( SCRNfullScreen, CONFIG_CUSTOM, FALSE );
}

void RestoreJoystickBindings( void )
{
	int i=0;
	// restore Sarge
	i = 0;
	while( JoystickDescs[i].dispatcher != NULL )
	{
		JoystickDescs[i].CustomKey = JoystickDescs[i].DefaultKey1;
		++i;
	}

	// now go load up the configuration data
	ScrnLoadJoystickConfiguration( SCRNfullScreen, CONFIG_JOYSTICK, FALSE );
}


void SelectKeyBindings( int eConfigType )
{
	int					i, j;
	BYTE*				pKey;
	BYTE*				pFixed;
	char*				pData;
	int					len;
	char*				pFileName = NULL;
	BOOL				bInserted = FALSE;

	// store the current configuration type
	UIcurrentConfig = (CONFIG)eConfigType;
	switch( eConfigType )
	{
		case CONFIG_DEFAULT1:
			pData = "Default1";
			len = strlen( pData ) + 1;
			gpComm->RegSet(TEXT("Config"), (CONST BYTE *)pData, len);
			break;
		case CONFIG_DEFAULT2:
			pData = "Default2";
			len = strlen( pData ) + 1;
			gpComm->RegSet(TEXT("Config"), (CONST BYTE *)pData, len);
			break;
		case CONFIG_CUSTOM:
			pData = "Custom";
			len = strlen( pData ) + 1;
			gpComm->RegSet(TEXT("Config"), (CONST BYTE *)pData, len);
			break;

		default:
			ASSERT(0);
			return;
	}

	// set the Sarge keys
	i = 0;
	while( SargeKeyDescs[i].dispatcher != NULL )
	{
		pFixed = &(SargeKeyDescs[i].FixedKey);	// fixed in data
		switch( eConfigType )
		{
			case CONFIG_DEFAULT1:
				pKey = &(SargeKeyDescs[i].DefaultKey1);
				break;
			case CONFIG_DEFAULT2:
				pKey = &(SargeKeyDescs[i].DefaultKey2);
				break;
			case CONFIG_CUSTOM:
				pKey = &(SargeKeyDescs[i].CustomKey);
				break;
		}

		bInserted = FALSE;
		j         = 0;
		while( !bInserted && (SargeKeys[j].dispatcher != NULL) )
		{
			if( SargeKeys[j].dispatcher == SargeKeyDescs[i].dispatcher )
			{
				if ( *pKey == *pFixed )
				{
					SargeKeys[j].key = 0;
					bInserted = TRUE;
				}
				else
				{
					SargeKeys[j].key = *pKey;
					bInserted = TRUE;
				}
			}
			++j;		// try the next SargeKeys slot
		}

		i++;	// process the next SargeKeyDescs slot
	}

	// set the Game Play keys
	i = 0;
	while( GamePlayKeyDescs[i].dispatcher != NULL )
	{
		pFixed = &(GamePlayKeyDescs[i].FixedKey);	// fixed in data
		switch( eConfigType )
		{
			case CONFIG_DEFAULT1:
				pKey = &(GamePlayKeyDescs[i].DefaultKey1);
				break;
			case CONFIG_DEFAULT2:
				pKey = &(GamePlayKeyDescs[i].DefaultKey2);
				break;
			case CONFIG_CUSTOM:
				pKey = &(GamePlayKeyDescs[i].CustomKey);
				break;
		}

		bInserted = FALSE;
		j         = 0;
		while( !bInserted && (GamePlayKeys[j].dispatcher != NULL) )
		{
			if( GamePlayKeys[j].dispatcher == GamePlayKeyDescs[i].dispatcher )
			{
				if ( *pKey == *pFixed )
				{
					GamePlayKeys[j].key = 0;
					bInserted = TRUE;
				}
				else
				{
					GamePlayKeys[j].key = *pKey;
					bInserted = TRUE;
				}
			}
			++j;		// try the next SargeKeys slot
		}
		i++;			// process the next SargeKeyDescs slot
	}
}

// copy the first 4 key bindings from SargeKeys to SetupKeys
void CopyKeyBindingsToSetup()
{
	int j;
	int i=1;	// skip the first one
	while( (SetupKeys[i].dispatcher != NULL) )
	{
		j = 0;
		while( (SargeKeys[j].dispatcher != NULL) )
		{
			if ( SetupKeys[i].dispatcher == SargeKeys[j].dispatcher )
				SetupKeys[i].key = SargeKeys[j].key;
			j++;
		}

		j = 0;
		while( (GamePlayKeys[j].dispatcher != NULL) )
		{
			if ( SetupKeys[i].dispatcher == GamePlayKeys[j].dispatcher )
				SetupKeys[i].key = GamePlayKeys[j].key;
			j++;
		}

		i++;
	}
}

///========================================================================
//								EOF
///========================================================================

