#ifndef _ANIMMAPOBJECT_H_
#define _ANIMMAPOBJECT_H_

#include "MapObject.h"
#include "CSpriteCatalog.h"

class CAnimMapObject : public CMapObject
{
protected:
	CSpriteCatalog *m_pCatalog;  // optional pointer to sprite catalog
	int m_iSequence;             // current sequence
	int m_iFrame;                // current frame 

	CAnimMapObject();          // for dynacreate only
	DECLARE_DYNCREATE(CAnimMapObject)

	virtual void InitContents();
    virtual CSpriteSequence *GetSequence(int iSequence)
	{
		if (m_pCatalog && iSequence >= 0 && iSequence < m_pCatalog->iSeqs)
		{
			return m_pCatalog->arSeqs[iSequence];
		}
		return NULL;
	}
public:
	// Constructors
	CAnimMapObject(LPCTSTR pathName);

	// Overrides
	virtual ~CAnimMapObject();
	virtual CSize GetSize(int iSequence, int iFrame);
	virtual int GetDepth();
	virtual CPoint GetHotSpot(int iSequence, int iFrame, BOOL bFlipped);
	virtual void Draw(HDC hdc, const CPoint& pt, HDC hdcTemp, CDIB *pDst,
		int iSequence, int iFrame, BOOL bFlipped);
	virtual void DrawWithPalette( HDC hdc, const RECT& dstRect, HPALETTE hPalette);
    virtual int GetCurrentSequence() { return m_iSequence; }
	virtual int GetCurrentFrame() { return m_iFrame; }
	virtual int GetSequenceCount()
	{
		return (m_pCatalog ? m_pCatalog->iSeqs : 0);
	}
	virtual int GetFrameCount(int iSequence)
	{
		CSpriteSequence *pSequence = GetSequence(iSequence);
		return pSequence ? pSequence->iFrames : 0;
	}
	virtual int GetSpeed(int iSequence)
	{
		CSpriteSequence *pSequence = GetSequence(iSequence);
		return pSequence ? pSequence->iSpeed : 0;
	}
	virtual LPCTSTR GetSequenceName(int iSequence)
	{
		CSpriteSequence *pSequence = GetSequence(iSequence);
		return pSequence ? pSequence->csName : (LPCTSTR)NULL;
	}
};

#endif