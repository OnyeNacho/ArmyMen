//-----------------------------------------------------------------
// DIBPalette Object
// C++ Source - DIBPal.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------
#include "StdAfx.h"
//-----------------------------------------------------------------
#include "DIBPal.h"
#include "DIBitmap.h"

//-----------------------------------------------------------------
// MFC Debugging Support
//-----------------------------------------------------------------
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------
// CDIBPalette Public Constructor(s)/Destructor
//-----------------------------------------------------------------
CDIBPalette::CDIBPalette()
  : CPalette()
{
}

CDIBPalette::CDIBPalette(const CDIBitmap &dib)
  : CPalette()
{
  Create(dib);
}

CDIBPalette::~CDIBPalette()
{
}

//-----------------------------------------------------------------
// CDIBPalette Public Methods
//-----------------------------------------------------------------
BOOL
CDIBPalette::Create(const CDIBitmap &dib)
{
  if (dib.m_pbiInfo == NULL)
    return FALSE;

  // Get the number of colors
  DWORD dwColors = dib.GetNumColors();
  if (0 == dwColors)
    return FALSE;

  // Build a logical palette from the color table
  PLOGPALETTE pLogPal = (PLOGPALETTE)new BYTE[sizeof(LOGPALETTE) +
    dwColors * sizeof(PALETTEENTRY)];
  if (pLogPal == NULL)
    return FALSE;
  pLogPal->palVersion = 0x300;
  pLogPal->palNumEntries = (WORD)dwColors;
  dib.GetPaletteEntries(pLogPal->palPalEntry);
  BOOL bRetVal = CreatePalette(pLogPal);
  delete [] pLogPal;

  dib.CopyColorTable(ColorTable);

  return bRetVal;
}

BOOL CDIBPalette::MakeIdentity()
{
  // Create a screen DC
  CDC dcScreen;
  dcScreen.CreateCompatibleDC(NULL);

  // Make sure the graphics device is palettized
  if (!(dcScreen.GetDeviceCaps(RASTERCAPS) & RC_PALETTE))
    return FALSE;

  // Make sure the graphics device is in 256 color mode
  int nNumColors = dcScreen.GetDeviceCaps(NUMCOLORS);
  if ((nNumColors < 0) || (nNumColors > 256))
    return FALSE;

  // Force a reset of the system palette
  ::SetSystemPaletteUse(dcScreen.GetSafeHdc(), SYSPAL_NOSTATIC);
  ::SetSystemPaletteUse(dcScreen.GetSafeHdc(), SYSPAL_STATIC);

  // Realize and select the palette
  CPalette* ppalOld = dcScreen.SelectPalette(this, FALSE);
  dcScreen.RealizePalette();
  dcScreen.SelectPalette(ppalOld, FALSE);

  // Get the system palette entries
  PALETTEENTRY vpe[256];
  int nPalEntries = dcScreen.GetDeviceCaps(SIZEPALETTE);
  ::GetSystemPaletteEntries(dcScreen.GetSafeHdc(), 0, nPalEntries, vpe);

  // Set the palette entries to the system palette
  for (int i = 0; i < nNumColors/2 ;i++)
    vpe[i].peFlags = vpe[nPalEntries - 1 - i].peFlags = 0;
  for (; i < nPalEntries - nNumColors/2; i++)
    vpe[i].peFlags = PC_NOCOLLAPSE;
  ResizePalette(nPalEntries);
  SetPaletteEntries(0, nPalEntries, vpe);

	//	Turn PALETTEENTRYs into RGBQUADs.
	for( i = 0; i < 256; i++ )	{
		ColorTable[i].rgbRed = vpe[ i ].peRed;
		ColorTable[i].rgbBlue = vpe[ i ].peBlue;
		ColorTable[i].rgbGreen = vpe[ i ].peGreen;
	}

  return TRUE;
}

DWORD
CDIBPalette::GetNumColors() const
{
  // Get the number of entries in the palette
  DWORD dwNumColors = 0;
  if (!GetObject(sizeof(dwNumColors), &dwNumColors))
    TRACE("CDIBPalette::GetNumColors failed!");

  return dwNumColors;
}
