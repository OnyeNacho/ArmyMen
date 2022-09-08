//	CSequence.h

#ifndef CSequence_H
#define CSequence_H

#include "stdafx.h"

#include "CSequenceCel.h"

#define SEQUENCE_SPEEDMIN	0		//	Min and max values for iSpeed.
#define SEQUENCE_SPEEDMAX	99		//	 "

#define NO_BACKGROUND "None selected"

class CAnimEditorDoc;
class CSequenceView;
class CDIBitmap;

/////////////////////////////////////////////////////////////////////////////

class CHSpot : public CObject
{
public:
	CHSpot();
	CHSpot( BOOL bPrimary, const CString& csName );
	virtual ~CHSpot();	
	DECLARE_SERIAL(CHSpot)

public:
	BOOL		bPrimary;		//	True for one hotspot in a list only.
	CString		csName;

public:
	virtual void Serialize( CArchive& ar );

};

/////////////////////////////////////////////////////////////////////////////

class CSequence : public CObject
{
public:
	CSequence();
	CSequence( CAnimEditorDoc* pDoc );
	virtual ~CSequence();	
	DECLARE_SERIAL(CSequence)

protected:
//	//	The following can't be done because it causes a circular dependency between CCel.h and CSequence.h...
//	//	CTypedPtrList< CObList, CCel* >		lstCels;	//	List of cels included in sequence (serialized using cel keys).
//	CObList				lstSeqCels;		//	List of cels included in sequence (serialized using cel keys).

public:
	CTypedPtrList< CObList, CSequenceCel* >		lstSeqCels;		//	List of sequencecels included in sequence.
	CAnimEditorDoc*		pOwnerDoc;								//	Pointer to AnimEditorDoc that owns me.
	CSequenceView*		pSeqView;								//	Pointer to the view that shows me.

	//	Serialized...
	CString				csName;
	int					iSpeed;			//	Frames per second animation speed.
	int					iMoveSpeed;		//	Pixels per Frames animation movement speed.
	long				lAction;		//	Key of action, in Action table.
	int					iDirection;		//	Direction of object motion.
	CTypedPtrList< CObList, CHSpot* >			lstHSpots;		//	List of hotspots included in sequence.	

	CString				csBackgroundBMP;
	CDIBitmap*			pdibBackground;

private:
	void				CreateLinkedSequenceView();
	void				ForceMultipleSequencesViewArrange();

public:
	virtual void		Serialize( CArchive& ar );
	int					iCountSelected();
	POSITION			PosFirstSelectedSeqCel();
	int					iFirstSelectedSeqCel();
	void				SequenceCelSelect( POSITION posCel, UINT nFlags );
	void				SequenceCelSelectOnly( CSequenceCel* pSeqCelSelect );
	BOOL				DeleteSelected( BOOL bDragSelected );
	void				PutDataOnClipboard( COleDataSource* pData );
	void				GetDataFromClipboard();
	void				DeleteSequenceCelMatchingCel( CCel* pCel );
	void				ConvertSelectedToDragSelected();
	void				ClearDragSelected();
	CSize				ImageBoundsMax();
	void				AddHSpot();
	void				DeleteHSpot( int iDel );
	void				SetBackgroundBMP( const CString& csFileBMP );
	BOOL				LoadBackgroundBMP( const CString& csFileBMP );

	void				SetHotspotForCelInstances( CCel* pCel, int iX, int iY );
};

#endif