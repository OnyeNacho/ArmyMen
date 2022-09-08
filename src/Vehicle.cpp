/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Vehicle.cpp $
//
//	DESCRIPTION:	Vehicle movement
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Vehicle.cpp 374   4/15/98 12:00p Bwilcox $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Vehicle.cpp $
//  
//  374   4/15/98 12:00p Bwilcox
//  indenting normal traces and fixing setusercontrol setaicontrol
//  
//  373   4/10/98 6:12p Bwilcox
//  
//  372   4/10/98 6:07p Bwilcox
//  
//  371   4/10/98 11:19a Phu
//  change to vehicle collision allowance
//  
//  370   4/10/98 1:39a Nrobinso
//  reset anim callback
//  
//  369   4/10/98 1:14a Bwilcox
//  keeping deadposition as unique data
//  
//  368   4/09/98 9:57p Dmaynard
//  Added ItemSpecialUpdatePosition for cases where items enter and leave
//  the universe.
//  
//  367   4/09/98 8:50p Bwilcox
//  attemp to get pad status correct
//  
//  366   4/09/98 6:42p Dmaynard
//  Remove extraneous calls to ItemUpdatePad.  This gets called once per
//  loop from Army.cpp for everthing anyway.
//  
//  365   4/09/98 2:19p Phu
//  
//  364   4/08/98 3:12p Phu
//  improve vehicle-vehicle collision
//  
//  363   4/08/98 11:44a Bwilcox
//  husk vehicles masks
//  
//  362   4/07/98 3:23p Nrobinso
//  change order of sound play and volume set
//  
//  361   4/07/98 2:13p Nrobinso
//  make illelgally deployed message debug only
//  
//  360   4/03/98 9:01p Bwilcox
//  clean up vehicle movement layer code
//  
//  358   4/03/98 3:06p Nrobinso
//  truck and jeep can't rotate w/o moving
//  
//  357   4/02/98 6:29p Phu
//  typecast to avoid warnings
//  
//  356   4/02/98 1:48p Bwilcox
//  cleanups in event triggering and traces
//  
//  355   4/01/98 5:01p Bwilcox
//  fix movement chekcing for ai vehicles back to easy
//  
//  354   4/01/98 12:15p Phu
//  
//  353   3/31/98 5:27p Dmaynard
//  #ifnedef'ed    NO_AUDIO  the vehiclePlaySound rountine.  Was generating
//  a TRACE per frame if we compiled with NO_AUDIO.
//  
//  
//  352   3/31/98 12:42p Bwilcox
//  
//  351   3/31/98 12:35p Bwilcox
//  fixed bug i introduced moving code
//  
//  350   3/31/98 11:46a Bwilcox
//  try stop vehicle off map on remote
//  
//  349   3/30/98 10:11p Nrobinso
//  switch to animtime, which allows for pauses
//  
//  348   3/26/98 9:21p Bwilcox
//  
//  347   3/26/98 9:00p Bwilcox
//  subtracttraff dones less for vehicles
//  
//  346   3/26/98 8:23p Phu
//  vehicle fudge
//  
//  345   3/26/98 2:53p Bwilcox
//  
//  344   3/26/98 2:39p Bwilcox
//  vehicle in movement layer split into new layer
//  
//  343   3/25/98 3:43p Bwilcox
//  fixed introducted bug
//  
//  342   3/25/98 2:03p Bwilcox
//  fixing remote vehicle bug
//  
//  341   3/25/98 11:49a Bwilcox
//  vehicle invulnerable if sarge is cheat invulnerable
//  
//  340   3/25/98 10:05a Bwilcox
//  
//  339   3/25/98 9:49a Bwilcox
//  
//  338   3/25/98 9:39a Bwilcox
//  
//  337   3/25/98 9:34a Bwilcox
//  
//  336   3/25/98 8:51a Bwilcox
//  vehicle smoothing
//  
//  335   3/25/98 8:28a Bwilcox
//  vehicle smoothing across net
//  
//  334   3/23/98 7:10p Phu
//  
//  333   3/23/98 6:42p Phu
//  don't crush troopers at a different height!
//  
//  332   3/22/98 2:16p Nrobinso
//  full loop for tank
//  
//  331   3/22/98 1:24p Bwilcox
//  
//  330   3/20/98 12:06a Nrobinso
//  clear mouse buttons when not used by sarge
//  
//  329   3/19/98 7:50p Nrobinso
//  don't allow getting out of vehicle while it is moving
//  
//  328   3/19/98 1:49p Nrobinso
//  change vehicle sfx
//  
//  327   3/18/98 2:16p Nrobinso
//  add bullet hit sound to vehicles; add making of chips; armored vs flame
//  
//  326   3/18/98 3:13a Nrobinso
//  remove traces
//  
//  325   3/17/98 5:41p Nrobinso
//  add a turret count so turret can turn independently of vehicle
//  
//  324   3/16/98 3:32p Aburgess
//  correction of Audio deletion
//  
//  323   3/16/98 12:56p Aburgess
//  modifications to support vehicle decel,acel,and looping
//  
//  322   3/14/98 3:41p Bwilcox
//  vehicle computes fire from turret, not vehicle
//  
//  321   3/13/98 8:03p Nrobinso
//  sarge doesn't trnasfer in or out of vehicles if he isn't in control
//  
//  320   3/13/98 5:49p Nrobinso
//  set turret flag for non-convoy vehicles
//  
//  319   3/13/98 2:57p Bwilcox
//  fixed weaponless vehicles from trying to fire
//  
//  318   3/13/98 3:12p Phu
//  remove debug info for vehicle collision
//  
//  317   98-03-12 22:58 Dmaynard
//  remove unused volume data; only allocate 2 anims for vehicle instead of
//  3
//  
//  316   3/12/98 4:32p Phu
//  no weapon for convoy
//  
//  315   3/12/98 3:17p Phu
//  new vehicle collision methodology
//  
//  314   3/12/98 2:34p Bwilcox
//  enter closest vehicle (center)
//  
//  313   3/09/98 3:16p Phu
//  fix screen flash, vehicle sizes
//  
//  312   3/08/98 4:41p Phu
//  don't allow switch to other weapons when in vehicle
//  
//  311   3/08/98 3:20p Phu
//  prevent sarge from appearing in movement mask of dead vehicle.
//  don't allow fire if weapon is empty
//  
//  310   3/08/98 1:05a Nrobinso
//  only load anims for vehicle types that exist in the map
//  
//  309   3/07/98 11:54p Nrobinso
//  setup macro for debug layer
//  
//  308   3/07/98 10:45p Nrobinso
//  turn off sf if vehicle dies
//  
//  307   3/06/98 4:14p Phu
//  loading bar
//  
//  306   3/04/98 11:46a Phu
//  fix crash bug in UpdatePosing() if sarge had no avatar.
//  don't allow vehicle deployment on sarge
//  create convoy mask
//  
//  305   3/04/98 11:20a Phu
//  make mask for convoy
//  
//  304   3/03/98 1:16p Phu
//  don't assume vehicle has turret!
//  
//  303   3/02/98 12:24p Nrobinso
//  don't need to look for alt down
//  
//  302   2/28/98 9:37p Bwilcox
//  better vehicle control
//  
//  301   2/27/98 5:53p Nrobinso
//  fix sfx bug
//  
//  300   2/25/98 8:51p Nrobinso
//  make sure carried unit isn't in HQ
//  
//  299   2/25/98 5:40p Nrobinso
//  set vehicle dead
//  
//  298   2/23/98 1:03p Bwilcox
//  trooper run over only to limit of his strength
//  
//  297   2/21/98 5:49p Nrobinso
//  vehicle sounds
//  
//  296   2/20/98 6:17p Nrobinso
//  remove static sfx calls
//  
//  295   2/20/98 1:19p Nrobinso
//  fix up sounds
//  
//  294   2/20/98 12:01p Bwilcox
//  units die in dying vehicle
//  
//  293   2/19/98 4:09p Phu
//  
//  292   2/18/98 2:48p Phu
//  do not assume pHitme is valid
//  
//  291   2/18/98 2:06p Bwilcox
//  revsered tad args in call, reenabled tadbeing hit
//  
//  290   2/18/98 12:25p Bwilcox
//  tadbeing hit now called. removed useless formation code. removed attack
//  wander code
//  
//  289   2/17/98 7:52p Nrobinso
//  remove static sfx calls
//  
//  288   2/17/98 6:17p Nrobinso
//  load vehicle AXS files
//  
//  287   2/17/98 4:27p Phu
//  insert exploded vehicle husk remains into corpse layer.
//  Eliminate double explosions in single player
//  
//  286   2/17/98 3:18p Nrobinso
//  vehicles check for infinite ammo
//  
//  285   2/17/98 3:05p Nrobinso
//  put debug commands on final compile flag
//  
//  284   2/17/98 12:22p Phu
//  slow vehicle movement
//  
//  283   2/17/98 9:01a Aburgess
//  vehicles and weapons now use the new audioPlay interface
//  
//  281   2/16/98 4:43p Phu
//  change missiles back to axr
//  
//  280   2/16/98 4:16p Nrobinso
//  allow jeep to fire in all directions
//  
//  279   2/16/98 3:08p Phu
//  change missiles to *.axs instead of *.axr
//  
//  278   2/16/98 12:03p Phu
//  pass along fromUID with explosions
//  
//  277   2/13/98 7:01p Nrobinso
//  fix vehicle firing
//  
//  276   2/13/98 5:26p Nrobinso
//  fix vehicle turrets on death
//  
//  275   2/13/98 12:22p Nrobinso
//  move joystick access up a level
//  
//  274   2/13/98 12:15p Phu
//  check movement for stuff
//  
//  273   2/13/98 11:12a Nrobinso
//  make a common joystick routine
//  
//  272   2/12/98 9:44p Nrobinso
//  remove unused code; share joystick code with sarge
//  
//  271   2/12/98 6:38p Phu
//  vehicle armor = 1/10 of collision armor
//  
//  270   2/12/98 6:32p Phu
//  reduce damage done by stuff for crying out loud!
//  
//  269   2/12/98 12:53p Nrobinso
//  new sounds
//  
//  268   2/11/98 4:27p Nrobinso
//  no turret if truck
//  
//  267   2/11/98 2:26p Nrobinso
//  go back to move.axr
//  
//  266   2/11/98 12:04p Nrobinso
//  move anim should be a axs
//  
//  265   2/10/98 3:01p Phu
//  only use bmp as mask for vehicles
//  
//  264   2/10/98 2:52p Phu
//  npc vehicle stop moving if collide
//  
//  263   2/10/98 2:21p Phu
//  firing heights
//  
//  262   2/10/98 1:27p Bwilcox
//  changed animfiguremovevehicle to animfigurewouldmoveto and
//  merged in common code from vehicle update into it
//  
//  261   2/10/98 12:51p Bwilcox
//  cleanup vehicle update a bit
//  
//  259   2/10/98 12:16p Bwilcox
//  added focusitem to vehicle
//  
//  258   2/10/98 12:11p Bwilcox
//  npc can spin jeeps and halftracks w/o moving, other minor cleanups
//  
//  257   2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  256   2/06/98 7:34p Bwilcox
//  vehicle router improvments
//  
//  255   2/06/98 4:32p Bwilcox
//  making addvehicletomove visible
//  
//  254   2/06/98 3:56p Phu
//  real collision using the bmp for vehicles/units
//  better damage control on vehicles
//  
//  253   2/06/98 11:42a Phu
//  husks
//  
//  252   2/05/98 3:28p Nrobinso
//  track sarge kills of vehicles & vehicles killed
//  
//  251   2/05/98 12:15p Bwilcox
//  tighter vehicle collision
//  
//  250   2/04/98 3:34p Bwilcox
//  allow npc vhiecle onto blocked tile if not currently on one
//  
//  249   2/01/98 5:45p Nrobinso
//  remove TESTPATH
//  
//  248   1/30/98 11:41a Nrobinso
//  move mouse firing check out to common sarge/vehicle code
//  
//  247   1/29/98 4:14p Nrobinso
//  
//  246   1/28/98 7:27p Bwilcox
//  
//  245   1/28/98 7:17p Bwilcox
//  
//  244   1/28/98 4:00p Phu
//  
//  243   1/22/98 6:45p Nrobinso
//  use SetPath
//  
//  242   1/20/98 4:21p Phu
//  test code for expanding ownership areas in mp
//  
//  241   1/20/98 3:53p Phu
//  insert vehicle anim in corpse layer
//  
//  240   1/20/98 11:37a Bwilcox
//  implemented vehicleundeploy
//  
//  239   1/20/98 9:09a Nrobinso
//  check for player in vehicle dead callback
//  
//  238   1/20/98 12:50a Nrobinso
//  activate vehicle callback
//  
//  237   1/17/98 8:17p Nrobinso
//  remove unused code
//  
//  236   1/13/98 7:18p Phu
//  keep vehicles in boundary
//  
//  235   1/13/98 6:05p Bwilcox
//  expanded distance from vehicle allowing entry
//  
//  234   1/13/98 12:04p Bwilcox
//  vehicle deploy is no longer on top of sarge, but north if possible
//  
//  233   1/12/98 8:36p Phu
//  vehicle damage fix
//  
//  231   1/12/98 4:48p Phu
//  acquire armor value
//  
//  230   1/10/98 11:29a Phu
//  decelerate a vehicle when there is no driver
//  
//  229   1/09/98 4:20p Phu
//  redraw when items change visibility is fixed
//  
//  228   1/06/98 3:35p Phu
//  Mouse control debug menus
//  
//  
//  3     6/25/96 9:54p Nrobins
//  added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "audio.h"			// AUDIO       defines, structures, and prototypes
#include "sounds.h"			// AUDIO       sfx sound effects equates

