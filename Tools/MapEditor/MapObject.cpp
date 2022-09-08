// MapObject.cpp : implementation file
//
#include "stdafx.h"
#include "MapEditor.h"
#include "MapObject.h"
#include "DibPal.h"
#include "DibDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapObject

IMPLEMENT_DYNCREATE(CMapObject, CObject)

CMapObject::CMapObject()
{
	m_lpszKey = NULL;
	m_bFlipped = FALSE;
}

CMapObject::CMapObject(LPCTSTR pathName)
{
	m_lpszKey = NULL;
    m_bFlipped = FALSE;

	// compute & store the short object name (ie: path\foo.bmp -> "foo")
	CString tmp = pathName;                     
	if (!StripComponent(tmp,m_pszName,'\\'))
		m_pszName = pathName;
    VERIFY(StripComponent(m_pszName,tmp,'.'));	//     m_pszName = foo
    m_pszName.MakeLower(); // hash function is case-sensitive
}

void CMapObject::Draw(HDC hdc, int x1, int y1, int x2, int y2)
{
	HPEN oldPen = (HPEN)SelectObject(hdc, GetStockObject(BLACK_PEN));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x1, y2);
	MoveToEx(hdc, x2-1, y1, NULL);
	LineTo(hdc, x1, y2);
	Rectangle(hdc, x1, y1, x2, y2);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

void CMapObject::Draw(HDC hdc, const CPoint& pt, HDC hdcTemp, CDIB *pDst,
					  int iSequence, int iFrame, BOOL bFlipped)
{
	CSize size = GetSize(iSequence, iFrame);
	Draw(hdc, pt.x, pt.y, pt.x + size.cx, pt.y + size.cy);
}

void CMapObject::DrawWithPalette(HDC hdc, const RECT& dstRect, HPALETTE hPalette)
{
	Draw(hdc, dstRect.left, dstRect.top, dstRect.right, dstRect.bottom);
}

////////////////////////////////////////////////////////////////////////////////
// CMapObjectInst

IMPLEMENT_SERIAL(CMapObjectInst, CObject, VERSIONABLE_SCHEMA | 4)

void CMapObjectInst::Serialize(CArchive& ar)
{
	// Note: since CMapObjectInst's are only used dynamically we can
	// avoid the PUT_SAFE_SCHEMA/GET_SAFE_SCHEMA
	UINT nSchema;

	if (ar.IsLoading())
		nSchema = ar.GetObjectSchema();

	CObject::Serialize(ar);

    if (ar.IsStoring())
	{
		ar << m_ID;
		ar << m_location.x;
		ar << m_location.y;
		ar << m_iSequence;   // nSchema >= 2
		ar << m_bFlipped;    // nSchema >= 2
		ar << m_sTextBlock;  // nSchema >= 3
		ar << m_iNumber;     // nSchema >= 4
	}
	else
	{
		ar >> m_ID;
		ar >> m_location.x;
		ar >> m_location.y;

		if (nSchema >= 2)
		{
			ar >> m_iSequence;
			ar >> m_bFlipped;
		}
		else
		{
			m_iSequence = 0;
			m_bFlipped = FALSE;
		}

		if (nSchema >= 3)
			ar >> m_sTextBlock;

		if (nSchema >= 4)
			ar >> m_iNumber;

		m_iFrame = 0; // TBD: always reset the frame to 0
	}
}

#ifdef _DEBUG
void CMapObjectInst::Dump(CDumpContext& dc) const
{
	dc << "Object#" << m_ID 
	   << "[ x" 
	   << m_location.x << ", y" << m_location.y << ", Seq" 
	   << m_iSequence << ", Fr"  << m_iFrame << ","
	   << m_bSelected << m_iNumber
	   << "]\n";
}
#endif

//////////////////////////////////////////////////////////////////
// CStaticMapObject 
IMPLEMENT_DYNCREATE(CStaticMapObject, CMapObject)

CStaticMapObject::CStaticMapObject()
{
	m_pDIB = NULL;
}
CStaticMapObject::~CStaticMapObject()
{
	delete m_pDIB;
}

