// ScenarioSet.cpp : implementation file
//
// From an implementation point of view: a ScenarioSet is
// just an ObjectSet with an even number of categories,
// where each pair of categories is associated with a
// player name.
//
//    Player[i] is always associated with:
//       a set of unit objects = m_categories[2 * i] 
//   and a set of resource objects = m_categories[2 * i + 1]
//
//  Note: we keep the player names seperate from the
//  category names just to save space. And since we
//  always know the name of the desired units and 
//  resource directories we don't need to store the
//  real category names either.
//
//  BUT, the object "key" contains both the player
//  name AND the internal unit/resource name so we can
//  accurately identify each object, where it belongs,
//  and whether or not it is deployable.
//
#include "stdafx.h"
#include "MapEditor.h"
#include "MapEditorDoc.h"
#include "ScenarioSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// INTERNAL unit and resource directory names: these can be mapped to the
// current unit/resource directory names when necessary.
//
// Note: the code assumes that these simple 1 letter names.
#define UNITNAME "0"
#define RESOURCENAME "1"

/////////////////////////////////////////////////////////////////////////////
// CScenarioSet

IMPLEMENT_DYNCREATE(CScenarioSet, CObjectSet)

CScenarioSet::CScenarioSet()
{
	m_bDeployable = FALSE;
}


#define OBJECTSET_HASHTABLE_SIZE 101  // should be prime number


CScenarioSet::~CScenarioSet()
{
	TRACE("CScenarioSet \"%s\" has been destroyed\n", m_strTitle);
	m_mapList.RemoveAll();
	// everything else is handled in DeleteContents()
}

void CScenarioSet::DeleteContents()
{
	CObjectSet::DeleteContents();
	m_players.RemoveAll();
	m_bDeployable = FALSE;
}

