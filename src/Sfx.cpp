//========================================================================
//	FILE:			$Workfile: Sfx.cpp $
//
//	DESCRIPTION:	Audio SFX processing.
//
//					Special Effects Audio processing. These usually refer
//					to short, static, often used sounds.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Friday, May 03, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Sfx.cpp 32    4/02/98 3:35p Phu $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//========================================================================
//	sfxInit()
//		initialize the SXF sound processing
//	sfxExit()
//		Clean up the SFX processing and data
//	sfxOpen()
//		Open a SFX .snd file for input
//	sfxLoad()
//		Load one or more SFX sounds from a .SND file
//	sfxLoadRes()
//		Load a single resouce SFX
//	sfxLoadWav()
//		Load a single SFX from a .WAV
//	sfxPlay()
//		Play a SFX sound by ID
//	sfxFade()
//		Fade in or out a SFX sound by ID
//	sfxStop()
//		Stop a SFX sound by ID
//	sfxDelete()
//		Delete a SFX sound by ID
//	sfxClose()
//		Close down an SFX .snd file
//	sfxGetFrequency()
// 		Get the SFX sound frequency level (effect pitch)
//	sfxSetFrequency()
// 		Set the SFX sound requency level (effect pitch)
//	sfxGetVolume()
// 		Get the SFX sound volume levels:
//	sfxSetVolume()
// 		Set the SFX sound volume levels:
//	sfxGetPan()
// 		Get the SFX sound pan levels
//	sfxSetPan()
// 		Set the SFX sound pan levels
//	sfxFindID()
//		Locate a SFX sound ID in the SFX lookup table
//	sfxFindSlot()
//		Locate an empty SFX sound slot in the SFX lookup table
//	sfxGetOffset()
//		Locate a SFX sound offset in the SFX lookup table
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Sfx.cpp $
//  
//  32    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  31    3/18/98 2:23p Aburgess
//  modifications to correct update error
//  
//  30    3/18/98 11:47a Aburgess
//  added Debug, and cleared AudioIDs
//  
//  29    3/17/98 11:25a Aburgess
//  correction of on/Off toggles
//  
//  28    3/16/98 5:29p Aburgess
//  added sfxInPlay()
//  
//  27    3/16/98 4:36p Aburgess
//  modifications made to correctly look up the SFX snd ID
//  
//  26    3/16/98 3:32p Aburgess
//  correction of Audio deletion
//  
//  25    3/16/98 12:56p Aburgess
//  modifications to support vehicle decel,acel,and looping
//  
//  24    3/09/98 12:03p Aburgess
//  replaced exit calls with return calls
//  
//  23    3/06/98 5:17p Aburgess
//  correction of audio flags and volume modifications
//  
//  22    3/02/98 10:31a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  21    2/25/98 2:53p Aburgess
//  modifications to improve AUDIO options interface. Still needs work.
//  
//  20    2/20/98 12:00p Aburgess
//  modifications to support clean up and deletion of SFX sounds
//  
//  19    1/21/98 9:22a Aburgess
//  modifications made to shorten the STRM and VOICE monitor interrupts.
//  Also merged the audio ON/OFF switching. In addition, all audio is now
//  turned off during mission load as that routine has a large frame
//  overrun problem disallowing updates to audio.
//  
//  18    12/23/97 6:25p Nrobinso
//  use audio variables for on/off
//  
//  17    12/22/97 11:34a Aburgess
//  anal change
//  
//  16    12/19/97 1:51p Aburgess
//  clarification of nSndID usage
//  
//  15    12/18/97 1:19p Aburgess
//  attempt to apply volume changes to SFX
//  
//  14    12/09/97 12:12p Phu
//  
//  13    12/07/97 6:28p Aburgess
//  disabled debug trace
//  
//  12    12/04/97 4:18p Nrobinso
//  look for null_snd_id
//  
//  11    12/04/97 9:14a Aburgess
//  Modifications made to properly handle delete race condition with
//  strmMonitor. Actual sound allocation tracking added to help minimize
//  static tables for audio
//  
//  10    12/02/97 10:21a Aburgess
//  locking mechanism added for deletes (load?)
//  
//  9     11/24/97 2:56p Aburgess
//  SFX, on create, now returns the nSndID rather than the nSfxID
//  
//  8     11/21/97 9:13a Aburgess
//  debug SND id reporting
//  
//  7     11/20/97 3:32p Aburgess
//  modifications made to allow app to run regardless of existence of .ASD,
//  .AST files or DirectSound itself
//  
//  6     11/20/97 11:52a Aburgess
//  audio modifications
//  
//  5     11/17/97 10:08a Aburgess
//  rework of audio/sfx/strm/voice/snd interface
//  
//  4     11/16/97 2:21p Aburgess
//  cleanup of sound files (fclose)
//  
//  2     9/02/97 9:39a Aburgess
//  added SFX master volume control
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  16    4/14/97 7:28a Aburgess
//  modifications made to support full Army creation along with unit
//  reserves. Vehicle reserves have yet to be done.
//  
//  15    11/13/96 12:40p Nrobinso
//  moved malloc.h and string.h to stdafx
//  
//  14    10/02/96 11:25a Aburgess
//  added sfxReset() and altered nSndID lookup to use proper ID.
//  
//  13    9/10/96 12:59p Aburgess
//  move commonly used but infrequently changed header files to stdafx.h
//  (precompiled header)
//  
//  12    8/15/96 6:01a Aburgess
//  removed superfluous TRACE warnings and errors
//  
//  11    8/14/96 10:21p Aburgess
//  fixed bug that failed to place the callers bFlag value into the snd
//  info. Thus Looping would never be set.
//  
//  10    7/23/96 2:42p Nrobins
//  freed SFXlookupTable
//  
//  6     6/26/96 10:26a Aburgess
//  added new Source Control header
// 
//  $Nokeywords:$
///========================================================================
#include "stdafx.h"

#include "snd.h"			// SND         defines, structures, and prototypes
#include "sfx.h"			// SFX         defines, structures, and prototypes

extern	char*	audioIDname( ULONG nAudioID );
extern	char*	audioSndIDname( ULONG nSndID );
extern	BOOL	audioDeleteSnd( ULONG nSndID  );
extern	BOOL	audioDeleteSfx( ULONG nSndID, ULONG nSfxID  );
extern	void	SndSetVolumePercent( ULONG nSndID ,ULONG Percent, BOOL bMax );
extern	LONG	audioGetMasterVolume( USHORT bFlag );
extern	BOOL	sndExist( ULONG nSndID  );

///========================================================================
//							LOCAL DEFINES
///========================================================================

///========================================================================
//							LOCAL DATA TYPES
///========================================================================

///========================================================================
//							LOCAL VARIABLES
///========================================================================

// SFX lookup table
SFX_SND*		SFXlookupTable;
unsigned		SFXmaxSounds;
unsigned		SFXactualMaxSounds;
unsigned		SFXsoundsActive;

ULONG			SFXnextID;

SND_HEADER*		SFXsndHeader;

static	FILE*	pSFXfile;

static	BOOL	SFXon = TRUE;		// sfx audio on/off
static	LONG	SFXmasterVolume = 100;

BOOL			SFXenabled;

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
SFX_SND*	sfxFindSfxID( ULONG nSfxID );
SFX_SND*	sfxFindSlot( void );
ULONG		sfxGetOffset( ULONG nSfxID, unsigned nIndexToLoad );
void		sfxDumpTable( void );


