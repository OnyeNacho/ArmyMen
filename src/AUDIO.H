//========================================================================
//	FILE:			$Workfile: AUDIO.H $
//
//	DESCRIPTION:	Audio processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, May 02, 1996
//
//	REVISION:		$Header: /ArmyMen/src/AUDIO.H 37    4/02/98 10:42p Nrobinso $
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
//  $Log: /ArmyMen/src/AUDIO.H $
//  
//  37    4/02/98 10:42p Nrobinso
//  decrease audio range
//  
//  36    4/02/98 2:03p Phu
//  typecast to prevent warnings
//  
//  35    3/22/98 3:58p Nrobinso
//  remove static streams
//  
//  34    3/22/98 2:49p Nrobinso
//  remove vehicle audio call by audiostopall; add script loop off command
//  
//  33    3/18/98 8:20a Aburgess
//  modifications to AUDIOsounds compression
//  
//  32    3/18/98 2:32a Nrobinso
//  have a audio registry writing routine
//  
//  31    3/15/98 7:13p Nrobinso
//  reduce sfx distance range
//  
//  30    2/25/98 10:31p Nrobinso
//  add audioGetSndByAudioID
//  
//  29    2/20/98 6:17p Nrobinso
//  remove static sfx calls
//  
//  28    2/20/98 1:20p Nrobinso
//  fix up sounds
//  
//  27    2/20/98 12:00p Aburgess
//  modifications to support clean up and deletion of SFX sounds
//  
//  26    2/17/98 7:52p Nrobinso
//  remove audiokill
//  
//  25    2/17/98 8:54a Aburgess
//  new audioplay interface
//  
//  24    2/03/98 2:40p Aburgess
//  modifications made to correct music stream failures
//  
//  23    1/28/98 10:09a Aburgess
//  modifications made to correct Audio memory leaks on exit
// 
//  $Nokeywords:$
///========================================================================

#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "snd.h"				// SND  defines, structures, and prototypes
#include "sfx.h"				// SFX  defines, structures, and prototypes
#include "strm.h"				// STRM defines, structures, and prototypes
#include "voice.h"				// VOICE defines, structures, and prototypes
#include "sounds.h"
#include "streams.h"
#include "voices.h"
#include "army.h"
#include "object.h"

///========================================================================
//							GLOBAL DEFINES
///========================================================================

#ifndef	TRUE
#define	TRUE						~0
#endif
#ifndef	FALSE
#define	FALSE						 0
#endif

#define	AUDIO_OK					 0
#define	AUDIO_ERR					SND_NULL_SND_ID

#define	AUDIO_MAX_SOUNDS		   2048
#define	AUDIO_MAX_VOICES			256
#define	AUDIO_MAX_STREAMS			256
#define	AUDIO_MAX_SFXS				256
#define	AUDIO_MAX_FILES			     16
#define	AUDIO_MAX_STREAM_BUFFERS	 4

// audio states
#define	AUDIO_INIT_STATE			0
#define	AUDIO_SFX_STATE				1
#define	AUDIO_STRM_STATE			2
#define	AUDIO_LINK_STATE			3
#define	AUDIO_VOLUME_STATE			4
#define	AUDIO_EXIT_STATE			5

#define	AUDIO_NULL_ID			    ~0
#define	AUDIO_NULL_SOUND		    ~0

#define	AUDIO_11kHZ_FREQUENCY	 SND_11kHZ_FREQUENCY
#define	AUDIO_22kHZ_FREQUENCY	 SND_22kHZ_FREQUENCY
#define	AUDIO_44kHZ_FREQUENCY	 SND_44kHZ_FREQUENCY

#define	AUDIO_MONO					 0
#define	AUDIO_STEREO				 1

#define	AUDIO_FADE_IN				 0
#define	AUDIO_FADE_OUT				~0

#define	AUDIO_MIN_FREQUENCY		SND_MIN_FREQUENCY
#define	AUDIO_MAX_FREQUENCY		SND_MAX_FREQUENCY

