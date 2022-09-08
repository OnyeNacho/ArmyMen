/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: damage.cpp $
//
//	DESCRIPTION:	Trooper avatar animation
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		unknown
//
//	REVISION:		$Header: /ArmyMen/src/damage.cpp 113   4/18/98 4:03p Bwilcox $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/damage.cpp $
//  
//  113   4/18/98 4:03p Bwilcox
//  scripts objects now also raise damage and death events
//  
//  112   4/18/98 12:45p Bwilcox
//  created xtriggers, moved trigger_branch to it, added
//  xtrigger_sargecarried
//  
//  111   4/09/98 4:26p Nrobinso
//  ignore damage sounds for object pieces
//  
//  110   4/08/98 7:51p Phu
//  fix object removal if no next sprite specified
//  
//  108   4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  107   4/02/98 2:44p Nrobinso
//  set scripted objects to changed for saving purposes
//  
//  106   4/01/98 1:36p Bwilcox
//  change local test
//  
//  105   4/01/98 1:06p Bwilcox
//  
//  104   3/31/98 4:18p Nrobinso
//  don't change max strength
//  
//  103   3/27/98 3:57p Bwilcox
//  
//  102   3/27/98 2:29p Bwilcox
//  
//  101   3/27/98 2:25p Bwilcox
//  asset cleanup in message
//  
//  100   3/21/98 8:29p Nrobinso
//  only ricochet off rocks
//  
//  99    3/20/98 3:53p Phu
//  change the way groups kill each other (use damage)
//  
//  98    3/19/98 9:00p Phu
//  change the way grouped stuff does damage
//  
//  97    3/19/98 8:13p Phu
//  
//  96    3/18/98 7:37p Bwilcox
//  spontaneous fire and barrel fire suppressed in multiplayer
//  
//  95    98/03/18 17:45 Dmaynard
//  fix test for already_dead in damage.cpp
//  
//  94    98/03/18 16:42 Dmaynard
//  pass along side effect damage uid
//  
//  93    3/18/98 3:03p Nrobinso
//  make sure we can do sfx even if an object is fully damaged
//  
//  92    3/18/98 12:47p Nrobinso
//  Even tho rocks have no hitpoints, go thru the damage function so we get
//  a sfx
//  
//  91    3/17/98 11:53a Nrobinso
//  
//  90    3/13/98 5:23p Phu
//  new tree stuff
//  
//  89    98/03/12 23:08 Dmaynard
//  When calling releaseobjectsprite you must store null afterwards or
//  crash sometimes.
//  
//  88    3/12/98 5:22p Bwilcox
//  air fixes
//  
//  87    3/12/98 2:07p Bwilcox
//  
//  86    3/11/98 7:24p Phu
//  crush damage when set to last damage sprite
//  
//  85    3/07/98 7:33p Bwilcox
//  
//  84    3/06/98 10:05p Bwilcox
//  
//  83    3/06/98 5:34p Bwilcox
//  barrels sometimes explode into flames
//  
//  82    3/06/98 2:03p Bwilcox
//  spontaneous combustion once every 30 minutes maybe
//  
//  81    3/06/98 1:20p Bwilcox
//  
//  80    3/03/98 4:50p Bwilcox
//  
//  79    3/03/98 4:49p Bwilcox
//  a pyro at heart
//  
//  76    3/02/98 5:17p Bwilcox
//  restricting number of simultaneous flames
//  
//  75    3/02/98 4:39p Bwilcox
//  fixing fire bug
//  
//  74    3/02/98 4:16a Bwilcox
//  occasional major forest fires from flame thrower
//  
//  73    2/25/98 7:24p Nrobinso
//  improve object damage sounds
//  
//  72    2/20/98 7:08p Nrobinso
//  put in new sfx calls
//  
//  71    2/20/98 1:16p Nrobinso
//  fix up sounds
//  
//  70    2/19/98 8:46p Nrobinso
//  turn off damage sounds
//  
//  69    2/19/98 6:32p Phu
//  send uid with object damage
//  
//  68    2/19/98 5:56p Phu
//  flaming trees
//  
//  67    2/17/98 7:50p Nrobinso
//  comment out static sfx commands
//  
//  66    2/17/98 7:03p Phu
//  fix damage sprites when much bigger than original sprite
//  
//  65    2/16/98 12:03p Phu
//  pass along fromUID with explosions
//  
//  64    2/12/98 6:38p Phu
//  negative armor for non-flameproof items
//  
//  63    2/12/98 12:53p Nrobinso
//  new sounds
//  
//  62    2/11/98 4:37p Phu
//  wavy smoke from husks
//  
//  61    2/10/98 7:34p Phu
//  fix to damage of attached objects / script assert
//  
//  60    2/10/98 4:25p Nrobinso
//  Attached objects
//  
//  59    2/10/98 11:32a Bwilcox
//  mines are placed by net message object_place, not by local firing.
//  objectdamage now takes spoint instead of spoint *
//  dead field removed from objectmessage
//  
//  58    2/09/98 7:40p Phu
//  fix to objectisdestroyed function
//  
//  57    2/07/98 5:14p Phu
//  apply full damage to linked components
//  
//  56    2/07/98 4:22p Phu
//  temporary smoking tree sturff
//  
//  55    2/06/98 12:34p Bwilcox
//  
//  54    2/06/98 12:21p Bwilcox
//  
//  53    2/06/98 12:11p Bwilcox
//  only send husk damage if local machine did it
//  
//  52    2/06/98 11:42a Phu
//  husks
//  
//  51    2/04/98 3:16p Phu
//  armor for objects
//  
//  50    2/04/98 3:08p Bwilcox
//  damage events happen once
//  
//  49    2/01/98 1:40p Phu
//  -3 extension to libarary load
//  
//  48    1/27/98 1:50p Bwilcox
//  allow repeated hit events
//  
//  47    1/26/98 5:17p Bwilcox
//  damage hit triggers hit event only once
//  
//  46    1/21/98 1:52p Phu
//  check in for bruce - mine removal function
//  
//  45    1/20/98 1:21p Phu
//  mines now take damage instead of blowing up right away
//  
//  44    1/19/98 3:41p Awerner
//  once again fixed the mine damage
//  
//  43    1/15/98 7:57p Phu
//  fix to damage level setting (activate anim on moving layers)
//  
//  42    1/15/98 6:38p Phu
//  
//  41    1/15/98 5:05p Phu
//  new aai
//  
//  40    1/09/98 12:21p Awerner
//  fixed mines and bushes so they trigger events when damaged
//  
//  39    1/05/98 3:37p Phu
//  Mines get damage done from aai file
//  
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "Army.h"
#include "Ai.h"
#include "AiAccess.h"
#include "Disp.h"
#include "MainFrm.h"
#include "Map.h"
#include "GameFlow.h"
#include "miscfile.h"
#include "Tile.h"
#include "item.h"
#include "damage.h"
#include "explosions.h"
#include "vehicle.h"
#include "trooper.h"
#include "aibtank.h"
#include "sarge.h"
#include "weapon.h"
#include "ObjectMsg.h"
#include "AssetMsg.h"
#include "Comm.h"
#include "audio.h"
#include "event.h"
#include "fileio.h"
#include "husk.h"
#include "wobject.h"


