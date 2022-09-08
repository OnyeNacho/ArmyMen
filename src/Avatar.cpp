/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Avatar.cpp $
//
//	DESCRIPTION:	Trooper avatar animation
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Thursday, June 26, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Avatar.cpp 103   4/14/98 12:58p Nrobinso $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/Avatar.cpp $
//  
//  103   4/14/98 12:58p Nrobinso
//  mine blowing up based on animtime not systime
//  
//  102   4/12/98 3:36p Nrobinso
//  improve fire move to
//  
//  101   4/10/98 11:45a Nrobinso
//  add a fire now option for sarge
//  
//  100   4/10/98 1:33a Nrobinso
//  clear anim callback
//  
//  99    4/09/98 4:43p Nrobinso
//  play with weapon reset to fix firing problems
//  
//  98    4/08/98 5:29p Phu
//  don't killk sarge if he is untrafficable
//  
//  97    4/03/98 1:07p Nrobinso
//  talk is a pose
//  
//  96    4/03/98 12:43p Nrobinso
//  fix firing pose problems
//  
//  95    4/03/98 12:04p Nrobinso
//  remove no ammo
//  
//  94    4/02/98 2:54p Nrobinso
//  change SetFire for avatars
//  
//  93    3/31/98 4:47p Bwilcox
//  
//  92    3/31/98 4:42p Bwilcox
//  mp stepping on mines can be done by any local army, not just armyplayer
//  
//  91    3/30/98 12:30p Phu
//  5 sec delay before interaction
//  
//  90    3/27/98 8:20p Nrobinso
//  fix troopers not firing
//  
//  89    3/27/98 7:23p Nrobinso
//  remove currentpose (confusing)
//  
//  88    3/27/98 3:18p Bwilcox
//  make scar called explicitly for mines
//  
//  87    3/27/98 11:36a Phu
//  avatarinair
//  
//  86    3/26/98 9:35p Phu
//  strategy items: prone, roll & dive protection
//  
//  85    3/26/98 7:33p Nrobinso
//  fix fire anims
//  
//  84    3/26/98 3:35p Bwilcox
//  
//  83    3/26/98 2:59p Bwilcox
//  
//  82    3/26/98 1:50p Nrobinso
//  minesweeper doesn't kneel to fire
//  
//  81    3/26/98 9:03a Bwilcox
//  
//  80    3/26/98 6:41a Bwilcox
//  change in sweeper behavior
//  
//  79    3/24/98 5:58p Phu
//  3 second delay before you allow someone to pick up an item
//  
//  78    98/03/24 17:39 Dmaynard
//  fixing immediate pickup when sarge dies with 2 things
//  
//  77    3/20/98 10:28a Bwilcox
//  fixing actions table
//  
//  76    3/19/98 7:45p Nrobinso
//  flamethrower must kneel to fire
//  
//  75    3/18/98 5:27p Nrobinso
//  sweeper is a kneeling weapon
//  
//  74    3/17/98 6:16p Bwilcox
//  sargefind may now safely return null
//  
//  73    3/17/98 11:54a Nrobinso
//  do auto switching of fire poses
//  
//  72    3/16/98 6:33p Nrobinso
//  remove stationary avatar commands
//  
//  71    3/16/98 3:53p Nrobinso
//  check for pose if firing
//  
//  70    3/16/98 1:20p Bwilcox
//  removing unneeded checks for ARMY_OBSTACLE when category is
//  clearly unique.
//  
//  69    3/16/98 12:07p Nrobinso
//  remove avatar stationary and pass a pose into avatar calls
//  
//  68    98-03-13 21:50 Dmaynard
//  make sure mines are made visble/invisble properly
//  
//  67    3/13/98 11:57a Bwilcox
//  blitz no longer stops flag pickup
//  
//  66    3/13/98 11:32a Nrobinso
//  playing with directions doesn't touch the owning item
//  
//  65    3/11/98 4:41p Phu
//  don't crash if mine doesn't have an owner
//  
//  64    98-03-11 9:39 Dmaynard
//  fixing trooper moving to illegal bug
//  
//  63    3/10/98 12:27p Bwilcox
//  6 second mine delay now
//  
//  62    3/10/98 7:14a Bwilcox
//  
//  61    3/10/98 7:06a Bwilcox
//  sarge gets credit for mine kills
//  
//  60    98-03-09 10:34 Dmaynard
//  added talk into text list
//  
//  59    3/03/98 4:59p Nrobinso
//  fix roll & walk back oddities
//  
//  58    3/01/98 8:20p Nrobinso
//  add prone turn anim
//  
//  57    2/27/98 2:53p Nrobinso
//  remove unsued code
//  
//  56    2/20/98 1:16p Nrobinso
//  fix up sounds
//  
//  55    2/16/98 12:03p Phu
//  pass along fromUID with explosions
//  
//  54    2/06/98 12:43p Bwilcox
//  
//  53    2/05/98 3:27p Bwilcox
//  sarge doesnt die on untrafficle unless he was stationary
//  
//  52    2/04/98 4:43p Phu
//  kill sarge when untrafficable
//  
//  51    2/04/98 11:48a Phu
//  lure item
//  
//  50    2/04/98 11:32a Phu
//  mines will now always blow up in single player
//  
//  49    2/04/98 9:25a Bwilcox
//  fixing actions text list to match header file
//  
//  48    2/03/98 3:22p Bwilcox
//  sargegetactiveweapon now takes arg,
//  fixed avatar mine interactions
//  
//  47    2/03/98 11:19a Bwilcox
//  sarge sweeping is immune to mines
//  
//  46    2/02/98 8:39a Nrobinso
//  modify roll directions
//  
//  45    1/30/98 2:07p Nrobinso
//  remove ActionFrame and AVATAR_THROW
//  
//  44    1/29/98 10:58a Nrobinso
//  put in sarge test in AvatarPerform
//  
//  43    1/28/98 4:22p Nrobinso
//  pass facing to SetFire
//  
//  42    1/28/98 3:14p Nrobinso
//  stop a fcaing change when firing flag is locked
//  
//  41    1/27/98 4:27p Phu
//  fix mines for one-player
//  
//  40    1/27/98 2:47p Phu
//  fix one-player mines to always blow up
//  
//  39    1/27/98 10:32a Phu
//  mines are blown up by placer of the mine charge
//  
//  38    1/22/98 4:25p Phu
//  avatar last complete fix
//  
//  37    1/22/98 3:53p Phu
//  take out 1.5sec delay on completion, localize switching viewpoint back
//  to sarge
//  
//  36    1/22/98 10:02a Bwilcox
//  fixing ordering problem with mine stepping on
//  
//  35    1/21/98 1:52p Phu
//  check in for bruce - mine removal function
//  
//  34    1/17/98 9:45p Nrobinso
//  keep a reversed flag so we can tell when sarge is backwards
//  
//  33    1/17/98 7:20p Nrobinso
//  commented out unused variable
//  
//  32    1/14/98 6:02p Dmaynard
//  
//  31    98/01/14 17:54 Dmaynard
//  
//  30    1/13/98 6:54p Phu
//  fix paratrooper pick-up
//  
//  29    1/13/98 3:49p Phu
//  quest items
//  
//  28    1/13/98 4:02p Nrobinso
//  allow avatars to die
//  
//  27    1/13/98 1:06p Nrobinso
//  change avatarwouldmove to to be simpler for full animation sequence
//  
//  26    1/08/98 4:19p Phu
//  air support items/paratrooper initialization
//  
//  25    1/07/98 5:12p Nrobinso
//  add AvatarSetFacing
//  
//  24    1/07/98 3:20p Nrobinso
//  add AvatarCurrentPose; changed AvatarPose to take only the avatar
//  pointer; AvatarPoseChange also takes an action
//  
//  23    1/05/98 3:37p Phu
//  Mines get damage done from aai file
//  
//	...
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Header files
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "army.h"
#include "aiaccess.h"
#include "disp.h"
#include "GameFlow.h"
#include "comm.h"
#include "item.h"
#include "map.h"
#include "sarge.h"
#include "trooper.h"
#include "explosions.h"
#include "wobject.h"
#include "weapon.h"
#include "mainfrm.h"
#include "input.h"
#include "commands.h"
#include "vehicle.h"
#include "sounds.h"
#include "avatar.h"
#include "aibtank.h"
/////////////////////////////////////////////////////////////////////////////
// Data files
/////////////////////////////////////////////////////////////////////////////
#include "avatar.dat"


