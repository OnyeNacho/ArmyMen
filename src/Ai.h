//========================================================================
//	FILE:			$Workfile: Ai.h $
//
//	DESCRIPTION:	AI (Artificial Intelligence) defines, structures, and prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Friday, October 11, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Ai.h 77    4/02/98 2:24p Phu $
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
//  $Log: /ArmyMen/src/Ai.h $
//  
//  77    4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  76    3/27/98 1:38p Nrobinso
//  rename aigetmissionkey
//  
//  75    3/25/98 6:26p Nrobinso
//  have multiple mission voice overs
//  
//  74    3/25/98 3:47p Nrobinso
//  remove unused
//  
//  73    3/23/98 4:07p Aburgess
//  added Mission KEY fields
//  
//  72    3/23/98 1:57p Nrobinso
//  fix problem in inisitalizing of ai data tables
//  
//  71    3/23/98 12:27p Nrobinso
//  switch to loading the aai data every map load
//  
//  70    3/16/98 12:30a Nrobinso
//  keep failures as part of mission data
//  
//  69    3/12/98 2:10p Aburgess
//  modifications to put music in multiplayer games using terrain type
//  
//  68    3/11/98 7:23p Phu
//  crush damage when set to last damage sprite
//  
//  67    3/03/98 7:26a Aburgess
//  array definition bug in AVI movie access
//  
//  66    2/25/98 9:23p Nrobinso
//  recognize special unit troopers
//  
//  65    2/04/98 3:16p Phu
//  armor for objects
//  
//  64    2/02/98 1:00p Aburgess
//  modifications made to support new mission briefing references through
//  campaign.cpn
//  
//  63    2/01/98 4:31p Aburgess
//  modifications made to support new ART and maps files
//  
//  62    1/29/98 5:50p Bwilcox
//  unit names system removed from aidefaults and code
//  
//  61    1/27/98 12:21p Aburgess
//  increased MAX OBJECTS table size
//  
//  60    1/27/98 11:25a Phu
//  buff up the ai objects table size
//  
//  59    1/25/98 4:55a Bwilcox
//  paracount added for aai files
//  
//  58    1/23/98 11:12a Nrobinso
//  change fence gate to gate
//  
//  57    1/17/98 7:38a Bwilcox
//  added follow_radius, and follow_engaged radius and fixed a
//  defend-radius bug
//  
//  56    1/15/98 8:18p Phu
//  modify max size of aai items
//  
//  55    1/15/98 5:05p Phu
//  new aai
//  
//  54    1/12/98 4:48p Phu
//  acquire armor value
//  
//  53    1/08/98 2:11p Bwilcox
//  attack paramaters and trooper slide parameters added to defaults file
//  
//  52    1/08/98 1:18p Bwilcox
//  parameters now in aidefaults.aai (runtime) include
//  DEFENSE_RADIUS, TROOPER_TURN_RATE, TROOPER_POSE_RATE, VEHICLE_DANGER,
//  VEHICLE_STANDOFF
//  
//  51    12/24/97 5:19p Bwilcox
//  removed epoint datatype
//  
//  50    12/24/97 4:52p Bwilcox
//  removed DecodePoint
//  
//  49    12/22/97 4:42p Phu
//  medkits & medpacks
//  
//  48    12/15/97 1:00a Aburgess
//  new debug prototype AiDumpVisibility()
//  
//  47    12/11/97 10:16a Aburgess
//  made AiDumpCPN more accessible
//  
//  46    12/09/97 12:11p Phu
//  
//  45    12/05/97 4:08p Phu
//  
//  44    12/05/97 2:50p Phu
//  visibility layer
//  
//  43    12/04/97 9:17a Aburgess
//  Modification made to support mission statement Music ID. Text is mapped
//  in VOICES.OPT file.
//  
//  42    12/02/97 3:24p Phu
//  Create an overlay layer, put explosions in that layer
//  
//  41    11/26/97 12:01p Awerner
//  multi part objects can now be on any of the 3 layers
//  
//  40    11/24/97 2:49p Aburgess
//  modifications made for expanded CAMPAIGN reader codes
//  
//  39    11/20/97 11:41a Aburgess
//  FreeCampaign replaced with AiCampaignFree
//  
//  38    11/19/97 5:47p Nrobinso
//  increase number of units
//  
//  37    11/18/97 11:35a Awerner
//  added capability for subobjects to be on specified layers
//  
//  36    11/16/97 7:12p Aburgess
//  added category ID to ObjTable
//  
//  35    11/16/97 5:32p Nrobinso
//  army_explosive becomes army_explosive_weapon; the MINE object category
//  became the EXPLOSIVES category
//  
//  34    11/16/97 2:22p Aburgess
//  free campaign reference prototype
//  
//  33    11/13/97 8:10a Aburgess
//  added height and movement fields
//  
//  32    11/11/97 4:53p Phu
//  
//  31    11/11/97 8:53a Nrobinso
//  chaged commander to sarge
//  
//  30    11/10/97 5:21p Awerner
//  Kludgy fix to AI loading code to load in part numbers
//  
//  29    11/07/97 10:38a Aburgess
//  ID to index converstion prototypes
//  
//  28    11/05/97 1:32p Nrobinso
//  add vehicle collision damage
//  
//  27    11/04/97 3:20p Nrobinso
//  increase max units
//  
//  26    11/03/97 9:45a Aburgess
//  added reference to mission ID global
//  
//  25    10/30/97 10:39a Phu
//  add mine sweeper weapon
//  
//  24    10/30/97 10:15a Nrobinso
//  sarge guns become rifle and auto rifle
//  
//  23    10/27/97 10:50a Aburgess
//  changes made to remove directory overrides
//  
//  22    10/22/97 10:56a Bwilcox
//  nsize removed from common,
//  boat changed to convoy throughout (including aai files)
//  
//  21    10/22/97 10:42a Bwilcox
//  boat renamed to convoy
//  
//  20    10/20/97 2:31p Bwilcox
//  adjusted Makeweapon to use aidefaults.aai stuff
//  simplified aiinput code and expanded it to handle more sitems
//  
//  19    10/08/97 3:44p Nrobinso
//  ARMY_SARGE_GUN -> ARMY_RIFLE
//  
//  17    9/29/97 3:41p Aburgess
//  lastest changes for DIALOG representations of FullScreen UI screens
//  
//  16    9/23/97 3:00p Aburgess
//  latest modifications for Dialog base version
//  
//  15    9/14/97 12:19p Bwilcox
//  influence stuff moved to deadcode.cpp (not in project)
//  
//  14    8/18/97 2:55p Nrobinso
//  get object hp info
//  
//  13    8/13/97 6:52p Nrobinso
//  add weapon projectile speeds to aidefault file
//  
//  12    8/12/97 3:47p Nrobinso
//  added sarge gun
//  
//  11    8/05/97 3:27p Nrobinso
//  rename item bFlags bItemFlags
//  
//  10    8/03/97 8:56p Bwilcox
//  added VIS_RANGE to global defaults
//  
//  9     7/30/97 5:08p Aburgess
//  added AI_NO_NAME
//  
//  8     7/27/97 9:41a Nrobinso
//  call mortar instead of artillery; remove helicopters
//  
//  7     7/23/97 3:31p Bwilcox
//  removed throw ranges. Now is only MIN and MAX range for a weapon.
//  
//  6     7/21/97 10:20p Aburgess
//  new unit Long,Short, and Target names.
//  
//  5     7/15/97 7:51p Nrobinso
//  added rifle unit
//  
//  4     7/14/97 7:04p Nrobinso
//  moved UnitTypeName() to army.h
//  
//  3     7/05/97 10:14p Bwilcox
//  removed air refereneces
//  
//  2     7/03/97 7:53p Bwilcox
//  massive cleanups.
//
//  $Nokeywords:$
///========================================================================