#include "Ai.h"
#include "AiAccess.h"
#include "anim.h"
#include "AnimFile.h"
#include "Army.h"
#include "ArmyMsg.h"
#include "avatar.h"
#include "comm.h"
#include "damage.h"
#include "Disp.h"
#include "explosions.h"
#include "GameFlow.h"
#include "Input.h"
#include "MainFrm.h"
#include "Map.h"
#include "miscfile.h"
#include "newdoor.h"
#include "object.h"
#include "StratMap.h"
#include "Tad.h"
#include "trooper.h"
#include "unit.h"
#include "ui.h"
#include "Vehicle.h"
#include "VehicleMsg.h"
#include "item.h"
#include "Weapon.h"
#include "pad.h"
#include "aix.h"
#include "sarge.h"
#include "wobject.h"
#include "husk.h"
#include "commands.h"
#include "aibtank.h"
#include "Vehicle.dat"


/////////////////////////////////////////////////////////////////////////////
// Debugging support
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char scriptDebug;
/////////////////////////////////////////////////////////////////////////////
//					#defines
/////////////////////////////////////////////////////////////////////////////
#define TURN_DELAY			60
#define TURN_TURRET_DELAY	60

#define VEHICLE_MAX_UNTRAFFICABLE_TILES 4 //the maximum number of untrafficable
										  //tiles a vehicle can ever be over (when 
									      //trying to get unstuck)

#define VEHICLE_STUCK_FRAMES_BEFORE_UNSTICK 20 //how many frames the vehicle has to be
											   //stuck before it starts allowing some number of
											   //untrafficable tiles

#define VEHICLE_TRAFFICABILITY 16 //the amount a vehicle adds to the movement layer

#define FRAMES_BEFORE_ADD_TO_MOVEMENT_LAYER 2 //how many frames the vehicle has to be nonmoving
												//before we add it to the movement layer

#define ACCELERATE_SOUND	0
#define DECELERATE_SOUND	1
#define SLOW_LOOP_SOUND		2
#define HALF_LOOP_SOUND		3
#define FULL_LOOP_SOUND		4
#define OFF_SOUND			5
#define DELETE_SOUND		6

typedef struct
{
	ULONG	audioID;			
	ULONG	sndID;
} AUDIO_PAIR;

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
unsigned char vehiclemasks[ARMY_LAST_VEHICLE][32][4][4][16];

short vehiclesizes[ARMY_LAST_VEHICLE][4]=//front, back, left, right (in pixels, from hotspot)
{
	{0, 0, 0, 0},
	{57, 7, 14, 22},
	{51, 34, 22, 23},
	{50, 40, 20, 20},
	{50, 40, 20, 20},
	{0, 0, 0, 0}
};

BOOL cheat_move = FALSE;
extern unsigned char *pMarkers;
extern char sargeImmune;
/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////

static ULONG vehicle_snds[ARMY_LAST_VEHICLE] = {
	SND_NULL_SND_ID, JEEP_FULL_LOOP, TANK_FULL_LOOP, HT_FULL_LOOP, TRUCK_FULL_LOOP };

#define MAX_MOVEMENT 0x0F
#define MIN_MOVEMENT 0x0
#define MOVEMENT_VALUES 16

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////
extern void AIControlUI();

/////////////////////////////////////////////////////////////////////////////
//					LOCAL Prototypes
/////////////////////////////////////////////////////////////////////////////
static void	VehicleSet( VEHICLE *pVehicle);
static void	VehicleSetFire(VEHICLE *pVehicle,SPOINT from);
static void	VehicleLockTurret(VEHICLE* pVehicle, int spin);
static void PlayVehicleSound(VEHICLE *pVehicle, int type);

/////////////////////////////////////////////////////////////////////////////
//					     Code
/////////////////////////////////////////////////////////////////////////////

extern int MouseDx;
extern int MouseDy;
extern char MouseOn;
extern char MouseDxRotate;
extern char MouseTurret;

int vehaccelwait = 0;


inline int  CropRange( int n, int min, int max )
{
	if( n > max )
		return( max );
	else
	if( n < min )
		return( min );
	else
		return n;
}


BOOL VehicleTurnTurret(VEHICLE* pVehicle, int turn_command, int vehicle_facing)	{
	ANIM *pAnim = pVehicle->pAnimation;
	int facing;

	if (pVehicle->tcount < TURN_TURRET_DELAY)
		return TRUE;

	pVehicle->tcount = 0;

	facing = pVehicle->gun_facing;
	if( MouseDxRotate && MouseDx != 0 )
	{
		if( MouseDx > GROSS_MOTOR )
			facing -= GROSS_MOTOR;
		else
		if( MouseDx < -GROSS_MOTOR )
			facing += GROSS_MOTOR;
		else
			facing -= MouseDx;
	}
	else
	if( MouseDx != 0 || MouseDy != 0 )
	{
		int Dx, Dy;

		Dx = CropRange( MouseDx, -GROSS_MOTOR, GROSS_MOTOR );
		Dy = CropRange( MouseDy, -GROSS_MOTOR, GROSS_MOTOR );
		if( abs( MouseDy ) > abs( MouseDx ) )
			goto mousevert;
		if( MouseDx != 0 )
		{
			if( facing >= 218 || facing <= 38 )
				facing -= MouseDx;
			else
			if( facing >= 90 && facing <= 166 )
				facing += MouseDx;
			else
			if( facing <= 64 || facing >= 192 )
				facing -= (MouseDx >> 1);
			else
				facing += (MouseDx >> 1);
		}
mousevert:
		if( MouseDy != 0 )
		{
			if( facing >= 154 && facing <= 230 )
				facing -= MouseDy;
			else
			if( facing >= 28 && facing <= 102 )
				facing += MouseDy;
			else
			if( facing >= 128 )
				facing -= (MouseDy >> 1);
			else
				facing += (MouseDy >> 1);
		}
	}
	else
	{
		switch(turn_command)	
		{
			case LEFT_VEHICLE:
				facing += GROSS_MOTOR;
				break;
			case RIGHT_VEHICLE:
				facing -= GROSS_MOTOR;
				break;
			case FINE_LEFT_VEHICLE:
				facing += FINE_MOTOR;
				break;
			case FINE_RIGHT_VEHICLE:
				facing -= FINE_MOTOR;
				break;
			case VERYFINE_LEFT_VEHICLE:
				facing += 1;
				break;
			case VERYFINE_RIGHT_VEHICLE:
				facing -= 1;
			break;
			default:
				facing += turn_command - 1000;
		}
	}
	facing = NormalizeFacing(facing);
	vehaccelwait += gpGame->dwDeltaTime;
	if( vehaccelwait > 120 )
	{
		vehaccelwait = 0;
		vehaccelwait++;
		if( vehaccelwait > GROSS_MOTOR )
			vehaccelwait = GROSS_MOTOR;
	}

	// limit gun facing
	if (ITEM_CLASS(pVehicle) == ARMY_HALFTRACK)	{
		int diff = abs(facing - vehicle_facing);
		if ((diff > 32) && (diff < 224)) return FALSE;
	}

	pVehicle->gun_facing = facing;
	AnimForceFacing(&pAnim[TURRETANIM], facing);

	// TBD: check for ability to turn turret that way
	return TRUE;
}

static void VehicleLockTurret(VEHICLE* pVehicle, int spin)	{
	ANIM *pAnim = pVehicle->pAnimation;
	int facing = pVehicle->gun_facing + spin;
	pVehicle->gun_facing = NormalizeFacing(facing);
	AnimForceFacing(&pAnim[TURRETANIM], pVehicle->gun_facing);
}

void VehicleTurretTurnAnalog(VEHICLE *pVehicle, int turn_amount)
{
	ANIM *pAnim = pVehicle->pAnimation;
	int facing;

	facing = pVehicle->gun_facing;

	facing += (int)(((int)gpGame->dwDeltaTime*GROSS_MOTOR*turn_amount)*(0.5)/(-1000)/33);

	facing = NormalizeFacing(facing);

	pVehicle->gun_facing = facing;
	AnimForceFacing(&pAnim[TURRETANIM], facing);
}

void VehicleTurn(VEHICLE* pVehicle, int turn_command)	{
	if (pVehicle->count < TURN_DELAY)
		return;

	pVehicle->count = 0;

	int facing = pVehicle->spin;
	switch(turn_command)	{
		case LEFT_VEHICLE:
			facing += GROSS_MOTOR;
			break;
		case RIGHT_VEHICLE:
			facing -= GROSS_MOTOR;
			break;
		case FINE_LEFT_VEHICLE:
			facing += FINE_MOTOR;
			break;
		case FINE_RIGHT_VEHICLE:
			facing -= FINE_MOTOR;
			break;
	}
	pVehicle->spin = facing;
}


void VehicleSetDesiredVelocity(VEHICLE* pVehicle, int velocity /*-1000 to 1000*/)
{
	int		desiredvelocity;
	DWORD	dwDeltaTime = gpGame->dwDeltaTime;
	int		velocity_change;
	BOOL	slow = FALSE;
	int		max_velocity = pVehicle->max_velocity;
	int		min_velocity = pVehicle->min_velocity;

	if (velocity>=0)
		desiredvelocity=((int)pVehicle->max_velocity)*velocity/1000;
	else
		desiredvelocity=((int)pVehicle->min_velocity)*velocity/(-1000);

	if( user_action & DO_SLOW )	{
		slow = TRUE;
		desiredvelocity = desiredvelocity >> 1;
	}

	if (desiredvelocity > 0)
	{
		if (pVehicle->full_velocity < 0)
		{
			velocity_change = ((gpGame->dwDeltaTime << 4) / pVehicle->brake_coefficient);
			pVehicle->full_velocity += velocity_change;
			if (pVehicle->full_velocity > 0)
				pVehicle->full_velocity = 0;
			if (pVehicle->full_velocity > desiredvelocity)
				pVehicle->full_velocity = desiredvelocity;
		}
		else if (pVehicle->full_velocity < desiredvelocity)
		{
			velocity_change = ((gpGame->dwDeltaTime<<4) / pVehicle->accel_coefficient);
			pVehicle->full_velocity += velocity_change;
			if (pVehicle->full_velocity > desiredvelocity)
				pVehicle->full_velocity = desiredvelocity;
		}
		else if (pVehicle->full_velocity > desiredvelocity)
		{
			velocity_change = ((gpGame->dwDeltaTime << 4) / pVehicle->brake_coefficient);
			pVehicle->full_velocity -= velocity_change;
			if (pVehicle->full_velocity < desiredvelocity)
				pVehicle->full_velocity = desiredvelocity;
		}
	}
	else if (desiredvelocity<0)
	{
		if (pVehicle->full_velocity>0)
		{
			velocity_change = ((gpGame->dwDeltaTime << 4) / pVehicle->brake_coefficient);
			pVehicle->full_velocity -= velocity_change;
			if (pVehicle->full_velocity < 0)
				pVehicle->full_velocity = 0;
			if (pVehicle->full_velocity < desiredvelocity)
				pVehicle->full_velocity = desiredvelocity;
		}
		else if (pVehicle->full_velocity>desiredvelocity)
		{
			velocity_change=((gpGame->dwDeltaTime<<4) / pVehicle->reverse_coefficient);
			pVehicle->full_velocity-=velocity_change;
			if (pVehicle->full_velocity<desiredvelocity)
				pVehicle->full_velocity=desiredvelocity;
		}
		else if (pVehicle->full_velocity<desiredvelocity)
		{
			velocity_change=((gpGame->dwDeltaTime << 4) / pVehicle->brake_coefficient);
			pVehicle->full_velocity+=velocity_change;
			if (pVehicle->full_velocity>desiredvelocity)
				pVehicle->full_velocity=desiredvelocity;
		}
	}
	else //desiredvelocity==0
	{
		velocity_change = ((gpGame->dwDeltaTime << 4) / pVehicle->brake_coefficient);

		if (pVehicle->full_velocity > 0)
		{
			pVehicle->full_velocity -= velocity_change;
			if (pVehicle->full_velocity < 0)
			{
				pVehicle->full_velocity = 0;
			}
		}
		else if (pVehicle->full_velocity < 0)
		{
			pVehicle->full_velocity += velocity_change;
			if (pVehicle->full_velocity > 0)
			{
				pVehicle->full_velocity = 0;
			}
		}
	}
}


