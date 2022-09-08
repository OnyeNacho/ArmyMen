/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Error.cpp $
//
//	DESCRIPTION:	Error handling and chat messages.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		Wednesday, December 4th, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Error.cpp 44    4/08/98 9:08p Dmaynard $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//=========================================================================
//  HISTORY
//
//  $Log: /ArmyMen/src/Error.cpp $
//  
//  44    4/08/98 9:08p Dmaynard
//  New Flow Control for case when connection is so bad we have run out of
//  message buffers
//  
//  42    4/02/98 3:05p Phu
//  
//  41    4/02/98 12:57p Nrobinso
//  switch to only version number in resources
//  
//  40    3/31/98 6:31p Dmaynard
//  Adjusted mpping from latency to latency-meter color.  now four stage
//  green yelow dark-red  red   <750 <1250 <1750<2250
//  
//  39    3/30/98 1:07p Nrobinso
//  version .93
//  
//  38    3/29/98 10:18p Dmaynard
//  Report Bandwidth statistics after every game instead of at end of
//  session.
//  
//  37    3/29/98 7:06p Dmaynard
//  Better reporting of Bandwidth Measurements.  Highwater mark for send
//  and receive bandwidth, and reporting Bandwidth at the end of each game.
//  
//  36    3/28/98 9:40a Nrobinso
//  version .92
//  
//  35    3/27/98 1:49p Phu
//  survive ALT_TAB dammit
//  
//  34    3/26/98 11:01a Nrobinso
//  version .91
//  
//  33    3/25/98 4:32p Nrobinso
//  add v. to version string
//  
//  32    3/25/98 4:30p Nrobinso
//  put version on screen
//  
//  31    3/24/98 5:45p Nrobinso
//  switch to the untrafficable error only showing up in debug versions
//  
//  30    3/17/98 4:42p Dmaynard
//  Added PAUSE_MAPLOAD instead of piggy-backing on the normal PAUSE_LOCAL
//  flags.
//  
//  29    3/07/98 11:51p Nrobinso
//  make sure latency code compiles for FINAL
//  
//  28    3/02/98 5:50p Dmaynard
//  Moved Latency Display to GameFlow so it is no longer just in Debug
//  Builds. 
//  
//  27    3/02/98 11:15a Dmaynard
//  Visual Fix for latency display
//  
//  26    3/01/98 6:24p Dmaynard
//  Changed Text to be Transparent instead of white background
//  
//  25    2/26/98 6:26p Dmaynard
//  Fixing clearing of dbgDisplay surface and updating of allah mode debug
//  display.
//  
//  24    2/24/98 6:51p Dmaynard
//  Added Latency display in Debug only mode
//  
//  23    2/10/98 2:58p Dmaynard
//  Split Pause flag PAUSE_REMOTEGONE into separate Pause flags for each
//  remote machine.
//  
//  22    2/10/98 9:56a Dmaynard
//  Changed transparent color on CreateSurfaceOfSize from RGB_WHITE to
//  RGB_TRANSPARENT to fox bug where the debug overlay was no longer
//  transparent.
//  
//  21    2/09/98 7:23p Nrobinso
//  remove unused fonts, share debugging fonts
//  
//  20    2/04/98 5:52p Bwilcox
//  suppress debug buffer if bw2
//  
//  19    2/01/98 10:55p Nrobinso
//  put debug text under the DBG_TEXT_ACTIVE compile flag
//  
//  18    1/21/98 10:07a Dmaynard
//  
//  17    1/21/98 9:39a Dmaynard
//  Added additional Trace statements
//  
//  16    1/21/98 8:55a Dmaynard
//  
//  15    1/21/98 8:44a Dmaynard
//  Error Handling and flow control for large latency cases.
//  
//  14    1/16/98 7:30p Dmaynard
//  
//  13    1/16/98 6:26p Dmaynard
//  Error handling if flowq not yet set-up
//  
//  12    1/16/98 5:51p Dmaynard
//  Added Toggle GuaranteedSend from host and communicating this to
//  Clients.
//  
//  11    1/16/98 1:50p Dmaynard
//  Minor positioning tweaks to debug seq pixel display
//  
//  10    1/16/98 1:13p Dmaynard
//  Added DebugDisplay for tracing Comm Flow and Symmetric Protocol Flow.
//  
//  9     1/16/98 9:10a Dmaynard
//  
//  8     1/15/98 5:27p Dmaynard
//  Comm Debug Code
//  
//  7     12/09/97 12:12p Phu
//  
//  6     12/01/97 10:02a Nrobinso
//  FlipToGDI before putting up MessageBox
//  
//  4     8/17/97 6:08p Nrobinso
//  cleanup pause code
//  
//  3     8/06/97 9:41a Nrobinso
//  moved globals.h to stdafx.h
//  
//  2     7/14/97 1:16p Awerner
//  Modified prototype of TextWrite
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  14    5/14/97 1:50p Nrobinso
//  added DEMO flag to turn of debug messages
//  
//  13    5/09/97 2:07p Dmaynard
//  Added B_PAUSEDREMOTEGONE to prevent us from sending msgs when we are
//  not receiving any messages from opposing player.
//  
//  12    5/07/97 2:29p Dmaynard
//  Added Checksum and Sequence numbers to Packed ArmyMsgs
//  
//  11    5/06/97 5:16p Dmaynard
//  
//  10    5/06/97 4:10p Dmaynard
//  Added dbgCommRate display of Bandwidth
//  
//  9     4/29/97 1:41p Nrobinso
//  maintain debugging message colors for different lines
//  
//  8     3/18/97 5:47p Nrobinso
//  changed dbgObjets to take number of objects displayed and total
//  objects; removed setState from Error(), so it is more generally useful
//  
//  7     3/12/97 3:40p Nrobinso
//  add object # debug display
//  
//  6     2/11/97 6:12p Glake
//  Added Frame Rate display in upper left corner [dbgFrameRate()]
//  
//  5     1/15/97 9:48p Nrobinso
//  Add __cdecl to Error()
//  
//  4     97-01-14 9:54 Ereich
//  Next to last version before clean-up is complete.
//  
//  3     97-01-07 16:02 Ereich
//  Cleaning house day 1.  I have made many changes to most of the files
//  and it seems to still work.  So I thought I would check-it in and
//  continue tomorrow.
//  
//  2     96-12-04 13:53 Ereich
//  Moved all of the debugging message output routines from MainFrm.cpp to
//  here.  This included dbgMessage which is used for the chat mode.
//  
//  1     96-12-04 12:39 Ereich
//  Initial seperation of error handling functions from MainFrm.cpp.  This
//  will also have the Chat message support since it will have the overlay
//  buffer handling.
//
//  $Nokeywords:$
//=========================================================================

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"						// required for pre-compiled headers...

