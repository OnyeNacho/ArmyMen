// MapEditorDoc.cpp : implementation of the CMapEditorDoc class
//
// Note: for now, the map/layers keeps track of all selections so both the
// MapEditorView and the MapOverview can display the selection.  We'll have
// change this if the artists need the selections work on a view by view 
// basis.
//
#include "stdafx.h"
#include "MapEditor.h"
#include "MainFrm.h"
#include "MapEditorDoc.h"
#include "NewMapDlg.h"
#include "TileLayer.h"
#include "MapUpdate.h"
#include "ObjectLayer.h"
#include "MapBmpDlg.h"
#include "LayersDlg.h"
#include "IFFFile.h"
#include "AttributeLayer.h"
#include "NewAttributeDlg.h"
#include "ScenarioLayer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////
CTileLayer *g_pTileLayer = NULL;	 // target for generating new map from tileset

IMPLEMENT_DYNAMIC(CMapUpdate, CObject)

/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc

BEGIN_MESSAGE_MAP(CMapEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CMapEditorDoc)
	ON_COMMAND(ID_FILE_REVERT, OnFileRevert)
	ON_UPDATE_COMMAND_UI(ID_FILE_REVERT, OnUpdateFileRevert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CROP, OnUpdateEditCrop)
	ON_COMMAND(ID_EDIT_CROP, OnEditCrop)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_NONE, OnUpdateEditSelectNone)
	ON_COMMAND(ID_EDIT_SELECT_NONE, OnEditSelectNone)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_UPDATE_COMMAND_UI(ID_EDIT_WITHATTRIBUTES, OnUpdateEditWithAttributes)
	ON_COMMAND(ID_EDIT_WITHATTRIBUTES, OnEditWithAttributes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_LAYERS_ACTIVATETOP, OnUpdateLayersActivate)
	ON_COMMAND(ID_LAYERS_ACTIVATETOP, OnLayersActivateTop)
	ON_COMMAND(ID_LAYERS_ACTIVATEBOTTOM, OnLayersActivateBottom)
	ON_COMMAND(ID_LAYERS_ACTIVATENEXT, OnLayersActivateNext)
	ON_COMMAND(ID_LAYERS_ACTIVATEPREVIOUS, OnLayersActivatePrevious)
	ON_COMMAND(ID_LAYERS_ARRANGE, OnLayersArrange)
	ON_UPDATE_COMMAND_UI(ID_LAYERS_ACTIVATEBOTTOM, OnUpdateLayersActivate)
	ON_UPDATE_COMMAND_UI(ID_LAYERS_ACTIVATENEXT, OnUpdateLayersActivate)
	ON_UPDATE_COMMAND_UI(ID_LAYERS_ACTIVATEPREVIOUS, OnUpdateLayersActivate)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc construction/destruction

CMapEditorDoc::CMapEditorDoc()
{
    InitContents();
}

void CMapEditorDoc::InitContents()
{
	m_iMapHeight = 0;
	m_iMapWidth = 0;
	m_pActiveLayer = NULL;
	m_bNeedsUpdate = FALSE;
	m_bOldDataFormat = FALSE;
	m_bGrid = FALSE;

	m_pObjectSet = NULL;
	m_pszObjectSetPath.Empty();

	m_pTileSet = NULL;
	m_pszTileSetPath.Empty();
	
	m_pScenarioSet = NULL;
	m_pszScenarioSetPath.Empty();

	m_pszDescription.Empty();
	m_rgbBackground = RGB(255,255,255); // for backward compatibility

	m_previewRect.SetRectEmpty();
	m_bAnimating = FALSE;

	m_iBX = 0;
	m_iBY = 0;
	m_iEX = 0;
	m_iEY = 0;
}

CMapEditorDoc::~CMapEditorDoc()
{
	TRACE("Map \"%s\" has been destroyed\n", m_strTitle);
	// the rest is handled by DeleteContents()
}

void CMapEditorDoc::DeleteLayers()
{
	CMapLayer *pLayer;
	while (!m_layers.IsEmpty())
	{
		pLayer = m_layers.RemoveHead();
		delete pLayer; 
	}
	m_pActiveLayer = NULL;
}

void CMapEditorDoc::DeleteContents()
{
	if (m_pTileSet) 
	{
		m_pTileSet->RemoveMap(this);
		m_pTileSet = NULL;
	}
	if (m_pObjectSet) 
	{
		m_pObjectSet->RemoveMap(this);
		m_pObjectSet = NULL;
	}
	if (m_pScenarioSet)
	{
		m_pScenarioSet->RemoveMap(this);
		m_pScenarioSet = NULL;
	}
	DeleteLayers();
	CDocument::DeleteContents();
	InitContents();
}


CMapLayer *CMapEditorDoc::FindLayer(const CString& title)
{
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CMapLayer *pLayer = m_layers.GetNext(pos);
		ASSERT(pLayer != NULL);
		if (title.CompareNoCase(pLayer->GetTitle()) == 0)
			return pLayer;
	}
	return NULL;
}

CString CMapEditorDoc::NewLayerName(int iLayerNameID)
{
	CString title;
	title.LoadString(iLayerNameID);
	CString newTitle = title;
    int iCount = 2;

	while (FindLayer(newTitle))
	{
		newTitle.Format("%s%d",title,iCount++);
	}
	return newTitle;
}


CTileLayer *CMapEditorDoc::CreateTileLayer(int iLayerNameID,BOOL bTransparent,int defaultTile)
{
	CTileLayer *pLayer = NULL;

	TRY
	{
		CString newTitle = NewLayerName(iLayerNameID);
		pLayer = new CTileLayer(this,newTitle,bTransparent,defaultTile);
		ASSERT_NEW(pLayer);
		pLayer->SetVisible(TRUE);
		AddLayer(pLayer);
		if (defaultTile >= 0)
			UpdateAllViews(NULL);
	}
	CATCH_ALL(e)
	{
		delete pLayer;
		pLayer = NULL;
		THROW_LAST();
	}
	END_CATCH_ALL
	return pLayer;
}


BOOL CMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CNewMapDlg dlg;
	if (dlg.DoModal() != IDOK)
		return FALSE;
	
	m_iMapWidth = dlg.m_iNewWidth;
	m_iMapHeight = dlg.m_iNewHeight;
	m_pszTileSetPath = dlg.m_pszTileSet; 
	m_pszObjectSetPath = dlg.m_pszObjectSet;
	m_rgbBackground = dlg.m_rgbColor;
	m_pszDescription = dlg.m_pszDescription;
	g_pTileLayer = CreateBaseLayer();
	return InitDocument();
}

BOOL CMapEditorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	BOOL bOpened = CDocument::OnOpenDocument(lpszPathName);

	if (!bOpened && !g_bOldDataFormat)
	{
		g_bOldDataFormat = TRUE;
		bOpened = OnOpenDocument(lpszPathName);
    }
    if (bOpened)
		bOpened = InitDocument();
    
	g_bOldDataFormat = FALSE; // reset for future opens
	return bOpened;
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc serialization

