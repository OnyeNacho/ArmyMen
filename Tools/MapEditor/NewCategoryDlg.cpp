// NewCategoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "NewCategoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewCategoryDlg dialog


CNewCategoryDlg::CNewCategoryDlg(CTileSet *pTileSet, CWnd* pParent /*=NULL*/)
	: CDialog(CNewCategoryDlg::IDD, pParent)
{
	m_pTileSet = pTileSet;
	//{{AFX_DATA_INIT(CNewCategoryDlg)
	m_pszTitle = _T("");
	//}}AFX_DATA_INIT
}


void CNewCategoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewCategoryDlg)
	DDX_Control(pDX, IDC_CATEGORY_TITLE, m_listCtrl);
	DDX_CBString(pDX, IDC_CATEGORY_TITLE, m_pszTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewCategoryDlg, CDialog)
	//{{AFX_MSG_MAP(CNewCategoryDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCategoryDlg message handlers

BOOL CNewCategoryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_pTileSet != NULL)
	{
		int iCount = m_pTileSet->GetTileCategoryCount();
		for (int i=0; i < iCount; i++)
		{
			m_listCtrl.AddString(m_pTileSet->GetTileCategory(i)->GetTitle());
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
