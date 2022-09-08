// dib.cpp : implementation file
//
//

#include "stdafx.h"
#include "dib.h"
#include "malloc.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/*
 * Dib Header Marker - used in writing DIBs to files
 */
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

#ifdef _MAC
#define SWAPWORD(x) MAKEWORD(HIBYTE(x), LOBYTE(x))
#define SWAPLONG(x) MAKELONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))
void ByteSwapHeader(BITMAPFILEHEADER* bmiHeader);
void ByteSwapInfo(LPSTR lpHeader, BOOL fWin30Header);
#endif



/////////////////////////////////////////////////////////////////////////////
// CDIB

CDIB::CDIB()
{
    m_pBMI = NULL;
    m_pBits = NULL;
	m_hBitmap = NULL;
	m_hOldBitmap = NULL;
	m_hMaskBitmap = NULL;
	m_hDC = NULL;
	m_nRefHDC = 0;
}

CDIB::~CDIB()
{
    DeleteContents();
}

void CDIB::DeleteHDC()
{
	if (m_hDC)
	{
		ASSERT(m_nRefHDC > 0);
		if (--m_nRefHDC == 0)
		{
			//TRACE("HDC %x deleted\n", m_hDC);
			SelectHBitmap(m_hDC, m_hOldBitmap);
			DeleteDC(m_hDC);
			m_hOldBitmap = NULL;
			m_hDC = NULL;
		}
		else
			; //TRACE("HDC %x refcount = %d\n", m_hDC, m_nRefHDC);
	}
}

void CDIB::DeleteMask()
{
	if (m_hMaskBitmap != NULL)
	{
		::DeleteObject(m_hMaskBitmap);
		m_hMaskBitmap = NULL;
	}
}

HDC CDIB::CreateHDC(HDC hdc)
{
	HDC hDisplayDC = NULL;

	if (m_hDC == NULL)
	{
		if (hdc) 
		{
			// TBD: is this necessary or can I just use CreateCompatibleDC(NULL)?
			hDisplayDC = CreateDC("DISPLAY",NULL,NULL,NULL);
			if (hDisplayDC == NULL)
			{
				TRACE0("CDIB::CreateDC couldn't get display DC\n");
				return NULL;
			}
			m_hDC = CreateCompatibleDC(hDisplayDC);
			DeleteDC(hDisplayDC);
		}
		else
			m_hDC = CreateCompatibleDC(hdc);

		if (m_hDC == NULL)
		{
			TRACE0("CDIB:CreateDC couldn't create compatible DC\n");
			return NULL;
		}
		m_hOldBitmap = SelectHBitmap(m_hDC, m_hBitmap);
	}
	if (m_hDC)
	{
		++m_nRefHDC;
		//TRACE("HDC %x refcount = %d\n", m_hDC, m_nRefHDC);
	}
	return m_hDC;
}
	