///////////////////////////////////////////////////////////////////////////
//// Function Prototypes
///////////////////////////////////////////////////////////////////////////

void GenericObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects, int fromUID );
void GenericObjectDamageFunction_nosideeffects(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects );
void MineObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects, int fromUID);
//void FenceObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects);
//void TreeObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects);
//void BuildingObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects);
//void BridgeObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects);
void BushObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects, int fromUID);
//void BaseObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects);
void KillAttachedObjects(OBJECT *pObj);
void AudioPlayObjectDamage(OBJECT *pObj, int damagetype, int kind);

///////////////////////////////////////////////////////////////////////////
//// TYPEDEFS
///////////////////////////////////////////////////////////////////////////
typedef void(*ObjectDamageFunc)(OBJECT *, int, int, SPOINT*, int, int);

///////////////////////////////////////////////////////////////////////////
//// DATA
///////////////////////////////////////////////////////////////////////////
#define UNKNOWN 10

#define DESTROYED_KIND	0
#define DAMAGED_KIND	1
#define NO_DAMAGE_KIND	2


ObjectDamageFunc damagefuncs[]=
{
	GenericObjectDamageFunction,			//"Rock",
	BushObjectDamageFunction,				//"Bush",
	GenericObjectDamageFunction,			//"Tree",
	GenericObjectDamageFunction,			//"BigTree",
	GenericObjectDamageFunction,			//"FallenTree",
	GenericObjectDamageFunction,			//"Fence",
	GenericObjectDamageFunction,			//"Wall",
	GenericObjectDamageFunction,			//"Bridge",
	GenericObjectDamageFunction,			//"FootBridge",
	MineObjectDamageFunction,				//"Explosives",
	GenericObjectDamageFunction,			//"GunTurret",
	GenericObjectDamageFunction, 			//"AAGun",
	GenericObjectDamageFunction,			//"Base",
	GenericObjectDamageFunction,			//"Auxbase",
	GenericObjectDamageFunction,			//"AirStrip",
	GenericObjectDamageFunction,			//"HeliPad",
	GenericObjectDamageFunction,			//"PrisonCamp",
	GenericObjectDamageFunction,			//"Building",
	GenericObjectDamageFunction,			//"PillBox",
	GenericObjectDamageFunction,			//"PowerPlant",
	GenericObjectDamageFunction,			//"FenceGate",
	GenericObjectDamageFunction,			//"WallGate",
	GenericObjectDamageFunction,			//"RadarBuilding",
	GenericObjectDamageFunction,			//"Miscellaneous",
	GenericObjectDamageFunction,			//"Overpass"
	GenericObjectDamageFunction				//"Sitems"
};


COMMAND_NUMBERS randomexplosionssmoke[]=
{
	EXPLOSION_SMOKE_S_COMMAND,
	EXPLOSION_SMOKE_M_COMMAND,
	EXPLOSION_SMOKE_L_COMMAND
};

