//========================================================================
//	FILE:			$Workfile: Item.cpp $
//
//	DESCRIPTION:	
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, August 13, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Item.cpp 116   4/14/98 10:30a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unauthorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Item.cpp $
//  
//  116   4/14/98 10:30a Bwilcox
//  switch playcycle to elapsed time printout,
//  optimize trooper no routing when fail on victim
//  
//  115   4/13/98 10:47p Bwilcox
//  ai order failures delay 3 seconds before reporting now
//  
//  114   4/10/98 6:02p Bwilcox
//  
//  113   4/10/98 5:53p Bwilcox
//  allow fanout from witihin off visible space
//  
//  112   4/10/98 11:57a Bwilcox
//  emove redundante updatetad from specual update
//  
//  111   4/10/98 11:19a Bwilcox
//  added itemdeadposition
//  
//  110   4/09/98 9:57p Dmaynard
//  Added ItemSpecialUpdatePosition for cases where items enter and leave
//  the universe.
//  
//  109   4/08/98 10:46a Phu
//  removed an assert
//  
//  108   4/07/98 4:43p Bwilcox
//  dont trigger vis events on dead things
//  
//  107   4/07/98 6:14a Bwilcox
//  tad cleanup
//  
//  106   4/05/98 1:55p Bwilcox
//  invisiblitly cheat
//  
//  104   4/02/98 6:13p Phu
//  typecast to avoid warnings
//  
//  103   4/02/98 3:06p Phu
//  
//  102   4/02/98 2:16p Bwilcox
//  guard towers cannot see invisible troopers, but normal folks can
//  
//  101   3/31/98 12:54p Bwilcox
//  dispell fog
//  
//  100   3/30/98 10:09p Nrobinso
//  switch to animtime, which allows for pauses
//  
//  99    3/26/98 9:07p Bwilcox
//  
//  98    3/26/98 9:00p Bwilcox
//  guard tower sees farther wo line of sight
//  
//  97    3/26/98 2:39p Bwilcox
//  vehicle in movement layer split into new layer
//  
//  96    3/22/98 3:16p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  95    3/16/98 1:09a Nrobinso
//  remove points
//  
//  94    3/15/98 6:53a Bwilcox
//  
//  93    3/04/98 6:56p Dmaynard
//  ItemUpdateSeen does not have to broadcast an event if we are just
//  seeing ourselves for the first time, for instance at initial
//  deployment.
//  
//  92    3/04/98 2:34p Phu
//  fix to ItemCenterPos
//  
//  91    3/03/98 3:03p Bwilcox
//  tad drops target after it goes invisible (10 sec after no longer seen)
//  or if target has 0 strength
//  
//  90    2/26/98 6:11p Bwilcox
//  per fruin request, reduce y vis range of all but sarge, and make x/y
//  uniform
//  Use sargecane to see the range of other vision
//  
//  89    2/24/98 11:47a Bwilcox
//  all pads now updated after movement completes to avoid bugs from
//  undeploy in script
//  
//  88    2/20/98 10:55a Bwilcox
//  reenable assert_on_untrafficable code if it is turned on
//  
//  87    2/18/98 2:26p Bwilcox
//  stop air recon from using allah mode to do its dirty work
//  
//  86    2/17/98 11:30a Bwilcox
//  firing mortar gives sarge better range
//  
//  85    2/13/98 6:03p Phu
//  change in elevation factor
//  
//  84    2/10/98 2:21p Phu
//  firing heights
//  
//  83    2/03/98 5:34p Phu
//  visibility linger is now 5 real seconds
//  
//  82    2/03/98 5:34p Phu
//  visibility decay changed from 40 fromes to 100
//  
//  81    1/30/98 1:50p Bwilcox
//  new vis range model
//  
//  80    1/30/98 1:37p Bwilcox
//  
//  79    1/30/98 1:28p Bwilcox
//  trying new visibility stuff
//  
//  78    1/19/98 5:46p Nrobinso
//  add ItemCenterPos
//  
//  77    1/17/98 8:15p Nrobinso
//  make sarge view based on saved info in sarge
//  
//  76    1/16/98 11:48p Bwilcox
//  
//  75    1/16/98 9:56p Bwilcox
//  sarge view changed
//  
//  74    1/16/98 9:10p Bwilcox
//  sarge sees his screen
//  
//  73    1/15/98 9:35a Bwilcox
//  tile line optimizations
//  
//  72    98/01/14 17:09 Dmaynard
//  
//  71    1/14/98 4:28p Bwilcox
//  replaced cansee/canshoot coding
//  
//  70    1/12/98 7:02p Bwilcox
//  vis testing moved to common place in unit
//  now trigger vison events
//  
//  69    1/09/98 6:36p Nrobinso
//  add ITemClearOldLocation
//  
//  68    1/08/98 1:51p Bwilcox
//  added assert checks on bounds for writing into an array
//  
//  67    1/06/98 1:52p Bwilcox
//  fixed trooper clearmem problem
//  
//  66    1/06/98 12:42p Bwilcox
//  
//  65    1/06/98 12:35p Bwilcox
//  added PropogateTrafficable fanout code in item.
//  fixed troopercover bug when enemy dies
//  
//  64    12/24/97 5:01p Bwilcox
//  removing use of location and oldlocation epoints
//  
//  63    12/23/97 11:27a Nrobinso
//  set assert_on_untrafficable to default to false
//  
//  62    12/16/97 10:21a Bwilcox
//  itemfanout no longer selects places off the visible screen
//  
//  61    12/15/97 3:38a Phu
//  Mines/Minesweeper
//  
//  60    12/14/97 2:39p Phu
//  Have vehicles w/commanders update the fog layer
//  
//  59    12/12/97 2:04p Phu
//  
//  58    12/09/97 7:18p Bwilcox
//  removed access to unitprivatedata
//  
//  57    12/09/97 12:12p Phu
//  
//  56    12/08/97 2:05p Bwilcox
//  
//  55    12/07/97 5:00p Phu
//  Modified CanSee routines
//  
//  54    12/07/97 1:18p Phu
//  
//  53    12/05/97 5:40p Phu
//  Every trooper updates fog now
//  
//  52    12/05/97 3:25p Phu
//  better los based on visibility layer
//  
//  51    12/05/97 12:34p Phu
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"

