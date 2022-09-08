//========================================================================
//	FILE:			$Workfile: AiAccess.h $
//
//	DESCRIPTION:	AI (Artificial Intelligence) Commander Access defines,
//					structures, and prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, February 13, 1997
//
//	REVISION:		$Header: /ArmyMen/src/AiAccess.h 35    3/26/98 2:39p Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996, 1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/AiAccess.h $
//  
//  35    3/26/98 2:39p Bwilcox
//  vehicle in movement layer split into new layer
//  
//  34    3/06/98 11:56a Phu
//  convert to 29 bit unique id mask
//  
//  33    3/02/98 12:24p Nrobinso
//  have a no turn command for vehicles
//  
//  32    1/29/98 5:50p Bwilcox
//  unit names system changed
//  
//  31    1/17/98 7:38a Bwilcox
//  added follow_radius, and follow_engaged radius and fixed a
//  defend-radius bug
//  
//  30    1/08/98 1:19p Bwilcox
//  parameters now in aidefaults.aai (runtime) include
//  DEFENSE_RADIUS, TROOPER_TURN_RATE, TROOPER_POSE_RATE, VEHICLE_DANGER,
//  VEHICLE_STANDOFF
//  
//  29    12/18/97 6:03p Bwilcox
//  converting epoint to spoint (not spoint*) notation
//  
//  28    12/15/97 4:15a Nrobinso
//  move ammo checking functions to weapon
//  
//  27    12/09/97 12:11p Phu
//  
//  26    11/20/97 10:43a Bwilcox
//  paratrooper suppoert
//  
//  25    10/30/97 10:16a Nrobinso
//  GROSS_MOTOR should be 8 not 6 to correspond to anims
//  
//  24    10/24/97 2:03p Awerner
//  First checkin of special vehicle firing code
//  
//  23    10/23/97 4:06p Bwilcox
//  removing dead code relating to units entering vehicles and installing
//  new code
//  
//  22    10/23/97 3:10p Awerner
//  Vehicle movement now feels better and stops when the key is released
//  
//  21    10/14/97 1:34p Nrobinso
//  removed excess headers
//  
//  20    10/14/97 11:58a Nrobinso
//  moved SargePointer and SargePosition to sarge.cpp/sarge.h
//  
//  18    9/24/97 1:12p Bwilcox
//  added AiItemFind
//  
//  17    9/12/97 7:35a Bwilcox
//  redefined return type of SargePointer to Sarge* and changed and added
//  uses of it
//  
//  16    8/25/97 5:01p Bwilcox
//  removal of legions pVehicle, rough support for multiple vehicles.
//  
//  15    8/25/97 3:26p Bwilcox
//  vehicledeploy/undeploy messages removed, code changes around vehicle
//  create.deploy and sarge in vehicle
//  
//  14    8/17/97 11:27a Bwilcox
//  names of TROOPxxx are now TROOPERxxx in a cleanup
//  
//  13    8/07/97 2:53p Nrobinso
//  put in ammo checks
//  
//	...
//  
//  1     2/17/97 8:27a Aburgess
//  AI Access prototypes, structures, and defines
//  
//  $Nokeywords:$
///========================================================================

#ifndef __AI_ACCESS_H__
#define __AI_ACCESS_H__
#include "army.h"

///========================================================================
//							GLOBAL DEFINES
///========================================================================

// Unique ID masks.  All masks are 1-based, so 0 means not present.
// Masks are 24 bit to leave top byte free (used by ai planner)
// Not really needed to be this way, because ai planner keeps a local
// id and doesnt use the UID as originally anticipated.

#define	AI_ID_29_BIT_MASK				0x1FFFFFFF

// Army mask is 3 bits [ARMY_TYPE]  (armies 0..3  e.g., ARMY_PLAYER)
#define	AI_ID_ARMY_MASK					(LONG)0x1C000000
// Object mask is 4 bits [OBJECT_TYPE] (1..15   e.g. ARMY_UNIT)
#define	AI_ID_OBJ_MASK					(LONG)0x03C00000
// SUB1_MASK is 6 bits	(1..63 local type of object)
#define	AI_ID_SUB1_MASK					(LONG)0x003F0000
// SUB2_MASK is 16 bits ( local id of object)
#define	AI_ID_SUB2_MASK					(LONG)0x0000FFFF

// Unique ID shift values
#define	AI_ID_ARMY_SHIFT				26
#define	AI_ID_OBJ_SHIFT					22
#define	AI_ID_SUB1_SHIFT				16
#define	AI_ID_SUB2_SHIFT				0

