//	CSpriteCatalog.cpp

#include "stdafx.h"
#include "CSpriteCatalog.h"
//#include "ddutil.h"

#ifdef ANIMEDITORDOC_VERSION
#include "AnimEditorDoc.h"
#include "AnimEditor.h"
#include "Dibpal.h"
#endif

/////////////////////////////////////////////////////////////////////////////
//	Constructor/Destructor
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CSpriteCatalog, CObject, 1)

CSpriteCatalog::CSpriteCatalog()
{
	//	Used for Serialization only.
	m_pbmArray			= NULL;
//	pRLEPixels			= NULL;
//	iRLEPixelCount		= 0;
#ifndef ANIMEDITORDOC_VERSION
	lpDDSStrip			= NULL;
	lpDDPalStrip		= NULL;
#endif
//	m_ppalStrip			= NULL;

//	iDarkTestxxx = 0;
//	iDarkTestDeltaxxx = 1;
}

#ifdef ANIMEDITORDOC_VERSION
CSpriteCatalog::CSpriteCatalog( CAnimEditorDoc* pDocToCopy, BOOL bRLE )
{
	csName	= pDocToCopy->csName;

	iSeqs	= pDocToCopy->lstSeqs.GetCount();

	arSeqs.SetSize( iSeqs );
	POSITION posSequence = pDocToCopy->lstSeqs.GetHeadPosition();
	CSequence* pSeq;
	int iCount = 0;
	while( posSequence )
	{
		pSeq = pDocToCopy->lstSeqs.GetNext( posSequence );
		ASSERT( pSeq );
		CSpriteSequence* pSpSeq = new CSpriteSequence( pDocToCopy, this, pSeq, bRLE );
		arSeqs.SetAt( iCount++, pSpSeq );
	}

	m_pbmArray			= NULL;
//	m_ppalStrip			= NULL;

#ifndef ANIMEDITORDOC_VERSION
	lpDDSStrip			= NULL;
	lpDDPalStrip		= NULL;
#endif

//	pRLEPixels			= NULL;
//	iRLEPixelCount		= 0;
}
#endif

CSpriteCatalog::~CSpriteCatalog()
{
	//	Delete created SpriteSequences.
	for( int i = 0; i <= arSeqs.GetUpperBound(); i++ )
		delete arSeqs[ i ];

#ifndef	ANIMEDITORDOC_VERSION
	if( lpDDSStrip )
	{
		lpDDSStrip->Release();
		lpDDSStrip = NULL;
	}
#endif

	if( m_pbmArray )
		delete [] m_pbmArray;
//	if( m_ppalStrip )
//		delete m_ppalStrip;
//	if( pRLEPixels )
//		delete [] pRLEPixels;
}

//-----------------------------------------------------------------------------------------------------------------
void CSpriteCatalog::Serialize( CArchive& ar )
{
	//	[ My member var bSerializeRLE has been set ahead of time if this I'm to save RLE data. ]
	// if loading, the file knows whether it is RLE or not

	int iAXRVersion;

	if( ar.IsStoring() )
	{
		iAXRVersion = 2;
		ar << iAXRVersion;
		ar << csName << iSeqs;
//		ar << iRLEPixelCount;
	}
	else
	{
		ar >> iAXRVersion;
		ar >> csName >> iSeqs;
//		ar >> iRLEPixelCount;
		arSeqs.SetSize( iSeqs );
	}

#ifdef ANIMEDITORDOC_VERSION
	for( int i = 0; i <= arSeqs.GetUpperBound(); i++ )
		arSeqs[i]->bSerializeRLE = bSerializeRLE;
#endif

	arSeqs.Serialize( ar );

#ifdef ANIMEDITORDOC_VERSION
	if( ar.IsStoring() )
	{
		//	Append BMP to file.
		if( bSerializeRLE )
		{
			char szHeader[] = "AXR:";
			ar.Write( szHeader, 4 );
			int iVersion = 1;
			ar.Write( &iVersion, sizeof( iVersion ) );

//			ar.Write( pRLEPixels, iRLEPixelCount );
		}
		else	{
			char szHeader[] = "AXC:";
			ar.Write( szHeader, 4 );
			int iVersion = 1;
			ar.Write( &iVersion, sizeof( iVersion ) );

//			VERIFY( WriteBMP( ar, pbmStrip, ppalStrip, iStripWidth, iStripHeight ) );
		}

		VERIFY( WriteBMPs( ar ) );
	}
#endif

#ifndef ANIMEDITORDOC_VERSION
	// note this is now wrong (NAR)
	if( !ar.IsStoring() )
	{
		char szHeader[4];
		ar.Read( szHeader, 4 );
		int iVersion;
		ar.Read( &iVersion, sizeof( iVersion ) );

		if( bSerializeRLE )
		{
			//	Read in RLE data from the rest of the file.
			pRLEPixels = new BYTE[iRLEPixelCount];
			ar.Read( pRLEPixels, iRLEPixelCount );
			//	Set RLE data origin values in each sequence.
//			for( int i = 0; i <= arSeqs.GetUpperBound(); i++ )
//				arSeqs[i]->Set_arRLEOrigins( pRLEPixels );
		}
		else
		{
			//	Read in BMP information from the rest of the file.
//			CFile* pfile = ar.GetFile();
//			VERIFY( ReadBMP( pfile, &pbmStrip, &ppalStrip, iStripWidth, iStripHeight ) );
			//	My lpDDObject and lpDDPalette vars have been set by the CSpriteManager that called the serialize.
			VERIFY( ReadBMP( ar, lpDDObject, lpDDPalette ) );
		}
	}
#endif
}


#ifdef ANIMEDITORDOC_VERSION
//-----------------------------------------------------------------------------------------------------------------
BOOL CSpriteCatalog::WriteBMPs( CArchive& ar )
{
	//	Appends one CPalette and an array of CBitmaps to an archive being written to, in BMP format.
	ASSERT( ar.IsStoring() );

	// write out the number of bitmaps
	ar << m_iNumBitmaps;

	//	Write the single file header, suitably altered
	BITMAPFILEHEADER bmpFileHeader;
	bmpFileHeader.bfType		= 0x4142;			//	"BA" (Bitmap array)
	bmpFileHeader.bfSize		= 0;				//	Not used.
	bmpFileHeader.bfOffBits		= sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + 4 * 256;	//	Assumes palette uses all 256 colors.
	ar.Write( &bmpFileHeader, sizeof( BITMAPFILEHEADER ) );

	//	Write the single bitmapinfo header.
	BITMAPINFOHEADER bmpInfoHeader;
	bmpInfoHeader.biSize			= sizeof( BITMAPINFOHEADER );
	bmpInfoHeader.biWidth			= 0;
	bmpInfoHeader.biHeight			= 0;
	bmpInfoHeader.biPlanes			= 1;			//	Always 1.
	bmpInfoHeader.biBitCount		= 8;			//	This function is for 8 bpp images only.
	bmpInfoHeader.biCompression		= BI_RGB;		//	Not compressed.
	bmpInfoHeader.biSizeImage		= 0;
	bmpInfoHeader.biXPelsPerMeter	= 0;
	bmpInfoHeader.biYPelsPerMeter	= 0;
	bmpInfoHeader.biClrUsed			= 256;			//	Assumes palette uses all 256 colors.
	bmpInfoHeader.biClrImportant	= 256;			//	"They're all important."
	ar.Write( &bmpInfoHeader, sizeof( BITMAPINFOHEADER ) );

	//	Write the palette, which is the input palette ("palette.bmp")
	CDIBPalette* ppal = m_pbmArray[0]->GetOriginalPalette();
	ar.Write( ppal->ColorTable, 256 * 4 );

	BYTE *map = new BYTE[256];
	m_pbmArray[0]->MakeMappingToOriginal(map);

	BYTE *copy = new BYTE[m_iMaxSize];
	BYTE* pRLEPixels = NULL;	
	if (bSerializeRLE)	{
		pRLEPixels = new BYTE[m_iMaxSize * 5];	
	}

	// write the pixels for each bitmap
	for (int bm=0; bm<m_iNumBitmaps; bm++)	{
		CDIBitmap *pbm = m_pbmArray[bm];

		int iHeight = pbm->GetHeight();
		int iWidth = pbm->GetWidth();
		int	iWidthByFour = pbm->GetLineSize(); // ( iWidth + 3 ) & ~3;
		int iSize = pbm->GetImageSize();

		BYTE* pBytes = pbm->GetBits();

	// translate the bitmap to correspond to the common logical palette
		for( int i = 0; i < iSize; i++ )	{
			copy[i] = map[pBytes[i]];
		}

		if (bSerializeRLE)	{
			iSize = MemoryWriteBMP_RLE( pRLEPixels, copy, iWidthByFour, iWidth, iHeight, theApp.indexTransparent );
		}

	//	Write the bitmapinfo header, with specifics for this bitmap
		bmpInfoHeader.biWidth			= iWidth;
		bmpInfoHeader.biHeight			= iHeight;
		bmpInfoHeader.biSizeImage		= iSize;
		bmpInfoHeader.biXPelsPerMeter	= pbm->GetHotspotX();
		bmpInfoHeader.biYPelsPerMeter	= pbm->GetHotspotY();
		ar.Write( &bmpInfoHeader, sizeof( BITMAPINFOHEADER ) );		

		if (bSerializeRLE)	{
			ar.Write( pRLEPixels, iSize );
		}
		else	{
			ar.Write( copy, iSize );
		}

		ar.Write( &(pbm->m_shadowsize), sizeof(LONG) );
		if( pbm->m_shadowsize && pbm->m_pShadow )
			ar.Write( pbm->m_pShadow, pbm->m_shadowsize );
	}

	if (pRLEPixels);	
		delete [] pRLEPixels;

	delete [] copy;
	delete [] map;

	return TRUE;
}
#endif

