// TextPage.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "TextPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextPage property page

IMPLEMENT_DYNCREATE(CTextPage, CPropertyPage)

CTextPage::CTextPage() : CPropertyPage(CTextPage::IDD)
{
	//{{AFX_DATA_INIT(CTextPage)
	m_sTextBlock = _T("");
	//}}AFX_DATA_INIT
}

CTextPage::~CTextPage()
{
}

void CTextPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextPage)
	DDX_Text(pDX, IDC_TEXT, m_sTextBlock);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextPage, CPropertyPage)
	//{{AFX_MSG_MAP(CTextPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextPage message handlers
