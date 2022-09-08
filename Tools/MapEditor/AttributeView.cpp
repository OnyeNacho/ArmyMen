// AttributeView.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "AttributeView.h"
#include "AttributeLayer.h"
#include "TileLayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// #define USE_ATTR_DDV   // to use custom DDV validation code

/////////////////////////////////////////////////////////////////////////////
// CAttributeView

IMPLEMENT_DYNCREATE(CAttributeView, CFormView)

CAttributeView::CAttributeView()
	: CFormView(CAttributeView::IDD)
{
	m_pAttributeLayer = NULL;
	//{{AFX_DATA_INIT(CAttributeView)
	m_iColorType = -1;
	m_bUpdateDefault = FALSE;
	m_bUpdateTiles = FALSE;
	m_bShowObjectAttributes = FALSE;
	//}}AFX_DATA_INIT
	m_iDefault = 0;
	m_iValue = 0;
}

CAttributeView::~CAttributeView()
{
}

void CAttributeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttributeView)
	DDX_Control(pDX, IDC_ATTRIBUTE_TILELAYER, m_layerCtrl);
	DDX_Control(pDX, IDC_ATTRIBUTE_MAX, m_maxCtrl);
	DDX_Control(pDX, IDC_ATTRIBUTE_VALUE_UPDOWN, m_valueCtrl);
	DDX_Control(pDX, IDC_ATTRIBUTE_DEFAULT_UPDOWN, m_defaultCtrl);
	DDX_Control(pDX, IDC_ATTRIBUTE_COLOR, m_colorCtrl);
	DDX_Radio(pDX, IDC_ATTRIBUTE_SOLID, m_iColorType);
	DDX_Check(pDX, IDC_ATTRIBUTE_UPDATE_DEFAULT, m_bUpdateDefault);
	DDX_Check(pDX, IDC_ATTRIBUTE_UPDATE_TILES, m_bUpdateTiles);
	DDX_Check(pDX, IDC_ATTRIBUTE_SHOW_OBJECTS, m_bShowObjectAttributes);
	//}}AFX_DATA_MAP

#ifdef USE_ATTR_DDV
	ASSERT(m_pAttributeLayer != NULL);

	// TBD: why doesn't this work? It works in the scenario view!
	// Is it because the text gadget has a "buddy" control?

	int iMax = m_pAttributeLayer->GetMaxValue();
	//DDV_MinMaxUnsigned(pDX, m_iValue, 0-iMax, iMax);
	//DDV_MinMaxUnsigned(pDX, m_iDefault, 0-iMax, iMax);
#endif

}


BEGIN_MESSAGE_MAP(CAttributeView, CFormView)
	//{{AFX_MSG_MAP(CAttributeView)
	ON_BN_CLICKED(IDC_ATTRIBUTE_COLOR, OnAttributeColor)
	ON_NOTIFY(UDN_DELTAPOS, IDC_ATTRIBUTE_DEFAULT_UPDOWN, OnDeltaposAttributeDefault)
	ON_NOTIFY(UDN_DELTAPOS, IDC_ATTRIBUTE_VALUE_UPDOWN, OnDeltaposAttributeValue)
	ON_EN_CHANGE(IDC_ATTRIBUTE_VALUE, OnChangeAttributeValue)
	ON_EN_CHANGE(IDC_ATTRIBUTE_DEFAULT, OnChangeAttributeDefault)
	ON_BN_CLICKED(IDC_ATTRIBUTE_SOLID, OnAttributeSolid)
	ON_BN_CLICKED(IDC_ATTRIBUTE_GREYSCALE, OnAttributeGreyscale)
	ON_BN_CLICKED(IDC_ATTRIBUTE_INVERTEDGREY, OnAttributeInvertedGrey)
	ON_BN_CLICKED(IDC_ATTRIBUTE_UPDATE_DEFAULT, OnAttributeUpdateDefault)
	ON_BN_CLICKED(IDC_ATTRIBUTE_UPDATE_TILES, OnAttributeUpdateTiles)
	ON_BN_CLICKED(IDC_ATTRIBUTE_SHOW_OBJECTS, OnAttributeShowObjects)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributeView diagnostics