//-----------------------------------------------------------------------------------------------------------------
/*
BOOL CSpriteCatalog::WriteBMP( CArchive& ar, CBitmap* pBMP, CPalette* pPal, int iWidth, int iHeight )
{
	//	Appends a CBitmap and CPalette to an archive being written to, in BMP format.

	if( !ar.IsStoring() )
		return FALSE;

	//	Write the file header.
	BITMAPFILEHEADER bmpFileHeader;
	bmpFileHeader.bfType		= 0x4D42;			//	"BM"
	bmpFileHeader.bfSize		= 0;				//	Not used.
	bmpFileHeader.bfOffBits		= sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + 4 * 256;	//	Assumes palette uses all 256 colors.
//	pfileBMP->Write( &bmpFileHeader, sizeof( BITMAPFILEHEADER ) );
	ar.Write( &bmpFileHeader, sizeof( BITMAPFILEHEADER ) );

	//	Write the bitmapinfo header.
	BITMAPINFOHEADER bmpInfoHeader;
	bmpInfoHeader.biSize			= sizeof( BITMAPINFOHEADER );
	bmpInfoHeader.biWidth			= iWidth;
	bmpInfoHeader.biHeight			= iHeight;
	bmpInfoHeader.biPlanes			= 1;			//	Always 1.
	bmpInfoHeader.biBitCount		= 8;			//	This function is for 8 bpp images only.
	bmpInfoHeader.biCompression		= BI_RGB;		//	Not compressed.
	bmpInfoHeader.biSizeImage		= 0;			//	Doesn't have to be set.
	bmpInfoHeader.biXPelsPerMeter	= 0;
	bmpInfoHeader.biYPelsPerMeter	= 0;
	bmpInfoHeader.biClrUsed			= 256;			//	Assumes palette uses all 256 colors.
	bmpInfoHeader.biClrImportant	= 0;			//	"They're all important."
	ar.Write( &bmpInfoHeader, sizeof( BITMAPINFOHEADER ) );

	//	Write the palette.
	ASSERT( pPal->GetEntryCount() == 256 );				//	Verify palette uses 256 colors.
	PALETTEENTRY PalEntries[ 256 ];											//	Assumes palette uses all 256 colors.
	VERIFY( pPal->GetPaletteEntries( 0, 256, PalEntries ) == 256 );			//	Assumes palette uses all 256 colors.
	//	Turn bloody PALETTEENTRYs into bloody RGBQUADs.
	BYTE q;
	for( int i = 0; i < 256; i++ )
	{
		q = PalEntries[ i ].peRed;
		PalEntries[ i ].peRed	= PalEntries[ i ].peBlue;
		PalEntries[ i ].peBlue	= q;
	}
	ar.Write( &PalEntries[0], 256 * 4 );								//	Assumes palette uses all 256 colors.

	//	Write the pixels.
	int	iWidthByFour = ( iWidth + 3 ) & ~3;
	int iWidthByTwo = ( iWidth + 1 ) & ~1;
	DWORD dwBytes = iWidthByTwo * iHeight;
	BYTE* pBytes = new BYTE[ dwBytes ];
	DWORD dwRead = pBMP->GetBitmapBits( dwBytes, pBytes );
	ASSERT( dwRead == dwBytes );

//	BYTE* pBytes = new BYTE[ iWidthByFour * iHeight ];
//	DWORD dwLines = GetDIBits( pDC->GetSafeHdc(), (HBITMAP)pBMP, 0, iHeight, pBytes, m_pbiInfo, DIB_PAL_COLORS );

//	//	Can't just do a ' ar.Write( pBytes, dwBytes ); ' because the bloody lines go bottom to top in a BMP.
//	for( int y = iHeight - 1; y >= 0; y-- )
//	{
//		ar.Write( &pBytes[ y * iWidthActual ], iWidthActual );
//	}
//	//	Store image upside down, for convenience loading and saving.
//	ar.Write( pBytes, dwBytes );
	//	Can't just do a ' ar.Write( pBytes, dwBytes ); ' because the bloody lines may be WORD divisible in memory, not DWORD.
	BYTE* pPadding = new BYTE[ 2 ];
	::ZeroMemory( pPadding, 2 );
	//for( int y = 0; y < iHeight; y++ )
	for( int y = iHeight - 1; y >= 0; y-- )
	{
		ar.Write( &pBytes[ y * iWidthByTwo ], iWidthByTwo );
		if( iWidthByFour != iWidthByTwo )	//	Pad end of line to divisible by 4.
			ar.Write( pPadding, 2 );
	}
	delete [] pBytes;
	delete pPadding;

	return TRUE;

	//	#define bloody "Poorly implemented by Microsoft."
}
*/


/*
//-----------------------------------------------------------------------------------------------------------------
BOOL CSpriteCatalog::WriteBMP_RLE( CArchive& ar, CBitmap* pBMP, int iWidth, int iHeight, BYTE qTransparentIndex )
{
	//	Not longer used. See MemoryWriteBMP_RLE(), below. xxx

	//	Appends a bitmap to an archive being written to, without a palette, run length encoded.
	if( !ar.IsStoring() )
		return FALSE;

	//	Header.
	char szHeader[] = "AXC";
	ar.Write( &szHeader[0], 3 );
	//	Width and height of image, in pixels (int).
	ar.Write( &iWidth, sizeof( int ) );
	ar.Write( &iHeight, sizeof( int ) );

	//	Write the pixels. The "pitch" of a line is simply the length in pixels.
	//	RLE format:
	//	{
	//		(BYTE)		# of transparent pixels (never larger than 254)
	//		(BYTE)		# of non-transparent pixels, n (n never larger than 254)
	//		(n BYTES)	non-transparent pixel values
	//	}
	//	Repeat, until value of -1 in the first field indicates new line.

	int iWidthByTwo = ( iWidth + 1 ) & ~1;
	DWORD dwBytes = iWidthByTwo * iHeight;
	BYTE* pBytes = new BYTE[ dwBytes ];
	BYTE* pqPixel;
	BYTE* pqLineEnd;
	BYTE* pqPixelStart;
	DWORD dwRead = pBMP->GetBitmapBits( dwBytes, pBytes );		//	Aligns on WORD boundary.
	ASSERT( dwRead == dwBytes );
	BYTE qPixels;
	for( int y = iHeight - 1; y >= 0; y-- )
	{
		pqPixel = &pBytes[ y * iWidthByTwo ];
		pqLineEnd = pqPixel + iWidth;	//	one beyond line end
		while( TRUE )
		{
			//	Count forward till we hit a non-transparent pixel.
			qPixels = 0;
			while( *pqPixel == qTransparentIndex && qPixels < 254 && pqPixel != pqLineEnd )
			{
				pqPixel++;
				qPixels++;
			}
			//	Write # of transparent pixels.
			ar.Write( &qPixels, 1 );
			//	Save starting location of non-transparent pixel set.
			pqPixelStart = pqPixel;
			//	Count forward till we hit a transparent pixel.
			qPixels = 0;
			while( *pqPixel != qTransparentIndex && qPixels < 254 && pqPixel != pqLineEnd )
			{
				pqPixel++;
				qPixels++;
			}
			//	Write # of non-transparent pixels.
			ar.Write( &qPixels, 1 );
			if( qPixels )
			{
				//	Write non-transparent pixel values.
				ar.Write( pqPixelStart, qPixels );
			}
			if( pqPixel == pqLineEnd )
			{
				BYTE qEndOfLine = 0xFF;
				ar.Write( &qEndOfLine, 1 );
				break;
			}
		}
	}

	delete [] pBytes;

	return TRUE;
}
*/

//-----------------------------------------------------------------
// One-to-One BITMAPINFO Struct ( Used below, in ReadBMP() )
//-----------------------------------------------------------------
struct BITMAPINFO_1TO1_DUPED
{
  BITMAPINFOHEADER  bmiHeader;
  WORD              bmiColors[256];

