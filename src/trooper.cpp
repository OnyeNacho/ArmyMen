//========================================================================
//	FILE:			$Workfile: trooper.cpp $
//
//	DESCRIPTION:	Army Troop processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, August 13, 1996
//
//	REVISION:		$Header: /ArmyMen/src/trooper.cpp 403   4/17/98 7:16a Bwilcox $
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
//  $Log: /ArmyMen/src/trooper.cpp $
//  
//  403   4/17/98 7:16a Bwilcox
//  death trace now under scriptdebug
//  
//  402   4/17/98 7:01a Bwilcox
//  put deploy trace under scriptdebug to reduce noise
//  
//  401   4/16/98 2:51p Bwilcox
//  special troopers wont duck or evade or whatnot
//  
//  400   4/15/98 11:57a Bwilcox
//  indenting normal traces and fixing setusercontrol setaicontrol
//  
//  399   4/14/98 10:40a Bwilcox
//  
//  398   4/14/98 10:36a Bwilcox
//  switch playcycle to elapsed time printout,
//  optimize trooper no routing when fail on victim
//  
//  397   4/12/98 3:18p Bwilcox
//  stuck guys can still shoot
//  
//  396   4/12/98 1:20p Bwilcox
//  linger in current pose at last direciotn
//  
//  395   4/12/98 12:32p Bwilcox
//  stop wiggle on 7 or fewer pixles
//  
//  394   4/10/98 6:04p Bwilcox
//  
//  393   4/07/98 11:35p Bwilcox
//  immobilie trooper if routing failure
//  
//  392   4/07/98 4:15p Bwilcox
//  slide restrict only far goals
//  
//  391   4/04/98 9:35p Bwilcox
//  make units off edge come onto main map to fight
//  
//  389   4/03/98 12:44p Nrobinso
//  set default pose
//  
//  388   4/03/98 12:43p Nrobinso
//  fix firing pose problems
//  
//  387   4/02/98 7:35p Nrobinso
//  add variety of death sfx
//  
//  386   4/02/98 4:27p Phu
//  change pSeen to array of unsigned short
//  
//  385   4/02/98 3:07p Phu
//  typecast to avoid warnings
//  
//  384   4/02/98 10:46a Bwilcox
//  fixing sarge npc movement
//  
//  383   4/02/98 8:06a Bwilcox
//  better script tracing.
//  troopers now avoid vehicles even if engaged
//  
//  382   4/01/98 11:57a Bwilcox
//  remove defunct variables. Make prone damage protection a true 12.5 of
//  original damage.
//  
//  381   3/30/98 10:10p Nrobinso
//  switch to animtime, which allows for pauses
//  
//  380   3/30/98 8:08p Bwilcox
//  troopers now aim from guntip rather than their feet
//  
//  379   3/30/98 11:45a Dmaynard
//  Fixed it non-local Troopers can still fire even if they don't have a
//  pVictim pointer.  Victims are not transmitted across the net.
//  
//  378   3/30/98 11:18a Bwilcox
//  revised vehicle evade
//  
//  377   3/28/98 7:14a Bwilcox
//  multiplayer-mode easter egg. Enjoy. Best Regards, The AI Guru
//  
//  376   3/27/98 7:24p Nrobinso
//  put back pose change limitations on troopers
//  
//  375   3/27/98 8:37a Bwilcox
//  trooper formation/unit follow point change
//  
//  374   3/26/98 9:35p Phu
//  strategy items: prone, roll & dive protection
//  
//  373   3/26/98 6:44p Bwilcox
//  
//  372   3/26/98 6:31p Bwilcox
//  
//  371   3/22/98 3:16p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  370   3/22/98 1:37p Bwilcox
//  setfire and fire now use UID and lookup instead of direct ptr
//  
//  369   3/19/98 4:39p Bwilcox
//  no flame prone
//  
//  368   3/19/98 1:19p Bwilcox
//  passing firepose for troopers across net
//  
//  367   3/19/98 1:04p Bwilcox
//  disallow troopers formation spots off the visible map
//  
//  366   3/18/98 7:29p Bwilcox
//  fixed a follow crash when target of follow is destroyed
//  
//  365   3/18/98 2:35p Bwilcox
//  limit grenadiers fire position
//  
//  364   3/18/98 1:49p Phu
//  make chips for troopers
//  
//  363   3/17/98 4:18p Bwilcox
//  troopers not required to linger in pose for now
//  
//  362   3/16/98 1:03p Nrobinso
//  turn off trace
//  
//  361   3/16/98 12:06p Bwilcox
//  remove junk lines
//  
//  360   3/16/98 12:07p Nrobinso
//  remove avatar stationary and pass a pose into avatar calls
//  
//  359   3/15/98 7:13p Nrobinso
//  add trooper damage sfx
//  
//  358   3/12/98 3:26p Bwilcox
//  troopers go prone during an airstrike,
//  troopers fire mortar and grenade higher to clear a rock
//  
//  357   3/06/98 12:16p Bwilcox
//  troopers too close to fire will try to retreat
//  
//  356   3/04/98 7:25p Bwilcox
//  trooper immobile cant evade vehicles
//  
//  355   3/04/98 3:28p Bwilcox
//  troopers at a different height from vehicles dont bother to evade it
//  
//  354   3/02/98 12:44p Bwilcox
//  protect trooper formation point from errors
//  
//  353   2/25/98 6:28p Phu
//  rename wobject files
//  
//  352   2/25/98 1:07p Bwilcox
//  changes to vehicle/trooper interactions
//  
//  351   2/24/98 1:48p Bwilcox
//  engaged units dont worry about evading own vehicles
//  
//  350   2/24/98 12:46p Bwilcox
//  fixing standfireetc behavior when not engaged
//  
//  349   2/24/98 12:03p Bwilcox
//  troopers can fire sometimes while evading
//  
//  348   2/23/98 1:41p Bwilcox
//  fixed vehicles running over troops contained within
//  
//  347   2/20/98 6:41p Phu
//  different deaths
//  
//  346   2/20/98 2:38p Bwilcox
//  imrpvoing evade
//  
//  345   2/20/98 1:16p Bwilcox
//  attack/defend focus must be away from vehicle danger or troopers wills
//  scatter
//  
//  344   2/20/98 1:18p Nrobinso
//  fix up sounds
//  
//  343   2/20/98 11:57a Bwilcox
//  units die in dying vehicle
//  
//  342   2/19/98 11:38a Bwilcox
//  unmoving vehicle with trooper on attack or defend can be ignored
//  
//  341   2/18/98 8:50p Bwilcox
//  poststation ignore guys stand
//  
//  340   2/18/98 2:28p Phu
//  in trooperdamage don't assume aiitemfind is successful
//  
//  339   2/18/98 2:03p Phu
//  Miscellaneous avatar death parts
//  
//  338   2/18/98 2:03p Bwilcox
//  revsered tad args in call, reenabled tadbeing hit
//  
//  337   2/18/98 12:19p Bwilcox
//  tadbeing hit now called. removed useless formation code. removed attack
//  wander code
//  
//  336   2/17/98 6:56p Phu
//  if trying to face towards your own point, don't change facing
//  
//  335   2/17/98 4:27p Phu
//  insert exploded vehicle husk remains into corpse layer.
//  Eliminate double explosions in single player
//  
//  334   2/17/98 3:17p Bwilcox
//  fixing vehicle evasion
//  
//  333   2/16/98 8:48p Phu
//  remove bad line that was causing assert and wasn't doing anything at
//  all
//  
//  332   2/16/98 1:30p Nrobinso
//  fix first line
//  
//  331   2/16/98 12:03p Phu
//  pass along fromUID with explosions
//  
//  330   2/16/98 10:59a Bwilcox
//  trooper too close who is immobile cant move
//  
//  329   2/14/98 1:43p Bwilcox
//  hitwhen now time based, not frame based
//  
//  328   2/11/98 5:13p Bwilcox
//  maynard multivehcile follow bug fixed
//  
//  327   2/11/98 4:06p Bwilcox
//  better evade vehicl
//  
//  326   2/11/98 12:25p Phu
//  
//  325   2/10/98 4:58p Bwilcox
//  scirpt slow speed is now walk, not shuffle
//  
//  324   2/10/98 2:21p Phu
//  firing heights
//  
//  323   2/10/98 12:42p Bwilcox
//  aim to center of target, not at its toes
//  
//  322   2/09/98 2:57p Bwilcox
//  improved vehicle=trooper interaction
//  
//  321   2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  320   2/06/98 7:36p Bwilcox
//  
//  319   2/05/98 6:29p Bwilcox
//  
//  318   2/05/98 6:00p Bwilcox
//  
//  317   2/05/98 3:27p Nrobinso
//  set srage kils of troopers & troopers killed
//  
//  316   2/05/98 1:06p Bwilcox
//  fixed troopers lingering behind
//  
//  315   2/05/98 12:06p Bwilcox
//  removed troopercrashmap
//  
//  314   2/05/98 8:58a Bwilcox
//  
//  313   2/04/98 6:17p Nrobinso
//  make sure killerArmy is ok
//  
//  312   2/04/98 5:57p Nrobinso
//  track troops killed
//  
//  311   2/04/98 4:27p Bwilcox
//  better facing assert control
//  
//  310   2/04/98 2:35p Bwilcox
//  trooper to o close will stay put
//  
//  309   2/04/98 10:14a Bwilcox
//  removal of dead formation stuff
//  
//  308   2/04/98 9:51a Bwilcox
//  
//  307   2/04/98 9:25a Bwilcox
//  tracking override status for display
//  
//  306   2/03/98 9:19p Bwilcox
//  shoot path checkks both ways
//  
//  305   2/03/98 7:09p Bwilcox
//  
//  304   2/03/98 6:54p Phu
//  
//  303   2/03/98 6:36p Phu
//  fixing fire line of sight
//  
//  302   2/03/98 5:49p Phu
//  
//  301   2/03/98 5:16p Bwilcox
//  
//  300   2/03/98 12:53p Bwilcox
//  
//  299   2/03/98 10:52a Bwilcox
//  
//  298   2/02/98 4:11p Bwilcox
//  anim invis for inactive troopers
//  
//  297   1/30/98 1:36p Bwilcox
//  
//  296   1/30/98 10:37a Bwilcox
//  fixed showtile
//  
//  295   1/30/98 10:23a Bwilcox
//  routedata fix
//  
//  294   1/29/98 12:33p Bwilcox
//  moved invis from trooper to unit
//  
//  293   1/28/98 8:59p Bwilcox
//  
//  292   1/28/98 8:42p Bwilcox
//  troopers chevron invisible. event tracing improved
//  
//  291   1/28/98 8:20p Bwilcox
//  Script visible and invisible for units
//  
//  290   1/28/98 7:16p Bwilcox
//  
//  289   1/28/98 4:22p Nrobinso
//  pass facing to SetFire
//  
//  288   1/28/98 3:52p Bwilcox
//  fixing samefacing calls 
//  
//  287   1/28/98 11:47a Bwilcox
//  troopers who stop for collision remain stopped for 10 frames
//  
//  286   1/27/98 4:45p Bwilcox
//  FIXED HALFWAY WEAPON DISTANFCE OF TROOPERS
//  
//  285   1/27/98 1:06p Bwilcox
//  finishing armydelete adjustments for multiplayer
//  
//  284   1/27/98 8:27a Bwilcox
//  MODIFIED EVADE OF VECHILE
//  
//  283   1/26/98 4:36p Bwilcox
//  enter/exit vehicle code keeps troopers from being hit
//  
//  282   1/26/98 2:10p Nrobinso
//  npc stationary vehicle wont bother troopers any more
//  
//  281   1/25/98 5:26a Bwilcox
//  troopers can be ordered slow
//  
//  280   1/23/98 11:32a Bwilcox
//  removed _DEBUG from some code that needs to exist in final-release.
//  added wasAt and whenAt for debugging
//  
//  279   1/22/98 3:53p Phu
//  take out 1.5sec delay on completion, localize switching viewpoint back
//  to sarge
//  
//  278   1/17/98 7:38a Bwilcox
//  added follow_radius, and follow_engaged radius and fixed a
//  defend-radius bug
//  
//  277   1/16/98 10:28p Bwilcox
//  made canshoot use slower code different from cansee cache since
//  see is now < shoot in range
//  
//  276   1/15/98 4:54p Bwilcox
//  more router fixes
//  
//  275   1/15/98 4:21p Bwilcox
//  
//  274   1/15/98 3:41p Bwilcox
//  more router fixes (fulllist optimization) and trooper fixdireciton fid
//  
//  273   1/15/98 1:20p Bwilcox
//  troopers wont try to fix los if they fail until the unit moves
//  
//  272   1/15/98 9:35a Bwilcox
//  tile line optimizations
//  
//  271   98/01/14 20:43 Dmaynard
//  troopers cannot change out of dying, even in the same frame
//  
//  270   98/01/14 20:05 Dmaynard
//  trooper dies if untrafficable in multiplayer
//  
//  269   98/01/14 17:09 Dmaynard
//  
//  268   1/14/98 4:37p Bwilcox
//  
//  267   1/14/98 4:30p Bwilcox
//  
//  266   1/14/98 4:29p Bwilcox
//  replaced cansee/canshoot coding
//  
//  265   1/14/98 2:42p Bwilcox
//   face foe even if cant move
//  
//  264   1/14/98 8:25a Bwilcox
//  fix to trooper routing system
//  
//  263   1/13/98 5:52p Bwilcox
//  kneelfire added
//  
//  262   1/13/98 5:21p Bwilcox
//  pronefire and standfire
//  
//  261   1/13/98 1:51p Bwilcox
//  added DrawSpoint
//  
//  260   98/01/13 11:00 Dmaynard
//  imrpoved walk around vehicle for troopers
//  
//  259   98/01/13 10:51 Dmaynard
//  allow trooper to walk away from a stationary vehicle even in standoff
//  range
//  
//  258   1/09/98 12:33p Bwilcox
//  trooper collision override added 
//  airouter overshoot now allows 1 tile at no rerouting cost
//  
//  257   1/09/98 12:17p Phu
//  different corpse layer
//  
//  256   1/08/98 2:14p Bwilcox
//  attack paramaters and trooper slide parameters added to defaults file
//  
//  255   1/08/98 1:20p Bwilcox
//  parameters now in aidefaults.aai (runtime) include
//  DEFENSE_RADIUS, TROOPER_TURN_RATE, TROOPER_POSE_RATE, VEHICLE_DANGER,
//  VEHICLE_STANDOFF
//  
//  254   1/07/98 5:12p Nrobinso
//  fix deployed unit facing bug
//  
//  253   1/07/98 3:21p Nrobinso
//  add AvatarCurrentPose; changed AvatarPose to take only the avatar
//  pointer; AvatarPoseChange also takes an action
//  
//  252   1/07/98 12:31p Bwilcox
//  fixed initial facing on predeployed troopers
//  
//  251   1/06/98 1:53p Bwilcox
//  fixed trooper clearmem problem
//  
//  250   1/06/98 12:35p Bwilcox
//  added PropogateTrafficable fanout code in item.
//  fixed troopercover bug when enemy dies
//  
//  249   1/02/98 2:11p Bwilcox
//  distance tests moved into canshoot
//  
//  248   1/02/98 1:26p Bwilcox
//  line of sight from a canshoot call will test for friendlies in the way.
//  Vehicle/sarge ai now checks using canshoot also
//  
//  $Nokeywords:$
///========================================================================



