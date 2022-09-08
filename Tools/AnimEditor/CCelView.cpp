// CCelView.cpp : implementation file
//

#include "stdafx.h"

#include <math.h>

#include "animeditor.h"
#include "CCelView.h"

#include "CSequence.h"
#include "CSequenceView.h"
#include "AnimEditorDoc.h"
#include "MainFrm.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct BITMAPINFO_256
{
  BITMAPINFOHEADER  bmiHeader;
  RGBQUAD           bmiColors[256];
};


#define OFFSCREEN_WIDTH		320
#define OFFSCREEN_HEIGHT	240

/////////////////////////////////////////////////////////////////////////////
// CCelView

IMPLEMENT_DYNCREATE(CCelView, CFormView)

//-----------------------------------------------------------------------------------------------------------------
CCelView::CCelView()
	: CFormView(CCelView::IDD)
{
	//{{AFX_DATA_INIT(CCelView)
	bLooped = TRUE;
	csCelNumber = _T("");
	csCelFileBMP = _T("");
	csHSpotLoc = _T("");
	uiSpeed = 0;
	csBackgroundBMP = _T("");
	m_bMoving = FALSE;
	m_uiMoveSpeed = 0;
	m_uiCycles = 1;
	csCelFolder = _T("");
	bTransition = FALSE;
	//}}AFX_DATA_INIT

	pSequence		= NULL;
	pSequencePrev	= NULL;
	iSeqCel			= -1;

	m_move_cycles = 1;

	sizImageArea	= CSize( 0, 0 );	//	xxx
	iXOriginBig		= 260;
	iYOriginBig		= 43;
	iXOriginSmall	= 15;
	iYOriginSmall	= 315;
	iZoom			= 1;
	bPlaying		= FALSE;
	iTimerID		= 42;			//	(Only one ever exists.)
	bMouseDown		= FALSE;
	bMoveAll		= FALSE;
	
	hcurHSpotPrimarySet		= AfxGetApp()->LoadCursor( IDC_HSPOTPRIMARYSET );
	hcurHSpotPrimarySetAll	= AfxGetApp()->LoadCursor( IDC_HSPOTPRIMARYSETALL );
	hcurHSpotSet			= AfxGetApp()->LoadCursor( IDC_HSPOTSET );
	hcurNormal				= ::LoadCursor( NULL, IDC_ARROW );


	//	Get a DC to use when creating dibs.
	CDC* pDC = new CDC;
	pDC->CreateCompatibleDC( NULL );

	VERIFY( dibHSpotPrimary.Create( pDC, (UINT)IDB_BITMAP_HSPOTPRIMARY, (HMODULE)NULL ) );
	VERIFY( dibHSpot.Create( pDC, (UINT)IDB_BITMAP_HSPOT, (HMODULE)NULL ) );

	delete pDC;

	m_offscreen_hbm = NULL;

	SetupMovementTables();
}

//-----------------------------------------------------------------------------------------------------------------
CCelView::~CCelView()
{
	if (m_offscreen_hbm)	{
		DeleteObject(m_offscreen_hbm);
		m_offscreen_hbm = NULL;
	}
}


