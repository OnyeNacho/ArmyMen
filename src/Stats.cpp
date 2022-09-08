//========================================================================
//	FILE:			$Workfile: Stats.cpp $
//
//	DESCRIPTION:	ArmyMen Statistics processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, October 29, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Stats.cpp 44    4/03/98 4:22p Aburgess $
//
//========================================================================
//                 COPYRIGHT(C)1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Stats.cpp $
//  
//  44    4/03/98 4:22p Aburgess
//  removed debug #ifs
//  
//  43    4/03/98 4:18p Aburgess
//  modifications to fix next mission bug
//  
//  42    4/02/98 11:39p Aburgess
//  modifications to support NEXT playable mission
//  
//  41    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  40    4/01/98 12:44p Aburgess
//  New Player comparision correction
//  
//  39    4/01/98 11:03a Aburgess
//  added "NewPlayer" button size
//  
//  38    3/28/98 9:40a Nrobinso
//  do a case insensitive compare on player names
//  
//  37    3/26/98 10:18a Nrobinso
//  set all saved game operations to the save game folder
//  
//  36    3/25/98 7:52p Nrobinso
//  save path
//  
//  35    3/18/98 2:31a Nrobinso
//  set player name to new player if can't read the registry
//  
//  34    3/18/98 12:51a Nrobinso
//  cleanup registry access
//  
//  33    3/16/98 12:29a Nrobinso
//  save mission failures
//  
//  32    3/09/98 11:30a Nrobinso
//  don't save stats if run off cd
//  
//  31    3/02/98 12:23p Nrobinso
//  don't assert if can't save a file
//  
//  30    2/05/98 3:26p Nrobinso
//  add real stats
//  
//  29    2/04/98 5:57p Nrobinso
//  add SetPath before getting stats file; change surviving units to
//  surviving troops
//  
//  28    2/03/98 8:54p Nrobinso
//  
//  27    1/23/98 12:08p Aburgess
//  put in oneplayer check (to fix multiplayer problem) into StatsStable
//  
//  26    1/22/98 6:44p Nrobinso
//  use SetPath
//  
//  25    1/09/98 8:50a Aburgess
//  modified StatMakeAllVisible to set a do later flag (g_numberCampaigns
//  == -1) when campaigns haven't been loaded yet.
//  
//  23    12/15/97 1:14a Aburgess
//  corrected Stats completed Campaign,Scenario, Mission save and load
//  process
//  
//  22    12/11/97 1:51p Aburgess
//  removed erroneous STAT_PLAY_FLAG setting. Also added setting of current
//  IDs (campaign,scenario, and mission) at startup and reading of
//  completedmissions info
//  
//  21    12/11/97 10:44a Aburgess
//  stats now saved even when" All Scenarios Visible" is on
//  
//  20    12/11/97 10:21a Aburgess
//  corrected Player CallSign bugs
//  
//  19    12/10/97 9:44a Aburgess
//  changes made to centralize REGKEY access. Also
//  fixes CANCEL or BACK in multiplayer connect
//  
//  18    12/09/97 12:12p Phu
//  
//  17    12/05/97 9:53p Nrobinso
//  add StatSaveNext to save the visibility of the next mission
//  
//  16    12/02/97 10:45a Aburgess
//  modifications for Make All 1st Missions Visible
//  
//  15    12/01/97 6:25p Nrobinso
//  improve stats read error and eof checking
//  
//  14    12/01/97 5:21p Aburgess
//  no longer ALL missions visible, only 1st mission of ALL scenarios and
//  campaigns
//  
//  13    12/01/97 4:48p Aburgess
//  code to process make all missions visible
//  
//  12    12/01/97 9:56a Aburgess
//  dummy end marker added to mission data record
//  
//  11    11/20/97 12:17p Aburgess
//  added StatStable to AiCampaignLoad in case someone goes through menus
//  rather than UI
//  
//  10    11/20/97 11:54a Aburgess
//  added new campaign interfaces
//  
//  9     11/20/97 11:32a Nrobinso
//  remove uneeded directory change
//  
//  8     11/18/97 10:31a Aburgess
//  corrected path specifications to be relative to BASE_WORK_PATH. Added
//  class function to miscfile (cdPath) that changes based on starting from
//  BASE_WORK_PATH
//  
//  7     11/16/97 2:02p Nrobinso
//  attempt to remove RegCreateKeyEx reource leak
//  
//  6     11/11/97 3:00p Aburgess
//  added check for duplicate PlayerName during EDIT
//  
//  5     11/11/97 8:50a Aburgess
//  added HaveSavedMission() routine and added data file close calls
//  (fclose)
//  
//  4     11/10/97 10:00a Aburgess
//  Corrected Registry Key access failure and crash. Nicky Robinson
//  
//  3     11/07/97 12:18p Aburgess
//  call to stablize ID and Indecies for campaign data
//  
//  2     11/07/97 10:35a Aburgess
//  stats and mission save/read modifications
//  
//  1     11/06/97 9:27a Aburgess
//  Game Statistics Modules
//  
//  
//  $Nokeywords:$
//========================================================================

// Includes
#include "stdafx.h"
#include "comm.h"
#include "Armymen.h"
#include "MainFrm.h"
#include "GameFlow.h"
#include "gameproc.h"
#include "Dialog.h"
#include "Audio.h"
#include "Ai.h"
#include "ui.h"
#include "comm.h"
#include "miscfile.h"
#include "bmptext.h"
#include "States.h"
#include "Screen.h"
#include "util.h"
#include "fileio.h"

