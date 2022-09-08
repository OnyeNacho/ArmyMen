#include "stdafx.h"
#include "MapEditor.h"
#include "MapFrame.h"
#include "MapEditorDoc.h"
#include "ObjectSetView.h"
#include "ObjectLayer.h"
#include "ObjectSet.h"
#include "MapUpdate.h"
#include "AttributeLayer.h"
#include "AttributeSheet.h"
#include "AnimPropPage.h"
#include "AnimMapObject.h"
#include "textpage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////////
// CObjectLayer

IMPLEMENT_SERIAL(CObjectLayer, CMapLayer, VERSIONABLE_SCHEMA | 1)

void CObjectLayer::Serialize(CArchive& ar) 
{
	// Note: since CObjectLayers are only used dynamically we can
	// avoid the PUT_SAFE_SCHEMA/GET_SAFE_SCHEMA
	CMapLayer::Serialize(ar);
	m_objects.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CObjectLayer, CMapLayer)
	//{{AFX_MSG_MAP(CObjectLayer)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_TOP, OnUpdateMultipleObjects)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_FORWARD, OnUpdateSingleObject)
	ON_COMMAND(ID_OBJECT_TOP, OnObjectTop)
	ON_COMMAND(ID_OBJECT_BOTTOM, OnObjectBottom)
	ON_COMMAND(ID_OBJECT_FORWARD, OnObjectForward)
	ON_COMMAND(ID_OBJECT_BACK, OnObjectBack)
	ON_COMMAND(ID_LEFT, OnObjectLeft)
	ON_COMMAND(ID_RIGHT, OnObjectRight)
	ON_COMMAND(ID_UP, OnObjectUp)
	ON_COMMAND(ID_DOWN, OnObjectDown)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPLACE, OnUpdateEditReplace)
	ON_COMMAND(ID_EDIT_REPLACE, OnEditReplace)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_COMMAND(ID_EDIT_ATTRIBUTES, OnObjectAttributes)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ATTRIBUTES, OnUpdateObjectAttributes)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_SORT, OnUpdateObjectSort)
	ON_COMMAND(ID_OBJECT_SORT, OnObjectSort)
	ON_COMMAND(ID_OBJECT_FLIPHORIZONTAL, OnObjectFlipHorizontal)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_BOTTOM, OnUpdateMultipleObjects)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_BACK, OnUpdateSingleObject)
	ON_UPDATE_COMMAND_UI(ID_LEFT, OnUpdateMultipleObjects)
	ON_UPDATE_COMMAND_UI(ID_RIGHT, OnUpdateMultipleObjects)
	ON_UPDATE_COMMAND_UI(ID_UP, OnUpdateMultipleObjects)
	ON_UPDATE_COMMAND_UI(ID_DOWN, OnUpdateMultipleObjects)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateMultipleObjects)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateMultipleObjects)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_FLIPHORIZONTAL, OnUpdateMultipleObjects)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
CRect CObjectLayer::GetSelection()
{
	CRect selection;
	selection.SetRectEmpty();
	POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
	{
		CMapObjectInst *pObject = m_objects.GetNext(pos);
		ASSERT(pObject != NULL);
		if (pObject->m_bSelected)
		{
		    selection.UnionRect(selection,GetObjectRect(pObject));
		}
	}
	return selection;
}

CObjectLayer::CObjectLayer() 
{ 
	m_nSelected = 0;
	m_pLastObject = NULL;
}

CObjectLayer::CObjectLayer(CMapEditorDoc *pMap, LPCSTR lpszTitle) 
{
	m_nSelected = 0;
	m_pLastObject = NULL;
	SetMap(pMap);
	SetTitle(lpszTitle);
}

CObjectLayer::~CObjectLayer()
{
	TRACE("Deleting objects %s\n",GetTitle());
	while (!m_objects.IsEmpty())
	{
		CMapObjectInst *pObject = m_objects.RemoveHead();
		delete pObject;
	}
}

void CObjectLayer::InvalidateOb(CMapObjectInst *pObject)
{ 
	if (m_pMap)
	{
		Invalidate(GetObjectRect(pObject));	

		// in case the object has visible attributes, update the
		// tile containing the attribute value.
		int iRow,iColumn;
		m_pMap->GetRowColumn(GetHotSpot(pObject),iRow,iColumn,FALSE,TRUE);
		Invalidate(m_pMap->GetTileRect(iRow,iColumn)); 
	}
}

/*
** METHOD
**    CObjectLayer::CopyObjectAttributes
**
** PARAMETERS
**    CObjectLayer *pNewLayer -- new object layer that is supposed to be equivalent to this
**    CLayersList& rNewLayers -- list to which pNewLayer belongs.
**    CRect rect              -- rectangle that was used to resize/crop this and generate pNewLayer
**    BOOL bSelectedOnly      -- boolean value that was used to resize/crop this and generate pNewLayer
**
** DESCRIPTION
**   Awful method to copy object attributes from the current object layer
**   to a new object layer (pNewLayer) that was presumably generated via
**   call to CropToSelection on this layer.
**
**   This method must be called after all the new map layers have been
**   generated/cropped and before the current layer is destroyed or
**   otherwise detached from the map.
**
**   Assumes that rNewLayers contains an equivalent attribute layer for
**   each old attribute layer and that the order of the attribute layers
**   has been preserved.
**
**   THIS IS VERY GROSS -- I apologize. Maybe I should have kept 
**   attribute information local to each CMapObjectInst after all.
*/
void CObjectLayer::CopyObjectAttributes(CObjectLayer *pNewLayer, CLayersList& rNewLayers, CRect rect, BOOL bSelectedOnly)
{
	ASSERT(pNewLayer != NULL);
	POSITION oldPos = GetFirstObjectPosition();
    POSITION newPos = pNewLayer->GetFirstObjectPosition();
    CMapObjectInst *pOld,*pNew;
	CAttributeLayer *pAttribute;
	CAttributeInfo attr;
    CRect irect;

	while (oldPos != NULL)
	{
		pOld = GetNextObject(oldPos);
		ASSERT(pOld != NULL);

		if (irect.IntersectRect(GetObjectRect(pOld), rect))
		{
			if (!bSelectedOnly || pOld->m_bSelected)
			{
				pNew = pNewLayer->GetNextObject(newPos);
				ASSERT(pNew != NULL);
				ASSERT(pOld->m_ID == pNew->m_ID);

				POSITION oldAttrPos = GetFirstAttribute();
				POSITION newAttrPos = rNewLayers.GetHeadPosition();
				while (oldAttrPos != NULL)
				{
					GetNextAttribute(oldAttrPos,pOld,attr); // get attr & increment pos
					while ( (newAttrPos != NULL) &&
						    !(pAttribute = DYNAMIC_DOWNCAST(CAttributeLayer, 
							             rNewLayers.GetNext(newAttrPos))) );
					ASSERT(pAttribute != NULL);
					pAttribute->AdjustObjectAttribute(pNew,attr);
				}
			}
		}
	}
}
CMapLayer *CObjectLayer::FinishCrop(CObjectLayer *pLayer, int iExpandRow, int iExpandCol, CRect rect, BOOL bSelectedOnly)
{
	ASSERT(pLayer != NULL);
	POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
	{
		CMapObjectInst *pObject = m_objects.GetNext(pos);
		ASSERT(pObject != NULL);
        CRect irect;

		if (irect.IntersectRect(GetObjectRect(pObject), CRect(0, 0, rect.right, rect.bottom)))
		{
			if (!bSelectedOnly || pObject->m_bSelected)
			{
				CPoint pt = pObject->m_location;
				if (0 == iExpandRow)
					pt.y -= rect.top;
				else
					pt.y += rect.top;
				if (0 == iExpandCol)
					pt.x -= rect.left;
				else
					pt.x += rect.left;
				
				//pt -= rect.TopLeft();
				pLayer->AddObject(pObject->m_ID, pt);
			}
		}
	}
	// TBD: somehow need to preserve object attributes
	pLayer->SetTitle(m_pszTitle);
	pLayer->m_bVisible = m_bVisible;
	return pLayer;
}