extern long user_action;

    
/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////
static AVATAR_STATE_CHANGE *AvatarStateChange(AVATAR* avatar, ACTION action);
inline static SHORT AvatarCommandChange(AVATAR* avatar);
static ITEM* AvatarFind(LONG nUniqueID);
static void AvatarFire(ITEM *pItem);
static void AvatarNoFire(ITEM *pItem);
static void AvatarAnimFire(ANIM *pAnim);
static void AvatarSetFire(ITEM *pItem, int facing);
static void AvatarSetFireUpdate(ITEM *pItem, int facing);
static inline void AvatarClearFire(ITEM *pItem);
static SHORT AvatarPlayWithDirections(ANIM *pAnim, int command, SHORT facing);

/////////////////////////////////////////////////////////////////////////////
// Data Types
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Local Data
/////////////////////////////////////////////////////////////////////////////
char* actions[]={
"run","walk","walkback","shuffle",
"readyfire","fire","firestationary","firenow","rollleft",
 "rollright","dive","kneel","stand","prone","talk",
"melt","shot","squash","invisible","stopnow",
"explode","actions??","inactivate"
};

/////////////////////////////////////////////////////////////////////////////
// Code
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// allocate memory for avatar and associated anim data, and initialize it all
// initialized to an invisible, non-moving animation         
/////////////////////////////////////////////////////////////////////////////
AVATAR* AvatarCreate(UID id)	{

	// should be ARMY_TROOPER
	ASSERT(OBJTYPE(id) == ARMY_TROOPER || OBJTYPE(id) == ARMY_SARGE);

	AVATAR* avatar = (AVATAR*) malloc(sizeof(AVATAR));
	ZeroMemory(avatar, sizeof(AVATAR));
#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): avatar [%s : %d]\n", ( sizeof(AVATAR) ), __FILE__, __LINE__ );
#endif

	avatar->eType = SUB1TYPE(id);	// trooper type (e.g. rifle man or grenade man)

	avatar->avatar_action = AVATAR_INVISIBLE;
	avatar->current_action = avatar->avatar_action;
	avatar->avatar_facing = DIRECTION_UP;
	avatar->facing = avatar->avatar_facing;
	avatar->current_command = INVISIBLE_COMMAND;

	avatar->pAnimation = (ANIM*) malloc( sizeof(ANIM) );
#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): avatar animation [%s : %d]\n", ( sizeof(ANIM) ),  __FILE__, __LINE__ );
#endif

	// clear the animation structure and set some internal pointers
	AnimInit( 255, 255, avatar->pAnimation, OL_ORDEREDLAYER );

	// now apply the sprite associated with this trooper avatar
	// default to position 0,0
	AnimSet( avatar->pAnimation, 
			0, 0,
			TrooperCommands[ avatar->eType ], 
			avatar->current_command,
			avatar->avatar_facing,
			SEQUENCE_VELOCITY);

	// required for anim callback and for collision detection
	ITEM *pOwner = AvatarFind(id);
//	ASSERT(pOwner);
	AnimSetOwner(avatar->pAnimation, pOwner);

	// set the color translation for this trooper
	avatar->pAnimation->trans_table = UnitColorTable((ARMY_TYPE) EXTRACT_ARMY(id));

    return avatar;
}


