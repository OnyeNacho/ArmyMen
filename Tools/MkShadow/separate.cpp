/*
	Shadow separation program
	Peter Hu
	970818

	Attempts to separate shadows from a bitmap file.
	Shadows are single pixels of a particular color separated by a non-transparent pixel.
	Writes out the bitmap file without the shadow and a separate shadow file (*.sha)
	which is a 1 bpp bitmap file with the shadow as a solid line.
	Assumes that the upper left pixel of each bitmap is the transparent color.

  SYNTAX:
  separate.exe [-orsu] [-p#] path

  -o:	overwrite existing files
  -r:	recurse directories
  -s:	separates out shadows
  -u:	unlock locked files & overwrite (always enables -o)
  -p#:	# is palette index of shadow color
  path:	directory name to process
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
	TYPES
*/
typedef struct BITMAPINFO_256
{
  BITMAPINFOHEADER  bmiHeader;
  RGBQUAD           bmiColors[256];
} BITMAPINFO_256;


/*
	GLOBALS
*/
BOOL OVERWRITE_EXIST = FALSE;
BOOL OVERWRITE_LOCK = FALSE;
BOOL SEPARATE_SHADOWS = FALSE;
BOOL RECURSE_DIRECTORIES = FALSE;
BOOL COMPUTE_SHADOW_INDEX = TRUE;
BOOL DITHERED_SHADOWS = FALSE;
BYTE SHADOW_INDEX =	0;
char SEARCH_DIRECTORY[128] = {""};
int	 NUM_FILES_PROCESSED = 0;


/*
	BITMAP FUNCTIONS
*/
//	Read a bitmap from a file stream
BYTE *ReadBitmap( FILE* fp, BITMAPINFO_256 *pbminfo )
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
BYTE *GetBitmap( char *szName, BITMAPINFO_256 *pbminfo )	
{
	FILE *pfile;
	BYTE *pBits;

	if ((pfile = fopen( szName, "rb" )) != NULL)	
	{
		pBits = ReadBitmap(pfile, pbminfo);
		fclose(pfile);
		return pBits;
	}
	else
		return NULL;
}	// GetBitmap


//  Write a bitmap file to disk
BOOL SaveBitmap( char *filename, BITMAPINFO_256 &bminfo, BYTE *pBits )
{
	BITMAPFILEHEADER	bmfile;
	FILE				* fp;
	int					bminfosize;

	bminfo.bmiHeader.biClrUsed = (bminfo.bmiHeader.biBitCount == 8 ? 256 : 2); 
	bminfosize = sizeof(BITMAPINFOHEADER) + bminfo.bmiHeader.biClrUsed * 4;
	
	bmfile.bfType = 0x4D42;					// 'BM'
	bmfile.bfSize = sizeof(BITMAPFILEHEADER) + bminfosize + bminfo.bmiHeader.biSizeImage;
	bmfile.bfOffBits = sizeof(BITMAPFILEHEADER) + bminfosize;

	bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bminfo.bmiHeader.biPlanes = 1; 
	bminfo.bmiHeader.biCompression = BI_RGB; 
	bminfo.bmiHeader.biClrImportant = bminfo.bmiHeader.biClrUsed;

	if( bminfo.bmiHeader.biClrUsed == 2 )
	{
	    bminfo.bmiColors[0].rgbRed = 0;
		bminfo.bmiColors[0].rgbGreen = 0;
		bminfo.bmiColors[0].rgbBlue = 0;
		bminfo.bmiColors[0].rgbReserved = 0;
	    bminfo.bmiColors[1].rgbRed = 255;
		bminfo.bmiColors[1].rgbGreen = 255;
		bminfo.bmiColors[1].rgbBlue = 255;
		bminfo.bmiColors[1].rgbReserved = 255;
	}

	if ( ( fp = fopen( filename, "wb" ) ) != NULL )
	{
		size_t actual;

		// Write the BMP header and info structures
		actual = fwrite( &bmfile, 1, sizeof(BITMAPFILEHEADER), fp );
		actual = fwrite( &bminfo, 1, bminfosize, fp );

		//write the BMP data
		actual = fwrite( pBits, bminfo.bmiHeader.biSizeImage, 1, fp );

		fclose( fp );
	}
	else
	{
		printf( "*** ERROR CREATING FILE %s ***\n", filename );
		return FALSE;
	}

	return TRUE;
}