CMapLayer *CObjectLayer::CropToSelection(CRect rect, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol, BOOL bSelectedOnly)
{
#ifdef _DEBUG
	CMapLayer::CropToSelection(rect,iStartRow,iStartCol,iEndRow,iEndCol,bSelectedOnly); // verify pre-conditions
#endif

	CObjectLayer *pLayer = new CObjectLayer;
	ASSERT_NEW(pLayer);
	return FinishCrop(pLayer,(iEndRow > GetMap()->m_iMapHeight) ? 1 : 0, (iEndCol > GetMap()->m_iMapWidth) ? 1 : 0, rect,bSelectedOnly);
}

void CObjectLayer::RemoveObjectAt(POSITION pos)
{
	CMapObjectInst *pInstance = m_objects.GetAt(pos);
	if (pInstance)
	{
		m_objects.RemoveAt(pos);
		if (m_pMap)
		{
			POSITION pos = m_pMap->GetFirstAttribute();
			while (pos != NULL)
			{
				CAttributeLayer *pAttribute = m_pMap->GetNextAttribute(pos);
				pAttribute->RemoveObjectAttribute(pInstance);
			}
		}
	}
}

CMapLayerMode CObjectLayer::InitMove(CMapObjectInst *pObject, CPoint pt)
{
    m_pLastObject = pObject;
	m_lastPoint = pt;
	if (pObject) UpdateItemPos(pObject->m_location);
	return (m_nSelected ? moveItem : none);
}

// Note: this method assumes that all views of the map share the same active
// layer. This is kind of a shame; 
void CObjectLayer::Activate(BOOL bRefresh)
{
	CMapFrame *pFrame = GetParentFrame();
	if (pFrame) 
		pFrame->InstallToolPane(RUNTIME_CLASS(CObjectSetView), 
		                        theApp.m_pObjectSetTemplate, GetObjectSet(), bRefresh);
}


int CObjectLayer::GetCurrentItem()
{
	CObjectSet *pObjectSet = GetObjectSet();
	if (pObjectSet)
	{
		return pObjectSet->GetCurrentItem();
	}
	return -1;
}

CMapLayerMode CObjectLayer::PlaceItem(CPoint point, int iRow, int iColumn)
{
	CObjectSetView *pView = DYNAMIC_DOWNCAST(CObjectSetView, GetParentFrame()->GetToolView());
	CObjectSet *pSet = pView->GetDocument();
	SMog *pMog=NULL;
	SMogObj *pObj=NULL;
	CMapObjectInst *pObject=NULL;

	int iCurrentItem = GetCurrentItem();
	if (iCurrentItem >= 0)
	{
		if (pView->m_listCtrl.IsMogMode())
		{
			int iCur=0,iCount=0,iItem=0;
			CPoint sTp;
			
			pMog = pView->GetMog(iCurrentItem);
			if (NULL != pMog)
			{
				iCount = pMog->m_sObjs.GetSize();
				while (iCur < iCount)
				{
					pObj = pMog->m_sObjs[iCur];
					if (NULL != pObj)
					{
						iItem = pSet->FindObject(pObj->m_sID, FALSE);
						if (0 <= iItem)
						{
							sTp.x = (pObj->m_sLoc.x - pMog->m_sBegin.x) + point.x;
							sTp.y = (pObj->m_sLoc.y - pMog->m_sBegin.y) + point.y;

							pObject = AddObject(iItem, sTp);
							ASSERT(pObject != NULL);
							pObject->m_bSelected = TRUE;
							++m_nSelected;
							InvalidateOb(pObject);
							UpdateSelectedStatus();

							LoadDefaults(pObject, pView);
							if (pView)
								pView->PlaceItem();
							InitMove(pObject,point);
						}
					}
					iCur++;
				}
			}
			return moveItem;
		}
		else
		{
			pObject = AddObject(iCurrentItem, point);
			ASSERT(pObject != NULL);
			pObject->m_bSelected = TRUE;
			++m_nSelected;
			InvalidateOb(pObject);
			UpdateSelectedStatus();

			LoadDefaults(pObject, pView);
			if (pView)
				pView->PlaceItem();
			return InitMove(pObject,point);  
		}
	}
	return none; // so we don't paint with the objects.
}

void CObjectLayer::MoveItem(CPoint point, int iRow, int iColumn)
{
	if (m_nSelected && m_lastPoint != point)
	{
		MoveSelection(point.x - m_lastPoint.x, point.y - m_lastPoint.y);
		m_lastPoint = point;
	}
}

CMapLayerMode CObjectLayer::ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelected) 
{
	CMapObjectInst *pObject = FindObjectAt(point);
	if (pObject)
	{
		bSelected = !pObject->m_bSelected;
		if (bSelected)
			++m_nSelected;
		else
			--m_nSelected;
		pObject->m_bSelected = bSelected;
		InvalidateOb(pObject);
		UpdateSelectedStatus();
		return InitMove(pObject->m_bSelected ? pObject : NULL, point);
	}
	return none;
}


