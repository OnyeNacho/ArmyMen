// RotateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "RotateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg dialog


CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotateDlg)
	m_iType = 0;
	m_iRotDir = 0;
	m_iFlipDir = 0;
	//}}AFX_DATA_INIT
}


void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotateDlg)
	DDX_Radio(pDX, IDC_ROTATE, m_iType);
	DDX_Radio(pDX, IDC_RT_CW, m_iRotDir);
	DDX_Radio(pDX, IDC_FL_H, m_iFlipDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
	//{{AFX_MSG_MAP(CRotateDlg)
	ON_BN_CLICKED(IDC_ROTATE, OnRotate)
	ON_BN_CLICKED(IDC_FLIP, OnFlip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg message handlers

void CRotateDlg::OnRotate() 
{
	ChangeMode();
}

void CRotateDlg::OnFlip() 
{
	ChangeMode();
}

void CRotateDlg::ChangeMode()
{
	UpdateData(TRUE);
	if (0 == m_iType)
	{
		// Disable Flip Items
		GetDlgItem(IDC_RT_CW)->EnableWindow(TRUE);
		GetDlgItem(IDC_RT_CCW)->EnableWindow(TRUE);
		GetDlgItem(IDC_RT_FULLCW)->EnableWindow(TRUE);
		GetDlgItem(IDC_FL_H)->EnableWindow(FALSE);
		GetDlgItem(IDC_FL_V)->EnableWindow(FALSE);
	}
	else
	{
		// Disable Rotate Items
		GetDlgItem(IDC_RT_CW)->EnableWindow(FALSE);
		GetDlgItem(IDC_RT_CCW)->EnableWindow(FALSE);
		GetDlgItem(IDC_RT_FULLCW)->EnableWindow(FALSE);
		GetDlgItem(IDC_FL_H)->EnableWindow(TRUE);
		GetDlgItem(IDC_FL_V)->EnableWindow(TRUE);
	}
}
