//========================================================================
//	FILE:			$Workfile: UnitText.h $
//
//	DESCRIPTION:	Unit Text data
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, September 18, 1996
//
//	REVISION:		$Header: /ArmyMen/src/UnitText.h 15    2/04/98 9:53a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited
//                      All rights reserved
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/UnitText.h $
//  
//  15    2/04/98 9:53a Bwilcox
//  dead code elim and improved trace in debug
//  
//  14    1/13/98 5:52p Bwilcox
//  kneelfire added
//  
//  13    1/13/98 5:21p Bwilcox
//  pronefire and standfire
//  
//  12    12/09/97 12:12p Phu
//  
//  11    12/07/97 5:01p Bwilcox
//  
//  10    11/12/97 2:19p Bwilcox
//  nestfire implemenattion
//  
//  9     11/06/97 12:41p Bwilcox
//  better unit trace
//  
//  8     11/05/97 10:40a Nrobinso
//  removed units names and other unused string data
//  
//  6     8/21/97 1:44p Bwilcox
//  changed unitorders names
//  
//  5     7/15/97 3:33p Awerner
//  fixed typo in unitordertext
//  
//  4     7/14/97 1:46p Bwilcox
//  revising unit orders
//  
//  3     7/05/97 10:25p Bwilcox
//  removed air refereneces
//  
//  2     7/03/97 8:32p Bwilcox
//  massive cleanups.
//  
//  2     9/30/96 4:11p Aburgess
//  added error string
//  
//  1     9/19/96 2:16p Aburgess
//  UNIT text strings (i.e."Tiger Squad")
//  
// 
//  $Nokeywords:$
//========================================================================

#ifndef __UNITTEXT_H__
#define __UNITTEXT_H__

///========================================================================
//							DEFINES
///========================================================================

#define	MSG_MAX_MSGS					200

#define	MSG_MAX_PIECES					6

///========================================================================
//							LOOKUP TABLES
///========================================================================


// Unit mode strings	
char*	UNIT_MODE_TEXT[] =
{
	"Terminated"			// DEAD
	"In Reserve",			// inside HQ
	"In Transit",			// in a vehicle
	"Moving",				// moving
	"Engaged",				// in a fight
	"Terminated",			// DEAD but graphic still running
};

char*	UnitModeText[] =
{"IgnoreFire","ReturnFire","DefendFire","AttackFire",
    "Nestfire","ProneFire","KneelFire","StandFire","EvadeFire"};

// Unit order strings	
char*	UnitOrderText[] =
{
	"No Order",
	"Goto", // defend
	"Goto", // attack
	"Follow",		
};

#endif	__UNITTEXT_H__

///========================================================================
//							EOF
///========================================================================