void  AvatarSetType(AVATAR* avatar, int eType)	{
	avatar->eType = eType;
	AnimSetCommandList(avatar->pAnimation, TrooperCommands[ avatar->eType ]);
}

void AvatarDestroy(AVATAR* avatar)	
{
	if (avatar)	
	{
		if (avatar->pAnimation)	
		{
			AnimDelete( avatar->pAnimation );
			free( avatar->pAnimation );
			avatar->pAnimation = NULL;
		}
		free(avatar);
	}
}	//	AvatarDestroy


void  AvatarSetPosition(SPOINT location, AVATAR* avatar)	{
	AnimSetPosition(avatar->pAnimation, location.x, location.y, SAME_FACING);
}

void  AvatarSetFacing(int facing, AVATAR* avatar)	{
	AnimForceFacing(avatar->pAnimation, facing);
	avatar->avatar_facing = facing;
	avatar->facing = avatar->facing;
}


//  can the object be picked up by the actor?  NOTE: return -1 if same item
int isPickupable( ITEM *object, SARGE *actor )
{
	LEGION *pLegion;

		if( actor->prevPickup == object )
			return -1;

		if( ((OBJECTSTRUCT *)object)->category == SPECIAL_ITEMS )
        {
			if( !object->pWeapon )
				return 0;

			if( gpGame->dwAnimTime - ((OBJECTSTRUCT *)object)->timer < 5000 )
				return 0;

			((OBJECTSTRUCT *)object)->timer = gpGame->dwAnimTime;

			// one use items - pickup only if useful
			switch( object->pWeapon->eWeapon )
			{
			case ARMY_MEDKIT:
				if( actor->common.nStrength >= actor->common.nMaxStrength )
					return 0;
				break;
			case ARMY_AIRSTRIKE:
				pLegion = ArmyGetLegion( ITEM_ARMY(actor) );
				if( pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE] >= 3 )
					return 0;
				break;
			case ARMY_PARATROOPERS:
				pLegion = ArmyGetLegion( ITEM_ARMY(actor) );
				if( pLegion->AirResources[ARMY_RESOURCE_PARATROOPERS] >= 3 )
					return 0;
				break;
			case ARMY_RECON:
				pLegion = ArmyGetLegion( ITEM_ARMY(actor) );
				if( pLegion->AirResources[ARMY_RESOURCE_AIR_RECON] >= 3 )
					return 0;
				break;
			}

            #ifdef JUNK
            // in old blitz you couldnt pick up your own flag.
            // in new blitz you can.
            if (gpComm->ColorFromIndex(ITEM_ARMY(actor)) == ARMY_GREEN &&
                object->pWeapon->eWeapon == ARMY_GREENFLAG) return 0;
            if (gpComm->ColorFromIndex(ITEM_ARMY(actor)) == ARMY_TAN &&
                object->pWeapon->eWeapon == ARMY_TANFLAG) return 0;
            if (gpComm->ColorFromIndex(ITEM_ARMY(actor)) == ARMY_BLUE &&
                object->pWeapon->eWeapon == ARMY_BLUEFLAG) return 0;
            if (gpComm->ColorFromIndex(ITEM_ARMY(actor)) == ARMY_GRAY &&
                object->pWeapon->eWeapon == ARMY_GRAYFLAG) return 0;
            #endif
         
			// don't pickup vehicle weapons
			if( object->pWeapon->eWeapon >= ARMY_LARGE_CANNON && object->pWeapon->eWeapon <= ARMY_HEAVY_MACHINE_GUN )
				return 0;
			return 1;
        }
	return 0;
}	//  isPickupable


