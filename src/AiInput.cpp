//========================================================================
//	FILE:			$Workfile: AiInput.cpp $
//
//	DESCRIPTION:	Artificial Intelligence (AI) default settings external
//					input processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Monday, October 07, 1996
//
//	REVISION:		$Header: /ArmyMen/src/AiInput.cpp 94    4/17/98 2:29p Dmaynard $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	AiGetCommand()
//		parse the input string for the next command.
//	AiAcquireToken()
//		parse the input string for the next token.
//	AiAcquireNumber()
//		parse the input string for a numerical value.
//	AiLoadLine()
//		extract the next line of data from the input source.
//	AiFlushInput()
//		flush the input stream up to the newline or null.
//-------------------------------------------------------------------------
//	AiDumpInfo()
//		Dump the AI_INFO structure.
//	WeaponName()
//		return the string equivalent for a weapon type.
//	IsNumeric()
//		verify that the caller's input is a numeric character.
//	IsWhiteSpace()
//		verify that the caller's input is a white space character.
//	StripWhiteSpace()
//		strip away any leading white space in the command string.
//	SkipToWhiteSpace()
//		skip forward through the data until you locate some white space.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/AiInput.cpp $
//  
//  94    4/17/98 2:29p Dmaynard
//  Found and Fixed Damaged RUL file bug (AIFileName was getting
//  overwritten in single player games)
//  
//  92    4/03/98 4:18p Aburgess
//  modifications to fix next mission bug
//  
//  91    3/31/98 2:43p Bwilcox
//  cleanups and better script debug
//  
//  90    3/27/98 1:38p Nrobinso
//  rename aigetmissionkey
//  
//  89    3/27/98 10:52a Dmaynard
//  Added Checksumming of AiDefault.aii files in Map Checking
//  
//  88    3/26/98 8:53p Bwilcox
//  
//  87    3/25/98 6:26p Nrobinso
//  have multiple mission voice overs
//  
//  86    3/25/98 3:43p Nrobinso
//  properly get the mission briefing
//  
//  85    3/24/98 1:14p Nrobinso
//  don't assert if bad message id, just set it to null
//  
//  84    3/23/98 4:07p Aburgess
//  added Mission KEY fields
//  
//  83    3/23/98 1:57p Nrobinso
//  fix problem in inisitalizing of ai data tables
//  
//  82    3/12/98 2:10p Aburgess
//  modifications to put music in multiplayer games using terrain type
//  
//  81    3/11/98 7:24p Phu
//  crush damage when set to last damage sprite
//  
//  80    2/25/98 9:23p Nrobinso
//  recognize special unit troopers
//  
//  79    2/04/98 3:16p Phu
//  armor for objects
//  
//  78    2/02/98 1:00p Aburgess
//  modifications made to support new mission briefing references through
//  campaign.cpn
//  
//  77    2/01/98 4:31p Aburgess
//  modifications made to support new ART and maps files
//  
//  76    1/29/98 5:50p Bwilcox
//  unit names system changed
//  
//  75    1/25/98 4:55a Bwilcox
//  paracount added for aai files
//  
//  74    1/23/98 11:19a Nrobinso
//  fix typo
//  
//  73    1/23/98 11:12a Nrobinso
//  change fence gate to gate
//  
//  72    1/23/98 11:09a Nrobinso
//  add GATE object category, replacing FENCE_GATE
//  
//  71    1/22/98 6:38p Nrobinso
//  use SetPath
//  
//  70    1/17/98 7:38a Bwilcox
//  added follow_radius, and follow_engaged radius and fixed a
//  defend-radius bug
//  
//  69    1/15/98 5:05p Phu
//  new aai
//  
//  68    1/12/98 4:48p Phu
//  acquire armor value
//  
//  67    1/09/98 8:37a Aburgess
//  fixed initialization of campaign data
//  
//  66    1/08/98 2:18p Bwilcox
//  
//  65    1/08/98 2:11p Bwilcox
//  attack paramaters and trooper slide parameters added to defaults file
//  
//  64    1/08/98 1:19p Bwilcox
//  parameters now in aidefaults.aai (runtime) include
//  DEFENSE_RADIUS, TROOPER_TURN_RATE, TROOPER_POSE_RATE, VEHICLE_DANGER,
//  VEHICLE_STANDOFF
//  
//  63    1/07/98 1:41p Aburgess
//  adjusted access of campaign data to use g_numbercampaigns rather than
//  AI_MAX_CAMPAIGNS
//  
//  62    12/22/97 4:42p Phu
//  medkits & medpacks
//  
//  61    12/16/97 12:20p Dmaynard
//  Temp fix for AiScenarioIndex error in MultiPlayer game
//  
//  60    12/15/97 1:02a Aburgess
//  added debug routine AiDumpVisibility()
//  
//  59    12/11/97 1:48p Aburgess
//  debug for NextMission flag setting
//  
//  58    12/11/97 10:16a Aburgess
//  made AiDumpCPN more accessible
//  
//  57    12/09/97 12:11p Phu
//  
//  56    12/07/97 7:28p Phu
//  read in unit names
//  
//  55    12/05/97 4:08p Phu
//  
//  54    12/05/97 2:50p Phu
//  visibility layer
//  
//  53    12/04/97 8:59a Aburgess
//  Modifications made to support Mission Statement Voice ID and Music ID.
//  Missions Statement Text now in the Voices.opt file
//  
//  52    11/26/97 12:01p Awerner
//  multi part objects can now be on any of the 3 layers
//  
//  51    11/26/97 11:03a Awerner
//  Fixed bug in multi-part object loading
//  
//  50    11/24/97 2:48p Aburgess
//  expanded CAMPAIGN reader codes
//  
//  49    11/20/97 4:07p Phu
//  fix z_velocity keyword
//  
//  48    11/20/97 11:42a Aburgess
//  added AiCampaignFree
//  
//  47    11/18/97 11:35a Awerner
//  added capability for subobjects to be on specified layers
//  
//  46    11/17/97 10:54a Aburgess
//  acquireNumber properly implemented
//  
//  45    11/17/97 9:55a Aburgess
//  disabled debug statements with compile time flags
//  
//  44    11/16/97 7:13p Aburgess
//  corrected objTable load
//  
//  43    11/16/97 5:22p Nrobinso
//  add sitems; fix miscellaneous spelling
//  
//  42    11/16/97 2:17p Aburgess
//  moved routines around
//  
//  41    11/13/97 9:21a Aburgess
//  added height and movement to OBJECT data
//  
//  40    11/12/97 10:17a Aburgess
//  re-initialize campaign globals at campaign load
//  
//  39    11/11/97 4:51p Phu
//  Guard Towers
//  
//  38    11/11/97 8:53a Nrobinso
//  changed commander to sarge in ai file
//  
//  37    11/10/97 5:21p Awerner
//  Kludgy fix to AI loading code to load in part numbers
//  
//  36    11/07/97 12:18p Aburgess
//  call to stablize ID and Indecies for campaign data
//  
//  35    11/07/97 10:24a Aburgess
//  added index to ID conversion routines
//  
//  34    11/05/97 1:32p Nrobinso
//  add vehicle collision damage; comment out engineers
//  
//  33    11/03/97 9:44a Aburgess
//  added mission ID global
//  
//  32    10/30/97 10:43a Phu
//  add mine sweeper weapon
//  
//  31    10/30/97 9:29a Nrobinso
//  changed sarge guns to rifle and auto rifle
//  
//  30    10/28/97 1:25p Bwilcox
//  moved decodepoint
//  
//  29    10/27/97 3:00p Phu
//  Fix for exploding barrels/ chain explosions
//  
//  28    10/27/97 10:31a Aburgess
//  merged in BW and NR changes
//  
//  27    10/27/97 10:26a Aburgess
//  changes made to support FULL SCREEN UI interface
//  
//  26    10/23/97 11:06a Nrobinso
//  fix movement table bug
//  
//  25    10/22/97 10:43a Bwilcox
//  boat renamed to convoy
//
//  24    10/20/97 2:31p Bwilcox
//  adjusted Makeweapon to use aidefaults.aai stuff
//  simplified aiinput code and expanded it to handle more sitems
//  
//  23    10/08/97 3:40p Nrobinso
//  ARMY_SARGE_GUN -> ARMY_RIFLE
//  
//  21    9/29/97 3:40p Aburgess
//  lastest changes for DIALOG representation of FullScreen UI screens
//  
//  20    9/23/97 3:00p Aburgess
//  latest modifications for Dialog base version
//  
//  19    8/18/97 2:56p Nrobinso
//  get object hp info
//  
//  18    8/18/97 2:27p Bwilcox
//  C = viewvisibility from unit
//  
//  17    8/17/97 11:27a Bwilcox
//  names of TROOPxxx are now TROOPERxxx in a cleanup
//  
//  16    8/16/97 1:43p Nrobinso
//  troopers have only 1 weapon
//  
//  15    8/13/97 6:52p Nrobinso
//  add weapon projectile speeds to aidefault file
//  
//  14    8/12/97 3:47p Nrobinso
//  added sarge gun
//  
//  13    8/07/97 11:09p Nrobinso
//  moved globals.h to stdafx.h
//  
//  12    8/03/97 8:57p Bwilcox
//  added VIS_RANGE to global defaults
//  
//  11    7/27/97 11:38a Nrobinso
//  pulled all the name functions out to TextData.cpp
//  
//  10    7/27/97 9:36a Nrobinso
//  remove helicopters; call mortars instead of artillery
//  
//  9     7/26/97 4:12p Nrobinso
//  fixed looking for an ARMY ID,n not an aiinput id; now sets troopers
//  besides riflemen
//  
//  8     7/23/97 3:31p Bwilcox
//  removed throw ranges. Now is only MIN and MAX range for a weapon.
//  
//  7     7/22/97 11:12a Awerner
//  corrected String input routine. (AJB)
//  
//  6     7/21/97 10:00p Aburgess
//  added processing for Long, Short, and Target name processing.
//  
//  5     7/15/97 7:51p Nrobinso
//  added rifle unit
//  
//  4     7/14/97 7:05p Nrobinso
//  updated UnitTypeName() and TrooperTypeName(); added UnitTypeShortName()
//  
//  3     7/05/97 10:15p Bwilcox
//  removed air refereneces
//  
//  2     7/03/97 7:56p Bwilcox
//  massive cleanups.
//  
//  25    6/30/97 2:41p Aburgess
//  AiDefaultLoad() now uses the terrain path to locate the input file
//  
//  24    6/30/97 7:47a Aburgess
//  added support for a slow speed in units.
//  
//  23    6/16/97 5:30p Bwilcox
//  
//  22    6/16/97 5:27p Bwilcox
//  added break for single trooper units when ONETROOPER is defined
//  
//  21    6/04/97 9:38a Aburgess
//  converted BASE token to BASEDOOR. Added new part count specification
//  commands for each object in the world.
//  
//  20    5/14/97 10:56a Nrobinso
//  fix trooper names to not have spaces
//  
//  19    5/07/97 9:30p Aburgess
//  added ASSERTs and context initialization.
//  
//  18    5/07/97 3:43p Dbunch
//  
//  17    4/23/97 2:08p Nrobinso
//  comment out name functions declarations and out them in army.h
//  
//  16    4/16/97 11:48a Nrobinso
//  Andrew: clear the composition
//  
//  15    4/14/97 7:28a Aburgess
//  modifications made to support full Army creation along with unit
//  reserves. Vehicle reserves have yet to be done.
//  
//  14    3/19/97 3:26p Aburgess
//  corrected activation setting
//  
//  13    3/18/97 3:35p Aburgess
//  added new composition parsing
//  
//  12    3/14/97 11:28a Aburgess
//  added Unit Composition and MainBase processing
//  
//  11    3/12/97 7:57a Aburgess
//  Added new Unit description, Trooper description, and Terrain Movement
//  description porcessing
//  
//  10    2/17/97 12:22p Aburgess
//  changed Hit_Points specifications to TroopStrength and Strength for
//  units and vehicles. Added Vehicle capacity specifications
//  
//  9     12/13/96 1:32p Aburgess
//  added TARGET tag for specifying target min and max acquisition values.
//  
//  8     11/20/96 9:17a Aburgess
//  move AI global routines to AI.CPP. This is now a module devited to the
//  default inputs for UNIT, VEHICLE, and WEAPON.
//  
//  7     11/18/96 11:54a Aburgess
//  added ACCEL fields to vehicle defaults: Forward, Reverse, and
//  deccelerate.
//  
//  6     10/15/96 7:49a Aburgess
//  
//  5     10/14/96 4:32p Aburgess
//  changed AiGetNumber to use strtok(). Medium Machine Gun now calls
//  Medium rather than Heavy
//  
//  4     10/14/96 4:04p Aburgess
//  corrected change to ...MISSILE..
//  
//  3     10/14/96 4:00p Aburgess
//  corrected AI command spelling and made TRACE statements compile-time
//  flaged
//  
//  2     10/14/96 9:37a Aburgess
//  initial release of the AI Defaults runtime loader
//  
//  1     10/11/96 3:56p Aburgess
//  AI external tuning input parser routines
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"

#include "Army.h"
#include "miscfile.h"
#include "Ai.h"
#include "Aix.h"
#include "Object.h"
#include "Screen.h"
#include "Stats.h"
#include "Audio.h"
#include "Map.h"
#include "GameFlow.h"

///========================================================================
//							LOCAL DEFINES
///========================================================================

///========================================================================
//							LOCAL DATA STRUCTURES
///========================================================================

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
void			AiDfLookAheadTime( int type);
void			AiDfMovementLookAhead( int type );
void			AiDfVisRange( int type );
void			AiDfVDanger( int type );
void			AiDfVStandoff( int type );
void			AiDfTTurnRate( int type );
void			AiDfTPoseRate( int type );
void			AiDfTSlideRate( int type );
void			AiDfDefenseRadius( int type );
void			AiDfAttackRadius( int type );
void			AiDfAttackHunt( int type );
void			AiDfFollowRadius( int type );
void			AiDfFollowEngagedRadius( int type );
void			AiDfParaCount( int type );

void			AiDfUnit(int type);
void			AiDfMen(int type);
void			AiDfVehicle( int type );
void			AiDfWeapon( int type );
void			AiDfGun( int type );
void			AiDfTroopers( int type );
void			AiDfCapacity( int type );
void			AiDfTroops( int type );
void			AiDfWeapon( int type );
void			AiDfTroopStrength( int type );
void			AiDfSpeed( int type );
void			AiDfAmmo( int type );
void			AiDfFuel( int type );
void			AiDfRateOfFire( int type );
void			AiDfLineOfSight( int type );
void			AiDfGroundMissile( int type );
void			AiDfConeSpread( int type );
void			AiDfAreaBurst( int type );
void			AiDfMinimumRange( int type );
void			AiDfMaximumRange( int type );
void			AiDfVelocity( int type );
void			AiDfZVelocity( int type );
void			AiDfCollisionDamage( int type );
void			AiDfArmor( int type );
void			AiDfPercentageDecreaseRate( int type );
void			AiDfDamage( int type );
void			AiDfDamageDecreaseRate( int type );
void			AiDfDrift( int type );
void			AiDfAccel( int type );
void			AiDfTarget( int type );
void			AiDfTerrain( int type );
void			AiDfObject( int type );
///========================================================================
void			AiDfGround( );
void			AiDfObjCategories(  );
void			AiDfObjIndividuals( int type );
void			AiDfUnitSetUp( int type );
void			AiDfUnitPower( int type );
void			AiDfUnitComposition( int type );
void			AiDfNameComposition( int type );
void			AiDfComposition( int type );
void			AiDfBaseDoor( int type );
///========================================================================
void			MapCampaign( int type );
void			MapScenario( int type );
void			MapMission( int type );
void			MapTitle( int type );
void			MapVisibility( int type );
void			MapMessage( int type );
void			MapFile( int type );
void			MapStratMap( int type );
void			MapMusic( int type );
void			MapAvi( int type );
void			MapKey( int type );
///========================================================================
AI_CMD_ENTRY*	AiGetCommand(  );
BOOL			AiAcquireToken( char* pToken );
BOOL			AiAcquireNumber( int* pTheNumber );
int				AiAcquireString( char* pTheString, int nMaxSize );
BOOL			AiLoadLine(  );
void			AiFlushInput(  );
void			AiDumpInfo( );
///========================================================================
BOOL			IsNumeric( char* pCharacter );
BOOL			IsWhiteSpace( char* pCharacter );
char*			StripWhiteSpace( char* pString );
char*			SkipToWhiteSpace( char* pString );
extern			char	AIfileName[];

///========================================================================
//							LOCAL VARIABLES
///========================================================================