#define MAPDOC_VERSION 6
IMPLEMENT_SERIAL(CMapEditorDoc, CDocument, VERSIONABLE_SCHEMA | MAPDOC_VERSION)
/*   
** Note: internally the map uses 0 to mean no tile, negative numbers to
** mean a selected tile, and positive numbers to mean a non-selected tile.
** When the map is serialized to disk, we just store the actual tile
** indices (0...ntiles-1)
**/
void CMapEditorDoc::Serialize(CArchive& ar)
{
	BuildObjectTable();
	CDocument::Serialize(ar);
	if (ar.IsStoring())
	{
		PUT_SAFE_SCHEMA(ar, CMapEditorDoc); 
		ar << m_iMapWidth;
		ar << m_iMapHeight;
		ar << m_pszTileSetPath;
		m_layers.Serialize(ar); 
		ar << m_pszObjectSetPath;     // schema >= 2
		m_objectTable.Serialize(ar);  // schema >= 2
		ar << m_pszScenarioSetPath;   // schema >= 3
		ar << m_pszDescription;       // schema >= 4
		ar << m_rgbBackground;        // schema >= 4
		ar << m_sAFile;
		ar << m_sPFile;
		ar << m_sAText;
		ar << m_sPText;
		ar << m_iBX;
		ar << m_iBY;
		ar << m_iEX;
		ar << m_iEY;
	}
	else 
	{
		UINT schema = GET_SAFE_SCHEMA(ar, CMapEditorDoc, 1);
		ar >> m_iMapWidth;
		ar >> m_iMapHeight;
		if (schema < 1) 	// for backward compatibility
		{
			CTileLayer *pLayer = CreateBaseLayer();
			int iTile;
			for (int iRow = 0; iRow < m_iMapHeight; iRow++)
			{
				for (int iCol = 0; iCol < m_iMapWidth; iCol++)
				{
					ar >> iTile;
					pLayer->SetTile(iRow,iCol,iTile);
				}
			}
			ar.ReadString(m_pszTileSetPath); // it was written with ar.WriteString()
			m_bOldDataFormat = TRUE;
			return;	
		}
	
		ASSERT(schema >= 1);
		ar >> m_pszTileSetPath; // ar.ReadString/WriteString get access violations.
		m_layers.Serialize(ar);
		POSITION pos = m_layers.GetHeadPosition();
		while (pos != NULL)
		{
			m_layers.GetNext(pos)->SetMap(this);
		}
		if (schema >= 2)
		{
			ar >> m_pszObjectSetPath;
			m_objectTable.Serialize(ar);
		}
		if (schema >= 3)
		{
			ar >> m_pszScenarioSetPath;
		}
		if (schema >= 4)
		{
			ar >> m_pszDescription;
			ar >> m_rgbBackground;
		}
		if (schema >= 5)
		{
			ar >> m_sAFile;
			ar >> m_sPFile;
			ar >> m_sAText;
			ar >> m_sPText;
		}
		if (schema >= 6)
		{
			ar >> m_iBX;
			ar >> m_iBY;
			ar >> m_iEX;
			ar >> m_iEY;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc diagnostics

#ifdef _DEBUG
void CMapEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc commands

BOOL CMapEditorDoc::InitDocument()
{
    if (m_iMapWidth > 0 && 
		m_iMapHeight > 0 &&
		UseTileSet(m_pszTileSetPath) && 
		UseObjectSet(m_pszObjectSetPath) &&
		UseScenarioSet(m_pszScenarioSetPath))
	{
		g_pTileLayer = NULL;
		if (SetActiveLayer())
			m_pActiveLayer->Activate(); // make sure tool pane is installed
		return TRUE;
	}
    return FALSE;
}



BOOL CMapEditorDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	m_pszTileSetPath = m_pTileSet->GetPathName();
	BOOL bNoPath = m_pszTileSetPath.IsEmpty();
	if (bNoPath || m_pTileSet->IsModified())
	{
		if (m_pTileSet->DoFileSave())
			m_pszTileSetPath = m_pTileSet->GetPathName();
		else
			return FALSE;
	}
	return CDocument::OnSaveDocument(lpszPathName);
}

CSize CMapEditorDoc::GetSize()
{
   if (m_pTileSet)
	  return CSize(m_iMapWidth * m_pTileSet->m_iTileWidth, 
				   m_iMapHeight * m_pTileSet->m_iTileHeight);
   else // called before tileset was assigned
	  return CSize(m_iMapWidth, m_iMapHeight);
}


BOOL CMapEditorDoc::ResizeMap( int iNewWidth, int iNewHeight)
{
   
   if (iNewWidth == m_iMapWidth && iNewHeight == m_iMapHeight)
	   return FALSE;

   SelectNone();
   CLayersList newLayers;
   BOOL bResize = FALSE;
   POSITION pos,pos2;

   TRY
   {
	    CRect rect(CPoint(0,0),
		          CSize(iNewWidth * m_pTileSet->m_iTileWidth,
				        iNewHeight * m_pTileSet->m_iTileHeight));
        int iMinWidth = min(iNewWidth,m_iMapWidth);
		int iMinHeight = min(iNewHeight,m_iMapHeight);

		pos = m_layers.GetHeadPosition();
		while (pos != NULL)
		{
			CMapLayer *pLayer = m_layers.GetNext(pos);
			if (pLayer != NULL)
			{
				newLayers.AddTail(pLayer->CropToSelection(rect,0,0,
					iMinHeight,iMinWidth,FALSE));
			}
		}

		pos = m_layers.GetHeadPosition();
		pos2 = newLayers.GetHeadPosition();
		while (pos != NULL)
		{
			CObjectLayer *pOld = DYNAMIC_DOWNCAST(CObjectLayer,m_layers.GetNext(pos));
			CObjectLayer *pNew = DYNAMIC_DOWNCAST(CObjectLayer,newLayers.GetNext(pos2));
            if (pOld)
			{
				pOld->CopyObjectAttributes(pNew,newLayers,rect,FALSE);
			}
		}

		DeleteLayers();
		m_iMapWidth = iNewWidth;
		m_iMapHeight = iNewHeight;
		bResize = TRUE;  // if we're gotten this far, we're effectively resized
		while (!newLayers.IsEmpty())
		{
			CMapLayer *pLayer = newLayers.RemoveHead();
			pLayer->SetMap(this);
			m_layers.AddTail(pLayer);
		}		
		SetActiveLayer();
		SetModifiedFlag();

   }
   CATCH_ALL(e)
   {
	   CMapLayer *pLayer;
	   while (!newLayers.IsEmpty())
	   {
		   pLayer = newLayers.RemoveHead();
		   delete pLayer;
	   }
	   THROW_LAST();
   }
   END_CATCH_ALL
   return bResize;
}

BOOL CMapEditorDoc::UseTileSet(CString pszPathName)
{
    CDocument *pDoc;
	CTileSet *pTileSet;
    BOOL bUsed = FALSE;
    BOOL bAdded = FALSE;

	LPCTSTR lpszPath = pszPathName.IsEmpty() ? NULL : (LPCTSTR)pszPathName;
	pDoc = theApp.m_pTileSetTemplate->OpenDocument(lpszPath,TRUE);
    if (pDoc != NULL)
	{
		pTileSet = STATIC_DOWNCAST(CTileSet, pDoc);
		TRY
		{
			// see if we need to add any preset tile attributes
			ResolveAttributeConflicts(pTileSet);
			pTileSet->AddMap(this);
			bAdded = TRUE;
			m_pszTileSetPath = pszPathName;
			if (m_pTileSet != NULL)
			{
				m_pTileSet->RemoveMap(this);
				SetModifiedFlag();
			}
			m_pTileSet = pTileSet;
			bUsed = TRUE;
		}
		CATCH_ALL(e)
		{
			// close if no maps or views
			if (bAdded) pTileSet->RemoveMap(this);    
			pTileSet->OnChangedViewList(); 
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	return bUsed;
}


BOOL CMapEditorDoc::UseObjectSet(CString pszPathName)
{
    CDocument *pDoc = NULL;
	CObjectSet *pObjectSet;
    BOOL bUsed = FALSE;
    BOOL bAdded = FALSE;

	if (!pszPathName.IsEmpty())
		pDoc = theApp.m_pObjectSetTemplate->OpenDocument(pszPathName,TRUE);
    else
		return TRUE; // using no tileset

    if (pDoc != NULL)
	{
		pObjectSet = STATIC_DOWNCAST(CObjectSet, pDoc);
		TRY
		{
			pObjectSet->AddMap(this);
			bAdded = TRUE;
			m_pszObjectSetPath = pszPathName;
			if (m_pObjectSet != NULL)
			{
				BuildObjectTable();
				m_pObjectSet->RemoveMap(this);
				SetModifiedFlag();
			}
			m_pObjectSet = pObjectSet;
			UpdateObjects();
			m_pObjectSet->UpdateAllViews(NULL); // in case fake objects were added
			bUsed = TRUE;
		}
		CATCH_ALL(e)
		{
			// close if no maps or view
			if (bAdded) pObjectSet->RemoveMap(this); 
			pObjectSet->OnChangedViewList();
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	return bUsed;
}

BOOL CMapEditorDoc::UseScenarioSet(CString pszPathName)
{
    CDocument *pDoc = NULL;
	CScenarioSet *pScenarioSet;
    BOOL bUsed = FALSE;
    BOOL bAdded = FALSE;

	if (!pszPathName.IsEmpty())
		pDoc = theApp.m_pScenarioSetTemplate->OpenDocument(pszPathName,TRUE);
    else
		return TRUE; // using no scenario set

    if (pDoc != NULL)
	{
		pScenarioSet = STATIC_DOWNCAST(CScenarioSet, pDoc);
		TRY
		{
			pScenarioSet->AddMap(this);
			bAdded = TRUE;
			m_pszScenarioSetPath = pszPathName;
			if (m_pScenarioSet != NULL)
			{
				m_pScenarioSet->RemoveMap(this);
				SetModifiedFlag();
			}
			m_pScenarioSet = pScenarioSet;
			UpdateScenarios();
			m_pScenarioSet->UpdateAllViews(NULL); // in case fake objects were added
			bUsed = TRUE;
		}
		CATCH_ALL(e)
		{
			// close if no maps or view
			if (bAdded) pScenarioSet->RemoveMap(this); 
			pScenarioSet->OnChangedViewList();
			THROW_LAST();
		}
		END_CATCH_ALL
	}
	return bUsed;
}

CPoint CMapEditorDoc::GetTileOffset(int iRow, int iColumn)
{
	ASSERT(iRow >= 0 && iRow <= m_iMapHeight); // note: allows for bottom edge of tile
	ASSERT(iColumn >= 0 && iColumn <= m_iMapWidth); // note: allows for right edge of tile
	ASSERT(m_pTileSet != NULL);
	return CPoint(iColumn * m_pTileSet->m_iTileWidth, iRow * m_pTileSet->m_iTileHeight);
}

CRect CMapEditorDoc::GetTileRect(int iRow, int iColumn)
{
	return CRect(GetTileOffset(iRow,iColumn), m_pTileSet->GetTileSize());
}

// GetRowColumn
// rounds down, no clipping
BOOL CMapEditorDoc::GetRowColumn(CPoint point, int& iRow, int& iColumn)
{
	ASSERT(m_pTileSet != NULL);
	iColumn = point.x / m_pTileSet->m_iTileWidth;
	iRow = point.y / m_pTileSet->m_iTileHeight;

	if (point.x < 0 || point.y < 0 || iRow < 0 || iColumn < 0 || iRow >= m_iMapHeight || iColumn >= m_iMapWidth)
		return FALSE;

	return TRUE;
}


BOOL CMapEditorDoc::GetRowColumn(CPoint point, int& iRow, int& iColumn, BOOL bRoundUp, BOOL bClip)
{
	ASSERT(m_pTileSet != NULL);

	int iTileWidth = m_pTileSet->m_iTileWidth;
	int iTileHeight = m_pTileSet->m_iTileHeight;
    int iMaxRow = m_iMapHeight-1;
	int iMaxColumn = m_iMapWidth-1;


	ASSERT(iTileWidth > 0);
	ASSERT(iTileHeight > 0);

	if (bRoundUp)
	{
		point.x += iTileWidth - 1;
		point.y += iTileHeight - 1;
		iMaxRow += 1;
		iMaxColumn += 1;
	}

	iColumn = point.x / iTileWidth;
	iRow = point.y / iTileHeight;

	if (bClip)
	{
		if (iRow < 0) 
			iRow = 0;
	    else if (iRow > iMaxRow) 
			iRow = iMaxRow;
		if (iColumn < 0)
			iColumn = 0;
		else if (iColumn > iMaxColumn)
			iColumn = iMaxColumn;
	}
	else if (point.x < 0 || point.y < 0 || iRow > iMaxRow || iColumn > iMaxColumn)
		return FALSE;

	return TRUE;
}

void CMapEditorDoc::RemoveTile(int iTile)
{
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CTileLayer *pLayer = DYNAMIC_DOWNCAST(CTileLayer, m_layers.GetNext(pos));
	    if (pLayer)
		{
			pLayer->RemoveTile(iTile);
			pLayer->ClearUndo(); // TBD
		}
	}
}

void CMapEditorDoc::ReplaceTile(int iTile, int iReplacement)
{
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CTileLayer *pLayer = DYNAMIC_DOWNCAST(CTileLayer, m_layers.GetNext(pos));
	    if (pLayer)
		{
		   pLayer->ReplaceTile(iTile,iReplacement);
		   pLayer->ClearUndo(); // TBD
		}
	}
}

void CMapEditorDoc::ReplaceTiles(CTileList& repList)
{
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CTileLayer *pLayer = DYNAMIC_DOWNCAST(CTileLayer, m_layers.GetNext(pos));
	    if (pLayer)
		{
		   pLayer->ReplaceTiles(repList);
		   pLayer->ClearUndo(); // TBD
		}
	}
}

void CMapEditorDoc::Select(CRect& rect, BOOL bSelected)
{
	rect.NormalizeRect();
	if (m_pActiveLayer)
		m_pActiveLayer->Select(rect,bSelected);
}


BOOL CMapEditorDoc::UsingTransparency()
{
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CMapLayer *pLayer = m_layers.GetNext(pos);
		ASSERT(pLayer != NULL);
	    if (pLayer->IsVisible() && pLayer->IsTransparent())
			return TRUE;
	}
	return FALSE;
}

/*
** METHOD
**   CMapEditorDoc::SetActiveLayer
**
** PARAMETERS
**   BOOL bNext - true if you want to make the next visible layer the active layer
**                false if you want to make the previous visible layer the active layer
**
**   POSITION startPos - optional layer position used to start iteration
**
** RETURNS                         
**   pointer to newly active layer or null if no layer is active.
**
** Notes:
**   If startPos is NULL and bNext is FALSE, this function will activate the
**   top-most visible layer. 
**
**   If startPos is NULL and bNext is TRUE, this function will activate the
**   bottom-most visible layer.
**
**   This function should be called whenever the layers list has been modified
**   or a layer has been made visible/invisible.
**
** ASSUMES:
**   If startPos is non-NULL, it is a valid position of m_layers.  
*/           
CMapLayer *CMapEditorDoc::SetActiveLayer(BOOL bNext/*=FALSE*/,POSITION startPos/*=NULL*/)
{
	CMapLayer *pNewLayer = NULL;
    POSITION pos = startPos;
	if (bNext)
	{
		if (pos == NULL)
			pos = m_layers.GetHeadPosition(); // start at bottom
		while (pos != NULL)
		{
			CMapLayer *pLayer = m_layers.GetNext(pos);
			if (pLayer->IsVisible())
			{
				pNewLayer = pLayer;
				break;
			}
		}
	}
    else
	{
		if (pos == NULL)
			pos = m_layers.GetTailPosition(); // start at the top
		while (pos != NULL)
		{
			CMapLayer *pLayer = m_layers.GetPrev(pos);
			if (pLayer->IsVisible())
			{
				pNewLayer = pLayer;
				break;
			}
		}
	}
    SetActiveLayer(pNewLayer);
	return m_pActiveLayer;
}



void CMapEditorDoc::SetActiveLayer(CMapLayer *pNewLayer)
{
	if (m_pActiveLayer != pNewLayer)
	{
		if (m_pActiveLayer)
			m_pActiveLayer->Deactivate();

		m_pActiveLayer = pNewLayer;
		if (pNewLayer)
		{
			ASSERT(m_layers.Find(pNewLayer) != NULL);
			ASSERT(pNewLayer->IsVisible());
			pNewLayer->Activate();
		}
		UpdateAllViews(NULL, MEV_UPDATE_LAYER);
	}
}

BOOL CMapEditorDoc::SelectActiveLayer(int iLayerIndex, BOOL bHideCurrent)
{
	CMapLayer *pNewLayer = NULL;
    POSITION pos = m_layers.FindIndex(iLayerIndex);
	if (pos != NULL)
	{
	    BOOL bRepaint = FALSE;
		CMapLayer *pLayer = m_layers.GetAt(pos);
		ASSERT(pLayer != NULL);

		if (pLayer != m_pActiveLayer)
		{
			if (m_pActiveLayer)
			{
				if (bHideCurrent)
				{
					m_pActiveLayer->SetVisible(FALSE);
					bRepaint = TRUE;
				}
				m_pActiveLayer->Deactivate();
			}
			if (!pLayer->IsVisible())
			{
				pLayer->SetVisible();
				bRepaint = TRUE;
			}

			m_pActiveLayer = pLayer;
			pLayer->Activate(); 
		
			UpdateAllViews(NULL, MEV_UPDATE_LAYER);
			if (bRepaint) UpdateAllViews(NULL);
		}
		return TRUE;
	}
	return FALSE;
}


void CMapEditorDoc::OnFileRevert() 
{
	ASSERT(!GetPathName().IsEmpty());

 	if (IsModified())
	{
		CString msg;
		AfxFormatString1(msg, IDS_REVERT_MAY_LOSE_DATA, GetPathName());
		if (AfxMessageBox(msg, MB_ICONQUESTION|MB_YESNO) != IDYES)
			return; // user aborted the revert
	}
	g_bOldDataFormat = m_bOldDataFormat;
	if (OnOpenDocument(GetPathName()))
		UpdateAllViews(NULL, MEV_UPDATE_PALETTE|MEV_UPDATE_SIZE);
	else
		OnCloseDocument(); // man we're in trouble. 
}

void CMapEditorDoc::OnUpdateFileRevert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetPathName().IsEmpty());	
}


