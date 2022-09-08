// CycleButton.h : header file
//
#include <stdarg.h>
/////////////////////////////////////////////////////////////////////////////
// CCycleButton window

class CCycleButton : public CButton
{
// Construction
public:
	CCycleButton();

// Attributes
public:
	virtual UINT GetCycleState() { return m_nCycleState; }
	virtual UINT GetCycleCount() { return m_hBitmapList.GetCount(); }

// Operations
public:
	virtual void SetCycleState(UINT nCycleState);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCycleButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCycleButton();
	virtual void LoadBitmaps(UINT nCycleStates, ...);


	// Generated message map functions
protected:
	CList<HBITMAP, HBITMAP> m_hBitmapList;
    UINT m_nCycleState;

	//{{AFX_MSG(CCycleButton)
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#define CCYCLE_INVALID ~0
/////////////////////////////////////////////////////////////////////////////
