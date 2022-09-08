//========================================================================
//	FILE:			$Workfile: Smacker.cpp $
//
//	DESCRIPTION:	SMACKER video playback routines and processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, January 8, 1998
//
//	REVISION:		$Header: /ArmyMen/src/Smacker.cpp 29    4/02/98 10:55p Nrobinso $
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
//  $Log: /ArmyMen/src/Smacker.cpp $
//  
//  29    4/02/98 10:55p Nrobinso
//  turn off focus trace
//  
//  28    4/02/98 7:10p Aburgess
//  making the movies work
//  
//  27    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  26    4/02/98 9:39a Aburgess
//  modifications to support interlaced and non-interlaced Smaker videos
//  
//  25    3/26/98 9:58a Aburgess
//  made smacker aware of Alt-Tab
//  
//  24    3/23/98 4:23p Aburgess
//  removed excess trace statement
//  
//  23    3/23/98 12:17p Aburgess
//  modifications to support double buffering, and proper deletion of
//  smacker objects at end of movie play
//  
//  22    3/19/98 9:40a Aburgess
//  modifications made to present the 3DO logo Video
//  
//  21    3/16/98 10:34a Aburgess
//  modifications made to pulee setting of minimum timerEvent period and
//  termination to audioEnable() and audioDisable() respectively.
//  
//  20    3/10/98 11:23p Nrobinso
//  make sure both cursors are off
//  
//  19    3/10/98 3:32p Nrobinso
//  change include back to ui
//  
//  18    3/10/98 3:25p Nrobinso
//  
//  17    3/07/98 11:52p Nrobinso
//  move .h file to stdafx
//  
//  16    3/06/98 4:56p Aburgess
//  removed interlacing for creation
//  
//  15    3/06/98 11:44a Nrobinso
//  
//  14    3/06/98 10:45a Aburgess
//  removed LastKey frame check from SmackerUpdate
//  
//  13    3/05/98 1:47p Aburgess
//  added check for existence of SmackerObj
//  
//  12    3/05/98 1:06p Aburgess
//  modifications to properly set the smacker palette using only the middle
//  236 colors. Checks to restore the front buffer surface during
//  rendering. And recognition of LastKeyFrame updates.
//  
//  11    2/20/98 6:16p Nrobinso
//  turn off pointer during movies
//  
//  10    2/13/98 3:59p Nrobinso
//  remove avi player
//  
//  9     2/09/98 1:54p Aburgess
//  modifications made to support IN GAME screens, Cursor control, and
//  Rules presentation
//  
//  8     2/02/98 11:42a Phu
//  implement ShowWindowsCursor()
//  
//  7     1/20/98 3:42p Nrobinso
//  turn cursor on & off
//  
//  6     1/20/98 3:25p Nrobinso
//  fix centering in windowed mode
//  
//  5     1/20/98 10:50a Dmaynard
//  Removed and ASSERT that asserts directsound is available.  TEMP FIX
//  for now if DSound not available, don't try to play smacker movies..
//  This re-enables compiling with AUDIO_OFF.
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

#include "stdafx.h"

#include "MainFrm.h"
#include "Audio.h"
#include "input.h"
#include "Dd.h"
#include "Error.h"

//smacker
#define WIN32_LEAN_AND_MEAN

#include "smacker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPDIRECTDRAWSURFACE CreatePixelSurfaceOfSize( DWORD width, DWORD height, LONG flags, COLORREF rgb );

//========================================================================
//	LOCAL VARIABLES
//========================================================================
static	int				bSmackSoundInitialized = FALSE;
static	PALETTEENTRY	pal[256];
static	LPDIRECTSOUND	pDirectSound;
static	CSmacker*		pSmackerObj;

static	BOX				rects1[256];
static	BOX				rects2[256];
static	BOX				merged[256];
static	ULONG			doneone   =0;
static	ULONG			lastnum   = 0;
static	BOX*			lastframe = rects1;
static	BOX*			curframe  = rects2;

//========================================================================
//	LOCAL PROTOTYPES
//========================================================================

		void CALLBACK		SmackerOnTick( int nParam );
		void				SmackerOnDone( void );
static	void				SmackerMergeInterRect(BOX* r1, BOX* r2, BOX* m, BOX* i);
static	void				SmackerMergeRects( BOX* r1, ULONG r1num, BOX* r2, ULONG r2num, BOX** o, ULONG* onum);
static	void				SmackerBlitRect( HWND wh,ULONG x, ULONG y, ULONG w, ULONG h);
static	LPDIRECTDRAWSURFACE	SmackerCreateBuffer( int nWidth, int nHeight );
static	void				SmackerDirtyRects( void );

