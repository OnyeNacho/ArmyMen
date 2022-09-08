#include "stdafx.h"
#include "CAnimEditorCommandLine.h"

void CAnimEditorCommandLine::ParseParam( LPCTSTR pszParam, BOOL bFlag, BOOL bLast )
{
	BOOL bHandled = FALSE;

	if( bFlag )
	{
		bExpectAutoExportFile = FALSE;

		if( lstrcmp( pszParam, "auto" ) == 0)
		{
			bExpectAutoExportFile	= TRUE;
			bHandled				= TRUE;
		}
	}
	else
	{
		if( bExpectAutoExportFile )
		{
			csAutoExportFile	= pszParam;
			bHandled			= TRUE;
		}
	}

	if( !bHandled )
		CCommandLineInfo::ParseParam( pszParam, bFlag, bLast );
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