COMMAND_NUMBERS randomexplosionsflashsmoke[]=
{
	EXPLOSION_FLASH_SMOKE_S_COMMAND,
	EXPLOSION_FLASH_SMOKE_M_COMMAND,
	EXPLOSION_FLASH_SMOKE_L_COMMAND
};

COMMAND_NUMBERS randomexplosionsgunpuff[]=
{
	EXPLOSION_GUN_PUFF_M_COMMAND,
	EXPLOSION_GUN_PUFF_M_COMMAND,
	EXPLOSION_GUN_PUFF_M_COMMAND
};


///////////////////////////////////////////////////////////////////////////
//// FUNCTIONS
///////////////////////////////////////////////////////////////////////////


///========================================================================
//	Function:		Dmg_SetObjectDamage()
//
//	Description:
//		Sets a particular object to have a particular level of displayed damage
//
//	Input:			pObj			which object to damage
//					damagelevel		what damage level to set
//
//	Ouput:			none		
//
///========================================================================
void Dmg_SetObjectDamage( OBJECT *pObj, AI_ITBL *pAiObjDef, int damageindex )
{
	OBJECT_SPRITE *curobjectsprite;
	PSPRITE  newSprite;
	ITEM_OVERLAP overlap;

	if( pObj->damageindex == damageindex )
		return;

	if( _LOAD_FROM_DATAFILE )
	{
		PSPRITE pSprite;

		pSprite = AcquireObjectSprite( pObj->category, pObj->number, damageindex );
		if( !pSprite )
		{
			SubtractObjectFromMovementLayer( pObj );
			AnimInactivate( (ANIM *)(&(pObj->cell)), FALSE );
			pObj->triggers |= TRIGGER_CHANGED;
			pObj->triggers |= TRIGGER_UNDEPLOYED;
			pObj->triggers |= TRIGGER_DESTROYED;
			MoveDispXObject( &(pObj->cell), FALSE );
			return;
		}

		SubtractObjectFromMovementLayer( pObj, &overlap );
		ReleaseObjectSprite( pObj->cell.pSprite );
		pObj->cell.pSprite = NULL;  // IF YOU AINT CLEAN, YOU DIE.
		newSprite = pSprite;
	}
	else
	{
		if( damageindex >= the_map.obj_sprite_array_list[pObj->category][pObj->index].nLevelsOfDamage )
		{
			SubtractObjectFromMovementLayer( pObj );
			AnimInactivate( (ANIM *)(&(pObj->cell)), FALSE );
			pObj->triggers |= TRIGGER_CHANGED;
			pObj->triggers |= TRIGGER_UNDEPLOYED;
			pObj->triggers |= TRIGGER_DESTROYED;
			MoveDispXObject( &(pObj->cell), FALSE );
			return;
		}

		curobjectsprite = &(the_map.obj_sprite_array_list[pObj->category][pObj->index]);
		// change the graphic
		SubtractObjectFromMovementLayer( pObj, &overlap );
		if( pAiObjDef )
			newSprite = &(curobjectsprite->sprites[damageindex]);
	}

	if( pAiObjDef )						// get the aai object attributes & set them
	{
		ChangeAnimSprite( &(pObj->cell), (EObjectLayer)pAiObjDef->nLayer, newSprite );
		pObj->movement = pAiObjDef->nMovement;
		if( pAiObjDef->nCrushDamage > 0 && pAiObjDef->nHitPoints == 0 )
			AddObjectToMovementLayer( pObj, &overlap, pAiObjDef->nCrushDamage );
		else
			AddObjectToMovementLayer(pObj);
		pObj->damageindex = damageindex;
		pObj->common.nStrength = pAiObjDef->nHitPoints;
		pObj->elevation = pAiObjDef->nHeight;
		pObj->visibility = pAiObjDef->nVisibility;
		pObj->permeability = pAiObjDef->nPermeability;
		pObj->armor = pAiObjDef->nArmor;
		pObj->triggers |= TRIGGER_CHANGED;
	}
	else								// if no aai entry, remove the object from the world
	{
		AnimInactivate( (ANIM *)(&(pObj->cell)), FALSE );
		pObj->triggers |= TRIGGER_CHANGED;
		pObj->triggers |= TRIGGER_UNDEPLOYED;
		pObj->triggers |= TRIGGER_DESTROYED;
		MoveDispXObject( &(pObj->cell), FALSE );
	}
}


void Dmg_IncObjectDamage(OBJECT *pObj)   // dummy function for debugging only
{
/*
	OBJECT_SPRITE *curobjectsprite;
	int newdamagelevel;

	curobjectsprite=&the_map.obj_sprite_array_list[pObj->category][pObj->index];

	newdamagelevel=(pObj->damageindex+1)%curobjectsprite->nLevelsOfDamage;

	Dmg_SetObjectDamage(pObj, newdamagelevel);
*/
}


void MineObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects, int fromUID )
{
	if( pObj->common.nStrength )
	{
		int oldStrength = pObj->common.nStrength;
		DamageItemTriggerEvents((ITEM*)pObj, oldStrength, 0, oldStrength);

		if( damageamount >= pObj->common.nStrength )
		{
			int damage = 20;
			int id;

			if( pObj->number == ARMY_MINE )
			{
				damage = AIinfo.weaponTables[ARMY_MINE].damage.nDamage;
				SARGE *pSarge;

				if( pObj->owner >= 0 )
				{
					pSarge = SargePointer(OBJECT_OWNER(pObj));
					if( pSarge )
						id = ITEM_UID( pSarge );
					else
						id = fromUID;
				}
				else
					id = fromUID;
				UnplaceMine(pObj);
			}
			else
			{
				GenericObjectDamageFunction_nosideeffects(pObj, damageamount, damagetype, damageloc, dosideeffects);
				id = fromUID;
			}


			DoExplosion(pObj->cell.world_pos.x, pObj->cell.world_pos.y, 
				EXPLOSION_FLASH_COMBUSTION_M_COMMAND, NULL, DMGTYPE_OTHER_EXPLOSION, 
				dosideeffects ? damage : 0, NULL, FALSE, id, MINE_EXPLODE);

			DiedItemTriggerEvents((ITEM*)pObj);
		}
		else
		{
			if( pObj->number == ARMY_MINE )
				pObj->common.nStrength -= damageamount;
			else
				GenericObjectDamageFunction_nosideeffects(pObj, damageamount, damagetype, damageloc, dosideeffects);
		}
	}
}

void BushObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects, int fromUID )
{

}


void ObjectWithScriptDamageFunction(OBJECT *pObj, int damageamount )
{
	int olddamage;
	int newdamage;

	olddamage=pObj->common.nStrength;
	if (!olddamage)
		return;

	newdamage=olddamage-damageamount;
	if (newdamage<0)
		newdamage=0;

	pObj->common.nStrength=newdamage;

	int hps = pObj->common.nMaxStrength;

	olddamage*=100;
	olddamage/=hps;

	newdamage*=100;
	newdamage/=hps;

	pObj->triggers |= TRIGGER_CHANGED;

	SOBJ_Damage(pObj->sobj, olddamage, newdamage);
	
	DamageItemTriggerEvents( (ITEM*)pObj, olddamage, newdamage, hps );
	if (!newdamage) DiedItemTriggerEvents((ITEM*)pObj);
}



void GenericObjectDamageFunction(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects, int fromUID )
{
	int hps, newstrength, newdamageindex;
	int secondarydamagetype = 0;

	// the turtle in bootcamp shrinks with each hit
	if (pObj->category == MISCELLANEOUS && pObj->number == 395 && gpGame->BootCamp) 
		damageamount = 1; 

	hps = pObj->common.nStrength;
	newstrength = __max( 0, hps - damageamount );

	//first of all, if this was a bazooka or a tank shell, we'll need a secondary explosion
	switch(damagetype)
	{
		case DMGTYPE_BAZOOKA:
		case DMGTYPE_MISSILE:
			secondarydamagetype |= DMGTYPE_EXPLOSION;
			break;
	}

	//if we need a secondary explosion, do it
	if( secondarydamagetype )
		if (damageloc && damageloc->x)
			DoExplosion(damageloc->x, damageloc->y, randomexplosionsflashsmoke[rand()%3], 
				NULL, secondarydamagetype, 0, (ITEM *)pObj, FALSE, 0, DESTROYED );
	else
	if( damagetype == DMGTYPE_BULLET )			// make a bullet puff
		DoExplosion( damageloc->x, damageloc->y, randomexplosionsgunpuff[rand()%3],
			NULL, 0, 0, NULL, FALSE, 0, BULLET_HIT_OBJECT);

	// if object started with no hps, still won't have any, or damage amount was 0
	if( newstrength == hps )
	{
		AudioPlayObjectDamage(pObj, damagetype, NO_DAMAGE_KIND);
		return;
	}

	DamageItemTriggerEvents( (ITEM*)pObj, pObj->common.nStrength, newstrength, hps );
		
	// check if the object needs to change sprites
	AI_ITBL *pAiObjDefs;
	AI_ITBL *pAiObjTemp;

	// continue to get the next object until our hit points is <= the new hit points
	newdamageindex = pObj->damageindex + 1;
	pAiObjTemp = pAiObjDefs = AiGetObjectDefs( pObj->category, pObj->number, newdamageindex );
	while( pAiObjDefs && (newstrength <= pAiObjDefs->nHitPoints) )
	{
		pAiObjTemp = pAiObjDefs;
		pAiObjDefs = AiGetNextObjectDef( pAiObjDefs );
		newdamageindex++;
	}
	if( pAiObjTemp != pAiObjDefs )
	{
		newdamageindex--;
		pAiObjDefs = pAiObjTemp;
	}
	else if( newstrength > 0 )
		newdamageindex = pObj->damageindex;

    if (newdamageindex != pObj->damageindex && pObj->category == 10 &&
        pObj->number == 201)
       TRACE("Gun tower damage level to %d\n",newdamageindex);


	pObj->triggers |= TRIGGER_CHANGED;
	pObj->common.nStrength = newstrength;

	// if a further level of damage was found and is applicable
	if( pAiObjDefs && (newstrength <= pAiObjDefs->nHitPoints) )
	{
		// object is destroyed
		if( newstrength == 0 )
		{
			DiedItemTriggerEvents((ITEM*)pObj);
			KillAttachedObjects(pObj);
			AudioPlayObjectDamage(pObj, damagetype, DESTROYED_KIND);
		}
		Dmg_SetObjectDamage( pObj, pAiObjDefs, newdamageindex );
	}
	else	// damage was done 
	if( newstrength == 0 )		// item is obliterated
	{
		DiedItemTriggerEvents((ITEM*)pObj);
		KillAttachedObjects(pObj);
		AudioPlayObjectDamage(pObj, damagetype, DESTROYED_KIND);
		Dmg_SetObjectDamage( pObj, pAiObjDefs, newdamageindex );
	}
	else						// item was simply damaged
	{
		AudioPlayObjectDamage(pObj, damagetype, DAMAGED_KIND);
	}
}


