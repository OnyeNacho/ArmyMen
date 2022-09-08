/*
	Objects Directory Compiler
	Peter Hu
	980129

	Compiles all of the objects in a terrain folder into a data file

	SYNTAX:
	compobj.exe terrainpath
*/


/*
	INCLUDE
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <conio.h>
#include <windows.h>
#include <sys\stat.h>
#include <time.h>


/*
	MAJOR DEFINES
*/
#define MAX_NUM_OBJECTS		4096
#define MAXHOTSPOTOFFSET	680

#define CAT_FLAMEBURST	400
#define CAT_FOGTILES	401
#define CAT_FRAGCOUNTER	402
#define CAT_MUZZLEFLASH	403
#define CAT_SCAR		407
#define CAT_SMOKE		408
#define CAT_STRIPES		409
#define CAT_BODYPARTS	410
#define CAT_AIRSUPPORT	411
#define CAT_PARACHUTE	412
#define CAT_FIRE		413
#define CAT_FLAG		414


/*
	SPRITE FLAGS
*/
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

#define SP_DRLE				BM_DRLE
#define SP_WRLE				BM_WRLE
#define SP_TRLE				BM_TRLE
#define SP_SRLE				BM_SRLE
#define SP_MASKRECT			0x20
#define SP_PRIMEMASK		0x40
#define SP_USESELFRECT      0x80


/*
	TYPES
*/
typedef struct BITMAPINFO_256
{
  BITMAPINFOHEADER  bmiHeader;
  RGBQUAD           bmiColors[256];
} BITMAPINFO_256;


struct ObjectTableEntry
{
	DWORD	key;
	DWORD	offset;
};


struct SPOINT
{
	short	x, y;
};


/*
	GLOBALS
*/
char	TERRAIN_PATH[128] = {""};
FILE	*hfp;
FILE	*dfp;
int		FILEID = 132415161;
RGBQUAD	mainPalette[256];
BYTE	trans_table[256];
int		numobjects = 0;
ObjectTableEntry ObjectTable[MAX_NUM_OBJECTS];


/*
	Bitwise Functions
*/
BOOL isBitSet( BYTE *pBits, int i, int j, int ht, int sPitch )
{
	BYTE b = *(BYTE *)(pBits + (ht - j - 1) * sPitch + (i >> 3) );
	BYTE bit = 7 - (i % 8);
	return ( b & (1 << bit) );
}


/*
	Palette Functions
*/
int  RGBDiff( RGBQUAD &a, RGBQUAD &b )
{
	int dr, dg, db;

	dr = abs( a.rgbRed - b.rgbRed );
	dg = abs( a.rgbGreen - b.rgbGreen );
	db = abs( a.rgbBlue - b.rgbBlue );

	return ( dr * dr + dg * dg + db * db );
}


BYTE GetNearestPalIndex( RGBQUAD & c, int trleflag )
{
	BYTE closestIndex;
	int  closestDiff = 65535 * 3,
		 diff;
	int  j;

	if( trleflag )
		j = 17;
	else
		j = 0;
	for (int i = j; i < 256; i++)
	{
		diff = RGBDiff( mainPalette[i], c );
		if ( diff < closestDiff )
		{
			closestDiff = diff;
			closestIndex = i;
		}
	}

	return( closestIndex );
}


void BuildTransTable( BITMAPINFO_256 & bminfo, int trleflag )
{
	int i, j;

	if( trleflag )
		j = 17;
	else
		j = 0;

	trans_table[0] = 0;

	for( i = 0; i < j; i++ )
		trans_table[i] = i;

	for( i = j; i < 256; i++ )
		trans_table[i] = GetNearestPalIndex( bminfo.bmiColors[i], trleflag );
}


/*
	BITMAP FUNCTIONS
*/
//	Read a bitmap from a file stream
BYTE *ReadBitmap( FILE* fp, BITMAPINFO_256 *pbminfo, int expectedbitdepth )
{
	BITMAPINFOHEADER *pHeader = &pbminfo->bmiHeader;

	// Get the current file position
	DWORD dwFileStart = ftell( fp );

 	BITMAPFILEHEADER bmfile;
	if (fread( &bmfile, sizeof(bmfile), 1, fp ) != 1)
	{
		printf ( "Unable to read bitmap file.\n" );
		return NULL;
	}

	if (fread( pHeader, sizeof(BITMAPINFOHEADER), 1, fp ) != 1)
	{
		printf ( "Unable to read bitmap file.\n" );
		return NULL;
	}

	if( pHeader->biBitCount != expectedbitdepth )
	{
		printf( "Bitmap was not of the correct bit depth!  (%d bit instead of %d bit).\n",
			pHeader->biBitCount, expectedbitdepth );
		return NULL;
	}

	if (pHeader->biClrUsed == 0)
		pHeader->biClrUsed = 1 << pHeader->biBitCount;

	UINT iColorTableSize = pHeader->biClrUsed * sizeof(RGBQUAD);

	// Now read the color table in
	fread( pbminfo->bmiColors, iColorTableSize, 1, fp );

	// Seek to the bits
	fseek( fp, dwFileStart + bmfile.bfOffBits, SEEK_SET );

	DWORD bmsize = pHeader->biSizeImage;
	if ( bmsize == 0 )	
	{
		if ( pHeader->biBitCount == 8 )
			bmsize = ((pHeader->biWidth + 3) & ~3) * pHeader->biHeight * (pHeader->biBitCount / 8);
		else	
//			bmsize = (((pHeader->biWidth + 7)/8) & ~3) * pHeader->biHeight;
			bmsize = ((pHeader->biWidth / 32 + 1) * 4) * pHeader->biHeight;
	}
	pHeader->biSizeImage = bmsize;

	// create a memory area for this bitmap
	BYTE *pBits = (BYTE *)malloc(bmsize);
	if (pBits == NULL)	
	{
	    printf( "malloc failed in ReadBitmap()\n" );
		return NULL;
	}

	// Read the bits.
	fread( pBits, bmsize, 1, fp );

	return pBits;
}	// ReadBitmap


