//	CSpriteSequence.cpp

#include "stdafx.h"
#include "resource.h"
#include "CSpriteSequence.h"
#ifdef ANIMEDITORDOC_VERSION
#include "..\animeditor\CSequence.h"
#include "..\animeditor\AnimEditorDoc.h"
#include "..\animeditor\CCel.h"
#include "CSpriteCatalog.h"
#endif

/////////////////////////////////////////////////////////////////////////////
//	Constructor/Destructor
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CSpriteSequence, CObject, 1)

CSpriteSequence::CSpriteSequence()
{
	//	Used by Serialize only.
#ifndef ANIMEDITORDOC_VERSION
	bSerializeRLE = TRUE;			//	change - needed because of problem that you can't set it before it exists!!! xxx
#endif
}

#ifdef ANIMEDITORDOC_VERSION
CSpriteSequence::CSpriteSequence( CAnimEditorDoc* pDoc, CSpriteCatalog* pCat, CSequence* pSeqToCopy, BOOL bRLE )
{
	csName		= pSeqToCopy->csName;
	lAction		= pSeqToCopy->lAction;
	iDirection	= pSeqToCopy->iDirection;
	iSpeed		= pSeqToCopy->iSpeed;
	iFrames		= pSeqToCopy->lstSeqCels.GetCount();
	iHotspots	= pSeqToCopy->lstHSpots.GetCount() - 1;		//	-1 because the primary is not included here.

	if( !bRLE )
		arOrigins.SetSize( iFrames );
	else
		arRLEOffsets.SetSize( iFrames );

	arSizes.SetSize( iFrames );
	arOffsets.SetSize( iFrames );
	arHotspots.SetSize( iFrames * iHotspots );

	POSITION posInList = pSeqToCopy->lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	CPoint* pptAdd;
	int iFrameCount = 0;
	int iHotspotsCount = 0;
	while( posInList )
	{
		pSeqCel = pSeqToCopy->lstSeqCels.GetNext( posInList );
		if( !bRLE )
		{
			//	Origin of image in strip bitmap.
			pptAdd = new CPoint;
			*pptAdd = ptOriginOfCelInStrip( pDoc, pSeqCel->pCel );
			arOrigins.SetAt( iFrameCount, pptAdd );
		}
		else
		{
			//	Origins of image as a memory offset can't be set until images are RLE'd. Set in Initialize_RLEOffsets(). 
		}
		//	Size of image.
		pptAdd = new CPoint( pSeqCel->pCel->GetWidth(), pSeqCel->pCel->GetHeight() );
		arSizes.SetAt( iFrameCount, pptAdd );
		//	Get hotspot locations.
		POSITION posHSpotLoc = pSeqCel->lstHSpotLocs.GetHeadPosition();
		POSITION posNow;
		CHSpotLoc* pHSpotLoc;
		while( posNow = posHSpotLoc )
		{
			pHSpotLoc = pSeqCel->lstHSpotLocs.GetNext( posHSpotLoc );
			pptAdd = new CPoint( pHSpotLoc->x - pSeqCel->pCel->xCrop, pHSpotLoc->y - pSeqCel->pCel->yCrop );
			if( posNow == pSeqCel->lstHSpotLocs.GetHeadPosition() )		//	[ First hotspot == primary ]
				arOffsets.SetAt( iFrameCount, pptAdd );
			else
				arHotspots.SetAt( iHotspotsCount++, pptAdd );	//	[ We are storing these in an implicit 2D array: [ frame, hotspot ]. ]
		}
		iFrameCount++;
	}
	//	arRLEOffsets is used only when RLE sequence is imported into a game.
}
#endif

CSpriteSequence::~CSpriteSequence()
{
	//	Delete created CPoints.
	int i;
	for( i = 0; i <= arOrigins.GetUpperBound(); i++ )
		delete arOrigins[ i ];
	for( i = 0; i <= arSizes.GetUpperBound(); i++ )
		delete arSizes[ i ];
	for( i = 0; i <= arOffsets.GetUpperBound(); i++ )
		delete arOffsets[ i ];
	for( i = 0; i <= arHotspots.GetUpperBound(); i++ )
		delete arHotspots[ i ];
}

