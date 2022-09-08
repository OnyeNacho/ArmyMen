//-----------------------------------------------------------------
// DIBitmap Object
// C++ Source - DIBitmap.cpp
//-----------------------------------------------------------------

//	xxx I added some procs at the end, and fixed the CRect Width() and Height() bugs...

//-----------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------
#include "StdAfx.h"
//-----------------------------------------------------------------
#include "DIBitmap.h"
#include "DIBPal.h"
#include "BMInfo.h"
#include "AnimEditor.h"

//-----------------------------------------------------------------
// MFC Debugging Support
//-----------------------------------------------------------------
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------
// One-to-One BITMAPINFO Struct
//-----------------------------------------------------------------
struct BITMAPINFO_1TO1
{
  BITMAPINFOHEADER  bmiHeader;
  WORD              bmiColors[256];

                    BITMAPINFO_1TO1(const BITMAPINFOHEADER &bmih);
                    operator BITMAPINFO*()
                      { return (BITMAPINFO*)this; }
};

BITMAPINFO_1TO1::BITMAPINFO_1TO1(const BITMAPINFOHEADER
  &bmihToCopy)
{
  ::CopyMemory(&bmiHeader, &bmihToCopy, sizeof(BITMAPINFOHEADER));
  for (int i = 0; i < 256; i++)
    bmiColors[i] = i;
}

//-----------------------------------------------------------------
// CDIBitmap Static Member Variables
//-----------------------------------------------------------------
CDIBPalette* CDIBitmap::m_pPalette = NULL;
CDIBPalette* CDIBitmap::m_pOriginalPalette = NULL;

//-----------------------------------------------------------------
// CDIBitmap Public Constructor(s)/Destructor
//-----------------------------------------------------------------
CDIBitmap::CDIBitmap()
  : m_hBitmap(NULL), m_pbiInfo(NULL), m_pBits(NULL), m_LineSize(0)
{
	m_pShadow = NULL;
}

CDIBitmap::CDIBitmap(CDC* pdc, const CString &sFileName, BOOL
  bRemapToPal)
  : m_hBitmap(NULL),  m_pbiInfo(NULL), m_pBits(NULL), m_LineSize(0)
{
  Create(pdc, sFileName, bRemapToPal);
}

CDIBitmap::CDIBitmap(CDC* pdc, UINT uiResID, HMODULE hmod, BOOL
  bRemapToPal)
  : m_hBitmap(NULL), m_pbiInfo(NULL), m_pBits(NULL)
{
  Create(pdc, uiResID, hmod, bRemapToPal);
}

CDIBitmap::~CDIBitmap()
{
  Free();
}

//-----------------------------------------------------------------
// CDIBitmap Public Methods
//-----------------------------------------------------------------
BOOL isBitSet( BYTE *pBits, int i, int j, int ht, int sPitch )
{
	BYTE b = *(BYTE *)(pBits + (ht - j - 1) * sPitch + (i >> 3) );
	BYTE bit = 7 - (i % 8);
	return ( b & (1 << bit) );
}


