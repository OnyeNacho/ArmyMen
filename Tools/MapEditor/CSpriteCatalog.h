//	CSpriteCatalog.h

//	CSpriteCatalog - simpler version of AnimEditor's CAnimEditorDoc, for use in games.

#ifndef CSpriteCatalog_H
#define CSpriteCatalog_H

#include "CSpriteSequence.h"

class CSpriteCatalog : public CObject
{
public:
	CSpriteCatalog(); 
	DECLARE_SERIAL(CSpriteCatalog)
	virtual ~CSpriteCatalog();

// Attributes
protected:
	//	Used for RLE export and storage after import:
	BYTE*											pRLEPixels;		//	Array of bytes allocated for RLE image storage.
	int												iRLEPixelCount;	//	Number of bytes of RLE data.

public:
	CString											csName;			//	User-assigned name of catalog.
	int												iSeqs;			//	Number of sprite sequences.
	CTypedPtrArray< CObArray, CSpriteSequence* >	arSeqs;			//	Array of sprite sequences.


// Operations
public:
	virtual			void Serialize(CArchive& ar);
	BOOL			RLEFastBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines );
	BOOL			RLEFastBltHFlipped( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, int iWidth );
	BOOL			RLEFastBltClipped( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, const CRect* rcSrc );
	BOOL			RLEFastBltHFlipClipped( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, long lSrcWidth, const CRect* rcSrc );

	void			DrawSprite( BYTE *pDestStart, long lPitchDest, int iDestX, int iDestY, DWORD dwDestWidth, DWORD dwDestHeight, CSpriteSequence* pSeq, int iFrame, BOOL bHorizFlip);

};

#endif