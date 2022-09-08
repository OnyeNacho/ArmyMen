// chgbmDoc.cpp : implementation of the CChgbmDoc class
//

#include "stdafx.h"
#include "chgbm.h"

#include "chgbmDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChgbmDoc

IMPLEMENT_DYNCREATE(CChgbmDoc, CDocument)

BEGIN_MESSAGE_MAP(CChgbmDoc, CDocument)
	//{{AFX_MSG_MAP(CChgbmDoc)
	ON_COMMAND(ID_CHANGE_XPPM, OnChangeXppm)
	ON_COMMAND(ID_CHANGE_YPPM, OnChangeYppm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChgbmDoc construction/destruction

CChgbmDoc::CChgbmDoc()
{
	// TODO: add one-time construction code here

}

CChgbmDoc::~CChgbmDoc()
{
	free(dataptr);
	dataptr = NULL;
}

BOOL CChgbmDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


#ifdef COMMENTED_OUT
typedef struct tagBITMAPFILEHEADER { // bmfh 
        WORD    bfType; 
        DWORD   bfSize; 
        WORD    bfReserved1; 
        WORD    bfReserved2; 
        DWORD   bfOffBits; 
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{ // bmih 
   DWORD  biSize; 
   LONG   biWidth; 
   LONG   biHeight; 
   WORD   biPlanes; 
   WORD   biBitCount 
   DWORD  biCompression; 
   DWORD  biSizeImage; 
   LONG   biXPelsPerMeter; 
   LONG   biYPelsPerMeter; 
   DWORD  biClrUsed; 
   DWORD  biClrImportant; 
} BITMAPINFOHEADER; 
#endif

/////////////////////////////////////////////////////////////////////////////
// CChgbmDoc serialization

void CChgbmDoc::Serialize(CArchive& ar)
{
	int i;
	int colors;

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		if (bmFileHdr.bfType != 0x4D42)
			return;

        ar << bmFileHdr.bfType; 
        ar << bmFileHdr.bfSize; 
        ar << bmFileHdr.bfReserved1; 
        ar << bmFileHdr.bfReserved2; 
        ar << bmFileHdr.bfOffBits; 

		ar << bmInfoHdr.biSize; 
		ar << bmInfoHdr.biWidth; 
		ar << bmInfoHdr.biHeight; 
		ar << bmInfoHdr.biPlanes; 
		ar << bmInfoHdr.biBitCount;
		ar << bmInfoHdr.biCompression; 
		ar << bmInfoHdr.biSizeImage; 
		ar << bmInfoHdr.biXPelsPerMeter; 
		ar << bmInfoHdr.biYPelsPerMeter; 
		ar << bmInfoHdr.biClrUsed; 
		ar << bmInfoHdr.biClrImportant; 

		colors = bmInfoHdr.biClrUsed;
		if (!colors)
			colors = 1 << bmInfoHdr.biBitCount;

		for( i = 0; i < colors; i++ )	{
			ar << bmiColors[i].rgbBlue; 
			ar << bmiColors[i].rgbGreen; 
			ar << bmiColors[i].rgbRed; 
			ar << bmiColors[i].rgbReserved; 
		}

		int size = bmFileHdr.bfSize - bmFileHdr.bfOffBits;
		for( i = 0; i < size; i++ )
			ar << dataptr[i];

		UpdateAllViews(NULL);
	}
	else
	{
		// TODO: add loading code here
		int count = 0;

        ar >> bmFileHdr.bfType;

		if (bmFileHdr.bfType != 0x4D42)	{
			return;
		}

        ar >> bmFileHdr.bfSize; 
        ar >> bmFileHdr.bfReserved1; 
        ar >> bmFileHdr.bfReserved2; 
        ar >> bmFileHdr.bfOffBits; 
		count += sizeof(bmFileHdr);

		ar >> bmInfoHdr.biSize; 
		ar >> bmInfoHdr.biWidth; 
		ar >> bmInfoHdr.biHeight; 
		ar >> bmInfoHdr.biPlanes; 
		ar >> bmInfoHdr.biBitCount;
		ar >> bmInfoHdr.biCompression; 
		ar >> bmInfoHdr.biSizeImage; 
		ar >> bmInfoHdr.biXPelsPerMeter; 
		ar >> bmInfoHdr.biYPelsPerMeter; 
		ar >> bmInfoHdr.biClrUsed; 
		ar >> bmInfoHdr.biClrImportant; 
		count += sizeof(bmInfoHdr);

		colors = bmInfoHdr.biClrUsed;
		if (!colors)
			colors = 1 << bmInfoHdr.biBitCount;

		for( i = 0; i < colors; i++ ){
			ar >> bmiColors[i].rgbBlue; 
			ar >> bmiColors[i].rgbGreen; 
			ar >> bmiColors[i].rgbRed; 
			ar >> bmiColors[i].rgbReserved; 
			count += sizeof(RGBQUAD);
		}

		int size = bmFileHdr.bfSize - bmFileHdr.bfOffBits;
		dataptr = (unsigned char *) malloc(size);
		for( int i = 0; i < size; i++ )
			ar >> dataptr[i];
	}
}


/////////////////////////////////////////////////////////////////////////////
// CChgbmDoc diagnostics

#ifdef _DEBUG
void CChgbmDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChgbmDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChgbmDoc commands

void CChgbmDoc::OnChangeXppm() 
{
	// TODO: Add your command handler code here
	bmInfoHdr.biXPelsPerMeter = 4747;
	UpdateAllViews(NULL);
}

void CChgbmDoc::OnChangeYppm() 
{
	// TODO: Add your command handler code here
	bmInfoHdr.biYPelsPerMeter = 47;
	UpdateAllViews(NULL);
}