void CDIB::DeleteContents()
{
	if (m_nRefHDC)
	{
		TRACE("Deleting dib while there are %d outstanding hdc references\n", m_nRefHDC);
		ASSERT(m_hDC != NULL);
		m_nRefHDC = 1; // so the hdc will get destroyed
	}
	DeleteHDC();
	DeleteMask();
	if (m_hBitmap != NULL)
	{
		::DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
		m_pBits = NULL;
	}
    else if (m_pBits)
	{
		free(m_pBits);
		m_pBits = NULL;
	}
    if (m_pBMI != NULL) 
	{
		free(m_pBMI);
		m_pBMI = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Private functions

static BOOL IsWinDIB(BITMAPINFOHEADER* pBIH)
{
    ASSERT(pBIH);
    if (((BITMAPCOREHEADER*)pBIH)->bcSize == sizeof(BITMAPCOREHEADER)) {
        return FALSE;
    }
    return TRUE;
}

static int GetColorCount(int iDepth)
{
	int iColors;

	switch (iDepth) 
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
	return iColors;
}

static int NumDIBColorEntries(BITMAPINFO* pBmpInfo) 
{
    BITMAPINFOHEADER* pBIH;
    BITMAPCOREHEADER* pBCH;
    int iColors, iBitCount;

    ASSERT(pBmpInfo);

    pBIH = &(pBmpInfo->bmiHeader);
    pBCH = (BITMAPCOREHEADER*) pBIH;

    // Start off by assuming the color table size from
    // the bit-per-pixel field.
    if (IsWinDIB(pBIH)) {
        iBitCount = pBIH->biBitCount;
    } else {
        iBitCount = pBCH->bcBitCount;
    }

    iColors = GetColorCount(iBitCount);

    // If this is a Windows DIB, then the color table length
    // is determined by the biClrUsed field if the value in
    // the field is nonzero.
    if (IsWinDIB(pBIH) && (pBIH->biClrUsed != 0)) {
        iColors = pBIH->biClrUsed;
    }

    return iColors;
}


/////////////////////////////////////////////////////////////////////////////
// CDIB commands

/* METHOD
**    CDIB:GetLineSize:
** 
** DESCRIPTION
**    returns the number of bytes per line in this dib.
*/
int CDIB::GetLineSize()
{
	return (DibWidth() * DibDepth() / 8 + 3) & ~3;
}

BOOL CDIB::Create(int iWidth, int iHeight, int iDepth, RGBQUAD *pRGB)
{
	HDC hdc = NULL;
	RGBQUAD *prgb;
	BITMAPINFOHEADER *pBI;
    int i;

	ASSERT(iWidth > 0);
	ASSERT(iHeight > 0);
    ASSERT(iDepth == 1 || iDepth == 4 || iDepth == 8 || iDepth == 16 || iDepth == 24 || iDepth == 32);

    // Delete any existing stuff.
	DeleteContents();

	int iColors = GetColorCount(iDepth);

    // Allocate memory for the header.
    m_pBMI = (BITMAPINFO*) malloc(sizeof(BITMAPINFOHEADER)
                                  + iColors * sizeof(RGBQUAD));
    if (!m_pBMI) {
        TRACE("Out of memory for DIB header");
        return FALSE;
    }

	hdc = ::CreateDC("DISPLAY",NULL,NULL,NULL);
	if (!hdc)
		goto $abort;

    // Fill in the header info.
    pBI = (BITMAPINFOHEADER*) m_pBMI;
    pBI->biSize = sizeof(BITMAPINFOHEADER);
    pBI->biWidth = iWidth;
	pBI->biHeight = iHeight;

    pBI->biPlanes = 1;
    pBI->biBitCount = iDepth;
    pBI->biCompression = BI_RGB;
    pBI->biSizeImage = 0;
    pBI->biXPelsPerMeter = 0;
    pBI->biYPelsPerMeter = 0;
    pBI->biClrUsed = 0;
    pBI->biClrImportant = 0;

    prgb = GetClrTabAddress();
	if (iColors)
	{
		if (pRGB)
		{
			memcpy(prgb, pRGB, iColors * sizeof(RGBQUAD));
		}
		else
		{
			// create a greyscale palette
			int color,inc = 256/iColors;
			for (i = 0, color = 0; i < iColors; i++, color+=inc) 
			{
				prgb->rgbBlue = color;
				prgb->rgbGreen = color;
				prgb->rgbRed = color;
				prgb->rgbReserved = 0;
				prgb++;
			}
		}
	}
	// create the dibsection
	m_hBitmap = ::CreateDIBSection(hdc, 
		m_pBMI,
		DIB_RGB_COLORS,
		(void **)&m_pBits,
		NULL,
		0);

	if (m_hBitmap == NULL)
		goto $abort;

	if (hdc) ::DeleteDC(hdc);
    return TRUE;

$abort:
	DeleteContents();
	if (hdc) ::DeleteDC(hdc);
	return FALSE;
}


// Save a DIB to an open file
BOOL CDIB::Save(CFile* fp)
{
	BITMAPFILEHEADER bmfHdr; // Header for Bitmap file
	LPBITMAPINFOHEADER lpBI;
	UINT nInfoSize;
	UINT nPaletteSize;
	UINT dwBitsSize;

	if ((fp == NULL) || (m_pBMI == NULL) || (m_pBits == FALSE))
		return FALSE;

	GdiFlush();
	lpBI = &m_pBMI->bmiHeader;

	/*
	 * Fill in the fields of the file header
	 */

	/* Fill in file type (first 2 bytes must be "BM" for a bitmap) */
	bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM"

	// Calculating the size of the DIB is a bit tricky (if we want to
	// do it right).  The easiest way to do this is to call _memsize
	// on our memeory handle, but since the size of our memory may have
	// been padded a few bytes, we may end up writing out a few too
	// many bytes to the file (which may cause problems with some apps).
	//
	// So, instead let's calculate the size manually (if we can)
	//
	// First, find size of header plus size of color table.  Since the
	// first DWORD in both BITMAPINFOHEADER and BITMAPCOREHEADER conains
	// the size of the structure, let's use this.
    nPaletteSize = 	GetNumClrEntries() * sizeof(RGBQUAD);
	nInfoSize = *(LPDWORD)lpBI + nPaletteSize;  

	// Now calculate the size of the image

	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// It's an RLE bitmap, we can't calculate size, so trust the
		// biSizeImage field

		dwBitsSize = lpBI->biSizeImage;
	}
	else
	{
		// It's not RLE, so size is Width (DWORD aligned) * Height

		dwBitsSize = GetLineSize() * GetHeight();

		// Now, since we have calculated the correct size, why don't we
		// fill in the biSizeImage field (this will fix any .BMP files which
		// have this field incorrect).

		lpBI->biSizeImage = dwBitsSize;
	}


	// Calculate the file size by adding the DIB size to sizeof(BITMAPFILEHEADER)

	bmfHdr.bfSize = nInfoSize + dwBitsSize + sizeof(BITMAPFILEHEADER);
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;

	/*
	 * Now, calculate the offset the actual bitmap bits will be in
	 * the file -- It's the Bitmap file header plus the DIB header,
	 * plus the size of the color table.
	 */
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + nInfoSize;

#ifdef _MAC
	ByteSwapHeader(&bmfHdr);

	// First swap the size field
	*((LPDWORD)lpBI) = SWAPLONG(*((LPDWORD)lpBI));

	// Now swap the rest of the structure (we don't save < Win30 files)
	ByteSwapInfo((LPSTR)lpBI, TRUE);
#endif

	TRY
	{
		// Write the file header
		fp->Write((LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER));
		// Write the DIB header and the palette
		fp->Write(m_pBMI, nInfoSize);
		// Write the actual bits
		fp->WriteHuge(m_pBits, dwBitsSize);
	}
	CATCH (CFileException, e)
	{
#ifdef _MAC
		// Swap everything back
		*((LPDWORD)lpBI) = SWAPLONG(*((LPDWORD)lpBI));
		ByteSwapInfo((LPSTR)lpBI, TRUE);
#endif
		THROW_LAST();
	}
	END_CATCH

#ifdef _MAC
	// Swap everything back
	*((LPDWORD)lpBI) = SWAPLONG(*((LPDWORD)lpBI));
	ByteSwapInfo((LPSTR)lpBI, TRUE);
#endif
	fp->Flush();
	return TRUE;
}

// Load a DIB from an open file
// TBD: should take full advantage of exception handling capabilities
BOOL CDIB::Load(CFile *fp)
{
	HDC hdc = NULL;
    BOOL bIsPM = FALSE;
    LPBITMAPINFOHEADER lpBI;

	if (fp == NULL)
		return FALSE;

	DeleteContents();

	// Get the current file position.
	DWORD dwFileStart = fp->GetPosition();

	// Read the file header to get the file size and to
	// find out where the bits start in the fp->
	BITMAPFILEHEADER BmpFileHdr;
	UINT iBytes;

	iBytes = fp->Read(&BmpFileHdr, sizeof(BmpFileHdr));
	if (iBytes != sizeof(BmpFileHdr)) {
		TRACE("Failed to read file header");
		goto $abort;
	}

	// Check that we have the magic 'BM' at the start.
	if (BmpFileHdr.bfType != DIB_HEADER_MARKER) {
		TRACE("Not a bitmap file");
		goto $abort;
	}

	// Make a wild guess that the file is in Windows DIB
	// format and read the BITMAPINFOHEADER. If the file turns
	// out to be a PM DIB file we'll convert it later.
	BITMAPINFOHEADER BmpInfoHdr;
	iBytes = fp->Read(&BmpInfoHdr, sizeof(BmpInfoHdr)); 
	if (iBytes != sizeof(BmpInfoHdr)) 
	{
		TRACE("Failed to read BITMAPINFOHEADER");
		goto $abort;
	}

	// Check that we got a real Windows DIB fp->
	if (BmpInfoHdr.biSize != sizeof(BITMAPINFOHEADER)) 
	{
		if (BmpInfoHdr.biSize != sizeof(BITMAPCOREHEADER)) 
		{
			TRACE(" File is not Windows or PM DIB format");
			goto $abort;
		}

		// Set a flag to convert PM file to Win format later.
		bIsPM = TRUE;

		// Back up the file pointer and read the BITMAPCOREHEADER
		// and create the BITMAPINFOHEADER from it.
		fp->Seek(dwFileStart + sizeof(BITMAPFILEHEADER), CFile::begin);
		BITMAPCOREHEADER BmpCoreHdr;
		iBytes = fp->Read(&BmpCoreHdr, sizeof(BmpCoreHdr)); 
		if (iBytes != sizeof(BmpCoreHdr)) 
		{
			TRACE("Failed to read BITMAPCOREHEADER");
			goto $abort;
		}

		BmpInfoHdr.biSize = sizeof(BITMAPINFOHEADER);
		BmpInfoHdr.biWidth = (int) BmpCoreHdr.bcWidth;
		BmpInfoHdr.biHeight = (int) BmpCoreHdr.bcHeight;
		BmpInfoHdr.biPlanes = BmpCoreHdr.bcPlanes;
		BmpInfoHdr.biBitCount = BmpCoreHdr.bcBitCount;
		BmpInfoHdr.biCompression = BI_RGB;
		BmpInfoHdr.biSizeImage = 0;
		BmpInfoHdr.biXPelsPerMeter = 0;
		BmpInfoHdr.biYPelsPerMeter = 0;
		BmpInfoHdr.biClrUsed = 0;
		BmpInfoHdr.biClrImportant = 0;
	}
	else	{
		if (BmpInfoHdr.biXPelsPerMeter > 640)
			BmpInfoHdr.biXPelsPerMeter = 0;
		if (BmpInfoHdr.biYPelsPerMeter > 480)
			BmpInfoHdr.biYPelsPerMeter = 0;
	}

	// Work out how much memory we need for the BITMAPINFO
	// structure, color table and then for the bits.  
	// Allocate the memory blocks.
	// Copy the BmpInfoHdr we have so far,
	// and then read in the color table from the fp->
	int iColors;
	UINT iColorTableSize;
	iColors = NumDIBColorEntries((LPBITMAPINFO) &BmpInfoHdr);
	iColorTableSize = iColors * sizeof(RGBQUAD);
	DWORD dwBitsSize;
	UINT iBISize;

	// Always allocate enough room for iColor entries.
	iBISize = sizeof(BITMAPINFOHEADER)  + iColorTableSize;  

	// Allocate the memory for the header.
	m_pBMI = (LPBITMAPINFO) malloc(iBISize);
	if (!m_pBMI) {
		TRACE("Out of memory for DIB header");
		goto $abort;
	}

	// Copy the header we already have.
	memcpy(m_pBMI, &BmpInfoHdr, sizeof(BITMAPINFOHEADER));

	// Now read the color table in from the fp->
	if (bIsPM == FALSE) {
		// Read the color table from the fp->
		iBytes = fp->Read(((LPBYTE) m_pBMI) + sizeof(BITMAPINFOHEADER),
							 iColorTableSize);
		if (iBytes != iColorTableSize) {
			TRACE("Failed to read color table");
			goto $abort;
		}
	} else {
		// Read each PM color table entry in turn and convert it
		// to Windows DIB format as we go.
		LPRGBQUAD lpRGB;
		lpRGB = (LPRGBQUAD) ((LPBYTE) m_pBMI + sizeof(BITMAPINFOHEADER));
		int i;
		RGBTRIPLE rgbt;
		for (i=0; i<iColors; i++) {
			iBytes = fp->Read(&rgbt, sizeof(RGBTRIPLE));
			if (iBytes != sizeof(RGBTRIPLE)) {
				TRACE("Failed to read RGBTRIPLE");
				goto $abort;
			}
			lpRGB->rgbBlue = rgbt.rgbtBlue;
			lpRGB->rgbGreen = rgbt.rgbtGreen;
			lpRGB->rgbRed = rgbt.rgbtRed;
			lpRGB->rgbReserved = 0;
			lpRGB++;
		}
	}
	// Compute the image size and update the header if necessary...
	lpBI = &m_pBMI->bmiHeader;
	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// It's an RLE bitmap, we can't calculate size, so trust the
		// biSizeImage field

		dwBitsSize = lpBI->biSizeImage;
	}
	else
	{
		// It's not RLE, so size is Width (DWORD aligned) * Height

		dwBitsSize = GetLineSize() * GetHeight();

		// Now, since we have calculated the correct size, why don't we
		// fill in the biSizeImage field (this will fix any .BMP files which
		// have this field incorrect).

		lpBI->biSizeImage = dwBitsSize;
	}

	// get the system device context
	hdc = CreateDC("DISPLAY",NULL,NULL,NULL);
	if (!hdc) goto $abort;

	m_hBitmap = ::CreateDIBSection(hdc, 
		m_pBMI,
		DIB_RGB_COLORS,
		(void **)&m_pBits,
		NULL,
		0);

	if (m_hBitmap == NULL)
		goto $abort;

	// Seek to the bits in the fp->
	fp->Seek(dwFileStart + BmpFileHdr.bfOffBits, CFile::begin);

	// Read the bits.
	if (fp->ReadHuge(m_pBits, dwBitsSize) != dwBitsSize) {
		TRACE("Failed to read bits");
		goto $abort;
	}
	// MakeCompatibleDIB(hdc); // try to make it compatible
	if (hdc) ::DeleteDC(hdc);
	return TRUE;
            
$abort: // Something went wrong.
	DeleteContents();
	if (hdc) ::DeleteDC(hdc);
    return FALSE;    
}