CMapLayerMode CObjectLayer::SelectItem(CPoint point, int iRow, int iColumn, BOOL bSelected /* TRUE */)
{
	CMapObjectInst *pObject = FindObjectAt(point);
	if (pObject)
	{
		if (pObject->m_bSelected != bSelected)
		{
			if (bSelected)
				++m_nSelected;
			else
				--m_nSelected;
			pObject->m_bSelected = bSelected;
			UpdateSelectedStatus();
			InvalidateOb(pObject);
		}
		return InitMove(pObject,point);
	}
	return none;
}

void CObjectLayer::SelectNone()
{
	if (m_nSelected)
	{
	   m_pLastObject = NULL;
	   CRect rect = GetSelection();
	   POSITION pos = m_objects.GetHeadPosition();
	   while (pos != NULL)
	   {
		   CMapObjectInst *pObject = m_objects.GetNext(pos);
		   ASSERT(pObject != NULL);
		   pObject->m_bSelected = FALSE;
	   }
	   m_nSelected = 0;
	   Invalidate(rect);
	}
}


CMapLayerMode CObjectLayer::GetItem(CPoint point, int iRow, int iColumn)
{
	CMapObjectInst *pObject = FindObjectAt(point);
	if (pObject)
	{
		SelectNone();
		pObject->m_bSelected = TRUE;
		m_nSelected = 1;
		CObjectSet *pObjectSet = GetObjectSet();
		ASSERT(pObjectSet != NULL);
		pObjectSet->SetCurrentItem(pObject->m_ID);
		InvalidateOb(pObject);
		UpdateSelectedStatus();
		return InitMove(pObject, point);
	}
	return none;
}

#ifdef PREVIEW_OBJECT
// don't use this code until we figure out how to handle keyboard
// input while capturing the mouse.
BOOL CObjectLayer::PreviewItem(CPoint point, int iRow, int iColumn)
{
	int iCurrentItem = GetCurrentItem();
	if (iCurrentItem >= 0)
	{
		CMapObject *pObject = GetObjectSet()->GetObject(iCurrentItem);
		GetMap()->SetPreviewRect(CRect(point, pObject->GetSize())); // TBD: object hot-spot
		return TRUE;
	}
	return FALSE;
}

void CObjectLayer::DrawPreview(HDC hdc, CPoint pt, CDIB *pDIB)
{
	int iCurrentItem = GetCurrentItem();
	if (iCurrentItem >= 0)
	{
		CObjectSet *pObjectSet = GetObjectSet();
		CMapObject *pObject = pObjectSet->GetObject(iCurrentItem);
	    ASSERT(pObject != NULL);

		HDC hdcTemp = CreateCompatibleDC(hdc);
		BOOL bDrawn = FALSE;
		int iSequence = pObject->GetCurrentSequence();
		int iFrame = pObject->GetCurrentFrame();
		if (hdcTemp)
		{
			pObjectSet->DrawObject(hdc, iCurrentItem, pt, hdcTemp,
				iSequence, iFrame, pObject->GetFlipped()); 
			DeleteDC(hdcTemp);
			bDrawn = TRUE;
		}
		if (g_bOutlinePreview || !bDrawn)
		   DrawObjectOutline(hdc, pt, pObject->GetSize(iSequence, iFrame), FALSE);

	}
}
#endif

void CObjectLayer::Select(CRect rect, BOOL bSelected)
{
	POSITION pos = m_objects.GetTailPosition();
	CRect inter, obRect;
	while (pos != NULL)
	{
		CMapObjectInst *pObject = m_objects.GetPrev(pos);
		ASSERT(pObject);

		obRect = GetObjectRect(pObject);
		if (inter.IntersectRect(rect,obRect) && (pObject->m_bSelected != bSelected))
		{
			if (bSelected)
				++m_nSelected;
			else
				--m_nSelected;
			pObject->m_bSelected = bSelected;
			Invalidate(obRect);
		}	
	}
	UpdateSelectedStatus();
}

void CObjectLayer::DrawObjectOutline(HDC hdc, const CPoint& pt, const CSize& size, BOOL bDotted)
{
	HPEN hPen;
	if (bDotted)
		hPen = CreatePen(PS_DOT,0,RGB(0,0,0)); // white is the secondary color
	else
		hPen = (HPEN)GetStockObject(WHITE_PEN);

	HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, pt.x, pt.y, pt.x + size.cx, pt.y + size.cy); // TBD: object handle..
	SelectObject(hdc,oldPen);
	SelectObject(hdc,oldBrush);
	if (bDotted) DeleteObject(hPen);
}

void CObjectLayer::Draw(HDC hdc, CPoint offset, CRect rect, HPALETTE hPalette, CDIB *pDst)
{
	HDC hdcTemp = CreateCompatibleDC(hdc); // TBD: the map could do this once before drawing all the layers
	CObjectSet *pObjectSet = GetObjectSet();
    if (!pObjectSet) return;

	if (hdcTemp)
	{
		HPALETTE hPalette1, hPalette2;
		if (hPalette)
		{
			hPalette1 = SelectPalette(hdc, hPalette, TRUE);
			hPalette2 = SelectPalette(hdcTemp, hPalette, TRUE);
        }
		POSITION pos = m_objects.GetHeadPosition();
		while (pos != NULL)
		{
			CMapObjectInst *pObject = m_objects.GetNext(pos);
			ASSERT(pObject != NULL);
            CRect irect, orect = GetObjectRect(pObject);

			if (irect.IntersectRect(orect, rect))
			{
				CPoint pt = pObject->m_location - offset;
				pObjectSet->DrawObject(hdc, pObject->m_ID, pt, hdcTemp, pDst,
					pObject->m_iSequence, pObject->m_iFrame, pObject->m_bFlipped);
				if (pObject->m_bSelected)
				{
					DrawObjectOutline(hdc, pt, orect.Size(), TRUE);
				}
			}
		}
		if (hPalette)
		{
			SelectPalette(hdc, hPalette1 , TRUE);
			SelectPalette(hdcTemp, hPalette2, TRUE);
		}
		DeleteDC(hdcTemp);
	}
	else
		TRACE0("CObjectLayer::Draw couldn't create temp dc\n");
}

CMapObjectInst * CObjectLayer::FindObjectAt(CPoint pt)
{
	POSITION pos = m_objects.GetTailPosition();
	while (pos != NULL)
	{
		CMapObjectInst *pObject = m_objects.GetPrev(pos);
		ASSERT(pObject);

		CRect rect(GetObjectRect(pObject));
		if (rect.PtInRect(pt))
			return pObject;
	}
	return NULL;
}

