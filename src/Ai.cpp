//========================================================================
//	FILE:			$Workfile: Ai.cpp $
//
//	DESCRIPTION:	Artificial Intelligence (AI) default settings external
//					input processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Monday, November 19, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Ai.cpp 19    3/23/98 1:57p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	AiInit()
//		Initialize the AI processing.
//	AiExit()
//		Terminate the AI processor.
//	AiUnitDefaults()
//		acquire a unit's information block.
//	AiVehicleDefaults()
//		acquire a vehicle's information block.
//	AiWeaponDefaults()
//		acquire a weapon's information block.
//	AiAcquireDefaults()
//		acquire the default information block for an object.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Ai.cpp $
//  
//  19    3/23/98 1:57p Nrobinso
//  fix problem in inisitalizing of ai data tables
//  
//  18    3/23/98 12:27p Nrobinso
//  switch to loading the aai data every map load
//  
//  17    12/09/97 12:11p Phu
//  
//  16    11/20/97 11:41a Aburgess
//  FreeCampaign changed to AiCampaignFree
//  
//  15    11/16/97 2:17p Aburgess
//  frees campaign reference info
//  
//  13    9/14/97 12:19p Bwilcox
//  influence stuff moved to deadcode.cpp (not in project)
//  
//  12    8/07/97 11:07p Nrobinso
//  moved globals.h to stdafx.h
//  
//  11    8/05/97 3:25p Nrobinso
//  removed linking of tad flags with item flags
//  
//  10    7/30/97 11:57a Bwilcox
//  UnitUpdateInfluece is no longer public, call removed from ai.cpp
//  
//  9     7/29/97 10:44p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
//  
//  8     7/28/97 11:56p Nrobinso
//  make pObjs an anonymous union; add SARGE
//  
//  7     7/28/97 8:24p Nrobinso
//  FOR_EACH_ARMY macros requires comm.h; deal with this later
//  
//  6     7/28/97 6:48p Nrobinso
//  add sarge to AiUpdateInfluence
//  
//  5     7/24/97 12:59p Aburgess
//  added knowledge of ARMY_NULL_OBJs and removal of superfluous trace
//  statements
//  
//  4     7/23/97 10:55p Aburgess
//  now acquires next attacker for each army
//  
//  3     7/14/97 1:16p Awerner
//  Modified prototype of TextWrite
//  
//  2     7/12/97 3:19p Bwilcox
//  deleted ARMY_POSITION pseudo-object type and all associated code
//  
//  1     7/03/97 5:17p Nrobinso
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"
#include "Text.h"
#include "Army.h"
#include "Map.h"
#include "MainFrm.h"
#include "Tad.h"
#include "Ai.h"
#include "unit.h"
#include "vehicle.h"

#include "miscfile.h"
#include "newdoor.h"

///========================================================================
//							LOCAL DEFINES
///========================================================================
#define	INFLUENCE_BLOCKED	127
#define	INFLUENCE_MOVEMENT_FACTOR	2
#define	INFLUENCE_ELEVATION_FACTOR	6
#define	INFLUENCE_OBSTACLE_FACTOR	2
#define	INFLUENCE_TAD_FACTOR		2

///========================================================================
//							LOCAL DATA STRUCTURES
///========================================================================

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
void*			AiAcquireDefaults( int eObjType, int eObjId );
AI_ACQUIRE*		AiAcquireTargetDefaults( int eObjType, int eObjId );

///========================================================================
//							LOCAL VARIABLES
///========================================================================

AI_INFO			AIinfo;					// AI DEFAULT DATA

char*	AIhex[] =
{
	 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e","f",
	"-0","-1","-2","-3","-4","-5","-6","-7","-8","-9","-a","-b","-c","-d","-e","-f"
};


///========================================================================
//	Function:		AiDataLoad()
//
//	Description:
//		Load the basic ai data
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

BOOL	AiDataLoad( char* pPathName )
{
	BOOL	error = TRUE;

	// if we made it here we were successful
	error = FALSE;

	// initialize globals
//	ZeroMemory( (void*)&AIinfo, sizeof(AI_INFO) );

	ClearAiData();

	// initialize all the AI defaults
	AiDefaultLoad( NULL );
	AiDefaultLoad( pPathName );

	return( error );
}


///========================================================================
//	Function:		AiInit()
//
//	Description:
//		Initialize the AI processing.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

BOOL	AiInit( void )
{
	BOOL	error = TRUE;

	// if we made it here we were successful
	error = FALSE;

	// initialize globals
	ZeroMemory( (void*)&AIinfo, sizeof(AI_INFO) );

	// initialize all the AI defaults
	AiDefaultLoad( NULL );

	return( error );
}

