// DupSearchDlg.h : header file
// CG: This file was added by the Progress Dialog component

/////////////////////////////////////////////////////////////////////////////
// CDupSearchDlg dialog
//
// Shows the user how far the duplicate search has progressed
// And gives the user the option of canceling the search.
//
#ifndef __DUPSEARCHDLG_H__
#define __DUPSEARCHDLG_H__

class CDupSearchDlg : public CDialog
{
// Construction / Destruction
protected:
	int m_iMinDiff;
	int m_iFound;
public:
    CDupSearchDlg(UINT nCaptionID = 0);   // standard constructor
    ~CDupSearchDlg();

    BOOL Create(CWnd *pParent=NULL);

    // Checking for Cancel button
    BOOL CheckCancelButton();

    // Progress Dialog manipulation
    void SetRange(int nLower,int nUpper);
    int  SetStep(int nStep);
    int  SetPos(int nPos);
    int  OffsetPos(int nPos);
    int  StepIt();
	void SetStatus(int iFound, int iMinDiff);
    void UpdateFound(int iFound) { SetStatus(iFound, m_iMinDiff); }
	void UpdateMinDiff(int iMinDiff) { SetStatus(m_iFound, iMinDiff); }

// Dialog Data
    //{{AFX_DATA(CDupSearchDlg)
	enum { IDD = CG_IDD_PROGRESS };
	CStatic	m_statusCtrl;
    CProgressCtrl	m_Progress;
	//}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDupSearchDlg)
    public:
    virtual BOOL DestroyWindow();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_nCaptionID;
    int m_nLower;
    int m_nUpper;
    int m_nStep;
    
    BOOL m_bCancel;
    BOOL m_bParentDisabled;

    void ReEnableParent();

    virtual void OnCancel();
    virtual void OnOK() {}; 
    void UpdatePercent(int nCurrent);
    void PumpMessages();

    // Generated message map functions
    //{{AFX_MSG(CDupSearchDlg)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // __DUPSEARCHDLG_H__
