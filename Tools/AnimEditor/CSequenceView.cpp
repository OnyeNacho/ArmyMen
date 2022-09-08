// CSequenceView.cpp : implementation file
//

#include "stdafx.h"
#include "animeditor.h"
#include "CSequenceView.h"

#include "CSequence.h"
#include "CCel.h"
#include "CMultipleSequencesView.h"
#include "CCelView.h"
#include "AnimEditorDoc.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSequenceView

IMPLEMENT_DYNCREATE(CSequenceView, CScrollView)

CSequenceView::CSequenceView()
{
	iHeight			= CSEQUENCEVIEW_DEFAULTHEIGHT;

	//	Create the view's fonts.
	LOGFONT	lf;
	memset( &lf, 0, sizeof(LOGFONT) );
	lstrcpy( lf.lfFaceName, "Arial" );
	lf.lfHeight = 10;
	lf.lfWidth	= 5;
	VERIFY( fontSmall.CreateFontIndirect( &lf ) );

	memset( &lf, 0, sizeof(LOGFONT) );
	lstrcpy( lf.lfFaceName, "Arial" );
	lf.lfHeight = 40;
	lf.lfWidth	= 30;
	VERIFY( fontLarge.CreateFontIndirect( &lf ) );

	pSequence = NULL;
}

CSequenceView::~CSequenceView()
{
}

BEGIN_MESSAGE_MAP(CSequenceView, CScrollView)
	//{{AFX_MSG_MAP(CSequenceView)
	ON_WM_LBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopyOrCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_WM_KEYUP()
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_SEQUENCE_HOTSPOTNEW, OnUpdateSequenceHotspotnew)
	ON_COMMAND(ID_SEQUENCE_HOTSPOTNEW, OnSequenceHotspotnew)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopyOrCut)
	ON_COMMAND(ID_SPECIAL_HSPOTSEQCELTOCATALOG, OnSpecialHspotseqceltocatalog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSequenceView drawing

void CSequenceView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

//	CSize sizeTotal;
//	// TODO: calculate the total size of this view
//	sizeTotal.cx = sizeTotal.cy = 100;
//	SetScrollSizes(MM_TEXT, sizeTotal);
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CSequenceView::OnEraseBkgnd(CDC* pDC) 
{
	RECT rcWindow;
	GetClientRect( (LPRECT)&rcWindow );
	CBrush brBack;

	//	Does the CelView have focus and is linked to us?...
	BOOL bCelViewPseudoFocus = FALSE;
	bCelViewPseudoFocus = GetCelView()->bActiveAndLinkedToSequence( pSequence );

	//	And do we have focus??
	CFrameWnd* pMainFrame = GetParentFrame();
	if( bCelViewPseudoFocus || pMainFrame->GetActiveView() == this )
		brBack.CreateSolidBrush( theApp.colorWindow );
	else
		brBack.CreateSolidBrush( theApp.colorDialog );
	pDC->FillRect( &rcWindow, &brBack );

//	return CScrollView::OnEraseBkgnd(pDC);
	return TRUE;
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();

	CChildFrame* pFrame = (CChildFrame*)GetParentFrame();
	//BOOL bShowSelected = ( pMainFrame->GetActiveView() == this );
	BOOL bShowSelected = ( pFrame->pCelViewSequence == pSequence );

	CRect rcThis;
	GetClientRect( &rcThis );

	if( bShowSelected )		//	ajw added 5/14/97
		pDC->BitBlt( 0, 0, rcThis.right, rcThis.bottom, pDC, 0, 0, WHITENESS );

	//	Select our font in.
	CFont* pfontOld = pDC->SelectObject( &fontSmall );

	//	Draw CSequenceCels in related CSequence.
	int	iCol = 0;
	POSITION posSeqCel = pSequence->lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posSeqCel )
	{
		pSeqCel = pSequence->lstSeqCels.GetNext( posSeqCel );
		pSeqCel->pCel->Draw( pDC, iCol * iColumnWidth + GAPFIRSTCOLUMN, 0, 
								pSeqCel->bSelected, pSeqCel->bDragSelected, pSeqCel->bActionFrame );
		iCol++;
	}

	rcThis.InflateRect( -1, -1 );
	CPoint ptScroll = GetScrollPosition();
	rcThis.OffsetRect( ptScroll.x, 0 );

	//	Show sequence 'appearance order' number as an additional means of telling them apart.
	pDC->SelectObject( &fontLarge );
	pDC->TextOut( rcThis.right - 5, rcThis.top + 5, csAppearance );

	if( bShowSelected )
	{
		rcThis.InflateRect( -1, -1 );
		pDC->DrawEdge( &rcThis, EDGE_SUNKEN, BF_RECT );
	}

	//	Restore original font.
	pDC->SelectObject( pfontOld );

}