///========================================================================
//	Function:		sfxInit()
//
//	Description:
//		initialize the SXF sound processing
//
//	Input:			nMaxSounds		maximum size of the sfx sound table
//
//	Ouput:			error			FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sfxInit ( unsigned nMaxSounds )
{
	SFX_SND*	pSfxTblPtr;
	unsigned	index;
	BOOL		error = TRUE;	// assume failure

	// remember the max number of sounds that can be created
	SFXmaxSounds       = nMaxSounds;
	SFXactualMaxSounds = 0;
	SFXsoundsActive    = 0;
	SFXnextID          = SFX_START_ID;
	SFXenabled         = FALSE;

	// allocate the memory necessary to support
	SFXlookupTable = (SFX_SND*)malloc( SFXmaxSounds* sizeof(SFX_SND) );
	if ( SFXlookupTable == NULL )
	{
		// report an error
		TRACE("ERROR: Insufficient memory available. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): SFX lookup table [%s : %d]\n", (SFXmaxSounds* sizeof(SFX_SND)), __FILE__, __LINE__ );
#endif

	// initialize the sfx lookup table
	pSfxTblPtr = SFXlookupTable;
	for( index=0; index<SFXmaxSounds; ++index, pSfxTblPtr++ )
	{
		pSfxTblPtr->bLock           = FALSE;			// audio lock
		pSfxTblPtr->nAudioID		= SFX_NULL_SND_ID;	// audio identifier
		pSfxTblPtr->nSfxID			= SFX_NULL_SND_ID;	// SFX identifier
		pSfxTblPtr->nSndID			= SFX_NULL_SND_ID;	// sound identifier
		pSfxTblPtr->bFlags			= SND_CLEAR_FLAG;	// Boolean Flag fields
														// 0    : resource flag
														// 1    : streaming flag															// 2-15 : unused
		pSfxTblPtr->nImageLen		= 0;				// length of sound data
		pSfxTblPtr->nPlayBufferLen	= 0;				// length of play buffer
		pSfxTblPtr->pSndData		= NULL;				// play data buffer
		pSfxTblPtr->pDSBuffer		= NULL;				// DirectSound play buffer
	}

	// initialize the SND header structure
	SFXsndHeader = NULL;

	// initialize the input file pointer
	pSFXfile = NULL;

	// set the SFX toggle
//	sfxSetOn(TRUE);

	// if we got here we were successful
	error = FALSE;

exit:
	return( error );
}

///========================================================================
//	Function:		sfxExit()
//
//	Description:
//		Clean up the SFX processing and data
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void		sfxExit ( void )
{
	SFX_SND*	pSfxTblPtr;
	unsigned	index;

	if ( !SFXenabled )
		return;

	// cleanup the sfx lookup table
	pSfxTblPtr = SFXlookupTable;
	if ( pSfxTblPtr != (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// clean up each legal sound in the table
		for ( index=0; index<SFXmaxSounds; ++index )
		{
			// delete this sound
			if ( pSfxTblPtr->nSfxID != (ULONG)SFX_NULL_SND_ID )
				sfxDelete( pSfxTblPtr->nAudioID );

			// check the next entry
			++pSfxTblPtr;
		}

		// de-allocate the SND header structure
		if ( SFXsndHeader )
		{
			free( SFXsndHeader );
			SFXsndHeader = NULL;
#ifdef MALLOC_DEBUG
			TRACE( "free: SFX header [%s : %d]\n", __FILE__, __LINE__ );
#endif
		}
	}

	free(SFXlookupTable);
	SFXlookupTable = (SFX_SND*)SFX_NULL_SND_PTR;

#ifdef MALLOC_DEBUG
		TRACE( "free: SFX lookup table [%s : %d]\n", __FILE__, __LINE__ );
#endif

	// now close the voice file
	if ( pSFXfile )
	{
		fclose( pSFXfile );
		pSFXfile = NULL;
	}

	// disable SFX
	SFXenabled = FALSE;

#ifdef SND_DEBUG
	TRACE( "SFXactualMaxSounds = %d\n", SFXactualMaxSounds );
#endif
}

///========================================================================
//	Function:		sfxOpen()
//
//	Description:
//		open a SFX .snd file for input
//
//	Input:			pFilename		.SND filename that needs opening
//
//	Ouput:			nFileID			file id to file info is successful
//									SND_NULL_SND_ID otherwise
//
///========================================================================

unsigned	sfxOpen ( char* pFilename )
{
	unsigned	nFileID = SND_NULL_SND_ID;

	// now open the new wav file
	if ( (pSFXfile = (FILE*)fopen( pFilename, "rb" )) == NULL )
	{
		// report an error
		TRACE("ERROR: failed to open file: \"%s\". [%s:%d]\n", 
			  pFilename, __FILE__, __LINE__ );
		goto exit;
	}

	// copy in the .SND header information
	SFXsndHeader = (SND_HEADER*)malloc( sizeof( SND_HEADER ) );
	if ( SFXsndHeader == NULL )
	{
		// report an error
		TRACE("ERROR: Insufficient memory available. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}
#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): SFX header [%s : %d]\n", (sizeof( SND_HEADER )), __FILE__, __LINE__ );
#endif

	if ( fread( SFXsndHeader, sizeof( SND_HEADER ), 1, pSFXfile ) != 1 )
	{
		// report an error: failed writing header
		TRACE("ERROR: failed to read .SND header. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		if ( pSFXfile )
			fclose( pSFXfile );
		pSFXfile = NULL;
		goto exit;
	}

	// store the FILE and the FileName
	nFileID = sndSaveFile( pSFXfile, pFilename );
	if ( nFileID == SND_NULL_SND_ID )
	{
		// report an error
		TRACE("ERROR: failed to save file info: \"%s\". [%s:%d]\n", 
			  pFilename, __FILE__, __LINE__ );
	}

exit:
	return( nFileID );
}

///========================================================================
//	Function:		sfxMaxSounds()
//
//	Description:
//		return the current number of sounds in the SFX lookup table
//
//	Input:			none
//
//	Ouput:			maxSounds		number of sounds in the look table
//									NULL otherwise
//
///========================================================================

unsigned	sfxMaxSounds ( void )
{
	unsigned	maxSounds = 0;

	if ( SFXsndHeader == NULL )
	{
		// report an error
		TRACE("WARNING: SFX sound lookup table not present. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// get the sound count
	maxSounds = SFXsndHeader->numberOfSounds;
exit:
	return( maxSounds );
}

///========================================================================
//	Function:		sfxLoad()
//
//	Description:
//		Load one or more SFX sounds from a .SND file
//
//	Input:			nFileID			id of file to access
//					nSfxID			sound Id number to be stored into
//					nIndexToLoad	index within .SND file from which to
//									load SFX sound
//					bFlags			falgs associated with this sound.
//									 
//
//	Ouput:			nSndID			ID assigned to this sound if successful
//									SND_NULL_SND_ID if failure
//
///========================================================================

ULONG	sfxLoad ( unsigned nFileID, ULONG nAudioID, unsigned nIndexToLoad, USHORT bFlags )
{
	SND*			pSndPtr;
	DSBUFFERDESC	dsBufferDesc;
	LPDIRECTSOUND	pDirectSound;
	DWORD			dwDataLen;
    BYTE*			pDSBuffData;
	unsigned		status;
	unsigned		error;
	ULONG			offset;
	int				nSndIdx;
	SFX_SND*		pSfxTblPtr = NULL;
	ULONG			nSndID     = SND_NULL_SND_ID;		// assume failure

	if ( !SFXenabled )
		goto exit;

	if ( nAudioID == SND_NULL_SND_ID )
		goto exit;

	// make sure the table isn't full already
	if ( SFXsoundsActive == SFXmaxSounds )
	{
		// report an error that the sound table is full
		TRACE("ERROR: sfx table limited exceeded (%d). [%s:%d]\n", 
			  SFXmaxSounds, __FILE__, __LINE__ );
#if 0
		sfxDumpTable();
#endif
		goto exit;
	}

    // Get the DirectSound Object for this application
	pDirectSound = sndGetDSobject();
	if ( !pDirectSound )
		goto exit;

	// get the expected offset
	offset = sfxGetOffset( nAudioID, nIndexToLoad );
	if ( offset == SND_NULL_SND_ID )
	{
		// report an error that the sound table is full
		TRACE("ERROR: failed to get sfx offset.[%s:%d]\n", 
			   __FILE__, __LINE__ );
		goto exit;
	}

	// create this sound. if already created will return address
	// of existing sound
	nSndID = sndCreate( nAudioID, bFlags, nFileID, &offset );
	if ( nSndID == SND_NULL_SND_ID )
	{
		// report an error that the sound table is full
		TRACE("ERROR: failed to create new sfx entry.[%s:%d]\n", 
			   __FILE__, __LINE__ );
		goto cleanUp;
	}

	// find an available sound
	pSfxTblPtr = sfxFindSlot();
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// report an error that the sound table is full
		TRACE("ERROR: failed to create new sfx entry.[%s:%d]\n", 
			   __FILE__, __LINE__ );
		goto cleanUp;
	}

	// lock this sound
//	pSfxTblPtr->bLock = TRUE;

	// if we're here we have a sfx entry to fill.
	// initialize the Sfx entry
	// start by locating the SND and load in the data
	status = sndFindSndID( nSndID, &pSndPtr, &nSndIdx );
	if ( status == SND_BAD_STATUS )
	{
		// report an error
		TRACE("ERROR: unable to find snd ID: %d (%d). [%s:%d]\n", 
			  status, nSndID, __FILE__, __LINE__ );
		nSndID = SND_NULL_SND_ID;
		goto exit;
	}

	pSfxTblPtr->nAudioID		= nAudioID;			// audio identifier
//	pSfxTblPtr->nSfxID			= SFXnextID++;		// sfx identifier
//	pSfxTblPtr->nSndID			= nSndID;			// sound identifier
	pSfxTblPtr->nSndID			= SFXnextID++;		// sfx identifier
	pSfxTblPtr->nSfxID			= nSndID;			// sound identifier
	pSfxTblPtr->bFlags			= bFlags;			// Boolean Flag fields
	pSfxTblPtr->nImageLen		= pSndPtr->wavSnd.nSndSize;	// length of sound data


    // Setup the DS buffer description
	memset( &dsBufferDesc, 0, sizeof(DSBUFFERDESC)); 
    dsBufferDesc.dwSize        = sizeof(DSBUFFERDESC);
    dsBufferDesc.dwFlags       = DSBCAPS_CTRLDEFAULT | DSBCAPS_STATIC;
    dsBufferDesc.lpwfxFormat   = &(pSndPtr->wavSnd.wfSndFormat);
    dsBufferDesc.dwBufferBytes = pSfxTblPtr->nImageLen;

    // Create the DS buffer
    error = pDirectSound->CreateSoundBuffer(
											&dsBufferDesc,
										    &(pSfxTblPtr->pDSBuffer),
										    NULL
										   );
    if (error != DS_OK)
	{
		// report an error
		TRACE("ERROR:  failed to create the DirectSoundbuffer (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

    // Lock the DS buffer
    error = pSfxTblPtr->pDSBuffer->Lock(0, pSfxTblPtr->nImageLen, (LPLPVOID)&pDSBuffData,
							       &dwDataLen, NULL, 0, 0);
    if (error != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer lock (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	if ( fseek( pSndPtr->wavSnd.pSndFile, pSndPtr->wavSnd.nSndStart, SEEK_SET) )
	{
		// report an error
		TRACE("ERROR: fseek failure. [%s:%d]\n", __FILE__, __LINE__ );
		goto exit;
	}

    // Write wave data to the DS buffer
	if ( (long)fread( (void*)pDSBuffData, 1, dwDataLen, pSndPtr->wavSnd.pSndFile) != (long)dwDataLen)
	{
		// report an error
		TRACE("ERROR: failed to read \"data\" chunk data\n");
		goto exit;
	}

    // Unlock the DS buffer
    if (pSfxTblPtr->pDSBuffer->Unlock(pDSBuffData, dwDataLen, NULL, 0) != DS_OK)
	{
		// report an error
		TRACE("ERROR: failed DSbuffer unlock\n");
		goto cleanUp;
	}

	// if we made it here we've had success
	++SFXsoundsActive;
	if ( SFXactualMaxSounds < SFXsoundsActive )
		SFXactualMaxSounds = SFXsoundsActive;

	// see if we were error free
	goto exit;

	// clean up after getting an error
cleanUp:
	// clean up this SFX entry
	if ( pSfxTblPtr )
	{
		if ( pSfxTblPtr != (SFX_SND*)SFX_NULL_SND_PTR )
		{
			// now start deleting
			pSfxTblPtr->nSfxID			= SND_NULL_SND_ID;	// sound identifier
			pSfxTblPtr->nSndID			= SND_NULL_SND_ID;	// sound identifier
			pSfxTblPtr->bFlags			= SND_CLEAR_FLAG;	// Boolean Flag fields
			pSfxTblPtr->nImageLen		= 0;				// length of sound data
			if ( pSfxTblPtr->pDSBuffer )
			{
				error = pSfxTblPtr->pDSBuffer->Release();
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

		pSfxTblPtr = NULL;
	}

	// return the result to the caller
exit:
	if ( pSfxTblPtr )
	{
		// unlock this sound
//		pSfxTblPtr->bLock = FALSE;

		nSndID            = pSfxTblPtr->nSndID;

#if 0
if ( (pSfxTblPtr->bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG )
{
	TRACE( "SFX - Load (w/DELETE) of %d:%d:%d:%s\n",
		  pSfxTblPtr->nAudioID, pSfxTblPtr->nSfxID, pSfxTblPtr->nSndID, audioIDname(pSfxTblPtr->nAudioID) );
}
#endif
	}

	return( nSndID );
}

///========================================================================
//	Function:		sfxLoadRes()
//
//	Description:
//		Load a single resouce SFX
//
//	Input:			nResId			Resource ID containing sfx data
//
//	Ouput:			nSfxID			sfx ID assigned to this resource
//
///========================================================================

ULONG		sfxLoadRes ( unsigned nResId )
{
	return( 1L );
}

///========================================================================
//	Function:		sfxLoadWav()
//
//	Description:
//		Load a single SFX from a .WAV
//
//	Input:			pWaveFilename	data file containing sfx data
//					
//
//	Ouput:			nSfxID			sfx ID assigned to this wave
//
///========================================================================

ULONG		sfxLoadWav ( char* pWaveFilename )
{
	return( 1L );
}

///========================================================================
//	Function:		sfxPlay()
//
//	Description:
//		Play a SFX sound by ID
//
//	Input:			nSfxID			sound Id number to be played
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxPlay ( ULONG nAudioID )
{
	SFX_SND*			pSfxTblPtr;
	LPDIRECTSOUNDBUFFER pDSbuffer;
	LONG				nMasterVolume = 0L;
	BOOL				error = TRUE;		// assume failure

	if ( !SFXenabled )
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
	pSfxTblPtr = sfxFindID( nAudioID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to play a non-exitent AudioID (%ld). [%s:%d]\n", 
			nAudioID, __FILE__, __LINE__ );
		goto exit;
	}

	// get the DirectSound Buffer
	pDSbuffer = pSfxTblPtr->pDSBuffer;

	// reposition the buffer to the beginning
	pDSbuffer->SetCurrentPosition( 0 );

	// make sure the user hasn't turned sfx off
	if ( SFXon )
		nMasterVolume = audioGetMasterVolume( SND_SFX_FLAG );
	SndSetVolumePercent( pSfxTblPtr->nSndID, nMasterVolume, FALSE );

	// now play it
	if ( (pSfxTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG)
		pDSbuffer->Play( 0, 0, DSBPLAY_LOOPING );
	else
		pDSbuffer->Play( 0, 0, 0 );

	// turn on the playing flag
	pSfxTblPtr->bFlags |= SND_PLAYING_FLAG;

	// if we made it here we were successful
	error = FALSE;

#if 0
	TRACE( "Playing SFX Audio - %ld:%ld:%ld:%s:0x%4X\n", nAudioID,
		pSfxTblPtr->nSfxID, pSfxTblPtr->nSndID, audioIDname( nAudioID ),
		pSfxTblPtr->bFlags );
#endif
 
exit:
	return( error );
}

///========================================================================
//	Function:		sfxPlaySnd()
//
//	Description:
//		Play a SFX sound by ID
//
//	Input:			nSfxID			sound Id number to be played
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxPlaySnd ( ULONG nSndID )
{
	SFX_SND*			pSfxTblPtr;
	LPDIRECTSOUNDBUFFER pDSbuffer;
	LONG				nMasterVolume;
	BOOL				error = TRUE;		// assume failure

	if ( !SFXenabled )
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
	pSfxTblPtr = sfxFindSndID( nSndID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to play a non-exitent nSndID (%ld). [%s:%d]\n", 
			nSndID, __FILE__, __LINE__ );
		goto exit;
	}

	// get the DirectSound Buffer
	pDSbuffer = pSfxTblPtr->pDSBuffer;

	// reposition the buffer to the beginning
	pDSbuffer->SetCurrentPosition( 0 );

	// make sure the user hasn't turned sfx off
	if ( SFXon )
		nMasterVolume = audioGetMasterVolume( SND_SFX_FLAG );
	SndSetVolumePercent( pSfxTblPtr->nSndID, nMasterVolume, FALSE );

	// now play it
	if ( (pSfxTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG)
		pDSbuffer->Play( 0, 0, DSBPLAY_LOOPING );
	else
		pDSbuffer->Play( 0, 0, 0 );

	// turn on the playing flag
	pSfxTblPtr->bFlags |= SND_PLAYING_FLAG;

#if 0
	TRACE( "Playing SFX Snd - %ld:%ld:%ld:%s:0x%4X\n", pSfxTblPtr->nAudioID,
		pSfxTblPtr->nSfxID, nSndID, audioIDname(pSfxTblPtr->nAudioID),
		pSfxTblPtr->bFlags );
#endif
 
	// if we made it here we were successful
	error = FALSE;

exit:
	return( error );
}

///========================================================================
//	Function:		sfxPlaySfx()
//
//	Description:
//		Play a SFX sound by Sfx ID
//
//	Input:			nSfxID			sfx Id number to be played
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxPlaySfx ( ULONG nSfxID )
{
	SFX_SND*			pSfxTblPtr;
	LPDIRECTSOUNDBUFFER pDSbuffer;
	LONG				nMasterVolume;
	BOOL				error = TRUE;		// assume failure

	if ( !SFXenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nSfxID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pSfxTblPtr = sfxFindSfxID( nSfxID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to play a non-exitent nSfxID (%ld). [%s:%d]\n", 
			nSfxID, __FILE__, __LINE__ );
		goto exit;
	}

	// get the DirectSound Buffer
	pDSbuffer = pSfxTblPtr->pDSBuffer;

	// reposition the buffer to the beginning
	pDSbuffer->SetCurrentPosition( 0 );

	// make sure the user hasn't turned sfx off
	if ( SFXon )
		nMasterVolume = audioGetMasterVolume( SND_SFX_FLAG );
	SndSetVolumePercent( pSfxTblPtr->nSndID, nMasterVolume, FALSE );

	// now play it
	if ( (pSfxTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG)
		pDSbuffer->Play( 0, 0, DSBPLAY_LOOPING );
	else
		pDSbuffer->Play( 0, 0, 0 );

	// turn on the playing flag
	pSfxTblPtr->bFlags |= SND_PLAYING_FLAG;

#if 0
	TRACE( "Playing SFX Snd - %ld:%ld:%ld:%s:0x%4X\n", pSfxTblPtr->nAudioID,
		pSfxTblPtr->nSfxID, pSfxTblPtr->nSndID, audioIDname(pSfxTblPtr->nAudioID),
		pSfxTblPtr->bFlags );
#endif
 
	// if we made it here we were successful
	error = FALSE;

exit:
	return( error );
}

///========================================================================
//	Function:		sfxFade()
//
//	Description:
//		Fade in or out a SFX sound
//
//	Input:			nSfxID			sound Id number to be faded
//					nInOrOut		fade sound IN or OUT		
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxFade ( ULONG nAudioID, unsigned nInOrOut )
{
	SFX_SND*	pSfxTblPtr;
	BOOL		error = TRUE;		// assume a failure

	if ( !SFXenabled )
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
	pSfxTblPtr = sfxFindID( nAudioID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to fade a non-exitent audioID (%ld). [%s:%d]\n", 
			nAudioID, __FILE__, __LINE__ );
		goto exit;
	}

	// Set up the sound for fading
	if ( nInOrOut == SND_FADE_IN_FLAG )
	{
		// strip off the FADE BITS
		pSfxTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade In bit
		pSfxTblPtr->bFlags |= SND_FADE_IN_FLAG;
	}
	else
	if ( nInOrOut == SND_FADE_OUT_FLAG )
	{
		// strip off the FADE BITS
		pSfxTblPtr->bFlags &= ~SND_FADE_FLAGS;
		
		// set the Fade Out bit
		pSfxTblPtr->bFlags |= SND_FADE_OUT_FLAG;
	}
	else
	{
		// report an error
		TRACE("ERROR: illegal FADE type (%d). [%s:%d]\n", 
			nInOrOut, __FILE__, __LINE__ );
		goto exit;
	}
		 
	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sfxStop()
//
//	Description:
//		stop a SFX sound by ID
//
//	Input:			nSfxID			sound Id number to be stop
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxStop ( ULONG nAudioID )
{
	SFX_SND*	pSfxTblPtr;
	BOOL		error = TRUE;		// assume a failure

	if ( !SFXenabled )
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
	pSfxTblPtr = sfxFindID( nAudioID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		error = FALSE;
		goto exit;
	}

	// stop the sound
	if ( sndStop( pSfxTblPtr->pDSBuffer ) != DS_OK )
		goto exit;	// error occurred

	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sfxStopSnd()
//
//	Description:
//		stop a SFX sound by sndID
//
//	Input:			nSndID			sound Id number to be stop
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxStopSnd( ULONG nSndID )
{
	SFX_SND*	pSfxTblPtr;
	BOOL		error = TRUE;		// assume a failure

	if ( !SFXenabled )
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
	pSfxTblPtr = sfxFindSndID( nSndID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		error = FALSE;
		goto exit;
	}

	// stop the sound
	if ( sndStop( pSfxTblPtr->pDSBuffer ) != DS_OK )
		goto exit;	// error occurred

	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sfxReset()
//
//	Description:
//		reset a SFX sound by ID
//
//	Input:			nSfxID			sound Id number to be reset
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxReset ( ULONG nAudioID )
{
	SFX_SND*	pSfxTblPtr;
	USHORT		bFlags;
	BOOL		error = TRUE;		// assume a failure

	if ( !SFXenabled )
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
	pSfxTblPtr = sfxFindID( nAudioID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// report an error
		TRACE("ERROR: attempted to stop a non-exitent AudioID (%ld). [%s:%d]\n", 
			  nAudioID, __FILE__, __LINE__ );
		goto exit;
	}

	// stop the sound
	if ( (pSfxTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// turn off the playing flag
//		pSfxTblPtr->bFlags &= ~SND_PLAYING_FLAG;

		// stop the stream
		if ( sndStop( pSfxTblPtr->pDSBuffer ) != DS_OK )
			goto exit;	// error occurred
	}

	// now set the flags
	bFlags = SND_SFX_FLAG;
	if ( (pSfxTblPtr->bFlags & SND_LOOP_FLAG) == SND_LOOP_FLAG )
		bFlags |= SND_LOOP_FLAG;
	pSfxTblPtr->bFlags &= ~bFlags;

	// if we got here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sfxDelete()
//
//	Description:
//		Delete a SFX sound by ID
//
//	Input:			nSfxID			sound Id number to delete
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxDelete ( ULONG nAudioID )
{
	SFX_SND*	pSfxTblPtr = (SFX_SND*)SND_NULL_SND_PTR;
	BOOL		error      = TRUE;		// assume a failure

#if 0
	char*		pAudioName;
#endif

	if ( !SFXenabled )
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
TRACE("sfxDelete( A:%ld ) ", nAudioID );
#endif

#if 0
	pAudioName = audioIDname( nAudioID );
#endif

	// find the sound in the table
	pSfxTblPtr = sfxFindID( nAudioID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// no need to delete this
		error = FALSE;
		goto exit;
	}

	// lock this sound
	pSfxTblPtr->bLock	= TRUE;

	// free up this table entry
	if ( pSfxTblPtr->pSndData )
	{
		free( pSfxTblPtr->pSndData );
#ifdef MALLOC_DEBUG
		TRACE( "free: SFX snd data [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}

	if ( pSfxTblPtr->pDSBuffer )
	{
		error = pSfxTblPtr->pDSBuffer->Release();
		if ( error != DS_OK )
		{
			// report an error
			TRACE("ERROR:  failed to relase the DirectSoundbuffer (%s) [%s:%d]\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
			goto exit;
		}
	}

	// now delete the snd
	audioDeleteSfx( pSfxTblPtr->nSndID,  pSfxTblPtr->nSfxID );

	// re-initalize this entry
	//	pSfxTblPtr->bLock				= FALSE;		// CLEAR THIS AT END
	pSfxTblPtr->nAudioID		= SND_NULL_SND_ID;	// SFX sound identifier
	pSfxTblPtr->nSfxID			= SND_NULL_SND_ID;	// SFX sound identifier
	pSfxTblPtr->nSndID			= SND_NULL_SND_ID;	// sound identifier
	pSfxTblPtr->bFlags			= SND_CLEAR_FLAG;	// Boolean Flag fields
													// 0    : resource flag
													// 1    : streaming flag															// 2-15 : unused
	pSfxTblPtr->nImageLen		= 0;				// length of sound data
	pSfxTblPtr->nPlayBufferLen	= 0;				// length of play buffer
	pSfxTblPtr->pSndData		= NULL;				// play data buffer
	pSfxTblPtr->pDSBuffer		= NULL;				// DirectSound play buffer

	// if we got here we we're successful
	--SFXsoundsActive;
	error = FALSE;

#if 0
	TRACE("sfxDelete( A:%s-A:%ld )\n", pAudioName, nAudioID );
#endif

exit:
	// unlock this sound
	if( pSfxTblPtr != (SFX_SND*)SFX_NULL_SND_PTR ) 
		pSfxTblPtr->bLock = FALSE;

#if 0
	if ( error )
		TRACE("sfxDelete( A:%s-A:%ld ) ERROR\n", pAudioName, nAudioID );
#endif

	return( error );
}

///========================================================================
//	Function:		sfxDeleteSnd()
//
//	Description:
//		Delete a SFX sound by SndID
//
//	Input:			nSndID			sound Id number to delete
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxDeleteSnd( ULONG nSndID )
{
	SFX_SND*	pSfxTblPtr = (SFX_SND*)SND_NULL_SND_PTR;
	BOOL		error      = TRUE;		// assume a failure

#if 0
	char*		pAudioName;
#endif

	if ( !SFXenabled )
	{
		error = FALSE;
		goto exit;
	}

	// make sure we have a useable ID
	if ( nSndID == (ULONG)SFX_NULL_SND_ID )
	{
		// no need to delete this
		error = FALSE;
		goto exit;
	}

#if 0
	pAudioName = audioSndIDname( nSndID );
#endif

	// find the sound in the table
	pSfxTblPtr = sfxFindSndID( nSndID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// no need to delete this
		error = FALSE;
		goto exit;
	}

	// lock this sound
	pSfxTblPtr->bLock	= TRUE;

	// free up this table entry
	if ( pSfxTblPtr->pSndData )
	{
		free( pSfxTblPtr->pSndData );
#ifdef MALLOC_DEBUG
		TRACE( "free: SFX snd data [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}

	if ( pSfxTblPtr->pDSBuffer )
	{
		error = pSfxTblPtr->pDSBuffer->Release();
		if ( error != DS_OK )
		{
			// report an error
			TRACE("ERROR:  failed to relase the DirectSoundbuffer (%s) [%s:%d]\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
			goto exit;
		}
	}

	// now delete the snd
//	sndDelete( pSfxTblPtr->nSndID );
	sndDelete( pSfxTblPtr->nSfxID );

	// re-initalize this entry
	//	pSfxTblPtr->bLock				= FALSE;		// CLEAR THIS AT END
	pSfxTblPtr->nAudioID		= SND_NULL_SND_ID;	// SFX sound identifier
	pSfxTblPtr->nSfxID			= SND_NULL_SND_ID;	// SFX sound identifier
	pSfxTblPtr->nSndID			= SND_NULL_SND_ID;	// sound identifier
	pSfxTblPtr->bFlags			= SND_CLEAR_FLAG;	// Boolean Flag fields
													// 0    : resource flag
													// 1    : streaming flag															// 2-15 : unused
	pSfxTblPtr->nImageLen		= 0;				// length of sound data
	pSfxTblPtr->nPlayBufferLen	= 0;				// length of play buffer
	pSfxTblPtr->pSndData		= NULL;				// play data buffer
	pSfxTblPtr->pDSBuffer		= NULL;				// DirectSound play buffer

	// if we got here we we're successful
	--SFXsoundsActive;
	error = FALSE;

#if 0
	TRACE("strmDeleteSnd( A:%s-S:%ld )\n", pAudioName, nSndID );
#endif

exit:
	// unlock this sound
	if( pSfxTblPtr != (SFX_SND*)SFX_NULL_SND_PTR ) 
		pSfxTblPtr->bLock = FALSE;

#if 0
	if ( error )
		TRACE("sfxDeleteSnd( A:%s-S:%ld ) ERROR\n", pAudioName, nSndID );
#endif

	return( error );
}

///========================================================================
//	Function:		sfxDeleteSfx()
//
//	Description:
//		Delete a SFX sound by SfxID
//
//	Input:			nSndID			sound Id number to delete
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxDeleteSfx( ULONG nSfxID )
{
	SFX_SND*	pSfxTblPtr = (SFX_SND*)SND_NULL_SND_PTR;
	BOOL		error      = TRUE;		// assume a failure

	if ( !SFXenabled )
	{
		error = FALSE;
		goto exit;
	}

	// make sure we have a useable ID
	if ( nSfxID == (ULONG)SFX_NULL_SND_ID )
	{
		// no need to delete this
		error = FALSE;
		goto exit;
	}

#ifdef SND_DEBUG
TRACE("sfxDeleteSnd( S:%ld ) ", nSfxID );
#endif

	// find the sound in the table
	pSfxTblPtr = sfxFindSfxID( nSfxID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// no need to delete this
		error = FALSE;
		goto exit;
	}

	// lock this sound
	pSfxTblPtr->bLock	= TRUE;

	// free up this table entry
	if ( pSfxTblPtr->pSndData )
	{
		free( pSfxTblPtr->pSndData );
#ifdef MALLOC_DEBUG
		TRACE( "free: SFX snd data [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}

	if ( pSfxTblPtr->pDSBuffer )
	{
		error = pSfxTblPtr->pDSBuffer->Release();
		if ( error != DS_OK )
		{
			// report an error
			TRACE("ERROR:  failed to relase the DirectSoundbuffer (%s) [%s:%d]\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
			goto exit;
		}
	}

	// now delete the snd
	sndDelete( pSfxTblPtr->nSndID );
//	sndDelete( pSfxTblPtr->nSfxID );

	// re-initalize this entry
	//	pSfxTblPtr->bLock				= FALSE;		// CLEAR THIS AT END
	pSfxTblPtr->nSfxID			= SFX_NULL_SND_ID;	// SFX sound identifier
	pSfxTblPtr->nSndID			= SFX_NULL_SND_ID;	// sound identifier
	pSfxTblPtr->bFlags			= SND_CLEAR_FLAG;	// Boolean Flag fields
													// 0    : resource flag
													// 1    : streaming flag															// 2-15 : unused
	pSfxTblPtr->nImageLen		= 0;				// length of sound data
	pSfxTblPtr->nPlayBufferLen	= 0;				// length of play buffer
	pSfxTblPtr->pSndData		= NULL;				// play data buffer
	pSfxTblPtr->pDSBuffer		= NULL;				// DirectSound play buffer

	// if we got here we we're successful
	--SFXsoundsActive;
	error = FALSE;

#ifdef SND_DEBUG
TRACE( " deleted." );
#endif

exit:
	// unlock this sound
	if( pSfxTblPtr != (SFX_SND*)SFX_NULL_SND_PTR ) 
		pSfxTblPtr->bLock = FALSE;

#ifdef SND_DEBUG
TRACE( "\n" );
#endif

	return( error );
}

///========================================================================
//	Function:		sfxCleanUp()
//
//	Description:
//		clean up and possibly delete a SFX sound by sndID
//
//	Input:			nSndID			sound Id number to be cleaned up
//
//	Ouput:			none
//
///========================================================================

void	sfxCleanUp( ULONG nSndID )
{
	HRESULT				result;
	DWORD				status;
	LPDIRECTSOUNDBUFFER pDSbuffer;
	SFX_SND*			pSfxTblPtr;

	if ( !SFXenabled )	return;

	if ( nSndID == SND_NULL_SND_ID )	return;

	// find the sound in the table
	pSfxTblPtr = sfxFindSndID( nSndID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )		return;

	// first check to see if this sound is deleteable
	if ( (pSfxTblPtr->bFlags & SND_DELETE_FLAG) != SND_DELETE_FLAG )	return;

	// next check to see if this sound has been played
	if ( (pSfxTblPtr->bFlags & SND_PLAYING_FLAG) != SND_PLAYING_FLAG )	return;

	// finally check to see if this sound is playing
	pDSbuffer = pSfxTblPtr->pDSBuffer;
	result    = pDSbuffer->GetStatus( &status );
	if ( result != DS_OK ) return;
	if ( (status == DSBSTATUS_PLAYING) /* || (status == DSBSTATUS_LOOPING) */ )	return;

	// go ahead and delete this sound
#if 0
TRACE( "SFX - clean up DELETE of %d:%d:%d:%s\n",
	  pSfxTblPtr->nAudioID, pSfxTblPtr->nSfxID, pSfxTblPtr->nSndID, audioIDname(pSfxTblPtr->nAudioID) );
#endif
	sfxDeleteSnd( nSndID );

	// now delete the snd
	audioDeleteSnd( nSndID );
}

///========================================================================
//	Function:		sfxTableCleanUp()
//
//	Description:
//		clean up and delete any SFX sounds in the local SFX table
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	sfxTableCleanUp( void )
{
	HRESULT				result;
	DWORD				status;
	LPDIRECTSOUNDBUFFER pDSbuffer;
	SFX_SND*			pSfxTblPtr;
	int					index;

	if ( !SFXenabled )	return;

	// cleanup the sfx lookup table
	pSfxTblPtr = SFXlookupTable;
	if ( pSfxTblPtr != (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// clean up each legal sound in the table
		for ( index=0; index<(int)SFXmaxSounds; ++index )
		{
			// delete this sound
			if ( pSfxTblPtr->nSndID != (ULONG)SFX_NULL_SND_ID )
			{
				// first check to see if this sound is deleteable
				if ( (pSfxTblPtr->bFlags & SND_DELETE_FLAG) == SND_DELETE_FLAG )
				{
					// next check to see if this sound has been played
					if ( (pSfxTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
					{
						// finally check to see if this sound is playing
						pDSbuffer = pSfxTblPtr->pDSBuffer;
						result    = pDSbuffer->GetStatus( &status );
						if ( result == DS_OK )
						{
							if ( (status != DSBSTATUS_PLAYING) /* && (status != DSBSTATUS_LOOPING) */ )
							{
#if 0
TRACE( "SFX - clean up DELETE of %d:%d:%d:%s\n",
	  pSfxTblPtr->nAudioID, pSfxTblPtr->nSfxID, pSfxTblPtr->nSndID, audioIDname(pSfxTblPtr->nAudioID) );
#endif
								sfxDeleteSnd( pSfxTblPtr->nSndID );		// go ahead and delete this sound

								// now delete the snd
								audioDeleteSnd( pSfxTblPtr->nSndID );
							}
						}
					}
				}
			}

			// check the next entry
			++pSfxTblPtr;
		}
	}
}

///========================================================================
//	Function:		sfxClose()
//
//	Description:
//		Close down an SFX .snd file
//
//	Input:			nFileID			file Id number to close
//
//	Ouput:			none
//
///========================================================================

void		sfxClose ( unsigned nFileID )
{

	if ( !SFXenabled )
		return;

	// clear the file reference and null the pointer
	sndDeleteFile( nFileID );

	// since we've closed the file, we can deallocate the SND header
	if ( SFXsndHeader )
	{
		free( SFXsndHeader );
		SFXsndHeader = NULL;
#ifdef MALLOC_DEBUG
		TRACE( "free: SFX header [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}
}

///========================================================================
//	Function:		sfxGetFrequency()
//
//	Description:
// 		Get the SFX sound frequency level (effect pitch)
//
//	Input:			nSfxID			sound Id number to retrieve pan from
//
//	Ouput:			nFrequency		current SFX frequency setting
//
///========================================================================

LONG		sfxGetFrequency ( ULONG nSfxID )
{
	LONG		nFrequency;
	SFX_SND*	pSfxTblPtr;

	if ( !SFXenabled )
		return( 0 );

	if ( nSfxID == SND_NULL_SND_ID )
		return( 0 );

	// find the sound in the table
	pSfxTblPtr = sfxFindID( nSfxID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
		nFrequency = 0;
	else				// Get the FREQUENCY value
	if ( sndGetFrequency( pSfxTblPtr->pDSBuffer, &nFrequency ) )
		nFrequency = 0;
	   
	return( nFrequency );
}

///========================================================================
//	Function:		sfxSetFrequency()
//
//	Description:
// 		Set the SFX sound requency level (effect pitch)
//
//	Input:			nSfxID			sound Id number to retrieve pan from
//					nFrequency		volume setting to apply
//
//	Ouput:			none
//
///========================================================================

BOOL		sfxSetFrequency ( ULONG nAudioID, LONG nFrequency )
{
	SFX_SND*	pSfxTblPtr;
	BOOL		error = TRUE;		// assume failed

	if ( !SFXenabled )
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
	pSfxTblPtr = sfxFindID( nAudioID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
		goto exit;

	// set the Frequency value
	if ( sndSetFrequency( pSfxTblPtr->pDSBuffer, nFrequency ) )
		goto exit;
	   
	// If we made it here we did everything ok
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sfxGetVolume()
//
//	Description:
// 		Get the SFX sound volume levels:
//
//	Input:			nSfxID			sound Id number to retrieve pan from
//
//	Ouput:			nVolume			current SFX volume setting
//
///========================================================================

LONG		sfxGetVolume ( ULONG nSfxID ) 
{
	LONG		nVolume;
	SFX_SND*	pSfxTblPtr;

	if ( !SFXenabled )
		return( 0 );

	if ( nSfxID == SND_NULL_SND_ID )
		return(0);

	// find the sound in the table
	pSfxTblPtr = sfxFindID( nSfxID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
		nVolume = 0;
	else				// Get the VOLUME value
	if ( sndGetVolume( pSfxTblPtr->pDSBuffer, &nVolume ) )
		nVolume = 0;
	   
	return( nVolume );
}

///========================================================================
//	Function:		sfxSetVolume()
//
//	Description:
// 		Set the SFX sound volume levels:
//
//	Input:			nSndID			sound Id number to retrieve pan from
//					nVolume			volume setting to apply
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL		sfxSetVolume ( ULONG nSndID, LONG nVolume )
{
	SFX_SND*	pSfxTblPtr;
	BOOL		error = TRUE;		// assume failed

	if ( !SFXenabled )
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
	pSfxTblPtr = sfxFindSndID( nSndID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
		goto exit;

	// set the Volume value
	if ( sndSetVolume( pSfxTblPtr->pDSBuffer, nVolume ) )
		goto exit;
	   
	// If we made it here we did everything ok
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sfxGetPan()
//
//	Description:
// 		Get the SFX sound pan level
//
//	Input:			nSfxID			sound Id number to retrieve pan from
//
//	Ouput:			nPan			current SFX pan setting
//
///========================================================================

LONG		sfxGetPan ( ULONG nSfxID )
{
	LONG		nPan;
	SFX_SND*	pSfxTblPtr;

	if ( !SFXenabled )
		return(0);

	if ( nSfxID == SND_NULL_SND_ID )
		return(0);

	// find the sound in the table
	pSfxTblPtr = sfxFindID( nSfxID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
		nPan = 0;
	else			// Get the PAN value
	if ( sndGetPan( pSfxTblPtr->pDSBuffer, &nPan ) )
		nPan = 0;
	   
	return( nPan );
}

///========================================================================
//	Function:		sfxSetPan()
//
//	Description:
// 		Set the SFX sound pan level
//
//	Input:			nSfxID			sound Id number to apply pan to
//					nPan			pan setting to apply
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

BOOL		sfxSetPan ( ULONG nSfxID, LONG nPan )
{
	SFX_SND*	pSfxTblPtr;
	BOOL		error = TRUE;		// assume failed

	if ( !SFXenabled )
	{
		error = FALSE;
		goto exit;
	}

	if ( nSfxID == SND_NULL_SND_ID )
	{
		error = FALSE;
		goto exit;
	}

	// find the sound in the table
	pSfxTblPtr = sfxFindID( nSfxID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
		goto exit;

	// set the PAN value
	if ( sndSetPan( pSfxTblPtr->pDSBuffer, nPan ) )
		goto exit;
	   
	// If we made it here we did everything ok
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sfxFindID()
//
//	Description:
//		Locate a SFX sound ID in the SFX lookup table
//
//	Input:			nAudioID			audio Id number to apply pan to
//
//	Ouput:			pSfxTblPtr			address of slot, SFX_NULL_SND_PTR otherwise
//
///========================================================================

SFX_SND*	sfxFindID( ULONG nAudioID )
{
	SFX_SND*	pSfxTblPtr = (SFX_SND*)SFX_NULL_SND_PTR;
	unsigned	index;

	if ( !SFXenabled )
		return( pSfxTblPtr );

	if ( nAudioID == SND_NULL_SND_ID )
		return( pSfxTblPtr );

	// find the sound in the table
	index      = 0;
	pSfxTblPtr = SFXlookupTable;
	while ( (index<SFXmaxSounds) && (pSfxTblPtr->nAudioID != nAudioID) )
	{
		++index;
		++pSfxTblPtr;
	}
   
	// did we find it ?
	if ( index >= SFXmaxSounds )
		pSfxTblPtr = (SFX_SND*)SFX_NULL_SND_PTR;
   
	return( pSfxTblPtr );    
}

///========================================================================
//	Function:		sfxFindSndID()
//
//	Description:
//		Locate a SFX snd ID in the SFX lookup table
//
//	Input:			nSndID				snd Id number to locate
//
//	Ouput:			pSfxTblPtr			address of slot, SFX_NULL_SND_PTR otherwise
//
///========================================================================

SFX_SND*	sfxFindSndID( ULONG nSndID )
{
	SFX_SND*	pSfxTblPtr = (SFX_SND*)SFX_NULL_SND_PTR;
	unsigned	index;

	if ( !SFXenabled )
		return( pSfxTblPtr );

	if ( nSndID == SND_NULL_SND_ID )
		return( pSfxTblPtr );

	// find the sound in the table
	index      = 0;
	pSfxTblPtr = SFXlookupTable;
	while ( (index<SFXmaxSounds) && (pSfxTblPtr->nSndID != nSndID) )
	{
		++index;
		++pSfxTblPtr;
	}
   
	// did we find it ?
	if ( index >= SFXmaxSounds )
		pSfxTblPtr = (SFX_SND*)SFX_NULL_SND_PTR;
   
	return( pSfxTblPtr );    
}

///========================================================================
//	Function:		sfxFindSfxID()
//
//	Description:
//		Locate a SFX snd ID in the SFX lookup table
//
//	Input:			nSndID				snd Id number to locate
//
//	Ouput:			pSfxTblPtr			address of slot, SFX_NULL_SND_PTR otherwise
//
///========================================================================

SFX_SND*	sfxFindSfxID( ULONG nSfxID )
{
	SFX_SND*	pSfxTblPtr = (SFX_SND*)SFX_NULL_SND_PTR;
	unsigned	index;

	if ( !SFXenabled )
		return( pSfxTblPtr );

	if ( nSfxID == SND_NULL_SND_ID )
		return( pSfxTblPtr );

	// find the sound in the table
	index      = 0;
	pSfxTblPtr = SFXlookupTable;
	while ( (index<SFXmaxSounds) && (pSfxTblPtr->nSfxID != nSfxID) )
	{
		++index;
		++pSfxTblPtr;
	}
   
	// did we find it ?
	if ( index >= SFXmaxSounds )
		pSfxTblPtr = (SFX_SND*)SFX_NULL_SND_PTR;
   
	return( pSfxTblPtr );    
}

///========================================================================
//	Function:		sfxExist()
//
//	Description:
//		Does a SND id exist in the SND lookup table
//
//	Input:			nSndID			sound Id number
//
///========================================================================

BOOL sfxExist ( ULONG nSndID )
{
	SFX_SND*	pSfxTblPtr;

	pSfxTblPtr = sfxFindSndID ( nSndID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
		return FALSE;
	return ( sndExist ( pSfxTblPtr->nSfxID ) );
}

///========================================================================
//	Function:		sfxInPlay()
//
//	Description:
//		check to see if a SFX sound has been created and is in play
//
//	Input:			nSndID			sound Id number
//
///========================================================================

BOOL sfxInPlay ( ULONG nSndID )
{
	LPDIRECTSOUNDBUFFER pDSbuffer;
	SFX_SND*			pSfxTblPtr;
	HRESULT				result;
	DWORD				status;

	pSfxTblPtr = sfxFindSndID ( nSndID );
	if ( pSfxTblPtr == (SFX_SND*)SFX_NULL_SND_PTR )
		return FALSE;
	if ( !sndExist ( pSfxTblPtr->nSfxID ) )
		return FALSE;

	// next check to see if this sound has been played
	if ( (pSfxTblPtr->bFlags & SND_PLAYING_FLAG) == SND_PLAYING_FLAG )
	{
		// finally check to see if this sound is playing
		pDSbuffer = pSfxTblPtr->pDSBuffer;
		result    = pDSbuffer->GetStatus( &status );
		if ( result == DS_OK )
			if ( status == DSBSTATUS_PLAYING )
				return TRUE;
	}
	return FALSE;
}

///========================================================================
//	Function:		sfxFindSlot()
//
//	Description:
//		Locate an empty SFX sound slot in the SFX lookup table
//
//	Input:			none
//
//	Ouput:			pSfxTblPtr			address of slot, SFX_NULL_SND_PTR otherwise
//
///========================================================================

SFX_SND*	sfxFindSlot( void )
{
	SFX_SND*	pSfxTblPtr;
	unsigned	index;

	if ( !SFXenabled )
	{
		pSfxTblPtr = (SFX_SND*)SFX_NULL_SND_PTR;
		return( pSfxTblPtr );
	}

	// find the sound in the table
	index      = 0;
	pSfxTblPtr = SFXlookupTable;
	while ( (index<SFXmaxSounds) && (pSfxTblPtr->nSndID != SFX_NULL_SND_ID) )
	{
		++index;
		++pSfxTblPtr;
	}
   
	// did we find it ?
	if ( index == SFXmaxSounds )
		pSfxTblPtr = (SFX_SND*)SFX_NULL_SND_PTR;
   
	return( pSfxTblPtr );    
}

///========================================================================
//	Function:		sfxGetOffset()
//
//	Description:
//		Locate a SFX sound offset in the SFX lookup table
//
//	Input:			nSfxID			sound Id number to apply pan to
//					nIndexToLoad	relative index from sndID
//
//	Ouput:			offset			offset of slot, SFX_NULL_SND_ID otherwise
//
///========================================================================

ULONG	sfxGetOffset( ULONG nSfxID, unsigned nIndexToLoad )
{
	ULONG		offset;
	unsigned	index;
	unsigned	maxIndex;

	if ( !SFXenabled )
		return(0);

	if ( nSfxID == SND_NULL_SND_ID )
		return(0);

	// search the header for this snd id
	offset  = (ULONG)SFX_NULL_SND_ID;
	maxIndex = SFXsndHeader->numberOfSounds;
	index   = 0;
	while ( (SFXsndHeader->sounds[ index ].soundID != nSfxID) && (index<maxIndex) )
		++index;

	if ( SFXsndHeader->sounds[ index ].soundID != nSfxID )
	{
		// report an error that the snd ID is not in this file
		TRACE("ERROR:  snd ID (%d) not in .snd file [%s:%d]\n", 
			nSfxID, __FILE__, __LINE__ );
		goto exit;
	}
	
	// now adjust our choice based on the index
	if ( (index + nIndexToLoad) > maxIndex )
	{
		// report an error that the snd index exceeds table size
		TRACE("ERROR: load index (%d+%d) excceds table size (%d) [%s:%d]\n", 
			(index), __FILE__, __LINE__ );
		goto exit;
	}

	// adjust the indexed element
	(index) += nIndexToLoad;
	offset = SFXsndHeader->sounds[ index ].offset;

exit:
	return( offset );
}

///========================================================================
//	Function:		sfxSetOn(BOOL on)
//	Function:		sfxGetOn()
//	Function:		sfxToggleOn()
//
//	Description: maintainence of sound effects on/off flag
//
///========================================================================
void	sfxSetOn(BOOL on)	{
	SFXon = on;
//	TRACE( "sfxSetOn() - SFXon = %s\n", (SFXon?"TRUE":"FALSE"));
}

BOOL	sfxGetOn()	{
//	TRACE( "sfxGetOn() - SFXon = %s\n", (SFXon?"TRUE":"FALSE"));
	return SFXon;
}

void	sfxToggleOn()	{
	SFXon ^= TRUE;
}

///========================================================================
//	Function:		sfxGetMasterVolume()
//
//	Description:
// 		Get the SFX sound volume levels:
//
//	Input:			none
//
//	Ouput:			nVolume			current SFX volume setting
//
///========================================================================

LONG		sfxGetMasterVolume ( void ) 
{
	return( SFXmasterVolume );
}

///========================================================================
//	Function:		sfxSetVolume()
//
//	Description:
// 		Set the SFX sound volume levels:
//
//	Input:			nSfxID				sound Id number to retrieve pan from
//					nVolumePercentage	volume setting to apply
//
//	Ouput:			TRUE			if successfull, FALSE otherwise
//
///========================================================================

void	sfxSetMasterVolume ( LONG nVolumePercentage )
{
	SFX_SND	*pSfxTblPtr;
	int		nIndex;

	SFXmasterVolume = nVolumePercentage;

	// now adjust all sounds to this volume precentage
	if ( !SFXenabled )
		return;

	// cleanup the sfx lookup table
	pSfxTblPtr = SFXlookupTable;
	if ( pSfxTblPtr != (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// lower the volume of each legal sound in the table
		for ( nIndex=0; nIndex<(int)SFXmaxSounds; ++nIndex )
		{
			// change the volume of this sound
			if ( pSfxTblPtr->nSndID != (ULONG)SFX_NULL_SND_ID )
				SndSetVolumePercent( pSfxTblPtr->nSndID, nVolumePercentage, FALSE );

			// check the next entry
			++pSfxTblPtr;
		}
	}
}

///========================================================================
//	Function:		sfxDumpTable()
//
//	Description:
//		Dump the SFX table entries
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	sfxDumpTable( void )
{
	SFX_SND*			pSfxTblPtr;
	int					index;

	if ( !SFXenabled )	return;

	// cleanup the sfx lookup table
	pSfxTblPtr = SFXlookupTable;
	if ( pSfxTblPtr != (SFX_SND*)SFX_NULL_SND_PTR )
	{
		// clean up each legal sound in the table
		for ( index=0; index<(int)SFXmaxSounds; ++index )
		{
			// delete this sound
			if ( pSfxTblPtr->nSndID != (ULONG)SFX_NULL_SND_ID )
			{
				TRACE( "SFX Table Entry %d: %d:%d:%d:%s:", index,
					  pSfxTblPtr->nAudioID, pSfxTblPtr->nSfxID, pSfxTblPtr->nSndID, audioIDname(pSfxTblPtr->nAudioID) );

				// SND Flag Fields
				if ( pSfxTblPtr->bFlags  ==	SND_CLEAR_FLAG)
					TRACE( "SND_CLEAR_FLAG " );
				else
				{
					if ( (pSfxTblPtr->bFlags & SND_SFX_FLAG)       ==	SND_SFX_FLAG)
						TRACE( "SND_SFX_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_STREAM_FLAG)    ==	SND_STREAM_FLAG)
						TRACE( "SND_STREAM_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_VOICE_FLAG)     ==	SND_VOICE_FLAG)
						TRACE( "SND_VOICE_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_MUSIC_FLAG)     ==	SND_MUSIC_FLAG)
						TRACE( "SND_MUSIC_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_RESOURCE_FLAG)  ==	SND_RESOURCE_FLAG)
						TRACE( "SND_RESOURCE_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_EOS_FLAG)       ==	SND_EOS_FLAG)
						TRACE( "SND_EOS_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_TIMER_FLAG)     ==	SND_TIMER_FLAG)
						TRACE( "SND_TIMER_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_PLAYING_FLAG)   ==	SND_PLAYING_FLAG)
						TRACE( "SND_PLAYING_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_FADE_IN_FLAG)   ==	SND_FADE_IN_FLAG)
						TRACE( "SND_FADE_IN_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_FADE_OUT_FLAG)  ==	SND_FADE_OUT_FLAG)
						TRACE( "SND_FADE_OUT_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_LOOP_FLAG)      ==	SND_LOOP_FLAG)
						TRACE( "SND_LOOP_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_INSTALLED_FLAG) ==	SND_INSTALLED_FLAG)
						TRACE( "SND_INSTALLED_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_CUED_FLAG)      ==	SND_CUED_FLAG)
						TRACE( "SND_CUED_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_DELETE_FLAG)    ==	SND_DELETE_FLAG)
						TRACE( "SND_DELETE_FLAG " );
					if ( (pSfxTblPtr->bFlags & SND_DONE_FLAG)      ==	SND_DONE_FLAG)
						TRACE( "SND_DONE_FLAG " );
				}
				TRACE("\n");
			}

			// check the next entry
			++pSfxTblPtr;
		}
	}
	ASSERT(0);
}

///========================================================================
//								EOF
///========================================================================
