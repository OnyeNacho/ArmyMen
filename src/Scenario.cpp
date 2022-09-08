//========================================================================
//	FILE:			$Workfile: Scenario.cpp $
//
//	DESCRIPTION:	Scneario.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Monday, October 07, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Scenario.cpp 32    4/08/98 8:20p Bwilcox $
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
//  $Log: /ArmyMen/src/Scenario.cpp $
//  
//  32    4/08/98 8:20p Bwilcox
//  saving death status in game for units and vehicles
//  
//  30    4/02/98 3:21p Phu
//  typecast to avoid warnings
//  
//  29    2/21/98 5:48p Nrobinso
//  remove TRACE
//  
//  28    1/27/98 1:06p Bwilcox
//  finishing armydelete adjustments for multiplayer
//  
//  27    12/09/97 12:12p Phu
//  
//  26    12/05/97 10:33p Nrobinso
//  verify that number of missions corresponds in map & campaign file
//  
//  25    12/05/97 9:52p Nrobinso
//  changed deployment member name; clear deployment data on allocation
//  
//  24    11/03/97 9:46p Nrobinso
//  fix off by 1's if NO_ is 0
//  
//  23    97-10-24 17:36 Dmaynard
//  remapping color correctly for scenario force copy
//  
//  22    10/16/97 3:56p Nrobinso
//  default number of troopers in a unit to 1
//  
//  21    10/14/97 11:46p Nrobinso
//  fix DeleteScenarioForces exit bug
//  
//  20    10/10/97 8:07p Nrobinso
//  scenario data needs to be processed for max armies (4)
//  
//  19    10/10/97 6:52p Nrobinso
//  return number of mission from SetupScenario()
//  
//  18    10/08/97 8:53a Nrobinso
//  put scenario data into mission order
//  
//	...
//  
//  1     10/07/96 12:29p Nrobinso
//  Scneario related functions
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"

#include "Army.h"
#include "Vehicle.h"
#include "Map.h"
#include "MainFrm.h"
#include "Tad.h"
#include "Ai.h"
#include "Disp.h"
#include "Comm.h"
#include "gameflow.h"

#include "Scenario.h"

///========================================================================
//							GLOBAL VARIABLES
///========================================================================

///========================================================================
//							LOCAL DEFINES
///========================================================================

///========================================================================
//							LOCAL VARIABLES
///========================================================================

///========================================================================
//							LOCAL FUNCTIONS
///========================================================================
static long	CopyScenarioForces( FORCE *pForces, char* pData );
static void	DeleteScenarioForces( FORCE *pForces );

#if SCENARIO_DEBUG
static void	DumpScenario( MISSION* pMission );
#endif

///========================================================================
//								CODE

///========================================================================
//	Function:		CopyScenarioForces()
//
//	Description:
//		Reads in a SCENARIO block of data.
//
// SCENario data
//	'SCEN'
//		LONG		datasize
//		LONG		NumberOfScenarios;		// number of scenarios for this map
//		SCENARIO	Missions[ NumberOfScenarios ];
//
//	where SCENARIO is defined as
//		char	ScenarioName[ MAX_NAME ];
//		LEGION	Player1;
//		LEGION	Player2;
//		LEGION	Player3;
//		LEGION	Player4;
//
//	where LEGION is defined as
//		long		NumberUnitTypes					// number of unit types
//		long		Reserved_1;
//		long		UnitsAvail[ NumberUnitTypes ];	// avail num of each unit type
//		long		NumberVehicleTypes				// number of vehicle types
//		long		Reserved_2;
//		long		VehicleAvail[ NumberVehicleTypes ];		// based on NumberUnitTypes
//		long		NumberUnitsDeployed;					// number of units/vehicles in deployment list
//		DEPLOYED	UnitsDeployed[ NumberUnitsDeployed ];	// list of deployed units/vehicles
//
//	where DEPLOYED is defined as
///		long		eUnitType;						// type of unit/vehicle deployed (hi bit set indciates vehicle)		
//		long		xWorldCoord;					// restricted by map boundary and unit
//		long		yWorldCoord;					//    rectangle from BMP, based on hotspot
//		long		facing;							// direction unit is facing
//
//	Input:			pForces		where to store the scenario block data
//					pData		start of the scenario block data
//
//	Ouput:			none
//
///========================================================================

