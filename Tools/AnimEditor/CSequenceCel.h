//	CSequenceCel.h

#ifndef CSEQUENCECEL_H
#define CSEQUENCECEL_H

#include "stdafx.h"

class CCel;
class CAnimEditorDoc;
class CSequence;

/////////////////////////////////////////////////////////////////////////////

class CHSpotLoc : public CObject		//	Hot spot locations. Tied to CHSpots in CSequence. (Matches based on place in list.)
{
public:
	CHSpotLoc();
	CHSpotLoc( CCel* pCel );
	virtual ~CHSpotLoc();	
	DECLARE_SERIAL(CHSpotLoc)

public:
	int			x;
	int			y;

public:
	virtual void Serialize( CArchive& ar );

};

/////////////////////////////////////////////////////////////////////////////

class CSequenceCel : public CObject
{
public:
	CSequenceCel();
	CSequenceCel( CSequence* pOwnerSequence, CCel* pCel );
//	CSequenceCel( CCel* pCel );
	virtual ~CSequenceCel();	
	DECLARE_SERIAL(CSequenceCel)

protected:
//	CSequence*	pOwnerSequence;	

public:
	CCel*		pCel;				//	CCel that I'm linked to.
	BOOL		bSelected;
	BOOL		bDragSelected;
	CTypedPtrList< CObList, CHSpotLoc* >		lstHSpotLocs;		//	List of hotspotlocs included in sequence.	
	BOOL		bActionFrame;		//	True if cel set as the ArmyMen "action frame" for this sequence (there can be only one).

public:
	virtual void	Serialize( CArchive& ar );
	void			LinkToCelByFileName( CAnimEditorDoc* pDoc, const CString& csFile );
	void			CreateHSpotLocs( CSequence* pSequence );
	void			DeleteHSpotLoc( int iDel );
	void			SetPrimaryHotSpot( const CPoint& ptPrimary );
	CPoint			ptPrimaryHotSpot();

};

#endif