CRect CObjectLayer::GetObjectRect(CMapObjectInst *pInstance)
{
	CObjectSet *pObjectSet = GetObjectSet();
	ASSERT(pInstance != NULL);
    ASSERT(pObjectSet != NULL);

	CMapObject *pObject = pObjectSet->GetObject(pInstance->m_ID);
	ASSERT(pObject != NULL);

	// TBD: use object hotspot...
	return CRect(pInstance->m_location, 
		         pObject->GetSize(pInstance->m_iSequence, pInstance->m_iFrame)); 
}

void CObjectLayer::AddObject(CMapObjectInst *pObject) 
{ 
	m_objects.AddTail(pObject); 
}



CMapObjectInst * CObjectLayer::AddObject(int ID, CPoint pt)
{
	CMapObjectInst *pObject = new CMapObjectInst(ID, pt); // allocate it
	ASSERT_NEW(pObject);
	TRY
	{
		AddObject(pObject); // add it to the layer
	}
	CATCH_ALL(e)
	{
		delete pObject;
		pObject = NULL;
		THROW_LAST();
	}
	END_CATCH_ALL
	return pObject;
}

void CObjectLayer::OnUpdateMultipleObjects(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nSelected > 0);
}

void CObjectLayer::OnObjectTop() 
{
	POSITION pos2,pos1 = m_objects.GetHeadPosition();
    int iCount = m_objects.GetCount();
	
	// for each selected object (in back to front order)
	// move object to top of list 
	for (int i=0; i < iCount; i++)
	{
		pos2 = pos1; 
		CMapObjectInst *pObject = m_objects.GetNext(pos1);
		ASSERT(pObject != NULL);
		if (pObject->m_bSelected)
		{
		    m_objects.RemoveAt(pos2);
			m_objects.AddTail(pObject);
			pObject->m_bOutOfOrder = TRUE;
		}
	}	
	Invalidate(GetSelection());
}


void CObjectLayer::OnObjectBottom() 
{
	POSITION pos2,pos1 = m_objects.GetTailPosition();
    int iCount = m_objects.GetCount();

	// for each selected object (in front to back order)
	// move object to bottom of list 
	for (int i=0; i < iCount; i++)
	{
		pos2 = pos1; 
		CMapObjectInst *pObject = m_objects.GetPrev(pos1);
		ASSERT(pObject != NULL);
		if (pObject->m_bSelected)
		{
		    m_objects.RemoveAt(pos2);
			m_objects.AddHead(pObject);
			pObject->m_bOutOfOrder = TRUE;
		}
	}
	Invalidate(GetSelection());
}

void CObjectLayer::OnObjectForward() 
{
	POSITION pos1 = m_objects.GetHeadPosition();
	POSITION pos2,pos3,pos4;

	// move the selected object in front of the next overlapping
	// object or, if no overlapping objects, move it one position
	// forward in the list.
	while (pos1 != NULL)
	{
		pos2 = pos1; 
		CMapObjectInst *pObject = m_objects.GetNext(pos1);
		ASSERT(pObject != NULL);
		if (pObject->m_bSelected)
		{
			CRect objectRect = GetObjectRect(pObject);
			pos3 = pos1;
			while (pos3 != NULL)
			{
				pos4 = pos3;
				CMapObjectInst *pOverlap = m_objects.GetNext(pos3);
				ASSERT(pOverlap != NULL);
				CRect nextObRect = GetObjectRect(pOverlap);
				if (nextObRect.IntersectRect(nextObRect,objectRect))
				{
                    pos1 = pos4;
					break;
				}
			}
			m_objects.RemoveAt(pos2);
			m_objects.InsertAfter(pos1,pObject);
			pObject->m_bOutOfOrder = TRUE;
			Invalidate(objectRect);
			return;
		}
	}
}

void CObjectLayer::OnUpdateSingleObject(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nSelected == 1);
}

void CObjectLayer::OnObjectBack() 
{
	POSITION pos1 = m_objects.GetTailPosition();
	POSITION pos2,pos3,pos4;

	// move the selected object behind the previous overlapping
	// object or, if no overlapping objects, move it one position
	// backward in the list.
	while (pos1 != NULL)
	{
		pos2 = pos1; 
		CMapObjectInst *pObject = m_objects.GetPrev(pos1);
		ASSERT(pObject != NULL);
		if (pObject->m_bSelected)
		{
			CRect objectRect = GetObjectRect(pObject);
			pos3 = pos1;
			while (pos3 != NULL)
			{
				pos4 = pos3;
				CMapObjectInst *pOverlap = m_objects.GetPrev(pos3);
				ASSERT(pOverlap != NULL);
				CRect nextObRect = GetObjectRect(pOverlap);
				if (nextObRect.IntersectRect(nextObRect,objectRect))
				{
                    pos1 = pos4;
					break;
				}
			}
		    m_objects.RemoveAt(pos2);
			m_objects.InsertBefore(pos1,pObject);
			pObject->m_bOutOfOrder = TRUE;
			Invalidate(objectRect);
			return;
		}
	}
	
}

void CObjectLayer::MoveSelection(int dx, int dy)
{
	CMapObjectInst *pInstance = GetSelected();
	if (pInstance)
	{
		// optimize for one known object
		InvalidateOb(pInstance);
		pInstance->m_location.x += dx;
		pInstance->m_location.y += dy;
		InvalidateOb(pInstance);
		UpdateItemPos(pInstance->m_location); // update x,y
	}
	else
	{
		POSITION pos = m_objects.GetHeadPosition();
		while (pos != NULL)
		{
			CMapObjectInst *pObject = m_objects.GetNext(pos);
			ASSERT(pObject != NULL);
			if (pObject->m_bSelected)
			{
				InvalidateOb(pObject);
				pObject->m_location.x += dx;
				pObject->m_location.y += dy;
				InvalidateOb(pObject);
				m_pLastObject = pObject; 
			}
		}
		UpdateItemPos(); // erase x,y
	}
	SetModifiedFlag();
}

void CObjectLayer::OnObjectLeft() 
{
   MoveSelection(-1,0);	
}

void CObjectLayer::OnObjectRight() 
{
	MoveSelection(1,0);
}

void CObjectLayer::OnObjectUp() 
{
	MoveSelection(0,-1);
}

void CObjectLayer::OnObjectDown() 
{
	MoveSelection(0,1);
}