#ifndef __AI_H__
#define __AI_H__

///========================================================================
//							EXTERNAL REFERENCES
///========================================================================
void AINewObject( long nUniqueID ); // Notify AI Commander of new Unique IDs

///========================================================================
//							GLOBAL DEFINES
///========================================================================
#define AAI_PATH "./"

#define	AI_MAX_TBL_SIZE					32
#define	AI_MAX_BASES					32
#define	AI_MAX_OBJS_SIZE				1024
#define	AI_MAX_CATEGORY_SIZE			100
#define	AI_MAX_MESSAGE_LEN				256

#define	AI_NO_NAME						-1
#define	AI_MAX_UNIT_NAMES				3

#define	AI_MAX_NAME						32
#define	AI_MAX_NAME_LONG				64
#define	AI_MAX_NAME_SHORT				32
#define	AI_MAX_NAME_TARGET				16
#define	AI_MAX_STRING					64

#define	AI_MAX_COMP_ENTRIES				8

#define	AI_SPECIAL_TROOPER				'S'
#define	AI_RIFLE_TROOPER				'R'
#define	AI_special_TROOPER				's'
#define	AI_rifle_TROOPER				'r'

// Information STATE IDS
#define	AI_NO_CONTEXT					-1
#define	AI_UNIT_CONTEXT					0
#define	AI_VEHICLE_CONTEXT				1
#define	AI_WEAPON_CONTEXT				2
#define	AI_TROOP_CONTEXT				3
#define	AI_ASSET_CONTEXT				4
#define	AI_TERRAIN_CONTEXT				5
#define	AI_OBJS_CONTEXT					6
#define	AI_CAMPAIGN_CONTEXT				7
#define	AI_SCENARIO_CONTEXT				8
#define	AI_MISSION_CONTEXT				9

