//========================================================================
//	FILE:			$Workfile: Army.cpp $
//
//	DESCRIPTION:	Text processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, July 02, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Army.cpp 255   4/17/98 7:21a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	ArmyInit()
//		Initialize the Army processing.
//	ArmyExit()
//		Terminate the Army processor.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Army.cpp $
//  
//  255   4/17/98 7:21a Bwilcox
//  traces now under scriptdebug
//  
//  254   4/16/98 11:57p Nrobinso
//  fix debug message
//  
//  253   4/16/98 4:39p Bwilcox
//  indented army normal save traces to make errors easier to see
//  
//  252   4/10/98 11:22a Bwilcox
//  
//  251   4/10/98 1:18a Bwilcox
//  
//  250   4/10/98 1:10a Bwilcox
//  keeping deadposition as unique data
//  
//  249   4/09/98 7:15p Dmaynard
//  Actually making the changes described in the previous check-in (forgot
//  to save  (DOH)
//  
//  248   4/09/98 6:40p Dmaynard
//  Fixed bug: When sarge was killed on a PAD the ItemUpdatePad was not
//  getting called, therefore the event system thought he was still on his
//  pad and he could get immediate credit for picking up another flag at
//  some else's base.
//  
//  247   4/08/98 8:39p Bwilcox
//  
//  246   4/08/98 8:18p Bwilcox
//  saving death status in game for units and vehicles
//  
//  245   4/07/98 6:12a Bwilcox
//  tad cleanup
//  
//  243   4/03/98 4:18p Aburgess
//  modifications to fix next mission bug
//  
//  242   4/02/98 11:39p Aburgess
//  modifications to support NEXT playable mission
//  
//  241   4/02/98 2:03p Phu
//  typecasting to prevent warnings
//  
//  240   4/02/98 10:26a Nrobinso
//  save air support
//  
//  239   4/01/98 5:22p Nrobinso
//  addd base air resources to current resources
//  
//  238   98/04/01 16:25 Dmaynard
//  Changed IRunArmy  per BRUCE TO TRY TO PREPARE FOR TWO HUMAN TWO
//  COMPUTER PLAYERS.
//  
//  237   4/01/98 1:31p Bwilcox
//  CHANGE LOCAL TEST
//  
//  236   4/01/98 12:28p Bwilcox
//  IRunArmy changed
//  
//  235   3/31/98 5:41p Bwilcox
//  
//  234   3/31/98 5:35p Bwilcox
//  
//  233   3/29/98 11:17p Bwilcox
//  FIXED PARATROOPER UNIT CREATION DATA
//  
//  232   3/29/98 1:29a Nrobinso
//  don't save sarge's ammo separately
//  
//  231   3/28/98 11:52p Nrobinso
//  test for proper number of units being written out
//  
//  230   3/28/98 7:14a Bwilcox
//  multiplayer-mode easter egg. Enjoy. Best Regards, The AI Guru
//  
//  229   3/27/98 7:15p Bwilcox
//  cheats and script settings cleared on mission startup
//  
//  228   3/26/98 11:01a Nrobinso
//  have last mission in a scenario automatically go on to the next mission
//  
//  227   3/26/98 10:23a Nrobinso
//  look for saved games in save path
//  
//  226   3/26/98 9:21a Nrobinso
//  remove unused
//  
//  225   3/26/98 6:42a Bwilcox
//  blowitem added to header, added when weapon is unplaced
//  
//  224   3/25/98 6:09p Phu
//  flag frags
//  
//  223   3/24/98 12:08p Nrobinso
//  remove unused
//  
//  222   3/23/98 1:00a Nrobinso
//  handle saving of non-existant armies
//  
//  221   3/22/98 3:16p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  220   3/22/98 1:30p Bwilcox
//  
//  219   3/19/98 7:57p Dmaynard
//  Fixed Bug in ArmyDelete.  Don't delete the comm data structures for
//  players just because we are deleting the armies at the end of the first
//  multi-player game.  Only delete comm if this player is leaving via the
//  event/script "tanarmyleaving" mechanisms.
//  
//  218   3/19/98 2:35p Dmaynard
//  Added TIMEOUT for players in Release Builds ONLY.  If we don't hear
//  from a player for 30 seconds we remove the player.
//  
//  217   3/19/98 1:46p Nrobinso
//  remove unused
//  
//  216   3/18/98 9:32p Bwilcox
//  
//  215   3/18/98 9:22p Bwilcox
//  
//  214   3/18/98 8:50p Bwilcox
//  added traces for save and restore(into vehicles)
//  
//  213   3/18/98 1:02p Bwilcox
//  dont save out armies that dont exist. Load will allow you to skip army
//  
//  212   3/17/98 6:06p Bwilcox
//  proper null checking around aiitemfind calls
//  
//  211   3/17/98 12:39p Bwilcox
//  when army gets deleted, delete stratmap elements
//  
//  210   3/16/98 12:11p Bwilcox
//  adding paratroop dop box count also
//  
//  209   3/16/98 12:22a Nrobinso
//  add auto tuning based on failures in a mission
//  
//  208   3/14/98 3:11p Nrobinso
//  move function header
//  
//  207   3/13/98 11:29a Nrobinso
//  always set sarge anim type
//  
//  206   3/09/98 6:01p Bwilcox
//  
//  205   3/09/98 11:25a Nrobinso
//  don't set mission visibility if running off the CD
//  
//  204   3/08/98 1:23p Phu
//  change fixed_trans_table generation
//  
//  203   3/08/98 1:02a Nrobinso
//  oops, check to make sure it is a legit type
//  
//  202   3/08/98 1:00a Nrobinso
//  maintain a count of sarge types based on weapons he can pick up
//  
//  201   3/06/98 4:14p Phu
//  loading bar
//  
//  200   3/05/98 4:56p Aburgess
//  added routine to check specifically for scenario end to play SMK videos
//  
//  199   2/27/98 10:03p Bwilcox
//  fixing unitinitaial deploy for vehicles
//  
//  198   2/27/98 7:05p Nrobinso
//  save if unit or sarge is in a vehicle
//  
//  197   2/25/98 3:15p Nrobinso
//  save sarge & vehicle health
//  
//  196   2/24/98 11:44a Bwilcox
//  all pads now updated after movement completes to avoid bugs from
//  undeploy in script
//  
//  195   2/18/98 2:24p Bwilcox
//  stop air recon from using allah mode to do its dirty work
//  
//  194   2/17/98 3:02p Nrobinso
//  put debug commands on final compile flag
//  
//  193   2/12/98 1:32p Bwilcox
//  labelling paratroopers
//  
//  192   2/11/98 10:48a Dmaynard
//  Fixed bug in replay of multiplayer game when one player left the
//  session in the first game.
//  
//  191   2/09/98 10:42a Nrobinso
//  fix sargeskiled routine typo
//  
//  190   2/05/98 3:25p Nrobinso
//  add stats
//  
//  189   2/05/98 12:35p Phu
//  flaming plastic
//  
//  188   2/05/98 10:05a Bwilcox
//  
//  187   2/04/98 5:54p Nrobinso
//  track troopers & units killed
//  
//  186   2/04/98 12:03p Bwilcox
//  adjusted use of armymax units
//  
//  185   2/03/98 9:27p Nrobinso
//  fix save/restore for sargeless army
//  
//  184   2/03/98 8:32p Nrobinso
//  switch to troopers instead of units
//  
//  183   2/03/98 4:50p Nrobinso
//  add ammo restore
//  
//  182   2/03/98 4:30p Nrobinso
//  restore changed objects
//  
//  181   2/03/98 4:17p Nrobinso
//  save & restore all armies
//  
//  180   2/02/98 3:36p Aburgess
//  attempt to fix the NEXT AIVALABLY
//  
//  179   2/01/98 10:54p Nrobinso
//  FINAL not _FINAL is the fina versionl compile flag
//  
//  178   2/01/98 5:32p Nrobinso
//  fix restore game bug
//  
//  177   1/30/98 1:12p Bwilcox
//  fixing hiding of flags in multiplayer bug
//  
//  176   1/29/98 4:19p Bwilcox
//  check for assets before discarding army on satartu[
//  
//  175   1/28/98 1:25p Bwilcox
//  fixed load/free stuff
//  
//  174   1/28/98 1:01p Bwilcox
//  fixed drop bug for sarge in armydelete
//  
//  173   1/27/98 4:35p Bwilcox
//  sarge drops weapons before being deleted in armydelete
//  
//  172   1/27/98 3:11p Bwilcox
//  no more curselectedunit if own army goes away
//  
//  171   1/27/98 2:37p Bwilcox
//  puff away dead forces
//  
//  170   1/27/98 1:21p Bwilcox
//  no army update calls if army not playing
//  
//  169   1/27/98 1:06p Bwilcox
//  finishing armydelete adjustments for multiplayer
//  
//  168   1/27/98 12:18p Bwilcox
//  removeditems of army when army delete
//  
//  167   1/27/98 11:26a Bwilcox
//  
//  166   1/27/98 11:24a Bwilcox
//  aix dead code removal. spawned ArmiesDelete from ArmyDelete
//  
//  165   1/25/98 4:55a Bwilcox
//  paracount added for aai files
//  
//  164   1/22/98 6:43p Nrobinso
//  use SetPath
//  
//  163   98/01/22 18:13 Dmaynard
//  
//  162   98/01/22 18:01 Dmaynard
//  
//  161   1/21/98 1:44p Phu
//  fix paratrooper initialization
//  
//  160   1/20/98 5:50p Bwilcox
//  fix excess troops generated for paratroopers
//  
//  159   1/09/98 6:33p Nrobinso
//  add ArmyUpdatePads; put up error box if no sarge
//  
//  158   1/08/98 7:35p Phu
//  paratroopers
//  
//  157   1/08/98 4:19p Phu
//  air support items/paratrooper initialization
//  
//  156   1/08/98 1:52p Phu
//  mp airsupport
//  
//  155   1/07/98 7:43p Phu
//  
//  154   1/07/98 1:42p Aburgess
//  adjusted access of campaign data to use g_numbercampaigns rather than
//  AI_MAX_CAMPAIGNS
//  
//  153   98/01/07 13:29 Dmaynard
//  
//  152   98/01/07 13:20 Dmaynard
//  fix multi-player deployment
//  
//  151   1/07/98 12:41p Phu
//  potential fix to army allocation in multi-player mode
//  
//  150   1/07/98 12:29p Phu
//  Multi-color dash
//  
//  149   1/06/98 6:22p Phu
//  don't deploy forces if player is not in game
//  
//  148   12/23/97 7:38p Nrobinso
//  deal with less than the max number of campaigns
//  
//  147   12/16/97 12:12p Aburgess
//  Campaign Select only processes NextAdvance data for Scenarios and
//  Missions, ovoiding overwrite of CampignIndex when Saved data is present
//  
//  146   12/15/97 1:03a Aburgess
//  corrected mission/campaign transitions
//  
//  145   12/11/97 1:49p Aburgess
//  added ArmySetCurrentCampaignID, ArmySetCurrentScenarioID, and
//  ArmySetCurrentMissionID
//  
//  144   12/11/97 10:49a Aburgess
//  put AiDumpCPN into compile time flags and removed superfluous
//  STAT_VISIBLE_FLAG settings when STAT_NEXT_FLAG applied
//  
//  143   12/11/97 10:17a Aburgess
//  expanded bVisible in Campaigns, Scenarios, and Missions to be flags
//  
//  142   12/10/97 9:28p Bwilcox
//  
//  141   12/10/97 8:59p Bwilcox
//  
//  140   12/10/97 8:46p Bwilcox
//  
//  139   97/12/10 20:08 Dmaynard
//  
//  138   97/12/10 19:51 Dmaynard
//  
//  137   97/12/10 19:24 Dmaynard
//  traces around death
//  
//  136   12/09/97 1:00p Aburgess
//  commented out superfluous MissionMsgFront call
//  
//  135   12/09/97 12:11p Phu
//  
//  134   12/07/97 5:46p Bwilcox
//  
//  133   12/07/97 3:33p Bwilcox
//  fixing god mode redraw all bug
//  
//  132   12/07/97 2:29p Nrobinso
//  don't save a muliplayer game; check for null item label befor esaving
//  it
//  
//  131   12/07/97 11:29a Nrobinso
//  save ammo
//  
//  130   12/06/97 1:09p Nrobinso
//  deploy saved forces before restoring object info
//  
//  129   12/05/97 11:00p Nrobinso
//  make ArmyGetMission work multiplayer
//  
//  128   12/05/97 10:07p Aburgess
//  ArmyApplyNextAdvance now does a stat mission ID save
//  
//  127   12/05/97 9:50p Nrobinso
//  removed mission info from the_map; fixed when mission data is setup;
//  added sarge & vehicles to save data
//  
//  126   12/05/97 1:04p Nrobinso
//  srmyisnewmission changes to armyisfirstmission
//  
//  125   12/05/97 11:30a Awerner
//  fixed some save bugs (typos)
//  
//  124   12/04/97 9:03p Aburgess
//  get playerindex after validation
//  
//  123   12/04/97 8:25p Nrobinso
//  add unitupdate to setup actions
//  
//  122   12/04/97 8:13p Aburgess
//  make sure NextMission is for ONEPLAYER only
//
//  121   12/04/97 7:34p Nrobinso
//  turn off animated objects
//  
//  122   12/04/97 8:13p Aburgess
//  make sure NextMission is for ONEPLAYER only
//  
//  119   12/04/97 10:10a Nrobinso
//  check for bad vehicle data
//  
//  118   12/04/97 9:02a Aburgess
//  Hooks in place to support Saved and Restored map objects. ALEX: use
//  SAVE_DEBUG compile flag to enable new code. Also, I'd like to suggest
//  you taking on debugging here at the moment. My plate is FULL, unless
//  Nicky feels its a higher priority. The supporting code is fairly simple
//  and straight forward.
//  
//  117   12/03/97 10:00a Aburgess
//  corrected player color mappiung and PlayerColor call
//  
//  116   12/01/97 6:20p Nrobinso
//  replace ASSERT with Error() if multiple sarges
// 
//	...
//  
//  $Nokeywords:$
///========================================================================


