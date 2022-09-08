//========================================================================
//	FILE:			$Workfile: Movie.cpp $
//
//	DESCRIPTION:	Avi Movie state processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, July 1, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Movie.cpp 50    4/17/98 3:14p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996,1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	MovieInit()
//		Initialize the AVI Movie state processor
//	MovieExit()
//		Terminate the AVI Movie state processor.
//========================================================================
//  History
//
//  $Log: /ArmyMen/src/Movie.cpp $
//  
//  50    4/17/98 3:14p Nrobinso
//  command switch to turn off movies
//  
//  49    4/07/98 3:22p Nrobinso
//  automatically pick small version of video for slow machine
//  
//  48    4/06/98 11:25p Nrobinso
//  clear surfaces before playing movies
//  
//  47    4/06/98 11:58a Nrobinso
//  turn off cursor in credits movie
//  
//  45    4/02/98 7:10p Aburgess
//  making the movies work
//  
//  44    4/02/98 3:21p Phu
//  typecast to avoid warnings
//  
//  43    4/02/98 3:39p Nrobinso
//  only Enter & Esc get out of movie
//  
//  42    4/02/98 11:24a Aburgess
//  cleanup of Movie processing on close or destroy
//  
//  41    4/02/98 10:04a Aburgess
//  for now, non-interlaced intro video
//  
//  40    4/02/98 9:39a Aburgess
//  modifications to support interlaced and non-interlaced Smaker videos
//  
//  39    3/30/98 10:28a Aburgess
//  reversed result of SlowMachine test
//  
//  38    3/27/98 1:48p Aburgess
//  accesses small intro movie if slow machine
//  
//  37    3/27/98 1:24p Nrobinso
//  fix IsMovie
//  
//  36    3/25/98 8:11p Nrobinso
//  check for movie
//  
//  35    3/23/98 12:17p Aburgess
//  proper handling of smacker object deletion at end of Movie play
//  (MovieEject)
//  
//  34    3/19/98 9:40a Aburgess
//  modifications made to present the 3DO logo Video
//  
//  33    3/17/98 11:18a Aburgess
//  stopping all sounds during movie sequences
//  
//  32    3/13/98 11:34a Nrobinso
//  remove resert menu items
//  
//  31    3/12/98 11:38a Aburgess
//  added delay at end of intro movie
//  
//  30    3/09/98 9:57a Aburgess
//  credits transitions
//  
//  29    3/03/98 9:18a Aburgess
//  corrected FMV Lose transition and setup
//  
//  28    2/20/98 6:15p Nrobinso
//  remove extra setpaths
//  
//  27    2/20/98 4:27p Aburgess
//  multiplayer update calls removed (called initally from init routine)
//  
//  26    2/13/98 4:05p Nrobinso
//  remove uneeded audioinit
//  
//  25    2/13/98 3:59p Nrobinso
//  remove avi player
//  
//  24    2/02/98 3:12p Aburgess
//  smacker now ejects when smk not available, advancing to next state
//  
//  23    1/26/98 12:01p Nrobinso
//  new path defines; use only one MOVIE_PATH
//  
//  22    1/23/98 9:33a Aburgess
//  noe uses new LEGAL title screen
//  
//  21    1/22/98 6:44p Nrobinso
//  use SetPath
//  
//  20    1/20/98 11:03a Aburgess
//  removed SMACKER directory dependency.
//  
//  19    1/20/98 8:36a Aburgess
//  Smacker now interruptable. Playback is currently 320 x 200, We are
//  unable to stretch the image.
//  
//  18    1/20/98 12:46a Aburgess
//  lastest working murder
//  
//  17    1/14/98 3:25p Aburgess
//  re-application of SMACKCLIPS compile time flag
//  
//  16    1/14/98 2:17p Aburgess
//  modifications made to support Smacker
//  
//  15    12/23/97 11:29a Aburgess
//  new MOVIE avi interface and substates
//  
//  14    12/09/97 12:12p Phu
//  
//  13    11/24/97 2:54p Aburgess
//  addition of FINALE state
//  
//  12    11/20/97 11:28a Nrobinso
//  look in avi folder for avi's
//  
//  11    11/17/97 10:04a Aburgess
//  applied audioInit in AVI Movie state changes
//  
//  10    11/13/97 9:57a Aburgess
//  removed external runtime reference for paths
//  
//  9     11/13/97 8:08a Aburgess
//  added proper path changes
//  
//  8     11/12/97 10:24a Aburgess
//  change MoviePlay to MovieRandomPlay. Added new MoviePlay routine. added
//  change directory to ./avi/
//  
//  6     9/08/97 8:53a Aburgess
//  corrected bad movie index problem
//  
//  5     8/26/97 11:00a Aburgess
//  corrected movie indexing
//  
//  4     8/17/97 6:09p Nrobinso
//  rename connect_state to title_screen_state
//  
//  3     8/07/97 11:53p Nrobinso
//  moved globals.h to stdafx.h
//  
//  2     7/23/97 10:58p Aburgess
//  Avi movie processing modified for 3DO commericial AVI
//  
//  1     7/03/97 5:18p Nrobinso
//  
// 
//  $Nokeywords:$
///========================================================================

