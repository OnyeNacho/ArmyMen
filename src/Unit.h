//========================================================================
//	FILE:			$Workfile: Unit.h $
//
//	DESCRIPTION:	unit headers
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		Thursday, June 02, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Unit.h 103   3/27/98 7:32p Bwilcox $
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
//  $Log: /ArmyMen/src/Unit.h $
//  
//  103   3/27/98 7:32p Bwilcox
//  
//  102   3/25/98 5:18p Bwilcox
//  script notify for mp capture data
//  
//  101   3/12/98 7:35p Bwilcox
//  scriptrecharge
//  
//  100   3/12/98 5:22p Bwilcox
//  air fixes
//  
//  99    2/27/98 10:08p Bwilcox
//  fixing unitinitaial deploy for vehicles
//  
//  98    2/27/98 7:07p Nrobinso
//  unit deploy takes a vehicle pointer
//  
//  97    2/26/98 4:39p Awerner
//  added script support for AIRDROP command
//  
//  since this may be the last time I ever check a file into the armyman
//  project, and since I've tried to make a tradition of adding glib little
//  observations and suchlike to my checkin notices, I'd just like to take
//  this moment to say, and I'm getting all choked up here, I love you
//  guys! (sniffle)
//  
//  96    2/17/98 1:44p Nrobinso
//  script visible back in
//  
//  95    2/16/98 9:25p Nrobinso
//  script display bmp
//  
//  94    2/16/98 4:16p Nrobinso
//  change showbmp to take a filename
//  
//  93    2/15/98 12:15p Bwilcox
//  removedscript visible and invisible. added scriptbmp
//  
//  92    2/03/98 10:37a Bwilcox
//  sargedrop on deleting army
//  
//  91    2/02/98 4:25p Bwilcox
//  nits in vehicles fix. deploy when sareg exit vehicle
//  
//  90    2/02/98 4:06p Bwilcox
//  
//  89    1/30/98 4:29p Bwilcox
//  fixing tab ring cycle
//  
//  88    1/29/98 11:22a Bwilcox
//  script explode now takes optional type of explosion
//  
//  87    1/28/98 8:20p Bwilcox
//  Script visible and invisible for units
//  
//  86    1/19/98 3:24p Awerner
//  Added ALLY and UNALLY, MAKESTRATEGIC and MAKENONSTRATEGIC, and changed
//  get_ and drop_ to take specific item names
//  
//  85    1/15/98 12:58p Bwilcox
//  scriptfollow order extended to optional then clause
//  
//  84    1/13/98 8:49a Bwilcox
//  fixing goal fix of vehcile
//  
//  83    1/12/98 7:15p Bwilcox
//  visibility tmp added to common, and moved itemsees army from
//  sarge/vehicle to unit.cpp
//  
//  82    1/06/98 3:25p Awerner
//  added in script ALLY command
//  
//  81    12/18/97 6:16p Bwilcox
//  converting epoint to spoint (not spoint* notation)
//  
//  80    12/11/97 12:10p Bwilcox
//  added args to scriptdeploy
//  
//  79    12/11/97 9:46a Bwilcox
//  removed teleport command
//  
//  78    12/09/97 12:12p Phu
//  
//  77    12/05/97 5:15p Awerner
//  added code so vehicles can't be placed on units
//  
//  76    12/05/97 3:49p Awerner
//  Changed the HEAL command to take a percentage parameter, and slightly
//  modified the way AFTER events work
//  
//  75    11/26/97 2:01p Awerner
//  added in PLACEOBJECT script command
//  
//  74    11/20/97 12:44p Nrobinso
//  UnitCreateAll takes number of units to create of that type
//  
//  73    11/20/97 10:55a Bwilcox
//  unitsafedeploy made visible
//  
//  72    11/20/97 10:43a Bwilcox
//  paratrooper suppoert
//  
//  71    11/19/97 6:30p Awerner
//  added NUKE command
//  
//  70    11/18/97 3:12p Awerner
//  
//  69    11/18/97 4:13p Bwilcox
//  resurrect args fixed
//  
//  68    11/17/97 7:41p Bwilcox
//  added behavior parameter to unitdeploy and unitinitialdeploy to
//  improve trace
//  
//  67    11/17/97 2:16a Bwilcox
//  
//  66    11/17/97 1:58a Bwilcox
//  sitrep use
//  
//  65    11/05/97 7:07p Bwilcox
//  armyresentdeathevents now resends death events on mission startup
//  
//  64    10/30/97 11:18a Bwilcox
//  removed obsolete pickanddrop unit code
//  
//  63    10/29/97 1:49p Awerner
//  Added REMOVEOBJECT command to scripting language
//  
//  62    10/24/97 9:47a Bwilcox
//  unit vehicle code fixed
//  
//  61    10/24/97 9:10a Bwilcox
//  cleaning up messages and doing unit into vehcle
//  
//  60    10/23/97 4:06p Bwilcox
//  removing dead code relating to units entering vehicles and installing
//  new code
//  
//  59    10/21/97 4:29p Bwilcox
//  revising unitdeploy into unitinitialdeploy and unitdeploy, fixed
//  multiplayer bug
//  
//  58    10/16/97 6:26p Nrobinso
//  add nMaxStrength to ITEM; made Unit consistent with new scheme, put
//  number of troopers inot pUnit->troops
//  
//  57    10/15/97 5:05p Nrobinso
//  all deploys now consistent
//  
//  56    10/14/97 9:12p Nrobinso
//  add UnitValidateAttackers
//  
//  55    10/13/97 6:07p Bwilcox
//  eventtype argument added to script orders and unit data
//  
//  54    10/13/97 4:31p Bwilcox
//  scriptexplode
//  
//  53    10/13/97 2:29p Bwilcox
//  supporting variable numbers of troopers from map data
//  
//  52    10/13/97 10:02a Aburgess
//  added global reference to UnitValidateTad
//  
//  51    10/05/97 1:17p Bwilcox
//  added unitgettrooperstatus
//  
//  50    10/02/97 2:38p Awerner
//  Added scripting for Resurrection and Airstrikes
//  
//  49    10/02/97 2:19p Bwilcox
//  added scriptresurrect
//  
//  48    10/02/97 12:25p Bwilcox
//  airstrike added
//  
//  46    9/30/97 2:59p Bwilcox
//  added scriptteleport
//  
//  45    9/29/97 1:25p Bwilcox
//  added scriptfollow
//  
//  44    9/27/97 3:15p Bwilcox
//  scripts can now do a GOTO on sarge
//  
//  43    9/26/97 11:58a Bwilcox
//  changes args to scriptDeploy
//  changed name of scriptUnitMode to ScriptAtMode
//  
//  42    9/25/97 2:49p Bwilcox
//  revise trooper representation in units
//  
//  41    9/24/97 5:26p Bwilcox
//  added scriptheal and scriptsetweapon
//  
//  40    9/24/97 1:23p Bwilcox
//  added ScriptAIControl and ScriptUserControl
//  
//  39    9/23/97 6:23p Bwilcox
//  added scriptunitmode
//  
//  38    9/23/97 5:53p Bwilcox
//  protos for script functions
//  
//  37    9/22/97 1:50p Bwilcox
//  added behaviors separable from orders, so orders will become GOTO with
//  pre and post behaviors
//  
//  36    9/14/97 7:02p Bwilcox
//  
//  35    9/14/97 1:32p Bwilcox
//  
//  34    9/14/97 12:19p Bwilcox
//  influence stuff moved to deadcode.cpp (not in project)
//  
//  33    9/10/97 4:55p Bwilcox
//  UnitsValidateLocations added
//  
//  32    9/09/97 9:29a Nrobinso
//  UnitDeploy and TrooperDeploy take a position and facing
//  
//  1     6/23/97 11:05p Bwilcox
//  
//  $Nokeywords:$
///========================================================================