// Includes
#include "stdafx.h"

#include "AiAccess.h"
#include "Army.h"
#include "Aix.h"
#include "Comm.h"
#include "Disp.h"
#include "explosions.h"
#include "GameFlow.h"
#include "Item.h"
#include "MainFrm.h"
#include "Map.h"
#include "Msg.h"
#include "Sarge.h"
#include "Scenario.h"
#include "snd.h"
#include "Tad.h"
#include "trooper.h"
#include "unit.h"
#include "UnitMsg.h"
#include "Vehicle.h"
#include "Screen.h"
#include "Stats.h"
#include "Object.h"
#include "miscfile.h"
#include "Ai.h"
#include "Comm.h"
#include "pad.h"
#include "stratmap.h"
#include "debug.h"
#include "ui.h"

extern char scriptDebug;

extern char randomize;

void UpdateArmyProjectiles( int enumArmy );

#define	ARMY_MAX_PARAUNITS			64

char* armylabels[] ={"Green","Tan","Blue","Gray"};
    
///========================================================================
//							DEFINES
///========================================================================
typedef struct {
	int ammo[SARGE_LAST_WEAPON];
} SARGE_AMMO;


///========================================================================
//							VARIABLES
///========================================================================
ARMY			Armies[ARMY_LAST_ARMY];
SCENARIO		Scenario;
int				gAMCampaignID;
int				gAMScenarioID;
int				gAMMissionID;
static char lastView = 0;					// what visiblity to display(god)
static int allahDelay = 0;

static	int		ARMYcurrentCampaignIndex = 0;
static	int		ARMYcurrentScenarioIndex = 0;
static	int		ARMYcurrentMissionIndex  = 0;
static	int		ARMYoldCampaignIndex     = 0;
static	int		ARMYoldScenarioIndex     = 0;
static	int		ARMYoldMissionIndex      = 0;

int AdditionalParatroopers = 3;
int	ParaDropBoxCount = 0;


///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
static BOOL	ArmyBuildLegion( ARMY_TYPE eArmy, ARMY *pArmy );
static void	ArmyUpdatePositions( void );
static void	ArmyUpdateComm( void );
static BOOL DeployForces(DEPLOYED *pDeployedUnit, int nDeployed, BOOL use_extra_data);
static void RestoreSavedAmmo(DEPLOYED *pDeployed, int nDeployed, SARGE_AMMO *pAmmo);
static void RestoreSargeAmmo(SARGE_AMMO *pAmmo);
static	void ArmiesDelete( void );

void StratMapArmyDelete(int eArmy);

///========================================================================
//	Function:		ArmyInit()
//	Description:	Initialize the Army processing.
///========================================================================

BOOL	ArmyInit( void )
{
	int eArmy;

	ZeroMemory( (void*)&Scenario, sizeof(SCENARIO) );

	// clear the armies and 
	FOR_EACH_ARMY(eArmy)
	{
		ZeroMemory( (void*)&Armies[eArmy], sizeof(ARMY) );
	}

	return( FALSE );
}

///========================================================================
//	Function:		ArmyExit()
//	Description:	Terminate the Army processor.
///========================================================================

void	ArmyExit( void )
{
	// delete each of the armies
    TrooperSystemFree();
	ArmiesDelete();
}


///========================================================================
//	Function:		ArmyColorInit()
//	Description:	Sets up the tables needed to recolor plastic units & things
///========================================================================

#define FIRST_TAN_INDEX		(256-32)
#define FIRST_GREEN_INDEX	(256-48)
#define FIRST_GREY_INDEX	(256-64)
#define FIRST_BLUE_INDEX	(256-80)

typedef struct COLOR_TRANSLATION
{
  WORD first_index;
  WORD NumberOfEntries;
  BYTE *translate_table;
} COLOR_TRANSLATION;

LOCAL BYTE tan_colors[256];
LOCAL BYTE green_colors[256];
LOCAL BYTE grey_colors[256];
LOCAL BYTE blue_colors[256];

LOCAL BYTE *unit_color_tables[MAX_PLAYERS];

//#ifdef TAN
//LOCAL BYTE player_colors[MAX_PLAYERS] = {1,0,2,3};
//#else
//LOCAL BYTE player_colors[MAX_PLAYERS] = {0,1,2,3};
//#endif

LOCAL COLOR_TRANSLATION translation_tables[MAX_PLAYERS] = {
	{FIRST_GREEN_INDEX, 16, green_colors},
	{FIRST_TAN_INDEX, 16, tan_colors},
	{FIRST_BLUE_INDEX, 16, blue_colors},
	{FIRST_GREY_INDEX, 16, grey_colors}
};

extern BYTE  main_trans_table[256];

void ArmyColorInit()	{
	int index;
	int rgb;
	BYTE *ttable;
	int i;

	for (int j=0; j<MAX_PLAYERS; j++)	{
		ttable = translation_tables[j].translate_table;
		ZeroMemory(ttable, 256);

		for( i = 0; i<translation_tables[j].NumberOfEntries; i++)	
		{
			index = i + translation_tables[j].first_index;
			rgb = RGB(OriginalPalette.aEntries[index].peRed, OriginalPalette.aEntries[index].peGreen, OriginalPalette.aEntries[index].peBlue);
			ttable[i+1] = (BYTE) DDColorMatch(pBackBuffer, rgb);
		}

		// get the rest of the colors
		for( i = translation_tables[j].NumberOfEntries; i < 255; i++ )
		{
			ttable[i+1] = i;
		}
	}
}

// get the color translation table for that army
BYTE * UnitColorTable(ARMY_TYPE eArmy)	{
	return unit_color_tables[eArmy];
}

// get the color translation table for that army
SHORT PlayerColor(ARMY_TYPE eArmy)	{
	return( (SHORT)gpComm->ColorFromIndex( eArmy ) );
//	return (SHORT) gpComm->GetArmyIndex(eArmy);
//	return (SHORT) player_colors[eArmy];
}


///========================================================================
//	Function:		PlayerColorMapping()
//	Description:	Sets up the unit colors based on the colors selected by the
//					players. Until this is actually selected, the default setup is
//					Green, Tan, Grey, Blue
///========================================================================
void PlayerColorMapping()
{
	int	nextColor = ARMY_GREEN;

	for (int player=0; player<MAX_PLAYERS; player++)	{
		int color = gpComm->ColorFromIndex(player);
		if ( color == ARMY_NO_COLOR )
		{
			color = nextColor++;

			// now assign this color to the player
			gpComm->AcquireColor( gpComm->GetIDFromIndex(player), (ARMY_COLOR)color );
		}
		else
		if ( color == nextColor )
			++nextColor;
		unit_color_tables[player] = translation_tables[color].translate_table;
	}

// This would be a good place to set up whatever else other code will need
// to deal with units colors, e.g. the different colored art needed in
// the main base.
}


///========================================================================
//	Function:		ArmyLoad()
//	Description:	Load in the Army.
//					returns	FALSE if successful, TRUE otherwise
///========================================================================

static BOOL	ArmyGraphicsLoaded = FALSE;


BOOL	ArmyGraphicsLoad( void )
{
	if (ArmyGraphicsLoaded)
		goto exit;

	ArmyColorInit();			// sets up green/tan etc. color tables

	
	// load in all the UNIT data
	if ( UnitLoad() )
		goto exit;
	MissionLoading( 12000, 20000 );

	if (!VehicleLoad())
		goto exit;
	MissionLoading( 13100, 20000 );

    if (!TrooperSystemLoad())
        goto exit;
	MissionLoading( 14600, 20000 );

	// if we made it here we were successfull
	ArmyGraphicsLoaded = TRUE;

exit:
	return ArmyGraphicsLoaded;
}

///========================================================================
//	Function:		ArmyGraphicsFree()
//	Description:	Release the Army graphics
///========================================================================

void	ArmyGraphicsFree( void )
{
	UnitFree();
	VehicleFree();

	ArmyGraphicsLoaded = FALSE;
}

///========================================================================
//	Function:		ArmyAtScenarioEnd()
//	Description:	see if we are on the last mission of the scenario
///========================================================================

BOOL	ArmyAtScenarioEnd( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	BOOL			bAtEnd = FALSE;

	// now update the scenario, mission indecies
	pCampaign          = g_Campaigns[ g_CampaignIndex ];
	pScenario          = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
	pMission           = &(pScenario->pMissions[ g_MissionIndex ]);
	pMission->bVisible = STAT_PLAYED_FLAG;

	// now increment the mission index and make this mission accessible
	// as the NEXT playable mission
	if ( (g_MissionIndex+1) >= pScenario->nNumberMissions )
		bAtEnd = TRUE;
	return( bAtEnd );
}