// Includes
#include "stdafx.h"

#include "Army.h"
#include "Tad.h"
#include "Disp.h"
#include "Damage.h"
#include "audio.h"
#include "UnitMsg.h"
#include "avatar.h"
#include "trooper.h"
#include "newdoor.h"
#include "aix.h"
#include "unit.h"
#include "aiaccess.h"
#include "comm.h"
#include "anim.h"
#include "gameflow.h"
#include "weapon.h"
#include "item.h"
#include "aibtank.h"
#include "map.h"
#include "wobject.h"
#include "vehicle.h"
#include "sarge.h"
extern char scriptDebug;

int tarmy = -1, tunit = -1, ttrooper = -1;
BOOL VehicleEnterable(VEHICLE* pVehicle);

static void WaitHere(UNIT* pUnit) // a debug trap using tarmy, tunit
{
    int x;
	if (ITEM_INDEX(pUnit) != tunit) return;
	if (tarmy > 1 && ITEM_ARMY(pUnit) != (tarmy-1) ) return;
	if (tarmy < 2 && ITEM_ARMY(pUnit) != tarmy) return;

	x = 1;
}
extern char unitBehavior;
extern BOOL	assert_on_untrafficable;

///========================================================================
//					LOCAL VARIABLES & DEFINES
///========================================================================
#include "trooper.dat"
SPOINT ValidGoal(ITEM* pItem);

#define WAIT_TO_START 10;		// delay before restart if collide w troopers

int TROOPER_APART	= 40;		// pixel dist between troopers
static void	TrooperSetFace(TROOPER* pTrooper,int direction);
int VEHICLE_DANGER = 14;		// tile distance to avoid vehicle
int VEHICLE_STANDOFF = 9;   	 // tile distance to wait at
int TROOPER_TURNRATE =  20;		// turn shift at any one frame
extern int DEFENSE_RADIUS;
int LINGER_RATE = 150	;		// frames to stay in one pose
int TROOPER_SLIDERATE = 4;	// >> << round to nearest direction (16)
	
// A sub2type field of UID consists of 4 bits of trooper and x bits of unit
#define TROOPER_ID_SHIFT	4			// 4 bits for trooper id
#define TROOPER_X(p)  ((p)->common.position.x)
#define TROOPER_Y(p)  ((p)->common.position.y)
#define TROOPER_LOCATION(x)  ((x)->common.location)
#define TROOPER_INDEX(p) (ITEM_INDEX(p) & 0x07)
#define TROOPER_SITFIGHT(p) ((p)->pUnit->poststationBehavior==DEFENDFIRE || \
                             (p)->pUnit->poststationBehavior==NESTFIRE)
#define TROOPER_DUGIN(p) (TROOPER_SITFIGHT(p) && IS_POSTSTATION((p)->pUnit))
// dug in refers to damage protection

#define TROOPER_POSEGIVEN(p) ((p)->pUnit->poststationBehavior==NESTFIRE || \
                              (p)->pUnit->poststationBehavior==STANDFIRE || \
                              (p)->pUnit->poststationBehavior==KNEELFIRE || \
                              (p)->pUnit->poststationBehavior==PRONEFIRE)
#define TROOPER_IMMOBILE(p) (TROOPER_POSEGIVEN(p) && IS_POSTSTATION((p)->pUnit))
// immobile means not allowed to move under any circumstances


long maplimit;

extern int manDied;    
int FRAME_STOP = -1;					// debugging control

static SPOINT behindTiles[] = // block 8 around us replicated 2x for snakepoint
{
  {0,-16},{-16,-16},{-16,0},{-16,16},{0,16},{16,16},{16,0},{16,-16},
  {0,-16},{-16,-16},{-16,0},{-16,16},{0,16},{16,16},{16,0},{16,-16},
  {0,-16},{-16,-16},{-16,0},{-16,16},{0,16},{16,16},{16,0},{16,-16}
};

TROOPER* traceTrooper = 0; // if monitoring a trooper

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
SPOINT OffPoint(SPOINT from,int direction,int distance);
static BOOL NextToCover(TROOPER* pTrooper);
static BOOL SafeCover(TROOPER* pTrooper,ITEM* pVictim);
static void	TrooperSetAvatar(TROOPER* pTrooper,ACTION action,int direction);
static SPOINT	TrooperSnakePoint(TROOPER* pTrooper,int tile); 
static SPOINT	TrooperFormationPoint(TROOPER* pTrooper); 
static void TrooperUpdate(TROOPER* pTrooper);
static void	TrooperComplete(TROOPER* pTrooper);
static void TroopersComplete(UNIT* pUnit);
static void TrooperFight(TROOPER* pTrooper);
static void InitVisibilityArray();
static void FreeVisibilityArray();
static void TrooperLeaderStill (TROOPER* pLeader, SPOINT* facePoint);
static void TrooperLeaderMove (TROOPER* pLeader, SPOINT position);
static void TrooperFollowerMove(TROOPER* pTrooper,int direction);
static void	TroopInitWeapon( TROOPER* pTrooper, TROOPER_TYPE eTroopType );
static void TrooperDoMove(TROOPER* pTrooper, SPOINT position, ACTION pace,int direction);
static ACTION TrooperPace(TROOPER* pTrooper,SPOINT goal);


USHORT* pSeen = NULL;
short int *tileLineOffsets = NULL;
long tileIndices[5000];
int maxvisblock;


///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - startup routines
///*****************************************************************
///*****************************************************************

int  XY2Tile(int x,int y)
{
      return (int) ENCODE_IPOINT(x,y);
}

void ShowTile(IPOINT where)
{
	SPOINT p;
	p.x = IPOINT_X(where) << 4;
	p.y = IPOINT_Y(where) << 4;
	WorldToScreen(&p);
    RECT bb;
    bb.left = p.x-5;
    bb.right = p.x+5;
    bb.top = p.y-5;
    bb.bottom = p.y+5;
    FillRectFront(&bb,RGB_WHITE);
}

void ShowXY(int x,int y)
{
	SPOINT p;
	p.x = x;
	p.y = y;
	WorldToScreen(&p);
    RECT bb;
    bb.left = p.x-5;
    bb.right = p.x+5;
    bb.top = p.y-5;
    bb.bottom = p.y+5;
    FillRectFront(&bb,RGB_WHITE);
}

void ShowSpoint(SPOINT p)
{
	WorldToScreen(&p);
    RECT bb;
    bb.left = p.x-5;
    bb.right = p.x+5;
    bb.top = p.y-5;
    bb.bottom = p.y+5;
    FillRectFront(&bb,RGB_WHITE);
}

// prevent troopers from moving at angles they dont have
// animations for (esthetic avoidance of sliding) unless
// they are real close to their goal, and need precision to get there
static int SlideRestrict(int facing,SPOINT from,SPOINT to)
{
    int x,y;
	x = from.x - to.x;
	y = from.y - to.y;
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (x < 48 && y < 48) return facing;
	return (facing >> TROOPER_SLIDERATE) << TROOPER_SLIDERATE;
}

///========================================================================
//	Function:		CanShoot
//	Description:	Line of sight to shoot? (SEE CANSEEITEM to match)
//  Returns:		>0 if ok. -1 if not in range. 0 if bad line of sight
//					-2 if too close
///========================================================================

static int myxheight;

long ShootBlock(IPOINT at)
{
    int blockHeight;
    
    // block height 0 = blocks nothing
    blockHeight = the_map.vis_layer[at];
    if (blockHeight >= myxheight)
        return TRUE; // we are blocked
    return 0; // no problem
}

int CanShoot(WEAPON* pWeapon,ITEM* pItem,IPOINT to)
{
      WEAPON_TYPE eWeapon = pWeapon->eWeapon;   IPOINT set[1000];
      long maxRange = AiObjectFiringRange(pItem);
      long minRange = WeaponMinRange(eWeapon);

      long gap = TileDistance(pItem->tile,to) << 4; // pixel distance
      // too far or near
      if (gap > maxRange) return -1;
      if (gap < minRange) return -2;

      // lob weapons require no line of sight.
      if (eWeapon == ARMY_GRENADE || eWeapon == ARMY_MORTAR) return 1;

      myxheight = GetItemPov(pItem);  
      int ans = 0;
      int n;
      n = TileLine(pItem->tile,to,set);
      ASSERT(n < 1000); // how could it be with a 256x256 map?
      while (--n > 1) // start by ignoring terminal tile and end before start tile
      {
          if (ShootBlock(set[n]))
          {
              ans = 1;
              break;
          }
      }

      // try for 2ndary path
      if (ans == 1)
      {
          ans = 0;
          n = TileLine(to,pItem->tile,set);      
          while (--n > 1) 
          {
              if (ShootBlock(set[n]))
              {
                  ans = 1;
                  break;
              }
          }
      }
      if (ans == 1) return 0; // cannot shoot

      return TRUE; // yes we can shoot safely enough
}

///========================================================================
//	Function:		TroopSystemLoad
//	Description:	Initialize trooper system. Build formations.
///========================================================================

int TrooperSystemLoad()
{
    long  nbytes;
    maplimit = the_map.height * the_map.width;

    // marker array
	nbytes = maplimit * sizeof(short);
    pSeen = (unsigned short*) malloc(nbytes);
    if (!pSeen) TRACE("Failedmalloc seen data\n");
    else ZeroMemory((void*)pSeen,nbytes);

    // allocate 1 private trooper space for crash map
	nbytes = maplimit * sizeof(long);

    InitVisibilityArray();

    return TRUE;
}


///========================================================================
//	Function:		TrooperCreate
//	Description:	Create a Troop of a given type 
///========================================================================

void TrooperCreate(UNIT* pUnit,TROOPER* pTrooper,TROOPER_TYPE eTroopType)
{
	ZeroMemory( (void*)pTrooper, sizeof(TROOPER) );		// clear the struct

    // set trooper basics
    // set partial id
    ItemSetUID(pTrooper,ITEM_ARMY(pUnit),ARMY_TROOPER,eTroopType,0);

    pTrooper->common.nMaxStrength =
          AIinfo.unitTables[eTroopType].nTroopStrength,
	pTrooper->common.nStrength = pTrooper->common.nMaxStrength;
    TrooperSetFace(pTrooper,DIRECTION_UP);
    pTrooper->mode = TROOPER_INACTIVE;
    pTrooper->poseDuringRound = AVATAR_STAND;

    // initialize weapon subcomponent
	TroopInitWeapon(pTrooper, eTroopType);

    TrooperAssignToUnit(pTrooper,pUnit);

    // leave avatar subcomponent NULL til deployed
}

///========================================================================
//	Function:		TrooperTestCreate
//	Description:	create a stand alone (no unit) trooper for testing purposes
///========================================================================
void TrooperTestCreate(ARMY_TYPE army_type, TROOPER* pTrooper,TROOPER_TYPE eTroopType)
{
    int nID = 0;

	ZeroMemory( (void*)pTrooper, sizeof(TROOPER) );		// clear the struct

    // set trooper basics
	pTrooper->pUnit = NULL;

    // limited to 8 bits of units (255) in game
    ASSERT(!(nID & ~AI_ID_SUB2_MASK));	// prove no id overflow
    ItemSetUID(pTrooper,army_type,ARMY_TROOPER,eTroopType,nID);

	pTrooper->common.nStrength = pTrooper->common.nMaxStrength = AIinfo.unitTables[eTroopType ].nTroopStrength,
    TrooperSetFace(pTrooper,DIRECTION_UP);
    pTrooper->mode = TROOPER_INACTIVE;

    // initialize weapon subcomponent
	TroopInitWeapon(pTrooper, eTroopType);

    // leave avatar subcomponent NULL til deployed
}


///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - enter trooper into play
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		TrooperDeploy
//	Description:	Deploy a trooper onto the map with full legal existence
///========================================================================

void	TrooperDeploy( TROOPER* pTrooper, SPOINT point, short facing )
{
    // set his    ocation
    AVATAR* pAvatar;
    ASSERT(!UntrafficableUnit(ENCODE_IPOINT(point.x,point.y)));
    ItemSetLocation(pTrooper,&point);
    // prove he is currently legal location
    ASSERT(!UntrafficableUnit(pTrooper->common.tile));
    if (scriptDebug) TRACE("    %s deploying at %d.%d\n",ItemDBName(pTrooper),point.x,point.y);

    // assign his avatar (invisble)
    if (pTrooper->pAvatar == NULL) // when actual deploy and not vehicle deploy
    {
      pAvatar = AvatarCreate(ITEM_UID(pTrooper));
      pTrooper->pAvatar = pAvatar;
      pTrooper->mode = TROOPER_ALIVE;
      pTrooper->routeData.owner = ITEM_UID(pTrooper);
    }
    else
    {
	  pAvatar = pTrooper->pAvatar;
      AnimActivate(pAvatar->pAnimation,NO_ACTIVATE_LINKS);
    }
      
    // now prepare avatar to be displayed visibly
    pTrooper->pendingAction = pTrooper->action = pTrooper->oldAction = AVATAR_STAND;
    pTrooper->direction = pTrooper->oldDirection = facing;
    TrooperSetFace(pTrooper,facing);
	pTrooper->common.facing = facing;
    pTrooper->nearAirstrike = 0;

	AvatarSetPosition(point, pAvatar);
	AvatarSetFacing(facing, pAvatar);

    // troopers are not in tad, their units are
    // troopers visbility over things acrue next frame
}

///========================================================================
//	Function:		TrooperAssignToUnit
//	Description:	make trooper member of a unit (or change membership)
///========================================================================