#include "Stats.h"
#include "Stats.dat"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//================================================================
//			GLOBAL variables
//================================================================
extern	char	NEWPLAYER_TextBtn[];
extern	int		NEWPLAYER_BtnSize;

char	STATplayerNames[ STAT_MAX_PLAYERS ][SBTN_MAX_PLAYER_NAME_LEN+1];	// player choice name strings data
char	STATcurrentName[SBTN_MAX_PLAYER_NAME_LEN+1];						// player current name strings data

//================================================================
//			GLOBAL prototypes
//================================================================

//================================================================
//			LOCAL variables
//================================================================
static	STATS	STATplayer;							// current player statistics
static	STATS	STATprevious;						// previous statistics for the current mission
static	int		STATplayerIndex;					// player name index
static	char	STATupdate[ STAT_MAX_PLAYERS ];		// update registry/stats data

static	FILE*	STATfile;							// stats data file

static	STAT_CHUNK	STATchunkBuffer;				// stats file i/o data buffer

//================================================================
//			LOCAL prototypes
//================================================================
void	StatSetCampaignVisibility( CAMPAIGNREF* pCampaign, STAT_ID_RECORD* pStats, int nRecords );
void	StatSetScenarioVisibility( SCENARIOREF* pScenario, STAT_ID_RECORD* pStats, int nRecords );
void	StatSetMissionVisibility( MISSIONREF* pMission, STAT_ID_RECORD* pStats, int nRecords );
void	StatSetMissionFailures( MISSIONREF* pMission, STAT_ID_RECORD* pStats, int nRecords );
BOOL	StatFindVisibility( USHORT nID, STAT_ID_RECORD* pStats, int nRecords, BOOL* bVisibility );
BOOL	StatFindFailed( USHORT nID, STAT_ID_RECORD* pStats, int nRecords, unsigned char* pnFailed );
BOOL	StatRead( STATS* pMissionStats, char* pASFname );
BOOL	StatCheckForSavedMission( char* ASFname );

//================================================================
//			STATS Routines
//================================================================

//========================================================================
//	Function:		StatInit()
//
//	Description:
//		Initalize the Statistics processing.
//
//	Input:			none
//
//	Ouput:			FALSE			if successful, TRUE if an error occured
//
//========================================================================

BOOL	StatInit( void )
{
	int		nPlayerName;
	DWORD	dwSize;
	LPCTSTR pNameKey;
    char*   pDataBuffer;
	LONG	bError = TRUE;

	// initialize the stats chunk buffer (data i/o)
	STATchunkBuffer.nChunkID   = (ULONG)STAT_ID;
	STATchunkBuffer.nChunkSize = sizeof( STATchunkBuffer );
	ZeroMemory( (void*)&(STATchunkBuffer.dStats), sizeof( STATS ) );

	// initialize the player name data
	STATplayerIndex = -1;					// undefined
	ZeroMemory( (void*)&(STATplayer), sizeof( STATS ) );
	ZeroMemory( (void*)&(STATprevious), sizeof( STATS ) );
	ZeroMemory( (void*)&(STATplayerNames), ((SBTN_MAX_PLAYER_NAME_LEN+1)<<2) );

	for( nPlayerName=0; nPlayerName<STAT_MAX_PLAYERS; ++nPlayerName )
	{
		pNameKey    = STATnameKey[ nPlayerName ];
		pDataBuffer = STATplayerNames[ nPlayerName ];

		// clear data, for if not in registry
		*pDataBuffer = 0;

		dwSize = SBTN_MAX_PLAYER_NAME_LEN+1;
		gpComm->RegGet(pNameKey, (LPBYTE)pDataBuffer, &dwSize);
		// make sure the StatPlayerName has a valid string, if NULL simply
		// initialize to the NewPlayer string name
		if ( *pDataBuffer == 0 )	// NEW data, set to New Player
		{
			strcpy( pDataBuffer, NEWPLAYER_TextBtn );
			dwSize = strlen( pDataBuffer );

			// remember we're outputing an ascii string, use the ascii write
			// version of RegSet - RegSetA
			gpComm->RegSetA(pNameKey, (CONST BYTE *)pDataBuffer, dwSize);
		}
    }

	// set the current player index
	StatSetPlayerNameIndex( 0 );
	StatUpdate( STAT_CURRENT_PLAYER_INDEX, STAT_UPDATE_PLAYER_NAME, FALSE );

	bError = FALSE;
	return( bError );
}

//========================================================================
//	Function:		StatExit()
//
//	Description:
//		terminate and clear the Statistics processing.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	StatExit( void )
{
}

//========================================================================
//	Function:		StatStable()
//
//	Description:
//		put the campign, scenario, and mission IDs and Indecies into a stable
//		state.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	StatStable( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;

	// set the played field in the campaign data block
	g_CampaignIndex    = AiCampaignIndex( gpGame->CampaignID );
	if ( (g_CampaignIndex != -1) && (gpGame->GameType == GAMETYPE_ONEPLAYER) )
	{
		pCampaign          = g_Campaigns[ g_CampaignIndex ];
		g_ScenarioIndex    = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
		pScenario          = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
		g_MissionIndex     = AiMissionIndex( pScenario, gpGame->MissionID );
	}
	else
	{
		g_CampaignIndex    = 0;
		g_ScenarioIndex    = 0;
		g_MissionIndex     = 0;
		pCampaign          = g_Campaigns[ g_CampaignIndex ];
		gpGame->CampaignID = pCampaign->nCampaignID;
		pScenario          = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
		gpGame->ScenarioID = pScenario->nScenarioID;
		pMission           = &(pScenario->pMissions[ g_MissionIndex ]);
		gpGame->MissionID  = pMission->nMissionID;
	}
}

