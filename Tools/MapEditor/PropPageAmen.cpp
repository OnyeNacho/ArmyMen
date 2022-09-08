// PropPageAmen.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "PropPageAmen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPropPageAmen property page

IMPLEMENT_DYNCREATE(CPropPageAmen, CPropertyPage)

CPropPageAmen::CPropPageAmen() : CPropertyPage(CPropPageAmen::IDD)
{
	//{{AFX_DATA_INIT(CPropPageAmen)
	m_pszTrigger1 = g_pszArmyMenTriggers[0];
	m_pszTrigger2 = g_pszArmyMenTriggers[1];
	m_pszTrigger3 = g_pszArmyMenTriggers[2];
	m_pszTrigger4 = g_pszArmyMenTriggers[3];
	m_pszTrigger5 = g_pszArmyMenTriggers[4];
	m_pszTrigger6 = g_pszArmyMenTriggers[5];
	m_pszTrigger7 = g_pszArmyMenTriggers[6];
	m_pszTrigger8 = g_pszArmyMenTriggers[7];
	//}}AFX_DATA_INIT
}

CPropPageAmen::~CPropPageAmen()
{
}

void CPropPageAmen::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPageAmen)
	DDX_Text(pDX, IDC_EDIT1, m_pszTrigger1);
	DDX_Text(pDX, IDC_EDIT2, m_pszTrigger2);
	DDX_Text(pDX, IDC_EDIT3, m_pszTrigger3);
	DDX_Text(pDX, IDC_EDIT4, m_pszTrigger4);
	DDX_Text(pDX, IDC_EDIT5, m_pszTrigger5);
	DDX_Text(pDX, IDC_EDIT6, m_pszTrigger6);
	DDX_Text(pDX, IDC_EDIT7, m_pszTrigger7);
	DDX_Text(pDX, IDC_EDIT8, m_pszTrigger8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPageAmen, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPageAmen)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPageAmen message handlers