static void BlowUpMine(OBJECT* pObject)
{
       int damage;
	   SPOINT position;
	   position = pObject->common.position;
       damage = AIinfo.weaponTables[ARMY_MINE].damage.nDamage;
       // do explosion can blow up the mine, so remove 1st
       UnplaceMine(pObject);
       // credit sarge with the damage because he laid the mine
       SARGE* pSarge;
	   int id;
       pSarge = SargePointer(OBJECT_OWNER(pObject));
	   if( pSarge )
		   id = ITEM_UID(pSarge);
	   else
		   id = 0;
       DoExplosion(position.x,position.y,  EXPLOSION_FLASH_COMBUSTION_M_COMMAND, &SmallExplosion,
           DMGTYPE_OTHER_EXPLOSION, damage, NULL, TRUE,id, MINE_EXPLODE );
}

static void MineInteract (OBJECT* pObject, SARGE* pSarge)
{
    if (pSarge )
    {
        int eArmy;
        eArmy = ITEM_ARMY(pSarge);
        int weapon;
        weapon = SargeGetActiveWeapon(eArmy);

        // any sarge sweeping it sees it, SOME CLEAR IT
        if (GetSargeWeapon(weapon) == ARMY_SWEEPER)
        {
            // make it visible
            if( pObject->cell.flags & ANIM_FLAG_INVISIBLE )
            {
                pObject->cell.flags &= ~ANIM_FLAG_INVISIBLE;
                pObject->triggers &= ~TRIGGER_INVISIBLE;
                MoveDispXObject( &(pObject->cell), TRUE );
            }

            // any sarge on his machine can pick up mine
            if (eArmy == ARMY_PLAYER && user_action & DO_FIRE )
            {
                UnplaceMine(pObject);      // remove the mine
            }

           // any sarge sweeping is safe from mines
           return;
        }
   }


   // avatar (sarge or trooper) stepping on live mine on our machine
   if(IS_LOCAL_ARMY(pObject->owner) & (gpGame->dwAnimTime - pObject->timer) > 6000 )
   {
       BlowUpMine(pObject);
   }
}

static void CheckLocalMine(SARGE* pSarge,IPOINT tile,int close)
{
	ITEM * pItemList;
    OBJECT* pObject;
    SPOINT pt;
    pt = CenterPointFromTile(tile);
    //avatar finds stuff where he is
	pItemList = GetObjectsIntersectPoint(&pt);
	while( pItemList != NULL )
	{
        // something interacting with a mine object?
        pObject = (OBJECTSTRUCT *)pItemList;
		if (pObject->category == EXPLOSIVES && pObject->number == ARMY_MINE)
        {
            // make it visible
            if( pObject->cell.flags & ANIM_FLAG_INVISIBLE )
            {
                pObject->cell.flags &= ~ANIM_FLAG_INVISIBLE;
                pObject->triggers &= ~TRIGGER_INVISIBLE;
                MoveDispXObject( &(pObject->cell), TRUE );
            }

            // any sarge on his machine can destroy close mine also
            if (ITEM_ARMY(pSarge) == ARMY_PLAYER && user_action & DO_FIRE )
            {
   				BlowItem((ITEM*)pObject);
				GenerateFlashBurn(pObject->common.position.x,
                                pObject->common.position.y,0);
				UnplaceMine(pObject);
            }

        }
		pItemList = pItemList->next;
	}
}

