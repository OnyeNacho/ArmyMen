//========================================================================
//	FILE:			$Workfile: Voice.cpp $
//
//	DESCRIPTION:	Audio VOICE processing.
//
//					Voice Audio processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Saturday, November 15, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Voice.cpp 46    4/02/98 6:29p Phu $
//
//========================================================================
//                 COPYRIGHT(C)1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//========================================================================
//	voiceInit()
//		initialize the VOICE sound processing
//	voiceExit()
//		Clean up the VOICE processing and data
//	voiceOpen()
//		Open a VOICE .snd file for input
//	voiceLoad()
//		Load one or more VOICE sounds from a .SND file
//	voiceLoadRes()
//		Load a single resouce VOICE
//	voiceLoadWav()
//		Load a single VOICE from a .WAV
//	voicePlay()
//		Play a VOICE sound by ID
//	voiceCue()
//		Cue up a VOICE sound by ID
//	voiceFade()
//		Fade in or out a VOICE sound by ID
//	voiceStop()
//		Stop a VOICE sound by ID
//	voiceDelete()
//		Delete a VOICE sound by ID
//	voiceClose()
//		Close down an VOICE .snd file
//	voiceGetFrequency()
// 		Get the VOICE sound frequency level (effect pitch)
//	voiceSetFrequency()
// 		Set the VOICE sound requency level (effect pitch)
//	voiceGetVolume()
// 		Get the VOICE sound volume levels:
//	voiceSetVolume()
// 		Set the VOICE sound volume levels:
//	voiceGetPan()
// 		Get the VOICE sound pan levels
//	voiceSetPan()
// 		Set the VOICE sound pan levels
//	voiceMonitor()
//		Monitor VOICE processing, updating the playback buffer at regular
//		intervals.
//	voiceLoadData()
//		read in a buffer segment's worth of data
//	voiceLoadNextData()
//		read in a buffer segment's worth of data
//	voiceFindID()
//		Locate a VOICE sound ID in the VOICE lookup table
//	voiceFindSlot()
//		Locate a VOICE sound slot in the VOICE lookup table
//	voiceGetOffset()
//		Locate a VOICE sound offset in the VOICE lookup table
//	voiceGetFileName()
//		Retreive the VOICE filename associated with a file pointer
//	voiceDelFileName()
//		Delete the VOICE filename associated with a file pointer
//	voiceTimerCheck()
//		Verify that a timer ID belongs to the voiceMonitor.
//	voiceSetLink()
//		Link a dynamic list of voice sounds together. It is assumed that all
//		the listed streams have been loaded.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Voice.cpp $
//  
//  46    4/02/98 6:29p Phu
//  typecast to avoid warnings
//  
//  45    3/25/98 4:09p Aburgess
//  using new DIRECTSOUND flags
//  
//  44    3/21/98 6:56a Nrobinso
//  fix crash bugs
//  
//  42    3/20/98 11:53a Aburgess
//  modifications made to correct VOICE and MUSIC cut offs. It apprears
//  that ALL Music and Voice streams need to be run with LOOP on.
//  
//  41    3/18/98 2:23p Aburgess
//  modifications to correct update error
//  
//  40    3/18/98 11:45a Aburgess
//  added debug and cleared unused code
//  
//  39    3/17/98 11:26a Aburgess
//  correction of on/Off toggles
//  
//  38    3/16/98 3:32p Aburgess
//  correction of Audio deletion
//  
//  37    3/16/98 10:34a Aburgess
//  modifications made to pulee setting of minimum timerEvent period and
//  termination to audioEnable() and audioDisable() respectively.
//  
//  36    3/11/98 3:59p Aburgess
//  compiled out VOICE and MUSIC queues
//  
//  35    3/06/98 5:17p Aburgess
//  correction of audio flags and volume modifications
//  
//  34    3/02/98 10:32a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  33    2/13/98 10:28a Aburgess
//  removed superfluous trace statements
//  
//  32    2/03/98 3:29p Aburgess
//  eliminated infinite loop on stream load problem
//  
//  31    2/03/98 2:40p Aburgess
//  modifications made to correct music stream failures
//  
//  30    1/30/98 12:59p Bwilcox
//  
//  28    1/26/98 12:03p Nrobinso
//  new path defines
//  
//  27    1/21/98 2:03p Nrobinso
//  modification to stream updates for non queued items
//  
//  26    1/21/98 1:35p Aburgess
//  fix to illiminate voice orders
//  
//  25    1/21/98 9:22a Aburgess
//  modifications made to shorten the STRM and VOICE monitor interrupts.
//  Also merged the audio ON/OFF switching. In addition, all audio is now
//  turned off during mission load as that routine has a large frame
//  overrun problem disallowing updates to audio.
//  
//  24    1/05/98 2:31p Aburgess
//  corrected Voice deletions.
//  
//  23    1/05/98 10:32a Aburgess
//  latest attempt to resolve Streaming bug. Voice is now handled in a
//  seperate handler.
//  
//  22    12/23/97 6:26p Nrobinso
//  use audio variables for on/off
//  
//  21    12/22/97 11:35a Aburgess
//  added Snd prototype equivalents
//  
//  20    12/19/97 1:52p Aburgess
//  clarification of nSndID usage
//  
//  19    12/18/97 1:21p Aburgess
//  attempt to apply volume changes to Voice. Also now managing Voice queue
//  on enable and disable of audio
//  
//  18    12/15/97 11:02a Aburgess
//  put debug under compile time control
//  
//  17    12/15/97 10:20a Aburgess
//  added EventTimer killing.
//  
//  16    12/15/97 9:03a Aburgess
//  conversion to limit # of voice and music streams playing
//  
//  15    12/09/97 12:50p Aburgess
//  correction of VOICE streaming
//  
//  14    12/09/97 12:12p Phu
//  
//  14    12/09/97 12:12p Phu
//  
//  13    12/07/97 6:28p Aburgess
//  disabled debug trace
//  
//  12    12/04/97 4:19p Nrobinso
//  check for null sound id
//  
//  11    12/04/97 9:14a Aburgess
//  Modifications made to properly handle delete race condition with
//  strmMonitor. Actual sound allocation tracking added to help minimize
//  static tables for audio
//  
//  10    12/02/97 10:21a Aburgess
//  locking mechanism added for deletes (load?)
//  
//  9     12/01/97 9:59a Aburgess
//  removed superfluous error reporting
//  
//  8     11/24/97 2:57p Aburgess
//  debug modification
//  
//  7     11/21/97 9:15a Aburgess
//  debug SND id reporting
//  
//  6     11/20/97 3:32p Aburgess
//  modifications made to allow app to run regardless of existence of .ASD,
//  .AST files or DirectSound itself
//  
//  5     11/20/97 11:55a Aburgess
//  audio modifications
//  
//  4     11/18/97 10:31a Aburgess
//  corrected path specifications to be relative to BASE_WORK_PATH. Added
//  class function to miscfile (cdPath) that changes based on starting from
//  BASE_WORK_PATH
//  
//  3     11/17/97 10:11a Aburgess
//  rework of audio/voice/strm interfaces. Additional voice-overs
//  
//  2     11/16/97 2:21p Aburgess
//  voice file cleanup (fclose)
//  
//  1     11/16/97 12:45p Aburgess
//  voice audio/text process
//  
//  $Nokeywords:$
///========================================================================
#include "stdafx.h"

#include "snd.h"			// SND      defines, structures, and prototypes
#include "strm.h"			// STRM     defines, structures, and prototypes
#include "voice.h"			// VOICE	internal defines and structures

#include "util.h"
#include "fileio.h"
#include "miscfile.h"

extern	char*	audioIDname( ULONG nAudioID );
extern	char*	audioSndIDname( ULONG nSndID );
extern	BOOL	audioDeleteSnd( ULONG nSndID  );
extern	void	SndSetVolumePercent( ULONG nSndID ,ULONG Percent, BOOL bMax );
extern	LONG	audioGetMasterVolume( USHORT bFlag );

///========================================================================
//							LOCAL DEFINES
///========================================================================

///========================================================================
//							LOCAL DATA TYPES
///========================================================================

///========================================================================
//							LOCAL VARIABLES
///========================================================================

// VOICE lookup table
VOICE_SND*		VOICElookupTable;
VOICE_TEXT		VOICEtextTable[ VOICE_MAX_IDS ];
unsigned		VOICEnextText;
unsigned		VOICEmaxSounds;
unsigned		VOICEactualMaxSounds;
unsigned		VOICEsoundsActive;

SND_HEADER*		VOICEsndHeader;

static	FILE*	pVOICEfile;
static	FILE*	pTEXTfile;
static	long	VOICEwaitCount;

static	ULONG	VOICEnextID;

#ifndef AUDIO_TIMER
static	int		VOICEtimerID;
#endif

static	LONG	VOICEvoiceMasterVolume = 100;
static	LONG	VOICEmusicMasterVolume = 100;

BOOL			VOICEenabled;
BOOL			VOICEon;
BOOL			VOICETEXTenabled;

static	ULONG	VOICEqueue[ VOICE_MAX_QUEUE_ENTRIES ];
static	int		VOICEqueueCount = 0;

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
BOOL		voiceLoadData( VOICE_SND* pVoiceTblPtr, BYTE* pDSBuffData, DWORD maxLen );
VOICE_SND*	voiceFindSlot( void );
ULONG		voiceGetOffset( ULONG nSndID, unsigned nIndexToLoad );
void		voiceLoadText ( void );
void		voiceDump( VOICE_SND* pVoiceTblPtr );


