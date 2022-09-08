// dibpal.h : header file
//
// CDIBPal class
//

#ifndef __DIBPAL__
#define __DIBPAL__

#include "dib.h"

class CDIBPal : public CPalette
{
public:
    CDIBPal();
    ~CDIBPal();
    BOOL Create(CDIB *pDIB);            // Create from a DIB.
    void Draw(CDC* pDC, CRect* pRect, BOOL bBkgnd = FALSE); 
	// serialize...
};

#endif // __DIBPAL__