///========================================================================
//	Function:		AiExit()
//
//	Description:
//		Terminate the AI processor.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	AiExit( void )
{
	// terminate the TAD Processor
	TadExit();

	// free up the campaign data
	AiCampaignFree();
}

///========================================================================
//	Function:		AiAssetDefaults()
//
//	Description:
//		acquire an asset's information block.
//
//	Input:			eAssetId		Asset id ( Mainbase, Turret, etc)
//
//	Ouput:			pDefaultData	Asset default information. NULL if failed.
//
///========================================================================

AI_ATBL*	AiAssetDefaults( int eAssetId )
{
	AI_ATBL*	pDefaultData;

	// validate parameters
//	ASSERT( eAssetId && (eAssetId < ARMY_LAST_ASSET) );

	// acquire the default formation
	pDefaultData = (AI_ATBL*)AiAcquireDefaults( AI_ASSET_OBJ, eAssetId );

	return( pDefaultData );
}

///========================================================================
//	Function:		AiUnitDefaults()
//
//	Description:
//		acquire a unit's information block.
//
//	Input:			eUnitId			unit id ( Light Infantry, Commandos, etc)
//
//	Ouput:			pUnitDefaults	unit default information. NULL if failed.
//
///========================================================================

AI_UTBL*	AiUnitDefaults( int eUnitId )
{
	AI_UTBL*	pDefaultData;

	// validate parameters
//	ASSERT( eUnitId && (eUnitId < ARMY_LAST_UNIT) );

	// acquire the default formation
	pDefaultData = (AI_UTBL*)AiAcquireDefaults( AI_UNIT_OBJ, eUnitId );

	return( pDefaultData );
}

///========================================================================
//	Function:		AiVehicleDefaults()
//
//	Description:
//		acquire a vehicle's information block.
//
//	Input:			eVehicleId			vehicle id ( Jeep, Tank, etc)
//
//	Ouput:			pVehicleDefaults	vehicle default information. NULL if failed.
//
///========================================================================

AI_VTBL*	AiVehicleDefaults( int eVehicleId )
{
	AI_VTBL*	pDefaultData;

	// validate parameters
//	ASSERT( eVehicleId && (eVehicleId < ARMY_LAST_VEHICLE) );

	// acquire the default formation
	pDefaultData = (AI_VTBL*)AiAcquireDefaults( AI_VEHICLE_OBJ, eVehicleId );

	return( pDefaultData );
}

///========================================================================
//	Function:		AiWeaponDefaults()
//
//	Description:
//		acquire a weapon's information block.
//
//	Input:			eWeaponId		Weapon id ( Light Machine Gun, Falme Thrower, etc)
//
//	Ouput:			pWeaponDefaults	Weapon default information. NULL if failed.
//
///========================================================================

AI_WTBL*	AiWeaponDefaults( int eWeaponId )
{
	AI_WTBL*	pDefaultData;

	// validate parameters
//	ASSERT( eWeaponId && (eWeaponId < ARMY_LAST_WEAPON) );

	// acquire the default formation
	pDefaultData = (AI_WTBL*)AiAcquireDefaults( AI_WEAPON_OBJ, eWeaponId );

	return( pDefaultData );
}

///========================================================================
//	Function:		AiAcquireDefaults()
//
//	Description:
//		acquire the default information block for an object.
//
//	Input:			eObjType	object type (UNIT, VEHICLE, ASSET, WEAPON)
//					eObjId		object identification
//
//	Ouput:			pointer to object default data, NULL otherwise
//
///========================================================================

void*	AiAcquireDefaults( int eObjType, int eObjId )
{
	void*	pDefaultData = NULL;

	// validate parameters
//	ASSERT( eObjType && (eObjType <= AI_WEAPON_OBJ) );
//	ASSERT( eObjId && (eObjId < ARMY_LAST_WEAPON) );

	switch( eObjType )
	{
	case AI_UNIT_OBJ:
		// make sure the object id is legal for a UNIT
		if ( (eObjId>ARMY_NO_UNIT) && (eObjId<ARMY_LAST_UNIT) )
			pDefaultData = (void*)&(AIinfo.unitTables[ eObjId ]);
		break;
	case AI_VEHICLE_OBJ:
		// make sure the object id is legal for a VEHICLE
		if ( (eObjId>ARMY_NO_VEHICLE) && (eObjId<ARMY_LAST_VEHICLE) )
			pDefaultData = (void*)&(AIinfo.vehicleTables[ eObjId ]);
		break;
	case AI_ASSET_OBJ:
		break;
	case AI_WEAPON_OBJ:
		// make sure the object id is legal for a UNIT
		if ( (eObjId>ARMY_NO_VEHICLE) && (eObjId<ARMY_LAST_VEHICLE) )
			pDefaultData = (void*)&(AIinfo.weaponTables[ eObjId ]);
		break;
	default:
		break;
	}

	return( pDefaultData );
}

