// CCelView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCelView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "DIBitmap.h"


#define CIRCLE_UNITS 32

class CSequence;
class CAnimEditorDoc;
class CSequenceCel;

class CCelView : public CFormView
{
protected:
	CCelView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCelView)

// Form Data
public:
	//{{AFX_DATA(CCelView)
	enum { IDD = IDD_CELVIEW };
	CButton	btnPrevious;
	CComboBox	comboDirection;
	CComboBox	comboAction;
	CButton	btnPlayStop;
	CListBox	listboxHSpots;
	CScrollBar	scrollCel;
	BOOL	bLooped;
	CString	csCelNumber;
	CString	csCelFileBMP;
	CString	csHSpotLoc;
	UINT	uiSpeed;
	CString	csBackgroundBMP;
	BOOL	m_bMoving;
	UINT	m_uiMoveSpeed;
	int		m_uiCycles;
	CString	csCelFolder;
	BOOL	bTransition;
	//}}AFX_DATA

// Attributes
private:
	int			iSeqCel;			//	Current sequence cel being shown. # is location in sequence's list. -1 = no seqcel.

	CSize		sizImageArea;					//	Size of the area that images can cover.
	int			iXOriginBig, iYOriginBig;		//	Corner of big bitmap.
	int			iXOriginSmall, iYOriginSmall;	//	Corner of small bitmap.
	int			iZoom;
	int			m_iWidthAvail;
	int			m_iHeightAvail;
	BOOL		bPlaying;
	UINT		iTimerID;
	HCURSOR		hcurHSpotPrimarySet;
	HCURSOR		hcurHSpotPrimarySetAll;
	HCURSOR		hcurHSpotSet;
	HCURSOR		hcurNormal;
	BOOL		bMouseDown;
	BOOL		bMoveAll;
	CPoint		ptMouseDown;
	CPoint		ptHSpotOriginal;
	CDIBitmap	dibHSpotPrimary;	//	Primary hotspot crosshairs.
	CDIBitmap	dibHSpot;			//	Normal hotspot crosshairs.

	HBITMAP		m_offscreen_hbm;
	BYTE		*m_poffscreen_bits;
	CRect		m_rcOffscreen;

	int			iXPosSeq, iYPosSeq;				// Position of moving sequence
	float		fdx, fdy;						// partial pixels
	int			m_cycle;
	int			m_move_cycles;

	double sin_table[CIRCLE_UNITS];
	double cos_table[CIRCLE_UNITS];

public:
	CSequence*	pSequence;
	CSequence*	pSequencePrev;		//	Selected sequence before this one.

// Operations
private:
	void		DrawImages( BOOL bErase );
	void		SetScrollBarRange();
	void		SetScrollFrom_iSeqCel();
	BOOL		bHotSpotsListBoxMatchesList();
	BOOL		StartTimer();
	BOOL		bPtOnBigCel( const CPoint& ptTest );
	void		SetHSpotLocText( CSequenceCel* pSeqCel );
	void		SetupMovementTables(void);
	void		ResetCycle(void);
	void		SetupOffscreen(CDC *pDC);

public:
	CAnimEditorDoc*		GetDocument()	{ return (CAnimEditorDoc*)m_pDocument; }

	void		LinkImage( CSequenceCel* pSeqCelLink );
	void		LinkToSequence( CSequence* pSeq );
	BOOL		bActiveAndLinkedToSequence( CSequence* pSeq );
	void		CalcSizeChanges( int cx = 0, int cy = 0 );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCelView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCelView)
	afx_msg void OnChangeEditSequence();
	afx_msg void OnDeltaposSpinSpeed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnUpdateSequenceHotspotnew(CCmdUI* pCmdUI);
	afx_msg void OnSequenceHotspotnew();
	afx_msg int OnVKeyToItem(UINT nKey, CListBox* pListBox, UINT nIndex);
	afx_msg void OnSelchangeListHspots();
	afx_msg void OnChangeEditSpeed();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeComboAction();
	afx_msg void OnSelchangeComboDirection();
	afx_msg void OnButtonBackground();
	afx_msg void OnButtonBackgroundclear();
	afx_msg void OnButtonPlaystop();
	afx_msg void OnCheckLooped();
	afx_msg void OnCheckMoving();
	afx_msg void OnChangeEditMove();
	afx_msg void OnDeltaposSpinMove(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditMoveCycles();
	afx_msg void OnDeltaposSpinMoveCycles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonPrevious();
	afx_msg void OnCheckTransition();
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnDeltaposSpinShifthorz(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinShiftvert(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
