// MapEditorView.cpp : implementation of the CMapEditorView class
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapEditorDoc.h"
#include "MapEditorView.h"
#include "MapFrame.h"
#include "NewMapDlg.h"
#include "MapUpdate.h"
#include "TileSetView.h"
#include "TileLayer.h"
#include "ObjectSetView.h"
#include "ScenarioView.h"
#include "scriptsdlg.h"
#include "selectdlg.h"
#include "mapoverview.h"
#include "mainfrm.h"
#include "expanddlg.h"
#include "rotatedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef MM_SCALETOFIT
#define MM_SCALETOFIT       (-1)
#endif

#ifdef x_DEBUG
#include <time.h>
static time_t g_startTime;
#define START_TIME() time(&g_startTime);
inline void ELAPSED_TIME(char *msg) 
{
	time_t end; 
	time(&end); 
	double elapsed = difftime(end,g_startTime); 
    TRACE("%s time =  %6.0f\n",msg,elapsed);
}
#else
#define START_TIME()
#define ELAPSED_TIME(msg)
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapEditorView

IMPLEMENT_DYNCREATE(CMapEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CMapEditorView, CScrollView)
	//{{AFX_MSG_MAP(CMapEditorView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_SELECT, OnEditSelect)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT, OnUpdateEditSelect)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CANCEL_OP, OnCancelOp)
	ON_WM_CANCELMODE()
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLONE, OnUpdateEditClone)
	ON_COMMAND(ID_EDIT_CLONE, OnEditClone)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_UPDATE_COMMAND_UI(ID_VIEW_REPOSITION, OnUpdateViewReposition)
	ON_COMMAND(ID_VIEW_REPOSITION, OnViewReposition)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_SCRIPTS, OnEditScripts)
	ON_COMMAND(ID_EDIT_SELECTDLG, OnSelectArea)
	ON_COMMAND(ID_EDIT_VIEWABLE, OnEditViewable)
	ON_COMMAND(ID_EDIT_EXPAND, OnEditExpand)
	ON_COMMAND(ID_EDIT_ROTATE, OnEditRotate)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditorView construction/destruction

CMapEditorView::CMapEditorView()
{
	m_mode = none;
	m_bActive = FALSE;
	m_bUseLast = TRUE;
}

CMapEditorView::~CMapEditorView()
{
}

