// ObjectSet.cpp : implementation file
//
#include "stdafx.h"
#include "MapEditor.h"
#include "ObjectSet.h"
#include "MapEditorDoc.h"
#include "AnimMapObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OBJECTSET_HASHTABLE_SIZE 101  // should be prime number
 
CString id_array[26][999];

extern BOOL ParseArmyMenName(CMapObject *pObject, int& iCategory, int& iID);



/////////////////////////////////////////////////////////////////////////////
// CObjectSet

IMPLEMENT_DYNCREATE(CObjectSet, CDocument)

CObjectSet::CObjectSet()
{
	m_iCurrentItem = -1;
}

BOOL CObjectSet::OnNewDocument()
{
   AfxThrowNotSupportedException();
   return FALSE;
}

CObjectSet::~CObjectSet()
{
	TRACE("ObjectSet \"%s\" has been destroyed\n", m_strTitle);
	m_mapList.RemoveAll();
	// everything else is handled in DeleteContents()
}


BEGIN_MESSAGE_MAP(CObjectSet, CDocument)
	//{{AFX_MSG_MAP(CObjectSet)
	ON_COMMAND(ID_FILE_REVERT, OnFileRevert)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMTYPE, OnUpdateItemType)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMID,	OnUpdateItemId)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ITEMINFO, OnUpdateItemInfo)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectSet diagnostics

#ifdef _DEBUG
void CObjectSet::AssertValid() const
{
	CDocument::AssertValid();
}

void CObjectSet::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObjectSet serialization

void CObjectSet::Serialize(CArchive& ar)
{
	AfxThrowNotSupportedException();
}

/////////////////////////////////////////////////////////////////////////////
// CObjectSet commands

void CObjectSet::DeleteContents() 
{
	// Note: this method does not clear m_mapList because
	// presumably re-using the same document would mean 
	// re-using the same m_mapList.  Hopefully this will
	// not get us in trouble later on...
	m_iCurrentItem = -1;
	CCategory *pCategory;
	while (!m_categories.IsEmpty())
	{
		pCategory = m_categories.RemoveHead();
		delete pCategory;
	}
	int iCount = GetObjectCount();
	for (int i=0; i < iCount; i++)
	{
		delete m_objects[i];
	}
	m_objects.RemoveAll();
	m_objectMap.RemoveAll();
	CDocument::DeleteContents();
}




void CObjectSet::OnFileRevert() 
{
	if (IsModified())
	{
		CString msg;
		AfxFormatString1(msg, IDS_REVERT_MAY_LOSE_DATA, GetPathName());
		if (AfxMessageBox(msg, MB_ICONQUESTION|MB_YESNO) != IDYES)
			return;
	}

	POSITION pos = m_mapList.GetHeadPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
		ASSERT(pDoc != NULL);
		pDoc->BuildObjectTable();
	}

	OnOpenDocument(GetPathName());

	// worse comes to worse we have an empty document;
	// the map ObjectLayers *can* handle not having any
	// object data.

	// update all the maps
	pos = m_mapList.GetHeadPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
		ASSERT(pDoc != NULL);
		pDoc->UpdateObjects();
		pDoc->UpdateAllViews(NULL);
	}

	UpdateAllViews(NULL,OSV_UPDATE_ALL);
}

/*
** METHOD 
**   CObjectSet::LoadMatchingFiles
**
** PARAMETERS
**    const CString& pathName   -- directory to scan for files
**    const CString& ext        -- extension of files to load (ie: "bmp")
**    CCategory *pCategory      -- category to which loaded files should be added.
**
** DESCRIPTION
**    Loads all non-hidden files with the given extension fro the
**    given directory into the given category.   
**   
*/
void CObjectSet::LoadMatchingFiles(const CString& pathName, const CString& ext, CCategory *pCategory, int eObjectType)
{
    ASSERT(pCategory != NULL);
	int iExtLength = ext.GetLength();
	CString pattern = pathName + "\\*." + ext;
	WIN32_FIND_DATA fdata;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFile(pattern, &fdata);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fdata.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_HIDDEN)))
			{
				TRY
				{   CWaitCursor wait;
					CString filePath = pathName + "\\" + fdata.cFileName;
					// stupid windows, it shouldn't match.bmpx to .bmp
					int iDot = filePath.ReverseFind('.');
					ASSERT(iDot>= 0);
					if (iDot == (filePath.GetLength() - iExtLength - 1))
					{
						CString id = GetObjectID(filePath, pCategory);
						char *str = id.GetBuffer(40);

						char *pThird;
						strtok(str, "_");
						strtok(NULL, "_");
						pThird = strtok(NULL, "_");
						if (pThird == NULL)
						{
							CString loading;
							loading.Format(IDS_LOADING_FILE,fdata.cFileName);
							ShowStatus(loading);
							AddObject(filePath, pCategory, eObjectType);
						}
					}
				}
				END_TRY // don't abort just because of a bad object
			}   
		} while (FindNextFile(hFind, &fdata));
		FindClose(hFind);
	}
}

