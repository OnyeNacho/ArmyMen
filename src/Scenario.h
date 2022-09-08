//========================================================================
//	FILE:			$Workfile: Scenario.h $
//
//	DESCRIPTION:	SCenario routiens
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Monday, October 7, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Scenario.h 5     12/09/97 12:12p Phu $
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
//  $Log: /ArmyMen/src/Scenario.h $
//  
//  5     12/09/97 12:12p Phu
//  
//  4     10/10/97 6:52p Nrobinso
//  return number of mission from SetupScenario()
//  
//  2     9/15/97 9:56a Nrobinso
//  change scenarios/missions to conform to new standard
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  3     4/14/97 7:28a Aburgess
//  modifications made to support full Army creation along with unit
//  reserves. Vehicle reserves have yet to be done.
//  
//  2     12/05/96 12:48p Aburgess
//  added new prototypes for skipping and reading scenario blocks.
//  
//  1     10/07/96 12:29p Nrobinso
//  Scneario related functions
//  
//  $Nokeywords:$
///========================================================================

#ifndef __SCENARIO_H__
#define __SCENARIO_H__

///========================================================================
//							GLOBAL DEFINES
///========================================================================

#define	SCENARIO_SKIP_FAIL			(LONG)~0

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================


///========================================================================
//							GLOBAL VARIABLES
///========================================================================

///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================
int		SetupScenario( char* pData, long nDataSize );
void	DeleteScenario();

///========================================================================

#endif		// __SCENARIO_H__

///========================================================================
//								EOF
///========================================================================
