//========================================================================
//	FILE:			$Workfile: Weapon.cpp $
//
//	DESCRIPTION:	Army Troop processing.
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		July 25, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Weapon.cpp 136   4/18/98 12:16p Bwilcox $
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
//  $Log: /ArmyMen/src/Weapon.cpp $
//  
//  136   4/18/98 12:16p Bwilcox
//  weapon charges must come from undeployed ones
//  
//  135   4/17/98 11:21p Bwilcox
//  mines and explosives look for the TRIGGER_UNDEPLOYED flag to find an
//  unused charge. This is no longer a destroyed field from scripts
//  
//  134   4/16/98 12:06p Bwilcox
//  fixed explosives bug like mine bug
//  
//  133   4/15/98 12:28p Bwilcox
//  
//  132   4/15/98 12:25p Bwilcox
//  
//  131   4/15/98 12:24p Bwilcox
//  changed how mines detect they've been allocated
//  
//  130   4/12/98 4:17p Bwilcox
//  removed debugging trace from weapons
//  
//  129   4/12/98 1:18p Phu
//  
//  128   4/09/98 11:37p Bwilcox
//  
//  126   4/03/98 11:00a Bwilcox
//  
//  125   4/03/98 10:59a Bwilcox
//  mine gets tile also
//  
//  124   4/02/98 6:29p Phu
//  typecast to avoid warnings
//  
//  123   4/02/98 5:35p Nrobinso
//  change tower gun to medium machine gun
//  
//  122   4/01/98 6:48p Dmaynard
//  Fix for Mines in Multi-Player
//  
//  121   4/01/98 1:53p Bwilcox
//  change local test
//  
//  120   4/01/98 12:19p Nrobinso
//  fix freeweapon so it releases asset weapons
//  
//  119   3/30/98 10:11p Nrobinso
//  switch to animtime, which allows for pauses
//  
//  118   3/27/98 4:29p Phu
//  Mortar Burst
//  
//  117   3/27/98 3:29p Phu
//  mortar blasts
//  
//  116   3/24/98 4:52p Bwilcox
//  fixing mine routeplanner darta
//  
//  115   3/24/98 4:31p Bwilcox
//  center mines in tiles
//  
//  114   3/24/98 4:13p Bwilcox
//  
//  113   3/24/98 4:09p Bwilcox
//  mp sarge remote will not fire a mine.
//  
//  112   3/24/98 2:41p Bwilcox
//  trace on mine placement
//  
//  111   3/20/98 11:37a Bwilcox
//  fixing troopers dist values when firing grenades and mortars
//  
//  110   3/18/98 4:16p Phu
//  stop flames when they hit
//  
//  109   3/18/98 11:07a Nrobinso
//  a weapon starts ready to fire
//  
//  108   3/14/98 3:13p Nrobinso
//  placed mines are marked changed so they will be saved
//  
//  107   98-03-13 21:50 Dmaynard
//  make sure mines are made visble/invisble properly
//  
//  106   3/12/98 4:32p Phu
//  no weapon for convoy
//  
//  105   3/08/98 5:42p Phu
//  set tile for script-placed/moved objects so removeobject works (gets
//  rid of remnant explosives).
//  
//  104   3/05/98 6:46p Phu
//  move flame thrower back to appropriate place
//  
//  103   3/05/98 4:48p Nrobinso
//  add realweapon lag for firing purposes
//  
//  102   2/27/98 7:08p Nrobinso
//  remove audio load
//  
//  101   2/27/98 12:58p Nrobinso
//  improve sfx playing
//  
//  100   2/20/98 1:19p Nrobinso
//  fix up sounds
//  
//  99    2/17/98 9:04p Nrobinso
//  weapon sounds
//  
//  98    2/17/98 9:01a Aburgess
//  vehicles and weapons now use the new audioPlay interface
//  
//  97    2/16/98 12:03p Phu
//  pass along fromUID with explosions
//  
//  96    2/13/98 7:02p Nrobinso
//  remove unused code
//  
//  95    2/12/98 6:32p Phu
//  reduce damage done by stuff for crying out loud!
//  
//  94    2/12/98 12:53p Nrobinso
//  new sounds
//  
//  93    2/10/98 5:05p Bwilcox
//  fixing mine ownership I broke
//  
//  92    2/10/98 3:58p Dmaynard
//  Added call to ObjectPlaceMessageSend for Mines
//  
//  91    2/10/98 11:34a Bwilcox
//  mines are placed by net message object_place, not by local firing.
//  objectdamage now takes spoint instead of spoint *
//  dead field removed from objectmessage
//  
//  90    2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  89    2/04/98 2:49p Phu
//  
//  88    2/04/98 2:13p Phu
//  
//  87    2/04/98 1:38p Phu
//  
//  86    2/04/98 11:48a Phu
//  lure item
//  
//  85    2/02/98 6:39p Bwilcox
//  mine removal over the net
//  
//  84    2/02/98 5:57p Bwilcox
//  allah sees mine placement
//  
//  83    2/02/98 4:20p Nrobinso
//  default ammo to 3 if none is set
//  
//  82    2/02/98 10:44a Phu
//  increase initial z for mortars/grenades
//  
//  81    1/30/98 4:20p Nrobinso
//  remove commented out line
//  
//  80    1/29/98 3:17p Nrobinso
//  no muzzle flash for sweeper
//  
//  79    1/25/98 3:21a Bwilcox
//  static placemine
//  
//  78    98/01/22 11:53 Dmaynard
//  set tile for mines
//  
//  77    1/22/98 10:02a Bwilcox
//  fixing ordering problem with mine stepping on
//  
//  76    1/22/98 9:53a Bwilcox
//  fixed bug in unplace mine
//  
//  75    1/21/98 1:52p Phu
//  check in for bruce - mine removal function
//  
//  74    1/20/98 12:28a Nrobinso
//  make sure RIFLE has infinite ammo
//  
//  73    1/19/98 3:26p Phu
//  fixed isweaponready function
//  
//  72    1/08/98 4:19p Phu
//  air support items/paratrooper initialization
//  
//  71    1/05/98 11:56a Phu
//  Remove #s from flags
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"