//	Open a bitmap file & read it in using ReadBitmap
BYTE *GetBitmap( char *szName, BITMAPINFO_256 *pbminfo, int expectedbitdepth )	
{
	FILE *pfile;
	BYTE *pBits;

	if ((pfile = fopen( szName, "rb" )) != NULL)	
	{
		pBits = ReadBitmap(pfile, pbminfo, expectedbitdepth );
		fclose(pfile);
		return pBits;
	}
	else
		return NULL;
}	// GetBitmap


DWORD BitsToRLE256( BYTE *bits, BYTE ** rle, int Width, int Height, int Pitch, int & rle_type )
{
	BYTE  buf[200000];
	BYTE  *dp;
	BYTE  *sp, *spEnd;
	DWORD table[1024];
	WORD  wtable[1024];
	BYTE  xpc;
	int   i, j, count;
	DWORD sz;
	int   table_size, table_length;

	dp = buf;
	sp = bits;

	xpc = *((BYTE *)bits + ( (Height-1) * Pitch ));

	for( j = Height-1; j >= 0; j-- )
	{
		table[Height-j-1] = dp - buf;
		sp = (BYTE *)bits + ( j * Pitch );
		spEnd = sp + Width;
		while ( TRUE )
		{
			count = 0;
			while ( sp != spEnd && *sp == xpc && count < 255 )
			{
				sp++;
				count++;
			}
			*dp++ = count;

			count = 0;
			while ( sp != spEnd && *sp != xpc && count < 255 )
			{
				sp++;
				count++;
			}
			*dp++ = count;
			if ( count > 0 )
			{
				sp = sp - count;
				for ( int c = 0; c < count; c++ )
					*dp++ = trans_table[ *sp++ ];
			}

			if (sp == spEnd)
				break;
		}
	}

	rle_type = ( dp-buf >= 60000 ? 1 : 0 );
	table_size = rle_type ? sizeof(DWORD) : sizeof(WORD);
	table_length = sizeof(WORD) * 2 + Height * table_size;

	for( i = 0; i < Height; i++ )
		table[i] += table_length;

	if( !rle_type )
		for( i = 0; i < Height; i++ )
			wtable[i] = (WORD)table[i];

	sz = dp - buf + (table_size * Height) + (sizeof(WORD) * 2);

	*rle = (BYTE *)malloc(sz);
	if ( *rle == NULL ) 
	{
		printf( "Error allocating memory for RLE buffer.\n" );
		return 0;
	}

	sp = *rle;
	*((WORD *)sp) = Width;
	sp += sizeof(WORD);
	*((WORD *)sp) = Height;
	sp += sizeof(WORD);
	if( rle_type )
		CopyMemory( sp, table, table_size * Height );
	else
		CopyMemory( sp, wtable, table_size * Height );
	sp += table_size * Height;
	CopyMemory( sp, buf, (dp-buf) );

	return sz;
}


/*
	HELP / INVALID COMMAND LINE
*/
void exit_err( void )
{
	printf( "\n" );
	printf( "SYNTAX: compobj.exe terrainpath\n\n" );
	printf( "DESCRIPTION:  Compiles all of the objects in the terrain directory into a data file.\n" );
	printf( "     Requires there to be a final_pal.bmp palette file and also an Objects sub-directory\n" );
	printf( "     in the specified terrain path.\n" );
	exit( -1 );
}


int get_pal( FILE * dfp )
{
	BITMAPINFO_256	bminfo;
	BYTE			*pBits;
	char			palfile[256];

	sprintf( palfile, "%s\\final_pal.bmp", TERRAIN_PATH );
	pBits = GetBitmap( palfile, &bminfo, 8 );
	if( !pBits )
	{
		printf( "Unable to open palette file <%s>\n", palfile );
		return 0;
	}
	CopyMemory( mainPalette, bminfo.bmiColors, sizeof(RGBQUAD) * 256 );
	fwrite( mainPalette, sizeof(RGBQUAD), 256, dfp );	
	return 1;
}


BOOL appendFile( FILE * dfp, FILE * sfp )
{
	long err, size, bufsize;
	BYTE buffer[4096];

	err = fseek( sfp, 0, SEEK_END );
	if ( err < 0 )
	{
		printf( "\nERROR - Error moving cursor to end of file.\n" );
		return FALSE;
	}
	size = ftell( sfp );
	if ( size < 0 )
	{
		printf( "\nERROR - Error determining file size.\n" );
		return FALSE;
	}
	fseek( sfp, 0, SEEK_SET );
	fseek( dfp, 0, SEEK_END );

	while( size > 0 )
	{
		bufsize = ( size < 4096 ? size : 4096 );
		if( fread( buffer, bufsize, 1, sfp ) != 1 )
		{
			printf( "\nERROR - Reading data from temporary file.\n" );
			return FALSE;
		}
		fwrite( buffer, 1, bufsize, dfp );
		size -= bufsize;
	}

	return TRUE;
}


#define NUM_CATEGORIES 26


char *obj_category_dirs[NUM_CATEGORIES] = 
{	
	"Rock",			//	0
	"Bush",
	"Tree",
	"BigTree",
	"FallenTree",
	"Fence",		//	5
	"Wall",
	"Bridge",
	"FootBridge",
	"Explosives",
	"GunTurret",	//	10
	"AAGun",
	"Base",
	"Auxbase",
	"AirStrip",
	"HeliPad",		//	15
	"PrisonCamp",
	"Building",
	"PillBox",
	"PowerPlant",
	"Gate",			//	20
	"WallGate",
	"RadarBuilding",
	"Miscellaneous",
	"Overpass",
	"Sitems"		//	25
};


inline int AiObjectKey( int category, int number, int damagelevel )
{
	return( damagelevel + (number << 5) + (category << 15) );
}


