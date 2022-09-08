// ScriptsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "ScriptsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptsDlg dialog


CScriptsDlg::CScriptsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScriptsDlg)
	m_sFile = _T("");
	m_iScript = 0;
	m_sText = _T("");
	//}}AFX_DATA_INIT
}


void CScriptsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptsDlg)
	DDX_Text(pDX, IDC_FILE, m_sFile);
	DDX_CBIndex(pDX, IDC_SLIST, m_iScript);
	DDX_Text(pDX, IDC_TEXT, m_sText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScriptsDlg, CDialog)
	//{{AFX_MSG_MAP(CScriptsDlg)
	ON_CBN_SELCHANGE(IDC_SLIST, OnListChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptsDlg message handlers

void CScriptsDlg::OnListChange() 
{
	UpdateData(TRUE);
	if (0 == m_iScript)
	{
		m_sPFile = m_sFile;
		m_sPText = m_sText;
		m_sFile = m_sAFile;
		m_sText = m_sAText;
	}
	else
	{
		m_sAFile = m_sFile;
		m_sAText = m_sText;
		m_sFile = m_sPFile;
		m_sText = m_sPText;
	}
	UpdateData(FALSE);
}

BOOL CScriptsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_sFile = m_sAFile;
	m_sText = m_sAText;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScriptsDlg::OnOK() 
{
	UpdateData(TRUE);
	if (0 == m_iScript)
	{
		m_sAFile = m_sFile;
		m_sAText = m_sText;
	}
	else
	{
		m_sPFile = m_sFile;
		m_sPText = m_sText;
	}
	CDialog::OnOK();
}
