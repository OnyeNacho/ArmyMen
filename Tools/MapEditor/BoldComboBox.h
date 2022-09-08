// BoldComboBox.h : header file
//
#ifndef _BOLDCOMBOBOX_H_
#define _BOLDCOMBOBOX_H_

/////////////////////////////////////////////////////////////////////////////
// CBoldComboBox window

class CBoldComboBox : public CComboBox
{
// Construction
public:
	CBoldComboBox();

// Attributes
public:

// Operations
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoldComboBox)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBoldComboBox();
	int AddItem(LPCTSTR lpszString, BOOL bBold)
	{
		int nIndex = AddString(lpszString);
		SetItemData(nIndex, (DWORD)bBold);
		return nIndex;
	}

	// Generated message map functions
protected:	
    HFONT m_hBoldFont;

	//{{AFX_MSG(CBoldComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif