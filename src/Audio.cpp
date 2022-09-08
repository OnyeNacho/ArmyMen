//========================================================================
//	FILE:			$Workfile: Audio.cpp $
//
//	DESCRIPTION:	Audio processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, May 02, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Audio.cpp 99    4/10/98 3:07p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	audioInit()
//		Initialize the audio processor
//	audioExit()
//		Terminate the audio processor.
//	audioOpen()
//		Open an audio sound file.
//	audioClose()
//		Close an audio sound file.
//	audioCreateSnd()
//		Create an audio sound instance.
//	audioCue()
//		Cue up an audio sound instance.
//	audioPlay()
//		Play an audio sound instance.
//	audioStop()
//		Stop an audio sound instance.
//	audioDelete()
//		Stop an audio sound instance.
//	audioGetFrequency()
// 		Get the Global Frequency levels (effect pitch)
//	audioSetFrequency()
// 		Set the Global Frequency levels (effect pitch)
//	audioGetVolume()
// 		Get the Global Volume levels:
//	audioSetVolume()
// 		Set the Global Volume levels:
//	audioGetPan()
// 		Get Global Pan levels
//	audioSetPan()
// 		Set Global Pan levels
//	audioCreateLink()
//		Create a linked audio stream.
//	audioSetLink()
//		Stop an audio sound instance.
//------------------------------------------------------------------------
//	audioStoreFile()
//		Save off the audio file access information.
//	audioDeleteFile()
//		Delete the audio file access information.
//	audioStoreSnd()
// 		terminate audio test driver
//	audioGetSndBySndID()
// 		retrieve a SND from the lookuptable using the SND ID as key.
//	audioGetSndByAudioID()
// 		retrieve a SND from the lookuptable using the AUDIO ID as key.
//	audioDeleteSnd()
// 		delete an audio SND from the lookup table.
//------------------------------------------------------------------------
//  History
//
//  $Log: /ArmyMen/src/Audio.cpp $
//  
//  99    4/10/98 3:07p Nrobinso
//  fix audio level problem
//  
//  98    4/08/98 11:45p Nrobinso
//  remove unused
//  
//  97    4/07/98 3:21p Nrobinso
//  change order of audio play and volume
//  
//  95    4/02/98 2:03p Phu
//  typecasting to prevent warnings
//  
//  94    3/25/98 2:10p Aburgess
//  added access to SFX via PlayStream/PlayStreamUnit
//  
//  93    3/25/98 1:33p Aburgess
//  modification to call playstream with the proper DELETE flag setting
//  
//  92    3/22/98 3:58p Nrobinso
//  remove static streams
//  
//  91    3/22/98 2:49p Nrobinso
//  remove vehicle audio call by audiostopall; add script loop off command
//  
//  90    3/21/98 6:54a Nrobinso
//  fix crash bugs
//  
//  89    3/20/98 4:08p Aburgess
//  added special audio off calls for potential Vehicle sounds
//  
//  88    3/20/98 11:53a Aburgess
//  modifications made to correct VOICE and MUSIC cut offs. It apprears
//  that ALL Music and Voice streams need to be run with LOOP on.
//  
//  87    3/19/98 2:17p Aburgess
//  corrected sound deletion bug
//  
//  86    3/18/98 2:21p Aburgess
//  modifications to stop and delete audio test sounds
//  
//  85    3/18/98 11:51a Aburgess
//  converted ON/OFF reg references to ON/OFF_CONFIG. added Debug.
//  
//  84    3/18/98 8:20a Aburgess
//  modifications to AUDIOsounds compression
//  
//  83    3/18/98 2:55a Nrobinso
//  fix string length bug
//  
//  82    3/18/98 2:43a Nrobinso
//  get music to actually go on
//  
//  81    3/18/98 2:29a Nrobinso
//  add volume saving in registry
//  
//  80    3/18/98 12:50a Nrobinso
//  clean up registry access
//  
//  79    3/17/98 3:09p Aburgess
//  registry storage of Audio parameters and Config parameter
//  
//  78    3/17/98 11:18a Aburgess
//  correction of on/off setting of SFX,MUSIC,VOICE
//  
//  77    3/16/98 6:22p Aburgess
//  attempt to correct audio deletion problems
//  
//  76    3/16/98 3:32p Aburgess
//  correction of Audio deletion
//  
//  75    3/16/98 12:56p Aburgess
//  modifications to support vehicle decel,acel,and looping
//  
//  74    3/16/98 10:34a Aburgess
//  modifications made to pulee setting of minimum timerEvent period and
//  termination to audioEnable() and audioDisable() respectively.
//  
//  73    3/09/98 12:03p Aburgess
//  added missing parenthesis
//  
//  72    3/07/98 11:50p Nrobinso
//  move .h file to stdafx
//  
//  71    3/06/98 5:17p Aburgess
//  correction of audio flags and volume modifications
//  
//  70    3/02/98 10:31a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  69    2/25/98 10:31p Nrobinso
//  have audioPlayItem use audioGetSndByAudioID
//  
//  68    2/25/98 10:24a Nrobinso
//  audioPlayItem saves the sound if it isn't a;ready saved
//  
//  67    2/24/98 1:37p Aburgess
//  disabled debug
//  
//  66    2/24/98 10:45a Aburgess
//  modifications made to correct no audio on continue game problem
//  
//  65    2/20/98 6:13p Nrobinso
//  remove static sfx
//  
//  64    2/20/98 4:31p Aburgess
//  added debug
//  
//  63    2/20/98 1:16p Nrobinso
//  fix up sounds
//  
//  62    2/20/98 12:00p Aburgess
//  modifications to support clean up and deletion of SFX sounds
//  
//  61    2/17/98 7:49p Nrobinso
//  get rid of audio kill
//  
//  60    2/17/98 8:53a Aburgess
//  added flag parameters. 
//  
//  59    2/13/98 3:59p Nrobinso
//  remove avi player
//  
//  58    2/13/98 10:27a Aburgess
//  removed superfluous trace statements
//  
//  57    2/13/98 10:06a Aburgess
//  modifications made to further support keyboard configurations. Support
//  of Audio slider bar. implementation of all known buttons
//  
//  56    2/12/98 12:52p Nrobinso
//  
//  55    2/03/98 2:41p Aburgess
//  modifications made to correct music stream failures
//  
//  54    2/01/98 5:45p Nrobinso
//  remove TESTPATH
//  
//  53    1/28/98 10:09a Aburgess
//  modifications made to correct Audio memory leaks on exit
//  
//  52    1/26/98 11:59a Nrobinso
//  new path defines
//  
//  51    1/21/98 2:03p Nrobinso
//  modification to stream updates for non queued items
//  
//  50    1/21/98 9:22a Aburgess
//  modifications made to shorten the STRM and VOICE monitor interrupts.
//  Also merged the audio ON/OFF switching. In addition, all audio is now
//  turned off during mission load as that routine has a large frame
//  overrun problem disallowing updates to audio.
//  
//  49    1/20/98 12:46a Aburgess
//  lastest working murder
//  
//  48    1/14/98 3:25p Aburgess
//  re-application of SMACKCLIPS compile time flag
//  
//  47    1/14/98 2:16p Aburgess
//  modifications made to support GAME_PLAY Options screens
//  
//  46    1/12/98 2:31p Aburgess
//  PlayStream was not checking for the various sound processors being
//  enabled.
//  
//  45    1/05/98 2:31p Aburgess
//  corrected Voice deletions.
//  
//  44    1/05/98 10:32a Aburgess
//  latest attempt to resolve Streaming bug. Voice is now handled in a
//  seperate handler.
// 
//  $Nokeywords:$
///========================================================================

#include "stdafx.h"

#include "comm.h"
#include "audio.h"			// AUDIO       defines, structures, and prototypes
#include "sounds.h"
#include "streams.h"
#include "voice.h"

#include "miscfile.h"
#include "GameFlow.h"
#include "MainFrm.h"
#include "gameproc.h"
#include "ui.h"
#include "Msg.h"
#include "Screen.h"
#include "Vehicle.h"

extern	char*	audioIDname( ULONG nAudioID );

///========================================================================
//							externs
///========================================================================
extern SPOINT		AudioPosition();
extern SND_NAMES	SND_sounds_Names[];
extern SND_NAMES	SND_streams_Names[];
extern SND_NAMES	SND_voices_Names[];
extern int			GFnRestore;

extern	ULONG		SCRNsfxSnd;
extern	ULONG		SCRNmusicSnd;
extern	ULONG		SCRNvoiceSnd;

///========================================================================
//							LOCAL DEFINES
///========================================================================
#define ASD_PATH BASE_WORK_PATH

#define OFF_LEN 3
#define AUDIO_REG_SIZE sizeof(OFF_CONFIG)

char ON_CONFIG[] = "ON 100";
char OFF_CONFIG[] = "OFF100";

///========================================================================
//							LOCAL DATA
///========================================================================

///========================================================================
//							LOCAL VARIABLES
///========================================================================

static BOOL				AUDIOdSoundEnabled;	// DirectSound Enabled flag

static LONG				AUDIOfrequency;		// base frequency
static LONG				AUDIOvolume;		// base volume
static LONG				AUDIOpan;			// base pan
static LONG				AUDIOintensity;		// LO-HI intensity of music

static FILE*	        AUDIOsoundFile;
static FILE*	        AUDIOstreamFile;
static FILE*	        AUDIOvoiceFile;

static ULONG			AUDIOcurrentSound;
static ULONG			AUDIOcurrentMaxSound;

static AUDIO_IDS		AUDIOsounds[ AUDIO_MAX_SOUNDS ];
static unsigned			AUDIOsoundIndex;
static unsigned			AUDIOmaxSoundIndex;

static unsigned			AUDIOstate;
static unsigned			AUDIOfiles[ AUDIO_MAX_FILES ];

static ULONG			AUDIOlinks[ AUDIO_MAX_SOUNDS ];
static unsigned			AUDIOlinkIndex;

static ULONG			nVolSndID;
static LONG				nVolTestStart;

BOOL					AUDIOsfxOn   = TRUE;
BOOL					AUDIOmusicOn = TRUE;
BOOL					AUDIOvoiceOn = TRUE;

char					AUDIOfileSearch[128];	// path and file name for .ASD accesses

	   

///========================================================================
//							GLOBAL VARIABLES
///========================================================================
ULONG			AUDIOsfxID;
ULONG			AUDIOstreamID;
ULONG			AUDIOvoiceID;

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
BOOL		audioSetLink( ULONG nSndID, ULONG nPreviousID, USHORT bFlags );
void		audioStoreFile( unsigned nFileID );
AUDIO_IDS*	audioGetSndBySndID( ULONG nSndID );
AUDIO_IDS*	audioGetSndByAudioID( ULONG nAudioID );
void		audioTestKeys( UINT nChar );
void		Set_SFX_Volume_Percent(ULONG nSndID , ULONG Percent, BOOL bMax);
void		Modify_SFX_Volume_Percent( ULONG nSndID ,ULONG Percent);
int			audioFindVolumePercent( SPOINT *pSrc );
void		StopStream(ULONG nAudioID);
void		audioCompressSoundList( void );

