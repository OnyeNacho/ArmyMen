//-----------------------------------------------------------------
// DIBPalette Object
// C++ Header - DIBPal.h
//-----------------------------------------------------------------

#ifndef __DIBPAL_H__
#define __DIBPAL_H__

//-----------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------
class CDIBitmap;

//-----------------------------------------------------------------
// CDIBPalette Class - DIBPalette Object
//-----------------------------------------------------------------
class CDIBPalette : public CPalette
{
  // Public Constructor(s)/Destructor
public:
                CDIBPalette();
                CDIBPalette(const CDIBitmap&);
  virtual       ~CDIBPalette();

  // Public Methods
public:
  BOOL          Create(const CDIBitmap&);
  DWORD         GetNumColors() const;
  BOOL          MakeIdentity();

public:
	RGBQUAD		ColorTable[256];
};

#endif
