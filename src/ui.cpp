/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: ui.cpp $
//
//	DESCRIPTION:	Code for handling the user interface
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Tuesday, June 24, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ui.cpp 392   4/18/98 1:26p Nrobinso $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////
 
/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/ui.cpp $
//  
//  392   4/18/98 1:26p Nrobinso
//  if in setup mode, don't allow switching into sarge control mode
//  
//  391   4/17/98 11:19a Bwilcox
//  scrolling click on paper map takes you there
//  
//  390   4/16/98 4:54p Nrobinso
//  defensive programming to prevent sarge from being controlled during
//  game setup
//  
//  389   4/14/98 4:01a Aburgess
//  GADGET processing forces a return rather than continuing to process
//  changed gadgets
//  
//  388   4/14/98 12:19p Phu
//  viewing distance modifications for vehicles
//  
//  387   4/13/98 3:57p Nrobinso
//  fix doing a start in the middle of chat
//  
//  386   4/13/98 1:38p Nrobinso
//  start audio once briefing is drawn
//  
//  385   4/13/98 12:40p Nrobinso
//  properly clear aborted message
//  
//  384   4/12/98 11:20p Nrobinso
//  don't restart music on exit from F11, F12 and script bmp's
//  
//  383   4/12/98 1:29p Bwilcox
//  allow alex to exist in final build
//  
//  382   4/10/98 11:47a Nrobinso
//  try to fix strat button leading to alliance button being depressed
//  
//  381   4/09/98 10:19a Nrobinso
//  remove unused
//  
//  380   4/08/98 12:17p Nrobinso
//  map has a different keyboard routine
//  
//  379   4/06/98 2:03p Nrobinso
//  have releaserecall return a boolean to tell if it was really released
//  
//  378   4/06/98 12:00p Nrobinso
//  keyboard placing of items in setup
//  
//  377   4/05/98 6:04p Bwilcox
//  dtos drawn on view map
//  
//  375   4/02/98 6:29p Phu
//  typecast to avoid warnings
//  
//  374   4/01/98 4:07p Nrobinso
//  no v/o for mp mission briefing
//  
//  373   4/01/98 3:21p Nrobinso
//  new v/o's
//  
//  372   4/01/98 12:06p Bwilcox
//  cant deploy forces close to the edge
//  
//  371   4/01/98 10:06a Aburgess
//  fix bug where message data is written over
//  
//  370   3/30/98 2:27p Nrobinso
//  set up to replace no air support v/o
//  
//  369   3/29/98 5:40p Dmaynard
//  Total Hack (I think) to get it so that you can see where you are
//  driving.
//  There should be more screen visible in front of you than behind you
//  when vehicle is moving forward.
//  
//  368   3/29/98 3:17p Nrobinso
//  move the unit name left 3 pixels
//  
//  367   3/27/98 10:34p Nrobinso
//  invisible cursor after air support
//  
//  366   3/27/98 8:36p Phu
//  invisble cursor
//  
//  365   3/27/98 8:54p Nrobinso
//  switch to scrolling cursor after air command; do a no air v/o if none
//  
//  364   3/27/98 6:16p Phu
//  new frag/flag
//  
//  363   3/27/98 5:41p Phu
//  fix whereitem location in script place object
//  
//  362   3/27/98 2:19p Phu
//  quest item load from campaign file
//  
//  361   3/26/98 8:24p Nrobinso
//  fix firing when clicking thru in game screens; add MP music
//  
//  360   3/26/98 5:34p Nrobinso
//  attack and defend colros are by color
//  
//  359   3/26/98 4:41p Nrobinso
//  new v/o's
//  
//  358   3/25/98 3:47p Nrobinso
//  play the mission briefing v/o
//  
//  357   3/24/98 4:11p Phu
//  clear firing bar info if user manually changes weapon
//  
//  356   3/24/98 2:29p Nrobinso
//  add sarge voice messages
//  
//  355   3/24/98 1:35p Nrobinso
//  go to voice over intead of text for aagun and blocked paratroopers
//  
//  354   3/22/98 2:51p Nrobinso
//  fix so sarge doesn't kneel when calling in recon or attack/defend now
//  
//  353   3/21/98 8:02p Dmaynard
//  Made UnitFind return NULL instead of asserting  on failure.  Fixes a
//  Bug in Desert2 Multiplayer when a player leaves during startup and the
//  script tries to control his units.
//  
//  352   3/20/98 5:24p Dmaynard
//  Changed assembly-two player to only include one small start light
//  (only one other player).  It used to have 3 lights.
//  
//  351   3/20/98 12:06a Nrobinso
//  clear mouse buttons when not used by sarge
//  
//  350   3/19/98 11:21p Nrobinso
//  left button doesn't work uf paused
//  
//  349   3/19/98 7:49p Nrobinso
//  change pause delays
//  
//  348   3/19/98 1:48p Nrobinso
//  vehicle sfx off if pause for recall mission
//  
//  347   3/18/98 3:08a Nrobinso
//  big map name rules same for multiplayer
//  
//  346   3/17/98 4:43p Dmaynard
//  Added PAUSE_MAPLOAD instead of piggy-backing on the normal PAUSE_LOCAL
//  flags.
//  
//  345   3/17/98 4:17p Bwilcox
//  fixed blue dash multiplayer problem (mortar units)
//  
//  344   3/14/98 8:56p Nrobinso
//  allow switching between mouse button 2 controlling the weapons and
//  forward movement
//  
//  343   3/14/98 3:13p Nrobinso
//  fix chat
//  
//  342   3/14/98 10:56a Nrobinso
//  replace pause delay in mission statement
//  
//  341   3/13/98 8:03p Nrobinso
//  sarge doesn't walkie talkie on a follow command
//  
//  340   3/13/98 7:29p Phu
//  alt gunsight
//  
//  339   3/13/98 4:49p Dmaynard
//  Changed  Comm::IsRemote to return 1 if remote, 0 if not playing, and -1
//  if was playing but has left.  Needed so scripts can send messages to
//  others players that this player has left the game.
//  
//  338   3/13/98 11:39a Nrobinso
//  go back to 2nd mouse button changing weapon
//  
//  337   3/12/98 4:32p Phu
//  no weapon for convoy
//  
//  336   3/12/98 11:39a Aburgess
//  added delay for GAME_PLAY background update
//  
//  335   98-03-11 11:06 Dmaynard
//  
//  334   3/10/98 11:22p Nrobinso
//  move windows cursor routines to input
//  
//  333   3/09/98 1:08p Phu
//  adjust gunsight position
//  
//  332   3/09/98 11:32a Nrobinso
//  remove test windows cursor stuff
//  
//  331   3/08/98 10:10p Nrobinso
//  take showcursor one past where it needs to be
//  
//  330   3/08/98 4:41p Phu
//  don't allow switch to other weapons when in vehicle
//  
//  329   3/08/98 1:52a Nrobinso
//  fix chatting only by broadcast; fix cursor bouncing off bottom
//  
//  328   3/07/98 11:53p Nrobinso
//  move .h file to stdafx
//  
//  327   3/07/98 10:45p Nrobinso
//  fix delays in pop ups; remove "Rules" button in multiplayer dash
//  
//  326   3/06/98 4:14p Phu
//  loading bar
//  
//  325   3/06/98 3:15p Nrobinso
//  allow clicking on start map when deploying things in MP setup
//  
//  324   3/06/98 2:41p Nrobinso
//  mission statement and map use pause delay which ignore direct key input
//  
//  323   3/05/98 6:36p Nrobinso
//  swap enter & fire for executing orders
//  
//  322   3/04/98 6:56p Nrobinso
//  make big maps opaque; no endtalk with right button
//  
//  321   3/04/98 2:57p Phu
//  rubberband after airsupport
//  
//  320   3/04/98 12:48p Phu
//  don't allow sarge control if sarge is dead
//  don't draw gunsight if sarge is dead
//  
//  319   3/03/98 11:47p Nrobinso
//  put in a delay after user clicks thru mission briefing
//  
//  318   3/03/98 9:39p Nrobinso
//  walkie talkie calls
//  
//  317   3/03/98 1:59p Phu
//  esc handling for setup state
//  
//  316   3/03/98 1:16p Phu
//  don't assume vehicle has turret!
//  
//  315   3/03/98 9:20a Aburgess
//  modified Chat to use ESC key to exit chat without sending message
//  
//  314   3/02/98 1:01p Phu
//  keep screen scrolled even for last mortar shell
//  
//  313   3/02/98 11:23a Phu
//  restore after alt-tab for ODF
//  
//  312   2/27/98 1:19p Bwilcox
//  cleaning up the air, supporting script airdrops for foes,e tc
//  
//  311   2/27/98 11:58a Nrobinso
//  add big map
//  
//  310   2/26/98 8:56p Phu
//  renamed some body part stuff
//  
//  309   2/26/98 10:55a Aburgess
//  modifications made to support delayed User Input on info type screens
//  
//  308   2/25/98 3:54p Phu
//  odf dashboard load
//  
//  307   2/25/98 3:25p Phu
//  rename dashboard sprites
//  
//  306   2/25/98 10:38a Nrobinso
//  Enter/left button return you to sarge after giving order
//  
//  305   2/24/98 7:30p Phu
//  cursor load from data file, moved closedatafile
//  
//  304   2/24/98 2:08p Phu
//  changed cursor loading
//  
//  303   2/20/98 6:16p Nrobinso
//  remove unused
//  
//  302   2/17/98 4:00p Nrobinso
//  remove reset cursor
//  
//  301   2/17/98 11:02a Aburgess
//  scriptbmp modified to support game pause and key overrides
//  
//  300   2/16/98 9:25p Nrobinso
//  script display bmp
//  
//  299   2/16/98 3:30p Phu
//  raise gun sight
//  
//  298   2/13/98 7:02p Nrobinso
//  remove special firing for vehicles
//  
//  297   2/13/98 12:47p Phu
//  get rid of firing bar
//  
//  296   2/12/98 8:55p Phu
//  mortar screen scroll, better force of gravity
//  
//  295   2/12/98 4:18p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  294   2/12/98 11:57a Phu
//  grenade stuff
//  
//  293   2/11/98 5:42p Bwilcox
//  
//  292   2/11/98 5:27p Phu
//  delay cursor retract
//  
//  291   2/11/98 4:26p Nrobinso
//  reverse paratroopers & air strikes
//  
//  290   2/11/98 3:18p Phu
//  return cursor back to sarge after firing
//  
//  289   2/11/98 2:42p Phu
//  change mortar firing, have cursor follow range for grenade/mortar
//  
//  288   2/11/98 11:32a Bwilcox
//  enter key stays on sarge by default
//  
//  287   2/10/98 4:26p Nrobinso
//  fix chat state change
//  
//  286   2/10/98 3:36p Phu
//  hook firing cursor to primary hotspot for sarge, sarge fine turning
//  
//  285   2/10/98 3:01p Phu
//  only use bmp as mask for vehicles
//  
//  284   2/09/98 7:26p Nrobinso
//  fix up dash chat
//  
//  283   2/09/98 1:54p Aburgess
//  modifications made to support IN GAME screens, Cursor control, and
//  Rules presentation
//  
//  282   2/09/98 11:16a Awerner
//  added chat button, and moved chat receive to the main receive window
//  
//  281   2/07/98 2:57p Phu
//  don't restore cursor that was never loaded
//  
//  280   2/07/98 12:26a Nrobinso
//  activate next weapon with right button
//  
//  279   2/06/98 11:27p Nrobinso
//  change mission and map function names
//  
//  278   2/06/98 1:58p Bwilcox
//  fixedc curosr in mp setup
//  
//  277   2/06/98 1:04p Bwilcox
//  tmp change gun radius cursor to see if closer is easier to use
//  
//  276   2/06/98 10:02a Bwilcox
//  fix flame3 to flame
//  
//  275   2/05/98 3:57p Bwilcox
//  show unit types on buttons in mp setup
//  
//  274   2/03/98 3:36p Dmaynard
//  Remote Pause for Multi-Player
//  
//  273   2/03/98 3:28p Dmaynard
//  Game Pause Fixe for Multi-Player
//  
//  272   2/03/98 3:22p Bwilcox
//  sargegetactiveweapon now takes arg,
//  fixed avatar mine interactions
//  
//  271   2/03/98 11:26a Nrobinso
//  reenable air support decrement on use; put back global air recon
//  
//  270   2/02/98 3:51p Bwilcox
//  
//  269   2/02/98 3:22p Bwilcox
//  
//  268   2/02/98 3:16p Nrobinso
//  move rules button more
//  
//  267   2/02/98 3:03p Nrobinso
//  move pause button
//  
//  266   2/02/98 1:56p Bwilcox
//  
//  265   2/02/98 1:51p Nrobinso
//  move mission statement sprite
//  
//  264   2/02/98 1:01p Aburgess
//  modifications made to support new mission briefing references through
//  campaign.cpn
//  
//  263   2/02/98 11:49a Nrobinso
//  setup for keyboard go to chat
//  
//  262   2/02/98 11:42a Phu
//  implement ShowWindowsCursor()
//  
//  261   2/02/98 1:37a Nrobinso
//  switch recon back to the way strikes & paratroopers work; return cursor
//  to no command after an air command
//  
//  260   2/02/98 1:07a Nrobinso
//  change ui for multiplayer
//  
//  ...
//  
//  1     6/24/97 11:20a Awerner
//
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "gameflow.h"
#include "Army.h"
#include "Disp.h"
#include "Map.h"
#include "comm.h"
#include "miscfile.h"
#include "input.h"
#include "stratmap.h"
#include "damage.h"
#include "ui.h"
#include "ai.h"
#include "aiaccess.h"
#include "unit.h"
#include "vehicle.h"
#include "gameproc.h"
#include "trooper.h"
#include "item.h"
#include "sarge.h"
#include "bmptext.h"
#include "air.h"
#include "weapon.h"
#include "fileio.h"
#include "commands.h"
#include "States.h"
#include "Audio.h"

extern void Kbd_Sarge_ChgWeapon( BYTE nChar, UINT nFlags );
extern void SendGameReadyMsg(BOOL ready);
extern char scriptDebug;
extern SPRITE RecallSprite;

static void SetSelectedUnit(UNIT *pUnit);
static void ClearSelectedUnit(void);
static BOOL ChatMsgTooBig(void);
static void UI_EndChat(void);
static void LoadOnePlayerRecall( char *file );
static void LoadMultiPlayerRecall( char *file );
static BOOL chathandlekey(UINT key, BOOL down);
char bDisplayPaperMap;

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
DASHBOARD *curdashboard=NULL;
static int chatscrollcounter=0;
GENERIC_TARGET curtarget;
char UI_CurMode=UIMODE_IGNORE;
char NeedToJumpToSarge=0;
int  NumSpecialItems = 5;
char MouseOn = 1;
char MouseDxRotate = 1;
char MouseTurret = 0;
DWORD AirSupportRubberband = 0;
int  UseAltGunsight = 0;
int  UseAltMouseButton = 0;

#define CURSOR_RETRACT_DELAY 2000


SBOX	gBoxMissionMessage = { 120,100,400,200 };
BYTE*	gMissionShadeTable;

ITEM* UndeployedItems[MAX_UNDEPLOYED_STUFF];
ITEM* CurSelectedUndeployedItem;

CURSORTYPE UI_CurCursorType=CURSORTYPE_NORMAL;
int		   UI_CurPlacementItem;

SPRITE *UI_CursorSprites[CURSORTYPE_LAST];

static int inscroll = 0;	// used to know to restart ring of units

SPRITE *UI_Cursor;

int	 GunsightRadius;
SPOINT GunsightCursorPos;
BYTE *pGunsight;

char cursorsLoaded = FALSE;
char draw_cursors = TRUE;

int squadmessagepixelwidth=180;

unsigned char chatMask=0; //who you're sending chat messages to.

BARSTRUCT firingBar;
//char firingBarLoaded=0;

DASHBOARD_GADGETS sargehealth[8]=
{
	DASHBOARD_SARGEHEALTH_1,
	DASHBOARD_SARGEHEALTH_2,
	DASHBOARD_SARGEHEALTH_3,
	DASHBOARD_SARGEHEALTH_4,
	DASHBOARD_SARGEHEALTH_5,
	DASHBOARD_SARGEHEALTH_6,
	DASHBOARD_SARGEHEALTH_7,
	DASHBOARD_SARGEHEALTH_8
};

DASHBOARD_GADGETS vehiclehealth[8]=
{
	DASHBOARD_VEHICLEHEALTH_1,
	DASHBOARD_VEHICLEHEALTH_2,
	DASHBOARD_VEHICLEHEALTH_3,
	DASHBOARD_VEHICLEHEALTH_4,
	DASHBOARD_VEHICLEHEALTH_5,
	DASHBOARD_VEHICLEHEALTH_6,
	DASHBOARD_VEHICLEHEALTH_7,
	DASHBOARD_VEHICLEHEALTH_8
};

DASHBOARD_GADGETS weaponselected[3]=
{
	DASHBOARD_WEAPONSELECTED_1,
	DASHBOARD_WEAPONSELECTED_2,
	DASHBOARD_WEAPONSELECTED_3
};

int damagelevels[8]=
{
	1, 
	15,
	29,
	43,
	57,
	71,
	85,
	100
};

DASHBOARD_GADGETS startlights[3]=
{
	DASHBOARD_STARTLIGHT_1,
	DASHBOARD_STARTLIGHT_2,
	DASHBOARD_STARTLIGHT_3,
};

DASHBOARD_GADGETS trooperinfo[7]=
{
	DASHBOARD_TROOPERINFO_1,
	DASHBOARD_TROOPERINFO_2,
	DASHBOARD_TROOPERINFO_3,
	DASHBOARD_TROOPERINFO_4,
	DASHBOARD_TROOPERINFO_5,
	DASHBOARD_TROOPERINFO_6,
	DASHBOARD_TROOPERINFO_7
};

DASHBOARD_GADGETS airdrop[3]=
{
	DASHBOARD_AIRDROP_1,
	DASHBOARD_AIRDROP_2,
	DASHBOARD_AIRDROP_3
};

DASHBOARD_GADGETS airstrike[3]=
{
	DASHBOARD_AIRSTRIKE_1,
	DASHBOARD_AIRSTRIKE_2,
	DASHBOARD_AIRSTRIKE_3
};

DASHBOARD_GADGETS recon[3]=
{
	DASHBOARD_RECON_1,
	DASHBOARD_RECON_2,
	DASHBOARD_RECON_3
};

DASHBOARD_GADGETS itemselect[18]=
{
	DASHBOARD_ITEMSELECT_1,
	DASHBOARD_ITEMSELECT_2,
	DASHBOARD_ITEMSELECT_3,
	DASHBOARD_ITEMSELECT_4,
	DASHBOARD_ITEMSELECT_5,
	DASHBOARD_ITEMSELECT_6,
	DASHBOARD_ITEMSELECT_7,
	DASHBOARD_ITEMSELECT_8,
	DASHBOARD_ITEMSELECT_9,
	DASHBOARD_ITEMSELECT_10,
	DASHBOARD_ITEMSELECT_11,
	DASHBOARD_ITEMSELECT_12,
	DASHBOARD_ITEMSELECT_13,
	DASHBOARD_ITEMSELECT_14,
	DASHBOARD_ITEMSELECT_15,
	DASHBOARD_ITEMSELECT_16,
	DASHBOARD_ITEMSELECT_17,
	DASHBOARD_ITEMSELECT_18,
};

typedef enum
{
	RECALL_INITIAL_STATE = 0,
	RECALL_MISSION_STATE,
	RECALL_MAP_STATE,

	// nothing below this line
	RECALL_LAST_STATE
} RECALL_STATES;

RECALL_STATES	RecallState = RECALL_INITIAL_STATE;

/////////////////////////////////////////////////////////////////////////////
// Function Prototypes
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////


#define BARSPRITEWIDTH 16
#define BARSPRITEHEIGHT 193
#define BARSPRITEBORDER 2
#define BARSPRITETOPBORDER 20
#define BARCYCLETIME 2000

void initFiringBar(void)
{
//	if (firingBarLoaded)
//		return;

	firingBar.startingTime=0;
	firingBar.curBarType=BAR_TYPE_LAST;
	firingBar.rubberband = ARMY_NO_WEAPON;
/*
	firingBar.color=RGB_YELLOW;
	firingBar.spritePos.x=613;
	firingBar.spritePos.y=12;
	firingBar.barRect.top=firingBar.spritePos.y+BARSPRITETOPBORDER;
	firingBar.barRect.left=firingBar.spritePos.x+BARSPRITEBORDER;
	firingBar.barRect.bottom=firingBar.spritePos.y+BARSPRITEHEIGHT-BARSPRITEBORDER;
	firingBar.barRect.right=firingBar.spritePos.x+BARSPRITEWIDTH-BARSPRITEBORDER;
	SetPath(DASH_PATH);
	if( gpGame->GameType != GAMETYPE_ONEPLAYER )
	{
		if( PlayerColor(ARMY_PLAYER) != 0 )
		{
			char *colordir[] = { "", "tan", "blue", "grey" };
			char path[40];

			sprintf( path, "%s\\%s", DASH_PATH, colordir[PlayerColor(ARMY_PLAYER)] );
			SetPath(path);
		}
	}

	if (LoadSprite( &firingBar.barSprite[BAR_TYPE_GRENADE], "gbar.bmp", BM_TRANSPARENT )<0)
		TRACE("ERROR: Unable to load bar sprite\n");

	if (LoadSprite( &firingBar.barSprite[BAR_TYPE_MORTAR], "mbar.bmp", BM_TRANSPARENT )<0)
		TRACE("ERROR: Unable to load bar sprite\n");


	firingBarLoaded=1;
*/
}

void killFiringBar(void)
{
/*
	if (!firingBarLoaded)
		return;

	FreeSprite(&firingBar.barSprite[BAR_TYPE_GRENADE]);
	FreeSprite(&firingBar.barSprite[BAR_TYPE_MORTAR]);

	firingBarLoaded=0;
*/
	firingBar.startingTime=0;

}


void turnOnFiringBar(BARTYPE curType)
{
	if (curType<BAR_TYPE_LAST)
	{
		firingBar.curBarType=curType;
		firingBar.startingTime=gpGame->dwAnimTime-(BARCYCLETIME/4);
		firingBar.percent = 0;
	}

	SARGE *pSarge;
	pSarge = SargePointer(ARMY_PLAYER);
	switch( pSarge->common.pWeapon->eWeapon )
	{
	case ARMY_MORTAR:
	case ARMY_GRENADE:
		firingBar.rubberband = pSarge->common.pWeapon->eWeapon;
		break;
	default:
		firingBar.rubberband = ARMY_NO_WEAPON;
	}
}


void clearFiringBar( void )
{
	firingBar.startingTime = 0;
	firingBar.rubberband = ARMY_NO_WEAPON;
	firingBar.percent = 0;
	firingBar.retractDelay = 0;
}


int getFiringBarPercent(void)
{
	int n;
	int	retval;
	
	if (!firingBar.startingTime)
		return firingBar.percent;

	n=(gpGame->dwAnimTime-firingBar.startingTime)%BARCYCLETIME;

	if (n<(BARCYCLETIME/2))
		retval = (n*100)/(BARCYCLETIME/2);
	else
		retval = ((BARCYCLETIME-n)*100)/(BARCYCLETIME/2);

	firingBar.percent = retval;

	return retval;
}

int turnOffFiringBar(void)
{
	int retval;

	retval=getFiringBarPercent();
	firingBar.retractDelay = CURSOR_RETRACT_DELAY;
	firingBar.startingTime=0;
	return retval;
}


void updateFiringBar( void )
{
	if( !firingBar.startingTime )
		return;

	getFiringBarPercent();
}


/*
void drawFiringBar(void)
{

	int percent;
	RECT barRect;

	if (!firingBar.startingTime)
		return;

//	if (!VerifyFiringBar())	{
//		turnOffFiringBar();
//		return;
//	}

	DisplaySprite(&firingBar.barSprite[firingBar.curBarType], firingBar.spritePos.x, firingBar.spritePos.y);
	
	percent=getFiringBarPercent();

	barRect=firingBar.barRect;

	barRect.top=barRect.bottom-(firingBar.barRect.bottom-firingBar.barRect.top)*percent/100;

	DrawScreenRect( pBackBuffer, barRect, firingBar.color);
}
*/