void CMapEditorDoc::SetPreviewRect(CRect rect)
{
	CRect oldRect = m_previewRect;

    if (rect.IsRectEmpty())
		goto updateold;

	rect.NormalizeRect();
	if (m_previewRect.IntersectRect(rect,CRect(CPoint(0,0),GetSize())))
	{
		CRect changeRect;

		changeRect.UnionRect(oldRect,m_previewRect);
#ifdef _DEBUG
		if (oldRect.IsRectEmpty())
			ASSERT(changeRect == m_previewRect);
		else 
		{
			ASSERT(changeRect.left == min(oldRect.left,m_previewRect.left));
			ASSERT(changeRect.right == max(oldRect.right,m_previewRect.right));
			ASSERT(changeRect.top == min(oldRect.top, m_previewRect.top));
			ASSERT(changeRect.bottom == max(oldRect.bottom, m_previewRect.bottom)); 
		}
#endif
		//TRACE("old=%d,%d,%d,%d\n",oldRect.left,oldRect.top,oldRect.right,oldRect.bottom);
		//TRACE("new=%d,%d,%d,%d\n",m_previewRect.left,m_previewRect.top,m_previewRect.right,m_previewRect.bottom);
		//TRACE("chg=%d,%d,%d,%d\n",changeRect.left,changeRect.top,changeRect.right,changeRect.bottom);
		UpdateAllViews(NULL,MEV_UPDATE_PREVIEW,&CMapUpdate(changeRect));
	}
	else 
	{
updateold:
		if (!oldRect.IsRectEmpty())
		{
			UpdateAllViews(NULL,NULL,&CMapUpdate(oldRect));
			m_previewRect.SetRectEmpty();
		}
	}
}


void CMapEditorDoc::ClearPreviewRect()
{
	if (!m_previewRect.IsRectEmpty())
	{
		UpdateAllViews(NULL,NULL,&CMapUpdate(m_previewRect));
		m_previewRect.SetRectEmpty();
	}
}


// Assumes palette has already been selected into hdc
void CMapEditorDoc::Draw(HDC hdc, CRect rect, CDIB *pDst, HBITMAP hBitmap)
{
	int iStartRow, iStartCol;
	int iEndRow, iEndCol;

	ASSERT(m_pTileSet != NULL);

	rect.NormalizeRect();
    GetRowColumn(rect.TopLeft(),iStartRow,iStartCol,FALSE,TRUE);
	GetRowColumn(rect.BottomRight(), iEndRow,iEndCol,TRUE,TRUE);

	if (iStartRow == iEndRow || iStartCol == iEndCol)
		return;

	CPoint tOffset,rOffset;
	if (pDst || hBitmap) 
	{
		// drawing off-screen
		tOffset.x = tOffset.y = 0;
		rOffset = rect.TopLeft();
	}
	else 
	{
		// drawing on-screen
		tOffset = GetTileOffset(iStartRow, iStartCol);
        rOffset.x = rOffset.y = 0;
	}

    CPoint previewOffset;
	BOOL bPreview = FALSE;

	if (!m_previewRect.IsRectEmpty())
	{
		CRect tmp;
		if (tmp.IntersectRect(rect,m_previewRect))
		{
			previewOffset = m_previewRect.TopLeft();
			if (pDst || hBitmap) 
			{
				//TRACE("rect=%d,%d,%d,%d\n",rect.left,rect.top,rect.right,rect.bottom);
				//TRACE("prev=%d,%d\n",previewOffset.x, previewOffset.y);
				previewOffset -= rect.TopLeft();
				//TRACE("offs=%d,%d\n",previewOffset.x, previewOffset.y);
			}
			bPreview = TRUE;
		}
	}

	POSITION pos = m_layers.GetHeadPosition();
	HPALETTE hPalette = GetHPalette();
	while (pos != NULL)
	{
		CMapLayer *pLayer = m_layers.GetNext(pos);
		if (pLayer && pLayer->IsVisible())
		{
			if (pLayer->IsTileBased())
				pLayer->Draw(hdc,tOffset,iStartRow,iStartCol,iEndRow,iEndCol,pDst);
			else
				pLayer->Draw(hdc,rOffset,rect,hPalette,pDst);

			if (g_bActivePreview && bPreview && pLayer == m_pActiveLayer)
			   pLayer->DrawPreview(hdc,previewOffset,pDst);
		}
	}	

	if (!g_bActivePreview && bPreview && m_pActiveLayer)
		m_pActiveLayer->DrawPreview(hdc,previewOffset,pDst);
}

// sets bounds to the minimum rectangle to enclose the given
// rect on tile boundaries.
BOOL CMapEditorDoc::GetBoundingRect(CRect rect, CRect& bounds)
{
	int iStartRow, iStartColumn;
	int iEndRow, iEndColumn;

	rect.NormalizeRect();
    GetRowColumn(rect.TopLeft(),iStartRow,iStartColumn,FALSE,TRUE);
	GetRowColumn(rect.BottomRight(), iEndRow,iEndColumn,TRUE,TRUE);

 	bounds.SetRect(GetTileOffset(iStartRow,iStartColumn), 
		           GetTileOffset(iEndRow, iEndColumn));

	if (iStartRow == iEndRow || iStartColumn == iEndColumn)
		return FALSE;

	return TRUE;
}

BOOL CMapEditorDoc::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if ((m_pActiveLayer != NULL)
		&& m_pActiveLayer->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CDocument::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMapEditorDoc::OnUpdateEditCrop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pActiveLayer && m_pActiveLayer->IsSelected());
}

void CMapEditorDoc::OnEditCrop() 
{
   ASSERT(m_pActiveLayer != NULL);
   CRect rect = m_pActiveLayer->GetSelection(); 
   if (rect.IsRectEmpty())
	   return;

    int iStartRow, iStartCol, iEndRow, iEndCol;
	GetRowColumn(rect.TopLeft(),iStartRow,iStartCol,FALSE);
	GetRowColumn(rect.BottomRight(),iEndRow,iEndCol,TRUE);
    CPoint p1 = GetTileOffset(iStartRow,iStartCol);
	CPoint p2 = GetTileOffset(iEndRow,iEndCol);
    rect.SetRect(p1.x,p1.y,p2.x,p2.y);

   if (rect.IsRectEmpty())
	   return;

#ifdef _DEBUG
	ASSERT(m_pTileSet != NULL);
    CSize tileSize = m_pTileSet->GetTileSize();
	ASSERT(tileSize.cx != 0);
	ASSERT(tileSize.cy != 0);
    ASSERT((rect.left % tileSize.cx) == 0);
	ASSERT((rect.right % tileSize.cx) == 0);
	ASSERT((rect.top % tileSize.cy) == 0);
	ASSERT((rect.bottom % tileSize.cy) == 0);
#endif

   int iWidth = rect.Width() / m_pTileSet->m_iTileWidth;
   int iHeight = rect.Height() / m_pTileSet->m_iTileHeight;

   CLayersList newLayers;
   BOOL bCropped = FALSE;
   POSITION pos,pos2;

   TRY
   {
		pos = m_layers.GetHeadPosition();
		while (pos != NULL)
		{
			CMapLayer *pLayer = m_layers.GetNext(pos);
			if (pLayer != NULL)
			{
				BOOL bActive = (m_pActiveLayer == pLayer);
				newLayers.AddTail(pLayer->CropToSelection(rect,iStartRow,iStartCol,
					iEndRow,iEndCol,bActive));
			}
		}
		pos = m_layers.GetHeadPosition();
		pos2 = newLayers.GetHeadPosition();
		while (pos != NULL)
		{
			CObjectLayer *pOld = DYNAMIC_DOWNCAST(CObjectLayer,m_layers.GetNext(pos));
			CObjectLayer *pNew = DYNAMIC_DOWNCAST(CObjectLayer,newLayers.GetNext(pos2));
            if (pOld)
			{
				pOld->CopyObjectAttributes(pNew,newLayers,rect,m_pActiveLayer == pOld);
			}
		}

		DeleteLayers();
		m_iMapWidth = iWidth;
		m_iMapHeight = iHeight;
		bCropped = TRUE;  // if we've gotten this far, we're effectively cropped
		while (!newLayers.IsEmpty())
		{
			CMapLayer *pLayer = newLayers.RemoveHead();
			pLayer->SetMap(this);
			m_layers.AddTail(pLayer);
		}
		SetActiveLayer();
   }
   CATCH_ALL(e)
   {
	   CMapLayer *pLayer;
	   while (!newLayers.IsEmpty())
	   {
		   pLayer = newLayers.RemoveHead();
		   delete pLayer;
	   }
	   THROW_LAST();
   }
   END_CATCH_ALL

   if (bCropped)
   {
	   SetModifiedFlag();
	   UpdateAllViews(NULL,MEV_UPDATE_SIZE);
   }
}

CTileLayer *CMapEditorDoc::CreateBaseLayer() 
{ 
	return CreateTileLayer(IDS_BASE_LAYER,FALSE,0); 
}

CTileLayer *CMapEditorDoc::CreateOverlayLayer() 
{ 
	return CreateTileLayer(IDS_OVERLAY_LAYER,TRUE,-1); 
}

CObjectLayer *CMapEditorDoc::CreateObjectLayer()
{
	CObjectLayer *pLayer = NULL;
	TRY
	{
		CString newTitle = NewLayerName(IDS_OBJECT_LAYER);
		pLayer = new CObjectLayer(this,newTitle);
		ASSERT_NEW(pLayer);
		pLayer->SetVisible(TRUE);
		AddLayer(pLayer);
	}
	CATCH_ALL(e)
	{
		delete pLayer;
		pLayer = NULL;
		THROW_LAST();
	}
	END_CATCH_ALL
	return pLayer;

}

// TBD: collapse this and CreateObjectLayer...
CScenarioLayer *CMapEditorDoc::CreateScenario()
{
	CScenarioLayer *pLayer = NULL;

	TRY
	{
		CString newTitle = NewLayerName(IDS_SCENARIO);
		pLayer = new CScenarioLayer(this,newTitle);
		ASSERT_NEW(pLayer);
		pLayer->SetVisible(TRUE);
		AddLayer(pLayer);
	}
	CATCH_ALL(e)
	{
		delete pLayer;
		pLayer = NULL;
		THROW_LAST();
	}
	END_CATCH_ALL
	return pLayer;

}


CAttributeLayer * CMapEditorDoc::CreateAttributeLayer(LPCTSTR lpszName, int iBitCount, int iDefaultValue, BOOL bVisible)
{
	CAttributeLayer *pLayer = new CAttributeLayer(this,lpszName,iBitCount,iDefaultValue);
	ASSERT_NEW(pLayer);
	pLayer->SetVisible(bVisible);
	AddLayer(pLayer);
	SetModifiedFlag();
	return pLayer;
}

CAttributeLayer * CMapEditorDoc::CreateAttributeLayer()
{
	CAttributeLayer *pLayer = NULL;

	TRY
	{
		CString newTitle = NewLayerName(IDS_ATTRIBUTE_LAYER);
		CNewAttributeDlg dlg(NULL,newTitle);
		ASSERT(m_pTileSet != NULL);

		if ((dlg.DoModal() == IDOK) &&
			m_pTileSet->AddAttribute(dlg.m_pszName, dlg.m_nBitCount, dlg.m_iDefaultValue))
		{
			pLayer = CreateAttributeLayer(dlg.m_pszName, dlg.m_nBitCount, dlg.m_iDefaultValue, TRUE);
		}
	}
	CATCH_ALL(e)
	{
		delete pLayer;
		pLayer = NULL;
		THROW_LAST();
	}
	END_CATCH_ALL
	return pLayer;
}

void CMapEditorDoc::Invalidate(int iRow, int iColumn)
{
	UpdateAllViews(NULL,NULL,&CMapUpdate(GetTileRect(iRow,iColumn)));
}

void CMapEditorDoc::Invalidate(LPRECT lpRect)
{
	if (lpRect)
		UpdateAllViews(NULL,NULL,&CMapUpdate(lpRect));
	else
		UpdateAllViews(NULL);
}

CMapLayerMode CMapEditorDoc::ToggleItem(CPoint point, int iRow, int iColumn, BOOL& bSelect)
{
	if (m_pActiveLayer)
		return m_pActiveLayer->ToggleItem(point,iRow,iColumn,bSelect);
	else
		return none;
}

CMapLayerMode CMapEditorDoc::GetItem(CPoint point, int iRow, int iColumn)
{
	if (m_pActiveLayer)
	{
		return m_pActiveLayer->GetItem(point,iRow,iColumn);
	}
	else
		return none;
}

CMapLayerMode CMapEditorDoc::SelectItem(CPoint point, int iRow, int iColumn,BOOL bSelected)
{
	if (m_pActiveLayer)
		return m_pActiveLayer->SelectItem(point,iRow,iColumn,bSelected);
	else
		return none;
}


CMapLayerMode CMapEditorDoc::PlaceItem(CPoint point, int iRow, int iColumn)
{
	if (m_pActiveLayer)
		return m_pActiveLayer->PlaceItem(point,iRow,iColumn);
	else
		return none;
}

void CMapEditorDoc::MoveItem(CPoint point, int iRow, int iColumn)
{
	if (m_pActiveLayer)
		m_pActiveLayer->MoveItem(point,iRow,iColumn);
}

