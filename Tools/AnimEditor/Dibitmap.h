//-----------------------------------------------------------------
// DIBimap Object
// C++ Header - DIBitmap.h
//-----------------------------------------------------------------

#ifndef __DIBITMAP_H__
#define __DIBITMAP_H__

//-----------------------------------------------------------------
// Inclusions
//-----------------------------------------------------------------
#include <MMSystem.h>

//-----------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------
class CDIBPalette;

//-----------------------------------------------------------------
// CDIBitmap Class - DIB Object
//-----------------------------------------------------------------
class CDIBitmap : public CObject
{
  // Public Constructor(s)/Destructor
public:
                CDIBitmap();
                CDIBitmap(CDC* pdc, const CString& sFileName, BOOL
                  bRemapToPal = TRUE);
                CDIBitmap(CDC* pdc, UINT uiResID, HMODULE hmod =
                  AfxGetInstanceHandle(), BOOL bRemapToPal = TRUE);
  virtual       ~CDIBitmap();

  // Public Methods
public:
	BOOL	Create(CDC* pdc, const CString& sFileName, const CString &sPath = "", BOOL bRemapToPal = TRUE, BOOL bMask = TRUE);
	BOOL	Create(CDC* pdc, UINT uiResID, HMODULE hmod = AfxGetInstanceHandle(), BOOL bRemapToPal = TRUE, BOOL bMask = TRUE);
	void	Draw(CDC* pdc, CPoint ptDest = CPoint(0, 0), BOOL bInstallPalette = TRUE);
	void	Draw(CDC* pdc, CPoint ptDest, CRect rcSrc, BOOL bInstallPalette = TRUE);
//	void	DrawTransparent( CDC* pdc, COLORREF& colorTransparent, CPoint ptDest = CPoint( 0, 0 ), BOOL bInstallPal = TRUE );
//	void	DrawTransparent( CDC* pdc, COLORREF& colorTransparent, CPoint ptDest, CRect rcSrc, BOOL bInstallPal = TRUE );
  
    void	DrawTransparent(CDC* pdc, int dx, int dy, CDC* pdcUser, int sx, int sy, int sw, int sh);
    void	DrawTransparent(CDC* pdc, int dx, int dy, CDC* pdcUser = NULL)	{
		DrawTransparent(pdc, dx, dy, pdcUser, 0, 0, GetWidth(), GetHeight());
	}
	
	void	Blit(BYTE *pDest, int nDestPitch, int x, int y, int nWidth, int nHeight) const;
	BOOL	GetPaletteEntries(PALETTEENTRY vpeToBeFilled[]) const;
	UINT	GetTransColorIndex() const;
	LONG	GetWidth() const;
	LONG	GetHeight() const;
	DWORD	GetImageSize() const;
	DWORD	GetNumColors() const;
	LONG	GetLineSize() const;

	LONG	GetHotspotX() const;
	LONG	GetHotspotY() const;
	void	SetHotspotX( LONG lValNew );
	void	SetHotspotY( LONG lValNew );

	static void   CleanupPalette();
	BOOL	SetOriginalPalette();

	BOOL	SaveHotspot( const CString &sFileNameFullPath ) const;

	//	xxx
	//	Added by AJW...
	void		DrawZoomed(CDC* pdc, CPoint ptDest, int iZoom, DWORD dwRasterOp = SRCCOPY, BOOL bInstallPal = TRUE);
	void		DrawZoomed(CDC* pdc, CPoint ptDest, CRect rcSrc, int iZoom, DWORD dwRasterOp = SRCCOPY, BOOL bInstallPal = TRUE );
	static CDIBPalette*	GetOriginalPalette() { return m_pOriginalPalette; }
	static CDIBPalette*	GetPalette() { return m_pPalette; }
	RGBQUAD*	GetPaletteColors();
	CPoint		Crop( CDC* pDC );
	BYTE*		GetBits()	{ return m_pBits; }
	BOOL		MakeMappingToOriginal(BYTE byMap[256]);

  // Protected Methods
protected:
	void		Free();
	BOOL		InstallPalette(CDC* pdc);
	BOOL		RemapToPalette();
	HBITMAP		CreateMask(CDC* pdc, COLORREF rgbTransparent);
	void		DeleteMask();
	RGBQUAD		*CopyColorTable(RGBQUAD *pRGB) const;
	RGBQUAD		*CreateMaskTable(RGBQUAD *pRGB, COLORREF colorref, RGBQUAD match, RGBQUAD nomatch, BOOL bMatchOnly);

	BOOL		SaveHotspot_ReadAndVerifyOneValue( CFile& fileDIB, const CString& csFileNameFullPath, void* pItem, DWORD dwItemSize ) const;

  // Protected Data
protected:
	static CDIBPalette* m_pPalette;
	static CDIBPalette* m_pOriginalPalette;

	PBITMAPINFO         m_pbiInfo;
	PBYTE               m_pBits;
	LONG                m_LineSize;

// added by NAR
  LONG                m_hotspotx;
  LONG                m_hotspoty;
  HBITMAP             m_hMaskBitmap;

public:
  HBITMAP             m_hBitmap;	//	xxx publicized by AJW
  LONG				  m_shadowsize;
  PBYTE				  m_pShadow;

  // Friend Classes
  friend class CDIBPalette;
};

//-----------------------------------------------------------------
// CDIBitmap Inline Public Methods
//-----------------------------------------------------------------
inline LONG
CDIBitmap::GetWidth() const
{
 // ASSERT(m_pbiInfo);
	if (!m_pbiInfo)
		return 0;
	else
		return m_pbiInfo->bmiHeader.biWidth;
}

inline LONG
CDIBitmap::GetHeight() const
{
 // ASSERT(m_pbiInfo);
	if (!m_pbiInfo)
		return 0;
	else
		return m_pbiInfo->bmiHeader.biHeight;
}

inline DWORD
CDIBitmap::GetImageSize() const
{
 // ASSERT(m_pbiInfo);
	if (!m_pbiInfo)
		return 0;
	else
		return m_pbiInfo->bmiHeader.biSizeImage;
}

inline LONG
CDIBitmap::GetLineSize() const
{
  return m_LineSize;
}

inline LONG
CDIBitmap::GetHotspotX() const
{
  return m_hotspotx;
}

inline LONG
CDIBitmap::GetHotspotY() const
{
  return m_hotspoty;
}

inline void CDIBitmap::SetHotspotX( LONG lValNew )
{
	m_hotspotx = lValNew;
}

inline void CDIBitmap::SetHotspotY( LONG lValNew )
{
	m_hotspoty = lValNew;
}

#endif