BYTE *LoadShadow( char *filename, int &shadowsize, int width, int height )
{
	BITMAPINFO_256	bminfo;
	FILE			*pFile;
	BITMAPINFOHEADER *pHeader = &(bminfo.bmiHeader);
	BYTE			*pShadow;
	BYTE			*tempBuf;
	BYTE			*dp;
	int				sPitch;

	shadowsize = 0;
	if( ( pFile = fopen( filename, "rb" )) == NULL )	
		return NULL;

	DWORD dwFileStart = ftell( pFile );
 	BITMAPFILEHEADER bmfile;

	fread( &bmfile, sizeof(bmfile), 1, pFile );
	fread( pHeader, sizeof(BITMAPINFOHEADER), 1, pFile );
	if (pHeader->biBitCount != 1 )
	{
		fclose( pFile );
		printf( "ERROR: <%s> is not 1-bit.\n", filename );
		return NULL;
	}

	UINT iColorTableSize = pHeader->biClrUsed * sizeof(RGBQUAD);
	fread( &(bminfo.bmiColors), iColorTableSize, 1, pFile );	
	fseek( pFile, dwFileStart + bmfile.bfOffBits, SEEK_SET );

	DWORD bmsize = pHeader->biSizeImage;

	if( bmsize <= 0 )
	{
		fclose( pFile );
		printf( "ERROR: Invalid file size in <%s>.\n", filename );
		return NULL;
	}

	pShadow = (BYTE *)malloc(bmsize);
	if( pShadow == NULL )	
	{
		printf( "ERROR: Malloc failed in LoadShadow()\n" );
		fclose( pFile );
		return NULL;
	}

	fread( pShadow, bmsize, 1, pFile );
	fclose( pFile );

	if( width > 0 )
	{
		if( (bminfo.bmiHeader.biWidth != width) ||
			(bminfo.bmiHeader.biHeight != height) )
		{
			printf( "ERROR: Shadow <%s> has an illegal size.\n", filename );
			free( pShadow );
			shadowsize = 0;
			return NULL;
		}
	}


	sPitch = bmsize / pHeader->biHeight;
	tempBuf = (BYTE *)malloc( pHeader->biHeight * 2 * 40 );
	if( tempBuf == NULL )
	{
		free( pShadow );
		pShadow = NULL;
		fclose( pFile );
		printf( "ERROR: Malloc failed in LoadShadow()\n" );
		return NULL;
	}

	*(WORD *)tempBuf = (WORD)(pHeader->biWidth);
	*(WORD *)(tempBuf + 2) = (WORD)(pHeader->biHeight);
	dp = tempBuf + 4 + pHeader->biHeight * 2;
	for( int j = 0; j < pHeader->biHeight; j++ )
	{
		BYTE count;
		int i = 0;

		*(WORD *)( tempBuf + 4 + j * sizeof(WORD) ) = dp-tempBuf;
		while( TRUE )
		{
			count = 0;
			while( (i < pHeader->biWidth) && (count < 255) && 
				(!isBitSet( pShadow, i, j, pHeader->biHeight, sPitch )) )
			{
				i++;
				count++;
			}
			*dp++ = count;

			count = 0;
			while( (i < pHeader->biWidth) && (count < 255) && 
				(isBitSet( pShadow, i, j, pHeader->biHeight, sPitch )) )
			{
				i++;
				count++;
			}
			*dp++ = count;

			if (i >= pHeader->biWidth-1 )
				break;
		}
	}
	free( pShadow );
	bmsize = dp - tempBuf;
	pShadow = (BYTE *)malloc( bmsize );
	if( pShadow == NULL )
	{
		free( tempBuf );
		fclose( pFile );
		printf( "ERROR: Malloc failed in LoadShadow()\n" );
		return NULL;
	}
	memcpy( pShadow, tempBuf, bmsize );
	shadowsize = bmsize;
	free( tempBuf );

	return pShadow;
}


BOOL TranslateMask( BYTE* pDest,			//	First byte in dest data.
					const BYTE* pBMStart,	//	First byte in source data.
					int size,				//	total size of mask
					int	height )			//	Number of lines in source image.
{
	const BYTE*	pSrc;
	LONG		pitch = size / height;

	pSrc = pBMStart + (height - 1) * pitch;	// beginning of last line of source

	for( int y = 0; y < height; y++ )	
	{
		memcpy(pDest, pSrc, pitch);
		pDest += pitch;
		pSrc -= pitch;
	}
	return TRUE;
}


//	Load a mask (bitmap) given the name of it, return ptr to mask
BYTE *LoadMask( char *filename, int &masksize, int width, int height )
{
	BYTE	*pBits = NULL;
	BYTE	*pNewBits = NULL;
	BITMAPINFO_256	bminfo;

	masksize = 0;

	pBits = GetBitmap(filename, &bminfo, 1);
	if( !pBits )
	{
		printf( "ERROR: Unable to read mask file <%s>\n", filename );
		return NULL;
	}
	masksize = bminfo.bmiHeader.biSizeImage;
	if( !masksize )
	{
		printf( "ERROR: Mask <%s> has a listed size of 0.\n", filename );
		free( pBits );
		return NULL;
	}
	if( (bminfo.bmiHeader.biWidth != width) ||
		(bminfo.bmiHeader.biHeight != height) )
	{
		printf( "ERROR: Mask <%s> has an illegal size.\n", filename );
		free( pBits );
		masksize = 0;
		return NULL;
	}

	pNewBits = (BYTE *)malloc(masksize);
	TranslateMask( pNewBits, pBits, masksize, bminfo.bmiHeader.biHeight );
	free( pBits );

	return( pNewBits );
}	// LoadMask


//  Load a Rect from a file
BOOL LoadRect( char *filename, RECT *pRect )
{
	FILE *pFile;

	ZeroMemory( pRect, sizeof(RECT) );
	if ( ( pFile = fopen( filename, "rb" ) ) != NULL )	
	{
		fread( pRect, sizeof(RECT), 1, pFile );
		fclose( pFile );
		return TRUE;
	}
	else
		return FALSE;
}	// LoadRect