BOOL CMapEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditorView drawing
void CMapEditorView::OnDraw(CDC* pDC)
{
	CMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rect,clip;

	// only update the region that needs repainting
	pDC->GetClipBox(&clip);
	clip.InflateRect(1,1); // avoid severe round-off errors due to scaling

	if (!pDoc->GetBoundingRect(clip, rect))
		return;

	CSize size = pDoc->GetSize();
	BOOL bWaitCursor ;

	if (rect.Width() == size.cx && rect.Height() == size.cy)
	{
		BeginWaitCursor();
		bWaitCursor = TRUE;
	}
    else
		bWaitCursor = FALSE;

	//Note: CScrollView::OnPaint() will have already adjusted the
	//viewpoint origin before calling OnDraw(), to reflect the
	//currently scrolled position.

    // try to do the drawing offscreen because it's faster
	// and avoids preview tearing/flickering when painting with
	// transparency.
    HDC hClientDC = pDC->GetSafeHdc();
	HPALETTE hPalette = pDoc->GetHPalette();
	HPALETTE hOldPalette = SelectPalette(hClientDC, hPalette, !m_bActive);
	int rw = rect.Width();
	int rh = rect.Height();
	BOOL bDrawn = FALSE;

	CTileSet *pTileSet = GetTileSet();
	CDIB *pDib = pTileSet->GetDIB();
	ASSERT(pDib != NULL);

	if (g_bUseOffScreenDibs && pDib->IsSimpleDib())
	{
		START_TIME();
		CSize wsize = rect.Size();
		CSize vsize = wsize;

		if (m_nMapMode == MM_SCALETOFIT)
		{
			POINT pt; 
			pt.x = wsize.cx; 
			pt.y = wsize.cy;
			VERIFY(LPtoDP(hClientDC,&pt,1));
			vsize.cx = pt.x+1;
			vsize.cy = pt.y+1;
		}
		CDibDoc *pOffScreenDib = pTileSet->CreateCompatibleDIB(vsize.cx, vsize.cy);
		if (pOffScreenDib)
		{
			CDIB *pDst = pOffScreenDib->GetDIB();
			HDC hdc = pDst->CreateHDC(hClientDC);
			if (hdc)
			{
				HPALETTE hOldPalette = SelectPalette(hdc, hPalette, !m_bActive);
				UINT nIndex = GetNearestPaletteIndex(hPalette,pDoc->m_rgbBackground);			
#if 1
				SetMapMode(hdc, GetMapMode(hClientDC));
				if (m_nMapMode == MM_SCALETOFIT)
				{
					SetWindowExtEx(hdc, m_totalLog.cx, m_totalLog.cy, NULL);
					SetViewportExtEx(hdc, m_totalDev.cx, m_totalDev.cy, NULL);
				}
#endif
				pDst->Fill(0,0,vsize.cx,vsize.cy,nIndex);
				pDoc->Draw(hdc, rect, pDst);

				// copy the off-screen bitmap on screen to avoid tearing
				bDrawn = BitBlt(hClientDC, rect.left, rect.top, rw, rh, 
								hdc, 0, 0, SRCCOPY);

				if (!bDrawn)
					TRACE0("Error copying offscreen dib to view\n");

				SelectPalette(hdc, hOldPalette, TRUE);
				pDst->DeleteHDC();
			}
			else
				TRACE0("Can't create offscreen hdc\n");

			delete pOffScreenDib;
		}
		else
			TRACE0("Can't create offscreen dib\n");
		ELAPSED_TIME("offscreen dib");
	}
	else
	{
		START_TIME()
		// Draw into and off-screen bitmap compatible with the display
		//
		// Note: we use logical width/height to avoid of MFC in StretchBlt() bug
		// we draw off-screen at full-size then scale down using final BitBlt.
		HBITMAP hBitmap = CreateCompatibleBitmap(hClientDC, rw, rh);
		if (hBitmap)
		{
			// paint the map into the offscreen area
			HDC hdc = CreateCompatibleDC(hClientDC);
			if (hdc)
			{
				HPALETTE hOldPalette = SelectPalette(hdc, hPalette, !m_bActive);
				HBITMAP hOldBitmap = SelectHBitmap(hdc, hBitmap);
				HBRUSH hBrush = CreateSolidBrush(pDoc->m_rgbBackground);
				if (hBrush)
				{
					CRect fullRect(0,0,rw,rh);
					FillRect(hdc,&fullRect,hBrush);
					DeleteObject(hBrush);
				}
				else
					BitBlt(hdc, 0, 0, rw, rh, hdc, 0, 0, WHITENESS);
				pDoc->Draw(hdc, rect, NULL, hBitmap);

				// blt the off-screen bitmap on screen to avoid tearing
				bDrawn = BitBlt(hClientDC, rect.left, rect.top, rw, rh, 
					hdc, 0, 0,SRCCOPY);

				if (!bDrawn)
					TRACE0("Error copying offscreen bitmap to view\n");

				SelectHBitmap(hdc, hOldBitmap);
				SelectPalette(hdc, hOldPalette, TRUE);
				DeleteDC(hdc);
			}
			else
				TRACE0("Can't create offscreen hdc\n");
			DeleteObject(hBitmap);
		}
		else
			TRACE0("Can't create offscreen bitmap\n");
        ELAPSED_TIME("offscreen");
	}

	// worse comes to worse, just draw on screen
	if (!bDrawn)
	{
		START_TIME();
		pDoc->Draw(hClientDC,rect,NULL);
		ELAPSED_TIME("onscreen");
	}
	SelectPalette(hClientDC, hOldPalette, TRUE);
	if (bWaitCursor) EndWaitCursor();
}


// Select and realize our palette.
BOOL CMapEditorView::RealizePalette(BOOL bForceBkgnd)
{
    // We are going active, so realize our palette.
	CPalette *pPal = GetDocument()->GetPalette();
    if (pPal == NULL) 
		return FALSE;

	CDC *pDC = GetDC();
    CPalette *poldpal = pDC->SelectPalette(pPal, bForceBkgnd);
    UINT u = pDC->RealizePalette();

    // If any colors have changed or we are in the
    // background, repaint the lot.
    if (u || bForceBkgnd) 
	{
        Invalidate();
    }
    pDC->SelectPalette(poldpal, TRUE);
    ReleaseDC(pDC);
    return (BOOL) u; // TRUE if some colors changed
}

void CMapEditorView::OnPaletteChanged(CWnd* pFocusWnd)
{
    // See if the change was caused by us and ignore it if not.
    if ((pFocusWnd == this) || IsChild(pFocusWnd))
		return;

    RealizePalette(TRUE); // Realize in background.
}

BOOL CMapEditorView::OnQueryNewPalette()
{
	return RealizePalette(FALSE); // Realize in foreground
}