//========================================================================
//	Function:		StatGetPlayerNameIndex()
//
//	Description:
//		return the current playerName index.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

int	StatGetPlayerNameIndex( void )
{
	return( STATplayerIndex );
}

//========================================================================
//	Function:		StatSetPlayerNameIndex()
//
//	Description:
//		set the current playerName index.
//
//	Input:			nPlayerNameIndex		// player name index to set as current
//
//	Ouput:			none
//
//========================================================================

void	StatSetPlayerNameIndex( int nPlayerNameIndex )
{
	STATplayerIndex = nPlayerNameIndex;
//	StatUpdate( STAT_CURRENT_PLAYER_INDEX, STAT_UPDATE_PLAYER_NAME, FALSE );
}

//========================================================================
//	Function:		StatLoad()
//
//	Description:
//		load or read in the armymen statistics data from a .ASF
//		( Armymen SAVE File ) file.
//
//	Input:			nMissionID		mission stats relate to
//
//	Ouput:			none
//
//========================================================================
/*
// currently not in use
void	StatLoad( USHORT nMissionID )
{
	char	ASFname[STAT_MAX_REF_LEN+1];
	STATS*	pMissionStats = &(STATprevious);

	// build the potential .ASF filename
	if ( strncmp( STATcurrentName, NEWPLAYER_TextBtn, NEWPLAYER_BtnSize ) == 0 )
		TRACE( "WARNING: New Player has no stats data\n" );
	else
	{
		sprintf( ASFname, "%s_%d.asf", STATcurrentName, nMissionID );
		StatRead( pMissionStats, ASFname );
	}
}
*/

//========================================================================
//	Function:		StatUpdate()
//
//	Description:
//		update the player stats data by player name index
//
//	Input:			nPlayerNameIndex	index into the stats data block
//					bFlags				special case update flags
//					bWrite				write the update data out
//
//	Ouput:			none
//
//========================================================================

void	StatUpdate( int nPlayerNameIndex, int bFlags, BOOL bWrite )
{
	int		nIndex;
	LPCTSTR pNameKey;
    char*   pDataBuffer;
	ULONG	dwSize;
	STATS*	pMissionStats;

	// are we reading or writing
	if ( bWrite )
	{
		// start by checking the bit fields of the update global
		if ( (bFlags & STAT_UPDATE_PLAYER_NAME) == STAT_UPDATE_PLAYER_NAME )
		{
			if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
			{
				// copy the current player name into the permanent set
				nIndex = StatGetPlayerNameIndex();
				strcpy( STATplayerNames[ nIndex ], STATcurrentName );
			}
			else
			{
				// acquire the player name key and retreive the StatPlayer string from the registry
				pNameKey    = STATnameKey[ nPlayerNameIndex ];
				pDataBuffer = STATplayerNames[ nPlayerNameIndex ];
				dwSize      = strlen( pDataBuffer );

				// remember we're outputing an ascii string, use the ascii write
				// version of RegSet - RegSetA
				gpComm->RegSetA(pNameKey, (CONST BYTE *)pDataBuffer, dwSize);
			}
		}
	}
	else
	{
		// start by checking the bit fields of the update global
		if ( (bFlags & STAT_UPDATE_PLAYER_NAME) == STAT_UPDATE_PLAYER_NAME )
		{
			if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
			{
				// acquire the player name key and string name
				nIndex = StatGetPlayerNameIndex();
				strcpy( STATcurrentName, STATplayerNames[ nIndex ] );
			}
			else
			{
				// acquire the player name key and retreive the StatPlayer string from the registry
				pNameKey    = STATnameKey[ nPlayerNameIndex ];
				pDataBuffer = STATplayerNames[ nPlayerNameIndex ];
				dwSize      = SBTN_MAX_PLAYER_NAME_LEN;

				// now read in the player name from the registry
				gpComm->RegGet(pNameKey, (LPBYTE)pDataBuffer, &dwSize);
			}
		}

		if ( (bFlags & STAT_UPDATE_PLAYER_STATS) == STAT_UPDATE_PLAYER_STATS )
		{
			if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
			{
				pMissionStats = &STATplayer;

				// load the current stats data from the game
				pMissionStats->nMissionID         = gpGame->MissionID;					// mission UID (see .CPN file)
				pMissionStats->nSurvivingTroops   = ArmySurvivingTroops( ARMY_PLAYER );
				pMissionStats->nCasualties        = ArmyCasualties( ARMY_PLAYER );
				pMissionStats->nVehicleCasualties = ArmyVehicleCasualties( ARMY_PLAYER );
				pMissionStats->nTroopsKilled      = ArmyTroopsKilled( ARMY_PLAYER );
				pMissionStats->nVehiclesKilled    = ArmyVehiclesKilled( ARMY_PLAYER );
				pMissionStats->nSargeKills        = ArmySargeKills( ARMY_PLAYER  );
				pMissionStats->nPerformance       = ArmyPerformance( ARMY_PLAYER );
				pMissionStats->nSargeDeaths       = ArmySargeDeaths( ARMY_PLAYER );
				pMissionStats->nSargesKilled      = ArmySargesKilled( ARMY_PLAYER );
			}
		}
	}

}

//========================================================================
//	Function:		StatSave()
//
//	Description:
//		save the existing stats data to the .ASF ( Armymen Statistics File ) file.
//
//	Input:			nPlayerNameIndex	player name index whose data is to be saved
//
//	Ouput:			none
//
//========================================================================