#define	AI_NULL							~0L

// Generic TOKEN IDs
#define	AI_COMMENT						100
#define	AI_LAT							101
#define	AI_MLA							102
#define	AI_VISRANGE						103

#define	AI_VEHICLEDANGER				104
#define	AI_VEHICLESTANDOFF				105
#define	AI_TROOPERTURNRATE				106
#define	AI_TROOPERPOSERATE				107
#define	AI_DEFENSERADIUS				108
#define	AI_TROOPERSLIDERATE				109
#define	AI_ATTACKHUNT					110
#define	AI_ATTACKRADIUS					111
#define AI_FOLLOWRADIUS					112
#define AI_FOLLOWENGAGEDRADIUS			113

#define AI_PARACOUNT					114



// Unit Parameters and Information
#define	UNIT_ID_BASE			200
#define	AI_RIFLE_UNIT			UNIT_ID_BASE+ARMY_RIFLE_UNIT
#define	AI_GRENADE_UNIT			UNIT_ID_BASE+ARMY_GRENADE_UNIT
#define	AI_FLAME_UNIT			UNIT_ID_BASE+ARMY_FLAME_UNIT
#define	AI_BAZOOKA_UNIT			UNIT_ID_BASE+ARMY_BAZOOKA_UNIT
#define	AI_ENGINEER_UNIT		UNIT_ID_BASE+ARMY_ENGINEER_UNIT
#define	AI_MORTAR_UNIT			UNIT_ID_BASE+ARMY_MORTAR_UNIT
#define	AI_MINER_UNIT			UNIT_ID_BASE+ARMY_MINER_UNIT
#define	AI_SPECIAL_UNIT			UNIT_ID_BASE+ARMY_SPECIAL_UNIT

#define	AI_FIRST_UNIT			AI_RIFLE_UNIT
#define AI_LAST_UNIT			AI_SPECIAL_UNIT

// TROOPER Parameters and Information
#define	TROOP_ID_BASE			300
#define	AI_RIFLE_MEN			TROOP_ID_BASE+ARMY_RIFLE_MEN
#define	AI_GRENADE_MEN			TROOP_ID_BASE+ARMY_GRENADE_MEN
#define	AI_FLAME_MEN			TROOP_ID_BASE+ARMY_FLAME_MEN
#define	AI_BAZOOKA_MEN			TROOP_ID_BASE+ARMY_BAZOOKA_MEN
#define	AI_ENGINEER_MEN			TROOP_ID_BASE+ARMY_ENGINEER_MEN
#define	AI_MORTAR_MEN			TROOP_ID_BASE+ARMY_MORTAR_MEN
#define	AI_MINER_MEN			TROOP_ID_BASE+ARMY_MINER_MEN
#define	AI_SPECIAL_MEN			TROOP_ID_BASE+ARMY_SPECIAL_MEN

#define AI_FIRST_MEN			AI_RIFLE_MEN
#define AI_LAST_MEN				AI_SPECIAL_MEN

// Vehicle Parameters and Information
#define	VEHICLE_ID_BASE			400
#define	AI_FIRST_VEHICLE		VEHICLE_ID_BASE+ARMY_JEEP
#define	AI_JEEP					VEHICLE_ID_BASE+ARMY_JEEP
#define	AI_TANK					VEHICLE_ID_BASE+ARMY_TANK
#define	AI_HALFTRACK			VEHICLE_ID_BASE+ARMY_HALFTRACK
#define	AI_CONVOY				VEHICLE_ID_BASE+ARMY_CONVOY
#define	AI_SARGE				VEHICLE_ID_BASE+ARMY_COMMANDER
#define	AI_LAST_VEHICLE			VEHICLE_ID_BASE+ARMY_COMMANDER

// Weapon Parameters and Information
#define	WEAPONS_ID_BASE			500

#define	AI_FIRST_WEAPON			WEAPONS_ID_BASE+ARMY_LIGHT_MACHINE_GUN
#define	AI_LIGHT_MACHINE_GUN	WEAPONS_ID_BASE+ARMY_LIGHT_MACHINE_GUN