CAMPAIGNREF* GetCampaign( void )
{
	CAMPAIGNREF*	pCampaign;

	// now update the scenario, mission indecies
	pCampaign = g_Campaigns[ g_CampaignIndex ];
	return (pCampaign);
}

SCENARIOREF* GetScenario( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;

	// now update the scenario, mission indecies
	pCampaign = g_Campaigns[ g_CampaignIndex ];
	pScenario = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
	return (pScenario);
}

MISSIONREF* GetMission( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;

	// now update the scenario, mission indecies
	pCampaign = g_Campaigns[ g_CampaignIndex ];
	pScenario = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
	pMission = &(pScenario->pMissions[ g_MissionIndex ]);
	return (pMission);
}


void MissionVisible(MISSIONREF* pMission)	{
	int	nPlayerNameIndex;

	if (!gpGame->cdBoot)
	{
		pMission->bVisible = STAT_PLAYED_FLAG;

		// now save out this info
		nPlayerNameIndex = StatGetPlayerNameIndex();
		StatSaveNext( nPlayerNameIndex, gpGame->CampaignID, pMission->nMissionID );
	}
}

void MissionNextVisible(MISSIONREF* pMission)	{
	int	nPlayerNameIndex;

	if (!gpGame->cdBoot)
	{
		pMission->bVisible = STAT_NEXT_FLAG;

		// now save out this info
		nPlayerNameIndex = StatGetPlayerNameIndex();
		StatSaveNext( nPlayerNameIndex, gpGame->CampaignID, pMission->nMissionID );
	}
}

///========================================================================
//	Function:		ArmyHaveNextMission()
//	Description:	see if there is another mission
///========================================================================

BOOL	ArmyHaveNextMission( void )
{
	int				nPlayerNameIndex;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	BOOL			bHave = FALSE;

	// the first thing we need to do is mark this latest mission as
	// being played
	pScenario = GetScenario();
	pMission = GetMission();
	MissionVisible(pMission);

	// now increment the mission index and make this mission accessible
	// as the NEXT playable mission
	if ( (g_MissionIndex+1) < pScenario->nNumberMissions )
	{
		++g_MissionIndex;

		pMission = &(pScenario->pMissions[ g_MissionIndex ]);
		if ( !pMission )
			goto exit;
		if ( !(pMission->nMissionID) )
			goto exit;

		gpGame->MissionID  = pMission->nMissionID;
		if ( pMission->bVisible == STAT_DISABLED_FLAG )
			pMission->bVisible = STAT_NEXT_FLAG;

		ArmySetNextAdvance(-1,-1,g_MissionIndex);	// set most advanced mission

		bHave = TRUE;
	}
exit:

	// now save out this info
	nPlayerNameIndex = StatGetPlayerNameIndex();
	StatSaveNext( nPlayerNameIndex, gpGame->CampaignID, gpGame->MissionID );

	return( bHave );
}

///========================================================================
//	Function:		ArmyHaveNextScenario()
//	Description:	see if there is another scenario
///========================================================================

BOOL	ArmyHaveNextScenario( void )
{
	int				nPlayerNameIndex;
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	BOOL			bHave = FALSE;


	pCampaign = GetCampaign();
	pScenario = GetScenario();
	pMission = GetMission();

	// the first thing we need to do is mark this latest scenario as
	// being played
	pScenario->bVisible = STAT_PLAYED_FLAG;
	MissionVisible(pMission);

	// now look for the next scenario
	if ((g_ScenarioIndex+1) < pCampaign->nNumberScenarios)
	{
		++(g_ScenarioIndex);
		g_MissionIndex = 0;

		// now update the scenario, mission indecies
		pScenario           = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
		if ( !pScenario )
			goto exit;
		if ( !(pScenario->nScenarioID) )
			goto exit;

		gpGame->ScenarioID  = pScenario->nScenarioID;
		pScenario->bVisible = STAT_NEXT_FLAG;

		pMission            = &(pScenario->pMissions[ g_MissionIndex ]);
		gpGame->MissionID   = pMission->nMissionID;
		if ( pMission->bVisible == STAT_DISABLED_FLAG )
			pMission->bVisible = STAT_NEXT_FLAG;

		ArmySetNextAdvance(-1,g_ScenarioIndex,g_MissionIndex);	// set most advanced mission

		bHave = TRUE;
	}
exit:
	// now save out this info
	nPlayerNameIndex = StatGetPlayerNameIndex();
	StatSaveNext( nPlayerNameIndex, gpGame->CampaignID, gpGame->MissionID );

	return( bHave );
}

///========================================================================
//	Function:		ArmyHaveNextCampaign()
//	Description:	see if there is another campaign
///========================================================================

BOOL	ArmyHaveNextCampaign( void )
{
	int				nPlayerNameIndex;
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	BOOL			bHave = FALSE;

	// the first thing we need to do is mark this latest campaign as
	// being played
	pCampaign = GetCampaign();
	pScenario = GetScenario();
	pMission = GetMission();

	pCampaign->bVisible = STAT_PLAYED_FLAG;
	pScenario->bVisible = STAT_PLAYED_FLAG;
	MissionVisible(pMission);

	if ((g_CampaignIndex+1) < g_NumberCampaigns)
	{
		++(g_CampaignIndex);
		g_ScenarioIndex = 0;
		g_MissionIndex  = 0;

		// now update the scenario, mission indecies
		pCampaign = g_Campaigns[ g_CampaignIndex ];
		if ( !pCampaign )
			goto exit;
		if ( !(pCampaign->nCampaignID) )
			goto exit;

		gpGame->CampaignID  = pCampaign->nCampaignID;
		pCampaign->bVisible = STAT_NEXT_FLAG;

		pScenario           = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
		gpGame->ScenarioID  = pScenario->nScenarioID;
		pScenario->bVisible = STAT_NEXT_FLAG;

		pMission            = &(pScenario->pMissions[ g_MissionIndex ]);
		gpGame->MissionID   = pMission->nMissionID;
		if ( pMission->bVisible == STAT_DISABLED_FLAG )
			pMission->bVisible = STAT_NEXT_FLAG;

		// prepare for presentation of the NEXT IDs
		ArmySetNextAdvance(g_CampaignIndex,g_ScenarioIndex,g_MissionIndex);

		// prepare for presentation of the NEXT IDs
//		ArmySetNextAdvance(g_CampaignIndex,g_ScenarioIndex,g_MissionIndex);
		bHave = TRUE;
	}
exit:
	// now save out this info
	nPlayerNameIndex = StatGetPlayerNameIndex();
	StatSaveNext( nPlayerNameIndex, gpGame->CampaignID, gpGame->MissionID );

	return( bHave );
}

///========================================================================
//	Function:		ArmySetNextAdvance()
//	Description:	set the next possible mission flags
///========================================================================

void	ArmySetNextAdvance( ULONG nCampaignIndex, ULONG nScenarioIndex, ULONG nMissionIndex )
{
	if ( nCampaignIndex != -1 )
	{
		ARMYoldCampaignIndex     = ARMYcurrentCampaignIndex;
		ARMYcurrentCampaignIndex = nCampaignIndex;
	}
	if ( nScenarioIndex != -1 )
	{
		ARMYoldScenarioIndex     = ARMYcurrentScenarioIndex;
		ARMYcurrentScenarioIndex = nScenarioIndex;
	}
	if ( nMissionIndex != -1 )
	{
		ARMYoldMissionIndex      = ARMYcurrentMissionIndex;
		ARMYcurrentMissionIndex  = nMissionIndex;
	}
#ifdef VISIBILITY_DEBUG
	TRACE( "ArmySetNextAdvance( %d:%d, %d%d %d%d )\n",
		g_CampaignIndex, gpGame->CampaignID, g_ScenarioIndex,
		gpGame->ScenarioID, g_MissionIndex, gpGame->MissionID );
	AiDumpVisibility();
#endif

}

///========================================================================
//	Function:		ArmyCurrentIndecies()
//	Description:	set the current campaign/scenario/mission indecies
///========================================================================

void	ArmyCurrentIndecies( int nCampaignIndex, int nScenarioIndex, int nMissionIndex )
{
	ARMYcurrentCampaignIndex = nCampaignIndex;
	ARMYcurrentScenarioIndex = nScenarioIndex;
	ARMYcurrentMissionIndex  = nMissionIndex;
}


///========================================================================
//	Function:		ArmyMissionFailures()
//	Description:	Get the number of times this mission has been failed
///========================================================================

unsigned char	ArmyMissionFailures( void )
{
	MISSIONREF*		pMission;
	unsigned char	nFailures;

	if ( gpGame->GameType == GAMETYPE_ONEPLAYER )	{
		pMission = GetMission();
		nFailures   = pMission->nFailed;
	}
	else
		nFailures = 0;

	return nFailures;
}


///========================================================================
//	Function:		ArmyCampaignFindNextAdvance()
//	Description:	set the next possible scenario/mission flags
///========================================================================

void	ArmyCampaignFindNextAdvance( void )
{
	int				nScenario;
	int				nMission;
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	BOOL			bHave = FALSE;

	pCampaign = g_Campaigns[ g_CampaignIndex ];
	if ( pCampaign )
	{
		for( nScenario=0; nScenario<pCampaign->nNumberScenarios; ++nScenario )
		{
			pScenario = &(pCampaign->pScenarios[ nScenario ]);
			if ( pScenario )
			{
				if ( (pScenario->bVisible & STAT_NEXT_FLAG ) == STAT_NEXT_FLAG )
				{
					if ( nScenario != ARMYcurrentScenarioIndex )
						ARMYoldScenarioIndex = ARMYcurrentScenarioIndex;

					ARMYcurrentScenarioIndex = nScenario;
					gpGame->ScenarioID       = pScenario->nScenarioID;
					g_ScenarioIndex          = ARMYcurrentScenarioIndex;
				}
				for( nMission=0; nMission<pScenario->nNumberMissions; ++nMission )
				{
					pMission = &(pScenario->pMissions[ nMission ]);
					if ( pMission )
					{
						if ( (pMission->bVisible & STAT_NEXT_FLAG ) == STAT_NEXT_FLAG )
						{
							if ( nMission != ARMYcurrentMissionIndex )
								ARMYoldMissionIndex = ARMYcurrentMissionIndex;

							ARMYcurrentMissionIndex = nMission;
							gpGame->MissionID       = pMission->nMissionID;
							g_MissionIndex          = ARMYcurrentMissionIndex;
						}
					}
				}
			}
		}
	}

//	ArmyApplyNextAdvance();
}

///========================================================================
//	Function:		ArmyApplyNextAdvance()
//	Description:	set the next possible mission flags
///========================================================================

