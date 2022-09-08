/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: util.cpp $
//
//	DESCRIPTION:	lobby routines
//
//	AUTHOR:			MicroSoft
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/util.cpp 11    4/02/98 6:29p Phu $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/util.cpp $
//  
//  11    4/02/98 6:29p Phu
//  typecast to avoid warnings
//  
//  10    12/09/97 12:12p Phu
//  
//  9     12/01/97 6:25p Nrobinso
//  fix oef reading
//  
//  8     11/20/97 11:55a Aburgess
//  corrected ChunkFindNext EODF error
//  
//  7     11/17/97 10:09a Aburgess
//  rework of CHUNK interface
//  
//  6     11/16/97 4:26p Aburgess
//  findNext reads from current location in case request is in middle of
//  chunk
//  
//  5     11/11/97 3:00p Aburgess
//  corrected chunk read skipping
//  
//  4     11/07/97 10:36a Aburgess
//  added generic Windows Registry access routines and Chunk read/write
//  routines
//  
//  2     8/06/97 9:46a Nrobinso
//  TadDistance now GetDistance and moved to utils
//  
//  1     7/03/97 5:19p Nrobinso
//  
//  2     4/27/97 3:42p Dmaynard
//  Change to precompiled headers
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "fileio.h"
//#include "util.h"

/*
 * Globals
 */
static const BYTE GuidMap[] = { 3, 2, 1, 0, '-', 5, 4, '-', 7, 6, '-',
                                8, 9, '-', 10, 11, 12, 13, 14, 15 };
static const WCHAR wszDigits[] = L"0123456789ABCDEF";


/*
 * StringFromGUID
 * 
 * Converts a GUID into a wide string
 */
int StringFromGUID(LPGUID lpguid, LPWSTR lpwsz)
{
    int i;

    const BYTE * pBytes = (const BYTE *) lpguid;

    *lpwsz++ = L'{';

    for (i = 0; i < sizeof(GuidMap); i++)
    {
        if (GuidMap[i] == '-')
        {
            *lpwsz++ = L'-';
        }
        else
        {
            *lpwsz++ = wszDigits[ (pBytes[GuidMap[i]] & 0xF0) >> 4 ];
            *lpwsz++ = wszDigits[ (pBytes[GuidMap[i]] & 0x0F) ];
        }
    }
    *lpwsz++ = L'}';
    *lpwsz   = L'\0';

    return GUIDSTR_MAX;
}

/*
 * IsEqualGuid
 *
 * Determines if two guids are equal
 */
BOOL  IsEqualGuid(GUID *lpguid1, GUID *lpguid2)
{
   return (
      ((PLONG) lpguid1)[0] == ((PLONG) lpguid2)[0] &&
      ((PLONG) lpguid1)[1] == ((PLONG) lpguid2)[1] &&
      ((PLONG) lpguid1)[2] == ((PLONG) lpguid2)[2] &&
      ((PLONG) lpguid1)[3] == ((PLONG) lpguid2)[3]);
}


// convert a hex char to an int - used by str to guid conversion
// we wrote our own, since the ole one is slow, and requires ole32.dll
// we use ansi strings here, since guids won't get internationalized
int GetDigit(LPSTR lpstr)
{
    char ch = *lpstr;
    
    if (ch >= '0' && ch <= '9')
        return(ch - '0');
    if (ch >= 'a' && ch <= 'f')
        return(ch - 'a' + 10);
    if (ch >= 'A' && ch <= 'F')
        return(ch - 'A' + 10);
    return(0);
}
// walk the string, writing pairs of bytes into the byte stream (guid)
// we need to write the bytes into the byte stream from right to left
// or left to right as indicated by fRightToLeft
void ConvertField(LPBYTE lpByte,LPSTR * ppStr,int iFieldSize,BOOL fRightToLeft)
{
    int i;

    for (i=0;i<iFieldSize ;i++ )
    {
        // don't barf on the field separators
        if ('-' == **ppStr) (*ppStr)++; 
        if (fRightToLeft == TRUE)
        {
            // work from right to left within the byte stream
            *(lpByte + iFieldSize - (i+1)) = 16*GetDigit(*ppStr) + GetDigit((*ppStr)+1);
        } 
        else 
        {
            // work from  left to right within the byte stream
            *(lpByte + i) = 16*GetDigit(*ppStr) + GetDigit((*ppStr)+1);
        }
        *ppStr+=2; // get next two digit pair
    }
} // ConvertField


