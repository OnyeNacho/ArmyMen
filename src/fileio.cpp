//
//  File I/O operations
//
//
//

#include "stdafx.h"


#include "miscfile.h"
#include "fileio.h"
#include "army.h"
#include "object.h"
#include "map.h"
#include "disp.h"
#include "ui.h"


//************************************************************************
//	Externs
//************************************************************************
extern LPDIRECTDRAW2 pDirectDraw2;
DWORD TranslateBitmapToDD( BYTE* pDestStart,	//	First byte in dest data.
				long lPitchDest,			//	Dest data's line pitch.
				const BYTE* pBMStart,		//	First byte in source data.
				int width,					//  Number of bytes per line in source image
				int	height,					//	Number of lines in source image.
				BYTE table[256] );			//	translation table


//************************************************************************
//	Definitions
//************************************************************************

#define OBJECT_FILEID  132415161				// this is the uid for object data files


//************************************************************************
//	Structures
//************************************************************************

struct TObjectTableEntry						// object directory entry
{
	int key;									// object key
	int offset;									// offset in data file
	int count;									// instance count
	PSPRITE pSprite;							// pointer to the sprite
};


int   ObjectTableEntryHeaderSize = sizeof(int) + sizeof(int);


struct TObjectDataFile							// object data file
{
	FILE	*fp;								// file pointer
	int		nObjects;							// # of objects in directory
	TObjectTableEntry *ObjectTable;				// object directory (sorted)
	RGBQUAD palette[256];						// palette
};


TObjectDataFile ODF =							// global object data file variable
{
	NULL,
	0,
	NULL
};


//************************************************************************
//	Global Variables
//************************************************************************

BOOL	_LOAD_FROM_DATAFILE = TRUE;


#ifdef _OBJECT_DEBUG
int OD_Category;
int OD_Number;
int	OD_Width;
int	OD_Height;
int OD_Size;
int OD_nAnimFrames;
int OD_nDamageFrames;
int OD_MaskSize;
int OD_ShadowSize;
int OD_Rect;
int OD_SharedBitmap;
int OD_Hotspot;
int OD_Linkspot;
int OD_FrameNumber;
int OD_SpriteType;
#endif


//************************************************************************
//	Local Variables
//************************************************************************

//	object graphic filenames are generated from:
//	4 letter category prefix (see below)
//	- 3 digit id number (unique w/in category)
//	- 8 letter info tag (optional)
//	.bmp
//	e.g. ROCK-001.BMP is rock #1 and BRID-003-SUSP135.bmp is bridge #3.
//	it is an error condition to have a repeated ID number
//	e.g. BRID-003-SUSP135.bmp and BRID-003-SUSP180.bmp can't both exist


extern char *obj_category_dirs[];

BYTE  main_trans_table[256];						// translation table from mainpal
BYTE  fixed_trans_table[256];



//************************************************************************
//	Basic File I/O Functions
//************************************************************************

//	Read into buffer from a stream  (file & line is used for trace only)
BOOL Read( void *buffer, size_t size, size_t count, FILE *stream, char *file, int line )	
{
	size_t bytes;

	if (!count || !size)
		return 0;

	bytes = fread( buffer, size, count, stream );
	if ( bytes != count )
	{
		// report an error: failed reading header
		TRACE("ERROR: failed to read. (%d of %d) [%s:%d]\n", 
			  bytes, count, file, line );
		return FALSE;
	}
	return TRUE;
}	// Read


//	Get a short from the buffer
short GetShort(char *pBuffer, int offset) 
{
	short *pShort;

	pShort = (short *) &pBuffer[offset];
	return *pShort;
}	// GetShort


//	Get a long from the buffer
long GetLong(char *pBuffer, int offset)	
{
	long *pLong;

	pLong = (long *) &pBuffer[offset];
	return *pLong;
}	// GetLong


//  Read a word from the buffer
WORD readWord( FILE * fp )
{
  WORD buf;
  int  err;

  err = fread( &buf, sizeof(WORD), 1, fp );
  if ( err != 1 )
  {
	  TRACE( "Error in readWord\n" );
	  return 0;
  }
  return buf;
} // readWord


// Read a dword from the buffer
DWORD readDword( FILE * fp )
{
  DWORD buf;
  int   err;

  err = fread( &buf, sizeof(DWORD), 1, fp );
  if ( err != 1 )
  {
	  TRACE( "Error in readDword\n" );
	  return 0;
  }
  return buf;
} // readDword



//************************************************************************
//	Bitmap I/O Functions
//************************************************************************

//	Get a bitmap from a resource
BYTE *CopyBitmapFromResource(HRSRC hrsrc, BITMAPINFO_256 *pbminfo)
{
	BYTE *pRsrc;
	BITMAPINFOHEADER *pHeader = &pbminfo->bmiHeader;

	pRsrc = (BYTE *) LockResource(LoadResource(NULL, hrsrc));
	if (!pRsrc)
		return NULL;

	BYTE *pSrc = pRsrc;

	memcpy(pHeader, pSrc, sizeof(BITMAPINFOHEADER));
	pSrc += sizeof(BITMAPINFOHEADER);

	ASSERT(pHeader->biBitCount <= 8 );

	if (pHeader->biClrUsed == 0)
		pHeader->biClrUsed = 1 << pHeader->biBitCount;

	UINT iColorTableSize = pHeader->biClrUsed * sizeof(RGBQUAD);

	// Now read the color table in
	memcpy(pbminfo->bmiColors, pSrc, iColorTableSize);
	pSrc += iColorTableSize;

	DWORD bmsize = pHeader->biSizeImage;
	if (bmsize == 0)
		bmsize = ((pHeader->biWidth + sizeof(LONG) - 1) & ~3) * pHeader->biHeight * (pHeader->biBitCount / 8);

	// create a memory area for this bitmap
	BYTE *pBits = (BYTE *) malloc(bmsize);
	if (pBits == NULL)	
	{
	    TRACE("malloc failed in CopyBitmapFromResource()\n");
		return NULL;
	}

	// copy the bits.
	memcpy(pBits, pSrc, bmsize);

	return pBits;
}	// CopyBitmapFromResource


