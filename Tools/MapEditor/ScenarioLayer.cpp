#include "stdafx.h"
#include "MapEditor.h"
#include "MapFrame.h"
#include "MapEditorDoc.h"
#include "ScenarioLayer.h"
#include "ScenarioSet.h"
#include "ScenarioView.h"
#include "MapUpdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int  g_iScenarioInfoVersion = FALSE; // hack to load ScenarioInfo v1
//////////////////////////////////////////////////////////////////////////////
// CScenarioInfo
#define SCENARIOINFO_VERSION 3
IMPLEMENT_SERIAL(CScenarioInfo, CObject, VERSIONABLE_SCHEMA | SCENARIOINFO_VERSION)

void CScenarioInfo::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	// Note: we use a simple versioning because the CMap will allocate
	// an array of these objects and call Serialize directly. We don't
	// want to store the class info (via PUT_SAFE_SCHEMA) for each 
	// element because it just wastes too much space and we are already
	// wasting a lot storing the player names.
	if (ar.IsStoring())
	{
		ar << (int)SCENARIOINFO_VERSION; 
		ar << m_nTotal;
		ar << m_nDeployed;
		ar << m_ID; // version >= 2
		m_openList.Serialize(ar); // version >= 3
	}
	else
	{
		ar >> g_iScenarioInfoVersion;
		ar >> m_nTotal;
		ar >> m_nDeployed;
		if (g_iScenarioInfoVersion >= 2)
		{
			ar >> m_ID; 
		}
		if (g_iScenarioInfoVersion >= 3)
		{
			m_openList.Serialize(ar);
		}
		else
		{
			m_openList.SetSize(m_nTotal);

			for (int i=0; i<m_openList.GetSize(); i++)	{
				m_openList[i] = FALSE;
			}
		}
	}
}

void AFXAPI SerializeElements( CArchive& ar, CScenarioInfo* pElements, int nCount )
{
	for (int i=0; i < nCount; i++)
	{
		pElements[i].Serialize(ar);
	}
}

int CScenarioInfo::NextNumber()
{
	BOOL true_value = TRUE;

	for (int i=0; i<m_openList.GetSize(); i++)	{
		if (m_openList[i] == FALSE)
		{
			TRACE("Added %d\n", i);
			m_openList[i] = TRUE;
			return i;
		}
	}

	// didn't find a free number, so add a new one
	m_openList.Add(true_value);
	TRACE("Added new %d\n", m_openList.GetUpperBound());
	return m_openList.GetUpperBound();
}

void CScenarioInfo::ClearNumber(int iNumber)
{
	m_openList[iNumber] = FALSE;
	TRACE("Cleared %d\n", iNumber);
}


///////////////////////////////////////////////////////////////////////////////////
// CScenarioLayer
CScenarioLayer::~CScenarioLayer()
{
	TRACE("Deleting scenario %s\n",GetTitle());
	m_infoTable.RemoveAll();
}

CScenarioLayer::CScenarioLayer(CMapEditorDoc *pDoc, LPCSTR lpszTitle) 
: CObjectLayer(pDoc, lpszTitle)
{
	m_infoTable.InitHashTable(101);
}

CScenarioLayer::CScenarioLayer()
: CObjectLayer()
{
	m_infoTable.InitHashTable(101);
}

//////////////////////////////////////////////////////////////////////////////

#define SCENARIOLAYER_VERSION 2
IMPLEMENT_SERIAL(CScenarioLayer, CObjectLayer, VERSIONABLE_SCHEMA | SCENARIOLAYER_VERSION)