//-----------------------------------------------------------------------------------------------------------------
void CCelView::SetupOffscreen(CDC *pDC)	{
	BITMAPINFO_256	bminfo;

	if (m_offscreen_hbm)
		return;

	CAnimEditorDoc* pDoc = GetDocument();

	RGBQUAD* colors = pDoc->docPalette.GetPaletteColors();
	memcpy( bminfo.bmiColors, colors, 256 * 4 );

	bminfo.bmiHeader.biSize				= sizeof( BITMAPINFOHEADER );
	bminfo.bmiHeader.biWidth			= OFFSCREEN_WIDTH;
	bminfo.bmiHeader.biHeight			= OFFSCREEN_HEIGHT;
	bminfo.bmiHeader.biPlanes			= 1;			//	Always 1.
	bminfo.bmiHeader.biBitCount			= 8;			//	This function is for 8 bpp images only.
	bminfo.bmiHeader.biCompression		= BI_RGB;		//	Not compressed.
	bminfo.bmiHeader.biSizeImage		= 0;
	bminfo.bmiHeader.biXPelsPerMeter	= 0;
	bminfo.bmiHeader.biYPelsPerMeter	= 0;
	bminfo.bmiHeader.biClrUsed			= 256;			//	Assumes palette uses all 256 colors.
	bminfo.bmiHeader.biClrImportant		= 256;			//	"They're all important."
	
	m_offscreen_hbm = ::CreateDIBSection(pDC->GetSafeHdc(), (BITMAPINFO *) &bminfo, DIB_RGB_COLORS, (PVOID*)&m_poffscreen_bits, 0, 0);
	m_rcOffscreen.SetRect(0, 0, OFFSCREEN_WIDTH, OFFSCREEN_HEIGHT );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	if( !pSequence )
	{
		SendMessageToDescendants( WM_ENABLE, (WPARAM)FALSE );
		EnableWindow( FALSE );
		return;
	}

	SendMessageToDescendants( WM_ENABLE, (WPARAM)TRUE );
	EnableWindow( TRUE );

	if( !pDX->m_bSaveAndValidate )		//	We are updating the controls, not the sequence.
	{
		if( !comboAction.m_hWnd )
		{
			//	Set up actions list.

			//	xxx Not sure how else I can get this thing to bind to a real control...
			DDX_Control( pDX, IDC_COMBO_ACTION, comboAction );

			POSITION		posInList = theApp.lstActions.GetHeadPosition();
			CActionRecord*	parAction;
			int				iIndex;
			while( posInList )
			{
				parAction = theApp.lstActions.GetNext( posInList );
				iIndex = comboAction.AddString( parAction->csAction );
				ASSERT( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
				//	Key value is stored as the "ItemData" for the combobox element.
				VERIFY( comboAction.SetItemData( iIndex, parAction->lKey ) != CB_ERR );
			}
		}
		//	Select the appropriate combobox item for the sequence.
		ASSERT( comboAction.GetCount() > 0 );
		BOOL bFound = FALSE;
		for( int iIndex = 0; iIndex < comboAction.GetCount(); iIndex++ )
		{
			if( comboAction.GetItemData( iIndex ) == pSequence->lAction )
			{
				comboAction.SetCurSel( iIndex );		//	Select item.
				bFound = TRUE;
				break;
			}
		}
		if( !bFound )
			comboAction.SetCurSel( -1 );

		if( !comboDirection.m_hWnd )
		{
			//	Set up directions list.

			//	xxx Not sure how else I can get this thing to bind to a real control...
			DDX_Control( pDX, IDC_COMBO_DIRECTION, comboDirection );

			POSITION		posInList = theApp.lstDirections.GetHeadPosition();
			CDirectionRecord*	parDirection;
//			int				iDir;
//			CString			csDir;
			int				iIndex;
			while( posInList )
			{
				parDirection = theApp.lstDirections.GetNext( posInList );
//				iDir = theApp.lstDirections.GetNext( posInList );
//				csDir.Format( "%i", iDir );
//				iIndex = comboDirection.AddString( csDir );
				iIndex = comboDirection.AddString( parDirection->csDirection );
				ASSERT( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
				//	Direction value is also stored as the "ItemData" for the combobox element.
//				VERIFY( comboDirection.SetItemData( iIndex, iDir ) != CB_ERR );
				VERIFY( comboDirection.SetItemData( iIndex, parDirection->lKey ) != CB_ERR );
			}
		}
		//	Select the appropriate combobox item for the sequence.
		ASSERT( comboDirection.GetCount() > 0 );
		bFound = FALSE;
		for( iIndex = 0; iIndex < comboDirection.GetCount(); iIndex++ )
		{
			if( comboDirection.GetItemData( iIndex ) == pSequence->iDirection )
			{
				comboDirection.SetCurSel( iIndex );		//	Select item.
				bFound = TRUE;
				break;
			}
		}
		if( !bFound )
			comboDirection.SetCurSel( -1 );

		CSequenceCel* pSeqCel;
		if( iSeqCel == -1 )
		{
			csCelNumber = "No Cel selected.";
			csCelFileBMP = "";
		}
		else
		{
			csCelNumber.Format( "Cel #%i", iSeqCel+1 );
			POSITION posSeqCel = pSequence->lstSeqCels.FindIndex( iSeqCel );
			ASSERT( posSeqCel );
			pSeqCel = pSequence->lstSeqCels.GetAt( posSeqCel );
			csCelFileBMP = pSeqCel->pCel->csFileBMP;
		}
		CAnimEditorDoc* pDoc = GetDocument();
		csCelFolder = pDoc->csFolder;


		if( !listboxHSpots.m_hWnd ) 	//	On first run, listbox isn't yet tied to an hWnd. This sets it up. xxx
			DDX_Control(pDX, IDC_LIST_HSPOTS, listboxHSpots);

		if( !bHotSpotsListBoxMatchesList() )
		{
			//	Rebuild listbox only if there has been a change, so we don't lose highlight otherwise.
			while( listboxHSpots.GetCount() > 0 )
			{
				listboxHSpots.DeleteString( 0 );
			}
			POSITION posInList = pSequence->lstHSpots.GetHeadPosition();
			CHSpot* pHSpot;
			while( posInList )
			{
				pHSpot = pSequence->lstHSpots.GetNext( posInList );
				listboxHSpots.AddString( pHSpot->csName );
			}
		}
		else
		{
			//	Sync static showing hot spot location.
			SetHSpotLocText( pSeqCel );	//	Sets csHSpotLoc.
		}
		if( !btnPlayStop.m_hWnd ) 	//	On first run, button isn't yet tied to an hWnd. This sets it up. xxx
			DDX_Control(pDX, IDC_BUTTON_PLAYSTOP, btnPlayStop);

		if( bPlaying )
			btnPlayStop.SetWindowText( CString( "Stop" ) );
		else
			btnPlayStop.SetWindowText( CString( "Play" ) );

		uiSpeed = pSequence->iSpeed;
		m_uiMoveSpeed = pSequence->iMoveSpeed;
		m_uiCycles = m_move_cycles;

		csBackgroundBMP = pSequence->csBackgroundBMP;
	}

	//{{AFX_DATA_MAP(CCelView)
	DDX_Control(pDX, IDC_BUTTON_PREVIOUS, btnPrevious);
	DDX_Control(pDX, IDC_COMBO_DIRECTION, comboDirection);
	DDX_Control(pDX, IDC_COMBO_ACTION, comboAction);
	DDX_Control(pDX, IDC_BUTTON_PLAYSTOP, btnPlayStop);
	DDX_Control(pDX, IDC_LIST_HSPOTS, listboxHSpots);
	DDX_Control(pDX, IDC_SCROLL_CEL, scrollCel);
	DDX_Check(pDX, IDC_CHECK_LOOPED, bLooped);
	DDX_Text(pDX, IDC_STATIC_CELNUMBER, csCelNumber);
	DDX_Text(pDX, IDC_STATIC_CELFILEBMP, csCelFileBMP);
	DDX_Text(pDX, IDC_STATIC_HSPOTLOC, csHSpotLoc);
	DDX_Text(pDX, IDC_EDIT_SPEED, uiSpeed);
	DDV_MinMaxUInt(pDX, uiSpeed, 1, 99);
	DDX_Text(pDX, IDC_STATIC_BACKGROUND, csBackgroundBMP);
	DDX_Check(pDX, IDC_CHECK_MOVING, m_bMoving);
	DDX_Text(pDX, IDC_EDIT_MOVE, m_uiMoveSpeed);
	DDV_MinMaxUInt(pDX, m_uiMoveSpeed, 0, 999);
	DDX_Text(pDX, IDC_EDIT_MOVE_CYCLES, m_uiCycles);
	DDV_MinMaxInt(pDX, m_uiCycles, 1, 10);
	DDX_Text(pDX, IDC_STATIC_CELFILEFOLDER, csCelFolder);
	DDX_Check(pDX, IDC_CHECK_TRANSITION, bTransition);
	//}}AFX_DATA_MAP

	//	Manual mappings, direct to sequence data...
	DDX_Text( pDX, IDC_EDIT_SEQUENCE, pSequence->csName );
	DDV_MaxChars( pDX, pSequence->csName, 50 );

	if( !pDX->m_bSaveAndValidate )		//	We are updating the controls, not the sequence.
	{
		//	Force image redraw. xxx
//		DrawImages( TRUE );
		InvalidateRect( NULL, FALSE );
	}
	else								//	We are updating the sequence.
	{
		//	Indirect mappings of controls to sequence data...
		if( pSequence->iSpeed != uiSpeed )
		{
			//	[ This can only happen if user makes a change to the Speed *edit box*. (See below.) ]
			pSequence->iSpeed = uiSpeed;
			if( bPlaying )
				StartTimer();
		}
		if( pSequence->iMoveSpeed != m_uiMoveSpeed )
		{
			//	[ This can only happen if user makes a change to the Move *edit box*. (See below.) ]
			pSequence->iMoveSpeed = m_uiMoveSpeed;
			if( bPlaying )
				StartTimer();
		}

		// this is absurd to need to keep 2 copies of this value, but
		// maybe I am missing something
		if( m_move_cycles != m_uiCycles )
		{
			//	[ This can only happen if user makes a change to the Move *edit box*. (See below.) ]
			m_move_cycles = m_uiCycles;
			if( bPlaying )
				StartTimer();
		}

		//	Sync lAction with combobox.
		int iComboSelect = comboAction.GetCurSel();
		//ASSERT( iComboSelect != CB_ERR );	//	Something must always be selected.
		if( comboAction.GetItemData( iComboSelect ) != pSequence->lAction )
		{
			pSequence->lAction = comboAction.GetItemData( iComboSelect );
			//	[ ItemData value equals the action key value. ]
		}
		//	Sync iDirection with combobox.
		iComboSelect = comboDirection.GetCurSel();
		ASSERT( iComboSelect != CB_ERR );	//	Something must always be selected.
		if( comboDirection.GetItemData( iComboSelect ) != pSequence->iDirection )
		{
			pSequence->iDirection = comboDirection.GetItemData( iComboSelect );
			//	[ ItemData value equals the direction. ]
		}

		//	[ Note: SetModifiedFlag calls for the doc are now done below, in the handlers for each of these controls. ]
	}
}


BEGIN_MESSAGE_MAP(CCelView, CFormView)
	//{{AFX_MSG_MAP(CCelView)
	ON_EN_CHANGE(IDC_EDIT_SEQUENCE, OnChangeEditSequence)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SPEED, OnDeltaposSpinSpeed)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_UPDATE_COMMAND_UI(ID_SEQUENCE_HOTSPOTNEW, OnUpdateSequenceHotspotnew)
	ON_COMMAND(ID_SEQUENCE_HOTSPOTNEW, OnSequenceHotspotnew)
	ON_WM_VKEYTOITEM()
	ON_LBN_SELCHANGE(IDC_LIST_HSPOTS, OnSelchangeListHspots)
	ON_EN_CHANGE(IDC_EDIT_SPEED, OnChangeEditSpeed)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO_ACTION, OnSelchangeComboAction)
	ON_CBN_SELCHANGE(IDC_COMBO_DIRECTION, OnSelchangeComboDirection)
	ON_BN_CLICKED(IDC_BUTTON_BACKGROUND, OnButtonBackground)
	ON_BN_CLICKED(IDC_BUTTON_BACKGROUNDCLEAR, OnButtonBackgroundclear)
	ON_BN_CLICKED(IDC_BUTTON_PLAYSTOP, OnButtonPlaystop)
	ON_BN_CLICKED(IDC_CHECK_LOOPED, OnCheckLooped)
	ON_BN_CLICKED(IDC_CHECK_MOVING, OnCheckMoving)
	ON_EN_CHANGE(IDC_EDIT_MOVE, OnChangeEditMove)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MOVE, OnDeltaposSpinMove)
	ON_EN_CHANGE(IDC_EDIT_MOVE_CYCLES, OnChangeEditMoveCycles)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MOVE_CYCLES, OnDeltaposSpinMoveCycles)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnButtonPrevious)
	ON_BN_CLICKED(IDC_CHECK_TRANSITION, OnCheckTransition)
	ON_COMMAND(ID_ZOOMIN, OnZoomin)
	ON_COMMAND(ID_ZOOMOUT, OnZoomout)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SHIFTHORZ, OnDeltaposSpinShifthorz)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SHIFTVERT, OnDeltaposSpinShiftvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCelView diagnostics

