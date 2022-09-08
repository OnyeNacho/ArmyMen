#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_

#include "dib.h"

// A CMapObject contains all the information necessary to render
// a single object placed anywhere on the map.  It does not contain
// any position information. The generic CMapObject simply renders
// its outline (no image).
class CMapObject : public CObject
{
	friend class CObjectSet;
	friend class CScenarioSet;

	// action types
	enum
	{
		eFlipHorizontal,  
		eAnimation,
	};

protected:
	int m_ID;            // this object's objectset id
	BOOL m_bFlipped;     // non-zero when flipped horizontally

	CString m_pszFolder;	// folder name, which defines category
	LPCTSTR m_lpszKey;		// key within the object set
	CString m_pszName;		// object name

	CMapObject();		 // for dynacreate only 
	DECLARE_DYNCREATE(CMapObject)

	void Draw(HDC hdc, int x1, int y1, int x2, int y2);

public:
	CMapObject(LPCTSTR pathName);
	virtual ~CMapObject() {}

	LPCTSTR GetFolder() const { return m_pszFolder; }
	LPCTSTR GetKey() const { return m_lpszKey; }
	virtual CString GetName() const { return m_pszName; }
	virtual CSize GetSize(int iSequence, int iFrame) { return CSize(16,16); }
	virtual CPoint GetHotSpot(int iSequence, int iFrame, BOOL bFlipped)	{ return CPoint(0,0);}
	virtual int GetDepth() { return 0; }
	virtual void UpdateTransparentColor(CPalette *pPalette) {}
	virtual void Remap(CPalette *pPalette) {}
	virtual void Draw(HDC hdc, const CPoint& pt, HDC hdcTemp, CDIB *pDst,
		int iSequence, int iFrame, int bFlipped);
	virtual void DrawWithPalette( HDC hdc, const RECT& dstRect, HPALETTE hPalette);
	virtual int GetCurrentSequence() { return 0; }
	virtual int GetCurrentFrame()    { return 0; }
    virtual BOOL GetFlipped()        { return m_bFlipped; }
    virtual void SetFlipped(BOOL bFlipped) { m_bFlipped = bFlipped; }
	virtual int GetFrameCount(int iSequence) { return 0; }
    virtual int GetSpeed(int iSequence) { return 0; }
	virtual int GetSequenceCount() { return 0; }
    virtual LPCTSTR GetSequenceName(int iSequence) { return NULL; }

	// utility methods
	virtual CSize GetSize() 
	{
		return GetSize(GetCurrentSequence(), GetCurrentFrame());
	}
	virtual CPoint GetHotSpot()
	{
		return GetHotSpot(GetCurrentSequence(), GetCurrentFrame(), GetFlipped());
	}
};

class CStaticMapObject : public CMapObject
{
protected:
	CDIB *m_pDIB;                // optional pointer to bitmap image 
    COLORREF m_rgbTransparent;   // transparent rgb color value
	UINT m_nTransparentColor;    // index of m_rgbTransparent in palette

	CStaticMapObject();          // for dynacreate only
	DECLARE_DYNCREATE(CStaticMapObject)

public:
	// Constructors
	CStaticMapObject(LPCTSTR pathName);

	// Overrides
	virtual ~CStaticMapObject();
	virtual CSize GetSize(int iSequence, int iFrame)
	{
		if (m_pDIB)
			return CSize(m_pDIB->GetWidth(), m_pDIB->GetHeight());
		return CMapObject::GetSize(iSequence, iFrame);
	}
	virtual int GetDepth()
	{
		if (m_pDIB)
			return m_pDIB->GetDepth();
		return CMapObject::GetDepth();
	}
	virtual CPoint GetHotSpot(int iSequence, int iFrame, BOOL bFlipped)
	{
		if (m_pDIB)
		{
			CPoint pt = m_pDIB->GetHotSpot();
			if (bFlipped)
				pt.x = m_pDIB->GetWidth() - pt.x -1;
			return pt;
		}
		return CMapObject::GetHotSpot(iSequence, iFrame, bFlipped);
	}
	virtual void UpdateTransparentColor(CPalette *pPalette);
	virtual void Remap(CPalette *pPalette);
	virtual void Draw(HDC hdc, const CPoint& pt, HDC hdcTemp, CDIB *pDst,
		int iSequence, int iFrame, BOOL bFlipped);
	virtual void DrawWithPalette( HDC hdc, const RECT& dstRect, HPALETTE hPalette);
};


// A CMapObjectInst is an instance of a CMapObject (or derived class).
// It contains position and selection information for the instance and a 
// reference ID for the master CMapObject (or derived class).
class CMapObjectInst : public CObject
{
public:
	int m_ID;          // index of this object in current objectSet   
	BOOL m_bSelected;
	BOOL m_bFlipped;
	BOOL m_bOutOfOrder;
    CPoint m_location;
	CString m_sTextBlock;

	// For animatable objects
	int m_iSequence;
	int m_iFrame;

	// For objects that need a unique number
	BOOL m_iNumber;

	CMapObjectInst(int ID, CPoint pt, int iSequence = 0, int iFrame = 0, BOOL bFlipped = FALSE, int iNumber = 0) 
	{ 
		m_ID = ID; 
		m_location = pt; 
		m_bSelected = FALSE; 
		m_iSequence = iSequence;
		m_iFrame = iFrame;
		m_bFlipped = bFlipped;
		m_iNumber = iNumber;
	}
	virtual void Serialize(CArchive& ar);
	virtual ~CMapObjectInst() {}

protected:

#ifdef _DEBUG
	void Dump(CDumpContext& dc) const;
#endif

	CMapObjectInst() {	m_bOutOfOrder = m_bSelected = FALSE;  }  // for serialization
	DECLARE_SERIAL(CMapObjectInst);
};


#endif