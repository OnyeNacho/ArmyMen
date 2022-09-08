// dibdoc.cpp : implementation of the CDibDoc class
//

#include "stdafx.h"
#include "resource.h"
#include "dib.h"
#include "dibpal.h"
#include "dibdoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDibDoc

IMPLEMENT_DYNCREATE(CDibDoc, CDocument)

BEGIN_MESSAGE_MAP(CDibDoc, CDocument)
    //{{AFX_MSG_MAP(CDibDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDibDoc construction/destruction

CDibDoc::CDibDoc()
{
    m_pDIB = NULL;
    m_pPal = NULL;
}

CDibDoc::~CDibDoc()
{
    delete m_pDIB;
    delete m_pPal;
}

void CDibDoc::DeleteContents()
{
    if (m_pDIB) 
	{
        delete m_pDIB;
        m_pDIB = NULL;
    }
    if (m_pPal) 
	{
        delete m_pPal;
        m_pPal = NULL;
    }
}


/////////////////////////////////////////////////////////////////////////////
// CDibDoc serialization

void CDibDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) 
	{
		if (m_pDIB == NULL)
			AfxThrowUserException();
		m_pDIB->Save(ar);
    } 
	else 
	{
		DeleteContents();
        // Load the DIB from the file.
        m_pDIB = new CDIB;
		ASSERT_NEW(m_pDIB);
		m_pDIB->Load(ar);

        // Create the palette from the DIB.
		if (m_pDIB->GetNumClrEntries())
		{
			m_pPal = new CDIBPal;
			ASSERT_NEW(m_pPal);
			if (!m_pPal->Create(m_pDIB)) {
				TRACE0("Can't create palette from DIB\n");
				delete m_pPal;
				m_pPal = NULL;
			}
		}
		else
			m_pPal = NULL;
    }
}


/////////////////////////////////////////////////////////////////////////////
// CDibDoc diagnostics

#ifdef _DEBUG
void CDibDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CDibDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDibDoc commands

CSize CDibDoc::GetSize()
{
	if (m_pDIB)
		return CSize(m_pDIB->GetWidth(), m_pDIB->GetHeight());
	else
		return CSize(0,0);
}



BOOL CDibDoc::OnNewDocument()
{
	return CDocument::OnNewDocument();
}

BOOL CDibDoc::OnNewDocument(int iWidth, int iHeight, int iTileDepth, RGBQUAD *pRGB)
{
	BOOL bCreated = FALSE;
	if (CDocument::OnNewDocument())
	{
		// Create a new dib
		m_pDIB = new CDIB;
		ASSERT_NEW(m_pDIB);

		if (m_pDIB->Create(iWidth, iHeight, iTileDepth, pRGB) && (m_pDIB->GetNumClrEntries() > 0))
		{
			m_pPal = new CDIBPal;
			ASSERT_NEW(m_pPal);
			bCreated = m_pPal->Create(m_pDIB);
		}
		else
		{
			m_pPal = NULL;
			bCreated = TRUE;
		}
        
	}
	if (!bCreated) DeleteContents();
	return bCreated;
}

void CDibDoc::SetDIB(CDIB *pDIB)
{
    delete m_pDIB;
    m_pDIB = pDIB;
}

void CDibDoc::SetPal(CDIBPal *pPal)
{
	delete m_pPal;
	m_pPal = pPal;
}

CDIB * CDibDoc::DetachDIB()
{
	CDIB *pDIB = m_pDIB;
	m_pDIB = NULL;
	return pDIB;
}

CDIBPal * CDibDoc::DetachPal()
{
	CDIBPal *pPal = m_pPal;
	m_pPal = NULL;
	return pPal;
}

void CDibDoc::CopyPalette(CPalette *pPal)
{
	if (pPal && m_pPal)
	{
		UINT nEntries = min(pPal->GetEntryCount(),m_pPal->GetEntryCount());
		PALETTEENTRY *pData = (PALETTEENTRY *)malloc(nEntries * sizeof(PALETTEENTRY));
		if (pData)
		{
			pPal->GetPaletteEntries(0,nEntries,pData);
			m_pPal->SetPaletteEntries(0,nEntries,pData);
			m_pDIB->SetPalette(0,nEntries,pData); // TBD: why is this necessary?
			free(pData);
		}
		else
			AfxThrowMemoryException();
	}
}

void CDibDoc::SetPaletteEntry(UINT i, PALETTEENTRY *pData)
{
	if (m_pPal)	m_pDIB->SetPalette(0,1,pData);
}

BOOL CDibDoc::Copy(CDIB *pSrc, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
{
	// get the system device context
	HDC hdc = CreateDC("DISPLAY",NULL,NULL,NULL); // TBD: how bad is this?  should this be passed in?
	HDC hdcMem;
	BOOL bCopied = FALSE;
	if (hdc)
	{
		hdcMem = CreateCompatibleDC(hdc);
		if (hdcMem)
		{
			HPALETTE oldPal = SelectPalette(hdcMem, (HPALETTE)m_pPal->GetSafeHandle(), FALSE);
			HBITMAP oldBM = SelectHBitmap(hdcMem, m_pDIB->GetHBitmap());
			RealizePalette(hdcMem);
			bCopied = pSrc->Draw(hdcMem,sx,sy,sw,sh,dx,dy,dw,dh);
			SelectHBitmap(hdcMem, oldBM);
			SelectPalette(hdcMem, oldPal, FALSE);
			bCopied = TRUE;
			DeleteDC(hdcMem);
		}
		DeleteDC(hdc);
	}
	return bCopied;
}
