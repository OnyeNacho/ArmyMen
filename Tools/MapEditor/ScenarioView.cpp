// ScenarioView.cpp : implementation file
//
// Note: the scenarioView uses m_iCategory to represent the 
// "player" type.
//
#include "stdafx.h"
#include "MapEditor.h"
#include "MapFrame.h"
#include "MapEditorDoc.h"
#include "ScenarioSet.h"
#include "ScenarioLayer.h"
#include "ScenarioView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScenarioView

IMPLEMENT_DYNCREATE(CScenarioView, CObjectSetView)

CScenarioView::CScenarioView() 
	: CObjectSetView(CScenarioView::IDD)
{
	m_pScenario = NULL;
	//{{AFX_DATA_INIT(CScenarioView)
	m_nTotal = 0;
	m_pszDeployed = _T("");
	//}}AFX_DATA_INIT
}

CScenarioView::~CScenarioView()
{
}

void CScenarioView::DoDataExchange(CDataExchange* pDX)
{
	CObjectSetView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScenarioView)
	DDX_Control(pDX, IDC_SCENARIO_DEPLOYED, m_deployedCtrl);
	DDX_Control(pDX, IDC_SCENARIO_ITEMID, m_itemNameCtrl);
	DDX_Control(pDX, IDC_SCENARIO_TOTAL, m_totalCtrl);
	DDX_Control(pDX, IDC_SCENARIO_RESOURCES, m_resourceCtrl);
	DDX_Text(pDX, IDC_SCENARIO_TOTAL, m_nTotal);
	DDX_Text(pDX, IDC_SCENARIO_DEPLOYED, m_pszDeployed);
	//}}AFX_DATA_MAP


	CScenarioSet *pScenarioSet = GetDocument();
	UINT nMin = 0;
	if (pScenarioSet && m_pScenario && pScenarioSet->IsItemDeployable())
	{
		CScenarioInfo info;
		int iItem = pScenarioSet->GetCurrentItem();
		ASSERT(iItem >= 0);
		CMapObject *pObject = pScenarioSet->GetObject(iItem);
		m_pScenario->GetObjectInfo(pObject,info);
		nMin = info.m_nDeployed;
		
	}
	DDV_MinMaxUInt(pDX, m_nTotal, nMin, UINT_MAX);
}


BEGIN_MESSAGE_MAP(CScenarioView, CObjectSetView)
	//{{AFX_MSG_MAP(CScenarioView)
	ON_LBN_SELCHANGE(IDC_SCENARIO_RESOURCES, OnSelchangeResource)
	ON_EN_KILLFOCUS(IDC_SCENARIO_TOTAL, OnKillFocusScenarioTotal)
	ON_LBN_SELCHANGE(IDC_OBJECTSET_LIST, OnSelchangeObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScenarioView diagnostics

#ifdef _DEBUG
void CScenarioView::AssertValid() const
{
	CObjectSetView::AssertValid();
}

void CScenarioView::Dump(CDumpContext& dc) const
{
	CObjectSetView::Dump(dc);
}
#endif //_DEBUG

CScenarioSet* CScenarioView::GetDocument() 
{
   ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScenarioSet)));
   return (CScenarioSet*)m_pDocument;
}
/////////////////////////////////////////////////////////////////////////////

void CScenarioView::AdjustControls()
{
	CRect wndRect,newRect,listRect;

	GetWindowRect(&wndRect);
	if (!m_itemCtrl.m_hWnd) return;

	// size m_tabCtrl to fill the rest of the view
	m_tabCtrl.GetWindowRect(&newRect);
	newRect.right = wndRect.right - 5;
	newRect.bottom = wndRect.bottom - 5;
    ScreenToClient(&newRect);
	m_tabCtrl.MoveWindow(&newRect,FALSE);

	// size m_listCtrl to fill left half the of m_tabCtrl area
    m_tabCtrl.GetItemRect(0,&listRect);
	newRect.DeflateRect(5,listRect.Height()+5,5,5);

	int iWidth = newRect.Width() / 2;
	newRect.right = newRect.left + iWidth - 5;
	m_listCtrl.MoveWindow(&newRect, FALSE);

	// size the m_resourceCtrl to fill the right half of m_tabCtrl area
	newRect.OffsetRect(iWidth+5,0);
    m_resourceCtrl.MoveWindow(&newRect,FALSE);
	Invalidate();
}

void CScenarioView::RenewListCtrl(BOOL bRepaint)
{
	// update the list control to display the correct set of objects
	CWaitCursor wait;
	CObjectSet *pObjectSet = CObjectSetView::GetDocument();
	m_listCtrl.UseObjectSet(pObjectSet, GetHPalette(), FALSE); // this does a ResetContent()
    m_resourceCtrl.UseObjectSet(pObjectSet, GetHPalette(), FALSE);
	TRY
	{
		// fill the list with only those objects in the current category
		int iUnits = m_iCategory * 2;
		int iResources = iUnits + 1;

		CCategory *pCategory = pObjectSet->GetCategory(iUnits);
		ASSERT(pCategory != NULL);

		int i,iItem,iCount = pCategory->GetItemCount();
		for (i=0; i < iCount; i++)
		{
			iItem = pCategory->GetItemAt(i);
			m_listCtrl.AddItem(iItem);
		}

		pCategory = pObjectSet->GetCategory(iResources);
		ASSERT(pCategory != NULL);

		iCount = pCategory->GetItemCount();
		for (i=0; i < iCount; i++)
		{
			iItem = pCategory->GetItemAt(i);
			m_resourceCtrl.AddItem(iItem);
		}

		if (bRepaint) 
		{
			m_listCtrl.UpdateWindow();
			m_resourceCtrl.UpdateWindow();
		}
	}
	END_TRY
}

