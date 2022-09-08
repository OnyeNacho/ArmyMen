//========================================================================
//	FILE:			$Workfile: Army.h $
//
//	DESCRIPTION:	Message defines, structures, and prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, July 02, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Army.h 153   4/08/98 8:19p Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Army.h $
//  
//  153   4/08/98 8:19p Bwilcox
//  saving death status in game for units and vehicles
//  
//  151   3/28/98 7:14a Bwilcox
//  multiplayer-mode easter egg. Enjoy. Best Regards, The AI Guru
//  
//  150   3/26/98 12:08p Nrobinso
//  have last mission in a scenario automatically go on to the next mission
//  
//  149   3/25/98 6:09p Phu
//  flag frags
//  
//  148   3/24/98 12:10p Nrobinso
//  remove unused
//  
//  147   3/22/98 3:16p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  146   3/19/98 1:49p Nrobinso
//  remove unused
//  
//  145   3/16/98 1:10a Nrobinso
//  remove points from Item
//  
//  144   3/16/98 12:22a Nrobinso
//  add auto tuning based on failures in a mission
//  
//  143   3/09/98 11:32a Nrobinso
//  remove unused
//  
//  142   3/08/98 1:05a Nrobinso
//  maintain sarge's anim types
//  
//  141   3/05/98 4:56p Aburgess
//  added routine to check specifically for scenario end to play SMK videos
//  
//  140   2/27/98 7:07p Nrobinso
//  extra saved data include a vehicle UID
//  
//  139   2/25/98 2:49p Nrobinso
//  add to save data
//  
//  138   2/24/98 11:46a Bwilcox
//  all pads now updated after movement completes to avoid bugs from
//  undeploy in script
//  
//  137   2/20/98 1:20p Nrobinso
//  keep a missile float snd id
//  
//  136   2/19/98 11:55a Nrobinso
//  add new unit/trooper type
//  
//  135   2/10/98 2:21p Phu
//  firing heights
//  
//  134   2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  133   2/06/98 11:42a Phu
//  husks
//  
//  132   2/05/98 3:29p Nrobinso
//  update stats
//  
//  131   2/04/98 5:54p Nrobinso
//  track troopers & units killed
//  
//  130   2/04/98 12:03p Bwilcox
//  adjusted use of armymax units
//  
//  129   2/03/98 8:32p Nrobinso
//  
//  128   2/03/98 4:02p Nrobinso
//  # of deployed units no longer in MISN info
//  
//  127   2/02/98 8:39a Nrobinso
//  modify roll directions
//  
//  126   1/29/98 5:51p Bwilcox
//  unit names system changed
//  
//  125   1/29/98 3:16p Nrobinso
//  separate miner and sweeper
//  
//  124   1/28/98 1:25p Bwilcox
//  fixed load/free stuff
//  
//  123   1/27/98 1:06p Bwilcox
//  finishing armydelete adjustments for multiplayer
//  
//  122   1/27/98 11:24a Bwilcox
//  aix dead code removal. spawned ArmiesDelete from ArmyDelete
//  
//  121   1/26/98 3:32p Phu
//  multiplayer frag counters
//  
//  120   1/19/98 3:24p Awerner
//  Added ALLY and UNALLY, MAKESTRATEGIC and MAKENONSTRATEGIC, and changed
//  get_ and drop_ to take specific item names
//  
//  119   1/17/98 9:45p Nrobinso
//  keep a reversed flag so we can tell when sarge is backwards
//  
//  118   1/14/98 7:10p Phu
//  use weapon type w/ floats instead of pointer
//  
//  117   1/12/98 7:15p Bwilcox
//  visibility tmp added to common, and moved itemsees army from
//  sarge/vehicle to unit.cpp
//  
//  116   1/09/98 6:36p Nrobinso
//  add ArmyUpdatePads
//  
//  115   1/06/98 6:22p Phu
//  don't deploy forces if player is not in game
//  
//  114   12/24/97 5:21p Bwilcox
//  the item location field and the epoint datatype are now gone
//  
//  113   12/16/97 12:12p Aburgess
//  Campaign Select only processes NextAdvance data for Scenarios and
//  Missions, ovoiding overwrite of CampignIndex when Saved data is present
//  
//  112   12/15/97 1:18a Aburgess
//  new prototype ArmyFindNextAdvance()
//  
//  111   12/11/97 1:52p Aburgess
//  added prototypes for setting current IDs for Campaigns, Scenarios, and
//  Missions
//  
//  110   12/09/97 12:22p Bwilcox
//  max vehicles now 50
//  
//  109   12/09/97 12:11p Phu
//  
//  108   12/07/97 10:42a Nrobinso
//  increased number of vehicles
//  
//  107   12/06/97 1:11p Nrobinso
//  add extra data to deployment info
//  
//  106   12/05/97 9:54p Nrobinso
//  added uniqueID to deployment struct
//  
//  105   12/05/97 1:06p Nrobinso
//  
//  104   12/04/97 6:12p Nrobinso
//  add ArmyUpdateInSetup
//  
//  103   12/04/97 11:10a Phu
//  Added extra layer, moved order variable, changed flamer
//  
//  102   12/03/97 10:02a Aburgess
//  added ARMY_NO_COLOR
//  
//  101   11/24/97 8:35p Phu
//  Add Z component to projectile firing
//  
//  100   11/24/97 2:49p Aburgess
//  update current indecies routine
//  
//  99    11/19/97 6:30p Awerner
//  added NUKE command
//  
//  98    11/19/97 5:40p Phu
//  flamethrowers & muzzle flashes
//  
//  97    11/19/97 4:42p Nrobinso
//  increase max number of units
//  
//  96    11/17/97 8:33p Nrobinso
//  increase max units per army
//  
//  95    11/17/97 2:40p Aburgess
//  added Most Avanced prototypes
//  
//  94    11/16/97 5:32p Nrobinso
//  simplified float types
//  
//  93    11/17/97 1:27a Bwilcox
//  
//  92    11/14/97 2:00p Nrobinso
//  set max vehicles to 8 to account for debugging vehicles
//  
//  91    11/13/97 9:35a Aburgess
//  extern references
//  
//  90    11/11/97 4:52p Phu
//  Guard Towers
//  
//  89    11/11/97 9:39a Aburgess
//  moved pointer designator
//  
//  88    11/11/97 8:45a Aburgess
//  ArmyLoadSavedMission prototype
//  
//  87    11/07/97 10:39a Aburgess
//  added "point" and mission save modifications
//  
//  86    11/03/97 9:41p Nrobinso
//  switch NO_RESOURCE back to 0; put human readable sahdows of unitqueID
//  values under _DEBUG control
//  
//  85    10/31/97 5:28p Awerner
//  Fix for air support numeration
//  
//  84    10/31/97 3:55p Bwilcox
//  raising limit on number of vehicles in army and issusing warning if
//  exceeded
//  
//  83    10/30/97 2:37p Phu
//  
//  82    10/30/97 1:49p Aburgess
//  added definition for army max units
//  
//  81    10/29/97 1:04p Bwilcox
//  added trooperprivatedata
//  
//  80    10/28/97 11:22a Aburgess
//  Moved Alliance setting and queries from TADPRIV to ARMY
//  
//  79    10/23/97 4:06p Bwilcox
//  removing dead code relating to units entering vehicles and installing
//  new code
//  
//  78    10/23/97 8:51a Bwilcox
//  activating all armies
//  
//  77    10/22/97 10:56a Bwilcox
//  nsize removed from common,
//  boat changed to convoy throughout (including aai files)
//  
//  76    10/21/97 10:54a Dmaynard
//  Added ARMY_GREEN thru ARMY_GRAY constants.  New Functions in CComm
//  ColorFromIndex and IndexFromColor to map between army number and army
//  color.
//  
//  75    10/20/97 3:28p Phu
//  Added ordering field to ITEM structure
//  
//  74    10/20/97 2:28p Phu
//  Damaging Explosions
//  
//  73    10/16/97 6:26p Nrobinso
//  add nMaxStrength to ITEM; made Unit consistent with new scheme, put
//  number of troopers inot pUnit->troops
//  
//  72    10/16/97 1:19p Nrobinso
//  cleanup scenario start up sequence
//  
//  71    10/15/97 6:22p Nrobinso
//  execute StartScripting at beginning of new missions
//  
//  70    10/15/97 5:06p Nrobinso
//  Create all items at beginning of scenario; process deployed items for
//  each mission
//  
//  69    10/14/97 5:56p Phu
//  
//  68    10/14/97 3:37p Nrobinso
//  inline a number of simple access functions
//  
//  67    10/14/97 1:37p Nrobinso
//  make ArmyGetVehicle inline
//  
//  66    10/14/97 11:59a Nrobinso
//  make ArmyGetLegion inline
//  
//  65    10/14/97 11:43a Phu
//  Added a next pointer to ITEM structure
//  
//  64    10/14/97 10:11a Nrobinso
//  move info interface routines out to sarge.h
//  
//  63    10/13/97 5:20p Nrobinso
//  change weapon in ITEM to an item pointer, then add WEAPON data to those
//  structures that need it.
//  
//  62    10/10/97 8:08p Nrobinso
//  add a FOR_ALL_ARMIES macro loop
//  
//  61    10/10/97 6:54p Nrobinso
//  add mission functions
//  
//  60    10/08/97 4:41p Nrobinso
//  add sarge weapon prototypes
//
//  ...
//  
//  1     7/26/96 10:10a Aburgess
//  
//  $Nokeywords:$
///========================================================================