static void PlayVehicleSound(VEHICLE *pVehicle, int type)	{
#ifndef AUDIO_OFF
    VEHICLE_TYPE eVehicleType = (VEHICLE_TYPE) ITEM_CLASS(pVehicle);
	ULONG sndID;
	ULONG audioID;
	int volume;
	AUDIO_IDS*	pAudioPtr;

	switch (type)	
	{
		case OFF_SOUND:
			if (pVehicle->looping_sndID != SND_NULL_SND_ID)
				SndSetVolumePercent(pVehicle->looping_sndID, 0, FALSE);
			break;
		case DELETE_SOUND:
			if (pVehicle->looping_sndID != SND_NULL_SND_ID)
			{
				TRACE("Deleting Vehicle sound: %d\n", pVehicle->looping_sndID);
				sfxDeleteSnd( pVehicle->looping_sndID );
				audioDeleteSnd( pVehicle->looping_sndID );
				pVehicle->looping_sndID = SND_NULL_SND_ID;
			}
			break;
		case FULL_LOOP_SOUND:
			volume = abs((pVehicle->full_velocity * 100)/pVehicle->max_velocity);
			volume = max(volume, 20);

			if (pVehicle->looping_sndID != SND_NULL_SND_ID)	
			{
				SndSetVolumePercent(pVehicle->looping_sndID, volume, FALSE);
				return;
			}
			else
			{
				audioID = vehicle_snds[eVehicleType];
				pAudioPtr = audioGetSndByAudioID( audioID  );
				if ( pAudioPtr == (AUDIO_IDS*)SND_NULL_SND_PTR )	
				{
					sndID = audioCreateSnd( AUDIOsfxID, audioID, 0, SND_SFX_FLAG | SND_LOOP_FLAG );
					audioStoreSnd( audioID, sndID, SND_SFX_FLAG );
					TRACE("Creating Vehicle sound first time: %d\n", sndID);
				}
				else
				{
					sndID = audioCreateSnd( AUDIOsfxID, audioID, 0, SND_SFX_FLAG | SND_LOOP_FLAG);
					TRACE("Creating Vehicle sound: %d\n", sndID);
				}

				pVehicle->looping_sndID = sndID;

				if ( sndID != SND_NULL_SND_ID )	{
					sndPlay(sndID);
					SndSetVolumePercent(sndID, volume, FALSE);
				}
			}

			break;
	}
#endif
}


void VehicleAccel(VEHICLE* pVehicle, int command)	{
	ANIM *pAnim = pVehicle->pAnimation;
	SHORT velocity_change;
	DWORD dwDeltaTime = gpGame->dwDeltaTime;
	DWORD coefficient;

	switch (command)	{
		case STOP_VEHICLE:
			velocity_change = (SHORT) ((gpGame->dwDeltaTime << 4) / pVehicle->brake_coefficient);

			if (pVehicle->full_velocity < 0)	{
				pVehicle->full_velocity += velocity_change;
				if (pVehicle->full_velocity > 0)
					pVehicle->full_velocity = 0;
			}
			else if (pVehicle->full_velocity > 0)	{
				pVehicle->full_velocity -= velocity_change;
				if (pVehicle->full_velocity < 0)
					pVehicle->full_velocity = 0;
			}
			break;

		case SPEEDUP_VEHICLE:
			coefficient = pVehicle->accel_coefficient;
			if (pAnim->velocity < 0)
				coefficient = pVehicle->brake_coefficient;

			velocity_change = (SHORT) ((dwDeltaTime << 4) / coefficient);
			pVehicle->full_velocity += velocity_change;
			pVehicle->full_velocity = min(pVehicle->full_velocity, pVehicle->max_velocity);

			break;
		case SLOWDOWN_VEHICLE:
			coefficient = pVehicle->brake_coefficient;

			if (pAnim->velocity < 0)
				coefficient = pVehicle->reverse_coefficient;

			velocity_change = (SHORT) ((dwDeltaTime << 4) / coefficient);
			pVehicle->full_velocity -= velocity_change;
			pVehicle->full_velocity = max(pVehicle->full_velocity, pVehicle->min_velocity);
		break;
	}
}


void VehicleExit(void)	{
//	VehicleSfxFree();
}


short	move_table[ARMY_LAST_VEHICLE][MOVEMENT_VALUES];

BOOL VehicleInit()	{
	int v;

	FOR_EACH_VEHICLE_TYPE(v)
    {
		int t;

		switch (v)	{
			case ARMY_TANK:
				for (t=0; t<MOVEMENT_VALUES; t++)	{
					move_table[v][t] = AIinfo.terrainTables[ t ].nTank;
				}
				break;
			case ARMY_CONVOY:
			case ARMY_HALFTRACK:
				for (t=0; t<MOVEMENT_VALUES; t++)	{
					move_table[v][t] = AIinfo.terrainTables[ t ].nHalfTrack;
				}
				break;
			case ARMY_JEEP:
				for (t=0; t<MOVEMENT_VALUES; t++)	{
					move_table[v][t] = AIinfo.terrainTables[ t ].nJeep;
				}
				break;
		}
	}

	return TRUE;
}

BOOL VehicleGraphicsLoaded = FALSE;

#define MAX_VANIM_FILES 2
#define MAX_TANIM_FILES 2
#define MAX_MANIM_FILES 2
CSpriteCatalog *VAnimFiles[ARMY_LAST_VEHICLE][MAX_VANIM_FILES];
CSpriteCatalog *TAnimFiles[ARMY_LAST_VEHICLE][MAX_TANIM_FILES];
CSpriteCatalog *MAnimFiles[MAX_MANIM_FILES];

char *vehicle_anim_names[MAX_VANIM_FILES] = {"Move.AXS", "Die.AXS"};
char *turret_anim_names[MAX_TANIM_FILES] = {"Turret.AXS", "DieTurret.AXS"};
char *missile_anim_names[MAX_MANIM_FILES] = {"Missile.AXS", "Shadow.AXS"};


//test function

void showvehiclemask(VEHICLE *pVehicle)
{
	ANIM *pAnim;
	SPOINT loc;
	int at;

	
	int whichvehicle=ITEM_CLASS(pVehicle);

	pAnim = pVehicle->pAnimation;
	SHORT facing = pAnim->facing;

    loc.x = pAnim->world_pos.x;
    loc.y = pAnim->world_pos.y;

    if (scriptDebug)
    {
        TRACE("Showing mask at %d, %d\n", loc.x, loc.y);
    }

    at = ENCODE_IPOINT(loc.x,loc.y);

    // clear all
#ifndef FINAL
 	int x;
	IPOINT index;
	WALKGRID(index)
	{
		if (DEBUG_LAYER(index) == 'V')
			SET_DEBUG_LAYER(index, 0);
	}
#endif

	SPOINT tilepos;
	SPOINT withintilepos;
	int y;
	int facingindex;
	int start, stop;

	tilepos.x=loc.x>>4;
	tilepos.y=loc.y>>4;
	withintilepos.x=(loc.x&15)>>2;
	withintilepos.y=(loc.y&15)>>2;

	//round facing to nearest multiple of 8
	facing=((facing+4)%256)&0xf8;


	facingindex=facing>>3;

	for (y=0;y<16;y++)
	{
		if ((stop=vehiclemasks[whichvehicle][facingindex][withintilepos.x][withintilepos.y][y])!=64)
		{
			start=stop>>4;
			stop&=15; //the high 4 bits of the byte are the starting pixel, tile, the low 4 are the stopping tile

#ifndef FINAL
			for (x=start;x<=stop;x++)
				SET_DEBUG_LAYER((INDEX(tilepos.x-8+x, tilepos.y-8+y)), 'F');
#endif
		}

	}
	

    DisplayDebugLayer(RGB_WHITE);
}						

int pointtoright(SPOINT l1, SPOINT l2, SPOINT p)
{
	SPOINT normal, to_p;

	to_p.x=p.x-l1.x;
	to_p.y=p.y-l1.y;

	normal.x=-(l2.y-l1.y);
	normal.y=(l2.x-l1.x);

	if ((to_p.x*normal.x+to_p.y*normal.y)>=0)
		return 1;
	return 0;
}

int pointinbox(SPOINT b1, SPOINT b2, SPOINT b3, SPOINT b4, SPOINT p)
{
	if (!pointtoright(b1, b2, p))
		return 0;
	if (!pointtoright(b2, b3, p))
		return 0;
	if (!pointtoright(b3, b4, p))
		return 0;
	if (!pointtoright(b4, b1, p))
		return 0;
	return 1;
}

static BOOL LegalAndVehicleTrafficable(int x, int y, int whichvehicle)
 //checks to see if a given tile is both on the map and trafficable

{
	if ((x>=0) && (y>=0) && (x<map_width) && (y<map_height) &&
        the_map.movement_layer[INDEX(x,y)] < 15 &&
        !getVehicleOnTile(x, y))
		return TRUE;
	return FALSE;
}

static BOOL LegalAndVehicleTrafficable_novehicleintersect(int x, int y, int whichvehicle)
//checks to see if a given tile is both on the map and trafficable
{
	if ((x>=0) && (y>=0) && (x<map_width) && (y<map_height) &&
        the_map.movement_layer[INDEX(x,y)] < 15)
		return TRUE;
	return FALSE;
}

void calculatevehiclemasks(void)
{
	int angle, xintile, yintile, x, y;
	int curvehicle;

	int start,stop;

	SPOINT b1, b2, b3, b4;
	SPOINT center, curpoint;

	unsigned char smalltempbuf[16][16];
	

	ZeroMemory(vehiclemasks, sizeof(vehiclemasks));


	for (curvehicle=ARMY_JEEP; curvehicle<=	ARMY_CONVOY; curvehicle++)
	{
		for (angle=0;angle<32;angle++)
		{
			for (xintile=0;xintile<4;xintile++)
				for (yintile=0;yintile<4;yintile++)
				{
					center.x=128+xintile*4+2;
					center.y=128+yintile*4+2;

					b1.x=(short)(center.x+(float)cos_table[angle*8]*vehiclesizes[curvehicle][0]+(float)cos_table[(angle*8+64)%256]*vehiclesizes[curvehicle][2]);
					b1.y=(short)(center.y+(float)sin_table[angle*8]*vehiclesizes[curvehicle][0]+(float)sin_table[(angle*8+64)%256]*vehiclesizes[curvehicle][2]);

					b2.x=(short)(center.x+(float)cos_table[angle*8]*vehiclesizes[curvehicle][0]+(float)cos_table[(angle*8+192)%256]*vehiclesizes[curvehicle][3]);
					b2.y=(short)(center.y+(float)sin_table[angle*8]*vehiclesizes[curvehicle][0]+(float)sin_table[(angle*8+192)%256]*vehiclesizes[curvehicle][3]);

					b3.x=(short)(center.x+(float)cos_table[angle*8]*(-vehiclesizes[curvehicle][1])+(float)cos_table[(angle*8+192)%256]*vehiclesizes[curvehicle][3]);
					b3.y=(short)(center.y+(float)sin_table[angle*8]*(-vehiclesizes[curvehicle][1])+(float)sin_table[(angle*8+192)%256]*vehiclesizes[curvehicle][3]);

					b4.x=(short)(center.x+(float)cos_table[angle*8]*(-vehiclesizes[curvehicle][1])+(float)cos_table[(angle*8+64)%256]*vehiclesizes[curvehicle][2]);
					b4.y=(short)(center.y+(float)sin_table[angle*8]*(-vehiclesizes[curvehicle][1])+(float)sin_table[(angle*8+64)%256]*vehiclesizes[curvehicle][2]);



					ZeroMemory(smalltempbuf, sizeof(smalltempbuf));

					for (x=0;x<16;x++)
						for (y=0;y<16;y++)
						{

							curpoint.x=x*16+8;
							curpoint.y=y*16+8;

							if (pointinbox(b1, b2, b3, b4, curpoint))
								smalltempbuf[y][x]=1;
						}

					for (y=0;y<16;y++)
					{
						start=-1;
						stop=-1;
						for (x=0;x<16;x++)
							if (smalltempbuf[y][x])
							{
								if (start==-1)
									start=x;
								stop=x;
							}
		
						if (start==-1)
							vehiclemasks[curvehicle][angle][xintile][yintile][y]=64;
						else
							vehiclemasks[curvehicle][angle][xintile][yintile][y]=(start<<4)+stop;
					}

					/*if (xintile==0 && yintile==0 && angle==0)
					{
						TRACE("Vehicle %d angle %d\n", curvehicle, angle);

						for (y=0;y<16;y++)
						{
							for (x=0;x<16;x++)
								TRACE("%d", smalltempbuf[y][x]);
							TRACE("\n");
						}
			

					}*/


				}
					

		}
	}	

}