// AI commands
AI_CMD_ENTRY	AIcommandTable[] =
{
	// Comment token
	{ "#",                    AI_COMMENT,            NULL },

	// Generic Game Parameters and Information
	{ "LAT",                  AI_LAT,                AiDfLookAheadTime },
	{ "MLA",                  AI_MLA,                AiDfMovementLookAhead },
	{ "VIS_RANGE",            AI_VISRANGE,           AiDfVisRange },

	{ "VEHICLE_DANGER",       AI_VEHICLEDANGER,      AiDfVDanger },
	{ "VEHICLE_STANDOFF", 	  AI_VEHICLESTANDOFF,    AiDfVStandoff },
	{ "TROOPER_TURN_RATE",    AI_TROOPERTURNRATE,    AiDfTTurnRate },
	{ "TROOPER_POSE_RATE",    AI_TROOPERPOSERATE,    AiDfTPoseRate },
	{ "TROOPER_SLIDE_RATE",    AI_TROOPERSLIDERATE,    AiDfTSlideRate },
	{ "DEFENSE_RADIUS",       AI_DEFENSERADIUS,      AiDfDefenseRadius },
	{ "ATTACK_HUNT_RADIUS",    AI_ATTACKHUNT,      AiDfAttackHunt },
	{ "ATTACK_RADIUS",       AI_ATTACKRADIUS,      AiDfAttackRadius },
	{ "FOLLOW_RADIUS",       AI_FOLLOWRADIUS,      AiDfFollowRadius },
	{ "FOLLOW_ENGAGED_RADIUS", AI_FOLLOWENGAGEDRADIUS, AiDfFollowEngagedRadius },

	{ "PARACOUNT", AI_PARACOUNT, AiDfParaCount },

	// Unit Parameters and Information
	{ "RIFLE_UNIT",			  AI_RIFLE_UNIT,		 AiDfUnit },
	{ "GRENADE_UNIT",		  AI_GRENADE_UNIT,       AiDfUnit },
	{ "FLAME_UNIT",			  AI_FLAME_UNIT,         AiDfUnit },
	{ "BAZOOKA_UNIT",         AI_BAZOOKA_UNIT,       AiDfUnit },
	{ "MORTAR_UNIT",          AI_MORTAR_UNIT,        AiDfUnit },
	{ "MINER_UNIT",           AI_MINER_UNIT,         AiDfUnit },
	{ "SPECIAL_UNIT",         AI_SPECIAL_UNIT,       AiDfUnit },

	// Trooper Parameters and Information
	{ "RIFLE_MEN",		      AI_RIFLE_MEN,          AiDfMen },
	{ "GRENADE_MEN",          AI_GRENADE_MEN,        AiDfMen },
	{ "FLAME_MEN",            AI_FLAME_MEN,          AiDfMen },
	{ "BAZOOKA_MEN",          AI_BAZOOKA_MEN,        AiDfMen },
	{ "MORTAR_MEN",           AI_MORTAR_MEN,         AiDfMen },
	{ "MINER_MEN",            AI_MINER_MEN,          AiDfMen },
	{ "SPECIAL_MEN",          AI_SPECIAL_MEN,        AiDfMen },

	// Vehicle Parameters and Information
	{ "JEEP",                 AI_JEEP,	             AiDfVehicle },
	{ "TANK",                 AI_TANK,               AiDfVehicle },
	{ "HALF_TRACK",           AI_HALFTRACK,          AiDfVehicle },
	{ "CONVOY",               AI_CONVOY,             AiDfVehicle },
	{ "SARGE",				  AI_SARGE,				 AiDfVehicle },

	// Weapon Parameters and Information
	{ "LIGHT_MACHINE_GUN",     AI_LIGHT_MACHINE_GUN,  AiDfWeapon },
	{ "MEDIUM_MACHINE_GUN",    AI_MEDIUM_MACHINE_GUN, AiDfWeapon },
	{ "HEAVY_MACHINE_GUN",     AI_HEAVY_MACHINE_GUN,  AiDfWeapon },
	{ "FLAME_THROWER",	       AI_FLAME_THROWER,      AiDfWeapon },
	{ "GRENADE",               AI_GRENADE,            AiDfWeapon },
	{ "BAZOOKA",               AI_BAZOOKA,            AiDfWeapon },
	{ "MORTAR",                AI_MORTAR,             AiDfWeapon },
	{ "LARGE_CANNON",          AI_LARGE_CANNON,       AiDfWeapon },
	{ "RIFLE",					AI_RIFLE,	          AiDfWeapon },
	{ "AUTO_RIFLE",				AI_AUTO_RIFLE,	      AiDfWeapon },
	{ "SWEEPER",				AI_ARMY_SWEEPER,	  AiDfWeapon },
	{ "MINE",        			AI_ARMY_MINE,	      AiDfWeapon },
	{ "EXPLOSIVE",				AI_ARMY_EXPLOSIVE,    AiDfWeapon },
	{ "TOWER_RIFLE",			AI_ARMY_GUARD_TOWER_RIFLE,	AiDfWeapon },	
	{ "MEDKIT",					AI_ARMY_MEDKIT,		  AiDfWeapon },
	{ "MEDPACK",				AI_ARMY_MEDPACK,	  AiDfWeapon },

	// Projectile Parameters and Information
	{ "LINE_OF_SIGHT",            AI_LINE_OF_SIGHT,            AiDfLineOfSight },
	{ "GROUND_MISSILE",           AI_GROUND_MISSILE,           AiDfGroundMissile },
	{ "CONE",                     AI_CONE,                     AiDfConeSpread },
	{ "AREA",                     AI_AREA,                     AiDfAreaBurst },

	// Projectile Parameters and Information
	{ "T_0",                      AI_T_0,                      AiDfTerrain },
	{ "T_1",                      AI_T_1,                      AiDfTerrain },
	{ "T_2",                      AI_T_2,                      AiDfTerrain },
	{ "T_3",                      AI_T_3,                      AiDfTerrain },
	{ "T_4",                      AI_T_4,                      AiDfTerrain },
	{ "T_5",                      AI_T_5,                      AiDfTerrain },
	{ "T_6",                      AI_T_6,                      AiDfTerrain },
	{ "T_7",                      AI_T_7,                      AiDfTerrain },
	{ "T_8",                      AI_T_8,                      AiDfTerrain },
	{ "T_9",                      AI_T_9,                      AiDfTerrain },
	{ "T_10",                     AI_T_10,                     AiDfTerrain },
	{ "T_11",                     AI_T_11,                     AiDfTerrain },
	{ "T_12",                     AI_T_12,                     AiDfTerrain },
	{ "T_13",                     AI_T_13,                     AiDfTerrain },
	{ "T_14",                     AI_T_14,                     AiDfTerrain },
	{ "T_15",                     AI_T_15,                     AiDfTerrain },

// Objects Parts Parameters and Information
	{ "ROCK",                     AI_ROCK,                     AiDfObject },
	{ "BUSH",				      AI_BUSH,                     AiDfObject },
	{ "TREE",				      AI_TREE,                     AiDfObject },
	{ "BIGTREE",				  AI_BIGTREE,                  AiDfObject },
	{ "FALLENTREE",			      AI_FALLENTREE,               AiDfObject },
	{ "FENCE",				      AI_FENCE,                    AiDfObject },
	{ "WALL",				      AI_WALL,                     AiDfObject },
	{ "BRIDGE",				      AI_BRIDGE,                   AiDfObject },
	{ "FOOTBRIDGE",			      AI_FOOTBRIDGE,               AiDfObject },
	{ "EXPLOSIVES",			      AI_EXPLOSIVES,               AiDfObject },
	{ "GUNTURRET",			      AI_GUNTURRET,                AiDfObject },
	{ "AAGUN",				      AI_AAGUN,                    AiDfObject },
	{ "BASE",				      AI_BASE,                     AiDfObject },
	{ "AUXBASE",				  AI_AUXBASE,                  AiDfObject },
	{ "AIRSTRIP",			      AI_AIRSTRIP,                 AiDfObject },
	{ "HELIPAD",				  AI_HELIPAD,                  AiDfObject },
	{ "PRISONCAMP",			      AI_PRISONCAMP,               AiDfObject },
	{ "BUILDING",			      AI_BUILDING,                 AiDfObject },
	{ "PILLBOX",				  AI_PILLBOX,                  AiDfObject },
	{ "POWERPLANT",			      AI_POWERPLANT,               AiDfObject },
	{ "GATE",				      AI_GATE,                     AiDfObject },
	{ "WALLGATE",			      AI_WALLGATE,                 AiDfObject },
	{ "RADARBUILDING",            AI_RADARBUILDING,            AiDfObject },
	{ "MISCELLANEOUS",		      AI_MISCELLANEOUS,            AiDfObject },
	{ "OVERPASS",                 AI_OVERPASS,                 AiDfObject },
	{ "SITEMS",					  AI_SITEMS,				   AiDfObject },

	// Secondary Parameters and Information
	{ "TROOPERS",                 AI_TROOPERS,                 AiDfTroopers },
	{ "CAPACITY",                 AI_CAPACITY,                 AiDfCapacity },
	{ "TROOPS",                   AI_TROOPS,                   AiDfTroops },
	{ "WEAPON",                   AI_WEAPONS,                  AiDfGun },
	{ "TROOP_STRENGTH",           AI_TROOP_STRENGTH,           AiDfTroopStrength },
	{ "SPEED",                    AI_SPEEDS,                   AiDfSpeed },
	{ "AMMO",                     AI_AMMOS,                    AiDfAmmo },
	{ "FUEL",                     AI_FUELS,                    AiDfFuel },
	{ "ARMOR",                    AI_ARMOR,                    AiDfArmor },
	{ "RATE_OF_FIRE",             AI_RATE_OF_FIRE,             AiDfRateOfFire },
	{ "MINIMUM_RANGE",            AI_MINIMUM_RANGE,            AiDfMinimumRange },
	{ "MAXIMUM_RANGE",            AI_MAXIMUM_RANGE,            AiDfMaximumRange },
	{ "PERCENTAGE_DECREASE_RATE", AI_PERCENTAGE_DECREASE_RATE, AiDfPercentageDecreaseRate },
	{ "DAMAGE",                   AI_DAMAGES,                  AiDfDamage },
	{ "DAMAGE_DECREASE_RATE",     AI_DAMAGE_DECREASE_RATE,     AiDfDamageDecreaseRate },
	{ "DRIFT",                    AI_DRIFT,                    AiDfDrift },
	{ "ACCEL",                    AI_ACCEL,                    AiDfAccel },
	{ "TARGET",					  AI_TARGET,                   AiDfTarget },
	{ "VELOCITY",				  AI_VELOCITIES,               AiDfVelocity },
	{ "Z_VELOCITY",				  AI_ZVELOCITIES,              AiDfZVelocity },
	{ "COLLISION",				  AI_COLLISION,				   AiDfCollisionDamage },

	// Composition TOKEN IDS
	{ "UNIT_POWER",               AI_UNIT_POWER,               AiDfUnitPower },
	{ "UNIT",                     AI_UNIT,                     AiDfUnitComposition },
	{ "NAME",                     AI_NAME,                     AiDfNameComposition },
	{ "COMPOSITION",			  AI_COMPOSITION,              AiDfComposition },

	// Base TOKEN IDS
	{ "BASEDOOR",                 AI_BASE_DOOR,				   AiDfBaseDoor },

	// Campaign select TOKEN IDS
	{ "CAMPAIGN",                 CAMPAIGN_ID,				   MapCampaign },
	{ "SCENARIO",                 SCENARIO_ID,				   MapScenario },
	{ "MISSION",				  MISSION_ID,				   MapMission },
	{ "TITLE",					  TITLE_ID,				       MapTitle },
	{ "VISIBILITY",				  VISIBILITY_ID,			   MapVisibility },
	{ "MESSAGE",				  MESSAGE_ID,				   MapMessage },
	{ "MAPFILE",				  MAPFILE_ID,				   MapFile },
	{ "STARTMAP",				  STARTMAP_ID,				   MapStratMap },
	{ "MUSIC",					  MUSIC_ID,				       MapMusic },
	{ "AVI",					  AVI_ID,				       MapAvi },
	{ "KEY",					  KEY_ID,				       MapKey },

	// END OF LIST marker
	{ "EOL",                      AI_EOL,                      NULL },
	{ "\0",                       NULL,                        NULL }
};

void*			AIactivePtr;
int				AIcontext;
FILE*			AIfile;
HRSRC			AIresourceHandle;
char*			AIresource;
char*			AIresourcePtr;
char			AIcommandLine[256];
int				AIlineCount;
char*			AItokenPtr;
// char			AIfileName[132];     // Moved to USA.h
short			AIterrainContext;
short			AIpartContext;
int				AIiObjsCount;
int				AIobjsCount;
char			AIlogMessage[256];

//static	BOOL	AIfirstLoad      = FALSE;
//static	BOOL	AIdataLoaded     = FALSE;
BOOL			AIcampaignLoaded = FALSE;

		CAMPAIGNREF*	g_Campaigns[ AI_MAX_CAMPAIGNS ];
static	CAMPAIGNREF*	g_pCampaign = NULL;
		int				g_NumberCampaigns = 0;
		int				g_NumberScenarios = 0;
		int			    g_CampaignIndex   = 0;
		int			    g_ScenarioIndex   = 0;
		int			    g_MissionIndex    = 0;
		USHORT			g_MissionID;


void ClearAiData()	{
	ZeroMemory( &AIinfo, sizeof( AI_INFO ) );
	AIiObjsCount = 0;
	AIobjsCount  = 0;
}

inline int AiObjectKey( int category, int number, int damagelevel )
{
	return( damagelevel + (number << 5) + (category << 15) );
}


AI_ITBL *AiGetNextObjectDef( AI_ITBL *aiPtr )
{
	AI_ITBL *aiPtrB;

	if( (aiPtr > &(AIinfo.objIndivTables[0])) &&
		(aiPtr <= &(AIinfo.objIndivTables[AiGetNumObjects()-1])) )
	{
		aiPtrB = aiPtr + 1;
		if( (aiPtr->nCategoryID == aiPtrB->nCategoryID) &&
			(aiPtr->nObjectID == aiPtrB->nObjectID) )
			return( aiPtrB );
	}
	else
	if( (aiPtr > &(AIinfo.objTables[0])) &&
		(aiPtr <= &(AIinfo.objTables[AiGetNumCategories()-1])) )
	{
		aiPtrB = aiPtr + 1;
		if( (aiPtr->nCategoryID == aiPtrB->nCategoryID) &&
			(aiPtr->nObjectID == aiPtrB->nObjectID) )
			return( aiPtrB );
	}
	return( NULL );
}


AI_ITBL *AiGetObjectDefs( int category, int number, int damagelevel )
{
	int i, min, max, key, ikey;
	AI_ITBL *aiPtr;

	key = AiObjectKey( category, number, damagelevel );

	if( number != 0 )
	{
		// do a binary search on the individual object defaults table
		min = 0;
		max = AiGetNumObjects();
		while( max > min )
		{
			i = min + ((max - min) >> 1);
			aiPtr = &(AIinfo.objIndivTables[i]);
			ikey = AiObjectKey( aiPtr->nCategoryID, aiPtr->nObjectID, aiPtr->nDamageLevel );
			if( ikey == key )
				return( aiPtr );
			else
			if( ikey < key )
				min = i + 1;
			else
				max = i;
		}
	}

	key = AiObjectKey( category, 0, damagelevel );
	// do a binary search on the categories defaults table
	min = 0;
	max = AiGetNumCategories();
	while( max > min )
	{
		i = min + ((max - min) >> 1 );
		aiPtr = &(AIinfo.objTables[i]);
		ikey = AiObjectKey( aiPtr->nCategoryID, 0, aiPtr->nDamageLevel );
		if( ikey == key )
			return( aiPtr );
		else
		if( ikey < key )
			min = i + 1;
		else
			max = i;
	}

	// not found on either table
	return NULL;
}


void AiSwapObjectEntries( AI_ITBL *aiPtrA, AI_ITBL *aiPtrB )
{
	AI_ITBL temp;

	memcpy( &temp, aiPtrA, sizeof(AI_ITBL) );
	memcpy( aiPtrA, aiPtrB, sizeof(AI_ITBL) );
	memcpy( aiPtrB, &temp, sizeof(AI_ITBL) );
}


// I know this is a lame sorting algorithm & I'm going to use it anyways
void AiSortIndividualTable( void )
{
	int hasmismatch;
	int i, keyA, keyB;
	AI_ITBL *aiPtrA, *aiPtrB;

	if( AiGetNumObjects() < 1 )
		return;

	do
	{
		aiPtrA = &(AIinfo.objIndivTables[0]);
		keyA = AiObjectKey( aiPtrA->nCategoryID, aiPtrA->nObjectID, aiPtrA->nDamageLevel );
		hasmismatch = FALSE;
		for( i = 0; i < AiGetNumObjects()-1; i++ )
		{
			aiPtrB = &(AIinfo.objIndivTables[i+1]);
			keyB = AiObjectKey( aiPtrB->nCategoryID, aiPtrB->nObjectID, aiPtrB->nDamageLevel );
			if( keyA > keyB )
			{
				AiSwapObjectEntries( aiPtrA, aiPtrB );
				hasmismatch = TRUE;
			}	
			else
			{
				aiPtrA = aiPtrB;
				keyA = keyB;
			}
		}
	}	while( hasmismatch );
}


