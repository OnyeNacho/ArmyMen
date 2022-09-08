/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Dd.h $
//
//	DESCRIPTION:	Interface for routines for loading bitmap and palettes from resources
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, May 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Dd.h 40    4/02/98 2:50p Phu $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/Dd.h $
//  
//  40    4/02/98 2:50p Phu
//  
//  39    4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  38    3/27/98 2:02p Phu
//  survive alt-tab
//  
//  37    3/27/98 1:49p Phu
//  survive ALT_TAB dammit
//  
//  36    3/19/98 11:21p Nrobinso
//  
//  35    3/11/98 10:20p Nrobinso
//  new ClipRect
//  
//  34    2/09/98 6:55p Phu
//  true line clipping function
//  
//  33    2/06/98 3:56p Phu
//  real collision using the bmp for vehicles/units
//  better damage control on vehicles
//  
//  32    12/24/97 4:47p Bwilcox
//  removed DrawExxx functions
//  
//  31    12/23/97 6:01p Phu
//  anim shadows
//  
//  30    12/21/97 3:26p Phu
//  shade table loading
//  
//  29    12/12/97 12:24p Phu
//  
//  28    12/11/97 9:51a Phu
//  
//  27    12/09/97 12:12p Phu
//  
//  26    12/04/97 6:48p Phu
//  add scarring, improved palette shifting, shadow-only sprites
//  
//  25    12/04/97 2:37p Phu
//  
//  24    12/01/97 9:23p Nrobinso
//  add copybacktofront routine
//  
//  23    11/20/97 11:34a Nrobinso
//  change DrawRect to FillRect function
//  
//  22    11/19/97 10:08a Nrobinso
//  fix bug in FillRectFront; move DrawRect functions in from ui.cpp; make
//  all rgb colors intor COLORREFs
//  
//  21    11/11/97 9:30p Nrobinso
//  collapse sprite flags
//  
//  20    10/27/97 11:24a Aburgess
//  added FillRectFront
//  
//  19    10/24/97 2:03p Awerner
//  First checkin of special vehicle firing code
//  
//  18    10/15/97 10:43a Phu
//  New DD line & point & rect f()s
//  
//  17    10/13/97 2:54p Phu
//  modified displayspriteclipped to clip to an arbitrary window
//  
//  16    10/10/97 3:46p Awerner
//  The small map is now fully funcitonal, although I've commented out the
//  drawing of the dots, because it's _very_ slow right now
//  
//  15    9/30/97 4:00p Phu
//  New display engine!
//  
//  13    8/25/97 5:56p Phu
//  Optimized inline shaded shadow blits
//  
//  12    8/21/97 10:07a Phu
//  Shadow Blitting
//  
//  11    8/20/97 9:30a Phu
//  Shade function stubs
//  
//  10    8/20/97 8:35a Phu
//  Load & Attach shadow files.  Draw shadows in black.
//  
//  9     8/12/97 7:06a Phu
//  RLE Text functions
//  
//  8     8/08/97 12:16p Phu
//  RLE Optimizations
//  
//  7     7/30/97 7:06p Phu
//  WORD vs DWORD line table RLE functions
//  
//  6     7/24/97 3:32p Phu
//  Lock/Unlock during display area update only when necessary
//  
//  5     7/24/97 12:04p Phu
//  Inside RLE256 function
//  
//  4     7/23/97 7:25p Phu
//  Now handles RLE256 objects w/ regular masking for library load only
//  
//  3     7/23/97 11:26a Phu
//  Load objects from library file
//  
//  2     7/15/97 2:24p Awerner
//  Added ScreenToWorld() function
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  47    6/05/97 5:26p Nrobinso
//  add DrawDotFront() and DrawLineFront()
//  
//  46    5/13/97 8:29p Nrobinso
//  add a prototype
//  
//  45    5/13/97 3:49p Nrobinso
//  add the BM_FORCE_OPQUE flag, which uses 255 instead of the upper left
//  corner for transparent
//  
//  44    5/09/97 11:36a Aburgess
//  clipline prototypes added
//  
//  43    4/30/97 12:00p Aburgess
//  multi-draw prototypes added
//  
//  42    4/09/97 8:00a Nrobinso
//  add ability to set palettes
//  
//  41    4/01/97 9:05p Nrobinso
//  ClipRectToBackWindow becomes ClipRectToGameWindow
//  
//  40    4/01/97 6:33p Nrobinso
//  make file read macros easier to error check
//  
//  39    3/28/97 11:05a Nrobinso
//  add LoadMask() for mask bitmaps
//  
//  38    3/20/97 1:41p Bwilcox
//  added DrawELine
//  
//  37    3/19/97 5:06p Bwilcox
//  added DrawEDot for doing epoints instead of spoints
//  
//  36    3/19/97 9:57a Nrobinso
//  fix InRect & InBox; add ClipRect, ClipSPoint, ValidateSpoint and MinMax
//  founctions
//  
//  35    3/18/97 5:51p Nrobinso
//  new DrawDot(); move InRect and InBox into DD.cpp
//  
//  34    3/17/97 11:45a Nrobinso
//  switched to SBOX's from BOX's; fixed a pointer going beyond it's memory
//  block
//  
//  33    3/12/97 3:39p Nrobinso
//  load already RLE images; remove dependence on CreateDIB
//  
//  31    2/20/97 1:32p Aburgess
//  Conversion from POINT to SPOINT
//  
//  30    1/27/97 4:54p Nrobinso
//  Add RLETranslateBlt() and RLEFastBlt(); Fix off by one bug in
//  TranslateBlt routines
//  
//  29    1/24/97 5:44p Nrobinso
//  combine the LoadBitmap() processes for normal & RLE bitmaps
//  
//  28    1/23/97 5:31p Nrobinso
//  Add RLE Sprites, translated and not
//  
//  27    1/21/97 6:48p Nrobinso
//  switched to our own translation when laoding bitmaps; added a
//  recoloring blitter
//  
//  26    1/16/97 12:10p Nrobinso
//  Added color translation to bitmap copies
//  
//  25    1/15/97 9:48p Nrobinso
//  Add direct copied bitmap load
//  
//  24    97-01-09 16:42 Ereich
//  Added #ifndef/#endif around code...
//  
//  23    1/07/97 10:28a Aburgess
//  added DrawDot prototype
//  
//  22    12/11/96 9:41a Lozer
//  DrawLine() now takes rgb COLORREF instead of palette index.
//  
//  21    12/10/96 5:33p Nrobinso
//   Added a world_coordiantes BOOL tp DrawLine()
//  
//  20    12/06/96 2:50p Lozer
//  Added DrawLine
//  
//  19    12/05/96 9:33a Nrobinso
//  save originally loaded palette information
//  
//  18    12/05/96 8:40a Nrobinso
//  Add FillRect()
//  
//  17    96-12-04 13:50 Ereich
//  4-functions from MainFrm.cpp were moved to Dd.cpp for organizational
//  reasons.
//  
//  16    11/26/96 10:49a Nrobinso
//  Add DDColorMatch()
//  
//  15    10/07/96 12:45p Nrobinso
//  DDSetColorKey() returns the color index set
//  
//  14    9/29/96 5:33p Nrobinso
//  Add screen shot capability
//  
//  13    9/10/96 12:59p Aburgess
//  move commonly used but infrequently changed header files to stdafx.h
//  (precompiled header)
//  
//  12    96-09-09 21:27 Ereich
//  Add getOurPalette()
//  
//  11    8/28/96 3:02p Aburgess
//  added BM_OWNDC
//  
//  10    8/14/96 7:53p Nrobins
//  allow switching of palettes
//  
//  9     8/09/96 4:46p Nrobins
//  Changed ClipRect() to ClipRectToBackWindow(); Added RectIntersect() and
//  BoxIntersect()
//  
//  8     7/31/96 9:10p Nrobins
//  Moved ClipRect here from Map.h
//  
//  7     7/26/96 9:20p Nrobins
//  Moved CreateSurfaceOfSize() from Mainfrm.cpp; removed dd object passing
//  to DDLoadBitmap()
//  
//  6     7/24/96 6:18p Nrobins
//  move dd bitmap flags from sprite.h and make them more general than just
//  for sprites
//  
//  4     7/08/96 4:08p Nrobins
//  Added ReadDDBitmap() for already open files
// 
// 3     6/25/96 9:53p Nrobins
// added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __DD_H__
#define	__DD_H__
#define INIT_DD_STRUCT(structure, structname) {ZeroMemory( &structure, sizeof( structname ) ); structure.dwSize = sizeof(structname);}