#define	AI_GRENADE				WEAPONS_ID_BASE+ARMY_GRENADE
#define	AI_FLAME_THROWER		WEAPONS_ID_BASE+ARMY_FLAME_THROWER
#define	AI_BAZOOKA				WEAPONS_ID_BASE+ARMY_BAZOOKA
#define	AI_MORTAR				WEAPONS_ID_BASE+ARMY_MORTAR

#define	AI_LARGE_CANNON			WEAPONS_ID_BASE+ARMY_LARGE_CANNON
#define	AI_MEDIUM_MACHINE_GUN	WEAPONS_ID_BASE+ARMY_MEDIUM_MACHINE_GUN
#define	AI_HEAVY_MACHINE_GUN	WEAPONS_ID_BASE+ARMY_HEAVY_MACHINE_GUN

#define	AI_RIFLE				WEAPONS_ID_BASE+ARMY_RIFLE
#define	AI_AUTO_RIFLE			WEAPONS_ID_BASE+ARMY_AUTORIFLE

#define AI_ARMY_MINE			WEAPONS_ID_BASE+ARMY_MINE
#define AI_ARMY_EXPLOSIVE		WEAPONS_ID_BASE+ARMY_EXPLOSIVE_WEAPON

#define AI_ARMY_SWEEPER			WEAPONS_ID_BASE+ARMY_SWEEPER

#define AI_ARMY_GUARD_TOWER_RIFLE	WEAPONS_ID_BASE+ARMY_GUARD_TOWER_RIFLE
#define AI_ARMY_MEDKIT			WEAPONS_ID_BASE + ARMY_MEDKIT
#define AI_ARMY_MEDPACK			WEAPONS_ID_BASE + ARMY_MEDPACK

// these are not provided in aai defaults, because they are not weapons
#define AI_ARMY_DETONATOR		WEAPONS_ID_BASE+ARMY_DETONATOR
#define AI_ARMY_LURE			WEAPONS_ID_BASE+ARMY_LURE

// these are not provided in aai defaults, because they are not weapons
#define AI_ARMY_FLAG			WEAPONS_ID_BASE+ARMY_FLAG
#define AI_ARMY_GREENFLAG		WEAPONS_ID_BASE+ARMY_GREENFLAG
#define AI_ARMY_TANFLAG			WEAPONS_ID_BASE+ARMY_TANFLAG
#define AI_ARMY_BLUEFLAG		WEAPONS_ID_BASE+ARMY_BLUEFLAG
#define AI_ARMY_GRAYFLAG		WEAPONS_ID_BASE+ARMY_GRAYFLAG

#define	AI_LAST_WEAPON			WEAPONS_ID_BASE+AI_ARMY_GRAYFLAG

// Weapon Parameters and Information
#define	PROJECTILE_ID_BASE		600
#define	AI_LINE_OF_SIGHT		PROJECTILE_ID_BASE+ARMY_LINE_OF_SIGHT
#define	AI_GROUND_MISSILE		PROJECTILE_ID_BASE+ARMY_GROUND_MISSILE
#define	AI_CONE					PROJECTILE_ID_BASE+ARMY_CONE
#define	AI_AREA					PROJECTILE_ID_BASE+ARMY_AREA

// Terrain Parameters and Information
#define	TERRAIN_ID_BASE			700
#define	AI_T_0					TERRAIN_ID_BASE+0
#define	AI_T_1					TERRAIN_ID_BASE+1
#define	AI_T_2					TERRAIN_ID_BASE+2
#define	AI_T_3					TERRAIN_ID_BASE+3
#define	AI_T_4					TERRAIN_ID_BASE+4
#define	AI_T_5					TERRAIN_ID_BASE+5
#define	AI_T_6					TERRAIN_ID_BASE+6
#define	AI_T_7					TERRAIN_ID_BASE+7
#define	AI_T_8					TERRAIN_ID_BASE+8
#define	AI_T_9					TERRAIN_ID_BASE+9
#define	AI_T_10					TERRAIN_ID_BASE+10
#define	AI_T_11					TERRAIN_ID_BASE+11
#define	AI_T_12					TERRAIN_ID_BASE+12
#define	AI_T_13					TERRAIN_ID_BASE+13
#define	AI_T_14					TERRAIN_ID_BASE+14
#define	AI_T_15					TERRAIN_ID_BASE+15