#define	AUDIO_MIN_PAN			SND_MIN_PAN
#define	AUTIO_BALANCED_PAN		SND_BALANCED_PAN
#define	AUDIO_MAX_PAN			SND_MAX_PAN

#define	AUDIO_MIN_VOLUME		SND_MIN_VOLUME
#define	AUDIO_BALANCED_VOLUME	SND_BALANCED_VOLUME
#define	AUDIO_MAX_VOLUME		SND_MAX_VOLUME

#define	AUDIO_MAX_PRIORITY		  0xFF		
#define	AUDIO_HIGH_PRIORITY		  0x3F		
#define	AUDIO_MID_PRIORITY		  0x1F		
#define	AUDIO_LOW_PRIORITY		  0x0F		
#define	AUDIO_MIN_PRIORITY		  0x00		

#define	AUDIO_FREQUENCY_DEFAULT	SND_22kHZ_FREQUENCY	
#define	AUDIO_PAN_DEFAULT		SND_BALANCED_PAN	
#define	AUDIO_VOLUME_DEFAULT	SND_BALANCED_VOLUME	

// AUDIO boolean flags
#define	AUDIO_CLEAR_FLAG		SND_CLEAR_FLAG
#define	AUDIO_RESOURCE_FLAG		SND_RESOURCE_FLAG
#define	AUDIO_STREAM_FLAG		SND_STREAM_FLAG
#define	AUDIO_FADE_IN_FLAG		SND_FADE_IN_FLAG
#define	AUDIO_FADE_OUT_FLAG		SND_FADE_OUT_FLAG
#define	AUDIO_FADE_FLAGS		SND_FADE_FLAGS
#define	AUDIO_LOOP_FLAG			SND_LOOP_FLAG
#define	AUDIO_EOS_FLAG			SND_EOS_FLAG
#define	AUDIO_DONE_FLAG			SND_DONE_FLAG

// David  B
#define  LASTSOUND	-1
#define  MIN_VOLUME 1800
#define  VOLUME_PERCENT_MULT   MIN_VOLUME/100

// Davd M
#define VOL_MAX_PERCENT 100
#define VOL_MIN_PERCENT 10
#define AUDIO_RANGE 1500

// audio music intensity
#define	AUDIO_INTENSITY_LO		0
#define	AUDIO_INTENSITY_HI		1

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================

typedef struct
{
	FILE*	pFilePtr;
	char*	pFileName;
} AUDIO_FILE;

typedef struct
{
	ULONG	nAudioID;
	ULONG	nSndID;
	USHORT	bFlags;
	LONG	nVolume;
} AUDIO_IDS;


///========================================================================
//							GLOBAL DATA
///========================================================================
extern ULONG			AUDIOsfxID;
extern ULONG			AUDIOstreamID;
extern ULONG			AUDIOvoiceID;

///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================

// Initialize the audio processor to handle up to nNumberSfxSounds and
//			and nNumberStrmSounds sounds
extern	BOOL		audioInit( HWND baseWnd );
extern	void		audioExit( void );
extern	BOOL		audioEnable( HWND baseWnd );
extern	void		audioDisable( void );
extern	void		audioClear( void );
extern	unsigned	audioOpen( char* pFileName, USHORT bFlags );
extern	void		audioClose( unsigned nFileID );
extern	void		audioSetMasterVolume( USHORT bFlag, LONG nVolume );
extern	LONG		audioGetMasterVolume( USHORT bFlag );
extern	unsigned	audioCreateSnd( unsigned nFileID, ULONG nAudioID,
						    unsigned nIndexToLoad, USHORT bFlags );
