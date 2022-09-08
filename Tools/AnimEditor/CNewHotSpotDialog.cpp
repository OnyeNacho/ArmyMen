// CNewHotSpotDialog.cpp : implementation file
//

#include "stdafx.h"
#include "animeditor.h"
#include "CNewHotSpotDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewHotSpotDialog dialog

CString CNewHotSpotDialog::csNameLast = "";

CNewHotSpotDialog::CNewHotSpotDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNewHotSpotDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewHotSpotDialog)
	csHSpotName = _T("");
	csSequenceName = _T("");
	//}}AFX_DATA_INIT
	csHSpotName = csNameLast;
}


void CNewHotSpotDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewHotSpotDialog)
	DDX_Text(pDX, IDC_EDIT_HOTSPOTNAME, csHSpotName);
	DDV_MaxChars(pDX, csHSpotName, 30);
	DDX_Text(pDX, IDC_STATIC_SEQUENCENAME, csSequenceName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewHotSpotDialog, CDialog)
	//{{AFX_MSG_MAP(CNewHotSpotDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewHotSpotDialog message handlers