/////////////////////////////////////////////////////////////////////////////
// CSequenceView diagnostics

#ifdef _DEBUG
void CSequenceView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSequenceView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSequenceView message handlers


//-----------------------------------------------------------------------------------------------------------------
int CSequenceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//	Register drop target.
	if( m_dropTarget.Register( this ) )
		return 0;
	else
		return -1;
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SelectAtPoint( TRUE, nFlags, point );

	CScrollView::OnLButtonDown(nFlags, point);
}


//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonDblClk(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	//	Set seqcel hit as the "action frame" for the sequence.

	//	Ask each seqcel if it's been hit.
	BOOL bChanged = FALSE;
	//	[ Much code duplicated from SelectAtPoint(). ]
	int	iCol = 0;
	POSITION posSeqCel = pSequence->lstSeqCels.GetHeadPosition();
	POSITION posNow;
	CSequenceCel* pSeqCel;
	while( posNow = posSeqCel )
	{
		pSeqCel = pSequence->lstSeqCels.GetNext( posSeqCel );
		if( pSeqCel->pCel->bPointInMe( CPoint( iCol * iColumnWidth + GAPFIRSTCOLUMN, 0 ), point ) )
		{
			if( !pSeqCel->bActionFrame )
			{
				pSeqCel->bActionFrame = TRUE;
				bChanged = TRUE;
			}
		}
		else
		{
			if( pSeqCel->bActionFrame )
			{
				pSeqCel->bActionFrame = FALSE;
				bChanged = TRUE;
			}
		}
		iCol++;
	}

	if( bChanged )
	{
		InvalidateRect( NULL );
		pSequence->pOwnerDoc->SetModifiedFlag( TRUE );
	}

	CScrollView::OnRButtonDown(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnRButtonUp(UINT nFlags, CPoint point) 
{
//	CAnimEditorDoc* pDoc = (CAnimEditorDoc*)GetDocument();

//	pSequence->xxx_AddSelectedCels();		//	Add cels selected in AnimEditorView to the sequence.
//	CalcSizeChanges();
//
//	( (CMultipleSequencesView*)GetParent() )->Arrange();
//	
	CScrollView::OnRButtonUp(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
//	//	Force myself to redraw, so the focus rect is shown/unshown.
//	InvalidateRect( NULL );
	
	if( bActivate )
	{
		//	Sync the CelView to my sequence.
		GetCelView()->LinkToSequence( pSequence );
	}

	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CSequenceView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	//	Hack so that focus rect is drawn correctly.
	InvalidateRect( NULL );
	
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnUpdateSequenceHotspotnew(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( TRUE );	
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	//	Enable menu choice based on availability of valid data in the clipboard.
	COleDataObject dataObj;
	dataObj.AttachClipboard();
	BOOL bAvail = ( dataObj.IsDataAvailable( theApp.clipFormatCel ) || 
					dataObj.IsDataAvailable( theApp.clipFormatSequenceCel ) );
	pCmdUI->Enable( bAvail );
//	pCmdUI->Enable( TRUE );
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnUpdateEditCopyOrCut(CCmdUI* pCmdUI) 
{
	//	Enable menu choice based on availability of selected sequence cels.
	pCmdUI->Enable( pSequence->iCountSelected() > 0 );
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnEditCopy() 
{
	//	Create an OLE data source on the heap
	COleDataSource* pData = new COleDataSource;		//	[Deleted by the framework.]
	pSequence->PutDataOnClipboard( pData );
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnEditCut() 
{
	//	Create an OLE data source on the heap
	COleDataSource* pData = new COleDataSource;		//	[Deleted by the framework.]
	pSequence->PutDataOnClipboard( pData );
	if( pSequence->DeleteSelected( FALSE ) )
		pSequence->pOwnerDoc->DocModified();
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnEditPaste() 
{
	pSequence->GetDataFromClipboard();
	CalcSizeChanges();
	( (CMultipleSequencesView*)GetParent() )->Arrange();
}

//-----------------------------------------------------------------------------------------------------------------
DROPEFFECT CSequenceView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
//	return CScrollView::OnDragOver(pDataObject, dwKeyState, point);
	COleDataObject dataObj;
	dataObj.AttachClipboard();
	BOOL bAvail = ( dataObj.IsDataAvailable( theApp.clipFormatCel ) || 
					dataObj.IsDataAvailable( theApp.clipFormatSequenceCel ) );
	DROPEFFECT effect;
	if( dataObj.IsDataAvailable( theApp.clipFormatCel ) )
	{
		//	Data is from an AnimEditorView.
		if( dwKeyState & MK_SHIFT )
			effect = DROPEFFECT_MOVE;
		else
			effect = DROPEFFECT_COPY;
	}
	else if( dataObj.IsDataAvailable( theApp.clipFormatSequenceCel ) )
	{
		//	Data is from a SequenceView.
		if( dwKeyState & MK_CONTROL )
			effect = DROPEFFECT_COPY;
		else
			effect = DROPEFFECT_MOVE;
	}
	else
	{
		return DROPEFFECT_NONE;
	}
	if( !SelectAtPoint( FALSE, 0, point ) )
	{
		//	[ Nothing is hit at this point. ]
		//	For dragging, we'll clear any selection if this is the case (mainly so cels can be appended to the end easily).
		if( pSequence->iCountSelected() > 0 )
		{
			pSequence->SequenceCelSelectOnly( NULL );
			InvalidateRect( NULL );
		}
	}

	return effect;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CSequenceView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
//	return CScrollView::OnDrop(pDataObject, dropEffect, point);
	COleDataObject dataObj;
	dataObj.AttachClipboard();
	BOOL bAvail = ( dataObj.IsDataAvailable( theApp.clipFormatCel ) || 
					dataObj.IsDataAvailable( theApp.clipFormatSequenceCel ) );
	if( bAvail )
	{
		OnEditPaste();
		return TRUE;
	}
	else
		return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	CString x;
//	x.Format( "char: %i  \n", nChar );
//	TRACE( x );

	BOOL	bShift = GetKeyState( VK_SHIFT ) & 0x8000;
	BOOL	bCtrl = GetKeyState( VK_CONTROL ) & 0x8000;

	switch( nChar )
	{
	case 45:	//	Insert key.
//		if( bCtrl )
//			OnEditCopy();
//		else if( bShift )
//			OnEditPaste();
		break;
	case 46:	//	Delete key.
//		if( bShift )
//			OnEditCut();
//		else
//			pSequence->DeleteSelected( FALSE );
		if( !bShift )
			if( pSequence->DeleteSelected( FALSE ) )
				((CAnimEditorDoc*)GetDocument())->DocModified();
		break;
	}

	CScrollView::OnKeyUp(nChar, nRepCnt, nFlags);
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnSequenceHotspotnew() 
{
	pSequence->AddHSpot();	
}



//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::Initialize( CSequence* pSequence )
{
	this->pSequence = pSequence;
	//	Called immediately following construction.
	CalcSizeChanges();
}

//-----------------------------------------------------------------------------------------------------------------
CCelView* CSequenceView::GetCelView()
{
	//	Returns pointer to the CCelView.
	//	It stuff like this that makes me doubt all the benefits of MFC...
	CAnimEditorDoc* pDoc = pSequence->pOwnerDoc;
	POSITION posView = pDoc->GetFirstViewPosition();
	CView* pView;
	while( posView != NULL )
	{
		pView = pDoc->GetNextView( posView );
		if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CCelView" ) == 0 )
		{
			return (CCelView*)pView;
		}
	}
	ASSERT( FALSE );
	return NULL;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CSequenceView::SelectAtPoint( BOOL bClickCaused, UINT nFlags, CPoint& point )
{
	//	Used by OnLButtonDown() and by OnDragOver().
	//	In both cases, a sequence cel at a certain point is "selected".
	//	Functionality differs in that dragging over never results in a new drag operation being started.

	//	[ Much duplicated from CAnimEditorView::OnLButtonDown(). ]
	point += GetScrollPosition();

	//	Ask each cel if it's been hit.
	BOOL bFound = FALSE;
	//	[ Much code duplicated from OnDraw(). ]
	int	iCol = 0;
	POSITION posSeqCel = pSequence->lstSeqCels.GetHeadPosition();
	POSITION posNow;
	CSequenceCel* pSeqCel;
	while( posNow = posSeqCel )
	{
		pSeqCel = pSequence->lstSeqCels.GetNext( posSeqCel );
		if( pSeqCel->pCel->bPointInMe( CPoint( iCol * iColumnWidth + GAPFIRSTCOLUMN, 0 ), point ) )
		{
			bFound = TRUE;
			if( bClickCaused && pSeqCel->bSelected )
			{
//				//	Cel is already selected (and user has mousedowned on it). Begin dragdrop...
//				//	Create an OLE data source on the heap.
				COleDataSource* pData = new COleDataSource;		//	[Deleted by the framework.] xxx?
				pSequence->PutDataOnClipboard( pData );
				pSequence->ConvertSelectedToDragSelected();
				InvalidateRect( NULL );
				DROPEFFECT effect = pData->DoDragDrop( DROPEFFECT_COPY | DROPEFFECT_MOVE );
				if( effect == DROPEFFECT_MOVE )
				{
					//	User has attempted to CUT.
					if( pSequence->DeleteSelected( TRUE ) )		//	Examines bDragSelected states.
						pSequence->pOwnerDoc->DocModified();
				}
				pSequence->ClearDragSelected();
			}
			else
			{
				//	My CSequence handles selection states...
				pSequence->SequenceCelSelect( posNow, nFlags );
			}
			break;
		}
		iCol++;
	}
	if( bFound )
	{
		InvalidateRect( NULL );
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::CalcSizeChanges()
{
	//	Sets column width based on widest of current sequence cels,
	//	and sets ScrollSize.

	int iMaxWidth = 0;
	int	iMaxHeight = 0;

	if (!pSequence)
		return;

	POSITION posSeqCel = pSequence->lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posSeqCel )
	{
		pSeqCel = pSequence->lstSeqCels.GetNext( posSeqCel );
		iMaxWidth = max( iMaxWidth, pSeqCel->pCel->GetWidth() );
		iMaxHeight = max( iMaxHeight, pSeqCel->pCel->GetHeight() );
	}
	iColumnWidth	= iMaxWidth + GAPCOLUMN;
	iHeight			= iMaxHeight + GAPIMAGE + 5;						//	xxx Gap at bottom added here.
	iHeight			= max( iHeight, CSEQUENCEVIEW_DEFAULTHEIGHT );		//	Height never less than default minimum.

	SetScrollSizes( MM_TEXT, CSize( iColumnWidth * pSequence->lstSeqCels.GetCount() + GAPFIRSTCOLUMN, iHeight ) );
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CalcSizeChanges();	
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceView::OnSpecialHspotseqceltocatalog() 
{
	//	Copy the current primary hotspots assigned to select sequencecels back to the cels in the catalog.
	CString csMess = "";
	POSITION posSeqCel = pSequence->lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	while( posSeqCel )
	{
		pSeqCel = pSequence->lstSeqCels.GetNext( posSeqCel );
		if( pSeqCel->bSelected )
		{
			pSeqCel->pCel->dibImage.SetHotspotX( pSeqCel->ptPrimaryHotSpot().x );
			pSeqCel->pCel->dibImage.SetHotspotY( pSeqCel->ptPrimaryHotSpot().y );
			csMess += pSeqCel->pCel->csFileBMP;
			csMess += "\n";
			pSeqCel->pCel->bDIBHotspotSaved = FALSE;
		}
	}
	if( csMess == "" )
		AfxMessageBox( "No primary hotspots copied." );		//	Shouldn't happen.
	else
	{
		csMess = "Primary hotspots for the following images copied to catalog cels:\n\n" + csMess;
		AfxMessageBox( csMess );
	}
}