void CMapEditorView::OnActivateView(BOOL bActivate, CView* pAcView, CView* pDeacView)
{
    if (bActivate) 
	{
	 // TRACE("%s Activate %lx\n",GetDocument()->GetTitle(), this);
		GetParentFrame()->OnUpdateFrameTitle(TRUE);
		OnQueryNewPalette();
    }
	CScrollView::OnActivateView(bActivate, pAcView, pDeacView);
	m_bActive = bActivate;
}
/////////////////////////////////////////////////////////////////////////////
// CMapEditorView printing

BOOL CMapEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMapEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMapEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditorView diagnostics

#ifdef _DEBUG
void CMapEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMapEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapEditorDoc* CMapEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditorDoc)));
	return (CMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/* METHOD
**    CMapEditorView::OnUpdateSizes
**
** DESCRIPTION
**    This method should be called whenever the map's document size
**    has changed, the tile size used by the map has changed, or
**    the view size has changed
**
**    Adjusts the scroll bars:
**          -- to reflect the current document size 
**          -- to allow arrows to scroll view by exactly one tile
**          -- to allow clicking in scrollbar to scroll view by
**             one full page of tiles keeping the last row/column
**             of previous page in view.
*/
void CMapEditorView::OnUpdateSizes()
{
	CTileSet *pTileSet = GetTileSet();
	if (pTileSet) // might be called before tileSet is attached.
	{
		CSize tileSize(pTileSet->m_iTileWidth, pTileSet->m_iTileHeight);
		CRect rect;
		GetClientRect(&rect);
		CSize pageSize(rect.Width()-tileSize.cx, rect.Height()-tileSize.cy);
		SetScrollSizes(MM_TEXT, GetDocument()->GetSize(), pageSize, tileSize);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditorView message handlers

void CMapEditorView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	OnUpdateSizes();

    // Make sure tool pane is installed 
	// TBD: should this be in the map class? 
	CMapEditorDoc *pDoc = GetDocument();
    CMapLayer *pLayer = pDoc->GetActiveLayer();
    if (pLayer) pLayer->Activate();
}

void CMapEditorView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMapEditorDoc *pDoc = GetDocument();
	CTileSet *pTileSet = GetTileSet();

	GetParentFrame()->SetActiveView(this,TRUE);
	if (m_mode == viewReposition)
	{
		m_anchor = point;
		SetCapture();
		return;
	}

    CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	int		iColumn = point.x / pTileSet->m_iTileWidth;
	int		iRow	= point.y / pTileSet->m_iTileHeight;

	if( iRow >= pDoc->m_iMapHeight || iColumn >= pDoc->m_iMapWidth )
	    return;

	switch(m_mode)
	{
		case selectArea:
			// TBD: don't tile align selection if active layer is not
			// constrained to tile boundaries.
			m_focusRect.left = iColumn * pTileSet->m_iTileWidth;
			m_focusRect.top = iRow * pTileSet->m_iTileHeight;
			m_focusRect.right = m_focusRect.left;
			m_focusRect.bottom = m_focusRect.top;
			m_anchor = m_focusRect.TopLeft();
			m_bSelect = FALSE;
			SetCapture();
			dc.DrawFocusRect(&m_focusRect);
		case selectClone:
		case cloneItem:
			SetClone(iRow, iColumn);
			break;
		default:
			if (nFlags & MK_CONTROL)
				m_mode = pDoc->ToggleItem(point,iRow,iColumn,m_bSelect);
			else
				m_mode = pDoc->GetItem(point,iRow,iColumn);
			if (pDoc->GetActiveLayer()->IsKindOf(RUNTIME_CLASS(CTileLayer)))
			{
				BOOL bSel=FALSE;
				CTileLayer *pLayer = (CTileLayer*)pDoc->GetActiveLayer();
				pLayer->GetTile(iRow, iColumn, &bSel);
				if (TRUE == bSel)
				{
					pLayer->m_movelast.x = -1;
					m_mode = moveItem;
				}
			}
			if (m_mode != none) 
				SetCapture();
	}
}


void CMapEditorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CMapEditorDoc *pDoc = GetDocument();
	CTileSet *pTileSet = GetTileSet();
	
	GetParentFrame()->SetActiveView(this,TRUE);
	if (m_mode == viewReposition)
	{
		m_anchor = point;
		SetCapture();
		return;
	}

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	int iRow, iColumn;
	if (!pDoc->GetRowColumn(point,iRow, iColumn))
		return;

	switch(m_mode)
	{
		case selectArea:
			m_focusRect.left = iColumn * pTileSet->m_iTileWidth;
			m_focusRect.top = iRow * pTileSet->m_iTileHeight;
			m_focusRect.right = m_focusRect.left;
			m_focusRect.bottom = m_focusRect.top;
			m_anchor = m_focusRect.TopLeft();
			m_bSelect = TRUE;
			SetCapture();
			dc.DrawFocusRect(&m_focusRect);
			m_bUseLast = FALSE;
			m_lastold = GetDocument()->GetActiveLayer()->m_last;
			GetDocument()->GetActiveLayer()->m_last.x = iColumn;
			GetDocument()->GetActiveLayer()->m_last.y = iRow;
			break;
		case cloneItem:
			DoClone(point,iRow,iColumn);
			break;
		case selectClone:
			SetClone(iRow, iColumn);
			break;
		default:
			if (nFlags & MK_CONTROL)
			{
				m_mode = pDoc->ToggleItem(point,iRow,iColumn,m_bSelect);
			}
			else 
			{
				pDoc->BeginEdit();
				m_mode = pDoc->PlaceItem(point, iRow, iColumn);
			}
			if (m_mode != none) 
				SetCapture();

	}
}


