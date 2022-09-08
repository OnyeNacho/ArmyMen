//	CSpriteCatalog.h

//	CSpriteCatalog - simpler version of AnimEditor's CAnimEditorDoc, for use in games.

#ifndef CSpriteCatalog_H
#define CSpriteCatalog_H

#include "CSpriteSequence.h"
#include <ddraw.h>

#ifdef ANIMEDITORDOC_VERSION
class CAnimEditorDoc;
#endif

struct BITMAPINFO_256
{
  BITMAPINFOHEADER  bmiHeader;
  RGBQUAD           bmiColors[256];
};

class CDIBitmap;

class CSpriteCatalog : public CObject
{
public:
	CSpriteCatalog();
#ifdef ANIMEDITORDOC_VERSION
	CSpriteCatalog( CAnimEditorDoc* pDocToCopy, BOOL bRLE );
#endif
	DECLARE_SERIAL(CSpriteCatalog)
	
	virtual ~CSpriteCatalog();

// Attributes
protected:
	//	Used for normal export:
//	CBitmap*		pbmStrip;
//	CPalette*		m_ppalStrip;
//	int				iStripWidth;
//	int				iStripHeight;
	int				m_iNumBitmaps;
	int				m_iMaxSize;
	CDIBitmap**		m_pbmArray;

//	int	iDarkTestxxx;
//	int iDarkTestDeltaxxx;

#ifndef	ANIMEDITORDOC_VERSION
	//	Used for storage of catalogs exported normally:
	LPDIRECTDRAWSURFACE		lpDDSStrip;		//	Storage surface for strip bitmap.
	LPDIRECTDRAWPALETTE		lpDDPalStrip;	//	ppalStrip, converted into a directdraw palette.
	//[xxx conflicts with the concept of using lpDDPalette, below]
#endif

	//	Used for RLE export and storage after import:
//	BYTE*	pRLEPixels;		//	Array of bytes allocated for RLE image storage.
//	int		iRLEPixelCount;	//	Number of bytes of RLE data.

public:
	CString											csName;			//	User-assigned name of catalog.
	int												iSeqs;			//	Number of sprite sequences.
	CTypedPtrArray< CObArray, CSpriteSequence* >	arSeqs;			//	Array of sprite sequences.
#ifndef	ANIMEDITORDOC_VERSION
	LPDIRECTDRAW									lpDDObject;
	LPDIRECTDRAWPALETTE								lpDDPalette;
#endif

	BOOL											bSerializeRLE;	//	Flag used by serialize, set by caller.
#ifdef ANIMEDITORDOC_VERSION
//	CMap< CString, LPCSTR, int, int >				mapCelStartPos;	//	Map of cel image starting byte offsets in pRLEPixels, 
																	//	used before serializing out only.
#endif

// Operations
protected:
//	int			MemoryWriteBMP_RLE( BYTE*& pDest, const BYTE* pSrc, int iPitchSrc, 
	int			MemoryWriteBMP_RLE( BYTE* pRLE, const BYTE* pSrc, int iPitchSrc, 
										int iWidth, int iHeight, BYTE qTransparentIndex );
public:
	virtual void	Serialize( CArchive& ar );
#ifdef ANIMEDITORDOC_VERSION
//	void			Initialize( CBitmap* pBMP, CPalette* pPal, int iStripWidth, int iStripHeight );
	void			Initialize( CAnimEditorDoc* pDoc );
//	void			Initialize_RLE( CAnimEditorDoc* pDoc );
#endif
//	BOOL			WriteBMP( CArchive& ar, CBitmap* pBMP, CPalette* pPal, int iWidth, int iHeight );
	BOOL			WriteBMPs( CArchive& ar );
//	BOOL			WriteBMP_RLE( CArchive& ar, CBitmap* pBMP, int iWidth, int iHeight, BYTE qTransparentIndex );
//	BOOL			ReadBMP( CFile* pfileBMP, CBitmap** ppBMP, CPalette** ppPal, int& iWidth, int& iHeight );
#ifndef ANIMEDITORDOC_VERSION
	BOOL			ReadBMP( CArchive& ar, LPDIRECTDRAW lpDDObject, LPDIRECTDRAWPALETTE lpDDPalette );
//	void			PrepareSurface( LPDIRECTDRAW lpDDObject, LPDIRECTDRAWSURFACE lpDDSample );
	void			DrawSprite( LPDIRECTDRAWSURFACE lpDDSTarget, int iDestX, int iDestY, CSpriteSequence* pSeq, int iFrame, BOOL bHorizFlip, int iLightLevel );

	BOOL			RLEFastBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines );
	BOOL			RLEFastBltHFlipped( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, int iWidth );
	BOOL			RLEFastBltClipped( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, const CRect* rcSrc );

	BOOL			RLEXBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, int iPalette );
	BOOL			RLEXBltHFlipped( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, int iWidth, int iPalette );

	BOOL			RLEBiXBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, bixlat* pbixlatPal );
	BOOL			RLEBiXBltHFlipped( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines, int iWidth, bixlat* pbixlatPal);

	BOOL			RLEInvisBlt( void* pDestStart, long lPitchDest, const BYTE* pSrcStart, int iLines );

#endif
};

#endif