void TrooperAssignToUnit(TROOPER* pTrooper,UNIT* pUnit)
{
    int nID;
    nID = ++pUnit->nLastTroop;
    ASSERT(nID < MAX_TROOPERS);
    // set up cross link
	pTrooper->pUnit = pUnit;
    pUnit->pTroops[nID] = pTrooper;    
    // revise UID
    nID |=	ITEM_INDEX(pUnit) << TROOPER_ID_SHIFT;
    ItemSetUID(pTrooper,ITEM_ARMY(pUnit),ARMY_TROOPER,ITEM_CLASS(pTrooper),nID);

    // revise strength of unit
    pUnit->common.nMaxStrength += pTrooper->common.nMaxStrength;
    pUnit->common.nStrength += pTrooper->common.nStrength;
    pUnit->troops += 1;
}

///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - simulation update routines
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		TroopersInactive
//	Description:	Tell troopers to go invisible
///========================================================================

void TroopersInactive (UNIT* pUnit) 
{
      pUnit->beInvisible = TRUE;
      int i;
      TROOPER* pTrooper;
      AVATAR* pAvatar;
      FOR_EACH_TROOPER(pUnit,pTrooper,i)
      {
          pAvatar = pTrooper->pAvatar;
          pAvatar->pAnimation->flags |= ANIM_FLAG_INVISIBLE;
          AnimInactivate(pAvatar->pAnimation,FALSE);
      }
}
      
///========================================================================
//	Function:		TroopersActive
//	Description:	Tell troopers to go visible standing
///========================================================================

void TroopersActive (UNIT* pUnit) 
{
      pUnit->beInvisible = FALSE;
      int i;
      TROOPER* pTrooper;
      AVATAR* pAvatar;
      FOR_EACH_TROOPER(pUnit,pTrooper,i)
      {
          pAvatar = pTrooper->pAvatar;
          pAvatar->pAnimation->flags |= ANIM_FLAG_ACTIVE;
      }
}

///========================================================================
//	Function:		TroopersStill
//	Description:	Tell troopers to face a particular location
///========================================================================

void TroopersStill (UNIT* pUnit, SPOINT* facePoint) 
{
    TROOPER* pLeader;
    TROOPER* pTrooper;
    int i;
    pLeader = THE_LEADER(pUnit);
    if (!pLeader) return; // unit is dying presuambley
     
    WaitHere(pUnit);

	// First face the leader. He will also pick the formation to use.
    TrooperLeaderStill(pLeader,facePoint);
    
    // followers face the way the leader does
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
		pTrooper->couldShoot = 0;
		if (pTrooper == pLeader) continue;
		TrooperFollowerMove(pTrooper,pLeader->common.facing); 
    }

    // now they finish off their processing from setup above
    TroopersComplete(pUnit);
}

///========================================================================
//	Function:		TroopersMove
//	Description:	Tell squad leader to move and the rest follow (setup)
///========================================================================

void TroopersMove (UNIT* pUnit, SPOINT position) 
{
    TROOPER* pLeader;
    TROOPER* pTrooper;
    int i;
    pLeader = THE_LEADER(pUnit);      	
    ASSERT(pLeader);
    WaitHere(pUnit);

	// First move the leader. He will also pick the formation to use.
    TrooperLeaderMove(pLeader,position);
    pLeader->fSpot = 0; // turn off engagement cover    

    // Whether or not the lead trooper moved, his followers move wrt him.
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
 		pTrooper->couldShoot = 0;
		if (pTrooper == pLeader) continue;
        pTrooper->fSpot = 0; // turn off engagement cover
        TrooperFollowerMove(pTrooper,pTrooper->common.facing); 
    }

    // now they finish off their processing from setup above
    TroopersComplete(pUnit);
}


///========================================================================
//	Function:		TroopersFight
//	Description:	All troopers in battle do this (setup)
///========================================================================

void TroopersFight(UNIT* pUnit)
{
    TROOPER* pTrooper;
    int i;
    WaitHere(pUnit);
      
    // default victims to none
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
      pTrooper->common.pVictim = NULL;
	  pTrooper->victimUID = 0;
	  pTrooper->couldShoot = 0;
    }

    // determine current victims to target for each trooper
    if (pUnit->common.pTad) TadAssignVictims((TAD*)pUnit->common.pTad);

    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
      if (!TROOPER_HEALTHY(pTrooper)) continue;      

      TrooperFight(pTrooper);  // every man for himself!
    }

    // now they finish off their processing from setup above
    TroopersComplete(pUnit);
}

///========================================================================
//	Function:		TrooperEvadeTheVehicle
//	Description:	stay out of way of vehicle or stop
///========================================================================

void TrooperEvadeTheVehicle(TROOPER* pTrooper,VEHICLE* pVehicle,int stop)
{
	ACTION wasaction = pTrooper->pendingAction;

	// just stop
	if (stop)
	{
		pTrooper->override = AVOID_VEHICLE;
		TrooperSetAvatar(pTrooper,AVATAR_STOP_IMMEDIATELY,pTrooper->common.facing);      
		return;
	}

	// actually run away

	int facing;
	// randomly pick running direction away with going to the side
	// run perpendicular since he is our friend ( ALSO ALLOW FOE)
	facing = pVehicle->common.facing;
	if (pVehicle->full_velocity < 0) facing += 128;
	if (facing >= CIRCLE_UNITS) facing -= CIRCLE_UNITS;
	SPOINT to;
	to = pVehicle->common.position;
	to.x += (short)(cos_table[facing] * 48);
	to.y += (short)(sin_table[facing] * 48);
	IPOINT totile;
	totile = ENCODE_IPOINT(to.x,to.y);
	// left of, go left
	if (cross(pTrooper->common.tile,pVehicle->common.tile,totile) < 0)
		facing += 64;
	 else facing -= 64;
	if (facing < 0) facing += CIRCLE_UNITS;
	if (facing >= CIRCLE_UNITS) facing -= CIRCLE_UNITS;
            
	facing = SlideRestrict(facing,pTrooper->common.position,OFF_THE_MAP ); // always restrict move
	TrooperSetAvatar(pTrooper,AVATAR_RUN,facing);              
	pTrooper->override = AVOID_VEHICLE;
	if (unitBehavior)
		TRACE("    %s evading vehicle\n",ItemDBName(pTrooper));
}

void TrooperAirCenter(SPOINT at)
{
      IPOINT tile;
      tile = ENCODE_IPOINT(at.x,at.y);
      int eArmy;
      int i;
      UNIT* pUnit;
      TROOPER* pTrooper;
      LEGION* pLegion;
      FOR_EACH_LOCAL_ARMY(eArmy)
      {
          if (Armies[eArmy].Status == 0) continue;
      
          pLegion = ArmyGetLegion(eArmy);
          FOR_EACH_UNIT(pLegion,pUnit)
          {
              if (!UNIT_ON_MAP(pUnit)) continue;
              FOR_EACH_TROOPER(pUnit,pTrooper,i)
              {
                  if (pTrooper->common.nStrength == 0) continue;

                  if (TileDistance(pTrooper->common.tile,tile) > 20) continue;

                  // he was near a strike
                  pTrooper->nearAirstrike = gpGame->dwAnimTime;
              }
          }
      }
}
      
static void TrooperSawAir(TROOPER* pTrooper)
 {
 //  guys were near an airstrike, run for a moment

    if (pTrooper->nearAirstrike == 0) return;


    // troopers go prone for 3 seconds
    if ((gpGame->dwAnimTime - pTrooper->nearAirstrike) > 3000)
    {
      pTrooper->nearAirstrike = 0;
    }      

    else  TrooperSetAvatar(pTrooper,AVATAR_PRONE,pTrooper->pendingDirection);
 }

static void TrooperEvadeVehicle(TROOPER* pTrooper)
{
      int eArmy,vehicle,facing,d;
      int theight;
      int vheight;
      theight = ELEVATION(the_map.elevation_layer[pTrooper->common.tile]);
      LEGION* pLegion;
      VEHICLE* pVehicle;
	  UNIT* pUnit = pTrooper->pUnit;
      FOR_EACH_DEPLOYED_ARMY(eArmy)
      { 
          pLegion = ArmyGetLegion(eArmy);
          FOR_EACH_VEHICLE(pLegion,vehicle)
          {
              pVehicle = pLegion->pLegionVehicles[vehicle];
              if (pVehicle->state != VEHICLE_DEPLOYED) continue;
			
			  d = TileDistance(pVehicle->common.tile,pTrooper->common.tile);
              if (d > VEHICLE_DANGER) continue;

              // if vehicle is at a different height, he cant drive to us
              // diff of 2 or more is safe. diff of 1 is a ramp, danger
              vheight = ELEVATION(the_map.elevation_layer[pVehicle->common.tile]);
              vheight -= theight;
              if (vheight >= 2 || vheight <= -2) continue;

              // we are may be in danger of being run over. 
              facing = GetDirection(&pVehicle->common.position,
                                    &pTrooper->common.position);
              // if the vehicle is ours, special rules apply */
              if (ITEM_ARMY(pVehicle) == ITEM_ARMY(pTrooper)){
				  SARGE* pSarge;
				  pSarge = SargePointer(ITEM_ARMY(pVehicle));
				  // own non-npc and sarge not in this vehicle cannot harm us
				  if (pVehicle->npc == 0 && pSarge->pVehicle != pVehicle)
                      continue;
				  // assume a stationary npc vehicle will remain stationary
				  if (pVehicle->npc && pVehicle->full_velocity == 0)
                      continue;	  
                  // assume unmoving vehilce with not a follow order is ok
                  // if the focus is far enough away
                  if (pVehicle->full_velocity == 0 &&
                      pTrooper->pUnit->order != UNIT_FOLLOW &&
                      TileDistance(pUnit->focusTile,pVehicle->common.tile)
                      > VEHICLE_DANGER)
                      continue;

				  VEHICLE* targetVehicle = NULL;
				  if (pUnit->order == UNIT_FOLLOW && pUnit->focusItem)
				  {
					  if (ITEM_TYPE(pUnit->focusItem) == ARMY_VEHICLE) 
						  targetVehicle = (VEHICLE*) pUnit->focusItem;
					  else if (ITEM_TYPE(pUnit->focusItem) == ARMY_SARGE)
						  targetVehicle = ((SARGE*)pUnit->focusItem)->pVehicle;
				  }

				  // assume an unmoving vehicle we want to enter is ok to approach
				  if (pVehicle->full_velocity == 0 &&
					  pTrooper->pUnit->order == UNIT_FOLLOW &&
					  pVehicle == targetVehicle &&
					  VehicleEnterable(pVehicle))
					  continue;
		

                 int towardVehicle;
				 towardVehicle = CIRCLE_UNITS - facing;
				 int offVehicle = towardVehicle - pTrooper->pendingDirection;
				 if (offVehicle < 0) offVehicle = - offVehicle;

				  int vface = pVehicle->common.facing;
				  if (pVehicle->full_velocity < 0) // backing up, invert face
				  {
					  vface += 128;
					  if (vface >= CIRCLE_UNITS) vface -= CIRCLE_UNITS;
				  }
                  // if vehicle doesnt face us we may approach if on follow
                  int face = facing - vface;
                  if (face < 0) face = -face;

                  // we cannot hope to enter these vehicles.
                  // so if hit perim getting closer, stop.
                  if (!VehicleEnterable(pVehicle) &&
                      d == VEHICLE_STANDOFF &&
               TileDistance(pTrooper->common.oldTile,pVehicle->common.tile)
                       > d)
                  {
                      TrooperEvadeTheVehicle(pTrooper,pVehicle,TRUE);
                      continue;
                  }

                  // if we are within standoff of a vehicle we cannot
                  // enter, move away
                  if (!VehicleEnterable(pVehicle) &&
                      d < VEHICLE_STANDOFF)
                  {
                      goto evadenow;
                  }

                  // if we follow and he faces away and is moving, ok
                  if (face >= 64 && pUnit->order == UNIT_FOLLOW &&
                      pVehicle->full_velocity != 0)
                      continue;

                  // if he faces away or isnt moving and we are not following,
                  // and we cant enter then just stop
                  if (face >= 64 || pVehicle->full_velocity == 0)
                  {
                      TrooperEvadeTheVehicle(pTrooper,pVehicle,TRUE);
                      continue;
                  }

				  // otherwise if he is moving toward us, we MUST evade.
              }

              else  // for all enemy vehicles
              {
				  // assume a moving vehicle or sarge vehicle must be avoided
				  if (pVehicle->full_velocity != 0);
                  else if (pVehicle->pDriver);
				  // except bazooka guys can try to kill him
				  else if (ITEM_CLASS(pTrooper) == ARMY_BAZOOKA_MEN)
					  continue;
                  else continue;
              }

        // for all enemy vehicles and for our vehicles approaching us
       // EVADE!
              
 evadenow:
         TrooperEvadeTheVehicle(pTrooper,pVehicle,FALSE);
         eArmy = 20; // abort outer loop as well
         break;
          }
      }
  }


