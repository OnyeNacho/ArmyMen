#ifndef __CAnimEditorCommandLine_H_
#define __CAnimEditorCommandLine_H_

class CAnimEditorCommandLine : public CCommandLineInfo
{
public:
	BOOL	bExpectAutoExportFile;
	CString	csAutoExportFile;

	CAnimEditorCommandLine() : CCommandLineInfo()	
	{
		bExpectAutoExportFile = FALSE;
	}

	virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );
};

#endif