//	Read a bitmap from a file stream
BYTE *ReadBitmap( FILE* pFile, BITMAPINFO_256 *pbminfo )
{
	BITMAPINFOHEADER *pHeader = &pbminfo->bmiHeader;

	// Get the current file position
	DWORD dwFileStart = ftell(pFile);

 	BITMAPFILEHEADER bmfile;
	READ_BUFFER(&bmfile, sizeof(bmfile));

	READ_BUFFER(pHeader, sizeof(BITMAPINFOHEADER));

#if _DEBUG
	if (pHeader->biBitCount > 8)
		Error("Too many colors in bitmap\n");
#endif
	ASSERT(pHeader->biBitCount <= 8 );

	if (pHeader->biClrUsed == 0)
		pHeader->biClrUsed = 1 << pHeader->biBitCount;

	UINT iColorTableSize = pHeader->biClrUsed * sizeof(RGBQUAD);

	// Now read the color table in
	READ_BUFFER( pbminfo->bmiColors, iColorTableSize );	

	// Seek to the bits
	fseek(pFile, dwFileStart + bmfile.bfOffBits, SEEK_SET);

	DWORD bmsize = pHeader->biSizeImage;
	if (bmsize == 0)	
	{
		if (pHeader->biBitCount == 8)
			bmsize = ((pHeader->biWidth + 3) & ~3) * pHeader->biHeight * (pHeader->biBitCount / 8);
		else	
		{
			bmsize = (((pHeader->biWidth + 7)/8) & ~3) * pHeader->biHeight;
			TRACE( "WARNING: setting bmsize for a non-8 bit bitmap. [%s,%d]\n", __FILE__, __LINE__ );
		}
	}

	// create a memory area for this bitmap
	BYTE *pBits = (BYTE *) malloc(bmsize);
	if (pBits == NULL)	
	{
	    TRACE("malloc failed in ReadBitmap()\n");
		return NULL;
	}

	// Read the bits.
	READ_BUFFER(pBits, bmsize);

	return pBits;
}	// ReadBitmap


//  read a bitmap from a file stream
BOOL DDReadBitmap( FILE* pFile, LOADBITMAP *plbitmap )
{
	BITMAPINFO_256	bminfo;
	BOOL size = 0;

	BYTE *pBits = ReadBitmap(pFile, &bminfo);
	if (pBits)	{
		size = MakeBitmap(&bminfo, pBits, plbitmap, NULL);
		free(pBits);
	}

    return size;
}	// DDReadBitmap


//	Open a bitmap file & read it in using ReadBitmap
BYTE *GetBitmap( char *szName, BITMAPINFO_256 *pbminfo )	
{
	FILE *pfile;
	BYTE *pBits;

	ASSERT( szName != NULL );
	ASSERT( szName[0] != 0 );
	if ((pfile = fopen( szName, "rb" )) != NULL)	
	{
		pBits = ReadBitmap(pfile, pbminfo);
		fclose(pfile);
		return pBits;
	}
	else
		return NULL;
}	// GetBitmap


//  Load & create a bitmap
DWORD BitmapLoad(char *szName, LOADBITMAP *plbitmap)
{
	BITMAPINFO_256		bminfo;
	HRSRC	hrsrc;
	BOOL	size = 0;
	BYTE	*pBits;

	if (hrsrc = FindResource(NULL, szName, RT_BITMAP))
		pBits = CopyBitmapFromResource(hrsrc, &bminfo);
	else
		pBits = GetBitmap(szName, &bminfo);

	if (pBits)	{
		size = MakeBitmap(&bminfo, pBits, plbitmap, NULL);
		free(pBits);
	}

    return size;
}	// BitmapLoad



//************************************************************************
//	Shadow Functions
//************************************************************************

BOOL isBitSet( BYTE *pBits, int i, int j, int ht, int sPitch )
{
	BYTE b = *(BYTE *)(pBits + (ht - j - 1) * sPitch + (i >> 3) );
	BYTE bit = 7 - (i % 8);
	return ( b & (1 << bit) );
}


void *SpriteShadowLoad( char *szName )
{
	BITMAPINFO_256	bminfo;
	BYTE	*pBits;
	FILE	*pFile;
	BITMAPINFOHEADER *pHeader = &(bminfo.bmiHeader);
	BYTE	*tempBuf;
	BYTE	*dp;
	int		sPitch;

#ifdef _OBJECT_DEBUG
	OD_ShadowSize = 0;
#endif
	if ( ( pFile = fopen( szName, "rb" )) == NULL )	
		return NULL;

	DWORD dwFileStart = ftell(pFile);
 	BITMAPFILEHEADER bmfile;
	READ_BUFFER(&bmfile, sizeof(bmfile));
	READ_BUFFER(pHeader, sizeof(BITMAPINFOHEADER));
//	ASSERT(pHeader->biBitCount == 1 );
	if (pHeader->biBitCount != 1 )
	{
		fclose( pFile );
		TRACE("ERROR: %s not in 1-bit mode\n",szName);
		return NULL;
	}

	UINT iColorTableSize = pHeader->biClrUsed * sizeof(RGBQUAD);
	READ_BUFFER(&(bminfo.bmiColors), iColorTableSize );	
	fseek(pFile, dwFileStart + bmfile.bfOffBits, SEEK_SET);

	DWORD bmsize = pHeader->biSizeImage;

	if( bmsize <= 0 )
	{
		fclose( pFile );
		TRACE( "ERROR: invalid file size in %s.\n", szName );
		return NULL;
	}
	pBits = (BYTE *)malloc(bmsize);
	if (pBits == NULL)	
	{
	    TRACE("malloc failed in ReadShadow()\n");
		fclose( pFile );
		return NULL;
	}
	READ_BUFFER(pBits, bmsize);
	fclose( pFile );

	sPitch = bmsize / pHeader->biHeight;
	tempBuf = (BYTE *)malloc( pHeader->biHeight * 2 * 40 );
	if( tempBuf == NULL )
	{
		free( pBits );
		fclose( pFile );
	    TRACE("malloc failed in ReadShadow()\n");
		return NULL;
	}
	*(WORD *)tempBuf = (WORD)pHeader->biWidth;
	*(WORD *)(tempBuf + 2) = (WORD)pHeader->biHeight;
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
				(!isBitSet( pBits, i, j, pHeader->biHeight, sPitch )) )
			{
				i++;
				count++;
			}
			*dp++ = count;

			count = 0;
			while( (i < pHeader->biWidth) && (count < 255) && 
				(isBitSet( pBits, i, j, pHeader->biHeight, sPitch )) )
			{
				i++;
				count++;
			}
			*dp++ = count;

			if (i >= pHeader->biWidth-1 )
				break;
		}
	}
	free( pBits );
	bmsize = dp - tempBuf;
	pBits = (BYTE *)malloc( bmsize );
	if( pBits == NULL )
	{
		free( tempBuf );
		fclose( pFile );
	    TRACE("malloc failed in ReadShadow()\n");
		return NULL;
	}
	memcpy( pBits, tempBuf, bmsize );
	free( tempBuf );