// I know this is a lame sorting mechanism & I'm going to use it anyways
void AiSortCategoryTable( void )
{
	int hasmismatch;
	int i, keyA, keyB;
	AI_ITBL *aiPtrA, *aiPtrB;

	if( AiGetNumCategories() < 1 )
		return;

	do
	{
		aiPtrA = &(AIinfo.objTables[0]);
		keyA = AiObjectKey( aiPtrA->nCategoryID, aiPtrA->nObjectID, aiPtrA->nDamageLevel );
		hasmismatch = FALSE;
		for( i = 0; i < AiGetNumCategories()-1; i++ )
		{
			aiPtrB = &(AIinfo.objTables[i+1]);
			keyB = AiObjectKey( aiPtrB->nCategoryID, aiPtrB->nObjectID, aiPtrB->nDamageLevel );
			if( keyA > keyB )
			{
				AiSwapObjectEntries( aiPtrA, aiPtrB );
				hasmismatch = TRUE;
			}	
			else
			{
				aiPtrA = aiPtrB;
				keyA = keyB;
			}
		}
	}	while( hasmismatch );
}


void AiProcessObjects( void )
{
	AiSortIndividualTable();
	AiSortCategoryTable();

	int i;
	AI_ITBL *aiPtrA, *aiPtrB;

	for( i = 0; i < AiGetNumObjects()-1; i++ )
	{
		aiPtrA = &(AIinfo.objIndivTables[i]);
		if( aiPtrA->nDamageLevel > 1 )
		{
			// make sure numbering starts at 0
			aiPtrB = AiGetObjectDefs( aiPtrA->nCategoryID, aiPtrA->nObjectID, 0 );
			if( !aiPtrB )
				TRACE( "Missing damage level 1 for object [%d,%d]\n", aiPtrA->nCategoryID, aiPtrA->nObjectID );
			// make sure previous item is -1 to current one
			aiPtrB = AiGetObjectDefs( aiPtrA->nCategoryID, aiPtrA->nObjectID, aiPtrA->nDamageLevel - 1 );
			if( !aiPtrB )
				TRACE( "Missing damage level %d for object [%d,%d]\n", aiPtrA->nDamageLevel, aiPtrA->nCategoryID, aiPtrA->nObjectID );
		}
	}

	for( i = 0; i < AiGetNumCategories()-1; i++ )
	{
		aiPtrA = &(AIinfo.objTables[i]);
		if( aiPtrA->nDamageLevel > 1 )
		{
			// make sure numbering starts at 0
			aiPtrB = AiGetObjectDefs( aiPtrA->nCategoryID, aiPtrA->nObjectID, 0 );
			if( !aiPtrB )
				TRACE( "Missing damage level 1 for object [%d,%d]\n", aiPtrA->nCategoryID, aiPtrA->nObjectID );
			// make sure previous item is -1 to current one
			aiPtrB = AiGetObjectDefs( aiPtrA->nCategoryID, aiPtrA->nObjectID, aiPtrA->nDamageLevel - 1 );
			if( !aiPtrB )
				TRACE( "Missing damage level %d for object [%d,%d]\n", aiPtrA->nDamageLevel, aiPtrA->nCategoryID, aiPtrA->nObjectID );
		}
	}
}


///========================================================================
//	Function:		AiDefaultLoad()
//
//	Description:
//		Load in the AI default settings for Units, Vehicles, and Weapons.
//
//	Input:			pInput		optional AI default data input file.
//
//	Ouput:			none
//
///========================================================================

void	AiDefaultLoad( char* pPathName )
{
	// initialize application globals
	AIfile              = NULL;
	AIlineCount         = -1;
	strcpy( AIfileName, "AiDefault.AAI" );
	AIcommandLine[0]    = '\0';
	AIresourceHandle    = 0;

	// The AI default file
	AIresourceHandle = FindResource( NULL, AIfileName, RT_RCDATA );
	if ( AIresourceHandle )
	{
#ifdef AI_DEBUG
TRACE( "AiDefaultLoad( %s : %s )\n", pPathName, AIfileName );
#endif
		AIresource = (char*)LockResource( LoadResource( NULL, AIresourceHandle) );
        if ( !AIresource )
		{
            TRACE( "lock resource failed\n" );
			return;
		}

		// remember the current input location
		AIresourcePtr = AIresource;
	}
	else
	{
		// check to see if the file is on the CDROM 
		if ( pPathName )
		{
#ifdef AI_DEBUG
TRACE( "AiDefaultLoad( %s : %s )\n", pPathName, AIfileName );
#endif
			SetPath( pPathName );
		}
		else
		{
#ifdef AI_DEBUG
TRACE( "AiDefaultLoad( %s : %s )\n", AAI_PATH, AIfileName );
#endif
			SetPath( AAI_PATH );
		}

		// now open the ASCII data file
		if ( (AIfile = (FILE*)fopen( AIfileName, "rt" )) == NULL )
		{
			// report an error
			TRACE("ERROR: failed to open file: \"%s\". [%s:%d]\n\n", 
				  AIfileName, __FILE__, __LINE__ );
			goto exit;
		}
	}

	// Process the build file <filename>.aai
	AiInput( );

exit:
	// now close the file or resource
	if ( !AIresourceHandle )
	{
		// close in input file
		if ( AIfile )
			fclose( AIfile );
		AIfile = NULL;
	}
	if ( AIresourceHandle )
		AIresourceHandle = NULL;
	AiDumpInfo();

	return;
}

///========================================================================
//	Function:		AiCampaignLoad()
//
//	Description:
//		Load in the campaign choices for the user.
//
//	Input:			pFileName		campaign data filename.
//
//	Ouput:			none
//
///========================================================================

void	AiCampaignLoad( char* pFileName )
{
	BOOL	bRunMakeAllVisible = FALSE;
	char oldFileName[250];

	// make sure we've cleared any previous data
	if ( AIcampaignLoaded )
	{
//		StatStable();
		AiCampaignFree();
	}

	// see if we need to run make all visible
	if ( g_NumberCampaigns == -1 )
		StatMakeAllVisible();

	// initialize application globals
	AIfile              = NULL;
	AIlineCount         = -1;
	strcpy( oldFileName, AIfileName );
	strcpy( AIfileName, pFileName );
	AIcommandLine[0]    = '\0';
	AIresourceHandle    = 0;
	g_NumberCampaigns   = 0;
	g_NumberScenarios   = 0;

	// The AI default file
	AIresourceHandle = FindResource( NULL, pFileName, RT_RCDATA );
	if ( AIresourceHandle )
	{
#ifdef CAMPAIGN_DEBUG
		TRACE( "AiCampaignLoad( %s ) RESOURCE\n", pFileName );
#endif
		AIresource = (char*)LockResource( LoadResource( NULL, AIresourceHandle) );
        if ( !AIresource )
		{
            TRACE( "lock resource failed\n" );
			goto exit;
		}

		// remember the current input location
		AIresourcePtr = AIresource;
	}
	else
	{
#ifdef CAMPAIGN_DEBUG
		TRACE( "AiCampaignLoad( %s ) FILE\n", pFileName );
#endif

		// now open the ASCII data file
		if ( (AIfile = (FILE*)fopen( pFileName, "rt" )) == NULL )
		{
			// report an error
			TRACE("ERROR: failed to open file: \"%s\". [%s:%d]\n\n", 
				  pFileName, __FILE__, __LINE__ );
			goto exit;
		}
	}

	// Process the campaign data
	AiInput( );
	strcpy(AIfileName,oldFileName);
	// now look for mission completed data and adjust
	// the visibility
	StatStable();
	StatLoadCompletedMissions();

	// Now the campaign data has been fully loaded
	AIcampaignLoaded = TRUE;
exit:
	// now close the file or resource
	if ( !AIresourceHandle )
	{
		// close in input file
		if ( AIfile )
			fclose( AIfile );
		AIfile = NULL;
	}
	if ( AIresourceHandle )
		AIresourceHandle = NULL;
	AiDumpInfo();

	return;
}

///========================================================================
//	Function:		AiCampaignFree()
//
//	Description:
//		free up the campain,scenario, and mission base data.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiCampaignFree( void )
{
	int				nCampaign;

	for( nCampaign=0; nCampaign<g_NumberCampaigns; ++nCampaign )
	{
		free( g_Campaigns[ nCampaign ] );
		g_Campaigns[ nCampaign ] = NULL;
	}
	g_NumberCampaigns = 0;
}

///========================================================================
//	Function:		AiInput()
//
//	Description:
//		Parse the AI default settings data.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiInput(  )
{
	AI_CMD_ENTRY*	pCommand  = NULL;
	BOOL			done      = FALSE;

	// if this is the first load ever, clear the AIinfo structure
//	if ( AIfirstLoad )
//	{
//		ZeroMemory( &AIinfo, sizeof( AI_INFO ) );
//		AIiObjsCount = 0;
//		AIobjsCount  = 0;
//		AIfirstLoad  = FALSE;
//	}

	// initialize the input context
	AIcontext = AI_NO_CONTEXT;

	// loop until file is completely read
	while( !done  )
	{
		// read in a line of data from the file
		if ( !AiLoadLine( ) )
			done = TRUE;	// report that we've finished
		else
		{
			// Parse the line to see what type of command it is
			pCommand = AiGetCommand();

			// see if we found the command
			if ( pCommand )
			{
				// execute the associated function
				if ( pCommand->pActionFunc )
					(pCommand->pActionFunc)((int)pCommand->nCmdID);
			}
		}
	}

	AiProcessObjects( );
}

///========================================================================
//	Function:		AiDfLookAheadTime()
//
//	Description:
//		acquire the Look Ahead Time for calculating the Zone Of Control
//		from weapons.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfLookAheadTime( int type )
{
	int	nLookAheadTime;

	// we need to acquire the look ahead time value
	if ( AiAcquireNumber( &nLookAheadTime ) )
	{
		AIinfo.nLookAheadTime = nLookAheadTime;
#ifdef AI_DEBUG
		TRACE("%d\n", nLookAheadTime );
#endif
	}
}

///========================================================================
//	Function:		AiDfMovementLookAhead()
//
//	Description:
//		acquire the Movement Look Ahead value. The distance a unit looks
//		ahead during local movement.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfMovementLookAhead( int type )
{
	int	nMovementLookAhead;

	// we need to acquire the movement look ahead value
	if ( AiAcquireNumber( &nMovementLookAhead ) )
	{
		AIinfo.nMovementLookAhead = nMovementLookAhead;
#ifdef AI_DEBUG
		TRACE("%d\n", nMovementLookAhead );
#endif
	}
}

///========================================================================
//	Function:		AiDfVisRange()
//	Description:	range troopers can see
///========================================================================

void	AiDfVisRange( int type )
{
	int	nRange;

	// we need to acquire the movement look ahead value
	if ( AiAcquireNumber( &nRange ) )
	{
		 if (visibilityRange != nRange)
		 {
			 TRACE("ignoring vis range\n");
			return;
		}
       visibilityRange = nRange;
	}
}

///========================================================================
//	Function:		AiDfVDanger()
//	Description:	vehicle avoid radius
///========================================================================

extern int VEHICLE_DANGER;
void	AiDfVDanger( int type ){
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) VEHICLE_DANGER = nRange;
}

///========================================================================
//	Function:		AiDfVStandoff()
//	Description:	own vehicle approach radius
///========================================================================

extern int VEHICLE_STANDOFF;
void	AiDfVStandoff( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) VEHICLE_STANDOFF = nRange;
}

///========================================================================
//	Function:		AiDfTTurnRate()
//	Description:	how many frames in one pose before change allowed
///========================================================================

extern int TROOPER_TURNRATE;
void	AiDfTTurnRate( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) TROOPER_TURNRATE = nRange;
}

///========================================================================
//	Function:		AiDfTPoseRate()
//	Description:	moving trooper turning rate per frame
///========================================================================

extern int LINGER_RATE;
void	AiDfTPoseRate( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) LINGER_RATE = nRange;
}

///========================================================================
//	Function:		AiDfTSlideRate()
//	Description:	moving trooper turning rate per frame
///========================================================================

extern int TROOPER_SLIDERATE;
void	AiDfTSlideRate( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) TROOPER_SLIDERATE = nRange;
}

///========================================================================
//	Function:		AiDfDefenseRadius()
//	Description:	moving trooper turning rate per frame
///========================================================================

extern int DEFENSE_RADIUS;
void	AiDfDefenseRadius( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) DEFENSE_RADIUS = nRange;
}

///========================================================================
//	Function:		AiDfAttackRadius()
//	Description:	
///========================================================================

extern int ATTACK_RADIUS;
void	AiDfAttackRadius( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) ATTACK_RADIUS = nRange;
}

///========================================================================
//	Function:		AiDfAttackHunt()
//	Description:	how far to look around center during patrol
///========================================================================

extern int ATTACK_TILES;
void	AiDfAttackHunt( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) ATTACK_TILES = nRange;
}


///========================================================================
//	Function:		AiDfFollowRadius()
//	Description:	
///========================================================================

extern int FOLLOW_RADIUS;
void	AiDfFollowRadius( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) FOLLOW_RADIUS = nRange;
}

///========================================================================
//	Function:		AiDfFollowEngagedRadius()
//	Description:	
///========================================================================

extern int FOLLOW_ENGAGED_RADIUS;
void	AiDfFollowEngagedRadius( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) FOLLOW_ENGAGED_RADIUS = nRange;
}

///========================================================================
//	Function:		AiDfFollowEngagedRadius()
//	Description:	
///========================================================================

extern int PARACOUNT;
void	AiDfParaCount( int type )
{
	int	nRange;
	if ( AiAcquireNumber( &nRange ) ) PARACOUNT = nRange;
}



///========================================================================
//	Function:		AiDfUnit()
//	Description:	acquire the unit's information block.
///========================================================================

void	AiDfUnit(int type)
{
	// set the info pointer to the rifle unit entry
	AIactivePtr = (void*)&(AIinfo.unitTables[ type - UNIT_ID_BASE]);

	// set the AI context for later commands
	AIcontext = AI_UNIT_CONTEXT;

}


///========================================================================
//	Function:		AiDfMen()
//	Description:	acquire the men's information block.

void	AiDfMen(int type)
{
	// set the info pointer to the grenade men entry
	AIactivePtr = (void*)&(AIinfo.troopTables[ type - TROOP_ID_BASE]);

	// set the AI context for later commands
	AIcontext = AI_TROOP_CONTEXT;

}

///========================================================================
//	Function:		AiDfVehicle()
//	Description:	acquire the vhiecleinformation block.
///========================================================================

void	AiDfVehicle( int type )
{
	// set the info pointer to the Jeep entry
	AIactivePtr = (void*)&(AIinfo.vehicleTables[ type - VEHICLE_ID_BASE]);

	// set the AI context for later commands
	AIcontext = AI_VEHICLE_CONTEXT;
}

///========================================================================
//	Function:		AiDfWeapon()
//	Description:	acquire weapon of type
///========================================================================

void	AiDfWeapon(int type)
{
	// set the info pointer to the Grenade entry
	AIactivePtr = (void*)&(AIinfo.weaponTables[type - WEAPONS_ID_BASE]);

	// set the AI context for later commands
	AIcontext = AI_WEAPON_CONTEXT;
}

///========================================================================
//	Function:		AiDfTroopers()
//
//	Description:
//		acquire the maximum unit capacity for a vehicle type.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfTroopers( int type )
{
	AI_CMD_ENTRY*	pCommand;
	int				index;
	int				id;
	AI_UTBL*		pUnitInfo;

#ifdef AI_DEBUG
	TRACE( "command TROOPERS: " );
#endif

	// access the active pointer
	pUnitInfo = (AI_UTBL*)AIactivePtr;

	// the ids for the troopers here are the same as those of commands so
	// use the get next command mechanism to acquire them
	for ( index=0; index<2; ++index )
	{
		pCommand = AiGetCommand();

		// see if we found the command
		if ( pCommand )
		{
			// make sure that this is a weapon command type
			id = pCommand->nCmdID;
			if ( ( id >= AI_FIRST_MEN ) && ( id <= AI_LAST_MEN ) )
			{
#ifdef AI_DEBUG
				TRACE( "%s  ",  pCommand->pCmdName );
#endif

				if ( !index )
					pUnitInfo->makeup.ePrimary = (TROOPER_TYPE)(id - TROOP_ID_BASE);
				else
					pUnitInfo->makeup.eSecondary = (TROOPER_TYPE)(id - TROOP_ID_BASE);
			}
		}
	}

#ifdef AI_DEBUG
	TRACE ("\n");
#endif
}