static long	CopyScenarioForces( FORCE *pForces, char* pData )
{
	DEPLOYED*	pDeployment;
	LONG		nDeployed;
	long*		pBlockData;
	char*		pByteData;
	int			nDeploySize;
	LONG		nNumber;
	LONG		nResources;
	LONG		nType;
	LONG		nTotalSize;
	int			nCount;
	LONG		nData;
	LONG		reserved;

	ZeroMemory(pForces, sizeof(FORCE));

	// setup to read through this block of data
	pBlockData = (long *)pData;
	nTotalSize = 0;

	// get the number of units and skip the in reserve field
	nNumber = *pBlockData++;
	reserved = *pBlockData++;
	nTotalSize += 2*sizeof(long);		// LONG (number available) + LONG (number in reserve)
	ASSERT(nNumber <= ARMY_LAST_UNIT);

	// now read in the unit reserve information
	for ( nCount=0; nCount<nNumber; ++nCount )
	{
		// get the long value and stuff into a char
		nData = *pBlockData++;
		pForces->Reserves.nUnitsAvail[ nCount ] = (char)nData;

		nTotalSize += sizeof(long);
	}

	// get the number of vehicles and the number of resources
	nNumber = *pBlockData++;
	nResources = *pBlockData++;
	nTotalSize += 2*sizeof(long);		// LONG (number vehicles) + LONG (number resources)
	ASSERT(nNumber <= ARMY_LAST_VEHICLE);
	ASSERT(nResources <= ARMY_LAST_RESOURCE);

	// now read in the vehicle reserve information
	for ( nCount=0; nCount<nNumber; ++nCount )
	{
		// get the long value and stuff into a char
		nData = *pBlockData++;
		pForces->Reserves.nVehiclesAvail[ nCount+1 ] = (char)nData;

		nTotalSize += sizeof(long);
	}

	// now read in the reources information
	for ( nCount=0; nCount<nResources; ++nCount )
	{
		// get the long value and stuff into a char
		nData = *pBlockData++;
		pForces->Reserves.nResourcesAvail[ nCount+1 ] = (char)nData;

		nTotalSize += sizeof(long);
	}

	// read in the deployment data, including the number deployed value
	nDeployed = *pBlockData++;
	nTotalSize += sizeof(long);
	pForces->nDeployed = (SHORT)nDeployed;
	if ( nDeployed )
	{
		nDeploySize = (nDeployed*(sizeof(DEPLOYED)));
		pForces->pDeployment = (DEPLOYED*)malloc(nDeploySize);
		if ( pForces->pDeployment == NULL )
		{
			TRACE( "ERROR: unable to allocate memory for scenario. [%s,%d]\n",
					__FILE__, __LINE__ );
			nTotalSize = 0;
			goto exit;
		}

		pDeployment = pForces->pDeployment;
		ZeroMemory(pDeployment, nDeploySize);

#ifdef MALLOC_DEBUG
		TRACE( "malloc (%ld): army DEPLOYED (army %d) [%s : %d]\n", nDeploySize, eArmy, __FILE__, __LINE__ );
#endif

		// copy in the deployment information
		for ( nNumber=0; nNumber<nDeployed; ++nNumber )
		{
			// load in the deployment information.
			nType = *pBlockData++;
			pDeployment->eType      = (UNIT_TYPE)nType;
			pDeployment->location.x = (short)(*pBlockData++);
			pDeployment->location.y = (short)(*pBlockData++);

			pByteData = (char *) pBlockData;
			pDeployment->facing     = *pByteData++;
			pDeployment->deployed   = !(*pByteData++);
			pDeployment->number     = *pByteData++;
			pDeployment->dead		= FALSE;
			pDeployment->deadPosition = OFF_THE_MAP;
			if (!pDeployment->number)	{
				pDeployment->number = 1;
//				TRACE("unit deployed with 0 troopers, modified to 1\n");
			}

//			char reserved  = *pByteData++;
			char size  = *pByteData++;

			if (size)	{
				ASSERT(size <= 255);
				strcpy(pDeployment->text, pByteData);
				pByteData += size;
				pBlockData = (long *) pByteData;
				nTotalSize += size;
			}
			else	{
				pDeployment->text[0] = '\0';
				pBlockData++;
			}

			// now adjust the size tracker
			nTotalSize += 4*sizeof(long);

			// advance to the next deploment block
			++pDeployment;
		}
	}

exit:
	return( nTotalSize );
}


///========================================================================
//	Function:		DeleteScenarioForces()
///========================================================================

static void	DeleteScenarioForces( FORCE *pForces )
{
	if(pForces->pDeployment)
		free(pForces->pDeployment);

	ZeroMemory(pForces, sizeof(FORCE));
}


///========================================================================
//	Function:		SetupScenario()
//	Description:	Setup the scenario data for this game.
///========================================================================

