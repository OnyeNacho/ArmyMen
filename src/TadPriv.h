//========================================================================
//	FILE:			$Workfile: TadPriv.h $
//
//	DESCRIPTION:	AI Target Acquisition Driver defines, structures, and prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Friday, October 22, 1996
//
//	REVISION:		$Header: /ArmyMen/src/TadPriv.h 33    4/07/98 6:17a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/TadPriv.h $
//  
//  33    4/07/98 6:17a Bwilcox
//  tad cleanup
//  
//  31    3/30/98 3:27p Aburgess
//  path for bad HitMe pointer
//  
//  30    3/27/98 2:05p Aburgess
//  hack to resolve HitMe bug
//  
//  29    3/09/98 6:44p Bwilcox
//  fixed tad bug of beinghit
//  
//  28    3/03/98 2:29p Aburgess
//  modifications made to release a active target if out of visibility
//  
//  27    2/20/98 3:41p Nrobinso
//  remove unsued code
//  
//  
//  $Nokeywords:$
///========================================================================

#ifndef __TADPRIV_H__
#define __TADPRIV_H__


///========================================================================
//							INCLUDES
///========================================================================
#ifndef __AIROUTER_H__
    #include "airouter.h"
#endif

#include "object.h"

#ifndef __MAINFRAME_H__
	#include "mainfrm.h"
#endif



///========================================================================
//							GLOBAL DEFINES
///========================================================================

#define	TAD_MAX_PROCESSED		3
#define	TAD_MAX_POTENTIAL		16
#define	TAD_LAST_POTENTIAL		TAD_MAX_POTENTIAL-1
#define	TAD_MIN_QUADS_2_SEARCH	3
#define	TAD_MAX_ATTACKERS		64

// 16 x 16 tile quadrant
#define	TAD_QUAD_SIZE_DEFAULT	16

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================


struct TAD; // forward ref

// TAD attacker information structure
typedef struct
{
	// potential targeting information
	SHORT			nNumPotentialTargets;
	TAD*			pPotentialTargets[ TAD_MAX_POTENTIAL+1 ];  // list of potential targets
	USHORT			nTargetQuotients[ TAD_MAX_POTENTIAL+1 ];   // values of those targets

} ATTACKINFO;

// TAD target information structure
typedef struct
{
	USHORT		nTargetingValue;
	USHORT		nMinAttackLevel;
	USHORT		nMaxAttackLevel;
	USHORT		nNumAttackers;
	TAD*		pAttackers[ TAD_MAX_ATTACKERS+1 ];  // list of who is already attacking this target
} TARGETINFO;


// TAD object information structure
struct TAD
{
    // this armies lists of tads
    TAD*			tadList;		// linked list of this armies tads
	// leave tadlist first so can keep arrays looking like tads for linked list purposes
	
	ITEM_TYPE		eObjType;		// type of object in the list.
									// defines how to access the pointer.
	ULONG			bFlags;			// Bit-Field Flags
	ITEM*			pItem;			// what object this tad corresponds to

	// these are the various targets
	TAD*			pLastTarget;		// the last target we actually chose
	TAD*			pHitMeTarget;		// last tad to shoot at this guy

	SHORT			nQuotient;		// quotient for targeting
	SHORT			nSort;			// sorting preference
	TARGETINFO		targetInfo;		// who is attacking this tad at present 
	
	// miscellaneous data
	BOOL			bAlliances[ARMY_LAST_ARMY];
	char			nBirthBonus;	// artificial weighting factor
	BOOL			bChgQuad;		// trigger for quadrant changes
};

// TAD linked list structure
struct TADLINK;
struct TADLINK
{
	TAD*		pTadObject;		// TAD object information
	TADLINK*	pPrev;			// previous object in list
	TADLINK*	pNext;			// next object in list
} ;

typedef	TADLINK	QUADS;

// TAD search lookup table entry
typedef struct
{
	short	nXoffset;
	short	nYoffset;
} TAD_OFFSET;

///========================================================================
//							GLOBAL VARIABLES
///========================================================================
extern 	TAD*		TADlist[ ARMY_LAST_ARMY ];		
extern	BOOL		TADactive;

///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================

extern	BOOL		TadInit( void );
extern	void		TadExit( void );
extern	void		TadFree( void );
extern	BOOL		TadCreate( int eArmy, int eObjType, ITEM* pObject, ULONG bFlags );
extern	void		TadRestore( void );
extern	void		TadBestTargets( TAD* pAttacker );
extern	BOOL		TadIsFlags( TAD* pTad, int mask );
extern	void		TadInitNextAttacker( ARMY_TYPE eArmy );
void	TadSelectTarget( TAD* pAttackerTad );

extern	void		TadDeleteTad( TAD* pTadObject );
extern	TADLINK*	TadFindQuadLink( TAD* pTadObject );
extern	int			TadWhichArmy( TAD* pObject );
extern	int			TadArmy( TAD* pObject );
extern	void		TadRoutePlan( TAD* pTadObject, SPOINT pLocation );
extern	SPOINT		TadMyPosition( TAD* pObject );
extern	SPOINT		TadPosition( TAD* pTadObject );
extern	long		TadFiringRange( TAD* pTadObject );
extern	long		TadDistanceToTarget( TAD* pTadObject );
extern	TAD*		TadMyTarget( TAD* pTadObject );
extern	ITEM*		TadMyTargetObject( TAD* pTadObject );
extern	TAD*		TadMyTargetTad( TAD* pTadObject );
extern	ITEM_TYPE	TadTargetType( TAD* pTadObject );
extern	SPOINT		TadTargetPosition( TAD* pTadObject );
extern	void		TadDrawLines( void );

///========================================================================

#endif		// __TADPRIV_H__

///========================================================================
//								EOF
///========================================================================
