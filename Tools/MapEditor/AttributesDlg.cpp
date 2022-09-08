// AttributesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapEditorDoc.h"
#include "AttributesDlg.h"
#include "AttributeLayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributesDlg dialog


CAttributesDlg::CAttributesDlg(UINT nTitleID, CAttributeTarget *pTarget, void *pTargetData)
	: CPropertyPage(CAttributesDlg::IDD, nTitleID)
{
	m_pTarget = pTarget;
	m_pTargetData = pTargetData;
	m_iSelected = -1;
    m_bUpdate = FALSE;
    m_pszTitle.LoadString(nTitleID);
	ASSERT(m_pTarget != NULL);
	m_pDoc = NULL;
	m_pDefile = NULL;
	//{{AFX_DATA_INIT(CAttributesDlg)
	//}}AFX_DATA_INIT
}


void CAttributesDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttributesDlg)
	DDX_Control(pDX, IDC_ATTRIBUTE_LABEL, m_attributeLabel);
	DDX_Control(pDX, IDC_ATTRIBUTE_VALUE_UPDOWN, m_valueCtrl);
	DDX_Control(pDX, IDC_ATTRIBUTE_MAX, m_maxCtrl);
	DDX_Control(pDX, IDC_ATTRIBUTE_LIST, m_listCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttributesDlg, CDialog)
	//{{AFX_MSG_MAP(CAttributesDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ATTRIBUTE_LIST, OnItemchangedAttributeList)
	ON_NOTIFY(UDN_DELTAPOS, IDC_ATTRIBUTE_VALUE_UPDOWN, OnDeltaposAttributeValueUpdown)
	ON_EN_CHANGE(IDC_ATTRIBUTE_VALUE, OnChangeAttributeValue)
	ON_EN_KILLFOCUS(IDC_ATTRIBUTE_VALUE, OnKillfocusAttributeValue)
	ON_NOTIFY(NM_CLICK, IDC_ATTRIBUTE_LIST, OnClickAttributeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributesDlg message handlers

BOOL CAttributesDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	SetWindowText(m_pszTitle);
	ASSERT((m_listCtrl.GetStyle() & LVS_TYPEMASK)==LVS_REPORT);
	int iCount = m_pTarget->GetAttributeCount();
	int iIndex = 0;

    // TBD: verify that we have is a single selection report list ctrl
	VERIFY(m_attributeHeader.LoadString(IDS_ATTRIBUTE));
	VERIFY(m_valueHeader.LoadString(IDS_VALUE));
	m_stateImageList.Create(IDB_STATE,16,1,RGB(255,0,0));
	m_listCtrl.SetImageList(&m_stateImageList,LVSIL_STATE);
	m_attributes.SetSize(iCount);

	CRect rect;
	m_listCtrl.GetWindowRect(&rect);
	int iWidth = (rect.Width() - 5)/2; // TBD
	m_listCtrl.InsertColumn(0,m_attributeHeader,LVCFMT_LEFT,iWidth);
	m_listCtrl.InsertColumn(1,m_valueHeader,LVCFMT_LEFT, iWidth, 1);
	
	if (NULL != m_pTargetData)
	{
		POSITION pos = m_pTarget->GetFirstAttribute();
		while (pos != NULL)
		{
			CAttributeInfo *pAttribute = &m_attributes[iIndex];
			m_pTarget->GetNextAttribute(pos, m_pTargetData, m_attributes[iIndex]);
			int nItem = m_listCtrl.InsertItem(iIndex,pAttribute->m_pszName);
			m_listCtrl.SetItemData(nItem,(unsigned long)pAttribute);
			UpdateState(nItem,pAttribute->m_bRemoved);
			UpdateAttributeValue(nItem,pAttribute->m_currentValue);
			iIndex++;
		}
	}
	else
	{
		POSITION pPos;
		CAttributeLayer *pLayer=NULL;
		CAttributeInfo *pAttrib=NULL;
		LV_FINDINFO lvFind;
		int iFind=-1;

		lvFind.flags = LVFI_STRING;

		// 1. Get the attribute layers from the Document.
		// 2. Add the attribute layers to the list control
		if (NULL == m_pDoc)
		{
			// NOT GOOD
		}

		LoadDefaults();

		pPos = m_pDoc->GetFirstAttribute();

		if (NULL != pPos)
		{
			while (NULL != pPos)
			{
				pLayer = m_pDoc->GetNextAttribute(pPos);
				if (NULL == pLayer)
					break;

				lvFind.psz = pLayer->GetTitle();
				if (-1 != (iFind = m_listCtrl.FindItem(&lvFind, -1)))
					continue;

				pAttrib = &m_attributes[iIndex];
				pAttrib->m_pszName = pLayer->GetTitle();
				pAttrib->SetMaxValue(pLayer->GetMaxValue());
				pAttrib->SetDefaultValue(pLayer->GetDefaultValue());
				pAttrib->SetBitCount(pLayer->GetBitCount());
				pAttrib->SetValue(pAttrib->GetDefaultValue());
				int nItem = m_listCtrl.InsertItem(iIndex, pAttrib->m_pszName);
				m_listCtrl.SetItemData(nItem, (unsigned long)pAttrib);
				UpdateState(nItem, pAttrib->m_bRemoved);
				UpdateAttributeValue(nItem, pAttrib->m_currentValue);
				iIndex++;
			}
		}
	}

	if (iCount) UpdateAttribute(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAttributesDlg::UpdateAttribute(int iAttribute)
{
	CAttributeInfo *pAttribute = GetAttribute(iAttribute);
	ASSERT(pAttribute != NULL);
	int iMaxValue = pAttribute->GetMaxValue();
	m_iSelected = iAttribute;
	m_bUpdate = TRUE;
	m_attributeLabel.SetWindowText(pAttribute->m_pszName);
	m_attributeLabel.UpdateWindow();
	m_valueCtrl.SetRange(0, iMaxValue);
	m_valueCtrl.SetBase(g_bDecimal ? 10 : 16);
	m_valueCtrl.SetPos(pAttribute->m_currentValue);
	m_valueCtrl.GetBuddy()->UpdateWindow(); // why do I have to do this?
	m_maxCtrl.SetWindowText(GetFullValueString(iMaxValue));
	m_maxCtrl.UpdateWindow();
	m_bUpdate = FALSE;
}

void CAttributesDlg::OnItemchangedAttributeList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem >= 0)
	{
		// TRACE("selected attribute is %d\n", pNMListView->iItem);
		UpdateAttribute(pNMListView->iItem);
	}	
	*pResult = 0;
}