#include "Army.h"
#include "aix.h"
#include "unit.h"
#include "Tad.h"
#include "miscfile.h"
#include "Ai.h"
#include "Map.h"
#include "Animfile.h"
#include "UnitMsg.h"
#include "newdoor.h"
#include "trooper.h"
#include "aiaccess.h"
#include "object.h"
#include "comm.h"
#include "item.h"
#include "pad.h"
#include "input.h"
#include "gameflow.h"
#include "vehicle.h"
#include "sarge.h"
int xVisRange = 170;
int yVisRange = 170;
int TowerxVisRange = 450;
int ToweryVisRange = 450;
char sargeInvisible = 0;
extern long user_action;
extern long maplimit;
BOOL assert_on_untrafficable = FALSE;
char Allah = 0;				// can you see all things?
extern int ReconTimer;
ITEM* fanoutItem;
IPOINT maxFanIndex;
long maxFanDistance;
long ItemFanIncremental(ITEM* pItem,IPOINT at,int limit,FANFUNC func,
                        int xdif,int ydif);

extern short int *tileLineOffsets;
extern long tileIndices[];
extern int maxvisblock;
int SEEN_TIME_DELAY = 10000;
///========================================================================
//	Function:		ItemPower
//	Description:	estimated power of attacker vs. target
///========================================================================

int ItemPower(ITEM* pAttacker, ITEM* pTarget)
{
	return( 5 );
}

///========================================================================
//	Function:		See
//	Description:	mark item as seen by this army
///========================================================================

void See(int eArmy,ITEM* pItem)
{
    pItem->seen[eArmy] = gpGame->dwAnimTime;
    pItem->seenWhere[eArmy] = pItem->position;
}

///========================================================================
//	Function:		ItemVisible
//	Description:	Does army "see" this item or is it undiscovered still
///========================================================================

#define ITEM_RECENTLY_SEEN_BY(x,by)	((gpGame->dwAnimTime - (DWORD)(ITEM_SEEN_WHEN(x,by)))<(DWORD)SEEN_TIME_DELAY)

BOOL ItemVisible(int eArmy, void* pItem)
{
	int when = ITEM_SEEN_WHEN(pItem,eArmy);
	if (when == -1) return FALSE;

    if (ITEM_ARMY(pItem) == eArmy) return TRUE; // you see your own stuff

    // flip visibility to see what foe would see of you
    if (ITEM_TYPE(pItem) == ARMY_UNIT || ITEM_TYPE(pItem) == ARMY_SARGE ||
		ITEM_TYPE(pItem) == ARMY_VEHICLE)
    {
        if (ITEM_RECENTLY_SEEN_BY(pItem,eArmy)) return TRUE;
    }
    else return TRUE; // later some buildings might need to be seen first

    return FALSE;
}

BOOL ItemUserVisible(int eArmy, void* pItem)
{

    if (Allah == 1)	return TRUE;				// god sees all things
    if (ReconTimer)	return TRUE;				// air support sees all things


    if (ITEM_ARMY(pItem) == eArmy && Allah == 0) return TRUE; // you see your own stuff
    if (ITEM_ARMY(pItem) != eArmy && Allah == 2) return TRUE; // you see his stuff

    // flip visibility to see what foe would see of you
    if (Allah == 2) eArmy = (eArmy == ARMY_PLAYER) ? ARMY_COMPUTER : ARMY_PLAYER;
    int when = ITEM_SEEN_WHEN(pItem,eArmy);
	if (when == -1) return FALSE;
	
	if (ITEM_TYPE(pItem) == ARMY_UNIT || ITEM_TYPE(pItem) == ARMY_SARGE ||
        ITEM_TYPE(pItem) == ARMY_VEHICLE)
    {
        if (ITEM_RECENTLY_SEEN_BY(pItem,eArmy)) return TRUE;
    }
    else return TRUE; // later some buildings might need to be seen first

    return FALSE;
}

///========================================================================
//	Function:		ItemSetUID
//	Description:	set id and human readable fields of an item
///========================================================================


