/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Dd.cpp $
//
//	DESCRIPTION:	routines for loading bitmap and palettes
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, May 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Dd.cpp 81    4/09/98 1:32p Nrobinso $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Dd.cpp $
//  
//  81    4/09/98 1:32p Nrobinso
//  don't put up an error when can't get a palette for front buffer
//  
//  79    4/02/98 7:27p Aburgess
//  add new surface creation routine for smacker
//  
//  78    4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  77    3/31/98 12:49p Bwilcox
//  dispell fog
//  
//  76    3/27/98 2:02p Phu
//  survive alt-tab
//  
//  75    3/27/98 1:49p Phu
//  survive ALT_TAB dammit
//  
//  74    3/22/98 6:08p Phu
//  fix parameter mismatch in rectintersect
//  
//  73    3/19/98 11:19p Nrobinso
//  add EraseBackSurface
//  
//  72    3/19/98 4:39p Phu
//  TRACES if surface doesn't fit into video memory
//  
//  71    3/11/98 10:21p Nrobinso
//  replace ClipRect with the one from Disp.cpp
//  
//  70    3/10/98 3:45p Phu
//  note that clipline sometimes returns 0!
//  added assert to getobjects
//  fix flamethrowers go off screen
//  
//  69    3/08/98 1:23p Phu
//  change fixed_trans_table generation
//  
//  68    3/06/98 2:53p Phu
//  library load as default,  faster animation loading
//  
//  67    3/02/98 5:13p Phu
//  fixed trans table for ODF trle sprites
//  
//  66    3/01/98 10:02p Nrobinso
//  fix DDfail so it doesn't trace twice
//  
//  65    3/01/98 1:02p Bwilcox
//  ddrect now fixes values rather than assertjng (god mode off bottom fix)
//  
//  64    2/24/98 10:46a Aburgess
//  modification made to clear screen (front/back buffers) on palette
//  transitions
//  
//  63    2/23/98 12:48p Phu
//  don't clear palette
//  
//  62    2/19/98 11:31a Aburgess
//  modifications for screen layouts
//  
//  61    2/09/98 6:55p Phu
//  true line clipping function
//  
//  60    2/05/98 12:35p Phu
//  flaming plastic
//  
//  59    1/22/98 6:43p Nrobinso
//  use SetPath
//  
//  58    1/12/98 10:42a Aburgess
//  changes made to look in the RUNTIME/MAPS directory for map based
//  information
//  
//  57    1/09/98 6:33p Nrobinso
//  put up error box if bitmap is >8bits
//  
//  56    12/24/97 4:45p Bwilcox
//  removed DrawExxx functions
//  
//  55    12/21/97 3:26p Phu
//  shade table loading
//  
//  54    12/19/97 10:22a Phu
//  
//  53    12/17/97 11:42a Phu
//  
//  52    12/16/97 11:16p Phu
//  Create 4 level shading tables
//  
//  51    12/16/97 10:57p Phu
//  
//  50    12/12/97 12:24p Phu
//  
//  49    12/11/97 11:39p Nrobinso
//  put DD error string in DrawScreenRect
//  
//  48    12/11/97 10:41a Phu
//  fix bad fonts
//  
//  47    12/11/97 9:51a Phu
//  
//  46    12/09/97 5:56p Phu
//  
//  45    12/09/97 12:12p Phu
//  
//  44    12/04/97 6:48p Phu
//  add scarring, improved palette shifting, shadow-only sprites
//  
//  43    12/04/97 2:37p Phu
//  
//  42    12/02/97 11:21a Phu
//  fog of war
//  
//  41    12/01/97 9:20p Nrobinso
//  add DDCopyBackToFront
//  
//  40    12/01/97 6:21p Nrobinso
//  turn of pallette trace
//  
//  39    12/01/97 10:01a Nrobinso
//  switch to Error instead of raw MessageBox
//  
//  38    11/20/97 11:26a Nrobinso
//  DrawRect functions removed, since they just dup the FillRect functions
//  
//  37    11/19/97 10:07a Nrobinso
//  fix bug in FillRectFront; move DrawRect functions in from ui.cpp; make
//  all rgb colors intor COLORREFs
//  
//  36    11/07/97 10:25a Aburgess
//  added debug
//  
//  35    11/03/97 9:42p Nrobinso
//  return sizes from bitmap creation routines
//  
//  34    11/03/97 10:33a Phu
//  revised shadow code
//  
//  33    10/28/97 5:53p Phu
//  create a shadow palette
//  
//  32    10/28/97 4:41p Phu
//  Make shadow function work w/ new disp
//  
//  31    10/27/97 10:32a Aburgess
//  added FillRectFront()
//  
//  30    10/21/97 8:27p Phu
//  Changed ClipLine to clip for x
//  
//  29    10/15/97 10:43a Phu
//  New DD line & point & rect f()s
//  
//  28    10/13/97 2:54p Phu
//  modified displayspriteclipped to clip to an arbitrary window
//  
//  27    10/10/97 3:46p Awerner
//  The small map is now fully funcitonal, although I've commented out the
//  drawing of the dots, because it's _very_ slow right now
//  
//  26    9/30/97 4:00p Phu
//  New display engine!
//  
//  24    8/25/97 5:56p Phu
//  Optimized inline shaded shadow blits
//  
//  23    8/22/97 3:30p Nrobinso
//  fix typo
//  
//  22    8/22/97 3:24p Nrobinso
//  allow a null result rect passed to RectIntersect
//  
//  21    8/22/97 10:39a Phu
//  Shadow Blitting
//  
//  20    8/21/97 10:07a Phu
//  Shadow Blitting
//  
//  19    8/20/97 9:30a Phu
//  Shade function stubs
//  
//  18    8/20/97 8:35a Phu
//  Load & Attach shadow files.  Draw shadows in black.
//  
//  17    8/13/97 10:46p Phu
//  Fix to load-time WRLE loading & color transformation
//  
//  16    8/13/97 9:27p Phu
//  Handle non-translated WRLE on load
//  
//  15    8/12/97 7:06a Phu
//  RLE Text functions
//  
//  14    8/08/97 12:16p Phu
//  RLE Optimizations
//  
//  13    7/30/97 7:06p Phu
//  WORD vs DWORD line table RLE functions
//  
//  12    7/25/97 11:34a Aburgess
//  added file and line info to trace messages
//  
//  11    7/24/97 5:49p Phu
//  Various tests to see if things are going into vidmem
//  
//  10    7/24/97 3:32p Phu
//  Lock/Unlock during display area update only when necessary
//  
//  9     7/24/97 3:03p Phu
//  DirectDraw Surface Lock status flag
//  
//  8     7/24/97 2:19p Phu
//  Color correction for RLE256 objects
//  
//  7     7/24/97 12:04p Phu
//  Inside RLE256 function
//  
//  6     7/23/97 11:26a Phu
//  Load objects from library file
//  
//  5     7/15/97 6:42p Phu
//  Fix to _USESYSTEMMEMORY_ directive
//  
//  4     7/15/97 2:24p Awerner
//  Added ScreenToWorld() function
//  
//  3     7/14/97 6:04p Phu
//  Vidmem objects
//  
//  2     7/14/97 5:02p Phu
//  Basic functionality for vidmem sprites
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  66    6/16/97 6:02p Nrobinso
//  assert on > 8 bit bitmaps being loaded
//  
//  65    6/05/97 5:26p Nrobinso
//  add DrawDotFront() and DrawLineFront()
//  
//  64    5/20/97 10:47a Awerner
//  new RLEFastBltClipped, untested and commented out
//  
//  63    5/13/97 3:49p Nrobinso
//  add the BM_FORCE_OPQUE flag, which uses 255 instead of the upper left
//  corner for transparent
//  
//  62    5/09/97 11:35a Aburgess
//  new clipping routines
//  
//  61    5/08/97 1:48p Nrobinso
//  assert if >8 bits of color in a loaded bitmap
//  
//  60    5/08/97 12:21p Nrobinso
//  
//  59    4/30/97 11:50a Aburgess
//  added multi-draw support
//  
//  58    4/23/97 3:44p Nrobinso
//  delete windows palette
//  
//  57    4/09/97 7:59a Nrobinso
//  add ability to change palettes
//  
//  56    4/01/97 9:05p Nrobinso
//  ClipRectToBackWindow becomes ClipRectToGameWindow
//  
//  55    4/01/97 6:26p Nrobinso
//  fix error checking bugs; fix 1-bit mask load code
//  
//  54    3/28/97 11:05a Nrobinso
//  add LoadMask() for mask bitmaps
//  
//  53    3/20/97 1:40p Bwilcox
//  added DrawELine
//  
//  52    3/19/97 5:06p Bwilcox
//  added DrawEDot for doing epoints instead of spoints
//  
//  51    3/19/97 9:57a Nrobinso
//  fix InRect & InBox; add ClipRect, ClipSPoint, ValidateSpoint and MinMax
//  founctions
//  
//  50    3/18/97 5:51p Nrobinso
//  new DrawDot(); move InRect and InBox into DD.cpp
//  
//  49    3/17/97 11:44a Nrobinso
//  switched to SBOX's from BOX's; fixed a pointer going beyond it's memory
//  block
//  
//  48    3/12/97 3:39p Nrobinso
//  load already RLE images; remove dependence on CreateDIB
//
//  47    3/03/97 8:06a Nrobinso
//  switch to BITMAPINFO_256 in types.h; add DDMakeBitmapFrom Memory to
//  support anim files
//  
//  46    2/25/97 4:15p Nrobinso
//  change rcWindow ro rcWindowScreen
//  
//  45    2/20/97 1:19p Aburgess
//  Conversion from POINT to SPOINT
//  
//  44    2/14/97 2:47p Nrobinso
//  fix bug when the bitmap size is set 0 in the bitmap header
//  
//  43    1/28/97 10:36a Nrobinso
//  replace strcats with a single sprintf
//  
//  42    1/27/97 4:54p Nrobinso
//  Add RLETranslateBlt() and RLEFastBlt(); Fix off by one bug in
//  TranslateBlt routines
//  
//  41    1/24/97 5:44p Nrobinso
//  combine the LoadBitmap() processes for normal & RLE bitmaps
//  
//  40    1/23/97 5:31p Nrobinso
//  Add RLE Sprites, translated and not
//  
//  39    1/21/97 6:48p Nrobinso
//  switched to our own translation when laoding bitmaps; added a
//  recoloring blitter
//  
//  38    1/16/97 12:10p Nrobinso
//  Added color translation to bitmap copies
//  
//  37    1/15/97 9:48p Nrobinso
//  Add direct copied bitmap load
//  
//  36    97-01-14 9:53 Ereich
//  Next to last version before clean-up is complete.
//  
//  35    97-01-10 16:34 Ereich
//  A good check-in point for code clean-up...
//  
//  34    1/09/97 2:49p Nrobinso
//  Add RLE blitter
//  
//  33    1/08/97 8:00a Aburgess
//  added MOVE_DEBUG ifdef
//  
//  32    97-01-07 16:02 Ereich
//  Cleaning house day 1.  I have made many changes to most of the files
//  and it seems to still work.  So I thought I would check-it in and
//  continue tomorrow.
//  
//  31    1/07/97 2:58p Aburgess
//  four pixel dots for DrawDot
//  
//  30    1/07/97 1:46p Aburgess
//  corrected DrawDot routine and added WorldToScreen point conversion
//  routine.
//  
//  29    1/07/97 10:28a Aburgess
//  added DrawDot routine
//  
//	...
// 
//  4     6/25/96 9:53p Nrobins
//  added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "Globals.h"
#include "MainFrm.h"
/////////////////////////////////////////////////////////////////////////////
#include "ArmyMen.h"
#include "DrawObject.h"
#include "miscfile.h"
#include "fileio.h"

// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//  Direct Draw 2 Object (mainfrm.cpp)
extern LPDIRECTDRAW2 pDirectDraw2;

//	Largest size bitmap to attempt to load into video memory
#define VIDEO_BITMAP_THRESHOLD		10000

//	Handle to the global palette
PALETTE		current_palette = {NULL, NULL};

pal LogicalPalette = {0x300, 256};
pal OriginalPalette = {0x300, 256};

//  Drawing stuff
DWORD		LPITCH;
BYTE		*SCRPTR;
BYTE		DDCOLOR = 0;
BOOL		ODDLINE;
BYTE		SHADE_TABLE[264];
BYTE		*PSHADE_TABLE = (BYTE *)(((DWORD)SHADE_TABLE+3) & (~3));
BYTE		LIGHT_TABLE[264];
BYTE		*PLIGHT_TABLE = (BYTE *)(((DWORD)LIGHT_TABLE+3) & (~3));
BYTE		RED_TABLE[264];
BYTE		*PRED_TABLE = (BYTE *)(((DWORD)RED_TABLE+3) & (~3));
BYTE		DARK_TABLE[1040];
BYTE		*PDARK_TABLE[4];
BYTE		*PShadeTable = PSHADE_TABLE;

//	Bitmap size counter
DWORD total_size = 0;


//  Lock status
BOOL  LOCK_STATUS = FALSE;
BOOL  LOCK_COMPLEX_ON = FALSE;


extern BYTE main_trans_table[256];


RECT  DefaultClipRect = { 0, 0, 640, 480 };
RECT  *pClipRect = &DefaultClipRect;


//************************************************************************
//	Palette Functions
//************************************************************************

//	This routine ensures that our logical indentity palette
//	won't get collasped or remapped when we realize it
void ClearSystemPalette ( void )
{
	HDC Screen;

	Screen = GetDC(NULL);				//	Force a reset of the system palette

	SetSystemPaletteUse(Screen, SYSPAL_NOSTATIC);
	SetSystemPaletteUse(Screen, SYSPAL_STATIC);

	ReleaseDC( NULL, Screen);
}	// ClearSystemPalette


//	Creates a logical palette made up of the STATIC COLORS and 
//	unique palette colors passed in 
//	input: 
//	  RGBQUAD *palette (indexes 10 - 245 )
//	returns:
//	  HPALETTE - handle to new palette
HPALETTE CreateIDPalette( RGBQUAD *palette )
{
    HDC Screen;
    int i;
	UINT colors;
	HPALETTE temp_pal,
			 old_pal;

	ClearSystemPalette();

	for ( i = 0; i < 256; i++ )	{
        OriginalPalette.aEntries[i].peRed = palette[i].rgbRed;
        OriginalPalette.aEntries[i].peGreen = palette[i].rgbGreen;
        OriginalPalette.aEntries[i].peBlue = palette[i].rgbBlue;
        OriginalPalette.aEntries[i].peFlags = 0;
	}

	temp_pal = CreatePalette((LOGPALETTE *)&OriginalPalette);
	if (temp_pal)	{
		Screen = GetDC(NULL);

		old_pal = SelectPalette(Screen, temp_pal, FALSE);
		colors = RealizePalette(Screen);
		SelectPalette(Screen, old_pal, FALSE);
		DeleteObject(temp_pal);

		ReleaseDC ( NULL, Screen );
	}
	else
		return NULL;

	GetSystemPaletteEntries ( Screen, 0, 256, LogicalPalette.aEntries );

	for (i = 0; i < 10; i++)
		LogicalPalette.aEntries[i].peFlags = LogicalPalette.aEntries[255-i].peFlags = 0;
	for (i = 10; i < 246; i++)
		LogicalPalette.aEntries[i].peFlags = PC_NOCOLLAPSE;

	temp_pal = CreatePalette((LOGPALETTE *)&LogicalPalette);

	return temp_pal;
}	// CreateIDPalette


//	Gets a palette from a 8 bit BMP file
//	input:
//	  LPDIRECTDRAW lpDirectDrawObject - DirectDraw Object
//    BITMAPINFO_256 *pbminfo - bitmap info header
//	returns:
//    TRUE - success
BOOL GetPal( char *bmp, BITMAPINFO_256 *pbminfo )
{
	BITMAPINFOHEADER *pHeader = &pbminfo->bmiHeader;
	HRSRC	hrsrc;
	FILE	*pfile;
	UINT	iColorTableSize;

	if (hrsrc = FindResource(NULL, bmp, RT_BITMAP))	{
		BYTE *pRsrc;

		pRsrc = (BYTE *) LockResource(LoadResource(NULL, hrsrc));
		if (!pRsrc)
			return FALSE;

		memcpy(pHeader, pRsrc, sizeof(BITMAPINFOHEADER));
		pRsrc += sizeof(BITMAPINFOHEADER);

		ASSERT(pHeader->biBitCount <= 8 );

		if (pHeader->biClrUsed == 0)
			pHeader->biClrUsed = 1 << pHeader->biBitCount;

		iColorTableSize = pHeader->biClrUsed * sizeof(RGBQUAD);

		// Now read the color table in
		memcpy(pbminfo->bmiColors, pRsrc, iColorTableSize);
	}
	else if ((pfile = fopen( bmp, "rb" )) != NULL)	{

		// Read the BMP header and info structures
		BITMAPFILEHEADER    BMPFileHead;
		fread( &BMPFileHead, 1, sizeof(BMPFileHead), pfile );

		fread( pHeader, 1, sizeof(BITMAPINFOHEADER), pfile );

//		ASSERT(pHeader->biBitCount <= 8 );
		if (pHeader->biBitCount > 8)
			Error("%s has more than 8 bits of color", bmp);

		//get the BMP palette
		if (pHeader->biClrUsed == 0)
			pHeader->biClrUsed = 1 << pHeader->biBitCount;

		iColorTableSize = pHeader->biClrUsed * sizeof(RGBQUAD);

		fread( pbminfo->bmiColors, pHeader->biClrUsed, sizeof(RGBQUAD), pfile );

		fclose(pfile);
	}
	else	{
		TRACE("Error in GetPal: %d\n", errno);
		return FALSE;
	}

    if (pbminfo->bmiHeader.biSize < sizeof(BITMAPINFOHEADER))
		return FALSE;
    else if (pbminfo->bmiHeader.biBitCount > 8)
		return FALSE;

    return TRUE;
}	// GetPal


