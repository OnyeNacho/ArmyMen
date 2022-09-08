/*
	Header file for Bitmap fonts
*/
typedef enum {
	BMPFONT_DASHCOMM,
	BMPFONT_BUTTON,
	BMPFONT_MAP,
	BMPFONT_LAST
} BMPFONTS;


void InitBitmapFonts( void );
void FreeBitmapFonts( void );
BYTE *BmpTextGetCharData( int fontid, char c );
void BmpTextWrite( LPDIRECTDRAWSURFACE pdds, int x, int y, 
				  char * txt, int fontid = 0, SIZE * sz = NULL, int color = 0 );
void BmpTextWriteLocked( int x, int y, char * txt, int fontid, SIZE * sz, int color );
int BmpTextWidth( char * txt, int fontid = 0, SIZE * sz = NULL);