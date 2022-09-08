/*
	Includes
*/
#include "stdafx.h"

#include "text.h"
#include "mainfrm.h"
#include "bmptext.h"


/*
	Globals
*/
int		NumBitmapFonts = 0;
void **	TblBitmapFonts = NULL;
BYTE	TEXT_COLOR_TABLE[32] = {
	0,
	DK_RED_IDX,
	DK_GREEN_IDX,
	BROWN_IDX,
	DK_BLUE_IDX,
	DK_MAGENTA_IDX,
	DK_CYAN_IDX,
	GREY_IDX,
	DK_GREY_IDX,
	RED_IDX,
	GREEN_IDX,
	YELLOW_IDX,
	BLUE_IDX,
	MAGENTA_IDX,
	CYAN_IDX,
	WHITE_IDX,
	BLACK_IDX,
	DK_RED_IDX,
	DK_GREEN_IDX,
	BROWN_IDX,
	DK_BLUE_IDX,
	DK_MAGENTA_IDX,
	DK_CYAN_IDX,
	GREY_IDX,
	DK_GREY_IDX,
	RED_IDX,
	GREEN_IDX,
	YELLOW_IDX,
	BLUE_IDX,
	MAGENTA_IDX,
	CYAN_IDX,
	WHITE_IDX
};


char testchar = 0;


BYTE *BmpTextGetCharData( int fontid, char c )
{
	WORD *tbl;

	tbl = (WORD *)(TblBitmapFonts[fontid]);
	return( (BYTE *)(tbl) + *(WORD *)( tbl + (c-32) ) );
}


void BmpTextWrite( LPDIRECTDRAWSURFACE pdds, int x, int y, char * txt, int fontid, SIZE * sz, int color )
{
	HRESULT			ddrval;
	DDSURFACEDESC	ddsd;
	int   i, j, l, t;
	SIZE  tsz;
	WORD * tbl;

	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddrval = pdds->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
	tbl = (WORD *)(TblBitmapFonts[fontid]);
	if ( ddrval == DD_OK )
	{
		SCRPTR = (BYTE *)ddsd.lpSurface;
		LPITCH = ddsd.lPitch;

		if ( sz == NULL )
		{
			tsz.cx = 640 - x - 16;
			tsz.cy = 480 - y;
		}
		else
		{
			tsz.cx = sz->cx;
			tsz.cy = sz->cy;
		}
		l = strlen( txt );
		i = x;
		j = y;
		t = 0;
		if( l >= 2 && txt[0] == '#' )
			t = 2;
		for( int s = t; s < l; s++ )
		{
			unsigned char c;
			BYTE * buf;
			WORD ht, wd;

			c = txt[s];
			if( c < 32 )
			{
				color = TEXT_COLOR_TABLE[c];
			}
			else
			{
				RECT srect;
				buf = (BYTE *)(tbl) + *(WORD *)( tbl + (c-32) );
//				buf = (BYTE *)(tbl) + *(WORD *)( tbl + (testchar++) );
//				if( testchar > 95 )
//					testchar = 0;
				wd = *(WORD *)buf;
				ht = *((WORD *)(buf + 2));

				srect.left = 0;
				srect.top = 0;
				srect.right = wd;
				srect.bottom = ht;

				if( i + wd > x + tsz.cx )
				{
					j += ht;
					i = x;
				}
				if( j + ht > y + tsz.cy )
					break;

				DrawSRleClippedColor( i, j, buf, srect, color );
				i += wd;
			}
		}

		pdds->Unlock(SCRPTR);
	}
}