#ifdef _DEBUG
void CCelView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCelView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCelView message handlers


//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	SetScrollSizes( MM_TEXT, CSize( 0, 0 ) );

}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	//	Tell my sequence to redraw itself if focus is leaving me.
	if( pSequence && !bActivate )
		pSequence->pSeqView->InvalidateRect( NULL );

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnDraw(CDC* pDC) 
{
//	DrawImages( FALSE );	
	DrawImages( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	CalcSizeChanges( cx, cy );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnUpdateSequenceHotspotnew(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( pSequence != NULL );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnChangeEditSequence() 
{
	//	Edit box for sequence name has changed.

	CAnimEditorDoc* pDoc = GetDocument();
	pDoc->SetModifiedFlag();

	//	Resync sequence data to current control data.
	UpdateData( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnSelchangeComboAction() 
{
	//	Action ComboBox control selection has changed.

	CAnimEditorDoc* pDoc = GetDocument();
	pDoc->SetModifiedFlag();

	//	Resync sequence data to current control data.
	UpdateData( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnSelchangeComboDirection() 
{
	//	Diretion ComboBox control selection has changed.

	CAnimEditorDoc* pDoc = GetDocument();
	pDoc->SetModifiedFlag();

	//	Resync sequence data to current control data.
	UpdateData( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnChangeEditSpeed() 
{
	//	Speed edit control has changed.

	CAnimEditorDoc* pDoc = GetDocument();
	pDoc->SetModifiedFlag();

	//	Resync sequence data to current control data.
	UpdateData( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnChangeEditMove() 
{
	//	Move edit control has changed.

	CAnimEditorDoc* pDoc = GetDocument();
	pDoc->SetModifiedFlag();

	//	Resync sequence data to current control data.
	UpdateData( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnChangeEditMoveCycles() 
{
	UpdateData( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnDeltaposSpinSpeed(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//	Spin control change handler.

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	pSequence->iSpeed -= pNMUpDown->iDelta;

	pSequence->iSpeed = max( SEQUENCE_SPEEDMIN, min( SEQUENCE_SPEEDMAX, pSequence->iSpeed ) );

	CAnimEditorDoc* pDoc = GetDocument();
	pDoc->SetModifiedFlag();

	//	Update controls data based on sequence data.
	UpdateData( FALSE );

	if( bPlaying )
		StartTimer();

	*pResult = 0;
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnDeltaposSpinMove(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	pSequence->iMoveSpeed -= pNMUpDown->iDelta;

	pSequence->iMoveSpeed = max( 0, min( 999, pSequence->iMoveSpeed ) );

	CAnimEditorDoc* pDoc = GetDocument();
	pDoc->SetModifiedFlag();

	//	Update controls data based on sequence data.
	UpdateData( FALSE );

	if( bPlaying )
		StartTimer();

	*pResult = 0;
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnDeltaposSpinMoveCycles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_move_cycles -= pNMUpDown->iDelta;

	m_move_cycles = max( 1, min( 10, m_move_cycles ) );

	UpdateData( FALSE );

	if( bPlaying )
		StartTimer();

	*pResult = 0;
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);

	if( pScrollBar != &scrollCel )
		return;

/*
·	SB_LEFT   Scroll to far left.
·	SB_ENDSCROLL   End scroll.
·	SB_LINELEFT   Scroll left.
·	SB_LINERIGHT   Scroll right.
·	SB_PAGELEFT   Scroll one page left.
·	SB_PAGERIGHT   Scroll one page right.
·	SB_RIGHT   Scroll to far right.
·	SB_THUMBPOSITION   Scroll to absolute position. The current position is specified by the nPos parameter.
·	SB_THUMBTRACK   Drag scroll box to specified position. The current position is specified by the nPos parameter.
*/
	if( !pSequence || pSequence->lstSeqCels.IsEmpty() )
		return;

	switch( nSBCode )
	{
	case SB_LEFT:
		iSeqCel = 0;
		break;
	case SB_ENDSCROLL:
//		"The SB_ENDSCROLL scroll bar notification code, which indicates that the
//		user has released the mouse button after scrolling, is missing from the
//		documentation for the CWnd::OnHScroll() function."  Gotta love it.
		break;
	case SB_LINELEFT:
	case SB_PAGELEFT:
		iSeqCel -= 1;
		if( iSeqCel == -1 || iSeqCel == -2 )
			iSeqCel = pSequence->lstSeqCels.GetCount() - 1;
		break;
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
		iSeqCel += 1;
		if( iSeqCel == pSequence->lstSeqCels.GetCount() )
			iSeqCel = 0;
		break;
	case SB_RIGHT:
		iSeqCel = pSequence->lstSeqCels.GetCount() - 1;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		iSeqCel = nPos;
		break;
	}
	SetScrollFrom_iSeqCel();

	//	Update controls data based on sequence data.
	UpdateData( FALSE );

}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnSequenceHotspotnew() 
{
	//	New hotspot menu choice selected.
	ASSERT( pSequence );
	pSequence->AddHSpot();	
}

//-----------------------------------------------------------------------------------------------------------------
int CCelView::OnVKeyToItem(UINT nKey, CListBox* pListBox, UINT nIndex) 
{
	//	Listbox virtual keypress handler.

	int iSelected;

	switch( nKey )
	{
	case VK_DELETE:
		ASSERT( pSequence );
		iSelected = listboxHSpots.GetCurSel();
		if( iSelected == 0 )
			MessageBox( "The Primary hotspot cannot be deleted.", "Error", MB_OK | MB_ICONEXCLAMATION );
		else if( iSelected != LB_ERR )
		{
			CString csText;
			listboxHSpots.GetText( iSelected, csText );
			csText = "Are you sure you want to remove the hotspot \"" + csText;
			csText += "\" from all cels in this sequence?";
			if( MessageBox( csText, "Confirm Hotspot Delete", MB_YESNO | MB_ICONQUESTION ) == IDYES )
				pSequence->DeleteHSpot( iSelected );
		}
		break;
	case VK_INSERT:
		ASSERT( pSequence );
		pSequence->AddHSpot();
		break;
	}

	return CFormView::OnVKeyToItem(nKey, pListBox, nIndex);
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnSelchangeListHspots() 
{
	//	Hotspots listbox selection changed.
//	SyncHSpot();

	//	Update controls.
	UpdateData( FALSE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnButtonPlaystop() 
{
	if( !bPlaying )
	{
		if( pSequence->lstSeqCels.IsEmpty() )
			return;
		if( !StartTimer() )
			MessageBox( "Could not create animation timer.", "Error", MB_OK | MB_ICONEXCLAMATION );
		else
			bPlaying = TRUE;
	}
	else
	{
		VERIFY( KillTimer( iTimerID ) );
		bPlaying = FALSE;
	}	
	UpdateData( FALSE );	//	Reflect button text change.
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnTimer(UINT nIDEvent) 
{
	//	Only called when bPlaying.
	ASSERT( nIDEvent == iTimerID );
	
	if( !pSequence || pSequence->lstSeqCels.IsEmpty() )
	{
		//	[ This can't happen the way the UI is set now, but might come up in future. ] 
		//	Press the "Stop" button.
		GetDlgItem( IDC_BUTTON_PLAYSTOP )->PostMessage( BM_CLICK );
		return;
	}

	iSeqCel += 1;
	if( iSeqCel == pSequence->lstSeqCels.GetCount() )
	{
		iSeqCel = 0;

		m_cycle++;
		if (m_cycle > m_move_cycles)
			ResetCycle();

		if( !bLooped )
			GetDlgItem( IDC_BUTTON_PLAYSTOP )->PostMessage( BM_CLICK );

		//	ajw 5/14/97
		if( bTransition && pSequencePrev )
			LinkToSequence( pSequencePrev );
	}

	SetScrollFrom_iSeqCel();

	DrawImages( TRUE );

}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( bPtOnBigCel( point ) && iSeqCel != -1 )
	{
		int iSelected = listboxHSpots.GetCurSel();
		if( iSelected == 0 )
		{
			//	[ Primary hot spot is selected. Go into moving primary hot spot mode. ]
			bMouseDown	= TRUE;
			bMoveAll	= ( nFlags & MK_CONTROL );		//	Mousedown with Ctrl starts moving all primary hot spots mode.
			ptMouseDown	= point;
			//	Record pSeqCel's current primary hotspot location.
			ASSERT( pSequence );
			ASSERT( iSeqCel != -1 );

			POSITION posSeqCel = pSequence->lstSeqCels.FindIndex( iSeqCel );
			ASSERT( posSeqCel );
			CSequenceCel* pSeqCel = pSequence->lstSeqCels.GetAt( posSeqCel );
			//	Primary hotspotloc is guaranteed to appear as the first HSpotLoc for the sequence cel.
			POSITION posFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetHeadPosition();
			CHSpotLoc* pFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posFirstHSpotLoc );
			ptHSpotOriginal.x = pFirstHSpotLoc->x;
			ptHSpotOriginal.y = pFirstHSpotLoc->y;

			//	Set the cursor. (Brute force method, perhaps unkosher.)
			if( bMoveAll )
			{
				SetCursor( hcurHSpotPrimarySet );											//	Good until the mouse moves.
				SetClassLong( GetSafeHwnd(), GCL_HCURSOR, (LONG)hcurHSpotPrimarySet );		//	Good after the mouse moves.
			}
			else
			{
				SetCursor( hcurHSpotPrimarySetAll );											//	Good until the mouse moves.
				SetClassLong( GetSafeHwnd(), GCL_HCURSOR, (LONG)hcurHSpotPrimarySetAll );		//	Good after the mouse moves.
			}

			int iXLoEndGap = ( ( sizImageArea.cx / 2 ) - ptHSpotOriginal.x + pSeqCel->pCel->xCrop ) * iZoom;
			int iYLoEndGap = ( ( sizImageArea.cy / 2 ) - ptHSpotOriginal.y + pSeqCel->pCel->yCrop ) * iZoom;
			int iXHiEndGap = ( ( sizImageArea.cx / 2 ) - ( pSeqCel->pCel->GetWidth() - ptHSpotOriginal.x + pSeqCel->pCel->xCrop ) ) * iZoom;
			int iYHiEndGap = ( ( sizImageArea.cy / 2 ) - ( pSeqCel->pCel->GetHeight() - ptHSpotOriginal.y + pSeqCel->pCel->yCrop ) ) * iZoom;
			CRect rcClip( point.x - iXLoEndGap, point.y - iYLoEndGap + 1, point.x + iXHiEndGap, point.y + iYHiEndGap + 1 );
			//	[ +1 to bottom right hand corner because of CRect's nonsensical implementation. ]
			ClientToScreen( &rcClip );
			//	ajw ClipCursor removed 5/8/97
			//VERIFY( ClipCursor( &rcClip ) );
			////	[ Note: Clipping the cursor now makes less sense with the addition of the 'bMoveAll' concept, but I'll leave it for now. ]
		}
		else if( iSelected != LB_ERR )
		{
			ASSERT( pSequence );
			ASSERT( iSeqCel != -1 );

			//	Get current sequencecel.
			POSITION posSeqCel = pSequence->lstSeqCels.FindIndex( iSeqCel );
			ASSERT( posSeqCel );
			CSequenceCel* pSeqCel = pSequence->lstSeqCels.GetAt( posSeqCel );
			//	Primary hotspotloc is guaranteed to appear as the first HSpotLoc for the sequence cel.
			POSITION posFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetHeadPosition();
			CHSpotLoc* pFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posFirstHSpotLoc );
			//	Get HSpotLoc based on listbox selection.
			POSITION posHSpotLoc = pSeqCel->lstHSpotLocs.FindIndex( iSelected );
			CHSpotLoc* pHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posHSpotLoc );
			//	Set to new position.
			pHSpotLoc->x = ( point.x - iXOriginBig - ( sizImageArea.cx/2 - pFirstHSpotLoc->x ) * iZoom ) / iZoom;
			pHSpotLoc->y = ( point.y - iYOriginBig - ( sizImageArea.cy/2 - pFirstHSpotLoc->y ) * iZoom ) / iZoom;

			CAnimEditorDoc* pDoc = GetDocument();
			pDoc->SetModifiedFlag();

			//	Reflect hot spot location change.
			UpdateData( FALSE );
		}
	}
	CFormView::OnLButtonDown(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( bMouseDown )
	{
		//	[ Leave moving primary hot spot mode. ]
		bMouseDown = FALSE;
		//	Set the cursor. (Brute force method, perhaps unkosher.)
		SetCursor( hcurNormal );											//	Good until the mouse moves.
		SetClassLong( GetSafeHwnd(), GCL_HCURSOR, (LONG)hcurNormal );		//	Good after the mouse moves.
		ClipCursor( NULL );

		CMainFrame* pMainFrame = (CMainFrame*)GetParentFrame();
		pMainFrame->SetMessageText( "" );

		//	Reflect hot spot location change.
		UpdateData( FALSE );
	}

	CFormView::OnLButtonUp(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( bMouseDown )
	{
		//	[ Moving primary hot spot mode. ]
		CPoint ptDelta = point - ptMouseDown;
		ptDelta.x /= iZoom;
		ptDelta.y /= iZoom;

		//	Set pSeqCel's primary hotspot location.
		ASSERT( pSequence );
		ASSERT( iSeqCel != -1 );

		if( !bMoveAll )
		{
			POSITION posSeqCel = pSequence->lstSeqCels.FindIndex( iSeqCel );
			ASSERT( posSeqCel );
			CSequenceCel* pSeqCel = pSequence->lstSeqCels.GetAt( posSeqCel );

			//	Primary hotspotloc is guaranteed to appear as the first HSpotLoc for the sequence cel.
			POSITION posFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetHeadPosition();
			CHSpotLoc* pFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posFirstHSpotLoc );
			pFirstHSpotLoc->x = ptHSpotOriginal.x - ptDelta.x;
			pFirstHSpotLoc->y = ptHSpotOriginal.y - ptDelta.y;
			SetHSpotLocText( pSeqCel );		//	Sets csHSpotLoc.
		}
		else
		{
			POSITION posSeqCel = pSequence->lstSeqCels.GetHeadPosition();
			ASSERT( posSeqCel );
			CSequenceCel* pSeqCel;
			while( posSeqCel )
			{
				pSeqCel = pSequence->lstSeqCels.GetNext( posSeqCel );

				//	Primary hotspotloc is guaranteed to appear as the first HSpotLoc for the sequence cel.
				POSITION posFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetHeadPosition();
				CHSpotLoc* pFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posFirstHSpotLoc );
				pFirstHSpotLoc->x = ptHSpotOriginal.x - ptDelta.x;		//	xxx this is incorrect - need an array of orig pts. xxx
				pFirstHSpotLoc->y = ptHSpotOriginal.y - ptDelta.y;
			}
			posSeqCel = pSequence->lstSeqCels.FindIndex( iSeqCel );
			ASSERT( posSeqCel );
			pSeqCel = pSequence->lstSeqCels.GetAt( posSeqCel );
			SetHSpotLocText( pSeqCel );		//	Sets csHSpotLoc.
		}

		DrawImages( TRUE );

		CMainFrame* pMainFrame = (CMainFrame*)GetParentFrame();
		pMainFrame->SetMessageText( csHSpotLoc );	//	Would like to set it on the view instead...

		CAnimEditorDoc* pDoc = GetDocument();
		pDoc->SetModifiedFlag();
	}
	else 
	{
		int iSelected = listboxHSpots.GetCurSel();
		if( iSelected != LB_ERR && iSelected != 0 && bPtOnBigCel( point ) )
		{
			//	Non-primary hotspot selected.
			//	Set the cursor till mouse moves.
			SetCursor( hcurHSpotSet );											//	Good until the mouse moves.
		}
	}

	CFormView::OnMouseMove(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if( bMouseDown )
	{
		//	[ Cancel moving primary hot spot mode. ]
		//	Set pSeqCel's primary hotspot location.
		ASSERT( pSequence );
		ASSERT( iSeqCel != -1 );

		CSequenceCel* pSeqCel;
		if( !bMoveAll )
		{
			POSITION posSeqCel = pSequence->lstSeqCels.FindIndex( iSeqCel );
			ASSERT( posSeqCel );
			pSeqCel = pSequence->lstSeqCels.GetAt( posSeqCel );

			//	Primary hotspotloc is guaranteed to appear as the first HSpotLoc for the sequence cel.
			POSITION posFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetHeadPosition();
			CHSpotLoc* pFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posFirstHSpotLoc );
			pFirstHSpotLoc->x = ptHSpotOriginal.x;
			pFirstHSpotLoc->y = ptHSpotOriginal.y;
			SetHSpotLocText( pSeqCel );	//	Sets csHSpotLoc.
		}
		else
		{
			//	Figure out how much we've offsetted everyone's hotspots by examining iSeqCel.
			POSITION posSeqCel = pSequence->lstSeqCels.FindIndex( iSeqCel );
			ASSERT( posSeqCel );
			pSeqCel = pSequence->lstSeqCels.GetAt( posSeqCel );
			CSequenceCel* pSeqCelNow = pSeqCel;

			//	Primary hotspotloc is guaranteed to appear as the first HSpotLoc for the sequence cel.
			POSITION posFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetHeadPosition();
			CHSpotLoc* pFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posFirstHSpotLoc );
			int iXOffset = pFirstHSpotLoc->x - ptHSpotOriginal.x;
			int iYOffset = pFirstHSpotLoc->y - ptHSpotOriginal.y;

			//	Reset all primary hotspots based on offset.
			posSeqCel = pSequence->lstSeqCels.GetHeadPosition();
			ASSERT( posSeqCel );
			while( posSeqCel )
			{
				pSeqCel = pSequence->lstSeqCels.GetNext( posSeqCel );

				//	Primary hotspotloc is guaranteed to appear as the first HSpotLoc for the sequence cel.
				posFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetHeadPosition();
				pFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posFirstHSpotLoc );
				pFirstHSpotLoc->x -= iXOffset;
				pFirstHSpotLoc->y -= iYOffset;
			}
			SetHSpotLocText( pSeqCelNow );	//	Sets csHSpotLoc.
		}

		bMouseDown = FALSE;
		//	Set the cursor. (Brute force method, perhaps unkosher.)
		SetCursor( hcurNormal );											//	Good until the mouse moves.
		SetClassLong( GetSafeHwnd(), GCL_HCURSOR, (LONG)hcurNormal );		//	Good after the mouse moves.
		ClipCursor( NULL );

		CMainFrame* pMainFrame = (CMainFrame*)GetParentFrame();
		pMainFrame->SetMessageText( "" );

		//	Reflect hot spot location change.
		UpdateData( FALSE );
	}

	CFormView::OnRButtonDown(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------------------
void CCelView::LinkToSequence( CSequence* pSeq )
{
	//	Tie celview to a sequence and show change. ( pSeq can be NULL to remove link to any sequence. )

	if( bPlaying )
	{
//		VERIFY( KillTimer( iTimerID ) );
//		bPlaying = FALSE;
	}

	pSequencePrev = pSequence;
	if( btnPrevious.GetSafeHwnd() )
		btnPrevious.EnableWindow( pSequencePrev != NULL );
	
	pSequence = pSeq;
	CChildFrame* pFrame = (CChildFrame*)GetParentFrame();
	pFrame->pCelViewSequence = pSequence;

	if( pSequencePrev )
		pSequencePrev->pSeqView->InvalidateRect( NULL );

	if( pSequence )
	{
		//	iSeqCel is set to first currently selected seqcel.
		iSeqCel		= pSequence->iFirstSelectedSeqCel();
		//	Set size vars...
		CalcSizeChanges();
		SetScrollBarRange();
		pSequence->pSeqView->InvalidateRect( NULL, FALSE );
	}
	else
	{
		iSeqCel = -1;
	}
	SetScrollFrom_iSeqCel();

//	if( !bPlaying )			//	trying to stop it flashing on transition anims...
		//	Update controls data based on sequence data.
		UpdateData( FALSE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::LinkImage( CSequenceCel* pSeqCelLink )
{
	ASSERT( pSequence );

	//	Set iSeqCel to refer to the sequence cel passed and redraw.
	//	Also resets scroll bar ranges and position.
	SetScrollBarRange();

	if( pSeqCelLink == NULL )
	{
		iSeqCel = -1;
		SetScrollFrom_iSeqCel();
	}
	else
	{
		POSITION posInList = pSequence->lstSeqCels.GetHeadPosition();
		CSequenceCel* pSeqCel;
		int	iCount = -1;
		while( posInList )
		{
			iCount++;
			pSeqCel = pSequence->lstSeqCels.GetNext( posInList );
			if( pSeqCelLink == pSeqCel )
			{
				iSeqCel = iCount;
				SetScrollFrom_iSeqCel();
				break;
			}
		}
	}

	//	Update controls data based on sequence data.
	UpdateData( FALSE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::SetScrollBarRange()
{
	if( scrollCel.m_hWnd )	//	[ scrollCel is not attached to the real scroll bar until first DoDataExchange... ]
	{
		if( pSequence )
			scrollCel.SetScrollRange( 0, pSequence->lstSeqCels.GetCount() - 1 );
		else
			scrollCel.SetScrollRange( 0, 0 );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::SetScrollFrom_iSeqCel()
{
	if( scrollCel.m_hWnd )	//	[ scrollCel is not attached to the real scroll bar until first DoDataExchange... ]
	{
		if( iSeqCel == -1 )
			scrollCel.SetScrollPos( 0 );
		else
			scrollCel.SetScrollPos( iSeqCel );
	}
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CCelView::bHotSpotsListBoxMatchesList()
{
	//	Returns TRUE if the listboxHSpots control exactly matches the pSequence->lstHSpots.
	if( listboxHSpots.GetCount() != pSequence->lstHSpots.GetCount() )
		return FALSE;

	BOOL		bMatches		= TRUE;
	POSITION	posInList		= pSequence->lstHSpots.GetHeadPosition();
	CHSpot*		pHSpot;
	CString		csListBoxText;
	int			iListCount		= -1;
	while( posInList )
	{
		iListCount++;
		pHSpot = pSequence->lstHSpots.GetNext( posInList );
		listboxHSpots.GetText( iListCount, csListBoxText );
		if( pHSpot->csName != csListBoxText )
		{
			bMatches = FALSE;
			break;
		}
	}
	return bMatches;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CCelView::bActiveAndLinkedToSequence( CSequence* pSeq )
{
	//	Return TRUE if I am linked to pSeq and currently have focus.
	if( pSequence != pSeq )
		return FALSE;

	CFrameWnd* pMainFrame = GetParentFrame();
	if( pMainFrame->GetActiveView() == this )
		return TRUE;
	else
		return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::DrawImages( BOOL bErase )
{
	//	Draw the bitmaps. bErase is TRUE when we are animating.

	if( !pSequence || iSeqCel == -1 )
		return;

	POSITION posSeqCel = pSequence->lstSeqCels.FindIndex( iSeqCel );
	ASSERT( posSeqCel );
	CSequenceCel* pSeqCel = pSequence->lstSeqCels.GetAt( posSeqCel );

	//	Get pSeqCel's primary hotspot location.
	//	Guaranteed to appear as the first HSpotLoc for the sequence cel.
	POSITION posFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetHeadPosition();
	CHSpotLoc* pFirstHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posFirstHSpotLoc );
	int iXOff = pFirstHSpotLoc->x;
	int iYOff = pFirstHSpotLoc->y;

	if( sizImageArea.cx != 0 || sizImageArea.cy != 0 )
	{
		CClientDC dc( this );

		CDC* pdcOffScreen = new CDC;
		pdcOffScreen->CreateCompatibleDC( NULL );

		SetupOffscreen(pdcOffScreen);
		SelectObject(pdcOffScreen->GetSafeHdc(), m_offscreen_hbm);

		CRect rcEdgeMove( iXOriginBig, iYOriginBig, iXOriginBig + m_iWidthAvail - 6 , iYOriginBig + m_iHeightAvail - 6 );
		CRect rcEdgeBig( iXOriginBig, iYOriginBig, iXOriginBig + sizImageArea.cx * iZoom , iYOriginBig + sizImageArea.cy * iZoom );
		CRect rcEdgeSmall( iXOriginSmall, iYOriginSmall, iXOriginSmall + sizImageArea.cx, iYOriginSmall + sizImageArea.cy );

		int iXCenterMove = iXOriginBig + m_iWidthAvail / 2;
		int iYCenterMove = iYOriginBig + m_iHeightAvail / 2;
		int iXCenterBig = iXOriginBig + ( sizImageArea.cx * iZoom ) / 2;
		int iYCenterBig = iYOriginBig + ( sizImageArea.cy * iZoom ) / 2;
		int iXCenterSmall = iXOriginSmall + sizImageArea.cx / 2;
		int iYCenterSmall = iYOriginSmall + sizImageArea.cy / 2;

		int iWidth = pSeqCel->pCel->dibImage.GetWidth();
		int iHeight = pSeqCel->pCel->dibImage.GetHeight();

		CBrush brBack;
		brBack.CreateSolidBrush( theApp.colorDialog );
		CRect rcOff(0,0,iWidth,iHeight);
		pdcOffScreen->FillRect( &rcOff, &brBack );

		if( bErase )
		{
			dc.FillRect( &rcEdgeSmall, &brBack );

			if (m_bMoving)
				dc.FillRect( &rcEdgeMove, &brBack );
		}

		if( pSequence->pdibBackground )	{
			int iX = iXCenterSmall - pSequence->pdibBackground->GetHotspotX();
			int iY = iYCenterSmall - pSequence->pdibBackground->GetHotspotY();
			pSequence->pdibBackground->DrawTransparent(&dc, iX, iY );
		}

//		pSeqCel->pCel->dibImage.DrawTransparent(&dc, 
//			iXCenterSmall - ( iXOff - pSeqCel->pCel->xCrop ), 
//			iYCenterSmall - ( iYOff - pSeqCel->pCel->yCrop) );
		pSeqCel->pCel->dibImage.DrawTransparent(pdcOffScreen, 0, 0);
		dc.BitBlt(iXCenterSmall - ( iXOff - pSeqCel->pCel->xCrop ), iYCenterSmall - ( iYOff - pSeqCel->pCel->yCrop),
			iWidth, iHeight, pdcOffScreen, 0, 0, SRCCOPY);

		if( !bErase )
		{
			rcEdgeSmall.InflateRect( 3, 3 );
			dc.DrawEdge( &rcEdgeSmall, EDGE_SUNKEN, BF_RECT );

			if (m_bMoving)	{
				rcEdgeMove.InflateRect( 3, 3 );
				dc.DrawEdge( &rcEdgeMove, EDGE_SUNKEN, BF_RECT );
			}
			else	{
				dc.FillRect( &rcEdgeMove, &brBack );

				rcEdgeBig.InflateRect( 3, 3 );
				dc.DrawEdge( &rcEdgeBig, EDGE_SUNKEN, BF_RECT );
			}
			//	[ Actually drawn one pixel short because of CRect's stupid implementation. ]
		}

		if (!m_bMoving)	{
			// normal animation in place
			dc.StretchBlt( rcEdgeBig.left, rcEdgeBig.top, rcEdgeBig.Width(), rcEdgeBig.Height(),
						&dc, rcEdgeSmall.left, rcEdgeSmall.top, rcEdgeSmall.Width(), rcEdgeSmall.Height(), SRCCOPY );
		}
		else	{
			// moving animation
			long pixels;
			long direction = pSequence->iDirection;

			fdx += (float)cos_table[direction] * pSequence->iMoveSpeed / pSequence->iSpeed;
			pixels = (long) fdx;
			fdx -= pixels;
			iXPosSeq += pixels;

			fdy += (float)sin_table[direction] * pSequence->iMoveSpeed / pSequence->iSpeed;
			pixels = (long) fdy;
			fdy -= pixels;
			iYPosSeq += pixels;

			dc.BitBlt(iXPosSeq+iXCenterMove-iXOff, iYPosSeq+iYCenterMove-iYOff, iWidth, iHeight, pdcOffScreen, 0, 0, SRCCOPY);
		}

		//	Hotspots...
		int iSelected = listboxHSpots.GetCurSel();
		if( iSelected == 0 )
		{
			//	Show primary hotspot in center.
			int iXHSpot = iXCenterBig - ( dibHSpotPrimary.GetWidth() / 2 ) * iZoom;
			int iYHSpot = iYCenterBig - ( dibHSpotPrimary.GetHeight() / 2 ) * iZoom;
			dibHSpotPrimary.DrawZoomed( &dc, CPoint( iXHSpot, iYHSpot ), iZoom, SRCPAINT, FALSE );
		}
		else if( iSelected != LB_ERR )
		{
			//	Get the appropriate CHSpotLoc from pSeqCel. Appears in list in the same location that
			//	the selected hot spot appears in CSequence's list (and therefore also in the list box).
			POSITION posHSpotLoc = pSeqCel->lstHSpotLocs.FindIndex( iSelected );
			CHSpotLoc* pHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posHSpotLoc );
			int iXHSpot = iXCenterBig + ( pHSpotLoc->x - iXOff - dibHSpot.GetWidth()/2 ) * iZoom;
			int iYHSpot = iYCenterBig + ( pHSpotLoc->y - iYOff - dibHSpot.GetHeight()/2 ) * iZoom;
			dibHSpot.DrawZoomed( &dc, CPoint( iXHSpot, iYHSpot ), iZoom, SRCPAINT, FALSE );
		}

		delete pdcOffScreen;
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::CalcSizeChanges( int cx, int cy )
{
	//	Sets sizImageArea and iZoom after changes to size or sequence occur.
	if( cx == 0 || cy == 0 )
	{
		CRect rcWindow;
		GetClientRect( &rcWindow );
		cx = rcWindow.right;
		cy = rcWindow.bottom;
	}

	//	Determine Zoom factor based on size of images in sequence and size of view.
	if( !pSequence )
	{
		iZoom = 1;
		return;
	}

	if( pSequence->lstSeqCels.GetCount() == 0 )
		iZoom = 1;
	else
	{
		//	Set sizImageArea to size of largest sequence cel.
		sizImageArea = pSequence->ImageBoundsMax();

		sizImageArea.cx *= 2;		//	Double the space is needed because image can be offset.
		sizImageArea.cy *= 2;

		//	How many times can we fit this size into the window space available?
		m_iWidthAvail	= cx - iXOriginBig;
		m_iHeightAvail	= cy - iYOriginBig;

		int iFitX = (int)( m_iWidthAvail / sizImageArea.cx );
		int iFitY = (int)( m_iHeightAvail / sizImageArea.cy );

		iZoom = max( min( iFitX, iFitY ), 1 );
	}

	InvalidateRect( NULL );		//	Happens anyway? xxx

}

//-----------------------------------------------------------------------------------------------------------------
BOOL CCelView::StartTimer()
{
	//	Start a timer going for animation.
	//	If a timer is already running, kills it and creates a new one (for speed changes).
	ASSERT( pSequence );
	if( bPlaying )
	{
		VERIFY( KillTimer( iTimerID ) );
	}

	ResetCycle();
	return ( SetTimer( iTimerID, 1000 / pSequence->iSpeed, NULL ) == iTimerID );
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CCelView::bPtOnBigCel( const CPoint& ptTest )
{
	//	Returns TRUE if point is on the big animation cel area.
	CRect rcArea( iXOriginBig, iYOriginBig + 1, iXOriginBig + sizImageArea.cx * iZoom , iYOriginBig + sizImageArea.cy * iZoom + 1 );
	return rcArea.PtInRect( ptTest );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::SetHSpotLocText( CSequenceCel* pSeqCel )
{
	//	Sets csHSpotLoc.
	int iSelected = listboxHSpots.GetCurSel();
	if( iSelected != LB_ERR  &&  iSeqCel != -1 )
	{
		//	Get the appropriate CHSpotLoc from pSeqCel. Appears in list in the same location that
		//	the selected hot spot appears in CSequence's list (and therefore also in the list box).
		POSITION posHSpotLoc = pSeqCel->lstHSpotLocs.FindIndex( iSelected );
		CHSpotLoc* pHSpotLoc = pSeqCel->lstHSpotLocs.GetAt( posHSpotLoc );
		csHSpotLoc.Format( "(%i,%i)", pHSpotLoc->x - pSeqCel->pCel->xCrop, pHSpotLoc->y - pSeqCel->pCel->yCrop );
	}
	else
		csHSpotLoc = "";
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnButtonBackground() 
{
	ASSERT( pSequence );
	CString csBackgroundBMPOld = pSequence->csBackgroundBMP;

	CString csFileExt		= "BMP";
	CString csFileFilter	= "Bitmap Files (*.bmp)|*.bmp||";
	CString csDefault;
	if( csBackgroundBMPOld != NO_BACKGROUND )
		csDefault = csBackgroundBMPOld;

	CFileDialog	dlg( TRUE, csFileExt, csDefault, OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, csFileFilter );

	if( dlg.DoModal() == IDOK )
	{
		pSequence->SetBackgroundBMP( dlg.GetPathName() );

		if( csBackgroundBMPOld != pSequence->csBackgroundBMP )
		{
			CAnimEditorDoc* pDoc = GetDocument();
			pDoc->SetModifiedFlag();
			//	Update controls data based on sequence data.
			UpdateData( FALSE );
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnButtonBackgroundclear() 
{
	ASSERT( pSequence );
	if( pSequence->csBackgroundBMP != NO_BACKGROUND )
	{
		pSequence->SetBackgroundBMP( NO_BACKGROUND );
		CAnimEditorDoc* pDoc = GetDocument();
		pDoc->SetModifiedFlag();
		//	Update controls data based on sequence data.
		UpdateData( FALSE );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnCheckLooped() 
{
	UpdateData( TRUE );	
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnCheckMoving() 
{
	UpdateData( TRUE );		
}

//-----------------------------------------------------------------------------------------------------------------
#define PI 3.1415926535
//-----------------------------------------------------------------------------------------------------------------
void CCelView::SetupMovementTables(void)	{
	int dir;
	int degrees;
	int angle;
	double radians;

	for (dir = 0; dir<CIRCLE_UNITS; dir++)	{
		degrees = (int) (((double) dir * 360) / CIRCLE_UNITS);
		angle = degrees + 90;
		radians = (angle * PI) / 180;
		sin_table[dir] = -sin(radians);
		cos_table[dir] = cos(radians);
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::ResetCycle() 
{
	// setup movement animation
	iXPosSeq = 0;
	iYPosSeq = 0;
	fdx = fdy = 0;
	m_cycle = 0;
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnButtonPrevious() 
{
	//	User pressed "Go To Previous" button. Switch to previously selected sequence.
	if( pSequencePrev )
	{
		LinkToSequence( pSequencePrev );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnCheckTransition() 
{
	UpdateData( TRUE );		
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnZoomin() 
{
	iZoom++;
	DrawImages( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnZoomout() 
{
	if( iZoom > 1 )
		iZoom--;
	DrawImages( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnDeltaposSpinShifthorz(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	iXOriginBig -= 10 * pNMUpDown->iDelta;
	DrawImages( TRUE );
	
	*pResult = 0;
}

//-----------------------------------------------------------------------------------------------------------------
void CCelView::OnDeltaposSpinShiftvert(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	iYOriginBig += 10 * pNMUpDown->iDelta;
	DrawImages( TRUE );
	
	*pResult = 0;
}
