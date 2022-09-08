/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Float.cpp $
//
//	DESCRIPTION:	floating objects (missiles, etc.)
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Sunday, March 23, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Float.cpp 114   4/10/98 5:38p Phu $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Float.cpp $
//  
//  114   4/10/98 5:38p Phu
//  explosion sounds from off screen
//  
//  112   4/02/98 7:21p Phu
//  put missiles in top layer
//  
//  111   4/02/98 3:06p Phu
//  
//  110   4/01/98 12:43p Bwilcox
//  changed isremote to is-local_army
//  
//  109   4/01/98 12:15p Phu
//  
//  108   4/01/98 12:14p Phu
//  fix appearance, etc of tank missiles, fix vehicle heights to be 12+
//  
//  107   3/30/98 2:33p Phu
//  make it a little easier to hit troopers
//  
//  106   3/27/98 11:58a Phu
//  account for height when limiting projectiles off the edge of the screen
//  
//  105   3/26/98 9:35p Phu
//  strategy items: prone, roll & dive protection
//  
//  104   3/20/98 3:40p Phu
//  don't hit an object with movement 0 unless height is exact
//  
//  103   3/20/98 1:39p Phu
//  fix up shadows for mortar/grenade
//  
//  102   3/18/98 4:16p Phu
//  stop flames when they hit
//  
//  101   3/13/98 4:49p Dmaynard
//  Changed  Comm::IsRemote to return 1 if remote, 0 if not playing, and -1
//  if was playing but has left.  Needed so scripts can send messages to
//  others players that this player has left the game.
//  
//  100   3/13/98 11:38a Phu
//  increase minimum grenade & mortar velocity
//  
//  99    3/10/98 3:45p Phu
//  note that clipline sometimes returns 0!
//  added assert to getobjects
//  fix flamethrowers go off screen
//  
//  98    3/10/98 2:15p Phu
//  
//  97    3/10/98 2:15p Phu
//  
//  96    3/05/98 6:07p Phu
//  
//  95    3/04/98 3:01p Phu
//  change flame thrower timings
//  
//  94    3/04/98 2:34p Phu
//  Start rifle bullets sooner
//  
//  93    3/03/98 7:56p Phu
//  multi-directional flame thrower
//  
//  92    2/20/98 7:09p Nrobinso
//  change water sfx
//  
//  91    2/20/98 4:59p Phu
//  make sure to add pixels to total_distance for floats
//  
//  90    2/20/98 4:23p Aburgess
//  initialized float value
//  
//  89    2/20/98 2:50p Phu
//  make floats hit bridges at height 0
//  
//  88    2/20/98 1:17p Nrobinso
//  fix up sounds
//  
//  87    2/17/98 5:22p Phu
//  only display damaging explosion in MP
//  
//  86    2/16/98 12:03p Phu
//  pass along fromUID with explosions
//  
//  85    2/13/98 6:56p Phu
//  
//  84    2/13/98 6:03p Phu
//  change in elevation factor
//  
//  83    2/13/98 5:56p Phu
//  fix collision detection
//  
//  82    2/13/98 4:12p Phu
//  
//  81    2/13/98 4:12p Phu
//  good lobbing action
//  
//  80    2/13/98 11:13a Phu
//  
//  79    2/12/98 8:55p Phu
//  mortar screen scroll, better force of gravity
//  
//  78    2/12/98 7:11p Phu
//  don't do double damage from behind for some weapons
//  
//  77    2/12/98 6:32p Phu
//  reduce damage done by stuff for crying out loud!
//  
//  76    2/12/98 5:53p Nrobinso
//  
//  75    2/12/98 1:55p Phu
//  make mortars work better
//  
//  74    2/12/98 11:56a Phu
//  grenade stuff
//  
//  73    2/11/98 2:42p Phu
//  change mortar firing, have cursor follow range for grenade/mortar
//  
//  72    2/11/98 12:25p Phu
//  
//  71    2/11/98 12:05p Phu
//  better bazooka firing
//  
//  70    2/10/98 4:37p Phu
//  grenades vary velocity for distance now
//  
//  69    2/10/98 3:02p Phu
//  only use bmp as mask for vehicles
//  
//  68    2/10/98 3:01p Phu
//  only use bmp as mask for vehicles
//  
//  67    2/10/98 2:21p Phu
//  firing heights
//  
//  66    2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  65    2/07/98 4:21p Phu
//  up flame damage again!
//  
//  64    2/06/98 11:42a Phu
//  husks
//  
//  63    2/04/98 5:45p Phu
//  up flamethrower damage rate
//  
//  62    2/03/98 2:33p Phu
//  Changed force_of_gravity to be consistent on a time basis instead of a
//  frame basis.  Change flamethrowers to do damage on a time basis instead
//  of a frame basis
//  
//  61    2/01/98 2:09p Phu
//  make grenades/mortars blow up on elevation 0
//  
//  60    1/27/98 12:56p Phu
//  
//  59    98-01-15 19:26 Dmaynard
//  Checked DoDameFlag in ProjectileExplode
//  
//  58    1/15/98 2:45p Phu
//  fix flamethrower weapon type
//  
//  57    1/15/98 2:18p Phu
//  flame throwers now hurt friendlies
//  
//  56    1/15/98 12:00p Phu
//  
//  55    1/14/98 7:10p Phu
//  use weapon type w/ floats instead of pointer
//  
//  54    1/09/98 6:32p Phu
//  flamers now do damage more
//  
//  53    12/19/97 2:35p Phu
//  implement 14 tile boundary
//  
//  52    12/19/97 10:21a Phu
//  
//  51    12/11/97 1:11p Phu
//  
//  50    12/11/97 9:51a Phu
//  
//  49    12/09/97 12:12p Phu
//  
//  48    12/05/97 5:13p Phu
//  fix weird grenade handling
//  
//  47    12/04/97 11:10a Phu
//  Added extra layer, moved order variable, changed flamer
//  
//  46    11/25/97 6:41p Phu
//  do something for floats
//  
//  45    11/24/97 8:35p Phu
//  Add Z component to projectile firing
//  
//  44    11/21/97 4:31p Phu
//  
//  43    11/21/97 11:44a Phu
//  don't remember what I did but I'm sure it was good
//  
//  42    11/20/97 8:54p Phu
//  Wacky stuff with grenades/mortars
//  
//  41    11/20/97 6:39p Phu
//  
//  40    11/20/97 5:30p Phu
//  
//  39    11/20/97 11:42a Phu
//  attached muzzle flashes
//  
//  38    11/19/97 5:40p Phu
//  flamethrowers & muzzle flashes
//  
//  37    11/17/97 11:06a Nrobinso
//  improved missile hit code
//  
//  36    11/16/97 5:29p Nrobinso
//  FLoatCreate no longer takes a type; the MINE object category became the
//  EXPLOSIVES category
//  
//  35    11/11/97 6:07p Phu
//  fix z-velocity vs. shadow vs. gun origin
//  add gun turret sides
//  
//  34    11/11/97 5:25p Phu
//  get rid of double explosions
//  
//  33    11/11/97 4:52p Phu
//  Guard Towers
//  
//  32    11/06/97 3:29p Phu
//  Moved Explosions to top layer
//  
//  31    11/06/97 3:06p Phu
//  Rifle firing stuff
//  
//  30    10/30/97 9:32a Nrobinso
//  turret_facing becomes gun_facing
//  
//  29    10/16/97 6:26p Nrobinso
//  add nMaxStrength to ITEM; made Unit consistent with new scheme, put
//  number of troopers inot pUnit->troops
//  
//  28    10/13/97 5:20p Nrobinso
//  change weapon in ITEM to an item pointer, then add WEAPON data to those
//  structures that need it.
//  
//  27    10/09/97 12:07p Phu
//  fix for item size maximums
//  
//  26    10/08/97 3:43p Nrobinso
//  ARMY_SARGE_GUN -> ARMY_RIFLE
//  
//  25    10/01/97 3:48p Phu
//  Algorithmic implementation for big items & item deletion
//  
//  24    9/30/97 4:00p Phu
//  New display engine!
//  
//  22    8/21/97 6:47p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  21    8/17/97 11:27a Bwilcox
//  names of TROOPxxx are now TROOPERxxx in a cleanup
//  
//  20    8/13/97 10:22p Nrobinso
//  fix so projectiles don't hurt your own guys unless they explode
//  
//  19    8/13/97 6:52p Nrobinso
//  add weapon projectile speeds to aidefault file
//  
//  18    8/13/97 2:36p Nrobinso
//  projectiles check trooper conditions to see if they are hit
//  
//  17    8/12/97 3:48p Nrobinso
//  added tracer round; mines blow up with missiles/tracer
//  
//  16    8/08/97 9:45a Nrobinso
//  mortars & grenades only explode at end; turn off recoloring of
//  projectiles
//  
//  15    8/07/97 11:19p Nrobinso
//  simplified projectiles; all projectile damage occursa tru ItemDamage
//  
//  14    8/06/97 9:51a Nrobinso
//  ProjwctileSet takes a distance; projectile damage does double damage
//  when hitting from behind
//  
//  13    8/05/97 3:31p Nrobinso
//  item bflags becomes bItemFlags
//  
//  12    8/03/97 10:07p Bwilcox
//  replaced compile-time constants of float with WeaponRange call
//  
//  11    7/30/97 12:26p Bwilcox
//  damage now hits ARMY_SARGE as well
//  
//  10    7/29/97 10:56p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
//  
//  9     7/29/97 10:48a Nrobinso
//  GetTile functions now return OBJ_DATA*
//  
//  8     7/28/97 7:47p Nrobinso
//  add projectile collisions with sarge
//  
//  7     7/27/97 12:30p Nrobinso
//  slow down mortar
//  
//  6     7/27/97 11:39a Nrobinso
//  added a mortar float type
//  
//  5     7/24/97 1:02p Aburgess
//  added knowledge of ARMY_NULL_OBJ and removal of superfluous trace
//  statements
//  
//  4     7/14/97 4:27p Nrobinso
//  removed dead code
//  
//  3     7/11/97 7:24p Bwilcox
//  nUniqueID's now work for all objects (except ARMY_POSITION, which is
//  fake)
//  avoid direct refs to eWhoseArmy,eType,eID and use macros:
//  OBJECT_ARMY(x), OBJECT_TYPE(x), OBJECT_CLASS(x) where x is
//  any kind of object.
//  Use UnitFind, TrooperFind, or AssetFind on a UID to get ptr (assetfind
//  works on assets, buildings, etc).
//  
//  2     7/09/97 11:29p Bwilcox
//  Hiding unit dsr access via functions and macros
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  12    6/30/97 8:41p Bwilcox
//  moving protos out of army.h into vehicle.h, trooper.h, unit.h 
//  removing dead code and variables.
//  
//  11    6/14/97 4:51p Nrobinso
//  call projectileremoteupdate from projectileupdate if remote
//  
//  10    5/16/97 4:45a Dmaynard
//  Removed Friendly Fire upon Troops
//  
//  9     5/15/97 9:09p Dmaynard
//  Added New Paramter to AnimMove() to allow interploated movement of
//  remote objects (while still allowing animation to be controled by local
//  frame rates.
//  
//  8     5/15/97 5:44p Dmaynard
//  Added vechile velocity to grenade velocity when launchin a grenade from
//  a jeep moving forward so that it no longer lands on top of you.
//  
//  7     5/15/97 2:49p Nrobinso
//  recolor missiles to match vehicle
//  
//  6     5/14/97 10:32p Nrobinso
//  move projectile code here
//  
//  5     5/12/97 1:58p Nrobinso
//  temporary grenade patch
//  
//  4     5/09/97 10:01a Nrobinso
//  switch to using anim active flags
//  
//  3     5/08/97 10:29a Nrobinso
//  check float obj having moved it's max distance
//  
//  2     5/06/97 9:57p Nrobinso
//  DispCreate now only takes 1 arg
//  
//  1     5/05/97 10:20a Nrobinso
//  initial check in
//  
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "Anim.h"
#include "Army.h"
#include "audio.h"
#include "Comm.h"
#include "Disp.h"
#include "MainFrm.h"
#include "AiAccess.h"
#include "Tad.h"
#include "Map.h"
#include "Explosions.h"
#include "trooper.h"
#include "sarge.h"
#include "vehicle.h"
#include "Damage.h"
#include "item.h"
#include "weapon.h"