#include "MainFrm.h"
#include "text.h"
#include "GameFlow.h"
#include "3donetwork.h"
#include "comm.h"
#include "armymen.h"

// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern TDGLIST sendqueue;
extern char bw2;

/////////////////////////////////////////////////////////////////////////////
//					Local Defines
/////////////////////////////////////////////////////////////////////////////
#define	DBG_SURFACE_HEIGHT	80
#define	DBG_SURFACE_WIDTH	640

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////

 
/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////

#ifdef DBG_TEXT_ACTIVE
///========================================================================
//	Function:		dbgTextFree()
//
//	Description:
//		Release a Debug text surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	dbgTextFree( void )
{
	// if the buffer exists release it
	if ( pDbgBuffer )
	{
		pDbgBuffer->Release();
		pDbgBuffer = NULL;
	}
}


///========================================================================
//	Function:		dbgTextInit()
//
//	Description:
//		Initialize a Debug text surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

#define	DBG_CLEAR_STRING  "                                                                                "
char	pLine1Message[ 132 ];
char	pLine2Message[ 132 ];

BOOL	dbgTextInit( void )
{
	BOOL			error = TRUE;	// assume failure

#ifndef DEMO
	// make sure the buffer is released
	dbgTextFree();

	// create the debug text surface

	if ( pDbgBuffer == NULL)	{
        if (bw2) goto exit;
		pDbgBuffer = CreateSurfaceOfSize( DBG_SURFACE_WIDTH, DBG_SURFACE_HEIGHT,
										  BM_SYSTEMMEMORY, RGB_TRANSPARENT );
		if( pDbgBuffer == NULL )	{
			TRACE( "ERROR: could not create DBG Text Surface\n" );
			goto exit;
		}
	} 

	DDClearSurface( pDbgBuffer, TextTransColor );
	*pLine1Message = '\0';
	*pLine2Message = '\0';
#endif

	// success
	error = FALSE;

#ifndef DEMO
exit:
#endif
	return( error );
}

