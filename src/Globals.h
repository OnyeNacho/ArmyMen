//========================================================================
//	FILE:			$Workfile: Globals.h $
//
//	DESCRIPTION:	Global variables.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, June 18, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Globals.h 12    4/02/98 7:36p Nrobinso $
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
//  $Log: /ArmyMen/src/Globals.h $
//  
//  12    4/02/98 7:36p Nrobinso
//  dd surface 3
//  
//  11    3/11/98 3:21p Aburgess
//  modifications made to correct Disabled button colors
//  
//  10    3/09/98 3:34p Aburgess
//  new RGB color references
//  
//  9     3/07/98 11:54p Nrobinso
//  move .h file to stdafx
//  
//  8     2/09/98 1:54p Aburgess
//  modifications made to support IN GAME screens, Cursor control, and
//  Rules presentation
//  
//  7     12/09/97 12:12p Phu
//  
//  6     10/30/97 10:18a Nrobinso
//  change fixed frame rate to 30 from 20
//  
//  5     10/13/97 10:01a Aburgess
//  added CYAN and DK_CYAN RGB color definitions
//  
//  3     7/17/97 10:11p Nrobinso
//  move DASH_HEIGHT to globals.h; add MAX_FRAME_TIME
//  
//  2     7/15/97 7:54p Nrobinso
//  added FRAME_TIME
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  37    5/06/97 10:04p Nrobinso
//  fix RGB_BLACK
//  
//  36    4/02/97 3:34p Aburgess
//  added debug variable
//  
//  35    4/01/97 9:07p Nrobinso
//  add rcGameWindow
//  
//  34    2/25/97 4:18p Nrobinso
//  change rcWindow to rcWindowScreen, remove rcBackSurface
//  
//  33    1/21/97 6:45p Nrobinso
//  removed MainFrm.h
//  
//  32    97-01-14 9:54 Ereich
//  Next to last version before clean-up is complete.
//  
//  31    97-01-10 16:34 Ereich
//  A good check-in point for code clean-up...
//  
//  30    97-01-07 16:02 Ereich
//  Cleaning house day 1.  I have made many changes to most of the files
//  and it seems to still work.  So I thought I would check-it in and
//  continue tomorrow.
//  
//  29    1/07/97 1:46p Aburgess
//  added Yellow and Brown RGB colors
//  
//  28    12/16/96 6:36a Aburgess
//  new RGB colors added for AI debugging
//  
//  27    12/11/96 10:51a Aburgess
//  new RGB globals
//  
//  26    12/10/96 5:33p Nrobinso
//  Added a BOX DisplayBox; that tracks what area of the world is displayed
//  on the screen
//  
//  25    12/06/96 3:40p Aburgess
//  added color indecies
//  
//  24    12/05/96 1:57p Aburgess
//  added GetArmyIndex extern reference
//  
//  23    96-12-04 13:50 Ereich
//  Changes were made to this file to aid in the organizational changes
//  made to MainFrm.cpp.
//  
//  22    12/02/96 10:44a Aburgess
//  new game states
//  
//  21    11/11/96 5:56p Aburgess
//  added extern references to dbgClear() and dbgMessage()
//  
//  20    9/17/96 5:16p Nrobinso
//  add dwAnimTime and GraphicsFree/Load
//  
//  19    9/10/96 1:00p Aburgess
//  move commonly used but infrequently changed header files to stdafx.h
//  (precompiled header)
//  
//  18    9/09/96 8:23p Aburgess
//  made theApp static
//  
//  17    9/03/96 2:48p Aburgess
//  Added TileBuffer
//  
//  16    8/15/96 4:39a Aburgess
//  added a new state
//  
//  15    8/14/96 7:55p Nrobins
//  mae gamebpp & palette loading global
//  
//  14    7/31/96 10:36a Aburgess
//  redefinted global RGB_xxxxx color references
//  
//  13    7/26/96 9:28p Nrobins
//  Removed dbg init & exit calls from globals
//  
//  12    7/25/96 4:08p Aburgess
//  converted MAPROOM state to MAINBASE state.
// 
// 10    6/25/96 9:53p Nrobins
// added history info
// 
//  $Nokeywords:$
//=========================================================================

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//#include "resource.h"       // main symbols
//#include "Dd.h"

