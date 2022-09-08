/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Sarge.cpp $
//
//	DESCRIPTION:	Vehicle movement
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Sunday, July 27, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Sarge.cpp 503   4/18/98 12:49p Bwilcox $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Sarge.cpp $
//  
//  503   4/18/98 12:49p Bwilcox
//  created xtriggers, moved trigger_branch to it, added
//  xtrigger_sargecarried
//  
//  502   4/17/98 2:02p Bwilcox
//  removed a trace
//  
//  501   4/15/98 12:08p Bwilcox
//  indent deploy trace
//  
//  500   4/14/98 2:42p Nrobinso
//  turn off health voice over on sarge death
//  
//  499   4/14/98 10:58a Phu
//  increase viewbox for sarge
//  
//  498   4/13/98 7:34p Nrobinso
//  make sure all sarge audio message are for your sarge only
//  
//  497   4/12/98 11:16p Nrobinso
//  heal sarge with voice over
//  
//  496   4/10/98 11:46a Nrobinso
//  use fire now option; try to keep need health happening when sarge is
//  really almost dead
//  
//  495   4/10/98 1:11a Bwilcox
//  keeping deadposition as unique data
//  
//  494   4/09/98 9:57p Dmaynard
//  Added ItemSpecialUpdatePosition for cases where items enter and leave
//  the universe.
//  
//  493   4/09/98 8:45p Bwilcox
//  attemp to get pad status correct
//  
//  492   4/09/98 7:30p Dmaynard
//  Removed call to ItemUpdatePad in SargeGone (was creating "Error a pad
//  thinks there are less than zero items on it
//  
//  491   4/09/98 7:10p Dmaynard
//  Added call to ItemUpdatePad inside of SargeGone just after we moved his
//  position off map. To prevent sarges that died on Pads from still being
//  on Pad in event world.
//  
//  490   4/09/98 6:40p Dmaynard
//  Removed extraneous calls to ItemUpdate Pad. Army does this once a frame
//  for everyone anyway.
//  
//  489   4/09/98 12:39p Bwilcox
//  testing npc sarge movement
//  
//  488   4/09/98 12:05p Bwilcox
//  issargeuntrafficable varies if sarge is npc. new arg added
//  
//  487   4/08/98 11:48p Nrobinso
//  make sarge health a voice over
//  
//  486   4/08/98 2:50p Bwilcox
//  NPC SARGE WILL ACTIVATE ANY 2NDARY WEAPON HE PICKS UP
//  
//  485   4/07/98 2:13p Nrobinso
//  make illelgally deployed message debug only
//  
//  484   4/07/98 6:40a Bwilcox
//  using setaiview
//  
//  483   4/06/98 2:02p Nrobinso
//  add to auto tuning
//  
//  482   4/05/98 11:49p Bwilcox
//  reducing hp damage when prone even for small damages
//  
//  481   4/03/98 8:56p Bwilcox
//  clean up vehicle movement layer code
//  
//  479   4/03/98 4:47p Phu
//  fix sarge out of vehicle
//  
//  478   4/03/98 3:53p Phu
//  remove unreferenced variable
//  
//  477   4/03/98 3:42p Phu
//  change sarge movement
//  
//  476   4/03/98 2:23p Phu
//  use untrafficableunit for vehicle out
//  
//  475   4/03/98 2:15p Nrobinso
//  only do pickup audio for your sarge
//  
//  474   4/03/98 12:26p Bwilcox
//  give sarge a default pending pose on creation
//  
//  473   4/03/98 12:30p Nrobinso
//  fix the second incarnation of popping back to sarge when another sarge
//  dies
//  
//  472   4/03/98 12:19p Nrobinso
//  fix retruning to sarge when local ai sarge dies; add pixk up of air
//  support
//  
//  471   4/03/98 10:15a Bwilcox
//  npc sarge wont pick up anything but valid flags in 3rnd slot
//  
//  470   4/02/98 7:35p Nrobinso
//  fix med pack anim and timing; add variety of death sounds
//  
//  469   98/04/02 16:59 Dmaynard
//  typecast ITemfanout to be Ipoint
//  
//  468   4/02/98 3:21p Phu
//  typecast to avoid warnings
//  
//  467   4/02/98 2:45p Nrobinso
//  cleanup object triggers
//  
//  466   4/02/98 1:44p Bwilcox
//  cleanups in event triggering and traces
//  
//  465   4/02/98 10:51a Bwilcox
//  revising sargeupdate for npc sarges
//  
//  464   4/01/98 1:51p Bwilcox
//  change local test
//  
//  463   4/01/98 1:17p Bwilcox
//  allow normal trafficability for sargedeploy
//  
//  462   3/31/98 4:51p Bwilcox
//  testing for locaol sarge, not player sarge
//  
//  461   3/31/98 2:15p Bwilcox
//  fix jumping of sargeviewpoint from ai dead sarge
//  
//  460   3/31/98 12:59p Bwilcox
//  dispell fog
//  
//  459   3/30/98 11:48p Nrobinso
//  sarge grunts when goes below 30% health
//  
//  458   3/30/98 8:10p Phu
//  make it +5
//  
//  457   3/30/98 8:08p Phu
//  pass fire height for flame throwers (ground + 4)
//  
//  456   3/29/98 4:32p Nrobinso
//  limit how much sarge says "loaded up"
//  
//  455   3/29/98 1:28a Nrobinso
//  don't play pickup sound when loading a saved game
//  
//  454   3/28/98 2:53p Nrobinso
//  put in the full slot v/o
//  
//  453   3/28/98 7:14a Bwilcox
//  multiplayer-mode easter egg. Enjoy. Best Regards, The AI Guru
//  
//  452   3/27/98 8:34p Nrobinso
//  fix sarge with mortar running instead of firing
//  
//  451   3/27/98 8:21p Nrobinso
//  use sarge's actual avatar command intead of his requested avatar
//  command
//  
//  450   3/27/98 2:19p Phu
//  quest item load from campaign file
//  
//  449   3/27/98 1:49p Phu
//  survive ALT_TAB dammit
//  
//  448   3/27/98 1:25p Nrobinso
//  stop turning off firing bar, which allows you to see where the mortar
//  lands, but means that the mortar woun't go off under certain
//  circumstances
//  
//  447   3/27/98 11:19a Bwilcox
//  assert sarges strength
//  
//  446   3/27/98 10:13a Nrobinso
//  clear firing bar only after all other processing
//  
//  445   3/26/98 9:35p Phu
//  strategy items: prone, roll & dive protection
//  
//  444   3/26/98 6:40p Nrobinso
//  turn off firing bar (cursor) if not actively firing
//  
//  443   3/26/98 4:41p Nrobinso
//  new v/o's
//  
//  442   3/26/98 2:39p Bwilcox
//  vehicle in movement layer split into new layer
//  
//  441   3/26/98 1:50p Nrobinso
//  minesweeper doesn't kneel to fire
//  
//  440   3/26/98 12:36p Nrobinso
//  fix no moving cursor when running with greades or mortar
//  
//  439   3/25/98 6:56p Nrobinso
//  only play pickup voice on local sarge
//  
//  438   3/25/98 10:05a Bwilcox
//  
//  437   3/25/98 9:16a Bwilcox
//  fireweapon lock on remote
//  
//  436   3/25/98 9:07a Bwilcox
//  
//  435   3/25/98 9:06a Bwilcox
//  
//  434   3/25/98 9:04a Bwilcox
//  add fireindex
//  
//  433   3/24/98 8:00p Dmaynard
//  renamed killerarmycolor to killerarmyindex  because it IS an index.
//  
//  432   3/24/98 5:58p Phu
//  3 second delay before you allow someone to pick up an item
//  
//  431   98/03/24 17:40 Dmaynard
//  
//  430   98/03/24 17:39 Dmaynard
//  fixing immediate pickup when sarge dies with 2 things
//  
//  429   3/24/98 5:22p Nrobinso
//  pick up messages
//  
//  428   3/24/98 4:55p Phu
//  change event trigger version of killerarmy
//  
//  427   3/23/98 5:57p Phu
//  triggerdelay on events from sarge pickup
//  
//  426   3/23/98 11:48a Bwilcox
//  change sarge illegal deploy propogate
//  
//  425   3/22/98 3:16p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  424   3/22/98 2:50p Nrobinso
//  sound for heal sarge and change weapon
//  
//  423   3/22/98 1:34p Bwilcox
//  testing for non-army existing when getting a sarge
//  
//  422   3/20/98 12:06a Nrobinso
//  clear mouse buttons when not used by sarge
//  
//  421   3/19/98 1:47p Nrobinso
//  update vehicle sfx
//  
//  420   3/18/98 5:23p Nrobinso
//  remove special sweeper check for movement
//  
//  419   3/17/98 6:16p Bwilcox
//  sargefind may now safely return null
//  
//  418   3/17/98 4:43p Nrobinso
//  increaseaffect of auto tuning
//  
//  417   3/17/98 11:54a Nrobinso
//  don't check posing for weapons, let the avaatar code do it
//  
//  416   3/16/98 6:31p Nrobinso
//  fix firing with pose change
//  
//  415   3/16/98 5:28p Aburgess
//  changed sfxExist() call to sfxInPlay() call
//  
//  414   3/16/98 4:36p Aburgess
//  modifications made to correctly look up the SFX snd ID
//  
//  413   3/16/98 4:48p Nrobinso
//  make the rifle act more like the bazooka
//  
//  412   3/16/98 4:09p Nrobinso
//  put in sndID test
//  
//  411   3/16/98 12:10p Nrobinso
//  new avatar calls; auto balance after 8 failures again
//  
//  410   3/16/98 12:27a Nrobinso
//  add autotune of strength
//  
//  409   3/15/98 7:12p Nrobinso
//  improve sarge damage sfx
//  
//  408   3/14/98 8:56p Nrobinso
//  allow switching between mouse button 2 controlling the weapons and
//  forward movement
//  
//  407   3/13/98 10:03p Bwilcox
//  
//  406   3/13/98 6:16p Phu
//  make health percentage based
//  
//  405   3/13/98 6:10p Phu
//  sweeper in slot 3
//  
//  404   3/13/98 11:37a Nrobinso
//  set sarge's anim type properly for explosives
//  
//  403   98-03-11 12:31 Dmaynard
//  
//  402   98-03-10 16:29 Dmaynard
//  Bruce & Peter:  Sarge can move from untrafficable position to
//  untrafficable position.  Prevent cheat move from moving off edge of the
//  map.
//  
//  401   3/10/98 3:46p Phu
//  note that clipline sometimes returns 0!
//  added assert to getobjects
//  fix flamethrowers go off screen
//  
//  400   98-03-10 9:02 Dmaynard
//  Testing a slightly larger raduis for laying mines around Sarge.
//  
//  399   98-03-10 7:58 Dmaynard
//  sargeptr returns null if army_independeint
//  
//  398   3/08/98 10:11p Nrobinso
//  try sarge movement with mouse
//  
//  397   3/08/98 4:41p Phu
//  don't allow switch to other weapons when in vehicle
//  
//  396   3/08/98 4:08p Nrobinso
//  fix typo
//  
//  395   3/08/98 4:07p Nrobinso
//  don't do sarge pose changes when he's in a vehicle
//  
//  394   3/08/98 3:20p Phu
//  prevent sarge from appearing in movement mask of dead vehicle.
//  don't allow fire if weapon is empty
//  
//  393   3/08/98 1:04a Nrobinso
//  combine 2 functions looking at sarge anim type
//  
//  392   3/08/98 1:02a Nrobinso
//  get the anim type of sarge based on his weapon
//  
//  391   3/07/98 10:43p Nrobinso
//  sarge can't move if firing mortar; have interface routines for setting
//  sarge invulnerable
//  
//  390   3/05/98 6:47p Phu
//  sarge fire weapon direction == sarge's gun facing now...
//  
//  389   3/05/98 6:30p Nrobinso
//  fix prone throw and non-kneel mortar
//  
//  388   3/05/98 5:17p Nrobinso
//  sarge can only walk while flaming
//  
//  387   3/05/98 4:56p Nrobinso
//  remove trace
//  
//  386   3/05/98 4:47p Nrobinso
//  fix firing
//  
//  385   3/04/98 3:45p Nrobinso
//  sarge stands after ending his talk action
//  
//  384   3/04/98 12:48p Phu
//  don't allow sarge control if sarge is dead
//  don't draw gunsight if sarge is dead
//  
//  383   3/04/98 11:46a Phu
//  fix crash bug in UpdatePosing() if sarge had no avatar.
//  don't allow vehicle deployment on sarge
//  create convoy mask
//  
//  382   3/03/98 9:41p Nrobinso
//  sargedown no longer take an argument; add SargeTalk & SargeEndTalk
//  
//  381   3/03/98 4:59p Nrobinso
//  fix roll & walk back oddities
//  
//  380   3/02/98 5:20p Phu
//  only make chips if sarge is hit by bullets
//  
//  379   98/03/02 15:24 Dmaynard
//  SargeOutVehicle now sets the Avatar's Animation's ANIM_FLAG_ACTIVE bit.
//  This should fix a bug whereby remote sarges that exited a vehicle were
//  invisible until the moved.
//  
//  378   3/02/98 12:14p Phu
//  always assign death
//  always makechips & play sfx if sarge is hit
//  move sarge death sound into sarge death
//  
//  377   2/27/98 7:06p Nrobinso
//  sarge deploy takes a vehicle pointer
//  
//  376   98/02/27 14:57 Dmaynard
//  Fixed it so that for remote vehicles we do not make units exit vehicles
//  when Sarge exits vehicle.  This will be done on the local machine for
//  this sarge and that will send the appropiate exitvehicle messages.
//  
//  375   2/27/98 2:52p Nrobinso
//  fix required cast to audio
//  
//  374   2/27/98 1:17p Bwilcox
//  cleaning up the air, supporting script airdrops for foes,e tc
//  
//  373   2/27/98 12:57p Nrobinso
//  improve sfx calls
//  
//  372   2/25/98 8:51p Nrobinso
//  clear vehicle pointer
//  
//  371   2/25/98 6:28p Phu
//  rename wobject files
//  
//  370   2/20/98 6:41p Phu
//  different deaths
//  
//  369   2/20/98 6:15p Nrobinso
//  don't clear owner of a weapon when it is dropped
//  
//  368   2/20/98 12:53p Phu
//  sarge trafficability stuff
//  
//  367   2/20/98 1:18p Nrobinso
//  fix up sounds
//  
//  366   2/18/98 5:54p Phu
//  better sarge trafficability determination
//  
//  365   2/18/98 2:03p Phu
//  Miscellaneous avatar death parts
//  
//  364   2/17/98 7:50p Nrobinso
//  remove static sfx call
//  
//  363   2/17/98 4:26p Phu
//  insert exploded vehicle husk remains into corpse layer.
//  Eliminate double explosions in single player
//  
//  362   2/17/98 3:03p Nrobinso
//  put debug commands on final compile flag
//  
//  361   2/17/98 9:18a Aburgess
//  new audio parameters
//  
//  360   2/16/98 12:03p Phu
//  pass along fromUID with explosions
//  
//  359   2/13/98 12:21p Nrobinso
//  move joystick access up a level
//  
//  358   2/13/98 11:12a Nrobinso
//  make a common joystick routine
//  
//  357   2/12/98 9:44p Nrobinso
//  fix firing; move SargeDown in from commands
//  
//  356   2/12/98 12:54p Nrobinso
//  new sounds
//  
//  355   2/12/98 11:56a Phu
//  grenade stuff
//  
//  354   2/11/98 4:26p Nrobinso
//  noise when sarge gets hit
//  
//  353   2/11/98 12:05p Phu
//  better bazooka firing
//  
//  352   2/11/98 10:46a Nrobinso
//  don't do normal movement if roll key is on
//  
//  351   2/10/98 3:36p Phu
//  hook firing cursor to primary hotspot for sarge, sarge fine turning
//  
//  350   2/10/98 3:02p Phu
//  only use bmp as mask for vehicles
//  
//  349   2/10/98 3:01p Phu
//  only use bmp as mask for vehicles
//  
//  348   2/10/98 2:21p Phu
//  firing heights
//  
//  347   2/10/98 1:34p Nrobinso
//  add JoystickPresent routine
//  
//  346   2/10/98 1:10p Nrobinso
//  add relative joystick movement
//  
//  345   2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  344   2/09/98 10:42a Nrobinso
//  clarify sarge die call
//  
//  343   2/07/98 1:17p Phu
//  changed keyboard turning
//  
//  342   2/07/98 12:25a Nrobinso
//  activate next weapon with right button
//  
//  341   2/06/98 11:42a Phu
//  husks
//  
//  340   2/05/98 3:27p Bwilcox
//  sarge doesnt die on untrafficle unless he was stationary
//  
//  339   2/05/98 10:30a Nrobinso
//  fix incorrect comment
//  
//  338   2/04/98 5:55p Nrobinso
//  change passing of sarge killed by army to correspond to trooper
//  
//  337   2/04/98 4:43p Phu
//  kill sarge when untrafficable
//  
//  336   2/04/98 1:01p Phu
//  allow sarge to pickup one-use items even if primary slot is occupied
//  
//  335   2/04/98 11:48a Phu
//  lure item
//  
//  334   2/03/98 4:02p Nrobinso
//  flag sarge as deployed
//  
//  333   2/03/98 3:22p Bwilcox
//  sargegetactiveweapon now takes arg,
//  fixed avatar mine interactions
//  
//  332   2/03/98 11:24a Nrobinso
//  fix firing bar stay up; make local & remote call a common routine to
//  set sarge's anim
//  
//  331   2/02/98 5:51p Bwilcox
//  fix mine fire again
//  
//  330   2/02/98 4:26p Bwilcox
//  
//  329   2/02/98 4:26p Bwilcox
//  
//  328   2/02/98 4:25p Bwilcox
//  nits in vehicles fix. deploy when sareg exit vehicle
//  
//  327   2/02/98 4:21p Phu
//  make mines use secondary hotspot for placement
//  
//  326   2/02/98 10:53a Nrobinso
//  make sarge stop rolling
//  
//  325   2/02/98 8:41a Nrobinso
//  mark rolls as being turned
//  
//	...
//  
//  1     7/27/97 2:08p Nrobinso
//  
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "AiAccess.h"
#include "Army.h"
#include "audio.h"
#include "Map.h"
#include "Sarge.h"
#include "explosions.h"
#include "GameFlow.h"
#include "trooper.h"
#include "item.h"
#include "weapon.h"
#include "UI.H"
#include "tad.h"
#include "comm.h"
#include "SargeMsg.h"
#include "unit.h"
#include "input.h"
#include "aix.h"
#include "vehicle.h"
#include "pad.h"
#include "damage.h"
#include "ui.h"
#include "wobject.h"
#include "Commands.h"