void GenericObjectDamageFunction_nosideeffects(OBJECT *pObj, int damageamount, int damagetype, SPOINT *damageloc, int dosideeffects)
{
	int hps, newstrength, newdamageindex;

	//	if the current strength is zero, object is invunerable
	hps = pObj->common.nStrength;
	newstrength = __max( 0, hps - damageamount );
	
	if( hps == newstrength )
		return;

	// check if the object needs to change sprites
	AI_ITBL *pAiObjDefs, *pAiObjTemp;

	// continue to get the next object until our hit points is <= the new hit points
	newdamageindex = pObj->damageindex + 1;
	pAiObjTemp = pAiObjDefs = AiGetObjectDefs( pObj->category, pObj->number, newdamageindex );
	while( pAiObjDefs && (newstrength <= pAiObjDefs->nHitPoints) )
	{
		pAiObjTemp = pAiObjDefs;
		pAiObjDefs = AiGetNextObjectDef( pAiObjDefs );
		newdamageindex++;
	}
	if( pAiObjDefs != pAiObjTemp )
	{
		pAiObjDefs = pAiObjTemp;
		newdamageindex--;
	}

	// if a further level of damage was found and is applicable
	if( pAiObjDefs && (newstrength <= pAiObjDefs->nHitPoints) )
	{
		Dmg_SetObjectDamage( pObj, pAiObjDefs, newdamageindex );
	}
	else		// object is obliterated
	if( newstrength == 0 )
	{
		Dmg_SetObjectDamage( pObj, NULL, newdamageindex );
	}
	pObj->triggers |= TRIGGER_CHANGED;
	pObj->common.nStrength = newstrength;
}


///========================================================================
//	Function:		ObjectDamage()
//
//	Description:
//		does (or attempts to do) a particular amount of damage to a 
//		particular object
//
//	Input:			pObj			which object to damage
//					damagetodo		how much damage to do
//					damagetype		what type of damage it is
//
//	Ouput:			none		
//
///========================================================================
static UID flameUID;
int spreadCnt;
int spreadFrom;

long Ignite(IPOINT index)
{
    ITEM* pItemList;
    OBJECTSTRUCT* pObj;
    SPOINT point;
    point = CenterPointFromTile(index);
    pItemList = GetObjectsIntersectPoint(&point);
    while (pItemList != NULL)
    {
        pObj = (OBJECTSTRUCT*) pItemList;
        if (ITEM_TYPE(pItemList) != ARMY_OBSTACLE || pObj->category != TREE)
            goto next;

        // if tree already gone ignore it
        if (pObj->common.nStrength == 0) goto next;

		// begin ignition of new tree never before damaged
		if (pObj->flames < 3) 
		{
            pObj->flames = 3;  // bypass ignition later
			SPOINT pt;
			pt = pObj->cell.world_pos;
			pt.y++;
			MakeFlame(pt,flameUID, 
				pObj->cell.pSprite->srect.right,
				pObj->cell.pSprite->srect.bottom );
            if (pObj->common.nStrength > 15) pObj->common.nStrength = 15; // weaken this tree for future 
            
            // should we stop igniting now?
            if (--spreadCnt <= 0) return 1; // stop spread globally now
            if (--spreadFrom <= 0)// stop local ignition from this tree
            { 
                return 1; //stop local spread
            }
		}

next:
		pItemList = pItemList->next;
    }
	return 0;
}

// see if other trees can ignite really wildly
void SpreadFlames(OBJECT* pObj,UID fromUID)
{
    flameUID = fromUID;
	if (!spreadCnt)  // reroll new spread attempt
	{
		spreadCnt = (rand() % 300);
		if (spreadCnt == 99 || Allah == 2) 
		{
			spreadCnt = 180; // large spread 
			spreadFrom = 0;
		}
		else spreadCnt = 0; // no spread
	}

    if (spreadCnt > 0)
	{
		if (spreadFrom <= 0) spreadFrom = 3;
        ItemFanOut((ITEM*)NULL,pObj->common.tile,10,Ignite);
	}
}