//========================================================================
//	CSmacker Constructor and Destructor
//========================================================================

CSmacker::CSmacker(char* fname, int stretch_w, int stretch_h, BOOL bInterlaced )
{
	// initialize the class members
	m_bRegisteredForEvents = FALSE;			// flag for signifying event callback control
	m_bPlaying             = FALSE;			// flag signifying that a playback is being played
	m_bStretching          = FALSE;			// flag signifying playback stretching
	m_bDirty               = FALSE;
	m_bInterlaced          = bInterlaced;

	m_PlaybackRect.left    = 0;
	m_PlaybackRect.top     = 0;
	m_PlaybackRect.right   = 0;
	m_PlaybackRect.bottom  = 0;
	m_PlaybackWidth        = stretch_w;		// width of playback window
	m_PlaybackHeight       = stretch_h;		// height of playback window
	m_uTimerID             = 0;
//	m_StopHandler          = NULL;			// callback for signifying end of playback
//	m_StopHandlerParam     = -1;			// callback input parameter
	m_smk                  = NULL;			// smacker reference for an open playback
	m_LastKey              = 0;				// last smacker Key Frame
	strcpy( m_szFname, fname );				// smacker playback file name

	// evaluate the input parameters
	if (m_PlaybackWidth != -1)
		m_bStretching = TRUE;

	if (!bSmackSoundInitialized)
	{
		// Get the DirectSound Object for this application
		pDirectSound = sndGetDSobject();
		//  ASSERT( pDirectSound );	   // means we have to compile with audoi on

		if( pDirectSound) {
			u8 err = SmackSoundUseDirectSound(pDirectSound);
			bSmackSoundInitialized = TRUE; 
		}
	}
	m_PlaybackRect.left = 0;
	m_PlaybackRect.top  = 0;

	if ( m_bInterlaced )
		m_smk = SmackOpen( fname, (SMACKTRACKS|SMACKNEEDVOLUME|SMACKNOSKIP|SMACKYINTERLACE), SMACKAUTOEXTRA);
	else
		m_smk = SmackOpen( fname, (SMACKTRACKS|SMACKNEEDVOLUME),							 SMACKAUTOEXTRA);
	if ( m_smk )
	{
		if ( m_bStretching )
		{   // stretch the smacker playback to the specified window size
			m_PlaybackRect.right  = m_PlaybackWidth-1;
			m_PlaybackRect.bottom = m_PlaybackHeight-1;
		}
		else
		{
//			m_PlaybackRect.right  = m_smk->Width-1;
//			m_PlaybackRect.bottom = m_smk->Height-1;
			m_PlaybackRect.right  = m_smk->Width;
			m_PlaybackRect.bottom = m_smk->Height;
		}
	}

#if 1
	m_pPlaybackBuff = SmackerCreateBuffer( (m_PlaybackRect.right - m_PlaybackRect.left),
										   (m_PlaybackRect.bottom - m_PlaybackRect.top));	// handle to playback window
#else
	m_pPlayback1    = SmackerCreateBuffer( (m_PlaybackRect.right - m_PlaybackRect.left),
										   (m_PlaybackRect.bottom - m_PlaybackRect.top));	// handle to playback window

	m_pPlayback2    = SmackerCreateBuffer( (m_PlaybackRect.right - m_PlaybackRect.left),
										   (m_PlaybackRect.bottom - m_PlaybackRect.top));	// handle to playback window
	m_pPlaybackBuff = m_pPlayback1;
#endif
	m_SurfaceType   = SmackDDSurfaceType( m_pPlaybackBuff );

	InitPalette();
}

