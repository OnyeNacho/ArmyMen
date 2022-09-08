//========================================================================
//	FILE:			$Workfile: Asset.cpp $
//
//	DESCRIPTION:	Text processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Monday, May 12, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Asset.cpp 49    4/15/98 4:58p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996,1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	AssetInit()
//		Initialize the Asset processing.
//	AssetExit()
//		Terminate the Asset processor.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Asset.cpp $
//  
//  49    4/15/98 4:58p Nrobinso
//  improve objectfind
//  
//  48    4/07/98 6:13a Bwilcox
//  tad cleanup
//  
//  46    4/02/98 2:03p Phu
//  typecasting to prevent warnings
//  
//  45    4/01/98 1:33p Bwilcox
//  CHANGE LOCAL TEST
//  
//  44    3/02/98 3:04p Phu
//  new asset firing hotspots
//  
//  43    2/13/98 11:13a Phu
//  
//  42    2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  41    1/29/98 1:56p Bwilcox
//  assets not removed by remove unused items now
//  
//  40    1/29/98 1:41p Bwilcox
//  fixed asset delete
//  
//  39    1/02/98 11:22a Bwilcox
//  fixing asset fire some
//  
//  38    12/24/97 5:01p Bwilcox
//  removing use of location and oldlocation epoints
//  
//  37    12/21/97 8:28p Bwilcox
//  removing use of elevation
//  
//  36    12/19/97 8:50p Phu
//  assets...
//  
//  35    97/12/19 17:03 Dmaynard
//  
//  34    12/19/97 4:26p Phu
//  Network assets
//  
//  33    12/09/97 12:11p Phu
//  
//  32    11/24/97 8:35p Phu
//  Add Z component to projectile firing
//  
//  31    11/20/97 3:25p Phu
//  base muzzle flash anchor on uid
//  
//  30    11/20/97 11:42a Phu
//  attached muzzle flashes
//  
//  29    10/13/97 5:20p Nrobinso
//  change weapon in ITEM to an item pointer, then add WEAPON data to those
//  structures that need it.
//  
//  28    10/13/97 9:53a Aburgess
//  added TadValidation checks to ASSET
//  
//  26    8/21/97 6:44p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  25    8/16/97 3:01p Nrobinso
//  add distance to Fire Weapon
//  
//  24    8/16/97 1:53p Bwilcox
//  
//  23    8/16/97 1:51p Bwilcox
//  FireWeapons now calls ItemMakeVisible
//  
//  22    8/08/97 9:44a Nrobinso
//  ObjectFind replaces AssetFind
//  
//  21    8/07/97 11:12p Nrobinso
//  moved globals.h to stdafx.h
//  
//  20    8/06/97 9:50a Nrobinso
//  WeaponFire now FireWeapon
//  
//  19    7/31/97 7:32p Nrobinso
//  removed unused ,h files; moved an ASSERT improperly placed
//  
//  18    7/29/97 10:52p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
//  
//  17    7/29/97 10:46a Nrobinso
//  new general object firing range
//  
//  16    7/28/97 9:08p Bwilcox
//  deleted extraneous TadSwarmArmy, Mainbase + Invisble flags+macros
//  TadSelect now call ObjectIsVisible for visibility testing of targets
//  
//  ...
//
//  4     6/30/97 8:39p Bwilcox
//  moving protos out of army.h into vehicle.h, trooper.h, unit.h 
//  removing dead code and variables.
//  
//  3     5/14/97 7:15p Aburgess
//  added AssetKill() stub
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"

#include "Army.h"
#include "Tad.h"
#include "Map.h"
#include "Comm.h"
#include "Disp.h"
#include "Object.h"
#include "Explosions.h"
#include "Audio.h"
#include "AssetMsg.h"
#include "aiaccess.h"
#include "weapon.h"
#include "item.h"


extern	void UnitValidateTad();

///========================================================================
//							DEFINES
///========================================================================

///========================================================================
//							VARIABLES
///========================================================================

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================

///========================================================================
//	Function:		AssetInit()
//
//	Description:
//		Initialize the Asset processing.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

BOOL	AssetInit( void )
{
	return( FALSE );
}

///========================================================================
//	Function:		AssetExit()
//
//	Description:
//		Terminate the Asset processor.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AssetExit( void )
{
}

///========================================================================
//	Function:		AssetCreate()
//
//	Description:
//		Create an Asset. An Asset is created once it is placed actively into
//		the world
//
//	Input:			eArmy			which army this asset belongs to
//					pNewAsset		new asset to create
//					pPosition		where to place the asset in the world 
//
//	Ouput:			none
//
///========================================================================

BOOL	AssetCreate( ARMY_TYPE eArmy, OBJECT* pNewAsset, SPOINT* pPosition )
{
	BOOL		error = FALSE;		// assume success

	// now set the starting location, also save as the old postion
	pNewAsset->common.position.x    = pPosition->x;	// x position within the world
	pNewAsset->common.position.y    = pPosition->y;	// y position within the world
	pNewAsset->common.oldPosition.x = pPosition->x;	// x position within the world
	pNewAsset->common.oldPosition.y = pPosition->y;	// y position within the world

	// create the tad for this asset
	if (TadCreateObject((int)ITEM_ARMY(pNewAsset), (int)ARMY_ASSET, (ITEM*)pNewAsset, TAD_SMART))
	{
		TRACE("ERROR: failed TAD ASSET create object. [%s:%d]\n", __FILE__, __LINE__ );
		error = TRUE;
	}
	return( error );
}