static void	TrooperComplete(TROOPER* pTrooper)
{
      AVATAR* pAvatar = pTrooper->pAvatar;
      UNIT* pUnit;
      TROOPER* pOtherTrooper;
      int i;
      pUnit = pTrooper->pUnit;
      pTrooper->override = NO_OVERRIDE;
      ACTION intendedAction = pTrooper->pendingAction;

      // track how long we have been in a pose
      // we dont want to shift in and out too quickly
      ACTION myPose = AvatarPose(pAvatar);
      if (myPose == pTrooper->currentPose) ++pTrooper->framesInPose;
      else
      {
          // decrement round count
          if (pTrooper->roundsBeforeStall) --pTrooper->roundsBeforeStall;
          pTrooper->framesInPose = 0;
          pTrooper->currentPose = myPose;
      }

      switch(pTrooper->pendingAction)
      {
          // are death sequences complete
          case AVATAR_DIE_MELT:
          case AVATAR_DIE_SHOT:
          case AVATAR_DIE_SQUASH:
            if (AvatarLastCompleted(pTrooper->pendingAction, pAvatar))
			{
				TrooperGone(pTrooper);
			}
			return;

          case AVATAR_DIE_EXPLODE:
			TrooperGone(pTrooper);
			return;

          // something else like pickup or deploy?
          default: ;
      };

	  if (ITEM_CLASS(pTrooper) == ARMY_SPECIAL_MEN) return; // leave special alone

      // if we are undergoing collision or other delay, remain stationary.
      if (pTrooper->stopDelay)
      {
          -- pTrooper->stopDelay;
          if (pTrooper->pendingAction == AVATAR_RUN ||
              pTrooper->pendingAction == AVATAR_SHUFFLE)
          {
              TrooperSetAvatar(pTrooper,
                  AVATAR_STAND,pTrooper->pendingDirection);
              pTrooper->override = STILL_WAIT_FOR_TROOPER;
          }
          goto exit;
      }


      // avoid sudden pose changes by remaining idle and/or firing if need be
      BOOL pChange;
	  pChange = FALSE;
      if (pTrooper->pendingAction == AVATAR_RUN &&
          (pTrooper->currentPose == AVATAR_PRONE ||
           pTrooper->currentPose == AVATAR_KNEEL)) pChange = TRUE;
      else if (pTrooper->pendingAction == AVATAR_KNEEL &&
          (pTrooper->currentPose == AVATAR_PRONE ||
           pTrooper->currentPose == AVATAR_STAND)) pChange = TRUE;
      else if (pTrooper->pendingAction == AVATAR_PRONE &&
          (pTrooper->currentPose == AVATAR_KNEEL ||
           pTrooper->currentPose == AVATAR_STAND)) pChange = TRUE;
      if (pChange && pTrooper->framesInPose < LINGER_RATE)
      {
          pTrooper->override = WAIT_IN_POSE;

          TrooperSetAvatar(pTrooper,pTrooper->currentPose,pTrooper->direction); // stay the way he was
          if (unitBehavior)
              TRACE("    %s waiting to change pose\n",ItemDBName(pTrooper));
      }


	  // avoid drastic turns when running
	  int faceChange;
	  faceChange = pTrooper->pendingDirection - pTrooper->common.facing;
	  int faceDelta;
	  faceDelta = (faceChange >= 0) ? faceChange : -faceChange;
	  if (faceDelta > TROOPER_TURNRATE && pTrooper->action == AVATAR_RUN)
	  {
		  int newDirection;
		  if (faceChange > 0) newDirection = pTrooper->common.facing + TROOPER_TURNRATE;
		  else newDirection = pTrooper->common.facing - TROOPER_TURNRATE;

		  while (newDirection < 0) newDirection += CIRCLE_UNITS;
          while (newDirection >= CIRCLE_UNITS) newDirection -= CIRCLE_UNITS;
          TrooperSetFace(pTrooper,newDirection);

		  // prove this worked
		  faceChange = pTrooper->pendingDirection - pTrooper->common.facing;
		  faceDelta = (faceChange >= 0) ? faceChange : -faceChange;
		  ASSERT(faceDelta <= TROOPER_TURNRATE);
          if (unitBehavior)
              TRACE("    %s limiting turn\n",ItemDBName(pTrooper));
	  }
     

      TrooperSawAir(pTrooper);

      // stay out of harms way of vehicles if allowed to move
      if (!TROOPER_IMMOBILE(pTrooper)) 
          TrooperEvadeVehicle(pTrooper);

      // prevent guys from walking onto friends locations
      // dont worry about collision if we are not moving
      if (pTrooper->pendingAction != AVATAR_RUN &&
          pTrooper->pendingAction != AVATAR_SHUFFLE);
      else FOR_EACH_TROOPER(pUnit,pOtherTrooper,i)
      {
          if (pOtherTrooper == pTrooper) break; // checked all below
          SPOINT xx,yy;
          xx = pTrooper->lands;
          yy = pOtherTrooper->lands;
          if (GetDistance(&xx,&yy) > TROOPER_APART)
              continue;
          pTrooper->override = WAIT_FOR_TROOPER;
          TrooperSetAvatar(pTrooper,
                  AVATAR_STOP_IMMEDIATELY,pTrooper->common.facing);
          pTrooper->stopDelay = WAIT_TO_START;
          break;
      }
  exit:

      // no change to trooper action
      if (intendedAction == pTrooper->pendingAction) return;

      // we overrode his action. can we patch it to allow firing?

      //  he wasnt trying to fire
      if (intendedAction == AVATAR_FIRE_STATIONARY);
      else if (intendedAction == AVATAR_FIRE);
      else return;
      
      // if we are coming to an abrupt halt, do it.
      if (pTrooper->pendingAction == AVATAR_STOP_IMMEDIATELY) return;

      // if we are running for our lives, do it.
      if (pTrooper->pendingAction == AVATAR_RUN) return;

      TrooperSetAvatar(pTrooper,AVATAR_FIRE_STATIONARY,pTrooper->pendingDirection);

}

///========================================================================
//	Function:		TroopersComplete
//	Description:	finish off setup of each trooper
///========================================================================

static void	TroopersComplete(UNIT* pUnit)
{
    TROOPER* 	pTrooper;
    int i;

	//  check for death completion from previous cycle
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
      TrooperComplete(pTrooper);
    }
}

///========================================================================
//	Function:		TroopersUpdateAvatar
//	Description:	Carry out pending avatar orders
///========================================================================

void TroopersUpdateAvatars(UNIT* pUnit)
{
// cause the troopers avatars to do their thing and update the
// resulting position of the trooper     

     TROOPER* pTrooper;
	 SPOINT lands;
     AVATAR* avatar;
     if (playCycle ==  FRAME_STOP) ASSERT(0); // debug warning to here

    // now make the avatars do their movement/stunts/whatever
    // and update troopers resulting position
    int i;
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
         avatar = pTrooper->pAvatar;	

         // check next frame movement
         lands = AvatarWouldMoveTo((ACTION)pTrooper->pendingAction, pTrooper->poseDuringRound,
                                       pTrooper->pendingDirection,FALSE,
                                       avatar);

         if (UntrafficableUnit(ENCODE_IPOINT(lands.x,lands.y))){
              TrooperSetAvatar(pTrooper,
                              AVATAR_STOP_IMMEDIATELY,pTrooper->common.facing);
         }

         TrooperUpdate(pTrooper);
   }
}

///========================================================================
//	Function:		TrooperFireWeapon
//	Description:	The trooper weapon animation fired, now we do damage
///========================================================================
static char testit = 0;
void TrooperFireWeapon(TROOPER* pTrooper)
{
    WEAPON* pWeapon;
    WEAPON_TYPE eWeapon;
    UNIT* pUnit;
    int eArmy;
	ITEM *pVictim;
    
//    TRACE("%s is Firing  ",ItemDBName(pTrooper));
	pWeapon = pTrooper->common.pWeapon;
    eWeapon = pWeapon->eWeapon;
    pVictim = AiItemFind(pTrooper->victimUID);
	if ( IS_LOCAL_ITEM(pTrooper) ) {
		if (!pVictim) return;
		if ( pVictim->nStrength == 0) return;
	}
    
    // decrement round count
    if (pTrooper->roundsBeforeStall) --pTrooper->roundsBeforeStall;

	// firing makes you visible to EVERYONE, no matter where.
    pUnit = TROOPER_UNIT(pTrooper);
	if (pUnit)	{
		ItemMakeVisible(pUnit);
	
		if (IS_LOCAL_ITEM(pTrooper))	{
//			hit = HIT;

            // if victim is dead he will be off the map when we try cover.
			if (pVictim && pVictim->nStrength)	{// not already dead
				// firing makes you visible to whom you fired upon
				// BUG- but not to buildings??
              eArmy = ITEM_ARMY(pVictim);
              if (eArmy != ARMY_INDEPENDENT)
              {
                  pUnit->common.seen[eArmy] = gpGame->dwAnimTime;
                  pUnit->common.seenWhere[eArmy] = pUnit->common.position;
              }
			}
		}
	}

	SPOINT	pt, *hotspot;
	ANIM	*pAnim;

	pt = pTrooper->common.position;
	pAnim = pTrooper->pAvatar->pAnimation;
	hotspot = &(pAnim->pFrame[pAnim->current_frame].secondary_hotspot);
	pt.x += hotspot->x;
	pt.y += hotspot->y;
    int height;
    height = GetItemHeight((ITEM *)pTrooper)+1;
    // lob weapons start from high (to allow clearing rocks and such)
    if (eWeapon == ARMY_GRENADE || eWeapon == ARMY_MORTAR) 
        height += 4;
	if (testit) height = 0;
	FireWeapon((ARMY_TYPE)ITEM_ARMY(pTrooper), pTrooper->common.pWeapon, &pt,
                    height,
					pTrooper->common.fireDirection, pTrooper->common.fireDistance, pTrooper->fireHeight, 
					ITEM_UID(pTrooper) );
//    TRACE("Done \n");
}


static SPOINT TrooperFiringPosition(TROOPER* pTrooper)
{
	ANIM	*pAnim;
	SPOINT pt;
    pt = pTrooper->common.position;
    
    // if sarge has not died, include avatars pose 
    if( pTrooper->pAvatar && ((ITEM *)(pTrooper))->pWeapon )
    {
        pAnim = pTrooper->pAvatar->pAnimation;
		pt.x +=  pAnim->pFrame[pAnim->current_frame].secondary_hotspot.x;
		pt.y += pAnim->pFrame[pAnim->current_frame].secondary_hotspot.y;
   }
	return pt;
}


///========================================================================
//	Function:		TrooperSetFire
//	Description:	Note the direction and distance we intend to fire
//					so we can pass that across the network                     
///========================================================================

void TrooperSetFire(TROOPER* pTrooper, int facing)
{
	SET_WEAPON set_weapon;
	ITEM* pVictim;
	pVictim = AiItemFind(pTrooper->victimUID);
	if (!pVictim) return;
	SPOINT pt;
	pt = TrooperFiringPosition(pTrooper);
	set_weapon = SetFireWeapon(pTrooper->common.pWeapon, &pt, facing, pVictim);

	pTrooper->common.fireDirection = set_weapon.direction;
	pTrooper->common.fireDistance = set_weapon.distance;
	int eheight, height, myheight, theight;

	eheight = GetElevationHeightAtItem( (ITEM *)( pVictim) );
	height = eheight + 1;

	// build in a random "shoot high" variable into the firing mechanism depending on target pose
	theight = GetItemHeightNoElevation(pVictim);
	if( theight < 8 )								// 8 is defined as standing height
		height += rand() % (8 - theight);
	myheight = GetItemHeight( (ITEM *)pTrooper );
	if( height > myheight + 4 )						// 4 is maximum vertical difference
		height = myheight + 4;
	// set the height
	pTrooper->fireHeight = height;
}