void process_file( char *filename, _finddata_t &fdata, int category )
{
	int  key, number, damagelevel;
	int  len;
	char cnum[4], cdam[4];
	char buf[256];
	WIN32_FIND_DATA FindFileData;
	HANDLE hSearch;

	// process the filename to get number & damagelevel
	if( filename[4] != '_' )
	{
		printf( "ERROR: Illegal object name <%s>\n", filename );
		return;
	}
	strncpy( cnum, filename + 5, 3 );
	cnum[3] = 0;
	number = atoi( cnum );

	len = strlen( filename );
	if( len > 13 )
	{
		if( filename[8] != '_' )
		{
			printf( "ERROR: Illegal object name <%s>\n", filename );
			return;
		}
		strncpy( cdam, filename + 9, 2 );
		if( cdam[1] == '.' )
			cdam[1] = 0;
		else
			cdam[2] = 0;
		damagelevel = atoi(cdam) + 1;
	}
	else
		damagelevel = 0;

	// get the bitmap
	BITMAPINFO_256	bminfo;
	BYTE			*pBits;
	int				pitch, sz;
	BYTE			*rle;
	int				rle_type;
	
	pBits = GetBitmap( filename, &bminfo, 8 );
	if( pBits == NULL )
	{
		printf( "ERROR: Error reading bitmap file <%s>\n", filename );
		return;
	}

	// translate the palette to the master palette
	BuildTransTable( bminfo, 0 );

	// process the bitmap
	pitch = ( (bminfo.bmiHeader.biWidth  + 3) & ~3);
	sz = BitsToRLE256( pBits, &rle, bminfo.bmiHeader.biWidth, bminfo.bmiHeader.biHeight,
					    pitch, rle_type );
	if( sz <= 0 )
	{
		printf( "ERROR: Unable to convert bitmap <%s> to rle\n", filename );
		free( pBits );
		return;
	}

	int		flags;
	SPOINT	hotspot, linkspot;

	flags = 0;
	if( rle_type )
		flags |= SP_DRLE;
	else
		flags |= SP_WRLE;
	hotspot.x = (SHORT)bminfo.bmiHeader.biXPelsPerMeter & 0xFFFF;
	hotspot.y = (SHORT)bminfo.bmiHeader.biYPelsPerMeter & 0xFFFF;
	linkspot.x = (SHORT)(bminfo.bmiHeader.biXPelsPerMeter >> 16 );
	linkspot.y = (SHORT)(bminfo.bmiHeader.biYPelsPerMeter >> 16 );

	if( (hotspot.x > MAXHOTSPOTOFFSET) || (hotspot.x < -MAXHOTSPOTOFFSET) )	
		hotspot.x = 0;
	if( (hotspot.y > MAXHOTSPOTOFFSET) || (hotspot.y < -MAXHOTSPOTOFFSET) )	
		hotspot.y = 0;
	if( (linkspot.x > MAXHOTSPOTOFFSET) || (linkspot.x < -MAXHOTSPOTOFFSET) )	
		linkspot.x = 0;
	if( (linkspot.y > MAXHOTSPOTOFFSET) || (linkspot.y < -MAXHOTSPOTOFFSET) )	
		linkspot.y = 0;

	if( hotspot.x == 0 && hotspot.y == 0 )
		printf( "   WARNING: Bitmap <%s> has a possibly illegal hotspot of (0,0)\n", filename );

	// compute the key
	key = AiObjectKey( category, number, damagelevel );
	ObjectTable[numobjects].key = key;

	// compute the offset from the start of the data file
	ObjectTable[numobjects].offset = ftell( dfp );

	// write the key
	fwrite( &key, sizeof(int), 1, dfp );

	strncpy( buf, filename, len-4 );
	buf[len-4] = 0;

	// look for a shadow file
	char shadowname[256];
	int	 shadowsize = 0;
	BYTE *pShadow = NULL;

	strcpy( shadowname, buf );
	strcat( shadowname, ".sha" );
	hSearch = FindFirstFile( shadowname, &FindFileData );
	if( hSearch != INVALID_HANDLE_VALUE )	
	{
		pShadow = LoadShadow( shadowname, shadowsize, bminfo.bmiHeader.biWidth, bminfo.bmiHeader.biHeight );
		FindClose( hSearch );
	}

	// look for a mask file
	char maskname[256];
	int  masksize = 0;
	BYTE *pMask = NULL;

	sprintf( maskname, "masks\\%s.msk", buf );
	hSearch = FindFirstFile( maskname, &FindFileData );
	if( hSearch != INVALID_HANDLE_VALUE )	
	{
		if( pMask = LoadMask( maskname, masksize, bminfo.bmiHeader.biWidth, bminfo.bmiHeader.biHeight ) )
			flags |= SP_PRIMEMASK;
		FindClose( hSearch );
	}

	// look for a rect file
	char rectname[256];
	int	 hasrect = 0;
	RECT rect = {0, 0, 0, 0};

	sprintf( rectname, "rects\\%s.rec", buf );
	hSearch = FindFirstFile( rectname, &FindFileData );
	if( hSearch != INVALID_HANDLE_VALUE )	
	{
		if( hasrect = LoadRect( rectname, &rect ) )
			flags |= SP_MASKRECT;
		FindClose( hSearch );
	}

	// write sprite information
	fwrite( &(bminfo.bmiHeader.biWidth), sizeof(long), 1, dfp );
	fwrite( &(bminfo.bmiHeader.biHeight), sizeof(long), 1, dfp );
	fwrite( &flags, sizeof(long), 1, dfp );			// sprite flags
	fwrite( &hotspot, sizeof(SPOINT), 1, dfp );		// hotspot
	fwrite( &linkspot, sizeof(SPOINT), 1, dfp );	// linkspot

	fwrite( &sz, sizeof(int), 1, dfp );				// graphic rle data
	if( sz > 0 && rle )
	{
		fwrite( rle, sz, 1, dfp );
		free( rle );
		rle = NULL;
	}

	fwrite( &shadowsize, sizeof(int), 1, dfp );		// shadow data
	if( shadowsize > 0 && pShadow)
	{
		fwrite( pShadow, shadowsize, 1, dfp );
		free( pShadow );
		pShadow = NULL;
	}

	fwrite( &masksize, sizeof(int), 1, dfp );		// mask data
	if( masksize > 0 && pMask )
	{
		fwrite( pMask, masksize, 1, dfp );
		free( pMask );
		pMask = NULL;
	}

	fwrite( &rect, sizeof(RECT), 1, dfp );			// rect data

	// free objects
	free( pBits );

	// output trace info
	printf( "      %-15s  %2d  %3d  %2d %6d  %6d  %6d  %c\n", 
		filename, category, number, damagelevel, sz, shadowsize, masksize, hasrect ? 'Y' : 'N' );

	numobjects++;
}


