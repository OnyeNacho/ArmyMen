// Mainwnd.cpp -- Autoplay teaser runtime main window.
// New World Computing's AutoPlay Teaser Toolkit for Windows 95.
// Copyright © 1997 The 3DO Company. All rights reserved.

//////////////////////////////////////////////////////////////////////////////
//
// Header dependencies 
//
#include <windows.h>
#include <windowsx.h>
#include <string.h>
#include <direct.h>
#include <vfw.h>
#include "resource.h"
#include "commfunc.h"
#include "mainwnd.h"

//////////////////////////////////////////////////////////////////////////////
//
// Private constant variables
//
static const char k_szWndClass[] = "nWorld_AutoRunClass";
static const char k_szTitle[] = "New World Computing's Autorun Toolkit for Windows 95";
static const char k_szError[] = "Error";

//////////////////////////////////////////////////////////////////////////////
//
// Private global variables
//
static char v_szWndTitle[ 256 ];
static HDRAWDIB v_hddBkgnd=NULL;
static HDRAWDIB v_hdd=NULL;
static int v_iLastHotspot = 0;

static LPSTR v_lpBitmap = NULL;
static LPBITMAPFILEHEADER v_lpbfh = NULL;
static LPBITMAPINFOHEADER v_lpbih = NULL;
static LPSTR v_lpBits = NULL;

//////////////////////////////////////////////////////////////////////////////
//
// Private data types
//
struct HOTSPOT
{
	RECT clickable;
	RECT rect;

	char szHotspotBMPName[ 256 ];
	LPSTR pBitmapData;

	// non-allocated pointers
	LPBITMAPFILEHEADER pBitmapFileHeader;
	LPBITMAPINFOHEADER pBitmapInfoHeader;
	LPSTR pBitmapBits;

	char szMouseOverWaveFile[256];
	char szMouseClickWaveFile[256];
	char szExecCmd[256];

	BOOL fCloseAfterRun;
};

#define MAX_HOTSPOT 16
int v_iNumHotspot=0;
static HOTSPOT hotspot[ MAX_HOTSPOT ];

//////////////////////////////////////////////////////////////////////////////
//
// Private function
// 
static char * LoadDIB( char * pszFilename )
{
	char * pData = NULL;
	OFSTRUCT of;
	HFILE hfile = OpenFile( pszFilename, &of, OF_READ|OF_SHARE_DENY_WRITE );
	if( hfile != HFILE_ERROR )
	{
		DWORD dwFileSize = GetFileSize( (HANDLE)hfile, NULL );

		if( dwFileSize > 0  && dwFileSize != 0xFFFFFFFF )
		{
			char * pBuf = (LPSTR)GlobalAlloc( GPTR, dwFileSize );
			if( pBuf != NULL )
			{
				DWORD dwNumBytesRead = 0;
				if( ReadFile( (HANDLE)hfile, pBuf, dwFileSize, &dwNumBytesRead, NULL ) == TRUE
				&& dwNumBytesRead == dwFileSize )
				{
					pData = pBuf;
				}
			}
			CloseHandle( (HANDLE)hfile );
		}
	}
	return pData;
}

//////////////////////////////////////////////////////////////////////////////
//
// Private function
// 
static int LookupHotspot( int x, int y )
{
	int iHotspot = 0;
	for( int i = 0; i < v_iNumHotspot; i++ )
	{
		if( x >= hotspot[i].clickable.left 
		&&  x <  hotspot[i].clickable.left + hotspot[i].clickable.right 
		&&  y >= hotspot[i].clickable.top 
		&&  y <  hotspot[i].clickable.top + hotspot[i].clickable.bottom )
			return i+1;
	}
	return iHotspot;
}

