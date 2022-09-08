// ObjectListBox.h : header file
//
#ifndef _OBJECTLISTBOX_H_
#define _OBJECTLISTBOX_H_

class CObjectSet;
class CObjectSetView;
/////////////////////////////////////////////////////////////////////////////
// CObjectListBox window

class CObjectListBox : public CListBox
{

protected:
    CObjectSet *m_pObjectSet; // image data for this objectList
	CSize m_maxSize;          // max size for all the objects
    int m_iItemWidth;
	int m_iItemHeight;
    int m_iFontHeight;
    int m_iLastItem;
    HPALETTE m_hPalette;
	BOOL m_bMogMode;

// Attributes
public:
	int FindItem(int iItem);

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	CObjectSetView *m_pView;
	BOOL IsMogMode();
	void SetMog(BOOL bMog);
	CObjectListBox();
	void ClearSelection() { SetSel(-1,FALSE); }
	void ResetSelection(int iIndex);
	void InitContent();
	void ResetContent();

	// Operations
	virtual int AddItem(int iItem);
    virtual void UseObjectSet(CObjectSet *pObjectSet, HPALETTE hPalette, BOOL bShowFullName); // does a ResetContent
	virtual int GetItem(int iItem) { return (int)GetItemData(iItem); }
    int GetLastItem() { return m_iLastItem; }
    
	// Implementation
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCIS);

	// Generated message map functions
protected:
	BOOL m_bShowFullName;
	//{{AFX_MSG(CObjectListBox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