int getSelectedItemType(ITEM *pItem)
{
	if (!pItem)
		return ITEMSELECTTYPE_NONE;

	switch(ITEM_TYPE(pItem))
	{
	case ARMY_UNIT:
		switch(ITEM_CLASS(pItem))
		{
		case 	ARMY_RIFLE_MEN: return ITEMSELECTTYPE_RIFLE;
		case 	ARMY_GRENADE_MEN: return ITEMSELECTTYPE_GRENADE;
		case	ARMY_FLAME_MEN:	return ITEMSELECTTYPE_FLAME;
		case ARMY_BAZOOKA_MEN: return ITEMSELECTTYPE_BAZOOKA;
		case ARMY_MORTAR_MEN: return ITEMSELECTTYPE_MORTAR;
		default: return ITEMSELECTTYPE_RIFLE;
		}

	case ARMY_VEHICLE:
		switch(ITEM_CLASS(pItem))
		{
		case ARMY_JEEP:
			return ITEMSELECTTYPE_JEEP;

		case ARMY_TANK:
			return ITEMSELECTTYPE_TANK;

		case ARMY_HALFTRACK:
			return ITEMSELECTTYPE_HALFTRACK;

		case ARMY_CONVOY:
			return ITEMSELECTTYPE_TRUCK;
		}
	}

	return ITEMSELECTTYPE_NONE;
}




int UI_GetUndeployedStuff(ITEM* items[MAX_UNDEPLOYED_STUFF])
{
	int numfound=0;
	int i,j;
	int tempnumfound;
	UNIT *pUnit;

	long uids[MAX_UNDEPLOYED_STUFF];

	for (i=	ARMY_RIFLE_MEN; i<ARMY_LAST_TROOPER;i++)
	{
		tempnumfound=UnitsInHQ( ARMY_PLAYER, (UNIT_TYPE)i, uids);
		for (j=0;j<tempnumfound;j++)
		{
			pUnit=UnitFind(uids[j]);
			if (pUnit &&  pUnit->troops)
				items[numfound++]=(ITEM*)pUnit;
		}
	}

	for (i=ARMY_JEEP; i<=ARMY_CONVOY;i++)
	{
		tempnumfound=VehiclesInHQ( ARMY_PLAYER, (VEHICLE_TYPE) i, uids );
		for (j=0;j<tempnumfound;j++)
			items[numfound++]=(ITEM*)VehicleFind(uids[j]);
	}




    if (scriptDebug)
	for (i=0;i<numfound;i++)
		TRACE("Undeployed Item %d: %s\n", i, ItemDBName(items[i]));

	return numfound;
}

int CanItemDeploy(ITEM *pItem, SPOINT *pPos)
{
	int x = pPos->x >> 4;
	int y = pPos->y >> 4;
	// dont allow placement close to the edge.
	if  (x < (VISIBLE_BOUNDARY+4) || x  >= (map_width-VISIBLE_BOUNDARY-4)) return 0;
	if (y < (VISIBLE_BOUNDARY+4) || y  >= (map_height-VISIBLE_BOUNDARY-4)) return 0;

	switch (ITEM_TYPE(pItem))
	{
	case ARMY_UNIT:
		int owner;
		
		if (UntrafficableUnit(ENCODE_IPOINT(pPos->x, pPos->y)))
			return 0;

		owner = OWNER(the_map.owner_layer[IndexOfWorldPos(*pPos)]);
		if( (owner != (int)gpComm->GetArmyIndex(ARMY_PLAYER)) && (owner != gGlobalPlacement) )
			return 0;

		return 1;
		break;

	case ARMY_VEHICLE:
		
		if (!LegalVehicleDeployPos(pPos, VEHICLE_DEPLOY_HEADING, ITEM_CLASS(pItem)))
			return 0;

		if (TroopersOnVehiclePos( pPos, VEHICLE_DEPLOY_HEADING, ITEM_CLASS(pItem)))
			return 0;

		return 1;
		break;
	}

	return 1;
}


int ItemDeploy(ITEM *pItem, SPOINT *pPos)
{

	if (!CanItemDeploy(pItem, pPos))
		return -1;

	switch (ITEM_TYPE(pItem))
	{
	case ARMY_UNIT:
		
		UnitDeploy((UNIT*)pItem, pPos, 0,DEFENDFIRE);

		return 1;
		break;

	case ARMY_VEHICLE:
		

		VehicleDeploy((VEHICLE*)pItem, pPos, VEHICLE_DEPLOY_HEADING);

		return 1;
		break;
	}

	return -1;
}





//This function must be run once per frame. It either scrolls the screen 
//(if in scroll mode) or updates the screen to look at sarge
#define SCROLL_SPEED 12

extern LONG    user_action;

void UI_InitScreen(void)
{
	NeedToJumpToSarge=1;
}

#define SCROLLMODE_CURSOR_TOP 8
#define SCROLLMODE_CURSOR_LEFT 8
#define SCROLLMODE_CURSOR_BOTTOM 352
#define SCROLLMODE_CURSOR_RIGHT 628


#define CURSOR_CENTER_X 308
#define CURSOR_CENTER_Y 176


char *cursorfilenames[]=
{
	"cros_002.bmp",
	"cros_002.bmp",
	"attk_003.bmp",
	"dfnd_004.bmp",
	"cros_002.bmp", //follow
	"bomb_005.bmp",
	"para_006.bmp",
	"reco_007.bmp",
	"guns_001.bmp",
	"guns_008.bmp",
	"invi_009.bmp",
	"rifl_001_1.bmp",
	"mort_002_1.bmp",
	"flam_003_1.bmp",
	"bzka_004_1.bmp",
	"gren_005_1.bmp",
	"jeep_006_1.bmp",
	"half_007_1.bmp",
	"tank_008_1.bmp",
	"truk_009_1.bmp",
	"rifl_001_2.bmp",
	"mort_002_2.bmp",
	"flam_003_2.bmp",
	"bzka_004_2.bmp",
	"gren_005_2.bmp",
	"jeep_006_2.bmp",
	"half_007_2.bmp",
	"tank_008_2.bmp",
	"truk_009_2.bmp",
	"rifl_001_3.bmp",
	"mort_002_3.bmp",
	"flam_003_3.bmp",
	"bzka_004_3.bmp",
	"gren_005_3.bmp",
	"jeep_006_3.bmp",
	"half_007_3.bmp",
	"tank_008_3.bmp",
	"truk_009_3.bmp"
};


void UI_LoadCursors(void)
{
	int i, num;
	char nbuf[5];
	
	if (cursorsLoaded)
		return;

	ZeroMemory(UI_CursorSprites, sizeof(SPRITE *) * (int)CURSORTYPE_LAST);

	if( _LOAD_FROM_DATAFILE )
	{
		for( i = 0; i <= CURSORTYPE_INVISIBLE; i++ )
		{
			strncpy( nbuf, cursorfilenames[i]+5, 3 );
			nbuf[3] = 0;
			num = atoi(nbuf);			
			if( !(UI_CursorSprites[i] = AcquireObjectSprite( 200, num, 1 )) )
				TRACE("ERROR: Unable to load cursor %s\n", cursorfilenames[i]);
		}
		if( gpGame->GameType != GAMETYPE_ONEPLAYER )
		{
			for( i = 0; i < CURSORTYPE_ITEM_TRUCK_DASH - CURSORTYPE_ITEM_RIFLE_DASH + 1; i++ )
			{
				for( int j = 0; j < 3; j++ )
				{
					int t;

					t = CURSORTYPE_ITEM_RIFLE_DASH + i +
						j * (CURSORTYPE_ITEM_TRUCK_DASH - CURSORTYPE_ITEM_RIFLE_DASH + 1);
					if( !(UI_CursorSprites[t] = AcquireObjectSprite( 201+PlayerColor(ARMY_PLAYER), i+1, j+1 )) )
						TRACE("ERROR: Unable to load cursor %s\n", cursorfilenames[t]);
				}
			}
		}
	}
	else
	{
		char *colordir[] = { "green", "tan", "blue", "grey" };
	
		SetPath(CURSOR_PATH);
		for (i = 0; i <= CURSORTYPE_ALTGUNSIGHT;i++)
		{
			UI_CursorSprites[i] = (SPRITE *)malloc(sizeof(SPRITE));
			if (LoadSprite( UI_CursorSprites[i], cursorfilenames[i], BM_TRANSPARENT )<0)
				TRACE("ERROR: Unable to load cursor %s\n", cursorfilenames[i]);
		}
		// load setup cursors if needed
		if( gpGame->GameType != GAMETYPE_ONEPLAYER )
		{
			char pathname[80];

			sprintf( pathname, "%s\\%s", CURSOR_PATH, colordir[PlayerColor(ARMY_PLAYER)] );
			SetPath( pathname );
			for( i = CURSORTYPE_ITEM_RIFLE_DASH; i < CURSORTYPE_LAST; i++ )
			{
				UI_CursorSprites[i] = (SPRITE *)malloc(sizeof(SPRITE));
				if (LoadSprite( UI_CursorSprites[i], cursorfilenames[i], BM_TRANSPARENT )<0)
					TRACE("ERROR: Unable to load cursor %s\n", cursorfilenames[i]);
//				CenterSpriteHotSpot( &UI_CursorSprites[i] );
			}
		}
	}

	UI_Cursor=UI_CursorSprites[0];

	cursorsLoaded=1;
}

void UI_FreeCursors(void)
{
	int i;

	if (!cursorsLoaded)
		return;


	for(i=0;i<CURSORTYPE_LAST;i++)
	{
		if( UI_CursorSprites[i] )
		{
			if( _LOAD_FROM_DATAFILE )
			{
				if( UI_CursorSprites[i] )
					ReleaseObjectSprite( UI_CursorSprites[i] );
			}
			else
			{
				if( UI_CursorSprites[i]->pGraphic )
					FreeSprite(UI_CursorSprites[i]);
				free( UI_CursorSprites[i] );
			}
			UI_CursorSprites[i] = NULL;
		}
	}

	cursorsLoaded=0;
}

void UI_CursorsOn(void)
{
	draw_cursors = TRUE;
}

void UI_CursorsOff(void)
{
	draw_cursors = FALSE;
}


extern int specialmodedelay;


void UI_DrawShadedCursor( BYTE *pShadowMask, BYTE *pShadeTable, int xpos, int ypos )
{
	int		h, w;
	int		x, y;
	RECT	rect, irect;
	RECT	scrrect = {0, 0, 639, 479};

	if( !pShadowMask )
		return;
	w = *((WORD *)pShadowMask);
	h = *(((WORD *)pShadowMask)+1);
	rect.left = xpos - (w >> 1);
	rect.top = ypos - (h >> 1);
	rect.right = rect.left + w;
	rect.bottom = rect.top + h;
	if (!RectIntersect( &scrrect, &rect, &irect) )
		return;
	x = irect.left;
	y = irect.top;
	w = irect.right - irect.left;
	h = irect.bottom - irect.top;
	irect.left = irect.left - rect.left;
	irect.top = irect.top - rect.top;
	irect.right = irect.left + w;
	irect.bottom = irect.top + h;

	DrawShadeSpriteToOverlayLayer( x, y, pShadowMask, irect, pShadeTable );
}

extern BYTE *PRED_TABLE;

void UI_DrawCursors(void)
{
	if (!cursorsLoaded)
		return;

	if (!draw_cursors)
		return;

	if (UI_CurMode==UIMODE_PLACINGITEM)
	{
		SPOINT worldpos;

		worldpos.x=(short)CursorPos.x;
		worldpos.y=(short)CursorPos.y;

		ScreenToWorld(&worldpos);

		if( CursorPos.y > 380 )
		{
			if( !(UI_CurCursorType >= CURSORTYPE_ITEM_RIFLE_DASH && UI_CurCursorType <= CURSORTYPE_ITEM_TRUCK_DASH) )
				UI_SetCursor((CURSORTYPE)(CURSORTYPE_ITEM_RIFLE_DASH + UI_CurPlacementItem));
		}
		else
		if( CanItemDeploy(CurSelectedUndeployedItem, &worldpos) )
		{
			if( !(UI_CurCursorType >= CURSORTYPE_ITEM_RIFLE_GREEN && UI_CurCursorType <= CURSORTYPE_ITEM_TRUCK_GREEN) )
				UI_SetCursor((CURSORTYPE)(CURSORTYPE_ITEM_RIFLE_GREEN + UI_CurPlacementItem));
		}
		else
		{
			if( !(UI_CurCursorType >= CURSORTYPE_ITEM_RIFLE_RED && UI_CurCursorType <= CURSORTYPE_ITEM_TRUCK_RED) )
				UI_SetCursor((CURSORTYPE)(CURSORTYPE_ITEM_RIFLE_RED + UI_CurPlacementItem));
		}
	}


	if ( UI_CurMode == UIMODE_LOOKINGATSARGE || (specialmodedelay > 0) )
	{
		SARGE *pSarge;

		pSarge = SargePointer(ARMY_PLAYER);
		if( pSarge->common.nStrength > 0 )
		{
			if( pSarge->pVehicle )
			{
				if( pSarge->pVehicle->common.pWeapon && 
					pSarge->pVehicle->common.pWeapon->eWeapon )
					DisplaySpriteClipped( UI_CursorSprites[CURSORTYPE_GUNSIGHT+UseAltGunsight], 
											GunsightCursorPos.x, GunsightCursorPos.y);
			}
			else
			if( pSarge->common.pWeapon && pSarge->common.pWeapon->eWeapon )				
				DisplaySpriteClipped( UI_CursorSprites[CURSORTYPE_GUNSIGHT+UseAltGunsight],
										GunsightCursorPos.x, GunsightCursorPos.y);
		}
	}
	else if( UI_Cursor )
		DisplaySpriteClipped( UI_Cursor, CursorPos.x, CursorPos.y );
}


#define GUNSIGHT_RADIUS 95

#define GUNSIGHT_CLIP_TOP 0
#define GUNSIGHT_CLIP_LEFT 0
#define GUNSIGHT_CLIP_RIGHT 640
#define GUNSIGHT_CLIP_BOTTOM 375


int GetDesiredGunsightRadius( SARGE *pSarge )
{
	int radius;

	radius = GUNSIGHT_RADIUS;
	if( pSarge->pVehicle )
		return radius;

	if( !firingBar.startingTime )
	{
		if( firingBar.retractDelay > 0 )
			firingBar.retractDelay -= gpGame->dwDeltaTime;
		else
		{
			firingBar.retractDelay = 0;
			if( firingBar.percent > 2 )
				firingBar.percent -= 2;
			else
				firingBar.percent = 0;
		}
	}

	switch(pSarge->common.pWeapon->eWeapon)
	{
	case ARMY_GRENADE:
	case ARMY_MORTAR:
		radius = WeaponMinRange(pSarge->common.pWeapon->eWeapon);
		radius = radius + 
			(WeaponMaxRange(pSarge->common.pWeapon->eWeapon) - radius) * getFiringBarPercent() / 100;
		break;
	default:
		if( firingBar.rubberband > 0 )
		{
			radius = WeaponMinRange( firingBar.rubberband );
			radius = radius +
				(WeaponMaxRange(firingBar.rubberband) - radius) * getFiringBarPercent() / 100;
			if( firingBar.percent <= 2 )
				firingBar.rubberband = ARMY_NO_WEAPON;
		}
		break;
	}
	return radius;
}


int GunsightXAdjustment = 6;
int GunsightYAdjustment[3] = {2, 16, 20};

void UI_PositionGunsight(void)
{

	SARGE *pSarge;
	VEHICLE *pVehicle;

	int facing;
	SPOINT centerpoint;
	SPOINT targetpoint;
	float ratio;

	if (Armies[ARMY_PLAYER].Status == 0) return; // dead army

	if( UI_CurMode != UIMODE_LOOKINGATSARGE )
		if( specialmodedelay <= 0)
			return;	

	pSarge=SargePointer(ARMY_PLAYER);
	
	if (!pSarge)
		return;

	pVehicle=pSarge->pVehicle;

	if (pVehicle)	
	{
		VehicleFiringPosition(pVehicle, &centerpoint);
//		centerpoint=pVehicle->common.position;
		facing=pVehicle->gun_facing;
	}
	else	
	{
//		SargeFiringPosition(pSarge, &centerpoint);
		centerpoint=pSarge->common.position;
		centerpoint.x += GunsightXAdjustment;
		switch( GetItemHeightNoElevation((ITEM *)pSarge) )
		{
		case 4:
			centerpoint.y -= GunsightYAdjustment[0];
			break;
		case 6:
			centerpoint.y -= GunsightYAdjustment[1];
			break;
		case 8:
			centerpoint.y -= GunsightYAdjustment[2];
			break;
		}
		facing=pSarge->gun_facing;
	}


	WorldToScreen(&centerpoint);

	targetpoint.x=(short)(centerpoint.x+ GunsightRadius*cos_table[facing]);
	targetpoint.y=(short)(centerpoint.y+ GunsightRadius*sin_table[facing]);

	if (targetpoint.x>GUNSIGHT_CLIP_RIGHT)
	{
		ratio=((float)(GUNSIGHT_CLIP_RIGHT-centerpoint.x))/(targetpoint.x-centerpoint.x);
		targetpoint.x=GUNSIGHT_CLIP_RIGHT;
		targetpoint.y=(short)(centerpoint.y+ratio*(targetpoint.y-centerpoint.y));
	}
	else if (targetpoint.x<GUNSIGHT_CLIP_LEFT)
	{
		ratio=((float)(centerpoint.x-GUNSIGHT_CLIP_LEFT))/(centerpoint.x-targetpoint.x);
		targetpoint.x=GUNSIGHT_CLIP_LEFT;
		targetpoint.y=(short)(centerpoint.y-ratio*(centerpoint.y-targetpoint.y));
	};

	if (targetpoint.y>GUNSIGHT_CLIP_BOTTOM)
	{
		ratio=((float)(GUNSIGHT_CLIP_BOTTOM-centerpoint.y))/(targetpoint.y-centerpoint.y);
		targetpoint.y=GUNSIGHT_CLIP_BOTTOM;
		targetpoint.x=(short)(centerpoint.x+ratio*(targetpoint.x-centerpoint.x));
	}
	else if (targetpoint.y<GUNSIGHT_CLIP_TOP)
	{
		ratio=((float)(centerpoint.y-GUNSIGHT_CLIP_TOP))/(centerpoint.y-targetpoint.y);
		targetpoint.y=GUNSIGHT_CLIP_TOP;
		targetpoint.x=(short)(centerpoint.x-ratio*(centerpoint.x-targetpoint.x));
	}

	GunsightCursorPos=targetpoint;	
}



void ScrollModeUpdateCursor(short x, short y)
{
	CursorPos.x+=x;
	CursorPos.y+=y;

	if (CursorPos.x>SCROLLMODE_CURSOR_RIGHT)
		CursorPos.x=SCROLLMODE_CURSOR_RIGHT;

	if (CursorPos.x<SCROLLMODE_CURSOR_LEFT)
		CursorPos.x=SCROLLMODE_CURSOR_LEFT;
	
	if (CursorPos.y>SCROLLMODE_CURSOR_BOTTOM)
		CursorPos.y-=y;
//		CursorPos.y=SCROLLMODE_CURSOR_BOTTOM;
	
	if (CursorPos.y<SCROLLMODE_CURSOR_TOP)
		CursorPos.y=SCROLLMODE_CURSOR_TOP;
}



void ScrollMapOrCursor(short x, short y)
{
	short dx, dy;

	if ((x>0) && (CursorPos.x<CURSOR_CENTER_X))
	{
		short d = (short)(CURSOR_CENTER_X-CursorPos.x);
		if (x<=d)
		{
			CursorPos.x+=x;
			x=0;
		}
		else
		{
			CursorPos.x+=d;
			x-=d;
		}
	}

	if ((x<0) && (CursorPos.x>CURSOR_CENTER_X))
	{
		short d = (short)(CURSOR_CENTER_X-CursorPos.x);
		if (x>=d)
		{
			CursorPos.x+=x;
			x=0;
		}
		else
		{
			CursorPos.x+=d;
			x-=d;
		}
	}

	if ((y>0) && (CursorPos.y<CURSOR_CENTER_Y))
	{
		short d= (short)(CURSOR_CENTER_Y-CursorPos.y);
		if (y<=d)
		{
			CursorPos.y+=y;
			y=0;
		}
		else
		{
			CursorPos.y+=d;
			y-=d;
		}
	}

	if ((y<0) && (CursorPos.y>CURSOR_CENTER_Y))
	{
		short d= (short)(CURSOR_CENTER_Y-CursorPos.y);
		if (y>=d)
		{
			CursorPos.y+=y;
			y=0;
		}
		else
		{
			CursorPos.y+=d;
			y-=d;
		}
	}

	//Attempts to scroll the screen x and y pixels, and returns
	//the actual distance scrolled
	ScrollMapReturn(x,y,&dx,&dy);
	if ((x!=dx) || (y!=dy))
		ScrollModeUpdateCursor(x-dx, y-dy);
}



extern long user_action;		


void InitSargeView(SARGE* pSarge)
{
    ANIM *curanim;
    curanim=pSarge->pAvatar->pAnimation;
    MapJumpToAnim( curanim, TRUE, FALSE, 0 );
    SargeSetView(pSarge);
}


int DiffInAngle( int angle1, int angle2 )
{
	int diff;

	diff = abs(angle2 - angle1);
	if( diff > 127 )
		diff = 256-diff;
	ASSERT( diff >= 0 && diff < 256 );
	return diff;
}


void UI_ProcessScreen(void)
{   
	SARGE *pSarge;
	ANIM *curanim;
	int x=0,y=0;

	switch(UI_CurMode)
	{
	case UIMODE_IGNORE:
		break;
	case UIMODE_LOOKINGATSARGE:
		BOOL reverse;
		int  mindist;
		double	 mult;				// multiplier

		pSarge=SargePointer(ARMY_PLAYER);
		reverse = FALSE;
		mindist = 0;

		GunsightRadius = GetDesiredGunsightRadius( pSarge );

		if (pSarge->pVehicle)
		{
			if (pSarge->pVehicle->bTurret)
			{
				int diff;
				curanim = &pSarge->pVehicle->pAnimation[TURRETANIM];
				diff = DiffInAngle( pSarge->pVehicle->gun_facing, pSarge->pVehicle->common.facing );
				mult = (double)((64 - diff)/64.0);
			}
			else
			{
				curanim = &pSarge->pVehicle->pAnimation[BODYANIM];
				mult = 1.0;
			}
		//  DSM hack to try to get vehicles to scroll properly enough so that you can see where you are going
			mindist = (int)(pSarge->pVehicle->velocity * mult);
		}
		else
		{
			if (!pSarge->pAvatar)
			{
				//sarge is dead, so can't look at him
				return;
			}
			curanim=pSarge->pAvatar->pAnimation;

			// walk backwards
			if( pSarge->common.bItemFlags & ITEM_REVERSED ) 
				reverse = TRUE;

			if( pSarge->common.pWeapon->eWeapon == ARMY_MORTAR ||
				firingBar.rubberband == ARMY_MORTAR )
				mindist = GunsightRadius;			// have screen follow me
		}

		if (NeedToJumpToSarge)
		{
			MapJumpToAnim( curanim, TRUE, reverse, mindist );
			NeedToJumpToSarge=0;
		}
		else
			MapLookAtAnim(curanim, TRUE, reverse, mindist);

		UI_PositionGunsight();

		SargeSetView(pSarge);
		break;

	case UIMODE_SCROLLING:
	case UIMODE_PLACINGITEM:
		if( AirSupportRubberband > 0 )
		{
			if( gpGame->dwDeltaTime < AirSupportRubberband )
				AirSupportRubberband -= gpGame->dwDeltaTime;
			else
				endScrollingMode();
		}
		if( NeedToJumpToSarge )
		{
			SARGE *pSarge;

			pSarge = SargePointer(ARMY_PLAYER);
			MapJumpToPoint( pSarge->common.position.x, pSarge->common.position.y );
			NeedToJumpToSarge = 0;
			break;
		}
		if ((user_action & DO_ACCELERATE) || CursorAtTop)
			y=-SCROLL_SPEED;

		if ((user_action & DO_DECELERATE) || CursorAtBottom)
			y=SCROLL_SPEED;

		if ((user_action & DO_TURN_RIGHT) || CursorAtRight)
			x=SCROLL_SPEED;

		if ((user_action & DO_TURN_LEFT) || CursorAtLeft)
	
			x=-SCROLL_SPEED;
	

		ScrollMapOrCursor(x,y);
		break;
	}
}


void UI_SetCursor(CURSORTYPE newcursortype)
{
	UI_CurCursorType=newcursortype;
	UI_Cursor= UI_CursorSprites[UI_CurCursorType];
}

void endScrollingMode()
{
	if ( gpGame->GetSubState() == PLAY_SUB_STATE) {
		UI_CurMode=UIMODE_LOOKINGATSARGE;
		UI_SetCursor(CURSORTYPE_NORMAL);
		AirSupportRubberband = 0;
		NeedToJumpToSarge=1;
		inscroll = 0;
	}
}


