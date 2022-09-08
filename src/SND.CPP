//========================================================================
//	FILE:			$Workfile: SND.CPP $
//
//	DESCRIPTION:	SND processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, May 02, 1996
//
//	REVISION:		$Header: /ArmyMen/src/SND.CPP 20    4/02/98 3:35p Phu $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	sndInit()
//		Initialize the SND processor
//	sndExit()
//		Terminate the SND processor.
//	sndCreate()
//		Create a SND.
//	sndDelete()
//		Delete a SND.
//	sndDirectSoundCleanup()
//		Cleanup the SND processor structures.
//	sndGetDSobject()
//		Retrieve the current DirectSound Object.
//	sndGetFrequency()
// 		Get the SND Frequency levels (effect pitch)
//	sndSetFrequency()
// 		Set the SND Frequency levels (effect pitch)
//	sndGetVolume()
// 		Get the SND Volume levels:
//	sndSetVolume()
// 		Set the SND Volume levels:
//	sndGetPan()
// 		Get the SND Pan levels
//	sndSetPan()
// 		Set the SND Pan levels
//	sndStop()
// 		Stop a sound being played
//	sndFindWave()
//		Find the "WAVE" chunk. This reads to the end of the "WAVE" header.
//	sndFindWaveformatex()
//		Retrieve the WAVEFORMATEX information
//	sndFindSample()
//		Locate the raw smaple data information.
//	sndFindSndID()
//		Locate a SND id in the SND lookup table
//	sndFindAudioID()
//		Locate a AUDIO id in the SND lookup table
//	sndFindSlot()
//		Locate a SND slot in the SND lookup table
//	sndSaveFile()
//		Save the SND fileptr and filename for an OPEN snd file.
//		Used during loading a sound.
//	sndGetFile()
//		Retreive the STRM fileptr associated with a file pointer
//	sndGetFileName()
//		Retreive the SND filename associated with a file ID
//	sndDeleteFile()
//		Delete the SND filename and close the file pointer associated with a file id
//========================================================================
//  History
//
//  $Log: /ArmyMen/src/SND.CPP $
//  
//  20    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  19    3/19/98 10:16a Aburgess
//  changed error message
//  
//  18    3/16/98 4:36p Aburgess
//  modifications made to correctly look up the SFX snd ID
//  
//  17    3/16/98 12:56p Aburgess
//  modifications to support vehicle decel,acel,and looping
//  
//  16    3/15/98 5:48p Nrobinso
//  add sndExist
//  
//  15    3/06/98 5:17p Aburgess
//  correction of audio flag useage
//  
//  14    2/25/98 3:11p Aburgess
//  corrected proper use of (SND_FILES*)SND_NULL_SND_PTR as a null
//  reference.
//  
//  13    2/24/98 5:36p Bwilcox
//  fixed pSndFiles cleanup exit code to use the correct null value
//  
//  12    2/24/98 4:44p Bwilcox
//  sndinit and exit are not symmetric in all cases, so cleared ptrs as
//  predefined data
//  
//  11    2/24/98 10:51a Aburgess
//  simple comment correction
//  
//  10    1/12/98 10:43a Aburgess
//  changes made to support Smacker DSound useage
//  
//  9     12/09/97 12:12p Phu
//  
//  8     12/04/97 11:53a Nrobinso
//  patch problem in audioStopAll by putting a NULL pointer check in
//  sndStop
//  
//  7     12/04/97 9:14a Aburgess
//  Modifications made to properly handle delete race condition with
//  strmMonitor. Actual sound allocation tracking added to help minimize
//  static tables for audio
//  
//  6     11/20/97 3:32p Aburgess
//  modifications made to allow app to run regardless of existence of .ASD,
//  .AST files or DirectSound itself
//  
//  5     11/17/97 10:39a Aburgess
//  disabled debug with compile time flags
//  
//  4     11/17/97 10:08a Aburgess
//  rework of audio/sfx/strm/voice/snd interface
//  
//  3     11/16/97 2:21p Aburgess
//  cleanup of sound files (fclose)
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  12    5/14/97 4:27p Dbunch
//  Fixed SND reference count bug
//  
//  11    4/14/97 7:28a Aburgess
//  modifications made to support full Army creation along with unit
//  reserves. Vehicle reserves have yet to be done.
//  
//  10    10/02/96 11:25a Aburgess
//  removed superfluous TRACE code
//  
//  9     9/16/96 8:13a Aburgess
//  free on a null possibility corrected
//  
//  8     9/10/96 12:59p Aburgess
//  move commonly used but infrequently changed header files to stdafx.h
//  (precompiled header)
//  
//  5     6/26/96 10:28a Aburgess
//  added new Source Control headers
// 
//  $Nokeywords:$
///========================================================================

#include "stdafx.h"

#include "snd.h"			// SND         defines, structures, and prototypes

///========================================================================
//							LOCAL DEFINES
///========================================================================
extern	char*	audioIDname( ULONG nAudioID );

///========================================================================
//							LOCAL VARIABLES
///========================================================================

static SND*				pSndTable;
static unsigned			nMaxSnds;
static unsigned			nLoadedSounds;
static SND_FILES*		pSndFiles;
static USHORT			nSndFileID;
static unsigned			nMaxSndFiles;
static unsigned			nSoundFiles;
static LPDIRECTSOUND	pDirectSound;

BOOL					SNDenabled;

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================

///========================================================================
//	Function:		sndInit()
//
//	Description:
//		Initialize the SND processor
//
//	Input:			none
//
//	Ouput:			error		TRUE if successful, FALSE otherwise
//
///========================================================================

