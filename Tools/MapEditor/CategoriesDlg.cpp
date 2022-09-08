// CategoriesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapeditor.h"
#include "CategoriesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCategoriesDlg dialog


CCategoriesDlg::CCategoriesDlg(CCategoryList * pCategories, UINT nTitleID, CWnd* pParent /*=NULL*/)
	: CDialog(CCategoriesDlg::IDD, pParent)
{
	m_pCategories = pCategories;
	m_nTitleID = nTitleID;

	//{{AFX_DATA_INIT(CCategoriesDlg)
	m_title = _T("");
	//}}AFX_DATA_INIT
}


void CCategoriesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCategoriesDlg)
	DDX_Control(pDX, IDC_CATEGORY_TITLE, m_titleCtrl);
	DDX_Control(pDX, IDC_UP_ITEM, m_upButton);
	DDX_Control(pDX, IDC_NEW_ITEM, m_newButton);
	DDX_Control(pDX, IDC_DOWN_ITEM, m_downButton);
	DDX_Control(pDX, IDC_DELETE_ITEM, m_deleteButton);
	DDX_Control(pDX, IDC_CATEGORY_LIST, m_listCtrl);
	DDX_Text(pDX, IDC_CATEGORY_TITLE, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCategoriesDlg, CDialog)
	//{{AFX_MSG_MAP(CCategoriesDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_NEW_ITEM, OnNewItem)
	ON_LBN_SELCHANGE(IDC_CATEGORY_LIST, OnSelchangeCategoryList)
	ON_EN_CHANGE(IDC_CATEGORY_TITLE, OnChangeCategoryTitle)
	ON_BN_CLICKED(IDC_DELETE_ITEM, OnDeleteItem)
	ON_BN_CLICKED(IDC_UP_ITEM, OnUpItem)
	ON_BN_CLICKED(IDC_DOWN_ITEM, OnDownItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCategoriesDlg message handlers

BOOL CCategoriesDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
		return CDialog::PreTranslateMessage(pMsg);
	}
}

BOOL CCategoriesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	HINSTANCE hInstance = AfxGetInstanceHandle();
	m_deleteButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DELETE)));
	m_newButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_NEW)));
	m_upButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_UP)));
	m_downButton.SetBitmap(LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DOWN)));

	// Create the ToolTip control.
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);

	m_tooltip.AddTool(GetDlgItem(IDC_UP_ITEM), IDC_UP_ITEM);
	m_tooltip.AddTool(GetDlgItem(IDC_DOWN_ITEM), IDC_DOWN_ITEM);
	m_tooltip.AddTool(GetDlgItem(IDC_DELETE_ITEM), IDC_DELETE_ITEM);
	m_tooltip.AddTool(GetDlgItem(IDC_NEW_ITEM), IDC_NEW_ITEM);

	CString title;
	if (title.LoadString(m_nTitleID))
		SetWindowText(title);

	POSITION pos = m_pCategories->GetHeadPosition();
	while (pos != NULL)
	{
		CCategory *pCategory = m_pCategories->GetNext(pos);
	    ASSERT(pCategory != NULL);
		int iIndex = m_listCtrl.AddString(pCategory->GetTitle());
		m_listCtrl.SetItemData(iIndex,(unsigned long)pCategory);
	}
	
	return TRUE;

}

void CCategoriesDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	DelBitmap(m_deleteButton);
	DelBitmap(m_newButton);
	DelBitmap(m_newButton);
	DelBitmap(m_upButton);
	CDialog::OnDestroy();	
}
	
void CCategoriesDlg::DelBitmap(CButton& button)
{
	ASSERT(button.m_hWnd);
	HBITMAP hBitmap = button.SetBitmap(NULL);
	if (hBitmap) DeleteObject(hBitmap);
}

void CCategoriesDlg::OnNewItem() 
{
	CString title;
	int iIndex = m_pCategories->GetCount();
    BOOL bFound = TRUE;

	while (bFound)
	{
		title.Format(IDS_CATEGORY_FORMAT,++iIndex);
		bFound = FindItem(title);
	}

	CCategory *pCategory = new CCategory(title);
	ASSERT_NEW(pCategory);

	// add the new category to the actual list
	m_pCategories->AddTail(pCategory);

	// add the new category to the listctrl 
	// and make it the current item.
	iIndex = m_listCtrl.AddString(title);
	UpdateCategory(iIndex,pCategory);

	// update the titlectrl and make it active
	// so the user can change the new category's 
	// title if necessary.
    UpdateTitle();
	m_titleCtrl.SetFocus();
}