void process_as_bmp( char *filename, _finddata_t &fdata, int category, int flags  )
{
	int  key, number, spriteindex;
	int  len;
	char cnum[4], cidx[4];
	char buf[256];
	WIN32_FIND_DATA FindFileData;
	HANDLE hSearch;

	// process the filename to get number & spriteindex
	if( filename[4] != '_' )
	{
		printf( "ERROR: Illegal object name <%s>\n", filename );
		return;
	}
	strncpy( cnum, filename + 5, 3 );
	cnum[3] = 0;
	number = atoi( cnum );
	len = strlen( filename );
	if( len > 13 )
	{
		if( filename[8] != '_' )
		{
			printf( "ERROR: Illegal object name <%s>\n", filename );
			return;
		}
		strncpy( cidx, filename + 9, 15-13 );
		if( cidx[1] == '.' )
			cidx[1] = 0;
		else
			cidx[2] = 0;
		spriteindex = atoi(cidx);
	}
	else
		spriteindex = 1;

	// get the bitmap
	BITMAPINFO_256	bminfo;
	BYTE			*pBits;
	BYTE			*pb;
	int				sz;
	
	pBits = GetBitmap( filename, &bminfo, 8 );
	if( pBits == NULL )
	{
		printf( "ERROR: Error reading bitmap file <%s>\n", filename );
		return;
	}

	// translate the palette to the master palette
	BuildTransTable( bminfo, 0 );

	// process the bitmap
	sz = bminfo.bmiHeader.biSizeImage;
	pb = pBits;
	for( int i = 0; i < sz; i++ )
	{
		*pb = trans_table[*pb];
		pb++;
	}

	SPOINT	hotspot, linkspot;

	hotspot.x = (SHORT)bminfo.bmiHeader.biXPelsPerMeter & 0xFFFF;
	hotspot.y = (SHORT)bminfo.bmiHeader.biYPelsPerMeter & 0xFFFF;
	linkspot.x = 0;
	linkspot.y = 0;

	if( (hotspot.x > MAXHOTSPOTOFFSET) || (hotspot.x < -MAXHOTSPOTOFFSET) )	
		hotspot.x = 0;
	if( (hotspot.y > MAXHOTSPOTOFFSET) || (hotspot.y < -MAXHOTSPOTOFFSET) )	
		hotspot.y = 0;

	if( hotspot.x == 0 && hotspot.y == 0 )
		printf( "   WARNING: Bitmap <%s> has a possibly illegal hotspot of (0,0)\n", filename );

	// compute the key
	key = AiObjectKey( category, number, spriteindex );
	ObjectTable[numobjects].key = key;

	// compute the offset from the start of the data file
	ObjectTable[numobjects].offset = ftell( dfp );

	// write the key
	fwrite( &key, sizeof(int), 1, dfp );

	strncpy( buf, filename, len-4 );
	buf[len-4] = 0;

	// look for a shadow file
	char shadowname[256];
	int	 shadowsize = 0;
	BYTE *pShadow = NULL;

	strcpy( shadowname, buf );
	strcat( shadowname, ".sha" );
	hSearch = FindFirstFile( shadowname, &FindFileData );
	if( hSearch != INVALID_HANDLE_VALUE )	
	{
		pShadow = LoadShadow( shadowname, shadowsize, bminfo.bmiHeader.biWidth, bminfo.bmiHeader.biHeight );
		FindClose( hSearch );
	}

	// write sprite information
	fwrite( &(bminfo.bmiHeader.biWidth), sizeof(long), 1, dfp );
	fwrite( &(bminfo.bmiHeader.biHeight), sizeof(long), 1, dfp );
	fwrite( &flags, sizeof(long), 1, dfp );			// sprite flags
	fwrite( &hotspot, sizeof(SPOINT), 1, dfp );		// hotspot
	fwrite( &linkspot, sizeof(SPOINT), 1, dfp );	// linkspot

	fwrite( &sz, sizeof(int), 1, dfp );				// graphic data
	if( sz > 0 && pBits )
	{
		fwrite( pBits, sz, 1, dfp );
	}

	fwrite( &shadowsize, sizeof(int), 1, dfp );		// shadow data
	if( shadowsize > 0 && pShadow)
	{
		fwrite( pShadow, shadowsize, 1, dfp );
		free( pShadow );
		pShadow = NULL;
	}

	int masksize = 0;
	RECT rect = {0, 0, 0, 0};

	fwrite( &masksize, sizeof(int), 1, dfp );
	fwrite( &rect, sizeof(RECT), 1, dfp );			// rect data

	// free object graphics
	free( pBits );

	printf( "      %4d: processed bitmap %s  (%3d %3d %2d : %d)\n", numobjects, fdata.name, category, number, spriteindex, key );

	numobjects++;
}


