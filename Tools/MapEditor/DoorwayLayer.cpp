// DoorwayLayer.cpp : implementation file  (for ArmyMen)
//
#include "stdafx.h"
#include "MapEditor.h"
#include "MapEditorDoc.h"
#include "MapFrame.h"
#include "DoorwayLayer.h"
#include "DoorwayView.h"
#include "AttributeLayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
//  This is Bruce's old code
#include "doorways/doorway.c"

/////////////////////////////////////////////////////////////////////////////
// CDoorwayLayer

#define MAXDOORS 500 // for now
#define MAXROUTE 20000 // for now
#define MAXOBSTACLES 1000 // for now

CDoorwayLayer::CDoorwayLayer()
{
	m_lineColor = RGB(0,0,255);
	m_pointColor = RGB(255,0,0);
	m_routeColor = RGB(255,255,0);
	m_iDoorways = 0;
	m_pDoorways = NULL;
    m_pBWDataC1 = NULL;
    m_pBWDataC2 = NULL;
    m_pBWDataL1 = NULL;
    m_pBWDataL2 = NULL;
    m_pBWDataL3 = NULL;
	m_bSelected = FALSE;
	m_routeStart.x = m_routeStart.y = 0;
	m_routeEnd.x = m_routeEnd.y = 0;
	m_iRoutePoints = 0;
	m_pRoutePoints = NULL;
}

void CDoorwayLayer::DeleteDoorways()
{
	m_iDoorways = 0;
	delete [] m_pDoorways;
	m_pDoorways = NULL;
	delete [] m_pBWDataC1;
	m_pBWDataC1 = NULL;
	delete [] m_pBWDataC2;
	m_pBWDataC2 = NULL;
	delete [] m_pBWDataL1;
	m_pBWDataL1 = NULL;
	delete [] m_pBWDataL2;
	m_pBWDataL2 = NULL;
	delete [] m_pBWDataL3;
	m_pBWDataL3 = NULL;
}

void CDoorwayLayer::DeleteRoute()
{
	m_iRoutePoints = 0;
	delete [] m_pRoutePoints;
	m_pRoutePoints = NULL;
}

CDoorwayLayer::~CDoorwayLayer()
{
	DeleteDoorways();
	DeleteRoute();
}

