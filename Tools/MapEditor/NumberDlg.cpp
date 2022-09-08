// NumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "NumberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumberDlg dialog


CNumberDlg::CNumberDlg(LPCTSTR lpszCaption, int iNumber, int iMin, int iMax, CWnd* pParent /*=NULL*/)
	: CDialog(CNumberDlg::IDD, pParent)
{
	ASSERT(iMin <= iMax);
	ASSERT(iNumber >= iMin);
	ASSERT(iNumber <= iMax);
	m_iMin = iMin;
	m_iMax = iMax;
	//{{AFX_DATA_INIT(CNumberDlg)
	m_iNumber = iNumber;
	m_pszCaption = lpszCaption;
	//}}AFX_DATA_INIT
}


void CNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNumberDlg)
	DDX_Text(pDX, IDC_GET_NUMBER, m_iNumber);
	DDX_Text(pDX, IDC_GET_NUMBER_CAPTION, m_pszCaption);
	//}}AFX_DATA_MAP

	DDV_MinMaxInt(pDX, m_iNumber, m_iMin, m_iMax);
}


BEGIN_MESSAGE_MAP(CNumberDlg, CDialog)
	//{{AFX_MSG_MAP(CNumberDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumberDlg message handlers