#include "gameflow.h"
#include "wobject.h"


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
#define MAX_VELOCITY	1000
#define FLOAT_STEP		2
#define AUTO_HIT_ZONE	48
int		force_of_gravity = 400;


extern COMMAND_LIST missile_commands;

/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////
extern void AnimWorldBoundary( ANIM* pTheAnim );

/////////////////////////////////////////////////////////////////////////////
//					LOCAL Prototypes
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//					     Code
/////////////////////////////////////////////////////////////////////////////

///========================================================================
//	Function:		FloatCreate()
//
//	Description:
//		Create a Float object.
//
//	Input:			pNewFloat		the new vehicle data
//					pPosition		where to place the vehicle in the world 
//
//	Ouput:			none
//
///========================================================================

BOOL	FloatCreate( FLOAT_OBJ* pNewFloat, ARMY_TYPE eArmy, SPOINT* pPosition )
{
	BOOL	ok = FALSE;
    LEGION* pLegion = ArmyGetLegion(eArmy);

	// create the vehicle animation structures
	pNewFloat->pAnimation = (ANIM*)malloc( sizeof(ANIM) );
	if ( pNewFloat->pAnimation == NULL )
	{
		TRACE( "ERROR: failed to allocate float ANIM structure. [%s,%d]\n",
			__FILE__, __LINE__ );
		goto exit;
	}

	// clear the animation structure and set some internal pointers
	AnimInit( 10, 10, pNewFloat->pAnimation, OL_TOPLAYER );

	// if we made it here we're in business
	ok = TRUE;

exit:
	return( ok );
}