/////////////////////////////////////////////////////////////////////////////
// Debugging support
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char sargeInvulnerable[ARMY_LAST_ARMY] = {0,0,0,0};
char sargeImmune = 0;

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
extern BOOL cheat_move;

int specialmodedelay = 0;

#define IsPointEqual(ptA,ptB)   (((ptA).x == (ptB).x) && ((ptA).y == (ptB).y))
#define	NONE SND_NULL_SND_ID

/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////

int gunturnaccel = 1;
int gunturnwait = 0;


/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					LOCAL Prototypes
/////////////////////////////////////////////////////////////////////////////
static void	SargeInitWeapons( SARGE* pSarge );
inline static void SargeSetAvatar(SARGE* pSarge, ACTION pendingAction);

/////////////////////////////////////////////////////////////////////////////
//					     Code
/////////////////////////////////////////////////////////////////////////////

///========================================================================
//	Function:		SargeCreate()
//	Description:	Create Sarge.
///========================================================================

RETERROR	SargeCreate( ARMY_TYPE eArmy )
{
	SARGE *pSarge = SargePointer(eArmy);

// TroopCreate equivalent
    int nID = 0;
	ZeroMemory( (void*)pSarge, sizeof(SARGE) );		// clear the struct

    // limited to 8 bits of units (255) in game
    ASSERT(!(nID & ~AI_ID_SUB2_MASK));	// prove no id overflow
    ItemSetUID(pSarge, eArmy, ARMY_SARGE, ARMY_RIFLE_MEN, nID);

    // we fix the name, independent of map data.
    // a mission should have only 1 sarge. Period.
    if (PlayerColor(eArmy) == ARMY_GREEN)
        ItemSetLabel((ITEM *)pSarge, "GreenSarge");
    else if (PlayerColor(eArmy) == ARMY_TAN)
        ItemSetLabel((ITEM *)pSarge, "TanSarge");
    else if (PlayerColor(eArmy) == ARMY_BLUE)
        ItemSetLabel((ITEM *)pSarge, "BlueSarge");
    else if (PlayerColor(eArmy) == ARMY_GRAY)
        ItemSetLabel((ITEM *)pSarge, "GraySarge");
	pSarge->pendingPose = AVATAR_STAND; // must init this

	return( FALSE );
}


///========================================================================
//	Function:		SargeDelete()
//	Description:	Cleanup after sarge
///========================================================================

static void	SargeDelete( SARGE* pSarge )
{
	if (pSarge->pAvatar)
    {
        AvatarDestroy(pSarge->pAvatar);
        pSarge->pAvatar = NULL;
    }
    
    if (pSarge->common.pTad)
    {
		UnitValidateTad(); // just test the hell out of the links
        TadDeleteObject((TAD*)pSarge->common.pTad);
        pSarge->common.pTad = NULL;
		UnitValidateTad(); // just test the hell out of the links
    }

    pSarge->common.nStrength = 0;			// he must seem dead
}

BOOL LegalAndTrafficable(int x, int y) //checks to see if a given tile is
										//both on the map and trafficable
{
	if ((x>=0) && (y>=0) && (x<map_width) && (y<map_height) && (!UntrafficableUnit(INDEX(x,y))))
		return TRUE;
	return FALSE;
}

///========================================================================
//	Function:		int TrafficableAroundPoint(IPOINT p)
//
//	Description:	determines which, if any, of the 8 tiles surrounding
//					a given tile are trafficable, and codes that information
//					into the low 8 bits of an int.
//
//	Input:			p		which point
//
//	Ouput:			the coded int
//
///========================================================================
int TrafficableAroundPoint(IPOINT p)
{
	int x,y, retvalue=0;

	x=IPOINT_X(p);
	y=IPOINT_Y(p);

	if (LegalAndTrafficable(x,y-1))
		retvalue|=1;

	if (LegalAndTrafficable(x-1,y-1))
		retvalue|=2;

	if (LegalAndTrafficable(x-1,y))
		retvalue|=4;
	
	if (LegalAndTrafficable(x-1,y+1))
		retvalue|=8;
	
	if (LegalAndTrafficable(x,y+1))
		retvalue|=16;
	
	if (LegalAndTrafficable(x+1,y+1))
		retvalue|=32;
	
	if (LegalAndTrafficable(x+1,y))
		retvalue|=64;

	if (LegalAndTrafficable(x+1,y-1))
		retvalue|=128;

	return retvalue;
}

// if pItemList is -1, we need to get our own itemlist
int isSargeUntrafficable(SARGE* pSarge,SPOINT spt, ITEM *pItemList)
{
	int retval;
	int movement;
    IPOINT ipt;

	if (!InRect(&the_map.sargeboundrect,&spt))
		return 1;

    ipt = ENCODE_IPOINT(spt.x,spt.y);
		// npc has tougher standard
	if (pSarge->npc) return UntrafficableUnit(ipt);

//	tileOK= !UntrafficableUnit(ipt);
	retval = the_map.triggers[ipt] & TILE_UNTRAFFICABLE;	// retval=1 if base tile untraff.
//	if( tileOK && !retval )					// movement layer says it's ok
//        return 0;
	movement = retval ? 16 : 0;

	if( pItemList == (ITEM *)(-1) )							// get our own itemlist?
		pItemList = GetObjectsIntersectPoint(&spt);

	while( pItemList )
	{
		switch( ITEM_TYPE(pItemList) )
		{
			case ARMY_ASSET:
			case ARMY_STRUCTURE:
			case ARMY_OBSTACLE:
				movement += ((OBJECTSTRUCT *)pItemList)->movement;
				break;
			case ARMY_VEHICLE:			// fall through!
			case ARMY_HUSK:
				movement += 16;
				break;
		}
		pItemList = pItemList->next;
	}
	
	return( movement >= 15 );
}



void drawSargeTrafficability(void)
{
	int x,y;

	if( !InitBackBufferLockComplex() )
		return;

	DDCOLOR=255;
	SPOINT spt;


	for (x=0;x<the_map.screenrect.right-the_map.screenrect.left;x++)
		for (y=0;y<the_map.screenrect.bottom-the_map.screenrect.top;y++)
		{
			spt.x=x;
			spt.y=y;
			ScreenToWorld(&spt);
			if (isSargeUntrafficable(SargePointer(ARMY_PLAYER),spt))
				DDPutPixel(x, y);
	}


	FreeBackBufferLockComplex();
}


///========================================================================
//	Function:		SargeUpdate()
//
//	Description:	Update sarge position & actions after input (player or commander ai)
//
//	Input:			pSarge		pointer to sarge data
//
//	Ouput:			none
//
///========================================================================