CSmacker::~CSmacker( void )
{
	if (m_smk && m_bRegisteredForEvents)
	{
//		g_pEventManager->UnregisterAll(this);

		// kill off the timer event controlling this stream
		if ( m_uTimerID )
			timeKillEvent( m_uTimerID );
		m_uTimerID             = 0;
		m_bRegisteredForEvents = FALSE;

#if 0
		// this will display summary info, if you uncomment it
		char buf[256];
		SmackSum ss;

		SmackSummary(m_smk,&ss); 
		sprintf(buf,"Smacker(%s): frames: %i  decomp : %i  blit : %i  read : %i time : %i\n",
			m_szFname, ss.TotalFrames, ss.TotalDecompTime, ss.TotalBlitTime,
			ss.TotalReadTime, ss.TotalTime);
		TRACE( buf );
		sprintf(buf,"Smacker(%s): fps: %i  decomp %%: %i  blit %%: %i  read %%: %i\n",
			m_szFname, ss.TotalFrames*1000/ss.TotalTime, ss.TotalDecompTime*100/ss.TotalTime,
			ss.TotalBlitTime*100/ss.TotalTime,ss.TotalReadTime*100/ss.TotalTime);
		TRACE( buf );
//		MessageBox(0,buf,"Summary",MB_OK);
#endif

		// release the playback surface
		m_pPlaybackBuff->Release();
		m_pPlaybackBuff = NULL;

		SmackClose(m_smk);
	}
}

//========================================================================
//	InitPalette()
//========================================================================

void CSmacker::InitPalette(void)
{
	HWND	wh;
	int		i;
	HDC		dc;

	wh = pMainFrame->m_hWnd;
	dc = GetDC( wh );

	GetSystemPaletteEntries(dc,0,256,pal);

	for(i=0;i<10;i++)
		pal[i].peFlags=0;
	for(;i<246;i++)
		pal[i].peFlags=PC_NOCOLLAPSE;
	for(;i<256;i++)
		pal[i].peFlags=0;

	ReleaseDC(wh,dc);
}

//========================================================================
//	Play()
//========================================================================

BOOL CSmacker::Play(int nFrame)
{
	BOOL	bSuccess = FALSE;
	LONG	nData    = 0;

 	if (!bSmackSoundInitialized) return FALSE;

	// now play this smacker playback
	if (m_smk && !m_bPlaying) 
	{
		m_bPlaying = TRUE;

		// go ahead and render the first frame
		pSmackerObj->Render();

//		g_pEventManager->Register(this, (FPTickCallback) OnTick);

		// Start a timer event. After the event has been activated, the timer will
		// make a callback to the Smacker monitor routine "OnTick".
		nData = timeSetEvent( SMACKER_PLAYBACK_TIMER_PERIOD, SMACKER_PLAYBACK_TIMER_ACCURACY,
							  (LPTIMECALLBACK)SmackerOnTick, (DWORD)0, TIME_PERIODIC
							);

		// if the timer was successfull installed, set the appropriate flag
		m_uTimerID = nData;
		if ( m_uTimerID == 0 )
		{
			delete pSmackerObj;
			pSmackerObj = NULL;
			pMainFrame->PostMessage(AVIVID_NOT_STARTED, 0, 0L);	// notify main code that clip never started
			return FALSE;
		}
		else
			m_bRegisteredForEvents = TRUE;

		// disable the windows cursor
		ShowWindowsCursor(FALSE);
		ShowTheCursor(FALSE);

		// signify that the process was successful
		bSuccess = TRUE;
	}

	return( bSuccess );
}

//========================================================================
//	SetVolume()
//========================================================================

void CSmacker::SetVolume(unsigned long volo)
{
	if (!bSmackSoundInitialized)  return;
	u32 vol = volo;
	SmackVolumePan(m_smk, SMACKTRACK1, vol, 32758);
	SmackVolumePan(m_smk, SMACKTRACK2, vol, 32758);
	SmackVolumePan(m_smk, SMACKTRACK3, vol, 32758);
	SmackVolumePan(m_smk, SMACKTRACK4, vol, 32758);
	SmackVolumePan(m_smk, SMACKTRACK5, vol, 32758);
	SmackVolumePan(m_smk, SMACKTRACK6, vol, 32758);
	SmackVolumePan(m_smk, SMACKTRACK7, vol, 32758);
}

//void CSmacker::SetStopHandler( LPVOID pFunc, int nFuncParam )
//{
//	m_StopHandler      = (void*)pFunc;
//	m_StopHandlerParam = nFuncParam;
//}

//========================================================================
//	BuildPalette()
//========================================================================

