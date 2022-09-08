//========================================================================
//	FILE:			$Workfile: STRM.H $
//
//	DESCRIPTION:	Audio Stream processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, May 15, 1996
//
//	REVISION:		$Header: /ArmyMen/src/STRM.H 16    3/02/98 10:32a Aburgess $
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
//  $Log: /ArmyMen/src/STRM.H $
//  
//  16    3/02/98 10:32a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  15    1/21/98 2:03p Nrobinso
//  modification to stream updates for non queued items
//  
//  14    1/21/98 9:22a Aburgess
//  modifications made to shorten the STRM and VOICE monitor interrupts.
//  Also merged the audio ON/OFF switching. In addition, all audio is now
//  turned off during mission load as that routine has a large frame
//  overrun problem disallowing updates to audio.
//  
//  13    1/05/98 10:32a Aburgess
//  latest attempt to resolve Streaming bug. Voice is now handled in a
//  seperate handler.
//  
//  12    12/23/97 6:25p Nrobinso
//  use audio variables for on/off
//  
//  11    12/22/97 11:35a Aburgess
//  added Snd prototype equivalents
//  
//  10    12/19/97 1:52p Aburgess
//  clarification of nSndID usage
//  
//  9     12/15/97 9:04a Aburgess
//  conversion to limit # of voice and music streams playing
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
//  2     9/02/97 9:42a Aburgess
//  added STRM master volume control prototypes
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  10    10/02/96 11:31a Aburgess
//  prototypes for strmReset() and strmNextLink() added
//  
//  7     6/28/96 2:25p Aburgess
//  corrected audio streaming code. NOTE: DirectSound smaples from
//  MicroSoft changed with DXII. These changes helped slove the streaming
//  problem.
//  
//  6     6/26/96 11:24a Aburgess
//  added new Source Control headers
// 
//  $Nokeywords:$
///========================================================================

#ifndef __STRM_H__
#define __STRM_H__

///========================================================================
//							GLOBAL DEFINES
///========================================================================

// NULL sound ID value
#define	STRM_NULL_SND_ID		(ULONG)~0
#define	STRM_NULL_SND_PTR		(ULONG)~0
#define	STRM_NULL_TIMER_ID		(UINT)~0

#define	STRM_MAX_QUEUE_ENTRIES	1

#define	STRM_START_ID			500
#define	MUSIC_AUDIO_START		2000

//-------------------------------------------------------------------------
// WARNING -- Be careful about changing STRM_NUM_BUFFER_SEGMENTS -- it
// should be at least 3, or there will probably not be enough time for the
// interrupt to do its thing before the player catches up to it. Also,
// STRM_PLAYBACK_TIMER_PERIOD is set at 200ms because we are oversampling
// by a factor of four (STRM_PLAYBACK_OVERSAMPLE). This is so we can shift
// the frequency on the fly and still keep up with the play cursor. The
// timer routine will only fill when necessary. Experiments have shown that
// the timer still operates well when interrupted every 50ms (and possibly
// even more often than that). If you do not require real-time frequency
// changes, you reduce the STRM_PLAYBACK_OVERSAMPLE value as well as the
// STRM_TIMER_PERIOD. However, note that since a buffer segment is only an
// approximation of the number of bytes played per interrupt, it's a good
// idea to interupt a bit more often than STRM_PLAYBACK_TIMER_PERIOD, just
// to make sure the timer isn't falling behind the player. If your frequency
// is fixed, the call to initialize the timer event could be changed to
// first calculate something like (STRM_PLAYBACK_TIMER_PERIOD * 0.8). This
// should ensure that the buffer is well maintained and system performance
// is maximized.
//-------------------------------------------------------------------------

#define STRM_NUM_BUFFER_SEGMENTS		6
#define STRM_PLAYBACK_TIMER_PERIOD		200
#define STRM_PLAYBACK_OVERSAMPLE		4
#define STRM_PLAYBACK_TIMER_ACCURACY	10
#define STRM_FREQUENCY_MULTIPLIER		100

/* Streaming communication defines and structures */

#define WM_DSSTREAM_DONE        WM_USER + 0x100 /* Make our own app messages */
#define WM_DSSTREAM_DEBUG       WM_USER + 0x101
#define WM_DSSTREAM_PROGRESS    WM_USER + 0x102

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================

// AUDIO STRM data
// This structure keeps all the data that the TimeFunc callback uses in one
// place.  In this implementation, elements of the structure are allocated
// from the local heap via MALLOC. Additionally, this is setup so that if
// we wanted to put our callback in a DLL, all we'd need to do is pass the
// address of this structure as a parameter.

