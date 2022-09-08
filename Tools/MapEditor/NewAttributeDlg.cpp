// NewAttributeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "AttributeLayer.h"
#include "NewAttributeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewAttributeDlg dialog

#define DEFAULT_BITS 8
#define DEFAULT_MAX  "255"

CNewAttributeDlg::CNewAttributeDlg(CWnd* pParent /*=NULL*/, LPCTSTR lpszName /*=NULL*/)
	: CDialog(CNewAttributeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewAttributeDlg)
	m_maxString = _T(DEFAULT_MAX);
	m_pszName = lpszName ? lpszName : _T("");
	m_nBitCount = DEFAULT_BITS;
	m_iDefaultValue = 0;
	//}}AFX_DATA_INIT
}


void CNewAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewAttributeDlg)
	DDX_Control(pDX, IDC_ATTRIBUTE_BITS, m_bitCtrl);
	DDX_Control(pDX, IDC_ATTRIBUTE_DEFAULT, m_defaultCtrl);
	DDX_Text(pDX, IDC_ATTRIBUTE_MAX, m_maxString);
	DDX_Text(pDX, IDC_ATTRIBUTE_NAME, m_pszName);
	DDX_Text(pDX, IDC_ATTRIBUTE_BITCOUNT, m_nBitCount);
	DDV_MinMaxUInt(pDX, m_nBitCount, 1, MAX_ATTRIBUTE_BITS);
	DDX_Text(pDX, IDC_ATTRIBUTE_DSTRING, m_iDefaultValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewAttributeDlg, CDialog)
	//{{AFX_MSG_MAP(CNewAttributeDlg)
	ON_NOTIFY(UDN_DELTAPOS, IDC_ATTRIBUTE_BITS, OnDeltaposAttributeBits)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewAttributeDlg message handlers

void CNewAttributeDlg::OnDeltaposAttributeBits(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int iBits = pNMUpDown->iPos + pNMUpDown->iDelta;
	int iMax = (1 << iBits) - 1;
	int iDefault = min(m_defaultCtrl.GetPos(), iMax);
	m_defaultCtrl.SetRange(0-iMax, iMax);
	m_defaultCtrl.SetPos(iDefault);
	m_maxString.Format("0 - %d", iMax);
	UpdateData(FALSE); // set values
	*pResult = 0;
}

BOOL CNewAttributeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_defaultCtrl.SetPos(0);
	m_bitCtrl.SetRange(1,MAX_ATTRIBUTE_BITS);
	m_bitCtrl.SetPos(DEFAULT_BITS);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