void	SargeUpdate( SARGE* pSarge )
{
	AVATAR *pAvatar = pSarge->pAvatar;
    SPOINT	frame_pt;
    SPOINT	full_pt;
	BOOL	bIsSargeIllegal;

	ASSERT(pSarge->common.nStrength >= 0 && pSarge->common.nStrength < 8000); // prove we are valid

	if (!pAvatar) 
	{
		ItemUpdatePosition((ITEM*)pSarge,&pSarge->common.position); // to keep pads correct
		return;
	}
	ASSERT( (pSarge->common.nStrength && pSarge->common.position.x) || pSarge->common.nStrength == 0);

	pAvatar = pSarge->pAvatar;

	if( pSarge->invulnerableTimer > 0 )
	{
		pSarge->invulnerableTimer -= gpGame->dwDeltaTime;
		if( pSarge->invulnerableTimer < 0 )
			pSarge->invulnerableTimer = 0;
	}

	// handle sarge dying
	int dead = FALSE;
	switch (pSarge->pendingAction)
	{
        case AVATAR_DIE_MELT:
        case AVATAR_DIE_SHOT:
        case AVATAR_DIE_SQUASH:
            if (AvatarLastCompleted(pSarge->pendingAction,pAvatar))
				dead = TRUE;
			break;
        case AVATAR_DIE_EXPLODE:
			dead = TRUE;
	}
	if (dead)
	{
		if (IS_LOCAL_ITEM(pSarge))
			SargeGone(pSarge);
		return;
	}


	if (pSarge->pendingAction == AVATAR_INACTIVATE)	{

        // if sarge is in a vehicle, keep him located with it
        if (pSarge->pVehicle)
        {
            ItemUpdatePosition((ITEM*)pSarge,&(pSarge->pVehicle->common.position));
            // jump avatar as well since normally position comes FROM avatar
            AvatarSetPosition(pSarge->common.position,pSarge->pAvatar);
			ASSERT(pSarge->common.position.x);
			VehicleSoundOn();
        }
		else  ItemUpdatePosition((ITEM*)pSarge,&(pSarge->common.position));
    
        // will pick up even if in a vehicle, since avatar perform (inactive)
        // is called.
		AvatarPerform((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose), pSarge->pendingDirection, TRUE, pAvatar);

		return;
	}

	switch( pSarge->pendingAction )
	{
        case AVATAR_DIE_MELT:
        case AVATAR_DIE_SHOT:
        case AVATAR_DIE_SQUASH:
			AvatarPerform((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose), pSarge->pendingDirection, TRUE, pAvatar);
			goto gotdirection;
		default:
			break;
	}


	if (pSarge->npc)
	{
		SPOINT lands;
		lands = AvatarWouldMoveTo((ACTION)pSarge->pendingAction, AVATAR_STAND,
                                       pSarge->pendingDirection,FALSE,
                                       pAvatar);
		// Test for vehicle in the way of moving sarge
		if (getVehicleOnTile(lands.x >> 4, lands.y >> 4) &&
		(lands.x != pSarge->common.position.x || lands.y != pSarge->common.position.y))
			pSarge->pendingAction = AVATAR_STOP_IMMEDIATELY;


		if (UntrafficableUnit(ENCODE_IPOINT(lands.x,lands.y)))
			pSarge->pendingAction = AVATAR_STOP_IMMEDIATELY;
      
		AvatarPerform((ACTION) (pSarge->pendingAction), (ACTION) AVATAR_STAND, pSarge->pendingDirection, TRUE, pAvatar);

		goto gotdirection;
	}

	bIsSargeIllegal = isSargeUntrafficable(pSarge, pSarge->common.position );

	//  try to go back in the direction we were going before collision.
	if (IS_LOCAL_ITEM(pSarge))
	{	
		if( pSarge->desiredDirection != pSarge->pendingDirection )
		{
			full_pt = AvatarWouldMoveTo( (ACTION)(pSarge->pendingAction),
									(ACTION)(pSarge->pendingPose),
									pSarge->desiredDirection, TRUE, pAvatar);

			if( !isSargeUntrafficable(pSarge,full_pt) )
			{
				frame_pt = AvatarWouldMoveTo( (ACTION)(pSarge->pendingAction),
										(ACTION)(pSarge->pendingPose),
										pSarge->desiredDirection, FALSE, pAvatar);
                if( !isSargeUntrafficable(pSarge,frame_pt) )
                {
                    pSarge->pendingDirection = pSarge->desiredDirection;
					AvatarPerform((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose), pSarge->pendingDirection, TRUE, pAvatar);
                    goto gotdirection;
                }
			}
		}
	}

	if( cheat_move || bIsSargeIllegal )
	{
		full_pt = AvatarWouldMoveTo((ACTION) (pSarge->pendingAction), 
									(ACTION)(pSarge->pendingPose),
									pSarge->pendingDirection, TRUE, pAvatar);
		if (!InRect(&the_map.sargeboundrect,&full_pt))
		{
			goto dorealmove;
		}
		AvatarPerform((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose), pSarge->pendingDirection, TRUE, pAvatar);
		TRACE("untrafficable\n");
	}
	else
	{
dorealmove:
		// check Sarge's next step
		frame_pt = AvatarWouldMoveTo( (ACTION)(pSarge->pendingAction),
									(ACTION)(pSarge->pendingPose),
									pSarge->pendingDirection, FALSE, pAvatar);
	    if( isSargeUntrafficable(pSarge,frame_pt) )	
		{
			int tempdirection, i, oldaction, olddirection, oldpose;

			oldaction = pSarge->pendingAction;
			olddirection = pSarge->pendingDirection;
			oldpose = pSarge->pendingPose;

			// we're about to run into an obstacle in the middle of an animation
			// so cut the animation short
			SargeSetAvatar(pSarge, AVATAR_STOP_IMMEDIATELY);
			AvatarPerform((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose), pSarge->pendingDirection, TRUE, pAvatar);

			// try to find a direction sarge can move to "slide" along a diagonal obstruction	
			for (i = 0; i < 4; i++)
			{
				tempdirection = (olddirection+(i%2==0 ? (i/2+1)*16 : 256-(i/2+1)*16)) % 256;

				full_pt = AvatarWouldMoveTo((ACTION) oldaction, (ACTION) oldpose, tempdirection, TRUE, pAvatar);
				if (!isSargeUntrafficable(pSarge,full_pt))
				{
					frame_pt = AvatarWouldMoveTo((ACTION) oldaction, (ACTION) oldpose, tempdirection, FALSE, pAvatar);
					if (!isSargeUntrafficable(pSarge,frame_pt))
					{
						pSarge->pendingDirection = tempdirection;
						pSarge->pendingAction = (ACTION)oldaction;
						pSarge->pendingPose = (ACTION)oldpose;
						AvatarPerform((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose), pSarge->pendingDirection, TRUE, pAvatar);
						break;
					}
				}
			}
		}
		else
		{
			// if his next step is ok, check his next full animation sequence
			full_pt = AvatarWouldMoveTo((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose),
				pSarge->pendingDirection, TRUE, pAvatar);
			if( isSargeUntrafficable(pSarge,full_pt) )	
			{
				int tempdirection, i;

				//find a direction sarge can move to "slide" along a diagonal obstruction	
				for( i = 0; i < 4; i++ )
				{
					tempdirection = (pSarge->pendingDirection+(i%2==0 ? (i/2+1)*16 : 256-(i/2+1)*16)) % 256;

					full_pt = AvatarWouldMoveTo((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose),
											tempdirection, TRUE, pAvatar);
					if (!isSargeUntrafficable(pSarge,full_pt))
					{
						frame_pt = AvatarWouldMoveTo((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose),
												tempdirection, FALSE, pAvatar);
						if (isSargeUntrafficable(pSarge,frame_pt))
							TRACE("trying to move to a point which is ok for an anim but not a step\n");
						pSarge->pendingDirection = tempdirection;
						break;
					}
				}
			}

			AvatarPerform((ACTION) (pSarge->pendingAction), (ACTION) (pSarge->pendingPose), pSarge->pendingDirection, TRUE, pAvatar);
		}
	}

gotdirection:
    pSarge->oldAction = pSarge->action;
    pSarge->oldDirection = pSarge->direction;             
    SPOINT point;
    point = AvatarPosition(pAvatar);
    ItemUpdatePosition((ITEM*)pSarge,&point);
            
    pSarge->action = pSarge->pendingAction;
    pSarge->direction = pSarge->pendingDirection;             
    pSarge->common.facing = AVATAR_FACING(pAvatar);

	// if sarge is carrying a flag, update the flag location so that it gets updated on the stratmap
	if( pSarge->pWeaponItemList[SARGE_WEAPON_SPECIAL] != NULL )
	{
		int sarge_special = pSarge->pWeaponList[SARGE_WEAPON_SPECIAL]->eWeapon;
		if( sarge_special >= ARMY_FLAG && sarge_special <= ARMY_GRAYFLAG )
		{
			ItemUpdatePosition( pSarge->pWeaponItemList[SARGE_WEAPON_SPECIAL], &(pSarge->common.position) );
		}
	}

    // update last viable place in case sarge moves onto blocked tile
    // briefly. Route planner wont like him being on bad tile
    if (!UntrafficableUnit(pSarge->common.tile))
    {
        pSarge->lastLegalPosition = pSarge->common.position;
    }

    // update visibility from sarge

    // sarge now sees foe army elsewhere in unit.cpp code
        
	if (ItemUserVisible(ARMY_PLAYER, pSarge))	{
		ITEM_SET_VISIBLE((ITEM *) pSarge);
	}
	else	{
		ITEM_SET_INVISIBLE((ITEM *) pSarge);
	}

    if (IS_LOCAL_ITEM(pSarge)) 
		SargeUpdateMessageSend(pSarge, FALSE);

	if (pSarge->reset_gun_facing)
		pSarge->gun_facing = pSarge->common.facing;

	WeaponFireUpdate(pSarge->common.pWeapon);

	if (pSarge->npc) SetAISargeView(pSarge);
}


extern int MouseDx;
extern int MouseDy;
extern char MouseOn;
extern char MouseDxRotate;
extern char MouseTurret;

int SargeTurnWait = 130;
int SargeTurnMax = 8;
float MouseSensitivity = 200.0;
float MouseOutsideSensitivity = 1.0 / 2;
int MouseWait = 30;
int BigSargeTurnRate = 40000;
int SmallSargeTurnRate = 16600;
BOOL SargeFineTurn = FALSE;


void SargeTurn(SARGE *pSarge, int turn_command)	
{
	int facing;

	facing = pSarge->desiredDirection;

	switch(turn_command)	
	{
		case LEFT_VEHICLE:
			facing += 8;
			break;
		case RIGHT_VEHICLE:
			facing -= 8;
			break;
	}

	facing = NormalizeFacing(facing);
	facing = (facing >> 3) << 3;					// round facing to eigths
	pSarge->desiredDirection = pSarge->pendingDirection = facing;
	pSarge->reset_gun_facing = TRUE;
}


void SargeGunTurn(SARGE *pSarge, int turn_command)	
{
	static WORD BigSargeFacing = 0;
	WORD TurnAmount;
	
	if( pSarge->reset_gun_facing )
	{
		pSarge->reset_gun_facing = FALSE;
		BigSargeFacing = (pSarge->desiredDirection << 8) + 8;
	}

	if( MouseDx != 0 )
	{
		BigSargeFacing -= (short)(MouseDx * MouseSensitivity);
	}
	else
	{
		if( SargeFineTurn )
			TurnAmount = (short)(gpGame->dwDeltaTime * SmallSargeTurnRate / 1000);
		else
			TurnAmount = (short)(gpGame->dwDeltaTime * BigSargeTurnRate / 1000);
		switch(turn_command)	
		{
			case LEFT_VEHICLE:
				BigSargeFacing += TurnAmount;
				break;
			case RIGHT_VEHICLE:
				BigSargeFacing -= TurnAmount;
				break;
		}
	}

	pSarge->gun_facing = (BigSargeFacing + 8) >> 8;
	pSarge->pendingDirection = pSarge->desiredDirection = pSarge->gun_facing;
}


BOOL SargeMove(SARGE *pSarge)	{
	ACTION pose = AvatarPose(pSarge->pAvatar);
	int temp = 0;

	if (pose == AVATAR_STAND)	{
		if (user_action & DO_ALT)
		{
			if( user_action & DO_DECELERATE )
				SargeDown();
		}
		else if( user_action & DO_ACCELERATE )
		{
			if( user_action & DO_SLOW || ((pSarge->common.pWeapon->eWeapon == ARMY_FLAME_THROWER) && (user_action & DO_FIRE)))
				SargeSetAvatar( pSarge, AVATAR_WALK );
			else
				SargeSetAvatar( pSarge, AVATAR_RUN );
		}
		else
		if( user_action & DO_DECELERATE )
		{
			if (pSarge->common.pWeapon->eWeapon == ARMY_SWEEPER)
  				SargeSetAvatar( pSarge, AVATAR_STAND );
			else	{
				SargeSetAvatar( pSarge, AVATAR_WALK_BACKWARDS );
			}
		}
		else	{
			if( user_action & DO_FIRE )
				SargeSetAvatar( pSarge, AVATAR_READY_FIRE );
			else
				SargeSetAvatar( pSarge, pSarge->pendingPose );
		}
	}
	else	{
		if (user_action & DO_ALT)
			;
		else 
		if( user_action & DO_ACCELERATE || user_action & DO_DECELERATE)	{
			if (pSarge->common.pWeapon->eWeapon == ARMY_MORTAR && (user_action & DO_FIRE))
				;
			else
				switch (pose)	{
					case AVATAR_PRONE:
						pSarge->pendingPose = AVATAR_KNEEL;
						pSarge->setPendingPose = TRUE;
						SargeSetAvatar(pSarge, pSarge->pendingPose);
						return TRUE;
						break;
					case AVATAR_KNEEL:
						pSarge->pendingPose = AVATAR_STAND;
						pSarge->setPendingPose = TRUE;
						SargeSetAvatar(pSarge, pSarge->pendingPose);
						return TRUE;
						break;
				}
		}
		else	{
			if( user_action & DO_FIRE )
				;
			else
				SargeSetAvatar( pSarge, pSarge->pendingPose );
		}
	}

	return FALSE;
}


void SargeDown()
{
	SARGE*	pSarge = SargePointer(ARMY_PLAYER);

	if( !pSarge->pAvatar ) 
		return;								// sarge is pending resurrection

	ACTION	pose = AvatarPose(pSarge->pAvatar);

	switch (pose)	
	{
		case AVATAR_STAND:
			pSarge->pendingPose = AVATAR_KNEEL;
			pSarge->setPendingPose = TRUE;
			break;
		case AVATAR_KNEEL:
			pSarge->pendingPose = AVATAR_PRONE;
			pSarge->setPendingPose = TRUE;
			break;
	}
}


void SargeTalk()
{
	SARGE*	pSarge = SargePointer(ARMY_PLAYER);

	if( !pSarge->pVehicle )	{
		pSarge->pendingPose = AVATAR_TALK;
		pSarge->setPendingPose = TRUE;
	}
}

void SargeEndTalk()
{
	SARGE*	pSarge = SargePointer(ARMY_PLAYER);

	if( !pSarge->pVehicle )	{
		pSarge->pendingPose = AVATAR_STAND;
		pSarge->setPendingPose = TRUE;
	}
}

void SargeDive(SARGE *pSarge)	{
	ACTION pose = AvatarPose(pSarge->pAvatar);

	if( user_action & DO_ALT)	{		// a dive command
		if( user_action & DO_ACCELERATE )
		{
			SargeSetAvatar( pSarge, AVATAR_DIVE );
		}
		else if ( user_action & DO_TURN_RIGHT )
		{
			SargeSetAvatar( pSarge, AVATAR_ROLL_RIGHT );
		}
		else if ( user_action & DO_TURN_LEFT )
		{
			SargeSetAvatar( pSarge, AVATAR_ROLL_LEFT );
		}
	}
}