typedef struct pal
{
  WORD Version;
  WORD NumberOfEntries;
  PALETTEENTRY aEntries[256];
} pal;

typedef struct LOADBITMAP {
	void	*pGraphic;
	LONG	width;
	LONG	height;
	LONG	xppm;		// x pixels per meter or x hotspot
	LONG	yppm; 		// y pixels per meter or y hotspot
	LONG	flags;
	DWORD	xpc;
} LOADBITMAP;

typedef struct PALETTE {
	HPALETTE				hpal;
	LPDIRECTDRAWPALETTE		pDDPalette;
} PALETTE;

// dd bitmap flags
#define BM_TRANSPARENT		0x00
#define BM_DEFAULTMEMORY	0x00

#define BM_OPAQUE			0x01
#define BM_RLE				0x02
#define BM_DRLE				0x04
#define BM_WRLE				0x08
#define BM_TRLE				0x10
#define BM_SRLE				0x20
#define BM_SYSTEMMEMORY		0x40
#define BM_NOTRANSLATE		0x80
#define BM_FORCE_OPAQUE		0x100
#define BM_ANIM_SHADOW		0x200
#define BM_USEBMPASMASK     0x400

// non-user flag
#define BM_RLE_ONLOAD		0x8000
#define BM_DRLE_ONLOAD		0x0100
#define BM_WRLE_ONLOAD		0x0200
#define BM_TRLE_ONLOAD		0x0400

//The current global palette
extern PALETTE		current_palette;

extern pal OriginalPalette;	// the original palette, as loaded

extern BOOL LOCK_STATUS;
extern BOOL LOCK_COMPLEX_ON;
extern BYTE * SCRPTR;
extern BYTE DDCOLOR;
extern DWORD LPITCH;
extern BOOL ODDLINE;
extern RECT * pClipRect;
extern BYTE * PSHADE_TABLE;
extern BYTE * PLIGHT_TABLE;
extern BYTE * PShadeTable;


LPDIRECTDRAWSURFACE	CreateSurfaceOfSize(DWORD width, DWORD height, LONG flags, COLORREF rgb);
BOOL MakeIdentityPalette  ( char *bmp, PALETTE *pPalette);
void FreeIdentityPalette  ( PALETTE *pPalette);
BOOL SetCurrentPalette();
BOOL SetPalette(PALETTE *pPalette);
extern	void		ForceLoadIdentityPalette(char *terrain_name);
extern	void		LoadIdentityPalette(char *terrain_name);
void CreateShadeTable( char *palfile, BYTE *shadetable );


DWORD MakeBitmap(BITMAPINFO_256 *pbminfo, BYTE *pSrc, LOADBITMAP *plbitmap, BYTE *trans_table);

void DDSetColorKey(LPDIRECTDRAWSURFACE pdds, COLORREF xpc);
BOOL DDClearSurface( LPDIRECTDRAWSURFACE pdds, COLORREF rgb );
BOOL DDCopyBackToFront( void );

BOOL EraseSurfaces();
BOOL EraseVisibleSurface();
BOOL EraseBackSurface( void );

HRESULT FillRect(RECT *prect, COLORREF rgb);
HRESULT FillRectFront( RECT *prect, COLORREF rgb );
HRESULT FillTransRectFront(RECT* pRect, BYTE* pShadeTable );

BOOL DDFail(const char* err_str, HRESULT ddrval);
DWORD DDColorMatch(LPDIRECTDRAWSURFACE pdds, COLORREF rgb);
DWORD BitmapColorMatch(BITMAP *bm, COLORREF rgb);

BOOL DDSaveBitmap(char *szBitmap, LPDIRECTDRAWSURFACE pdds);
void DDSetSaveBitmap(LPDIRECTDRAWSURFACE pdds);
BOOL DDCacheBitmap(LPDIRECTDRAWSURFACE pdds, HBITMAP *bmarray, BYTE **bitarray);
void DDSaveBitmapArray(char *szBitmap, HBITMAP *bmarray, BYTE **bitarray);