// convert the passed in string to a real GUID
// walk the guid, setting each byte in the guid to the two digit hex pair in the
// passed string
HRESULT GUIDFromString(LPWSTR lpWStr, GUID * pGuid)
{
    BYTE * lpByte; // byte index into guid
    int iFieldSize; // size of current field we're converting
    // since its a guid, we can do a "brute force" conversion
    char lpTemp[GUID_STRING_SIZE];
    char *lpStr = lpTemp;

    WideToAnsi(lpStr,lpWStr,GUID_STRING_SIZE);
    
    // make sure we have a {xxxx-...} type guid
    if ('{' !=  *lpStr) return E_FAIL;
    lpStr++;
    
    lpByte = (BYTE *)pGuid;
    // data 1
    iFieldSize = sizeof(unsigned long);
    ConvertField(lpByte,&lpStr,iFieldSize,TRUE);
    lpByte += iFieldSize;

    // data 2
    iFieldSize = sizeof(unsigned short);
    ConvertField(lpByte,&lpStr,iFieldSize,TRUE);
    lpByte += iFieldSize;

    // data 3
    iFieldSize = sizeof(unsigned short);
    ConvertField(lpByte,&lpStr,iFieldSize,TRUE);
    lpByte += iFieldSize;

    // data 4
    iFieldSize = 8*sizeof(unsigned char);
    ConvertField(lpByte,&lpStr,iFieldSize,FALSE);
    lpByte += iFieldSize;

    // make sure we ended in the right place
    if ('}' != *lpStr) 
    {
        memset(pGuid,0,sizeof(GUID));
        return E_FAIL;
    }

    return S_OK;
}// GUIDFromString

/*
 ** WideToAnsi
 *
 *  CALLED BY:  everywhere
 *
 *  PARAMETERS: lpStr - destination string
 *              lpWStr - string to convert
 *              cchStr - size of dest buffer
 *
 *  DESCRIPTION:
 *              converts unicode lpWStr to ansi lpStr.
 *              fills in unconvertable chars w/ DPLAY_DEFAULT_CHAR "-"
 *              
 *
 *  RETURNS:  if cchStr is 0, returns the size required to hold the string
 *              otherwise, returns the number of chars converted
 *
 */
int WideToAnsi(LPSTR lpStr,LPWSTR lpWStr,int cchStr)
{

    int rval;
    BOOL bDefault;

    // use the default code page (CP_ACP)
    // -1 indicates WStr must be null terminated
    rval = WideCharToMultiByte(CP_ACP,0,lpWStr,-1,lpStr,cchStr,"-",&bDefault);

    return rval;

} // WideToAnsi

/*
 ** AnsiToWide
 *
 *  CALLED BY: everywhere
 *
 *  PARAMETERS: lpWStr - dest string
 *              lpStr  - string to convert
 *              cchWstr - size of dest buffer
 *
 *  DESCRIPTION: converts Ansi lpStr to Unicode lpWstr
 *
 *
 *  RETURNS:  if cchStr is 0, returns the size required to hold the string
 *              otherwise, returns the number of chars converted
 *
 */
int AnsiToWide(LPWSTR lpWStr,LPSTR lpStr,int cchWStr)
{
    int rval;

    rval =  MultiByteToWideChar(CP_ACP,0,lpStr,-1,lpWStr,cchWStr);

    return rval;
}  // AnsiToWide


/* 
 * randInt
 *
 * returns a random integer in the specified range
 */
int randInt( int low, int high )
{
    int range = high - low;
    int num = rand() % range;
    return( num + low );
}

/*
 * randDouble
 *
 * returns a random double in the specified range
 */
double randDouble( double low, double high )
{
    double range = high - low;
    double num = range * (double)rand()/(double)RAND_MAX;
    return( num + low );
}

///========================================================================
//	Function:		GetDistance()
//
//	Description:
//		return the distance between two points.
//		This algorithm has an error potential of up to 12%
//
//	Input:			pPointA		position of point A
//					pPointB		position of point B
//
//	Ouput:			nDistance	distance from point A to point B
//
///========================================================================

