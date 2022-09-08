// Autorun.cpp -- Autoplay teaser runtime source.
// New World Computing's AutoPlay Teaser Toolkit for Windows 95.
// Copyright © 1997 The 3DO Company. All rights reserved.

//////////////////////////////////////////////////////////////////////////////
//
// Header dependencies 
//
#include <windows.h>
#include "commfunc.h"
#include "mainwnd.h"

//////////////////////////////////////////////////////////////////////////////
//
// WinMain -- Program entrance and exit.
//
int WINAPI WinMain( HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER( hinstPrev );
	UNREFERENCED_PARAMETER( lpszCmdLine ); 


	HANDLE mutex;
	
	mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "ArmyMenMutex");
	if (mutex)	// if mutex exists, ArmyMen is running
		return 0;

	//
	// Win32 will always set hinstPrev to NULL, so lets check things a little
	// closer. This is because we only want a single version of this app to
	// run at a time
	//
	HWND hwndMain = NULL;
	hwndMain = FindWindow( MainWnd_GetClassName(), NULL );

//#define MULTIPLE_INSTANCES
#ifndef MULTIPLE_INSTANCES
    if( hwndMain )
    {
        //
        // We found another version of ourself. Lets defer to it:
        //
        if( IsIconic(hwndMain) )
	        ShowWindow( hwndMain, SW_RESTORE );

        SetForegroundWindow( GetLastActivePopup(hwndMain) );	

        return 0;
    }
#endif	
	//
	// Register the window class for the main window and create it.
	//
	if( !MainWnd_RegisterClass( hinst )
	||  !(hwndMain=MainWnd_CreateWindow(hinst,NULL)) )

		//
		// If the main window cannot be created, terminate the application.
		//
		return 0;

	//
	// Center the window, show it and paint its contents.
	//
	CenterWindow( hwndMain, GetDesktopWindow() );
	ShowWindow( hwndMain, nCmdShow );
	UpdateWindow( hwndMain );

	//
	// Start the message loop.
	//
	MSG msg;
	while( GetMessage(&msg,NULL,0,0) )
	{ 
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
	
	//
	// Return the exit code to Windows.
	//
	return msg.wParam;
}

