//========================================================================
//	FILE:			$Workfile: UnitMsg.h $
//
//	DESCRIPTION:	Unit messaging interface.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, November 21, 1996
//
//	REVISION:		$Header: /ArmyMen/src/UnitMsg.h 25    3/27/98 10:06a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996, 1997 The 3DO Company
//      Unauthorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/UnitMsg.h $
//  
//  25    3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  24    3/16/98 2:20p Dmaynard
//  Passing the Comm Message Sequence number all the way down to
//  TrooperUpdateReceiveMessage in order to handle multiple commands packed
//  into same comm sequence message.
//  
//  23    2/15/98 12:46p Bwilcox
//  
//  22    2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  21    1/15/98 2:20p Bwilcox
//  convert firedist to unsigned char
//  
//  20    1/15/98 12:07p Bwilcox
//  removed nstrength
//  
//  19    12/09/97 12:12p Phu
//  
//  18    10/24/97 4:38p Bwilcox
//  revised trooperupdate message 
//  
//  17    10/24/97 9:10a Bwilcox
//  cleaning up messages and doing unit into vehcle
//  
//  16    10/21/97 3:59p Bwilcox
//  unitdeploy messaging
//  
//  14    8/21/97 6:55p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  13    8/17/97 7:16p Nrobinso
//  minimize message data
//  
//  12    8/17/97 11:27a Bwilcox
//  names of TROOPxxx are now TROOPERxxx in a cleanup
//  
//  11    8/16/97 3:08p Nrobinso
//  revamp fire weapon system
//  
//  10    8/15/97 2:13p Bwilcox
//  added 2nd death message for troopers upon final death removal
//  
//  9     8/07/97 11:22p Nrobinso
//  removed percent data from damage messages
//  
//  8     8/01/97 6:05p Dmaynard
//  Rearranged Message Structures to conform to the required first two
//  fields a USHORT nSize and a UniqueID
//  
//  7     7/22/97 1:37p Bwilcox
//  removed UnitUpdate messages, fixed remote trooper updating
//  
//  5     7/09/97 11:44p Bwilcox
//  unit/trooper cleanups
//  
//  4     7/08/97 2:36p Bwilcox
//  minimal crashlogic added
//  
//  3     7/08/97 11:28a Bwilcox
//  separating receive for unit/trooper and cleanups
//  
//  2     7/07/97 6:14p Bwilcox
//  contigious UID for units in legion, unit messaging cleanups, removal of
//  dead defs in army.h
//  
//  1     7/03/97 5:19p Nrobinso
//  
//  
//  $Nokeywords:$
///========================================================================

#ifndef __UNITMSG_H__
#define __UNITMSG_H__

///========================================================================
// Includes
///========================================================================

#include "ArmyMsg.h"
#include "donottouch.h"


///========================================================================
//					Global Variables
///========================================================================

///========================================================================
//					Global Prototypes
///========================================================================

void	UnitUpdateMessageSend( UNIT* pUnit );
void	UnitSendPending( UNIT *pUnit );
void	UnitDeployMessageSend( UNIT* pUnit );
void	UnitVehicleMessageSend( UNIT* pUnit,VEHICLE* pVehicle,BOOL bEnter );

void	UnitMessageReceive( ARMY_MESSAGE *pMsg, int army_index, DWORD seq);

void	TrooperDamageMessageSend( TROOPER* pTrooper, int damagetodo, int damagetype, SPOINT *from,UID fromUID );
void	TrooperDeathMessageSend( TROOPER* pTrooper );
void	TrooperGoneMessageSend( TROOPER* pTrooper );

void	TrooperMessageReceive( ARMY_MESSAGE *pMsg, int army_index );

#endif

///========================================================================
//								EOF
///========================================================================