                    BITMAPINFO_1TO1_DUPED(const BITMAPINFOHEADER &bmih);
                    operator BITMAPINFO*()
                      { return (BITMAPINFO*)this; }
};

BITMAPINFO_1TO1_DUPED::BITMAPINFO_1TO1_DUPED(const BITMAPINFOHEADER
  &bmihToCopy)
{
  ::CopyMemory(&bmiHeader, &bmihToCopy, sizeof(BITMAPINFOHEADER));
  for (int i = 0; i < 256; i++)
    bmiColors[i] = i;
}

//-----------------------------------------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION
BOOL CSpriteCatalog::ReadBMP( CArchive& ar, LPDIRECTDRAW lpDDObject, LPDIRECTDRAWPALETTE lpDDPalette )
{
	//	Reads BMP info from a file, already opened and sitting in the right place.
	//	Writes data directly onto a direct draw surface that is created here.
	//	Sets lpDDSStrip, ppalStrip, lpDDPalStrip, iStripWidth, iStripHeight.
	//	Returns TRUE if successful.

	if( ar.IsStoring() )
		return FALSE;

	//	Read the file header.
	BITMAPFILEHEADER bmpFileHeader;
	DWORD dwBytesRead = ar.Read( &bmpFileHeader, sizeof( BITMAPFILEHEADER ) );
	if( dwBytesRead != sizeof( BITMAPFILEHEADER ) || bmpFileHeader.bfType != 0x4D42 )
		return FALSE;

	//	Read the bitmapinfo header.
	PBITMAPINFO pbmpInfo = (PBITMAPINFO)( new BITMAPINFO_256 );
	dwBytesRead = ar.Read( pbmpInfo, sizeof( BITMAPINFOHEADER ) );
	if( dwBytesRead != sizeof( BITMAPINFOHEADER ) )
		return FALSE;
	
	//	Verify 8 bpp (256 color).
	ASSERT( pbmpInfo->bmiHeader.biBitCount == 8 );
	//	Verify no compression.
	ASSERT( pbmpInfo->bmiHeader.biCompression == BI_RGB );

	int nColors = pbmpInfo->bmiHeader.biClrUsed;
	if( nColors == 0 )
		nColors = pbmpInfo->bmiHeader.biClrUsed = 256;

	//	dword align.
	long LineSize = ( pbmpInfo->bmiHeader.biWidth + 3 ) & ~3;

	if( pbmpInfo->bmiHeader.biSizeImage == 0 )
	{
		long h = pbmpInfo->bmiHeader.biHeight;
		if( h < 0L )
			h = -h;
		pbmpInfo->bmiHeader.biSizeImage = LineSize * h;
	}
	::ZeroMemory( pbmpInfo->bmiColors, 256 * sizeof( RGBQUAD ) );

//	//	Skip (forward or backward) to the color info, if necessary.
//	if( pbmpInfo->bmiHeader.biSize != sizeof( BITMAPINFOHEADER ) )
//		pfileBMP->Seek( pbmpInfo->bmiHeader.biSize - sizeof( BITMAPINFOHEADER ), CFile::current );
	VERIFY( pbmpInfo->bmiHeader.biSize == sizeof( BITMAPINFOHEADER ) );

	iStripWidth		= pbmpInfo->bmiHeader.biWidth;
	iStripHeight	= pbmpInfo->bmiHeader.biHeight;

	//	Read the color info.
	ar.Read( pbmpInfo->bmiColors, nColors * sizeof( RGBQUAD ) );

	//	Create a new CPalette.
	PLOGPALETTE pLogPal = (PLOGPALETTE)( new BYTE[ sizeof( LOGPALETTE ) + nColors * sizeof( PALETTEENTRY ) ] );
	ASSERT( pLogPal );
	pLogPal->palVersion		= 0x300;
	pLogPal->palNumEntries	= (WORD)nColors;
	
	const RGBQUAD* pRGB = pbmpInfo->bmiColors;
	for( int i = 0; i < nColors; i++ )
	{
		pLogPal->palPalEntry[i].peRed	= pRGB[i].rgbRed;
		pLogPal->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
		pLogPal->palPalEntry[i].peBlue	= pRGB[i].rgbBlue;
		pLogPal->palPalEntry[i].peFlags	= 0;
	}
	ppalStrip = new CPalette;
	VERIFY( ppalStrip->CreatePalette( pLogPal ) );
	delete [] pLogPal;

	//	[xxx don't even load palette at all anymore?]

	//	Create directdraw surface.
	HRESULT ddrval;
	DDSURFACEDESC ddsd;
	::memset( &ddsd, 0, sizeof( ddsd ) );

    ddsd.dwSize			= sizeof( ddsd );
    ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_CKSRCBLT;		// | DDSD_PIXELFORMAT;
	ddsd.dwWidth		= iStripWidth;
	ddsd.dwHeight		= iStripHeight;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue	= 255;			//	Set transparent color. (these are palette indexes) xxx (should be 0)
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue	= 255;			//	 "
//	ddsd.ddpfPixelFormat.dwSize			= sizeof( ddsd.ddpfPixelFormat );
//	ddsd.ddpfPixelFormat.dwFlags		= DDPF_RGB | DDPF_PALETTEINDEXED8;
//	ddsd.ddpfPixelFormat.dwRGBBitCount	= 8;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;	
	//	Note: Not specifying 'system memory' resulted in 0x80070057 hresult on createsurface. xxx

	ddrval = lpDDObject->CreateSurface( &ddsd, &lpDDSStrip, NULL );
	ASSERT( ddrval == DD_OK );

	//	Lock the surface, in preparation for writing to it.
	CRect rcLock( 0, 0, iStripWidth, iStripHeight );
	DDSURFACEDESC ddsdFilled;
	ddsdFilled.dwSize = sizeof( ddsdFilled );
	ddrval = lpDDSStrip->Lock( &rcLock, &ddsdFilled, DDLOCK_WAIT, NULL );
	ASSERT( ddrval == DD_OK );

	//	Read the pixel info into the surface. (Lines are upside down in a BMP.)
	//	Go line by line, as the pitch of the surface might be different than the length of a line in the BMP.

	LONG lDestPitch	= ddsdFilled.lPitch;
	LONG lSrcPitch	= LineSize;

	BYTE* pDest = (BYTE*)ddsdFilled.lpSurface;		//	Beginning of data.
	pDest += ( iStripHeight - 1 ) * lDestPitch;		//	Beginning of last line of data.
	
	for( int y = 0; y < iStripHeight; y++ )
	{
		ar.Read( pDest, lSrcPitch );
		pDest -= lDestPitch;
	}
	ddrval = lpDDSStrip->Unlock( ddsdFilled.lpSurface );
	ASSERT( ddrval == DD_OK );

//	ddrval = lpDDSStrip->SetPalette( lpDDPalette );			//	If no palette is set, I think it uses the palette of the primary surface.
//	ASSERT( ddrval == DD_OK );

//	//	Create palette for surface, lpDDPalStrip. (xxx?)
//	PALETTEENTRY* pPalEntries = new PALETTEENTRY[ ppalStrip->GetEntryCount() ];
//	ppalStrip->GetPaletteEntries( 0, ppalStrip->GetEntryCount(), pPalEntries );
//	ddrval = lpDDObject->CreatePalette( DDPCAPS_8BIT | DDPCAPS_ALLOW256, pPalEntries, &lpDDPalStrip, NULL );
//	ASSERT( ddrval == DD_OK );
//	delete [] pPalEntries;
//	ddrval = lpDDSStrip->SetPalette( lpDDPalStrip );
//	ASSERT( ddrval == DD_OK );

	
/*
	//	Read the pixel info. (Lines are inverted, but we stored in upside down.)
//	BYTE* pPixel = new BYTE[ pbmpInfo->bmiHeader.biSizeImage ];
//	pfileBMP->Seek( bmpFileHeader.bfOffBits, CFile::begin );
//	[ This Seek is not possible now that CArchive is being used. It *shouldn't* strictly be necessary. ]

	//	Rationale for the following:
	//	Using CreateDIBSection, it seems I can use DWORD aligned bytes directly in the creation of a bitmap.
	//	CreateBitmap would appear to be expecting WORD aligned kruft, for some *&$%&@!ing historical reason.
	//	And the bytes from a BMP are DWORD divisible.
	//	Problem is, CreateDIBSection gives me an HBITMAP, and there's no way to make a CBitmap and then 
	//	attach it to an existing HBITMAP (more $#&*). So I'll blit it from the first into the second...

	PBYTE pPixel;

    //	Create a BITMAPINFO struct with a one-to-one color mapping.
    BITMAPINFO_1TO1_DUPED bi1To1( pbmpInfo->bmiHeader );
	//	Get an HBITMAP using CreateDIBSection and copy image bits.
	pDCSample->SelectPalette( pPalNew, FALSE );
    HBITMAP hbmpRead = ::CreateDIBSection( pDCSample->GetSafeHdc(), bi1To1, DIB_PAL_COLORS, (PVOID*)&pPixel, 0, 0 );

	//	Read data into the dib.
	ar.Read( pPixel, pbmpInfo->bmiHeader.biSizeImage );

	//xxx temp. Read number of transparent pixels.
	BYTE qTransIndex = pPixel[0];
	int iCount = 0;
	for( int ii = 0; ii < pbmpInfo->bmiHeader.biSizeImage; ii++ )
	{
		if( pPixel[ii] == qTransIndex )
			iCount++;
	}
	CString csTrace;
	csTrace.Format( "Trans. pixels: %f percent\n", (float)( ( (float)iCount / (float)pbmpInfo->bmiHeader.biSizeImage ) * 100 ) );
	TRACE( csTrace );
	
	//	Create a new CBitmap.
	CBitmap* pBMPNew = new CBitmap;
	VERIFY( pBMPNew->CreateBitmap( pbmpInfo->bmiHeader.biWidth, pbmpInfo->bmiHeader.biHeight, 1, 8, NULL ) );

	//	Copy bits from one to the other. Of course, without a pointer to the data in the CBitmap's bitmap, I'm forced
	//	to do the following... [sigh]
	CDC dcSource;
	CDC dcTarget;

	VERIFY( dcSource.CreateCompatibleDC( NULL ) ); //pDCSample );
	HBITMAP hbmpSourceOrig = (HBITMAP)::SelectObject( dcSource.GetSafeHdc(), hbmpRead );
	CPalette* ppalSourceOld = dcSource.SelectPalette( pPalNew, FALSE );
	ASSERT( ppalSourceOld );
	int iNumColorsChanged = dcSource.RealizePalette();
	ASSERT( iNumColorsChanged == 0 ); // no colors should be getting remapped here --xxxAJM

	VERIFY( dcTarget.CreateCompatibleDC( &dcSource ) ); //pDCSample );
	CBitmap* pbmpTargetOrig = dcTarget.SelectObject( pBMPNew );
	CPalette* ppalTargetOld = dcTarget.SelectPalette( pPalNew, FALSE );
	ASSERT( ppalTargetOld );

	iNumColorsChanged = dcTarget.RealizePalette();
	ASSERT( iNumColorsChanged == 0 ); // no colors should be getting remapped here --xxxAJM
//	dcSource.RealizePalette();
//	dcTarget.RealizePalette();

	dcTarget.BitBlt( 0, 0, pbmpInfo->bmiHeader.biWidth, pbmpInfo->bmiHeader.biHeight, &dcSource, 0, 0, SRCCOPY );

	BYTE* pBytes = new BYTE[ ( pbmpInfo->bmiHeader.biWidth + 3 & ~3 ) * pbmpInfo->bmiHeader.biHeight ];
//	pbmpInfo->bmiHeader.biBitCount = 0;
	HBITMAP hbmpNew = (HBITMAP)(*pBMPNew);
	DWORD dwLines = ::GetDIBits( dcTarget.GetSafeHdc(), hbmpNew, 0, pbmpInfo->bmiHeader.biHeight, (void*)pBytes, pbmpInfo, DIB_PAL_COLORS );
	delete [] pBytes;

	VERIFY( dcTarget.SelectObject( pbmpTargetOrig ) == pBMPNew );
	VERIFY( ::SelectObject( dcSource.GetSafeHdc(), hbmpSourceOrig ) == hbmpRead );

	//	Set return values.
	*ppBMP	= pBMPNew;
	*ppPal	= pPalNew;
	iStripWidth		= pbmpInfo->bmiHeader.biWidth;
	iStripHeight	= pbmpInfo->bmiHeader.biHeight;

*/

	delete (BITMAPINFO_256*)pbmpInfo;

	return TRUE;
}
#endif
//-----------------------------------------------------------------------------------------------------------------
/*
#ifndef ANIMEDITORDOC_VERSION

void CSpriteCatalog::PrepareSurface( LPDIRECTDRAW lpDDObject, LPDIRECTDRAWSURFACE lpDDSample )
{
	HRESULT ddrval;

	//	Called after Serializing in, to set up the DD surface the strip bitmap will reside in during the game.
	DDSURFACEDESC ddsd;
	::memset( &ddsd, 0, sizeof( ddsd ) );
    ddsd.dwSize			= sizeof( ddsd );
    ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_CKSRCBLT;		// | DDSD_PIXELFORMAT;
	ddsd.dwWidth		= iStripWidth;
	ddsd.dwHeight		= iStripHeight;
	ddsd.ddckCKSrcBlt.dwColorSpaceLowValue	= 0;			//	Set transparent color. (xxx not sure if these are palette indexes or rgbs)
	ddsd.ddckCKSrcBlt.dwColorSpaceHighValue	= 0;			//	 "
//	ddsd.ddpfPixelFormat.dwSize			= sizeof( ddsd.ddpfPixelFormat );
//	ddsd.ddpfPixelFormat.dwFlags		= DDPF_RGB | DDPF_PALETTEINDEXED8;
//	ddsd.ddpfPixelFormat.dwRGBBitCount	= 8;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;	
	//	Note: Not specifying 'system memory' resulted in 0x80070057 hresult on createsurface. xxx

	ddrval = lpDDObject->CreateSurface( &ddsd, &lpDDSStrip, NULL );
	ASSERT( ddrval == DD_OK );

	//	xxx Note: 0x80070057 HRESULT is 'invalid argument'.

	//	xxx
	//	Prep the ddutil hpalApp global, before calling DDCopyBitmap, as I may be the first to do this.
	//	MakeIdentityHPalette( gpActiveGame->GetArenaDoc()->GetTileSet()->GetHPalette() );
	//	Copy the bitmap into the surface.
	//ddrval = ::DDCopyBitmap( lpDDSStrip, (HBITMAP)(*pbmStrip), 0, 0, 0, 0 );
	//ASSERT( ddrval == DD_OK );

	//	Copy my bitmap onto the surface...

	//	Create palette for surface. (xxx?)
	PALETTEENTRY* pPalEntries = new PALETTEENTRY[ ppalStrip->GetEntryCount() ];
	ppalStrip->GetPaletteEntries( 0, ppalStrip->GetEntryCount(), pPalEntries );
	LPDIRECTDRAWPALETTE lpDDPalette;
	VERIFY( lpDDObject->CreatePalette( DDPCAPS_8BIT | DDPCAPS_ALLOW256, pPalEntries, &lpDDPalette, NULL ) == DD_OK );
	delete [] pPalEntries;
	VERIFY( lpDDSStrip->SetPalette( lpDDPalette ) == DD_OK );


	//	Set up dc to blit from.
	CDC dcTemp;
	VERIFY( dcTemp.CreateCompatibleDC( NULL ) );
	VERIFY( dcTemp.SelectPalette( ppalStrip, FALSE ) );
	CBitmap* pbmOrig = dcTemp.SelectObject( pbmStrip );
	ASSERT( pbmOrig );
	//	Set up dc representing dd surface, to blit to.
	HDC hdcSurface;
	VERIFY( lpDDSStrip->GetDC( &hdcSurface ) == DD_OK );

	VERIFY( ::BitBlt( hdcSurface, 0, 0, iStripWidth, iStripHeight, dcTemp.GetSafeHdc(), 0, 0, SRCCOPY ) );

	//	Unsetup dcs.
	VERIFY( lpDDSStrip->ReleaseDC( hdcSurface ) == DD_OK );
	VERIFY( dcTemp.SelectObject( pbmOrig ) );


/*
	//	Copy the bytes directly onto the surface...

	//	Get a dc to use in GetDIBits.
	HDC hdcSample;
	ddrval = lpDDSample->GetDC( &hdcSample );		//xxx lpDDSample parameter passed for this only
	ASSERT( ddrval == DD_OK );

	//	Get bytes out of the bitmap...
	BITMAPINFO bmi;
	bmi.bmiHeader.biSize			= sizeof( bmi.bmiHeader );
	bmi.bmiHeader.biWidth			= iStripWidth;
	bmi.bmiHeader.biHeight			= iStripHeight;
	bmi.bmiHeader.biPlanes			= 1;
	bmi.bmiHeader.biBitCount		= 8;
	bmi.bmiHeader.biCompression		= BI_RGB;
	bmi.bmiHeader.biSizeImage		= ( iStripWidth + 3 & ~3 ) * iStripHeight;
	bmi.bmiHeader.biXPelsPerMeter	= 0;
	bmi.bmiHeader.biYPelsPerMeter	= 0;
	bmi.bmiHeader.biClrUsed			= 256;			//	Assumes palette uses all 256 colors.
	bmi.bmiHeader.biClrImportant	= 0;			//	"They're all important."
	BYTE* pBytes = new BYTE[ iStripWidth + 3 & ~3 ];
//	CDC dcTemp;
//	VERIFY( dcTemp.CreateCompatibleDC( NULL ) );
//	VERIFY( dcTemp.SelectPalette( ppalStrip, FALSE ) );
//	CBitmap bmTemp;
//	bmTemp.CreateBitmap( 1, 1, 1, 8, NULL );
//	CBitmap* pbmOrig = dcTemp.SelectObject( &bmTemp );
//	ASSERT( pbmOrig );
//	DWORD dwLines = ::GetDIBits( dcTemp.GetSafeHdc(), (HBITMAP)pbmStrip, 0, iStripHeight, pBytes, &bmi, DIB_PAL_COLORS );
//	ASSERT( dwLines == iStripHeight );
//	VERIFY( dcTemp.SelectObject( pbmOrig ) );
	
	DWORD dwLines = ::GetDIBits( hdcSample, (HBITMAP)pbmStrip, 0, iStripHeight, pBytes, &bmi, DIB_PAL_COLORS );
	//	[xxx this is failing. Tried many dc's. Possibly bmi needs color table initialized?]
	ASSERT( dwLines == iStripHeight );

	ddrval = lpDDSample->ReleaseDC( hdcSample );
	ASSERT( ddrval == DD_OK );

	//	Write bytes to the surface...
	CRect rcLock( 0, 0, iStripWidth, iStripHeight );
	DDSURFACEDESC ddsdFilled;
	ddrval = lpDDSStrip->Lock( &rcLock, &ddsdFilled, DDLOCK_WAIT, NULL );
	VERIFY( ddrval == DD_OK );

	LONG lDestPitch = ddsdFilled.lPitch;
	LONG lSrcPitch = -( iStripWidth + 3 & ~3 );

	BYTE* pSrc;
	BYTE* pDest = (BYTE*)ddsdFilled.lpSurface;
	
	//	Go line by line, upside down.
	for( int y = iStripHeight - 1; y >= 0; y-- )
	{
		pSrc = pBytes + lSrcPitch * y;
		::CopyMemory( pDest, pSrc, iStripWidth );
		pDest += lDestPitch;
	}
	lpDDSStrip->Unlock( ddsdFilled.lpSurface );



}

#endif
*/
//-----------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION

void CSpriteCatalog::DrawSprite( LPDIRECTDRAWSURFACE lpDDSTarget, int iDestX, int iDestY, CSpriteSequence* pSeq, int iFrame, BOOL bHorizFlip, int iLightLevel )
{
	//	iLightLevel is a light_levels[] array palette. If == -1 or LIGHT_LEVEL_NORMAL, regular blit is done instead of XBlt.

	if( iLightLevel == -1 )
		iLightLevel = LIGHT_LEVEL_NORMAL;

	HRESULT ddrval;

	if( !theApp.bFadeLOS )
		iLightLevel = LIGHT_LEVEL_NORMAL;
	else
		ASSERT( iLightLevel <= LIGHT_LEVEL_NORMAL );
		
	if( lpDDSTarget->IsLost() != DD_OK )
	{
		ddrval = lpDDSTarget->Restore();
		ASSERT( ddrval = DD_OK );
	}

	//	Get size of surface.
	DDSURFACEDESC ddsd;
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    lpDDSTarget->GetSurfaceDesc( &ddsd );

	CPoint* pptOffset	= pSeq->arOffsets[iFrame];
	CPoint* pptSize		= pSeq->arSizes[iFrame];
	CRect rcTarget;

	if( bHorizFlip )
		rcTarget.SetRect( iDestX + pptOffset->x - pptSize->x, iDestY - pptOffset->y, 
							iDestX + pptOffset->x, iDestY - pptOffset->y + pptSize->y );
	else
		rcTarget.SetRect( iDestX - pptOffset->x, iDestY - pptOffset->y,
							iDestX - pptOffset->x + pptSize->x, iDestY - pptOffset->y + pptSize->y );

	CRect rcSource;
	CPoint* pptOrigin;		//	Used for non-RLE only.

/*
	if( bSerializeRLE )
		rcSource.SetRect( 0, 0, pptSize->x, pptSize->y );
	else
	{
		pptOrigin	= pSeq->arOrigins[iFrame];
		rcSource.SetRect( pptOrigin->x, pptOrigin->y, pptOrigin->x + pptSize->x,  pptOrigin->y + pptSize->y );
	}
*/

	BOOL bClipped = FALSE;
	if( rcTarget.left < 0L )
	{
		rcSource.left += -rcTarget.left;
		rcTarget.left = 0;
		bClipped = TRUE;
	}
	if( rcTarget.right > (LONG)ddsd.dwWidth )
	{
		rcSource.right -= rcTarget.right - ddsd.dwWidth;
		rcTarget.right = ddsd.dwWidth;
		bClipped = TRUE;
	}
	if( rcTarget.top < 0L )
	{
		rcSource.top += -rcTarget.top;
		rcTarget.top = 0;
		bClipped = TRUE;
	}
	if( rcTarget.bottom > (LONG)ddsd.dwHeight )
	{
		rcSource.bottom -= rcTarget.bottom - ddsd.dwHeight;
		rcTarget.bottom = ddsd.dwHeight;
		bClipped = TRUE;
	}

	if( rcTarget.left < rcTarget.right && rcTarget.top < rcTarget.bottom )		//	( Else nothing is visible. )
	{
		if( bSerializeRLE )				//	Set when the thing was serialized in. (xxx was going to be just a temp. flag...?)
		{
			DDSURFACEDESC ddsdTarget;
			ddsdTarget.dwSize = sizeof( DDSURFACEDESC );

			ddrval = lpDDSTarget->Lock( &rcTarget, &ddsdTarget, DDLOCK_WRITEONLY | DDLOCK_WAIT, NULL );	//	DDLOCK_WAIT may delay things xxx (apparently not?)
			ASSERT( ddrval == DD_OK );
			
			if( !bClipped )
			{
				if( !bHorizFlip )
				{
/*
//					DWORD timeStart = timeGetTime();
//					for( int xxx = 0; xxx < 100000; xxx++ )
						RLEFastBlt( ddsdTarget.lpSurface, ddsdTarget.lPitch, pSeq->arRLEOrigins[iFrame], rcSource.bottom );

//						iDarkTestxxx += iDarkTestDeltaxxx;
//						if( iDarkTestxxx == NUM_PALETTES-1 ) { iDarkTestxxx = NUM_PALETTES - 3; iDarkTestDeltaxxx = -1; }
//						if( iDarkTestxxx == -1 ) { iDarkTestxxx = 1; iDarkTestDeltaxxx = 1; }
//						RLEXBlt( ddsdTarget.lpSurface, ddsdTarget.lPitch, pSeq->arRLEOrigins[iFrame], rcSource.bottom, iDarkTestxxx );

//						RLEInvisBlt( ddsdTarget.lpSurface, ddsdTarget.lPitch, pSeq->arRLEOrigins[iFrame], rcSource.bottom );

//						RLEBiXBlt( ddsdTarget.lpSurface, ddsdTarget.lPitch, pSeq->arRLEOrigins[iFrame], rcSource.bottom, &_blend75 );

//					TRACE( "\nTime:%i\n", timeGetTime() - timeStart );
*/
					if( iLightLevel == LIGHT_LEVEL_NORMAL )
						RLEFastBlt( ddsdTarget.lpSurface, ddsdTarget.lPitch, pSeq->arRLEOrigins[iFrame], rcSource.bottom );
					else
						RLEXBlt( ddsdTarget.lpSurface, ddsdTarget.lPitch, pSeq->arRLEOrigins[iFrame], rcSource.bottom, iLightLevel );

				}
				else
				{
/*
//					iDarkTestxxx += iDarkTestDeltaxxx;
//					if( iDarkTestxxx == NUM_PALETTES-1 ) { iDarkTestxxx = NUM_PALETTES - 3; iDarkTestDeltaxxx = -1; }
//					if( iDarkTestxxx == -1 ) { iDarkTestxxx = 1; iDarkTestDeltaxxx = 1; }
//					VERIFY( RLEXBltHFlipped( ddsdTarget.lpSurface, ddsdTarget.lPitch, 
//												pSeq->arRLEOrigins[iFrame], rcSource.bottom, rcSource.right, iDarkTestxxx ) );

					VERIFY( RLEFastBltHFlipped( ddsdTarget.lpSurface, ddsdTarget.lPitch, 
												pSeq->arRLEOrigins[iFrame], rcSource.bottom, rcSource.right ) );

//					RLEBiXBltHFlipped( ddsdTarget.lpSurface, ddsdTarget.lPitch, 
//										pSeq->arRLEOrigins[iFrame], rcSource.bottom, rcSource.right, &_blend25 );
*/
					if( iLightLevel == LIGHT_LEVEL_NORMAL )
						RLEFastBltHFlipped( ddsdTarget.lpSurface, ddsdTarget.lPitch, 
											pSeq->arRLEOrigins[iFrame], rcSource.bottom, rcSource.right );
					else
						RLEXBltHFlipped( ddsdTarget.lpSurface, ddsdTarget.lPitch, 
											pSeq->arRLEOrigins[iFrame], rcSource.bottom, rcSource.right, iLightLevel );

				}
			}
			else
				VERIFY( RLEFastBltClipped( ddsdTarget.lpSurface, ddsdTarget.lPitch, pSeq->arRLEOrigins[iFrame], &rcSource ) );
			
			ddrval = lpDDSTarget->Unlock( ddsdTarget.lpSurface );
			ASSERT( ddrval == DD_OK );
		}
		else	//	not RLE...
		{
	//		//	Set palette for target surface.
	//		ddrval = lpDDSTarget->SetPalette( lpDDPalStrip ) == DD_OK;
	//		ASSERT( ddrval == DD_OK );
			//	Force realize of palette in primary surface...
	//		ddrval = lpDDSPrimary->SetPalette( lpDDPalette );
			if( bHorizFlip )
			{
				DDBLTFX fx;
				fx.dwSize	= sizeof( fx );
				fx.dwDDFX	= DDBLTFX_MIRRORLEFTRIGHT;
				
				ddrval = lpDDSTarget->Blt( &rcTarget, lpDDSStrip, &rcSource, DDBLT_WAIT | DDBLT_KEYSRC | DDBLT_DDFX, &fx );
				ASSERT( ddrval == DD_OK );
			}
			else
			{
				//ddrval = lpDDSTarget->BltFast( iDestX - pptOffset->x, iDestY - pptOffset->y, lpDDSStrip, &rcSource, DDBLTFAST_DESTCOLORKEY );
				ddrval = lpDDSTarget->Blt( &rcTarget, lpDDSStrip, &rcSource, DDBLT_WAIT | DDBLT_KEYSRC, NULL );
				ASSERT( ddrval == DD_OK );
			}

	/*		//	xxx Checking byte values on target surface...
			DDSURFACEDESC ddsdFilled;
			ddsdFilled.dwSize = sizeof( ddsdFilled );
			ddrval = lpDDSTarget->Lock( &rcTarget, &ddsdFilled, DDLOCK_WAIT, NULL );
			ASSERT( ddrval == DD_OK );
			//	xxx What happens if we copy the memory directly...?
			LONG lPitchDest = ddsdFilled.lPitch;
			DDSURFACEDESC ddsdSrc;
			ddsdSrc.dwSize = sizeof( ddsdSrc );
			ddrval = lpDDSStrip->Lock( &rcSource, &ddsdSrc, DDLOCK_WAIT, NULL );
			ASSERT( ddrval == DD_OK );
			LONG lPitchSrc	= ddsdSrc.lPitch;
			BYTE* pDest = (BYTE*)ddsdFilled.lpSurface;
			BYTE* pSrc	= (BYTE*)ddsdSrc.lpSurface;
			for( int i = 0; i < rcSource.Height(); i++ )
			{
				::CopyMemory( pDest, pSrc, rcSource.Width() );
				pDest	+= lPitchDest;
				pSrc	+= lPitchSrc;
			}

			ddrval = lpDDSStrip->Unlock( ddsdSrc.lpSurface );
			ddrval = lpDDSTarget->Unlock( ddsdFilled.lpSurface );
			ASSERT( ddrval == DD_OK );
	*/
		}
	}
}