#ifndef __UNIT_H__
#define __UNIT_H__

#include "tad.h"
        
            // accessing troopers of unit.
//  There is 1 leader and some number of followers.
#define THE_LEADER(unit)  (unit->pTroops[unit->nLeader])
#define FOR_EACH_TROOPER(unit,trooper,i)\
        for (i=0,trooper = unit->pTroops[0];\
             i <= unit->nLastTroop;\
             ++i,trooper=unit->pTroops[i])

            // station status
#define IS_PRESTATION(x)  (((UNIT*) (x))->focusArrived == FALSE)
#define IS_POSTSTATION(x)  (((UNIT*) (x))->focusArrived == TRUE)

            // accessing mode of unit.
//		ALIVE means not dead or dying (might be usable in future)
// 		STILL means unit is not involved in a fight, still, and is on map
// 		MOVING means unit is not involved in a fight, going somewhere on map
// 		ENGAGED means unit is involved in a fight
// 		ACTIVE means deployed and targetable (not dying)
// 		ON_MAP means unit is deployed and visible (may be dying or in vehicle)
// 		IN_HQ means unit is not released to user at present
//		IN_VEHICLE means unit is being transported by user

typedef enum 
{
    STATUS_DEAD,
    STATUS_DYING,
    STATUS_WEAK,
    STATUS_STRONG
} HEALTH;

