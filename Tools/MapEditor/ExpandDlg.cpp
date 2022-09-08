// ExpandDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "ExpandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExpandDlg dialog


CExpandDlg::CExpandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpandDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpandDlg)
	m_iMove = 0;
	m_iWidth = 0;
	m_iHeight = 0;
	//}}AFX_DATA_INIT
}


void CExpandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpandDlg)
	DDX_Radio(pDX, IDC_TOP, m_iMove);
	DDX_Text(pDX, IDC_WIDTH, m_iWidth);
	DDX_Text(pDX, IDC_HEIGHT, m_iHeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpandDlg, CDialog)
	//{{AFX_MSG_MAP(CExpandDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpandDlg message handlers