void	ArmyApplyNextAdvance( void )
{
	int				nPlayerNameIndex;
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;

	// first reset the old most advance mission to visible
	pCampaign = g_Campaigns[ ARMYoldCampaignIndex ];
	if ( ARMYoldCampaignIndex != ARMYcurrentCampaignIndex )
		pCampaign->bVisible = STAT_PLAYED_FLAG;
	pScenario = &(pCampaign->pScenarios[ ARMYoldScenarioIndex ]);
	if ( ARMYoldScenarioIndex != ARMYcurrentScenarioIndex )
		pScenario->bVisible = STAT_PLAYED_FLAG;
	pMission = &(pScenario->pMissions[ ARMYoldMissionIndex ]);
	if ( ARMYoldMissionIndex != ARMYcurrentMissionIndex )
		MissionVisible(pMission);

	// now apply visibility and the MSB on for most advanced
	pCampaign  = g_Campaigns[ ARMYcurrentCampaignIndex ];
	if ( pCampaign->bVisible == STAT_DISABLED_FLAG )
		pCampaign->bVisible = STAT_NEXT_FLAG;
	pScenario  = &(pCampaign->pScenarios[ ARMYcurrentScenarioIndex ]);
	if ( pScenario->bVisible == STAT_DISABLED_FLAG )
		pScenario->bVisible = STAT_NEXT_FLAG;
	pMission = &(pScenario->pMissions[ ARMYcurrentMissionIndex ]);
	if ( pMission->bVisible == STAT_DISABLED_FLAG )
		pMission->bVisible = STAT_NEXT_FLAG;

	// now assign to the globals
	gpGame->CampaignID = pCampaign->nCampaignID;
	gpGame->ScenarioID = pScenario->nScenarioID;
	gpGame->MissionID  = pMission->nMissionID;
	g_CampaignIndex    = ARMYcurrentCampaignIndex;
	g_ScenarioIndex    = ARMYcurrentScenarioIndex;
	g_MissionIndex     = ARMYcurrentMissionIndex;

#ifdef VISIBILITY_DEBUG
	TRACE( "ArmyApplyNextAdvance( %d:%d, %d%d %d%d )\n",
		g_CampaignIndex, gpGame->CampaignID, g_ScenarioIndex,
		gpGame->ScenarioID, g_MissionIndex, gpGame->MissionID );
	AiDumpVisibility();
#endif

	// now save out this info
	nPlayerNameIndex = StatGetPlayerNameIndex();
	StatSaveNext( nPlayerNameIndex, gpGame->CampaignID, gpGame->MissionID );
}

void	ArmySetCurrentCampaignID( int nCampaignID )
{
	ARMYcurrentCampaignIndex = AiCampaignIndex( nCampaignID );
	ASSERT( ARMYcurrentCampaignIndex != -1 );
	gpGame->CampaignID = nCampaignID;
	g_CampaignIndex    = ARMYcurrentCampaignIndex;
}

void	ArmySetCurrentScenarioID( int nScenarioID )
{
	CAMPAIGNREF*	pCampaign;

	pCampaign = g_Campaigns[ ARMYcurrentCampaignIndex ];
	ASSERT( pCampaign );
	ARMYcurrentScenarioIndex = AiScenarioIndex( pCampaign, nScenarioID );
	ASSERT( ARMYcurrentScenarioIndex != -1 );
	gpGame->ScenarioID = nScenarioID;
	g_ScenarioIndex    = ARMYcurrentScenarioIndex;
}

void	ArmySetCurrentMissionID( int nMissionID )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;

	pCampaign = g_Campaigns[ g_CampaignIndex ];
	ASSERT( pCampaign );
	pScenario = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
	ASSERT( pScenario );
	ARMYcurrentMissionIndex = AiMissionIndex( pScenario, nMissionID );
	ASSERT( ARMYcurrentMissionIndex != -1 );
	gpGame->MissionID       = nMissionID;
	g_MissionIndex          = ARMYcurrentMissionIndex;
}

///========================================================================
//	Function:		ArmyNextMission()
//	Description:	set the new mission info
///========================================================================

BOOL	ArmyGetMission( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	ULONG			nMissionID;
	int				eArmy;
	int				nStatPlayerIndex;
	int				nNumberMissions;

	if ( gpGame->GameType == GAMETYPE_ONEPLAYER )	{
		// acquire the previous mission ID
		pCampaign   = g_Campaigns[ g_CampaignIndex ];
		pScenario   = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
		pMission    = &(pScenario->pMissions[ g_MissionIndex-1 ]);
		nMissionID  = pMission->nMissionID;
		nNumberMissions = pScenario->nNumberMissions;
	}
	else	{
		nNumberMissions = 1;
	}

	// later missions need to do some additional set, including getting saved data
	if ( g_MissionIndex > 0 )	{
		// make sure we're in single player mode
		ASSERT( gpGame->GameType == GAMETYPE_ONEPLAYER );

		nStatPlayerIndex = StatGetPlayerNameIndex();

		if (gpGame->newMission)	{
			// process any saved data
			ArmyLoadSavedMission( nStatPlayerIndex, nMissionID );
		}
	}

	// now initialize the mission
	if (g_MissionIndex < nNumberMissions)
	{
		FOR_EACH_ARMY(eArmy)	{
			// set resources & predeploy units & vehicles
			ArmyMissionInit( (ARMY_TYPE)eArmy, g_MissionIndex );

			if (gpGame->newMission)	{
				TadActivateArmy( (ARMY_TYPE)eArmy );		// Activate this army
			}
		}
		return(TRUE);
	}

	return( FALSE );
}


///========================================================================
//	Function:		ArmyMissionInit()
//	Description:	set the new mission info
///========================================================================
#define IS_VEHICLE(type) ((type) & 0x00008000)
#define GET_VEHICLE(type) ((type) & 0x00007FFF)
#define SET_VEHICLE(type) ((type) | 0x00008000)

void	ArmyMissionInit( ARMY_TYPE eArmy, int mission )
{
	MISSION*	pMissions;
	FORCE*		pForces;
	LEGION*		pLegion;
	ARMY*		pArmy;
	int			eType;
	int			count;
	int			i;

	pMissions = Scenario.pMissions;
 	pArmy = &Armies[ eArmy ];
	pLegion = &pArmy->Legion;
	pForces = &pMissions[mission].forces[eArmy];

	pArmy->troops_killed = 0;
	pArmy->vehicles_killed = 0;
	pArmy->sarge_kills = 0;

	// set the reources information
	for ( eType=0; eType<ARMY_LAST_RESOURCE; ++eType )
	{
		count = pForces->Reserves.nResourcesAvail[ eType ];
		pLegion->AirResources[ eType ] += count;
	}

	if( pArmy->Status <= 0 )
		return;

	BOOL foundSarge = DeployForces(pForces->pDeployment, pForces->nDeployed, FALSE);

	// allocate troopers for paratroopers
	long uids[ARMY_MAX_PARAUNITS];
	int  tempnumfound;
	UNIT *pUnit;

	tempnumfound = ParatroopersInHQ( eArmy, uids );
	for( i = 0; i < tempnumfound; i++ )
	{
		pUnit = UnitFind( uids[i] );
		{
			ASSERT(pUnit);
			ASSERT(pUnit->pTroops);

            // create troopers according to deployment data
            // if not already created by earlier mission
            if( !(pUnit->pTroops[0]) )
                UnitTrooperCreate( pUnit, pUnit->initialTroops );
		}
	}

#ifdef _DEBUG
	if ((eArmy == ARMY_PLAYER) && (g_MissionIndex == 0) && !foundSarge)	{
		Error("No Sarge found.");
		ASSERT(0);
	}
#endif
}


void ArmiesClearOldLocation()
{
    int			eArmy;
	LEGION*		pLegion;
	int			i;
	UNIT*		pUnit;
	VEHICLE*	pVehicle;
	SARGE*		pSarge;

	FOR_EACH_ARMY(eArmy)
    {
		if (Armies[eArmy].Status == 0) continue; // no such army

        pLegion = &Armies[ eArmy ].Legion;

        FOR_EACH_UNIT(pLegion, pUnit)
        {
            if (UNIT_ON_MAP(pUnit))
            {
				ItemClearOldLocation((ITEM *)pUnit);
			}
         }

		FOR_EACH_VEHICLE(pLegion,i)
        {
			pVehicle = pLegion->pLegionVehicles[i];
			if (VEHICLE_ON_MAP(pVehicle))
            {
				ItemClearOldLocation((ITEM *)pVehicle);
			}
		}

		pSarge = SargePointer(eArmy);
        if (pSarge->common.position.x)
            ItemClearOldLocation((ITEM *)pSarge);
     }
}


void ArmiesUpdatePads()	{
// updating pads may trigger events. Having a common update area
// instead of updating as things move prevents events from undeploying
// that which is moving, causing confusion in the code.    

    int			eArmy;
	LEGION*		pLegion;
	int			i;
	UNIT*		pUnit;
	VEHICLE*	pVehicle;
	SARGE*		pSarge;

	FOR_EACH_ARMY(eArmy)
    {
		if (Armies[eArmy].Status == 0) continue; // no such army
        pLegion = &Armies[ eArmy ].Legion;

        FOR_EACH_UNIT(pLegion, pUnit)
        {
        //    if (UNIT_ON_MAP(pUnit))	{
				ItemUpdatePad((ITEM *)pUnit);
		//	}
         }

		FOR_EACH_VEHICLE(pLegion,i)
        {
			pVehicle = pLegion->pLegionVehicles[i];
		//	if (VEHICLE_ON_MAP(pVehicle))	{
				ItemUpdatePad((ITEM *)pVehicle);
		//	}
		}

		pSarge = SargePointer(eArmy);
       // if (pSarge->common.position.x)
            ItemUpdatePad((ITEM *)pSarge);
     }
}


