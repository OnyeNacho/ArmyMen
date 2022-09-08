/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Vehicle.h $
//
//	DESCRIPTION:	Vehicle movement interface
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Vehicle.h 63    4/03/98 9:03p Bwilcox $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Vehicle.h $
//  
//  63    4/03/98 9:03p Bwilcox
//  clean up vehicle movement layer code
//  
//  61    3/26/98 9:21p Bwilcox
//  
//  60    3/26/98 9:00p Bwilcox
//  subtracttraff dones less for vehicles
//  
//  59    3/26/98 2:39p Bwilcox
//  vehicle in movement layer split into new layer
//  
//  58    3/19/98 1:49p Nrobinso
//  change vehicle sfx
//  
//  57    3/08/98 4:41p Phu
//  don't allow switch to other weapons when in vehicle
//  
//  56    3/08/98 3:20p Phu
//  prevent sarge from appearing in movement mask of dead vehicle.
//  don't allow fire if weapon is empty
//  
//  55    2/25/98 5:41p Nrobinso
//  update VEHICLE_ON_MAP
//  
//  54    2/21/98 5:49p Nrobinso
//  
//  53    2/20/98 6:17p Nrobinso
//  remove outdated calls
//  
//  52    2/12/98 9:46p Nrobinso
//  remove unused code
//  
//  51    2/06/98 4:32p Bwilcox
//  making addvehicletomove visible
//  
//  50    1/17/98 8:17p Nrobinso
//  remove unused code
//  
//  49    12/19/97 2:12p Bwilcox
//  more epoint to spoint conversion
//  
//  48    12/11/97 10:02p Nrobinso
//  ALT bit
//  
//  47    12/09/97 5:57p Nrobinso
//  changed VehiclePlayerClearInput to PlayerClearInput
//  
//  46    12/09/97 12:12p Phu
//  
//  45    12/07/97 6:52p Phu
//  
//  44    12/05/97 9:55p Nrobinso
//  added VEHICLE_ON_MAP()
//  
//  43    12/05/97 5:15p Awerner
//  added code so vehicles can't be placed on units
//  
//  42    12/05/97 4:27p Awerner
//  In multiplayer setup, vehicles now deploy at the angle they appear to
//  be at
//  
//  41    12/04/97 11:24a Awerner
//  Added red and green cursors to multiplayer setup
//  
//  40    12/02/97 4:16p Awerner
//  Added ClearVehicleFromMovementLayer function
//  
//  39    11/20/97 6:08p Nrobinso
//  cheat key
//  
//  38    11/17/97 11:08a Nrobinso
//  projectile hit code added
//  
//  37    11/15/97 5:17a Bwilcox
//  unifying remote updates of vehicles with local updates
//  
//  36    11/11/97 2:34p Nrobinso
//  center aiming curosr off of aiming hotspot (on trooper anim or turret
//  anim)
//  
//  35    11/11/97 8:57a Nrobinso
//  FOR_EACH_VEHICLE_TYPE doesn't loop thru commander
//  
//  34    11/07/97 4:05p Nrobinso
//  rename turret functions
//  
//  33    11/04/97 4:04p Awerner
//  Vehicles now intersect with each other properly
//  
//  32    10/30/97 11:12a Bwilcox
//  removed vehiclepickingup and dropping code that was obsolete
//  
//  31    10/30/97 10:20a Nrobinso
//  add slow action
//  
//  30    10/24/97 11:52a Nrobinso
//  remove RepCnt from key interface routines
//  
//  29    10/23/97 4:06p Bwilcox
//  removing dead code relating to units entering vehicles and installing
//  new code
//  
//  28    10/23/97 11:01a Awerner
//  Vehicle movement masks now only use the appropriate half of the vehicle
//  (front or back)
//  
//  27    10/22/97 1:47p Awerner
//  Added vehicle deployment to the multiplayer dashboard
//  
//  26    10/22/97 10:17a Bwilcox
//  remote vehicle deploy, enter and exit of vehicle
//  
//  25    10/21/97 11:09a Bwilcox
//  reserving E for enter/exit vehicle
//  
//  24    10/21/97 11:03a Awerner
//  Restored screen scrolling following vehicles
//  
//  23    10/20/97 3:53p Nrobinso
//  rename vehicle user interface routines
//  
//  22    10/17/97 2:31p Nrobinso
//  move non-vehicle commands out to commands.cpp
//  
//  21    10/15/97 5:03p Nrobinso
//  all deploys now consistent
//  
//  20    10/14/97 3:36p Nrobinso
//  simplify vehicle access
//  
//  19    10/10/97 2:10p Bwilcox
//  added vehiclenextinhq function and deployposition data in struct
//  
//  18    10/07/97 5:33p Awerner
//  First check-in of new dashboard and new scrolling mode
//  code
//  
//  16    9/09/97 9:31a Nrobinso
//  VehicleDeploy and UnitDeploy now take position and facing
//  
//  15    8/26/97 4:36p Bwilcox
//  split vehicledeploy into 2 functions
//  
//  14    8/26/97 11:17a Bwilcox
//  adjusting vehicledeploy and undeploy
//  
//  13    8/26/97 10:00a Bwilcox
//  vehiclecreate now creates explicit kinds of vehicles from reserves in
//  scenaio
//  
//  12    8/25/97 5:10p Bwilcox
//  removal of legions pVehicle, rough support for multiple vehicles.
//  
//  11    8/25/97 3:32p Bwilcox
//  vehicledeploy/undeploy messages removed, code changes around vehicle
//  create.deploy and sarge in vehicle
//  
//  10    8/25/97 1:08p Bwilcox
//  sarginvehicle calls and associated data changed from item to vehicle
//  VehicleScroll added and called whenever sarge enters vehicle.
//  Exiting vehicle rescrolls to sarge
//  
//  9     8/22/97 2:08p Awerner
//  The vehicle movement now uses a better algorithm to
//  check for intersection with untrafficable regions
//  
//  8     8/21/97 6:57p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  7     8/20/97 11:20a Nrobinso
//  fixup DeployVehicle; cleanup default key commands; new call to input
//  processing function
//  
//  6     8/07/97 11:27p Nrobinso
//  damage cleanup
//  
//  5     8/06/97 9:48a Nrobinso
//  VehicleFire now VehicleFireWeapon
//  
//  4     7/29/97 11:01a Nrobinso
//  moved weapon into common
//  
//  3     7/27/97 9:37p Nrobinso
//  
//  2     7/11/97 8:08p Bwilcox
//  
//  1     7/03/97 5:19p Nrobinso
//  
//  16    6/30/97 9:02p Bwilcox
//  moving protos out of army.h into vehicle.h, trooper.h, unit.h 
//  removing dead code and variables.
//  
//  15    5/20/97 3:28p Nrobinso
//  Change VehiclePosition() to take a vehicle pointer and return an EPOINT
//  
//  14    5/13/97 12:45a Dmaynard
//  RemoteVehicle  Missiles Firing and tracking
//  
//  13    4/29/97 2:06p Nrobinso
//  remove vehicle stats struct
//  
//  12    3/22/97 3:29p Bwilcox
//  split tad from ai debug control over v scroll
//  
//  11    2/20/97 1:36p Aburgess
//  Conversion from POINT to SPOINT
//  
//  10    1/31/97 3:06p Aburgess
//  new VehiclePosition() prototype
//  
//  9     1/16/97 3:53p Nrobinso
//  Added free-scrolling mode; turns off vehicle
//  
//  8     10/07/96 1:13p Nrobinso
//  Add vehicle stat
//  
//  7     9/17/96 5:18p Nrobinso
//  changed function names to conform to standard
//  
//  6     8/14/96 10:34p Nrobins
//  add tank sfx
//  
//  5     8/14/96 12:23a Nrobins
//  new vehicle animation data
//  
//  4     7/26/96 9:27p Nrobins
//  Changed nomeclature of Init/Load/Free calls; Fixed scrolling
// 
// 3     6/25/96 9:54p Nrobins
// added history info
// 
//  2     6/25/96 9:22p Nrobins
//  added history info
//
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __VEHICLE_H__
#define __VEHICLE_H__

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#ifndef __ANIM_H__
	#include "anim.h"