//This function fills in a vehicle mask, given a position, facing and
//vehicle type
static void getVehicleMask(SPOINT pos, int facing,
                           int whichvehicle, VEHICLE_MASK *mask)
{
	SPOINT tilepos;
	SPOINT withintilepos;
	int x,y;
	int facingindex;
	int start, stop;

	tilepos.x=pos.x>>4;
	tilepos.y=pos.y>>4;
	withintilepos.x=(pos.x&15)>>2;
	withintilepos.y=(pos.y&15)>>2;

	//round facing to nearest multiple of 8
	facing=((facing+4)%256)&0xf8;

	facingindex=facing>>3;

	mask->upperLeft.x=tilepos.x-8;
	mask->upperLeft.y=tilepos.y-8;

	ZeroMemory(mask->data, sizeof(mask->data));

	for (y=0;y<16;y++)
		if ((stop=vehiclemasks[whichvehicle][facingindex][withintilepos.x][withintilepos.y][y])!=64)
		{
			start=stop>>4;
			stop&=15; //the high 4 bits of the byte are the starting pixel, tile, the low 4 are the stopping tile

			for (x=start;x<=stop;x++)
				mask->data[y]|=(1<<(15-x));
		}
}

//this function checks to see whether a particular vehicle mask is trafficable for a
//particular vehicle type
int isVehicleMaskTrafficable(int whichvehicle, VEHICLE_MASK *mask)
{
	int x,y;

	for (y=0;y<16;y++)
		for (x=0;x<16;x++)
			if (mask->data[y]&(1<<(15-x)))
				if (!LegalAndVehicleTrafficable(mask->upperLeft.x+x, mask->upperLeft.y+y, whichvehicle))
					return 0;
	return 1;
}

// unconditionally deduct from vehicle layer

void SubtractMaskFromVehicleLayer(VEHICLE_MASK *mask)
{
	int x,y, mapy, mapx; 
	for (y=0;y<16;y++)
	{
		mapy=mask->upperLeft.y+y;
		if (mapy>=0 && mapy<map_height)
			for (x=0;x<16;x++)
			{
				mapx=mask->upperLeft.x+x;
				if (mapx>=0 && mapx<map_width && mask->data[y]&(1<<(15-x)))
                    --pVehicleBlock[mapy*the_map.width + mapx];
			}
	}
}

void SubtractVehicleFromVehicleLayer(VEHICLE* pVehicle)
{
    SubtractMaskFromVehicleLayer(&pVehicle->mask);
}

// unconditionally add to movement layer
void AddVehicleToVehicleLayer(VEHICLE* pVehicle)
{
	int x,y, mapy, mapx;
    VEHICLE_MASK *mask = &pVehicle->mask;
	for (y=0;y<16;y++)
	{
		mapy=mask->upperLeft.y+y;
		if (mapy>=0 && mapy<map_height)
			for (x=0;x<16;x++)
			{
				mapx=mask->upperLeft.x+x;
				if (mapx>=0 && mapx<map_width && mask->data[y]&(1<<(15-x)))
                    ++pVehicleBlock[mapy*the_map.width + mapx];
			}
	}
}

// remove from layer if it is placed and return did
int ClearVehicleFromVehicleLayer(VEHICLE *pVehicle)
{
	if (pVehicle->framesNotMoving==FRAMES_BEFORE_ADD_TO_MOVEMENT_LAYER)
	{
	    SubtractVehicleFromVehicleLayer(pVehicle);
		pVehicle->framesNotMoving=0;
		return FRAMES_BEFORE_ADD_TO_MOVEMENT_LAYER;
	}
    else return 0;
}

// add back into layer if did is true
void ReinsertVehicleInVehicleLayer(VEHICLE *pVehicle,int did)
{
	if (!did) return; // not previously inserted
	AddVehicleToVehicleLayer(pVehicle);
	pVehicle->framesNotMoving= FRAMES_BEFORE_ADD_TO_MOVEMENT_LAYER;
}

void countVehicleMaskTrafficability(int whichvehicle, VEHICLE_MASK *mask, int *masksize, int *intersect)
{
	int x,y;
	*masksize=0;
	*intersect=0;

	for (y=0;y<16;y++)
		for (x=0;x<16;x++)
			if (mask->data[y]&(1<<(15-x)))
			{
				(*masksize)++;
				if (!LegalAndVehicleTrafficable(mask->upperLeft.x+x, mask->upperLeft.y+y, whichvehicle))
					(*intersect)++;
			}
}
void countVehicleMaskTrafficability_novehicleintersect(int whichvehicle, VEHICLE_MASK *mask, int *masksize, int *intersect)
{
	int x,y;
	*masksize=0;
	*intersect=0;

	for (y=0;y<16;y++)
		for (x=0;x<16;x++)
			if (mask->data[y]&(1<<(15-x)))
			{
				(*masksize)++;
				if (!LegalAndVehicleTrafficable_novehicleintersect(mask->upperLeft.x+x, mask->upperLeft.y+y, whichvehicle))
					(*intersect)++;
			}
}

void printVehicleMask(VEHICLE_MASK *v)
{
    if (scriptDebug)
    {
	int x,y;

	TRACE("(%d,%d)\n", v->upperLeft.x, v->upperLeft.y);

	for (y=0;y<16;y++)
	{
		for (x=0;x<16;x++)
			if (v->data[y]&(1<<(15-x)))
				TRACE("1");
			else
				TRACE("0");
		TRACE("\n");
	}
    }
}

//this function makes a new vehicle mask containing all the tiles that are in b but not in a
void calcVehicleMaskDifference(VEHICLE_MASK *a, VEHICLE_MASK *b, VEHICLE_MASK *c)
{

	int startx, endx, xoffset, starty, endy, yoffset;
	int x,y;


	memcpy(c, b, sizeof(VEHICLE_MASK));


	//no overlap. Thus, no pixels in common;
	if (abs(a->upperLeft.x-b->upperLeft.x)>15 || abs(a->upperLeft.x-b->upperLeft.x)>15)
		return;

	xoffset=b->upperLeft.x-a->upperLeft.x;
	yoffset=b->upperLeft.y-a->upperLeft.y;

	if (xoffset==0)
	{
		startx=0;
		endx=16;
	}
	else if (xoffset>0)
	{
		startx=0;
		endx=16-xoffset;
	}
	else
	{
		startx=-xoffset;
		endx=16;
	}

	if (yoffset==0)
	{
		starty=0;
		endy=16;
	}
	else if (yoffset>0)
	{
		starty=0;
		endy=16-yoffset;
	}
	else
	{
		starty=-yoffset;
		endy=16;
	}

	for (y=starty;y<endy;y++)
		for (x=startx;x<endx;x++)
			if (a->data[y+yoffset]&(1<<(15-(x+xoffset))))
				c->data[y]&=~(1<<(15-x));

}

// return recoil = # of tiles intersected, pMask is a pointer to the difference mask!
static int damageItemsInMask( VEHICLE *pVehicle, VEHICLE_MASK *pMask, int &nDeltaTiles )
{
	ITEM *pItemList;
	SPOINT pos;
	int x, y;
	int recoil = 0;
	int bItemInTile;
	int waterInTile;
	int damageamount = pVehicle->nCollisionDamage;
	int damagetype = DMGTYPE_RUNOVER;
	long uid = pVehicle->common.nUniqueID;
	float damagemult;
	int effectivevelocity;
	int tx, ty, tile;
	int vht, tht;
	
	waterInTile = 0;
	vht = GetElevationHeightAtItem( (ITEM *)pVehicle );
	nDeltaTiles = 0;
	if( ITEM_CLASS(pVehicle) == ARMY_TANK )
	{
		if( pVehicle->velocity >= 0 )
			effectivevelocity = __max( pVehicle->max_velocity >> 1, pVehicle->velocity );
		else
			effectivevelocity = __max( -pVehicle->min_velocity / 2, -pVehicle->velocity );
	}
	else
		effectivevelocity = abs(pVehicle->velocity);
	damagemult = (float)effectivevelocity / (float)pVehicle->max_velocity;

	for (y=0;y<16;y++)
	{
		for (x=0;x<16;x++)
		{
			tx = pMask->upperLeft.x + x;
			ty = pMask->upperLeft.y + y;
			if( tx < the_map.tileboundrect.left )
				continue;
			if( ty < the_map.tileboundrect.top )
				continue;
			if( tx > the_map.tileboundrect.right )
				continue;
			if( ty > the_map.tileboundrect.bottom )
				continue;

			bItemInTile = 0;
			if (pMask->data[y]&(1<<(15-x)))
			{
//				the_map.debug_layer[INDEX(pMask->upperLeft.x+x, pMask->upperLeft.y+y)]='F';
				tile = INDEX( tx, ty );
				nDeltaTiles++;
				pos.x=((pMask->upperLeft.x+x)<<4)+8;
				pos.y=((pMask->upperLeft.y+y)<<4)+8;
				pItemList=GetObjectsIntersectPoint(&pos);
				while (pItemList)
				{
					switch(ITEM_TYPE(pItemList))
					{
						case ARMY_SARGE:
						case ARMY_TROOPER:
							tht = GetElevationHeightAtItem( pItemList );
							if( abs(vht-tht) > 4 )
								break;
							ItemDamage(pItemList, (int)((float)damageamount*damagemult), damagetype, &pos, uid);
							break;
						case ARMY_VEHICLE:
							if (pItemList->nUniqueID==uid) break;
                            VEHICLE *pHitVehicle;
                            int dmg;

                            pHitVehicle = (VEHICLE *)pItemList;

                            bItemInTile += 3;
                            if( pHitVehicle->nArmor - pVehicle->nArmor > 10 )
                            {
								if( damagemult > 0.5 )
									ItemDamage( (ITEM *)pVehicle, 1, damagetype, &pos, pItemList->nUniqueID );
                            }
                            else
                            {
                                dmg = (int)(__max( 0, damageamount - pHitVehicle->nArmor ) * damagemult);
                                ItemDamage(pItemList, dmg, damagetype, &pos, uid);
                                bItemInTile += 2;
                            }
							break;
						case ARMY_ASSET:
						case ARMY_STRUCTURE:
						case ARMY_OBSTACLE:
							if( ((OBJECT *)pItemList)->movement > 0 && !pVehicle->npc)
								bItemInTile++;
							switch(ITEM_CLASS(pItemList))
							{
								case 1: //bush
								case 5: //fence
								case 9: //explosive
									ItemDamage(pItemList, (int)((float)damageamount*damagemult), damagetype, &pos, uid);
									break;
							}
							break;
						case ARMY_HUSK:
							bItemInTile++;
							ItemDamage( pItemList, (int)((float)damageamount*damagemult), damagetype, &pos, uid);
							break;
					}
                    pItemList=pItemList->next;
				}
                // if there was nothing in the objects
                // see if the tile is and was untrafficable as a boundary
				if( !bItemInTile  && the_map.movement_layer[tile] >= 15  &&
                    the_map.triggers[tile] & TILE_UNTRAFFICABLE && !pVehicle->npc)
                    bItemInTile  = 1;

				if( the_map.triggers[tile] & TRIGGER_WATER && !pVehicle->npc)
					waterInTile++;
				recoil += bItemInTile;
			}
		}
	}
	if( waterInTile )				// for now just deduct 1 from recoil for water tils
		waterInTile = 1;			// to make bridges easier to traverse.
	return recoil - waterInTile;
}


int isTileInMask(int x, int y, VEHICLE_MASK *mask)
{
	if (x<mask->upperLeft.x)
		return 0;
	if (x>mask->upperLeft.x+15)
		return 0;
	if (y<mask->upperLeft.y)
		return 0;
	if (y>mask->upperLeft.y+15)
		return 0;

	if (mask->data[y-mask->upperLeft.y]&(1<<(15-(x-mask->upperLeft.x))))
		return 1;

	return 0;
}

VEHICLE *getVehicleOnTile(int x, int y) //x,y are tile coordinates
{
	int eArmy;
	int vehicle;
    LEGION* pLegion;
    VEHICLE* pVehicle;


	for (eArmy=ARMY_PLAYER;eArmy<ARMY_LAST_ARMY;++eArmy)
	{

		pLegion = ArmyGetLegion(eArmy);
		
		FOR_EACH_VEHICLE(pLegion,vehicle)
		{
			pVehicle = pLegion->pLegionVehicles[vehicle];
            // ignore dying vehicles. OTHERWISE vehicles travel
            // real slowly thru where a vehicle died, though the
            // anim image of the dead vehicle is elsewhere.
            if (pVehicle->state != VEHICLE_DEPLOYED)  continue;

			if (pVehicle->common.tile)
				if (isTileInMask(x,y,&pVehicle->mask))
					return pVehicle;
		}
	}

	return NULL;
}