// gone forever
#define UNIT_DEAD(x)((x)->mode == UNIT_DEAD)
// not yet deployed
#define UNIT_IN_HQ(x) ((x)->mode == UNIT_IN_HQ)

    // these are all on the map  ...
#define UNIT_ON_MAP(x) ((x)->mode >= UNIT_IN_VEHICLE)

// being carried
#define UNIT_IN_VEHICLE(x) ((x)->mode == UNIT_IN_VEHICLE)
// not going anywhere
#define UNIT_STILL(x)	((x)->mode == UNIT_STILL)
// moving someplace
#define UNIT_MOVING(x)	((x)->mode == UNIT_MOVING)
// in a fight
#define UNIT_ENGAGED(x)	((x)->mode == UNIT_ENGAGED)
// dying on the map
#define UNIT_DYING(x)((x)->mode == UNIT_DYING)

#define UNIT_ALIVE(x) ((x)->mode != UNIT_DEAD && (x)->mode != UNIT_DYING)

// unit must be on map and not hidden in a vehicle    
#define UNIT_IN_OPEN(x) ((x)->mode == UNIT_STILL || (x)->mode == UNIT_MOVING ||(x)->mode == UNIT_ENGAGED)  


            //	subroutines with side effects
// game startup routines
BOOL		UnitLoad( void );
void		UnitCreateAll( ARMY_TYPE eArmy, int eUnitType, UNIT* pUnits, int nNumberOfUnits);
void 		UnitTrooperCreate(UNIT* pUnit,int n);

// enter a unit into play
void		UnitDeploy(UNIT *pUnit, SPOINT *pPos, short facing,BEHAVIOR atmode);
void		UnitInitialDeploy(UNIT *pUnit, SPOINT pPos, short facing, BEHAVIOR atmode, VEHICLE *pVehicle = NULL);
void		UnitDeployPosition( UNIT* pUnit, SPOINT *pPos, short facing);

// change operating behavior of a unit
void		UnitOrders(UNIT* pUnit,UNIT_ORDER orders,SPOINT loc,ITEM* pTad,SPEED eSpeed);


// simulation update routines
void 		UnitUpdate();		// updates all controllable units
 
// exit a unit from play
void		UnitKill( UNIT* pUnit );
void		UnitUndeploy(UNIT *pUnit);

// game wind-down routines
void 		UnitDisband(LEGION* pLegion);
void		UnitFree( void );