void ItemSetUID(void* ptr,int eArmy,int eObjType,int eSubType1,int eSubType2)
{
    ITEM* pItem = (ITEM*) ptr;

	UID	nUniqueID = AiRequestUniqueID(eArmy,eObjType,eSubType1,eSubType2);

    pItem->nUniqueID = nUniqueID;

#ifdef _DEBUG
    // now assign the human readable shadows
    pItem->exWhoseArmy = (ARMY_TYPE)eArmy;		
    pItem->exOType = (ITEM_TYPE)eObjType;
    pItem->exType = eSubType1;
    pItem->exID = eSubType2;
#endif
}

///========================================================================
//	Function:		ItemSetLocation
//	Description:	sets location of item
///========================================================================

void ItemSetLocation(void* ptr, SPOINT* position)
{
    ITEM* pItem = (ITEM*) ptr;

    pItem->position.x = position->x;
    pItem->position.y = position->y;
	IPOINT tile;
    tile = ENCODE_IPOINT(position->x,position->y);
//	ASSERT(tile || !position->x); 
//  note: normally the the position of an item == its' world position
//  but this is not true for objects, where the position is its' UL corner
//  while world_pos is its' hotspot.  An object placed @ 0,0 can have a
//  valid tile value because its' world_pos will not be 0,0  -PH
	pItem->tile = tile;

    // prove they are legal if on map
	if (assert_on_untrafficable)	{
		if (!pItem->tile);
        else if (!UntrafficableUnit(pItem->tile));
		else if (ITEM_TYPE(pItem) == ARMY_UNIT ||
                 ITEM_TYPE(pItem) == ARMY_TROOPER)
        {
			TRACE("%s trooper on untrafficable spot: %d,%d\n", pItem->label, position->x, position->y);
			if (IS_LOCAL_ITEM(pItem)) ASSERT(0);
        }
        else if (ITEM_TYPE(pItem) == ARMY_VEHICLE)
        {
            if (IS_LOCAL_ITEM(pItem)) ASSERT(0); //allow vehicles to be illegal
        }
	}
}

///========================================================================
//	Function:		ItemSetOldLocation
//	Description:	transfers current location data to old data
///========================================================================

void ItemSetOldLocation(void* ptr)
{
    ITEM* pItem = (ITEM*) ptr;

    pItem->oldTile = pItem->tile;
    pItem->oldPosition = pItem->position;
    pItem->oldFacing = pItem->facing;

    // prove they were legal if on map
	if (assert_on_untrafficable)	{    
		if (!pItem->oldTile);
        else if (!UntrafficableUnit(pItem->oldTile));
		else if (ITEM_TYPE(pItem) == ARMY_UNIT ||
                 ITEM_TYPE(pItem) == ARMY_TROOPER)
        {
			if (IS_LOCAL_ITEM(pItem)) ASSERT(0);
        }
        else if (ITEM_TYPE(pItem) == ARMY_VEHICLE)
        {
            if (IS_LOCAL_ITEM(pItem)) ASSERT(0);
        }
	}
}


///========================================================================
//	Function:		ItemClearOldLocation
//	Description:	set old location to 0,0 so item will show as moved
///========================================================================

void ItemClearOldLocation(ITEM *pItem)
{
    pItem->oldTile = 0;
    pItem->oldPosition.x = 0;
    pItem->oldPosition.y = 0;
    pItem->oldFacing = 0;
}


///========================================================================
//	Function:		ItemCenterPos
//	Get

SPOINT ItemCenterPos(ITEM* pItem)
{
	ANIM *pAnim = NULL;
	SPOINT	pos = pItem->position;
	VEHICLE *pVehicle;
	SARGE *pSarge;
	TROOPER *pTrooper;

    switch(ITEM_TYPE(pItem))
	{
		case ARMY_VEHICLE:
			pVehicle = (VEHICLE *)pItem;
			pAnim = pVehicle->pAnimation;
			break;
		case ARMY_SARGE:
			pSarge = (SARGE *)pItem;
			pAnim = pSarge->pAvatar->pAnimation;
			break;
		case ARMY_TROOPER:
			pTrooper = (TROOPER *)pItem;
			pAnim = pTrooper->pAvatar->pAnimation;
			break;
		case ARMY_OBSTACLE:
		case ARMY_STRUCTURE:
		case ARMY_ASSET:
		case ARMY_HUSK:
			pAnim = (ANIM *)( &(((OBJECTSTRUCT *)(pItem))->cell) );
			break;
	}

	if (pAnim)	{
		pos.x = (short)(pAnim->wrect.left + ((pAnim->wrect.right - pAnim->wrect.left) >> 1));
		pos.y = (short)(pAnim->wrect.top + ((pAnim->wrect.bottom - pAnim->wrect.top) >> 1));
	}

	return pos;
}


extern SHORT vehicle_height[];


//  get the elevation of the terrain for an item
int GetElevationHeightAtItem( ITEM *pItem )
{
	int		height = 0;
	IPOINT	tile;

	switch( ITEM_TYPE(pItem) )
	{
	case ARMY_VEHICLE:
		if( ((VEHICLE *)pItem)->pAnimation )
			tile = IPOINT_FROM_SPOINT(((VEHICLE *)pItem)->pAnimation->world_pos);
		else
			tile = pItem->tile;
		height = (ELEVATION(the_map.elevation_layer[tile]) << 2);
		break;
	case ARMY_TROOPER:
		if( ((TROOPER *)pItem)->pAvatar )
			height = (ELEVATION(the_map.elevation_layer[pItem->tile]) << 2);
		break;
	case ARMY_SARGE:
		if( ((SARGE *)pItem)->pAvatar )
			height = (ELEVATION(the_map.elevation_layer[pItem->tile]) << 2);
		break;
	case ARMY_ASSET:
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
	case ARMY_HUSK:
		height = (ELEVATION(the_map.elevation_layer[pItem->tile]) << 2);
		break;
	}
	return height;
}