//  Set the palette for the front buffer of DD surface
BOOL SetCurrentPalette( void )
{
//	ClearSystemPalette();

	if (current_palette.pDDPalette && pFrontBuffer)	
	{
		HRESULT ddrval;

		ddrval = pFrontBuffer->SetPalette(current_palette.pDDPalette);
		if( ddrval == DDERR_SURFACELOST )	
		{
			pFrontBuffer->Restore();

			ddrval= pFrontBuffer->SetPalette(current_palette.pDDPalette);
			if( ddrval == DDERR_SURFACELOST )	
			{
				bWaitForSurfaceRestore = TRUE;
//				TRACE("Failed to restore palette after second try\n");
				return FALSE;
			}
		}
	}

	return TRUE;
}	// SetCurrentPalette


//	Set the current palette
//	input:
//	  PALETTE - palette to set as current palette
BOOL SetPalette( PALETTE *pPalette )	
{
	current_palette = *pPalette;
	return(SetCurrentPalette());
}	// SetPalette


//	Free an identity palette
//	input:
//	  PALETTE - palette to free
void FreeIdentityPalette( PALETTE *pPalette )
{
	if (pPalette->pDDPalette)	
	{
		pPalette->pDDPalette->Release();
		pPalette->pDDPalette = NULL;
	}

	if (pPalette->hpal)	
	{
		DeleteObject(pPalette->hpal);
		pPalette->hpal = NULL;
	}
}  // FreeIdentityPalette


//MakeIdentityPalette - makes an identity palette from a 8 bit BMP file
//input:
//  char *bmp - filename
//	PALETTE *pPalette - pointer to PALETTE structure to set
//returns:
//  TRUE if sets ok
//  puts palette info into pPalette
BOOL MakeIdentityPalette( char *bmp, PALETTE *pPalette )
{
    BITMAPINFO_256		bminfo;
    LPDIRECTDRAWPALETTE pddpal = NULL;
	HPALETTE			hPalette = NULL;
	BOOL				ok = FALSE;

    if( pMainFrame->GetBPP() != 8)
		return TRUE;

	// for now, always erase the surfaces before creating the
	// new palette
	EraseSurfaces();

	// set the table pointers for 4 levels of shading
	PDARK_TABLE[0] = (BYTE *)(((DWORD)DARK_TABLE+3) & (~3));
	for( int i = 1; i < 4; i++ )
		PDARK_TABLE[i] = PDARK_TABLE[i-1] + 256;
	
	if (GetPal(bmp, &bminfo))	
	{
		FreeIdentityPalette(pPalette);

		hPalette = CreateIDPalette( bminfo.bmiColors );

		if (hPalette)	
		{

			HRESULT ddrval;
			ddrval = pDirectDraw->CreatePalette(DDPCAPS_8BIT, LogicalPalette.aEntries, &pddpal, NULL);

			if (pddpal)	
			{
				ddrval = pFrontBuffer->SetPalette(pddpal);
 				if( ddrval != DD_OK )
					TRACE("SetPalette() failure for front buffer\n");
//					DDFail("SetPalette() failure for front buffer", ddrval);
				else
					ok = TRUE;
			}
			else
				TRACE("ERROR: Can't create DD palette\n");
		}

		current_palette.hpal = pPalette->hpal = hPalette;
 		current_palette.pDDPalette = pPalette->pDDPalette = pddpal;

		// create the main_trans_table
		RGBQUAD		*pColors = bminfo.bmiColors;

		HDC	hdc = GetDC(NULL);
		for ( int i=0; i < 256; i++ )
		{
			BYTE  r, g, b;
			BYTE  dw;
			BYTE  j;

			r = pColors[i].rgbRed;
			g = pColors[i].rgbGreen;
			b = pColors[i].rgbBlue;

			dw = GetNearestPaletteIndex(current_palette.hpal, RGB(r, g, b) );
			main_trans_table[i] = dw;
			if( i <= 16 )
				fixed_trans_table[i] = i;
			else
				fixed_trans_table[i] = main_trans_table[i];

			j = dw;
			if( r <= 48 && g <= 48 && b <= 48 )
				dw = GetNearestPaletteIndex(current_palette.hpal, RGB(r, g, b) );
			else
				dw = GetNearestPaletteIndex(current_palette.hpal, RGB(r * 0.7, g * 0.7, b * 0.7) );			
			PSHADE_TABLE[j] = (BYTE)dw;
			dw = GetNearestPaletteIndex(current_palette.hpal, RGB( 
				__min( r * 1.333, 255), __min( g * 1.666, 255 ), __min( b * 1.333, 255) ) );
			PLIGHT_TABLE[j] = (BYTE)dw;
			dw = GetNearestPaletteIndex(current_palette.hpal, RGB(255, 255, 255) );
			PRED_TABLE[j] = (BYTE)dw;

			double DarkFactor[4] = 
				{ 0.4, 0.5, 0.6, 0.85};
			for( int t = 0; t < 4; t++ )
			{
				dw = GetNearestPaletteIndex(current_palette.hpal, RGB(r * DarkFactor[t], g * DarkFactor[t], b * DarkFactor[t]) );
				PDARK_TABLE[t][j] = (BYTE)dw;
			}
		}
		ReleaseDC( NULL, hdc);	
	}

   return ok;
}  // MakeIdentityPalette


//  Force a palette load from a bitmap file named "final_pal.bmp"
//  input:
//	  char * terrain_name - path to file
void ForceLoadIdentityPalette( char *terrain_name )
{
	char filename[64];

	SetPath(NULL);
	sprintf(filename, "%s/final_pal.bmp", terrain_name);
//	TRACE( "Forcing Palette to: %s\n", filename );

	MakeIdentityPalette( filename, &pMainFrame->GamePalette );
}	// ForceLoadIdentityPalette


//	Load a palette if one is not already loaded
//  input:
//	  char * terrain_name - path to file
void LoadIdentityPalette( char *terrain_name )	
{
	if (!pMainFrame->GamePalette.hpal)
		ForceLoadIdentityPalette(terrain_name);
}	// LoadIdentityPalette


//	load a translation table from a binary file
void CreateShadeTable( char *palfile, BYTE *shadetable )
{
	FILE *fp;
	BYTE buffer[256];
	int  i;

	fp = fopen( palfile, "rb" );
	if( !fp )
	{
		TRACE( "Unable to load shade table %s\n", palfile );
		return;
	}
	if( fread( buffer, 256, 1, fp ) != 256 )
	{
		TRACE( "Error reading shade table %s\n", palfile );
		goto done;
	}
	for( i = 0; i < 256; i++ )
	{
		shadetable[main_trans_table[i]] = buffer[i];
	}

done:
	fclose( fp );
}


//************************************************************************
//	Memory Functions
//************************************************************************

//	Memcopy w/ translate (table lookup)
BYTE *memxlat( BYTE *pDest, const BYTE *pSrc, BYTE table[256], int count )	
{
	if (table)	
	{
		for (int i = 0; i < count; i++)
			*pDest++ = table[*pSrc++];
	}
	else
		memcpy( pDest, pSrc, count );

	return pDest;
}	// memxlat



//************************************************************************
//	RLE Functions
//************************************************************************

// Check if a point (as an offset from the rle UL corner) is "in" an RLE surface
BOOL IsPointInDRle( WORD offX, WORD offY, BYTE * buf )
{
	WORD ht, wd;
	BYTE *rp;
	WORD cc;
	BYTE n;

	if ( offX < 0 || offY < 0 )
		return FALSE;

	wd = *(WORD *)buf;
	ht = *(WORD *)( buf + sizeof(WORD) );

	if ( offX > wd || offY > ht )
		return FALSE;

	rp = buf + *( (DWORD *)( buf + ( offY * sizeof(DWORD) ) + sizeof(WORD) * 2 ) );
	cc = 0;
	while ( cc <= offX )
	{
		n = *rp++;						// # of transparent pixels
		cc += n;
		if ( cc > offX )
			return FALSE;

		n = *rp++;						// # of data pixels
		cc += n;
		if ( cc >= offX )
			return TRUE;
		rp += n;
	}

	return FALSE;
}


// Check if a point (as an offset from the rle UL corner) is "in" an RLE surface
BOOL IsPointInWRle( WORD offX, WORD offY, BYTE * buf )
{
	WORD ht, wd;
	BYTE *rp;
	WORD cc;
	BYTE n;

	if ( offX < 0 || offY < 0 )
		return FALSE;

	wd = *(WORD *)buf;
	ht = *(WORD *)( buf + sizeof(WORD) );

	if ( offX > wd || offY > ht )
		return FALSE;

	rp = buf + *( (WORD *)( buf + ( offY * sizeof(WORD) ) + sizeof(WORD) * 2 ) );
	cc = 0;
	while ( cc <= offX )
	{
		n = *rp++;						// # of transparent pixels
		cc += n;
		if ( cc > offX )
			return FALSE;

		n = *rp++;						// # of data pixels
		cc += n;
		if ( cc >= offX )
			return TRUE;
		rp += n;
	}

	return FALSE;
}


//	x is passed in ecx
//	y is passed in edx
void __fastcall DrawDRleClipped( DWORD x, DWORD y, BYTE * buf, RECT rc )
{
	DWORD * lbeg;
	DWORD * lend;
	BYTE  * dline;

__asm
{
	imul	edx, LPITCH		// edx = y * LPITCH								// NP	10

	add		edx, ecx		// edx = edx + x								// U
	mov		eax, rc.top		// lbeg = buf + 4 + rc.top * sizeof(DWORD)		//  V 

	mov		ecx, rc.bottom	// lend = buf + 4 + rc.bottom * sizeof(DWORD)	// U
	add		edx, SCRPTR		// edx = edx + SCRPTR							//  V

	mov		ebx, buf		// ebx = buf									// U
	mov		edi, edx		// edi (dp) = edx (SCRPTR + y*LPITCH + x)		//  V

	lea		edx, DWORD PTR [ebx + ecx * 4 + 4]	// lend						// U   !AGI
	lea		eax, DWORD PTR [ebx + eax * 4 + 4]	// lbeg						//  V

	mov		lend, edx														// U
	mov		lbeg, eax														//  V

rowloopstart:
	cmp		edx, eax		// if ( lend <= lbeg )							// U
	jbe		endoffunction	//   goto end of function						//  V

	mov		dline, edi		// dline = dp									// U
	mov		esi, buf		// sp = buf + *lbeg								//  V

	xor		edx, edx		// edx = cc = 0									// U
	mov		ecx, [eax]		// load line offset contents (*lbeg)			//  V

	add		esi, ecx														// U	
	cmp		edx, rc.right	// if ( cc >= ce )								//  V

	jae		rowloopend		//   goto rowloopend							// U

colloopstart:
	xor		eax, eax		// zero eax										// U
	mov		ecx, edx		// ecx = cc										//  V

	mov		al, BYTE PTR [esi]	// n = *sp++								// U
	mov		ebx, rc.left	// store a temp of rc.left						//  V

	inc		esi				// load a byte from sp							// U
	add		ecx, eax		// ecx = cc + n									//  V

	cmp		edx, ebx		// if ( cc < cs )								// U
	jb		midline			//   goto midline								//  V

	add		edi, eax		// dp += n										// U
	jmp	short transpartend													//  V

midline:
	sub		ecx, ebx		// if ( cc + n < cs )							// U
	jb		transpartend	//   goto transpartend							//  V	PV

	add		edi, ecx		// dp += cc + n - cs							// U

transpartend:
	add		edx, eax		// cc += n										// U
	xor		eax, eax		// zero eax										//  V

	cmp		edx, rc.right	// if ( cc >= ce )								// U
	jae		rowloopend		//   goto rowloopend							//  V   PV

	mov		al, BYTE PTR [esi]	// n = *sp  (al = n)						// U
	mov		ecx, edx		// ecx = cc										//  V

	inc     esi				// sp++											// U
	add		ecx, eax		// ecx = cc + n									//  V

	test	eax, eax		// if ( n = 0 )									// U
	je		nocopy			//   goto nocopy								//  V

	mov		ebx, rc.left	// get a copy of rc.left						// U
	cmp		ecx, ebx		// if ( cc + n  <= cs )							//  V

	jbe		nocopy			//   goto nocopy								// U	PV

	mov		eax, edx		// eax = cc										// U
	sub		ebx, edx		// ms = cs - cc									//  V

	jae		complen			// if ( ms > 0 ) goto complen					// U	PV
	xor     ebx, ebx		// ms = 0										// U

complen:
	add		eax, ebx		// eax = cc + ms								// U
	cmp		ecx, rc.right	// if ( cc + n <= ce )							//  V	2
	jbe		copyray			//   goto copyray								// U	PV
	mov		ecx, rc.right	// mn = ce;										// U

copyray:
	sub		ecx, eax		// mn -= cc + ms
	add		esi, ebx		// sp += ms

	add		edx, ebx		// cc += ms
	mov		eax, ecx		// save run count

	add		edx, ecx		// cc += mn
	mov		ebx, edi		// get the destination address

	cmp		ecx, 12			// test for small # of pixels
	jb	    copytrail		// just do byte copy if # pixels is small

	and		ebx, 3			// compute the leading count
	jz		copybody		// copy body if leading count is zero

	sub		eax, ebx		// subtract leading count from run count
	mov		ecx, ebx		// prepare ecx with leading count

	rep		movsb			// copy leading pixels

	mov		ecx, eax		// retrieve count

copybody:
	shr		ecx, 2			// compute dword count
	and		eax, 3			// precompute trail count

	rep		movsd			// copy 4-pixel chunks

	mov		ecx, eax		// get trail count

copytrail:
	rep		movsb			// copy trailing pixels

	xor		eax, eax		// clear eax

nocopy:
	add		edx, eax		// cc += n	(n is 0 if copied)
	add		esi, eax		// sp += n

	jmp		colloopstart

rowloopend:
	mov		eax, lbeg		// eax = lbeg
	mov		edi, dline		// dp = dline + LPITCH

	mov		edx, lend		// edx = lend
	add		eax, 4			// lbeg ++

	add 	edi, LPITCH		// add pitch to edi
	mov		lbeg, eax		// store new lbeg

	jmp		rowloopstart	// do next loop

endoffunction:
	nop
}	
}	//	DrawDRleClipped


//	x is passed in ecx
//	y is passed in edx
void __fastcall DrawWRleClipped( DWORD x, DWORD y, BYTE * buf, RECT rc )
{
	WORD  * lbeg;
	WORD  * lend;
	BYTE  * dline;

__asm
{
	imul	edx, LPITCH		// edx = y * LPITCH								// NP	10

	add		edx, ecx		// edx = edx + x								// U
	mov		eax, rc.top		// lbeg = buf + 4 + rc.top * sizeof(DWORD)		//  V 

	mov		ecx, rc.bottom	// lend = buf + 4 + rc.bottom * sizeof(DWORD)	// U
	add		edx, SCRPTR		// edx = edx + SCRPTR							//  V

	mov		ebx, buf		// ebx = buf									// U
	mov		edi, edx		// edi (dp) = edx (SCRPTR + y*LPITCH + x)		//  V

	lea		edx, DWORD PTR [ebx + ecx * 2 + 4]	// lend						// U   !AGI
	lea		eax, DWORD PTR [ebx + eax * 2 + 4]	// lbeg						//  V

	mov		lend, edx														// U
	mov		lbeg, eax														//  V

rowloopstart:
	cmp		edx, eax		// if ( lend <= lbeg )							// U
	jbe		endoffunction	//   goto end of function						//  V

	mov		dline, edi		// dline = dp									// U
	xor     ecx, ecx		// ecx = 0										//  V

	mov		esi, buf		// sp = buf + *lbeg								// U
	mov		cx, WORD PTR [eax]		// load line offset contents (*lbeg)	//  V

	xor		edx, edx		// edx = cc = 0									// U
	add		esi, ecx														//  V

	cmp		edx, rc.right	// if ( cc >= ce )								// U
	jae		rowloopend		//   goto rowloopend							//  V

colloopstart:
	xor		eax, eax		// zero eax										// U
	mov		ecx, edx		// ecx = cc										//  V

	mov		al, BYTE PTR [esi]	// n = *sp++								// U
	mov		ebx, rc.left	// store a temp of rc.left						//  V

	inc		esi				// load a byte from sp							// U
	add		ecx, eax		// ecx = cc + n									//  V

	cmp		edx, ebx		// if ( cc < cs )								// U
	jb		midline			//   goto midline								//  V

	add		edi, eax		// dp += n										// U
	jmp	short transpartend													//  V

midline:
	sub		ecx, ebx		// if ( cc + n < cs )							// U
	jb		transpartend	//   goto transpartend							//  V	PV

	add		edi, ecx		// dp += cc + n - cs							// U

transpartend:
	add		edx, eax		// cc += n										// U
	xor		eax, eax		// zero eax										//  V

	cmp		edx, rc.right	// if ( cc >= ce )								// U
	jae		rowloopend		//   goto rowloopend							//  V   PV

	mov		al, BYTE PTR [esi]	// n = *sp  (al = n)						// U
	mov		ecx, edx		// ecx = cc										//  V

	inc     esi				// sp++											// U
	add		ecx, eax		// ecx = cc + n									//  V

	test	eax, eax		// if ( n = 0 )									// U
	je		nocopy			//   goto nocopy								//  V

	mov		ebx, rc.left	// get a copy of rc.left						// U
	cmp		ecx, ebx		// if ( cc + n  <= cs )							//  V

	jbe		nocopy			//   goto nocopy								// U	PV

	mov		eax, edx		// eax = cc										// U
	sub		ebx, edx		// ms = cs - cc									//  V

	jae		complen			// if ( ms > 0 ) goto complen					// U	PV
	xor     ebx, ebx		// ms = 0										// U

complen:
	add		eax, ebx		// eax = cc + ms								// U
	cmp		ecx, rc.right	// if ( cc + n <= ce )							//  V	2
	jbe		copyray			//   goto copyray								// U	PV
	mov		ecx, rc.right	// mn = ce;										// U

copyray:
	sub		ecx, eax		// mn -= cc + ms
	add		esi, ebx		// sp += ms

	add		edx, ebx		// cc += ms
	mov		eax, ecx		// save run count

	add		edx, ecx		// cc += mn
	mov		ebx, edi		// get the destination address

	cmp		ecx, 12			// test for small # of pixels
	jb	    copytrail		// just do byte copy if # pixels is small

	and		ebx, 3			// compute the leading count
	jz		copybody		// copy body if leading count is zero

	sub		eax, ebx		// subtract leading count from run count
	mov		ecx, ebx		// prepare ecx with leading count

	rep		movsb			// copy leading pixels

	mov		ecx, eax		// retrieve count

copybody:
	shr		ecx, 2			// compute dword count
	and		eax, 3			// precompute trail count

	rep		movsd			// copy 4-pixel chunks

	mov		ecx, eax		// get trail count

copytrail:
	rep		movsb			// copy trailing pixels

	xor		eax, eax		// clear eax

nocopy:
	add		edx, eax		// cc += n	(n is 0 if copied)
	add		esi, eax		// sp += n

	jmp		colloopstart

rowloopend:
	mov		eax, lbeg		// eax = lbeg
	mov		edi, dline		// dp = dline + LPITCH

	mov		edx, lend		// edx = lend
	add		eax, 2			// lbeg ++

	add 	edi, LPITCH		// add pitch to edi
	mov		lbeg, eax		// store new lbeg

	jmp		rowloopstart	// do next loop

endoffunction:
	nop
}	
}	//	DrawWRleClipped


