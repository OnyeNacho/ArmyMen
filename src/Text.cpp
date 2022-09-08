//========================================================================
//	FILE:			$Workfile: Text.cpp $
//
//	DESCRIPTION:	Text processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Text.cpp 20    4/02/98 3:35p Phu $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	TextInit()
//		Initialize the Text processing.
//	TextExit()
//		Terminate the Text processor.
//	TextWrite()
//		Write a text string out.
//	TextApplyFont()
//		Specifiy the current Text Font.
//	TextBuildFont()
//		Set the Font size for.
//	TextGetSize()
//		Specifiy the current Text Font.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Text.cpp $
//  
//  20    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  19    3/11/98 7:10p Nrobinso
//  remove times roman 10
//  
//  18    3/09/98 9:40a Aburgess
//  added FONT_TIMES_18
//  
//  17    2/09/98 7:25p Nrobinso
//  remove unused fonts; create a TextWidth function
//  
//  16    1/19/98 7:46p Aburgess
//  added Times 10pt
//  
//  15    12/09/97 12:12p Phu
//  
//  14    10/30/97 1:48p Aburgess
//  added CARGO 36 font
//  
//  13    10/27/97 11:10a Aburgess
//  more debug info
//  
//  12    10/13/97 9:57a Aburgess
//  added Cargo Fonts and TextBox calculation routine
//  
//  10    8/11/97 5:46p Phu
//  Stubs for bitmap font functionality
//  
//  9     8/07/97 11:53p Nrobinso
//  moved globals.h to stdafx.h
//  
//  8     7/18/97 2:43p Phu
//  Fix to fool bounds checker (hopefully)
//  
//  7     7/14/97 4:12p Aburgess
//  added check for NULL string in TextWrite to return a textsize of 0,0.
//  Remvoed redundant call
//  
//  6     7/14/97 1:27p Aburgess
//  corrected function description
//  
//  5     7/14/97 12:00p Awerner
//  Modified prototype for TextWrite to add a parameter for a SIZE
//  structure which, if non-null, is filled with the size of the text
//  string just written
//  
//  4     7/10/97 2:55p Phu
//  
//  3     7/10/97 2:22p Phu
//  
//  2     7/10/97 11:41a Phu
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  22    5/06/97 9:27p Bwilcox
//  actual font height of character used in dashcomm font
//  
//  21    5/06/97 8:38p Bwilcox
//  
//  20    5/06/97 7:56p Bwilcox
//  
//  19    5/06/97 7:34p Bwilcox
//  added FONT_DASHCOMM
//  
//  18    4/17/97 11:22a Awerner
//  
//  17    3/22/97 12:47p Bwilcox
//  Nikkis changes to support debug_layer display
//  
//  16    3/21/97 5:14p Nrobinso
//  add courier fonr for displaying map attributes
//  
//  15    1/17/97 3:46p Aburgess
//  added an INFLUENCE debug font and an interface to get the current text
//  colors
//  
//  14    1/08/97 8:17a Aburgess
//  removed unneeded DEBUG font definition
//  
//  13    11/26/96 8:35a Nrobinso
//  let TextWrite() calculate it's own string length
//  
//  12    10/01/96 11:55a Aburgess
//  added new FONT definitions. Altered interface to accept font IDs rather
//  than HFONT handles, allowing calling sequences to be oblivious of how
//  fonts are formed.
//  
//  11    8/28/96 3:02p Aburgess
//  added textDraw prototypes which acquire the HDC, perform a series of
//  text draws and then releases the HDC.
//  
//  10    8/27/96 3:32p Aburgess
//  attempted to get correct extent values. Cleaned up some locked surface
//  problems.
//  
//  9     8/23/96 9:56a Aburgess
//  changed to use GetExtent32
//  
//  8     7/31/96 10:35a Aburgess
//  converted color specifications to be set with an access routine, making
//  Text more versatile
//  
//  7     7/26/96 9:27p Nrobins
//  added TextReleaseFont()
//  
//  6     6/26/96 10:14a Aburgess
//  added new Source Control header and function descriptions.
// 
//  $Nokeywords:$
///========================================================================


// Includes
#include "stdafx.h"

#include "Text.h"
#include "bmptext.h"


