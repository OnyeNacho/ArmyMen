// LayersDlg.cpp : implementation file
//
// CLayersDlg dialog: allows the user to see and manipulate the current
// set of map layers:
//   1. shows the user a list of the current layers,
//   2. allows the user to toggle the visibility of one or more layers
//   3. allows the user to add, remove, rename layers
//   4. allows the user to reposition layers within the layer hierarchy

#include "stdafx.h"
#include "MapEditor.h"
#include "LayersDlg.h"
#include "MapEditorDoc.h"
#include "MapLayer.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "AttributeLayer.h"
#include "DoorwayLayer.h"
#include "ScenarioLayer.h"
#include "NewLayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayersDlg dialog


CLayersDlg::CLayersDlg(CMapEditorDoc *pMap, CWnd* pParent /*=NULL*/)
	: CDialog(CLayersDlg::IDD, pParent)
{

	ASSERT(pMap != NULL);
	m_pMap = pMap;
	m_iSelected = -1; // nothing selected
	//{{AFX_DATA_INIT(CLayersDlg)
	//}}AFX_DATA_INIT
}


void CLayersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLayersDlg)
	DDX_Control(pDX, IDC_LAYER_LIST, m_listCtrl);
	DDX_Control(pDX, IDC_UP_ITEM, m_upButton);
	DDX_Control(pDX, IDC_NEW_ITEM, m_newButton);
	DDX_Control(pDX, IDC_DOWN_ITEM, m_downButton);
	DDX_Control(pDX, IDC_DELETE_ITEM, m_deleteButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLayersDlg, CDialog)
	//{{AFX_MSG_MAP(CLayersDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_UP_ITEM, OnUpItem)
	ON_BN_CLICKED(IDC_DOWN_ITEM, OnDownItem)
	ON_BN_CLICKED(IDC_DELETE_ITEM, OnDeleteItem)
	ON_BN_CLICKED(IDC_NEW_ITEM, OnNewItem)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LAYER_LIST, OnEndlabeleditLayerList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LAYER_LIST, OnItemchangedLayerList)
	ON_NOTIFY(NM_CLICK, IDC_LAYER_LIST, OnClickLayerList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayersDlg message handlers

BOOL CLayersDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT((m_listCtrl.GetStyle() & LVS_TYPEMASK)==LVS_REPORT);
	VERIFY(m_layerHeader.LoadString(IDS_LAYER));
	VERIFY(m_infoHeader.LoadString(IDS_TYPE));
	m_stateImageList.Create(IDB_STATE,16,1,RGB(255,0,0));
	m_listCtrl.SetImageList(&m_stateImageList,LVSIL_STATE);

	CRect rect;
	m_listCtrl.GetWindowRect(&rect);
	int iWidth = (rect.Width() - 5)/2; // TBD
	m_listCtrl.InsertColumn(0,m_layerHeader,LVCFMT_LEFT,iWidth);
	m_listCtrl.InsertColumn(1,m_infoHeader,LVCFMT_LEFT, iWidth, 1);

	HINSTANCE hInstance = AfxGetInstanceHandle();
	m_deleteButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DELETE)));
	m_newButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_NEW)));
	m_upButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_UP)));
	m_downButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DOWN)));
	
	POSITION pos = m_pMap->m_layers.GetHeadPosition();
	int iLayer = 0;
	while (pos != NULL)
	{
		CMapLayer *pLayer = m_pMap->m_layers.GetNext(pos);
		AddLayer(iLayer++,pLayer,FALSE);
	}
		
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		m_tooltip.AddTool(GetDlgItem(IDC_UP_ITEM), IDC_UP_ITEM);
		m_tooltip.AddTool(GetDlgItem(IDC_DOWN_ITEM), IDC_DOWN_ITEM);
		m_tooltip.AddTool(GetDlgItem(IDC_DELETE_ITEM), IDC_DELETE_ITEM);
		m_tooltip.AddTool(GetDlgItem(IDC_NEW_ITEM), IDC_NEW_ITEM);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLayersDlg::UpdateState(int iLayer, BOOL bVisible)
{
	int iState = bVisible ? 2 : 1; // state is 1-based image index
	m_listCtrl.SetItemState(iLayer,INDEXTOSTATEIMAGEMASK(iState),LVIS_STATEIMAGEMASK);
}

