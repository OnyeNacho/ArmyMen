// MapEditor.h : main header file for the MAPEDITOR application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "mymacros.h"
#include "MyMultiDocTemplate.h"

#define MAPEDIT_MAJOR_VERSION 6
#define MAPEDIT_MINOR_VERSION 15

/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp:
// See MapEditor.cpp for the implementation of this class
//

class CMapEditorApp : public CWinApp
{
protected:
	void SerializeProfileColor(BOOL bSave, LPCTSTR section, LPCTSTR name, COLORREF& color);
	void SerializeProfileInt(BOOL bSave, LPCTSTR section, LPCTSTR name, int& iValue);
	void SerializeProfileUInt(BOOL bSave, LPCTSTR section, LPCTSTR name, UINT& iValue);
	void SerializeProfileBool(BOOL bSave, LPCTSTR section, LPCTSTR name, BOOL& bValue);
	void SerializeProfileString(BOOL bSave, LPCTSTR section, LPCTSTR name, CString& pszValue);
	void SerializeSettings(BOOL bSave);
	void LoadStdProfileSettings(UINT nMaxMRU = _AFX_MRU_COUNT);
	BOOL GetProfileBool( LPCTSTR lpszSection, LPCTSTR lpszEntry, BOOL nDefault )
	{
		UINT val = GetProfileInt(lpszSection,lpszEntry,(UINT)nDefault);
		return (BOOL) val ? TRUE : FALSE;
	}
	BOOL WriteProfileBool( LPCTSTR lpszSection, LPCTSTR lpszEntry, BOOL nValue )
	{
		return WriteProfileInt(lpszSection, lpszEntry, (UINT)nValue);
	}


public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMyMultiDocTemplate *m_pMapDocTemplate;
	CMyMultiDocTemplate *m_pTileSetTemplate;
	CMyMultiDocTemplate *m_pObjectSetTemplate;
	CMyMultiDocTemplate *m_pScenarioSetTemplate;
	CMapEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEditorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMapEditorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateAttributeDecimal(CCmdUI* pCmdUI);
	afx_msg void OnAttributeDecimal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// Global variables/defaults
extern CMapEditorApp theApp;
extern UINT g_nBitmapWidth;
extern BOOL g_bUseBitmapWidth;
extern BOOL g_bCompactOnSave;
extern UINT g_nMapWidth;
extern UINT g_nMapHeight;
extern BOOL g_bMapRepeat;
extern UINT g_nTileWidth;
extern UINT g_nTileHeight;
extern BOOL g_bOutlinePreview;
extern BOOL g_bOldDataFormat;  // for backward compatibility with first doc format.
extern COLORREF g_rgbTransparent;
extern COLORREF g_rgbColors[16];
extern UINT g_nTileSetFormat;
extern UINT g_nObjectLayerFormat;
extern UINT g_nAttributeLayerFormat;
extern BOOL g_bTemporaryPaste;
extern BOOL g_bActivePreview;
extern CString g_pszMapTileSet;
extern CString g_pszInitTileData;
extern CString g_pszMapObjectSet;
extern BOOL g_bShowFullObjectName;
extern BOOL g_bUseOffScreenDibs;
extern BOOL g_bDecimal;
extern BOOL g_bPlaceWithAttributes;
extern CFindReplaceDialog *g_pReplaceDlg;
extern UINT WM_FINDREPLACE;
extern CString g_pszScenarioResources;
extern CString g_pszScenarioUnits;
extern CString g_pszMapScenarioSet;
extern CString g_pszArmyMenTriggers[8];
extern COLORREF g_rgbMapColor; // background color for map

#define MAX_MAP_WIDTH 65535
#define MAX_MAP_HEIGHT 65535
#define MAX_TILE_WIDTH 255
#define MAX_TILE_HEIGHT 255

/////////////////////////////////////////////////////////////////////////////
// Serialization Macros: 
//     yuk..there's got to be a better way...thanks Microsoft :-(
//
UINT GetSafeSchema(CArchive& ar, CRuntimeClass *pClass, UINT first_safe_schema);

#define GET_SAFE_SCHEMA(archive, classname, first_safe_schema) \
	GetSafeSchema(archive, RUNTIME_CLASS(classname), first_safe_schema)

#define PUT_SAFE_SCHEMA(ar, classname) \
	(ar).SerializeClass(RUNTIME_CLASS(classname))
/////////////////////////////////////////////////////////////////////////////

void UserError(UINT nID,int iCondition=TRUE);
void UserError(LPCTSTR msg, int iCondition=TRUE);
void UserWarn(UINT nID, int iCondition=TRUE);

CString GetValueString(int iValue);
CString GetFullValueString(int iValue);

void ShowStatus(LPCTSTR msg);
CRect GetPropRect(CRect rect, CSize size);

BOOL StripComponent(CString& path, CString& tail, char cSeperator);
BOOL DoChooseColor(CWnd *pWnd, COLORREF& color);

#define ARMYMEN_MAP_EXT  "AMM"
#define ARMYMEN_TILE_EXT "ATL"

#define U_SPLASH 1  // 0 to disable splash screen