///========================================================================
//	Function:		GetUserInput()
//
//	Description:
//		Get input from user to control sarge/vehicle
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================
BOOL fire_flag = FALSE;


void GetSargeKbdInput( void )
{
	static SARGE	*pSarge = SargePointer(ARMY_PLAYER);
	ACTION			action;
		
	ASSERT( pSarge != NULL );

	// TBD: modify so that this is never called except in PLAY_SUB_STATE
	// ignore mouse for purposes of sarge control if not in play mode
	if( gpGame->game_substate != PLAY_SUB_STATE )
	{
		MouseDx = 0;
		MouseDy = 0;
		MouseDown0 = FALSE;
		MouseDown1 = FALSE;
	}

	// deal with pose changes
	ACTION pose = AvatarPose(pSarge->pAvatar);

	if (pSarge->common.pWeapon->eWeapon == ARMY_SWEEPER)	{
		if (pSarge->pendingPose == AVATAR_PRONE)
			pSarge->pendingPose = AVATAR_KNEEL;
	}

	if (pose != pSarge->pendingPose)	
	{
		if (pSarge->setPendingPose)	{
			SargeSetAvatar(pSarge, pSarge->pendingPose);
			return;
		}
		else
			pSarge->pendingPose = pose;
	}
	else
		pSarge->setPendingPose = FALSE;


	// determine if we are using fine turning
	if( user_action & DO_FIRE )
	{
		SargeFineTurn = TRUE;
		SargeTurnWait = 300;
	}
	else
	{
		if( SargeFineTurn )					// delay a bit before releasing fine turn
		{
			SargeTurnWait -= gpGame->dwDeltaTime;
			if( SargeTurnWait <= 0 )
			{
				SargeFineTurn = FALSE;
				SargeTurnWait = 0;
			}
		}
	}

	switch( action = (ACTION) pSarge->pAvatar->current_action )
	{
	case AVATAR_RUN:
	case AVATAR_WALK:	
	case AVATAR_WALK_BACKWARDS:
	case AVATAR_SHUFFLE:
		clearFiringBar();

		if (SargeMove(pSarge))
			return;

		SargeDive(pSarge);

		// if firing, overrides pace change!
		if( user_action & DO_FIRE )
		{
			switch( pSarge->common.pWeapon->eWeapon )
			{
				case ARMY_MORTAR:
				case ARMY_MINE:
				case ARMY_EXPLOSIVE_WEAPON:
					SargeSetAvatar( pSarge, AVATAR_KNEEL );
					break;

				case ARMY_GRENADE:
					turnOnFiringBar(BAR_TYPE_GRENADE);
					SargeSetAvatar( pSarge, AVATAR_READY_FIRE );
					break;

				case ARMY_BAZOOKA:
				case ARMY_RIFLE:
					SargeSetAvatar( pSarge, AVATAR_READY_FIRE );
					break;

				case ARMY_AUTORIFLE:
				case ARMY_FLAME_THROWER:
				case ARMY_SWEEPER:
					SargeSetAvatar(pSarge, AVATAR_FIRE_NOW);
					pSarge->previous_state = action;
					break;

				default: 
					SargeSetAvatar(pSarge, AVATAR_KNEEL);
					break;
			}
		}
		break;

	case AVATAR_STOP_IMMEDIATELY:
	case AVATAR_STAND:
	case AVATAR_TALK:
	case AVATAR_KNEEL:
	case AVATAR_PRONE:
		if (SargeMove(pSarge))
			return;
		SargeDive(pSarge);

		if( user_action & DO_FIRE )
		{
			if (pSarge->common.pWeapon->bTrueWeapon)	{
				fire_flag = TRUE;
				pSarge->reset_gun_facing = FALSE;
				SargeSetAvatar(pSarge, AVATAR_READY_FIRE);
				pSarge->previous_state = action;

				switch(pSarge->common.pWeapon->eWeapon)
				{
					case ARMY_MORTAR:
						turnOnFiringBar(BAR_TYPE_MORTAR);
						break;
					case ARMY_GRENADE:
						SargeSetAvatar( pSarge, AVATAR_READY_FIRE );
						turnOnFiringBar(BAR_TYPE_GRENADE);
						break;
				}
			}
			else	{
				if (WeaponFireTime(pSarge->common.pWeapon))
				{
					SargeFireWeapon(pSarge);
					WeaponFireReset(pSarge->common.pWeapon);
					switch(pSarge->common.pWeapon->eWeapon)
					{
						case ARMY_MEDPACK:
							SargeSetAvatar(pSarge, AVATAR_KNEEL);
							break;
					}
				}
			}
		}
		break;

	case AVATAR_READY_FIRE:				// get ready to fire command
		if (SargeMove(pSarge))
			return;
		SargeDive(pSarge);

		if( user_action & DO_FIRE )
		{
			fire_flag = TRUE;

			if( WeaponSingleShot(pSarge->common.pWeapon) )	{
				SargeSetAvatar( pSarge, AVATAR_READY_FIRE );
			}
			else	{
				SargeSetAvatar( pSarge, AVATAR_FIRE_NOW );
			}

			pSarge->previous_state = AVATAR_READY_FIRE;
		}
		else	{
			SargeSetAvatar( pSarge, AVATAR_FIRE_NOW ); 
			if( fire_flag )
			{
				switch( pSarge->common.pWeapon->eWeapon )
				{
					case ARMY_MORTAR:
					case ARMY_GRENADE:
						WeaponDistancePercentage(pSarge->common.pWeapon, turnOffFiringBar());
					break;

					default: 
						WeaponDistancePercentage(pSarge->common.pWeapon, 100);
					break;

				}
			}
		}
		break;

	case AVATAR_FIRE_NOW:
		if ( fire_flag )	{
			SargeSetAvatar(pSarge, action);
		}
		else
		{
			turnOffFiringBar();
			SargeSetAvatar( pSarge, pSarge->previous_state );
			SargeMove(pSarge);
			SargeDive(pSarge);
		}
		break;

	case AVATAR_DIVE:
	case AVATAR_ROLL_LEFT:
	case AVATAR_ROLL_RIGHT:
		SargeSetAvatar( pSarge, pSarge->pendingPose );	// go stationary
		SargeDive(pSarge);
		break;

	case AVATAR_INVISIBLE:
		break;

	default:
		TRACE("sarge state not used\n");
		ASSERT(0);
		break;
	}

	// handle any keyboard ui related to direction separately
	if( (MouseDx != 0) || ((MouseDy != 0) && (!MouseDxRotate)) )
	{
		if( pSarge->count >= MouseWait )	
		{
			pSarge->count = 0;
			SargeGunTurn(pSarge, LEFT_VEHICLE);
		}
	}
	else if (user_action & DO_ALT)
		;
	else if( user_action & DO_TURN_LEFT )	
	{
		pSarge->count = 0;
		if( user_action & DO_FIRE )
			SargeGunTurn( pSarge, LEFT_VEHICLE );
		else
			SargeGunTurn(pSarge, LEFT_VEHICLE);
	}
	else if( user_action & DO_TURN_RIGHT )	
	{
		pSarge->count = 0;
		if( user_action & DO_FIRE )
			SargeGunTurn( pSarge, RIGHT_VEHICLE );
		else
			SargeGunTurn(pSarge, RIGHT_VEHICLE);
	}

//	if( user_action & DO_FIRE )
//		;
//	else
//		clearFiringBar();
}


void UpdatePosing( void )
{
	static SARGE	*pSarge = SargePointer(ARMY_PLAYER);
		
	ASSERT( pSarge != NULL );

	if( !(pSarge->pAvatar) )
		return;

	// deal with pose changes
	ACTION pose = AvatarPose(pSarge->pAvatar);

	if (pose != pSarge->pendingPose && pSarge->setPendingPose)	
	{
		SargeSetAvatar(pSarge, pSarge->pendingPose);
	}
	else
		pSarge->setPendingPose = FALSE;
}


void GetUserInput( void )
{
	static ARMY_TYPE	eArmy = ARMY_PLAYER;
	static SARGE		*pSarge = &Armies[ eArmy ].Legion.Sarge;

	if( Player0IsAI() )							// we are under ai control
		return;
    if( pSarge->npc )							// different kind of ai control
		return;
	if( UI_CurMode == UIMODE_SCROLLING || UI_CurMode == UIMODE_PLACINGITEM )	{ // we aren't controlling sarge
		UpdatePosing();
		return;
	}
    if( pSarge->common.nStrength == 0 )			// you can't control dead sarge
		return;

	pSarge->count += gpGame->dwDeltaTime;		// turning counter

	if( MouseDown0 )
		user_action |= DO_FIRE;

	if( MouseDown1 && UseAltMouseButton)
		user_action |= DO_ACCELERATE;

	if (pSarge->pVehicle)						// sarge is in a vehicle
	{
		GetVehicleInput( (VEHICLE *)pSarge->pVehicle );
		return;
	}

	GetSargeKbdInput();
}


///========================================================================
//	Function:		SargeInitWeapons
//	Description:	apply a weapon to sarge
///========================================================================

static void	SargeInitWeapons( SARGE* pSarge )
{
    WEAPON* pWeapon;
	WEAPON_TYPE eWeapon = (WEAPON_TYPE) AIinfo.vehicleTables[ ARMY_COMMANDER ].weapons.eWeapon1;

	if( !pSarge->pWeaponList[SARGE_WEAPON_PRIMARY] )
	{
		pWeapon = MakeWeapon(&pSarge->primary_weapon,eWeapon,
			    AIinfo.vehicleTables[ ARMY_COMMANDER ].ammo.nAmmo1);
		pSarge->pWeaponList[SARGE_WEAPON_PRIMARY] = pWeapon;
		SetWeaponOwner(pWeapon, (ITEM *)pSarge);
	}
	pSarge->pWeaponList[SARGE_WEAPON_SECONDARY] = NULL;
	pSarge->pWeaponList[SARGE_WEAPON_SPECIAL] = NULL;
	pSarge->pWeaponItemList[SARGE_WEAPON_SECONDARY] = NULL;
	pSarge->pWeaponItemList[SARGE_WEAPON_SPECIAL] = NULL;

	pSarge->common.pWeapon = pSarge->pWeaponList[SARGE_WEAPON_PRIMARY];
}

void SargeFiringPosition(SARGE* pSarge, SPOINT *pt)
{
	ANIM	*pAnim;
    pt->x = pSarge->common.position.x;
    pt->y = pSarge->common.position.y;
    
    // if sarge has not died, include avatars pose 
    if( pSarge->pAvatar && ((ITEM *)(pSarge))->pWeapon )
    {
        pAnim = pSarge->pAvatar->pAnimation;

		switch( ((ITEM *)(pSarge))->pWeapon->eWeapon )
		{
		case ARMY_MINE:
            double radians,degrees;
            degrees = (((double) pSarge->common.facing * 360) / CIRCLE_UNITS) + 90;
            radians = (degrees * 3.1415926535) / 180;
            if (degrees<=90 || degrees > 270)
                radians = atan2(tan(radians),1);
            else 
                radians = atan2(-tan(radians),-1);
            pt->x = (short)((cos(radians) * 36) + pSarge->common.position.x);
            pt->y = (short)((-sin(radians) * 36) + pSarge->common.position.y);
			break;
		default:
			pt->x += (short)(pAnim->pFrame[pAnim->current_frame].secondary_hotspot.x);
			pt->y += (short)(pAnim->pFrame[pAnim->current_frame].secondary_hotspot.y);
			break;
		}
    }
}


void SargeNoFireWeapon(SARGE* pSarge)
{
    if (IS_LOCAL_ITEM(pSarge))	{
		fire_flag = FALSE;
	}
}


int FastGetDir( SPOINT &from, SPOINT &to, int dist )
{
	int dy, dx;
	int dir;

	dx = to.x - from.x;
	dy = to.y - from.y;
	dir = arc_sin_table[(int)((double)dy/(double)dist * 100.0) + 100];
	if( (dx > 0) && (dir > 0) )
		dir = 256 - dir;

	return( dir );
}


// return distance if pItem is on a line from pt, direction (-1 fails)
/*
int isOnLine( SPOINT &pt, int direction, ITEM *pItem )
{
	int dir, dist;

	dist = GetDistance( &pt, &pItem->position );
	dir = FastGetDir( pt, pItem->position, dist );
	if( abs(dir-direction) < 16 )
		return dist;
	return -1;
}
*/