void ObjectDamage(OBJECT *pObj, int damagetodo, int damagetype, SPOINT damageloc, int dosideeffects, UID fromUID)
{
	ObjectDamageFunc curdamagefunc = damagefuncs[pObj->category];
	int				orgdamage;
	BOOL			already_dead = FALSE;

//	if (pObj->common.nStrength == 0) return;
	if (pObj->common.nStrength == 0)
		already_dead = TRUE;

	orgdamage = damagetodo;
	if( pObj->armor < 0 )
	{
		if( damagetype != DMGTYPE_FLAMED )
			damagetodo += pObj->armor;
	}
	else
		damagetodo -= pObj->armor;

	if( damagetodo <= 0 )
		return;

	if (already_dead)
	{
		curdamagefunc(pObj, damagetodo, damagetype, &damageloc, dosideeffects, fromUID);
		return;
	}

	if (pObj->sobj)
		ObjectWithScriptDamageFunction(pObj, damagetodo);
	else
	{
		curdamagefunc(pObj, damagetodo, damagetype, &damageloc, dosideeffects, fromUID);

		if (damagetype!=DMGTYPE_STRUCTURAL && dosideeffects)
		{
			if (pObj->nextsubobject)
			{
				OBJECT* curObj=pObj->nextsubobject;

				while (curObj!=pObj)
				{
					ObjectDamage(curObj, orgdamage, DMGTYPE_STRUCTURAL, OFF_THE_MAP, dosideeffects,0);
					curObj=curObj->nextsubobject;
				}
			}
		}
	}

	// army barrels of explosives may trigger flames randomly (easter egg)
	if (pObj->category == EXPLOSIVES && pObj->number == 10 &&
        gpGame->GameType == GAMETYPE_ONEPLAYER && 
		pObj->common.nStrength == 0 && (rand()%20) == 13)
	{
		SPOINT pt;
		pt = pObj->cell.world_pos;
		pt.y -= 4;
		MakeFlame( pt, fromUID, 
			pObj->cell.pSprite->srect.right,
			pObj->cell.pSprite->srect.bottom );
	}


	if( pObj->category == TREE && damagetype == DMGTYPE_FLAMED )
	{
		if( fromUID && pObj->common.nStrength > 0 )
		{
			if (pObj->flames <= 3) ++pObj->flames;

			// flame ignites tree
			if( pObj->flames == 3)
			{
				SPOINT pt;
				pt = pObj->cell.world_pos;
				pt.y++;
				MakeFlame( pt, fromUID,
					pObj->cell.pSprite->srect.right,
					pObj->cell.pSprite->srect.bottom );
			}

			// spark spreads to nearby trees rarely (easter egg)
			// but only if half second since last elapsed
			if (pObj->flames != 5 &&
				pObj->common.nStrength < 7 &&
                gpGame->GameType == GAMETYPE_ONEPLAYER && 
				CountFlames() < 25)
			{
				 SpreadFlames(pObj,fromUID);
				 pObj->flames = 5; // dont spawn from here again
			}
		}
	}

	if (dosideeffects)
    {
        ObjectDamageMessageSend(pObj, orgdamage, damagetype, damageloc, fromUID );
	}
}



///========================================================================
//	Function:		HuskDamage()
//
//	Description:
//		does (or attempts to do) a particular amount of damage to a 
//		particular object
//
//	Input:			pHusk			which object to damage
//					damagetodo		how much damage to do
//					damagetype		what type of damage it is
//
//	Ouput:			none		
//
///========================================================================
void HuskDamage(THusk *pHusk, int damagetodo, int damagetype, SPOINT *damageloc, UID fromUID)
{
	OBJECTSTRUCT *pObj;
	int			 orgdamage;

	pObj = &(pHusk->object);

	if( pObj->common.nStrength <= 0 )
		return;

	orgdamage = damagetodo;
	damagetodo -= pObj->armor;
	if( damagetodo <= 0 )
		return;
	if( damagetodo >= pObj->common.nStrength )
		damagetodo = pObj->common.nStrength;
	pObj->common.nStrength -= damagetodo;

	if( pObj->common.nStrength <= 0 )
	{
		if( IS_LOCAL_ARMY(EXTRACT_ARMY(fromUID) ) )
			HuskDamageMessageSend( pHusk, pObj->common.nMaxStrength + pObj->armor, damagetype, *damageloc );
		DoExplosion( pHusk->object.common.position.x, pHusk->object.common.position.y, 
			EXPLOSION_FLASH_SMOKE_M_COMMAND, &SmallExplosion, 
   			DMGTYPE_OTHER_EXPLOSION, 0, NULL, 0, 0, DESTROYED );
		DestroyVehicleHusk( pHusk );
	}
	else
	{
		switch( damagetype )
		{
		case DMGTYPE_BULLET:
		case DMGTYPE_MISSILE:
			MakeChips( *damageloc, pHusk->object.cell.trans_table, 0 );
		}
		if( IS_LOCAL_ARMY(EXTRACT_ARMY(fromUID) ) )
			HuskDamageMessageSend( pHusk, orgdamage, damagetype, *damageloc );
	}
}