void UI_PutItemBackInTray( void )
{
	if( UI_CurMode != UIMODE_PLACINGITEM )
		return;

	for( int i = 0; i < 10; i++ )
		if (UndeployedItems[i]==NULL)
		{
			UndeployedItems[i]=CurSelectedUndeployedItem;
			CurSelectedUndeployedItem=NULL;
			break;
		}

	if (CurSelectedUndeployedItem)
		TRACE("ERROR: could not put back the item being placed\n");

    UI_CurMode=UIMODE_SCROLLING;
	UI_SetCursor(CURSORTYPE_NORMAL);
}


void UI_SwitchMode( int jumptounit )
{
	if (UI_CurMode==UIMODE_LOOKINGATSARGE)
	{
		UI_SetCursor(CURSORTYPE_SCROLLING);
		UI_CurMode=UIMODE_SCROLLING;
		if( jumptounit )
		{
			if (curselectedunit)
			{
				//Clears out any so far unresolved scrolling
				MapUndoScrolling();
				MapJumpToPoint(curselectedunit->common.position.x, curselectedunit->common.position.y);
			}
		}
        inscroll = TRUE;				// keep hunting now
		CursorPos.x=CURSOR_CENTER_X;
		CursorPos.y=CURSOR_CENTER_Y;
	}
	else
	{
		if (UI_CurMode == UIMODE_PLACINGITEM)
		{
			UI_PutItemBackInTray();
			return;
		}

        endScrollingMode();
	}
}


void UI_EnterItemPlacingMode(void)
{
	UI_CurPlacementItem = getSelectedItemType(CurSelectedUndeployedItem)-1;
	UI_SetCursor((CURSORTYPE)(CURSORTYPE_ITEM_RIFLE_DASH + UI_CurPlacementItem));
	UI_CurMode=UIMODE_PLACINGITEM;
}
		



///========================================================================
//	Function:		NumHumanPlayers()
//
//	Description:
//		Returns the number of actual humans who are playing
//
//	Input:			none
//
//	Ouput:			the number of human players		
//
///========================================================================

int NumHumanPlayers(void)
{
	int totalnum, numhuman=1;
	int i;

	totalnum= 4; // always use all players, some missions need it.
	for (i=1;i<totalnum;i++)
		if (gpComm->IsRemote(i)==1)
			numhuman++;

//	TRACE("found %d human players\n", numhuman);
	
//  The following is necessary to be able to play a multiplayer game with one player
//  Otherwise no start button appears on dash and we can end the setup phase
	if( gpGame->GameType == GAMETYPE_HOST_MULTIPLAYER && numhuman < 2 ) numhuman = 2;
	return numhuman; 
}




BOOL turnoffkeys(void);
void turnonkeys(int whichbutton, int whichmousebutton);
void SendDashboardChat( void );

int messageColorIndices[4]=
{
	10,
	11,
	12,
	7
};

static BOOL chathandlekey(UINT character)  //returns true if the character was used
{
	char c=character;

	ASSERT(curdashboard);

	switch (c)	{
		case VK_ESCAPE:
			curdashboard->texthasarrived=TRUE;
			ZeroMemory(curdashboard->curmessage, curdashboard->curmessagelength);
			curdashboard->curmessagelength = 0;
			UI_EndChat();
			return TRUE;
			break;

		case VK_BACK:
			curdashboard->texthasarrived=TRUE;
			if (curdashboard->curmessagelength-1>0)
			{
				curdashboard->curmessage[--curdashboard->curmessagelength]=0;
				curdashboard->curmessage[curdashboard->curmessagelength-1]='_';
			}
			return TRUE;
			break;

		case VK_RETURN:
			curdashboard->texthasarrived=TRUE;
			SendDashboardChat();
			UI_EndChat();
			return TRUE;
			break;

		default:
			if ( c >= VK_SPACE )	{
				curdashboard->texthasarrived=TRUE;
				curdashboard->curmessage[curdashboard->curmessagelength-1]=c;
				if (ChatMsgTooBig())	{
					SendDashboardChat();
					curdashboard->curmessage[curdashboard->curmessagelength++]=c;
				}

				curdashboard->curmessage[curdashboard->curmessagelength++]='_';
				return TRUE;
			}
			break;
	}

	return FALSE;
}


static BOOL ChatMsgTooBig()	{
	if (curdashboard->curmessagelength>=MESSAGE_COMP_MAXLENGTH-1)
		return TRUE;

	if (BmpTextWidth( curdashboard->curmessage, BMPFONT_DASHCOMM, NULL) > squadmessagepixelwidth)
		return TRUE;

	return FALSE;
}


void SendDashboardChat( void )
{
	//append the proper color header
	char tempbuffer[MESSAGE_COMP_MAXLENGTH+5];

	// strip off the underscore
	if ( curdashboard->curmessagelength )
	{
		--curdashboard->curmessagelength;
		curdashboard->curmessage[curdashboard->curmessagelength]=0;

		if (curdashboard->curmessage[0])	{
			tempbuffer[0]=messageColorIndices[PlayerColor(ARMY_PLAYER)];
			strcpy(tempbuffer+1, curdashboard->curmessage);

			// finally, send the chat message out to all
			// the other players
			for (int i=1;i<ARMY_LAST_ARMY;i++)
				if (chatMask & (1<<i))
					SendChatMessageToPlayer(tempbuffer, i);

			receivechatmessage(tempbuffer);

			ZeroMemory(curdashboard->curmessage, curdashboard->curmessagelength);
		}
	}
	curdashboard->curmessagelength=0;
}

TKeyBindingEntry **chatPreviousUI = NULL;


BOOL turnoffkeys(void)
{
	if (curdashboard->capturingkeys)
	{
		curdashboard->capturingkeys=FALSE;
		pMainFrame->SetUICharHandler(NULL);
		pKeyTable = chatPreviousUI;
		chatPreviousUI = NULL;
		return TRUE;
	}
	else
		return FALSE;
}

void turnonkeys(int whichbutton, int whichmousebutton, void *dummy)
{
	if (!curdashboard->capturingkeys)
	{
		curdashboard->capturingkeys=TRUE;
		pMainFrame->SetUICharHandler(chathandlekey);
		curdashboard->curmessagelength=0;
		curdashboard->curmessage[curdashboard->curmessagelength++]='_';
		chatPreviousUI = pKeyTable;
		pKeyTable = ChatKeyTable;
	}
}


///========================================================================
//	Function:		Gadget_Press_Button()
//
//	Description:
//		Called when an on-screen button is pressed. Activates the
//		appropriate gadget
//
//	Input:			button				pointer to the on screen button
//					whichmousebutton	int (0=left, 1=right)	
//					whichsubdivision	used only for lists... tells which was clicked
//
//	Ouput:			none		
//
///========================================================================

void Gadget_Press_Button(ONSCREENBUTTON *button, int whichmousebutton, int whichsubdivision)
{
	if (!button)
		return;
	if (!button->pGadget)
		return;
	switch(button->pGadget->type)
	{
	case (GADGETTYPE_BUTTON) :
		GADGET_BUTTON *gadget_button;

		gadget_button=(GADGET_BUTTON*)button->pGadget->pGadget;

		gadget_button->curdelay=GADGET_BUTTON_DELAY;
		if (gadget_button->func)
			gadget_button->func(whichmousebutton);

		break;
	case (GADGETTYPE_MULTIBUTTON) :
		GADGET_MULTIBUTTON *gadget_multibutton;

		gadget_multibutton=(GADGET_MULTIBUTTON*)button->pGadget->pGadget;

		gadget_multibutton->curdelay=GADGET_BUTTON_DELAY;
		if (gadget_multibutton->func)
			gadget_multibutton->func(whichmousebutton, gadget_multibutton->curpicture);

		break;

	case (GADGETTYPE_2WAYBUTTON) :
		GADGET_2WAYBUTTON *gadget_2waybutton;

		gadget_2waybutton=(GADGET_2WAYBUTTON*) button->pGadget->pGadget;

		gadget_2waybutton->curstatus=!(gadget_2waybutton->curstatus);
		
		if (gadget_2waybutton->func)
			gadget_2waybutton->func(gadget_2waybutton->curstatus, whichmousebutton);

		break;

	case (GADGETTYPE_RADIOBUTTON) :
		{
			GADGET_RADIOBUTTON *radiobutton=(GADGET_RADIOBUTTON*) button->pGadget->pGadget;
	
			if (button->whichpart>=radiobutton->numbuttons)
			{
				return;
			}

			if (button->whichpart==radiobutton->curbutton)
				switch (radiobutton->radiotype)
				{
				case (GADGET_RADIOTYPE_REPRESS) :
					if (radiobutton->func)
						radiobutton->func(radiobutton->curbutton, whichmousebutton);
					break;
				case (GADGET_RADIOTYPE_DESELECT) :
					radiobutton->curbutton=GADGET_RADIO_NONE;
					if (radiobutton->func)
						radiobutton->func(GADGET_RADIO_NONE, whichmousebutton);
					break;
				}
			else
			{
				radiobutton->curbutton=button->whichpart;
				if (radiobutton->func)
					radiobutton->func(radiobutton->curbutton, whichmousebutton);
			};						

			break;
		}
	case (GADGETTYPE_LIST) :
		{
			GADGET_LIST *list=(GADGET_LIST*) button->pGadget->pGadget;
			int newlistitem;		

			switch (button->whichpart)
			{
			case (GADGET_LIST_BUTTONTYPE_MAIN): 
				if (whichsubdivision>=list->displaysize)
				{
					return;
				}

				newlistitem=list->howfarscrolled+whichsubdivision;
				if (newlistitem>=list->listsize)
					return;

				if (list->listtype==GADGET_LISTTYPE_NOSELECTIONS)
				{
					if (list->func)
						list->func(newlistitem, whichmousebutton, list->extradata);
					return;
				}	

				if (newlistitem==list->curitem)
					switch (list->listtype)
					{
					case (GADGET_LISTTYPE_REPRESS) :
						if (list->func)
							list->func(newlistitem, whichmousebutton, list->extradata);
						break;
					case (GADGET_LISTTYPE_DESELECT):
						list->curitem=GADGET_LIST_NONE;
						if (list->func)
							list->func(GADGET_LIST_NONE, whichmousebutton, list->extradata);
						break;
					}
				else
					{
					list->curitem=newlistitem;
					if (list->func)
						list->func(newlistitem, whichmousebutton, list->extradata);
				};

				break;

			case (GADGET_LIST_BUTTONTYPE_SCROLLUP):
				if (list->scrollbuttons[0])
					list->scrollbuttons[0]->curdelay=GADGET_BUTTON_DELAY;			

				if (list->howfarscrolled>0)
					list->howfarscrolled--;

				break;

			case (GADGET_LIST_BUTTONTYPE_SCROLLDOWN):
				if (list->scrollbuttons[1])
					list->scrollbuttons[1]->curdelay=GADGET_BUTTON_DELAY;

				if (list->howfarscrolled+list->displaysize<list->listsize)
					list->howfarscrolled++;

				break;
			};
			break;
		}
	}
}


#define DISPLAYSPRITE(s,x,y) { if (s!=NULL) DisplaySprite(s,x,y);}
#define DISPLAYSPRITEFRONT(s,x,y) { if (s!=NULL) DisplaySpriteFront(s,x,y);}


///========================================================================
//	Function:		Gadget_Draw()
//
//	Description:
//		Draws a UI gadget in its current state
//
//	Input:			gadget				pointer to the gadget
//
//	Ouput:			none		
//
///========================================================================

void Gadget_Draw(GADGET *gadget)
{

	if (!gadget->pGadget)
		return;

	switch (gadget->type)
	{
	case GADGETTYPE_BUTTON:
		{
			GADGET_BUTTON *button=(GADGET_BUTTON*)gadget->pGadget;

			if (button->curdelay)
			{
				DISPLAYSPRITE(button->sprites[1], button->screenpos.x, button->screenpos.y);
				button->curdelay--;
			}
			else
				DISPLAYSPRITE(button->sprites[0], button->screenpos.x, button->screenpos.y);

			break;
		}

	case GADGETTYPE_MULTIBUTTON:
		{
			GADGET_MULTIBUTTON *button=(GADGET_MULTIBUTTON*)gadget->pGadget;

			if (button->curdelay)
			{
				DISPLAYSPRITE(button->sprites[1][button->curpicture], button->screenpos.x, button->screenpos.y);
				button->curdelay--;
			}
			else
				DISPLAYSPRITE(button->sprites[0][button->curpicture], button->screenpos.x, button->screenpos.y);

			break;
		}

	case GADGETTYPE_2WAYBUTTON:
		{
			GADGET_2WAYBUTTON *button=(GADGET_2WAYBUTTON*)gadget->pGadget;

			DISPLAYSPRITE(button->sprites[button->curstatus], button->screenpos.x, button->screenpos.y);

			break;
		}

	case GADGETTYPE_RADIOBUTTON:
		{
			GADGET_RADIOBUTTON *button=(GADGET_RADIOBUTTON*)gadget->pGadget;
			int i;

			for (i=0;i<button->numbuttons;i++)
				if (i==button->curbutton)
				{
					DISPLAYSPRITE(button->sprites[1][i], button->screenpos[i].x, button->screenpos[i].y);
				}
				else
					DISPLAYSPRITE(button->sprites[0][i], button->screenpos[i].x, button->screenpos[i].y);

			break;
		}
	
	case GADGETTYPE_LIST:
		{
			GADGET_LIST *list=(GADGET_LIST*)gadget->pGadget;
			int i;

			TextSetColors( RGB_GREEN, RGB_BLACK ); //eventually, the list structure will
												   //specify the font color

			for (i=0;i<list->displaysize;i++)
				if ((i+list->howfarscrolled==list->curitem) && (list->listtype!=GADGET_LISTTYPE_NOSELECTIONS))
				{
					TextSetColors( RGB_BLACK, RGB_WHITE);
					BmpTextWrite( pBackBuffer, list->screenpos.x, list->screenpos.y + list->spacing * i,
						list->listtext[i + list->howfarscrolled], BMPFONT_DASHCOMM, NULL, GREEN_IDX );
/*
					TextWrite( pBackBuffer, list->screenpos.x, list->screenpos.y+list->spacing*i, 
						list->listtext[i+list->howfarscrolled], list->listfont, (SIZE*)list->cursordata);
*/
					TextSetColors( RGB_WHITE, RGB_BLACK);
				}
				else
					BmpTextWrite( pBackBuffer, list->screenpos.x, list->screenpos.y + list->spacing * i,
						list->listtext[i + list->howfarscrolled], BMPFONT_DASHCOMM, NULL, GREEN_IDX );
/*
					TextWrite( pBackBuffer, list->screenpos.x, list->screenpos.y+list->spacing*i, 
						list->listtext[i+list->howfarscrolled], list->listfont, (SIZE*)list->cursordata);
*/
			if (list->drawfunc)
				list->drawfunc(list);

			break;
		}

	case GADGETTYPE_TEXTBOX:
		{
			GADGET_TEXTBOX *textbox=(GADGET_TEXTBOX*)gadget->pGadget;
			int i, linestodraw;

			TextSetColors( RGB_GREEN, RGB_BLACK);


			if (textbox->linesoftext<textbox->onscreenlines)
				linestodraw=textbox->linesoftext;
			else
				linestodraw=textbox->onscreenlines;
			for (i=0;i<linestodraw;i++)
/*
				TextWrite(pBackBuffer, textbox->screenpos.x, textbox->screenpos.y+textbox->spacing*i,
					textbox->boxtext[i], textbox->textfont, NULL);
*/
				BmpTextWrite( pBackBuffer, textbox->screenpos.x, textbox->screenpos.y+textbox->spacing * i,
					textbox->boxtext[i], BMPFONT_DASHCOMM, NULL, GREEN_IDX );
			break;
		}




	}
}

///========================================================================
//	Function:		Gadget_DrawFront()
//
//	Description:
//		Draws a UI gadget in its current state into the Front Buffer
//
//	Input:			gadget				pointer to the gadget
//
//	Ouput:			none		
//
///========================================================================

void Gadget_DrawFront(GADGET *gadget)
{
	if (!gadget)
		return;

	if (!gadget->pGadget)
		return;

	switch (gadget->type)
	{
	case GADGETTYPE_BUTTON:
		{
			GADGET_BUTTON *button=(GADGET_BUTTON*)gadget->pGadget;

			if (button->curdelay)
			{
				DISPLAYSPRITEFRONT(button->sprites[1], button->screenpos.x, button->screenpos.y);
				button->curdelay--;
			}
			else
				DISPLAYSPRITEFRONT(button->sprites[0], button->screenpos.x, button->screenpos.y);

			break;
		}

	case GADGETTYPE_MULTIBUTTON:
		{
			GADGET_MULTIBUTTON *button=(GADGET_MULTIBUTTON*)gadget->pGadget;

			if (button->curdelay)
			{
				DISPLAYSPRITEFRONT(button->sprites[1][button->curpicture], button->screenpos.x, button->screenpos.y);
				button->curdelay--;
			}
			else
				DISPLAYSPRITEFRONT(button->sprites[0][button->curpicture], button->screenpos.x, button->screenpos.y);

			break;
		}

	case GADGETTYPE_2WAYBUTTON:
		{
			GADGET_2WAYBUTTON *button=(GADGET_2WAYBUTTON*)gadget->pGadget;

			DISPLAYSPRITEFRONT(button->sprites[button->curstatus], button->screenpos.x, button->screenpos.y);

			break;
		}

	case GADGETTYPE_RADIOBUTTON:
		{
			GADGET_RADIOBUTTON *button=(GADGET_RADIOBUTTON*)gadget->pGadget;
			int i;

			for (i=0;i<button->numbuttons;i++)
				if (i==button->curbutton)
				{
					DISPLAYSPRITEFRONT(button->sprites[1][i], button->screenpos[i].x, button->screenpos[i].y);
				}
				else
					DISPLAYSPRITEFRONT(button->sprites[0][i], button->screenpos[i].x, button->screenpos[i].y);

			break;
		}
	
	case GADGETTYPE_LIST:
		{
			GADGET_LIST *list=(GADGET_LIST*)gadget->pGadget;
			int i;

			TextSetColors( RGB_GREEN, RGB_BLACK ); //eventually, the list structure will
												   //specify the font color

			for (i=0;i<list->displaysize;i++)
				if ((i+list->howfarscrolled==list->curitem) && (list->listtype!=GADGET_LISTTYPE_NOSELECTIONS))
				{
					TextSetColors( RGB_BLACK, RGB_WHITE);
					BmpTextWrite( pFrontBuffer, list->screenpos.x, list->screenpos.y + list->spacing * i,
						list->listtext[i + list->howfarscrolled], BMPFONT_DASHCOMM, NULL, GREEN_IDX );
/*
					TextWrite( pFrontBuffer, list->screenpos.x, list->screenpos.y+list->spacing*i, 
						list->listtext[i+list->howfarscrolled], list->listfont, (SIZE*)list->cursordata);
*/
					TextSetColors( RGB_WHITE, RGB_BLACK);
				}
				else
					BmpTextWrite( pFrontBuffer, list->screenpos.x, list->screenpos.y + list->spacing * i,
						list->listtext[i + list->howfarscrolled], BMPFONT_DASHCOMM, NULL, GREEN_IDX );
/*
					TextWrite( pFrontBuffer, list->screenpos.x, list->screenpos.y+list->spacing*i, 
						list->listtext[i+list->howfarscrolled], list->listfont, (SIZE*)list->cursordata);
*/
			if (list->drawfunc)
				list->drawfunc(list);

			break;
		}

	case GADGETTYPE_TEXTBOX:
		{
			GADGET_TEXTBOX *textbox=(GADGET_TEXTBOX*)gadget->pGadget;
			int i, linestodraw;

			TextSetColors( RGB_GREEN, RGB_BLACK);


			if (textbox->linesoftext<textbox->onscreenlines)
				linestodraw=textbox->linesoftext;
			else
				linestodraw=textbox->onscreenlines;
			for (i=0;i<linestodraw;i++)
/*
				TextWrite(pFrontBuffer, textbox->screenpos.x, textbox->screenpos.y+textbox->spacing*i,
					textbox->boxtext[i], textbox->textfont, NULL);
*/
				BmpTextWrite( pFrontBuffer, textbox->screenpos.x, textbox->screenpos.y+textbox->spacing * i,
					textbox->boxtext[i], BMPFONT_DASHCOMM, NULL, GREEN_IDX );
			break;
		}




	}
}

///========================================================================
//	Function:		Dashboard_Draw()
//
//	Description:
//		Draws a dashboard
//
//	Input:			dashboard			pointer to the dashboard
//
//	Ouput:			none		
//
///========================================================================

void Dashboard_Draw(DASHBOARD *dashboard)
{
	DASHBOARD_GADGETS curgadget;

	if (!dashboard)
		return;
	
	DisplaySprite(dashboard->dashboardsprite, dashboard->dashboardloc.x, dashboard->dashboardloc.y);

	for (curgadget=DASHBOARD_START; curgadget!=DASHBOARD_LAST; curgadget=(DASHBOARD_GADGETS)(((int)curgadget)+1))
		if (dashboard->dashboard_gadgets[curgadget])
			if (dashboard->chunksActive[dashboard->dashboard_gadgets[curgadget]->chunk])
				Gadget_Draw(dashboard->dashboard_gadgets[curgadget]);


}

#define CHATSCROLLTIME 5000 //milliseconds

///========================================================================
//	Function:		Dashboard_DrawFront()
//
//	Description:
//		Draws a dashboard to the front buffer
//
//	Input:			dashboard			pointer to the dashboard
//
//	Ouput:			none		
//
///========================================================================

void Dashboard_DrawFront(DASHBOARD *dashboard)
{
	DASHBOARD_GADGETS curgadget;

	if (!dashboard)
		return;
	
	DisplaySpriteFront(dashboard->dashboardsprite, dashboard->dashboardloc.x, dashboard->dashboardloc.y);

	for (curgadget=DASHBOARD_START; curgadget!=DASHBOARD_LAST; curgadget=(DASHBOARD_GADGETS)(((int)curgadget)+1))
		if (dashboard->dashboard_gadgets[curgadget])
			if (dashboard->chunksActive[dashboard->dashboard_gadgets[curgadget]->chunk])
				Gadget_DrawFront(dashboard->dashboard_gadgets[curgadget]);

}


