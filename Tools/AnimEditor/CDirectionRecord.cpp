// CDirectionRecord.cpp : implementation file
//

#include "stdafx.h"
#include "CDirectionRecord.h"

CDirectionRecord::CDirectionRecord( const CString& csTextLine )
{
	//	Given a line of "Directions.txt", parse it into an action string and a key value.
	//	NOTE ABOUT ACTIONS.TXT:
	//		Key value must appear at the beginning of a line. Action string must appear in double quotes on same line.
	bFileOk = FALSE;

	CString csNumber = csTextLine.SpanIncluding( " 0123456789" );
	if( csNumber == "" )
		return;

	lKey = atol( csNumber );
	
	int iFirst = csTextLine.Find( '\"' );
	if( iFirst == -1 )
		return;
	int iLast = csTextLine.ReverseFind( '\"' );
	if( iLast == -1 || iLast == iFirst || iLast == iFirst + 1 )
		return;
	
	csDirection = csTextLine.Mid( iFirst + 1, iLast - iFirst - 1 );

	bFileOk = TRUE;
}
