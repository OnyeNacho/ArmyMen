//	CSpriteSequence.cpp

#include "stdafx.h"

#include "CSpriteSequence.h"

/////////////////////////////////////////////////////////////////////////////
//	Constructor/Destructor
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CSpriteSequence, CObject, 1)

CSpriteSequence::CSpriteSequence()
{
	bSerializeRLE = FALSE;
}


CSpriteSequence::~CSpriteSequence()
{
	//	Delete created CPoints.
	int i;

	for( i = 0; i <= arSizes.GetUpperBound(); i++ )
		delete arSizes[ i ];
	for( i = 0; i <= arOffsets.GetUpperBound(); i++ )
		delete arOffsets[ i ];
	for( i = 0; i <= arHotspots.GetUpperBound(); i++ )
		delete arHotspots[ i ];
}


//-----------------------------------------------------------------------------------------------------------------
void CSpriteSequence::Serialize( CArchive& ar )
{
	int iVersion;
	int i;
	if( ar.IsLoading() )
	{
		ar >> iVersion;
		ASSERT( iVersion == 2 || iVersion == 3);

		ar >> csName >> lAction >> iDirection >> iSpeed >> iMoveSpeed >> iFrames >> iHotspots;

		if( iVersion == 3)
			ar >> iActionFrame;
		else
			iActionFrame = 0;

		arIndexes.SetSize( iFrames );
		arSizes.SetSize( iFrames );
		arOffsets.SetSize( iFrames );
		arHotspots.SetSize( iFrames * iHotspots );

		arIndexes.Serialize( ar );

		CPoint* pptAdd;
		int iCount = 0;
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