#include "aiaccess.h"
#include "anim.h"
#include "audio.h"
#include "Army.h"
#include "comm.h"
#include "explosions.h"
#include "Disp.h"
#include "Damage.h"
#include "gameflow.h"
#include "item.h"
#include "weapon.h"
#include "map.h"
#include "wobject.h"
#include "objectmsg.h"
#include "aibtank.h"


extern int AdditionalParatroopers;

///------------------------------------------------------------------------
//	Weapon (Audio) Fire Tables
WEAPONSND	WeaponSndTable[ ARMY_LAST_WEAPON ] =
{
	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_NO_WEAPON,
	{ LIGHT_MG, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_LIGHT_MACHINE_GUN,	

	{ GRENADE, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_GRENADE,             
	{ FLAME_BEGIN, SND_NULL_SND_ID, SND_NULL_SND_ID },	// ARMY_FLAME_THROWER,       
	{ BAZOOKA, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_BAZOOKA,             
	{ MORTAR, MORTAR_WHISTLE, SND_NULL_SND_ID },		// ARMY_MORTAR,              

	{ CANNON, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_LARGE_CANNON,	    
	{ MEDIUM_MG, SND_NULL_SND_ID, SND_NULL_SND_ID },	// ARMY_MEDIUM_MACHINE_GUN,	
	{ HEAVY_MG, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_HEAVY_MACHINE_GUN,	

	{ RIFLE, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_RIFLE,               
	{ RIFLE, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_AUTORIFLE,           

	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_MINE,                
	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_EXPLOSIVE_WEAPON,    
	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_DETONATOR,           

	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_LURE,                

	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_FLAG,                
	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_GREENFLAG,           
	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_TANFLAG,             
	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_BLUEFLAG,            
	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_GRAYFLAG,            

	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_SWEEPER,	            

	{ MEDIUM_MG, SND_NULL_SND_ID, SND_NULL_SND_ID },			// ARMY_GUARD_TOWER_RIFLE,	

	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID },		// ARMY_MEDKIT,				
	{ SND_NULL_SND_ID, SND_NULL_SND_ID, SND_NULL_SND_ID }		// ARMY_MEDPACK,				

};

static void PlaceMineCharge( WEAPON *pWeapon, SPOINT position,int eArmy);


///------------------------------------------------------------------------
//	Damage Tables

EXPLOSION_DATA BulletPuff=
{	TRUE, 	EXPLOSION_GUN_SPARK_M_COMMAND, NULL, SND_NULL_SND_ID};

EXPLOSION_DATA BazookaExplode=
{	TRUE, EXPLOSION_FLASH_COMBUSTION_S_COMMAND, &MediumExplosion, BAZOOKA_EXPLODE };

EXPLOSION_DATA GrenadeExplode=
{	TRUE, EXPLOSION_FLASH_COMBUSTION_M_COMMAND, &LargeExplosion, GRENADE_EXPLODE };

EXPLOSION_DATA MortarExplode=
{	TRUE, EXPLOSION_FLASH_COMBUSTION_M_COMMAND, &LargeExplosion, MORTAR_EXPLODE };


int MORTAR_RADIUS = 31;			// must be power of two -1!!!


void DoWeaponExplosion(ITEM *pItem, int damagetodo, int damagetype, SPOINT *damageloc, EXPLOSION_DATA *pExplode, UID fromUID )
{
	switch( damagetype )
	{
		case DMGTYPE_GRENADE:
			if (!pExplode)
				pExplode = &GrenadeExplode;
			break;
		case DMGTYPE_MORTAR:
			if (!pExplode)
				pExplode = &MortarExplode;
			break;
		case DMGTYPE_BULLET:
			if (!pExplode)	{
				pExplode = &BulletPuff;
				damagetodo = 0;
			}
			break;
		case DMGTYPE_OTHER_EXPLOSION:
			damagetodo = damagetodo >> 1;
			break;
		case DMGTYPE_BAZOOKA:
		case DMGTYPE_MISSILE:
			if (!pExplode)
				pExplode = &BazookaExplode;
			damagetodo = damagetodo >> 1;
			break;
	}

	if (pExplode)
		if (pExplode->bExplode)
			DoExplosion(damageloc->x, damageloc->y, 
					pExplode->eExplosion, pExplode->pPattern,
					damagetype|DMGTYPE_EXPLOSION, damagetodo, pItem, TRUE, fromUID, pExplode->audioID );
	if( damagetype == DMGTYPE_MORTAR )
	{
		int	i, x, y;

		for( i = 0; i < 4; i++ )
		{
			x = ((rand() & MORTAR_RADIUS) << 1) - MORTAR_RADIUS;
			y = ((rand() & MORTAR_RADIUS) << 1) - MORTAR_RADIUS;
			DoDelayedExplosion( damageloc->x + x, damageloc->y + y,
				EXPLOSION_COMBUSTION_S_COMMAND, NULL,
				DMGTYPE_OTHER_EXPLOSION, 0, NULL, TRUE,
				rand() & 7, fromUID, GRENADE_EXPLODE );
		}
		for( i = 0; i < 3; i++ )
		{
			x = (rand() & MORTAR_RADIUS) + (rand() & MORTAR_RADIUS) - MORTAR_RADIUS;
			y = (rand() & MORTAR_RADIUS) + (rand() & MORTAR_RADIUS) - MORTAR_RADIUS;
			DoDelayedExplosion( damageloc->x + x, damageloc->y + y,
				EXPLOSION_FLASH_SMOKE_M_COMMAND, NULL,
				DMGTYPE_OTHER_EXPLOSION, 0, NULL, TRUE,
				rand() & 7 + 7, fromUID, SND_NULL_SND_ID );
		}
	}
}


///========================================================================
//	Function:		WeaponMinRange
//	Description:	you cant fire at less than this range
///========================================================================

int	WeaponMinRange(WEAPON_TYPE eWeapon)
{
      AI_WTBL*	pWeaponDesc = &(AIinfo.weaponTables[ eWeapon ]);
      int minRange = pWeaponDesc->range.nMinRange;
      return minRange;
}

///========================================================================
//	Function:		WeaponMaxRange
//	Description:	max distance of weapon at sealevel
///========================================================================

int	WeaponMaxRange(WEAPON_TYPE eWeapon)
{
      AI_WTBL*	pWeaponDesc = &(AIinfo.weaponTables[ eWeapon ]);
      int maxRange = pWeaponDesc->range.nMaxRange;
      return maxRange;
}


///========================================================================
//	Function:		FireWeapon
//	Description:	fire any weapon, calculating distance to target (if there is one)
//					varying distance and direction a touch
//					start off a projectile, or just do the damage if a target
///========================================================================

void FireWeapon(ARMY_TYPE eArmy, WEAPON* pWeapon, SPOINT* pFrom, int z, int direction, int distance, int height, UID fromUID )
{
	int		flashtype = EFT_RifleFlash;
	FLOAT_OBJ	*pMissile = NULL;

	// fire the weapon
	switch(pWeapon->eWeapon)
	{
		case ARMY_GRENADE:

			pMissile = ProjectileSet(eArmy, pWeapon, pFrom->x, pFrom->y, z + 4, direction, distance, height, NULL, fromUID );
			break;

		case ARMY_MORTAR:
			DoExplosion( pFrom->x, pFrom->y, 
						 EXPLOSION_GUN_PUFF_M_COMMAND, &SmallExplosion, 
						 DMGTYPE_OTHER_EXPLOSION, 0, NULL, 0, 0, SND_NULL_SND_ID ); 
			pMissile = ProjectileSet(eArmy, pWeapon, pFrom->x, pFrom->y, z + 6, direction, distance, height, NULL, fromUID );
			break;

		case ARMY_BAZOOKA:
			DoExplosion( pFrom->x, pFrom->y, 
						 EXPLOSION_GUN_PUFF_M_COMMAND, &SmallExplosion, 
						 DMGTYPE_OTHER_EXPLOSION, 0, NULL, 0, 0, SND_NULL_SND_ID ); 
			pMissile = ProjectileSet(eArmy, pWeapon, pFrom->x, pFrom->y, z, direction, distance, height, NULL, fromUID );
			break;

		case ARMY_LARGE_CANNON:
			MakeMuzzleFlash( pFrom->x, pFrom->y, direction, EFT_TankFlash, fromUID );
			pMissile = ProjectileSet(eArmy, pWeapon, pFrom->x, pFrom->y, z, direction, distance, height, NULL, fromUID);
			break;

		case ARMY_LIGHT_MACHINE_GUN:
		case ARMY_AUTORIFLE:
		case ARMY_RIFLE:
			MakeMuzzleFlash( pFrom->x, pFrom->y, direction, EFT_RifleFlash, fromUID );
			pMissile = ProjectileSet(eArmy, pWeapon, pFrom->x, pFrom->y, z, direction, distance, height, NULL, fromUID );
			break;

		case ARMY_GUARD_TOWER_RIFLE:
			MakeMuzzleFlash( pFrom->x, pFrom->y, direction, EFT_RifleFlash, fromUID );
			pMissile = ProjectileSet(eArmy, pWeapon, pFrom->x, pFrom->y, z, direction, distance, height, NULL, fromUID );
			break;

		case ARMY_FLAME_THROWER:
			MakeFlameBurst( eArmy, pWeapon, pFrom->x, pFrom->y, direction, distance, height, fromUID);
			break;

		case ARMY_MEDIUM_MACHINE_GUN:
			flashtype = EFT_JeepFlash;
			MakeMuzzleFlash( pFrom->x, pFrom->y, direction, flashtype, fromUID );
			pMissile = ProjectileSet(eArmy, pWeapon, pFrom->x, pFrom->y, z, direction, distance, height, NULL, fromUID );
			break;

		case ARMY_HEAVY_MACHINE_GUN:
			flashtype = EFT_HalfFlash;
			MakeMuzzleFlash( pFrom->x, pFrom->y, direction, flashtype, fromUID );
			pMissile = ProjectileSet(eArmy, pWeapon, pFrom->x, pFrom->y, z, direction, distance, height, NULL, fromUID );
			break;

		case ARMY_EXPLOSIVE_WEAPON:
			PlaceExplosiveCharge( pWeapon, pFrom->x, pFrom->y );
			break;

		case ARMY_MINE:
			// ignore sarges not your own. must be Multiplayer and mines are placed via host message
			if (!IS_LOCAL_ARMY(EXTRACT_ARMY(fromUID))) return; 
			PlaceMineCharge( pWeapon, *pFrom,eArmy );
			break;

		case ARMY_SWEEPER:
			break;

		default: // all machine guns
			break;
	}

	// sound effect
	AudioPlayItem(WeaponSndTable[pWeapon->eWeapon].nFireAudio, pWeapon->pOwner);

	if (WeaponSndTable[pWeapon->eWeapon].nContinueAudio != SND_NULL_SND_ID)	{
		ULONG sndID = AudioPlayItem(WeaponSndTable[pWeapon->eWeapon].nContinueAudio, pWeapon->pOwner);
		SetFloatSnd(pMissile, sndID);
	}
}


///========================================================================
//	Function:		SetFireWeapon
//	Description:	calculate distance to target (if there is one)
//					vary distance and direction a touch
///========================================================================
#define DIRECTION_ERROR 8
extern int mortar_minz,grenade_minz;
SET_WEAPON SetFireWeapon(WEAPON* pWeapon, SPOINT* pFrom, int direction, ITEM* pTarget)
{
	int distance;
	int nDamage =  pWeapon->nDamage;
	int eDamageType = pWeapon->eDamageType;
	SET_WEAPON set_weapon;

	WEAPON_TYPE eWeapon = pWeapon->eWeapon;

	// sarge always fires at max range
	distance = WeaponMaxRange(eWeapon);
	if (pTarget)	{
		distance = min(GetDistance(pFrom, &pTarget->position), distance);		// already an up to 12% error
		// mortars need to scale distance above min range
		if( eWeapon == ARMY_MORTAR || eWeapon == ARMY_GRENADE )
		{
			if( distance < WeaponMinRange(eWeapon) )
				distance = WeaponMinRange(eWeapon);
			else
			if( distance > WeaponMaxRange(eWeapon) )
				distance = WeaponMaxRange(eWeapon);
			pWeapon->percentDistance = (int)((float)(distance - WeaponMinRange(eWeapon))/
				(float)(WeaponMaxRange(eWeapon)-WeaponMinRange(eWeapon))*100.0);
			distance = WeaponMaxRange(eWeapon);
		}
		direction = NormalizeFacing(direction);
	}

	distance = (distance * pWeapon->percentDistance)/100;
	set_weapon.distance = distance;
	set_weapon.direction = direction;

	return set_weapon;
}

void WeaponDistancePercentage(WEAPON* pWeapon, char percent)	{
	pWeapon->percentDistance = percent;
}

static int chargecount = 0;

void WeaponFireUpdate(WEAPON* pWeapon)
{
	pWeapon->fire_count += gpGame->dwDeltaTime;
}

void WeaponFireReset(WEAPON* pWeapon)
{
	pWeapon->fire_count = 0;
}

inline BOOL WeaponFireTime(WEAPON* pWeapon)
{
	if( !pWeapon )
		return 0;
	return (pWeapon->fire_count >= pWeapon->nFireRate);
}

BOOL WeaponSingleShot(WEAPON* pWeapon)
{
	// call out auto-weapons
	switch(pWeapon->eWeapon)
	{
		case ARMY_LIGHT_MACHINE_GUN:
		case ARMY_MEDIUM_MACHINE_GUN:
		case ARMY_HEAVY_MACHINE_GUN:
		case ARMY_AUTORIFLE:
		case ARMY_FLAME_THROWER:
			return FALSE;
			break;
	}

	return TRUE;
}

//  make weapon
WEAPON* MakeWeapon( WEAPON* pWeapon, WEAPON_TYPE eWeaponType, int maxammo)
{
	if( !pWeapon )
		pWeapon = (struct WEAPONSTRUCT*)malloc( sizeof( struct WEAPONSTRUCT ));
	ASSERT(	pWeapon);

	AI_WTBL*	pWeaponDesc = &(AIinfo.weaponTables[ eWeaponType ]);

	if( maxammo == 0 )
		maxammo = 3;

	pWeapon->bTrueWeapon = FALSE;
	switch( eWeaponType )
	{
		case ARMY_MORTAR:
		case ARMY_GRENADE:
		case ARMY_BAZOOKA:
		case ARMY_MINE:
		case ARMY_EXPLOSIVE_WEAPON:
			pWeapon->bTrueWeapon = TRUE;
			break;

		case ARMY_FLAME_THROWER:
			maxammo *= 6;
			pWeapon->bTrueWeapon = TRUE;
			break;

		case ARMY_SWEEPER:
		case ARMY_RIFLE:
		case ARMY_AUTORIFLE:
			pWeapon->bTrueWeapon = TRUE;
//			break;	// fall thru

		case ARMY_FLAG:
		case ARMY_GREENFLAG:
		case ARMY_TANFLAG:
		case ARMY_BLUEFLAG:
		case ARMY_GRAYFLAG:
		case ARMY_LURE:
		case ARMY_MEDKIT:
			maxammo = -1;
			break;
	}
	if( maxammo > 99 )
		maxammo = 99;

	// now copy in the data
	pWeapon->eWeapon     = eWeaponType;
	pWeapon->nAmmo       = maxammo;
	pWeapon->nMaxAmmo    = maxammo;
	pWeapon->nFireRate   = pWeaponDesc->rateOfFire.nFrameDelay;
	pWeapon->nDamage     = pWeaponDesc->damage.nDamage;
	pWeapon->nVelocity   = pWeaponDesc->velocity.nVelocity;
	pWeapon->nZVelocity  = pWeaponDesc->velocity.nZVelocity;
	pWeapon->eDamageType = WEAPON_DAMAGE_TYPE[eWeaponType];
	pWeapon->charges	 = NULL;
	pWeapon->fire_count  = pWeapon->nFireRate;
	pWeapon->percentDistance = 100;

	int i, n;

	if( (eWeaponType == ARMY_MINE) || (eWeaponType == ARMY_EXPLOSIVE_WEAPON) )
	{
		if (!pWeapon->nAmmo)
		{
			TRACE("WARNING: no ammo set for weapon\n");
			pWeapon->charges = NULL;
			return pWeapon;
		}
		pWeapon->charges = (short *)malloc( pWeapon->nAmmo * sizeof(short) );
		ZeroMemory( pWeapon->charges,  pWeapon->nAmmo * sizeof(short) );

		n = 0;
		for( i = 0; i < the_map.num_objects; i++ )
		{
			if( (the_map.objects[i].category == EXPLOSIVES) && 
				(the_map.objects[i].number == eWeaponType) &&
				(the_map.objects[i].triggers & TRIGGER_UNDEPLOYED) &&
				(the_map.objects[i].common.pWeapon == NULL) )
			{
				pWeapon->charges[n] = i;
				the_map.objects[i].common.pWeapon = pWeapon; // this transient marker is just for init. does not get saved later
				n++;
				if( n>= pWeapon->nAmmo )
					break;
			}
		}
	}
	else if( eWeaponType == ARMY_PARATROOPERS )
	{
		AdditionalParatroopers += maxammo;
	}
    return pWeapon;
}	//	MakeWeapon


void FreeWeapon( OBJECTSTRUCT * pObject )
{
	if( !pObject)
		return;
	if( pObject->category == SPECIAL_ITEMS || pObject->attribute == ARMY_ASSET)
	{
		if( !(pObject->common.pWeapon) )
			return;

		if( pObject->common.pWeapon->charges )
			free( pObject->common.pWeapon->charges );
		free( pObject->common.pWeapon );
		pObject->common.pWeapon = NULL;
	}
}	//	FreeWeapon


void UnplaceMine(OBJECTSTRUCT *pObject)
{
    ObjectRemoveMessageSend(pObject);
    RawUnplaceMine(pObject);
}

void RawUnplaceMine(OBJECTSTRUCT *pObject)
{
    IPOINT tile;
    // note tile before object is removed
    tile = pObject->common.tile;
    if (!tile) return; // incase it has already been removed somehow
    MapRemoveObject(pObject);
	pObject->triggers |= TRIGGER_CHANGED | TRIGGER_UNDEPLOYED | TRIGGER_DESTROYED;
	MineDeleted(tile);// tell routeplanner

}

void PlaceExplosiveCharge( WEAPON *pWeapon, int x, int y )
{
	int i;

	if( !pWeapon )
		return;

	if( x <= 0 )
		return;
	if( y <= 0 )
		return;

	if( pWeapon->eWeapon != ARMY_EXPLOSIVE_WEAPON )
		return;
	OBJECT* expObj;
	for( i = 0; i < pWeapon->nMaxAmmo; i++ )
	{
		expObj = &the_map.objects[ pWeapon->charges[i] ];
		if(expObj->triggers & TRIGGER_UNDEPLOYED && !(expObj->triggers & TRIGGER_DESTROYED))
			break;
	}

	if( i >= pWeapon->nMaxAmmo )
		return;


	i = pWeapon->charges[i];

	ASSERT ( i > 0 );
	ASSERT( the_map.objects[i].common.eventNum );
	ASSERT( the_map.objects[i].sobj);
	ASSERT( the_map.objects[i].common.nUniqueID );

	the_map.objects[i].cell.flags |= ANIM_FLAG_ACTIVE;
	the_map.objects[i].cell.world_pos.x = x;
	the_map.objects[i].cell.world_pos.y = y;
	the_map.objects[i].common.pWeapon = NULL;
	the_map.objects[i].common.position.x = x;
	the_map.objects[i].common.position.y = y;
	the_map.objects[i].triggers &= ~TRIGGER_UNDEPLOYED;
	the_map.objects[i].common.tile = ENCODE_IPOINT( x, y );

	MoveDispXObject( &(the_map.objects[i].cell), TRUE );
	SOBJ_ResetStartingPosition(the_map.objects[i].sobj);
	EventTrigger( EVENT_ITEMGO, the_map.objects[i].common.eventNum,
		the_map.objects[i].common.nUniqueID, 0, 0 );
}


void PutMine(OBJECT* pObj,SPOINT position,int eArmy)
{
    IPOINT tile = ENCODE_IPOINT(position.x,position.y);
	pObj->cell.flags |= ANIM_FLAG_ACTIVE;
	pObj->cell.world_pos = position;
	pObj->common.pWeapon = NULL;  // this makes the mine used, unable to be reused
	pObj->common.position = position;
	pObj->common.tile = ENCODE_IPOINT(position.x,position.y);
	pObj->timer = gpGame->dwAnimTime;
	pObj->owner = eArmy;
	pObj->common.tile = tile;
	pObj->triggers &= ~TRIGGER_UNDEPLOYED;
	pObj->triggers |= TRIGGER_CHANGED;
	if( eArmy != ARMY_PLAYER  && Allah != 1)
	{
		pObj->cell.flags |= ANIM_FLAG_INVISIBLE;
		pObj->triggers |= TRIGGER_INVISIBLE;
	}
	else
	{
		pObj->cell.flags &= ~ANIM_FLAG_INVISIBLE;
		pObj->triggers &= ~TRIGGER_INVISIBLE;
	}
	MoveDispXObject( &(pObj->cell), TRUE );
    MineAdded(tile,eArmy); // tell routeplanner
}

static void PlaceMineCharge( WEAPON *pWeapon, SPOINT position,int eArmy )
{
	int i;
	OBJECT* mineObj;
	if( !pWeapon )
		return;

	if( position.x <= 0 )
		return;
	if( position.y <= 0 )
		return;

	if( pWeapon->eWeapon != ARMY_MINE )
		return;

	if( pWeapon->charges == NULL )
		return;

	for( i = 0; i < pWeapon->nMaxAmmo; i++ )
	{
		mineObj = &the_map.objects[ pWeapon->charges[i] ];
		if(mineObj->triggers & TRIGGER_UNDEPLOYED && !(mineObj->triggers & TRIGGER_DESTROYED))
			break;
	}

	if( i >= pWeapon->nMaxAmmo )
		return;

	i = pWeapon->charges[i];
	ASSERT ( i > 0 );
    OBJECT* pObj;
    pObj = &the_map.objects[i];

    position = CenterPoint(position);


    if (!IS_LOCAL_ARMY(eArmy)) return; // remote mines are placed by net message
    TRACE("Placing mine %d at tile %d\n",i,ENCODE_IPOINT(position.x,position.y));
        
    PutMine(pObj,position,eArmy);
	ObjectPlaceMessageSend(pObj);

}

void SetItemCurrentAmmo(ITEM *pItem, int ammo)
{
	if( pItem->pWeapon )
		pItem->pWeapon->nAmmo = ammo;
}

int GetItemCurrentAmmo(ITEM *pItem)
{
	if( pItem && pItem->pWeapon )
		return pItem->pWeapon->nAmmo;
	else
		return 0;
}

int GetItemMaxAmmo(ITEM *pItem)
{
	if( pItem && pItem->pWeapon )
		return pItem->pWeapon->nMaxAmmo;
	else
		return 0;
}

void SetWeaponOwner(WEAPON *pWeapon, ITEM *pOwner)	{
	pWeapon->pOwner = pOwner;
}