#endif

#ifndef __ARMY_H__
	#include "army.h"
#endif

/////////////////////////////////////////////////////////////////////////////
//					Structures
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
extern BOOL vehicle_control;

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////
typedef	enum	Action {
	VFIRE = 0,
	ACCELERATE,
	DECELERATE,
	STOP,
	TURN_LEFT,
	TURN_RIGHT,
	GUN_LEFT,
	GUN_RIGHT,
	SLOW,
	ALT,

	SVFIRE = 16,
	SACCELERATE,
	SDECELERATE,
	SSTOP,
	STURN_LEFT,
	STURN_RIGHT,
	SGUN_LEFT,
	SGUN_RIGHT,
	SSLOW,

} Action;

typedef	enum {
	BODYANIM,
	TURRETANIM,
	} VSPRITE;

#define DO_FIRE        (1 << VFIRE)
#define DO_ACCELERATE  (1 << ACCELERATE)
#define DO_DECELERATE  (1 << DECELERATE)
#define DO_STOP        (1 << STOP)
#define DO_TURN_LEFT   (1 << TURN_LEFT)
#define DO_TURN_RIGHT  (1 << TURN_RIGHT)
#define DO_GUN_LEFT    (1 << GUN_LEFT)
#define DO_GUN_RIGHT   (1 << GUN_RIGHT)
#define DO_SLOW		   (1 << SLOW)
#define DO_ALT		   (1 << ALT)