void CLayersDlg::OnDestroy() 
{
	if (m_pMap)
		m_pMap->InitFrameLayersList();

	DelBitmap(m_deleteButton);
	DelBitmap(m_downButton);
	DelBitmap(m_newButton);
	DelBitmap(m_upButton);
	CDialog::OnDestroy();	
}

void CLayersDlg::DelBitmap(CButton& button)
{
	ASSERT(button.m_hWnd);
	HBITMAP hBitmap = button.SetBitmap(NULL);
	if (hBitmap) DeleteObject(hBitmap);
}

void CLayersDlg::SelectItem(int iIndex)
{
	if (iIndex >= 0 && iIndex < m_listCtrl.GetItemCount())
	{
		// TBD: why doesn't this work
		m_listCtrl.SetItemState(iIndex,0xffff, LVIS_FOCUSED | LVIS_SELECTED);
		m_iSelected = iIndex;
	}
	else
		m_iSelected = -1;
}

void CLayersDlg::OnDeleteItem() 
{	
	int iIndex = m_iSelected;
	if (iIndex >= 0)
	{
		POSITION pos = m_pMap->m_layers.FindIndex(iIndex);
		CMapLayer *pLayer = m_pMap->m_layers.GetAt(pos);

		CString msg;
		msg.Format(IDS_ASK_DELETE_LAYER,pLayer->GetTitle());
		if (AfxMessageBox(msg,MB_ICONQUESTION|MB_YESNO) != IDYES)
			return;

		SelectItem(iIndex+1);
		m_listCtrl.DeleteItem(iIndex);
		m_listCtrl.UpdateWindow();

		// see if the user wants to delete the attribute from the
		// tileset as well
		TRY
		{
			CAttributeLayer *pAttribute = DYNAMIC_DOWNCAST(CAttributeLayer, pLayer);
			if (pAttribute)
			{
				CTileSet *pTileSet = m_pMap->GetTileSet();
				CTileAttribute *pTileAttribute;
				CString name = pAttribute->GetTitle();
				if (pTileSet && (pTileAttribute = pTileSet->FindAttribute(name)))
				{
					CString msg;
					AfxFormatString2(msg,IDS_DELETE_TILEATTRIBUTE,name,pTileSet->GetTitle());
					if (AfxMessageBox(msg,MB_ICONQUESTION|MB_YESNO) == IDYES)
						VERIFY(pTileSet->DeleteAttribute(pTileAttribute));
				}
			}
		}
		END_TRY

		if (pLayer->IsVisible())
		{
			pLayer->SetVisible(FALSE);
			if (pLayer == m_pMap->m_pActiveLayer)
				m_pMap->SetActiveLayer();
			m_pMap->UpdateAllViews(NULL);
		}
		m_pMap->m_layers.RemoveAt(pos);
		m_pMap->SetModifiedFlag();
        delete pLayer;
	}
}

void CLayersDlg::OnUpItem() 
{
  int iIndex = m_iSelected;
  if (iIndex > 0)
  {
	  POSITION pos = m_pMap->m_layers.FindIndex(iIndex);
	  CMapLayer *pLayer = m_pMap->m_layers.GetAt(pos);
	  POSITION target = pos;
	  m_pMap->m_layers.GetPrev(target);
	  m_pMap->m_layers.RemoveAt(pos);
	  m_pMap->m_layers.InsertBefore(target,pLayer);
	  if (pLayer->IsVisible())
		  m_pMap->UpdateAllViews(NULL);

	  m_listCtrl.DeleteItem(iIndex);
	  m_iSelected = AddLayer(iIndex-1,pLayer,TRUE);
	  m_pMap->SetModifiedFlag();
  }
}


void CLayersDlg::OnDownItem() 
{
   int iIndex = m_iSelected;
   if (iIndex >= 0)
   {
	  int iCount = m_listCtrl.GetItemCount();
	  if (iIndex < (iCount -1))
	  {
		  POSITION pos = m_pMap->m_layers.FindIndex(iIndex);
		  CMapLayer *pLayer = m_pMap->m_layers.GetAt(pos);
		  m_pMap->m_layers.RemoveAt(pos);

		  pos = m_pMap->m_layers.FindIndex(iIndex);
		  m_pMap->m_layers.InsertAfter(pos,pLayer);
		  if (pLayer->IsVisible())
			  m_pMap->UpdateAllViews(NULL);

		  m_listCtrl.DeleteItem(iIndex);
		  m_iSelected = AddLayer(iIndex+1,pLayer,TRUE);
  		  m_pMap->SetModifiedFlag();

	  }
   }
}