static void CheckWideMines(SARGE* pSarge)
{
    IPOINT tile;
    SPOINT pt;
    SargeFiringPosition(pSarge,&pt); // where is sweeper centered
    tile = ENCODE_IPOINT(pt.x,pt.y);

    // block8 around it
    CheckLocalMine(pSarge,tile+LEFT1,TRUE);
    CheckLocalMine(pSarge,tile+RIGHT1,TRUE);
    CheckLocalMine(pSarge,tile+UP1,TRUE);
    CheckLocalMine(pSarge,tile+DOWN1,TRUE);
    CheckLocalMine(pSarge,tile+LEFT1+UP1,TRUE);
    CheckLocalMine(pSarge,tile+RIGHT1+UP1,TRUE);
    CheckLocalMine(pSarge,tile+LEFT1+DOWN1,TRUE);
    CheckLocalMine(pSarge,tile+RIGHT1+DOWN1,TRUE);

    //4 center pts on ring2
    CheckLocalMine(pSarge,tile+LEFT1+LEFT1,FALSE);
    CheckLocalMine(pSarge,tile+RIGHT1+RIGHT1,FALSE);
    CheckLocalMine(pSarge,tile+UP1+UP1,FALSE);
    CheckLocalMine(pSarge,tile+DOWN1+DOWN1,FALSE);

    // 8 on wider ring
    CheckLocalMine(pSarge,tile+LEFT1+LEFT1+UP1,FALSE);
    CheckLocalMine(pSarge,tile+LEFT1+UP1+UP1,FALSE);
    CheckLocalMine(pSarge,tile+RIGHT1+RIGHT1+UP1,FALSE);
    CheckLocalMine(pSarge,tile+RIGHT1+UP1+UP1,FALSE);
    CheckLocalMine(pSarge,tile+LEFT1+LEFT1+DOWN1,FALSE);
    CheckLocalMine(pSarge,tile+LEFT1+DOWN1+DOWN1,FALSE);
    CheckLocalMine(pSarge,tile+RIGHT1+RIGHT1+DOWN1,FALSE);
    CheckLocalMine(pSarge,tile+RIGHT1+DOWN1+DOWN1,FALSE);
}

void AvatarInteract( AVATAR * avatar )
{
	ITEM * pItemList;
	int    i;
	BOOL   itemHere = FALSE;
	SARGE *pSarge;
	SPOINT at;
	OBJECTSTRUCT *pObject;
	pSarge = (SARGE*)(avatar->pAnimation->pOwner);
    if (ITEM_TYPE(pSarge) != ARMY_SARGE) pSarge = NULL;
	at = avatar->pAnimation->world_pos;

    // sarge damage on collapsing stuff if he is standing still
	pItemList = GetObjectsIntersectPoint( &at );
/*	Don't kill sarge if he is untrafficable
	if (pSarge != NULL)
	{
		if( (pSarge->pendingAction == AVATAR_KNEEL ||
             pSarge->pendingAction == AVATAR_STAND ||
             pSarge->pendingAction == AVATAR_FIRE_STATIONARY) &&
             IS_LOCAL_ITEM(pSarge) &&
             isSargeUntrafficable(avatar->pAnimation->world_pos, pItemList ))
				SargeDamage(pSarge, pSarge->common.nStrength, DMGTYPE_RUNOVER, 
					&at,pSarge->common.nUniqueID);
	}
*/
    //avatar finds stuff where he is
	while( pItemList != NULL )
	{
		// sarge is always there, so lets optimize this. 

		if (pItemList == (ITEM *) pSarge)
		{
			pItemList = pItemList->next;
			continue;
  		}

        // if sarge and not in a vehicle and he hasnt just died, dropping all
        // then he can pick up stuff
		if( pSarge && !pSarge->pVehicle && pSarge->common.nStrength)
		{
			i = isPickupable( pItemList, pSarge );
			if( i == 1 )
			{
				SargePickupWeapon( pSarge, pItemList );
				itemHere = TRUE;
			}
			else if( i < 0 )
			{
				itemHere = TRUE;
			}
		}

        // something interacting with a mine object?
        pObject = (OBJECTSTRUCT *)pItemList;
		if (pObject->category == EXPLOSIVES && pObject->number == ARMY_MINE)
        {
            MineInteract(pObject,pSarge); // psarge is null if trooper
        }
		pItemList = pItemList->next;
	}

    // a mine sweeper sees objects a lot farther out for dealing with mines
	int weapon;
    weapon =  (pSarge) ? pSarge->weapon_index : 0;
    if (pSarge && GetSargeWeapon(weapon) == ARMY_SWEEPER)
        CheckWideMines(pSarge);

	if( pSarge && !itemHere )
		pSarge->prevPickup = NULL;

}	//	AvatarInteract