void CAttributesDlg::OnDeltaposAttributeValueUpdown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int iValue = pNMUpDown->iPos + pNMUpDown->iDelta;
	if (m_iSelected >= 0)
	{
#ifdef _DEBUG
		// spin controls don't limit their values correctly when _DEBUG
		int iMin,iMax;
		m_valueCtrl.GetRange(iMin,iMax);
		iValue = max(iMin,min(iValue,iMax));
#endif
		SetAttributeValue(m_iSelected, iValue);
	}
	*pResult = 0;
}

void CAttributesDlg::OnChangeAttributeValue() 
{
	if ((m_iSelected >= 0) && !m_bUpdate)
		SetAttributeValue(m_iSelected,m_valueCtrl.GetPos());
}

void CAttributesDlg::SetAttributeValue(int iAttribute, int iValue)
{
	CAttributeInfo *pAttribute = GetAttribute(iAttribute);
	pAttribute->SetValue(iValue);
    UpdateState(iAttribute,pAttribute->m_bRemoved);
	UpdateAttributeValue(iAttribute,pAttribute->m_currentValue);
}

void CAttributesDlg::OnKillfocusAttributeValue() 
{
	if (m_iSelected >= 0)
		UpdateAttribute(m_iSelected);
}

void CAttributesDlg::OnClickAttributeList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UINT uFlags=0;
	CPoint point;

	if (GetCursorPos(&point))
	{
		m_listCtrl.ScreenToClient(&point);
		int nHitItem=m_listCtrl.HitTest(point,&uFlags);
		if (uFlags & LVHT_ONITEMSTATEICON && -1 != nHitItem)
		{
			CAttributeInfo *pAttribute = GetAttribute(nHitItem);
			if (pAttribute->m_bRemoved)
			   pAttribute->SetValue(pAttribute->m_currentValue);
			else
			   pAttribute->RemoveValue();
			UpdateState(nHitItem,pAttribute->m_bRemoved);
			UpdateAttributeValue(nHitItem,pAttribute->m_currentValue);
			if (m_iSelected != nHitItem && m_iSelected >= 0)
				m_listCtrl.SetItemState(m_iSelected,0,LVIS_SELECTED);
			UpdateAttribute(nHitItem); 
		}
	}
	*pResult = 0;
}

CAttributeInfo * CAttributesDlg::GetAttribute(int iItem)
{
	return (CAttributeInfo *)m_listCtrl.GetItemData(iItem);
}