/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void CDoorwayLayer::AssertValid() const
{
	if (m_pMap)
	{
		ASSERT_VALID(m_pMap);
		ASSERT(m_routeStart.x >= 0 && m_routeStart.x < m_pMap->m_iMapWidth);
		ASSERT(m_routeStart.y >= 0 && m_routeStart.y < m_pMap->m_iMapHeight);
		ASSERT(m_routeEnd.x >= 0 && m_routeEnd.x < m_pMap->m_iMapWidth);
		ASSERT(m_routeEnd.y >= 0 && m_routeEnd.y < m_pMap->m_iMapHeight);
	}
	if (m_iDoorways)
	{
		// TBD: check the pointer and allocation of m_pDoorways
	}
	if (m_iRoutePoints)
	{
		// TBD: check the pointer and allocation of m_pRoutePoints
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDoorwayLayer, CMapLayer, VERSIONABLE_SCHEMA | 3)

void CDoorwayLayer::Serialize(CArchive& ar) 
{
	UINT nSchema;
	if (ar.IsLoading())
		nSchema = ar.GetObjectSchema();

	CMapLayer::Serialize(ar);
	if (ar.IsStoring())
	{	
		ar << m_lineColor;
		ar << m_pointColor;
		ar << m_routeColor; // schema >= 2
		ar << m_routeStart; // schema >= 3
		ar << m_routeEnd;   // schema >= 3
	}
	else
	{
		ar >> m_lineColor;
		ar >> m_pointColor;
		if (nSchema >= 2)
		{
			ar >> m_routeColor;
		}
		if (nSchema >= 3)
		{
			ar >> m_routeStart;
			ar >> m_routeEnd;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CDoorwayLayer, CMapLayer)
	//{{AFX_MSG_MAP(CDoorwayLayer)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMPOS, OnUpdateItemPos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void CDoorwayLayer::DrawTile(HDC hdc, CPoint pos, CPoint offset, CRect rect, COLORREF color)
{
	ASSERT(GetMap() != NULL);
	if (pos.y >= 0 && pos.y < m_pMap->m_iMapHeight && 
		pos.x >= 0 && pos.x < m_pMap->m_iMapWidth)
	{
		CRect tmp,srect = m_pMap->GetTileRect(pos.y,pos.x);
		if (tmp.IntersectRect(srect,rect))
		{
			HGDIOBJ brush = GetStockObject(NULL_BRUSH);
			HPEN hOutlinePen = CreatePen(PS_DOT,0,color);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
			HPEN oldPen = (HPEN)SelectObject(hdc, hOutlinePen);
			srect -= offset;
			CPoint center = srect.CenterPoint();
			Rectangle(hdc, srect.left, srect.top, srect.right, srect.bottom);
			MoveToEx(hdc, center.x, center.y, NULL);
			LineTo(hdc, center.x+1, center.y+1);
			SelectObject(hdc,oldPen);
			SelectObject(hdc,oldBrush);
			DeleteObject(hOutlinePen);
		}
	}
}

void CDoorwayLayer::Draw(HDC hdc, CPoint offset, CRect rect, HPALETTE hPalette)
{
	CTileSet *pTileSet = GetTileSet();
	if (!pTileSet) return;

	DrawTile(hdc,m_routeStart,offset,rect,m_lineColor);
	DrawTile(hdc,m_routeEnd,offset,rect,m_pointColor);
	if (m_bSelected)
	{
		DrawTile(hdc,m_last,offset,rect,RGB(0,0,0)); // white is the secondary color
	}

	if (m_iDoorways > 0 && m_pDoorways)
	{
		HPEN hLinePen = CreatePen(PS_SOLID, 1, m_lineColor);
		HPEN hOldPen = (HPEN)SelectObject(hdc, hLinePen);

		for (int i=0; i < m_iDoorways; i++)
		{
			CPoint left,right;
			BOOL bDisplayed;

			VERIFY(GetDoorway(i,left,right,bDisplayed));
			if (bDisplayed) 
			{
				CRect dr = GetDoorwayRect(left,right);
                CRect tmp;
				if (!IntersectRect(tmp,dr,rect))
				   continue;

				left -= offset;
				right -= offset;
			
				MoveToEx(hdc, left.x, left.y, NULL);
				LineTo(hdc, right.x, right.y);

				SetPixel(hdc, left.x, left.y, m_pointColor);
				SetPixel(hdc, right.x, right.y, m_pointColor);
			}
		}
		SelectObject(hdc, hOldPen);
		DeleteObject(hLinePen);
	}

	if (m_iRoutePoints > 1 && m_pRoutePoints)
	{
		HPEN hRoutePen = CreatePen(PS_SOLID, 1, m_routeColor);
		HPEN hOldPen = (HPEN)SelectObject(hdc, hRoutePen);
		long *pPoint = m_pRoutePoints;
        CPoint pt;
		
		// TBD: only redraw the lines in the given rect.
	    CSize size = pTileSet->GetTileSize();
		CPoint half(size.cx >> 1, size.cy >> 1);
		half -= offset; // in case we are drawing off-screen
		pt = m_pMap->GetTileOffset(DECODEI(*pPoint), DECODEJ(*pPoint)) + half;
		MoveToEx(hdc,pt.x,pt.y,NULL);
		for (int i=1; i < m_iRoutePoints; i++)
		{
			++pPoint;
			pt = m_pMap->GetTileOffset(DECODEI(*pPoint), DECODEJ(*pPoint)) + half;
			LineTo(hdc,pt.x,pt.y);
		}
		SelectObject(hdc,hOldPen);
		DeleteObject(hRoutePen);
	}

}

void BindMovementData(char* pData,
                      int w,
                      int h,
                      CAttributeLayer *pAttr,
                      CAttributeLayer *pType)    
{

    ATTRIBUTE_FLAGS flags; // ignored

    // make sure all the object attributes are up-to-date
    pType->UpdateOverrides();  
    pAttr->UpdateOverrides();  

    for (int iRow=0; iRow < h; iRow++)
    {
        for (int iCol=0; iCol < w; iCol++)
        {
            int index = INDEX(iRow,iCol,w);
            char type = pType->GetAttribute(iRow,iCol,&flags) & 0x0f;
            char movement = pAttr->GetAttribute(iRow,iCol,&flags) & 0x0f; 
            ASSERT(index >= 0 && index < (w * h));
            pData[index] = (type << 4) | movement;
        }
    }
}

void CDoorwayLayer::Compute()
{
	CAttributeLayer *pAttr,*pType = NULL;
	CMapLayer *pLayer;

	if (m_pMap)
	{
        if ((m_pMap->m_iMapWidth > MAXCOORD) || (m_pMap->m_iMapHeight > MAXCOORD))
		{
			CString msg;
			msg.Format("Map Width and Map Height must not exceed %u", MAXCOORD);
			UserError(msg);
		}
        else if (!(pLayer = m_pMap->FindLayer("Movement")) || 
				 !(pAttr = DYNAMIC_DOWNCAST(CAttributeLayer,pLayer)))
		{
            UserError("Map must have an attribute layer named 'Movement'");
		}
        else if (!(pLayer = m_pMap->FindLayer("Type")) || 
				 !(pType = DYNAMIC_DOWNCAST(CAttributeLayer,pLayer)))
		{
            UserError("Map must have an attribute layer named 'Type'");
		}

		char *pData = NULL;
		int w = m_pMap->m_iMapWidth;
		int h = m_pMap->m_iMapHeight;
		TRY
		{
			if (!m_pDoorways)
			{
				m_pDoorways = new ANSWERS[MAXDOORS];
				ASSERT_NEW(m_pDoorways);
			}

            // allocate persistent data for route planner (GetRoute)

			if (!m_pBWDataC1)
			{
				m_pBWDataC1 = new char[(w * h)];
				ASSERT_NEW(m_pBWDataC1);
			}
			if (!m_pBWDataC2)
			{
				m_pBWDataC2 = new char[(w * h)];
				ASSERT_NEW(m_pBWDataC2);
			}
			if (!m_pBWDataL1)
			{
				m_pBWDataL1 = new long[(w * h) + 2]; // +2 = overflow protect
				ASSERT_NEW(m_pBWDataL1);
			}
			if (!m_pBWDataL2)
			{
				m_pBWDataL2 = new long[(w * h) + 2]; // +2 = overflow protect
				ASSERT_NEW(m_pBWDataL2);
			}
			if (!m_pBWDataL3)
			{
				m_pBWDataL3 = new long[MAXOBSTACLES + 2];//+2 =overflow protect
				ASSERT_NEW(m_pBWDataL3);
			}

            // acquire the movement data to pass for analysis 
            BindMovementData(m_pBWDataC1,w,h,pAttr,pType);

			int doors = GetDoors(1,w,h,m_pBWDataC1,m_pBWDataC2,
                                 m_pBWDataL1,m_pBWDataL2,m_pBWDataL3,
                                 m_pDoorways,MAXDOORS);
                                 /* number of answers returned */

			// TBD: if doors > MAXDOORS grow m_pDoorways and try again...
			m_iDoorways = min(doors,MAXDOORS);   

			for (int i=0; i < m_iDoorways; i++)
			{
				m_pDoorways[i].id1 = TRUE; // this doorway is shown
			}
			// TBD: compute the visible doorway rect
			m_doorwayRect = CRect(CPoint(0,0),m_pMap->GetSize());
			InvalidateDoorways();
		}
		CATCH_ALL(e)
		{
			THROW_LAST();
		}
		END_CATCH_ALL
	}
}

void CDoorwayLayer::InvalidateDoorways()
{
	if (m_iDoorways)
		Invalidate(m_doorwayRect);
}

void CDoorwayLayer::InvalidateRoute()
{
	if (m_iRoutePoints)
		Invalidate(m_routeRect);
}

void CDoorwayLayer::SetLineColor(COLORREF color)
{
	if (m_lineColor != color)
	{
		m_lineColor = color;
		InvalidateDoorways();
	}
}

void CDoorwayLayer::SetPointColor(COLORREF color)
{
	if (m_pointColor != color)
	{
		m_pointColor = color;
		InvalidateDoorways();
	}
}

void CDoorwayLayer::SetRouteColor(COLORREF color)
{
	if (m_routeColor != color)
	{
		m_routeColor = color;
		InvalidateRoute();
	}
}

CDoorwayLayer *CDoorwayLayer::Create(CMapEditorDoc *pMap)
{
	ASSERT(pMap != NULL);
    CString pszName = pMap->NewLayerName(IDS_DOORWAY);
	CDoorwayLayer *pLayer = new CDoorwayLayer;
	ASSERT_NEW(pLayer);
	pLayer->SetMap(pMap);
	pLayer->SetTitle(pszName);
	pLayer->SetVisible(TRUE);
	pMap->AddLayer(pLayer);
	return pLayer;
}

// Note: this method assumes that all views of the map share the same active
// layer. This is kind of a shame; 
 
void CDoorwayLayer::Activate(BOOL bRefresh)
{
	CMapFrame *pFrame = GetParentFrame();
    if (pFrame)	
		pFrame->InstallToolPane(RUNTIME_CLASS(CDoorwayView), 
		                        theApp.m_pMapDocTemplate, GetMap(), TRUE);
}

BOOL CDoorwayLayer::GetDoorway(int iDoorway, CPoint& left, CPoint& right, BOOL& bDisplayed)
{
	if (iDoorway >= 0 && iDoorway <= m_iDoorways && m_pDoorways)
	{
		struct Doorway *pDoorway = &m_pDoorways[iDoorway];

		left.x = DECODEJ(pDoorway->endleft);
		left.y = DECODEI(pDoorway->endleft);

		right.x = DECODEJ(pDoorway->endright);
		right.y = DECODEI(pDoorway->endright);
		bDisplayed = pDoorway->id1;
		return TRUE;
	}
	return FALSE;
}

CRect CDoorwayLayer::GetDoorwayRect(CPoint& left, CPoint& right)
{
	CTileSet *pTileSet = GetTileSet();
    CSize size = pTileSet->GetTileSize();
	CSize half(size.cx >> 1, size.cy >> 1);
	CRect rect(left.x * size.cx, left.y * size.cy, 
		      right.x * size.cx, right.y * size.cy);

	rect.OffsetRect(half);
	left = rect.TopLeft();
	right = rect.BottomRight();

	rect.NormalizeRect();
	rect.InflateRect(half); // so we have a non-null rectangle
	return rect;
}

void CDoorwayLayer::DisplayDoorway(int iDoorway,BOOL bDisplayIt)
{
	LPCTSTR pszTitle = GetTitle();
	ASSERT(iDoorway >= 0 && iDoorway <= m_iDoorways && m_pDoorways);
	struct Doorway *pDoorway = &m_pDoorways[iDoorway];
	pDoorway->id1 = bDisplayIt;
	if (m_pMap)
	{
		CPoint left, right;
        VERIFY(GetDoorway(iDoorway,left,right,bDisplayIt));
		Invalidate(GetDoorwayRect(left,right));
	}
}

CPoint CDoorwayLayer::LimitPoint(CPoint pt, int iStartRow, int iStartCol, int iEndRow, int iEndCol)
{
	ASSERT(iStartRow < iEndRow);
	ASSERT(iStartCol < iEndCol);

	pt.x = max( min(pt.x, iEndCol-1), iStartCol) - iStartCol;
	pt.y = max( min(pt.y, iEndRow-1), iStartRow) - iStartRow;
	return pt;
}

CMapLayer * CDoorwayLayer::CropToSelection(CRect rect, int iStartRow, int iStartCol, int iEndRow, int iEndCol, BOOL bSelectedOnly)
{
	CDoorwayLayer *pLayer = new CDoorwayLayer;
	ASSERT_NEW(pLayer);
	pLayer->SetMap(GetMap());
	pLayer->SetTitle(GetTitle());
	pLayer->SetVisible(IsVisible());
	pLayer->m_routeStart = LimitPoint(m_routeStart,iStartRow,iStartCol,iEndRow,iEndCol);
	pLayer->m_routeEnd = LimitPoint(m_routeEnd,iStartRow,iStartCol,iEndRow,iEndCol);
	return pLayer;
}

CMapLayerMode CDoorwayLayer::ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected)
{
	if (m_last.y == iRow && m_last.x == iColumn)
	{
		m_bSelected ^= TRUE;  // invert current selection
		bSelected = m_bSelected;
		Invalidate(iRow,iColumn);
	}
	else
	{
		PlaceItem(point,iRow,iColumn);
	}
	return none;
}

CMapLayerMode CDoorwayLayer::PlaceItem(CPoint point, int iRow, int iColumn)
{
	if (m_bSelected)
	{
		// invalidate old selection
		Invalidate(m_last.y,m_last.x);
	}
	// set new selection
	m_bSelected = TRUE;
	UpdateItemPos(iRow,iColumn);
	Invalidate(iRow,iColumn);
	return none;
}


void CDoorwayLayer::SelectNone()
{
	if (m_bSelected)
	{
		m_bSelected = FALSE;
		Invalidate(m_last.y, m_last.x);
		UpdateItemPos();
	}
}

void CDoorwayLayer::SetPoint(CPoint& pt)
{
	if (m_bSelected)
	{
		if (m_last.x != pt.x && m_last.y != pt.y)
		{
			InvalidateRoute();
			DeleteRoute();
		}
		Invalidate(pt.y, pt.x); // dehighlight old point
		pt = m_last;            // set new point
		SelectNone();           // remove selection
	}
}

void CDoorwayLayer::SetRouteStart()
{
	SetPoint(m_routeStart);
}

void CDoorwayLayer::SetRouteEnd()
{
	SetPoint(m_routeEnd);
}

void CDoorwayLayer::Clear()
{
	if (m_bSelected)
	{
		ToggleItem(m_last,m_last.y,m_last.x,m_bSelected);
	}
	if (m_iDoorways)
	{
		InvalidateDoorways();
		DeleteDoorways();
	}
	if (m_iRoutePoints)
	{
		InvalidateRoute();
		DeleteRoute();
	}
}


void CDoorwayLayer::ComputeRoute()
{
	ASSERT(GetMap());

	ASSERT_VALID(this);
	if (m_pDoorways == NULL)
		Compute(); // compute doorways
	if (m_pDoorways == NULL)
		return; 

    // must already have allocated this data by computing doorways 1st
    ASSERT_NEW(m_pBWDataC1);
    ASSERT_NEW(m_pBWDataC2);
    ASSERT_NEW(m_pBWDataL1);
    ASSERT_NEW(m_pBWDataL2);
    ASSERT_NEW(m_pBWDataL3);

    int w = m_pMap->m_iMapWidth;
    int h = m_pMap->m_iMapHeight;
    TRY
    {
        if (m_pRoutePoints == NULL)
        {
            m_pRoutePoints = new long[MAXROUTE];
            ASSERT_NEW(m_pRoutePoints);
        }

        m_iRoutePoints = GetRoute(m_routeStart.y, m_routeStart.x, 
                                  m_routeEnd.y, m_routeEnd.x, 
                                  (unsigned long*) m_pRoutePoints, MAXROUTE);

        // TBD: compute the visible route rect
        m_routeRect = CRect(CPoint(0,0),m_pMap->GetSize());
        InvalidateRoute();
    }
    CATCH_ALL(e)
    {
        THROW_LAST();
    }
    END_CATCH_ALL

}
/////////////////////////////////////////////////////////////////////////////
// CDoorwayLayer message handlers

void CDoorwayLayer::OnUpdateItemPos(CCmdUI *pCmdUI)
{
	if (m_bSelected)
	{
		CString data;
		data.Format(IDS_ROW_COLUMN_FORMAT,m_last.y, m_last.x);
		pCmdUI->SetText(data);
	}
	else
	{
		pCmdUI->SetText(NULL); // SetText("") may result in memory leak
	}
}