BOOL
CDIBitmap::Create(CDC* pdc, const CString &sFileName, const CString &sPath, BOOL bRemapToPal, BOOL bMask)
{
	CString full_path = sPath + sFileName;

	// Free any previous DIB info
	Free();

	// Open the DIB file
	CFile fileDIB;
	if (!fileDIB.Open(full_path, CFile::modeRead))
		return FALSE;

	// Read the file header
	BITMAPFILEHEADER  Header;
	DWORD dwBytesRead = fileDIB.Read(&Header, sizeof (BITMAPFILEHEADER));
	if (dwBytesRead != sizeof(BITMAPFILEHEADER) || Header.bfType != 0x4D42)
		return FALSE;

	// Read and verify the DIB information
	m_shadowsize = 0;
	m_pbiInfo = (PBITMAPINFO)(new BITMAPINFO_N<256>);
	if (m_pbiInfo)	{
		dwBytesRead = fileDIB.Read(m_pbiInfo, sizeof (BITMAPINFOHEADER));
		if (dwBytesRead != sizeof(BITMAPINFOHEADER))	{
			Free();
			return FALSE;
		}

		// CDIBitmap only supports 8 bpp (256 color) images
		if( m_pbiInfo->bmiHeader.biBitCount != 8 )	{
			AfxMessageBox( "Sorry, AnimEditor supports only 8 bits-per-pixel BMPs." );
			return FALSE;
		}

		// CDIBitmap does not support compression methods
		if( m_pbiInfo->bmiHeader.biCompression != BI_RGB )	{
			AfxMessageBox( "Sorry, AnimEditor does not support compressed BMPs." );
			return FALSE;
		}

		// save the xppm and yppm, which are the hotspots for preprocessed bitmaps
		// reset to 0 if too far outside bounds
		m_hotspotx = m_pbiInfo->bmiHeader.biXPelsPerMeter;
		m_hotspoty = m_pbiInfo->bmiHeader.biYPelsPerMeter;

		if ((m_hotspotx > 640) || (m_hotspotx < -640))	{
			m_hotspotx = 0;
			TRACE("Reset x hotspot for %s\n", sFileName);
		}

		if ((m_hotspoty > 480) || (m_hotspoty < -480))	{
			m_hotspoty = 0;
			TRACE("Reset y hotspot for %s\n", sFileName);
		}

		int nColors = m_pbiInfo->bmiHeader.biClrUsed;
		if (nColors == 0)
			nColors = m_pbiInfo->bmiHeader.biClrUsed = 256;
		m_LineSize = (m_pbiInfo->bmiHeader.biWidth + 3) & ~3;
		if (m_pbiInfo->bmiHeader.biSizeImage == 0)	{
			LONG h = m_pbiInfo->bmiHeader.biHeight;
			if (h < 0L)
				h = -h;
			m_pbiInfo->bmiHeader.biSizeImage = m_LineSize * h;
		}
		::ZeroMemory(m_pbiInfo->bmiColors, 256 * sizeof(RGBQUAD));

		// Skip (forward or backward) to the color info, if necessary
		if (m_pbiInfo->bmiHeader.biSize != sizeof(BITMAPINFOHEADER))
			fileDIB.Seek(m_pbiInfo->bmiHeader.biSize - sizeof (BITMAPINFOHEADER), CFile::current);

		// Read the color info
		fileDIB.Read(m_pbiInfo->bmiColors, nColors * sizeof(RGBQUAD));

		// Install (select and realize) our palette
		if (!InstallPalette(pdc))
			return FALSE;

		// Create a BITMAPINFO struct with a one-to-one color mapping
		BITMAPINFO_1TO1 bi1To1(m_pbiInfo->bmiHeader);

		// Get an HBITMAP using CreateDIBSection and copy image bits
		m_hBitmap = ::CreateDIBSection(pdc->GetSafeHdc(), bi1To1, DIB_PAL_COLORS, (PVOID*)&m_pBits, 0, 0);
		if (m_hBitmap && m_pBits)	{
			fileDIB.Seek(Header.bfOffBits, CFile::begin);
			fileDIB.Read(m_pBits, GetImageSize());

			if (bRemapToPal)
				RemapToPalette();

			if (bMask)
				CreateMask(pdc, theApp.colorTransparent);

			// try to open a shadow file
			CString shadowfile = full_path.Left( full_path.GetLength() - 4 ) + ".sha";
			CFile fileSHA;

			if (!fileSHA.Open(shadowfile, CFile::modeRead))
				return TRUE;

			BITMAPFILEHEADER  ShaHeader;
			BITMAPINFOHEADER  ShaInfo;
			dwBytesRead = fileSHA.Read(&ShaHeader, sizeof (BITMAPFILEHEADER));
			if (dwBytesRead != sizeof(BITMAPFILEHEADER) || Header.bfType != 0x4D42)
				return TRUE;

			dwBytesRead = fileSHA.Read(&ShaInfo, sizeof (BITMAPINFOHEADER));
			if (dwBytesRead != sizeof(BITMAPINFOHEADER))	
				return TRUE;

			char shadowmsg[80];
			// Shadow must be 1 bit
			if( ShaInfo.biBitCount != 1 )	
			{
				sprintf( shadowmsg, "Sorry, AnimEditor supports only 1 bit-per-pixel SHAs (%s)", shadowfile );
				AfxMessageBox( shadowmsg );
				return TRUE;
			}
			if( ShaInfo.biWidth != m_pbiInfo->bmiHeader.biWidth )	
			{
				sprintf( shadowmsg, "Sorry, SHA must have same width as corresponding BMP (%s).", shadowfile );
				AfxMessageBox( shadowmsg );
				return TRUE;
			}
			if( ShaInfo.biHeight != m_pbiInfo->bmiHeader.biHeight )	
			{
				sprintf( shadowmsg, "Sorry, SHA must have same height as corresponding BMP (%s).", shadowfile );
				AfxMessageBox( shadowmsg );
				return TRUE;
			}

			// Shadow does not support compression methods
			if( ShaInfo.biCompression != BI_RGB )	
			{
				sprintf( shadowmsg, "Sorry, AnimEditor does not support compressed SHAs (%s).", shadowfile );
				AfxMessageBox( shadowmsg );
				return TRUE;
			}

			fileSHA.Seek(ShaHeader.bfOffBits, CFile::begin);
			DWORD bmsize = ShaInfo.biSizeImage;
			if( bmsize <= 0 )
			{
				sprintf( shadowmsg, "There was an error in the file (%s)\n", shadowfile );
				AfxMessageBox( shadowmsg );
				return TRUE;
			}
			
			BYTE *pShaBits = (BYTE *)malloc(bmsize);
			if (pShaBits == NULL)	
			{
			    AfxMessageBox("malloc failed while reading shadow\n");
				return TRUE;
			}
			fileSHA.Read(pShaBits, bmsize);

			int sPitch = bmsize / ShaInfo.biHeight;
			BYTE *tempBuf = (BYTE *)malloc( ShaInfo.biHeight * 2 * 40 );
			if( tempBuf == NULL )
			{
				AfxMessageBox("malloc failed while reading shadow\n");
				return TRUE;
			}
			*(WORD *)tempBuf = ShaInfo.biWidth;
			*(WORD *)(tempBuf + 2) = ShaInfo.biHeight;
			BYTE *dp = tempBuf + 4 + ShaInfo.biHeight * 2;
			for( int j = 0; j < ShaInfo.biHeight; j++ )
			{
				BYTE count;
				int i = 0;

				*(WORD *)( tempBuf + 4 + j * sizeof(WORD) ) = dp-tempBuf;
				while( TRUE )
				{
					count = 0;
					while( (i < ShaInfo.biWidth) && (count < 255) && 
						(!isBitSet( pShaBits, i, j, ShaInfo.biHeight, sPitch )) )
					{
						i++;
						count++;
					}
					*dp++ = count;

					count = 0;
					while( (i < ShaInfo.biWidth) && (count < 255) && 
						(isBitSet( pShaBits, i, j, ShaInfo.biHeight, sPitch )) )
					{
						i++;
						count++;
					}
					*dp++ = count;

					if (i >= ShaInfo.biWidth-1 )
						break;
				}
			}
			free( pShaBits );
			m_shadowsize = dp - tempBuf;
			m_pShadow = (BYTE *)malloc( m_shadowsize );
			if( m_pShadow == NULL )
			{
				AfxMessageBox("malloc failed while reading shadow\n");
				return TRUE;
			}
			memcpy( m_pShadow, tempBuf, m_shadowsize );
			free( tempBuf );

			return TRUE;
		}
	}

	// Something went wrong, cleanup everything
	Free();
	return FALSE;
}