int	SetupScenario( char* pData, long nDataSize )
{
	long	nMaxSize;
	LONG	nSize;
	LONG	scenarioSize;
	LONG	nNumMissions;
	char*	pScenarioData;
	MISSION *pMissions;
	int		eArmy;
	int		nArmyIndex;

	// NOTE: this scenario block contains all the data for all missions and all players
	pScenarioData = pData;
	nMaxSize = nDataSize;

	// Start by acquiring the number of scenarios in this block.
	// NOTE: we only want to read the scenario block associated with
	// this instance of the player COMM will have determined in advance
	// which scenario block to access.
	nNumMissions = (LONG)*pScenarioData;
	nSize = sizeof( nNumMissions );
	pScenarioData += nSize;
	nMaxSize -= nSize;

	pMissions = (MISSION *)malloc(nNumMissions*sizeof(MISSION));
	Scenario.pMissions = pMissions;
	Scenario.nNumMissions = (WORD)nNumMissions;

	for (int i=0; i<nNumMissions; i++)	{
		char name[SCENARIO_NAME_SIZE];
		int mission;

		// now get the scenario name and advance past it
		memcpy( name, pScenarioData, SCENARIO_NAME_SIZE );
		pScenarioData += SCENARIO_NAME_SIZE;
		nMaxSize -= SCENARIO_NAME_SIZE;

		if (strncmp(name,"Scenario",8) != 0)
			ASSERT(0);

		if (name[8] == '\0')
			mission = 0;
		else	{
			mission = name[8] - '1';
			ASSERT(name[9] == '\0');
		}

		memcpy( pMissions[mission].scenarioName, name, SCENARIO_NAME_SIZE );

		FOR_EACH_ARMY(eArmy)
		{
			nArmyIndex = gpComm->IndexFromColor((ARMY_COLOR) eArmy );
			scenarioSize = CopyScenarioForces( &pMissions[mission].forces[nArmyIndex], pScenarioData );

#if SCENARIO_DEBUG
			TRACE( "ARMY %d:\n", eArmy );
			DumpScenario( pArmyScenario );
#endif

			pScenarioData += scenarioSize;
			nMaxSize -= scenarioSize;
		}
	}

#if _DEBUG
	// verify that the map corresponds to the campaign file
    if (gpGame->GameType == GAMETYPE_ONEPLAYER)
		ASSERT(Scenario.nNumMissions == g_Campaigns[ g_CampaignIndex ]->pScenarios[ g_ScenarioIndex ].nNumberMissions);
	else
		ASSERT(Scenario.nNumMissions == 1);
#endif

	return( nNumMissions );
}

///========================================================================
//	Function:		DeleteScenario()
//	Description:	Display an Army.
///========================================================================

void	DeleteScenario()
{
	long		nNumMissions = Scenario.nNumMissions;
	MISSION*	pMissions = Scenario.pMissions;
	int			eArmy;
	long		nTotalSize = 0;

	if (pMissions)	{
		for (int i=0; i<nNumMissions; i++)	{
			FOR_EACH_ARMY(eArmy)
			{
				DeleteScenarioForces( &pMissions[i].forces[eArmy] );
			}
		}

		free(Scenario.pMissions);
	}

	ZeroMemory( (void*)&Scenario, sizeof(SCENARIO) );
}

///========================================================================
//	Function:		DumpScenario()
//	Description:
///========================================================================

#if SCENARIO_DEBUG
static void	DumpScenario( SCENARIO* pScenario )
{
	int unit;

	TRACE( "Scenario Data:\n" );
	TRACE( "\tReserves\n" );
	TRACE( "\tDeployed = %d\n", pScenario->nDeployed );
	if ( pScenario->nDeployed )
	{
		for( unit=0; unit<pScenario->nDeployed; ++unit )
		{
			switch( pScenario->pDeployment->eUnitType )
			{
			case ARMY_GRENADE_UNIT:
				TRACE( "\t\tARMY_GRENADE_UNIT  - " );
				break;
			case ARMY_FLAME_UNIT:
				TRACE( "\t\tARMY_FLAME_UNIT    - " );
				break;
			case ARMY_BAZOOKA_UNIT:
				TRACE( "\t\tARMY_BAZOOKA_UNIT  - " );
				break;
			case ARMY_ENGINEER_UNIT:
				TRACE( "\t\tARMY_ENGINEER_UNIT - " );
				break;
			case ARMY_MORTAR_UNIT:
				TRACE( "\t\tARMY_MORTAR_UNIT   - " );
				break;
			case ARMY_MINER_UNIT:
				TRACE( "\t\tARMY_MINER_UNIT    - " );
				break;
			}
			TRACE( "(%d,%d)\n",	pScenario->pDeployment[unit].location.x,
						pScenario->pDeployment[unit].location.y	);
		}
	}
}
#endif

///========================================================================
//								EOF
///========================================================================
