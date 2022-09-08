//========================================================================
//	FILE:			$Workfile: TadPriv.cpp $
//
//	DESCRIPTION:	AI Target Acquisition Driver (TAD) routines.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Monday, October 22, 1996
//
//	REVISION:		$Header: /ArmyMen/src/TadPriv.cpp 94    4/07/98 6:15a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996,1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/TadPriv.cpp $
//  
//  94    4/07/98 6:15a Bwilcox
//  tad cleanup
//  
//  91    4/02/98 11:41p Aburgess
//  debug for HitMe bug
//  
//  90    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  89    4/02/98 2:23p Bwilcox
//  assets will not aim at invisible
//  
//  88    3/30/98 3:27p Aburgess
//  path for bad HitMe pointer
//  
//  87    3/27/98 2:05p Aburgess
//  hack to resolve HitMe bug
//  
//  86    3/23/98 12:27p Nrobinso
//  switch to loading the aai data every map load
//  
//  85    3/09/98 6:44p Bwilcox
//  fixed tad bug of beinghit
//  
//  84    3/09/98 3:24p Aburgess
//  debug
//  
//  83    3/03/98 2:29p Aburgess
//  modifications made to release a active target if out of visibility
//  
//  82    2/20/98 3:40p Nrobinso
//  remove unsued code
//  
//  81    2/03/98 9:57p Nrobinso
//  turn off tadvalidate
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"
#include "Army.h"
#include "miscfile.h"
#include "Ai.h"
#include "MainFrm.h"
#include "Tad.h"
#include "Map.h"
#include "Comm.h"
#include "newdoor.h"

#include "Tad.dat"
#include "unit.h"
#include "vehicle.h"

#include "aiaccess.h"
#include "item.h"

///========================================================================
//							LOCAL DATA STRUCTURES
///========================================================================
        UNIT*	 pAIUnit	   = NULL;		// for debugging
///========================================================================
//							LOCAL VARIABLES
///========================================================================

TADLINK*		TADquadMap;							// quadrant map data
int				TADnumberOfQuads;					// number of total quadrants in map
int				TADmaxSearch;						// maximum quadrant index for searching
int				TADquadWidth;						// width of map in quadrants
int				TADquadHeight;						// height of map in quadrants
int				TADquadSize;						// quad dimension if tiles (16x16, 8x8, etc.)
int				TADquadHalfSize;					// 1/2 the quad dimension for rounding

TAD*			TADlist[ ARMY_LAST_ARMY ];		// list of tads for this army

BOOL			TADactive;

static TAD*		TADPotentialTargets[ TAD_MAX_POTENTIAL+1 ];
static USHORT	TADTargetQuotients[ TAD_MAX_POTENTIAL+1 ];


///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
void		TadForceAcquisition( TAD* pTarget, TAD* pAttacker );
void		TadRemoveTargetReferences(TAD* pWho, TAD* pFromWhom);
BOOL		TadCreateMap( int tilesWide, int tilesTall );
void		TadDeleteMap( void );
void		TadDeleteTadlink( TADLINK* pQuad );
TAD*		TadSelectPotentialTarget( TAD* pAttacker, int* pQuadIndecies, int nNumQuads );
void		TadCalcSortQuotient( TAD* pAttacker );
int			TadWhichQuad( TAD* pObject );
int			TadGetQuad( SPOINT pPoint );
int			TadAttackQuotient( int eArmy, SPOINT pAttackPos, TAD* pTarget );
void		TadInsertTarget( TAD* pTarget, USHORT nQuotient, int* nNumPotentialTargets );
void		TadApplyTargetInfo( TAD* pNewTad );
BOOL		TadHaveThisAttacker( TAD* pTarget, TAD* pAttacker );
BOOL		TadHaveThisPotential( TAD* pTarget, int nNumPotentialTargets );
BOOL		TadHaveThisMapEntry( int nQuad, TAD* pObject );
int			TadGetDirection( TAD* pTadObject );
void		TadSearchPattern( int nQuad, int nDirection, int* pIndecies );
TADLINK*	TadSearchLink( TADLINK* pListPtr, int* pListCount, LONG nTadID );

///========================================================================

///========================================================================
//	Function:		TadInit()
//
//	Description:		Initialize the target acquisition driver.
///========================================================================

BOOL	TadInit( void )
{
	int			army;

	// clear the lists of tads
	TADactive        = FALSE;
	FOR_EACH_ARMY(army)
	{
		// the attackers
		TADlist[ army ] = NULL;
	}

	// clear the quad map
	TADquadMap       = NULL;
	TADnumberOfQuads = 0;
	TADquadSize      = TAD_QUAD_SIZE_DEFAULT;
	TADquadHalfSize  = (TAD_QUAD_SIZE_DEFAULT >> 1);

	// now createt the quadrant map, which is an arry of doubly-linked tadlinks.
	TadCreateMap( the_map.width, the_map.height );

	// Active TAD
	TADactive = TRUE;

	return( FALSE );
}


///========================================================================
//	Function:		TadExit()
//
//	Description:     shutdown the target acquisition driver.
///========================================================================

void	TadExit( void )
{
}

///========================================================================
//	Function:		TadFree()
//
//	Description:	shutdown the target acquisition driver.
///========================================================================

void	TadFree( void )
{
	TAD*		pAttackerTad;
	TAD*		pNextTad;
	int			army;

	if (!TADactive) return;

	// free up the tads of all armies
    FOR_EACH_ARMY(army)
	{
		// destroy any residual attackers
		pAttackerTad     = TADlist[ army ];
		while (pAttackerTad != NULL)
		{
  			pNextTad = pAttackerTad->tadList; // get the next pointer before we delete this tad

			TadDeleteTad( pAttackerTad );

			pAttackerTad = pNextTad; // the next on the list				
		}
			
		TADlist[ army ] = NULL; // should already end up this way anyway.
	}

	// now deallocate the quadrant map
	TadDeleteMap();

	// now deactivate TAD
	TADactive = FALSE;
}