BOOL		sndInit( HWND baseWnd, UINT nMaxSounds )
{
	SND*		pSndPtr;
	SND_FILES*	pSndFilePtr;
	ULONG		nSoundCount;
	BOOL		error = TRUE;	// assume failure

	// remember the max number of sounds
	nMaxSnds      = nMaxSounds;
	nMaxSndFiles  = SND_MAX_SND_FILES;
	nSndFileID    = 0;
	pSndFiles     = (SND_FILES*)SND_NULL_SND_PTR;
	nLoadedSounds = 0;
	nSoundFiles   = 0;

	// create the Direct Sound Object
	error = DirectSoundCreate( NULL, &pDirectSound, NULL );
	if ( error != DS_OK )
	{
		// report an error
		TRACE("ERROR: Could not create DirectSound object. (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );

		// cleanup the direct sound object
		sndDirectSoundCleanup();
		goto exit;
	}

    // Set the cooperative level for the DS buffer
	error = pDirectSound->SetCooperativeLevel(baseWnd,DSSCL_NORMAL);
	if ( error != DS_OK )
	{
		// report an error
		TRACE("ERROR: failed to set cooperative level. (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// now allocate the sound file manager table
	pSndFiles = (SND_FILES*)malloc( nMaxSndFiles * sizeof(SND_FILES) );
	if ( pSndFiles == NULL )
	{
		// report an error
		TRACE("ERROR: Insufficient memory available. [%s:%d]\n", 
			  __FILE__, __LINE__ );
        pSndFiles = (SND_FILES*)SND_NULL_SND_PTR;
		goto exit;
	}

#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): SND file manager table [%s : %d]\n",
			( nMaxSndFiles * sizeof(SND_FILES) ),__FILE__, __LINE__ );
#endif

	// clear the snd file table
	pSndFilePtr = pSndFiles;
	for ( nSoundCount=0; nSoundCount<nMaxSndFiles; ++ nSoundCount )
	{
		pSndFilePtr->nSndFileID   = (unsigned)SND_NULL_SND_ID;
		pSndFilePtr->pSndFile     = NULL;
		pSndFilePtr->pSndFileName = NULL;
		++pSndFilePtr;
	}


	// now allocate the sound table
	pSndTable = (SND*)malloc( nMaxSnds * sizeof(SND) );
	if ( pSndTable == NULL )
	{
		// report an error
		TRACE("ERROR: Insufficient memory available. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): SND table [%s : %d]\n", ( nMaxSnds * sizeof(SND) ),__FILE__, __LINE__ );
#endif

	// clear the snd table
	pSndPtr = pSndTable;
	for ( nSoundCount=0; nSoundCount<nMaxSnds; ++ nSoundCount )
	{
		pSndPtr->nAudioID  = SND_BAD_SND_ID;
		pSndPtr->nSndID    = SND_BAD_SND_ID;
		pSndPtr->bFlags    = SND_CLEAR_FLAG;
		pSndPtr->nRefCount = 0;
		++pSndPtr;
	}

	// we made it here, success
	SNDenabled = TRUE;
	error = FALSE;

exit:
	return( error );
}

///========================================================================
//	Function:		sndExit()
//
//	Description:
//		Terminate the SND processor.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void		sndExit( void )
{
	SND*		pSndTblPtr;
	SND_FILES*	pSndFilesTblPtr;
	SND_RES*	pResPtr;
	SND_WAV*	pWavPtr;
	unsigned	snd;

	// cleanup the sound table
	if ( pSndTable )
	{
		// free up each entry in the table
		pSndTblPtr = pSndTable;
		for ( snd=0; snd<nMaxSnds; ++snd )
		{
			// is there a sound here?
			if ( pSndTblPtr->nAudioID != SND_NULL_SND_ID )
			{
				// what type of sound is it
				if ( pSndTblPtr->bFlags & SND_RESOURCE_FLAG )
				{
					pResPtr = &(pSndTblPtr->resSnd);

					// free up the resource name
					if ( pResPtr->pResName )
					{
						free ( pResPtr->pResName );
						pResPtr->pResName = NULL;
					}

					// free up the data buffer
					if ( pResPtr->pSndData )
					{
						free ( pResPtr->pSndData );
						pResPtr->pSndData = NULL;
					}
				}
				else
				{
					pWavPtr = &(pSndTblPtr->wavSnd);

					// free up the filename
					if ( pWavPtr->pSndFileName )
					{
						free ( pWavPtr->pSndFileName );
						pWavPtr->pSndFileName = NULL;
					}
				}
			}

			// update the snd pointer
			++ pSndTblPtr;
		}

		// now finally free the table
		free( pSndTable );
		pSndTable = NULL;
#ifdef MALLOC_DEBUG
		TRACE( "free: SND table [%s : %d]\n", __FILE__, __LINE__ );
#endif
	}

	// cleanup the sound file table
	if ( pSndFiles != (SND_FILES*)SND_NULL_SND_PTR )
	{
		// free up each entry in the table
		pSndFilesTblPtr = pSndFiles;
		for ( snd=0; snd<nSoundFiles; ++snd )
		{
			// is there a sound here?
			if ( pSndFilesTblPtr->pSndFile )
			{
				// is the filename there
				if ( pSndFilesTblPtr->pSndFileName )
				{
					free ( pSndFilesTblPtr->pSndFileName );
					pSndFilesTblPtr->pSndFileName = NULL;
				}

				// close the file
				fclose( pSndFilesTblPtr->pSndFile );
				pSndFilesTblPtr->pSndFile = NULL;
			}

			// update the snd file pointer
			++pSndFilesTblPtr;
		}

		// now finally free the table
		if ( pSndFiles != (SND_FILES*)SND_NULL_SND_PTR )
		{
			free( pSndFiles );
#ifdef MALLOC_DEBUG
			TRACE( "free: SND manager files [%s : %d]\n", __FILE__, __LINE__ );
#endif
		}
		pSndFiles = (SND_FILES*)SND_NULL_SND_PTR;
	}

	// cleanup the direct sound object
	sndDirectSoundCleanup();
}

///========================================================================
//	Function:		sndCreate()
//
//	Description:
//		Create a SND.
//
//	Input:			nAudioID	new sound to create
//					bFlags		specifies whether this is a WAVE or RES snd
//					nFileID		file id to file data
//					offset		offset into sound file for data, updated to
//								raw sample position
//
//	Ouput:			nSndID		SND id assigned this instance
//								SND_BAD_SND_ID if failure.
//
///========================================================================

ULONG		sndCreate( ULONG nAudioID, USHORT bFlags, unsigned nFileID, ULONG* offset )
{
	FILE*		pSndFile;
	HRSRC		hResource;
	int			size;
	char*		pFileName;
	char*		pSndData;
	SND*		pSndPtr;
	unsigned	status;
	ULONG		nSndID = SND_BAD_SND_ID;

	// see if we already have this sound
	status = sndFindAudioID( nAudioID, &pSndPtr );
	if ( status == SND_ACTIVE_STATUS )		// did we have it already? 
	{
		// have it, ignore subsequent request and return this ID
		nSndID = pSndPtr->nSndID;

		// increment the reference count
		++(pSndPtr->nRefCount);

		goto exit;
	}

	// find a vacant slot
	pSndPtr = sndFindSlot( &nSndID );
	if ( pSndPtr == (SND*)SND_NULL_SND_PTR )
	{
		nSndID = SND_NULL_SND_ID;
		goto exit;
	}

	// the file info for this sound
	pSndFile = sndGetFile( nFileID );
	pFileName = sndGetFileName( nFileID );

	// now we have a vacant SND, fill it in
	pSndPtr->nAudioID = nAudioID;
	pSndPtr->nSndID   = nSndID;
	pSndPtr->bFlags   = bFlags;
	if ( (bFlags & SND_RESOURCE_FLAG) != SND_RESOURCE_FLAG )
	{
		// WAVE FILE PROCESSING


		// get the WAVEFORMATEX data
		if ( sndFindWaveformatex( pSndFile, *offset, &(pSndPtr->wavSnd.wfSndFormat) ) )
		{
			// report an error
			TRACE("ERROR:WAVEFORMATEX header access failure\n" ); 
			goto cleanUp;
		}

		// get the raw sample data
		if ( sndFindSample( pSndFile, *offset, 0, &(pSndPtr->wavSnd.nSndSize) ) )
		{
			// report an error
			TRACE("ERROR: Raw Sample Data access failure\n");
			nSndID = SND_NULL_SND_ID;
			goto cleanUp;
		}

		// initialize the read location
		pSndPtr->wavSnd.pSndFile  = pSndFile;
		*offset                   = ftell( pSndFile );
		pSndPtr->wavSnd.nSndStart = *offset;

		// allocate memory for the file name
		if (pFileName)
		{
			// get the size of the name
			size = strlen(pFileName);
			pSndPtr->wavSnd.pSndFileName = (char*)malloc( size+1 );
			if (pSndPtr->wavSnd.pSndFileName == NULL)
			{
				// report an error
				TRACE("ERROR: Insufficient memory available. [%s:%d]\n", 
					  __FILE__, __LINE__ );
				goto cleanUp;
			}
			else
				strcpy( pSndPtr->wavSnd.pSndFileName, pFileName );

#ifdef MALLOC_DEBUG
			TRACE( "malloc (%ld): SND Filename [%s : %d]\n", (size+1), __FILE__, __LINE__ );
#endif
		}
		else
			pSndPtr->wavSnd.pSndFileName = NULL;
	}
	else
	{
		// RESOURCE PROCESSING

		// begin filling in the resource information
		pSndPtr->resSnd.nResID    = nAudioID;

		// allocate memory for the resource name
		size = strlen(MAKEINTRESOURCE(nAudioID));
		pSndPtr->resSnd.pResName = (char*)malloc( size+1 );
		if (pSndPtr->resSnd.pResName == NULL)
		{
			// report an error
			TRACE("ERROR: Insufficient memory available. [%s:%d]\n", 
				  __FILE__, __LINE__ );
			goto cleanUp;
		}
		strncpy( pSndPtr->resSnd.pResName, MAKEINTRESOURCE(nAudioID), size );

#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): SND resource [%s : %d]\n", ( size+1 ), __FILE__, __LINE__ );
#endif

		// now allocate data buffer space for the sfx
		hResource                 = FindResource( NULL, pSndPtr->resSnd.pResName,
												  RT_RCDATA);
		pSndPtr->resSnd.nImageLen = SizeofResource( NULL, hResource );
		if ( pSndPtr->resSnd.nImageLen )
		{
			pSndPtr->resSnd.pSndData = (unsigned char*)malloc( pSndPtr->resSnd.nImageLen );
			if (pSndPtr->resSnd.pSndData == NULL)
			{
				// report an error
				TRACE("ERROR: Insufficient memory available. [%s:%d]\n", 
					  __FILE__, __LINE__ );
				goto cleanUp;
			}
#ifdef MALLOC_DEBUG
			TRACE( "malloc (%ld) : SND resource snd data [%s : %d]\n",
					(pSndPtr->resSnd.nImageLen), __FILE__, __LINE__ );
#endif
		}

		// access the raw data
		pSndData = (char*)GlobalLock( hResource );
		if ( pSndData != NULL )
			memcpy( pSndPtr->resSnd.pSndData, pSndData, pSndPtr->resSnd.nImageLen );
		GlobalUnlock( hResource );
	}

	// up the sound count
	++nLoadedSounds;

	// increment the reference count
	++(pSndPtr->nRefCount);

	// if we're here we were successful and the ID has been chosen
#ifdef SND_DEBUG
	TRACE( "sndCreate(): nAudioID (%d) nSndID (%d) nRefCnt (%d) \"%s\":",
		pSndPtr->nAudioID, pSndPtr->nSndID, pSndPtr->nRefCount,
		audioIDname( nAudioID )
		 );
	if ( (pSndPtr->bFlags & SND_SFX_FLAG) == SND_SFX_FLAG )
		TRACE( "SFX" );
	if ( (pSndPtr->bFlags & SND_VOICE_FLAG) == SND_VOICE )
		TRACE( "VOICE" );
	if ( (pSndPtr->bFlags & SND_MUSIC_FLAG) == SND_MUSIC_ID )
		TRACE( "MUSIC" );
	TRACE( "\n" );
#endif

	nSndID  = pSndPtr->nSndID;
	goto exit;

	// if we're here we had a problem and want to clean up
cleanUp:
	nSndID                 = SND_NULL_SND_ID;
	pSndPtr->nAudioID	   = SND_BAD_SND_ID;
	pSndPtr->nSndID		   = SND_BAD_SND_ID;
	pSndPtr->bFlags        = SND_CLEAR_FLAG;
	pSndPtr->nRefCount     = 0;

exit:
	return( nSndID );
}

///========================================================================
//	Function:		sndDelete()
//
//	Description:
//		Delete a SND.
//
//	Input:			nSndID
//
//	Ouput:			none
//
///========================================================================

void		sndDelete( ULONG nSndID )
{
	SND*		pSndTblPtr;
	SND_RES*	pResPtr;
	SND_WAV*	pWavPtr;
	unsigned	status;
	int			nSndIdx;

	// cleanup the sound table
	if ( pSndTable )
	{

#ifdef SND_DEBUG
TRACE("sndDelete( S:%ld ) ", nSndID );
TRACE( "BEFORE DELETE:\n" );
pSndTblPtr = pSndTable;
for( nSndIdx=0; nSndIdx<nMaxSnds;++nSndIdx)
{
	if ( pSndTblPtr->nSndID != SND_NULL_SND_ID )
	{
		TRACE( "snd %d: %s A:%ld S:%ld F:0x%x R:%d\n",
			nSndIdx,
			audioIDname(pSndTblPtr->nAudioID),
			pSndTblPtr->nAudioID,
			pSndTblPtr->nSndID,
			pSndTblPtr->bFlags,
			pSndTblPtr->nRefCount);
	}
	++pSndTblPtr;
}
#endif

		// free up entry in the table
		status = sndFindSndID( nSndID, &pSndTblPtr, &nSndIdx );

		// is there a sound here?
		if ( status == SND_BAD_STATUS )
		{
			TRACE( "WARNING: failed to find SndID (%ld)\n", nSndID );
			goto exit;
		}

		if ( pSndTblPtr->nRefCount == 1 )
		{
			// what type of sound is it
			if ( pSndTblPtr->bFlags & SND_RESOURCE_FLAG )
			{
				pResPtr = &(pSndTblPtr->resSnd);

				// free up the resource name
				if ( pResPtr->pResName )
				{
					free ( pResPtr->pResName );
					pResPtr->pResName = NULL;
				}

				// free up the data buffer
				if ( pResPtr->pSndData )
				{
					free ( pResPtr->pSndData );
					pResPtr->pSndData = NULL;
				}
			}
			else
			{
				pWavPtr = &(pSndTblPtr->wavSnd);

				// free up the filename
				if ( pWavPtr->pSndFileName )
				{
					free ( pWavPtr->pSndFileName );
					pWavPtr->pSndFileName = NULL;
				}
			}

		}

		// decrease the reference count
		--(pSndTblPtr->nRefCount);

		if ( pSndTblPtr->nRefCount == 0 )
		{
			// now clear the other information
			pSndTblPtr->nAudioID  = SND_BAD_SND_ID;
			pSndTblPtr->nSndID	  = SND_BAD_SND_ID;
			pSndTblPtr->bFlags    = SND_CLEAR_FLAG;
#ifdef SND_DEBUG
			TRACE( "SND: slot %d deallocated\n", nSndIdx );
#endif
		}

#ifdef SND_DEBUG
TRACE( "AFTER DELETE:\n" );
pSndTblPtr = pSndTable;
for( nSndIdx=0; nSndIdx<nMaxSnds;++nSndIdx)
{
	if ( pSndTblPtr->nSndID != SND_NULL_SND_ID )
	{
		TRACE( "snd %d: %s A:%ld S:%ld F:0x%x R:%d\n",
			nSndIdx,
			audioIDname(pSndTblPtr->nAudioID),
			pSndTblPtr->nAudioID,
			pSndTblPtr->nSndID,
			pSndTblPtr->bFlags,
			pSndTblPtr->nRefCount);
	}
	++pSndTblPtr;
}
#endif

	}

exit:
	return;
}

///========================================================================
//	Function:		sndDirectSoundCleanup()
//
//	Description:
//			Cleanup the SND processor structures.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void		sndDirectSoundCleanup( void )
{
	BOOL	error;

	// Cleanup the DS object
	if (pDirectSound)
	{
		error = pDirectSound->Release();
		if ( error != DS_OK )
		{
			// report an error
			TRACE("ERROR: failed to release DirectSound Object. (%s) [%s:%d]\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
		}
		else
		{
			// mark the DirectSound pointer as NULL
			pDirectSound = NULL;
		}
	}
}

///========================================================================
//	Function:		sndGetDSobject()
//
//	Description:
//			Retrieve the current DirectSound Object.
//
//	Input:			none
//
//	Ouput:			pDirectSound	pointer to the Direct Sound object
//
///========================================================================

LPDIRECTSOUND		sndGetDSobject( void )
{
	return( pDirectSound );
}

///========================================================================
//	Function:		sndGetFrequency()
//
//	Description:
// 	Get the SND Frequency levels (effect pitch)
//			specifies at which rate the buffer is played
//
//			range: 10,000 <= nFrequency <= 100,000 : 100Hz to 100kHz
//
//			normal rates are 11kHz, 22kHz, 44kHz
//
//	Input:			pDSbuffer	DirectSound sound buffer to effect
//					pFrequency	where to place current base frequency setting
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sndGetFrequency( LPDIRECTSOUNDBUFFER pDSbuffer, LONG* pFrequency )
{
	BOOL	error = TRUE;		// assume failure

	// get this buffer's frequency
	error = pDSbuffer->GetFrequency( (LPDWORD)pFrequency );
	if ( error != DS_OK )
	{
		// report an error
		TRACE("ERROR: Failed to get Frequency.. (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// if we made it here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sndSetFrequency()
//
//	Description:
// 	Set the SND Frequency levels (effect pitch)
//			specifies at which rate the buffer is played
//
//			range: 10,000 <= nFrequency <= 100,000 : 100Hz to 100kHz
//
//			normal rates are 11kHz, 22kHz, 44kHz
//
//	Input:			pDSbuffer	DirectSound sound buffer to effect
//					nFrequency	new base frequency setting
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sndSetFrequency( LPDIRECTSOUNDBUFFER pDSbuffer, LONG nFrequency )
{
	BOOL	error = TRUE;		// assume failure

	// set this buffer's frequency
	error = pDSbuffer->SetFrequency( (DWORD)nFrequency );
	if ( error != DS_OK )
	{
		// report an error
		TRACE("ERROR: Failed to set Frequency.. (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// if we made it here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sndGetVolume()
//
//	Description:
// 	Get the SND Volume levels:
//			Specifies the volume level of the buffer.
//			The initial volume of a buffer is always 0. Any modification in volume
//			levels reflected by values other than 0. Positive values increase volume
//			and negative values decrease volume
//
//			range:  -10,000 <= volumne <= 10,000 : -100db (silent) to 100db
//
//	Input:			pDSbuffer	DirectSound sound buffer to effect
//					pVolume		where to place current base volume setting
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sndGetVolume( LPDIRECTSOUNDBUFFER pDSbuffer, LONG* pVolume )
{
	BOOL	error = TRUE;		// assume failure

	// get this buffer's volume
	error = pDSbuffer->GetVolume( (LPLONG)pVolume );
	if ( error != DS_OK )
	{
		// report an error
		TRACE("ERROR: Failed to get volume. (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// if we made it here we we're successful
	error = FALSE;
exit:
	return( error );
}
 
///========================================================================
//	Function:		sndSetVolume()
//
//	Description:
// 	Set the SND Volume levels:
//			Specifies the volume level of the buffer.
//			The initial volume of a buffer is always 0. Any modification in volume
//			levels reflected by values other than 0. Positive values increase volume
//			and negative values decrease volume
//
//			range:  -10,000 <= volume <= 10,000 : -100db (silent) to 100db
//
//	Input:			pDSbuffer	DirectSound sound buffer to effect
//					nVolume		new base volume setting
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sndSetVolume( LPDIRECTSOUNDBUFFER pDSbuffer, LONG nVolume )
{
	BOOL	error = TRUE;		// assume failure

	// set this buffer's volume
	error = pDSbuffer->SetVolume( (LONG)nVolume );
	if ( error != DS_OK )
	{
		// report an error
		TRACE("ERROR: Failed to set volume. (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// if we made it here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sndGetPan()
//
//	Description:
// 	Get the SND Pan levels
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
//	Input:			pDSbuffer	DirectSound sound buffer to effect
//					pPan		where to place current Pan setting
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sndGetPan( LPDIRECTSOUNDBUFFER pDSbuffer, LONG* pPan )
{
	BOOL	error = TRUE;		// assume failure

	// get this buffer's pan value
	error = pDSbuffer->GetPan( (LPLONG)pPan );
	if ( error != DS_OK )
	{
		// report an error
		TRACE("ERROR: Failed to get pan. (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// if we made it here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sndSetPan()
//
//	Description:
// 	Set the SND Pan levels
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
//	Input:			pDSbuffer	DirectSound sound buffer to effect
//					nPan		new base volume setting
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sndSetPan( LPDIRECTSOUNDBUFFER pDSbuffer, LONG nPan )
{
	BOOL	error = TRUE;		// assume failure

	// set this buffer's pan value
	error = pDSbuffer->SetPan( (LONG)nPan );
	if ( error != DS_OK )
	{
		// report an error
		TRACE("ERROR: Failed to set pan. (%s) [%s:%d]\n", 
			DSErrorToString(error), __FILE__, __LINE__ );
		goto exit;
	}

	// if we made it here we we're successful
	error = FALSE;

exit:
	return( error );
}

///========================================================================
//	Function:		sndStop()
//
//	Description:
// 		Stop a sound being played
//
//	Input:			pDSbuffer	DirectSound sound buffer to effect
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sndStop( LPDIRECTSOUNDBUFFER pDSbuffer )
{
	BOOL	error = TRUE;		// assume failure

#ifdef SNDCHK
	TRACE("sndStop( )\n" ); 
#endif

	// stop the sound
	if (pDSbuffer)
	{
		error = pDSbuffer->Stop();
		if ( error != DS_OK )
		{
			// report an error
			TRACE("ERROR: Failed to stop sound. (%s) [%s:%d]\n", 
				DSErrorToString(error), __FILE__, __LINE__ );
		}

		// if we made it here we we're successful
		error = FALSE;
	}
	else
		TRACE("ERROR: NULL DSBuffer in sndStop. [%s:%d]\n", 
				__FILE__, __LINE__ );

	return( error );
}

///========================================================================
//	Function:		sndFindWave()
//
//	Description:
//		Find the "WAVE" chunk. This reads to the end of the "WAVE" header
//
//	Input:			pSndFile		File to scan through
//					nSndStart		Starting offset into file for sound
//
//	Ouput:			filePos			current position in file, end of WAVE chunk.
//									SND_BAD_FILE_POS if error.
//
///========================================================================

ULONG		sndFindWave( FILE* pSndFile )
{
	SND_CHUNK_HEADER	sndChunkHeader;
	ULONG				filePos;
	BOOL				found;
	BOOL				error = TRUE;		// assume a failure

	// set the filePos to anreasonable value to denote an error
	filePos = SND_BAD_FILE_POS;

	// reset to the beginning of the file
	if ( fseek( pSndFile, 0, SEEK_SET) )
	{
		// report an error
		TRACE("ERROR: fseek failure. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// get the "RIFF" chunk
	found = FALSE;
	while ( !found && !feof( pSndFile ) )
	{
		if ( fread( (void*)&sndChunkHeader, sizeof(SND_CHUNK_HEADER), 1, pSndFile) != 1)
		{
			// report an error
			TRACE("ERROR: failed to read \"RIFF\" chunk header. [%s:%d]\n", 
				  __FILE__, __LINE__ );
			goto exit;
		}

		// make sure this is a "RIFF" chunk
		if (strncmp( "RIFF", sndChunkHeader.chunkID, 4 ) == 0 )
			found = TRUE;

		// now seek pass the data in this chunk
		if ( fseek( pSndFile, sndChunkHeader.chunkSize, SEEK_CUR) )
		{
			// report an error
			TRACE("ERROR: fseek failure (%ld). [%s:%d]\n", 
				  sndChunkHeader.chunkSize, __FILE__, __LINE__ );
			goto exit;
		}
	}

	// did we find the RIFF chunk
	if (!found )
	{
		// report an error
		TRACE("ERROR: failed to locate RIFF. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// now locate get the "WAVE" chunk
	found = FALSE;
	while ( !found && !feof( pSndFile ) )
	{
		if ( fread( (void*)&sndChunkHeader, sizeof(SND_CHUNK_HEADER), 1, pSndFile) != 1)
		{
			// report an error
			TRACE("ERROR: failed to read \"WAVE\" chunk header. [%s:%d]\n", 
				  __FILE__, __LINE__ );
			goto exit;
		}

		// make sure this is a "WAVE" chunk
		if (strncmp( "WAVE", sndChunkHeader.chunkID, 4 ) == 0 )
			found = TRUE;

		// now seek pass the data in this chunk
		if ( fseek( pSndFile, sndChunkHeader.chunkSize, SEEK_CUR) )
		{
			// report an error
			TRACE("ERROR: fseek failure (%ld). [%s:%d]\n", 
				  sndChunkHeader.chunkSize, __FILE__, __LINE__ );
			goto exit;
		}
	}

	// did we find the "WAVE" chunk
	if (!found )
	{
		// report an error
		TRACE("ERROR: failed to locate \"WAVE\" chunk. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// get the current file position
	filePos = ftell( pSndFile );

	error = FALSE;

exit:
	return( error );
}

///========================================================================
//	Function:		sndFindWaveformatex()
//
//	Description:
//		Retrieve the WAVEFORMATEX information
//
//	Input:			pSndFile		File to scan through
//					nSndStart		Starting offset into file for sound
//					pWaveformatex	WAVEFORMATEX data buffer to be filled
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL		sndFindWaveformatex( FILE* pSndFile, ULONG nSndStart, WAVEFORMATEX* pWaveformatex )
{
	SND_CHUNK_HEADER	sndChunkHeader;
	BOOL				found;
	BOOL				error = TRUE;		// assume a failure

	// now seek to this offset
	if ( fseek( pSndFile, nSndStart, SEEK_SET) )
	{
		// report an error
		TRACE("ERROR: fseek failure (%ld). [%s:%d]\n", 
			  nSndStart, __FILE__, __LINE__ );
		goto exit;
	}

	// get the "fmt " chunk
	found = FALSE;
	while ( !found && !feof( pSndFile ) )
	{
		if ( fread( (void*)&sndChunkHeader, sizeof(SND_CHUNK_HEADER), 1, pSndFile) != 1)
		{
			// report an error
			TRACE("ERROR: failed to read \"fmt \" chunk header (%ld). [%s:%d]\n", 
				  nSndStart, __FILE__, __LINE__ );
			goto exit;
		}

		// make sure this is a "fmt " chunk
		if (strncmp( "fmt ", sndChunkHeader.chunkID, 4 ) == 0 )
			found = TRUE;
		else
		{
			// now seek pass the data in this chunk
			if ( fseek( pSndFile, sndChunkHeader.chunkSize, SEEK_CUR) )
			{
				// report an error
				TRACE("ERROR: fseek failure (%ld). [%s:%d]\n", 
					  sndChunkHeader.chunkSize, __FILE__, __LINE__ );
				goto exit;
			}
		}
	}

	// did we find the WAVEFORMATEX chunk
	if (!found )
	{
		// report an error
		TRACE("ERROR: failed to locate WAVEFORMATEX. [%s:%d]\n\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// note: some wave files don't include the cbSize data so clear the waveformatex
	// structure and read in only the chunk size number of bytes.
	memset( pWaveformatex, 0, sizeof(WAVEFORMATEX));
	if ( fread( (void*)pWaveformatex, sndChunkHeader.chunkSize, 1, pSndFile) != 1)
	{
		// report an error
		TRACE("ERROR: WAVEFORMATEX access failure. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// if we made it here we we're successful
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		sndFindSample()
//
//	Description:
//		Locate the raw smaple data information. The file pointer will be
//		advanced to the beginning of the "WAVE" raw data. If an offset is
//		specified, the file pointer will advance that far into the data.
//
//	Input:			pSndFile		File to scan through
//					nSndStart	Starting offset into file for sound
//					nOffset		offset into the raw to advance the file pointer
//					nSize		size of the sample data retrieved.
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//					pSndFile	pointing to the specified raw data
//
///========================================================================

BOOL		sndFindSample( FILE* pSndFile, ULONG nSndStart, ULONG nOffset, ULONG* nSize )
{
	// now seek to this offset
	SND_CHUNK_HEADER	sndChunkHeader;
	BOOL				found;
	BOOL				error = TRUE;		// assume a failure

	// make sure this sound file is active
	if ( pSndFile == NULL )
		goto exit;

	// now seek to this offset
	if ( fseek( pSndFile, nSndStart, SEEK_SET) )
	{
		// report an error
		TRACE("ERROR: fseek failure (%ld). [%s:%d]\n", 
			  nSndStart, __FILE__, __LINE__ );
		goto exit;
	}

	// get the "data" chunk
	found = FALSE;
	while ( !found && !feof( pSndFile ) )
	{
		if ( fread( (void*)&sndChunkHeader, sizeof(SND_CHUNK_HEADER), 1, pSndFile) != 1)
		{
			// report an error
			TRACE("ERROR: failed to read \"data\" chunk header. [%s:%d]\n", 
				  __FILE__, __LINE__ );
			goto exit;
		}

		// make sure this is a "data" chunk
		if (strncmp( "data", sndChunkHeader.chunkID, 4 ) == 0 )
			found = TRUE;
		else
		{
			// now seek pass the data in this chunk
			if ( fseek( pSndFile, sndChunkHeader.chunkSize, SEEK_CUR) )
			{
				// report an error
				TRACE("ERROR: fseek failure (%ld). [%s:%d]\n", 
					  sndChunkHeader.chunkSize, __FILE__, __LINE__ );
				goto exit;
			}
		}
	}

	// did we find the raw sample data chunk
	if (!found )
	{
		// report an error
		TRACE("ERROR: failed to locate raw sampled data. [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit;
	}

	// report back to the caller the data size
	*nSize = sndChunkHeader.chunkSize;

	// if we made it here we we're successful
	error = FALSE;
exit:
	return( error );

}

///========================================================================
//	Function:		sndFindSndID()
//
//	Description:
//		Locate a SND id in the SND lookup table
//
//	Input:			nSndID			sound Id number to apply pan to
//					pSndPtr			where to place the address of the request
//									snd to locate.
//
//	Ouput:			status			SND_BAD_STATUS if failure,
//									SND_NEW_STATUS if a new snd
//									SND_ACTIVE_STATUS if snd already processed			
//					pSndPtr		    address of SND being requested.
//									SND_NULL_SND_PTR if failed
//
///========================================================================

unsigned sndFindSndID ( ULONG nSndID, SND** pSndPtr, int* nSndIdx )
{
	unsigned	snd;
	unsigned	status = SND_BAD_STATUS;

	if (nSndID == SND_NULL_SND_ID)
		return status;

	// find the sound in the table
	*pSndPtr = pSndTable;
	if ( *pSndPtr  && (*pSndPtr != (SND*)SND_NULL_SND_PTR) ) 
	{
		snd = 0;
		while ( (snd<nMaxSnds) && ((*pSndPtr)->nSndID != nSndID) )
		{
			++snd;
			++(*pSndPtr);
		}
   
		// did we find it ?
		if ( snd == nMaxSnds )
			*pSndPtr = (SND*)SND_NULL_SND_PTR;
		else
		if ( (*pSndPtr)->nSndID == nSndID )
			status = SND_ACTIVE_STATUS;
		else
			status = SND_NEW_STATUS;

		*nSndIdx = snd;
	}
	else
		*pSndPtr = (SND*)SND_NULL_SND_PTR;

	return( status );    
}


///========================================================================
//	Function:		sndExist()
//
//	Description:
//		Does a SND id exist in the SND lookup table
//
//	Input:			nSndID			sound Id number
//
///========================================================================

BOOL sndExist ( ULONG nSndID )
{
	SND snd;
	SND *pSnd = &snd;
	int nSndIdx;

	if (sndFindSndID ( nSndID, &pSnd, &nSndIdx ) != SND_ACTIVE_STATUS)
		return FALSE;

	return TRUE;
}

///========================================================================
//	Function:		sndFindAudioID()
//
//	Description:
//		Locate a AUDIO id in the SND lookup table
//
//	Input:			nAudioID		Audio Id number to search for
//					pSndPtr			where to place the address of the request
//									snd to locate.
//
//	Ouput:			status			SND_BAD_STATUS if not present,
//									SND_NEW_STATUS if a new snd
//									SND_ACTIVE_STATUS if snd already processed			
//					pSndPtr		    address of SND being requested.
//									SND_NULL_SND_PTR if failed
//
///========================================================================

unsigned sndFindAudioID ( ULONG nAudioID, SND** pSndPtr )
{
	SND*		pAudioPtr;
	unsigned	snd;
	unsigned	status = SND_BAD_STATUS;

	// find the sound in the table
	pAudioPtr = pSndTable;
	if ( pAudioPtr ) 
	{
		snd = 0;
		while ( (snd<nMaxSnds) && (pAudioPtr->nAudioID != nAudioID) )
		{
			++snd;
			++pAudioPtr;
		}
   
		// did we find it ?
		if ( snd == nMaxSnds )
			*pSndPtr = (SND*)SND_NULL_SND_PTR;
		else
		if ( pAudioPtr->nAudioID == nAudioID )
		{
			status   = SND_ACTIVE_STATUS;
			*pSndPtr = pAudioPtr;
		}
		else
		{
			status   = SND_NEW_STATUS;
			*pSndPtr = pAudioPtr;
		}
	}
	else
		*pSndPtr = (SND*)SND_NULL_SND_PTR;

	return( status );    
}

///========================================================================
//	Function:		sndFindSlot()
//
//	Description:
//		Locate a SND slot in the SND lookup table
//
//	Input:			none
//
//	Ouput:			pSndPtr		    address of SND being requested.
//									SND_NULL_SND_PTR if failed
//
///========================================================================

SND* sndFindSlot( ULONG* pSndID )
{
	ULONG	nSndID;
	SND*	pSndPtr = (SND*)SND_NULL_SND_PTR;

	// see if the sound table is full
	if ( nLoadedSounds >= nMaxSnds )
	{
		*pSndID = SND_NULL_SND_ID;
		goto exit;
	}

	// now locate an empty sound slot
	pSndPtr = pSndTable;
	nSndID  = 0;
	while ( (nSndID<nMaxSnds) && (pSndPtr->nSndID != SND_NULL_SND_ID) )
	{
		++pSndPtr;
		++nSndID;
	}
	// did we find an empty slot?  
	if ( nSndID >= nMaxSnds )
	{
		pSndPtr = (SND*)SND_NULL_SND_PTR;
		*pSndID = SND_NULL_SND_ID;
		goto exit;
	}
#ifdef SND_DEBUG
	TRACE( "SND: slot %d allocated\n", nSndID );
#endif

	// if we're here we found the slot
	*pSndID = nSndID;

exit:
	return( pSndPtr );
}

///========================================================================
//	Function:		sndSaveFile()
//
//	Description:
//		Save the SND fileptr and filename for an OPEN snd file.
//		Used during loading a sound.
//
//	Input:			pSndFile		SND file that name is associated
//					pSndFileName	Actual filename
//
//	Ouput:			nFileID			file id assigned
//
///========================================================================

unsigned	sndSaveFile( FILE* pSndFile, char* pSndFileName )
{
	SND_FILES*	pSndFilePtr;
	unsigned	snd;
	unsigned	len;
	unsigned	nFileID = SND_NULL_SND_ID;

	// scan the table to see if this file already exits
	pSndFilePtr = pSndFiles;
	snd         = 0;
	while( (pSndFilePtr->pSndFile != pSndFile) && (snd<nMaxSndFiles) )
	{
		++pSndFilePtr;
		++snd;
	}

	// did the file actually already exist
	if (snd<nMaxSndFiles) 
	{
		// compare the file names to check for conflict
		if ( pSndFilePtr->pSndFileName != NULL )
		{
			if ( strcmp( pSndFileName, pSndFilePtr->pSndFileName ) != 0 )
			{
				// report an error
				TRACE("ERROR: SND file name conflict \"%s\" vs. \"%s\". [%s:%d]\n", 
					  pSndFilePtr->pSndFileName, pSndFileName, __FILE__, __LINE__ );
				goto exit;
			}
			else
			{
				// return the existing file ID
				nFileID = pSndFilePtr->nSndFileID;
				goto exit;
			}
		}
	}

	// find an available slot
	pSndFilePtr = pSndFiles;
	snd         = 0;
	while( (pSndFilePtr->pSndFile != NULL) && (snd<nMaxSndFiles) )
	{
		++pSndFilePtr;
		++snd;
	}

	// did we find a slot
	if (snd<nMaxSndFiles) 
	{

		// save the file pointer address
		pSndFilePtr->pSndFile = pSndFile;

		//allocate a buffer for this name and store it here
		len = strlen( pSndFileName );

		// copy in the .SND header information
		pSndFilePtr->pSndFileName = (char*)malloc( len+1 );
		if ( pSndFilePtr->pSndFileName == NULL )
		{
			// report an error
			TRACE("ERROR: Insufficient memory available. [%s:%d]\n\n", 
				  __FILE__, __LINE__ );
			goto exit;
		}
#ifdef MALLOC_DEBUG
		TRACE( "malloc (%ld): SND resource filename [%s : %d]\n", ( len+1 ), __FILE__, __LINE__ );
#endif

		// now copy in the filename
		strcpy( pSndFilePtr->pSndFileName, pSndFileName );
		*(pSndFilePtr->pSndFileName + len) = '\0';

		// now assign the snd file id
		nFileID                 = nSndFileID;
		pSndFilePtr->nSndFileID = nFileID;

		// update the file id
		++nSndFileID;
	}
	else
	{
		// report an error
		TRACE("ERROR: too many files open... [%s:%d]\n", 
			  __FILE__, __LINE__ );
	}

exit:
	return (nFileID);

}

///========================================================================
//	Function:		sndGetFile()
//
//	Description:
//		Retreive the STRM fileptr associated with a file pointer
//
//	Input:			nFileID			.snd or .wav file id
//
//	Ouput:			pSndFile		pointer to .snd or .wav file pointer
//
///========================================================================

FILE*	sndGetFile( unsigned nFileID )
{
	SND_FILES*	pSndFilePtr;
	unsigned	snd;
	FILE*		pSndFile = NULL;

	if ( !SNDenabled )
		return( pSndFile );

	// scan the table to see if this file exits
	pSndFilePtr = pSndFiles;
	snd = 0;
	while( (pSndFilePtr->nSndFileID != nFileID) && (snd<nMaxSndFiles) )
	{
		++pSndFilePtr;
		++snd;
	}

	// did the sound actually already exist
	if (snd<nMaxSndFiles) 
		pSndFile = pSndFilePtr->pSndFile;

	return( pSndFile );
}

///========================================================================
//	Function:		sndGetFileName()
//
//	Description:
//		Retreive the STRM filename associated with a file pointer
//
//	Input:			nFileID			.snd or .wav file id
//
//	Ouput:			pSndFileName	pointer to .snd or .wav filename
//
///========================================================================

char*	sndGetFileName ( unsigned nFileID )
{
	SND_FILES*	pSndFilePtr;
	unsigned	snd;
	char*		pSndFileName = NULL;

	if ( !SNDenabled )
		return( pSndFileName );

	// scan the table to see if this file exits
	pSndFilePtr = pSndFiles;
	snd = 0;
	while( (pSndFilePtr->nSndFileID != nFileID) && (snd<nMaxSndFiles) )
	{
		++pSndFilePtr;
		++snd;
	}

	// did the sound actually already exist
	if (snd<nMaxSndFiles) 
		pSndFileName = pSndFilePtr->pSndFileName;

	return( pSndFileName );
}

///========================================================================
//	Function:		sndDeleteFile()
//
//	Description:
//		Delete the SND filename and close the file pointer associated with a file id
//
//	Input:			nFileID		.snd or .wav file ID
//
//	Ouput:			none
//
///========================================================================

void	sndDeleteFile ( unsigned nFileID )
{
	SND_FILES*	pSndFilePtr;
	unsigned	snd;

	if ( !SNDenabled )
		return;

	// make sure we haven't already cleaned up the file list
	if ( pSndFiles != (SND_FILES*)SND_NULL_SND_PTR )
	{
		// scan the table to see if this file exits
		pSndFilePtr = pSndFiles;
		snd = 0;
		while( (pSndFilePtr->nSndFileID != nFileID) && (snd<nMaxSndFiles) )
		{
			++pSndFilePtr;
			++snd;
		}

		// did the sound file actually exist
		if (snd<nMaxSndFiles)
		{
			// clear the file reference then free the filename
			if ( pSndFilePtr->pSndFile )
			{
				fclose( pSndFilePtr->pSndFile );
				pSndFilePtr->pSndFile = NULL;
			}
			if ( pSndFilePtr->pSndFileName )
			{
				free( pSndFilePtr->pSndFileName );
				pSndFilePtr->pSndFileName = NULL;
#ifdef MALLOC_DEBUG
				TRACE( "free: SND filename [%s : %d]\n", __FILE__, __LINE__ );
#endif
			}
		}
	}
}

///========================================================================
//								EOF
///========================================================================
