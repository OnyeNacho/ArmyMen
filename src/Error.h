//========================================================================
//	FILE:			$Workfile: Error.h $
//
//	DESCRIPTION:	Error header file.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		Wednesday, December 4th, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Error.h 10    3/25/98 4:30p Nrobinso $
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
//  $Log: /ArmyMen/src/Error.h $
//  
//  10    3/25/98 4:30p Nrobinso
//  put version on screen
//  
//  9     3/24/98 5:45p Nrobinso
//  switch to the untrafficable error only showing up in debug versions
//  
//  8     3/07/98 11:54p Nrobinso
//  move .h file to stdafx
//  
//  7     3/02/98 5:50p Dmaynard
//  Moved Latency Display to GameFlow so it is no longer just in Debug
//  Builds. 
//  
//  6     2/26/98 6:26p Dmaynard
//  Fixing clearing of dbgDisplay surface and updating of allah mode debug
//  display.
//  
//  5     2/01/98 10:55p Nrobinso
//  put debug text under the DBG_TEXT_ACTIVE compile flag
//  
//  4     1/16/98 1:13p Dmaynard
//  Added DebugDisplay for tracing Comm Flow and Symmetric Protocol Flow.
//  
//  3     12/09/97 12:12p Phu
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  7     5/06/97 4:10p Dmaynard
//  Added dbgCommRate display of Bandwidth
//  
//  6     3/18/97 5:46p Nrobinso
//  changed dbgObjects to take 2 numbers: objects displayed and total
//  objects
//  
//  5     3/12/97 3:40p Nrobinso
//  add object # debug display
//  
//  4     2/11/97 6:12p Glake
//  Added Frame Rate display in upper left corner [dbgFrameRate()]
//  
//  3     1/15/97 9:48p Nrobinso
//  Add __cdecl to Error()
//  
//  2     97-01-07 16:02 Ereich
//  Cleaning house day 1.  I have made many changes to most of the files
//  and it seems to still work.  So I thought I would check-it in and
//  continue tomorrow.
//  
//  1     96-12-04 13:52 Ereich
//  Added to reflect organizational changes in MainFrm.cpp.
//  
//  $Nokeywords:$
//=========================================================================

#ifndef __ERROR_H__
#define __ERROR_H__

#ifdef _DEBUG
#define ODS( a ) OutputDebugString( a )
#else
#define ODS( a )
#endif

//=========================================================================
//						GLOBAL DEFINES
//=========================================================================


//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================


//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================


//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================

#ifdef FINAL
	#define DisplayDBG()
	#define dbgTextInit()
	#define dbgTextFree()
	#define dbgTextExit()
	#define dbgClear()
	#define dbgWrite( pMessage )
	#define dbgMessage( pMessage )
	#define dbgFrameRate()
	#define dbgCommRate()
	#define dbgVersion(num, total)
#else
	#ifdef DEMO
		#define DisplayDBG()
		#define dbgTextInit()
		#define dbgTextFree()
		#define dbgTextExit()
		#define dbgClear()
		#define dbgWrite( pMessage )
		#define dbgMessage( pMessage )
		#define dbgFrameRate()
		#define dbgCommRate()
		#define dbgVersion()
	#else
		#define DBG_TEXT_ACTIVE
		extern void		DisplayDBG( void );
		extern BOOL		dbgTextInit( void );
		extern void		dbgTextFree( void );
		extern void		dbgTextExit( void );
		extern	void	dbgClear( void );
		extern	void	dbgWrite( char* pMessage );
		extern	void	dbgMessage( char* pMessage );
		extern  void    dbgFrameRate (void);
		extern  void    dbgCommRate (void);
		extern  void    dbgVersion();
		extern void     dbgAllah(void);
	#endif
#endif


extern	void DrawLatencyDisplay(void);
extern	void __cdecl Error(char *format, ...);
extern	void __cdecl ErrorDebug(char *format, ...);

#endif		// __ERROR_H__
//=========================================================================
//								EOF
//=========================================================================