static BOOL DeployForces(DEPLOYED *pDeployed, int nDeployed, BOOL use_extra_data)
{
	int			i;
	BOOL		foundSarge = FALSE;
	ITEM*		pItem;
	SPOINT		point;
	short		facing;
	VEHICLE*	pVehicle;

	// handle predeployed units/vehicles
	for( i=0; i < nDeployed; ++i )
	{
		// get the uniqueID for this deployed object and find it
		// in the players army forces
		if (!pDeployed->pItem)	{
			if (pDeployed->nUniqueID)	{
				pItem = AiItemFind( pDeployed->nUniqueID );
				ASSERT( pItem );
			}
			else
				goto nextunit;

			pDeployed->pItem = pItem;

			point.x = pDeployed->location.x;
			point.y = pDeployed->location.y;
		}
		else	{
			point.x = ((pDeployed->location.x >> 4) << 4) + 8;
			point.y = ((pDeployed->location.y >> 4) << 4) + 8;
		}

		// now deploy this item
		facing = pDeployed->facing;

		if (IS_VEHICLE(pDeployed->eType))	{
			int type = GET_VEHICLE(pDeployed->eType);
			if (type == ARMY_COMMANDER)	{
				SARGE* pSarge = (SARGE *) pDeployed->pItem;
				ASSERT(pSarge);

				if (foundSarge)	{
					Error("Found multiple Sarges");
				}
				else	{
					// note where he is to deploy (in case he can revive)
					SargeDeployPosition(pSarge, &point, facing);
					if (pDeployed->dead) 
					{
						pSarge->deadPosition = pDeployed->deadPosition;
						goto nextunit;
					}
					
					pVehicle = NULL;
					if (use_extra_data)
					{
						if (pDeployed->extra_data.vehicle)	{
							pVehicle = (VEHICLE *) AiItemFind( pDeployed->extra_data.vehicle );
							ASSERT( pVehicle );
                            char namebuf[100];
                            sprintf(namebuf,"%s",ItemDBName(pSarge));
                            if (scriptDebug) TRACE("    %s deploying in vehicle %s\n",namebuf,ItemDBName(pVehicle));
						}
					}

					if (pDeployed->deployed)
						SargeInitialDeploy(pSarge, &point, facing, pVehicle);	// deploy sarge

					if (use_extra_data)	{
						pSarge->common.nStrength = pDeployed->extra_data.strength;
						AutoTuneStrength(pSarge, TRUE);
					}

					foundSarge = TRUE;
				}
			}
			else
            {
				pVehicle = (VEHICLE *) pDeployed->pItem;
				ASSERT(pVehicle);
				if (pDeployed->dead) 
				{
					if (pDeployed->dead)
					{
						pVehicle->deadPosition = pDeployed->deadPosition;
						pVehicle->state = VEHICLE_DEAD;
						//it disappears, husk and all, too bad.
					}
					else
					{
						pVehicle->state = VEHICLE_DEAD;
					}
					goto nextunit;
				}

                // else note where to deploy later
                VehicleDeployPosition(pVehicle, &point, facing);

                // Deploy this vehicle now
                if (pDeployed->deployed)
                    VehicleInitialDeploy(pVehicle, &point, facing);

				if (use_extra_data)
					pVehicle->common.nStrength = pDeployed->extra_data.strength;
            }
		}
		else	{
			UNIT* pUnit = (UNIT *) pDeployed->pItem;
			ASSERT(pUnit);
			if (pDeployed->dead)
			{
				pUnit->mode = UNIT_DEAD;
				pUnit->deadPosition = pDeployed->deadPosition;
				goto nextunit;
			}

            // create troopers according to deployment data
            UnitTrooperCreate(pUnit,pDeployed->number);

            UnitDeployPosition(pUnit, &point, facing);

			pVehicle = NULL;
			if (use_extra_data)
			{
				if (pDeployed->extra_data.vehicle)	{
					pVehicle = (VEHICLE *) AiItemFind( pDeployed->extra_data.vehicle );
					ASSERT( pVehicle );
                    char namebuf[100];
                    sprintf(namebuf,"%s",ItemDBName(pUnit));
                    if (scriptDebug) TRACE("    %s deploying in vehicle %s\n",namebuf,ItemDBName(pVehicle));
				}
			}

			// Deploy this unit now?
            if (pDeployed->deployed)
                UnitInitialDeploy(pUnit, point, facing, DEFENDFIRE, pVehicle);
		}

nextunit:
		// get the next deployed unit
		++pDeployed;
	}

	return (foundSarge);
}



///========================================================================
//	Function:		ArmyForcesInit()
//	Description:	set the new mission info
///========================================================================
void	ArmyForcesInit( ARMY_TYPE eArmy )
{
	MISSION*	pMissions;
	FORCE*		pForces;
	LEGION*		pLegion;
	ARMY*		pArmy;
	DEPLOYED*	pDeployedUnit;
	int			i,j;

	pMissions = Scenario.pMissions;
 	pArmy = &Armies[ eArmy ];
	pLegion = &pArmy->Legion;

	for (j=0; j<Scenario.nNumMissions; j++)	{
		pForces = &pMissions[j].forces[eArmy];

		// handle predeployed units/vehicles
		pDeployedUnit = pForces->pDeployment;
		for( i=0; i < pForces->nDeployed; ++i )
		{
			if (IS_VEHICLE(pDeployedUnit->eType))	{
				int type = GET_VEHICLE(pDeployedUnit->eType);
				if (type == ARMY_COMMANDER)	{
					SARGE*	pSarge = SargePointer(eArmy);

					// create sarge
					SargeCreate( eArmy );
                    // his name is fixed, ignores what is in the map
					pDeployedUnit->pItem = (ITEM *) pSarge;
				}
				else
				{
					VEHICLE* pVehicle = VehicleNextInHQ(eArmy,(VEHICLE_TYPE) type);
					ASSERT(pVehicle);

					// label it regardless
					ItemSetLabel((ITEM *) pVehicle, pDeployedUnit->text);
					pDeployedUnit->pItem = (ITEM *) pVehicle;
				}
			}
			else	{
				// get a unit from HQ
				UNIT *pUnit = UnitNextInHQ( eArmy, pDeployedUnit->eType );
				ASSERT(pUnit);

				// label it regardless
				ItemSetLabel((ITEM *) pUnit, pDeployedUnit->text);
				pDeployedUnit->pItem = (ITEM *) pUnit;
			}

			// get the next deployed unit
			++pDeployedUnit;
		}
	}

    // if no sarge in scenario, create an undeployed one
	SARGE*	pSarge = SargePointer(eArmy);
	if (!pSarge->common.nUniqueID)
		SargeCreate(eArmy);
}

///========================================================================
//	Function:		ArmyCreate()
//	Description:	Create all Armies.
///========================================================================

BOOL	ArmyCreate( )
{
	MISSION*	pMissions;
	FORCE*		pForces;
	ARMY*		pArmy;
	BOOL		error = TRUE;		// assume failure
	RESERVES	mission_reserves;
	RESERVES	total_reserves;
	int			i,j;
	int			eArmy;
	int			total_forces;

    FOR_EACH_ARMY(eArmy)
    {
		pArmy = &Armies[ eArmy ];
	
 		// set this army's defaults
		pArmy->eTargetingId  = TARGETING_AGGRESSIVE;

		pArmy->Status = 0;

		ZeroMemory( (void*)&total_reserves, sizeof(RESERVES) );

		// sum the unit/vehicle reserves from all missions
		total_forces = 0;
		pMissions = Scenario.pMissions;
		for (i=0; i<Scenario.nNumMissions; i++)	{
			pForces = &pMissions[i].forces[eArmy];
			memcpy( (void*)&mission_reserves, (void*)&(pForces->Reserves), sizeof(RESERVES) );

			for (j=0; j<ARMY_LAST_UNIT; j++)	{
				total_reserves.nUnitsAvail[j] += mission_reserves.nUnitsAvail[j];
				total_forces += mission_reserves.nUnitsAvail[j];
			}

			for (j=0; j<ARMY_LAST_VEHICLE; j++)	{
				total_reserves.nVehiclesAvail[j] += mission_reserves.nVehiclesAvail[j];
				total_forces += mission_reserves.nUnitsAvail[j];
			}
			total_forces += pForces->nDeployed;

			total_reserves.nUnitsAvail[ARMY_RIFLE_MEN] += mission_reserves.nResourcesAvail[ARMY_RESOURCE_PARATROOPERS];
			total_reserves.nResourcesAvail[ARMY_RESOURCE_PARATROOPERS] += mission_reserves.nResourcesAvail[ARMY_RESOURCE_PARATROOPERS];
		}

        // allow for pickup of boxes and default extra paratroops also
		total_reserves.nResourcesAvail[ARMY_RESOURCE_PARATROOPERS] += ParaDropBoxCount + AdditionalParatroopers;
		// need to reserve units of riflemen for the named paratrooper count
		total_reserves.nUnitsAvail[ARMY_RIFLE_MEN] += total_reserves.nResourcesAvail[ ARMY_RESOURCE_PARATROOPERS ];

		memcpy( (void*)&(pArmy->Reserves), (void*)&total_reserves, sizeof(RESERVES) );

        // so see if he has any assets on the map or deployable
        // assets will require the army to exist.
        if (total_forces == 0)
        {
            OBJECT* pObject;
            int j;
            for (j = 0; j < the_map.num_objects; ++j)
            {
                pObject = &the_map.objects[j];
                if (pObject->attribute != ARMY_ASSET) continue;
                if (ITEM_ARMY(pObject) != eArmy) continue;
                ++total_forces;
                break; // one is enough to know about army existing
            }
        }


		if( total_forces > 0 )
			pArmy->Status = 1;

        if (pArmy->Status == 0) continue; // not playing

		// now create the legion structure
		if ( ArmyBuildLegion( (ARMY_TYPE)eArmy, pArmy ) == FALSE )	{
			TRACE( "ERROR: failed to build legion. [%s,%d]\n",
				__FILE__, __LINE__ );
			return( error );
		}
	
		ArmyForcesInit((ARMY_TYPE)eArmy);
   }

	AdditionalParatroopers = 3;
	// if we made it here we were successful
	error = FALSE;

	return( error );
}


///========================================================================
//	Function:		ArmyUpdate()
//	Description:	Get player input, ai commander input, 
///========================================================================

extern int ReconTimer;

void	ArmyUpdate( void )
{
//	return;

	ValidateMap();

	if( ReconTimer > 0 )
	{
		ReconTimer -= gpGame->dwDeltaTime;
		if( ReconTimer <= 0 )
		{
			ReconTimer = 0;
		}
	}

#ifndef FINAL
    // if god view changes, refresh whole screen
    if (allahDelay)
    {
        allahDelay = 0;
        the_map.redraw = REDRAW_FULL;        
    }
    if (lastView != Allah) 
    {
		if (!allahDelay) allahDelay = 1; // need delay to get refresh after changes
        lastView = Allah;
        the_map.redraw = REDRAW_FULL;        
		if (Allah == 1)	dbgWrite("GOD view");
        else if (Allah == 2) dbgWrite("FOE view");
        else if (Allah == 0) dbgWrite("FRND view");

    }
#endif    

	// allow ai commander (if any) to simulate his UI access to the system
	AICommander();

	// get player input
	GetUserInput();
	// all controllable units do their thing
	ValidateMap();

	UnitUpdate();
	ValidateMap();

	// update sarge/vehicle and projectiles
    ArmyUpdatePositions();

	// Update the explosions
	UpdateExplosions();

	// Update the animated objects on the map
	UpdateAnimatedObjects();

	//Update all the scripted objects
	SOBJ_ProcessAll();

    // update pad triggers of all army objects, causing new events.
    // Placed after movement in case event triggers undeploy of object
    // that moved.
    ArmiesUpdatePads();

	ArmyUpdateComm();

	ValidateMap();
}


///========================================================================
//	Function:		ArmyUpdateInSetup()
//	Description:	Get player input, ai commander input, 
///========================================================================

void	ArmyUpdateInSetup( void )
{
	// get player input
	GetUserInput();

	// all controllable units do their thing
	UnitUpdate();

	// update sarge/vehicle and projectiles
    ArmyUpdatePositions();

	// Update the animated objects on the map
	UpdateAnimatedObjects();
}


///========================================================================
//	Function:		ArmyUpdatePositions()
//	Description:	Update the positional information of the player Army.
///========================================================================

static void	ArmyUpdatePositions( void )
{
	int			eArmy;
	LEGION*		pLegion;		// the actual army information
    int 		i;

    // if modem, other player updates come across the modem
    FOR_EACH_ARMY(eArmy)
    {
		if (Armies[eArmy].Status == 0) continue; // army no longer in play

        // get your legion and update all units and vehicles
        pLegion = &Armies[ eArmy ].Legion;
        
        for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
        {
            // update the vehicle position
            VehicleUpdate( pLegion->pLegionVehicles[i] );
        }
        
        // update sarge's position
		SargeUpdate( SargePointer(eArmy));

		UpdateArmyProjectiles(eArmy);
    }

	test_troop_update();
}

///========================================================================
//	Function:		ArmyUpdateComm()
//	Description:	Update other machines
///========================================================================

