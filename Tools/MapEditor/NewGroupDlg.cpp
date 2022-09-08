// NewGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "NewGroupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewGroupDlg dialog


CNewGroupDlg::CNewGroupDlg(CTileSet *pTileSet, CWnd* pParent /*=NULL*/)
	: CDialog(CNewGroupDlg::IDD, pParent)
{
	m_pTileSet = pTileSet;
	//{{AFX_DATA_INIT(CNewGroupDlg)
	m_pszTitle = _T("");
	//}}AFX_DATA_INIT
}


void CNewGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewGroupDlg)
	DDX_Control(pDX, IDC_GROUP_NAME, m_listCtrl);
	DDX_Text(pDX, IDC_GROUP_NAME, m_pszTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewGroupDlg, CDialog)
	//{{AFX_MSG_MAP(CNewGroupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewGroupDlg message handlers

BOOL CNewGroupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (m_pTileSet != NULL)
	{
		int iCount = m_pTileSet->GetGroupCount();
		for (int i=0; i < iCount; i++)
		{
			m_listCtrl.AddString(m_pTileSet->GetGroupAt(i)->GetTitle());
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