#ifdef _DEBUG
#define ODS( a ) OutputDebugString( a )
#else
#define ODS( a )
#endif

//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================

#define MAX_LEVELS	1

#define MAX_PLAYERS	4


// some RGB color values
//#define	RGB_TRANSPARENT		RGB(255,255,255)
#define	RGB_TRANSPARENT		RGB(0,0,0)
#define	RGB_BLACK			RGB(0,0,0)
#define RGB_NEAR_BLACK		RGB(8,8,8)
#define	RGB_GRAY			RGB(127,127,127)
#define	RGB_RED				RGB(255,0,0)
#define	RGB_GREEN			RGB(0,255,0)
#define	RGB_BLUE			RGB(0,0,255)
#define	RGB_CYAN			RGB(0,96,136)
#define	RGB_DK_GRAY			RGB(72,72,72)
#define	RGB_LT_GRAY			RGB(203,203,203)
#define	RGB_DK_RED			RGB(127,0,0)
#define	RGB_DK_GREEN		RGB(40,53,38)
#define	RGB_DK_BLUE			RGB(19,35,59)
#define	RGB_DK_CYAN			RGB(0,64,96)
#define	RGB_DK_MAGENTA		RGB(64,0,64)
#define	RGB_MAGENTA			RGB(127,0,127)
#define	RGB_LT_MAGENTA		RGB(191,0,191)
#define	RGB_WHITE			RGB(255,255,255)
#define	RGB_YELLOW			RGB(242,255,20)
#define	RGB_BROWN			RGB(121,128,10)
#define	RGB_LT_GREEN		RGB(111,133,103)
#define	RGB_LT_TAN			RGB(210,188,157)
#define	RGB_LT_BLUE			RGB(79,135,195)
#define	RGB_DK_TAN			RGB(73,58,37)

// fixed color indecies
#define	BLACK_IDX			0
#define	DK_RED_IDX			1
#define	DK_GREEN_IDX		2
#define	BROWN_IDX			3
#define	DK_BLUE_IDX			4
#define	DK_MAGENTA_IDX		5
#define	DK_CYAN_IDX			6
#define	GREY_IDX			7
#define	DK_GREY_IDX			248
#define	RED_IDX				249
#define	GREEN_IDX			250
#define	YELLOW_IDX			251
#define	BLUE_IDX			252
#define	MAGENTA_IDX			253
#define	CYAN_IDX			254
#define	WHITE_IDX			255

#define	FRAME_TIME	33
#define	MAX_FRAME_TIME	66

//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================

//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================

extern	LPDIRECTDRAW			pDirectDraw;	// the DirectDraw object from which everything flows
extern	LPDIRECTDRAWSURFACE		pFrontBuffer;	// the front screen buffer
extern	LPDIRECTDRAWSURFACE		pBackBuffer;	// the off screen buffer
extern	LPDIRECTDRAWSURFACE3	pBackBufferPL;	// the off screen buffer (same as back buffer, but used for PageLock)
extern	LPDIRECTDRAWSURFACE		pDbgBuffer;		// the debug info buffer
	
extern	RECT					rcWindowScreen;	// Rectangle of window in screen coordinates
extern	RECT					rcBackWindow;	// Rectangle of back window in window coordinates
extern	RECT					rcGameWindow;	// Rectangle of back window in use in window coordinates
extern	RECT					rcWindow;		// Rectangle of window in window coordinates


extern	BOOL					DBGflag;		// runtime changeable Debug flag

//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================


#endif		// __GLOBAL_H__

//=========================================================================
//								EOF
//=========================================================================