///========================================================================
//	Function:		AiDfCapacity()
//
//	Description:
//		acquire the maximum unit capacity for a vehicle type.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfCapacity( int type )
{
	int			nCapacity;
	AI_VTBL*	pVehicleInfo;

#ifdef AI_DEBUG
	TRACE( "command CAPACITY: " );
#endif

	// acquire the maximum number of troops
	if ( AiAcquireNumber( &nCapacity ) )
	{
		// access the active pointer
		pVehicleInfo = (AI_VTBL*)AIactivePtr;

		// load the max troops value
		pVehicleInfo->capacity = nCapacity;

#ifdef AI_DEBUG
		TRACE( "%d\n", nCapacity );
#endif
	}
}

///========================================================================
//	Function:		AiDfTroops()
//
//	Description:
//		acquire the maximum troop strength for a unit type.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfTroops( int type )
{
	int			nTroops;
	AI_UTBL*	pUnitInfo;

#ifdef AI_DEBUG
	TRACE( "command TROOPS: " );
#endif

	// acquire the maximum number of troops
	if ( AiAcquireNumber( &nTroops ) )
	{
		// access the active pointer
		pUnitInfo = (AI_UTBL*)AIactivePtr;

		// load the max troops value
		pUnitInfo->nTroops = nTroops;

#ifdef AI_DEBUG
		TRACE( "%d\n", nTroops );
#endif
	}
}

///========================================================================
//	Function:		AiDfGun()
//
//	Description:
//		acquire weapons of choice.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfGun( int type )
{
	AI_CMD_ENTRY*	pCommand;
	int				index;
	int				maxIndex;
	int				id;
	AI_TTBL*		pTroopInfo;
	AI_VTBL*		pVehicleInfo;

#ifdef AI_DEBUG
	TRACE( "command WEAPON: " );
#endif

	// check the context to see who is acuiring the weapon info
	if ( AIcontext == AI_TROOP_CONTEXT )
	{
		// access the active pointer
		pTroopInfo = (AI_TTBL*)AIactivePtr;

		// Units have 1 weapon where as vehicles have 2
		maxIndex = 1;
	}
	else
	if ( AIcontext == AI_VEHICLE_CONTEXT )
	{
		// access the active pointer
		pVehicleInfo = (AI_VTBL*)AIactivePtr;

		// vehicles have 2 weapons where as units only have 1
		maxIndex = 2;
	}
	else
		ASSERT(0);

	// the ids for the weapons here are the same as those of commands so
	// use the get next command mechanism to acquire them
	for ( index=0; index<maxIndex; ++index )
	{
		pCommand = AiGetCommand();

		// see if we found the command
		if ( pCommand )
		{
			// make sure that this is a weapon command type
			id = pCommand->nCmdID;
			if ( ( id >= AI_FIRST_WEAPON ) && ( id <= AI_LAST_WEAPON ) )
			{
#ifdef AI_DEBUG
				TRACE( "%s  ",  pCommand->pCmdName );
#endif

				if ( AIcontext == AI_TROOP_CONTEXT )
				{
					pTroopInfo->weapon = (WEAPON_TYPE)(id - WEAPONS_ID_BASE);
				}
				else
				{
					if ( !index )
						pVehicleInfo->weapons.eWeapon1 = (WEAPON_TYPE)(id - WEAPONS_ID_BASE);
					else
						pVehicleInfo->weapons.eWeapon2 = (WEAPON_TYPE)(id - WEAPONS_ID_BASE);
				}
			}
		}
	}

#ifdef AI_DEBUG
	TRACE ("\n");
#endif
}

///========================================================================
//	Function:		AiDfTroopStrength()
//
//	Description:
//		acquire Troop Strength for a unit trooper or vehicle.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfTroopStrength( int type )
{
	int			nTroopStrength;
	AI_UTBL*	pUnitInfo;
	AI_VTBL*	pVehicleInfo;

#ifdef AI_DEBUG
	TRACE( "command TROOP_STRENGTH: " );
#endif

	// acquire the troop strength
	if ( AiAcquireNumber( &nTroopStrength ) )
	{
		// determine who recieves this info by the context
		if ( AIcontext == AI_UNIT_CONTEXT )
		{
			// access the active pointer
			pUnitInfo = (AI_UTBL*)AIactivePtr;

			// load the total hit points value
			pUnitInfo->nTroopStrength = nTroopStrength;

#ifdef AI_DEBUG
			TRACE( "%d\n", nTroopStrength );
#endif
		}
		else
		if ( AIcontext == AI_VEHICLE_CONTEXT )
		{
			// access the active pointer
			pVehicleInfo = (AI_VTBL*)AIactivePtr;

			// load the total hit points value
			pVehicleInfo->nHitPoints = nTroopStrength;

#ifdef AI_DEBUG
			TRACE( "%d\n", nTroopStrength );
#endif
		}
		else
			ASSERT(0);
	}
}