BOOL VehicleLoad()	{
	char	pathname[32];
	char	filename[64];
	CSpriteCatalog *pCat;
	int		eType;
	int		loadcount;
	int		eArmy;
	int		total;

	if (VehicleGraphicsLoaded)
		return TRUE;

	sprintf(pathname, "%s/Vehicles/", the_map.terrain_name);
	SetPath(pathname);
	loadcount = 0;


	int i;
    FOR_EACH_VEHICLE_TYPE(eType)
	{
		total = 0;
		FOR_EACH_ARMY(eArmy)
			total += Armies[eArmy].Reserves.nVehiclesAvail[eType];

		if (!total)
			continue;	// don't load data if no vehilces of that type

		for (i=0; i<MAX_VANIM_FILES; i++)	{
			ClearTotals();
			sprintf(filename, "%s/%s", VehicleName(eType), vehicle_anim_names[i]);
			pCat = AnimImport(filename, BM_NOTRANSLATE | BM_USEBMPASMASK);
			if (pCat)	{
				ProcessAnim(pCat, VehicleCommands[eType]);
				VAnimFiles[eType][i] = pCat;
			}
			MissionLoading( 12000 + loadcount * 95, 20000 );
			loadcount++;
		}
		CheckAnim(VehicleCommands[eType], VehicleName(eType), NULL);

		for (i=0; i<MAX_TANIM_FILES; i++)	{
			ClearTotals();
			sprintf(filename, "%s/%s", VehicleName(eType), turret_anim_names[i]);
			pCat = AnimImport(filename, BM_NOTRANSLATE | BM_USEBMPASMASK);
			if (pCat)	{
				ProcessAnim(pCat, TurretCommands[eType]);
				TAnimFiles[eType][i] = pCat;
			}
			MissionLoading( 12000 + loadcount * 95, 20000 );
			loadcount++;
		}
		CheckAnim(TurretCommands[eType], VehicleName(eType), NULL);
	}

	for (i=0; i<MAX_MANIM_FILES; i++)	
	{
		long flags;

		flags = BM_NOTRANSLATE;
		if( strncmp( strupr(missile_anim_names[i]), "SHAD", 4 ) == 0 )
			flags = 0;
		pCat = AnimImport(missile_anim_names[i], flags);
		if (pCat)	{
			ProcessAnim(pCat, &missile_commands);
			MAnimFiles[i] = pCat;
		}
		MissionLoading( 12000 + loadcount * 95, 20000 );
		loadcount++;
	}
	CheckAnim(&missile_commands, "Missiles", NULL);

	VehicleGraphicsLoaded = TRUE;


	calculatevehiclemasks();

	return( VehicleGraphicsLoaded );
}


void VehicleFree()	{
	int eType;

	if (!VehicleGraphicsLoaded)
		return;

	int i;
    FOR_EACH_VEHICLE_TYPE(eType)
	{
		for (i=0; i<MAX_VANIM_FILES; i++)	{
			FreeAnimImport(VAnimFiles[eType][i]);
			VAnimFiles[eType][i] = NULL;
		}
		for (i=0; i<MAX_TANIM_FILES; i++)	{
			FreeAnimImport(TAnimFiles[eType][i]);
			TAnimFiles[eType][i] = NULL;
		}
	}

	for (i=0; i<MAX_MANIM_FILES; i++)	{
		FreeAnimImport(MAnimFiles[i]);
		MAnimFiles[i] = NULL;
	}

	VehicleGraphicsLoaded = FALSE;
}

void VehicleFiringPosition(VEHICLE *pVehicle, SPOINT *pt)
{
	ANIM	*pAnim = pVehicle->pAnimation;

	if (pVehicle->bTurret)
		pAnim = &pVehicle->pAnimation[TURRETANIM];
	else
		pAnim = pVehicle->pAnimation;

	pt->x = pAnim->world_pos.x + pAnim->pFrame[pAnim->current_frame].secondary_hotspot.x;
	pt->y = pAnim->world_pos.y + pAnim->pFrame[pAnim->current_frame].secondary_hotspot.y;
}


#define MIN_VELOCITY -1000
#define MAX_VELOCITY 1000

void VehicleFireWeapon(VEHICLE *pVehicle)	{
	WEAPON *pWeapon = pVehicle->common.pWeapon;
	SPOINT	pt;
	if (!pWeapon) return; // unarmed
	if (pWeapon->eWeapon == ARMY_NO_WEAPON) return; // unarmed

    // We dont monitor remote vehicles legality!

    // check legality of our ammo for a local vehicle
    // and prove we have reloaded and are ready to fire again
    if (IS_LOCAL_ITEM(pVehicle))
    {
        if (!WeaponFireTime(pWeapon))
            return;

		if( pWeapon->nAmmo == 0 )
			return;

		if (pWeapon->nAmmo > 0)
			pWeapon->nAmmo--;

        WeaponFireReset(pWeapon);			

        // tell remote people we fired
		VehicleFireMessageSend(pVehicle);
	}

//	 showvehiclemask(pVehicle);

    ItemMakeVisible(pVehicle);

	VehicleFiringPosition(pVehicle, &pt);

	VehicleSetFire(pVehicle,pt);		// sets direction and distance

	FireWeapon((ARMY_TYPE)ITEM_ARMY(pVehicle), pWeapon, 
					&pt,
					GetElevationHeightAtItem((ITEM *)pVehicle) + 8,
					pVehicle->common.fireDirection,
					pVehicle->common.fireDistance, 
					GetElevationHeightAtItem((ITEM *)pVehicle),	// pVehicle->fireHeight supposedly, 
                    ITEM_UID(pVehicle) );
}


static void VehicleSetFire(VEHICLE *pVehicle,SPOINT from)
{
	SET_WEAPON set_weapon;

	set_weapon = SetFireWeapon(pVehicle->common.pWeapon, &from, 
		pVehicle->gun_facing, 
		NULL //pVehicle->pTarget
		);

	pVehicle->common.fireDirection = set_weapon.direction;
	pVehicle->common.fireDistance = set_weapon.distance;
}


///========================================================================
//	Function:		VehicleCreate()
//
//	Description:
//		Create a Vehicle.
//
//	Input:			pNewVehicle		the new vehicle data
//					pPosition		where to place the vehicle in the world 
//
//	Ouput:			none
//
///========================================================================

RETERROR	VehicleCreate(ARMY_TYPE eArmy, VEHICLE_TYPE eVehicleType )
{
	RETERROR		error = TRUE;		// assume failure
    VEHICLE* pVehicle;
	LEGION* pLegion = ArmyGetLegion(eArmy);
    
    // cannot create more
    if (pLegion->nNumberOfVehicles == ARMY_MAX_VEHICLES)
    {
        TRACE("Vehicle Creation Refused- %d exist\n",ARMY_MAX_VEHICLES);
        return TRUE;
    }

	// allocate the vehicle & clear it
	pVehicle = (VEHICLE*)malloc( sizeof(VEHICLE) );
	if (pVehicle == NULL )
	{
		// error
		TRACE( "ERROR: failed to allocate VEHICLE list. [%s,%d]\n",
			__FILE__, __LINE__ );
		goto exit;
	}
	ZeroMemory( (void*)(pVehicle), sizeof(VEHICLE) );
    pVehicle->state = VEHICLE_UNDEPLOYED;
	pVehicle->looping_sndID = SND_NULL_SND_ID;
	ItemSetUID(pVehicle,eArmy,ARMY_VEHICLE, eVehicleType, pLegion->nNumberOfVehicles );
	VehicleSet( pVehicle);

	// add to vehicle list in legion
    pLegion->pLegionVehicles[pLegion->nNumberOfVehicles] = pVehicle;
	++pLegion->nNumberOfVehicles;

    
	// create the vehicle animation structures (2): vehicle & turret
	pVehicle->pAnimation = (ANIM*)malloc( sizeof(ANIM)*2 );
	if ( pVehicle->pAnimation == NULL )
	{
		TRACE( "ERROR: failed to allocate vehicle ANIM structure. [%s,%d]\n",
			__FILE__, __LINE__ );
		goto exit;
	}

	// clear the animation structure and set some internal pointers
	AnimInit( 255, 255, pVehicle->pAnimation, OL_ORDEREDLAYER );				// vehicle body
	pVehicle->pAnimation->order = 5000;

	AnimInit( 255, 255, &pVehicle->pAnimation[TURRETANIM], OL_ORDEREDLAYER );	// vehicle turret
	pVehicle->pAnimation[TURRETANIM].order = 5000;

	if (eVehicleType != ARMY_CONVOY)	{
		AnimLink( pVehicle->pAnimation, &pVehicle->pAnimation[TURRETANIM]);
		pVehicle->bTurret = TRUE;
	}


	AnimTransTable(pVehicle->pAnimation, UnitColorTable(eArmy));
	AnimTransTable(&pVehicle->pAnimation[TURRETANIM], UnitColorTable(eArmy));

	AnimSetOwner(pVehicle->pAnimation, pVehicle);		// required for anim callback and for collision detection

	// if we made it here we're in business
	error = FALSE;

exit:
	return( error );
}


///========================================================================
//	Function:		VehicleDelete()
//
//	Description:
//		Create a Vehicle. A Vehicle is created once it is placed actively into
//		the world (via the main base).
//
//	Input:			pVehicle		the old vehicle data
//
//	Ouput:			none
//
///========================================================================

void	VehicleDelete( VEHICLE* pVehicle )
{
    ClearVehicleFromVehicleLayer(pVehicle);
   
	ItemFreeLabel((ITEM *)pVehicle);

    // release any ai controller
    if (pVehicle->controller)
    {
        free(pVehicle->controller);
        pVehicle->controller = NULL;
    }

    // release any tad 
    if (pVehicle->common.pTad)
    {
        UnitValidateTad(); // just test the hell out of the links
        TadDeleteObject( (TAD*)pVehicle->common.pTad );
        pVehicle->common.pTad = NULL;
        UnitValidateTad(); // just test the hell out of the links
    }

    // release any animation data
	if ( pVehicle->pAnimation )
	{
		if( &(pVehicle->pAnimation[TURRETANIM]) )
			AnimDelete( &(pVehicle->pAnimation[TURRETANIM]) );
		if( &(pVehicle->pAnimation[BODYANIM]) )
			AnimDelete( &(pVehicle->pAnimation[BODYANIM]) );
		free( pVehicle->pAnimation );
		pVehicle->pAnimation = NULL;

#ifdef MALLOC_DEBUG
		TRACE( "free: vehicle animation (army %d)[%s : %d]\n", eArmy, __FILE__, __LINE__ );
#endif
	}

    // now release the vehicle itself
    free(pVehicle);
}


///========================================================================
//	Function:		VehicleUndeploy()
//
//	Description:
//		Bring a vehicle back into base
///========================================================================

void	VehicleUndeploy(VEHICLE* pVehicle)	{

   SARGE* pSarge;
   ANIM	*pAnim = pVehicle->pAnimation;
   pVehicle->state = VEHICLE_UNDEPLOYED;
   pVehicle->common.nStrength = 0;
   ClearVehicleFromVehicleLayer(pVehicle);
 
    // if sarge was inside, he better bail out now
    pSarge = SargePointer(ITEM_ARMY(pVehicle));
    if (pSarge->pVehicle == pVehicle)  SargeOutVehicle(pSarge);

    pVehicle->full_velocity = 0;
    pAnim->velocity = 0;

    // remove tad
    if (pVehicle->common.pTad)
    {
        UnitValidateTad(); // just test the hell out of the links
        TadDeleteObject( (TAD*)(pVehicle->common.pTad) );	
        pVehicle->common.pTad = NULL;
        UnitValidateTad(); // just test the hell out of the links
    }

	AnimInactivate( pVehicle->pAnimation, INACTIVATE_LINKS );

	ItemSpecialUpdatePosition((ITEM*)pVehicle, &OFF_THE_MAP);

    
    // reset vehicle stats
	VehicleSet( pVehicle);
}


///========================================================================
//	Function:		VehicleDeployType()
//	Description:	Do deployment of selected vehicle dynamically
///========================================================================
void VehicleDeployType( ARMY_TYPE eArmy, VEHICLE_TYPE eVehicleType, SPOINT *pPos, short facing )
{
	VEHICLE* pVehicle = VehicleNextInHQ(eArmy,(VEHICLE_TYPE) eVehicleType);
    if (pVehicle)  VehicleDeploy(pVehicle, pPos, facing);
}


///========================================================================
//	Function:		VehicleInitialDeploy()
//	Description:	Do actual deployment of selected vehicle
///========================================================================
long ComboSafe(IPOINT tile)
{
	if (!UnitSafeDeploy(tile)) return 0;
	if (!VehicleSafeDeploy(tile)) return 0;
	return tile;
}