//	x is passed in ecx
//	y is passed in edx
void __fastcall DrawTRleClipped( DWORD x, DWORD y, BYTE * buf, RECT rc, BYTE * ttable )
{
	WORD  * lbeg;
	WORD  * lend;
	BYTE  * dline;

__asm
{
	imul	edx, LPITCH		// edx = y * LPITCH								// NP	10

	add		edx, ecx		// edx = edx + x								// U
	mov		eax, rc.top		// lbeg = buf + 4 + rc.top * sizeof(DWORD)		//  V 

	mov		ecx, rc.bottom	// lend = buf + 4 + rc.bottom * sizeof(DWORD)	// U
	add		edx, SCRPTR		// edx = edx + SCRPTR							//  V

	mov		ebx, buf		// ebx = buf									// U
	mov		edi, edx		// edi (dp) = edx (SCRPTR + y*LPITCH + x)		//  V

	lea		edx, DWORD PTR [ebx + ecx * 2 + 4]	// lend						// U   !AGI
	lea		eax, DWORD PTR [ebx + eax * 2 + 4]	// lbeg						//  V

	mov		lend, edx														// U
	mov		lbeg, eax														//  V

rowloopstart:
	cmp		edx, eax		// if ( lend <= lbeg )							// U
	jbe		endoffunction	//   goto end of function						//  V

	mov		dline, edi		// dline = dp									// U
	xor     ecx, ecx		// ecx = 0										//  V

	mov		esi, buf		// sp = buf + *lbeg								// U
	mov		cx, WORD PTR [eax]		// load line offset contents (*lbeg)	//  V

	xor		edx, edx		// edx = cc = 0									// U
	add		esi, ecx														//  V

	cmp		edx, rc.right	// if ( cc >= ce )								// U
	jae		rowloopend		//   goto rowloopend							//  V

colloopstart:
	xor		eax, eax		// zero eax										// U
	mov		ecx, edx		// ecx = cc										//  V

	mov		al, BYTE PTR [esi]	// n = *sp++								// U
	mov		ebx, rc.left	// store a temp of rc.left						//  V

	inc		esi				// load a byte from sp							// U
	add		ecx, eax		// ecx = cc + n									//  V

	cmp		edx, ebx		// if ( cc < cs )								// U
	jb		midline			//   goto midline								//  V

	add		edi, eax		// dp += n										// U
	jmp	short transpartend													//  V

midline:
	sub		ecx, ebx		// if ( cc + n < cs )							// U
	jb		transpartend	//   goto transpartend							//  V	PV

	add		edi, ecx		// dp += cc + n - cs							// U

transpartend:
	add		edx, eax		// cc += n										// U
	xor		eax, eax		// zero eax										//  V

	cmp		edx, rc.right	// if ( cc >= ce )								// U
	jae		rowloopend		//   goto rowloopend							//  V   PV

	mov		al, BYTE PTR [esi]	// n = *sp  (al = n)						// U
	mov		ecx, edx		// ecx = cc										//  V

	inc     esi				// sp++											// U
	add		ecx, eax		// ecx = cc + n									//  V

	test	eax, eax		// if ( n = 0 )									// U
	je		nocopy			//   goto nocopy								//  V

	mov		ebx, rc.left	// get a copy of rc.left						// U
	cmp		ecx, ebx		// if ( cc + n  <= cs )							//  V

	jbe		nocopy			//   goto nocopy								// U	PV

	mov		eax, edx		// eax = cc										// U
	sub		ebx, edx		// ms = cs - cc									//  V

	jae		complen			// if ( ms > 0 ) goto complen					// U	PV
	xor     ebx, ebx		// ms = 0										// U

complen:
	add		eax, ebx		// eax = cc + ms								// U
	cmp		ecx, rc.right	// if ( cc + n <= ce )							//  V	2
	jbe		copyray			//   goto copyray								// U	PV
	mov		ecx, rc.right	// mn = ce;										// U

copyray:
	sub		ecx, eax		// mn -= cc + ms
	add		esi, ebx		// sp += ms

	add		edx, ebx		// cc += ms
	mov		ebx, ttable		// ebx = trans_table offset

	add		edx, ecx		// cc += mn
	xor		eax, eax		// clear eax

startray:
	test	ecx, ecx		// use cx as loop counter
	jz		endray

	mov		al, [esi]		// load source byte
	inc		esi

	inc		edi
	dec		ecx

	mov		al, [ebx + eax] // get translated byte	
	mov		BYTE PTR [edi-1], al	// write destination byte

	jmp		startray

endray:
	xor		eax, eax		// clear eax

nocopy:
	add		edx, eax		// cc += n	(n is 0 if copied)
	add		esi, eax		// sp += n

	jmp		colloopstart

rowloopend:
	mov		eax, lbeg		// eax = lbeg
	mov		edi, dline		// dp = dline + LPITCH

	mov		edx, lend		// edx = lend
	add		eax, 2			// lbeg ++

	add 	edi, LPITCH		// add pitch to edi
	mov		lbeg, eax		// store new lbeg

	jmp		rowloopstart	// do next loop

endoffunction:
	nop
}	
}	//	DrawTRleClipped


//	x is passed in ecx
//	y is passed in edx
void __fastcall DrawSRleClippedDither( DWORD x, DWORD y, BYTE * buf, RECT rc )
{
}	//	DrawSRleClippedDither


//	x is passed in ecx
//	y is passed in edx
void __fastcall DrawSRleClippedShade( DWORD x, DWORD y, BYTE * buf, RECT rc)
{
	WORD  * lbeg;
	WORD  * lend;
	BYTE  * dline;
	DWORD   cc;
	DWORD	count;
//	DWORD   vara;

__asm
{
	imul	edx, LPITCH		// edx = y * LPITCH								// NP	10

	add		edx, ecx		// edx = edx + x								// U
	mov		eax, rc.top		// lbeg = buf + 4 + rc.top * sizeof(DWORD)		//  V 

	mov		ecx, rc.bottom	// lend = buf + 4 + rc.bottom * sizeof(DWORD)	// U
	add		edx, SCRPTR		// edx = edx + SCRPTR							//  V

	mov		ebx, buf		// ebx = buf									// U
	mov		edi, edx		// edi (dp) = edx (SCRPTR + y*LPITCH + x)		//  V

	lea		edx, DWORD PTR [ebx + ecx * 2 + 4]	// lend						// U   !AGI
	lea		eax, DWORD PTR [ebx + eax * 2 + 4]	// lbeg						//  V

	mov		lend, edx														// U
	mov		lbeg, eax														//  V

	align	2
rowloopstart:
	cmp		edx, eax		// if ( lend <= lbeg )							// U
	jbe		endoffunction	//   goto end of function						//  V

	mov		dline, edi		// dline = dp									// U
	xor     ecx, ecx		// ecx = 0										//  V

	mov		esi, buf		// sp = buf + *lbeg								// U
	mov		cx, WORD PTR [eax]		// load line offset contents (*lbeg)	//  V

	xor		edx, edx		// edx = cc = 0									// U
	add		esi, ecx														//  V

	cmp		edx, rc.right	// if ( cc >= ce )								// U
	jae		rowloopend		//   goto rowloopend							//  V

	align	2
colloopstart:
	xor		eax, eax		// zero eax										// U
	mov		ecx, edx		// ecx = cc										//  V

	mov		al, BYTE PTR [esi]	// n = *sp++								// U
	mov		ebx, rc.left	// store a temp of rc.left						//  V

	inc		esi				// load a byte from sp							// U
	add		ecx, eax		// ecx = cc + n									//  V

	cmp		edx, ebx		// if ( cc < cs )								// U
	jb		midline			//   goto midline								//  V

	add		edi, eax		// dp += n										// U
	jmp	short transpartend													//  V

midline:
	sub		ecx, ebx		// if ( cc + n < cs )							// U
	jb		transpartend	//   goto transpartend							//  V	PV

	add		edi, ecx		// dp += cc + n - cs							// U

transpartend:
	add		edx, eax		// cc += n										// U
	xor		eax, eax		// zero eax										//  V

	cmp		edx, rc.right	// if ( cc >= ce )								// U
	jae		rowloopend		//   goto rowloopend							//  V   PV

	mov		al, BYTE PTR [esi]	// n = *sp  (al = n)						// U
	mov		ecx, edx		// ecx = cc										//  V

	inc     esi				// sp++											// U
	add		ecx, eax		// ecx = cc + n									//  V

	test	eax, eax		// if ( n = 0 )									// U
	je		nocopy			//   goto nocopy								//  V

	mov		ebx, rc.left	// get a copy of rc.left						// U
	cmp		ecx, ebx		// if ( cc + n  <= cs )							//  V

	jbe		nocopy			//   goto nocopy								// U	PV

	mov		eax, edx		// eax = cc										// U
	sub		ebx, edx		// ms = cs - cc									//  V

	jae		complen			// if ( ms > 0 ) goto complen					// U	PV
	xor     ebx, ebx		// ms = 0										// U

complen:
	add		eax, ebx		// eax = cc + ms								// U
	cmp		ecx, rc.right	// if ( cc + n <= ce )							//  V	2
	jbe		drawray			//   goto drawray								// U	PV
	mov		ecx, rc.right	// mn = ce;										// U

drawray:
	sub		ecx, eax		// mn -= cc + ms
	add		edx, ebx		// cc += ms

	xor		eax, eax		// save run count
	add		edx, ecx		// cc += mn

//start drawing ray!
	mov		cc, edx							// store cc
	mov		ebx, edi

	cmp		ecx, 0							// don't copy an empty ray
	je		nocopy

	and		edi, NOT 3						// compute destination word address
	and		ebx, 3							// compute destination offset

	mov		edx, PShadeTable

	cmp		ebx, 0							// if offset = 0 
	je		shadebody						// goto whole word shading

	cmp		ebx, 1							// if offset <> 1
	jne		lead2							// check if offset = 2

	cmp		ecx, 3							// if count >= 3, copy 3 bytes
	jae		short l13

	cmp		ecx, 1							// if count = 2, copy 2 bytes
	jne		short l12

											// copy 1 byte with offset 1
	xor		ebx, ebx
	xor		eax, eax

	mov		bl, BYTE PTR [edi + 1]
	add		edi, 2

	mov		bl, BYTE PTR [edx + ebx]
	mov		edx, cc

	mov		[edi-1], bl
	jmp		colloopstart
	
	align	2
l12:										// copy 2 bytes with offset 1
	mov		ax, WORD PTR [edi+1]
	mov		count, ecx

	xor		ebx, ebx
	xor		ecx, ecx

	mov		bl, al
	mov		cl, ah

	add		edi, 3
	xor		eax, eax

	mov		bl, BYTE PTR [edx + ebx]
	mov		cl, BYTE PTR [edx + ecx]

	shl		ebx, 8
	mov		edx, count
	
	add		ebx, ecx
	sub		edx, 2

	mov		ecx, edx
	mov		edx, cc

	mov		WORD PTR [edi-2], bx
	jmp		colloopstart					// that's all

	align	2
l13:										// copy 3 bytes with offset 1
	mov		eax, [edi]
	xor		ebx, ebx

	mov		count, ecx
	mov		bl, ah

	mov		ah, BYTE PTR [edx + ebx]
	xor		ecx, ecx

	ror		eax, 16

	mov		bl, ah
	mov		cl, al

	mov		ah, BYTE PTR [edx + ebx]
	mov		al, BYTE PTR [edx + ecx]

	ror		eax, 16

	mov		ecx, count
	mov		[edi], eax

	sub		ecx, 3							// subtract from total count
	add		edi, 4

	jmp		shadebody

/*
	mov		eax, [edi]						// get the dword
	mov		count, ecx						// store count

	mov		ebx, eax						// copy eax to ebx
	and		eax, 0x0ff						// store unused byte for eax

	mov		vara, eax						// store it permanently
	mov		eax, ebx						// recover the byte

	mov		ecx, ebx						// copy eax to ecx
	and		eax, 0x0000ff00					// mask for ah of loword

	shr		eax, 8							// move to al position
	and		ecx, 0x00ff0000					// mask for cl of hiword

	shr		ecx, 16							// move to cl position
	and		ebx, 0xff000000					// mask for bh of hiword

	shr		ebx, 24							// move to bl position
	mov		eax, DWORD PTR [edx + eax]		// do table lookup

	mov		ecx, DWORD PTR [edx + ecx]      // do table lookup
	and		eax, 0xff						// mask for the shade

	shl		eax, 8							// move back to ah of loword
	mov		ebx, DWORD PTR [edx + ebx]		// do table lookup

	or		eax, vara						// or from memory
	and		ecx, 0xff						// mask for the shade

	shl		ecx, 16							// move back into position
	add		edi, 4							// increment destination ptr

	shl		ebx, 24							// no need to mask!
	or		eax, ecx						// move ecx into eax

	mov		ecx, count						// get the count
	or		eax, ebx						// or into position

	mov		[edi-4], eax					// write to video
	sub		ecx, 3							// subtract

	xor		ebx, ebx
	jmp 	shadebody						// there could be more
*/
	align	2
lead2:
	cmp		ebx, 2							// if offset <> 2
	jne		lead3							// offset must be 3

	cmp		ecx, 1							// if count <> 1
	jne		l22								// count must be 2
											// copy 1 byte with offset 2
	mov		bl, [edi+2]
	mov		bl, BYTE PTR [edx + ebx]
	mov		[edi+2], bl
	add		edi, 3
	mov		edx, cc

	jmp		colloopstart					// that's all!
	
	align	2
l22:										// count is 2 with offset 2
	mov		ax, [edi+2]
	mov		count, ecx

	xor		ebx, ebx
	xor		ecx, ecx

	mov		bl, al
	mov		cl, ah

	mov		al, BYTE PTR [edx + ebx]

	mov		ah, BYTE PTR [edx + ecx]
	mov		ecx, count

	mov		[edi+2], ax
	sub		ecx, 2

	add		edi, 4
	jmp		shadebody						// there could be more!

	align	2
lead3:										// offset is 3, copy 1 byte
	xor		ebx, ebx
	sub		ecx, 1

	mov		bl, BYTE PTR [edi+3]

	mov		bl, BYTE PTR [edx + ebx]

	mov		[edi+3], bl
	add		edi, 4

	align	2
shadebody:									// shade in up to 4 byte aligned 
	cmp		ecx, 3							// is count <= 3?
	jbe		short trailer

	mov		count, ecx
	xor		ebx, ebx

	mov		eax, [edi]
	xor		ecx, ecx

	mov		bl, al
	mov		cl, ah

	mov		al, BYTE PTR [edx + ebx]

	mov		ah,	BYTE PTR [edx + ecx]

	ror		eax, 16

	mov		bl, al
	mov		cl, ah

	mov		al, BYTE PTR [edx + ebx]

	mov		ah, BYTE PTR [edx + ecx]

	rol		eax, 16

	mov		ecx, count
	mov		[edi], eax

	add		edi, 4
	sub		ecx, 4

	jmp		shadebody						// loop until done

	align	2
trailer:	
	cmp		ecx, 3							// doesn't add any time?
	jb	 	short trail2					// see if count is 3
	
	mov		eax, [edi]
	xor		ebx, ebx

	mov		bl, al							// shade 3 bytes
	xor		ecx, ecx

	mov		al, BYTE PTR [edx + ebx]
	add		edi, 3

	ror     eax, 8

	mov		bl, al
	mov		cl, ah

	mov		al, BYTE PTR [edx + ebx]

	mov		ah, BYTE PTR [edx + ecx]

	rol		eax, 8

	mov		[edi-3], eax
	mov		edx, cc

	jmp		colloopstart

	align	2
trail2:
	cmp		ecx, 1
	je		short trail1
	jb		endray

	mov		eax, [edi]						// trail is 2
	add		edi, 2

	xor		ebx, ebx
	xor		ecx, ecx

	mov		bl, al
	mov		cl, ah

	mov		al, BYTE PTR [edx + ebx]

	mov		ah, BYTE PTR [edx + ecx]
	mov		edx, cc

	mov		[edi-2], eax
	jmp		colloopstart

	align	2
trail1:										// trail is 1
	xor		eax, eax

	mov		al, [edi]
	add		edi, 1

	mov		al, BYTE PTR [edx + eax]
	mov		edx, cc

	mov		BYTE PTR [edi-1], al
	jmp		colloopstart

	align	2
endray:
	xor 	eax, eax						// eax = 0
	mov		edx, cc							// restore column count

	align	2
nocopy:
	add		edx, eax		// cc += n	(n is 0 if copied)
	jmp		colloopstart

	align	2
rowloopend:
	mov		eax, lbeg		// eax = lbeg
	mov		edi, dline		// dp = dline + LPITCH

	mov		edx, lend		// edx = lend
	add		eax, 2			// lbeg ++

	add 	edi, LPITCH		// add pitch to edi
	mov		lbeg, eax		// store new lbeg

	jmp		rowloopstart	// do next loop

endoffunction:
	nop
}	
	return;
}	//	DrawSRleClippedShade