#endif

//-----------------------------------------------------------------------------------------------------------------
#if 0
void CSpriteCatalog::Initialize( CBitmap* pBMP, CPalette* pPal, int iStripWidth, int iStripHeight )
{	
	ASSERT( pbmStrip == NULL );
	ASSERT( ppalStrip == NULL );

	//	The bitmap *is* the one passed.
	pbmStrip = pBMP;

	//	The palette is a *copy* of the one passed...
	DWORD dwNumColors;
	VERIFY( pPal->GetObject( sizeof( dwNumColors ), &dwNumColors ) );
//	ASSERT( dwNumColors == 256 );	//xxx

	PLOGPALETTE pLogPal = (PLOGPALETTE)new BYTE[sizeof(LOGPALETTE) + dwNumColors * sizeof(PALETTEENTRY)];
	ASSERT( pLogPal != NULL );
	pLogPal->palVersion		= 0x300;
	pLogPal->palNumEntries	= (WORD)dwNumColors;
	
	pPal->GetPaletteEntries( 0, dwNumColors, pLogPal->palPalEntry );

	ppalStrip = new CPalette;
	VERIFY( ppalStrip->CreatePalette( pLogPal ) );
	delete [] pLogPal;

	this->iStripWidth	= iStripWidth;
	this->iStripHeight	= iStripHeight;
}
#endif