/////////////////////////////////////////////////////////////////////////////
void CDIB::Save(CArchive& ar)
{
	BITMAPFILEHEADER bmfHdr; // Header for Bitmap file
	LPBITMAPINFOHEADER lpBI;
	UINT nInfoSize;
	UINT nPaletteSize;
	UINT dwBitsSize;

	ASSERT(ar.IsStoring());

	if ((m_pBMI == NULL) || (m_pBits == FALSE))
	{
		TRACE("No data to save\n");
		AfxThrowArchiveException(CArchiveException::generic);
	}

	GdiFlush();
	lpBI = &m_pBMI->bmiHeader;

	/*
	 * Fill in the fields of the file header
	 */

	/* Fill in file type (first 2 bytes must be "BM" for a bitmap) */
	bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM"

	// Calculating the size of the DIB is a bit tricky (if we want to
	// do it right).  The easiest way to do this is to call _memsize
	// on our memeory handle, but since the size of our memory may have
	// been padded a few bytes, we may end up writing out a few too
	// many bytes to the file (which may cause problems with some apps).
	//
	// So, instead let's calculate the size manually (if we can)
	//
	// First, find size of header plus size of color table.  Since the
	// first DWORD in both BITMAPINFOHEADER and BITMAPCOREHEADER conains
	// the size of the structure, let's use this.
    nPaletteSize = 	GetNumClrEntries() * sizeof(RGBQUAD);
	nInfoSize = *(LPDWORD)lpBI + nPaletteSize;  

	// Now calculate the size of the image

	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// It's an RLE bitmap, we can't calculate size, so trust the
		// biSizeImage field

		dwBitsSize = lpBI->biSizeImage;
	}
	else
	{
		// It's not RLE, so size is Width (DWORD aligned) * Height

		dwBitsSize = GetLineSize() * GetHeight();

		// Now, since we have calculated the correct size, why don't we
		// fill in the biSizeImage field (this will fix any .BMP files which
		// have this field incorrect).

		lpBI->biSizeImage = dwBitsSize;
	}


	// Calculate the file size by adding the DIB size to sizeof(BITMAPFILEHEADER)

	bmfHdr.bfSize = nInfoSize + dwBitsSize + sizeof(BITMAPFILEHEADER);
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;

	/*
	 * Now, calculate the offset the actual bitmap bits will be in
	 * the file -- It's the Bitmap file header plus the DIB header,
	 * plus the size of the color table.
	 */
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + nInfoSize;

#ifdef _MAC
	ByteSwapHeader(&bmfHdr);

	// First swap the size field
	*((LPDWORD)lpBI) = SWAPLONG(*((LPDWORD)lpBI));

	// Now swap the rest of the structure (we don't save < Win30 files)
	ByteSwapInfo((LPSTR)lpBI, TRUE);
#endif

	TRY
	{
		// Write the file header
		ar.Write((LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER));

		// Write the DIB header and the palette
		ar.Write(m_pBMI, nInfoSize);

		// Write the actual bits
		ar.Write(m_pBits, dwBitsSize);
	}
	CATCH_ALL(e)
	{
#ifdef _MAC
		// Swap everything back
		*((LPDWORD)lpBI) = SWAPLONG(*((LPDWORD)lpBI));
		ByteSwapInfo((LPSTR)lpBI, TRUE);
#endif
		THROW_LAST();
	}
	END_CATCH_ALL

#ifdef _MAC
	// Swap everything back
	*((LPDWORD)lpBI) = SWAPLONG(*((LPDWORD)lpBI));
	ByteSwapInfo((LPSTR)lpBI, TRUE);
#endif
}