void CMapEditorView::OnButtonUp(UINT nFlags, CPoint point)
{
	switch(m_mode)
	{
		case selectArea:
			if (GetCapture()==this)
			{
				m_mode = selectAreaDone;
				OnMouseMove(nFlags, point);
				ReleaseCapture();
				GetDocument()->Select(m_focusRect, m_bSelect);

				if (!(nFlags & MK_CONTROL))
				{
					// turn off the selection process
					m_mode = none;
					SetViewCursor(IDC_ARROW);
				}
				else
					m_mode = selectArea;
			}
			break;
		case cloneItem:
		case selectClone:
			OnMouseMove(nFlags,point);
			break;
		default:
			OnMouseMove(nFlags,point); // fall thru
			if (GetCapture() == this) ReleaseCapture();
			SetViewCursor(IDC_ARROW);
			m_mode = none;
			break;
	}
	GetDocument()->EndEdit(); // must be safe to call even if no matching BeginEdit()
}

void CMapEditorView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	OnButtonUp(nFlags, point);
}

void CMapEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	OnButtonUp(nFlags, point);
}

void CMapEditorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CMapEditorDoc *pDoc = GetDocument();
	CTileSet *pTileSet = GetTileSet();
    CPoint viewPoint = point;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);	
	
	int iRow, iColumn;

	if (GetCapture() == this)
	{
#ifdef _DEBUG_CAPTURE
		ShowStatus("Capturing");
#endif
		if (m_mode == selectArea || m_mode == selectAreaDone)
		{
			// round up to nearest tile
			iColumn = (point.x + pTileSet->m_iTileWidth-1)/ pTileSet->m_iTileWidth;
			iRow	= (point.y + pTileSet->m_iTileHeight-1)/ pTileSet->m_iTileHeight;
			if (iColumn > pDoc->m_iMapWidth) 
				iColumn = pDoc->m_iMapWidth;
			if (iRow > pDoc->m_iMapHeight) 
				iRow = pDoc->m_iMapHeight;
			dc.DrawFocusRect(&m_focusRect); // erase the old rect

			CPoint newpt;
			newpt.x = iColumn * pTileSet->m_iTileWidth;
			newpt.y = iRow * pTileSet->m_iTileHeight;
			m_focusRect = CRect(m_anchor,newpt);
			m_focusRect.NormalizeRect();
			if (m_mode == selectArea)
				dc.DrawFocusRect(&m_focusRect); // draw the new rect
			if (!m_bUseLast)
			{
				if (selectAreaDone == m_mode)
				{
					m_bUseLast = TRUE;
					GetDocument()->GetActiveLayer()->m_last = m_lastold;
				}
				else
				{
					GetDocument()->GetActiveLayer()->m_last.x = (m_focusRect.right - m_focusRect.left) / pTileSet->m_iTileWidth;
					GetDocument()->GetActiveLayer()->m_last.y = (m_focusRect.bottom - m_focusRect.top) / pTileSet->m_iTileHeight;
				}
			}
			return;
		}

		CRect clientRect;
		GetClientRect(&clientRect);
		if (m_mode != moveItem && !clientRect.PtInRect(viewPoint))
		{
			m_mode = none;
			SetViewCursor(IDC_ARROW);
			ErasePreview();
			ReleaseCapture();
			return;
		}
		if (m_mode == viewReposition)
		{
			if (m_nMapMode != MM_SCALETOFIT)
			{

				 CPoint pos = GetScrollPosition() - viewPoint + m_anchor;
			     ScrollToPosition(pos);
				 m_anchor = viewPoint;
			}
			else
			{
				CMapFrame *pFrame = STATIC_DOWNCAST(CMapFrame,GetParentFrame());
				CMapEditorView *pView = pFrame->GetMapView();
				pView->ScrollToPosition(point);
			}
			return;
		}
	}