#ifdef _DEBUG
void CAttributeView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAttributeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMapEditorDoc* CAttributeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditorDoc)));
	return (CMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAttributeView message handlers

void CAttributeView::OnInitialUpdate() 
{
	m_pAttributeLayer = DYNAMIC_DOWNCAST(CAttributeLayer, GetDocument()->GetActiveLayer());
	ASSERT(m_pAttributeLayer != NULL);

	m_iColorType = (int)m_pAttributeLayer->GetColorType();
	m_bShowObjectAttributes = m_pAttributeLayer->GetShowObjectAttributes();
	m_pAttributeLayer->SetUpdateDefault(FALSE);
	m_pAttributeLayer->SetUpdateTiles(FALSE);
	m_pAttributeLayer->SetTileLayer(NULL);

	CFormView::OnInitialUpdate(); // this does an UpdateData

	// Note: even if you use data exchange validation hooks, you
	// have to set the range for the up/down controls.
	int iMax = m_pAttributeLayer->GetMaxValue();
	m_defaultCtrl.SetRange(0-iMax, iMax);
	m_valueCtrl.SetRange(0-iMax, iMax);
	UpdateValueFormat();
    			
	m_colorCtrl.SetColor(m_pAttributeLayer->GetColor());
	UpdateTileLayers();
}

void CAttributeView::UpdateValueFormat()
{
	//t iBase =  g_bDecimal ? 10 : 16;
	int iBase =  10;
    
	// do this before calling SetBase() so the controls DON'T reset the values to 0.
	m_iDefault = m_pAttributeLayer->GetDefaultValue();
	m_iValue = m_pAttributeLayer->GetCurrentValue();
	CString sBuf;
	CString sOut;
	_ltoa(m_iValue, sBuf.GetBufferSetLength(20), (g_bDecimal) ? 10 : 16);
	sBuf.ReleaseBuffer(-1);
	if (!g_bDecimal)
	{
		sOut = "0x";
		sOut += sBuf;
	}
	else
		sOut = sBuf;
	SetDlgItemText(IDC_ATTRIBUTE_VALUE, sOut);
	
	_ltoa(m_iDefault, sBuf.GetBufferSetLength(20), (g_bDecimal) ? 10 : 16);
	sBuf.ReleaseBuffer(-1);
	if (!g_bDecimal)
	{
		sOut = "0x";
		sOut += sBuf;
	}
	else
		sOut = sBuf;
	SetDlgItemText(IDC_ATTRIBUTE_DEFAULT, sOut);

	m_valueCtrl.SetBase(iBase);
	m_defaultCtrl.SetBase(iBase);

	int iMax = m_pAttributeLayer->GetMaxValue();
	m_defaultCtrl.SetRange(0-iMax, iMax);
	m_valueCtrl.SetRange(0-iMax, iMax);
	m_defaultCtrl.SetPos(m_iDefault);
	m_valueCtrl.SetPos(m_iValue);

	m_maxCtrl.SetWindowText(GetFullValueString(m_pAttributeLayer->GetMaxValue()));
	m_maxCtrl.UpdateWindow();
}

void CAttributeView::OnAttributeColor() 
{
	COLORREF color = m_pAttributeLayer->GetColor();
	if (DoChooseColor(this,color))
	{
		CWaitCursor wait;
		m_pAttributeLayer->SetColor(color);
		m_pAttributeLayer->SetColorType(EAttrSolid);
		m_colorCtrl.SetColor(color);
		m_iColorType = (int)m_pAttributeLayer->GetColorType();
		UpdateData(FALSE);
	}
}

void CAttributeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint & MEV_UPDATE_ATTRIBUTE_FORMAT)
		UpdateValueFormat();

	if (lHint & MEV_UPDATE_ATTRIBUTE_VALUE)
		m_valueCtrl.SetPos(m_pAttributeLayer->GetCurrentValue());

	if (lHint & MEV_UPDATE_LAYER)
		UpdateTileLayers();
}


void CAttributeView::OnDeltaposAttributeDefault(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int iValue = pNMUpDown->iPos + pNMUpDown->iDelta;
	*pResult = !m_pAttributeLayer->SetDefaultValue(iValue);
	CString sBuf;
	CString sOut;
	_ltoa(iValue, sBuf.GetBufferSetLength(20), (g_bDecimal) ? 10 : 16);
	sBuf.ReleaseBuffer(-1);
	if (!g_bDecimal)
	{
		sOut = "0x";
		sOut += sBuf;
	}
	else
		sOut = sBuf;
	_ltoa(iValue, sBuf.GetBufferSetLength(20), (g_bDecimal) ? 10 : 16);
	sBuf.ReleaseBuffer(-1);
	SetDlgItemText(IDC_ATTRIBUTE_DEFAULT, sBuf);
}

void CAttributeView::OnDeltaposAttributeValue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int iValue = pNMUpDown->iPos + pNMUpDown->iDelta;
	*pResult = !m_pAttributeLayer->SetCurrentValue(iValue);
	CString sBuf;
	CString sOut;
	_ltoa(iValue, sBuf.GetBufferSetLength(20), (g_bDecimal) ? 10 : 16);
	sBuf.ReleaseBuffer(-1);
	if (!g_bDecimal)
	{
		sOut = "0x";
		sOut += sBuf;
	}
	else
		sOut = sBuf;
	SetDlgItemText(IDC_ATTRIBUTE_VALUE, sOut);
	m_iValue = iValue;
	m_pAttributeLayer->SetCurrentValue(m_iValue);
}