///========================================================================
//	Function:		Dashboard_Update()
//
//	Description:
//		called every frame to do any necessary updating
//
//	Input:			none
//
//	Ouput:			none		
//
///========================================================================
void Dashboard_Update(void)
{
	GADGET_TEXTBOX *curtextbox;
	GADGET_2WAYBUTTON *cur2waybutton;
	GADGET_MULTIBUTTON *curmultibutton;
	GADGET_BUTTON *curbutton;

	int i;
	AI_COMP*	pComposition=NULL;

	if (!curdashboard)
		return;

	if (Armies[ARMY_PLAYER].Status == 0) return; // cannot update a dead army


#if 0
	//scroll the chat window if necessary
	if (gpGame->dwAnimTime-chatscrollcounter>CHATSCROLLTIME)
		receivechatmessage(" ");
#endif

	
	//update the currently selected unit info
	if (curdashboard->dashboard_gadgets[DASHBOARD_UNITINFO])
	{
		curtextbox=(GADGET_TEXTBOX*)curdashboard->dashboard_gadgets[DASHBOARD_UNITINFO]->pGadget;
		if (curselectedunit)
		{
			sprintf(curtextbox->boxtext[0], "%s", ItemName( (ITEM *)curselectedunit ));
		}
		else
		{
			sprintf(curtextbox->boxtext[0], "No unit");
		}
	}
 
	//update the ammo display
	if (curdashboard->dashboard_gadgets[DASHBOARD_AMMODISPLAY])
	{
		curtextbox=(GADGET_TEXTBOX*)curdashboard->dashboard_gadgets[DASHBOARD_AMMODISPLAY]->pGadget;
		i = GetSargeAmmo(SARGE_WEAPON_SECONDARY);
		if( i > 0 )
			sprintf(curtextbox->boxtext[0], "%d", i % 100);
		else
			sprintf(curtextbox->boxtext[0], "" );
		i = GetSargeAmmo(SARGE_WEAPON_SPECIAL);
		if( i > 0 )
			sprintf(curtextbox->boxtext[1], "%d", i % 100);
		else
			sprintf(curtextbox->boxtext[1], "" );
	}

	//change the main weapon icon

	if (curdashboard->dashboard_gadgets[DASHBOARD_WEAPONICON])
	{
		curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[DASHBOARD_WEAPONICON]->pGadget;

		curmultibutton->curpicture=GetSargeWeapon(SARGE_WEAPON_SECONDARY);	
	}

	//change the secondary item icon

	if (curdashboard->dashboard_gadgets[DASHBOARD_ITEMICON])
	{
		curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[DASHBOARD_ITEMICON]->pGadget;

		curmultibutton->curpicture=GetSargeWeapon(SARGE_WEAPON_SPECIAL);
	}



	//set the weapon select cursor
	{
		int sargeweapon=SargeGetActiveWeapon(ARMY_PLAYER);
		int isitready=IsSargeWeaponReady();

		switch(GetSargeVehicle())
		{
		case ARMY_NO_VEHICLE: 
			break;
		default:
			VEHICLE *pVehicle;
			pVehicle = SargePointer(ARMY_PLAYER)->pVehicle;
			if( pVehicle && (pVehicle->common.pWeapon) )
			{
				if( pVehicle->common.pWeapon->eWeapon == ARMY_NO_WEAPON )
					sargeweapon = -1;				// no weapon!
			}
		}

		for (i=0;i<3;i++)
			if (curdashboard->dashboard_gadgets[weaponselected[i]])
			{
				curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[weaponselected[i]]->pGadget;
				if (sargeweapon==i)
					if (isitready)
						curmultibutton->curpicture=2;
					else
						curmultibutton->curpicture=1;
				else 
					curmultibutton->curpicture=0;
			}
	}



	//Set Sarge Health
	{
		int cursargehealth=GetSargeHealthPercentage();
		for (i=0;i<8;i++)
			if (curdashboard->dashboard_gadgets[sargehealth[i]])
			{
				cur2waybutton=(GADGET_2WAYBUTTON*)curdashboard->dashboard_gadgets[sargehealth[i]]->pGadget;
				cur2waybutton->curstatus=(cursargehealth>=damagelevels[i]);
			}
	}

	//Set Vehicle Health
	{
		int curvehiclehealth=GetVehicleHealthPercentage();
		for (i=0;i<8;i++)
			if (curdashboard->dashboard_gadgets[vehiclehealth[i]])
			{
				cur2waybutton=(GADGET_2WAYBUTTON*)curdashboard->dashboard_gadgets[vehiclehealth[i]]->pGadget;
				cur2waybutton->curstatus=(curvehiclehealth>=damagelevels[i]);
			}
	}

    #ifdef JUNK //deleting trooper health bar
	//Set Trooper Info
  	for (i=0;i<7;i++)
		if (curdashboard->dashboard_gadgets[trooperinfo[i]])
		{
			curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[trooperinfo[i]]->pGadget;
			curmultibutton->curpicture=(int)UnitGetTrooperStatus(curselectedunit, i+1);
		}

    #endif

	//Set Airdrop Count
	{
		int curairdropcount=GetNumAirDrops();
		for (i=0;i<3;i++)
			if (curdashboard->dashboard_gadgets[airdrop[i]])
			{
				cur2waybutton=(GADGET_2WAYBUTTON*)curdashboard->dashboard_gadgets[airdrop[i]]->pGadget;
				cur2waybutton->curstatus=(curairdropcount>i);
			}
	}

	//Set Airstrike Count
	{
		int curairstrikecount=GetNumAirStrikes();
		for (i=0;i<3;i++)
			if (curdashboard->dashboard_gadgets[airstrike[i]])
			{
				cur2waybutton=(GADGET_2WAYBUTTON*)curdashboard->dashboard_gadgets[airstrike[i]]->pGadget;
				cur2waybutton->curstatus=(curairstrikecount>i);
			}
	}

	//Set Recon Count
	{
		int curreconcount=GetNumRecons();
		for (i=0;i<3;i++)
			if (curdashboard->dashboard_gadgets[recon[i]])
			{
				cur2waybutton=(GADGET_2WAYBUTTON*)curdashboard->dashboard_gadgets[recon[i]]->pGadget;
				cur2waybutton->curstatus=(curreconcount>i);
			}
	}

	//Set Vehicle Icon
	if (curdashboard->dashboard_gadgets[DASHBOARD_VEHICLEICON])
	{
		curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[DASHBOARD_VEHICLEICON]->pGadget;

		curmultibutton->curpicture=GetSargeVehicle();
	}

	//set the vehicle ammo icon
	if (curdashboard->dashboard_gadgets[DASHBOARD_VEHICLEAMMOICON])
	{
		curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[DASHBOARD_VEHICLEAMMOICON]->pGadget;
		switch(GetSargeVehicle())
		{
		case ARMY_NO_VEHICLE: 
			switch (GetSargeWeapon(0))
			{
			case ARMY_AUTORIFLE:
				curmultibutton->curpicture=2;
				break;
			case ARMY_NO_WEAPON:
				curmultibutton->curpicture=0;
				break;
			default:
				curmultibutton->curpicture=1;
			}
			break;
		default:
			VEHICLE *pVehicle;

			pVehicle = SargePointer(ARMY_PLAYER)->pVehicle;
			if( pVehicle && pVehicle->common.pWeapon )
			{
				switch( pVehicle->common.pWeapon->eWeapon )
				{
				case ARMY_LARGE_CANNON:
					curmultibutton->curpicture=3;
					break;
				case ARMY_MEDIUM_MACHINE_GUN:
				case ARMY_HEAVY_MACHINE_GUN:
					curmultibutton->curpicture=4;
					break;
				default:
					curmultibutton->curpicture=0;
				}
			}
			else
				curmultibutton->curpicture=0;
		}
	}

	//set the vehicle ammo amount
	if (curdashboard->dashboard_gadgets[DASHBOARD_VEHICLEAMMODISPLAY])
	{
		curtextbox=(GADGET_TEXTBOX*)curdashboard->dashboard_gadgets[DASHBOARD_VEHICLEAMMODISPLAY]->pGadget;

		SARGE*	pSarge = SargePointer(ARMY_PLAYER);

		if (pSarge->pVehicle && 
			pSarge->pVehicle->common.pWeapon &&
			pSarge->pVehicle->common.pWeapon->eWeapon != ARMY_NO_WEAPON )	
		{
			i = GetItemCurrentAmmo((ITEM*)(pSarge->pVehicle));
			if( i >= 0 )
				sprintf(curtextbox->boxtext[0], "%d", i );
			else
				sprintf(curtextbox->boxtext[0], "");
		}
		else
			sprintf(curtextbox->boxtext[0], "");
	}
	

	//Set the multiplayer stratego-mode item select icons
	for (i=0;i<18;i++)
		if (curdashboard->dashboard_gadgets[itemselect[i]])
		{
			curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[itemselect[i]]->pGadget;
			if (UndeployedItems[i])
			{
				//need to seriously flesh out later

				curmultibutton->curpicture=getSelectedItemType(UndeployedItems[i]);
			}
			else
				curmultibutton->curpicture=ITEMSELECTTYPE_NONE;
		}

	//Set the player start lights
	for (i=0;i<3;i++)
		if (curdashboard->dashboard_gadgets[startlights[i]])
		{
			curbutton=(GADGET_BUTTON*)curdashboard->dashboard_gadgets[startlights[i]]->pGadget;
			if (gpComm->m_ArmyReady[i+1])
				curbutton->curdelay=10;
			else
				curbutton->curdelay=0;
		}

	//update the special item item
	if (curdashboard->dashboard_gadgets[DASHBOARD_SPECIALITEM])
	{
		curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[DASHBOARD_SPECIALITEM]->pGadget;

		curmultibutton->curpicture=GetSargeQuestItem();
		if( curmultibutton->curpicture >= 30 )
			curmultibutton->curpicture = 0;
	}

}


///========================================================================
//	Function:		Dashboard_Click()
//
//	Description:
//		Handles a mouse click over a dashboard
//
//	Input:			dashboard			pointer to the dashboard
//					clickloc			where the click occurred
//					whichmousebutton	0=left 1=right
//
//	Ouput:			none		
//
///========================================================================

void Dashboard_Click(DASHBOARD *dashboard, CPoint *clickloc, int whichmousebutton)
{
	int whichonscreenbutton=-1;
	int cursubdivision=0;
	int i;


	for (i=0;i<dashboard->numbuttons;i++)
		if ((dashboard->buttons[i].screenrect.left<=clickloc->x) &&
			(dashboard->buttons[i].screenrect.right>clickloc->x) &&
			(dashboard->buttons[i].screenrect.top<=clickloc->y) &&
			(dashboard->buttons[i].screenrect.bottom>clickloc->y))
			{
				whichonscreenbutton=i;

				if (dashboard->buttons[whichonscreenbutton].subdivisionwidth)
					cursubdivision=(clickloc->y-dashboard->buttons[whichonscreenbutton].screenrect.top)/dashboard->buttons[whichonscreenbutton].subdivisionwidth;

				if (!dashboard->buttons[whichonscreenbutton].pGadget)
					break;

				if (dashboard->chunksActive[dashboard->buttons[whichonscreenbutton].pGadget->chunk])
				{
					Gadget_Press_Button(&dashboard->buttons[whichonscreenbutton], whichmousebutton, cursubdivision);
					return;
				}
			}
}

void FlipTrafficable(SPOINT pt);

extern int shiftTrafficable;

BOOL BruceLButtonDn(CPoint point)
{
    if (shiftTrafficable == 0) return 0; // nothing special
    if (point.y >= 384) return 0; // not on playfield
    SPOINT spt;
    spt.x = point.x + the_map.PixelBox.x;
    spt.y = point.y + the_map.PixelBox.y;
    FlipTrafficable(spt);
    return TRUE;
}

void InGameLButtonDn(UINT nFlags, CPoint point)
{
	if (gpGame->IsPaused())
		return;

    if (BruceLButtonDn(point))
		return;

	if (gpGame->game_substate == PLAY_SUB_STATE && UI_CurMode == UIMODE_LOOKINGATSARGE)
		return;

	if ( gpGame->nPauseDelay )
	{
		TRACE("InGameLButtonDn and gpGame->nPauseDelay\n");
		return;
	}


	UI_EndChat();
	MouseDown0 = FALSE;

	if ((!curdashboard) || (point.y<curdashboard->topborder))
	{
		SargeEndTalk();
		UI_GiveOrder(TRUE);
	}
	else
	{
		POINT pt;

		pt.x=point.x;
		pt.y=point.y;
		SPOINT wpt;

		if (SM_ProcessMouse(curstratmap, &pt, &wpt) == 0)	//click was on stratmap
		{
			if ((UI_CurMode==UIMODE_SCROLLING) || (UI_CurMode==UIMODE_PLACINGITEM))
				MapJumpToPoint(wpt.x, wpt.y);
		}
		else if (UI_CurMode==UIMODE_PLACINGITEM)
		{
			int i;

			i=0;
			while (UndeployedItems[i])
				i++;

			UndeployedItems[i]=CurSelectedUndeployedItem;
			CurSelectedUndeployedItem=NULL;
			UI_SwitchMode();
		}
		else
			Dashboard_Click(curdashboard, &point, 0);
	}
}


void PlacingItem()
{
	CPoint point;

	point.x = CursorPos.x;
	point.y = CursorPos.y;

	if ((!curdashboard) || (point.y<curdashboard->topborder))
	{
		SargeEndTalk();
		UI_GiveOrder(TRUE);
	}
	else
	{
		POINT pt;
		SPOINT wpt;

		pt.x=point.x;
		pt.y=point.y;

		if (SM_ProcessMouse(curstratmap, &pt, &wpt) == 0)	//click was on stratmap
		{
			if ((UI_CurMode==UIMODE_SCROLLING) || (UI_CurMode==UIMODE_PLACINGITEM))
				MapJumpToPoint(wpt.x, wpt.y);
		}
		else if (UI_CurMode==UIMODE_PLACINGITEM)
		{
			int i;

			i=0;
			while (UndeployedItems[i])
				i++;

			UndeployedItems[i]=CurSelectedUndeployedItem;
			CurSelectedUndeployedItem=NULL;
			UI_SwitchMode();
		}
		else
			Dashboard_Click(curdashboard, &point, 0);
	}
}


void InGameLButtonUp(UINT nFlags, CPoint point)
{
}


	//tell the unit to attack wherever it already is
void UI_GiveAttackOrderLocal(void)
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	if (curselectedunit)
		UnitOrders(curselectedunit, UNIT_ATTACK, curselectedunit->common.position, 0, NORMAL_SPEED);
}

void UI_GiveDefendOrderLocal(void)
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	if (curselectedunit)
		UnitOrders(curselectedunit, UNIT_DEFEND, curselectedunit->common.position, 0, NORMAL_SPEED);
}


void UI_GiveAttackOrder(void)
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	SPOINT spt;

	if (curselectedunit)
	{
		spt.x=(short)CursorPos.x;
		spt.y=(short)CursorPos.y;

		ScreenToWorld(&spt);

		UnitOrders(curselectedunit, UNIT_ATTACK, spt, NULL, (GetKeyState(VK_SHIFT)<0) ? FAST_SPEED : NORMAL_SPEED);
	}
}

void UI_GiveDefendOrder(void)
{
	SPOINT spt;
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;


	if (curselectedunit)
	{
		spt.x=(short)CursorPos.x;
		spt.y=(short)CursorPos.y;

		ScreenToWorld(&spt);

		UnitOrders(curselectedunit, UNIT_DEFEND,spt, NULL, (GetKeyState(VK_SHIFT)<0) ? FAST_SPEED : NORMAL_SPEED);
	}
}

void UI_GiveFollowOrder(void)
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	if (curselectedunit)
	{
		UnitOrders(curselectedunit, UNIT_FOLLOW, OFF_THE_MAP, NULL, (GetKeyState(VK_SHIFT)<0) ? FAST_SPEED : NORMAL_SPEED);
//		MsgBroadcastWithText( FOLLOW_ME );
	}
}

void UI_HitAttackKey(BOOL immediate)
{
	SARGE *pSarge;
	static attack_color[] = {GREEN_SQUAD_ATTACK, TAN_SQUAD_ATTACK, BLUE_SQUAD_ATTACK, GREY_SQUAD_ATTACK};
	static attack_color2[] = {GREEN_ATTACK, TAN_ATTACK, BLUE_ATTACK, GREY_ATTACK};

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	if (immediate)	{
		UI_GiveAttackOrderLocal();
		return;
	}

	int color = gpComm->ColorFromIndex(ARMY_PLAYER);
	if (rand() % 2)
		MsgBroadcastWithText( attack_color[color] );
	else
		MsgBroadcastWithText( attack_color2[color] );

	switch(UI_CurMode)
	{
	case UIMODE_LOOKINGATSARGE:
		SargeTalk();
		UI_SwitchMode();

		//FALL THROUGH

	case UIMODE_SCROLLING:
		UI_SetCursor(CURSORTYPE_ATTACK);
		break;
	}
}


void UI_HitDefendKey(BOOL immediate)
{
	SARGE *pSarge;
	static defend_color[] = {GREEN_SQUAD_DEFEND, TAN_SQUAD_DEFEND, BLUE_SQUAD_DEFEND, GREY_SQUAD_DEFEND};
	static defend_color2[] = {GREEN_DEFEND, TAN_DEFEND, BLUE_DEFEND, GREY_DEFEND};

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	if (immediate)	{
		UI_GiveDefendOrderLocal();
		return;
	}

	int color = gpComm->ColorFromIndex(ARMY_PLAYER);
	if (rand() % 2)
		MsgBroadcastWithText( defend_color[color] );
	else
		MsgBroadcastWithText( defend_color2[color] );

	switch(UI_CurMode)
	{
	case UIMODE_LOOKINGATSARGE:
		SargeTalk();
		UI_SwitchMode();

		//FALL THROUGH

	case UIMODE_SCROLLING:
		UI_SetCursor(CURSORTYPE_DEFEND);
		break;
	}
}

void UI_HitFollowKey(void)
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	switch(UI_CurMode)
	{
	case UIMODE_LOOKINGATSARGE:
//		UI_SwitchMode();

		//FALL THROUGH

	case UIMODE_SCROLLING:
		UI_GiveFollowOrder();
		break;
	}
}

void UI_HitAirDropKey(void)
{
	SARGE *pSarge;
	int howmany = GetNumAirDrops();

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	if (howmany <= 0)
	{
		MsgBroadcastWithText( NOAIR );
		return;
	}

	if (rand() % 2)
		MsgBroadcastWithText( REQUEST_PARATROOPERS );
	else
		MsgBroadcastWithText( SEND_PARATROOPERS );

	switch(UI_CurMode)
	{
	case UIMODE_LOOKINGATSARGE:
		SargeTalk();
		UI_SwitchMode( 0 );

		//FALL THROUGH

	case UIMODE_SCROLLING:
//		UI_SetCursor(GetNumAirDrops()>0 ? CURSORTYPE_AIRSUPPORT : CURSORTYPE_SCROLLING);
		UI_SetCursor(CURSORTYPE_AIRSUPPORT);
		break;
	}

}

void UI_HitAirStrikeKey(void)
{
	SARGE *pSarge;
	int howmany = GetNumAirStrikes();

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	if (howmany <= 0)
	{
		MsgBroadcastWithText( NOAIR );
		return;
	}

	if (rand() % 2)
		MsgBroadcastWithText( REQUEST_AIR_STRIKE );
	else
		MsgBroadcastWithText( NEED_AIR_STRIKE );

	switch(UI_CurMode)
	{
	case UIMODE_LOOKINGATSARGE:
		SargeTalk();
		UI_SwitchMode( 0 );

		//FALL THROUGH

	case UIMODE_SCROLLING:
//		UI_SetCursor(GetNumAirStrikes()>0 ? CURSORTYPE_AIRSTRIKE : CURSORTYPE_SCROLLING);
		UI_SetCursor(CURSORTYPE_AIRSTRIKE);
		break;
	}

}

void UI_HitReconKey(void)
{
	SPOINT spt;
	int result;
	SARGE *pSarge;
	int howmany = GetNumRecons();

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	if (howmany <= 0)
	{
		MsgBroadcastWithText( NOAIR );
		return;
	}
	
	spt.x = (short)CursorPos.x;
	spt.y = (short)CursorPos.y;
	ScreenToWorld( &spt );
	result = DoAirSupport(AIRSUPPORT_RECON, spt, ARMY_PLAYER);
    if( result == AIRSUPPORT_INVALID_AAGUNS )
		MsgBroadcastWithText( AAGUNS );
	else if (rand() % 2)
		MsgBroadcastWithText( REQUEST_RECON );
	else
		MsgBroadcastWithText( SEND_RECON );
}


//this function is called when the TAB key is hit
void UI_NextUnitKey(void)
{
	SelectNextUnit();
	if (UI_CurMode == UIMODE_SCROLLING)
	{
		if (curselectedunit)
		{
			MapUndoScrolling();
			MapJumpToPoint(curselectedunit->common.position.x, curselectedunit->common.position.y);
		}
	}
}


void UI_EnterKey(void)
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	switch (UI_CurMode)	{
		case UIMODE_SCROLLING:
			SargeEndTalk();
			UI_SwitchMode(0);
			break;

		case UIMODE_LOOKINGATSARGE:
			SargeTalk();
			UI_SwitchMode(0);
			break;
	}
}

int UI_nextMode;

void UI_ChatKey(void)
{
	SargeTalk();
	turnonkeys(0, 0, NULL);

	if ( gpGame->GetSubState() == PLAY_SUB_STATE) {
		UI_nextMode = UI_CurMode;
		if (UI_CurMode == UIMODE_LOOKINGATSARGE)
			UI_SwitchMode();
	}
}

static void UI_EndChat(void)
{
	if (turnoffkeys())	{
		SargeEndTalk();

		if ( gpGame->GetSubState() == PLAY_SUB_STATE) {
			if (UI_nextMode == UIMODE_LOOKINGATSARGE)
				UI_SwitchMode();
		}
	}
}


//this function is called to activate the currently selected order (typically because RETURN was hit)
void UI_GiveOrder(BOOL terminate)
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( !pSarge->common.nStrength )
		return;

	if (UI_CurMode == UIMODE_SCROLLING)
	{
		switch (UI_CurCursorType)
		{
		case CURSORTYPE_SCROLLING:
			if (terminate)
				endScrollingMode();
			break;

		case CURSORTYPE_ATTACK:
			UI_GiveAttackOrder();
			if (terminate)
				endScrollingMode();
			break;

		case CURSORTYPE_DEFEND:
			UI_GiveDefendOrder();
			if (terminate)
				endScrollingMode();
			break;

		case CURSORTYPE_FOLLOW:
			ASSERT(0);
			break;

		case CURSORTYPE_AIRSTRIKE:
			{
				SPOINT spt;
				int result;
				spt.x=(short)CursorPos.x;
				spt.y=(short)CursorPos.y;
				ScreenToWorld(&spt);
				result=DoAirSupport(AIRSUPPORT_AIRSTRIKE, spt,ARMY_PLAYER);

				if (result>0)
				{
					if (terminate)
					{
						AirSupportRubberband = 5000;
//						endScrollingMode();
						UI_SetCursor(CURSORTYPE_INVISIBLE);
					}
					else
						UI_SetCursor(CURSORTYPE_SCROLLING);
				}
				else if (result==AIRSUPPORT_INVALID_AAGUNS)
					MsgBroadcastWithText( AAGUNS );
			}
			break;

		case CURSORTYPE_AIRSUPPORT:
			{
				SPOINT spt;
				int result;
				spt.x=(short)CursorPos.x;
				spt.y=(short)CursorPos.y;
				ScreenToWorld(&spt);
				result=DoAirSupport(AIRSUPPORT_AIRDROP, spt,ARMY_PLAYER);

				if (result>0)
				{
					if (terminate)
					{
						AirSupportRubberband = 7500;
//						endScrollingMode();
						UI_SetCursor(CURSORTYPE_INVISIBLE);
					}
					else
						UI_SetCursor(CURSORTYPE_SCROLLING);
				}
				else if (result==AIRSUPPORT_INVALID_AAGUNS)
				{
					MsgBroadcastWithText( AAGUNS );
				}
			}
			break;

		case CURSORTYPE_RECON:
			ASSERT(0);
			break;

		}

	}
	else if (UI_CurMode==UIMODE_PLACINGITEM)
	{
		SPOINT spt;

		spt.x=(short)CursorPos.x;
		spt.y=(short)CursorPos.y;

		ScreenToWorld(&spt);

		if (!CurSelectedUndeployedItem || ItemDeploy(CurSelectedUndeployedItem, &spt)<0)
		{
			//unable to deploy item
		}
		else
		{
			CurSelectedUndeployedItem=NULL;
			UI_SwitchMode();
		}
	}

}

void InGameRButtonDn(UINT nFlags, CPoint point)
{
	POINT pt;
	SPOINT wpt;

	UI_EndChat();

    if (AlexRButtonDn( nFlags, point )) return;

	if (UI_CurMode==UIMODE_LOOKINGATSARGE)	
	{
		if (! UseAltMouseButton)
			Kbd_Sarge_ChgWeapon(0,0);
	}
	else if ((!curdashboard) || (point.y<curdashboard->topborder))
	{
		UI_GiveOrder(FALSE);
		MouseDown1 = FALSE;
	}
	else
	{
		pt.x=point.x;
		pt.y=point.y;

		if (UI_CurMode!=UIMODE_PLACINGITEM && SM_ProcessMouse(curstratmap, &pt, &wpt)<0)
			Dashboard_Click(curdashboard, &point, 0);
		MouseDown1 = FALSE;
	}
}

void InGameRButtonUp(UINT nFlags, CPoint point)
{
}

///========================================================================
//	Function:		AllocateGenericTextbox()
//
//	Description:
//		Allocates memory for character strings for a GADGET_TEXTBOX
//		to use, including an initial table of pointers to the beginnings
//		of each line
//
//	Input:			numlines			number of lines of text
//					linelength			length of each line
//
//	Ouput:			NULL on error, or pointer to allocated block		
//
///========================================================================
void *AllocateGenericTextbox(int numlines, int linelength)
{
	char **tablepointer;
	char *textpointer;
	int i;

	if (!(tablepointer=(char**)malloc(sizeof(char)*numlines*(linelength+1)+sizeof(char*)*numlines)))
		return NULL;

	ZeroMemory(tablepointer, sizeof(char)*numlines*(linelength+1)+sizeof(char*)*numlines);
	
	textpointer=(char*)(tablepointer+numlines);
	
	for (i=0;i<numlines;i++)
		tablepointer[i]=&textpointer[i*(linelength+1)];

	return (void*) tablepointer;
}