/*
	PROCESS BITS for Shadow
*/
BYTE get_shadow_index( BYTE *src, int height, int width, int srcpitch )
{
	long hist[256];
	int  i, j;
	BYTE shc, xpc, max;
	BYTE *sp;

	xpc = *src;
	memset( hist, 0, 256 * sizeof(long) );

	for( j = 0; j < height; j++ )
	{
		for( i = 0; i < width; i++ )
		{
			sp = src + j * srcpitch + i;
			shc = *sp;
			if( shc == xpc)
				continue;
			if( i != 0 )
				if( *(sp - 1) != xpc )
					continue;
			if( i != width - 1 )
				if( *(sp + 1) != xpc )
					continue;
			if( j != 0 )
				if( *(sp - srcpitch) != xpc )
					continue;
			if( j != height - 1 )
				if( *(sp + 1) != xpc )
					continue;
			hist[shc]++;
		}
	}

	max = 0;
	for( i = 1; i < 256; i++ )
		if( hist[i] > hist[max] )
			max = i;

	return (max);
}


BOOL separate_shadow( BYTE *src, BYTE *dest, int height, int width, 
					 int srcpitch, int destpitch )
{
	BYTE xpc;
	BYTE *sp, *dp;
	int	 bit;

	if( COMPUTE_SHADOW_INDEX )
		SHADOW_INDEX = get_shadow_index( src, height, width, srcpitch );
	xpc = *src;
	if( xpc == SHADOW_INDEX )
		return FALSE;

	for( int j= 0; j < height; j++ )
	{
		for( int i= 0; i < width; i++ )
		{
			sp = src + j * srcpitch + i;
			if ( *sp == SHADOW_INDEX )
			{
				if( !DITHERED_SHADOWS )
					goto isshadow;
				if( i > 1 )
				{
					if( *(sp - 1) == xpc )
						if( *(sp - 2) == SHADOW_INDEX )
							goto isshadow;
				}
				if( i < width - 2 ) 
				{
					if( *(sp + 1) == xpc )
						if( *(sp + 2) == SHADOW_INDEX )
							goto isshadow;
				}
				if( j > 1 )
				{
					if( *(sp - srcpitch) == xpc )
						if( *(sp - (srcpitch << 1)) == SHADOW_INDEX )
							goto isshadow;
				}
				if( j < height - 2 )
				{
					if( *(sp + srcpitch) == xpc )
						if( *(sp + (srcpitch << 1)) == SHADOW_INDEX )
							goto isshadow;
				}
				if( i > 0 )				
					if( *(sp - 1) != xpc )
						continue;
				if( i < width - 1 )
					if( *(sp + 1) != xpc )
						continue;
				if( j > 0 )
					if( *(sp - srcpitch) != xpc )
						continue;
				if( j < height - 1 )
					if( *(sp + srcpitch) != xpc )
						continue;
isshadow:
				*sp = xpc;
				dp = dest + j * destpitch + (i >> 3);
				bit = 7 - i % 8;
				*dp |= 1 << bit;					
				if( DITHERED_SHADOWS )
				{
					if( i < width - 2 )
					{
						if( (*(sp + 1) == xpc) && (*(sp + 2) != xpc) )
						{
							dp = dest + j * destpitch + ( (i + 1) >> 3 );
							bit = 7 - (i + 1) % 8;
							*dp |= 1 << bit;
						}
					}
					i++;								// next one can't be a shadow!
				}
			}
			else if( *sp == xpc )
			{
				if( DITHERED_SHADOWS )
				{
					if( j > 0 )
						if( *(sp - srcpitch) != SHADOW_INDEX )
							continue;
					if( j < height - 1)
						if( *(sp + srcpitch) != SHADOW_INDEX )
							continue;
					dp = dest + j * destpitch + ( i  >> 3 );
					bit = 7 - (i % 8);
					*dp |= 1 << bit;
				}
			}
		}
	}

	return TRUE;
}


