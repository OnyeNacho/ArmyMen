//========================================================================
//	FILE:			$Workfile: Msg.cpp $
//
//	DESCRIPTION:	Army Unit Message processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, September 17, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Msg.cpp 57    4/14/98 5:28a Aburgess $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	MsgInit()
//		Initialize the MSG processor
//	MsgExit()
//		Terminate the MSG processor.
//========================================================================
//  History
//
//  $Log: /ArmyMen/src/Msg.cpp $
//  
//  57    4/14/98 5:28a Aburgess
//  modifications to re-introduce the initial mission music
//  
//  56    4/14/98 4:24p Nrobinso
//  fix msg audio volume
//  
//  55    4/14/98 2:42p Nrobinso
//  turn off health voice over on sarge death
//  
//  54    4/07/98 3:23p Nrobinso
//  set volume of hq voices
//  
//  53    4/06/98 11:59a Nrobinso
//  cut volume of hq voice overs
//  
//  51    4/02/98 8:46p Nrobinso
//  turn off reched destination msg
//  
//  50    4/02/98 3:21p Phu
//  typecast to avoid warnings
//  
//  49    4/02/98 3:39p Nrobinso
//  change generic win/lose/dies msg names
//  
//  48    4/01/98 3:21p Nrobinso
//  add new v/o's; add text to mission briefings
//  
//  47    4/01/98 10:07a Aburgess
//  remove trace
//  
//  46    4/01/98 9:18a Dmaynard
//  Fixed Compile Error In MsgBroadcastWithText
//  
//  45    4/01/98 12:01a Aburgess
//  trace messages to dash
//  
//  44    3/29/98 4:31p Nrobinso
//  set mutiplayer win/lose v/o's
//  
//  43    3/25/98 7:01p Nrobinso
//  oops, trying to play which, not id
//  
//  42    3/25/98 6:26p Nrobinso
//  
//  41    3/25/98 3:45p Nrobinso
//  play the mission briefing v/o
//  
//  40    3/24/98 2:29p Nrobinso
//  put voice messages with text thru MsgBroadcastWithText
//  
//  39    3/24/98 12:09p Nrobinso
//  remove unused; add a looped msgbroadcast
//  
//  38    3/23/98 11:36a Nrobinso
//  removed enemy approaching; add 3 variants of reaching destination
//  
//  37    3/20/98 11:53a Aburgess
//  modifications made to correct VOICE and MUSIC cut offs. It apprears
//  that ALL Music and Voice streams need to be run with LOOP on.
//  
//  36    3/18/98 3:15p Aburgess
//  MsgBroadcast was using Music File ID rather than Voice File ID
//  
//  35    3/06/98 5:13p Aburgess
//  corrected flag settings for audio creation of voice messages
//  
//  34    1/21/98 1:35p Aburgess
//  fix to illiminate voice orders
//  
//  33    1/05/98 2:31p Aburgess
//  corrected Voice deletions.
//  
//  32    1/05/98 10:32a Aburgess
//  latest attempt to resolve Streaming bug. Voice is now handled in a
//  seperate handler.
//  
//  31    12/22/97 11:32a Aburgess
//  PlayStream interface changes
//  
//  30    12/12/97 9:25a Bwilcox
//  removed clock.h header use
//  
//  29    12/09/97 12:45p Aburgess
//  debug cleanup, and check for VOICEenabled
//  
//  28    12/09/97 12:12p Phu
//  
//  27    12/04/97 9:06a Aburgess
//  Modifications made to support Mission Statement Music and Text.
//  
//  26    11/24/97 2:55p Aburgess
//  Mission statement now accessed from the .CPN data
//  
//  25    11/17/97 2:38p Aburgess
//  removed SND_DELETE_FLAG
//  
//  24    11/17/97 10:05a Aburgess
//  Flushed out SitRep. Removed MsgBroadcast call. Updated audio/snd
//  interface calls
//  
//  23    11/17/97 1:42a Bwilcox
//  Sitrep added
//  
//  22    11/14/97 11:16a Aburgess
//  update of audio support
//  
//  21    11/12/97 10:25a Aburgess
//  now handles SND_NULL_SND_ID value for audio
//  
//  20    11/07/97 10:30a Aburgess
//  Mission Objective message update
//  
//  19    10/27/97 11:28a Aburgess
//  remove Repeat Key data
//  
//  18    10/27/97 10:56a Aburgess
//  Mission Objective broadcast routines
//  
//  17    10/24/97 11:50a Nrobinso
//  remove RepCnt from keyboard interface routines
//  
//  15    9/15/97 10:03a Nrobinso
//  make terminology of campaign/scenario/mission consistent with design
//  
//  14    9/02/97 9:38a Aburgess
//  added VOICE markings to audio call
//  
//  13    8/14/97 1:15p Nrobinso
//  get names for vehicles and sarge
//  
//  12    8/12/97 10:22a Awerner
//  Fixed bug in the sending of the campaign mission message
//  
//  11    8/08/97 10:17a Aburgess
//  moved message to dash message to occur before
//  the attempt to play the audio
//  
//  10    8/07/97 11:53p Nrobinso
//  moved globals.h to stdafx.h
//  
//  9     8/06/97 11:43a Aburgess
//  corrected for object of no army ownership
//  
//  8     8/05/97 2:05p Awerner
//  There's now a little box which gives info on the currently
//  selected target
//  
//  7     7/31/97 9:00a Aburgess
//  hide access to lastMessage inside MSG routines.
//  
//  6     7/30/97 7:04p Aburgess
//  new campaign message, delete message, and other mods to MSG
//  
//  5     7/30/97 5:15p Aburgess
//  new unit message processing
//  
//  4     7/29/97 11:00p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
//  
//  3     7/28/97 4:42p Aburgess
//  checking in for compatibility.
//  
//  2     7/23/97 10:59p Aburgess
//  initial modification of MSG processing
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  13    5/27/97 9:43a Aburgess
//  added snd flags paramter to link creation to insure deletion of linked
//  sounds at playback for messages
//  
//  12    5/21/97 3:16p Dbunch
//  
//  11    5/13/97 4:56p Dbunch
//  
//  10    5/12/97 11:14p Dbunch
//  
//  9     3/12/97 7:59a Aburgess
//  modification to new unit types.
//  
//  8     1/21/97 6:39p Nrobinso
//  added #include Globals.h
//  
//  7     1/08/97 8:08a Aburgess
//  added MSG_DEBUG ifdef
//  
//  6     10/03/96 11:00a Aburgess
//  ignore last  processing if none exists
//  
//  5     10/02/96 11:24a Aburgess
//  removed superfluous TRACE code
//  
//  4     10/01/96 11:54a Aburgess
//  added font application prior to getting text extent.
//  
//  3     9/30/96 4:07p Aburgess
//  added situation, unit ID, and target influence in Message selection.
//  Still attempting to correct formated text.
//  
//  2     9/26/96 11:55a Aburgess
//  first passs implementation of MSG interface
//  
//  1     9/19/96 2:20p Aburgess
//  MSG unit message routines
//  
// 
//  $Nokeywords:$
///========================================================================