///========================================================================
//	Function:		dbgClear()
//
//	Description:
//		clear the DBG surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	dbgClear( void )
{
	// clear the dbg line
	if (!pDbgBuffer)
		return;

	DDClearSurface( pDbgBuffer, TextTransColor );
}

///========================================================================
//	Function:		dbgWrite()
//
//	Description:
//		Output a text message to the DBG surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	dbgWrite( char* pMessage )
{
	unsigned	len;

	// clear the dbg line
	if (!pDbgBuffer)
		return;

	DDClearSurface( pDbgBuffer, TextTransColor );
	TextSetColors(  RGB_RED, RGB_TRANSPARENT );
	len = strlen( pMessage );
	strncpy( pLine1Message, pMessage, len+1 );
	TextWrite( pDbgBuffer, 20, 0, pMessage, FONT_TIMES_14, NULL );
	if ( *pLine2Message )
	{
		TextSetColors(  RGB_GREEN, RGB_TRANSPARENT );
		TextWrite( pDbgBuffer, 20, 24, pLine2Message, FONT_TIMES_14, NULL );
	}
}

///========================================================================
//	Function:		dbgMessage()
//
//	Description:
//		Output a text message to the DBG surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	dbgMessage( char* pMessage )
{
	unsigned	len;

	// clear the dbg line
	if (!pDbgBuffer)
		return;

	DDClearSurface( pDbgBuffer, TextTransColor );
	TextSetColors(  RGB_GREEN, RGB_TRANSPARENT );
	len = strlen( pMessage );
	strncpy( pLine2Message, pMessage, len+1 );
	TextWrite( pDbgBuffer, 20, 24, pMessage, FONT_TIMES_14, NULL );
	if ( *pLine1Message )
	{
		TextSetColors(  RGB_RED, RGB_TRANSPARENT );
		TextWrite( pDbgBuffer, 20, 0, pLine1Message, FONT_TIMES_14, NULL );
	}
}

 ///========================================================================
//	Function:		dbgAllah()
//
//	Description:
//		Output the  to the DBG surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================
extern char Allah;
void dbgAllah( ) {

		if (Allah == 1)	dbgWrite("GOD view");
        else if (Allah == 2) dbgWrite("FOE view");
        else if (Allah == 0) dbgWrite("FRND view");
 }

