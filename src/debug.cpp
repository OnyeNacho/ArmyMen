//========================================================================
//	FILE:			$Workfile: debug.cpp $
//
//	DESCRIPTION:	Debug stuff
//
//	AUTHOR:			Peter Hu
//
//	CREATED:		Tuesday, August 13, 1996
//
//	REVISION:		$Header: /ArmyMen/src/debug.cpp 133   4/12/98 3:39p Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unauthorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/debug.cpp $
//  
//  133   4/12/98 3:39p Bwilcox
//  hp moved in label disply
//  
//  132   4/10/98 11:30a Bwilcox
//  
//  131   4/10/98 2:36a Dmaynard
//  
//  130   4/10/98 2:02a Dmaynard
//  
//  129   4/09/98 12:46p Dmaynard
//  Display Packet Loss 
//  
//  128   4/09/98 12:04p Bwilcox
//  issargeuntrafficable varies if sarge is npc. new arg added
//  
//  127   4/08/98 11:24p Nrobinso
//  remove debug customization
//  
//  126   4/07/98 1:36a Phu
//  fix for release build
//  
//  125   4/04/98 9:11a Bwilcox
//  cheat fixes
//  
//  124   4/03/98 9:36p Bwilcox
//  cheat fixes
//  
//  122   4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  121   3/31/98 11:37p Aburgess
//  fix customization problems
//  
//  120   3/30/98 12:52p Phu
//  show movement in debug
//  
//  119   3/27/98 4:49p Nrobinso
//  move around stuff we don't want to eliminate
//  
//  118   3/27/98 1:49p Phu
//  survive ALT_TAB dammit
//  
//  117   3/25/98 3:28p Dmaynard
//  Added Debug Switch to Enable TimeOut  code even though we are in a
//  debug build.
//  
//  116   3/24/98 9:28p Bwilcox
//  
//  115   3/24/98 6:57p Nrobinso
//  fixed routingdraw crash
//  
//  114   3/23/98 5:02p Phu
//  don't crash if exceed update rects, just redraw full
//  
//  113   3/22/98 3:16p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  112   3/20/98 2:08p Bwilcox
//  rasied info line total to 200 (nobody checks it for safety, tsk tsk)
//  
//  111   3/19/98 8:31p Phu
//  add info in world objects display
//  
//  110   3/19/98 5:27p Phu
//  additional wobject info
//  
//  108   3/19/98 11:58a Phu
//  
//  107   3/17/98 7:20p Nrobinso
//  move keystext out to screenbtn
//  
//  106   3/17/98 10:24a Dmaynard
//  Added code for Busrt Mode Packet loss emulation
//  
//  105   3/16/98 12:08p Nrobinso
//  new avatar calls
//  
//  104   98-03-11 17:48 Dmaynard
//  
//  103   98-03-11 12:11 Dmaynard
//  
//  102   3/07/98 10:40p Nrobinso
//  maintain invulnerability for all sarges
//  
//  101   3/05/98 2:15p Bwilcox
//  vis layer display
//  
//  100   3/05/98 12:20p Bwilcox
//  
//  99    3/05/98 10:40a Dmaynard
//  Change Comm show show current state of GUaranteed Send Flag.
//  
//  98    3/03/98 4:50p Nrobinso
//  fix name of keypad /
//  
//  97    3/03/98 12:31p Bwilcox
//  add current tad target and visibility info to debug
//  
//  96    3/01/98 8:21p Nrobinso
//  put in XX for unknown keys
//  
//  95    2/26/98 12:36a Dmaynard
//  Changed ave Latency displayed to be the average over the last 100
//  messages, rather than the overall session average latency.
//  
//  94    2/25/98 11:53p Dmaynard
//  Added Latency Simulation
//  
//  93    2/25/98 1:11p Nrobinso
//  remove load/save of key bindings
//  
//  92    2/25/98 11:44a Aburgess
//  corrected SargeKey vs. GameKey problem. Defaults now applied and
//  redisplayed.
//  
//  91    2/24/98 11:29a Dmaynard
//  Comm Latency Debug printouts
//  
//  90    2/24/98 10:56a Bwilcox
//  teleport to oritgin is now teleport to cursor
//  
//  89    2/24/98 10:48a Aburgess
//  modifications made to correct keycode update bug
//  
//  88    2/23/98 4:19p Dmaynard
//  enabled toggling of Send-Guaranteed flag in IPX mode
//  
//  87    2/23/98 3:55p Phu
//  debug objects
//  
//  86    2/20/98 6:14p Nrobinso
//  rename numpad
//  
//  85    2/20/98 4:24p Aburgess
//  disabled Direct Win/Lose during setup mode
//  
//  84    2/18/98 6:35p Aburgess
//  modifications made to support Joystick and Custom configurations.
//  Corrected BACKSPACE in edit keys. Added Double-Click, and Name-Return
//  advance to next mission. Corrected multiple Callsign select bug.
//  Corrected configuration offset problem.
//  
//  83    2/17/98 3:02p Nrobinso
//  put debug commands on final compile flag
//  
//  82    2/17/98 9:31a Aburgess
//  corrected access to joystick button names
//  
//  81    2/17/98 8:56a Aburgess
//  added Joystick text
//  
//  80    2/16/98 6:27p Nrobinso
//  joystick configuration
//  
//  79    2/16/98 1:43p Nrobinso
//  fix first line
//  
//  78    2/13/98 10:06a Aburgess
//  modifications made to further support keyboard configurations. Support
//  of Audio slider bar. implementation of all known buttons
//  
//  77    2/12/98 4:17p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  76    2/11/98 12:05p Phu
//  fill ammo debug key
//  
//  75    2/09/98 2:24p Phu
//  display elevation layer
//  
//  74    2/09/98 1:54p Aburgess
//  modifications made to support IN GAME screens, Cursor control, and
//  Rules presentation
//  
//  73    2/06/98 2:20p Bwilcox
//  vehiclebehavior trace added
//  
//  72    2/05/98 6:08p Bwilcox
//  sarge cane added
//  
//  71    2/05/98 3:39p Bwilcox
//  fixed runvehicle
//  
//  70    2/05/98 9:50a Bwilcox
//  
//  69    2/05/98 9:25a Bwilcox
//  
//  68    2/05/98 9:12a Bwilcox
//  immobile foes in sarge cheat menu
//  
//  67    2/04/98 7:20p Bwilcox
//  
//  66    2/04/98 7:02p Bwilcox
//  
//  65    2/04/98 10:27a Bwilcox
//  
//  64    2/04/98 10:14a Bwilcox
//  removal of dead formation stuff
//  
//  63    2/04/98 9:53a Bwilcox
//  dead code elim and improved trace in debug
//  
//  
//  $Nokeywords:$
///========================================================================


#include "stdafx.h"

#include "Anim.h"
#include "Army.h"
#include "GameFlow.h"
#include "MainFrm.h"
#include "Input.h"
#include "Commands.h"
#include "debug.h"
#include "Avatar.h"
#include "Trooper.h"
#include "Weapon.h"
#include "Item.h"
#include "Sarge.h"
#include "Map.h"
#include "ui.h"
#include "Audio.h"
#include "bmptext.h"
#include "AiAccess.h"
#include "dplay.h"
#include "3doNetwork.h"
#include "comm.h"
#include "fileio.h"
#include "Screen.h"
#include "wobject.h"
#include "miscfile.h"

extern	char*	KeysText[];

extern char *actions[];
extern char labelForces;
extern char scriptDebug;
extern char vehicleBehavior;
extern char MouseDxRotate;
extern char MouseTurret;
extern int currbuttonexplosion;
extern char sargeImmune;
extern char immobileFoe;
extern BOOL explosions;
extern char bw1;


int shiftTrafficable = 0;

static void MakeObjectsVisible();