///========================================================================
//	Function:		ReceiveDashMessage(char *message, ITEM *unit)
//
//	Description:
//		Takes a message from a squad and sticks it, along with all 
//		necessary support info, into the message-from-squad window
//
//	Input:			message				pointer to the message
//					unit				pointer to the unit from whom
//										the message came (if any)
//
//	Ouput:			none		
//
///========================================================================
void ReceiveDashMessage(char *msg, OBJECT *unit)
{
	GADGET_LIST *curlist;
	int i;
	int linesused=0;
	char *header=NULL;
	int breakpoint;
	char *oldlisttext[50];
	OBJECT **punit;
	char tempmessage[SQUADMESSAGE_MAXLENGTH+5];
	char *message_allocated;
	char *message;
	int len;


	if (!curdashboard)
		return;

	if (!msg)
		return;

	len = strlen(msg) + 1;
	message = message_allocated = (char*)malloc(len);
	if (!message_allocated)
		return;

	strcpy(message, msg);

	if (curdashboard->dashboard_gadgets[DASHBOARD_MESSAGEFROMSQUADWINDOW])
	{
		curlist=(GADGET_LIST*)curdashboard->dashboard_gadgets[DASHBOARD_MESSAGEFROMSQUADWINDOW]->pGadget;
		
		if ((message[0]>0) && (message[0]<32))
		{
			header=message;
			message=message+1;
		} //if there's a color-setting header, we treat it separately
		

		while (strlen(message))
		{
			if (linesused==curlist->displaysize)
			{
				TRACE("ERROR: a single squad message took up more than the entire window\n");
				return;
			}

			if (BmpTextWidth( message, BMPFONT_DASHCOMM, NULL) <= squadmessagepixelwidth)
			{
				if (header)
					sprintf(curlist->listtext[linesused], "%c%s", header[0], message);
				else
					sprintf(curlist->listtext[linesused], "%s", message);

				punit=(OBJECT**)(curlist->listtext[linesused]-(sizeof(void*)/sizeof(char)));
				*punit=unit;

				linesused++;
				message[0]=0;
			}
			else
			{
				breakpoint=SQUADMESSAGE_MAXLENGTH-1;
				if (breakpoint>(int)strlen(message))
					breakpoint=(int)strlen(message);

				memcpy(tempmessage, message, breakpoint);
				tempmessage[breakpoint]=0;

				while (BmpTextWidth(tempmessage, BMPFONT_DASHCOMM, NULL) > squadmessagepixelwidth)
					tempmessage[--breakpoint]=0;

				int save_breakpoint = breakpoint;

				while (breakpoint && (message[breakpoint]!=' '))
					breakpoint--;
				if (!breakpoint)
				{
					TRACE("ERROR: no breakpoint found in squad message\n");
					breakpoint = save_breakpoint;
//					return;
				}
				
				message[breakpoint]=0;
				
				if (header)
					sprintf(curlist->listtext[linesused], "%c%s", header[0], message);
				else
					sprintf(curlist->listtext[linesused], "%s", message);

				punit=(OBJECT**)(curlist->listtext[linesused]-(sizeof(void*)/sizeof(char)));
				*punit=unit;
				
				linesused++;
				message+=breakpoint+1;
			}
		}

		for (i=0;i<curlist->displaysize;i++)
			oldlisttext[i]=curlist->listtext[i];

		for (i=0;i<curlist->displaysize;i++)
			curlist->listtext[i]=oldlisttext[(i+linesused)%curlist->displaysize];
	}

	free(message_allocated);
}

///========================================================================
//	Function:		MissionMessageFormat(char *message)
//
//	Description:
//		display a mission message within a dithered or translucent box in the
//		playfield strategic map area.
//
//	Input:			message				pointer to the message
//
//	Ouput:			none		
//
///========================================================================
#define	MISSION_MAX_LINE_LEN	64

void MissionMessageFormat(RECT* pRect, char *message)
{
	char	messageBuffer[ MISSION_MAX_LINE_LEN ];
	char*	pNextChar;
	char	nEndOfWord;
	SBOX	textBox;
	SPOINT	screenPos;
	BOOL	bEndOfLine;
	BOOL	bDone;
	int		nNextChar;
	LONG	xMaxLen;

	if (!pRect)
		return;
	if (!message)
		return;

	// initialize the screen position of the text
	screenPos.x = (short)pRect->left;
	screenPos.y = (short)(pRect->top + 40);
	xMaxLen     = pRect->right - pRect->left;

	TextSetColors( RGB_RED, RGB_TRANSPARENT );

	// now start outputing the message
	bDone     = FALSE;
	pNextChar = message;
	while ( !bDone )
	{
		nEndOfWord = -1;
		nNextChar  = 0;
		bEndOfLine = FALSE;
		// copy text into the buffer until you get a word break or EOL
		while ( !bEndOfLine )
		{
			messageBuffer[ nNextChar ]   = *pNextChar;
			messageBuffer[ nNextChar+1 ] = '\0';
#ifdef SCREEN_DEBUG
TRACE( "messageBuffer (%s)\n", messageBuffer );
#endif
			switch( *pNextChar )
			{
			case ' ':	// remember this End Of Word location
			case '\n':	// remember this End Of Word location
				// check to see if the current line will still fit
				// into the display window
				textBox.x  = 0;
				textBox.y  = 0;
				if ( TextBox( messageBuffer, &textBox, FONT_CARGO_20 ) )
				{
					// error: failed to acquire text box size
					TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
							__FILE__, __LINE__ );
					return;
				}
				if ( textBox.cx > xMaxLen )
				{
					// reload the last character since we null'd it
//					messageBuffer[ nNextChar ] = *pNextChar;

					// back up to the last whole word
					if ( nEndOfWord < 0 )
						ASSERT(0);
					else
					{
						pNextChar -= (nNextChar-nEndOfWord);
						nNextChar  = nEndOfWord+1;
						messageBuffer[ nEndOfWord ] = '\0';
					}

					// now output this string to the window
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								messageBuffer, FONT_CARGO_20, NULL );

					// advance the position
					screenPos.y += textBox.cy + 8;
					bEndOfLine = TRUE;
				}
				else
				{
					messageBuffer[ nNextChar ] = ' ';
					nEndOfWord                 = nNextChar;
					++nNextChar;
					++pNextChar;
					messageBuffer[ nNextChar ] = '\0';
				}
				break;
			case '\0':	// remember this End Of Word location
				// check to see if the current line will still fit
				// into the display window
				messageBuffer[ nNextChar ] = '\0';
				textBox.x  = 0;
				textBox.y  = 0;
				if ( TextBox( messageBuffer, &textBox, FONT_CARGO_20 ) )
				{
					// error: failed to acquire text box size
					TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
							__FILE__, __LINE__ );
					return;
				}
				if ( textBox.cx > xMaxLen )
				{
					// back up to the last whole word
					messageBuffer[ nEndOfWord ] = '\0';

					pNextChar -= (nNextChar-nEndOfWord);
					nNextChar  = nEndOfWord+1;
					messageBuffer[ nEndOfWord ] = '\0';

					// now output this string to the window
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								messageBuffer, FONT_CARGO_20, NULL );

					// advance the position
					screenPos.y += textBox.cy + 8;

					// now output this remainder of the string
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								&(messageBuffer[nNextChar]), FONT_CARGO_20, NULL );
					// advance the position
					screenPos.y += textBox.cy + 8;
				}
				else
				{
//					nEndOfWord = nNextChar;
					nEndOfWord = 0;
					++nNextChar;
					++pNextChar;
					messageBuffer[ nNextChar ] = '\0';

						// now output this string to the window
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								messageBuffer, FONT_CARGO_20, NULL );

					// advance the position
					screenPos.y += textBox.cy + 8;
				}
				bEndOfLine = TRUE;
				bDone      = TRUE;
				break;
			default:
				if ( nNextChar >= MISSION_MAX_LINE_LEN )
				{
					// back up to the last whole word
					if ( nEndOfWord != -1 )
					{
						messageBuffer[ nEndOfWord ] = '\0';

						// back up the source pointer
						pNextChar -= (nNextChar-nEndOfWord);
						nNextChar  = nEndOfWord+1;
						messageBuffer[ nNextChar ] = *pNextChar;
						++nNextChar;
						messageBuffer[ nNextChar ] = '\0';
					}
					else
					{
						// back up until the string fits
						nEndOfWord = 0;
						while ( nNextChar && !nEndOfWord )
						{
							--nNextChar;
							if ( nNextChar )
							{
								--pNextChar;
								messageBuffer[ nNextChar ] = '\0';
								if ( TextBox( messageBuffer, &textBox, FONT_CARGO_20 ) )
								{
									// error: failed to acquire text box size
									TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
											__FILE__, __LINE__ );
									return;
								}
								if ( textBox.cx < xMaxLen )
								{
									// good enough
									nEndOfWord = nNextChar;
								}
							}
						}
					}

					if ( TextBox( messageBuffer, &textBox, FONT_CARGO_20 ) )
					{
						// error: failed to acquire text box size
						TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
								__FILE__, __LINE__ );
						return;
					}

					// now output this string to the window
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								messageBuffer, FONT_CARGO_20, NULL );

					// advance the position
					screenPos.y += textBox.cy + 8;
					bEndOfLine   = TRUE;
				}
				else
				{
					// go on to the next character
					++nNextChar;
					++pNextChar;
					messageBuffer[ nNextChar ] = '\0';
				}
				break;
			}
		}
	}

}

///========================================================================
//	Function:		PresentMissionMessage(char *message)
//
//	Description:
//		display a mission message within a dithered or translucent box in the
//		playfield strategic map area.
//
//	Input:			message				pointer to the message
//
//	Ouput:			none		
//
///========================================================================
void PresentMissionMessage(char *message)
{
	char*	pMissionMessage;
	RECT	rcMissionMessage;
	int		len;

	if (!message)
		return;

	// copy the mission message so we can manipulate the formatting
	len = strlen( message );
	if ( !len )
		return;

	pMissionMessage = (char*)malloc( len+1 );
	if ( !pMissionMessage )
		return;

	strcpy( pMissionMessage, message );

	// now reformat the message to fit into the mission message display area
	rcMissionMessage.left   = gBoxMissionMessage.x;
	rcMissionMessage.top    = gBoxMissionMessage.y;
	rcMissionMessage.right  = rcMissionMessage.left + gBoxMissionMessage.cx;
	rcMissionMessage.bottom = rcMissionMessage.top  + gBoxMissionMessage.cy;
	gMissionShadeTable = CreateShadeTable( 192,192,192 );
	FillTransRectFront( &rcMissionMessage, gMissionShadeTable );

	// format the message text to fit in window
	rcMissionMessage.left   += 8;
	rcMissionMessage.top    += 8;
	rcMissionMessage.right  -= 8;
	rcMissionMessage.bottom -= 8;
	MissionMessageFormat( &rcMissionMessage, pMissionMessage );

	// free up the message now that we're done with it
	free( pMissionMessage );
	pMissionMessage = NULL;
}

///========================================================================
//	Function:		MissionLoading(char *message)
//
//	Description:
//		draw the mission loading bar
//
//	Input:			nBytesRead			number of bytes read thus far
//					nTotalBytes			total number of bytes to read
//
//	Ouput:			none		
//
///========================================================================

RECT	MissionLoadingRect = { 5, 463, 634, 474 };

void MissionLoading( long nBytesRead, long nTotalBytes )
{
	RECT	rcLoading;
	float	percentage;
	float	delta;
	long	width;

	// calculate the percentage loaded and the delta load marker width
	delta      = 0;
	percentage = (float)((float)nBytesRead/(float)nTotalBytes);
	if ( percentage )
		delta = (float)((float)(MissionLoadingRect.right - MissionLoadingRect.left)*percentage);

#ifdef	SCREEN_DEBUG
TRACE( "Loading: (%ld,%ld:%f:%f)\n",nTotalBytes,nBytesRead,percentage,delta);
#endif

	// first draw the area rectangle
	// FillRectFront( &MissionLoadingRect, RGB_WHITE );

	// now figure out the amount loaded thus far rectangle
	if ( percentage && delta )
	{
		width            = (long)delta;
		rcLoading.left   = MissionLoadingRect.left;
		rcLoading.top    = MissionLoadingRect.top;
		rcLoading.right  = MissionLoadingRect.left + width;
		rcLoading.bottom = MissionLoadingRect.bottom;

		// draw the bytes read thus far bar
		FillRectFront( &rcLoading, RGB_GREEN );
	}
}


char *testtext[]=
{
	"#pThis is test",
	"text to see if",
	"lists and textboxes",
	"are working...",
	"dah dah dah",
	"I could go on",
	"all day like",
	"this. But I",
	"won't"
};




#define CURSORON 5 //how many frames the cursor is on
#define CURSOROFF 10 //total length of the cursor cycle
#define CURSORSPACING 2 //pixels between end of string and cursor
#define CURSORRATIO 0.5 //number to multiply cursor height by to get cusor width
#define CURSORTOPSPACING 2 //pixels to move downward from the top of the text

void resetcursor(void *pList)
{
	CURSOR_INFO *cursorinfo;
	cursorinfo=(((GADGET_LIST*)pList)->cursordata);
	if (cursorinfo)
		cursorinfo->cursorrect.right=0;
}
	

void drawcursor(void *pList)
{
/*
	CURSOR_INFO *cursorinfo;

	if (curdashboard->capturingkeys)
	{
		cursorinfo=((GADGET_LIST*)pList)->cursordata;
		if (cursorinfo->counter++<CURSORON)
		{
			int len;
			
			len = BmpTextWidth( *((GADGET_LIST*)pList)->listtext, BMPFONT_DASHCOMM, NULL );
			if ((curdashboard->texthasarrived) || (cursorinfo->cursorrect.right==0)) //we need to recalculate the cursor position
			{
				curdashboard->texthasarrived=FALSE;
				cursorinfo->cursorrect.top=((GADGET_LIST*)pList)->screenpos.y+CURSORTOPSPACING;
				cursorinfo->cursorrect.left=((GADGET_LIST*)pList)->screenpos.x+len+CURSORSPACING;  //+cursorinfo->cursorsize.cx
				cursorinfo->cursorrect.bottom=cursorinfo->cursorrect.top+((GADGET_LIST*)pList)->spacing;
				cursorinfo->cursorrect.right=cursorinfo->cursorrect.left+((GADGET_LIST*)pList)->spacing*CURSORRATIO;
			}
//				FillRect(&cursorinfo->cursorrect, 0xbbbbbbbb);

		}

		if (cursorinfo->counter==CURSOROFF) 
			cursorinfo->counter=0;
	}
*/
}


void receivechatmessage(char *message)
{


	ReceiveDashMessage(message, NULL);

#if 0

	CHAT_RECEIVE_STRUCT *chat_receive;
	char *targetstring;
	int i;


	if (!curdashboard)
		return;
	if (!curdashboard->dashboard_gadgets[DASHBOARD_RECEIVECHATWINDOW])
		return;

	chatscrollcounter=gpGame->dwAnimTime;

	if (strlen(message)>MESSAGE_COMP_MAXLENGTH)
	{
		TRACE("ERROR: chat message received that was just too damn long\n");
		return;
	}

	chat_receive=(CHAT_RECEIVE_STRUCT*)((GADGET_TEXTBOX*)curdashboard->dashboard_gadgets[DASHBOARD_RECEIVECHATWINDOW]->pGadget)->extradata;
	targetstring=chat_receive->pstrings[0];
	ZeroMemory(targetstring, (MESSAGE_COMP_MAXLENGTH+1)*sizeof(char));

	sprintf(targetstring, "%s", message);

	chat_receive->curtopstring=(chat_receive->curtopstring+1)%CHAT_MESSAGES_ONSCREEN;

	for (i=0;i<CHAT_MESSAGES_ONSCREEN;i++)
		chat_receive->pstrings[i]=&chat_receive->strings[(MESSAGE_COMP_MAXLENGTH+1)*((i+chat_receive->curtopstring)%CHAT_MESSAGES_ONSCREEN)];

#endif
}

void startbuttonfunc(int upordown, int whichmousebutton)
{
//	SendDashboardChat();
//	UI_EndChat();

	if (upordown==GADGET_2WAYBUTTON_PRESSED)
		SendGameReadyMsg(TRUE);
	else
	{
		if (curdashboard->dashboard_gadgets[DASHBOARD_START])
		{
			GADGET_2WAYBUTTON* cur2waybutton=(GADGET_2WAYBUTTON*)curdashboard->dashboard_gadgets[DASHBOARD_START]->pGadget;
			cur2waybutton->curstatus=GADGET_2WAYBUTTON_PRESSED;
		}
	}

	MouseDown0 = FALSE;
	gpGame->nPauseDelay = GetTickCount() + 250;

	MissionMusic( FALSE );
}

void changestartbuttontomissionbutton(void)
{

	if (curdashboard->dashboard_gadgets[DASHBOARD_START])
	{

		GADGET_MULTIBUTTON* curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[DASHBOARD_START]->pGadget;

		curmultibutton->curpicture=1;
	}
}


void selectsquadfrommessage(int listbutton, int mousebutton, void *extradata)
{
	char **listtext;
	char *curtext;
	OBJECT **curobj;
	
	listtext=(char**) extradata;
	curtext=listtext[listbutton];

	curobj=(OBJECT**)(curtext-(sizeof(void*)/sizeof(char)));

	if ((*curobj) && (ITEM_TYPE(*curobj)==ARMY_UNIT) && (ITEM_ARMY(*curobj)==ARMY_PLAYER))
		SetSelectedUnit((UNIT*)*curobj);
}


///========================================================================
//	Function:		ClearSelectedUnit()
//
//	Description:
//		Clears the selected unit to NULL
//
//	Input:			none
//
//	Ouput:			none	
//
///========================================================================
static void ClearSelectedUnit(void)
{
	curselectedunit=NULL;
}

///========================================================================
//	Function:		SetSelectedUnit()
//
//	Description:
//		Sets a particular unit as the currently selected unit
//
//	Input:			pUnit		pointer to the unit for the selected pin
//
//	Ouput:			none	
//
///========================================================================
static void SetSelectedUnit(UNIT *pUnit)
{
	if (!pUnit)
		ClearSelectedUnit();

	curselectedunit=pUnit;
}


void SelectNextUnit(void)
{
	UNIT *newunit;
	newunit = UnitGetNextFunctional(curselectedunit);
	if (newunit)
		SetSelectedUnit(newunit);
}


void selectweapon0(int whichbutton, int whichpicture)
{
	ActivateSargeWeapon(SargePointer(ARMY_PLAYER),0);
	clearFiringBar();
}

void selectweapon1(int whichbutton, int whichpicture)
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pVehicle )
	{
		ActivateSargeWeapon( pSarge, 1 );
		clearFiringBar();
	}
}

void selectweapon2(int whichbutton, int whichpicture)
{
	SARGE *pSarge;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pVehicle )
	{
		ActivateSargeWeapon( pSarge, 2 );
		clearFiringBar();
	}
}


void itemselectfunc(int whichbutton)
{
	if (UI_CurMode==UIMODE_PLACINGITEM)
	{
		ITEM *dummy;

		dummy=CurSelectedUndeployedItem;
		CurSelectedUndeployedItem=UndeployedItems[whichbutton];
		UndeployedItems[whichbutton]=dummy;

		if (CurSelectedUndeployedItem==NULL)
			UI_SwitchMode();
	}
	else
	{
		CurSelectedUndeployedItem=UndeployedItems[whichbutton];
		if (CurSelectedUndeployedItem)
			{
			UndeployedItems[whichbutton]=NULL;
			UI_EnterItemPlacingMode();
		}
	}
}

void itemselectfunc0(int whichbutton, int whichpicture)
{
	itemselectfunc(0);
}
void itemselectfunc1(int whichbutton, int whichpicture)
{
	itemselectfunc(1);
}
void itemselectfunc2(int whichbutton, int whichpicture)
{
	itemselectfunc(2);
}
void itemselectfunc3(int whichbutton, int whichpicture)
{
	itemselectfunc(3);
}
void itemselectfunc4(int whichbutton, int whichpicture)
{
	itemselectfunc(4);
}
void itemselectfunc5(int whichbutton, int whichpicture)
{
	itemselectfunc(5);
}
void itemselectfunc6(int whichbutton, int whichpicture)
{
	itemselectfunc(6);
}
void itemselectfunc7(int whichbutton, int whichpicture)
{
	itemselectfunc(7);
}
void itemselectfunc8(int whichbutton, int whichpicture)
{
	itemselectfunc(8);
}
void itemselectfunc9(int whichbutton, int whichpicture)
{
	itemselectfunc(9);
}
void itemselectfunc10(int whichbutton, int whichpicture)
{
	itemselectfunc(10);
}
void itemselectfunc11(int whichbutton, int whichpicture)
{
	itemselectfunc(11);
}
void itemselectfunc12(int whichbutton, int whichpicture)
{
	itemselectfunc(12);
}
void itemselectfunc13(int whichbutton, int whichpicture)
{
	itemselectfunc(13);
}
void itemselectfunc14(int whichbutton, int whichpicture)
{
	itemselectfunc(14);
}
void itemselectfunc15(int whichbutton, int whichpicture)
{
	itemselectfunc(15);
}
void itemselectfunc16(int whichbutton, int whichpicture)
{
	itemselectfunc(16);
}
void itemselectfunc17(int whichbutton, int whichpicture)
{
	itemselectfunc(17);
}

void clickspecialfunc(int whichbutton, int whichpicture)
{
	/*
	char *QuestMusings[5] =
	{
		"\032Curious...",
		"\032Hmm... I wonder.",
		"\032Funny...",
		"\032I almost have it all!",
		"\032Now to get rid of it..."
	};
	char tempstrbuf[40];

	strcpy( tempstrbuf, QuestMusings[whichpicture] );
	ReceiveDashMessage( tempstrbuf, NULL );
	*/
}


void chattoggle1func(int whichway, int whichbutton)
{
	if (whichway==GADGET_2WAYBUTTON_PRESSED)
		chatMask|=(1<<1);
	else
		chatMask&=~(1<<1);
}
void chattoggle2func(int whichway, int whichbutton)
{
	if (whichway==GADGET_2WAYBUTTON_PRESSED)
		chatMask|=(1<<2);
	else
		chatMask&=~(1<<2);
}
void chattoggle3func(int whichway, int whichbutton)
{
	if (whichway==GADGET_2WAYBUTTON_PRESSED)
		chatMask|=(1<<3);
	else
		chatMask&=~(1<<3);
}

void alliance1func(int whichway, int whichbutton)
{
	if (whichway==GADGET_2WAYBUTTON_PRESSED)
		ArmySetAlliance( ARMY_PLAYER, (ARMY_TYPE)1, TRUE);
	else
		ArmySetAlliance( ARMY_PLAYER, (ARMY_TYPE)1, FALSE);
}

void alliance2func(int whichway, int whichbutton)
{
	if (whichway==GADGET_2WAYBUTTON_PRESSED)
		ArmySetAlliance( ARMY_PLAYER, (ARMY_TYPE)2, TRUE);
	else
		ArmySetAlliance( ARMY_PLAYER, (ARMY_TYPE)2, FALSE);
}

void alliance3func(int whichway, int whichbutton)
{
	if (whichway==GADGET_2WAYBUTTON_PRESSED)
		ArmySetAlliance( ARMY_PLAYER, (ARMY_TYPE)3, TRUE);
	else
		ArmySetAlliance( ARMY_PLAYER, (ARMY_TYPE)3, FALSE);
}

void SetWait(int whichbutton)	{
	gpGame->nPauseDelay = -1;
	gpGame->m_DelayFunc = NULL;
}


///========================================================================
//	Function:		ScriptBmp
//	Description:	Display the bmp named
///========================================================================

void ScriptBmp(char *file)
{
	gpGame->PauseGame(PAUSE_LOCAL);
	SendGamePause(TRUE, PAUSE_LOCAL);

	VehicleSoundOff();

	// initialize the recall image
	RecallInit(file);

	bDisplayRecall = TRUE;
    
	// apply a UI pause
	gpGame->nPauseDelay = 50;
	gpGame->m_DelayFunc = SetWait;

	RecallState = RECALL_MISSION_STATE;
	pMainFrame->SetUI(&UI_RECALL);
	pMainFrame->SetUIOverride(KeyOverride_RECALL);
}


void UI_MissionRecall(int whichbutton)
{
	gpGame->PauseGame(PAUSE_LOCAL);
	SendGamePause(TRUE, PAUSE_LOCAL);

	// initialize the recall image
	RecallInit();

	bDisplayRecall = TRUE;
	bAudioRecall = TRUE;

	// apply a UI pause
	gpGame->nPauseDelay = 25;
	gpGame->m_DelayFunc = SetWait;

	RecallState = RECALL_MISSION_STATE;
	pMainFrame->SetUI(&UI_RECALL);
	pMainFrame->SetUIOverride(KeyOverride_RECALL);

//	if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
//		MsgMission();
}

void UI_MapRecall(int whichbutton)
{
	// prepare to present the mission statement???
	if (RecallSprite.pGraphic)
		FreeSprite( &RecallSprite );	//	LoadSprite();

	// initialize the recall image
	MapRecallInit();

	bDisplayRecall = TRUE;
    bDisplayPaperMap = TRUE;
	// apply a UI pause
	gpGame->nPauseDelay = 25;
	gpGame->m_DelayFunc = SetWait;

	RecallState = RECALL_MAP_STATE;
	pMainFrame->SetUI(&UI_RECALL);
	pMainFrame->SetUIOverride(KeyOverride_RECALL_MAP);
}