// return the fire height for the local sarge
static int GetSargeFireHeight( SARGE* pSarge )
{
	int i, n;
	int height, sargeheight;
	IPOINT set[1000];
	IPOINT to;
	SPOINT frompt, destpt;

	sargeheight = GetElevationHeightAtItem( (ITEM*)pSarge );	// default to our elevation height
	destpt.x = pSarge->common.position.x + 
		(short)(cos_table[pSarge->common.fireDirection] * (float)pSarge->common.fireDistance);
	destpt.y = pSarge->common.position.y + 
		(short)(sin_table[pSarge->common.fireDirection] * (float)pSarge->common.fireDistance);
	frompt = pSarge->common.position;
	if( !ClipLine( frompt, destpt, the_map.boundrect ) )
		return sargeheight;

	to = IPOINT_FROM_SPOINT(destpt);
	n = TileLine( pSarge->common.tile, to, set );

	for( i = 0; i < n; i++ )					// walk the tile line, search for targets
	{
		ITEM *pItemList;
		int eArmy;
		SPOINT pt;

		pt.x = SPOINT_FROM_IPOINT_X(set[i]) + 8;
		pt.y = SPOINT_FROM_IPOINT_Y(set[i]) + 8;

		UseRectIntersect = 1;
		pItemList = GetObjectsIntersectPointInLayer( &pt, the_map.orderedlayer, NULL );
		while( pItemList )
		{
			switch( ITEM_TYPE(pItemList) )
			{
			case ARMY_TROOPER:
			case ARMY_SARGE:
			case ARMY_ASSET:
			case ARMY_VEHICLE:
				eArmy = ITEM_ARMY(pItemList);
				if( eArmy != ARMY_PLAYER && !ArmyHaveAllianceWith(ARMY_PLAYER, (ARMY_TYPE)eArmy) )
				{
					int eheight, myheight;

					eheight = GetElevationHeightAtItem( (ITEM *)(pItemList) );
					myheight = GetItemHeight( (ITEM *)(pSarge) );
					height = eheight + 1;
					if( height > myheight + 4 )
						height = myheight + 4;
					UseRectIntersect = 0;
					return( height );
				}
				break;
			}
			pItemList = pItemList->next;
		}
	}

	UseRectIntersect = 0;
	return sargeheight;
}


///========================================================================
//	Function:		SargeFireWeapon
//	Description:	The sarge weapon animation fired, now we actually fire
///========================================================================

void SargeFireWeapon(SARGE* pSarge)
{
	SPOINT	pt;

    if (IS_LOCAL_ITEM(pSarge))	{
		fire_flag = FALSE;
	}

    ItemMakeVisible(pSarge);

	SargeFiringPosition(pSarge, &pt);

	if( pSarge->common.pWeapon->eWeapon == ARMY_SWEEPER )
		;	// do nothing for now
	if( pSarge->common.pWeapon->eWeapon == ARMY_MEDPACK )
	{
		if( pSarge->common.nStrength >= pSarge->common.nMaxStrength )
			return;
		int amt;

		if (ITEM_ARMY(pSarge) == ARMY_PLAYER)
			MsgBroadcast( HEAL_SARGE );

		amt = (int)pSarge->common.nMaxStrength * (int)pSarge->common.pWeapon->nDamage / 100;
		pSarge->common.nStrength += amt;
		if( pSarge->common.nStrength > pSarge->common.nMaxStrength )
			pSarge->common.nStrength = pSarge->common.nMaxStrength;
	}
	else if( pSarge->common.pWeapon->eWeapon == ARMY_FLAME_THROWER )
		FireWeapon((ARMY_TYPE)ITEM_ARMY(pSarge), pSarge->common.pWeapon, &pt, 0,
			        pSarge->gun_facing, pSarge->pAvatar->pAnimation->velocity, 
					pSarge->fireHeight, ITEM_UID(pSarge) );
	else
		FireWeapon((ARMY_TYPE)ITEM_ARMY(pSarge), pSarge->common.pWeapon, &pt, 
					GetItemHeight((ITEM *)pSarge) + 1,
			        pSarge->common.fireDirection, pSarge->common.fireDistance, pSarge->fireHeight, 
					ITEM_UID(pSarge) );

    pSarge->fireIndex = 0;

	// reduce ammo & drop weapon if used up
    // ammo is set to -1 if infinite
    if (IS_LOCAL_ITEM(pSarge) && pSarge->common.pWeapon->nAmmo > 0 )
	{
		pSarge->common.pWeapon->nAmmo--;
		if( pSarge->common.pWeapon->nAmmo <= 0 )
		{
            SargeDropWeapon(pSarge,pSarge->common.position,
                (SARGE_WEAPON)SargeGetActiveWeapon(ITEM_ARMY(pSarge)));
		}
	}
}


void SargeSetFire(SARGE *pSarge, int facing)
{
	SET_WEAPON set_weapon;

	set_weapon = SetFireWeapon(pSarge->common.pWeapon, &pSarge->common.position, pSarge->gun_facing, pSarge->pTarget);

	pSarge->common.fireDirection = set_weapon.direction;
	pSarge->common.fireDistance = set_weapon.distance;
    pSarge->fireIndex = pSarge->common.pWeapon->eWeapon; // what is he trying to fire
	switch( pSarge->common.pWeapon->eWeapon )
	{
	case ARMY_AUTORIFLE:
	case ARMY_RIFLE:
	case ARMY_BAZOOKA:
		pSarge->fireHeight = GetSargeFireHeight(pSarge);
		break;
	case ARMY_FLAME_THROWER:
		pSarge->fireHeight = GetElevationHeightAtItem( (ITEM *)pSarge ) + 5;
		break;
	default:
		pSarge->fireHeight = GetElevationHeightAtItem( (ITEM *)pSarge );
		break;
	}
	
}


///========================================================================
//	Function:		SargeDamage
//	Description:	Hit sarge with damage
///========================================================================
extern BOOL sfxInPlay( ULONG nSndID );

int die_snds[DIE_SOUNDS] = 
	{TROOPER_DIE1,TROOPER_DIE2,TROOPER_DIE3,TROOPER_DIE4,
	TROOPER_DIE5,TROOPER_DIE6,TROOPER_DIE7,TROOPER_DIE8};

void 	SargeDamage(SARGE* pSarge, int nDamageToDo, int nDamageType, SPOINT* pFrom,UID fromUID)
{
	int oldstrength;
	int die;
	int originaldamage;
	originaldamage = nDamageToDo;

    if( pSarge->invulnerableTimer != 0 )
		return;

    if (pSarge->common.nStrength == 0) 
		return;

    if (! pSarge->pAvatar) 
		return;

	switch (nDamageType)	{
		case DMGTYPE_BULLET:
			AudioPlayItem(BULLET_HIT_SARGE, (ITEM *)pSarge);
			if( rand() & 01 )
				MakeChips( *pFrom, pSarge->pAvatar->pAnimation->trans_table, 0 );
			break;
		case DMGTYPE_GRENADE:
		case DMGTYPE_MORTAR:
		case DMGTYPE_BAZOOKA:
		case DMGTYPE_MISSILE:
		case DMGTYPE_OTHER_EXPLOSION:
		case DMGTYPE_FLAMED:
			if (!sfxInPlay(pSarge->flameSndId))
				pSarge->flameSndId = AudioPlayItem(FLAME_HIT_TROOPER, (ITEM *)pSarge);
			break;
	}

    if (!IS_LOCAL_ITEM(pSarge)) // tell remote sarge he is hit
    {
 		SargeDamageMessageSend(pSarge, nDamageToDo, nDamageType, pFrom,fromUID);
		return;
    }

	// this is used only for one player
    if( sargeInvulnerable[ITEM_ARMY(pSarge)] != 0 || (ITEM_ARMY(pSarge) == ARMY_PLAYER && sargeImmune))
		return;

	// if sarge is prone, he takes less damage
	if( pSarge->pAvatar )
	{
		if( AvatarPose(pSarge->pAvatar) == AVATAR_PRONE )
		{
			int reduced;
			reduced = originaldamage >> 3;	// 12.5% will be removed
			// if 12.5% is 0, consider randomly removing all damage
			if (!reduced && randInt(0,7) == 1) reduced = originaldamage;
 			nDamageToDo -= reduced;
		}
		// if he did a dive, change odds varyingly
		if( AvatarInAir( pSarge->pAvatar ) )
		{
			switch( rand() & 7 )
			{
			case 0:
				nDamageToDo = nDamageToDo << 1;		// 200%
				break;
			case 1:
			case 2:
				break;
			case 3:
			case 4:
				nDamageToDo -= nDamageToDo >> 2;	// 25% removed
				break;
			case 5:
			case 6:
				nDamageToDo -= nDamageToDo >> 1;	// 50% removed
				break;
			case 7:
				nDamageToDo = nDamageToDo >> 2;		// 75% removed
				break;
			}
		}
	}


    // damage the sarge no worse than dead
	oldstrength=pSarge->common.nStrength;
    if (pSarge->common.nStrength < nDamageToDo)
        nDamageToDo = pSarge->common.nStrength;

    pSarge->common.nStrength -= nDamageToDo;

	DamageItemTriggerEvents((ITEM*)pSarge, oldstrength, pSarge->common.nStrength, pSarge->common.nMaxStrength);

    // if he dies... set him to die
    if (pSarge->common.nStrength == 0)
    {
		ACTION deathAction;

		// choose death action
		if( pSarge->common.pWeapon && pSarge->common.pWeapon->eWeapon == ARMY_FLAME_THROWER )
		{
			switch( nDamageType )
			{
			case DMGTYPE_RUNOVER:
			case DMGTYPE_STRUCTURAL:
				deathAction = AVATAR_DIE_SQUASH;
				break;
			case DMGTYPE_GRENADE:
			case DMGTYPE_MORTAR:
			case DMGTYPE_BAZOOKA:
			case DMGTYPE_MISSILE:
			case DMGTYPE_OTHER_EXPLOSION:
			case DMGTYPE_FLAMED:
				deathAction = AVATAR_DIE_MELT;
				DoExplosion( pSarge->common.position.x, pSarge->common.position.y, 
					EXPLOSION_FLASH_COMBUSTION_M_COMMAND, &MediumExplosion, 
					DMGTYPE_OTHER_EXPLOSION, 15, NULL, TRUE, fromUID, BARREL_EXPLODE );
				break;
			case DMGTYPE_BULLET:
			default:
				deathAction = AVATAR_DIE_SHOT;
				break;
			}
		}
		else
		{
			switch( nDamageType )
			{
			case DMGTYPE_RUNOVER:
			case DMGTYPE_STRUCTURAL:
				deathAction = AVATAR_DIE_SQUASH;
				break;
			case DMGTYPE_OTHER_EXPLOSION:
			case DMGTYPE_GRENADE:
			case DMGTYPE_MORTAR:
				switch( rand() & 3 )
				{
				case 0:
				case 1:
					deathAction = AVATAR_DIE_EXPLODE;
					break;
				case 2:
					deathAction = AVATAR_DIE_MELT;
					break;
				case 3:
					deathAction = AVATAR_DIE_SHOT;
					break;
				}
				break;
			case DMGTYPE_FLAMED:
				deathAction = AVATAR_DIE_MELT;
				break;
			case DMGTYPE_BAZOOKA:
			case DMGTYPE_MISSILE:
			case DMGTYPE_BULLET:
			default:
				if( rand() & 1 )
					deathAction = AVATAR_DIE_SHOT;
				else
					deathAction = AVATAR_DIE_EXPLODE;
				break;
			}
		}

		switch (deathAction)	{
			case AVATAR_DIE_EXPLODE:
			case AVATAR_DIE_SHOT:
			case AVATAR_DIE_MELT:
				die = rand() % DIE_SOUNDS;
				AudioPlayItem(die_snds[die], (ITEM *)pSarge);
				break;

			case AVATAR_DIE_SQUASH:
				AudioPlayItem(SQUASH_SARGE, (ITEM *)pSarge);
				break;
		}

		// he dies aimed toward where hit
		int facing = GetDirection( &pSarge->common.position, pFrom );

		if( facing == -1 )			
			facing = pSarge->common.facing;

		SargeSetAvatar( pSarge, deathAction );
		pSarge->pendingDirection = facing;

		int killerArmy = EXTRACT_ARMY(fromUID);
        SargeDie(pSarge, killerArmy);

		if (ITEM_ARMY(pSarge) == ARMY_PLAYER)
			SndSetVolumePercent(pSarge->healthSndId, 0, FALSE);
    }
	else	{	// still alive
		if (ITEM_ARMY(pSarge) == ARMY_PLAYER)
		{
			int nOldPercent = (oldstrength * 100) / pSarge->common.nMaxStrength;
			int nNewPercent = (pSarge->common.nStrength * 100) / pSarge->common.nMaxStrength;
			if ((nOldPercent > 35) && (nNewPercent <= 35) && (nNewPercent > 5))
				pSarge->healthSndId = MsgBroadcast( SARGE_LOW_HEALTH );
		}
	}
}


///========================================================================
//	Function:		SargeDie
//	Description:	start him on the road to death, his animation runs
///========================================================================
void SargeDie(SARGE* pSarge, int killerArmy)
{
	pSarge->common.nStrength = 0;	// to insure remote death has 0 strength so
							// host wont think you can pick up anything
	
	pSarge->seeksWeapon = 0;   // not hunting for anything now
	if (IS_LOCAL_ITEM(pSarge)) 
	{
        SargeDeathMessageSend(pSarge, killerArmy);//send death over the network.
		if (ITEM_ARMY(pSarge) == ARMY_PLAYER)
			UI_CurMode = UIMODE_LOOKINGATSARGE;
	}

	if( killerArmy >= 0 )
	{
		Armies[killerArmy].sarges_killed[ITEM_ARMY(pSarge)]++;
		Armies[ITEM_ARMY(pSarge)].sarges_killedby[killerArmy]++;
		pSarge->killerarmyindex = killerArmy;
	}
	else
	{
		Armies[ITEM_ARMY(pSarge)].sarges_killedby[ITEM_ARMY(pSarge)]++;
		TRACE( "Sarge killed by unknown source! - Assigned to himself.\n" );
		pSarge->killerarmyindex = ITEM_ARMY(pSarge);
	}

    pSarge->pVehicle = NULL; // just in case

	// generate body parts as necessary
	if( pSarge->pendingAction == AVATAR_DIE_SHOT &&
		AvatarPose(pSarge->pAvatar) == AVATAR_STAND )
	{
		ShotDeathStandParts( pSarge->common.position, pSarge->pendingDirection, pSarge->pAvatar->pAnimation->trans_table );
	}

    TRACE("    %s died.",ItemDBName(pSarge));
	/*
	if( killerArmy < 0 )					// just in case killerArmy is an invalid index
		killerArmy = 0;
    pSarge->killerarmyindex = gpComm->IndexFromColor((ARMY_COLOR)killerArmy );
	*/
    // release any special you have
    SargeDropWeapon(pSarge, pSarge->common.position, (SARGE_WEAPON)2);
    SargeDropWeapon(pSarge, pSarge->common.position, (SARGE_WEAPON)1);

    if (pSarge->common.pTad)
    {
		UnitValidateTad(); // just test the hell out of the links
        TadDeleteObject((TAD*)pSarge->common.pTad);
        pSarge->common.pTad = NULL;
		UnitValidateTad(); // just test the hell out of the links
    }
}

