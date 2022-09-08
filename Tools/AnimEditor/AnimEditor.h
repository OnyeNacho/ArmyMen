// AnimEditor.h : main header file for the ANIMEDITOR application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "CActionRecord.h"
#include "CDirectionRecord.h"
#include "CVersion.h"

/////////////////////////////////////////////////////////////////////////////
// CAnimEditorApp:
// See AnimEditor.cpp for the implementation of this class
//

#define WM_AUTOEXPORT (WM_USER+1)


class CAnimEditorApp : public CWinApp
{
public:
	CAnimEditorApp();
	virtual ~CAnimEditorApp();

private:
	BOOL				bAppQuit;

public:
	CString				csAppPath;

	CMultiDocTemplate*	pCelViewTemplate;

	CString				csCelClipboardFormatName;
	CString				csSequenceCelClipboardFormatName;
	CLIPFORMAT			clipFormatCel;
	CLIPFORMAT			clipFormatSequenceCel;
	int					iSizeClipFormatCelBlock;
	int					iSizeClipFormatSequenceCelBlock;
	COLORREF			colorDialog;
	COLORREF			colorWindow;
	BOOL				bAutoCrop;
	CVersion			appVersion;
	CVersion			docVersion;

	CTypedPtrList< CObList, CActionRecord* >	lstActions;		//	List of actions, pulled from Action table or "Actions.txt".
	CTypedPtrList< CObList, CDirectionRecord* >	lstDirections;	//	List of sequence directions, pulled from "Directions.txt".
//	CList< int, int >							lstDirections;	//	List of sequence directions, pulled from "Directions.txt".

	COLORREF			colorTransparent;	//	Transparent color - RGB value of 0, 0 in "palette.bmp".
	BYTE				indexTransparent;	//	Palette index of transparent color.

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimEditorApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnimEditorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileAutocrop();
	afx_msg void OnUpdateFileAutocrop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// The one and only CAnimEditorApp object

extern CAnimEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