void CSmacker::BuildPalette(  LPDIRECTDRAWSURFACE pBuffer  )
{
	LPDIRECTDRAWPALETTE lpDDP = NULL;
	u32 i;
	u8* c;

//	c=m_smk->Palette;//+(3*10);   skip windows colors
	c=m_smk->Palette+(3*10);	//skip windows colors
//	for(i=0;i<256;i++) // i<246;i++)only do the middle 236 colors
	for(i=10;i<246;i++)			// only do the middle 236 colors
	{      
		pal[i].peRed=*c++;
		pal[i].peGreen=*c++;
		pal[i].peBlue=*c++;
	}

	pBuffer->GetPalette(&lpDDP);
	if ( lpDDP )
	{
		lpDDP->SetEntries(0,0,256,pal);
	//	lpDDP->SetEntries(0,10,236,pal);
		lpDDP->Release();
	}
}

//========================================================================
//	Render()
//========================================================================

BOOL CSmacker::Render( void )
{
	if (m_bPlaying)
	{
		// does smacker want us to wait
		if ( !SmackWait(m_smk) )
		{
			//render the available frame to the back buffer
			RenderSmackerFrame( pFrontBuffer );
		}
//		else
//			TRACE( "CSmacker:Render() waiting\n" );
	}
	return TRUE;
}

//========================================================================
//	RenderSmackerFrame()
//========================================================================

void CSmacker::RenderSmackerFrame( LPDIRECTDRAWSURFACE pBuffer )
{
	DDSURFACEDESC		ddsd;

	// make sure we have the focus
	if ( GetFocus() != pMainFrame->GetHwnd() )
	{
//		TRACE( "WARNING: not in current focus. [%s:%d]\n",
//			__FILE__, __LINE__ );
		return;
	}

	// see if we need to apply the palette
	if ( (m_smk->NewPalette)  && (m_SurfaceType==0) )    
	{
		BuildPalette( pBuffer );
		if ( m_pPlaybackBuff->Lock(NULL, &ddsd, DDLOCK_WAIT /* DDSCAPS_BACKBUFFER */, NULL) == DDERR_SURFACELOST )
		{
			if (m_pPlaybackBuff->Restore()==DD_OK)
			{
				m_pPlaybackBuff->SetPalette(current_palette.pDDPalette);
				BuildPalette( pBuffer );  // reset palette
			}
			else
				return;
		}
	}

	// acquire the direct draw surface to blit to
	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize = sizeof(DDSURFACEDESC);
	if ( m_pPlaybackBuff->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) == DDERR_SURFACELOST )
	{
		if (m_pPlaybackBuff->Restore()!=DD_OK)
		{
			TRACE( "WARNING: failed to restore Smacker surface. [%s:%d]\n",
				__FILE__, __LINE__ );
			return;  // just exit if we can't restore the surface
		}
	}

	// smack to the playback buffer
	SmackToBuffer( m_smk,
				   0,
				   0,
				   ddsd.lPitch,
				   m_smk->Height,
				   ddsd.lpSurface,
				   m_SurfaceType			  //0 is for 8bpp surface, use other flags for 16bpp
				 );

	SmackDoFrame(m_smk);
//	if ( SmackDoFrame(m_smk) )
//			TRACE( "SmackNextFrame(): wants to skip a frame\n" );

	m_pPlaybackBuff->Unlock(NULL);

	// now blit this surface to the buffer
	RenderPlayback( pBuffer );

#if 0
	// clean up any dirty rectangles
	SmackerDirtyRects();
#endif

	if ((m_smk->FrameNum==(m_smk->Frames-1))) // goto the next if not on the last
	{
		m_bPlaying = FALSE;
		SmackerOnDone();
	}
	else
		SmackNextFrame(m_smk);
}

//========================================================================
//	RenderPlayback()
//========================================================================

