// MapLayer.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapLayer.h"
#include "MapFrame.h"
#include "MapEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapLayer

CMapLayer::CMapLayer()
{
	m_bVisible = FALSE;  
	m_pMap = NULL;
	m_last.x = -1;
	m_last.y = -1;
}

CMapLayer::~CMapLayer()
{
	TRACE("Deleted layer %s\n",GetTitle());
}

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMapLayer, CCmdTarget, VERSIONABLE_SCHEMA | 1)

void CMapLayer::Serialize(CArchive& ar) 
{
	// Note: since MapLayer's are only used dynamically we could
	// have lived without the PUT_SAFE_SCHEMA/GET_SAFE_SCHEMA; live and learn

	// Notice the map pointer does not get stored so it is
	// up to the caller to restore the map pointer.
	CCmdTarget::Serialize(ar);
	if (ar.IsStoring())
	{	
		PUT_SAFE_SCHEMA(ar, CMapLayer);
		ar << m_pszTitle;
		ar << m_bVisible;
	}
	else
	{
		UINT schema = GET_SAFE_SCHEMA(ar, CMapLayer, 1);
		ar >> m_pszTitle;
		ar >> m_bVisible;
		m_last.x = -1;
		m_last.y = -1;
	}
}
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMapLayer, CCmdTarget)
	//{{AFX_MSG_MAP(CMapLayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_NONE, OnUpdateEditSelectNone)
	ON_COMMAND(ID_EDIT_SELECT_NONE, OnEditSelectNone)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMPOS, OnUpdateItemPos)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMTYPE,OnUpdateItemNone)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMID,  OnUpdateItemNone)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMINFO,OnUpdateItemNone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TBD: it might be more efficient to NOT have the layers do any invalidation
// and just have the map handle the invalidation for the active layer. 
// Especially if more than one layer is active at a time.
void CMapLayer::SetModifiedFlag()
{
	if (m_pMap)
		m_pMap->SetModifiedFlag();
}
void CMapLayer::Invalidate(int iRow, int iColumn)
{
	if (m_pMap && m_bVisible)
		m_pMap->Invalidate(iRow, iColumn);
}
void CMapLayer::Invalidate(LPRECT lpRect)
{
	if (m_pMap && m_bVisible)
		m_pMap->Invalidate(lpRect);
}

void CMapLayer::NeedsUpdate()
{
	if (m_pMap && m_bVisible)
		m_pMap->m_bNeedsUpdate = TRUE;
}

void CMapLayer::Invalidate(int iStartRow, int iStartCol, int iEndRow, int iEndCol)
{
	if (m_pMap && m_bVisible)
	{
		CSize tileSize = GetTileSet()->GetTileSize();
		m_pMap->Invalidate(CRect(iStartCol * tileSize.cx, iStartRow * tileSize.cy,
								 iEndCol * tileSize.cx, iEndRow * tileSize.cy));
	}
}
BOOL CMapLayer::SetVisible(BOOL bVisible)
{
	BOOL bOld = m_bVisible;
	m_bVisible = bVisible;
	return bOld;
}

CMapEditorDoc* CMapLayer::GetMap() 
{ 
	ASSERT(m_pMap);
	return m_pMap;
}

CTileSet *CMapLayer::GetTileSet()  
{
	ASSERT(m_pMap);
	return m_pMap->GetTileSet(); 
}

CPalette *CMapLayer::GetPalette()  
{ 
	ASSERT(m_pMap);
	return m_pMap->GetPalette(); 
}

CObjectSet *CMapLayer::GetObjectSet()
{
	ASSERT(m_pMap);
	return m_pMap->GetObjectSet();
}

CScenarioSet * CMapLayer::GetScenarioSet()
{
	ASSERT(m_pMap);
	return m_pMap->GetScenarioSet();
}

void CMapLayer::Deactivate()
{
	BOOL bVisible = m_bVisible; // so map doesn't get redrawn
	SelectNone();
	ClearUndo();

	m_bVisible = bVisible;
	m_last.x = -1;
	m_last.y = -1;
	if (g_pReplaceDlg)
	{
		g_pReplaceDlg->SendMessage(WM_CLOSE);
		g_pReplaceDlg = NULL;
	}
}

void CMapLayer::Draw(HDC hdc, CPoint offset, CRect rect, HPALETTE hPalette)
{
#ifdef _DEBUG
	// implement this routine for all non-tile based layers
	// the input rect will be the coordinates of the map
	// rectangle you should render. You may call this routine
	// to verify the preconditions.  You may assume that the
	// appropriate palette has already been selected into the hdc
	ASSERT_VALID(this);
	ASSERT(!rect.IsRectEmpty());
	ASSERT(hdc != NULL);
	CRect bounds(CPoint(0,0), GetMap()->GetSize());
	CRect tmp;
	ASSERT(tmp.IntersectRect(bounds,rect));
#endif
}