BOOL CMapEditorDoc::PreviewItem(CPoint point, int iRow, int iColumn)
{
	if (m_pActiveLayer)
		return m_pActiveLayer->PreviewItem(point,iRow,iColumn);
	else
		return FALSE;
}

void CMapEditorDoc::OnUpdateEditSelectNone(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pActiveLayer && m_pActiveLayer->IsSelected());
}

void CMapEditorDoc::OnEditSelectNone() 
{
	if (m_pActiveLayer)
		m_pActiveLayer->SelectNone();
}

void CMapEditorDoc::UpdateTiles(int iStartTile, int iEndTile)
{
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CTileLayer *pLayer = DYNAMIC_DOWNCAST(CTileLayer, m_layers.GetNext(pos));
	    if (pLayer)
			pLayer->UpdateTiles(iStartTile, iEndTile);
	}
	if (m_bNeedsUpdate)
	{
		UpdateAllViews(NULL);
		m_bNeedsUpdate = FALSE;
	}
}

void CMapEditorDoc::ExportBitmap(LPCSTR lpszPathName)
{
	CSize size = GetSize();
	CTileSet *pTileSet = GetTileSet();
	CMapBmpDlg bmpDlg(NULL, size.cx, size.cy, pTileSet->GetTileDepth());
	if (bmpDlg.DoModal() == IDOK)
	{
		CWaitCursor wait;
		POSITION pos;
        int nLayers = 0;
		switch(bmpDlg.m_iExportLayers)
		{
			case CMapBmpDlg::export_visible:
				pos = m_layers.GetHeadPosition();
				while (pos != NULL)
				{
					CMapLayer *pLayer = m_layers.GetNext(pos);
					if (pLayer && pLayer->IsVisible())
						++nLayers;
				}
				break;
			case CMapBmpDlg::export_active:
				if (m_pActiveLayer)
				   ++nLayers;
			default:
				nLayers = m_layers.GetCount();
		}

		if (nLayers == 0 || bmpDlg.m_nExportWidth == 0 || bmpDlg.m_nExportHeight == 0)
		{
			AfxMessageBox(IDS_NOTHING_TO_EXPORT, MB_ICONINFORMATION);
			return;
		}

		CDibDoc *pDoc = NULL;
		HDC hdc = NULL;
		CFile* pFile = NULL;
	    HPALETTE hOldPalette = NULL;
    
		TRY
		{
			HPALETTE hPalette = GetHPalette();
			CSize newsize(bmpDlg.m_nExportWidth, bmpDlg.m_nExportHeight);
			pDoc = pTileSet->CreateCompatibleDIB(newsize.cx, newsize.cy);
			if (pDoc)
			{
				CDIB *pDIB = pDoc->GetDIB();
				CDIB *pExportDIB = (g_bUseOffScreenDibs && pDIB->IsSimpleDib()) ? pDIB : NULL;
				hdc = pDIB->CreateHDC();
				if (hdc)
				{
					hOldPalette = SelectPalette(hdc, hPalette, FALSE);
					RealizePalette(hdc);
					CRect rect(CPoint(0,0),size);

					HBRUSH hBrush = CreateSolidBrush(m_rgbBackground);
					if (hBrush)
					{
						FillRect(hdc,&rect,hBrush);
						DeleteObject(hBrush);
					}
					else
						BitBlt(hdc,0,0,newsize.cx,newsize.cy,hdc,0,0,WHITENESS);

					// scale the hdc coordinate system if necessary
					if (bmpDlg.m_iExportType == CMapBmpDlg::export_custom)
					{
						VERIFY(SetMapMode(hdc, MM_ANISOTROPIC));
						VERIFY(SetWindowExtEx(hdc, size.cx, size.cy, NULL));
						VERIFY(SetViewportExtEx(hdc, newsize.cx, newsize.cy, NULL));
					}

					// paint the map into the off-screen bitmap
					pos = m_layers.GetHeadPosition();
					CPoint offset(0,0);
					while (pos != NULL)
					{
						CMapLayer *pLayer = m_layers.GetNext(pos);
						if (pLayer)
						{
							switch(bmpDlg.m_iExportLayers)
							{
								case CMapBmpDlg::export_visible:
									if (!pLayer->IsVisible())
										continue;
									break;
								case CMapBmpDlg::export_active:
									if (pLayer != m_pActiveLayer)
										continue;
									break;
							}
							
							if (pLayer->IsTileBased())
								pLayer->Draw(hdc,offset,0,0,m_iMapHeight,m_iMapWidth,pExportDIB);
							else
								pLayer->Draw(hdc,offset,rect,hPalette,pExportDIB);
						}
					}
					pDoc->OnSaveDocument(lpszPathName);

					// we're done, clean up...
					SelectPalette(hdc, hOldPalette, TRUE);
					pDoc->GetDIB()->DeleteHDC();
					delete pDoc;
				}
				else
				{
					TRACE0("Can't create export dib hdc\n");
					AfxThrowMemoryException();
				}
			}
			else
			{
				TRACE0("Can't allocate export dib\n");
				AfxThrowMemoryException();
			}
		} 
		CATCH_ALL(E)
		{
			TRACE0("Caught export error, freeing resources\n");
			if (pDoc)
			{
				if (hdc)
				{
					SelectPalette(hdc, hOldPalette, TRUE);
					pDoc->GetDIB()->DeleteHDC();
				}
				delete pDoc;
			}
			THROW_LAST();
		}
		END_CATCH_ALL
	}
}

/*
** METHOD
**   CMapEditorDoc::FindAttribute
**
** PARAMETERS
**   CString pszName -- name of the attribute you wish to find
**
** DESCRIPTION
**   searches for an attribute layer matching the given name.
*/
CAttributeLayer *CMapEditorDoc::FindAttribute(CString pszName)
{
	POSITION pos = m_layers.GetHeadPosition();
	CAttributeLayer *pFound = NULL;
    while (pos != NULL && pFound == NULL)
	{
		CAttributeLayer *pLayer = DYNAMIC_DOWNCAST(CAttributeLayer, m_layers.GetNext(pos));
		if (pLayer)
		{
			if (pszName.CompareNoCase(pLayer->GetTitle()) == 0)
               pFound = pLayer;
		}
	}
	return pFound;
}

////////////////////////////////////////////////////////////////////////////////////
// BEGIN ARMYMEN SPECIFIC CODE
#define NUMBER_LENGTH 3
#define NUMBER_SIZE (NUMBER_LENGTH+1)

BOOL ParseArmyMenName(CMapObject *pObject, int& iCategory, int& iID)
{
	CString name = pObject->GetName();
	CString folder = pObject->GetFolder();
	int iLength = name.GetLength();
	char number[NUMBER_SIZE];

    static const char *folder_names[] =
	{
		"Rock",
		"Bush",
		"Tree",
		"BigTree",
		"FallenTree",
		"Fence",
		"Wall",
		"Bridge",
		"FootBridge",
		"Explosives",
		"GunTurret",
		"AAGun",
		"Base",
		"Auxbase",
		"AirStrip",
		"HeliPad",
		"PrisonCamp",
		"Building",
		"PillBox",
		"PowerPlant",
		"Gate",
		"WallGate",
		"RadarBuilding",
		"Miscellaneous",
		"Overpass",
		"Sitems"
	};

#define MAX_AM_NAMES (sizeof(folder_names)/sizeof(char *))

    ASSERT(MAX_AM_NAMES == 26);  // so I don't get bitten by the missing , (string concat) problem again

	if (iLength >= 8)
	{
		LPCSTR pstr = name;
		for (int i=0; i < MAX_AM_NAMES; i++)
		{
			if (stricmp(folder,folder_names[i]) == 0)
			{
				iCategory = i;

				strncpy(number, &pstr[5],NUMBER_LENGTH);
				number[NUMBER_LENGTH] = '\0';
				iID = atoi(number);

				return TRUE;
			}
		}
	}	
	return FALSE;
}

void CMapEditorDoc::GetArmyMenAttribute(char *pData, CAttributeLayer *pAttribute, int iMax, int iShift)
{
	if (pAttribute)
	{
		for (int iRow = 0; iRow < m_iMapHeight; iRow++)	{
			for (int iCol = 0; iCol < m_iMapWidth; iCol++,pData++)	{
				char attr = min( pAttribute->GetAttribute(iRow,iCol), iMax);
				attr = max( attr, -iMax);
				attr <<= iShift;
				*pData |= attr;
			}
		}
	}
}

void CMapEditorDoc::GetArmyMenShortAttribute(short *pData, CAttributeLayer *pAttribute)
{
	if (pAttribute)
	{
		for (int iRow = 0; iRow < m_iMapHeight; iRow++)	{
			for (int iCol = 0; iCol < m_iMapWidth; iCol++,pData++)	{
				*pData = pAttribute->GetAttribute(iRow,iCol);
			}
		}
	}
}


static char *g_amUnitType[] = {
	"rifle",
	"grenadier",
	"flamer",
	"bazooka",
	"engineer",
	"mortar",
	"miner",
	"special",
};

#define N_AM_UNITS (sizeof(g_amUnitType)/sizeof(char*))

static char *g_amPlayerName[] = {
	"1-green",
	"2-tan",
	"3-blue",
	"4-gray",
};

#define N_AM_PLAYERS (sizeof(g_amPlayerName)/sizeof(char *))

static char *g_amVehicleType[] = {
	"jeep",
	"tank",
	"halftrack",
	"truck",
	"sarge",
};

#define N_AM_VEHICLES (sizeof(g_amVehicleType)/sizeof(char*))

static char *g_amResourceType[] = {
	"air strike",
	"paratroopers",
	"air recon",
};

#define N_AM_RESOURCES (sizeof(g_amResourceType)/sizeof(char*))

#define VEHICLE_TAG 0x00008000

static long AMScenarioUnit(CScenarioSet *pScenarioSet, int iPlayer, CMapObjectInst *pObject )
{
	ASSERT(pScenarioSet != NULL);
	ASSERT(pObject != NULL);
	ASSERT(iPlayer >= 0 && iPlayer < N_AM_PLAYERS);
	LPCTSTR lpszKey = pScenarioSet->GetObject(pObject->m_ID)->GetKey();

	for (long lUnit =0; lUnit < N_AM_UNITS; lUnit++)
	{
		CString name = pScenarioSet->MakeObjectKey(g_amPlayerName[iPlayer], g_amUnitType[lUnit], TRUE);
		if (name.CompareNoCase(lpszKey) == 0)
		{
			return lUnit;
		}
	}

	for (long lVehicle=0; lVehicle < N_AM_VEHICLES; lVehicle++)
	{
		CString name = pScenarioSet->MakeObjectKey(g_amPlayerName[iPlayer], g_amVehicleType[lVehicle], TRUE);
		if (name.CompareNoCase(lpszKey) == 0)
		{
			return ((lVehicle+1) | VEHICLE_TAG);
		}
	}

	return -1L;
}

