//========================================================================
//	FILE:			$Workfile: SND.H $
//
//	DESCRIPTION:	SND processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Monday, May 06, 1996
//
//	REVISION:		$Header: /ArmyMen/src/SND.H 11    3/02/98 10:31a Aburgess $
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
//  $Log: /ArmyMen/src/SND.H $
//  
//  11    3/02/98 10:31a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  10    2/24/98 10:52a Aburgess
//  made SND_VOICE_FLAG and SND_MUSIC_FLAG unique flags
//  
//  9     1/12/98 10:43a Aburgess
//  changes made to support Smacker DSound useage
//  
//  8     1/05/98 10:32a Aburgess
//  latest attempt to resolve Streaming bug. Voice is now handled in a
//  seperate handler.
//  
//  7     12/09/97 12:12p Phu
//  
//  6     11/20/97 3:32p Aburgess
//  modifications made to allow app to run regardless of existence of .ASD,
//  .AST files or DirectSound itself
//  
//  5     11/17/97 10:08a Aburgess
//  rework of audio/sfx/strm/voice/snd interface
//  
//  3     9/12/97 9:50a Aburgess
//  Addition of AUDIO Diagnostic dialog
//  
//  2     9/02/97 9:42a Aburgess
//  added master volume control flags
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  9     9/10/96 12:59p Aburgess
//  move commonly used but infrequently changed header files to stdafx.h
//  (precompiled header)
//  
//  8     8/22/96 3:52p Nrobins
//  make max volume 0 instead of 10000 for current direct sound
//  
//  5     6/26/96 11:24a Aburgess
//  added new Source Control headers
// 
//  $Nokeywords:$
//========================================================================

#ifndef __SND_H__
#define __SND_H__

///========================================================================
//							GLOBAL DEFINES
///========================================================================

#ifndef	TRUE
#define	TRUE						~0
#endif
#ifndef	FALSE
#define	FALSE						 0
#endif

#define	SND_MAX_NAME_LEN			64

#define	SND_NULL_SND_ID		 (ULONG)~0
#define	SND_BAD_SND_ID		 (ULONG)~0
#define	SND_BAD_FILE_POS	 (ULONG)~0
#define	SND_NULL_SND_PTR	 (ULONG)~0

#define	SND_NO_SOUNDS               ~0
#define	SND_MAX_SOUNDS             256
#define	SND_MAX_BUF_SIZE          (35*1024)
#define	SND_MAX_SND_FILES           16

// sound status values
#define	SND_NEW_STATUS				 0
#define	SND_ACTIVE_STATUS			 1
#define	SND_BAD_STATUS				 2

#define	SND_MIN_FREQUENCY		 10000
#define	SND_MAX_FREQUENCY		100000

#define	SND_MIN_PAN				-10000
#define	SND_BALANCED_PAN		     0
#define	SND_MAX_PAN				 10000

#define	SND_MIN_VOLUME			-10000
#define	SND_BALANCED_VOLUME		     0
#define	SND_MAX_VOLUME			     0	// 10000 in future DS release

#define	SND_MAX_PRIORITY		  0xFF		
#define	SND_HIGH_PRIORITY		  0x3F		
#define	SND_MID_PRIORITY		  0x1F		
#define	SND_LOW_PRIORITY		  0x0F		
#define	SND_MIN_PRIORITY		  0x00		

#define	SND_11kHZ_FREQUENCY		 11000
#define	SND_22kHZ_FREQUENCY		 22000
#define	SND_44kHZ_FREQUENCY		 44000

#define	SND_FREQUENCY_DEFAULT	SND_22kHZ_FREQUENCY	
#define	SND_PAN_DEFAULT			SND_BALANCED_PAN	
#define	SND_VOLUME_DEFAULT		SND_BALANCED_VOLUME

#define SND_VOLUME_INC			   500


#if 0
// The values for PAN may change in range...

//#define PAN_TB_MIN              0
//#define PAN_TB_MAX              2000
//#define PAN_TB_CENTER           1000
//#define PAN_MULTIPLIER          1
#define PAN_MIN                 0
#define PAN_MAX                 800
#define PAN_CENTER              400
#define PAN_SHIFT               (-400)
#define PAN_PAGESIZE            10
#define PAN_DIV                 10
#define PAN_MULT                10

//#define PAN_DSB_MIN           (-400)
//#define PAN_DSB_MAX           400
//#define PAN_DSB_CENTER        0

//#define VOL_TB_MIN              0
//#define VOL_TB_MAX              1000
//#define VOL_MULTIPLIER          1
#define VOL_SHIFT               (-400)
#define VOL_MIN                 0
#define VOL_MAX                 400
#define VOL_PAGESIZE            10
#define VOL_DIV                 10
#define VOL_MULT                10
#define FREQ_MIN                441
#define FREQ_MAX                4410
#define FREQ_PAGESIZE           100
#define FREQ_MULTIPLIER         10
#define PROG_MIN                0
#define PROG_MAX                10000
#define PROG_MULTIPLIER         100

#endif

// SND Flag Fields
#define	SND_CLEAR_FLAG			0x0000
#define	SND_SFX_FLAG			0x0001
#define	SND_STREAM_FLAG			0x0002
#define	SND_VOICE_FLAG			0x0004
#define	SND_MUSIC_FLAG			0x0008
#define	SND_RESOURCE_FLAG		0x0010
#define	SND_unused_0020			0x0020
#define	SND_EOS_FLAG			0x0040
#define	SND_TIMER_FLAG			0x0080
#define	SND_PLAYING_FLAG		0x0100
#define	SND_FADE_IN_FLAG		0x0200
#define	SND_FADE_OUT_FLAG		0x0400
#define	SND_LOOP_FLAG			0x0800
#define	SND_INSTALLED_FLAG		0x1000
#define	SND_CUED_FLAG			0x2000
#define	SND_DELETE_FLAG			0x4000
#define	SND_DONE_FLAG			0x8000