void releaserecalllfunc(int x,int y)
{
	if ( gpGame->IsPaused() & PAUSE_LOCAL )
	{
		gpGame->UnPauseGame( PAUSE_LOCAL );
		SendGamePause(FALSE, PAUSE_LOCAL);
	}

	if( gpGame->GetSubState() == PLAY_SETUP_SUB_STATE )
		pMainFrame->SetUI(&UI_GAME_SETUP_STATE);
	else
		pMainFrame->SetUI(&UI_GAME_PLAY_STATE);
	pMainFrame->SetUIOverride(NULL);

	gpGame->nPauseDelay = GetTickCount() + 100;
	MouseDown0 = FALSE;

//	MissionMusic( FALSE );

	if (RecallSprite.pGraphic)
		FreeSprite( &RecallSprite );


	if (x < 170) x = 0;
	if (x > (170 + 360)) x = 0;
	if (y < 12) y = 0;
	if (y > (12 + 360)) y = 0;
	if (bDisplayPaperMap && x && y && UI_CurMode==UIMODE_SCROLLING)
	{
		x -= 170;
		y -= 12;
		// scale position to full world from 360x360 map
		x = (x * (256*16)) / 360;
		y = (y * (256*16)) / 360;
		MapJumpToPoint(x, y);
	}

	bDisplayRecall = FALSE;
    bDisplayPaperMap = FALSE;

}

///========================================================================
//	Function:		DashboardInitFromAssembly()
//
//	Description:
//		Assembles a dashboard structure corresponding to an array of
//		DASHBOARD_ASSEMBLY_ELEMENTs. The dashboard assembled is 
//		always the global curdashboard
//		
//
//	Input:			assembly			pointer to the array
//
//	Ouput:			negative on error		
//
///========================================================================
int DashboardInitFromAssembly(DASHBOARD_ASSEMBLY_ELEMENT *assemblyarray)
{
	GADGET_BUTTON *curbutton;
	GADGET_MULTIBUTTON *curmultibutton;
	GADGET_2WAYBUTTON *cur2waybutton;
	GADGET_RADIOBUTTON *curradiobutton;
	GADGET_LIST *curlist;
	GADGET_TEXTBOX *curtextbox;
	int numonscreenbuttons=0;
	int i;

	ONSCREENBUTTON *curonscreenbutton;

	DASHBOARD_ASSEMBLY_ELEMENT *assembly;

	curdashboard=(DASHBOARD*)malloc(sizeof(DASHBOARD));
	ZeroMemory(curdashboard, sizeof(DASHBOARD));

	curdashboard->pcurmessage=curdashboard->curmessage;

	assembly=assemblyarray;

	while (assembly->whichtype!=GADGETTYPE_END)
	{
		
		switch (assembly->whichtype)
		{
		case GADGETTYPE_BUTTON:
			if (curdashboard->dashboard_gadgets[assembly->whichgadget]) //was already allocated
			{
				TRACE("ERROR: we appear to improperly have two dashboard assembly elements for gadget %d\n",assembly->whichgadget);
				return -1;
				break;
			}

			curdashboard->dashboard_gadgets[assembly->whichgadget]=(GADGET*)malloc(sizeof(GADGET));
			curdashboard->dashboard_gadgets[assembly->whichgadget]->type=GADGETTYPE_BUTTON;
			curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget=
				(void*)(curbutton=
				(GADGET_BUTTON*)malloc(sizeof(GADGET_BUTTON)));
			ZeroMemory(curbutton,sizeof(GADGET_BUTTON));

			curbutton->screenpos=assembly->onscreenloc;

			if (assembly->hotspot.right>0)
				numonscreenbuttons++;

			break;

		case GADGETTYPE_MULTIBUTTON:
			/*for multi buttons, aux1 and aux2 are the current button and how many buttons
			 */

			if (curdashboard->dashboard_gadgets[assembly->whichgadget])
			{
				TRACE("ERROR: Multiple definitions of the same dashboard MULTIBUTTON\n");
				return -1;
			}
			else
			{
				curdashboard->dashboard_gadgets[assembly->whichgadget]=(GADGET*)malloc(sizeof(GADGET));
				curdashboard->dashboard_gadgets[assembly->whichgadget]->type=GADGETTYPE_MULTIBUTTON;
				curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget=
					(void*)(curmultibutton=
					(GADGET_MULTIBUTTON*)malloc(sizeof(GADGET_MULTIBUTTON)));
				ZeroMemory(curmultibutton,sizeof(GADGET_MULTIBUTTON));

				curmultibutton->numpictures=assembly->aux1;

				curmultibutton->screenpos=assembly->onscreenloc;

				curmultibutton->sprites[0]=(SPRITE**)malloc(sizeof(SPRITE*)*curmultibutton->numpictures);
				ZeroMemory(curmultibutton->sprites[0], sizeof(SPRITE*)*curmultibutton->numpictures);

				curmultibutton->sprites[1]=(SPRITE**)malloc(sizeof(SPRITE*)*curmultibutton->numpictures);
				ZeroMemory(curmultibutton->sprites[1], sizeof(SPRITE*)*curmultibutton->numpictures);

				if (assembly->hotspot.right>0)
					numonscreenbuttons++;

				switch(assembly->whichgadget)
				{
		
					case DASHBOARD_ITEMSELECT_1:
						curmultibutton->func=itemselectfunc0;
						break;

					case DASHBOARD_ITEMSELECT_2:
						curmultibutton->func=itemselectfunc1;
						break;
				
					case DASHBOARD_ITEMSELECT_3:
						curmultibutton->func=itemselectfunc2;
						break;
				
					case DASHBOARD_ITEMSELECT_4:
						curmultibutton->func=itemselectfunc3;
						break;
				
					case DASHBOARD_ITEMSELECT_5:
						curmultibutton->func=itemselectfunc4;
						break;
				
					case DASHBOARD_ITEMSELECT_6:
						curmultibutton->func=itemselectfunc5;
						break;
				
					case DASHBOARD_ITEMSELECT_7:
						curmultibutton->func=itemselectfunc6;
						break;
				
					case DASHBOARD_ITEMSELECT_8:
						curmultibutton->func=itemselectfunc7;
						break;
				
					case DASHBOARD_ITEMSELECT_9:
						curmultibutton->func=itemselectfunc8;
						break;
				
					case DASHBOARD_ITEMSELECT_10:
						curmultibutton->func=itemselectfunc9;
						break;

					case DASHBOARD_ITEMSELECT_11:
						curmultibutton->func=itemselectfunc10;
						break;

					case DASHBOARD_ITEMSELECT_12:
						curmultibutton->func=itemselectfunc11;
						break;
				
					case DASHBOARD_ITEMSELECT_13:
						curmultibutton->func=itemselectfunc12;
						break;
				
					case DASHBOARD_ITEMSELECT_14:
						curmultibutton->func=itemselectfunc13;
						break;
				
					case DASHBOARD_ITEMSELECT_15:
						curmultibutton->func=itemselectfunc14;
						break;
				
					case DASHBOARD_ITEMSELECT_16:
						curmultibutton->func=itemselectfunc15;
						break;
				
					case DASHBOARD_ITEMSELECT_17:
						curmultibutton->func=itemselectfunc16;
						break;
				
					case DASHBOARD_ITEMSELECT_18:
						curmultibutton->func=itemselectfunc17;
						break;

				case DASHBOARD_WEAPONSELECTED_1:
						curmultibutton->func=selectweapon0;
						break;

				case DASHBOARD_WEAPONSELECTED_2:
						curmultibutton->func=selectweapon1;
						break;

				case DASHBOARD_WEAPONSELECTED_3:
						curmultibutton->func=selectweapon2;
						break;

				case DASHBOARD_SPECIALITEM:
					curmultibutton->func = clickspecialfunc;
					break;
				}

				//add code to set the function
			}

			break;
		case GADGETTYPE_2WAYBUTTON:
			if (curdashboard->dashboard_gadgets[assembly->whichgadget]) //was already allocated
			{
				TRACE("ERROR: we appear to improperly have two dashboard assembly elements for gadget %d\n",assembly->whichgadget);
				return -1;
				break;
			}

			curdashboard->dashboard_gadgets[assembly->whichgadget]=(GADGET*)malloc(sizeof(GADGET));
			curdashboard->dashboard_gadgets[assembly->whichgadget]->type=GADGETTYPE_2WAYBUTTON;
			curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget=
				(void*)(cur2waybutton=
				(GADGET_2WAYBUTTON*)malloc(sizeof(GADGET_2WAYBUTTON)));
			ZeroMemory(cur2waybutton,sizeof(GADGET_2WAYBUTTON));

			cur2waybutton->screenpos=assembly->onscreenloc;

			// do something to set the appropriate function

			switch (assembly->whichgadget)
			{
			case DASHBOARD_START:
				cur2waybutton->func=startbuttonfunc;
				break;


			case DASHBOARD_CHATTOGGLE_1:
				cur2waybutton->func=chattoggle1func;
				cur2waybutton->curstatus=1;
				break;

			case DASHBOARD_CHATTOGGLE_2:
				cur2waybutton->func=chattoggle2func;
				cur2waybutton->curstatus=1;
				break;

			case DASHBOARD_CHATTOGGLE_3:
				cur2waybutton->func=chattoggle3func;
				cur2waybutton->curstatus=1;
				break;

			case DASHBOARD_ALLIANCE_1:
				cur2waybutton->func=alliance1func;
				break;

			case DASHBOARD_ALLIANCE_2:
				cur2waybutton->func=alliance2func;
				break;

			case DASHBOARD_ALLIANCE_3:
				cur2waybutton->func=alliance3func;
				break;


			}


			numonscreenbuttons++;

			break;

		case GADGETTYPE_RADIOBUTTON:
			/*for radio buttons, aux1 and aux2 are the current button and how many buttons
			 *aux3 is the radiotype
			 */

			if (curdashboard->dashboard_gadgets[assembly->whichgadget])
			{
				if (curdashboard->dashboard_gadgets[assembly->whichgadget]->type!=GADGETTYPE_RADIOBUTTON)
				{
					TRACE("ERROR: multiple references to the same dashboard gadget in the assembly info\n");
					TRACE("have differet gadget types\n");
					return -1;
				}

				curradiobutton=(GADGET_RADIOBUTTON*)(curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget);

				if ((curradiobutton->radiotype!=assembly->aux3) || (curradiobutton->numbuttons!=assembly->aux2))
				{
					TRACE("ERROR: multiple references to the same radio button specify different base info\n");
					return -1;
				}

				if (curradiobutton->screenpos[assembly->aux1].x!=-1)
				{
					TRACE("ERROR: there appear to be multiple references to a single element of a radio button set\n");
					return -1;
				}

			}
			else
			{
				curdashboard->dashboard_gadgets[assembly->whichgadget]=(GADGET*)malloc(sizeof(GADGET));
				curdashboard->dashboard_gadgets[assembly->whichgadget]->type=GADGETTYPE_RADIOBUTTON;
				curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget=
					(void*)(curradiobutton=
					(GADGET_RADIOBUTTON*)malloc(sizeof(GADGET_RADIOBUTTON)));
				ZeroMemory(curradiobutton,sizeof(GADGET_RADIOBUTTON));

				curradiobutton->radiotype=assembly->aux3;
				curradiobutton->numbuttons=assembly->aux2;

				curradiobutton->screenpos=(SPOINT*)malloc(sizeof(SPOINT)*curradiobutton->numbuttons);
				for (i=0;i<curradiobutton->numbuttons;i++)
					curradiobutton->screenpos[i].x=-1;	//to show that it's unused

				curradiobutton->sprites[0]=(SPRITE**)malloc(sizeof(SPRITE*)*curradiobutton->numbuttons);
				ZeroMemory(curradiobutton->sprites[0], sizeof(SPRITE*)*curradiobutton->numbuttons);

				curradiobutton->sprites[1]=(SPRITE**)malloc(sizeof(SPRITE*)*curradiobutton->numbuttons);
				ZeroMemory(curradiobutton->sprites[1], sizeof(SPRITE*)*curradiobutton->numbuttons);

				numonscreenbuttons+=curradiobutton->numbuttons;

				//add code to set the function
			}

			curradiobutton->screenpos[assembly->aux1]=assembly->onscreenloc;

			break;

		case GADGETTYPE_LIST:
		/* aux1=(listtype<<16) + listfont
		 * aux2=displaysize
		 * aux3=spacing
		 */
			if (curdashboard->dashboard_gadgets[assembly->whichgadget]) //was already allocated
			{
				TRACE("ERROR: we appear to improperly have two dashboard assembly elements for gadget %d\n",assembly->whichgadget);
				return -1;
				break;
			}
			curdashboard->dashboard_gadgets[assembly->whichgadget]=(GADGET*)malloc(sizeof(GADGET));
			curdashboard->dashboard_gadgets[assembly->whichgadget]->type=GADGETTYPE_LIST;
			curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget=
				(void*)(curlist=
				(GADGET_LIST*)malloc(sizeof(GADGET_LIST)));
			ZeroMemory(curlist,sizeof(GADGET_LIST));

			curlist->screenpos=assembly->onscreenloc;
			curlist->listtype=(assembly->aux1)>>16;
			curlist->displaysize=assembly->aux2;
			curlist->spacing=assembly->aux3;
			curlist->listfont=(FONTS)(assembly->aux1 & 0xffff);

			// do something to set the appropriate function, listsize and listtext

			switch (assembly->whichgadget)
			{
				case DASHBOARD_COMPOSEMESSAGEWINDOW:
					curlist->listsize=1;
					curlist->listtext=&(curdashboard->pcurmessage);
					curlist->func=turnonkeys;
					curlist->cursordata=(CURSOR_INFO*)malloc(sizeof(CURSOR_INFO));
					ZeroMemory(curlist->cursordata, sizeof(CURSOR_INFO));
					curlist->drawfunc=drawcursor;
					UI_nextMode = UI_CurMode;

					break;

				case DASHBOARD_MESSAGEFROMSQUADWINDOW:
					{
						int i;

						curlist->listsize=curlist->displaysize;
						curlist->func=selectsquadfrommessage;

						curlist->extradata=AllocateGenericTextbox(curlist->listsize, SQUADMESSAGE_MAXLENGTH+(sizeof(void*)/sizeof(char)));
						curlist->listtext=(char**)curlist->extradata;
						
						for (i=0;i<curlist->listsize;i++)
							curlist->listtext[i]+=(sizeof(void*)/sizeof(char));
						//the first 4 bytes of each string in the message from squad window is
						//reserved for a pointer to the squad which sent the message

						squadmessagepixelwidth=assembly->hotspot.right-assembly->hotspot.left-3;

					}
					break;
			}

			numonscreenbuttons++;

			break;

		case GADGETTYPE_TEXTBOX:
		/* aux1=spacing
		 * aux2=onscreenlines;
		 * aux3=font
		 */
			if (curdashboard->dashboard_gadgets[assembly->whichgadget]) //was already allocated
			{
				TRACE("ERROR: we appear to improperly have two dashboard assembly elements for gadget %d\n",assembly->whichgadget);
				return -1;
				break;
			}
			curdashboard->dashboard_gadgets[assembly->whichgadget]=(GADGET*)malloc(sizeof(GADGET));
			curdashboard->dashboard_gadgets[assembly->whichgadget]->type=GADGETTYPE_TEXTBOX;
			curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget=
				(void*)(curtextbox=
				(GADGET_TEXTBOX*)malloc(sizeof(GADGET_TEXTBOX)));
			ZeroMemory(curtextbox,sizeof(GADGET_TEXTBOX));

			curtextbox->spacing=assembly->aux1;
			curtextbox->screenpos=assembly->onscreenloc;
			curtextbox->onscreenlines=assembly->aux2;
			curtextbox->textfont=(FONTS)assembly->aux3;

			switch (assembly->whichgadget)
			{
				case DASHBOARD_RECEIVECHATWINDOW:
					{
						CHAT_RECEIVE_STRUCT *chat_receive;
						int i;

						chat_receive=(CHAT_RECEIVE_STRUCT*)malloc(sizeof(CHAT_RECEIVE_STRUCT));
						ZeroMemory(chat_receive, sizeof(CHAT_RECEIVE_STRUCT));

						for (i=0;i<CHAT_MESSAGES_ONSCREEN;i++)
							chat_receive->pstrings[i]=&(chat_receive->strings[i*(MESSAGE_COMP_MAXLENGTH+1)]);


						curtextbox->linesoftext=CHAT_MESSAGES_ONSCREEN;
						curtextbox->boxtext=chat_receive->pstrings;
						curtextbox->extradata=(void*)chat_receive;
					}
					break;

				case DASHBOARD_UNITINFO:
					curtextbox->extradata=AllocateGenericTextbox(2, 30);
					curtextbox->linesoftext=2;
					curtextbox->boxtext=(char**)curtextbox->extradata;
					break;

				case DASHBOARD_AMMODISPLAY:
					curtextbox->extradata=AllocateGenericTextbox(2,10);
					curtextbox->linesoftext=2;
					curtextbox->boxtext=(char**)curtextbox->extradata;
					break;

				case DASHBOARD_VEHICLEAMMODISPLAY:
					curtextbox->extradata=AllocateGenericTextbox(2,10);
					curtextbox->linesoftext=2;
					curtextbox->boxtext=(char**)curtextbox->extradata;
					break;

			}

			break;

		case GADGETTYPE_WHOLEDASHBOARD:
			curdashboard->dashboardloc=assembly->onscreenloc;
			curdashboard->topborder=assembly->aux1;

			break;
		}
	
		if (curdashboard->dashboard_gadgets[assembly->whichgadget])
			curdashboard->dashboard_gadgets[assembly->whichgadget]->chunk=assembly->whichchunk;



	assembly++;

	}

	curdashboard->numbuttons=numonscreenbuttons;

	curonscreenbutton=curdashboard->buttons=(ONSCREENBUTTON*)malloc(sizeof(ONSCREENBUTTON)*numonscreenbuttons);
	ZeroMemory(curdashboard->buttons, sizeof(ONSCREENBUTTON)*numonscreenbuttons);

	assembly=assemblyarray;

	while (assembly->whichtype!=GADGETTYPE_END)
	{
		switch (assembly->whichtype)
		{
			case GADGETTYPE_BUTTON:

				if (assembly->hotspot.right>0)
				{
					curonscreenbutton->whichpart=0;
					curonscreenbutton->subdivisionwidth=0;
					curonscreenbutton->screenrect=assembly->hotspot;
					curonscreenbutton->pGadget=curdashboard->dashboard_gadgets[assembly->whichgadget];
				
					curonscreenbutton++;
				}

				break;

			case GADGETTYPE_MULTIBUTTON:
				if (assembly->hotspot.right>0)
				{
					curonscreenbutton->whichpart=0;
					curonscreenbutton->subdivisionwidth=0;
					curonscreenbutton->screenrect=assembly->hotspot;
					curonscreenbutton->pGadget=curdashboard->dashboard_gadgets[assembly->whichgadget];
				
					curonscreenbutton++;
				}

				break;

			case GADGETTYPE_2WAYBUTTON:
				curonscreenbutton->whichpart=0;
				curonscreenbutton->subdivisionwidth=0;
				curonscreenbutton->screenrect=assembly->hotspot;
				curonscreenbutton->pGadget=curdashboard->dashboard_gadgets[assembly->whichgadget];

				curonscreenbutton++;

				break;

			case GADGETTYPE_RADIOBUTTON:
				curonscreenbutton->whichpart=assembly->aux1;
				curonscreenbutton->subdivisionwidth=0;
				curonscreenbutton->screenrect=assembly->hotspot;
				curonscreenbutton->pGadget=curdashboard->dashboard_gadgets[assembly->whichgadget];

				curonscreenbutton++;

				break;

			case GADGETTYPE_LIST:
				curonscreenbutton->whichpart=0;
				curonscreenbutton->subdivisionwidth=(assembly->hotspot.bottom-assembly->hotspot.top)/assembly->aux2;
				curonscreenbutton->screenrect=assembly->hotspot;
				curonscreenbutton->pGadget=curdashboard->dashboard_gadgets[assembly->whichgadget];

				curonscreenbutton++;
		}

		assembly++;
	}
	
	return 0;

}
///========================================================================
//	Function:		DashBMPtoPointer()
//
//	Description:
//		Uses a table of ASSEMBLY_TRANS_ELEMENTs to look up a DASHBMP_TYPE
//		and return the pointer to the loaded sprite	
//
//	Input:			transtable			pointer to the table
//					dashbmp				which DASHBMP_TYPE to look up
//					dashboard			pointer to the dashboard under consideration
//
//	Ouput:			pointer to the sprite, or NULL on error		
//
///========================================================================
SPRITE *DashBMPtoPointer(ASSEMBLY_TRANS_ELEMENT *transtable, DASHBMP_TYPE dashbmp, DASHBOARD *dashboard)
{
	int i=0;
	
	if (!dashboard->sprites)
	{
		TRACE("ERROR: No dashboard sprites\n");
		return NULL;
	}

	while (transtable[i].filename!=NULL)
	{
		if (transtable[i].dashbmp==dashbmp)
			return dashboard->sprites[transtable[i].whichsprite];
		i++;
	}

	TRACE("ERROR: unable to find dashbmp %d: %s\n", dashbmp, transtable[i].filename);

	return NULL;
}