//////////////////////////////////////////////////////////////////////////////
//
// Private function
//
#define ERR_MISSINGHOTSPOTPARAMS 1
#define ERR_CANTLOADHOTSPOTBMP   2
static void ReportError( HWND hwndParent, int iError, LPARAM lparam1, LPARAM lparam2 )
{
	char szBuf[ 512 ];
	switch( iError )
	{
		case ERR_MISSINGHOTSPOTPARAMS:
		/* lparam1 = hotspot number */
		/* lparam2 = parameter number */
		{
			wsprintf( szBuf, GetString(GetWindowInstance(hwndParent),IDS_FAILMISSINGPARAMETER), lparam1, lparam2 ); 
			MessageBox( hwndParent, szBuf, k_szError, MB_ICONASTERISK|MB_OK );
		}
		break;

		case ERR_CANTLOADHOTSPOTBMP:
		/* lparam1 = hotspot number */
		{
			wsprintf( szBuf, GetString(GetWindowInstance(hwndParent),IDS_FAILLOADHOTSPOT), lparam1 );
			MessageBox( hwndParent, szBuf, k_szError, MB_ICONASTERISK|MB_OK );
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// Private function
// 
static void LoadHotspotInfo( HINSTANCE hinst, HWND hwnd )
{
	char szFilename[ 256 ];
	GetModuleFileName( hinst, szFilename, sizeof(szFilename) ) ;

	char drive[ _MAX_DRIVE ];
	char dir[ _MAX_DIR ];
	_splitpath( szFilename, drive, dir, NULL, NULL );
	wsprintf( szFilename, "%s%sautorun.ini", drive, dir );

	GetPrivateProfileString( "Options", "WindowTitle", "", v_szWndTitle, sizeof(v_szWndTitle), szFilename );

	v_iNumHotspot=0;
	
	int iNumLookUp=1;
	char szNum[ 10 ];
	wsprintf( szNum, "%d", iNumLookUp );

	char szBuf[ 512 ];
	while( v_iNumHotspot <= MAX_HOTSPOT && GetPrivateProfileString( "Hotspots", szNum, "", szBuf, sizeof(szBuf), szFilename ) )
	{
		char * pStart = szBuf;
		char * pEnd = NULL;

		/* 1 - mouse left coordinate */
		pEnd = strchr(pStart,','); if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 1 ); goto next; }
		*pEnd = '\0';
		hotspot[ v_iNumHotspot ].clickable.left = atoi( pStart );
		pStart = pEnd+1; if( !*pStart ) break;

		/* 2 - mouse right coordinate */
		pEnd = strchr(pStart,','); if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 1 ); goto next; }
		*pEnd = '\0';
		hotspot[ v_iNumHotspot ].clickable.top = atoi( pStart );
		pStart = pEnd+1; if( !*pStart ) break;

		/* 3 - mouse width coordinate */
		pEnd = strchr(pStart,','); if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 1 ); goto next; }
		*pEnd = '\0';
		hotspot[ v_iNumHotspot ].clickable.right = atoi( pStart );
		pStart = pEnd+1; if( !*pStart ) break;

		/* 4 - mouse height coordinate */
		pEnd = strchr(pStart,','); if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 1 ); goto next; }
		*pEnd = '\0';
		hotspot[ v_iNumHotspot ].clickable.bottom = atoi( pStart );
		pStart = pEnd+1; if( !*pStart ) break;

		/* 5 - left coordinate */
		pEnd = strchr(pStart,','); if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 1 ); goto next; }
		*pEnd = '\0';
		hotspot[ v_iNumHotspot ].rect.left = atoi( pStart );
		pStart = pEnd+1; if( !*pStart ) break;
	
		/* 6 - top coordinate */
		pEnd = strchr(pStart,',');  if( !pEnd ) if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 2 ); goto next; }
		*pEnd = '\0';
		hotspot[ v_iNumHotspot ].rect.top = atoi( pStart );
		pStart = pEnd+1; if( !*pStart ) break;

		/* 7 - width (only necissary if animated hotspot not provided) */
		pEnd = strchr(pStart,',');  if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 3 ); goto next; }
		*pEnd = '\0';
		hotspot[ v_iNumHotspot ].rect.right = atoi( pStart );
		pStart = pEnd+1; if( !*pStart ) break;
		
		/* 8 - height (only necissary if animated hotspot not provided) */
		pEnd = strchr(pStart,',');  if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 4 ); goto next; }
		*pEnd = '\0';
		hotspot[ v_iNumHotspot ].rect.bottom = atoi( pStart );
		pStart = pEnd+1; if( !*pStart ) break;

		/* 9 - cmd */
		pEnd = strchr(pStart,',');  if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 5 ); goto next; }
		*pEnd = '\0';
		strcpy( hotspot[ v_iNumHotspot ].szExecCmd, pStart );
		pStart = pEnd+1; if( !*pStart ) break;

		/* 10 - close flag */
		pEnd = strchr(pStart,',');  if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 6 ); goto next; }
		*pEnd = '\0';
		hotspot[ v_iNumHotspot ].fCloseAfterRun = atoi( pStart ) != 0;
		pStart = pEnd+1; if( !*pStart ) break;

		/* 11 - animated hotspot BMP filename */
		pEnd = strchr(pStart,',');  if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 7 ); goto next; }
		*pEnd = '\0';
		strcpy( hotspot[ v_iNumHotspot ].szHotspotBMPName, pStart );
		pStart = pEnd+1; if( !*pStart ) break;

		/* 12 - mouse over wave sound */
		pEnd = strchr(pStart,','); if( !pEnd ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 8 ); goto next; }
		*pEnd = '\0';
		strcpy( hotspot[ v_iNumHotspot ].szMouseOverWaveFile, pStart );
		pStart = pEnd+1; if( !*pStart ) break;

		/* 13 - mouse click wave sound */
		if( !strlen(pStart) ) { ReportError( hwnd, ERR_MISSINGHOTSPOTPARAMS, iNumLookUp, 8 ); goto next; }
		strcpy( hotspot[ v_iNumHotspot ].szMouseClickWaveFile, pStart );

		/* if hotspot BMP filename is not blank or set to (none), then try loading it */		
		if( strlen(hotspot[v_iNumHotspot].szHotspotBMPName) && strcmpi(hotspot[v_iNumHotspot].szHotspotBMPName,"(none)") != 0 )
		{
			/* Load hotspot BMP */
			if( (hotspot[ v_iNumHotspot ].pBitmapData = LoadDIB(hotspot[v_iNumHotspot].szHotspotBMPName)) != NULL )
			{
				hotspot[ v_iNumHotspot ].pBitmapFileHeader = (LPBITMAPFILEHEADER)hotspot[ v_iNumHotspot ].pBitmapData;
				hotspot[ v_iNumHotspot ].pBitmapInfoHeader = (LPBITMAPINFOHEADER)(hotspot[ v_iNumHotspot ].pBitmapData + sizeof(BITMAPFILEHEADER));
				hotspot[ v_iNumHotspot ].pBitmapBits = hotspot[ v_iNumHotspot ].pBitmapData + hotspot[ v_iNumHotspot ].pBitmapFileHeader->bfOffBits;
				hotspot[ v_iNumHotspot ].rect.right = hotspot[ v_iNumHotspot ].pBitmapInfoHeader->biWidth;
				hotspot[ v_iNumHotspot ].rect.bottom = hotspot[ v_iNumHotspot ].pBitmapInfoHeader->biHeight;
			}
			else
			{
				hotspot[ v_iNumHotspot ].pBitmapFileHeader = NULL;
				hotspot[ v_iNumHotspot ].pBitmapInfoHeader = NULL;
				hotspot[ v_iNumHotspot ].pBitmapBits = NULL;
				ReportError( hwnd, ERR_CANTLOADHOTSPOTBMP, iNumLookUp, 0 );
				goto next;
			}
		}

		/**/

		v_iNumHotspot++;