// return the height of an item w/o elevation
int GetItemHeightNoElevation( ITEM *pItem )
{
	int		height = 0;

	if( !pItem )
		return height;

	switch( ITEM_TYPE(pItem) )
	{
	case ARMY_VEHICLE:
		height = vehicle_height[ITEM_CLASS(pItem)];
		break;
	case ARMY_TROOPER:
		if( ((TROOPER *)pItem)->pAvatar )
			 height = AvatarHeight(AvatarPose(((TROOPER *)pItem)->pAvatar));
		break;
	case ARMY_SARGE:
		if( ((SARGE *)pItem)->pAvatar )
			height = AvatarHeight(AvatarPose(((SARGE *)pItem)->pAvatar));
		break;
	case ARMY_ASSET:
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
	case ARMY_HUSK:
		height = ((OBJECTSTRUCT *)pItem)->elevation;
		break;
	}
	return height;
}

// return the height of an item plus elevation
int GetItemHeight( ITEM *pItem )
{
	int		height = 0;
	IPOINT  tile;

	if( !pItem )
		return height;

	switch( ITEM_TYPE(pItem) )
	{
	case ARMY_VEHICLE:
		if( ((VEHICLE *)pItem)->pAnimation )
			tile = IPOINT_FROM_SPOINT(((VEHICLE *)pItem)->pAnimation->world_pos);
		else
			tile = pItem->tile;
		height = vehicle_height[ITEM_CLASS(pItem)] + 
				 (ELEVATION(the_map.elevation_layer[tile]) << 2);
		break;
	case ARMY_TROOPER:
		if( ((TROOPER *)pItem)->pAvatar )
		{
			height = (ELEVATION(the_map.elevation_layer[pItem->tile]) << 2) +
					 AvatarHeight(AvatarPose(((TROOPER *)pItem)->pAvatar));
		}
		break;
	case ARMY_SARGE:
		if( ((SARGE *)pItem)->pAvatar )
		{
			height = (ELEVATION(the_map.elevation_layer[pItem->tile]) << 2) +
					 AvatarHeight(AvatarPose(((SARGE *)pItem)->pAvatar));
		}
		break;
	case ARMY_ASSET:
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
	case ARMY_HUSK:
		height = (ELEVATION(the_map.elevation_layer[pItem->tile]) << 2) +
				 ((OBJECTSTRUCT *)pItem)->elevation;
		break;
	}
	return height;
}


///========================================================================
//	Function:		ItemDBName
//	Description:	get a printable name for traces (+ timestamp)
///========================================================================

char* ItemDBName(void* ptr)
{
    static char name[100]; char label[100];
    if (!ptr)
    {
        sprintf(name,"???");
        return name;
    }
	ITEM *pItem = (ITEM *) ptr;
    UNIT* pUnit;
    int eArmy = ITEM_ARMY(pItem);

    // get script name
    if (pItem->label) sprintf(label,"%s",pItem->label);
    else label[0] = 0;

    switch(ITEM_TYPE(pItem))
      {
          case ARMY_VEHICLE:
              switch(ITEM_CLASS(pItem))
              {
              case ARMY_JEEP:
                  sprintf(name,"%d.%3d- JEEP%d Army%d %s",nSec,nMilliSec,
                      ITEM_INDEX(pItem),eArmy,label);
				  break;
              case ARMY_TANK:
                  sprintf(name,"%d.%3d- TANK%d Army%d %s",nSec,nMilliSec,
                      ITEM_INDEX(pItem),eArmy,label);
				  break;
              case ARMY_HALFTRACK:
                  sprintf(name,"%d.%3d- HALFTRACK%d Army%d %s",nSec,nMilliSec,
                      ITEM_INDEX(pItem),eArmy,label);
				  break;
              case ARMY_CONVOY:
                  sprintf(name,"%d.%3d- CONVOY%d Army%d %s",nSec,nMilliSec,
                      ITEM_INDEX(pItem),eArmy,label);
				  break;
              default:
                  sprintf(name,"%d.%3d- ?VEHICLE%d Army%d %s",nSec,nMilliSec,
                      ITEM_INDEX(pItem),eArmy,label);
				  break;
              }
              break;
          case ARMY_SARGE:
              sprintf(name,"%d.%3d- SARGE~%d %s",nSec,nMilliSec,eArmy,label);
              break;
          case ARMY_UNIT:
              sprintf(name,"%d.%3d- UNIT-%d Army%d %s",nSec,nMilliSec,ITEM_INDEX(pItem),
                      eArmy,label);
              break;
          case ARMY_TROOPER:
              pUnit = ((TROOPER*)pItem)->pUnit;
              if (pUnit->common.label) sprintf(label,"%s",pUnit->common.label);
              else label[0] = 0;              
              sprintf(name,"%d.%3d- TROOPER-%d Unit%d Army%d of %s",
                  nSec,nMilliSec,ITEM_INDEX(pItem) & 15,
                  ITEM_INDEX(pItem) >> 4,eArmy,label);
              break;
          default: sprintf(name,"%d.%3d- ??%d~%d",nSec,nMilliSec,ITEM_INDEX(pItem),eArmy);
      }
      return name;
}

