// AppPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "AppPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppPropPage property page

IMPLEMENT_DYNCREATE(CAppPropPage, CPropertyPage)

CAppPropPage::CAppPropPage() : CPropertyPage(CAppPropPage::IDD)
{
	//{{AFX_DATA_INIT(CAppPropPage)
	m_bOutlinePreview = g_bOutlinePreview;
	m_bActivePreview = g_bActivePreview;
	m_bShowFullObjectName = g_bShowFullObjectName;
	m_bUseOffScreenDibs = g_bUseOffScreenDibs;
	//}}AFX_DATA_INIT
}

CAppPropPage::~CAppPropPage()
{
}

void CAppPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppPropPage)
	DDX_Check(pDX, IDC_OUTLINE_PREVIEW, m_bOutlinePreview);
	DDX_Check(pDX, IDC_PREVIEW_ACTIVE, m_bActivePreview);
	DDX_Check(pDX, IDC_SHOW_FULL_OBJECTNAME, m_bShowFullObjectName);
	DDX_Check(pDX, IDC_DRAW_OFFSCREEN, m_bUseOffScreenDibs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CAppPropPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppPropPage message handlers