#ifndef __ARMY_H__
#define __ARMY_H__

#ifndef __ANIM_H__
#include "anim.h"
#endif

#ifndef __AI_H__
#include "Ai.h"
#endif

#define	MAX_OBJECTS				64
#include "Msg.h"

//=========================================================================
//						GLOBAL DEFINES
//=========================================================================

#define	ARMY_MAX_TROOPS			5
#define	ARMY_MAX_VEHICLES		50

#define	UNIT_MAX_ANIMATIONS		16

#define WALK_CYCLE_SPRITES		10
#define RUN_CYCLE_SPRITES		10
#define FIRE_CYCLE_SPRITES		1

#define	ARMY_MAX_LINKS			8

#define	SCENARIO_NAME_SIZE		16
#define	MISSION_NAME_SIZE		64
#define	MISSION_FILENAME_SIZE	32


//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================

// ARMY types
typedef enum
{
	ARMY_INDEPENDENT = -1,
	ARMY_PLAYER = 0,
	ARMY_PLAYER_2,
	ARMY_PLAYER_3,
	ARMY_PLAYER_4,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_ARMY
} ARMY_TYPE;

typedef enum
{
    ARMY_NO_COLOR = -1,
    ARMY_GREEN    =  0,
    ARMY_TAN,
    ARMY_BLUE,
	ARMY_GRAY,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	LAST_COLOR_ARMY
} ARMY_COLOR;


 