void BmpTextWriteLocked( int x, int y, char * txt, int fontid, SIZE * sz, int color )
{
	int   i, j, l, t;
	SIZE  tsz;
	WORD * tbl;

	tbl = (WORD *)(TblBitmapFonts[fontid]);
	if ( sz == NULL )
	{
		tsz.cx = 640 - x - 16;
		tsz.cy = 480 - y;
	}
	else
	{
		tsz.cx = sz->cx;
		tsz.cy = sz->cy;
	}
	l = strlen( txt );
	i = x;
	j = y;
	t = 0;
	if( l >= 2 && txt[0] == '#' )
		t = 2;
	for( int s = t; s < l; s++ )
	{
		char c;
		BYTE * buf;
		WORD ht, wd;

		c = txt[s];
		if( c < 32 )
		{
			color = TEXT_COLOR_TABLE[c];
		}
		else
		{
			RECT srect;
			buf = (BYTE *)(tbl) + *(WORD *)( tbl + (c-32) );
			wd = *(WORD *)buf;
			ht = *((WORD *)(buf + 2));

			srect.left = 0;
			srect.top = 0;
			srect.right = wd;
			srect.bottom = ht;
			if( i + wd > x + tsz.cx )
			{
				j += ht;
				i = x;
			}
			if( j + ht > y + tsz.cy )
				break;

			DrawSRleClippedColor( i, j, buf, srect, color );
			i += wd;
		}
	}
}


//	return the width of a piece of text
int BmpTextWidth( char * txt, int fontid, SIZE * sz )
{
	int i, width;
	WORD *tbl;
	BYTE *buf;
	char c;

	width = 0;
	i = 0;

	tbl = (WORD *)(TblBitmapFonts[fontid]);
	while( txt[i] != 0 )
	{
		c = txt[i];
		if( c >= 31 )
		{
			buf = (BYTE *)(tbl) + *(WORD *)( tbl + (c-32) );
			width += *(WORD *)(buf);
		}
		i++;
	}

	if( sz != NULL )
	{
		sz->cx = width;
		buf = (BYTE *)(tbl) + *(WORD *)( tbl + 1 );
		sz->cy = *(((WORD *)buf) + 1);
	}
	return( width ); 
}	// BmpTextWidth


int EncodeRleChar( BYTE * bp, SIZE sz, int MaxSize )
{
	HRESULT			ddrval;
	DDSURFACEDESC	ddsd;
	BYTE *	SCRPTR;
	DWORD	LPITCH;
	int		size = 0;

	ASSERT( MaxSize >= 100 );
	*bp++ = (BYTE)sz.cx;
	*bp++ = (BYTE)sz.cy;
	size += 2;

	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddrval = pBackBuffer->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
	if ( ddrval == DD_OK )
	{
		SCRPTR = (BYTE *)ddsd.lpSurface;
		LPITCH = ddsd.lPitch;

		int  j = 0,
			 count;
		BYTE *sp, *spEnd, *spLine;
		BYTE xpc;

		sp = SCRPTR;
		xpc = *(BYTE *)(SCRPTR + 100 * LPITCH);

		while( j < sz.cy )	
		{
			spLine = sp;
			spEnd = sp + sz.cx;
			while( TRUE )	
			{
				//	Count forward till we hit a non-transparent pixel.
				count = 0;
				while( sp < spEnd && *sp == xpc && count < 254 )
				{
					sp++;
					count++;
				}
				//	Write # of transparent pixels.
				*bp++ = count;
				size++;
				ASSERT( size <= MaxSize );

				//	Count forward till we hit a transparent pixel.
				count = 0;
				while( sp < spEnd && *sp != xpc && count < 254 )
				{
					sp++;
					count++;
				}
				//	Write # of non-transparent pixels.
				*bp++ = count;
				size++;
				ASSERT(size <= MaxSize);

				// if we reached the end of a line, mark it with an 0xFF value
				if( sp == spEnd )	
				{
					*bp++ = 0xFF;
					size++;
					ASSERT(size <= MaxSize);
					break;
				}
			}
			j++;
			sp = spLine + LPITCH;
		}

		// clear 25x25 area for next font
		sp = SCRPTR;
		for( j = 0; j < 25; j++ )
		{
			memset( sp, xpc, 25 );
			sp += LPITCH;
		}
		pBackBuffer->Unlock( SCRPTR );
	}			

	return (size);
}