//	Function prototypes used by key tables - Basic Debugging
void Kbd_Debug_LoseGameDirect( BYTE nChar, UINT nFlags );
void Kbd_Debug_WinGameDirect( BYTE nChar, UINT nFlags );
void Kbd_Debug_RunVehicle( BYTE nChar, UINT nFlags );
void Kbd_Debug_FindTrooper( BYTE nChar, UINT nFlags );
void Kbd_Debug_ViewRadius( BYTE nChar, UINT nFlags );
void Kbd_Debug_FlipAllah( BYTE nChar, UINT nFlags );
void Kbd_Debug_BigCheat( BYTE nChar, UINT nFlags );
void Kbd_Debug_ClearDebug( BYTE nChar, UINT nFlags );
void Kbd_Debug_FireRadius( BYTE nChar, UINT nFlags );
void Kbd_Debug_StartAIControl( BYTE nChar, UINT nFlags );
void Kbd_Debug_MsgTest( BYTE nChar, UINT nFlags );
void Kbd_Debug_Clear( BYTE nChar, UINT nFlags ); 
void Kbd_Record_SaveSingle( BYTE nChar, UINT nFlags ); 
void Kbd_Record_SaveSeriesOn( BYTE nChar, UINT nFlags );
void Kbd_Record_SaveSeriesOff( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_ChangeMode( BYTE nChar, UINT nFlags );
void Kbd_ChangeTrafficability( BYTE nChar, UINT nFlags );

void DebugMode_Comm( void );
void DebugCommText (void ); 

void Kbd_Debug_AnimTest( BYTE nChar, UINT nFlags );
void Kbd_Debug_AnimTestHelp( BYTE nChar, UINT nFlags );
void Kbd_Debug_troop_center( BYTE nChar, UINT nFlags );
void Kbd_Debug_troop_single_step( BYTE nChar, UINT nFlags );
void Kbd_Debug_troop_next_step( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_walk( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_run( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_shuffle( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_fire( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_raise( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_throw( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_stationary( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_dive( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_kneel( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_prone( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_standup( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_invisible( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_TurnLeft( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_TurnRight( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_up( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_down( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_troop_stop( BYTE nChar, UINT nFlags ); 

void Kbd_Debug_TIScrollUp( BYTE nChar, UINT nFlags );
void Kbd_Debug_TIScrollDn( BYTE nChar, UINT nFlags );
void Kbd_Debug_TIActiveToggle( BYTE nChar, UINT nFlags );
void Kbd_Debug_TIArmyToggle( BYTE nChar, UINT nFlags );
void Kbd_Debug_TITrooperToggle( BYTE nChar, UINT nFlags );

void Kbd_Debug_Layers( BYTE nChar, UINT nFlags );
void Kbd_Debug_ClearLayers( BYTE nChar, UINT nFlags );
void Kbd_Debug_LayerBitPads( BYTE nChar, UINT nFlags );
void Kbd_Debug_LayerMovement( BYTE nChar, UINT nFlags );
void Kbd_Debug_LayerVis( BYTE nChar, UINT nFlags );
void Kbd_Debug_LayerNumPads( BYTE nChar, UINT nFlags );
void Kbd_Debug_LayerElevation( BYTE nChar, UINT nFlags );

void Kbd_Debug_Comm( BYTE nChar, UINT nFlags );
void Kbd_Debug_CommDisplay( BYTE nChar, UINT nFlags );
void Kbd_Debug_CommTimeOut( BYTE nChar, UINT nFlags );
void Kbd_Debug_CommGSend( BYTE nChar, UINT nFlags );
void Kbd_Debug_CommBMode( BYTE nChar, UINT nFlags );
void Kbd_Debug_CommFaster( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_CommSlower( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_CommMoreLoss( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_CommLessLoss( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_CommMoreLatency( BYTE nChar, UINT nFlags ); 
void Kbd_Debug_CommLessLatency( BYTE nChar, UINT nFlags ); 

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
void Kbd_Debug_Explosions( BYTE nChar, UINT nFlags );
void Kbd_Debug_Explosions_Toggle( BYTE nChar, UINT nFlags );
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

void Kbd_Debug_WorldCounts( BYTE nChar, UINT nFlags );
void Kbd_Debug_TrooperInfo( BYTE nChar, UINT nFlags );
void Kbd_Debug_Keys( BYTE nChar, UINT nFlags );

void Kbd_Debug_Mouse( BYTE nChar, UINT nFlags );
void Kbd_Debug_MouseRotate( BYTE nChar, UINT nFlags );
void Kbd_Debug_MouseTurret( BYTE nChar, UINT nFlags );

enum EDebugModes
{
	EDM_MainMenu,
	EDM_WorldCounts,
	EDM_TrooperInfo,
	EDM_Layers,
	EDM_AnimTest,
	EDM_Display,
	EDM_Cheat,
	EDM_Game,
	EDM_Keys,
	EDM_Mouse,
	EDM_Comm,
	EDM_DebugModeOff
};

EDebugModes			CurrentDebugMode = EDM_DebugModeOff;
char tempstringbuffer[160];

char *AllahModes[3] =
	{ "Friend", "Allah", "Foe" };


//	Key Tables used for debugging

#ifndef FINAL
TKeyBindingEntry DebugKeys[] = 
{
	{DIK_L,			Kbd_Debug_LoseGameDirect,		ETO_Pressed ,	DIK_LSHIFT,	0},
	{DIK_W,			Kbd_Debug_WinGameDirect,		ETO_Pressed,	DIK_LSHIFT,	0},
	{DIK_B,			Kbd_Debug_RunVehicle,			ETO_Pressed,	DIK_LSHIFT,	0},
	{DIK_C,			Kbd_Debug_FindTrooper,			ETO_Pressed,	DIK_LSHIFT,	0},
	{DIK_V,			Kbd_Debug_ViewRadius,			ETO_Pressed,	DIK_LSHIFT,	0},
	{DIK_G,			Kbd_Debug_FlipAllah,			ETO_Pressed,	DIK_LSHIFT,	0},
	{DIK_Y,			Kbd_Debug_ClearDebug,			ETO_Pressed,	DIK_LSHIFT,	0},
	{DIK_F,			Kbd_Debug_FireRadius,			ETO_Pressed,	DIK_LSHIFT,	0},
	{DIK_F10,		Kbd_Debug_StartAIControl,		ETO_Pressed,	0,	0},
	{DIK_Z,			Kbd_Debug_ChangeMode,			ETO_Pressed,    DIK_LSHIFT,	0},
	{0, NULL, 0, 0,	0}
};

TKeyBindingEntry TestKeys[] = 
{
	{DIK_ESCAPE,	Kbd_Debug_AnimTest,			ETO_Pressed,	0,	0},
	{DIK_H,			Kbd_Debug_AnimTestHelp,     ETO_Pressed,	0,	0},
	{DIK_1,			Kbd_Debug_AnimTest,			ETO_Pressed,	0,	0},
	{DIK_2,			Kbd_Debug_AnimTest,			ETO_Pressed,	0,	0},
	{DIK_3,			Kbd_Debug_AnimTest,			ETO_Pressed,	0,	0},
	{DIK_4,			Kbd_Debug_AnimTest,			ETO_Pressed,	0,	0},
	{DIK_5,			Kbd_Debug_AnimTest,			ETO_Pressed,	0,	0},
	{DIK_6,			Kbd_Debug_AnimTest,			ETO_Pressed,	0,	0},
	{DIK_W,			Kbd_Debug_troop_walk,		ETO_Pressed,	0,	0},
	{DIK_R,			Kbd_Debug_troop_run,		ETO_Pressed,	0,	0},
	{DIK_U,			Kbd_Debug_troop_shuffle,	ETO_Pressed,	0,	0},
	{DIK_F,			Kbd_Debug_troop_fire,		ETO_Pressed,	0,	0},
	{DIK_G,			Kbd_Debug_troop_raise,		ETO_Pressed,	0,	0},
	{DIK_T,			Kbd_Debug_troop_throw,		ETO_Pressed,	0,	0},
	{DIK_X,			Kbd_Debug_troop_stationary,	ETO_Pressed,	0,	0},
	{DIK_I,			Kbd_Debug_troop_invisible,	ETO_Pressed,	0,	0},
	{DIK_K,			Kbd_Debug_troop_kneel,		ETO_Pressed,	0,	0},
	{DIK_P,			Kbd_Debug_troop_prone,		ETO_Pressed,	0,	0},
	{DIK_S,			Kbd_Debug_troop_standup,	ETO_Pressed,	0,	0},
	{DIK_D,			Kbd_Debug_troop_dive,		ETO_Pressed,	0,	0},
	{DIK_LEFT,		Kbd_Debug_troop_TurnLeft,	ETO_Pressed,	0,	0},
	{DIK_RIGHT,		Kbd_Debug_troop_TurnRight,	ETO_Pressed,	0,	0},
	{DIK_DOWN,		Kbd_Debug_troop_down,		ETO_Pressed,	0,	0},
	{DIK_UP,		Kbd_Debug_troop_up,			ETO_Pressed,	0,	0},
	{DIK_SPACE,		Kbd_Debug_troop_center,		ETO_Pressed,	0,	0},
	{DIK_F1,		Kbd_Debug_troop_single_step,ETO_Pressed,	0,	0},
	{DIK_NEXT,		Kbd_Debug_troop_next_step,	ETO_Pressed,	0,	0},
	{0, NULL, 0, 0}
};

TKeyBindingEntry *DMTestKeyTable[] = 
{
	TestKeys,
	NULL
};


TKeyBindingEntry DModeKeys[] = 
{
	{DIK_ESCAPE,	Kbd_Debug_ChangeMode,		ETO_Pressed,	0,	0},
	{DIK_A,			Kbd_Debug_AnimTest,			ETO_Pressed,	0,	0},
	{DIK_D,			Kbd_Debug_Display,			ETO_Pressed,	0,	0},
	{DIK_G,			Kbd_Debug_Game,				ETO_Pressed,	0,	0},
	{DIK_L,			Kbd_Debug_Layers,			ETO_Pressed,	0,	0},
	{DIK_S,			Kbd_Debug_Cheat,			ETO_Pressed,	0,	0},
	{DIK_T,			Kbd_Debug_TrooperInfo,		ETO_Pressed,	0,	0},
	{DIK_W,			Kbd_Debug_WorldCounts,		ETO_Pressed,	0,	0},
	{DIK_K,			Kbd_Debug_Keys,				ETO_Pressed,    0,  0},
	{DIK_M,			Kbd_Debug_Mouse,			ETO_Pressed,	0,	0},
	{DIK_C,			Kbd_Debug_Comm,				ETO_Pressed,	0,	0},
	{0, NULL, 0,	0,	0}
};

TKeyBindingEntry *DModeKeyTable[] =
{
	DModeKeys,
	NULL
};


TKeyBindingEntry DMLayerKeys[] =
{
	{DIK_ESCAPE,	Kbd_Debug_Layers,			ETO_Pressed,	0,	0},
	{DIK_C,			Kbd_Debug_ClearLayers,		ETO_Pressed,	0,	0},
	{DIK_B,			Kbd_Debug_LayerBitPads,     ETO_Pressed,	0,	0},
	{DIK_M,			Kbd_Debug_LayerMovement,    ETO_Pressed,	0,	0},
	{DIK_N,			Kbd_Debug_LayerNumPads,     ETO_Pressed,	0,	0},
	{DIK_E,			Kbd_Debug_LayerElevation,	ETO_Pressed,	0,	0},
	{DIK_V,			Kbd_Debug_LayerVis,			ETO_Pressed,	0,	0},
	{0, NULL, 0, 0,	0}
};

TKeyBindingEntry *DMLayerKeyTable[] =
{
	DMLayerKeys,
	NULL
};

TKeyBindingEntry DMCommKeys[] =
{
	{DIK_ESCAPE,	Kbd_Debug_Comm	,				ETO_Pressed,	0,	0},
	{DIK_D,			Kbd_Debug_CommDisplay,			ETO_Pressed,	0,	0},
	{DIK_G,			Kbd_Debug_CommGSend,		    ETO_Pressed,	0,	0},
	{DIK_T,			Kbd_Debug_CommTimeOut,		    ETO_Pressed,	0,	0},
	{DIK_B,			Kbd_Debug_CommBMode,		    ETO_Pressed,	0,	0},
	{DIK_F,			Kbd_Debug_CommFaster,			ETO_Pressed,	0,	0},
	{DIK_S,			Kbd_Debug_CommSlower,			ETO_Pressed,	0,	0},
	{DIK_X,			Kbd_Debug_CommMoreLoss,			ETO_Pressed,	0,	0},
	{DIK_Z,			Kbd_Debug_CommLessLoss,			ETO_Pressed,	0,	0},
	{DIK_Q,			Kbd_Debug_CommLessLatency,		ETO_Pressed,	0,	0},
	{DIK_W,			Kbd_Debug_CommMoreLatency,		ETO_Pressed,	0,	0},
	{0, NULL, 0, 0,	0}
};

TKeyBindingEntry *DMCommKeyTable[] =
{
	DMCommKeys,
	NULL
};


TKeyBindingEntry DMDisplayKeys[] =
{
	{DIK_ESCAPE,	Kbd_Debug_Display,			ETO_Pressed,	0,	0},
	{DIK_A,			Kbd_Debug_FlipAllah,		ETO_Pressed,	0,	0},
	{DIK_G,			Kbd_Debug_VehicleTrace,		ETO_Pressed,	0,	0},
	{DIK_T,			Kbd_ChangeTrafficability,	ETO_Pressed,	0,	0},
	{DIK_C,			Kbd_Debug_ClearDisplay,		ETO_Pressed,	0,	0},
	{DIK_H,			Kbd_Debug_FlipHotspots,     ETO_Pressed,	0,	0},
	{DIK_R,			Kbd_Debug_RouteDraw,	    ETO_Pressed,	0,	0},
	{DIK_L,			Kbd_Debug_LabelDraw,	    ETO_Pressed,	0,	0},
	{DIK_B,			Kbd_Debug_BigCheat,			ETO_Pressed,	0,	0},
	{0, NULL, 0, 0,	0}
};


TKeyBindingEntry *DMDisplayKeyTable[] =
{
	DMDisplayKeys,
	NULL
};


TKeyBindingEntry DMCheatKeys[] =
{
	{DIK_ESCAPE,	Kbd_Debug_Cheat,			ETO_Pressed,	0,	0},
	{DIK_E,			Kbd_Debug_Explosions,		ETO_Pressed,	0,	0, "", 200},
	{DIK_R,			Kbd_Debug_Explosions_Toggle,ETO_Pressed,	0,	0, "", 200},
	{DIK_A,			Kbd_Debug_AddAirstrikes,	ETO_Pressed,	0,	0},
	{DIK_I,			Kbd_Debug_SargeInvulnerable,ETO_Pressed,	0,	0},
	{DIK_C,			Kbd_Debug_SargeCane,		ETO_Pressed,	0,	0},
	{DIK_U,			Kbd_Debug_FoeImmobile,		ETO_Pressed,	0,	0},
	{DIK_Q,			Kbd_Debug_SargeQuestItem,	ETO_Pressed,	0,	0},
	{DIK_M,			Kbd_Debug_Travel,			ETO_Pressed,	0,	0},
	{DIK_J,			Kbd_Debug_DeployJeep,		ETO_Pressed,	0,	0},
	{DIK_H,			Kbd_Debug_DeployHalftrack,	ETO_Pressed,	0,	0},
	{DIK_T,			Kbd_Debug_DeployTank,		ETO_Pressed,	0,	0},
	{DIK_O,			Kbd_Debug_Teleport,			ETO_Pressed,	0,	0},
	{DIK_B,			Kbd_Debug_RunVehicle,		ETO_Pressed,	0,	0},
	{DIK_F,			Kbd_Debug_MaxAmmo,			ETO_Pressed,	0,	0},
	{0, NULL, 0, 0,	0}
};


TKeyBindingEntry *DMCheatKeyTable[] =
{
	DMCheatKeys,
	NULL
};


TKeyBindingEntry TrooperInfoKeys[] =
{
	{DIK_LBRACKET,		Kbd_Debug_TIScrollUp,		ETO_Pressed,	0,	0, "", 150},
	{DIK_RBRACKET,		Kbd_Debug_TIScrollDn,		ETO_Pressed,	0,	0, "", 150},
	{DIK_BACKSLASH,		Kbd_Debug_TIActiveToggle,	ETO_Pressed,	0,	0, "", 0},
	{DIK_A,		Kbd_Debug_TIArmyToggle,	ETO_Pressed,	0,	0, "", 0},
	{DIK_BACKSPACE,		Kbd_Debug_TITrooperToggle,  ETO_Pressed,	0,	0, "", 0},
	{0, NULL, 0, 0, 0, 0}
};


TKeyBindingEntry *TrooperInfoKeyTable[] =
{
	TrooperInfoKeys,
	DebugKeys,
	GamePlayKeys,
	SargeKeys,
	NULL	
};


TKeyBindingEntry *WorldCountsKeyTable[] =
{
	DebugKeys,
	GamePlayKeys,
	SargeKeys,
	NULL	
};


TKeyBindingEntry DMGameKeys[] =
{
	{DIK_ESCAPE,	Kbd_Debug_Game,				   ETO_Pressed,	0,	0},
	{DIK_L,			Kbd_Debug_LoseGame,			   ETO_Pressed,	0,	0},
	{DIK_W,			Kbd_Debug_WinGame,			   ETO_Pressed,	0,	0},
	{DIK_S,			Kbd_Debug_AudioKill,		   ETO_Pressed,	0,	0},
	{DIK_M,			Kbd_Debug_MusicToggle,		   ETO_Pressed,	0,	0},
	{DIK_X,			Kbd_Debug_SoundToggle,		   ETO_Pressed,	0,	0},
	{0, NULL, 0, 0,	0}
};


TKeyBindingEntry *DMGameKeyTable[] =
{
	DMGameKeys,
	NULL
};


TKeyBindingEntry DMKeysKeys[] =
{
	{DIK_ESCAPE,	Kbd_Debug_Keys,				ETO_Pressed,	0,	0},
	{0, NULL, 0, 0,	0}
};


TKeyBindingEntry *DMKeysKeyTable[] =
{
	DMKeysKeys,
	NULL
};


TKeyBindingEntry DMMouseKeys[] =
{
	{DIK_ESCAPE,	Kbd_Debug_Mouse,			ETO_Pressed,	0,	0},
	{DIK_R,			Kbd_Debug_MouseRotate,		ETO_Pressed,	0,	0},
	{DIK_T,			Kbd_Debug_MouseTurret,		ETO_Pressed,	0,	0},
	{0, NULL, 0, 0,	0}
};


TKeyBindingEntry *DMMouseKeyTable[] =
{
	DMMouseKeys,
	NULL
};




char *LegionColors[4] =
	{
		"GREEN", "TAN", "BLUE", "GREY"
	};
char *VehicleTypes[] =
	{
		"NULL", "Jeep", "Tank", "Half", "Conv", "Cmdr"
	};
char *VehicleStates[] =
	{
		"Undep", "Activ", "Dying"
	};
char *UnitTypes[] =
	{
		"Rifl", "Gren", "Flam", "Bzka", "Engr", "Mort", "Mine"
	};
char *UnitModes[] =
	{
		"Dead", "InHQ", "InVeh", "Still", "Move", "Engag", "Dying"
	};
extern char *UnitOrderText[];

char *Behaviors[] =
	{
		"Ignore", "Returnfire", "Defend", "Attack", "Nest", "Prone","Kneel","Stand","Evade"
	};

char *ItemTypes[] =
	{
		"Null", "Unit", "Vehi", "Proj", "Trpr", "Sarg", "Asst", "Stru", "Obst"
	};
extern char* fstatuses[];
char *OverrideStatus[] =
	{
		"", "avoid veh", "waittrooper", "+waittrooper", "posewait"
	};


/*
	Debugging Functions
*/

extern char triggerFireDraw;
extern char triggerViewDraw;
void sendbuttonfunc(int x);
void switchtargetenemybuttonfunc(int x);
void switchtargetbuttonfunc(int x);

static void dumpVehicle(VEHICLE* pVehicle,char* text)
{
     char tempstringbuffer[200];

    sprintf(text, " %4s(%12s): %5s", 
            VehicleTypes[ITEM_CLASS(pVehicle)],
            pVehicle->common.label ? pVehicle->common.label : "No Label",
            VehicleStates[pVehicle->state]);
   if( (!pVehicle->common.pTad) && (pVehicle->state == VEHICLE_DEPLOYED) )
       strcat(text, "  ERROR: Vehicle has NULL tad!" );
   else if( pVehicle->state == VEHICLE_DEPLOYED )
   {
        sprintf( tempstringbuffer, "  %dammo  [%3d,%3d]",
                 pVehicle->common.pWeapon->nAmmo,
                pVehicle->common.position.x, 
                pVehicle->common.position.y);
      strcat(text, tempstringbuffer );
      if( pVehicle->controller )
      {
          sprintf( tempstringbuffer, "  {%s,%s}", 
                    Behaviors[pVehicle->imode], Behaviors[pVehicle->atmode] );
          strcat(text, tempstringbuffer );
      }
   }
}   

BOOL TIActiveOnly = TRUE;
int TIArmies = 0;
BOOL TITroopers = TRUE;
int  TrooperInfoMode = 0;
char TrooperInfoText[200][80];
int  TrooperInfoLines = 0;
int  TrooperInfoCurLine = 0;
int  TrooperInfoHeader = 1;


static void dumpUnit(UNIT* pUnit,char* text)
{
	char tempstringbuffer[200]; SPOINT pos;
    char victim[100];
    char seen;
    ITEM* pVictim;
    TAD* pTad;
    pTad = TadCurrentTarget((ITEM*)pUnit);
    pVictim = (pTad) ? pTad->pItem : NULL;
    victim[0] = 0;
    if (pVictim) sprintf(victim,"%s",ItemDBName(pVictim));

    if (ITEM_ARMY(pUnit) == ARMY_PLAYER)
        seen = ItemVisible(ARMY_TAN,(ITEM*)pUnit);
    else
        seen = ItemVisible(ARMY_PLAYER,(ITEM*)pUnit);
    seen = (seen) ? '@' : ' ';
    
    if (TITroopers)
    {
        sprintf(text, " %d.%d %s %c",
            ITEM_ARMY(pUnit)+1,ITEM_INDEX(pUnit),
            pUnit->common.label ? pUnit->common.label :  UnitTypes[ITEM_CLASS(pUnit)],
        seen);
    }
    else
    {
        sprintf(text, " %d.%d (%s) %c %s Troops=%d",
            ITEM_ARMY(pUnit)+1,ITEM_INDEX(pUnit),
            pUnit->common.label ? pUnit->common.label : AiUnitShortName(pUnit),
            seen,
            UnitTypes[ITEM_CLASS(pUnit)],
            pUnit->nLastTroop + 1);
    }
    if( (!pUnit->common.pTad) && (pUnit->mode > UNIT_IN_HQ ) )
        strcat(text, "  ERROR: Unit has NULL tad!" );
    else if( pUnit->common.tile && UntrafficableUnit(pUnit->common.tile) )
    {
        strcat(text, "  ERROR- Untrafficable! " );
    }
    else
    {
        char c = ' ';
        char c0 = ' ';
        if (IS_POSTSTATION(pUnit)) c = '*';
        else c0 = '*';

        switch( pUnit->mode )
        {
            case UNIT_DEAD:
                strcat(text, "  Dead" );
                break;
            case UNIT_IN_HQ:
                if( pUnit->paratrooper )
                    strcat(text, "  Paratrooper" );
                else if( pUnit->deployPosition.y > 0 )
                {
                    sprintf( tempstringbuffer, "  InHQ  Deploy %d.%d",
							pUnit->deployPosition.x,
							pUnit->deployPosition.y);
                    strcat(text, tempstringbuffer );
                }
                else
                    strcat(text, "  Not in mission" );
                break;
            case UNIT_IN_VEHICLE:
                if( pUnit->pVehicle )
                {
                    sprintf( tempstringbuffer, " In Vehicle %s(%s)",
						VehicleTypes[ITEM_CLASS(pUnit->pVehicle)],
						pUnit->pVehicle->common.label ? pUnit->pVehicle->common.label : "No Label" );
                    strcat(text, tempstringbuffer );
                }
                else
                    strcat(text, "  InVe  Vehicle ???" );
                break;
            case UNIT_STILL:
                sprintf( tempstringbuffer, " %d.%d %s %s {%c%s,%c%s} %s",
						pUnit->common.position.x, pUnit->common.position.y,
						UnitModes[pUnit->mode],
						UnitOrderText[pUnit->order],
                            c0,Behaviors[pUnit->prestationBehavior],c,
						Behaviors[pUnit->poststationBehavior],
                        victim);
                 strcat(text, tempstringbuffer );
                 break;
             case UNIT_MOVING:
                 pos = pUnit->focusLocation;
                 sprintf( tempstringbuffer, " %d.%d => %d.%d %s %s {%c%s,%c%s} %s",
						pUnit->common.position.x, pUnit->common.position.y,
						pos.x, pos.y,
						UnitModes[pUnit->mode],
						UnitOrderText[pUnit->order],
                        c0,Behaviors[pUnit->prestationBehavior],c,
						Behaviors[pUnit->poststationBehavior],
                        victim);
                   strcat(text, tempstringbuffer );
                   break;
              case UNIT_ENGAGED:
                  sprintf( tempstringbuffer, " %d.%d %s %s {%c%s,%c%s} ",
						pUnit->common.position.x, pUnit->common.position.y,
						UnitModes[pUnit->mode],
						UnitOrderText[pUnit->order],
                        c0,Behaviors[pUnit->prestationBehavior],c,
						Behaviors[pUnit->poststationBehavior]);
                  strcat(text, tempstringbuffer );
                  if( pUnit->pTarget )
                  {
                      sprintf( tempstringbuffer, "%s",
                          pUnit->pTarget->label ? pUnit->pTarget->label :
                              ItemTypes[ITEM_TYPE(pUnit->pTarget)]
                      );
					  strcat(text, tempstringbuffer );
                  }
                  else
                  {
                      strcat(text, "???" );
                  }
                  break;
              case UNIT_DYING:
                  sprintf( tempstringbuffer, " %d.%d Dying!",
						pUnit->common.position.x, pUnit->common.position.y );
                  strcat(text, tempstringbuffer );
                  break;
              default:
                  strcat(text, "  Unknown State" );
                  break;
              }
    }
}

void dumpTrooper(TROOPER* pTrooper,char* text)
{
    char tempstringbuffer[200];
    if( pTrooper->common.tile && UntrafficableUnit( pTrooper->common.tile ) )
    {
        strcat(text, "ERROR- Untrafficable!" );
    }
    else if( pTrooper->mode == TROOPER_DYING )
    {
        strcat(text, "dying" );
    }
    else if (pTrooper->pUnit->mode == UNIT_ENGAGED)
    {
        sprintf( tempstringbuffer, 
                 " %s av=%s %s %s",
                      actions[ pTrooper->pendingAction],
                     pTrooper->pAvatar ? actions[ pTrooper->pAvatar->current_action ] : "NoAv",
                     OverrideStatus[pTrooper->override],
                     fstatuses[ pTrooper->fstatus ]
                                  );
        strcat( text, tempstringbuffer );
    }
    else 
    {
        sprintf( tempstringbuffer, 
                 "%s av=%s %s",
                   actions[ pTrooper->pendingAction],
                     pTrooper->pAvatar ? actions[ pTrooper->pAvatar->current_action ] : "NoAv",
                     OverrideStatus[pTrooper->override]
                                  );
        strcat( text, tempstringbuffer );
    }
}

void Kbd_Debug_RunVehicle( BYTE nChar, UINT nFlags )
{    VEHICLE* pVehicle;
    SPOINT x;
    x.x = (short)CursorPos.x;
    x.y = (short)CursorPos.y;
	int i;
	LEGION* pLegion = ArmyGetLegion(ARMY_PLAYER);
    ScreenToWorld(&x);
    for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
    {
        pVehicle = pLegion->pLegionVehicles[i];
        if (pVehicle->common.tile == 0) continue;
        if (pVehicle->aiGoal.x) continue;
        break;
    }
    if (i >= pLegion->nNumberOfVehicles) return;
    
    pVehicle->humanAI = 1; // enable humanrun AI
    pVehicle->aiGoal = x;
}


extern TROOPER* traceTrooper;
TROOPER* debugTrooper = NULL;
VEHICLE* debugVehicle = NULL;
UNIT* debugUnit = NULL;

void Kbd_Debug_FindTrooper( BYTE nChar, UINT nFlags )
{
    int d = 999999,n;
    TROOPER* pBestTrooper = NULL;
    UNIT* pUnit;
    VEHICLE* pVehicle = NULL;
    VEHICLE* pBestVehicle = NULL;
    int eArmy;
    LEGION* pLegion;
    TROOPER* pTrooper;
    int i,vehicle;
    SPOINT x;
    IPOINT tile;
    x.x = (short)CursorPos.x;
    x.y = (short)CursorPos.y;
    ScreenToWorld(&x);
    tile = ENCODE_IPOINT(x.x,x.y);
    FOR_EACH_DEPLOYED_ARMY(eArmy)
    {
        pLegion = ArmyGetLegion(eArmy);
        FOR_EACH_UNIT(pLegion,pUnit)
        {
			if (!UNIT_ON_MAP(pUnit)) continue;
            FOR_EACH_TROOPER(pUnit,pTrooper,i)
            {
                n = TileDistance(tile,pTrooper->common.tile);
                if (n < d)
                {
                    d = n;
                    pBestTrooper = pTrooper;
                }
            }
        }
        FOR_EACH_VEHICLE(pLegion,vehicle)
        {
            pVehicle = pLegion->pLegionVehicles[vehicle];
            if (pVehicle->state != VEHICLE_DEPLOYED) continue;
            n = TileDistance(tile,pVehicle->common.tile);            
            if (n < d)
            {
                d = n;
                pBestVehicle = pVehicle;
            }
        }
    }
	if (n > 10)
    {
        pBestVehicle = NULL;
        pBestTrooper = NULL;
    }
    if (pBestVehicle)
    {
        char text[200];
        debugVehicle =  pBestVehicle;
        dumpVehicle(debugVehicle,text);
        TRACE("found %s %s\n",ItemDBName(debugVehicle),text);
    }
    else if (pBestTrooper)
    {
        char text[200];
        traceTrooper = pBestTrooper;
        debugTrooper = pBestTrooper;
        dumpTrooper(debugTrooper,text);
        TRACE("found %s %s\n",ItemDBName(debugTrooper),text);
        debugUnit = pBestTrooper->pUnit;
        dumpUnit(debugUnit,text);
        TRACE("found %s %s\n",ItemDBName(debugUnit),text);
    }
}


void Kbd_Debug_ViewRadius( BYTE nChar, UINT nFlags )
{
    triggerViewDraw = TRUE;
}


void Kbd_Debug_ClearDebug( BYTE nChar, UINT nFlags )
{
	ZeroMemory(the_map.debug_layer, the_map.width * the_map.height * sizeof(char));
	DisplayDebugInBox(&the_map.TileBox);
}


void Kbd_Debug_FireRadius( BYTE nChar, UINT nFlags )
{
    triggerFireDraw = TRUE;
}


void Kbd_Debug_StartAIControl( BYTE nChar, UINT nFlags )
{
    AIControlUI();
}


void VehicleDeployType( ARMY_TYPE eArmy, VEHICLE_TYPE eVehicleType, SPOINT *pPos, short facing );


void Kbd_Debug_DeployVehicle( BYTE nChar, UINT nFlags )
{
	SARGE* pSarge = SargePointer(ARMY_PLAYER);
	switch( nChar )
	{
		case DIK_7:
			VehicleDeployType( ARMY_PLAYER, ARMY_JEEP, &pSarge->common.position, pSarge->common.facing );
			break;
		case DIK_8:
            VehicleDeployType( ARMY_PLAYER, ARMY_HALFTRACK, &pSarge->common.position, pSarge->common.facing );
            break;
		case DIK_9:
            VehicleDeployType( ARMY_PLAYER, ARMY_TANK, &pSarge->common.position, pSarge->common.facing );
            break;
	}
}


void Kbd_Debug_MsgTest( BYTE nChar, UINT nFlags )
{
}

void Kbd_Debug_Clear( BYTE nChar, UINT nFlags ) 
{
	pMainFrame->OnAvenue();
}


void Kbd_Record_SaveSingle( BYTE nChar, UINT nFlags ) 
{
	gpGame->SaveSingle();
}


void Kbd_Record_SaveSeriesOn( BYTE nChar, UINT nFlags )
{
	gpGame->SaveSeriesOn();
}


void Kbd_Record_SaveSeriesOff( BYTE nChar, UINT nFlags ) 
{
	gpGame->SaveSeriesOff();
}


TKeyBindingEntry	**previousUI = NULL;
EDebugModes			previousDM = CurrentDebugMode;


#define NUM_DEBUG_LINES		21
#define DEBUG_LINE_HEIGHT	16

char DebugLines[NUM_DEBUG_LINES][80];
int  DebugLineNumber = 0;
BYTE DebugColor;
char *OnOffString[2] =
	{ "ON", "OFF" };
char *routingString[3] =
	{ "ON1", "ON2","OFF" };

void ClearDebugInfo( void )
{
	for( int i = 0; i < NUM_DEBUG_LINES; i++ )
		strcpy( DebugLines[i], "" );
	DebugLineNumber = 0;
}


void AddDebugLine( char *str )
{
	if( DebugLineNumber >= NUM_DEBUG_LINES )
	{
		for( int i = 1; i < NUM_DEBUG_LINES; i++ )
			strcpy( DebugLines[i-1], DebugLines[i] );
		DebugLineNumber = NUM_DEBUG_LINES-1;
	}
	strncpy( DebugLines[DebugLineNumber++], str, 79 );
}


void SetDebugLine( int i, char *str )
{
	ASSERT( i < NUM_DEBUG_LINES );

	while( i > DebugLineNumber )
		strcpy( DebugLines[DebugLineNumber++], "" );
	strncpy( DebugLines[i], str, 79 );
	if( i >= DebugLineNumber )
		DebugLineNumber++;
}


extern struct TGroundObjectsArray GroundObjects;
extern struct TWorldObjectsArray  WorldObjects;
extern struct TWorldObjectsArray  FlashObjects;
extern	int	debug_updatelistcount;
extern  int debug_displaylistcount;


void UpdateWorldCounts( void )
{
	static int updatelist_avgs[16] = 
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	static int updatelist_avgi = 0;
	int	updatelist_avg, updatelist_max;
	int i;

	updatelist_avgs[ updatelist_avgi++ ] = debug_updatelistcount;
	if( updatelist_avgi > 15 )
		updatelist_avgi = 0;
	for( i = 0, updatelist_max = updatelist_avg = 0; i < 16; i++ )
	{
		updatelist_avg += updatelist_avgs[i];
		if( updatelist_avgs[i] > updatelist_max )
			updatelist_max = updatelist_avgs[i];
	}
	if( DebugLineNumber > 5 )
		ClearDebugInfo();

	DebugColor = YELLOW_IDX;
	SetDebugLine( 0, "WORLD OBJECTS DATA - [LSHIFT-Z] to access Main Menu" );
	SetDebugLine( 1, "" );
	sprintf( tempstringbuffer, "GroundObjects: %4d", GroundObjects.count );
	SetDebugLine( 2, tempstringbuffer );
	sprintf( tempstringbuffer, "WorldObjects:  %4d", WorldObjects.count );
	SetDebugLine( 3, tempstringbuffer );
	sprintf( tempstringbuffer, "FlashObjects:  %4d", FlashObjects.count );
	SetDebugLine( 4, tempstringbuffer );
	sprintf( tempstringbuffer, "UpdateRects (avg, max over 16frames):  %4d, %4d", updatelist_avg >> 4, updatelist_max );
	SetDebugLine( 5, tempstringbuffer );
	sprintf( tempstringbuffer, "Max Display Rects: %d", debug_displaylistcount );
	SetDebugLine( 6, tempstringbuffer );
	sprintf( tempstringbuffer, "" );
	SetDebugLine( 7, tempstringbuffer );
	if( UI_CurMode == UIMODE_SCROLLING )
	{
		ITEM *pItemList;
		SPOINT pt;
		int i;

		pt.x = (short)CursorPos.x;
		pt.y = (short)CursorPos.y;
		i = 7;
		if ( pt.y < 384 )
		{
			pt.x += the_map.PixelBox.x;
			pt.y += the_map.PixelBox.y;

			pItemList = GetObjectsMaskPoint( &pt );
			while( pItemList )
			{
				switch( ITEM_TYPE(pItemList) )
				{
				case ARMY_ASSET:
				case ARMY_STRUCTURE:
				case ARMY_OBSTACLE:
					OBJECTSTRUCT *pObject;

					pObject = (OBJECTSTRUCT *)pItemList;
					sprintf( tempstringbuffer, "%s  #%d  DMG:%d  HS:(%d,%d)  L:%d  HP:%d  A:%d  GP:%d M:%d MV:%d\n",
						ItemName(pItemList), 
						pObject->number,
						pObject->damageindex,
						pObject->cell.pSprite->hotspot.x, pObject->cell.pSprite->hotspot.y,
						(int)pObject->layer, pObject->common.nStrength, pObject->armor, pObject->group,
						pObject->cell.pSprite->pMask ? 1 : 0, pObject->movement);
					SetDebugLine( i, tempstringbuffer );
					i++;
					if( i > 20 )
						pItemList = NULL;
					else
						pItemList = pItemList->next;
					break;
				default:
					pItemList = pItemList->next;
					break;
				}
			}
		}
	}
	//	Clear rest of lines
	while( i <= 20 )
		SetDebugLine( i++, "" );
}


int UpdateTI_Legions( void )
{
	int eArmy, lines;
	LEGION	*pLegion;
	VEHICLE *pVehicle;
	UNIT	*pUnit;
	TROOPER *pTrooper;

	lines = 0;
    FOR_EACH_DEPLOYED_ARMY(eArmy)
    {
        if (TIArmies && (eArmy != (TIArmies-1))) continue;

        pLegion = &Armies[ eArmy ].Legion;

		int i = PlayerColor((ARMY_TYPE)eArmy);
        int seen;

		if( pLegion->nTotalUnits > 0 || pLegion->nNumberOfVehicles > 3 || pLegion->Sarge.pAvatar )
			sprintf( TrooperInfoText[lines++], "%s ARMY (%2d Units,  %2d Vehicles,  %2d Assets,  %sSarge", 
				LegionColors[i], 
				pLegion->nTotalUnits, 
				pLegion->nNumberOfVehicles, 
				pLegion->nAssets,
				pLegion->Sarge.pAvatar ? "" : "No ");
		else
			continue;

		if( pLegion->Sarge.pAvatar )
		{
			SARGE	*pSarge = &(pLegion->Sarge);
			AVATAR	*pAvatar = pSarge->pAvatar;
            if (eArmy == ARMY_PLAYER)
                seen = ItemVisible(ARMY_TAN,(ITEM*)pSarge);
            else
                seen = ItemVisible(ARMY_PLAYER,(ITEM*)pSarge);
            seen = (seen) ? '@' : ' ';

			sprintf( TrooperInfoText[lines], " Sarg(%12s) %c   ",
				pSarge->common.label ? pSarge->common.label : "No Label",
                seen);

			if( !pSarge->common.pTad )
				strcat( TrooperInfoText[lines], "ERROR: Sarge has NULL tad!" );
			else
			if( pSarge->pVehicle )
			{
				sprintf( tempstringbuffer, "[%3d,%3d]  Driving Vehicle: %4s(%s)",
					pSarge->pVehicle->common.position.x,
					pSarge->pVehicle->common.position.y,
					VehicleTypes[ITEM_CLASS(pSarge->pVehicle)],
					pSarge->pVehicle->common.label ? pSarge->pVehicle->common.label : "No Label" );
				strcat( TrooperInfoText[lines], tempstringbuffer );
			}
			else
			{
				if( isSargeUntrafficable(pSarge,pSarge->common.position))
				{
					sprintf( tempstringbuffer, "[%3d,3d] is untrafficable at pt(%d,%d)",
						pSarge->common.position.x >> 4, 
						pSarge->common.position.y >> 4,
						pSarge->common.position.x, 
						pSarge->common.position.y );
				}
				else
				{
					sprintf( tempstringbuffer, "[%3d,%3d] req(%s) cur(%s) fac(%d) avf(%d)",
						pSarge->common.position.x >> 4, 
						pSarge->common.position.y >> 4,
						actions[pSarge->pAvatar->avatar_action],
						actions[pSarge->pAvatar->current_action],
						pSarge->pAvatar->pAnimation->facing,
						pSarge->pAvatar->facing);
				}
				strcat( TrooperInfoText[lines], tempstringbuffer );
			}
			lines++;
        }

        FOR_EACH_VEHICLE(pLegion,i)
        {
			pVehicle = pLegion->pLegionVehicles[i];
			if( pVehicle )
			{
				if( TIActiveOnly && (pVehicle->state != VEHICLE_DEPLOYED) )
					continue;
                dumpVehicle(pVehicle,TrooperInfoText[lines]);
				lines++;
			}
        }

		FOR_EACH_UNIT(pLegion, pUnit)
		{
			if( TIActiveOnly && (pUnit->mode < UNIT_STILL) )
				continue;
            dumpUnit(pUnit,TrooperInfoText[lines]);
            lines++;

            if( TITroopers && pUnit->mode > UNIT_IN_HQ )
            {
                FOR_EACH_TROOPER(pUnit, pTrooper, i)
                {
                    if( pTrooper )
                    {
                        sprintf(TrooperInfoText[lines], "     Trpr%d: ",i);

                        dumpTrooper(pTrooper,TrooperInfoText[lines]);
                    }
                    else
                    {
                        sprintf( TrooperInfoText[lines], "  ERROR: NULL Trooper!" );
                    }
                    lines++;
                }
            }
        }
    }
	return( lines );
}


void UpdateTrooperInfo( void )
{
	int lastline;

	switch( TrooperInfoMode )
	{
	case 0:
		TrooperInfoLines = UpdateTI_Legions();
		break;
	}

	if( TrooperInfoCurLine > TrooperInfoLines - NUM_DEBUG_LINES - TrooperInfoHeader )
		TrooperInfoCurLine = TrooperInfoLines - NUM_DEBUG_LINES - TrooperInfoHeader;
	if( TrooperInfoCurLine < 0 )
		TrooperInfoCurLine = 0;
	lastline = TrooperInfoCurLine + NUM_DEBUG_LINES - TrooperInfoHeader;
	if( lastline > TrooperInfoLines )
		lastline = TrooperInfoLines;

	DebugColor = YELLOW_IDX;
	strcpy( tempstringbuffer, "ARMY DATA - [LSHIFT-Z] Menu  " );
	if( TrooperInfoLines > NUM_DEBUG_LINES - TrooperInfoHeader )
	{
		strcat( tempstringbuffer, "[[]] Scroll" );
	}
	if( TIActiveOnly )
		strcat( tempstringbuffer, " [\\] All" );
	else
		strcat( tempstringbuffer, " [\\] Active" );
	if( TIArmies == 4 )
		strcat( tempstringbuffer, " [A] AllArmies" );
	if( TIArmies == 3 )
		strcat( tempstringbuffer, " [A] GrayOnly" );
	if( TIArmies == 2 )
		strcat( tempstringbuffer, " [A] BlueOnly" );
	if( TIArmies == 1 )
		strcat( tempstringbuffer, " [A] TanOnly" );
	if( TIArmies == 0 )
		strcat( tempstringbuffer, " [A] GreenOnly" );

	strcat( tempstringbuffer, " [BSPC] Troopers" );
	SetDebugLine( 0, tempstringbuffer );

	for( int i = TrooperInfoCurLine; i < lastline; i++ )
		SetDebugLine( i - TrooperInfoCurLine + TrooperInfoHeader, 
						TrooperInfoText[i] );
	if( i - TrooperInfoCurLine + TrooperInfoHeader < DebugLineNumber )
		DebugLineNumber = i - TrooperInfoCurLine + TrooperInfoHeader;
}


void DebugMode_MainMenu( void )
{
	ClearDebugInfo();
	CurrentDebugMode = EDM_MainMenu;
	DebugColor = YELLOW_IDX;

	MEMORYSTATUS memstatus;
	memstatus.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus( &memstatus );
	sprintf( tempstringbuffer, "Memory Status: %d available, %d total", memstatus.dwAvailPhys, memstatus.dwTotalPhys );
	AddDebugLine( tempstringbuffer );
	AddDebugLine( "DEBUG MODE MAIN MENU:  [ESCAPE] to Exit" );
	AddDebugLine( "" );
	AddDebugLine( "[A]      Animation Test" );
	AddDebugLine( "[D]      Debug Display" );
	AddDebugLine( "[G]      Game Functions" );
	AddDebugLine( "[L]      Debug Layers" );
	AddDebugLine( "[S]      Sarge Cheat" );
	sprintf( tempstringbuffer, "[T]      Toggle Legion/Unit Data (%s)", OnOffString[previousDM == EDM_TrooperInfo] );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[W]      Toggle World Object Counts (%s)", OnOffString[previousDM == EDM_WorldCounts] );
	AddDebugLine( tempstringbuffer );
	AddDebugLine( "[K]      Key Bindings" );
	AddDebugLine( "[M]      Mouse Control" );
	if (gpGame->GameType != GAMETYPE_ONEPLAYER ) AddDebugLine( "[C]      Communications" );
}


void DebugMode_Layers( void )
{
	ClearDebugInfo();
	CurrentDebugMode = EDM_Layers;
	DebugColor = YELLOW_IDX;
	AddDebugLine( "DEBUG LAYERS MENU:  [ESCAPE] to Exit" );
	AddDebugLine( "" );
	AddDebugLine( "[C]      Clear Layers" );
	AddDebugLine( "[B]      Bit Pads" );
	AddDebugLine( "[E]      Elevation Layer" );
	AddDebugLine( "[V]      Visibility Layer" );
	AddDebugLine( "[M]      Movement Layer" );
	AddDebugLine( "[N]      Number Pads" );
}

void DebugMode_Mouse( void )
{
	ClearDebugInfo();
	CurrentDebugMode = EDM_Mouse;
	DebugColor = YELLOW_IDX;
	AddDebugLine( "DEBUG MOUSE CONTROLS MENU:  [ESCAPE] to Exit" );
	AddDebugLine( "" );
	sprintf( tempstringbuffer, "[R]      Rotational Mouse (%s)", OnOffString[MouseDxRotate] );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[T]      Mouse Controls Vehicle Turret (%s)", OnOffString[MouseTurret] );
	AddDebugLine( tempstringbuffer );
}


extern char hotspots;	// controls hotspot green dot display
extern char routingDraw;
extern BOOL cheat_move;
extern char Allah;		// controls visibility


void DebugMode_Display( void )
{
	ClearDebugInfo();
	CurrentDebugMode = EDM_Display;
	DebugColor = YELLOW_IDX;
	AddDebugLine( "DEBUG DISPLAY MENU - [ESCAPE] to Exit" );
	AddDebugLine( "" );
	AddDebugLine( "[C]      Clear Debug Display" );
	sprintf( tempstringbuffer, "[A]      Flip Allah Mode (%s)", AllahModes[(Allah+1)%3] );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[G]      VehicleTrace (%s)",  OnOffString[vehicleBehavior]);
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[T]      EditTrafficaBILITY (%s)", OnOffString[shiftTrafficable]);
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[H]      Toggle Hotspots Display (%s)", OnOffString[hotspots] );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[R]      Toggle AI Router Draw (%s)", routingString[routingDraw] );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[L]      Toggle Labeling (%s)", OnOffString[labelForces] );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[B]      Toggle Big Cheat (%s)", OnOffString[bw1] );
	AddDebugLine( tempstringbuffer );
}


extern char sargeCane;
char *QuestString[] =
	{ "Unknown", "Blank", "Blue", "Red", "Green" };


void DebugMode_Cheat( void )
{
	SARGE *pSarge;
	ClearDebugInfo();
	CurrentDebugMode = EDM_Cheat;
	DebugColor = YELLOW_IDX;
	AddDebugLine( "DEBUG CHEAT MENU - [ESCAPE] to Exit" );
	AddDebugLine( "" );
	AddDebugLine( "[A]      Fill Air Support" );
	sprintf( tempstringbuffer, "[R]      Toggle Right-Click Explosion (%s)", OnOffString[explosions^1]);
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[E]      Change Right-Click Explosion Type (%d)", currbuttonexplosion );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[I]      Sarge Invunerable (%s)", OnOffString[sargeImmune] );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[C]      Sarge Cane (%s)", OnOffString[sargeCane] );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[U]      Foes Immobilized (%s)", OnOffString[immobileFoe] );
	AddDebugLine( tempstringbuffer );
	sprintf( tempstringbuffer, "[M]      Walk-Through Mode Toggle (%s)", OnOffString[cheat_move] );
	AddDebugLine( tempstringbuffer );
	if( NumHumanPlayers() == 1 )
	{
		pSarge = SargePointer( ARMY_PLAYER );
		sprintf( tempstringbuffer, "[Q]      Toggle Quest Item (%s)", 
			QuestString[ pSarge->questItem + 1 > 4 ? 0 : pSarge->questItem + 1 ] );
		AddDebugLine( tempstringbuffer );
	}
	AddDebugLine( "[J]      Deploy Jeep" );
	AddDebugLine( "[H]      Deploy Halftrack" );
	AddDebugLine( "[T]      Deploy Tank" );
	AddDebugLine( "[B]      Click vehicle drive" );
	AddDebugLine( "[O]      Teleport To Cursor" );
	AddDebugLine( "[F]      Max out Ammo" );
}


void DebugMode_Game( void )
{
	ClearDebugInfo();
	CurrentDebugMode = EDM_Game;
	DebugColor = YELLOW_IDX;
	AddDebugLine( "DEBUG GAME MENU - [ESCAPE] to Exit" );
	AddDebugLine( "" );
	AddDebugLine( "[L]      Lose Game" );
	AddDebugLine( "[M]      Music Toggle" );
	AddDebugLine( "[S]      Audio Kill" );
	AddDebugLine( "[W]      Win Game" );
	AddDebugLine( "[X]      Sound Effects Toggle" );
}


void DebugMode_Keys( void )
{
	ClearDebugInfo();
	CurrentDebugMode = EDM_Keys;
	DebugColor = YELLOW_IDX;
	AddDebugLine( "DEBUG KEYBOARD CONTROLS MENU - [ESCAPE] to Exit" );
	AddDebugLine( "" );
	sprintf( tempstringbuffer, "  %14s   %8s        %14s   %8s",
		"ACTION", "KEY", "COMMAND", "KEY" );
	AddDebugLine( tempstringbuffer );
}


int selectedcol = -1;
int selectedrow = -1;
BYTE selectedchar = 0;
void *selecteddispatcher = NULL;
TKeyDescriptors *selecteddiscriptor = NULL;


void DebugMode_Keys_Clear( void )
{
	selectedcol = -1;
	selectedrow = -1;
	selectedchar = -1;
	selecteddiscriptor = NULL;
}


// search through the key table provided and set the key
void DebugMode_Keys_Assign( TKeyBindingEntry *KeyTable, void *dispatcher, BYTE nKey, BYTE oKey )
{
	int i;

	i = 0;
	while( KeyTable[i].dispatcher != NULL )
	{
		if( (KeyTable[i].dispatcher == dispatcher) && (KeyTable[i].key == oKey) ) 
			KeyTable[i].key = nKey;
		i++;
	}
}


void DebugMode_KeysUpdate( void )
{
	int i, j, r;
	char buf1[80], buf2[14], buf3[54];

	DebugColor = YELLOW_IDX;
	SetDebugLine( 0, "DEBUG KEYBOARD CONTROLS MENU - [ESCAPE] to Exit" );
	SetDebugLine( 1, "" );

	i = j = 0;
	r = 2;
	while( TRUE )
	{
		if( GamePlayKeyDescs[i].dispatcher != NULL )
		{
			if( SargeKeyDescs[j].dispatcher != NULL )
			{
				sprintf( tempstringbuffer, "  %-14s   %-8s        %-14s   %-8s", 
					SargeKeyDescs[j].desc, KeysText[SargeKeyDescs[j].CustomKey],
					GamePlayKeyDescs[i].desc, KeysText[GamePlayKeyDescs[i].CustomKey] );
				i++;
				j++;
			}
			else
			{
				sprintf( tempstringbuffer, "  %-14s   %-8s        %-14s   %-8s", "", "",
					GamePlayKeyDescs[i].desc, KeysText[GamePlayKeyDescs[i].CustomKey] );
				i++;
			}
		}
		else
		if( SargeKeyDescs[j].dispatcher != NULL )
		{
			sprintf( tempstringbuffer, "  %-14s   %-8s        %-14s   %-8s", 
				SargeKeyDescs[j].desc, KeysText[SargeKeyDescs[j].CustomKey], "", "" );
			j++;
		}
		else
			break;
		SetDebugLine( r, tempstringbuffer );
		r++;
	}
	// go back and "fix" the cursor
	if( selectedrow >= 0 )
	{
		if( selectedrow > DebugLineNumber - 2 )
			goto badselection;
		strcpy( tempstringbuffer, DebugLines[selectedrow+2] );
		if( selectedcol == 0 )
		{
			if( j <= selectedrow )
				goto badselection;

			strncpy( buf1, tempstringbuffer, 19 );
			buf1[19] = 0;
			strncpy( buf2, tempstringbuffer + 19, 8 );
			buf2[8] = 0;
			strncpy( buf3, tempstringbuffer + 27, 33 );
			buf3[33] = 0;
			sprintf( tempstringbuffer, "%s%c%s%c%s", buf1, 9, buf2, 11, buf3 );
			SetDebugLine( selectedrow + 2, tempstringbuffer );
		}
		else
		if( selectedcol == 1 )
		{
			if( i <= selectedrow )
				goto badselection;
			strncpy( buf1, tempstringbuffer, 51 );
			buf1[51] = 0;
			strncpy( buf2, tempstringbuffer + 51, 8 );
			buf2[8] = 0;
			sprintf( tempstringbuffer, "%s%c%s%c", buf1, 9, buf2, 11 );
			SetDebugLine( selectedrow + 2, tempstringbuffer );
		}
		else
		{
badselection:
			DebugMode_Keys_Clear();
		}
	}
}


void MakeKeyAssignment( BYTE nChar, BYTE oKey )
{
	switch( selectedcol )
	{
	case 0:
		DebugMode_Keys_Assign( SargeKeys, selecteddiscriptor->dispatcher, nChar, oKey );
		break;
	case 1:
		DebugMode_Keys_Assign( GamePlayKeys, selecteddiscriptor->dispatcher, nChar, oKey );
		break;
	}
}

void Kbd_Debug_WorldCounts( BYTE nChar, UINT nFlags )
{
	ASSERT( previousUI );

	ClearDebugInfo();
	if( previousDM == EDM_WorldCounts )
	{
		previousDM = EDM_DebugModeOff;		
		Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
	}
	else
	{
		CurrentDebugMode = EDM_WorldCounts;
		pKeyTable = WorldCountsKeyTable;
		DebugColor = YELLOW_IDX;
		AddDebugLine( "WORLD OBJECTS DATA - [LSHIFT-Z] to access Main Menu" );
	}
}


void Kbd_Debug_TrooperInfo( BYTE nChar, UINT nFlags )
{
	ASSERT( previousUI );
	
	ClearDebugInfo();
	if( previousDM == EDM_TrooperInfo )
	{
		previousDM = EDM_DebugModeOff;
		Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
	}
	else
	{
		DebugColor = YELLOW_IDX;
		CurrentDebugMode = EDM_TrooperInfo;
		AddDebugLine( "DEBUG TROOPER INFO - [LSHIFT-Z] Menu" );
		pKeyTable = TrooperInfoKeyTable;
	}
}


void Kbd_Debug_TIScrollUp( BYTE nChar, UINT nFlags )
{
	if( TrooperInfoCurLine <= 0 )
		return;
	TrooperInfoCurLine--;
}


void Kbd_Debug_TIScrollDn( BYTE nChar, UINT nFlags )
{
	if( TrooperInfoCurLine >= TrooperInfoLines - NUM_DEBUG_LINES )
		return;
	TrooperInfoCurLine++;
}


void Kbd_Debug_TIActiveToggle( BYTE nChar, UINT nFlags )
{
	TIActiveOnly = !TIActiveOnly;
}

void Kbd_Debug_TIArmyToggle( BYTE nChar, UINT nFlags )
{
	++TIArmies;
    if (TIArmies == 5) TIArmies = 0;
}

void Kbd_Debug_TITrooperToggle( BYTE nChar, UINT nFlags )
{
	TITroopers = !TITroopers;
}


void Kbd_Debug_Mouse( BYTE nChar, UINT nFlags )
{
    if( nChar == DIK_ESCAPE )
	{
		pKeyTable = previousUI;
		previousUI = NULL;
		CurrentDebugMode = previousDM;
 	}
    else	
	{
		pKeyTable = DMMouseKeyTable;
		DebugMode_Mouse();
	}
}


void Kbd_Debug_Keys( BYTE nChar, UINT nFlags )
{
    if( nChar == DIK_ESCAPE )
	{
		pKeyTable = previousUI;
		previousUI = NULL;
		CurrentDebugMode = previousDM;
	}
    else	
	{
		pKeyTable = DMKeysKeyTable;
		DebugMode_Keys();
	}
}


void Kbd_Debug_ChangeMode( BYTE nChar, UINT nFlags )
{
    if( previousUI )
	{
		switch(nChar)	
		{
			case DIK_ESCAPE:
				pKeyTable = previousUI;
				previousUI = NULL;
				CurrentDebugMode = EDM_DebugModeOff;
				ClearDebugInfo();
				return;
			default:
				pKeyTable = DModeKeyTable;
				DebugMode_MainMenu();
				return;
		}
	}
    else	
	{
		previousUI = pKeyTable;
		previousDM = CurrentDebugMode;
		pKeyTable = DModeKeyTable;
		DebugMode_MainMenu();
	}
}


void Kbd_Debug_ClearLayers( BYTE nChar, UINT nFlags )
{
	previousDM = EDM_DebugModeOff;
	pMainFrame->OnAvenue();
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_Layers( BYTE nChar, UINT nFlags )
{
    if( nChar == DIK_ESCAPE )
	{
		pKeyTable = previousUI;
		previousUI = NULL;
		CurrentDebugMode = previousDM;
	}
    else	
	{
		pKeyTable = DMLayerKeyTable;
		DebugMode_Layers();
	}
}


void Kbd_Debug_LayerBitPads( BYTE nChar, UINT nFlags )
{
	pMainFrame->OnBitpads();
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_LayerMovement( BYTE nChar, UINT nFlags )
{
	pMainFrame->OnTemporary();
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}

void Kbd_Debug_LayerVis( BYTE nChar, UINT nFlags )
{
	pMainFrame->OnBw02();
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_LayerElevation( BYTE nChar, UINT nFlags )
{
    SetAIMapDisplay(ELEVATION_MAP);
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_LayerNumPads( BYTE nChar, UINT nFlags )
{
	pMainFrame->OnPads();
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_Display( BYTE nChar, UINT nFlags )
{
    if( nChar == DIK_ESCAPE )
	{
		pKeyTable = previousUI;
		previousUI = NULL;
		CurrentDebugMode = previousDM;
	}
    else	
	{
		pKeyTable = DMDisplayKeyTable;
		DebugMode_Display();
	}
}


void Kbd_Debug_FlipHotspots( BYTE nChar, UINT nFlags )
{
    hotspots = !hotspots;
	the_map.redraw = REDRAW_FULL;
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_ClearDisplay( BYTE nChar, UINT nFlags )
{
	hotspots = FALSE;
	routingDraw = FALSE;
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_RouteDraw( BYTE nChar, UINT nFlags )
{
    ++routingDraw;
    if (routingDraw == 3) routingDraw = 0;
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}

void Kbd_Debug_LabelDraw( BYTE nChar, UINT nFlags )
{
    ++labelForces;
    if (labelForces == 3) labelForces = 0;
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_VehicleTrace( BYTE nChar, UINT nFlags )
{
    vehicleBehavior = !vehicleBehavior;
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_Cheat( BYTE nChar, UINT nFlags )
{
    if( nChar == DIK_ESCAPE )
	{
		pKeyTable = previousUI;
		previousUI = NULL;
		CurrentDebugMode = previousDM;
	}
    else	
	{
		pKeyTable = DMCheatKeyTable;
		DebugMode_Cheat();
	}
}


void Kbd_Debug_MouseRotate( BYTE nChar, UINT nFlags )
{	
	MouseDxRotate = (MouseDxRotate == 0 ? 1 : 0);
	sprintf( tempstringbuffer, "[R]      Rotational Mouse (%s)", OnOffString[MouseDxRotate] );
	SetDebugLine( 2, tempstringbuffer );
}


void Kbd_Debug_MouseTurret( BYTE nChar, UINT nFlags )
{	
	MouseTurret = (MouseTurret == 0 ? 1 : 0);
	sprintf( tempstringbuffer, "[T]      Mouse Controls Vehicle Turret (%s)", OnOffString[MouseTurret] );
	SetDebugLine( 3, tempstringbuffer );
}


void Kbd_Debug_Travel( BYTE nChar, UINT nFlags )
{
	cheat_move = !cheat_move;	
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}

void Kbd_Debug_SargeCane( BYTE nChar, UINT nFlags )
{
    sargeCane = !sargeCane;
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}

void Kbd_Debug_SargeQuestItem( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	pSarge->questItem++;
	if( pSarge->questItem > 4 )
		pSarge->questItem = 0;
	sprintf( tempstringbuffer, "[Q]      Toggle Quest Item (%s)", 
		QuestString[ pSarge->questItem + 1 > 4 ? 0 : pSarge->questItem + 1 ] );
	SetDebugLine( 6, tempstringbuffer );
}


void Kbd_Debug_DeployJeep( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge;
	pSarge = SargePointer(ARMY_PLAYER);
	VehicleDeployType( ARMY_PLAYER, ARMY_JEEP, &pSarge->common.position, pSarge->common.facing );
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_DeployHalftrack( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge;
	pSarge = SargePointer(ARMY_PLAYER);
	VehicleDeployType( ARMY_PLAYER, ARMY_HALFTRACK, &pSarge->common.position, pSarge->common.facing );
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_DeployTank( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge;
	pSarge = SargePointer(ARMY_PLAYER);
	VehicleDeployType( ARMY_PLAYER, ARMY_TANK, &pSarge->common.position, pSarge->common.facing );
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_Game( BYTE nChar, UINT nFlags )
{
    if( nChar == DIK_ESCAPE )
	{
		pKeyTable = previousUI;
		previousUI = NULL;
		CurrentDebugMode = previousDM;
	}
    else	
	{
		pKeyTable = DMGameKeyTable;
		DebugMode_Game();
	}
}


void Kbd_Debug_AudioKill( BYTE nChar, UINT nFlags )
{
	audioStopAll();
}


void Kbd_Debug_MusicToggle( BYTE nChar, UINT nFlags ) 
{
	pMainFrame->OnMusicToggle();
}


void Kbd_Debug_SoundToggle( BYTE nChar, UINT nFlags )
{
	pMainFrame->OnSfxToggle();
}


void Kbd_Debug_LoseGame( BYTE nChar, UINT nFlags )
{
	if ( gpGame->GetSubState() == PLAY_SUB_STATE )
	{
		Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
		MissionDone(ARMY_PLAYER_2);
	}
}


void Kbd_Debug_WinGame( BYTE nChar, UINT nFlags )
{
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
	MissionDone(ARMY_PLAYER);
}

void ShowDebugInfo( void )
{
	if( CurrentDebugMode == EDM_DebugModeOff )
		return;
	if( DebugLineNumber < 1 )
		return;
	switch( CurrentDebugMode )
	{
	case EDM_WorldCounts:
		UpdateWorldCounts();
		break;
	case EDM_TrooperInfo:
		UpdateTrooperInfo();
		break;
	case EDM_Keys:
		DebugMode_KeysUpdate();
		break;
	case EDM_Comm:
		DebugCommText();
		break;
	}
	if( !LockOverlayLayer() )
		return;
	for( int i = 0; i < DebugLineNumber; i++ )
	{
		SIZE sz;

		sz.cx = 620;
		sz.cy = 22;
		BmpTextWriteLocked( 10, i * DEBUG_LINE_HEIGHT + 22, DebugLines[i], BMPFONT_MAP, &sz, DebugColor );
	}
	UnlockOverlayLayer();
}


/*
	Avatar animation test code
*/

AVATAR	*pAvatar = NULL;
int		avatar_facing = DIRECTION_UP;
ACTION	avatar_action = AVATAR_STAND;

TROOPER	test_trooper;
BOOL	single_step = FALSE;
BOOL	next_step = TRUE;

void troop_start( int trooper_type );
void troop_end( void );


void Kbd_Debug_AnimTest( BYTE nChar, UINT nFlags )
{
	int		trooper_type = ARMY_RIFLE_MEN;

	if( CurrentDebugMode == EDM_AnimTest )
	{
		switch( nChar )
		{
		case DIK_ESCAPE:
			troop_end();
			pKeyTable = previousUI;
			previousUI = NULL;
			CurrentDebugMode = previousDM;
			return;
		case DIK_1:
			trooper_type = ARMY_RIFLE_MEN;
			break;
		case DIK_2:
			trooper_type = ARMY_FLAME_MEN;
			break;
		case DIK_3:
			trooper_type = ARMY_BAZOOKA_MEN;
			break;
		case DIK_4:
			trooper_type = ARMY_MORTAR_MEN;
			break;
		case DIK_5:
			trooper_type = ARMY_MINER_MEN;
			break;
		}
    	AvatarSetType(pAvatar, trooper_type);
	}
    else
	{
		pKeyTable = DMTestKeyTable;
		ClearDebugInfo();
		CurrentDebugMode = EDM_AnimTest;
		DebugColor = YELLOW_IDX;
		AddDebugLine( "ANIM TEST MENU - [ESCAPE] to exit   [H] for help" );
		AddDebugLine( "" );
 		troop_start(ARMY_RIFLE_MEN);
	}
}


void Kbd_Debug_AnimTestHelp( BYTE nChar, UINT nFlags )
{
	if( DebugLineNumber > 3 )
	{
		ClearDebugInfo();
		AddDebugLine( "ANIM TEST MENU - [ESCAPE] to Exit   [H] for Help" );
	}
	else
	{
		ClearDebugInfo();
		AddDebugLine( "ANIM TEST MENU - [ESCAPE] to Exit   [H] for Help" );
		AddDebugLine( "1-5      - Rifleman, Flamer, Bazooka, Mortar, Minesweeper" );
		AddDebugLine( "W        - Walk" );
		AddDebugLine( "R        - Run" );
		AddDebugLine( "U        - Shuffle" );
		AddDebugLine( "F        - Fire" );
		AddDebugLine( "G        - Raise" );
		AddDebugLine( "T        - Throw" );
		AddDebugLine( "X        - Stationary" );
		AddDebugLine( "I        - Invisible" );
		AddDebugLine( "K        - Kneel" );
		AddDebugLine( "P        - Prone" );
		AddDebugLine( "S        - Standup" );
		AddDebugLine( "D        - Dive" );
		AddDebugLine( "LEFT     - Left" );
		AddDebugLine( "RIGHT    - Right" );
		AddDebugLine( "DOWN     - Down" );
		AddDebugLine( "UP       - Up" );
		AddDebugLine( "SPACE    - Center" );
		AddDebugLine( "F1       - Single Step" );
		AddDebugLine( "PGDN     - Next Step" );
		AddDebugLine( "H        - Hide Help" );
	}
}


void test_troop_update( void )	
{
	TROOPER* pTrooper = &test_trooper;

	if (pAvatar)	{
		WeaponFireUpdate(pTrooper->common.pWeapon);

		if (single_step)
			if (!next_step)
				return;
		next_step = FALSE;

		AvatarPerform(avatar_action, avatar_action, avatar_facing, TRUE, pAvatar);
		ItemSetLocation(pTrooper,&pAvatar->pAnimation->world_pos);
		pTrooper->common.facing = AVATAR_FACING(TROOPER_AVATAR(pTrooper));
		if (AvatarLastCompleted(avatar_action, pAvatar))
			BOOL b=TRUE;
	}
}


void Kbd_Debug_troop_center(BYTE nChar, UINT nFlags) 
{
	TROOPER* pTrooper = &test_trooper;

	SPOINT point = SargePosition(ARMY_PLAYER);
	point.y += 64;	// add 64 to y pos
	AvatarSetPosition(point, pAvatar);
    ItemSetLocation(pTrooper,&point);
	TRACE("Setting Avatar Location to %d,%d\n", point.x, point.y);
}


void troop_start(int trooper_type) 
{
	if (!pAvatar)	{
		TROOPER* pTrooper = &test_trooper;

		TrooperTestCreate(ARMY_PLAYER, pTrooper, (TROOPER_TYPE) trooper_type);

		pAvatar = AvatarCreate(ITEM_UID(pTrooper));
		pTrooper->pAvatar = pAvatar;
		TRACE("Creating Avatar\n");

		AnimSetOwner(pAvatar->pAnimation, pTrooper);
		pTrooper->common.pVictim = NULL;

		Kbd_Debug_troop_center(0,0);
		
		ItemUpdateSeen((ITEM*)pTrooper,(ITEM*)pTrooper);

		pTrooper->mode = TROOPER_ALIVE;
		avatar_action = AVATAR_STAND;
	}
}


void troop_end() 
{
	if (pAvatar)	{
		AvatarDestroy(pAvatar);
		pAvatar = NULL;
		TRACE("Destroying Avatar\n");
	}
}


void Kbd_Debug_troop_single_step(BYTE nChar, UINT nFlags) 
{
	single_step ^= TRUE;
	next_step = TRUE;
}


void Kbd_Debug_troop_next_step(BYTE nChar, UINT nFlags) 
{
	next_step = TRUE;
}


void Kbd_Debug_troop_walk(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_WALK;
}


void Kbd_Debug_troop_run(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_RUN;
}


void Kbd_Debug_troop_shuffle(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_SHUFFLE;
}


void Kbd_Debug_troop_fire(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_FIRE;
}


void Kbd_Debug_troop_raise(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_READY_FIRE;
}


void Kbd_Debug_troop_throw(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_FIRE;
//	avatar_action = AVATAR_THROW;
}


void Kbd_Debug_troop_stationary(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_STAND;
}


void Kbd_Debug_troop_dive(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_DIVE;
}


void Kbd_Debug_troop_kneel(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_KNEEL;
}


void Kbd_Debug_troop_prone(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_PRONE;
}


void Kbd_Debug_troop_standup(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_STAND;
}


void Kbd_Debug_troop_invisible(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_INVISIBLE;
	TRACE("Avatar Invisible\n");
}


void Kbd_Debug_troop_TurnLeft(BYTE nChar, UINT nFlags) 
{
	avatar_facing += 16;
	if (avatar_facing >= 256)
		avatar_facing -= 256;
}


void Kbd_Debug_troop_TurnRight(BYTE nChar, UINT nFlags) 
{
	avatar_facing -= 16;
	if (avatar_facing < 0)
		avatar_facing += 256;
}


void Kbd_Debug_troop_up(BYTE nChar, UINT nFlags) 
{
	avatar_facing = DIRECTION_UP;
}


void Kbd_Debug_troop_down(BYTE nChar, UINT nFlags) 
{
	avatar_facing = DIRECTION_DOWN;
}


void Kbd_Debug_troop_stop(BYTE nChar, UINT nFlags) 
{
	avatar_action = AVATAR_STOP_IMMEDIATELY;
}


void Kbd_Debug_Comm ( BYTE nChar, UINT nFlags )
{
    if (gpGame->GameType == GAMETYPE_ONEPLAYER ) return;
	if( nChar == DIK_ESCAPE )
	{
		pKeyTable = previousUI;
		previousUI = NULL;
		CurrentDebugMode = previousDM;
	}
    else	
	{
		pKeyTable = DMCommKeyTable;
		DebugMode_Comm();
	}
}




//  COMM Debug Stuff

extern TDGLIST freelist;
extern TDGLIST sendqueue;
extern TDGLIST latencyqueue;
extern TDGLIST inuselist;

void DebugCommText (void ) 
{
	int srate;
	int loss;
	int i, pktsto,pktsfrom;
	int totalmsgs=0;
	DWORD aveLatency;
	LPFLOWQ myflow,lpflow;
	myflow = FindFlowQ(gpComm->m_DPId);
	if (myflow) loss = myflow->packetLoss; else loss = 0;
	ClearDebugInfo();
	AddDebugLine( "DEBUG COMM MENU:  [ESCAPE] to Exit" );
	AddDebugLine( "" );
	srate = 1000/(gpComm->MINSENDINTERVAL ? gpComm->MINSENDINTERVAL: 1000);
	sprintf(tempstringbuffer," Send Rate = %d pps, Loss=%d%% Free List = %d,    SendList = %6d   Sending %6d  bps  Receiving %d bps ",
		srate, loss, ListSize(&freelist),ListSize(&sendqueue),gpComm->GetSendBW(),gpComm->GetReceiveBW() );
	AddDebugLine( tempstringbuffer);
	sprintf(tempstringbuffer," Added Latency (each way) is %d  milliseconds ", myflow->meanLatency);
	AddDebugLine( tempstringbuffer);
	sprintf(tempstringbuffer,"Player  Ave Latency   Packet Loss To  Packet Loss From ");
	AddDebugLine( tempstringbuffer);
	for (i=1;i<4;i++) {
		if( (gpComm->m_PlayerId[i] == 0) || (gpComm->m_PlayerId[i] == 0xffffffff)) continue;
		lpflow = FindFlowQ(gpComm->m_PlayerId[i]);
		if (!lpflow ) continue;
		aveLatency = AveLatency(lpflow);
		pktsto = lpflow->packetsto ? lpflow->packetsto : 1;
		pktsfrom = lpflow->packetsfrom ? lpflow->packetsfrom : 1;
		sprintf(tempstringbuffer," %6s    %6d          %4d%%               %4d%%",
			gpComm->GetColorStr(gpComm->m_PlayerId[i]), aveLatency, (lpflow->numResends*100)/pktsto,(lpflow->numNacks*100)/pktsfrom);
		totalmsgs += ListSize(&lpflow->pendingqueue);
	}
	
	AddDebugLine( tempstringbuffer);
	sprintf(tempstringbuffer,"%3d Msgs  Free = %3d SendQueue =%3d  Latency =%3d Pending = %3d",
		totalmsgs+ListSize(&freelist)+ListSize(&sendqueue)+ListSize(&latencyqueue)+ListSize(&inuselist) ,
		ListSize(&freelist),ListSize(&sendqueue),ListSize(&latencyqueue),ListSize(&inuselist) );
	AddDebugLine( tempstringbuffer);
	AddDebugLine( "" );
	AddDebugLine( "[D]      Toggle Comm Display" );
	AddDebugLine( "[F]      Faster Send Rate" );
	AddDebugLine( "[S]      Slower Send Display" );
	AddDebugLine( "[Z]      Less Packet Loss" );
	AddDebugLine( "[X]      More Packet Loss" );
	sprintf(tempstringbuffer,"[B]      Toggle Burst Mode Packet Loss (Currently %s) ",
		(myflow && (myflow->burstPacketLoss )) ? "On" : "Off");
	AddDebugLine(tempstringbuffer );
	AddDebugLine( "[Q]      Less Added Latency (Quicker)" );
	AddDebugLine( "[W]      More Added Latency (Wait More)" );
	sprintf(tempstringbuffer,"[T]      Toggle TimeOuts Enabled (Currently %s) ",
		gpComm->m_bTimeOutsEnabled ? "Enabled":"Disabled");
	AddDebugLine(tempstringbuffer );
	sprintf(tempstringbuffer,"[G]      Toggle Guaranteed Send (Currently %s) ",
		(gpComm->m_SendFlags & DPSEND_GUARANTEED) ? "On" : "Off");
	if (gpComm->m_bHost /* && ( gpComm->m_Caps.dwFlags & DPCAPS_GUARANTEEDSUPPORTED) */ ) 
		AddDebugLine(tempstringbuffer );
}

void DebugMode_Comm( void )
{
	CurrentDebugMode = EDM_Comm;
	DebugColor = YELLOW_IDX;
	DebugCommText();

}



void Kbd_Debug_CommGSend( BYTE nChar, UINT nFlags )
{
	FLAGSMSG msg;
	LPFLOWQ myflow;
	myflow = FindFlowQ(gpComm->m_DPId);
	if (!myflow) return;
	previousDM = EDM_DebugModeOff;
	if (gpComm->m_bHost /* && ( gpComm->m_Caps.dwFlags & DPCAPS_GUARANTEEDSUPPORTED) */ ){
		gpComm->m_SendFlags ^= DPSEND_GUARANTEED;
		msg.tdg.tdg_Type = MSG_SET_FLAGS;
		msg.tdg.tdg_Size = sizeof(FLAGSMSG);
		msg.flags = gpComm->m_SendFlags;
		msg.meanLatency = myflow->meanLatency;
		msg.deviationLatency = myflow->deviationLatency;
		SendGameMessage( (LPGENERICMSG) &msg,DPID_ALLPLAYERS, DPSEND_GUARANTEED);
	}


	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}

void Kbd_Debug_CommDisplay( BYTE nChar, UINT nFlags ) 
{
	previousDM = EDM_DebugModeOff;
//	gpComm->debugComm = !gpComm->debugComm;
	gpComm->debugDisplayComm++;
	if (gpComm->debugDisplayComm > 2) gpComm->debugDisplayComm=0;
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}

void Kbd_Debug_CommTimeOut( BYTE nChar, UINT nFlags ) 
{
	previousDM = EDM_DebugModeOff;
	gpComm->m_bTimeOutsEnabled = !gpComm->m_bTimeOutsEnabled;
	Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}

void Kbd_Debug_CommFaster( BYTE nChar, UINT nFlags ) 
{
	int newinterval;
	newinterval = gpComm->MINSENDINTERVAL-10;
	if(newinterval < 33) newinterval = 33;
	gpComm->MINSENDINTERVAL = newinterval;
	// previousDM = EDM_DebugModeOff;
	// Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}

void Kbd_Debug_CommBMode( BYTE nChar, UINT nFlags ) 
{
	LPFLOWQ myflow;
	myflow = FindFlowQ(gpComm->m_DPId);
	if (!myflow) return;
	myflow->burstPacketLoss = ! myflow->burstPacketLoss;
}

void Kbd_Debug_CommMoreLatency( BYTE nChar, UINT nFlags ) 
{
	FLAGSMSG msg;
	int newlatency;
	LPFLOWQ myflow;
	myflow = FindFlowQ(gpComm->m_DPId);
	if (!myflow) return;
	newlatency = myflow->meanLatency+50;
	if(newlatency > 1000) newlatency = 1000;
	myflow->meanLatency = newlatency;
	if (gpComm->m_bHost ){
		msg.tdg.tdg_Type = MSG_SET_FLAGS;
		msg.tdg.tdg_Size = sizeof(FLAGSMSG);
		msg.flags = gpComm->m_SendFlags;
		msg.meanLatency = myflow->meanLatency;
		msg.deviationLatency = myflow->deviationLatency;
		SendGameMessage( (LPGENERICMSG) &msg,DPID_ALLPLAYERS, DPSEND_GUARANTEED);
	}
}

void Kbd_Debug_CommLessLatency( BYTE nChar, UINT nFlags ) 
{
	FLAGSMSG msg;
	int newlatency;
	LPFLOWQ myflow;
	myflow = FindFlowQ(gpComm->m_DPId);
	if (!myflow) return;
	newlatency = myflow->meanLatency;
	if(myflow->meanLatency >= 50) newlatency = myflow->meanLatency-50;
	else newlatency = 0;
	myflow->meanLatency = newlatency;
	if (gpComm->m_bHost ){
		msg.tdg.tdg_Type = MSG_SET_FLAGS;
		msg.tdg.tdg_Size = sizeof(FLAGSMSG);
		msg.flags = gpComm->m_SendFlags;
		msg.meanLatency = myflow->meanLatency;
		msg.deviationLatency = myflow->deviationLatency;
		SendGameMessage( (LPGENERICMSG) &msg,DPID_ALLPLAYERS, DPSEND_GUARANTEED);
	}
}

void Kbd_Debug_CommSlower( BYTE nChar, UINT nFlags ) 
{
	int newinterval;
	newinterval = gpComm->MINSENDINTERVAL+10;
	if(newinterval > 1000) newinterval = 1000;
	gpComm->MINSENDINTERVAL = newinterval;
	// previousDM = EDM_DebugModeOff;
	// Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_Debug_CommLessLoss( BYTE nChar, UINT nFlags ) 
{
	int newloss;
	LPFLOWQ myflow;
	myflow = FindFlowQ(gpComm->m_DPId);
	if (!myflow) return;
	newloss = myflow->packetLoss-1;
	if(newloss < 0) newloss = 0;
	myflow->packetLoss = newloss;
	// previousDM = EDM_DebugModeOff;
	// Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}
void Kbd_Debug_CommMoreLoss( BYTE nChar, UINT nFlags ) 
{
	int newloss;
	LPFLOWQ myflow;
	myflow = FindFlowQ(gpComm->m_DPId);
	if (!myflow) return;
	newloss = myflow->packetLoss+1;
	if(newloss > 10) newloss = 10;
	myflow->packetLoss = newloss;
	// previousDM = EDM_DebugModeOff;
	// Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
}


void Kbd_ChangeTrafficability( BYTE nChar, UINT nFlags )
{
    shiftTrafficable = (shiftTrafficable) ? 0 : 1;
	if( CurrentDebugMode == EDM_Display )
	{
        sprintf( tempstringbuffer, "[T]      EditTrafficaBILITY (%s)", OnOffString[shiftTrafficable]);
		SetDebugLine( 4, tempstringbuffer );
	}

}
#endif


void Kbd_Debug_LoseGameDirect( BYTE nChar, UINT nFlags )
{
	MissionDone(ARMY_PLAYER_2);
}


void Kbd_Debug_WinGameDirect( BYTE nChar, UINT nFlags )
{
	if ( gpGame->GetSubState() == PLAY_SUB_STATE )
		MissionDone(ARMY_PLAYER);
}

void Kbd_Debug_FlipAllah( BYTE nChar, UINT nFlags )
{
    Allah += 1;
    if (Allah == 3) Allah = 0; // cycle
	if( CurrentDebugMode == EDM_Display )
	{
		sprintf( tempstringbuffer, "[A]      Flip Allah Mode (%s)", AllahModes[(Allah+1)%3] );
#ifndef FINAL
		SetDebugLine( 3, tempstringbuffer );
#endif
	}
    if (Allah == 1) MakeObjectsVisible();

#ifndef FINAL
	if( !ScrnOptionsVisible() )
		Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
#endif
}

void Kbd_Debug_Explosions( BYTE nChar, UINT nFlags )
{
	ChangeRButtonAction();
#ifndef FINAL
	sprintf( tempstringbuffer, "[E]      Change Right-Click Explosion Type (%d)", currbuttonexplosion );
	SetDebugLine( 4, tempstringbuffer );
#endif
}

void Kbd_Debug_AddAirstrikes( BYTE nChar, UINT nFlags )
{
	fillAirSupport();
#ifndef FINAL
	if( !ScrnOptionsVisible() )
		Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
#endif
}


void Kbd_Debug_SargeInvulnerable( BYTE nChar, UINT nFlags )
{
    sargeImmune = !sargeImmune;
#ifndef FINAL
	if( !ScrnOptionsVisible() )
		Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
#endif
}

void Kbd_Debug_FoeImmobile( BYTE nChar, UINT nFlags )
{
    immobileFoe = !immobileFoe;
#ifndef FINAL
	if( !ScrnOptionsVisible() )
		Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
#endif
}

void Kbd_Debug_Explosions_Toggle( BYTE nChar, UINT nFlags )
{
	explosions = (explosions ? 0 : 1);
#ifndef FINAL
	sprintf( tempstringbuffer, "[R]      Toggle Right-Click Explosion (%s)", OnOffString[explosions^1]);
	SetDebugLine( 3, tempstringbuffer );
#endif
}

void Kbd_Debug_Explosions_Cheat( BYTE nChar, UINT nFlags )
{
    currbuttonexplosion = 5;  // one big explosion
	explosions = !explosions;
}


void Kbd_Debug_Teleport( BYTE nChar, UINT nFlags )
{
    SPOINT x;
    x.x = (short)CursorPos.x;
    x.y = (short)CursorPos.y;
    ScreenToWorld(&x);
    if (UntrafficableUnit(ENCODE_IPOINT(x.x,x.y))) return;
    
	SARGE *pSarge;
	pSarge = SargePointer(ARMY_PLAYER);
	SargeTeleport(pSarge, x.x, x.y );
#ifndef FINAL
	if( !ScrnOptionsVisible() )
		Kbd_Debug_ChangeMode( DIK_ESCAPE, 0 );
#endif
}

void Kbd_Debug_MaxAmmo( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge;
	pSarge = SargePointer(ARMY_PLAYER);
	if( pSarge->pWeaponList[SARGE_WEAPON_SECONDARY] )
	{
		pSarge->pWeaponList[SARGE_WEAPON_SECONDARY]->nAmmo = -1;
		pSarge->pWeaponList[SARGE_WEAPON_SECONDARY]->nMaxAmmo = -1;
	}
}


void Kbd_Debug_BigCheat( BYTE nChar, UINT nFlags )
{
	SARGE *pSarge = SargePointer( ARMY_PLAYER );
    bw1 = !bw1;
    sargeImmune = !sargeImmune;
    labelForces = (bw1) ? 1 : 0;
    Allah = (bw1) ? 1 : 0;
    currbuttonexplosion = 5;    // be right exploder single guy
	explosions = !explosions;
	if (Allah == 1) MakeObjectsVisible();
#ifndef FINAL
    scriptDebug = !scriptDebug;
    vehicleBehavior = !vehicleBehavior;
#endif
}


static void MakeObjectsVisible()
{
    int j;
    for (j = 0; j < the_map.num_objects; ++j)
    {
        OBJECT* pObject;
        pObject = &the_map.objects[j];
        // make them thisible.
        if (pObject->cell.flags & ANIM_FLAG_INVISIBLE)
            pObject->cell.flags ^= ANIM_FLAG_INVISIBLE;
    }
}