#define	ARMY_COMPUTER	ARMY_PLAYER_2


#define	DMGTYPE_EXPLOSION		0x40

#define	DMGTYPE_RUNOVER			0x00
#define	DMGTYPE_GRENADE			(0x01 | DMGTYPE_EXPLOSION)
#define	DMGTYPE_MORTAR			(0x02 | DMGTYPE_EXPLOSION)
#define	DMGTYPE_BAZOOKA			0x03
#define	DMGTYPE_MISSILE			0x04
#define	DMGTYPE_OTHER_EXPLOSION	(0x05 | DMGTYPE_EXPLOSION)
#define	DMGTYPE_BULLET			0x06
#define	DMGTYPE_FLAMED			0x07
#define	DMGTYPE_STRUCTURAL		0x08
#define DMGTYPE_OTHER			0x09


// ARMY building types
typedef enum
{
	ARMY_MAIN_BASE = 0,
	ARMY_FUEL_DEPOT,
	ARMY_RADAR_OUTPOST,
	ARMY_POWER_PLANT,
	ARMY_PRISON_CAMP,
	ARMY_GUN_TURRET,
	ARMY_ACK_ACK_GUN,
	ARMY_PILLBOX,
	ARMY_GENERIC_BUILDING,
	ARMY_EXTRA_BASE,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_BLDNG_STATE
} BUILDING_TYPE;

// ARMY structure state
typedef enum
{
	ARMY_STRUCT_IDLE = 0,
	ARMY_STRUCT_DAMAGED,
	ARMY_STRUCT_ATTACK,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_STRUCT_STATE
} STRUCTURE_STATE;

// ARMY situations
typedef enum
{
	ARMY_NO_ACTION = 0,
	ARMY_UNDER_ATTACK,
	ARMY_ATTACKING,
	ARMY_ELIMINATED,
	ARMY_ENGAGED,
	ARMY_DISENGAGED,
	ARMY_APPROACH,
	ARMY_SUFFERING,
	ARMY_REACHED,
	ARMY_ORDERACK,
	ARMY_GOTOACK,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_ACTION
} ARMY_ACTION;

