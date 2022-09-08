/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: object.cpp $
//
//	DESCRIPTION:	Object manipulation code
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		unknown
//
//	REVISION:		$Header: /ArmyMen/src/object.cpp 22    4/18/98 12:49p Bwilcox $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/object.cpp $
//  
//  22    4/18/98 12:49p Bwilcox
//  created xtriggers, moved trigger_branch to it, added
//  xtrigger_sargecarried
//  
//  21    4/17/98 5:23p Phu
//  pass itemsetlocation position not worldpos on load
//  
//  20    4/17/98 4:52p Phu
//  anim undeploy removed 
//  
//  19    4/15/98 4:58p Nrobinso
//  return if don't find object
//  
//  18    4/08/98 10:59a Phu
//  always call itemsetlocation
//  
//  17    4/07/98 11:04a Phu
//  don't call itemsetlocation if no world_pos while restoring item
//  
//  15    4/03/98 5:19p Phu
//  save object owner, enable objects if they're placed
//  
//  14    4/02/98 3:21p Phu
//  typecast to avoid warnings
//  
//  13    3/29/98 1:28a Nrobinso
//  save ammo of objects
//  
//  12    3/28/98 11:59p Nrobinso
//  fix loadgame bug (it was starting at the beginning of the file instead
//  of continuing)
//  
//  11    3/17/98 6:09p Bwilcox
//  proper null checking around aiitemfind calls
//  
//  10    1/20/98 12:27a Nrobinso
//  make sure an UNDEPLOYEd, destroyed object is inactivated; save the cell
//  position as well as object position of objects
//  
//  9     1/15/98 5:05p Phu
//  new aai
//  
//  8     12/13/97 1:07a Phu
//  Use up objects / debug quest items
//  
//  7     12/09/97 12:28p Bwilcox
//  sarge cant pick up when in vehicle
//  
//  6     12/09/97 12:12p Phu
//  
//  5     12/07/97 5:10p Phu
//  
//  4     12/06/97 1:10p Nrobinso
//  save object triggers & position; give sarge an objects he picked up
//  
//  3     12/04/97 9:10a Aburgess
//  Put Load via Chunk wrapper on saved Object code.
//  
//  2     12/01/97 4:08p Awerner
//  Added code for object damage to be stored and restored
//  
//  1     12/01/97 3:38p Awerner
//  initial check-in
//  
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "army.h"
#include "util.h"
#include "object.h"
#include "map.h"
#include "aiaccess.h"
#include "damage.h"
#include "fileio.h"
#include "sarge.h"
#include "disp.h"
#include "item.h"


/////////////////////////////////////////////////////////////////////////////
// Global Prototypes
/////////////////////////////////////////////////////////////////////////////
extern int isPickupable( ITEM *object, SARGE *actor );

/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////
void RestoreObjectChanges(OBJECT_SAVE_INFO_STRUCT *pOsi);

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

void SaveObjectChanges(FILE* pSaveFile)
{
	int i;
	OBJECT_SAVE_INFO_STRUCT osi;
	long chunkheader=(long)OBJS_ID;
	long nSize;

	for (i=0;i<the_map.num_objects;i++)
	{
		if (the_map.objects[i].triggers & TRIGGER_CHANGED)
		{
			osi.nUid=the_map.objects[i].common.nUniqueID;
			osi.strength=the_map.objects[i].common.nStrength;
			osi.curframe=the_map.objects[i].damageindex;
			osi.triggers=the_map.objects[i].triggers;
			osi.xtriggers=the_map.objects[i].xtriggers;
			osi.position=the_map.objects[i].common.position;
			osi.cellpos=the_map.objects[i].cell.world_pos;
			osi.owner = the_map.objects[i].owner;
			if (the_map.objects[i].common.pWeapon)
				osi.nAmmo=the_map.objects[i].common.pWeapon->nAmmo;
			else
				osi.nAmmo=0;

			CHUNK_WRITE_LONG( pSaveFile, &chunkheader );

			// write out the size of the mission save block
			nSize = sizeof( osi );
			CHUNK_WRITE_LONG( pSaveFile, &nSize );

			// write the data to the file
			CHUNK_WRITE_BUFFER( pSaveFile, &osi, sizeof( osi ) );
		}
	}
}
	

void RestoreSavedObjects(FILE* pSaveFile)
{
	BOOL					bDone;
	LONG					nSaveSize;
	OBJECT_SAVE_INFO_STRUCT ObjectSaveInfo;

	// read in the data
	if ( ChunkFindNext( pSaveFile, OBJS_ID ) )
	{
		// now read in the stats data
		bDone = FALSE;
		while( !bDone && !feof( pSaveFile) )
		{
			// read in the chunk size
			CHUNK_READ_LONG( pSaveFile, &nSaveSize );
			if ( nSaveSize )
			{
				// read in the object record
				CHUNK_READ_BUFFER(pSaveFile, &ObjectSaveInfo, nSaveSize);
				RestoreObjectChanges( &ObjectSaveInfo );

				if ( !ChunkFindNext( pSaveFile, OBJS_ID ) )
					bDone = TRUE;
			}
			else
				bDone = TRUE;
		}
	}
}

void RestoreObjectChanges(OBJECT_SAVE_INFO_STRUCT *pOsi)
{
	OBJECT *pObject;
	SARGE	*pSarge = SargePointer(ARMY_PLAYER);

	pObject = (OBJECT*)AiItemFind(pOsi->nUid);
//	ASSERT(pObject);

	if (!pObject)
	{
		TRACE("Bad saved object: %X\n", pOsi->nUid);
		return;
	}

	// may need to act on triggers
	pObject->triggers = pOsi->triggers;
	pObject->xtriggers = pOsi->xtriggers;

	AI_ITBL *pAiObjDefs;
	pAiObjDefs = AiGetObjectDefs( pObject->category, pObject->number, pOsi->curframe );
	Dmg_SetObjectDamage( pObject, pAiObjDefs, pOsi->curframe );

	if (pObject->common.pWeapon)
	{
		pObject->common.pWeapon->nAmmo = pOsi->nAmmo;
	}

	pObject->common.nStrength = pOsi->strength;
	pObject->common.position = pOsi->position;
	pObject->cell.world_pos = pOsi->cellpos;
	pObject->owner = pOsi->owner;
	ItemSetLocation((ITEM*)pObject,&(pObject->common.position));   // phu change from cellpos to position
	ItemSetOldLocation((ITEM*)pObject);

	if( !(pOsi->triggers & TRIGGER_UNDEPLOYED) ) // its on the map
	{
		AnimActivate( (ANIM *)(&(pObject->cell)), FALSE );
		MoveDispXObject( &(pObject->cell), TRUE );
	}
	else if(pOsi->triggers & TRIGGER_DESTROYED ) // its dead
	{
		AnimInactivate( (ANIM *)&pObject->cell, FALSE );
		MoveDispXObject( &(pObject->cell), TRUE );	
	}
	else if(pOsi->xtriggers & XTRIGGER_SARGECARRIED )  // in sarge hands
	{
		if (isPickupable( (ITEM *)pObject, pSarge))	// he gets the weapon even if currently in a vehicle
			SargePickupWeapon( pSarge, (ITEM *)pObject, TRUE);	// pickup w/o sound
		else TRACE("ERROR- sarge cant carry this???\n");

	}
	else // ordinary undeployed thing
	{
		AnimInactivate( (ANIM *)&pObject->cell, FALSE );
		MoveDispXObject( &(pObject->cell), TRUE );	
	}
}