next:
		wsprintf( szNum, "%d", ++iNumLookUp );
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// Callback
// 
BOOL CALLBACK AboutDlgProc( HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_COMMAND:
			if( LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL )
			{
				EndDialog( hdlg, LOWORD(wParam) );
				return TRUE;
			}
			break;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////
//
// Callback
// 
LRESULT CALLBACK MainWnd_WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
char tempText[255],tempLen;

	switch( uMsg )
	{
		case WM_CREATE:
			{
				char szFilename[ 256 ];
				GetModuleFileName( GetWindowInstance(hwnd), szFilename, sizeof(szFilename) );

				char drive[ _MAX_DRIVE ];
				char dir[ _MAX_DIR ];
				_splitpath( szFilename, drive, dir, NULL, NULL );
				wsprintf( szFilename, "%s%sautorun.wav", drive, dir );

				PlaySound( szFilename, NULL, SND_ASYNC|SND_FILENAME|SND_NODEFAULT );
				
				LoadHotspotInfo( GetWindowInstance(hwnd), hwnd );
				
				if( v_szWndTitle[0] )
					SetWindowText( hwnd, v_szWndTitle );

				wsprintf( szFilename, "%s%sautorun.bmp", drive, dir );
			
				v_lpBitmap = LoadDIB( szFilename );
				if( !v_lpBitmap )
				{
					MessageBox( NULL, GetString(GetWindowInstance(hwnd),IDS_FAILLOADAUTORUNBMP), k_szError, MB_OK|MB_ICONASTERISK );
					return -1;
				}

				v_lpbfh = (LPBITMAPFILEHEADER)v_lpBitmap;
				v_lpbih = (LPBITMAPINFOHEADER)(v_lpBitmap + sizeof(BITMAPFILEHEADER));
				v_lpBits = v_lpBitmap + v_lpbfh->bfOffBits;

				v_hddBkgnd = DrawDibOpen();
				if( !v_hddBkgnd )
				{
					MessageBox( NULL, "Unable to open DrawDIB services.", k_szError, MB_OK|MB_ICONASTERISK );
					return -1;
				}

				v_hdd = DrawDibOpen();
				if( !v_hdd )
				{
					MessageBox( NULL, "Unable to open DrawDIB services.", k_szError, MB_OK|MB_ICONASTERISK );
					return -1;
				}

				RECT rc;
				GetWindowRect( hwnd, &rc );

				MoveWindow( hwnd, rc.left, rc.top, 
					v_lpbih->biWidth + (GetSystemMetrics(SM_CXDLGFRAME)*2), 
					v_lpbih->biHeight + (GetSystemMetrics(SM_CYDLGFRAME)*2) + GetSystemMetrics(SM_CYCAPTION), FALSE );

			}
			return 0;

		case WM_PALETTECHANGED:
			if( (HWND)wParam == hwnd )
				return 0;
			// else fall through

		case WM_QUERYNEWPALETTE:
			{
				HDC hdc = GetDC( hwnd ); 
				BOOL f = DrawDibRealize( v_hddBkgnd, hdc, FALSE ) > 0; 
				ReleaseDC( hwnd, hdc ); 
				if( f ) 
				{
					InvalidateRect( hwnd, NULL, FALSE ); 
					return TRUE;
				}
			}
			return FALSE;

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				BeginPaint( hwnd, &ps );

				DrawDibDraw( v_hddBkgnd, ps.hdc, 
						 ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom, 
						 v_lpbih, v_lpBits, 
						 ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom,  
						 0 );
						 
				if( v_iLastHotspot )
				{
					DrawDibDraw( v_hdd, ps.hdc, 
						 hotspot[ v_iLastHotspot-1 ].rect.left,
						 hotspot[ v_iLastHotspot-1 ].rect.top,
						 hotspot[ v_iLastHotspot-1 ].rect.right, /* width */
						 hotspot[ v_iLastHotspot-1 ].rect.bottom, /* height */
						 hotspot[ v_iLastHotspot-1 ].pBitmapInfoHeader,
						 hotspot[ v_iLastHotspot-1 ].pBitmapBits,
						 0, 0,
						 hotspot[ v_iLastHotspot-1 ].rect.right, /* width */
						 hotspot[ v_iLastHotspot-1 ].rect.bottom, /* height */
						 0 ); 
				}

				EndPaint( hwnd, &ps );
			}
			return 0;

		case WM_KEYDOWN:
			if( wParam == VK_F9 )
				DialogBox( GetWindowInstance(hwnd), MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC)AboutDlgProc );
			break;

		case WM_LBUTTONDOWN:
			{
				int xpos = LOWORD(lParam);
				int ypos = HIWORD(lParam);

				int iHotspot = LookupHotspot( xpos, ypos );
				if( iHotspot )
				{
					if( iHotspot )
						PlaySound( NULL, NULL, 0 );	//Stop Sound
						PlaySound( hotspot[ iHotspot-1 ].szMouseClickWaveFile, NULL, SND_SYNC|SND_FILENAME|SND_NOWAIT|SND_NODEFAULT );

					if( GetCapture() )
						ReleaseCapture();
					   
					PlaySound( NULL, NULL, 0 ); //Stop Sound
					strcpy(tempText,hotspot[iHotspot-1].szExecCmd);
					strrev(tempText);
					strtok(tempText,"\\");
					strrev(tempText);
					tempLen=strlen(tempText);
					if (tempLen != (char)strlen(hotspot[iHotspot-1].szExecCmd))
						{
						memset(tempText,0,sizeof(tempText));
						strncpy(tempText,hotspot[iHotspot-1].szExecCmd,strlen(hotspot[iHotspot-1].szExecCmd)-tempLen-1);
						_chdir(tempText);
						}
					WinExec( hotspot[iHotspot-1].szExecCmd, SW_SHOWNORMAL );
					if( hotspot[iHotspot-1].fCloseAfterRun )
						PostMessage( hwnd, WM_CLOSE, 0, 0L );
				}
			}
			return 0;

		case WM_MOUSEMOVE:
			if( GetActiveWindow() )
			{
				int xpos = LOWORD(lParam);
				int ypos = HIWORD(lParam);

				int iHotspot = LookupHotspot( xpos, ypos );

				if( iHotspot != v_iLastHotspot )
				{
					PlaySound( hotspot[ iHotspot-1 ].szMouseOverWaveFile, NULL, SND_ASYNC|SND_FILENAME|SND_NODEFAULT|SND_NOSTOP );

					v_iLastHotspot = iHotspot;
					InvalidateRect( hwnd, NULL, FALSE );
				}

				if( !iHotspot && GetCapture() )
					ReleaseCapture();
			}
			else
			{
				if( GetCapture() )
					ReleaseCapture();
			}
			break;

		case WM_ACTIVATE:
			if( LOWORD(wParam) == WA_INACTIVE )
			{
				if( GetCapture() )
					ReleaseCapture();

				if( v_iLastHotspot )
				{
					v_iLastHotspot = 0;
					InvalidateRect( hwnd, NULL, FALSE );
				}
			}
			break;

		case WM_DESTROY:
			{
				PlaySound( NULL, NULL, 0 );

				if( v_hddBkgnd )
				{
					DrawDibClose( v_hddBkgnd );
					v_hddBkgnd = NULL;
				}

				if( v_hdd )
				{
					DrawDibClose( v_hdd );
					v_hdd = NULL;
				}

				if( v_lpBitmap )
				{
					GlobalFree( v_lpBitmap );
					v_lpBitmap = NULL;
				}
	
				for( int i = 0; i < v_iNumHotspot; i++ )
				{
					if( hotspot[ i ].pBitmapData )
					{
						GlobalFree( hotspot[ i ].pBitmapData );
						hotspot[ i ].pBitmapData = NULL;
					}
				}

				PostQuitMessage( 0 );
			}
			return 0;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////////