static void	ArmyUpdateComm( void )
{
	int			eArmy;
	LEGION*		pLegion;		// the actual army information
	UNIT*		pUnit;

    FOR_EACH_LOCAL_ARMY(eArmy)
    {
        if (Armies[eArmy].Status == 0) continue;
        
        // get your legion and update all units and vehicles
        pLegion = &Armies[ eArmy ].Legion;

        // update each of the units within this army
        FOR_EACH_UNIT(pLegion,pUnit)
        {
            // see if the Unit is active
            if (UNIT_ON_MAP(pUnit))
            {
                // send any pending update messages
                UnitSendPending( pUnit );
             }
         }
     }
}

///========================================================================
//	Function:		ArmyDelete()
//	Description:	remove memory caused by army creation
//					If showit is true, give smoke puffs as clues he went away
///========================================================================

void	ArmyDelete(int eArmy,int showIt)
{
	LEGION*		pLegion;
    int 		i;
	ARMY*		pArmy;
	DPID		id;

   //  Let Comm know about it;
	id = gpComm->m_PlayerId[eArmy];
	if( (id != -1) && showIt) gpComm->RemoveActivePlayer(id);

	// remove things of this army from the stratmap
    StratMapArmyDelete(eArmy);

    // hide objects of this army (does not delete objects actually)
    RemoveUnusedItemsOfArmy(eArmy);

    // remove this armies assets
    MapAssetDeleteOfArmy(eArmy);

    // start by getting the legion
    pArmy = &Armies[ eArmy ];
    if (pArmy->Status == 0) return; // never allocated or already released

    if (eArmy == ARMY_PLAYER) curselectedunit  = NULL; // ui has no more unit

    pLegion = &pArmy->Legion;

    // remove vehicles
    VEHICLE* pVehicle;
    for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
    {
        pVehicle = pLegion->pLegionVehicles[i];
        if (pVehicle == NULL) continue;
        
        if (showIt)	BlowItem((ITEM*)pVehicle);
        VehicleDelete(pVehicle);
    }
    
    // delete sarge after dropping any items
    SARGE* pSarge;
    pSarge = SargePointer(eArmy);


    if (showIt)	BlowItem((ITEM*)pSarge);
    SargeFree(pSarge);

    // delete units
    UNIT* pUnit;
    if (pLegion->pUnitList != NULL)
    {
        if (showIt) FOR_EACH_UNIT(pLegion,pUnit)
        {
            BlowItem((ITEM*)pUnit);
        }

        UnitDisband(pLegion);
        free((char*) pLegion->pUnitList);
    }
    
    // delete army missiles for this player
    for (i=0; i<ARMY_LEGION_MISSILES; i++)	
    {
        FloatDelete( &pLegion->Projectiles[i] );
        FloatDelete( &pLegion->Shadows[i] );
    }

    free( pLegion->AssetList );

    // now clear out the army information
    ZeroMemory( (void*)pArmy, sizeof(ARMY) );
    // implictly pArmy->Status = 0;					// not in play any more
}


///========================================================================
//	Function:		ArmiesDelete()
//	Description:	remove memory caused by army creation
///========================================================================

static void	ArmiesDelete()
{
	int			eArmy;

	// delete each of the Armies
	FOR_EACH_ARMY(eArmy)
    {
        ArmyDelete(eArmy,FALSE); // delete without fancy display of smoke
	}

}

// If a weapon of a type exists, then sarge could pick it up and look a particular unit type
void ArmyUnitTypeExist(int eWeapon)	{
	int eType;
	
	eType = GetSargeAnimType(eWeapon);
	Armies[ARMY_PLAYER].nSargeTypesAvail[eType]++;
}


extern int PARACOUNT;

static void BuildPara(ARMY_TYPE eArmy,ARMY* pArmy,LEGION* pLegion,int count)
{
    // mark last units as paratroopers and label them
    MISSION* pMissions;
    pMissions = Scenario.pMissions;
    FORCE*		pForces;
    int nMission = 0;
    int nPara = 0;
    while (!nPara && nMission < Scenario.nNumMissions)
    {
        ++nMission;
        pForces = &pMissions[nMission-1].forces[eArmy];
        nPara = pForces->Reserves.nResourcesAvail[ARMY_RESOURCE_PARATROOPERS];
    }

    if (nPara == 0)
    {
        nPara = 99; // extra ones in boxes
        nMission = 0; // the 0th mission
    }

    int i = 0;
    int non_para;
    int counter = 0;
    non_para = pArmy->Reserves.nUnitsAvail[ ARMY_RIFLE_UNIT ];
    non_para -= pArmy->Reserves.nResourcesAvail[ ARMY_RESOURCE_PARATROOPERS ];
    UNIT* junkUnit;
    char label[100]; 
    FOR_EACH_UNIT(pLegion,junkUnit)
    {
		if (--count < 0) break;			// END OF RIFLE UNITS LIST
        if (++i <= non_para) continue; // skip nonpara units
		
                        
        // mark remaining forces
        junkUnit->paratrooper = TRUE;
        junkUnit->initialTroops = PARACOUNT; // paratroopers are own count

        // shouldnt already be labelled, but checked for in call
        ++counter; // for labeling
        sprintf(label,"%sPara%d%2.2d",
                    armylabels[gpComm->ColorFromIndex(eArmy)],
                    nMission,counter);
        ItemSetLabel((ITEM*)junkUnit,label);
                
        // use up this missions para count by one. if exhausted
        // find next mission with paratroops
        if (--nPara == 0)
        {
            while (!nPara && nMission && nMission < Scenario.nNumMissions)
            {
                ++nMission;
                pForces = &pMissions[nMission-1].forces[eArmy];
                nPara = pForces->Reserves.nResourcesAvail[ARMY_RESOURCE_PARATROOPERS];
                counter = 0;
            }
        }
        // ran out of predesignaed ones, now accept box extras
        if (nPara == 0)
        {
            nPara = 99; // extra ones in boxes
            nMission = 0; // the 0th mission
            counter = 0;
        }

    }
}


///========================================================================
//	Function:		ArmyBuildLegion()
//	Description:	Builds the player army legion data structures.
//	Input:			eArmy			whose this army belongs to
//					pArmy			army containing the legion
///========================================================================

static BOOL ArmyBuildLegion( ARMY_TYPE eArmy, ARMY *pArmy )
{
	LEGION*		pLegion;
	UNIT*		pUnit;
	int			eType;
	int			size;
	int			count;
	int			nNumberReserves;
	LEGION*		pNewLegion      = NULL;
	BOOL		ok              = FALSE;

	// validate the parameters
	ASSERT( pArmy );

	// clear the legion structure
	pLegion = &(pArmy->Legion);
	ZeroMemory( (void*)(pLegion), sizeof(LEGION) ); 

	// set up the projectiles
	int i;
	for (i=0; i<ARMY_LEGION_MISSILES; i++)	{
		SPOINT pos;
		pos.x = pos.y = 0;
		FloatCreate( &pLegion->Projectiles[i], eArmy, &pos );
		FloatCreate( &pLegion->Shadows[i], eArmy, &pos );
	}

    // set up vehicles (undeployed)
    FOR_EACH_VEHICLE_TYPE(eType)
    {
//		if (eType == ARMY_COMMANDER) continue;
        count = pArmy->Reserves.nVehiclesAvail[ eType ];
		ASSERT(count >= 0 && count <= ARMY_MAX_VEHICLES);
		while(count--) VehicleCreate(eArmy,(VEHICLE_TYPE) eType);
    }


    // count how many units to create 
	nNumberReserves = 0;
    FOR_EACH_UNIT_TYPE(eType)
	{
		nNumberReserves += pArmy->Reserves.nUnitsAvail[ eType ];
	}


	// now sum the number of units
	pLegion->nTotalUnits = nNumberReserves;

    count 							 = pLegion->nTotalUnits;
    size                             = (count * sizeof(UNIT));
	if (size == 0) size = 1;		// reserve some space just to please malloc
    pLegion->pUnitList 		         = (UNIT*)malloc( size );
    pLegion->pLastUnitList 		     = pLegion->pUnitList + count;
    pUnit = pLegion->pUnitList;	
    if ( pUnit == NULL )
    {
        TRACE( "ERROR: failed to allocate UNIT list. [%s,%d]\n",
                __FILE__, __LINE__ );
        goto exit;
    }
    // clear all the units of this type
    ZeroMemory( (void*)pUnit, size);

	// now create all units for this legion
    FOR_EACH_UNIT_TYPE(eType)
	{
		count = pArmy->Reserves.nUnitsAvail[ eType ];

		pLegion->pUnits[ eType] = pUnit;				// start
        pLegion->pLastUnit[ eType] = pUnit + count;		// end + 1
        UnitCreateAll( eArmy, eType, pUnit, count);

        if (eType == ARMY_RIFLE_UNIT) BuildPara(eArmy,pArmy,pLegion,count);
        pUnit += count;
	}

    ASSERT (pUnit == pLegion->pLastUnitList);

	// if we made it here we were successful
	ok = TRUE;

exit:

	return( ok );
}

///========================================================================
//	Function:		ArmyGetVehicle()
//	Description:	Retrieve the PLAYER or ENEMY units.
///========================================================================

inline VEHICLE*	ArmyGetVehicle( int eArmy )
{
	SARGE* pSarge = SargePointer(eArmy);

	return( pSarge->pVehicle );
}

///========================================================================
//	Function:		ArmyGetLegion()
//	Description:	Retrieve the PLAYER or ENEMY units.
///========================================================================

inline LEGION*	ArmyGetLegion( int eArmy )
{
	return( &Armies[ eArmy ].Legion );
}


///========================================================================
//	Function:		ArmyNoticeStrategicWinItem
//	Description:	record any objects we care about for winning
///========================================================================
void ArmyNoticeStrategicWinItem(ITEM* pItem)
{
}

///========================================================================
//	Function:		ArmySetAlliance
//	Description:	set up an alliance between two armies
///========================================================================
void ArmySetAlliance(ARMY_TYPE eMyArmy, ARMY_TYPE eNewAlly, BOOL bIsAlly )
{
	Armies[ eMyArmy ].bAlliances[ eNewAlly ] = bIsAlly;
}

///========================================================================
//	Function:		ArmyClearAlliance
//	Description:	clear all alliances
///========================================================================
void ArmyClearAlliance()
{
    int eArmy,eArmy2;
    FOR_EACH_ARMY(eArmy)
    {
        FOR_EACH_ARMY(eArmy2)
        {
            Armies[ eArmy ].bAlliances[ eArmy2 ] = 0;
        }
    }
}

///========================================================================
//	Function:		ArmyHaveAllianceWith
//	Description:	see if two armies are allied
///========================================================================
BOOL ArmyHaveAllianceWith(ARMY_TYPE eMyArmy, ARMY_TYPE eAlly )
{
	return( Armies[ eMyArmy ].bAlliances[ eAlly ] );
}

///========================================================================
//	Function:		ArmySurvivingTroops
//	Description:	retrieve the current number of surving units in an army
///========================================================================
int ArmySurvivingTroops( ARMY_TYPE eMyArmy )		// number of troops alive at end of mission
{
	LEGION*	pLegion;
	UNIT*	pUnit;
	int		nSurviving = 0;

    // get your legion
    pLegion = &Armies[ eMyArmy ].Legion;

    // quesry each of the units within this army
    FOR_EACH_UNIT(pLegion,pUnit)
    {
        // see if the Unit is alive
        if (UNIT_ON_MAP(pUnit))
		{
			nSurviving += pUnit->troops;
		}
    }

	return( nSurviving );
}