void VehicleInitialDeploy(VEHICLE* pVehicle, SPOINT *pPos, short facing)
{
	VEHICLE_TYPE eVehicleType = (VEHICLE_TYPE) ITEM_CLASS(pVehicle);
    if (ITEM_ARMY(pVehicle) != ARMY_PLAYER && gpGame->GameType == GAMETYPE_ONEPLAYER)
        pVehicle->npc = 1;
        
	VehicleSet( pVehicle );

	// TBD: change this to check vehicle safe intead of unit safe
    IPOINT tile = ENCODE_IPOINT(pPos->x,pPos->y);
    if (!UnitSafeDeploy(tile) || ! VehicleSafeDeploy(tile))
    {
      ErrorDebug("!*!*! %s deployed illegally at %d.%d\n",ItemDBName(pVehicle),
          pPos->x,pPos->y);
      tile = ItemFanOut((ITEM*)pVehicle,tile,100, ComboSafe);
      pPos->x = IPOINT_X(tile) << 4;
      pPos->y = IPOINT_Y(tile) << 4;
      if (scriptDebug)
      {
          TRACE("!*!*! %s relocatd to %d.%d\n",ItemDBName(pVehicle),pPos->x,pPos->y);
      }
        if (!pPos->x) return;
	}   
    else TRACE("    %s deploying at %d.%d \n", ItemDBName(pVehicle),pPos->x,pPos->y);

    // Update position, force pad trigger and then stabilize
    ItemSpecialUpdatePosition((ITEM*)pVehicle, pPos);

	pVehicle->common.facing = facing;

    pVehicle->state = VEHICLE_DEPLOYED;

    pVehicle->spin = 0;
    pVehicle->focusItem = NULL;

	AnimSet( pVehicle->pAnimation, pVehicle->common.position.x, pVehicle->common.position.y, VehicleCommands[eVehicleType], VSTOP_COMMAND, pVehicle->common.facing, ABSOLUTE_VELOCITY);
	AnimSetSize( pVehicle->pAnimation );
	AnimActivate( pVehicle->pAnimation, NO_ACTIVATE_LINKS );

	if (pVehicle->bTurret)	{
		pVehicle->gun_facing = pVehicle->common.facing;
		AnimSet( &pVehicle->pAnimation[TURRETANIM], pVehicle->common.position.x, pVehicle->common.position.y, TurretCommands[eVehicleType], VSTOP_COMMAND, pVehicle->common.facing, ABSOLUTE_VELOCITY);
		AnimActivate( &pVehicle->pAnimation[TURRETANIM], NO_ACTIVATE_LINKS );
	}

	pVehicle->full_velocity = 0;
	AnimForceVelocity(pVehicle->pAnimation, ABSOLUTE_VELOCITY, 0);
	
	AnimMove( pVehicle->pAnimation, FALSE );
	if (pVehicle->common.position.x != pVehicle->pAnimation->world_pos.x ||
		pVehicle->common.position.y != pVehicle->pAnimation->world_pos.y)
      ErrorDebug(" %s bounced on deployment (too close to edge?) \n",ItemDBName(pVehicle));

	// set ammo to max on deploy (which means on resurrect, as well)
	int ammo = AIinfo.vehicleTables[ eVehicleType ].ammo.nAmmo1;
	SetItemCurrentAmmo((ITEM *)pVehicle, ammo);

    // get vehicle into tad world
	if ( TadCreateObject((int) ITEM_ARMY(pVehicle),(int) ARMY_VEHICLE, (ITEM*)pVehicle, (ULONG)0 ) )
		TRACE("ERROR: failed to create TAD object for vehicle. [%s:%d]\n", __FILE__, __LINE__ );	// report an error

	getVehicleMask(pVehicle->common.position, pVehicle->common.facing, ITEM_CLASS(pVehicle), &pVehicle->mask);
	pVehicle->arrivalEvent = EVENT_NUM_UNDEFINED;
}

void	VehicleDeployPosition( VEHICLE* pVehicle, SPOINT *pPos, short facing)
{
	pVehicle->deployPosition = *pPos;
	pVehicle->deployFacing = facing;
}

///========================================================================
//	Function:		VehicleDeploy()
//	Description:	Do actual deployment of selected vehicle
///========================================================================


void VehicleDeploy(VEHICLE* pVehicle, SPOINT *pPos, short facing)
{
    VehicleInitialDeploy(pVehicle,pPos,facing);
    VehicleDeployMessageSend(pVehicle);
}

    
///========================================================================
//	Function:		VehicleNextInHQ
//	Description:	Find next referencable vehicle undeployed
///========================================================================
    
VEHICLE* 	VehicleNextInHQ(ARMY_TYPE eArmy,VEHICLE_TYPE eVehicleType)
{
    LEGION* pLegion = ArmyGetLegion(eArmy);
    VEHICLE* pVehicle;
	int i,n;
    for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
    {
        pVehicle = pLegion->pLegionVehicles[i];
        // already deployed
        if (pVehicle->state != VEHICLE_UNDEPLOYED) continue;
        // wrong type of vehicle?
        n = ITEM_CLASS(pVehicle);
        if (n != eVehicleType) continue;

        // if found an undeployed one of this vehicle type
        if (pVehicle->deployPosition.x == 0)
		{
			pVehicle->deployPosition.x = 1;
			return pVehicle;
		}
    }
    return NULL;
}


///========================================================================
//	Function:		VehicleSet()
//	Description:	Set vehicle stats
///========================================================================

static void VehicleSet( VEHICLE *pVehicle)
{
    VEHICLE_TYPE eVehicleType = (VEHICLE_TYPE) ITEM_CLASS(pVehicle);

	pVehicle->common.nStrength = pVehicle->common.nMaxStrength = AIinfo.vehicleTables[ eVehicleType ].nHitPoints;

	pVehicle->max_velocity = AIinfo.vehicleTables[ eVehicleType ].speed.nSpeed1;
	pVehicle->min_velocity = AIinfo.vehicleTables[ eVehicleType ].speed.nSpeed2;

	pVehicle->accel_coefficient = AIinfo.vehicleTables[ eVehicleType ].accel.nForward;
	pVehicle->reverse_coefficient = AIinfo.vehicleTables[ eVehicleType ].accel.nReverse;
	pVehicle->brake_coefficient = AIinfo.vehicleTables[ eVehicleType ].accel.nDeccel;


	pVehicle->common.pWeapon = &(pVehicle->weapon);

	int eWeapon = AIinfo.vehicleTables[ eVehicleType ].weapons.eWeapon1;
	int ammo = AIinfo.vehicleTables[ eVehicleType ].ammo.nAmmo1;
	if( eWeapon )
	{
		MakeWeapon(pVehicle->common.pWeapon, (WEAPON_TYPE) eWeapon, ammo);
		SetWeaponOwner(pVehicle->common.pWeapon, (ITEM *)pVehicle);
	}
	
	pVehicle->nCollisionDamage = AIinfo.vehicleTables[ eVehicleType ].nCollisionDamage;
	pVehicle->nArmor = AIinfo.vehicleTables[ eVehicleType ].nArmor;

	pVehicle->move_table = &move_table[eVehicleType][0];
	pVehicle->pDriver = NULL;
}

static void GetNextPos(ANIM* pAnim, int velocity, SPOINT *ppos_front, SPOINT *ppos_away)	{
	SHORT direction = pAnim->facing;
	int move = velocity / 25;
	int offset;

	if (velocity < 0)	{
		velocity = -velocity;
		direction = NormalizeFacingAdd(direction, CIRCLE_UNITS/2);
		offset = pAnim->move_off.back;
	}
	else
		offset = pAnim->move_off.front;

	move += offset;

	if (ppos_away)	{
		ppos_away->x = (short)(pAnim->world_pos.x + cos_table[direction]*move);
		ppos_away->y = (short)(pAnim->world_pos.y + sin_table[direction]*move);
	}

	if (ppos_front)	{
		ppos_front->x = (short)(pAnim->world_pos.x + cos_table[direction]*offset);
		ppos_front->y = (short)(pAnim->world_pos.y + sin_table[direction]*offset);
	}
}

///========================================================================
//	Function:		LegalVehiclePos
//
//	Description:
//		Given a vehicle, a location and a facing, returns whether the 
//		vehicle can legally be there or whether it would be obstructed
//
///========================================================================
int LegalVehicleDeployPos(SPOINT *pos, int facing, int whichvehicle)
{
	SPOINT tilepos;
	SPOINT withintilepos;
	int x,y;
	int facingindex;
	int start, stop;
	int army, owner;

	tilepos.x=pos->x>>4;
	tilepos.y=pos->y>>4;
	withintilepos.x=(pos->x&15)>>2;
	withintilepos.y=(pos->y&15)>>2;

	//round facing to nearest multiple of 8
	facing=((facing+4)%256)&0xf8;

	facingindex=facing>>3;

	army = gpComm->GetArmyIndex(ARMY_PLAYER);

	for (y=0;y<16;y++)
		if ((stop=vehiclemasks[whichvehicle][facingindex][withintilepos.x][withintilepos.y][y])!=64)
		{
			start=stop>>4;
			stop&=15; //the high 4 bits of the byte are the starting pixel, tile, the low 4 are the stopping tile

			for (x=start;x<=stop;x++)
			{
				if (!LegalAndVehicleTrafficable(tilepos.x-8+x, tilepos.y-8+y, whichvehicle))
					return 0;
				owner = OWNER(the_map.owner_layer[IndexOf(tilepos.x-8+x, tilepos.y-8+x)]);
				if( (owner != army) && (owner != gGlobalPlacement) )
					return 0;
			}
		}
	
	return 1;
}						


///========================================================================
//	Function:		TroopersOnVehiclePos
//
//	Description:
//		Given a vehicle, a location and a facing, returns whether there
//		are any troopers who would be intersecting with that vehicle
//
///========================================================================
int TroopersOnVehiclePos(SPOINT *pos, int facing, int whichvehicle)
{
	SPOINT tilepos;
	SPOINT withintilepos;
	int x,y;
	int facingindex;
	int start, stop;

	tilepos.x=pos->x>>4;
	tilepos.y=pos->y>>4;
	withintilepos.x=(pos->x&15)>>2;
	withintilepos.y=(pos->y&15)>>2;

	//round facing to nearest multiple of 8
	facing=((facing+4)%256)&0xf8;

	facingindex=facing>>3;

	for (y=0;y<16;y++)
		if ((stop=vehiclemasks[whichvehicle][facingindex][withintilepos.x][withintilepos.y][y])!=64)
		{
			start=stop>>4;
			stop&=15; //the high 4 bits of the byte are the starting pixel, tile, the low 4 are the stopping tile

			for (x=start;x<=stop;x++)
			{
				if (GetTrooperOnTile(tilepos.x-8+x, tilepos.y-8+y))
					return 1;
				if( GetSargeOnTile( tilepos.x-8+x, tilepos.y-8+y ) )
					return 1;
			}
		}
	
	return 0;
}	