// debug routines 
void	StartUnit();
void	StopUnit();
void 	UnitDumpAll(int eArmy);
void 	UnitFireDraw(UNIT* pUnit,HDC hDC);
void 	UnitViewDraw(UNIT* pUnit);
void 	UnitFireAllDraw(UNIT* pUnit);
void 	UnitsValidateLocations(IPOINT tile);

        // informational functions about a specific unit (no side effects)
int			UnitTroopCount(UNIT* pUnit);
long		UnitFiringRange( UNIT* pUnit );
TROOPER*	UnitFindClosestTrooper(UNIT* pUnit,SPOINT* point);
HEALTH	 	UnitGetTrooperStatus(UNIT* pUnit, int nTrooper);
int	UnitAvailable( int eArmy, int eType );
long UnitSafeDeploy(IPOINT index);
long ParaSafeDeploy(IPOINT index);

        // information about multiple units or to find a unit (no side effects)
UNIT*		UnitFind( LONG nUniqueID );
int			UnitsInHQ( ARMY_TYPE eArmy, UNIT_TYPE eUnitType, UID* pUnitUIDs);
UNIT*		UnitNextInHQ( ARMY_TYPE eArmy, int eUnitType );
UNIT*		UnitGetNextFunctional(UNIT* pOldUnit );
ITEM*		UnitGetNextTarget(ITEM* pOldItem );
        // information about paratroopers
int			ParatroopersInHQ( ARMY_TYPE eArmy, UID* pUnitUIDs);
UNIT*		ParatrooperNextInHQ( ARMY_TYPE eArmy );

extern char* UnitOrderText[];
    
TROOPER*		GetTrooperOnTile(int x, int y);

SPOINT ItemClosestWhere(ITEM* pItem,SPOINT where);

void UnitValidateTad();
void UnitValidateAttackers( UNIT* pUnit );

void UnitEnterVehicle(UNIT* pUnit, VEHICLE* pVehicle);
void UnitExitVehicle(UNIT* pUnit,SPOINT position,int facing);
void ArmiesRegenerateDeathEvents();
void UnitMissionInit();



void ScriptOrder(UID namedItem,UNIT_ORDER order,
                 BEHAVIOR inmode, BEHAVIOR arrivalmode,
                 BOOL speed,
                 SPOINT* position, UID destinationItem,
                 int eventNumber,int eventtype);
void ScriptFollow(UID namedItem,UID followItem,BEHAVIOR inmode,
                  BEHAVIOR arrivalmode,
                 int eventNumber,int eventtype);
void ScriptDeploy(UID namedItem, BEHAVIOR atMode,SPOINT* position,UID locationItem);
void ScriptUndeploy(UID namedItem);
void ScriptUnitMerge(UID namedUnit,UID otherUnit);
void ScriptAtMode(UID namedUnit,BEHAVIOR atMode);
void ScriptHeal(UID namedItem, int percentToHeal);
void ScriptSetWeapon(UID namedUnit,WEAPON_TYPE eWeapon);
void ScriptUserControl(UID namedItem);
void ScriptAIControl(UID namedItem);
void ScriptAirstrike(SPOINT* position,UID locationItem);
void ScriptResurrect(UID namedItem, SPOINT* position, UID armyItem);
void ScriptExplode(SPOINT* position,UID armyItem,int type);
void ScriptRemoveObject(UID nUid);
void ScriptNuke(UID namedItem);
void ScriptPlaceObject(UID nUid, SPOINT *position, UID whereItem);
void ScriptNotify(UID nUid, UID whereItem,int which);
void ScriptAlly(ARMY_COLOR army1, ARMY_COLOR army2);
void ScriptUnAlly(ARMY_COLOR army1, ARMY_COLOR army2);
void ScriptVisible(UID namedItem,int seen);
void ScriptAirdrop(SPOINT* position,UID locationItem, ARMY_COLOR whichColor);
void ScriptRecharge(UID army,int number);


#endif    