void CSmacker::RenderPlayback( LPDIRECTDRAWSURFACE pBuffer )
{
	HRESULT	hResult;
	RECT	DRect,SRect;

	if (pBuffer == pFrontBuffer )
	{
		// find the windows upper left corner and center
		DRect.left = rcWindowScreen.left + ((rcWindowScreen.right - rcWindowScreen.left - m_smk->Width)/2);
		DRect.top  = rcWindowScreen.top  + ((rcWindowScreen.bottom - rcWindowScreen.top - m_smk->Height)/2);
	}
	else
	{
		// the back buffer always has a 0,0 upper left, center within the windows width
		DRect.left = ((rcWindowScreen.right - rcWindowScreen.left) - m_smk->Width) /2;
		DRect.top  = ((rcWindowScreen.bottom - rcWindowScreen.top) - m_smk->Height) /2;
	}

	DRect.right  = DRect.left + m_smk->Width;
	DRect.bottom = DRect.top + m_smk->Height;

	SRect.left   = 0;
	SRect.top    = 0;
	SRect.right  = m_smk->Width;
	SRect.bottom = m_smk->Height;

	// use BltFast if the blit is one to one, otherwise use Blt
	if ( pSmackerObj->m_bStretching )
		hResult = pBuffer->Blt( &DRect, m_pPlaybackBuff, &SRect, DDBLT_WAIT|DDBLT_ASYNC, 0);
	else
		hResult = pBuffer->Blt( &DRect, m_pPlaybackBuff, &SRect, DDBLT_WAIT|DDBLT_ASYNC ,0);
//		hResult = pBuffer->BltFast( DRect.left, DRect.top, m_pPlaybackBuff, &SRect, DDBLTFAST_WAIT);

	if ( hResult != DD_OK )
		TRACE( "RenderPlayback() Blit failed: %s\n", DDErrorToString( hResult ) );
//	else
//		TRACE( "RenderPlayback(): Frame %d\n", m_smk->FrameNum );

#if 0
	// now swap the buffers
	if ( m_pPlaybackBuff == m_pPlayback1 )
		m_pPlaybackBuff = m_pPlayback2;
	else
		m_pPlaybackBuff = m_pPlayback1;
#endif
}

//========================================================================
//	SmackerOnTick()
//========================================================================

void CALLBACK SmackerOnTick( UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dwData1, DWORD dwData2 )
{
  	//if SmackWait returns FALSE, then this obj is dirty, and
	//Render will be called later to decompress the frame onto
	//the output buffer
	if ( pSmackerObj )
	{
#if 0
		if ( pSmackerObj->m_bPlaying && ((UINT)(pSmackerObj->m_uTimerID) == uTimerID) )
		{
			if (!SmackWait( pSmackerObj->m_smk ))
				pSmackerObj->m_bDirty = TRUE;
		}
#else
		pSmackerObj->m_bDirty = TRUE;
#endif
	}
}

//========================================================================
//	SmackerOnDone()
//========================================================================

void SmackerOnDone( void )
{
	// send a message signifying the smacker playback is being ejected
	pMainFrame->PostMessage(AVIVID_EJECTED, 0, 0L);	// notify main code that clip ended
}

//========================================================================
//	SmackerSetObject()
//========================================================================

void SmackerSetObject( void* pSmacker )
{
	pSmackerObj = (CSmacker*)pSmacker;
}

//========================================================================
//	SmackerUpdate()
//========================================================================

void SmackerUpdate( void )
{
	if ( pSmackerObj )
	{
#if 0
		// This code does not do any repaints - it simply goes back to
		// the last key frame and restarts the video.

		if (pSmackerObj->m_LastKey)
		{
			SmackSoundOnOff( pSmackerObj->m_smk,0 );  // turn off sound so that it is synched
			SmackGoto( pSmackerObj->m_smk, pSmackerObj->m_LastKey );
			SmackSoundOnOff( pSmackerObj->m_smk,1 );  // when we turn it back on
		}
#endif

#if 0
		if ( pSmackerObj->m_bDirty )
		{
//			ShowWindowsCursor(FALSE);
			pSmackerObj->Render();
			pSmackerObj->m_bDirty = FALSE;
		}
#else
		pSmackerObj->Render();
		pSmackerObj->m_bDirty = FALSE;
#endif
	}
}

//========================================================================
//	SmackerEject()
//========================================================================

void SmackerEject( void )
{
	if ( pSmackerObj )
	{
#if 0
		TRACE( "SmackerEject( %s )\n", pSmackerObj->m_szFname );
#endif
		pSmackerObj->m_bPlaying = FALSE;
		SmackerOnDone();
//		delete pSmackerObj;
		pSmackerObj = NULL;
	}
}

//========================================================================
//	SmackerCleanUp()
//========================================================================

void SmackerCleanUp( void )
{
	if ( pSmackerObj )
	{
#if 0
		TRACE( "SmackerCleanUp( %s )\n", pSmackerObj->m_szFname );
#endif
		pSmackerObj = NULL;
	}
}

//========================================================================
//	SmackerMergeInterRect()
//========================================================================

#define RectBytes(r) (((r)->cx)*((r)->cy))