#ifdef _OBJECT_DEBUG
	OD_ShadowSize = ( pHeader->biWidth == OD_Width && pHeader->biHeight == OD_Height ? bmsize : 0 );
#endif

	return pBits;
}	// SpriteShadowLoad


//	Load a sprite shadow from a file
void LoadSpriteShadow( PSPRITE pSprite, char *name )
{
	pSprite->pShadow = SpriteShadowLoad( name);
}   // LoadSpriteShadow


//  Load a sprite shadow & create an "empty" sprite
void LoadShadowAsSprite( PSPRITE pSprite, char *name, BYTE *ShadeTable )
{
	ZeroMemory(pSprite, sizeof(SPRITE));
	pSprite->pGraphic = NULL;
	LoadSpriteShadow(pSprite, name);
	if( !(pSprite->pShadow) )
		return;
	pSprite->srect.left   = pSprite->srect.top = 0;
	pSprite->srect.right  = *(WORD *)(pSprite->pShadow);
	pSprite->srect.bottom = *( ((WORD *)(pSprite->pShadow)) + 1);
	pSprite->hotspot.x = (short)(pSprite->srect.right >> 1);
	pSprite->hotspot.y = (short)(pSprite->srect.bottom >> 1);
	pSprite->linkspot.x = 0;
	pSprite->linkspot.y = 0;
	pSprite->sprite_flags |= ( BM_SRLE );
	pSprite->trans_table = ShadeTable;
	pSprite->sprite_type = SPRITE_TYPE_SRLE;
}


//************************************************************************
//	Mask Functions
//************************************************************************

// Translate an image to a mask
// assumes that bitmap (source) pitch is the width, padded to a LONG boundary
BOOL TranslateMask( BYTE* pDest,			//	First byte in dest data.
				const BYTE* pBMStart,		//	First byte in source data.
				int size,					//	total size of mask
				int	height )				//	Number of lines in source image.
{
	const BYTE*	pSrc;
	LONG		pitch = size / height;

	pSrc = pBMStart + (height - 1) * pitch;	// beginning of last line of source

	for( int y=0; y<height; y++ )	
	{
		memcpy(pDest, pSrc, pitch);
		pDest += pitch;
		pSrc -= pitch;
	}

	return TRUE;
}	// TranslateMask


//	Load a mask (bitmap) given the name of it, return ptr to mask
BYTE *MaskLoad( char *szName, BITMAPINFO_256 *pbminfo, DWORD *psize )
{
	HRSRC	hrsrc;
	BYTE	*pBits;
	BYTE	*pNewBits = NULL;
	DWORD	maxsize;

	*psize = 0;

	if (hrsrc = FindResource(NULL, szName, RT_BITMAP))
		pBits = CopyBitmapFromResource(hrsrc, pbminfo);
	else
		pBits = GetBitmap(szName, pbminfo);

	if (pBits)	
	{
		// create a memory area for this bitmap
		maxsize = pbminfo->bmiHeader.biSizeImage;
		if (!maxsize)
		{
			TRACE("ERROR: %s has listed size of 0 (try resaving)\n", szName);
			return NULL;
		}
		pNewBits = (BYTE *) malloc(maxsize);
		if (pNewBits != NULL)
		{
			TranslateMask(pNewBits, pBits, maxsize, pbminfo->bmiHeader.biHeight);
			*psize = maxsize;
			free(pBits);
		}
	}

	return (pNewBits);
}	// MaskLoad


//	Load a sprite mask (bitmap) from a file
DWORD LoadSpriteMask( PSPRITE pSprite, char *name )
{
	DWORD size;
	BITMAPINFO_256	bminfo;

	pSprite->pMask = MaskLoad(name, &bminfo, &size);
	pSprite->sprite_flags |= SP_PRIMEMASK;

#ifdef MASK_DEBUG
	if ( !pSprite->pMask )	{
		char *path = _getcwd( NULL, MAX_PATH );

		TRACE( "Can't load mask: %s\\%s!\n", path, name );
		free( path );
	}
#endif

	if((!pSprite->pMask) || bminfo.bmiHeader.biHeight != pSprite->srect.bottom || bminfo.bmiHeader.biWidth != pSprite->srect.right)
	{
		TRACE("Bad Mask size: %s\n", name);
		if( pSprite->pMask )
			free(pSprite->pMask);
		pSprite->pMask = NULL;
		pSprite->sprite_flags &= ~SP_PRIMEMASK;
		size = 0;
	}
#ifdef _OBJECT_DEBUG
	OD_MaskSize = (bminfo.bmiHeader.biHeight == OD_Height && bminfo.bmiHeader.biWidth == OD_Width  ? size : 0 );	
#endif

	return(size);
}  // LoadSpriteMask

/*
// Load a mask (bitmap) from a stream
BYTE *MaskLoadStream( FILE * fp )
{
	BYTE	*pBits;
	DWORD   dw, size;

	dw = readDword( fp );
	if ( dw != ARMYMEN_3DO_MASK_ID )
	{
		TRACE( "Error while reading mask data.\n" );
		return NULL;
	}
	size = readDword( fp );

	pBits = (BYTE *)malloc( size );
	if (pBits == NULL)
	{
		TRACE( "Out of memory error trying to allocate memory for mask.\n" );
		return NULL;
	}
	if ( fread( pBits, 1, size, fp ) != size )
	{
		TRACE( "Error reading mask data.\n" );
		return NULL;
	}

	return (pBits);
}	// MaskLoadStream
*/


//************************************************************************
//	Rect Functions
//************************************************************************

