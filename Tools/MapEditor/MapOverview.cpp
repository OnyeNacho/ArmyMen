// MapOverview.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapEditorDoc.h"
#include "MapEditorView.h"
#include "MapOverview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapOverview 

IMPLEMENT_DYNCREATE(CMapOverview, CMapEditorView)

BEGIN_MESSAGE_MAP(CMapOverview, CMapEditorView)
	//{{AFX_MSG_MAP(CMapOverview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapOverview : construction destruction

CMapOverview::CMapOverview()
{
	m_updateRect.SetRectEmpty();
	m_updateHeight = 1;
}

CMapOverview::~CMapOverview()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMapOverview diagnostics

#ifdef _DEBUG
void CMapOverview::AssertValid() const
{
	CView::AssertValid();
}

void CMapOverview::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapEditorDoc* CMapOverview::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditorDoc)));
	return (CMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CMapOverview message handlers

void CMapOverview::OnUpdateSizes()
{
	CSize size = GetDocument()->GetSize();
	SetScaleToFitSize( size );

	CRect rect;
	GetWindowRect(&rect);
	int iHeight = max(1, rect.Height());

	m_updateHeight = max(1, size.cy / iHeight);

	CTileSet *pTileSet = GetTileSet();
	if (pTileSet)
	{
		iHeight = pTileSet->m_iTileHeight;
		if (m_updateHeight > iHeight)
			m_updateHeight = iHeight;
	}

}

void CMapOverview::OnInitialUpdate() 
{
	GetParentFrame()->RecalcLayout(); // may sure view size has been set
	OnUpdateSizes();
}

/*
** METHOD
**   CMapOverview::OnDraw
** 
** PARAMETERS
**   CDC *pDC --  non-NULL pointer to device context to be used for rendering 
**
** DESCRIPTION
**	 Called by the framework to render a the map overview. The clipbox
**   determines how much of the overview to render.  If the entire overview
**   is being rendered, we set the m_updateRect for this view so the
**   overview will be rendered in the background.  If only a portion of
**   of the overview is being rendered, renders it now.
**
**   TBD: if only a portion of the overview is being rendered,
**   render only the portion outside m_updateRect.
*/
void CMapOverview::OnDraw(CDC *pDC)
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
	BOOL bNeedsUpdate = TRUE;

	if (rect.Width() >= size.cx && rect.Height() >= size.cy) 
	{
		// update this during idle time
		m_updateRect.UnionRect(m_updateRect,rect);
		bNeedsUpdate = FALSE;
	}
    if (bNeedsUpdate)
		CMapEditorView::OnDraw(pDC);
}



/*
** METHOD
**   CMapOverview::OnIdleUpdate
**
** DESCRIPTION
**   Call this method to update/redraw the overview window during 
**   the CWinApp::OnIdle time. This limits the redraw to map row
**   at a time to avoid bogging down UI interactions.
*/      
BOOL CMapOverview::OnIdleUpdate()
{
   BOOL bContinueUpdate = FALSE;
   if (!m_updateRect.IsRectEmpty())
   {
		CClientDC dc(this);
		OnPrepareDC(&dc);
		CRgn rgn;

		int bottom = min(m_updateRect.top + m_updateHeight, m_updateRect.bottom);
		CRect tmp(m_updateRect.left, m_updateRect.top, m_updateRect.right, bottom);
	    dc.LPtoDP(&tmp);

		if (rgn.CreateRectRgnIndirect(&tmp))
		{
			switch(dc.SelectClipRgn(&rgn))
			{
				case ERROR:
					TRACE("bad clip region? %d,%d,%d,%d\n",
						   m_updateRect.left, m_updateRect.top, m_updateRect.right, bottom);
					break;
				case NULLREGION:
					//TRACE("null region\n");
					break;
				case COMPLEXREGION: 
					CMapEditorView::OnDraw(&dc);
					InvalidateRect(&tmp); 
					break;
				default:
					CMapEditorView::OnDraw(&dc);
					break;
			}
			m_updateRect.top = bottom;
			if (m_updateRect.top < m_updateRect.bottom)
				bContinueUpdate = TRUE;
			else
				m_updateRect.SetRectEmpty();
		}
		else
		{
			TRACE("Can't create region\n");
			bContinueUpdate = TRUE;
		}
   }
   return bContinueUpdate;
}