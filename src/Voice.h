//========================================================================
//	FILE:			$Workfile: Voice.h $
//
//	DESCRIPTION:	Audio Voice Stream processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Saturday, November 15, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Voice.h 16    4/01/98 4:46p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Voice.h $
//  
//  16    4/01/98 4:46p Nrobinso
//  
//  15    3/02/98 10:32a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  14    1/21/98 2:03p Nrobinso
//  modification to stream updates for non queued items
//  
//  13    1/21/98 9:22a Aburgess
//  modifications made to shorten the STRM and VOICE monitor interrupts.
//  Also merged the audio ON/OFF switching. In addition, all audio is now
//  turned off during mission load as that routine has a large frame
//  overrun problem disallowing updates to audio.
//  
//  12    1/05/98 10:32a Aburgess
//  latest attempt to resolve Streaming bug. Voice is now handled in a
//  seperate handler.
//  
//  11    12/23/97 6:26p Nrobinso
//  use audio variables for on/off
//  
//  10    12/22/97 11:35a Aburgess
//  added Snd prototype equivalents
//  
//  9     12/19/97 1:52p Aburgess
//  clarification of nSndID usage
//  
//  8     12/15/97 9:04a Aburgess
//  conversion to limit # of voice and music streams playing
//  
//  7     12/09/97 12:59p Aburgess
//  added voiceFreeText prototype
//  
//  6     12/09/97 12:12p Phu
//  
//  5     12/04/97 9:14a Aburgess
//  Modifications made to properly handle delete race condition with
//  strmMonitor. Actual sound allocation tracking added to help minimize
//  static tables for audio
//  
//  4     12/02/97 10:21a Aburgess
//  locking mechanism added for deletes (load?)
//  
//  3     11/20/97 3:32p Aburgess
//  modifications made to allow app to run regardless of existence of .ASD,
//  .AST files or DirectSound itself
//  
//  2     11/17/97 10:11a Aburgess
//  rework of audio/voice/strm interfaces. Additional voice-overs
//  
//  1     11/16/97 12:45p Aburgess
//  voice audio/text process
//  
//  $Nokeywords:$
///========================================================================

#ifndef __VOICE_H__
#define __VOICE_H__

///========================================================================
//							GLOBAL DEFINES
///========================================================================

#define	VOICE_MAX_IDS			256
#define	VOICE_MAX_TEXT_LEN		256

#define	VOICE_MAX_QUEUE_ENTRIES	1

#define	VOICE_START_ID			800
#define	VOICE_AUDIO_START		5000

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================

// AUDIO VOICE data
// This structure keeps all the data that the TimeFunc callback uses in one
// place.  In this implementation, elements of the structure are allocated
// from the local heap via MALLOC. Additionally, this is setup so that if
// we wanted to put our callback in a DLL, all we'd need to do is pass the
// address of this structure as a parameter.

typedef struct
{
	ULONG				nAudioID;			// audio identifier
	ULONG				nSndID;				// sound identifier
	USHORT				bFlags;				// Flag fields (see SND.H)
	LONG				nVolume;			// initial volume setting
	ULONG				nVoiceID;			// VOICE identifier
	BOOL				bLock;				// locking mechanism
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
	ULONG				nSndLink;			// Link to another voice ID
} VOICE_SND;

// voice audio to string lookup table definition
typedef struct
{
	ULONG				nVoiceID;			// voice audio ID
	char*				pVoiceText;			// pointer to the text string corresponding
											// to the above voice ID
} VOICE_TEXT;

//=========================================================================
//		GLOBAL data
//=========================================================================
extern	BOOL			VOICEenabled;
extern	BOOL			VOICETEXTenabled;

///========================================================================
//	DESCRIPTION:	Stream Audio processing. These usually refer to long
//					sounds, typically being read from file or CD-ROM.
///========================================================================

BOOL		voiceInit ( unsigned nMaxSounds );
void		voiceExit ( void );
unsigned	voiceOpen ( char* pFilename );
unsigned	voiceMaxSounds ( void );
ULONG		voiceLoad ( unsigned nFileID, ULONG nVoiceID, unsigned nIndexToLoad,
					   USHORT bFlags );
ULONG		voiceLoadRes( unsigned nResId );
ULONG		voiceLoadWav( char* pWaveFilename );
BOOL		voiceCue ( ULONG nAudioID );
BOOL		voiceCueSnd ( ULONG nSndID );
BOOL		voicePlay ( ULONG nAudioID );
BOOL		voicePlaySnd ( ULONG nSndID );
BOOL		voiceFade ( ULONG nAudioID, unsigned nInOrOut );
BOOL		voiceFadeSnd ( ULONG nSndID, unsigned nInOrOut );
BOOL		voiceStop ( ULONG nAudioID );
BOOL		voiceStopSnd( ULONG nSndID );
BOOL		voiceReset ( ULONG nVoiceID );
void		voiceClose ( unsigned nFileID );
BOOL		voiceDelete ( ULONG nAudioID );
BOOL		voiceDeleteSnd ( ULONG nSndID );
LONG		voiceGetFrequency ( ULONG nVoiceID );
BOOL		voiceSetFrequency ( ULONG nVoiceID, LONG nFrequency );
LONG		voiceGetVolume ( ULONG nSndID ); 
BOOL		voiceSetVolume ( ULONG nSndID, LONG nVolume );
LONG		voiceGetPan ( ULONG nVoiceID );
BOOL		voiceSetPan ( ULONG nVoiceID, LONG nPan );

#ifdef AUDIO_TIMER
void CALLBACK voiceMonitor ( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 );
#else
void		voiceMonitor ( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 );
#endif
void		voiceUpdate ( VOICE_SND* pVoiceTblPtr );

BOOL		voiceTimerCheck ( UINT uTimerID );
BOOL		voiceSetLink( unsigned nLink, unsigned nNextLink );
ULONG		voiceNextLink( ULONG nVoiceId );

void		voiceSetMasterVoiceVolume( LONG nVolume );
LONG		voiceGetMasterVoiceVolume( void );
void		voiceSetMasterMusicVolume( LONG nVolume );
LONG		voiceGetMasterMusicVolume( void );

BOOL		voiceLoadNextData( VOICE_SND* pVoiceTblPtr, BYTE* pDSBuffData, DWORD maxLen, DWORD nPlayPos );
VOICE_SND*	voiceFindTimerID( UINT uTimerID );

VOICE_SND*	voiceFindID( ULONG nVoiceID );
VOICE_SND*	voiceFindSndID( ULONG nSndID );

char*		voiceFindText ( ULONG nVoiceID );
void		voiceFreeText ( void );

extern	void	voiceDeleteStream( unsigned nSndID );
extern	ULONG	voiceCreateStream( unsigned AUDIOstreamID, ULONG nAudioID,
								   unsigned nIndexToLoad,  USHORT bFlags );
extern	void	voiceCleanUpStreams( ULONG nSndID );
extern	void	voiceTableCleanUp( void );
extern	USHORT	voiceFlags( ULONG nSndID );

extern	void	voiceSetOn(BOOL on);
extern	BOOL	voiceGetOn(void);
extern	void	voiceToggleOn(void);

#endif __VOICE_H__

//=========================================================================
//								EOF
//=========================================================================