BOOL CObjectSet::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document.\n");

	CWaitCursor wait;
	DeleteContents();

	CString pathName;
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
					TRY 
					{
						CString adding;
						adding.Format(IDS_ADDING_CATEGORY, data.cFileName);
						ShowStatus(adding);
					}
					END_TRY
					CCategory *pCategory = AddCategory(data.cFileName);
					CString subdir = pathName + pCategory->GetTitle();
                    LoadMatchingFiles(subdir, "bmp", pCategory, eBmpObject);
					LoadMatchingFiles(subdir, "axr", pCategory, eAxrObject);
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

void CObjectSet::AddMap(CMapEditorDoc *pMap)
{
	m_mapList.AddHead(pMap);
}

void CObjectSet::RemoveMap(CMapEditorDoc *pMap)
{ 
	POSITION pos = m_mapList.Find(pMap);
	if (pos != NULL)
	{
		m_mapList.RemoveAt(pos); 
		OnChangedViewList();
	}
}

CString CObjectSet::GetObjectID(LPCTSTR lpszPath, CCategory *pCategory)
{
	CString id = lpszPath;
	CString filename;

	// if the id contains a \ then it is in a subdirectory
    if (StripComponent(id,filename,'\\')) // strip off the subdirectory name
	{
		// prepend the category name (not done for normal objects)
//		ASSERT(pCategory != NULL); 
//		id = pCategory->GetTitle() + "\\" + filename;
		id = filename;
	}
	id.MakeLower(); // hash function is case-sensitive
	return id;
}
	
int CObjectSet::AddObject(LPCTSTR pathName, CCategory *pCategory, int eObjectType)
{
	CMapObject *pObject;
	switch(eObjectType)
	{
	   case eBmpObject:
			pObject = new CStaticMapObject(pathName);
			break;
	   case eAxrObject:
		    pObject = new CAnimMapObject(pathName);
			break;
	   default:
		    AfxThrowNotSupportedException();
		    break;
	}

	ASSERT(pCategory != NULL);
	ASSERT_NEW(pObject);

	int iIndex = m_objects.Add(pObject);
	if (iIndex >= 0)
	{
		pCategory->AddItem(iIndex);

		ASSERT(pCategory != NULL); 
		pObject->m_pszFolder = pCategory->GetTitle();

	    CString id = GetObjectID(pathName, pCategory);
		CMapObject *pExists;
		if (m_objectMap.Lookup(id, pExists))	{
			CString msg;
			msg.FormatMessage( IDS_DUPLICATE_OBJECT_NAME, pObject->m_pszFolder, id);
			UserError(msg);
		}

		int iCategory, iID;
		if (ParseArmyMenName(pObject,iCategory,iID))
		{
			if (id_array[iCategory][iID] == "")
				id_array[iCategory][iID] = pObject->GetName();
			else	{
				if (id_array[iCategory][iID] != pObject->GetName())	{
					CString msg;
					msg.FormatMessage( IDS_DUPLICATE_OBJECT_NUMBER, id_array[iCategory][iID], pObject->GetName());
					UserError(msg);
				}
			}
		}

		m_objectMap[id] = pObject;
		pObject->m_ID = iIndex;
		VERIFY(m_objectMap.LookupKey(id, pObject->m_lpszKey));
	}
	else
		delete pObject;

	return iIndex;
}

int CObjectSet::FindObject(LPCTSTR lpszID, BOOL bAddFake /* FALSE */)
{
	CMapObject *pObject;
	CString name = lpszID;
	name.MakeLower(); // hash function is case-sensitive

	if (m_objectMap.Lookup(name,pObject))	{
//		strcmp(pObject->m_pszFolder,"");
		return pObject->m_ID;
	}
 
	if (bAddFake)
	{
		CMapObject *pFake = new CMapObject(name);
		ASSERT_NEW(pFake);

	    pFake->m_ID = m_objects.Add(pFake);
		m_objectMap[name] = pFake;

		VERIFY(m_objectMap.LookupKey(name, pFake->m_lpszKey));
		return pFake->m_ID;
	}
	return -1;
}