void __fastcall DrawRleChar( DWORD x, DWORD y, BYTE * buf, BYTE c )
{
	__asm
	{
	mov		esi, buf		// esi = buf
	mov		ebx, LPITCH
	imul	edx, ebx		// edx = y * LPITCH
	mov		ah,  BYTE PTR [esi + 1]		// ah = height of char
	add		edx, SCRPTR		// edx = edx + SCRPTR
	add		esi, 2			// point to data
	add		edx, ecx		// edx = edx + x
	xor		ecx, ecx		// clear ecx

row_loop:
	mov		edi, edx		// get destination address
	mov		al, c			// al = c
col_loop:
	mov		cl, BYTE PTR [esi]		// get # transparent pixels
	add		esi, 2			// increment sp
	add		edi, ecx		// skip transparent pixels
	mov		cl, BYTE PTR [esi-1]	// get # filled pixels

	rep		stosb			// fill bytes
	cmp		byte ptr [esi], 0xff	// check for end of line
	jne		col_loop		// col loop

	inc		esi				// increment for line end marker
	add		edx, ebx		// edx = edx + LPITCH
	dec		ah				// decrement height
	jnz		row_loop		// row loop
	}
}	//	DrawRleChar;


//	x is passed in ecx
//	y is passed in edx
void __fastcall DrawSRleClippedColor( DWORD x, DWORD y, BYTE * buf, RECT rc, BYTE color)
{
	WORD  * lbeg;
	WORD  * lend;
	BYTE  * dline;

__asm
{
	imul	edx, LPITCH		// edx = y * LPITCH								// NP	10

	add		edx, ecx		// edx = edx + x								// U
	mov		eax, rc.top		// lbeg = buf + 4 + rc.top * sizeof(DWORD)		//  V 

	mov		ecx, rc.bottom	// lend = buf + 4 + rc.bottom * sizeof(DWORD)	// U
	add		edx, SCRPTR		// edx = edx + SCRPTR							//  V

	mov		ebx, buf		// ebx = buf									// U
	mov		edi, edx		// edi (dp) = edx (SCRPTR + y*LPITCH + x)		//  V

	lea		edx, DWORD PTR [ebx + ecx * 2 + 4]	// lend						// U   !AGI
	lea		eax, DWORD PTR [ebx + eax * 2 + 4]	// lbeg						//  V

	mov		lend, edx														// U
	mov		lbeg, eax														//  V

	align	2
rowloopstart:
	cmp		edx, eax		// if ( lend <= lbeg )							// U
	jbe		endoffunction	//   goto end of function						//  V

	mov		dline, edi		// dline = dp									// U
	xor     ecx, ecx		// ecx = 0										//  V

	mov		esi, buf		// sp = buf + *lbeg								// U
	mov		cx, WORD PTR [eax]		// load line offset contents (*lbeg)	//  V

	xor		edx, edx		// edx = cc = 0									// U
	add		esi, ecx														//  V

	cmp		edx, rc.right	// if ( cc >= ce )								// U
	jae		rowloopend		//   goto rowloopend							//  V

	align	2
colloopstart:
	xor		eax, eax		// zero eax										// U
	mov		ecx, edx		// ecx = cc										//  V

	mov		al, BYTE PTR [esi]	// n = *sp++								// U
	mov		ebx, rc.left	// store a temp of rc.left						//  V

	inc		esi				// load a byte from sp							// U
	add		ecx, eax		// ecx = cc + n									//  V

	cmp		edx, ebx		// if ( cc < cs )								// U
	jb		midline			//   goto midline								//  V

	add		edi, eax		// dp += n										// U
	jmp	short transpartend													//  V

midline:
	sub		ecx, ebx		// if ( cc + n < cs )							// U
	jb		transpartend	//   goto transpartend							//  V	PV

	add		edi, ecx		// dp += cc + n - cs							// U

transpartend:
	add		edx, eax		// cc += n										// U
	xor		eax, eax		// zero eax										//  V

	cmp		edx, rc.right	// if ( cc >= ce )								// U
	jae		rowloopend		//   goto rowloopend							//  V   PV

	mov		al, BYTE PTR [esi]	// n = *sp  (al = n)						// U
	mov		ecx, edx		// ecx = cc										//  V

	inc     esi				// sp++											// U
	add		ecx, eax		// ecx = cc + n									//  V

	test	eax, eax		// if ( n = 0 )									// U
	je		nocopy			//   goto nocopy								//  V

	mov		ebx, rc.left	// get a copy of rc.left						// U
	cmp		ecx, ebx		// if ( cc + n  <= cs )							//  V

	jbe		nocopy			//   goto nocopy								// U	PV

	mov		eax, edx		// eax = cc										// U
	sub		ebx, edx		// ms = cs - cc									//  V

	jae		complen			// if ( ms > 0 ) goto complen					// U	PV
	xor     ebx, ebx		// ms = 0										// U

complen:
	add		eax, ebx		// eax = cc + ms								// U
	cmp		ecx, rc.right	// if ( cc + n <= ce )							//  V	2
	jbe		drawray			//   goto drawray								// U	PV
	mov		ecx, rc.right	// mn = ce;										// U

drawray:
	sub		ecx, eax		// mn -= cc + ms
	add		edx, ebx		// cc += ms

	xor		eax, eax		// save run count
	add		edx, ecx		// cc += mn

//start drawing ray!
	
	cmp		ecx, 0							// don't copy an empty ray
	je		nocopy

	mov		al, color		// set the color
	rep		stosb			// fill bytes

	xor 	eax, eax						// eax = 0

	align	2
nocopy:
	add		edx, eax		// cc += n	(n is 0 if copied)
	jmp		colloopstart

	align	2
rowloopend:
	mov		eax, lbeg		// eax = lbeg
	mov		edi, dline		// dp = dline + LPITCH

	mov		edx, lend		// edx = lend
	add		eax, 2			// lbeg ++

	add 	edi, LPITCH		// add pitch to edi
	mov		lbeg, eax		// store new lbeg

	jmp		rowloopstart	// do next loop

endoffunction:
	nop
}	
	return;
}	//	DrawSRleClippedColor


//	Translate a bitmap to a RLE w/ DWORD line table
DWORD BitmapToDRle(BYTE * pBMStart, BYTE ** rle, int width, int height, COLORREF xpc, BYTE *trans_table)
{
	int    j, count;					// bitmap column, row, state, count
	DWORD  *table;						// table pointer within temporary buffer
	BYTE   buf[200000];					// temporary buffer for storing rle
	BYTE   *dp, *sp, *spEnd, *spStart;  // buffer pointer, source pointer
	DWORD  sz = 0;
	LONG   lPitchBM;

	dp = buf;							// set destination pointer to buffer
	lPitchBM = ( width + sizeof(LONG) - 1 ) & ~3;
	if ( height > 0 )					// handle top-down & bottom-up bitmaps
	{
		sp = pBMStart + (height - 1) * lPitchBM;
		lPitchBM = -lPitchBM;
	}
	else
	{
		height = -height;
		sp = pBMStart;
	}
	*(WORD *)dp = width;				// write width & height
	dp += sizeof(WORD);
	*(WORD *)dp = height;
	dp += sizeof(WORD);
	table = (DWORD *)dp;
	dp += height * sizeof(DWORD);		// jump past line table
	xpc = *sp;
	height;

	j = 0;
	while (j < height)
	{
		table[j] = dp - buf;
		spStart = sp;
		spEnd = sp + width;
		while (TRUE)
		{
			count = 0;
			while (sp != spEnd && *sp == xpc && count < 255)
			{
				sp++;
				count++;
			}
			*dp++ = count;
			
			count = 0;
			while (sp != spEnd && *sp != xpc && count < 255)
			{
				sp++;
				count++;
			}

			*dp++ = count;
			if (count > 0)
			{
				memxlat( dp, sp-count, trans_table, count );
				dp += count;
			}

			if (sp == spEnd)
				break;
		}
		j++;
		sp = spStart + lPitchBM;
	}

	sz = dp - buf;
	*rle = (BYTE *)malloc(sz);
	CopyMemory(*rle, buf, sz);
	return (sz);
}	//	BitmapToDRle



//	Translate a bitmap to a RLE w/ DWORD line table
DWORD BitmapToWRle(BYTE * pBMStart, BYTE ** rle, int width, int height, DWORD xpc, BYTE *trans_table)
{
	int    j, count;					// bitmap column, row, state, count
	WORD  *table;						// table pointer within temporary buffer
	BYTE   buf[200000];					// temporary buffer for storing rle
	BYTE   *dp, *sp, *spEnd, *spStart;  // buffer pointer, source pointer
	DWORD  sz = 0;
	LONG   lPitchBM;

	dp = buf;							// set destination pointer to buffer
	lPitchBM = ( width + sizeof(LONG) - 1 ) & ~3;
	if ( height > 0 )					// handle top-down & bottom-up bitmaps
	{
		sp = pBMStart + (height - 1) * lPitchBM;
		lPitchBM = -lPitchBM;
	}
	else
	{
		height = -height;
		sp = pBMStart;
	}
	*(WORD *)dp = width;				// write width & height
	dp += sizeof(WORD);
	*(WORD *)dp = height;
	dp += sizeof(WORD);
	table = (WORD *)dp;
	dp += height * sizeof(WORD);		// jump past line table
	xpc = *sp;
	height;

	j = 0;
	while (j < height)
	{
		table[j] = dp - buf;
		spStart = sp;
		spEnd = sp + width;
		while (TRUE)
		{
			count = 0;
			while (sp != spEnd && *sp == xpc && count < 255)
			{
				sp++;
				count++;
			}
			*dp++ = count;
			
			count = 0;
			while (sp != spEnd && *sp != xpc && count < 255)
			{
				sp++;
				count++;
			}

			*dp++ = count;
			if (count > 0)
			{
				memxlat( dp, sp-count, trans_table, count );
				dp += count;
			}

			if (sp == spEnd)
				break;
		}
		j++;
		sp = spStart + lPitchBM;
	}

	sz = dp - buf;
	*rle = (BYTE *)malloc(sz);
	CopyMemory(*rle, buf, sz);
	return (sz);
}	//	BitmapToWRle


DWORD TranslateWRleBits( BYTE* pDest,	//	First byte in dest data.
				BYTE* pSrc,				//	First byte in source data.
				int	height,				//	Number of lines in image.
				BYTE* table,			//	translation table
				DWORD maxsize )
{
	int y = 0;
	BYTE *dp, *sp;
	BYTE n;
	WORD count, width;

	width = *(WORD*)(pSrc);
	memcpy( pDest, pSrc, maxsize );

	if (table == NULL)
		return( maxsize );

	while( y < height )
	{
		dp = pDest + *(WORD *)(pDest + 2 * y + 4);
		sp = pSrc + *(WORD *)(pSrc + 2 * y + 4);
		count = 0;

		while (count < width)
		{
			n = *dp++;							// # transparent pixels
			count += n;
			n = *dp++;							// # color pixels
			sp += 2;

			if (count >= width)
				break;

			//	translate color pixels
			if( n > 0 )	
			{
				memxlat( dp, sp, table, n );
				dp += n;
				sp += n;
				count += n;
			}
		}
		y++;
	}

	return (maxsize);
}	// TranslateWRleBits



//	Copy RLE bitmap data to memory location specified, translating for palette
//	RLE format:
//	{
//		(BYTE)		# of transparent pixels (never larger than 254)
//		(BYTE)		# of non-transparent pixels, n (n never larger than 254)
//		(n BYTES)	non-transparent pixel values
//	}
//	Repeat, until value of 0xFF in the first field indicates new line.
DWORD TranslateRLEBitmap( BYTE* pDest,	//	First byte in dest data.
				BYTE* pSrc,				//	First byte in source data.
				int	height,				//	Number of lines in image.
				BYTE table[256],		//	translation table
				DWORD maxsize )
{
	int y = 0;
	int size = 0;

	while( y < height )
	{
		*pDest++ = *pSrc++;						// # transparent pixels
		char qRun = *pDest++ = *pSrc++;			// # color pixels
		size += 2;

		//	translate color pixels
		if( qRun )	{
			size += qRun;
			ASSERT(size < (int)maxsize);

			memxlat( pDest, pSrc, table, qRun );
			pDest += qRun;
			pSrc += qRun;
		}

		if( *pSrc == 0xFF )
		{
			*pDest++ = *pSrc++;			// end of line
			y++;
			size++;
		}	
	}

	ASSERT(size == (int)maxsize);
	return (size);
}	// TranslateRLEBitmap


//	Create RLE bitmap data at memory location specified, translating for palette
//	RLE format:
//	{
//		(BYTE)		# of transparent pixels (never larger than 254)
//		(BYTE)		# of non-transparent pixels, n (n never larger than 254)
//		(n BYTES)	non-transparent pixel values
//	}
//	Repeat, until value of 0xFF in the first field indicates new line.
//  assumes that bitmap (source) pitch is the width, padded to a LONG boundary
//  returns size of RLE data in bytes
DWORD TranslateBitmapToRLE( BYTE* pDestStart,	//	First byte in dest data.
				BYTE* pBMStart,				//	First byte in source data.
				int width,					//  Number of bytes per line in source image
				int	height,					//	Number of lines in source image.
				DWORD xpc,					//  transparent color index (0-255)
				BYTE table[256],			//	translation table
				DWORD maxsize)
{
	BYTE*	pSrc;
	BYTE*	pDest = pDestStart;
	int		y = 0;
	long	lPitchBM = (width + sizeof(LONG) - 1) & ~3;
	BYTE	bxpc = (BYTE) xpc;
	BYTE*	pLine;
	BYTE*	pLineEnd;
	BYTE*	pPixelStart;
	BYTE	pixels;
	DWORD	size = 0;

	if (height > 0)	{	// bottom-up bitmap
		pSrc = pBMStart + (height - 1) * lPitchBM;	// beginning of last line of source
		lPitchBM = -lPitchBM;
	}
	else	{
		height = -height;
		pSrc = pBMStart;							// first source line
	}

	while( y < height )	{
		pLine = pSrc;
		pLineEnd = pLine + width;			//	one beyond line end
		while( TRUE )	{
			//	Count forward till we hit a non-transparent pixel.
			pixels = 0;
			while( pLine!=pLineEnd && *pLine==xpc && pixels<254 )	{
				pLine++;
				pixels++;
			}
			//	Write # of transparent pixels.
			*pDest++ = pixels;
			size += 1;
			ASSERT(size <= maxsize);

			//	Save starting location of non-transparent pixel set.
			pPixelStart = pLine;
			//	Count forward till we hit a transparent pixel.
			pixels = 0;
			while( pLine!=pLineEnd && *pLine!=xpc && pixels<254 )	{
				pLine++;
				pixels++;
			}
			//	Write # of non-transparent pixels.
			*pDest++ = pixels;
			//	Write non-transparent pixel values, if any
			//  Translate if a table exists, otherwise copy
			if( pixels )	{
				memxlat( pDest, pPixelStart, table, pixels );
				pDest += pixels;
			}
			size += pixels + 1;
			ASSERT(size <= maxsize);

			// if we reached the end of a line, mark it with an 0xFF value
			if( pLine == pLineEnd )	{
				*pDest++ = 0xFF;
				size += 1;
				ASSERT(size <= maxsize);
				break;
			}
		}
		y++;
		pSrc += lPitchBM;
	}

	return (size);
}	// TranslateBitmapToRLE



//************************************************************************
//	Transformation & Clipping Functions
//************************************************************************

//	Translate screen coordinates to world coordinates
void ScreenToWorld( SPOINT *pPoint )	
{
	pPoint->x += DisplayBox.x;
	pPoint->y += DisplayBox.y;
}	// ScreenToWorld


//  Translate world coordinates to screen coordinates 
void WorldToScreen( SPOINT *pPoint )	
{
	pPoint->x -= DisplayBox.x;
	pPoint->y -= DisplayBox.y;
}	// WorldToScreen


//  Translate a world coordinate line to screen coordinates
void WorldToScreenLine( SPOINT *pStart, SPOINT *pEnd )	
{
	pStart->x -= DisplayBox.x;
	pStart->y -= DisplayBox.y;
	pEnd->x   -= DisplayBox.x;
	pEnd->y   -= DisplayBox.y;
}	// WorldToScreenLine


//	Clip a screen coordinate line to the screen borders in y dimension only
BOOL ClipLine( SPOINT *pStart, SPOINT *pEnd )	
{
	RECT rc;

	rc.left = DisplayBox.x;
	rc.top = DisplayBox.y;
	rc.right = rc.left + DisplayBox.cx;
	rc.bottom = rc.top + DisplayBox.cy;
	return( ClipLine( *pStart, *pEnd, rc ) );
/*
	if( (!InBox( &DisplayBox, pStart )) && (!InBox( &DisplayBox, pEnd )) )
		return FALSE;

	if ( pStart->y >= (DisplayBox.y+DisplayBox.cy) )
		pStart->y = ((DisplayBox.y+DisplayBox.cy) - 1);

	if ( pEnd->y >= (DisplayBox.y+DisplayBox.cy) )
		pEnd->y = ((DisplayBox.y+DisplayBox.cy) - 1);

	if ( pStart->x >= (DisplayBox.x+DisplayBox.cx) )
		pStart->x = ((DisplayBox.x+DisplayBox.cx) - 1);

	if ( pEnd->x >= (DisplayBox.x+DisplayBox.cx) )
		pEnd->x = ((DisplayBox.x+DisplayBox.cx) - 1);
	return TRUE;
*/

}	// ClipLine


//  Clip end points of line to lie within screen area
void ScreenClipLine( SPOINT *pStart, SPOINT *pEnd )
{
	if ( (pEnd->x - pStart->x) > DisplayBox.cx )
		pEnd->x = (pStart->x + DisplayBox.cx);
	if ( (pEnd->y - pStart->y) > DisplayBox.cy )
		pEnd->y = (pStart->y + DisplayBox.cy);
}	// ScreenClipLine