///========================================================================
//							GLOBAL VARIABLES
///========================================================================
COLORREF	TextTransColor;
COLORREF	TextBkColor;
COLORREF	TextFgColor;
HFONT		TextFontRef;


HFONT		TextFonts[ TEXT_MAX_FONTS ];
int			textmode = TRANSPARENT;


///========================================================================
//							LOCAL DEFINES
///========================================================================


///========================================================================
//							LOCAL VARIABLES
///========================================================================
char	TextSample[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
SIZE    TextSampleSize;


///========================================================================
//							LOCAL PROTOTYPES
///========================================================================


///========================================================================
//	Function:		TextInit()
//
//	Description:
//		Initialize the Text processing.
//
//	Input:			none
//
//	Ouput:			error			FALSE if successful, TRUE otherwise
//
///========================================================================


BOOL	TextInit( )
{
	HDC hdc = ::GetDC(NULL);

	TextFontRef = NULL;
	TextTransColor = RGB_TRANSPARENT;
	TextBkColor    = RGB_WHITE;
	TextFgColor    = RGB_BLUE;

	// Setup for text processing
//	TextFonts[ FONT_TIMES_10 ]	= TextBuildFont( "Times New Roman", 10, TEXT_NORMAL );
	TextFonts[ FONT_TIMES_14 ]	= TextBuildFont( "Times New Roman", 14, TEXT_NORMAL );
	TextFonts[ FONT_TIMES_18 ]	= TextBuildFont( "Times New Roman", 18, TEXT_NORMAL );
	TextFonts[ FONT_TIMES_20 ]	= TextBuildFont( "Times New Roman", 20, TEXT_NORMAL );
	TextFonts[ FONT_CARGO_14 ]	= TextBuildFont( "ArialNarrow", 14, TEXT_NORMAL );
	TextFonts[ FONT_CARGO_20 ]	= TextBuildFont( "ArialNarrow", 20, TEXT_NORMAL );
	TextFonts[ FONT_CARGO_36 ]	= TextBuildFont( "ArialNarrow", 36, TEXT_NORMAL );
	TextFonts[ FONT_DASHCOMM ]	= TextBuildFont( "ArialNarrow", -10, TEXT_NORMAL );

#ifndef FINAL
	TextFonts[ FONT_MAP ]		= TextBuildFont( "Courier", 8, TEXT_NORMAL );
#endif

//	TextFonts[ FONT_DASHCOMM ]	= TextBuildFont( "Pica", 
//		-MulDiv(8, GetDeviceCaps(hdc, LOGPIXELSY), 72), TEXT_NORMAL );

	::ReleaseDC(NULL, hdc);

	InitBitmapFonts();

	return( FALSE );
}


///========================================================================
//	Function:		TextExit()
//
//	Description:
//		Terminate the Text processor.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================


void	TextExit( void )
{
	int	font;

	FreeBitmapFonts();

	// free up any font definitions
	for( font=0; font<TEXT_MAX_FONTS; ++font)
	{
		TextReleaseFont( TextFonts[ font ] );
	}

}


///========================================================================
//	Function:		TextAcquireDC()
//
//	Description:
//		Acquire and lock the surface context for future writes.
//
//	Input:			pDDS		pointer to surface whose context handle we want
//					pHDC		where to place the HDC acquired
//
//	Ouput:			error		FALSE if successful, TRUE if failure
//
///========================================================================


BOOL	TextAcquireDC( LPDIRECTDRAWSURFACE pDDS, HDC* pHDC )
{
	HRESULT		result;
	BOOL		error = TRUE;		// assume an error


	// make sure we have a surface to write to
	if ( pDDS == NULL )
	{
		TRACE( "WARNING: illegal surface [%s:%d]\n", __FILE__, __LINE__ );
		goto exit;
	}


    // make sure this surface is restored.
    result = pDDS->Restore();
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to restore device context(%s) [%s:%d]\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// retrieve the device context
	result = pDDS->GetDC( pHDC );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to retrieve device context(%s) [%s:%d]\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// if we made it here we were successful
	error = FALSE;


exit:
	return( error );


}


///========================================================================
//	Function:		TextReleaseDC()
//
//	Description:
//		Terminate the Text processor.
//
//	Input:			pDDS		pointer to surface whose context handle we want
//					hdc			context to be released
//
//	Ouput:			none
//
///========================================================================


void	TextReleaseDC( LPDIRECTDRAWSURFACE pDDS, HDC hdc )
{
	HRESULT		result;


	// release the surface
	result = pDDS->ReleaseDC( hdc );
	if ( result != DD_OK)
		TRACE( "ERROR: failed to release device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
}


///========================================================================
//	Function:		TextDraw()
//
//	Description:
//		Write a text string out.
//
//	Input:			hdc				DirectDraw handle context
//					nXStart			x-coordinate of starting position
//					nYStart			y-coordinate of starting position
//					pTextString		address of string
//					nNumberOfChars	number of characters in string
//
//	Ouput:			none
//
///========================================================================


BOOL TextDraw( HDC hdc, int nXStart, int nYStart, char *pTextString, int nNumberOfChars )
{
	BOOL				error = TRUE;	// assume failure


	// make sure we have something to write
	if ( !nNumberOfChars )
	{
		error = FALSE;
		goto exit;
	}


	// Send some text out into the world
	SetTextColor( hdc, TextFgColor );
	SetBkColor( hdc, TextBkColor );
//	SetBkMode( hdc, TRANSPARENT );
	SetBkMode( hdc, textmode );


	TextOut(hdc, nXStart, nYStart, (LPCTSTR)pTextString, nNumberOfChars );


	// if we got here, we've had a success
	error = FALSE;


exit:
	return( error );
}


///========================================================================
//	Function:		TextApplyDrawFont()
//
//	Description:
//		Specifiy the current Text Font.
//
//	Input:			hdc				DirectDraw handle context
//					hFontDef	    handle of logical font
//
//	Ouput:			none
//
///========================================================================


void	TextApplyDrawFont( HDC hdc, int fontID )
{
	HFONT	hFontDef;


	// acquire the font
	hFontDef = TextFonts[ fontID ];


	// apply the font to this context
    SelectObject(hdc, hFontDef);
}


///========================================================================
//	Function:		TextGetDrawSize()
//
//	Description:
//		Specifiy the current Text Font.
//
//	Input:			hdc			DirectDraw handle context
//					pString			pointer to string whose size we want
//					pTextSize		location to store size
//
//	Ouput:			pTextSize		size of text string.
//
///========================================================================


void	TextGetDrawSize( HDC hdc, char* pString, SIZE* pTextSize )
{
	int					length;


	// make sure we have a line to process. This length is also used to retrieve
	// the extent of the text later,
	length = strlen( pString );
	if ( !length )
	{
		pTextSize->cx = 0;
		pTextSize->cy = 0;
		goto exit;
	}


	// retrieve the size for the current context. Use the length calculated
	// upon entry.
    if ( GetTextExtentPoint32( hdc, pString, length, pTextSize ) == FALSE )
		TRACE( "ERROR: failed to release device context(%s) [%s:%d]\n\n", 
			DDErrorToString(GetLastError()), __FILE__, __LINE__ );


#if 0
	TRACE( "TextGetSize: #chars: %d  string[%s]\n", length, pString );
	TRACE( "TextGetSize: CX =    %d  CY =   %d\n", pTextSize->cx, pTextSize->cy );
#endif


exit:
	return;
}


///========================================================================
//	Function:		TextSetDrawMode()
//
//	Description:
//		Set the mapping mode for the current context.
//
//	Input:			hdc				DirectDraw handle context
//					eMapMode		mode value
//
//	Ouput:			none
//
///========================================================================


void	TextSetDrawMode( HDC hdc, int eMapMode, int interSpacing )
{
	// set the text inter-spacing values
	if ( SetTextCharacterExtra(hdc, interSpacing) == 0x80000000 )
	{
		TRACE( "ERROR: failed to apply text inter spacing.[%s:%d]\n\n", __FILE__, __LINE__ );
		goto exit;
	}


	// set the map mode.
    if ( SetMapMode(hdc, eMapMode) == FALSE )
	{
		TRACE( "ERROR: failed to apply map mode.[%s:%d]\n\n", __FILE__, __LINE__ );
	}


exit:
	return;
}



///========================================================================
//	Function:		TextSetTransparent()
//
//	Description:
//		Set the transparency mode for text writes
//
//	Input:			transparent			if TRUE, transparency mode is set
//
//	Ouput:			none
//
///========================================================================


void	TextSetTransparent( BOOL  transparent)
{
	if (transparent)
		textmode = TRANSPARENT;
	else
		textmode = OPAQUE;
}



///========================================================================
//	Function:		TextWrite()
//
//	Description:
//		Write a text string out.
//
//	Input:			pdds			DirectDraw object to write to
//					nXStart			x-coordinate of starting position
//					nYStart			y-coordinate of starting position
//					pTextString		address of string
//					textsize		pointer to a SIZE structure to fill, or NULL
//
//	Ouput:			none
//
///========================================================================


RETERROR TextWrite( LPDIRECTDRAWSURFACE pdds, int nXStart, int nYStart, char *pTextString,
			    int fontID, SIZE *textsize )
{
    HDC			hdc;
	HFONT		hFontDef;
	HRESULT		result;
	int			nNumberOfChars;
	RETERROR	error = TRUE;	// assume failure
	const COLORREF	TextColorTable[16] =
	{
		0x00ff0000,
		0x0000ff00,
		0x000000ff,
		0x00ffff00,
		0x0000ffff,
		0x00ff00ff,
		0x00000000,
		0x00ffffff,
		0x00800000,
		0x00008000,
		0x00000080,
		0x00ff0080,
		0x0000ff80,
		0x000080ff,
		0x00ff8000,
		0x0080ff00
	};


	// make sure we have a surface to write to
	ASSERT(pdds != NULL );


	// make sure we have something to write
	nNumberOfChars = strlen(pTextString);
	if ( !nNumberOfChars )
	{
		// fill in a zero length text size
		if (textsize)
		{
			textsize->cx = 0;
			textsize->cy = 0;
		}
		error = FALSE;
		goto exit;
	}

	//check for color code
	if (*pTextString == '#')
	{
		if (nNumberOfChars < 2)
		{
			error = FALSE;
			goto exit;
		}
   	    ASSERT ((*(pTextString+1) >= 'a') && (*(pTextString+1) <= 'p' ));
		TextSetColors( TextColorTable[(int)(*(char *)(pTextString+1) - (int)('a'))],
			TextBkColor);
		pTextString = pTextString + 2;
		nNumberOfChars -= 2;
	}

	// acquire the font
	hFontDef = TextFonts[ fontID ];


	// retrieve the device context
	result = pdds->GetDC( &hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to retrieve device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// Send some text out into the world
	SelectObject( hdc, hFontDef );
	SetTextColor( hdc, TextFgColor );
	SetBkColor( hdc, TextBkColor );
//	SetBkMode( hdc, TRANSPARENT );
	SetBkMode( hdc, textmode );


	TextOut(hdc, nXStart, nYStart, (LPCTSTR)pTextString, nNumberOfChars );

	if (textsize)
		TextGetDrawSize( hdc, pTextString, textsize);

	// release the surface
	result = pdds->ReleaseDC( hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to release device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// if we got here, we've had a success
	error = FALSE;


exit:
	return( error );
}


///========================================================================
//	Function:		TextWidth()
//
//	Description:
//		Write a text string out.
//
//	Input:			pTextString		address of string
//					fontID			ID for font to use
//
//	Ouput:			width
//
///========================================================================


int TextWidth( char *pTextString, int fontID )
{
    HDC					hdc;
	HFONT				hFontDef;
	SIZE				textsize;
	int					nNumberOfChars;
	int					width = 0;
	LPDIRECTDRAWSURFACE	pdds  = pFrontBuffer;

	ASSERT( pTextString );

	// make sure we have something to measure
	nNumberOfChars = strlen(pTextString);
	if ( !nNumberOfChars )
		goto exit;

	hFontDef = TextFonts[ fontID ];

	pdds->GetDC( &hdc );

	SelectObject( hdc, hFontDef );
	TextGetDrawSize( hdc, pTextString, &textsize);

	pdds->ReleaseDC( hdc );

	width = textsize.cx;

exit:
	return( width );
}



///========================================================================
//	Function:		TextBox()
//
//	Description:
//		Write a text string out.
//
//	Input:			pTextString		address of string
//					pBox			pointer to a SBOX structure to fill
//					fontID			ID for font to use
//
//	Ouput:			none
//
///========================================================================


BOOL TextBox( char *pTextString, SBOX *pBox, int fontID )
{
    HDC					hdc;
	HFONT				hFontDef;
	HRESULT				result;
	SIZE				textsize;
	int					nNumberOfChars;
	LPDIRECTDRAWSURFACE	pdds  = pFrontBuffer;
	BOOL				bError = TRUE;	// assume failure

	ASSERT( pTextString );
	ASSERT( pBox );

	// make sure we have something to measure
	nNumberOfChars = strlen(pTextString);
	if ( !nNumberOfChars )
	{
		// fill in a zero length text size
		textsize.cx = 0;
		textsize.cy = 0;

		bError = FALSE;
		goto exit;
	}

	// acquire the font
	hFontDef = TextFonts[ fontID ];

	// retrieve the device context
	result = pdds->GetDC( &hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to retrieve device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// Send some text out into the world
	SelectObject( hdc, hFontDef );
	TextGetDrawSize( hdc, pTextString, &textsize);

	// release the surface
	result = pdds->ReleaseDC( hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to release device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}

	// now update the box
	pBox->cx = (short)textsize.cx;
	pBox->cy = (short)textsize.cy;

#ifdef SCREEN_DBG
TRACE( "TextBox(%s): pBox (%d,%d,%d,%d )\n",
		pTextString, pBox->x, pBox->y, pBox->cx,   pBox->cy
	 );
#endif

	// if we got here, we've had a success
	bError = FALSE;

exit:
	return( bError );
}


///========================================================================
//	Function:		TextApplyFont()
//
//	Description:
//		Specifiy the current Text Font.
//
//	Input:			pdds			DirectDraw object to apply font to
//					hFontDef	    handle of logical font
//
//	Ouput:			none
//
///========================================================================


void	TextApplyFont( LPDIRECTDRAWSURFACE pdds, int fontID )
{
    HDC                 hdc;
	HFONT				hFontDef;
	HRESULT				result;


	// acquire the font
	hFontDef = TextFonts[ fontID ];


    // make sure this surface is restored.
    result = pdds->Restore();
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to restore device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// retrieve the device context
	result = pdds->GetDC( &hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to retrieve device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// apply the font to this context
    SelectObject(hdc, hFontDef);


	// release the surface
	result = pdds->ReleaseDC( hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to release device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
	}


exit:
	return;


}


///========================================================================
//	Function:		TextBuildFont()
//
//	Description:
//		Create a font for use
//
//	Input:			pTypeFaceName	pointer to type face name
//					nHeight			default logical height of font
//
//	Ouput:			hNewFont		handle to new font definition
//
///========================================================================


HFONT	TextBuildFont( char* pTypeFaceName, int nHeight, unsigned short flags )
{
	HFONT	hNewFont;


	// make sure we have a real font name
	ASSERT( pTypeFaceName );

	// now create the new font
	hNewFont = CreateFont(
        nHeight,									// logical height of font
        0,										// logical average character width
		0,										// angle of escapement
		0,										// base-line orientation angle
		FW_NORMAL,								// font weight
		((flags & TEXT_ITALIC)?TRUE:FALSE),		// Italic attribute flag
		((flags & TEXT_UNDERLINE)?TRUE:FALSE),	// Underline attribute flag
		((flags & TEXT_STRIKEOUT)?TRUE:FALSE),	// Strikeout attribute flag
        ANSI_CHARSET,							// Character set identifier
        OUT_DEFAULT_PRECIS,						// output precision
        CLIP_DEFAULT_PRECIS,					// clipping precision
        DRAFT_QUALITY,							// output quality,
        VARIABLE_PITCH,							// pitch and family
        pTypeFaceName							// pointer to typeface name string
						);


	// check for errors
	if ( hNewFont == NULL )
	{
		TRACE( "ERROR: failed to create font (%s) [%s:%d]\n\n", 
			DDErrorToString( GetLastError() ), __FILE__, __LINE__ );
		goto exit;
	}


exit:
	return( hNewFont );


}



///========================================================================
//	Function:		TextReleaseFont()
//
//	Description:
//		clean up a font
//
//	Input:			font			handle to font to release
//
//	Ouput:			none
//
///========================================================================


BOOL	TextReleaseFont( HFONT font )
{
	if (font)
		return DeleteObject(font);
	else
		return TRUE;
}



///========================================================================
//	Function:		TextGetSize()
//
//	Description:
//		Retrieve the size of a string.
//
//	Input:			pdds			DirectDraw object to base size on
//					pString			pointer to string whose size we want
//					pTextSize		location to store size
//
//	Ouput:			pTextSize		size of text string.
//
///========================================================================


void	TextGetSize( LPDIRECTDRAWSURFACE pdds, char* pString, SIZE* pTextSize )
{
    HDC                 hdc;
	HRESULT				result;
	int					length;


	// make sure we have a line to process. This length is also used to retrieve
	// the extent of the text later,
	length = strlen( pString );
	if ( !length )
	{
		pTextSize->cx = 0;
		pTextSize->cy = 0;
		goto exit;
	}


    // restore the display surface so we can get the HDC.
    result = pdds->Restore();
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to restore device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// retrieve the device context
	result = pdds->GetDC( &hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to retrieve device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// retrieve the size for the current context. Use the length calculated
	// upon entry.
    if ( GetTextExtentPoint32(hdc, pString, length, pTextSize) == FALSE )
	{
		TRACE( "ERROR: failed to release device context(%s) [%s:%d]\n\n", 
			DDErrorToString(GetLastError()), __FILE__, __LINE__ );
		goto cleanUp;
	}


cleanUp:
	// release the surface
	result = pdds->ReleaseDC( hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to release device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
	}


#if 0
	TRACE( "TextGetSize: #chars: %d  string[%s]\n", length, pString );
	TRACE( "TextGetSize: CX =    %d  CY =   %d\n", pTextSize->cx, pTextSize->cy );
#endif


exit:
	return;


}


///========================================================================
//	Function:		TextSetColors()
//
//	Description:
//		set the current foreground and background colors for text output.
//
//	Input:			fgColor		Text foreground color value
//					bgColor		Text background color value
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================


void	TextSetColors( COLORREF fgColor, COLORREF bgColor )
{
	// Set the colors
	TextFgColor = fgColor;
	TextBkColor = bgColor;
}


///========================================================================
//	Function:		TextGetColors()
//
//	Description:
//		retrieve the current foreground and background colors for text output.
//
//	Input:			fgColor		Text foreground color value
//					bgColor		Text background color value
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================


void	TextGetColors( COLORREF* fgColor, COLORREF* bgColor )
{
	// Set the colors
	*fgColor = TextFgColor;
	*bgColor = TextBkColor;
}


///========================================================================
//	Function:		TextSetMode()
//
//	Description:
//		Specifiy the current Text mapping mode.
//
//	Input:			pdds			DirectDraw object to apply font to
//					eMapMode		mode value
//
//	Ouput:			none
//
///========================================================================


void	TextSetMode( LPDIRECTDRAWSURFACE pdds, int eMapMode )
{
    HDC                 hdc;
	HRESULT				result;


    // restore the display surface so we can get the HDC.
    result = pdds->Restore();
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to restore device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// retrieve the device context
	result = pdds->GetDC( &hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to retrieve device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
		goto exit;
	}


	// set the text inter-spacing values
	if ( SetTextCharacterExtra(hdc, 2) == 0x80000000 )
	{
		TRACE( "ERROR: failed to apply text inter spacing.[%s:%d]\n\n", __FILE__, __LINE__ );
		goto cleanUp;
	}


	// set the map mode.
    if ( SetMapMode(hdc, MM_TEXT) == FALSE )
	{
		TRACE( "ERROR: failed to apply map mode.[%s:%d]\n\n", __FILE__, __LINE__ );
	}


cleanUp:
	// release the surface
	result = pdds->ReleaseDC( hdc );
	if ( result != DD_OK)
	{
		TRACE( "ERROR: failed to release device context(%s) [%s:%d]\n\n", 
			DDErrorToString(result), __FILE__, __LINE__ );
	}
exit:
	return;
}


///========================================================================
//								EOF
///========================================================================