void CObjectLayer::DoCutCopyPaste(CArchive &ar, BOOL bCut)
{
	CMapObjectInst *pObject;

	// Note: when objects are pasted into an object layer,
	// a new instance of that object is created therefore
	// the attributes for this new instance are NOT explicitly
	// set so there is no need to copy/paste object attributes.

	if (ar.IsStoring())
	{
		ar << m_nSelected;
		POSITION pos = m_objects.GetHeadPosition();
		while (pos != NULL)
		{
			pObject = m_objects.GetNext(pos);
			ASSERT(pObject != NULL);
			if (pObject->m_bSelected)
				ar << pObject;
		}
	}
	else
	{
		CObjectSet *pObjectSet = GetObjectSet();
		int iObjectCount = pObjectSet ? pObjectSet->GetObjectCount() : 0;

		SelectNone();
		ar >> m_nSelected;
		for (UINT n=0; n < m_nSelected; n++)
		{
			ar >> pObject;
			TRY
			{
				if (pObject->m_ID >= 0 && pObject->m_ID < iObjectCount)
				{
					AddObject(pObject);
					pObject->m_bSelected = TRUE;
				}
				else
				{
					delete pObject;
					m_nSelected -= 1;
				}
			}
			CATCH_ALL(e)
			{
				delete pObject;
				m_nSelected -= 1;
				THROW_LAST();
			}
			END_CATCH_ALL
		}
	}
	
	CRect rect = GetSelection();
	if (bCut)
	{
		ASSERT(ar.IsStoring());
  		POSITION pos,doomed;
		for(pos = m_objects.GetHeadPosition(); (doomed = pos) != NULL;)
		{
			pObject = m_objects.GetNext(pos);
			ASSERT(pObject != NULL);
			if (pObject->m_bSelected)
			{	
				RemoveObjectAt(doomed);
				delete pObject;
			}
		}
		m_nSelected = 0;
		m_pLastObject = NULL;
	}
	// updated view and flag as modified if cut or paste operation
	if (!(ar.IsStoring() && !bCut))
	{
	    Invalidate(rect); 
		SetModifiedFlag();
	}
	UpdateSelectedStatus();
}

void CObjectLayer::DoCutCopy(BOOL bCut) 
{
	if (OpenClipboard())
	{
		EmptyClipboard();
		TRY
		{
			CSharedFile	memFile;
			CArchive ar(&memFile, CArchive::store|CArchive::bNoFlushOnDelete);

			DoCutCopyPaste(ar, bCut);
			ar.Flush();

			HGLOBAL hData = memFile.Detach();
			::SetClipboardData(g_nObjectLayerFormat, hData);
			CloseClipboard();
		}
		CATCH_ALL(e)
		{
			CloseClipboard();
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	else
		AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
}

void CObjectLayer::OnEditCut() 
{
	DoCutCopy(TRUE);
}

void CObjectLayer::OnEditCopy() 
{
	DoCutCopy(FALSE);	
}

void CObjectLayer::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(::IsClipboardFormatAvailable(g_nObjectLayerFormat));	
}

void CObjectLayer::OnEditPaste() 
{
	if (OpenClipboard())
	{
		CSharedFile memFile;
		TRY
		{
			HANDLE hData = ::GetClipboardData(g_nObjectLayerFormat);
			if (hData != NULL)
			{
				memFile.SetHandle(hData,FALSE);
				CArchive ar(&memFile, CArchive::load|CArchive::bNoFlushOnDelete);
				DoCutCopyPaste(ar, FALSE);
			}
			else
				AfxMessageBox(CG_IDS_CANNOT_GET_CLIPBOARD_DATA);
			CloseClipboard();
			memFile.Detach(); // so global ptr gets unlocked and doesn't get deallocated
		}
		CATCH_ALL(e)
		{
			CloseClipboard();
			memFile.Detach();
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	else
		AfxMessageBox(CG_IDS_CANNOT_OPEN_CLIPBOARD);
	
}





void CObjectLayer::OnUpdateEditFind(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetCurrentItem() >= 0);
}

void CObjectLayer::OnEditFind() 
{
	int iCurrentItem = GetCurrentItem();
	ASSERT(iCurrentItem >= 0);

	SelectNone();
	CRect selection;
	selection.SetRectEmpty();

	POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
	{
		CMapObjectInst *pObject = m_objects.GetNext(pos);
		ASSERT(pObject != NULL);
		if (pObject->m_ID == iCurrentItem)
		{
		    selection.UnionRect(selection,GetObjectRect(pObject));
			pObject->m_bSelected = TRUE;
			++m_nSelected;
		}
	}
	Invalidate(selection);

	TRY
	{
		CString status;
		status.Format(IDS_ITEMS_FOUND_FORMAT,m_nSelected);
		ShowStatus(status);
	}
	END_TRY
}



void CObjectLayer::OnUpdateEditReplace(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_objects.IsEmpty());
}

void CObjectLayer::OnEditReplace() 
{
	if (g_pReplaceDlg == NULL)
	{
		g_pReplaceDlg = new CFindReplaceDialog;
		ASSERT_NEW(g_pReplaceDlg);
		CMapFrame *pParent = GetParentFrame();
		ASSERT(pParent != NULL);
		CString name;
		LPCTSTR lpname = NULL;
		CMapObjectInst *pInstance = GetSelected();
		if (pInstance)
		{
           name = GetObjectSet()->GetObject(pInstance->m_ID)->GetName();
		   lpname = name;
		}
		if (!g_pReplaceDlg->Create(FALSE,lpname,NULL,FR_ENABLEHOOK|FR_DOWN|FR_HIDEMATCHCASE|FR_NOMATCHCASE,pParent))
		{
			delete g_pReplaceDlg;
			g_pReplaceDlg = NULL;
			AfxThrowMemoryException();
		}
	}
	if (g_pReplaceDlg)
	{
		g_pReplaceDlg->SetForegroundWindow();
		m_pLastObject = NULL;
	}
}

afx_msg LRESULT CObjectLayer::OnFindReplace(WPARAM wParam, LPARAM lParam)
{
	TRACE("Got Find/Replace message: %x %x\n", wParam, lParam);

	ASSERT_VALID(this);
	CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);
	ASSERT(pDialog != NULL);
	ASSERT(pDialog == g_pReplaceDlg);
	if (pDialog->IsTerminating())
	{
		TRACE0("find/replace terminating\n");
		g_pReplaceDlg = NULL;
	}
	else if (pDialog->FindNext())
	{
		OnFindNext(pDialog->GetFindString(), 
			pDialog->SearchDown(), pDialog->MatchWholeWord());
	}
	else if (pDialog->ReplaceCurrent())
	{
		OnReplace(pDialog->GetFindString(),
			pDialog->GetReplaceString(), pDialog->MatchWholeWord(), TRUE);
	}
	else if (pDialog->ReplaceAll())
	{
		OnReplace(pDialog->GetFindString(), pDialog->GetReplaceString(),
			pDialog->MatchWholeWord(), FALSE);
	}
	ASSERT_VALID(this);
	return 0;
}