///========================================================================
//	Function:		TrooperAcceptDamage()
//	Description:	trooper will accept damage done to him
///========================================================================
void TrooperAcceptDamage(TROOPER* pTrooper,int nDamage,int nDamageType,SPOINT pFrom, UID fromUID)
{
    UNIT* pUnit = pTrooper->pUnit;
    int oldstrength;
      
	// update the unit strength
	oldstrength= pUnit->common.nStrength;
	pUnit->common.nStrength -= nDamage;

    if (pUnit->common.nStrength == 0)
      pUnit->mode = UNIT_DYING;

	// damage the trooper, no worse than dead
	pTrooper->common.nStrength -= nDamage;			

	//trigger any damage (not death) event
    if (pUnit->common.nStrength)
      DamageItemTriggerEvents((ITEM *)pUnit, oldstrength, pUnit->common.nStrength, pUnit->common.nMaxStrength);


	// if the trooper has died send a death message now
	if (pTrooper->common.nStrength == 0)
    {
      ACTION deathAction;
      // store how he dies anim
	  if( pTrooper->common.pWeapon && pTrooper->common.pWeapon->eWeapon == ARMY_FLAME_THROWER )
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
				DoExplosion( pTrooper->common.position.x, pTrooper->common.position.y, 
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

      // he dies aimed toward where hit
      int facing = GetDirection(&pTrooper->common.position,&pFrom);
      if (facing == -1)
      {
          facing = pTrooper->common.facing;
      }

      // if he was invisible, go to live display now
      if (pTrooper->pUnit->beInvisible)
      {
          pTrooper->pUnit->beInvisible = FALSE;
      }

      TrooperSetAvatar(pTrooper,deathAction,facing);

		int killerArmy = EXTRACT_ARMY(fromUID);
		if( killerArmy >= 0 )	{
			// this will only work locally -- we won't track sarge kills multiplayer
			if (OBJTYPE(fromUID) == ARMY_SARGE)
				Armies[killerArmy].sarge_kills++;
		}
   }
}            

///========================================================================
//	Function:		TrooperDamage()
//	Description:	Damage needs to be applied to a trooper.
//	Input:			pTrooperPtr			trooper to apply damage to
//					nDamageToDo			damage to apply
//					nDamageType			type of damage being applied
//					nDamagePercentage	relative location to damage
//					pPointOfDamage		location of damage
///========================================================================

void TrooperDamage(TROOPER* pTrooper, int nDamageToDo, int nDamageType, SPOINT* pFrom, UID fromUID )
{
    UNIT* pUnit;
    int reduceDamage = 0;
    int actualDamage;
    ITEM* pItem;
    TROOPER* pHit = NULL;
    pItem = AiItemFind(fromUID);
    
	if( pItem )
	{
		if (ITEM_TYPE(pItem) == ARMY_TROOPER)
		{
			pHit = (TROOPER*)pItem;
			pItem = (ITEM*) ((TROOPER*)pItem)->pUnit;
		}
	}
	
	// pFrom used to judge special animations (hit from where)

	if (pTrooper->common.nStrength == 0) return; // cannot die any more

	switch (nDamageType)	{
		case DMGTYPE_BULLET:
			AudioPlayItem(BULLET_HIT_TROOPER, (ITEM *)pTrooper);
			MakeChips( *pFrom, UnitColorTable(ITEM_ARMY(pTrooper)), 0 );
			break;
		case DMGTYPE_RUNOVER:
//		case DMGTYPE_STRUCTURAL:
			AudioPlayItem(SQUASH_TROOPER, (ITEM *)pTrooper);
			break;
//		case DMGTYPE_GRENADE:
//		case DMGTYPE_MORTAR:
//		case DMGTYPE_BAZOOKA:
//		case DMGTYPE_MISSILE:
		case DMGTYPE_OTHER_EXPLOSION:
//		case DMGTYPE_FLAMED:
			AudioPlayItem(FLAME_HIT_TROOPER, (ITEM *)pTrooper);
			break;
	}


	// see if this trooper is local. If not send a remote troop damamge message
	if (!IS_LOCAL_ITEM(pTrooper)) {  // tell remote trooper he is hit
		TrooperDamageMessageSend( pTrooper, nDamageToDo, nDamageType, pFrom,fromUID );
	 	return;
	}

    pUnit = TROOPER_UNIT(pTrooper);
    // knowing when allows us to disengage or engage if fired upon 
    pUnit->nHitWhen = gpGame->dwAnimTime;

    // tell tad we are being hit (high priority to defend)
    if (pItem) TadBeingHit(pItem,(ITEM*)pUnit); // my unit is being hit
 
	int originalDamage;
	originalDamage = nDamageToDo;

    // is he sheltered?
    if (TROOPER_DUGIN(pTrooper))
    {
         reduceDamage = originalDamage >> 2; // 25% will be removed
         // if 25% is 0, consider randomly removing all damage
         if (!reduceDamage && randInt(0,3) == 1) reduceDamage = originalDamage;
         
		 nDamageToDo -= reduceDamage;
    }
	// a prone trooper takes less damage
	if( pTrooper->pAvatar )
	{
		if( AvatarPose(pTrooper->pAvatar) == AVATAR_PRONE )
		{
			reduceDamage = originalDamage >> 3;	// 12.5% will be removed
			// if 12.5% is 0, consider randomly removing all damage
			if (!reduceDamage && randInt(0,7) == 1) reduceDamage = originalDamage;
 			nDamageToDo -= reduceDamage;
		}
	}

    actualDamage = nDamageToDo;
    if (actualDamage > pTrooper->common.nStrength)
      actualDamage = pTrooper->common.nStrength; // limit to killing amount

    
    // troopers close together KILL immediately
    if (pHit && TileDistance(pHit->common.tile,pTrooper->common.tile) < 3)
    {
          actualDamage = pTrooper->common.nStrength;
    }


    TrooperAcceptDamage(pTrooper,actualDamage,nDamageType,*pFrom,fromUID);
}

///========================================================================
//	Function:		TrooperKill
//	Description:	kill off trooper. continues to exist until animation gone
///========================================================================
void	TrooperKill( TROOPER* pTrooper )
{
    UNIT* pUnit;
    pUnit = pTrooper->pUnit;
    if (scriptDebug) TRACE("    %s died\n",ItemDBName(pTrooper));

    // first death of the mission
    if (ITEM_ARMY(pTrooper) == ARMY_PLAYER && !manDied)
    {
      manDied = TRUE;
      SitRep(ARMY_SUFFERING,(ITEM*) pTrooper->pUnit);
    }

	// generate body parts as necessary
	if( pTrooper->pendingAction == AVATAR_DIE_SHOT &&
		AvatarPose(pTrooper->pAvatar) == AVATAR_STAND )
	{
		ShotDeathStandParts( pTrooper->common.position, pTrooper->pendingDirection, pTrooper->pAvatar->pAnimation->trans_table );
	}

	int die = rand() % DIE_SOUNDS;
	AudioPlayItem(die_snds[die], (ITEM *)pTrooper);

    pTrooper->mode = TROOPER_DYING;						// waiting on anim
				
	Armies[ITEM_ARMY(pTrooper)].troops_killed++;

   // tell network he dies now...
	if (IS_LOCAL_ITEM(pTrooper)) TrooperDeathMessageSend( pTrooper );
}


///========================================================================
//	Function:		TrooperUpdate
//	Description:	carryout the avatar pending after some last checks
///========================================================================

static void TrooperUpdate(TROOPER* pTrooper)
{
   AVATAR* pAvatar = pTrooper->pAvatar;
   // he is on untrafficable space in singleplayer mode
   if (gpGame->GameType != GAMETYPE_ONEPLAYER && !IS_LOCAL_ITEM(pTrooper));
   else if (UntrafficableUnit(pTrooper->common.tile) && pTrooper->mode != TROOPER_DYING)
  {
      TRACE("BANG! %s died when terrain became untrafficable\n",
          ItemDBName(pTrooper));
      TrooperAcceptDamage(pTrooper,pTrooper->common.nStrength,
          DMGTYPE_RUNOVER, pTrooper->common.position,0);      
      return;
  }

   SPOINT lands;
   lands = AvatarWouldMoveTo((ACTION)pTrooper->pendingAction, pTrooper->poseDuringRound,
                                       pTrooper->pendingDirection,FALSE,
                                       pAvatar);
   // Test for vehicle in the way of moving trooper
   if (getVehicleOnTile(lands.x >> 4, lands.y >> 4) &&
       (lands.x != pTrooper->common.position.x || lands.y != pTrooper->common.position.y))
  {
	 TrooperSetAvatar(pTrooper,AVATAR_STOP_IMMEDIATELY,pTrooper->common.facing);
  }

	  ASSERT(pTrooper->pendingDirection >= 0 && pTrooper->pendingDirection < CIRCLE_UNITS);
	  int result;

      // prove he is currently legal location
	if (assert_on_untrafficable)	{
     if (IS_LOCAL_ITEM(pTrooper) && pTrooper->mode != TROOPER_DYING)
          ASSERT(!UntrafficableUnit(pTrooper->common.tile));
	}

      // we test here in case this is a remote trooper
      if (UntrafficableUnit(ENCODE_IPOINT(lands.x,lands.y)) && pTrooper->mode != TROOPER_DYING)
      {
          if (IS_LOCAL_ITEM(pTrooper))    ASSERT(0);
		  TrooperSetAvatar(pTrooper,AVATAR_STOP_IMMEDIATELY,pTrooper->common.facing);
          TRACE("%s Remote trooper being stopped\n",ItemDBName(pTrooper));
      }
 

	    // a local trooper standing or stopping, who can shoot, should try
	  if (IS_LOCAL_ITEM(pTrooper) && 
		  (pTrooper->pendingAction == AVATAR_STAND || pTrooper->pendingAction == AVATAR_STOP_IMMEDIATELY) &&
		  pTrooper->couldShoot)
	  {
		  int stopNeeded = FALSE;
		  // moving last turn requires stopping..
		  if (pTrooper->action == AVATAR_RUN || pTrooper->action == AVATAR_SHUFFLE || pTrooper->action == AVATAR_WALK
			  || pTrooper->action == AVATAR_FIRE) stopNeeded = TRUE;
		 if (stopNeeded && pTrooper->pendingAction == AVATAR_STOP_IMMEDIATELY); // must stop
		 else 
		 {
			pTrooper->pendingAction = AVATAR_FIRE_STATIONARY;
			pTrooper->pendingDirection = pTrooper->shootFace;
		 }
	  }
 
     
      result = AvatarPerform((ACTION)pTrooper->pendingAction, pTrooper->poseDuringRound,
              pTrooper->pendingDirection, TRUE, pAvatar);

      SPOINT xx;
      xx = AvatarPosition(pAvatar);

      if (UntrafficableUnit(ENCODE_IPOINT(xx.x,xx.y)) && pTrooper->mode != TROOPER_DYING)
      {
			TRACE("%s ended up at %d.%d (dir %d pace %d)\n",
						ItemDBName(pTrooper),
						xx.x,xx.y,pTrooper->pendingDirection,
						pTrooper->pendingAction);

			TRACE("Avatar ended up ILLEGAL!\n");

          // he is on untrafficable space in singleplayer mode
          if (gpGame->GameType != GAMETYPE_ONEPLAYER);
          else if (UntrafficableUnit(pTrooper->common.tile) && pTrooper->mode != TROOPER_DYING)
          {
              TRACE("BANG! %s died when he moved onto untrafficable terrain\n",
                  ItemDBName(pTrooper));
              TrooperAcceptDamage(pTrooper,pTrooper->common.nStrength,
                  0,pTrooper->common.position,0);      
              return;
          }
      }

      // just note when he moved (for debugging)
      if (!SameSPoint(xx,pTrooper->wasAt))
      {
          pTrooper->wasAt = xx;
          pTrooper->whenAt = playCycle;
      }
      else // he didnt move
      {
          // wasnt trying to move now
          if (pTrooper->pendingAction != AVATAR_RUN &&
              pTrooper->pendingAction != AVATAR_SHUFFLE);
          // wasnt trying to before
          else if (pTrooper->action != AVATAR_RUN &&
              pTrooper->action != AVATAR_SHUFFLE);
          // wasnt trying to before that
          else if (pTrooper->oldAction != AVATAR_RUN &&
              pTrooper->oldAction != AVATAR_SHUFFLE);
          else // for debugging test
          {
              int x;
              x = 1;
          }
      }


      // copy freshly done  into current and old done into old data
      ItemSetOldLocation(pTrooper);
      pTrooper->oldAction = pTrooper->action;
      pTrooper->oldDirection = pTrooper->direction;
      pTrooper->action = pTrooper->pendingAction;
      pTrooper->direction = pTrooper->pendingDirection;         
      
      // update trooper position data
      ItemSetLocation(pTrooper,&xx);


      pTrooper->common.facing = AVATAR_FACING(pAvatar);

		WeaponFireUpdate(pTrooper->common.pWeapon);
}
      
///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - exit trooper from play
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		TrooperPickup
//	Description:	Pickup a trooper off the map
///========================================================================

void	TrooperPickup( TROOPER* pTrooper)
{
    // set his location off the world
    ItemSetOldLocation(pTrooper);
    SPOINT point;
    point = OFF_THE_MAP;
    ItemSetLocation(pTrooper,&point);

    // destroy his avatar 
    AvatarDestroy(pTrooper->pAvatar);
    pTrooper->pAvatar = NULL;

    // troopers visbility over things disappears next frame
}

///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - wind-down routines
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		TrooperDelete
//	Description:	Delete a Troop.
///========================================================================

void	TrooperDelete( TROOPER* pTrooper )
{
	ASSERT(pTrooper);

    // if an avatar remains, kill it.
    if (pTrooper->pAvatar) AvatarDestroy(pTrooper->pAvatar);
}


///========================================================================
//	Function:		TroopSystemFree
//	Description:	Release any general storage of trooper
///========================================================================

void TrooperSystemFree()
{
      if (pSeen) free( pSeen);
	  pSeen = NULL;

      FreeVisibilityArray();
}


///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - informational functions
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		TrooperFind
//	Description:	locate the trooper having this UID
///========================================================================

TROOPER*	TrooperFind(LONG nUniqueID)
{
	LEGION*		pLegion;
	UNIT*		pUnit;
    TROOPER*		pTrooper;
	int eArmy;
	eArmy = EXTRACT_ARMY(nUniqueID);
	if (Armies[eArmy].Status == 0) return NULL; // army not there

	// now decode the unique ID
	ASSERT (OBJTYPE(nUniqueID) == ARMY_TROOPER );
	pLegion = ArmyGetLegion(eArmy);
	pUnit = pLegion->pUnitList + (SUB2TYPE(nUniqueID) >> TROOPER_ID_SHIFT);
    int i;
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
		if( pTrooper )
			if (ITEM_UID(pTrooper) == nUniqueID) return pTrooper;
//		else
//			return NULL;
    }
	return NULL;
}


///*****************************************************************
///*****************************************************************
//	INTERNAL ROUTINES not visible to outside
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		TrooperShoot
//	Description:	Go fire on him, because you can
///========================================================================

static void TrooperShoot(TROOPER* pTrooper,ITEM* pVictim,
      int myd,int mymin,int mymax,int hismax)
{
      UNIT* pUnit = pTrooper->pUnit;
      int facing;
      ACTION pose;
      ASSERT(pTrooper->common.nStrength);

      int halfway = (mymax + mymin) >> 1;   // halfway in my range

      // machine gun nest always kneels
      if (pUnit->poststationBehavior == NESTFIRE)
      {
          pose = AVATAR_FIRE_STATIONARY;
          pTrooper->poseDuringRound = AVATAR_KNEEL;
      }
      else if (pUnit->poststationBehavior == PRONEFIRE)
      {
          pose = AVATAR_FIRE_STATIONARY;
          pTrooper->poseDuringRound = AVATAR_PRONE;
      }
      else if (pUnit->poststationBehavior == KNEELFIRE)
      {
          pose = AVATAR_FIRE_STATIONARY;
          pTrooper->poseDuringRound = AVATAR_KNEEL;
      }
      else if (pUnit->poststationBehavior == STANDFIRE)
      {
          pose = AVATAR_FIRE_STATIONARY;
          pTrooper->poseDuringRound = AVATAR_STAND;
      }

      // if he cant reach us, shoot him from here
      else if (myd > hismax)
      {
          pose = AVATAR_FIRE_STATIONARY;
      }

      // if we are getting close, go stationary
      else if (myd <= halfway)
      {	
          pose = AVATAR_FIRE_STATIONARY;
      }

      // otherwise keep moving toward him if we are moving
      else 
	  {
		  pose = AVATAR_FIRE;
          pTrooper->poseDuringRound = AVATAR_STAND;
	  }

      // shoot at the middle of the object, not its toes
      SPOINT belly;
      belly = ItemCenterPos(pVictim);
	  SPOINT pt;
	  pt = TrooperFiringPosition(pTrooper);
	  // if too close, dont use gun barrel since we will wiggle it back and forth
	  if (GetDistance(&pTrooper->common.position,&belly) < 8) pt = pTrooper->common.position;
      facing = GetDirection(&pt,&belly);

      // troopers are standing on top of each other
      if (facing == -1) facing = pTrooper->common.facing;

	  // this data is used later during override in troopercomplete, if we get stuck
	   pTrooper->couldShoot = TRUE;
	   pTrooper->shootFace = facing;


      // if we are supposed to be still, select a pose
      if (pose == AVATAR_FIRE_STATIONARY)
      {      
          // in each firing potential round, randomly allow so many fires
          // before resting
          if (pTrooper->roundsBeforeStall == 0 && !TROOPER_IMMOBILE(pTrooper))
          {
              pTrooper->roundsBeforeStall = (rand() % 3) + 2;
              int poser;
              if (ITEM_CLASS(pTrooper) == ARMY_GRENADE_MEN)
                  poser = (rand() % 2) + AVATAR_KNEEL;  // kneel or stand
              else if (ITEM_CLASS(pTrooper) == ARMY_MORTAR_MEN)
                  poser = AVATAR_KNEEL;  // kneel only
			  else if (ITEM_CLASS(pTrooper) == ARMY_FLAME_MEN)
                  poser = (rand() % 2) + AVATAR_KNEEL;  // kneel or stand
              else poser = (rand() % 3) + AVATAR_KNEEL; 
              pTrooper->poseDuringRound =  (ACTION)poser; // kneel stand prone
          }

      
          // if we are not prone/kneel/stand for firing then go to it
          // before firing. We want to fire from various positions for looks.
          if (AvatarPoseChange(AVATAR_FIRE_STATIONARY,pTrooper->pAvatar) !=
              pTrooper->poseDuringRound)
          {
              pose = (ACTION) pTrooper->poseDuringRound;
          }
          // dont need full routing to here, just fake it
          RouterLineRouter(ValidGoal(pVictim),&pTrooper->routeData);
      }

      TrooperSetAvatar(pTrooper,pose,facing);
}      

///========================================================================
//	Function:		TrooperGotoCover
//	Description:	Cant shoot due to bad LOS, move toward him
///========================================================================