#ifdef _DEBUG_CAPTURE
	else
		ShowStatus(NULL);
#endif

	if (!pDoc->GetRowColumn(point,iRow,iColumn))
		return;

	switch(m_mode)
	{ 
	    case moveItem:
			pDoc->MoveItem(point,iRow,iColumn);
			break;
		case selectItem:
			pDoc->SelectItem(point,iRow,iColumn,m_bSelect);
			break;
		case selectClone:
			break;
		case cloneItem: 
			if (nFlags & MK_LBUTTON)
				DoClone(point,iRow,iColumn);
			break;
		case placeItem:
			if (nFlags & MK_LBUTTON)
				pDoc->PlaceItem(point,iRow,iColumn);
			break;
		case none:
			if (pDoc->PreviewItem(point,iRow,iColumn))
				SetCapture();
	}
}


void CMapEditorView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint & MEV_UPDATE_SIZE)
       OnUpdateSizes();

	if (lHint & MEV_UPDATE_PALETTE)
	{
	    RealizePalette(!m_bActive); 
		lHint &= ~MEV_UPDATE_PALETTE;
	}

	if (lHint & MEV_UPDATE_LAYER)
	{
		// Note: don't do any refresh; ]
		// the map will tell us what to refresh when it is ready.
		if (m_bActive)
		{
			GetDocument()->InitFrameLayersList();  // TBD: this is a bit heavy handed
		}
		if (m_mode != none) 
			OnCancelOp();
		return;
	}

	if (lHint & MEV_UPDATE_TRANSPARENT)
	{
		if (!GetDocument()->UsingTransparency())
			return;
	}

	if (lHint & (MEV_UPDATE_ATTRIBUTE_VALUE|MEV_UPDATE_ATTRIBUTE_FORMAT))
		return; // nothing to do

	if (m_totalDev.cx <= 0 || m_totalDev.cy <= 0)
		return; // in case we're using SetScaleToFit()...

	if (lHint & MEV_UPDATE_POSITION)
	{
		if (m_nMapMode != MM_SCALETOFIT) 
		{
			// scroll the view to show the given position
			ASSERT(pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CMapUpdate)));
			CMapUpdate *pUpdate = (CMapUpdate *)pHint;
			CRect rect = pUpdate->m_rect;
			// TBD: check to see if point is already visible
			ScrollToPosition(rect.TopLeft());
			// TBD: only update necessary area
			Invalidate();
		}
		return;
	}

	if (lHint & MEV_UPDATE_PREVIEW)
	{
		ASSERT(pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CMapUpdate)));
		// just fall thru to case below
    }

	if (pHint != NULL)
	{
		if (pHint->IsKindOf(RUNTIME_CLASS(CMapUpdate)))
		{
			CMapUpdate *pUpdate = (CMapUpdate *)pHint;
			CRect rect = pUpdate->m_rect;

			CClientDC dc(this);
			OnPrepareDC(&dc);
			dc.LPtoDP(&rect);

			if (m_nMapMode == MM_SCALETOFIT) 
			{
				// to avoid round-off errors
				rect.InflateRect(1,1);
			}

			InvalidateRect(&rect, FALSE);
			return;
		} 
	}
	CScrollView::OnUpdate(pSender, lHint, pHint);
}

void CMapEditorView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	OnUpdateSizes();
}