void CMapLayer::Draw(HDC hdc, CPoint offset, int iStartRow, int iStartCol,
					 int iEndRow, int iEndCol)
{
#ifdef _DEBUG
	// implement this routine for all tile based layers
	// You may call this routine to verify preconditions
	// you may assume that the appropriate palette has already 
	// been selected into hdc.
	ASSERT_VALID(this);
	ASSERT(m_pMap);
	ASSERT(iStartRow >= 0 && iStartRow < m_pMap->m_iMapHeight);
	ASSERT(iStartCol >= 0 && iStartCol < m_pMap->m_iMapWidth);
	ASSERT(iStartRow != iEndRow);
	ASSERT(iStartCol != iEndCol);
#endif
}

CRect CMapLayer::GetSelection() 
{ 
	// return the bounding box in map coordinates for the
	// current selection. If there is no current selection
	// return an empty box.

	CRect rect; 
	rect.SetRectEmpty(); 
	return rect; 
}

CMapLayer *CMapLayer::CropToSelection(CRect rect, int iStartRow, int iStartCol, int iEndRow, int iEndCol, BOOL bSelectedOnly)
{
	// return a new layer that just contains data for the given
	// map rectangle.  If there is no data for the given map
	// rectangle, you should return an empty layer -- do not
	// return NULL. If bSelectedOnly is TRUE, you should only
	// return data that is in the given rectangle AND is currently
	// selected otherwise return all data in the given rectangle.
	// Throw an exception if any error occurs.
	// the rectangle is in map coordinates -- aligned on tile
	// boundaries.
#ifdef _DEBUG
	CTileSet *pTileSet = GetTileSet();
	ASSERT(pTileSet != NULL);
    CSize tileSize = pTileSet->GetTileSize();
	ASSERT(tileSize.cx != 0);
	ASSERT(tileSize.cy != 0);
    //ASSERT((rect.left % tileSize.cx) == 0);
	//ASSERT((rect.right % tileSize.cx) == 0);
	//ASSERT((rect.top % tileSize.cy) == 0);
	//ASSERT((rect.bottom % tileSize.cy) == 0);
	//ASSERT((iStartRow >= 0) && (iStartRow < GetMap()->m_iMapHeight));
	//ASSERT((iStartCol >=0) && (iStartCol < GetMap()->m_iMapWidth));
#if 0
	// your code would look something like this...
	CMapLayer *pLayer = new CMapLayer;
	ASSERT_NEW(pLayer);

	// any initialization that requires
	// the map to be repainted, would go here...
	pLayer->m_bVisible = m_bVisible;
	pLayer->m_pMap = m_pMap;

	// other initializations can go after..

#endif

#else
	AfxThrowNotSupportedException();
#endif

	return NULL;
}

void CMapLayer::SelectNone() 
{
	TRACE("SelectNone not handled by layer: %s\n", GetTitle());
}
/////////////////////////////////////////////////////////////////////////////
// CMapLayer message handlers

void CMapLayer::OnUpdateEditSelectNone(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelected());	
}

void CMapLayer::OnEditSelectNone() 
{
	SelectNone();
}

void CMapLayer::OnUpdateItemNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(NULL); // SetText("") may result in memory leak
}

void CMapLayer::OnUpdateItemPos(CCmdUI *pCmdUI)
{
	if (m_last.x < 0 || m_last.y < 0)
	{
		pCmdUI->SetText(NULL); // SetText("") may result in memory leak
	}
	else
	{
		CString data;
		if (IsTileBased())
			data.Format(IDS_ROW_COLUMN_FORMAT,m_last.y, m_last.x);
		else
			data.Format(IDS_POINT_FORMAT, m_last.x, m_last.y);
		pCmdUI->SetText(data);
	}
}

void CMapLayer::UpdateItemPos(int iRow, int iColumn)
{
	m_last.x = iColumn;
	m_last.y = iRow;
}

void CMapLayer::UpdateItemPos(CPoint pos)
{
	m_last = pos;
}

// Note: this method assumes that all views of the map share the same active
// layer. This is kind of a shame; 
// TBD: should the frame keep track of the active layer so the user can open
// multiple views/frames of the same map and cut/paste between the layers?
void CMapLayer::Activate(BOOL bRefresh)
{
	CMapFrame *pFrame = GetParentFrame();
	if (pFrame) pFrame->InstallToolPane(bRefresh); // install empty tool pane
}

CMapFrame * CMapLayer::GetParentFrame()
{
	CMapEditorDoc *pDoc = GetMap();
	POSITION pos = pDoc ? pDoc->GetFirstViewPosition() : NULL;
	
	while (pos != NULL)
	{
		CView *pView = pDoc->GetNextView( pos );
		if (pView)
		{
			CMapFrame *pFrame = STATIC_DOWNCAST(CMapFrame, pView->GetParentFrame());
			return pFrame;
		}
	}
	return NULL;
}



BOOL CMapLayer::OpenClipboard()
{
	// Note: use the parent frame so we can make it the
	// clipboard owner if we need to.
	CMapFrame *pFrame = GetParentFrame();
	if (pFrame)
		return pFrame->OpenClipboard();
	else
		return ::OpenClipboard(NULL);
}