#include "stdafx.h"

#include "Army.h"
#include "Vehicle.h"
#include "MainFrm.h"
#include "Comm.h"
#include "GameFlow.h"
#include "Movie.h"
#include "miscfile.h"
#include "audio.h"
#include "Screen.h"
#include "States.h"
#include "Smacker.h"
#include "fileio.h"
#include "ui.h"
#include "input.h"

///========================================================================
//							LOCAL DEFINES
///========================================================================

///========================================================================
//							LOCAL DATA STRUCTURES
///========================================================================

typedef	struct
{
	GAME_STATE	eGameState;		// next game state to enter
	MOVIE_STATE	eMovieState;	// next Movie state to enter
} MOVIETABLE;

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
BOOL	MovieUIOverride(UINT key, BOOL down);
void	MovieEject( void );

///========================================================================
//							LOCAL VARIABLES
///========================================================================

static	MOVIE_STATE	MOVIEstate;
static	LONG		MOVIEcampaignIndex = 0;
static	LONG		MOVIEscenarioIndex = 0;
static	LONG		MOVIEmissionIndex  = 0;
static	CSmacker*	pSmackerClip       = NULL;

SUserInterface UI_MOVIE_STATE = {
	NULL,			// Mouse left-button down events
	NULL,			// Mouse left-button up events
	NULL,			// Mouse right-button down events
	NULL,			// Mouse right-button up events
	NULL,			// Mouse movement events

	NULL,			// key down events
	NULL,			// key up events

	MovieUIOverride	// special hadnling for any key
};

BOOL noPlayMovies = FALSE;

///========================================================================
//	Function:		MovieInit()
//
//	Description:
//		Initialize the AVI Movie state processor
//
//	Input:			none
//
//	Ouput:			error		TRUE if successful, FALSE otherwise
//
///========================================================================

BOOL		MovieInit( void )
{
	MOVIEstate = MOVIE_3DO_STATE;
	return( FALSE );
}

///========================================================================
//	Function:		MovieExit()
//
//	Description:
//		Terminate the AVI Movie state processor.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void		MovieExit( void )
{
	MovieEject();
}

///========================================================================
//	Function:		MovieSetState()
//
//	Description:
//		Setup the next AVI movie state.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void		MovieSetState( MOVIE_STATE eState )
{
	// check parameters
	ASSERT( (eState >= MOVIE_NULL_STATE) && (eState < MOVIE_LAST_STATE) );

	// save off the current  indecies for mission/scenario/campaign
	MOVIEcampaignIndex = g_CampaignIndex;
	MOVIEscenarioIndex = g_ScenarioIndex;
	MOVIEmissionIndex  = g_MissionIndex;

	// finally set the movie state
	MOVIEstate = eState;
}

///========================================================================
//	Function:		MovieGetState()
//
//	Description:
//	returnt the current movie state.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

MOVIE_STATE		MovieGetState( void )
{
	return( MOVIEstate );
}

///========================================================================
//	Function:		MoviePlay()
//
//	Description:
//		play an AVI movie.
//
//	Input:			m_hWnd		window handler for movie play
//					pAviName	filename of AVI movie file
//
//	Ouput:			none
//
///========================================================================

void		MoviePlay( HWND m_hWnd, char* pAviName, BOOL bInterlaced )
{
	SetPath(MOVIE_PATH);

	// check for the exisitance of the SMACKER file
	if ( FileExist( pAviName ) && !noPlayMovies )
	{
		MovieEject();
		pSmackerClip = new CSmacker( pAviName, -1, -1, bInterlaced );

		SmackerSetObject( pSmackerClip );
		pSmackerClip->SetVolume( 32768 );	// NORMAL VOLUME
		pSmackerClip->Play();
	}
	else
		pMainFrame->PostMessage(AVIVID_EJECTED, 0, 0L);	// notify main code that clip ended
}

