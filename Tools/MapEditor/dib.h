// dib.h : header file
//
// CDIB class
//
#ifndef __DIB__
#define __DIB__
#include "mmsystem.h"
#include "mymacros.h"

#ifndef C1_TRANSPARENT
    #define CAPS1           94          /* other caps */
    #define C1_TRANSPARENT  0x0001      /* new raster cap */
    #define NEWTRANSPARENT  3           /* use with SetBkMode() */

    #define QUERYROPSUPPORT 40          /* use to determine ROP support */
#endif  /* ifndef C1_TRANSPARENT */


class CDIB : public CObject
{
public:
	COLORREF ReadColor(int x, int y, HPALETTE hPalette);
    CDIB();  // for serialization only; TBD: protected?
    ~CDIB();

	// color/palette functions
    RGBQUAD* GetClrTabAddress()					  // Pointer to color table	
    {
		return (LPRGBQUAD)(((BYTE*)(m_pBMI)) + sizeof(BITMAPINFOHEADER));
	} 
	void CopyPalette(CPalette *pPal);
	void SetPalette(int iStart, int nEntries, PALETTEENTRY *pEntry);

	// masking functions 
	HBITMAP CreateMask(COLORREF rgbTransparent, HPALETTE hPalette);
	void DeleteMask();

    void DrawTrueMask(HDC hdcDst, const RECT& dstRect, HDC hdcTmp);
    void DrawTrueMask(HDC hdcDst, int dx, int dy, HDC hdcTmp, int sx, int sy, int sw, int sh);
    void DrawTrueMask(HDC hdcDst, int dx, int dy, HDC hdcTmp)
	{
		DrawTrueMask(hdcDst, dx, dy, hdcTmp, 0, 0, GetWidth(), GetHeight());
	}

	// masking based on color tables 
	RGBQUAD *CreateMaskTable(RGBQUAD *pRGB, COLORREF color, RGBQUAD match, RGBQUAD nomatch,BOOL bMatchOnly);
    RGBQUAD *CopyColorTable(RGBQUAD *pRGB);
	virtual BOOL DrawTransparent(HDC hdc, int dx, int dy, int sx, int sy, int sw, int sh, 
		RGBQUAD *pRGBColors,RGBQUAD *pRGBWhite, RGBQUAD *pRGBBlack,COLORREF rgbTransparent);


	// attributes
    BITMAPINFO* GetBitmapInfoAddress()
        {return m_pBMI;}                          // Pointer to bitmap info
    BYTE* GetBitsAddress()
        {return m_pBits;}                         // Pointer to the bits
	BYTE * GetBitsAddress(int x,int y);
	HBITMAP GetHBitmap() { return m_hBitmap; }    // may be NULL
	BYTE *GetTileStart(int iTileWidth, int iTileHeight, int iTile);       
    int GetNumClrEntries();                       // Number of color table entries
	int GetLineSize();                            // Number of bytes per bitmap line
	int GetLineIncrement() { return DibBottomUp() ? -GetLineSize() : GetLineSize(); }
    virtual int GetWidth() { return DibWidth(); }   // Image width
    virtual int GetHeight() { return abs(DibHeight());}  // Image height
	virtual int GetDepth()  { return DibDepth(); }       // Image depth
	virtual DWORD GetCompression() 
	{
		return (m_pBMI ? m_pBMI->bmiHeader.biCompression : 0);
	}
	virtual CPoint GetHotSpot();                         // For ArmyMen
    virtual BOOL Create(int iWidth, int iHeight, int iDepth, RGBQUAD *pRGB=NULL); // Create a new  DIB
   
	// Archive I/O
	virtual void Load(CArchive& ar);	
	virtual void Save(CArchive& ar);       

    // File I/O
	// Note we have to have both versions of this stupid stuff because
	// it is not legal to use the CArchive file pointer directly and we need to
	// load/save to both an archive and a file.
    virtual BOOL Save(CFile *fp);
    virtual BOOL Load(CFile *fp);

	// drawing: no mask or tables required
    virtual BOOL Draw(HDC hdc, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh);
	virtual BOOL Draw(HDC hdc, int dx, int dy, int sx, int sy, int sw, int sh);

#ifdef CAPS1
	// drawing with transparency: requires GetDevicesCaps(hdc, CAPS1) & C1_TRANSPARENT
    virtual BOOL DrawC1Transparent(HDC hdc, int dx, int dy, HDC hdcTmp, 
		         int sx, int sy, int sw, int sh, COLORREF rgbTransparent);

	virtual BOOL DrawC1Transparent(HDC hdc, RECT& dstRect, HDC hdcTmp,
		         COLORREF rgbTransparent);
#endif

	// custom copy and stretch functions
	BOOL IsSimpleDib()
	{
		return (GetDepth() == 8 && GetCompression() == BI_RGB);
	}
	void Copy(int sx, int sy, CDIB *dst, int dx, int dy, int dw, int dh);
	void CopyOver(int sx, int sy, CDIB *dst, int dx, int dy, int dw, int dh, UINT color);
	void Stretch(int sx, int sy, int sw, int sh, CDIB *dst, int dx, int dy, int dw, int dh);
	void StretchOver(int sx, int sy, int sw, int sh, CDIB *dst, int dx, int dy, int dw, int dh, UINT color);
	void Fill(int sx,int sy,int sw,int sh, UINT color);
	COLORREF GetColor(int iColor);
	void Remap(BYTE *pTable);

	// utility: TBD: are these really necessary?
	HDC CreateHDC(HDC hdc = NULL);
	HDC GetHDC() { return m_hDC; }
	void DeleteHDC();
    void DeleteContents();

protected:
	HDC m_hDC;
	UINT m_nRefHDC;
	HBITMAP m_hOldBitmap;
	HBITMAP m_hBitmap;
	HBITMAP m_hMaskBitmap;      // Optional pointer to 1-bit mask
    BITMAPINFO* m_pBMI;         // Pointer to BITMAPINFO struct
    BYTE* m_pBits;              // Pointer to the bits

	inline BOOL InitCopy(int& sx, int& sy, CDIB *dst, int& dx, int& dy, int& dw, int& dh);

private:
	void DestroyHBitmap();
    int DibWidth()
	{ return m_pBMI ? m_pBMI->bmiHeader.biWidth : 0;}
    int DibHeight() // Note: this will be negative if the dib is top-down
	{ return m_pBMI ? m_pBMI->bmiHeader.biHeight : 0;}
	int DibDepth()
	{ return m_pBMI ? m_pBMI->bmiHeader.biBitCount : 0; }
	BOOL DibBottomUp()
	{
		return m_pBMI ? ((m_pBMI->bmiHeader.biHeight > 0) ? TRUE : FALSE ): FALSE;
	}
};

#endif // __DIB__
