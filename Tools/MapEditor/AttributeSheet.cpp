// AttributeSheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Mapeditor.h"
#include "MapEditorDoc.h"
#include "AttributeSheet.h"
#include "AnimMapObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributeSheet

IMPLEMENT_DYNAMIC(CAttributeSheet, CPropertySheet)

CAttributeSheet::CAttributeSheet(UINT nTitleID, CAttributeTarget *pTarget, void *pTargetData, CWnd* pParent)
	 : CPropertySheet(nTitleID, pParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().
    m_pAttributePage = new CAttributesDlg(IDS_ATTRIBUTES,pTarget,pTargetData);
	m_pDoc = NULL;
	AddPage(m_pAttributePage);
}

CAttributeSheet::~CAttributeSheet()
{
	delete m_pAttributePage;
}


BEGIN_MESSAGE_MAP(CAttributeSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CAttributeSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAttributeSheet message handlers

BOOL CAttributeSheet::OnInitDialog()
{
	m_pAttributePage->m_pDoc = m_pDoc;
	m_pAttributePage->m_pObjs = m_pObjs;
	BOOL bResult = CPropertySheet::OnInitDialog();

	// add a preview window to the property sheet.
	CRect rectWnd;
	GetWindowRect(rectWnd);
	SetWindowPos(NULL, 0, 0,
		rectWnd.Width() + 100,
		rectWnd.Height(),
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	CRect rectPreview(rectWnd.Width() + 25, 25,
		rectWnd.Width()+75, 75);

	m_wndPreview.Create(NULL, NULL, WS_CHILD|WS_VISIBLE,
		rectPreview, this, 0x1000);

	CenterWindow();
	return bResult;
}