// anim updates are done here
int AvatarPerform(ACTION action, ACTION pose, int facing, BOOL doAction, AVATAR* avatar)	{
	SHORT command;
	int	retval;
	int animfacing;		// phu
	AVATAR_STATE_CHANGE *change;
	ANIM *pAnim = avatar->pAnimation;
	ITEM *pOwner = (ITEM *) pAnim->pOwner;

	ASSERT(pose == AVATAR_STAND || pose == AVATAR_KNEEL || pose == AVATAR_PRONE || pose == AVATAR_TALK);

	if (action == AVATAR_FIRE || action == AVATAR_FIRE_STATIONARY || action == AVATAR_FIRE_NOW)	{
		
		switch(pOwner->pWeapon->eWeapon)
		{
			case ARMY_MORTAR:
			case ARMY_MINE:
			case ARMY_EXPLOSIVE_WEAPON:
				if (pose != AVATAR_KNEEL)
					pose = AVATAR_KNEEL;
				break;
			case ARMY_GRENADE:
			case ARMY_FLAME_THROWER:
			case ARMY_BAZOOKA:
				if (pose == AVATAR_PRONE)
					pose = AVATAR_KNEEL;
				break;
		}

		if (pose != AvatarPose(avatar))
			action = pose;
	}

	change = AvatarStateChange(avatar, action);
	avatar->avatar_action = action;					// action that was requested
	command = change->next_command;

 	if (change->perform)
		retval = AVATAR_PERFORMING;
	else
		retval = AVATAR_READYING;
	
	if (pOwner->fireFlag)
		facing = pOwner->fireDirection;

	// walk backwards or roll
	animfacing = AvatarPlayWithDirections(pAnim, command, facing);

	switch (action)
	{
		case AVATAR_FIRE:
		case AVATAR_FIRE_STATIONARY:
		case AVATAR_FIRE_NOW:
			if (WeaponFireTime(pOwner->pWeapon))	{
				AvatarSetFire(pOwner, animfacing);

				if (command == SAME_COMMAND)
				{
					WeaponFireReset(pOwner->pWeapon);	// reload time
					AvatarFire(pOwner);
				}
				else
				{
					AnimCallback(pAnim, AvatarAnimFire, USE_ACTION_FRAME, change->match_command );
				}
			}
			else	{
				AvatarSetFireUpdate(pOwner, animfacing);

				if (action == AVATAR_FIRE_STATIONARY)
				{
					if (avatar->current_action != AVATAR_READY_FIRE)
					{
						action = AVATAR_READY_FIRE;
						change = AvatarStateChange(avatar, action);
						command = change->next_command;
					}
					else
						command = SAME_COMMAND;
				}
				else
					command = SAME_COMMAND;

				retval = AVATAR_READYING;
			}
			break;
		default:
			AvatarClearFire(pOwner);
			break;
	}


	if ( (action >= AVATAR_DIE_FIRST) && (action <= AVATAR_DIE_LAST))	{
		if (command != pAnim->current_command)	{
			AnimActivate( pAnim, NO_ACTIVATE_LINKS );
			AnimForceCommand(pAnim, command, animfacing);
		}
	}
	else if ( (action >= AVATAR_INTERRUPT_FIRST) && (action <= AVATAR_INTERRUPT_LAST))	{
		AnimActivate( pAnim, NO_ACTIVATE_LINKS );
		AnimForceCommand(pAnim, command, animfacing);
	}
	else if (action == AVATAR_INACTIVATE)	{
		AnimInactivate( pAnim, INACTIVATE_LINKS);
		AnimMove(pAnim, FALSE);
		return AVATAR_PERFORMING;
	}
	else {
		if (command == PRONE_COMMAND)	{
			int facing_index = INDEX_FACING(animfacing, pAnim->pSeq);

			if ( pAnim->facing_index != facing_index)	{
				int diff = NormalizeFacingSubtract(facing_index, pAnim->facing_index);
				if (diff < CIRCLE_UNITS/2)	{
					command = PRONE_INPLACE_L;
				}
				else	{
					command = PRONE_INPLACE_R;
				}
			}
		}

		AnimActivate( pAnim, NO_ACTIVATE_LINKS );
		AnimCommand(pAnim, command, animfacing);
	}
	
	AnimUpdate(pAnim);
	AnimMove(pAnim, FALSE );
	AvatarInteract( avatar );

	pAnim->flags &= ~ANIM_FLAG_INVISIBLE;
	if (pOwner->bItemFlags & ITEM_INVISIBLE)
		pAnim->flags |= ANIM_FLAG_INVISIBLE;

	avatar->current_command = pAnim->current_command;
	avatar->facing = facing;
	avatar->current_action = action;
	avatar->avatar_facing = facing;

	return retval;
}

BOOL AvatarNearlyReadyTo(ACTION action, int facing, AVATAR* avatar)	{
	AVATAR_STATE_CHANGE *change;

	if ( (action >= AVATAR_INTERRUPT_FIRST) && (action <= AVATAR_INTERRUPT_LAST))	{
		return TRUE;
	}

	change = AvatarStateChange(avatar, action);
		
	return (change->perform);
}