///========================================================================
//	Function:		VehicleUpdate()
//	Description:	Update the actions of any Army Vehicle
///========================================================================
void	VehicleUpdate( VEHICLE* pVehicle )
{
	ANIM *pAnim;
	int velocity;
	int abs_velocity;
	SHORT spin = pVehicle->spin;
	SPOINT remote_pos;
	int moved=0;
	int driverless_decel_factor = 2;         
	int direction;
  	VEHICLE_MASK newmask, diffmask;
    SPOINT newloc, tempnewloc;
	int newFacing;
	int testvelocity;
	int nNewBadTiles;
	int dummy;

	if ( !pVehicle )
		return;	

    if (!VEHICLE_ON_MAP(pVehicle))
        return;

	pAnim = pVehicle->pAnimation;
	newFacing = NormalizeFacing(pAnim->facing+spin);

	// this is  updating of vehicle not on local machine (is_remote)
	if (pVehicle->new_position.x) 
	{										// if pending update
		pVehicle->gun_facing = pVehicle->new_gun_facing;
		AnimForceFacing(&pAnim[TURRETANIM], pVehicle->new_gun_facing);
		velocity = pVehicle->new_velocity;
		pVehicle->velocity = velocity;
		abs_velocity = abs(velocity);
		IPOINT newtile;
		newtile = ENCODE_IPOINT(pVehicle->new_position.x,pVehicle->new_position.y);

        // if on tile, proceed normally to position
        if (TileDistance(pVehicle->common.tile,newtile) < 2)
        {
            remote_pos = pVehicle->new_position;
            pVehicle->new_position.x = 0;
       }
		else if (TileDistance(pVehicle->common.tile,newtile) < 4)
		{
			remote_pos = pVehicle->common.position;
            pVehicle->lastInterpolated	= gpGame->dwAnimTime + 30;
            direction = GetDirection(&pVehicle->common.position,
                                     &pVehicle->new_position);
            ASSERT(direction >= 0);
            remote_pos.x = (short)(pVehicle->common.position.x + cos_table[direction]*4);
            remote_pos.y = (short)(pVehicle->common.position.y + sin_table[direction]*4);
		}
        // else try to smooth move to desired position 
		// going 24 pixels per frame
        else if (gpGame->dwAnimTime > (DWORD)pVehicle->lastInterpolated)
        {
            pVehicle->lastInterpolated	= gpGame->dwAnimTime + 30;
            direction = GetDirection(&pVehicle->common.position,
                                     &pVehicle->new_position);
            ASSERT(direction >= 0);
            remote_pos.x = (short)(pVehicle->common.position.x + cos_table[direction]*24);
            remote_pos.y = (short)(pVehicle->common.position.y + sin_table[direction]*24);
        }
		else // do not interpoplate now
		{
            remote_pos = pVehicle->common.position;
		}
  		
		AnimForceFacing(pAnim, pVehicle->new_facing);

		moved = 1;
	}
	
	else if (!IS_LOCAL_ITEM(pVehicle))// remote vehicle has no more mov
	{
		velocity = pVehicle->velocity; 
		abs_velocity = abs(velocity);
		remote_pos = OFF_THE_MAP; 
		if( velocity >= 0 )							// compute from max possible velocity
			testvelocity = pVehicle->max_velocity;
		else 
			testvelocity = pVehicle->min_velocity;

		newloc = AnimFigureWouldMoveTo(pAnim, pVehicle->new_facing, testvelocity);
		if( !InRect( &(the_map.sargeboundrect), &newloc ) )
			pVehicle->full_velocity = velocity = 0;

	}

	else 	// ordinary local vehicle
	{
        pVehicle->old_velocity = pVehicle->velocity;

		// auto decelerate a driverless vehicle
		if( (!pVehicle->pDriver) && (!pVehicle->npc) )
		{
			velocity = pVehicle->velocity;

			if( velocity > 0 )
				velocity -= driverless_decel_factor;
			else
			if( velocity < 0 )
				velocity += driverless_decel_factor;

			pVehicle->velocity = velocity;
		}
		else					// vehicle has a driver
		{
			velocity = pVehicle->full_velocity;
		
			if (velocity)	
			{
				if (pVehicle->npc)
					abs_velocity = max( 10, min( 800, abs(velocity) ) );
				else 
					abs_velocity = max( 30, min( 800, abs(velocity) ) );

				if (velocity < 0)
				{
					velocity = -abs_velocity;
					spin=-spin;
				}
				else
					velocity = abs_velocity;
			}
			else	
				abs_velocity = 0;

			//jeeps and trucks only turn when moving (if driven by sarge)
            if (pVehicle->pDriver)
                switch(ITEM_CLASS(pVehicle))
                {
				case ARMY_JEEP:
				case ARMY_CONVOY:
					spin=spin*abs_velocity*(2)/pVehicle->max_velocity;  //correction factor
					if (spin<-GROSS_MOTOR) 	spin=-GROSS_MOTOR;
					if (spin>GROSS_MOTOR) 	spin=GROSS_MOTOR;
					break;
                }
		}
		
	
		if( velocity >= 0 )							// compute from max possible velocity
			testvelocity = pVehicle->max_velocity;
		else 
			testvelocity = pVehicle->min_velocity;

        // users may not drive their vehicles off the visible map space
        if (pVehicle->pDriver)
        {
			newloc = AnimFigureWouldMoveTo(pAnim, newFacing, testvelocity );
			if( !InRect( &(the_map.sargeboundrect), &newloc ) )
				pVehicle->full_velocity = velocity = 0;
        }

        // a moving local vehicle damages things it hits
        int recoil = 0;
		int nDeltaTiles = 0;

        if (velocity || spin)
        {
            newloc=AnimFigureWouldMoveTo(pAnim, newFacing, velocity);

			tempnewloc=AnimFigureWouldMoveTo(pAnim, newFacing, testvelocity);

            getVehicleMask(newloc, newFacing, ITEM_CLASS(pVehicle), &newmask);

            calcVehicleMaskDifference(&pVehicle->mask, &newmask, &diffmask);
            recoil = damageItemsInMask(pVehicle, &diffmask, nDeltaTiles);
        }
        
        // now see if vehicle can actually move where it wants to go

        // unmoving vehicle has no problem
        if (!spin && !velocity);
         
		// moving NPC vehicles do not hit most terrain, 
        else if (pVehicle->npc)
		{
			IPOINT tile;
            BOOL blocked;
            blocked = FALSE;
			if( recoil > 0 )
				blocked = TRUE;
			else
			if( !AnimInWorld( (ANIMCELL *)pAnim, newloc.x, newloc.y ) )
                blocked = TRUE;
			else
			{
				tile = ENCODE_IPOINT(newloc.x,newloc.y);

                // dont go onto untrafficalbe spot
                if (the_map.movement_layer[tile] >= 15) blocked = TRUE;
            }

            // if blocked, dont allow him to go here
            if (blocked)
            {
                pVehicle->full_velocity = velocity = 0;
                spin = 0;                    
            }
		}

        // moving not a npc (including abandoned) vehiclea has various allowable movement rules
		else
		{
			int absvelocity;
			int absmaxvelocity;

            // bounced off object?
			/*
			if( recoil > 1 )
			{
				int newvelocity;
				newvelocity = velocity * -0.5;
				pVehicle->full_velocity = velocity = newvelocity;
			}
			*/

			//if we've added the vehicle to the movement layer, subtract it to avoid confusion

			countVehicleMaskTrafficability_novehicleintersect(ITEM_CLASS(pVehicle), &newmask, &dummy, &nNewBadTiles);
			if( nNewBadTiles > recoil + 1 )
				recoil++;

			if( ((recoil <= 1) && (nNewBadTiles < VEHICLE_MAX_UNTRAFFICABLE_TILES)) 
				|| (pVehicle->prevBadTiles > nNewBadTiles)
				|| cheat_move ) //if we can move freely
			{	
				if (nDeltaTiles)	
					pVehicle->framesstuck=0; //if we actually moved any distance, we're not stuck
				pVehicle->prevBadTiles = nNewBadTiles;
			}
			else
			{
				pVehicle->framesstuck++;

				// if it looks like we're stuck, we see if we've been stuck for enough frames to 
				// start allowing some number of untrafficable tiles in the vehicle mask
				if (pVehicle->framesstuck>=VEHICLE_STUCK_FRAMES_BEFORE_UNSTICK)
				{
					if( (recoil <= pVehicle->framesstuck/VEHICLE_STUCK_FRAMES_BEFORE_UNSTICK) && 
						(nNewBadTiles<=VEHICLE_MAX_UNTRAFFICABLE_TILES))
						pVehicle->framesstuck=0;
					pVehicle->prevBadTiles = nNewBadTiles;
				}
							
				//if we're truly stuck
				if (pVehicle->framesstuck)
				{
					absvelocity = abs(pVehicle->pAnimation->velocity);
					if( pVehicle->pAnimation->velocity >= 0 )
						absmaxvelocity = pVehicle->max_velocity;
					else
						absmaxvelocity = -pVehicle->min_velocity;

					if( absvelocity >= absmaxvelocity )	
					{
						AudioPlayItem(VEHICLE_LOW_IMPACT, (ITEM *) pVehicle);
						SetupQuake( newloc, 3 );
					}
					pVehicle->full_velocity = velocity = 0;
					spin = 0;                    
				}
			}
		}

        // pending spin still allowed, implement it
		if (spin)	
		{	
			AnimForceFacing(pAnim,NormalizeFacing(pAnim->facing + spin));

			// add vehicle turn to immediate turret turn 
			VehicleLockTurret(pVehicle, spin);
		}

		pVehicle->spin = 0;						// no pending spin left
		pVehicle->velocity = velocity;			 // update velocity
		remote_pos = OFF_THE_MAP;
	}


	AnimForceVelocity(pAnim, ABSOLUTE_VELOCITY, velocity);

	if (pVehicle->common.nStrength)	
	{
		if (velocity == 0)
			AnimSetCommand(pAnim, VSTOP_COMMAND);
		else if (abs_velocity < 150)
			AnimSetCommand(pAnim, VMOVE_COMMAND);
		else
			AnimSetCommand(pAnim, VROCK_FAST_COMMAND);
	}

	AnimUpdate(pAnim);			// updates the old_world_pos

	if (remote_pos.x)	
	{
        pAnim->world_pos = remote_pos;
		AnimMoveUpdate(pAnim);
	}
	else	
	{
		AnimMove(pAnim, TRUE);
	}

	pVehicle->common.facing = pAnim->facing;		// mirror anim facing

	if ((moved) || (velocity) || (spin))
	{
        ClearVehicleFromVehicleLayer(pVehicle);
	}
	else
	{
        // vehicle must not be undeployed or dying
        if (pVehicle->state == VEHICLE_DEPLOYED &&
            pVehicle->framesNotMoving<FRAMES_BEFORE_ADD_TO_MOVEMENT_LAYER)
		{
			pVehicle->framesNotMoving++;
			if (pVehicle->framesNotMoving==FRAMES_BEFORE_ADD_TO_MOVEMENT_LAYER)
				AddVehicleToVehicleLayer(pVehicle);
		}
	}


	getVehicleMask(pVehicle->common.position, pVehicle->common.facing, ITEM_CLASS(pVehicle), &pVehicle->mask);

	if (IS_LOCAL_ITEM(pVehicle)) VehicleUpdateMessageSend(pVehicle);

	pVehicle->old_gun_facing = pVehicle->gun_facing;

	WeaponFireUpdate(pVehicle->common.pWeapon);

    // update visibility from sargeinvehicle or vehicle alone in unit.cpp now

	if (ItemUserVisible(ARMY_PLAYER, pVehicle))
		ITEM_SET_VISIBLE((ITEM *) pVehicle);
	else
		ITEM_SET_INVISIBLE((ITEM *) pVehicle);

    pAnim->flags &= ~ANIM_FLAG_INVISIBLE;
    (&pAnim[TURRETANIM])->flags &= ~ANIM_FLAG_INVISIBLE;
    if (pVehicle->common.bItemFlags & ITEM_INVISIBLE)
    {
        pAnim->flags |= ANIM_FLAG_INVISIBLE;
        (&pAnim[TURRETANIM])->flags |= ANIM_FLAG_INVISIBLE;
    }

	ItemUpdatePosition((ITEM*)pVehicle, &pAnim->world_pos);

	pVehicle->count += gpGame->dwDeltaTime;
	pVehicle->tcount += gpGame->dwDeltaTime;
}



///========================================================================
//	Function:		VehicleTeleport()
//
//	Description:
//		Update the actions of an remote Army Vehicle.
//
//	Input:			pUnits			list of units to update
//					nNumberOfUnits	number of units in list
//
//	Ouput:			none
//
///========================================================================

void	VehicleTeleport( VEHICLE* pVehicle, SHORT x, SHORT y )
{
	ANIM *pAnim = pVehicle->pAnimation;

    SPOINT point;
    point.x = x;
    point.y = y;
    ItemSpecialUpdatePosition((ITEM*)pVehicle, &point);

	AnimUpdate(pAnim);						// updates the old_world_pos
	AnimMove( pAnim, FALSE );

	pVehicle->pAnimation->world_pos.x = pVehicle->common.position.x;		// x position within the world
	pVehicle->pAnimation->world_pos.y = pVehicle->common.position.y;		// y position within the world
	AnimUpdateChildPos(pAnim);

}


extern BOOL fire_flag;

void	GetVehicleInput(VEHICLE *pVehicle)
{
    if (pVehicle->common.nStrength == 0) return; // you can't control dead vehicle
    if (pVehicle->aiGoal.x) return;	// controlled by ai at present

	if (user_action & DO_ACCELERATE)
		VehicleSetDesiredVelocity(pVehicle, 1000);
	else if (user_action & DO_DECELERATE)
		VehicleSetDesiredVelocity(pVehicle, -1000);
	else
		VehicleSetDesiredVelocity(pVehicle, 0);

	if (user_action & DO_ALT)
		;
	else if (user_action & DO_TURN_LEFT)
		VehicleTurn(pVehicle, LEFT_VEHICLE);
	else if (user_action & DO_TURN_RIGHT)
		VehicleTurn(pVehicle, RIGHT_VEHICLE);

	if( user_action & DO_FIRE )
	{
		if( WeaponSingleShot(pVehicle->common.pWeapon) )
			fire_flag = TRUE;
		else
			VehicleFireWeapon(pVehicle);
	}
	else	{
		if( fire_flag )	{
			fire_flag = FALSE;
			VehicleFireWeapon(pVehicle);
		}
	}

	if( (user_action & DO_GUN_LEFT) || (MouseDx > 0) || (MouseDy > 0) )
		VehicleTurnTurret(pVehicle, FINE_LEFT_VEHICLE, pVehicle->common.facing);
	else if( (user_action & DO_GUN_RIGHT) || (MouseDx < 0) || (MouseDy < 0)  )
		VehicleTurnTurret(pVehicle, FINE_RIGHT_VEHICLE, pVehicle->common.facing);
	else
	{
		vehaccelwait = 0;
	}
}



///========================================================================
//	Function:		VehicleSetDirection()
//
//	Description:
//		Set the direction for a vehicle.
//
//
//	Input:			pTheVehicle		vehicle that needs a direction change
//					direction		direction to apply
//
//	Ouput:			none
//
///========================================================================

void	VehicleSetDirection( VEHICLE* pVehicle, int direction )
{
	// validate the input
	ASSERT( pVehicle );
	ASSERT( direction < CIRCLE_UNITS );

	// now set the trooper's animation direction
	AnimChgFacing( pVehicle->pAnimation, direction );
}


///========================================================================
//	Function:		VehicleGetDamage()
//
//	Description:
//		return the % of damage still available for a vehicle
//
//
//	Input:			pVehicle		vehicle whose damage remaining we want.
//
//	Ouput:			nPercent		the % of damage still available.
//
///========================================================================

int	VehicleGetDamage( VEHICLE* pVehicle )
{
	int	eVehicle;
	int	nMaxStrength;

	// get the type of vehicle this is
	eVehicle = ITEM_CLASS(pVehicle);

	// get this vehicles maximum strength
	nMaxStrength = pVehicle->common.nMaxStrength;

	// now calculate the percentage left from the current strength
	int	nPercent = 0;			// assume fully damaged
	if (nMaxStrength)
		nPercent = (((nMaxStrength - pVehicle->common.nStrength) * 100) / nMaxStrength);

	// return the percentage remaining
	return( 100-nPercent );
}