//  Load a Rect from a file
BOOL RectLoad( char *szName, RECT *pRect )
{
	FILE *pFile;

	if ( ( pFile = fopen( szName, "rb" ) ) != NULL )	
	{
		READ_BUFFER( pRect, sizeof(RECT) );
		fclose( pFile );
		return TRUE;
	}
	else
		return FALSE;
}	// RectLoad


//	Load a Rect from a file & attach to a sprite
void LoadSpriteRect( PSPRITE pSprite, char *name )
{
	RECT maskRect;

#ifdef MASK_DEBUG
	char *path;
	path = _getcwd(NULL, MAX_PATH);
#endif

	if( !RectLoad(name, &maskRect) )	{
#ifdef MASK_DEBUG
		TRACE("Can't load rect: %s\\%s!\n", path, name);
#endif
		pSprite->sprite_flags &= ~SP_MASKRECT;
	}
	else	{
		pSprite->maskRect = maskRect;
		pSprite->sprite_flags |= SP_MASKRECT;
	}

#ifdef MASK_DEBUG
	free(path);
#endif
}	// LoadSpriteRect

/*
//	Load a Rect from a stream
BOOL RectLoadStream( FILE * fp, RECT *pRect )
{	
	return (fread( pRect, sizeof(RECT), 1, fp ) == 1 );
}	// RectLoadStream
*/


//************************************************************************
//	RLE Loading Functions
//************************************************************************

//  Load & color translate an RLE256 from a stream
BYTE *LoadRLE256Stream( FILE * fp, DWORD size, ESpriteType sprite_type )
{
	BYTE   *buf, *sp;
	WORD   wd, ht;
	DWORD  *lsd, *led;
	WORD   *lsw, *lew;
	BYTE   n;
	WORD   c;

	buf = (BYTE *)malloc( size );
	if ( buf == NULL )
	{
		TRACE( "Out of memory for RLE256 sprite.\n" );
		return NULL;
	}
	if( fread( buf, size, 1, fp ) != 1 )
	{
		TRACE( "Error reading RLE256 sprite from stream.\n" );
		free( buf );
		return NULL;
	}
	wd = *(WORD *)( buf );
	ht = *(WORD *)( buf + sizeof(WORD) );

	if( sprite_type == SPRITE_TYPE_DRLE )
	{
		lsd = (DWORD *)(buf + sizeof(WORD)*2 );
		led = (DWORD *)(buf + sizeof(WORD)*2 + sizeof(DWORD)*ht );
		while ( lsd < led )
		{	
			sp = buf + *lsd;
			c = 0;

			while ( c < wd )
			{
				n = *sp++;
				c += n;

				n = *sp++;
				c += n;
				for ( int i = 0; i < n; i++ )
				{
					*sp = main_trans_table[*sp];
					sp++;
				}
			}
			lsd++;
		}
	}
	else
	{
		BYTE *temp_trans_table;

		if( sprite_type == SPRITE_TYPE_TRLE )
			temp_trans_table = fixed_trans_table;
		else
			temp_trans_table = main_trans_table;

		lsw = (WORD *)(buf + sizeof(WORD)*2 );
		lew = (WORD *)(buf + sizeof(WORD)*2 + sizeof(WORD)*ht );
		while ( lsw < lew )
		{	
			sp = buf + *lsw;
			c = 0;

			while ( c < wd )
			{
				n = *sp++;
				c += n;

				n = *sp++;
				c += n;
				for ( int i = 0; i < n; i++ )
				{
					*sp = temp_trans_table[*sp];
					sp++;
				}
			}
			lsw++;
		}
	}
	return( buf );
}


//************************************************************************
//	Sprite Functions
//************************************************************************
typedef struct
{
	int	number;
	int	data_size;
	int	graphics_size;
	int	base_graphics_size;
	int	mask_size;
} ObjSize;


