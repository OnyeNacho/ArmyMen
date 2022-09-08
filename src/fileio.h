#include "stdafx.h"

#include "dd.h"

#include "sprite.h"


#ifndef _FILEIO_H_
#define _FILEIO_H_

//************************************************************************
//	Macros
//************************************************************************

#define READ_BUFFER(pBuffer, howmany) Read((void *)pBuffer, 1, howmany, pFile, __FILE__, __LINE__)
#define READ_LONG(pLong) Read((void *)pLong, 1, sizeof(long),  pFile, __FILE__, __LINE__)
#define READ_SHORT(pShort) Read((void *)pShort, 1, sizeof(short), pFile, __FILE__, __LINE__)
#define READ_BYTE(pChar) Read((void *)pChar, 1, sizeof(char), pFile, __FILE__, __LINE__)


//************************************************************************
//	Externals
//************************************************************************
extern BOOL	_LOAD_FROM_DATAFILE;
extern BYTE main_trans_table[256];
extern BYTE fixed_trans_table[256];


//************************************************************************
//	Structures
//************************************************************************


//************************************************************************
//	Functions
//************************************************************************

BOOL  Read( void *buffer, size_t size, size_t count, FILE *stream, char *file, int line );
short GetShort( char *pBuffer, int offset );
long  GetLong( char *pBuffer, int offset );
WORD  readWord( FILE * fp );
DWORD readDword( FILE * fp );

DWORD BitmapLoad( char *szName, LOADBITMAP *plbitmap );
BOOL  DDReadBitmap(FILE* pFile, LOADBITMAP *plbitmap);

void LoadObjects(char *obj_dir);

void LoadSpriteShadow( PSPRITE pSprite, char *name );
DWORD LoadSpriteMask( PSPRITE pSprite, char *name );
void LoadSpriteRect( PSPRITE pSprite, char *name );
void *SpriteShadowLoad( char *szName );
void LoadShadowAsSprite( PSPRITE pSprite, char *name, BYTE *ShadeTable );

BOOL FileExist(const char *filename);

// data file functions
PSPRITE AcquireObjectSprite( int cat, int num, int dam );
void ReleaseObjectSprite( PSPRITE pSprite );
void CloseDataFile( void );
BOOL OpenDataFile( char *terrain_path );
void RecoverODFSurfaces( void );

#endif