//
// Public API function
// 
const char * MainWnd_GetClassName( void )
{
	return k_szWndClass;
}

//////////////////////////////////////////////////////////////////////////////
//
// Public API function
// 
BOOL MainWnd_RegisterClass( HINSTANCE hinst )
{
	WNDCLASSEX wc;

	wc.cbSize        = sizeof( WNDCLASSEX );
	wc.style         = 0;
	wc.lpfnWndProc   = (WNDPROC)MainWnd_WindowProc;
	wc.cbClsExtra    = 0; 
    wc.cbWndExtra    = 0; 
	wc.hInstance     = hinst;
	wc.hIcon         = LoadIcon( hinst, MAKEINTRESOURCE(IDI_APP) ); 
	wc.hCursor       = LoadCursor( NULL, IDC_ARROW ); 
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = k_szWndClass;
	wc.hIconSm       = LoadImage( hinst, MAKEINTRESOURCE(IDI_APP), IMAGE_ICON, 16, 16, 0 ); 

	return RegisterClassEx( &wc );
}

//////////////////////////////////////////////////////////////////////////////
//
// Public API function
// 
HWND MainWnd_CreateWindow( HINSTANCE hinst, HWND hwndParent )
{
	return CreateWindowEx( 0, k_szWndClass, k_szTitle, 
        WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION|WS_DLGFRAME|WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        (HWND) NULL, (HMENU) NULL, hinst, (LPVOID) NULL ); 
}

