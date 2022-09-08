/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File:   util.h
 *  Content:    miscellaneous utilities include file
 *
 *
 ***************************************************************************/

#include <windows.h>

#define GUIDSTR_MAX 38
#define GUID_STRING_SIZE 64

//------------------------------------------------------------------------
//	CHUNK I/O routines
//------------------------------------------------------------------------
#define CHUNK_READ_BUFFER(pFile, pBuffer, howmany) Read((void *)(pBuffer), 1, (howmany), (pFile), __FILE__, __LINE__)
#define CHUNK_READ_LONG(pFile, pLong) Read((void *)(pLong), 1, sizeof(long),  (pFile), __FILE__, __LINE__)
#define CHUNK_READ_SHORT(pFile, pShort) Read((void *)(pShort), 1, sizeof(short), (pFile), __FILE__, __LINE__)
#define CHUNK_READ_BYTE(pFile, pChar) Read((void *)(pChar), 1, sizeof(char), (pFile), __FILE__, __LINE__)

#define	CHUNK_WRITE_BUFFER(pFile, pBuffer, howMany ) fwrite( (const void *)(pBuffer), (howMany), 1, (pFile) )
#define	CHUNK_WRITE_LONG(pFile, pLong ) fwrite( (const void *)(pLong), sizeof(long), 1, (pFile) )
#define	CHUNK_WRITE_SHORT(pFile, pShort ) fwrite( (const void *)(pShort), sizeof(short), 1, (pFile) )
#define	CHUNK_WRITE_BYTE(pFile, pChar ) fwrite( (const void *)(pChar), sizeof(char), 1, (pFile) )

// CHUNK IDS
//      STAT =         T A T S		Stats chunk block
#define STAT_ID		0x54415453
//      MISN =         N S I M		Mission save chunk block
#define MISN_ID		0x4E53494D
//      PLAY =         Y A L P		Player save chunk block
#define PLAY_ID		0x59414C50
//      DPLY =         Y L P D		Deployment save chunk block
#define DPLY_ID		0x594C5044
//      VTXT =         T X T V		Voice Stream Text chunk block
#define VTXT_ID		0x54585456
//      CPYR =         R Y P C		CopyRight Chunk block
#define CPYR_ID		0x52595043
//      EODF =         F D O E		End Of Data File chunk block
#define EODF_ID		0x46444F45
//      STRC =         C R T S		STAT MissionID Record block
#define STRC_ID		0x43525453
//		OBJS =		   S J B O		Objects record block
#define OBJS_ID		0x534A424F

extern	BOOL ChunkFind( FILE* pDataFile, ULONG nChunkID );
extern	BOOL ChunkFindNext( FILE* pDataFile, ULONG nChunkID );
extern	BOOL ChunkRead( FILE* pDataFile, void* pDataBuffer, ULONG* nDataSize );
extern	void ChunkName( ULONG nChunkID );

//------------------------------------------------------------------------
//	REG KEY routines
//------------------------------------------------------------------------
LONG RegSet(  HKEY hRegKey, LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize );
LONG RegSetA( HKEY hRegKey, LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize );
LONG RegGet( HKEY hRegKey, LPCTSTR lptszName, LPBYTE lpData, LPDWORD lpdwDataSize );

//------------------------------------------------------------------------
//	Miscellaneous routines
//------------------------------------------------------------------------
int     StringFromGUID(GUID *lpguid, LPWSTR lpsz);
BOOL    IsEqualGuid(GUID *lpguid1, LPGUID lpguid2);
int     GetDigit(LPSTR lpstr);
void    ConvertField(LPBYTE lpByte,LPSTR * ppStr,int iFieldSize,BOOL fRightToLeft);
HRESULT GUIDFromString(LPWSTR lpWStr, GUID * pGuid);
int     WideToAnsi(LPSTR lpStr,LPWSTR lpWStr,int cchStr);
int     AnsiToWide(LPWSTR lpWStr,LPSTR lpStr,int cchWStr);
int     randInt( int low, int high );
double  randDouble( double low, double high );
long	GetDistance( SPOINT* pPointA, SPOINT* pPointB );

//========================================================================
//						EOF
//========================================================================