/*
	PROCESS BITS for Cropping
*/
BOOL is_cropped( BYTE *pBits, int Height, int Width, int Pitch )
{
	BYTE xpc = *pBits;
	BYTE *sp;
	int  i, gap;

	sp = pBits;
	for( i = 0; i < Width; i++ )			// first row
		if( *sp++ != xpc )
			break;
	if( i >= Width )
		return FALSE;
	sp = pBits + (Height - 1) * Pitch;
	for( i = 0; i < Width; i++ )			// last row
		if( *sp++ != xpc )
			break;
	if( i >= Width )
		return FALSE;
	sp = pBits + Width - 1;
	gap = Pitch - Width + 1;
	for( i = 0; i < Height - 2; i++ )
	{
		if( *sp != xpc )
			break;
		sp += gap;
		if( *sp != xpc )
			break;
		sp += (Width - 1);
	}
	if( i >= Height - 2 )
		return FALSE;

	return TRUE;
}


/*
	count # of non-black colors in palette (add 1 for black)
*/
int get_ncolors_in_palette( BITMAPINFO_256 &bminfo )
{
	int count = 0;

	for (int i = 0; i < 256; i++ )
	{
		if( bminfo.bmiColors[i].rgbRed != 0 ||
			bminfo.bmiColors[i].rgbGreen != 0 ||
			bminfo.bmiColors[i].rgbBlue != 0 )
		count++;
	}
	if ( count < 256 )
		count++;

	return( count );
}