void process_as_rle( char *filename, _finddata_t &fdata, int category, int flags  )
{
	int  key, number, spriteindex;
	int  len;
	char cnum[4], cidx[4];
	char buf[256];

	// process the filename to get number & spriteindex
	if( filename[4] != '_' )
	{
		printf( "ERROR: Illegal object name <%s>\n", filename );
		return;
	}
	strncpy( cnum, filename + 5, 3 );
	cnum[3] = 0;
	number = atoi( cnum );
	len = strlen( filename );
	if( len > 13 )
	{
		if( filename[8] != '_' )
		{
			printf( "ERROR: Illegal object name <%s>\n", filename );
			return;
		}
		strncpy( cidx, filename + 9, 2 );
		if( cidx[1] == '.' )
			cidx[1] = 0;
		else
			cidx[2] = 0;
		spriteindex = atoi(cidx);
	}
	else
		spriteindex = 1;

	// get the bitmap
	BITMAPINFO_256	bminfo;
	BYTE			*pBits = NULL;
	BYTE			*pb = NULL;
	int				expectedbitdepth;
	int				trleflag;
	int				sz;
	int				pitch;
	BYTE			*rle = NULL;
	int				shadowsize;
	BYTE			*pShadow;
	int				rle_type;
	SPOINT			hotspot, linkspot;
	long			height, width;
	int				masksize;
	RECT			rect = {0, 0, 0, 0};

	if( strcmp( filename + strlen(filename) - 3, "sha") == 0 )
		expectedbitdepth = 1;
	else
		expectedbitdepth = 8;
	

	if( expectedbitdepth == 8 )
	{
		pBits = GetBitmap( filename, &bminfo, expectedbitdepth );
		if( pBits == NULL )
		{
			printf( "ERROR: Error reading bitmap file <%s>\n", filename );
			return;
		}

		trleflag = 0;
		if( flags & BM_TRLE )
			trleflag = 1;

		// translate the palette to the master palette
		BuildTransTable( bminfo, trleflag );

		// process the bitmap
		pitch = ( (bminfo.bmiHeader.biWidth  + 3) & ~3);
		sz = BitsToRLE256( pBits, &rle, bminfo.bmiHeader.biWidth, bminfo.bmiHeader.biHeight,
						    pitch, rle_type );
		if( sz <= 0 )
		{
			printf( "ERROR: Unable to convert bitmap <%s> to rle\n", filename );
			free( pBits );
			return;
		}

		if( trleflag )
		{
			if( rle_type )
			{
				printf( "ERROR: Bitmap <%s> is too large to be non-translated!\n", filename );
				free( pBits );
				return;
			}
			flags |= SP_TRLE;
		}
		else
		if( rle_type )
			flags |= SP_DRLE;
		else
			flags |= SP_WRLE;
		hotspot.x = (SHORT)bminfo.bmiHeader.biXPelsPerMeter & 0xFFFF;
		hotspot.y = (SHORT)bminfo.bmiHeader.biYPelsPerMeter & 0xFFFF;

		if( (hotspot.x > MAXHOTSPOTOFFSET) || (hotspot.x < -MAXHOTSPOTOFFSET) )	
			hotspot.x = 0;
		if( (hotspot.y > MAXHOTSPOTOFFSET) || (hotspot.y < -MAXHOTSPOTOFFSET) )	
			hotspot.y = 0;

		if( hotspot.x == 0 && hotspot.y == 0 )
			printf( "   WARNING: Bitmap <%s> has a possibly illegal hotspot of (0,0)\n", filename );

		height = bminfo.bmiHeader.biHeight;
		width = bminfo.bmiHeader.biWidth;
		if( height == 0 || width == 0 )
			printf( "WARNING: Bitmap <%s> has an illegal size of (%d x %d)\n", filename, width, height );

		shadowsize = 0;
		pShadow = NULL;
	}
	else
	{
		pShadow = LoadShadow( filename, shadowsize, 0, 0 );
		if( !pShadow )
		{
			printf( "ERROR: Reading shadowfile <%s>.\n", filename );
			free( pShadow );
			return;
		}
		width = *((WORD *)(pShadow));
		height = *((WORD *)(pShadow+2));;
		if( height == 0 || width == 0 )
			printf( "WARNING: Bitmap <%s> has an illegal size of (%d x %d)\n", filename, width, height );

		flags |= SP_SRLE;
		if( category == CAT_FOGTILES )
		{
			hotspot.x = 0;
			hotspot.y = 0;
		}
		else
		{
			hotspot.x = (short)width >> 1;
			hotspot.y = (short)height >> 1;
		}
		sz = 0;
		rle = NULL;
	}

	// for both bmp and sha files
	linkspot.x = 0;
	linkspot.y = 0;
	masksize = 0;

	// compute the key
	key = AiObjectKey( category, number, spriteindex );
	ObjectTable[numobjects].key = key;

	// compute the offset from the start of the data file
	ObjectTable[numobjects].offset = ftell( dfp );

	// write the key
	fwrite( &key, sizeof(int), 1, dfp );

	strncpy( buf, filename, len-4 );
	buf[len-4] = 0;

	// write sprite information
	fwrite( &width, sizeof(long), 1, dfp );
	fwrite( &height, sizeof(long), 1, dfp );
	fwrite( &flags, sizeof(long), 1, dfp );			// sprite flags
	fwrite( &hotspot, sizeof(SPOINT), 1, dfp );		// hotspot
	fwrite( &linkspot, sizeof(SPOINT), 1, dfp );	// linkspot

	fwrite( &sz, sizeof(int), 1, dfp );				// graphic rle data
	if( sz > 0 && rle )
	{
		fwrite( rle, sz, 1, dfp );
		free( rle );
		rle = NULL;
	}

	fwrite( &shadowsize, sizeof(int), 1, dfp );		// shadow data
	if( shadowsize > 0 && pShadow)
	{
		fwrite( pShadow, shadowsize, 1, dfp );
		free( pShadow );
		pShadow = NULL;
	}

	fwrite( &masksize, sizeof(int), 1, dfp );		// mask data
	fwrite( &rect, sizeof(RECT), 1, dfp );			// rect data

	// free objects
	free( pBits );

	printf( "      %4d: processed bitmap %s  (%3d %3d %2d : %d)\n", numobjects, fdata.name, category, number, spriteindex, key );

	numobjects++;
}