BOOL
CDIBitmap::Create(CDC* pdc, UINT uiResID, HMODULE hmod, BOOL bRemapToPal, BOOL bMask)
{
	// Free any previous DIB info
	Free();

	// Find the DIB resource
	HRSRC hresInfo = ::FindResource(hmod, MAKEINTRESOURCE(uiResID),
	RT_BITMAP);
	if (!hresInfo)
		return FALSE;

	// Load the DIB resource
	HGLOBAL hmemBitmap = ::LoadResource(hmod, hresInfo);
	if (!hmemBitmap)	{
		::FreeResource(hmemBitmap);
		return FALSE;
	}

	// Lock the resource and read info
	PBYTE pBitmapImage = (PBYTE)::LockResource(hmemBitmap);
	if (!pBitmapImage)	{
		::FreeResource(hmemBitmap);
		return FALSE;
	}

	// Copy and verify the DIB information
	PBITMAPINFO pbiInfo = (PBITMAPINFO)pBitmapImage;

	// CDIBitmap only supports 8 bpp (256 color) images
	ASSERT(pbiInfo->bmiHeader.biBitCount == 8);
	// CDIBitmap does not support compression methods
	ASSERT(pbiInfo->bmiHeader.biCompression == BI_RGB);

	int nColors = pbiInfo->bmiHeader.biClrUsed;
	if (nColors == 0)
		nColors = 256;
	m_pbiInfo = (PBITMAPINFO)(new BITMAPINFO_N<256>);
	if (m_pbiInfo)	{
		::ZeroMemory(m_pbiInfo, sizeof(BITMAPINFO_N<256>));
		::CopyMemory(&m_pbiInfo->bmiHeader, &pbiInfo->bmiHeader,
		sizeof(m_pbiInfo->bmiHeader));
		m_pbiInfo->bmiHeader.biClrUsed = nColors;
		m_LineSize = (m_pbiInfo->bmiHeader.biWidth + 3) & ~3;
		if (m_pbiInfo->bmiHeader.biSizeImage == 0)	{
			LONG  h = m_pbiInfo->bmiHeader.biHeight;
			if (h < 0L)
				h = -h;
			m_pbiInfo->bmiHeader.biSizeImage = m_LineSize * h;
		}

		// Copy the color info
		::CopyMemory(m_pbiInfo->bmiColors, (LPSTR)pbiInfo +
		pbiInfo->bmiHeader.biSize, nColors * sizeof(RGBQUAD));

		// Install (select and realize) our palette
		if (!InstallPalette(pdc))
			return FALSE;

		// Create a BITMAPINFO struct with a one-to-one color mapping
		BITMAPINFO_1TO1 bi1To1(m_pbiInfo->bmiHeader);

		// Get an HBITMAP using CreateDIBSection and copy image bits
		m_hBitmap = ::CreateDIBSection(pdc->GetSafeHdc(), bi1To1,
		DIB_PAL_COLORS, (PVOID*)&m_pBits, 0, 0);
		if (m_hBitmap && m_pBits)	{
			const PBYTE pBits = pBitmapImage + pbiInfo->bmiHeader.biSize + nColors * sizeof(RGBQUAD);
			::CopyMemory(m_pBits, pBits, GetImageSize());

			if (bRemapToPal)
				RemapToPalette();

			if (bMask)
				CreateMask(pdc, theApp.colorTransparent);

			// (Unlock and) free resource
			UnlockResource(hmemBitmap);
			::FreeResource(hmemBitmap);

			return TRUE;
		}
	}

	// Something went wrong, cleanup everything
	Free();
	if (pBitmapImage)
		UnlockResource(hmemBitmap);
	if (hmemBitmap)
		::FreeResource(hmemBitmap);
	return FALSE;
}