/*
	PROCESS A FILE
*/
void process_file( char *filename, _finddata_t &fdata )
{
	char			shadfile[128];

	BITMAPINFO_256	bminfo, shinfo;
	BYTE			*pBits;
	BYTE			*sBits;
	int				spitch, ssize, bpitch;
	_finddata_t		sfdata;
	long			fsh;
	tm				*dt;
	int				hsx, hsy;

	_strlwr( filename );
	strcpy( shadfile, filename );
	shadfile[strlen(shadfile)-4] = 0;
	dt = localtime( &(fdata.time_write) );
	
	printf( "%-12s  %8d  %02d%02d%02d  %02d:%02d", shadfile, (int)fdata.size,
		dt->tm_year, dt->tm_mon, dt->tm_mday, dt->tm_hour+1, dt->tm_min );
	strcat( shadfile, ".sha" );

	pBits = GetBitmap( filename, &bminfo );
	if( pBits == 0 )
	{
		printf( "\n*** ERROR READING FILE ***\n" );
		return;
	}
	memcpy( &shinfo, &bminfo, sizeof(BITMAPINFO_256) );
	spitch = ( ( bminfo.bmiHeader.biWidth + 31 ) & ( ~(DWORD)31 ) ) >> 3;
	bpitch = ( ( bminfo.bmiHeader.biWidth + 3 ) & ( ~(DWORD)3 ) );
	ssize = spitch * bminfo.bmiHeader.biHeight;
	sBits = (BYTE *)malloc( ssize );
	if( sBits == 0 )
	{
		printf( "\n*** OUT OF MEMORY ERROR ***\n" );
		return;
	}
	memset( sBits, 0, ssize );
	shinfo.bmiHeader.biBitCount = 1;
	shinfo.bmiHeader.biSizeImage = ssize;

	NUM_FILES_PROCESSED++;

	printf( "  %3d", get_ncolors_in_palette( bminfo ) );

	hsx = bminfo.bmiHeader.biXPelsPerMeter;
	hsy = bminfo.bmiHeader.biYPelsPerMeter;
	if( hsx == 0 && hsy == 0 )
		printf( "     %1s   ", "N" );
	else
	{
		if( hsx < 0 || hsx > 999 || hsy < 0 || hsy > 999 )
			printf( "    -,-  " );
		else
			printf( "  %3d,%3d", hsx, hsy );
	}
	if( is_cropped( pBits, bminfo.bmiHeader.biHeight, bminfo.bmiHeader.biWidth, bpitch ) )
		printf( "   Y " );
	else
		printf( "   N " );


	if( !SEPARATE_SHADOWS )
		goto skip_shadow_process;
	
	if( !separate_shadow( pBits, sBits, bminfo.bmiHeader.biHeight, bminfo.bmiHeader.biWidth, 
		bpitch, spitch))
	{
		if ( !COMPUTE_SHADOW_INDEX )
			printf( "\n*** ERROR: SHADOW INDEX = TRANSPARENT INDEX ***" );
		else
			goto write_bitmap_file;
		goto skip_shadow_process;
	}

write_bitmap_file:
	if( OVERWRITE_EXIST )
	{
		if( fdata.attrib & _A_RDONLY )
		{
			if( OVERWRITE_LOCK )
				_chmod( fdata.name, _S_IWRITE );
			else
			{
				printf( "\n*** BITMAP FILE IS WRITE PROTECTED ***" );
				goto write_shadow_file;
			}
		}
		SaveBitmap( filename, bminfo, pBits );
	}
write_shadow_file:
	fsh = _findfirst( shadfile, &sfdata );
	if( fsh != -1 )
	{
		_findclose( fsh );
		if ( OVERWRITE_EXIST )
		{
			printf( "\n*** SHADOW FILE ALREADY EXISTS ***" );
			goto end_write_shadow;
		}
		if ( sfdata.attrib & _A_RDONLY )
			if( OVERWRITE_LOCK )
				_chmod( sfdata.name, _S_IWRITE );
			else
			{
				printf( "\n*** SHADOW FILE IS WRITE PROTECTED ***" );
				goto end_write_shadow;
			}
	}
	SaveBitmap( shadfile, shinfo, sBits );
end_write_shadow:
	;

skip_shadow_process:
	free( pBits );
	free( sBits );
	printf( "\n" );
}


/*
	HELP / INVALID COMMAND LINE
*/
void exit_err( void )
{
	printf( "\n" );
	printf( "SYNTAX: separate [-r] [-p#] [SEARCHPATH]\n\n" );
	printf( "-o\t\tOverwrite existing files.\n" );
	printf( "-r\t\tRecurse directories.\n" );
	printf( "-s\t\tSeparates out dithered shadows.\n" );
	printf( "-u\t\tUnlock locked files & overwrite (always enables -o).\n" );
	printf( "-p#\t\tShadow pixel palette index. (0-255).\n" );
	printf( "-d\t\tDithered shadows.\n" );
	printf( "SEARCHPATH\tSearch directory.\n\n" );
	printf( "DESCRIPTION:  Attempts to separate shadows from bitmaps.  (Shadows are defined\n" );
	printf( "\tas single pixels of a particular color with at least a single\n" );
	printf( "\ttransparent pixel either to the left or the right of it).  The shadow\n" );
	printf( "\tis deleted from the original bitmap file, and a new bitmap file of\n" );
	printf( "\tthe same dimensions is created with the shadow image as a 1bpp solid\n" );
	printf( "\tmask.  The shadow file is given the extension .SHA\n" );
	exit( -1 );
}


void print_legend( void )
{
	printf( "BMP FILE: File name of bitmap file.\n" );
	printf( "SIZE:     File size in bytes.\n" );
	printf( "DATE:     Date file was last modified.\n" );
	printf( "TIME:     Time file was last modified.\n" );
	printf( "#CO:      Number of distinct colors in palette.\n" );
	printf( "HOTSPOT:  Hotspot location.  (N)o hotspot.  (-,-) Invalid hotspot.\n" );
	printf( "CR?:      Y= Cropped,  N= Not cropped.\n" );
	printf( "\n" );
}