///========================================================================
//	Function:		dbgFrameRate()
//
//	Description:
//		Output the  to the DBG surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void dbgFrameRate (void)
{
	static int Ticks = 0, RateNum = 0;
	static int Rates[5] = {18, 18, 18, 18, 18};
	int TickCurrent;
	int Tmp;
	char TickStr[] = "00";
	RECT	rcRect = {0, 0, 18, 18};
	DDBLTFX	ddbltfx;

	if (!pDbgBuffer)
		return;

	/* Read internal clock in milliseconds. */
	TickCurrent = GetTickCount();
	
	/* Don't want to divide by zero or end up with a frame rate
	   that is negative or greater than 100. */
	if ((Tmp = TickCurrent - Ticks) < 11)
		return;

	Ticks = TickCurrent;

	Rates[RateNum] = Tmp;
    if (++RateNum > 4)
		RateNum = 0;

	/* Average over the past five frames to stabalize just a little bit. */
	Tmp = Rates[0] + Rates[1] + Rates[2] + Rates[3] + Rates[4];
	itoa ((5000 / Tmp), TickStr, 10);

	TextSetColors (RGB_GREEN, RGB_TRANSPARENT);

	/* Erase the previous Frame Rate display. */ 
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = TextTransColor;
	if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt clear the old Frame Rate\n");

	TextWrite (pDbgBuffer, 0, 0, TickStr, FONT_TIMES_14, NULL);
}

static BYTE dbcommcolortable1 [5] = { DK_GREEN_IDX, BROWN_IDX, DK_BLUE_IDX, DK_GREY_IDX, RED_IDX} ;

static BYTE dbcommcolortable2 [5] = { GREEN_IDX, YELLOW_IDX, BLUE_IDX, GREY_IDX, RED_IDX} ;