//	Return TRUE if SPOINT is in RECT
BOOL InRect( RECT *pRect, SPOINT *pPos )	
{
	if (pPos->x < pRect->left)
		return FALSE;

	if (pPos->x >= pRect->right)
		return FALSE;

	if (pPos->y < pRect->top)
		return FALSE;

	if (pPos->y >= pRect->bottom)
		return FALSE;

	return TRUE;
}	// InRect


//	Return TRUE if SPOINT is in SBOX
BOOL InBox( SBOX *pBox, SPOINT *pPos )
{
	if (pPos->x < pBox->x)
		return FALSE;

	if (pPos->x >= pBox->x + pBox->cx)
		return FALSE;

	if (pPos->y < pBox->y)
		return FALSE;

	if (pPos->y >= pBox->y + pBox->cy)
		return FALSE;

	return TRUE;
}	// InBox


//  Return value clipped to min & max
LONG LongMinMax( LONG value, LONG min, LONG max )	
{
	if (value <= min)
		return min;

	if (value >= max)
		return max;

	return value;
}	// LongMinMax


//	Return value clipped to min & max
SHORT ShortMinMax( SHORT value, SHORT min, SHORT max )	
{
	if (value <= min)
		return min;

	if (value >= max)
		return max;

	return value;
}	// ShortMinMax


//  Clip an SPOINT to a RECT (Moves point to within RECT)
void ClipSPoint( SPOINT *ppoint, RECT *pBounds )	
{
	if (ppoint->x < (short)pBounds->left)
		ppoint->x = (short)pBounds->left;
	else if (ppoint->x >= (short)pBounds->right)
		ppoint->x = (short)pBounds->right - 1;

	if (ppoint->y < (short)pBounds->top )
		ppoint->y = (short)pBounds->top;
	else if (ppoint->y >= (short)pBounds->bottom)
		ppoint->y = (short)pBounds->bottom - 1;
}	// ClipSPoint


//	Clip an SPOINT to a RECT (Sets coordinate to -1)
void ValidateSPoint( SPOINT *ppoint, RECT *pBounds )	
{
	if ((ppoint->x < (short)pBounds->left) || (ppoint->x >= (short)pBounds->right))
		ppoint->x = -1;

	if ((ppoint->y < (short)pBounds->top ) || (ppoint->y >= (short)pBounds->bottom))
		ppoint->x = -1;
}	// ValidateSPoint


//  Return FALSE if a RECT given by offsets px & py is not within another RECT
//	for parital entries, modify RECT & offsets to represent on-screen RECT
BOOL ClipRectToGameWindow( RECT *prcSprite, LONG *px, LONG *py, RECT *pRectOut )
{
	RECT	rcImage,
			*pRect1,
			*pRect2;

	rcImage.left = prcSprite->left + *px;
	rcImage.right = prcSprite->right + *px;
	rcImage.top = prcSprite->top + *py;
	rcImage.bottom = prcSprite->bottom + *py;

	pRect1 = pClipRect;
	pRect2 = &rcImage;

	if (pRect1->left < pRect2->left)	
	{
		if (pRect1->right < pRect2->left)
			return FALSE;
		pRectOut->left = pRect2->left;
	}
	else	
	{
		if (pRect2->right < pRect1->left)
			return FALSE;
		pRectOut->left = pRect1->left;
	}

	pRectOut->right = min(pRect1->right, pRect2->right);
	if (pRectOut->left == pRectOut->right)
		return FALSE;

	if (pRect1->top < pRect2->top)	
	{
		if (pRect1->bottom < pRect2->top)
			return FALSE;
		pRectOut->top = pRect2->top;
	}
	else	
	{
		if (pRect2->bottom < pRect1->top)
			return FALSE;
		pRectOut->top = pRect1->top;
	}

	pRectOut->bottom = min(pRect1->bottom, pRect2->bottom);
	if (pRectOut->top == pRectOut->bottom)
		return FALSE;

	{
		LONG xdiff = *px;
		*px = pRectOut->left;
		pRectOut->left -= xdiff;
		pRectOut->right -= xdiff;
	}
	{
		LONG ydiff = *py;
		*py = pRectOut->top;
		pRectOut->top -= ydiff;
		pRectOut->bottom -= ydiff;
	}

	return TRUE;
}	// ClipRectToGameWindow


//	Clip a to b.  (a is modified).  Return TRUE if a is a valid rect.
BOOL ClipRect( RECT &a, RECT &b )
{
	if( a.left >= b.right || a.right <= b.left || 
		a.top >= b.bottom || a.bottom <= b.top )
		return FALSE;
	a.top = max( a.top, b.top );
	a.bottom = min( a.bottom, b.bottom );
	a.left = max( a.left, b.left );
	a.right = min( a.right, b.right );
	return TRUE;
}	//	ClipRect


//  Return TRUE if Rect1 intersects Rect2, bound RectOut by the intersection
BOOL RectIntersect(RECT *pRect1, RECT *pRect2, RECT *pRectOut)	
{
	RECT localRect;

	if (!pRectOut)
		pRectOut = &localRect;
	
	if (pRect1->left < pRect2->left)	
	{
		if (pRect1->right < pRect2->left)
			return FALSE;
		pRectOut->left = pRect2->left;
	}
	else	
	{
		if (pRect2->right < pRect1->left)
			return FALSE;
		pRectOut->left = pRect1->left;
	}

	pRectOut->right = min(pRect1->right, pRect2->right);

	if (pRect1->top < pRect2->top)	
	{
		if (pRect1->bottom < pRect2->top)
			return FALSE;
		pRectOut->top = pRect2->top;
	}
	else	
	{
		if (pRect2->bottom < pRect1->top)
			return FALSE;
		pRectOut->top = pRect1->top;
	}

	pRectOut->bottom = min(pRect1->bottom, pRect2->bottom);

	return TRUE;
}	// RectIntersect


//  Return TRUE if Box1 & Box2 intersect, bound BoxOut by intersection
BOOL BoxIntersect(SBOX *pBox1, SBOX *pBox2, SBOX *pBoxOut)	
{
	if (pBox1->x < pBox2->x)	
	{
		if (pBox1->x + pBox1->cx - 1 < pBox2->x)
			return FALSE;
		pBoxOut->x = pBox2->x;
	}
	else	
	{
		if (pBox2->x + pBox2->cx - 1 < pBox1->x)
			return FALSE;
		pBoxOut->x = pBox1->x;
	}

	pBoxOut->cx = min(pBox1->x + pBox1->cx, pBox2->x + pBox2->cx);
	pBoxOut->cx -= pBoxOut->x;

	if (pBox1->y < pBox2->y)	
	{
		if (pBox1->y + pBox1->cy - 1 < pBox2->y)
			return FALSE;
		pBoxOut->y = pBox2->y;
	}
	else	
	{
		if (pBox2->y + pBox2->cy - 1 < pBox1->y)
			return FALSE;
		pBoxOut->y = pBox1->y;
	}

	pBoxOut->cy = min(pBox1->y + pBox1->cy, pBox2->y + pBox2->cy);
	pBoxOut->cy -= pBoxOut->y;

	return TRUE;
}	// BoxIntersect


// true line clipping function (can return 0 if unable to clip)
int ClipLine( SPOINT &a, SPOINT &b, RECT &rc )
{
	int		i;
	float	m;

	// special case vertical lines
	if( a.x == b.x )
	{
		if( a.x < rc.left || a.x > rc.right )
			return 0;
		if( a.y <= rc.top && b.y <= rc.top )
			return 0;
		if( a.y >= rc.bottom && b.y >= rc.bottom )
			return 0;
		if( a.y < rc.top )
			a.y = (short)rc.top;
		else
		if( a.y > rc.bottom )
			a.y = (short)rc.bottom;
		if( b.y < rc.top )
			b.y = (short)rc.top;
		else
		if( b.y > rc.bottom )
			b.y = (short)rc.bottom;
		return 1;
	}

	if( a.x < rc.left )
	{
		if( b.x < rc.left )					// no intersect if both on same side
			return 0;
		m = (float)(b.y - a.y)/(float)(b.x - a.x);		// get line formula
		i = (int)(a.y + (rc.left - a.x) * m);	// compute y-axis intersect
		if( i < rc.top || i > rc.bottom )
			return 0;
		a.y = (short)i;						// found an intersection
		a.x = (short)rc.left;
	}
	else
	if( b.x < rc.left )
	{
		m = (float)(b.y - a.y)/(float)(b.x - a.x);
		i = (int)(b.y + (rc.left - b.x) * m);
		if( i < rc.top || i > rc.bottom )
			return 0;
		b.y = (short)i;						// found an intersection
		b.x = (short)rc.left;
	}

	if( a.x > rc.right )
	{
		if( b.x > rc.right )
			return 0;

		m = (float)(b.y - a.y)/(float)(b.x - a.x);
		i = (int)(b.y + (rc.right - b.x) * m);
		if( i < rc.top || i > rc.bottom )
			return 0;
		a.y = (short)i;
		a.x = (short)rc.right;
	}
	else
	if( b.x > rc.right )
	{
		m = (float)(b.y - a.y)/(float)(b.x - a.x);
		i = (int)(a.y + (rc.right - a.x) * m);
		if( i < rc.top || i > rc.bottom )
			return 0;
		b.y = i;
		b.x = (short)rc.right;
	}

	if( a.y < rc.top )
	{
		if( b.y < rc.top )
			return 0;
		m = (float)(b.x - a.x)/(float)(b.y - a.y);
		i = (int)(a.x + (rc.top - a.y) * m);
		if( i < rc.left || i > rc.right )
			return 0;
		a.y = (short)rc.top;
		a.x = i;
	}
	else
	if( b.y < rc.top )
	{
		m = (float)(b.x - a.x)/(float)(b.y - a.y);
		i = (int)(b.x + (rc.top - b.y) * m);
		if( i < rc.left || i > rc.right )
			return 0;
		b.y = (short)rc.top;
		b.x = i;
	}

	if( a.y > rc.bottom )
	{
		if( b.y > rc.bottom )
			return 0;
		m = (float)(b.x - a.x)/(float)(b.y - a.y);
		i = (int)(b.x + (rc.bottom - b.y) * m);
		if( i < rc.left || i > rc.right )
			return 0;
		a.y = (short)rc.bottom;
		a.x = (short)i;
	}
	else
	if( b.y > rc.bottom )
	{
		m = (float)(b.x - a.x)/(float)(b.y - a.y);
		i = (int)(a.x + (rc.bottom - a.y) * m);
		if( i < rc.left || i > rc.right )
			return 0;
		b.y = (short)rc.bottom;
		b.x = (short)i;
	}

	return 1;
}


//************************************************************************
//	Direct Draw color functions
//************************************************************************

//  Convert a RGB color to a physical color index, look at UL of surface if no color given
//	input:
//	  surface for default color
//	  rgb color to convert
//  output:
//	  palette index for RGB color
DWORD DDColorMatch(LPDIRECTDRAWSURFACE pdds, COLORREF rgb)
{
	HDC hdc;
    DWORD dw = CLR_INVALID;

	if (rgb == CLR_INVALID)	
	{
		if (pdds->GetDC(&hdc) == DD_OK)	
		{
			rgb = GetPixel(hdc, 0, 0);
			pdds->ReleaseDC(hdc);
		}
	}

	hdc = GetDC(NULL);
	dw = GetNearestPaletteIndex(current_palette.hpal, rgb);
	ReleaseDC( NULL, hdc);

    return dw;
}	// DDColorMatch


//	Convert a RGB color to a physical color index, look at UL of bitmap if no color given
//	input:
//	  bitmap to look at for default color
//	  rgb color to convert
//	output:
//	  palette index of RGB color
DWORD BitmapColorMatch(BITMAP *bm, COLORREF rgb)
{
    HDC hdc;
    DWORD dw;
	BYTE *bmBits;
	DWORD index;

	if (rgb == CLR_INVALID)			// look up default color
	{
		if (bm->bmHeight > 0)		// bottom-up bitmap : get index from last line
			index = (bm->bmHeight - 1) * ((bm->bmWidth + sizeof(LONG) - 1) & ~3);
		else
			index = 0;

		bmBits = (BYTE *)bm->bmBits;
		dw = (DWORD) bmBits[index];
	}
	else	
	{
		hdc = GetDC(NULL);
		dw = GetNearestPaletteIndex(current_palette.hpal, rgb);
		ReleaseDC( NULL, hdc);
	}

    return dw;
}	// BitmapColorMatch


//  Set a color key for a surface, given a RGB 
//	  - use UL pixel color if CLR_INVALID passed
//	input:
//	  surface to use to determine default color
//	  rgb to use as color key (can be CLR_INVALID)
void DDSetColorKey(LPDIRECTDRAWSURFACE pdds, COLORREF xpc)
{
    DDCOLORKEY          ddck;

    ddck.dwColorSpaceLowValue  = xpc;
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}	// DDSetColorKey



//************************************************************************
//	Direct Draw Point & Line drawing functions
//************************************************************************


enum ELockStatus {
	DDLS_OFF,
	DDLS_LOCKED,
	DDLS_UNLOCKED
};


ELockStatus	BACKBUFFER_LOCKSTATUS = DDLS_OFF;


//	Exchange the values of two ints
inline void exchange( int &a, int &b )
{
	int c;

	c = a;
	a = b;
	b = c;
}	//	exchange


//	This function locks the back buffer & sets the status flag
inline BOOL LockBackBufferLockComplex( void )
{
    DDSURFACEDESC	ddsd;
	HRESULT			ddrval;

	ASSERT( BACKBUFFER_LOCKSTATUS != DDLS_OFF );

	if( BACKBUFFER_LOCKSTATUS != DDLS_UNLOCKED )
		return TRUE;

	ddsd.dwSize = sizeof(DDSURFACEDESC);
	
	if ((ddrval = pBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)) != DD_OK)
	{
		return FALSE;
	}

	SCRPTR = (BYTE *)(ddsd.lpSurface);
	LPITCH = ddsd.lPitch;
	BACKBUFFER_LOCKSTATUS = DDLS_LOCKED;
	return TRUE;
}	//  LockBackBufferLockComplex


//  Call this function before drawing to the back buffer
BOOL InitBackBufferLockComplex( void )
{	
	if( BACKBUFFER_LOCKSTATUS != DDLS_OFF )
		return TRUE;

	BACKBUFFER_LOCKSTATUS = DDLS_UNLOCKED;
	return LockBackBufferLockComplex();
}	//  InitBackBufferLockComplex


//  Call this function after drawing to back buffer is complete
void FreeBackBufferLockComplex( void )
{
	if( BACKBUFFER_LOCKSTATUS == DDLS_OFF )
		return;

	if( BACKBUFFER_LOCKSTATUS == DDLS_LOCKED )
		pBackBuffer->Unlock(SCRPTR);
	BACKBUFFER_LOCKSTATUS = DDLS_OFF;
}	//	FreeBackBufferLockComplex


//  Draw a dot on the back buffer using color (DDCOLOR)
void DDPutPixel( int x, int y )
{
	ASSERT( x >= DefaultClipRect.left );
	ASSERT( y >= DefaultClipRect.top );
	ASSERT( x < DefaultClipRect.right );
	ASSERT( y < DefaultClipRect.bottom );

	if( !LockBackBufferLockComplex() )
		return;

	*(SCRPTR + y * LPITCH + x) = DDCOLOR;
}	//  DDPutPixel


//  Draw a vertical line on the back buffer using color (DDCOLOR)
void DDVLine( int x, int y1, int y2 )
{
	BYTE	*sptr, *eptr;

	if( y1 > y2 )
		exchange( y1, y2 );

	ASSERT( x >= DefaultClipRect.left );
	ASSERT( x < DefaultClipRect.right );
	ASSERT( y1 >= DefaultClipRect.top );
	ASSERT( y2 < DefaultClipRect.bottom );

	sptr = SCRPTR + y1 * LPITCH + x;
	eptr = sptr + LPITCH * (y2 - y1);

	if( !LockBackBufferLockComplex() )
		return;

	while( sptr <= eptr )
	{
		*sptr = DDCOLOR;
		sptr += LPITCH;
	}
}	//	DDVLine


//	Draw a horizontal line on the back buffer using color (DDCOLOR)
void DDHLine( int y, int x1, int x2 )
{
	if( x1 > x2 )
		exchange( x1, x2 );

	ASSERT( x1 >= DefaultClipRect.left );
	ASSERT( x2 < DefaultClipRect.right );
	ASSERT( y >= DefaultClipRect.top );
	ASSERT( y < DefaultClipRect.bottom );
	
	if( !LockBackBufferLockComplex() )
		return;

	memset( SCRPTR + y * LPITCH + x1, DDCOLOR, (x2-x1+1) );
}	//	DDHLine


//  Draw a rect on the back buffer using color (DDCOLOR)
void DDRect( int x1, int y1, int x2, int y2 )
{
	BYTE	*sptr, *eptr;
	int		l;

	if( x1 > x2 )
		exchange( x1, x2 );
	if( y1 > y2 )
		exchange( y1, y2 );

    if ( x1 < DefaultClipRect.left )
     x1 = DefaultClipRect.left;
	if ( x2 >= DefaultClipRect.right )
     x2 = DefaultClipRect.right -1;
	if ( y1 < DefaultClipRect.top )
     y1 =  DefaultClipRect.top ;
	if ( y2 >= DefaultClipRect.bottom )
     y2 = DefaultClipRect.bottom -1;
	
	if( !LockBackBufferLockComplex() )
		return;

	l = x2 - x1 + 1;
	sptr = SCRPTR + y1 * LPITCH + x1;
	eptr = SCRPTR + y2 * LPITCH + x1;
	memset( sptr, DDCOLOR, l );
	memset( eptr, DDCOLOR, l );
	while( sptr <= eptr )
	{
		*sptr = DDCOLOR;
		*(sptr + l) = DDCOLOR;
		sptr += LPITCH;
	}
}	//	DDRect