///========================================================================
//	Function:		TadCreate()
//
//	Description:
//		create a TAD structure.
//
//	Input:			eArmy		army this object belongs to
//					eObjType	type of object being loaded into a TAD
//					pObject		the object being loaded
//					pPosition	position in world of new object
//					bFlags		object flags
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	TadCreate( int eArmy, int eObjType, ITEM* pObj, ULONG bFlags )
{
	TADLINK*	pWhereTad;
	TAD*		pNewTad;
	int			size;
	BOOL		error = TRUE;			// assume failure

	// make sure TAD is active
	if ( !TADactive )
	{
		TRACE( "ERROR: TAD not active. [%s : %d]\n", __FILE__,__LINE__);
		goto exit;
	}

	// allocate memory for a TAD
	size    = sizeof( TAD );
	pNewTad = (TAD*)malloc( size );
	if ( pNewTad == NULL )
	{
		// error: we need this memory!
		TRACE( "ERROR: TAD memory allocation failure. [%s : %d]\n", __FILE__, __LINE__ );
		goto exit;
	}

#ifdef MALLOC_DEBUG
	TRACE( "malloc (%ld): TAD (army %d)[%s : %d]\n", size, eArmy, __FILE__, __LINE__ );
#endif

	// clear the data allocated
	ZeroMemory( pNewTad, size );

	// now insert the object and its data
	pNewTad->eObjType = (ITEM_TYPE)eObjType;
	pNewTad->bFlags   = bFlags;
    pNewTad->pItem    = pObj;
    pObj->pTad        = (void*)&(*pNewTad);

	switch( eObjType )
	{
	case ARMY_NULL_OBJ:
		// error: null object type
		TRACE( "ERROR: attempting to create a TAD for a NULL object type (%d). [%s : %d ]\n",
			eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	case ARMY_UNIT:
	case ARMY_VEHICLE:
	case ARMY_SARGE:
	case ARMY_ASSET:
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
		break;
	default:
		// error: unknown object type
		TRACE( "ERROR: attempting to create a TAD for an unknown object type (%d). [%s : %d ]\n",
			eObjType, __FILE__, __LINE__ );
		ASSERT(0);
	}


	// apply the default targeting information
	TadApplyTargetInfo( pNewTad );

	// Acquire the position of this object and place it into the
	// appropriate quadrant
	if ( TadCreateQuad( pNewTad, pObj->position) )
	{
		// error: we need this memory!
		TRACE( "ERROR: TAD create Quad failure. [%s : %d]\n", __FILE__, __LINE__ );

		// delete the previously allocated TAD
		TadDeleteTad( pNewTad );

		goto exit;
	}

    // prove we can find ourselves in the world
    pWhereTad = TadFindQuadLink(pNewTad);
    ASSERT(pWhereTad);

	// enter this tad onto armies tad list at front
	pNewTad->tadList = TADlist[ eArmy ];
	TADlist[ eArmy ] = pNewTad;
	// if we made it here we were successful
	error = FALSE;
  
exit:
 
	return( error );
}

///========================================================================
//	Function:		TadCreateMap()
//
//	Description:
//		based on the map size, build the quadrant map.
//
//	Input:			tilesWide	width of map in tiles
//					tilesTall	height of map in tiles
//
//	Ouput:			FALSE		if successful, TRUE for error
//
///========================================================================

BOOL	TadCreateMap(int tilesWide, int tilesTall )
{
	int		size;
	BOOL	error = TRUE;			// assume failure

	// make sure TAD is not active
	if ( TADactive )
	{
		// go free up the existing map
		TadFree();

		// deactive TAD
		TADactive = FALSE;
	}

	// now determine the number of quads wide and tall, round up
	TADquadWidth  = (tilesWide + TADquadHalfSize) / TADquadSize;
	TADquadHeight = (tilesTall + TADquadHalfSize) / TADquadSize;
	TADmaxSearch  = TADquadWidth * TADquadHeight;

	// now allocate the memory for the quad map
	TADnumberOfQuads = (TADquadWidth * TADquadHeight);
	size             = TADnumberOfQuads * (sizeof(TADLINK)) ;
	TADquadMap       = (TADLINK*)malloc( size );
	if ( TADquadMap == NULL )
	{
		// error: we need this memory!
		TRACE( "ERROR: QUAD memory allocation failure. [%s : %d]\n", __FILE__, __LINE__ );
		goto exit;
	}

	// clear the data allocated
	memset( TADquadMap, 0, size );

	// if we made it here we were successful
	error = FALSE;

exit:
	return( error );

}

///========================================================================
//	Function:		TadDeleteMap()
//
//	Description:		de-allocate the quadrant map.
///========================================================================

void	TadDeleteMap( void )
{
	TADLINK*	quadPtr;
	TADLINK*	quadNextPtr;
	TADLINK*	quadCurrentPtr;
	int			quad;

	// make sure TAD is active
	if ( !TADactive )
	{
		TRACE( "ERROR: TAD not active. [%s : %d]\n", __FILE__,__LINE__);
		return;
	}

	// make sure we actually have a quad map
	if ( TADquadMap )
	{
		// now remove all the QUADLINKs
		for( quad=0; quad<TADnumberOfQuads; ++quad )
		{
			// search this quadrant for elemets, the first element in the
			// list is a header, so check the next quad pointer for the first
			// real element.
			quadPtr        = TADquadMap + quad;
			quadCurrentPtr = quadPtr->pNext;
			while( quadCurrentPtr != NULL )
			{
				// get the next element
				quadNextPtr = quadCurrentPtr->pNext;

				// destroy the quad element (ignore the tad itself)
				TadDeleteTadlink( quadCurrentPtr );

				// now point to the next quadlink
				quadCurrentPtr = quadNextPtr;
			}
		}

		// free the allocated quad memory
		free( TADquadMap );
		TADquadMap = NULL;
	}
}

///========================================================================
//	Function:		TadCreateQuad()
//
//	Description:
//		create a quad element and insert it into the quadrant map.
//
//	Input:			pObject		TAD object whose quad entry we want to create
//					pNewPos		position of TAD for quadrant calculation
//
//	Ouput:			none
//
///========================================================================

BOOL	TadCreateQuad( TAD* pObject, SPOINT pNewPos )
{
	TADLINK*	pQuad;
	TADLINK*	pQuadHead;
	int			newQuad;
	BOOL		error = TRUE;		// assume failure

	// make sure TAD is active
	if ( !TADactive )
	{
		TRACE( "ERROR: TAD not active. [%s : %d]\n", __FILE__,__LINE__);
		goto exit;
	}

	// make sure we have a valid TAD object
	if ( pObject == NULL )
	{
		// error: we need this memory!
		TRACE( "ERROR: TAD object is NULL. [%s : %d]\n", __FILE__, __LINE__ );
		goto exit;
	}

	// now find the appropriate quad
	newQuad  = TadGetQuad( pNewPos );
	if ( newQuad == -1 )
		goto exit;

	// allocate a new TADLINK for this object
	pQuad = (TADLINK*)malloc( sizeof( TADLINK) );
	if ( pQuad == NULL )
	{
		// error: quad does not contain this object
		TRACE( "ERROR: QUAD malloc failure. [%s : %d ]\n", __FILE__, __LINE__ );
		goto exit;
	}

	// insert the TAD into the TADLINK
	pQuad->pTadObject = pObject;
	pQuad->pNext      = NULL;
	pQuad->pPrev      = NULL;

	// check to see if this object is already in the map
	if ( TadHaveThisMapEntry( newQuad, pObject ) ) ASSERT(0);

	// now insert the TADLINK into the appropriate quadrant, go ahead and put
	// it at the head of the list
	pQuadHead  = TADquadMap + newQuad;
	if ( pQuadHead->pNext )
	{
		pQuad->pNext            = pQuadHead->pNext;
		pQuadHead->pNext->pPrev = pQuad;
	}
	pQuadHead->pNext        = pQuad;
	pQuad->pPrev            = pQuadHead;
	
	// we're done
	error = FALSE;
exit:
	return( error );
}

///========================================================================
//	Function:		TadUpdateQuad()
//
//	Description:	update a quad element in the quadrant map.
///========================================================================

void	TadUpdateQuad( int objType, ITEM* object, SPOINT oldPos, SPOINT newPos )
{
	TADLINK*	oldQuadPtr;
	TADLINK*	newQuadPtr;
	TAD*		tadPtr;
	int			oldQuad;
	int			newQuad;
	BOOL		found = FALSE;

	// make sure TAD is active
	if ( !TADactive )
	{
		TRACE( "ERROR: TAD not active. [%s : %d]\n", __FILE__,__LINE__);
		return;
	}

	// if the old position is off the map then this object is being placed in to the
	// the quadrant map for the first time
	if ( oldPos.x == 0 )
		goto newObject;

	// first determine what the old quadrant is so we can remove it
	oldQuad = TadGetQuad( oldPos );
	if ( oldQuad == -1 )
		goto exit;

	// now get the new quadrant
	newQuad = TadGetQuad( newPos );
	if ( newQuad == -1 )
		goto exit;

	// if the old and new quadrants are the same, we're done
	if ( oldQuad == newQuad )
		goto exit;

	// now unlink the old quad pointer
	// search the quadrant list for this object
	oldQuadPtr = TADquadMap + oldQuad;
	if ( oldQuadPtr == NULL )
	{
		// error: quad does not contain this object
		TRACE( "ERROR: object not in quadrant #%d. [%s : %d ]\n", oldQuad, __FILE__, __LINE__ );
		goto exit;
	}

	// search for this object, remember to advance past the TADLINK header
	oldQuadPtr = oldQuadPtr->pNext;
	while( (oldQuadPtr != NULL) && !found )
	{
		if (oldQuadPtr->pTadObject->pItem == object) // we found what we were looking for
			found = TRUE;						// this is the one
		else
			oldQuadPtr = oldQuadPtr->pNext;		// try the next one
	}

	// did we actually find the object to update?
	if ( !found )
	{
		// error: quad does not contain this object
		TRACE( "ERROR: object not in quadrant #%d. [%s : %d ]\n", oldQuad, __FILE__, __LINE__ );
		goto exit;
	}
	else tadPtr = oldQuadPtr->pTadObject;

	// signify that a quadrant change has occurred
	tadPtr->bChgQuad = TRUE;

	// ok, we have the object in the old quadrant, remove it from this quadrant and place in
	// the new quadrant
	if ( oldQuadPtr->pPrev )
		oldQuadPtr->pPrev->pNext = oldQuadPtr->pNext;
	if ( oldQuadPtr->pNext )
		oldQuadPtr->pNext->pPrev = oldQuadPtr->pPrev;

	// now put this object into the new quadrant, go ahead and put it at the head of the list
newObject:
	newQuadPtr        = TADquadMap + newQuad;

	if ( newQuadPtr->pNext )
		newQuadPtr->pNext->pPrev = oldQuadPtr;
	oldQuadPtr->pNext = newQuadPtr->pNext;
	oldQuadPtr->pPrev = newQuadPtr;
	newQuadPtr->pNext = oldQuadPtr;

	// we're done
exit:
	return;
}


///========================================================================
//	Function:		TadRemoveTargetReferences()
//
//	Description:	remove ref from targets list 
//					We only get on a targets list if he was our lasttarget
///========================================================================

void TadRemoveTargetReferences(TAD* pWho, TAD* pFromWhom)
{
	TARGETINFO*	pTargetTargetInfo;
	TAD*		pAttacker;
	int			nAttacker;
	int			n;
	if ( pFromWhom )
	{
		// acquire the target info (attacker list) for this target
		pTargetTargetInfo = &(pFromWhom->targetInfo);

		// look for this attacker in the target's attacker list
		n = pTargetTargetInfo->nNumAttackers;
		for (nAttacker = 0; nAttacker < n; ++nAttacker)
		{
			// compare the attacker to the target's list of attackers, locate the
			// attacker's reference and remove it from the list
			pAttacker = pTargetTargetInfo->pAttackers[ nAttacker ];
			if ( pWho  == pAttacker   )
			{
				// clear this attacker from the list and note that it was located
				pTargetTargetInfo->pAttackers[ nAttacker ] = NULL;
				pTargetTargetInfo->pAttackers[ nAttacker ] = pTargetTargetInfo->pAttackers[ n-1 ];
				--n;
				--nAttacker;
				--(pTargetTargetInfo->nNumAttackers);
			}
		}
	}

	// now find references and remove them.
	if (pWho->pLastTarget == pFromWhom) pWho->pLastTarget = NULL;	
}

///========================================================================
//	Function:		TadBestTargets()
//	Description:	Find all the best 3 targets for the given attacker.
///========================================================================

TAD*	TadBestTarget( TAD* pAttackerTad )
{
	int			nAttackerQuad;
	int			nDirection;
	int			pQuadIndecies[ TAD_MAX_QUADS ];

	// validate the parameters
	ASSERT( pAttackerTad );

	// start by finding the attacker's quadrant
	nAttackerQuad = TadWhichQuad( pAttackerTad );

	// now search for potential targets in the search pattern specified by
	// the quadrant the attacker is in and the direction it is traveling.
	nDirection   = TadGetDirection( pAttackerTad );
	ASSERT( nDirection >= 0 );
	if ( nDirection >= 0 )
	{
		// set the indecies array to all -1
		memset( pQuadIndecies, 0xFF, (sizeof(int)*TAD_MAX_QUADS) );

		// get the search pattern to parse
		TadSearchPattern( nAttackerQuad, nDirection, pQuadIndecies );

		// now parse through all these quadrants choosing the potential targets
		return TadSelectPotentialTarget( pAttackerTad, pQuadIndecies, TAD_MAX_QUADS );
	}
	return NULL;
}

///========================================================================
//	Function:		TadSelectPotentialTarget()
//
//	Description:
//		choose all potential targets for this attacker.
//
//	Input:			pAttacker		attacker whose potential targets we want to find.
//					pQuadIndecies	list of quadrants that attacker searches.
//					nNumQuads		number of quadrants in list.
//
//	Ouput:			none
//
///========================================================================

TAD*	TadSelectPotentialTarget( TAD* pAttackerTad, int* pQuadIndecies, int nNumQuads )
{
	TAD*			pTargetTad   = NULL;
	TADLINK*		pTargetLink	 = NULL;
	TADLINK*		pQuadrant    = NULL;	// Quadrant information
	SPOINT			pAttackerPos;	// Attacker position
	int				eArmy;					// army this attacker belongs to
	int				eOppossingArmy;			// army target belongs to
	USHORT			nQuotient;				// attack quotient for target
	int				quad;
	int				quadIndex;
	int				nNumPotentialTargets;
	int				nTarget;
	BOOL			bFull;
	TAD*			pPotentialTad = NULL;

	// validate the parameters
	ASSERT( pAttackerTad );
	ASSERT( pQuadIndecies );

	// get this attacker's army and position
    eArmy        = ITEM_ARMY(pAttackerTad->pItem);
    pAttackerPos = pAttackerTad->pItem->position;

	// now for each quadrant in the list, find all the potential targets and
	// see if they have a higher quotient than any already in the attackers
	// list of potential targets.
	ZeroMemory( TADPotentialTargets, ((TAD_MAX_POTENTIAL+1) * sizeof(TADLINK*)) );
	ZeroMemory( TADTargetQuotients, ((TAD_MAX_POTENTIAL+1) * sizeof(USHORT)) );
	quad                 = 0;
	bFull                = FALSE;
	nNumPotentialTargets = 0;
	while( !bFull && (quad<nNumQuads) )
	{
		// get the quad
		quadIndex = pQuadIndecies[ quad ];

		if ( quadIndex >= 0 )
		{
			pQuadrant = TADquadMap+quadIndex;

			// note that the very first QUADLINK in this quadrant is the header
			// it either points to a list of objects in the quadrant or is null
			pTargetLink = pQuadrant->pNext;
			while ( pTargetLink )
			{
   				pTargetTad = pTargetLink->pTadObject;

				// make sure target is not friendly
				eOppossingArmy = ITEM_ARMY( (ITEM*)(pTargetTad->pItem) );
				if ( (eOppossingArmy != ARMY_INDEPENDENT) && (eOppossingArmy != eArmy) &&
					(ArmyHaveAllianceWith( (ARMY_TYPE)eArmy, (ARMY_TYPE)eOppossingArmy ) == FALSE))
				{
					if (pTargetTad->pItem->nStrength == 0);
					// for the prison camp.. make assets not target invisible soldiers.
					// even though regular troopers see invisible soldiers.
					else if (pAttackerTad->eObjType == ARMY_ASSET && pTargetTad->eObjType == ARMY_TROOPER &&
						((TROOPER*)pTargetTad->pItem)->pAvatar->pAnimation->flags & ANIM_FLAG_INVISIBLE);
					// otherwise prove the item is known to the army via visiblity
					else if (ItemVisible(eArmy,pTargetTad->pItem))
					{
						// get the attack quotient for this target
						nQuotient = TadAttackQuotient( eArmy, pAttackerPos, pTargetTad );

						// now compare this quotient to those that the attacker has
						TadInsertTarget( pTargetTad, nQuotient, &nNumPotentialTargets );
					}
				}

				// get the next Target in this quadrant
				pTargetLink = pTargetLink->pNext;
			}

			// we want to search at least the first TAD_MIN_QUADS_2_SEARCH quadrants
			// before checking to see if the attacker is full
			if ( quad >= TAD_MIN_QUADS_2_SEARCH )
			{
				if ( nNumPotentialTargets >= TAD_MAX_POTENTIAL )
					bFull = TRUE;
			}
		}

		// try the next quadrant
		if ( !bFull )
			++quad;
	}

	// now if we have a possible list of potential attackers
	if ( nNumPotentialTargets )
	{
		// now find an available target
		nTarget    = 0;
		while (nTarget<nNumPotentialTargets)
		{
			TAD* pTargetTad;
			TARGETINFO*	pTargetInfo;
			pTargetTad = TADPotentialTargets[ nTarget ];
	
			// if he is already our target, we are on his attackers list
			if (TadHaveThisAttacker( pTargetTad, pAttackerTad ) )
				return pTargetTad;

			// make sure this target isn't already full of attackers
			pTargetInfo = &(pTargetTad->targetInfo);
			if ( pTargetInfo->nNumAttackers < TAD_MAX_ATTACKERS )
				return pTargetTad;

			++nTarget;
		}
	}

	return NULL;
}

///========================================================================
//	Function:		TadCalcSortQuotient()
//
//	Description:
//		calculate the sort quotient for this attacker based on the potential
//		targets in its list.
///========================================================================

void	TadCalcSortQuotient( TAD* pAttacker )
{
	USHORT			nPrimaryValue;
	USHORT			nSecondaryValue;
	USHORT			nSortQuotient;
	USHORT			nBirthBonus;


	// get the target quotients for the primary and secondary targets
	nBirthBonus     = pAttacker->nBirthBonus;
	nPrimaryValue   = TADTargetQuotients[ 0 ];
	nSecondaryValue = TADTargetQuotients[ 1 ];

	// now calculate the sort quotient
	nSortQuotient    = (nPrimaryValue - nSecondaryValue + nBirthBonus);

	// insert the new sort quotient
	pAttacker->nSort = nSortQuotient;
	
}

///========================================================================
//	Function:		TadSelectTarget()
//	Description		Select a target for an attacker.
///========================================================================
BOOL ValidTarget(int eArmy,TAD* pTargetTad)
{
	if ( pTargetTad->pItem->nStrength == 0) return FALSE;
	if (!ItemVisible(eArmy,pTargetTad->pItem)) return FALSE;
	if (ArmyHaveAllianceWith( (ARMY_TYPE)eArmy, (ARMY_TYPE)ITEM_ARMY(pTargetTad->pItem) ) == TRUE) return FALSE;
	return TRUE;
}

void	TadSelectTarget( TAD* pAttackerTad )
{
	TAD*			pTargetTad	= NULL;
    int				eArmy = ITEM_ARMY(pAttackerTad->pItem);

	// validate the parameter
	ASSERT( pAttackerTad );

	//  see if there is a HIT_ME target:- it has priority
	if (pTargetTad == NULL)
	{
		pTargetTad = pAttackerTad->pHitMeTarget;
		if ( pTargetTad && ValidTarget(eArmy,pTargetTad) == 0)
		{
			pAttackerTad->pHitMeTarget = pTargetTad = NULL;
		}
	}

	// if that failed then look for a potential target (opportunistic).
	if ( pTargetTad == NULL )
	{
		// find the best potential targets for the attacker
		pTargetTad = TadBestTarget( pAttackerTad ); // get the best potential target
		if ( pTargetTad && ValidTarget(eArmy,pTargetTad) == 0)
		{
			pTargetTad = NULL;
		}
	}

	// now assign the LAST target pointer (who we go after)
	if ( pTargetTad != pAttackerTad->pLastTarget)
	{
		TadForceAcquisition( pTargetTad, pAttackerTad );
	}
}

///========================================================================
//	Function:		TadForceAcquisition()
//
//	Description:
//		acquire this target for acquisition. The request is always granted.
//
//	Input:			pTarget		target the attacker is requesting
//					pAttacker	attacker making request
//
//	Ouput:			TRUE		if acquired, FALSE otherwise
//
///========================================================================

void	TadForceAcquisition( TAD* pTargetTad, TAD* pAttackerTad )
{
	TARGETINFO*	pTargetInfo;
	// IF WE had some other last target, release it
	if ( pAttackerTad->pLastTarget && pTargetTad != pAttackerTad->pLastTarget )
	{
		TadRemoveTargetReferences( pAttackerTad,pAttackerTad->pLastTarget );
	}

	// assign the last target
	pAttackerTad->pLastTarget = pTargetTad;

	if (!pTargetTad) return;

	// make sure this target isn't already full of attackers
	pTargetInfo = &(pTargetTad->targetInfo);
	if ( pTargetInfo->nNumAttackers >= TAD_MAX_ATTACKERS )
		return;

	// make sure this attacker is not already in the targets list
	// from a prior acquisition
	if (! TadHaveThisAttacker( pTargetTad, pAttackerTad ) )
	{
		// put this attacker into the request list
		pTargetInfo->pAttackers[ pTargetInfo->nNumAttackers ] = pAttackerTad;
		++( pTargetInfo->nNumAttackers );
	}
}

///========================================================================
//	Function:		TadDeleteTad()
//
//	Description:
//		delete a TAD entry and its associated TADLINKs, removing it from the
//		TAD table.
//
//	Input:			pTadObject		TAD object we need to delete.
//
//	Ouput:			none
//
///========================================================================

void	TadDeleteTad( TAD* pTadObject )
{
	TAD*		pTad;
	int			eArmy;
	TADLINK*	pTadLink;

	if ( !pTadObject ) 
		return;
	pTadObject->pItem->pTad = NULL; // remove ref to this tad

	// find the Army this object
	eArmy = ITEM_ARMY( pTadObject->pItem) ;
	if ( eArmy != ARMY_INDEPENDENT )
	{
		// remove this from the army list
		pTad = (TAD*) &TADlist[eArmy];  // initial node looks like a tad
		// find the predecessor of our tad.
		while (pTad && pTad->tadList != pTadObject) pTad = pTad->tadList;
		ASSERT(pTad); // we must have found it.
		if (!pTad) return; // failed somehow

		// remove this TAD from any Targets Acquisition processing
		pTad->tadList = pTadObject->tadList; // link around our guy
		pTadObject->tadList = NULL;
	}

	// remove the Quad tad link for this object
	pTadLink = TadFindQuadLink( pTadObject );
	if ( pTadLink )
	{
		// delete the TADLINK object
		TadDeleteTadlink( pTadLink );
	}


	// MAKE SURE NO ONE USES THIS 
	int foeArmy;
	int n,i;
	FOR_EACH_ARMY(foeArmy)
	{
		if (eArmy == foeArmy) continue; // our own forces wont point to us to fight
		
		// walk all tads of this army and remove all refs to us
		pTad = TADlist[foeArmy];  
		// find the predecessor of our tad.
		while (pTad) 
		{
			if (pTad->pLastTarget == pTadObject) pTad->pLastTarget = NULL;		// the last target we were focusing on
			if (pTad->pHitMeTarget == pTadObject) pTad->pHitMeTarget = NULL;	// non NULL if the attacker was shot at		
			
			n = pTad->targetInfo.nNumAttackers;
			for (i = 0; i < n; ++i)
				if (pTad->targetInfo.pAttackers[ i] == pTadObject) // remove this entry
				{
					pTad->targetInfo.pAttackers[ i] = NULL;
					pTad->targetInfo.pAttackers[ i] = pTad->targetInfo.pAttackers[ n-1 ]; // swap in last, if any
					pTad->targetInfo.nNumAttackers = --n;
					--i; // try again
				}
			pTad = pTad->tadList;
		}
	}

	// now discard this tad memory
	free(pTadObject);
}

///========================================================================
//	Function:		TadRestore()
//
//	Description:
//		restore a group of objects visibility to the Target Acquisition Driver.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	TadRestore( )
{
	TAD*		pTadObject;
	int			eArmy;

	// clear up the army
	FOR_EACH_ARMY(eArmy)
	{
		// clear various flags for each attacker object
		pTadObject = TADlist[ eArmy ];
		while (pTadObject != NULL)
		{
			// decrement his birth bonus if applicable
			if ( pTadObject->nBirthBonus )
				--( pTadObject->nBirthBonus );

			// go to the next object
			pTadObject = pTadObject->tadList;
		}
	}
}


///========================================================================
//	Function:		TadUnlink()
//
//	Description:
//		unlink a quad from the TAD map
//
//	Input:			pObjLink		TAD object whose quad entry we unlink

//
//	Ouput:			none
//
///========================================================================

void	TadDeleteTadlink( TADLINK* pObjLink )
{
	TADLINK*	pPrev;
	TADLINK*	pNext;
	if (!pObjLink) return;

	// save off this objects next and previous pointers
	pPrev = pObjLink->pPrev;
	pNext = pObjLink->pNext;

	// now link the previous and next together
	if ( pNext )
	{
		pNext->pPrev = NULL;
		if ( pPrev )
			pNext->pPrev = pPrev;
	}

	if ( pPrev )
	{
		pPrev->pNext = NULL;
		if ( pNext )
			pPrev->pNext = pNext;
	}

	free( pObjLink );
}



///========================================================================
//	Function:		TadSearchLink()
//
//	Description:
//		find a TADs TADLINK
//
//	Input:			pListPtr		List of TADLINKs to search
//					pListCount		Number of TADLINKs in list
//					nTadID			UID of TAD we're looking for
//
//	Ouput:			pObject			TADLINK for this TAD object
//
///========================================================================

TADLINK*	TadSearchLink( TADLINK* pListPtr, int* pListCount, LONG nTadID )
{
	TADLINK*	pObject = NULL;
	ULONG		nListID;
	int			count = 0;
	BOOL		bFound = FALSE;			// assume failure

	if ( (pListPtr != NULL) && nTadID )
	{
		while( pListPtr && (count < *pListCount) && !bFound )
		{
			// compare the mapQ objects
			nListID = ITEM_UID( pListPtr->pTadObject->pItem );
			if ( nTadID == nListID )
			{
				pObject = pListPtr;
				bFound  = TRUE;					// this is the one
			}
			else
				pListPtr = (TADLINK*)(pListPtr->pNext);		// try the next one
		}
	}

	return( pObject );
}

///========================================================================
//	Function:		TadFindQuadLink()
//
//	Description:
//		find a TADs QUAD TADLINK
//
//	Input:			pTadObject		TAD object whose Quad tadlink we need to find.
//
//	Ouput:			pQuadLink		Quad TADLINK for this TAD object
//
///========================================================================

TADLINK*	TadFindQuadLink( TAD* pTadObject )
{
	TADLINK*	pQuadLink = NULL;
	TADLINK*	pQuadrant;
	TADLINK*	pObjectLink;
	SPOINT		pObjPos;
	LONG		nObjectID;
	LONG		nTadID;
	int			nQuad;
	BOOL		bFound;
	

	if ( !pTadObject )
		return( pQuadLink );
	nTadID = ITEM_UID( pTadObject->pItem );
	ASSERT(nTadID);

	// which quadrant does this object lie in
	pObjPos   = TadPosition( pTadObject );
	nQuad     = TadGetQuad( pObjPos );
	pQuadrant = TADquadMap+nQuad;

	// note that the very first QUADLINK in this quadrant is the header
	// it either points to a list of objects in the quadrant or is null
	pObjectLink = pQuadrant->pNext;
	bFound      = FALSE;
	while ( pObjectLink && !bFound )
	{
		// is this the object we're looking for?
		nObjectID = ITEM_UID( pObjectLink->pTadObject->pItem );
		if ( nTadID && nObjectID && (nTadID == nObjectID) )
			bFound = TRUE;
		else
			pObjectLink = pObjectLink->pNext;	// get the next tadlink in this quadrant
	}

	if ( !bFound )
		pObjectLink = NULL;

	return( pObjectLink );
}

///========================================================================
//	Function:		TadWhichQuad()
//
//	Description:
//		determine the quadrant this object is in.
//
//	Input:			pObject		object whose quadrant we want to find.
//
//	Ouput:			quadrant	quadrant index, -1 if error
//
///========================================================================

int		TadWhichQuad( TAD* pTadObject )
{
	SPOINT	pObjPos;
	int		quadrant = -1;

	// determine which object this is
	if ( !pTadObject )
		goto exit;
    pObjPos = pTadObject->pItem->position;

	switch( pTadObject->eObjType )
	{
	case ARMY_NULL_OBJ:
		// error: null object type
		TRACE( "ERROR: attempting to find a quad for a NULL object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	case ARMY_ASSET:
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
	case ARMY_UNIT:
	case ARMY_VEHICLE:
	case ARMY_SARGE:
	case ARMY_FLOAT:
	case ARMY_TROOPER:
		break;
	default:
		// error: unknown object
		TRACE( "ERROR: attempting to locate quad for an unknown object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		goto exit;
	}

	// now get the position of this object
	quadrant = TadGetQuad( pObjPos );

exit:
	return( quadrant );
}

///========================================================================
//	Function:		TadGetQuad()
//
//	Description:
//		determine the quadrant this point is in.
//
//	Input:			pPoint		point whose quadrant we want to find.
//
//	Ouput:			quad		the quadrant index, -1 otherwise
//
///========================================================================

int		TadGetQuad( SPOINT pPoint )
{
	int		quad = -1;
	int		nQuadCol;
	int		nQuadRow;

	// first make sure that the point is in the map
	if ( !InBox(&the_map.FullPixelBox, &pPoint) )
	{
		// error: position not in legal quadrant
		TRACE( "ERROR: point in illegal quadrant. [%s , %d]\n",
			__FILE__, __LINE__ );
		goto exit;
	}


	// determine which quadrant this point is in.
	nQuadRow = ((pPoint.y) >> 8);		// >>4 for pixel to tile, >>4 for tile to quad
	if (nQuadRow > TADquadHeight )
	{
		// error: position not in legal quadrant
		TRACE( "ERROR: position not in legal quadrant. [%s , %d]\n",
			__FILE__, __LINE__ );
		goto exit;
	}
	nQuadCol = ((pPoint.x) >> 8);		// >>4 for pixel to tile, >>4 for tile to quad
	if (nQuadCol > TADquadWidth )
	{
		// error: position not in legal quadrant
		TRACE( "ERROR: position not in legal quadrant. [%s , %d]\n",
			__FILE__, __LINE__ );
		goto exit;
	}

	// get the actual quadrant
	quad = ((nQuadRow * TADquadWidth) + nQuadCol);

	// if we got this far, we found the quadrant
exit:
	return( quad );
}


///========================================================================
//	Function:		TadWhichArmy()
//
//	Description:
//		determine the army this object belongs to.
//
//	Input:			pObject		object whose army we want to find.
//
//	Ouput:			eArmy		Army that this object belongs to, -1 if error
//
///========================================================================

int		TadWhichArmy( TAD* pTadObject )
{
	int		eArmy = ARMY_INDEPENDENT;

	if ( pTadObject )
		eArmy = ITEM_ARMY(pTadObject->pItem );
	return( eArmy );
}

///========================================================================
//	Function:		TadArmy()
//
//	Description:
//		determine the army this object belongs to.
//
//	Input:			pObject		object whose army we want to find.
//
//	Ouput:			eArmy		Army that this object belongs to, -1 if error
//
///========================================================================

int		TadArmy( TAD* pObject )
{
	int		eArmy =  ITEM_ARMY(pObject->pItem);

	// determine which object this is
	switch( pObject->eObjType )
	{
	case ARMY_NULL_OBJ:
		// error: null object type
		TRACE( "ERROR: attempting to find ARMY of a NULL object type (%d). [%s : %d ]\n",
			pObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	case ARMY_UNIT:
	case ARMY_VEHICLE:
	case ARMY_SARGE:
	case ARMY_ASSET:
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
		break;
	default:
		// warning: unknown object found in quadrant
		TRACE( "WARNING: attempting to find ARMY of an unknown object (%d). [%s : %d ]\n",
			pObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
	}
	
    ASSERT(eArmy < 4); // BW-

	return( eArmy );
}

///========================================================================
//	Function:		TadAttackQuotient()
//
//	Description:
//		determine the attack quotient for this target.
//
//	Input:			eArmy		army that attack belongs to.
//					pAttackPos	position of attacker.
//					pQuadrant	target whose potential we want
//
//	Ouput:			eArmy		Army that this object belongs to, -1 if error
//
///========================================================================

int		TadAttackQuotient( int eArmy, SPOINT pAttackPos, TAD* pTadObject )
{
	int		eAttackFormula = TARGETING_PASSIVE;
	long	nBaseValue;
	int		nQuotient = 0;
	int		eOpposingArmy;
	SPOINT	pTargetPos;
	SHORT	nTargetX;
	SHORT	nTargetY;
	ULONG	nDistance;

	// determine which object this is
	if ( !pTadObject )
		goto exit;
	pTargetPos    = pTadObject->pItem->position;
	eOpposingArmy = ITEM_ARMY(pTadObject->pItem);

	switch( pTadObject->eObjType )
	{
	case ARMY_NULL_OBJ:
		// error: null object type
		TRACE( "ERROR: attempting to find Attack Quotient for a NULL object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	case ARMY_UNIT:
//		nBaseValue    = UnitTroopStrength((UNIT*)pTadObject->pItem);
		nBaseValue    = pTadObject->pItem->nStrength;
		break;
	case ARMY_VEHICLE:
		nBaseValue    = ((ITEM*)(pTadObject->pItem))->nStrength;
		break;
	case ARMY_SARGE:
	case ARMY_ASSET:
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
		nBaseValue    = ((ITEM*)(pTadObject->pItem))->nStrength;
		break;
	default:
		// error: quad does not contain this object
		TRACE( "ERROR: attempting to find Attack Quotient for an unknown object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
	}
	nTargetX      = pTargetPos.x;
	nTargetY      = pTargetPos.y;

	// now get the players targeting formula
	eAttackFormula = Armies[ eArmy ].eTargetingId;

	// for now, square the base value
	nBaseValue = ( nBaseValue * nBaseValue );

	// calculate the distance between the attacker and the target
	nDistance = GetDistance( &pAttackPos, &pTargetPos );
	if ( nDistance == 0 )
		nDistance = 1;

	// select the quotient formula based on this objects general
	switch( eAttackFormula )
	{
	case TARGETING_NULL:
		nQuotient = 1;
		break;
	case TARGETING_PASSIVE:			// balanced		priority/distance
		nQuotient = ( nBaseValue << 8 )/ nDistance;
		break;
	case TARGETING_AGGRESSIVE:		// priority		(priority*priority)/distance
		nQuotient = (( nBaseValue * nBaseValue ) << 8 )/ nDistance;
		break;
	case TARGETING_DEFENSIVE:		// distance		priority/(distance*distance)
		nQuotient = ( nBaseValue << 8 )/ (nDistance * nDistance);
		break;
	}
exit:
	return( nQuotient );
}

///========================================================================
//	Function:		TadInsertTarget()
//
//	Description:
//		insert the target if it has a higher quotient than those already in the
//		attackers list.
//
//	Input:			pTarget					the target to be potentially inserted.
//					nQuotient				the target potential quotient for insertion
//					nNumPotentialTargets	actual number of potential targets found.
//
//	Ouput:			eArmy		Army that this object belongs to, -1 if error
//
///========================================================================

void	TadInsertTarget( TAD* pTargetTad, USHORT nQuotient, int* nNumPotentialTargets )
{
	TAD*		pListTad;
	USHORT*		pQuotientList;
	USHORT		nTargetQuotient = 0;
	USHORT		nListQuotient   = 0;
	int			index;
	int			nMaxIndex;
	int			shiftIdx;
	BOOL		inserted;

	if ( *nNumPotentialTargets >= TAD_MAX_POTENTIAL )
		return;

	// get the new target's quotient
	nTargetQuotient = nQuotient;
	nMaxIndex       = min( *nNumPotentialTargets, TAD_MAX_POTENTIAL );
	pQuotientList   = TADTargetQuotients;

	// now compare this against the other targets in the list
	inserted = FALSE;
	if ( nMaxIndex == 0 )
	{
		// nothing in the list, place in first location
		TADPotentialTargets[ 0 ] = pTargetTad;
		TADTargetQuotients[ 0 ]  = nTargetQuotient;
		*nNumPotentialTargets    = 1;
	}
	else
	{
		// something in the list, walk and compare
		index    = 0;
		inserted = TRUE;
		while ( !inserted && (index < TAD_MAX_POTENTIAL) )
		{
			// get the quotient for the attack list item
			pListTad = TADPotentialTargets[ index ];
			if ( pListTad )
			{
				// make sure this target isn't already in the list
				if ( !TadHaveThisPotential( pTargetTad, *nNumPotentialTargets ) )
				{
					// see if we need to insert it here
					nListQuotient = TADTargetQuotients[ index ];

					if ( nListQuotient < nTargetQuotient )
					{
						// move the others down the list, unless this is the last
						// item in the list
						if ( index < TAD_LAST_POTENTIAL )
						{
							// shift everyone down
							for( shiftIdx=(TAD_LAST_POTENTIAL-1); shiftIdx>=index; --shiftIdx )
							{
								// shift this one down one
								TADPotentialTargets[ shiftIdx+1 ] = TADPotentialTargets[ shiftIdx ];
								TADTargetQuotients[ shiftIdx+1 ]  = TADTargetQuotients[ shiftIdx ];
							}
						}

						// now insert this new target at the current index
						TADPotentialTargets[ index ] = pTargetTad;
						TADTargetQuotients[ index ]  = nTargetQuotient;

						// increment the number of targets
						++(*nNumPotentialTargets);

						// note that we actually inserted the new target
						inserted = TRUE;
					}
				}
			}

			// advance to the next potential target
			++index;
		}
	}
}

///========================================================================
//	Function:		TadApplyTargetInfo()
//
//	Description:
//		apply the default atrgeting information to this new TAD.
//
//	Input:			pNewTad		TAD requiring target info.
//
//	Ouput:			none
//
///========================================================================

void	TadApplyTargetInfo( TAD* pNewTad )
{
	int			eObjType;
	int			eType;
	AI_ACQUIRE*	pTargeting = NULL;

	// get the TAD object type
	eObjType = pNewTad->eObjType;
    eType      = ITEM_CLASS(pNewTad->pItem);

	// make sure the actual objects match
	switch( eObjType )
	{
	case ARMY_NULL_OBJ:
		// error: null object type
		TRACE( "ERROR: attempting to apply target info to a NULL object type (%d). [%s : %d ]\n",
			eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	case ARMY_UNIT:
		pTargeting = AiUnitTargetDefaults( eType );
		break;
	case ARMY_VEHICLE:
		pTargeting = AiVehicleTargetDefaults( eType );
		break;
	case ARMY_SARGE:
		pTargeting = AiVehicleTargetDefaults( ARMY_COMMANDER );
		break;
	case ARMY_ASSET:
		pTargeting = AiAssetTargetDefaults( eType );
		break;
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
		break;
	default:
		// error: quad does not contain this object
		TRACE( "ERROR: attempting to apply target info to an unknown object type (%d). [%s : %d ]\n",
			eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	}

	// make sure we found targeting data
	if ( pTargeting )
	{
		// copy in the min and max values
		pNewTad->targetInfo.nMinAttackLevel = pTargeting->nMinAttackLevel;
		pNewTad->targetInfo.nMaxAttackLevel = pTargeting->nMaxAttackLevel;
	}
    else // structures with no data...
    {
		pNewTad->targetInfo.nMinAttackLevel = 1;
		pNewTad->targetInfo.nMaxAttackLevel = 4;

    }
}

///========================================================================
//	Function:		TadHaveThisAttacker()
//
//	Description:
//		see if this attacker is already in the targets list.
//
//	Input:			pTarget			target being searched
//					pAttacker		attacker we're looking for in target list
//
//	Ouput:			TRUE			if attacker is already in the list
//									FALSE otherwise
//
///========================================================================

BOOL	TadHaveThisAttacker( TAD* pTargetTad, TAD* pAttacker )
{
	TAD**	pEnemies;
	TAD*		pTargetAttacker;
	TARGETINFO*	pTargetInfo;
	int			nNumAttackers;
	int			nAttacker = 0;
	BOOL		bFound    = FALSE;		// assume not in the list

	ASSERT( pTargetTad );
	ASSERT( pAttacker );

	// first make sure we're not looking at ourselves
	ASSERT ( pTargetTad != pAttacker );
	if ( pTargetTad == pAttacker )
		goto exit;

	// get the target information
	pTargetInfo   = &(pTargetTad->targetInfo);
	nNumAttackers = pTargetInfo->nNumAttackers;

	// look for this attacker in the target list
	nAttacker = 0;
	pEnemies  = (TAD**)pTargetInfo->pAttackers;
	while( !bFound  && (nAttacker<nNumAttackers) )
	{
		pTargetAttacker = pEnemies[ nAttacker ];
		if ( pTargetAttacker )
		{
			// compare the attacker to the target's list
			if ( pTargetAttacker == pAttacker )
			{
				bFound = TRUE;	// specify that this attacker is already in the list.
			}
		}

		// try the next target
		++nAttacker;
	}

exit:
	return( bFound );
}

///========================================================================
//	Function:		TadHaveThisPotential()
//
//	Description:
//		see if this target is already in the potential list.
//
//	Input:			pTarget					target we're trying insert
//					nNumPotentialTargets	number of current potential targets
//
//	Ouput:			TRUE			if target is already in the list
//									FALSE otherwise
//
///========================================================================

BOOL	TadHaveThisPotential( TAD* pTarget, int nNumPotentialTargets )
{
	TAD*	pTargetPotential;
	LONG		nPotentialID;
	LONG		nTargetID;
	int			nPotential;
	BOOL		bFound;

	// validate the parameters
	ASSERT( pTarget );

	// search the potential list for this target
	nTargetID = 0L;
	nTargetID    = ITEM_UID( pTarget->pItem );
	nPotential    = 0;
	bFound        = FALSE;
	if ( nNumPotentialTargets && nTargetID )
	{
		// look for this attacker in the target list
		while( !bFound && (nPotential<TAD_MAX_POTENTIAL)  )
		{
			if ( TADPotentialTargets[ nPotential ] )
			{
				// compare the target to the potential entry
				pTargetPotential = TADPotentialTargets[ nPotential ];
				if ( pTargetPotential )
				{
					nPotentialID = ITEM_UID( pTargetPotential->pItem );
					if ( nPotentialID == nTargetID )
						bFound = TRUE;	// specify that this target is already in the list.
				}
			}

			// try the next potential
			++nPotential;
		}
	}

	return( bFound );
}

///========================================================================
//	Function:		TadHaveThisMapEntry()
//
//	Description:
//		see if this target is already in the potential list.
//
//	Input:			nQuad			quadrant in map to search for this object
//					pObject			object whose map entry we're looking for
//
//	Ouput:			TRUE			if object is already in the map
//									FALSE otherwise
//
///========================================================================

BOOL	TadHaveThisMapEntry( int nQuad, TAD* pTadObject )
{
	TADLINK*	quadPtr;
	TADLINK*	quadCurrentPtr;
	TAD*		pQuadTad;
	LONG		nObjectID;
	LONG		nQuadID;
	BOOL		bFound = FALSE;		// assume failure

	// validate the parameters
	ASSERT( nQuad >= 0 );
	ASSERT( pTadObject );

	nObjectID = ITEM_UID( pTadObject->pItem );
	ASSERT( nObjectID );

	// search this quadrant for elemets, the first element in the
	// list is a header, so check the next quad pointer for the first
	// real element.
	quadPtr        = TADquadMap + nQuad;
	quadCurrentPtr = quadPtr->pNext;
	bFound         = FALSE;
	while( !bFound && (quadCurrentPtr != NULL) )
	{
		// get the TAD for this object and see if it matches
		pQuadTad = quadCurrentPtr->pTadObject;
		nQuadID  = 0L;
		if ( pQuadTad )
			nQuadID  = ITEM_UID( pQuadTad->pItem );
		if ( nQuadID && nObjectID && (nQuadID == nObjectID) )
			bFound = TRUE;
		else	// try the next element
			quadCurrentPtr = quadCurrentPtr->pNext;
	}

	return( bFound );
}

///========================================================================
//	Function:		TadMyPosition()
//
//	Description:
//		return a pointer to a TAD objects position.
//
//	Input:			pObject			object whose current position we want to find.
//
//	Ouput:			pMyPosition		objects current position
//
///========================================================================

SPOINT		TadMyPosition( TAD* pTadObject )
{
	SPOINT	pMyPosition = OFF_THE_MAP;
	if ( pTadObject )
		pMyPosition = TadPosition( pTadObject );

	return  pMyPosition ;
}

///========================================================================
//	Function:		TadPosition()
//
//	Description:
//		return a pointer to a TAD objects position.
//
//	Input:			pObject			object whose current position we want to find.
//
//	Ouput:			pMyPosition		objects current position
//
///========================================================================

SPOINT		TadPosition( TAD* pTadObject )
{
	SPOINT	pMyPosition;

	ASSERT( pTadObject );
    pMyPosition = (((ITEM*)(pTadObject->pItem))->position);

	// determine which object this is
	switch( pTadObject->eObjType )
	{
	case ARMY_NULL_OBJ:
		// error: null object type
		TRACE( "ERROR: attempting to a position of a NULL object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	case ARMY_UNIT:
	case ARMY_VEHICLE:
	case ARMY_SARGE:
	case ARMY_ASSET:
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
		break;
	default:
		// error: quad does not contain this object
		TRACE( "ERROR: attempting to a position of an unknown object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	}
	return( pMyPosition );
}

///========================================================================
//	Function:		TadGetDirection()
//
//	Description:
//		get the direction of an object's animation.
//
//	Input:			pTadObject	object whose direction we want
//
//	Ouput:			none
//
///========================================================================

int	TadGetDirection( TAD* pTadObject )
{
	int	nDirection = 0;

	ASSERT( pTadObject );

	// determine which object this is
	switch( pTadObject->eObjType )
	{
	case ARMY_NULL_OBJ:
		// error: null object type
		TRACE( "ERROR: attempting to obtain a direction for a NULL object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
//	case ARMY_STRUCTURE:
//	case ARMY_OBSTACLE:
		break;
	case ARMY_ASSET:
	case ARMY_FLOAT:
	case ARMY_TROOPER:
	case ARMY_UNIT:
	case ARMY_VEHICLE:
	case ARMY_SARGE:
		nDirection = ITEM_FACING( (ITEM*)(pTadObject->pItem) );
		break;
	default:
		// error: unknown object
		TRACE( "ERROR: attempting to obtain a direction for an unknown object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	}

	return( nDirection );
}


///========================================================================
//	Function:		TadMyTarget()
//
//	Description:
//		return the Target TADLINK for this TAD.
//
//	Input:			pTadObject		TAD object whose target target position is needed
//
//	Ouput:			pMyTarget		TAD Target object's TADLINK
//
///========================================================================

TAD*	TadMyTarget( TAD* pTadObject )
{
	TAD*		pMyTarget = NULL;
	if( pTadObject )
		pMyTarget = pTadObject->pLastTarget;
	return( pMyTarget );
}

///========================================================================
//	Function:		TadMyTargetObject()
//
//	Description:
//		return the Target object for this TAD.
//
//	Input:			pTadObject		TAD object whose target target position is needed
//
//	Ouput:			pTargetObject	Target TAD's object
//
///========================================================================

ITEM*	TadMyTargetObject( TAD* pTadObject )
{
	TAD*			pTadTarget  = NULL;
	ITEM*			pTargetObject = NULL;

	if( pTadObject )
	{
		// see if we already have a last target
		pTadTarget = pTadObject->pLastTarget;
		if ( pTadTarget )	// now point to the actual object this TADLINK points to
			pTargetObject = pTadTarget->pItem;
	}
	return( pTargetObject );
}

///========================================================================
//	Function:		TadMyTargetTad()
//
//	Description:
//		return the Target TAD for this Attacker TAD.
//
//	Input:			pTadObject		TAD object whose target target position is needed
//
//	Ouput:			pMyTarget		TAD of Target
//
///========================================================================

TAD*	TadMyTargetTad( TAD* pTadObject )
{
	TAD*		pTadTarget  = NULL;

	if( pTadObject )
	{
		// see if we already have a last target
		pTadTarget = pTadObject->pLastTarget;
	}
	return( pTadTarget );
}

///========================================================================
//	Function:		TadTargetType()
//
//	Description:
//		return the firing range for the TAD object's Target.
//
//	Input:			pTadObject		TAD object whose target target position is needed
//
//	Ouput:			pTargetPos		TAD object target's position
//
///========================================================================

ITEM_TYPE	TadTargetType( TAD* pTadObject )
{
	TAD*			pTarget;
	ITEM_TYPE		eTargetType = ARMY_NULL_OBJ;

	ASSERT( pTadObject );

	// get the Target's target type
	if( pTadObject->pLastTarget )
	{
		pTarget     = pTadObject->pLastTarget;
		eTargetType = pTarget->eObjType;
	}

	return( eTargetType );
}

///========================================================================
//	Function:		TadFiringRange()
//
//	Description:
//		return the firing range for the TAD object.
//
//	Input:			pTadObject		TAD object whose firing range is needed
//
//	Ouput:			nFiringRange	TAD object firing range
//
///========================================================================

long	TadFiringRange( TAD* pTadObject )
{
	long	nFiringRange = 0;

	// validate the paramters
	ASSERT( pTadObject );

	// does this tad object actually have a firing range?
	switch( pTadObject->eObjType )
	{
	case ARMY_NULL_OBJ:
		// error: null object type
		TRACE( "ERROR: attempting to obtain a firing range for a NULL object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	case ARMY_UNIT:
		nFiringRange = UnitFiringRange((UNIT *) (pTadObject->pItem));
		break;

	case ARMY_VEHICLE:
	case ARMY_SARGE:
	case ARMY_ASSET:
	case ARMY_TROOPER:
		nFiringRange = AiObjectFiringRange(pTadObject->pItem);
		break;

//	case ARMY_STRUCTURE:
//	case ARMY_OBSTACLE:
//		break;
	default:
		// error: unknown object type
		TRACE( "ERROR: attempting to obtain a firing range for an unknown object type (%d). [%s : %d ]\n",
			pTadObject->eObjType, __FILE__, __LINE__ );
		ASSERT(0);
		break;
	}

	// give em the range
	return( nFiringRange );
}

///========================================================================
//	Function:		TadDistanceToTarget()
//
//	Description:
//		return the distance from the TAD object to it's Target.
//
//	Input:			pTadObject		TAD object whose target firing range is needed
//
//	Ouput:			nDistance		distance from TAD object to Target
//
///========================================================================

long	TadDistanceToTarget( TAD* pTadObject )
{
	SPOINT	pObjectPos;
	SPOINT	pTargetPos;
	long	nDistance = 0;

	// validate the paramters
	ASSERT( pTadObject );
	if( pTadObject->pLastTarget == NULL)
		goto exit;

	// get the object's position
	pObjectPos = TadPosition( pTadObject );

	// get the Target's position
	pTargetPos = TadMyPosition(pTadObject->pLastTarget );
	ASSERT( pTargetPos.x );

	// get the distance
	nDistance = GetDistance( &pObjectPos, &pTargetPos );

	// give em the distance
exit:
	return( nDistance );
}

///========================================================================
//	Function:		TadTargetPosition()
//
//	Description:
//		return the firing range for the TAD object's Target.
//
//	Input:			pTadObject		TAD object whose target target position is needed
//
//	Ouput:			pTargetPos		TAD object target's position
//
///========================================================================

SPOINT	TadTargetPosition( TAD* pTadObject )
{
	SPOINT		pTargetPos = OFF_THE_MAP;

	if ( pTadObject )
	{
		// get the Target's position
		if( pTadObject->pLastTarget )
			pTargetPos = TadMyPosition( pTadObject->pLastTarget );
	}
	return( pTargetPos );
}

///========================================================================
//	Function:		TadSearchPattern()
//
//	Description:
//		return the search patten indecies matching the direction parameter..
//
//	Input:			nQuad		0,0 quad index
//					nDirection	direction object is searching
//					pIndecies	the list of indecies for the search pattern found
//
//	Ouput:			none
//
///========================================================================

void	TadSearchPattern( int nQuad, int nDirection, int* pIndecies )
{
	short		nXoffset;
	short		nYoffset;
	int			nIndex;
	int			nEntry;
	int*		pEntryPtr;
	TAD_OFFSET*	pPattern;

	// determine which of the 16 quadrants the direction parameter is in
	nIndex = (nDirection >> 4);

	// now extract the pattern
	pPattern = TADsearchTable[ nIndex ];

	// now convert the pattern into quadrant indecies for searching,
	// note that the initial quadrant value is the 0th entry
	pEntryPtr  = pIndecies;
	*pEntryPtr = nQuad;
	++pEntryPtr;

	// now fill in the remaining quad indecies
	for( nEntry=1; nEntry<TAD_MAX_QUADS; ++nEntry )
	{
		// get the X and Y offsets and calculate the corresponding index
		nXoffset   = pPattern[ nEntry ].nXoffset;
		nYoffset   = pPattern[ nEntry ].nYoffset;
		nIndex     = nQuad + (nYoffset * TADquadWidth) + nXoffset;
		if ( (nIndex >= 0) && (nIndex < TADmaxSearch) )
		{
			*pEntryPtr = nIndex;
			++pEntryPtr;
		}
	}
}

///========================================================================
//	Function:		TadFlags()
//
//	Description:
//		set the currently active Primary Target object.
//
//
//	Input:			pTadObject		pointer to object
//					mask			mask to apply to flags field
//					bClear			clear or set the field using the mask
//
//	Ouput:			TRUE		if object has another way point
//					FALSE		otherwise
//
///========================================================================

void	TadFlags( TAD* pTadObject, int mask, BOOL bClear )
{
	if ( pTadObject )
	{
		if ( bClear )
			CLEAR_FLAGS( pTadObject->bFlags, mask );
		else
			SET_FLAGS( pTadObject->bFlags, mask );
	}
}

///========================================================================
//	Function:		TadIsFlags()
//
//	Description:
//		set the currently active Primary Target object.
//
//
//	Input:			pObject		pointer to object
//					mask		mask to apply to flags field
//
//	Ouput:			TRUE		if object has mask set
//					FALSE		otherwise
//
///========================================================================

BOOL	TadIsFlags( TAD* pTad, int mask )
{
	BOOL	answer = FALSE;

	if ( pTad )
		if ( ( pTad->bFlags & mask) == mask )
			answer = TRUE;

	return( answer );
}

///========================================================================
//	Function:		TadValidate()
//	Description:	Prove a tad is plausibly legal
///========================================================================

void TadValidate(TAD* pTad)
{
}

///========================================================================
//	Function:		TadValidateAttacker()
//	Description:	Prove an attacker is in a targets attacker list
///========================================================================

void TadValidateAttacker( TARGETINFO* pTargetInfo, LONG nAttackerID )
{

}




///========================================================================
//	Function:		TadValidateHitMe()
//	Description:	validate all active unit hitme objects
///========================================================================

void TadValidateHitMe( char* pSourceName )
{
}


void TadDrawLines( void ) {;}

//=======================================================================
//								EOF
//=======================================================================