void process_categories( void )
{
	_finddata_t fdata;
	long		fsh;
	char		path[256];
	char		cd[256];

	for( int cat = 0; cat < NUM_CATEGORIES; cat++ )
	{
		_getcwd( cd, 128 );
		sprintf( path, "%s\\Objects\\%s", TERRAIN_PATH, obj_category_dirs[cat] );
		if( _chdir( path ) != 0 )
		{
			_chdir(cd);
			continue;
		}
		printf( "      Processing... %s\n", path );

		fsh = _findfirst( "*.*", &fdata );
		if( fsh != -1 )
		{
			do
			{
				int len;

				if( strcmp( fdata.name, "." ) == 0 )
					continue;
				if( strcmp( fdata.name, ".." ) == 0 )
					continue;
				if( fdata.attrib & _A_SUBDIR )
					continue;
				len = strlen( fdata.name );
				if( len < 12 || len > 15)
					continue;
				strlwr( fdata.name );
				if( strcmp( fdata.name + len - 3, "bmp") != 0 )
					continue;
				else
				{
					process_file( fdata.name, fdata, cat );
				}
			} while( _findnext( fsh, &fdata ) == 0 );
			_findclose( fsh );
		}

		_chdir( cd );
	}
};


void process_cursors( void )
{
	_finddata_t fdata;
	long		fsh;
	char		path[256];
	char		cd[256];
	char		*cursorsubpath[] =
		{ "", "\\green", "\\tan", "\\blue", "\\grey" };

	for( int i = 0; i < 5; i++ )
	{
		_getcwd( cd, 128 );
		sprintf( path, "Cursors%s", cursorsubpath[i] );
		if( _chdir( path ) != 0 )
		{
			_chdir( cd );
			printf( "Unable to locate directory %s.  NOTE: You must be in the runtime folder!\n", path );
			continue;
		}
		printf( "      Processing... %s\n", path );

		fsh = _findfirst( "*.*", &fdata );
		if( fsh != -1 )
		{
			do
			{
				int len;

				if( strcmp( fdata.name, "." ) == 0 )
					continue;
				if( strcmp( fdata.name, ".." ) == 0 )
					continue;
				if( fdata.attrib & _A_SUBDIR )
					continue;
				len = strlen( fdata.name );
				if( len < 12 || len > 15)
					continue;
				strlwr( fdata.name );
				if( strcmp( fdata.name + len - 3, "bmp") != 0 )
					continue;
				else
				{
					process_as_bmp( fdata.name, fdata, 200 + i, 0 );
				}
			} while( _findnext( fsh, &fdata ) == 0 );
			_findclose( fsh );
		}
		_chdir( cd );
	}
}


void process_dashboard( void )
{
	_finddata_t fdata;
	long		fsh;
	char		path[256];
	char		cd[256];
	char		*dashsubpath[] =
		{ "", "\\tan", "\\blue", "\\grey" };

	for( int i = 0; i < 4; i++ )
	{
		_getcwd( cd, 128 );
		sprintf( path, "Dashboard%s", dashsubpath[i] );
		if( _chdir( path ) != 0 )
		{
			_chdir( cd );
			printf( "Unable to locate directory %s.  NOTE: You must be in the runtime folder!\n", path );
			continue;
		}
		printf( "      Processing... %s\n", path );

		fsh = _findfirst( "*.*", &fdata );
		if( fsh != -1 )
		{
			do
			{
				int len;

				if( strcmp( fdata.name, "." ) == 0 )
					continue;
				if( strcmp( fdata.name, ".." ) == 0 )
					continue;
				if( fdata.attrib & _A_SUBDIR )
					continue;
				len = strlen( fdata.name );
				if( len < 12 || len > 15)
					continue;
				strlwr( fdata.name );
				if( strcmp( fdata.name + len - 3, "bmp") != 0 )
					continue;
				else
				{
					process_as_bmp( fdata.name, fdata, 300 + i, 0 );
				}
			} while( _findnext( fsh, &fdata ) == 0 );
			_findclose( fsh );
		}
		_chdir( cd );
	}
}