///========================================================================
//	Function:		SargeGone
//	Description:	delete sarge 
///========================================================================

void SargeGone(SARGE* pSarge)
{
    SPOINT pos;
	AVATAR *pAvatar;
    TRACE("    Sarge erased.");
    if (IS_LOCAL_ITEM(pSarge)) SargeGoneMessageSend(pSarge);
    pSarge->pVehicle = NULL; // just in case
    

	pAvatar = pSarge->pAvatar;
	ASSERT(pAvatar);
	switch (pSarge->pendingAction)
	{
        case AVATAR_DIE_MELT:
        case AVATAR_DIE_SHOT:
        case AVATAR_DIE_SQUASH:
            if (AvatarLastCompleted(pSarge->pendingAction,pAvatar))
				InsertAnimInCorpseLayer( pAvatar->pAnimation );
			else
				GenerateExplodingAvatar( pAvatar );
			break;
        case AVATAR_DIE_EXPLODE:
		default:
			GenerateExplodingAvatar( pAvatar );
			break;		
	}


	ARMY_TYPE eArmy = ITEM_ARMY(pSarge);

	pSarge->deadPosition = pSarge->common.position;

	// if sarge was on a pad, updatepad will detect him leaving
	// then we update again, so both present and past show him off the map.
	// that way if an event resurrects him, he will detect going on the pad.
	ItemSpecialUpdatePosition((ITEM*)pSarge, &OFF_THE_MAP);

    pos = pSarge->deployPosition;
    SargeDelete(pSarge);
    pSarge->lastLegalPosition = OFF_THE_MAP; // he isnt legal anymore


	if (ITEM_ARMY(pSarge) == ARMY_PLAYER)
		UI_CurMode = UIMODE_LOOKINGATSARGE;

    // now that he is truly dead, trigger the dead events

	DiedItemTriggerEvents((ITEM*)pSarge);

    if (pSarge->common.eventNum)
        EventTrigger(EVENT_KILLEDSARGE,
            GetKillerEventNum(pSarge->common.eventNum,pSarge->killerarmyindex),
            ITEM_UID(pSarge),0,0);
}

///========================================================================
//	Function:		SargeUndeploy
///========================================================================

void	SargeUndeploy( ARMY_TYPE eArmy )
{
    SARGE*	pSarge = SargePointer(eArmy);
    if (IS_LOCAL_ITEM(pSarge))
        SargeVehicleMessageSend(pSarge,0, 3);

	pSarge->pVehicle = NULL;
	ItemSpecialUpdatePosition((ITEM*)pSarge, &OFF_THE_MAP); 
	ItemFreeLabel((ITEM *)pSarge);
    SargeDelete(pSarge);
}


///========================================================================
//	Function:		AutoTuneStrength
///========================================================================

void AutoTuneStrength(SARGE *pSarge, BOOL nomax)
{
	unsigned char failures = ArmyMissionFailures();

	// TBD: put these values in the aai file
	if (failures > 9 )	{
		if (!nomax)
			pSarge->common.nMaxStrength += pSarge->common.nMaxStrength*2;
		pSarge->common.nStrength += pSarge->common.nStrength*2;
	}
	else if (failures > 7 )	{
		if (!nomax)
			pSarge->common.nMaxStrength += (pSarge->common.nMaxStrength*3) / 2;
		pSarge->common.nStrength += (pSarge->common.nStrength*3) / 2;
	}
	else if (failures > 5 )	{
		if (!nomax)
			pSarge->common.nMaxStrength += pSarge->common.nMaxStrength;
		pSarge->common.nStrength += pSarge->common.nStrength;
	}
	else if (failures > 3 )	{
		if (!nomax)
			pSarge->common.nMaxStrength += pSarge->common.nMaxStrength / 2;
		pSarge->common.nStrength += pSarge->common.nStrength / 2;
	}

	pSarge->common.nStrength = min(pSarge->common.nStrength, pSarge->common.nMaxStrength);
}


///========================================================================
//	Function:		SargeInitialDeploy
///========================================================================

void	SargeInitialDeploy( SARGE*	pSarge, SPOINT *pPos, short facing, VEHICLE *pVehicle )
{
	int		eArmy = ITEM_ARMY(pSarge);

    if (eArmy != ARMY_PLAYER && gpGame->GameType == GAMETYPE_ONEPLAYER)
        pSarge->npc = 1;

	IPOINT tile = ENCODE_IPOINT(pPos->x,pPos->y);
	if (isSargeUntrafficable(pSarge,*pPos) && !pVehicle)
    {
      ErrorDebug("!*!*! %s deployed illegally at %d.%d\n",ItemDBName(pSarge),
          pPos->x,pPos->y);
      tile = (IPOINT)ItemFanOut((ITEM*)pSarge,tile,10,UnitSafeDeploy);
	  pPos->x = (IPOINT_X(tile) << 4) + 8;
	  pPos->y = (IPOINT_Y(tile) << 4) + 8;
      if (!pPos->x) return;
      TRACE("!*!*! %s relocatd to %d.%d\n",ItemDBName(pSarge),
          pPos->x,pPos->y);
    }   
    else TRACE("    %s deploying to %d.%d \n", ItemDBName(pSarge),
		pPos->x,pPos->y);

    // note sarge is invulnerable for 5 seconds at start of ANYTHING, even
    // single player
    pSarge->invulnerableTimer = 5000; // he will be invulnerable
        
    // initialize weapon subcomponents
	SargeInitWeapons(pSarge);

	pSarge->common.seen[ARMY_PLAYER] = -1;
	pSarge->common.seen[ARMY_PLAYER_2] = -1;
	pSarge->common.seen[ARMY_PLAYER_3] = -1;
	pSarge->common.seen[ARMY_PLAYER_4] = -1;

	short strength = AIinfo.vehicleTables[ARMY_COMMANDER].nHitPoints;
	pSarge->common.nStrength = pSarge->common.nMaxStrength = strength;

	AutoTuneStrength(pSarge);

	AVATAR* 	pAvatar = 	AvatarCreate(ITEM_UID(pSarge));
	pSarge->pAvatar = pAvatar;
	AnimSetOwner(pAvatar->pAnimation, pSarge);
    // update location, PAD,FOG
	AvatarSetPosition(*pPos, pAvatar);

	ItemUpdatePosition((ITEM*)pSarge,pPos);		

    pSarge->action = pSarge->oldAction = AVATAR_STAND;
    pSarge->pendingPose = AVATAR_STAND;
    pSarge->setPendingPose = TRUE;
	pSarge->pendingDirection = facing;
	pSarge->common.facing = pSarge->pendingDirection;
	pSarge->gun_facing = pSarge->common.facing;
	pSarge->reset_gun_facing = TRUE;
	SargeSetAvatar(pSarge, AVATAR_STAND);

    // last ok location
    pSarge->lastLegalPosition = pSarge->common.position;

    // put sarge into tad world
	ASSERT(!pSarge->common.pTad);
    if ( TadCreateObject((int) eArmy,(int) ARMY_SARGE,(ITEM*)pSarge,(ULONG)0) )
        TRACE("ERROR: failed to create TAD object for sarge. \n");


	See(ITEM_ARMY(pSarge),(ITEM*)pSarge); // give sarge a viewpoint

	// make it seen initially to self
	ItemUpdateSeen((ITEM*)pSarge,(ITEM*)pSarge);

	pSarge->routeData.owner = ITEM_UID(pSarge);

	pSarge->mode = SARGE_DEPLOYED;

	pSarge->flameSndId = SND_NULL_SND_ID;
	pSarge->pickupSndId = SND_NULL_SND_ID;
	pSarge->healthSndId = SND_NULL_SND_ID;
	pSarge->arrivalEvent = EVENT_NUM_UNDEFINED;
	ASSERT(pSarge->common.position.x);

	if (pVehicle)	{
		SargeInVehicle(pSarge, pVehicle);
		TRACE("    Sarge in vehicle %s\n",ItemDBName(pVehicle) );
	}


}

///========================================================================
//	Function:		SargeDeploy
///========================================================================

void SargeDeploy(SARGE* pSarge,SPOINT* position,short facing)
{
    SargeInitialDeploy(pSarge,position,facing);
    if (IS_LOCAL_ITEM(pSarge))
	{
        SargeVehicleMessageSend(pSarge,0, 2);
		if (ITEM_ARMY(pSarge) == ARMY_PLAYER)
			MapJumpToPoint( pSarge->common.position.x, pSarge->common.position.y );
	}
}

///========================================================================
//	Function:		SargeDeployPosition
///========================================================================


void	SargeDeployPosition( SARGE* pSarge, SPOINT *pPos, short facing)
{
	pSarge->deployPosition = *pPos;
	pSarge->deployFacing = facing;
}

///========================================================================
//	Function:		SargeTeleport
///========================================================================


void	SargeTeleport(SARGE* pSarge,SHORT x,SHORT y)
{
    AVATAR* pAvatar = pSarge->pAvatar;
	SPOINT point;
    point.x = x;
    point.y = y;

    // change position, TAD,PAD,FOG
    ItemSpecialUpdatePosition((ITEM*)pSarge,&point);
	// ItemUpdatePad((ITEM*)pSarge); // since sargeupdate will happen before pad update.
	MapJumpToPoint( pSarge->common.position.x, pSarge->common.position.y );

    // jump avatar as well since normally position comes FROM avatar
    AvatarSetPosition(point,pAvatar);

    // finally update influece
}


///========================================================================
//	Function:		SargeSetAvatar
///========================================================================
extern char* actions[];

inline static void SargeSetAvatar(SARGE* pSarge, ACTION pendingAction)
{
//	if (pSarge->pendingAction == AVATAR_STOP_IMMEDIATELY)
//		TRACE("STOP_IMMEDIATELY to %s\n", actions[pendingAction]);

//	TRACE("%s\n", AvatarActionDBName(pendingAction));
	pSarge->pendingAction = pendingAction;
}


///========================================================================
//	Function:		SargeInVehicle
//========================================================================

void SargeInVehicle( SARGE* pSarge, VEHICLE* pVehicle )
{
    if (pSarge->common.nStrength == 0) return; // not if dead

	// sarge in vehicle
	pSarge->pVehicle = pVehicle;

	// set driver of vehicle
	pVehicle->pDriver = pSarge;

	// inactivate avatar
	SargeSetAvatar(pSarge, AVATAR_INACTIVATE);

    // sarge cannot be targeted or target while in a vehicle
    if (pSarge->common.pTad)
    {
		UnitValidateTad(); // just test the hell out of the links
        TadDeleteObject((TAD*)pSarge->common.pTad);
        pSarge->common.pTad = NULL;
		UnitValidateTad(); // just test the hell out of the links
    }

    if (IS_LOCAL_ITEM(pSarge))
	{
		ActivateSargeWeapon(pSarge, 0);
        SargeVehicleMessageSend(pSarge,pVehicle, TRUE);
	}
}

///========================================================================
//	Function:		SargeOutVehicle
///========================================================================

static long OutOfVehicle(IPOINT at) // find a trafficable place to exit
{
    if (UntrafficableUnit(at)) 
		return 0;
    SPOINT x;
    x.x = IPOINT_X(at) << 4;
    x.y = IPOINT_Y(at) << 4;
    if (isSargeUntrafficable(SargePointer(ARMY_PLAYER),x)) return 0;
    return at;
}

void SargeOutVehicle( SARGE* pSarge )
{
    VEHICLE* pVehicle = pSarge->pVehicle;
    if (!pVehicle) return; // not in one

	ClearVehicleFromVehicleLayer( pVehicle ); // we dont know if it is there
	ReinsertVehicleInVehicleLayer(pVehicle,TRUE); // require vehicle have a mask for now
	// when troopers get out, if it wasnt moveing it will also

    // find non-vehcile tile to be on
    IPOINT out;
    out = (IPOINT)ItemFanOut((ITEM*)pSarge,pSarge->common.tile,8,OutOfVehicle);


  
	SPOINT position;
    position.x = IPOINT_X(out) << 4;
    position.y = IPOINT_Y(out) << 4;
	ASSERT( !isSargeUntrafficable(pSarge,position) );
    AvatarSetPosition(position,pSarge->pAvatar);
	ItemUpdatePosition((ITEM*)pSarge,&position);		
    pSarge->lastLegalPosition = pSarge->common.position;

	// sarge in vehicle
    pVehicle->pDriver = NULL;
	pSarge->pVehicle = NULL;

	// activate avatar
	SargeSetAvatar(pSarge, AVATAR_STAND);

	// make sarge visible
	if( pSarge->pAvatar )
	{
		ANIM *pAnim = pSarge->pAvatar->pAnimation;
		pAnim->flags |= ANIM_FLAG_PREV_INVISIBLE;
		pAnim->flags &= ~ANIM_FLAG_INVISIBLE;
		pAnim->flags |= ANIM_FLAG_ACTIVE;
	}

	ASSERT(!pSarge->common.pTad);
    if ( TadCreateObject(ITEM_ARMY(pSarge),(int) ARMY_SARGE,(ITEM*)pSarge,(ULONG)0) )
        TRACE("ERROR: failed to create TAD object for sarge. \n");

    if (IS_LOCAL_ITEM(pSarge))
    {
		UNIT* pUnit;
		LEGION* pLegion;
		pLegion = ArmyGetLegion(ITEM_ARMY(pSarge));
		 SargeVehicleMessageSend(pSarge, 0, 0);
		FOR_EACH_UNIT(pLegion,pUnit)
		{
			if (pUnit->pVehicle == pVehicle) UnitExitVehicle(pUnit,OFF_THE_MAP,0);
		}
    }

}

