// AnimEditorView.cpp : implementation of the CAnimEditorView class
//

#include "stdafx.h"
#include "AnimEditor.h"

#include "AnimEditorDoc.h"
#include "AnimEditorView.h"

#include "CCel.h"
#include "CCelView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAnimEditorView

IMPLEMENT_DYNCREATE( CAnimEditorView, CScrollView )

BEGIN_MESSAGE_MAP( CAnimEditorView, CScrollView )
	//{{AFX_MSG_MAP(CAnimEditorView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopyOrCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_WM_KEYUP()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_SEQUENCE_HOTSPOTNEW, OnUpdateSequenceHotspotnew)
	ON_COMMAND(ID_SPECIAL_HSPOTCATALOGSAVE, OnSpecialHspotcatalogsave)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopyOrCut)
	ON_COMMAND(ID_SPECIAL_HSPOTCATALOGTOSEQCELS, OnSpecialHspotcatalogtoseqcels)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorView construction/destruction

CAnimEditorView::CAnimEditorView()
{
	SetScrollSizes( MM_TEXT, CSize( 0, 0 ) );	//	xxx In OnInitialUpdate() instead?

	iWndColumns		= -1;		//	Note: OnSize() must be called before OnDraw().
	iWndRows		= -1;		//	These numbers will make it obvious in case you screw up.
	iWndColWidth	= -1;
	iWndRowHeight	= -1;

	//	Create the view's font.
	LOGFONT	lf;
	memset( &lf, 0, sizeof(LOGFONT) );
	lstrcpy( lf.lfFaceName, "Arial" );
	lf.lfHeight = 10;
	lf.lfWidth	= 5;
	VERIFY( fontSmall.CreateFontIndirect( &lf ) );

	hcurQuestion	= AfxGetApp()->LoadCursor( IDC_QUESTION );
	hcurNormal		= ::LoadCursor( NULL, IDC_ARROW );
}

CAnimEditorView::~CAnimEditorView()
{
}

BOOL CAnimEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorView drawing