void CAttributeView::OnChangeAttributeValue() 
{
	CString sValue;
	if (NULL != m_valueCtrl.m_hWnd)
	{
		GetDlgItemText(IDC_ATTRIBUTE_VALUE, sValue);
		if (!sValue.IsEmpty())
			UpdateData(TRUE);
	}
	if (g_bDecimal)
	{
		m_iValue = atoi(sValue.GetBufferSetLength(20));
		sValue.ReleaseBuffer(-1);
	}
	if (m_valueCtrl.m_hWnd && !m_pAttributeLayer->SetCurrentValue(m_iValue))
		UpdateValueFormat();
}

void CAttributeView::OnChangeAttributeDefault() 
{
	CString sValue;
	if (NULL != m_defaultCtrl.m_hWnd)
	{
		GetDlgItemText(IDC_ATTRIBUTE_DEFAULT, sValue);
		if (!sValue.IsEmpty())
			UpdateData(TRUE);
	}
	if (g_bDecimal)
	{
		m_iDefault = atoi(sValue.GetBufferSetLength(20));
		sValue.ReleaseBuffer(-1);
	}
	if (m_defaultCtrl.m_hWnd && !m_pAttributeLayer->SetDefaultValue(m_iDefault))
		UpdateValueFormat();
}


void CAttributeView::OnAttributeSolid() 
{
	m_pAttributeLayer->SetColorType(EAttrSolid);
}

void CAttributeView::OnAttributeGreyscale() 
{
	m_pAttributeLayer->SetColorType(EAttrGreyscale);
}

void CAttributeView::OnAttributeInvertedGrey() 
{
	m_pAttributeLayer->SetColorType(EAttrInvertedGreyscale);
}

void CAttributeView::OnAttributeUpdateDefault() 
{
	CTileLayer *pTileLayer = GetTileLayer();
	m_bUpdateDefault = !m_bUpdateDefault;
	m_pAttributeLayer->SetUpdateDefault(pTileLayer && m_bUpdateDefault);
}

void CAttributeView::OnAttributeUpdateTiles() 
{
	CTileLayer *pTileLayer = GetTileLayer();
	m_bUpdateTiles = !m_bUpdateTiles;
	m_pAttributeLayer->SetUpdateTiles(pTileLayer && m_bUpdateTiles);
}

CTileLayer * CAttributeView::GetTileLayer()
{
	CTileLayer *pLayer = NULL;
	int iIndex = m_layerCtrl.GetCurSel();
	if (iIndex >= 0)
	{
		POSITION pos = (POSITION)m_layerCtrl.GetItemData(iIndex);
		pLayer = DYNAMIC_DOWNCAST(CTileLayer, m_pAttributeLayer->GetMap()->GetNextLayer(pos));
	}
	m_pAttributeLayer->SetTileLayer(pLayer);
	return pLayer;
}


void CAttributeView::UpdateTileLayers()
{
	m_layerCtrl.ResetContent();
	CMapEditorDoc *pDoc = m_pAttributeLayer->GetMap();
	ASSERT(pDoc != NULL);

	CRuntimeClass *pClass = RUNTIME_CLASS( CTileLayer );
    ASSERT(pClass != NULL);

	POSITION pos = pDoc->GetFirstLayer();
	while (pos != NULL)
	{
		POSITION lpos = pos;
		CMapLayer *pLayer = pDoc->GetNextLayer(pos);
		if (pLayer->IsKindOf(pClass))
		{
			int iIndex = m_layerCtrl.AddString(pLayer->GetTitle());
			ASSERT(iIndex >= 0);
			m_layerCtrl.SetItemData(iIndex, (unsigned long)lpos);
		}
	}
	if (m_layerCtrl.GetCount() > 0)
		m_layerCtrl.SetCurSel(0);
	else
	{
		m_layerCtrl.EnableWindow(FALSE);
		CWnd *pWnd = GetDlgItem(IDC_ATTRIBUTE_UPDATE_DEFAULT);
		if (pWnd) pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_ATTRIBUTE_UPDATE_TILES);
		if (pWnd) pWnd->EnableWindow(FALSE);
	}
}

void CAttributeView::OnAttributeShowObjects() 
{
	m_bShowObjectAttributes = !m_bShowObjectAttributes;
	m_pAttributeLayer->SetShowObjectAttributes(m_bShowObjectAttributes);
}