static int TrooperGotoCover(TROOPER* pTrooper,IPOINT goal)
{
      ACTION pace;
      SPOINT to;
      SPOINT aim;

      // conserve on rerouting if target hasnt moved too much
      aim = CenterPointFromTile(goal);
      to = AIRouter(aim,&(pTrooper->routeData),
                         UNIT_ROUTE,
                         pTrooper->common.position,
                         pTrooper->common.facing);
      pace = TrooperPace(pTrooper,aim);

      // turn off going to cover (we got there or cant get there)
      if (to.x == 0)
      {
          pTrooper->fSpot = 1; // got there
          return FALSE;
      }
            
      // tell him to move toward cover
      TrooperDoMove(pTrooper,to,pace,pTrooper->common.facing);

	  return TRUE;
}
      
///========================================================================
//	Function:		TrooperFixLOS
//	Description:	Cant shoot due to bad LOS, move toward him
///========================================================================

static void TrooperFixLOS(TROOPER* pTrooper,ITEM* pVictim)
{
	  // we previously couldnt get a route, wait a bit
	  if (pTrooper->delayUID == ITEM_UID(pVictim) &&
		  pTrooper->delayVictim > gpGame->dwSysTime)
	  {
		  TrooperSetAvatar(pTrooper,pTrooper->currentPose,pTrooper->common.facing);
		  return;
	  }



      // what pose are we in
      ACTION pose = AvatarPoseChange(pTrooper->currentPose, pTrooper->pAvatar);
      ACTION pace;

      // conserve on rerouting. Go to where we last routed to target until
      // we get there
      SPOINT location = ValidGoal(pVictim);
      SPOINT spot = OFF_THE_MAP;

      // if he hast moved much from our plan ask for a new plan
      if (!pTrooper->waygoal.x || GetDistance(&location,&pTrooper->waygoal) > 63)
			pTrooper->waygoal = location;			// we are going to go here

      spot = AIRouter(pTrooper->waygoal,&(pTrooper->routeData),
                         UNIT_ROUTE,pTrooper->common.position,
                          pTrooper->common.facing);

      // none possible or needed. stay put
      if (!spot.x){
	      pTrooper->delayUID = ITEM_UID(pVictim);
		  pTrooper->delayVictim = gpGame->dwSysTime + 1500; // wait 3 seconds;
		  TrooperSetAvatar(pTrooper,pTrooper->currentPose,pTrooper->common.facing);
		  return;
      }

      // tell him to move toward victim
      pace = TrooperPace(pTrooper,location);
      TrooperDoMove(pTrooper,spot,pace,pTrooper->common.facing);
}

///========================================================================
//	Function:		AdjacentCover
//	Description:	return True if cover is close to us
///========================================================================

static IPOINT coverList[20];
static int coverIndex;      
      
static long TrooperCover(IPOINT at)
{

      int i;
      // avoid cover used by other guys in our unit
      for (i = 1; i <= coverIndex; ++i)
      {
          if (TileDistance(coverList[i],at) < 5) return 0;
      }
      
      // this is our cover, return next to it
      if (UntrafficableUnit(at)) return propogateAt;
       
	  return 0;
}

static IPOINT AdjacentCover(TROOPER* pTrooper)
{ // returns some place (current place) even if no cover found

	 IPOINT cover;
     cover = (IPOINT)PropogateTrafficable((ITEM*) pTrooper,pTrooper->common.tile,10,TrooperCover);
     return  (cover) ? cover : pTrooper->common.tile;
}


///========================================================================
//	Function:		TrooperFStatus
//	Description:	Set status of fighting
///========================================================================

char* fstatuses[] ={	 "no victim",
"seeking cover","fixing sight","firing","chasing","out-of-radius",
"backing up"};

static void TrooperFStatus(TROOPER* pTrooper,FIGHT_STATUS status)
{
      if (pTrooper->fstatus != status && unitBehavior)
          TRACE("    %s %s\n",ItemDBName(pTrooper),fstatuses[status]);
      pTrooper->fstatus = status;
}

///========================================================================
//	Function:		SetFoeCover
//	Description:	avoid going close to enemy 
///========================================================================

static void SetFoeCover(UNIT* pUnit)
{
      TROOPER* pfoeTrooper;
      int i;
      switch(ITEM_TYPE(pUnit->pTarget))
      {
      case ARMY_UNIT:
          FOR_EACH_TROOPER(((UNIT*)pUnit->pTarget),pfoeTrooper,i)
          {
              coverList[++coverIndex] = pfoeTrooper->common.tile;
			  ASSERT(coverIndex < 20);
          }
          break;
      default:
        coverList[++coverIndex] = pUnit->pTarget->tile;
		ASSERT(coverIndex < 20);
      }
}

///========================================================================
//	Function:		TrooperEvadeFind
//	Description:	find where to evade
///========================================================================
static IPOINT backupTile;
static IPOINT victimTile;
static IPOINT attackerTile;
static long victimDist;
static long score;

static long TrooperEvadeFind(IPOINT at) // starting 5 tiles away working in
{
      // we want max dist from foe with min dist from us
      int vd,ad; int vscore;
      if (UntrafficableUnit(at)) return 0; // cant go here

      vd = TileDistance(at,victimTile);
      if (vd <= victimDist) return 0;		// not farther from victim

      ad = TileDistance(at,attackerTile);	// dist from where we are
      vscore = (vd * 100) + (100 - ad);     // go close to us, far from him
      if (vscore <= score) return 0;		// not better

      // this is better (farther from victim, as close to us as possible)
      score = vscore;
      victimDist = vd;
      backupTile = at;
      return 0;
}

///========================================================================
//	Function:		TrooperFight
//	Description:	All troopers in battle do this.
///========================================================================

static void TrooperFight(TROOPER* pTrooper)
{
// This is called for all troopers whenever a unit is engaged.
// Troopers have already been assigned victims.

      UNIT* pUnit = TROOPER_UNIT(pTrooper);
      TROOPER* pXTrooper;
      int j;
      BOOL covered;
      ACTION idlePose = pTrooper->currentPose;
      IPOINT nearbyCover = 0;
      
      if (pUnit->poststationBehavior == NESTFIRE) idlePose = AVATAR_KNEEL;
      if (pUnit->poststationBehavior == KNEELFIRE) idlePose = AVATAR_KNEEL;
      if (pUnit->poststationBehavior == PRONEFIRE) idlePose = AVATAR_PRONE;
      if (pUnit->poststationBehavior == STANDFIRE) idlePose = AVATAR_STAND;

      // tell if covered. a nestfire guy is automatically at cover
      if (pTrooper->pUnit->poststationBehavior == NESTFIRE &&
          IS_POSTSTATION(pTrooper->pUnit)) covered = TRUE;
      else covered = NextToCover(pTrooper);

      // he is dying, nothing more for him
      if (!TROOPER_HEALTHY(pTrooper)) return;

      WEAPON* pWeapon = pTrooper->common.pWeapon;
      WEAPON_TYPE eWeapon = pWeapon->eWeapon;
      ITEM* pVictim = pTrooper->common.pVictim;
	  if (pVictim)
	  	  pTrooper->victimUID = ITEM_UID(pVictim);
	  else pTrooper->victimUID = 0;

      // there is no one to attack (unit will disengage when foe unit removed)
      if (!pVictim)
      {
          TrooperFStatus(pTrooper,NO_VICTIM);
          TrooperSetAvatar(pTrooper,idlePose,pTrooper->common.facing);

          // dont need full routing to here, just fake it
          RouterLineRouter(pTrooper->common.position,&pTrooper->routeData);

          return;
      }


      int hisMaxRange = (AiObjectFiringRange(pVictim)+15) >> 4;
      int myMinRange = WeaponMinRange(eWeapon) >> 4;
      int myMaxRange = (AiObjectFiringRange((ITEM*)pTrooper)+15) >> 4;
      long d =  TileDistance(pTrooper->common.tile,pVictim->tile);

      // can I fire at him (range and los and clear to fire)
      int bCanShoot;
      bCanShoot = CanShoot(pWeapon,(ITEM*)pTrooper,pVictim->tile);

      // if I am at the limit of my defense radius during poststation defend,
      // and victim is outside of my defense sphere,
      // I dont need to move. just shoot when I can.
	  SPOINT toGoal,uGoal;		  
	  uGoal = pTrooper->pUnit->destination;
	  IPOINT utile,totile;
	  utile = ENCODE_IPOINT(uGoal.x,uGoal.y);
      if (TROOPER_IMMOBILE(pTrooper) &&
          TileDistance(utile,pTrooper->common.tile) > DEFENSE_RADIUS)
       {
		  toGoal = ValidGoal(pVictim);
		  totile = ENCODE_IPOINT(toGoal.x,toGoal.y);
		  if (TileDistance(totile,utile) <= DEFENSE_RADIUS);

          // If i cant shoot, just rest
          else if (bCanShoot <= 0) 
          {
              // dont need full routing to here, just fake it
              RouterLineRouter(pTrooper->common.position,&pTrooper->routeData);

              TrooperDoMove(pTrooper,pTrooper->common.position,idlePose,
                  pTrooper->common.facing);

              TrooperFStatus(pTrooper,OUT_OF_RADIUS);
              return;
          }
      }

	// if we were too close, and trying to back up, run until we arrive and 
	// then reconsider.
	if (pTrooper->fstatus == BACKUP)
	{
		SPOINT goal;
		goal = AIRouter(pTrooper->routeData.destination,&(pTrooper->routeData),UNIT_ROUTE,
                              pTrooper->common.position,
                              pTrooper->common.facing);
        if (goal.x) 
		{
            TrooperDoMove(pTrooper,goal,AVATAR_RUN,pTrooper->common.facing);
			return;
		}
	}


    // if we are close or in his range and not covered, consider getting cover
 	BOOL went = FALSE;
    if (d < (hisMaxRange+5) && !covered && !TROOPER_IMMOBILE(pTrooper))
    {
          // counting down til next cover seek?
          if (pTrooper->fSpot > 0 && pTrooper->fSpot < 250)
          {
              --pTrooper->fSpot;
          }
		// we got stuck last turn. then wait
		  else if (pTrooper->action == AVATAR_STOP_IMMEDIATELY)
		  {
			  pTrooper->fSpot = 249;
		  }

          // we have already computed a cover for this round, go there
          else if (pTrooper->fSpot) 
          {
              went = TrooperGotoCover(pTrooper,pTrooper->fSpot);
          }

          // we need to find a cover
          else
          {
			  coverIndex = 0;
              // locate other covers to avoid cause our friends are there
              FOR_EACH_TROOPER(pUnit,pXTrooper,j)
              {
                  if (pXTrooper == pTrooper) continue; // ignore self

                  // use where he is as his cover if he hasnt computed yet
                  if (pXTrooper->fSpot < 250) {
                      coverList[++coverIndex] = pXTrooper->common.tile;
					  ASSERT(coverIndex < 20);

				  }
                  // use where he is going as his cover
                  else {
                      coverList[++coverIndex] = pXTrooper->fSpot;
					  ASSERT(coverIndex < 20);
				  }
              }
			  SetFoeCover(pUnit); // mark enemy places to avoid also

              nearbyCover = AdjacentCover(pTrooper);
              pTrooper->fSpot = nearbyCover;
              went = TrooperGotoCover(pTrooper,nearbyCover);
          }
      }

	
	  int xp,yp;
	  xp = IPOINT_X(pTrooper->common.tile);
	  yp = IPOINT_X(pTrooper->common.tile);
	  int offit;
	  // require troopers to fight from on the visible map
	  offit = 0;
	  if (xp < (VISIBLE_BOUNDARY+2) || xp  >= (map_width-VISIBLE_BOUNDARY-2)) offit = TRUE;
	  if (yp < (VISIBLE_BOUNDARY+2) || xp  >= (map_height-VISIBLE_BOUNDARY-2)) offit = TRUE;


	  // if going to cover, cant do anything else yet
	  if (went) TrooperFStatus(pTrooper,SEEKING_COVER);
      
	  // if our LOS is bad or distance is too far away, fix it if we can
	  // or if we are offthe visible map, run on first
      else if (bCanShoot == 0 || bCanShoot == -1 || offit)
	  {
          if (TROOPER_IMMOBILE(pTrooper)); // dont move.
          else
          {
              pTrooper->fSpot = 150; // no cover for 150 cycles
              TrooperFixLOS(pTrooper,pVictim);
              if ((d + 5) > hisMaxRange) TrooperFStatus(pTrooper,CHASING);
              else TrooperFStatus(pTrooper,FIXING_SIGHT);
          }
	  }

      else if (bCanShoot == -2) // we are too close
      {
          if (TROOPER_IMMOBILE(pTrooper)); // dont move.
          // try to get farther away by evading...
          else
          {	
              // set up data for spread call
              backupTile = pTrooper->common.tile; // we are here by default
              attackerTile = backupTile;
              victimTile = pVictim->tile;  // he is there
              victimDist = TileDistance(attackerTile,victimTile);
              score = 0;
              PropogateTrafficable((ITEM*)pTrooper,attackerTile,3,TrooperEvadeFind);

              ACTION pace;
              SPOINT goal;
              goal = CenterPointFromTile(backupTile);
              goal = AIRouter(goal,&(pTrooper->routeData),UNIT_ROUTE,
                              pTrooper->common.position,
                              pTrooper->common.facing);
              if (goal.x) pace = AVATAR_RUN;
              else pace = pTrooper->currentPose;

              TrooperFStatus(pTrooper,BACKUP);
              TrooperDoMove(pTrooper,goal,pace,pTrooper->common.facing);
          }
      }

      // otherwise shoot
      else
      {
          TrooperFStatus(pTrooper,FIRING);
          pTrooper->routeData.arrived = TRUE; // we can shoot now, clear data
          TrooperShoot(pTrooper,pVictim,d,myMinRange,myMaxRange,hisMaxRange);
      }
}

///========================================================================
//	Function:		TroopInitWeapon
//	Description:	apply a weapon to a trooper.
///========================================================================

static void	TroopInitWeapon( TROOPER* pTrooper, TROOPER_TYPE eTroopType )
{
	WEAPON_TYPE eWeapon = AiTrooperWeapon(eTroopType);
	pTrooper->common.pWeapon = MakeWeapon(&pTrooper->weapon,eWeapon,MAX_AMMO);
	SetWeaponOwner(pTrooper->common.pWeapon, (ITEM *)pTrooper);
}


///========================================================================
//	Function:		TrooperGone
//	Description:	Now completely dead. Animation complete. Remove him.
///========================================================================