static void SmackerMergeInterRect(BOX* r1, BOX* r2, BOX* m, BOX* i)
{
	if (r1->x > r2->x)
	{
		m->cx=r1->cx+(r1->x - r2->x);    // do merge
		m->x=r2->x;
		i->x=r1->x;
		i->cx=r1->cx;
	}
	else
	{
		i->cx=r1->cx-(r2->x - r1->x);    // do inter
		i->x=r2->x;
		m->x=r1->x;
		m->cx=r1->cx;
	}
	if (r1->y > r2->y)
	{
		m->cy=r1->cy+(r1->y - r2->y);    // do merge
		m->y=r2->y;
		i->y=r1->y;
		i->cy=r1->cy;
	}
	else
	{
		i->cy=r1->cy-(r2->y - r1->y);    // do inter
		i->y=r2->y;
		m->y=r1->y;
		m->cy=r1->cy;
	}

	if ((r1->x+r1->cx) < (r2->x+r2->cx))
		m->cx=(r2->x+r2->cx) - m->x;    // do merge   
	else
		i->cx=(r2->x+r2->cx) - i->x;    // do inter

	if ((r1->y+r1->cy) < (r2->y+r2->cy))
		m->cy=(r2->y+r2->cy) - m->y;    // do merge
	else
		i->cy=(r2->y+r2->cy) - i->y;    // do inter

	if ((i->cx<=0) || (i->cy<=0))
	{
		i->x=0;
		i->y=0;
		i->cx=0;
		i->cy=0;
	}
}

//========================================================================
//	SmackerMergeRects()
//========================================================================

static void SmackerMergeRects( BOX* r1, ULONG r1num, BOX* r2, ULONG r2num, BOX** o, ULONG* onum)
{
	ULONG	c;
	BOX		bestmerg,tr1,tr2,tr3;
	ULONG	bestwast,besttot;
	BOX*	mr;
	ULONG	mnum;
	ULONG	totnum;
	ULONG	totamt,wasted;
	ULONG	rtotal;

	if (r1num==0)			// if no rects in r1, return r2
	{
		*o=r2;
		*onum=r2num;
	}
	else if (r2num==0)		// if no rects in r2, return r1
	{
		*o=r1;
		*onum=r1num;
	}
	else					// merge 'em
	{
		*o=merged;
		mnum=0;

		tr1=r1[0];
		totnum=r1num+r2num-1;
		r1[0].cx=-r1[0].cx;
		while (totnum)
		{
			bestwast=0x1000000;
			rtotal=RectBytes(&tr1);
			for(c=0;c<r1num;c++)
			{
				if (r1[c].cx>0)
				{
					SmackerMergeInterRect(&r1[c],&tr1,&tr2,&tr3);
					totamt=RectBytes(&tr2);
					wasted=totamt-RectBytes(&r1[c])-rtotal+RectBytes(&tr3);
					if (wasted<bestwast)
					{
						besttot=totamt;
						bestwast=wasted;
						bestmerg=tr2;
						mr=&r1[c];
						if (wasted==0)
							goto doamerge;
					}
				}
			}
			for(c=0;c<r2num;c++)
			{
				if (r2[c].cx>0)
				{
					SmackerMergeInterRect(&r2[c],&tr1,&tr2,&tr3);
					totamt=RectBytes(&tr2);
					wasted=totamt-RectBytes(&r2[c])-rtotal+RectBytes(&tr3);
					if (wasted<bestwast)
					{
						besttot=totamt;
						bestwast=wasted;
						bestmerg=tr2;
						mr=&r2[c];
						if (wasted==0)
							goto doamerge;
					}
				}
			}
			if ((bestwast) && ((besttot/bestwast)<20))
			{
				// more than 5% wasted blitting, so don't merge
				merged[mnum++]=tr1;
				if (bestwast!=0x1000000)
				{
					tr1=*mr;
					mr->cx=-mr->cx;
				}
			}
			else
			{
				doamerge:
				tr1=bestmerg;
				mr->cx=-mr->cx;
			}
			totnum--;
		}
		merged[mnum++]=tr1;
		*onum=mnum;
		for(c=0;c<r1num;c++)
			r1[c].cx=abs(r1[c].cx);
		for(c=0;c<r2num;c++)
			r2[c].cx=abs(r2[c].cx);
	}
}

//========================================================================
//	SmackerBlitRect()
//========================================================================