// Unique ID macros
#define	EXTRACT_ARMY(y) (((((long)y) & AI_ID_ARMY_MASK)>>AI_ID_ARMY_SHIFT)-1)
#define	OBJTYPE(y) (((((long)y) & AI_ID_OBJ_MASK) >> AI_ID_OBJ_SHIFT) -1)
#define	SUB1TYPE(y) (((((long)y) & AI_ID_SUB1_MASK) >> AI_ID_SUB1_SHIFT) -1)
#define	SUB2TYPE(y) ((((long)y) & AI_ID_SUB2_MASK) - 1)
#define ANY_INSTANCE_OF(y) (((long)y) & ~AI_ID_SUB2_MASK)
#define	ENCODE_ARMY(y) ((((long)(y)+1)<<AI_ID_ARMY_SHIFT) & AI_ID_ARMY_MASK)
#define ENCODE_OBJ(y)  ((((long)(y)+1)<< AI_ID_OBJ_SHIFT) & AI_ID_OBJ_MASK)
#define ENCODE_SUB1(y) ((((long)(y)+1)<< AI_ID_SUB1_SHIFT) & AI_ID_SUB1_MASK)
#define ENCODE_SUB2(y)  (((long)(y)+1) & AI_ID_SUB2_MASK)


#define GROSS_MOTOR 8
#define FINE_MOTOR 2   

// Unique ID masks
#define	AI_VEHICLE_CLEAR_MASK					(LONG)0x00000000
#define	AI_VEHICLE_GO_LEFT_MASK					(LONG)0x00000001
#define	AI_VEHICLE_GO_RIGHT_MASK				(LONG)0x00000002
#define	AI_VEHICLE_GO_FORWARD_MASK				(LONG)0x00000004
#define	AI_VEHICLE_GO_BACK_MASK					(LONG)0x00000008
#define	AI_VEHICLE_FINE_CONTROL_MASK			(LONG)0x00000400

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================

// vehicle commands
typedef enum {
	STRAIGHT_VEHICLE = 0,
	LEFT_VEHICLE = 1,
	RIGHT_VEHICLE,
	SPEEDUP_VEHICLE,
	SLOWDOWN_VEHICLE,
	FINE_LEFT_VEHICLE,
	FINE_RIGHT_VEHICLE,
	VERYFINE_LEFT_VEHICLE,
	VERYFINE_RIGHT_VEHICLE,
	STOP_VEHICLE = 0x51, // Nicki said to change to match anim command

	NUM_VEHICLE_COMMANDS
} VEHICLE_COMMAND_NUMBER;

///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================

// object info requests by unique id
SPOINT*	AiPosition( UID nUniqueID, BOOL bOldPos );
SPOINT*	AiTargetPosition( UID nAttackerUniqueID, BOOL bOldPos );
LONG	AiClosing( UID nFriendUID, UID nFoeUID, BOOL bStationary );
BOOL	AiInRange( UID nFriendUID, UID nFoeUID );

// object info requests by object pointer
long	AiObjectFiringRange( ITEM* pObj );
ITEM*	AiMyTargetObject( ITEM* pObj );

// Army specific info requests
int		AiArmyLegion( UID nUniqueID );
int		AiArmyForces( UID nUniqueID );
    
// vehicle specific info requests
LONG	AiVehicleMoveStatus(VEHICLE* pVehicle, SPOINT pTargetPoint );
LONG	AiVehicleFireStatus(VEHICLE* pVehicle, SPOINT pTargetPoint );
int		AiVehicleAdjustedSpeed(VEHICLE*	pVehicle);
int		AiVehicleRawSpeed(VEHICLE*	pVehicle);
int		AiVehicleMaxSpeed(VEHICLE*	pVehicle);

// vehicle commands
void	AiVehicleDoTurn(VEHICLE* pVehicle, int eTurnCommand );
void	AiVehicleDoAccelerate(VEHICLE* pVehicle, int eAccelCommand );
BOOL	AiVehicleDoTurnGun(VEHICLE* pVehicle, int eTurnCommand );

// Unit specific info requests
int		AiUnitGetOrders( UID nUniqueID );
char*	AiUnitShortName( UNIT* pUnit );


ITEM* AiItemFind( UID nUniqueID);

WEAPON_TYPE	AiTrooperWeapon( TROOPER_TYPE eTrooper );

///========================================================================

#endif		// __AI_ACCESS_H__

///========================================================================
//								EOF
///========================================================================