BOOL InitBackBufferLockComplex( void );
void FreeBackBufferLockComplex( void );
void DDPutPixel( int x, int y );
void DDVLine( int x, int y1, int y2 );
void DDHLine( int y, int x1, int x2 );
void DDRect( int x1, int y1, int x2, int y2 );


HDC   DrawOpen( void );
void  DrawLine( SPOINT* pStart, SPOINT* pEnd, COLORREF rgb, BOOL world_coordinates );
void  DrawMultiLine( HDC hdc, SPOINT* pStart, SPOINT* pEnd, COLORREF rgb, BOOL world_coordinates );
void ScreenDrawDot( SPOINT* pPoint, COLORREF rgb );


void  DrawDotFront( SPOINT* pPoint, COLORREF rgb );
void  DrawDot( SPOINT* pPoint, COLORREF rgb );
void  DrawLineFront( SPOINT* pStart, SPOINT* pEnd, COLORREF rgb, BOOL world_coordinates );

void  DrawClose( HDC hdc );
void  ScreenClipLine(SPOINT *pStart, SPOINT *pEnd);
BOOL  ClipLine(SPOINT *pStart, SPOINT *pEnd);

BOOL DDTranslateBlt(BYTE* pDestStart, long lPitchDest, const BYTE* pSrcStart, long lPitchSrc,
					const RECT* rcSrc, const DWORD xpc, const BYTE table[256]);

BOOL IsPointInDRle( WORD offX, WORD offY, BYTE * buf );
BOOL IsPointInWRle( WORD offX, WORD offY, BYTE * buf );
BOOL RLEFastBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int	iLines );
BOOL RLETranslateBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int	iLines, const BYTE table[256] );

BOOL RLEFastBltClipped( void* pDestStart, long lPitchDest,
					const BYTE* pSrcStart, 	const RECT& rcSrc );
BOOL RLETranslateBltClipped( void* pDestStart, long lPitchDest,
					const BYTE* pSrcStart, const RECT& rcSrc, const BYTE table[256]);

void __fastcall DrawDRleClipped( DWORD x, DWORD y, BYTE * buf, RECT rc );
void __fastcall DrawWRleClipped( DWORD x, DWORD y, BYTE * buf, RECT rc );
void __fastcall DrawTRleClipped( DWORD x, DWORD y, BYTE * buf, RECT rc, BYTE * ttable );
void __fastcall DrawRleChar( DWORD x, DWORD y, BYTE * buf, BYTE c );
void __fastcall DrawSRleClippedDither( DWORD x, DWORD y, BYTE * buf, RECT rc);
void __fastcall DrawSRleClippedShade( DWORD x, DWORD y, BYTE * buf, RECT rc);
void __fastcall DrawSRleClippedColor( DWORD x, DWORD y, BYTE * buf, RECT rc, BYTE color);
DWORD BitmapToDRle(BYTE * pBMStart, BYTE ** rle, int width, int height, COLORREF xpc, BYTE *trans_table);

void DrawScreenRect( LPDIRECTDRAWSURFACE pSurface, RECT &rect, COLORREF rgb );


DWORD BitmapSize();
void BitmapSizeInit();

BOOL InRect(RECT *pRect, SPOINT *pPos);
BOOL InBox(SBOX *pBox, SPOINT *pPos);
SHORT ShortMinMax(SHORT value, SHORT min, SHORT max);
LONG LongMinMax(LONG value, LONG min, LONG max);
void ClipSPoint(SPOINT *ppoint, RECT *pBounds);
void ValidateSPoint(SPOINT *ppoint, RECT *pBounds);
BOOL ClipRect( RECT &a, RECT &b );
BOOL ClipRectToGameWindow(RECT *prcSprite, LONG *px, LONG *py, RECT *pRectOut);
BOOL RectIntersect(RECT *pRect1, RECT *pRect2, RECT *pRectOut);
BOOL BoxIntersect(SBOX *pBox1, SBOX *pBox2, SBOX *pBoxOut);
int ClipLine( SPOINT &a, SPOINT &b, RECT &rc );

void ScreenToWorld(SPOINT *pPoint);
void WorldToScreen(SPOINT *pPoint);

void DrawShadeSpriteToOverlayLayer( int x, int y, BYTE *data, RECT &rect, BYTE *ShadeTable );
BOOL LockOverlayLayer( void );
void UnlockOverlayLayer( void );


#endif	//ndef __DD_H__