void CScenarioLayer::Serialize(CArchive& ar) 
{
	// Note: since CScenarioLayers are only used dynamically we can
	// avoid the PUT_SAFE_SCHEMA/GET_SAFE_SCHEMA
	if (ar.IsStoring())
	{
		CObjectLayer::Serialize(ar);
		m_infoTable.Serialize(ar); // schema >= 2
	}
	else
	{
		UINT nSchema = ar.GetObjectSchema();
		CObjectLayer::Serialize(ar);
		if (nSchema >= 2) 
			m_infoTable.Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CScenarioLayer, CObjectLayer)
	//{{AFX_MSG_MAP(CScenarioLayer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////
CObjectSet *CScenarioLayer::GetObjectSet()
{
	return GetScenarioSet();
}

void CScenarioLayer::RemoveObjectAt(POSITION pos)
{
	CMapObjectInst *pInstance = m_objects.GetAt(pos);
	ASSERT(pInstance != NULL);

	CMapObject *pObject = GetScenarioSet()->GetObject(pInstance->m_ID);
	ASSERT(pObject != NULL);

	ASSERT(GetScenarioSet()->IsDeployable(pObject));

	LPCTSTR pszKey = pObject->GetKey();
	CScenarioInfo info;

	VERIFY(m_infoTable.Lookup(pszKey,info));
	ASSERT(info.m_ID == pInstance->m_ID);
	ASSERT(info.m_nDeployed > 0);
	--info.m_nDeployed;

	// mark number as freed & reset the next open number
	info.ClearNumber(pInstance->m_iNumber);

	m_infoTable.SetAt(pszKey,info);

	CObjectLayer::RemoveObjectAt(pos);
}
	
BOOL CScenarioLayer::SetObjectTotal(LPCTSTR lpszKey, int iObjectID, UINT nTotal, BOOL bDeployable)
{
	CScenarioInfo info;
	LPCTSTR lpszKeyTest;

	lpszKeyTest = GetScenarioSet()->GetObject(iObjectID)->GetKey();
	ASSERT(strcmp(lpszKey, lpszKeyTest) == 0);

//	ASSERT(lpszKey == GetScenarioSet()->GetObject(iObjectID)->GetKey());
	if (GetObjectInfo(lpszKey, info))
	{
		ASSERT(info.m_ID == iObjectID);
		if (bDeployable && (nTotal < info.m_nDeployed))
		{
			// If the user wants to decrease the total number of a
			// certain deployable object, they will first have to
			// remove the deployed objects from the scenario.
			return FALSE;
		}
	}
	if (nTotal == 0)
	{
		// Don't bother to keep information about objects that are
		// not used in this scenario.
		m_infoTable.RemoveKey(lpszKey);
	}
	else
	{
		info.m_ID = iObjectID;
		info.m_nTotal = nTotal;
		m_infoTable.SetAt(lpszKey,info);
	}
	return TRUE;
}
 
CMapLayer *CScenarioLayer::CropToSelection(CRect rect, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol, BOOL bSelectedOnly)
{
#ifdef _DEBUG
	CMapLayer::CropToSelection(rect,iStartRow,iStartCol,iEndRow,iEndCol,bSelectedOnly); // verify pre-conditions
#endif

	CScenarioLayer *pLayer = new CScenarioLayer;
	ASSERT_NEW(pLayer);

	// copy the table of non-zero totals
	POSITION pos = m_infoTable.GetStartPosition();
	CString pszKey;
	CScenarioInfo info;
	while (pos != NULL)
	{
		m_infoTable.GetNextAssoc(pos,pszKey,info);
		info.m_nDeployed = 0; // assume nothing is deployed
		pLayer->m_infoTable.SetAt(pszKey,info);
	}
	// fill in all the deployed objects
	pLayer->SetMap(GetMap());
	return FinishCrop(pLayer,(iEndRow > GetMap()->m_iMapHeight) ? 1 : 0, (iEndCol > GetMap()->m_iMapWidth) ? 1 : 0, rect,bSelectedOnly);
}

void CScenarioLayer::ScenarioFormatText(CString &dest, CString &pszKey, int iNumber)
{
	int len;
	int index;
	int base;
	CString mid;
	CString right;
	char numberstr[8];
	CString title = GetTitle();

	index = title.FindOneOf( "23456789" );
	if (index == -1)
		base = 0;
	else
		base = title[index] - '1';
	
	base *= 100;
	sprintf(numberstr, "%d", base+iNumber+1);

	len = pszKey.GetLength();
	mid = pszKey.Mid(2,len-6);	// crops off botht the #- prfix and the .bmp

	index = mid.Find("\\0\\");
	len = mid.GetLength();

	dest = mid.Left(index);
	dest.SetAt(0, _toupper(dest[0]));

	right = mid.Right(len-index-3);
	right.SetAt(0, _toupper(right[0]));

	dest += right;
	dest += numberstr;
}

void CScenarioLayer::AddObject(CMapObjectInst *pInstance)
{
	ASSERT(pInstance != NULL);

	CScenarioSet *pScenarioSet = GetScenarioSet();
	CMapObject *pObject = pScenarioSet->GetObject(pInstance->m_ID);
	CString pszKey = pObject->GetKey();
	CScenarioInfo info;
    BOOL bDeployable = pScenarioSet->IsDeployable(pObject);

	// Reminder: if the id is not in the table, the object has a "0" total.
//	if (bDeployable && m_infoTable.Lookup(pszKey,info))
	if (bDeployable)
	{
		if (!m_infoTable.Lookup(pszKey,info))
		{
			SetObjectTotal(pszKey, pInstance->m_ID, 1, bDeployable);
			VERIFY(m_infoTable.Lookup(pszKey,info));
		}

		ASSERT(info.m_ID == pInstance->m_ID);

		if (info.m_nDeployed == info.m_nTotal)
		{
			info.m_nTotal += 1;
//			m_infoTable.SetAt(pszKey,info);
		}

//		if (info.m_nDeployed < info.m_nTotal)
//		{
			CObjectLayer::AddObject(pInstance);

			// set the number of the unit
			pInstance->m_iNumber = info.NextNumber();

			if (pInstance->m_sTextBlock.IsEmpty())	{
				ScenarioFormatText(pInstance->m_sTextBlock, pszKey, pInstance->m_iNumber);
			}
			else	{
				CString msg;
				msg.FormatMessage( "Trying to reset %s unit text\n", pInstance->m_sTextBlock );
				UserError(msg);
			}

			info.m_nDeployed += 1;
			m_infoTable.SetAt(pszKey,info);
			pScenarioSet->UpdateAllViews(NULL,OSV_UPDATE_ITEM);
			return;
//		}
	}
	else	{
		CString msg;
//		msg.Format(bDeployable ? IDS_DEPLOYMENT_ERROR : IDS_RESOURCE_DEPLOYMENT_ERROR,
//				   pScenarioSet->GetFullObjectName(pObject));
		msg.Format(IDS_RESOURCE_DEPLOYMENT_ERROR, pScenarioSet->GetFullObjectName(pObject));
		UserError(msg);	
	}
}


#ifdef DEBUG
void CScenarioLayer::AssertValid() const;
{
	CObjectLayer::AssertValid();
	POSITION pos = m_infoTable.GetStartPosition();
	CScenarioSet *pScenarioSet = GetScenarioSet();
	CScenarioInfo info;
	CString pszName;

	if (pScenarioSet)
	{
		while (pos != NULL)
		{	  
			GetNextAssoc( pos, pszName, info); 
			int iID = pScenarioSet->FindObject(pszName);
			CMapObject *pObject = pScenarioSet->GetObject(iID);
			if (pScenarioSet->IsDeployable(pObject))
			{
				ASSERT(info.m_nDeployed <= info.m_nTotal);
				UINT nTotal = CountOccurrences(info.m_ID);
				ASSERT(info.m_nDeployed == nTotal);
			}
		}
	}
}
#endif

CMapLayerMode CScenarioLayer::PlaceItem(CPoint point, int iRow, int iColumn)
{
	CScenarioSet *pScenarioSet = GetScenarioSet();
    ASSERT(pScenarioSet != NULL);
    int iObject = pScenarioSet->GetCurrentItem();
	if (iObject >= 0)
	{
		if (pScenarioSet->IsItemDeployable())
		{
			return CObjectLayer::PlaceItem(point, iRow, iColumn);
		}
		else TRY 
		{
			CString msg;
			CMapObject *pObject = pScenarioSet->GetObject(iObject);
			msg.Format(IDS_RESOURCE_DEPLOYMENT_ERROR,pScenarioSet->GetFullObjectName(pObject));
			UserError(msg);
		}
		END_TRY
	}
	return none;
}

// Note: this method assumes that all views of the map share the same active
// layer. This is kind of a shame; 
void CScenarioLayer::Activate(BOOL bRefresh)
{
	CMapFrame *pFrame = GetParentFrame();
	if (pFrame)
		pFrame->InstallToolPane(RUNTIME_CLASS(CScenarioView), 
		                        theApp.m_pScenarioSetTemplate, GetScenarioSet(), bRefresh);
}


// called whenever the ScenarioSet is changed
void CScenarioLayer::UpdateObjects()
{
	CScenarioSet *pScenarioSet = GetScenarioSet();
	ASSERT(pScenarioSet != NULL);

	CString pszKey;
	CScenarioInfo info;
    CMap<int,int,int,int> objectMap;
    objectMap.InitHashTable(101);

	// update the infoTable IDs
	POSITION pos = m_infoTable.GetStartPosition();
	while (pos != NULL)
	{	
		m_infoTable.GetNextAssoc(pos, pszKey, info);
		int iObjectID = pScenarioSet->FindObject(pszKey, TRUE);
		ASSERT(iObjectID >= 0);
		if (g_iScenarioInfoVersion == 1)
			info.m_ID = iObjectID;   // hack for v1.0 compatibility; assumes exact same scenarioset
		objectMap.SetAt(info.m_ID, iObjectID); // map old id to new id
		info.m_ID = iObjectID;
    	m_infoTable.SetAt(pszKey, info);

	}
	// update the IDs of all the objects; must be done as a second pass
	pos = GetFirstObjectPosition();
	while (pos != NULL)
	{
		CMapObjectInst *pInstance = GetNextObject(pos);
		VERIFY(objectMap.Lookup(pInstance->m_ID, pInstance->m_ID));
	}
}