BEGIN_MESSAGE_MAP(CScenarioSet, CObjectSet)
	//{{AFX_MSG_MAP(CScenarioSet)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMTYPE, OnUpdateItemType)
	ON_COMMAND(ID_FILE_REVERT, OnFileRevert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScenarioSet diagnostics

#ifdef _DEBUG
void CScenarioSet::AssertValid() const
{
	CObjectSet::AssertValid();
}

void CScenarioSet::Dump(CDumpContext& dc) const
{
	CObjectSet::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScenarioSet serialization

void CScenarioSet::Serialize(CArchive& ar)
{
	AfxThrowNotSupportedException();
}

/////////////////////////////////////////////////////////////////////////////
// CScenarioSet implemenation
/////////////////////////////////////////////////////////////////////////////

void CScenarioSet::AddObjects(CCategory *pCategory, CString playerDir, CString typeDir)
{
    CString pathName = playerDir + "\\" + typeDir;
	LoadMatchingFiles(pathName, "bmp", pCategory, eBmpObject);
}

/*
** METHOD
**   CScenarioSet::ParseObjectName
**
** PARAMETERS
**   LPCTSTR lpszPath  -- full path to the object's bitmap file
**   CString& player   -- place to store the player name string
**   CString& type     -- place to store the units/resource type string
**   CString& filename -- place to store the object bmp filename
**
** DESCRIPTION
**    parses the bitmap file path and returns the player, type and
**    filename components.
**
** RETURNS
**    the remainder of the path (ie: the path up to the player 
**    directory) if any.
*/
CString CScenarioSet::ParseObjectName(LPCTSTR lpszPath, CString& player, CString& type, CString& filename)
{
    CString path = lpszPath;
	path.MakeLower(); // hash function is case-sensitive

	VERIFY(StripComponent(path,filename,'\\'));
	VERIFY(StripComponent(path,type,'\\'));
	if (!StripComponent(path,player,'\\') && !StripComponent(path,player,':'))
	{
		player = path;
		path.Empty();
	}
	return path;
}

CString CScenarioSet::GetObjectID(LPCTSTR lpszPath, CCategory *pCategory)
{
    CString id, type, filename;
	ParseObjectName(lpszPath, id, type, filename);

	ASSERT(pCategory != NULL);
    id += "\\" + pCategory->GetTitle() + "\\" + filename;
	return id;
}

CString CScenarioSet::MakeObjectKey(LPCTSTR pszPlayer, LPCTSTR pszObject, BOOL bDeployable)
{
	CString key = pszPlayer;
	key += "\\";
	key +=  bDeployable ? UNITNAME : RESOURCENAME;
	key += "\\";
	key += pszObject;
	key += ".bmp";
	return key;
}

/*
** METHOD
**   CScenarioSet::FindObject
** 
** PARAMETERS
**   LPCTSTR lpszID  -- the ID or hash key for the scenario object
**   BOOL bAddFake   -- TRUE to add a new object with lpszID and no bitmap image
**                      
** DESCRIPTION
**   checks to see if an object with the given ID/hashkey is 
**   already present in this CScenarioSet.  If isn't and bAddFake
**   is TRUE, a new "fake" object -- one with no associated bitmap
**   image -- will be added to the scenario objects.
**
**  RETURNS
**    the index of the scenario object with the given id
**    or -1 if the object could not be found and/or created.
**
**  SIDE-EFFECTS
**    If a fake object IS added to the scenario set, it may also
**    add a new player name and its associated unit/resource categories
**    to the CScenarioSet.
**
**  EXCEPTIONS
**     CMemoryException
*/
int CScenarioSet::FindObject(LPCTSTR lpszID, BOOL bAddFake /* FALSE */)
{
	CMapObject *pObject;
    CString id, player, type, filename;
	ParseObjectName(lpszID, player, type, filename);

    ASSERT(!type.CompareNoCase(UNITNAME) || !type.CompareNoCase(RESOURCENAME));
	id = player + "\\" + type + "\\" + filename;
	if (m_objectMap.Lookup(id,pObject))
		return pObject->m_ID;
 
	if (bAddFake)
	{	
		// object doesn't exits so we don't care about loading it.
		CMapObject *pFake = new CMapObject(id);
		ASSERT_NEW(pFake);

		int iObjectID = m_objects.Add(pFake);
	    pFake->m_ID = iObjectID;
		m_objectMap[id] = pFake;

		VERIFY(m_objectMap.LookupKey(id, pFake->m_lpszKey));

		int iPlayer = FindPlayer(player);
		CCategory *pUnits, *pResources, *pCategory;

		if (iPlayer < 0)
		{
			iPlayer = AddPlayer(player);
            pUnits = AddCategory(UNITNAME);
		    pResources = AddCategory(RESOURCENAME);
		}
		else
		{
			int iIndex = iPlayer * 2;
			pUnits = GetCategory(iIndex);
			pResources = GetCategory(iIndex + 1);
		}
		ASSERT(pUnits != NULL);
		ASSERT(pResources != NULL);

		if (!type.CompareNoCase(UNITNAME))
			pCategory = pUnits;
		else
			pCategory = pResources;

		pCategory->AddItem(iObjectID);
		return iObjectID;
	}
	return -1;
}

int CScenarioSet::FindPlayer(LPCTSTR lpszPlayerName)
{
	int iCount = GetPlayerCount();
	for (int i=0; i < iCount; i++)
	{
		if (m_players.GetAt(i).CompareNoCase(lpszPlayerName)==0)
			return i;
	}
	return -1;
}

BOOL CScenarioSet::IsDeployable(CMapObject *pObject)
{
	CString pszKey = pObject->GetKey();
	int iSeperator = pszKey.Find('\\');
	ASSERT(iSeperator >= 0);

	ASSERT(UNITNAME[0] != RESOURCENAME[0]);
	return pszKey[iSeperator + 1] == UNITNAME[0];
}

/*
** METHOD
**    CScenarioSet::GetObjectInfo
**
** PARAMETERS
**    CMapObject *pObject -- object to lookup info
**    int& iPlayerID      -- place to store the player index 
**    BOOL& bDeployable   -- place to store the deployable attribute of the given object
**
** DESCRIPTION
**    if the given object COULD belong to this CScenarioSet
**    (ie: it has a valid player name) returns the index of the
**    player it WOULD belong to AND its deployability attribute.
**
**  RETURNS
**    TRUE if has a valid player index.
**
**  NOTES
**    This function DOES NOT actually verify that the object
**    belongs to this CScenarioSet.  
** 
**  SEE ALSO
**    CScenarioSet::FindObject()
*/
BOOL CScenarioSet::GetObjectInfo(CMapObject *pObject,  int& iPlayerID,  BOOL& bDeployable)
{
	ASSERT(pObject != NULL);
    CString player, type, filename;
	ParseObjectName(pObject->GetKey(), player, type, filename);
	
	if ((iPlayerID = FindPlayer(player)) >= 0)
	{
		bDeployable = (type == UNITNAME);
		return TRUE;
	}
	return FALSE;
}

void CScenarioSet::SetCurrentItem(int iItem, BOOL bDeployable)
{
	m_bDeployable = bDeployable;
	CObjectSet::SetCurrentItem(iItem);
}

// Returns the player\bitmap name
CString CScenarioSet::GetFullObjectName(CMapObject *pObject)
{
	CString name = pObject->GetKey();
	int iSeperator = name.Find('\\');
	ASSERT(iSeperator >= 0);
	name = name.Left(iSeperator + 1) + pObject->GetName();
	return name;
}

/////////////////////////////////////////////////////////////////////////////
// CScenarioSet commands

BOOL CScenarioSet::OnNewDocument()
{
	AfxThrowNotSupportedException();
	return FALSE;
}

BOOL CScenarioSet::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document.\n");

	CWaitCursor wait;
	DeleteContents();

	CString pathName, player;
	WIN32_FIND_DATA data;
    HANDLE hFind = INVALID_HANDLE_VALUE;

	TRY
	{
		m_objectMap.InitHashTable(OBJECTSET_HASHTABLE_SIZE);
#ifdef WIDE_PATHS
		pathName = "\\\\?\\";
		pathName += lpszPathName;
		pathName += "\\";
		hFind = FindFirstFileW(pathName + "*", &data);
#else
		pathName = lpszPathName;
		pathName += "\\";
		hFind = FindFirstFile(pathName + "*", &data);
#endif
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if ((data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ||
						!strcmp(data.cFileName,".") ||
						!strcmp(data.cFileName,".."))
						continue;
					player = data.cFileName;
					TRY {
						CString adding;
						adding.Format(IDS_ADDING_PLAYER, data.cFileName);
						ShowStatus(adding);
					}
					END_TRY
					
					int iPlayer = AddPlayer(player);
					ASSERT(iPlayer >= 0);

					player = pathName + data.cFileName;
					AddObjects(AddCategory(UNITNAME), player, g_pszScenarioUnits);
					AddObjects(AddCategory(RESOURCENAME), player, g_pszScenarioResources);
				}
			} 
			while (FindNextFile(hFind, &data));
			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
		}
	}
	CATCH_ALL(e)
	{
		if (hFind != INVALID_HANDLE_VALUE)
			FindClose(hFind);
		THROW_LAST();
	}
	END_CATCH_ALL
	ShowStatus(NULL);
	return TRUE;
}