///========================================================================
//	Function:		ArmyCasualties
//	Description:	retrieve the current number of casulaties for an army
///========================================================================
int ArmyCasualties( ARMY_TYPE eMyArmy )			// number of troopers killed
{
	int		nCasualties;
	ARMY	*pArmy = &Armies[eMyArmy];

	nCasualties = pArmy->troops_killed;

	return( nCasualties );
}


///========================================================================
//	Function:		ArmyVehicleCasualties
//	Description:	retrieve the current number of casulaties for an army
///========================================================================
int ArmyVehicleCasualties( ARMY_TYPE eMyArmy )			// number of troopers killed
{
	int		nCasualties;
	ARMY	*pArmy = &Armies[eMyArmy];

	nCasualties = pArmy->vehicles_killed;

	return( nCasualties );
}


///========================================================================
//	Function:		ArmyTroopsKilled
//	Description:	retrieve the current number of casulaties for an army
///========================================================================
int ArmyTroopsKilled( ARMY_TYPE eMyArmy )			// number of troopers killed
{
	int		nKilled = 0;
	int		eArmy;
	ARMY	*pArmy;

	FOR_EACH_ARMY(eArmy)	{
		if (eArmy != eMyArmy)	{
			pArmy = &Armies[eArmy];
			nKilled += pArmy->troops_killed;
		}
	}

	return( nKilled );
}


///========================================================================
//	Function:		ArmyVehiclesKilled
//	Description:	retrieve the current number of casulaties for an army
///========================================================================
int ArmyVehiclesKilled( ARMY_TYPE eMyArmy )			// number of troopers killed
{
	int		nKilled = 0;
	int		eArmy;
	ARMY	*pArmy;

	FOR_EACH_ARMY(eArmy)	{
		if (eArmy != eMyArmy)	{
			pArmy = &Armies[eArmy];
			nKilled += pArmy->vehicles_killed;
		}
	}

	return( nKilled );
}


///========================================================================
//	Function:		ArmySargeKills
//	Description:	retrieve the current number of kills by an armys Sarge
///========================================================================
int ArmySargeKills( ARMY_TYPE eMyArmy )			// kills by Sarge
{
	int		nKills;
	ARMY	*pArmy = &Armies[eMyArmy];

	nKills = pArmy->sarge_kills;

	return( nKills );
}


///========================================================================
//	Function:		ArmySargeDeaths
//	Description:	retrieve the number of times sarge died
///========================================================================
int ArmySargeDeaths( int eMyArmy )			// kills by Sarge
{
	int		nKills = 0;
	int		eArmy;

	FOR_EACH_ARMY(eArmy)	{
		nKills += Armies[eMyArmy].sarges_killedby[eArmy];
	}

	return( nKills );
}

///========================================================================
//	Function:		ArmySargesKilled
//	Description:	retrieve the current number of other sarges killed
///========================================================================
int ArmySargesKilled( int eMyArmy )			// kills by Sarge
{
	int		nKilled = 0;
	int		eArmy;

	FOR_EACH_ARMY(eArmy)	{
		if (eArmy != eMyArmy)	{
			nKilled += Armies[eMyArmy].sarges_killed[eArmy];
		}
	}

	return( nKilled );
}


///========================================================================
//	Function:		ArmyFlagsCollectedOfArmy
//	Description:	retrieve the current number flags collected from each army
///========================================================================
int ArmyFlagsCollectedOfArmy( int eMyArmy, int eOpArmy )
{
	return( Armies[eMyArmy].flags_collected[eOpArmy] );
}


///========================================================================
//	Function:		ArmyCollectedFlag
//	Description:	eMyArmy collects eOpArmy's flag
///========================================================================
int ArmyCollectedFlag( int eMyArmy, int eOpArmy )
{
	return( (++Armies[eMyArmy].flags_collected[eOpArmy]) );
}


///========================================================================
//	Function:		ArmyPerformance
//	Description:	retrieve the current par points for this mission
///========================================================================
int ArmyPerformance( ARMY_TYPE eMyArmy )
{
	return( Armies[ eMyArmy ].nPoints );
}


///========================================================================
//	Function:		ArmyMissionSave
//	Description:	save the end of mission data
///========================================================================

void ArmyMissionSave( FILE* pSaveFile )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	LEGION*			pLegion;		// the actual army information
	UNIT*			pUnit;
	VEHICLE*		pVehicle;
	SARGE*			pSarge;
	DEPLOYED*		pDeploymentList;	// list of deployed units
	DEPLOYED*		pDeploy;			// a deployed unit or vehicle
	ITEM*			pItem;
	int				eArmy;
	int				nCount;
	int				nCampaignIndex;
	int				nScenarioIndex;
	int				nMissionIndex;
	long			nSize;
	long			nMissionID = (long)MISN_ID;
	long			nPlayerID = (long)PLAY_ID;
	long			nDeployID  = (long)DPLY_ID;
	int				i;
	MISN			MissionSaveData;
	LONG			nDeployed;

	if ( gpGame->GameType != GAMETYPE_ONEPLAYER )
		return;

	// start by storing the mission name and map filename
	nCampaignIndex  = AiCampaignIndex( gpGame->CampaignID );
	ASSERT( nCampaignIndex != -1 );
	pCampaign       = g_Campaigns[ nCampaignIndex ];
	nScenarioIndex  = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
	pScenario       = &(pCampaign->pScenarios[ nScenarioIndex ]);
	nMissionIndex   = AiMissionIndex( pScenario, gpGame->MissionID );
	pMission        = &(pScenario->pMissions[ nMissionIndex ]);

	// write out the MISN chunk ID
	CHUNK_WRITE_LONG( pSaveFile, &nMissionID );

	// initialize the saved data space
	ZeroMemory( &MissionSaveData, sizeof( MISN ) );
	strcpy( MissionSaveData.missionName, pMission->pMissionName );
	strcpy( MissionSaveData.fileName, pMission->pFileName );

	// write out the size of the mission save block
	nSize = sizeof( MISN );
	CHUNK_WRITE_LONG( pSaveFile, &nSize );

	// write the header data to the file
	CHUNK_WRITE_BUFFER( pSaveFile, &MissionSaveData, sizeof( MISN ) );


	FOR_EACH_ARMY(eArmy)
	{
		pLegion = &Armies[ eArmy ].Legion;

		nDeployed = 0;

		// write out the PLAY chunk ID
		CHUNK_WRITE_LONG( pSaveFile, &nPlayerID );

		// write out the size of the mission save block
		nSize = sizeof( Armies[eArmy].Status );
		CHUNK_WRITE_LONG( pSaveFile, &nSize );
		CHUNK_WRITE_LONG( pSaveFile, &Armies[eArmy].Status );

		if (Armies[eArmy].Status == 0)	// inactive army
			continue;

		// save the reources information
		nSize = sizeof( int );
		for ( int eType=0; eType<ARMY_LAST_RESOURCE; ++eType )
		{
			int air = (int) pLegion->AirResources[ eType ];
			CHUNK_WRITE_LONG( pSaveFile, &nSize );
			CHUNK_WRITE_LONG( pSaveFile, &air );
		}


		// get player legion and count all deployed units
		FOR_EACH_UNIT(pLegion,pUnit)
		{
			// count the number of active/deployed Units
            if (!UNIT_IN_HQ(pUnit))
				++nDeployed;
		}

		// count all deployed vehicles
		FOR_EACH_VEHICLE(pLegion,i)
		{
			pVehicle = pLegion->pLegionVehicles[i];
			if (pVehicle->state != VEHICLE_UNDEPLOYED)
				++nDeployed;
		}

		// add sarge
		++nDeployed;

        TRACE("     %d forces saved for %d army\n",nDeployed,eArmy);

		// write the deployed data to the file
		nSize = sizeof( nDeployed );
		CHUNK_WRITE_LONG( pSaveFile, &nSize );
		CHUNK_WRITE_LONG( pSaveFile, &nDeployed );

		// allocate a block of DEPLOYED structures
		nSize = nDeployed * sizeof( DEPLOYED );
		pDeploymentList = (DEPLOYED*)malloc( nSize );
		ASSERT( pDeploymentList );
		ZeroMemory( pDeploymentList, nSize );

		// output the unit deployment information DPLY_ID
		CHUNK_WRITE_LONG( pSaveFile, &nDeployID );

		// write out the size of the deploy save block
		CHUNK_WRITE_LONG( pSaveFile, &nSize );

		// now assemble and output the deployment data
		nCount = 0;
		FOR_EACH_UNIT(pLegion,pUnit)
		{
			// count the number of active/deployed Units
			if (!UNIT_IN_HQ(pUnit))
			{
				pDeploy = &(pDeploymentList[ nCount ]);
				pItem               = (ITEM *) pUnit;
				pDeploy->eType      = (UNIT_TYPE)ITEM_CLASS( pItem );	// type of UNIT (being carried if VEHICLE)
				pDeploy->location.x = pItem->position.x;		// deployment position in world coordinates
				pDeploy->location.y = pItem->position.y;		// deployment position in world coordinates
				pDeploy->facing     = (BYTE)(pItem->facing);	// facing of deployed unit
				pDeploy->deployed   = TRUE;						// unit is deployed
				pDeploy->number     = pUnit->troops;			// number of troopers in unit
				pDeploy->nUniqueID  = pItem->nUniqueID;
				ASSERT(pDeploy->nUniqueID);
				pDeploy->pItem      = NULL;
				pDeploy->extra_data.strength = pUnit->common.nStrength;
				pDeploy->deadPosition = ItemDeadPosition((ITEM*)pUnit);
				if (UNIT_DEAD(pUnit))
					pDeploy->dead = TRUE;
				else pDeploy->dead = FALSE;

				if (pUnit->pVehicle)
					pDeploy->extra_data.vehicle = pUnit->pVehicle->common.nUniqueID;
				else
					pDeploy->extra_data.vehicle = 0;

				pDeploy->text[0] = '\0';
				if (pItem->label)
					strcpy( pDeploy->text, pItem->label );
                char namebuf[100];
                sprintf(namebuf,"%s",ItemDBName(pItem));
                if (pUnit->pVehicle && scriptDebug)
                    TRACE("    %s saved in vehicle %s\n",namebuf,ItemDBName(pUnit->pVehicle));
                else if (scriptDebug) TRACE("    %s saved at %d.%d\n",namebuf,
                    pItem->position.x,
                    pItem->position.y);
				++nCount;
			}
		}

		FOR_EACH_VEHICLE(pLegion,i)
		{
 			pVehicle = pLegion->pLegionVehicles[i];

		   // count the number of active/deployed Vehicles
			if (pVehicle->state != VEHICLE_UNDEPLOYED)
			{
				pDeploy = &(pDeploymentList[ nCount ]);
				pItem               = (ITEM *) pVehicle;
				pDeploy->eType      = SET_VEHICLE(ITEM_CLASS( pItem ));	// type of VEHICLE
				pDeploy->location.x = pItem->position.x;		// deployment position in world coordinates
				pDeploy->location.y = pItem->position.y;		// deployment position in world coordinates
				pDeploy->facing     = (BYTE)pItem->facing;		// facing of deployed unit
				pDeploy->deployed   = TRUE;						// vehicle is deployed
				pDeploy->nUniqueID  = pItem->nUniqueID;
				pDeploy->deadPosition = ItemDeadPosition((ITEM*)pVehicle);
				ASSERT(pDeploy->nUniqueID);
				pDeploy->pItem      = NULL;
				if (pVehicle->state == VEHICLE_DEAD || pVehicle->state == VEHICLE_DYING )
					pDeploy->dead = TRUE; // let it disappear completely, no husk or traffic problems
				else pDeploy->dead = FALSE;

				pDeploy->extra_data.ammo[0] = (char)(pItem->pWeapon->nAmmo & 0xff);
				pDeploy->extra_data.strength = pItem->nStrength;

				pDeploy->text[0] = '\0';
				if (pItem->label)
					strcpy( pDeploy->text, pItem->label );
                if (scriptDebug) TRACE("    %s saved at %d.%d\n",ItemDBName(pItem),
                    pItem->position.x,pItem->position.y);
				++nCount;
			}
		}

 		pSarge = &pLegion->Sarge;
		pDeploy = &(pDeploymentList[ nCount ]);
		pItem               = (ITEM *) pSarge;
		pDeploy->eType      = SET_VEHICLE(ARMY_COMMANDER);	// ARMY_COMMANDER means sarge
		pDeploy->location.x = pItem->position.x;		// deployment position in world coordinates
		pDeploy->location.y = pItem->position.y;		// deployment position in world coordinates
		pDeploy->facing     = (BYTE)(pItem->facing);	// facing of deployed unit
		pDeploy->nUniqueID  = pItem->nUniqueID;
		ASSERT(pDeploy->nUniqueID);
		pDeploy->pItem      = NULL;
		pDeploy->extra_data.strength = pSarge->common.nStrength;
		pDeploy->deadPosition = ItemDeadPosition((ITEM*)pSarge);

		if (pSarge->pVehicle)
			pDeploy->extra_data.vehicle = pSarge->pVehicle->common.nUniqueID;
		else
			pDeploy->extra_data.vehicle = 0;

		pDeploy->deployed   = FALSE;
		if (SARGE_ON_MAP(pSarge))
			pDeploy->deployed   = TRUE;

//		for (i=0; i<SARGE_LAST_WEAPON; i++)
//			if (pSarge->pWeaponList[i])
//				pDeploy->extra_data.ammo[i] = pSarge->pWeaponList[i]->nAmmo;

		pDeploy->text[0] = '\0';
		if (pItem->label)
			strcpy( pDeploy->text, pItem->label );
        char namebuf[100];
        sprintf(namebuf,"%s",ItemDBName(pItem));
        if (pSarge->pVehicle && scriptDebug)
            TRACE("    %s saved in vehicle %s\n",namebuf,ItemDBName(pSarge->pVehicle));
        else if (scriptDebug)
            TRACE("    %s saved at %d.%d\n",namebuf,
                pItem->position.x,pItem->position.y);
		++nCount;


		ASSERT(nCount == nDeployed);

		// write the data to the file
		CHUNK_WRITE_BUFFER( pSaveFile, pDeploymentList, nSize );

		// free up the deployed data
		free( pDeploymentList );
	}

	SaveObjectChanges( pSaveFile );
}