CStaticMapObject::CStaticMapObject(LPCTSTR pathName) 
: CMapObject(pathName) // call this default constructor
{
	m_pDIB = NULL; // in case we can't open the dib
	CDibDoc *pDibDoc = new CDibDoc;
	ASSERT_NEW(pDibDoc);
    TRY
	{
		if (pDibDoc->OnOpenDocument(pathName))
			m_pDIB = pDibDoc->DetachDIB();

		if (m_pDIB == NULL)
			AfxThrowUserException(); // open document already told the user why

		UpdateTransparentColor(pDibDoc->GetPalette());
		delete pDibDoc;
	}
	CATCH_ALL(E)
	{
		delete pDibDoc;
		THROW_LAST();
	}
	END_CATCH_ALL
}

void CStaticMapObject::UpdateTransparentColor(CPalette *pPalette)
{
	HPALETTE hPalette = (HPALETTE)pPalette;
	m_rgbTransparent = m_pDIB->ReadColor(0,0,hPalette);
	if (!m_pDIB->CreateMask(m_rgbTransparent,hPalette))
	   AfxThrowMemoryException();

	if (m_pDIB->IsSimpleDib())
	{
		ASSERT(hPalette != NULL);
		m_nTransparentColor = *m_pDIB->GetBitsAddress(0,0);
	}
	else
		m_nTransparentColor = 0;
}

void CStaticMapObject::Remap(CPalette *pPalette)
{
	BYTE pTable[256];
	if (m_pDIB && m_pDIB->IsSimpleDib())
	{
		int iTotal = m_pDIB->GetNumClrEntries();
		for (int i=0; i < iTotal; i++)
		{
			COLORREF srcColor = m_pDIB->GetColor(i);
			UINT color = pPalette->GetNearestPaletteIndex(srcColor);
			ASSERT(color >= 0 && color < 256);
			pTable[i] = (BYTE)color;
		}
		m_pDIB->Remap(pTable);
		m_pDIB->CopyPalette(pPalette);
		UpdateTransparentColor(pPalette);
	}
}

void CStaticMapObject::Draw(HDC hdc, const CPoint& pt, HDC hdcTemp, CDIB *pDst,
							int iSequence, int iFrame, BOOL bFlipped)
{
	if (m_pDIB)
	{
		 if (pDst && m_pDIB->IsSimpleDib())
		 {
			 // drawing into off-screen dib
			CSize size = GetSize(iSequence, iFrame);
			ASSERT(pDst->IsSimpleDib());
			POINT points[2];
			points[0].x = pt.x; points[0].y = pt.y;
			points[1].x = pt.x + size.cx; points[1].y = pt.y + size.cy;
			VERIFY(LPtoDP(hdc,points,2));
			int w = points[1].x - points[0].x;
			int h = points[1].y - points[0].y;

			if (w > 0 && h > 0)
			{
				GdiFlush();
				m_pDIB->StretchOver(0,0,size.cx,size.cy,
					    pDst,points[0].x,points[0].y,w,h,m_nTransparentColor);
				return;
			}
		 }
		 else
		 {
			 // drawing into screen or screen compatible bitmap
			 m_pDIB->DrawTrueMask(hdc, pt.x, pt.y, hdcTemp);
			 return;
		 }
	}

	// if we get here, use the default drawing routine...
	CMapObject::Draw(hdc, pt, hdcTemp, pDst, iSequence, iFrame, bFlipped);
}

void CStaticMapObject::DrawWithPalette( HDC hdc, const RECT& dstRect, HPALETTE hPalette)
{
	if (m_pDIB)
	{
		HDC hdcTemp = CreateCompatibleDC(hdc);
		if (hdcTemp)
		{
	        HPALETTE hPalette1, hPalette2;
			if (hPalette)
			{
				hPalette1 = SelectPalette(hdc, hPalette, FALSE);
				hPalette2 = SelectPalette(hdcTemp, hPalette, FALSE);
			}

			m_pDIB->DrawTrueMask(hdc, dstRect, hdcTemp);

            if (hPalette)
			{
				SelectPalette(hdc, hPalette1, TRUE);
				SelectPalette(hdcTemp, hPalette2, TRUE);
			}

			DeleteDC(hdcTemp);
			return;
		}
	}

	// if we get here, use the default drawing routine...
	CMapObject::DrawWithPalette(hdc, dstRect, hPalette);
}