/*
** METHOD 
**   CDIBitmap::CreateMask
**
** DESCRIPTION
**   creates and returns a 1-bit per pixel mask as large as the 
**   dib that is 1s wherever the dib color matches the 
**   rgbTransparent color and 0s everywhere else.
*/
HBITMAP CDIBitmap::CreateMask(CDC* pdc, COLORREF rgbTransparent)
{
	CDC dcImage;
	dcImage.CreateCompatibleDC( pdc );
	HBITMAP hbmImageOld = (HBITMAP)dcImage.SelectObject(m_hBitmap);

	int width = GetWidth() + 1;
	int height = GetHeight() + 1;
	if (m_hMaskBitmap == NULL)
		m_hMaskBitmap = CreateBitmap(width,height,1,1,NULL);

	if (m_hMaskBitmap)	{
		CDC dcMask;
		dcMask.CreateCompatibleDC(pdc);
		HBITMAP hbmMaskOld = (HBITMAP)dcMask.SelectObject(m_hMaskBitmap);

		// THIS WON'T WORK IF THE BITMAP DOES NOT HAVE A PALETTE
		RGBQUAD white,black;

		black.rgbRed = 0;
		black.rgbGreen = 0; 
		black.rgbBlue = 0; 
		black.rgbReserved = 0;

		white.rgbRed = 255; 
		white.rgbGreen = 255; 
		white.rgbBlue = 255; 
		white.rgbReserved = 0;

		UINT nColors = GetNumColors();
		if (nColors)	{
			RGBQUAD *pWhite = CreateMaskTable(NULL,rgbTransparent,white,black,FALSE);
			RGBQUAD *pColors = m_pPalette->ColorTable;

			if (pWhite && pColors)	{
				VERIFY(dcMask.BitBlt(0, 0, width, height, &dcMask, 0, 0, WHITENESS));
				SetDIBColorTable(dcImage.GetSafeHdc(), 0, nColors, pWhite);
				dcMask.SetBkColor(RGB(0,0,0));            // 1s --> black (0x000000)
				dcMask.SetTextColor(RGB(255,255,255));    // 0s --> white (0xFFFFFF)
				VERIFY(dcMask.BitBlt(0, 0, width, height, &dcImage, 0, 0, SRCAND));
				SetDIBColorTable(dcImage.GetSafeHdc(), 0, nColors, pColors);
			}
			delete pWhite;
		}
		else	{
			// it's true color or hi color or it doesn't have a palette
			// TBD: what do we do? FOR NOW, make the mask completely opaque
			dcMask.BitBlt(0, 0, width, height, &dcMask, 0, 0, BLACKNESS);
		}

		dcMask.SelectObject(hbmMaskOld);
		dcMask.DeleteDC();
	}
	else	{
		DeleteMask();
	}

	dcImage.SelectObject(hbmImageOld);
	dcImage.DeleteDC();

	return m_hMaskBitmap;
}


void CDIBitmap::DeleteMask()
{
	if (m_hMaskBitmap != NULL)
	{
		::DeleteObject(m_hMaskBitmap);
		m_hMaskBitmap = NULL;
	}
}


// Get the number of color table entries.
DWORD
CDIBitmap::GetNumColors() const
{
    BITMAPINFOHEADER* pBIH;
    int iColors, iBitCount;

    ASSERT(m_pbiInfo);

	pBIH = &(m_pbiInfo->bmiHeader);

	// the color table length is determined by the biClrUsed
	// field if the value in the field is nonzero.
    if (pBIH->biClrUsed != 0) {
        iColors = pBIH->biClrUsed;
    }
	else	{
		iBitCount = pBIH->biBitCount;
		switch (iBitCount) 
		{
			case 1:
				iColors = 2;
				break;
			case 4:
				iColors = 16;
				break;
			case 8:
				iColors = 256;
				break;
			default:
				iColors = 0;
				break;
		}
	}

    return iColors;
}


RGBQUAD *CDIBitmap::CopyColorTable(RGBQUAD *pRGB) const
{
	UINT size = GetNumColors() * sizeof(RGBQUAD);
	if (!size)
		return NULL;

	if (!pRGB)	{
		pRGB = new RGBQUAD[size];
		ASSERT_NEW(pRGB);
	}
	memcpy(pRGB, m_pbiInfo->bmiColors, size);
	return pRGB;
}


RGBQUAD *CDIBitmap::CreateMaskTable(RGBQUAD *pRGB, COLORREF colorref, RGBQUAD match, RGBQUAD nomatch, BOOL bMatchOnly)
{
	UINT nColors = GetNumColors();
	UINT size = nColors * sizeof(RGBQUAD);
	if (!size)
		return NULL;

	if (!pRGB)	{
		pRGB = new RGBQUAD[size];
		ASSERT_NEW(pRGB);
	}

	RGBQUAD *pSrc;
	RGBQUAD *pOld = m_pPalette->ColorTable;
//	RGBQUAD *pOld = m_pbiInfo->bmiColors;
	RGBQUAD *pNew = pRGB;

    BYTE red = GetRValue(colorref);
	BYTE blue = GetBValue(colorref);
	BYTE green = GetGValue(colorref);

	for (UINT i = 0; i < nColors; i++,pOld++,pNew++)	{
		if (pOld->rgbRed == red && pOld->rgbGreen == green && pOld->rgbBlue == blue)
			pSrc = &match;
		else if (bMatchOnly)
			pSrc = pOld;
		else 
			pSrc = &nomatch;

		pNew->rgbRed = pSrc->rgbRed;
		pNew->rgbGreen = pSrc->rgbGreen;
		pNew->rgbBlue = pSrc->rgbBlue;
		pNew->rgbReserved = pSrc->rgbReserved;
	}
	return pRGB;
}


void
CDIBitmap::Draw(CDC* pdc, CPoint ptDest, BOOL bInstallPal)
{
  // Create a rectangle for the whole DIB and draw
  CRect rcDIB(0, 0, GetWidth()-1, GetHeight()-1);
  Draw(pdc, ptDest, rcDIB, bInstallPal);
}