static void ExportArmyMenScenario(CIFFFile& iff, CScenarioLayer *pScenario, CAttributeLayer *pFacing, 
								  CAttributeLayer *pUndeployed, CAttributeLayer *pNumber,
								  CAttributeLayer *pAmmo)
{
/*
	// maximums allowed of any unit type
	static LONG lUnitValues[N_AM_UNITS] = 
	{
		8, // riflemen
		4, // grenade
		4, // flame
		4, // bazooka
		0, // engineer
		4, // mortar
		4, // miner
	};
*/

	ASSERT(N_AM_UNITS == 8);
	ASSERT(N_AM_PLAYERS == 4);
	ASSERT(N_AM_VEHICLES == 5);
	ASSERT_VALID(pScenario);

	char name[16];
	strncpy(name,pScenario->GetTitle(),16);
	iff.Write(&name,16);

    // Don't ask me, this is their format...yuk
	CScenarioInfo info;
	CString pszKey;
	long lValue;
  
    CScenarioSet *pScenarioSet = pScenario->GetScenarioSet();
	ASSERT(pScenarioSet != NULL);

	for (int iPlayer=0; iPlayer < N_AM_PLAYERS; iPlayer++)
	{
		// write out this player legion
		iff.WriteLong(N_AM_UNITS);        // NumberUnitTypes
		iff.WriteLong(0L);                // Reserved_1
		for (int iUnit=0; iUnit < N_AM_UNITS; iUnit++)
		{
			// UnitsAvail[iUnit]
		   pszKey = pScenarioSet->MakeObjectKey(g_amPlayerName[iPlayer],g_amUnitType[iUnit],TRUE);
		   lValue = pScenario->GetObjectTotal(pszKey);
/*
		   if (lValue < 0 || lValue > lUnitValues[iUnit])
		   {
			   CString msg;
			   msg.Format(IDS_AMV_BADUNITTOTAL,pScenario->GetTitle(),
				          g_amPlayerName[iPlayer],
				          g_amUnitType[iUnit],lUnitValues[iUnit]);
			   UserError(msg);
		   }
*/
		   iff.WriteLong(lValue); 
		}
		iff.WriteLong(N_AM_VEHICLES);     // NumberVehicleTypes
//		iff.WriteLong(0L);                // Reserved_2
		iff.WriteLong(N_AM_RESOURCES);			// replaced reserved with the number of resources

		for (int iVehicle=0; iVehicle < N_AM_VEHICLES; iVehicle++)
		{
			// VehiclesAvail[iVehicle]
		    pszKey = pScenarioSet->MakeObjectKey(g_amPlayerName[iPlayer],g_amVehicleType[iVehicle],TRUE);
			lValue = pScenario->GetObjectTotal(pszKey);
			iff.WriteLong(lValue);
		}

		for (int iResource=0; iResource < N_AM_RESOURCES; iResource++)
		{
		    pszKey = pScenarioSet->MakeObjectKey(g_amPlayerName[iPlayer],g_amResourceType[iResource],FALSE);
			lValue = pScenario->GetObjectTotal(pszKey);
			iff.WriteLong(lValue);
		}

		POSITION pos = pScenario->GetFirstObjectPosition();
		lValue = 0;
		while (pos != NULL)
		{
			if (AMScenarioUnit(pScenarioSet, iPlayer, pScenario->GetNextObject(pos)) >= 0)
				++lValue;
		}
        iff.WriteLong(lValue); // NumberUnitsDeployed
		
		// write out UnitsDeployed[] for this legion
		pos = pScenario->GetFirstObjectPosition();
		while (pos != NULL)
		{
			CMapObjectInst *pInstance = pScenario->GetNextObject(pos);
			lValue = AMScenarioUnit(pScenarioSet, iPlayer, pInstance);
			if (lValue >= 0)
			{
				pScenario->ForceInside(pInstance);

				CPoint hot = pScenario->GetHotSpot(pInstance);

				iff.WriteLong(lValue);                  // eUnitType;
				iff.WriteLong(hot.x);					// xWorldCoord (of hotspot)
				iff.WriteLong(hot.y);					// yWorldCoord (of hotspot)
//				iff.WriteLong(pInstance->m_location.x); // xWorldCoord
//				iff.WriteLong(pInstance->m_location.y); // yWorldCoord

				char facing = 0;
				if (pFacing)
				{
					CAttributeInfo info;
					pFacing->GetObjectAttribute(pInstance,hot,info);
					facing = (char) info.m_currentValue;
				}
				iff.Write(&facing,1);

				char bits = 0;
				if (pUndeployed)
				{
					CAttributeInfo info;
					pUndeployed->GetObjectAttribute(pInstance,hot,info);
					bits |= (char) info.m_currentValue;

					// any other bits of info we need go here
				}
				iff.Write(&bits,1);

				char number = 0;
				if (pNumber)
				{
					CAttributeInfo info;
					pNumber->GetObjectAttribute(pInstance,hot,info);
					number = (char) info.m_currentValue;
				}
				if (pAmmo)
				{
					CAttributeInfo info;
					pAmmo->GetObjectAttribute(pInstance,hot,info);
					if (info.m_currentValue)
						number = (char) info.m_currentValue;
				}
				iff.Write(&number,1);

//				char reserve = 0;
//				iff.Write(&reserve,1);

				char *pChar = NULL;
				char size = 0;
				if (!pInstance->m_sTextBlock.IsEmpty())
				{
					pChar = (LPSTR)(LPCTSTR)pInstance->m_sTextBlock;
					size = strlen(pChar) + 1;
					iff.Write(&size,1);
					iff.Write(pChar,size);
				}
				else
					iff.Write(&size,1);
			}
		}
	}
}


class CArmyMenObjAttr  
{
public:
	static long m_total_number;
	long m_index;
	char m_movement;
	char m_elev_owner;
	char m_triggers;
	char *m_ptext;
	char m_number;
	char m_group;

    CArmyMenObjAttr(long index, char movement, char elev_owner, char triggers, char *ptext, char number, char group)
	{
		m_index = index;
		m_movement = movement;
		m_elev_owner = elev_owner;
		m_triggers = triggers;
		m_ptext = ptext;
		m_number = number;
		m_group = group;
	};
};

long CArmyMenObjAttr::m_total_number = 7;	// there are 7 attributes set