// ARMY terrain movement rate indecies
typedef enum
{
	TERRAIN_0 = 0,
	TERRAIN_1,
	TERRAIN_2,
	TERRAIN_3,
	TERRAIN_4,
	TERRAIN_5,
	TERRAIN_6,
	TERRAIN_7,
	TERRAIN_8,
	TERRAIN_9,
	TERRAIN_10,
	TERRAIN_11,
	TERRAIN_12,
	TERRAIN_13,
	TERRAIN_14,
	TERRAIN_15,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	LAST_TERRAIN
} TERRAIN;


// FLOAT types
typedef enum
{
	ARMY_FLOAT_OK = 0,

	ARMY_FLOAT_INACTIVATED,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_FLOAT_LAST_RETURN
} FLOAT_RETURN_TYPE;

// ITEM types
typedef enum
{
	ARMY_NULL_OBJ = 0, 
	ARMY_UNIT,
	ARMY_VEHICLE,
	ARMY_FLOAT,
	ARMY_TROOPER,
	ARMY_SARGE,
	ARMY_ASSET,
	ARMY_STRUCTURE,
	ARMY_OBSTACLE,
	ARMY_HUSK,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_LEGION
} ITEM_TYPE;

#define IS_ARMY_OBJECT(item_type) ((item_type)>= ARMY_ASSET)

// vehicle types
typedef enum
{
	ARMY_NO_VEHICLE = 0,

	ARMY_JEEP,
	ARMY_TANK,
	ARMY_HALFTRACK,
	ARMY_CONVOY,
	ARMY_COMMANDER,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_VEHICLE
} VEHICLE_TYPE;
#define ARMY_FIRST_VEHICLE ARMY_JEEP


// resource types
typedef enum
{
	ARMY_NO_RESOURCE = 0,

	ARMY_RESOURCE_AIR_STRIKE,
	ARMY_RESOURCE_PARATROOPERS,
	ARMY_RESOURCE_AIR_RECON,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_RESOURCE
} RESOURCE_TYPE;

// float types
typedef enum
{
	ARMY_NO_FLOAT = 0,

	ARMY_MISSILE_FLOAT,
	ARMY_GRENADE_FLOAT,
	ARMY_MORTAR_FLOAT,
	ARMY_RIFLE_FLOAT,
	ARMY_FLAME_FLOAT,
 	ARMY_EXPLOSION_FLOAT,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_FLOAT
} FLOAT_TYPE;

// ARMY troop types
typedef enum
{
	ARMY_NO_MEN = -1,
	ARMY_RIFLE_MEN = 0,
	ARMY_GRENADE_MEN,
	ARMY_FLAME_MEN,
	ARMY_BAZOOKA_MEN,
	ARMY_SWEEPER_MEN,
	ARMY_MORTAR_MEN,
	ARMY_MINER_MEN,
	ARMY_SPECIAL_MEN,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_TROOPER
} TROOPER_TYPE;

#define ARMY_FIRST_TROOPER ARMY_RIFLE_MEN


// ARMY vehicle types
typedef enum
{
	ARMY_NO_ASSET = 0,
	ARMY_MAINBASE,
	ARMY_TURRET,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_ASSET
} ASSET_TYPE;

typedef enum
{
	TARGETING_NULL,
	TARGETING_AGGRESSIVE,
	TARGETING_PASSIVE,
	TARGETING_DEFENSIVE,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_TARGETING
} TARGETING;

// COMMON fields to all world objects
struct OBJECTSTRUCT;				// forward ref
#define OBJECT struct OBJECTSTRUCT

struct WEAPONSTRUCT;				// forward reference
#define WEAPON struct WEAPONSTRUCT
#include "weaponp.h"

struct ITEM
{
	LONG			nUniqueID;		// the unique ID for this object

#ifdef _DEBUG
    // these next 4 fields are mirrored for human readability during
    // debugging. Do not use them directly in code. Use the macros below.
    // That way we can change macros without changing code, should efficiency
    // be an issue. BW
	ARMY_TYPE		exWhoseArmy;	// use ITEM_ARMY(pItem) instead
    ITEM_TYPE		exOType;		// use ITEM_TYPE(pItem) instead
	short			exType;			// use ITEM_CLASS(pItem) instead
    short			exID;			// use ITEM_INDEX(pItem) instead
#endif