static void SmackerBlitRect( HWND wh,ULONG x, ULONG y, ULONG w, ULONG h)
{
	DDSURFACEDESC		ddsd;
	LPDIRECTDRAWSURFACE pBuffer;
//	DDSCAPS				caps;
//	ULONG				count;
	RECT				DRect,SRect;

//	DRect.left=rcWindowScreen.left+cp.x + x;		// +(x*ZOOM);
//	DRect.top=rcWindowScreen.top+cp.y + y;			// +(y*ZOOM);
	DRect.left=rcWindowScreen.left + x;				// +(x*ZOOM);
	DRect.top=rcWindowScreen.top + y;				// +(y*ZOOM);
	DRect.right=DRect.left + w;						// +(w*ZOOM);
	DRect.bottom=DRect.top + h;						// +(h*ZOOM);

	SRect.left=x;
	SRect.top=y;
	SRect.right=SRect.left+w;
	SRect.bottom=SRect.top+h;

//	caps.dwCaps=DDSCAPS_BACKBUFFER;

	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize = sizeof(DDSURFACEDESC);

	pBuffer = pSmackerObj->m_pPlaybackBuff;
	while ( pBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT /* DDSCAPS_BACKBUFFER */, NULL) == DDERR_SURFACELOST )
	{
		if (pBuffer->Restore()==DD_OK)
		{
			pBuffer->SetPalette(current_palette.pDDPalette);
			pSmackerObj->BuildPalette( pBuffer );  // reset palette
		}
		else
			return;
	}
  
	//hide if we have a software cursor

	// use BltFast if the blit is one to one, otherwise use Blt
	if ( pSmackerObj->m_bStretching )
	{
//		while(pBuffer->Blt(&DRect,NULL,&SRect,DDBLT_WAIT|DDBLT_ASYNC,0)==DDERR_SURFACELOST)
		if( pBuffer->Blt(&DRect,NULL,&SRect,DDBLT_WAIT|DDBLT_ASYNC,0)==DDERR_SURFACELOST )
		{
			if (pBuffer->Restore()!=DD_OK)
				return;
		}
	}
	else
	{
//		while(pBuffer->BltFast(DRect.left,DRect.top,NULL,&SRect,DDBLTFAST_WAIT)==DDERR_SURFACELOST)
		if( pBuffer->BltFast(DRect.left,DRect.top,NULL,&SRect,DDBLTFAST_WAIT)==DDERR_SURFACELOST )
		{
			if (pBuffer->Restore()!=DD_OK)
				return;
		}
	}
	pBuffer->Unlock(NULL);
}

//========================================================================
//	SmackerCreateBuffer()
//========================================================================

static LPDIRECTDRAWSURFACE SmackerCreateBuffer( int nWidth, int nHeight )
{
	LPDIRECTDRAWSURFACE	pBuffer;

//	pBuffer = CreatePixelSurfaceOfSize( nWidth, nHeight, BM_SYSTEMMEMORY, RGB(0,0,0) );
	pBuffer = CreatePixelSurfaceOfSize( 640, 480, BM_SYSTEMMEMORY, RGB(0,0,0) );
	return pBuffer;
}

//========================================================================
//	SmackerDirtyRects()
//========================================================================

static	void	SmackerDirtyRects( void )
{
 	ULONG			curnum;
	ULONG			rnum;
	BOX*			r;

    // Smacker's dirty rect system is based on the current frame, so
    // we have to do a little extra work to combine the dirty rects from
    // this frame with the dirty rects of the previous frame

	// this loop gets all of the current rectangles
    curnum=0;
    while (SmackToBufferRect(pSmackerObj->m_smk,SMACKSURFACEFAST)) {
      if (pSmackerObj->m_smk->LastRectw) {
        curframe[curnum].x  = pSmackerObj->m_smk->LastRectx;
        curframe[curnum].y  = pSmackerObj->m_smk->LastRecty;
        curframe[curnum].cx = pSmackerObj->m_smk->LastRectw;
        curframe[curnum].cy = pSmackerObj->m_smk->LastRecth;
        curnum++;
      }
    }

    // merge with the last set of rects
    SmackerMergeRects(curframe,curnum,lastframe,lastnum,&r,&rnum);

    // blit the rects
    while (rnum--) 
		SmackerBlitRect(pMainFrame->GetHwnd(),r[rnum].x,r[rnum].y,r[rnum].cx,r[rnum].cy);

    // swap the rect pointers
    r=lastframe;
    lastframe=curframe;
    curframe=r;

    lastnum=curnum;
}

//========================================================================
//								EOF
//========================================================================