void process_wobjects( void )
{
	_finddata_t fdata;
	long		fsh;
	char		path[256];
	char		cd[256];
	int			cat;

	_getcwd( cd, 128 );

	sprintf( path, "BodyParts" );
	if( _chdir( path ) != 0 )
	{
		_chdir( cd );
		printf( "Unable to locate directory %s.  NOTE: You must be in the runtime folder!\n", path );
		goto getflash;
	}
	printf( "      Processing... %s\n", path );

	fsh = _findfirst( "*.*", &fdata );
	if( fsh != -1 )
	{
		do
		{
			int len;

			if( strcmp( fdata.name, "." ) == 0 )
				continue;
			if( strcmp( fdata.name, ".." ) == 0 )
				continue;
			if( fdata.attrib & _A_SUBDIR )
				continue;
			len = strlen( fdata.name );
			if( len < 12 || len > 15)
				continue;
			strlwr( fdata.name );
			if( strcmp( fdata.name + len - 3, "bmp") != 0 )
				continue;
			else
			{
				process_as_rle( fdata.name, fdata, CAT_BODYPARTS, SP_TRLE );
			}
		} while( _findnext( fsh, &fdata ) == 0 );
		_findclose( fsh );
	}
	_chdir( cd );

getflash:
	sprintf( path, "Flash" );
	if( _chdir( path ) != 0 )
	{
		_chdir( cd );
		printf( "Unable to locate directory %s.  NOTE: You must be in the runtime folder!\n", path );
		goto getmisc;
	}
	printf( "      Processing... %s\n", path );

	fsh = _findfirst( "*.*", &fdata );
	if( fsh != -1 )
	{
		do
		{
			int len;

			if( strcmp( fdata.name, "." ) == 0 )
				continue;
			if( strcmp( fdata.name, ".." ) == 0 )
				continue;
			if( fdata.attrib & _A_SUBDIR )
				continue;
			len = strlen( fdata.name );
			if( len < 12 || len > 15)
				continue;
			strlwr( fdata.name );
			if( strcmp( fdata.name + len - 3, "bmp") != 0 )
				if( strcmp( fdata.name + len - 3, "sha") != 0 )
					continue;

			if( strncmp( fdata.name, "flam", 4 ) == 0 )
				cat = CAT_FLAMEBURST;
			else
			if( strncmp( fdata.name, "fogt", 4 ) == 0 )
				cat = CAT_FOGTILES;
			else
			if( strncmp( fdata.name, "frag", 4 ) == 0 )
				cat = CAT_FRAGCOUNTER;
			else
			if( strncmp( fdata.name, "flag", 4 ) == 0 )
				cat = CAT_FLAG;
			else
			if( strncmp( fdata.name, "htfl", 4 ) == 0 )
				cat = CAT_MUZZLEFLASH;
			else
			if( strncmp( fdata.name, "jtfl", 4 ) == 0 )
				cat = CAT_MUZZLEFLASH;
			else
			if( strncmp( fdata.name, "muzz", 4 ) == 0 )
				cat = CAT_MUZZLEFLASH;
			else
			if( strncmp( fdata.name, "tmfl", 4 ) == 0 )
				cat = CAT_MUZZLEFLASH;
			else
			if( strncmp( fdata.name, "scar", 4 ) == 0 )
				cat = CAT_SCAR;
			else
			if( strncmp( fdata.name, "smok", 4 ) == 0 )
				cat = CAT_SMOKE;
			else
			if( strncmp( fdata.name, "strp", 4 ) == 0 )
				cat = CAT_STRIPES;
			else
				continue;

			if( cat == CAT_FRAGCOUNTER || CAT_FLAG )
				process_as_bmp( fdata.name, fdata, cat, 0 );
			else
				process_as_rle( fdata.name, fdata, cat, 0 );
		} while( _findnext( fsh, &fdata ) == 0 );
		_findclose( fsh );
	}
	_chdir( cd );

getmisc:
	sprintf( path, "%s\\Misc", TERRAIN_PATH );
	if( _chdir( path ) != 0 )
	{
		_chdir( cd );
		printf( "Unable to locate directory %s.  NOTE: You must be in the runtime folder!\n", path );
		return;
	}
	printf( "      Processing... %s\n", path );

	fsh = _findfirst( "*.*", &fdata );
	if( fsh != -1 )
	{
		do
		{
			int len;

			if( strcmp( fdata.name, "." ) == 0 )
				continue;
			if( strcmp( fdata.name, ".." ) == 0 )
				continue;
			if( fdata.attrib & _A_SUBDIR )
				continue;
			len = strlen( fdata.name );
			if( len < 12 || len > 15)
				continue;
			strlwr( fdata.name );
			if( strcmp( fdata.name + len - 3, "bmp") != 0 )
				if( strcmp( fdata.name + len - 3, "sha") != 0 )
					continue;

			if( strncmp( fdata.name, "airs", 4 ) == 0 )
				cat = CAT_AIRSUPPORT;
			else
			if( strncmp( fdata.name, "para", 4 ) == 0 )
				cat = CAT_PARACHUTE;
			else
			if( strncmp( fdata.name, "fire", 4 ) == 0 )
				cat = CAT_FIRE;
			else
				continue;

			process_as_rle( fdata.name, fdata, cat, 0 );
		} while( _findnext( fsh, &fdata ) == 0 );
		_findclose( fsh );
	}
	_chdir( cd );
}


void SwapObjectEntries( ObjectTableEntry *objPtrA, ObjectTableEntry *objPtrB )
{
	ObjectTableEntry temp;

	CopyMemory( &temp, objPtrA, sizeof(ObjectTableEntry) );
	CopyMemory( objPtrA, objPtrB, sizeof(ObjectTableEntry) );
	CopyMemory( objPtrB, &temp, sizeof(ObjectTableEntry) );
}


void SortObjectTable( void )
{
	int hasmismatch;
	int i, keyA, keyB;
	ObjectTableEntry *objPtrA, *objPtrB;

	if( numobjects < 1 )
		return;

	do
	{
		objPtrA = &(ObjectTable[0]);
		keyA = objPtrA->key;
		hasmismatch = FALSE;
		for( i = 0; i < numobjects-1; i++ )
		{
			objPtrB = &(ObjectTable[i+1]);
			keyB = objPtrB->key;
			if( keyA > keyB )
			{
				SwapObjectEntries( objPtrA, objPtrB );
				hasmismatch = TRUE;
			}	
			else if( keyA < keyB )
			{
				objPtrA = objPtrB;
				keyA = keyB;
			}
			else
			{
				printf( "ERROR: identical keys %d %d %d\n",
					keyA >> 15, (keyA >> 5) & 1023, keyA & 31 );
				exit( 0 );
			}
		}
	}	while( hasmismatch );
}


/*
	MAIN
*/
void main( int argc, char *argv[ ], char *envp[ ] )
{
	char HEADER_FILENAME[256];
	int  i, headersize;

	if( argc != 2 )
		exit_err();

	strcpy( TERRAIN_PATH, argv[1] );

	sprintf( HEADER_FILENAME, "%s\\objects.dat", TERRAIN_PATH );

	hfp = fopen( HEADER_FILENAME, "wb" );
	if( hfp == NULL )
	{
		printf( "Unable to create data file 'objects.dat'\n" );
		exit( -1 );
	}
	dfp = tmpfile();
	if( dfp == NULL )
	{
		printf( "Unable to create temporary file\n" );
		fclose( hfp );
		exit( - 1);
	}

	// write the file id
	fwrite( &FILEID, sizeof(int), 1, hfp );

	// read & write the palette
	if( !get_pal(hfp) )
		goto done;

	// process the objects directory
	process_categories();

	// process the cursors
	process_cursors();

	// process the dashboard
	process_dashboard();

	// process flash, bodyparts, misc
	process_wobjects();

	// write the number of objects
	fwrite( &numobjects, sizeof(int), 1, hfp );

	// compute the headersize
	headersize = sizeof(int) +						// fileid
				 sizeof(RGBQUAD) * 256 +			// palette
				 sizeof(int) +						// # of objects
				 sizeof(ObjectTableEntry) * numobjects;		// object directory

	// sort the object table by key order
	SortObjectTable();

	for( i = 0; i < numobjects; i++ )
	{
		ObjectTable[i].offset += headersize;
		fwrite( &(ObjectTable[i]), sizeof(ObjectTableEntry), 1, hfp );
	}

	// create the final file by concatenating the header and data files
	appendFile( hfp, dfp );

done:
	if( hfp )
		fclose( hfp );
	if( dfp )
		fclose( dfp );

	getch();
}