///========================================================================
//	Function:		dbgCommRate()
//
//	Description:
//		Output the Comm Statistics to the DBG surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void dbgCommRate (void)
{
	RECT	rcRect = {200, 0, 500, 28};
	DDBLTFX	ddbltfx;
	DWORD	sendbw;
	DWORD	receivebw;
	static int modframe = 0;
	int barh=4,barw;
	if( !gpComm->m_pDPlay) return;

	if (!pDbgBuffer)
		return;
    if (!gpComm->debugDisplayComm ) return;
//	if (((modframe++) % 5) == 0)
//	 TRACE("SBW %d RBW %d SPR %d RPR %d \n", gpComm->GetSendBW(),
//		gpComm->GetReceiveBW(),  gpComm->GetSendPR(), gpComm->GetReceivePR());
	/* Erase the previous Comm Rate display. */ 
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = TextTransColor;
	if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt clear the old Frame Rate\n");

	sendbw = gpComm->GetSendBW();
	ddbltfx.dwFillColor = (sendbw > DESIGNSENDBW) ?  RED_IDX : 
				(sendbw > 3*DESIGNSENDBW/4) ? 	YELLOW_IDX : DK_GREEN_IDX;
	barw = (sendbw)*440/DESIGNSENDBW; // percent of 28.8 modem bandwidth
	rcRect.bottom = rcRect.top+barh;
	rcRect.right = rcRect.left+barw;
	if( rcRect.right > 639) rcRect.right = 639;
	if (barw) if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt SendBW\n");

	// Draw high water mark;
	ddbltfx.dwFillColor =  (gpComm->m_SendBWHWM > DESIGNSENDBW) ?  RED_IDX : 
				(gpComm->m_SendBWHWM > 3*DESIGNSENDBW/4) ? 	YELLOW_IDX : DK_GREEN_IDX;

	rcRect.left = 200 + (gpComm->m_SendBWHWM*440/DESIGNSENDBW);
	if (rcRect.left >= 637) rcRect.left = 637; 
	rcRect.right = rcRect.left+2;
	if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt SendBWHWM\n");
	rcRect.left = 200;
	rcRect.top +=barh;
	rcRect.top +=barh;

	receivebw = gpComm->GetReceiveBW();
	ddbltfx.dwFillColor = (receivebw > DESIGNRECEIVEBW) ?  RED_IDX : ddbltfx.dwFillColor;
	ddbltfx.dwFillColor = (receivebw > DESIGNSENDBW) ?  RED_IDX : 
				(receivebw > 3*DESIGNSENDBW/4) ? 	YELLOW_IDX : DK_BLUE_IDX;
	if (gpComm->m_CommErrorCnt[1]) ddbltfx.dwFillColor = RED_IDX;
	barw = (receivebw)*440/DESIGNRECEIVEBW; // percent of 28.8  bandwidth
	rcRect.bottom = rcRect.top+barh;
	rcRect.right = rcRect.left+barw;
	if( rcRect.right > 639) rcRect.right = 639;
	if (barw) if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt ReceiveBW\n");

	
	// Draw high water mark;
	ddbltfx.dwFillColor =  (gpComm->m_ReceiveBWHWM > DESIGNSENDBW) ?  RED_IDX : 
				(gpComm->m_ReceiveBWHWM > 3*DESIGNSENDBW/4) ? 	YELLOW_IDX : DK_GREEN_IDX;

	rcRect.left = 200 + (gpComm->m_ReceiveBWHWM*440/DESIGNRECEIVEBW);
	if (rcRect.left >= 637) rcRect.left = 637; 
	rcRect.right = rcRect.left+2;
	if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt ReceiveBWHWM\n");
	rcRect.left = 200;
	rcRect.top +=barh;
	rcRect.top +=barh;
	rcRect.top +=barh;
	rcRect.top +=barh;

	ddbltfx.dwFillColor = DK_GREEN_IDX;
	barw = (gpComm->GetSendPR()*300)/60;  // percent of 60Hz
	rcRect.bottom = rcRect.top+barh;
	rcRect.right = rcRect.left+barw;
	if( rcRect.right > 500) rcRect.right = 500;
	if (barw) if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt SendPR\n");
	rcRect.top +=barh;
	rcRect.top +=barh;

	ddbltfx.dwFillColor = (gpComm->m_CommErrorCnt[1]? RED_IDX :DK_BLUE_IDX);
	barw = (gpComm->GetReceivePR()*300)/60;
	if (barw < 0 ) barw = 0;
	if (gpGame->IsPaused() & (PAUSE_REMOTEGONE1))  {
		barw = 100;
		ddbltfx.dwFillColor = dbcommcolortable2[gpComm->m_ArmyIndex[1]];
	}
	if (gpGame->IsPaused() & (PAUSE_REMOTEGONE2))  {
		barw = 100;
		ddbltfx.dwFillColor = dbcommcolortable2[gpComm->m_ArmyIndex[2]];
	}
	if (gpGame->IsPaused() & (PAUSE_REMOTEGONE3))  {
		barw = 100;
		ddbltfx.dwFillColor = dbcommcolortable2[gpComm->m_ArmyIndex[3]];
	}
	if (gpGame->IsPaused() & PAUSE_FLOW)  {
		barw = 100;
		ddbltfx.dwFillColor = CYAN_IDX;
	}
	rcRect.bottom = rcRect.top+barh;
	rcRect.right = rcRect.left+barw;
	if( rcRect.right > 500) rcRect.right = 500;
	if (barw) if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt ReceivePR\n");
	if (gpComm->debugDisplayComm < 2) return;
	rcRect.top +=barh;
 	rcRect.top +=barh;
	ddbltfx.dwFillColor = DK_GREY_IDX;
	barw	= ListSize(&sendqueue);
	rcRect.right = rcRect.left+barw;
	rcRect.bottom = rcRect.top+barh;
	if( rcRect.right > 639) rcRect.right = 39;
	if (barw) if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt ReceivePR\n");

}

static void	DrawCommStrip( int ystart, BYTE color, DWORD *data) {
	RECT	rcRect = {0, 0, 0, 0};
	DDBLTFX	ddbltfx;
	DWORD val;
	int i;
	int barh=4,barw=4;
	rcRect.top = ystart;
	rcRect.left = 0;
	rcRect.bottom = rcRect.top+barh;
	ddbltfx.dwSize = sizeof(ddbltfx);
	for (i=0;i<NSEQPIXELS;i++ ) {
		val = data[i];
		if (val) {
			ddbltfx.dwFillColor = ((val > 1) ? RED_IDX : color);
			rcRect.right = rcRect.left+barw;
		if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
			TRACE("Couldn't Blt Seq Pixels\n");
		}
		
		rcRect.left +=barw;
	}
}