BOOL CCategoriesDlg::FindItem(LPCTSTR title)
{
	POSITION pos = m_pCategories->GetHeadPosition();
	while (pos != NULL)
	{
		CCategory *pCategory = m_pCategories->GetNext(pos);
		ASSERT(pCategory != NULL);
        if (pCategory->GetTitle().CompareNoCase(title)==0)
			return TRUE;
	}
	return FALSE;
}

void CCategoriesDlg::OnSelchangeCategoryList() 
{
	int iIndex = m_listCtrl.GetCurSel();
	if (iIndex != LB_ERR)
	{
		CCategory *pCategory = (CCategory *)m_listCtrl.GetItemData(iIndex);
		m_titleCtrl.SetSel(0,-1);
		m_titleCtrl.ReplaceSel(pCategory->GetTitle());
	}
}

void CCategoriesDlg::OnChangeCategoryTitle() 
{
	int iIndex = m_listCtrl.GetCurSel();
	if (iIndex != LB_ERR)
	{
		UpdateData();
		CCategory *pCategory = (CCategory *)m_listCtrl.GetItemData(iIndex);
		pCategory->SetTitle(m_title);
		m_listCtrl.DeleteString(iIndex); // yuk
		m_listCtrl.InsertString(iIndex,m_title);
		UpdateCategory(iIndex,pCategory);
	}
}

void CCategoriesDlg::UpdateCategory(int iIndex, CCategory *pCategory)
{
	m_listCtrl.SetItemData(iIndex, (unsigned long)pCategory);
	m_listCtrl.SetCurSel(iIndex);
	m_listCtrl.UpdateWindow();	
}

void CCategoriesDlg::OnDeleteItem() 
{
	int iIndex = m_listCtrl.GetCurSel();
	if (iIndex != LB_ERR && AfxMessageBox(IDS_ASK_DELETE_CATEGORY,MB_ICONQUESTION|MB_YESNO) == IDYES)
	{
		POSITION pos = m_pCategories->FindIndex(iIndex);
		CCategory *pCategory = m_pCategories->GetAt(pos);

		m_pCategories->RemoveAt(pos);
        delete pCategory;

		if (iIndex < (m_listCtrl.GetCount() - 1))
			m_listCtrl.SetCurSel(iIndex + 1);
		else
			m_listCtrl.SetCurSel(iIndex - 1);

		m_listCtrl.DeleteString(iIndex);
		m_listCtrl.UpdateWindow();
		UpdateTitle();
	}	
}

void CCategoriesDlg::UpdateTitle()
{
	int iIndex = m_listCtrl.GetCurSel();
	m_titleCtrl.SetSel(0,-1);
	
	if (iIndex != LB_ERR)
	{ 
		CCategory *pCategory = (CCategory *)m_listCtrl.GetItemData(iIndex);
		ASSERT(pCategory != NULL);
		m_titleCtrl.ReplaceSel(pCategory->GetTitle());
	}
	else
		m_titleCtrl.ReplaceSel("");
}

void CCategoriesDlg::OnUpItem() 
{
	int iIndex = m_listCtrl.GetCurSel();
   if (iIndex != LB_ERR)
   {
      if (iIndex > 0)
	  {
		  POSITION pos = m_pCategories->FindIndex(iIndex);
		  CCategory *pCategory =  m_pCategories->GetAt(pos);
		  POSITION target = pos;
		  m_pCategories->GetPrev(target);
		  m_pCategories->RemoveAt(pos);
		  m_pCategories->InsertBefore(target,pCategory);

		  m_listCtrl.DeleteString(iIndex);
		  iIndex = m_listCtrl.InsertString(iIndex-1,pCategory->GetTitle());
		  UpdateCategory(iIndex, pCategory);
	  }
   }	
	
}

void CCategoriesDlg::OnDownItem() 
{
   int iIndex = m_listCtrl.GetCurSel();
   if (iIndex != LB_ERR)
   {
	  int iCount = m_listCtrl.GetCount();
	  if (iIndex < (iCount -1))
	  {
		  POSITION pos = m_pCategories->FindIndex(iIndex);
		  CCategory *pCategory = m_pCategories->GetAt(pos);
		  m_pCategories->RemoveAt(pos);

		  pos = m_pCategories->FindIndex(iIndex);
		  m_pCategories->InsertAfter(pos,pCategory);

		  m_listCtrl.DeleteString(iIndex);
		  iIndex = m_listCtrl.InsertString(iIndex+1,pCategory->GetTitle());
		  UpdateCategory(iIndex,pCategory);
	  }
   }
}