///========================================================================
//	Function:		AiDfSpeed()
//
//	Description:
//		acquire the speed attributes for a unit or vehicle.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfSpeed( int type )
{
	int			index;
	int			nNumSpeeds;
	int			nSpeed;
	AI_UTBL*	pUnitInfo;
	AI_VTBL*	pVehicleInfo;

#ifdef AI_DEBUG
	TRACE( "command SPEED: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	if ( AIcontext == AI_UNIT_CONTEXT )
	{
#ifdef AI_DEBUG
		TRACE( "(unit-3 speeds) " );
#endif
		pUnitInfo  = (AI_UTBL*)AIactivePtr;
		nNumSpeeds = 3;
	}
	else
	if ( AIcontext == AI_VEHICLE_CONTEXT )
	{
#ifdef AI_DEBUG
		TRACE( "(vehicle-2 speeds) " );
#endif
		pVehicleInfo = (AI_VTBL*)AIactivePtr;
		nNumSpeeds   = 2;
	}
	else
		ASSERT(0);

	// acquire the normal and run speeds
	for ( index=0; index<nNumSpeeds; ++index )
	{
		// acquire a speed value
		if ( AiAcquireNumber( &nSpeed ) )
		{
#ifdef AI_DEBUG
			TRACE( "%d  ", nSpeed );
#endif

			if ( AIcontext == AI_UNIT_CONTEXT )
			{
				// load the speed value
				switch( index )
				{
				case 0:
					pUnitInfo->speed.nSpeed0 = nSpeed;
					break;
				case 1:
					pUnitInfo->speed.nSpeed1 = nSpeed;
					break;
				case 2:
					pUnitInfo->speed.nSpeed2 = nSpeed;
					break;
				}
			}
			else
			{
				// load the speed value
				switch( index )
				{
				case 0:
					pVehicleInfo->speed.nSpeed1 = nSpeed;
					break;
				case 1:
					pVehicleInfo->speed.nSpeed2 = nSpeed;
					break;
				}
			}
		}
	}
#ifdef AI_DEBUG
	TRACE( "\n" );
#endif

}

///========================================================================
//	Function:		AiDfAmmo()
//
//	Description:
//		acquire the Ammo capacity for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfAmmo( int type )
{
	int			index;
	int			nAmmo;
	AI_VTBL*	pVehicleInfo;

#ifdef AI_DEBUG
	TRACE( "command AMMO: " );
#endif

	// access the active pointer
	pVehicleInfo = (AI_VTBL*)AIactivePtr;

	// acquire the weapon ammo values
	for ( index=0; index<2; ++index )
	{
		// acquire a ammo value
		if ( AiAcquireNumber( &nAmmo ) )
		{
#ifdef AI_DEBUG
			TRACE( "%d   ", nAmmo );
#endif

			// load the ammo value
			if ( !index )
				pVehicleInfo->ammo.nAmmo1 = nAmmo;
			else
				pVehicleInfo->ammo.nAmmo2 = nAmmo;
		}
	}

#ifdef AI_DEBUG
	TRACE( "\n" );
#endif
}

///========================================================================
//	Function:		AiDfFuel()
//
//	Description:
//		acquire the Fuel capacity for a vehicle.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfFuel( int type )
{
	int			index;
	int			nFuel;
	AI_VTBL*	pVehicleInfo;

#ifdef AI_DEBUG
	TRACE( "command FUEL: " );
#endif

	// access the active pointer
	pVehicleInfo = (AI_VTBL*)AIactivePtr;

	// acquire the fuel values
	for ( index=0; index<2; ++index )
	{
		// acquire a fuel value
		if ( AiAcquireNumber( &nFuel ) )
		{
#ifdef AI_DEBUG
			TRACE( "%d   ", nFuel );
#endif

			// load the fuel value
			if ( !index )
				pVehicleInfo->fuel.nTotalFuel = nFuel;
			else
				pVehicleInfo->fuel.nBurnRate  = nFuel;
		}
	}

#ifdef AI_DEBUG
	TRACE( "\n" );
#endif
}

///========================================================================
//	Function:		AiDfRateOfFire()
//
//	Description:
//		acquire the weapon Rate Of Fire attributes.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfRateOfFire( int type )
{
	int			index;
	int			nRateOfFire;
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command RATE_OF_FIRE: " );
#endif

	// access the active pointer
	pWeaponInfo = (AI_WTBL*)AIactivePtr;

	// acquire the rate of fire values
	for ( index=0; index<2; ++index )
	{
		// acquire a rate of fire value
		if ( AiAcquireNumber( &nRateOfFire ) )
		{
#ifdef AI_DEBUG
			TRACE( "%d   ", nRateOfFire );
#endif

			// load the rate of fire value
			if ( !index )
				pWeaponInfo->rateOfFire.nFrameDelay       = nRateOfFire;
			else
				pWeaponInfo->rateOfFire.nFrameContinuous  = nRateOfFire;
		}
	}

#ifdef AI_DEBUG
	TRACE( "\n" );
#endif
}

///========================================================================
//	Function:		AiDfLineOfSight()
//
//	Description:
//		acquire the Line Of Sight attributes for a weapon. Line of sight is
//      is a striaght line, hit or no hit, projectile. Its effect range
//      decreases over distance.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfLineOfSight( int type )
{
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command LINE_OF_SIGHT:\n" );
#endif

	// access the active pointer
	pWeaponInfo = (AI_WTBL*)AIactivePtr;

	// assign the projectile type
	pWeaponInfo->eProjectile = ARMY_LINE_OF_SIGHT;
}

///========================================================================
//	Function:		AiDfGroundMissile()
//
//	Description:
//		acquire the Ground Burst Damage attributes for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfGroundMissile( int type )
{
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command GROUND_MISSLE:\n" );
#endif

	// access the active pointer
	pWeaponInfo = (AI_WTBL*)AIactivePtr;

	// assign the projectile type
	pWeaponInfo->eProjectile = ARMY_GROUND_MISSILE;
}

///========================================================================
//	Function:		AiDfConeSpread()
//
//	Description:
//		acquire the Cone Of Damage attributes for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfConeSpread( int type )
{
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command CONE:\n" );
#endif

	// access the active pointer
	pWeaponInfo = (AI_WTBL*)AIactivePtr;

	// assign the projectile type
	pWeaponInfo->eProjectile = ARMY_CONE;
}

///========================================================================
//	Function:		AiDfAreaBurst()
//
//	Description:
//		acquire the Area Of Damage attributes for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfAreaBurst( int type )
{
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command AREA:\n" );
#endif

	// access the active pointer
	pWeaponInfo = (AI_WTBL*)AIactivePtr;

	// assign the projectile type
	pWeaponInfo->eProjectile = ARMY_AREA;
}

///========================================================================
//	Function:		AiDfMinimumRange()
//
//	Description:
//		acquire the Maximum Effective Range for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfMinimumRange( int type )
{
	int			nMinimumRange;
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command MINIMUM_RANGE: " );
#endif

	// acquire the minimum range for this weapon type
	if ( AiAcquireNumber( &nMinimumRange ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nMinimumRange );
#endif

		// access the active pointer
		pWeaponInfo = (AI_WTBL*)AIactivePtr;

		// load the minimum range value
		pWeaponInfo->range.nMinRange = nMinimumRange;
	}
}

///========================================================================
//	Function:		AiDfMaximumRange()
//
//	Description:
//		acquire the Maximum Effective Range for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfMaximumRange( int type )
{
	int			nMaximumRange;
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
 	TRACE( "command MAXIMUM_RANGE: " );
#endif

	// acquire the maximum range for this unit type
	if ( AiAcquireNumber( &nMaximumRange ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nMaximumRange );
#endif

		// access the active pointer
		pWeaponInfo = (AI_WTBL*)AIactivePtr;

		// load the maximum range value
		pWeaponInfo->range.nMaxRange = nMaximumRange;
	}
}

///========================================================================
//	Function:		AiDfVelocity()
//
//	Description:
//		acquire the velocity for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfVelocity( int type )
{
	int			nVelocity;
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
 	TRACE( "command VELOCITY: " );
#endif

	// acquire the maximum range for this unit type
	if ( AiAcquireNumber( &nVelocity ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nVelocity );
#endif

		// access the active pointer
		pWeaponInfo = (AI_WTBL*)AIactivePtr;

		// load the maximum range value
		pWeaponInfo->velocity.nVelocity = nVelocity;
	}
}

///========================================================================
//	Function:		AiDfZVelocity()
//
//	Description:
//		acquire the velocity for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfZVelocity( int type )
{
	int			nZVelocity;
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
 	TRACE( "command ZVELOCITY: " );
#endif

	// acquire the maximum range for this unit type
	if ( AiAcquireNumber( &nZVelocity ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nZVelocity );
#endif

		// access the active pointer
		pWeaponInfo = (AI_WTBL*)AIactivePtr;

		// load the maximum range value
		pWeaponInfo->velocity.nZVelocity = nZVelocity;
	}
}

///========================================================================
//	Function:		AiDfCollisionDamage()
//
//	Description:
//		acquire the collision damage a vehicle takes.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfCollisionDamage( int type )
{
	int			nCollision;
	AI_VTBL*	pVehicleInfo;

#ifdef AI_DEBUG
 	TRACE( "command COLLISION: " );
#endif

	// acquire the collision damage for this vehicle
	if ( AiAcquireNumber( &nCollision ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nCollision );
#endif

		// access the active pointer
		pVehicleInfo = (AI_VTBL*)AIactivePtr;

		// load the collision damage value
		pVehicleInfo->nCollisionDamage = nCollision;
	}
}


///========================================================================
//	Function:		AiDfArmor()
//
//	Description:
//		acquire the Armor for a vehicle.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfArmor( int type )
{
	int			nArmor;
	AI_VTBL*	pVehicleInfo;

#ifdef AI_DEBUG
	TRACE( "command ARMOR: " );
#endif

	// access the active pointer
	pVehicleInfo = (AI_VTBL*)AIactivePtr;

	// acquire the collision damage for this vehicle
	if ( AiAcquireNumber( &nArmor ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nArmor );
#endif

		// access the active pointer
		pVehicleInfo = (AI_VTBL*)AIactivePtr;

		// load the collision damage value
		pVehicleInfo->nArmor = nArmor;
	}
}


///========================================================================
//	Function:		AiDfPercentageDecreaseRate()
//
//	Description:
//		acquire the range Percentage Decrease Rate for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfPercentageDecreaseRate( int type )
{
	int			nPercentDecreaseRate;
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command PERCENTAGE_DECREASE_RATE: " );
#endif

	// acquire the percentage decrease rate for a weapon
	if ( AiAcquireNumber( &nPercentDecreaseRate ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nPercentDecreaseRate );
#endif

		// access the active pointer
		pWeaponInfo = (AI_WTBL*)AIactivePtr;

		// load the percentage decrease rate value
		pWeaponInfo->range.nPercentDecreaseRate = nPercentDecreaseRate;
	}
}

///========================================================================
//	Function:		AiDfDamage()
//
//	Description:
//		acquire the Inflicted Damage attribute for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfDamage( int type )
{
	int			nDamage;
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command DAMAGE: " );
#endif

	// acquire the inflicted damage for a weapon
	if ( AiAcquireNumber( &nDamage ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nDamage );
#endif

		// access the active pointer
		pWeaponInfo = (AI_WTBL*)AIactivePtr;

		// load the inflicted damage value
		pWeaponInfo->damage.nDamage = nDamage;
	}
}

///========================================================================
//	Function:		AiDfDamageDecreaseRate()
//
//	Description:
//		acquire the Damge Decrease Rate for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfDamageDecreaseRate( int type )
{
	int			nDamageDecreaseRate;
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command DAMAGE_DECREASE_RATE: " );
#endif

	// acquire the inflicted damage for a weapon
	if ( AiAcquireNumber( &nDamageDecreaseRate ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nDamageDecreaseRate );
#endif

		// access the active pointer
		pWeaponInfo = (AI_WTBL*)AIactivePtr;

		// load the inflicted damage value
		pWeaponInfo->damage.nDamageDecreaseRate = nDamageDecreaseRate;
	}
}

///========================================================================
//	Function:		AiDfDrift()
//
//	Description:
//		acquire the Drift factor attributes for a weapon.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfDrift( int type )
{
	int			nDrift;
	AI_WTBL*	pWeaponInfo;

#ifdef AI_DEBUG
	TRACE( "command DRIFT: " );
#endif

	// acquire the maximum drift value for this weapon type
	if ( AiAcquireNumber( &nDrift ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d\n", nDrift );
#endif

		// access the active pointer
		pWeaponInfo = (AI_WTBL*)AIactivePtr;

		// load nDrift value
		pWeaponInfo->range.nDrift = nDrift;
	}
}

///========================================================================
//	Function:		AiDfAccel()
//
//	Description:
//		acquire the acceleration attributes for a vehicle.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfAccel( int type )
{
	int			index;
	int			nCoefficient;
	AI_VTBL*	pVehicleInfo;

#ifdef AI_DEBUG
	TRACE( "command ACCEL: " );
#endif

	// access the active pointer. Check the context to see who is acquiring the info
	if ( AIcontext == AI_VEHICLE_CONTEXT )
		pVehicleInfo = (AI_VTBL*)AIactivePtr;
	else
		ASSERT(0);

	// acquire the forward, reverse, and decceleration speeds
	for ( index=0; index<3; ++index )
	{
		// acquire a speed value
		if ( AiAcquireNumber( &nCoefficient ) )
		{
#ifdef AI_DEBUG
			TRACE( "%d  ", nCoefficient );
#endif

			switch( index )
			{
			case ACCEL_FORWARD:
				// load the forward acceleration value
				pVehicleInfo->accel.nForward = nCoefficient;
				break;
			case ACCEL_REVERSE:
				// load the forward acceleration value
				pVehicleInfo->accel.nReverse = nCoefficient;
				break;
			case ACCEL_DECCEL:
				// load the forward acceleration value
				pVehicleInfo->accel.nDeccel = nCoefficient;
				break;
			}
		}
	}
#ifdef AI_DEBUG
	TRACE( "\n" );
#endif

}

///========================================================================
//	Function:		AiDfTarget()
//
//	Description:
//		acquire the target attacker values.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfTarget( int type )
{
	int			nTargetMin;
	int			nTargetMax;
	void*		pObjectInfo;

#ifdef AI_DEBUG
	TRACE( "command TARGET: " );
#endif

	// acquire the minimum number of attackers necessary to acquire this
	// object as a target
	pObjectInfo = AIactivePtr;
	if ( AiAcquireNumber( &nTargetMin ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d ", nTargetMin );
#endif
	}
	else
		return;

	if ( AiAcquireNumber( &nTargetMax ) )
	{
#ifdef AI_DEBUG
		TRACE( "%d ", nTargetMax );
#endif
	}
	else
		return;

	// check the context to see who is acuiring this info
	switch( AIcontext )
	{
	case AI_UNIT_CONTEXT:
		// access the active pointer
		((AI_UTBL*)pObjectInfo)->targeting.nMinAttackLevel = nTargetMin;
		((AI_UTBL*)pObjectInfo)->targeting.nMaxAttackLevel = nTargetMax;
		break;
	case AI_VEHICLE_CONTEXT:
		// access the active pointer
		((AI_VTBL*)pObjectInfo)->targeting.nMinAttackLevel = nTargetMin;
		((AI_VTBL*)pObjectInfo)->targeting.nMaxAttackLevel = nTargetMax;
		break;
	case AI_ASSET_CONTEXT:
		// access the active pointer
		((AI_ATBL*)pObjectInfo)->targeting.nMinAttackLevel = nTargetMin;
		((AI_ATBL*)pObjectInfo)->targeting.nMaxAttackLevel = nTargetMax;
		break;
	default:
		ASSERT(0);
	}
#ifdef AI_DEBUG
	TRACE( "\n" );
#endif
}

///========================================================================
//	Function:		AiDfTerrain()
//	Description:	acquire the terrain movement rate for TERRAIN.
///========================================================================

void	AiDfTerrain( int type )
{
	AIactivePtr = (void*)&(AIinfo.terrainTables[ type - TERRAIN_ID_BASE ]);

	// set the AI context for later commands
	AIcontext = AI_TERRAIN_CONTEXT;

	// now go read in the values for this terrain
	AiDfGround();
}

///========================================================================
//	Function:		AiDfRock()
//	Description:	acquire the part count for a  category object.
///========================================================================

void			AiDfObject( int type )
{
	// set the AI context for later commands
	AIcontext     = AI_OBJS_CONTEXT;
	AIpartContext = type - OBJS_ID_BASE;
	AiDfObjCategories();
}


///========================================================================
//	Function:		AiDfGround()
//
//	Description:
//		acquire the terrain attributes for all ground vehicles and humans, including the commander.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfGround(  )
{
	int			index;
	int			nTerrain;
	AI_GTBL*	pTerrainInfo;

#ifdef AI_DEBUG
	TRACE( "command SPEED: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	if ( AIcontext == AI_TERRAIN_CONTEXT )
		pTerrainInfo = (AI_GTBL*)AIactivePtr;
	else
		ASSERT(0);

	// acquire the vehicle and human movement rate values
	for ( index=AI_TANK_TERRAIN; index<=AI_HUMAN_TERRAIN; ++index )
	{
		// acquire a speed value
		if ( AiAcquireNumber( &nTerrain ) )
		{
			switch( index )
			{
			case AI_TANK_TERRAIN:		// TANK TERRAIN RATE
				pTerrainInfo->nTank = nTerrain;
#ifdef AI_DEBUG
				TRACE( "Tank %d  ", nTerrain );
#endif
				break;
			case AI_HALFTRACK_TERRAIN:	// HALFTRACK TERRAIN RATE
				pTerrainInfo->nHalfTrack = nTerrain;
#ifdef AI_DEBUG
				TRACE( "HalfTrack %d  ", nTerrain );
#endif
				break;
			case AI_JEEP_TERRAIN:		// JEEP TERRAIN RATE
				pTerrainInfo->nJeep = nTerrain;
#ifdef AI_DEBUG
				TRACE( "Jeep %d  ", nTerrain );
#endif
				break;
			case AI_HUMAN_TERRAIN:		// HUMAN TERRAIN RATE
				pTerrainInfo->nHuman = nTerrain;
#ifdef AI_DEBUG
				TRACE( "Human %d  ", nTerrain );
#endif
				break;
			}
		}
	}
#ifdef AI_DEBUG
	TRACE( "\n" );
#endif

}


#if 0
///========================================================================
//	Function:		AiDfObjIndividuals()
//
//	Description:
//		acquire the object and part count values.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfObjIndividuals( int type )
{
	int			index=0;
	int			nNumber;
	int			nPart;
	BOOL		bFound;
	AI_ITBL*	pObjsInfo;

	return;

	AIactivePtr = (void*)AIinfo.objIndivTables;

	if ( AIiObjsCount >= AI_MAX_OBJS_SIZE )	{
		Error( "AI objects table size exceeded (%d)\n", AI_MAX_OBJS_SIZE );
		return;
	}

	// keep loading object number and part counts until another
	// category is encountered
//	while( AiAcquireNumber( &nNumber ) )
	do
	{
#ifdef AI_DEBUG
		TRACE( "%d   ", nNumber );
#endif

		// load the numerical value
		if ( !index )
		{
			// if object number is 0, this is a category wide value
			if (nNumber == 0)
				break;

			// access the active pointer
			pObjsInfo = (AI_ITBL*)AIactivePtr;

			// first check to see if this object has already been mentioned
			bFound = FALSE;
			nPart  = 0;
			while( (nPart < AIiObjsCount) && !bFound )
			{
				// compare the category and object values
				if ( (pObjsInfo->nCategoryID == AIpartContext) && (pObjsInfo->nObjectID == nNumber) )
					bFound = TRUE;
				else
				{
					++pObjsInfo;
					++nPart;
				}
			}

			// info pointer is either pointing to the already load object or the new location
			pObjsInfo->nCategoryID = AIpartContext;
			pObjsInfo->nObjectID  = nNumber;

			// if this was a new object we need to up the part count
			if ( !bFound )
			{
				++AIiObjsCount;
				TRACE("HEY HEY HEY incremented AIiObjsCount\n");
			}

			// set index to the part count
			++index;
		}
		else
		{
			// load in the part count
			pObjsInfo->nPartCount = nNumber;

			// acquire & load in the hit point value
			if ( AiAcquireNumber( &nNumber ) )
				pObjsInfo->nHitPoints = nNumber;

			// set index to the object number
			index = 0;
		}
	}
	while( AiAcquireNumber( &nNumber ) );

#ifdef AI_DEBUG
	TRACE( "\n" );
#endif
}
#endif

///========================================================================
//	Function:		AiDfObjCategories()
//
//	Description:
//		acquire the object and part count values.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfObjIndividual( int nNumber )
{
	int		nDamageLevel;
	int		i;
	AI_ITBL* pIndivInfo;

	if( !AiAcquireNumber( &nDamageLevel ) )
	{
		TRACE( "Error in aai file: damage level missing.\n" );
		return;
	}
	nDamageLevel = nDamageLevel - 1;
	pIndivInfo = NULL;

	//first check to see if we already have an entry for this sucker
	for( i = 0; i < AIiObjsCount; i++ )
	{
		if( (AIinfo.objIndivTables[i].nCategoryID == AIpartContext) &&  //compare category
			(AIinfo.objIndivTables[i].nObjectID == nNumber) &&			//compare number
			(AIinfo.objIndivTables[i].nDamageLevel == nDamageLevel) )
		{
			pIndivInfo = &AIinfo.objIndivTables[i];
			break;
		}
	}

	//setup a new entry if not found
	if( !pIndivInfo )
	{
		if( AIiObjsCount >= AI_MAX_OBJS_SIZE )
		{
			TRACE( "Overflowed aai objects buffer\n" );
			return;
		}
		pIndivInfo = &AIinfo.objIndivTables[AIiObjsCount++];
		pIndivInfo->nCategoryID = AIpartContext;
		pIndivInfo->nObjectID = nNumber;
		pIndivInfo->nDamageLevel = nDamageLevel;
	}

	//field 4: # of parts
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pIndivInfo->nPartCount = nNumber;


	//field 5: layer
	if( !AiAcquireNumber( &nNumber ) )
		return;
	if( (nNumber < 0) || (nNumber > 3) )
	{
		TRACE( "Illegal layer entry.\n" );
	}
	pIndivInfo->nLayer = nNumber;

	//field 6: hit points
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pIndivInfo->nHitPoints = nNumber;

	//field 7: height
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pIndivInfo->nHeight = nNumber;

	//field 8: movement
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pIndivInfo->nMovement = nNumber;

	//field 9: visibility
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pIndivInfo->nVisibility = nNumber;

	//field 10: permeability
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pIndivInfo->nPermeability = nNumber;

	//field 11: armor
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pIndivInfo->nArmor = nNumber;

	//field 12: amount of damage it does when mvmt layer changes at last level
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pIndivInfo->nCrushDamage = nNumber;

#ifdef AI_DEBUG
	TRACE("\n");
#endif

	return;
}


void AiDfObjCategories( void )
{
	int			i, index=0;
	int			nNumber, nDamageLevel;
	AI_ITBL*	pObjsInfo;

	// do the same for specific object
	// set the info pointer to the Obj category entry
	// and read in the values for this object category
	AIactivePtr = (void*)AIinfo.objTables;

	// Acquire the object number
	if( !AiAcquireNumber( &nNumber ) )
		return;
	if( nNumber != 0 )
	{
		AiDfObjIndividual( nNumber );
		return;
	}

	if( !AiAcquireNumber( &nDamageLevel ) )
	{
		TRACE( "Error in aai file: damage level missing.\n" );
		return;
	}
	nDamageLevel = nDamageLevel - 1;

	//first check to see if we already have an entry for this sucker
	pObjsInfo = NULL;

	for( i = 0; i < AIobjsCount; i++ )
	{
		if( (AIinfo.objTables[i].nCategoryID == AIpartContext) &&  //compare category
			(AIinfo.objTables[i].nDamageLevel == nDamageLevel) )
		{
			pObjsInfo = &AIinfo.objTables[AIobjsCount];
			break;
		}
	}

	//setup a new entry if not found
	if( !pObjsInfo )
	{
		if( AIobjsCount >= AI_MAX_CATEGORY_SIZE )
		{
			TRACE( "Overflowed aai objects category buffer\n" );
			return;
		}
		pObjsInfo = &AIinfo.objTables[AIobjsCount++];
		pObjsInfo->nCategoryID = AIpartContext;
		pObjsInfo->nDamageLevel = nDamageLevel;
	}

	pObjsInfo->nObjectID = 0;

	//field 4: # of parts - don't store
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pObjsInfo->nPartCount = 1;

	//field 5: layer
	if( !AiAcquireNumber( &nNumber ) )
		return;
	if( (nNumber < 0) || (nNumber > 3) )
	{
		TRACE( "Illegal layer entry.\n" );
	}
	pObjsInfo->nLayer = nNumber;

	//field 6: hit points
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pObjsInfo->nHitPoints = nNumber;

	//field 7: height
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pObjsInfo->nHeight = nNumber;

	//field 8: movement
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pObjsInfo->nMovement = nNumber;

	//field 9: visibility
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pObjsInfo->nVisibility = nNumber;

	//field 10: permeability
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pObjsInfo->nPermeability = nNumber;

	//field 11: armor
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pObjsInfo->nArmor = nNumber;

	//field 12: crushdamage
	if( !AiAcquireNumber( &nNumber ) )
		return;
	pObjsInfo->nCrushDamage = nNumber;
	
#ifdef AI_DEBUG
	TRACE("\n");
#endif

	return;
}

///========================================================================
//	Function:		AiDfUnitPower()
//
//	Description:
//		acquire average power of each unit type.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfUnitPower( int type )
{
	int			index;
	int			nMax;
	AI_UTBL*	pUnitInfo;

#ifdef AI_DEBUG
	TRACE( "command UNIT_POWER: " );
#endif

	// the data for this is sequential so set the active pointer to
	// the unit context

	// acquire the unit maximums
	for ( index=AI_RIFLE_UNIT; index<=AI_LAST_UNIT; ++index )
	{
		// acquire the unit table entry
		pUnitInfo = &(AIinfo.unitTables[ (index - UNIT_ID_BASE) ]);

		// acquire a max value
		if ( AiAcquireNumber( &nMax ) )
		{

#ifdef AI_DEBUG
			TRACE( "%d  ", nMax );
#endif
			// load the max
			pUnitInfo->nPowerUnits = nMax;
		}
	}

#ifdef AI_DEBUG
	TRACE( "\n" );
#endif

}

///========================================================================
//	Function:		AiDfUnitComposition()
//
//	Description:
//		set the context to the unit type specified.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfUnitComposition( int type )
{
	AI_CMD_ENTRY*	pCommand;
	int				id;

#ifdef AI_DEBUG
	TRACE( "command UNIT: " );
#endif

	// we need to acquire the unit name in order to determine which unit
	// table entry to make active
	pCommand = AiGetCommand();

	// see if we found the command
	if ( pCommand )
	{
		// make sure that this is a unit type
		id = pCommand->nCmdID;
		if ( ( id >= AI_FIRST_UNIT ) && ( id <= AI_LAST_UNIT ) )
		{
#ifdef AI_DEBUG
			TRACE( "%s",  pCommand->pCmdName );
#endif
			// set the context and the active pointer
			AIcontext   = AI_UNIT_CONTEXT;
			AIactivePtr = (void*)&(AIinfo.unitTables[ (id - UNIT_ID_BASE) ]);
		}
	}

#ifdef AI_DEBUG
	TRACE( "\n" );
#endif
}

///========================================================================
//	Function:		AiDfNameComposition()
//
//	Description:
//		acquire the name of the active instance of a unit type.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfNameComposition( int type )
{
	AI_COMP*	pCompInfo;
	char*		pNamePtr;
	int			len;

	AI_UTBL*	pUnitInfo;
    pUnitInfo = (AI_UTBL*)AIactivePtr;
    AIactivePtr = (void*)&(pUnitInfo->comp);

#ifdef AI_DEBUG
	TRACE( "command NAME: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	if ( AIcontext == AI_UNIT_CONTEXT )
		pCompInfo = (AI_COMP*)AIactivePtr;
	else
		ASSERT(0);

    pNamePtr = pCompInfo->pNameShort;
    // acquire the name of the active instance of a unit type
    len = AiAcquireString( pNamePtr, AI_MAX_NAME-1 );
    if ( len <= 0 )
        strcpy( pNamePtr, "No Unit" );
}

///========================================================================
//	Function:		AiDfComposition()
//
//	Description:
//		acquire the active units composition values.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfComposition( int type )
{
	char		command[132];
	int			index;
	AI_COMP*	pCompInfo;

#ifdef AI_DEBUG
	TRACE( "command COMPOSITION: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	if ( AIcontext == AI_UNIT_CONTEXT )
		pCompInfo = (AI_COMP*)AIactivePtr;
	else
		ASSERT(0);

	// clear the composition
	for( index=0; index<AI_MAX_COMP_ENTRIES; ++index )
		pCompInfo->composition[ index ] = 0;

	// acquire the composition of the special and rifle men troopers
	index       = 0;
	while ( (AiAcquireToken( command ) == TRUE) && (index < AI_MAX_COMP_ENTRIES) )
	{
#ifdef AI_DEBUG
		TRACE( "%c  ", *command );
#endif
		if (*command == AI_SPECIAL_TROOPER )
			pCompInfo->composition[ index ] = 0;
		else
		if (*command == AI_RIFLE_TROOPER )
			pCompInfo->composition[ index ] = 1;
		else
		if (*command == AI_special_TROOPER )
			pCompInfo->composition[ index ] = 0;
		else
		if (*command == AI_rifle_TROOPER )
			pCompInfo->composition[ index ] = 1;

		// advance to the next item
		++index;
#ifdef ONETROOPER
		break;
#endif
	}

#ifdef AI_DEBUG
	TRACE( "\n" );
#endif

}

///========================================================================
//	Function:		AiDfBaseDoor()
//
//	Description:
//		acquire the terrain attributes for all ground vehicles and humans, including the commander.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDfBaseDoor( int type )
{
	int			index;
	int			nNumber;
	AI_BTBL*	pBaseInfo;

#ifdef AI_DEBUG
	TRACE( "command BASEDOOR: " );
#endif

	// start by acquiring the base index
	if ( AiAcquireNumber( &nNumber ) )
	{
		// now acquire the appropriate base
		if ( nNumber < AI_MAX_BASES )
		{
			pBaseInfo = &(AIinfo.baseTables[ nNumber ]);

			// acquire the base data
			for ( index=0; index<=3; ++index )
			{
				// acquire a base value
				if ( AiAcquireNumber( &nNumber ) )
				{
					switch( index )
					{
					case 0:		// base X Offset
						pBaseInfo->nXoffset = nNumber;
#ifdef AI_DEBUG
						TRACE( "( %d, ", nNumber );
#endif
						break;
					case 1:	// base Y Offset
						pBaseInfo->nYoffset = nNumber;
#ifdef AI_DEBUG
						TRACE( "%d )  ", nNumber );
#endif
						break;
					case 2:		// facing
						pBaseInfo->nFacing = nNumber;
#ifdef AI_DEBUG
						TRACE( "Facing %d", nNumber );
#endif
						break;
					}
				}
			}
		}
	}
#ifdef AI_DEBUG
	TRACE( "\n" );
#endif
}

///========================================================================
//	Function:		MapCampaign()
//
//	Description:
//		acquire the Campaign attributes.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	MapCampaign( int type )
{
	CAMPAIGNREF*	pCampaignRef;
	int				nNumber;

#ifdef CPN_DEBUG
	TRACE( "command CAMPAIGN: " );
#endif

	// make sure we have enough room
	if ( g_NumberCampaigns > AI_MAX_CAMPAIGNS )
	{
		TRACE( "ERROR: number of campaigns max exceeded (%d) [%s:%d]\n",
			AI_MAX_CAMPAIGNS, __FILE__, __LINE__ );
		ASSERT(0);
	}

	// allocate a map campaign structure
	pCampaignRef = (CAMPAIGNREF*)malloc( sizeof( CAMPAIGNREF ) );
	if ( !pCampaignRef )
	{
		TRACE( "ERROR: failed to allocate Campaign Reference [%s:%d]\n",
			__FILE__, __LINE__ );
		ASSERT(0);
	}
	ZeroMemory( pCampaignRef, sizeof( CAMPAIGNREF ) );

	// start by acquiring the campaign ID
	if ( AiAcquireNumber( &nNumber ) )
	{
#ifdef CPN_DEBUG
		TRACE( "%d\n", nNumber );
#endif
		// now assign the campaign
		pCampaignRef->nCampaignID        = nNumber;
		g_Campaigns[ g_NumberCampaigns ] = pCampaignRef;
		g_pCampaign                      = pCampaignRef;
		++g_NumberCampaigns;

		// set the context
		AIcontext   = AI_CAMPAIGN_CONTEXT;
		AIactivePtr = (void*)pCampaignRef;

		// now acquire the Loading background image
		if ( AiAcquireToken( pCampaignRef->pLoadBkg ) == FALSE )
		{
			// error: failed to acquire filename
			TRACE( "ERROR: failed to acquire campaign load bkg filename [%s:%d]\n",
				__FILE__, __LINE__ );
			ASSERT(0);
		}
		else
		{
#ifdef CPN_DEBUG
			TRACE( "%s ", pName );
#endif
			// now acquire the mission select background image
			if ( AiAcquireToken( pCampaignRef->pCampaignBkg ) == FALSE )
			{
				// error: failed to acquire filename
				TRACE( "ERROR: failed to acquire campaign mission select bkg filename [%s:%d]\n",
					__FILE__, __LINE__ );
				ASSERT(0);
			}
#ifdef CPN_DEBUG
			else
			{
				TRACE( "%s\n", pName );
			}
#endif
		}
	}
	else
	{
		TRACE( "ERROR: failed to acquire Campaign ID [%s:%d]\n",
			__FILE__, __LINE__ );

		// free the campaign data
		free( pCampaignRef );

		ASSERT(0);
	}
}

///========================================================================
//	Function:		MapScenario()
//
//	Description:
//		acquire the scenario attributes.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	MapScenario( int type )
{
	SCENARIOREF*	pScenarioRef;
	CAMPAIGNREF*	pCampaignRef;
	int				nNumber;

#ifdef CPN_DEBUG
	TRACE( "command SCENARIO: " );
#endif

	// acquire the campaigns
	pCampaignRef = g_pCampaign;

	// acquire a scenario reference
	if ( pCampaignRef->nNumberScenarios >= AI_MAX_SCENARIOS )
	{
		// error: to many scenarios
		TRACE( "ERROR: number of scenarios for this campaign exceeded (%d) [%s:%d]\n",
			AI_MAX_SCENARIOS, __FILE__, __LINE__ );
		ASSERT(0);
	}
	pScenarioRef = &(pCampaignRef->pScenarios[ pCampaignRef->nNumberScenarios ]);

	// start by acquiring the scenario ID
	if ( AiAcquireNumber( &nNumber ) )
	{
#ifdef CPN_DEBUG
		TRACE( "%d\n", nNumber );
#endif
		// now assign the scenario
		pScenarioRef->nScenarioID = nNumber;
		++(pCampaignRef->nNumberScenarios);
		g_NumberScenarios = pCampaignRef->nNumberScenarios;

		// set the context
		AIcontext   = AI_SCENARIO_CONTEXT;
		AIactivePtr = (void*)pScenarioRef;
	}
	else
	{
		TRACE( "ERROR: failed to acquire Scenario ID [%s:%d]\n",
			__FILE__, __LINE__ );
		ASSERT(0);
	}
}

///========================================================================
//	Function:		MapMission()
//
//	Description:
//		acquire the mission attributes.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	MapMission( int type )
{
	MISSIONREF*		pMissionRef;
	SCENARIOREF*	pScenarioRef;
	CAMPAIGNREF*	pCampaignRef;
	int				nNumber;

#ifdef CPN_DEBUG
	TRACE( "command MISSION: " );
#endif

	// set the context
	pCampaignRef = g_pCampaign;
	pScenarioRef = &(pCampaignRef->pScenarios[ pCampaignRef->nNumberScenarios - 1 ]);
	pMissionRef  = &(pScenarioRef->pMissions[ pScenarioRef->nNumberMissions ]);

	// acquire the scenario reference
	if ( pScenarioRef->nNumberMissions >= AI_MAX_MISSIONS )
	{
		// error: to many missions
		TRACE( "ERROR: number of missions for this scenario exceeded (%d) [%s:%d]\n",
			AI_MAX_MISSIONS, __FILE__, __LINE__ );
		ASSERT(0);
	}

	// start by acquiring the scenario ID
	if ( AiAcquireNumber( &nNumber ) )
	{
#ifdef CPN_DEBUG
		TRACE( "%d ", nNumber );
#endif
		// now assign the mission
		pMissionRef->nMissionID = nNumber;
		++(pScenarioRef->nNumberMissions);

		// now acquire the map filename
		if ( AiAcquireToken( pMissionRef->pBriefFile ) == FALSE )
		{
			// error: failed to acquire the mission message
			TRACE( "ERROR: failed to acquire Mission Briefing filename [%s:%d]\n",
				__FILE__, __LINE__ );
		}
	#ifdef CPN_DEBUG
		else
		{
			TRACE( "\"%s\"\n", pMissionRef->pBriefFile );
		}
	#endif

		// set the context
		AIcontext   = AI_MISSION_CONTEXT;
		AIactivePtr = (void*)pMissionRef;
	}
	else
	{
		TRACE( "ERROR: failed to acquire Scenario ID [%s:%d]\n",
			__FILE__, __LINE__ );
	}
}

///========================================================================
//	Function:		MapTitle()
//
//	Description:
//		acquire the campaign/scenario/mission title.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void			MapTitle( int type )
{
	int				len;
	CAMPAIGNREF*	pCampaign = NULL;
	SCENARIOREF*	pScenario = NULL;
	MISSIONREF*		pMission  = NULL;
	char*			pName     = NULL;

#ifdef CPN_DEBUG
	TRACE( "command TITLE: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	switch ( AIcontext )
	{
	case AI_CAMPAIGN_CONTEXT:
		pCampaign = (CAMPAIGNREF*)AIactivePtr;
		pName     = pCampaign->pCampaignName;
		break;
	case AI_SCENARIO_CONTEXT:
		pScenario = (SCENARIOREF*)AIactivePtr;
		pName     = pScenario->pScenarioName;
		break;
	case AI_MISSION_CONTEXT:
		pMission = (MISSIONREF*)AIactivePtr;
		pName     = pMission->pMissionName;
		break;
	default:
		TRACE( "ERROR: illegal context (%d) [%s:%d]\n",
				AIcontext, __FILE__, __LINE__ );
		ASSERT(0);
	}

	// now acquire the map filename
	len = AiAcquireString( pName, AI_MAX_STRING );
	if (  len == -1 )
	{
		// error: failed to acquire filename
		TRACE( "ERROR: failed to acquire filename [%s:%d]\n",
			__FILE__, __LINE__ );
		ASSERT(0);
	}
#ifdef CPN_DEBUG
	else
	{
		TRACE( "\"%s\"\n", pName );
	}
#endif
}

///========================================================================
//	Function:		MapVisibility()
//
//	Description:
//		acquire the campaign/scenario/mission visibility.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void			MapVisibility( int type )
{
	CAMPAIGNREF*	pCampaign = NULL;
	SCENARIOREF*	pScenario = NULL;
	MISSIONREF*		pMission  = NULL;
	BOOL*			pVisible  = NULL;

#ifdef CPN_DEBUG
	TRACE( "command VISIBILITY: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	switch ( AIcontext )
	{
	case AI_CAMPAIGN_CONTEXT:
		pCampaign = (CAMPAIGNREF*)AIactivePtr;
		pVisible  = &(pCampaign->bVisible);
		break;
	case AI_SCENARIO_CONTEXT:
		pScenario = (SCENARIOREF*)AIactivePtr;
		pVisible  = &(pScenario->bVisible);
		break;
	case AI_MISSION_CONTEXT:
		pMission = (MISSIONREF*)AIactivePtr;
		pVisible = &(pMission->bVisible);
		break;
	default:
		TRACE( "ERROR: illegal context (%d) [%s:%d]\n",
				AIcontext, __FILE__, __LINE__ );
		ASSERT(0);
	}

	// acquire the campaign visibility
	if ( AiAcquireNumber( pVisible ) == FALSE )
	{
		// error: failed to acquire filename
		TRACE( "ERROR: failed to acquire visibility [%s:%d]\n",
			__FILE__, __LINE__ );
		ASSERT(0);
	}
#ifdef CPN_DEBUG
	else
	{
		if ( (*pVisible & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
			TRACE( "NEXT " );
		if ( (*pVisible & STAT_PLAYED_FLAG) == STAT_PLAYED_FLAG )
			TRACE( "PLAYED " );
		if ( (*pVisible & STAT_VISIBLE_FLAG) == STAT_VISIBLE_FLAG )
			TRACE( "VISIBLE " );
		if ( *pVisible == STAT_DISABLED_FLAG )
			TRACE( "DISABLED " );
		TRACE( "\n" );
	}
#endif
}

///========================================================================
//	Function:		MapMessage()
//
//	Description:
//		acquire the mission attributes.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void			MapMessage( int type )
{
	char			pMusicIDname[AI_MAX_STRING+1];
	char*			pMessage  = NULL;
	CAMPAIGNREF*	pCampaign = NULL;
	SCENARIOREF*	pScenario = NULL;
	MISSIONREF*		pMission  = NULL;
	int				which = 0;

#ifdef CPN_DEBUG
	TRACE( "command MESSAGE: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	if ( AIcontext == AI_MISSION_CONTEXT )
	{
		pMission = (MISSIONREF*)AIactivePtr;

		for (int i=0; i<MISSION_VOICES; i++)
			pMission->nMissionVoiceID[i] = SND_NULL_SND_ID;	

		// now acquire the mission statement music ID name
		if ( AiAcquireToken( pMusicIDname ) == TRUE )
		{
			pMission->nMissionVoiceID[which++] = audioFindIDbyName( pMusicIDname );

			// now acquire the mission statement voice ID name
			while ( AiAcquireToken( pMusicIDname ) )
			{
				pMission->nMissionVoiceID[which++] = audioFindIDbyName( pMusicIDname );
				if (which >= MISSION_VOICES)
					break;
			}
		}
	}
#ifdef CPN_DEBUG
	else
	{
		TRACE( "ERROR: illegal context (%d) expected MISSION context [%s:%d]\n",
			AIcontext, __FILE__, __LINE__ );
		ASSERT(0);
	}
#endif
}

///========================================================================
//	Function:		MapFile()
//
//	Description:
//		acquire the mission .AMM map filename.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void			MapFile( int type )
{
	MISSIONREF*		pMission  = NULL;
	char*			pMapFile  = NULL;

#ifdef CPN_DEBUG
	TRACE( "command MAPFILE: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	if ( AIcontext == AI_MISSION_CONTEXT )
	{
		pMission = (MISSIONREF*)AIactivePtr;
		pMapFile = pMission->pFileName;

		// now acquire the map filename
		if ( AiAcquireToken( pMapFile ) == FALSE )
		{
			// error: failed to acquire the mission message
			TRACE( "ERROR: failed to acquire Mission .AMM filename [%s:%d]\n",
				__FILE__, __LINE__);
		}
	#ifdef CPN_DEBUG
		else
		{
			TRACE( "\"%s\"\n", pMapFile );
		}
	#endif
	}
#ifdef CPN_DEBUG
	else
	{
		TRACE( "ERROR: illegal context (%d) expected MISSION context [%s:%d]\n",
			AIcontext, __FILE__, __LINE__ );
		ASSERT(0);
	}
#endif
}

///========================================================================
//	Function:		MapStratMap()
//
//	Description:
//		acquire the mission .BMP strategic map filename.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void			MapStratMap( int type )
{
	MISSIONREF*		pMission  = NULL;
	char*	pStratMap = NULL;

#ifdef CPN_DEBUG
	TRACE( "command STRATMAP: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	if ( AIcontext == AI_MISSION_CONTEXT )
	{
		pMission  = (MISSIONREF*)AIactivePtr;
		pStratMap = pMission->pStratFile;

		// now acquire the map filename
		if ( AiAcquireToken( pStratMap ) == FALSE )
		{
			// error: failed to acquire the mission message
			TRACE( "ERROR: failed to acquire Mission Map .BMP filename [%s:%d]\n",
				__FILE__, __LINE__ );
		}
	#ifdef CPN_DEBUG
		else
		{
			TRACE( "\"%s\"\n", pStratMap );
		}
	#endif
	}
#ifdef CPN_DEBUG
	else
	{
		TRACE( "ERROR: illegal context (%d) expected MISSION context [%s:%d]\n",
			AIcontext, __FILE__, __LINE__ );
		ASSERT(0);
	}
#endif
}

///========================================================================
//	Function:		MapMusic()
//
//	Description:
//		acquire the campaign/mission MUSIC filenames.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void			MapMusic( int type )
{
	char			pMusicIDname[AI_MAX_STRING+1];
	CAMPAIGNREF*	pCampaign  = NULL;
	MISSIONREF*		pMission   = NULL;
	ULONG*			pMusic0    = NULL;
	ULONG*			pMusic1    = NULL;
	ULONG*			pMusicID   = NULL;
	int				nFileCount = 0;
	int				nIndex     = 0;

	// access the active pointer. Check the context to see who is acuiring the info
	switch ( AIcontext )
	{
	case AI_CAMPAIGN_CONTEXT:
#ifdef CPN_DEBUG
	TRACE( "command MUSIC [campaign]: " );
#endif

		pCampaign  = (CAMPAIGNREF*)AIactivePtr;
		pMusic0    = &(pCampaign->nCampaignMusicID);
		nFileCount = 1;
		break;
	case AI_MISSION_CONTEXT:
#ifdef CPN_DEBUG
	TRACE( "command MUSIC [mission]: " );
#endif

		pMission   = (MISSIONREF*)AIactivePtr;
		pMusic0    = &(pMission->nMissionMusicID[0]);
		pMusic1    = &(pMission->nMissionMusicID[1]);
		nFileCount = 2;
		break;
	default:
#ifdef CPN_DEBUG
	TRACE( "command MUSIC [error]: " );
#endif

		TRACE( "ERROR: illegal context (%d) expected CAMPAIGN or MISSION context [%s:%d]\n",
			AIcontext, __FILE__, __LINE__ );
		ASSERT(0);
	}

	// access the active pointer. Check the context to see who is acuiring the info
	for( nIndex=0; nIndex<nFileCount; ++nIndex )
	{
		if ( nIndex == 0 )
			pMusicID = pMusic0;
		else
			pMusicID = pMusic1;

		// now acquire the music ID name
		if ( AiAcquireToken( pMusicIDname ) == FALSE )
		{
			// error: failed to acquire the music
			TRACE( "ERROR: failed to acquire Music ID name [%s:%d]\n",
				__FILE__, __LINE__ );
			ASSERT(0);
		}
		else
		{
			// convert the name to a proper AUDIO ID
			*pMusicID = audioFindIDbyName( pMusicIDname );

#ifdef CPN_DEBUG
			TRACE( "\"%s\" %ld ", pMusicIDname, *pMusicID );
#endif
		}
	}

#ifdef CPN_DEBUG
	TRACE( "\n" );
#endif
}

///========================================================================
//	Function:		MapAvi()
//
//	Description:
//		acquire the Scenario win/lose AVI filename.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void			MapAvi( int type )
{
	SCENARIOREF*	pScenario = NULL;
	char*			pAviFile  = NULL;
	int				nIndex    = 0;

#ifdef CPN_DEBUG
	TRACE( "command AVI: " );
#endif

	// access the active pointer. Check the context to see who is acuiring the info
	if ( AIcontext == AI_SCENARIO_CONTEXT )
	{
		pScenario = (SCENARIOREF*)AIactivePtr;

		// access the active pointer. Check the context to see who is acuiring the info
		for( nIndex=0; nIndex<4; ++nIndex )
		{
			if ( nIndex == 0 )	// AVI WIN
				pAviFile = pScenario->pScenarioWin;
			else				// AVI LOSe
				pAviFile = pScenario->pScenarioLose[ nIndex - 1 ];

			// now acquire the avi filename
			if ( AiAcquireToken( pAviFile ) == FALSE )
			{
				// error: failed to acquire the Scenario AVI
				TRACE( "ERROR: failed to acquire Scenario AVI filename [%s:%d]\n",
					__FILE__, __LINE__ );
				ASSERT(0);
			}
		#ifdef CPN_DEBUG
			else
			{
				TRACE( "\"%s\" ", pAviFile );
			}
		#endif
		}
#ifdef CPN_DEBUG
		TRACE( "\n" );
#endif
	}
#ifdef CPN_DEBUG
	else
	{
		TRACE( "ERROR: illegal context (%d) expected SCENARIO context [%s:%d]\n",
			AIcontext, __FILE__, __LINE__ );
		ASSERT(0);
	}
#endif
}

///========================================================================
//	Function:		MapKey()
//
//	Description:
//		acquire the mission KEY id.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void			MapKey( int type )
{
	MISSIONREF*		pMission   = NULL;
	int				nData;

	// access the active pointer. Check the context to see who is acuiring the info
	if ( AIcontext != AI_MISSION_CONTEXT )
	{
		TRACE( "ERROR: illegal context (%d) expected MISSION context [%s:%d]\n",
			AIcontext, __FILE__, __LINE__ );
		// return;
		ASSERT(0);
	}
	pMission   = (MISSIONREF*)AIactivePtr;

	// now acquire the Mission KEY
	if ( AiAcquireNumber( &nData ) == FALSE )
	{
		// error: failed to acquire the music
		TRACE( "ERROR: failed to acquire Mission KEY [%s:%d]\n",
			__FILE__, __LINE__ );
		// return;
		ASSERT(0);
	}
	else
		pMission->nMissionKey = nData;

#ifdef CPN_DEBUG
	TRACE( "\n" );
#endif
}

///========================================================================
//	Function:		AiGetCommand()
//
//	Description:
//		parse the input string for the next command.
//
//	Input:			none
//
//	Ouput:			pCmdPtr		pointer to commadn info found
//
///========================================================================

AI_CMD_ENTRY*	AiGetCommand( )
{
	AI_CMD_ENTRY*	pCmdPtr = NULL;
	char			command[132];
	int				index     = 0;
	int				lineCount = 0;
	BOOL			found     = FALSE;
	BOOL			endOfList = FALSE;
	BOOL			error     = FALSE;

	// strip all leading white space
	AItokenPtr = StripWhiteSpace( AItokenPtr );
	if ( (*AItokenPtr != '\n') && (*AItokenPtr != '\0') )
	{
		// now request the command name
		if ( AiAcquireToken( command ) == TRUE )
		{
			// determine which command it was
			if ( command[0] != '#' )						// comment
			{
				// now look through the command list for action
				found     = FALSE;
				endOfList = FALSE;
				index     = 0;
				while (!found && !endOfList)
				{
					if ( strcmp( AIcommandTable[index].pCmdName, command ) == 0 )
						found = TRUE;
					else
					if ( strcmp( AIcommandTable[index].pCmdName, "EOL" ) == 0 )
						endOfList = TRUE;
					else
						++index;
				}

				// see if we found the command
				if ( found )
				{
					// acquire the address of the entry found
					pCmdPtr = &(AIcommandTable[index]);
				}
			}
			else
			{
				pCmdPtr = &(AIcommandTable[0]);		// the comment command token
			}
		}
	}

	// return a pointer to the command table item matching the command
	return( pCmdPtr );
}

///========================================================================
//	Function:		AiAcquireToken()
//
//	Description:
//		parse the input string for the next token.
//
//	Input:			pToken			where to place the token found
//
//	Ouput:			TRUE			if successful, FALSE otherwise
//
///========================================================================

BOOL	AiAcquireToken( char* pToken )
{
	char*		pTokenStart;
	int			len;
	BOOL		found = FALSE;		// assume failure

	// strip all leading white space
	AItokenPtr = StripWhiteSpace( AItokenPtr );

	// setup token name pointers
	pTokenStart = AItokenPtr;

	// now read in the characters that make up the token
	pTokenStart = strtok( AItokenPtr, ",\n\t ;\0" );
	if ( pTokenStart != NULL )
	{
		// we found a token
		strcpy( pToken, pTokenStart );
		found = TRUE;

		// determine how far to advance the token stream pointer
		len = strlen(pTokenStart);

		// now advance the command pointer past the token and NULL
		AItokenPtr += len + 1;
	}
	else
		*pToken = '\0';

	return( found );
}

///========================================================================
//	Function:		AiAcquireNumber()
//
//	Description:
//		parse the input string for a numerical value.
//
//	Input:			none
//
//	Ouput:			TRUE			if successful, FALSE otherwise
//
///========================================================================

BOOL	AiAcquireNumber( int* pTheNumber )
{
	char*		pTokenStart;
	int			len;
	BOOL		found = FALSE;		// assume failure

	// strip all leading white space
	AItokenPtr = StripWhiteSpace( AItokenPtr );

	// setup token number pointers
	pTokenStart = AItokenPtr;

	// initialize the answer to zero just in case
	*pTheNumber = 0;

	// now read in the characters that make up the token
	pTokenStart = strtok( AItokenPtr, ",\n\t ;\0" );
	if ( pTokenStart != NULL )
	{
		switch( *pTokenStart )
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '-':
		case '+':
			// now read in the characters that make up the number
			if ( sscanf( pTokenStart, "%d", pTheNumber ) != EOF )
			{
				found = TRUE;		// got a number

				// determine how far to advance the token stream pointer
				len = strlen(pTokenStart);

				// now advance the command pointer past the token and NULL
				AItokenPtr += len + 1;
			}
			break;
		default:
			break;
		}
	}

	return( found );
}

///========================================================================
//	Function:		AiAcquireString()
//
//	Description:
//		acquire a quoted string, striping the quotes and NULL terminate.
//
//	Input:			none
//
//	Ouput:			len			size of the string acquired.
//
///========================================================================

int	AiAcquireString( char* pTheString, int nMaxSize )
{
	char*		pTokenStart;
	char*		pNextChar;
	int			len   = -1;

	// strip all leading white space
	AItokenPtr = StripWhiteSpace( AItokenPtr );

	// setup token number pointers
	pTokenStart = AItokenPtr;

	// initialize the answer to NULL just in case
	*pTheString = '\0';
	pNextChar   = pTheString;

	// now look for a double quote
	if ( *AItokenPtr == '\"' )
	{
		// advance past the double quote
		++AItokenPtr;

		// now read in the characters that make up the string token
		pTokenStart = strtok( AItokenPtr, "\"\n\0" );
		if ( pTokenStart != NULL )
		{
			// determine how far to advance the token stream pointer
			--nMaxSize;		// make room for the NULL terminator
			len = strlen(pTokenStart);
			if ( len > nMaxSize )
				len = nMaxSize;
			strncpy( pNextChar, pTokenStart, len );
			pNextChar += len;

			// NULL terminate this string
			*pNextChar = '\0';

			// now advance the command pointer past the token and NULL
			AItokenPtr += len + 1;
		}
	}

	return( len );
}

///========================================================================
//	Function:		AiLoadLine()
//
//	Description:
//		extract the next line of data from the input source.
//
//	Input:			none
//
//	Ouput:			TRUE		if a line of data was loaded, FALSE otherwise
//
///========================================================================

BOOL	AiLoadLine( )
{
	char*	pSrc;
	char*	pDst;
	BOOL	answer = FALSE;			// assume we failed to load a line

	// clear the command line and increment the line count
	memset( AIcommandLine, 0, 255 );
	++AIlineCount;

	// first see if we have a resource or a file
	if ( AIresourceHandle )			// we have a resource
	{
		// point to the current source and destination locations
		pSrc = AIresourcePtr;
		pDst = AIcommandLine;

		// now load up to an including a newline
		while ( (*pSrc != '\n') || (*pSrc != '\0') )
		{
			// copy the data from source to destination
			*pDst = *pSrc;

			// advance the source and destination
			++pDst;
			++pSrc;
		}

		// remember to insert the terminating character ( either '\n' or '\0' )
		*pDst = *pSrc;
		++pDst;
		++pSrc;

		// update the current location pointer
		AIresourcePtr = pSrc;
	}
	else							// we have a text file
	{
		// read in a line of data from the file
		if ( fgets( AIcommandLine, 255, AIfile ) == NULL )
		{
			// check to see what kind of error, if at all
			if ( !feof( AIfile ) )
			{
				// report an error of some sort
				TRACE("ERROR: file input failure: \"%s\". [%s:%d]\n\n", 
						AIfileName, __FILE__, __LINE__ );
			}

			// report that we failed to load a line of data
			answer = FALSE;
			goto exit;
		}
	}

	// set the initial current position pointer
	AItokenPtr = AIcommandLine;
#ifdef AI_DEBUG
	TRACE( "line #%3d: \"%s\"\n", AIlineCount, AItokenPtr );
#endif

	// if we made it here we were successful getting the line of data
	answer = TRUE;

exit:
	return( answer );
}

///========================================================================
//	Function:		AiFlushInput()
//
//	Description:
//		flush the input stream up to the newline or null.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiFlushInput( )
{
	if ( (*AItokenPtr != '\0') && ( *AItokenPtr != '\n' ) )
		*AItokenPtr = '\n';
}

///========================================================================
//	Function:		AiDumpCPN()
//
//	Description:
//		Dump the CAMPAIGNREF structure.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDumpCPN( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	int				nCampaign;
	int				nScenario;
	int				nMission;
	char*			pMissionStatement;

	for( nCampaign=0; nCampaign<g_NumberCampaigns; ++nCampaign )
	{
		pCampaign = g_Campaigns[ nCampaign ];
		TRACE( "CAMPAIGN:    %d, \"%s\"\n", pCampaign->nCampaignID, pCampaign->pCampaignName );
		TRACE( "   MUSIC:    %d, \"%s\"\n", pCampaign->nCampaignMusicID,
										   audioIDname( pCampaign->nCampaignMusicID ) );
		TRACE( "   VISIBLE:  %s\n", ((pCampaign->bVisible) ? "VISIBLE" : "DISABLED") );

		for( nScenario=0; nScenario<pCampaign->nNumberScenarios; ++nScenario )
		{
			pScenario = &(pCampaign->pScenarios[ nScenario ]);
			TRACE( "   SCENARIO:    %d, \"%s\"\n", pScenario->nScenarioID, pScenario->pScenarioName );
			TRACE( "     VISIBLE:   %s\n", ((pScenario->bVisible) ? "VISIBLE" : "DISABLED") );
			TRACE( "     AVI:       \"%s\", \"%s\", \"%s\", \"%s\"\n",
				pScenario->pScenarioWin,     pScenario->pScenarioLose[0],
				pScenario->pScenarioLose[1], pScenario->pScenarioLose[2]
				);
			for( nMission=0; nMission<pScenario->nNumberMissions; ++nMission )
			{
				pMission = &(pScenario->pMissions[ nMission ]);
				TRACE( "       MISSION:       %d, \"%s\"\n", pMission->nMissionID,
					pMission->pMissionName );
				TRACE( "       VISIBLILITY:   " );
				if ( (pMission->bVisible & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
					TRACE( "NEXT " );
				if ( (pMission->bVisible & STAT_PLAYED_FLAG) == STAT_PLAYED_FLAG )
					TRACE( "PLAYED " );
				if ( (pMission->bVisible & STAT_VISIBLE_FLAG) == STAT_VISIBLE_FLAG )
					TRACE( "VISIBLE " );
				if ( pMission->bVisible == STAT_DISABLED_FLAG )
					TRACE( "DISABLED " );
				TRACE("\n");
				TRACE( "          MAPS:       \"%s\", %s\n", pMission->pFileName,
					pMission->pStratFile);
				pMissionStatement = voiceFindText( pMission->nMissionVoiceID[0] );
				TRACE( "          STATEMENT:  \"%s\"\n", pMissionStatement );
				TRACE( "              VOICE:  %d, \"%s\"\n",
					pMission->nMissionVoiceID[0], audioIDname(pMission->nMissionVoiceID[0]) );
				TRACE( "          MUSIC:      %d, \"%s\", %d, \"%s\"\n",
					pMission->nMissionMusicID[0], audioIDname(pMission->nMissionMusicID[0]),
					pMission->nMissionMusicID[1], audioIDname(pMission->nMissionMusicID[1])
					);
			}
		}
	}
}

///========================================================================
//	Function:		AiDumpVisibility()
//
//	Description:
//		Dump the CAMPAIGNREF structure.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDumpVisibility( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	int				nCampaign;
	int				nScenario;
	int				nMission;

	for( nCampaign=0; nCampaign<g_NumberCampaigns; ++nCampaign )
	{
		pCampaign = g_Campaigns[ nCampaign ];
		TRACE( "CAMPAIGN:    %d, \"%s\"\n", pCampaign->nCampaignID, pCampaign->pCampaignName );
		TRACE( "   VISIBLE:  " );
		if ( (pCampaign->bVisible & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
			TRACE( "NEXT " );
		if ( (pCampaign->bVisible & STAT_PLAYED_FLAG) == STAT_PLAYED_FLAG )
			TRACE( "PLAYED " );
		if ( (pCampaign->bVisible & STAT_VISIBLE_FLAG) == STAT_VISIBLE_FLAG )
			TRACE( "VISIBLE " );
		if ( pCampaign->bVisible == STAT_DISABLED_FLAG )
			TRACE( "DISABLED " );
		TRACE( "\n" );

		for( nScenario=0; nScenario<pCampaign->nNumberScenarios; ++nScenario )
		{
			pScenario = &(pCampaign->pScenarios[ nScenario ]);
			TRACE( "   SCENARIO:    %d, \"%s\"\n", pScenario->nScenarioID, pScenario->pScenarioName );
			TRACE( "     VISIBLE:   " );
			if ( (pScenario->bVisible & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
				TRACE( "NEXT " );
			if ( (pScenario->bVisible & STAT_PLAYED_FLAG) == STAT_PLAYED_FLAG )
				TRACE( "PLAYED " );
			if ( (pScenario->bVisible & STAT_VISIBLE_FLAG) == STAT_VISIBLE_FLAG )
				TRACE( "VISIBLE " );
			if ( pScenario->bVisible == STAT_DISABLED_FLAG )
				TRACE( "DISABLED " );
			TRACE( "\n" );
			for( nMission=0; nMission<pScenario->nNumberMissions; ++nMission )
			{
				pMission = &(pScenario->pMissions[ nMission ]);
				TRACE( "       MISSION:       %d, \"%s\"\n", pMission->nMissionID,
					pMission->pMissionName );
				TRACE( "       VISIBLILITY:   " );
				if ( (pMission->bVisible & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
					TRACE( "NEXT " );
				if ( (pMission->bVisible & STAT_PLAYED_FLAG) == STAT_PLAYED_FLAG )
					TRACE( "PLAYED " );
				if ( (pMission->bVisible & STAT_VISIBLE_FLAG) == STAT_VISIBLE_FLAG )
					TRACE( "VISIBLE " );
				if ( pMission->bVisible == STAT_DISABLED_FLAG )
					TRACE( "DISABLED " );
				TRACE("\n");
			}
		}
	}
}

///========================================================================
//	Function:		AiDumpInfo()
//
//	Description:
//		Dump the AI_INFO structure.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiDumpInfo( )
{
#ifdef READER_DEBUG
	int	index;
	int	comp;

	TRACE( "MainBase Tables:\n" );
	for( index=0;index<4;++index)
	{
		TRACE( "   Base %d:\t offset ( %d, %d )\t Facing-%d\n",
				index, AIinfo.baseTables[ index ].nXoffset,
				AIinfo.baseTables[ index ].nYoffset,
				AIinfo.baseTables[ index ].nFacing );
	}
	TRACE( "\n" );

	TRACE( "nLookAheadTime:                %d\n", AIinfo.nLookAheadTime );
	TRACE( "nMovementLookAhead:            %d\n", AIinfo.nMovementLookAhead );
	TRACE( "\n" );

	TRACE( "Unit Tables:\n" );

	FOR_EACH_UNIT_TYPE(index)
	{
		TRACE( "   unit:                       %s\n", UnitTypeName(index, FALSE) );
		TRACE( "     makeup:\n" );
		TRACE( "        Primary:               %s\n",
										TrooperName( AIinfo.unitTables[ index ].makeup.ePrimary ) );
		TRACE( "        Secondary:             %s\n",
										TrooperName( AIinfo.unitTables[ index ].makeup.eSecondary ) );
		TRACE( "     troop strength:           %d\n", AIinfo.unitTables[ index ].nTroopStrength );
		TRACE( "     nTroops:                  %d\n", AIinfo.unitTables[ index ].nTroops );
		TRACE( "     speed:\n" );
		TRACE( "        nSpeed1:               %d\n",
										AIinfo.unitTables[ index ].speed.nSpeed1 );
		TRACE( "        nSpeed2:               %d\n",
										AIinfo.unitTables[ index ].speed.nSpeed2 );
		TRACE( "     acquisition level:\n" );
		TRACE( "        minimum:               %d\n",
										AIinfo.unitTables[ index ].targeting.nMinAttackLevel );
		TRACE( "        maximum:               %d\n",
										AIinfo.unitTables[ index ].targeting.nMaxAttackLevel );
		TRACE( "     composition data:\n" );
        TRACE( "        name:              %s\n",
            AIinfo.unitTables[ index ].comp.pName );
        TRACE( "        composition:           %d;%d\n",
            AIinfo.unitTables[ index ].comp.nSpecial,
            AIinfo.unitTables[ index ].comp.nRifle );
		}
	}
	TRACE( "\n" );

	TRACE( "Trooper Tables:\n" );
	for( index=1;index<ARMY_LAST_UNIT;++index)
	{
		TRACE( "   unit:                       %s\n", TrooperName( index ) );
		TRACE( "     weapon:                   %s\n",
										WeaponName( AIinfo.troopTables[ index ].weapon ) );
	}
	TRACE( "\n" );

	TRACE( "Vehicle Tables:\n" );
	for( index=1;index<ARMY_LAST_VEHICLE;++index)
	{
		TRACE( "   vehicle:                    %s\n", VehicleName( index ) );
		TRACE( "     weapons:\n" );
		TRACE( "        eWeapon1:              %s\n",
										WeaponName( AIinfo.vehicleTables[ index ].weapons.eWeapon1 ) );
		TRACE( "        eWeapon2:              %s\n",
										WeaponName( AIinfo.vehicleTables[ index ].weapons.eWeapon2 ) );
		TRACE( "     hitPoints:                %d\n", AIinfo.vehicleTables[ index ].nHitPoints );
		TRACE( "     speed:\n" );
		TRACE( "        nSpeed1:               %d\n",
										AIinfo.vehicleTables[ index ].speed.nSpeed1 );
		TRACE( "        nSpeed2:               %d\n",
										AIinfo.vehicleTables[ index ].speed.nSpeed2 );
		TRACE( "     accel:\n" );
		TRACE( "        nForward:              %d\n",
										AIinfo.vehicleTables[ index ].accel.nForward );
		TRACE( "        nReverse:               %d\n",
										AIinfo.vehicleTables[ index ].accel.nReverse );
		TRACE( "        nDeccel:               %d\n",
										AIinfo.vehicleTables[ index ].accel.nDeccel );
		TRACE( "     capacity:                 %d\n", AIinfo.vehicleTables[ index ].capacity );
		TRACE( "     ammo:\n" );
		TRACE( "        nAmmo1:                %d\n",
										AIinfo.vehicleTables[ index ].ammo.nAmmo1 );
		TRACE( "        nAmmo2:                %d\n",
										AIinfo.vehicleTables[ index ].ammo.nAmmo2 );
		TRACE( "     fuel:\n" );
		TRACE( "        nTotalFuel:            %d\n",
										AIinfo.vehicleTables[ index ].fuel.nTotalFuel );
		TRACE( "        nBurnRate:             %d\n",
										AIinfo.vehicleTables[ index ].fuel.nBurnRate );
		TRACE( "     acquisition level:\n" );
		TRACE( "        minimum:               %d\n",
										AIinfo.vehicleTables[ index ].targeting.nMinAttackLevel );
		TRACE( "        maximum:               %d\n",
										AIinfo.vehicleTables[ index ].targeting.nMaxAttackLevel );
	}
	TRACE( "\n" );

	TRACE( "Weapon Tables:\n" );
	for( index=1;index<ARMY_LAST_WEAPON;++index)
	{
		TRACE( "   weapon:                     %s\n", WeaponName( index ) );
		TRACE( "     rateOfFire:\n" );
		TRACE( "        nFrameDelay:           %d\n",
										AIinfo.weaponTables[ index ].rateOfFire.nFrameDelay );
		TRACE( "        nFrameContinuous:      %d\n",
										AIinfo.weaponTables[ index ].rateOfFire.nFrameContinuous );
		TRACE( "     eProjectile:              %d\n", AIinfo.weaponTables[ index ].eProjectile );
		TRACE( "     range:\n" );
		TRACE( "        nMinRange:             %d\n",
										AIinfo.weaponTables[ index ].range.nMinRange );
		TRACE( "        nMaxRange:             %d\n",
										AIinfo.weaponTables[ index ].range.nMaxRange );
		TRACE( "        nPercentDecreaseRate:  %d\n",
										AIinfo.weaponTables[ index ].range.nPercentDecreaseRate );
		TRACE( "        nDrift:                %d\n",
										AIinfo.weaponTables[ index ].range.nDrift );
		TRACE( "     damage:\n" );
		TRACE( "        nDamage:               %d\n",
										AIinfo.weaponTables[ index ].damage.nDamage );
		TRACE( "        nDamageDecreaseRate:   %d\n",
										AIinfo.weaponTables[ index ].damage.nDamageDecreaseRate );
	}
	TRACE( "\n" );

	TRACE( "Terrain Tables:\n" );
	for( index=0;index<AI_MAX_TBL_SIZE;++index)
	{
		TRACE( "   Terrain %d:\t Tank-%d\t HalfTrack-%d\t Jeep-%d\t Human-%d\n",
				index, AIinfo.terrainTables[ index ].nTank,
				AIinfo.terrainTables[ index ].nHalfTrack,
				AIinfo.terrainTables[ index ].nJeep,
				AIinfo.terrainTables[ index ].nHuman );
	}
	TRACE( "\n" );
#endif
}

///========================================================================
//	Function:		IsNumeric()
//
//	Description:
//		verify that the caller's input is a numeric character.
//
//	Input:			pCharacter		character to verify.
//
//	Ouput:			TRUE			if input was a numeric character
//
///========================================================================

BOOL	IsNumeric( char* pCharacter )
{
	BOOL	answer = FALSE;		// assume its not whitespace

	if( (( *pCharacter >= '0' )  && ( *pCharacter <= '9' ))
		||
		(( *pCharacter == '+' )  || ( *pCharacter == '-' ))
	  )
		answer = TRUE;

	return( answer );
}

///========================================================================
//	Function:		IsWhiteSpace()
//
//	Description:
//		verify that the caller's input is a white space character.
//
//	Input:			pCharacter		character to verify.
//
//	Ouput:			TRUE			if input was a white space character
//
///========================================================================

BOOL	IsWhiteSpace( char* pCharacter )
{
	BOOL	answer = FALSE;		// assume its not whitespace

	if( (*pCharacter == ' ')  ||
		(*pCharacter == '\t') ||
		(*pCharacter == ';')  ||			// special delimter
		(*pCharacter == '\n') ||
		(*pCharacter == '\0')
	  )
		answer = TRUE;

	return( answer );
}

///========================================================================
//	Function:		StripWhiteSpace()
//
//	Description:
//		strip away any leading white space in the command string.
//
//	Input:			pString		pointer to string being stripped.
//
//	Ouput:			pScanPtr	first non-white space character encountered
//
///========================================================================

char*	StripWhiteSpace( char* pString )
{
	char*	pScanPtr = pString;
	int		len      = strlen( pString );

	while( (*pScanPtr == ' ')  || (*pScanPtr == '\t') ||
		   (*pScanPtr == ';')  && (pScanPtr != (pString+len-1)) )
		++pScanPtr;

	return( pScanPtr );
}

///========================================================================
//	Function:		SkipToWhiteSpace()
//
//	Description:
//		skip forward through the data until you locate some white space.
//
//	Input:			pString		pointer to string being stripped.
//
//	Ouput:			pScanPtr	first non-white space character encountered
//
///========================================================================

char*	SkipToWhiteSpace( char* pString )
{
	char*	pScanPtr = pString;
	int		len      = strlen( pString );

	while( (*pScanPtr != ' ')  && (*pScanPtr != '\t') &&
		   (*pScanPtr != '\n') && (*pScanPtr != '\0') &&
		   (*pScanPtr != ';')  && ( pScanPtr != (pString+len-1))
		 )
		++pScanPtr;

	return( pScanPtr );
}

///========================================================================
//	Function:		AiGetCampaignRef()
//
//	Description:
//		locate the Campaign reference.
//
//	Input:			nCampaignID		ID reference for campaign data
//
//	Ouput:			pCampaignRef	pointer to campaign reference found
//
///========================================================================

CAMPAIGNREF*	AiGetCampaignRef( int nCampaignID )
{
	CAMPAIGNREF*	pCampaignRef = NULL;
	BOOL			bFound = FALSE;
	int				nIndex = 0;

	while ( !bFound && (nIndex<g_NumberCampaigns) )
	{
		pCampaignRef = g_Campaigns[ nIndex ];
		if ( pCampaignRef )
		{
			if ( pCampaignRef->nCampaignID == nCampaignID )
				bFound = TRUE;
		}
		++nIndex;
	}
	if ( !bFound )
		pCampaignRef = NULL;

	return( pCampaignRef );
}

///========================================================================
//	Function:		AiGetScenarioRef()
//
//	Description:
//		locate the scenario reference.
//
//	Input:			pCampaignRef	campaign scenario is in
//					nScenarioID		ID reference for scenario data
//
//	Ouput:			pScenarioRef	pointer to scenario reference found
//
///========================================================================

SCENARIOREF*	AiGetScenarioRef( CAMPAIGNREF* pCampaignRef, int nScenarioID )
{
	SCENARIOREF*	pScenarioRef = NULL;
	BOOL			bFound = FALSE;
	int				nIndex = 0;

	while ( !bFound && (nIndex<pCampaignRef->nNumberScenarios) )
	{
		pScenarioRef = &(pCampaignRef->pScenarios[ nIndex ]);
		if ( pScenarioRef->nScenarioID == nScenarioID )
			bFound = TRUE;
		else
			++nIndex;
	}
	if ( !bFound )
		pScenarioRef = NULL;

	return( pScenarioRef );
}

///========================================================================
//	Function:		AiGetMissionRef()
//
//	Description:
//		locate the scenario reference.
//
//	Input:			pScenarioRef	scenario set mission is in
//					nMissionID		ID reference for mission data
//
//	Ouput:			pMissionRef		pointer to mission reference found
//
///========================================================================

MISSIONREF*	AiGetMissionRef( SCENARIOREF* pScenarioRef, int nMissionID )
{
	MISSIONREF*	pMissionRef;
	BOOL		bFound = FALSE;
	int			nIndex = 0;

	while ( !bFound && (nIndex<pScenarioRef->nNumberMissions) )
	{
		pMissionRef = &(pScenarioRef->pMissions[ nIndex ]);
		if ( pMissionRef->nMissionID == nMissionID )
			bFound = TRUE;
		else
			++nIndex;
	}
	if ( !bFound )
		pMissionRef = NULL;

	return( pMissionRef );
}

///========================================================================
///========================================================================
char*	MPterrains[] =
{
	"Desert", "Alpine", "Bayou", "Tropical", "\0"
};

int	AiMPCampaignIndex( void )
{
	BOOL			bFound = FALSE;
	int				nIndex = 0;

	while( !bFound && *(MPterrains[ nIndex ]) )
	{
		if ( strcmp( the_map.terrain_name, MPterrains[ nIndex ] ) == 0 )
			bFound = TRUE;
		else
			++nIndex;
	}

	return( nIndex );
}

int	AiCampaignIndex( int nCampaignID )
{
	CAMPAIGNREF*	pCampaignRef;
	BOOL			bFound = FALSE;
	int				nIndex = 0;

	while( !bFound && nIndex<g_NumberCampaigns )
	{
		pCampaignRef = g_Campaigns[ nIndex ];
		if ( pCampaignRef->nCampaignID == nCampaignID )
			bFound = TRUE;
		else
			++nIndex;
	}

	if ( !bFound )
		nIndex = -1;

	return( nIndex );
}

int	AiScenarioIndex( CAMPAIGNREF* pCampaignRef, int nScenarioID )
{
	SCENARIOREF*	pScenarioRef;
	BOOL			bFound = FALSE;
	int				nIndex = 0;

	if (pCampaignRef == NULL) {
		TRACE("Warning: Null CampaignRef in AiScenarioIndex Ignoring it for now, wish me luck");
		return(-1);
	}
	while( !bFound && nIndex<AI_MAX_SCENARIOS )
	{
		pScenarioRef = &(pCampaignRef->pScenarios[ nIndex ]);
		if ( pScenarioRef->nScenarioID == nScenarioID )
			bFound = TRUE;
		else
			++nIndex;
	}

	if ( !bFound )
		nIndex = -1;

	return( nIndex );
}

int	AiMissionIndex( SCENARIOREF* pScenarioRef, int nMissionID )
{
	MISSIONREF*	pMissionRef;
	BOOL		bFound = FALSE;
	int			nIndex = 0;

	while( !bFound && nIndex<AI_MAX_MISSIONS )
	{
		pMissionRef = &(pScenarioRef->pMissions[ nIndex ]);
		if ( pMissionRef->nMissionID == nMissionID )
			bFound = TRUE;
		else
			++nIndex;
	}

	if ( !bFound )
		nIndex = -1;

	return( nIndex );
}

///========================================================================
//	Function:		AiGetCampaignRef()
//
//	Description:
//		locate the Campaign reference.
//
//	Input:			nCampaignID		ID reference for campaign data
//
//	Ouput:			pCampaignRef	pointer to campaign reference found
//
///========================================================================

USHORT	GetMissionKey( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	int				nIndex;
	USHORT			nKey = 0;

	// get the campaign string based on the army and campaign
	nIndex    = AiCampaignIndex( gpGame->CampaignID );
	if ( nIndex == -1 )
		goto exit;
	pCampaign = g_Campaigns[ nIndex ];
	if ( !pCampaign )
		goto exit;
	nIndex    = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
	if ( nIndex == -1 )
		goto exit;
	pScenario = &(pCampaign->pScenarios[ nIndex ]);
	if ( !pScenario )
		goto exit;
	nIndex    = AiMissionIndex( pScenario, gpGame->MissionID );
	if ( nIndex == -1 )
		goto exit;
	pMission  = &(pScenario->pMissions[ nIndex ]);
	if ( !pMission )
		goto exit;
	nKey = pMission->nMissionKey;

exit:
	return( nKey );
}

inline int AiGetNumObjects(void)
{
	return AIiObjsCount;
}

inline int AiGetNumCategories(void)
{
	return AIobjsCount;
}
//=======================================================================
//								EOF
//=======================================================================