void CDIB::Load(CArchive& ar)
{
	HDC hdc = NULL;
    BOOL bIsPM = FALSE;
    LPBITMAPINFOHEADER lpBI;
    DWORD dwSkip = 0;

	TRY
	{
		// Read the file header to get the file size and to
		// find out where the bits start
		BITMAPFILEHEADER BmpFileHdr;
		UINT iBytes;

		iBytes = ar.Read(&BmpFileHdr, sizeof(BmpFileHdr));
		if (iBytes != sizeof(BmpFileHdr)) 
		{
			TRACE("Failed to read file header");
			AfxThrowArchiveException(CArchiveException::endOfFile);
		}
        dwSkip = BmpFileHdr.bfOffBits;
        dwSkip -= iBytes;

		// Check that we have the magic 'BM' at the start.
		if (BmpFileHdr.bfType != DIB_HEADER_MARKER) 
		{
			TRACE("Not a bitmap file");
			AfxThrowArchiveException(CArchiveException::generic);
		}

		// Make a wild guess that the file is in Windows DIB
		// format and read the BITMAPINFOHEADER. If the file turns
		// out to be a PM DIB file we'll convert it later.
		BITMAPINFOHEADER BmpInfoHdr;
		iBytes = ar.Read(&BmpInfoHdr, sizeof(BmpInfoHdr)); 
		if (iBytes != sizeof(BmpInfoHdr)) 
		{
			TRACE("Failed to read BITMAPINFOHEADER");
			AfxThrowArchiveException(CArchiveException::endOfFile);

		}
        dwSkip -= iBytes;
		// Check that we got a real Windows DIB fp->
		if (BmpInfoHdr.biSize != sizeof(BITMAPINFOHEADER)) 
		{
			if (BmpInfoHdr.biSize != sizeof(BITMAPCOREHEADER)) 
			{
				TRACE(" File is not Windows or PM DIB format");
				AfxThrowArchiveException(CArchiveException::generic);
			}

			// Set a flag to convert PM file to Win format later.
			BITMAPCOREHEADER BmpCoreHdr;
			ASSERT(sizeof(BITMAPCOREHEADER) <= sizeof(BITMAPINFOHEADER));
			memmove(&BmpCoreHdr,&BmpInfoHdr,sizeof(BITMAPCOREHEADER));
			bIsPM = TRUE;

			// Back up the file pointer and read the BITMAPCOREHEADER
			BmpInfoHdr.biSize = sizeof(BITMAPINFOHEADER);
			BmpInfoHdr.biWidth = (LONG) BmpCoreHdr.bcWidth;
			BmpInfoHdr.biHeight = (LONG) BmpCoreHdr.bcHeight;
			BmpInfoHdr.biPlanes = BmpCoreHdr.bcPlanes;
			BmpInfoHdr.biBitCount = BmpCoreHdr.bcBitCount;
			BmpInfoHdr.biCompression = BI_RGB;
			BmpInfoHdr.biSizeImage = 0;
			BmpInfoHdr.biXPelsPerMeter = 0;
			BmpInfoHdr.biYPelsPerMeter = 0;
			BmpInfoHdr.biClrUsed = 0;
			BmpInfoHdr.biClrImportant = 0;
		}

		// Work out how much memory we need for the BITMAPINFO
		// structure, color table and then for the bits.  
		// Allocate the memory blocks.
		// Copy the BmpInfoHdr we have so far,
		// and then read in the color table from the fp->
		int iColors;
		UINT iColorTableSize;
		iColors = NumDIBColorEntries((LPBITMAPINFO) &BmpInfoHdr);
		iColorTableSize = iColors * sizeof(RGBQUAD);
		DWORD dwBitsSize;
		UINT iBISize;

		// Always allocate enough room for iColor entries.
		iBISize = sizeof(BITMAPINFOHEADER)  + iColorTableSize;  

		// Allocate the memory for the header.
		m_pBMI = (LPBITMAPINFO) malloc(iBISize);
		if (!m_pBMI) 
		{
			TRACE("Out of memory for DIB header");
			AfxThrowMemoryException();
		}

		// Copy the header we already have.
		memcpy(m_pBMI, &BmpInfoHdr, sizeof(BITMAPINFOHEADER));

		// Now read the color table
		if (bIsPM == FALSE) 
		{
			// Read the color table 
			iBytes = ar.Read(((LPBYTE) m_pBMI) + sizeof(BITMAPINFOHEADER),
								 iColorTableSize);
			if (iBytes != iColorTableSize) 
			{
				TRACE("Failed to read color table");
				AfxThrowArchiveException(CArchiveException::endOfFile);
			}
			dwSkip -= iBytes;
		} 
		else 
		{
			// Read each PM color table entry in turn and convert it
			// to Windows DIB format as we go.
			LPRGBQUAD lpRGB;
			lpRGB = (LPRGBQUAD) ((LPBYTE) m_pBMI + sizeof(BITMAPINFOHEADER));
			int i;
			RGBTRIPLE rgbt;
			for (i=0; i<iColors; i++) 
			{
				iBytes = ar.Read(&rgbt, sizeof(RGBTRIPLE));
				if (iBytes != sizeof(RGBTRIPLE)) 
				{
					TRACE("Failed to read RGBTRIPLE");
					AfxThrowArchiveException(CArchiveException::endOfFile);
				}
				dwSkip -= iBytes;
				lpRGB->rgbBlue = rgbt.rgbtBlue;
				lpRGB->rgbGreen = rgbt.rgbtGreen;
				lpRGB->rgbRed = rgbt.rgbtRed;
				lpRGB->rgbReserved = 0;
				lpRGB++;
			}
		}
		// Compute the image size and update the header if necessary...
		lpBI = &m_pBMI->bmiHeader;
		if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
		{
			// It's an RLE bitmap, we can't calculate size, so trust the
			// biSizeImage field
			dwBitsSize = lpBI->biSizeImage;
		}
		else
		{
			// It's not RLE, so size is Width (DWORD aligned) * Height

			dwBitsSize = GetLineSize() * GetHeight();

			// Now, since we have calculated the correct size, why don't we
			// fill in the biSizeImage field (this will fix any .BMP files which
			// have this field incorrect).

			lpBI->biSizeImage = dwBitsSize;
		}

		// get the system device context
		hdc = CreateDC("DISPLAY",NULL,NULL,NULL);
		if (hdc == NULL) 
			AfxThrowMemoryException();

		m_hBitmap = ::CreateDIBSection(hdc, 
			m_pBMI,
			DIB_RGB_COLORS,
			(void **)&m_pBits,
			NULL,
			0);

		if (m_hBitmap == NULL)
			AfxThrowMemoryException();

		if (dwSkip > 0)
		{
			// Seek forward to the bitmap data bits
			BYTE *pBuffer;
			TRY
			{
				pBuffer = (BYTE *)malloc(1024);
				if (pBuffer == NULL)
					AfxThrowMemoryException();
				while (dwSkip)
				{
					DWORD dwBytes = min(dwSkip,1024);
					if (ar.Read(pBuffer, dwBytes) != dwBytes)
						AfxThrowArchiveException(CArchiveException::endOfFile);
					dwSkip -= dwBytes;
				}
				delete pBuffer;
			}
			CATCH_ALL(e)
			{
				delete pBuffer;
				THROW_LAST();
			}
			END_CATCH_ALL
		}
				

		// Read the bits.
		if (ar.Read(m_pBits, dwBitsSize) != dwBitsSize) 
		{
			TRACE("Failed to read dib bits");
			AfxThrowArchiveException(CArchiveException::endOfFile);
		}

		::DeleteDC(hdc);
	}
	CATCH_ALL(e)
	{
		DeleteContents();
		if (hdc) ::DeleteDC(hdc);
		THROW_LAST();
	}
	END_CATCH_ALL 
}

/* 
** METHOD
**    CDIB::Draw
** 
** PARAMETERS
**    HDC hdc          -- destination hardware device context
**    int dx,dy,dw,dh  -- destination rectangle 
**    int sx,sy,sw,sh  -- source rectangle (for now all numbers must be positive)
**
** DESCRIPTION
**    Copies the source rectangle from this DIB to the destination
**    rectangle in the given hardware device context.  Assumes CreateHDC
**    has already been called for this DIB. Also assumes that whatever palette
**    you want to use has already been installed and realized.
** 
** RETURNS
**    TRUE if the operation was successful
*/
BOOL CDIB::Draw(HDC hdc, int dx, int dy, int dw, int dh, 
				int sx, int sy, int sw, int sh)
{
	ASSERT(0 < sw && sw <= GetWidth() && (sx + sw <= GetWidth()));
	ASSERT(0 < sh && sh <= GetHeight() && (sy + sh <= GetHeight()));
	ASSERT(m_hDC != NULL);

    BOOL bDrawn = FALSE;

	if (dw == sw && dh == sh)
		bDrawn = BitBlt(hdc, dx, dy, dw, dh, m_hDC, sx, sy, SRCCOPY);
	else
		bDrawn = StretchBlt(hdc, dx, dy, dw, dh, m_hDC, sx, sy, sw, sh, SRCCOPY);

	return bDrawn;
}

BOOL CDIB::Draw(HDC hdc, int dx, int dy, int sx, int sy, int sw, int sh)
{
	ASSERT(0 < sw && sw <= GetWidth() && (sx + sw <= GetWidth()));
	ASSERT(0 < sh && sh <= GetHeight() && (sy + sh <= GetHeight()));
	ASSERT(m_hDC != NULL);

    return BitBlt(hdc, dx, dy, sw, sh, m_hDC, sx, sy, SRCCOPY);
}

// Assumes appropriate palettes have been selected into hdcDest and hdcTmp
void CDIB::DrawTrueMask(HDC hdcDest, int dx, int dy, HDC hdcTmp, int sx, int sy, int sw, int sh)
{
	ASSERT(m_hMaskBitmap != NULL);
	ASSERT(m_hBitmap != NULL);

	COLORREF oldBk = SetBkColor(hdcDest, RGB(255, 255, 255));      // 1s --> 0xFFFFFF
	COLORREF oldTx = SetTextColor(hdcDest, RGB(0, 0, 0));          // 0s --> 0x000000

	HBITMAP hBitmap = SelectHBitmap(hdcTmp, m_hBitmap);
	VERIFY(BitBlt(hdcDest, dx, dy, sw, sh, hdcTmp, sx, sy, SRCINVERT));

	SelectHBitmap(hdcTmp, m_hMaskBitmap);
	VERIFY(BitBlt(hdcDest, dx, dy, sw, sh, hdcTmp, sx, sy, SRCAND));

	SelectHBitmap(hdcTmp, m_hBitmap);
	VERIFY(BitBlt(hdcDest, dx, dy, sw, sh, hdcTmp, sx, sy, SRCINVERT));

	SelectHBitmap(hdcTmp, hBitmap);
	SetBkColor(hdcDest, oldBk);
	SetTextColor(hdcDest, oldTx);
}