void	StatSave( int nPlayerNameIndex, USHORT nMissionID )
{
	FILE*	statFile;
	char	ASFname[STAT_MAX_REF_LEN+1];
	long	nStatSize;
	long	nStatID = STAT_ID;
	STATS*	pMissionStats = &(STATplayer);

	if (gpGame->cdBoot)
		return;

	// first update the missions played data
//	sprintf( ASFname, "%s.asf", STATplayerNames[ nPlayerNameIndex ] );
//	StatSaveCompletedMissions( ASFname, gpGame->CampaignID, nMissionID );

	// build the .ASF filename from the playername and mission id
	sprintf( ASFname, "%s_%d.asf", STATplayerNames[ nPlayerNameIndex ], nMissionID );

	// make sure the stats data has been fully updated
	StatUpdate( nPlayerNameIndex, STAT_UPDATE_PLAYER_NAME, FALSE );
	StatUpdate( STAT_CURRENT_PLAYER_INDEX, STAT_UPDATE_PLAYER_STATS, FALSE );

	// open the file
	SetPath(SAVE_PATH);
	statFile = fopen( ASFname, "wb" );
	if ( statFile == NULL )
	{
		TRACE( "ERROR: failed to open .ASF file (%s)\n", ASFname );
		return;
	}

	// output the chunk header
	nStatSize = sizeof( STATS );
	CHUNK_WRITE_LONG( statFile, &nStatID );
	CHUNK_WRITE_LONG( statFile, &nStatSize );

	// now write the data to the file
	CHUNK_WRITE_BUFFER( statFile, pMissionStats, sizeof( STATS ) );

	// now apply the mission data
	ArmyMissionSave( statFile );

	// now close the file
	fclose( statFile );
}


//========================================================================
//	Function:		StatSaveNext()
//
//	Description:
//		save the existing stats data to the .ASF ( Armymen Statistics File ) file
//			for the next mission
//
//	Input:			nPlayerNameIndex	player name index whose data is to be saved
//
//	Ouput:			none
//
//========================================================================

void	StatSaveNext( int nPlayerNameIndex, USHORT nCampaignID, USHORT nMissionID, BOOL increment_loss )
{
	char	ASFname[STAT_MAX_REF_LEN+1];

	// first update the missions played data
	sprintf( ASFname, "%s.asf", STATplayerNames[ nPlayerNameIndex ] );
	StatSaveCompletedMissions( ASFname, nCampaignID, nMissionID, increment_loss );
}

