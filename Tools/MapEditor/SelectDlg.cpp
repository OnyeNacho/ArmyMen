// SelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "SelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog


CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectDlg)
	m_iBX = 0;
	m_iBY = 0;
	m_iEX = 0;
	m_iEY = 0;
	m_bReset = FALSE;
	//}}AFX_DATA_INIT
	m_bViewable = FALSE;
}


void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDlg)
	DDX_Text(pDX, IDC_BX, m_iBX);
	DDX_Text(pDX, IDC_BY, m_iBY);
	DDX_Text(pDX, IDC_EX, m_iEX);
	DDX_Text(pDX, IDC_EY, m_iEY);
	DDX_Check(pDX, IDC_RESET, m_bReset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg message handlers

void CSelectDlg::SetViewArea()
{
	m_bViewable = TRUE;
}

BOOL CSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_bViewable)
	{
		CString sTitle;
		sTitle.LoadString(IDS_VIEWAREA);
		SetWindowText(sTitle);
		GetDlgItem(IDC_RESET)->EnableWindow(FALSE);
		GetDlgItem(IDC_RESET)->ShowWindow(SW_HIDE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