extern	void		audioStoreSnd( ULONG nAudioID, ULONG nSndID, USHORT bFlags );
extern	BOOL		audioDeleteSnd( ULONG nSndID  );
extern	BOOL		audioCue( ULONG nAudioID );
extern	BOOL		audioPlay( ULONG nAudioID, USHORT bFlags );
extern	BOOL		sndPlay( ULONG nSndID );
extern	BOOL		sndHalt( ULONG nSndID );
extern	BOOL		audioStop( ULONG nAudioID );
extern	BOOL		audioReset( ULONG nSndID );
extern	BOOL		audioDelete( ULONG nSndID );
extern	BOOL		audioChangeVolume( ULONG nAudioID, SHORT delta );
extern	int			audioFindVolumePercent( SPOINT *pSrc );
extern	int			audioFindVolumeItem( ITEM *pItem); 

// Global Frequency levels (effect pitch)
//		specifies at which rate the buffer is played
//		range: 10,000 <= nFrequency <= 100,000 : 100Hz to 100kHz
//		normal rates are 11kHz, 22kHz, 44kHz
extern	LONG		audioGetFrequency( void );
extern	BOOL		audioSetFrequency( LONG nFrequency );

// Global Volume levels:
//		Specifies the volume level of the buffer.
//		The initial volume of a buffer is always 0. Any modification in volume
//		levels reflected by values other than 0. Positive values increase volume
//		and negative values decrease volume
//
//		range:  -10,000 <= volumne <= 10,000 : -100db (silent) to 100db
//
extern	LONG		audioGetVolume( ULONG nSndID ); 
extern	BOOL		audioSetVolume( ULONG nSndID, LONG nVolume, BOOL bMax );

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
extern	LONG		audioGetPan( void );
extern	BOOL		audioSetPan( LONG nPan );

extern	ULONG	audioCreateLink( unsigned nFileID, ULONG* pLinks, USHORT bFlags );
extern	BOOL	audioMonitor ( UINT uTimerID );
extern	void	audioStopAll( void );

extern	void	audioVoiceOff( void );
extern	void	audioVoiceOn( void );
extern	BOOL	audioVoiceGetOn( void );
extern	void	audioMusicOff( void );
extern	void	audioMusicOn( void );
extern	BOOL	audioMusicGetOn( void );
extern	void	audioSfxOff( void );
extern	void	audioSfxOn( void );
extern	BOOL	audioSfxGetOn( void );
extern	void	AudioSetReg(void);

extern	void	Set_STRM_Volume_Percent( ULONG nSndID ,ULONG Percent, BOOL bMax);
extern	void	Set_SFX_Volume_Percent( ULONG nSndID ,ULONG Percent, BOOL bMax);
extern	void	Modify_SFX_Volume_Percent( ULONG nSndID ,ULONG Percent);
extern	ULONG	PlayStream(ULONG nAudioID, USHORT bFlags, BOOL bDelete );
extern	ULONG	PlayStreamUnit(ULONG nUaudioID, ULONG uid, USHORT bFlags);
extern	ULONG	EndStreamUnit(ULONG nAudioID);
extern	void	StopStream(ULONG nAudioID);
extern	void	StopAllStreams( void );
extern	void	CleanUpStreams( void );
extern	void	CleanUpSfx( void );

extern	void	SndSetVolumePercent( ULONG nSndID, ULONG Percent, BOOL bMax );
extern	void	SndSetVolumePoint(ULONG nSndID, SPOINT *pPoint);
extern	void	SndPlayItem(ULONG nSndID, ITEM *pItem);
extern	ULONG	AudioPlayItem(ULONG nAudioID, ITEM *pItem);
extern	ULONG	AudioPlayPoint(ULONG nAudioID, SPOINT *pPoint);

extern	ULONG	audioFindIDbyName( char* pAudioName );
extern	char*	audioIDname( ULONG nAudioID );
extern	char*	audioSndIDname( ULONG nSndID );

extern	void	audioDump( void );
extern	void	audioSetTableIndex( int nIndex );
extern	void	audioSetIntensity( int nIntensity );
extern	int		audioGetIntensity( void );
extern	AUDIO_IDS*	audioGetSndByAudioID( ULONG nAudioID  );
extern	void	audioCleanUp( void );

///========================================================================

#endif		// __AUDIO_H__

///========================================================================
//								EOF
///========================================================================
