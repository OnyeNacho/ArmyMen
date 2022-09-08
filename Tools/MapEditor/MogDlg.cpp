// MogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "MogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMogDlg dialog


CMogDlg::CMogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMogDlg)
	m_sName = _T("");
	//}}AFX_DATA_INIT
}


void CMogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMogDlg)
	DDX_Text(pDX, IDC_NAME, m_sName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMogDlg, CDialog)
	//{{AFX_MSG_MAP(CMogDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMogDlg message handlers

void CMogDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
