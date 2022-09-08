// ShowUsageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "ShowUsageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowUsageDlg dialog


CShowUsageDlg::CShowUsageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowUsageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowUsageDlg)
	m_iUsageThreshold = 0;
	//}}AFX_DATA_INIT
}


void CShowUsageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowUsageDlg)
	DDX_Text(pDX, IDC_USAGE_THRESHOLD, m_iUsageThreshold);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowUsageDlg, CDialog)
	//{{AFX_MSG_MAP(CShowUsageDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowUsageDlg message handlers