// Objects Objs Parameters and Information
#define	OBJS_ID_BASE			801
#define	AI_ROCK					OBJS_ID_BASE+ROCK
#define	AI_BUSH					OBJS_ID_BASE+BUSH
#define	AI_TREE					OBJS_ID_BASE+TREE
#define	AI_BIGTREE				OBJS_ID_BASE+BIG_TREE
#define	AI_FALLENTREE			OBJS_ID_BASE+FALLEN_TREE
#define	AI_FENCE				OBJS_ID_BASE+FENCE
#define	AI_WALL					OBJS_ID_BASE+WALL
#define	AI_BRIDGE				OBJS_ID_BASE+BRIDGE
#define	AI_FOOTBRIDGE			OBJS_ID_BASE+FOOT_BRIDGE
#define	AI_EXPLOSIVES			OBJS_ID_BASE+EXPLOSIVES
#define	AI_GUNTURRET			OBJS_ID_BASE+GUN_TURRET
#define	AI_AAGUN				OBJS_ID_BASE+AA_GUN
#define	AI_BASE					OBJS_ID_BASE+BASE
#define	AI_AUXBASE				OBJS_ID_BASE+AUX_BASE
#define	AI_AIRSTRIP				OBJS_ID_BASE+AIR_STRIP
#define	AI_HELIPAD				OBJS_ID_BASE+HELI_PAD
#define	AI_PRISONCAMP			OBJS_ID_BASE+PRISON_CAMP
#define	AI_BUILDING				OBJS_ID_BASE+BUILDING
#define	AI_PILLBOX				OBJS_ID_BASE+PILL_BOX
#define	AI_POWERPLANT			OBJS_ID_BASE+POWER_PLANT
#define	AI_GATE					OBJS_ID_BASE+GATE
#define	AI_WALLGATE				OBJS_ID_BASE+WALL_GATE
#define	AI_RADARBUILDING		OBJS_ID_BASE+RADAR_BUILDING
#define	AI_MISCELLANEOUS		OBJS_ID_BASE+MISCELLANEOUS
#define	AI_OVERPASS				OBJS_ID_BASE+OVERPASS
#define	AI_SITEMS				OBJS_ID_BASE+SPECIAL_ITEMS

// Secondary TOKEN IDs
#define	SECONDARY_BASE_ID				1000
#define	AI_TROOPERS						SECONDARY_BASE_ID+1
#define	AI_CAPACITY						SECONDARY_BASE_ID+2
#define	AI_TROOPS						SECONDARY_BASE_ID+3
#define	AI_WEAPONS						SECONDARY_BASE_ID+4
#define	AI_TROOP_STRENGTH				SECONDARY_BASE_ID+5
#define	AI_SPEEDS						SECONDARY_BASE_ID+6
#define	AI_AMMOS						SECONDARY_BASE_ID+7
#define	AI_FUELS						SECONDARY_BASE_ID+8
#define	AI_RATE_OF_FIRE					SECONDARY_BASE_ID+9
#define	AI_MINIMUM_RANGE				SECONDARY_BASE_ID+10
#define	AI_MAXIMUM_RANGE				SECONDARY_BASE_ID+11
#define	AI_PERCENTAGE_DECREASE_RATE		SECONDARY_BASE_ID+12
#define	AI_DAMAGES						SECONDARY_BASE_ID+13
#define	AI_DAMAGE_DECREASE_RATE			SECONDARY_BASE_ID+14
#define	AI_DRIFT						SECONDARY_BASE_ID+15
#define	AI_ACCEL						SECONDARY_BASE_ID+16
#define	AI_TARGET						SECONDARY_BASE_ID+17
#define	AI_VELOCITIES					SECONDARY_BASE_ID+18
#define	AI_ZVELOCITIES					SECONDARY_BASE_ID+19
#define	AI_COLLISION					SECONDARY_BASE_ID+20
#define AI_ARMOR						SECONDARY_BASE_ID+21

// Composition TOKEN IDS
#define COMPOSITION_BASE_ID				1100
#define	AI_UNIT_POWER					COMPOSITION_BASE_ID+1
#define	AI_UNIT							COMPOSITION_BASE_ID+2
#define	AI_INDEX						COMPOSITION_BASE_ID+3
#define	AI_NAME							COMPOSITION_BASE_ID+4
#define	AI_COMPOSITION					COMPOSITION_BASE_ID+5

// base TOKEN IDS
#define MAINBASE_BASE_ID				1200
#define	AI_BASE_DOOR					MAINBASE_BASE_ID+1

// Campaign Select TOKEN IDS
#define CAMPAIGN_ID						9000
#define	SCENARIO_ID						CAMPAIGN_ID+1
#define	MISSION_ID						CAMPAIGN_ID+2
#define	TITLE_ID						CAMPAIGN_ID+3
#define	MUSIC_ID						CAMPAIGN_ID+4
#define	VISIBILITY_ID					CAMPAIGN_ID+5
#define	MESSAGE_ID						CAMPAIGN_ID+6
#define	MAPFILE_ID						CAMPAIGN_ID+7
#define	STARTMAP_ID						CAMPAIGN_ID+8
#define	AVI_ID							CAMPAIGN_ID+9
#define	KEY_ID							CAMPAIGN_ID+10