///========================================================================
//	Function:		ArmyLoadSavedMission
//	Description:	read in the saved mission data
///========================================================================

void ArmyLoadSavedMission( int	nPlayerIndex, int nMissionID )
{
	FILE*			pMisnFile;
	DEPLOYED*		pDeployment;	// list of deployed units
	ULONG			nSize;
	int				eArmy;
	char			ASFname[STAT_MAX_REF_LEN+1];
	int				nPlayerNameIndex = StatGetPlayerNameIndex();
	MISN			MissionSaveData;
	long			nDeployed;
	SARGE_AMMO		SavedAmmo;
	LEGION*			pLegion;


	// start by opening the ASF file
	SetPath(SAVE_PATH);
	sprintf( ASFname, "%s_%d.asf", STATplayerNames[ nPlayerNameIndex ], nMissionID );
	pMisnFile = fopen( ASFname, "rb" );
	if ( pMisnFile == NULL )
		return;

	// initialize the saved data space
	ZeroMemory( &MissionSaveData, sizeof( MISN ) );

	// read in the MISN block to determine what need to be allocated
	if ( ChunkFind( pMisnFile, MISN_ID ) )
	{
		nSize = sizeof( MISN );
		if ( ChunkRead( pMisnFile, (void*)&MissionSaveData, &nSize ) )
		{
			TRACE( "ERROR: failed to read MISN chunk [%s:%d]\n", __FILE__, __LINE__ );
			ASSERT(0);
		}
	}
	else
		TRACE( "ERROR: failed to find MISN chunk [%s:%d]\n", __FILE__, __LINE__ );


	FOR_EACH_ARMY(eArmy)
	{
		pLegion = &Armies[ eArmy ].Legion;

		if ( ChunkFindNext( pMisnFile, PLAY_ID ) )
		{
			nSize = sizeof( Armies[eArmy].Status );
			if ( ChunkRead( pMisnFile, (void*)&Armies[eArmy].Status, &nSize ) )
			{
				TRACE( "ERROR: failed to read PLAY chunk1 [%s:%d]\n", __FILE__, __LINE__ );
				ASSERT(0);
			}

			if ( Armies[eArmy].Status == 0)
				continue;

			// restore the reources information
			nSize = sizeof( int );
			for ( int eType=0; eType<ARMY_LAST_RESOURCE; ++eType )
			{
				int air;

				if ( ChunkRead( pMisnFile, (void*)&air, &nSize ) )
				{
					TRACE( "ERROR: failed to read PLAY chunk2-4 [%s:%d]\n", __FILE__, __LINE__ );
					ASSERT(0);
				}

				pLegion->AirResources[ eType ] = air;
			}

			nSize = sizeof( nDeployed );
			if ( ChunkRead( pMisnFile, (void*)&nDeployed, &nSize ) )
			{
				TRACE( "ERROR: failed to read PLAY chunk5 [%s:%d]\n", __FILE__, __LINE__ );
				ASSERT(0);
			}
		}
		else
			TRACE( "ERROR: failed to find PLAY_ID chunk [%s:%d]\n", __FILE__, __LINE__ );

		// allocate a block of DEPLOYED structures
		nSize       = nDeployed * sizeof( DEPLOYED );
		pDeployment = (DEPLOYED*)malloc( nSize );
		ASSERT( pDeployment );
		ZeroMemory( pDeployment, nSize );

		// now read in the DPLY blocks
		if ( ChunkFindNext( pMisnFile, DPLY_ID ) )
		{
			if ( ChunkRead( pMisnFile, (void*)pDeployment, &nSize ) )
			{
				TRACE( "ERROR: failed to read DPLY chunk [%s:%d]\n", __FILE__, __LINE__ );
				ASSERT(0);
			}
		}
		else
		{
			TRACE( "ERROR: failed to find DPLY chunk [%s:%d]\n", __FILE__, __LINE__ );
		}

		// now its time to deploy these units, treat them as pre-deployed units
		BOOL foundSarge = DeployForces(pDeployment, nDeployed, TRUE);
		if (eArmy == ARMY_PLAYER)	{
			ASSERT(foundSarge);
			RestoreSavedAmmo(pDeployment, nDeployed, &SavedAmmo);
		}
		else	{
			RestoreSavedAmmo(pDeployment, nDeployed, NULL);
		}


		// free up the deployed data
		free( pDeployment );
		pDeployment = NULL;
	}

	RestoreSavedObjects( pMisnFile );
//	RestoreSargeAmmo(&SavedAmmo);

	fclose( pMisnFile );
}


static void RestoreSavedAmmo(DEPLOYED *pDeployed, int nDeployed, SARGE_AMMO *pAmmo)
{
	int			i;
	ITEM*		pItem;

	// handle predeployed units/vehicles
	for( i=0; i < nDeployed; ++i )
	{
		// get the uniqueID for this deployed object and find it
		// in the players army forces
		if (!pDeployed->pItem)	{
			pItem = AiItemFind( pDeployed->nUniqueID );
            ASSERT(pItem);
			pDeployed->pItem = pItem;
		}

		if (IS_VEHICLE(pDeployed->eType))	{
			int type = GET_VEHICLE(pDeployed->eType);

			if (type == ARMY_COMMANDER)	{
				;
			/*
				SARGE* pSarge = (SARGE *) pDeployed->pItem;

				if (pDeployed->deployed && pAmmo)	{
					for (int j=0; j<SARGE_LAST_WEAPON; j++)	{
						pAmmo->ammo[j] = pDeployed->extra_data.ammo[j];
					}
				}
			*/
			}
			else
            {
				VEHICLE* pVehicle = (VEHICLE *) pDeployed->pItem;
 				pVehicle->common.pWeapon->nAmmo = pDeployed->extra_data.ammo[0];
			}
		}

		// get the next deployed unit
		++pDeployed;
	}
}


static void RestoreSargeAmmo(SARGE_AMMO *pAmmo)	{
	int j;
	SARGE* pSarge = SargePointer(ARMY_PLAYER);

	for (j=0; j<SARGE_LAST_WEAPON; j++)
		if (pSarge->pWeaponList[j])
			pSarge->pWeaponList[j]->nAmmo = pAmmo->ammo[j];
}

///========================================================================
//	Function:		ArmyIsFirstMission
//	Description:	is this the first mission of a scenario
///========================================================================

BOOL	ArmyIsFirstMission( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	int				nCampaignIndex;
	int				nScenarioIndex;
	int				nMissionIndex;

	// start by getting the campaign
	nCampaignIndex  = AiCampaignIndex( gpGame->CampaignID );
	ASSERT( nCampaignIndex != -1 );
	pCampaign       = g_Campaigns[ nCampaignIndex ];
	nScenarioIndex  = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
	pScenario       = &(pCampaign->pScenarios[ nScenarioIndex ]);
	nMissionIndex   = AiMissionIndex( pScenario, gpGame->MissionID );

	return( !nMissionIndex );
}


//	FOR_EACH_LOCAL_ARMY macro support

extern inline int GetNextDeployedArmy(int eArmy)
{
	do
	{
		eArmy++;

		if( eArmy >= ARMY_LAST_ARMY ||
			Armies[eArmy].Status != 0 )
			break;
	} while (1);
	return eArmy;
}

int IRunArmy(int eArmy)
{
	int remote;
	if (eArmy == ARMY_INDEPENDENT) return FALSE;

	if (gpGame->GameType == GAMETYPE_ONEPLAYER) return TRUE; // all armies are on this machine

	remote = gpComm->IsRemote(eArmy);
	if (eArmy == ARMY_PLAYER) return TRUE; // we are this machine
	if (remote != COMM_REMOTE && gpGame->GameType == GAMETYPE_HOST_MULTIPLAYER) return TRUE; // we are host and so run non-human armies
	return FALSE;
}

int GetNextLocalArmy(int eArmy) 
{
	while (++eArmy < ARMY_LAST_ARMY)
	{
		if (Armies[eArmy].Status == 0) continue; // not in play
		if (IRunArmy(eArmy)) break; // its under my control
	} 
	return eArmy;
}

///========================================================================
//								EOF
///========================================================================
