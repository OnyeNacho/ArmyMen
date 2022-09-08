// AnimMapObject.cpp : implementation file
//
#include "stdafx.h"
#include "MapEditor.h"
#include "AnimMapObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////
// CAnimMapObject 
IMPLEMENT_DYNCREATE(CAnimMapObject, CMapObject)

CAnimMapObject::CAnimMapObject() 
{
	InitContents();
}

CAnimMapObject::~CAnimMapObject()
{
	delete m_pCatalog;
}

void CAnimMapObject::InitContents()
{
	m_pCatalog = NULL;
	m_iSequence = 0;
	m_iFrame = 0;
}

CAnimMapObject::CAnimMapObject(LPCTSTR pathName) 
: CMapObject(pathName) // call this default constructor
{

	InitContents();
	TRY
	{
		CFile fileRead( pathName, CFile::modeRead );
		CArchive ar( &fileRead, CArchive::load );
		m_pCatalog = new CSpriteCatalog;
        m_pCatalog->Serialize(ar);
	}
	CATCH_ALL(E)
	{
		delete m_pCatalog;
		m_pCatalog = NULL;
		THROW_LAST();
	}
	END_CATCH_ALL
}

CSize CAnimMapObject::GetSize(int iSequence, int iFrame)
{
	CSpriteSequence *pSequence = GetSequence(iSequence);
	if (pSequence && iFrame >= 0 && iFrame < pSequence->iFrames)
	{
		return CSize(*pSequence->arSizes[iFrame]); 
	}
	return CMapObject::GetSize(iSequence, iFrame);

}

int CAnimMapObject::GetDepth()
{
	return (m_pCatalog ? 8 : 0);
}

CPoint CAnimMapObject::GetHotSpot(int iSequence, int iFrame, BOOL bFlipped)
{
	CSpriteSequence *pSequence = GetSequence(iSequence);

	if (pSequence && iFrame >= 0 && iFrame < pSequence->iFrames)
	{
		CPoint pt = *pSequence->arOffsets[iFrame]; 
		if (bFlipped)
			pt.x = pSequence->arSizes[iFrame]->x - pt.x -1;
		return pt;
	}
	return CMapObject::GetHotSpot(iSequence, iFrame, bFlipped);
}

void CAnimMapObject::DrawWithPalette( HDC hdc, const RECT& dstRect, HPALETTE hPalette)
{
	CSpriteSequence *pSequence = GetSequence(m_iSequence);
	if (pSequence)
	{
		CDIB dib;
		CSize size = GetSize(m_iSequence, m_iFrame);
		if (dib.Create(size.cx,size.cy,GetDepth())) // TBD: palette
		{
			HDC hdcSrc = dib.CreateHDC(hdc);
			if (hdcSrc)
			{
				HPALETTE hOldPal;
				if (hPalette) hOldPal = SelectPalette(hdc, hPalette, FALSE);
				BitBlt(hdcSrc,0,0,size.cx,size.cy,hdcSrc,0,0,WHITENESS);

				Draw(hdc,CPoint(0,0),NULL,&dib, m_iSequence, m_iFrame, m_bFlipped); 
				StretchBlt(hdc, dstRect.left, dstRect.top, 
						   dstRect.right - dstRect.left, dstRect.bottom - dstRect.top,
						   hdcSrc, 0, 0, size.cx, size.cy, SRCCOPY);

				if (hOldPal) SelectPalette(hdc, hOldPal, TRUE);
				dib.DeleteHDC();
				return;
			}
		}
	}
	CMapObject::DrawWithPalette(hdc, dstRect, hPalette);
}
void CAnimMapObject::Draw(HDC hdc, const CPoint& pt, HDC hdcTemp, CDIB *pDst,
						  int iSequence, int iFrame, BOOL bFlipped)
{
    CSpriteSequence *pSequence = GetSequence(iSequence);
	if (pSequence)
	{
		ASSERT(m_pCatalog != NULL);
		CSize size = GetSize(iSequence, iFrame);

		 if (pDst)
		 {
			 // drawing into off-screen dib
			ASSERT(pDst->IsSimpleDib());
			ASSERT(pDst->GetDepth() == 8);
		
			POINT points[2];
			points[0].x = pt.x; points[0].y = pt.y;
			points[1].x = pt.x + size.cx; points[1].y = pt.y + size.cy;
			VERIFY(LPtoDP(hdc,points,2));

			int px = points[0].x;
			int py = points[0].y;
			int w = points[1].x - px;
			int h = points[1].y - py;
           
			if (w > 0 && h > 0)
			{
				if (w != size.cx || h != size.cy)
					goto draw_dib;

				GdiFlush();
				BYTE *pDestStart = pDst->GetBitsAddress(0,0);
				long lDestPitch = pDst->GetLineIncrement();
				CPoint hot = GetHotSpot(iSequence, iFrame, bFlipped);
				px += hot.x;
				py += hot.y;
				m_pCatalog->DrawSprite(pDestStart, lDestPitch,
						px, py, 
						pDst->GetWidth(), pDst->GetHeight(),
						pSequence, iFrame, bFlipped);
				return;
			}
		 }
		 else
		 {
draw_dib:    
		     RGBQUAD *pRGB;
		     if (pDst && pDst->GetDepth() >= GetDepth())
				 pRGB = pDst->GetClrTabAddress();
			 else
				 pRGB = NULL;

			 CDIB dib;
			 if (dib.Create(size.cx,size.cy,GetDepth(), pRGB)) 
			 {
				 HDC hdcSrc = dib.CreateHDC(NULL);
				 if (hdcSrc)
				 {
					BitBlt(hdcSrc,0,0,size.cx,size.cy,hdcSrc,0,0,BLACKNESS);
					Draw(hdcSrc,CPoint(0,0),hdc,&dib,iSequence,iFrame,bFlipped);
					BitBlt(hdc, pt.x, pt.y, size.cx, size.cy, 
						   hdcSrc, 0, 0, SRCCOPY);
					dib.DeleteHDC();
					return;
				 }
			 }
		 }
	}

	// if we get here, use the default drawing routine...
	CMapObject::Draw(hdc, pt, hdcTemp, pDst, iSequence, iFrame, bFlipped);
}





