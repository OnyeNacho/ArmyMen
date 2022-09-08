// FindDupDlg.cpp : implementation file
// Asks the user for the search tolerance value.

#include "stdafx.h"
#include "mapeditor.h"
#include "FindDupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindDupDlg dialog


CFindDupDlg::CFindDupDlg(int iTolerance, int iMaxTol, CWnd* pParent /*=NULL*/)
	: CDialog(CFindDupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDupDlg)
	m_iTolerance = iTolerance;
	m_iMaxTol = iMaxTol;
	//}}AFX_DATA_INIT
}


void CFindDupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDupDlg)
	DDX_Control(pDX, IDC_TILESET_MAXTOL, m_maxCtrl);
	DDX_Text(pDX, IDC_TILESET_TOLERANCE, m_iTolerance);
	DDV_MinMaxInt(pDX, m_iTolerance, -1, m_iMaxTol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDupDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindDupDlg message handlers

BOOL CFindDupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char str[20];
	m_maxCtrl.SetWindowText(itoa(m_iMaxTol,str,10));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