///========================================================================
//	Function:		ItemMakeVisible
//	Description:	this guy has revealed himself as visible to all
///========================================================================

void ItemMakeVisible(void* pX)
{
    ITEM* pItem = (ITEM*) pX;
    See(ARMY_PLAYER,pItem);
    See(ARMY_PLAYER_2,pItem);
    See(ARMY_PLAYER_3,pItem);
    See(ARMY_PLAYER_4,pItem);
}




extern char Allah;



///========================================================================
//	Function:		ItemUpdateTad
//	Description:	process any tad info about items movement
///========================================================================

void ItemUpdateTad(ITEM* pItem)
{
    int type;
    if (pItem->pTad == NULL) return;			// has nothing to update
    if (pItem->tile == pItem->oldTile) return;	// no tile change
    type = ITEM_TYPE(pItem);  
    TadUpdateQuad(type,pItem,pItem->oldPosition,pItem->position);
}

///========================================================================
//	Function:		ItemUpdateSeen
//	Description:	does item from see item to
///========================================================================

static int TurretCanSee(IPOINT from,IPOINT to){ // direct see in range

  
    int x,y;
    x = (IPOINT_X(from) << 4) - (IPOINT_X(to) << 4);
    y = (IPOINT_Y(from) << 4) - (IPOINT_Y(to) << 4);
    if (x > xVisRange || x < -xVisRange) return FALSE;
    if (y > yVisRange || y < -yVisRange) return FALSE;

    return TRUE;
}

static int TowerCanSee(IPOINT from,IPOINT to){ // direct see in range

  
    int x,y;
    x = (IPOINT_X(from) << 4) - (IPOINT_X(to) << 4);
    y = (IPOINT_Y(from) << 4) - (IPOINT_Y(to) << 4);
    if (x > TowerxVisRange || x < -TowerxVisRange) return FALSE;
    if (y > ToweryVisRange || y < -ToweryVisRange) return FALSE;

    return TRUE;
}


void ItemUpdateSeen(ITEM* pItemFrom, ITEM* pItemTo)
{
    BOOL bOldSeen = TRUE;	// assume we could see him before
    BOOL bNowSee = FALSE;   // assume we dont see him now
    int	eMyArmy  = 	ITEM_ARMY(pItemFrom);			// my army index

		// sarge in stealth mode cheat?
	if (sargeInvisible && ITEM_ARMY(pItemTo) == ARMY_PLAYER &&
		ITEM_TYPE(pItemTo) == ARMY_SARGE) return;


    // already seen by someone else in my forces
    if (ITEM_SEEN_THIS_TURN(pItemTo,eMyArmy)) return;

    // note whether I already have seen him, to trigger new seeing event maybe
    if (!ItemVisible(ITEM_ARMY(pItemFrom),pItemTo)) bOldSeen = FALSE;

    // sarge gets to see all within screen range, ignoring line of sight.
    if (ITEM_TYPE(pItemFrom) == ARMY_SARGE)
    {
		SARGE *pSarge = (SARGE *) pItemFrom;

        // sarge firing a mortar gets to see more 
		// and since mortar does damage out from landing spot,
		// add a few tiles more than range
        if (ITEM_ARMY(pSarge) == ARMY_PLAYER &&
            user_action & DO_FIRE  &&
            pSarge->common.pWeapon->eWeapon == ARMY_MORTAR &&
            GetDistance(&pSarge->common.position,&pItemTo->position)
                < (AiObjectFiringRange((ITEM*)pSarge) + 48))
        {
            See(eMyArmy,pItemTo);
            bNowSee = TRUE;
			goto done;
			
        }

		if ( InBox(&pSarge->ViewBox, &pItemTo->position) )
		{
			See(eMyArmy,pItemTo);
            bNowSee = TRUE;
			goto done;
		}


        return;
    }
    
    // If I see him, mark him seen as of this frame.
    // I can continue to have lingering knowledge of seeing him
    // for some time even after he goes out of sight.
	if (ITEM_CLASS(pItemFrom) == GUN_TURRET)
    {	
        OBJECT* pObject;
        pObject = (OBJECT*) pItemFrom;
        if (pObject->number == 201) // the guard tower
        {
            // guard tower will not be allowed to see invisible troopers (prison camp executions)
			if (ITEM_TYPE(pItemTo) == ARMY_TROOPER &&
				((TROOPER*)pItemTo)->pAvatar->pAnimation->flags & ANIM_FLAG_INVISIBLE);

            else if (TowerCanSee(pItemFrom->tile,pItemTo->tile))
            {
                See(eMyArmy,pItemTo);
                bNowSee = TRUE;
            }            
        }
        else if (TurretCanSee(pItemFrom->tile,pItemTo->tile))
        {
			See(eMyArmy,pItemTo);
            bNowSee = TRUE;
        }
    }
    else if (CanSeeFromItem(pItemFrom,pItemTo->tile))
    {	
        See(eMyArmy,pItemTo);
        bNowSee = TRUE;
    }
done:
    // trigger visibility on event
    if (bOldSeen == FALSE && bNowSee == TRUE && ITEM_ARMY(pItemFrom) != ITEM_ARMY(pItemTo) &&
		pItemTo->nStrength != 0)
        EventTrigger(EVENT_ITEMVISON,
                     pItemTo->eventNum,
                     ITEM_UID(pItemFrom),0,0);
}