BOOL AvatarLastCompleted(ACTION action, AVATAR* avatar)	{
	AVATAR_STATE_CHANGE *change;

	change = AvatarStateChange(avatar, action);

	if( action == AVATAR_DIE_EXPLODE )
		return TRUE;

    ANIM* pAnim = avatar->pAnimation;

	SEQUENCE *pSeq = pAnim->pSeq;
	if( !pSeq )
		return FALSE;

	if( (change->next_command == LAST_FRAME_COMMAND) || (change->match_command == avatar->current_command) )
		if( pAnim->current_frame == pSeq->frames - 1 )
			return TRUE;

	return FALSE;
}


SPOINT AvatarWouldMoveTo(ACTION action, ACTION pose, int facing, BOOL whole_cycle, AVATAR* avatar)	{
	SHORT command;
	AVATAR_STATE_CHANGE *change;
	POINT pt;
	int animfacing;
	ANIM *pAnim = avatar->pAnimation;
	ITEM *pOwner = (ITEM *) pAnim->pOwner;

	if ( (action >= AVATAR_INTERRUPT_FIRST) && (action <= AVATAR_INTERRUPT_LAST))
        return AvatarPosition(avatar);

	if (action == AVATAR_FIRE || action == AVATAR_FIRE_STATIONARY || action == AVATAR_FIRE_NOW)	{
		switch(pOwner->pWeapon->eWeapon)
		{
			case ARMY_MORTAR:
			case ARMY_MINE:
			case ARMY_EXPLOSIVE_WEAPON:
				if (pose != AVATAR_KNEEL)
					pose = AVATAR_KNEEL;
				break;
			case ARMY_GRENADE:
			case ARMY_FLAME_THROWER:
			case ARMY_BAZOOKA:
				if (pose == AVATAR_PRONE)
					pose = AVATAR_KNEEL;
				break;
		}

		if (pose != AvatarPose(avatar))
			action = pose;
	}

	change = AvatarStateChange(avatar, action);
	command = change->next_command;

	if (pOwner->fireFlag)
		facing = pOwner->fireDirection;

	animfacing = AvatarPlayWithDirections(avatar->pAnimation, command, facing);

	switch (action)
	{
		case AVATAR_FIRE:
		case AVATAR_FIRE_STATIONARY:
		case AVATAR_FIRE_NOW:
			if (!WeaponFireTime(pOwner->pWeapon))	{
				if (action == AVATAR_FIRE_STATIONARY)
				{
					if (avatar->current_action != AVATAR_READY_FIRE)
					{
						action = AVATAR_READY_FIRE;
						change = AvatarStateChange(avatar, action);
						command = change->next_command;
					}
					else
						command = SAME_COMMAND;
				}
				else
					command = SAME_COMMAND;
			}
			break;
	}



	if (whole_cycle)
		pt = AnimFigureMove(avatar->pAnimation, command, animfacing, CONTINUE_CMD);
	else
		pt = AnimFigureMove(avatar->pAnimation, command, animfacing, ONE_STEP_CMD);

    avatar->x = avatar->pAnimation->world_pos.x + pt.x;
    avatar->y = avatar->pAnimation->world_pos.y + pt.y;
    SPOINT ptnew;
    ptnew.x = avatar->x;
    ptnew.y = avatar->y;
    return ptnew;
}

static AVATAR_STATE_CHANGE *AvatarStateChange(AVATAR* avatar, ACTION action)	{
	AVATAR_COMMAND_RESULT *command_result;
	AVATAR_STATE_CHANGE *pChgDefault;
	AVATAR_STATE_CHANGE *pChg;
	int	offset = 0;

	command_result = avatar_changes[avatar->eType];

	pChgDefault = command_result[avatar->current_command].pDefaultStateChange;
	pChg = command_result[avatar->current_command].pStateChange;

	if (pChgDefault)	{
		if (pChgDefault[action].next_command != SPECIAL_COMMAND)	{
			pChg = pChgDefault;
		}
		else	{
			offset = (int) pChgDefault[action].perform;
		}
	}

	pChg -= offset;
	return &pChg[action];
}

ACTION AvatarPose(AVATAR* avatar)	{
	AVATAR_COMMAND_RESULT *command_result;

	command_result = avatar_changes[avatar->eType];
		
	return((ACTION) command_result[avatar->current_command].pose);
}

ACTION AvatarPoseChange(ACTION action, AVATAR* avatar)	{
	return (AvatarPose(avatar));
}

inline static SHORT AvatarCommandChange(AVATAR* avatar)	{
	return(final_chg[avatar->current_command].next_command);
}