// last TOKEN IDS
#define	MAX_BASE_ID						9999
#define	AI_EOL							MAX_BASE_ID

// Acceleration TOKEN IDs
#define	ACCEL_FORWARD					0
#define	ACCEL_REVERSE					1
#define	ACCEL_DECCEL					2

// Terrain types
#define	AI_TANK_TERRAIN					0
#define	AI_HALFTRACK_TERRAIN			1
#define	AI_JEEP_TERRAIN					2
#define	AI_HUMAN_TERRAIN				3


// Campaign data max
#define	AI_MAX_CAMPAIGNS				4
#define	AI_MAX_SCENARIOS				4
#define	AI_MAX_MISSIONS					4

// campaign filename max
#define	CPN_MAX_FILENAME				63

#define MULTIPARTOBJECT_MAXNUMPARTS		8


///========================================================================
//							GLOBAL MACROS
///========================================================================

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================

typedef long	UID;				// 24-bit object Unique ID


enum EObjectLayer {
	OL_GROUNDLAYER,
	OL_ORDEREDLAYER,
	OL_TOPLAYER,
	OL_OVERLAYLAYER
};

// campaign types
typedef enum
{
	CPN_CAMPAIGN_MAP = 0,			// one player campaigns
	CPN_LOAD_MAP,					// multiplayer/one player saved campaigns
	CPN_LAST_MAP,					// multiplayer/one player last played campaign
	CPN_NEW_MAP,					// multiplayer NEW campaigns
	CPN_USER_MAP					// multiplayer USER defined campaigns

} CAMPAIGN_TYPE;

// Object types
typedef enum
{
	AI_UNIT_OBJ = 0,
	AI_VEHICLE_OBJ,
	AI_ASSET_OBJ,
	AI_WEAPON_OBJ
} AI_OBJECT;

// Target Acquisition min and max
typedef struct
{
	USHORT		nMinAttackLevel;
	USHORT		nMaxAttackLevel;
} AI_ACQUIRE;

// weapons cache
typedef struct
{
	int		eWeapon1;			// Primary weapon of choice
	int		eWeapon2;			// Secondary weapon of choice if available
} AI_WEAPON;

// ammo cache
typedef struct
{
	short	nAmmo1;					// Ammo for primary weapon
	short	nAmmo2;					// Ammo for secondary weapon
} AI_AMMO;

// acceleration capabilities
typedef struct
{
	short	nForward;				// forward (driving) speed
	short	nReverse;				// reverse (driving) speed
	short	nDeccel;				// decceleration (driving) speed
} AI_ACCELS;

// speed capabilities
typedef struct
{
	short	nSpeed0;				// slow (shuffle) speed
	short	nSpeed1;				// normal (walking) speed
	short	nSpeed2;				// fast (running) speed
} AI_SPEED;

// fuel capabilities
typedef struct
{
	short	nTotalFuel;				// total fuel supply
	short	nBurnRate;				// fuel comsumption rate
} AI_FUEL;

// rate of fire capabilities
typedef struct
{
	short	nFrameDelay;			// frame delay between shots
	short	nFrameContinuous;		// frames of continuous effect
} AI_FIRE;

// Damage characteristics
typedef struct
{
	short	nDamage;				// damage at point of attack
	char	nDamageDecreaseRate;	// damage fall-off rate
} AI_DAMAGE;

// Range characteristics
typedef struct
{
	short	nMinRange;				// default maximum range of weapon
	short	nMaxRange;				// default maximum range of weapon
	char	nPercentDecreaseRate;	// weapon fall-off rate
	short	nDrift;					// random drift of projectile
} AI_RANGE;

// rate of fire capabilities
typedef struct
{
	short	nVelocity;				// projectile velocity in frames/second
	short	nZVelocity;				// z direction projectile velocity in frames/second
} AI_VELOCITY;

// makeup AI information
typedef struct
{
	int			ePrimary;			// primary troopers 
	int			eSecondary;			// secondary troopers
} AI_MAKEUP;

// Unit composition AI information
typedef struct
{
	char		pNameShort[AI_MAX_NAME_SHORT];		// Unit short Name 
	char		composition[AI_MAX_COMP_ENTRIES];	// default number of special troopers 
} AI_COMP;

// asset AI information
typedef struct
{
	AI_WEAPON	weapons;			// default weapon choices (choice of 2) 
	short		nHitPoints;			// default total hit points
	AI_ACQUIRE	targeting;			// default target acquisition levels	
} AI_ATBL;