// Note: this method is here rather than in CMapEditorDoc because
// we want to update the frame that contains the map.  By rights 
// we should update all the frames that contain the map but for
// now we ASSUME that the map will only be opened in one frame
// at a time.
void CMapEditorView::OnEditProperties() 
{
	CMapEditorDoc *pDoc = GetDocument();
	CTileSet *pTileSet = GetTileSet();
	CObjectSet *pObjectSet = pDoc->GetObjectSet();
	CScenarioSet *pScenarioSet = pDoc->GetScenarioSet();
	CString pszPath = pTileSet->GetPathName();
	CString pszObjectPath = pObjectSet ? pObjectSet->GetPathName() : _T("");
	CString pszScenarioPath = pScenarioSet ? pScenarioSet->GetPathName() : _T("");
	BOOL bModified = FALSE;
	CNewMapDlg dlg(this);

    dlg.m_pszTileSet = pszPath;
	dlg.m_pszObjectSet = pszObjectPath;
	dlg.m_pszScenarioSet = pszScenarioPath;
	dlg.m_iNewWidth = pDoc->m_iMapWidth;
	dlg.m_iNewHeight = pDoc->m_iMapHeight;
    dlg.m_rgbColor = pDoc->m_rgbBackground;
	dlg.m_pszDescription = pDoc->m_pszDescription;

	if (dlg.DoModal() == IDOK)
	{
		CMapFrame *pFrame = STATIC_DOWNCAST(CMapFrame, GetParentFrame());
		if (pszPath.CompareNoCase(dlg.m_pszTileSet))
		{
			if (pDoc->UseTileSet(dlg.m_pszTileSet))
			{
				pFrame->ReInstallToolPane(RUNTIME_CLASS(CTileSetView));
				if (pTileSet = pDoc->GetTileSet())
					pTileSet->UpdateAllViews(NULL);
				bModified = TRUE;
			}
		}

		if (pszObjectPath.CompareNoCase(dlg.m_pszObjectSet))
		{
			if (pDoc->UseObjectSet(dlg.m_pszObjectSet))
			{
				pFrame->ReInstallToolPane(RUNTIME_CLASS(CObjectSetView));
				if (pObjectSet = pDoc->GetObjectSet()) 
					pObjectSet->UpdateAllViews(NULL);
				bModified = TRUE;
			}
		}

		if (pszScenarioPath.CompareNoCase(dlg.m_pszScenarioSet))
		{
			if (pDoc->UseScenarioSet(dlg.m_pszScenarioSet))
			{
				pFrame->ReInstallToolPane(RUNTIME_CLASS(CScenarioView));
				if (pScenarioSet = pDoc->GetScenarioSet())
					pScenarioSet->UpdateAllViews(NULL);	
				bModified = TRUE;
			}
		}

		if (dlg.m_iNewWidth != pDoc->m_iMapWidth || dlg.m_iNewHeight != pDoc->m_iMapHeight)
		{
			if (dlg.m_iNewWidth < pDoc->m_iMapWidth ||
				dlg.m_iNewHeight < pDoc->m_iMapHeight)
			{
				if (AfxMessageBox(IDS_RESIZE_MAY_LOSE_DATA, MB_ICONQUESTION|MB_YESNO) != IDYES)
				   return; // user aborted the resize
			}
			if (!pDoc->ResizeMap(dlg.m_iNewWidth, dlg.m_iNewHeight))
               AfxMessageBox(IDS_CANT_RESIZE_MAP);
			else
			   bModified = TRUE;
		}
		if (dlg.m_rgbColor != pDoc->m_rgbBackground)
		{
			pDoc->m_rgbBackground = dlg.m_rgbColor;
		    bModified = TRUE;
        }
		if (pDoc->m_pszDescription.Compare(dlg.m_pszDescription))
		{
			pDoc->m_pszDescription = dlg.m_pszDescription;
			pDoc->SetModifiedFlag();
			// don't update bModified because we don't need to redraw
		}
		if (bModified)
		{
			pDoc->UpdateAllViews(NULL,MEV_UPDATE_SIZE|MEV_UPDATE_PALETTE);
			pDoc->SetModifiedFlag();
		}
	}
	
}

///////////////////////////////////////////////////////////////////////////////

void CMapEditorView::OnEditSelect() 
{
	CMainFrame *pMainFrame = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (pMainFrame)
	{
		CMapFrame *pFrame = DYNAMIC_DOWNCAST(CMapFrame,pMainFrame->GetActiveFrame());
		if (pFrame)
		{
			CView *pView = pFrame->GetActiveView();
			if (pView->IsKindOf(RUNTIME_CLASS(CMapOverview)))
			{
				((CMapOverview*)pView)->DoSelect();
			}
			else
			{
				DoSelect();
			}
			return;
		}
	}
}

void CMapEditorView::DoSelect()
{
	if (m_mode == selectArea)
	{
		// abort the current selection
		ReleaseCapture();
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DrawFocusRect(&m_focusRect);
		InvalidateRect(&m_focusRect);
		m_focusRect = CRect(0,0,0,0);

		// turn off the selection process
		m_mode = none;
		SetViewCursor(IDC_ARROW);
	}
	else
	{
		m_mode = selectArea;
		GetDocument()->SelectNone();
		GetTileSet()->SetCurrentItem(TSV_TILES,-1); // TBD: GetDocuemt()->ClearCurrentItem()
		ErasePreview();
		SetViewCursor(IDC_CROSS);
	}
}

void CMapEditorView::OnUpdateEditSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_mode == selectArea);
}