///========================================================================
//	Function:		VehicleDeadCallback()
//
//	Description:
//		do damage 
//
//
//	Input:			pAnim		vehicle whose damage remaining we want.
//									
//									
//									
//	Ouput:			.
//
///========================================================================

LONG VehicleDeadCallback(Anim *pAnim)
{
	// really most sincerely dead
	VEHICLE *pVehicle = (VEHICLE *) pAnim->pOwner;
	// make sure this goes into vehicle layer
	ClearVehicleFromVehicleLayer(pVehicle);
	AnimCallbackClear(pAnim);
	CreateVehicleHusk( pVehicle );
 	ReinsertVehicleInVehicleLayer(pVehicle,TRUE);
	pVehicle->state = VEHICLE_DEAD;

	if (ITEM_ARMY(pVehicle) == ARMY_PLAYER)
		;					// do player only stuff

	return TRUE;
}


EXPLOSION_DATA	VehicleHitAndExplode[] =
{
	{ FALSE, INACTIVATE_COMMAND,                   NULL,			SND_NULL_SND_ID },	// ARMY_NO_VEHICLE
	{ TRUE,  EXPLOSION_FLASH_COMBUSTION_S_COMMAND, &SmallExplosion,	SND_NULL_SND_ID },	// ARMY_JEEP
	{ TRUE,  EXPLOSION_FLASH_COMBUSTION_L_COMMAND, &LargeExplosion,	SND_NULL_SND_ID },	// ARMY_TANK
	{ TRUE,  EXPLOSION_FLASH_COMBUSTION_M_COMMAND, &MediumExplosion,SND_NULL_SND_ID },	// ARMY_HALFTRACK
	{ TRUE,  EXPLOSION_FLASH_COMBUSTION_M_COMMAND, &MediumExplosion,SND_NULL_SND_ID }	// ARMY_CONVOY
};


EXPLOSION_DATA	VehicleExplode[] =
{
	{ FALSE, INACTIVATE_COMMAND,					NULL,			SND_NULL_SND_ID },	// ARMY_NO_VEHICLE
	{ TRUE,  EXPLOSION_COMBUSTION_S_COMMAND,		&SmallExplosion,SND_NULL_SND_ID },	// ARMY_JEEP
	{ TRUE,  EXPLOSION_COMBUSTION_L_COMMAND,		&LargeExplosion,SND_NULL_SND_ID },	// ARMY_TANK
	{ TRUE,  EXPLOSION_COMBUSTION_M_COMMAND,		&MediumExplosion,SND_NULL_SND_ID },	// ARMY_HALFTRACK
	{ TRUE,  EXPLOSION_COMBUSTION_M_COMMAND,		&MediumExplosion,SND_NULL_SND_ID }	// ARMY_CONVOY
};


///========================================================================
//	Function:		VehicleDamage()
//	Description:	do damage 
///========================================================================

LONG VehicleDamage(VEHICLE *pVehicle, int damagetodo, int damagetype, SPOINT *damageloc,UID fromUID)
{
	ANIM	*pAnim = pVehicle->pAnimation;
	BOOL	HitByExplosion = FALSE;
	BOOL	HitByBullet = FALSE;
	if (pVehicle->pDriver && sargeImmune && ITEM_ARMY(pVehicle) == ARMY_PLAYER) 
		return pVehicle->common.nStrength; // sarge and vehicle are immune
	int oldstrength;
	oldstrength=pVehicle->common.nStrength;

	// now decide the reaction to the damage
	switch( damagetype )
	{
		case DMGTYPE_BAZOOKA:
		case DMGTYPE_MISSILE:
			HitByExplosion = TRUE;
			break;

		case DMGTYPE_BULLET:
			AudioPlayItem(BULLET_HIT_VEHICLE, (ITEM *) pVehicle);
			MakeChips( *damageloc, UnitColorTable(ITEM_ARMY(pVehicle)), 0 );
			HitByBullet = TRUE;
			break;
	}


	if (!IS_LOCAL_ITEM(pVehicle)) {	  // tell the other player he is hit
		VehicleDamageMessageSend(pVehicle, damagetodo, damagetype, damageloc);
	 	return( (ULONG)(pVehicle->common.nStrength) );
	}

    ITEM* pHitme = AiItemFind(fromUID);
	if( pHitme )
	{
		if (ITEM_TYPE(pHitme) == ARMY_TROOPER)
			pHitme = (ITEM*) ((TROOPER*)pHitme)->pUnit;
		TadBeingHit(pHitme,(ITEM*) pVehicle);
	}


    if (!oldstrength) return 0; // cannot be damaged more

  
	if ((pVehicle->common.nStrength <= damagetodo) )	{
		damagetodo += EXPLODINGVEHICLEDAMAGE;

        // must do secondary explosion before this, so vehicle on map
		VehicleDie(pVehicle); // kill off this vehicle now, after explosion

		// this will only work locally -- we won't track sarge kills multiplayer
		if (OBJTYPE(fromUID) == ARMY_SARGE)
			Armies[EXTRACT_ARMY(fromUID)].sarge_kills++;
	}
	else 
	{
		int vehicle_armor;

		if( damagetype == DMGTYPE_FLAMED && damagetodo > 1)
		{
			vehicle_armor = damagetodo;
			if( (rand() & 0xff) < 96 )					// do damage only part of the time
				vehicle_armor--;;
		}
		else
		{
			vehicle_armor = pVehicle->nArmor / 10;
			if( damagetodo > 1 && damagetodo <= vehicle_armor )		// do at least 1 point of damage!
				damagetodo = vehicle_armor + 1;
		}
		if( vehicle_armor < damagetodo )
			pVehicle->common.nStrength -= (damagetodo - vehicle_armor);
	}

	DamageItemTriggerEvents((ITEM*)pVehicle, oldstrength, pVehicle->common.nStrength, pVehicle->common.nMaxStrength);

	return( (ULONG)(pVehicle->common.nStrength) );
}


///========================================================================
//	Function:		VehicleDie()
//	Description:
//		start animation for death sequence on vehicle
///========================================================================

void VehicleDie(VEHICLE *pVehicle)
{
    SARGE* 	pSarge;
	ANIM	*pAnim = pVehicle->pAnimation;
    pVehicle->state = VEHICLE_DYING;
    pVehicle->common.nStrength = 0;

	Armies[ITEM_ARMY(pVehicle)].vehicles_killed++;


    // remove tad
    if (pVehicle->common.pTad)
    {
        UnitValidateTad(); // just test the hell out of the links
        TadDeleteObject( (TAD*)(pVehicle->common.pTad) );	
        pVehicle->common.pTad = NULL;
        UnitValidateTad(); // just test the hell out of the links
    }

	pVehicle->full_velocity = 0;
    pAnim->velocity = 0;
	AnimSetCommand(pAnim, VDIE_COMMAND);
	AnimSetCommand(&pAnim[TURRETANIM], INACTIVATE_COMMAND);

	AnimCallback(pAnim, VehicleDeadCallback, 0, VDEAD_COMMAND);
	
	GenerateDeadVehicleParts( (int)(ITEM_CLASS(pVehicle)), pAnim->world_pos, 
		pAnim->trans_table );

	ClearVehicleFromVehicleLayer(pVehicle);

	pVehicle->deadPosition = pVehicle->common.position;

	ItemSpecialUpdatePosition((ITEM*)pVehicle, &OFF_THE_MAP);

    if (IS_LOCAL_ITEM(pVehicle))	{
		VehicleDiedMessageSend(pVehicle);
		PlayVehicleSound(pVehicle, DELETE_SOUND);
	}

    // if sarge was inside, he better bail out now
    pSarge = SargePointer(ITEM_ARMY(pVehicle));
    if (IS_LOCAL_ITEM(pSarge) && pSarge->pVehicle == pVehicle)
        SargeOutVehicle(pSarge);

    // if units carried, they die
    UNIT* pUnit;
    LEGION* pLegion;
    TROOPER* pTrooper;
    int i;
    pLegion = ArmyGetLegion(ITEM_ARMY(pVehicle));
    if (IS_LOCAL_ITEM(pVehicle))
    {
        FOR_EACH_UNIT(pLegion,pUnit)
        {
            if (pUnit->pVehicle != pVehicle) continue;	// not in with us
			if (UNIT_IN_HQ(pUnit)) continue;				// shouldn't happen
            pUnit->pVehicle = NULL;
            FOR_EACH_TROOPER(pUnit,pTrooper,i)
            {
                // we dont know who killed this vehicle.
                TrooperAcceptDamage(pTrooper,pTrooper->common.nStrength,DMGTYPE_RUNOVER,
                    pTrooper->common.position,0);
            }
        }
    }
    
    // this should be last, in case it executes a resurrection
	DiedItemTriggerEvents((ITEM*)pVehicle);
}

///========================================================================
//	Function:		VehicleFind()
//	Description:	locate the vehicle with this UID
///========================================================================

VEHICLE*	VehicleFind( LONG nUniqueID )
{
    LEGION* 	pLegion;
    int 		i;
	int eArmy;
	eArmy = EXTRACT_ARMY(nUniqueID);
	if (Armies[eArmy].Status == 0) return NULL; // army not there
	ASSERT (OBJTYPE(nUniqueID) == ARMY_VEHICLE );
    pLegion = ArmyGetLegion(eArmy);
    i = SUB2TYPE(nUniqueID);
    if (ITEM_UID(pLegion->pLegionVehicles[i]) == nUniqueID)
        return pLegion->pLegionVehicles[i];

    return NULL;
}

///////////////////////////////////////////////////////////////////////////
// Vehicle UI

void VehicleSargeFlip()
{
    SARGE* pSarge = SargePointer(ARMY_PLAYER);
    VEHICLE* pVehicle;
    VEHICLE* pEnterVehicle = NULL;
	LEGION* pLegion;			
	SPOINT cntr;

	if (UI_CurMode != UIMODE_LOOKINGATSARGE)
		return;

    int d = 10000;
    int i;
    // if in vehicle, exit it
    if (pSarge->pVehicle)
    {
		if (!pSarge->pVehicle->full_velocity)	{
			PlayVehicleSound(pSarge->pVehicle, DELETE_SOUND);
			SargeOutVehicle(pSarge);
		}
    }
    else
    {
		pLegion = ArmyGetLegion(ARMY_PLAYER);
        for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
        {
			pVehicle= pLegion->pLegionVehicles[i];
			if (!pVehicle) continue;
            // no undeployed or dying vehicles
            if (pVehicle->state != VEHICLE_DEPLOYED) continue;
            // cannot enter an npc vehicle
            if (pVehicle->npc) continue;
            int n;
			cntr = ItemCenterPos((ITEM*)pVehicle);
            n = TileDistance(ENCODE_IPOINT(cntr.x,cntr.y),pSarge->common.tile);
			if (n > 6) continue;
            if (n < d)
            {
                d = n;
                pEnterVehicle = pVehicle;
            }
        }
        if (pEnterVehicle)
            SargeInVehicle(pSarge,pEnterVehicle);
    }
}

///========================================================================
//	Function:		VehiclsInHQ
//	Description:	Get list of vehicles of this type still in HQ
///========================================================================

int	VehiclesInHQ( ARMY_TYPE eArmy, VEHICLE_TYPE eVehicleType, UID* pUIDs )
{
	LEGION*		pLegion = ArmyGetLegion(eArmy);
	VEHICLE*	pVehicle;
	int			nVehiclesInReserve = 0;
	int			i,n;

    for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
    {
        pVehicle = pLegion->pLegionVehicles[i];
        // already deployed
        if (pVehicle->state != VEHICLE_UNDEPLOYED) continue;
        n = ITEM_CLASS(pVehicle);
        if (n != eVehicleType) continue;
                        
        *pUIDs = ITEM_UID(pVehicle);
        ++nVehiclesInReserve;
        ++pUIDs;
    }

	// let the caller know how many names were found
	return( nVehiclesInReserve );
}


SHORT vehicle_height[] = {
	0,		// ARMY_NO_VEHICLE = 0,

	12,		// ARMY_JEEP,
	12,		// ARMY_TANK,
	12,		// ARMY_HALFTRACK,
	12,		// ARMY_CONVOY,
};

///========================================================================
//	Function:		VehicleHitByMissile
//	Description:	will this vehicle stop a missile and take damage from it?
///========================================================================

BOOL VehicleHitByMissile(VEHICLE* pVehicle, SHORT height)
{
	if (height <= GetItemHeight((ITEM *)pVehicle) )
		return TRUE;
	return FALSE;
}

void VehicleSoundOff()	{
    SARGE *pSarge = SargePointer(ARMY_PLAYER);
    if (pSarge->pVehicle)
		PlayVehicleSound(pSarge->pVehicle, DELETE_SOUND);
}

void VehicleSoundOn()	{
    SARGE *pSarge = SargePointer(ARMY_PLAYER);
    if (pSarge->pVehicle)
		PlayVehicleSound(pSarge->pVehicle, FULL_LOOP_SOUND);
}

///========================================================================
//								EOF
///========================================================================

