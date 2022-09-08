//========================================================================
//	FILE:			$Workfile: Tad.cpp $
//
//	DESCRIPTION:	AI Target Acquisition Driver (TAD) API routines.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, June 17, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Tad.cpp 57    4/07/98 6:14a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	TadTargetLocation()
//		For the attacker, passed in, return the location, as an EPOINT, of
//		the current target if there is one, or 0 if none.
//	TadTargetFiringRange()
//		For the attacker, passed in, return the firing range of the current
//		target. This should be the same as the target fire perimeter.
//	TadBeingHit()
//		Inform TAD who is currently damaging an attacker. Note that one can
//		be hit by multiple parties on a turn (a logical frame). TAD decides
//		which party is the single most important one, and just keeps that one
//		as the HIT_ME TARGET. TAD can store the current play cycle timestamp
//		to assist it in its HIT_ME decisions
//	TadUpdateQuadLocation()
//		updates the object TAD quadrant location reference.
//	TadAssignVictims()
//		updates the object TAD quadrant location reference.
//	TadTargetAcquisition()
//		Perform target acquisition for a local army.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Tad.cpp $
//  
//  57    4/07/98 6:14a Bwilcox
//  tad cleanup
//  
//  55    4/03/98 2:33p Phu
//  validation from andy
//  
//  54    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  53    3/30/98 3:27p Aburgess
//  path for bad HitMe pointer
//  
//  52    3/27/98 2:05p Aburgess
//  hack to resolve HitMe bug
//  
//  51    98-03-10 18:15 Dmaynard
//  
//  50    3/10/98 8:32a Bwilcox
//  
//  49    3/09/98 6:44p Bwilcox
//  fixed tad bug of beinghit
//  
//  48    3/07/98 11:53p Nrobinso
//  move .h file to stdafx; setup macro for debug layer
//  
//  47    3/04/98 12:15p Nrobinso
//  Fix release of tad if enemy out of sight
//  
//  46    3/03/98 11:46p Nrobinso
//  avoid the bad pitem
//  
//  45    3/03/98 9:34p Nrobinso
//  Assert on bad tad item
//  
//  44    3/03/98 3:05p Bwilcox
//  tad drops target after it goes invisible (10 sec after no longer seen)
//  or if target has 0 strength
//  
//  43    3/03/98 2:29p Aburgess
//  modifications made to release a active target if out of visibility
//  
//  42    2/18/98 2:18p Phu
//  return immediatley from TadHitme
//  
//  41    2/18/98 2:02p Bwilcox
//  revsered tad args in call, reenabled tadbeing hit
//  
//  40    2/18/98 12:18p Bwilcox
//  tadbeing hit now called. removed useless formation code. removed attack
//  wander code
//  
//  39    2/18/98 12:05p Bwilcox
//  args to tadbeing hit changed to items from tads
//  
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"

#include "Army.h"
#include "AiAccess.h"
#include "miscfile.h"
#include "Ai.h"
#include "MainFrm.h"
#include "Tad.h"
#include "trooper.h"
#include "unit.h"
#include "item.h"
#include "aix.h"
#include "comm.h"

///========================================================================
//	Function:		TadTargetFiringRange()
//
//	Description:
//		For the attacker, passed in, return the firing range of the current
//		target. This should be the same as the target fire perimeter.
//
//	Input:			pAttacker	Attacker TAD information pointer
//
//	Ouput:			location	firing range of attacker"s current Target
//								if no target, a value of 0 is returned
//
///========================================================================

long	TadTargetFiringRange( TAD* pAttacker )
{
	TAD*	pTad;
	long	nFiringRange = 0;

	// validate the paramters
	ASSERT( pAttacker );
	pTad         = pAttacker->pLastTarget;

	// make sure we have a target
	if ( pTad )
		nFiringRange = TadFiringRange( pTad );
	
	return( nFiringRange );
}

///========================================================================
//	Function:		TadBeingHit()
//
//	Description:
//		Inform TAD who is currently damaging an attacker. Note that one can
//		be hit by multiple parties on a turn (a logical frame). TAD decides
//		which party is the single most important one, and just keeps that one
//		as the HIT_ME TARGET. TAD can store the current play cycle timestamp
//		to assist it in its HIT_ME decisions
//
//	Input:			pHitter		Attacker TAD information pointer
//					pBeingHit	Target TAD information pointer
//
//	Ouput:			none
//
///========================================================================