//	Load all sprite frames for an object from a file
static int LoadObjectSprites(int index, OBJECT_SPRITE *pObjSprite, LONG number, LONG category, char *dir, ObjSize *pobjsize )
{
	char pathname[MAX_PATH];
	char filename[_MAX_FNAME];
	DWORD	size = 0;
	BOOL	ok = TRUE;
	int filesfound=0;
	BOOL done=FALSE;
	int i;
	char base_filename[32];
	char eight_char_filename[10];

	pobjsize->number = 0;
	pobjsize->data_size = 0;
	pobjsize->graphics_size = 0;
	pobjsize->base_graphics_size = 0;
	pobjsize->mask_size = 0;

	sprintf(pathname,"LoadObjects/%s/Objects/%s", dir, obj_category_dirs[category]);
	SetPath(pathname);

	sprintf(filename,"????_%03d*.bmp", number);

	WIN32_FIND_DATA FindFileData;
	HANDLE hSearch;

	hSearch = FindFirstFile(filename, &FindFileData);
	if (hSearch == INVALID_HANDLE_VALUE)	
	{
		TRACE("ERROR: unable to find a file %s %s for object %d of category %d number %d\n", filename,
            pathname,index,category,number);
		return -1;
	}

	// check for a non-underscore name, which indeicates the basic name 
	if (FindFileData.cFileName[8] != '_')
		strcpy(base_filename, FindFileData.cFileName);

	filesfound=1;

	for (i=0;i<8;i++)
		eight_char_filename[i]=FindFileData.cFileName[i];
	eight_char_filename[8]='\0'; //we take the filename that we got back from our search
							  //and save the first 8 characters, because we'll need them
							  //to construct the filenames of all the levels of damage, plus
							  //the masks and rects and whatnot

	do
	{
		if (FindNextFile(hSearch, &FindFileData))
		{
			// check for duplicate numbers and badly formed names
			if (strnicmp(eight_char_filename, FindFileData.cFileName, 8) == 0)
			{
				// check for a non-underscore name, which indeicates the basic name 
				if (FindFileData.cFileName[8] != '_')
					strcpy(base_filename, FindFileData.cFileName);

				filesfound++;
			}
#ifdef SPRITE_DEBUG
			else
			{
				TRACE("Duplicate object numbers: %s and %s\n", FindFileData.cFileName, eight_char_filename);
			}
#endif
		}
		else
		{
			if (GetLastError()!=ERROR_NO_MORE_FILES)
				TRACE("ERROR: unkown error in file search\n");
			else
				done=TRUE;
		}
	}
	while(!done);

	FindClose(hSearch);

	//in this section of code, we'll try to find a file with a name like
	//"TREE_030_a13,2" which will tell us that the last 13 sprites we find
	//are animation, rather than damage. The 2 means that it skips 2 frames
	//between every time it animates (so that it animates at 1/3 speed)
	sprintf(filename, "%s_a*", eight_char_filename);
	hSearch = FindFirstFile(filename, &FindFileData);
	if (hSearch!=INVALID_HANDLE_VALUE)
	{
		FindFileData.cFileName[12]=0;
		pObjSprite->nAnimFrames=atoi((FindFileData.cFileName)+10);
		pObjSprite->nAnimDelay=atoi((FindFileData.cFileName)+13);
		FindClose(hSearch);
		pObjSprite->nLevelsOfDamage=filesfound-pObjSprite->nAnimFrames+1;

	}
	else
	{
		pObjSprite->nAnimFrames=0;
		pObjSprite->nLevelsOfDamage=filesfound;
	};

#ifdef _OBJECT_DEBUG
	OD_Category = category;
	OD_Number = number;
	OD_nAnimFrames = pObjSprite->nAnimFrames;
	OD_nDamageFrames = pObjSprite->nLevelsOfDamage;
#endif

	pobjsize->number = filesfound;
	pobjsize->data_size = sizeof(SPRITE)*filesfound;

	pObjSprite->sprites=(SPRITE*)malloc(sizeof(SPRITE)*filesfound);
	if (pObjSprite->sprites==NULL)
		return -1;

	ZeroMemory(pObjSprite->sprites,sizeof(SPRITE)*filesfound);

#ifdef _OBJECT_DEBUG
	OD_FrameNumber = 0;
#endif

	if ( !(size = LoadSpritePlusMaskAndShadow(&pObjSprite->sprites[0], eight_char_filename, (BM_TRANSPARENT | BM_DRLE_ONLOAD))) )
	{
		TRACE("ERROR while trying to load file %s\n", base_filename);
		return -1;
	}
	pobjsize->base_graphics_size += size;
	pobjsize->graphics_size += size;


	for (i=1;i<filesfound;i++)
	{
#ifdef _OBJECT_DEBUG
		OD_FrameNumber = i;
#endif
		sprintf(filename, "%s_%d", eight_char_filename, i-1);
		if ( !(size = LoadSpritePlusMaskAndShadow(&pObjSprite->sprites[i], filename, (BM_TRANSPARENT | BM_DRLE_ONLOAD))) )
		{
			TRACE("ERROR while trying to load file %s\n", filename);
			return -1;
		}
		pobjsize->graphics_size += size;
	}



#ifdef MASK_DEBUG
	if (!pObjSprite->sprites[0].pMask && !pObjSprite->sprites[0].useMaskRect)
		TRACE("No mask for object %d/%d\n", category, number);
#endif
	
	//set all the hotspots to be the same as the main sprite's hotspot
	
/*	if (filesfound>1)
		for (i=1;i<filesfound;i++)
		{
			pObjSprite->sprites[i].hotspot.x=pObjSprite->sprites[0].hotspot.x;
			pObjSprite->sprites[i].hotspot.y=pObjSprite->sprites[0].hotspot.y;
		};
*/

	return ok;
}	// LoadObjectSprites



//  Load Objects for Scenario