void CDIB::DrawTrueMask(HDC hdcDest, const RECT& dstRect, HDC hdcTmp)
{
	ASSERT(m_hMaskBitmap != NULL);
	ASSERT(m_hBitmap != NULL);
	int dx = dstRect.left;
	int dy = dstRect.top;
	int dw = dstRect.right - dstRect.left;
    int dh = dstRect.bottom - dstRect.top;
    int sw = GetWidth();
	int sh = GetHeight();

	ASSERT(dstRect.right >= dstRect.left);
	ASSERT(dstRect.bottom >= dstRect.top);

#if 0
	// TBD: why doesn't this work when you use this code on an 8-bit display?
	// the colors come out all wrong.
	COLORREF oldBk = SetBkColor(hdcDest, RGB(255, 255, 255));      // 1s --> 0xFFFFFF
	COLORREF oldTx = SetTextColor(hdcDest, RGB(0, 0, 0));          // 0s --> 0x000000

	HBITMAP hBitmap = SelectHBitmap(hdcTmp, m_hBitmap);
	VERIFY(StretchBlt(hdcDest, dx, dy, dw, dh, hdcTmp, 0, 0, sw, sh, SRCINVERT));
	
	SelectHBitmap(hdcTmp, m_hMaskBitmap);
	VERIFY(StretchBlt(hdcDest, dx, dy, dw, dh, hdcTmp, 0, 0, sw, sh, SRCAND));

	SelectHBitmap(hdcTmp, m_hBitmap);
	VERIFY(StretchBlt(hdcDest, dx, dy, dw, dh, hdcTmp, 0, 0, sw, sh, SRCINVERT));

	SelectHBitmap(hdcTmp, hBitmap);
	SetBkColor(hdcDest, oldBk);
	SetTextColor(hdcDest, oldTx);
#else
	if (dw == sw && dh == sh)
	{
		DrawTrueMask(hdcDest, dx, dy, hdcTmp, 0, 0, sw, sh);
	}
	else
	{
		// do the blt off-screen (at full size) to preserve the colors.
		HBITMAP hBitmap = CreateCompatibleBitmap(hdcDest, sw, sh);
		if (hBitmap)
		{	
			// copy the destination area to the off-screen buffer
			HBITMAP hTmpBitmap = SelectHBitmap(hdcTmp, hBitmap);
#if 0
			// TBD: this code hangs on David's portable Compaq....it seems to be
			// a bug in Compaq video driver.  
			StretchBlt(hdcTmp, 0, 0, sw, sh, hdcDest, dx, dy, dw, dh, SRCCOPY);
#else
			BitBlt(hdcTmp,0,0,sw,sh,hdcDest,0,0,WHITENESS);
#endif
			// draw the full-size object over the off-screen buffer
			// Note: we can't just use hdcDest as our temporary dc 
			// because it might be the screen.
			if (CreateHDC())
			{
				DrawTrueMask(hdcTmp, 0, 0, m_hDC, 0, 0, sw, sh);
				DeleteHDC();

				// draw the off-screen buffer to the destination
    			StretchBlt(hdcDest, dx, dy, dw, dh, hdcTmp, 0, 0, sw, sh, SRCCOPY);
			}
			SelectHBitmap(hdcTmp, hTmpBitmap);
			::DeleteObject(hBitmap);
		}
	}
#endif
}

#ifdef CAPS1
BOOL CDIB::DrawC1Transparent(HDC hdc, int dx, int dy, HDC hdcTmp, int sx, int sy, int sw, int sh, COLORREF rgbTransparent)
{
    ASSERT(GetDeviceCaps(hdc, CAPS1) & C1_TRANSPARENT);

	// Special transparency background mode
	int oldMode = SetBkMode(hdc, NEWTRANSPARENT);
	COLORREF oldBk = SetBkColor(hdc, rgbTransparent);
    HBITMAP hBitmap = SelectHBitmap(hdcTmp, m_hBitmap);

	// Actual blt is a simple source copy; transparency is automatic.
	BOOL bDrawn = BitBlt(hdc, dx, dy, sw, sh, hdcTmp, sx, sy, SRCCOPY);

	SelectHBitmap(hdcTmp, hBitmap);
	SetBkColor(hdc, oldBk);
	SetBkMode(hdc, oldMode);
	return bDrawn;
}

BOOL CDIB::DrawC1Transparent(HDC hdc, RECT& dstRect, HDC hdcTmp, COLORREF rgbTransparent)
{
	ASSERT(GetDeviceCaps(hdc, CAPS1) & C1_TRANSPARENT);
    ASSERT(m_hBitmap != NULL);

	int dx = dstRect.left;
	int dy = dstRect.top;
	int dw = dstRect.right - dstRect.left;
    int dh = dstRect.bottom - dstRect.top;
    int sw = GetWidth();
	int sh = GetHeight();

	int oldMode = SetBkMode(hdc, NEWTRANSPARENT);
	COLORREF oldBk = SetBkColor(hdc, rgbTransparent);
    HBITMAP hBitmap = SelectHBitmap(hdcTmp, m_hBitmap);

	// Actual blt is a simple source copy; transparency is automatic.
	BOOL bDrawn;

	if (dw == sw && dh == sh)
	   bDrawn = BitBlt(hdc, dx, dy, sw, sh, hdcTmp, 0, 0, SRCCOPY);
	else
	   bDrawn = StretchBlt(hdc, dx, dy, dw, dh, hdcTmp, 0, 0, sw, sh, SRCCOPY);

	SelectHBitmap(hdcTmp, hBitmap);
	SetBkColor(hdc, oldBk);
	SetBkMode(hdc, oldMode);
	return bDrawn;
}
#endif



// Get the number of color table entries.
int CDIB::GetNumClrEntries()
{
    return NumDIBColorEntries(m_pBMI);
}

BYTE * CDIB::GetBitsAddress(int x,int y)
{
	ASSERT(0 <= x && x < GetWidth());
	ASSERT(0 <= y && y < GetHeight());

	int xoffset = (x * DibDepth() + 7) >> 3;
	int iLineInc = GetLineIncrement();
    register BYTE *pAddress = m_pBits;

	if (iLineInc < 0)
		pAddress += (GetHeight() - 1 - y) * -iLineInc;
    else
		pAddress += y * iLineInc;

	pAddress += xoffset;
	return pAddress;
}

COLORREF CDIB::GetColor(int iColor)
{
	ASSERT(iColor >= 0 && iColor < GetNumClrEntries());
	RGBQUAD *pRGB = GetClrTabAddress() + iColor;
	return RGB(pRGB->rgbRed, pRGB->rgbGreen, pRGB->rgbBlue);
}

void CDIB::SetPalette(int iStart, int nEntries, PALETTEENTRY *pEntry)
{
	/// TBD: WHY DOESN'T THIS WORK!!!!
	int iEnd = iStart + nEntries;
	int iMax = GetNumClrEntries();
	if (iEnd > iMax) iEnd = iMax;

	nEntries = iEnd - iStart;
	if (nEntries == 0) return;

	RGBQUAD *pRGB = GetClrTabAddress();
    ASSERT(pRGB);

	for (int i=iStart; i < iEnd; i++)
	{
		pRGB[i].rgbRed = pEntry[i].peRed;
		pRGB[i].rgbGreen = pEntry[i].peGreen;
		pRGB[i].rgbBlue = pEntry[i].peBlue;
		pRGB[i].rgbReserved = 0;
	}
	if (CreateHDC())
	{
		HBITMAP oldBM = SelectHBitmap(m_hDC, m_hBitmap);
		SetDIBColorTable(m_hDC, iStart, nEntries, pRGB);
#ifdef _DEBUG
		RGBQUAD tmp;
		for (int i=iStart; i < iEnd; i++)
		{
			GetDIBColorTable(m_hDC, i, 1, &tmp);
			ASSERT(tmp.rgbRed == pRGB[i].rgbRed);
			ASSERT(tmp.rgbGreen == pRGB[i].rgbGreen);
			ASSERT(tmp.rgbBlue == pRGB[i].rgbBlue);
		}
#endif

		SelectHBitmap(m_hDC, oldBM);
		DeleteHDC();
	}

}