typedef struct
{
	BOOL				bLock;				// locking mechanism
	ULONG				nAudioID;			// audio identifier
	ULONG				nStrmID;			// STREAM identifier
	ULONG				nSndID;				// sound identifier
	USHORT				bFlags;				// Flag fields (see SND.H)
	LPDIRECTSOUNDBUFFER pDSBuffer;			// Direct Sound Buffer
    WAVEFORMATEX*       pWaveForm;          // Wave Format data structure

											// these are filled at load time.
	LONG				nSndStart;			// Start offset into file to reach sound chunk
	LONG				nSndOffset;			// current offset into wave stream
	LONG				nSndSize;			// size of raw stream data

	UINT				uTimerID;			// stream timer ID
    DWORD               dwBufferSize;       // Size of the entire buffer
    DWORD               dwBufferSegSize;    // Size of one buffer segment
    DWORD               dwNextWriteOffset;  // Offset to next buffer segment
    DWORD               dwPlayLast;         // Position of last play cursor
    DWORD               dwProgress;         // Used with above to show prog
    DWORD               nRemainingBytes;	// Bytes 'til timer shutdown
	ULONG				nSndLink;			// Link to another strm ID
} STRM_SND;

//=========================================================================
//		GLOBAL data
//=========================================================================
extern	BOOL			STRMenabled;

///========================================================================
//	DESCRIPTION:	Stream Audio processing. These usually refer to long
//					sounds, typically being read from file or CD-ROM.
///========================================================================

BOOL		strmInit ( unsigned nMaxSoundstrmvoices );
void		strmExit ( void );
unsigned	strmOpen ( char* pFilename );
unsigned	strmMaxSounds ( void );
ULONG		strmLoad ( unsigned nFileID, ULONG nAudioID, unsigned nIndexToLoad,
					   USHORT bFlags );
ULONG		strmLoadRes( unsigned nResId );
ULONG		strmLoadWav( char* pWaveFilename );
BOOL		strmCue ( ULONG nAudioID );
BOOL		strmCueSnd ( ULONG nSndID );
BOOL		strmPlay ( ULONG nAudioID );
BOOL		strmPlaySnd ( ULONG nSndID );
BOOL		strmFade ( ULONG nAudioID, unsigned nInOrOut );
BOOL		strmFadeSnd ( ULONG nSndID, unsigned nInOrOut );
BOOL		strmStop ( ULONG nAudioID );
BOOL		strmStopSnd( ULONG nSndID );
BOOL		strmReset ( ULONG nAudioID );
void		strmClose ( unsigned nFileID );
BOOL		strmDelete ( ULONG nStrmID );
BOOL		strmDeleteSnd ( ULONG nSndID );
LONG		strmGetFrequency ( ULONG nStrmID );
BOOL		strmSetFrequency ( ULONG nStrmID, LONG nFrequency );
LONG		strmGetVolume ( ULONG nSndID ); 
BOOL		strmSetVolume ( ULONG nSndID, LONG nVolume );
LONG		strmGetPan ( ULONG nStrmID );
BOOL		strmSetPan ( ULONG nStrmID, LONG nPan );

#ifdef AUDIO_TIMER
void CALLBACK strmMonitor ( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 );
#else
void		strmMonitor ( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 );
#endif

extern	STRM_SND*	strmFindID ( ULONG nAudioID );
extern	STRM_SND*	strmFindSndID ( ULONG nSndID );

extern	void		strmUpdate ( STRM_SND* pStrmTblPtr );
extern	BOOL		strmTimerCheck ( UINT uTimerID );
extern	BOOL		strmSetLink( unsigned nLink, unsigned nNextLink );
extern	ULONG		strmNextLink( ULONG nStrmId );

extern	void		strmSetMasterVoiceVolume( LONG nVolume );
extern	LONG		strmGetMasterVoiceVolume( void );
extern	void		strmSetMasterMusicVolume( LONG nVolume );
extern	LONG		strmGetMasterMusicVolume( void );

extern	void	strmDeleteStream( ULONG nSndID );
extern	ULONG	strmCreateStream( unsigned AUDIOstreamID, ULONG nAudioID,
								  unsigned nIndexToLoad,  USHORT bFlags );
extern	void	strmCleanUpStreams( ULONG nSndID );
extern	void	strmTableCleanUp( void );
extern	USHORT	strmFlags( ULONG nSndID );

extern	void	strmSetOn(BOOL on);
extern	BOOL	strmGetOn(void);
extern	void	strmToggleOn(void);

#endif __STRM_H__

//=========================================================================
//								EOF
//=========================================================================

