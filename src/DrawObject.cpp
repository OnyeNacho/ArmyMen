/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: DrawObject.cpp $
//
//	DESCRIPTION:	.CPP source file template.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		day, Month ##, 1996
//
//	REVISION:		$Header: /ArmyMen/src/DrawObject.cpp 8     4/02/98 2:24p Phu $
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
//  $Log: /ArmyMen/src/DrawObject.cpp $
//  
//  8     4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  7     3/27/98 1:49p Phu
//  survive ALT_TAB dammit
//  
//  6     3/09/98 3:16p Phu
//  fix screen flash, vehicle sizes
//  
//  5     12/09/97 12:12p Phu
//  
//  4     10/07/97 8:03a Aburgess
//  added capability of pausing page flipping without pausing everything
//  else in the game (PausePageFlip)
//  
//  2     7/28/97 2:20p Awerner
//  Removed necessity for dash.cpp
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  6     5/08/97 12:22p Bwilcox
//  page flip change for dash
//  
//  5     5/08/97 11:48a Nrobinso
//  add sample code for copying dashboard in full screen mode
//  
//  4     5/02/97 4:29p Nrobinso
//  add DrawObject::Init() to initialize the fullscreen boolean
//  
//  3     2/25/97 4:16p Nrobinso
//  change rcWindow to rcWindowScreen
//  
//  2     97-01-10 16:34 Ereich
//  A good check-in point for code clean-up...
//  
//  1     97-01-10 15:30 Ereich
//  Initial version of DrawObject
//
//  $Nokeywords:$
//=========================================================================

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"						// required for pre-compiled headers...

#include "DrawObject.h"
#include "Dd.h"
#include "Armymen.h"
#include "MainFrm.h"


// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
CDrawObject gDO, *gpDO=&gDO;		// global draw object
/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Class construction/destruction


// Default constructor
CDrawObject::CDrawObject() {
	// TODO: is there anything to do here...
//	bFullscreen = FALSE;		// default to windowed
}

// destructor
CDrawObject::~CDrawObject() {
	// TODO: is there anything to do here...
}

void CDrawObject::Init(BOOL fullscreen) {
	bFullscreen = fullscreen;
}

/////////////////////////////////////////////////////////////////////////////
// Public Methods

BOOL CDrawObject::ReadyForDraw() {
	HRESULT       ddrval;

	if (!bFullscreen)	{
		ddrval = pBackBufferPL->PageLock(0);
		if (ddrval == DDERR_SURFACELOST)
			if (DD_OK != pBackBuffer->Restore())	{
				return DDFail("Couldn't restore back surface", ddrval);

			if (!EraseSurfaces())
				return DDFail("Couldn't erase the surfaces", ddrval);

			TRACE("Had to Erase Surfaces\n");

			// And try again
			ddrval = pBackBufferPL->PageLock(0);
		}

		if (ddrval != DD_OK)
			return DDFail("Couldn't page lock offscreen surface", ddrval);
	}

	return TRUE;
}


void CDrawObject::PageFlip() {
	HRESULT       ddrval;

	if ( pMainFrame->bPausePageFlip )
		return;
	if (bFullscreen)
	{
		// Flip the surfaces
		do
		{
			ddrval = pFrontBuffer->Flip(NULL, 0);
			if (ddrval != DD_OK)	
			{
				if (ddrval == DDERR_SURFACELOST)	
				{
					ddrval = pFrontBuffer->Restore();
					if (ddrval != DD_OK)
						return;
//						DDFail("Restore() failure for primary surface", ddrval);
				}
				else
				{
					MSG msg;

					if( ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
					{
						if (!theApp.PumpMessage())
						{
							::PostQuitMessage(msg.wParam);
							break;
						}
					}
				}
			}
			else
				break;
		} while( TRUE );

	}
	else	{
		// then copy the whole surface forward
		ddrval = pFrontBuffer->Blt(
			&rcWindowScreen,	// dest rect
			pBackBuffer,		// src surface
			&rcBackWindow,		// src rect
			DDBLT_WAIT,
			NULL);

		if (ddrval != DD_OK)
			DDFail("Blt() failure of back buffer to front buffer", ddrval);

		// Unlock the offscreen surface
		ddrval = pBackBufferPL->PageUnlock(0);
		if (ddrval != DD_OK)	{
			DDFail("PageUnlock() failure for back buffer", ddrval);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// Protected Methods


/////////////////////////////////////////////////////////////////////////////
// Private Methods


//=========================================================================
//								EOF
//=========================================================================