static ITEM* AvatarFind(LONG nUniqueID)
{
	if (OBJTYPE(nUniqueID) == ARMY_TROOPER)
		return ((ITEM *) TrooperFind(nUniqueID));
	else if (OBJTYPE(nUniqueID) == ARMY_SARGE)	{
        ITEM* pItem ;
        pItem = ((ITEM *) SargeFind(nUniqueID));
        ASSERT(pItem);
        return pItem;
	}
	else	{
		TRACE("Not a legitimate avatar target\n");
		ASSERT(0);
		return NULL;
	}
}

static void AvatarAnimFire(ANIM *pAnim)
{
	ITEM *pOwner = (ITEM*) pAnim->pOwner;

	WeaponFireReset(pOwner->pWeapon);	// reload time
	AvatarFire(pOwner);
	AnimCallbackClear(pAnim);
}


static void AvatarFire(ITEM *pItem)
{	
	AvatarClearFire(pItem);
	if (ITEM_TYPE(pItem) == ARMY_TROOPER)	{
		TrooperFireWeapon((TROOPER*) pItem);
	}
	else	{
		SargeFireWeapon((SARGE *) pItem);
	}
//	TRACE("Avatar Fire\n");
}

static void AvatarNoFire(ITEM *pItem)
{
	ASSERT(ITEM_TYPE(pItem) != ARMY_TROOPER);

	SargeNoFireWeapon((SARGE *) pItem);
}


static void AvatarSetFire(ITEM *pItem, int facing)
{
    if (IS_LOCAL_ITEM(pItem))	{
		if (ITEM_TYPE(pItem) == ARMY_SARGE)	{
			SargeSetFire((SARGE *) pItem, facing);
		}
		else if (!pItem->fireFlag)	{
			pItem->fireFlag = TRUE;
			if (ITEM_TYPE(pItem) == ARMY_TROOPER)	{
				TrooperSetFire((TROOPER*) pItem, facing);
			}
		}
	}
}

static void AvatarSetFireUpdate(ITEM *pItem, int facing)
{
    if (IS_LOCAL_ITEM(pItem))	{
		if (ITEM_TYPE(pItem) == ARMY_SARGE)	{
			SargeSetFire((SARGE *) pItem, facing);
		}
		else	{
			pItem->fireFlag = TRUE;
			if (ITEM_TYPE(pItem) == ARMY_TROOPER)	{
				TrooperSetFire((TROOPER*) pItem, facing);
			}
		}
	}
}

static inline void AvatarClearFire(ITEM *pItem)
{
	ASSERT(pItem);
	pItem->fireFlag = FALSE;
}

#if _DEBUG
char *AvatarActionDBName(ACTION action)	{
	if (action == AVATAR_INACTIVATE)
		return "inactive";
	else
		return actions[action];
}
#endif


#define PRONE_HEIGHT	4
#define KNEEL_HEIGHT	6
#define STAND_HEIGHT	8

///========================================================================
//	Function:		AvatarHitByMissile
//	Description:	will this avatar stop a missile and take damage from it?
///========================================================================

BOOL AvatarHitByMissile(ACTION pose, SHORT height)
{
	int i;

	i = AvatarHeight( pose );
	if( (i >= 0) && (i >= height) )
		return TRUE;
	else
		return FALSE;
}	//	AvatarHitByMissile


BOOL AvatarInAir( AVATAR *pAvatar )
{
	if( !pAvatar )
		return FALSE;
	switch( pAvatar->current_action )
	{
	case AVATAR_ROLL_LEFT:
	case AVATAR_ROLL_RIGHT:
	case AVATAR_DIVE:
		return TRUE;
		break;
	default:
		return FALSE;
	}
}


int	AvatarHeight( ACTION pose )
{
	switch( pose )
	{
	case AVATAR_KNEEL:
		return( KNEEL_HEIGHT );
	case AVATAR_STAND:
		return( STAND_HEIGHT );
	case AVATAR_PRONE:
		return( PRONE_HEIGHT );
	default:
		return( -1 );
	}
}	//  AvatarHeight

SPOINT AvatarPosition(AVATAR* pAvatar)
{
    return pAvatar->pAnimation->world_pos;
}


static SHORT AvatarPlayWithDirections(ANIM *pAnim, int command, SHORT facing)
{
	SHORT animfacing = facing;

	if (command == SAME_COMMAND)
		command = pAnim->current_command;

	if (command == WALK_BACK_LEFT || command == WALK_BACK_RIGHT)	{
		animfacing = NormalizeFacing( animfacing + 128 );
	}
	else if (command == ROLL_FROM_STAND_L || command == ROLL_FROM_KNEEL_L || command == ROLL_FROM_PRONE_L)	{
		animfacing = NormalizeFacing( animfacing + 64 );
	}
	else if (command == ROLL_FROM_STAND_R || command == ROLL_FROM_KNEEL_R || command == ROLL_FROM_PRONE_R)	{
		animfacing = NormalizeFacing( animfacing - 64 );
	}

	return animfacing;
}