///========================================================================
//	Function:		ItemUpdatePosition
//	Description:	Change item to new location and update
//					related issues ( visibility, tad, influence)
//					Called for UNITS,VEHICLES,SARGE
//	An item not on the map have a position of (0,0), coming or going.		
///========================================================================

void ItemUpdatePosition(ITEM* pItem,SPOINT* position)
{	
    // xfer current to old
    ItemSetOldLocation(pItem);
    // change to new location
    ItemSetLocation(pItem,position);
    // update simulation data
    ItemUpdateTad(pItem);

}

///========================================================================
//	Function:		ItemFanOut
//	Description:	This walks in expanding boxes around item calling
//					user function at each tile. If function returns non-zero,
//					then ItemFanOut will stop and return that value.
///========================================================================
static int visillegal;

long ItemFanOut(ITEM* pItem,IPOINT at,int limit,FANFUNC func)
{
	IPOINT index;
	long result;
    int x,y,n = 0,atx,aty;
	atx = x = IPOINT_X(at);
    aty = y = IPOINT_Y(at);
	fanoutItem = pItem;// temp global
	// do we start out off visible?
	visillegal = TRUE;
	if (OffVisible(at)) visillegal = 0;
 
    // walk in expanding squares from self til limit
    while (++n <= limit) // move out to the next layer out
	{
        int ylow = aty - n, xlow = atx - n;
        int yhi = aty + n, xhi = atx + n;
		if (!visillegal && OFF_X(xlow)) xlow = 0;
        if (!visillegal && OFF_X(xhi)) xhi = 0;
        if (!visillegal && OFF_Y(ylow)) ylow = 0;
        if (!visillegal && OFF_Y(yhi)) yhi = 0;

        if (visillegal && OFF_VISIBLE_X(xlow)) xlow = 0;
        if (visillegal && OFF_VISIBLE_X(xhi)) xhi = 0;
        if (visillegal && OFF_VISIBLE_Y(ylow)) ylow = 0;
        if (visillegal && OFF_VISIBLE_Y(yhi)) yhi = 0;

		// walk to top and bottom box edges
        int xlim = atx + n;
        for (x = atx - n; x <= xlim; ++x){
            if (visillegal && OFF_VISIBLE_X(x)) continue;
             if (!visillegal &&  OFF_X(x)) continue;
             if (ylow)
			{
                index = INDEX(x,ylow);
				result = (*func)(index);
				if (result) return result;
            }
            if (yhi)
			{
                index = INDEX(x,yhi);
 				result = (*func)(index);
				if (result) return result;
            }
        }

		// walk the left and right box edges
        int ylim = aty + n - 1;
        for (y = aty - n + 1; y <= ylim; ++y){
             if (visillegal && OFF_VISIBLE_Y(y)) continue;
           if (!visillegal && OFF_Y(y)) continue;
            if (xlow)
			{
                index = INDEX(xlow,y);
  				result = (*func)(index);
				if (result) return result;
            }
            if (xhi)
			{
                index = INDEX(xhi,y);
 				result = (*func)(index);
				if (result) return result;
            }
        }
    }
	return 0;
}

///========================================================================
//	Function:		ItemFanIn
//	Description:	This walks in decreasing boxes around item calling
//					user function at each tile. If function returns non-zero,
//					then ItemFanIn will stop immediately and return that value.
///========================================================================

long ItemFanIn(ITEM* pItem,IPOINT at, int limit,FANFUNC func)
{
	IPOINT index;
	long result;
    int x,y,n,atx,aty;
	atx = x = IPOINT_X(at);
    aty = y = IPOINT_Y(at);
	fanoutItem = pItem;										// temp global
    maxFanIndex = 0;										// clear max d
    maxFanDistance = 0;
    n = limit + 1;

    // walk in expanding squares from self til limit
    while (--n) // move out to the next layer out
	{
        int ylow = aty - n, xlow = atx - n;
        int yhi = aty + n, xhi = atx + n;
        if (OFF_VISIBLE_X(xlow)) xlow = 0;
        if (OFF_VISIBLE_X(xhi)) xhi = 0;
        if (OFF_VISIBLE_Y(ylow)) ylow = 0;
        if (OFF_VISIBLE_Y(yhi)) yhi = 0;

		// walk to top and bottom box edges
        int xlim = atx + n;
        for (x = atx - n; x <= xlim; ++x){
            if (OFF_VISIBLE_X(x)) continue;
            if (ylow)
			{
                index = INDEX(x,ylow);
				result = (*func)(index);
				if (result) return result;
            }
            if (yhi)
			{
                index = INDEX(x,yhi);
 				result = (*func)(index);
				if (result) return result;
            }
        }

		// walk the left and right box edges
        int ylim = aty + n - 1;
        for (y = aty - n + 1; y <= ylim; ++y){
            if (OFF_VISIBLE_Y(y)) continue;
            if (xlow)
			{
                index = INDEX(xlow,y);
  				result = (*func)(index);
				if (result) return result;
            }
            if (xhi)
			{
                index = INDEX(xhi,y);
 				result = (*func)(index);
				if (result) return result;
            }
        }
    }
	return 0;
}