void print_header( char *dir )
{
	printf( "\nDIR: %s\n", dir );
	printf( "%-12s  %8s  %6s  %5s  %3s  %7s  %3s\n", 
		"BMP FILE", "SIZE", "DATE", "TIME", "#CO", "HOTSPOT", "CR?" );
}


/*
	SEARCH FOR FILES TO PROCESS
*/
void process_directory( char *dirname )
{
	_finddata_t fdata;
	long		fsh;
	static char	pd[128] = "";
	static char cd[128] = "";
	static BOOL HAS_SHOWN_LEGEND = FALSE;

	_getcwd( cd, 128 );
	if( _chdir( dirname ) != 0 )
	{
		printf("Invalid search path.\n" );
		exit_err();
		return;
	}
	fsh = _findfirst( "*.*", &fdata );
	if( fsh != -1 )
	{
		do
		{
			if( strcmp( fdata.name, "." ) == 0 )
				continue;
			if( strcmp( fdata.name, ".." ) == 0 )
				continue;
			if( (fdata.attrib & _A_SUBDIR) && RECURSE_DIRECTORIES )
			{
				process_directory( fdata.name );
				_chdir( ".." );
			}
			else
			{
				int l = strlen( fdata.name );
				if( l < 5 )
					continue;
				if( stricmp( (char *)(fdata.name + l - 4), ".bmp") == 0 )
				{
					_getcwd( cd, 128 );
					if( strcmp( pd, cd ) != 0 )
					{
						if( !HAS_SHOWN_LEGEND )
						{
							HAS_SHOWN_LEGEND = TRUE;
							print_legend();
						}
						print_header( cd );
						strcpy( pd, cd );
					}
					process_file( fdata.name, fdata );
				}
			}
		} while( _findnext( fsh, &fdata ) == 0 );
		_findclose( fsh );
	}
}


/*
	MAIN
*/
void main( int argc, char *argv[ ], char *envp[ ] )
{
	int shc;

	if( argc > 4 )
		exit_err();
	for( int i = 1; i < argc; i++ )
	{
		if( (argv[i][0] == '-') || (argv[i][0] == '/') )
		{
			int j, l;

			l = strlen( argv[i] );
			j = 1;

			while( j < l )
			{
				switch( argv[i][j++] )
				{
				case 'o':
					OVERWRITE_EXIST = TRUE;
					break;
				case 'p':
					if( argv[i][j] == 0 )
						exit_err();
					shc = atoi( argv[i]+j );
					if(shc < 0 || shc > 255 )
					{
						printf("Invalid shadow color (should be 0-255).\n" );
						exit_err();
					}
					COMPUTE_SHADOW_INDEX = FALSE;
					SHADOW_INDEX = shc;
					while( argv[i][j] >= '0' && argv[i][j] <= '9' )
						j++;
					break;
				case 'r':
					RECURSE_DIRECTORIES = TRUE;
					break;
				case 's':
					SEPARATE_SHADOWS = TRUE;
					break;
				case 'd':
					DITHERED_SHADOWS = TRUE;
					break;
				case 'u':
					OVERWRITE_EXIST = TRUE;
					OVERWRITE_LOCK = TRUE;
					break;
				case '?':
					exit_err();
					break;
				}
			}
		}
		else strcpy( SEARCH_DIRECTORY, argv[i] );
	}
	if( SEARCH_DIRECTORY[0] == 0 )
		strcpy( SEARCH_DIRECTORY, "." );		

	process_directory( SEARCH_DIRECTORY );

	printf( "\nProcessed a total of %d files.\n", NUM_FILES_PROCESSED );
	printf( "\n" );
}