// gets called when the user hits escape
void CMapEditorView::OnCancelOp() 
{
	switch(m_mode)
	{
		case selectArea:
			OnEditSelect();
			break;
		case selectClone:
		case cloneItem:
			OnEditClone();
			break;
		case viewReposition:
			OnViewReposition();
			break;
		default:
			m_mode = none;
			break;
    } 
}

void CMapEditorView::ErasePreview()
{
	GetDocument()->ClearPreviewRect();
}

// gets called when dialog is put up.
void CMapEditorView::OnCancelMode() 
{
	CScrollView::OnCancelMode(); // release capture
	ErasePreview();
}


void CMapEditorView::OnUpdateEditClone(CCmdUI* pCmdUI) 
{
	
	CMapLayer *pLayer = GetDocument()->GetActiveLayer();
	BOOL enabled = pLayer && pLayer->IsKindOf(RUNTIME_CLASS(CTileLayer));
	pCmdUI->Enable(enabled);
	pCmdUI->SetCheck(m_mode == cloneItem || m_mode == selectClone);
}

void CMapEditorView::SetViewCursor(LPCSTR lpszCursorName)
{
	HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(lpszCursorName);
	SetCursor(hCursor);
	SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG) hCursor);
}

void CMapEditorView::OnEditClone() 
{
	if (m_mode == cloneItem || m_mode == selectClone)
	{
		m_mode = none;
		SetViewCursor(IDC_ARROW);
	}
	else
	{
		m_mode = selectClone;
		ErasePreview();
		SetViewCursor(IDC_CROSS);
	}
}

// set the anchor (first point) for the cloning operation
void CMapEditorView::SetClone(int iRow, int iColumn)
{
	SetViewCursor(IDC_ARROW);
	m_anchor.x = iColumn;
	m_anchor.y = iRow;
	m_cloneLast.x = m_cloneLast.y = -1;
	m_mode = cloneItem;

	CMapEditorDoc *pDoc = GetDocument();
	pDoc->SelectNone();
	pDoc->BeginEdit();
	pDoc->SelectItem(m_anchor, iRow, iColumn);
	m_cloneHi = m_anchor;
	
}

// place cloned tiles 
void CMapEditorView::DoClone(CPoint point, int iRow, int iColumn)
{
    CPoint diff;
	if (m_cloneLast.x >= 0 && m_cloneLast.y >= 0)
	{
		diff.x = iColumn - m_cloneLast.x;
		diff.y = iRow - m_cloneLast.y;
	}
	else
	{
		diff.x = 0;
		diff.y = 0;
		m_cloneLast.x = iColumn;
		m_cloneLast.y = iRow;
	}	
	CMapEditorDoc *pDoc = GetDocument();

	int y = m_anchor.y + diff.y;
	int x = m_anchor.x + diff.x;

	if (m_cloneHi.x >= 0 && m_cloneHi.y >= 0)
	{
	   // deselect old source tile
	   pDoc->SelectItem(point, m_cloneHi.y, m_cloneHi.x, FALSE);
    }

	if (x >= 0 && y >= 0 && x < pDoc->m_iMapWidth && y < pDoc->m_iMapHeight)
	{
		// select new source tile
		pDoc->SelectItem(point,y,x,TRUE); 
		m_cloneHi.x = x;	
		m_cloneHi.y = y; 

		// clone the tile data
		pDoc->GetItem(point,y,x); 
		pDoc->PlaceItem(point, iRow, iColumn); 
	}
    else
		m_cloneHi.x = m_cloneHi.y = -1; 
}


void CMapEditorView::OnUpdateViewReposition(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_mode == viewReposition);
}

void CMapEditorView::OnViewReposition() 
{
	if (m_mode == viewReposition)
	{
		m_mode = none;
		ReleaseCapture();
		SetViewCursor(IDC_ARROW);
	}
	else
	{
		m_mode = viewReposition;
		HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_HAND_CURSOR);
		SetCursor(hCursor);
		SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG) hCursor);
		ErasePreview();
	}

}


BOOL CMapEditorView::OnEraseBkgnd(CDC* pDC) 
{
	CMapEditorDoc *pDoc = GetDocument();
	if (pDoc)
	{
		CRect rect;
		pDC->GetClipBox(&rect);     // Erase the area needed
		pDC->FillSolidRect(&rect,pDoc->m_rgbBackground);
		return TRUE;
	}
	else
		return CScrollView::OnEraseBkgnd(pDC);
}