void CObjectSet::DrawObject(HDC hdc, int iIndex, CPoint pt, HDC hdcTemp, CDIB *pDst,
							int iSequence, int iFrame, BOOL bFlipped)
{ 
	GetObject(iIndex)->Draw(hdc, pt, hdcTemp, pDst, iSequence, iFrame, bFlipped);	
}

void CObjectSet::DrawWithPalette( HDC hdc, int iIndex, RECT& dstRect, HPALETTE hPalette)
{
	GetObject(iIndex)->DrawWithPalette(hdc, dstRect, hPalette);
}


CMapObject * CObjectSet::GetCurrentObject()
{
	if (m_iCurrentItem >= 0 && m_iCurrentItem < GetObjectCount())
	{
		return GetObject(m_iCurrentItem);
	}
	return NULL;
}

void CObjectSet::OnChangedViewList() 
{
	// if no more views on the document, delete ourself
	// not called if directly closing the document or terminating the app
	if (m_viewList.IsEmpty() && m_bAutoDelete && !HasOpenMaps())
	{
		OnCloseDocument();
		return;
	}

	// update the frame counts as needed
	UpdateFrameCounts();
}


afx_msg void CObjectSet::OnUpdateItemType(CCmdUI* pCmdUI)
{
	CMapObject *pObject = GetCurrentObject();
	CString string;
	if (pObject)
	{
		if (pObject->IsKindOf(RUNTIME_CLASS(CAnimMapObject)))
			string.LoadString(IDS_ANIM);
		else
			string.LoadString(IDS_OBJECT);
		pCmdUI->SetText(string);
	}
	pCmdUI->Enable(TRUE);
}

afx_msg void CObjectSet::OnUpdateItemId(CCmdUI* pCmdUI)
{
	CMapObject *pObject = GetCurrentObject();
	if (pObject)
	{
		pCmdUI->SetText(pObject->GetName());
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->SetText(NULL);
		pCmdUI->Enable(FALSE);
	}
}

afx_msg void CObjectSet::OnUpdateItemInfo(CCmdUI* pCmdUI)
{
	CMapObject *pObject = GetCurrentObject();
	if (pObject)
	{
		CSize size = pObject->GetSize();
		CString dimensions;
		int iDepth = pObject->GetDepth();
		dimensions.Format("%d x %d x %d", size.cx, size.cy, iDepth);
		pCmdUI->SetText(dimensions);
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->SetText(NULL);
		pCmdUI->Enable(FALSE);
	}
}

void CObjectSet::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CObjectSet::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}


void CObjectSet::RemapObjects(CPalette *pPalette)
{
	ASSERT(pPalette != NULL);

	CString msg;
	int iCount = GetObjectCount();

	for (int i=0; i < iCount; i++)
	{
		CMapObject *pObject = m_objects[i];
		TRY
		{
			msg.Format(IDS_REMAPPING_OBJECT,pObject->GetName());
			ShowStatus(msg);
		}
		END_TRY
		
		pObject->Remap(pPalette);
	}

	// refresh all the associated maps 
	POSITION pos = m_mapList.GetHeadPosition();
	while (pos != NULL)
	{
		CMapEditorDoc *pDoc = m_mapList.GetNext(pos);
		ASSERT(pDoc != NULL);
		pDoc->UpdateAllViews(NULL);
	}
	UpdateAllViews(NULL);
	ShowStatus(NULL);
}

int CObjectSet::GetObjectCategory(int iObject)
{
//	CString pszName = GetObject(iObject)->GetKey();
	CString pszName = GetObject(iObject)->GetFolder();
//	int slash = pszName.Find('\\');
//	if (slash > 0)
//	{
//		pszName = pszName.Left(slash);
		return FindCategory(pszName);
//	}
//	return -1; 
}

int CObjectSet::FindCategory(const CString& pszName)
{
	POSITION pos = m_categories.GetHeadPosition();
	int iIndex = 0;
	while (pos != NULL)
	{
		CCategory *pCategory = m_categories.GetNext(pos);
		if (pszName.CompareNoCase(pCategory->GetTitle()) == 0)
			return iIndex;
		else
			++iIndex;
	}
	return -1;
}