void
CDIBitmap::Draw(CDC* pdc, CPoint ptDest, CRect rcSrc, BOOL
  bInstallPal)
{
  if (m_hBitmap)
  {
//		//xxx
//	  	BYTE* pBytes = new BYTE[ m_pbiInfo->bmiHeader.biWidth + 3 & ~3 ];
//		DWORD dwLines = GetDIBits( pdc->GetSafeHdc(), m_hBitmap, 20, 1, pBytes, m_pbiInfo, DIB_PAL_COLORS );
////		dwLines = GetDIBits( NULL, m_hBitmap, 20, 1, pBytes, m_pbiInfo, DIB_PAL_COLORS );
//		//xxx

    // Create a memory DC
    CDC dcMem;
    dcMem.CreateCompatibleDC(pdc);

    // Install the palette
	if (bInstallPal)
		InstallPalette(pdc);

    // Select the DIB into the DC
    HBITMAP hbmOld = (HBITMAP)dcMem.SelectObject(m_hBitmap);

    // Draw and cleanup
    pdc->BitBlt(ptDest.x, ptDest.y, rcSrc.Width()+1, rcSrc.Height()+1,
      &dcMem, rcSrc.left, rcSrc.top, SRCCOPY);
    dcMem.SelectObject(hbmOld);

//		//xxx
//		delete [] pBytes;
//		//xxx
  }
}


void CDIBitmap::DrawTransparent(CDC* pdc, int dx, int dy, CDC* pdcUser, int sx, int sy, int sw, int sh)
{
	ASSERT(m_hMaskBitmap != NULL);
	ASSERT(m_hBitmap != NULL);

	CDC *pdcTmp;
	CDC dcTmp;

	pdcTmp = pdcUser;
	if (!pdcTmp)	{
		dcTmp.CreateCompatibleDC( pdc );
		pdcTmp = &dcTmp;
	}

	COLORREF oldBk = pdc->SetBkColor(RGB(255, 255, 255));      // 1s --> 0xFFFFFF
	COLORREF oldTx = pdc->SetTextColor(RGB(0, 0, 0));          // 0s --> 0x000000

	HBITMAP hOldBitmap = (HBITMAP) pdcTmp->SelectObject(m_hBitmap);
	VERIFY(pdc->BitBlt(dx, dy, sw, sh, pdcTmp, sx, sy, SRCINVERT));

	pdcTmp->SelectObject(m_hMaskBitmap);
	VERIFY(pdc->BitBlt(dx, dy, sw, sh, pdcTmp, sx, sy, SRCAND));

	pdcTmp->SelectObject(m_hBitmap);
	VERIFY(pdc->BitBlt(dx, dy, sw, sh, pdcTmp, sx, sy, SRCINVERT));

	pdcTmp->SelectObject(hOldBitmap);
	pdc->SetBkColor(oldBk);
	pdc->SetTextColor(oldTx);
}

/*
void CDIBitmap::DrawTransparent( CDC* pdc, COLORREF& colorTransparent, CPoint ptDest, BOOL bInstallPal )
{
  // Create a rectangle for the whole DIB and draw
  CRect rcDIB(0, 0, GetWidth()-1, GetHeight()-1);
  DrawTransparent( pdc, colorTransparent, ptDest, rcDIB, bInstallPal );
}

void CDIBitmap::DrawTransparent( CDC* pdc, COLORREF& colorTransparent, CPoint ptDest, CRect rcSrc, BOOL bInstallPal )
{
	//	ajw added
	if( m_hBitmap )
	{
		//	Prepare image.
		CDC dcImage;
		dcImage.CreateCompatibleDC( pdc );

		if( bInstallPal )
			InstallPalette( pdc );

		HBITMAP hbmImageOld = (HBITMAP)dcImage.SelectObject( m_hBitmap );

		//	Prepare mask.
		CDC dcMask;
		dcMask.CreateCompatibleDC( pdc );

		HBITMAP hbmMask = CreateBitmap( GetWidth()+1, GetHeight()+1, 1, 1, NULL );		   //	xxx +1?
		HBITMAP hbmMaskOld = (HBITMAP)dcMask.SelectObject( hbmMask );

		dcImage.SetBkColor( colorTransparent );

		dcMask.BitBlt( 0, 0, rcSrc.Width()+1, rcSrc.Height()+1, &dcImage, rcSrc.left, rcSrc.top, SRCCOPY );

		//	Blit mask.
		pdc->BitBlt( ptDest.x, ptDest.y, rcSrc.Width()+1, rcSrc.Height()+1, &dcMask, 0, 0, SRCAND );

		//	Blit image.
		pdc->BitBlt( ptDest.x, ptDest.y, rcSrc.Width()+1, rcSrc.Height()+1, &dcImage, 0, 0, SRCPAINT );
		
		//	Clean-up.
		dcImage.SelectObject( hbmImageOld );
		dcMask.SelectObject( hbmMaskOld );
		::DeleteObject( hbmMask );
	}
}
*/

void
CDIBitmap::Blit(BYTE *pDest, int nDestPitch, int x, int y, int
  nWidth, int nHeight) const
{
  const BYTE* pSource;
  int         nSourcePitch;
  
  if (GetHeight() > 0)
  {
    pSource = m_pBits + (GetHeight() - y - 1) * GetLineSize() + x;
    nSourcePitch = -GetLineSize();
  }
  else
  {
    pSource = m_pBits + y * GetLineSize() + x;
    nSourcePitch = GetLineSize();
  }

  for (; nHeight; --nHeight)
  {
    ::CopyMemory(pDest, pSource, nWidth);
    pDest += nDestPitch;
    pSource += nSourcePitch;
  }
}

