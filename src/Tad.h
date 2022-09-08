//========================================================================
//	FILE:			$Workfile: Tad.h $
//
//	DESCRIPTION:	AI Target Acquisition Driver API defines, structures,
//						and prototypes.
//
//	DESIGNER:		Bruce Wilcox
//	IMPLEMENTOR:	Andrew J Burgess
//
//	CREATED:		Tuesday, June 17, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Tad.h 21    4/07/98 6:15a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Nokeywords:$
///========================================================================

#ifndef __TAD_H__
#define __TAD_H__


///========================================================================
//							INCLUDES
///========================================================================
#ifndef __TADPRIV_H__
#include "TadPriv.h"
#endif

///========================================================================
//							GLOBAL DEFINES
///========================================================================
#define	TARGET_STANDBY_PERIMETER	200
#define	TARGET_FIRE_PERIMETER		160

// clear/set flags
#define	TAD_SET_IT				FALSE
#define	TAD_CLEAR_IT			TRUE

// Army Flags
#define TAD_ARMY_1				0x0001
#define TAD_ARMY_2				0x0002
#define TAD_ARMY_3				0x0004
#define TAD_ARMY_4				0x0008

// TAD flags
#define	TAD_CLEAR				(ULONG)0x00000000
#define	TAD_UNUSED_D				(ULONG)0x00000001
#define	TAD_UNUSED_C			(ULONG)0x00000002
#define	TAD_JUNK				(ULONG)0x00000008
#define	TAD_UNUSED_E			(ULONG)0x00000040
#define	TAD_UNUSED_F			(ULONG)0x00000080
#define	TAD_UNUSED_G			(ULONG)0x00000100
#define	TAD_UNUSED_H			(ULONG)0x00000200
#define	TAD_UNUSED_I			(ULONG)0x00000400
#define	TAD_UNUSED_J			(ULONG)0x00000800
#define	TAD_UNUSED_K			(ULONG)0x00001000
#define	TAD_UNUSED_L			(ULONG)0x00002000
#define	TAD_UNUSED_M			(ULONG)0x00004000
#define	TAD_UNUSED_N			(ULONG)0x00008000
#define	TAD_UNUSED_O			(ULONG)0x00010000
#define	TAD_UNUSED_P			(ULONG)0x00020000
#define	TAD_UNUSED_Q			(ULONG)0x00040000
#define	TAD_UNUSED_R			(ULONG)0x00080000
#define	TAD_UNUSED_S			(ULONG)0x00100000
#define	TAD_UNUSED_T			(ULONG)0x00200000
#define	TAD_UNUSED_W			(ULONG)0x00400000
#define	TAD_UNUSED_X			(ULONG)0x00800000
#define	TAD_UNUSED_U			(ULONG)0x01000000
#define	TAD_UNUSED_V			(ULONG)0x02000000
#define	TAD_SMART				(ULONG)0x08000000

///========================================================================
//							GLOBAL MACROS
///========================================================================
#define	CHK_FLAGS( bFlags, mask )		((bFlags) &= ~(mask))
#define	SET_FLAGS( bFlags, mask )		((bFlags) |= (mask))
#define	CLEAR_FLAGS( bFlags, mask )		((bFlags) &= ~(mask))

#define	IS_SMART( bFlags )				(((bFlags) & TAD_SMART))
#define	SET_SMART( bFlags )				((bFlags) |= TAD_SMART)
#define	CLEAR_SMART( bFlags )			((bFlags) &= ~TAD_SMART)

#define	TAD_VALIDATE( x )				// nada


///========================================================================
//							GLOBAL DATA TYPES
///========================================================================


///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================

extern	long	TadTargetFiringRange( TAD* pAttacker );
extern	void	TadBeingHit( ITEM* pHitter, ITEM* pBeingHit );
extern	void	TadUpdateQuadLocation( TAD* pAttacker );
extern	void	TadAssignVictims( TAD* pAttacker );
extern	void	TadTargetAcquisition( ARMY_TYPE eArmy );
extern	BOOL	TadCreateObject( int eArmy, int eObjType, ITEM* pObject, ULONG bFlags );
extern	void	TadDeleteObject( TAD* pTadObject );
extern	void	TadActivateArmy( ARMY_TYPE eArmy );
extern	TAD*	TadCurrentTarget( ITEM* pObject );
extern	void	TadSetAlliance( ITEM* pObject, int fArmyFlags );
extern	int		TadGetAlliance( ITEM* pObject );
extern	int		TadHaveAllianceWith( ITEM* pObject, int fArmyFlags );

// these were in tadpriv but are publicly visible to UNIT.cpp and ARMY.cpp
extern	void	TadFlags( TAD* pTadObject, int mask, BOOL bClear );
extern	BOOL	TadCreateQuad( TAD* pObject, SPOINT pNewPos );
extern	void	TadUpdateQuad( int objType, ITEM* object, SPOINT oldPos, SPOINT newPos );

///========================================================================

#endif		// __TAD_H__

///========================================================================
//								EOF
///========================================================================