#ifdef ANIMEDITORDOC_VERSION
void CSpriteCatalog::Initialize( CAnimEditorDoc* pDoc )
{
	ASSERT( m_pbmArray == NULL );
//	ASSERT( m_ppalStrip == NULL );
	
	//	Determine number of cels that are to be included, and the maximum size
	int			iNumBitmaps = 0;
	int			iMaxSize = 0;
	CCel*		pCel;
	POSITION	posInList = pDoc->lstCels.GetHeadPosition();
	while( posInList )	{
		pCel = pDoc->lstCels.GetNext( posInList );
		if( !pCel->lstSeqs.IsEmpty() )	{			//	( Is it used in a sequence? )
			iNumBitmaps++;
			iMaxSize = max( iMaxSize, pCel->GetImageSize() );
		}
	}
	//	Add a little in case of worst case RLE scenario - no transparent pixels.
	//	( Each 254 pixels would have 2 extra bytes, plus the extra at the end of the line, so say... 10%)
// no longer getting a total size, but a max size
//	Size += iSize/10;

	m_pbmArray = new CDIBitmap*[iNumBitmaps];
	
	int	iBitmap = 0;
	posInList = pDoc->lstCels.GetHeadPosition();
	while( posInList )	{
		pCel = pDoc->lstCels.GetNext( posInList );
		if( !pCel->lstSeqs.IsEmpty() )	{			//	( Is it used in a sequence? )
			m_pbmArray[iBitmap] = &(pCel->dibImage);
			iBitmap++;
		}
	}

	m_iNumBitmaps = iNumBitmaps;
	m_iMaxSize = iMaxSize;

/*
	CPalette* pPal = (CPalette*)CDIBitmap::GetPalette();

	// copy palette
	DWORD dwNumColors;
	VERIFY( pPal->GetObject( sizeof( dwNumColors ), &dwNumColors ) );

	PLOGPALETTE pLogPal = (PLOGPALETTE)new BYTE[sizeof(LOGPALETTE) + dwNumColors * sizeof(PALETTEENTRY)];
	ASSERT( pLogPal != NULL );
	pLogPal->palVersion		= 0x300;
	pLogPal->palNumEntries	= (WORD)dwNumColors;
	
	pPal->GetPaletteEntries( 0, dwNumColors, pLogPal->palPalEntry );

	m_ppalStrip = new CPalette;
	VERIFY( m_ppalStrip->CreatePalette( pLogPal ) );
	delete [] pLogPal;
*/
}
#endif

//-----------------------------------------------------------------------------------------------------------------
#if 0
void CSpriteCatalog::Initialize_RLE( CAnimEditorDoc* pDoc )
{
	//	[ We are initializing a temporary CSpriteCatalog in the AnimEditor, in preparation for serialization out. ]
	//	Set aside a big chunk of memory and RLE the catalog images into it.
	//	As we go, create a map of filenames keys to memory offsets, for the CSpriteSequences to use when they serialize.

	//	Estimate amount of memory needed...
	int			iSize = 0;
	CCel*		pCel;
	POSITION	posInList = pDoc->lstCels.GetHeadPosition();
	while( posInList )	{
		pCel = pDoc->lstCels.GetNext( posInList );
		if( !pCel->lstSeqs.IsEmpty() )			//	( Is it used in a sequence? )
			iSize += pCel->GetWidth() * pCel->GetHeight();
	}
	//	Add a little in case of worst case RLE scenario - no transparent pixels.
	//	( Each 254 pixels would have 2 extra bytes, plus the extra at the end of the line, so say... 10%)
	iSize += iSize/10;
	pRLEPixels = new BYTE[iSize];
	
	BYTE* pPosition = &pRLEPixels[0];

	//	RLE the images, saving starting mem offsets of each in mapCelStartPos, for the sake of CSpriteSequences later.
	posInList = pDoc->lstCels.GetHeadPosition();
	while( posInList )
	{
		pCel = pDoc->lstCels.GetNext( posInList );
		if( !pCel->lstSeqs.IsEmpty() )			//	( Is it used in a sequence? )
		{
			mapCelStartPos.SetAt( pCel->csFileBMP, (int)( pPosition - &pRLEPixels[0] ) );
			int iSize = MemoryWriteBMP_RLE( pPosition, pCel->dibImage.GetBits(), pCel->dibImage.GetLineSize(), 
								pCel->GetWidth(), pCel->GetHeight(), theApp.indexTransparent );
			//	[ no longer Advances pPosition. ]
			pPosition += iSize;	// update by size
		}
	}
	//	Remember how many bytes were actually used, for serialization out.
	iRLEPixelCount = pPosition - &pRLEPixels[0];

	//	Set the memory offset values in each of my CSpriteSequences.
	//	( Was part of construction, now messy as I've made it two-part construction. )
	POSITION posSequence = pDoc->lstSeqs.GetHeadPosition();
	CSequence* pSeq;
	int iCount = 0;
	while( posSequence )
	{
		pSeq = pDoc->lstSeqs.GetNext( posSequence );
		ASSERT( pSeq );
		arSeqs[iCount]->Initialize_RLEOffsets( this, pSeq );
		iCount++;
	}

}
#endif