long	GetDistance( SPOINT* pPointA, SPOINT* pPointB )
{
	long	deltaX;
	long	deltaY;
	long	nMin;
	long	nDistance = 0;

	// validate the paramters
	ASSERT( pPointA );
	ASSERT( pPointB );

	// get the deltas
	deltaX       = (pPointB->x - pPointA->x);
	deltaY       = (pPointB->y - pPointA->y);
	if ( deltaX < 0 ) deltaX = -deltaX;
	if ( deltaY < 0 ) deltaY = -deltaY;
	if ( deltaX > deltaY )
		nMin = deltaY;
	else
		nMin = deltaX;
	nDistance = (deltaX + deltaY - (nMin>>1));

	// give em the distance
	return( nDistance );
}


//------------------------------------------------------------------------
//	REG KEY routines
//------------------------------------------------------------------------

/*
 * RegSet
 *
 * Stores a data value in the registry
 */
LONG RegSet(  HKEY hRegKey, LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize )
{
	LONG	errorCode;
#ifdef UNICODE
    dwSize *= 2; // calc number of bytes
#endif
	errorCode = RegSetValueEx(hRegKey, lptszName, 0, REG_SZ, lpData, dwSize);
	if ( errorCode != ERROR_SUCCESS )
		TRACE( "ERROR: failed on data write to system registry [%s:%d]\n", __FILE__, __LINE__ );

    return( errorCode ); 
}

/*
 * RegSetA
 *
 * Stores data as an ascii string in the registry
 */
LONG RegSetA( HKEY hRegKey, LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize )
{
	LONG	errorCode = RegSetValueEx(hRegKey, lptszName, 0, REG_SZ, lpData, dwSize);
	if ( errorCode != ERROR_SUCCESS )
		TRACE( "ERROR: failed on ascii write to system registry [%s:%d]\n", __FILE__, __LINE__ );

    return( errorCode );
}

/*
 * RegGet
 *
 * Queries a value from the registry
 */
LONG RegGet( HKEY hRegKey, LPCTSTR lptszName, LPBYTE lpData, LPDWORD lpdwDataSize )
{
    DWORD	dwType;
	LONG	errorCode = RegQueryValueEx(hRegKey, lptszName, NULL, &dwType, lpData, lpdwDataSize);
	if ( errorCode != ERROR_SUCCESS )
		TRACE( "ERROR: failed on read from system registry [%s:%d]\n", __FILE__, __LINE__ );
    
	return( errorCode );
}

//------------------------------------------------------------------------
//	CHUNK I/O routines
//------------------------------------------------------------------------

/*
 * ChunkFind
 *
 * find the first occurrence of a chunk in a file
 */
BOOL ChunkFind( FILE* pDataFile, ULONG nChunkID )
{
	long	nSize;
	long	chunkIDName;
	fpos_t	pos;
	BOOL	error;

	BOOL	bFound      = FALSE;
	BOOL	bDone       = FALSE;

	// rewind the file pointer to the begining of the file
	pos = 0;
	error = fsetpos( pDataFile, &pos );
	if ( error )
	{
		// report an error
		TRACE("ERROR: (%d) failed to reset file to position 0 [%s:%d]\n", error, __FILE__, __LINE__ );
		ASSERT(0);
	}

	while ( !bFound && !bDone )
	{
		if (CHUNK_READ_LONG(pDataFile, &chunkIDName))	{

#ifdef CHUNK_DEBUG
			ChunkName( chunkIDName );
#endif

			if ((ULONG)chunkIDName == nChunkID)
				bFound = TRUE;
			else
			{
				// skip over the chunk
				CHUNK_READ_LONG(pDataFile, &nSize);
	#ifdef CHUNK_DEBUG
				TRACE( "chunk size: %ld ", nSize );
	#endif

				// now we're gonna play a game with file i/o.
				// first acquire the current position in the file
				// and then simply add the chunk data size to
				// the file pointer and reset it.
				if ( fgetpos( pDataFile, &pos ) )
				{
					// report an error
					TRACE("ERROR: failed to get file to position [%s:%d]\n", __FILE__, __LINE__ );
					ASSERT(0);
				}
				pos += nSize;
				if ( fsetpos( pDataFile, &pos ) )
				{
					// report an error
					TRACE("ERROR: failed to reset file to position %ld [%s:%d]\n", pos, __FILE__, __LINE__ );
					ASSERT(0);
				}
			}
			TRACE( "\n" );
		}
		else
			bDone = TRUE;

		if (feof( pDataFile ) )
			bDone = TRUE;
	}


#ifdef CHUNK_DEBUG
	TRACE( "Found: %s ", ((bFound)?"TRUE":"FALSE") );
#endif
	return( bFound );
}