//	Draw a line from pStart to pEnd in the back buffer using the
//  given palette index. 
void DrawLine( SPOINT* pStart, SPOINT* pEnd, COLORREF rgb, BOOL world_coordinates )
{
	SPOINT	tmpStart;
	SPOINT	tmpEnd;

	ASSERT(pStart != NULL);
	ASSERT(pEnd != NULL);
    ASSERT(pBackBuffer != NULL);

	// load points into locals for clipping purposes
	tmpStart.x = pStart->x;
	tmpStart.y = pStart->y;
	tmpEnd.x   = pEnd->x;
	tmpEnd.y   = pEnd->y;
	if (world_coordinates)
		WorldToScreenLine(&tmpStart,&tmpEnd);

	HDC hdc;
	HRESULT ddrval = pBackBuffer->GetDC(&hdc);
	if (ddrval == DD_OK) 
	{
		HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
		if (hBrush)
		{
			HPEN hPen = CreatePen(PS_SOLID,0,rgb);
			if (hPen)
			{
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
				MoveToEx(hdc, tmpStart.x, tmpStart.y, NULL);
				LineTo(hdc, tmpEnd.x, tmpEnd.y); // open-ended line
				SetPixel(hdc, tmpEnd.x, tmpEnd.y, rgb); // plot final point
				SelectObject(hdc,hOldPen);
				SelectObject(hdc,hOldBrush);
				DeleteObject(hPen);
			}
		}
		ddrval = pBackBuffer->ReleaseDC(hdc);
	}
	else
		TRACE("DrawLine: couldn't get back buffer's device context [ %s : %d ]\n",
			__FILE__, __LINE__ );
}	// DrawLine


//    Draw a line from pStart to pEnd in the back buffer using the
//    given palette index - Uses DC argument so we don't need to get it again
void DrawMultiLine( HDC hdc, SPOINT* pStart, SPOINT* pEnd, COLORREF rgb, BOOL world_coordinates )
{
	SPOINT	tmpStart;
	SPOINT	tmpEnd;

	ASSERT(pStart != NULL);
	ASSERT(pEnd != NULL);
    ASSERT(pBackBuffer != NULL);
    ASSERT(pBackBuffer != NULL);

	// load points into locals for clipping purposes
	tmpStart.x = pStart->x;
	tmpStart.y = pStart->y;
	tmpEnd.x   = pEnd->x;
	tmpEnd.y   = pEnd->y;
	if (world_coordinates)
		WorldToScreenLine(&tmpStart,&tmpEnd);

	HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
	if (hBrush)
	{
		HPEN hPen = CreatePen(PS_SOLID,0,rgb);
		if (hPen)
		{
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, tmpStart.x, tmpStart.y, NULL);
			LineTo(hdc, tmpEnd.x, tmpEnd.y); // open-ended line
			SetPixel(hdc, tmpEnd.x, tmpEnd.y, rgb); // plot final point
			SelectObject(hdc,hOldPen);
			SelectObject(hdc,hOldBrush);
			DeleteObject(hPen);
		}
	}
	else
		TRACE("DrawMultiLine: couldn't get back buffer's device context\n");
}	// DrawMultiLine


//Draws a dot at an absolute screen location
void ScreenDrawDot( SPOINT* pPoint, COLORREF rgb )
{
	SPOINT	tmpPoint;

	ASSERT(pPoint != NULL);
    ASSERT(pBackBuffer != NULL);

	// get color to use
	BYTE color_index = (BYTE) GetNearestPaletteIndex(current_palette.hpal, rgb );

	tmpPoint = *pPoint;

    DDSURFACEDESC	ddsd;
	HRESULT ddrval;

	ddsd.dwSize = sizeof(DDSURFACEDESC);
	if ((ddrval = pBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)) != DD_OK)	
		TRACE( "DrawDot: couldn't lock back buffer\n" );

	SCRPTR = (BYTE *)(ddsd.lpSurface);
	LPITCH = ddsd.lPitch;

	DWORD offset = tmpPoint.y * LPITCH + tmpPoint.x;
	BYTE *pDest = (BYTE *)SCRPTR;

	pDest[offset] = color_index;
#ifdef MOVE_DEBUG
	pDest[offset+1] = color_index;

	offset += ddsd.lPitch;
	pDest[offset] = color_index;
	pDest[offset+1] = color_index;
#endif		

	pBackBuffer->Unlock(SCRPTR);
}	// ScreenDrawDot


//	Draw a dot at the specified point in the back buffer using the
//	given palette index. 
void DrawDot( SPOINT* pPoint, COLORREF rgb )
{
	SPOINT	tmpPoint;

	ASSERT(pPoint != NULL);
    ASSERT(pBackBuffer != NULL);

	// get color to use
	BYTE color_index = (BYTE) GetNearestPaletteIndex(current_palette.hpal, rgb );

	// load points into locals for clipping purposes
	tmpPoint = *pPoint;
	WorldToScreen(&tmpPoint);

	// make sure point is on screen
	if (!InRect(&rcGameWindow, &tmpPoint))
		return;

    DDSURFACEDESC	ddsd;
	HRESULT ddrval;

	if ( !LOCK_STATUS )
	{
		ddsd.dwSize = sizeof(DDSURFACEDESC);
		if ((ddrval = pBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)) != DD_OK)	
			TRACE( "DrawDot: couldn't lock back buffer\n" );

		SCRPTR = (BYTE *)(ddsd.lpSurface);
		LPITCH = ddsd.lPitch;
		if ( LOCK_COMPLEX_ON )
			LOCK_STATUS = TRUE;
	}

	DWORD offset = tmpPoint.y * LPITCH + tmpPoint.x;
	BYTE *pDest = (BYTE *)SCRPTR;

	pDest[offset] = color_index;
#ifdef MOVE_DEBUG
	pDest[offset+1] = color_index;

	offset += ddsd.lPitch;
	pDest[offset] = color_index;
	pDest[offset+1] = color_index;
#endif		

	if ( !LOCK_COMPLEX_ON )
		pBackBuffer->Unlock(SCRPTR);
}	// DrawDot



//	Draw a line from pStart to pEnd in the front buffer using the
//  given palette index. 
void DrawLineFront( SPOINT* pStart, SPOINT* pEnd, COLORREF rgb, BOOL world_coordinates )
{
	SPOINT	tmpStart;
	SPOINT	tmpEnd;

	ASSERT(pStart != NULL);
	ASSERT(pEnd != NULL);
    ASSERT(pFrontBuffer != NULL);

	// load points into locals for clipping purposes
	tmpStart.x = pStart->x;
	tmpStart.y = pStart->y;
	tmpEnd.x   = pEnd->x;
	tmpEnd.y   = pEnd->y;
	if (world_coordinates)
		WorldToScreenLine(&tmpStart,&tmpEnd);

	tmpStart.x += (short)rcWindowScreen.left;
	tmpStart.y += (short)rcWindowScreen.top;
	tmpEnd.x += (short)rcWindowScreen.left;
	tmpEnd.y += (short)rcWindowScreen.top;

	HDC hdc;
	HRESULT ddrval = pFrontBuffer->GetDC(&hdc);
	if (ddrval == DD_OK) 
	{
		HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
		if (hBrush)
		{
			HPEN hPen = CreatePen(PS_SOLID,0,rgb);
			if (hPen)
			{
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
				MoveToEx(hdc, tmpStart.x, tmpStart.y, NULL);
				LineTo(hdc, tmpEnd.x, tmpEnd.y); // open-ended line
				SetPixel(hdc, tmpEnd.x, tmpEnd.y, rgb); // plot final point
				SelectObject(hdc,hOldPen);
				SelectObject(hdc,hOldBrush);
				DeleteObject(hPen);
			}
		}
		ddrval = pFrontBuffer->ReleaseDC(hdc);
	}
	else
		TRACE("DrawLine: couldn't get back buffer's device context [ %s : %d ]\n",
			__FILE__, __LINE__);
}	// DrawLineFront


//	Draw a dot at the specified point in the front buffer using the
//  given palette index.  (Using direct access instead of GDI)
void DrawDotFront2( SPOINT* pPoint, COLORREF rgb )
{
	SPOINT	tmpPoint;

	ASSERT(pPoint != NULL);
    ASSERT(pFrontBuffer != NULL);

	// get color to use
	BYTE color_index = (BYTE) GetNearestPaletteIndex(current_palette.hpal, rgb );

	// load points into locals for clipping purposes
	//	if (world_coordinates)
	tmpPoint = *pPoint;
	WorldToScreen(&tmpPoint);

	// make sure point is on screen
	if (!InRect(&rcGameWindow, &tmpPoint))
		return;

	// tmpPoint.x += rcWindowScreen.left;
	//tmpPoint.y += rcWindowScreen.top;

    DDSURFACEDESC	ddsd;
	HRESULT ddrval;

	ZeroMemory( &ddsd, sizeof( DDSURFACEDESC ) );
	ddsd.dwSize = sizeof(DDSURFACEDESC);

	ddrval = pFrontBuffer->GetSurfaceDesc(&ddsd);

	//	ddrval = pFrontBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	ddrval = pFrontBuffer->Lock(&rcWindowScreen, &ddsd, DDLOCK_WAIT, NULL);
	if (ddrval == DD_OK)	{
		DWORD offset = tmpPoint.y*ddsd.lPitch + tmpPoint.x;
		BYTE *pDest = (BYTE *)ddsd.lpSurface;

		pDest[offset] = color_index;
#ifdef MOVE_DEBUG
		pDest[offset+1] = color_index;

		offset += ddsd.lPitch;
		pDest[offset] = color_index;
		pDest[offset+1] = color_index;
#endif
		
		pFrontBuffer->Unlock(ddsd.lpSurface);
	}
	else 
		TRACE("DrawDot: couldn't lock front buffer: %s.\n", DDErrorToString(ddrval));
}	// DrawDotFront2


//	Draw a dot at the specified point in the front buffer using the
//	given palette index. 
void DrawDotFront( SPOINT* pPoint, COLORREF rgb )
{
	SPOINT	tmpPoint;

	ASSERT(pPoint != NULL);

	// if (world_coordinates)
	tmpPoint = *pPoint;
	WorldToScreen(&tmpPoint);

	tmpPoint.x += (short)rcWindowScreen.left;
	tmpPoint.y += (short)rcWindowScreen.top;

	HDC hdc;
	HRESULT ddrval = pFrontBuffer->GetDC(&hdc);
	if (ddrval == DD_OK) 
	{
		HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
		if (hBrush)
		{
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			SetPixel(hdc, tmpPoint.x, tmpPoint.y, rgb); // plot final point
			SelectObject(hdc,hOldBrush);
		}
		ddrval = pFrontBuffer->ReleaseDC(hdc);
	}
	else
		TRACE("DrawLine: couldn't get back buffer's device context [ %s : %d ]\n"
				__FILE__, __LINE__);
}	// DrawDotFront



//	Draw a filled rect on the back buffer
void DrawScreenRect( LPDIRECTDRAWSURFACE pSurface, RECT &rect, COLORREF rgb )	
{
	DDBLTFX ddbltfx;
	HRESULT	ddrval;
	DWORD	bltflags = DDBLT_WAIT | DDBLT_COLORFILL;
	DWORD	nPaletteIndex;

	// convert the RGB color to a palette index
	nPaletteIndex = DDColorMatch(pSurface, rgb);
	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = nPaletteIndex;
	ddrval = pSurface->Blt( &rect, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx );
	if( ddrval != DD_OK )
		TRACE("Error in DrawScreenRect: %s; %d, %d, %d, %d\n", DDErrorToString(ddrval), rect.left, rect.top,
		  rect.right, rect.bottom );
}



//************************************************************************
//	Buffer Functions
//************************************************************************

//************************************************************************
//	Bitmap Functions
//************************************************************************

//  Return bitmap size counter
DWORD BitmapSize()	
{
	return total_size;					// global from this module
}	// BitmapSize


//  Initialize bitmap size counter
void BitmapSizeInit()	
{
	total_size = 0;						// global
}	// BitmapSizeInit


//	Write a translated bitmap to a DD surface
//	assumes that bitmap (source) pitch is the width, padded to a LONG boundary
DWORD TranslateBitmapToDD( BYTE* pDestStart,	//	First byte in dest data.
				long lPitchDest,			//	Dest data's line pitch.
				const BYTE* pBMStart,		//	First byte in source data.
				int width,					//  Number of bytes per line in source image
				int	height,					//	Number of lines in source image.
				BYTE table[256] )			//	translation table
{
	const BYTE*	pSrc;
	BYTE*		pDest = pDestStart;
	int			y = 0;
	int			x;
	long lPitchBM = (width + sizeof(LONG) - 1) & ~3;

	if (height > 0)	{	// bottom-up bitmap
		pSrc = pBMStart + (height - 1) * lPitchBM;	// beginning of last line of source
		lPitchBM = -lPitchBM;
	}
	else	{
		height = -height;
		pSrc = pBMStart;							// first source line
	}

	while( y < height )	{
		x = 0;
		if (table)	{
			while ( x < width )	{
				pDest[x] = table[pSrc[x]];
				x++;
			}
		}
		else	{
			while ( x < width )	{
				pDest[x] = pSrc[x];
				x++;
			}
		}
		y++;
		pDest += lPitchDest;
		pSrc += lPitchBM;
	}

	return height*lPitchDest;
}	// TranslateBitmapToDD



//************************************************************************
//	Direct Draw Surface Functions
//************************************************************************

//	Report an error
BOOL DDFail(const char* err_str, HRESULT ddrval)	
{
	Error("%s: %s\n", err_str, DDErrorToString(ddrval));

	return FALSE;
}	// DDFail


//	Clear a Direct Draw Surface to an RGB color
BOOL DDClearSurface( LPDIRECTDRAWSURFACE pdds, COLORREF rgb )
{
	DWORD	nPaletteIndex;

	// acquire the palette index for the RGB
	nPaletteIndex = DDColorMatch(pdds, rgb);

	// Erase the background
	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = nPaletteIndex;

	if (pdds->Blt(NULL, NULL, NULL, 
			DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx) != DD_OK)
		return FALSE;

	return TRUE;
}	// DDClearSurface


//	Erase both front & back buffer
BOOL EraseSurfaces( void )
{

	if (EraseBackSurface())
	{
		if (gpDO->bFullscreen)	
		{
			// Flip the surfaces
			if (pFrontBuffer->Flip(NULL, DDFLIP_WAIT) != DD_OK)
				return FALSE;

			return EraseBackSurface();
		}
		else	
			return EraseVisibleSurface();
	}

	return FALSE;
}	// EraseSurfaces


//	Erase the front buffer
BOOL EraseVisibleSurface( void )
{
	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = 0;

	if (pFrontBuffer->Blt(&rcWindowScreen, NULL, NULL, 
			DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx) != DD_OK)
		return FALSE;

	return TRUE;
}

//	Erase both buffer
BOOL EraseBackSurface( void )
{
	// Erase the background
	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = 0;

	if (pBackBuffer->Blt(NULL, NULL, NULL, 
			DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx) != DD_OK)
		return FALSE;
	return TRUE;
}	// EraseBackSurface

//	Erase the front buffer
BOOL DDCopyBackToFront( void )
{
	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(DDBLTFX);

	if (pFrontBuffer->Blt(&rcWindowScreen, pBackBuffer, &rcBackWindow, 
			DDBLT_WAIT, &ddbltfx) != DD_OK)
		return FALSE;

	return TRUE;
}


//	Draw a filled rect on the back buffer
HRESULT FillRect( RECT *prect, COLORREF rgb )	
{
	DDBLTFX ddbltfx;
	DWORD	nPaletteIndex;

	// acquire the palette index for the RGB
	nPaletteIndex = DDColorMatch(pBackBuffer, rgb);

	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = nPaletteIndex;
	return (pBackBuffer->Blt(prect, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx));
}

//	Draw a filled rect on the front buffer
HRESULT FillRectFront( RECT *pRect, COLORREF rgb )	
{
	DDBLTFX ddbltfx;
	RECT	rcFrontRect;
	DWORD	nPaletteIndex;

	// acquire the palette index for the RGB
	nPaletteIndex = DDColorMatch(pFrontBuffer, rgb);

	// since we are writing to the front buffer, we need
	// to add in the offset (left,top) if the screen window
	// we think we're drawing into
	rcFrontRect.left   = pRect->left   + rcWindowScreen.left;
	rcFrontRect.top    = pRect->top    + rcWindowScreen.top;
	rcFrontRect.right  = pRect->right  + rcWindowScreen.left;
	rcFrontRect.bottom = pRect->bottom + rcWindowScreen.top;

	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = nPaletteIndex;
	return (pFrontBuffer->Blt(&rcFrontRect, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx));
}


HRESULT FillTransRectFront(RECT* pRect, BYTE* pShadeTable )
{
	RECT	rcFrontRect;
	DDBLTFX ddbltfx;
	DWORD	nPaletteIndex;

	// acquire the palette index for the RGB
	nPaletteIndex = DDColorMatch(pFrontBuffer, RGB_BLACK);

	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = nPaletteIndex;

	// since we are writing to the front buffer, we need
	// to add in the offset (left,top) if the screen window
	// we think we're drawing into
	rcFrontRect.left   = pRect->left   + rcWindowScreen.left;
	rcFrontRect.top    = pRect->top    + rcWindowScreen.top;
	rcFrontRect.right  = pRect->right  + rcWindowScreen.left;
	rcFrontRect.bottom = pRect->bottom + rcWindowScreen.top;

	return (pFrontBuffer->Blt( &rcFrontRect, NULL, NULL, 
			DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx));
}


//  Create a direct draw surface & set the color key (for SRCBLT)
LPDIRECTDRAWSURFACE CreateSurfaceOfSize( DWORD width, DWORD height, LONG flags, COLORREF rgb )	
{
	DDSURFACEDESC       ddsd;
	HRESULT             ddrval;
	DDCOLORKEY          ddck;
	LPDIRECTDRAWSURFACE psurf;

	// fill in surface desc
	ZeroMemory( &ddsd, sizeof( DDSURFACEDESC ) );
	ddsd.dwSize = sizeof( DDSURFACEDESC );
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;

	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	if( flags & BM_SYSTEMMEMORY )
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

	ddsd.dwHeight = height;
	ddsd.dwWidth = width;

	ddrval = pDirectDraw2->CreateSurface( &ddsd, &psurf, NULL );
	if( ddrval != DD_OK )	
	{
		DDFail("CreateSurface() failure", ddrval);
		return NULL;
	}

    // set the color key for this bitmap
	ddck.dwColorSpaceLowValue = rgb;
	ddck.dwColorSpaceHighValue = rgb;
	psurf->SetColorKey( DDCKEY_SRCBLT, &ddck);

	return psurf;
}   // CreateSurfaceOfSize