// base AI information
typedef struct
{
	short		nXoffset;			// default x offset for base doorway 
	short		nYoffset;			// default y offset for base doorway 
	short		nFacing;			// default facing of base doorway
} AI_BTBL;

// terrain AI information
typedef struct
{
	short		nTank;				// default tank movement rate 
	short		nHalfTrack;			// default halftrack movement rate 
	short		nJeep;				// default jeep movement rate 
	short		nHuman;				// default human, including Commander, movement rate 
} AI_GTBL;




// pobject obj AI information
typedef struct
{
	short		nCategoryID;		// category number
	short		nObjectID;			// object number
	short		nDamageLevel;		// damage level
	short		nPartCount;			// number of parts used to create this object
	short		nLayer;				// layer this object goes in
	short		nHitPoints;			// hitpoints
	BYTE		nHeight;			// height or elevation
	signed char	nMovement;			// movement
	BYTE		nVisibility;		// visibility
	BYTE		nPermeability;		// chance to miss
	signed char nArmor;				// subtract armor from damage
	short		nCrushDamage;		// amount of damage this item does to movement layer		
} AI_ITBL;

// troop AI information
typedef struct
{
	int			weapon;				// default weapon choice 
} AI_TTBL;

// unit AI information
typedef struct
{
	AI_MAKEUP	makeup;				// default unit make up 
	short		nTroopStrength;		// default hit points per trooper
	short		nTroops;			// default maximum number of troops in a unit
	AI_SPEED	speed;				// default speeds (normal,run)
	AI_ACQUIRE	targeting;			// default target acquisition levels
	short		nPowerUnits;		// default average of units
	AI_COMP		comp;				// default unit compostion data
} AI_UTBL;

// Vehicle AI information
typedef struct
{
	AI_WEAPON	weapons;			// default weapon choices (choice of 2) 
	short		nHitPoints;			// default total hit points
	AI_ACCELS	accel;				// default acceleratios
	AI_SPEED	speed;				// default speeds (normal,run)
	char		capacity;			// default maximum unit capacity
	AI_AMMO		ammo;				// default ammo for weapons 
	AI_FUEL		fuel;				// default fuel for vehicle 
	AI_ACQUIRE	targeting;			// default target acquisition levels
	short		nCollisionDamage;	// default vehicle collision damage
	short		nArmor;
} AI_VTBL;

// Weapon AI information
typedef struct
{
	AI_FIRE		rateOfFire;			// default weapon rate of fire 
	int			eProjectile;		// default weapon projectile
	AI_RANGE	range;				// default weapon range effects
	AI_DAMAGE	damage;				// default weapon damage effects
	AI_VELOCITY velocity;			// default weapon velocities
} AI_WTBL;

// AI Tuning Information structure (default tuning parameters)
typedef struct
{
	short	nLookAheadTime;			// Look Ahead Time for calculating the Zone of Control
	short	nMovementLookAhead;		// Movement Look Ahead, the distance you look ahead during
									// local movement.
	AI_ATBL	assetTables[ AI_MAX_TBL_SIZE ];		// ASSET default AI information tables
	AI_BTBL	baseTables[ AI_MAX_BASES ];			// BASE default AI information tables
	AI_GTBL	terrainTables[ AI_MAX_TBL_SIZE ];	// TERRAIN default AI information tables
	AI_ITBL	objTables[ AI_MAX_CATEGORY_SIZE ];		// OBJECT default AI information tables
	AI_ITBL	objIndivTables[ AI_MAX_OBJS_SIZE ];	// OBJECT default AI information tables
	AI_TTBL	troopTables[ AI_MAX_TBL_SIZE ];		// TROOP default AI information tables
	AI_UTBL	unitTables[ AI_MAX_TBL_SIZE ];		// UNIT default AI information tables
	AI_VTBL	vehicleTables[ AI_MAX_TBL_SIZE ];	// VEHICLE default AI information tables
	AI_WTBL	weaponTables[ AI_MAX_TBL_SIZE ];	// WEAPONRY default AI information tables
} AI_INFO;

typedef struct
{
	char*	pCmdName;
	int		nCmdID;
	void	(*pActionFunc)(int type);
} AI_CMD_ENTRY;

#define MISSION_BRIEFING	0
#define MISSION_WIN			1
#define MISSION_LOSE		2
#define MISSION_DIE			3
#define MISSION_VOICES		4

//=========================================================================
//	campaign, scenario, and mission data structures for dialogs
//=========================================================================