void CMapEditorDoc::ExportArmyMen(LPCSTR lpszPathName)
{
	CFileException fe;

    // check for basic army men violations before we write out file.
	CSize tileSize = m_pTileSet->GetTileSize();
	UserError(IDS_AMV_MAPSIZE, m_iMapWidth > 300 || m_iMapHeight > 300);
	UserError(IDS_AMV_MAPSIZE, tileSize.cx != 16 || tileSize.cy != 16);
	UserError(IDS_AMV_TILEDEPTH, m_pTileSet->GetTileDepth() != 8);
    UserError(IDS_AMV_TILESET, m_pszTileSetPath.IsEmpty());
    UserError(IDS_AMV_MAPDESC, m_pszDescription.GetLength() >= 1024);
 
	int baseCount = 0;
	int overlayCount = 0;
    int objectCount = 0;
    int scenarioCount = 0;
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CMapLayer *pLayer = m_layers.GetNext(pos);
		ASSERT(pLayer != NULL);
		if (pLayer->IsKindOf(RUNTIME_CLASS(CTileLayer)))
		{
			if (pLayer->IsTransparent())
				overlayCount += 1;
			else if (++baseCount > 1 || pLayer != m_layers.GetHead())
				UserError(IDS_AMV_BASELAYER);
		}
		else if (pLayer->IsKindOf(RUNTIME_CLASS(CScenarioLayer)))
		{	
			// Note: this case must come before the test for CObjectLayer
		    // because a CScenarioLayer is derived from CObjectLayer
			if (m_pScenarioSet)
			{
				CScenarioLayer *pScenario = STATIC_DOWNCAST(CScenarioLayer, pLayer);
				++scenarioCount;
				UserError(IDS_AMV_SCENARIONAME, strlen(pScenario->GetTitle()) >= 16);
			}
		}
		else if (pLayer->IsKindOf(RUNTIME_CLASS(CObjectLayer)) && m_pObjectSet)
		{ 
			// only write out the objects if there is an object set
			CObjectLayer *pObjectLayer = STATIC_DOWNCAST(CObjectLayer, pLayer);
			POSITION pos = pObjectLayer->GetFirstObjectPosition();
//			UserError(IDS_AMV_OBJECTLAYER, ++objectCount > 1);
            while (pos != NULL)
			{
				CMapObjectInst *pInstance = pObjectLayer->GetNextObject(pos);
				CMapObject *pObject = m_pObjectSet->GetObject(pInstance->m_ID);
				int iCategory, iID;
             
				if (!ParseArmyMenName(pObject,iCategory,iID))
				{
					CString msg;
					AfxFormatString1(msg,IDS_AMV_BADOBJECT,pObject->GetName());
					UserError(msg);
				}
				else
				{
					CSize size = pObject->GetSize();
					if ( 
							( pInstance->m_location.x < 0 ) || 
							( pInstance->m_location.y < 0 ) || 
							( (pInstance->m_location.x+size.cx) > (m_iMapWidth<<4) ) || 
							( (pInstance->m_location.y+size.cy) > (m_iMapHeight<<4) )
						)
					{
						CString msg;
						msg.FormatMessage( IDS_AMV_OBJOFFMAP, pInstance->m_location.x, pInstance->m_location.y );
						UserError(msg);
					}
				}
			}
		}
	}

    CIFFFile iff;
	if (! iff.Open(lpszPathName, CIFFFile::modeCreate |
		           CIFFFile::modeReadWrite | CIFFFile::shareExclusive, &fe))
	{
		ReportSaveLoadException(lpszPathName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		return;
	}

	TRY
	{
		CWaitCursor wait;
		UINT form = iff.PushChunk('F','O','R','M');
        iff.WriteLong(iff.MakeID('M','A','P',' '));

		// write armymen map fileformat version information
		ULONG csum = iff.PushChunk('C','S','U','M', sizeof(ULONG));
		iff.WriteLong(iff.m_checksum);

		// write armymen map fileformat version information
		ULONG vers = iff.PushChunk('V','E','R','S', 2*sizeof(ULONG));
		iff.WriteLong(MAPEDIT_MAJOR_VERSION);  // major
		iff.WriteLong(MAPEDIT_MINOR_VERSION);  // minor
        iff.PopChunk(vers);

		// write the map description chunk
		iff.WriteChunk('D','E','S','C',m_pszDescription);

		// write the ai script filename
		// this filename should not be the full path, but just the filename itself
		iff.WriteChunk('A','F','I','L',m_sAFile);

		// write the pad script filename
		// this filename should not be the full path, but just the filename itself
		iff.WriteChunk('O','F','I','L',m_sPFile);

		// write the ai script
		iff.WriteChunk('A','S','C','R',m_sAText);

		// write the pad script
		iff.WriteChunk('P','S','C','R',m_sPText);

		// write the map header information
		UINT mhdr = iff.PushChunk('M','H','D','R', 12);
		iff.WriteLong((long)m_iMapWidth);
		iff.WriteLong((long)m_iMapHeight);
		iff.WriteLong((long)baseCount + overlayCount);
		iff.PopChunk(mhdr); 

		// write the tileset references by this map (don't include path)
		CString path = m_pszTileSetPath;
		int ipos = path.ReverseFind('\\');
		if (ipos >= 0)
		{
		   UINT len = path.GetLength() - ipos - 1;
		   path = path.Right(len);
		}
		ipos = path.Find('.');
		if (ipos >= 0)
			path = path.Left(ipos + 1);
		else
			path += ".";

		path += ARMYMEN_TILE_EXT;
		iff.WriteChunk('T','N','A','M', path);

		path = m_pszObjectSetPath;
		ipos = path.ReverseFind('\\');
		if (ipos >= 0)
		{
		   UINT len = path.GetLength() - ipos - 1;
		   CString subDir = path.Right(len);
		   if (subDir.CompareNoCase("Objects")==0)
		   {
			   path = path.Left(ipos); 
			   ipos = path.ReverseFind('\\');
			   if (ipos >= 0)
			   {
				   len = path.GetLength() - ipos - 1;
				   path = path.Right(len);
			   }
			   else
				   path = "Objects";
		   }
		   else
			   path = subDir;   
		}
		iff.WriteChunk('O','N','A','M', path);
         
		CAttributeLayer *pMovement = FindAttribute("Movement");		// 4 bit layer into 8 bits
		CAttributeLayer *pOwner = FindAttribute("Owner");			// 3 bit layer, combine with elevation (low)
        CAttributeLayer *pElevation = FindAttribute("Elevation");	// 4 bit layer, combine with owner (high)
		CAttributeLayer *pBitPad = FindAttribute("BitPad");			// 8 bit layer
		CAttributeLayer *pPad = FindAttribute("NumberPad");			// 8 bit layer
		CAttributeLayer *pNumber = FindAttribute("Number");
		CAttributeLayer *pAmmo = FindAttribute("Ammo");
		CAttributeLayer *pGroup = FindAttribute("Group");
		CAttributeLayer *pTrigger[8];

		for (int i=0; i < 8; i++)
		{
			pTrigger[i] = FindAttribute(g_pszArmyMenTriggers[i]);
		}
		// write out the layers
		POSITION pos = m_layers.GetHeadPosition();
		while (pos != NULL)
		{
		  CMapLayer *pLayer = m_layers.GetNext(pos);
		  CTileLayer *pTileLayer = DYNAMIC_DOWNCAST(CTileLayer, pLayer);
		  if (pTileLayer)
		  {
//			  CRect rect = pTileLayer->GetMinRect();

			  CRect rect;
			  CSize size = pTileLayer->GetSize();
			  rect.bottom = size.cx;
			  rect.right = size.cy;
			  rect.top = 0;
			  rect.left = 0;

			  int iWidth = rect.Width();
			  int iHeight = rect.Height();
			  UINT tlay = iff.PushChunk('T','L','A','Y', 20 + 2 * iWidth * iHeight);
			  iff.WriteLong((long)pTileLayer->IsTransparent() ? 1L : 0L);
			  iff.WriteLong((long)iWidth);
			  iff.WriteLong((long)iHeight);
			  iff.WriteLong((long)rect.left);
			  iff.WriteLong((long)rect.top);
			  for (int iRow = rect.top; iRow < rect.bottom; iRow++)
			  {
				  for (int iCol = rect.left; iCol < rect.right; iCol++)
				  {
					  int iTile = pTileLayer->GetTile(iRow, iCol);
					  ASSERT(iTile >= -1);
					  UserError(IDS_AMV_TILE, iTile > SHRT_MAX);
					  iff.WriteShort((short)iTile);
				  }
			  }
			  iff.PopChunk(tlay); 
		  }
		  else if (pLayer->IsKindOf(RUNTIME_CLASS(CScenarioLayer)))
		  {
			  // Note: this case must come before the test for CObjectLayer
			  // because a CScenarioLayer is derived from CObjectLayer
			  continue; // skip scenarios for now; these get written later
		  }
		  else if (m_pObjectSet && pLayer->IsKindOf(RUNTIME_CLASS(CObjectLayer)))
		  {
			CObjectLayer *pObjectLayer = STATIC_DOWNCAST(CObjectLayer, pLayer);
			int iCount = pObjectLayer->GetObjectCount();
			UINT olay = iff.PushChunk('O','L','A','Y');
			iff.WriteLong((long)iCount);
			POSITION pos = pObjectLayer->GetFirstObjectPosition();
			while (pos != NULL)
			{
				CMapObjectInst *pInstance = pObjectLayer->GetNextObject(pos);
				CMapObject *pObject = m_pObjectSet->GetObject(pInstance->m_ID);
				int iCategory, iID;
                VERIFY(ParseArmyMenName(pObject,iCategory,iID));
				iff.WriteLong(iCategory);
				iff.WriteLong(iID);
				iff.WriteLong(pInstance->m_location.x);
				iff.WriteLong(pInstance->m_location.y);
				//TRACE("OBJ(%s):%d,%d,%d,%d\n",name,iCategory,iID,pInstance->m_location.x,pInstance->m_location.y);
			}
			iff.PopChunk(olay);

			// write out the explicitly set object attributes: presumably 
			// there won't be many of these so here goes...
			CTypedPtrList<CPtrList,CArmyMenObjAttr *> attrList;
			CArmyMenObjAttr *pAttr;

			TRY
			{
				// find all objects with explicitly set attributes
				POSITION pos = pObjectLayer->GetFirstObjectPosition();
				for (long lIndex=0; lIndex < iCount; lIndex++)
				{
					BOOL bImplicit = TRUE;
					char movement=0,elev_owner=0,triggers=0,number=1,attr;
					unsigned char uattr, group=0;
					short pad = 0;
					CMapObjectInst *pInstance = pObjectLayer->GetNextObject(pos);
					CPoint hot = pObjectLayer->GetHotSpot(pInstance);
					CAttributeInfo info;

					if (pMovement)
					{
						pMovement->GetObjectAttribute(pInstance,hot,info);
						attr = min(info.m_currentValue,15);
						attr = max( attr,-15);
						movement = attr;
						bImplicit &= info.m_bRemoved;
					}
					if (pElevation)
					{
						pElevation->GetObjectAttribute(pInstance,hot,info);
						attr = min(info.m_currentValue,15);
						attr = max( attr,0);
						elev_owner |= (attr << 4);
						bImplicit &= info.m_bRemoved;
					}
					if (pOwner)
					{
						pOwner->GetObjectAttribute(pInstance,hot,info);
						attr = min(info.m_currentValue,4);
						attr = max( attr,0);
						elev_owner |= attr;
						bImplicit &= info.m_bRemoved;
					}
					for (i=0; i < 8; i++)
					{
						if (pTrigger[i])
						{
							pTrigger[i]->GetObjectAttribute(pInstance,hot,info);
							triggers |= (min(info.m_currentValue,1) << i);
							bImplicit &= info.m_bRemoved;
						}
					}
					if (pGroup)
					{
						pGroup->GetObjectAttribute(pInstance,hot,info);
						uattr = min(info.m_currentValue,255);
						uattr = max( uattr,0);
						group = uattr;
						bImplicit &= info.m_bRemoved;
					}
					if (pAmmo)
					{
						pAmmo->GetObjectAttribute(pInstance,hot,info);
						attr = min(info.m_currentValue,255);
						attr = max( attr,0);
						number = attr;
						bImplicit &= info.m_bRemoved;
					}
					/*
					if (pNumber)
					{
						pNumber->GetObjectAttribute(pInstance,hot,info);
						attr = min(info.m_currentValue,15);
						attr = max( attr,0);

						if (number <= 1)	{
							number = attr;
							bImplicit &= info.m_bRemoved;
						}
					}
					*/

					// check for object text block
					// if text block exists, set bImplicit to false
					char *pChar = NULL;
					if (!pInstance->m_sTextBlock.IsEmpty())
					{
						pChar = (LPSTR)(LPCTSTR)pInstance->m_sTextBlock;
						bImplicit = FALSE;
					}


					if (!bImplicit)
					{
						// pass text block pointer in place of the NULL (pass NULL if it doesn't exist)
						pAttr = new CArmyMenObjAttr(lIndex,movement,elev_owner,triggers,pChar,number,group);
						ASSERT_NEW(pAttr);
						attrList.AddTail(pAttr);
					}
				} 


				// this is the object attribute specifier
				UINT oattr = iff.PushChunk('O','A','T','T');
				iff.WriteLong(pAttr->m_total_number);
				iff.WriteLong('I','N','D','X');	iff.WriteLong(sizeof(pAttr->m_index));
				iff.WriteLong('M','O','V','E');	iff.WriteLong(sizeof(pAttr->m_movement));
				iff.WriteLong('E','L','O','W');	iff.WriteLong(sizeof(pAttr->m_elev_owner));
				iff.WriteLong('T','R','I','G');	iff.WriteLong(sizeof(pAttr->m_triggers));
				iff.WriteLong('N','U','M','B');	iff.WriteLong(sizeof(pAttr->m_number));
				iff.WriteLong('G','R','U','P');	iff.WriteLong(sizeof(pAttr->m_group));
				iff.WriteLong('S','C','R','I');	iff.WriteLong(sizeof(long));

				// write out only attributes for those objects that
				// explicitly set at least one of the armymen specific
				// attributes.
				iCount = attrList.GetCount();
				iff.WriteLong((long)iCount);
				char reserved = 0;
				for (i=0; i < iCount; i++)
				{
					pAttr = attrList.GetHead();
					iff.WriteLong(pAttr->m_index);
					iff.Write(&pAttr->m_movement,1);
					iff.Write(&pAttr->m_elev_owner,1);
					iff.Write(&pAttr->m_triggers,1);
					iff.Write(&pAttr->m_number,1);
					iff.Write(&pAttr->m_group,1);

					if (pAttr->m_ptext)	{
						long nBytes = strlen(pAttr->m_ptext)+1;
						iff.WriteLong(nBytes);
						iff.Write(pAttr->m_ptext,nBytes);
					}
					else	{
						iff.WriteLong(0);
					}

				//	TRACE("OATTR(%d):0x%x,0x%x,0x%x,0x%x\n",pAttr->m_index,
				//		(int)pAttr->m_movement,(int)pAttr->m_elev_owner,(int)pAttr->m_triggers,(int)pAttr->m_pad);
					delete attrList.RemoveHead();
				}

				iff.PopChunk(oattr);
			} 
			CATCH_ALL(e)
			{
				// error occurred while writing out object attributes
				while (pAttr = attrList.RemoveHead())
					delete pAttr;
				THROW_LAST();
			}
			END_CATCH_ALL
//			iff.PopChunk(olay);
		  }
		}

		// write out the attribute layers
		UINT nBytes = m_iMapWidth * m_iMapHeight;
		char *pData = new char[nBytes];
		ASSERT_NEW(pData);

		UINT attr = iff.PushChunk('M','O','V','E', m_iMapWidth * m_iMapHeight);
		TRY
		{
			// movement attributes
			memset(pData,0,nBytes);
			GetArmyMenAttribute(pData,pMovement,15,0);
			iff.Write(pData,nBytes);
		}
		CATCH_ALL(E)
		{
			delete pData;
			pData = NULL;
			THROW_LAST();
		}
		END_CATCH_ALL
		iff.PopChunk(attr);


		attr = iff.PushChunk('E','L','O','W', m_iMapWidth * m_iMapHeight);
		TRY
		{
			// elevation & owner  attributes
			memset(pData,0,nBytes);
			GetArmyMenAttribute(pData,pElevation,15,4);	// hi bits
			GetArmyMenAttribute(pData,pOwner,15,0);		// lo bits
			iff.Write(pData,nBytes);
		}
		CATCH_ALL(E)
		{
			delete pData;
			pData = NULL;
			THROW_LAST();
		}
		END_CATCH_ALL
		iff.PopChunk(attr);


		attr = iff.PushChunk('T','R','I','G', m_iMapWidth * m_iMapHeight);
		TRY
		{
			// trigger attributes
			memset(pData,0,nBytes);
			for (int trigger = 0; trigger < 8; trigger++)
			{
				GetArmyMenAttribute(pData,pTrigger[trigger],1,trigger);
			}
			iff.Write(pData,nBytes);
		}
		CATCH_ALL(E)
		{
			delete pData;
			pData = NULL;
			THROW_LAST();
		}
		END_CATCH_ALL
		iff.PopChunk(attr);


		attr = iff.PushChunk('B','P','A','D', m_iMapWidth * m_iMapHeight);
		TRY
		{
			// bit pad
			memset(pData,0,nBytes);
			GetArmyMenAttribute(pData,pBitPad,255,0);
			iff.Write(pData,nBytes);
		}
		CATCH_ALL(E)
		{
			delete pData;
			pData = NULL;
			THROW_LAST();
		}
		END_CATCH_ALL
		iff.PopChunk(attr);


		attr = iff.PushChunk('N','P','A','D', m_iMapWidth * m_iMapHeight);
		TRY
		{
			// number pad
			memset(pData,0,nBytes);
			GetArmyMenAttribute(pData,pPad,255,0);
			iff.Write(pData,nBytes);
		}
		CATCH_ALL(E)
		{
			delete pData;
			pData = NULL;
			THROW_LAST();
		}
		END_CATCH_ALL
		iff.PopChunk(attr);

		delete pData;

		/*
		short *pShortData = new short[nBytes];
		ASSERT_NEW(pShortData);
		attr = iff.PushChunk('P','A','D','S', 2 * m_iMapWidth * m_iMapHeight);
		TRY
		{
			// pad attributes
			memset(pShortData,0,nBytes*2);
			GetArmyMenShortAttribute(pShortData,pPad);
			iff.Write(pShortData,nBytes*2);
		}
		CATCH_ALL(E)
		{
			delete pShortData;
			pShortData = NULL;
			THROW_LAST();
		}
		END_CATCH_ALL
		delete pShortData;
		iff.PopChunk(attr);
		*/

		// write scenario layers
		if (scenarioCount >= 0)
		{
			UINT scen = iff.PushChunk('S','C','E','N');
			iff.WriteLong(scenarioCount);
			pos = m_layers.GetHeadPosition();
			while (pos != NULL)
			{
				CScenarioLayer *pLayer = DYNAMIC_DOWNCAST(CScenarioLayer, m_layers.GetNext(pos));
				if (pLayer)	{
					CAttributeLayer *pFacing = FindAttribute("Facing");
					CAttributeLayer *pUndeployed = FindAttribute("Undeployed");
					CAttributeLayer *pNumber = FindAttribute("Number");
					CAttributeLayer *pAmmo = FindAttribute("Ammo");
					ExportArmyMenScenario(iff,pLayer,pFacing,pUndeployed,pNumber,pAmmo);
				}
			}
			iff.PopChunk(scen);
		}

		iff.PopChunkBuffer(csum, (char *) &iff.m_checksum);

		// end the top-level IFF FORM
		iff.PopChunk(form);
		iff.Close();
	}
	CATCH_ALL(e)
	{
		iff.Abort();

		TRY
		{
			ReportSaveLoadException(lpszPathName, e,
				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		}
		END_TRY
	}
	END_CATCH_ALL
}
// END ARMYMEN SPECIFIC CODE
////////////////////////////////////////////////////////////////////////////////////


void CMapEditorDoc::OnFileExport() 
{
	CString lpszName;
	CString lpszFilter;

	int iPos = m_strTitle.ReverseFind('.');
	int iCount = (iPos > 0) ? iPos : m_strTitle.GetLength(); 
	lpszName = m_strTitle.Left(iCount) + ".";
	lpszName += ARMYMEN_MAP_EXT; 
	lpszFilter.LoadString(IDS_MAP_EXPORT_FILTER);
	// TBD: use OFN_EXPORER + callback hooks to follow shortcuts
	CFileDialog dlg(NULL, NULL, lpszName,  OFN_LONGNAMES | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_SHAREWARN, lpszFilter);
	if (dlg.DoModal() == IDOK)
	{
		CString pathName = dlg.GetPathName();
		CString ext = dlg.GetFileExt();
		if (ext.CompareNoCase(ARMYMEN_MAP_EXT) == 0)
			ExportArmyMen(pathName);
		else 
			ExportBitmap(pathName);
	}
}

void CMapEditorDoc::InitFrameLayersList()
{
	CMainFrame *pMainFrame = STATIC_DOWNCAST(CMainFrame, AfxGetApp()->m_pMainWnd);
	pMainFrame->ResetLayersList();
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CMapLayer *pLayer = m_layers.GetNext(pos);
		ASSERT(pLayer != NULL);
		pMainFrame->AddLayer(pLayer->GetTitle(), pLayer->IsVisible(), pLayer == m_pActiveLayer);
	}	
}


void CMapEditorDoc::OnLayersArrange() 
{
	CLayersDlg dlg(this);
	dlg.DoModal();
}