BOOL
CDIBitmap::GetPaletteEntries(PALETTEENTRY vpeToBeFilled[]) const
{
  // Get the number of colors
  DWORD dwColors = GetNumColors();
  if (0 == dwColors)
    return FALSE;

  // Get a pointer to the the DIB's color table
  const RGBQUAD* vRGB = m_pbiInfo->bmiColors;
  for (DWORD i = 0; i < dwColors; i++)
  {
    vpeToBeFilled[i].peRed = vRGB[i].rgbRed;
    vpeToBeFilled[i].peGreen = vRGB[i].rgbGreen;
    vpeToBeFilled[i].peBlue = vRGB[i].rgbBlue;
    vpeToBeFilled[i].peFlags = 0;
  }

  return TRUE;
}

UINT
CDIBitmap::GetTransColorIndex() const
{
  return (UINT)*m_pBits;
}

void
CDIBitmap::CleanupPalette()
{
  if (m_pPalette)
  {
    delete m_pPalette;
    m_pPalette = NULL;
  }

  if (m_pOriginalPalette)
  {
    delete m_pOriginalPalette;
    m_pOriginalPalette = NULL;
  }
}

//-----------------------------------------------------------------
// CDIBitmap Protected Methods
//-----------------------------------------------------------------
void
CDIBitmap::Free()
{
  if (m_hBitmap)
  {
    DeleteObject(m_hBitmap);
    m_hBitmap = NULL;
    m_pBits = NULL;
  }

  if( m_pShadow )
  {
	  free( m_pShadow );
	  m_pShadow = NULL;
  }
	DeleteMask();

  if (m_pbiInfo)
  {
    delete (BITMAPINFO_N<256>*)m_pbiInfo;
    m_pbiInfo = NULL;
  }
}

BOOL
CDIBitmap::InstallPalette(CDC* pdc)
{
  ASSERT(m_pbiInfo);
  ASSERT(pdc);
  if (m_pbiInfo && pdc)
  {
    if (NULL == m_pPalette)
    {
		m_pPalette = new CDIBPalette(*this);
		if (!m_pPalette->MakeIdentity())		// testing removal
			return FALSE;
    }
    if (m_pPalette)
    {
      pdc->SelectPalette(m_pPalette, FALSE);
      pdc->RealizePalette();
      return TRUE;
    }
  }

  return FALSE;
}


BOOL
CDIBitmap::SetOriginalPalette()
{
	ASSERT(m_pbiInfo);

	if (NULL == m_pOriginalPalette)	{
		m_pOriginalPalette = new CDIBPalette(*this);
		return TRUE;
	}
	return FALSE;
}


BOOL
CDIBitmap::RemapToPalette()
{
  if (m_pPalette && m_pbiInfo && m_pBits)
  {
    BYTE      byMap[256];
    DWORD     dwColors = GetNumColors();
    size_t    i;

    for (i = 0; i < dwColors; i++)
    {
      RGBQUAD &rgb = m_pbiInfo->bmiColors[i];
      byMap[i] = m_pPalette->GetNearestPaletteIndex(
        PALETTERGB(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue));
    }

    PBYTE pBits = m_pBits;
    for (i = 0; i < GetImageSize(); i++, pBits++)
      *pBits = byMap[*pBits];
    return TRUE;
  }

  return FALSE;
}