int GetSargeAmmo(int whichweapon)	{
    SARGE*	pSarge = SargePointer(ARMY_PLAYER);
	WEAPON* pWeapon = pSarge->pWeaponList[whichweapon];

	if (pWeapon)
		return pWeapon->nAmmo;
	else
		return 0;
}

void SetSargeAmmo(int whichweapon, int ammo)	{
    SARGE*	pSarge = SargePointer(ARMY_PLAYER);
	WEAPON* pWeapon = pSarge->pWeaponList[whichweapon];

	if (pWeapon)
		pWeapon->nAmmo = ammo;
#ifdef _DEBUG
	else
		ASSERT(0);
#endif
}

int GetSargeWeapon(int whichweapon)	{
    SARGE*	pSarge = SargePointer(ARMY_PLAYER);
	WEAPON* pWeapon = pSarge->pWeaponList[whichweapon];

	if (pWeapon)
		return pWeapon->eWeapon;
	else
		return ARMY_NO_WEAPON;
}

  // Note: we need an actual weapon to assign a pointer to
void SetSargeWeapon(int whichweapon, int eWeapon)	{
    SARGE*	pSarge = SargePointer(ARMY_PLAYER);

	if (whichweapon != SARGE_WEAPON_PRIMARY)
		pSarge->pWeaponList[whichweapon];
#ifdef _DEBUG
	else
		ASSERT(0);
#endif
}

void ActivateNextSargeWeapon(SARGE*	pSarge)	{
	int index = pSarge->weapon_index;

	do {
		index++;
		if (index >= SARGE_LAST_WEAPON)
			index = 0;
	}
	while (!ActivateSargeWeapon(pSarge, index));
}

BOOL ActivateSargeWeapon(SARGE*	pSarge, int whichweapon)	{
 	WEAPON* pWeapon = pSarge->pWeaponList[whichweapon];

    // already the active weapon
    if (pSarge->weapon_index == whichweapon) return TRUE;

    // if sarge dies but the host takes a while to send out the drop
    // weapon, sarge may have no avatar when this comes in.
    // so dont tell the avatar (now not existing) to change
	if (pWeapon) {
		pSarge->weapon_index = whichweapon;
		pSarge->common.pWeapon = pWeapon;
		// cannot remotely update someones sarge
		// nor do it if sarge is dead. His resurrection will send an update later
		// so that is good enough. We dont want to send update on a OFF_MAP position.
		if (IS_LOCAL_ITEM(pSarge) && pSarge->common.nStrength)	{
			SargeUpdateMessageSend(pSarge, TRUE);
			AudioPlayItem(WEAPON_ACTIVATE, (ITEM *)pSarge);
		}

		SetSargeAnimType(pSarge);

		return TRUE;
	}

	return FALSE;
}

int SargeGetActiveWeapon(int eArmy)
{
	SARGE *pSarge = SargePointer(eArmy);

	return pSarge->weapon_index;
}

int IsSargeWeaponReady(void)
{
	SARGE *pSarge = SargePointer(ARMY_PLAYER);
	WEAPON *pWeapon;

	if( pSarge->pVehicle )
		pWeapon = ((ITEM *)(pSarge->pVehicle))->pWeapon;
	else
		pWeapon = ((ITEM *)(pSarge))->pWeapon;
	return ( WeaponFireTime( pWeapon ) );
}

///========================================================================
//	Function:		GetSargeHealthPercentage
//	Description:	return the % of damage still available for sarge
///========================================================================

int	GetSargeHealthPercentage()
{
    SARGE*	pSarge = SargePointer(ARMY_PLAYER);

	// get maximum strength
	int nMaxStrength = pSarge->common.nMaxStrength;

	// now calculate the percentage left from the current strength
	int	nPercent = 0;			// assume full health
	if (nMaxStrength)
		nPercent = (((nMaxStrength - pSarge->common.nStrength) * 100) / nMaxStrength);

	// return the percentage remaining
	return( 100-nPercent );
}

int GetVehicleHealthPercentage(void)
{
    SARGE*	pSarge = SargePointer(ARMY_PLAYER);

	if (pSarge->pVehicle)	{
		return VehicleGetDamage(pSarge->pVehicle);
	}
	else
		return 0;
}

void fillAirSupport(void)
{
	LEGION *pLegion = ArmyGetLegion( ARMY_PLAYER );

	pLegion->AirResources[ARMY_RESOURCE_PARATROOPERS]=3;
	pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE]=3;
	pLegion->AirResources[ARMY_RESOURCE_AIR_RECON]=3;
}



int GetNumAirDrops(void)
{
	LEGION *pLegion = ArmyGetLegion( ARMY_PLAYER );

	return pLegion->AirResources[ARMY_RESOURCE_PARATROOPERS];
}

int GetNumAirStrikes(void)
{
	LEGION *pLegion = ArmyGetLegion( ARMY_PLAYER );

	return pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE];
}

int GetNumRecons(void)
{
	LEGION *pLegion = ArmyGetLegion( ARMY_PLAYER );

	return pLegion->AirResources[ARMY_RESOURCE_AIR_RECON];
}

int UseUpAirDrop(int eArmy)
{
	LEGION *pLegion = ArmyGetLegion( eArmy);

	return --pLegion->AirResources[ARMY_RESOURCE_PARATROOPERS];
}

int UseUpAirStrike(int eArmy)
{
	LEGION *pLegion = ArmyGetLegion( eArmy );

	return --pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE];
}


int UseUpRecon(int eArmy)
{
	LEGION *pLegion = ArmyGetLegion( eArmy );

	return --pLegion->AirResources[ARMY_RESOURCE_AIR_RECON];
}

int GetSargeVehicle(void)
{
    SARGE*	pSarge = SargePointer(ARMY_PLAYER);

	if (pSarge->pVehicle)	{
		return ITEM_CLASS(pSarge->pVehicle);
	}
	else
		return ARMY_NO_VEHICLE;
}


int GetSargeQuestItem( void )
{
	SARGE* pSarge = SargePointer( ARMY_PLAYER );

	return( pSarge->questItem );
}

SPOINT AudioPosition()	{
	return (SargePosition(ARMY_PLAYER));
}

inline SPOINT	SargePosition(ARMY_TYPE eArmy)
{
	ITEM *pSarge = (ITEM*)SargePointer(eArmy);

    return (pSarge->position);
}

inline SARGE* SargePointer(int eArmy)
{
	if (eArmy == ARMY_INDEPENDENT) return NULL;
	if (Armies[eArmy].Status == 0) return NULL; // army not there

	LEGION*	pLegion = ArmyGetLegion(eArmy);
	return &pLegion->Sarge;
}

inline SARGE*	SargeFind(LONG nUniqueID)
{
	int eArmy;
	eArmy = EXTRACT_ARMY(nUniqueID);
	if (Armies[eArmy].Status == 0) return NULL; // army not there
	LEGION*	pLegion = ArmyGetLegion(eArmy);
	if (pLegion->Sarge.common.nUniqueID == nUniqueID) return (&pLegion->Sarge);
    else return NULL;
}

inline VEHICLE* SargeVehiclePointer(ARMY_TYPE eArmy)
{
	if (Armies[eArmy].Status == 0) return NULL; // army not there

    SARGE*	pSarge = SargePointer(eArmy);

	return pSarge->pVehicle;
}