typedef struct
{
	BOOL			bVisible;							// is this mission viewable yet
	unsigned char	nFailed;							// number of times failed
	USHORT			nMissionKey;						// KEY reference for mission data
	USHORT			nMissionID;							// ID reference for mission data
	ULONG			nMissionVoiceID[MISSION_VOICES];	// Mission Statement Voice Audio
	ULONG			nMissionMusicID[2];					// music to be played during mission (low/hi intensity)
	char			pMissionName[AI_MAX_NAME_LONG+1];	// mission text name
	char			pFileName[AI_MAX_NAME_SHORT+1];		// mission file name
	char			pBriefFile[AI_MAX_NAME_SHORT+1];	// mission briefing file name
	char			pStratFile[AI_MAX_NAME_SHORT+1];	// mission stratmap file name
} MISSIONREF;

typedef struct
{
	BOOL			bVisible;							// is this scenario viewable yet
	USHORT			nScenarioID;						// ID reference for scenario data
	char			pScenarioName[AI_MAX_STRING+1];		// scenario text name
	char			pScenarioWin[AI_MAX_NAME_SHORT+1];	// Scenario win avi
	char			pScenarioLose[3][AI_MAX_NAME_SHORT+1];// Scenario lose avis
	int				nNumberMissions;					// number of missions in scenarios
	MISSIONREF		pMissions[ AI_MAX_MISSIONS ];		// list of mission data
} SCENARIOREF;

typedef struct
{
	BOOL			bVisible;							// is this campaign viewable yet
	USHORT			nCampaignID;						// ID reference for campaign data
	ULONG			nCampaignMusicID;					// music to be played during mission select
	char			pCampaignName[AI_MAX_STRING+1];		// campaign text name
	char			pLoadBkg[AI_MAX_STRING+1];			// loading BKG filename
	char			pCampaignBkg[AI_MAX_STRING+1];		// Mission select BKG filename
	int				nNumberScenarios;					// number of scenarios in campaign
	SCENARIOREF		pScenarios[ AI_MAX_SCENARIOS ];		// list of scenario data
} CAMPAIGNREF;


///========================================================================
//							GLOBAL VARIABLES
///========================================================================
extern	AI_INFO			AIinfo;
extern	CAMPAIGNREF*	g_Campaigns[ AI_MAX_CAMPAIGNS ];
extern	int				g_NumberCampaigns;
extern	int				g_NumberScenarios;
extern	int				g_CampaignIndex;
extern	int				g_ScenarioIndex;
extern	int				g_MissionIndex;
extern	USHORT			g_MissionID;

///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================

BOOL			AiInit( void );
void			AiExit( void );
AI_UTBL*		AiUnitDefaults( int eUnitId );
AI_VTBL*		AiVehicleDefaults( int eVehicleId );
AI_WTBL*		AiWeaponDefaults( int eWeaponId );
AI_ACQUIRE*		AiAssetTargetDefaults( int eAssetId );
AI_ACQUIRE*		AiUnitTargetDefaults( int eUnitId );
AI_ACQUIRE*		AiVehicleTargetDefaults( int eVehicleId );

void			AiDefaultLoad( char* pInput );
BOOL			AiDataLoad( char* pInput );
void			AiCampaignLoad( char* pFileName );
void			AiInput( void );

UID		AiRequestUniqueID( int eArmy, int eObjType, int eSubType1, int eSubType2 );
void	AiDecodeUniqueID( UID nUniqueID, int* eArmy, int* eObjType, int* eSubType1, int* eSubType2 );

CAMPAIGNREF*	AiGetCampaignRef( int nCampaignID );
SCENARIOREF*	AiGetScenarioRef( CAMPAIGNREF* pCampaignRef, int nScenarioID );
MISSIONREF*		AiGetMissionRef( SCENARIOREF* pScenarioRef, int nMissionID );
USHORT			GetMissionKey( void );
int				AiMPCampaignIndex( void );
int				AiCampaignIndex( int nCampaignID );
int				AiScenarioIndex( CAMPAIGNREF* pCampaignRef, int nScenarioID );
int				AiMissionIndex( SCENARIOREF* pScenarioRef, int nMissionID );
void			AiCampaignFree( void );

extern inline int AiGetNumObjects(void);
extern inline int AiGetNumCategories(void);
extern void ClearAiData();

AI_ITBL *AiGetObjectDefs( int category, int number, int damagelevel );
AI_ITBL *AiGetNextObjectDef( AI_ITBL *aiPtr );

extern	void	AiDumpCPN( void );
extern	void	AiDumpVisibility( void );

///========================================================================

#endif		// __AI_H__

///========================================================================
//								EOF
///========================================================================