/*
 * ChunkFindNext
 *
 * find the next occurrence of a chunk in a file
 */
BOOL ChunkFindNext( FILE* pDataFile, ULONG nChunkID )
{
	long	chunkIDName;
	BOOL	bFound      = FALSE;
	BOOL	bEOF        = FALSE;
	BOOL	bError      = TRUE;

	// read from the current position in the file
	while ( !bFound && !bEOF )
	{
		bEOF = !CHUNK_READ_LONG(pDataFile, &chunkIDName);
		if ( chunkIDName == EODF_ID )
			bEOF = TRUE;
		if ( !bEOF )
		{
#ifdef CHUNK_DEBUG
			ChunkName( chunkIDName );
#endif
			if ((ULONG)chunkIDName == nChunkID)
				bFound = TRUE;
			else
			{
				fpos_t	pos;
				long	nSize;

				// skip over the chunk
				CHUNK_READ_LONG(pDataFile, &nSize);
#ifdef CHUNK_DEBUG
				TRACE( "chunk size: %ld\n", nSize );
#endif

				// now we're gonna play a game with file i/o.
				// first acquire the current position in the file
				// and then simply add the chunk data size to
				// the file pointer and reset it.
				if ( fgetpos( pDataFile, &pos ) )
				{
					// report an error
					TRACE("ERROR: failed to get file to position [%s:%d]\n", __FILE__, __LINE__ );
					ASSERT(0);
				}
				pos += nSize;
				if ( fsetpos( pDataFile, &pos ) )
				{
					// report an error
					TRACE("ERROR: failed to reset file to position %ld [%s:%d]\n", pos, __FILE__, __LINE__ );
					ASSERT(0);
				}
			}
			if ( feof( pDataFile ) != 0 )
				bEOF = TRUE;
		}
	}

#ifdef CHUNK_DEBUG
	TRACE( "Found: %s ", ((bFound)?"TRUE":"FALSE") );
#endif
	return( bFound );
}

/*
 * ChunkRead
 *
 * read a chunk of data
 */
BOOL ChunkRead( FILE* pDataFile, void* pDataBuffer, ULONG* nDataSize )
{
	ULONG	nSize;
	BOOL	bFound      = FALSE;
	BOOL	bError      = TRUE;

	// read in the size field
	CHUNK_READ_LONG(pDataFile, &nSize);
#ifdef CHUNK_DEBUG
	TRACE( "chunk size: %ld ", nSize );
#endif

	ASSERT(nSize);

	// read in the data
	if ( nSize < *nDataSize )
		*nDataSize = nSize;
	CHUNK_READ_BUFFER( pDataFile, pDataBuffer, *nDataSize );

	// success
	bError = FALSE;

	return( bError );
}

/*
 * ChunkName
 *
 * output a chunk ID Name
 */
void ChunkName( ULONG nChunkID )
{
	switch( nChunkID )
	{
	case STAT_ID:	// Stats chunk block
		TRACE( "STAT: " );
		break;
	case MISN_ID:	// Mission save chunk block
		TRACE( "MISN: " );
		break;
	case DPLY_ID:	// Deployment save chunk block
		TRACE( "DPLY: " );
		break;
	case VTXT_ID:	// Voice Stream Text chunk block
		TRACE( "VTXT: " );
		break;
	case CPYR_ID:	// CopyRight Chunk block
		TRACE( "CPYR: " );
		break;
	case EODF_ID:	// End Of Data File chunk block
		TRACE( "EODF: " );
		break;
	default:
		TRACE( "0x%8X: ", nChunkID );
		break;
	}
}

//========================================================================
//								EOF
//========================================================================