///========================================================================
//	Function:		ItemFanIncremental
//	Description:	This walks exterior ring only calling
//					user function at each tile. If function returns non-zero,
//					then ItemFanOut will stop and return that value.
///========================================================================

long ItemFanIncremental(ITEM* pItem,IPOINT at,int limit,FANFUNC func,
                        int xdif,int ydif)
{
	IPOINT index;
	long result;
    int x,y,n = limit,atx,aty;
	atx = x = IPOINT_X(at);
    aty = y = IPOINT_Y(at);
	fanoutItem = pItem;										// temp global

    // walk exterior ring
    int ylow = aty - n, xlow = atx - n;
    int yhi = aty + n, xhi = atx + n;
    if (OFF_VISIBLE_X(xlow)) xlow = 0;
    if (OFF_VISIBLE_X(xhi)) xhi = 0;
    if (OFF_VISIBLE_Y(ylow)) ylow = 0;
    if (OFF_VISIBLE_Y(yhi)) yhi = 0;

    // walk top and bottom box edges if his y changed
    int xlim = atx + n;
    if (ydif < 0 && ylow){ // he walked up, scan new up rim
        for (x = atx - n; x <= xlim; ++x){
            if (OFF_VISIBLE_X(x)) continue;
            index = INDEX(x,ylow);
            result = (*func)(index);
            if (result) return result;
        }
    }
    if (ydif > 0 && yhi){ // he walked down, scan new down rim
        for (x = atx - n; x <= xlim; ++x){
            if (OFF_VISIBLE_X(x)) continue;
            index = INDEX(x,yhi);
            result = (*func)(index);
            if (result) return result;
        }
    }
    
    // walk left and right box edges if his x changed
    int yfrom = aty - n;
    int ylim = aty + n ;
    if (xdif < 0 && xlow)
    {
        for (y = yfrom ; y <= ylim; ++y){
            if (OFF_VISIBLE_Y(y)) continue;
            index = INDEX(xlow,y);
            result = (*func)(index);
            if (result) return result;
        }
    }
    if (xdif > 0 && xhi)
    {
        for (y = yfrom ; y <= ylim; ++y){
            if (OFF_VISIBLE_Y(y)) continue;
            index = INDEX(xhi,y);
            result = (*func)(index);
            if (result) return result;
        }
    }
        
	return 0;
}

///========================================================================
//	Function:		PropogateTrafficable & ItemPropogateTrafficable1
//	Description:	spread out on trafficable tiles from center 
//					calling user-function to find a nearby tile of some critera
///========================================================================

static long propogationResult;			// temp local param
static FANFUNC currentfunc;				// temp local param
IPOINT propogateAt;						// where my tile predecessor is

static long testp(IPOINT at)
{
      if (TileDistance(at,fanoutItem->tile) > 5) return at;
	  return 0;
}

static long PropogateTrafficable1(IPOINT loc,IPOINT* stack)
{
      int x,y;
      if (pSeen[loc]) return 0;				// been here already
      x = IPOINT_X(loc);
      y = IPOINT_Y(loc);

      // dont go onto unseeable edge  (also saves falling off map)
	  if (OffVisible(loc)) return 0;

      // try the propogation
      propogationResult = (*currentfunc)(loc);

      // can only propogate thru trafficable space
      if (!UntrafficableUnit(loc))
      {
          // add to stack to follow out in future
          stack[++stack[0]] = loc;	
          ASSERT(loc >= 0 && (int)loc < maplimit);
          pSeen[loc] = (USHORT)propogateAt;		// mark came from here (been here)
      }

      return (propogationResult); // non-zero will terminate search
}

long PropogateTrafficable(ITEM* pItem,IPOINT at, int limit,FANFUNC func)
{
	IPOINT loc; IPOINT stack[1000]; IPOINT* ptr; 
    int height, i = 0;

	fanoutItem = pItem;										// temp global
    height = the_map.height;
    propogationResult = 0; 	// default answer
	currentfunc = func;

    // walk in expanding contiguous trafficable rings from self til limit
    stack[0] = 2;		// number of entries being put on this stack
    stack[1] = at;		// starting location entry
    stack[2] = 0;		// end of 1st layer marker
    ASSERT(at >= 0 && at < (DWORD)maplimit);
    pSeen[at] = (USHORT)at;	// been here mark
    while (++i <= (int)stack[0]) // fan out in layers
	{
      propogateAt = stack[i];
      if (!propogateAt) // level ended
      {
          if (--limit <= 0) break; 	// ran out
          if (i < (int)stack[0]) stack[++stack[0]] = 0;	// set next level marker
          continue;
      }

      if (stack[0] >= 980) break; 		// too close to stack limit, abort
      
      // check its 4 neighbors
      loc = propogateAt + 1; // east
      if (PropogateTrafficable1(loc,stack)) break;
      loc = propogateAt - 1; // west
      if (PropogateTrafficable1(loc,stack)) break;
      loc = propogateAt + height; // up
      if (PropogateTrafficable1(loc,stack)) break;
      loc = propogateAt - height; // down
      if (PropogateTrafficable1(loc,stack)) break;
    }      

    // turn off the seen marks
    ptr = stack + stack[0] + 1;			// ptr to last entry + 1
    while (--ptr != stack){
        ASSERT(*ptr >= 0 && *ptr < (IPOINT)maplimit);
        pSeen[*ptr] = 0; // 0 markers dont matter
    }

    return propogationResult;		// answer or 0 if none found
}


