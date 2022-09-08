//========================================================================
//	FILE:			$Workfile: strm.cpp $
//
//	DESCRIPTION:	Audio STRM processing.
//
//					Special Effects Audio processing. These usually refer
//					to short, static, often used sounds.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Friday, May 03, 1996
//
//	REVISION:		$Header: /ArmyMen/src/strm.cpp 50    4/03/98 2:23p Aburgess $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//========================================================================
//	strmInit()
//		initialize the SXF sound processing
//	strmExit()
//		Clean up the STRM processing and data
//	strmOpen()
//		Open a STRM .snd file for input
//	strmLoad()
//		Load one or more STRM sounds from a .SND file
//	strmLoadRes()
//		Load a single resouce STRM
//	strmLoadWav()
//		Load a single STRM from a .WAV
//	strmPlay()
//		Play a STRM sound by ID
//	strmCue()
//		Cue up a STRM sound by ID
//	strmFade()
//		Fade in or out a STRM sound by ID
//	strmStop()
//		Stop a STRM sound by ID
//	strmDelete()
//		Delete a STRM sound by ID
//	strmClose()
//		Close down an STRM .snd file
//	strmGetFrequency()
// 		Get the STRM sound frequency level (effect pitch)
//	strmSetFrequency()
// 		Set the STRM sound requency level (effect pitch)
//	strmGetVolume()
// 		Get the STRM sound volume levels:
//	strmSetVolume()
// 		Set the STRM sound volume levels:
//	strmGetPan()
// 		Get the STRM sound pan levels
//	strmSetPan()
// 		Set the STRM sound pan levels
//	strmMonitor()
//		Monitor STRM processing, updating the playback buffer at regular
//		intervals.
//	strmLoadData()
//		read in a buffer segment's worth of data
//	strmLoadNextData()
//		read in a buffer segment's worth of data
//	strmFindID()
//		Locate a STRM sound ID in the STRM lookup table
//	strmFindSlot()
//		Locate a STRM sound slot in the STRM lookup table
//	strmGetOffset()
//		Locate a STRM sound offset in the STRM lookup table
//	strmGetFileName()
//		Retreive the STRM filename associated with a file pointer
//	strmDelFileName()
//		Delete the STRM filename associated with a file pointer
//	strmTimerCheck()
//		Verify that a timer ID belongs to the strmMonitor.
//	strmSetLink()
//		Link a dynamic list of strm sounds together. It is assumed that all
//		the listed streams have been loaded.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/strm.cpp $
//  
//  50    4/03/98 2:23p Aburgess
//  replaced exit call with return call
//  
//  49    4/03/98 1:33p Nrobinso
//  push music volume back up
//  
//  48    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  47    3/25/98 7:40p Nrobinso
//  default music volume to 80%
//  
//  46    3/25/98 4:09p Aburgess
//  using new DIRECTSOUND flags
//  
//  45    3/22/98 4:27p Nrobinso
//  remove sndPlay
//  
//  44    3/21/98 6:55a Nrobinso
//  
//  42    3/20/98 11:53a Aburgess
//  modifications made to correct VOICE and MUSIC cut offs. It apprears
//  that ALL Music and Voice streams need to be run with LOOP on.
//  
//  41    3/18/98 2:23p Aburgess
//  modifications to correct update error
//  
//  40    3/18/98 11:46a Aburgess
//  removed unused code, added debug, and cleared StrmID values
//  
//  39    3/17/98 11:25a Aburgess
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
//  33    2/27/98 3:34p Nrobinso
//  replaced SFX references with STRM references
//  
//  32    2/03/98 3:28p Aburgess
//  eliminated infinite loop on stream load problem
//  
//  31    2/03/98 2:40p Aburgess
//  modifications made to correct music stream failures
//  
//  30    1/30/98 12:54p Bwilcox
//  andrews unlooping fixes
//  
//  29    1/21/98 2:03p Nrobinso
//  modification to stream updates for non queued items
//  
//  28    1/21/98 9:22a Aburgess
//  modifications made to shorten the STRM and VOICE monitor interrupts.
//  Also merged the audio ON/OFF switching. In addition, all audio is now
//  turned off during mission load as that routine has a large frame
//  overrun problem disallowing updates to audio.
//  
//  27    1/05/98 2:31p Aburgess
//  corrected Voice deletions.
//  
//  26    1/05/98 10:32a Aburgess
//  latest attempt to resolve Streaming bug. Voice is now handled in a
//  seperate handler.
//  
//  25    12/23/97 6:25p Nrobinso
//  use audio variables for on/off
//  
//  24    12/22/97 11:35a Aburgess
//  added Snd prototype equivalents
//  
//  23    12/19/97 1:52p Aburgess
//  clarification of nSndID usage
//  
//  22    12/18/97 1:20p Aburgess
//  attempt to apply volume changes to Music. Also not managing Music queue
//  on enable and disable of audio. strmMonitor debug added
//  
//  21    12/17/97 11:03a Aburgess
//  moved up SND_TIMER check and changed later exits to clear SND_TIMER
//  flag on exit
//  
//  20    12/15/97 10:20a Aburgess
//  added EventTimer killing.
//  
//  19    12/15/97 9:03a Aburgess
//  conversion to limit # of voice and music streams playing
//  
//  18    12/09/97 12:49p Aburgess
//  corrected STREAM processing
//  
//  17    12/09/97 12:12p Phu
//  
//  17    12/09/97 12:12p Phu
//  
//  16    12/07/97 6:28p Aburgess
//  disabled debug trace
//  
//  15    12/04/97 4:19p Nrobinso
//  check for null sound id
//  
//  14    12/04/97 9:14a Aburgess
//  Modifications made to properly handle delete race condition with
//  strmMonitor. Actual sound allocation tracking added to help minimize
//  static tables for audio
//  
//  13    12/02/97 10:21a Aburgess
//  locking mechanism added for deletes (load?)
//  
//  12    12/01/97 9:57a Aburgess
//  removed superfluous error reporting
//  
//  11    11/24/97 2:56p Aburgess
//  debug modification
//  
//  10    11/21/97 9:14a Aburgess
//  corrected return value to be nSndID rather than nStrmID. Debug of SND
//  id reporting
//  
//  9     11/20/97 3:32p Aburgess
//  modifications made to allow app to run regardless of existence of .ASD,
//  .AST files or DirectSound itself
//  
//  8     11/20/97 11:54a Aburgess
//  audio modifications
//  
//  7     11/17/97 10:08a Aburgess
//  rework of audio/sfx/strm/voice/snd interface
//  
//  6     11/16/97 2:21p Aburgess
//  cleanup of sound files (fclose)
//  
//  4     9/10/97 10:14a Aburgess
//  removed unecessary warning message
//  
//  3     9/02/97 9:39a Aburgess
//  added VOICE and MUSIC master volume control
//  
//  2     8/14/97 5:05p Nrobinso
//  audio fixes
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  18    4/14/97 7:28a Aburgess
//  modifications made to support full Army creation along with unit
//  reserves. Vehicle reserves have yet to be done.
//  
//  17    11/13/96 12:39p Nrobinso
//  moved malloc.h and string.h to stdafx
//  
//  16    10/02/96 11:29a Aburgess
//  added strmReset() and strmNextLink()
//  
//  15    9/10/96 12:59p Aburgess
//  move commonly used but infrequently changed header files to stdafx.h
//  (precompiled header)
//  
//  14    8/15/96 6:01a Aburgess
//  removed superfluous TRACE warnings and errors
//  
//  13    8/14/96 10:21p Aburgess
//  fixed bug that failed to place the callers bFlag value into the snd
//  info. Thus Looping would never be set.
//  
//  9     6/28/96 2:25p Aburgess
//  corrected audio streaming code. NOTE: DirectSound smaples from
//  MicroSoft changed with DXII. These changes helped slove the streaming
//  problem.
//  
//  8     6/26/96 10:46a Aburgess
//  added new Source Control headers
// 
//  $Nokeywords:$
///========================================================================
#include "stdafx.h"

#include "Snd.h"			// SND      defines, structures, and prototypes
#include "Strm.h"			// STRM		internal defines and structures
#include "Voice.h"			// VOICE	internal defines and structures

extern	char*		audioIDname( ULONG nAudioID );
extern	char*		audioSndIDname( ULONG nSndID );
extern	BOOL		audioDeleteSnd( ULONG nSndID  );
extern	unsigned	VOICEsoundsActive;
extern	void		SndSetVolumePercent( ULONG nSndID ,ULONG Percent, BOOL bMax );
extern	LONG		audioGetMasterVolume( USHORT bFlag );

///========================================================================
//							LOCAL DEFINES
///========================================================================

///========================================================================
//							LOCAL DATA TYPES
///========================================================================

///========================================================================
//							LOCAL VARIABLES
///========================================================================

// STRM lookup table
STRM_SND*		STRMlookupTable;
unsigned		STRMmaxSounds;
unsigned		STRMactualMaxSounds;
unsigned		STRMsoundsActive;

SND_HEADER*		STRMsndHeader;

static	FILE*	pSTRMfile;
static	long	STRMwaitCount;

static	ULONG	STRMnextID;

#ifndef AUDIO_TIMER
static	int		STRMtimerID;
#endif
static	int		STRMmonitorBusy = FALSE;

static	LONG	STRMvoiceMasterVolume = 100;
static	LONG	STRMmusicMasterVolume = 100;

BOOL			STRMenabled;
BOOL			STRMon;

static	ULONG	STRMqueue[ VOICE_MAX_QUEUE_ENTRIES ];
static	int		STRMqueueCount = 0;

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
BOOL		strmLoadData ( STRM_SND* pStrmTblPtr, BYTE* pDSBuffData, DWORD maxLen );
BOOL		strmLoadNextData ( STRM_SND* pStrmTblPtr, BYTE* pDSBuffData, DWORD maxLen, DWORD nPlayPos );
STRM_SND*	strmFindSlot( void );
ULONG		strmGetOffset( ULONG nSndID, unsigned nIndexToLoad );
STRM_SND*	strmFindTimerID ( UINT uTimerID );
void		strmDump( STRM_SND* pStrmTblPtr );