///========================================================================
//	Function:		DashboardLoadGraphicsFromAssembly()
//
//	Description:
//		Loads in all the graphics for a dashboard created from
//		an array of DASHBOARD_ASSEMBLY_ELEMENTs		
//
//	Input:			assembly			pointer to the array
//					transtable			pointer to an array of trans elements
//
//	Ouput:			negative on error		
//
///========================================================================
int DashboardLoadGraphicsFromAssembly(DASHBOARD_ASSEMBLY_ELEMENT *assemblyarray, ASSEMBLY_TRANS_ELEMENT *transtable)
{
	GADGET_BUTTON *curbutton;
	GADGET_MULTIBUTTON *curmultibutton;
	GADGET_2WAYBUTTON *cur2waybutton;
	GADGET_RADIOBUTTON *curradiobutton;
	DASHBOARD_ASSEMBLY_ELEMENT *assembly;
	int i;
	int numsprites;
	int size;
	int total_size = 0;
	int cat;
	
	if (!curdashboard)
		return 0;

	if (curdashboard->graphics_loaded)
		return 0;

	curdashboard->graphics_loaded=TRUE;

	if( _LOAD_FROM_DATAFILE )
	{
		cat = 300;
		if( gpGame->GameType != GAMETYPE_ONEPLAYER )
			cat = 300 + PlayerColor(ARMY_PLAYER);
	}
	else
	{
		SetPath(DASH_PATH);
		if( gpGame->GameType != GAMETYPE_ONEPLAYER )
		{
			if( PlayerColor(ARMY_PLAYER) != 0 )
			{
				char *colordir[] = { "", "tan", "blue", "grey" };
				char path[40];

				sprintf( path, "%s\\%s", DASH_PATH, colordir[PlayerColor(ARMY_PLAYER)] );
				SetPath(path);
			}
		}
	}


	//first off, we have to prepare the translation table and load in all the sprites
	
	//count up how many sprites there are
	numsprites = 0;
	for( i = 0; transtable[i].filename != NULL; i++ )
	{
		if( i < DASHBMP_SPECIALITEM_0 + NumSpecialItems )
			numsprites++;
	}

	curdashboard->sprites=(SPRITE **)malloc(sizeof(SPRITE *)*numsprites);
	ZeroMemory(curdashboard->sprites, sizeof(SPRITE *)*numsprites);
	curdashboard->numsprites=numsprites;

	if( _LOAD_FROM_DATAFILE )
	{
		for( i = 0; i < numsprites; i++ )
		{
			int num, idx;
			char cnum[5], cidx[5];

			strncpy( cnum, transtable[i].filename + 5, 3 );
			cnum[3] = 0;
			num = atoi( cnum );
			if( strlen(transtable[i].filename) > 13 )
			{
				strncpy( cidx, transtable[i].filename + 9, 15-13 );
				if( cidx[1] == '.' )
					cidx[1] = 0;
				else
					cidx[2] = 0;
				idx = atoi(cidx);
			}
			else
				idx = 0;
			
			if( !(curdashboard->sprites[i] = AcquireObjectSprite(cat, num, idx)) )
			{
				TRACE( "ERROR: failed to load a dashboard sprite [%s:%d]\n\n", 
						__FILE__, __LINE__ );
				return -1;
			}

			if( transtable[i].flags & BM_OPAQUE )
				curdashboard->sprites[i]->sprite_flags |= SP_OPAQUE;
			transtable[i].whichsprite = i;
		}
	}
	else
	{
		for ( i = 0; i < numsprites; i++ )
		{
			curdashboard->sprites[i] = (SPRITE *)malloc( sizeof(SPRITE) );
			if (!(size = LoadSprite( curdashboard->sprites[i], transtable[i].filename, transtable[i].flags )) )
			{
				TRACE( "ERROR: failed to load a dashboard sprite [%s:%d]\n\n", 
						__FILE__, __LINE__ );
				return -1;
			}

			transtable[i].whichsprite=i;
			total_size += size;
		}
	}

	assembly=assemblyarray;

	while (assembly->whichtype!=GADGETTYPE_END)
	{
		switch(assembly->whichtype)
		{
		case GADGETTYPE_WHOLEDASHBOARD:	
			if ((curdashboard->dashboardsprite=DashBMPtoPointer(transtable, assembly->bmp1, curdashboard))==NULL)
			{
				TRACE("ERROR: failed to find a dashboard sprite\n");
				return -1;
			}
			break;

		case GADGETTYPE_BUTTON:
			if (!curdashboard->dashboard_gadgets[assembly->whichgadget])
				return -1;

			if (!curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget)
				return -1;

			curbutton=(GADGET_BUTTON*) curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget;

			if ((curbutton->sprites[0]=DashBMPtoPointer(transtable, assembly->bmp1, curdashboard))==NULL)
			{
				TRACE("ERROR: failed to find a dashboard sprite\n");
				return -1;
			}
			
			if (assembly->bmp2!=DASHBMP_LAST)
				if ((curbutton->sprites[1]=DashBMPtoPointer(transtable, assembly->bmp2, curdashboard))==NULL)
				{
					TRACE("ERROR: failed to find a dashboard sprite\n");
					return -1;
				}

				break;

		case GADGETTYPE_MULTIBUTTON:
			if (!curdashboard->dashboard_gadgets[assembly->whichgadget])
				return -1;

			if (!curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget)
				return -1;

			curmultibutton=(GADGET_MULTIBUTTON*) curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget;

			for (i=0;i<curmultibutton->numpictures;i++)
			{

				if (assembly->bmps1[i]!=DASHBMP_LAST)
					if ((curmultibutton->sprites[0][i]=DashBMPtoPointer(transtable, assembly->bmps1[i], curdashboard))==NULL)
					{
						TRACE("ERROR: failed to find a dashboard sprite\n");
						return -1;
					}
				
				if (assembly->bmps2[i]!=DASHBMP_LAST)
					if ((curmultibutton->sprites[1][i]=DashBMPtoPointer(transtable, assembly->bmps2[i], curdashboard))==NULL)
					{
						TRACE("ERROR: failed to find a dashboard sprite\n");
						return -1;
					}
			}

			break;

		case GADGETTYPE_2WAYBUTTON:
			if (!curdashboard->dashboard_gadgets[assembly->whichgadget])
				return -1;

			if (!curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget)
				return -1;

			cur2waybutton=(GADGET_2WAYBUTTON*) curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget;

			if (assembly->bmp1!=DASHBMP_LAST)
				if ((cur2waybutton->sprites[0]=DashBMPtoPointer(transtable, assembly->bmp1, curdashboard))==NULL)
				{
					TRACE("ERROR: failed to find a dashboard sprite\n");
					return -1;
				}
			

			if (assembly->bmp2!=DASHBMP_LAST)
				if ((cur2waybutton->sprites[1]=DashBMPtoPointer(transtable, assembly->bmp2, curdashboard))==NULL)
				{
					TRACE("ERROR: failed to find a dashboard sprite\n");
					return -1;
				}


			break;

		case GADGETTYPE_RADIOBUTTON:
			if (!curdashboard->dashboard_gadgets[assembly->whichgadget])
				return -1;

			if (!curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget)
				return -1;

			curradiobutton=(GADGET_RADIOBUTTON*) curdashboard->dashboard_gadgets[assembly->whichgadget]->pGadget;

			if ((curradiobutton->sprites[0][assembly->aux1]=DashBMPtoPointer(transtable, assembly->bmp1, curdashboard))==NULL)
			{
				TRACE("ERROR: failed to find a dashboard sprite\n");
				return -1;
			}
			

			if ((curradiobutton->sprites[1][assembly->aux1]=DashBMPtoPointer(transtable, assembly->bmp2, curdashboard))==NULL)
			{
				TRACE("ERROR: failed to find a dashboard sprite\n");
				return -1;
			}

			break;
		}
	
		assembly++;
	}
	return 0;
}

///========================================================================
//	Function:		DashboardUnloadGraphics()
//
//	Description:
//		Unloads all the graphics associated with curdashboard	
//
//	Input:			none
//
//	Ouput:			none		
//
///========================================================================



void DashboardUnloadGraphics(void)
{
	int i;

	if (!curdashboard)
		return;

	curdashboard->graphics_loaded=FALSE;

	if( curdashboard->sprites )
	{
		for (i=0;i<curdashboard->numsprites;i++)
		{
			if( curdashboard->sprites[i] )
			{
				if( _LOAD_FROM_DATAFILE )
				{
					ReleaseObjectSprite(curdashboard->sprites[i]);
				}
				else
				{
					FreeSprite(curdashboard->sprites[i]);
					free( curdashboard->sprites[i] );
				}
			}
		}
		free( curdashboard->sprites );
		curdashboard->sprites = NULL;
	}

	curdashboard->numsprites=0;
}


///========================================================================
//	Function:		FreeDashboard()
//
//	Description:
//		Frees up all the memory associated with a dashboard	
//
//	Input:			none
//
//	Ouput:			none	
//
///========================================================================
void FreeDashboard(void)
{
	DASHBOARD_GADGETS curgadget;
	GADGET_MULTIBUTTON *curmultibutton;
	GADGET_RADIOBUTTON *curradiobutton;
	GADGET_LIST *curlist;
	GADGET_TEXTBOX *curtextbox;

	if (!curdashboard)
		return;

	for (curgadget=DASHBOARD_START;curgadget!=DASHBOARD_LAST;curgadget=(DASHBOARD_GADGETS)(((int)curgadget)+1))
	{
		if (curdashboard->dashboard_gadgets[curgadget])
		{
			switch (curdashboard->dashboard_gadgets[curgadget]->type)
			{
			case GADGETTYPE_BUTTON:
				free(curdashboard->dashboard_gadgets[curgadget]->pGadget);
				free(curdashboard->dashboard_gadgets[curgadget]);
				break;
			case GADGETTYPE_MULTIBUTTON:
				curmultibutton=(GADGET_MULTIBUTTON*)curdashboard->dashboard_gadgets[curgadget]->pGadget;
				free(curmultibutton->sprites[0]);
				free(curmultibutton->sprites[1]);

				free(curdashboard->dashboard_gadgets[curgadget]->pGadget);
				free(curdashboard->dashboard_gadgets[curgadget]);
				break;
			case GADGETTYPE_2WAYBUTTON:
				free(curdashboard->dashboard_gadgets[curgadget]->pGadget);
				free(curdashboard->dashboard_gadgets[curgadget]);
				break;
			case GADGETTYPE_RADIOBUTTON:
				curradiobutton=(GADGET_RADIOBUTTON*)curdashboard->dashboard_gadgets[curgadget]->pGadget;

				free(curradiobutton->screenpos);
				free(curradiobutton->sprites[0]);
				free(curradiobutton->sprites[1]);
				free(curdashboard->dashboard_gadgets[curgadget]->pGadget);
				free(curdashboard->dashboard_gadgets[curgadget]);
				break;

			case GADGETTYPE_LIST:
				curlist=(GADGET_LIST*)curdashboard->dashboard_gadgets[curgadget]->pGadget;

				if (curlist->cursordata)
					free(curlist->cursordata);

				if (curlist->extradata)
					free(curlist->extradata);

				free(curdashboard->dashboard_gadgets[curgadget]->pGadget);
				free(curdashboard->dashboard_gadgets[curgadget]);
				break;

			case GADGETTYPE_TEXTBOX:
				curtextbox=(GADGET_TEXTBOX*)curdashboard->dashboard_gadgets[curgadget]->pGadget;

				if (curtextbox->extradata)
					free(curtextbox->extradata);

				free(curdashboard->dashboard_gadgets[curgadget]->pGadget);
				free(curdashboard->dashboard_gadgets[curgadget]);
				break;

			case GADGETTYPE_RADAR:
				free(curdashboard->dashboard_gadgets[curgadget]->pGadget);
				free(curdashboard->dashboard_gadgets[curgadget]);
				break;


			}
		}
	}

	free(curdashboard->buttons);
	free(curdashboard);
	curdashboard=NULL;
	ClearSelectedUnit();
}

DASHBMP_TYPE sitemicons[]=
{
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_WEAPONICON_GRENADE,
		DASHBMP_WEAPONICON_FLAME,
		DASHBMP_WEAPONICON_BAZOOKA,
		DASHBMP_WEAPONICON_MORTAR,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_WEAPONICON_RIFLE,
		DASHBMP_WEAPONICON_AUTORIFLE,
		DASHBMP_WEAPONICON_MINE,
		DASHBMP_WEAPONICON_BOMB  ,
		DASHBMP_WEAPONICON_BOMB,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_WEAPONICON_MINESWEEPER,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_WEAPONICON_MEDPACK
};


DASHBMP_TYPE mitemicons[]=
{
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_WEAPONICON_GRENADE,
		DASHBMP_WEAPONICON_FLAME,
		DASHBMP_WEAPONICON_BAZOOKA,
		DASHBMP_WEAPONICON_MORTAR,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_WEAPONICON_RIFLE,
		DASHBMP_WEAPONICON_AUTORIFLE,
		DASHBMP_WEAPONICON_MINE,
		DASHBMP_WEAPONICON_BOMB  ,
		DASHBMP_WEAPONICON_BOMB,
		DASHBMP_LAST,
		DASHBMP_WEAPONICON_FLAG,
		DASHBMP_WEAPONICON_GREENFLAG,
		DASHBMP_WEAPONICON_TANFLAG,
		DASHBMP_WEAPONICON_BLUEFLAG,
		DASHBMP_WEAPONICON_GRAYFLAG,
		DASHBMP_WEAPONICON_MINESWEEPER,
		DASHBMP_LAST,
		DASHBMP_LAST,
		DASHBMP_WEAPONICON_MEDPACK
};

DASHBMP_TYPE specialitemicons[]=
{
	DASHBMP_SPECIALITEM_0,
	DASHBMP_SPECIALITEM_1,
	DASHBMP_SPECIALITEM_2,
	DASHBMP_SPECIALITEM_3,
	DASHBMP_SPECIALITEM_4,
	DASHBMP_SPECIALITEM_5,
	DASHBMP_SPECIALITEM_6,
	DASHBMP_SPECIALITEM_7,
	DASHBMP_SPECIALITEM_8,
	DASHBMP_SPECIALITEM_9,
	DASHBMP_SPECIALITEM_10,
	DASHBMP_SPECIALITEM_11,
	DASHBMP_SPECIALITEM_12,
	DASHBMP_SPECIALITEM_13,
	DASHBMP_SPECIALITEM_14,
	DASHBMP_SPECIALITEM_15,
	DASHBMP_SPECIALITEM_16,
	DASHBMP_SPECIALITEM_17,
	DASHBMP_SPECIALITEM_18,
	DASHBMP_SPECIALITEM_19,
	DASHBMP_SPECIALITEM_10,
	DASHBMP_SPECIALITEM_21,
	DASHBMP_SPECIALITEM_22,
	DASHBMP_SPECIALITEM_23,
	DASHBMP_SPECIALITEM_24,
	DASHBMP_SPECIALITEM_25,
	DASHBMP_SPECIALITEM_26,
	DASHBMP_SPECIALITEM_27,
	DASHBMP_SPECIALITEM_28,
	DASHBMP_SPECIALITEM_29,
};


DASHBMP_TYPE weaponcursors[]=
{
		DASHBMP_LAST,
		DASHBMP_WEAPONSELECTCURSOR_OFF,
		DASHBMP_WEAPONSELECTCURSOR_ON
};

DASHBMP_TYPE vehicleicons[]=
{
	DASHBMP_LAST,
	DASHBMP_VEHICLEICON_JEEP,
	DASHBMP_VEHICLEICON_TANK,
	DASHBMP_VEHICLEICON_HALFTRACK,
	DASHBMP_VEHICLEICON_CONVOY,
	DASHBMP_LAST
};
	
DASHBMP_TYPE trooperinfolights[]=
{
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_RED,
		DASHBMP_SMALLLIGHT_YELLOW,
		DASHBMP_SMALLLIGHT_GREEN
};

DASHBMP_TYPE vehicleammoicons[]=
{
	DASHBMP_LAST,
	DASHBMP_WEAPONICON_RIFLE,
	DASHBMP_WEAPONICON_AUTORIFLE,
	DASHBMP_VEHICLEAMMOICON_TANK,
	DASHBMP_VEHICLEAMMOICON_OTHER,
};

DASHBMP_TYPE itemselecticons[]=
{
	DASHBMP_ITEMSELECT_NONE,
	DASHBMP_ITEMSELECT_RIFLE,
	DASHBMP_ITEMSELECT_GRENADE,
	DASHBMP_ITEMSELECT_FLAME,
	DASHBMP_ITEMSELECT_BAZOOKA,
	DASHBMP_ITEMSELECT_MORTAR,
	DASHBMP_ITEMSELECT_JEEP,
	DASHBMP_ITEMSELECT_HALFTRACK,
	DASHBMP_ITEMSELECT_TANK,
	DASHBMP_ITEMSELECT_TRUCK
};

#define NUMITEMTYPES (sizeof(itemselecticons)/sizeof(DASHBMP_TYPE))