///========================================================================
//	Function:		voiceInit()
//
//	Description:
//		initialize the Voice Stream sound processing
//
//	Input:			nMaxSounds		maximum size of the voice sound table
//
//	Ouput:			error			FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		voiceInit ( unsigned nMaxSounds )
{
	VOICE_SND*	pVoiceTblPtr;
	unsigned	index;
	BOOL		error = TRUE;	// assume failure

	// remember the max number of sounds that can be created
	VOICEmaxSounds       = nMaxSounds;
	VOICEactualMaxSounds = 0;
	VOICEsoundsActive    = 0;
	VOICEwaitCount       = 0;
	VOICEnextID          = VOICE_START_ID;
	VOICEnextText        = 0;

	for( index=0;index<VOICE_MAX_QUEUE_ENTRIES;++index)
		VOICEqueue[ index ] = 0;
	VOICEqueueCount = 0;

	VOICEenabled      = FALSE;
	VOICETEXTenabled  = FALSE;

	// allocate the memory necessary to support
	VOICElookupTable = (VOICE_SND*)malloc( VOICEmaxSounds* sizeof(VOICE_SND) );
	if ( VOICElookupTable == NULL )
	{
		// report an error
		TRACE("ERROR: Insufficient memory available. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}
#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): VOICE lookup table [%s : %d]\n",
			( VOICEmaxSounds* sizeof(VOICE_SND) ),__FILE__, __LINE__ );
#endif

	// initialize the voice lookup table
	pVoiceTblPtr = VOICElookupTable;
	for( index=0; index<VOICEmaxSounds; ++index, pVoiceTblPtr++ )
	{
		pVoiceTblPtr->bLock              = FALSE;			// audio lock
		pVoiceTblPtr->nAudioID			 = SND_NULL_SND_ID;	// audio sound identifier
		pVoiceTblPtr->nVoiceID			 = SND_NULL_SND_ID;	// voice sound identifier
		pVoiceTblPtr->nSndID			 = SND_NULL_SND_ID;	// sound identifier
		pVoiceTblPtr->bFlags			 = SND_CLEAR_FLAG;	// Boolean Flag fields
		pVoiceTblPtr->pWaveForm          = (WAVEFORMATEX*)NULL; // Wave Format data structure
		pVoiceTblPtr->nSndStart          = 0;			// index into .snd or .wav file to read from
		pVoiceTblPtr->nSndOffset         = 0;			// offset into file to reach sound chunk
														// this is filled at load time.
		pVoiceTblPtr->nSndSize           = 0;			// size of raw data
		pVoiceTblPtr->uTimerID           = 0;			// play interrupt timer ID
		pVoiceTblPtr->dwBufferSize       = 0;			// Size of the entire buffer
		pVoiceTblPtr->dwBufferSegSize    = 0;			// Size of one buffer segment
		pVoiceTblPtr->dwNextWriteOffset  = 0;			// Offset to next buffer segment
		pVoiceTblPtr->dwPlayLast         = 0;			// Used with above to show prog
		pVoiceTblPtr->dwProgress         = 0;			// Used with above to show prog
		pVoiceTblPtr->nRemainingBytes    = 0;			// Segments 'til timer shutdown
		pVoiceTblPtr->nSndLink           = SND_NULL_SND_ID;	// Link to another voice ID

	}

	// initialize the SND header structure
	VOICEsndHeader = NULL;

	// initialize the input file pointer
	pVOICEfile = NULL;

#ifndef	AUDIO_TIMER
	VOICEtimerID = 1;
#endif

	// set the VOICE toggle
//	voiceSetOn( TRUE );

	// go ahead and load in the voice text
	voiceLoadText();

	// if we got here we were successful
	error = FALSE;

exit:
	return( error );
}


///========================================================================
//	Function:		voiceExit()
//
//	Description:
//		Clean up the VOICE processing and data
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void		voiceExit ( void )
{
	VOICE_SND*	pVoiceTblPtr;
	unsigned	index;

	for( index=0;index<VOICE_MAX_QUEUE_ENTRIES;++index)
		VOICEqueue[ index ] = 0;
	VOICEqueueCount = 0;

	// cleanup the voice lookup table
	pVoiceTblPtr = VOICElookupTable;
	if ( pVoiceTblPtr != (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// clean up each legal sound in the table
		for ( index=0; index<VOICEmaxSounds; ++index )
		{
			// delete this sound
			if ( pVoiceTblPtr->nVoiceID != (ULONG)SND_NULL_SND_ID )
			{
				voiceDeleteSnd( pVoiceTblPtr->nSndID );

				// now delete the snd
				audioDeleteSnd( pVoiceTblPtr->nSndID );
			}

			// check the next entry
			++pVoiceTblPtr;
		}

		// de-allocate the look up table structure
		if ( VOICElookupTable )
		{
			free( VOICElookupTable );
			VOICElookupTable = (VOICE_SND*)SND_NULL_SND_PTR;
		}
	}

	// de-allocate the SND header structure
	if ( VOICEsndHeader )
	{
		free( VOICEsndHeader );
		VOICEsndHeader = NULL;

#ifdef MALLOC_DEBUG
			TRACE( "free: VOICE header [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}

	// now close the voice file
	if ( pVOICEfile )
	{
		fclose( pVOICEfile );
		pVOICEfile = NULL;
	}

	// disable the stream processing
	VOICEenabled = FALSE;

#ifdef SND_DEBUG
	TRACE( "VOICEactualMaxSounds = %d\n", VOICEactualMaxSounds );
#endif
}


///========================================================================
//	Function:		voiceOpen()
//
//	Description:
//		open a VOICE .snd file for input
//
//	Input:			pFilename		.SND filename that needs opening
//
//	Ouput:			nFileID			file id to file info is successful
//									NULL otherwise
//
///========================================================================

unsigned	voiceOpen ( char* pFilename )
{
	unsigned	nFileID = SND_NULL_SND_ID;

	// make sure there isn't a file open already
	if ( pVOICEfile != NULL )
	{
		// report an error
		TRACE("WARNING: voice file already open. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// now open the new .SND file
	if ( (pVOICEfile = (FILE*)fopen( pFilename, "rb" )) == NULL )
	{
		// report an error
		TRACE("ERROR: failed to open file: \"%s\". [%s:%d]\n\n", 
			  pFilename, __FILE__, __LINE__ );
		goto exit;
	}

	// make sure the SND header is free
	if ( VOICEsndHeader )
	{
		free( VOICEsndHeader );
		VOICEsndHeader = NULL;

#ifdef MALLOC_DEBUG
		TRACE( "free: VOICE header [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}

	// copy in the .SND header information
	VOICEsndHeader = (SND_HEADER*)malloc( sizeof( SND_HEADER ) );
	if ( VOICEsndHeader == NULL )
	{
		// report an error
		TRACE("ERROR: Insufficient memory available. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}
#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): VOICE header [%s : %d]\n", ( sizeof( SND_HEADER ) ), __FILE__, __LINE__ );
#endif

	if ( fread( VOICEsndHeader, sizeof( SND_HEADER ), 1, pVOICEfile ) != 1 )
	{
		// report an error: failed writing header
		TRACE("ERROR: failed to read .SND header. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		if ( pVOICEfile )
			fclose( pVOICEfile );
		pVOICEfile = NULL;
		nFileID = SND_NULL_SND_ID;
	}

	// if we made it here, its time to save off the filename with
	// the file pointer for use at load time to set the filename to
	// the stream.
	nFileID = sndSaveFile( pVOICEfile, pFilename );

exit:
	return( nFileID );
}


///========================================================================
//	Function:		voiceMaxSounds()
//
//	Description:
//		return the current number of sounds in the VOICE lookup table
//
//	Input:			none
//
//	Ouput:			maxSounds		number of sounds in the look table
//									NULL otherwise
//
///========================================================================

unsigned	voiceMaxSounds ( void )
{
	unsigned	maxSounds = 0;

	if ( VOICEsndHeader == NULL )
	{
		// report an error
		TRACE("WARNING: VOICE sound lookup table not present. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// get the sound count
	maxSounds = VOICEsndHeader->numberOfSounds;
exit:
	return( maxSounds );
}


///========================================================================
//	Function:		voiceLoad()
//
//	Description:
//		Load one or more VOICE sounds from a .SND file
//
//	Input:			nFileID			id of file to access
//					nAudioID		audio Id number to be stored into
//					nIndexToLoad	index within .SND file from which to
//									load VOICE sound
//					bFlags			falgs associated with this sound.
//
//	Ouput:			nSndID			ID assigned to this sound if successful
//									SND_NULL_SND_ID if failure
//
///========================================================================

ULONG	voiceLoad ( unsigned nFileID, ULONG nAudioID, unsigned nIndexToLoad, USHORT bFlags )
{
	DSBUFFERDESC		dsBufferDesc;
	SND*				pSndPtr;
	LPDIRECTSOUND		pDirectSound;
	DWORD				dwDataLen1;
	DWORD				dwDataLen2;
    BYTE*				pDSBuffData1;
    BYTE*				pDSBuffData2;
	unsigned			status;
	ULONG				offset;
	unsigned			error;
	int					nSndIdx;
	VOICE_SND*			pVoiceTblPtr = NULL;
	ULONG				nSndID       = SND_NULL_SND_ID;

#ifdef SNDCHK
	TRACE("voiceLoad( ID:%ld)\n",nAudioID ); 
#endif

	if ( !VOICEenabled )
		return( nSndID );

	if ( nAudioID == SND_NULL_SND_ID )
		return( nSndID );

#ifdef DBG_AUDIO
	char* pAudioName = audioIDname( nAudioID );
	if ( strcmp( pAudioName, "MENDOWN" ) == 0 )
		TRACE("voiceLoad( %s:%ld )\n", pAudioName, nAudioID ); 
#endif

	// make sure the table isn't full already
	if ( VOICEsoundsActive == VOICEmaxSounds )
	{
		// report an error that the sound table is full
		TRACE("ERROR: voice table limited exceeded (%d). [%s:%d]\n\n", 
			  VOICEmaxSounds, __FILE__, __LINE__ );
		goto exit;
	}

    // Get the DirectSound Object for this application
	pDirectSound = sndGetDSobject();
	if ( !pDirectSound )
		goto exit;

	// get the expected offset
	offset = voiceGetOffset( nAudioID, nIndexToLoad );
	if ( offset == SND_NULL_SND_ID )
	{
		// report an error that the sound table is full
		TRACE("ERROR: failed to get voice offset.[%s:%d]\n", 
			   __FILE__, __LINE__ );
		goto exit;
	}

	// create this sound. if already created will return address
	// of existing sound
	nSndID = sndCreate( nAudioID, bFlags, nFileID, &offset );
	if ( nSndID == SND_NULL_SND_ID )
	{
		// report an error that the sound table is full
		TRACE("ERROR: failed to create new voice entry.[%s:%d]\n", 
			   __FILE__, __LINE__ );
		goto cleanUp;
	}

	// find an available sound
	pVoiceTblPtr = voiceFindSlot();
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// report an error that the sound table is full
		TRACE("ERROR: failed to create new voice entry.[%s:%d]\n\n", 
			   __FILE__, __LINE__ );
		goto cleanUp;
	}

	// if we're here we have a voice entry to fill.
	// start by locating the SND and load in the data
	status = sndFindSndID( nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, nSndID, __FILE__, __LINE__ );
		goto cleanUp;
	}

	// initialize the VOICE entry
	pVoiceTblPtr->nAudioID = nAudioID;			// audio sound identifier
	pVoiceTblPtr->nVoiceID = VOICEnextID++;		// stream sound identifier
	pVoiceTblPtr->nSndID   = nSndID;			// sound identifier
	pVoiceTblPtr->bFlags   = bFlags;			// Flag fields

	// save this location in the file incase we need to reload
	pVoiceTblPtr->nSndStart  = pSndPtr->wavSnd.nSndStart;
	pVoiceTblPtr->nSndOffset = pVoiceTblPtr->nSndStart;

	// save the size of the stream for termination purposes
	pVoiceTblPtr->nSndSize   = pSndPtr->wavSnd.nSndSize;

    // Calculate a buffer length, making sure it is an exact multiple of the
    // buffer segment size.
	pVoiceTblPtr->pWaveForm    = &(pSndPtr->wavSnd.wfSndFormat);
    pVoiceTblPtr->dwBufferSize = ((DWORD)pVoiceTblPtr->pWaveForm->nAvgBytesPerSec
                               * (((STRM_NUM_BUFFER_SEGMENTS * STRM_PLAYBACK_TIMER_PERIOD)
                               / 10)) / 100);
    pVoiceTblPtr->dwBufferSegSize   = pVoiceTblPtr->dwBufferSize / STRM_NUM_BUFFER_SEGMENTS;
    pVoiceTblPtr->dwBufferSize      = pVoiceTblPtr->dwBufferSegSize * STRM_NUM_BUFFER_SEGMENTS;

    // Create the secondary DirectSoundBuffer object to receive our sound data.
	memset( &dsBufferDesc, 0, sizeof(DSBUFFERDESC)); 
    dsBufferDesc.dwSize        = sizeof(DSBUFFERDESC);
    dsBufferDesc.dwFlags       = DSBCAPS_CTRLDEFAULT | DSBCAPS_GETCURRENTPOSITION2;
    dsBufferDesc.dwBufferBytes = pVoiceTblPtr->dwBufferSize;

    /* Set Format properties according to the WAVE file we just opened */
    dsBufferDesc.lpwfxFormat   = pVoiceTblPtr->pWaveForm;
    error = pDirectSound->CreateSoundBuffer(
											&dsBufferDesc,
										    &(pVoiceTblPtr->pDSBuffer),
										    NULL
										   );
    if (error != DS_OK)
	{
		// report an error
		TRACE("voiceLoad( %s:%ld)\n", audioIDname(nAudioID),nAudioID ); 
		TRACE("ERROR:  failed to create the DirectSoundbuffer (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto cleanUp;
	}

	// since we're loading here, we can't of found the End Of Stream and
	// we don't have segments ready as yet.
    pVoiceTblPtr->bFlags           &= ~SND_EOS_FLAG;
    pVoiceTblPtr->nRemainingBytes   = 0;
	pVoiceTblPtr->dwNextWriteOffset = 0;
	pVoiceTblPtr->dwPlayLast        = 0;
	pVoiceTblPtr->dwProgress        = 0;

    // Lock the DS buffer
    error = pVoiceTblPtr->pDSBuffer->Lock( 0, pVoiceTblPtr->dwBufferSize,
										 (LPLPVOID)&pDSBuffData1, &dwDataLen1,
										 (LPLPVOID)&pDSBuffData2, &dwDataLen2,
										 0
									   );
    if (error != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer lock (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto cleanUp;
	}

    // Write wave data to the DS buffer
	if ( dwDataLen1 )
	{
		if ( voiceLoadData( pVoiceTblPtr, (BYTE*)pDSBuffData1, dwDataLen1 ) )
		{
			// report an error
			TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );

			// Unlock the DS buffer
			error = pVoiceTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
												   (LPVOID)pDSBuffData2, 0
												 );
			if ( error != DS_OK)
			{
				// report an error
				TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
					DSErrorToString(error), __FILE__, __LINE__ );
				goto cleanUp;
			}

			goto cleanUp;
		}
	}

    // Unlock the DS buffer
    error = pVoiceTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
										   (LPVOID)pDSBuffData2, 0
									     );
	if ( error != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto cleanUp;
	}

	pVoiceTblPtr->bFlags           &= ~SND_DONE_FLAG;

	// if we made it here we've had success
	++VOICEsoundsActive;
	if ( VOICEactualMaxSounds < VOICEsoundsActive )
		VOICEactualMaxSounds = VOICEsoundsActive;

#ifdef DBG_AUDIO
//	if ( strcmp( pAudioName, "MENDOWN" ) == 0 )
//		voiceDump( pStrmTblPtr );
#endif

	// see if we were error free
	goto exit;

	// clean up after getting an error
cleanUp:
	// clean up this SFX entry
	if ( pVoiceTblPtr )
	{
		if ( pVoiceTblPtr != (VOICE_SND*)SND_NULL_SND_PTR )
		{
			pVoiceTblPtr->nVoiceID	= SND_NULL_SND_ID;	// stream sound identifier
			pVoiceTblPtr->nSndID	= SND_NULL_SND_ID;	// sound identifier
			pVoiceTblPtr->bFlags	= SND_CLEAR_FLAG;	// Boolean Flag fields
			pVoiceTblPtr->pWaveForm	= (WAVEFORMATEX*)NULL;// waveformatex information
			if ( pVoiceTblPtr->pDSBuffer )
			{
				error = pVoiceTblPtr->pDSBuffer->Release();
				if ( error != DS_OK )
				{
					// report an error
					TRACE("ERROR:  failed to relase the DirectSoundbuffer (%s) [%s:%d]\n", 
						DSErrorToString(error), __FILE__, __LINE__ );
					goto exit;
				}
			}
		}

		// now attempt to clean up the SND entry
		if ( nSndID != SND_NULL_SND_ID )
			sndDelete( nSndID );

		pVoiceTblPtr = NULL;
	}

	// return the result to the caller
exit:
	if ( pVoiceTblPtr )
	{
		// unlock this sound
//		pVoiceTblPtr->bLock	= FALSE;

		nSndID = pVoiceTblPtr->nSndID;
	}
	return( nSndID );
}


///========================================================================
//	Function:		voiceLoadRes()
//
//	Description:
//		Load a single resouce VOICE
//
//	Input:			nResId			Resource ID containing voice data
//
//	Ouput:			nVoiceID			voice ID assigned to this resource
//
///========================================================================

ULONG		voiceLoadRes ( unsigned nResId )
{

#ifdef TRACK
TRACE("Entered: voiceLoadRes()...\n" );
#endif


#ifdef TRACK
TRACE("Exiting: voiceLoadRes()...\n" );
#endif

	return( 1L );
}


///========================================================================
//	Function:		voiceLoadWav()
//
//	Description:
//		Load a single VOICE from a .WAV
//
//	Input:			pWaveFilename	data file containing voice data
//					
//
//	Ouput:			nVoiceID			voice ID assigned to this wave
//
///========================================================================

ULONG		voiceLoadWav ( char* pWaveFilename )
{

#ifdef TRACK
TRACE("Entered: voiceLoadWav()...\n" );
#endif

#ifdef TRACK
TRACE("Exiting: voiceLoadWav()...\n" );
#endif

	return( 1L );
}


///========================================================================
//	Function:		voiceCue()
//
//	Description:
//		Cue up a VOICE by ID
//
//	Input:			nAudioID		audio Id number to be stored into
//
//	Ouput:			error			FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		voiceCue ( ULONG nAudioID )
{
	VOICE_SND*			pVoiceTblPtr;
	SND*				pSndPtr;
	DWORD				dwDataLen1;
	DWORD				dwDataLen2;
    BYTE*				pDSBuffData1;
    BYTE*				pDSBuffData2;
	int					nSndIdx;
	unsigned			status;
	BOOL				error = TRUE;		// assume failure

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nAudioID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nAudioID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to play a non-exitent nAudioID (%ld). [%s:%d]\n\n", 
			nAudioID, __FILE__, __LINE__ );
		goto exit;
	}

	// make sure we haven't already cued up
	if ( (pVoiceTblPtr->bFlags & SND_CUED_FLAG) == SND_CUED_FLAG )
	{
		// already cue'd, exit and save time
		error = FALSE;
		goto exit;
	}

	status = sndFindSndID( pVoiceTblPtr->nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, pVoiceTblPtr->nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// since we're loading here, we can't of found the End Of Stream and
	// we don't have segments ready as yet.
    pVoiceTblPtr->bFlags           &= ~SND_EOS_FLAG;
    pVoiceTblPtr->nRemainingBytes   = 0;
	pVoiceTblPtr->dwNextWriteOffset = 0;
	pVoiceTblPtr->dwPlayLast        = 0;
	pVoiceTblPtr->dwProgress        = 0;

    // Lock the DS buffer
    error = pVoiceTblPtr->pDSBuffer->Lock( 0, pVoiceTblPtr->dwBufferSize,
										 (LPLPVOID)&pDSBuffData1, &dwDataLen1,
										 (LPLPVOID)&pDSBuffData2, &dwDataLen2,
										 0
									   );
    if (error != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer lock (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// re-initialize the load position
	pVoiceTblPtr->nSndOffset = pVoiceTblPtr->nSndStart;

    // Write wave data to the DS buffer
	if ( dwDataLen1 )
	{
		if ( voiceLoadData( pVoiceTblPtr, (BYTE*)pDSBuffData1, dwDataLen1 ) )
		{
			// report an error
			TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );

			// Unlock the DS buffer
			error = pVoiceTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
												   (LPVOID)pDSBuffData2, 0
												 );
			if ( error != DS_OK)
			{
				// report an error
				TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
					DSErrorToString(error), __FILE__, __LINE__ );
				goto exit;
			}

			goto exit;
		}
	}

    // Unlock the DS buffer
    error = pVoiceTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
										   (LPVOID)pDSBuffData2, 0
									     );
	if ( error != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// mark as cued and not done playing
	pVoiceTblPtr->bFlags |= SND_CUED_FLAG;
	pVoiceTblPtr->bFlags &= ~SND_DONE_FLAG;

	// if we made it here, we were successful
	error = FALSE;
exit:
	return( error );

}

///========================================================================
//	Function:		voiceCueSnd()
//
//	Description:
//		Cue up a VOICE by SND ID
//
//	Input:			nSndID		SND Id number to be stored into
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		voiceCueSnd ( ULONG nSndID )
{
	VOICE_SND*			pVoiceTblPtr;
	SND*				pSndPtr;
	DWORD				dwDataLen1;
	DWORD				dwDataLen2;
    BYTE*				pDSBuffData1;
    BYTE*				pDSBuffData2;
	int					nSndIdx;
	unsigned			status;
	BOOL				error = TRUE;		// assume failure

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nSndID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindSndID( nSndID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to play a non-exitent nSndID (%ld). [%s:%d]\n\n", 
			nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// make sure we haven't already cued up
	if ( (pVoiceTblPtr->bFlags & SND_CUED_FLAG) == SND_CUED_FLAG )
	{
		// already cue'd, exit and save time
		error = FALSE;
		goto exit;
	}

	status = sndFindSndID( nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// since we're loading here, we can't of found the End Of Stream and
	// we don't have segments ready as yet.
    pVoiceTblPtr->bFlags           &= ~SND_EOS_FLAG;
    pVoiceTblPtr->nRemainingBytes   = 0;
	pVoiceTblPtr->dwNextWriteOffset = 0;
	pVoiceTblPtr->dwPlayLast        = 0;
	pVoiceTblPtr->dwProgress        = 0;

    // Lock the DS buffer
    error = pVoiceTblPtr->pDSBuffer->Lock( 0, pVoiceTblPtr->dwBufferSize,
										 (LPLPVOID)&pDSBuffData1, &dwDataLen1,
										 (LPLPVOID)&pDSBuffData2, &dwDataLen2,
										 0
									   );
    if (error != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer lock (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// re-initialize the load position
	pVoiceTblPtr->nSndOffset = pVoiceTblPtr->nSndStart;

    // Write wave data to the DS buffer
	if ( dwDataLen1 )
	{
		if ( voiceLoadData( pVoiceTblPtr, (BYTE*)pDSBuffData1, dwDataLen1 ) )
		{
			// report an error
			TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );

			// Unlock the DS buffer
			error = pVoiceTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
												   (LPVOID)pDSBuffData2, 0
												 );
			if ( error != DS_OK)
			{
				// report an error
				TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
					DSErrorToString(error), __FILE__, __LINE__ );
				goto exit;
			}

			goto exit;
		}
	}

    // Unlock the DS buffer
    error = pVoiceTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
										     (LPVOID)pDSBuffData2, 0
									       );
	if ( error != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// mark as cued and not done playing
	pVoiceTblPtr->bFlags |= SND_CUED_FLAG;
	pVoiceTblPtr->bFlags &= ~SND_DONE_FLAG;

	// if we made it here, we were successful
	error = FALSE;
exit:
	return( error );

}

///========================================================================
//	Function:		voicePlaySnd()
//
//	Description:
//		Play a VOICE sound by Snd ID
//
//	Input:			nSndID		SND Id number to be played
//
//	Ouput:			none
//
///========================================================================

BOOL		voicePlaySnd ( ULONG nSndID )
{
#ifdef AUDIO_TIMER
	UINT				uTimerID;
#endif

	VOICE_SND*		    pVoiceTblPtr;
	SND*				pSndPtr;
	LPDIRECTSOUNDBUFFER pDSbuffer;
	int					nSndIdx;
	unsigned			status;
	LONG				nMasterVolume = 0L;
	BOOL				error = TRUE;		// assume failure

#ifdef SNDCHK
	TRACE("voicePlaySnd( ID:%ld)\n",nSndID ); 
#endif

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nSndID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindSndID( nSndID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to play a non-exitent nSndID (%ld). [%s:%d]\n\n", 
			nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	status = sndFindSndID( nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// make sure the file for this stream is open
	if ( pSndPtr->wavSnd.pSndFile == NULL )
	{
		// report an error
		TRACE("ERROR: stream file not open for voice ID (%ld). [%s:%d]\n\n", 
			nSndID, __FILE__, __LINE__ );

		// make sure the flags for this stream are clear
		pVoiceTblPtr->bFlags = SND_CLEAR_FLAG;
		goto exit;
	}

	// stop this stream if its already playing
	if ( (pVoiceTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		if ( voiceStopSnd( nSndID ) )
		{
			// report an error
			TRACE("ERROR: failed to stop voice ID (%ld). [%s:%d]\n\n", 
				   nSndID, __FILE__, __LINE__ );

			// make sure the flags for this stream are clear
			pVoiceTblPtr->bFlags = SND_CLEAR_FLAG;
			goto exit;
		}

		// make sure the stream is properly cue'd to the begining
		if ( voiceCueSnd( nSndID ) )
		{
			// report an error
			TRACE("ERROR: failed to cue voice ID (%ld). [%s:%d]\n\n", 
				   nSndID, __FILE__, __LINE__ );

			// make sure the flags for this stream are clear
			pVoiceTblPtr->bFlags = SND_CLEAR_FLAG;
			goto exit;
		}
	}

	// get the DirectSound Buffer
	pDSbuffer = pVoiceTblPtr->pDSBuffer;
	if ( (pDSbuffer != NULL) && (pSndPtr->wavSnd.pSndFile != NULL) )
	{
		// reposition the buffer to the beginning
		pDSbuffer->SetCurrentPosition( 0 );

		// make sure the user hasn't turned voice off
		if ( VOICEon )
			nMasterVolume = audioGetMasterVolume( SND_VOICE_FLAG );
		SndSetVolumePercent( pVoiceTblPtr->nSndID, nMasterVolume, FALSE );

		// now play it
		pDSbuffer->Play( 0, 0, DSBPLAY_LOOPING );
//		if ( (pVoiceTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG)
//			pDSbuffer->Play( 0, 0, DSBPLAY_LOOPING );
//		else
//			pDSbuffer->Play( 0, 0, 0 );
	}
	else
	{
		// make sure the playing and installed flags for this stream are clear
		pVoiceTblPtr->bFlags &= ~(SND_PLAYING_FLAG|SND_INSTALLED_FLAG);
		goto exit;
	}

#ifdef AUDIO_TIMER
	// Start a timer event. After the event has been activated, the timer will
	// make a callback to the STRM monitor routine.
	uTimerID = timeSetEvent( (STRM_PLAYBACK_TIMER_PERIOD/STRM_PLAYBACK_OVERSAMPLE),
							 STRM_PLAYBACK_TIMER_ACCURACY, (LPTIMECALLBACK)voiceMonitor,
							 (DWORD)0, TIME_PERIODIC
						   );

	// if the timer was successfull installed, set the appropriate flag
	if ( uTimerID == 0 )
		goto exit;

	// remember this id for processing in the voice monitor
	pVoiceTblPtr->uTimerID = uTimerID;

#ifdef	TIMER_DEBUG
TRACE("VoicePlay() new TimerID %d\n", pVoiceTblPtr->uTimerID );
#endif

	pVoiceTblPtr->bFlags  |= (SND_INSTALLED_FLAG|SND_PLAYING_FLAG);

#else
	pVoiceTblPtr->uTimerID = VOICEtimerID++;
	pVoiceTblPtr->bFlags  |= (SND_INSTALLED_FLAG|SND_PLAYING_FLAG);
#endif

	// now clear the CUE flag
	pVoiceTblPtr->bFlags  &= ~SND_CUED_FLAG;

	// if we made it here we were successful
	error = FALSE;

#if 0
TRACE( "Playing VOICE SND Audio: %ld\n", nSndID );
#endif
 
exit:
	return( error );
}

///========================================================================
//	Function:		voiceFade()
//
//	Description:
//		Fade in or out a VOICE sound
//
//	Input:			nAudioID		audio Id number to be faded
//					nInOrOut		fade sound IN or OUT		
//
//	Ouput:			none
//
///========================================================================

BOOL		voiceFade ( ULONG nAudioID, unsigned nInOrOut )
{
	VOICE_SND*	pVoiceTblPtr;
	BOOL			error = TRUE;		// assume a failure

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nAudioID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nAudioID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to fade a non-exitent nAudioID (%ld). [%s:%d]\n\n", 
			nAudioID, __FILE__, __LINE__ );
		goto exit;
	}

	// Set up the sound for fading
	if ( nInOrOut == SND_FADE_IN_FLAG )
	{
		// strip off the FADE BITS
		pVoiceTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade In bit
		pVoiceTblPtr->bFlags |= SND_FADE_IN_FLAG;
	}
	else
	if ( nInOrOut == SND_FADE_OUT_FLAG )
	{
		// strip off the FADE BITS
		pVoiceTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade Out bit
		pVoiceTblPtr->bFlags |= SND_FADE_OUT_FLAG;
	}
	else
	{
		// report an error
		TRACE("ERROR: illegal FADE type (%d). [%s:%d]\n\n", 
			nInOrOut, __FILE__, __LINE__ );
		goto exit;
	}
		 
	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		voiceFadeSnd()
//
//	Description:
//		Fade in or out a VOICE sound
//
//	Input:			nSndID		SND Id number to be faded
//					nInOrOut	fade sound IN or OUT		
//
//	Ouput:			none
//
///========================================================================

BOOL		voiceFadeSnd ( ULONG nSndID, unsigned nInOrOut )
{
	VOICE_SND*	pVoiceTblPtr;
	BOOL			error = TRUE;		// assume a failure

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nSndID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindSndID( nSndID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to fade a non-exitent nAudioID (%ld). [%s:%d]\n\n", 
			nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// Set up the sound for fading
	if ( nInOrOut == SND_FADE_IN_FLAG )
	{
		// strip off the FADE BITS
		pVoiceTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade In bit
		pVoiceTblPtr->bFlags |= SND_FADE_IN_FLAG;
	}
	else
	if ( nInOrOut == SND_FADE_OUT_FLAG )
	{
		// strip off the FADE BITS
		pVoiceTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade Out bit
		pVoiceTblPtr->bFlags |= SND_FADE_OUT_FLAG;
	}
	else
	{
		// report an error
		TRACE("ERROR: illegal FADE type (%d). [%s:%d]\n\n", 
			nInOrOut, __FILE__, __LINE__ );
		goto exit;
	}
		 
	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		voiceStop()
//
//	Description:
//		stop a VOICE sound by ID
//
//	Input:			nAudioID		audio Id number to be stop
//
//	Ouput:			none
//
///========================================================================

BOOL		voiceStop ( ULONG nAudioID )
{
	VOICE_SND*	pVoiceTblPtr;
	BOOL			error = TRUE;		// assume a failure
   
#ifdef SNDCHK
	TRACE("voiceStop( ID:%ld)\n",nAudioID ); 
#endif

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nAudioID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nAudioID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		error = FALSE;
		goto exit;
	}

	// kill off the timer event controlling this stream
#ifdef AUDIO_TIMER
	if ( pVoiceTblPtr->uTimerID )
	{
#ifdef TIMER_DEBUG
TRACE("VoiceStop() TimerID %d being killed\n", pVoiceTblPtr->uTimerID );
#endif
		timeKillEvent( pVoiceTblPtr->uTimerID );
	}
#endif
	pVoiceTblPtr->uTimerID = 0;

	// uninstall this stream
	if ( (pVoiceTblPtr->bFlags & SND_INSTALLED_FLAG) == SND_INSTALLED_FLAG )
		pVoiceTblPtr->bFlags &= ~SND_INSTALLED_FLAG;

	// stop the sound
	if ( (pVoiceTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// turn off the playing flag
		pVoiceTblPtr->bFlags &= ~SND_PLAYING_FLAG;

		// stop the stream
		if ( sndStop( pVoiceTblPtr->pDSBuffer ) != DS_OK )
			goto exit;	// error occurred
	}

	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		voiceStopSnd()
//
//	Description:
//		stop a VOICE sound by sndID
//
//	Input:			nSndID		snd Id number to be stop
//
//	Ouput:			none
//
///========================================================================

BOOL		voiceStopSnd( ULONG nSndID )
{
	VOICE_SND*	pVoiceTblPtr;
	BOOL			error = TRUE;		// assume a failure
   
#ifdef SNDCHK
	TRACE("voiceStopSnd( ID:%ld)\n",nSndID ); 
#endif

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nSndID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindSndID( nSndID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		error = FALSE;
		goto exit;
	}

	// kill off the timer event controlling this stream
#ifdef AUDIO_TIMER
	if ( pVoiceTblPtr->uTimerID )
	{
#ifdef TIMER_DEBUG
TRACE("VoiceStopSnd() TimerID %d being killed\n", pVoiceTblPtr->uTimerID );
#endif
		timeKillEvent( pVoiceTblPtr->uTimerID );
	}
#endif
	pVoiceTblPtr->uTimerID = 0;

	// uninstall this stream
	if ( (pVoiceTblPtr->bFlags & SND_INSTALLED_FLAG) == SND_INSTALLED_FLAG )
		pVoiceTblPtr->bFlags &= ~SND_INSTALLED_FLAG;

	// stop the sound
	if ( (pVoiceTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// turn off the playing flag
		pVoiceTblPtr->bFlags &= ~SND_PLAYING_FLAG;

		// stop the stream
		if ( sndStop( pVoiceTblPtr->pDSBuffer ) != DS_OK )
			goto exit;	// error occurred
	}

	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		voiceReset()
//
//	Description:
//		reset a VOICE sound by ID
//
//	Input:			nAudioID		audio Id number to be reset
//
//	Ouput:			none
//
///========================================================================

BOOL		voiceReset ( ULONG nAudioID )
{
	VOICE_SND*	pVoiceTblPtr;
	USHORT		bFlags;
	BOOL		error = TRUE;		// assume a failure
   
#ifdef SNDCHK
	TRACE("voiceStop( ID:%ld)\n",nAudioID ); 
#endif

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nAudioID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nAudioID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to stop a non-exitent nAudioID (%ld). [%s:%d]\n\n", 
			  nAudioID, __FILE__, __LINE__ );
		goto exit;
	}

	// kill off the timer event controlling this stream
#ifdef AUDIO_TIMER
	if ( pVoiceTblPtr->uTimerID )
	{
#ifdef TIMER_DEBUG
TRACE("VoiceReset() TimerID %d being killed\n", pVoiceTblPtr->uTimerID );
#endif

		timeKillEvent( pVoiceTblPtr->uTimerID );
	}
#endif
	pVoiceTblPtr->uTimerID = 0;

	// uninstall this stream
	if ( (pVoiceTblPtr->bFlags & SND_INSTALLED_FLAG) == SND_INSTALLED_FLAG )
		pVoiceTblPtr->bFlags &= ~SND_INSTALLED_FLAG;

	// stop the sound
	if ( (pVoiceTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// turn off the playing flag
		pVoiceTblPtr->bFlags &= ~SND_PLAYING_FLAG;

		// stop the stream
		if ( sndStop( pVoiceTblPtr->pDSBuffer ) != DS_OK )
			goto exit;	// error occurred
	}

	// now set the flags
	bFlags = SND_SFX_FLAG;
	if ( (pVoiceTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG )
		bFlags |= SND_LOOP_FLAG;
	pVoiceTblPtr->bFlags &= ~bFlags;

	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		voiceDelete()
//
//	Description:
//		Delete a VOICE sound by ID
//
//	Input:			nAudioID		audio Id number to delete
//
//	Ouput:			none
//
///========================================================================

BOOL		voiceDelete ( ULONG nAudioID )
{
	VOICE_SND*		pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
	BOOL			error        = TRUE;		// assume a failure

#if 0
	char*			pAudioName;
#endif

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	// make sure we have a useable ID
	if ( nAudioID == (ULONG)SND_NULL_SND_ID )
	{
		// no need to delete this
		error = FALSE;
		goto exit;
	}

#ifdef SND_DEBUG
TRACE("voiceDelete( A:%ld ) ", nAudioID );
#endif

#if 0
	pAudioName = audioIDname( nAudioID );
#endif

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nAudioID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// no need to worry about this
		error = FALSE;
		goto exit;
	}

	// lock this sound during deletion
	pVoiceTblPtr->bLock = TRUE;

	// free up this table entry
	if ( pVoiceTblPtr->pDSBuffer != NULL )
	{
		error = pVoiceTblPtr->pDSBuffer->Release();
		if ( error != DS_OK )
		{
			// report an error
			TRACE("ERROR:  failed to relase the DirectSoundbuffer (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
			goto exit;
		}
		pVoiceTblPtr->pDSBuffer = NULL;
	}

	// now delete the snd
	sndDelete( pVoiceTblPtr->nSndID );

	// re-initalize this entry
	//	pVoiceTblPtr->bLock				= FALSE;		// CLEAR THIS AT END
	pVoiceTblPtr->nAudioID			 = SND_NULL_SND_ID;	// stream sound identifier
	pVoiceTblPtr->nSndID			 = SND_NULL_SND_ID;	// sound identifier
	pVoiceTblPtr->bFlags			 = SND_CLEAR_FLAG;	// Boolean Flag fields
	pVoiceTblPtr->pWaveForm          = NULL;		// .wave info
	pVoiceTblPtr->nSndStart          = 0;			// index into .snd or .wav file to read from
	pVoiceTblPtr->nSndOffset         = 0;			// offset into file to reach sound chunk
													// this is filled at load time.
	pVoiceTblPtr->nSndSize           = 0;			// size of raw data
	pVoiceTblPtr->uTimerID           = 0;            // play interrupt timer ID
	pVoiceTblPtr->dwBufferSize       = 0;            // Size of the entire buffer
	pVoiceTblPtr->dwBufferSegSize    = 0;            // Size of one buffer segment
	pVoiceTblPtr->dwNextWriteOffset  = 0;            // Offset to next buffer segment
	pVoiceTblPtr->dwPlayLast         = 0;            // Used with above to show prog
	pVoiceTblPtr->dwProgress         = 0;            // Used with above to show prog
	pVoiceTblPtr->nRemainingBytes    = 0;			// Segments 'til timer shutdown
	pVoiceTblPtr->nSndLink           = SND_NULL_SND_ID;	// Link to another voice ID

	// if we got here we we're successful
	--VOICEsoundsActive;
	error = FALSE;

#if 0
	TRACE("voiceDelete( A:%s-A:%ld )\n", pAudioName, nAudioID );
#endif

exit:
	// un-lock this sound during deletion
	if ( pVoiceTblPtr != (VOICE_SND*)SND_NULL_SND_PTR )
		pVoiceTblPtr->bLock = FALSE;

#if 0
	if ( error )
		TRACE("voiceDelete( A:%s-A:%ld ) ERROR\n", pAudioName, nAudioID );
#endif

	return( error );
}

///========================================================================
//	Function:		voiceDeleteSnd()
//
//	Description:
//		Delete a VOICE sound by SndID
//
//	Input:			nAudioID		audio Id number to delete
//
//	Ouput:			none
//
///========================================================================

BOOL		voiceDeleteSnd( ULONG nSndID )
{
	VOICE_SND*		pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
	BOOL			error        = TRUE;		// assume a failure

#if 0
	char*			pAudioName;
#endif

	if ( !VOICEenabled )
	{
		// no need to delete this
		error = FALSE;
		goto exit;
	}

	// make sure we have a useable ID
	if ( nSndID == (ULONG)SND_NULL_SND_ID )
	{
		// no need to delete this
		error = FALSE;
		goto exit;
	}

#if 0
	pAudioName = audioSndIDname( nSndID );
#endif

	// find the sound in the table
	pVoiceTblPtr = voiceFindSndID( nSndID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// no need to worry about this
		error = FALSE;
		goto exit;
	}

	// lock this sound during deletion
	pVoiceTblPtr->bLock = TRUE;

	// kill off the timer event controlling this stream
#ifdef AUDIO_TIMER
	if ( pVoiceTblPtr->uTimerID )
	{
#ifdef TIMER_DEBUG
TRACE("voiceDeleteSnd() TimerID %d being killed\n", pVoiceTblPtr->uTimerID );
#endif

		timeKillEvent( pVoiceTblPtr->uTimerID );
	}
#endif
	pVoiceTblPtr->uTimerID = 0;

	// uninstall this stream
	if ( (pVoiceTblPtr->bFlags & SND_INSTALLED_FLAG) == SND_INSTALLED_FLAG )
		pVoiceTblPtr->bFlags &= ~SND_INSTALLED_FLAG;

	// stop the sound
	if ( (pVoiceTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// turn off the playing flag
		pVoiceTblPtr->bFlags &= ~SND_PLAYING_FLAG;

		// stop the stream
		if ( sndStop( pVoiceTblPtr->pDSBuffer ) != DS_OK )
			goto exit;	// error occurred
	}

	// free up this table entry
	if ( pVoiceTblPtr->pDSBuffer != NULL )
	{
		error = pVoiceTblPtr->pDSBuffer->Release();
		if ( error != DS_OK )
		{
			// report an error
			TRACE("ERROR:  failed to relase the DirectSoundbuffer (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
			goto exit;
		}
		pVoiceTblPtr->pDSBuffer = NULL;
	}

	// re-initalize this entry
	//	pVoiceTblPtr->bLock				= FALSE;		// CLEAR THIS AT END
	pVoiceTblPtr->nAudioID			 = SND_NULL_SND_ID;	// voice sound identifier
	pVoiceTblPtr->nSndID			 = SND_NULL_SND_ID;	// sound identifier
	pVoiceTblPtr->bFlags			 = SND_CLEAR_FLAG;	// Boolean Flag fields
	pVoiceTblPtr->pWaveForm          = NULL;		// .wave info
	pVoiceTblPtr->nSndStart          = 0;			// index into .snd or .wav file to read from
	pVoiceTblPtr->nSndOffset         = 0;			// offset into file to reach sound chunk
													// this is filled at load time.
	pVoiceTblPtr->nSndSize           = 0;			// size of raw data
	pVoiceTblPtr->uTimerID           = 0;            // play interrupt timer ID
	pVoiceTblPtr->dwBufferSize       = 0;            // Size of the entire buffer
	pVoiceTblPtr->dwBufferSegSize    = 0;            // Size of one buffer segment
	pVoiceTblPtr->dwNextWriteOffset  = 0;            // Offset to next buffer segment
	pVoiceTblPtr->dwPlayLast         = 0;            // Used with above to show prog
	pVoiceTblPtr->dwProgress         = 0;            // Used with above to show prog
	pVoiceTblPtr->nRemainingBytes    = 0;			// Segments 'til timer shutdown
	pVoiceTblPtr->nSndLink           = STRM_NULL_SND_ID;// Link to another voice ID

	// if we got here we we're successful
	--VOICEsoundsActive;
	error = FALSE;

#if 0
	TRACE("voiceDeleteSnd( A:%s-S:%ld )\n", pAudioName, nSndID );
#endif

#ifdef SND_DEBUG
TRACE("deleted\n" );
TRACE( "VOICEsoundsActive = %d   Decremented\n", VOICEsoundsActive );
#endif

exit:
	// un-lock this sound
	if ( pVoiceTblPtr != (VOICE_SND*)SND_NULL_SND_PTR )
		pVoiceTblPtr->bLock = FALSE;

#if 0
	if ( error )
		TRACE("voiceDeleteSnd( A:%s-S:%ld ) ERROR\n", pAudioName, nSndID );
#endif

	return( error );
}

///========================================================================
//	Function:		voiceClose()
//
//	Description:
//		Close down an VOICE .snd file
//
//	Input:			nFileID			file Id to close
//
//	Ouput:			none
//
///========================================================================

void		voiceClose ( unsigned nFileID )
{

	if ( !VOICEenabled )
		return;

	sndDeleteFile( nFileID );
	pVOICEfile = NULL;
}


///========================================================================
//	Function:		voiceGetFrequency()
//
//	Description:
// 		Get the VOICE sound frequency level (effect pitch)
//
//	Input:			nVoiceID			sound Id number to retrieve pan from
//
//	Ouput:			nFrequency		current VOICE frequency setting
//
///========================================================================

LONG		voiceGetFrequency ( ULONG nVoiceID )
{
	LONG			nFrequency;
	VOICE_SND*	pVoiceTblPtr;

	if ( !VOICEenabled )
		return( 0 );

	if ( nVoiceID == SND_NULL_SND_ID )
		return( 0 );

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nVoiceID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		nFrequency = 0;
	else				// Get the FREQUENCY value
	if ( sndGetFrequency( pVoiceTblPtr->pDSBuffer, &nFrequency ) )
		nFrequency = 0;
	   
	return( nFrequency );
}


///========================================================================
//	Function:		voiceSetFrequency()
//
//	Description:
// 		Set the VOICE sound requency level (effect pitch)
//
//	Input:			nVoiceID			sound Id number to retrieve pan from
//					nFrequency		volume setting to apply
//
//	Ouput:			none
//
///========================================================================

BOOL		voiceSetFrequency ( ULONG nVoiceID, LONG nFrequency )
{
	VOICE_SND*	pVoiceTblPtr;
	BOOL		error = TRUE;		// assume failed

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nVoiceID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nVoiceID );
   if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		goto exit;

	// set the Frequency value
	if ( sndSetFrequency( pVoiceTblPtr->pDSBuffer, nFrequency ) )
		goto exit;
	   
	// If we made it here we did everything ok
	error = FALSE;
exit:
	return( error );
}


///========================================================================
//	Function:		voiceGetVolume()
//
//	Description:
// 		Get the VOICE sound volume levels:
//
//	Input:			nVoiceID			sound Id number to retrieve pan from
//
//	Ouput:			nVolume			current VOICE volume setting
//
///========================================================================

LONG		voiceGetVolume ( ULONG nVoiceID ) 
{
	LONG		nVolume;
	VOICE_SND*	pVoiceTblPtr;

	if ( !VOICEenabled )
		return( 0 );

	if ( nVoiceID == SND_NULL_SND_ID )
		return( 0 );

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nVoiceID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		nVolume = 0;
	else				// Get the VOLUME value
	if ( sndGetVolume( pVoiceTblPtr->pDSBuffer, &nVolume ) )
		nVolume = 0;

	return( nVolume );
}


///========================================================================
//	Function:		voiceSetVolume()
//
//	Description:
// 		Set the VOICE sound volume levels:
//
//	Input:			nSndID			sound Id number to retrieve pan from
//					nVolume			volume setting to apply
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL		voiceSetVolume ( ULONG nSndID, LONG nVolume )
{
	VOICE_SND*	pVoiceTblPtr;
	BOOL		error = TRUE;		// assume failed

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nSndID == SND_NULL_SND_ID )
		return( 0 );

	// find the sound in the table
	pVoiceTblPtr = voiceFindSndID( nSndID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		goto exit;

	// set the Volume value
	if ( sndSetVolume( pVoiceTblPtr->pDSBuffer, nVolume ) )
		goto exit;
	   
	// If we made it here we did everything ok
	error = FALSE;
exit:
	return( error );
}


///========================================================================
//	Function:		voiceGetPan()
//
//	Description:
// 		Get the VOICE sound pan level
//
//	Input:			nVoiceID			sound Id number to retrieve pan from
//
//	Ouput:			nPan			current VOICE pan setting
//
///========================================================================

LONG		voiceGetPan ( ULONG nVoiceID )
{
	LONG		nPan;
	VOICE_SND*	pVoiceTblPtr;

	if ( !VOICEenabled )
		return( 0 );

	if ( nVoiceID == SND_NULL_SND_ID )
		return( 0 );

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nVoiceID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		nPan = 0;
	else			// Get the PAN value
	if ( sndGetPan( pVoiceTblPtr->pDSBuffer, &nPan ) )
		nPan = 0;
	   
	return( nPan );
}


///========================================================================
//	Function:		voiceSetPan()
//
//	Description:
// 		Set the VOICE sound pan level
//
//	Input:			nVoiceID			sound Id number to apply pan to
//					nPan			pan setting to apply
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL		voiceSetPan ( ULONG nVoiceID, LONG nPan )
{
	VOICE_SND*	pVoiceTblPtr;
	BOOL		error = TRUE;		// assume failed

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nVoiceID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pVoiceTblPtr = voiceFindID( nVoiceID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		goto exit;

	// set the PAN value
	if ( sndSetPan( pVoiceTblPtr->pDSBuffer, nPan ) )
		goto exit;
	   
	// If we made it here we did everything ok
	error = FALSE;
exit:
	return( error );
}


///========================================================================
//	Function:		voiceMonitor()
//
//	Description:
//		Monitor STRM processing, updating the playback buffer at regular
//		intervals.
//
//	Input:			uTimerID		timer Id triggering this processing
//					uMessage		
//					dwUser			
//					dwData1			potential data for processing
//					dwData2			secondary potential data for processing
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

#ifdef AUDIO_TIMER
void CALLBACK voiceMonitor ( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 )
#else
void		  voiceMonitor ( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 )
#endif
{
	VOICE_SND*			pVoiceTblPtr;

	// make sure we have sounds that are active
	if ( !VOICEenabled )
		goto exit;

	if ( !VOICEsoundsActive )
		goto exit;

	if ( !uTimerID )
		goto exit;

	// find the sound in the table
	pVoiceTblPtr = voiceFindTimerID( uTimerID );
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
			goto exit;

	// are we already processing?
	if ( (pVoiceTblPtr->bFlags & SND_TIMER_FLAG) == SND_TIMER_FLAG )
		goto exit;
	else

	// check to see if this sound is locked
	if ( pVoiceTblPtr->bLock )
		goto cleanUp;

	if ( pVoiceTblPtr->nAudioID == SND_NULL_SND_ID )
	{
#ifdef AUDIO_TIMER
		if ( pVoiceTblPtr->uTimerID )
		{
#ifdef TIMER_DEBUG
TRACE("voiceMonitor() TimerID %d being killed\n", pVoiceTblPtr->uTimerID );
#endif

			timeKillEvent( pVoiceTblPtr->uTimerID );
		}
#endif
		pVoiceTblPtr->uTimerID = 0;
		pVoiceTblPtr->bFlags |= SND_DONE_FLAG;
		goto cleanUp;
	}

#ifdef DBG_AUDIO
	char*	pAudioName;
	pAudioName = audioIDname( pVoiceTblPtr->nAudioID );
	if ( strcmp( pAudioName, "MENDOWN" ) == 0 )
		TRACE( "voiceMonitor( %s )\n", audioIDname( pVoiceTblPtr->nAudioID ) );
#endif

	// from this point on, we can't be interrupted
	pVoiceTblPtr->bFlags |= SND_TIMER_FLAG;
	goto exit;

cleanUp:

	// signify that we are no longer occupying the timer interrupt
	pVoiceTblPtr->bFlags &= ~SND_TIMER_FLAG;

exit:
	return;
}

///========================================================================
//	Function:		voiceUpdate()
//
//	Description:
//		Update VOICE processing, updating the playback buffer at regular
//		intervals.
//
//	Input:			pVoiceTblPtr	voice triggering this processing
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

void	voiceUpdate ( VOICE_SND* pVoiceTblPtr )
{
	VOICE_SND*			pVoiceLinkPtr;
	LPDIRECTSOUNDBUFFER pDSBuffer;
	DWORD				nPlayPos;
	DWORD				nWritePos;
	DWORD				nPlayLength;
	LPBYTE				pDSBuffData1;
	LPBYTE				pDSBuffData2;
	DWORD				dwDataLen1;
	DWORD				dwDataLen2;
	BOOL				error;

	// get the play buffer for manipulation
	pDSBuffer = pVoiceTblPtr->pDSBuffer;
	if ( pDSBuffer == NULL )
		goto cleanUp;

#ifdef DBG_AUDIO
	char*	pAudioName;
	pAudioName = audioIDname( pVoiceTblPtr->nAudioID );
	if ( strcmp( pAudioName, "MENDOWN" ) == 0 )
		TRACE( "voiceMonitor( %s )\n", audioIDname( pVoiceTblPtr->nAudioID ) );
#endif

	// Get the current position in the play buffer
	pDSBuffer->GetCurrentPosition( &nPlayPos, &nWritePos );

#if 0
	if (dwPlayPos < wiWave.dwLastPos)
	{
		dwPlayed = wiWave.dwBufferSize - wiWave.dwLastPos + dwPlayPos;
	}
	else
	{
		dwPlayed = dwPlayPos - wiWave.dwLastPos;
	}
#endif

	// calculate writeable bytes
//	if ( nPlayPos < pVoiceTblPtr->dwNextWriteOffset )
	if ( nPlayPos < pVoiceTblPtr->dwPlayLast )
	{
		// calculate how many writable bytes there are behind the play cursor
//		nPlayLength = (nPlayPos + pVoiceTblPtr->dwBufferSize - pVoiceTblPtr->dwNextWriteOffset);
		nPlayLength = (pVoiceTblPtr->dwBufferSize - pVoiceTblPtr->dwPlayLast + nPlayPos);
	}
	else
	{
		// calculate how many writable bytes there are after the play cursor
//		nPlayLength = (nPlayPos - pVoiceTblPtr->dwNextWriteOffset);
		nPlayLength = (nPlayPos - pVoiceTblPtr->dwPlayLast);
	}
	pVoiceTblPtr->dwProgress += nPlayLength;
	pVoiceTblPtr->dwPlayLast = nPlayPos;

#ifdef DBG_AUDIO
	pAudioName = audioIDname( pVoiceTblPtr->nAudioID );
	TRACE("\n\nnPlayPos = %ld  nPlayLength = %ld dwNextWriteOffset = %ld\n",
		nPlayPos, nPlayLength, pVoiceTblPtr->dwNextWriteOffset );
#endif

	// if the play cursor is at the same spot as the last call, there are two possibilities.
	// The first is that we were called extremely late and happened to land on an integer
	// number of complete buffer cycles. This is not very likely. The other is that the
	// play cursor didn't move. Since we're oversampling, this is very likely. In this
	// case, we should bail.
	if ( pVoiceTblPtr->dwNextWriteOffset == nPlayPos )
	{
		// can't write yet...
#ifdef DBG_AUDIO
		TRACE( "can't write yet...(%ld==%ld)\n", pVoiceTblPtr->dwNextWriteOffset, nPlayPos);
//		voiceDump( pVoiceTblPtr );
#endif
		goto cleanUp;
	}

	// Have we found the end of the stream and passed the buffer end?
	if ( ((pVoiceTblPtr->bFlags & SND_EOS_FLAG) == SND_EOS_FLAG ) &&
		 !(pVoiceTblPtr->nRemainingBytes)
	   )
	{
		// see if we're done playing
		if ( (pVoiceTblPtr->bFlags & SND_DONE_FLAG) != SND_DONE_FLAG )
		{
			if ( voiceStopSnd( pVoiceTblPtr->nSndID ) )
			{
				// report an error
				TRACE("ERROR: failed to stop voice ID (%ld:%ld). [%s:%d]\n\n", 
					   pVoiceTblPtr->nAudioID, pVoiceTblPtr->nSndID, __FILE__, __LINE__ );

				// make sure the flags for this stream are clear
				pVoiceTblPtr->bFlags = SND_CLEAR_FLAG;
				goto cleanUp;
			}

			// check to see if this is a looping stream
			if ( ((pVoiceTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG) &&
				 ((pVoiceTblPtr->bFlags & SND_DELETE_FLAG) != SND_DELETE_FLAG) )
			{
				if ( voiceCueSnd( pVoiceTblPtr->nSndID ) )
				{
					// report an error
					TRACE("ERROR: failed to cue up (sndID: %ld). [%s:%d]\n\n", 
						   pVoiceTblPtr->nSndID, __FILE__, __LINE__ );

					// make sure the flags for this stream are clear
					pVoiceTblPtr->bFlags = SND_CLEAR_FLAG;
					goto cleanUp;
				}

				if ( voicePlaySnd( pVoiceTblPtr->nSndID ) )
				{
					// report an error
					TRACE("ERROR: failed to startup link (sndID: %ld). [%s:%d]\n\n", 
						   pVoiceTblPtr->nSndID, __FILE__, __LINE__ );

					// make sure the flags for this stream are clear
					pVoiceTblPtr->bFlags = SND_CLEAR_FLAG;
					goto cleanUp;
				}

				// clear the cue'd flag
				pVoiceTblPtr->bFlags &= ~SND_CUED_FLAG;
			}
			else
			{
				pVoiceTblPtr->bFlags |= SND_DONE_FLAG;

				// check to see if this stream is linked to another
				if ( pVoiceTblPtr->nSndLink != SND_NULL_SND_ID )
				{
					// start up the next link
					pVoiceLinkPtr = voiceFindID(pVoiceTblPtr->nSndLink);
					if ( voiceCueSnd( pVoiceLinkPtr->nSndID ) )
					{
						// report an error
						TRACE("ERROR: failed to cue up (sndID: %ld). [%s:%d]\n\n", 
							   pVoiceLinkPtr->nSndID, __FILE__, __LINE__ );

						// make sure the flags for this stream are clear
						pVoiceLinkPtr->bFlags = SND_CLEAR_FLAG;
						goto cleanUp;
					}

					if ( voicePlaySnd( pVoiceLinkPtr->nSndID ) )
					{
						// report an error
						TRACE("ERROR: failed to startup link (sndID: %ld). [%s:%d]\n\n", 
							   pVoiceLinkPtr->nSndID, __FILE__, __LINE__ );

						// make sure the flags for this stream are clear
						pVoiceLinkPtr->bFlags = SND_CLEAR_FLAG;
						goto cleanUp;
					}

					// clear the cue'd flag
					pVoiceLinkPtr->bFlags &= ~SND_CUED_FLAG;
				}
			}
		}

		goto cleanUp;
	}

	// If we've found the end of the stream, then we've finished reading in
	// the file. But we need to wait until the buffer's play cursor passes
	// the point we were at when we found out we were done reading.
	if ( ((pVoiceTblPtr->bFlags & SND_EOS_FLAG) == SND_EOS_FLAG ) &&
		 (pVoiceTblPtr->nRemainingBytes)
	   )
	{
#ifdef	SNDCHK
		TRACE("...EOS and %d remaining bytes...\n",
				pVoiceTblPtr->nRemainingBytes );
#endif

		// reduce the number of bytes we have to wait until we can safely
		// terminate the timer associated with this stream.
		if ( nPlayLength > pVoiceTblPtr->nRemainingBytes )
			pVoiceTblPtr->nRemainingBytes = 0;
		else
			pVoiceTblPtr->nRemainingBytes -= nPlayLength;

		error = pDSBuffer->Lock( pVoiceTblPtr->dwNextWriteOffset,
								 nPlayLength,
								 (LPLPVOID)&pDSBuffData1, &dwDataLen1,
								 (LPLPVOID)&pDSBuffData2, &dwDataLen2,
								 0
							   );
		if (error != DS_OK)
		{
			// report an error
			TRACE("ERROR: failed DSbuffer lock (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
			goto cleanUp;
		}

		// silence out both parts of the locked buffer
		// if the sample was 8 bits fill with 128
		if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 8)
			memset( pDSBuffData1, 128, dwDataLen1);
		else
		// if the sample was 16 bits fill with 0
		if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 16)
			memset( pDSBuffData1, 0, dwDataLen1);

		if ( dwDataLen1 && dwDataLen2 )
		{
			// if the sample was 8 bits fill with 128
			if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 8)
				memset( pDSBuffData2, 128, dwDataLen2);
			else
			// if the sample was 16 bits fill with 0
			if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 16)
				memset( pDSBuffData2, 0, dwDataLen2);
		}

		// unlock the sound buffer
		error = pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
								   (LPVOID)pDSBuffData2, dwDataLen2
								 );
		if ( error != DS_OK)
		{
			// report an error
			TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
			goto cleanUp;
		}

		// the following code is from the end of the is routine. We need to keep
		// zeroing out buffer segments while we're waiting for the play cursor to
		// catch up to the end of the wave data.
		pVoiceTblPtr->dwNextWriteOffset += nPlayLength;
		if (pVoiceTblPtr->dwNextWriteOffset >= pVoiceTblPtr->dwBufferSize)
			pVoiceTblPtr->dwNextWriteOffset -= pVoiceTblPtr->dwBufferSize;
//		pVoiceTblPtr->dwProgress += nPlayLength;

		goto cleanUp;
	}

	// now lock the segment of memory that is behind the play cursor
	error = pDSBuffer->Lock( pVoiceTblPtr->dwNextWriteOffset,
							 nPlayLength,
							 (LPLPVOID)&pDSBuffData1, &dwDataLen1,
							 (LPLPVOID)&pDSBuffData2, &dwDataLen2,
							 0
						   );
	if (error != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer lock (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto cleanUp;
	}

	// read in the next segment of data into the buffer, that is if the
	// is is still playing.
	if ( dwDataLen1 && ((pVoiceTblPtr->bFlags & SND_DONE_FLAG) != SND_DONE_FLAG) )
		voiceLoadNextData( (VOICE_SND*)pVoiceTblPtr, (BYTE*)pDSBuffData1, dwDataLen1, nPlayPos );
	else
	if ( dwDataLen1 && ((pVoiceTblPtr->bFlags & SND_DONE_FLAG) == SND_DONE_FLAG) )
	{
		// The done playing flag is set before the end of the wave file is
		// encountered. It tells us to cut this stream off and play nothing
		// in case it takes the caller a couple of interrupts to shut off
		// the timer.

		//Set the appropriate silence value
		// if the sample was 8 bits fill with 128
		if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 8)
			memset( pDSBuffData1, 128, dwDataLen1);
		else
		// if the sample was 16 bits fill with 0
		if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 16)
			memset( pDSBuffData1, 0, dwDataLen1);

	}

	// read in the next segment of data into the buffer, that is if the
	// is is still playing.
	if ( dwDataLen2 && ((pVoiceTblPtr->bFlags & SND_DONE_FLAG) != SND_DONE_FLAG) )
	{
		ASSERT( pVoiceTblPtr->nAudioID != SND_NULL_SND_ID );
		// load in the next buffer's worth of data
		voiceLoadNextData( (VOICE_SND*)pVoiceTblPtr, (BYTE*)pDSBuffData2, dwDataLen2, nPlayPos );
	}
	else
	if ( dwDataLen2 && ((pVoiceTblPtr->bFlags & SND_DONE_FLAG) == SND_DONE_FLAG) )
	{
		// The done playing flag is set before the end of the wave file is
		// encountered. It tells us to cut this stream off and play nothing
		// in case it takes the caller a couple of interrupts to shut off
		// the timer.

		//Set the appropriate silence value
		// if the sample was 8 bits fill with 128
		if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 8)
			memset( pDSBuffData2, 128, dwDataLen2);
		else
		// if the sample was 16 bits fill with 0
		if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 16)
			memset( pDSBuffData2, 0, dwDataLen2);
	}

	// Unlock the DS buffer
	pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
					   (LPVOID)pDSBuffData2, dwDataLen2
					 );

	// update the next write positions
	pVoiceTblPtr->dwNextWriteOffset += nPlayLength;
	if (pVoiceTblPtr->dwNextWriteOffset >= pVoiceTblPtr->dwBufferSize)
		pVoiceTblPtr->dwNextWriteOffset -= pVoiceTblPtr->dwBufferSize;

cleanUp:

	// signify that we are no longer occupying the timer interrupt
	pVoiceTblPtr->bFlags &= ~SND_TIMER_FLAG;

	// if this stream is done, set its volume to off
	if ( (pVoiceTblPtr->bFlags & SND_DONE_FLAG) == SND_DONE_FLAG )
		SndSetVolumePercent( pVoiceTblPtr->nSndID, 0, FALSE );

	return;
}

///========================================================================
//	Function:		voiceLoadData()
//
//	Description:
//		read in a buffer segment's worth of data
//
//	Input:			pVoiceTblPtr		VOICE sound processing
//					nMaxLen			max buffer segment length
//					
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL	voiceLoadData ( VOICE_SND* pVoiceTblPtr, BYTE* pDSBuffData, DWORD nMaxLen )
{
	SND*				pSndPtr;
	FILE*				pFilePtr;
	DWORD				dwLen;
	DWORD				dwReadLen;
	DWORD				dwLeftToRead;
	int					nSndIdx;
	unsigned			status;
	BOOL				error = TRUE;		// assume failure

#ifdef	SNDCHK
	TRACE("voiceLoadData( ID:%ld )...\n", pVoiceTblPtr->nSndID );
#endif

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( pVoiceTblPtr->nSndID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// there might be more than one sound in the file, make sure we
	// we don't read past the end of the this particular sound
	if ( (LONG)nMaxLen > pVoiceTblPtr->nSndSize )
		dwReadLen = pVoiceTblPtr->nSndSize;
	else
		dwReadLen = nMaxLen;

	// get the sound data
	status = sndFindSndID( pVoiceTblPtr->nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, pVoiceTblPtr->nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// retrieve the file pointer
	pFilePtr = pSndPtr->wavSnd.pSndFile;

	if ( fseek( pFilePtr, pVoiceTblPtr->nSndStart, SEEK_SET) )
	{
		// report an error
		TRACE("ERROR: fseek failure. [%s:%d]\n", __FILE__, __LINE__ );
		goto exit;
	}

	dwLen = (long)fread( (void*)pDSBuffData, 1, dwReadLen, pFilePtr );

	// see if the new data will fit into the buffer
	if ( (long)dwLen < (long)nMaxLen )
	{
		// see if we're doing any looping
		if ( (pVoiceTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG )
		{
			// if the file is shorter than the buffer and we're looping. we need to
			// read the file in again so that we don't get a block of silence before
			// the timer loops playback.
#if 1
			dwLeftToRead = dwLen;	// from previous call above.
			while (dwLeftToRead < nMaxLen)
			{	// this will keep reading in until the buffer is full. For very short files.
				if ( fseek( pFilePtr, pVoiceTblPtr->nSndStart, SEEK_SET) )
				{
					// report an error
					TRACE("ERROR: fseek failure. [%s:%d]\n", 
						__FILE__, __LINE__ );
					goto exit;
				}
				dwLen = (long)fread( (void*)(pDSBuffData+dwLeftToRead), 1, dwReadLen, pFilePtr );
				dwLeftToRead += dwLen;
			} // while
#else
			BYTE*	pTmpData;

			dwLeftToRead = nMaxLen;
			pTmpData     = pDSBuffData;
			do
			{
				// Continue decrementing our count and moving our temp
				// pointer forward until we've read the file enough times
				// to fill the buffer.  NOTE: It's probably not efficient
				// to bother with the overhead of streaming a file that's
				// not at least as large as the buffer...
				pTmpData      += dwLen;
				dwLeftToRead  -= dwLen;
				if ( fseek( pFilePtr, pVoiceTblPtr->nSndStart, SEEK_SET) )
				{
					// report an error
					TRACE("ERROR: fseek failure. [%s:%d]\n", 
						__FILE__, __LINE__ );
					goto exit;
				}
				dwLen = (long)fread( (void*)pTmpData, 1, dwReadLen, pFilePtr );
//			} while( dwLen && (dwLen < dwLeftToRead) );
			} while( (dwLen < dwLeftToRead) );
#endif
		}
		else
		{
			// zero out the rest of this block
			// if the sample was 8 bits fill with 128
			if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 8)
				memset( (pDSBuffData+dwLen), 128, (nMaxLen - dwLen));
			else
			// if the sample was 16 bits fill with 0
			if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 16)
				memset( (pDSBuffData+dwLen), 0, (nMaxLen - dwLen));

			// we have the end of the stream, enable play completion detection
			// code at the beginning of the next call.
			pVoiceTblPtr->bFlags |= SND_EOS_FLAG;

			// here the number of bytes remaining equals the data readin
			pVoiceTblPtr->nRemainingBytes = dwReadLen;
		}
	}

	// save this location in the file incase we need to reload
	pVoiceTblPtr->nSndOffset = ftell( pFilePtr );

	// set up the next write position
	pVoiceTblPtr->dwNextWriteOffset += dwReadLen;
	if (pVoiceTblPtr->dwNextWriteOffset >= pVoiceTblPtr->dwBufferSize)
		pVoiceTblPtr->dwNextWriteOffset -= pVoiceTblPtr->dwBufferSize;

	// mark this stream as cue'd
	pVoiceTblPtr->bFlags |= SND_CUED_FLAG;

	// made it here, we were successful
	error = FALSE;
exit:

	return( error );
}


///========================================================================
//	Function:		voiceLoadNextData()
//
//	Description:
//		read in a buffer segment's worth of data
//
//	Input:			pVoiceTblPtr		VOICE sound processing
//					pDSBuffData		where to load data
//					nMaxLen			max buffer segment length
//					nPlayPos		play cursor position in buffer
//					
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL	voiceLoadNextData ( VOICE_SND* pVoiceTblPtr, BYTE* pDSBuffData, DWORD nMaxLen, DWORD nPlayPos )
{
	SND*				pSndPtr;
	FILE*				pFilePtr;
	DWORD				dwLen;
	DWORD				dwReadLen;
	DWORD				dwLeftToRead;
	int					nSndIdx;
	unsigned			status;
	BOOL				error = TRUE;		// assume failure

#ifdef	SNDCHK
	TRACE("voiceLoadNextData( ID:%ld )...\n", pVoiceTblPtr->nSndID );
#endif

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( pVoiceTblPtr->nSndID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// there might be more than one sound in the file, make sure we
	// we don't read past the end of the this particular sound
	dwLen = pVoiceTblPtr->nSndSize - (pVoiceTblPtr->nSndOffset - pVoiceTblPtr->nSndStart);
	if ( (long)nMaxLen > (long)dwLen )
		dwReadLen = dwLen;
	else
		dwReadLen = nMaxLen;

#ifdef	SNDCHK
	TRACE("voiceLoadNextData( ID:%ld )...\n", pVoiceTblPtr->nSndID );
	TRACE("                 MaxLen  = %ld\n", nMaxLen );
	TRACE("                 ReadLen = %ld\n", dwReadLen );
#endif

	// get the sound data
	status = sndFindSndID( pVoiceTblPtr->nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, pVoiceTblPtr->nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// retrieve the file pointer
	pFilePtr = pSndPtr->wavSnd.pSndFile;

	// remember that there might be more than one stream in the data file
	// cross check by comparing the existing offset with the size and start
	// offset. Otherwise look for a true end of file.
	if ( (pVoiceTblPtr->bFlags & SND_EOS_FLAG) != SND_EOS_FLAG )
	{
		if ( pVoiceTblPtr->nSndOffset >= (pVoiceTblPtr->nSndStart + pVoiceTblPtr->nSndSize) )
		{
#ifdef	SNDCHK
TRACE("...nSndSize exceeded...\n" );
#endif
			// zero out the rest of this block
			// if the sample was 8 bits fill with 128
			if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 8)
				memset( pDSBuffData, 128, nMaxLen);
			else
			// if the sample was 16 bits fill with 0
			if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 16)
				memset( pDSBuffData, 0, nMaxLen);

			// first set the EOS flag so we can terminate loading
			pVoiceTblPtr->bFlags |= SND_EOS_FLAG;

			// handle wrapping in this circular buffer
			if ( nPlayPos > pVoiceTblPtr->dwNextWriteOffset )
			{
				pVoiceTblPtr->nRemainingBytes = (pVoiceTblPtr->dwNextWriteOffset
												+ pVoiceTblPtr->dwBufferSize
												- nPlayPos
											   );
			}
			else
			{
				pVoiceTblPtr->nRemainingBytes = (pVoiceTblPtr->dwNextWriteOffset
												- nPlayPos
											   );
			}

			goto cleanup;
		}
	}

	// find the next read point in the stream data
	if ( fseek( pFilePtr, pVoiceTblPtr->nSndOffset, SEEK_SET) )
	{
		// report an error
		TRACE("ERROR: fseek failure. [%s:%d]\n", __FILE__, __LINE__ );
		goto exit;
	}
	dwLen = (long)fread( (void*)pDSBuffData, 1, dwReadLen, pFilePtr );

	// see if the new data will fit into the buffer
	if ( (long)dwLen < (long)nMaxLen )
	{
#ifdef	SNDCHK
TRACE("...dwLen < nMaxLen...\n" );
#endif
		// see if we're doing any looping
		if ( (pVoiceTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG )
		{
#ifdef	SNDCHK
TRACE("...filling buffer (looping)...\n" );
#endif

			// if the file is shorter than the buffer and we're looping. we need to
			// read the file in again so that we don't get a block of silence before
			// the timer loops playback.
#if 1
			dwLeftToRead = dwLen;	// from previous call above.
			while (dwLeftToRead < nMaxLen)
			{	// this will keep reading in until the buffer is full. For very short files.
				if ( fseek( pFilePtr, pVoiceTblPtr->nSndOffset, SEEK_SET) )
				{
					// report an error
					TRACE("ERROR: fseek failure. [%s:%d]\n", 
						__FILE__, __LINE__ );
					goto exit;
				}
				dwLen = (long)fread( (void*)(pDSBuffData+dwLeftToRead), 1, dwReadLen, pFilePtr );
				dwLeftToRead += dwLen;
			} // while
#else
			BYTE*	pTmpData;

			dwLeftToRead = nMaxLen;
			pTmpData     = pDSBuffData;
			do
			{
				// Continue decrementing our count and moving our temp
				// pointer forward until we've read the file enough times
				// to fill the buffer.  NOTE: It's probably not efficient
				// to bother with the overhead of streaming a file that's
				// not at least as large as the buffer...
				pTmpData      += dwLen;
				dwLeftToRead  -= dwLen;
				if ( fseek( pFilePtr, pVoiceTblPtr->nSndOffset, SEEK_SET) )
				{
					// report an error
					TRACE("ERROR: fseek failure. [%s:%d]\n", 
						__FILE__, __LINE__ );
					goto exit;
				}
				dwLen = (long)fread( (void*)pTmpData, 1, dwReadLen, pFilePtr );
			} while( dwLen && (dwLen < dwLeftToRead) );
#endif
		}
		else
		{
#ifdef	SNDCHK
TRACE("...EOS encountered...\n" );
#endif

			// zero out the rest of this block
			// if the sample was 8 bits fill with 128
			if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 8)
				memset( (pDSBuffData+dwLen), 128, (UINT)(nMaxLen - dwLen));
			else
			// if the sample was 16 bits fill with 0
			if (pVoiceTblPtr->pWaveForm->wBitsPerSample == 16)
				memset( (pDSBuffData+dwLen), 0, (UINT)(nMaxLen - dwLen));

			// we have the end of the stream, enable play completion detection
			// code at the beginning of the next call.
			pVoiceTblPtr->bFlags |= SND_EOS_FLAG;

			// handle wrapping in this circular buffer
			if ( nPlayPos > pVoiceTblPtr->dwNextWriteOffset )
			{
				pVoiceTblPtr->nRemainingBytes = (pVoiceTblPtr->dwNextWriteOffset
												+ pVoiceTblPtr->dwBufferSize
												- nPlayPos
											   );
			}
			else
			{
				pVoiceTblPtr->nRemainingBytes = (pVoiceTblPtr->dwNextWriteOffset
												- nPlayPos
											   );
			}
		}
	}
#ifdef	SNDCHK
	else
	{
TRACE("...dwLen >= nMaxLen...\n" );
	}
#endif

	// save this location in the file incase we need to reload
	pVoiceTblPtr->nSndOffset = ftell( pFilePtr );

cleanup:
	// made it here, we were successful
	error = FALSE;
exit:
	return( error );
}


///========================================================================
//	Function:		voiceFindID()
//
//	Description:
//		Locate a VOICE sound ID in the VOICE lookup table
//
//	Input:			nAudioID		audio Id number to apply pan to
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

VOICE_SND* voiceFindID ( ULONG nAudioID )
{
	VOICE_SND*	pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
	unsigned	index;

	if ( !VOICEenabled )
		goto exit;

	if ( nAudioID == SND_NULL_SND_ID )
		goto exit;

	// find the sound in the table
	pVoiceTblPtr = VOICElookupTable;
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		goto exit;

	index      = 0;
	while ( (index<VOICEmaxSounds) && (pVoiceTblPtr->nAudioID != nAudioID) )
	{
		++index;
		++pVoiceTblPtr;
	}
   
	// did we find it ?
	if ( index == VOICEmaxSounds )
		pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
exit:   
	return( pVoiceTblPtr );    
}

///========================================================================
//	Function:		voiceFindSndID()
//
//	Description:
//		Locate a VOICE snd ID in the VOICE lookup table
//
//	Input:			nSndID			SND Id number to locate
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

VOICE_SND* voiceFindSndID ( ULONG nSndID )
{
	VOICE_SND*	pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
	unsigned	index;

	if ( !VOICEenabled )
		goto exit;

	if ( nSndID == SND_NULL_SND_ID )
		goto exit;

	// find the sound in the table
	pVoiceTblPtr = VOICElookupTable;
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		goto exit;

	index      = 0;
	while ( (index<VOICEmaxSounds) && (pVoiceTblPtr->nSndID != nSndID) )
	{
		++index;
		++pVoiceTblPtr;
	}
   
	// did we find it ?
	if ( index == VOICEmaxSounds )
		pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
exit:   
	return( pVoiceTblPtr );    
}

///========================================================================
//	Function:		voiceFindSlot()
//
//	Description:
//		Locate a VOICE sound slot in the VOICE lookup table
//
//	Input:			nVoiceID			sound Id number to apply pan to
//
//	Ouput:			pVoiceTblPtr		address of slot, SND_NULL_SND_PTR otherwise
//
///========================================================================

VOICE_SND* voiceFindSlot( void )
{
	VOICE_SND*	pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
	unsigned	index;

	if ( !VOICEenabled )
		goto exit;

	// find the sound in the table
	pVoiceTblPtr = VOICElookupTable;
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		goto exit;

	index      = 0;
	while ( (index<VOICEmaxSounds) && (pVoiceTblPtr->nAudioID != SND_NULL_SND_ID) )
	{
		++index;
		++pVoiceTblPtr;
	}
   
	// did we find it ?
	if ( index == VOICEmaxSounds )
		pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
exit:   
	return( pVoiceTblPtr );    
}

///========================================================================
//	Function:		voiceFindTimerID()
//
//	Description:
//		Locate a VOICE timer ID in the VOICE lookup table
//
//	Input:			uTimerID		timer Id number associated with a sound
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

VOICE_SND* voiceFindTimerID ( UINT uTimerID )
{
	VOICE_SND*	pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
	unsigned	index;

	if ( !VOICEenabled )
		goto exit;
	if ( !uTimerID )
		goto exit;

	// find the sound in the table
	pVoiceTblPtr = VOICElookupTable;
	if ( pVoiceTblPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: VOICElookupTable is empty. [%s:%d]\n", 
			  __FILE__, __LINE__ );
       
		goto exit;
	}

	index      = 0;
	while ( (index<VOICEmaxSounds) && (pVoiceTblPtr->uTimerID != uTimerID) )
	{
		++index;
		++pVoiceTblPtr;
	}
   
	// did we find it ?
	if ( index == VOICEmaxSounds )
		pVoiceTblPtr = (VOICE_SND*)SND_NULL_SND_PTR;
exit:   
	return( pVoiceTblPtr );    
}

///========================================================================
//	Function:		voiceGetOffset()
//
//	Description:
//		Locate a VOICE sound offset in the VOICE lookup table
//
//	Input:			nSndID			sound Id number to apply pan to
//					nIndexToLoad	relative index from sndID
//
//	Ouput:			offset			offset of slot, SND_NULL_SND_ID otherwise
//
///========================================================================

ULONG	voiceGetOffset( ULONG nSndID, unsigned nIndexToLoad )
{
	ULONG		offset;
	unsigned	index;
	unsigned	maxIndex;
   
	// search the header for this snd id
	offset  = (ULONG)SND_NULL_SND_ID;

	if ( !VOICEenabled )
		goto exit;

	if ( nSndID == SND_NULL_SND_ID )
		goto exit;

	// search the header for this snd id
	maxIndex = VOICEsndHeader->numberOfSounds;
	index    = 0;
	while ( (VOICEsndHeader->sounds[ index ].soundID != nSndID) && (index<maxIndex) )
		++index;

	if ( VOICEsndHeader->sounds[ index ].soundID != nSndID )
	{
		// report an error that the snd ID is not in this file
		TRACE("ERROR:  snd ID (%d) not in .snd file [%s:%d]\n\n", 
			nSndID, __FILE__, __LINE__ );
		goto exit;
	}
	
	// now adjust our choice based on the index
	if ( (index + nIndexToLoad) > maxIndex )
	{
		// report an error that the snd index exceeds table size
		TRACE("ERROR: load index (%d+%d) excceds table size (%d) [%s:%d]\n\n", 
			index, __FILE__, __LINE__ );
		goto exit;
	}

	// adjust the indexed element
	index += nIndexToLoad;

	// get the expected offset
	offset = VOICEsndHeader->sounds[ index ].offset;

exit:
	return( offset );
}

///========================================================================
//	Function:		voiceTimerCheck()
//
//	Description:
//		Verify that a timer ID belongs to the voiceMonitor.
//
//	Input:			uTimerID		timer Id triggering this processing
//
//	Ouput:			TRUE			if ID found, FALSE otherwise
//
///========================================================================

BOOL	voiceTimerCheck ( UINT uTimerID )
{
	VOICE_SND*	pVoiceTblPtr;
	unsigned	index;
	BOOL		answer = FALSE;		//assume timer is not ours

	if ( !VOICEenabled )
		return( answer );
	if ( !uTimerID )
		return( answer );

	// find the sound in the table
	index      = 0;
	pVoiceTblPtr = VOICElookupTable;
	while ( (index<VOICEmaxSounds) && (pVoiceTblPtr->uTimerID != uTimerID) )
	{
		++index;
		++pVoiceTblPtr;
	}
   
	// did we find it ?
	if ( index < VOICEmaxSounds )
		answer = TRUE;

	return( answer );
}

///========================================================================
//	Function:		voiceSetLink()
//
//	Description:
//		Link a dynamic list of voice sounds together. It is assumed that all
//		the listed streams have been loaded.
//
//	Input:			nVoiceID			sound ID to ste link for
//					nLink			link value
//
//	Ouput:			TRUE			if ID found, FALSE otherwise
//
///========================================================================

BOOL	voiceSetLink( unsigned nVoiceID, unsigned nLink )
{
	VOICE_SND*	pVoiceLinkPtr;
	BOOL		error = FALSE;		//assume timer is not ours

	if ( !VOICEenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nVoiceID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// Locate the sound ID and assigning the link sound ID into the link field.
	pVoiceLinkPtr = voiceFindID( nVoiceID );
	if ( pVoiceLinkPtr == (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: failed to locate VOICE ID (%ld). [%s:%d]\n\n", 
			  nVoiceID, __FILE__, __LINE__ );
		goto exit;
	}

	// apply the link
	pVoiceLinkPtr->nSndLink = nLink;

	// made it here so we must have been successful
	error = FALSE;

exit:
	return( error );
   
}

///========================================================================
//	Function:		voiceNextLink()
//
//	Description:
//		based on the snd ID passed in, determine if there is a link to another
//		snd ID. Return that ID or SND_NULL_SND_ID.
//
//	Input:			nVoiceID			sound ID whose link we want
//
//	Ouput:			nextVoiceLink	snd ID link to the input sound,
//									SND_NULL_SND_ID otherwise
//
///========================================================================

ULONG	voiceNextLink( ULONG nVoiceID )
{
	VOICE_SND*	pVoiceLinkPtr;
	ULONG		nextVoiceLink = SND_NULL_SND_ID;		// assume no link

	if ( !VOICEenabled )
		goto exit;

	if ( nVoiceID == SND_NULL_SND_ID )
		goto exit;

	// Locate the sound ID
	pVoiceLinkPtr = voiceFindID( nVoiceID );
	if ( pVoiceLinkPtr == (VOICE_SND*)SND_NULL_SND_PTR )
		goto exit;

	// Check for a link
	if ( pVoiceLinkPtr->nSndLink != SND_NULL_SND_ID )
		nextVoiceLink = pVoiceLinkPtr->nSndLink;			// there is a link

exit:
	return( nextVoiceLink );
   
}

///========================================================================
//	Function:		voiceGetMasterVoiceVolume()
//
//	Description:
// 		Get the stream voice sound volume level:
//
//	Input:			none
//
//	Ouput:			nVolume			current SFX volume setting
//
///========================================================================

LONG		voiceGetMasterVoiceVolume ( void ) 
{
	return( VOICEvoiceMasterVolume );
}

///========================================================================
//	Function:		voiceSetMasterVoiceVolume()
//
//	Description:
// 		Set the voice voice sound volume level:
//
//	Input:			nVolume			volume setting to apply
//
//	Ouput:			none
//
///========================================================================

void	voiceSetMasterVoiceVolume ( LONG nVolumePercentage )
{
	VOICE_SND	*pVoiceTblPtr;
	int		nIndex;

	VOICEvoiceMasterVolume = nVolumePercentage;

	// now adjust all sounds to this volume precentage
	if ( !VOICEenabled )
		return;

	// cleanup the sfx lookup table
	pVoiceTblPtr = VOICElookupTable;
	if ( pVoiceTblPtr != (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// lower the volume of each legal sound in the table
		for ( nIndex=0; nIndex<(int)VOICEmaxSounds; ++nIndex )
		{
			// change the volume of this sound this sound
			if ( pVoiceTblPtr->nSndID != (ULONG)SND_NULL_SND_ID )
				SndSetVolumePercent( pVoiceTblPtr->nSndID, nVolumePercentage, FALSE );

			// check the next entry
			++pVoiceTblPtr;
		}
	}
}

///========================================================================
//	Function:		voiceGetMasterMusicVolume()
//
//	Description:
// 		Get the stream music sound volume level:
//
//	Input:			none
//
//	Ouput:			nVolume			current SFX volume setting
//
///========================================================================

LONG		voiceGetMasterMusicVolume ( void ) 
{
	return( VOICEmusicMasterVolume );
}

///========================================================================
//	Function:		voiceSetMasterMusicVolume()
//
//	Description:
// 		Set the voice voice sound volume level:
//
//	Input:			nVolume			volume setting to apply
//
//	Ouput:			none
//
///========================================================================

void	voiceSetMasterMusicVolume ( LONG nVolume )
{
	VOICEmusicMasterVolume = nVolume;
}

///========================================================================
//	Function:		voiceLoadText()
//
//	Description:
// 		load the text string associated with the voice audio ids. Access
//		the file voice.ast
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	voiceLoadText ( void )
{
	char		pBuffer[ VOICE_MAX_TEXT_LEN + 1 ];
	char*		pVoiceText;
	ULONG		nSize;
	ULONG		nID;
	ULONG		nVoiceID;
	ULONG		nLen;
	BOOL		bDone;

	// start by opening the .AST file
	SetPath( AUDIO_PATH );
	if ( (pTEXTfile = (FILE*)fopen( "voices.ast", "rb" )) == NULL )
	{
		// report an error
		TRACE("ERROR: failed to open file: \"voices.ast\". [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}
	VOICETEXTenabled = TRUE;

	// make sure the first thing in the file is a CPRY chunk
	CHUNK_READ_LONG( pTEXTfile, &nID );
	if ( nID != CPYR_ID )
	{
		TRACE( "ERROR: failed read of CPYR chunk [%s;%d]\n", __FILE__, __LINE__ );
		goto cleanUP;
	}
#ifdef CHUNK_DEBUG
	ChunkName( nID );
#endif

	// now read in the chunk size
	CHUNK_READ_LONG( pTEXTfile, &nSize );
#ifdef CHUNK_DEBUG
	TRACE( "%ld ", nSize );
#endif

	// now read in the chunk
	CHUNK_READ_BUFFER( pTEXTfile, pBuffer, nSize );
#ifdef CHUNK_DEBUG
	TRACE( "\"%s\" %d\n", pBuffer, nSize );
#endif

	// now find the first VTXT chunk
	nID = VTXT_ID;
	if ( ChunkFind( pTEXTfile, VTXT_ID ) )
	{
		bDone = FALSE;
		while( !bDone )
		{
			// read in the size of the chunk
			CHUNK_READ_LONG( pTEXTfile, &nSize );
#ifdef CHUNK_DEBUG
			TRACE( "size:%ld ", nSize );
#endif

			// read in the voice audio ID
			CHUNK_READ_LONG( pTEXTfile, &nVoiceID );
#ifdef CHUNK_DEBUG
			TRACE( "voice ID:%ld ", nVoiceID );
#endif

			// read in the voice string length
			CHUNK_READ_LONG( pTEXTfile, &nLen );
#ifdef CHUNK_DEBUG
			TRACE( "len:%ld ", nLen );
#endif

			// malloc a string to fit the text data
			pVoiceText = (char*)malloc( nLen+1 );
			ASSERT( pVoiceText );

			// now read in the chunk
			CHUNK_READ_BUFFER( pTEXTfile, pVoiceText, nLen );
			pVoiceText[nLen] = '\0';
#ifdef CHUNK_DEBUG
			TRACE( "\"%s\" %d\n", pVoiceText, nLen );
#endif

			// insert the string into the table
			VOICEtextTable[ VOICEnextText ].nVoiceID   = nVoiceID;
			VOICEtextTable[ VOICEnextText ].pVoiceText = pVoiceText;
			++VOICEnextText;
			pVoiceText = NULL;

			// go find the next chunk
			if ( ChunkFindNext( pTEXTfile, VTXT_ID ) == FALSE )
				bDone = TRUE;
		}
	}
cleanUP:
	// now close the voice file
	if ( pTEXTfile )
	{
		fclose( pTEXTfile );
		pTEXTfile = NULL;
	}

exit:
	return;
}

///========================================================================
//	Function:		voiceFreeText()
//
//	Description:
// 		free the text string associated with the voice audio ids.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	voiceFreeText ( void )
{
	int			nVoice;

	if ( !VOICETEXTenabled )
		return;

	// start by freeing the text string
	for( nVoice=0; nVoice<(int)VOICEnextText; ++nVoice )
	{
		free( VOICEtextTable[ nVoice ].pVoiceText );
		VOICEtextTable[ nVoice ].pVoiceText      = NULL;
		VOICEtextTable[ VOICEnextText ].nVoiceID = SND_NULL_SND_ID;
	}
}

///========================================================================
//	Function:		voiceFinfText()
//
//	Description:
// 		free the text string associated with the voice audio ids.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

char*	voiceFindText ( ULONG nVoiceID )
{
	int			nVoice;
	BOOL		bFound;
	char*		pText = NULL;

	if ( !VOICETEXTenabled )
		return( pText );

	// start by freeing the text string
	nVoice = 0;
	bFound = 0;
	while( !bFound && (nVoice<(int)VOICEnextText) )
	{
		if ( VOICEtextTable[ nVoice ].nVoiceID == nVoiceID )
			bFound = TRUE;
		else
			++nVoice;
	}
	if ( bFound )
		pText = VOICEtextTable[ nVoice ].pVoiceText;
	return( pText );
}

ULONG	voiceCreateStream( unsigned AUDIOvoiceID, ULONG nAudioID,
						       unsigned nIndexToLoad,  USHORT bFlags )
{
	ULONG	nSndID = SND_NULL_SND_ID;

	nSndID = voiceLoad( AUDIOvoiceID, nAudioID, nIndexToLoad, bFlags );

	return( nSndID );
}

void	voiceDeleteStream( unsigned nSndID )
{
	voiceDeleteSnd( nSndID );

	// now delete the snd
	audioDeleteSnd( nSndID );
}

void	voiceCleanUpStreams( ULONG nSndID )
{
	VOICE_SND	*pVoiceTblPtr;
	ULONG		bFlags;

	if ( nSndID != SND_NULL_SND_ID )
	{
		bFlags = voiceFlags( nSndID );
		if ( ((bFlags & SND_TIMER_FLAG) == SND_TIMER_FLAG) && ((bFlags & SND_DONE_FLAG) != SND_DONE_FLAG) )
		{
			pVoiceTblPtr = voiceFindSndID( nSndID );
			if ( pVoiceTblPtr )
				voiceUpdate( pVoiceTblPtr );
		}
		if ( ((bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG) && ((bFlags & SND_DONE_FLAG) == SND_DONE_FLAG) )
			voiceDeleteStream( nSndID );
	}
}

void		voiceTableCleanUp( void )
{
	VOICE_SND*	pVoiceTblPtr;
	ULONG		nSndID;
	unsigned	index;
	ULONG		bFlags;

	// cleanup the voice lookup table
	pVoiceTblPtr = VOICElookupTable;
	if ( pVoiceTblPtr != (VOICE_SND*)SND_NULL_SND_PTR )
	{
		// clean up each legal sound in the table
		for ( index=0; index<VOICEmaxSounds; ++index )
		{
			// delete this sound
			if ( pVoiceTblPtr->nSndID != (ULONG)SND_NULL_SND_ID )
			{
				nSndID = pVoiceTblPtr->nSndID;
				bFlags = voiceFlags( nSndID );
				if ( ((bFlags & SND_TIMER_FLAG) == SND_TIMER_FLAG) && ((bFlags & SND_DONE_FLAG) != SND_DONE_FLAG) )
					voiceUpdate( pVoiceTblPtr );
				if ( ((bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG) && ((bFlags & SND_DONE_FLAG) == SND_DONE_FLAG) )
					voiceDeleteStream( nSndID );
			}

			// check the next entry
			++pVoiceTblPtr;
		}
	}
}

USHORT	voiceFlags( ULONG nSndID )
{
	VOICE_SND* pVoice = (VOICE_SND*)voiceFindSndID ( nSndID );
	if ( pVoice != (VOICE_SND*)SND_NULL_SND_PTR )
		return ( pVoice->bFlags );
	else
		return( 0 );
}


void	voiceSetOn(BOOL on)	{
	VOICEon = on;
}

BOOL	voiceGetOn(void)	{
	return( VOICEon );
}

void	voiceToggleOn(void)	{
	VOICEon ^= TRUE;
}

void	voiceDump ( VOICE_SND* pVoiceTblPtr )
{
	TRACE( "pStrmTblPtr:\n" );
	TRACE( " bLock             = %d\n", pVoiceTblPtr->bLock );			// locking mechanism
	TRACE( " nAudioID          = %d:%s\n", pVoiceTblPtr->nAudioID,		// audio identifier
										   audioIDname( pVoiceTblPtr->nAudioID ) );

	TRACE( " nVoiceID           = %d\n", pVoiceTblPtr->nVoiceID );			// STREAM identifier
	TRACE( " nSndID            = %d\n", pVoiceTblPtr->nSndID );			// sound identifier
	TRACE( " bFlags            = %d\n", pVoiceTblPtr->bFlags );			// Flag fields (see SND.H)
	TRACE( " pDSBuffer         = %d\n", pVoiceTblPtr->pDSBuffer );		// Direct Sound Buffer
	TRACE( " pWaveForm         = %d\n", pVoiceTblPtr->pWaveForm );		// Wave Format data structure

				// these are filled at load time.
	TRACE( " nSndStart         = %d\n", pVoiceTblPtr->nSndStart );		// Start offset into file to reach sound chunk
	TRACE( " nSndOffset        = %d\n", pVoiceTblPtr->nSndOffset );		// current offset into wave stream
	TRACE( " nSndSize          = %d\n", pVoiceTblPtr->nSndSize );		// size of raw stream data

	TRACE( " uTimerID          = %d\n", pVoiceTblPtr->uTimerID );		// stream timer ID
	TRACE( " dwBufferSize      = %d\n", pVoiceTblPtr->dwBufferSize );    // Size of the entire buffer
	TRACE( " dwBufferSegSize   = %d\n", pVoiceTblPtr->dwBufferSegSize ); // Size of one buffer segment
	TRACE( " dwNextWriteOffset = %d\n", pVoiceTblPtr->dwNextWriteOffset );// Offset to next buffer segment
	TRACE( " dwPlayLast        = %d\n", pVoiceTblPtr->dwPlayLast );      // Position of last play cursor
	TRACE( " dwProgress        = %d\n", pVoiceTblPtr->dwProgress );      // Used with above to show prog
	TRACE( " nRemainingBytes   = %d\n", pVoiceTblPtr->nRemainingBytes );	// Bytes 'til timer shutdown
	TRACE( " nSndLink          = %d\n", pVoiceTblPtr->nSndLink );		// Link to another strm ID
	TRACE( " DUMP DONE\n" );
}

///========================================================================
//								EOF
///========================================================================