void CObjectLayer::OnFindNext(CString match, BOOL bSearchDown, BOOL bWholeWord)
{
	TRACE("find next: %s, searchDown = %d, wholeword = %d\n", match, bSearchDown, bWholeWord);
    CMapObjectInst *pObject = m_pLastObject;
    match.MakeLower();
	POSITION pos;

    SelectNone();
	if (pObject == NULL)
	{
		if (bSearchDown)
			pos = m_objects.GetHeadPosition();
		else
			pos = m_objects.GetTailPosition();
	}
	else
	{
		pos = m_objects.Find(pObject);
		if (bSearchDown)
			m_objects.GetNext(pos);
		else
			m_objects.GetPrev(pos);
	}

	CString name;
	while (pos != NULL)
	{   
		if (bSearchDown)
			m_pLastObject = m_objects.GetNext(pos);
		else
			m_pLastObject = m_objects.GetPrev(pos);
		
		if (m_pLastObject)
		{
			CMapObject *pMapObject = GetObjectSet()->GetObject(m_pLastObject->m_ID);
			ASSERT(pMapObject != NULL);
			name = pMapObject->GetName();
		    if (bWholeWord)
			{
				if (name.Compare(match) != 0)
					continue;
			}
			else
			{
				if (name.Find(match) == -1)
					continue;
			}
			CRect rect = GetObjectRect(m_pLastObject);
			GetMap()->UpdateAllViews(NULL,MEV_UPDATE_POSITION,&CMapUpdate(rect));
			m_pLastObject->m_bSelected = TRUE;
			m_nSelected += 1;
			UpdateItemPos(m_pLastObject->m_location);
			Invalidate(rect);
			return;
		}
		else
			MessageBeep(MB_ICONSTOP);
	}
}

void CObjectLayer::OnReplace(CString pszFind,  CString pszReplace, BOOL bWholeWord, BOOL bSelectedOnly)
{
   if (bSelectedOnly && m_nSelected == 0)
	   return;
#if 0
   // TBD: this gets annoying if you're doing successive find and replace operations.
   if (GetMap()->IsModified())
	   UserWarn(IDS_CANT_UNDO_REPLACE);
#endif
	   
   BeginWaitCursor();
   TRY
   {
// removed 3/26/97 NAR; no longer keying on folder name
//	   int iReplaceId = pszReplace.Find('\\');
//	   CString id;
//	   if (iReplaceId >= 0)
//	   {
//		   id = pszReplace.Left(iReplaceId + 1);
//		   pszReplace = pszReplace.Right( pszReplace.GetLength() - iReplaceId - 1);
//	   }

	   POSITION pos = m_objects.GetHeadPosition();
	   pszFind.MakeLower();
	   int iFindLen = pszFind.GetLength();
	   int iIndex;
	   pszReplace.MakeLower();
	   while (pos != NULL)
	   {
			CMapObjectInst *pObject = m_objects.GetNext(pos);
			ASSERT(pObject != NULL);
			if (bSelectedOnly && !pObject->m_bSelected)
				continue;
			CMapObject *pMapObject = GetObjectSet()->GetObject(pObject->m_ID);
			CString name = pMapObject->GetName();
			if (bWholeWord)
			{
				if (name.Compare(pszFind) != 0)
					continue;
				iIndex = 0;
			}
			else
			{
				iIndex = name.Find(pszFind);
				if (iIndex < 0)
					continue;
			}
// removed 3/26/97 NAR; no longer keying on folder name
//			if (iReplaceId < 0)
//			{
//				id = pMapObject->GetKey();
//				int iSeperator = id.ReverseFind('\\');
//				ASSERT(iSeperator >= 0);
//				id = id.Left(iSeperator + 1);
//			}
            CString remains = name;

			// TBD: only replace all occurrences of string if we're doing a pattern
			// replacement.
			do
			{
				CString newName = name.Left(iIndex);
				remains = name.Right( name.GetLength() - newName.GetLength() - iFindLen);
				newName += pszReplace;
				iIndex = remains.Find(pszFind);
                if (iIndex >= 0) 
					iIndex += newName.GetLength();			
				newName += remains;
				name = newName;
			} while (iIndex >= 0);

// changed 3/26/97 NAR; no longer keying on folder name
//			name = id + name + ".bmp";
			name = name + ".bmp";
			pObject->m_ID = GetObjectSet()->FindObject(name,TRUE);
			InvalidateOb(pObject);
			GetMap()->SetModifiedFlag();
	   }
	   if (bSelectedOnly && m_nSelected == 1)
		   OnFindNext(pszFind, TRUE /* TBD */, bWholeWord);
   }
   CATCH_ALL(e)
   {
		EndWaitCursor();
		THROW_LAST();
   }
   END_CATCH_ALL
   EndWaitCursor();
}

void CObjectLayer::OnEditSelectAll() 
{
	if (m_nSelected < (UINT)GetObjectCount())
	{
	   m_pLastObject = NULL;
	   POSITION pos = m_objects.GetHeadPosition();
	   while (pos != NULL)
	   {
		   CMapObjectInst *pObject = m_objects.GetNext(pos);
		   ASSERT(pObject != NULL);
		   if (pObject->m_bSelected != TRUE)
		   {
				pObject->m_bSelected = TRUE;
				++m_nSelected;
				InvalidateOb(pObject);
		   }
	   }
	   ASSERT(m_nSelected == (UINT)GetObjectCount());
	   UpdateSelectedStatus();
	}

}

void CObjectLayer::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetObjectCount() > 0);
}

void CObjectLayer::UpdateSelectedStatus()
{
	TRY
	{
		CString status;
		status.Format(IDS_ITEMS_SELECTED_FORMAT,m_nSelected);
		ShowStatus(status);
	}
	END_TRY
}



UINT CObjectLayer::CountOccurrences(int iObjectID)
{
   POSITION pos = GetFirstObjectPosition();
   UINT nTotal = 0;

   while (pos != NULL)
   {
	   CMapObjectInst *pObject = GetNextObject(pos);
	   ASSERT(pObject);
	   
	   if (pObject->m_ID == iObjectID)
		   ++nTotal;
   }
   return nTotal;
}