void LoadObjects(char *obj_dir)	
{
	int i;
	OBJECT_SPRITE *pObjSprite;
	LONG category,
		 index,
		 count = 0,
		 footsize,
		 total_footsize = 0;
	ObjSize	objsize;
	ObjSize	total_objsize;
	SPOINT	hotspot, linkspot;


	total_objsize.number = 0;
	total_objsize.data_size = 0;
	total_objsize.graphics_size = 0;
	total_objsize.base_graphics_size = 0;
	total_objsize.mask_size = 0;

	int mapsize = sizeof(the_map);

	//initialize the count of animated objects
	the_map.num_animated_objects=0;

	if (_LOAD_FROM_DATAFILE)
		OpenDataFile( the_map.terrain_name );

	// load sprites for objects we have into sprite arrays in each category
	for( i = 0; i < the_map.num_objects; i++ )	
	{
		category = the_map.objects[i].category;

		MissionLoading( (long)(1300 + i * (float)(2000.0/(float)the_map.num_objects)), 20000 );
		if( _LOAD_FROM_DATAFILE )
		{
			the_map.objects[i].cell.pSprite = AcquireObjectSprite( category, the_map.objects[i].number, 0 );
			if( the_map.objects[i].cell.pSprite )
			{
				hotspot = the_map.objects[i].cell.pSprite->hotspot;
				linkspot = the_map.objects[i].cell.pSprite->linkspot;
			}
		}
		else
		{										// load all damage levels now
			index = the_map.objects[i].index;
			pObjSprite = the_map.obj_sprite_array_list[category];

			if (pObjSprite)	
			{
 				if (!pObjSprite[index].sprites)	
 				{
//					TRACE( "%14s   %4d\n", obj_category_dirs[category], the_map.objects[i].number );
					LoadObjectSprites(i,&pObjSprite[index], the_map.objects[i].number, category, obj_dir, &objsize);
					count++;
					total_objsize.number += objsize.number;
					total_objsize.data_size += objsize.data_size;
					total_objsize.graphics_size += objsize.graphics_size;
					total_objsize.base_graphics_size += objsize.base_graphics_size;
					total_objsize.mask_size += objsize.mask_size;
				}

	 			if (pObjSprite[index].sprites)	
				{
					if (the_map.objects[i].triggers & TRIGGER_DESTROYED)
					{
						the_map.objects[i].cell.pSprite=&pObjSprite[index].sprites[pObjSprite[index].nLevelsOfDamage-1];
						the_map.objects[i].damageindex=pObjSprite[index].nLevelsOfDamage-1;
					}
					else
						the_map.objects[i].cell.pSprite=&pObjSprite[index].sprites[0];

					hotspot = pObjSprite[index].sprites[0].hotspot;
					linkspot = pObjSprite[index].sprites[0].linkspot;		

					//if this object is animated
					if (pObjSprite[index].nAnimFrames>0)
					{
						ANIMATED_OBJECT *pAnimObject;

						if (the_map.num_animated_objects==MAX_NUM_ANIMATED_OBJECTS)
							TRACE("ERROR: too many animated objects\n");

						pAnimObject=&the_map.animatedobjects[the_map.num_animated_objects++];

						pAnimObject->pObj=&the_map.objects[i];
						pAnimObject->curframe=(rand() % pObjSprite[index].nAnimFrames);
						if (pObjSprite[index].nAnimDelay)
							pAnimObject->curcounter=(rand() % pObjSprite[index].nAnimDelay);
						else
							pAnimObject->curcounter=0;
					}
				}
				else	
				{
					TRACE("ERROR: no graphic for object %d/%d\n", category, the_map.objects[i].number);
						the_map.objects[i].cell.flags = ANIM_FLAG_CELL;
				}

			}
			else
				TRACE("ERROR: no obj_sprite_array_list for category %d", category);
		}

		the_map.objects[i].cell.flags = ANIM_FLAG_CELL;
		AnimCellSetOwner( &the_map.objects[i].cell, &the_map.objects[i] );

		if( the_map.objects[i].cell.pSprite )
		{				
			//	set cell flags
			the_map.objects[i].cell.flags |= ANIM_FLAG_ACTIVE;
			if( the_map.objects[i].triggers & TRIGGER_INVISIBLE )
				the_map.objects[i].cell.flags |= ANIM_FLAG_INVISIBLE;
			if( the_map.objects[i].triggers & TRIGGER_UNDEPLOYED )
				the_map.objects[i].cell.flags &= ~ANIM_FLAG_ACTIVE;


			the_map.objects[i].cell.world_pos.x += hotspot.x-linkspot.x;
			the_map.objects[i].cell.world_pos.y += hotspot.y-linkspot.y;
			the_map.objects[i].common.tile = IPOINT_FROM_SPOINT( the_map.objects[i].cell.world_pos );

			the_map.objects[i].cell.order = i + 1;
			if( the_map.objects[i].category == SPECIAL_ITEMS )
				the_map.objects[i].cell.order += 5000;
			footsize = CreateDispXObject( the_map.objects[i].cell.pSprite->srect.right + 32,
										  the_map.objects[i].cell.pSprite->srect.bottom + 32,
										  &the_map.objects[i].cell, the_map.objects[i].layer );
			total_footsize += footsize;

			AddObjectToMovementLayer( &the_map.objects[i] );
		}
	}

//	DWORD time2 = timeGetTime(); 
//	TRACE( "%d unique objects loaded.\n", count );
//	TRACE( "%d seconds to load.\n", (time2-time)/1000 );

#ifdef LAYER_DEBUG
	int x,y;
	for (y=0; y<the_map.height; y++)	{
		int index = y*the_map.width;
		for (x=0; x<the_map.width; x++)	{
			char value = the_map.movement_layer[index+x];
			if (value >= 15)
				the_map.debug_layer[index+x] = '+';
		}
	}
	DisplayDebugLayer(RGB_YELLOW);
#endif
}	// LoadObjects



BOOL FileExist(const char *filename)	{
	WIN32_FIND_DATA FindFileData;
	HANDLE hSearch;
	BOOL exists = TRUE;;

	hSearch = FindFirstFile(filename, &FindFileData);
	if (hSearch == INVALID_HANDLE_VALUE)
		exists = FALSE;

	FindClose(hSearch);

	return exists;
}



//************************************************************************
//	Datafile Functions
//************************************************************************

//	Initialize an object data file for a particular terrain
//	This function sets up the ODF global variable structure and leaves the
//  ODF.fp file pointer open
BOOL OpenDataFile( char *terrain_path )
{
	char	*filename = "objects.dat";
	int		fileid = 0;

	if( ODF.fp )								// close pre-existing file
		CloseDataFile();

	SetPath( terrain_path );
	ODF.fp = fopen( filename, "rb" );			// open the file
	if( ODF.fp == NULL )
	{
		TRACE( "Unable to open object data file <%s>\n", filename );
		return FALSE;
	}
	fread( &fileid, sizeof(int), 1, ODF.fp );	// verify the file id
	if( fileid != OBJECT_FILEID )
	{
		TRACE( "Invalid file id in object data file <%s>\n", filename );
		return FALSE;
	}
	fread( ODF.palette, sizeof(RGBQUAD), 256, ODF.fp );		// read the palette
	fread( &(ODF.nObjects), sizeof(int), 1, ODF.fp );		// # of objects
	ObjectTableEntryHeaderSize = sizeof(int) + sizeof(int);

	if( ODF.nObjects > 0 )						// initialize object directory
	{
		ODF.ObjectTable = (TObjectTableEntry *)malloc(sizeof(TObjectTableEntry) * ODF.nObjects);
		if( !ODF.ObjectTable )
		{
			TRACE( "Out of Memory Error allocating object table.\n" );
			return FALSE;
		}
		ZeroMemory( ODF.ObjectTable, sizeof(TObjectTableEntry) * ODF.nObjects );
		for( int i = 0; i < ODF.nObjects; i++ )				// read directory entries
		{
			fread( &(ODF.ObjectTable[i]), ObjectTableEntryHeaderSize, 1, ODF.fp );
		}
	}

	return TRUE;
}	//	OpenDataFile()


//	This function closes the ODF data file.
//  It deletes any sprites that remain and closes the ODF.fp file pointer
void CloseDataFile( void )
{
	if( !ODF.fp )
		return;

	fclose( ODF.fp );
	ODF.fp = NULL;

	for( int i = 0; i < ODF.nObjects; i++ )
	{
		if( ODF.ObjectTable[i].pSprite )
		{
			FreeSprite( ODF.ObjectTable[i].pSprite );
			free( ODF.ObjectTable[i].pSprite );
		}
	}

	if( ODF.ObjectTable )
	{
		free( ODF.ObjectTable );
	}
	ZeroMemory( &ODF, sizeof(ODF) );
}	//	CloseDataFile()


//  This function returns the key for a described object
int GetObjectKey( int category, int number, int damagelevel )
{
	return( damagelevel + (number << 5) + (category << 15) );
}	//	GetObjectKey()