DASHBOARD_ASSEMBLY_ELEMENT assembly_singleplayer[]=
{
	{
		GADGETTYPE_LIST,
		DASHBOARD_MESSAGEFROMSQUADWINDOW,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{25, 387},
		{23,386,168,460},
		(GADGET_LISTTYPE_NOSELECTIONS<<16)+FONT_TIMES_14,
		6,
		12
	},	
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_UNITINFO,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{325, 440},
		{0,0,0,0},
		11,
		2,
		FONT_TIMES_14
	},
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_AMMODISPLAY,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{291,423},
		{0,0,0,0},
		20,
		2,
		FONT_TIMES_14
	},
	/*
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_MISSION,
		DASH_CHUNK_MAIN,
		DASHBMP_MISSION_UP,
		DASHBMP_MISSION_DOWN,
		NULL, NULL,
		{ 188, 447},
		{ 189, 448, 241, 477 },
		0,
		0,
		0
	},
	*/
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_VEHICLEAMMOICON,
		DASH_CHUNK_MAIN,
		DASHBMP_LAST,
		DASHBMP_LAST,
		vehicleammoicons, vehicleammoicons,
		{ 249, 400},
		{0,0,0,0},
		5,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONICON,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		sitemicons, sitemicons,
		{249,421},
		{0,0,0,0},
		24,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMICON,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		sitemicons, sitemicons,
		{249,442},
		{0,0,0,0},
		24,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONSELECTED_1,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		weaponcursors, weaponcursors,
		{247,399},
		{249,400,306,419},
		3,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONSELECTED_2,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,		
		weaponcursors, weaponcursors,
		{247,420},
		{249,421,306,440},
		3,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONSELECTED_3,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		weaponcursors, weaponcursors,
		{247,441},
		{249,442,306,461},
		3,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_VEHICLEICON,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		vehicleicons, vehicleicons,
		{394,412},
		{0,0,0,0},
		6,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_1,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_RED,
		NULL, NULL,
		{329,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_2,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{337,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_3,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{345,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_4,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{353,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_5,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{361,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_6,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{369,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_7,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{377,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_8,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{385,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_1,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_RED,
		NULL, NULL,
		{329,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_2,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{337,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_3,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{345,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_4,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{353,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_5,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{361,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_6,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{369,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_7,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{377,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_8,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{385,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRDROP_1,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{456,431},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRDROP_2,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{450,431},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRDROP_3,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{444,431},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRSTRIKE_1,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{456,407},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRSTRIKE_2,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{450,407},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRSTRIKE_3,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{444,407},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_RECON_1,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{456,454},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_RECON_2,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{450,454},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_RECON_3,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{444,454},
		{0,0,0,0},
		0,
		0,
		0
	},
#ifdef JUNK //deleting trooper info
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_1,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{329,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_2,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{337,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_3,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{345,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_4,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{353,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_5,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{361,467},
		{0,0,0,0},
		4,
		0,
		0
	},
        #endif
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_SPECIALITEM,
		DASH_CHUNK_MAIN,
		DASHBMP_LAST,
		DASHBMP_LAST,
		specialitemicons, specialitemicons,
		{190, 390},
		{190, 390, 238, 435},
		30,
		0,
		0
	},
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_VEHICLEAMMODISPLAY,
		DASH_CHUNK_MAIN,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{291, 402},
		{0,0,0,0},
		20,
		1,
		FONT_TIMES_14
	},
	{
		GADGETTYPE_WHOLEDASHBOARD,
		DASHBOARD_LAST,
		DASH_CHUNK_MAIN,			
		DASHBMP_MAIN,
		DASHBMP_LAST,
		NULL, NULL,
		{0, 365},
		{0,0,0,0},
		384,
		0,
		0
	},
	{
		GADGETTYPE_END,
		DASHBOARD_LAST,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{0, 0},
		{0,0,0,0},
		0,
		0,
		0
	}
};



ASSEMBLY_TRANS_ELEMENT assembly_sprites_singleplayer[]=
{
	{
		DASHBMP_MAIN,
		"dash_001_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_MISSION_UP,
		"misn_002_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_MISSION_DOWN,
		"misn_002_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_AIRSUPPORT_ON,
		"airs_003_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SMALLLIGHT_GREEN,
		"smli_004_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SMALLLIGHT_YELLOW,
		"smli_004_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SMALLLIGHT_RED,
		"smli_004_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_TANK,
		"tank_005_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_JEEP,
		"jeep_005_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_HALFTRACK,
		"half_005_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_CONVOY,
		"conv_005_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_GRENADE,
		"gren_006_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_FLAME,
		"flam_006_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_BAZOOKA,
		"bzka_006_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MORTAR,
		"mort_006_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MINE,
		"mine_006_5.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_BOMB,
		"bomb_006_6.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MEDPACK,
		"medp_006_7.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MINESWEEPER,
		"swpr_006_8.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONSELECTCURSOR_ON,
		"ghil_007_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_WEAPONSELECTCURSOR_OFF,
		"rhil_007_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_WEAPONICON_RIFLE,
		"rifl_006_9.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_AUTORIFLE,
		"auto_006_10.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEAMMOICON_TANK,
		"tank_006_11.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEAMMOICON_OTHER,
		"vehi_006_12.bmp",
		0,
		BM_OPAQUE
	},
	{									// special items go last in this list
		DASHBMP_SPECIALITEM_0,
		"spec_018_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SPECIALITEM_1,
		"spec_018_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SPECIALITEM_2,
		"spec_018_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SPECIALITEM_3,
		"spec_018_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SPECIALITEM_4,
		"spec_018_5.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SPECIALITEM_5,
		"spec_018_6.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_6,
		"spec_018_7.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_7,
		"spec_018_8.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_8,
		"spec_018_9.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_9,
		"spec_018_10.bmp",
		0,
		BM_TRANSPARENT
	},	{
		DASHBMP_SPECIALITEM_10,
		"spec_018_11.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_11,
		"spec_018_12.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_12,
		"spec_018_13.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_13,
		"spec_018_14.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_14,
		"spec_018_15.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_15,
		"spec_018_16.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_16,
		"spec_018_17.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_17,
		"spec_018_18.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_18,
		"spec_018_19.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_19,
		"spec_018_20.bmp",
		0,
		BM_TRANSPARENT
	},	{
		DASHBMP_SPECIALITEM_20,
		"spec_018_21.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_21,
		"spec_018_22.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_22,
		"spec_018_23.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_23,
		"spec_018_24.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_24,
		"spec_018_25.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_25,
		"spec_018_26.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_26,
		"spec_018_27.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_27,
		"spec_018_28.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_28,
		"spec_018_29.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_SPECIALITEM_29,
		"spec_018_30.bmp",
		0,
		BM_TRANSPARENT							// do not put anything here
	},
	{
		DASHBMP_LAST,
		NULL,
		0,
		BM_TRANSPARENT
	}
};


DASHBOARD_ASSEMBLY_ELEMENT assembly_twoplayer[]=
{
	{	
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_START,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_START_UP,
		DASHBMP_START_DOWN,
		NULL, NULL,
		{185,434},
		{188, 435, 228, 447},
		0,
		0,
		0
	},
	/*
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_PAUSE,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_PAUSE_UP,
		DASHBMP_PAUSE_DOWN,
		NULL, NULL,
		{ 182, 451},			// { 188, 447},
		{ 183, 452, 232, 477 },	// { 189, 448, 241, 477 },
		0,
		0,
		0
	},
	*/
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_STARTLIGHT_1,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_LIGHT_GREENPLAYER_OFF,
		DASHBMP_LIGHT_GREENPLAYER_ON,
		NULL, NULL,
		{191, 456},
		{0,0,0,0},
		0,
		0,
		0
	},
/*
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_STARTLIGHT_2,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_LIGHT_GREENPLAYER_OFF,
		DASHBMP_LIGHT_GREENPLAYER_ON,
		NULL, NULL,
		{204, 456},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_STARTLIGHT_3,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_LIGHT_GREENPLAYER_OFF,
		DASHBMP_LIGHT_GREENPLAYER_ON,
		NULL, NULL,
		{217, 456},
		{0,0,0,0},
		0,
		0,
		0
	},
  */
	{
		GADGETTYPE_LIST,
		DASHBOARD_MESSAGEFROMSQUADWINDOW,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{24, 408},
		{23,407,176,460},
		(GADGET_LISTTYPE_NOSELECTIONS<<16)+FONT_TIMES_14,
		5,
		10
	},
	{
		GADGETTYPE_LIST,
		DASHBOARD_COMPOSEMESSAGEWINDOW,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{24, 386},
		{23,385,176,399},
		(GADGET_LISTTYPE_NOSELECTIONS<<16)+FONT_TIMES_14,
		1,
		12
	},
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_RECEIVECHATWINDOW,
		DASH_CHUNK_MAIN,			
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{30, 30},
		{0,0,0,0},
		20,
		CHAT_MESSAGES_ONSCREEN,
		FONT_TIMES_20
	},		
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_UNITINFO,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{325, 440},
		{0,0,0,0},
		11,
		2,
		FONT_TIMES_14
	},
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_AMMODISPLAY,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{291,423},
		{0,0,0,0},
		20,
		2,
		FONT_TIMES_14
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_VEHICLEAMMOICON,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		vehicleammoicons, vehicleammoicons,
		{ 249, 400},
		{0,0,0,0},
		5,
		0,
		0
	},	
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_VEHICLEAMMODISPLAY,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{291, 402},
		{0,0,0,0},
		20,
		1,
		FONT_TIMES_14
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONICON,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		mitemicons, mitemicons,
		{249,421},
		{0,0,0,0},
		24,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMICON,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		mitemicons, mitemicons,
		{249,442},
		{0,0,0,0},
		24,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONSELECTED_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		weaponcursors, weaponcursors,
		{247,399},
		{249,400,306,419},
		3,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONSELECTED_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,		
		weaponcursors, weaponcursors,
		{247,420},
		{249,421,306,440},
		3,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONSELECTED_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		weaponcursors, weaponcursors,
		{247,441},
		{249,442,306,461},
		3,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_VEHICLEICON,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		vehicleicons, vehicleicons,
		{394,412},
		{0,0,0,0},
		6,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_RED,
		NULL, NULL,
		{329,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{337,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{345,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_4,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{353,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_5,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{361,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_6,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{369,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_7,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{377,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_8,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{385,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_RED,
		NULL, NULL,
		{329,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{337,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{345,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_4,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{353,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_5,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{361,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_6,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{369,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_7,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{377,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_8,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{385,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRDROP_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{456,431},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRDROP_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{450,431},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRDROP_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{444,431},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRSTRIKE_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{456,407},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRSTRIKE_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{450,407},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRSTRIKE_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{444,407},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_RECON_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{456,454},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_RECON_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{450,454},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_RECON_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{444,454},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{329,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{337,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{345,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_4,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{353,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_5,
		DASH_CHUNK_HIDDENBYMULTISETUP,		
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{361,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_ITEMSELECT_BACKGROUND,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_ITEMSELECT_BACKGROUND,
		DASHBMP_ITEMSELECT_BACKGROUND,
		NULL, NULL,
		{242, 384},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_1,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{257,393},
		{257,393,292,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_2,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{295,393},
		{295,393,330,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_3,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{333,393},
		{333,393,368,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_4,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{371,393},
		{371,393,406,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_5,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{409,393},
		{409,393,444,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_6,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{447,393},
		{447,393,482,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_7,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{257,418},
		{257,418,292,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_8,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{295,418},
		{295,418,330,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_9,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{333,418},
		{333,418,368,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_10,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{371,418},
		{371,418,406,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_11,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{409,418},
		{409,418,444,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_12,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{447,418},
		{447,418,482,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_13,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{257,443},
		{257,443,292,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_14,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{295,443},
		{295,443,330,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_15,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{333,443},
		{333,443,368,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_16,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{371,443},
		{371,443,406,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_17,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{409,443},
		{409,443,444,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_18,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{447,443},
		{447,443,482,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_WHOLEDASHBOARD,
		DASHBOARD_LAST,
		DASH_CHUNK_MAIN,
		DASHBMP_MAIN,
		DASHBMP_LAST,
		NULL, NULL,
		{0, 365},
		{0,0,0,0},
		384,
		0,
		0
	},
	{
		GADGETTYPE_END,
		DASHBOARD_LAST,
		DASH_CHUNK_MAIN,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{0, 0},
		{0,0,0,0},
		0,
		0,
		0
	}
};











ASSEMBLY_TRANS_ELEMENT assembly_sprites_twoplayer[]=
{
	{
		DASHBMP_MAIN,
		"dash_001_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_START_UP,
		"strt_008_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_START_DOWN,
		"strt_008_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_PAUSE_UP,
		"paus_009_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_PAUSE_DOWN,
		"paus_009_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_AIRSUPPORT_ON,
		"airs_003_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SMALLLIGHT_GREEN,
		"smli_004_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SMALLLIGHT_YELLOW,
		"smli_004_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SMALLLIGHT_RED,
		"smli_004_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_TANK,
		"tank_005_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_JEEP,
		"jeep_005_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_HALFTRACK,
		"half_005_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_CONVOY,
		"conv_005_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_GRENADE,
		"gren_006_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_FLAME,
		"flam_006_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_BAZOOKA,
		"bzka_006_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MORTAR,
		"mort_006_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MINE,
		"mine_006_5.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_BOMB,
		"bomb_006_6.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MEDPACK,
		"medp_006_7.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_FLAG,
		"flag_006_13.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_GREENFLAG,
		"gflg_006_14.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_TANFLAG,
		"tflg_006_15.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_BLUEFLAG,
		"bflg_006_16.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_GRAYFLAG,
		"yflg_006_17.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MINESWEEPER,
		"swpr_006_8.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONSELECTCURSOR_ON,
		"ghil_007_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_WEAPONSELECTCURSOR_OFF,
		"rhil_007_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_ITEMSELECT_RIFLE,
		"rifl_010_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_GRENADE,
		"gren_010_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_FLAME,
		"flam_010_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_BAZOOKA,
		"bzka_010_5.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_MORTAR,
		"mort_010_6.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_NONE,
		"empt_010_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_JEEP,
		"jeep_010_7.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_HALFTRACK,
		"half_010_8.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_TANK,
		"tank_010_9.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_TRUCK,
		"conv_010_10.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_BACKGROUND,
		"tray_011_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_LIGHT_GREENPLAYER_ON,
		"redy_012_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_GREENPLAYER_OFF,
		"redy_012_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_TANPLAYER_ON,
		"redy_012_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_TANPLAYER_OFF,
		"redy_012_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_BLUEPLAYER_ON,
		"redy_012_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_BLUEPLAYER_OFF,
		"redy_012_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_GRAYPLAYER_ON,
		"redy_012_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_GRAYPLAYER_OFF,
		"redy_012_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_WEAPONICON_RIFLE,
		"rifl_006_9.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_AUTORIFLE,
		"auto_006_10.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEAMMOICON_TANK,
		"tank_006_11.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEAMMOICON_OTHER,
		"vehi_006_12.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_LAST,
		NULL,
		0,
		BM_OPAQUE
	}
};



DASHBOARD_ASSEMBLY_ELEMENT assembly_multiplayer[]=
{
	{	
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_START,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_START_UP,
		DASHBMP_START_DOWN,
		NULL, NULL,
		{185,434},
		{188, 435, 228, 447},
		0,
		0,
		0
	},
	/*
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_PAUSE,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_PAUSE_UP,
		DASHBMP_PAUSE_DOWN,
		NULL, NULL,
		{ 182, 451},			// { 188, 447},
		{ 183, 452, 232, 477 },	// { 189, 448, 241, 477 },
		0,
		0,
		0
	},
	*/
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_STARTLIGHT_1,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_LIGHT_GREENPLAYER_OFF,
		DASHBMP_LIGHT_GREENPLAYER_ON,
		NULL, NULL,
		{191, 456},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_STARTLIGHT_2,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_LIGHT_GREENPLAYER_OFF,
		DASHBMP_LIGHT_GREENPLAYER_ON,
		NULL, NULL,
		{204, 456},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_STARTLIGHT_3,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_LIGHT_GREENPLAYER_OFF,
		DASHBMP_LIGHT_GREENPLAYER_ON,
		NULL, NULL,
		{217, 456},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_LIST,
		DASHBOARD_MESSAGEFROMSQUADWINDOW,
		DASH_CHUNK_MAIN,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{24, 408},
		{23,407,176,460},
		(GADGET_LISTTYPE_NOSELECTIONS<<16)+FONT_TIMES_14,
		5,
		10
	},
	{
		GADGETTYPE_LIST,
		DASHBOARD_COMPOSEMESSAGEWINDOW,
		DASH_CHUNK_MAIN,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{24, 386},
		{23,385,176,399},
		(GADGET_LISTTYPE_NOSELECTIONS<<16)+FONT_TIMES_14,
		1,
		12
	},
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_RECEIVECHATWINDOW,
		DASH_CHUNK_MAIN,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{30, 30},
		{0,0,0,0},
		20,
		CHAT_MESSAGES_ONSCREEN,
		FONT_TIMES_20
	},		
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_UNITINFO,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{325, 440},
		{0,0,0,0},
		11,
		2,
		FONT_TIMES_14
	},
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_AMMODISPLAY,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{291,423},
		{0,0,0,0},
		20,
		2,
		FONT_TIMES_14
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_VEHICLEAMMOICON,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		vehicleammoicons, vehicleammoicons,
		{ 249, 400},
		{0,0,0,0},
		5,
		0,
		0
	},	
	{
		GADGETTYPE_TEXTBOX,
		DASHBOARD_VEHICLEAMMODISPLAY,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{291, 402},
		{0,0,0,0},
		20,
		1,
		FONT_TIMES_14
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONICON,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		mitemicons, mitemicons,
		{249,421},
		{0,0,0,0},
		24,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMICON,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		mitemicons, mitemicons,
		{249,442},
		{0,0,0,0},
		24,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONSELECTED_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		weaponcursors, weaponcursors,
		{247,399},
		{249,400,306,419},
		3,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONSELECTED_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,		
		weaponcursors, weaponcursors,
		{247,420},
		{249,421,306,440},
		3,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_WEAPONSELECTED_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		weaponcursors, weaponcursors,
		{247,441},
		{249,442,306,461},
		3,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_VEHICLEICON,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		vehicleicons, vehicleicons,
		{394,412},
		{0,0,0,0},
		6,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_RED,
		NULL, NULL,
		{329,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{337,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{345,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_4,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{353,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_5,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{361,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_6,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{369,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_7,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{377,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_SARGEHEALTH_8,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{385,399},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_RED,
		NULL, NULL,
		{329,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{337,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_YELLOW,
		NULL, NULL,
		{345,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_4,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{353,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_5,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{361,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_6,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{369,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_7,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{377,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_VEHICLEHEALTH_8,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_SMALLLIGHT_GREEN,
		NULL, NULL,
		{385,423},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRDROP_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{456,431},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRDROP_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{450,431},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRDROP_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{444,431},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRSTRIKE_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{456,407},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRSTRIKE_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{450,407},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_AIRSTRIKE_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{444,407},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_RECON_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{456,454},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_RECON_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{450,454},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_RECON_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_AIRSUPPORT_ON,
		NULL, NULL,
		{444,454},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{329,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{337,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{345,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_4,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{353,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_TROOPERINFO_5,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_LAST,
		DASHBMP_LAST,
		trooperinfolights, trooperinfolights,
		{361,467},
		{0,0,0,0},
		4,
		0,
		0
	},
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_ITEMSELECT_BACKGROUND,
		DASH_CHUNK_MULTISETUP,
		DASHBMP_ITEMSELECT_BACKGROUND,
		DASHBMP_ITEMSELECT_BACKGROUND,
		NULL, NULL,
		{242, 384},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_1,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{257,393},
		{257,393,292,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_2,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{295,393},
		{295,393,330,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_3,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{333,393},
		{333,393,368,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_4,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{371,393},
		{371,393,406,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_5,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{409,393},
		{409,393,444,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_6,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{447,393},
		{447,393,482,414},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_7,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{257,418},
		{257,418,292,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_8,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{295,418},
		{295,418,330,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_9,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{333,418},
		{333,418,368,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_10,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{371,418},
		{371,418,406,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_11,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{409,418},
		{409,418,444,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_12,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{447,418},
		{447,418,482,439},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_13,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{257,443},
		{257,443,292,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_14,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{295,443},
		{295,443,330,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_15,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{333,443},
		{333,443,368,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_16,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{371,443},
		{371,443,406,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_17,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{409,443},
		{409,443,444,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_MULTIBUTTON,
		DASHBOARD_ITEMSELECT_18,
		DASH_CHUNK_MULTISETUP,		
		DASHBMP_ITEMSELECT_NONE,
		DASHBMP_ITEMSELECT_NONE,
		itemselecticons, itemselecticons,
		{447,443},
		{447,443,482,464},
		NUMITEMTYPES,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_CHATTOGGLE_1,
		DASH_CHUNK_MAIN,
		DASHBMP_TANUP,
		DASHBMP_TANDOWN,
		NULL, NULL,
		{185, 406},
		{185, 406, 197, 417},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_CHATTOGGLE_2,
		DASH_CHUNK_MAIN,
		DASHBMP_BLUEUP,
		DASHBMP_BLUEDOWN,
		NULL, NULL,
		{201, 406},
		{201, 406, 213, 417},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_CHATTOGGLE_3,
		DASH_CHUNK_MAIN,
		DASHBMP_GREYUP,
		DASHBMP_GREYDOWN,
		NULL, NULL,
		{217, 406},
		{217, 406, 229, 417},
		0,
		0,
		0
	},
	{
		GADGETTYPE_BUTTON,
		DASHBOARD_ALLIANCE_BACKGROUND,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_ALLIANCEBACKGROUND,
		DASHBMP_ALLIANCEBACKGROUND,
		NULL, NULL,
		{182, 425},
		{0,0,0,0},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_ALLIANCE_1,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_TANUP,
		DASHBMP_TANDOWN,
		NULL, NULL,
		{185, 438},
		{185, 438, 197, 449},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_ALLIANCE_2,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_BLUEUP,
		DASHBMP_BLUEDOWN,
		NULL, NULL,
		{201, 438},
		{201, 438, 213, 449},
		0,
		0,
		0
	},
	{
		GADGETTYPE_2WAYBUTTON,
		DASHBOARD_ALLIANCE_3,
		DASH_CHUNK_HIDDENBYMULTISETUP,
		DASHBMP_GREYUP,
		DASHBMP_GREYDOWN,
		NULL, NULL,
		{217, 438},
		{217, 439, 229, 449},
		0,
		0,
		0
	},


	{
		GADGETTYPE_WHOLEDASHBOARD,
		DASHBOARD_LAST,
		DASH_CHUNK_MAIN,
		DASHBMP_MAIN,
		DASHBMP_LAST,
		NULL, NULL,
		{0, 365},
		{0,0,0,0},
		384,
		0,
		0
	},
	{
		GADGETTYPE_END,
		DASHBOARD_LAST,
		DASH_CHUNK_MAIN,
		DASHBMP_LAST,
		DASHBMP_LAST,
		NULL, NULL,
		{0, 0},
		{0,0,0,0},
		0,
		0,
		0
	}
};




ASSEMBLY_TRANS_ELEMENT assembly_sprites_multiplayer[]=
{
	{
		DASHBMP_MAIN,
		"dash_001_3.bmp",
		0
	},
	{
		DASHBMP_START_UP,
		"strt_008_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_START_DOWN,
		"strt_008_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_PAUSE_UP,
		"paus_009_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_PAUSE_DOWN,
		"paus_009_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_AIRSUPPORT_ON,
		"airs_003_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SMALLLIGHT_GREEN,
		"smli_004_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SMALLLIGHT_YELLOW,
		"smli_004_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_SMALLLIGHT_RED,
		"smli_004_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_TANK,
		"tank_005_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_JEEP,
		"jeep_005_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_HALFTRACK,
		"half_005_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEICON_CONVOY,
		"conv_005_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_GRENADE,
		"gren_006_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_FLAME,
		"flam_006_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_BAZOOKA,
		"bzka_006_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MORTAR,
		"mort_006_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MINE,
		"mine_006_5.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_BOMB,
		"bomb_006_6.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_FLAG,
		"flag_006_13.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_GREENFLAG,
		"gflg_006_14.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_TANFLAG,
		"tflg_006_15.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_BLUEFLAG,
		"bflg_006_16.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_GRAYFLAG,
		"yflg_006_17.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MINESWEEPER,
		"swpr_006_8.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONSELECTCURSOR_ON,
		"ghil_007_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_WEAPONSELECTCURSOR_OFF,
		"rhil_007_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_ITEMSELECT_RIFLE,
		"rifl_010_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_GRENADE,
		"gren_010_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_FLAME,
		"flam_010_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_BAZOOKA,
		"bzka_010_5.bmp",
		0,
		BM_OPAQUE
	},
		{
		DASHBMP_ITEMSELECT_MORTAR,
		"mort_010_6.bmp",
		0,
		BM_OPAQUE
	},

	{
		DASHBMP_ITEMSELECT_NONE,
		"empt_010_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_JEEP,
		"jeep_010_7.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_HALFTRACK,
		"half_010_8.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_TANK,
		"tank_010_9.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_TRUCK,
		"conv_010_10.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_GREENUP,
		"gbtn_016_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_GREENDOWN,
		"gbtn_016_2.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_TANUP,
		"tbtn_016_3.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_TANDOWN,
		"tbtn_016_4.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_BLUEUP,
		"bbtn_016_5.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_BLUEDOWN,
		"bbtn_016_6.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_GREYUP,
		"ybtn_016_7.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_GREYDOWN,
		"ybtn_016_8.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_ITEMSELECT_BACKGROUND,
		"tray_011_1.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_LIGHT_GREENPLAYER_ON,
		"redy_012_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_GREENPLAYER_OFF,
		"redy_012_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_TANPLAYER_ON,
		"redy_012_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_TANPLAYER_OFF,
		"redy_012_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_BLUEPLAYER_ON,
		"redy_012_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_BLUEPLAYER_OFF,
		"redy_012_2.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_GRAYPLAYER_ON,
		"redy_012_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_LIGHT_GRAYPLAYER_OFF,
		"redy_012_2.bmp",
		0,
		BM_TRANSPARENT
	},	
	{
		DASHBMP_ALLIANCEBACKGROUND,
		"ally_017_1.bmp",
		0,
		BM_TRANSPARENT
	},
	{
		DASHBMP_WEAPONICON_RIFLE,
		"rifl_006_9.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_AUTORIFLE,
		"auto_006_10.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_WEAPONICON_MEDPACK,
		"medp_006_7.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEAMMOICON_TANK,
		"tank_006_11.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_VEHICLEAMMOICON_OTHER,
		"vehi_006_12.bmp",
		0,
		BM_OPAQUE
	},
	{
		DASHBMP_LAST,
		NULL,
		0
	}
};




int DashboardLoadGraphics(void)
{
	switch(NumHumanPlayers())
	{

#ifdef MULTISETUPDEBUG		
		case 1:return DashboardLoadGraphicsFromAssembly(assembly_twoplayer, assembly_sprites_twoplayer/*assembly_singleplayer, assembly_sprites_singleplayer*/);
#else
		case 1:return DashboardLoadGraphicsFromAssembly(assembly_singleplayer, assembly_sprites_singleplayer);
#endif
		case 2:return DashboardLoadGraphicsFromAssembly(assembly_twoplayer, assembly_sprites_twoplayer);

		case 3: 
		case 4:return DashboardLoadGraphicsFromAssembly(assembly_multiplayer, assembly_sprites_multiplayer);

	}
	TRACE("ERROR: invalid number of players when trying to load dashboard!\n");
	exit(-1);
	return -1;
}


DASHBMP_TYPE playerlights[4][2]=
{
	{
		DASHBMP_GREENUP,
		DASHBMP_GREENDOWN
	},
	{
		DASHBMP_TANUP,
		DASHBMP_TANDOWN
	},
	{
		DASHBMP_BLUEUP,
		DASHBMP_BLUEDOWN
	},
	{
		DASHBMP_GREYUP,
		DASHBMP_GREYDOWN
	}
};

DASHBMP_TYPE smallplayerlights[4][2]=
{
	{
		DASHBMP_LIGHT_GREENPLAYER_OFF,
		DASHBMP_LIGHT_GREENPLAYER_ON
	},
	{
		DASHBMP_LIGHT_TANPLAYER_OFF,
		DASHBMP_LIGHT_TANPLAYER_ON
	},
	{
		DASHBMP_LIGHT_BLUEPLAYER_OFF,
		DASHBMP_LIGHT_BLUEPLAYER_ON
	},
	{
		DASHBMP_LIGHT_GRAYPLAYER_OFF,
		DASHBMP_LIGHT_GRAYPLAYER_ON
	}
};



void DashboardInit(void)
{

	DASHBOARD_ASSEMBLY_ELEMENT *assembly;
	int numhumanplayers, i;
	
	chatscrollcounter=gpGame->dwAnimTime;

	curtarget.target_type=TARGET_NONE;
	curtarget.pObj=NULL;

	curtarget.importanttargetindex=0;

	numhumanplayers=NumHumanPlayers();

	switch (numhumanplayers) //set up the colored player lights properly
	{
	case 3:
			assembly=assembly_multiplayer;

			while (assembly->whichtype!=GADGETTYPE_END)
			{
				switch(assembly->whichgadget)
				{
				case DASHBOARD_ALLIANCE_1:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)1)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)1)][1];
					break;
				case DASHBOARD_CHATTOGGLE_1:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)1)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)1)][1];
					break;
				case DASHBOARD_ALLIANCE_2:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)2)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)2)][1];
					break;
				case DASHBOARD_CHATTOGGLE_2:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)2)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)2)][1];
					break;
				case DASHBOARD_ALLIANCE_3:
					assembly->whichtype=GADGETTYPE_INACTIVE;
					break;
				case DASHBOARD_CHATTOGGLE_3:
					assembly->whichtype=GADGETTYPE_INACTIVE;
					break;
				case DASHBOARD_STARTLIGHT_1:
					assembly->bmp1=smallplayerlights[PlayerColor((ARMY_TYPE)1)][0];
					assembly->bmp2=smallplayerlights[PlayerColor((ARMY_TYPE)1)][1];
					break;
				case DASHBOARD_STARTLIGHT_2:
					assembly->bmp1=smallplayerlights[PlayerColor((ARMY_TYPE)2)][0];
					assembly->bmp2=smallplayerlights[PlayerColor((ARMY_TYPE)2)][1];
					break;
				case DASHBOARD_STARTLIGHT_3:
					assembly->whichtype=GADGETTYPE_INACTIVE;
					break;

				}

				assembly++;
			}
			break;
	case 4:
			assembly=assembly_multiplayer;

			while (assembly->whichtype!=GADGETTYPE_END)
			{
				switch(assembly->whichgadget)
				{
				case DASHBOARD_ALLIANCE_1:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)1)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)1)][1];
					break;
				case DASHBOARD_CHATTOGGLE_1:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)1)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)1)][1];
					break;
				case DASHBOARD_ALLIANCE_2:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)2)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)2)][1];
					break;
				case DASHBOARD_CHATTOGGLE_2:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)2)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)2)][1];
					break;
				case DASHBOARD_ALLIANCE_3:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)3)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)3)][1];
					break;
				case DASHBOARD_CHATTOGGLE_3:
					assembly->bmp1=playerlights[PlayerColor((ARMY_TYPE)3)][0];
					assembly->bmp2=playerlights[PlayerColor((ARMY_TYPE)3)][1];
					break;
				case DASHBOARD_STARTLIGHT_1:
					assembly->bmp1=smallplayerlights[PlayerColor((ARMY_TYPE)1)][0];
					assembly->bmp2=smallplayerlights[PlayerColor((ARMY_TYPE)1)][1];
					break;
				case DASHBOARD_STARTLIGHT_2:
					assembly->bmp1=smallplayerlights[PlayerColor((ARMY_TYPE)2)][0];
					assembly->bmp2=smallplayerlights[PlayerColor((ARMY_TYPE)2)][1];
					break;
				case DASHBOARD_STARTLIGHT_3:
					assembly->bmp1=smallplayerlights[PlayerColor((ARMY_TYPE)3)][0];
					assembly->bmp2=smallplayerlights[PlayerColor((ARMY_TYPE)3)][1];
					break;
				}

				assembly++;
			}
			break;
	}

	switch(numhumanplayers)
	{

#ifdef MULTISETUPDEBUG
		case 1:DashboardInitFromAssembly(/*assembly_singleplayer*/ assembly_twoplayer);
#else
		case 1:DashboardInitFromAssembly(assembly_singleplayer);
#endif
		  break;

		case 2:DashboardInitFromAssembly(assembly_twoplayer);
		  break;

		case 3:
		case 4: DashboardInitFromAssembly(assembly_multiplayer);
	      break;

		default:
			TRACE("ERROR: invalid number of players when trying to load dashboard!\n");
			exit(-1);
	};

	CurSelectedUndeployedItem=NULL;
	ZeroMemory(UndeployedItems, sizeof(UndeployedItems));

	curdashboard->chunksActive[DASH_CHUNK_MAIN]=1;
	curdashboard->chunksActive[DASH_CHUNK_MULTISETUP]=1;
	curdashboard->chunksActive[DASH_CHUNK_HIDDENBYMULTISETUP]=0;


	Dashboard_Update();

	for (i=0;i<numhumanplayers;i++)
		chatMask|=(1<<i);
}


void InitUndeployedUnitInfo(void)
{
	UI_GetUndeployedStuff(UndeployedItems);

}


BYTE	UIshadeTable[256];
BYTE*	CreateShadeTable( int rLevel, int gLevel, int bLevel )		// level = 0-255
{
	memset( UIshadeTable, 0, sizeof( BYTE ) );
	return( UIshadeTable );
}


void UI_TurnOffStrategoMode(void)
{
	if (!curdashboard)
		return;

	SendDashboardChat();
	UI_EndChat();

	curdashboard->chunksActive[DASH_CHUNK_MULTISETUP]=0;
	curdashboard->chunksActive[DASH_CHUNK_HIDDENBYMULTISETUP]=1;
}

int ESC_Mode() // esc key to cancel command to unit or scroll
{
    if (UI_CurMode == UIMODE_LOOKINGATSARGE) return FALSE;

    endScrollingMode();
    return TRUE;
}

void	RecallInit( char *file )
{
	if (RecallSprite.pGraphic)
		FreeSprite( &RecallSprite );

	if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
		LoadOnePlayerRecall(file);
	else
		LoadMultiPlayerRecall(file);
}

void	MapRecallInit()
{
	char name[32];

	SetPath( MAP_PATH );

	if (RecallSprite.pGraphic)
		FreeSprite( &RecallSprite );

	sprintf( name, "%s_%d.bmp", the_map.map_name, g_MissionIndex+1 );

	// now load the mission briefing
	LoadSprite( &RecallSprite, name, BM_OPAQUE | BM_SYSTEMMEMORY );
}

static void	LoadOnePlayerRecall( char *file )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	char *name = file;

	SetPath( BRIEFS_PATH );

	if (!name)	{
		// get the campaign, scenario, and mission references
		pCampaign          = g_Campaigns[ g_CampaignIndex ];
		if ( !pCampaign )
			return;
		g_ScenarioIndex    = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
		pScenario          = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
		if ( !pScenario )
			return;
		g_MissionIndex     = AiMissionIndex( pScenario, gpGame->MissionID );
		pMission           = &(pScenario->pMissions[ g_MissionIndex ]);
		if ( !pMission )
			return;

		name = pMission->pBriefFile;
	}

	// now load the mission briefing
	LoadSprite( &RecallSprite, name, BM_TRANSPARENT|BM_SYSTEMMEMORY );
}

static void	LoadMultiPlayerRecall( char *file )
{
	char *name = file;
	char tempname[32];

	SetPath( BRIEFS_PATH );
	if (!name)	{
		name = tempname;
		sprintf( name, "%s", brieffilename );
	}

	LoadSprite( &RecallSprite, name, BM_TRANSPARENT|BM_SYSTEMMEMORY );
}

//===================================================================
//							EOF
//===================================================================