///========================================================================
//	Function:		dbgVersion()
//
//	Description:
//		Output the version # to the DBG surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void dbgVersion ()
{
	char version[] = "0000000000";
	RECT	rcRect = {550, 0, 600, 18};
	DDBLTFX	ddbltfx;

	if (!pDbgBuffer)
		return;

	TextSetColors (RGB_YELLOW, RGB_TRANSPARENT);

	sprintf(version,"v. %d.%d",theApp.appVersion.major,theApp.appVersion.minor);

	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = TextTransColor;
	if ((pDbgBuffer->Blt (&rcRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
		TRACE("Couldn't Blt clear the old object text\n");

	TextWrite (pDbgBuffer, 550, 0, version, FONT_TIMES_14, NULL);
}


///========================================================================
//	Function:		DisplayDBG()
//
//	Description:
//		Terminate a Debug text surface.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

extern /* temp */void	DisplayDBG( void )
{
	HRESULT		ddrval;
	RECT		rcRect;

	if (!pDbgBuffer)
		return;

	// display debug string surface
	rcRect.left   = 0;
	rcRect.top    = 0;
	rcRect.right  = DBG_SURFACE_WIDTH;
	rcRect.bottom = DBG_SURFACE_HEIGHT;
	ddrval = pBackBuffer->BltFast(0, 0,
								 pDbgBuffer, &rcRect,
								 DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	if (ddrval != DD_OK)
	{
		return;
//		DDFail("BltFast() failure for DBG text buffer", ddrval);
	}
}


///========================================================================
//	Function:		dbgTextExit()
//
//	Description:
//		Final terminatation of Debug text
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	dbgTextExit( void )
{
	dbgTextFree();
	*pLine1Message = '\0';
	*pLine2Message = '\0';
}
#endif


///========================================================================
//	Function:		Error()
//
//	Description:
//		Print an Error Message
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

char ErrorString[256];

void	__cdecl Error (char *format, ...)
{
    va_list arglist;
    int rc = 0;

	/* build the message string for output		*/
	va_start( arglist, format);
	rc = vsprintf( ErrorString, format, arglist );
	va_end( arglist );
	TRACE( ErrorString );
	pDirectDraw->FlipToGDISurface();
	MessageBox( pMainFrame->m_hWnd, ErrorString, "Error", MB_OK );
}

void	__cdecl ErrorDebug (char *format, ...)
{

#ifdef _DEBUG
    va_list arglist;
    int rc = 0;

	/* build the message string for output		*/
	va_start( arglist, format);
	rc = vsprintf( ErrorString, format, arglist );
	va_end( arglist );
	TRACE( ErrorString );
	pDirectDraw->FlipToGDISurface();
	MessageBox( pMainFrame->m_hWnd, ErrorString, "Error", MB_OK );
#endif
}

static RECT Snake [NSEQPIXELS];
static  BOOL SnakeInit = FALSE;

static void InitSnake (void) {
	int i,index;
	int largedim =4;
	int smalldim =2;
	int width = 60;
	int height = 52;
	int nhoriz,nvert;
	nhoriz = (width+largedim)/smalldim;
	nvert = (height+largedim)/smalldim;
	Snake[0].left = -largedim;
	Snake[0].top = -largedim;
	Snake[0].right = Snake[0].left+smalldim;
	Snake[0].bottom = 0;
	index = 1;
	for( i=1;i<nhoriz;i++,index++ )	{
		Snake[index].left = Snake[index-1].left+smalldim;
		Snake[index].right = Snake[index].left+smalldim;
		Snake[index].top = Snake[index-1].top;
		Snake[index].bottom = Snake[index].top+largedim;
	}
	Snake[index].left =Snake[index-1].left+smalldim;
	Snake[index].right = Snake[index].left+largedim;
	Snake[index].top =Snake[index-1].top;
	Snake[index].bottom =Snake[index].top+smalldim;
	index++;
	for( i=1;i<nvert;i++ ,index++)	{
		Snake[index].left = Snake[index-1].left;
		Snake[index].right = Snake[index].left+largedim;
		Snake[index].top = Snake[index-1].top+smalldim;
		Snake[index].bottom = Snake[index].top+smalldim;
	}
	Snake[index].left =Snake[index-1].right-smalldim;
	Snake[index].right = Snake[index].left+smalldim;
	Snake[index].top =Snake[index-1].top+smalldim;
	Snake[index].bottom =Snake[index].top+largedim;
	index++;
  	for( i=1;i<nhoriz;i++,index++ )	{
		Snake[index].left = Snake[index-1].left-smalldim;
		Snake[index].right = Snake[index].left+smalldim;
		Snake[index].top = Snake[index-1].top;
		Snake[index].bottom = Snake[index].top+largedim;
	}
	Snake[index].left =Snake[index-1].left-largedim;
	Snake[index].right = Snake[index].left+largedim;
	Snake[index].top =Snake[index-1].top+largedim-smalldim;
	Snake[index].bottom =Snake[index].top+smalldim;
	index++;
 	for( i=1;i<nvert;i++,index++ )	{
		Snake[index].left = Snake[index-1].left;
		Snake[index].right = Snake[index].left+largedim;
		Snake[index].top = Snake[index-1].top-smalldim;
		Snake[index].bottom = Snake[index].top+smalldim;
	}
	TRACE("Snake [%d] Entries \n", index);
	SnakeInit = TRUE;
}

static void DrawSnake (int xstart, int ystart, BYTE color, DWORD *data ) {
	RECT	rcRect = {0, 0, 0, 0};
	DDBLTFX	ddbltfx;
	DWORD val;
	int i;
	int barh=2,barw=2;
	if (!SnakeInit) InitSnake();
	rcRect.top = ystart;
	rcRect.left = 0;
	rcRect.bottom = rcRect.top+barh;
	ddbltfx.dwSize = sizeof(ddbltfx);
	for (i=0;i<NSEQPIXELS;i++ ) {
		val = data[i];
		if (val) {
			rcRect.top = ystart+Snake[i].top;
			rcRect.left = xstart+Snake[i].left;
			rcRect.bottom = ystart+Snake[i].bottom;
			rcRect.right = xstart+Snake[i].right;
			ddbltfx.dwFillColor = ((val > 1) ? RED_IDX : color);
			if ((pBackBuffer->Blt (&rcRect, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx)) != DD_OK)
				TRACE("Couldn't Blt Seq Pixels\n");
		}
		
	}
}

extern SPOINT fragPos[];
static BYTE dbcommcolorlatency [4] = { GREEN_IDX, YELLOW_IDX,  DK_RED_IDX, RED_IDX} ;

void DrawLatencyDisplay (void) {
	LPFLOWQ lpflow;
	BYTE color;
	int i,colorindex,aveLatency;
	int x,y;
	if( !gpComm->m_pDPlay) return;
	for (i = 1; i < (int)gpComm->m_NumDPPlayers; i++ ) {
		if( gpComm->m_PlayerId[i] == 0xFFFFFFFF) continue;
		lpflow = FindFlowQ(gpComm->m_PlayerId[i]);
		if( !lpflow ) return;
		colorindex = 0;
		aveLatency=AveLatency(lpflow);
		if( aveLatency > 750 ) colorindex = 1;
		if(	aveLatency > 1250 ) colorindex = 2;
		if(	aveLatency > 1750 ) colorindex = 3;

	    color = dbcommcolorlatency[colorindex];			
		x = fragPos[i].x;
		y = fragPos[i].y;
		DrawSnake(x,y, color, lpflow->SendHistory);
	}
}

//=========================================================================
//								EOF
//=========================================================================