void CMapEditorDoc::UpdateTileUsage(CTileList& usage)
{
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CTileLayer *pLayer = DYNAMIC_DOWNCAST(CTileLayer, m_layers.GetNext(pos));
	    if (pLayer)
			pLayer->UpdateTileUsage(usage);
	}	
}

// TBD: instead of having all these m_pActiveLayer hand-off functions
// perhaps the each layer should handle the button-down,mouse-move etc..
// and just do this stuff as part of the layer...
void CMapEditorDoc::BeginEdit()
{
	if (m_pActiveLayer)
	{
		m_pActiveLayer->SelectNone();
		m_pActiveLayer->BeginEdit();
	}
}

void CMapEditorDoc::EndEdit()
{
	if (m_pActiveLayer)
		m_pActiveLayer->EndEdit();
}

/*
** METHOD
**   CMapEditorDoc::BuildObjectTable
**
** DESCRIPTION
**   creates the mapping between object IDs in all
**   the object layers and object indices in the 
**   current objectSet.
*/
void CMapEditorDoc::BuildObjectTable()
{
	if (!m_pObjectSet) return;

	m_objectTable.RemoveAll();
	m_objectTable.InitHashTable(101);
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CMapLayer *pLayer = m_layers.GetNext(pos);
		ASSERT(pLayer != NULL);
		CObjectLayer *pObjectLayer = DYNAMIC_DOWNCAST(CObjectLayer,pLayer);
		if (pObjectLayer != NULL)
		{
			POSITION pos = pObjectLayer->GetFirstObjectPosition();
			while (pos != NULL)
			{
				CMapObjectInst *pInstance = pObjectLayer->GetNextObject(pos);
				ASSERT(pInstance != NULL);
				CMapObject *pObject = m_pObjectSet->GetObject(pInstance->m_ID);
				ASSERT(pObject != NULL);
				m_objectTable[pInstance->m_ID] = pObject->GetKey();	// now returns just the name
			}
		}
	}
}

/*
** METHOD
**   CMapEditorDoc::UpdateObjects
**
** DESCRIPTION
**   for each object in the each of the object layers
**   updates the object index based on the mapping 
**   between its object id and the current objectSet.
**
**   Assumes BuildObjectTable() for this map has already
**   been called.
**
**   Does not refresh the map because this function is
**   called when the map is first loaded.
**
*/
void CMapEditorDoc::UpdateObjects()
{
	if (!m_pObjectSet) return;
    if (m_objectTable.IsEmpty()) return;

	// update mapping: for each object in each layer
	// update object index to current objectSet index

	POSITION pos = m_layers.GetHeadPosition();
	CString name;
	CRuntimeClass *pOLClass = RUNTIME_CLASS(CObjectLayer);
	CRuntimeClass *pSLClass = RUNTIME_CLASS(CScenarioLayer);
	while (pos != NULL)
	{
		CMapLayer *pLayer = m_layers.GetNext(pos);
		ASSERT(pLayer != NULL);
		if (pLayer->IsKindOf(pOLClass) && !pLayer->IsKindOf(pSLClass))
		{
			CObjectLayer *pObjectLayer = STATIC_DOWNCAST(CObjectLayer,pLayer);
			POSITION pos = pObjectLayer->GetFirstObjectPosition();
			while (pos != NULL)
			{
				CMapObjectInst *pInstance = pObjectLayer->GetNextObject(pos);
				ASSERT(pInstance != NULL);
				VERIFY(m_objectTable.Lookup(pInstance->m_ID,name));
				// check here for folder name

				CString path = name;
				StripComponent(path, name, '\\');

				int newID = m_pObjectSet->FindObject(name,TRUE);
				pInstance->m_ID = newID;
			}
		}
	}

	DeleteObjectTable(); // it is no longer necessary (or up to date)
}

void CMapEditorDoc::DeleteObjectTable()
{
	m_objectTable.RemoveAll();
}

void CMapEditorDoc::UpdateScenarios()
{
	if (!m_pScenarioSet)
		return;

	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CScenarioLayer *pLayer = DYNAMIC_DOWNCAST(CScenarioLayer, m_layers.GetNext(pos));
		if (pLayer) pLayer->UpdateObjects();
	}
}

void CMapEditorDoc::UpdateAttributeFormat()
{
	POSITION pos = m_layers.GetHeadPosition();
	BOOL bInvalidate = FALSE;

	while (pos != NULL)
	{
		CAttributeLayer *pLayer = DYNAMIC_DOWNCAST(CAttributeLayer, m_layers.GetNext(pos));
		if (pLayer && pLayer->IsVisible())
		{
			bInvalidate = TRUE;
			pos = NULL;
		}
	}
	if (bInvalidate)
		UpdateAllViews(NULL); // redisplay all the attribute layers

	// tell all the attribute views to update their controls
	UpdateAllViews(NULL,MEV_UPDATE_ATTRIBUTE_FORMAT);
}

void CMapEditorDoc::OnUpdateEditWithAttributes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(g_bPlaceWithAttributes);
	pCmdUI->Enable(m_pActiveLayer && DYNAMIC_DOWNCAST(CTileLayer,m_pActiveLayer));	
}

void CMapEditorDoc::OnEditWithAttributes() 
{
	g_bPlaceWithAttributes = !g_bPlaceWithAttributes;
}

void CMapEditorDoc::SetAttributes(int iRow, int iColumn, int iTile)
{
	if (!m_pTileSet) 
		return; // just in case we're called from a new map before tileset is loaded

	POSITION pos = m_layers.GetHeadPosition();
	int iValue;

	while (pos != NULL)
	{
		CAttributeLayer *pAttribute = DYNAMIC_DOWNCAST(CAttributeLayer, m_layers.GetNext(pos));
		if (pAttribute && m_pTileSet->GetAttribute(pAttribute->GetTitle(), iTile, iValue))
			pAttribute->SetAttribute(iRow, iColumn, min(iValue,pAttribute->GetMaxValue()));
	}
}

void CMapEditorDoc::BeginEditAttributes()
{
	ASSERT(m_pTileSet != NULL);

	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CAttributeLayer *pAttribute = DYNAMIC_DOWNCAST(CAttributeLayer, m_layers.GetNext(pos));
		if (pAttribute) pAttribute->BeginEdit();
	}
}

void CMapEditorDoc::EndEditAttributes()
{
	ASSERT(m_pTileSet != NULL);

	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CAttributeLayer *pAttribute = DYNAMIC_DOWNCAST(CAttributeLayer, m_layers.GetNext(pos));
		if (pAttribute) pAttribute->EndEdit();
	}
}

void CMapEditorDoc::UndoAttributes()
{
	ASSERT(m_pTileSet != NULL);

	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CAttributeLayer *pAttribute = DYNAMIC_DOWNCAST(CAttributeLayer, m_layers.GetNext(pos));
		if (pAttribute) 
			pAttribute->OnCmdMsg(ID_EDIT_UNDO, WM_COMMAND, NULL, NULL);
	}
}

void CMapEditorDoc::RedoAttributes()
{
	ASSERT(m_pTileSet != NULL);

	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CAttributeLayer *pAttribute = DYNAMIC_DOWNCAST(CAttributeLayer, m_layers.GetNext(pos));
		if (pAttribute) 
			pAttribute->OnCmdMsg(ID_EDIT_REDO, WM_COMMAND, NULL, NULL);
	}
}


// This method will return TRUE if the map has at least one attribute
// in common with the given tileset.
BOOL CMapEditorDoc::ResolveAttributeConflicts(CTileSet *pTileSet)
{
	BOOL bSharedAttribute = FALSE;
	ASSERT(pTileSet != NULL);
	CString msg;

	// first resolve the attributes in the map
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CAttributeLayer *pLayer = DYNAMIC_DOWNCAST(CAttributeLayer, m_layers.GetNext(pos));
		if (pLayer)
		{
			// this will also detect and adjust attribute conflicts
			if (pTileSet->AddAttribute(pLayer->GetTitle(), pLayer->GetBitCount(), pLayer->GetDefaultValue()))
				bSharedAttribute = TRUE;
		}
	}

	// now resolve any additional tileset attributes
	int iCount = pTileSet->GetAttributeCount();
	for (int i=0; i < iCount; i++)
	{
		CTileAttribute *pAttribute = pTileSet->GetAttribute(i);
		ASSERT(pAttribute != NULL);
		LPCTSTR lpszName = pAttribute->GetName();
		int iBitCount = pAttribute->GetBitCount();
		CAttributeLayer *pLayer = DYNAMIC_DOWNCAST(CAttributeLayer, FindLayer(lpszName));
		if (pLayer == NULL)
		{
			char bitString[20];
			itoa(iBitCount,bitString,10);
			AfxFormatString2(msg,IDS_ASK_NEWATTRIBUTELAYER,bitString,lpszName);
			if (AfxMessageBox(msg,MB_ICONQUESTION|MB_YESNO) == IDYES)
			{
				CreateAttributeLayer(lpszName,iBitCount,pAttribute->GetDefaultValue(),FALSE);
				bSharedAttribute = TRUE;
			}
		}
	}
	return bSharedAttribute;
}


void CMapEditorDoc::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bGrid);
}

void CMapEditorDoc::OnViewGrid() 
{
	m_bGrid = !m_bGrid;
	UpdateAllViews(NULL);
}

void CMapEditorDoc::OnUpdateLayersActivate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pActiveLayer != NULL);
}

void CMapEditorDoc::ControlHideActiveLayer()
{
	if (m_pActiveLayer && (GetAsyncKeyState(VK_CONTROL) & 0x8000))
	{
		m_pActiveLayer->SetVisible(FALSE);
		UpdateAllViews(NULL);
	}
}

void CMapEditorDoc::OnLayersActivateTop() 
{
	ControlHideActiveLayer();
	SetActiveLayer(FALSE);
}

void CMapEditorDoc::OnLayersActivateBottom() 
{
	ControlHideActiveLayer();
	SetActiveLayer(TRUE);
}

void CMapEditorDoc::OnLayersActivateNext() 
{
	ControlHideActiveLayer();
	ASSERT(m_pActiveLayer != NULL);
	POSITION pos = m_layers.Find(m_pActiveLayer);
	ASSERT(pos != NULL);
	m_layers.GetNext(pos);
	if (!SetActiveLayer(TRUE, pos))
		SetActiveLayer(TRUE,NULL); // wrap
}

void CMapEditorDoc::OnLayersActivatePrevious() 
{
	ControlHideActiveLayer();
	ASSERT(m_pActiveLayer != NULL);
	POSITION pos = m_layers.Find(m_pActiveLayer);
	ASSERT(pos != NULL);
    m_layers.GetPrev(pos);
	if (!SetActiveLayer(FALSE, pos))
		SetActiveLayer(FALSE,NULL); // wrap
}

/*
** METHOD
**   CMapEditorDoc::GetObjectIndex
**
** PARAMETERS
**   CMapObjectInst *pInstance -- a non-NULL pointer to a map object 
**
** DESCRIPTION
**   Goes through all the object layers (including scenarios)
**   in back to front order, going through all the object lists
**   in back to front order to compute the index of the given object
**
** RETURNS
**   the index of the given object or -1
**   if the instance couldn't be found.
*/
int CMapEditorDoc::GetObjectIndex(CMapObjectInst *pInstance)
{
	int iIndex = 0;
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CObjectLayer *pLayer = DYNAMIC_DOWNCAST(CObjectLayer, m_layers.GetNext(pos));
		if (pLayer)
		{
			POSITION opos = pLayer->GetFirstObjectPosition();
			while (opos != NULL)
			{
				CMapObjectInst *pInst = pLayer->GetNextObject(opos);
				if (pInst == pInstance)
					return iIndex;
				++iIndex;
			}
		}
	}
	return -1;
}

/*
** METHOD
**   CMapEditorDoc::GetObjectInstance
**
** PARAMETERS
**   int iIndex -- 0 based index of a map object
**
** DESCRIPTION
**   returns a pointer to map object at the given
**   index position. Goes through all the object
**   layers (including scenarios) in back to front
**   order and all the object lists in back to front
**   order.
**
** RETURNS
**   a pointer to the map object at the given
**   index position or NULL if iIndex is an invalid
**   index for this map.
*/
CMapObjectInst * CMapEditorDoc::GetObjectInstance(int iIndex)
{
//	ASSERT(iIndex >= 0);
	int iTmpIndex = 0;
	POSITION pos = m_layers.GetHeadPosition();
	while (pos != NULL)
	{
		CObjectLayer *pLayer = DYNAMIC_DOWNCAST(CObjectLayer, m_layers.GetNext(pos));
		if (pLayer)
		{
			int iCount = pLayer->GetObjectCount();
			if (iIndex >= iTmpIndex + iCount)
			{
				iTmpIndex += iCount;
				continue;
			}

			POSITION opos = pLayer->GetFirstObjectPosition();
			while (opos != NULL)
			{
				CMapObjectInst *pInst = pLayer->GetNextObject(opos);
				if (iTmpIndex == iIndex)
					return pInst;
				++iTmpIndex;
			}
		}
	}
	return NULL;	
}

