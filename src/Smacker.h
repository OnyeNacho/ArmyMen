//========================================================================
//	FILE:			$Workfile: Smacker.h $
//
//	DESCRIPTION:	SMACKER video playback prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, January 8, 1998
//
//	REVISION:		$Header: /ArmyMen/src/Smacker.h 9     4/02/98 7:10p Aburgess $
//
//========================================================================
//                 COPYRIGHT(C)1997,1998 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Smacker.h $
//  
//  9     4/02/98 7:10p Aburgess
//  making the movies work
//  
//  8     4/02/98 9:39a Aburgess
//  modifications to support interlaced and non-interlaced Smaker videos
//  
//  7     3/23/98 12:16p Aburgess
//  modification to Smacker class
//  
//  6     3/05/98 1:06p Aburgess
//  modifications to properly set the smacker palette using only the middle
//  236 colors. Checks to restore the front buffer surface during
//  rendering. And recognition of LastKeyFrame updates.
//  
//  5     2/18/98 1:30p Aburgess
//  adjusted SMACKER playback frame rate from 20 to 24. New files will be
//  done in 20 frames/sec (50ms).
//  
//  4     1/20/98 8:36a Aburgess
//  Smacker now interruptable. Playback is currently 320 x 200, We are
//  unable to stretch the image.
//  
//  3     1/20/98 12:46a Aburgess
//  lastest working murder
//  
//  2     1/14/98 2:42p Aburgess
//  wrong version checked in initially
//
//  $Nokeywords:$
//========================================================================
#include "smack.h"

#define SMACKER_PLAYBACK_TIMER_PERIOD		50			// 20 frames/second  (1000ms/50)
#define SMACKER_PLAYBACK_TIMER_ACCURACY		10

//========================================================================
//						CSMACKER CLASS
//========================================================================
class CSmacker
{
	// public member functions
public:
					CSmacker(char* fname, int w = -1, int h = -1, BOOL bInterlaced = FALSE);	// smacker constructor
					~CSmacker();									// smacker destructor

//	void CALLBACK	OnTick(int nParam);								// event callback
	void			InitPalette(void);								// initialize the Smacker Palette
	virtual BOOL	Render( void );									// display the smacker playback data 
	BOOL			Play(int nFrame = 0);							// execute a smacker playback
//	void			SetStopHandler(LPVOID pFunc, int nParam);
	void			SetVolume(unsigned long vol);					// set the playback volume
	void			BuildPalette( LPDIRECTDRAWSURFACE pBuffer );	// build the playback palette

	// private member functions
private:
	// protected member functions
protected:
	void			RenderSmackerFrame( LPDIRECTDRAWSURFACE pBuffer ); // render a single playback frame
	void			RenderPlayback( LPDIRECTDRAWSURFACE pBuffer );

	// public member variables
public:
	LPDIRECTDRAWSURFACE	m_pPlaybackBuff;		// handle to playback window
//	LPDIRECTDRAWSURFACE	m_pPlayback1;			// handle to playback window
//	LPDIRECTDRAWSURFACE	m_pPlayback2;			// handle to playback window
	BOOL				m_bRegisteredForEvents;	// flag for signifying event callback control
	BOOL				m_bPlaying;				// flag signifying that a playback is being played
	BOOL				m_bStretching;			// flag signifying playback stretching
	BOOL				m_bDirty;
	BOOL				m_bInterlaced;			// Interlaced format flag
	Smack*				m_smk;					// smacker reference for an open playback
	u32					m_LastKey;				// last known smacker keyframe
	u32					m_SurfaceType;			// DirectDraw surface type 8bpps, 16bpps, etc.
	LONG				m_uTimerID;				// smaker playback timer ID
	char				m_szFname[128];			// smacker playback file name

	// private member variables
private:
	// protected member variables
protected:
	RECT				m_PlaybackRect;			// playback window rectangle
//	CDib*				m_pPlaybackBuff;		// handle to playback CDib
	int					m_PlaybackWidth;		// width of playback window
	int					m_PlaybackHeight;		// height of playback window
//	LONG				((*m_StopHandler)(int iData));	// callback for signifying end of playback
//	int					m_StopHandlerParam;		// callback input parameter
};

//========================================================================
//						GLOBAL PROTOTYPES
//========================================================================
extern	void CALLBACK SmackerOnTick( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 );
extern	void SmackerSetObject( void* pSmacker );
extern	void SmackerUpdate( void );
extern	void SmackerEject( void );
extern	void SmackerCleanUp( void );

//========================================================================
//								EOF
//========================================================================