int EncodeSRleChar( BYTE * bp, SIZE sz, int MaxSize )
{
	HRESULT			ddrval;
	DDSURFACEDESC	ddsd;
	BYTE			*SCRPTR;
	DWORD			LPITCH;
	int				size = 0;
	WORD			*linetable;
	BYTE			*start;

	ASSERT( MaxSize >= 256 );
	start = bp;
	*(WORD *)bp = (WORD)sz.cx;
	*(WORD *)(bp + 2) = (WORD)sz.cy;
	bp += 4;
	size += 4;
	linetable = (WORD *)bp;
	bp += (sizeof(WORD) * sz.cy);
	size += (sizeof(WORD) * sz.cy);

	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddrval = pBackBuffer->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
	if ( ddrval == DD_OK )
	{
		SCRPTR = (BYTE *)ddsd.lpSurface;
		LPITCH = ddsd.lPitch;

		int  j = 0,
			 count;
		BYTE *sp, *spEnd, *spLine;
		BYTE xpc;

		sp = SCRPTR;
		xpc = *(BYTE *)(SCRPTR + 100 * LPITCH);

		while( j < sz.cy )	
		{
			*(linetable + j) = bp - (BYTE*)start;
			spLine = sp;
			spEnd = sp + sz.cx;
			while( TRUE )	
			{
				//	Count forward till we hit a non-transparent pixel.
				count = 0;
				while( (sp < spEnd) && (*sp == xpc) && (count < 254) )
				{
					sp++;
					count++;
				}
				//	Write # of transparent pixels.
				*bp++ = count;
				size++;
				ASSERT( size <= MaxSize );

				//	Count forward till we hit a transparent pixel.
				count = 0;
				while( (sp < spEnd) && (*sp != xpc) && (count < 254) )
				{
					sp++;
					count++;
				}
				//	Write # of non-transparent pixels.
				*bp++ = count;
				size++;
				ASSERT(size <= MaxSize);

				if( sp == spEnd )
					break;
			}
			j++;
			sp = spLine + LPITCH;
		}

		// clear 25x25 area for next font
		sp = SCRPTR;
		for( j = 0; j < 25; j++ )
		{
			memset( sp, xpc, 25 );
			sp += LPITCH;
		}
		pBackBuffer->Unlock( SCRPTR );
	}			

	return (size);
}


/*
	Functions
*/
#define FontBufferSize 32768
int MakeBitmapFont( int fontid )
{
	BYTE *	buf;
	BYTE *  bptr;
	WORD * lut;
	int	 size;

	DDClearSurface( pBackBuffer, TextTransColor );

	buf = (BYTE *)malloc( FontBufferSize );
	lut = (WORD *)buf;
	bptr = buf + sizeof(WORD) * 96;

	for( int c = 32; c < 128; c++ )
	{
		char str[5];
		SIZE sz;

		*(lut + c-32) = bptr - buf;
		sprintf( str, "#a%c", (char)c );
		TextWrite( pBackBuffer, 0, 0, str, fontid, &sz );
		size = EncodeSRleChar( bptr, sz, FontBufferSize - (bptr-buf) );
		bptr += size;
	}

	size = bptr - buf;
	TblBitmapFonts[ NumBitmapFonts ] = malloc( size );
	memcpy( TblBitmapFonts[NumBitmapFonts], buf, size );
	free( buf );
	NumBitmapFonts++;

	return NumBitmapFonts;
}


void FreeBitmapFonts( void )
{
	for( int i = 0; i < NumBitmapFonts; i++ )
	{
		if( TblBitmapFonts[i] != NULL )
			free( TblBitmapFonts[i] );
		TblBitmapFonts[i] = NULL;
	}
	if( TblBitmapFonts )
	{
		free( TblBitmapFonts );
		TblBitmapFonts = NULL;
	}
	NumBitmapFonts = 0;
}


void InitBitmapFonts( void )
{
	FreeBitmapFonts();

	TextSetTransparent( TRUE );

	TblBitmapFonts = (void **)malloc((int)BMPFONT_LAST * sizeof(void *));
	MakeBitmapFont( FONT_DASHCOMM );
	MakeBitmapFont( FONT_TIMES_20 );
	MakeBitmapFont( FONT_MAP );

#if 0
	MakeBitmapFont( FONT_CARGO_14 );
	MakeBitmapFont( FONT_CARGO_20 );
	MakeBitmapFont( FONT_CARGO_36 );
#endif
}