//-----------------------------------------------------------------------------------------------------------------
#ifdef ANIMEDITORDOC_VERSION
//int CSpriteCatalog::MemoryWriteBMP_RLE( BYTE*& pDest, const BYTE* pSrc, int iPitchSrc, int iWidth, int iHeight, BYTE qTransparentIndex )
int CSpriteCatalog::MemoryWriteBMP_RLE( BYTE* pRLE, const BYTE* pSrc, int iPitchSrc, int iWidth, int iHeight, BYTE qTransparentIndex )
{
	//	Write RLE bitmap data to memory location specified, without a palette, run length encoded.

	//	Write the pixels. The "pitch" of a line is simply the length in pixels, padded to a 4 byte boundary
	//	RLE format:
	//	{
	//		(BYTE)		# of transparent pixels (never larger than 254)
	//		(BYTE)		# of non-transparent pixels, n (n never larger than 254)
	//		(n BYTES)	non-transparent pixel values
	//	}
	//	Repeat, until value of 0xFF in the first field indicates new line.

	//	XXX Leaves pDest at the byte following the final byte of the RLE.
	// don't change pDest, but return the size of the rle data

	int    j, count;					// bitmap column, row, state, count
	WORD   *table;						// table pointer within temporary buffer
	BYTE   *buf;						// temporary buffer for storing rle
	BYTE   *dp, *sp, *spEnd;			// buffer pointer, source pointer
	DWORD  sz = 0;
	BYTE   xpc;

	buf = pRLE;
	dp = buf;							// set destination pointer to buffer
	*(WORD *)dp = iWidth;				// write width & height
	dp += sizeof(WORD);
	*(WORD *)dp = iHeight;
	dp += sizeof(WORD);
	table = (WORD *)dp;
	dp += iHeight * sizeof(WORD);		// jump past line table
	xpc = qTransparentIndex;

	for( j = iHeight - 1; j >= 0; j-- )
	{
		table[j] = dp - buf;
		sp = (BYTE *)pSrc + (iHeight - 1 - j) * iPitchSrc;
		spEnd = sp + iWidth;
		while (TRUE)
		{
			count = 0;
			while (sp != spEnd && *sp == xpc && count < 255)
			{
				sp++;
				count++;
			}
			*dp++ = count;
			
			count = 0;
			while (sp != spEnd && *sp != xpc && count < 255)
			{
				sp++;
				count++;
			}

			*dp++ = count;
			if (count > 0)
			{
				memcpy( dp, sp-count, count );
				dp += count;
			}

			if (sp == spEnd)
				break;
		}
	}

	sz = dp - buf;
	pRLE = dp;
	return (sz);
/*
	BYTE *pDest = pRLE;
	const BYTE* pqPixel;
	const BYTE* pqLineEnd;
	const BYTE* pqPixelStart;
	BYTE qPixels;
	for( int y = iHeight - 1; y >= 0; y-- )
	{
		pqPixel = &pSrc[ y * iPitchSrc ];
		pqLineEnd = pqPixel + iWidth;	//	one beyond line end
		while( TRUE )
		{
			//	Count forward till we hit a non-transparent pixel.
			qPixels = 0;
			while( *pqPixel == qTransparentIndex && qPixels < 254 && pqPixel != pqLineEnd )
			{
				pqPixel++;
				qPixels++;
			}
			//	Write # of transparent pixels.
			*pDest++ = qPixels;
			//	Save starting location of non-transparent pixel set.
			pqPixelStart = pqPixel;
			//	Count forward till we hit a transparent pixel.
			qPixels = 0;
			while( *pqPixel != qTransparentIndex && qPixels < 254 && pqPixel != pqLineEnd )
			{
				pqPixel++;
				qPixels++;
			}
			//	Write # of non-transparent pixels.
			*pDest++ = qPixels;
			if( qPixels )
			{
				//	Write non-transparent pixel values.
				::memcpy( pDest, pqPixelStart, qPixels );
				pDest += qPixels;
			}
			if( pqPixel == pqLineEnd )
			{
				BYTE qEndOfLine = 0xFF;
				*pDest++ = qEndOfLine;
				break;
			}
		}
	}

	return (pDest - pRLE);	// number of RLE bytes
*/
}
#endif

//-----------------------------------------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION
BOOL CSpriteCatalog::RLEFastBlt(void* pDestStart,			//	First byte in locked DD surface.
								long lPitchDest,			//	Surface's line pitch.
								const BYTE* pSrcStart,		//	First byte in RLE data.
								int	iLines )				//	Number of lines in source image.
{
	//	FastBlt rewrite!!!
	//	For unclipped blits. All of source image can be written to the surface.

	//	Copy DWORDs at a time when possible, WORDs and BYTEs when necessary.

#if 0
	const BYTE*	pSrc = pSrcStart;
	void*		pDest = pDestStart;

	BYTE		qSkip;
	BYTE		qRun;

	int			y = 0;
	const BYTE*	pSrcQuadEnd;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= (BYTE*)pDest + qSkip;

		//	Copy color pixels...

		//	Complete sets of four pixels.
		pSrcQuadEnd = pSrc + ( qRun & ~3 );
		while( pSrc != pSrcQuadEnd )
		{
			//	*((DWORD*)pDest)++ = *((DWORD*)pSrc)++;
			*(DWORD*)pDest = *(DWORD*)pSrc;
			pDest = ((DWORD*)pDest) + 1;
			pSrc += 4;
		}
		//	Catch remainders if not divisible by four...
		if( qRun & 2 )
		{
			//	*((WORD*)pDest)++ = *((WORD*)pSrc)++;
			*(WORD*)pDest = *(WORD*)pSrc;
			pDest = ((WORD*)pDest) + 1;
			pSrc += 2;
		}
		if( qRun & 1 )
		{
			//	*((BYTE*)pDest)++ = *pSrc++;
			*(BYTE*)pDest = *pSrc;
			pDest = ((BYTE*)pDest) + 1;
			pSrc++;
		}

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDest = (void*)( (BYTE*)pDestStart + y * lPitchDest );
		}	
	}

#else

	BYTE* pDestTerminator = (BYTE*)pDestStart + iLines * lPitchDest;	//	Used to determine when we are done.

	__asm
	{
		mov		edx, pDestStart					//	Put destination start address in edx. This register will always point to the 
												//	beginning of the current "line".
		mov		ebx, lPitchDest					//	Save destination pitch in ebx (ebx won't change).
		mov		esi, pSrcStart					//	Put source address in esi.

		image_loop:

			mov		edi, edx						//	Set edi to beginning of destination line.

			line_loop:

				xor		ecx, ecx						//	Clear ecx.
				mov		cl, [esi]						//	Put skip count in ecx.
				inc		esi								//	Move source pointer forward.
				add		edi, ecx						//	Skip over transparent pixels in destination.

				mov		cl, [esi]						//	Put run count in ecx.
				mov		eax, ecx						//	Save run count value in eax.
				inc		esi								//	Move source pointer forward.
				shr		ecx, 2							//	Set ecx to the number of complete quads in run count.
				rep		movsd							//	Copy dwords from esi to edi (incrementing the ptrs), ecx times.

				and		eax, 0x00000003					//	Get remainder of division of run count by 4.
				mov		ecx, eax						//	Set ecx to number of remaining pixels to copy.
				rep		movsb							//	Copy bytes from esi to edi (incrementing the ptrs), ecx times.

				cmp		byte ptr [esi], 0xff			//	Is the next byte the end-of-line marker?

			jne		line_loop

			inc		esi								//	Move source pointer forward.
			add		edx, ebx						//	Advance beginning-of-line pointer to start of next line.
			cmp		edx, pDestTerminator			//	Have we reached the end of the image?

		jne		image_loop
	}

#endif

	return TRUE;
}
#endif