///========================================================================
//	Function:		ItemDamage
//	Description:	Apply known damage to item
///========================================================================
void ItemDamage(ITEM* pItem, int nDamage, int eDamageType, SPOINT* pFrom,UID fromUID)
{
	switch (ITEM_TYPE(pItem))
	{
		case ARMY_SARGE:
			SargeDamage((SARGE*)pItem, nDamage, eDamageType, pFrom,fromUID);
			break;
		case ARMY_TROOPER:
			TrooperDamage((TROOPER*)pItem, nDamage, eDamageType, pFrom,fromUID);
			break;
		case ARMY_VEHICLE:
			VehicleDamage((VEHICLE *)pItem, nDamage, eDamageType, pFrom,fromUID);
			break;
		case ARMY_ASSET:
		case ARMY_STRUCTURE:
		case ARMY_OBSTACLE:
			ObjectDamage((OBJECT *)pItem, nDamage, eDamageType, *pFrom, TRUE,fromUID);
			break;
		case ARMY_HUSK:
			HuskDamage( (THusk *)pItem, nDamage, eDamageType, pFrom, fromUID );
			break;
		default:
			return;
	}
}

char WEAPON_DAMAGE_TYPE[ARMY_LAST_WEAPON] =   // correlates with weapons above
{
	(char) -1, 							//ARMY_NO_WEAPON
	(char) DMGTYPE_BULLET, 				//ARMY_LIGHT_MACHINE_GUN
    (char) DMGTYPE_GRENADE,				//ARMY_GRENADE
    (char) DMGTYPE_FLAMED,				//ARMY_FLAME_THROWER
    (char) DMGTYPE_BAZOOKA,				//ARMY_BAZOOKA
    (char) DMGTYPE_MORTAR,				//ARMY_MORTAR
    (char) DMGTYPE_MISSILE,				//ARMY_LARGE_CANNON
    (char) DMGTYPE_BULLET,				//ARMY_MEDIUM_MACHINE_GUN
    (char) DMGTYPE_BULLET,				//ARMY_HEAVY_MACHINE_GUN
    (char) DMGTYPE_BULLET,				//ARMY_SARGE_GUN
    (char) DMGTYPE_BULLET,				//ARMY_AUTORIFLE
	(char) DMGTYPE_OTHER_EXPLOSION,		//ARMY_MINE
	(char) DMGTYPE_OTHER_EXPLOSION,		//ARMY_EXPLOSIVE
	(char) -1,							//ARMY_DETONATOR
	(char) -1,							//ARMY_LURE
	(char) -1,							//ARMY_FLAG
	(char) -1,							//ARMY_GREENFLAG
	(char) -1,							//ARMY_TANFLAG
	(char) -1,							//ARMY_BLUEFLAG
	(char) -1,							//ARMY_GRAYFLAG
	(char) -1,							//ARMY_SWEEPER
    (char) DMGTYPE_BULLET				//ARMY_GUARD_TOWER_RIFLE
};


///========================================================================
//	Function:		ObjectIsDestroyed()
//
//	Description:
//		returns TRUE if the Object is Destroyed 
//		
//
//	Input:			pObj			which object 
//					
//					
//
//	Ouput:			BOOL		
//
///========================================================================
BOOL ObjectIsDestroyed(OBJECT *pObj)
{

	int hps;
	OBJECT *curobj;

	if (((OBJECT*)pObj)->nextsubobject)
	{
		curobj=(OBJECT*)pObj;
		hps = curobj->common.nMaxStrength;
		do
		{
			if( !(curobj->triggers | TRIGGER_DESTROYED) )
				return 0;
			curobj=curobj->nextsubobject;
		}
		while (curobj!=pObj);
	}

	return( !(pObj->triggers | TRIGGER_DESTROYED) );
}


int DamageFromBehind(int nDamage, int direction, ITEM *pItem)	{
	if (IS_ARMY_OBJECT(ITEM_TYPE(pItem)))
		return nDamage;

	int left = (pItem->facing + (CIRCLE_UNITS/4)) % CIRCLE_UNITS;
	int right = (pItem->facing + (CIRCLE_UNITS*3/4)) % CIRCLE_UNITS;

	if (direction > left && direction < right)	{	// hit from behind
		nDamage *= 2;
	}

	return nDamage;
}


void DamageItemTriggerEvents(ITEM *pItem, int oldstrength, int newstrength, int maxstrength)
{
	if (pItem->eventNum && newstrength != oldstrength &&
        oldstrength == maxstrength)
    {
        EventTrigger(EVENT_ITEMDAMAGED, pItem->eventNum, pItem->nUniqueID, 0, 0);
	}
}

void DiedItemTriggerEvents(ITEM *pItem)
{
    EventTrigger(EVENT_ITEMDESTROYED, pItem->eventNum, pItem->nUniqueID, 0, 0);
}

