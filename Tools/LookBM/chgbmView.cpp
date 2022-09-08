// chgbmView.cpp : implementation of the CChgbmView class
//

#include "stdafx.h"
#include "chgbm.h"

#include "chgbmDoc.h"
#include "chgbmView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChgbmView

IMPLEMENT_DYNCREATE(CChgbmView, CView)

BEGIN_MESSAGE_MAP(CChgbmView, CView)
	//{{AFX_MSG_MAP(CChgbmView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChgbmView construction/destruction

CChgbmView::CChgbmView()
{
	// TODO: add construction code here

}

CChgbmView::~CChgbmView()
{
}

BOOL CChgbmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
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
// CChgbmView drawing

void CChgbmView::OnDraw(CDC* pDC)
{
	char buffer[100];

	CChgbmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	// apply the font to this context
    pDC->SelectObject(the_font);
	pDC->SetTextColor( RGB(0,0,0) );
	pDC->SetBkColor( RGB(255,255,255) );
	pDC->SetBkMode( TRANSPARENT );

	int y = 10;
	int x = 10;

	if (pDoc->bmFileHdr.bfType != 0x4D42)	{
		sprintf(buffer,"Not a bitmap");
		pDC->TextOut(10, y, buffer, strlen(buffer) );
		return;
	}

	sprintf(buffer,"file header: type %X, size %X, offset %X", 
				pDoc->bmFileHdr.bfType, pDoc->bmFileHdr.bfSize, pDoc->bmFileHdr.bfOffBits);
	pDC->TextOut(10, y, buffer, strlen(buffer) );
	y += 18;

	sprintf(buffer,"bitmap info: size %d, width %d, height %d, planes %d, bbp %d", 
				pDoc->bmInfoHdr.biSize, 
				pDoc->bmInfoHdr.biWidth, pDoc->bmInfoHdr.biHeight,
				pDoc->bmInfoHdr.biPlanes, pDoc->bmInfoHdr.biBitCount);
	pDC->TextOut(10, y, buffer, strlen(buffer) );
	y += 14;

	sprintf(buffer,"comp %d, size image %d, xppm %d, yppm %d", 
				pDoc->bmInfoHdr.biCompression, pDoc->bmInfoHdr.biSizeImage, 
				pDoc->bmInfoHdr.biXPelsPerMeter, pDoc->bmInfoHdr.biYPelsPerMeter);
	pDC->TextOut(10, y, buffer, strlen(buffer) );
	y += 14;

	int colors = pDoc->bmInfoHdr.biClrUsed;
	if (!colors)
		colors = 1 << pDoc->bmInfoHdr.biBitCount;

	sprintf(buffer,"palette: used %d, important %d, colors %d", 
		pDoc->bmInfoHdr.biClrUsed, pDoc->bmInfoHdr.biClrImportant, colors);
	pDC->TextOut(10, y, buffer, strlen(buffer) );
	y += 20;


	x = 10;
	for (int i=0; i<colors; i++)	{
		sprintf(buffer,"%4.4X ", 
					pDoc->bmiColors[i]);
		pDC->TextOut(x, y, buffer, strlen(buffer) );
		x += 64;
		if (x > 640)	{
			x = 10;
			y += 14;
		}
	}
	y += 14;
}

/////////////////////////////////////////////////////////////////////////////
// CChgbmView printing

BOOL CChgbmView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CChgbmView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CChgbmView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CChgbmView diagnostics

#ifdef _DEBUG
void CChgbmView::AssertValid() const
{
	CView::AssertValid();
}

void CChgbmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChgbmDoc* CChgbmView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChgbmDoc)));
	return (CChgbmDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChgbmView message handlers