afx_msg void CScenarioSet::OnUpdateItemType(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(m_bDeployable ? g_pszScenarioUnits : g_pszScenarioResources);
}


int CScenarioSet::GetCurItem(int& iPlayerID, BOOL& bDeployable)
{
	if (m_iCurrentItem >= 0)
	{
		GetObjectInfo(GetObject(m_iCurrentItem), iPlayerID, bDeployable);
		ASSERT(m_bDeployable == bDeployable);
		m_bDeployable = bDeployable;
	}
	else
		iPlayerID = 0;
	return m_iCurrentItem;
}

void CScenarioSet::OnFileRevert() 
{
	if (IsModified())
	{
		CString msg;
		AfxFormatString1(msg, IDS_REVERT_MAY_LOSE_DATA, GetPathName());
		if (AfxMessageBox(msg, MB_ICONQUESTION|MB_YESNO) != IDYES)
			return;
	}

	OnOpenDocument(GetPathName());

	// worse comes to worse we have no object data
	// the map ScenarioLayers should be able to handle 
	// not having any objects

	// update all the maps
	POSITION pos = m_mapList.GetHeadPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
		ASSERT(pDoc != NULL);
		pDoc->UpdateScenarios();
		pDoc->UpdateAllViews(NULL);
	}
	UpdateAllViews(NULL,OSV_UPDATE_ALL);
}