///========================================================================
//	Function:		AssetInFiringRange()
//
//	Description:
//		check to see if an object is within firing range
//
//	Input:			pAsset		asset to be checked
//
//	Ouput:			none
//
///========================================================================

BOOL	AssetInFiringRange( OBJECT* pAsset )
{
	TAD*	pTad;
	SPOINT	pTargetPosition;
	SPOINT	pAssetPosition;
	int		direction;
	long	nAssetRange;
	long	nTargetRange;
	long	nFiringRange;
	long	nDistance;
	BOOL	bInRange = FALSE;

	// validate the parameter
	pTad = (TAD*)(pAsset->common.pTad);
	ASSERT( pTad );

	if ( IS_SMART( pTad->bFlags ) == FALSE)
		goto exit;
	if (TadCurrentTarget( (ITEM*)pAsset ) == NULL ) 
		goto exit;

	// access the firing ranges
	nAssetRange  = AiObjectFiringRange( (ITEM*)pAsset );
	nTargetRange = TadTargetFiringRange( pTad );

	// choose the larger of the two
	nFiringRange = nAssetRange;
	if ( nAssetRange < nTargetRange )
		nFiringRange = nTargetRange;

	// calculate the distance from the target
	nDistance = TadDistanceToTarget( pTad );

	// compare the distances, if unit distance is inside firing range return TRUE
	if ( nDistance < nFiringRange )
	{
		pAssetPosition  = pAsset->common.position;
		pTargetPosition = TadTargetPosition( pTad );
		direction       = GetDirection( &pAssetPosition,&pTargetPosition );
		AssetSetDirection( pAsset, direction );
		bInRange = TRUE;
	}
exit:
	return( bInRange );
}

///========================================================================
//	Function:		AssetSetDirection()
//
//	Description:
//		Set the direction for an Asset object.
//
//
//	Input:			pAsset			pointer to Asset to change direction
//					direction		direction to apply
//
//	Ouput:			none
//
///========================================================================

void	AssetSetDirection( OBJECT* pAsset, int direction )
{
	// tell the Asset which direction they are facing
	pAsset->common.facing = direction;
}


///========================================================================
//	Function:		AssetFireWeapon()
//
//	Description:
//		fire the Asset's weapon.
//
//
//	Input:			pAsset		Asset firing the weapon
//
//	Ouput:			none
//
///========================================================================

SPOINT gun_hotspots[4] = 
{
	{ 30, 23 },
	{ 30, 78 },
	{ 85, 78 },
	{ 85, 23 }
};


void AssetFireWeapon( OBJECT* pAsset, ITEM *pTarget )
{
	if( IS_LOCAL_ARMY(ITEM_ARMY(pAsset) ) )
	{
		if( pAsset->common.nStrength <= 0 )
			return;
	}
	if( !pTarget )
		return;

	if( !pAsset->common.pWeapon )
		return;

	SPOINT	pt;
	int		dy, dx;
	int		dist, range, dir;

	dy = pTarget->position.y - pAsset->cell.world_pos.y;
	dx = pTarget->position.x - pAsset->cell.world_pos.x;
	dist = GetDistance( &(pAsset->cell.world_pos), &(pTarget->position) );
	range = WeaponMaxRange( pAsset->common.pWeapon->eWeapon);
	if( dist < WeaponMinRange(pAsset->common.pWeapon->eWeapon) || dist > range )
		if( IS_LOCAL_ARMY(ITEM_ARMY(pAsset)))
			return;

	dir = arc_sin_table[(int)((double)dy/(double)dist * 100.0) + 100];
	if( (dx > 0) && (dir > 0) )
		dir = 256 - dir;
	dir += (rand()%5) - 2;
	if( dir > 255 )
		dir -= 256;
	else if( dir < 0 )
		dir += 256;
	dist += (rand()%20) - 15;

	pt.x = pAsset->cell.wrect.left + gun_hotspots[dir >> 6].x;
	pt.y = pAsset->cell.wrect.top + gun_hotspots[dir >> 6].y;

	pAsset->common.fireDirection = dir;
	pAsset->common.fireDistance = dist;
	pAsset->common.pVictim = pTarget;
	FireWeapon( (ARMY_TYPE)ITEM_ARMY((ITEM *)pAsset), 
				pAsset->common.pWeapon, 
				&pt,
				96,
				pAsset->common.fireDirection, 
				pAsset->common.fireDistance, 
				0, 
				ITEM_UID(pAsset) );
	ItemMakeVisible(pAsset);
	if( IS_LOCAL_ARMY( ITEM_ARMY(pAsset) ) )
		AssetFireMessageSend( pAsset );
}


///========================================================================
//	Function:		AssetKill()
//
//	Description:
//		kill off an Asset object.
//
//
//	Input:			pAsset			pointer to Asset to change direction
//
//	Ouput:			none
//
///========================================================================

void	AssetKill( OBJECT* pAsset )
{
	TRACE( "Asset killed....\n" );
}


///========================================================================
//	Function:		ObjectFind()
//	Description:
///========================================================================

OBJECT*	ObjectFind( ULONG nUniqueID )
{
	OBJECT *pObj;
    int index = SUB2TYPE(nUniqueID);

	pObj = &the_map.objects[index];

	if (pObj->common.nUniqueID == nUniqueID)
		return pObj;

	for (int i=0; i<the_map.num_objects; i++)
	{
		if (the_map.objects[i].common.nUniqueID == nUniqueID)
			return &the_map.objects[i];
	}

	return NULL;
}


//========================================================================
//								EOF
///========================================================================
