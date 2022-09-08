//	CSequenceCel.cpp

#include "stdafx.h"
#include "CSequenceCel.h"

#include "CCel.h"
#include "AnimEditorDoc.h"
#include "AnimEditor.h"

IMPLEMENT_SERIAL(CHSpotLoc, CObject, 1)

//-----------------------------------------------------------------------------------------------------------------
//	CHSpotLoc implementation.
//-----------------------------------------------------------------------------------------------------------------
CHSpotLoc::CHSpotLoc()
{
	//	Used by Serialize only.
}

CHSpotLoc::CHSpotLoc( CCel* pCel )
{
//	x = (int)( ( pCel->GetWidth() + 1 ) / 2 );
//	y = (int)( ( pCel->GetHeight() + 1 ) / 2 );
	x = 0;
	y = 0;
}

CHSpotLoc::~CHSpotLoc()
{
}

void CHSpotLoc::Serialize( CArchive& ar )
{
	if( ar.IsStoring() )
	{
		ar << theApp.docVersion.major;
		ar << x << y;
	}
	else
	{
		int iAFCVersion;
		ar >> iAFCVersion;
		ar >> x >> y;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	Constructor/Destructor
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CSequenceCel, CObject, 1)

CSequenceCel::CSequenceCel()
{
	bSelected		= FALSE;
	bDragSelected	= FALSE;
	bActionFrame	= FALSE;
}

CSequenceCel::CSequenceCel( CSequence* pOwnerSequence, CCel* pCel ) 
//CSequenceCel::CSequenceCel( CCel* pCel ) 
{
//	this->pOwnerSequence	= pOwnerSequence;	//xxx needed?
	this->pCel				= pCel;
	bSelected				= FALSE;
	bDragSelected			= FALSE;
	CreateHSpotLocs( pOwnerSequence );
	bActionFrame			= FALSE;
}

CSequenceCel::~CSequenceCel()
{
	//	Delete constructed hotspotlocs.
	POSITION posInList;
	CHSpotLoc*	pHSpotLoc;
	while( posInList = lstHSpotLocs.GetHeadPosition() )
	{
		pHSpotLoc = lstHSpotLocs.GetAt( posInList );
		delete pHSpotLoc;
		lstHSpotLocs.RemoveAt( posInList );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceCel::Serialize( CArchive& ar )
{
	//	Serialize using the filename of pCel...

	if (ar.IsStoring())
	{
		ar << theApp.docVersion.major;
		ar << pCel->csFileBMP;
		ar << bActionFrame;
	}
	else
	{
		int iAFCVersion;
		ar >> iAFCVersion;
		CString csFileBMP;
		ar >> csFileBMP;
		LinkToCelByFileName( (CAnimEditorDoc*)ar.m_pDocument, csFileBMP );
		if( iAFCVersion > 2 )		//	ajw Version set to 3 and bActionFrame added on 5/9/97.
			ar >> bActionFrame;
	}
	lstHSpotLocs.Serialize( ar );
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceCel::LinkToCelByFileName( CAnimEditorDoc* pDoc, const CString& csFile )
{
	//	Sets pCel to point to cel in pDoc keyed to csFile.
	//	( pCel is set to NULL if matching cel not found.)
	pCel = pDoc->GetCelPtrByFileName( csFile );
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceCel::CreateHSpotLocs( CSequence* pSequence )
{
	//	Create CHSpotLoc objects for each CHSpot that exists in pSequence.
	//	Part of CSequenceCel creation, done after I have been linked to a cel.

	ASSERT( pCel );
	POSITION posInList = pSequence->lstHSpots.GetHeadPosition();
	CHSpot*	pHSpot;
	while( posInList )
	{
		pHSpot = pSequence->lstHSpots.GetNext( posInList );
		CHSpotLoc* pHSpotLoc = new CHSpotLoc( pCel );
		lstHSpotLocs.AddTail( pHSpotLoc );
	}
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceCel::DeleteHSpotLoc( int iDel )
{
	//	Delete hspotloc at index iDel in list.
	POSITION posInList = lstHSpotLocs.FindIndex( iDel );
	ASSERT( posInList );
	CHSpotLoc* pHSpotLoc = lstHSpotLocs.GetAt( posInList );
	ASSERT( pHSpotLoc );
	lstHSpotLocs.RemoveAt( posInList );
	delete pHSpotLoc;	
}

//-----------------------------------------------------------------------------------------------------------------
void CSequenceCel::SetPrimaryHotSpot( const CPoint& ptPrimary )
{
	//	Primary hotspot is always first in list.
	POSITION posInList = lstHSpotLocs.GetHeadPosition();
	ASSERT( posInList );
	CHSpotLoc* pHSpotLoc = lstHSpotLocs.GetAt( posInList );
	pHSpotLoc->x = ptPrimary.x;
	pHSpotLoc->y = ptPrimary.y;
}

//-----------------------------------------------------------------------------------------------------------------
CPoint CSequenceCel::ptPrimaryHotSpot()
{
	//	Primary hotspot is always first in list.
	CPoint ptPrimary;
	POSITION posInList = lstHSpotLocs.GetHeadPosition();
	ASSERT( posInList );
	CHSpotLoc* pHSpotLoc = lstHSpotLocs.GetAt( posInList );
	ptPrimary.x = pHSpotLoc->x;
	ptPrimary.y = pHSpotLoc->y;
	return ptPrimary;
}
