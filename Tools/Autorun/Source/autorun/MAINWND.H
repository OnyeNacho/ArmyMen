#ifndef __MAINWND_H
#define __MAINWND_H

BOOL MainWnd_RegisterClass( HINSTANCE hinst );
HWND MainWnd_CreateWindow( HINSTANCE hinst, HWND hwndParent );
const char * MainWnd_GetClassName( void );

#endif//__MAINWND_H

