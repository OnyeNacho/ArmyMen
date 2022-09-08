/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Armymen.h $
//
//	DESCRIPTION:	main header file for the ARMYMEN application
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Thursday, May 23, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Armymen.h 12    3/23/98 6:42p Nrobinso $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/Armymen.h $
//  
//  12    3/23/98 6:42p Nrobinso
//  remove about box
//  
//  11    2/01/98 10:58p Nrobinso
//  removed old dialog code
//  
//  10    12/09/97 12:11p Phu
//  
//  9     11/26/97 2:27p Aburgess
//  modifications made to support MultiPlayer Campaign Select
//  
//  8     10/07/97 8:21a Aburgess
//  made theApp available
//  
//  6     9/29/97 3:41p Aburgess
//  lastest changes for DIALOG representations of FullScreen UI screens
//  
//  5     9/23/97 3:00p Aburgess
//  latest modifications for Dialog base version
//  
//  4     9/12/97 9:50a Aburgess
//  Addition of AUDIO Diagnostic dialog
//  
//  3     9/02/97 9:40a Aburgess
//  added new dialog class functions
//  
//  2     7/08/97 4:17p Phu
//  Override Run() member for CArmyMenApp to call MainLoop.
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  8     2/13/97 9:42a Nrobinso
//  added version info (dipslayed in About Box)
//  
//  7     9/10/96 1:00p Aburgess
//  move commonly used but infrequently changed header files to stdafx.h
//  (precompiled header)
//  
//  6     9/09/96 8:22p Aburgess
//  removed old MFC declaration
//  
//  5     9/03/96 2:47p Aburgess
//  expanded Box definition
//  
//  4     7/31/96 9:13p Nrobins
//  Added comments in structs
//  
//  3     6/28/96 5:45a Nrobins
//  Added FileOpen command to Load maps
// 
// 2     6/25/96 9:53p Nrobins
// added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __ARMYMEN_H__
#define __ARMYMEN_H__

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "CVersion.h"

/////////////////////////////////////////////////////////////////////////////
// CArmyMenApp:
// See ArmyMen.cpp for the implementation of this class
//

class CArmyMenApp : public CWinApp
{
public:
				CArmyMenApp();
virtual			~CArmyMenApp();
 
afx_msg void	OnFileOpen( );
int				Run();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArmyMenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CArmyMenApp)
	afx_msg void OnTestGameStartDialog();
	afx_msg void OnTestGameOptionsDialog();
	afx_msg void OnTestServiceProviderDialog();
	afx_msg void OnTestGameSetupDialog();
	afx_msg void OnTestHostSessionDialog();
	afx_msg void OnTestJoinSessionDialog();
	afx_msg void OnTestSelectCampaignDialog();
	afx_msg void OnTestSelectMissionDialog();
	afx_msg void OnTestMultiPlyrSelectCampaignDialog();
	afx_msg void OnTestJoinArmySelectDialog();
	afx_msg void OnTestTitleScreenDialog();
	afx_msg void OnAudioDiagnosticDialog();
	afx_msg void OnScrnRemoteTest();
	//}}AFX_MSG

public:
	CVersion			appVersion;
	CVersion			docVersion;

protected:
	DECLARE_MESSAGE_MAP()
};

extern	CArmyMenApp theApp;

#endif