///========================================================================
//	Function:		audioInit()
//
//	Description:
//		Initialize the audio processor to handle up to nNumberSfxSounds
//		and and nNumberStrmSounds sounds
//
//	Input:			none
//
//	Ouput:			error			FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		audioInit( HWND baseWnd )
{
	unsigned	snd;
	char		bData[AUDIO_REG_SIZE];
	DWORD		dwSize;
	BOOL		error = TRUE;		// assume failure
	int			volume;

#ifdef TRACK
	TRACE("Entered: audioInit()...\n" );
#endif

	if ( AUDIOdSoundEnabled )
	{
		error = FALSE;
		goto exit;
	}
 
	// initialize the base values
	AUDIOdSoundEnabled   = FALSE;
	AUDIOstate           = AUDIO_INIT_STATE;
	AUDIOfrequency       = 0L;
	AUDIOvolume          = 0L;
	AUDIOpan             = 0L;
	AUDIOcurrentSound    = 0;
	AUDIOcurrentMaxSound = 0;
	AUDIOsfxID           = 0;
	AUDIOstreamID        = 0;
	AUDIOvoiceID         = 0;
	AUDIOintensity       = AUDIO_INTENSITY_LO;

	// initialize the file register
	for( snd=0; snd<AUDIO_MAX_FILES; ++snd )
		AUDIOfiles[ snd ] = (unsigned)SND_NULL_SND_ID;

	// initialize the sound lookup table
	for( snd=0; snd<AUDIO_MAX_SOUNDS; ++snd )
	{
		AUDIOsounds[ snd ].nAudioID = SND_NULL_SND_ID;
		AUDIOsounds[ snd ].nSndID   = SND_NULL_SND_ID;
		AUDIOsounds[ snd ].bFlags   = SND_CLEAR_FLAG;
		AUDIOsounds[ snd ].nVolume  = 0;
	}
	AUDIOsoundIndex    = 0;
	AUDIOmaxSoundIndex = 0;


	gpGame->Sfx = TRUE;
	dwSize = AUDIO_REG_SIZE;
	if (gpComm->RegGet(TEXT("AudioSFX"), (LPBYTE)&bData, &dwSize))
	{
		if ( strncmp( bData, OFF_CONFIG, OFF_LEN ) == 0 )
			gpGame->Sfx = FALSE;

		volume = atoi( bData+OFF_LEN );
		audioSetMasterVolume( SND_SFX_FLAG, (LONG)volume );
	}


	gpGame->Music = TRUE;
	dwSize = AUDIO_REG_SIZE;
	if (gpComm->RegGet(TEXT("AudioMUSIC"), (LPBYTE)&bData, &dwSize))
	{
		if ( strncmp( bData, OFF_CONFIG, OFF_LEN ) == 0 )
			gpGame->Music = FALSE;

		volume = atoi( bData+OFF_LEN );
		audioSetMasterVolume( SND_MUSIC_FLAG, (LONG)volume );
	}


	gpGame->Voice = TRUE;
	dwSize = AUDIO_REG_SIZE;
	if (gpComm->RegGet(TEXT("AudioVOICE"), (LPBYTE)&bData, &dwSize))
	{
		if ( strncmp( bData, OFF_CONFIG, OFF_LEN ) == 0 )
			gpGame->Voice = FALSE;

		volume = atoi( bData+OFF_LEN );
		audioSetMasterVolume( SND_VOICE_FLAG, (LONG)volume );
	}


	// enable direct sound audio
	audioEnable( pMainFrame->m_hWnd );

	// store the current audio settings
	AudioSetReg();

	// if we made it here, we were successful
	error = FALSE;

exit:

#ifdef TRACK
TRACE("Exited: audioInit()...\n" );
#endif
 
	return( error );
}


void AudioSetReg()
{
	char*		pData;
	int			volume;

	pData = OFF_CONFIG;
	if ( gpGame->Sfx )
		pData = ON_CONFIG;
	volume = audioGetMasterVolume( SND_SFX_FLAG );
	_itoa( volume, pData+OFF_LEN, 10 );
	gpComm->RegSet(TEXT("AudioSFX"), (CONST BYTE *)pData, AUDIO_REG_SIZE);

	pData = OFF_CONFIG;
	if (  gpGame->Music )
		pData = ON_CONFIG;
	volume = audioGetMasterVolume( SND_MUSIC_FLAG );
	_itoa( volume, pData+OFF_LEN, 10 );
	gpComm->RegSet(TEXT("AudioMUSIC"), (CONST BYTE *)pData, AUDIO_REG_SIZE);

	pData = OFF_CONFIG;
	if (  gpGame->Voice )
		pData = ON_CONFIG;
	volume = audioGetMasterVolume( SND_VOICE_FLAG );
	_itoa( volume, pData+OFF_LEN, 10 );
	gpComm->RegSet(TEXT("AudioVOICE"), (CONST BYTE *)pData, AUDIO_REG_SIZE);
}


///========================================================================
//	Function:		audioExit()
//
//	Description:
//		Terminate the audio processor.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void		audioExit( void )
{
#ifdef TRACK
TRACE("Entered: audioExit()...\n" );
#endif

	// terminate the audio processing
	if ( AUDIOdSoundEnabled )
		audioDisable();
	else
		audioClear();

#ifdef MAX_AUDIO
	TRACE( "AUDIOmaxSoundIndex = %d\n", AUDIOmaxSoundIndex );
#endif

#ifdef TRACK
TRACE("Exit: audioExit()...\n" );
#endif
 
}

///========================================================================
//	Function:		audioEnable()
//
//	Description:
//		Enable the audio processor
//
//	Input:			baseWnd			application base window handle
//
//	Ouput:			error			FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		audioEnable( HWND baseWnd )
{
#ifndef AUDIO_OFF
	unsigned	nFileID;
	unsigned	totalSounds;
#endif
	BOOL		error = TRUE;		// assume failure

#ifndef AUDIO_OFF
	// make sure we haven't already been enabled
	if ( AUDIOdSoundEnabled )
	{
		// everything already enabled
		error = FALSE;
		goto exit;
	}
 
#ifdef DBG_AUDIO
	TRACE("\n\naudioEnable( AUDIOdSoundEnabled:%d )\n", AUDIOdSoundEnabled );
	TRACE("    Game State     = %s\n", GetStateName( gpGame->GetState() ) );
	TRACE("    Game Sub State = %s\n", GetSubStateName( gpGame->GetSubState() ) );
	TRACE("    Scrn State     = %s\n", ScrnGetStateName( ScrnGetState() ) );
#endif

	// enable DirectSound
	AUDIOdSoundEnabled = TRUE;

#ifdef AUDIO_TIMER
	// Now set the minimum timer resolution for this stream
	if ( timeBeginPeriod( (UINT)((STRM_PLAYBACK_TIMER_PERIOD/STRM_PLAYBACK_OVERSAMPLE)>>1) ) != 0)
	{
		// report an error
		TRACE("ERROR: timeBeginPeriod failed. [%s:%d]\n", __FILE__, __LINE__ );
		goto cleanUp;
	}
#endif

	// Calc the total numberof sounds, assume 2X for duplicate instances
	totalSounds = (((AUDIO_MAX_STREAMS+AUDIO_MAX_SFXS)<<1)+AUDIO_MAX_VOICES);
	if ( totalSounds > AUDIO_MAX_SOUNDS )
	{
		// report an error
		TRACE("ERROR: total sounds exceeds application max (%d). [%s:%d]\n", 
			AUDIO_MAX_SOUNDS, __FILE__, __LINE__ );
		goto cleanUp;
	}

	// now initialize the SFX and STRM buffers
	if ( sndInit( baseWnd, totalSounds ) )
	{
		// report an error
		TRACE("ERROR: SND initialization failed. [%s:%d]\n", 
			__FILE__, __LINE__ );
		goto cleanUp;
	}

	if ( sfxInit( AUDIO_MAX_SFXS ) )
	{
		// report an error
		TRACE("ERROR: SFX initialization failed. [%s:%d]\n", 
			__FILE__, __LINE__ );
		goto cleanUp;
	}

	if ( strmInit( AUDIO_MAX_STREAMS ) )
	{
		// report an error
		TRACE("ERROR: STRM initialization failed. [%s:%d]\n", 
			__FILE__, __LINE__ );
		goto cleanUp;
	}

	if ( voiceInit( AUDIO_MAX_VOICES ) )
	{
		// report an error
		TRACE("ERROR: STRM initialization failed. [%s:%d]\n", 
			__FILE__, __LINE__ );
		goto cleanUp;
	}

	// open a sound file
	SetPath( AUDIO_PATH );
	strcpy(AUDIOfileSearch, "sounds.asd");
	nFileID    = audioOpen( AUDIOfileSearch, SND_SFX_FLAG );
	AUDIOsfxID = nFileID;
	SFXenabled = TRUE;
	if ( AUDIOsfxID == SND_NULL_SND_ID )
	{
		// report an error
		TRACE("ERROR: failed to open sounds.ASD file. [%s:%d]\n", 
			__FILE__, __LINE__ );
		SFXenabled = FALSE;
	}

	// open a stream file
	SetPath( AUDIO_PATH );
	strcpy(AUDIOfileSearch, "streams.asd");
	nFileID       = audioOpen( AUDIOfileSearch, SND_STREAM_FLAG|SND_MUSIC_FLAG );
	AUDIOstreamID = nFileID;
	STRMenabled   = TRUE;
	if ( AUDIOstreamID == SND_NULL_SND_ID )
	{
		// report an error
		TRACE("ERROR: failed to open streams.ASD file. [%s:%d]\n", 
			__FILE__, __LINE__ );
		STRMenabled = FALSE;
	}

	// open a stream file
	SetPath( AUDIO_PATH );
	strcpy(AUDIOfileSearch, "voices.asd");
 	nFileID      = audioOpen( AUDIOfileSearch, SND_STREAM_FLAG|SND_VOICE_FLAG );
	AUDIOvoiceID = nFileID;
	VOICEenabled = TRUE;
	if ( AUDIOvoiceID == SND_NULL_SND_ID )
	{
		// report an error
		TRACE("ERROR: failed to open voices.ASD file. [%s:%d]\n", 
			__FILE__, __LINE__ );
		VOICEenabled = FALSE;
	}

	if (!SFXenabled || !STRMenabled || !VOICEenabled )
		goto cleanUp;

	// if you made it this fair, you were successful
	error = FALSE;
	goto exit;

cleanUp:
	// disable DirectSound
	AUDIOdSoundEnabled = FALSE;

exit:

	if ( gpGame->Sfx )
		audioSfxOn();
//	else
//		audioSfxOff();
	if ( gpGame->Music )
		audioMusicOn();
//	else
//		audioMusicOff();
	if ( gpGame->Voice )
		audioVoiceOn();
//	else
//		audioVoiceOff();

#else
	AUDIOdSoundEnabled = FALSE;
	error              = FALSE;
#endif 
	return( error );
}

///========================================================================
//	Function:		audioDisable()
//
//	Description:
//		Disable the audio processor.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void		audioDisable( void )
{
	// free up the voice text
	voiceFreeText();

	// make sure we haven't already been disabled
	if ( !AUDIOdSoundEnabled )
		return;

#ifdef DBG_AUDIO
	TRACE("\n\naudioDisable( AUDIOdSoundEnabled:%d )\n", AUDIOdSoundEnabled );
	TRACE("    Game State     = %s\n", GetStateName( gpGame->GetState() ) );
	TRACE("    Game Sub State = %s\n", GetSubStateName( gpGame->GetSubState() ) );
	TRACE("    Scrn State     = %s\n", ScrnGetStateName( ScrnGetState() ) );
#endif

	// stop all streams
//	StopAllStreams();
	audioStopAll();

#ifdef AUDIO_TIMER
	timeEndPeriod( (UINT)((STRM_PLAYBACK_TIMER_PERIOD/STRM_PLAYBACK_OVERSAMPLE)>>1) );
#endif

	// now cleanup any allocated tables
	audioClear();
}

void		audioClear( void )
{
	unsigned	nFileCount;

#ifdef DBG_AUDIO
	TRACE("\n\naudioClear( AUDIOdSoundEnabled:%d )\n", AUDIOdSoundEnabled );
	TRACE("    Game State     = %s\n", GetStateName( gpGame->GetState() ) );
	TRACE("    Game Sub State = %s\n", GetSubStateName( gpGame->GetSubState() ) );
	TRACE("    Scrn State     = %s\n", ScrnGetStateName( ScrnGetState() ) );
#endif

	// clear all audio files created
	for( nFileCount=0; nFileCount<AUDIO_MAX_FILES; ++nFileCount )
	{
		if ( AUDIOfiles[ nFileCount ] != SND_NULL_SND_ID )
		{
			sndDeleteFile( AUDIOfiles[ nFileCount ] );
			AUDIOfiles[ nFileCount ] = SND_NULL_SND_ID;
		}
	}
	
	// clean up
	voiceExit();			// clean up the VOICE data

	strmExit();				// clean up the STRM data

	sfxExit();				// clean up the SFX data

	sndExit();				// clean up the SND data

	// disable DirectSound
	AUDIOdSoundEnabled = FALSE;
}

///========================================================================
//	Function:		audioOpen()
//
//	Description:
//		Open an audio sound file.
//
//	Input:			pFileName	name of file to be opened
//					bFlags		how to treat the file	
//
//	Ouput:			nFileID		id assigned to this file
//								AUDIO_ERR if failure
//
///========================================================================