//  Create a direct draw surface & set the color key (for SRCBLT)
LPDIRECTDRAWSURFACE CreatePixelSurfaceOfSize( DWORD width, DWORD height, LONG flags, COLORREF rgb )	
{
	DDSURFACEDESC       ddsd;
	HRESULT             ddrval;
	DDCOLORKEY          ddck;
	LPDIRECTDRAWSURFACE psurf;

	// fill in surface desc
	ZeroMemory( &ddsd, sizeof( DDSURFACEDESC ) );
	ddsd.dwSize = sizeof( DDSURFACEDESC );
	ddrval = pFrontBuffer->GetSurfaceDesc( &ddsd );
	if( ddrval != DD_OK )	
	{
		DDFail("CreateSurface() failure", ddrval);
		return NULL;
	}

	ddsd.dwFlags = (DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT);

	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	if( flags & BM_SYSTEMMEMORY )
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

	ddsd.dwHeight = height;
	ddsd.dwWidth  = width;

	ddrval = pDirectDraw2->CreateSurface( &ddsd, &psurf, NULL );
	if( ddrval != DD_OK )	
	{
		DDFail("CreateSurface() failure", ddrval);
		return NULL;
	}

    // set the color key for this bitmap
	ddck.dwColorSpaceLowValue = rgb;
	ddck.dwColorSpaceHighValue = rgb;
	psurf->SetColorKey( DDCKEY_SRCBLT, &ddck);

	return psurf;
}   // CreateSurfaceOfSize


//  Open a draw session to cut down on surface acquisition.  Return acquired DC
HDC DrawOpen( void )
{
 	HDC		hdc;
	HRESULT ddrval;

	ASSERT(pBackBuffer != NULL);

	ddrval = pBackBuffer->GetDC(&hdc);
	if (ddrval != DD_OK)
	{
//		TRACE("DrawLine: couldn't get back buffer's device context [ %s : %d ]\n"
//				__FILE__, __LINE__);
		hdc = 0;
	}

	return( hdc );
}	// DrawOpen


//  Close a draw session to cut down on surface acquisition. 
void DrawClose( HDC hdc )
{
	HRESULT ddrval;

    ASSERT(pBackBuffer != NULL);

	ddrval = pBackBuffer->ReleaseDC(hdc);
	if ( ddrval )
		TRACE("ERROR: failed to release the back buffer's device context\n");
}


//	Lock overlay layer = back buffer (assert if LOCK_COMPLEX_ON)
BOOL LockOverlayLayer( void )
{
	DDSURFACEDESC	ddsd;
	HRESULT			ddrval;

	ASSERT( !LOCK_COMPLEX_ON );

	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddrval = pBackBuffer->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
	if ( ddrval == DD_OK )
	{
		SCRPTR = (BYTE *)ddsd.lpSurface;
		LPITCH = ddsd.lPitch;
		return TRUE;
	}			
	else 
		return FALSE;
}	//	LockOverlayLayer


//	Unlock overlay layer (assert if LOCK_COMPLEX_ON)
void UnlockOverlayLayer( void )
{
	ASSERT( !LOCK_COMPLEX_ON );

	pBackBuffer->Unlock( SCRPTR );
}	//	UnlockDrawingSurface


void DrawShadeSpriteToOverlayLayer( int x, int y, BYTE *data, RECT &rect, BYTE *ShadeTable )
{
	if( !LockOverlayLayer() )
		return;
	PShadeTable = ShadeTable;
	DrawSRleClippedShade( x, y, data, rect );
	UnlockOverlayLayer();
	PShadeTable = PSHADE_TABLE;
}



//************************************************************************




DWORD MakeBitmap(BITMAPINFO_256 *pbminfo, BYTE *pSrc, LOADBITMAP *plbitmap, BYTE *trans_table)	{
	BOOL		translate;
	BYTE		table[256];
	DWORD		size = 0;

	translate = !(plbitmap->flags & BM_NOTRANSLATE);

#if _DEBUG
//	if (!translate)
//		ASSERT(trans_table == NULL);
#endif

 	plbitmap->width = pbminfo->bmiHeader.biWidth;
	plbitmap->height = pbminfo->bmiHeader.biHeight;
	plbitmap->xppm = pbminfo->bmiHeader.biXPelsPerMeter;
	plbitmap->yppm = pbminfo->bmiHeader.biYPelsPerMeter;

	if (trans_table == NULL )	
	{
		int startcolor = 0;
		int i;
		RGBQUAD		*pColors = pbminfo->bmiColors;
		trans_table = table;

		if( !translate )
		{
			for( i = 0; i < 16; i++ )
				trans_table[i] = i;
			startcolor = 16;
		}

		HDC	hdc = GetDC(NULL);
		for( i = startcolor; i < 256; i++)	
		{
			BYTE r, g, b;
			DWORD dw;

			r = pColors[i].rgbRed;
			g = pColors[i].rgbGreen;
			b = pColors[i].rgbBlue;
			dw = GetNearestPaletteIndex(current_palette.hpal, RGB(r, g, b));
			trans_table[i] = (BYTE) dw;
		}
		ReleaseDC( NULL, hdc);
	}

	DWORD	maxsize;

	BYTE	*pBits;
	if (plbitmap->flags & BM_RLE_ONLOAD)	
	{
		// create a memory area for this bitmap
		maxsize = pbminfo->bmiHeader.biSizeImage;
		pBits = (BYTE *) malloc(maxsize);
		if (pBits == NULL)	
		{
	        TRACE("malloc failed in MakeBitmap()\n");
			return 0;
		}

		plbitmap->xpc = 0;

		if ( plbitmap->flags & BM_TRLE )
		{
			if (size = TranslateWRleBits(pBits, pSrc, plbitmap->height, trans_table, maxsize))
			{
				plbitmap->pGraphic = pBits;
				plbitmap->flags |= BM_TRLE;
				total_size += size;
			}
			else
				free(pBits);
		}
		else if ( plbitmap->flags & BM_WRLE )
		{
			if (size = TranslateWRleBits(pBits, pSrc, plbitmap->height, trans_table, maxsize))
			{
				plbitmap->pGraphic = pBits;
				plbitmap->flags |= BM_WRLE;
				total_size += size;
			}
		}
		else
		{
			if (size = TranslateRLEBitmap(pBits, pSrc, plbitmap->height, trans_table, maxsize))	
			{
				plbitmap->pGraphic = pBits;
				plbitmap->flags |= BM_RLE;
				total_size += (plbitmap->width * plbitmap->height);
			}
			else
				free(pBits);
		}
	}
	else if ( plbitmap->flags & BM_DRLE_ONLOAD )
	{
		plbitmap->flags = plbitmap->flags & (~BM_DRLE_ONLOAD);
		plbitmap->xpc = 0;
		if ( plbitmap->width * plbitmap->height < 60000 )
		{
			size = BitmapToWRle( pSrc, (BYTE **)&(plbitmap->pGraphic), plbitmap->width, 
				plbitmap->height, plbitmap->xpc, trans_table);			
			plbitmap->flags |= BM_WRLE;
		}
		else
		{
			size = BitmapToDRle( pSrc, (BYTE **)&(plbitmap->pGraphic), plbitmap->width, 
				plbitmap->height, plbitmap->xpc, trans_table);
			plbitmap->flags |= BM_DRLE;
		}
		total_size += size;
	}
	else if ( plbitmap->flags & BM_TRLE_ONLOAD )
	{
		plbitmap->flags = plbitmap->flags & (~BM_DRLE_ONLOAD);
		plbitmap->xpc = 0;
		size = BitmapToWRle( pSrc, (BYTE **)&(plbitmap->pGraphic), plbitmap->width, 
			plbitmap->height, plbitmap->xpc, trans_table);			
		plbitmap->flags |= BM_TRLE;
	}
	else if (plbitmap->flags & BM_RLE)	
	{
		// create a memory area for this bitmap
		maxsize = plbitmap->width * plbitmap->height * 2;
		pBits = (BYTE *) malloc(maxsize);
		if (pBits == NULL)	
		{
	        TRACE("malloc failed in MakeBitmap()\n");
			return 0;
		}

		// transparency is from pixel in upper left (lower left of bottom up bitmap)
		if (plbitmap->flags & BM_FORCE_OPAQUE)
			plbitmap->xpc = 255;
		else
			plbitmap->xpc = pSrc[(plbitmap->height - 1) * ((plbitmap->width+3) & ~3)];

		if (size = TranslateBitmapToRLE(pBits, pSrc, plbitmap->width, plbitmap->height, plbitmap->xpc, trans_table, maxsize))	
		{
			plbitmap->pGraphic = realloc(pBits, size);
			total_size += maxsize/2;
		}
		else
			free(pBits);
	}
	else
	{
		DDSURFACEDESC		ddsd;
		LPDIRECTDRAWSURFACE pdds;
		HRESULT				hr;
		#if !defined(_USESYSTEMMEMORY_)
		DWORD				dwTotalFreeMem, dwTotalAvailMem;
		#endif
		DDSCAPS				ddsc;

		// create a DirectDrawSurface for this bitmap
		ddsd.dwSize = sizeof(DDSURFACEDESC);
		ddsd.dwWidth = plbitmap->width;
		ddsd.dwHeight = plbitmap->height;
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

		ddsc.dwCaps = DDSCAPS_OFFSCREENPLAIN;

		#if !defined(_USESYSTEMMEMORY_)		// use video memory if available
		if (!(plbitmap->flags & BM_SYSTEMMEMORY))
		{
			DWORD  sz;

			sz = plbitmap->width * plbitmap->height;
			if (pDirectDraw2)
			{
				pDirectDraw2->GetAvailableVidMem(&ddsc,	&dwTotalFreeMem, &dwTotalAvailMem);
				if (dwTotalAvailMem < sz)
					plbitmap->flags |= BM_SYSTEMMEMORY;
			}
			else
			{
				plbitmap->flags |= BM_SYSTEMMEMORY;
			}
		}
		#else
		if (!(plbitmap->flags & BM_SYSTEMMEMORY))
		{
			plbitmap->flags |= BM_SYSTEMMEMORY;
		}
		#endif

		if (plbitmap->flags & BM_SYSTEMMEMORY)
			ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

		if (pDirectDraw->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
		{
			if (!(plbitmap->flags & BM_SYSTEMMEMORY))
			{
				TRACE( "Failed to put surface into video memory!\n" );
				plbitmap->flags |= BM_SYSTEMMEMORY;
				ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
				if (pDirectDraw->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
				{
					TRACE("CreateSurface failed in MakeBitmap()\n");
					return 0;
				}
			}
			else
			{
				TRACE("CreateSurface failed in MakeBitmap()\n");
				return 0;
			}
		}

		pdds->Restore();

		if ((hr = pdds->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)) == DD_OK)	{
			if (size = TranslateBitmapToDD((BYTE *)ddsd.lpSurface, ddsd.lPitch, pSrc, plbitmap->width, plbitmap->height, trans_table))	{
				pdds->Unlock(ddsd.lpSurface);

  				plbitmap->pGraphic = pdds;
				plbitmap->xpc  = DDColorMatch(pdds, CLR_INVALID);
				DDSetColorKey(pdds, plbitmap->xpc);
				total_size += size;
			}
			else	{
				pdds->Release();
				TRACE("Error on Lock in DDCopyBitmap()");
			}
		} 
		else	{
			pdds->Release();
			TRACE("Error on Lock in DDCopyBitmap()");
		}
	}

	return size;
}


#if 0
HBITMAP OldReadBitmap(FILE* pFile, BITMAPINFO_256 *pbminfo)
{
	HBITMAP hBitmap = NULL;
	HDC hdc = NULL;
	DWORD bmsize;
	BITMAPINFOHEADER *pHeader = &pbminfo->bmiHeader;

	// Get the current file position
	DWORD dwFileStart = ftell(pFile);

 	BITMAPFILEHEADER bmfile;
	READ_BUFFER(&bmfile, sizeof(bmfile));

	READ_BUFFER(pHeader, sizeof(BITMAPINFOHEADER));

	if (pHeader->biClrUsed == 0)
		pHeader->biClrUsed = 1 << pHeader->biBitCount;

	UINT iColorTableSize = pHeader->biClrUsed * sizeof(RGBQUAD);

	// Now read the color table in
	READ_BUFFER( pbminfo->bmiColors, iColorTableSize );

	// get the screen device context
	hdc = GetDC(NULL);
	
	BYTE *pBits;

	hBitmap = CreateDIBSection(hdc, (BITMAPINFO *) pbminfo, DIB_RGB_COLORS, (void **)&pBits, NULL, 0);
	if (hBitmap == NULL) {
		TRACE("ERROR: Out of memory for DIBSection: [%s:%d]\n", 
			  __FILE__, __LINE__ );
		goto exit_bm;
	}

	// Seek to the bits
	fseek(pFile, dwFileStart + bmfile.bfOffBits, SEEK_SET);

	bmsize = pHeader->biSizeImage;
	if (bmsize == 0)
		bmsize = ((pHeader->biWidth + sizeof(LONG) - 1) & ~3) * pHeader->biHeight * (pHeader->biBitCount / 8);

	// Read the bits.
	READ_BUFFER(pBits, bmsize);

exit_bm:
	if (hdc)
		ReleaseDC( NULL, hdc);

	return hBitmap;
}
#endif


//-----------------------------------------------------------------------------------------------------------------
BOOL
//CSpriteCatalog::
RLEFastBlt(	void* pDestStart,			//	First byte in locked DD surface.
			long lPitchDest,			//	Surface's line pitch.
			const BYTE* pSrcStart,		//	First byte in RLE data.
			int	iLines )				//	Number of lines in source image.
{
	//	FastBlt rewrite!!!
	//	For unclipped blits. All of source image can be written to the surface.

	//	Copy DWORDs at a time when possible, WORDs and BYTEs when necessary.

#if 0
	const BYTE*	pSrc = pSrcStart;
	void*		pDest = pDestStart;

	BYTE		qSkip;
	BYTE		qRun;

	int			y = 0;
	const BYTE*	pSrcQuadEnd;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= (BYTE*)pDest + qSkip;

		//	Copy color pixels...

		//	Complete sets of four pixels.
		pSrcQuadEnd = pSrc + ( qRun & ~3 );
		while( pSrc != pSrcQuadEnd )
		{
			//	*((DWORD*)pDest)++ = *((DWORD*)pSrc)++;
			*(DWORD*)pDest = *(DWORD*)pSrc;
			pDest = ((DWORD*)pDest) + 1;
			pSrc += 4;
		}
		//	Catch remainders if not divisible by four...
		if( qRun & 2 )
		{
			//	*((WORD*)pDest)++ = *((WORD*)pSrc)++;
			*(WORD*)pDest = *(WORD*)pSrc;
			pDest = ((WORD*)pDest) + 1;
			pSrc += 2;
		}
		if( qRun & 1 )
		{
			//	*((BYTE*)pDest)++ = *pSrc++;
			*(BYTE*)pDest = *pSrc;
			pDest = ((BYTE*)pDest) + 1;
			pSrc++;
		}

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDest = (void*)( (BYTE*)pDestStart + y * lPitchDest );
		}	
	}

#else

	BYTE* pDestTerminator = (BYTE*)pDestStart + iLines * lPitchDest;	//	Used to determine when we are done.

	__asm
	{
		mov		edx, pDestStart					//	Put destination start address in edx. This register will always point to the 
												//	beginning of the current "line".
		mov		ebx, lPitchDest					//	Save destination pitch in ebx (ebx won't change).
		mov		esi, pSrcStart					//	Put source address in esi.

		image_loop:

			mov		edi, edx						//	Set edi to beginning of destination line.

			line_loop:

				xor		ecx, ecx						//	Clear ecx.
				mov		cl, [esi]						//	Put skip count in ecx.
				inc		esi								//	Move source pointer forward.
				add		edi, ecx						//	Skip over transparent pixels in destination.

				mov		cl, [esi]						//	Put run count in ecx.
				mov		eax, ecx						//	Save run count value in eax.
				inc		esi								//	Move source pointer forward.
				shr		ecx, 2							//	Set ecx to the number of complete quads in run count.
				rep		movsd							//	Copy dwords from esi to edi (incrementing the ptrs), ecx times.

				and		eax, 0x00000003					//	Get remainder of division of run count by 4.
				mov		ecx, eax						//	Set ecx to number of remaining pixels to copy.
				rep		movsb							//	Copy bytes from esi to edi (incrementing the ptrs), ecx times.

				cmp		byte ptr [esi], 0xff			//	Is the next byte the end-of-line marker?

			jne		line_loop

			inc		esi								//	Move source pointer forward.
			add		edx, ebx						//	Advance beginning-of-line pointer to start of next line.
			cmp		edx, pDestTerminator			//	Have we reached the end of the image?

		jne		image_loop
	}

#endif

	return TRUE;
}

	
#if 1

BOOL 
//CSpriteCatalog::
RLEFastBltClipped(	void* pDestStart,			//	First byte in locked DD surface.
					long lPitchDest,			//	Surface's line pitch.
					const BYTE* pSrcStart,		//	First byte in RLE data.
					const RECT& rcSrc )			//	Rect within source image to write.
