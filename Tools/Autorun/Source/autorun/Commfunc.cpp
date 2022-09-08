// File: Commfunc.cpp - Common functions
// New World Computing's AutoPlay Teaser Toolkit for Windows 95.
// Copyright © 1997 The 3DO Company. All rights reserved.

//////////////////////////////////////////////////////////////////////////////
//
// Header dependencies
//
#include <windows.h>
#include "commfunc.h"

//////////////////////////////////////////////////////////////////////////////
//
// CenterWindow -- Center a window over another. Make sure it is within the
// display limits of the screen and not obscured by the tray or other elements
// of the desktop. If it succeeds, the return value is TRUE. If it fails, the
// return value is FALSE.
//
BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
	RECT rChild, rParent, rWorkArea = {0,0,0,0};
	int wChild, hChild, wParent, hParent;
	int wScreen, hScreen, xScreen, yScreen, xNew, yNew;
	BOOL bResult;

	//
	// Get the Height and Width of the child window
	//
	GetWindowRect (hwndChild, &rChild);
	wChild = rChild.right - rChild.left;
	hChild = rChild.bottom - rChild.top;

	//
	// Get the Height and Width of the parent window
	//
	GetWindowRect (hwndParent, &rParent);
	wParent = rParent.right - rParent.left;
	hParent = rParent.bottom - rParent.top;

	//
	// Get the limits of the 'workarea'
	//
#if !defined(SPI_GETWORKAREA)
#define SPI_GETWORKAREA 48
#endif
	bResult = SystemParametersInfo( SPI_GETWORKAREA, sizeof(RECT), &rWorkArea, 0 );	

	wScreen = rWorkArea.right - rWorkArea.left;
	hScreen = rWorkArea.bottom - rWorkArea.top;
	xScreen = rWorkArea.left;
	yScreen = rWorkArea.top;

	//
	// On Windows NT, the above metrics aren't valid (yet), so they all return
	// '0'. Lets deal with that situation properly:
	//
	if( wScreen==0 && hScreen==0 )
	{
		wScreen = GetSystemMetrics(SM_CXSCREEN);
		hScreen = GetSystemMetrics(SM_CYSCREEN);
		xScreen = 0; // These values should already be '0', but just in case
		yScreen = 0;
	}

	//
	// Calculate new X position, then adjust for screen
	//
	xNew = rParent.left + ((wParent - wChild) /2);
	if( xNew < xScreen )
	{
		xNew = xScreen;
	}
	else if( (xNew+wChild) > wScreen )
	{
		xNew = (xScreen + wScreen) - wChild;
	}

	//
	// Calculate new Y position, then adjust for screen
	//
	yNew = rParent.top  + ((hParent - hChild) /2);
	if( yNew < yScreen )
	{
		yNew = yScreen;
	}
	else if( (yNew+hChild) > hScreen )
	{
		yNew = (yScreen + hScreen) - hChild;
	}

	//
	// Set it, and return.
	//
	return SetWindowPos( hwndChild, NULL, xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
}

//////////////////////////////////////////////////////////////////////////////
//
// GetString -- Gets a resource string. Be careful because this function 
// returns a pointer to a static string that is rewritten each time the 
// function is called.
//
char * GetString( HINSTANCE hinst, int idString )
{             		   
	static char szBuf[ 512 ];

	szBuf[0] = '\0';
	LoadString( hinst, idString, szBuf, sizeof(szBuf) );

	return szBuf;
}