    // location and orientation data
	SPOINT			position;		// position within the world
	short			facing;			// directional facing of item (0..255)
    IPOINT			tile;			// tile of location

	SPOINT			oldPosition;	// prior position within the world
	short			oldFacing;		// prior facing of item (0..255)
    IPOINT			oldTile;		// prior tile of the world

	short			nStrength;		// item current strength
	short			nMaxStrength;	// item full strength

	WEAPON			*pWeapon;		// weapon info
	unsigned char	bItemFlags;		// item bit flags

	unsigned char	fireDirection;		// direction trooper wants to fire in
	char			fireFlag;			// lock flag for changing fireing info above
	SHORT			fireDistance;		// distance trooper wants to fire

	// tad data
	void*			pTad;			// item TAD block
    ITEM*			pVictim;		// victim to be attacked by this object

    // visibility data
    int				seen[ARMY_LAST_ARMY];//when did army x last see thisthing
    int				seentemp;		// seen or not this frame
                                    // You can always see your own forces.
    SPOINT			seenWhere[ARMY_LAST_ARMY]; // where did he get seen

	//for event management
	int				eventNum;		//event number this item will generated if destroyed/damaged
									//0 if none
	char*			label;
	struct ITEM *   next;
	short			temp;
};


// given an item, retrieve information about it
#define ITEM_UID(x) (((ITEM*)x)->nUniqueID)
#define ITEM_ARMY(x) ( (ARMY_TYPE) EXTRACT_ARMY( ((ITEM*)x)->nUniqueID ))
#define ITEM_TYPE(x) ( (ITEM_TYPE) OBJTYPE( ((ITEM*)x)->nUniqueID  ))
#define ITEM_CLASS(x) ( SUB1TYPE( ((ITEM*)x)->nUniqueID  ))
#define ITEM_INDEX(x) ( SUB2TYPE( ((ITEM*)x)->nUniqueID  ))

#define ITEM_POSITION(x)  (((ITEM*)x)->position)
#define ITEM_X(a)  (((ITEM*)a)->position.x)
#define ITEM_Y(a)  (((ITEM*)a)->position.y)
#define ITEM_LOCATION(x)  (((ITEM*)x)->location)
#define ITEM_FACING(x)  (((ITEM*)x)->facing)

#ifndef __AIROUTER_H__
#include "Airouter.h"
#endif

// ITEM flags
#define	ITEM_CLEAR				(unsigned char)0x00
#define	ITEM_ACTIVE				(unsigned char)0x01
#define	ITEM_UPDATED			(unsigned char)0x02
#define	ITEM_INVISIBLE			(unsigned char)0x04
#define	ITEM_REVERSED			(unsigned char)0x08
#define	ITEM_STRATEGIC			(unsigned char)0x10
#define	ITEM_LEFT				(unsigned char)0x20
#define	ITEM_RIGHT				(unsigned char)0x40
#define	ITEM_UNUSED_A			(unsigned char)0x80

#define	SET_ITEM_FLAGS( bFlags, mask )		((bFlags) |= (mask))
#define	CLEAR_ITEM_FLAGS( bFlags, mask )	((bFlags) &= ~(mask))

#define	IS_ITEM_CLEAR( bFlags )			((bFlags))
#define	SET_ITEM_CLEAR( bFlags )		((bFlags) = ITEM_CLEAR)

#define	IS_ITEM_UPDATED( bFlags )		(((bFlags) & ITEM_UPDATED))
#define	SET_ITEM_UPDATED( bFlags )		((bFlags) |= ITEM_UPDATED)
#define	CLEAR_ITEM_UPDATED( bFlags )	((bFlags) &= ~ITEM_UPDATED)

#define	IS_ITEM_ACTIVE( bFlags )		(((bFlags) & ITEM_ACTIVE))
#define	SET_ITEM_ACTIVE( bFlags )		((bFlags) |= ITEM_ACTIVE)
#define	CLEAR_ITEM_ACTIVE( bFlags )		((bFlags) &= ~ITEM_ACTIVE)
#define	SET_ITEM_INACTIVE( bFlags )		((bFlags) &= ~ITEM_ACTIVE)

#define	IS_ITEM_INVISIBLE( bFlags )			(((bFlags) & ITEM_INVISIBLE))
#define	SET_ITEM_INVISIBLE( bFlags )		((bFlags) |= ITEM_INVISIBLE)
#define	CLEAR_ITEM_INVISIBLE( bFlags )		((bFlags) &= ~ITEM_INVISIBLE)