/*
** METHOD
**   CMapEditorDoc::GetNextAttribute
**
** PARAMETERS
**   POSITION& pos -- non-NULL position of current attribute layer
**                    initialized by call GetFirstAttribute()
**                    or previous call to GetNextAttribute()
**
** DESCRIPTION
**   returns the AttributeLayer at the given position
**   then increments the position to the next available
**   AttributeLayer (or NULL if there are no additional
**   AttributeLayers).
*/
CAttributeLayer *CMapEditorDoc::GetNextAttribute(POSITION& pos)
{
	ASSERT(pos != NULL);
	CAttributeLayer *pLayer = STATIC_DOWNCAST(CAttributeLayer, GetNextLayer(pos));

	while (pos != NULL)
	{
		if (DYNAMIC_DOWNCAST(CAttributeLayer, GetLayerAt(pos)))
			break;
		GetNextLayer(pos);
	}
	return pLayer;
}

/*
** METHOD
**   CMapEditorDoc::GetFirstAttribute
**
** DESCRIPTION
**   returns the list position of the first AttributeLayer
**   belonging to this map or NULL if there are no 
**   attribute layers.
*/
POSITION CMapEditorDoc::GetFirstAttribute()
{
	POSITION pos = GetFirstLayer();
	while (pos != NULL)
	{
		POSITION saved = pos;
		CAttributeLayer *pLayer = DYNAMIC_DOWNCAST(CAttributeLayer, GetNextLayer(pos));
		if (pLayer) 
			return saved;
	}
	return NULL;
}


int CMapEditorDoc::GetAttributeCount()
{
	int iCount = 0;
	POSITION pos = GetFirstAttribute();
	while (pos != NULL)
	{
		GetNextAttribute(pos);
		++iCount;
	}
	return iCount;
}


void CMapEditorDoc::SingleStep()
{
	POSITION pos = GetFirstLayer();
	while (pos != NULL)
	{
		CMapLayer *pLayer = GetNextLayer(pos);
		ASSERT(pLayer);
		if (pLayer->IsVisible())
			pLayer->SingleStep();
	}
}

BOOL CMapEditorDoc::Expand(int iMove, int iWidth, int iHeight)
{
	int iNewWidth = m_iMapWidth + iWidth;
	int iNewHeight = m_iMapHeight + iHeight;
	

	if (iNewWidth == m_iMapWidth && iNewHeight == m_iMapHeight)
	   return FALSE;

   SelectNone();
   CLayersList newLayers;
   BOOL bResize = FALSE;
   POSITION pos,pos2;

   TRY
   {
	   CRect rect(CPoint((0 == iMove) ? 0 : iWidth*m_pTileSet->m_iTileWidth, (0 == iMove) ? 0 : iHeight*m_pTileSet->m_iTileHeight),
		          CSize(iNewWidth * m_pTileSet->m_iTileWidth,
				        iNewHeight * m_pTileSet->m_iTileHeight));
        int iMinWidth = min(iNewWidth,m_iMapWidth);
		int iMinHeight = min(iNewHeight,m_iMapHeight);

		pos = m_layers.GetHeadPosition();
		while (pos != NULL)
		{
			CMapLayer *pLayer = m_layers.GetNext(pos);
			if (pLayer != NULL)
			{
				newLayers.AddTail(pLayer->CropToSelection(rect,0, 0,
					(0 == iMove) ? iMinHeight : iNewHeight, (0 == iMove) ? iMinWidth : iNewWidth,FALSE));
			}
		}

		pos = m_layers.GetHeadPosition();
		pos2 = newLayers.GetHeadPosition();
		while (pos != NULL)
		{
			CObjectLayer *pOld = DYNAMIC_DOWNCAST(CObjectLayer,m_layers.GetNext(pos));
			CObjectLayer *pNew = DYNAMIC_DOWNCAST(CObjectLayer,newLayers.GetNext(pos2));
            if (pOld)
			{
				pOld->CopyObjectAttributes(pNew,newLayers,rect,FALSE);
			}
		}

		DeleteLayers();
		m_iMapWidth = iNewWidth;
		m_iMapHeight = iNewHeight;
		bResize = TRUE;  // if we're gotten this far, we're effectively resized
		while (!newLayers.IsEmpty())
		{
			CMapLayer *pLayer = newLayers.RemoveHead();
			pLayer->SetMap(this);
			m_layers.AddTail(pLayer);
		}		
		SetActiveLayer();
		SetModifiedFlag();

   }
   CATCH_ALL(e)
   {
	   CMapLayer *pLayer;
	   while (!newLayers.IsEmpty())
	   {
		   pLayer = newLayers.RemoveHead();
		   delete pLayer;
	   }
	   THROW_LAST();
   }
   END_CATCH_ALL
	return bResize;
}

BOOL CMapEditorDoc::Rotate(int iType, int iDir)
{
	// Rotate
	// Take all tiles in selection area..
	// Draw on to a device context
	// Process rotation on device context
	// Seperate device context into tiles
	// Add tiles to tileset
	// Modify tilelayer to use newly created tiles.

	/*
	- Adding tiles to tileset
		Call CTileSet::Resize(TileCount+1)
		Then paint tile to tileset dib

	- Setting tiles
		Call CTileLayer::SetTile and specify index of newly created index.
	*/
	CRect sRectSel;
	CTileLayer *pLayer=NULL;
	CTileSet *pSet=NULL;

	pSet = GetTileSet();
	if (NULL == pSet)
		return FALSE;

	// Determine selection area
	if (NULL == GetActiveLayer() || 
		FALSE == GetActiveLayer()->IsKindOf(RUNTIME_CLASS(CTileLayer)))
		return FALSE;

	pLayer = (CTileLayer*)GetActiveLayer();

	if (FALSE == pLayer->IsSelected())
		return FALSE;

	sRectSel = pLayer->GetSelection();

	CDIB *pDIBTiles;
	CDIB dibDest;
	CDIB dibSrc;
	HDC hdcDest=NULL;
	HDC hdcSrc=NULL;
	HDC hdcSet=NULL;
	CPalette *pSetPal=NULL;
	CTileSet sTempSet;
	int iSrcCol=0, iSrcRow=0;
	int iDestCol=0, iDestRow=0;
	int iDestWidth=0,iDestHeight=0;
	int iCol=0, iRow=0;
	int iMaxCol=0, iMaxRow=0;
	int iRectWidth=sRectSel.Width(), iRectHeight=sRectSel.Height();
	COLORREF clrPix;
	int iNewTiles = ((iRectWidth/pSet->m_iTileWidth) * (iRectHeight/pSet->m_iTileHeight));
	int iTiles = pSet->GetTileCount();
	int iCurTile=0;
	CPoint sLoc;
	int iTempTile=0;
	BOOL bJunk = TRUE;

	iCol = sRectSel.left/pSet->m_iTileWidth;
	iRow = sRectSel.top/pSet->m_iTileHeight;
	iMaxCol = sRectSel.right/pSet->m_iTileWidth;
	iMaxRow = sRectSel.bottom/pSet->m_iTileHeight;

	pDIBTiles = pSet->GetDIB();

	if (NULL == pDIBTiles)
		return FALSE;

	if (FALSE == dibSrc.Create(iRectWidth, iRectHeight, pSet->GetTileDepth(), pDIBTiles->GetClrTabAddress()))
		return FALSE;
	
	if (NULL == (hdcSrc = dibSrc.CreateHDC()))
		return FALSE;

	if (NULL == (hdcSet = pDIBTiles->CreateHDC()))
		return FALSE;

	while (iRow < iMaxRow)
	{
		if (FALSE == pSet->Draw(hdcSrc, pLayer->GetTile(iRow, iCol), 
			CPoint(iSrcCol, iSrcRow)))
			return FALSE;

		iCol++;
		iSrcCol += pSet->m_iTileWidth;
		if (iCol == iMaxCol)
		{
			iCol = sRectSel.left/pSet->m_iTileWidth;
			iSrcCol = 0;
			iRow++;
			iSrcRow += pSet->m_iTileHeight;
		}
	}

	iSrcCol = 0;
	iSrcRow = 0;

	if (0 == iType && (0 == iDir || 1 == iDir))
	{
		if (FALSE == dibDest.Create(iRectHeight, iRectWidth, pSet->GetTileDepth(), 
			pDIBTiles->GetClrTabAddress()))
			return FALSE;
		iDestWidth = iRectHeight;
		iDestHeight = iRectWidth;
	}
	else
	{
		if (FALSE == dibDest.Create(iRectWidth, iRectHeight, pSet->GetTileDepth(), 
			pDIBTiles->GetClrTabAddress()))
			return FALSE;
		iDestWidth = iRectWidth;
		iDestHeight = iRectHeight;
	}
	if (NULL == (hdcDest = dibDest.CreateHDC()))
		return FALSE;
	
	
	if (0 == iType)
	{
		if (0 == iDir)
		{
			iDestCol = iRectHeight-1;
			iDestRow = 0;
		}
		else if (1 == iDir)
		{
			iDestCol = 0;
			iDestRow = iRectWidth-1;
		}
		else
		{
			iDestCol = iRectWidth-1;
			iDestRow = iRectHeight-1;
		}
	}
	else
	{
		if (0 == iDir)
		{
			iDestCol = iRectWidth-1;
			iDestRow = 0;
		}
		else
		{
			iDestCol = 0;
			iDestRow = iRectHeight-1;
		}
	}
	while (iSrcRow < iRectHeight)
	{
		clrPix = ::GetPixel(hdcSrc, iSrcCol, iSrcRow);
		::SetPixel(hdcDest, iDestCol, iDestRow, clrPix);
		
		iSrcCol++;
		if (0 == iType)
		{
			if (0 == iDir)
				iDestRow++;
			else if (1 == iDir)
				iDestRow--;
			else
				iDestCol--;
		}
		else
		{
			if (0 == iDir)
				iDestCol--;
			else
				iDestCol++;
		}
		if (iSrcCol == iRectWidth)
		{
			iSrcRow++;
			iSrcCol = 0;
			if (0 == iType)
			{
				if (0 == iDir)
				{
					iDestCol--;
					iDestRow = 0;
				}
				else if (1 == iDir)
				{
					iDestCol++;
					iDestRow = iRectWidth-1;
				}
				else
				{
					iDestCol = iRectWidth-1;
					iDestRow--;
				}
			}
			else
			{
				if (0 == iDir)
				{
					iDestCol = iRectWidth-1;
					iDestRow++;
				}
				else
				{
					iDestCol = 0;
					iDestRow--;
				}
			}
		}
	}

	iDestCol = 0;
	iDestRow = 0;
	iCol = sRectSel.left/pSet->m_iTileWidth;
	iRow = sRectSel.top/pSet->m_iTileHeight;

	hdcSet = NULL;
	
	// Take dibDest and draw it onto the HDC of the temporary tileset
	// Then copy the tiles from the temp set to the actual tileset and set the tiles on the tilelayer
	if (FALSE == sTempSet.Create(pSet->m_iTileHeight, pSet->m_iTileWidth, 
		pSet->GetTileDepth(), pSet->m_iTolerance, iNewTiles, pDIBTiles->GetClrTabAddress(), iDestWidth))
	{
		// cleanup
		return FALSE;
	}

	CDIB *pTempDIB = sTempSet.GetDIB();
	if (NULL == pTempDIB)
	{
		//cleanup
		return FALSE;
	}
	hdcSet = NULL;
	if (NULL == (hdcSet = pTempDIB->CreateHDC()))
	{
		//cleanup
		return FALSE;
	}

	if (FALSE == ::BitBlt(hdcSet, 0, 0, iDestWidth, iDestHeight, hdcDest, 0, 0, SRCCOPY))
	{
		//cleanup
		return FALSE;
	}

	iCol = sRectSel.left/pSet->m_iTileWidth;
	iRow = sRectSel.top/pSet->m_iTileHeight;

	sTempSet.MatchMap();
	pDIBTiles->DeleteHDC();
	pSet->Resize(iNewTiles+iTiles);

	pLayer->SelectNone();
	while (iDestRow < iDestHeight)
	{
		// copy tile from temp set to map tileset
		// set tile on tile layer
		iTempTile = pSet->CopyTile(&sTempSet, iCurTile);
		pLayer->SetTile(iRow, iCol, iTempTile, NULL);
		pLayer->ToggleItem(CPoint(0, 0), iRow, iCol, bJunk);

		iCurTile++;
		iDestCol+=pSet->m_iTileWidth;
		iCol++;
		if (iDestCol >= iDestWidth)
		{
			iDestCol = 0;
			iDestRow+=pSet->m_iTileHeight;
			iCol = sRectSel.left/pSet->m_iTileWidth;
			iRow++;
		}
	}

	// cleanup
	pTempDIB->DeleteHDC();
	dibSrc.DeleteHDC();
	dibDest.DeleteHDC();
	pDIBTiles->DeleteHDC();
	return TRUE;
}
