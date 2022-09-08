// AnimPropPage.h : header file
//

#ifndef __ANIMPROPPAGE_H__
#define __ANIMPROPPAGE_H__

/////////////////////////////////////////////////////////////////////////////
// CAnimPropPage dialog

class CAnimMapObject;
class CObjectSet;

class CAnimPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CAnimPropPage)

// Construction
public:
	int m_iFrame;
	int m_iSequence;
	CAnimPropPage(CObjectSet *pObjectSet=NULL, CAnimMapObject *pObject=NULL, int iSequence=0, int iFrame=0);
	~CAnimPropPage();

// Dialog Data
	//{{AFX_DATA(CAnimPropPage)
	enum { IDD = IDD_PROP_ANIM };
	CListCtrl	m_listCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAnimPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_sequenceHeader;
	CString m_framesHeader;
	CAnimMapObject * m_pObject;
	CObjectSet * m_pObjectSet;
	// Generated message map functions
	//{{AFX_MSG(CAnimPropPage)
	afx_msg void OnItemchangedSequenceList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __ANIMPROPPAGE_H__