///========================================================================
//	Function:		AiAssetTargetDefaults()
//
//	Description:
//		acquire an asset's information block.
//
//	Input:			eAssetId		Asset id ( Mainbase, Turret, etc)
//
//	Ouput:			pDefaultData	Asset default information. NULL if failed.
//
///========================================================================

AI_ACQUIRE*	AiAssetTargetDefaults( int eAssetId )
{
	AI_ACQUIRE*	pDefaultData;

	// validate parameters
//	ASSERT( eAssetId && (eAssetId < ARMY_LAST_ASSET) );

	// acquire the default formation
	pDefaultData = AiAcquireTargetDefaults( AI_ASSET_OBJ, eAssetId );

	return( pDefaultData );
}

///========================================================================
//	Function:		AiUnitTargetDefaults()
//
//	Description:
//		acquire a unit's information block.
//
//	Input:			eUnitId			unit id ( Light Infantry, Commandos, etc)
//
//	Ouput:			pUnitDefaults	unit default information. NULL if failed.
//
///========================================================================

AI_ACQUIRE*	AiUnitTargetDefaults( int eUnitId )
{
	AI_ACQUIRE*	pDefaultData;

	// validate parameters
//	ASSERT( eUnitId && (eUnitId < ARMY_LAST_UNIT) );

	// acquire the default formation
	pDefaultData = AiAcquireTargetDefaults( AI_UNIT_OBJ, eUnitId );

	return( pDefaultData );
}

///========================================================================
//	Function:		AiVehicleTargetDefaults()
//
//	Description:
//		acquire a vehicle's information block.
//
//	Input:			eVehicleId			vehicle id ( Jeep, Tank, etc)
//
//	Ouput:			pVehicleDefaults	vehicle default information. NULL if failed.
//
///========================================================================

AI_ACQUIRE*	AiVehicleTargetDefaults( int eVehicleId )
{
	AI_ACQUIRE*	pDefaultData;

	// validate parameters
//	ASSERT( eVehicleId && (eVehicleId < ARMY_LAST_VEHICLE) );

	// acquire the default formation
	pDefaultData = AiAcquireTargetDefaults( AI_VEHICLE_OBJ, eVehicleId );

	return( pDefaultData );
}

///========================================================================
//	Function:		AiAcquireTargetDefaults()
//
//	Description:
//		acquire the default information block for an object.
//
//	Input:			eObjType	object type (UNIT, VEHICLE, ASSET, WEAPON)
//					eObjId		object identification
//
//	Ouput:			pointer to object targeting default data, NULL otherwise
//
///========================================================================

AI_ACQUIRE*	AiAcquireTargetDefaults( int eObjType, int eObjId )
{
	AI_ACQUIRE*	pDefaultData = NULL;

	// validate parameters
//	ASSERT( eObjType && (eObjType <= AI_WEAPON_OBJ) );
//	ASSERT( eObjId && (eObjId < ARMY_LAST_WEAPON) );

	switch( eObjType )
	{
	case AI_UNIT_OBJ:
		// make sure the object id is legal for a UNIT
		if ( (eObjId>ARMY_NO_UNIT) && (eObjId<ARMY_LAST_UNIT) )
			pDefaultData = &(AIinfo.unitTables[ eObjId ].targeting);
		break;
	case AI_VEHICLE_OBJ:
		// make sure the object id is legal for a VEHICLE
		if ( (eObjId>ARMY_NO_VEHICLE) && (eObjId<ARMY_LAST_VEHICLE) )
			pDefaultData = &(AIinfo.vehicleTables[ eObjId ].targeting);
		break;
	case AI_ASSET_OBJ:
		// make sure the object id is legal for a VEHICLE
		if ( (eObjId>ARMY_NO_ASSET) && (eObjId<ARMY_LAST_ASSET) )
			pDefaultData = &(AIinfo.assetTables[ eObjId ].targeting);
		break;
	case AI_WEAPON_OBJ:
		break;
	default:
		break;
	}

	return( pDefaultData );
}

//=======================================================================
//								EOF
//=======================================================================