void	TadBeingHit( ITEM* pHitItem, ITEM* pBHitItem )
{
    TAD* pHitter 	= (TAD*) pHitItem->pTad;
    TAD* pBeingHit  = (TAD*) pBHitItem->pTad;

	int			nPotentialPower;
	int			nOldPower;
	TAD*		pOldHitMeTad;	// who used to hit us
    TAD*		selectedHitter;  // who we will treat as needing defense from

    selectedHitter = pHitter;		// by default he will be the one to hit


	// validate the parameters and their tads
	if (!pHitItem || !pBHitItem) return;
    if (!pHitter || !pBeingHit) return;

	int itype = ITEM_TYPE(pHitItem);
	ASSERT ((itype == ARMY_SARGE || itype == ARMY_VEHICLE || itype == ARMY_UNIT ||
		itype == ARMY_TROOPER ||	itype == ARMY_ASSET));

	// cant hit ourselves for now
	if ( ITEM_ARMY( pHitItem ) == ITEM_ARMY( pBHitItem) )
		return;

	// see if there are any prior hitter of me
	pOldHitMeTad     = pBeingHit->pHitMeTarget; // who was previous hitting him

    // if this is not the same guy, see if old is better
	if (pOldHitMeTad != pHitter && pOldHitMeTad)
	{
		// see if this hit was a better one than the last
		nPotentialPower = ItemPower( pHitItem, pBeingHit->pItem );
		nOldPower       = ItemPower( pOldHitMeTad->pItem, pBeingHit->pItem );

		SPOINT oldpt = TadPosition(pOldHitMeTad); 	// where old guy was
		SPOINT hitpt = TadPosition(pHitter);		// where new guy is
		SPOINT basept = TadPosition(pBeingHit);		// where I am

        // if new is weaker in value, use old
		if ( nPotentialPower < nOldPower )
			selectedHitter = pOldHitMeTad;						// select old guy
        // if they are the same, pick old if as close or better
		else if ( (nPotentialPower == nOldPower) &&
            GetDistance(&oldpt,&basept) <= GetDistance(&hitpt,&basept))
            selectedHitter = pOldHitMeTad;
	}

    pBeingHit->pHitMeTarget  = selectedHitter;

}

///========================================================================
//	Function:		TadUpdateQuadLocation()
//
//	Description:
//		updates the object TAD quadrant location reference.
//
//	Input:			pAttacker	Attacker TAD information pointer
//
//	Ouput:			none
//
///========================================================================

void	TadUpdateQuadLocation( TAD* pAttacker )
{
	ITEM*	pItem;
	
	// validate the parameter
	ASSERT( pAttacker );

	// get the actual object then request the update to the TAD hash map
	pItem = pAttacker->pItem;

	// update the hash map
	TadUpdateQuad( pAttacker->eObjType, pItem,
				   pItem->oldPosition,
				   pItem->position
				 );
}


///========================================================================
//	Function:		TadAssignVictims()
//
//	Description:
//		This routine is invoked by units to assign victims to each trooper
//		to fire upon. This call is made once per frame when a unit is engaged,
//		prior to asking the troopers to fight.
//
//		This routine looks at who is attacking and who is being attacked,
//		and stores in each trooper both the specific object to be attacked,
//		and what type that object is. That is, it is writing directly onto
//		the trooper data.  Later, troopers can just consult this data.
//
//	Input:			pAttacker	Attacker TAD looking for a victim
//
//	Ouput:			none
//
///========================================================================

void	TadAssignVictims( TAD* pAttacker )
{
	ITEM_TYPE	eAttackerType;
	ITEM_TYPE	eTargetType;
	SPOINT		pPosition;
	UNIT*		pUnit;
	UNIT*		pTargetUnit;
	TROOPER*	pTrooper;
	ITEM*		pItem;
	ITEM*		pTarget;

	// validate parameters
	ASSERT( pAttacker );

	// get the attacker type
	eAttackerType = pAttacker->eObjType;

	// find the target
	pTarget =  TadMyTargetObject( pAttacker );
	if ( pTarget )
	{
		eTargetType = ITEM_TYPE( pTarget );

		// decide how to assign the victims based on the attacker and target types
		if ( eAttackerType == ARMY_UNIT )
		{
			pUnit       = (UNIT*)pAttacker->pItem;
			pTargetUnit = (UNIT*)(pTarget);
            int i;
			FOR_EACH_TROOPER(pUnit,pTrooper,i)
			{
				// find the closest trooper
				if ( eTargetType == ARMY_UNIT )
					pTarget = (ITEM*)UnitFindClosestTrooper( pTargetUnit,
										 &(pTrooper->common.position) );

				// remember who the victim is
				pTrooper->common.pVictim = pTarget;
			}
		}
		else
		{
			if ( eTargetType == ARMY_UNIT )
			{
				// get the attackers position
				pPosition = TadPosition( pAttacker );

				// find the closest trooper
				pUnit   = (UNIT*)(pTarget);
				pTarget = (ITEM*)UnitFindClosestTrooper( pUnit, &pPosition );
			}

			// remember who the victim is
			pItem                     = pAttacker->pItem;
			pItem->pVictim     = pTarget;
		}
	}
}