#include "stdafx.h"

#include "Army.h"
#include "Text.h"
#include "Audio.h"
#include "AiAccess.h"
#include "ui.h"
#include "stratmap.h"
#include "snd.h"
#include "gameflow.h"
#include "ai.h"
#include "sarge.h"

///========================================================================
//							GLOBAL VARIABLES
///========================================================================
extern	BOOL	bMissionMusic;

///========================================================================
//							LOCAL DEFINES
///========================================================================

///========================================================================
//							LOCAL VARIABLES
///========================================================================
//TIME				MSGdefaultTime = { MONDAY,8,45,30,(UINT)~1 };
//LPDIRECTDRAWSURFACE	pMsgSurface;
//int					nMsgMaxWidth;
//int					nMsgEdgeZone;

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================

///========================================================================
//	Function:		MsgMission()
//
//	Description:
//		broadcast audio version of mission objective and display text version
//		in the dash chat window.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	MsgMission()
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	int				nIndex;

	pCampaign = g_Campaigns[ g_CampaignIndex ];
	nIndex    = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
	pScenario = &(pCampaign->pScenarios[ nIndex ]);
	nIndex    = AiMissionIndex( pScenario, gpGame->MissionID );
	pMission  = &(pScenario->pMissions[ nIndex ]);

	// get the campaign string based on the army and campaign
	if ( pMission->nMissionVoiceID[MISSION_BRIEFING] != SND_NULL_SND_ID )
	{
		// broadcast the message
		MsgBroadcastWithText( pMission->nMissionVoiceID[MISSION_BRIEFING] );
	}

	// see if we need to start the mission music
	if ( bMissionMusic )
		MissionMusic( FALSE );
}


///========================================================================
//	Function:		MsgMissionEnd()
//
//	Description:
//		broadcast audio version of mission objective and display text version
//		in the dash chat window.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	MsgMissionEnd(BOOL winner, BOOL one_player)
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	int				nIndex;
	int				which;
	int				id;
	static			mp_end1[] = {DESERT_MP_WIN, DESERT_MP_DIE, DESERT_MP_LOSE};
	static			mp_end2[] = {ALPINE_MP_WIN, ALPINE_MP_DIE, ALPINE_MP_LOSE};
	static			mp_end3[] = {BAYOU_MP_WIN, BAYOU_MP_DIE, BAYOU_MP_LOSE};

	if (one_player)	{
		pCampaign = g_Campaigns[ g_CampaignIndex ];
		nIndex    = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
		pScenario = &(pCampaign->pScenarios[ nIndex ]);
		nIndex    = AiMissionIndex( pScenario, gpGame->MissionID );
		pMission  = &(pScenario->pMissions[ nIndex ]);

		if (winner)
			which = MISSION_WIN;
		else if (!GetSargeHealthPercentage())
			which = MISSION_DIE;
		else
			which = MISSION_LOSE;

		id = pMission->nMissionVoiceID[which];
	}
	else	{
		if (winner)
			which = 0;
		else if (!GetSargeHealthPercentage())
			which = 1;
		else
			which = 2;

		int nChoice = rand() % 3;
		switch( nChoice )
		{
		case 0:
			id = mp_end1[which];
			break;
		case 1:
			id = mp_end2[which];
			break;
		default:
			id = mp_end3[which];
			break;
		}
	}

	// get the campaign string based on the army and campaign
	if ( id != SND_NULL_SND_ID )
	{
		// broadcast the message
		MsgBroadcastWithText( id );
	}
}