void CObjectLayer::ForceInside(CMapObjectInst *pInstance)
{
	CRect rect = GetObjectRect(pInstance);
	BOOL bModified = FALSE;
	if (m_pMap)
	{
		CSize size = m_pMap->GetSize();
		if (rect.right > size.cx)
		{
			rect.OffsetRect(size.cx - rect.right, 0);
			bModified = TRUE;
		}
		if (rect.bottom > size.cy)
		{
			rect.OffsetRect(0, size.cy - rect.bottom);
			bModified = TRUE;
		}
	}
    if (rect.left < 0)
	{
		rect.OffsetRect(-rect.left,0);
		bModified = TRUE;
	}
	if (rect.top < 0)
	{
		rect.OffsetRect(0,-rect.top);
		bModified = TRUE;
	}
	if (bModified)
	{
		InvalidateOb(pInstance);
		pInstance->m_location = rect.TopLeft();
		InvalidateOb(pInstance);
		SetModifiedFlag();
	}
}

int CObjectLayer::GetAttributeCount()
{
	return GetMap()->GetAttributeCount();
}

POSITION CObjectLayer::GetFirstAttribute()
{
	return GetMap()->GetFirstAttribute();
}

CPoint CObjectLayer::GetHotSpot(CMapObjectInst *pInstance)
{
    CObjectSet *pObjectSet = GetObjectSet();
	ASSERT(pObjectSet != NULL);
    CMapObject *pObject = pObjectSet->GetObject(pInstance->m_ID);
	ASSERT(pObject != NULL);
	CPoint hotSpot = pObject->GetHotSpot(pInstance->m_iSequence, 
		pInstance->m_iFrame, pInstance->m_bFlipped);
	hotSpot += pInstance->m_location;
	return hotSpot;
}

void CObjectLayer::GetNextAttribute(POSITION& pos, void *pTargetData, CAttributeInfo& rInfo)
{
	CAttributeLayer *pLayer = GetMap()->GetNextAttribute(pos);
	ASSERT(pLayer != NULL);

	CMapObjectInst *pInstance = (CMapObjectInst *)pTargetData;
	pLayer->GetObjectAttribute(pInstance,GetHotSpot(pInstance),rInfo);
}

void CObjectLayer::OnUpdateObjectAttributes(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(m_nSelected > 0 && m_pMap);
	if (NULL != m_pMap)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

// TBD: this should be part of AssertValid and not a seperate method.
BOOL CObjectLayer::GetLastSelected()
{
   if (m_nSelected > 0)
   {
	   if (!m_pLastObject || m_pLastObject->m_bSelected == FALSE)
	   {
		   POSITION pos = GetFirstObjectPosition();
		   while (pos != NULL)
		   {
			   m_pLastObject = GetNextObject(pos);
			   if (m_pLastObject->m_bSelected)
				   break;
		   }
	   }
   }
   else
	   m_pLastObject = NULL;

   return (m_pLastObject && m_pLastObject->m_bSelected);
}

void CObjectLayer::OnObjectAttributes() 
{
   CAnimPropPage *pAnimPropPage = NULL;
   CTextPage *pTextPage = NULL;
   CObjectSet *pObjectSet = GetObjectSet();
   //VERIFY(GetLastSelected());
   if (FALSE == GetLastSelected())
	   return;

   CAnimMapObject *pAnimObject = DYNAMIC_DOWNCAST(CAnimMapObject, 
	   pObjectSet->GetObject(m_pLastObject->m_ID));
	   
   CAttributeSheet dlg(IDS_OBJECT,this,(void *)m_pLastObject, NULL);
   TRY
   {
	   if (pAnimObject)
	   {
			pAnimPropPage = new CAnimPropPage(pObjectSet, pAnimObject, 
								m_pLastObject->m_iSequence, m_pLastObject->m_iFrame);
			dlg.AddPage(pAnimPropPage);
	   }

		pTextPage = new CTextPage();
		pTextPage->m_sTextBlock = m_pLastObject->m_sTextBlock;
		dlg.AddPage(pTextPage);

	   if (dlg.DoModal() == IDOK)
	   {
		   m_pLastObject->m_sTextBlock = pTextPage->m_sTextBlock;
		   CMapEditorDoc *pMap = GetMap();
			ASSERT(pMap->GetAttributeCount() == dlg.m_pAttributePage->m_attributes.GetSize());

			// adjust the object attributes of all selected objects
			POSITION pos = pMap->GetFirstAttribute();
			int iIndex = 0;
			while (pos != NULL)
			{
				CAttributeLayer *pLayer = pMap->GetNextAttribute(pos);
				ASSERT(pLayer != NULL);

				POSITION opos = GetFirstObjectPosition();
				while (opos != NULL)
				{
					CMapObjectInst *pInstance = GetNextObject(opos);
					ASSERT(pInstance != NULL);
					if (pInstance->m_bSelected)
					{
						pLayer->AdjustObjectAttribute(pInstance,dlg.m_pAttributePage->m_attributes[iIndex]);
						InvalidateOb(pInstance); // in case object has or had visible attributes.
					}
				}
				++iIndex;
			}
			// adjust the anim attributes of all selected objects
			if (pAnimPropPage)
			{
				POSITION opos = GetFirstObjectPosition();
				while (opos != NULL)
				{
					CMapObjectInst *pInstance = GetNextObject(opos);
					ASSERT(pInstance != NULL);
					if  (pInstance->m_bSelected)
					{
						CMapObject *pObject = pObjectSet->GetObject(pInstance->m_ID);
						if (pAnimPropPage->m_iSequence < pObject->GetSequenceCount())
							pInstance->m_iSequence = pAnimPropPage->m_iSequence;
						if (pAnimPropPage->m_iFrame < pObject->GetFrameCount(pInstance->m_iSequence))
							pInstance->m_iFrame = pAnimPropPage->m_iFrame;
						InvalidateOb(pInstance); // in case object size changed
					}
				}
			}
			SetModifiedFlag();
	   }

	   delete pAnimPropPage;
	   delete pTextPage;
   }
   CATCH_ALL(e)
   {
	   delete pAnimPropPage;
	   delete pTextPage;
	   THROW_LAST();
   }
   END_CATCH_ALL
}


void CObjectLayer::OnUpdateObjectSort(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_objects.IsEmpty()); 
}



