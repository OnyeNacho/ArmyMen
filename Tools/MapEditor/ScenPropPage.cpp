// ScenPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "ScenPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScenPropPage property page

IMPLEMENT_DYNCREATE(CScenPropPage, CPropertyPage)

CScenPropPage::CScenPropPage() : CPropertyPage(CScenPropPage::IDD)
{
	//{{AFX_DATA_INIT(CScenPropPage)
	m_pszResources = g_pszScenarioResources;
	m_pszUnits = g_pszScenarioUnits;
	//}}AFX_DATA_INIT
}

CScenPropPage::~CScenPropPage()
{
}

void CScenPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScenPropPage)
	DDX_Text(pDX, IDC_SCENARIO_RSRCNAME, m_pszResources);
	DDX_Text(pDX, IDC_SCENARIO_UNITNAME, m_pszUnits);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScenPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CScenPropPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScenPropPage message handlers