//-------------------------------------------------------------------------
// FLOAT structure
typedef struct
{
	ITEM		common;			// common components of all objects
	// ADD NEW FIELDS AFTER THIS POINT

	// variable info
	ANIM*		pAnimation;		// animation information
	LONG		total_distance;
	LONG		max_distance;
	unsigned char dest_height;	// destination height
    UID			fromUID;		// who fired this originally
	WEAPON_TYPE weaponType;
	short		link_missile;
	ULONG		sndID;
} FLOAT_OBJ;

struct UNITSTRUCT;					// forward reference
#define UNIT struct UNITSTRUCT
struct TROOPERSTRUCT;					// forward reference
#define TROOPER struct TROOPERSTRUCT
struct SARGESTRUCT;					// forward reference
#define SARGE struct SARGESTRUCT

#include "avatar.h"			
#include "vehiclep.h"
#include "trooperP.h"
#include "sargeP.h"
#include "unitP.h"
#include "object.h"


// Army Deployment Structure
typedef struct
{
	char	ammo[SARGE_LAST_WEAPON];
	char	reserved_char1;

	short	strength;
	short	reserved_short_1;

	long	vehicle;		// vehicle UID
	long	reserved1;
} EXTRA_DATA;	// size of should be 4

typedef struct
{
	int				eType;			// type of unit or vehicle
	SPOINT			location;		// deployment position in world coordinates
	ITEM*			pItem;
	long			nUniqueID;
	unsigned char	facing;			// facing of deployed unit
	unsigned char	deployed;		// is unit deployed?
	unsigned char	number;			// number of troopers in unit
	char			text[65];
	EXTRA_DATA		extra_data;
	SPOINT			deadPosition;   // where it died
	unsigned char	dead;			// true if it died
} DEPLOYED;

typedef struct
{
	int			eTargetID;			// what type of target are we going after
	SPOINT		targetPos;			// target position in world coordinates
	SPOINT		stepPos;			// next reachable position ( a step )
									//		in world coordinates
} TARGET;


// COMMON Position references to all world objects
typedef struct
{
	SPOINT			position;		// current object position
	SPOINT			oldPosition;	// previous object postion
	SPOINT			goalPosition;	// next goal position for object
	SPOINT			targetPosition;	// final position for object
	SPOINT			parentPosition;	// current parent position
} POSITIONS;


// Army Reserves Structure
typedef struct
{
	char	nUnitsAvail[ ARMY_LAST_UNIT ];
	char	nVehiclesAvail[ ARMY_LAST_VEHICLE ];
	char	nResourcesAvail[ ARMY_LAST_RESOURCE ];
} RESERVES;

#define ARMY_LEGION_MISSILES 20

#define REMOVE_INFLUENCE 1
#define ADD_INFLUENCE 2


// LEGION structure
typedef struct
{
	int		nTotalUnits;							// number of active units
    UNIT* 	pUnitList;								//all units consecutive
    UNIT* 	pLastUnitList;							//end units consecutive
	UNIT*	pUnits[ ARMY_LAST_UNIT ];				// unit information
    UNIT* 	pLastUnit[ARMY_LAST_UNIT];				// end of units
    unsigned char* pUnitPrivateData;				// data for units

	char		nNumberOfVehicles;					// number of active vehicles
    VEHICLE*	pLegionVehicles[ARMY_MAX_VEHICLES]; // all vehicles of the army

	int				nAssets;						// #of assets owned by this legion
	OBJECTSTRUCT	**AssetList;					// array of ptrs to assets

	SARGE		Sarge;								// Sarge

	char		AirResources[ARMY_LAST_RESOURCE];	// number of air resources

	int			which_missile;						// which missile is currently assignable
	FLOAT_OBJ	Projectiles[ARMY_LEGION_MISSILES];	// total legion projectiles
	FLOAT_OBJ	Shadows[ARMY_LEGION_MISSILES];		// total legion projectile shadows
} LEGION;

#define FOR_EACH_ARMY(eArmy)	for (eArmy=ARMY_PLAYER;\
                                     eArmy < ARMY_LAST_ARMY;\
                                    ++eArmy)
 // must maintain all 4 armies for some missions and multiplayer

