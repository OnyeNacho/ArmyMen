// AnimPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MapEditor.h"
#include "AnimPropPage.h"
#include "ObjectSet.h"
#include "AnimMapObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CAnimPropPage, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CAnimPropPage property page

CAnimPropPage::CAnimPropPage(CObjectSet *pObjectSet, CAnimMapObject *pObject, int iSequence, int iFrame) 
: CPropertyPage(CAnimPropPage::IDD)
{
	//{{AFX_DATA_INIT(CAnimPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	ASSERT(m_pObject != NULL);
	ASSERT(m_pObjectSet != NULL);

	m_pObject = pObject;
	m_pObjectSet = pObjectSet;
	m_iSequence = iSequence;
	m_iFrame = iFrame;
}

CAnimPropPage::~CAnimPropPage()
{
}

void CAnimPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimPropPage)
	DDX_Control(pDX, IDC_SEQUENCE_LIST, m_listCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CAnimPropPage)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SEQUENCE_LIST, OnItemchangedSequenceList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CAnimPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT((m_listCtrl.GetStyle() & LVS_TYPEMASK)==LVS_REPORT);
	VERIFY(m_sequenceHeader.LoadString(IDS_SEQUENCE));
	VERIFY(m_framesHeader.LoadString(IDS_FRAMES));

	CRect rect;
	m_listCtrl.GetWindowRect(&rect);
	int iWidth = (rect.Width() - 5)/2; // TBD
	m_listCtrl.InsertColumn(0,m_sequenceHeader,LVCFMT_LEFT,iWidth);
	m_listCtrl.InsertColumn(1,m_framesHeader,LVCFMT_LEFT, iWidth, 1);

	int iCount = m_pObject->GetSequenceCount();
	for (int iSequence = 0; iSequence < iCount; iSequence++)
	{
		int nItem = m_listCtrl.InsertItem(iSequence, m_pObject->GetSequenceName(iSequence));
		m_listCtrl.SetItemData(nItem,iSequence);
		int iFrameCount = m_pObject->GetFrameCount(iSequence);
		m_listCtrl.SetItem(nItem, 1, LVIF_TEXT,  GetFullValueString(iFrameCount),0,0,0,iSequence);
	}  
	m_listCtrl.SetItem(m_iSequence, 0, LVIF_STATE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED, m_iSequence); 
	m_listCtrl.UpdateWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAnimPropPage::OnItemchangedSequenceList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem >= 0 && (pNMListView->uChanged & LVIF_STATE) &&
		  (pNMListView->uNewState & LVIS_SELECTED)) 
	{
		m_iSequence = pNMListView->iItem;
		m_iFrame = 0;
	}
	*pResult = 0;
}
