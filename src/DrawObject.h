//========================================================================
//	FILE:			$Workfile: DrawObject.h $
//
//	DESCRIPTION:	Draw object header.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		Friday, January 10, 1996
//
//	REVISION:		$Header: /ArmyMen/src/DrawObject.h 4     12/09/97 12:12p Phu $
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
//  $Log: /ArmyMen/src/DrawObject.h $
//  
//  4     12/09/97 12:12p Phu
//  
//  3     11/03/97 9:00a Nrobinso
//  add contructor and deconstructor to object definition
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  3     5/02/97 4:29p Nrobinso
//  add DrawObject::Init() to initialize the fullscreen boolean
//  
//  2     97-01-16 10:21 Ereich
//  Finally got the new state machine working.  Subtleties in the
//  transition from the old state to the new cost me many hours.
//  
//  1     97-01-14 9:26 Ereich
//  
//  $Nokeywords:$
//=========================================================================

#ifndef __DRAWOBJECT_H__
#define __DRAWOBJECT_H__

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

class CDrawObject {
	// private member variables
private:
	// protected member variables
protected:
	// public member variables
public:
	BOOL bFullscreen;		// full screen display flag

	// private methods
private:
	// protected methods
protected:
	// public methods
public:
	CDrawObject();
	~CDrawObject();

	BOOL ReadyForDraw();
	void PageFlip();
	void Init(BOOL fullscreen);


};

//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================
extern	CDrawObject gDO, *gpDO;		// global draw object

//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================



#endif		// __DRAWOBJECT_H__
//=========================================================================
//								EOF
//=========================================================================