BOOL
CDIBitmap::MakeMappingToOriginal(BYTE byMap[256])
{
  if (m_pPalette && m_pOriginalPalette)
  {
    DWORD     dwColors = GetNumColors();
    size_t    i;

    for (i = 0; i < dwColors; i++)	{
      RGBQUAD rgb = m_pPalette->ColorTable[i];
//    byMap[i] = m_pOriginalPalette->GetNearestPaletteIndex( PALETTERGB(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue));
      byMap[i] = m_pOriginalPalette->GetNearestPaletteIndex( RGB(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue));
    }

    return TRUE;
  }

  return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------
//	xxx
//	The following added by AJW...
//-----------------------------------------------------------------------------------------------------------------
void CDIBitmap::DrawZoomed(CDC* pdc, CPoint ptDest, int iZoom, DWORD dwRasterOp, BOOL bInstallPal)
{
  // Create a rectangle for the whole DIB and draw
  CRect rcDIB(0, 0, GetWidth()-1, GetHeight()-1);
  DrawZoomed(pdc, ptDest, rcDIB, iZoom, dwRasterOp, bInstallPal);
}

//-----------------------------------------------------------------------------------------------------------------
void CDIBitmap::DrawZoomed(CDC* pdc, CPoint ptDest, CRect rcSrc, int iZoom, DWORD dwRasterOp, BOOL bInstallPal)
{
  if (m_hBitmap)
  {
    // Create a memory DC
    CDC dcMem;
    dcMem.CreateCompatibleDC(pdc);

    // Install the palette
	if (bInstallPal)
		InstallPalette(pdc);

    // Select the DIB into the DC
    HBITMAP hbmOld = (HBITMAP)dcMem.SelectObject(m_hBitmap);

    // Draw and cleanup
	if( iZoom == 1 )
	{
	    pdc->BitBlt( ptDest.x, ptDest.y, rcSrc.Width()+1, rcSrc.Height()+1,
					&dcMem, rcSrc.left, rcSrc.top, dwRasterOp );
	}
	else
	{
		pdc->StretchBlt( ptDest.x, ptDest.y, (rcSrc.Width()+1) * iZoom, (rcSrc.Height()+1) * iZoom,
					  &dcMem, rcSrc.left, rcSrc.top, rcSrc.Width()+1, rcSrc.Height()+1, dwRasterOp );

	}
    dcMem.SelectObject(hbmOld);
  }
}

//-----------------------------------------------------------------------------------------------------------------
CPoint CDIBitmap::Crop( CDC* pDC )
{
	//	Crops the bitmap by removing any rows and columns of pixels around the borders that are purely transparent
	//	(transparent is defined as palette index specified by top left corner of "palette.bmp").
	//	Return CPoint( -1, -1 ) if crop isn't possible because it's all transparent, otherwise, offset from top left to crop pos.
	//	pDC is used as the "compatible" DC.

	ASSERT( m_hBitmap );

	//	Examine the bitmap's bytes, looking for bounds of non-transparent pixels.

	int	iXMin = m_pbiInfo->bmiHeader.biWidth;
	int iYMin = m_pbiInfo->bmiHeader.biHeight;
	int iXMax = -1;
	int iYMax = -1;

	BYTE* pPixel = m_pBits;		//	iterator

	for( int iY = m_pbiInfo->bmiHeader.biHeight - 1; iY >= 0; iY-- )
	{
		for( int iX = 0; iX < m_LineSize; iX++ )
		{
			if( iX < m_pbiInfo->bmiHeader.biWidth )		//	[ else we are reading end-of-line buffer bytes - ignore ]
			{
				if( *pPixel != theApp.indexTransparent )
				{
					iXMin = min( iXMin, iX );
					iYMin = min( iYMin, iY );
					iXMax = max( iXMax, iX );
					iYMax = max( iYMax, iY );
				}				
			}
			pPixel++;
		}
	}
	if( iXMax < iXMin )
	{
		//	Can happen only if all is transparent.
		return CPoint( -1, -1 );
	}

	int iWidthNew = iXMax - iXMin + 1;
	int iHeightNew = iYMax - iYMin + 1;

	//	Set up a mem dc.
	CDC dcNew;
	VERIFY( dcNew.CreateCompatibleDC( pDC ) );
	CPalette* ppalOrig;
	VERIFY( ppalOrig = dcNew.SelectPalette( (CPalette*)m_pPalette, FALSE ) );

	//	Set up a new bitmap.
	LONG m_LineSizeNew = ( iWidthNew + 3 ) & ~3;
	PBITMAPINFO m_pbiInfoNew = (PBITMAPINFO)(new BITMAPINFO_N<256>);
	m_pbiInfoNew->bmiHeader.biSize			= m_pbiInfo->bmiHeader.biSize;
	m_pbiInfoNew->bmiHeader.biWidth			= iWidthNew;
	m_pbiInfoNew->bmiHeader.biHeight		= iHeightNew;
	m_pbiInfoNew->bmiHeader.biPlanes		= m_pbiInfo->bmiHeader.biPlanes;
	m_pbiInfoNew->bmiHeader.biBitCount		= m_pbiInfo->bmiHeader.biBitCount;
	m_pbiInfoNew->bmiHeader.biCompression	= m_pbiInfo->bmiHeader.biCompression;
	m_pbiInfoNew->bmiHeader.biSizeImage		= m_LineSizeNew * iHeightNew;
	m_pbiInfoNew->bmiHeader.biXPelsPerMeter = m_pbiInfo->bmiHeader.biXPelsPerMeter;
	m_pbiInfoNew->bmiHeader.biYPelsPerMeter = m_pbiInfo->bmiHeader.biYPelsPerMeter;
	m_pbiInfoNew->bmiHeader.biClrUsed		= m_pbiInfo->bmiHeader.biClrUsed;
	m_pbiInfoNew->bmiHeader.biClrImportant	= m_pbiInfo->bmiHeader.biClrImportant;
	PBYTE m_pBitsNew;
	//	Make the new bitmap using CreateDIBSection, so that m_pBitsNew can be grabbed 
	//	(so that we can replace all existing CDIBitmap members - I don't really know if this pointer is actually really needed, though...)

    // Create a BITMAPINFO struct with a one-to-one color mapping
    BITMAPINFO_1TO1 bi1To1( m_pbiInfoNew->bmiHeader );

	HBITMAP hbmpNew = ::CreateDIBSection( dcNew.GetSafeHdc(), bi1To1, DIB_PAL_COLORS, (PVOID*)&m_pBitsNew, NULL, 0 );

	//	Put the new bitmap into the dc.
	HBITMAP hbmpOrig = (HBITMAP)::SelectObject( dcNew.GetSafeHdc(), hbmpNew );
	//CBitmap* pbmpOrig = dcNew.SelectObject( 

	//	Blit the appropriate rect of the current bitmap into the new bitmap.
	Draw( &dcNew, CPoint( 0, 0 ), CRect( iXMin, iYMin, iXMax, iYMax ) );

	//	[ hbmpNew is now what we want this CDIBitmap to be. ]

	//	Redefine member vars.
	m_LineSize = m_LineSizeNew;
	::CopyMemory( m_pbiInfo, m_pbiInfoNew, sizeof( BITMAPINFO_N<256> ) );

	m_pBits = m_pBitsNew;

	//	Unselect new bitmap from dc.
	VERIFY( ::SelectObject( dcNew.GetSafeHdc(), hbmpOrig ) == hbmpNew );
	VERIFY( dcNew.SelectPalette( ppalOrig, FALSE ) == (CPalette*)m_pPalette );

	//	The last, and most important, member to replace.
    ::DeleteObject( m_hBitmap );
	m_hBitmap = hbmpNew;

	delete m_pbiInfoNew;

	return CPoint( iXMin, iYMin );
}

//-----------------------------------------------------------------------------------------------------------------
RGBQUAD* CDIBitmap::GetPaletteColors() { 
	return m_pPalette->ColorTable;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CDIBitmap::SaveHotspot( const CString &csFileNameFullPath ) const
{
	//	Writes out hotspot to the bmiHeader.biXPelsPerMeter and bmiHeader.biYPelsPerMeter in BMP file.
	CString csErr;

	//	Open the BMP file.
	CFile fileDIB;
	if( !fileDIB.Open( csFileNameFullPath, CFile::modeReadWrite | CFile::shareExclusive ) )
	{
		csErr.Format( "Error: Cannot open %s. (File is read-only?)", csFileNameFullPath );
		AfxMessageBox( csErr );
		return FALSE;
	}

	//	Read the file header.
	BITMAPFILEHEADER  Header;
	DWORD dwBytesRead = fileDIB.Read( &Header, sizeof( BITMAPFILEHEADER ) );
	if( dwBytesRead != sizeof(BITMAPFILEHEADER) || Header.bfType != 0x4D42 )
	{
		csErr.Format( "Error: %s does not appear to be a valid BMP file!", csFileNameFullPath );
		AfxMessageBox( csErr );
		return FALSE;
	}

	//	Read the data leading up to the values we'll set, and as an extra check, check them against what we have previously read in.
	//	(Since we need to pass through them anyway.)
	BOOL bHeaderChanged = FALSE;
	DWORD	   biSize;
	if( !SaveHotspot_ReadAndVerifyOneValue( fileDIB, csFileNameFullPath, (void*)&biSize, sizeof( biSize ) ) )		return FALSE;
	if( biSize != m_pbiInfo->bmiHeader.biSize )																		bHeaderChanged = TRUE;
	LONG       biWidth;
	if( !SaveHotspot_ReadAndVerifyOneValue( fileDIB, csFileNameFullPath, (void*)&biWidth, sizeof( biWidth ) ) )		return FALSE;
	if( biWidth != m_pbiInfo->bmiHeader.biWidth )																	bHeaderChanged = TRUE;
	LONG       biHeight;
	if( !SaveHotspot_ReadAndVerifyOneValue( fileDIB, csFileNameFullPath, (void*)&biHeight, sizeof( biHeight ) ) )	return FALSE;
	if( biHeight != m_pbiInfo->bmiHeader.biHeight )																	bHeaderChanged = TRUE;
	WORD       biPlanes;
	if( !SaveHotspot_ReadAndVerifyOneValue( fileDIB, csFileNameFullPath, (void*)&biPlanes, sizeof( biPlanes ) ) )	return FALSE;
	if( biPlanes != m_pbiInfo->bmiHeader.biPlanes )																	bHeaderChanged = TRUE;
	WORD       biBitCount;
	if( !SaveHotspot_ReadAndVerifyOneValue( fileDIB, csFileNameFullPath, (void*)&biBitCount, sizeof( biBitCount ) ) )		return FALSE;
	if( biBitCount != m_pbiInfo->bmiHeader.biBitCount ) 																bHeaderChanged = TRUE;
	DWORD      biCompression;
	if( !SaveHotspot_ReadAndVerifyOneValue( fileDIB, csFileNameFullPath, (void*)&biCompression, sizeof( biCompression ) ) )	return FALSE;
	if( biCompression != m_pbiInfo->bmiHeader.biCompression )																bHeaderChanged = TRUE;
	DWORD      biSizeImage;
	if( !SaveHotspot_ReadAndVerifyOneValue( fileDIB, csFileNameFullPath, (void*)&biSizeImage, sizeof( biSizeImage ) ) )		return FALSE;
	if( biSizeImage != m_pbiInfo->bmiHeader.biSizeImage )																bHeaderChanged = TRUE;

	if( bHeaderChanged )
	{
		csErr.Format( "Warning: %s appears to have changed since it was loaded. (Saving anyway.)", csFileNameFullPath );
		AfxMessageBox( csErr );
	}

	//	Write new values for biXPelsPerMeter and biYPelsPerMeter.
	fileDIB.Write( &m_hotspotx, sizeof( m_hotspotx ) );
	fileDIB.Write( &m_hotspoty, sizeof( m_hotspotx ) );

	return TRUE;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CDIBitmap::SaveHotspot_ReadAndVerifyOneValue( CFile& fileDIB, const CString& csFileNameFullPath, void* pItem, DWORD dwItemSize ) const
{
	DWORD dwBytesRead = fileDIB.Read( pItem, dwItemSize );
	if( dwBytesRead != dwItemSize )
	{
		CString csErr;
		csErr.Format( "Error: %s seems to cut off in the middle of header information!", csFileNameFullPath );
		AfxMessageBox( csErr );
		return FALSE;
	}
	return TRUE;
}