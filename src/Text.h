//========================================================================
//	FILE:			$Workfile: Text.h $
//
//	DESCRIPTION:	Text defines, structures, and prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Text.h 10    3/11/98 7:10p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Text.h $
//  
//  10    3/11/98 7:10p Nrobinso
//  remove times roman 10
//  
//  9     3/09/98 9:40a Aburgess
//  added FONT_TIMES_18
//  
//  8     2/09/98 7:25p Nrobinso
//  remove unused fonts; create a TextWidth function
//  
//  7     1/19/98 7:46p Aburgess
//  added Times 10pt
//  
//  6     12/09/97 12:12p Phu
//  
//  5     10/30/97 1:49p Aburgess
//  added FONT_CARGO_36
//  
//  4     10/13/97 9:58a Aburgess
//  added Cargo font creation and TextBox prototype
//  
//  2     7/14/97 12:00p Awerner
//  Modified prototype for TextWrite to add a parameter for a SIZE
//  structure which, if non-null, is filled with the size of the text
//  string just written
//  
//  1     7/03/97 5:19p Nrobinso
//  
//  15    5/06/97 7:34p Bwilcox
//  added FONT_DASHCOMM
//  
//  14    3/22/97 12:47p Bwilcox
//  Nikkis changes to support debug_layer display
//  
//  13    3/21/97 5:14p Nrobinso
//  add courier fonr for displaying map attributes
//  
//  12    1/17/97 3:49p Aburgess
//  added DEBUG font
//  
//  11    11/26/96 8:35a Nrobinso
//  let TextWrite() calculate it's own string length
//  
//  10    10/01/96 11:57a Aburgess
//  added new font IDs
//  
//  9     8/28/96 3:03p Aburgess
//  added textDraw prototypes
//  
//  8     8/27/96 3:33p Aburgess
//  added TextSetMode() prototype
//  
//  7     7/31/96 10:37a Aburgess
//  added color setting prototype
//  
//  6     7/26/96 9:27p Nrobins
//  added TextReleaseFont()
//  
//  5     6/26/96 11:24a Aburgess
//  added new Source Control headers
// 
//  $Nokeywords:$
///========================================================================


#ifndef __TEXT_H__
#define __TEXT_H__
//=========================================================================
//						GLOBAL DEFINES
//=========================================================================
#define	TEXT_NORMAL		0x00
#define	TEXT_ITALIC		0x01
#define	TEXT_UNDERLINE	0x02
#define	TEXT_STRIKEOUT	0x04


// Font IDs
typedef enum {
	FONT_TIMES_14 = 0,
	FONT_TIMES_18,
	FONT_TIMES_20,
	FONT_DASHCOMM,
	FONT_CARGO_14,
	FONT_CARGO_20,
	FONT_CARGO_36,
	FONT_MAP,
//	FONT_TIMES_10,
	TEXT_MAX_FONTS
} FONTS;



//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================


//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================
extern	COLORREF  TextTransColor;		// BLACK - for transparency
extern	COLORREF  TextBkColor;			// White
extern	COLORREF  TextFgColor;			// almost Black


//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================
BOOL	TextInit( void );
void	TextExit( void );
BOOL	TextAcquireDC( LPDIRECTDRAWSURFACE pDDS, HDC* pHDC );
void	TextReleaseDC( LPDIRECTDRAWSURFACE pDDS, HDC hdc );
BOOL	TextDraw( HDC hdc, int nXStart, int nYStart, char *pTextString, int nNumberOfChars );
void	TextApplyDrawFont( HDC hdc,  int fontID );
void	TextGetDrawSize( HDC hdc, char* pString, SIZE* pTextSize );
void	TextSetDrawMode( HDC hdc, int eMapMode, int interSpacing );
void	TextSetTransparent(BOOL transparent);
//=========================================================================
RETERROR	TextWrite( LPDIRECTDRAWSURFACE pdds, int nXStart, int nYStart, char *pTextString,
				   int fontID, SIZE *textsize );
BOOL	TextBox( char *pTextString, SBOX *pBox, int fontID );
void	TextApplyFont( LPDIRECTDRAWSURFACE pdds, int fontID );
HFONT	TextBuildFont( char* pTypeFaceName, int nHeight, unsigned short flags );
BOOL	TextReleaseFont( HFONT font );
void	TextGetSize( LPDIRECTDRAWSURFACE pdds, char* pString, SIZE* pTextSize );
void	TextSetColors( COLORREF fgColor, COLORREF bgColor );
void	TextGetColors( COLORREF* fgColor, COLORREF* bgColor );
void	TextSetMode( LPDIRECTDRAWSURFACE pdds, int eMapMode );
int		TextWidth( char *pTextString, int fontID );


#endif		// __TEXT_H__


//=========================================================================
//								EOF
//=========================================================================