void TrooperGone( TROOPER* pTrooperDead )
{
    TROOPER* pTrooper;
	AVATAR   *pAvatar;
    UNIT* pUnit = pTrooperDead->pUnit;
    BOOL   bFound = FALSE;
	int i;
    if (!pTrooperDead) return;
    pTrooperDead->fSpot = 0;	// no cover area used now

    if (IS_LOCAL_ITEM(pTrooperDead)) TrooperGoneMessageSend(pTrooperDead);

	ASSERT( pTrooperDead->pAvatar );
	pAvatar = pTrooperDead->pAvatar;

    switch(pTrooperDead->pendingAction)
    {
		// are death sequences complete
	case AVATAR_DIE_MELT:
	case AVATAR_DIE_SHOT:
	case AVATAR_DIE_SQUASH:
		if (AvatarLastCompleted(pTrooperDead->pendingAction, pAvatar))
			InsertAnimInCorpseLayer( pAvatar->pAnimation );
		else
			GenerateExplodingAvatar( pAvatar );
		break;

	case AVATAR_DIE_EXPLODE:
	default:
		GenerateExplodingAvatar( pAvatar );
		break;

          // something else like pickup or deploy?
//	default: ;
    };


    // destroy this trooper
    TrooperDelete(pTrooperDead);

    // find his index in list and kill him off.
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
      if (pTrooper != pTrooperDead) continue;

      // remove him from slot and free his space
      free(pTrooperDead);
      pUnit->pTroops[i] = NULL;

      // if he was last trooper, dont need to do anything more.
      if (i == pUnit->nLastTroop) break;

      // otherwise move last guy into his place
      pUnit->pTroops[i] = pUnit->pTroops[pUnit->nLastTroop];
    }

    --pUnit->nLastTroop; 							// new end of trooper list

    // reduce "strength" of unit"
    --pUnit->troops;
      
	// assign  a new leader 
    pUnit->nLeader = 0;					// change to this leader (if any)
  
    // if all troopers are erased, the unit is killed off
    // BUT NOT NOW. Let unit do it later.

    // test that it is correct
    if (pUnit->troops) ASSERT(THE_LEADER(pUnit));
    else ASSERT(THE_LEADER(pUnit) == NULL);
  }

///========================================================================
//	Function:		TrooperSnakePoint
//	Description:	Find open tile nearest me behind some guy in front of me but avoid tile
///========================================================================

static SPOINT	TrooperSnakePoint(TROOPER* pTrooper,int tile) 
{
    SPOINT			closestLocation = OFF_THE_MAP;
    int				d;
    int				minDistance = 1000000;
    UNIT* 			pUnit = TROOPER_UNIT(pTrooper);
	TROOPER*		pLeader = THE_LEADER(pUnit);
	int				nFacing;
    SPOINT 			at;
    TROOPER* 		pBefore = NULL;		// some guy before me
    TROOPER*		junk;
    int i;
    // find a trooper immediately before me in list
    FOR_EACH_TROOPER(pUnit,junk,i)
    {
          if (junk == pTrooper) break;
          pBefore = junk;
    }	
    if (!pBefore)
	{
          TRACE("Warning- trooper snake found no predecessor\n");
          return pTrooper->common.position; // shouldnt happen
	}
	SPOINT where;
	where	= pBefore->lands; // where he will be

    // find the rear facing of this guy
	nFacing = (pBefore->common.facing >> 5);		// remap 0..255 => 0..7
    nFacing += 4;
    if (nFacing > 7) nFacing -= 8;
	IPOINT newtile;

    // look at the rear 3 tiles and see if one is trafficable
    for (i = nFacing - 1; i <= nFacing + 1; ++i)
    {
		at = where;
		at.x  += behindTiles[i + 8].x;
		at.y  += behindTiles[i+8].y;
		newtile = ENCODE_IPOINT(at.x,at.y);
		if (UntrafficableUnit(newtile)) continue;
		if (OffVisible(newtile)) continue;
		if (newtile == tile) continue;

		d = TileDistance(pTrooper->common.tile,newtile);
		if (d < minDistance)
		{
          d = minDistance;
          closestLocation = at;
		}
    }
    // go to an adjoin tile behind
    if (closestLocation.x) where =  closestLocation;
 	return where; // go directly to the guy.
}

///========================================================================
//	Function:		TrooperFormationPoint
//	Description:	Find where this follower should form to
//					The returned point is always trafficable      
//					He will aim for formation at destination of leader
///========================================================================

static SPOINT	TrooperFormationPoint(TROOPER* pTrooper) 
{
    UNIT* 			pUnit = TROOPER_UNIT(pTrooper);
    TROOPER* 		pLeader = THE_LEADER(pUnit);
	TFORMATION*		pFormation;			// specific formation data ptr
    int 			index = TROOPER_INDEX(pTrooper) - 1;
	SPOINT			to = 	pLeader->routeData.destination;
    // precautionary fixes
    if (pLeader->common.tile == 0) return pTrooper->common.position;
    if (to.x < 100 || to.y < 100) return pTrooper->common.position;

    if (index < 0) index = 0;
    if (index >= FORMATION_TROOPER_MAX)
      index = FORMATION_TROOPER_MAX-1; // LIMIT on TROOPERS in FORMATION DATA

    pFormation = &(TROOPPerfectFormations[0]);
    to.x += pFormation->loc[index].x;
    to.y += pFormation->loc[index].y;    
	SARGE* pSarge;
	IPOINT tile;
	tile = ENCODE_IPOINT(to.x,to.y);

	// try not to form on sarge
	pSarge = SargePointer(ITEM_ARMY(pTrooper));
	if (pSarge && pSarge->common.tile == tile)
	{
       // hug the trooper before me Im told to hug
       // will always be a legal tile (and he will always exist)
       to =  TrooperSnakePoint(pTrooper,tile);
	}

    // if I cant be at my formation point, find my alternate point
    else if (UntrafficableUnit(tile) || OffVisible(tile))
    {
       // hug the trooper before me Im told to hug
       // will always be a legal tile (and he will always exist)
       to =  TrooperSnakePoint(pTrooper,tile);
    }

	return to;
}


///========================================================================
//	Function:		TrooperLeaderStill
//	Description:	Tell squad leader to face here if non-zero
///========================================================================

static void TrooperLeaderStill (TROOPER* pLeader, SPOINT* facePoint) 
{
	UNIT* pUnit = pLeader->pUnit;
	SPOINT lands;
	ACTION pose;
	AVATAR* pAvatar;

    // he is dying, so he cant do anything else
    if (!TROOPER_HEALTHY(pLeader)) return;		// no longer there

	pAvatar = pLeader->pAvatar;

    int facing;
    if (facePoint->x)
    {
        facing = GetDirection(&pLeader->common.position,facePoint);
		if (facing == -1)
			facing = pLeader->common.facing;
   }
    else facing = pLeader->common.facing;
    pose = AVATAR_STAND;
    RouterLineRouter(pLeader->common.position,&pLeader->routeData);
      
    // units on ignore just stand
    if (pUnit->poststationBehavior == IGNOREFIRE && IS_POSTSTATION(pUnit))
          pose = AVATAR_STAND;
    else if (pUnit->poststationBehavior == STANDFIRE && IS_POSTSTATION(pUnit))
          pose = AVATAR_STAND;
    else if (pUnit->poststationBehavior == KNEELFIRE && IS_POSTSTATION(pUnit))
          pose = AVATAR_KNEEL;
    else if (pUnit->poststationBehavior == PRONEFIRE && IS_POSTSTATION(pUnit))
          pose = AVATAR_PRONE;
    else if (!TROOPER_UNIT(pLeader)->pTarget);
    else if (ITEM_CLASS(pLeader) == ARMY_MORTAR_MEN) pose = AVATAR_KNEEL;
    else if (ITEM_CLASS(pLeader) == ARMY_GRENADE_MEN) pose = AVATAR_STAND;
    else if (ITEM_CLASS(pLeader) == ARMY_FLAME_MEN) pose = AVATAR_STAND;
    else if (NextToCover(pLeader)) pose = AVATAR_PRONE;

    TrooperSetAvatar(pLeader,pose,facing);

    lands = AvatarWouldMoveTo(AVATAR_STAND, AVATAR_STAND, pLeader->common.facing,
              TRUE,pAvatar);    
    pLeader->lands = lands;
}

///========================================================================
//	Function:		TrooperPace
//	Description:	How fast do we move to get there?
///========================================================================

static ACTION TrooperPace(TROOPER* pTrooper,SPOINT goal)
{
    UNIT* pUnit;
    ACTION pace;					// speed to move at
    pUnit = pTrooper->pUnit;
    int xdif = goal.x - pTrooper->common.position.x;
    if (xdif < 0) xdif = -xdif;
    int ydif = goal.y - pTrooper->common.position.y;
    if (ydif < 0) ydif = -ydif;

    if (goal.x == 0)
    {
      // units on ignore just stand
      if (pUnit->poststationBehavior == IGNOREFIRE && IS_POSTSTATION(pUnit))
          return AVATAR_STAND;	

      else if (pUnit->poststationBehavior == STANDFIRE && IS_POSTSTATION(pUnit))
          return AVATAR_STAND;
      else if (pUnit->poststationBehavior == KNEELFIRE && IS_POSTSTATION(pUnit))
          return AVATAR_KNEEL;
      else if (pUnit->poststationBehavior == PRONEFIRE && IS_POSTSTATION(pUnit))
          return AVATAR_PRONE;


      return AVATAR_STAND; // not trying to go anywhere
    }

    if (ENCODE_IPOINT(goal.x,goal.y) == pTrooper->common.tile)
    {
      pace = AVATAR_STOP_IMMEDIATELY;
      if (pTrooper->action == AVATAR_STOP_IMMEDIATELY )
		pace = AVATAR_STAND;

    } 

    // if he is real close but not yet there, shuffle into place
    else if (xdif < 8 && ydif < 8)
    {
        pace = AVATAR_SHUFFLE;
    }

    // go close
    else if (xdif < 50 && ydif < 50)  
	{
		pace = AVATAR_WALK;
	}

    // if in poststation attackfire and not engaged, leader should walk
    // when not chasing a target
    else if (IS_POSTSTATION(pUnit) &&
        pUnit->poststationBehavior == ATTACKFIRE && !UNIT_ENGAGED(pUnit) &&
        pUnit->focusItem == NULL)
        pace = AVATAR_WALK;

    else if (pUnit->focusSpeed  == NORMAL_SPEED) pace = AVATAR_WALK;

    else // go far fast
    {
        pace = AVATAR_RUN;
    }

    return pace;
}

///========================================================================
//	Function:		TrooperLeaderMove
//	Description:	Tell squad leader to go here.
///========================================================================
static void TrooperLeaderMove (TROOPER* pLeader, SPOINT position) 
{
//Called for the leader when the unit is not engaged.
//Called before any followers are asked to move.

    // he is dying, can do nothing
    if (!TROOPER_HEALTHY(pLeader)) return;
	UNIT* pUnit = TROOPER_UNIT(pLeader);
    ACTION pace;					// speed to move at
     IPOINT atTile = pLeader->common.tile;	// current tile

	SPOINT to;
    to = AIRouter(position,			// long-distance goal
                       &(pLeader->routeData),	
                       UNIT_ROUTE|COLLAPSE,
                       pLeader->common.position,		// where he is now
                       pLeader->common.facing);
    pace = TrooperPace(pLeader,pUnit->destination);
    TrooperDoMove(pLeader,to,pace,pLeader->common.facing);
}

///========================================================================
//	Function:		TrooperFollowerMove
//	Description:	Followers must decide where to go relative to leader.
///========================================================================

static void TrooperFollowerMove(TROOPER* pTrooper,int direction)
{
// Called for followers when the unit is not engaged.
// Called after the leader has computed his move.
// The unit is in either pre-station or post-station status.

    // he is dying and can do nothing further
    if (!TROOPER_HEALTHY(pTrooper)) return; 
    UNIT* pUnit = TROOPER_UNIT(pTrooper);
    ACTION pace;						// speed we will use
	SPOINT formationSpot = OFF_THE_MAP;
    SPOINT spot = OFF_THE_MAP;
    TROOPER* pLeader = THE_LEADER(pUnit);
        
    BOOL useOld = FALSE;
    // if our leaders waypoint goal remains unchanged and we have a
    // formation routing, keep using it until we arrive
    if (SameSPoint(pTrooper->waygoal,pLeader->routeData.destination) &&
          pTrooper->routeData.destination.x)
          useOld = TRUE;
    // OR, if we are far from the moving leader, keep going to catch up
    // w/o worrying about his movements.
    else if (TileDistance(pTrooper->common.tile,pLeader->common.tile) > 8 &&
      pLeader->action == AVATAR_RUN)
          useOld = TRUE;

    if (useOld)
    {
      spot = AIRouter(pTrooper->routeData.destination,
                               &(pTrooper->routeData),
                         UNIT_ROUTE|COLLAPSE,
                         pTrooper->common.position,
                          pTrooper->common.facing);
    }

    // if we have no point assigned 
    if (!spot.x)
    {
      //Find out where we should move to,
      // Dug in guys never move, even if death of earlier troopers would
      // cause a change in formation
      if (TROOPER_IMMOBILE(pTrooper)) 
		  formationSpot = pTrooper->common.position;
      else 
		  formationSpot = TrooperFormationPoint(pTrooper);
      // note where leader is aiming.
      pTrooper->waygoal = pLeader->routeData.destination;
      pTrooper->fTile = ENCODE_IPOINT(formationSpot.x,formationSpot.y);
      spot = AIRouter(formationSpot,
                         &(pTrooper->routeData),
                         UNIT_ROUTE|COLLAPSE,
                         pTrooper->common.position,
                          pTrooper->common.facing);
    }

    // tell him to mark toward center of formation tile
    pace = TrooperPace(pTrooper,spot);
    TrooperDoMove(pTrooper,spot,pace,direction);
}

SPOINT ClosestCorner(SPOINT from,SPOINT to)
{ // find the pixel of FROM closest to TO

    if (!to.x) return OFF_THE_MAP;			// not trying to go to legal place
    
    BOOL diag = TRUE;
    IPOINT fromI = ENCODE_IPOINT(from.x,from.y);
    IPOINT toI = ENCODE_IPOINT(to.x,to.y);
    int xdif = (from.x - to.x) >> 4;
    int ydif = (from.y - to.y) >> 4;
    if (xdif != -1 && xdif != 1) diag = FALSE;
    else if (ydif != -1 && ydif != 1) diag = FALSE;
    if (diag) // should be a diagonal tile
    {
        from.x = IPOINT_X(fromI) << 4;		// start with upperleft corner
        from.y = IPOINT_Y(fromI) << 4;		// start with upperleft corner
        if (ydif < 0) from.y += 15;			// shift to bottom
        if (xdif < 0) from.x += 15;			// shift to right
    }
    else // should be an adjacent tile (but go to nearest corner regardless)
    {
        from.x = IPOINT_X(fromI) << 4;		// start with upperleft corner
        from.y = IPOINT_Y(fromI) << 4;		// start with upperleft corner
       // on horizontal tiles go almost a tile, keeping the y the same
        if (xdif < 0) from.x += 15;
        // on vertical tiles go almost a tile, keeping the x the same
        if (ydif < 0) from.y += 15;
    }
    return from;								// closest corner now found
}