//  Return the object table index for the described object
//  Return -1 if not found
int GetObjectTableIndex( int key )
{
	int i, min, max, ikey;

	// do a binary search on the object table
	min = 0;
	max = ODF.nObjects;
	while( max > min )
	{
		i = min + ((max - min) >> 1);
		ikey = ODF.ObjectTable[i].key;
		if( ikey == key )
			return( i );
		else
		if( ikey < key )
			min = i + 1;
		else
			max = i;
	}
	return -1;
}	//	GetObjectTableIndex()


BYTE *CreateBitmapSurface( FILE *fp, int size, int width, int height )
{
	DDSURFACEDESC		ddsd;
	LPDIRECTDRAWSURFACE pdds;
	HRESULT				hr;
	#if !defined(_USESYSTEMMEMORY_)
	DWORD				dwTotalFreeMem, dwTotalAvailMem;
	#endif
	DDSCAPS				ddsc;
	int					flags;
	BYTE				*pSrc;

	pSrc = (BYTE *)malloc( size );
	if ( pSrc == NULL )
	{
		TRACE( "Out of memory in CreateBitmapSurface().\n" );
		return NULL;
	}
	if( fread( pSrc, size, 1, fp ) != 1 )
	{
		TRACE( "Error sprite from stream in CreateBitmapSurface().\n" );
		free( pSrc );
		return NULL;
	}

	// create a DirectDrawSurface for this bitmap
	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddsd.dwWidth = width;
	ddsd.dwHeight = height;
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	ddsc.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	flags = 0;

	#if !defined(_USESYSTEMMEMORY_)		// use video memory if available
	if (pDirectDraw2)
	{
		pDirectDraw2->GetAvailableVidMem(&ddsc,	&dwTotalFreeMem, &dwTotalAvailMem);
		if (dwTotalAvailMem < (DWORD)size)
			flags |= BM_SYSTEMMEMORY;
	}
	else
		flags |= BM_SYSTEMMEMORY;
	#else
	flags |= BM_SYSTEMMEMORY;
	#endif

	if( flags & BM_SYSTEMMEMORY )
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

	if( pDirectDraw->CreateSurface(&ddsd, &pdds, NULL) != DD_OK )
	{
		if ( !(flags & BM_SYSTEMMEMORY) )
		{
			TRACE( "Failed to create bitmap surface in video memory.\n" );
			flags |= BM_SYSTEMMEMORY;
			ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
			if( pDirectDraw->CreateSurface(&ddsd, &pdds, NULL) != DD_OK )
			{
				TRACE("CreateSurface failed in CreateBitmapSurface()\n");
				return 0;
			}
		}
		else
		{
			TRACE("CreateSurface failed in CreateBitmapSurface()\n");
			return 0;
		}
	}

	// do a color transform
	pdds->Restore();
	if( (hr = pdds->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)) == DD_OK )  	
	{
		if( TranslateBitmapToDD((BYTE *)ddsd.lpSurface, ddsd.lPitch, pSrc, width, height, main_trans_table) )	
		{
			pdds->Unlock(ddsd.lpSurface);

			DDSetColorKey( pdds, DDColorMatch(pdds, CLR_INVALID) );
		}
		else	
		{
			pdds->Release();
			TRACE("Error on Lock in CreateBitmapSurface()");
		}
	} 
	else	
	{
		pdds->Release();
		TRACE("Error on Lock in CreateBitmapSurface()");
	}

	free( pSrc );
	return( (BYTE *)pdds );
}


//  Create/Load a sprite from the ODF file.  Set the instance to 1
PSPRITE LoadODFSprite( int i )
{
	ASSERT( ODF.fp );								// make sure file is open
	ASSERT( ODF.ObjectTable[i].count == 0 );		// make sure sprite isn't alread loaded
	ASSERT( ODF.ObjectTable[i].pSprite == NULL );	// ditto

	ODF.ObjectTable[i].pSprite = (PSPRITE)malloc(sizeof(SPRITE));
	PSPRITE pSprite = ODF.ObjectTable[i].pSprite;	// allocate sprite memory
	if( !pSprite )
	{
		TRACE( "Error allocating memory for sprite.\n" );
		return NULL;
	}

	ODF.ObjectTable[i].count = 1;					// set instance count
	ZeroMemory( pSprite, sizeof(SPRITE) );
													// find the data in the data file
	if( fseek( ODF.fp, ODF.ObjectTable[i].offset, SEEK_SET ) != 0 )
	{
		TRACE( "Error seeking to location %d in data file.\n", ODF.ObjectTable[i].offset );
		goto errorinload;
	}

	int  key, ibuf;
	long lbuf;

	fread( &key, sizeof(int), 1, ODF.fp );			// read the key
	if( key != ODF.ObjectTable[i].key )				// validate
	{
		TRACE( "Error in validating object in data file.\n" );
		goto errorinload;
	}
	fread( &lbuf, sizeof(int), 1, ODF.fp );			// get width & height
	pSprite->srect.left = pSprite->srect.top = 0;
	pSprite->srect.right = lbuf;
	fread( &lbuf, sizeof(int), 1, ODF.fp );
	pSprite->srect.bottom = lbuf;

	fread( &ibuf, sizeof(int), 1, ODF.fp );			// get the sprite flags
	pSprite->sprite_flags = ibuf;
	if( pSprite->sprite_flags & SP_DRLE )
		pSprite->sprite_type = SPRITE_TYPE_DRLE;
	else if( pSprite->sprite_flags & SP_WRLE )
		pSprite->sprite_type = SPRITE_TYPE_WRLE;
	else if( pSprite->sprite_flags & SP_TRLE )
		pSprite->sprite_type = SPRITE_TYPE_TRLE;
	else if( pSprite->sprite_flags & SP_SRLE )
		pSprite->sprite_type = SPRITE_TYPE_SRLE;
	else if( pSprite->sprite_flags & SP_RLE )
		pSprite->sprite_type = SPRITE_TYPE_RLE;
	else
		pSprite->sprite_type = SPRITE_TYPE_BMP;

	fread( &(pSprite->hotspot), sizeof(SPOINT), 1, ODF.fp );
	fread( &(pSprite->linkspot), sizeof(SPOINT), 1, ODF.fp );

	fread( &ibuf, sizeof(int), 1, ODF.fp );			// get the size for the main graphic
	if( ibuf > 0 )
	{												// load the main graphic
		if( pSprite->sprite_type == SPRITE_TYPE_BMP )
			pSprite->pGraphic = CreateBitmapSurface( ODF.fp, ibuf, 
				pSprite->srect.right, pSprite->srect.bottom );
		else
			pSprite->pGraphic = LoadRLE256Stream( ODF.fp, ibuf, (ESpriteType)pSprite->sprite_type );
	}
	
	fread( &ibuf, sizeof(int), 1, ODF.fp );			// get the shadow size
	if( ibuf > 0 )
	{
		pSprite->pShadow = (BYTE *)malloc( ibuf );
		if( !pSprite->pShadow )
		{
			TRACE( "Error allocating memory for graphic object.\n" );
			goto errorinload;
		}
		fread( pSprite->pShadow, ibuf, 1, ODF.fp );	// load the shadow graphic
	}

	fread( &ibuf, sizeof(int), 1, ODF.fp );			// get the mask size
	if( ibuf > 0 )
	{
		pSprite->pMask = (BYTE *)malloc( ibuf );
		if( !pSprite->pMask )
		{
			TRACE( "Error allocating memory for graphic object.\n" );
			goto errorinload;
		}
		fread( pSprite->pMask, ibuf, 1, ODF.fp );	// load the mask graphic
	}

	fread( &(pSprite->maskRect), sizeof(RECT), 1, ODF.fp );		// load the rect
	pSprite->ODFKey = i + 1;

	return pSprite;									// successful exit

errorinload:
	ODF.ObjectTable[i].count = 0;					// free up everything before exit
	if( pSprite->pGraphic )
		free( pSprite->pGraphic );
	if( pSprite->pShadow )
		free( pSprite->pShadow );
	if( pSprite->pMask )
		free( pSprite->pMask );
	free( ODF.ObjectTable[i].pSprite );				// due to error
	ODF.ObjectTable[i].pSprite = NULL;
	return NULL;
}	//	LoadODFSprite()


