// CActionRecord.h : header file
//

#ifndef CActionRecord_H
#define CActionRecord_H

#ifdef USE_DATABASE
/*
/////////////////////////////////////////////////////////////////////////////
// CActionRecord DAO recordset

class CActionRecord : public CDaoRecordset
{
public:
	CActionRecord(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CActionRecord)

// Field/Param Data
	//{{AFX_FIELD(CActionRecord, CDaoRecordset)
	CString	csAction;
	long	lKey;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActionRecord)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	CActionRecord& operator=( const CActionRecord& arToCopy );

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
*/
#else	//	not USE_DATABASE

class CActionRecord : public CObject
{
public:
	CActionRecord()		{}
	CActionRecord( const CString& csTextLine );

	CString	csAction;
	long	lKey;

	BOOL	bFileOk;
};

#endif

#endif