extern inline int GetNextDeployedArmy(int eArmy);


#define FOR_EACH_DEPLOYED_ARMY(eArmy) for( eArmy = ARMY_PLAYER;\
										   eArmy < ARMY_LAST_ARMY;\
										   eArmy=GetNextDeployedArmy(eArmy) )

//extern inline 
int GetNextLocalArmy(int eArmy);

#define FOR_EACH_LOCAL_ARMY(eArmy)	for (eArmy=ARMY_PLAYER;\
                                    eArmy<ARMY_LAST_ARMY;\
                                    eArmy=GetNextLocalArmy(eArmy) )

#define FOR_EACH_UNIT_TYPE(eType)	for (eType = ARMY_FIRST_UNIT;\
                                         eType < ARMY_LAST_UNIT; ++eType)
    
#define FOR_EACH_UNIT_OF_TYPE(legion,type,unit) for (unit = legion->pUnits[type];\
                                             unit < legion->pLastUnit[type];\
                                             ++unit)

#define FOR_EACH_UNIT(legion,unit)  for (unit = legion->pUnitList;\
                                         unit < legion->pLastUnitList;\
                                         ++unit)

#define FOR_EACH_TROOPER_TYPE(eType)	for (eType = ARMY_FIRST_TROOPER;\
                                         eType < ARMY_LAST_TROOPER; ++eType)
    
#define FOR_EACH_VEHICLE(legion,vehicle)  for (vehicle=0;\
                                         vehicle < legion->nNumberOfVehicles;\
                                         ++vehicle)

typedef struct
{
	TARGETING		eTargetingId;	// default targeting type ID
	RESERVES		Reserves;		// Orders and startup information
	LEGION			Legion;			// the actual army information
	BOOL			bAlliances[ARMY_LAST_ARMY];
	char			nSargeTypesAvail[ ARMY_LAST_TROOPER ];
	int				nPoints;		// point total for this army
	int				Status;			// 0 = not in play, 1 = human control
	int				sarges_killed[ARMY_LAST_ARMY];
	int				sarges_killedby[ARMY_LAST_ARMY];
	int				flags_collected[ARMY_LAST_ARMY];

	int				troops_killed;
	int				vehicles_killed;

	int				sarge_kills;
} ARMY;


// Army Mission Structure
typedef struct
{
	RESERVES	Reserves;		// available units and vehicles
	SHORT		nDeployed;		// number of deployed units
	DEPLOYED*	pDeployment;	// list of deployed units
} FORCE;

// Army Mission Structure
typedef struct
{
	char		scenarioName[ SCENARIO_NAME_SIZE ];
	FORCE		forces[ARMY_LAST_ARMY];
} MISSION;

// Army Scenario Structure
typedef struct
{
	USHORT		nNumPlayers;	// Number of "players" in the scenario
	USHORT		nNumMissions;	// Number of missions in the scenario
	MISSION		*pMissions;		// mission data, one for each mission in the scenario
} SCENARIO;

// Army Mission Save Data Block definition
typedef struct
{
	char		missionName[ MISSION_NAME_SIZE ];
	char		fileName[ MISSION_FILENAME_SIZE ];
} MISN;

//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================
extern	long			playCycle;

extern	Sprite			invisible_sprite;

extern	MISSION			Missions[ARMY_LAST_ARMY];
extern	ARMY			Armies[ARMY_LAST_ARMY];
extern	SCENARIO		Scenario;

extern COMMAND_LIST* VehicleCommands[ARMY_LAST_VEHICLE];
extern COMMAND_LIST* TurretCommands[ARMY_LAST_VEHICLE];
extern COMMAND_LIST* TrooperCommands[ARMY_LAST_TROOPER];

extern	UNIT*			pTestUnit;
extern	UNIT*			pAIUnit;

extern	MISN*			pArmySaveData;

extern	int				gAMCampaignID;
extern	int				gAMScenarioID;
extern	int				gAMMissionID;

