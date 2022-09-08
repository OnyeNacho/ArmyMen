// CActionRecord.cpp : implementation file
//

#include "stdafx.h"
#include "CActionRecord.h"

#ifdef USE_DATABASE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActionRecord

IMPLEMENT_DYNAMIC(CActionRecord, CDaoRecordset)

CActionRecord::CActionRecord(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CActionRecord)
	csAction = _T("");
	lKey = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenSnapshot;
}


CString CActionRecord::GetDefaultDBName()
{
	//return _T("C:\\GenePool\\AnimEditor\\Lookup\\animeditor.mdb");
	return _T("C:\\GenePool\\genepool.mdb");
}

CString CActionRecord::GetDefaultSQL()
{
	return _T("[Action]");
}

void CActionRecord::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CActionRecord)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Action]"), csAction);
	DFX_Long(pFX, _T("[Key]"), lKey);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CActionRecord diagnostics

#ifdef _DEBUG
void CActionRecord::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CActionRecord::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

CActionRecord& CActionRecord::operator=( const CActionRecord& arToCopy )
{
	this->csAction	= arToCopy.csAction;
	this->lKey		= arToCopy.lKey;

	return *this;
}

#else	//	not USE_DATABASE

CActionRecord::CActionRecord( const CString& csTextLine )
{
	//	Given a line of "Actions.txt", parse it into an action string and a key value.
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
	
	csAction = csTextLine.Mid( iFirst + 1, iLast - iFirst - 1 );

	bFileOk = TRUE;
}

#endif