void KillAttachedObjects(OBJECT *pObj)
{
	int i;
	char group;
	int	category;

	if (!(pObj->group & 0x80))
		return;

	group = pObj->group & 0x7F;

	category = pObj->category;
	if (the_map.num_objs[category])	{
		OBJECT	*optr = the_map.obj_type_list[category];

		// loop thru the objects of each type
		for (i=0; i<the_map.num_objs[category]; i++)	{
			if ((optr[i].group & 0x7F) == group)	{
//				AI_ITBL *pAiObjDefs;
//				int		damageindex;

				// kill this grouped object if it is not already dead
				if( optr[i].common.nStrength > 0 )
				{
					ObjectDamage(&(optr[i]), 5000, DMGTYPE_STRUCTURAL, optr[i].common.position, FALSE, 0);
/*
					damageindex = optr[i].damageindex;
					do
					{
						damageindex++;
						pAiObjDefs = AiGetObjectDefs( optr[i].category, optr[i].number, damageindex );
						if( !pAiObjDefs )
							break;
						if( pAiObjDefs->nHitPoints <= 0 )
							break;
					}	while( TRUE );
					Dmg_SetObjectDamage( &optr[i], pAiObjDefs, damageindex );
*/
				}
			}
		}
	}
}



#define DESTROYED_SOUND 0
#define BULLET_SOUND	1


ULONG objDamageSounds[][3]=
{
//	destroyed,	bullet hit,	
	{0,			ROCK_HIT,			0},	//"Rock",  
	{0,			0,					0},	//"Bush",
	{0,			BULLET_HIT_OBJECT,	0},	//"Tree",
	{0,			BULLET_HIT_OBJECT,	0},	//"BigTree",
	{0,			BULLET_HIT_OBJECT,	0},	//"FallenTree",
	{DESTROYED,	BULLET_HIT_OBJECT,	0},	//"Fence",
	{DESTROYED,	BULLET_HIT_OBJECT,	0},	//"Wall",
	{DESTROYED,	0,					0},	//"Bridge",
	{DESTROYED,	0,					0},	//"FootBridge",
	{0,			0,					0},	//"Mine",
	{DESTROYED,	BULLET_HIT_OBJECT,	0},	//"GunTurret",
	{DESTROYED,	BULLET_HIT_OBJECT,	0},	//"AAGun",
	{DESTROYED,	BULLET_HIT_OBJECT,	0},	//"Base",
	{DESTROYED,	BULLET_HIT_OBJECT,	0},	//"Auxbase",
	{0,			0,					0},	//"AirStrip",
	{0,			0,					0},	//"HeliPad",
	{0,			0,					0},	//"PrisonCamp",
	{DESTROYED,	BULLET_HIT_OBJECT,	0},	//"Building",
	{0,			0,					0},	//"PillBox",
	{0,			0,					0},	//"PowerPlant",
	{DESTROYED,	BULLET_HIT_OBJECT,	0},	//"Gate",
	{DESTROYED,	BULLET_HIT_OBJECT,	0},	//"WallGate",
	{0,			0,					0},	//"RadarBuilding",
	{0,			BULLET_HIT_OBJECT,	0},	//"Miscellaneous",
	{0,			0,					0},	//"Overpass"
	{0,			0,					0},	//"Sitems"
};

//				case DMGTYPE_BULLET:
//				case DMGTYPE_RUNOVER:
//				case DMGTYPE_STRUCTURAL:
//				case DMGTYPE_GRENADE:
//				case DMGTYPE_MORTAR:
//				case DMGTYPE_BAZOOKA:
//				case DMGTYPE_MISSILE:
//				case DMGTYPE_OTHER_EXPLOSION:
//				case DMGTYPE_FLAMED:

void AudioPlayObjectDamage(OBJECT *pObj, int damagetype, int kind)	{
	int sound;

	if ( pObj->group != 0 && !(pObj->group & 0x80) )
		return;

	if (pObj->xtriggers & XTRIGGER_BRANCH)
		return;

	switch (kind)	{
		case DAMAGED_KIND:
			switch (damagetype)	{
				case DMGTYPE_BULLET:
					sound = objDamageSounds[pObj->category][BULLET_SOUND];
					if (sound)
						AudioPlayItem(sound, (ITEM *) pObj);
					break;
//				case DMGTYPE_RUNOVER:
//				case DMGTYPE_STRUCTURAL:
//				case DMGTYPE_GRENADE:
//				case DMGTYPE_MORTAR:
//				case DMGTYPE_BAZOOKA:
//				case DMGTYPE_MISSILE:
//				case DMGTYPE_OTHER_EXPLOSION:
			}
			break;
		case NO_DAMAGE_KIND:
			if (damagetype == DMGTYPE_BULLET)	{
				switch (pObj->category)	{
					case ROCK:
						AudioPlayItem(ROCK_HIT, (ITEM *) pObj);
						break;
				}
			}
			break;
		case DESTROYED_KIND:
			sound = objDamageSounds[pObj->category][DESTROYED_SOUND];
			if (sound)
				AudioPlayItem(sound, (ITEM *) pObj);
			break;
	}
}
