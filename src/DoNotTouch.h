//========================================================================
//	FILE:			$Workfile: DoNotTouch.h $
//
//	DESCRIPTION:	The essential released message formats.
//
//	AUTHOR:			David S. Maynard
//
//	CREATED:		Tuesday, July 30, 1997
//
//	REVISION:		$Header: /ArmyMen/src/DoNotTouch.h 3     4/06/98 5:36p Dmaynard $
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
//  $Log: /ArmyMen/src/DoNotTouch.h $
//  
//  3     4/06/98 5:36p Dmaynard
//  Removed unused struct definition: TROOPER_MESSAGE
//  
//  1     3/27/98 10:06a Bwilcox
//  
//  30    3/26/98 8:55a Bwilco
//  
//  $Nokeywords:$
///========================================================================

// THIS FILE IS THE RELEASED FORMATS FOR THE ARMYMEN TRANSMISSION.
// IF YOU CHANGE THIS YOU BREAK COMMUNICATION WITH ALL RELEASED PRODUCT.
// BAD IDEA!!!


#ifndef __DONOTTOUCH_H__
#define __DONOTTOUCH_H__

typedef enum
{
	// Generic and General purpose Message Types
	UPDATE_MESSAGE,
	DAMAGE_MESSAGE,
	FIRE_MESSAGE,
	DEATH_MESSAGE,
    GAME_LOST_MESSAGE,
    GAME_WON_MESSAGE,

	// Object message types
	OBJMSG_DAMAGE,
    OBJECT_REMOVE,

	// Float message types
	FLOATMSG_MISSILE,
	FLOATMSG_GRENADE,
 	FLOATMSG_EXPLOSION,

	// Unit message types
    UNIT_DEATH_MESSAGE,
	UNIT_DEPLOY_MESSAGE,
	UNIT_CHANGING_VEHICLE_MESSAGE,

	// Trooper message types
	TROOPER_UPDATE_MESSAGE,
	TROOPER_DEATH_MESSAGE,
	TROOPER_GONE_MESSAGE,

	// Vehicle message types
	DEPLOY_MESSAGE,
	UNDEPLOY_MESSAGE,
	DIED_MESSAGE,

	// SARGE and Unit message types
	SARGE_DEATH_MESSAGE,
	SARGE_GONE_MESSAGE,
	SARGETYPE_MESSAGE,
	SARGE_CHANGING_VEHICLE_MESSAGE,
    ITEM_MESSAGE,
    WANT_ITEM_MESSAGE,
	AIR_SUPPORT_MESSAGE,


	// event message type
	EVENT_MESSAGE_TYPE,

    OBJECT_PLACE,

	NUM_MSG_TYPES
} MSG_TYPE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
} ARMY_MESSAGE;

typedef struct
{
	int				num;			
	int				bytes;
	int				min;	
    int             max;
} MSGSTAT;

///========================================================================
//					SARGEMSG Structures
///========================================================================
typedef enum{
    WANT_PICKUP,
    WANT_DROP,
    DO_PICKUP,
    DO_DROP
} REQUEST;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	SPOINT			position;		
	unsigned char	fireDistance;
	unsigned char	fireDirection;
    unsigned char	fireIndex;
	unsigned char	pendingDirection;
    unsigned char	pendingAction;
    unsigned char	weaponIndex;
    unsigned short	strength;
} SARGE_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	LONG			int_data;		// 32 bits of data
} SARGE_SHORT_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	LONG			int_data;		// 32 bits of data
    SPOINT			position;
    ACTION			howDie;
} SARGE_DIE_MESSAGE;


typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	LONG			uid;			// UID for item
    SPOINT			position;		// position for item
    REQUEST			pickup;
    int				ammo;			// how many shots
    int				slot;
} SARGE_ITEM_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the vehicle
//--------------------------------------------------------std header above
	LONG			nVehicleIDFrag;	// which vehicle entered
    BOOL			bEnter;			// enter true, exit false
	SPOINT			position;		// position within the world
	unsigned char	facing;			// directional facing of object
} SARGE_VEHICLE_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above

    UID				fromUID;
	SHORT			x;
	SHORT			y;
	SHORT			damagetodo;
	unsigned char	damagetype;
} SARGE_DAMAGE_MESSAGE;


typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	char			airsupportType;
	SPOINT			where;
} SARGE_AIRSUPPORT_MESSAGE;

///========================================================================
//					OBJECTMSG Structures
///========================================================================

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	SPOINT			damagelocation;
	SHORT			damagetodo;
	unsigned char	damagetype;
	UID				fromUID;
} OBJECT_MESSAGE;

///========================================================================
//					UNITMSG Structures
///========================================================================


typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
} TROOPER_SHORT_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
    UID				fromUID;
	SHORT			x;
	SHORT			y;
	SHORT			damagetodo;
	unsigned char	damagetype;
} TROOPER_DAMAGE_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	SPOINT			position;
    SHORT			facing;
} UNITDEPLOY_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the vehicle
//--------------------------------------------------------std header above
	LONG			nVehicleIDFrag;	// which vehicle entered
    BOOL			bEnter;			// enter true, exit false
	SPOINT			position;		// position within the world
	unsigned char	facing;			// directional facing of object
} UNIT_VEHICLE_MESSAGE;

///========================================================================
//					VEHICLEMSG Structures
///========================================================================
typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
    // these could become bytes if we want (see BWilcox)
	SPOINT			position;		// position within the world
	SHORT			nStrength;		// vehicle strength

	SHORT			full_velocity;
	SHORT			velocity;		// anim velocity (after terrain effects)

	unsigned char	facing;			// directional facing of object
	unsigned char	gun_facing;	// directional facing of gun turret
} VEHICLE_MESSAGE;


typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	ULONG			nUniqueIDsecondary;//addiitonal ID needed for some commands
} VEHICLE_SHORT_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	UID				fromUID;
	SHORT			x;
	SHORT			y;
	SHORT			damagetodo;
	unsigned char	damagetype;
} VEHICLE_DAMAGE_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
    SPOINT			position;
    int				facing;
} VEHICLEDEPLOY_MESSAGE;

///========================================================================
//					ASSETMSG Structures
///========================================================================
typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	ULONG			nUniqueIDsecondary;//addiitonal ID needed for some commands

	SPOINT			position;			// position within the world
	unsigned char	facing;				// directional facing of object
	unsigned char	eCommands;			// current orders
	unsigned char	eState;				// object state
	SHORT			nStrength;			// object strength

	unsigned char	damage;				//0=undamaged. the amount of damage to destroy varies for different
										//object categories
	unsigned char	damageindex;		//which damage sprite to show (0=undamaged)
} ASSET_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	ULONG			nUniqueIDsecondary;//addiitonal ID needed for some commands

	unsigned char	facing;				// directional facing of trooper
	unsigned char	damage;				//0=undamaged. the amount of damage to destroy varies for different
										//object categories
	unsigned char	damageindex;		//which damage sprite to show (0=undamaged)
} ASSET_SHORT_MESSAGE;

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	ULONG			nUniqueIDsecondary;//addiitonal ID needed for some commands
    UID				fromUID;
    
	SHORT			x;
	SHORT			y;
	SHORT			damagetodo;
	unsigned char	damagetype;
} ASSET_DAMAGE_MESSAGE;

///========================================================================
//					FLOATMSG Structures
///========================================================================

typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	ULONG			nUniqueIDsecondary;//addiitonal ID needed for some commands
	SHORT			x;
	SHORT			y;
	ULONG			audioID;
	unsigned char	exptype;
	unsigned char	delay;
} FLOAT_MESSAGE;

///========================================================================
//					EVENTStructures
///========================================================================



typedef struct
{
	USHORT			nSize;			// size of message
	USHORT			msg_type;
	LONG			nUniqueID;		// UID for the unit
//--------------------------------------------------------std header above
	char			type;
	int				num;
	long			uid;
	int				removeevent;


} EVENT_MESSAGE;



#endif