#define	SND_FADE_FLAGS				0x0600

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================

typedef struct
{
	unsigned long	soundID;			// Sound ID name
	unsigned long	offset;				// offset from base of file to sound
} SND_ENTRY;

typedef struct
{
			 char	version[4];					// APP version identifier
	unsigned long	numberOfSounds;				// number of sound IDs in this file
	SND_ENTRY		sounds[ SND_MAX_SOUNDS ];	// actual sound information
	SND_ENTRY		endOfTable;					// End of Table Marker
} SND_HEADER;

typedef struct
{
			 char	chunkID[4];
	unsigned long	chunkSize;
} SND_CHUNK_HEADER;

typedef struct
{
	unsigned		nSndFileID;					// File ID for reference
	FILE*			pSndFile;					// File pointer to SND data
	char*			pSndFileName;				// Name of SND data file
} SND_FILES;

typedef struct
{
	char*				pSndFileName;		// .snd or .wav filename
	FILE*				pSndFile;			// .snd or .wav file containing data
	ULONG				nSndStart;			// Start offset into file to reach sound chunk
	ULONG				nSndSize;			// size of raw stream data
	WAVEFORMATEX		wfSndFormat;		// sound wave form data
} SND_WAV;

typedef struct
{
	ULONG				nResID;				// Resource ID identifier
	char*				pResName;			// Resource Name String [alternative]
	ULONG				nImageLen;			// length of sound data
	BYTE*				pSndData;			// sfx data buffer
} SND_RES;

typedef struct
{
	ULONG				nAudioID;			// audio identifier
	ULONG				nSndID;				// snd identifier
	USHORT				bFlags;				// Flag fields
	USHORT				nRefCount;			// number of references to this sound

	union	{
		SND_RES			resSnd;				// resource based sound
		SND_WAV			wavSnd;				// wave file based sound
	};

} SND;

typedef struct
{
	ULONG	nAudioID;						// Audio ID
	char	SndName[ SND_MAX_NAME_LEN+1 ];	// Sound String Name
 } SND_NAMES;

//=========================================================================
//		GLOBAL data
//=========================================================================
extern	BOOL			SNDenabled;

///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================
BOOL			sndInit( HWND hwnd, UINT nMaxSounds );
void			sndExit( void );
ULONG			sndCreate( ULONG nAudioID, USHORT bFlags, unsigned nFileID, ULONG* offset );
void			sndDelete( ULONG nSndID );
void			sndDirectSoundCleanup( void );
LPDIRECTSOUND	sndGetDSobject( void );

// Global Frequency levels (effect pitch)
//		specifies at which rate the buffer is played
//		range: 10,000 <= nFrequency <= 100,000 : 100Hz to 100kHz
//		normal rates are 11kHz, 22kHz, 44kHz
BOOL		sndGetFrequency( LPDIRECTSOUNDBUFFER pDSbuffer, LONG* pFrequency );
BOOL		sndSetFrequency( LPDIRECTSOUNDBUFFER pDSbuffer, LONG nFrequency );

// Global Volume levels:
//		Specifies the volume level of the buffer.
//		The initial volume of a buffer is always 0. Any modification in volume
//		levels reflected by values other than 0. Positive values increase volume
//		and negative values decrease volume
//
//		range:  -10,000 <= volumne <= 10,000 : -100db (silent) to 100db
//
BOOL		sndGetVolume( LPDIRECTSOUNDBUFFER pDSbuffer, LONG* pVolume ); 
BOOL		sndSetVolume( LPDIRECTSOUNDBUFFER pDSbuffer, LONG nVolume );

// Global Pan levels
//		Specifies the volume level of the buffers left and right channels.
//		A value of 0 corresponds to both channels at full volume with no
//		panning effects. The sign of this value determines which channel
//		is being attenuated. Positive=Left channel, Negative = Right channel
//
//		range: -10,000 <= nPan <= 10,000 : -100db to 100db
//
//		if nPan= 10,000 the left channel is silent
//             =-10,000 the right channel is silent
BOOL		sndGetPan( LPDIRECTSOUNDBUFFER pDSbuffer, LONG* pPan );
BOOL		sndSetPan( LPDIRECTSOUNDBUFFER pDSbuffer, LONG nPan );

// Stop a sound being played
BOOL		sndStop( LPDIRECTSOUNDBUFFER pDSbuffer );

// Find the "WAVE" chunk. This reads to the end of the "WAVE" header
ULONG		sndFindWave( FILE* pSndFile );

// Retrieve the WAVEFORMATEX information
BOOL		sndFindWaveformatex( FILE* pSndFile, ULONG nSndStart, WAVEFORMATEX* pWaveformatex );

// Locate the raw smaple data information
BOOL		sndFindSample( FILE* pSndFile, ULONG nSndStart, ULONG nOffset, ULONG* nSize );

// Locate the SND data information
unsigned	sndFindSndID( ULONG nSndID, SND** pSndPtr, int* nSndIdx );
unsigned	sndFindAudioID ( ULONG nAudioID, SND** pSndPtr );
SND*		sndFindSlot( ULONG* nSndID );

// Locate the SND data information
unsigned	sndSaveFile( FILE* pSndFile, char* pSndFileName );
FILE*		sndGetFile( unsigned nFileID );
char*		sndGetFileName( unsigned pFileID );
void		sndDeleteFile( unsigned pFileID );

///========================================================================

#endif		// __SND_H__

///========================================================================
//								EOF
///========================================================================