///========================================================================
///========================================================================
LONG	MovieWhatIsNext( void )
{
	if ( gpGame->GameType == GAMETYPE_ONEPLAYER)
	{
		if ( ArmyHaveNextScenario() )	// end of scenario, go onto next
		{
			// need to return the player to the mission select screen
			gpGame->SetState( GAME_TITLE_SCREEN_STATE );
			ScrnSetState( SCRN_SELECT_MISSION_STATE );
		}
		else
		if ( ArmyHaveNextCampaign() )	// end of campaign, go onto next
		{
			// need to return the player to the mission select screen
			gpGame->SetState( GAME_TITLE_SCREEN_STATE );
			ScrnSetState( SCRN_SELECT_CAMPAIGN_STATE );
		}
		else	// player is finished the entire disk. Remove all the army data
		{
			// need to return the player to the mission select screen
			gpGame->SetState( GAME_TITLE_SCREEN_STATE );
			ScrnSetState( SCRN_GAME_START_STATE );
		}
	}
	else
	{
		// clear the screen state and put up a title screen background
		ScrnSetState( SCRN_NULL_STATE );
		gpGame->newMission = TRUE;

		SetPath( SCREEN_PATH );
		LoadBackground( "Title_legal.bmp", FALSE );

		pMainFrame->StartGame();	// start the game
	}

	return( SBTN_STATE_CHANGE );
}

///========================================================================
///========================================================================
void	MovieEject( void )
{
	if ( pSmackerClip )
	{
		SmackerCleanUp();
		delete pSmackerClip;
		pSmackerClip = NULL;
	}
}


void GetMovieName(char *name, char *basename)
{
	strcpy(name, basename);

	if ( gpGame->SlowMachine )
		strcat(name, "Sml");

	strcat(name, ".smk");
}


///========================================================================
///========================================================================
LONG	MovieInit3DO( void )
{
	char name[32];

	GetMovieName(name, "Logo20");

	MoviePlay( pMainFrame->m_hWnd, name, FALSE );

	return(0);
}

LONG	MovieTerminate3DO( void )
{
	MovieEject();
	MovieSetState( MOVIE_INTRO_STATE );
	gpGame->SetState( GAME_MOVIE_STATE );

	return(0);
}

LONG	MovieInitIntro( void )
{
	char name[32];

	GetMovieName(name, "intro");

	MoviePlay( pMainFrame->m_hWnd, name, FALSE );

	return(0);
}

LONG	MovieTerminateIntro( void )
{
	MovieEject();
	MovieSetState( MOVIE_NULL_STATE );

	gpGame->SetState( GAME_TITLE_SCREEN_STATE );
	gpGame->nPauseDelay = GetTickCount() + HALF_SECOND;

	return(0);
}

LONG	MovieInitWin( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	char	name[32];

	gpGame->PauseGame( PAUSE_MOVIE );
	EraseSurfaces();
	ShowTheCursor( FALSE );

	pMainFrame->SetUI(&UI_MOVIE_STATE);

	// use the current scenario to get the win avi
	pCampaign = g_Campaigns[ MOVIEcampaignIndex ];
	pScenario = &(pCampaign->pScenarios[ MOVIEscenarioIndex ] );

	// stop all music streams
	audioStopAll();

	GetMovieName(name, pScenario->pScenarioWin);
	MoviePlay( pMainFrame->m_hWnd, name, FALSE );

	return(0);
}

LONG	MovieTerminateWin( void )
{
	MovieEject();
	MovieSetState( MOVIE_NULL_STATE );

	ShowTheCursor( TRUE );
	pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
	pMainFrame->SetUIOverride(KeyOverride_GAME_TITLE_SCREEN_STATE);
	gpGame->UnPauseGame( PAUSE_MOVIE );
	
	// where do we go from here
	MovieWhatIsNext();

	return(0);
}