void CMapEditorView::OnEditScripts() 
{
	CScriptsDlg dlg;
	CMapEditorDoc *pDoc = GetDocument();
	
	if (NULL == pDoc)
	{
		AfxMessageBox(_T("Error"));
	}
	else
	{
		dlg.m_sAFile = pDoc->m_sAFile;
		dlg.m_sAText = pDoc->m_sAText;
		dlg.m_sPFile = pDoc->m_sPFile;
		dlg.m_sPText = pDoc->m_sPText;
		if (IDOK == dlg.DoModal())
		{
			pDoc->m_sAFile = dlg.m_sAFile;
			pDoc->m_sAText = dlg.m_sAText;
			pDoc->m_sPFile = dlg.m_sPFile;
			pDoc->m_sPText = dlg.m_sPText;
		}
	}
}

void CMapEditorView::OnSelectArea() 
{
	CSelectDlg dlg;
	CMapEditorDoc *pDoc = GetDocument();
	CTileSet *pTileSet = GetTileSet();
	CMapLayer *pLayer = NULL;
	CRect rectOld;
	CRect rectNew;

	pLayer = pDoc->GetActiveLayer();

	if (NULL != pLayer)
	{
		rectOld = pLayer->GetSelection();
		dlg.m_iBX = rectOld.left/pTileSet->m_iTileWidth;
		dlg.m_iBY = rectOld.top/pTileSet->m_iTileHeight;
		dlg.m_iEX = rectOld.right/pTileSet->m_iTileWidth;
		dlg.m_iEY = rectOld.bottom/pTileSet->m_iTileHeight;
	}

	if (IDOK == dlg.DoModal())
	{
		rectNew.left = dlg.m_iBX*pTileSet->m_iTileWidth;
		rectNew.top = dlg.m_iBY*pTileSet->m_iTileHeight;
		rectNew.right = dlg.m_iEX*pTileSet->m_iTileWidth;
		rectNew.bottom = dlg.m_iEY*pTileSet->m_iTileHeight;
		if (TRUE == dlg.m_bReset)
			pDoc->Select(rectOld, FALSE);
		pDoc->Select(rectNew, TRUE);
	}
}

void CMapEditorView::OnEditViewable() 
{
	CSelectDlg dlg;
	CMapEditorDoc *pDoc = GetDocument();
	CTileSet *pTileSet = GetTileSet();
	CMapLayer *pLayer = NULL;
	CRect rectOld;

	if(0 == pDoc->m_iEX && 0 == pDoc->m_iEY)
	{
		pLayer = pDoc->GetActiveLayer();

		if (NULL != pLayer)
		{
			rectOld = pLayer->GetSelection();
			dlg.m_iBX = rectOld.left/pTileSet->m_iTileWidth;
			dlg.m_iBY = rectOld.top/pTileSet->m_iTileHeight;
			dlg.m_iEX = rectOld.right/pTileSet->m_iTileWidth;
			dlg.m_iEY = rectOld.bottom/pTileSet->m_iTileHeight;
		}
	}
	else
	{
		dlg.m_iBX = pDoc->m_iBX;
		dlg.m_iBY = pDoc->m_iBY;
		dlg.m_iEX = pDoc->m_iEX;
		dlg.m_iEY = pDoc->m_iEY;
	}

	dlg.SetViewArea();

	if (IDOK == dlg.DoModal())
	{
		pDoc->m_iBX = dlg.m_iBX;
		pDoc->m_iBY = dlg.m_iBY;
		pDoc->m_iEX = dlg.m_iEX;
		pDoc->m_iEY = dlg.m_iEY;
	}
}

void CMapEditorView::OnEditExpand() 
{
	CExpandDlg dlg;
	CMapEditorDoc *pDoc = GetDocument();
	int iNewWidth=0,iNewHeight=0;

	// Here we expand the map then...
	// if its to the bottom and right, just use the code from the properties dialog.
	// if its to the top and left than use the code from the poperties dialog and do the following
	// Use the cropping code to copy the map to the bottom right of the newly expanded map
	if (IDOK == dlg.DoModal() && (0 != dlg.m_iHeight || 0 != dlg.m_iWidth))
	{
		// Just Do It.
		pDoc->Expand(dlg.m_iMove, dlg.m_iWidth, dlg.m_iHeight);
		RedrawWindow();
	}
}

void CMapEditorView::OnEditRotate() 
{
	CRotateDlg dlg;
	CMapEditorDoc *pDoc = GetDocument();

	if (IDOK == dlg.DoModal())
	{
		if (FALSE == pDoc->Rotate(dlg.m_iType, (0 == dlg.m_iType) ? dlg.m_iRotDir : dlg.m_iFlipDir))
		{
			// Display Error
		}
	}
}