void CScenarioView::RenewItemCtrl(BOOL bRepaint)
{
	CScenarioSet *pScenarioSet = GetDocument();
	CMapObject *pObject = pScenarioSet->GetCurrentObject();
    CString tmp;

	// TBD: resize the item so we can draw it in proportion 

	m_itemCtrl.SetButtonStyle(m_itemCtrl.GetButtonStyle(), bRepaint);
	m_itemNameCtrl.SetWindowText(pObject ? pScenarioSet->GetFullObjectName(pObject) : _T(""));

	CScenarioInfo info;
	BOOL bEnable = FALSE;
	int iPlayer = -1, iItem = -1;
    BOOL bDeployed = FALSE;

	if (m_pScenario && pObject)
	{
		m_pScenario->GetObjectInfo(pObject->GetKey(), info);
		iItem = pScenarioSet->GetCurItem(iPlayer, bDeployed);
	    bEnable = TRUE;
	}
	m_nTotal = info.m_nTotal;
	m_pszDeployed.Format(IDS_SCENARIO_DEPLOYED, info.m_nDeployed);
	m_totalCtrl.EnableWindow(bEnable);
	m_deployedCtrl.EnableWindow(bDeployed);
    UpdateData(FALSE);

	if (bRepaint && pObject)
	{
		if (m_tabCtrl.GetCurSel() != iPlayer)
		{
			m_tabCtrl.SetCurSel(iPlayer);
			RenewListCtrl();
		}
		if (bDeployed) 
		{
			m_listCtrl.ResetSelection(m_listCtrl.FindItem(iItem));
			m_resourceCtrl.ClearSelection();
		}
		else
		{
			m_listCtrl.ClearSelection();
			m_resourceCtrl.ResetSelection(m_resourceCtrl.FindItem(iItem));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScenarioView message handlers

void CScenarioView::OnSelchangeResource() 
{
	int iItem = m_resourceCtrl.GetLastItem(); // get the list item that was last selected
	if (iItem < 0)
		return;

    iItem = m_resourceCtrl.GetItemData(iItem); 

	// set the current item, which in turn will update all the views
	GetDocument()->SetCurrentItem(iItem,FALSE);	

	m_listCtrl.ClearSelection();
	m_deployedCtrl.EnableWindow(FALSE);
}

void CScenarioView::OnSelchangeObject() 
{
	int iItem = m_listCtrl.GetLastItem(); // get the list item that was last selected
	if (iItem < 0)
		return;

    iItem = m_listCtrl.GetItemData(iItem); 

	// set the current item, which in turn will update all the views
	GetDocument()->SetCurrentItem(iItem,TRUE);

	m_resourceCtrl.ClearSelection();
	m_deployedCtrl.EnableWindow(TRUE);
}

void CScenarioView::RenewTabCtrl(BOOL bRepaint/*=TRUE*/)
{
	m_tabCtrl.DeleteAllItems();

	
	TC_ITEM item;
	CString tab;
	item.mask = TCIF_TEXT;

	CScenarioSet *pScenarioSet = GetDocument();
	ASSERT(pScenarioSet != NULL);

	int iCount = pScenarioSet->GetPlayerCount();
	for (int i=0; i < iCount; i++)
	{
		item.pszText = (LPSTR)((LPCSTR)pScenarioSet->GetPlayerName(i));
		m_tabCtrl.InsertItem(i,&item);
	}

	BOOL bDeployable;
	pScenarioSet->GetCurItem(m_iCategory, bDeployable);
	ASSERT(m_iCategory >= -1 && m_iCategory < iCount);

	m_tabCtrl.SetCurSel(m_iCategory);
}

void CScenarioView::OnInitialUpdate() 
{
	CMapFrame *pFrame = STATIC_DOWNCAST(CMapFrame,GetParentFrame());
	ASSERT(pFrame != NULL);

	CMapEditorDoc *pMap = pFrame->GetMap();
	ASSERT(pMap != NULL);

	m_pScenario = STATIC_DOWNCAST(CScenarioLayer, pMap->GetActiveLayer());
	ASSERT(m_pScenario != NULL);

	CObjectSetView::OnInitialUpdate();
}


void CScenarioView::OnKillFocusScenarioTotal() 
{
	if (m_pScenario)
	{
		CScenarioSet *pScenarioSet = GetDocument();
		int iItem = pScenarioSet->GetCurrentItem();
		if (iItem >= 0)
		{
			BOOL bDeployable = pScenarioSet->IsItemDeployable();
			CScenarioInfo info;
			UpdateData(TRUE);

			LPCTSTR pszKey = pScenarioSet->GetObject(iItem)->GetKey();
			if (!m_pScenario->SetObjectTotal(pszKey, iItem, m_nTotal,bDeployable));
			{
				m_pScenario->GetObjectInfo(pszKey,info);
				m_nTotal = info.m_nTotal;
				UpdateData(FALSE);
			}
		}
	}
}