void ItemSetLabel(ITEM *pItem, char *pText)	{
	int size;

    char* pText1 = pText;
    // remove bad endings 
    if (pText && *pText) while (*(++pText1))
    {
        if (*pText1 == 10 || *pText1 == 13 || *pText1 == 9)
        {
            TRACE("Warning: trimming itemlabel %s",pText);
            *pText1 = 0;
            break;
        }
    }
	size = strlen(pText) + 1;
	if (size)	{
		if (pItem->label)
			free(pItem->label);

		pItem->label = (char *)malloc(size);
		strcpy(pItem->label, pText);
	}
}

void ItemFreeLabel(ITEM *pItem)	{
	if (pItem->label)
		free(pItem->label);
	pItem->label = NULL;
}

static int myheight;

long SeeBlock(IPOINT at)
{
    int blockHeight;
    
    // block height 0 = blocks nothing
    blockHeight = the_map.vis_layer[at];
    if (blockHeight >= myheight)
        return TRUE; // we are blocked
    return 0; // no problem
}

int	 CanSeeFromItem(ITEM* pFrom, IPOINT to)
{ 
    IPOINT from;

    int x,y;
	x = (IPOINT_X(to) << 4);
	y =  (IPOINT_Y(to) << 4);
    x = pFrom->position.x - x;
    y = pFrom->position.y - y;
    if (x > xVisRange || x < -xVisRange)
        return FALSE;
    if (y > yVisRange || y < -yVisRange) 
        return FALSE;

    from = pFrom->tile;

    // our height 1 prone 2 kneel 3 stand, 4 tower
    myheight = GetItemPov(pFrom);
    int ans;
    ans = !TileLineCheck(from,to, SeeBlock); // 1 is good
    return ans;
}


int TileLineCheck(IPOINT from, IPOINT to, FANFUNC func){
// execute set of points between the ends. 0 result is went the whole way
    
    IPOINT at; short int *set; int offsetx,offsety,offset,val,ans;
    if (from == to) return 0; // no between points
    if (from > to) // cannonical orientation forward
    {
        at = from;
        from = to;
        to = at;
    }

    offsetx = IPOINT_X(to) - IPOINT_X(from);
    offsety = IPOINT_Y(to) - IPOINT_Y(from);
    offsetx += visibilityRange; // 0 .. visrange+1 
    ASSERT(offsetx >= 0 && offsety >= 0);
    offset = offsetx + (offsety * ((visibilityRange+1) * 2));
    ASSERT(offset < maxvisblock);
    set = tileLineOffsets + tileIndices[offset];  // this is the line data

    while ((val = *set++) != 0) // for each between point on the line
    {
        from += val;  // next point between
        ans = (*func)(from);
        if (ans) return ans; // problem arose
    }
    return 0;
}    

ITEM* ItemContainedBy(ITEM* pItem)
{
	// only a vehicle can contain sarge
	if (ITEM_TYPE(pItem) == ARMY_SARGE)
	{
		return (ITEM*) ((SARGE*)pItem)->pVehicle;
	}

	// only a vehicle can contain a unit
	if (ITEM_TYPE(pItem) == ARMY_UNIT)
	{
		return (ITEM*) ((UNIT*)pItem)->pVehicle;
    }
   
	// all other things are objects that maybe a sarge carries
	int eArmy;
	SARGE* pSarge;
	ITEM* pHeldItem;
	FOR_EACH_DEPLOYED_ARMY(eArmy)
    {
		pSarge = SargePointer(eArmy);
		if (!pSarge) continue;
		pHeldItem = pSarge->pWeaponItemList[(SARGE_WEAPON)1];
		if (pItem == pHeldItem)
 			return (ITEM*)pSarge;
		pHeldItem = pSarge->pWeaponItemList[(SARGE_WEAPON)2];
		if (pItem == pHeldItem)
			return (ITEM*)pSarge;
	}
	return NULL;
}

// Force Tad and Pad to update 
// And prevent any further updating

void ItemSpecialUpdatePosition(ITEM* pItem,SPOINT* position) 
{
	ItemUpdatePosition(pItem, position );   // calls update tad from updateposition
	ItemUpdatePad(pItem);
	ItemUpdatePosition(pItem,position);
}

SPOINT ItemDeadPosition(ITEM* pItem)
{
	if (ITEM_TYPE(pItem) == ARMY_UNIT) return ((UNIT*)pItem)->deadPosition;
	if (ITEM_TYPE(pItem) == ARMY_VEHICLE) return ((VEHICLE*)pItem)->deadPosition;
	if (ITEM_TYPE(pItem) == ARMY_SARGE) return ((SARGE*)pItem)->deadPosition;
	return pItem->oldPosition;
}