//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================
extern	BOOL		ArmyInit( void );
extern	void		ArmyExit( void );
extern	BOOL		ArmyGraphicsLoad( void );
extern	void		ArmyGraphicsFree( void );
extern	BOOL		ArmyCreate( void );
extern	void		ArmyUpdate( void );
extern	void		ArmyUpdateInSetup( void );
extern	int			ArmyAvailable( LONG nUniqueID, int eArmy, int eObjType, int eSubType1, int eSubType2 );
extern	void		ArmyBuildBases( int nNumPlayers );
extern	void		ArmyMissionInit( ARMY_TYPE eArmy, int mission );
extern	unsigned char	ArmyMissionFailures( void );
extern	void		ArmyCurrentIndecies( int nCampaignIndex, int nScenarioIndex, int nMissionIndex );
extern	BOOL		ArmyAtScenarioEnd( void );
extern	BOOL		ArmyHaveNextMission( void );
extern	BOOL		ArmyHaveNextScenario( void );
extern	BOOL		ArmyHaveNextCampaign( void );
extern	BOOL		ArmyGetMission( void );

extern inline VEHICLE*	ArmyGetVehicle( int eArmy );
extern inline LEGION*	ArmyGetLegion( int eArmy );

RETERROR	FloatCreate( FLOAT_OBJ* pFloat, ARMY_TYPE eArmy, SPOINT* pPosition );
void		FloatDelete( FLOAT_OBJ* pFloat );
void		ProjectileRemoteUpdate( int eArmy );
void		ProjectileUpdate( int eArmy );
FLOAT_OBJ	*ProjectileSet(int eArmy, WEAPON *pWeapon, int x, int y, int z, int direction, int distance, int height, VEHICLE * pVehicle,UID fromUID);
void		SetFloatSnd(FLOAT_OBJ *pMissile, ULONG sndID);

void		PlayerColorMapping();
BYTE*		UnitColorTable(ARMY_TYPE eArmy);
SHORT		PlayerColor(ARMY_TYPE eArmy);

// aiinput.cpp routines
char*		VehicleName( int eVehicle );
char*		TrooperName( int eTrooper );
char*		WeaponName( int	eWeapon );
char*		UnitTypeName( int eUnit );
char*		ItemName(ITEM *pObj);

// Army Alliance prototypes
extern	void	ArmySetAlliance(ARMY_TYPE eMyArmy, ARMY_TYPE eNewAlly, BOOL bIsAlly );
extern	BOOL	ArmyHaveAllianceWith(ARMY_TYPE eMyArmy, ARMY_TYPE eAlly );

extern	int		ArmySurvivingTroops( ARMY_TYPE eMyArmy );	// number of units alive at end of mission
extern	int		ArmyCasualties( ARMY_TYPE eMyArmy );		// number of troopers killed
extern	int		ArmyVehicleCasualties( ARMY_TYPE eMyArmy );	// number of vehicles killed
extern	int		ArmyTroopsKilled( ARMY_TYPE eMyArmy );		// number of enemy troopers killed
extern	int		ArmyVehiclesKilled( ARMY_TYPE eMyArmy );	// number of enemy vehicles killed
extern	int		ArmySargeKills( ARMY_TYPE eMyArmy );		// kills by Sarge
extern	int		ArmyPerformance( ARMY_TYPE eMyArmy );		// expected score for this mission
extern	int		ArmySargesKilled( int eMyArmy );
extern	int		ArmySargeDeaths( int eMyArmy );
extern  int		ArmyFlagsCollectedOfArmy( int eMyArmy, int eOpArmy );
extern  int		ArmyCollectedFlag( int eMyArmy, int eOpArmy );


extern	void	ArmyMissionSave( FILE* pSaveFile );
extern	void	ArmyLoadSavedMission( int	nPlayerIndex, int nMissionID );
extern	BOOL	ArmyIsFirstMission( void );
extern	void	ArmiesUpdatePads(void);
extern	void	ArmiesClearOldLocation(void);

extern	void	ArmySetNextAdvance( ULONG nCampaignIndex, ULONG nScenarioIndex, ULONG nMissionIndex );
extern	void	ArmyCampaignFindNextAdvance( void );
extern	void	ArmyApplyNextAdvance( void );
extern	void	ArmySetCurrentCampaignID( int nCampaignID );
extern	void	ArmySetCurrentScenarioID( int nScenarioID );
extern	void	ArmySetCurrentMissionID( int nMissionID );
extern	void	ArmyUnitTypeExist(int eWeapon);

extern	CAMPAIGNREF* GetCampaign( void );
extern	SCENARIOREF* GetScenario( void );
extern	MISSIONREF* GetMission( void );

// global variables
extern char	aiPlayers;

#endif		// __ARMY_H__

//=========================================================================
//								EOF
//=========================================================================
