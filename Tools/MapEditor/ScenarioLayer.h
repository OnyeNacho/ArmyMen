#ifndef _SCENARIOLAYER_H_
#define _SCENARIOLAYER_H_

#include "ObjectLayer.h"

class CScenarioInfo : public CObject
{
	DECLARE_SERIAL(CScenarioInfo)

public:
	int m_ID;           // for mostly for serialization
	UINT m_nTotal;
	UINT m_nDeployed;
	CArray<BOOL, int> m_openList;

	CScenarioInfo()
	{
		m_ID = m_nTotal = m_nDeployed = 0;
	}
	void operator=(CScenarioInfo& src)
	{
		m_nTotal = src.m_nTotal;
		m_nDeployed = src.m_nDeployed;
		m_ID = src.m_ID;
//		m_openList.Copy(src.m_openList);	// There is a bug in the CArray Copy function!
		for (int i=0; i<src.m_openList.GetSize(); i++)	{
			m_openList.SetAtGrow(i, src.m_openList[i]);
		}
	}
    virtual void Serialize(CArchive& ar);
	int NextNumber();
	void ClearNumber(int iNumber);
};

void AFXAPI SerializeElements( CArchive& ar, CScenarioInfo* pElements, int nCount );


class CScenarioLayer : public CObjectLayer
{
protected:
	CMap<CString,LPCTSTR,CScenarioInfo,CScenarioInfo&> m_infoTable;

// Attributes
public:
	void UpdateObjects();

// Operations
public:
	CScenarioLayer(CMapEditorDoc *pMap, LPCSTR lpszTitle);
	BOOL GetObjectInfo(LPCTSTR key, CScenarioInfo& info) 
	{ 
		return m_infoTable.Lookup(key,info);
	}
	BOOL GetObjectInfo(CMapObject *pObject, CScenarioInfo& info) 
	{ 
		ASSERT(pObject != NULL);
		return m_infoTable.Lookup(pObject->GetKey(),info);
	}
	UINT GetObjectTotal(LPCTSTR key)
	{
		CScenarioInfo info;
		ASSERT(info.m_nTotal == 0);
		GetObjectInfo(key,info);
		return info.m_nTotal;
	}
	BOOL SetObjectTotal(LPCTSTR lpszKey, int iObjectID, UINT nTotal, BOOL bDeployable);
    
// Overrides
	virtual ~CScenarioLayer();
	virtual CObjectSet *GetObjectSet();
	virtual void Activate(BOOL bRefresh);
	virtual CMapLayerMode PlaceItem(CPoint point, int iRow, int iColumn);
	virtual void DoCutCopyPaste(CArchive &ar, BOOL bCut)
	{
		CObjectLayer::DoCutCopyPaste(ar,bCut);
		GetScenarioSet()->UpdateAllViews(NULL,OSV_UPDATE_ITEM); //deployment count may have changed
	}
	CMapLayer *CropToSelection(CRect rect, int iStartRow, int iStartCol,
					  int iEndRow, int iEndCol, BOOL bSelectedOnly);
#ifdef DEBUG
	virtual void AssertValid() const;
#endif
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScenarioLayer)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CScenarioLayer();  // for serialization
	DECLARE_SERIAL(CScenarioLayer)
	virtual void AddObject(CMapObjectInst *pInstance);
    virtual void RemoveObjectAt(POSITION pos);

	void ScenarioFormatText(CString &dest, CString &pszKey, int iNumber);

	// Generated message map functions
	//{{AFX_MSG(CScenarioLayer)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif