//========================================================================
//	FILE:			$Workfile: SFX.H $
//
//	DESCRIPTION:	Audio Special Effects (SFX) processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Saturday, May 18, 1996
//
//	REVISION:		$Header: /ArmyMen/src/SFX.H 13    3/02/98 10:31a Aburgess $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/SFX.H $
//  
//  13    3/02/98 10:31a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  12    2/25/98 2:53p Aburgess
//  modifications to improve AUDIO options interface. Still needs work.
//  
//  11    2/20/98 12:00p Aburgess
//  modifications to support clean up and deletion of SFX sounds
//  
//  10    1/21/98 9:22a Aburgess
//  modifications made to shorten the STRM and VOICE monitor interrupts.
//  Also merged the audio ON/OFF switching. In addition, all audio is now
//  turned off during mission load as that routine has a large frame
//  overrun problem disallowing updates to audio.
//  
//  9     12/19/97 1:51p Aburgess
//  clarification of nSndID usage
//  
//  8     12/09/97 12:12p Phu
//  
//  7     12/04/97 9:14a Aburgess
//  Modifications made to properly handle delete race condition with
//  strmMonitor. Actual sound allocation tracking added to help minimize
//  static tables for audio
//  
//  6     12/02/97 10:21a Aburgess
//  locking mechanism added for deletes (load?)
//  
//  5     11/20/97 3:32p Aburgess
//  modifications made to allow app to run regardless of existence of .ASD,
//  .AST files or DirectSound itself
//  
//  4     11/17/97 10:08a Aburgess
//  rework of audio/sfx/strm/voice/snd interface
//  
//  2     9/02/97 9:41a Aburgess
//  added SFX master volume control prototypes
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  5     10/02/96 11:31a Aburgess
//  sfxReset prototype added
//  
//  2     6/26/96 11:24a Aburgess
//  added new Source Control headers
// 
//  $Nokeywords:$
///========================================================================

#ifndef __SFX_H__
#define __SFX_H__


///========================================================================
//							GLOCAL DEFINES
///========================================================================

// NULL sound ID value
#define	SFX_NULL_SND_ID		(ULONG)~0
#define	SFX_NULL_SND_PTR	(ULONG)~0

#define	SFX_START_ID		80000
#define	SFX_AUDIO_START		1000

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================

// AUDIO SFX data
// This structure keeps all the data that DirectSound needs to use in one
// place.  In this implementation, elements of the structure are allocated
// from the local heap via MALLOC.  

typedef struct
{
	ULONG				nAudioID;			// audio identifier
	ULONG				nSndID;				// sound identifier
	USHORT				bFlags;				// Flag fields (see SND.H)
	ULONG				nVolume;			// SFX identifier
	BOOL				bLock;				// locking mechanism
	ULONG				nSfxID;				// SFX identifier
	LPDIRECTSOUNDBUFFER pDSBuffer;			// Direct Sound Buffer
	BYTE*				pSndData;			// play buffer
	ULONG				nImageLen;			// length of sound data
	ULONG				nPlayBufferLen;		// length of play buffer
} SFX_SND;

//=========================================================================
//		GLOBAL data
//=========================================================================
extern	BOOL			SFXenabled;
extern	unsigned		SFXactualMaxSounds;

//=========================================================================
//	DESCRIPTION:	Special Effects Audio processing. These usually refer
//					to short, static, often used sounds.
//=========================================================================
BOOL		sfxInit ( unsigned nMaxSounds );
void		sfxExit ( void );
unsigned	sfxOpen ( char* pFilename );
unsigned	sfxMaxSounds ( void );
ULONG		sfxLoad ( unsigned nFileID, ULONG nSfxID, unsigned nIndexToLoad,
					  USHORT bFlags );
ULONG		sfxLoadRes ( unsigned nResId );
ULONG		sfxLoadWav ( char* pWaveFilename );
BOOL		sfxPlay ( ULONG nAudioID );
BOOL		sfxPlaySnd ( ULONG nSndID );
BOOL		sfxPlaySfx ( ULONG nSfxID );
BOOL		sfxFade ( ULONG nAudioID, unsigned nInOrOut );
BOOL		sfxStop ( ULONG nAudioID );
BOOL		sfxStopSnd( ULONG nSndID );
BOOL		sfxReset ( ULONG nAudioID );
void		sfxCleanUp( ULONG nSndID );
void		sfxTableCleanUp( void );
void		sfxClose ( unsigned nFileID );
BOOL		sfxDelete ( ULONG nSfxID );
BOOL		sfxDeleteSnd ( ULONG nSndID );
BOOL		sfxDeleteSfx( ULONG nSfxID );
LONG		sfxGetFrequency ( ULONG nSfxID );
BOOL		sfxSetFrequency ( ULONG nSfxID, LONG nFrequency );
LONG		sfxGetVolume ( ULONG nSndID ); 
BOOL		sfxSetVolume ( ULONG nSndID, LONG nVolume );
LONG		sfxGetPan ( ULONG nSfxID );
BOOL		sfxSetPan ( ULONG nSfxID, LONG nPan );
void		sfxSetOn( BOOL on );
BOOL		sfxGetOn( void );
void		sfxToggleOn( void );
void		sfxSetMasterVolume( LONG nVolume );
LONG		sfxGetMasterVolume( void );

SFX_SND*	sfxFindID( ULONG nAudioID );
SFX_SND*	sfxFindSndID( ULONG nSndID );

#endif // __SFX_H__

//=========================================================================
//								EOF
//=========================================================================