BOOL CAnimEditorView::OnEraseBkgnd(CDC* pDC) 
{
	RECT rcWindow;
	GetClientRect( (LPRECT)&rcWindow );
	CBrush brBack;

	//	Do we have focus?
	CFrameWnd* pMainFrame = GetParentFrame();
	if( pMainFrame->GetActiveView() == this )
		brBack.CreateSolidBrush( theApp.colorWindow );
	else
		brBack.CreateSolidBrush( theApp.colorDialog );
	pDC->FillRect( &rcWindow, &brBack );

//	return CScrollView ::OnEraseBkgnd(pDC);
	return TRUE;
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnDraw(CDC* pDC)
{
	//	Note: Can't be allowed to run before size variables are set in OnSize.

	CAnimEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//	Do we have focus?
	CFrameWnd* pMainFrame = GetParentFrame();
	BOOL bShowSelected = ( pMainFrame->GetActiveView() == this );

	//	Select our font in.
	CFont* pfontOld = pDC->SelectObject( &fontSmall );

	//	Draw cels...
	int	iDrawPosition = 0;
	int iRow, iCol;
	POSITION posInList = pDoc->lstCels.GetHeadPosition();
	CCel* pCel;
	while( posInList )
	{
		pCel = pDoc->lstCels.GetNext( posInList );
		iRow = (int)( iDrawPosition / iWndColumns );
		iCol = iDrawPosition % iWndColumns;
		pCel->Draw( pDC, iCol * iWndColWidth + GAPFIRSTCOLUMN, iRow * iWndRowHeight, pCel->bSelected, pCel->bDragSelected );
		iDrawPosition++;
	}

	if( bShowSelected )
	{
		CRect rcThis;
		GetClientRect( &rcThis );
		rcThis.InflateRect( -1, -1 );
		CPoint ptScroll = GetScrollPosition();
		rcThis.OffsetRect( ptScroll.x, ptScroll.y );
		pDC->DrawEdge( &rcThis, EDGE_SUNKEN, BF_RECT );
	}

	//	Restore original font.
	pDC->SelectObject( pfontOld );
}

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorView printing

BOOL CAnimEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAnimEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAnimEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorView diagnostics

#ifdef _DEBUG
void CAnimEditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAnimEditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CAnimEditorDoc* CAnimEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimEditorDoc)));
	return (CAnimEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorView message handlers


//-----------------------------------------------------------------------------------------------------------------
int CAnimEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView ::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	//	Register drop target.
	if( m_dropTarget.Register( this ) )
		return 0;
	else
		return -1;

}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	//	Hack so that focus rect is drawn correctly.
	InvalidateRect( NULL );
	
	return CScrollView ::OnScroll(nScrollCode, nPos, bDoScroll);
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnSize(UINT nType, int cx, int cy) 
{
	//	Set required size of the view, and other attributes.
	//	Called whenever catalog elements change or view is resized by user.
	
	CAnimEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rcWindow;
	GetClientRect( &rcWindow );

	int iWndWidth = rcWindow.right + 1;

	//	Determine row and column spacing, using the largest of the images in the catalog.
	int iMaxWidth	= 0;
	int iMaxHeight	= 0;
	POSITION	posInList;
	CCel*		pCel;
	posInList = pDoc->lstCels.GetHeadPosition();
	while( posInList )
	{
		pCel = pDoc->lstCels.GetNext( posInList );
		iMaxWidth	= max( iMaxWidth, pCel->GetWidth() );
		iMaxHeight	= max( iMaxHeight, pCel->GetHeight() );
	}

	//if( iMaxWidth == 0 || iMaxHeight == 0 )
	//	return;	//xxx

	iWndColWidth	= iMaxWidth + GAPCOLUMN;
	iWndRowHeight	= iMaxHeight + GAPIMAGE;

	iWndColumns = (int)( ( iWndWidth - GAPFIRSTCOLUMN ) / iWndColWidth );
	if( !( iWndColumns > 0 ) )
		iWndColumns = 1;	//	Force at least one column.

	iWndRows = (int)( ( pDoc->lstCels.GetCount() + ( iWndColumns - 1 ) ) / iWndColumns );
	SetScrollSizes( MM_TEXT, CSize( iWndColWidth * iWndColumns + GAPFIRSTCOLUMN, iWndRowHeight * iWndRows ) );
	
	CScrollView::OnSize(nType, cx, cy);
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CAnimEditorDoc* pDoc = GetDocument();

	point += GetScrollPosition();

	//	Ask each cel if it's been hit.
	BOOL bFound = FALSE;
	//	[ Much code duplicated from OnDraw(). ]
	int	iDrawPosition = 0;
	int iRow, iCol;
	POSITION posNext = pDoc->lstCels.GetHeadPosition();
	POSITION posNow;
	CCel* pCel;
	while( posNow = posNext )
	{
		pCel = pDoc->lstCels.GetNext( posNext );
		iRow = (int)( iDrawPosition / iWndColumns );
		iCol = iDrawPosition % iWndColumns;
		if( pCel->bPointInMe( CPoint( iCol * iWndColWidth + GAPFIRSTCOLUMN, iRow * iWndRowHeight ), point ) )
		{
			bFound = TRUE;
			if( pCel->bSelected )
			{
				//	Cel is already selected. Begin dragdrop...
				//	Create an OLE data source on the heap.
				COleDataSource* pData = new COleDataSource;		//	[Deleted by the framework.]
				pDoc->PutDataOnClipboard( pData );
				pDoc->ConvertSelectedToDragSelected();
				InvalidateRect( NULL );
				DROPEFFECT effect = pData->DoDragDrop( DROPEFFECT_COPY | DROPEFFECT_MOVE );
				if( effect == DROPEFFECT_MOVE )
				{
					//	User has attempted to CUT. If there are sequence cels linked to cel(s), they won't be deleted.
					if( !pDoc->DeleteSelected( TRUE, FALSE ) )		//	Examines bDragSelected states.
					{
						//	[ Not all cels were deleted, because of sequence cel links. ]
						MessageBox( "Not all cels could be cut, because they are being used in sequences.",
									"Warning", MB_OK | MB_ICONINFORMATION );
					}
				}
				pDoc->ClearDragSelected();
			}
			else
			{
				//	The doc handles selection states...
				CAnimEditorDoc* pDoc = GetDocument();
				pDoc->CelSelect( posNow, nFlags );
			}
			break;
		}
		iDrawPosition++;
	}
	if( bFound )
	{
		InvalidateRect( NULL );
	}	

	CScrollView ::OnLButtonDown(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView ::OnLButtonUp(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	//	Set the cursor. (Brute force method, perhaps unkosher.)
	SetCursor( hcurQuestion );										//	Good until the mouse moves.
	SetClassLong( GetSafeHwnd(),		/* window handle */			//	Good after the mouse moves.
				GCL_HCURSOR,			/* change cursor */ 
				(LONG)hcurQuestion );	/* new cursor    */  

	//SetCursor( hcurQuestion );

	CScrollView ::OnRButtonDown(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	//	Set the cursor. (Brute force method, perhaps unkosher.)
	SetCursor( hcurNormal );										//	Good until the mouse moves.
	SetClassLong( GetSafeHwnd(),		/* window handle */			//	Good after the mouse moves.
				GCL_HCURSOR,			/* change cursor */ 
				(LONG)hcurNormal );		/* new cursor    */  

	CAnimEditorDoc* pDoc = GetDocument();

	point += GetScrollPosition();

	//	Ask each cel if it's been hit.
	BOOL bFound = FALSE;
	//	[ Much code duplicated from OnLButtonDown(). ]
	int	iDrawPosition = 0;
	int iRow, iCol;
	POSITION posNext = pDoc->lstCels.GetHeadPosition();
	POSITION posNow;
	CCel* pCel;
	while( posNow = posNext )
	{
		pCel = pDoc->lstCels.GetNext( posNext );
		iRow = (int)( iDrawPosition / iWndColumns );
		iCol = iDrawPosition % iWndColumns;
		if( pCel->bPointInMe( CPoint( iCol * iWndColWidth + GAPFIRSTCOLUMN, iRow * iWndRowHeight ), point ) )
		{
			pCel->bDragSelected = TRUE;
			InvalidateRect( NULL );
			CString csText = "Bitmap File: ";
			csText += pCel->csFileBMP;
			csText += "\n\n";
			CString csSize;
			csSize.Format( "Size: ( %i, %i ), Crop: ( %i, %i )\nDIB Hotspot: ( %i, %i ) %s\n\n", pCel->GetWidth(), pCel->GetHeight(), 
							pCel->xCrop, pCel->yCrop, pCel->dibImage.GetHotspotX(), pCel->dibImage.GetHotspotY(),
							pCel->bDIBHotspotSaved ? "(saved)" : "(NOT SAVED)" );
			csText += csSize;
			CString csUsage = pDoc->csUsedInWhatSequences( pCel );
			if( csUsage != "" )
			{
				csText += "This cel is used in the following sequences:\n\n";
				csUsage = csText + csUsage;				
			}
			else
			{
				csUsage = csText;
				csUsage += "This cel is not used in any sequences.";
			}
			MessageBox( csUsage, "Cel Usage", MB_OK | MB_ICONINFORMATION );
			pCel->bDragSelected = FALSE;
			break;
		}
		iDrawPosition++;
	}

	CScrollView ::OnRButtonUp(nFlags, point);
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CAnimEditorDoc* pDoc = GetDocument();

	//	Force myself to redraw, so focus rects are shown/unshown.
	InvalidateRect( NULL );

	if( bActivate )
	{
		//	Sync the CelView to NULL (no sequence).
		POSITION posView = pDoc->GetFirstViewPosition();
		CView* pView;
		while( posView != NULL )
		{
			pView = pDoc->GetNextView( posView );
			if( strcmp( pView->GetRuntimeClass()->m_lpszClassName, "CCelView" ) == 0 )
			{
				( (CCelView*)pView )->LinkToSequence( NULL );
				break;
			}
		}
	}

	CScrollView ::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	//	Called by OnInitialUpdate. Results in Serialize forcing a resize and repaint.
	PostMessage( WM_SIZE );
	InvalidateRect( NULL );	
}


//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnUpdateSequenceHotspotnew(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( FALSE );	
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	//	Enable menu choice based on availability of valid data in the clipboard.
	COleDataObject dataObj;
	dataObj.AttachClipboard();
	BOOL bAvail = ( dataObj.IsDataAvailable( theApp.clipFormatCel ) || 
					dataObj.IsDataAvailable( theApp.clipFormatSequenceCel ) );
	pCmdUI->Enable( bAvail );
//	pCmdUI->Enable( FALSE );	
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnUpdateEditCopyOrCut(CCmdUI* pCmdUI) 
{
	//	Enable menu choice based on availability of selected cels.
	CAnimEditorDoc* pDoc = GetDocument();
	pCmdUI->Enable( pDoc->iCountSelected() > 0 );
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnEditCopy() 
{
	CAnimEditorDoc* pDoc = GetDocument();

	//	Create an OLE data source on the heap
	COleDataSource* pData = new COleDataSource;		//	[Deleted by the framework.]
	pDoc->PutDataOnClipboard( pData );
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnEditCut() 
{
	CAnimEditorDoc* pDoc = GetDocument();

	//	The doc asks the user to confirm deletion if the cel is used in any sequences.
	if( pDoc->VerifyDeleteSelected() )
	{
		//	Create an OLE data source on the heap
		COleDataSource* pData = new COleDataSource;		//	[Deleted by the framework.]
		pDoc->PutDataOnClipboard( pData );
		pDoc->DeleteSelected( FALSE, TRUE );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnEditPaste() 
{
	CAnimEditorDoc* pDoc = GetDocument();
	pDoc->GetDataFromClipboard();
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CAnimEditorDoc* pDoc = GetDocument();

//	CString x;
//	x.Format( "char: %i  \n", nChar );
//	TRACE( x );

	BOOL	bShift = GetKeyState( VK_SHIFT ) & 0x8000;
	BOOL	bCtrl = GetKeyState( VK_CONTROL ) & 0x8000;

	switch( nChar )
	{
	case 45:	//	Insert key.
		if( bCtrl )
			OnEditCopy();
		else if( bShift )
			OnEditPaste();
		break;
	case 46:	//	Delete key.
		if( bShift )
			OnEditCut();
		else if( pDoc->VerifyDeleteSelected() )
			pDoc->DeleteSelected( FALSE, TRUE );
		break;
	}

	CScrollView ::OnKeyUp(nChar, nRepCnt, nFlags);
}

//-----------------------------------------------------------------------------------------------------------------
DROPEFFECT CAnimEditorView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
//	return CScrollView ::OnDragOver(pDataObject, dwKeyState, point);
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

	return effect;
}

//-----------------------------------------------------------------------------------------------------------------
BOOL CAnimEditorView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
//	return CScrollView ::OnDrop(pDataObject, dropEffect, point);
	COleDataObject dataObj;
	dataObj.AttachClipboard();
	BOOL bAvail = ( dataObj.IsDataAvailable( theApp.clipFormatCel ) || 
					dataObj.IsDataAvailable( theApp.clipFormatSequenceCel ) );
	if( bAvail )
	{
		CAnimEditorDoc* pDoc = GetDocument();
		return pDoc->GetDataFromClipboard();
		//	[ Returns FALSE if operation was requested on the same view from which the drag started, so that
		//	  a CUT operation won't go through. ]
	}
	else
		return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnSpecialHspotcatalogsave() 
{
	//	Save the primary hotspot stored in selected cels' DIBitmaps back out to their BMP files.
	CAnimEditorDoc* pDoc = GetDocument();
	CString		csResults = "";
	POSITION	posInList;
	CCel*		pCel;
	posInList = pDoc->lstCels.GetHeadPosition();
	while( posInList )
	{
		pCel = pDoc->lstCels.GetNext( posInList );
		if( pCel->bSelected )
		{
			csResults += pDoc->csFolder;
			csResults += pCel->csFileBMP;
			csResults += ": ";
			if( pCel->dibImage.SaveHotspot( pDoc->csFolder + pCel->csFileBMP ) )
			{
				csResults += "Hotspot saved successfully.\n";
				pCel->bDIBHotspotSaved = TRUE;
			}
			else
				csResults += "Save failed.\n";
		}
	}
	if( csResults == "" )
		AfxMessageBox( "No hotspots saved." );		//	Shouldn't happen.
	else
	{
		csResults = "Hotspot save results:\n\n" + csResults;
		AfxMessageBox( csResults );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CAnimEditorView::OnSpecialHspotcatalogtoseqcels() 
{
	//	Copy the primary hotspot stored in selected cels' DIBitmaps to all their sequencecel instances.
	//	We are copying for possibly multiple cels in catalog.
	//	Each cel can appear in multiple sequences.
	//	Each cel can appear multiple times within a given sequence.
	CAnimEditorDoc* pDoc = GetDocument();
	CString		csResults = "";
	POSITION	posInList;
	CCel*		pCel;
	posInList = pDoc->lstCels.GetHeadPosition();
	while( posInList )
	{
		pCel = pDoc->lstCels.GetNext( posInList );
		if( pCel->bSelected )
		{
			CString csAdd;
			csAdd.Format( "Primary hotspot for %s copied from catalog to cel instances in %i sequences.\n", pCel->csFileBMP, pCel->lstSeqs.GetCount() );
			csResults += csAdd;
			pCel->CopyCatalogHotspotToSequences();
		}
	}
	if( csResults == "" )
		AfxMessageBox( "No instances of selected catalog cels found to copy to." );
	else
	{
		csResults = "Hotspot catalog to sequence copy results:\n\n" + csResults;
		AfxMessageBox( csResults );
	}
}