///========================================================================
//	Function:		strmInit()
//
//	Description:
//		initialize the SXF sound processing
//
//	Input:			nMaxSounds		maximum size of the strm sound table
//
//	Ouput:			error			FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		strmInit ( unsigned nMaxSounds )
{
	STRM_SND*	pStrmTblPtr;
	unsigned		index;
	BOOL			error = TRUE;	// assume failure

	// remember the max number of sounds that can be created
	STRMmaxSounds       = nMaxSounds;
	STRMactualMaxSounds = 0;
	STRMsoundsActive    = 0;
	STRMwaitCount       = 0;
	STRMnextID          = STRM_START_ID;

	for( index=0;index<VOICE_MAX_QUEUE_ENTRIES;++index)
		STRMqueue[ index ] = 0;
	STRMqueueCount = 0;

	STRMenabled         = TRUE;

	// allocate the memory necessary to support
	STRMlookupTable = (STRM_SND*)malloc( STRMmaxSounds* sizeof(STRM_SND) );
	if ( STRMlookupTable == NULL )
	{
		// report an error
		TRACE("ERROR: Insufficient memory available. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}
#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): STRM lookup table [%s : %d]\n",
			( STRMmaxSounds* sizeof(STRM_SND) ),__FILE__, __LINE__ );
#endif

	// initialize the strm lookup table
	pStrmTblPtr = STRMlookupTable;
	for( index=0; index<STRMmaxSounds; ++index, pStrmTblPtr++ )
	{
		pStrmTblPtr->bLock              = FALSE;			// audio lock
		pStrmTblPtr->nAudioID			= SND_NULL_SND_ID;	// audio sound identifier
		pStrmTblPtr->nStrmID			= SND_NULL_SND_ID;	// stream sound identifier
		pStrmTblPtr->nSndID			    = SND_NULL_SND_ID;	// sound identifier
		pStrmTblPtr->bFlags			    = SND_CLEAR_FLAG;	// Boolean Flag fields
		pStrmTblPtr->pWaveForm          = (WAVEFORMATEX*)NULL; // Wave Format data structure
		pStrmTblPtr->nSndStart          = 0;			// index into .snd or .wav file to read from
		pStrmTblPtr->nSndOffset         = 0;			// offset into file to reach sound chunk
														// this is filled at load time.
		pStrmTblPtr->nSndSize           = 0;			// size of raw data
		pStrmTblPtr->uTimerID           = 0;            // play interrupt timer ID
		pStrmTblPtr->dwBufferSize       = 0;            // Size of the entire buffer
		pStrmTblPtr->dwBufferSegSize    = 0;            // Size of one buffer segment
		pStrmTblPtr->dwNextWriteOffset  = 0;            // Offset to next buffer segment
		pStrmTblPtr->dwPlayLast         = 0;            // Used with above to show prog
		pStrmTblPtr->dwProgress         = 0;            // Used with above to show prog
		pStrmTblPtr->nRemainingBytes    = 0;			// Segments 'til timer shutdown
		pStrmTblPtr->nSndLink           = SND_NULL_SND_ID;	// Link to another strm ID

	}

	// initialize the SND header structure
	STRMsndHeader = NULL;

	// initialize the input file pointer
	pSTRMfile = NULL;

#ifndef	AUDIO_TIMER
	STRMtimerID = 1;
#endif

	// set the MUSIC toggle
//	strmSetOn(TRUE);

	// if we got here we were successful
	error = FALSE;

exit:
	return( error );
}


///========================================================================
//	Function:		strmExit()
//
//	Description:
//		Clean up the STRM processing and data
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void		strmExit ( void )
{
	STRM_SND*	pStrmTblPtr;
	unsigned	index;

	for( index=0;index<VOICE_MAX_QUEUE_ENTRIES;++index)
		STRMqueue[ index ] = 0;
	STRMqueueCount = 0;

	// cleanup the strm lookup table
	pStrmTblPtr = STRMlookupTable;
	if ( pStrmTblPtr != (STRM_SND*)SND_NULL_SND_PTR )
	{
		// clean up each legal sound in the table
		for ( index=0; index<STRMmaxSounds; ++index )
		{
			// delete this sound
			if ( pStrmTblPtr->nStrmID != (ULONG)SND_NULL_SND_ID )
			{
				strmDeleteSnd( pStrmTblPtr->nSndID );

				// now delete the snd
				audioDeleteSnd( pStrmTblPtr->nSndID );
			}

			// check the next entry
			++pStrmTblPtr;
		}

		// de-allocate the look up table structure
		if ( STRMlookupTable )
		{
			free( STRMlookupTable );
			STRMlookupTable = (STRM_SND*)SND_NULL_SND_PTR;
		}
	}

	// de-allocate the SND header structure
	if ( STRMsndHeader )
	{
		free( STRMsndHeader );
		STRMsndHeader = NULL;

#ifdef MALLOC_DEBUG
			TRACE( "free: STRM header [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}

	// now close the voice file
	if ( pSTRMfile )
	{
		fclose( pSTRMfile );
		pSTRMfile = NULL;
	}

	// disable the stream processing
	STRMenabled = FALSE;

#ifdef SND_DEBUG
	TRACE( "STRMactualMaxSounds = %d\n", STRMactualMaxSounds );
#endif
}


///========================================================================
//	Function:		strmOpen()
//
//	Description:
//		open a STRM .snd file for input
//
//	Input:			pFilename		.SND filename that needs opening
//
//	Ouput:			nFileID			file id to file info is successful
//									NULL otherwise
//
///========================================================================

unsigned	strmOpen ( char* pFilename )
{
	unsigned	nFileID = SND_NULL_SND_ID;

	// make sure there isn't a file open already
	if ( pSTRMfile != NULL )
	{
		// report an error
		TRACE("WARNING: strm file already open. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// now open the new .SND file
	if ( (pSTRMfile = (FILE*)fopen( pFilename, "rb" )) == NULL )
	{
		// report an error
		TRACE("ERROR: failed to open file: \"%s\". [%s:%d]\n\n", 
			  pFilename, __FILE__, __LINE__ );
		goto exit;
	}

	// make sure the SND header is free
	if ( STRMsndHeader )
	{
		free( STRMsndHeader );
		STRMsndHeader = NULL;

#ifdef MALLOC_DEBUG
		TRACE( "free: STRM header [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}

	// copy in the .SND header information
	STRMsndHeader = (SND_HEADER*)malloc( sizeof( SND_HEADER ) );
	if ( STRMsndHeader == NULL )
	{
		// report an error
		TRACE("ERROR: Insufficient memory available. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}
#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): STRM header [%s : %d]\n", ( sizeof( SND_HEADER ) ), __FILE__, __LINE__ );
#endif

	if ( fread( STRMsndHeader, sizeof( SND_HEADER ), 1, pSTRMfile ) != 1 )
	{
		// report an error: failed writing header
		TRACE("ERROR: failed to read .SND header. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		if ( pSTRMfile )
			fclose( pSTRMfile );
		pSTRMfile = NULL;
		nFileID = SND_NULL_SND_ID;
	}

	// if we made it here, its time to save off the filename with
	// the file pointer for use at load time to set the filename to
	// the stream.
	nFileID = sndSaveFile( pSTRMfile, pFilename );

exit:
	return( nFileID );
}


///========================================================================
//	Function:		strmMaxSounds()
//
//	Description:
//		return the current number of sounds in the STRM lookup table
//
//	Input:			none
//
//	Ouput:			maxSounds		number of sounds in the look table
//									NULL otherwise
//
///========================================================================

unsigned	strmMaxSounds ( void )
{
	unsigned	maxSounds = 0;

	if ( STRMsndHeader == NULL )
	{
		// report an error
		TRACE("WARNING: STRM sound lookup table not present. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// get the sound count
	maxSounds = STRMsndHeader->numberOfSounds;
exit:
	return( maxSounds );
}


///========================================================================
//	Function:		strmLoad()
//
//	Description:
//		Load one or more STRM sounds from a .SND file
//
//	Input:			nFileID			id of file to access
//					nAudioID		audio Id number to be stored into
//					nIndexToLoad	index within .SND file from which to
//									load STRM sound
//					bFlags			falgs associated with this sound.
//
//	Ouput:			nSndID			ID assigned to this sound if successful
//									SND_NULL_SND_ID if failure
//
///========================================================================

ULONG	strmLoad( unsigned nFileID, ULONG nAudioID, unsigned nIndexToLoad, USHORT bFlags )
{
	DSBUFFERDESC		dsBufferDesc;
	SND*				pSndPtr;
	LPDIRECTSOUND		pDirectSound;
	DWORD				dwDataLen1;
	DWORD				dwDataLen2;
    BYTE*				pDSBuffData1;
    BYTE*				pDSBuffData2;
	int					nSndIdx;
	unsigned			status;
	ULONG				offset;
	unsigned			error;
	STRM_SND*			pStrmTblPtr = NULL;
	ULONG				nSndID      = SND_NULL_SND_ID;

	if ( !STRMenabled )
		return( nSndID );

	if ( nAudioID == SND_NULL_SND_ID )
		return( nSndID );

#ifdef DBG_AUDIO
	char* pAudioName = audioIDname( nAudioID );
	if ( strcmp( pAudioName, "LOSE_MUSIC" ) == 0 )
		TRACE("strmLoad( %s:%ld )\n", pAudioName, nAudioID ); 
#endif

	// make sure the table isn't full already
	if ( STRMsoundsActive == STRMmaxSounds )
	{
		// report an error that the sound table is full
		TRACE("ERROR: strm table limited exceeded (%d). [%s:%d]\n\n", 
			  STRMmaxSounds, __FILE__, __LINE__ );
		goto exit;
	}

    // Get the DirectSound Object for this application
	pDirectSound = sndGetDSobject();
	if ( !pDirectSound )
		goto exit;

	// get the expected offset
	offset = strmGetOffset( nAudioID, nIndexToLoad );
	if ( offset == SND_NULL_SND_ID )
	{
		// report an error that the sound table is full
		TRACE("ERROR: failed to get STRM offset.[%s:%d]\n", 
			   __FILE__, __LINE__ );
		goto exit;
	}

	// create this sound. if already created will return address
	// of existing sound
	nSndID = sndCreate( nAudioID, bFlags, nFileID, &offset );
	if ( nSndID == SND_NULL_SND_ID )
	{
		// report an error that the sound table is full
		TRACE("ERROR: failed to create new STRM entry.[%s:%d]\n", 
			   __FILE__, __LINE__ );
		goto cleanUp;
	}

	// find an available sound
	pStrmTblPtr = strmFindSlot();
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		// report an error that the sound table is full
		TRACE("ERROR: failed to create new strm entry.[%s:%d]\n\n", 
			   __FILE__, __LINE__ );
		goto cleanUp;
	}

	// if we're here we have a strm entry to fill.
	// start by locating the SND and load in the data
	status = sndFindSndID( nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, nSndID, __FILE__, __LINE__ );
		goto cleanUp;
	}

	// initialize the STRM entry
	pStrmTblPtr->nAudioID		  = nAudioID;			// audio sound identifier
	pStrmTblPtr->nStrmID		  = STRMnextID++;		// stream sound identifier
	pStrmTblPtr->nSndID			  = nSndID;				// sound identifier
	pStrmTblPtr->bFlags			  = bFlags;				// Flag fields

	// save this location in the file incase we need to reload
	pStrmTblPtr->nSndStart  = pSndPtr->wavSnd.nSndStart;
	pStrmTblPtr->nSndOffset = pStrmTblPtr->nSndStart;

	// save the size of the stream for termination purposes
	pStrmTblPtr->nSndSize   = pSndPtr->wavSnd.nSndSize;

    // Calculate a buffer length, making sure it is an exact multiple of the
    // buffer segment size.
	pStrmTblPtr->pWaveForm    = &(pSndPtr->wavSnd.wfSndFormat);
    pStrmTblPtr->dwBufferSize = ((DWORD)pStrmTblPtr->pWaveForm->nAvgBytesPerSec
                               * (((STRM_NUM_BUFFER_SEGMENTS * STRM_PLAYBACK_TIMER_PERIOD)
                               / 10)) / 100);
    pStrmTblPtr->dwBufferSegSize   = pStrmTblPtr->dwBufferSize / STRM_NUM_BUFFER_SEGMENTS;
    pStrmTblPtr->dwBufferSize      = pStrmTblPtr->dwBufferSegSize * STRM_NUM_BUFFER_SEGMENTS;

    // Create the secondary DirectSoundBuffer object to receive our sound data.
	memset( &dsBufferDesc, 0, sizeof(DSBUFFERDESC)); 
    dsBufferDesc.dwSize        = sizeof(DSBUFFERDESC);
    dsBufferDesc.dwFlags       = DSBCAPS_CTRLDEFAULT | DSBCAPS_GETCURRENTPOSITION2;
    dsBufferDesc.dwBufferBytes = pStrmTblPtr->dwBufferSize;

    /* Set Format properties according to the WAVE file we just opened */
    dsBufferDesc.lpwfxFormat   = pStrmTblPtr->pWaveForm;
    error = pDirectSound->CreateSoundBuffer(
											&dsBufferDesc,
										    &(pStrmTblPtr->pDSBuffer),
										    NULL
										   );
    if (error != DS_OK)
	{
		// report an error
		TRACE("strmLoad( %s:%ld)\n", audioIDname(nAudioID),nAudioID ); 
		TRACE("ERROR:  failed to create the DirectSoundbuffer (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto cleanUp;
	}

	// since we're loading here, we can't of found the End Of Stream and
	// we don't have segments ready as yet.
    pStrmTblPtr->bFlags           &= ~SND_EOS_FLAG;
    pStrmTblPtr->nRemainingBytes   = 0;
	pStrmTblPtr->dwNextWriteOffset = 0;
	pStrmTblPtr->dwPlayLast        = 0;
	pStrmTblPtr->dwProgress        = 0;

    // Lock the DS buffer
    error = pStrmTblPtr->pDSBuffer->Lock( 0, pStrmTblPtr->dwBufferSize,
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
		if ( strmLoadData( pStrmTblPtr, (BYTE*)pDSBuffData1, dwDataLen1 ) )
		{
			// report an error
			TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );

			// Unlock the DS buffer
			error = pStrmTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
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
    error = pStrmTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
										   (LPVOID)pDSBuffData2, 0
									     );
	if ( error != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto cleanUp;
	}

	pStrmTblPtr->bFlags           &= ~SND_DONE_FLAG;

	// if we made it here we've had success
	++STRMsoundsActive;
	if ( STRMactualMaxSounds < STRMsoundsActive )
		STRMactualMaxSounds = STRMsoundsActive;

#ifdef DBG_AUDIO
//	if ( strcmp( pAudioName, "LOSE_MUSIC" ) == 0 )
//		strmDump( pStrmTblPtr );
#endif

	// see if we were error free
	goto exit;

	// clean up after getting an error
cleanUp:
	// clean up this STRM entry
	if ( pStrmTblPtr )
	{
		if (pStrmTblPtr != (STRM_SND*)SND_NULL_SND_PTR)
		{
			pStrmTblPtr->nStrmID		= SND_NULL_SND_ID;	// stream sound identifier
			pStrmTblPtr->nSndID			= SND_NULL_SND_ID;	// sound identifier
			pStrmTblPtr->bFlags			= SND_CLEAR_FLAG;	// Boolean Flag fields
			pStrmTblPtr->pWaveForm		= (WAVEFORMATEX*)NULL;// waveformatex information
			if ( pStrmTblPtr->pDSBuffer )
			{
				error = pStrmTblPtr->pDSBuffer->Release();
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

		pStrmTblPtr = NULL;
	}

	// returnt he result to the caller
exit:
	if ( pStrmTblPtr )
		nSndID = pStrmTblPtr->nSndID;

	return( nSndID );
}


///========================================================================
//	Function:		strmLoadRes()
//
//	Description:
//		Load a single resouce STRM
//
//	Input:			nResId			Resource ID containing strm data
//
//	Ouput:			nStrmID			strm ID assigned to this resource
//
///========================================================================

ULONG		strmLoadRes ( unsigned nResId )
{

#ifdef TRACK
TRACE("Entered: strmLoadRes()...\n" );
#endif


#ifdef TRACK
TRACE("Exiting: strmLoadRes()...\n" );
#endif

	return( 1L );
}


///========================================================================
//	Function:		strmLoadWav()
//
//	Description:
//		Load a single STRM from a .WAV
//
//	Input:			pWaveFilename	data file containing strm data
//					
//
//	Ouput:			nStrmID			strm ID assigned to this wave
//
///========================================================================

ULONG		strmLoadWav ( char* pWaveFilename )
{

#ifdef TRACK
TRACE("Entered: strmLoadWav()...\n" );
#endif

#ifdef TRACK
TRACE("Exiting: strmLoadWav()...\n" );
#endif

	return( 1L );
}


///========================================================================
//	Function:		strmCue()
//
//	Description:
//		Cue up a STRM by ID
//
//	Input:			nAudioID		audio Id number to be stored into
//
//	Ouput:			error			FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		strmCue ( ULONG nAudioID )
{
	STRM_SND*			pStrmTblPtr;
	SND*				pSndPtr;
	DWORD				dwDataLen1;
	DWORD				dwDataLen2;
    BYTE*				pDSBuffData1;
    BYTE*				pDSBuffData2;
	int					nSndIdx;
	unsigned			status;
	BOOL				error = TRUE;		// assume failure

	if ( !STRMenabled )
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
	pStrmTblPtr = strmFindID( nAudioID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to play a non-exitent nAudioID (%ld). [%s:%d]\n\n", 
			nAudioID, __FILE__, __LINE__ );
		goto exit;
	}

	// make sure we haven't already cued up
	if ( (pStrmTblPtr->bFlags & SND_CUED_FLAG) == SND_CUED_FLAG )
	{
		// already cue'd, exit and save time
		error = FALSE;
		goto exit;
	}

	status = sndFindSndID( pStrmTblPtr->nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, pStrmTblPtr->nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// since we're loading here, we can't of found the End Of Stream and
	// we don't have segments ready as yet.
    pStrmTblPtr->bFlags           &= ~SND_EOS_FLAG;
    pStrmTblPtr->nRemainingBytes   = 0;
    pStrmTblPtr->nRemainingBytes   = 0;
	pStrmTblPtr->dwNextWriteOffset = 0;
	pStrmTblPtr->dwPlayLast        = 0;
	pStrmTblPtr->dwProgress        = 0;

    // Lock the DS buffer
    error = pStrmTblPtr->pDSBuffer->Lock( 0, pStrmTblPtr->dwBufferSize,
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
	pStrmTblPtr->nSndOffset = pStrmTblPtr->nSndStart;

    // Write wave data to the DS buffer
	if ( dwDataLen1 )
	{
		if ( strmLoadData( pStrmTblPtr, (BYTE*)pDSBuffData1, dwDataLen1 ) )
		{
			// report an error
			TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );

			// Unlock the DS buffer
			error = pStrmTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
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
    error = pStrmTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
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
	pStrmTblPtr->bFlags |= SND_CUED_FLAG;
	pStrmTblPtr->bFlags &= ~SND_DONE_FLAG;

	// if we made it here, we were successful
	error = FALSE;
exit:
	return( error );

}

///========================================================================
//	Function:		strmCueSnd()
//
//	Description:
//		Cue up a STRM by SND ID
//
//	Input:			nSndID		Snd Id number to be stored into
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		strmCueSnd ( ULONG nSndID )
{
	STRM_SND*			pStrmTblPtr;
	SND*				pSndPtr;
	DWORD				dwDataLen1;
	DWORD				dwDataLen2;
    BYTE*				pDSBuffData1;
    BYTE*				pDSBuffData2;
	int					nSndIdx;
	unsigned			status;
	BOOL				error = TRUE;		// assume failure

	if ( !STRMenabled )
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
	pStrmTblPtr = strmFindSndID( nSndID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to play a non-exitent nSndID (%ld). [%s:%d]\n\n", 
			nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// make sure we haven't already cued up
	if ( (pStrmTblPtr->bFlags & SND_CUED_FLAG) == SND_CUED_FLAG )
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
    pStrmTblPtr->bFlags           &= ~SND_EOS_FLAG;
    pStrmTblPtr->nRemainingBytes   = 0;
	pStrmTblPtr->dwNextWriteOffset = 0;
	pStrmTblPtr->dwPlayLast        = 0;
	pStrmTblPtr->dwProgress        = 0;

    // Lock the DS buffer
    error = pStrmTblPtr->pDSBuffer->Lock( 0, pStrmTblPtr->dwBufferSize,
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
	pStrmTblPtr->nSndOffset = pStrmTblPtr->nSndStart;

    // Write wave data to the DS buffer
	if ( dwDataLen1 )
	{
		if ( strmLoadData( pStrmTblPtr, (BYTE*)pDSBuffData1, dwDataLen1 ) )
		{
			// report an error
			TRACE("ERROR: failed DSbuffer unlock (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );

			// Unlock the DS buffer
			error = pStrmTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
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
    error = pStrmTblPtr->pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
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
	pStrmTblPtr->bFlags |= SND_CUED_FLAG;
	pStrmTblPtr->bFlags &= ~SND_DONE_FLAG;

	// if we made it here, we were successful
	error = FALSE;
exit:
	return( error );

}

///========================================================================
//	Function:		strmPlaySnd()
//
//	Description:
//		Play a STRM sound by SND ID
//
//	Input:			nSndID			SND Id number to be played
//
//	Ouput:			none
//
///========================================================================

BOOL		strmPlaySnd ( ULONG nSndID )
{
	LONG				nMasterVolume = 0L;
#ifdef AUDIO_TIMER
	UINT				uTimerID;
#endif

	STRM_SND*		    pStrmTblPtr;
	SND*				pSndPtr;
	LPDIRECTSOUNDBUFFER pDSbuffer;
	int					nSndIdx;
	unsigned			status;
	BOOL				error = TRUE;		// assume failure

#ifdef DBG_AUDIO
	TRACE("strmPlaySnd( %s:%ld)\n", audioSndIDname( nSndID ), nSndID ); 
#endif

	if ( !STRMenabled )
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
	pStrmTblPtr = strmFindSndID( nSndID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
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
		TRACE("ERROR: stream file not open for strm ID (%ld). [%s:%d]\n\n", 
			nSndID, __FILE__, __LINE__ );

		// make sure the flags for this stream are clear
		pStrmTblPtr->bFlags = SND_CLEAR_FLAG;
		goto exit;
	}

	// stop this stream if its already playing
	if ( (pStrmTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		if ( strmStopSnd( nSndID ) )
		{
			// report an error
			TRACE("ERROR: failed to stop strm ID (%ld). [%s:%d]\n\n", 
				   nSndID, __FILE__, __LINE__ );

			// make sure the flags for this stream are clear
			pStrmTblPtr->bFlags = SND_CLEAR_FLAG;
			goto exit;
		}

		// make sure the stream is properly cue'd to the begining
		if ( strmCueSnd( nSndID ) )
		{
			// report an error
			TRACE("ERROR: failed to cue strm ID (%ld). [%s:%d]\n\n", 
				   nSndID, __FILE__, __LINE__ );

			// make sure the flags for this stream are clear
			pStrmTblPtr->bFlags = SND_CLEAR_FLAG;
			goto exit;
		}
	}

	// get the DirectSound Buffer
	pDSbuffer = pStrmTblPtr->pDSBuffer;
	if ( (pDSbuffer != NULL) && (pSndPtr->wavSnd.pSndFile != NULL) )
	{
		// reposition the buffer to the beginning
		pDSbuffer->SetCurrentPosition( 0 );

		// make sure the user hasn't turned voice off
		if ( STRMon )
			nMasterVolume = audioGetMasterVolume( SND_MUSIC_FLAG );
		SndSetVolumePercent( pStrmTblPtr->nSndID, nMasterVolume, FALSE );

		// now play it
		pDSbuffer->Play( 0, 0, DSBPLAY_LOOPING );
//		if ( (pStrmTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG)
//			pDSbuffer->Play( 0, 0, DSBPLAY_LOOPING );
//		else
//			pDSbuffer->Play( 0, 0, 0 );
	}
	else
	{
		// make sure the playing and installed flags for this stream are clear
		pStrmTblPtr->bFlags &= ~(SND_PLAYING_FLAG|SND_INSTALLED_FLAG);
		goto exit;
	}

#ifdef AUDIO_TIMER
	// Start a timer event. After the event has been activated, the timer will
	// make a callback to the STRM monitor routine.
	uTimerID = timeSetEvent( (STRM_PLAYBACK_TIMER_PERIOD/STRM_PLAYBACK_OVERSAMPLE),
							 STRM_PLAYBACK_TIMER_ACCURACY, (LPTIMECALLBACK)strmMonitor,
							 (DWORD)0, TIME_PERIODIC
						   );

	// if the timer was successfull installed, set the appropriate flag
	if ( uTimerID == 0 )
		goto exit;

	// remember this id for processing in the strm monitor
	pStrmTblPtr->uTimerID = uTimerID;

#ifdef TIMER_DEBUG
TRACE("strmPlay() new TimerID %d\n", pStrmTblPtr->uTimerID );
#endif

	pStrmTblPtr->bFlags  |= SND_INSTALLED_FLAG;

	// this stream should be playing happily along now
	pStrmTblPtr->bFlags |= SND_PLAYING_FLAG;

#else
	pStrmTblPtr->uTimerID = STRMtimerID++;
	pStrmTblPtr->bFlags  |= (SND_INSTALLED_FLAG|SND_PLAYING_FLAG);
#endif

	// now clear the CUE flag
	pStrmTblPtr->bFlags  &= ~SND_CUED_FLAG;

	// if we made it here we were successful
	error = FALSE;

#ifdef SND_DEBUG
TRACE( "Playing STRM SND: %s-%ld\n", audioSndIDname( nSndID ), nSndID );
#endif
 
exit:
	return( error );
}

///========================================================================
//	Function:		strmFade()
//
//	Description:
//		Fade in or out a STRM sound
//
//	Input:			nAudioID		audio Id number to be faded
//					nInOrOut		fade sound IN or OUT		
//
//	Ouput:			none
//
///========================================================================

BOOL		strmFade ( ULONG nAudioID, unsigned nInOrOut )
{
	STRM_SND*	pStrmTblPtr;
	BOOL			error = TRUE;		// assume a failure

	if ( !STRMenabled )
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
	pStrmTblPtr = strmFindID( nAudioID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
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
		pStrmTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade In bit
		pStrmTblPtr->bFlags |= SND_FADE_IN_FLAG;
	}
	else
	if ( nInOrOut == SND_FADE_OUT_FLAG )
	{
		// strip off the FADE BITS
		pStrmTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade Out bit
		pStrmTblPtr->bFlags |= SND_FADE_OUT_FLAG;
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
//	Function:		strmFadeSnd()
//
//	Description:
//		Fade in or out a STRM SND ID
//
//	Input:			nSndID			snd Id number to be faded
//					nInOrOut		fade sound IN or OUT		
//
//	Ouput:			none
//
///========================================================================

BOOL		strmFadeSnd ( ULONG nSndID, unsigned nInOrOut )
{
	STRM_SND*	pStrmTblPtr;
	BOOL		error = TRUE;		// assume a failure

	if ( !STRMenabled )
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
	pStrmTblPtr = strmFindSndID( nSndID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to fade a non-exitent nSndID (%ld). [%s:%d]\n\n", 
			nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// Set up the sound for fading
	if ( nInOrOut == SND_FADE_IN_FLAG )
	{
		// strip off the FADE BITS
		pStrmTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade In bit
		pStrmTblPtr->bFlags |= SND_FADE_IN_FLAG;
	}
	else
	if ( nInOrOut == SND_FADE_OUT_FLAG )
	{
		// strip off the FADE BITS
		pStrmTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade Out bit
		pStrmTblPtr->bFlags |= SND_FADE_OUT_FLAG;
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
//	Function:		strmStop()
//
//	Description:
//		stop a STRM sound by ID
//
//	Input:			nAudioID			audio Id number to be stop
//
//	Ouput:			none
//
///========================================================================

BOOL		strmStop ( ULONG nAudioID )
{
	STRM_SND*	pStrmTblPtr;
	BOOL		error = TRUE;		// assume a failure
   
#ifdef SNDCHK
	TRACE("strmStop( ID:%ld)\n",nAudioID ); 
#endif

	if ( !STRMenabled )
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
	pStrmTblPtr = strmFindID( nAudioID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		error = FALSE;
		goto exit;
	}

	// kill off the timer event controlling this stream
#ifdef AUDIO_TIMER
	if ( pStrmTblPtr->uTimerID )
	{
#ifdef TIMER_DEBUG
TRACE("strmStop() TimerID %d being killed\n", pStrmTblPtr->uTimerID );
#endif

		timeKillEvent( pStrmTblPtr->uTimerID );
	}
#endif
	pStrmTblPtr->uTimerID = 0;

	// uninstall this stream
	if ( (pStrmTblPtr->bFlags & SND_INSTALLED_FLAG) == SND_INSTALLED_FLAG )
		pStrmTblPtr->bFlags &= ~SND_INSTALLED_FLAG;

	// stop the sound
	if ( (pStrmTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// turn off the playing flag
		pStrmTblPtr->bFlags &= ~SND_PLAYING_FLAG;

		// stop the stream
		if ( sndStop( pStrmTblPtr->pDSBuffer ) != DS_OK )
			goto exit;	// error occurred
	}

	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		strmStopSnd()
//
//	Description:
//		stop a STRM sound by ID
//
//	Input:			nSndID			snd Id number to be stop
//
//	Ouput:			none
//
///========================================================================

BOOL		strmStopSnd( ULONG nSndID )
{
	STRM_SND*	pStrmTblPtr;
	BOOL		error = TRUE;		// assume a failure
   
#ifdef SNDCHK
	TRACE("strmStopSnd( ID:%ld)\n",nSndID ); 
#endif

	if ( !STRMenabled )
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
	pStrmTblPtr = strmFindSndID( nSndID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		error = FALSE;
		goto exit;
	}

	// kill off the timer event controlling this stream
#ifdef AUDIO_TIMER
	if ( pStrmTblPtr->uTimerID )
	{
#ifdef TIMER_DEBUG
TRACE("strmStopSnd() TimerID %d being killed\n", pStrmTblPtr->uTimerID );
#endif

		timeKillEvent( pStrmTblPtr->uTimerID );
	}
#endif
	pStrmTblPtr->uTimerID = 0;

	// uninstall this stream
	if ( (pStrmTblPtr->bFlags & SND_INSTALLED_FLAG) == SND_INSTALLED_FLAG )
		pStrmTblPtr->bFlags &= ~SND_INSTALLED_FLAG;

	// stop the sound
	if ( (pStrmTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// turn off the playing flag
		pStrmTblPtr->bFlags &= ~SND_PLAYING_FLAG;

		// stop the stream
		if ( sndStop( pStrmTblPtr->pDSBuffer ) != DS_OK )
			goto exit;	// error occurred
	}

	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		strmReset()
//
//	Description:
//		reset a STRM sound by ID
//
//	Input:			nAudioID			sound Id number to be reset
//
//	Ouput:			none
//
///========================================================================

BOOL		strmReset ( ULONG nAudioID )
{
	STRM_SND*	pStrmTblPtr;
	USHORT		bFlags;
	BOOL		error = TRUE;		// assume a failure
   
#ifdef SNDCHK
	TRACE("strmReset( ID:%ld)\n",nAudioID ); 
#endif

	if ( !STRMenabled )
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
	pStrmTblPtr = strmFindID( nAudioID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to stop a non-exitent nAudioID (%ld). [%s:%d]\n\n", 
			  nAudioID, __FILE__, __LINE__ );
		goto exit;
	}

	// kill off the timer event controlling this stream
#ifdef AUDIO_TIMER
	if ( pStrmTblPtr->uTimerID )
	{
#ifdef TIMER_DEBUG
TRACE("strmReset() TimerID %d being killed\n", pStrmTblPtr->uTimerID );
#endif

		timeKillEvent( pStrmTblPtr->uTimerID );
	}
#endif
	pStrmTblPtr->uTimerID = 0;

	// uninstall this stream
	if ( (pStrmTblPtr->bFlags & SND_INSTALLED_FLAG) == SND_INSTALLED_FLAG )
		pStrmTblPtr->bFlags &= ~SND_INSTALLED_FLAG;

	// stop the sound
	if ( (pStrmTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// turn off the playing flag
		pStrmTblPtr->bFlags &= ~SND_PLAYING_FLAG;

		// stop the stream
		if ( sndStop( pStrmTblPtr->pDSBuffer ) != DS_OK )
			goto exit;	// error occurred
	}

	// now set the flags
	bFlags = SND_SFX_FLAG;
	if ( (pStrmTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG )
		bFlags |= SND_LOOP_FLAG;
	pStrmTblPtr->bFlags &= ~bFlags;

	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		strmDelete()
//
//	Description:
//		Delete a STRM sound by ID
//
//	Input:			nAudioID		audio Id number to delete
//
//	Ouput:			none
//
///========================================================================

BOOL		strmDelete ( ULONG nAudioID )
{
	STRM_SND*	pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
	BOOL		error       = TRUE;		// assume a failure

#ifdef DBG_AUDIO
	char*		pAudioName;
#endif

	if ( !STRMenabled )
	{
		// no need to delete this
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
TRACE("strmDelete( A:%ld ) ", nAudioID );
#endif

#ifdef DBG_AUDIO
	pAudioName = audioIDname( nAudioID );
#endif

	// find the sound in the table
	pStrmTblPtr = strmFindID( nAudioID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		// no need to worry about this
		error = FALSE;
		goto exit;
	}

	// lock this sound
	pStrmTblPtr->bLock = TRUE;

	// free up this table entry
	if ( pStrmTblPtr->pDSBuffer != NULL )
	{
		error = pStrmTblPtr->pDSBuffer->Release();
		if ( error != DS_OK )
		{
			// report an error
			TRACE("ERROR:  failed to relase the DirectSoundbuffer (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
			goto exit;
		}
		pStrmTblPtr->pDSBuffer = NULL;
	}

	// now delete the snd
	sndDelete( pStrmTblPtr->nSndID );

	// re-initalize this entry
	//	pStrmTblPtr->bLock				= FALSE;		// CLEAR THIS AT END
	pStrmTblPtr->nAudioID			= SND_NULL_SND_ID;	// stream sound identifier
	pStrmTblPtr->nSndID			    = SND_NULL_SND_ID;	// sound identifier
	pStrmTblPtr->bFlags			    = SND_CLEAR_FLAG;	// Boolean Flag fields
	pStrmTblPtr->pWaveForm           = NULL;		// .wave info
	pStrmTblPtr->nSndStart          = 0;			// index into .snd or .wav file to read from
	pStrmTblPtr->nSndOffset         = 0;			// offset into file to reach sound chunk
													// this is filled at load time.
	pStrmTblPtr->nSndSize           = 0;			// size of raw data
	pStrmTblPtr->uTimerID           = 0;			// play interrupt timer ID
	pStrmTblPtr->dwBufferSize       = 0;            // Size of the entire buffer
	pStrmTblPtr->dwBufferSegSize    = 0;            // Size of one buffer segment
	pStrmTblPtr->dwNextWriteOffset  = 0;            // Offset to next buffer segment
	pStrmTblPtr->dwPlayLast         = 0;            // Used with above to show prog
	pStrmTblPtr->dwProgress         = 0;            // Used with above to show prog
	pStrmTblPtr->nRemainingBytes    = 0;			// Segments 'til timer shutdown
	pStrmTblPtr->nSndLink           = SND_NULL_SND_ID;	// Link to another strm ID

	// if we got here we we're successful
	--STRMsoundsActive;

#ifdef DBG_AUDIO
	TRACE("strmDelete( A:%s-a:%ld )\n", pAudioName, nAudioID );
#endif

	error = FALSE;
exit:
	// unlock this sound
	if ( pStrmTblPtr != (STRM_SND*)SND_NULL_SND_PTR )
		pStrmTblPtr->bLock = FALSE;

#if 0
	if ( error )
		TRACE("strmDelete( A:%s-a:%ld ) ERROR\n", pAudioName, nAudioID );
#endif

	return( error );
}

///========================================================================
//	Function:		strmDeleteSnd()
//
//	Description:
//		Delete a STRM sound by sndID
//
//	Input:			nSndID		snd Id number to delete
//
//	Ouput:			none
//
///========================================================================

BOOL		strmDeleteSnd( ULONG nSndID )
{
	STRM_SND*	pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
	BOOL		error       = TRUE;		// assume a failure

#ifdef DBG_AUDIO
	char*		pAudioName;
#endif

	if ( !STRMenabled )
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

#ifdef AUDIO_DBG
	TRACE("strmDeleteSnd( A:%s-S:%ld )\n", audioSndIDname( nSndID ), nSndID );
#endif

#ifdef DBG_AUDIO
	pAudioName = audioSndIDname( nSndID );
#endif

	// find the sound in the table
	pStrmTblPtr = strmFindSndID( nSndID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		// no need to worry about this
		error = FALSE;
		goto exit;
	}

	// lock this sound
	pStrmTblPtr->bLock = TRUE;

	// kill off the timer event controlling this stream
#ifdef AUDIO_TIMER
	if ( pStrmTblPtr->uTimerID )
	{
#ifdef TIMER_DEBUG
TRACE("strmDeleteSnd() TimerID %d being killed\n", pStrmTblPtr->uTimerID );
#endif

		timeKillEvent( pStrmTblPtr->uTimerID );
	}
#endif
	pStrmTblPtr->uTimerID = 0;

	// uninstall this stream
	if ( (pStrmTblPtr->bFlags & SND_INSTALLED_FLAG) == SND_INSTALLED_FLAG )
		pStrmTblPtr->bFlags &= ~SND_INSTALLED_FLAG;

	// stop the sound
	if ( (pStrmTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// turn off the playing flag
		pStrmTblPtr->bFlags &= ~SND_PLAYING_FLAG;

		// stop the stream
		if ( sndStop( pStrmTblPtr->pDSBuffer ) != DS_OK )
			goto exit;	// error occurred
	}

	// free up this table entry
	if ( pStrmTblPtr->pDSBuffer != NULL )
	{
		error = pStrmTblPtr->pDSBuffer->Release();
		if ( error != DS_OK )
		{
			// report an error
			TRACE("ERROR:  failed to relase the DirectSoundbuffer (%s) [%s:%d]\n\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
			goto exit;
		}
		pStrmTblPtr->pDSBuffer = NULL;
	}

	// now delete the snd
	sndDelete( pStrmTblPtr->nSndID );

	// re-initalize this entry
	//	pStrmTblPtr->bLock				= FALSE;		// CLEAR THIS AT END
	pStrmTblPtr->nAudioID			= SND_NULL_SND_ID;	// stream sound identifier
	pStrmTblPtr->nSndID			    = SND_NULL_SND_ID;	// sound identifier
	pStrmTblPtr->nStrmID			= SND_NULL_SND_ID;	// sound identifier
	pStrmTblPtr->bFlags			    = SND_CLEAR_FLAG;	// Boolean Flag fields
	pStrmTblPtr->pWaveForm          = NULL;				// .wave info
	pStrmTblPtr->nSndStart          = 0;				// index into .snd or .wav file to read from
	pStrmTblPtr->nSndOffset         = 0;				// offset into file to reach sound chunk
														// this is filled at load time.
	pStrmTblPtr->nSndSize           = 0;				// size of raw data
	pStrmTblPtr->uTimerID           = 0;				// play interrupt timer ID
	pStrmTblPtr->dwBufferSize       = 0;				// Size of the entire buffer
	pStrmTblPtr->dwBufferSegSize    = 0;				// Size of one buffer segment
	pStrmTblPtr->dwNextWriteOffset  = 0;				// Offset to next buffer segment
	pStrmTblPtr->dwPlayLast         = 0;				// Used with above to show prog
	pStrmTblPtr->dwProgress         = 0;				// Used with above to show prog
	pStrmTblPtr->nRemainingBytes    = 0;				// Segments 'til timer shutdown
	pStrmTblPtr->nSndLink           = SND_NULL_SND_ID;	// Link to another strm ID

	// if we got here we we're successful
	--STRMsoundsActive;

#ifdef	SND_DEBUG
TRACE( "STRMsoundsActive = %d   Decremented\n", STRMsoundsActive );
#endif

	error = FALSE;

#ifdef DBG_AUDIO
	TRACE("strmDeleteSnd( A:%s-S:%ld )\n", pAudioName, nSndID );
#endif

exit:

	// unlock this sound
	if ( pStrmTblPtr != (STRM_SND*)SND_NULL_SND_PTR )
		pStrmTblPtr->bLock = FALSE;

#if 0
	if ( error )
		TRACE("strmDeleteSnd( A:%s-S:%ld ) ERROR\n", pAudioName, nSndID );
#endif

	return( error );
}

///========================================================================
//	Function:		strmClose()
//
//	Description:
//		Close down an STRM .snd file
//
//	Input:			nFileID			file ID to close
//
//	Ouput:			none
//
///========================================================================

void		strmClose ( unsigned nFileID )
{

	if ( !STRMenabled )
		return;

	sndDeleteFile( nFileID );
	pSTRMfile = NULL;
}


///========================================================================
//	Function:		strmGetFrequency()
//
//	Description:
// 		Get the STRM sound frequency level (effect pitch)
//
//	Input:			nStrmID			sound Id number to retrieve pan from
//
//	Ouput:			nFrequency		current STRM frequency setting
//
///========================================================================

LONG		strmGetFrequency ( ULONG nStrmID )
{
	LONG			nFrequency;
	STRM_SND*	pStrmTblPtr;

	if ( !STRMenabled )
		return( 0 );

	if ( nStrmID == SND_NULL_SND_ID )
		return( 0 );

	// find the sound in the table
	pStrmTblPtr = strmFindID( nStrmID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
		nFrequency = 0;
	else				// Get the FREQUENCY value
	if ( sndGetFrequency( pStrmTblPtr->pDSBuffer, &nFrequency ) )
		nFrequency = 0;
	   
	return( nFrequency );
}


///========================================================================
//	Function:		strmSetFrequency()
//
//	Description:
// 		Set the STRM sound requency level (effect pitch)
//
//	Input:			nStrmID			sound Id number to retrieve pan from
//					nFrequency		volume setting to apply
//
//	Ouput:			none
//
///========================================================================

BOOL		strmSetFrequency ( ULONG nStrmID, LONG nFrequency )
{
	STRM_SND*	pStrmTblPtr;
	BOOL		error = TRUE;		// assume failed

	if ( !STRMenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nStrmID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pStrmTblPtr = strmFindID( nStrmID );
   if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
		goto exit;

	// set the Frequency value
	if ( sndSetFrequency( pStrmTblPtr->pDSBuffer, nFrequency ) )
		goto exit;
	   
	// If we made it here we did everything ok
	error = FALSE;
exit:
	return( error );
}


///========================================================================
//	Function:		strmGetVolume()
//
//	Description:
// 		Get the STRM sound volume levels:
//
//	Input:			nStrmID			sound Id number to retrieve pan from
//
//	Ouput:			nVolume			current STRM volume setting
//
///========================================================================

LONG		strmGetVolume ( ULONG nStrmID ) 
{
	LONG		nVolume;
	STRM_SND*	pStrmTblPtr;

	if ( !STRMenabled )
		return( 0 );

	if ( nStrmID == SND_NULL_SND_ID )
		return( 0 );

	// find the sound in the table
	pStrmTblPtr = strmFindID( nStrmID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
		nVolume = 0;
	else				// Get the VOLUME value
	if ( sndGetVolume( pStrmTblPtr->pDSBuffer, &nVolume ) )
		nVolume = 0;

	return( nVolume );
}


///========================================================================
//	Function:		strmSetVolume()
//
//	Description:
// 		Set the STRM sound volume levels:
//
//	Input:			nSndID			sound Id number to retrieve pan from
//					nVolume			volume setting to apply
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL		strmSetVolume ( ULONG nSndID, LONG nVolume )
{
	STRM_SND*	pStrmTblPtr;
	BOOL		error = TRUE;		// assume failed

	if ( !STRMenabled )
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
	pStrmTblPtr = strmFindSndID( nSndID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
		goto exit;

	// set the Volume value
	if ( sndSetVolume( pStrmTblPtr->pDSBuffer, nVolume ) )
		goto exit;
	   
	// If we made it here we did everything ok
	error = FALSE;
exit:
	return( error );
}


///========================================================================
//	Function:		strmGetPan()
//
//	Description:
// 		Get the STRM sound pan level
//
//	Input:			nStrmID			sound Id number to retrieve pan from
//
//	Ouput:			nPan			current STRM pan setting
//
///========================================================================

LONG		strmGetPan ( ULONG nStrmID )
{
	LONG		nPan;
	STRM_SND*	pStrmTblPtr;

	if ( !STRMenabled )
		return( 0 );

	if ( nStrmID == SND_NULL_SND_ID )
		return( 0 );

	// find the sound in the table
	pStrmTblPtr = strmFindID( nStrmID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
		nPan = 0;
	else			// Get the PAN value
	if ( sndGetPan( pStrmTblPtr->pDSBuffer, &nPan ) )
		nPan = 0;
	   
	return( nPan );
}


///========================================================================
//	Function:		strmSetPan()
//
//	Description:
// 		Set the STRM sound pan level
//
//	Input:			nStrmID			sound Id number to apply pan to
//					nPan			pan setting to apply
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL		strmSetPan ( ULONG nStrmID, LONG nPan )
{
	STRM_SND*	pStrmTblPtr;
	BOOL		error = TRUE;		// assume failed

	if ( !STRMenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nStrmID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pStrmTblPtr = strmFindID( nStrmID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
		goto exit;

	// set the PAN value
	if ( sndSetPan( pStrmTblPtr->pDSBuffer, nPan ) )
		goto exit;
	   
	// If we made it here we did everything ok
	error = FALSE;
exit:
	return( error );
}


///========================================================================
//	Function:		strmMonitor()
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
void CALLBACK strmMonitor ( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 )
#else
void		  strmMonitor ( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 )
#endif
{
	STRM_SND*			pStrmTblPtr;

	// make sure we have sounds that are active
	if ( !STRMenabled )
		goto exit;

	if ( !(STRMsoundsActive+VOICEsoundsActive) )
		goto exit;

	if ( !uTimerID )
		goto exit;

	// find the sound in the table
	pStrmTblPtr = strmFindTimerID( uTimerID );
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
			goto exit;

	// are we already processing?
	if ( (pStrmTblPtr->bFlags & SND_TIMER_FLAG) == SND_TIMER_FLAG )
		goto exit;

	// check to see if this sound is locked
	if ( pStrmTblPtr->bLock )
		goto cleanUp;

	if ( pStrmTblPtr->nAudioID == SND_NULL_SND_ID )
	{
#ifdef AUDIO_TIMER
		if ( pStrmTblPtr->uTimerID )
		{
#ifdef TIMER_DEBUG
TRACE("strmMonitor() TimerID %d being killed\n", pStrmTblPtr->uTimerID );
#endif

			timeKillEvent( pStrmTblPtr->uTimerID );
		}
#endif
		pStrmTblPtr->uTimerID = 0;
		pStrmTblPtr->bFlags |= SND_DONE_FLAG;
		goto cleanUp;
	}

#ifdef DBG_AUDIO
	char*	pAudioName;
	pAudioName = audioIDname( pStrmTblPtr->nAudioID );
	if ( strcmp( pAudioName, "LOSE_MUSIC" ) == 0 )
		TRACE( "strmMonitor( %s )\n", audioIDname( pStrmTblPtr->nAudioID ) );
#endif

	// we can't be interrupted from this point on
	pStrmTblPtr->bFlags |= SND_TIMER_FLAG;
	goto exit;

cleanUp:

	// signify that we are no longer occupying the timer interrupt
	pStrmTblPtr->bFlags &= ~SND_TIMER_FLAG;

exit:
	return;
}

///========================================================================
//	Function:		strmUpdate()
//
//	Description:
//		Update STRM processing, updating the playback buffer at regular
//		intervals.
//
//	Input:			pStrmTblPtr		stream to be updated
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

void strmUpdate ( STRM_SND* pStrmTblPtr )
{
	STRM_SND*			pStrmLinkPtr;
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
	pDSBuffer = pStrmTblPtr->pDSBuffer;
	if ( pDSBuffer == NULL )
		goto cleanUp;

#ifdef DBG_AUDIO
	char*	pAudioName;
	pAudioName = audioIDname( pStrmTblPtr->nAudioID );
	if ( strcmp( pAudioName, "LOSE_MUSIC" ) == 0 )
		TRACE( "strmUpdate( %s )\n", audioIDname( pStrmTblPtr->nAudioID ) );
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
//	if ( nPlayPos < pStrmTblPtr->dwNextWriteOffset )
	if ( nPlayPos < pStrmTblPtr->dwPlayLast )
	{
		// calculate how many writable bytes there are behind the play cursor
		nPlayLength = (pStrmTblPtr->dwBufferSize - pStrmTblPtr->dwPlayLast + nPlayPos);
//		nPlayLength = (pStrmTblPtr->dwBufferSegSize - pStrmTblPtr->dwNextWriteOffset + nPlayPos);
//		nPlayLength = (pStrmTblPtr->dwBufferSize - pStrmTblPtr->dwNextWriteOffset + nPlayPos);
	}
	else
	{
		// calculate how many writable bytes there are after the play cursor
		nPlayLength = (nPlayPos - pStrmTblPtr->dwPlayLast);
//		nPlayLength = (nPlayPos - pStrmTblPtr->dwNextWriteOffset);
	}
	pStrmTblPtr->dwProgress += nPlayLength;
	pStrmTblPtr->dwPlayLast  = nPlayPos;

#ifdef DBG_AUDIO
	pAudioName = audioIDname( pStrmTblPtr->nAudioID );
	if ( strcmp( pAudioName, "LOSE_MUSIC" ) == 0 )
	{
		TRACE("\n\nnPlayPos = %ld  nPlayLength = %ld dwNextWriteOffset = %ld\n",
			nPlayPos, nPlayLength, pStrmTblPtr->dwNextWriteOffset );
//		strmDump( pStrmTblPtr );
	}
#endif

	// if the play cursor is at the same spot as the last call, there are two possibilities.
	// The first is that we were called extremely late and happened to land on an integer
	// number of complete buffer cycles. This is not very likely. The other is that the
	// play cursor didn't move. Since we're oversampling, this is very likely. In this
	// case, we should bail.
	if ( pStrmTblPtr->dwNextWriteOffset == nPlayPos )
	{
		// can't write yet...
#ifdef DBG_AUDIO
		TRACE( "can't write yet...(%ld==%ld)\n", pStrmTblPtr->dwNextWriteOffset, nPlayPos);
//		strmDump( pStrmTblPtr );
#endif

		goto cleanUp;
	}

	// Have we found the end of the stream and passed the buffer end?
	if ( ((pStrmTblPtr->bFlags & SND_EOS_FLAG) == SND_EOS_FLAG ) &&
		 !(pStrmTblPtr->nRemainingBytes)
	   )
	{
		// see if we're done playing
		if ( (pStrmTblPtr->bFlags & SND_DONE_FLAG) != SND_DONE_FLAG )
		{
			if ( strmStopSnd( pStrmTblPtr->nSndID ) )
			{
				// report an error
				TRACE("ERROR: failed to stop strm ID (%ld:%ld). [%s:%d]\n\n", 
					   pStrmTblPtr->nAudioID, pStrmTblPtr->nSndID, __FILE__, __LINE__ );

				// make sure the flags for this stream are clear
				pStrmTblPtr->bFlags = SND_CLEAR_FLAG;
				goto cleanUp;
			}

			// check to see if this is a looping stream
			if ( ((pStrmTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG) &&
				 ((pStrmTblPtr->bFlags & SND_DELETE_FLAG) != SND_DELETE_FLAG) )
			{
				if ( strmCueSnd( pStrmTblPtr->nSndID ) )
				{
					// report an error
					TRACE("ERROR: failed to cue up (sndID: %ld). [%s:%d]\n\n", 
						   pStrmTblPtr->nSndID, __FILE__, __LINE__ );

					// make sure the flags for this stream are clear
					pStrmTblPtr->bFlags = SND_CLEAR_FLAG;
					goto cleanUp;
				}

				if ( strmPlaySnd( pStrmTblPtr->nSndID ) )
				{
					// report an error
					TRACE("ERROR: failed to startup link (sndID: %ld). [%s:%d]\n\n", 
						   pStrmTblPtr->nSndID, __FILE__, __LINE__ );

					// make sure the flags for this stream are clear
					pStrmTblPtr->bFlags = SND_CLEAR_FLAG;
					goto cleanUp;
				}

				// clear the cue'd flag
				pStrmTblPtr->bFlags &= ~SND_CUED_FLAG;
			}
			else
			{
				pStrmTblPtr->bFlags |= SND_DONE_FLAG;

				// check to see if this stream is linked to another
				if ( pStrmTblPtr->nSndLink != SND_NULL_SND_ID )
				{
					// start up the next link
					pStrmLinkPtr = strmFindID(pStrmTblPtr->nSndLink);
					if ( strmCueSnd( pStrmLinkPtr->nSndID ) )
					{
						// report an error
						TRACE("ERROR: failed to cue up (sndID: %ld). [%s:%d]\n\n", 
							   pStrmLinkPtr->nSndID, __FILE__, __LINE__ );

						// make sure the flags for this stream are clear
						pStrmLinkPtr->bFlags = SND_CLEAR_FLAG;
						goto cleanUp;
					}

					if ( strmPlaySnd( pStrmLinkPtr->nSndID ) )
					{
						// report an error
						TRACE("ERROR: failed to startup link (sndID: %ld). [%s:%d]\n\n", 
							   pStrmLinkPtr->nSndID, __FILE__, __LINE__ );

						// make sure the flags for this stream are clear
						pStrmLinkPtr->bFlags = SND_CLEAR_FLAG;
						goto cleanUp;
					}

					// clear the cue'd flag
					pStrmLinkPtr->bFlags &= ~SND_CUED_FLAG;
				}
			}
		}

		goto cleanUp;
	}

	// If we've found the end of the stream, then we've finished reading in
	// the file. But we need to wait until the buffer's play cursor passes
	// the point we were at when we found out we were done reading.
	if ( ((pStrmTblPtr->bFlags & SND_EOS_FLAG) == SND_EOS_FLAG ) &&
		 (pStrmTblPtr->nRemainingBytes)
	   )
	{
#ifdef	SNDCHK
		TRACE("...EOS and %d remaining bytes...\n",
				pStrmTblPtr->nRemainingBytes );
#endif

		// reduce the number of bytes we have to wait until we can safely
		// terminate the timer associated with this stream.
		if ( nPlayLength > pStrmTblPtr->nRemainingBytes )
			pStrmTblPtr->nRemainingBytes = 0;
		else
			pStrmTblPtr->nRemainingBytes -= nPlayLength;

		error = pDSBuffer->Lock( pStrmTblPtr->dwNextWriteOffset,
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
		if (pStrmTblPtr->pWaveForm->wBitsPerSample == 8)
			memset( pDSBuffData1, 128, dwDataLen1);
		else
		// if the sample was 16 bits fill with 0
		if (pStrmTblPtr->pWaveForm->wBitsPerSample == 16)
			memset( pDSBuffData1, 0, dwDataLen1);

		if ( dwDataLen1 && dwDataLen2 )
		{
			// if the sample was 8 bits fill with 128
			if (pStrmTblPtr->pWaveForm->wBitsPerSample == 8)
				memset( pDSBuffData2, 128, dwDataLen2);
			else
			// if the sample was 16 bits fill with 0
			if (pStrmTblPtr->pWaveForm->wBitsPerSample == 16)
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
		pStrmTblPtr->dwNextWriteOffset += nPlayLength;
		if (pStrmTblPtr->dwNextWriteOffset >= pStrmTblPtr->dwBufferSize)
			pStrmTblPtr->dwNextWriteOffset -= pStrmTblPtr->dwBufferSize;
//		pStrmTblPtr->dwProgress += nPlayLength;

		goto cleanUp;
	}

	// now lock the segment of memory that is behind the play cursor
	error = pDSBuffer->Lock( pStrmTblPtr->dwNextWriteOffset,
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
	if ( dwDataLen1 && ((pStrmTblPtr->bFlags & SND_DONE_FLAG) != SND_DONE_FLAG) )
		strmLoadNextData( pStrmTblPtr, (BYTE*)pDSBuffData1, dwDataLen1, nPlayPos );
	else
	if ( dwDataLen1 && ((pStrmTblPtr->bFlags & SND_DONE_FLAG) == SND_DONE_FLAG) )
	{
		// The done playing flag is set before the end of the wave file is
		// encountered. It tells us to cut this stream off and play nothing
		// in case it takes the caller a couple of interrupts to shut off
		// the timer.

		//Set the appropriate silence value
		// if the sample was 8 bits fill with 128
		if (pStrmTblPtr->pWaveForm->wBitsPerSample == 8)
			memset( pDSBuffData1, 128, dwDataLen1);
		else
		// if the sample was 16 bits fill with 0
		if (pStrmTblPtr->pWaveForm->wBitsPerSample == 16)
			memset( pDSBuffData1, 0, dwDataLen1);

	}

	// read in the next segment of data into the buffer, that is if the
	// is is still playing.
	if ( dwDataLen2 && ((pStrmTblPtr->bFlags & SND_DONE_FLAG) != SND_DONE_FLAG) )
	{
		ASSERT( pStrmTblPtr->nAudioID != SND_NULL_SND_ID );
		// load in the next buffer's worth of data
		strmLoadNextData( pStrmTblPtr, (BYTE*)pDSBuffData2, dwDataLen2, nPlayPos );
	}
	else
	if ( dwDataLen2 && ((pStrmTblPtr->bFlags & SND_DONE_FLAG) == SND_DONE_FLAG) )
	{
		// The done playing flag is set before the end of the wave file is
		// encountered. It tells us to cut this stream off and play nothing
		// in case it takes the caller a couple of interrupts to shut off
		// the timer.

		//Set the appropriate silence value
		// if the sample was 8 bits fill with 128
		if (pStrmTblPtr->pWaveForm->wBitsPerSample == 8)
			memset( pDSBuffData2, 128, dwDataLen2);
		else
		// if the sample was 16 bits fill with 0
		if (pStrmTblPtr->pWaveForm->wBitsPerSample == 16)
			memset( pDSBuffData2, 0, dwDataLen2);
	}

	// Unlock the DS buffer
	pDSBuffer->Unlock( (LPVOID)pDSBuffData1, dwDataLen1,
					   (LPVOID)pDSBuffData2, dwDataLen2
					 );

	// update the next write positions
	pStrmTblPtr->dwNextWriteOffset += nPlayLength;
	if (pStrmTblPtr->dwNextWriteOffset >= pStrmTblPtr->dwBufferSize)
		pStrmTblPtr->dwNextWriteOffset -= pStrmTblPtr->dwBufferSize;

cleanUp:

	// signify that we are no longer occupying the timer interrupt
	pStrmTblPtr->bFlags &= ~SND_TIMER_FLAG;

	// if this stream is done, set its volume to off
	if ( (pStrmTblPtr->bFlags & SND_DONE_FLAG) == SND_DONE_FLAG )
		SndSetVolumePercent( pStrmTblPtr->nSndID, 0, FALSE );
	return;
}

///========================================================================
//	Function:		strmLoadData()
//
//	Description:
//		read in a buffer segment's worth of data
//
//	Input:			pStrmTblPtr		STRM sound processing
//					nMaxLen			max buffer segment length
//					
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL	strmLoadData ( STRM_SND* pStrmTblPtr, BYTE* pDSBuffData, DWORD nMaxLen )
{
	SND*				pSndPtr;
	FILE*				pFilePtr;
	DWORD				dwLen;
	DWORD				dwReadLen;
	DWORD				dwLeftToRead;
    BYTE*				pTmpData;
	int					nSndIdx;
	unsigned			status;
	BOOL				error = TRUE;		// assume failure

#ifdef	SNDCHK
	TRACE("strmLoadData( ID:%ld )...\n", pStrmTblPtr->nSndID );
#endif

	if ( !STRMenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( pStrmTblPtr->nSndID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// there might be more than one sound in the file, make sure we
	// we don't read past the end of the this particular sound
	if ( (LONG)nMaxLen > pStrmTblPtr->nSndSize )
		dwReadLen = pStrmTblPtr->nSndSize;
	else
		dwReadLen = nMaxLen;

	// get the sound data
	status = sndFindSndID( pStrmTblPtr->nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, pStrmTblPtr->nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// retrieve the file pointer
	pFilePtr = pSndPtr->wavSnd.pSndFile;

	if ( fseek( pFilePtr, pStrmTblPtr->nSndStart, SEEK_SET) )
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
		if ( (pStrmTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG )
		{
			// if the file is shorter than the buffer and we're looping. we need to
			// read the file in again so that we don't get a block of silence before
			// the timer loops playback.
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
				if ( fseek( pFilePtr, pStrmTblPtr->nSndStart, SEEK_SET) )
				{
					// report an error
					TRACE("ERROR: fseek failure. [%s:%d]\n", 
						__FILE__, __LINE__ );
					goto exit;
				}
				dwLen = (long)fread( (void*)pTmpData, 1, dwReadLen, pFilePtr );
			} while( dwLen && (dwLen < dwLeftToRead) );
		}
		else
		{
			// zero out the rest of this block
			// if the sample was 8 bits fill with 128
			if (pStrmTblPtr->pWaveForm->wBitsPerSample == 8)
				memset( (pDSBuffData+dwLen), 128, (nMaxLen - dwLen));
			else
			// if the sample was 16 bits fill with 0
			if (pStrmTblPtr->pWaveForm->wBitsPerSample == 16)
				memset( (pDSBuffData+dwLen), 0, (nMaxLen - dwLen));

			// we have the end of the stream, enable play completion detection
			// code at the beginning of the next call.
			pStrmTblPtr->bFlags |= SND_EOS_FLAG;

			// here the number of bytes remaining equals the data readin
			pStrmTblPtr->nRemainingBytes = dwReadLen;
		}
	}

	// save this location in the file incase we need to reload
	pStrmTblPtr->nSndOffset = ftell( pFilePtr );

	// set up the next write position
	pStrmTblPtr->dwNextWriteOffset += dwReadLen;
	if (pStrmTblPtr->dwNextWriteOffset >= pStrmTblPtr->dwBufferSize)
		pStrmTblPtr->dwNextWriteOffset -= pStrmTblPtr->dwBufferSize;

	// mark this stream as cue'd
	pStrmTblPtr->bFlags |= SND_CUED_FLAG;

	// made it here, we were successful
	error = FALSE;
exit:

	return( error );
}


///========================================================================
//	Function:		strmLoadNextData()
//
//	Description:
//		read in a buffer segment's worth of data
//
//	Input:			pStrmTblPtr		STRM sound processing
//					pDSBuffData		where to load data
//					nMaxLen			max buffer segment length
//					nPlayPos		play cursor position in buffer
//					
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL	strmLoadNextData ( STRM_SND* pStrmTblPtr, BYTE* pDSBuffData, DWORD nMaxLen, DWORD nPlayPos )
{
	SND*				pSndPtr;
	FILE*				pFilePtr;
	DWORD				dwLen;
	DWORD				dwReadLen;
	DWORD				dwLeftToRead;
	int					nSndIdx;
    BYTE*				pTmpData;
	unsigned			status;
	BOOL				error = TRUE;		// assume failure

#ifdef	DBG_AUDIO
	char*	pAudioName;

	pAudioName = audioIDname( pStrmTblPtr->nAudioID );
	if ( strcmp( pAudioName, "LOSE_MUSIC" ) == 0 )
	{
		TRACE("strmLoadNextData( %s:%ld:%ld )...\n",
			pAudioName, pStrmTblPtr->nAudioID, pStrmTblPtr->nSndID );
	}
#endif

	if ( !STRMenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( pStrmTblPtr->nSndID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// there might be more than one sound in the file, make sure we
	// we don't read past the end of the this particular sound
	dwLen = pStrmTblPtr->nSndSize - (pStrmTblPtr->nSndOffset - pStrmTblPtr->nSndStart);
	if ( (long)nMaxLen > (long)dwLen )
		dwReadLen = dwLen;
	else
		dwReadLen = nMaxLen;

#ifdef	SNDCHK
	TRACE("strmLoadNextData( ID:%ld )...\n", pStrmTblPtr->nSndID );
	TRACE("                 MaxLen  = %ld\n", nMaxLen );
	TRACE("                 ReadLen = %ld\n", dwReadLen );
#endif

	// get the sound data
	status = sndFindSndID( pStrmTblPtr->nSndID, &pSndPtr, &nSndIdx );
	if ( (status == SND_BAD_STATUS) || (pSndPtr == (SND*)SND_NULL_SND_PTR) )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, pStrmTblPtr->nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// retrieve the file pointer
	pFilePtr = pSndPtr->wavSnd.pSndFile;

	// remember that there might be more than one stream in the data file
	// cross check by comparing the existing offset with the size and start
	// offset. Otherwise look for a true end of file.
	if ( (pStrmTblPtr->bFlags & SND_EOS_FLAG) != SND_EOS_FLAG )
	{
		if ( pStrmTblPtr->nSndOffset >= (pStrmTblPtr->nSndStart + pStrmTblPtr->nSndSize) )
		{
#ifdef	SNDCHK
TRACE("...nSndSize exceeded...\n" );
#endif
			// zero out the rest of this block
			// if the sample was 8 bits fill with 128
			if (pStrmTblPtr->pWaveForm->wBitsPerSample == 8)
				memset( pDSBuffData, 128, nMaxLen);
			else
			// if the sample was 16 bits fill with 0
			if (pStrmTblPtr->pWaveForm->wBitsPerSample == 16)
				memset( pDSBuffData, 0, nMaxLen);

			// first set the EOS flag so we can terminate loading
			pStrmTblPtr->bFlags |= SND_EOS_FLAG;

			// handle wrapping in this circular buffer
			if ( nPlayPos > pStrmTblPtr->dwNextWriteOffset )
			{
				pStrmTblPtr->nRemainingBytes = (pStrmTblPtr->dwNextWriteOffset
												+ pStrmTblPtr->dwBufferSize
												- nPlayPos
											   );
			}
			else
			{
				pStrmTblPtr->nRemainingBytes = (pStrmTblPtr->dwNextWriteOffset
												- nPlayPos
											   );
			}

			goto cleanup;
		}
	}

	// find the next read point in the stream data
	if ( fseek( pFilePtr, pStrmTblPtr->nSndOffset, SEEK_SET) )
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
		if ( (pStrmTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG )
		{
#ifdef	SNDCHK
TRACE("...filling buffer (looping)...\n" );
#endif

			// if the file is shorter than the buffer and we're looping. we need to
			// read the file in again so that we don't get a block of silence before
			// the timer loops playback.
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
				if ( fseek( pFilePtr, pStrmTblPtr->nSndOffset, SEEK_SET) )
				{
					// report an error
					TRACE("ERROR: fseek failure. [%s:%d]\n", 
						__FILE__, __LINE__ );
					goto exit;
				}
				dwLen = (long)fread( (void*)pTmpData, 1, dwReadLen, pFilePtr );
			} while( dwLen && (dwLen < dwLeftToRead) );
		}
		else
		{
#ifdef	SNDCHK
TRACE("...EOS encountered...\n" );
#endif

			// zero out the rest of this block
			// if the sample was 8 bits fill with 128
			if (pStrmTblPtr->pWaveForm->wBitsPerSample == 8)
				memset( (pDSBuffData+dwLen), 128, (UINT)(nMaxLen - dwLen));
			else
			// if the sample was 16 bits fill with 0
			if (pStrmTblPtr->pWaveForm->wBitsPerSample == 16)
				memset( (pDSBuffData+dwLen), 0, (UINT)(nMaxLen - dwLen));

			// we have the end of the stream, enable play completion detection
			// code at the beginning of the next call.
			pStrmTblPtr->bFlags |= SND_EOS_FLAG;

			// handle wrapping in this circular buffer
			if ( nPlayPos > pStrmTblPtr->dwNextWriteOffset )
			{
				pStrmTblPtr->nRemainingBytes = (pStrmTblPtr->dwNextWriteOffset
												+ pStrmTblPtr->dwBufferSize
												- nPlayPos
											   );
			}
			else
			{
				pStrmTblPtr->nRemainingBytes = (pStrmTblPtr->dwNextWriteOffset
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
	pStrmTblPtr->nSndOffset = ftell( pFilePtr );

cleanup:
	// made it here, we were successful
	error = FALSE;
exit:
	return( error );
}


///========================================================================
//	Function:		strmFindID()
//
//	Description:
//		Locate a STRM sound ID in the STRM lookup table
//
//	Input:			nAudioID		audio Id number to apply pan to
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

STRM_SND* strmFindID ( ULONG nAudioID )
{
	STRM_SND*	pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
	unsigned	index;

	if ( !STRMenabled )
		goto exit;

	if ( nAudioID == SND_NULL_SND_ID )
		goto exit;

	// find the sound in the table
	pStrmTblPtr = STRMlookupTable;
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
		goto exit;

	index      = 0;
	while ( (index<STRMmaxSounds) && (pStrmTblPtr->nAudioID != nAudioID) )
	{
		++index;
		++pStrmTblPtr;
	}
   
	// did we find it ?
	if ( index == STRMmaxSounds )
		pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
exit:   
	return( pStrmTblPtr );    
}

///========================================================================
//	Function:		strmFindSndID()
//
//	Description:
//		Locate a STRM SND ID in the STRM lookup table
//
//	Input:			nSndID		snd Id number to locate
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

STRM_SND* strmFindSndID ( ULONG nSndID )
{
	STRM_SND*	pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
	unsigned	index;

	if ( !STRMenabled )
		goto exit;

	if ( nSndID == SND_NULL_SND_ID )
		goto exit;

	// find the sound in the table
	pStrmTblPtr = STRMlookupTable;
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
		goto exit;

	index      = 0;
	while ( (index<STRMmaxSounds) && (pStrmTblPtr->nSndID != nSndID) )
	{
		++index;
		++pStrmTblPtr;
	}
   
	// did we find it ?
	if ( index >= STRMmaxSounds )
		pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
exit:   
	return( pStrmTblPtr );    
}

///========================================================================
//	Function:		strmFindSlot()
//
//	Description:
//		Locate a STRM sound slot in the STRM lookup table
//
//	Input:			nStrmID			sound Id number to apply pan to
//
//	Ouput:			pStrmTblPtr		address of slot, SND_NULL_SND_PTR otherwise
//
///========================================================================

STRM_SND* strmFindSlot( void )
{
	STRM_SND*	pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
	unsigned	index;

	if ( !STRMenabled )
		goto exit;

	// find the sound in the table
	pStrmTblPtr = STRMlookupTable;
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
		goto exit;

	index      = 0;
	while ( (index<STRMmaxSounds) && (pStrmTblPtr->nStrmID != SND_NULL_SND_ID) )
	{
		++index;
		++pStrmTblPtr;
	}
   
	// did we find it ?
	if ( index == STRMmaxSounds )
		pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
exit:   
	return( pStrmTblPtr );    
}

///========================================================================
//	Function:		strmFindTimerID()
//
//	Description:
//		Locate a STRM timer ID in the STRM lookup table
//
//	Input:			uTimerID		timer Id number associated with a sound
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

STRM_SND* strmFindTimerID ( UINT uTimerID )
{
	STRM_SND*	pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
	unsigned	index;

	if ( !STRMenabled )
		goto exit;

	if ( !uTimerID )
		goto exit;

	// find the sound in the table
	pStrmTblPtr = STRMlookupTable;
	if ( pStrmTblPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: STRMlookupTable is empty. [%s:%d]\n", 
			  __FILE__, __LINE__ );
       
		goto exit;
	}

	index      = 0;
	while ( (index<STRMmaxSounds) && (pStrmTblPtr->uTimerID != uTimerID) )
	{
		++index;
		++pStrmTblPtr;
	}
   
	// did we find it ?
	if ( index == STRMmaxSounds )
		pStrmTblPtr = (STRM_SND*)SND_NULL_SND_PTR;
exit:   
	return( pStrmTblPtr );    
}

///========================================================================
//	Function:		strmGetOffset()
//
//	Description:
//		Locate a STRM sound offset in the STRM lookup table
//
//	Input:			nSndID			sound Id number to apply pan to
//					nIndexToLoad	relative index from sndID
//
//	Ouput:			offset			offset of slot, SND_NULL_SND_ID otherwise
//
///========================================================================

ULONG	strmGetOffset( ULONG nSndID, unsigned nIndexToLoad )
{
	ULONG		offset;
	unsigned	index;
	unsigned	maxIndex;
   
	// search the header for this snd id
	offset  = (ULONG)SND_NULL_SND_ID;

	if ( !STRMenabled )
		goto exit;

	if ( nSndID == SND_NULL_SND_ID )
		goto exit;

	// search the header for this snd id
	maxIndex = STRMsndHeader->numberOfSounds;
	index    = 0;
	while ( (STRMsndHeader->sounds[ index ].soundID != nSndID) && (index<maxIndex) )
		++index;

	if ( STRMsndHeader->sounds[ index ].soundID != nSndID )
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
	offset = STRMsndHeader->sounds[ index ].offset;

exit:
	return( offset );
}

///========================================================================
//	Function:		strmTimerCheck()
//
//	Description:
//		Verify that a timer ID belongs to the strmMonitor.
//
//	Input:			uTimerID		timer Id triggering this processing
//
//	Ouput:			TRUE			if ID found, FALSE otherwise
//
///========================================================================

BOOL	strmTimerCheck ( UINT uTimerID )
{
	STRM_SND*	pStrmTblPtr;
	unsigned	index;
	BOOL		answer = FALSE;		//assume timer is not ours

	if ( !STRMenabled )
		return( answer );

	if ( !uTimerID )
		return( answer );

	// find the sound in the table
	index      = 0;
	pStrmTblPtr = STRMlookupTable;
	while ( (index<STRMmaxSounds) && (pStrmTblPtr->uTimerID != uTimerID) )
	{
		++index;
		++pStrmTblPtr;
	}
   
	// did we find it ?
	if ( index < STRMmaxSounds )
		answer = TRUE;

	return( answer );
   
}

///========================================================================
//	Function:		strmSetLink()
//
//	Description:
//		Link a dynamic list of strm sounds together. It is assumed that all
//		the listed streams have been loaded.
//
//	Input:			nStrmID			sound ID to ste link for
//					nLink			link value
//
//	Ouput:			TRUE			if ID found, FALSE otherwise
//
///========================================================================

BOOL	strmSetLink( unsigned nStrmID, unsigned nLink )
{
	STRM_SND*	pStrmLinkPtr;
	BOOL		error = TRUE;		//assume an error

	if ( !STRMenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nStrmID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// Locate the sound ID and assigning the link sound ID into the link field.
	pStrmLinkPtr = strmFindID( nStrmID );
	if ( pStrmLinkPtr == (STRM_SND*)SND_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: failed to locate STRM ID (%ld). [%s:%d]\n\n", 
			  nStrmID, __FILE__, __LINE__ );
		goto exit;
	}

	// apply the link
	pStrmLinkPtr->nSndLink = nLink;

	// made it here so we must have been successful
	error = FALSE;

exit:
	return( error );
   
}

///========================================================================
//	Function:		strmNextLink()
//
//	Description:
//		based on the snd ID passed in, determine if there is a link to another
//		snd ID. Return that ID or SND_NULL_SND_ID.
//
//	Input:			nStrmID			sound ID whose link we want
//
//	Ouput:			nextStrmLink	snd ID link to the input sound,
//									SND_NULL_SND_ID otherwise
//
///========================================================================

ULONG	strmNextLink( ULONG nStrmID )
{
	STRM_SND*	pStrmLinkPtr;
	ULONG		nextStrmLink = SND_NULL_SND_ID;		// assume no link

	if ( !STRMenabled )
		goto exit;

	if ( nStrmID == SND_NULL_SND_ID )
		goto exit;

	// Locate the sound ID
	pStrmLinkPtr = strmFindID( nStrmID );
	if ( pStrmLinkPtr == (STRM_SND*)SND_NULL_SND_PTR )
		goto exit;

	// Check for a link
	if ( pStrmLinkPtr->nSndLink != SND_NULL_SND_ID )
		nextStrmLink = pStrmLinkPtr->nSndLink;			// there is a link

exit:
	return( nextStrmLink );
   
}

///========================================================================
//	Function:		strmGetMasterVoiceVolume()
//
//	Description:
// 		Get the stream voice sound volume level:
//
//	Input:			none
//
//	Ouput:			nVolume			current STRM volume setting
//
///========================================================================

LONG		strmGetMasterVoiceVolume ( void ) 
{
	return( STRMvoiceMasterVolume );
}

///========================================================================
//	Function:		strmSetMasterVoiceVolume()
//
//	Description:
// 		Set the strm voice sound volume level:
//
//	Input:			nVolume			volume setting to apply
//
//	Ouput:			none
//
///========================================================================

void	strmSetMasterVoiceVolume ( LONG nVolume )
{
	STRMvoiceMasterVolume = nVolume;
}

///========================================================================
//	Function:		strmGetMasterMusicVolume()
//
//	Description:
// 		Get the stream music sound volume level:
//
//	Input:			none
//
//	Ouput:			nVolume			current STRM volume setting
//
///========================================================================

LONG		strmGetMasterMusicVolume ( void ) 
{
	return( STRMmusicMasterVolume );
}

///========================================================================
//	Function:		strmSetMasterMusicVolume()
//
//	Description:
// 		Set the strm voice sound volume level:
//
//	Input:			nVolume			volume setting to apply
//
//	Ouput:			none
//
///========================================================================

void	strmSetMasterMusicVolume ( LONG nVolumePercentage )
{
	STRM_SND	*pMusicTblPtr;
	int		nIndex;

	STRMmusicMasterVolume = nVolumePercentage;

	// now adjust all sounds to this volume precentage
	if ( !STRMenabled )
		return;

	// cleanup the STRM lookup table
	pMusicTblPtr = STRMlookupTable;
	if ( pMusicTblPtr != (STRM_SND*)SND_NULL_SND_PTR )
	{
		// lower the volume of each legal sound in the table
		for ( nIndex=0; nIndex<(int)STRMmaxSounds; ++nIndex )
		{
			// change the volume of this sound this sound
			if ( pMusicTblPtr->nSndID != (ULONG)SND_NULL_SND_ID )
				SndSetVolumePercent( pMusicTblPtr->nSndID, nVolumePercentage, FALSE );

			// check the next entry
			++pMusicTblPtr;
		}
	}
}

ULONG	strmCreateStream( unsigned AUDIOstreamID, ULONG nAudioID,
						       unsigned nIndexToLoad,  USHORT bFlags )
{
	unsigned	nSndID = SND_NULL_SND_ID;

	nSndID = strmLoad( AUDIOstreamID, nAudioID, nIndexToLoad, bFlags );

	return( nSndID );
}

void	strmDeleteStream( ULONG nSndID )
{
	strmDeleteSnd( nSndID );

	// now delete the snd
	audioDeleteSnd( nSndID );
}

void	strmCleanUpStreams( ULONG nSndID )
{
	ULONG		bFlags;
	STRM_SND	*pStrmTblPtr;

	if ( nSndID != SND_NULL_SND_ID )
	{
		bFlags = strmFlags( nSndID );
		if ( ((bFlags & SND_TIMER_FLAG) == SND_TIMER_FLAG) && ((bFlags & SND_DONE_FLAG) != SND_DONE_FLAG) )
		{
			pStrmTblPtr = strmFindSndID( nSndID );
			if ( pStrmTblPtr )
				strmUpdate( pStrmTblPtr );
		}
		if ( ((bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG) && ((bFlags & SND_DONE_FLAG) == SND_DONE_FLAG) )
			strmDeleteStream( nSndID );
	}
}

///========================================================================
//	Function:		strmTableCleanUp()
//
//	Description:
//		Clean up the STRM processing and data
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	strmTableCleanUp(  )
{
	STRM_SND*	pStrmTblPtr;
	ULONG		bFlags;
	ULONG		nSndID;
	unsigned	index;

	// cleanup the strm lookup table
	pStrmTblPtr = STRMlookupTable;
	if ( pStrmTblPtr != (STRM_SND*)SND_NULL_SND_PTR )
	{
		// clean up each legal sound in the table
		for ( index=0; index<STRMmaxSounds; ++index )
		{
			// check this sound
			if ( pStrmTblPtr->nSndID != (ULONG)SND_NULL_SND_ID )
			{
				nSndID = pStrmTblPtr->nSndID;
				bFlags = strmFlags( pStrmTblPtr->nSndID );
				if ( ((bFlags & SND_TIMER_FLAG) == SND_TIMER_FLAG) && ((bFlags & SND_DONE_FLAG) != SND_DONE_FLAG) )
					strmUpdate( pStrmTblPtr );
				if ( ((bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG) && ((bFlags & SND_DONE_FLAG) == SND_DONE_FLAG) )
					strmDeleteStream( nSndID );
			}

			// check the next entry
			++pStrmTblPtr;
		}
	}
}

USHORT	strmFlags( ULONG nSndID )
{
	STRM_SND* pStream = strmFindSndID ( nSndID );
	if ( pStream != (STRM_SND*)SND_NULL_SND_PTR )
		return ( pStream->bFlags );
	else
		return( 0 );
}

void	strmSetOn(BOOL on)	{
	STRMon = on;
}

BOOL	strmGetOn(void)	{
	return( STRMon );
}

void	strmToggleOn(void)	{
	STRMon ^= TRUE;
}

void	strmDump ( STRM_SND* pStrmTblPtr )
{
	TRACE( "pStrmTblPtr:\n" );
	TRACE( " bLock             = %d\n", pStrmTblPtr->bLock );			// locking mechanism
	TRACE( " nAudioID          = %d:%s\n", pStrmTblPtr->nAudioID,		// audio identifier
										   audioIDname( pStrmTblPtr->nAudioID ) );

	TRACE( " nStrmID           = %d\n", pStrmTblPtr->nStrmID );			// STREAM identifier
	TRACE( " nSndID            = %d\n", pStrmTblPtr->nSndID );			// sound identifier
	TRACE( " bFlags            = %d\n", pStrmTblPtr->bFlags );			// Flag fields (see SND.H)
	TRACE( " pDSBuffer         = %d\n", pStrmTblPtr->pDSBuffer );		// Direct Sound Buffer
	TRACE( " pWaveForm         = %d\n", pStrmTblPtr->pWaveForm );		// Wave Format data structure

				// these are filled at load time.
	TRACE( " nSndStart         = %d\n", pStrmTblPtr->nSndStart );		// Start offset into file to reach sound chunk
	TRACE( " nSndOffset        = %d\n", pStrmTblPtr->nSndOffset );		// current offset into wave stream
	TRACE( " nSndSize          = %d\n", pStrmTblPtr->nSndSize );		// size of raw stream data

	TRACE( " uTimerID          = %d\n", pStrmTblPtr->uTimerID );		// stream timer ID
	TRACE( " dwBufferSize      = %d\n", pStrmTblPtr->dwBufferSize );    // Size of the entire buffer
	TRACE( " dwBufferSegSize   = %d\n", pStrmTblPtr->dwBufferSegSize ); // Size of one buffer segment
	TRACE( " dwNextWriteOffset = %d\n", pStrmTblPtr->dwNextWriteOffset );// Offset to next buffer segment
	TRACE( " dwPlayLast        = %d\n", pStrmTblPtr->dwPlayLast );      // Position of last play cursor
	TRACE( " dwProgress        = %d\n", pStrmTblPtr->dwProgress );      // Used with above to show prog
	TRACE( " nRemainingBytes   = %d\n", pStrmTblPtr->nRemainingBytes );	// Bytes 'til timer shutdown
	TRACE( " nSndLink          = %d\n", pStrmTblPtr->nSndLink );		// Link to another strm ID
	TRACE( " DUMP DONE\n" );
}

///========================================================================
//								EOF
///========================================================================
