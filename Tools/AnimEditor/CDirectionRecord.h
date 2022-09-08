// CDirectionRecord.h : header file
//

#ifndef CDirectionRecord_H
#define CDirectionRecord_H

class CDirectionRecord : public CObject
{
public:
	CDirectionRecord()		{}
	CDirectionRecord( const CString& csTextLine );

	CString	csDirection;
	long	lKey;

	BOOL	bFileOk;
};

#endif
