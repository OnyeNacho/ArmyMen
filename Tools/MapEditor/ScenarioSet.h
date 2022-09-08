// ScenarioSet.h : header file
//
#ifndef _SCENARIOSET_H_
#define _SCENARIOSET_H_


//  A ScenarioSet consists of a set of players each of 
//  which is associated with a set of unit and resource objects

#include "ObjectSet.h"

/////////////////////////////////////////////////////////////////////////////
// CScenarioSet document

class CScenarioSet : public CObjectSet
{
protected:
	CStringArray m_players;   // array of player names 
    BOOL m_bDeployable;       // non-zero if the current item is a deployable unit
	CScenarioSet();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScenarioSet)

	virtual CString GetObjectID(LPCTSTR lpszPath, CCategory *pCategory);
    void AddObjects(CCategory *pCategory, CString playerDir, CString typeDir);
	CString ParseObjectName(LPCTSTR lpszPath, CString& player, CString& type, CString& filename);

// Attributes
public:
	CString MakeObjectKey(LPCTSTR pszPlayer, LPCTSTR pszObject, BOOL bDeployable);
    int GetCurItem(int& iPlayerID, BOOL& bDeployable);
	CString GetFullObjectName(CMapObject *pObject);
	virtual void SetCurrentItem(int iItem, BOOL bDeployable);
	BOOL GetObjectInfo(CMapObject *pObject,  int& iPlayerID,  BOOL& bDeployable);
	int GetPlayerCount() { return m_players.GetSize(); }
    CString GetPlayerName(int iPlayer) { return m_players[iPlayer]; }

// Operations
public:
	int FindPlayer(LPCTSTR lpszName);
	int AddPlayer(LPCTSTR lpszName) { return m_players.Add(lpszName); }

// Overrides
    CScenarioSet *GetDocument();
	void DeleteContents();
    int FindObject(LPCTSTR lpszID, BOOL bAddFake /* FALSE */);
	void SetCurrentItem(int iItem) { SetCurrentItem(iItem, TRUE); }
    BOOL IsDeployable(CMapObject *pObject);
	BOOL IsItemDeployable()
	{
		return (m_iCurrentItem >= 0 && m_bDeployable);
	}
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScenarioSet)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScenarioSet();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CScenarioSet)
		afx_msg void OnUpdateItemType(CCmdUI* pCmdUI);
	afx_msg void OnFileRevert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
