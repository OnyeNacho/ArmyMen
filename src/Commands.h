/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Commands.h $
//
//	DESCRIPTION:	Keyboard interface routines
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, October 20, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Commands.h 22    3/31/98 5:55p Aburgess $
//
//	Copyright (C) 1996-7 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/Commands.h $
//  
//  22    3/31/98 5:55p Aburgess
//  copy sarge directional keys to setup keys for mp
//  
//  21    3/24/98 2:28p Phu
//  change key table for pause state
//  
//  20    3/20/98 6:07p Nrobinso
//  save right button and cursor color state to registry
//  
//  19    3/11/98 3:20p Aburgess
//  modifications to support non-overwriting key bindings
//  
//  18    2/25/98 1:14p Nrobinso
//  add load/save of kye bindings
//  
//  17    2/21/98 5:49p Nrobinso
//  
//  16    2/20/98 6:42p Nrobinso
//  fix default commands
//  
//  15    2/18/98 6:35p Aburgess
//  modifications made to support Joystick and Custom configurations.
//  Corrected BACKSPACE in edit keys. Added Double-Click, and Name-Return
//  advance to next mission. Corrected multiple Callsign select bug.
//  Corrected configuration offset problem.
//  
//  14    2/17/98 3:05p Nrobinso
//  put debug commands on final compile flag
//  
//  13    2/13/98 12:23p Nrobinso
//  joystick command descriptions
//  
//  12    2/12/98 4:17p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  11    2/09/98 1:54p Aburgess
//  modifications made to support IN GAME screens, Cursor control, and
//  Rules presentation
//  
//  10    1/08/98 5:28p Phu
//  chat keys don't control sarge now
//  
//  9     12/14/97 4:29p Phu
//  Vehicles/Sarge now use same key table
//  
//  8     12/13/97 10:17p Phu
//  
//  7     12/12/97 12:19a Phu
//  
//  6     12/11/97 5:08p Phu
//  
//  5     12/11/97 12:05p Phu
//  mouse handler
//  
//  4     12/11/97 9:51a Phu
//  
//  3     12/09/97 12:12p Phu
//  
//  2     11/07/97 3:51p Nrobinso
//  add input variants; have different commands for vehicle and sarge
//  
//  1     10/20/97 3:51p Nrobinso
//  
//	
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

/////////////////////////////////////////////////////////////////////////////
//					DEFINES
/////////////////////////////////////////////////////////////////////////////
typedef	enum
{
	KEYBOARD_KEYS = 0,			// keyboard based default keys
	KEYPAD_KEYS,				// keypad based default keys
	CUSTOM_KEYS,				// custom default keys

	// DO NOT ADD BEYOND THIS POINT
	MAX_CONFIG_KEYS
} CONFIG_KEYS;

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////

extern long user_action;

extern SUserInterface		UI_GAME_PLAY_STATE;
extern SUserInterface		UI_GAME_SETUP_STATE;
extern TKeyBindingEntry		DefaultKeys[];
extern TKeyBindingEntry		SargeKeys[];
extern TKeyBindingEntry		GamePlayKeys[];
extern TKeyBindingEntry		JoystickButtons[];

extern TKeyBindingEntry*	SargeConfigKeys[MAX_CONFIG_KEYS];
extern TKeyBindingEntry*	GameConfigKeys[MAX_CONFIG_KEYS];
extern TKeyBindingEntry		*SetupKeyTable[];
extern TKeyBindingEntry		*SargeKeyTable[];
extern TKeyBindingEntry		*ChatKeyTable[];
extern TKeyBindingEntry		*PauseKeyTable[];

struct TKeyDescriptors
{
	void	(*dispatcher)(BYTE nChar, UINT nFlags);		// function reference
	char	desc[16];									// key text description
	BYTE    CustomKey;									// Custom User mappable keys 
	BYTE	FixedKey;									// Fixed key mappings
	BYTE	DefaultKey1;								// Default key mappings set 1
	BYTE	DefaultKey2;								// Default key mappings set 2
};

extern TKeyDescriptors GamePlayKeyDescs[];
extern TKeyDescriptors SargeKeyDescs[];
extern TKeyDescriptors JoystickDescs[];

void PlayerClearInput();

extern void SaveKeyBindings( int eConfigType );
extern void LoadKeyBindings( int eConfigType );
extern void RestoreDefaultBindings( int eConfigType );
extern void SelectKeyBindings( int eConfigType );
extern void CopyKeyBindingsToSetup();

extern void Get_GamePlay_AltGunsight();
extern void Get_GamePlay_AltMouse();
extern void Set_GamePlay_AltGunsight();
extern void Set_GamePlay_AltMouse();

#endif