void CDIB::CopyPalette(CPalette *pPal)
{
	ASSERT(pPal != NULL);
	int nColors = min(pPal->GetEntryCount(),GetNumClrEntries());

	if (nColors)
	{
		PALETTEENTRY *pData = (PALETTEENTRY *)malloc(nColors * sizeof(PALETTEENTRY));
		if (pData)
		{
			pPal->GetPaletteEntries(0,nColors,pData);
			SetPalette(0,nColors,pData); 
			free(pData);
		}
		else
			AfxThrowMemoryException();
	}
}

#if 1
RGBQUAD *CDIB::CopyColorTable(RGBQUAD *pRGB)
{
	UINT size = GetNumClrEntries() * sizeof(RGBQUAD);
	if (!size)
		return NULL;

	if (!pRGB)
	{
		pRGB = new RGBQUAD[size];
		ASSERT_NEW(pRGB);
	}
	memcpy(pRGB,GetClrTabAddress(),size);
	return pRGB;
}

RGBQUAD *CDIB::CreateMaskTable(RGBQUAD *pRGB,COLORREF colorref, RGBQUAD match, RGBQUAD nomatch, BOOL bMatchOnly)
{
	UINT nColors = GetNumClrEntries();
	UINT size = nColors * sizeof(RGBQUAD);
	if (!size)
		return NULL;

	if (!pRGB)
	{
		pRGB = new RGBQUAD[size];
		ASSERT_NEW(pRGB);
	}
	RGBQUAD *pOld = GetClrTabAddress();
	RGBQUAD *pNew = pRGB, *pSrc;;
    BYTE red = GetRValue(colorref);
	BYTE blue = GetBValue(colorref);
	BYTE green = GetGValue(colorref);


	for (UINT i = 0; i < nColors; i++,pOld++,pNew++)
	{
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

// TBD: this doesn't seem to work on 8-bit displays but I am not sure if
// I am just not handling the palettes correctly.
BOOL CDIB::DrawTransparent(HDC hdc, int dx, int dy, int sx, int sy, int sw, int sh,
						   RGBQUAD *pRGB, RGBQUAD *pWhite, RGBQUAD *pBlack, COLORREF rgbTransparent)
{
	ASSERT(0 < sw && sw <= GetWidth() && (sx + sw <= GetWidth()));
	ASSERT(0 < sh && sh <= GetHeight() && (sy + sh <= GetHeight()));
	ASSERT(m_hDC != NULL);
    BOOL bDrawn = FALSE;
    COLORREF oldBk, oldTx;


	ASSERT(pWhite != NULL);
	ASSERT(pBlack != NULL);
	ASSERT(pRGB != NULL);

    UINT nColors = GetNumClrEntries();
	SetDIBColorTable(m_hDC, 0, nColors, pWhite);
	oldBk = SetBkColor(hdc, RGB(0,0,0));          // 1s --> black (0x000000)
	oldTx = SetTextColor(hdc, RGB(255,255,255));    // 0s --> white (0xFFFFFF)
	bDrawn = BitBlt(hdc, dx, dy, sw, sh, m_hDC, sx, sy, SRCAND);

	SetDIBColorTable(m_hDC, 0, nColors, pBlack);
	SetBkColor(hdc, rgbTransparent);      // 1s --> transparent color
	SetTextColor(hdc, RGB(0,0,0));        // 0s --> black (0x000000)
	bDrawn = BitBlt(hdc, dx, dy, sw, sh, m_hDC, sx, sy, SRCPAINT);

	SetDIBColorTable(m_hDC, 0, nColors, pRGB);
	SetBkColor(hdc, oldBk);
	SetTextColor(hdc, oldTx);
	return bDrawn;
}
#endif

/*
** METHOD 
**   CDIB::CreateMask
**
** PARAMETERS
**   COLORREF rgbTransparent    -- rgb transparent color
**   HPALETTE hPalette          -- palette to use with this bitmap (TBD: is this necessary)
**
** DESCRIPTION
**   creates and returns a 1-bit per pixel mask as large as the 
**   dib that is 1s wherever the dib color matches the 
**   rgbTransparent color and 0s everywhere else.
*/
HBITMAP CDIB::CreateMask(COLORREF rgbTransparent, HPALETTE hPalette)
{
	BOOL bCreated = FALSE;
	if (CreateHDC())
	{
		HDC hdcMask = CreateCompatibleDC(m_hDC);
		if (hdcMask)
		{
			int width = GetWidth();
			int height = GetHeight();
			if (m_hMaskBitmap == NULL)
				m_hMaskBitmap = CreateBitmap(width,height,1,1,NULL); // monochrome?
	
			if (m_hMaskBitmap)
			{
				HPALETTE hPal;
				if (hPalette) 
				{
					hPal = SelectPalette(m_hDC, hPalette, FALSE);
					RealizePalette(m_hDC);
				}
	
				HBITMAP hBitmap = SelectHBitmap(hdcMask, m_hMaskBitmap);

#if 1
			    // we shouldn't have to do this!!!!!..
				// AND THIS WON'T WORK IF THE BITMAP DOES NOT HAVE A PALETTE
				RGBQUAD white,black;

				black.rgbRed = 0;
				black.rgbGreen = 0; 
				black.rgbBlue = 0; 
				black.rgbReserved = 0;

				white.rgbRed = 255; 
				white.rgbGreen = 255; 
				white.rgbBlue = 255; 
				white.rgbReserved = 0;

				UINT nColors = GetNumClrEntries();
				if (nColors)
				{
					RGBQUAD *pWhite = CreateMaskTable(NULL,rgbTransparent,white,black,FALSE);
					RGBQUAD *pColors = CopyColorTable(NULL);

					if (pWhite && pColors)
					{
						VERIFY(BitBlt(hdcMask, 0, 0, width, height, hdcMask, 0, 0, WHITENESS));
						SetDIBColorTable(m_hDC, 0, nColors, pWhite);
						SetBkColor(hdcMask, RGB(0,0,0));            // 1s --> black (0x000000)
						SetTextColor(hdcMask, RGB(255,255,255));    // 0s --> white (0xFFFFFF)
						VERIFY(BitBlt(hdcMask, 0, 0, width, height, m_hDC, 0, 0, SRCAND));
						SetDIBColorTable(m_hDC, 0, nColors, pColors);
						bCreated = TRUE;
					}
					delete pWhite;
					delete pColors;
				}
				else
				{
					// it's true color or hi color or it doesn't have a palette
					// TBD: what do we do? FOR NOW, make the mask completely opaque
					BitBlt(hdcMask, 0, 0, width, height, hdcMask, 0, 0, BLACKNESS);
					bCreated = TRUE;
				}
#else
				COLORREF old = SetBkColor(m_hDC, rgbTransparent);
				VERIFY(BitBlt(hdcMask,0, 0, width, height, m_hDC, 0, 0, SRCCOPY));
				old = SetBkColor(m_hDC, old);
				bCreated = TRUE;
#endif
				SelectHBitmap(hdcMask,hBitmap);

				if (hPalette) 
					SelectPalette(m_hDC, hPal, TRUE);
			}
			::DeleteDC(hdcMask);
		}
		DeleteHDC();
	}
	if (!bCreated) DeleteMask();
	return m_hMaskBitmap;
}



COLORREF CDIB::ReadColor(int x, int y, HPALETTE hPalette)
{
	COLORREF color = CLR_INVALID;
	if (CreateHDC())
	{
		HPALETTE hPal;
		if (hPalette) 
			hPal = SelectPalette(m_hDC, hPalette, TRUE);
		color = GetPixel(m_hDC, x, y);

		if (hPalette)
			SelectPalette(m_hDC, hPalette, TRUE);
		DeleteHDC();
	}
	return color;		
}

CPoint CDIB::GetHotSpot()
{
	// TBD: this is really for ArmyMen and is not part of
	// a standard DIB.  This may go away if ArmyMen decides to
	// go with an objectset data file that contains all the 
	// hot-spot and/or attribute information for each object.
	ASSERT(m_pBMI != NULL);
	return CPoint(m_pBMI->bmiHeader.biXPelsPerMeter,
	              m_pBMI->bmiHeader.biYPelsPerMeter);
}

template <class DATATYPE> inline void COPY_DATA(DATATYPE iShift,int iBytes,
	register int iLines,
	register BYTE *pSrc,register int iSrcInc,
	register BYTE *pDst,register int iDstInc)
{
	register DATATYPE *pTmpSrc,*pTmpDst;
	register int ix,dw = iBytes >> iShift;
	while (iLines--)
	{
		pTmpSrc = (DATATYPE *)pSrc;
		pTmpDst = (DATATYPE *)pDst;
		ix = dw;
		while (ix--)
		{
			*pTmpDst++ = *pTmpSrc++;
		}
		pSrc += iSrcInc;
		pDst += iDstInc;
	}

}

inline BOOL CDIB::InitCopy(int& sx, int& sy, CDIB *dst, int& dx, int& dy, int& dw, int& dh)
{
	if (dx < 0)
	{
		// clip left 
		sx -= dx;
		dw += dx;
		dx = 0;
	}

	if (dy < 0)
	{
		// clip top
		sy -= dy;
		dh += dy;
		dy = 0;
	}

	if (dw <= 0 || dh <= 0)
		return FALSE;

	ASSERT(IsSimpleDib());
	ASSERT(sx >= 0 && (sx + dw) <= GetWidth());
	ASSERT(sy >= 0 && (sy + dh) <= GetHeight());

	ASSERT(dst != NULL);
	ASSERT(dst->IsSimpleDib());

	int iClip = dst->GetWidth();
	if (dx + dw > iClip)
	{
		// clip right
		dw = iClip - dx;
		if (dw <= 0) return FALSE;
	}
	iClip = dst->GetHeight();
	if (dy + dh > iClip)
	{
		// clip bottom
		dh = iClip - dy;
		if (dh <= 0) return FALSE;
	}
	
    ASSERT(dx >= 0 && (dx + dw) <= dst->GetWidth());
	ASSERT(dy >= 0 && (dy + dh) <= dst->GetHeight());
	return TRUE;
}

/*
** METHOD
**   CDIB::Copy
**  
** PARAMETERS
**   int sx,sy -- location of upper left corner of source rectangle
**   CDIB *dst -- non-NULL pointer to compatible destination bitmap
**   int dx,dy -- location of upper left corner of destination rectangle
**   int dw,dh -- number of pixels wide/high to transfer
**
** DESCRIPTION
**    simplified bitblt function.  Copies the given source rectangle
**    to the destination rectangle.  Does not rely on the GDI BitBlt 
**    functionality.  Does not do any palette remapping. Does not do
**    any stretching. For now, assumes both bitmaps are
**    8-bit per pixel.
**
**    Does minimal clipping: assumes sx,sy,dw,dh is a completely legal
**    source rectangle but dx,dy,dw,dh may be all or partially contained
**    by destination bitmap.
*/
void CDIB::Copy(int sx, int sy, CDIB *dst, int dx, int dy, int dw, int dh)
{
	if (!InitCopy(sx,sy,dst,dx,dy,dw,dh))
		return;

	register BYTE *pSrc = GetBitsAddress(sx,sy);
	register int iSrcInc = GetLineIncrement();
    
	register BYTE *pDst = dst->GetBitsAddress(dx,dy);
    register int iDstInc = dst->GetLineIncrement();

	ASSERT(pSrc != NULL);
	ASSERT(pDst != NULL);
    
	if (((ULONG)pSrc & 3) || ((ULONG)pDst & 3) || (dw & 3) || (iSrcInc & 3) || (iDstInc & 3))
	{
		if (((ULONG)pSrc & 1) || ((ULONG)pDst & 1) || (dw & 1) || (iSrcInc & 1) || (iDstInc & 1))
		{
			// do byte copy
			COPY_DATA((BYTE)0,dw,dh,pSrc,iSrcInc,pDst,iDstInc);
		}
		else
		{
			// do word copy
			COPY_DATA((SHORT)1,dw,dh,pSrc,iSrcInc,pDst,iDstInc);
		}
	}
	else
	{
		// do long copy
		COPY_DATA((LONG)2,dw,dh,pSrc,iSrcInc,pDst,iDstInc);
	}
}


/*
** METHOD
**   CDIB::CopyOver
**  
** PARAMETERS
**   int sx,sy      -- location of upper left corner of source rectangle
**   CDIB *dst      -- non-NULL pointer to compatible destination bitmap
**   int dx,dy      -- location of upper left corner of destination rectangle
**   int dw,dh      -- number of pixels wide/high to transfer
**   UINT color     -- transparent color index (must be a valid paletteindex)
**
** DESCRIPTION
**    simplified copy over function.  Copies the given source rectangle
**    over the destination rectangle where any pixel in source matching 
**    the given color palette-index is assumed to be transparent.
**
**    Does not rely on the GDI BitBlt functionality.  Does not do any palette 
**    remapping. For now, assumes both bitmaps are 8-bit per pixel.
**
**    Does minimal clipping: assumes sx,sy,dw,dh is a completely legal
**    source rectangle but dx,dy,dw,dh may be all or partially contained
**    by destination bitmap.
*/
void CDIB::CopyOver(int sx, int sy, 
					CDIB *dst, int dx, int dy, int dw, int dh, UINT color)
{
	if (!InitCopy(sx,sy,dst,dx,dy,dw,dh))
		return;
	
	register BYTE *pSrc = GetBitsAddress(sx,sy);
	register int iSrcInc = GetLineIncrement();
    
	register BYTE *pDst = dst->GetBitsAddress(dx,dy);
    register int iDstInc = dst->GetLineIncrement();

	ASSERT(pSrc != NULL);
	ASSERT(pDst != NULL);

	register BYTE *pTmpSrc,*pTmpDst,index=color;
	register int ix,iw = dw;
	while (dh--)
	{
		pTmpSrc = pSrc;
		pTmpDst = pDst;
		ix = iw;
		while (ix--)
		{
			if (*pTmpSrc != index)	
			   *pTmpDst = *pTmpSrc;

			++pTmpSrc;
			++pTmpDst;
		}
		pSrc += iSrcInc;
		pDst += iDstInc;
	}
}



/*
** METHOD
**   CDIB::Stretch
**  
** PARAMETERS
**   int sx,sy -- location of upper left corner of source rectangle
**   int sw,sh -- number of source pixels wide/high
**   CDIB *dst -- non-NULL pointer to compatible destination bitmap
**   int dx,dy -- location of upper left corner of destination rectangle
**   int dw,dh -- number of destination pixels wide/high
**
** DESCRIPTION
**    simplified StretchBlt function.  Copies the given source rectangle
**    to the destination rectangle stretching as needed  Does not rely on
**    the GDI StretchBlt functionality.  Does not do any palette remapping.
**    Does not do any negative stretching/flipping. For now, assumes
**    both bitmaps are 8-bit per pixel.
**
**    Does minimal clipping: assumes sx,sy,sw,sh is a completely legal
**    source rectangle but dx,dy,dw,dh may be all or partially contained
**    by destination bitmap.
*/
void CDIB::Stretch(int sx, int sy, int sw, int sh, 
				   CDIB *dst, int dx, int dy, int dw, int dh)
{
	if (sw == dw && sh == dh)
	{
		Copy(sx,sy,dst,dx,dy,dw,dh);
		return;
	}
	ASSERT(IsSimpleDib());
	ASSERT(sx >= 0 && (sx + sw) <= GetWidth());
	ASSERT(sy >= 0 && (sy + sh) <= GetHeight());

	ASSERT(dst != NULL);
	ASSERT(dst->IsSimpleDib());
	
	register BYTE *pSrc = GetBitsAddress(sx,sy);
	int iSrcInc = GetLineIncrement();

	register BYTE *pTmpSrc,*pTmpDst;
	register int ix,ixsum,iysum = -dh >> 1;
	register int dxclip,dwclip,iy = dh;

	// clip top
	while (dy < 0)
	{
		dy++;
		iy--;
		iysum += sh;
		while (iysum >= dh)
		{
			iysum -= dh;
			pSrc += iSrcInc; // go to the next source line
		}
	}
	// clip bottom
	iy = min(iy, dst->GetHeight() - dy);
	if (iy <= 0)
		return;

	// clip sides
	ix = dst->GetWidth();
	if (dx < 0)
	{
		dxclip = -dx;
		dx = 0;
		dwclip = min(dw - dxclip, ix);
	}
	else
	{
		dxclip = 0;
	    dwclip = min(dw, ix - dx);
    }
	if (dwclip <= 0)
		return;

	register BYTE *pDst = dst->GetBitsAddress(dx,dy);
    int iDstInc = dst->GetLineIncrement();

	if (sw == dw)
	{
		// we're just stretching in the y direction
		while (iy-- > 0)
		{
			iysum += sh;
			while (iysum >= dh)
			{
				iysum -= dh;
				pSrc += iSrcInc; // go to the next source line
			}
			// copy the current source line to the destination
			ix = dwclip;
			pTmpSrc = pSrc + dxclip;
			pTmpDst = pDst;
			while (ix-- > 0)
			{
				*pTmpDst++ = *pTmpSrc++;
			}
			pDst += iDstInc;
		}
	}
	else
	{
		// do a full stretch
		while (iy-- > 0)
		{
			iysum += sh;
			while (iysum >= dh)
			{
				iysum -= dh;
				pSrc += iSrcInc; // go to the next source line
			}
			// stretch the current source line
			pTmpSrc = pSrc;
			pTmpDst = pDst;
			ixsum = -dw >> 1;
			ix = dxclip;
			while (ix-- > 0)
			{
				ixsum += sw;
				while (ixsum >= dw)
				{
					ixsum -= dw;
					pTmpSrc++;
				}
			}
            ix = dwclip;
			while (ix-- > 0)
			{
				ixsum += sw;
				while (ixsum >= dw) 
				{
					ixsum -= dw;
					pTmpSrc++;
				}
				*pTmpDst++ = *pTmpSrc;
			}
		    pDst += iDstInc;
		}
	}
}

/*
** METHOD
**   CDIB::StretchOver
**  
** PARAMETERS
**   int sx,sy  -- location of upper left corner of source rectangle
**   int sw,sh  -- number of source pixels wide/high
**   CDIB *dst  -- non-NULL pointer to compatible destination bitmap
**   int dx,dy  -- location of upper left corner of destination rectangle
**   int dw,dh  -- number of destination pixels wide/high
**   UINT color -- transparent color index
**   
** DESCRIPTION
**    Copies the given source rectangle over the given destination rectangle
**    stretching as needed  Does not rely on the GDI StretchBlt functionality.
**    Does not do any palette remapping. Does not do any negative stretching
**    flipping. For now, assumes both bitmaps are 8-bit per pixel.
**    Assumes any source pixel matching the given color index is transparent
**    and should leave the corresponding destination pixel untouched.
**
**    Does minimal clipping: assumes sx,sy,sw,sh is a completely legal
**    source rectangle but dx,dy,dw,dh may be all or partially contained
**    by destination bitmap.
*/
void CDIB::StretchOver(int sx, int sy, int sw, int sh, 
		   CDIB *dst, int dx, int dy, int dw, int dh, UINT color)
{
	if (sw == dw && sh == dh)
	{
		CopyOver(sx,sy,dst,dx,dy,dw,dh,color);
		return;
	}
	ASSERT(IsSimpleDib());
	ASSERT(sx >= 0 && (sx + sw) <= GetWidth());
	ASSERT(sy >= 0 && (sy + sh) <= GetHeight());

	ASSERT(dst != NULL);
	ASSERT(dst->IsSimpleDib());
	
	register BYTE *pSrc = GetBitsAddress(sx,sy);
	int iSrcInc = GetLineIncrement();
   
	register BYTE *pTmpSrc,*pTmpDst;
	register int ix,ixsum,iysum = -dh >> 1;
	register int dxclip,dwclip,iy = dh;

	// clip top
	while (dy < 0)
	{
		dy++;
		iy--;
		iysum += sh;
		while (iysum >= dh)
		{
			iysum -= dh;
			pSrc += iSrcInc; // go to the next source line
		}
	}
	// clip bottom
	iy = min(iy, dst->GetHeight() - dy);
	if (iy <= 0)
		return;

	// clip sides
	ix = dst->GetWidth();
	if (dx < 0)
	{
		dxclip = -dx;
		dx = 0;
		dwclip = min(dw - dxclip, ix);
	}
	else
	{
		dxclip = 0;
	    dwclip = min(dw, ix - dx);
    }
	if (dwclip <= 0)
		return;

	register BYTE *pDst = dst->GetBitsAddress(dx,dy);
    int iDstInc = dst->GetLineIncrement();
	register BYTE index = color;

	if (sw == dw)
	{
		// we're just stretching in the y direction
		while (iy--)
		{
			iysum += sh;
			while (iysum >= dh)
			{
				iysum -= dh;
				pSrc += iSrcInc; // go to the next source line
			}
			// copy the current source line over the destination
			ix = dwclip;
			pTmpSrc = pSrc + dxclip;
			pTmpDst = pDst;
			while (ix--)
			{
				if (*pTmpSrc != index)
                   *pTmpDst = *pTmpSrc;

				++pTmpDst;
				++pTmpSrc;
			}
			pDst += iDstInc;
		}
	}
	else
	{
		// do a full stretch
		while (iy--)
		{
			iysum += sh;
			while (iysum >= dh)
			{
				iysum -= dh;
				pSrc += iSrcInc; // go to the next source line
			}
			// stretch the current source line over destination 
			pTmpSrc = pSrc;
			pTmpDst = pDst;
			ixsum = -dw >> 1;
			ix = dxclip;
			while (ix--)
			{
				ixsum += sw;
				while (ixsum >= dw) 
				{
					ixsum -= dw;
					pTmpSrc++;
				}
			}
			ix = dwclip;
			while (ix--)
			{
				ixsum += sw;
				while (ixsum >= dw) 
				{
					ixsum -= dw;
					pTmpSrc++;
				}
				if (*pTmpSrc != index)
					*pTmpDst = *pTmpSrc;
				++pTmpDst;
			}
		    pDst += iDstInc;
		}
	}
}

void CDIB::Fill(int sx,int sy,int sw,int sh, UINT color)
{
	ASSERT(IsSimpleDib());
	ASSERT(sx >= 0 && (sx + sw) <= GetWidth());
	ASSERT(sy >= 0 && (sy + sh) <= GetHeight());
	
	register BYTE *pSrc = GetBitsAddress(sx,sy);
	register int iSrcInc = GetLineIncrement();
	ASSERT(pSrc != NULL);

	register BYTE *pTmpSrc,index=color;
	register int ix,iw = sw;
	while (sh--)
	{
		pTmpSrc = pSrc;
		ix = iw;
		while (ix--)
		{
			*pTmpSrc++ = index;
		}
		pSrc += iSrcInc;
	}
}



void CDIB::Remap(BYTE *pTable)
{
	ASSERT(IsSimpleDib());
	ASSERT(pTable != NULL);

	register BYTE *pSrc = GetBitsAddress(0,0);
	register int iSrcInc = GetLineIncrement();
	register BYTE *pTmpSrc;
	register int ix,iw = GetWidth();
    register int ih = GetHeight();
	while (ih--)
	{
		pTmpSrc = pSrc;
		ix = iw;
		while (ix--)
		{
			*pTmpSrc = pTable[*pTmpSrc];
			++pTmpSrc;
		}
		pSrc += iSrcInc;
	}
	
}