//========================================================================
//	Function:		StatLoadCompletedMissions()
//
//	Description:
//		load the mission completed data
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	StatLoadCompletedMissions( void )
{
	FILE*			statFile;
	char			ASFname[STAT_MAX_REF_LEN+1];
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	STAT_ID_RECORD	stats[STAT_MAX_RECORDS+1];
	int				nCampaign;
	int				nScenario;
	int				nMission;
	int				nPlayerNameIndex;
	long			nStatSize;
	long			nRecords;
	long			nStatID = STAT_ID;
	STATS*			pMissionStats = &(STATplayer);

	ZeroMemory( stats, sizeof( STAT_ID ) * (STAT_MAX_RECORDS+1) );

	// open the file for reading first
	nRecords = 0;
	nPlayerNameIndex = StatGetPlayerNameIndex();
	sprintf( ASFname, "%s.asf", STATplayerNames[ nPlayerNameIndex ] );
	SetPath(SAVE_PATH);
	statFile = fopen( ASFname, "rb" );
	if ( statFile != NULL )
	{
		// read in the data
		if ( ChunkFind( statFile, STRC_ID ) )
		{
			// read in the chunk size
			CHUNK_READ_LONG( statFile, &nStatSize );

			// now read in the stats data
			while( !feof( statFile) && nStatSize )
			{
				// read in a mission record
				CHUNK_READ_SHORT( statFile, &(stats[nRecords].nID) );
				nStatSize -= sizeof(USHORT);
				CHUNK_READ_BYTE( statFile, &(stats[nRecords].bVisible) );
				nStatSize -= sizeof(BYTE);
				CHUNK_READ_BYTE( statFile, &(stats[nRecords].nFailed) );
				nStatSize -= sizeof(BYTE);
				++nRecords;
			}
		}

		// close the data file
		fclose( statFile );
	}

#if 0
	TRACE( "StatLoadCompletedMissions(): %d records\n", nRecords );
	for( nMission=0; nMission<nRecords; ++nMission )
	{
		TRACE( "record #%d: nID=%d bVisible=", nMission, stats[nMission].nID );
		if ( (stats[nMission].bVisible & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
			TRACE( "NEXT" );
		else
		if ( (stats[nMission].bVisible & STAT_PLAYED_FLAG) == STAT_PLAYED_FLAG )
			TRACE( "PLAYED" );
		else
		if ( (stats[nMission].bVisible & STAT_VISIBLE_FLAG) == STAT_VISIBLE_FLAG )
			TRACE( "VISIBLE" );
		else
		if ( stats[nMission].bVisible == STAT_DISABLED_FLAG )
			TRACE( "DISABLED" );
		TRACE( "\n" );
	}
#endif

	// set the visible field in the campaign data block
	for( nCampaign=0; nCampaign<g_NumberCampaigns; ++nCampaign )
	{
		pCampaign = g_Campaigns[nCampaign];
		if ( pCampaign )
		{
			StatSetCampaignVisibility( pCampaign, stats, nRecords );
			for( nScenario=0; nScenario<pCampaign->nNumberScenarios; ++nScenario )
			{
				pScenario = &(pCampaign->pScenarios[ nScenario ]);
				if ( pScenario )
				{
					StatSetScenarioVisibility( pScenario, stats, nRecords );
					for( nMission=0; nMission<pScenario->nNumberMissions; ++nMission )
					{
						pMission = &(pScenario->pMissions[ nMission ]);
						if ( pMission )
						{
							StatSetMissionVisibility( pMission, stats, nRecords );
							StatSetMissionFailures( pMission, stats, nRecords );
						}
					}
				}
			}
		}
	}

#if 0
	AiDumpVisibility();
#endif

	if ( pMainFrame->m_bScenariosVisible )
		StatMakeAllVisible();

#ifdef VISIBILITY_DEBUG
	TRACE( "StatLoadCompletedMissions()\n" );
	AiDumpVisibility();
#endif
}

//========================================================================
//	Function:		StatSaveCompletedMissions()
//
//	Description:
//		save the mission completed data
//
//	Input:			ASFname		data filename to update
//
//	Ouput:			none
//
//========================================================================

void	StatSaveCompletedMissions( char* ASFname, USHORT nCampaignID, USHORT nMissionID, BOOL increment_loss )
{
	FILE*			statFile;
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	STAT_ID_RECORD	stats[STAT_MAX_RECORDS+1];
	BOOL			bCampaignFound;
	BOOL			bMissionFound;
	BOOL			bFound;
	long			nStatSize;
	long			nIndex;
	long			nRecords;
	long			nStatID = STAT_ID;
	STATS*			pMissionStats = &(STATplayer);
//	BYTE			cDummy=(BYTE)0xFF;

	if (gpGame->cdBoot)
		return;

	ZeroMemory( stats, sizeof( STAT_ID ) * (STAT_MAX_RECORDS+1) );

	// open the file for reading first
	SetPath(SAVE_PATH);
	statFile = fopen( ASFname, "rb" );
	nRecords = 0;
	if ( statFile != NULL )
	{
		// read in the data
		if ( ChunkFind( statFile, STRC_ID ) )
		{
			// read in the chunk size
			CHUNK_READ_LONG( statFile, &nStatSize );

			// now read in the stats data
			while( !feof( statFile) && nStatSize )
			{
				// read in a mission record
				CHUNK_READ_SHORT( statFile, &(stats[nRecords].nID) );
				nStatSize -= sizeof(USHORT);
				CHUNK_READ_BYTE( statFile, &(stats[nRecords].bVisible) );
				nStatSize -= sizeof(BYTE);
				CHUNK_READ_BYTE( statFile, &(stats[nRecords].nFailed) );
				nStatSize -= sizeof(BYTE);
				++nRecords;
			}
		}

		// close the data file
		fclose( statFile );
	}

	// set the played field in the campaign data block
	nIndex             = AiCampaignIndex( nCampaignID );
	ASSERT ( nIndex != -1 );
	pCampaign          = g_Campaigns[ nIndex ];
	nIndex             = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
	ASSERT ( nIndex != -1 );
	pScenario          = &(pCampaign->pScenarios[ nIndex ]);
	nIndex             = AiMissionIndex( pScenario, nMissionID );
	ASSERT ( nIndex != -1 );
	pMission           = &(pScenario->pMissions[ nIndex ]);

	// now see if this ID is in the record block
	nIndex         = 0;
	bFound         = FALSE;
	bCampaignFound = FALSE;
	bMissionFound  = FALSE;
	while( !bFound && (nIndex < nRecords) )
	{
		if ( stats[ nIndex ].nID == nCampaignID )
		{
			// update the visible data
			stats[ nIndex ].bVisible = pCampaign->bVisible;
			bCampaignFound           = TRUE;
		}
//		else
//		if ( stats[ nIndex ].nID == pScenario->nScenarioID )
//		{
//			// update the visible data
//			stats[ nIndex ].bVisible = pScenario->bVisible;
//		}
		else
		if ( stats[ nIndex ].nID == nMissionID )
		{
			// update the visible data
			stats[ nIndex ].bVisible = pMission->bVisible;
			if (increment_loss)	{
				pMission->nFailed++;
				stats[ nIndex ].nFailed = pMission->nFailed;
			}
			bMissionFound            = TRUE;
		}

		if ( bCampaignFound && bMissionFound )
			bFound = TRUE;
		else
			++nIndex;
	}

	// see if this is a new record
	if ( !bCampaignFound && (nIndex < STAT_MAX_RECORDS) )
	{
		stats[ nIndex ].nID      = pCampaign->nCampaignID;
		stats[ nIndex ].bVisible = pCampaign->bVisible;
		++nIndex;
		++nRecords;
	}
	if ( !bMissionFound && (nIndex < STAT_MAX_RECORDS) )
	{
		stats[ nIndex ].nID      = pMission->nMissionID;
		stats[ nIndex ].bVisible = pMission->bVisible;
		if (increment_loss)
			pMission->nFailed++;
		stats[ nIndex ].nFailed = pMission->nFailed;
		++nRecords;
	}

#if 0
	TRACE( "StatSaveCompletedMissions(): %d records\n", nRecords );
	for( nIndex=0; nIndex<nRecords; ++nIndex )
	{
		TRACE( "record #%d: nID=%d bVisible=", nIndex, stats[nIndex].nID );
		if ( (stats[nIndex].bVisible & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
			TRACE( "NEXT" );
		else
		if ( (stats[nIndex].bVisible & STAT_PLAYED_FLAG) == STAT_PLAYED_FLAG )
			TRACE( "PLAYED" );
		else
		if ( (stats[nIndex].bVisible & STAT_VISIBLE_FLAG) == STAT_VISIBLE_FLAG )
			TRACE( "VISIBLE" );
		else
		if ( stats[nIndex].bVisible == STAT_DISABLED_FLAG )
			TRACE( "DISABLED" );
		TRACE( "\n" );
	}
#endif

	// open the file for writing
	SetPath(SAVE_PATH);
	statFile = fopen( ASFname, "wb" );
	if ( statFile != NULL )
	{
		// output the chunk header
		nStatSize = sizeof( STAT_ID_RECORD ) * nRecords;
		nStatID = STRC_ID;
		CHUNK_WRITE_LONG( statFile, &nStatID );
		CHUNK_WRITE_LONG( statFile, &nStatSize );

		// write out the data
		for( nIndex=0; nIndex<nRecords; ++nIndex )
		{
			// write out a mission record
			CHUNK_WRITE_SHORT( statFile, &(stats[nIndex].nID) );
			CHUNK_WRITE_BYTE( statFile, &(stats[nIndex].bVisible) );
			CHUNK_WRITE_BYTE( statFile, &(stats[nIndex].nFailed) );
		}

		// close the data file
		fclose( statFile );
	}
}

//========================================================================
//	Function:		StatClear()
//
//	Description:
//		clear the player stats data by player name index
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	StatClear( void )
{
	// copy the new data over the old data
	memcpy( (void*)&(STATplayer), (void*)&STATemptyDataBlock, sizeof( STATS ) );
}

//------------------------------------------------------------------------
//				STATS Support Routines
//------------------------------------------------------------------------

///========================================================================
//	Function:		StatSetCampaignVisibility()
//
//	Description:
//		set the visibility attributes of the passed in campaign data
//
//	Input:			pCampaign	AI campaign data
//					pStats		Stats complete block
//
//	Ouput:			none
//
//========================================================================

void	StatSetCampaignVisibility( CAMPAIGNREF* pCampaign, STAT_ID_RECORD* pStats, int nRecords )
{
	BOOL	bVisibility = 0;

	if ( StatFindVisibility( pCampaign->nCampaignID, pStats, nRecords, &bVisibility ) )
		pCampaign->bVisible = bVisibility;
	if ( (bVisibility & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
		ArmySetCurrentCampaignID( pCampaign->nCampaignID );
}

///========================================================================
//	Function:		StatSetScenarioVisibility()
//
//	Description:
//		set the visibility attributes of the passed in scenario data
//
//	Input:			pScenario	AI scenario data
//					pStats		Stats complete block
//
//	Ouput:			none
//
//========================================================================

void	StatSetScenarioVisibility( SCENARIOREF* pScenario, STAT_ID_RECORD* pStats, int nRecords )
{
	BOOL	bVisibility = 0;

	if ( StatFindVisibility( pScenario->nScenarioID, pStats, nRecords, &bVisibility ) )
		pScenario->bVisible = bVisibility;
	if ( (bVisibility & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
		ArmySetCurrentScenarioID( pScenario->nScenarioID );
}

///========================================================================
//	Function:		StatSetMissionVisibility()
//
//	Description:
//		set the visibility attributes of the passed in mission data
//
//	Input:			pMission	AI mission data
//					pStats		Stats complete block
//
//	Ouput:			none
//
//========================================================================

void	StatSetMissionVisibility( MISSIONREF* pMission, STAT_ID_RECORD* pStats, int nRecords )
{
	BOOL	bVisibility = STAT_DISABLED_FLAG;

	if ( StatFindVisibility( pMission->nMissionID, pStats, nRecords, &bVisibility ) )
		pMission->bVisible = bVisibility;

//	if ( (bVisibility & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
//		ArmySetCurrentMissionID( pMission->nMissionID );
}

///========================================================================
//	Function:		StatSetMissionFailures()
//
//	Description:
//		set the the number of failures from the passed in mission data
//
//	Input:			pMission	AI mission data
//					pStats		Stats complete block
//
//	Ouput:			none
//
//========================================================================

void	StatSetMissionFailures( MISSIONREF* pMission, STAT_ID_RECORD* pStats, int nRecords )
{
	unsigned char nFailed = 0;

	if ( StatFindFailed( pMission->nMissionID, pStats, nRecords, &nFailed ) )
		pMission->nFailed = nFailed;
}

///========================================================================
//	Function:		StatFindVisibility()
//
//	Description:
//		set the visibility attributes of the passed in mission data
//
//	Input:			nID			campaign, scenario, or mission ID we're searching for
//					pStats		list of currently used IDs
//					nRecords	number or IDs in list
//
//	Ouput:			none
//
//========================================================================

BOOL	StatFindVisibility( USHORT nID, STAT_ID_RECORD* pStats, int nRecords, BOOL* bVisibility )
{
	STAT_ID_RECORD*	pRecord;
	int				nIndex  = 0;
	BOOL			bFound  = FALSE;

	// search the list of ID records for this ID
	*bVisibility = STAT_DISABLED_FLAG;
	pRecord = pStats;
	while ( !bFound && (nIndex<nRecords) )
	{
		if ( pRecord->nID == nID )
			bFound = TRUE;
		else
		{
			++pRecord;
			++nIndex;
		}
	}

	if ( bFound )
		*bVisibility = pRecord->bVisible;

	return( bFound );
}


///========================================================================
//	Function:		StatFindFailed()
//
//	Description:
//		find the failed value in the mission data
//
//	Input:			nID			campaign, scenario, or mission ID we're searching for
//					pStats		list of currently used IDs
//					nRecords	number or IDs in list
//
//	Ouput:			none
//
//========================================================================

BOOL	StatFindFailed( USHORT nID, STAT_ID_RECORD* pStats, int nRecords, unsigned char* pnFailed )
{
	STAT_ID_RECORD*	pRecord;
	int				nIndex  = 0;
	BOOL			bFound  = FALSE;

	// search the list of ID records for this ID
	pRecord = pStats;
	while ( !bFound && (nIndex<nRecords) )
	{
		if ( pRecord->nID == nID )
			bFound = TRUE;
		else
		{
			++pRecord;
			++nIndex;
		}
	}

	if ( bFound )
		*pnFailed = pRecord->nFailed;

	return( bFound );
}

//========================================================================
//	Function:		StatRead()
//
//	Description:
//		read the player stats data by player name index
//
//	Input:			nPlayerNameIndex	index into the stats data block
//
//	Ouput:			returns FALSE if sucessfully read stats
//
//========================================================================

BOOL	StatRead( STATS* pStatBuffer, char* pASFname )
{
	ULONG	lData;
	FILE*	statFile;
	BOOL	bError = TRUE;

	// start by opening the ASF file
	SetPath(SAVE_PATH);
	statFile = fopen( pASFname, "rb" );
	if ( statFile == NULL )
	{
		return bError;
	}

	// now locate the STAT chunk
	if ( !ChunkFind( statFile, STAT_ID ) )
	{
		TRACE( "ERROR: failed to find STAT chunk [%s:%d]\n", __FILE__, __LINE__ );
	}
	else	// now read in the stat data
	{
		lData = sizeof( STATS );
		if ( bError = ChunkRead( statFile, (void*)pStatBuffer, &lData ) )
			TRACE( "ERROR: failed to read STAT chunk [%s:%d]\n", __FILE__, __LINE__ );
	}
	fclose( statFile );

	return bError;
}

//========================================================================
//	Function:		StatCheckForMission()
//
//	Description:
//		read the player stats data by player name index
//
//	Input:			nPlayerNameIndex	index into the stats data block
//					nMissionID			unique ID for mission
//
//	Ouput:			none
//
//========================================================================

STATS*	StatCheckForMission( int nPlayerNameIndex, USHORT nMissionID )
{
	char	ASFname[STAT_MAX_REF_LEN+1];
	STATS*	pMissionStats = &(STATprevious);

	// build the .ASF filename
	if ( strcmp( STATplayerNames[ nPlayerNameIndex ], NEWPLAYER_TextBtn ) == 0 )
		TRACE( "WARNING: New Player has no stats data\n" );
	else
	{
		sprintf( ASFname, "%s_%d.asf", STATplayerNames[ nPlayerNameIndex ], nMissionID );

		// read in the stats data
		if (StatRead( pMissionStats, ASFname ))
			pMissionStats = NULL;
	}

	// look for this mission in the stat data
	if ( pMissionStats )
	{
		if ( pMissionStats->nMissionID != nMissionID )
			pMissionStats = NULL;
	}

	return( pMissionStats );
}

//========================================================================
//	Function:		StatCheckForSavedMission()
//
//	Description:
//		check for the exisitence of a saved .ASF file
//
//	Input:			nPlayerNameIndex	index into the stats data block
//
//	Ouput:			none
//
//========================================================================

BOOL	StatCheckForSavedMission( char* ASFname )
{
	FILE* statFile;
	BOOL	bNotSaved = TRUE;

	SetPath(SAVE_PATH);
	statFile = fopen( ASFname, "rb" );
	if ( statFile )
	{
		bNotSaved = FALSE;
		fclose( statFile );
	}

	return( bNotSaved );
}

///========================================================================
//	Function:		StatSurvivingTroops
//	Description:	retrieve the number of surving units for a given PlayerNameIndex
///========================================================================
int StatSurvivingTroops( int nPlayerNameIndex )		// number of units alive at end of mission
{
	STATS*	pMissionStats;

	if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
		pMissionStats = &(STATplayer);
	else
		pMissionStats = &(STATprevious);

	return( pMissionStats->nSurvivingTroops );
}


///========================================================================
//	Function:		StatCasualties
//	Description:	retrieve the number of casulaties for a given PlayerNameIndex
///========================================================================
int StatCasualties( int nPlayerNameIndex )
{
	STATS*	pMissionStats;

	if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
		pMissionStats = &(STATplayer);
	else
		pMissionStats = &(STATprevious);

	return( pMissionStats->nCasualties );
}


///========================================================================
//	Function:		StatVehicleCasualties
//	Description:	retrieve the number of vehicle casulaties for a given PlayerNameIndex
///========================================================================
int StatVehicleCasualties( int nPlayerNameIndex )
{
	STATS*	pMissionStats;

	if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
		pMissionStats = &(STATplayer);
	else
		pMissionStats = &(STATprevious);

	return( pMissionStats->nVehicleCasualties );
}


///========================================================================
//	Function:		StatTroopsKilled
//	Description:	retrieve the number of troops killed for a given PlayerNameIndex
///========================================================================
int StatTroopsKilled( int nPlayerNameIndex )			// number of troopers killed
{
	STATS*	pMissionStats;

	if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
		pMissionStats = &(STATplayer);
	else
		pMissionStats = &(STATprevious);

	return( pMissionStats->nTroopsKilled );
}


///========================================================================
//	Function:		StatVehiclesKilled
//	Description:	retrieve the number of vehicles killed for a given PlayerNameIndex
///========================================================================
int StatVehiclesKilled( int nPlayerNameIndex )
{
	STATS*	pMissionStats;

	if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
		pMissionStats = &(STATplayer);
	else
		pMissionStats = &(STATprevious);

	return( pMissionStats->nVehiclesKilled );
}


///========================================================================
//	Function:		StatSargeKills
//	Description:	retrieve the number of kills by an armys Sarge for a given PlayerNameIndex
///========================================================================
int StatSargeKills( int nPlayerNameIndex )			// kills by Sarge
{
	STATS*	pMissionStats;

	if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
		pMissionStats = &(STATplayer);
	else
		pMissionStats = &(STATprevious);

	return( pMissionStats->nSargeKills );
}


///========================================================================
//	Function:		StatPerformance
//	Description:	retrieve the par points for a given PlayerNameIndex
///========================================================================
int StatPerformance( int nPlayerNameIndex )				// expected score for this mission
{
	STATS*	pMissionStats;

	if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
		pMissionStats = &(STATplayer);
	else
		pMissionStats = &(STATprevious);

	return( pMissionStats->nPerformance );
}


///========================================================================
//	Function:		StatSargeDeaths
//	Description:	retrieve the number of times sarge was killed (MP)
///========================================================================
int StatSargeDeaths( int nPlayerNameIndex )
{
	STATS*	pMissionStats;

	if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
		pMissionStats = &(STATplayer);
	else
		pMissionStats = &(STATprevious);

	return( pMissionStats->nSargeDeaths );
}

///========================================================================
//	Function:		StatSargesKilled
//	Description:	retrieve the number of sarges killed (MP)
///========================================================================
int StatSargesKilled( int nPlayerNameIndex )
{
	STATS*	pMissionStats;

	if ( nPlayerNameIndex == STAT_CURRENT_PLAYER_INDEX )
		pMissionStats = &(STATplayer);
	else
		pMissionStats = &(STATprevious);

	return( pMissionStats->nSargesKilled );
}


//========================================================================
//	Function:		HaveSavedMission()
//
//	Description:
//		see if a saved mission (.ASF) exits
//
//	Input:			nPlayerNameIndex	index into the stats data block
//					nMissionID			unique ID for mission
//
//	Ouput:			none
//
//========================================================================

BOOL	HaveSavedMission( int nPlayerNameIndex, USHORT nMissionID )
{
	char	ASFname[STAT_MAX_REF_LEN+1];

	// build the .ASF filename
	if ( strcmp( STATplayerNames[ nPlayerNameIndex ], NEWPLAYER_TextBtn ) == 0 )
	{
		TRACE( "WARNING: New Player has no stats data\n" );
		return( FALSE );
	}
	else
	{
		// build the saved file name, based on the playerName and missionID
		sprintf( ASFname, "%s_%d.asf", STATplayerNames[ nPlayerNameIndex ], nMissionID );

		// NOTE: StatCheckForSavedMission returns FALSE for a saved file
		return( !StatCheckForSavedMission( ASFname ) );
	}
}

//========================================================================
//	Function:		StatsHaveName()
//
//	Description:
//		see if a saved mission (.ASF) exits
//
//	Input:			PlayerName		player name string for comparision
//
//	Ouput:			none
//
//========================================================================

BOOL	StatsHaveName( char* pPlayerName )
{
	int		nPlayerNameIndex;
	BOOL	bFound = FALSE;

	nPlayerNameIndex = 0;
	while( !bFound && (nPlayerNameIndex<STAT_MAX_PLAYERS) )
	{
		if ( stricmp( pPlayerName, STATplayerNames[ nPlayerNameIndex ] ) == 0 )
			bFound = TRUE;
		else
			++nPlayerNameIndex;
	}

	return( bFound );
}

//========================================================================
//	Function:		StatsDeleteName()
//
//	Description:
//		delete a Stats player name reference
//
//	Input:			PlayerName		player name string for comparision
//
//	Ouput:			none
//
//========================================================================

void	StatsDeleteName( char* pPlayerName )
{
	int		nPlayerNameIndex;
	BOOL	bFound = FALSE;

	nPlayerNameIndex = 0;
	while( !bFound && (nPlayerNameIndex<STAT_MAX_PLAYERS) )
	{
		if ( strcmp( pPlayerName, STATplayerNames[ nPlayerNameIndex ] ) == 0 )
			bFound = TRUE;
		else
			++nPlayerNameIndex;
	}
	if ( bFound )
	{
		*(STATplayerNames[ nPlayerNameIndex ]) = '\0';
	}
}

//========================================================================
//	Function:		StatMakeAllVisible()
//
//	Description:
//		set the visibility flag on all missions/scenarios/and campaigns
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	StatMakeAllVisible( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	int				nCampaign;
	int				nScenario;

	if ( g_NumberCampaigns > 0 )
	{
		for( nCampaign=0; nCampaign<g_NumberCampaigns; ++nCampaign )
		{
			pCampaign            = g_Campaigns[ nCampaign ];
			pCampaign->bVisible |= STAT_VISIBLE_FLAG;

			for( nScenario=0; nScenario<pCampaign->nNumberScenarios; ++nScenario )
			{
				pScenario            = &(pCampaign->pScenarios[ nScenario ]);
				pScenario->bVisible |= STAT_VISIBLE_FLAG;
				pMission             = &(pScenario->pMissions[ 0 ]);
				pMission->bVisible  |= STAT_VISIBLE_FLAG;
			}
		}
	}
	else
	{
		// tell load campaign to run make all visible when it loads
		g_NumberCampaigns = -1;
	}
}

//========================================================================
//	Function:		StatRestoreVisibility()
//
//	Description:
//		restore the visibility flag on all missions/scenarios/and campaigns
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	StatRestoreVisibility( void )
{
}

//========================================================================
//							EOF
//========================================================================