///========================================================================
//	Function:		FloatDelete()
//
//	Description:
//		Create a Vehicle. A Vehicle is created once it is placed actively into
//		the world (via the main base).
//
//	Input:			eArmy			which army this unit belongs to
//					pNewVehicle		the new vehicle data
//					pPosition		where to place the vehicle in the world 
//
//	Ouput:			none
//
///========================================================================

void	FloatDelete( FLOAT_OBJ* pFloat )
{
	if ( pFloat->pAnimation )
	{
		AnimDelete( pFloat->pAnimation );
		free( pFloat->pAnimation );
		pFloat->pAnimation = NULL;

#ifdef MALLOC_DEBUG
		TRACE( "free: float anim [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}
}


///========================================================================
//	Function:		StopsMissile()
//
//	Description:
//		Update the actions of an Army Vehicle.
//
//	Input:			pObj			Pointer to OBJ
//
//	Ouput:			TRUE			if and only if the object should stop a missile
//
///========================================================================
static BOOL StopsMissile( ITEM *pItem, FLOAT_OBJ *pMissile, int height, int distance ) 
{
	if( pItem->nUniqueID == pMissile->fromUID )
		return FALSE;

	switch( ITEM_TYPE(pItem) )	
	{
		case ARMY_VEHICLE: 
			if (pItem->nStrength == 0)
				return FALSE;

			return ( VehicleHitByMissile((VEHICLE*)pItem, height ) );
			break;

		case ARMY_SARGE: 
			if (pItem->nStrength == 0)
				return FALSE;
			if( (pMissile->weaponType != ARMY_FLAME_THROWER) &&
				(ITEM_ARMY(pItem) == ITEM_ARMY( (ITEM *)pMissile )) )
				return FALSE;
/*
			SARGE *pSarge;
			pSarge = (SARGE *)pItem;			// diving/rolling to avoid a hit!
			if( AvatarInAir(pSarge->pAvatar) )	// 75% chance of miss
			{
				if( rand() & 3 )
					return FALSE;
			}
*/
			if( distance && distance < AUTO_HIT_ZONE )
				return TRUE;

			return( height <= GetItemHeight(pItem) );
			break;

		case ARMY_TROOPER:	
			if (pItem->nStrength == 0)
				return FALSE;
			if( (pMissile->weaponType != ARMY_FLAME_THROWER) &&
				(ITEM_ARMY(pItem) == ITEM_ARMY( (ITEM *)pMissile )) )
				return FALSE;
			if( distance && distance < AUTO_HIT_ZONE )
				return TRUE;
//			return ( TrooperHitByMissile((TROOPER*)pItem, height ) );
			return( height <= GetItemHeight(pItem) + 2 );
			break;

		case ARMY_ASSET:
		case ARMY_STRUCTURE:
		case ARMY_OBSTACLE:
		case ARMY_HUSK:
			OBJECT *pObj;

			pObj = (OBJECT *)pItem;
			if (ObjectIsDestroyed(pObj))
				return FALSE;
			if( pObj->movement == 0 )
			{
				if( pObj->elevation != height )
					return FALSE;
			}
			return ( ObjectHitByMissile((OBJECT*)pItem, height ) );
			break;
	}

	return FALSE;
}


int mortar_minz = 225;
int mortar_minv = 100;
int grenade_minz = 130;
int grenade_minv = 100;


FLOAT_OBJ *ProjectileSet( int eArmy, 
				    WEAPON *pWeapon, 
					int x, int y, int z,
					int direction, int distance, int height,
					VEHICLE *pVehicle, UID fromUID )
{
	LEGION* pLegion = &Armies[ eArmy ].Legion;
	int missile = pLegion->which_missile;
	ANIM *pAnim;
	FLOAT_OBJ *pMissile;
	FLOAT_OBJ *pShadow;
	int facingangle;
	int command1, command2;
	int z_velocity;
	int z_init;
	int velocity;
	int newvelocity;
	int type;
	EObjectLayer myLayer;

	velocity = pWeapon->nVelocity;
	z_velocity = pWeapon->nZVelocity;

	switch (pWeapon->eWeapon)	
	{
		case ARMY_MEDIUM_MACHINE_GUN:
		case ARMY_HEAVY_MACHINE_GUN:
			type = ARMY_RIFLE_FLOAT;
			command1 = GRENADE_COMMAND;
			command2 = GRENADE_SHADOW_COMMAND;
			z_init = 6;
			x += (int)(cos_table[direction] * 10);
			y += (int)(sin_table[direction] * 10);
			myLayer = OL_ORDEREDLAYER;
			break;

		case ARMY_LARGE_CANNON:
		case ARMY_BAZOOKA:
			type = ARMY_MISSILE_FLOAT;
			command1 = MISSILE_COMMAND;
			command2 = MISSILE_SHADOW_COMMAND;
			z_init = 8;
			myLayer = OL_ORDEREDLAYER;
			break;

		case ARMY_MORTAR:
			type = ARMY_MORTAR_FLOAT;
			command1 = MISSILE_COMMAND;
			command2 = MISSILE_SHADOW_COMMAND;			
			z_init = 8;
			z_velocity = (int)(mortar_minz + ((z_velocity - mortar_minz) * (distance/(float)WeaponMaxRange(pWeapon->eWeapon))));
			velocity = (int)(mortar_minv + ((velocity - mortar_minv) * (distance/(float)WeaponMaxRange(pWeapon->eWeapon))));
			distance = 1000;			// no max distance, explodes when it hits!
			myLayer = OL_TOPLAYER;
			break;

		case ARMY_GRENADE:
			type = ARMY_MORTAR_FLOAT;
			command1 = MISSILE_COMMAND;
			command2 = MISSILE_SHADOW_COMMAND;
			z_init = 8;
			velocity = (int)(grenade_minv + ((velocity - grenade_minv) * (distance/(float)WeaponMaxRange(pWeapon->eWeapon))));
			z_velocity = (int)(grenade_minz + ((z_velocity - grenade_minz) * (distance/(float)WeaponMaxRange(pWeapon->eWeapon))));
			distance = 1000;			// no max distance, explodes when it hits!
			myLayer = OL_TOPLAYER;
			break;

		case ARMY_LIGHT_MACHINE_GUN:
		case ARMY_AUTORIFLE:
		case ARMY_RIFLE:
			type = ARMY_RIFLE_FLOAT;
			command1 = GRENADE_COMMAND;
			command2 = GRENADE_SHADOW_COMMAND;
			z_init = 0;
			x -= (int)(cos_table[direction] * 10);		// start the bullet back a little bit
			y -= (int)(sin_table[direction] * 10);
			myLayer = OL_ORDEREDLAYER;
			break;

		case ARMY_GUARD_TOWER_RIFLE:
			type = ARMY_RIFLE_FLOAT;
			command1 = GRENADE_COMMAND;
			command2 = GRENADE_SHADOW_COMMAND;
			z_init = 96;
			z_velocity = -(int)(1000.0/(double)distance * z_init);
			myLayer = OL_ORDEREDLAYER;
			break;
		default:
			type = ARMY_RIFLE_FLOAT;
			command1 = GRENADE_COMMAND;
			command2 = GRENADE_SHADOW_COMMAND;
			myLayer = OL_ORDEREDLAYER;
			break;
	}

	if( z > 0 )
		z_init = z;
	if( pVehicle ) 
	{
		if( pVehicle->velocity ) 
		{
			facingangle = pVehicle->common.facing - pVehicle->gun_facing;
			if( facingangle < 0 )
				facingangle = -facingangle;
			if( facingangle < 48 || facingangle > 208 ) 
			{												// facing forward
				newvelocity = velocity+pVehicle->velocity;
				distance = newvelocity*distance/velocity;
				velocity = newvelocity;
			}
		}
	}

	pMissile = &pLegion->Projectiles[missile];
    pMissile->fromUID = fromUID;							// who fired this
	pMissile->weaponType = pWeapon->eWeapon;
	pMissile->link_missile = -1;
	pMissile->dest_height = height;
	pMissile->sndID = SND_NULL_SND_ID;;

	pAnim = pMissile->pAnimation;
    ItemSetUID( pMissile, eArmy, ARMY_FLOAT, type, missile);

	y = y + z_init;
	if( pAnim->layer != myLayer )
	{
		DestroyDispXObject( (ANIMCELL *)pAnim );
		CreateDispXObject( 10, 10, (ANIMCELL *)pAnim, myLayer );
	}
	AnimSet( pAnim, x, y, &missile_commands, command1, direction, ABSOLUTE_VELOCITY);
	AnimSetZ( pAnim, z_init, z_velocity);
	pAnim->dz = 0.0;
	pAnim->last_frame_time = 0;
	((ANIMCELL *)pAnim)->order = 0;
	AnimForceVelocity( pAnim, ABSOLUTE_VELOCITY, velocity);
	AnimActivate( pAnim, NO_ACTIVATE_LINKS);
	AnimTransTable( pAnim, UnitColorTable((ARMY_TYPE) eArmy) );
	pMissile->total_distance = 0;
	pMissile->max_distance = distance;

	pShadow = &pLegion->Shadows[missile];
	pShadow->fromUID = fromUID;
	pShadow->weaponType = pWeapon->eWeapon;
	pAnim = pShadow->pAnimation;
	pAnim->last_frame_time = 0;
    ItemSetUID(pShadow,eArmy,ARMY_FLOAT,type,missile);
	AnimSet( pAnim, x, y, &missile_commands, command2, direction, ABSOLUTE_VELOCITY);
	AnimSetZ( pAnim, 0, 0);
	AnimForceVelocity( pAnim, ABSOLUTE_VELOCITY, velocity);
	AnimActivate( pAnim, NO_ACTIVATE_LINKS);
	pShadow->total_distance = 0;
	pShadow->max_distance = distance;

	pLegion->which_missile++;
	if( pLegion->which_missile >= ARMY_LEGION_MISSILES )
		pLegion->which_missile = 0;

	return pMissile;
}


void MakeFlameBurst( int eArmy, WEAPON *pWeapon, int x, int y, 
					 int direction, int velocity, int height, UID fromUID )
{
	LEGION		*pLegion;
	FLOAT_OBJ	*pMissile;
	ANIM		*pAnim;
	int			missile;

	pLegion = &Armies[eArmy].Legion;
	missile = pLegion->which_missile;
	pMissile = &pLegion->Projectiles[missile];
    pMissile->fromUID = fromUID;							// who fired this
	pMissile->link_missile = -1;
	pMissile->weaponType = ARMY_FLAME_THROWER;

	if( gpGame->dwAnimTime - pWeapon->last_fire_time < 300 )
	{
		if( pWeapon->last_fire_projectile >= 0 )
		{
			FLOAT_OBJ *pPrevMissile;

			pPrevMissile = &(pLegion->Projectiles[pWeapon->last_fire_projectile]);
			if( pPrevMissile->pAnimation->flags & ANIM_FLAG_ACTIVE )
			{
				if( pPrevMissile->weaponType == ARMY_FLAME_THROWER )
					pPrevMissile->link_missile = missile;
			}
		}
	}
	pWeapon->last_fire_time = gpGame->dwAnimTime;
	pWeapon->last_fire_projectile = missile;

	direction += (rand() & 7) - 3;
	if( direction < 0 )
		direction += 256;
	else
	if( direction > 255 )
		direction -= 256;

	x += (int)(cos_table[direction] * 6);
	y += (int)(sin_table[direction] * 6);

	pMissile->common.position.x = x;
	pMissile->common.position.y = y;
	pMissile->dest_height = __max( height, 0);
	

    ItemSetUID(pMissile, eArmy, ARMY_FLOAT, ARMY_FLAME_FLOAT, pLegion->which_missile);
	pAnim = pMissile->pAnimation;

	if( pAnim->layer != OL_OVERLAYLAYER )
	{
		DestroyDispXObject( (ANIMCELL *)pAnim );
		CreateDispXObject( 64, 64, (ANIMCELL *)pAnim, OL_OVERLAYLAYER );
	}
	pAnim->facing = pAnim->next_facing = direction;
	pAnim->current_frame = 0;
	pAnim->last_frame_time = 0;
	pAnim->frame_time = 0;
	pAnim->facing_index = ((direction + 16) & 0xff) >> 5;
	pAnim->spriteArray = NULL;
	pAnim->pCommandList = NULL;
	pAnim->pSeq = NULL;
	pAnim->pFrame = NULL;
	pAnim->pSprite = FlameBurstData.sprites[pAnim->facing_index * FlameBurstData.num_frames];
	pAnim->set_velocity = ABSOLUTE_VELOCITY;
	pAnim->velocity = FlameBurstData.init_velocity + abs(velocity);
	pAnim->x_velocity = 0;
	pAnim->y_velocity = 0;
	pAnim->world_z = 0;
	pAnim->dx = 0.0;
	pAnim->dy = 0.0;
	pAnim->dz = 0.0;
	pAnim->world_pos = pMissile->common.position;
	((ANIMCELL *)pAnim)->order = 0x7fff;
	AnimActivate( pAnim, NO_ACTIVATE_LINKS);
	pMissile->total_distance = 0;
	pMissile->max_distance = 300;

	pLegion->which_missile++;
	if( pLegion->which_missile >= ARMY_LEGION_MISSILES )
		pLegion->which_missile = 0;
}


void DisplayDot( int x, int y )
{
	SPOINT pt;

	pt.x = x;
	pt.y = y;
	if( InRect( &the_map.screenrect, &pt ) )
		DrawDotFront( &pt, RGB_YELLOW );
}


int			eArmy;
FLOAT_OBJ	*pProjectile;
FLOAT_OBJ	*pShadow;
ANIM		*pProjectileAnim;
ANIM		*pShadowAnim;
LEGION		*pLegion;
BOOL		DoDamage;
DWORD		dwDeltaTime;


static void ProjectileExplode( FLOAT_OBJ *pMissile, int x, int y, int z, ITEM *pItem )	
{
	SPOINT	pt;
	int		nDamage, eDamageType;
	ANIM	*pAnim;

	pAnim = pMissile->pAnimation;
	pAnim->world_pos.x = x;
	pAnim->world_pos.y = y;
	pMissile->common.position = pAnim->world_pos;
	pt = pMissile->common.position;

	nDamage = AIinfo.weaponTables[pMissile->weaponType].damage.nDamage;
	eDamageType = WEAPON_DAMAGE_TYPE[pMissile->weaponType];

	if( DoDamage )					// take out this if check to make explosions on all sides
	{
		if( (!pItem) && (the_map.triggers[IPOINT_FROM_SPOINT(pt)] & TRIGGER_WATER) )
			DoExplosion( pt.x, pt.y,
						 EXPLOSION_WATER_L_COMMAND, 
						 &SmallExplosion,
						 eDamageType, nDamage, NULL, TRUE, pMissile->fromUID, WATER_HIT );
		else
		{
			pt.y -= z;
			DoWeaponExplosion(NULL, DoDamage ? nDamage : 0, eDamageType, &pt, NULL, pMissile->fromUID );
		}
	}
}


BOOL DealDamageVs( ITEM *pItem, WEAPON_TYPE weaponType )
{
	if( ITEM_TYPE(pItem) == ARMY_TROOPER )
		goto doswitch;
	if( ITEM_TYPE(pItem) == ARMY_SARGE )
		goto doswitch;
	return TRUE;						// all non trooper, sarge items get hit

doswitch:
	switch( weaponType )
	{
	case ARMY_MORTAR:					// these weapons have friendly trooper fire
	case ARMY_GRENADE:
	case ARMY_LARGE_CANNON:
	case ARMY_BAZOOKA:
		return TRUE;
	default:
		return( ITEM_ARMY(pItem) != eArmy );
	}	
}


BOOL DoFloatCollisionAtPoint( SPOINT &point, ITEM **pHitItem )
{
	int     height, distance;
	ITEM	*pItem;
	int		nDamage, eDamageType;
	int		elev;

//	DisplayDot( point.x, point.y );
	*pHitItem = NULL;

	// get missile height & distance traveled so far
	switch( pProjectile->weaponType )
	{
	case ARMY_LIGHT_MACHINE_GUN:
	case ARMY_AUTORIFLE:
	case ARMY_RIFLE:
	case ARMY_BAZOOKA:
		height = (int)(pProjectileAnim->world_z - pProjectileAnim->dz);
		distance = pProjectile->total_distance;
		break;
	default:
		height = pProjectileAnim->world_z;
		distance = 0;
		break;
	}

	pItem = GetObjectsIntersectPoint( &point );
	while( pItem )
	{
		if( !(StopsMissile( pItem, pProjectile, height, distance )) )
			goto nextitem;

//		if( pShadow->common.pWeapon->eWeapon != ARMY_GRENADE )
//		{
			nDamage = AIinfo.weaponTables[pShadow->weaponType].damage.nDamage;
			eDamageType = WEAPON_DAMAGE_TYPE[ pShadow->weaponType ];

			switch( ITEM_TYPE(pItem) )
			{
			case ARMY_TROOPER:
			case ARMY_SARGE:
				if( DoDamage )
				{
					switch( pProjectile->weaponType )
					{
					case ARMY_RIFLE:
					case ARMY_AUTORIFLE:
					case ARMY_LIGHT_MACHINE_GUN:
					case ARMY_MEDIUM_MACHINE_GUN:
					case ARMY_HEAVY_MACHINE_GUN:
					case ARMY_GUARD_TOWER_RIFLE:
						nDamage = DamageFromBehind( nDamage, pShadow->pAnimation->facing, pItem );				
						break;
					default:
						break;
					}
					ItemDamage( pItem, nDamage, eDamageType, &point, pProjectile->fromUID );
				}
				break;
			case ARMY_VEHICLE:
			case ARMY_ASSET:
			case ARMY_STRUCTURE:
			case ARMY_OBSTACLE:
			case ARMY_HUSK:
				if( DoDamage )
					ItemDamage( pItem, nDamage, eDamageType, &point, pProjectile->fromUID );
				break;
			default:
				goto nextitem;
			}
			*pHitItem = pItem;
			AnimForceCommand( pShadow->pAnimation, INACTIVATE_COMMAND, 0 );
			AnimForceCommand( pProjectile->pAnimation, INACTIVATE_COMMAND, 0 );
			return TRUE;
//		}
nextitem:
		pItem = pItem->next;
	}

	// determine if the missile hits the ground
	elev = ELEVATION(the_map.elevation_layer[IPOINT_FROM_SPOINT(point)]) << 2;
	if( pProjectile->weaponType == ARMY_LARGE_CANNON )
	{
		if( elev >= height + 4 )
		{
			AnimForceCommand( pShadow->pAnimation, INACTIVATE_COMMAND, 0 );
			AnimForceCommand( pProjectile->pAnimation, INACTIVATE_COMMAND, 0 );
			return TRUE;
		}
	}
	else
	if( elev >= height )
	{	// hit the ground!
		AnimForceCommand( pShadow->pAnimation, INACTIVATE_COMMAND, 0 );
		AnimForceCommand( pProjectile->pAnimation, INACTIVATE_COMMAND, 0 );
		return TRUE;
	}

	return FALSE;
}	//	DoFloatCollisionAtPoint


//	return the height at a given point
int GetHeightAtPoint( SPOINT &pt )
{
	int		h, iheight, height;
	ITEM	*pItemList;
	IPOINT	tile;

	tile = IPOINT_FROM_SPOINT(pt);
	height = (ELEVATION(the_map.elevation_layer[tile]) << 2);
	iheight = 0;
	pItemList = GetObjectsIntersectPoint( &pt );
	while( pItemList )
	{
		h = GetItemHeightNoElevation( pItemList );
		if( h > iheight )
			iheight = h;
		pItemList = pItemList->next;
	}
	return height + iheight;
}	//  GetHeightAtPoint


void UpdateProjectile( void )
{
	int		x1, y1, x2, y2;
	float	fi, fc, dx, dy;
	float	pixels=0.0;
	SPOINT	point;
	BOOL	hit;
	int		height, z;
	ITEM    *pHitItem;

	dwDeltaTime = gpGame->dwDeltaTime;
	hit = FALSE;

	// calculate intersection points & update projectile location
	pShadowAnim = pShadow->pAnimation;
	pProjectileAnim = pProjectile->pAnimation;

	ASSERT( pShadowAnim != NULL );
	ASSERT( pProjectileAnim != NULL );

	if( !(pShadowAnim->velocity && dwDeltaTime) )
		return;

	if( ITEM_CLASS(pProjectile) == ARMY_MISSILE_FLOAT )
	{
		DoExplosion( pProjectileAnim->world_pos.x, pProjectileAnim->world_pos.y - pProjectileAnim->world_z, 
					 EXPLOSION_GUN_PUFF_M_COMMAND, &SmallExplosion, 
					 DMGTYPE_OTHER_EXPLOSION, 0, NULL, 0, 0, SND_NULL_SND_ID ); 
	}

	pixels = ( (float)pShadowAnim->velocity * (float)dwDeltaTime ) / 1000;

	switch( pProjectile->weaponType )
	{
	case ARMY_LIGHT_MACHINE_GUN:
	case ARMY_AUTORIFLE:
	case ARMY_RIFLE:
		if( pProjectileAnim->world_z > 0 )
		{
			if( pProjectile->total_distance + pixels > AUTO_HIT_ZONE )
			{
				pProjectileAnim->dz = (pProjectileAnim->world_z - pProjectile->dest_height) *
					(float)(pProjectile->total_distance) / (float)pProjectile->max_distance;
			}
		}
		height = (int)(pProjectileAnim->world_z - pProjectileAnim->dz);
		break;
	case ARMY_BAZOOKA:
		if( pProjectileAnim->world_z > 0 )
		{
			pProjectileAnim->dz = (pProjectileAnim->world_z - pProjectile->dest_height) *
				(float)(pProjectile->total_distance) / (float)pProjectile->max_distance;
		}
		height = (int)(pProjectileAnim->world_z - pProjectileAnim->dz);
		break;
	default:
		height = pProjectileAnim->world_z;
		break;
	}

	if( pProjectileAnim->z_velocity && dwDeltaTime )	
	{									// this is for lobbing missiles (mortar/grenade)
		float	z;
		long	dz;
										// calculate new world_z / dz
		z = ((float)pProjectileAnim->z_velocity * (float)dwDeltaTime) / 1000;
		pProjectileAnim->dz += z;
		dz = (long)pProjectileAnim->dz;
		pProjectileAnim->dz -= dz;
		pProjectileAnim->world_z += (short)dz;
										// check if it hits the ground
		if( pProjectileAnim->world_z <= 0 )
		{
			pProjectileAnim->world_z = 0;
			pProjectileAnim->z_velocity = 0;
//			ProjectileExplode( pProjectile, x1, y1, 0, NULL );
//			hit = TRUE;
//			goto killfloat;
		}
		else							// apply force of gravity
		{
			pProjectileAnim->z_velocity -= (short)((force_of_gravity * dwDeltaTime) / 1000);
			if( pProjectileAnim->z_velocity == 0 )			// don't let it be 0!
				pProjectileAnim->z_velocity = -1;
		}
		height = pProjectileAnim->world_z;
	}
	else if( pProjectileAnim->world_z > 0 )				// line-of-sight weapons
	{
		pProjectile->total_distance += (long)pixels;
		height = (int)(pProjectileAnim->world_z - pProjectileAnim->dz);
	}

	x1 = pShadowAnim->world_pos.x;				// x1, y1 is original point
	y1 = pShadowAnim->world_pos.y;
	pShadowAnim->dx += (float)cos_table[pShadowAnim->facing] * pixels;
	pShadowAnim->dy += (float)sin_table[pShadowAnim->facing] * pixels;

	int sx, sy;
	sx = (int)pShadowAnim->dx;
	sy = (int)pShadowAnim->dy;
	pShadowAnim->x_velocity = (short)sx;
	pShadowAnim->y_velocity = (short)sy;
	pShadowAnim->dx -= sx;
	pShadowAnim->dy -= sy;

	x2 = x1 + (short)sx;
	y2 = y1 + (short)sy;

	point.x = x2;
	point.y = y2;
	if( !InRect( &the_map.boundrect, &point ) )
	{
		if( !InRect( &the_map.limitboundrect, &point ) )
		{
			hit = TRUE;
			ProjectileExplode( pProjectile, pProjectile->common.position.x, pProjectile->common.position.y, height, NULL );
			goto killfloat;
		}
		if( pShadowAnim->velocity > 0 )
		{
			switch( pProjectile->weaponType )
			{
			case ARMY_MORTAR:
			case ARMY_GRENADE:
				pShadowAnim->velocity = 25;
			}
		}
	}
	point.y = y2 - height;
	if( point.y <= the_map.limitboundrect.top )
	{
		pProjectileAnim->world_z = y2-the_map.limitboundrect.top-1;
	}

	dx = (float)sx;
	dy = (float)sy;
	if( ITEM_CLASS(pProjectile) == ARMY_MISSILE_FLOAT )
		z = - pProjectileAnim->world_z;
	else
		z = 0;

	if( fabs(dx) >= fabs(dy) )
	{													// greater dx
		fi = (float)dy/(float)(fabs(dx)) * (float)FLOAT_STEP;
		fc = (float)y1;
		if( dx > 0 )
		{												// x1 < x2
			while( x1 < x2 )
			{
				x1 += FLOAT_STEP;
				if( x1 >= x2 )
				{
					x1 = x2;
					y1 = y2;
				}
				else
				{
					fc += fi;
					y1 = (int)fc;
				}

				point.x = x1;
				point.y = y1+z;
				if( DoFloatCollisionAtPoint( point, &pHitItem ) )
				{
					ProjectileExplode( pShadow, x1, y1, height, pHitItem );
					hit = TRUE;
					goto stopfloat;
				}
			}
		}
		else if( dx < 0 )
		{
			while( x1 > x2 )
			{
				x1 -= FLOAT_STEP;
				if( x1 <= x2 )
				{
					x1 = x2;
					y1 = y2;
				}
				else
				{
					fc += fi;
					y1 = (int)fc;
				}

				point.x = x1;
				point.y = y1+z;
				if( DoFloatCollisionAtPoint( point, &pHitItem ) )
				{
					ProjectileExplode( pShadow, x1, y1, height, pHitItem );
					hit = TRUE;
					goto stopfloat;
				}
			}
		}	
	}
	else
	{													// greater dy
		fi = (float)dx/(float)(fabs(dy)) * (float)FLOAT_STEP;
		fc = (float)x1;
		if( dy > 0 )
		{
			while( y1 < y2 )
			{
				y1 += FLOAT_STEP;
				if( y1 >= y2 )
				{
					x1 = x2;
					y1 = y2;
				}
				else
				{
					fc += fi;
					x1 = (int)fc;
				}

				point.x = x1;
				point.y = y1+z;
				if( DoFloatCollisionAtPoint( point, &pHitItem ) )
				{
					ProjectileExplode( pShadow, x1, y1, height, pHitItem );
					hit = TRUE;
					goto stopfloat;
				}
			}
		}
		else if( dy < 0 )
		{
			while( y1 > y2 )
			{
				y1 -= FLOAT_STEP;
				if( y1 <= y2 )
				{
					x1 = x2;
					y1 = y2;
				}
				else
				{
					fc += fi;
					x1 = (int)fc;
				}

				point.x = x1;
				point.y = y1+z;
				if( DoFloatCollisionAtPoint( point, &pHitItem ) )
				{
					ProjectileExplode( pShadow, x1, y1, height, pHitItem );
					hit = TRUE;
					goto stopfloat;
				}
			}
		}
	}
stopfloat:

	AnimUpdate( pShadowAnim );
	AnimUpdate( pProjectileAnim );

	pShadowAnim->pixels = (short)pixels;
	pProjectileAnim->pixels = (short)pixels;

	pShadowAnim->world_pos.x = x2;
	pShadowAnim->world_pos.y = y2;
	pProjectileAnim->world_pos = pShadowAnim->world_pos;

	switch( ITEM_CLASS(pProjectile) )
	{
	case ARMY_MISSILE_FLOAT:
	case ARMY_MORTAR_FLOAT:
		pShadowAnim->world_z = GetHeightAtPoint( pShadowAnim->world_pos );
	}

	if( fabs(pShadowAnim->dx) < 0.001 )
		pShadowAnim->dx = 0.0;
	if( fabs(pShadowAnim->dy) < 0.001 )
		pShadowAnim->dy = 0.0;

//	AnimWorldBoundary( pShadowAnim );
//	AnimWorldBoundary( pProjectileAnim );

	pProjectile->common.oldPosition = pProjectile->common.position;			// maintain old position
	pProjectile->common.position = pProjectileAnim->world_pos;				// set current position
	pProjectile->common.facing  = pProjectileAnim->facing;
	pShadow->common.oldPosition = pShadow->common.position;			// maintain old position
	pShadow->common.position = pShadowAnim->world_pos;				// set current position
	pShadow->common.facing  = pShadowAnim->facing;
	pShadow->total_distance += (long)pixels;

killfloat:
	int truemaxdistance;
	
	truemaxdistance = WeaponMaxRange(pProjectile->weaponType);

	if( hit || (pShadow->total_distance > truemaxdistance) || (pShadowAnim->velocity == 0 && pProjectileAnim->z_velocity == 0) )
	{
		if( !hit )
			ProjectileExplode( pProjectile, pProjectile->common.position.x, pProjectile->common.position.y, height, NULL );
		AnimForceCommand(pShadowAnim, INACTIVATE_COMMAND, pShadowAnim->facing );
		AnimForceCommand(pProjectileAnim, INACTIVATE_COMMAND, pProjectileAnim->facing );
		sndHalt( pProjectile->sndID );
	}

	MoveDispXObject( (ANIMCELL *)pShadowAnim, FALSE );
	MoveDispXObject( (ANIMCELL *)pProjectileAnim, FALSE );
}


int DoFlameCollision( SPOINT &pt, int height )
{
	ITEM	*pItem;
	int		nDamage, eDamageType;
	ANIM	*pProjectileAnim;
	int		bHit;

//	DisplayDot( point.x, point.y );

	pProjectileAnim = pProjectile->pAnimation;

	if( pProjectileAnim->frame_time < 32 )
		return 0;

	bHit = 0;
	pProjectileAnim->frame_time -= 32;

	ASSERT( pProjectileAnim != NULL );
	
	nDamage = AIinfo.weaponTables[pProjectile->weaponType].damage.nDamage;
	eDamageType = WEAPON_DAMAGE_TYPE[ pProjectile->weaponType];
	pItem = GetObjectsIntersectPoint( &pt );
	while( pItem )
	{
		if( StopsMissile( pItem, pProjectile, 0, 0 ) )
		{
			if( DoDamage )
				ItemDamage( pItem, nDamage, eDamageType, &pt, pProjectile->fromUID );

			switch( ITEM_TYPE(pItem) )
			{
			case ARMY_VEHICLE:
				if( GetItemHeight(pItem) >= height )
					bHit = 1;
				break;
			case ARMY_ASSET:
			case ARMY_STRUCTURE:
			case ARMY_OBSTACLE:
			case ARMY_HUSK:
				if( GetItemHeight(pItem) >= height )
					bHit = 1;
				break;
			}
		}
		pItem = pItem->next;
	}
	if( height < (ELEVATION(the_map.elevation_layer[IPOINT_FROM_SPOINT(pt)]) << 2) )
		bHit = 1;
	return bHit;
}	//	DoFlameCollision



int flame_trailerdist = 48;


void UpdateFlameBurst( void )
{
	ANIM	*pProjectileAnim;
	float	pixels, dx, dy;
	int		bHit;
	SPOINT pt;

	dwDeltaTime = gpGame->dwDeltaTime;
	bHit = 0;

	// calculate intersection points & update projectile location
	pProjectileAnim = pProjectile->pAnimation;

	ASSERT( pProjectileAnim != NULL );

	if( !(pProjectileAnim->velocity && dwDeltaTime) )
		return;

	pProjectileAnim->last_frame_time += (short)gpGame->dwDeltaTime;
	pProjectileAnim->frame_time += (short)gpGame->dwDeltaTime;

/*
	if( pProjectileAnim->frame_time > 60 )
	{
		DropFlamePoop( pProjectileAnim->world_pos.x, pProjectileAnim->world_pos.y, pProjectileAnim->current_frame );
		pProjectileAnim->frame_time = 0;
	}
*/

	if( pProjectileAnim->last_frame_time > FlameBurstData.timing[pProjectileAnim->current_frame] )
	{
		pProjectileAnim->last_frame_time -= FlameBurstData.timing[pProjectileAnim->current_frame];
		pProjectileAnim->current_frame++;
		if( pProjectileAnim->current_frame >= FlameBurstData.num_frames )
		{
			pProjectileAnim->flags &= !ANIM_FLAG_ACTIVE;
			goto movedispx;
		}
		pProjectileAnim->velocity += FlameBurstData.velocity[pProjectileAnim->current_frame];
		pProjectileAnim->pSprite = 
			FlameBurstData.sprites[ pProjectileAnim->facing_index * FlameBurstData.num_frames +
				pProjectileAnim->current_frame];
	}

	pixels = ( (float)pProjectileAnim->velocity * (float)dwDeltaTime ) / 1000;
	pProjectileAnim->dx += (float)cos_table[pProjectileAnim->facing] * pixels;
	dx = (float)((long)pProjectileAnim->dx);
	pProjectileAnim->dx -= dx;
	pProjectileAnim->dy += (float)sin_table[pProjectileAnim->facing] * pixels;
	dy = (float)((long)pProjectileAnim->dy);
	pProjectileAnim->dy -= dy;

	pt.x = pProjectileAnim->world_pos.x + (short)dx;
	pt.y = pProjectileAnim->world_pos.y + (short)dy;
	if( !InRect( &the_map.limitboundrect, &pt ) )
	{
		pProjectileAnim->flags &= !ANIM_FLAG_ACTIVE;
		goto movedispx;
	}

	pProjectileAnim->world_pos.x = pt.x;
	pProjectileAnim->world_pos.y = pt.y;
	pProjectileAnim->x_velocity = (short)dx;
	pProjectileAnim->y_velocity = (short)dy;
	pProjectileAnim->pixels = (short)pixels;

	pProjectile->common.oldPosition = pProjectile->common.position;			// maintain old position
	pProjectile->common.position = pProjectileAnim->world_pos;				// set current position
	pProjectile->common.facing  = pProjectileAnim->facing;
	pProjectile->total_distance += (long)pixels;

	int			ldx, ldy;
	int			dist, tdist;

	if( pProjectile->link_missile >= 0 )
	{
		FLOAT_OBJ   *pLinkMissile;
		ANIM	    *pLinkAnim;

		pLinkMissile = &(pLegion->Projectiles[pProjectile->link_missile]);
		pLinkAnim = pLinkMissile->pAnimation;
		if( pLinkAnim->flags & ANIM_FLAG_ACTIVE )
		{
			ldx = pLinkAnim->world_pos.x - pProjectileAnim->world_pos.x;
			ldy = pLinkAnim->world_pos.y - pProjectileAnim->world_pos.y;
			dist = ldx * ldx + ldy * ldy;
		}
		else
		{
			tdist = __min( pProjectile->total_distance, flame_trailerdist );
			ldx = -(int)((float)cos_table[pProjectileAnim->facing] * tdist );
			ldy = -(int)((float)sin_table[pProjectileAnim->facing] * tdist );
			dist = tdist * tdist;
		}
	}
	else if( pProjectile->total_distance > 10 )
	{
		tdist = __min( pProjectile->total_distance, flame_trailerdist );
		ldx = -(int)((float)cos_table[pProjectileAnim->facing] * tdist );
		ldy = -(int)((float)sin_table[pProjectileAnim->facing] * tdist );
		dist = tdist * tdist;
	}
	else
		dist = 0;

	if( dist > 25 )
	{
		if( dist < 100 )
		{
			pt.x = pProjectileAnim->world_pos.x + (ldx >> 1);
			pt.y = pProjectileAnim->world_pos.y + (ldy >> 1);
			DropFlamePoop( pt.x, pt.y, pProjectileAnim->facing_index, pProjectileAnim->current_frame );
			bHit += DoFlameCollision( pt, pProjectile->dest_height );
		}
		else if( dist < 400 )
		{
			ldx = ldx >> 2;
			ldy = ldy >> 2;
			pt.x = pProjectileAnim->world_pos.x + ldx;
			pt.y = pProjectileAnim->world_pos.y + ldy;
			DropFlamePoop( pt.x, pt.y, pProjectileAnim->facing_index, pProjectileAnim->current_frame );
			bHit += DoFlameCollision( pt, pProjectile->dest_height );

			pt.x = pProjectileAnim->world_pos.x + (ldx << 1);
			pt.y = pProjectileAnim->world_pos.y + (ldy << 1);
			DropFlamePoop( pt.x, pt.y, pProjectileAnim->facing_index, pProjectileAnim->current_frame );
			bHit += DoFlameCollision( pt, pProjectile->dest_height );
		}
		else
		{
			pt.x = pProjectileAnim->world_pos.x + (ldx >> 2);
			pt.y = pProjectileAnim->world_pos.y + (ldy >> 2);
			DropFlamePoop( pt.x, pt.y, pProjectileAnim->facing_index, pProjectileAnim->current_frame );
			bHit += DoFlameCollision( pt, pProjectile->dest_height );

			pt.x = pProjectileAnim->world_pos.x + (ldx >> 1);
			pt.y = pProjectileAnim->world_pos.y + (ldy >> 1);
			DropFlamePoop( pt.x, pt.y, pProjectileAnim->facing_index, pProjectileAnim->current_frame );
			bHit += DoFlameCollision( pt, pProjectile->dest_height );

			pt.x = pProjectileAnim->world_pos.x + ldx - (ldx >> 2);
			pt.y = pProjectileAnim->world_pos.y + ldy - (ldy >> 2);
			DropFlamePoop( pt.x, pt.y, pProjectileAnim->facing_index, pProjectileAnim->current_frame );
		}
	}

	bHit += DoFlameCollision( pProjectileAnim->world_pos, pProjectile->dest_height );
	if( bHit )
	{
		if( pProjectile->total_distance < pProjectile->max_distance - 16 )
		{
			pProjectile->total_distance = pProjectile->max_distance - 16;
			pProjectileAnim->current_frame = FlameBurstData.num_frames-3;
			pProjectileAnim->velocity = 30;
			pProjectileAnim->last_frame_time = 0;
			pProjectileAnim->pSprite = 
				FlameBurstData.sprites[ pProjectileAnim->facing_index * FlameBurstData.num_frames +
					pProjectileAnim->current_frame];
		}
	}

	if( pProjectile->total_distance > pProjectile->max_distance )
	{
		pProjectileAnim->flags &= !ANIM_FLAG_ACTIVE;
	}

movedispx:
	MoveDispXObject( (ANIMCELL *)pProjectileAnim, FALSE );
}


void UpdateArmyProjectiles( int enumArmy )
{
	int		i;

	eArmy = enumArmy;
	DoDamage = IS_LOCAL_ARMY(eArmy);  // only missiles run locally cause damamge

//	InitBackBufferLockComplex();
//	DDCOLOR = YELLOW_IDX;
	pLegion = &(Armies[enumArmy].Legion);
	for( i = 0; i < ARMY_LEGION_MISSILES; i++ )
	{
		pProjectile = &(pLegion->Projectiles[i]);
		if( !(pProjectile->pAnimation->flags & ANIM_FLAG_ACTIVE) )
			continue;
		if( ITEM_CLASS(pProjectile) == ARMY_FLAME_FLOAT )
		{
			pShadow = NULL;
			UpdateFlameBurst();
		}
		else
		{
			pShadow = &(pLegion->Shadows[i]);			
			UpdateProjectile();
		}
	}
//	FreeBackBufferLockComplex();
}

void SetFloatSnd(FLOAT_OBJ *pMissile, ULONG sndID)
{
	pMissile->sndID = sndID;;
}

///========================================================================
//								EOF
///========================================================================