unsigned	audioOpen( char* pFileName, USHORT bFlags )
{
	unsigned	nFileID = (unsigned)AUDIO_ERR;

#ifdef TRACK
TRACE("Entered: audioOpen()...\n" );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// determine the type of file this
	if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
		nFileID = voiceOpen( pFileName );
	else
	if ( (bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
		nFileID = strmOpen( pFileName );
	else
	if ( (bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
		nFileID = sfxOpen( pFileName );

	// now store off this data for later
	if ( nFileID != SND_NULL_SND_ID )
		audioStoreFile( nFileID );

exit:

#ifdef TRACK
TRACE("Exit: audioOpen()...\n" );
#endif

	return( nFileID );
 
}

///========================================================================
//	Function:		audioClose()
//
//	Description:
//		Close an audio sound file.
//
//	Input:			nFileID		ID of file to close
//
//	Ouput:			none
//
///========================================================================

void	audioClose( unsigned nFileID )
{
	unsigned	nFileCount;

#ifdef TRACK
TRACE("Entered: audioClose()...\n" );
#endif

	for( nFileCount=0; nFileCount<AUDIO_MAX_FILES; ++nFileCount )
	{
		if ( AUDIOfiles[nFileCount] == nFileID )
		{
			sndDeleteFile( nFileID );
			AUDIOfiles[nFileCount] = SND_NULL_SND_ID;
		}
	}	

#ifdef TRACK
TRACE("Exit: audioClose()...\n" );
#endif
 
}

///========================================================================
//	Function:		audioCreateSnd()
//
//	Description:
//		Create an audio sound instance.
//
//	Input:			nFileID			id of file to access
//					nAudioID		sound Id number to be created
//					nIndexToLoad	index within .SND file from which to
//									load sound
//					bFlags			falgs associated with this sound.
//
//	Ouput:			nFileID		id assigned to this file
//								AUDIO_ERR if failure
//
///========================================================================

unsigned	audioCreateSnd( unsigned nFileID, ULONG nAudioID,
						    unsigned nIndexToLoad, USHORT bFlags )
{
	ULONG	nSndID = (unsigned)AUDIO_ERR;

#ifdef TRACK
TRACE("Entered: audioCreateSnd()...\n" );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// is this a valid audio ID
	if ( nAudioID == SND_NULL_SND_ID )
	{
		// no error, simply ignore
		goto exit;
	}

	// determine the type of file this
	if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
		nSndID   = voiceLoad( nFileID, nAudioID, nIndexToLoad, bFlags );
	else
	if ( (bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
		nSndID   = strmLoad( nFileID, nAudioID, nIndexToLoad, bFlags );
	else
		nSndID   = sfxLoad( nFileID, nAudioID, nIndexToLoad, bFlags );

#ifdef SND_DEBUG
TRACE( "Creating Audio: %d %s %d\n", nAudioID, audioIDname( nAudioID ), nSndID );
#endif

exit:

#ifdef TRACK
TRACE("Exit: audioCreateSnd()...\n" );
#endif

	return( nSndID );
 
}

///========================================================================
//	Function:		audioCue()
//
//	Description:
//		Cue up an audio sound instance.
//
//	Input:			nSndID		name of file to be opened
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	audioCue( ULONG nSndID )
{
	AUDIO_IDS*	pInfo;
	BOOL		result;
	BOOL		error = TRUE;		// assume an error

#ifdef TRACK
TRACE("Entered: audioCue( %ld )...\n", nSndID );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// is this a valid snd ID
	if ( nSndID == SND_NULL_SND_ID )
	{
		// no error, simply ignore
		error = FALSE;
		goto exit;
	}

	// start by getting the flags for this snd
	pInfo = audioGetSndBySndID( nSndID  );
	if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: failed to locate SND (%ld). [%s:%d]\n", 
			  nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// determine the type of sound this is. Only STREAM sounds can be cued
	if ( (pInfo->bFlags & SND_SFX_FLAG) != SND_SFX_FLAG )
	{
		error = FALSE;			// assume everything OK
		result = FALSE;
		while( !result && (nSndID != SND_NULL_SND_ID) )
		{
			if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
				result = voiceCue( pInfo->nAudioID );
			else
				result = strmCue( pInfo->nAudioID );
			if (!result)
			{
				if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
					nSndID = voiceNextLink( pInfo->nSndID );
				else
					nSndID = strmNextLink( pInfo->nSndID );
			}
			else
				error = TRUE;
		}
	}
	if ( error )
		goto exit;

	// got here so we must be ok
	error = FALSE;

exit:

#ifdef TRACK
TRACE("Exit: audioCue()...\n" );
#endif

	return( error );
 
}

///========================================================================
//	Function:		audioPlay()
//
//	Description:
//		Play an audio sound instance.
//
//	Input:			nAudioID	audio ID to be played
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	audioPlay( ULONG nAudioID, USHORT bFlags )
{
	AUDIO_IDS*	pInfo;
	ULONG		nSndID;
	BOOL		error = TRUE;		// assume an error

#ifdef TRACK
	TRACE("Entered: audioPlay( %ld : %ld )...\n", nAudioID, bFlags );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// ignore NULL sound IDs
	if ( nAudioID == SND_NULL_SND_ID )
	{
		// no error, simply ignore
		error = FALSE;
		goto exit;
	}

	// start by getting the flags for this snd
	pInfo = audioGetSndByAudioID( nAudioID );
	if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
	{
		// check to see if there are any flags, if so
		// create the sound
		if ( bFlags != SND_CLEAR_FLAG )
		{
			if ( (bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
				nSndID = audioCreateSnd( AUDIOsfxID, nAudioID, 0, bFlags );
			else
			if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
				nSndID = audioCreateSnd( AUDIOvoiceID, nAudioID, 0, bFlags );
			else
			if ( (bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
				nSndID = audioCreateSnd( AUDIOstreamID, nAudioID, 0, bFlags );

			if ( (bFlags & SND_DELETE_FLAG) != SND_DELETE_FLAG )
				audioStoreSnd( nAudioID, nSndID, bFlags );
#if 0
			else
				TRACE( "audioPlay() not storing %s a:%ld s:%ld f:",
					audioIDname( nAudioID ), nSndID );
				if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
					TRACE( "VOICE " );
				if ( (bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
					TRACE( "MUSIC " );
				if ( (bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
					TRACE( "SFX " );
				if ( (bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG )
					TRACE( "LOOP " );
				if ( (bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG )
					TRACE( "DELETE " );
				TRACE( ")\n" );
#endif
		}
		else
		{
			error = FALSE;
			goto exit;
		}
	}
	else
	{
		nSndID = pInfo->nSndID;
		if ( bFlags == SND_CLEAR_FLAG )
			bFlags = pInfo->bFlags;
	}

	// determine the type of sound this is.
	error = FALSE;
	if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
	{
		if ( audioVoiceGetOn() )
			error = voicePlaySnd( nSndID );
	}
	else
	if ( (bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
	{
		if ( audioMusicGetOn() )
			error = strmPlaySnd( nSndID );
	}
	else
	if ( (bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
	{
		if ( audioSfxGetOn() )
			error = sfxPlaySnd( nSndID );
	}

exit:

#ifdef TRACK
TRACE("Exit: audioPlay()...\n" );
#endif

	return( error );
 
}

///========================================================================
//	Function:		sndPlay()
//
//	Description:
//		Play a created SndID sound instance.
//
//	Input:			nSndID		Snd ID to be played
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	sndPlay( ULONG nSndID )
{
	AUDIO_IDS*	pInfo;
	BOOL		error = TRUE;		// assume an error

#ifdef TRACK
TRACE("Entered: sndPlay( %ld )...\n", nSndID );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

#ifdef AUDIO_DBG
TRACE("sndPlay(%s:%ld)\n",audioSndIDname( nSndID ), nSndID );
#endif

	// ignore NULL sound IDs
	if ( nSndID == SND_NULL_SND_ID )
	{
		// no error, simply ignore
		error = FALSE;
		goto exit;
	}

	// start by getting the flags for this snd
	pInfo = audioGetSndBySndID( nSndID  );
	if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
	{
		// no error, simply ignore
		error = FALSE;
		goto exit;
	}

#ifdef SND_DEBUG
	TRACE( "sndPlay( %1d, %s, %ld )\n", pInfo->nAudioID,
		audioIDname( pInfo->nAudioID ), pInfo->nSndID );
#endif

	// determine the type of sound this is.
	error = FALSE;
	if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
	{
		if ( audioVoiceGetOn() )
			error = voicePlaySnd( pInfo->nSndID );
	}
	else
	if ( (pInfo->bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
	{
		if ( audioMusicGetOn() )
			error = strmPlaySnd( pInfo->nSndID );
	}
	else
	if ( (pInfo->bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
	{
		error = FALSE;
		if ( audioSfxGetOn() )
			error = sfxPlaySnd( pInfo->nSndID );
	}

exit:

#ifdef TRACK
TRACE("Exit: sndPlay()...\n" );
#endif

	return( error );
 
}

///========================================================================
//	Function:		sndHalt()
//
//	Description:
//		Halt a Snd ID sound instance.
//
//	Input:			nSndID		nSndID to stop
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	sndHalt( ULONG nSndID )
{
	AUDIO_IDS*	pInfo;
	ULONG		oldID;
	ULONG		nextID;
	BOOL		result;
	BOOL		error = TRUE;		// assume an error

#ifdef TRACK
TRACE("Entered: sndHalt( %ld )...\n", nSndID );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// is this a valid snd ID
	if ( nSndID == SND_NULL_SND_ID )
	{
		// no error, simply ignore
		error = FALSE;
		goto exit;
	}

#ifdef AUDIO_DBG
TRACE("sndHalt(%s:%ld)\n",audioSndIDname( nSndID ), nSndID );
#endif

	// start by getting the flags for this snd
	pInfo = audioGetSndBySndID( nSndID  );
	if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
	{
		// no error
		error = FALSE;
		goto exit;
	}

	// determine the type of sound this is.
	if ( (pInfo->bFlags & SND_SFX_FLAG) != SND_SFX_FLAG )
	{
		error  = FALSE;
		result = FALSE;
		nextID = pInfo->nAudioID;
		while( !result && (nextID != SND_NULL_SND_ID) )
		{
			oldID  = nextID;
			if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
				result = voiceStopSnd( pInfo->nSndID );
			else
				result = strmStopSnd( pInfo->nSndID );
			if (!result)
			{
				if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
					nextID = voiceNextLink( nextID );
				else
					nextID = strmNextLink( nextID );

				if ( (pInfo->bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG )
				{
					if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
						voiceDeleteStream( pInfo->nSndID );
					else
						strmDeleteStream( pInfo->nSndID );
				}

				pInfo = audioGetSndByAudioID( nextID  );
				if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
				{
					// no error
					error = FALSE;
					goto exit;
				}
			}
			else
				error = TRUE;
		}
	}
	else
	{
		error = sfxStopSnd( pInfo->nSndID );
		if ( pInfo->bFlags & SND_DELETE_FLAG )
		{
			sfxDeleteSnd( pInfo->nSndID );

			// now delete the snd
			audioDeleteSnd( pInfo->nSndID );
		}
	}
	if ( error )
		goto exit;

	// got here so we must be ok
	error = FALSE;

exit:

#ifdef TRACK
TRACE("Exit: sndHalt()...\n" );
#endif

	return( error );
 
}

///========================================================================
//	Function:		audioStop()
//
//	Description:
//		Stop an audio sound instance.
//
//	Input:			nSndID		name of file to be opened
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	audioStop( ULONG nAudioID )
{
	BOOL		result;
	AUDIO_IDS*	pInfo;
	ULONG		oldID        = SND_NULL_SND_ID;
	ULONG		nNextAudioID = SND_NULL_SND_ID;
	BOOL		error        = TRUE;		// assume an error

#ifdef TRACK
TRACE("Entered: audioStop( %ld )...\n", nAudioID );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// is this a valid audio ID
	if ( nAudioID == SND_NULL_SND_ID )
	{
		// no error, simply ignore
		error = FALSE;
		goto exit;
	}

#ifdef AUDIO_DBG
	TRACE("audioStop( %s:%ld )...\n", audioIDname(nAudioID), nAudioID );
#endif

	// start by getting the flags for this snd
	pInfo = audioGetSndByAudioID( nAudioID  );
	if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
	{
		// no error
		error = FALSE;
		goto exit;
	}

	// determine the type of sound this is.
	if ( (pInfo->bFlags & SND_SFX_FLAG) != SND_SFX_FLAG )
	{
		result = FALSE;
		nNextAudioID = pInfo->nAudioID;
		while( !result && (nNextAudioID != SND_NULL_SND_ID) )
		{
			oldID  = nNextAudioID;
			if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
				result = voiceStopSnd( pInfo->nSndID );
			else
				result = strmStopSnd( pInfo->nSndID );
			if (!result)
			{
				if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
					nNextAudioID = voiceNextLink( nNextAudioID );
				else
					nNextAudioID = strmNextLink( nNextAudioID );

				if ( (pInfo->bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG )
				{
					if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
						voiceDeleteStream( pInfo->nSndID );
					else
						strmDeleteStream( pInfo->nSndID );
				}
#ifdef SND_DEBUG
				TRACE( "nNextAudioID = %x\n", nNextAudioID );
#endif

				if ( nNextAudioID != SND_NULL_SND_ID )
				{
					pInfo = audioGetSndByAudioID( nNextAudioID  );
					if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
					{
						// no error
						error = FALSE;
						goto exit;
					}
				}
			}
			else
				error = TRUE;
		}
	}
	if ( error )
		goto exit;

	// got here so we must be ok
	error = FALSE;

exit:

#ifdef TRACK
TRACE("Exit: audioStop()...\n" );
#endif

	return( error );
 
}

///========================================================================
//	Function:		audioReset()
//
//	Description:
//		reset an audio sound instance.
//
//	Input:			nSndID		sound ID to be reset
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	audioReset( ULONG nSndID )
{
	AUDIO_IDS*	pInfo;
	ULONG		nextID;
	BOOL		result;
	BOOL		error = TRUE;		// assume an error

#ifdef TRACK
TRACE("Entered: audioReset( %ld )...\n", nSndID );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// is this a valid snd ID
	if ( nSndID == SND_NULL_SND_ID )
	{
		// no error, simply ignore
		error = FALSE;
		goto exit;
	}

	// start by getting the flags for this snd
	pInfo = audioGetSndBySndID( nSndID  );
	if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: failed to locate SND (%ld). [%s:%d]\n", 
			  nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// determine the type of sound this is.
	if ( (pInfo->bFlags & SND_SFX_FLAG) != SND_SFX_FLAG )
	{
		result = FALSE;
		nextID = pInfo->nAudioID;
		while( !result && (nextID != SND_NULL_SND_ID) )
		{
			if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
				result = voiceReset( pInfo->nSndID );
			else
				result = strmReset( pInfo->nSndID );
			if (!result)
			{
				if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
					nextID = voiceNextLink( nextID );
				else
					nextID = strmNextLink( nextID );

				pInfo = audioGetSndByAudioID( nextID  );
				if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
				{
					// no error
					error = FALSE;
					goto exit;
				}
			}
			else
				error = TRUE;
		}
	}
	else
		error = sfxReset( pInfo->nAudioID );

	if ( error )
		goto exit;

	// got here so we must be ok
	error = FALSE;

exit:

#ifdef TRACK
TRACE("Exit: audioStop()...\n" );
#endif

	return( error );
 
}


///========================================================================
//	Function:		audioDelete()
//
//	Description:
//		Stop an audio sound instance.
//
//	Input:			nAudioID	audio ID to be deleted
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	audioDelete( ULONG nAudioID )
{
	AUDIO_IDS*	pInfo;
	BOOL		error = TRUE;		// assume an error

#ifdef AUDIO_DBG
	TRACE("audioDelete( %s:%ld )...\n", audioIDname(nAudioID), nAudioID );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// is this a valid audio ID
	if ( nAudioID == SND_NULL_SND_ID )
	{
		// no error, simply ignore
		error = FALSE;
		goto exit;
	}

	// start by getting the flags for this snd
	pInfo = audioGetSndByAudioID( nAudioID );
	if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
	{
		error = FALSE;
		goto exit;
	}

	// determine the type of sound this is.
	if ( (pInfo->bFlags & SND_SFX_FLAG) != SND_SFX_FLAG )
	{
		if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
			error = voiceDeleteSnd( pInfo->nSndID );
		else
		if ( (pInfo->bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
			error = strmDeleteSnd( pInfo->nSndID );
	}
	else
		error = sfxDeleteSnd( pInfo->nSndID );
	if ( error )
		goto exit;

	// now delete the snd
	audioDeleteSnd( pInfo->nSndID );

	// got here so we must be ok
	error = FALSE;

exit:

#ifdef TRACK
TRACE("Exit: audioDelete()...\n" );
#endif
	return( error );
 
}

///========================================================================
//	Function:		audioGetFrequency()
//
//	Description:
// 		Get the Global Frequency levels (effect pitch)
//			specifies at which rate the buffer is played
//
//			range: 10,000 <= nFrequency <= 100,000 : 100Hz to 100kHz
//
//			normal rates are 11kHz, 22kHz, 44kHz
//
//	Input:			none
//
//	Ouput:			AUDIOfrequency	current base frequency setting
//
///========================================================================

LONG		audioGetFrequency( void )
{

#ifdef TRACK
TRACE("Entered: audioGetFrequency()...\n" );
#endif
 

#ifdef TRACK
TRACE("Exiting: audioGetFrequency()...\n" );
#endif
 
	return( AUDIOfrequency );
}

///========================================================================
//	Function:		audioSetFrequency()
//
//	Description:
// 		Set the Global Frequency levels (effect pitch)
//			specifies at which rate the buffer is played
//
//			range: 10,000 <= nFrequency <= 100,000 : 100Hz to 100kHz
//
//			normal rates are 11kHz, 22kHz, 44kHz
//
//	Input:			nFrequency	new base frequency setting
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		audioSetFrequency( LONG nFrequency )
{
#ifdef TRACK
TRACE("Entered: audioSetFrequency()...\n" );
#endif
 

#ifdef TRACK
TRACE("Exiting: audioSetFrequency()...\n" );
#endif
 
	AUDIOfrequency = nFrequency;
	return( FALSE );
}

///========================================================================
//	Function:		audioGetVolume()
//
//	Description:
// 		Get the Global Volume levels:
//			Specifies the volume level of the buffer.
//			The initial volume of a buffer is always 0. Any modification in volume
//			levels reflected by values other than 0. Positive values increase volume
//			and negative values decrease volume
//
//			range:  -10,000 <= volumne <= 10,000 : -100db (silent) to 100db
//
//	Input:			none
//
//	Ouput:			AUDIOvolume		current base volume setting
//
///========================================================================

LONG		audioGetVolume( ULONG nSndID )
{
	AUDIO_IDS*	pInfo;
	LONG		nVolume = 0L;

#ifdef TRACK
TRACE("Entered: audioGetVolume()...\n" );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	if ( nSndID != AUDIO_NULL_ID )
	{
		// retrieve a particular sounds volume

		// start by getting the flags for this snd
		pInfo = audioGetSndBySndID( nSndID  );
		if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
		{
			// report an error
			TRACE("ERROR: failed to locate SND (%ld). [%s:%d]\n", 
				  nSndID, __FILE__, __LINE__ );
			goto exit;
		}

		// determine the type of sound this is.
		if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
			nVolume = voiceGetVolume( nSndID );
		else
		if ( (pInfo->bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
			nVolume = strmGetVolume( nSndID );
		else
		if ( (pInfo->bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
			nVolume = sfxGetVolume( nSndID );
	}
	else
	{
		// get the global volume
		nVolume = AUDIOvolume;
	}

exit:

#ifdef TRACK
	TRACE("Exiting: audioGetVolume()...\n" );
#endif
 
	return( nVolume );
}
 
///========================================================================
//	Function:		audioSetVolume()
//
//	Description:
// 		Set the Global Volume levels:
//			Specifies the volume level of the buffer.
//			The initial volume of a buffer is always 0. Any modification in volume
//			levels reflected by values other than 0. Positive values increase volume
//			and negative values decrease volume
//
//			range:  -10,000 <= volume <= 10,000 : -100db (silent) to 100db
//
//	Input:			nSndID		Snd to modify
//					nVolume		new volume setting
//					bMax		if TRUE set as new Base volume
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		audioSetVolume( ULONG nSndID, LONG nVolume, BOOL bMax )
{
	AUDIO_IDS*	pInfo;
	BOOL		error = TRUE;		// assume failure

#ifdef TRACK
TRACE("Entered: audioSetVolume()...\n" );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	if ( nSndID != AUDIO_NULL_ID )
	{
		// adjust a particular sounds volume

		// start by getting the flags for this snd
		pInfo = audioGetSndBySndID( nSndID  );
		if ( pInfo == (AUDIO_IDS*)SND_NULL_SND_PTR )
		{
			// report an error
			TRACE("ERROR: failed to locate SND (%ld). [%s:%d]\n", 
				  nSndID, __FILE__, __LINE__ );
			goto exit;
		}

		// reset the Max volume if necessary
		if ( bMax )
			pInfo->nVolume = nVolume;

		// determine the type of sound this is.
		if ( (pInfo->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
			error = voiceSetVolume( nSndID, nVolume );
		else
		if ( (pInfo->bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
			error = strmSetVolume( nSndID, nVolume );
		else
			error = sfxSetVolume( nSndID, nVolume );

		if ( error )
			goto exit;
	}
	else
	{
		// globally adjust the volume
		AUDIOvolume = nVolume;
	}

	// got here so we must be ok
	error = FALSE;

exit:

#ifdef TRACK
	TRACE("Exiting: audioSetVolume()...\n" );
#endif
 
	return( FALSE );
}

///========================================================================
//	Function:		audioGetPan()
//
//	Description:
// 		Get Global Pan levels
//			Specifies the volume level of the buffers left and right channels.
//			A value of 0 corresponds to both channels at full volume with no
//			panning effects. The sign of this value determines which channel
//			is being attenuated. Positive=Left channel, Negative = Right channel
//
//			range:  -10,000 <= pan <= 10,000 : -100db to 100db
//
//			if nPan= 10,000 the left channel is silent
//                =-10,000 the right channel is silent
//
//	Input:			none
//
//	Ouput:			AUDIOpan		new base pan setting
//
///========================================================================

LONG		audioGetPan( void )
{
#ifdef TRACK
TRACE("Entered: audioGetPan()...\n" );
#endif

#ifdef TRACK
TRACE("Exiting: audioGetPan()...\n" );
#endif

	return( AUDIOpan );
}

///========================================================================
//	Function:		audioSetPan()
//
//	Description:
// 		Set Global Pan levels
//			Specifies the volume level of the buffers left and right channels.
//			A value of 0 corresponds to both channels at full volume with no
//			panning effects. The sign of this value determines which channel
//			is being attenuated. Positive=Left channel, Negative = Right channel
//
//			range:  -10,000 <= pan <= 10,000 : -100db to 100db
//
//			if nPan= 10,000 the left channel is silent
//                =-10,000 the right channel is silent
//
//	Input:			nPan		new base pan setting
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		audioSetPan( LONG nPan )
{
#ifdef TRACK
TRACE("Entered: audioSetPan()...\n" );
#endif

	AUDIOpan = nPan;

#ifdef TRACK
TRACE("Exiting: audioSetPan()...\n" );
#endif

	return( FALSE );
}

///========================================================================
//	Function:		audioCreateLink()
//
//	Description:
//		Create a linked audio stream.
//
//	Input:			nFileID		id of file to get data
//					pLinks		a list of sound ids to link into a stream
//								this list is AUDIO_NULL_SOUND terminated.
//					bFlags		apply flags to snd buffers
//
//	Ouput:			nSndID		SndID of link reference
//
///========================================================================

ULONG	audioCreateLink( unsigned nFileID, ULONG* pLinks, USHORT bFlags )
{
	ULONG*		pLinkID;
	ULONG		nSndID = SND_NULL_SND_ID;
	ULONG		nPreviousID = SND_NULL_SND_ID;
	unsigned	nLinkCount;

#ifdef TRACK
TRACE("Entered: audioCreateLink( )...\n" );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// since the links look forward, we need to know the ID of the next
	// snd. This is simplified by starting from the end of the list.
	// we know the last snd has an id of SND_NULL_SND_ID and the snd we
	// create will provide the ID for the next snd (the previous) we process.
	pLinkID    = pLinks;
	nLinkCount = 0;
	while( *pLinkID != AUDIO_NULL_SOUND )
	{
		// advance to the next link
		++pLinkID;
		++nLinkCount;
	}

	// we dont want to process the link AUDIO_NULL_SOUND so back up one
	--pLinkID;

	// Now build the links in reverse order
	while( nLinkCount-- )
	{
		// create a snd
		nSndID = audioCreateSnd( nFileID, *pLinkID, 0, bFlags );
		if ( nSndID == SND_NULL_SND_ID )
		{
			// report an error
			TRACE("ERROR: failed to load sound. [%s:%d]\n", 
				__FILE__, __LINE__ );
			nSndID = SND_NULL_SND_ID;
			goto exit;
		}
		audioSetLink( nSndID, nPreviousID, bFlags );

		// update previous ID and pointers
		nPreviousID = nSndID;
		--pLinkID;
	}
 
exit:

#ifdef TRACK
TRACE("Exit: audioCreateLink()...\n" );
#endif

	return( nSndID );
 
}

///========================================================================
//	Function:		audioSetLink()
//
//	Description:
//		Stop an audio sound instance.
//
//	Input:			nStrmID		strm id to link
//					nPreviousID	snd id to be linked to
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	audioSetLink( ULONG nStrmID, ULONG nPreviousID, USHORT bFlags )
{
	BOOL		error = TRUE;		// assume an error

#ifdef TRACK
TRACE("Entered: audioSetLink( %ld )...\n", nStrmID );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// tell the strm processing to link these
	if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
		error = voiceSetLink( nStrmID, nPreviousID );
	else
		error = strmSetLink( nStrmID, nPreviousID );

	if ( error )
		goto exit;

	// got here so we must be ok
	error = FALSE;

exit:

#ifdef TRACK
TRACE("Exit: audioSetLink()...\n" );
#endif

	return( error );
 
}

///========================================================================
//	Function:		audioSetMasterVolume()
//
//	Description:
//		Stop an audio sound instance.
//
//	Input:			bFlag		SFX,VOICE,MUSIC flag
//					nVolume		Set the master volume
//
//	Ouput:			none
//
///========================================================================

void	audioSetMasterVolume( USHORT bFlag, LONG nVolume )
{
	switch(	bFlag )
	{
	case SND_SFX_FLAG:
		sfxSetMasterVolume( nVolume );
		break;
	case SND_VOICE_FLAG:
		voiceSetMasterVoiceVolume( nVolume );
		break;
	case SND_MUSIC_FLAG:
		strmSetMasterMusicVolume( nVolume );
		break;
	}
}

///========================================================================
//	Function:		audioGetMasterVolume()
//
//	Description:
//		Stop an audio sound instance.
//
//	Input:			bFlag		SFX,VOICE,MUSIC flag
//					nVolume		Set the master volume
//
//	Ouput:			nVolume		the particular volume
//
///========================================================================

LONG	audioGetMasterVolume( USHORT bFlag )
{
	LONG	nVolume = 0;

	switch(	bFlag )
	{
	case SND_SFX_FLAG:
		nVolume = sfxGetMasterVolume();
		break;
	case SND_VOICE_FLAG:
		nVolume = voiceGetMasterVoiceVolume();
		break;
	case SND_MUSIC_FLAG:
		nVolume = strmGetMasterMusicVolume();
		break;
	}
	return( nVolume );
}

///========================================================================
//	Function:		audioMonitor()
//
//	Description:
//		monitor and process audio timer messages.
//
//	Input:			uTimerID		timer Id triggering this processing
//
//	Ouput:			TRUE			if timer belonged to audio,
//
///========================================================================

BOOL	audioMonitor ( UINT uTimerID )
{
	BOOL	answer = FALSE;		// assume not ours

#ifdef TRACK
TRACE("Entered: audioMonitor()...\n" );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// first check to see if this timer ID is a music stream
	if ( strmTimerCheck( uTimerID ) )
	{
		strmMonitor( uTimerID, NULL, 0, 0, 0 );
		answer = TRUE;
	}
	else	// next check to see if this timer ID is a voice stream
	if ( voiceTimerCheck( uTimerID ) )
	{
		voiceMonitor( uTimerID, NULL, 0, 0, 0 );
		answer = TRUE;
	}

exit:

#ifdef TRACK
TRACE("Exiting: audioMonitor()...\n" );
#endif

	return( answer );
}

///========================================================================
//	Function:		audioStopAll()
//
//	Description:
//		stop all audio.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	audioStopAll( void )
{
	unsigned	snd;
	int			error;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

#ifdef DBG_AUDIO
	TRACE("\n\naudioStopAll( AUDIOdSoundEnabled:%d )\n", AUDIOdSoundEnabled );
	TRACE("    Game State     = %s\n", GetStateName( gpGame->GetState() ) );
	TRACE("    Game Sub State = %s\n", GetSubStateName( gpGame->GetSubState() ) );
	TRACE("    Scrn State     = %s\n", ScrnGetStateName( ScrnGetState() ) );
#endif

	// now try the sound tables
	for ( snd=0;snd<AUDIOsoundIndex; ++snd )
	{
		// determine the type of sound this is.
		if ( AUDIOsounds[ snd ].nSndID != SND_NULL_SND_ID )
		{
			if ( (AUDIOsounds[ snd ].bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
			{
				voiceStopSnd(AUDIOsounds[ snd ].nSndID);
				voiceDeleteStream( AUDIOsounds[ snd ].nSndID );
			}
			else
			if ( (AUDIOsounds[ snd ].bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
			{
				strmStopSnd(AUDIOsounds[ snd ].nSndID);
				strmDeleteStream( AUDIOsounds[ snd ].nSndID );
			}
			else
			if ( (AUDIOsounds[ snd ].bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
			{
				sfxStopSnd(AUDIOsounds[ snd ].nSndID);
				error = sfxDeleteSnd( AUDIOsounds[ snd ].nSndID );

				// now delete the snd
				audioDeleteSnd( AUDIOsounds[ snd ].nSndID );
			}
		}
	}

//	gameNoisy();
}

///========================================================================
//	Function:		audioVoiceOff()
//
//	Description:
//		turn OFF all Music.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	audioVoiceOff( void )
{
	unsigned	snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	AUDIOvoiceOn = FALSE;
	voiceSetOn( AUDIOvoiceOn );

	for ( snd=0;snd<AUDIOsoundIndex; ++snd )
	{
		if ( AUDIOsounds[ snd ].nSndID != SND_NULL_SND_ID )
		{
			if ((AUDIOsounds[ snd ].bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
				SndSetVolumePercent( AUDIOsounds[ snd ].nSndID, 0, FALSE );
		}
	}
}

///========================================================================
//	Function:		audioVoiceOn()
//
//	Description:
//		turn ON all Music.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	audioVoiceOn( void )
{
	unsigned	snd;
	LONG		nMasterVolume;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	AUDIOvoiceOn = TRUE;
	voiceSetOn( AUDIOvoiceOn );

	for ( snd=0;snd<AUDIOsoundIndex; ++snd )
	{
		if ( AUDIOsounds[ snd ].nSndID != SND_NULL_SND_ID )
		{
			if ((AUDIOsounds[ snd ].bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
			{
				// apply the master volume
				nMasterVolume = audioGetMasterVolume( SND_VOICE_FLAG );
				SndSetVolumePercent( AUDIOsounds[ snd ].nSndID, nMasterVolume, FALSE );
			}
		}
	}
}

///========================================================================
//	Function:		audioVoiceGetOn()
//
//	Description:
//		retrieve MUSIC ON state.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

BOOL	audioVoiceGetOn( void )
{
	return( AUDIOvoiceOn );
}

///========================================================================
//	Function:		audioMusicOff()
//
//	Description:
//		turn OFF all Music.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	audioMusicOff( void )
{
	unsigned	snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	AUDIOmusicOn = FALSE;
	strmSetOn( AUDIOmusicOn );

	for ( snd=0;snd<AUDIOsoundIndex; ++snd )
	{
		if ( AUDIOsounds[ snd ].nSndID != SND_NULL_SND_ID )
		{
			if ((AUDIOsounds[ snd ].bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
				SndSetVolumePercent( AUDIOsounds[ snd ].nSndID, 0, FALSE );
		}
	}
}

///========================================================================
//	Function:		audioMusicOn()
//
//	Description:
//		turn ON all Music.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	audioMusicOn( void )
{
	LONG		nMasterVolume;
	unsigned	snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	AUDIOmusicOn = TRUE;
	strmSetOn( AUDIOmusicOn );

	for ( snd=0;snd<AUDIOsoundIndex; ++snd )
	{
		if ( AUDIOsounds[ snd ].nSndID != SND_NULL_SND_ID )
		{
			if ((AUDIOsounds[ snd ].bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
			{
				// apply the master volume
				nMasterVolume = audioGetMasterVolume( SND_MUSIC_FLAG );
				SndSetVolumePercent( AUDIOsounds[ snd ].nSndID, nMasterVolume, FALSE );
			}
		}
	}
}

///========================================================================
//	Function:		audioMusicGetOn()
//
//	Description:
//		retrieve MUSIC ON state.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

BOOL	audioMusicGetOn( void )
{
	return( strmGetOn() );
}

///========================================================================
//	Function:		audioSfxOff()
//
//	Description:
//		turn OFF all SFX.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	audioSfxOff( void )
{
	unsigned	snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	AUDIOsfxOn = FALSE;
	sfxSetOn( AUDIOsfxOn );

	for ( snd=0;snd<AUDIOsoundIndex; ++snd )
	{
		if ( AUDIOsounds[ snd ].nSndID != SND_NULL_SND_ID )
		{
			if ((AUDIOsounds[ snd ].bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
				SndSetVolumePercent(  AUDIOsounds[ snd ].nSndID, 0, FALSE );
		}
	}
}

///========================================================================
//	Function:		audioSfxOn()
//
//	Description:
//		turn ON all SFX.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	audioSfxOn( void )
{
	LONG	nMasterVolume;
	int		snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	AUDIOsfxOn = TRUE;
	sfxSetOn( AUDIOsfxOn );

	for ( snd=0;snd < (int)AUDIOsoundIndex; ++snd )
	{
		if ( AUDIOsounds[ snd ].nSndID != SND_NULL_SND_ID )
		{
			if ((AUDIOsounds[ snd ].bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
			{
				// apply the master volume
				nMasterVolume = audioGetMasterVolume( SND_SFX_FLAG );
				SndSetVolumePercent( AUDIOsounds[ snd ].nSndID, nMasterVolume, FALSE );
			}
		}
	}
}

///========================================================================
//	Function:		audioSfxGetOn()
//
//	Description:
//		retrieve SFX ON state.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

BOOL	audioSfxGetOn( void )
{
	return( sfxGetOn() );
}

///========================================================================
//	Function:		audioStoreFile()
//
//	Description:
//		Save off the audio file access information.
//
//	Input:			nFileID		ID of file to close
//
//	Ouput:			none
//
///========================================================================

void	audioStoreFile( unsigned nFileID )
{
	unsigned	id = (unsigned)AUDIO_ERR;

#ifdef TRACK
TRACE("Entered: audioStoreFile()...\n" );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// make sure the data we have is valid
	if ( nFileID == SND_NULL_SND_ID )
	{
		// report an error
		TRACE("ERROR: failed to load sound. [%s:%d]\n", 
			__FILE__, __LINE__ );
		goto exit;
	}

	// locate an empty slot to save this info to
	id = 0;
	while ( (id<AUDIO_MAX_FILES) && (AUDIOfiles[id] != SND_NULL_SND_ID) )
		++id;

	// did we find an empty slot
	if ( id >= AUDIO_MAX_FILES ) 
	{
		// report an error
		TRACE("ERROR: failed to load sound. [%s:%d]\n", 
			__FILE__, __LINE__ );
		goto exit;
	}

	// copy in the file ID
	AUDIOfiles[id] = nFileID;

exit:

#ifdef TRACK
TRACE("Exit: audioStoreFile()...\n" );
#endif

	return;
}

///========================================================================
//	Function:		audioDeleteFile()
//
//	Description:
//		Delete the audio file access information.
//
//	Input:			nFileID		ID of file to close
//
//	Ouput:			none
//
///========================================================================

void	audioDeleteFile( unsigned nFileID )
{
	unsigned	id;

#ifdef TRACK
TRACE("Entered: audioDeleteFile()...\n" );
#endif

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	// make sure the data we have is valid
	if ( nFileID == SND_NULL_SND_ID )
	{
		// report an error
		TRACE("ERROR: failed to load sound. [%s:%d]\n", 
			__FILE__, __LINE__ );
		goto exit;
	}

	// locate the slot to delete
	id = 0;
	while ( (id<AUDIO_MAX_FILES) && (AUDIOfiles[id] != nFileID) )
		++id;

	// did we find the slot
	if ( id >= AUDIO_MAX_FILES ) 
	{
		// report an error
		TRACE("ERROR: failed to load sound. [%s:%d]\n", 
			__FILE__, __LINE__ );
		goto exit;
	}

	// delete the snd file info
	sndDeleteFile( AUDIOfiles[id] );

	// clear the file ID
	AUDIOfiles[id] = SND_NULL_SND_ID;

exit:

#ifdef TRACK
TRACE("Exit: audioDeleteFile()...\n" );
#endif

	return;
}

///========================================================================
//	Function:		audioStoreSnd()
//
//	Description:
// 		terminate audio test driver
//
//	Input:			nAudioID		original Audio ID for sound
//					nSndID			SND id applied to sound
//					bFlags			identification flags
//
//	Ouput:			none
//
///========================================================================

void	audioStoreSnd( ULONG nAudioID, ULONG nSndID, USHORT bFlags )
{
	LONG	nVolume;
	LONG	nMasterVolume;
	USHORT	nSndType;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	if ( nAudioID == SND_NULL_SND_ID )
		return;

	if ( nSndID == SND_NULL_SND_ID )
		return;

	if( AUDIOsoundIndex >= AUDIO_MAX_SOUNDS )
	{
		// report an error
		TRACE("ERROR: failed to add AUDIO sound. [%s:%d]\n", __FILE__, __LINE__ );
		return;
	}

#if 0
	TRACE( "audioStoreSnd( %s a:%ld s:%ld f:",
		audioIDname( nAudioID ), nAudioID, nSndID );
	if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
		TRACE( "VOICE " );
	if ( (bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
		TRACE( "MUSIC " );
	if ( (bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
		TRACE( "SFX " );
	if ( (bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG )
		TRACE( "LOOP " );
	if ( (bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG )
		TRACE( "DELETE " );
	TRACE( ")\n" );
#endif
	AUDIOsounds[ AUDIOsoundIndex ].nAudioID = nAudioID;
	AUDIOsounds[ AUDIOsoundIndex ].nSndID   = nSndID;
	AUDIOsounds[ AUDIOsoundIndex ].bFlags   = bFlags;

	// determine the type of sound this is.
	if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
		nVolume = voiceGetVolume( nSndID );
	else
	if ( (bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
		nVolume = strmGetVolume( nSndID );
	else
		nVolume = sfxGetVolume( nSndID );
	AUDIOsounds[ AUDIOsoundIndex ].nVolume  = nVolume;

	// apply the master volume
	if ( (bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
		nSndType = SND_SFX_FLAG;
	else
	if ( (bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
		nSndType = SND_MUSIC_FLAG;
	else
	if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
		nSndType = SND_VOICE_FLAG;
	else
		ASSERT(0);

	switch( nSndType )
	{
	case SND_SFX_FLAG:
		sfxSetVolume( nSndID, nVolume );
		break;
	case SND_MUSIC_FLAG:
		strmSetVolume( nSndID, nVolume );
		break;
	case SND_VOICE_FLAG:
		voiceSetVolume( nSndID, nVolume );
		break;
	}

	nMasterVolume = audioGetMasterVolume( nSndType );

	if ( nMasterVolume )
	{
		nVolume      *= nMasterVolume;
		nVolume      /= 100;
	}
	else
		nVolume = 0;

	// update sound index
	++AUDIOsoundIndex;
	if ( AUDIOmaxSoundIndex < AUDIOsoundIndex )
		AUDIOmaxSoundIndex = AUDIOsoundIndex;
}

///========================================================================
//	Function:		audioGetSndBySndID()
//
//	Description:
// 		retrieve a SND from the lookuptable using the SND ID as key.
//
//	Input:			nSndID		SND id to search for
//
//	Ouput:			pAudioPtr	address of audio id information
//
///========================================================================

AUDIO_IDS*	audioGetSndBySndID( ULONG nSndID  )
{
	AUDIO_IDS*	pAudioPtr = (AUDIO_IDS*)SND_NULL_SND_PTR;
	unsigned	snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	if ( nSndID == SND_NULL_SND_ID )
		goto exit;

	snd = 0;
	while( (AUDIOsounds[ snd ].nSndID != nSndID) && (snd<AUDIOsoundIndex) )
		++snd;

	if( snd < AUDIOsoundIndex )	// we've found the audio entry
		pAudioPtr = &(AUDIOsounds[ snd ]);
	else
	{
		// check to see if in one of the dynamic lists
		pAudioPtr = (AUDIO_IDS*)voiceFindSndID( nSndID );
		if ( pAudioPtr == (AUDIO_IDS*)SND_NULL_SND_PTR )
			pAudioPtr = (AUDIO_IDS*)strmFindSndID( nSndID );
		if ( pAudioPtr == (AUDIO_IDS*)SND_NULL_SND_PTR )
			pAudioPtr = (AUDIO_IDS*)sfxFindSndID( nSndID );
	}

exit:
	return( pAudioPtr );
}

///========================================================================
//	Function:		audioGetSndByAudioID()
//
//	Description:
// 		retrieve a SND from the lookuptable using the AUDIO ID as key.
//
//	Input:			nAudioID	Original sound id to search for
//
//	Ouput:			pAudioPtr	address of audio id information
//
///========================================================================

AUDIO_IDS*	audioGetSndByAudioID( ULONG nAudioID  )
{
	AUDIO_IDS*	pAudioPtr = (AUDIO_IDS*)SND_NULL_SND_PTR;
	unsigned	snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	if ( nAudioID == SND_NULL_SND_ID )
		goto exit;

	snd = 0;
	while( (snd<AUDIOsoundIndex) && (AUDIOsounds[ snd ].nAudioID != nAudioID)  )
		++snd;

	if( snd < AUDIOsoundIndex )	// we've found the audio entry
		pAudioPtr = &(AUDIOsounds[ snd ]);
	else
	{
		// check to see if in one of the dynamic lists
		if ( nAudioID >= VOICE_AUDIO_START )
			pAudioPtr = (AUDIO_IDS*)voiceFindID( nAudioID );
		else
		if ( nAudioID >= MUSIC_AUDIO_START )
			pAudioPtr = (AUDIO_IDS*)strmFindID( nAudioID );
		else
		if ( nAudioID >= SFX_AUDIO_START )
			pAudioPtr = (AUDIO_IDS*)sfxFindID( nAudioID );
	}

exit:
	return( pAudioPtr );
}

///========================================================================
//	Function:		audioDeleteSnd()
//
//	Description:
// 		delete an audio SND from the lookup table.
//
//	Input:			nSndID		SND id to search for
//
//	Ouput:			pAudioPtr	address of audio id information
//
///========================================================================

BOOL	audioDeleteSnd( ULONG nSndID  )
{
	unsigned	snd;
	unsigned	bFlags;
	BOOL		error = TRUE;			// assume an error

	// is this a real sound
	if ( nSndID == SND_NULL_SND_ID )
		goto cleanUp;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto cleanUp;

	snd = 0;
	while( (AUDIOsounds[ snd ].nSndID != nSndID) && (snd<AUDIOsoundIndex) )
		++snd;

	if( (AUDIOsounds[ snd ].nSndID == SND_NULL_SND_ID) || (snd>=AUDIOsoundIndex) )
		goto exit;

	// save the flags field
	bFlags = AUDIOsounds[ snd ].bFlags;

	// we've found the audio entry
	AUDIOsounds[ snd ].nAudioID = SND_NULL_SND_ID;
	AUDIOsounds[ snd ].nSndID   = SND_NULL_SND_ID;
	AUDIOsounds[ snd ].bFlags   = SND_CLEAR_FLAG;
	AUDIOsounds[ snd ].nVolume  = 0;

	// now delete it from the SND system
//	sndDelete( nSndID );

cleanUp:
	error = FALSE;

exit:
	return( error );
}

///========================================================================
//	Function:		audioDeleteSfx()
//
//	Description:
// 		delete an audio SND from the lookup table.
//
//	Input:			nSndID		SND id to search for
//
//	Ouput:			pAudioPtr	address of audio id information
//
///========================================================================

BOOL	audioDeleteSfx( ULONG nSndID, ULONG nSfxID  )
{
	unsigned	snd;
	unsigned	bFlags;
	BOOL		error = TRUE;			// assume an error

	// is this a real sound
	if ( nSndID == SND_NULL_SND_ID )
		goto cleanUp;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto cleanUp;

	snd = 0;
	while( (AUDIOsounds[ snd ].nSndID != nSndID) && (snd<AUDIOsoundIndex) )
		++snd;

	if( (AUDIOsounds[ snd ].nSndID == SND_NULL_SND_ID) || (snd>=AUDIOsoundIndex) )
		goto exit;

	// save the flags field
	bFlags = AUDIOsounds[ snd ].bFlags;

	// we've found the audio entry
	AUDIOsounds[ snd ].nAudioID = SND_NULL_SND_ID;
	AUDIOsounds[ snd ].nSndID   = SND_NULL_SND_ID;
	AUDIOsounds[ snd ].bFlags   = SND_CLEAR_FLAG;
	AUDIOsounds[ snd ].nVolume  = 0;

	// now delete it from the SND system
	sndDelete( nSfxID );

cleanUp:
	error = FALSE;

exit:
	return( error );
}

///========================================================================
//	Function:		audioChangeVolume()
//
//	Description:
// 		adjust volume on audio stream
//
//	Input:			none
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	audioChangeVolume( ULONG nSndID, SHORT delta )
{
	AUDIO_IDS*	pAudioPtr;
	LONG	    nVolume;
	LONG	    nNewVolume;
	BOOL		error = TRUE;		// assume failure

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		goto exit;

	if ( nSndID == SND_NULL_SND_ID )
		goto exit;

	// get the current volume
	pAudioPtr = audioGetSndBySndID( nSndID );
	if ( (pAudioPtr->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
		nVolume   = voiceGetVolume( pAudioPtr->nSndID );
	else
	if ( (pAudioPtr->bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
		nVolume   = strmGetVolume( pAudioPtr->nSndID );
	else
	if ( (pAudioPtr->bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
		nVolume   = sfxGetVolume( pAudioPtr->nSndID );

	nNewVolume = nVolume + delta;

	if ( nNewVolume > AUDIO_MAX_VOLUME )
		nNewVolume = AUDIO_MAX_VOLUME;

	if ( nNewVolume < AUDIO_MIN_VOLUME )
		nNewVolume = AUDIO_MIN_VOLUME;

	if ( (pAudioPtr->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
	{
		if ( voiceSetVolume( nSndID, nNewVolume ) )
			goto exit;
	}
	else
	if ( (pAudioPtr->bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
	{
		if ( strmSetVolume( nSndID, nNewVolume ) )
			goto exit;
	}
	else
	if ( (pAudioPtr->bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
	{
		if ( sfxSetVolume( nSndID, nNewVolume ) )
			goto exit;
	}

	// made it here, must be successful
	error = FALSE;
exit:
	return error;
}


///========================================================================
//	Function:		audioFindIDbyName()
//
//	Description:
// 		return the audio ID associated with the audio name string
//
//	Input:			pAudioName	audio name whose ID we want
//
//	Ouput:			nAudioID	if Successful, SND_NULL_SND_ID otherwise
//
///========================================================================

ULONG audioFindIDbyName( char* pAudioName )
{
	ULONG		nAudioID = SND_NULL_SND_ID;
	ULONG		nID;
	BOOL		bFound;

	// first check the SFX table and then the STREAM table
	nID    = 0;
	bFound = FALSE;
	while ( !bFound && (SND_sounds_Names[ nID ].nAudioID != SND_NULL_SND_ID) )
	{
		if ( strcmp( SND_sounds_Names[ nID ].SndName, pAudioName) == 0 )
		{
			nAudioID = SND_sounds_Names[ nID ].nAudioID;
			bFound   = TRUE;
		}
		else
			++nID;
	}
	if ( !bFound )
	{
		nID    = 0;
		bFound = FALSE;
		while ( !bFound && (SND_streams_Names[ nID ].nAudioID != SND_NULL_SND_ID) )
		{
			if ( strcmp( SND_streams_Names[ nID ].SndName, pAudioName) == 0 )
			{
				nAudioID = SND_streams_Names[ nID ].nAudioID;
				bFound   = TRUE;
			}
			else
				++nID;
		}
	}
	if ( !bFound )
	{
		nID    = 0;
		bFound = FALSE;
		while ( !bFound && (SND_voices_Names[ nID ].nAudioID != SND_NULL_SND_ID) )
		{
			if ( strcmp( SND_voices_Names[ nID ].SndName, pAudioName) == 0 )
			{
				nAudioID = SND_voices_Names[ nID ].nAudioID;
				bFound   = TRUE;
			}
			else
				++nID;
		}
	}
	return( nAudioID );
}

///========================================================================
//	Function:		audioIDname()
//
//	Description:
// 		return the string name associated with nAudioID
//
//	Input:			nAudioID	audio ID whose string name we want
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

char* audioIDname(ULONG nAudioID)
{
	char*		pAudioName = NULL;
#ifndef AUDIO_OFF
	ULONG		nID;
	BOOL		bFound;

	// first check the SFX table and then the STREAM table
	nID    = 0;
	bFound = FALSE;
	while ( !bFound && (SND_sounds_Names[ nID ].nAudioID != SND_NULL_SND_ID) )
	{
		if ( SND_sounds_Names[ nID ].nAudioID == nAudioID )
		{
			pAudioName = SND_sounds_Names[ nID ].SndName;
			bFound     = TRUE;
		}
		else
			++nID;
	}
	if ( !bFound )
	{
		nID    = 0;
		bFound = FALSE;
		while ( !bFound && (SND_streams_Names[ nID ].nAudioID != SND_NULL_SND_ID) )
		{
			if ( SND_streams_Names[ nID ].nAudioID == nAudioID )
			{
				pAudioName = SND_streams_Names[ nID ].SndName;
				bFound     = TRUE;
			}
			else
				++nID;
		}
	}
	if ( !bFound )
	{
		nID    = 0;
		bFound = FALSE;
		while ( !bFound && (SND_voices_Names[ nID ].nAudioID != SND_NULL_SND_ID) )
		{
			if ( SND_voices_Names[ nID ].nAudioID == nAudioID )
			{
				pAudioName = SND_voices_Names[ nID ].SndName;
				bFound     = TRUE;
			}
			else
				++nID;
		}
	}
#endif

	return( pAudioName );
}

///========================================================================
//	Function:		audioSndIDname()
//
//	Description:
// 		return the string name associated with nAudioID
//
//	Input:			nSndID		snd ID whose string name we want
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

char* audioSndIDname(ULONG nSndID)
{
	char*		pAudioName = NULL;
#ifndef AUDIO_OFF
	int			nSndIdx;
	unsigned	status;
	SND*		pSndPtr;
	ULONG		nID;
	ULONG		nAudioID;
	BOOL		bFound;

	// first locate the audioID for this Snd ID
	status = sndFindSndID( nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
		goto exit;

	nAudioID = pSndPtr->nAudioID;

	// first check the SFX table and then the STREAM table
	nID    = 0;
	bFound = FALSE;
	while ( !bFound && (SND_sounds_Names[ nID ].nAudioID != SND_NULL_SND_ID) )
	{
		if ( SND_sounds_Names[ nID ].nAudioID == nAudioID )
		{
			pAudioName = SND_sounds_Names[ nID ].SndName;
			bFound     = TRUE;
		}
		else
			++nID;
	}
	if ( !bFound )
	{
		nID    = 0;
		bFound = FALSE;
		while ( !bFound && (SND_streams_Names[ nID ].nAudioID != SND_NULL_SND_ID) )
		{
			if ( SND_streams_Names[ nID ].nAudioID == nAudioID )
			{
				pAudioName = SND_streams_Names[ nID ].SndName;
				bFound     = TRUE;
			}
			else
				++nID;
		}
	}
	if ( !bFound )
	{
		nID    = 0;
		bFound = FALSE;
		while ( !bFound && (SND_voices_Names[ nID ].nAudioID != SND_NULL_SND_ID) )
		{
			if ( SND_voices_Names[ nID ].nAudioID == nAudioID )
			{
				pAudioName = SND_voices_Names[ nID ].SndName;
				bFound     = TRUE;
			}
			else
				++nID;
		}
	}
exit:
#endif

	return( pAudioName );
}

///========================================================================
//	Function:		audioDump()
//
//	Description:
// 		dump the contents of the audio sound table.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	audioDump( void )
{
#ifndef AUDIO_OFF
	unsigned	snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	for( snd=0; snd<AUDIOsoundIndex; ++snd )
	{
		if ( AUDIOsounds[ snd ].nAudioID != SND_NULL_SND_ID )
		{
			TRACE( "sound %4d: %16s a:%8d s:%8d f:0x%04x v:%4d\n",
				snd,
				audioIDname( AUDIOsounds[ snd ].nAudioID ),
				AUDIOsounds[ snd ].nAudioID,
				AUDIOsounds[ snd ].nSndID,
				AUDIOsounds[ snd ].bFlags,
				AUDIOsounds[ snd ].nVolume
				 );
		}
	}

#endif
}

void	SndSetVolumePoint(ULONG nSndID, SPOINT *pPoint)
{
	LONG	volume;
	LONG	nMasterVolume;

	if ( nSndID == SND_NULL_SND_ID )
		return;

	nMasterVolume = audioGetMasterVolume( SND_SFX_FLAG );
	volume = (audioFindVolumePercent(pPoint) * nMasterVolume) / 100;
	SndSetVolumePercent(nSndID, volume, FALSE);
}

void	SndPlayItem(ULONG nSndID, ITEM *pItem)
{
	LONG	volume;
	LONG	nMasterVolume;

	if ( nSndID == SND_NULL_SND_ID )
		return;

	nMasterVolume = audioGetMasterVolume( SND_SFX_FLAG );
	volume = (audioFindVolumeItem(pItem) * nMasterVolume) / 100;
	sndPlay(nSndID);
	SndSetVolumePercent(nSndID, volume, FALSE);
}

ULONG	AudioPlayItem(ULONG nAudioID, ITEM *pItem)
{
	LONG	volume;
	ULONG	sndID = SND_NULL_SND_ID;
	AUDIO_IDS*	pAudioPtr;
	LONG		nMasterVolume;

	nMasterVolume = audioGetMasterVolume( SND_SFX_FLAG );
	volume = (audioFindVolumeItem(pItem) * nMasterVolume) / 100;
	if (volume)	{

		// see if we already have this sound
		pAudioPtr = audioGetSndByAudioID( nAudioID  );
		if ( pAudioPtr == (AUDIO_IDS*)SND_NULL_SND_PTR )	{
			sndID = audioCreateSnd( AUDIOsfxID, nAudioID, 0, SND_SFX_FLAG );
			audioStoreSnd( nAudioID, sndID, SND_SFX_FLAG );
		}
		else
			sndID = audioCreateSnd( AUDIOsfxID, nAudioID, 0, SND_SFX_FLAG | SND_DELETE_FLAG );

		if ( sndID != SND_NULL_SND_ID )	{
			sndPlay(sndID);
			SndSetVolumePercent(sndID, volume, FALSE);
		}
	}

	return sndID;
}

ULONG	AudioPlayPoint(ULONG nAudioID, SPOINT *pPoint)
{
	LONG	volume;
	LONG	nMasterVolume;
	ULONG	sndID = SND_NULL_SND_ID;

	nMasterVolume = audioGetMasterVolume( SND_SFX_FLAG );
	volume = (audioFindVolumePercent(pPoint) * nMasterVolume) / 100;
	if (volume)	{
		sndID = audioCreateSnd( AUDIOsfxID, nAudioID, 0, SND_SFX_FLAG | SND_DELETE_FLAG );
		if ( sndID != SND_NULL_SND_ID )	{
			sndPlay(sndID);
			SndSetVolumePercent(sndID, volume, FALSE);
		}
	}

	return sndID;
}

void SndSetVolumePercent( ULONG nSndID, ULONG Percent, BOOL bMax )
{
	AUDIO_IDS*	pSndID = (AUDIO_IDS*)SND_NULL_SND_PTR;
	LONG nVolume;

	if ( nSndID == SND_NULL_SND_ID )
		return;

	if ( Percent )
	{
		nVolume = 0-(MIN_VOLUME-(VOLUME_PERCENT_MULT * Percent)) ;
		if (nVolume > 0)
			nVolume = 0;
		if (nVolume < -MIN_VOLUME)
			nVolume = -MIN_VOLUME;
	}
	else
		nVolume = SND_MIN_VOLUME;

	audioSetVolume( nSndID, nVolume, bMax  );
}

int audioFindVolumePercent ( SPOINT *pSrc) {
	SPOINT where;
	int volume;
	int distance;
	where = AudioPosition();

	distance = GetDistance( pSrc, &where );

	volume = VOL_MAX_PERCENT - ((distance*VOL_MAX_PERCENT)/AUDIO_RANGE) ;
//	volume = volume*volume/VOL_MAX_PERCENT;
	if (volume < VOL_MIN_PERCENT) volume = 0;
	if( volume > VOL_MAX_PERCENT) volume = VOL_MAX_PERCENT ;
#ifdef SND_DEBUG
	TRACE("distance = %d Volume = %d\n", distance, volume);
#endif
	return volume;
}

int audioFindVolumeItem( ITEM *pItem) {
	if (!pItem)	{
		TRACE("NULL weapon pOwner\n");
		return 100;
	}
	return(audioFindVolumePercent(&pItem->position));
}

void Set_STRM_Volume_Percent( ULONG nSndID ,ULONG Percent, BOOL bMax )
{
	if ( nSndID == SND_NULL_SND_ID )
		return;

	SndSetVolumePercent( nSndID, Percent, bMax );
}

void Set_SFX_Volume_Percent( ULONG nSndID, ULONG Percent, BOOL bMax )
{
#ifndef AUDIO_OFF
LONG nVolume;

	if ( nSndID == SND_NULL_SND_ID )
		return;

	if ( Percent )
	{
		nVolume = 0-(MIN_VOLUME-(VOLUME_PERCENT_MULT * Percent)) ;
		if (nVolume > 0)
			nVolume = 0;
		if (nVolume < -MIN_VOLUME)
			nVolume = -MIN_VOLUME;
	}
	else
		nVolume = SND_MIN_VOLUME;

	audioSetVolume( nSndID, nVolume, bMax );
#endif
}

void Modify_SFX_Volume_Percent( ULONG nSndID ,ULONG Percent)
{
#ifndef AUDIO_OFF
LONG nVolume;

	if ( nSndID == SND_NULL_SND_ID )
		return;

	nVolume = audioGetVolume( nSndID ) + (VOLUME_PERCENT_MULT * Percent) ;
	if (nVolume > 0)
		nVolume = 0;
	if (nVolume < -MIN_VOLUME)
		nVolume = -MIN_VOLUME;
	audioSetVolume( nSndID, nVolume, FALSE );
#endif
}

ULONG PlayStreamUnit(ULONG nAudioID, ULONG uid, USHORT bFlags)
{
	ULONG	nSndID  = SND_NULL_SND_ID;
	ULONG	nResult = 0;

	if ( nAudioID == SND_NULL_SND_ID )
		return( nResult );

	// using the uid, acquire the unit and retrieve any additional
	// audio info and create a linked audio block.

#ifdef SNDCHK
	TRACE("PlayStreamUnit(%s:%ld)\n",audioIDname( nAudioID ), nAudioID );
#endif

	if ( (bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG )
		nResult = PlayStream( nAudioID, bFlags, TRUE );
	else
		nResult = PlayStream( nAudioID, bFlags, FALSE );

	return( nResult );
}


ULONG EndStreamUnit(ULONG nAudioID)
{
	ULONG	nSndID  = SND_NULL_SND_ID;
	ULONG	nResult = 0;

	if ( nAudioID == SND_NULL_SND_ID )
		return( nResult );

#ifdef SNDCHK
	TRACE("EndStreamUnit(%s:%ld)\n",audioIDname( nAudioID ), nAudioID );
#endif

	nResult = audioDelete( nAudioID );

	return( nResult );
}



ULONG PlayStream(ULONG nAudioID, USHORT bFlags, BOOL bDelete )
{
	ULONG		nSndID = SND_NULL_SND_ID;
	AUDIO_IDS*	pSndID = (AUDIO_IDS*)SND_NULL_SND_PTR;

#ifndef AUDIO_OFF

	// make sure we have a valid audio ID
	if ( nAudioID == SND_NULL_SND_ID )
		return( nSndID );

	// maker sure the appropriate processor is active
	if ( ((bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG) && !STRMenabled )
		return( nSndID );
	if ( ((bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG) && !VOICEenabled )
		return( nSndID );
	if ( ((bFlags & SND_SFX_FLAG) == SND_SFX_FLAG) && !SFXenabled )
		return( nSndID );

#ifdef DBG_AUDIO
	TRACE("PlayStream(%s:%ld:%d)\n",audioIDname( nAudioID ), nAudioID, bDelete );
#endif

	// make sure this a stream
	bFlags |= SND_STREAM_FLAG;
	if ( bDelete )
		bFlags |= SND_DELETE_FLAG;

	if ( (bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
	{
		nSndID = voiceCreateStream( AUDIOvoiceID, nAudioID, 0, bFlags );
		if( nSndID != SND_NULL_SND_ID )
		{
			audioStoreSnd( nAudioID, nSndID, bFlags );
			voicePlaySnd( nSndID );
		}
	}
	else
	if ( (bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
	{
		nSndID = strmCreateStream( AUDIOstreamID, nAudioID, 0, bFlags );
		if( nSndID != SND_NULL_SND_ID )
		{
			audioStoreSnd( nAudioID, nSndID, bFlags );
			strmPlaySnd( nSndID );
		}
	}
	else
	if ( (bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
	{
		nSndID = audioCreateSnd( AUDIOsfxID, nAudioID, 0, bFlags );
		if( nSndID != SND_NULL_SND_ID )
		{
			audioStoreSnd( nAudioID, nSndID, bFlags );
			sfxPlaySnd( nSndID );
		}
	}

	if ( nSndID == SND_NULL_SND_ID )
	{
		// report an error
		TRACE("ERROR: failed to create sound (%d:%s). [%s:%d]\n", 
			nAudioID, audioIDname( nAudioID ), __FILE__, __LINE__ );
		return( nSndID );
	}
#endif

	return( nSndID );
}

void StopStream(ULONG nAudioID)
{
#ifndef AUDIO_OFF
	BOOL		bDone;
	ULONG		nLastSndID = SND_NULL_SND_ID;
	AUDIO_IDS*	pSndID     = (AUDIO_IDS*)SND_NULL_SND_PTR;

	// make sure this is a valid ID
	if ( nAudioID == SND_NULL_SND_ID )
		return;

#ifdef DBG_AUDIO
TRACE("StopStream(%s:%ld)\n",audioIDname( nAudioID ), nAudioID );
#endif

	// find the SndID using the AudioID
	bDone = FALSE;
	while (!bDone )
	{
		pSndID = audioGetSndByAudioID( nAudioID );
		if ( (pSndID != (AUDIO_IDS*)SND_NULL_SND_PTR) && (pSndID->nSndID != SND_NULL_SND_ID) )	// halt the stream
		{
#ifdef STATES_DEBUG
			TRACE( "retrieved: %s A:%ld S:%ld F:0x%x V:%ld\n",
				audioIDname( pSndID->nAudioID ), pSndID->nAudioID,
				pSndID->nSndID, pSndID->bFlags, pSndID->nVolume );
#endif
			if( nLastSndID == pSndID->nSndID )
				return;
//			ASSERT(nLastSndID != pSndID->nSndID);
			nLastSndID = pSndID->nSndID;
			audioStop( pSndID->nAudioID );
			if ( (pSndID->bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
				voiceDeleteStream(pSndID->nSndID);
			else
			if ( (pSndID->bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
				strmDeleteStream(pSndID->nSndID);
		}
		else
			bDone = TRUE;
	}
#endif
}

void StopAllStreams( void )
{
#ifndef AUDIO_OFF
	AUDIO_IDS*	pAudioPtr;
	unsigned	snd;
	BOOL		bDeleteIt;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

#ifdef DBG_AUDIO
	TRACE("\n\nStopAllStreams( AUDIOdSoundEnabled:%d )\n", AUDIOdSoundEnabled );
	TRACE("    Game State     = %s\n", GetStateName( gpGame->GetState() ) );
	TRACE("    Game Sub State = %s\n", GetSubStateName( gpGame->GetSubState() ) );
	TRACE("    Scrn State     = %s\n", ScrnGetStateName( ScrnGetState() ) );
#endif

	// take care of some special sounds
	if ( SCRNsfxSnd )
	{
		pAudioPtr = audioGetSndBySndID( SCRNsfxSnd );
		if ( pAudioPtr != (AUDIO_IDS*)SND_NULL_SND_PTR )
		{
			sfxDeleteSnd( pAudioPtr->nSndID );
			audioDeleteSnd( pAudioPtr->nSndID );
		}
	}
	if ( SCRNmusicSnd )
	{
		pAudioPtr = audioGetSndBySndID( SCRNmusicSnd );
		if ( pAudioPtr != (AUDIO_IDS*)SND_NULL_SND_PTR )
		{
			strmDeleteSnd( pAudioPtr->nSndID );
			audioDeleteSnd( pAudioPtr->nSndID );
		}
	}
	if ( SCRNvoiceSnd )
	{
		pAudioPtr = audioGetSndBySndID( SCRNvoiceSnd );
		if ( pAudioPtr != (AUDIO_IDS*)SND_NULL_SND_PTR )
		{
			voiceDeleteSnd( pAudioPtr->nSndID );
			audioDeleteSnd( pAudioPtr->nSndID );
		}
	}

	for ( snd=0;snd<AUDIOsoundIndex; ++snd )
	{
		if ( AUDIOsounds[ snd ].nSndID != SND_NULL_SND_ID )
		{
			bDeleteIt = FALSE;
			if ((AUDIOsounds[ snd ].bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
				bDeleteIt = TRUE;
			else
			if ((AUDIOsounds[ snd ].bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
				bDeleteIt = TRUE;

			if ( bDeleteIt )
			{
				// now delete this stream
				audioStop( AUDIOsounds[ snd ].nAudioID );
				if ( (AUDIOsounds[ snd ].bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
					voiceDeleteStream(AUDIOsounds[ snd ].nSndID);
				else
				if ( (AUDIOsounds[ snd ].bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
					strmDeleteStream(AUDIOsounds[ snd ].nSndID);

				AUDIOsounds[ snd ].nAudioID = SND_NULL_SND_ID;
				AUDIOsounds[ snd ].nSndID   = SND_NULL_SND_ID;
				AUDIOsounds[ snd ].bFlags   = SND_CLEAR_FLAG;
				AUDIOsounds[ snd ].nVolume  = 0;
			}
		}
	}
#endif
}

void StopAudioData( void )
{
#ifndef AUDIO_OFF
	AUDIO_IDS*	pAudioPtr;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	// take care of some special sounds
	if ( SCRNsfxSnd )
	{
		pAudioPtr = audioGetSndBySndID( SCRNsfxSnd );
		if ( pAudioPtr != (AUDIO_IDS*)SND_NULL_SND_PTR )
		{
			sfxDeleteSnd( pAudioPtr->nSndID );
			audioDeleteSnd( pAudioPtr->nSndID );
		}
	}
	if ( SCRNmusicSnd )
	{
		pAudioPtr = audioGetSndBySndID( SCRNmusicSnd );
		if ( pAudioPtr != (AUDIO_IDS*)SND_NULL_SND_PTR )
		{
			strmDeleteSnd( pAudioPtr->nSndID );
			audioDeleteSnd( pAudioPtr->nSndID );
		}
	}
	if ( SCRNvoiceSnd )
	{
		pAudioPtr = audioGetSndBySndID( SCRNvoiceSnd );
		if ( pAudioPtr != (AUDIO_IDS*)SND_NULL_SND_PTR )
		{
			voiceDeleteSnd( pAudioPtr->nSndID );
			audioDeleteSnd( pAudioPtr->nSndID );
		}
	}
#endif
}

void CleanUpSfx( void )
{
#ifndef AUDIO_OFF
	unsigned	snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	// scan through the static sounds
	for ( snd=0;snd<AUDIOsoundIndex; ++snd )
	{
		if ((AUDIOsounds[ snd ].bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
			sfxCleanUp( AUDIOsounds[ snd ].nSndID );
	}

	// now look for dynamic self deleting requested sounds
	sfxTableCleanUp();
#endif
}

void CleanUpStreams( void )
{
#ifndef AUDIO_OFF
	unsigned	snd;

	// is audio enabled
	if ( !AUDIOdSoundEnabled )
		return;

	for ( snd=0;snd<AUDIOsoundIndex; ++snd )
	{
		if ((AUDIOsounds[ snd ].bFlags & SND_MUSIC_FLAG) == SND_MUSIC_FLAG )
			strmCleanUpStreams( AUDIOsounds[ snd ].nSndID );
		else
		if ((AUDIOsounds[ snd ].bFlags & SND_VOICE_FLAG) == SND_VOICE_FLAG )
			voiceCleanUpStreams( AUDIOsounds[ snd ].nSndID );
	}
	// now look for dynamic self deleting requested streams
	strmTableCleanUp();
	voiceTableCleanUp();
#endif
}

void audioSetTableIndex( int nIndex )
{
	AUDIOsoundIndex = nIndex;
}

void audioSetIntensity( int nIntensity )
{
	AUDIOintensity = nIntensity;
}

int audioGetIntensity( void )
{
	return( AUDIOintensity );
}

void	audioCompressSoundList( void )
{
	int		nCountSounds;
	int		nLastIndex;
	int		nSndIndex;
	int		nSlotIndex;
	int		nNumberNull;

	// initialize
	nNumberNull  = 0;
	nCountSounds = 0;
	nSndIndex    = 0;
	nLastIndex   = (AUDIOsoundIndex-1);

	// walk through the list, everytime you find a NULL sound, move all
	// the others down.
	while ( nCountSounds<(int)AUDIOsoundIndex )
	{
		if ( AUDIOsounds[ nSndIndex ].nSndID == SND_NULL_SND_ID )
		{
			// compress the list
			for( nSlotIndex = nSndIndex; nSlotIndex < nLastIndex; ++nSlotIndex )
			{
				AUDIOsounds[ nSlotIndex ].nAudioID = AUDIOsounds[ nSlotIndex+1 ].nAudioID;
				AUDIOsounds[ nSlotIndex ].nSndID   = AUDIOsounds[ nSlotIndex+1 ].nSndID;
				AUDIOsounds[ nSlotIndex ].bFlags   = AUDIOsounds[ nSlotIndex+1 ].bFlags;
				AUDIOsounds[ nSlotIndex ].nVolume  = AUDIOsounds[ nSlotIndex+1 ].nVolume;
			}
			AUDIOsounds[ nSlotIndex ].nAudioID = SND_NULL_SND_ID;
			AUDIOsounds[ nSlotIndex ].nSndID   = SND_NULL_SND_ID;
			AUDIOsounds[ nSlotIndex ].bFlags   = SND_CLEAR_FLAG;
			AUDIOsounds[ nSlotIndex ].nVolume  = 0;

			// make note of the compression
			++nNumberNull;
		}
		else
			++nSndIndex;
		++nCountSounds;
	}

#if 0
	if ( nNumberNull )
		TRACE( "AUDIOsounds[] compressed (%d-%d)\n", AUDIOsoundIndex, nNumberNull );
#endif

	// update sound index
	AUDIOsoundIndex -= nNumberNull;
}

void	audioCleanUp( void )
{
	// make sure all deleted streams and sfx have been cleaned up
	CleanUpStreams();
	CleanUpSfx();

	// now compress the audio sounds list
	audioCompressSoundList();
}

///========================================================================
//								EOF
///========================================================================