///========================================================================
//	Function:		TrooperFixDirection
//	Description:	Adjust trooper who cant move onto tile aimed at
///========================================================================

static void TrooperFixDirection(TROOPER* pTrooper,SPOINT goal,ACTION pace,
                                SPOINT* at)
{
    int direction;
    SPOINT to,lands;
    
    // route planner will give us an adjacent tile if called again.
    // by computing the full list to goal
    to = AIRouter(goal,
                           &(pTrooper->routeData),
                           pTrooper->routeData.flags,
                           pTrooper->common.position,
                           pTrooper->common.facing);
  
    // find the corner pixel of our tile closest to the destination tile
    // and change our direction to aim to that point if not already there
    SPOINT spot = ClosestCorner(pTrooper->common.position,to);

    if (!spot.x)// router couldnt get us there or didnt need to
	{
		direction = pTrooper->common.facing;
		pace = AVATAR_STAND;
	}

    // we are not at corner yet, so aim there
    else if (pTrooper->common.position.x != spot.x ||
             pTrooper->common.position.y != spot.y) 
    {
        direction = GetDirection(at,&spot);     
		pace = AVATAR_SHUFFLE;
     }
    else				  // else aim into center of tile trying to get to
    {
       direction = GetDirection(at,&to);        
       if (direction == -1) // already on spot?
       {
          pace = AVATAR_STOP_IMMEDIATELY;
          direction = pTrooper->common.facing;
       }
       else pace = AVATAR_SHUFFLE;
    }

    // Ask the avatar where he would end up going to the adjacent tile
    // partially.
 	ASSERT(direction >= 0 && direction < CIRCLE_UNITS);
	lands = AvatarWouldMoveTo(pace,pTrooper->poseDuringRound,direction,FALSE,pTrooper->pAvatar);

   // Not OK to go to corner or tile somehow
   if (UntrafficableUnit(ENCODE_IPOINT(lands.x,lands.y))) 
   {
       pace = AVATAR_STOP_IMMEDIATELY,
       direction = pTrooper->common.facing;
       lands = pTrooper->common.position;
    }
    
   TrooperSetAvatar(pTrooper,pace,direction);

    lands = AvatarWouldMoveTo(pTrooper->pendingAction,pTrooper->poseDuringRound,direction,
              TRUE,pTrooper->pAvatar);    
    pTrooper->lands = lands;
}

///========================================================================
//	Function:		TrooperDoMove
//	Description:	common low-level move ability
///========================================================================

static void TrooperDoMove(TROOPER* pTrooper, SPOINT position, ACTION pace,int direction)
{
// Determines the commands to give the avatar to goto location at pace.
// Location may or may not be adjacent to us. It is presumed straight,however.

    UNIT* pUnit = TROOPER_UNIT(pTrooper);
	SPOINT to;
    SPOINT lands;
    SPOINT at;
    AVATAR* pAvatar;
    pAvatar = pTrooper->pAvatar;
	ASSERT(pAvatar);
    if (!position.x) position = pTrooper->common.position;
    at = pTrooper->common.position;
    to = position;

	if (to.x == 0) // not going anywhere
		pace = AVATAR_STAND;

    // DETERMINE HEADING

    // if already there, maintain heading
	if (pace == AVATAR_STOP_IMMEDIATELY ||
        pace == AVATAR_STAND || pace == AVATAR_KNEEL ||
        pace == AVATAR_PRONE)
	{

      // if no direction supplied by outside, maintain trooper heading
      lands = AvatarWouldMoveTo(pace,pTrooper->poseDuringRound,direction,FALSE,pAvatar);
      
      // units on ignore just stand
      if (pUnit->poststationBehavior == IGNOREFIRE && IS_POSTSTATION(pUnit))
          pace = AVATAR_STAND;
      else if (pUnit->poststationBehavior == STANDFIRE && IS_POSTSTATION(pUnit))
          pace = AVATAR_STAND;
      else if (pUnit->poststationBehavior == KNEELFIRE && IS_POSTSTATION(pUnit))
          pace = AVATAR_KNEEL;
      else if (pUnit->poststationBehavior == PRONEFIRE && IS_POSTSTATION(pUnit))
          pace = AVATAR_PRONE;

      else if (!pUnit->pTarget); // BUG
      else if (ITEM_CLASS(pTrooper) == ARMY_MORTAR_MEN) pace = AVATAR_KNEEL;
      else if (ITEM_CLASS(pTrooper) == ARMY_GRENADE_MEN) pace = AVATAR_STAND;
      else if (ITEM_CLASS(pTrooper) == ARMY_FLAME_MEN) pace = AVATAR_STAND;
      else if (NextToCover(pTrooper)) pace = AVATAR_PRONE;
	}
	else
	{
		direction = GetDirection(&at,&to);		// facing we need to go there
		if (direction == -1) direction = pTrooper->common.facing;
		
        direction = SlideRestrict(direction,at,to);
      

		// Now we have pace and direction, we must see if the avatar will be ok.
		// Ask the avatar where he would end up at end of anim. If illegal, try to fix it.
		lands = AvatarWouldMoveTo(pace,pTrooper->poseDuringRound,direction,TRUE,pAvatar);
		// if full walk is ok, see if partial walk is also (in case of diagonal corner)
		if (!UntrafficableUnit(ENCODE_IPOINT(lands.x,lands.y)))
		{
			lands = AvatarWouldMoveTo(pace,pTrooper->poseDuringRound,direction,FALSE,pAvatar);
		}
 	}

      // set up the planned move
    TrooperSetAvatar(pTrooper,pace,direction);
    pTrooper->lands = lands;

    // Not OK to go here? Find a better way
    if (UntrafficableUnit(ENCODE_IPOINT(pTrooper->lands.x,pTrooper->lands.y)))
    {
        TrooperFixDirection(pTrooper,pTrooper->routeData.destination,pace,&at);
    }
}

static void	TrooperSetFace(TROOPER* pTrooper,int direction)
{
    ASSERT(direction >= 0 && direction < CIRCLE_UNITS);

    // fix the assert problem
    if (direction < 0) direction += CIRCLE_UNITS;
    if (direction >= CIRCLE_UNITS) direction -= CIRCLE_UNITS;

	pTrooper->pendingDirection = direction;
}

//========================================================================
//	Function:		TrooperSetAvatar
//	Description:	change the pending setting for avatar of this trooper
///========================================================================

static void	TrooperSetAvatar(TROOPER* pTrooper,ACTION action,int direction)
{
	// may not change avatar. Even if he is now on untrafficable tile (squashed or whatever)
	if( (pTrooper->action == AVATAR_DIE_MELT || pTrooper->action == AVATAR_DIE_EXPLODE || pTrooper->action == AVATAR_DIE_SHOT || pTrooper->action == AVATAR_DIE_SQUASH)
			&& action != pTrooper->action)
			return;
		// may not change avatar. Even if he is now on untrafficable tile (squashed or whatever)
	if( (pTrooper->pendingAction == AVATAR_DIE_MELT || pTrooper->pendingAction == AVATAR_DIE_EXPLODE || pTrooper->pendingAction == AVATAR_DIE_SHOT || 
		pTrooper->pendingAction == AVATAR_DIE_SQUASH)
			&& action != pTrooper->pendingAction)
			return;

    pTrooper->pendingAction = action;
    TrooperSetFace(pTrooper,direction);
}

///========================================================================
//	Function:		SafeCover
//	Description:	see if we hit victims cover and not him
///========================================================================

static BOOL SafeCover(TROOPER* pTrooper,ITEM* pVictim)
{
    WEAPON_TYPE eWeapon = pTrooper->common.pWeapon->eWeapon;
    BOOL cover;
    // non-linear weapons get to ignore cover
    if (eWeapon != ARMY_LIGHT_MACHINE_GUN &&
        eWeapon != ARMY_HEAVY_MACHINE_GUN &&
         eWeapon != ARMY_MEDIUM_MACHINE_GUN) return FALSE;
  
    // find out which way we are hitting him and reverse it so his aim toward us.
	int direction = NormalizeFacingAdd(pTrooper->common.facing, (CIRCLE_UNITS/2));
	direction >>= 5; // 1 of 8 directions

    // check the 3 adjoining tiles with that direction as center
    int i;
	int access;
    SPOINT covered;
    IPOINT coveredIndex;
    cover = FALSE;
    for (i = -1; i <= 1; ++i)
    {
		access = direction + i + 8;
        covered.x = pVictim->position.x + behindTiles[access].x;
        covered.y = pVictim->position.y + behindTiles[access].y;
        coveredIndex = ENCODE_IPOINT(covered.x,covered.y);
       
		
		if (UntrafficableUnit(coveredIndex)) cover = TRUE;
    }
        
    if (!cover) return FALSE;

    // 50% of time you hit cover instead of him
    if (randInt(0,100) < 50)
        return TRUE;

    return FALSE;
}      

///========================================================================
//	Function:		NextToCover
//	Description:	Are we next to cover?
///========================================================================

static BOOL NextToCover(TROOPER* pTrooper)
{
    int i;
    SPOINT covered;
    IPOINT coveredIndex;
    for (i = 0; i <= 7; ++i)
    {
        covered.x = pTrooper->common.position.x + behindTiles[i].x;
        covered.y = pTrooper->common.position.y + behindTiles[i].y;
        coveredIndex = ENCODE_IPOINT(covered.x,covered.y);
        if (UntrafficableUnit(coveredIndex)) return TRUE;
    }

    return FALSE;
 }


///========================================================================
//	Function:		TrooperHitByMissile
//	Description:	will this trooper stop a missile and take damage from it?
///========================================================================

BOOL TrooperHitByMissile(TROOPER* pTrooper, SHORT height)
{
	ACTION pose = AvatarPose(pTrooper->pAvatar);

	return AvatarHitByMissile(pose, height);
}


extern SPRITE** Chevron;

void DrawTrooperChevron( TROOPER *pTrooper )
{
	ANIM	*pAnim;
	int		h, w;
	int		x, y;
	RECT	rect, irect;

	if( !pTrooper->pAvatar )
		return;
	if( pTrooper->pUnit->beInvisible == TRUE)
		return;
	pAnim = pTrooper->pAvatar->pAnimation;
	if( !pAnim->pSprite )
		return;
	if( pAnim->world_pos.x == 0 || pAnim->world_pos.y == 0 )
		return;
	w = Chevron[1]->srect.right;
	h = Chevron[1]->srect.bottom;
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

	DrawShadeSpriteToOverlayLayer( x, y, (BYTE *)(Chevron[1]->pShadow), irect, PLIGHT_TABLE );
}


///========================================================================
//								EOF
///========================================================================


// vis is a list of shorts terminated by 0 to see the next tile (local offset)

static int GetTilesBetween(IPOINT from, IPOINT to, short int *pts){ 
    
    int xdif, ydif,xstep,ystep,i, xcnt,ycnt,n = 0;
    int fromx = IPOINT_X(from);
    int fromy = IPOINT_Y(from);
    int tox = IPOINT_X(to); IPOINT index;
    int toy = IPOINT_Y(to),delta;
    IPOINT at = from;
	if (from == to)
	{
		pts[0] = 0;
		return 1;
	}

	/* set up step count and increment */
	xdif = tox - fromx;
	ydif = toy - fromy;
    xstep = (xdif >= 0) ? xdif : -xdif;
    ystep = (ydif >= 0) ? ydif : -ydif;
    xcnt = ycnt = 0;
    if (xstep >= ystep){ /* walk x */
        xdif = (xdif > 0) ? 1 : -1;

        /* now step one point at a time */
        for (i=1; i <= xstep; ++i) {
            /* per step expected location */
            fromx += xdif;
            ycnt += ydif;
            ystep = (ycnt / xstep) + fromy;
            index = INDEX(fromx,ystep);
            delta = index-at;
            pts[n++] = delta;
            at = index;
        }
    }
    else{
        ydif = (ydif > 0) ? 1 : -1;

        /* now step one point at a time */
        for (i=1; i <= ystep; ++i) {
            fromy += ydif;
            xcnt += xdif;
            xstep = (xcnt / ystep) + fromx;
            index = INDEX(xstep,fromy);
            delta = index-at;
            pts[n++] = delta;
            at = index;
        }
    }

    pts[n-1] = 0; // replace goal with end of list marker
    return n+1;  // offset + end marker
}

static void InitVisibilityArray(){

    long offset,size = 0; short int *setptr; short int *set;
    IPOINT center = INDEX(100,100); // someplace in the middle
    IPOINT at;
    int x,y,n,offsetx,offsety,bytes;

    ASSERT(visibilityRange > (320 >> 4)); // we need to match vis range

    maxvisblock = ((2 * (visibilityRange+1)) * (2 * (visibilityRange+1)));
	maxvisblock /= 2;
	set = (short int *) malloc( sizeof(short int) * 170000);
	ASSERT(set);
    ASSERT(maxvisblock < 5000); // our index limit
    setptr = set;
    for (x = -visibilityRange; x <= +visibilityRange; ++x)
    {
        for (y = 0; y <= +visibilityRange; ++y)
        {
            at = center + x + (y * map_width); // next tile
			if (at <= center) continue;
			offsetx = IPOINT_X(at) - IPOINT_X(center);
			offsety = IPOINT_Y(at) - IPOINT_Y(center);
		    offsetx += visibilityRange;
            ASSERT(offsetx >= 0 && offsety >= 0);
            offset = offsetx + (offsety * ((visibilityRange+1) * 2));
            ASSERT(offset < maxvisblock);
            tileIndices[offset] = size;				// ptr to start of list
            n = GetTilesBetween(center,at,setptr);    // put data into list
			ASSERT(n>= 0);
			size += n;
			ASSERT(size < 170000);
            setptr += n;							// go to next data
        }
    }
	size += 2; // margin of safety
	bytes =  sizeof(short int) * size;
    tileLineOffsets = (short int *) malloc(bytes);
	ASSERT(tileLineOffsets);
	memcpy((void*) tileLineOffsets, (void*) set, bytes);
//	TRACE("using %d bytes of vismap\n",bytes);
	free(set);
}

static void FreeVisibilityArray(){

	if (tileLineOffsets)
	{
		free(tileLineOffsets);
		tileLineOffsets = NULL;
	}
}

SPOINT OffPoint(SPOINT from,int direction,int distance)
{
   from.x += (short)(cos_table[direction] * distance);
   from.y += (short)(sin_table[direction] * distance);
   return from;
}