//					const CRect& rcSrc )		//	Rect within source image to write.
{
	//	FastBlt rewrite!!!
	//	For clipped blits.

	int sy = rcSrc.top;
//	int sh = rcSrc.Height();
	int sh = rcSrc.bottom - sy;
	int sx = rcSrc.left;
//	int xlast = sx + rcSrc.Width() - 1;
	int xlast = rcSrc.right - 1;
	int x = 0;

	ASSERT(rcSrc.left <= rcSrc.right);
	ASSERT(rcSrc.top <= rcSrc.bottom);

	BYTE* pDestTerminator = (BYTE*)pDestStart + sh * lPitchDest;	//	Used to determine when we are done.
	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE *)pDestStart;
	BYTE*		pDestLine = (BYTE *) pDestStart;

	BYTE		qSkip;
	BYTE		qRun;

	// skip all lines up to sy
	while (sy > 0)
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;
		pSrc	+= qRun;
		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			sy--;
		}
	}

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		while (qSkip-- > 0)
		{
			if (x >= sx && x <= xlast)
				pDest++;
			x++;
		}
		        
		//	Copy color pixels...
		while (qRun-- > 0)
		{
			if (x >= sx && x <= xlast)
				*pDest++ = *pSrc; 
			pSrc++;
			x++;
		}

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			pDestLine += lPitchDest;
			if (pDestLine == pDestTerminator)
				break;
			pDest = pDestLine;
			x = 0;
		}	
	}

	return TRUE;
}

#endif

//-----------------------------------------------------------------------------------------------------------------
BOOL
//CSpriteCatalog::
RLETranslateBlt(	void* pDestStart,			//	First byte in locked DD surface.
					long lPitchDest,			//	Surface's line pitch.
					const BYTE* pSrcStart,		//	First byte in RLE data.
					int	iLines,					//	Number of lines in source image.
					const BYTE table[256])		//	translation table
{
	//	FastBlt rewrite!!!
	//	For unclipped blits. All of source image can be written to the surface.

	//	Copy DWORDs at a time when possible, WORDs and BYTEs when necessary.

	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE *)pDestStart;
	BYTE*		pDestLine = (BYTE *) pDestStart;
	BYTE		qSkip;
	BYTE		qRun;
	int			y = 0;

	while( TRUE )
	{
		qSkip = *pSrc++;
		qRun = *pSrc++;

		//	Skip transparent pixels...
		pDest += qSkip;

		//	Copy color pixels...
		while (qRun-- > 0)
		{
			*pDest++ = table[*pSrc];
			pSrc++;
		}

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDestLine += lPitchDest;
			pDest = pDestLine;
		}	
	}
	return TRUE;
}


/*
** Copies the rectangle rcSrc from a source bitmap whose upper left hand
** corner is given by pSrcStart to a position in a destination bitmap 
** (pDestStart).
** 
** This method assumes that rcSrc is fully contained in source bitmap and
** the width and height of rcSrc can be copied to the destination.
**
** Assumes rcSrc has been normalized.
*/
BOOL 
//CSpriteCatalog::
RLETranslateBltClipped(	void* pDestStart,		//	First byte in locked DD surface.
					long lPitchDest,			//	Surface's line pitch.
					const BYTE* pSrcStart,		//	First byte in RLE data.
					const RECT& rcSrc,			//	Rect within source image to write.
//					const CRect& rcSrc )		//	Rect within source image to write.
					const BYTE *table)			//	translation table
{
	//	FastBlt rewrite!!!
	//	For clipped blits.

	int sy = rcSrc.top;
//	int sh = rcSrc.Height();
	int sh = rcSrc.bottom - sy;
	int sx = rcSrc.left;
//	int xlast = sx + rcSrc.Width() - 1;
	int xlast = rcSrc.right - 1;
	int x = 0;

	ASSERT(rcSrc.left <= rcSrc.right);
	ASSERT(rcSrc.top <= rcSrc.bottom);

	BYTE* pDestTerminator = (BYTE*)pDestStart + sh * lPitchDest;	//	Used to determine when we are done.
	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE *)pDestStart;
	BYTE*		pDestLine = (BYTE *) pDestStart;

	BYTE		qSkip;
	BYTE		qRun;

	// skip all lines up to sy
	while (sy > 0)
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;
		pSrc	+= qRun;
		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			sy--;
		}
	}

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		while (qSkip-- > 0)
		{
			if (x >= sx && x <= xlast)
				pDest++;
			x++;
		}
        
		//	Copy color pixels...
		while (qRun-- > 0)
		{
			if (x >= sx && x <= xlast)
				*pDest++ = table[*pSrc];
			pSrc++;
			x++;
		}

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			pDestLine += lPitchDest;
			if (pDestLine == pDestTerminator)
				break;
			pDest = pDestLine;
			x = 0;
		}	
	}

	return TRUE;
}


BOOL DDTranslateBlt(BYTE* pDestStart,			//	First byte in dest data.
					long lPitchDest,			//	Dest data's line pitch.
					const BYTE* pSrcStart,		//	First byte in source data.
					long lPitchSrc,				//	Source data's line pitch.
					const RECT* rcSrc,			//	Rect within source image to write.
					const DWORD xpc,			//  transparent color (0-255; -1 if opaque)
					const BYTE table[256])		//	translation table
{
	const BYTE*	pSrc;
	BYTE*		pDest = pDestStart;
	BYTE		bxpc = (BYTE) xpc;

	ASSERT(table != NULL);

	int left = rcSrc->left;
	int width = rcSrc->right - left;
	int top = rcSrc->top;
	int height = rcSrc->bottom - top;
	int x,y;
	int relPitchDest;
	int relPitchSrc;

	ASSERT(rcSrc->left <= rcSrc->right);
	ASSERT(rcSrc->top <= rcSrc->bottom);

	// skip all lines up to sy and all left side pixels
	pSrc = pSrcStart + ((top * lPitchSrc) + left);

	relPitchDest = lPitchDest - width;
	relPitchSrc = lPitchSrc - width;

	if (xpc == -1)	{	// if opaque
		y = 0;
		while( y < height )	{
			x = 0;
			while ( x < width )	{
				*pDest++ = table[*pSrc];
				pSrc++;
				x++;
			}
			y++;
			pDest += relPitchDest;
			pSrc += relPitchSrc;
		}
	}
	else	{	// otherwise transparent
		y = 0;
		while( y < height )	{
			x = 0;
			while ( x < width )	{
				if (*pSrc != bxpc)
					*pDest = table[*pSrc];
				pDest++;
				pSrc++;
				x++;
			}
			y++;
			pDest += relPitchDest;
			pSrc += relPitchSrc;
		}
	}

	return TRUE;
}




/*
// RLECopyBitmap: RLE a bitmap and draw it
DWORD RLECopyBitmap(BYTE *pDest, HBITMAP hbm, BYTE *trans_table, BOOL notranslate, DWORD xpc, DWORD maxsize)
{
    HDC				hdcImage;
    HDC				hdc;
    BITMAP			bm;
	RGBQUAD			local_palette[256];
	BYTE			table[256];
	DWORD			size;

	ASSERT(hbm != NULL);
	ASSERT(pDest != NULL);

#if _DEBUG
	if (notranslate)
		ASSERT(trans_table == NULL);
#endif

    //  select bitmap into a memoryDC so we can use it.
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)	{
        OutputDebugString("create compatible dc failed\n");
        return 0;
	}
    SelectObject(hdcImage, hbm);

	if (trans_table == NULL && !notranslate)	{
		trans_table = table;

		UINT colors = GetDIBColorTable(hdcImage, 0, 256, local_palette);
 
		hdc = GetDC(NULL);
		for (int i=0; i<256; i++)	{
			DWORD dw = GetNearestPaletteIndex(current_palette.hpal, RGB(local_palette[i].rgbRed, local_palette[i].rgbGreen, local_palette[i].rgbBlue,));
			trans_table[i] = (BYTE) dw;
		}
		ReleaseDC( NULL, hdc);
	}

    // get size of the bitmap
    GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap

	size = TranslateBitmapToRLE(pDest, (BYTE *)bm.bmBits, bm.bmWidth, bm.bmHeight, xpc, trans_table, maxsize); 

    DeleteDC(hdcImage);

    return size;
}


// DDCopyBitmap: draw a bitmap into a DirectDrawSurface, possibly translating for palettes
DWORD DDCopyBitmap(LPDIRECTDRAWSURFACE pdds, HBITMAP hbm, BYTE *trans_table, BOOL notranslate)
{
    HDC				hdcImage;
    HDC				hdc;
    BITMAP			bm;
    DDSURFACEDESC	ddsd;
    HRESULT			hr;
	RGBQUAD			local_palette[256];
	BYTE			table[256];
	DWORD			size = 0;

	ASSERT(hbm != NULL);
	ASSERT(pdds != NULL);

#if _DEBUG
	if (notranslate)
		ASSERT(trans_table == NULL);
#endif

    // make sure this surface is restored.
    pdds->Restore();

    //  select bitmap into a memoryDC so we can use it.
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)	{
        OutputDebugString("create compatible dc failed\n");
        return FALSE;
	}
    SelectObject(hdcImage, hbm);

	if (trans_table == NULL && !notranslate)	{
		trans_table = table;

		UINT colors = GetDIBColorTable(hdcImage, 0, 256, local_palette);
 
		hdc = GetDC(NULL);
		for (int i=0; i<256; i++)	{
			DWORD dw = GetNearestPaletteIndex(current_palette.hpal, RGB(local_palette[i].rgbRed, local_palette[i].rgbGreen, local_palette[i].rgbBlue,));
			trans_table[i] = (BYTE) dw;
		}
		ReleaseDC( NULL, hdc);
	}

    // get size of the bitmap
    GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap

// 	ZeroMemory( &ddsd, sizeof( DDSURFACEDESC ) );
	ddsd.dwSize = sizeof(DDSURFACEDESC);

    if ((hr = pdds->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)) == DD_OK)	{
		size = TranslateBitmapToDD((BYTE *)ddsd.lpSurface, ddsd.lPitch, (BYTE *)bm.bmBits, bm.bmWidth, bm.bmHeight, trans_table); 
        pdds->Unlock(ddsd.lpSurface);
    } else {
		TRACE("Error on Lock in DDCopyBitmap()");
	}

    DeleteDC(hdcImage);

    return size;
}
*/

/*
BOOL DDCopyBitmap(LPDIRECTDRAWSURFACE pdds, HBITMAP hbm, int x, int y)
{
    HDC                 hdcImage;
    HDC                 hdc;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    HRESULT             hr;
	BOOL				ok = FALSE;

    if (hbm == NULL || pdds == NULL)
        return FALSE;

    // make sure this surface is restored.
    pdds->Restore();

    //  select bitmap into a memoryDC so we can use it.
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)	{
        OutputDebugString("create compatible dc failed\n");
        return FALSE;
	}
    SelectObject(hdcImage, hbm);

    // get size of the bitmap
    GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap

    // get size of surface.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

// rather than use a StretchBlt(), do a copy and translation
    if ((hr = pdds->GetDC(&hdc)) == DD_OK)	{
        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, bm.bmWidth, bm.bmHeight, SRCCOPY);
        pdds->ReleaseDC(hdc);
		ok = TRUE;
    } else {
		TRACE("Error on GetDC in DDCopyBitmap()");
	}

    DeleteDC(hdcImage);

    return ok;
}
*/



#ifndef SAVE_OFF
BOOL DDSaveBitmap(char *szBitmap, LPDIRECTDRAWSURFACE pdds)
{
	FILE* pFile;
	DDSURFACEDESC       ddsd;
	BITMAPFILEHEADER	bmfile;
	BITMAPINFO_256		bminfo;
	BYTE				*pBits;
	HBITMAP             hBitmap;
	HDC                 hdcBitmap;
    HDC                 hdcSurface;
	DWORD				bmsize;
	BOOL				ok = FALSE;

    // get size of surface.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    pdds->GetSurfaceDesc(&ddsd);

	bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	bminfo.bmiHeader.biWidth = ddsd.dwWidth; 
	bminfo.bmiHeader.biHeight = ddsd.dwHeight; 
	bminfo.bmiHeader.biPlanes = 1; 
	bminfo.bmiHeader.biBitCount = (unsigned short) ddsd.ddpfPixelFormat.dwRGBBitCount;
	bminfo.bmiHeader.biCompression = BI_RGB; 
	bminfo.bmiHeader.biSizeImage = 0; 
	bminfo.bmiHeader.biXPelsPerMeter = 0; 
	bminfo.bmiHeader.biYPelsPerMeter = 0; 
	bminfo.bmiHeader.biClrUsed = 256; 
	bminfo.bmiHeader.biClrImportant = 256;

	bmsize = ddsd.dwWidth * ddsd.dwHeight * (bminfo.bmiHeader.biBitCount / 8);;
	bminfo.bmiHeader.biSizeImage = bmsize; 

	for ( int i = 0; i < 256; i++ )	{
        bminfo.bmiColors[i].rgbRed = LogicalPalette.aEntries[i].peRed;
        bminfo.bmiColors[i].rgbGreen = LogicalPalette.aEntries[i].peGreen;
        bminfo.bmiColors[i].rgbBlue = LogicalPalette.aEntries[i].peBlue;
        bminfo.bmiColors[i].rgbReserved = 0;
	}

	// get the screen device context
    hdcBitmap = CreateCompatibleDC(NULL);
	if (hdcBitmap)	{
		hBitmap = CreateDIBSection(hdcBitmap, (BITMAPINFO *) &bminfo, DIB_RGB_COLORS, (void **)&pBits, NULL, 0);
		if (hBitmap)	{
			SelectObject(hdcBitmap, hBitmap);

			if (pdds->GetDC(&hdcSurface) == DD_OK)	{
				StretchBlt(hdcBitmap, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcSurface, 0, 0, ddsd.dwWidth, ddsd.dwHeight, SRCCOPY);
				pdds->ReleaseDC(hdcSurface);
			}

			ok = TRUE;
		}
		DeleteDC(hdcBitmap);
	}
	
	bmfile.bfType = 0x4D42;	// 'BM'
	bmfile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO_256) + bmsize; 
	bmfile.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO_256); 

	if (ok)	{
		if ((pFile = fopen( szBitmap, "wb" )) != NULL)	{
			size_t actual;

			TRACE("Saving %s\n",szBitmap);

			// Write the BMP header and info structures
			actual = fwrite( &bmfile, 1, sizeof(BITMAPFILEHEADER), pFile );
			actual = fwrite( &bminfo, 1, sizeof(BITMAPINFO_256), pFile );

			//write the BMP data
			actual = fwrite( pBits, bmsize, 1, pFile );

			fclose(pFile);
		}
	}

	if (hBitmap)
		DeleteObject(hBitmap);

	return ok;
}


BITMAPFILEHEADER	gbmfile;
BITMAPINFO_256		gbminfo;
HDC                 ghdcBitmap;

void DDSetSaveBitmap(LPDIRECTDRAWSURFACE pdds)
{
	DDSURFACEDESC       ddsd;
	DWORD				bmsize;

    // get size of surface.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    pdds->GetSurfaceDesc(&ddsd);

	gbminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	gbminfo.bmiHeader.biWidth = ddsd.dwWidth; 
	gbminfo.bmiHeader.biHeight = ddsd.dwHeight; 
	gbminfo.bmiHeader.biPlanes = 1; 
	gbminfo.bmiHeader.biBitCount = (unsigned short) ddsd.ddpfPixelFormat.dwRGBBitCount;
	gbminfo.bmiHeader.biCompression = BI_RGB; 
	gbminfo.bmiHeader.biSizeImage = 0; 
	gbminfo.bmiHeader.biXPelsPerMeter = 0; 
	gbminfo.bmiHeader.biYPelsPerMeter = 0; 
	gbminfo.bmiHeader.biClrUsed = 256; 
	gbminfo.bmiHeader.biClrImportant = 256;

	bmsize = ddsd.dwWidth * ddsd.dwHeight * (gbminfo.bmiHeader.biBitCount / 8);;
	gbminfo.bmiHeader.biSizeImage = bmsize; 

	for ( int i = 0; i < 256; i++ )	{
        gbminfo.bmiColors[i].rgbRed = LogicalPalette.aEntries[i].peRed;
        gbminfo.bmiColors[i].rgbGreen = LogicalPalette.aEntries[i].peGreen;
        gbminfo.bmiColors[i].rgbBlue = LogicalPalette.aEntries[i].peBlue;
        gbminfo.bmiColors[i].rgbReserved = 0;
	}
	
	gbmfile.bfType = 0x4D42;	// 'BM'
	gbmfile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO_256) + bmsize; 
	gbmfile.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO_256);

	// get the screen device context
    ghdcBitmap = CreateCompatibleDC(NULL);
}


BOOL DDCacheBitmap(LPDIRECTDRAWSURFACE pdds, HBITMAP *bmarray, BYTE **bitarray)
{
	BYTE				*pBits;
	HBITMAP             hBitmap;
    HDC                 hdcSurface;
	BOOL				ok;

	if (ghdcBitmap)	{
		hBitmap = CreateDIBSection(ghdcBitmap, (BITMAPINFO *) &gbminfo, DIB_RGB_COLORS, (void **)&pBits, NULL, 0);
		*bmarray = hBitmap;
		*bitarray = pBits;
		if (hBitmap)	{
			SelectObject(ghdcBitmap, hBitmap);

			if (pdds->GetDC(&hdcSurface) == DD_OK)	{
				StretchBlt(ghdcBitmap, 0, 0, gbminfo.bmiHeader.biWidth, gbminfo.bmiHeader.biHeight, hdcSurface, 0, 0, gbminfo.bmiHeader.biWidth, gbminfo.bmiHeader.biHeight, SRCCOPY);
				pdds->ReleaseDC(hdcSurface);
				TRACE(".");
			}

			ok = TRUE;
		}
	}
	
	return ok;
}


void DDSaveBitmapArray(char *szBitmap, HBITMAP *bmarray, BYTE **bitarray)
{
	FILE* pFile;

	if (*bmarray)	{
		if ((pFile = fopen( szBitmap, "wb" )) != NULL)	{
			size_t actual;

			TRACE("Saving %s\n",szBitmap);

			// Write the BMP header and info structures
			actual = fwrite( &gbmfile, 1, sizeof(BITMAPFILEHEADER), pFile );
			actual = fwrite( &gbminfo, 1, sizeof(BITMAPINFO_256), pFile );

			//write the BMP data
			actual = fwrite( *bitarray, gbminfo.bmiHeader.biSizeImage, 1, pFile );

			fclose(pFile);
		}

		DeleteObject(*bmarray);
		*bmarray = NULL;
		*bitarray = NULL;
	}
}
#endif