//	Get the sprite described by the parameters (category, number & damage level)
//	Return NULL if unable to obtain the described sprite
PSPRITE AcquireObjectSprite( int cat, int num, int dam )
{
	//	Verify that the ODF is open
	if( !ODF.fp )
		return NULL;

	int key, i;

	key = GetObjectKey( cat, num, dam );
	i = GetObjectTableIndex( key );				// find the object in the directory
	if( i < 0 )
		return NULL;
	if( ODF.ObjectTable[i].count > 0 )			// return the sprite if already loaded
	{
		ODF.ObjectTable[i].count++;				// increment the instance count
		return( ODF.ObjectTable[i].pSprite );
	}

	if( !LoadODFSprite( i ) )					// load the sprite from the data file
		return NULL;
	
	return( ODF.ObjectTable[i].pSprite );
}	//  AcquireObjectSprite();


//  Release the sprite and decrement the instance count
void ReleaseObjectSprite( PSPRITE pSprite )
{
	int i;
	
	if( !pSprite )
		return;
	i = pSprite->ODFKey;
	if( i < 1 || i > ODF.nObjects )
		return;
	i--;
	ASSERT( ODF.ObjectTable[i].count > 0 );

	ODF.ObjectTable[i].count--;
	if( ODF.ObjectTable[i].count <= 0 )
	{
		FreeSprite( ODF.ObjectTable[i].pSprite );
		free( ODF.ObjectTable[i].pSprite );
		ODF.ObjectTable[i].pSprite = 0;
	}

	return;										// for now, don't release anything
}


//  Recover any lost surfaces in ODF
void RecoverODFSurfaces( void )
{
	int i;
	PSPRITE pSprite;
	LPDIRECTDRAWSURFACE	dds;

	if( !_LOAD_FROM_DATAFILE )
		return;

	for( i = 0; i < ODF.nObjects; i++ )
	{
		if( ODF.ObjectTable[i].count <= 0 )
			continue;
		if( !(ODF.ObjectTable[i].pSprite) )
			continue;
		pSprite = ODF.ObjectTable[i].pSprite;

		if( pSprite->sprite_type != SPRITE_TYPE_BMP ) 
			continue;
		if( !(pSprite->pGraphic) )
			continue;

		dds = (LPDIRECTDRAWSURFACE)(pSprite->pGraphic);	
		if( (dds) && (dds->IsLost() == DDERR_SURFACELOST) )
		{
			HRESULT dderr;
			int  key, ibuf;
			long lbuf;
			SPOINT tmppt;
		
			ASSERT( ODF.fp );								// make sure file is open

			dderr = dds->Release();
			pSprite->pGraphic = NULL;

			if( fseek( ODF.fp, ODF.ObjectTable[i].offset, SEEK_SET ) != 0 )
			{
				TRACE( "Error seeking to location %d in data file.\n", ODF.ObjectTable[i].offset );
				goto errorinload;
			}

			fread( &key, sizeof(int), 1, ODF.fp );			// read the key
			if( key != ODF.ObjectTable[i].key )				// validate
			{
				TRACE( "Error in validating object in data file.\n" );
				goto errorinload;
			}

			fread( &lbuf, sizeof(int), 1, ODF.fp );			// get width & height
			fread( &lbuf, sizeof(int), 1, ODF.fp );
			fread( &ibuf, sizeof(int), 1, ODF.fp );			// get the sprite flags
			fread( &tmppt, sizeof(SPOINT), 1, ODF.fp );
			fread( &tmppt, sizeof(SPOINT), 1, ODF.fp );

			fread( &ibuf, sizeof(int), 1, ODF.fp );			// get the size for the main graphic
			if( ibuf > 0 )
				pSprite->pGraphic = CreateBitmapSurface( ODF.fp, ibuf, 
										pSprite->srect.right, pSprite->srect.bottom );
	
			pSprite->ODFKey = i + 1;
			continue;

errorinload:
			ODF.ObjectTable[i].count = 0;					// free up everything before exit
			if( pSprite->pGraphic )
				free( pSprite->pGraphic );
			if( pSprite->pShadow )
				free( pSprite->pShadow );
			if( pSprite->pMask )
				free( pSprite->pMask );
			free( ODF.ObjectTable[i].pSprite );				// due to error
			ODF.ObjectTable[i].pSprite = NULL;
		}
	}
}	//	RecoverODFSurfaces
