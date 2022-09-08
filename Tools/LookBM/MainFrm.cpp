// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "chgbm.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFont the_font;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

	// now create the new font
	the_font.CreateFont(
		12,
        0,										// logical average character width
		0,										// angle of escapement
		0,										// base-line orientation angle
		FW_NORMAL,								// font weight
		TRUE,									// Italic attribute flag
		FALSE,									// Underline attribute flag
		FALSE,									// Strikeout attribute flag
        ANSI_CHARSET,							// Character set identifier
        OUT_DEFAULT_PRECIS,						// output precision
        CLIP_DEFAULT_PRECIS,					// clipping precision
        DRAFT_QUALITY,							// output quality,
        VARIABLE_PITCH,							// pitch and family
        "Courier"								// pointer to typeface name string
	);	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