void CLayersDlg::OnNewItem() 
{
	CNewLayerDlg dlg(this);
	CMapLayer *pLayer = NULL;
	if (dlg.DoModal() == IDOK)
	{
		switch(dlg.m_layerType)
		{
			case CNewLayerDlg::eBaseLayer:
				pLayer = m_pMap->CreateBaseLayer();
				break;
			case CNewLayerDlg::eOverlayLayer:
				pLayer = m_pMap->CreateOverlayLayer();
				break;
			case CNewLayerDlg::eObjectLayer:
				pLayer = m_pMap->CreateObjectLayer();
				break;
			case CNewLayerDlg::eAttributeLayer:
				pLayer = m_pMap->CreateAttributeLayer();
				break;
			case CNewLayerDlg::eScenarioLayer:
				pLayer = m_pMap->CreateScenario();
				break;
			case CNewLayerDlg::eDoorwayLayer:
				pLayer = CDoorwayLayer::Create(m_pMap);
				break;
		}
		if (pLayer)
		{
			AddLayer(m_listCtrl.GetItemCount(),pLayer,FALSE);
		}
	}
}

int CLayersDlg::AddLayer(int iIndex, CMapLayer *pLayer, BOOL bSelected)
{
	ASSERT(pLayer != NULL);
	iIndex = m_listCtrl.InsertItem(iIndex, pLayer->GetTitle());
	UpdateState(iIndex, pLayer->IsVisible());
	m_listCtrl.SetItemData(iIndex,(unsigned long)pLayer);
	m_listCtrl.SetItemText(iIndex,1,pLayer->GetInfo());
	if (bSelected) SelectItem(iIndex);
	return iIndex;
}

BOOL CLayersDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);

		return CDialog::PreTranslateMessage(pMsg);
	}
}

void CLayersDlg::OnEndlabeleditLayerList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	ASSERT(pDispInfo != NULL);

	int iIndex = pDispInfo->item.iItem;
	if (iIndex >= 0 && iIndex < m_listCtrl.GetItemCount())
	{
		if (pDispInfo->item.pszText)
		{
			CString pszTitle = pDispInfo->item.pszText;
			CMapLayer *pLayer = (CMapLayer *)m_listCtrl.GetItemData(iIndex);
			CMapLayer *pExistingLayer = m_pMap->FindLayer(pszTitle);
			if (pLayer) 
			{
				if (pExistingLayer && pExistingLayer != pLayer)
				{
					CString msg;
					msg.Format(IDS_DUPLICATE_LAYER, pszTitle);
					UserError(msg);
				}
				else
				{
					pLayer->Rename(pszTitle);
					m_listCtrl.SetItemText(iIndex,0,pszTitle);
					m_pMap->UpdateAllViews(NULL,MEV_UPDATE_LAYER);
					m_pMap->SetModifiedFlag();
				}
			}
		}
		else
			TRACE("layer name edit cancelled\n");
	}
	*pResult = 0;
}

void CLayersDlg::OnItemchangedLayerList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TBD: verify that this is a single selection CListCtrl
	if (pNMListView->iItem >= 0)
	{
		if (pNMListView->uChanged & LVIF_STATE)
		{
			if (pNMListView->uNewState & LVIS_SELECTED)
			{
				m_iSelected = pNMListView->iItem; // new selection
			}
			else if (pNMListView->iItem == m_iSelected)
			{
				m_iSelected = -1; // no selection
			}
		}

		// TRACE("selected layer is %d\n", m_iSelected);
	}	
	*pResult = 0;
}

void CLayersDlg::OnClickLayerList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UINT uFlags=0;
	CPoint point;

	if (GetCursorPos(&point))
	{
		m_listCtrl.ScreenToClient(&point);
		int nHitItem = m_listCtrl.HitTest(point,&uFlags);
		if (uFlags & LVHT_ONITEMSTATEICON)
		{
			CMapLayer *pLayer = (CMapLayer *)m_listCtrl.GetItemData(nHitItem);
			if (pLayer)
			{
				pLayer->SetVisible(!pLayer->IsVisible());
				UpdateState(nHitItem,pLayer->IsVisible());
				m_pMap->SetActiveLayer();
				m_pMap->UpdateAllViews(NULL);
				m_pMap->SetModifiedFlag();
			}
		}
	}
	*pResult = 0;
}


