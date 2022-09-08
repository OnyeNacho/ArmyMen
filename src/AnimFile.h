/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: AnimFile.h $
//
//	DESCRIPTION:	Animation loading interface
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Thursday, February 27, 1997
//
//	REVISION:		$Header: /ArmyMen/src/AnimFile.h 5     1/30/98 12:42p Nrobinso $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/AnimFile.h $
//  
//  5     1/30/98 12:42p Nrobinso
//  add CheckAnimFree which removes all remaining sequence copies
//  
//  4     12/09/97 12:11p Phu
//  
//  3     12/02/97 5:34p Nrobinso
//  CheckAnim takes a default pointer
//  
//  1     7/03/97 5:17p Nrobinso
//  
//  5     5/05/97 10:07a Nrobinso
//  add CheckAnim() to look for unloaded anim sequences
//  
//  4     4/23/97 3:43p Nrobinso
//  Add global catalogs
//  
//  3     3/06/97 4:44p Nrobinso
//  added load flags to AnimImport()
//  
//  2     3/03/97 1:40p Nrobinso
//  added anim processing routine
//  
//  1     3/03/97 7:54a Nrobinso
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////
#include "CSpriteCatalog.h"

#ifndef __ANIMFILE_H__
#define __ANIMFILE_H__

/////////////////////////////////////////////////////////////////////////////
//					Structures
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////
CSpriteCatalog *AnimImport(LPCTSTR pathName, LONG flags);
void FreeAnimImport(CSpriteCatalog *pCatalog );
void ProcessAnim(CSpriteCatalog *pCatalog, COMMAND_LIST *pCommandList);
BOOL CheckAnim(COMMAND_LIST *pCommandList, char *animname, COMMAND_LIST *pDefaultCommandList);
BOOL CheckAnimFree(COMMAND_LIST *pCommandList);

#endif