///========================================================================
//	Function:		TadTargetAcquisition()
//
//	Description:
//		Perform target acquisition for all LOCAL armies.
//
//	Input:			eArmy		local Army.
//
//	Ouput:			none
//
///========================================================================

void	TadTargetAcquisition( ARMY_TYPE eArmy )
{
	TAD*		pAttackerTad;
	TARGETINFO*	pTargetInfo;
	BOOL		bSmart;

	// make sure TAD is active
	if ( !TADactive )
	{
		TRACE( "ERROR: TAD not active. [%s : %d]\n", __FILE__,__LINE__);
		return;
	}

	pAttackerTad = TADlist[ eArmy ];

	// process all the ATTACKERs
	while (pAttackerTad != NULL)
	{
		// see if the Unit is active
		bSmart  = TadIsFlags( pAttackerTad, TAD_SMART );

		pTargetInfo  = &(pAttackerTad->targetInfo);
		if ( bSmart  )
		{
			// Select the target
			TadSelectTarget( pAttackerTad );
		}

		// go to next on list
		pAttackerTad = pAttackerTad->tadList;
	}
}

///========================================================================
//	Function:		TadCreateObject()
//
//	Description:
//		create a TAD structure.
//
//	Input:			eArmy		army this object belongs to
//					eObjType	type of object being loaded into a TAD
//					pItem		the object being loaded
//					pPosition	position in world of new object
//					bFlags		object flags
//
//	Ouput:			error		FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	TadCreateObject( int eArmy, int eObjType, ITEM* pItem, ULONG bFlags )
{
	TAD*		pTad     = NULL;
	BOOL		error    = TRUE;		// assume failure

	// creates a tad and crosslinks into the army's list of tads
	if ( TadCreate( eArmy, eObjType, pItem, bFlags ) )
	{
		TRACE("ERROR: failed TAD create. [%s:%d]\n", __FILE__, __LINE__ );
        pItem->pTad = NULL;
		goto exit;
	}
	pTad = (TAD*)(((UNIT*)pItem)->common.pTad);
	ASSERT(pTad);
	if (!pTad) 
		goto exit; // we failed

    	
	// if we made it here we were successful

	// signify success
	error = FALSE;

exit:
	return( error );
}

///========================================================================
//	Function:		TadDeleteObject()
//
//	Description:
//		delete a TAD entry and its associated TADLINK, removing it from the
//		TAD table.
//
//	Input:			pTadObject		MapQ object we need to delete.
//
//	Ouput:			none
//
///========================================================================

void	TadDeleteObject( TAD* pTadObject )
{
	ASSERT( pTadObject );
	TadDeleteTad( pTadObject );
}

///========================================================================
//	Function:		TadActivateArmy()
//
//	Description:
//		set the currently active Primary Target object.
//
//
//	Input:			eArmy		army to activate
//
//	Ouput:			none
//
///========================================================================

void	TadActivateArmy( ARMY_TYPE eArmy )
{
}

///========================================================================
//	Function:		TadCurrentTarget()
//
//	Description:
//		return the Target for this TAD.
//
//	Input:			pTadObject		TAD object whose target target position is needed
//
//	Ouput:			pTargetPos		TAD object target's position
//
///========================================================================

TAD*	TadCurrentTarget( ITEM* pItem )
{
	TAD*	pTadObject;
	TAD*	pMyTarget   = NULL;

	// verify parameters
	ASSERT( pItem );

	// now find the tad for this object
	pTadObject = (TAD*)pItem->pTad;
	if( pTadObject )	// find the target object
		pMyTarget = TadMyTargetTad( pTadObject );
	return( pMyTarget );
}

//=======================================================================
//								EOF
//=======================================================================
