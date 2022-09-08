//========================================================================
//	FILE:			$Workfile: Stats.h $
//
//	DESCRIPTION:	ArmyMen Statistics definitions.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, October 29, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Stats.h 15    4/03/98 4:19p Aburgess $
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
//  $Log: /ArmyMen/src/Stats.h $
//  
//  15    4/03/98 4:19p Aburgess
//  modifications to fix next mission bug
//  
//  14    3/16/98 12:32a Nrobinso
//  keep failed as part of saved stat data
//  
//  13    3/09/98 11:36a Nrobinso
//  remove unused
//  
//  12    2/05/98 3:26p Nrobinso
//  add real stats
//  
//  11    2/04/98 5:57p Nrobinso
//  add SetPath before getting stats file; change surviving units to
//  surviving troops
//  
//  10    12/15/97 1:19a Aburgess
//  modified parameters
//  
//  9     12/11/97 10:22a Aburgess
//  made StatDeleteName() accessible
//  
//  8     12/09/97 12:12p Phu
//  
//  7     12/05/97 9:54p Nrobinso
//  added StatSaveNext
//  
//  6     12/01/97 4:49p Aburgess
//  prototypes ofr make all missions visible
//  
//  5     11/20/97 11:56a Aburgess
//  stat ID record parameters
//  
//  4     11/11/97 3:01p Aburgess
//  added extern markers and new StatHaveName prototype
//  
//  3     11/11/97 8:50a Aburgess
//  added HaveSavedMission prototype.
//  
//  2     11/07/97 12:19p Aburgess
//  call to stablize ID and Indecies for campaign data
//  
//  1     11/06/97 9:27a Aburgess
//  Game Statistics Modules
//  
//  $Nokeywords:$
//========================================================================


#ifndef __STATS_H__
#define __STATS_H__


//------------------------------------------------------------------------
//				GENERAL STATS DEFINES
//------------------------------------------------------------------------
#define	STAT_MAX_REF_LEN			31
#define	STAT_MAX_PLAYERS			4

#define	STAT_CURRENT_PLAYER_INDEX	-1

#define	STAT_MAX_RECORDS			255

//------------------------------------------------------------------------
//				STATS FLAGS
//------------------------------------------------------------------------
#define	STAT_UPDATE_PLAYER_NAME		(char)0x01		// update the registry
#define	STAT_UPDATE_PLAYER_STATS	(char)0x02		// update the stats data

#define	STAT_DISABLED_FLAG			(BOOL)0x00		// undefined
#define	STAT_VISIBLE_FLAG			(BOOL)0x01		// visible
#define	STAT_PLAYED_FLAG			(BOOL)0x03		// visible and played
#define	STAT_NEXT_FLAG				(BOOL)0x05		// visible and next progression

//------------------------------------------------------------------------
//				STATS STRUCTURE
//------------------------------------------------------------------------
typedef struct	statsDef
{
	int		nMissionID;							// mission UID (see .CPN file)
	int		nSurvivingTroops;					// number of units alive at end of mission
	int		nCasualties;						// number of your troopers killed
	int		nVehicleCasualties;					// number of your vehicles killed
	int		nSargeKills;						// kills by Sarge
	int		nTroopsKilled;						// number of enemy troopers killed
	int		nVehiclesKilled;					// number of enemy vehicles killed
	int		nPerformance;						// expected score for this mission
	int		nSargeDeaths;						// number of deaths of your sarge
	int		nSargesKilled;						// number of deaths of all enemy sarges
} STATS;

typedef STATS*	HSTATS;

typedef	struct	statChunkDef
{
	ULONG	nChunkID;								// 'S','T','A','T'
	ULONG	nChunkSize;								// total size of chunk data
	STATS	dStats;									// stats data
} STAT_CHUNK;

typedef struct	statIDRecord
{
	USHORT	nID;
	char	bVisible;
	unsigned char	nFailed;
} STAT_ID_RECORD;

//========================================================================
//						DATA
//========================================================================
extern	char	STATplayerNames[ STAT_MAX_PLAYERS ][SBTN_MAX_PLAYER_NAME_LEN+1];	// player name strings data
extern	char	STATcurrentName[SBTN_MAX_PLAYER_NAME_LEN+1];						// player name strings data

//========================================================================
//						PROTOTYPES
//========================================================================
extern	BOOL	StatInit( void );
extern	void	StatExit( void );
extern	void	StatStable( void );
extern	void	StatLoad( USHORT nMissionID );
extern	void	StatUpdate( int nPlayerNameIndex, int bFlags, BOOL bWrite );
extern	void	StatSave( int nPlayerNameIndex, USHORT nMissionID );
extern	void	StatSaveNext( int nPlayerNameIndex, USHORT nCampaignID, USHORT nMissionID, BOOL increment_loss = FALSE );
extern	void	StatLoadCompletedMissions( void );
extern	void	StatSaveCompletedMissions( char* ASFname, USHORT nCampignID, USHORT nMissionID, BOOL increment_loss = FALSE );
extern	STATS*	StatCheckForMission( int nPlayerNameIndex, USHORT nMissionID );

extern	int		StatSurvivingTroops( int nPlayerNameIndex );	  // number of units alive at end of mission
extern	int		StatCasualties( int nPlayerNameIndex );		  // number of troopers killed
extern	int		StatSargeKills( int nPlayerNameIndex );		  // kills by Sarge
extern	int		StatPerformance( int nPlayerNameIndex );			  // expected score for this mission
extern	int		StatVehicleCasualties( int nPlayerNameIndex );
extern	int		StatTroopsKilled( int nPlayerNameIndex );
extern	int		StatVehiclesKilled( int nPlayerNameIndex );
extern	int		StatSargeDeaths( int nPlayerNameIndex );
extern	int		StatSargesKilled( int nPlayerNameIndex );

extern	int		StatGetPlayerNameIndex( void );
extern	void	StatSetPlayerNameIndex( int nPlayerNameIndex );

extern	BOOL	HaveSavedMission( int nPlayerNameIndex, USHORT nMissionID );
extern	BOOL	StatsHaveName( char* pPlayerName );
extern	void	StatsDeleteName( char* pPlayerName );
extern	void	StatMakeAllVisible( void );
extern	void	StatRestoreVisibility( void );


extern	void	StatIncrementLosses( int nPlayerNameIndex, USHORT nCampaignID, USHORT nMissionID );

#endif
//========================================================================
//							EOF
//========================================================================