void CAttributesDlg::UpdateState(int iAttribute, BOOL bRemoved)
{
	int iState = bRemoved ? 1 : 2; // state is 1-based image index
	m_listCtrl.SetItemState(iAttribute,INDEXTOSTATEIMAGEMASK(iState),LVIS_STATEIMAGEMASK);
}

void CAttributesDlg::UpdateAttributeValue(int iAttribute, int iValue)
{
	// TBD: why did adding LVIF_PARAM make the value string to disappear???
	m_listCtrl.SetItem(iAttribute, 1, LVIF_TEXT,  GetFullValueString(iValue),0,0,0,iAttribute);
}

BOOL CAttributesDlg::LoadDefaults()
{
	// Load the default attributes from the directory m_pObjs.
	// *Note m_pDoc->m_pszObjectSetPath;
	CString sObjDir;
	DefAtr *pAtr=NULL;
	CAttributeInfo *pAttrib=NULL;
	int iDefs=0;
	int iCur=0;
	int iIndex=0;
	int iItem=-1;
	
	sObjDir = *m_pDoc->GetObjectPath();
	sObjDir += '\\';
	sObjDir += *m_pObjs;
	sObjDir += "\\default.bin";
	m_pDefile = new CFile();

	if (FALSE == m_pDefile->Open(sObjDir, CFile::modeReadWrite|CFile::shareDenyWrite, NULL))
	{
		// File does not exist, create on save
		delete m_pDefile;
		m_pDefile = NULL;
		return FALSE;
	}
	else
	{
		// Load the defs
		if (sizeof(int) != m_pDefile->Read(&iDefs, sizeof(int)))
		{
			// Problem with file
			m_pDefile->Close();
			delete m_pDefile;
			m_pDefile = NULL;
			return FALSE;
		}
		while (iCur < iDefs)
		{
			pAtr = new DefAtr;
			if (sizeof(DefAtr) != m_pDefile->Read(pAtr, sizeof(DefAtr)))
			{
				delete pAtr;
				break;
			}

			pAttrib = &m_attributes[iIndex];
			pAttrib->m_pszName = (LPCTSTR)(void*)malloc(sizeof(pAtr->rcName));
			lstrcpy((LPTSTR)pAttrib->m_pszName, pAtr->rcName);
			pAttrib->SetMaxValue(pAtr->iMax);
			pAttrib->SetDefaultValue(pAtr->iDefValue);
			pAttrib->SetBitCount(pAtr->iBits);
			pAttrib->SetValue(pAtr->iValue);
			iItem = m_listCtrl.InsertItem(iIndex, pAttrib->m_pszName);
			m_listCtrl.SetItemData(iItem, (unsigned long)pAttrib);
			UpdateState(iItem, pAttrib->m_bRemoved);
			UpdateAttributeValue(iItem, pAttrib->m_currentValue);
			delete pAtr;
			iIndex++;
			iCur++;
		}
		if (0 != iDefs)
			UpdateAttribute(0);
	}
	return TRUE;
}

BOOL CAttributesDlg::SaveDefaults()
{
	CString sObjDir;
	DefAtr dAtr;
	int iDefs=0;
	int iCur=0;

	sObjDir = *m_pDoc->GetObjectPath();
	sObjDir += '\\';
	sObjDir += *m_pObjs;
	sObjDir += "\\default.bin";

	if (NULL != m_pDefile)
	{
		if (CFile::hFileNull != m_pDefile->m_hFile)
			m_pDefile->Close();

		if (FALSE == m_pDefile->Open(sObjDir, CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyWrite, NULL))
		{
			delete m_pDefile;
			m_pDefile = NULL;
			return FALSE;
		}
	}
	else
	{
		m_pDefile = new CFile();
		if (FALSE == m_pDefile->Open(sObjDir, CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyWrite, NULL))
		{
			delete m_pDefile;
			m_pDefile = NULL;
			return FALSE;
		}
	}

	iDefs = m_attributes.GetSize();
	m_pDefile->Write(&iDefs, sizeof(int));

	while (iCur < iDefs)
	{
		if (NULL == lstrcpy(dAtr.rcName, m_attributes[iCur].m_pszName))
		{
			iCur++;
			continue;
		}
		dAtr.iValue = m_attributes[iCur].m_currentValue;
		dAtr.iDefValue = m_attributes[iCur].GetDefaultValue();
		dAtr.iBits = m_attributes[iCur].GetBitCount();
		dAtr.iMax = m_attributes[iCur].GetMaxValue();
		m_pDefile->Write(&dAtr, sizeof(DefAtr));
		iCur++;
	}
	m_pDefile->Close();
	delete m_pDefile;
	m_pDefile = NULL;
	return TRUE;
}