///========================================================================
//	Function:		MsgBroadcastWithText()
//
//	Description:
//		Broadcast a message using the audio streaming system and display text
//
//	Input:			nAudioID	stream snd ID for the message to broadcast
//
//	Ouput:			none
//
///========================================================================

ULONG	MsgBroadcastWithText( ULONG nAudioID, int volume_percent )
{
	ULONG	nSndID;

	nSndID = MsgBroadcast( nAudioID, volume_percent );

	char *pMessage = voiceFindText( nAudioID );

	if ( pMessage  )
	{
		ReceiveDashMessage( pMessage, NULL );
	}

	return nSndID;
}

///========================================================================
//	Function:		MsgBroadcast()
//
//	Description:
//		Broadcast a message using the audio streaming system.
//
//	Input:			nAudioID	stream snd ID for the message to broadcast
//
//	Ouput:			none
//
///========================================================================

ULONG	MsgBroadcast( ULONG nAudioID, int volume_percent )
{
	USHORT		bFlags;
	ULONG		nSndID = SND_NULL_SND_ID;

	if ( !VOICEenabled )	return nSndID;
	if ( nAudioID == SND_NULL_SND_ID )	return nSndID;

	volume_percent = (volume_percent * audioGetMasterVolume( SND_VOICE_FLAG ))/100;
	if (!volume_percent)
		return nSndID;

	bFlags  = (SND_STREAM_FLAG|SND_VOICE_FLAG|SND_DELETE_FLAG);
	nSndID = audioCreateSnd( AUDIOvoiceID, nAudioID, 0, bFlags );
	if ( nSndID == SND_NULL_SND_ID )
	{
		// report an error
		TRACE("ERROR: failed to load voice (%ld). [%s:%d]\n", 
			nAudioID, __FILE__, __LINE__ );
	}

	if ( nSndID != SND_NULL_SND_ID )
	{
		audioStoreSnd( nAudioID, nSndID, bFlags );
		if ( nSndID != SND_NULL_SND_ID )
		{
			sndPlay( nSndID );
			SndSetVolumePercent(nSndID, volume_percent, FALSE);
		}
	}

	return nSndID;
}


///========================================================================
//	Function:		SitRep()
//	Description:	tell user about a situation on the battlefield.
///========================================================================

void	SitRep(int situation, ITEM* pItem)
{
	int		nChoice;
	char*	pMessage = NULL;
	ULONG	nVoiceID = SND_NULL_SND_ID;

	switch( situation )
	{
//	case ARMY_NO_ACTION:
//	case ARMY_UNDER_ATTACK:
//	case ARMY_ATTACKING:
//	case ARMY_ELIMINATED:
//	case ARMY_ENGAGED:
//	case ARMY_DISENGAGED:
//	case ARMY_APPROACH:
//		nVoiceID = APPROACHING;
//		break;
	case ARMY_SUFFERING:
		nVoiceID = MENDOWN;
		break;
		/*
	case ARMY_REACHED:
		nChoice = rand() % 3;
		switch( nChoice )
		{
		case 0:
			nVoiceID = DESTINATION;
			break;
		case 1:
			nVoiceID = DESTINATION;
			break;
		default:
			nVoiceID = DESTINATION;
			break;
		}
		break;
		*/
	case ARMY_ORDERACK:
		nChoice = rand() % 3;
		switch( nChoice )
		{
		case 0:
			nVoiceID = ONWAY;
			break;
		case 1:
			nVoiceID = YESSIR;
			break;
		default:
			nVoiceID = AFFIRMATIVE;
			break;
		}
		break;
	case ARMY_GOTOACK:
		nChoice = rand() % 3;
		switch( nChoice )
		{
		case 0:
			nVoiceID = ONWAY;
			break;
		case 1:
			nVoiceID = YESSIR;
			break;
		default:
			nVoiceID = AFFIRMATIVE;
			break;
		}
		break;
	}

	if ( nVoiceID != SND_NULL_SND_ID )
	{
		pMessage = voiceFindText( nVoiceID );
		MsgBroadcast( nVoiceID );
	}
}

///========================================================================
//								EOF
///========================================================================