//-----------------------------------------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION
BOOL CSpriteCatalog::RLEFastBltHFlipped(void* pDestStart,			//	First byte in locked DD surface.
										long lPitchDest,			//	Surface's line pitch.
										const BYTE* pSrcStart,		//	First byte in RLE data.
										int	iLines,					//	Number of lines in source image.
										int iWidth )				//	Width of image.
{
	//	FastBlt rewrite!!!
	//	For unclipped blits. All of source image can be written to the surface.
	//	Flips image horizontally.

	//	Copy BYTEs individually, for simplicity.

#if 0
	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE*)pDestStart + iWidth - 1;

	BYTE		qSkip;
	BYTE		qRun;

	const BYTE*	pSrcColorEnd;
	int			y = 0;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= pDest - qSkip;

		//	Copy color pixels...

		pSrcColorEnd = pSrc + qRun;
		while( pSrc != pSrcColorEnd )
			*pDest-- = *pSrc++;

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDest = ( (BYTE*)pDestStart + y * lPitchDest + iWidth - 1 );
		}	
	}

#else

	//	xxx needs to be examined for efficiency...

	int	iWidthMinusOne = iWidth - 1;

	BYTE* pDestTerminator = (BYTE*)pDestStart + iLines * lPitchDest + iWidthMinusOne;	//	Used to determine when we are done.

	__asm
	{
		mov		edx, pDestStart					//	Put destination start address in edx. This register will always point to the 
												//	beginning of the current "line".
		add		edx, iWidthMinusOne				//	Correction - the *end* of the current line.
		mov		esi, pSrcStart					//	Put source address in esi.

		image_loop:

			mov		edi, edx						//	Set edi to end of destination line.

			line_loop:

				xor		ecx, ecx						//	Clear ecx.
				mov		cl, [esi]						//	Put skip count in ecx.
				inc		esi								//	Move source pointer forward.
				sub		edi, ecx						//	Skip over transparent pixels in destination.

				mov		cl, [esi]						//	Put run count in ecx.
				mov		eax, ecx						//	Save run count value in eax.
				inc		esi								//	Move source pointer forward.

				shr		ecx, 2							//	Set ecx to the number of complete quads in run count.

				dword_loop:								//	No way to use rep for destination going backwards, it seems...
					jecxz	end_dword_loop					//	Break out of loop when ecx is zero.
					mov		ebx, [esi]						//	Put next 4 bytes of source into ebx.
					add		esi, 4							//	Advance forwards in source.
					bswap	ebx								//	Reverse order of the bytes.
					sub		edi, 4							//	Advance backwards in destination to start of quad.
					mov		[edi], ebx						//	Write the quad into the destination.
					dec		ecx								//	Decrement quad counter.
				jmp dword_loop
				end_dword_loop:

				and		eax, 0x00000003					//	Get remainder of division of run count by 4.
				mov		ecx, eax						//	Set ecx to number of remaining pixels to copy.
				
				byte_loop:
					jecxz	end_byte_loop					//	Break out of loop when ecx is zero.
					movsb									//	Copy a byte from source to destination.
					dec		edi								//	The movsb moved destination forward,	
					dec		edi								//	and we want it to move backward.   xxx better way?
					dec		ecx								//	Decrement counter.
				jmp		byte_loop
				end_byte_loop:

				cmp		byte ptr [esi], 0xff			//	Is the next byte the end-of-line marker?

			jne		line_loop

			inc		esi								//	Move source pointer forward.
			add		edx, lPitchDest					//	Advance end-of-line pointer to end of next line.
			cmp		edx, pDestTerminator			//	Have we reached the end of the image?

		jne		image_loop
	}

#endif

	return TRUE;
}
#endif

//-----------------------------------------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION
BOOL CSpriteCatalog::RLEFastBltClipped(	void* pDestStart,		//	First byte in locked DD surface.
										long lPitchDest,			//	Surface's line pitch.
										const BYTE* pSrcStart,		//	First byte in RLE data.
										const CRect* rcSrc )		//	Rect within source image to write.
{
	//	FastBlt rewrite!!!
	//	For clipped blits.

	return TRUE;
}
#endif

//-----------------------------------------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION
BOOL CSpriteCatalog::RLEXBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, int iPalette )
{
	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE*)pDestStart;

	BYTE		qSkip;
	BYTE		qRun;

	const BYTE*	pSrcColorEnd;
	int			y = 0;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= pDest + qSkip;

		//	Copy color pixels...

		pSrcColorEnd = pSrc + qRun;
		while( pSrc != pSrcColorEnd )
		{
			*pDest++ = light_palettes[iPalette][*pSrc];
			pSrc++;
		}

//			*pDest++ = *pSrc++;

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDest = ( (BYTE*)pDestStart + y * lPitchDest );
		}	
	}
	return TRUE;
}
#endif

//-----------------------------------------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION
BOOL CSpriteCatalog::RLEXBltHFlipped( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, int iWidth, int iPalette )
{
	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE*)pDestStart + iWidth - 1;

	BYTE		qSkip;
	BYTE		qRun;

	const BYTE*	pSrcColorEnd;
	int			y = 0;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= pDest - qSkip;

		//	Copy color pixels...

		pSrcColorEnd = pSrc + qRun;
		while( pSrc != pSrcColorEnd )
		{
			*pDest-- = light_palettes[iPalette][*pSrc];
			pSrc++;
		}

//			*pDest-- = *pSrc++;

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDest = ( (BYTE*)pDestStart + y * lPitchDest + iWidth - 1 );
		}	
	}
	return TRUE;
}
#endif

//-----------------------------------------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION
BOOL CSpriteCatalog::RLEInvisBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines )
{
	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE*)pDestStart;

	BYTE		qSkip;
	BYTE		qRun;

	int			iInvisOffset		= ( rand() % 4 ) * 2 + 2;
	int			iInvisOffsetDelta	= 2;
	int			iInvisOffsetMax		= 8;

	const BYTE*	pSrcColorEnd;
	int			y = 0;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= pDest + qSkip;

		//	Copy color pixels...

//		BOOL bFirst = TRUE;

		pSrcColorEnd = pSrc + qRun;
		while( pSrc != pSrcColorEnd )
		{
//			if( bFirst )
//			{
//				*pDest = 255;
//				bFirst = FALSE;
//			}
//			else if( pSrc == pSrcColorEnd - 1 )
//			{
//				*pDest = 255;
//			}
//			else
				*pDest = *( pDest + iInvisOffset );

			pDest++;
			pSrc++;
		}

//			*pDest++ = *pSrc++;

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			if( iInvisOffset == iInvisOffsetMax || iInvisOffset == 0 )
				iInvisOffsetDelta *= -1;
			iInvisOffset += iInvisOffsetDelta;

			pDest = ( (BYTE*)pDestStart + y * lPitchDest );
		}	
	}
	return TRUE;
}
#endif

//-----------------------------------------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION
BOOL CSpriteCatalog::RLEBiXBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, bixlat* pbixlatPal )
{
	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE*)pDestStart;

	BYTE		qSkip;
	BYTE		qRun;

	const BYTE*	pSrcColorEnd;
	int			y = 0;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= pDest + qSkip;

		//	Copy color pixels...

		pSrcColorEnd = pSrc + qRun;
		while( pSrc != pSrcColorEnd )
		{
			*pDest++ = fastBIXLAT( *pSrc, *pDest, pbixlatPal );
			pSrc++;
		}

//			*pDest++ = *pSrc++;

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDest = ( (BYTE*)pDestStart + y * lPitchDest );
		}	
	}
	return TRUE;
}
#endif

//-----------------------------------------------------------------------------------------------------------------
#ifndef ANIMEDITORDOC_VERSION
BOOL CSpriteCatalog::RLEBiXBltHFlipped( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, int iWidth, bixlat* pbixlatPal)
{
	const BYTE*	pSrc = pSrcStart;
	BYTE*		pDest = (BYTE*)pDestStart + iWidth - 1;

	BYTE		qSkip;
	BYTE		qRun;

	const BYTE*	pSrcColorEnd;
	int			y = 0;

	while( TRUE )
	{
		qSkip	= *pSrc++;
		qRun	= *pSrc++;

		//	Skip transparent pixels...
		pDest	= pDest - qSkip;

		//	Copy color pixels...

		pSrcColorEnd = pSrc + qRun;
		while( pSrc != pSrcColorEnd )
		{
			*pDest-- = fastBIXLAT( *pSrc, *pDest, pbixlatPal );
			pSrc++;
		}

//			*pDest-- = *pSrc++;

		if( *pSrc == 0xFF )
		{
			//	[ End of line. ]
			pSrc++;
			y++;
			if( y == iLines )
				break;
			pDest = ( (BYTE*)pDestStart + y * lPitchDest + iWidth - 1 );
		}	
	}
	return TRUE;
}
#endif