//-----------------------------------------------------------------------------------------------------------------
#ifdef ANIMEDITORDOC_VERSION
void CSpriteSequence::Initialize_RLEOffsets( CSpriteCatalog* pCat, CSequence* pSeqToCopy )
{
	//	Set arRLEOffsets values. Second part of CSpriteSequence construction when exporting RLE.
	POSITION posInList = pSeqToCopy->lstSeqCels.GetHeadPosition();
	CSequenceCel* pSeqCel;
	int iFrameCount = 0;
	while( posInList )
	{
		pSeqCel = pSeqToCopy->lstSeqCels.GetNext( posInList );
		//	Pull from map created when the images were RLE'd in CSpriteCatalog::Initialize_RLE(), just before our call.
		VERIFY( pCat->mapCelStartPos.Lookup( pSeqCel->pCel->csFileBMP, arRLEOffsets[iFrameCount] ) );
		iFrameCount++;
	}
}
#endif

//-----------------------------------------------------------------------------------------------------------------
void CSpriteSequence::Serialize( CArchive& ar )
{
	int iVersion;
	int i;
	if( ar.IsStoring() )
	{
#ifdef ANIMEDITORDOC_VERSION
		iVersion = 2;
		ar << iVersion;
		ar << csName << lAction << iDirection << iSpeed << iFrames << iHotspots;
		if( !bSerializeRLE )
		{
			for( i = 0; i < iFrames; i++ )
				ar << arOrigins[ i ]->x << arOrigins[ i ]->y;
		}
		else
			arRLEOffsets.Serialize( ar );

		for( i = 0; i < iFrames; i++ )
			ar << arSizes[ i ]->x << arSizes[ i ]->y;
		for( i = 0; i < iFrames; i++ )
			ar << arOffsets[ i ]->x << arOffsets[ i ]->y;
		for( i = 0; i < iFrames * iHotspots; i++ )
			ar << ( (CPoint*)arHotspots[ i ] )->x << ( (CPoint*)arHotspots[ i ] )->y;
#endif
	}
	else
	{
		ar >> iVersion;
		if (iVersion >= 2)
			ar >> csName;
		else
			csName.LoadString(IDS_UNTITLED);
		ar >> lAction >> iDirection >> iSpeed >> iFrames >> iHotspots;
		if( !bSerializeRLE )
			arOrigins.SetSize( iFrames );
		else
			arRLEOffsets.SetSize( iFrames );
		arSizes.SetSize( iFrames );
		arOffsets.SetSize( iFrames );
		arHotspots.SetSize( iFrames * iHotspots );
		CPoint* pptAdd;
		int iCount = 0;
		if( !bSerializeRLE )
		{
			for( i = 0; i < iFrames; i++ )
			{
				pptAdd = new CPoint;
				ar >> pptAdd->x >> pptAdd->y;
				arOrigins.SetAt( iCount++, pptAdd );
			}
			iCount = 0;
		}
		else
			arRLEOffsets.Serialize( ar );

		for( i = 0; i < iFrames; i++ )
		{
			pptAdd = new CPoint;
			ar >> pptAdd->x >> pptAdd->y;
			arSizes.SetAt( iCount++, pptAdd );
		}
		iCount = 0;
		for( i = 0; i < iFrames; i++ )
		{
			pptAdd = new CPoint;
			ar >> pptAdd->x >> pptAdd->y;
			arOffsets.SetAt( iCount++, pptAdd );
		}
		iCount = 0;
		for( i = 0; i < iFrames * iHotspots; i++ )
		{
			pptAdd = new CPoint;
			ar >> pptAdd->x >> pptAdd->y;
			arHotspots.SetAt( iCount++, pptAdd );
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
#ifdef ANIMEDITORDOC_VERSION
CPoint CSpriteSequence::ptOriginOfCelInStrip( CAnimEditorDoc* pDoc, CCel* pCelFind )
{
	//	Returns location of where cel would be within a strip bitmap of utilized cels.
	//	( Broken out just to keep the constructor clean. )

	POSITION posInList = pDoc->lstCels.GetHeadPosition();
	CCel* pCel;
	int iX = 0;
	while( posInList )
	{
		pCel = pDoc->lstCels.GetNext( posInList );
		if( pCel == pCelFind )
			return CPoint( iX, 0 );
		if( !pCel->lstSeqs.IsEmpty() )
			iX += pCel->GetWidth();
	}
	ASSERT( FALSE );
	return CPoint( 0, 0 );
}
#endif

//-----------------------------------------------------------------------------------------------------------------
void CSpriteSequence::Set_arRLEOrigins( BYTE* pCatalogOrigin )
{
	//	Sets up arRLEOrigins, memory locations of RLE data for sprites in sequence.
	//	Called after serialization in.
	arRLEOrigins.SetSize( iFrames );
	for( int i = 0; i < iFrames; i++ )
		arRLEOrigins[i] = pCatalogOrigin + arRLEOffsets[i];
}