#define START_FIRE        (1 << SVFIRE)
#define START_ACCELERATE  (1 << SACCELERATE)
#define START_DECELERATE  (1 << SDECELERATE)
#define START_STOP        (1 << SSTOP)
#define START_TURN_LEFT   (1 << STURN_LEFT)
#define START_TURN_RIGHT  (1 << STURN_RIGHT)
#define START_GUN_LEFT    (1 << SGUN_LEFT)
#define START_GUN_RIGHT   (1 << SGUN_RIGHT)
#define START_SLOW		  (1 << SSLOW)


#define NO_DO_ACTION 0x00000000


#define VEHICLE_DEPLOY_HEADING 33

#define VEHICLE_ON_MAP(x) ((x)->state == VEHICLE_DEPLOYED || (x)->state == VEHICLE_DYING)


BOOL VehicleLoad(void);
void VehicleFree(void);

void LockTurret(void);

BOOL VehicleInit();
void VehicleExit(void);
void VehicleFireWeapon(VEHICLE *pVehicle);	

#define FOR_EACH_VEHICLE_TYPE_ALL(x) for(x=ARMY_NO_VEHICLE+1;x<ARMY_LAST_VEHICLE;++x)
#define FOR_EACH_VEHICLE_TYPE(x) for(x=ARMY_NO_VEHICLE+1;x<ARMY_COMMANDER;++x)

void		GetVehicleInput(VEHICLE *pVehicle);

RETERROR	VehicleCreate(ARMY_TYPE eArmy, VEHICLE_TYPE eVehicleType );
void		VehicleUpdate( VEHICLE* pVehicle );
void		VehicleDelete( VEHICLE* pVehicle );
void		VehicleDeploy( VEHICLE* pVehicle, SPOINT *pPos, short facing );
void		VehicleInitialDeploy( VEHICLE* pVehicle, SPOINT *pPos, short facing );
void		VehicleDeployPosition( VEHICLE* pVehicle, SPOINT *pPos, short facing);
void		VehicleUndeploy(VEHICLE* pVehicle);
void		VehicleMoveTo( VEHICLE* pVehicle, BOOL net );
void		VehicleSetDirection( VEHICLE* pVehicle, int direction, BOOL net );
void		VehicleFiringPosition(VEHICLE *pVehicle, SPOINT *pt);

int			VehicleMaxAmmo( VEHICLE* pVehicle );
int			VehicleGetDamage( VEHICLE* pVehicle );
int			VehicleGetFuel( VEHICLE* pVehicle );
int			VehicleFuelMax( VEHICLE* pVehicle );
BOOL		VehicleHitByMissile(VEHICLE* pVehicle, SHORT height);

BOOL		VehicleTurnTurret(VEHICLE* pVehicle, int turn_command, int vehicle_facing);
void		VehicleTurn(VEHICLE* pVehicle, int turn_command);
void		VehicleAccel(VEHICLE* pVehicle, int command);
LONG		VehicleDamage( VEHICLE *pTrooperPtr, int nDamageToDo, int nDamageType, SPOINT* pPointOfDamage,UID fromUID );
void		VehicleDie(VEHICLE *pVehicle);
void		VehicleTeleport( VEHICLE* pVehicle, SHORT x, SHORT y );

VEHICLE*	VehicleFind( LONG nUniqueID );
VEHICLE* 	VehicleNextInHQ(ARMY_TYPE eArmy,VEHICLE_TYPE eVehicleType);

int LegalVehiclePos(SPOINT *pos, int facing, int whichvehicle);
int TroopersOnVehiclePos(SPOINT *pos, int facing, int whichvehicle);
int LegalVehicleDeployPos(SPOINT *pos, int facing, int whichvehicle);

void VehicleSargeFlip();
int	VehiclesInHQ( ARMY_TYPE eArmy, VEHICLE_TYPE eUnitType, UID* pUIDs );

VEHICLE *getVehicleOnTile(int x, int y); //x,y are tile coordinates
int ClearVehicleFromVehicleLayer(VEHICLE *pVehicle);
void ReinsertVehicleInVehicleLayer(VEHICLE* pVehicle,BOOL did);
void AddVehicleToVehicleLayer(VEHICLE* pVehicle);
void SubtractVehicleFromVehicleLayer(VEHICLE* pVehicle);

void VehicleSoundOff();
void VehicleSoundOn();

#endif