void CObjectLayer::OnObjectSort() 
{
	// SAMPLE SORTING ROUTINE

	CTypedPtrList<CObList,CMapObjectInst *> tmpList;
	TRY
	{
		// sorts objects according to their y position
	   TRACE0("BEFORE SORT:\n");
	   while (!m_objects.IsEmpty())
	   {
		   CMapObjectInst *pObject = m_objects.RemoveHead();
		   ASSERT(pObject != NULL);
		   pObject->m_bOutOfOrder = FALSE;
           TRACE("\t%d,%d\n",pObject->m_location.x,pObject->m_location.y);
		   // simple insertion sort
		   POSITION pos = tmpList.GetHeadPosition();
		   while (pos != NULL && pObject)
		   {
			   CMapObjectInst *pListOb = tmpList.GetAt(pos);
			   if ((pObject->m_location.y < pListOb->m_location.y) ||
				   ((pObject->m_location.y == pListOb->m_location.y) &&
				    (pObject->m_location.x <= pListOb->m_location.x)))
			   {
				   tmpList.InsertBefore(pos,pObject);
				   pObject = NULL;
			   }
			   else
				   tmpList.GetNext(pos);
		   }
		   if (pObject)
			   tmpList.AddTail(pObject);
		  
	   }
	   // copy sorted list to object list
	   TRACE0("AFTER:\n");
       while (!tmpList.IsEmpty())
	   {
	       CMapObjectInst *pObject = tmpList.RemoveHead();
		   ASSERT(pObject != NULL);
		   m_objects.AddTail(pObject);
		   TRACE("\t%d,%d\n",pObject->m_location.x,pObject->m_location.y);
	   }
	   Invalidate(NULL); // redraw everything
   }
   CATCH_ALL(E)
   {
	   TRACE0("caught error during sort, trying to restore object list\n");
	   TRY
	   {
			while (!tmpList.IsEmpty())
				m_objects.AddTail(tmpList.RemoveHead());
			Invalidate(NULL);
	   }
	   END_TRY
	   THROW_LAST();
   }
   END_CATCH_ALL
}


void CObjectLayer::OnObjectFlipHorizontal() 
{
	ASSERT(m_nSelected >= 1);
    POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
	{
		CMapObjectInst *pInstance = m_objects.GetNext(pos);
		if (pInstance->m_bSelected)
		{
			pInstance->m_bFlipped = !pInstance->m_bFlipped;
			InvalidateOb(pInstance);
		}
	}
}


CMapObjectInst * CObjectLayer::GetSelected()
{
	if (m_nSelected == 1 && m_pLastObject && m_pLastObject->m_bSelected)
		return m_pLastObject;
	return NULL;
}


void CObjectLayer::SingleStep()
{
	CObjectSet *pObjectSet = GetObjectSet();
	CRect rect;

	rect.SetRectEmpty();
	POSITION pos = GetFirstObjectPosition();
	while (pos != NULL)
	{
		CMapObjectInst *pInstance = GetNextObject(pos);
		ASSERT(pInstance);

		CMapObject *pObject = pObjectSet->GetObject(pInstance->m_ID);
		ASSERT(pObject);

		int iFrameCount = pObject->GetFrameCount(pInstance->m_iSequence);
		if (iFrameCount > 0)
		{
			// TBD: use timer
			rect.UnionRect(&rect, &GetObjectRect(pInstance));
			pInstance->m_iFrame += 1;
			if (pInstance->m_iFrame >= iFrameCount)
				pInstance->m_iFrame = 0;
			rect.UnionRect(&rect, &GetObjectRect(pInstance));
		}
	}
	if (!rect.IsRectEmpty())
		m_pMap->UpdateAllViews(NULL,NULL,&CMapUpdate(rect));
}

BOOL CObjectLayer::LoadDefaults(CMapObjectInst * pObj, CObjectSetView *pView)
{
	// Iterate through each attribute layer in the map, after each iteration - iterate through defs
	CPtrList sDefList;
	CFile sDefile;
	CString sObjDir;
	TC_ITEM sReq;
	DefAtr *pAtr=NULL;
	POSITION pPos;
	POSITION pPos2;
	CAttributeInfo pInfo;
	CAttributeLayer *pLayer=NULL;
	char rcBuf[256];
	
	int iDefs=0;
	int iCur=0;

	sObjDir = *GetMap()->GetObjectPath();
	sObjDir += '\\';
	sReq.mask = TCIF_TEXT;
	sReq.pszText = (LPSTR)&rcBuf;
	sReq.cchTextMax = sizeof(rcBuf);
	if (FALSE == pView->m_tabCtrl.GetItem(pView->m_tabCtrl.GetCurSel(), &sReq))
		return FALSE;
	sObjDir += rcBuf;
	sObjDir += "\\default.bin";

	if (FALSE == sDefile.Open(sObjDir, CFile::modeReadWrite|CFile::shareDenyWrite, NULL))
		return FALSE;

	if (sizeof(int) != sDefile.Read(&iDefs, sizeof(int)))
	{
		sDefile.Close();
		return FALSE;
	}

	if (iDefs <= 0)
		return FALSE;

	while (iCur < iDefs)
	{
		pAtr = new DefAtr;
		if (sizeof(DefAtr) != sDefile.Read(pAtr, sizeof(DefAtr)))
			break;

		// Add to list
		sDefList.AddTail(pAtr);
		iCur++;
	}

	// Now Cross-Reference
	pPos = GetFirstAttribute();

	while (NULL != pPos)
	{
		pLayer = GetMap()->GetNextAttribute(pPos);
		pLayer->GetObjectAttribute(pObj,GetHotSpot(pObj), pInfo);

		// Search Defaults
		pPos2 = sDefList.GetHeadPosition();
		while (NULL != pPos2)
		{
			pAtr = (DefAtr*)sDefList.GetNext(pPos2);
			if (NULL != pAtr)
			{
				if (0 == lstrcmpi((LPCTSTR)(LPSTR)&pAtr->rcName, pInfo.m_pszName))
				{
					pInfo.SetMaxValue(pAtr->iMax);
					pInfo.SetDefaultValue(pAtr->iDefValue);
					pInfo.SetBitCount(pAtr->iBits);
					pInfo.SetValue(pAtr->iValue);
					pLayer->AdjustObjectAttribute(pObj, pInfo);
					break;
				}
			}
		}
	}

	pPos2 = sDefList.GetHeadPosition();
	while (NULL != pPos2)
	{
		pAtr = (DefAtr*)sDefList.GetNext(pPos2);
		delete pAtr;
	}
	sDefList.RemoveAll();

	sDefile.Close();

	return TRUE;
}

int CObjectLayer::GetSelCount()
{
	return m_nSelected;
}
