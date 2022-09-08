// RemDupDlg.cpp : implementation file
//
// Shows the user a list of duplicate tiles and allows them to select
// one or more duplicate tiles to remove.
//
#include "stdafx.h"
#include "mapeditor.h"
#include "RemDupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemDupDlg dialog


CRemDupDlg::CRemDupDlg(CTileSet *pTileSet, CWnd* pParent /*=NULL*/)
	: CDialog(CRemDupDlg::IDD, pParent)
{
	m_pTileSet = pTileSet;
	ASSERT_VALID(pTileSet);
	//{{AFX_DATA_INIT(CRemDupDlg)
	//}}AFX_DATA_INIT
}


void CRemDupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemDupDlg)
	DDX_Control(pDX, IDC_REMDUP_FOUND, m_foundCtrl);
	DDX_Control(pDX, IDC_REMDUP_LIST, m_listCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemDupDlg, CDialog)
	//{{AFX_MSG_MAP(CRemDupDlg)
	ON_BN_CLICKED(IDC_REMDUP_REMOVE, OnRemoveSome)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRemDupDlg message handlers

BOOL CRemDupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_listCtrl.UseTileSet(m_pTileSet);

	int iCount = m_pTileSet->m_searchList.GetSize();
	for (int i=0; i < iCount; i++)
	{
		if (m_pTileSet->m_searchList[i] >= 0)
		{
		    m_listCtrl.SetSel(m_listCtrl.AddItem(i), TRUE);
		}
	}
	char str[20];
    m_foundCtrl.SetWindowText(itoa(m_listCtrl.GetCount(),str,10));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CRemDupDlg::AddTile(int iTile)
{
	m_listCtrl.AddItem(iTile);
	char str[20];
	m_foundCtrl.SetWindowText(itoa(m_listCtrl.GetCount(),str,10));
}


void CRemDupDlg::OnRemoveSome() 
{
	// only remove the selected duplicates.
	for (int i=0; i < m_listCtrl.GetCount(); i++)
	{
		if (!m_listCtrl.GetSel(i))
		{
			int iDup = m_listCtrl.GetItemData(i);
		    m_pTileSet->m_searchList[iDup] = -1; // pretend it was not found
		}
	}
	EndDialog(IDOK);
}