LONG	MovieInitLose( void )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	int				nLoseIndex;
	char			name[32];

	gpGame->PauseGame( PAUSE_MOVIE );
	EraseSurfaces();
	ShowTheCursor( FALSE );

	pMainFrame->SetUI(&UI_MOVIE_STATE);

	// use the current scenario to get the lose avi
	pCampaign = g_Campaigns[ MOVIEcampaignIndex ];
	pScenario = &(pCampaign->pScenarios[ MOVIEscenarioIndex ] );

	// randomly choose an avi
	nLoseIndex = rand() % 3;
	if ( nLoseIndex == 3 )
		nLoseIndex = 0;

	// stop all music streams
	audioStopAll();

	GetMovieName(name, pScenario->pScenarioLose[ nLoseIndex ]);
	MoviePlay( pMainFrame->m_hWnd, name, FALSE );

	return(0);
}

LONG	MovieTerminateLose( void )
{
	MovieEject();
	MovieSetState( MOVIE_NULL_STATE );

	ShowTheCursor( TRUE );
	pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
	pMainFrame->SetUIOverride(KeyOverride_GAME_TITLE_SCREEN_STATE);
	gpGame->UnPauseGame( PAUSE_MOVIE );	// decide what to do next

	switch(gpGame->GameType)	
	{
	case GAMETYPE_ONEPLAYER:
		// need to return the player to the mission select screen
		gpGame->SetState( GAME_TITLE_SCREEN_STATE );
		ScrnSetState( SCRN_SELECT_MISSION_STATE );
		break;
	case GAMETYPE_HOST_MULTIPLAYER:
		ScrnSetState( SCRN_MULTI_HOST_STATE );
		break;
	case GAMETYPE_REMOTE_MULTIPLAYER:
		ScrnSetState( SCRN_MULTI_REMOTE_STATE );
		break;
	}

	return(0);
}

LONG	MovieInitCredits( void )
{
	char name[32];

	gpGame->PauseGame( PAUSE_MOVIE );
	EraseSurfaces();

	// disable the windows cursor
	ShowTheCursor( FALSE );

	pMainFrame->SetUI(&UI_MOVIE_STATE);

	GetMovieName(name, "credits");

	MoviePlay( pMainFrame->m_hWnd, name, FALSE );

	return(0);
}

LONG	MovieTerminateCredits( void )
{
	MovieEject();
	MovieSetState( MOVIE_NULL_STATE );

	// now send a signal to terminate the credits screen state
	if ( ScrnGetState() == SCRN_ABOUT_STATE )
		ScrnSetState( SCRN_TITLE_STATE );
	else
		ScrnSetState( SCRN_NULL_STATE );

	ShowTheCursor( TRUE );
	pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
	pMainFrame->SetUIOverride(KeyOverride_GAME_TITLE_SCREEN_STATE);
	gpGame->UnPauseGame( PAUSE_MOVIE );

	return(0);
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
BOOL	MovieUIOverride(UINT key, BOOL down)	{
	if (down)
	{
		if (key == VK_RETURN || key == VK_ESCAPE)
		{
			SmackerEject();
			delete pSmackerClip;
			pSmackerClip = NULL;
		}
	}

	return TRUE;						// key taken care of
}


BOOL	IsMovie( BOOL bWin )
{
	SCENARIOREF*	pScenario;

	pScenario = GetScenario();

	if (bWin && strcmp(pScenario->pScenarioWin, "none") == 0)
		return FALSE;

	return TRUE;
}


//------------------------------------------------------------------------
//				MOVIE STATE LOOKUP TABLE
//------------------------------------------------------------------------
MOVIESTATES	MOVIEstateTable[ MOVIE_LAST_STATE ] =
{
	{	MOVIE_3DO_STATE,				// 3DO Intro Avi
		MovieInit3DO,					// Avi state initialization
		MovieTerminate3DO				// Avi state termination
	},

	{	MOVIE_INTRO_STATE,				// ArmyMen Intro Avi
		MovieInitIntro,					// Avi state initialization
		MovieTerminateIntro				// Avi state termination
	},

	{	MOVIE_WIN_STATE,				// ArmyMen Win Avi
		MovieInitWin,					// Avi state initialization
		MovieTerminateWin				// Avi state termination
	},

	{	MOVIE_LOSE_STATE,				// ArmyMen Lose Avi
		MovieInitLose,					// Avi state initialization
		MovieTerminateLose				// Avi state termination
	},

	{	MOVIE_CREDITS_STATE,			// ArmyMen Credits Avi
		MovieInitCredits,				// Avi state initialization
		MovieTerminateCredits			// Avi state termination
	}

};

///========================================================================
//								EOF
///========================================================================
