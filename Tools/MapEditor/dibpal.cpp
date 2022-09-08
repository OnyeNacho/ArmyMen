// dibpal.cpp : implementation file
//

#include "stdafx.h"
#include "dibpal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBPal

CDIBPal::CDIBPal()
{
}

CDIBPal::~CDIBPal()
{
}

// Create a palette from the color table in a DIB.
BOOL CDIBPal::Create(CDIB* pDIB)
{
    DWORD dwColors = pDIB->GetNumClrEntries();
    // Check to see whether the DIB has a color table.
    if (!dwColors) {
        TRACE("No color table");   
        return FALSE;
    }

    // Get a pointer to the RGB quads in the color table.
    RGBQUAD* pRGB = pDIB->GetClrTabAddress();

    // Allocate a logical palette and fill it with the color table info.
    LOGPALETTE* pPal = (LOGPALETTE*) malloc(sizeof(LOGPALETTE) 
                     + dwColors * sizeof(PALETTEENTRY));
    if (!pPal) {
        TRACE("Out of memory for logical palette");
        return FALSE;
    }
    pPal->palVersion = 0x300;              // Windows 3.0
    pPal->palNumEntries = (WORD) dwColors; // Table size
    for (DWORD dw=0; dw<dwColors; dw++) {
        pPal->palPalEntry[dw].peRed = pRGB[dw].rgbRed;
        pPal->palPalEntry[dw].peGreen = pRGB[dw].rgbGreen;
        pPal->palPalEntry[dw].peBlue = pRGB[dw].rgbBlue;
        pPal->palPalEntry[dw].peFlags = PC_NOCOLLAPSE; // TBD: was 0
    }
    BOOL bResult = CreatePalette(pPal);
    free(pPal);
    return bResult;
}


/////////////////////////////////////////////////////////////////////////////
// CDIBPal commands

void CDIBPal::Draw(CDC* pDC, CRect* pRect, BOOL bBkgnd)
{
    int iColors = GetEntryCount();
    CPalette* pOldPal = pDC->SelectPalette(this, bBkgnd);
    pDC->RealizePalette();
    int i, j, top, left, bottom, right;
    for (j=0, top=0; j<16 && iColors; j++, top=bottom) {
        bottom = (j+1) * pRect->bottom / 16 + 1;
        for (i=0, left=0; i<16 && iColors; i++, left=right) {
            right = (i+1) * pRect->right / 16 + 1;
            CBrush br (PALETTEINDEX(j * 16 + i));
            CBrush* brold = pDC->SelectObject(&br);
            pDC->Rectangle(left-1, top-1, right, bottom);
            pDC->SelectObject(brold);
            iColors--;
        }
    }
    pDC->SelectPalette(pOldPal, FALSE);
}


