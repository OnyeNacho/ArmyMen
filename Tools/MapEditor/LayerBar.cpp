// LayerBar.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapEditorDoc.h"
#include "MapFrame.h"
#include "LayerBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayerBar dialog


CLayerBar::CLayerBar()
{
	//{{AFX_DATA_INIT(CLayerBar)
	//}}AFX_DATA_INIT
}


void CLayerBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLayerBar)
	DDX_Control(pDX, IDC_ACTIVATE_LAYER, m_layerCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLayerBar, CDialogBar)
	//{{AFX_MSG_MAP(CLayerBar)
	ON_CBN_SELCHANGE(IDC_ACTIVATE_LAYER, OnSelchangeActivateLayer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


#ifdef _DEBUG
void CLayerBar::AssertValid() const
{
	CDialogBar::AssertValid();
	ASSERT_VALID(&m_layerCtrl);
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayerBar message handlers

BOOL CLayerBar::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
		return CDialogBar::PreTranslateMessage(pMsg);
	}
}

BOOL CLayerBar::Create( CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID )
{
	if (CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID))
	{
		UpdateData(FALSE); // so member variables get initialized
		CString string;
		string.LoadString(IDS_LAYERBARNAME);
		SetWindowText(string);

		// CG: The following block was added by the ToolTips component.
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// Add the tool tips for all the dialog controls
		// Note: the id of the string associated with the control must be 
		// the same as the id of the control for the tooltips to find it.
		m_tooltip.AddTool(GetDlgItem(IDC_ACTIVATE_LAYER), IDC_ACTIVATE_LAYER);
		m_tooltip.AddTool(GetDlgItem(ID_LAYERS_ACTIVATETOP),      ID_LAYERS_ACTIVATETOP);
		m_tooltip.AddTool(GetDlgItem(ID_LAYERS_ACTIVATEBOTTOM),   ID_LAYERS_ACTIVATEBOTTOM);
		m_tooltip.AddTool(GetDlgItem(ID_LAYERS_ACTIVATENEXT),     ID_LAYERS_ACTIVATENEXT);
		m_tooltip.AddTool(GetDlgItem(ID_LAYERS_ACTIVATEPREVIOUS), ID_LAYERS_ACTIVATEPREVIOUS);

		return TRUE;
	}
	return FALSE;
}



void CLayerBar::OnSelchangeActivateLayer() 
{
	CMapEditorDoc *pMap = GetActiveMap();
	if (pMap)
	{
		int index = m_layerCtrl.GetCurSel();
		if (index >= 0)
		{
			if (GetAsyncKeyState(VK_MENU) & 0x8000) // ALT key is pressed
			{
				POSITION pos = pMap->GetLayerPosition(index);
				ASSERT(pos != NULL);

				CMapLayer *pLayer = pMap->GetLayerAt(pos);
				ASSERT(pLayer != NULL);

				// if the selected layer is not the active layer, toggle visibility
				if (pLayer != pMap->GetActiveLayer())
				{
					pLayer->SetVisible(!pLayer->IsVisible());
					pMap->UpdateAllViews(NULL);
				}
			}
			else
			{
				// hide the current layer if the CONTROL key is pressed 
				pMap->SelectActiveLayer(index, (GetAsyncKeyState(VK_CONTROL) & 0x8000));
			}
			pMap->InitFrameLayersList();
		}
	}
}

// TBD: there has to be a better way to dispatch the 
// OnSelChangeLayersList to the active map view.
CMapEditorDoc * CLayerBar::GetActiveMap()
{
	// Note: get the active map from the application frame not the parent frame
	// because a floating toolbar has a minidockframe for its parent.
	CMDIFrameWnd *pFrameWnd = STATIC_DOWNCAST(CMDIFrameWnd, AfxGetApp()->m_pMainWnd);
	if (pFrameWnd)
	{
		CMapFrame *pMapFrame = DYNAMIC_DOWNCAST(CMapFrame, pFrameWnd->MDIGetActive());
		if (pMapFrame)
			return pMapFrame->GetMap();
		else
			TRACE0("CLayerBar: no active map\n");
	}
	else
		TRACE0("CLayerBar: no parent frame?\n");
	return NULL;
}





