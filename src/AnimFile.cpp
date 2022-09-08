/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: AnimFile.cpp $
//
//	DESCRIPTION:	animation loading routines
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Thursday, February 27, 1997
//
//	REVISION:		$Header: /ArmyMen/src/AnimFile.cpp 16    4/02/98 2:03p Phu $
//
//	Copyright (C) 1996-97 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/AnimFile.cpp $
//  
//  16    4/02/98 2:03p Phu
//  typecasting to prevent warnings
//  
//  15    3/06/98 5:50p Phu
//  convert extension to upr for comp
//  
//  14    1/30/98 12:42p Nrobinso
//  add CheckAnimFree which removes all remaining sequence copies
//  
//  13    1/29/98 4:59p Nrobinso
//  extra anim error checking
//  
//  12    1/29/98 10:58a Nrobinso
//  fix sequence copying between sequences
//  
//  11    12/23/97 6:01p Phu
//  anim shadows
//  
//  10    12/09/97 12:11p Phu
//  
//  9     12/02/97 5:27p Nrobinso
//  allow sharing of anim command lists
//  
//  8     12/01/97 6:20p Nrobinso
//  turn off trace
//  
//  7     11/20/97 12:07p Bwilcox
//  indent command not loaded msg
//  
//  6     10/30/97 12:58p Nrobinso
//  turn on error for command not found
//  
//  5     9/30/97 10:28p Nrobinso
//  turn off long trace messagers
//  
//  3     8/07/97 11:08p Nrobinso
//  moved globals.h to stdafx.h
//  
//  2     7/14/97 12:55p Nrobinso
//  fixup exception handling
//  
//  1     7/03/97 5:17p Nrobinso
//  
//  8     5/14/97 1:42a Nrobinso
//  put trace messages under compile time control
//  
//  7     5/05/97 10:07a Nrobinso
//  add CheckAnim() to look for unloaded anim sequences
//  
//  6     4/25/97 10:21a Nrobinso
//  rearrange AnimImport to better handle non-exitant anim files
//  
//  5     4/23/97 3:43p Nrobinso
//  Add global catalogs
//  
//  4     3/17/97 10:58a Nrobinso
//  fix new CSpriteCatlog call
//  
//  3     3/06/97 4:44p Nrobinso
//  added load flags to AnimImport()
//
//  2     3/03/97 1:35p Nrobinso
//  fix ProcessAnim args
//  
//  1     3/03/97 7:54a Nrobinso
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Anim.h"
#include "AnimFile.h"

// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Code

CSpriteCatalog *
AnimImport(LPCTSTR pathName, LONG flags) {
#ifdef ANIM_DEBUG
	TRACE("Importing Anim %s\n",pathName);
#endif

	if (flags & BM_RLE)
		ASSERT((flags & BM_OPAQUE) == 0);

	
	CSpriteCatalog *pCatalog = NULL;
	CFile fileImport;
	if (fileImport.Open( pathName, CFile::modeRead, NULL ))	{
		pCatalog = new CSpriteCatalog;

		char extension[4];
		strcpy( extension, pathName + strlen(pathName)-3 );
		strupr( extension );
		if( strcmp( extension, "AXS" ) == 0 )
			flags |= BM_ANIM_SHADOW;
		pCatalog->SetFlags(flags);

		TRY
		{
			CArchive arImport( &fileImport, CArchive::load );
			pCatalog->Serialize(arImport);
		}
		CATCH_ALL(E)
		{
			TRACE("Error in AnimImport()\n");
			delete pCatalog;
			pCatalog = NULL;
//			THROW_LAST();
		}
		END_CATCH_ALL
	}

	return pCatalog;
}

void
FreeAnimImport(CSpriteCatalog *pCatalog)	{
	if (pCatalog)
		delete pCatalog;
}


void
ProcessAnim(CSpriteCatalog *pCatalog, COMMAND_LIST *pCommandList)	{
	pCatalog->ProcessAnim(pCommandList);
}

BOOL
CheckAnim(COMMAND_LIST *pCommandList, char *animname, COMMAND_LIST *pDefaultCommandList)	{
	BOOL ok = TRUE;
	char *name = "Unknown";

	if (animname)
		name = animname;

	for (int i=0; i<pCommandList->commands; i++)	{
		if (pCommandList->command_array[i].seq == NULL)	{
			if (pDefaultCommandList)	{
				for (int j=0; j<pDefaultCommandList->commands; j++)	{
					if (pCommandList->command_array[i].command_now == pDefaultCommandList->command_array[j].command_now)	{
						pCommandList->command_array[i].seq = pDefaultCommandList->command_array[j].seq;
						pCommandList->command_array[i].copy_seq = TRUE;
						break;
					}
				}
			}

			if (pCommandList->command_array[i].seq == NULL)	{
				TRACE("    Command %d not loaded for %s\n", pCommandList->command_array[i].command_now, name);
				ok = FALSE;
			}
		}
	}

	return ok;
}

BOOL
CheckAnimFree(COMMAND_LIST *pCommandList)	{
	BOOL ok = TRUE;
	COMMAND *pCommand = pCommandList->command_array;

	for (int i=0; i<pCommandList->commands; i++)	{
		if (pCommand[i].seq != NULL)	{
			if (!pCommand[i].copy_seq)	{
				ok = FALSE;
				Error("Anim Sequence not deleted");
				ASSERT(0);
			}
		}
		pCommand[i].seq = NULL;
		pCommand[i].copy_seq = FALSE;
	}

	return ok;
}

///========================================================================
//									EOF
///========================================================================