void SargeDoDropWeapon( SARGE * pSarge, SPOINT position, SARGE_WEAPON slot )
{
	ITEM *pItem = pSarge->pWeaponItemList[slot];
    if (!pItem) return;
	pSarge->pWeaponItemList[slot] = NULL;
	pSarge->pWeaponList[slot] = NULL;
	if( slot == 0 )
	{
		pSarge->pWeaponItemList[slot] = NULL;
		pSarge->pWeaponList[slot] = &(pSarge->primary_weapon);
	}
	ActivateSargeWeapon(pSarge, 0);

	pSarge->prevPickup = pItem;

	if( pSarge->common.eventNum )
	{
		EventTrigger( EVENT_ITEMDROPPED, 
			GetWeaponPickupOrDropEventNum( pSarge->common.eventNum, pItem->pWeapon->eWeapon ),
			pSarge->common.nUniqueID, 1, 0 );
		if (pItem->eventNum)
			EventTrigger( EVENT_ITEMDROPPED,
				GetSpecificItemPickupEventNum( pSarge->common.eventNum, pItem->eventNum),
				pSarge->common.nUniqueID, 1, 0 );
	}
				

	((OBJECTSTRUCT*) pItem)->xtriggers &= ~XTRIGGER_SARGECARRIED;

	// destroy it now if it is empty
    if (pItem->pWeapon->nAmmo == 0)
	{
        ((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_DESTROYED;
        ((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_UNDEPLOYED;
        ItemSetLocation(pItem,&OFF_THE_MAP);
	}
    // otherwise drop it normally
    else 
    {
        ((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_CHANGED;
        ((OBJECTSTRUCT *)pItem)->triggers &= ~TRIGGER_UNDEPLOYED;
        ItemSetLocation(pItem,&position);
        AnimActivate( (ANIM *)(&((OBJECTSTRUCT *)pItem)->cell), FALSE );
        // to force animsetposition to see a change, change the position now
        ((OBJECTSTRUCT *)pItem)->cell.world_pos.x = 10;
        ((OBJECTSTRUCT *)pItem)->cell.world_pos.y = 10;
        AnimSetPosition( (ANIM *)(&((OBJECTSTRUCT *)pItem)->cell), position.x, position.y, 0 );
		((OBJECTSTRUCT *)pItem)->timer = gpGame->dwAnimTime;
	}
}

///========================================================================
//	Function:		WeaponSlot
//	Description:	where does an item go
///========================================================================

SARGE_WEAPON WeaponSlot(ITEM* pItem)
{
	SARGE_WEAPON slot;
	switch( pItem->pWeapon->eWeapon )
	{
	case ARMY_MEDKIT:
	case ARMY_AIRSTRIKE:
	case ARMY_LURE:
	case ARMY_PARATROOPERS:
	case ARMY_RECON:
	case ARMY_AUTORIFLE:
	case ARMY_SPECIAL_1:
	case ARMY_SPECIAL_2:
	case ARMY_SPECIAL_3:
	case ARMY_SPECIAL_4:
	case ARMY_SPECIAL_5:
	case ARMY_SPECIAL_6:
	case ARMY_SPECIAL_7:
	case ARMY_SPECIAL_8:
	case ARMY_SPECIAL_9:
	case ARMY_SPECIAL_10:
	case ARMY_SPECIAL_11:
	case ARMY_SPECIAL_12:
	case ARMY_SPECIAL_13:
	case ARMY_SPECIAL_14:
	case ARMY_SPECIAL_15:
	case ARMY_SPECIAL_16:
	case ARMY_SPECIAL_17:
	case ARMY_SPECIAL_18:
	case ARMY_SPECIAL_19:
	case ARMY_SPECIAL_20:
	case ARMY_SPECIAL_21:
	case ARMY_SPECIAL_22:
	case ARMY_SPECIAL_23:
	case ARMY_SPECIAL_24:
	case ARMY_SPECIAL_25:
	case ARMY_SPECIAL_26:
	case ARMY_SPECIAL_27:
	case ARMY_SPECIAL_28:
	case ARMY_SPECIAL_29:
	case ARMY_SPECIAL_30:
		slot = SARGE_WEAPON_PRIMARY;
		break;
	case ARMY_EXPLOSIVE_WEAPON:
	case ARMY_MINE:
	case ARMY_DETONATOR:
	case ARMY_GREENFLAG:
	case ARMY_FLAG:
	case ARMY_TANFLAG:
	case ARMY_BLUEFLAG:
	case ARMY_GRAYFLAG:
	case ARMY_MEDPACK:
	case ARMY_SWEEPER:
		slot = SARGE_WEAPON_SPECIAL;
		break;
	default:
		slot = SARGE_WEAPON_SECONDARY;
	}
    return slot;
}


	static int sarge_report[] = {NONE, NONE,
		SARGE_FOUND_GRENADES, SARGE_FOUND_FLAMER, SARGE_FOUND_BAZOOKA, SARGE_FOUND_MORTARS,
		NONE, NONE, NONE, NONE,
		SARGE_FOUND_AUTO_RIFLE,
		SARGE_FOUND_MINES,
		SARGE_FOUND_EXPLOSIVES,
		NONE,
		NONE,
		SARGE_FOUND_FLAG,		// ARMY_FLAG = 15,
		SARGE_FOUND_GREEN_FLAG,	// ARMY_GREENFLAG = 16,
		SARGE_FOUND_TAN_FLAG,	// ARMY_TANFLAG = 17,
		SARGE_FOUND_BLUE_FLAG,	// ARMY_BLUEFLAG = 18,
		SARGE_FOUND_GREY_FLAG,	// ARMY_GRAYFLAG = 19,
		SARGE_FOUND_MINESWEEPER,	// ARMY_SWEEPER = 20,
		NONE,	// 
		NONE,	// ARMY_MEDKIT = 22,
		SARGE_FOUND_FIRST_AID,	// ARMY_MEDPACK = 23,
		SARGE_FOUND_AIRSTRIKE,	// ARMY_AIRSTRIKE = 24,
		SARGE_FOUND_PARATROOPERS,	// ARMY_PARATROOPERS = 25,
		SARGE_FOUND_RECON,	// ARMY_RECON = 26,

		SARGE_FOUND_NOTE,	// ARMY_SPECIAL_1 = 27, (note)
		SARGE_FOUND_KEY1,	// ARMY_SPECIAL_2 = 28, (key 1)
		SARGE_FOUND_KEY2,	// ARMY_SPECIAL_3 = 29, (key 2)
		SARGE_FOUND_KEY3,	// ARMY_SPECIAL_4 = 30, (key 3)
		NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 
		NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 
		NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 
		NONE, NONE, 
	};


///========================================================================
//	Function:		SargeDoPickupWeapon
//	Description:	pick up the weapon
///========================================================================

void SargeDoPickupWeapon( SARGE * pSarge, ITEM * pItem, BOOL nosound)
{
    SARGE_WEAPON slot = WeaponSlot(pItem);
	LEGION *pLegion;
	ASSERT( pSarge );
	ASSERT( pItem );
	ASSERT( pItem->pWeapon );

	// handle special special items
	if( pItem->pWeapon->eWeapon >= ARMY_SPECIAL_1 && pItem->pWeapon->eWeapon <= ARMY_SPECIAL_30 )
	{
		pSarge->questItem = (int)(pItem->pWeapon->eWeapon) - (int)ARMY_SPECIAL_1 + 1;
		((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_DESTROYED;
		if( pSarge->common.eventNum )
		{
			EventTrigger( EVENT_ITEMPICKEDUP, 
				GetWeaponPickupOrDropEventNum( pSarge->common.eventNum,
				(WEAPON_TYPE) pItem->pWeapon->eWeapon ),
				pSarge->common.nUniqueID, 1, 0 );
			if (pItem->eventNum)
				EventTrigger( EVENT_ITEMPICKEDUP, 
					GetSpecificItemPickupEventNum( pSarge->common.eventNum,
					pItem->eventNum ),
					pSarge->common.nUniqueID, 1, 0 );
		}
			
		goto removeit;
	}

	// special case for one use items
	switch( pItem->pWeapon->eWeapon )
	{
	case ARMY_LURE:
		((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_DESTROYED;
		break;
	case ARMY_MEDKIT:
		int amt;

		if (ITEM_ARMY(pSarge) == ARMY_PLAYER)
			MsgBroadcast( HEAL_SARGE );

		amt = (int)pSarge->common.nMaxStrength * (int)pItem->pWeapon->nDamage / 100;
		pSarge->common.nStrength += amt;
		if( pSarge->common.nStrength > pSarge->common.nMaxStrength )
			pSarge->common.nStrength = pSarge->common.nMaxStrength;
		((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_DESTROYED;
		break;

	case ARMY_AIRSTRIKE:
		pLegion = ArmyGetLegion( ITEM_ARMY(pSarge) );
		pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE] += pItem->pWeapon->nAmmo;
		if( pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE] > 3 )
			pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE] = 3;
		((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_DESTROYED;
		break;

	case ARMY_PARATROOPERS:
		pLegion = ArmyGetLegion( ITEM_ARMY(pSarge) );
		pLegion->AirResources[ARMY_RESOURCE_PARATROOPERS] += pItem->pWeapon->nAmmo;
		if( pLegion->AirResources[ARMY_RESOURCE_PARATROOPERS] > 3 )
			pLegion->AirResources[ARMY_RESOURCE_PARATROOPERS] = 3;
		((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_DESTROYED;
		break;

	case ARMY_RECON:
		pLegion = ArmyGetLegion( ITEM_ARMY(pSarge) );
		pLegion->AirResources[ARMY_RESOURCE_AIR_RECON] += pItem->pWeapon->nAmmo;
		if( pLegion->AirResources[ARMY_RESOURCE_AIR_RECON] > 3 )
			pLegion->AirResources[ARMY_RESOURCE_AIR_RECON] = 3;
		((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_DESTROYED;
		break;

	default:
		if ( pSarge->pWeaponItemList[slot] != NULL ) TRACE("Warning Sarge weapon conflict slot %d\n",slot);
		pSarge->pWeaponList[slot] = pItem->pWeapon;
		pSarge->pWeaponItemList[slot] = pItem;
		((OBJECT*)pItem)->xtriggers |= XTRIGGER_SARGECARRIED;
		if( pSarge->weapon_index == slot )
			pSarge->common.pWeapon = pSarge->pWeaponList[slot];

		SetWeaponOwner(pItem->pWeapon, (ITEM *)pSarge);
	}

	// notify user with voice over
	if (!nosound)
		if (ITEM_ARMY(pSarge) == ARMY_PLAYER)
			MsgBroadcastWithText( sarge_report[pItem->pWeapon->eWeapon] );

	if( pSarge->common.eventNum  /*&& slot == SARGE_WEAPON_SPECIAL   {what was this for?}*/)
	{
		EventTrigger( EVENT_ITEMPICKEDUP, 
			GetWeaponPickupOrDropEventNum( pSarge->common.eventNum,
			(WEAPON_TYPE) pItem->pWeapon->eWeapon ),
			pSarge->common.nUniqueID, 1, 0 );
		if (pItem->eventNum)
			EventTrigger( EVENT_ITEMPICKEDUP, 
				GetSpecificItemPickupEventNum( pSarge->common.eventNum,
				pItem->eventNum ),
				pSarge->common.nUniqueID, 1, 0 );
	}
removeit:
	AnimInactivate( (ANIM *)(&((OBJECTSTRUCT *)pItem)->cell), FALSE );
	((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_CHANGED;
	((OBJECTSTRUCT *)pItem)->triggers |= TRIGGER_UNDEPLOYED;


	if (pSarge->npc && slot == SARGE_WEAPON_SECONDARY) ActivateSargeWeapon(pSarge, slot);
}


///========================================================================
//	Function:		SargePickupWeapon
//	Description:	handle local detection of weapon pickup
///========================================================================

void SargePickupWeapon( SARGE *pSarge, ITEM * pItem, BOOL nosound )
{
    SARGE_WEAPON slot = WeaponSlot(pItem);

	// npc sarges only want to pick up foe flags in last slot
	if (slot == SARGE_WEAPON_SPECIAL && pSarge->npc)
	{
		if (ITEM_ARMY(pItem) == ITEM_ARMY(pSarge)) return; // refuse own flag
		WEAPON_TYPE eWeapon ;
		eWeapon = pItem->pWeapon->eWeapon;
		if (eWeapon != ARMY_GREENFLAG && eWeapon != ARMY_TANFLAG && eWeapon != ARMY_BLUEFLAG && eWeapon != ARMY_GRAYFLAG )
			return;
	}

	if( (slot == SARGE_WEAPON_PRIMARY) &&
		(pItem->pWeapon->eWeapon != ARMY_AUTORIFLE) )
		goto OneUseItem;

	if( pSarge->pWeaponItemList[slot] != NULL )
    {
		// notify user with voice over
		if (!nosound)
			if (ITEM_ARMY(pSarge) == ARMY_PLAYER)
				if (!sfxInPlay(pSarge->pickupSndId))
					pSarge->pickupSndId = AudioPlayItem(SARGE_FULLY_LOADED, (ITEM *)pSarge);
        return;
    }

OneUseItem:
	switch(gpGame->GameType)	{
		case GAMETYPE_ONEPLAYER:
			SargeDoPickupWeapon(pSarge,pItem,nosound);
			break;
		case GAMETYPE_HOST_MULTIPLAYER:
			SargeDoPickupWeapon(pSarge,pItem,nosound);
			SargeWantItemMessageSend(pSarge,pItem,DO_PICKUP,slot);
			break;
//		case GAMETYPE_REMOTE_MULTIPLAYER:
//			// we cant pick up, only host can
//			break;
	}
}   

///========================================================================
//	Function:		SargeDropWeapon
//	Description:	handle local detection of weapon pickup
///========================================================================

void SargeDropWeapon( SARGE *pSarge, SPOINT position,SARGE_WEAPON where )
{
	ITEM *pItem;

	if( where == SARGE_WEAPON_PRIMARY )
		return;

	pItem = pSarge->pWeaponItemList[where];

	switch(gpGame->GameType)	{
		case GAMETYPE_ONEPLAYER:
			SargeDoDropWeapon(pSarge,position,where);
			break;
		case GAMETYPE_HOST_MULTIPLAYER:
			if (IS_LOCAL_ITEM(pSarge))	{ // we cant drop for others
				if (pItem)	{
					ItemSetLocation(pItem,&pSarge->common.position);
					SargeWantItemMessageSend(pSarge,pItem,DO_DROP,where);
					SargeDoDropWeapon(pSarge,position,where);          
				}
			}
			break;

		case GAMETYPE_REMOTE_MULTIPLAYER:
			if (IS_LOCAL_ITEM(pSarge))	{ // we cant drop for others
				if (pItem)	{
					ItemSetLocation(pItem,&pSarge->common.position);
					SargeWantItemMessageSend(pSarge,pItem,WANT_DROP,where);
				}
			}
			break;
	}
}   


///========================================================================
//	Function:		SargeFree
//	Description:	release any sarge when game shuts down
///========================================================================

void SargeFree(SARGE* pSarge)
{
    SargeDelete(pSarge);
    ItemFreeLabel((ITEM *)pSarge);
}


///========================================================================
//	Function:		SargeHitByMissile
//	Description:	will this sarge stop a missile and take damage from it?
///========================================================================

BOOL SargeHitByMissile(SARGE* pSarge, SHORT height)
{
	ACTION pose = AvatarPose(pSarge->pAvatar);

	return AvatarHitByMissile(pose, height);
}


extern SPRITE** Chevron;

void DrawSargeChevron( void )
{
	SARGE	*pSarge;
	ANIM	*pAnim;
	int		h, w;
	int		x, y;
	RECT	rect, irect;

	pSarge = SargePointer(ARMY_PLAYER);
	if( !pSarge->pAvatar )
		return;
	if( pSarge->pVehicle )
		return;
	if( pSarge->invulnerableTimer > 0 )
	{
		if( (pSarge->invulnerableTimer & 0x0200) > 0x0100 )
			return;
	}
	pAnim = pSarge->pAvatar->pAnimation;
	if( !pAnim->pSprite )
		return;
	if( pAnim->world_pos.x == 0 || pAnim->world_pos.y == 0 )
		return;
	w = Chevron[0]->srect.right;
	h = Chevron[0]->srect.bottom;
	rect.left = pAnim->world_pos.x - (w >> 1);
	rect.top = pAnim->world_pos.y -pAnim->pSprite->hotspot.y + pAnim->pSprite->srect.bottom;
	rect.right = rect.left + w;
	rect.bottom = rect.top + h;
	if (!RectIntersect( &the_map.screenrect, &rect, &irect) )
		return;

	irect.right -= irect.left;
	irect.bottom -= irect.top;
	x = irect.left - the_map.screenrect.left;
	y = irect.top - the_map.screenrect.top;
	irect.left = irect.left - rect.left;
	irect.top = irect.top - rect.top;
	irect.right += irect.left;
	irect.bottom += irect.top;

	DrawShadeSpriteToOverlayLayer( x, y, (BYTE *)(Chevron[0]->pShadow), irect, PLIGHT_TABLE );
}


void SargeSetView(SARGE	*pSarge)	{
	ProcessMapPosition();
	pSarge->ViewBox = GetMapPosition();

	// add 4 tiles worth of slop
	pSarge->ViewBox.x -= 64;
	pSarge->ViewBox.y -= 64;
	pSarge->ViewBox.cx += 128;
	pSarge->ViewBox.cy += 128;
}

BOOL VerifyFiringBar()	{
	if (!fire_flag)
		return FALSE;
	else
		return TRUE;
}

void SetSargeAnimType(SARGE *pSarge)	{
	int		eType;
	WEAPON *pWeapon = pSarge->common.pWeapon;

	if (pWeapon && pSarge->pAvatar)	{
		eType = GetSargeAnimType(pWeapon->eWeapon);
		AvatarSetType(pSarge->pAvatar, eType);
	}
}

int GetSargeAnimType(int eWeapon)	{
	int	eType = ARMY_RIFLE_MEN;

	switch(eWeapon)
	{
		case ARMY_GRENADE:
			eType = ARMY_GRENADE_MEN;
			break;
		case ARMY_SWEEPER:
			eType = ARMY_SWEEPER_MEN;
			break;
		case ARMY_MORTAR:
			eType = ARMY_MORTAR_MEN;
			break;
		case ARMY_BAZOOKA:
			eType = ARMY_BAZOOKA_MEN;
			break;
		case ARMY_FLAME_THROWER:
			eType = ARMY_FLAME_MEN;
			break;
		case ARMY_AUTORIFLE:
		case ARMY_RIFLE:
			eType = ARMY_RIFLE_MEN;
			break;
		case ARMY_MINE:
		case ARMY_EXPLOSIVE_WEAPON:
			eType = ARMY_MINER_MEN;
			break;
	}

	return eType;
}

SARGE *GetSargeOnTile( int x, int y )
{
	int		eArmy;
	LEGION	*pLegion;
	SARGE	*pSarge;
	IPOINT tile = INDEX(x,y);

	FOR_EACH_ARMY(eArmy)
	{
		pLegion = ArmyGetLegion(eArmy);
		pSarge = &(pLegion->Sarge);
		if( pSarge->pAvatar )
			if( pSarge->common.tile == tile )
				return pSarge;
	}
	return NULL;
}

void SetSargeInvulnerable(int army_color)	{
	int army = gpComm->IndexFromColor((ARMY_COLOR) army_color);
	sargeInvulnerable[army] = 1;

}

void SetSargeNormal(int army_color)	{
	int army = gpComm->IndexFromColor((ARMY_COLOR) army_color);
	sargeInvulnerable[army] = 0;
}


///========================================================================
//								EOF
///========================================================================

