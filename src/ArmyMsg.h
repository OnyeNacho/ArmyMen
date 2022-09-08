/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: ArmyMsg.h $
//
//	DESCRIPTION:	Vehicle messaging interface
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Friday, April 29, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ArmyMsg.h 24    3/27/98 10:06a Bwilcox $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/ArmyMsg.h $
//  
//  24    3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  23    3/16/98 2:20p Dmaynard
//  Passing the Comm Message Sequence number all the way down to
//  TrooperUpdateReceiveMessage in order to handle multiple commands packed
//  into same comm sequence message.
//  
//  22    2/25/98 5:33p Dmaynard
//  Added a parameter to ArmyMessage Flush, and protected against infinite
//  recurrsion in ArmyMessageSend.
//  
//  21    2/17/98 6:23p Dmaynard
//  Added Msg Summary output TRACE's after each game is finished.
//  94% of messages are Unit Update Messages.
//  
//  20    2/10/98 11:12a Bwilcox
//  added object_place message ytpe
//  
//  19    2/02/98 6:39p Bwilcox
//  mine removal over the net
//  
//  18    1/13/98 6:49p Dmaynard
//  Changed 3 defined constants to COmm member variables for tuning.
//  MAXSENDINTERVAl MINSENDINTERVAL AND ENOUGH_MSG_SIZE
//  
//  17    1/08/98 1:52p Phu
//  mp airsupport
//  
//  16    12/09/97 12:11p Phu
//  
//  15    11/18/97 12:45p Bwilcox
//  want_item_messages
//  
//  14    10/24/97 9:10a Bwilcox
//  cleaning up messages and doing unit into vehcle
//  
//  13    10/21/97 3:59p Bwilcox
//  unitdeploy messaging
//  
//  11    9/09/97 2:17p Awerner
//  Events should now work across the network
//  
//  10    8/25/97 3:07p Bwilcox
//  SargeVehicleMessages for entering and exiting vehicles across net added
//  
//  9     8/17/97 7:16p Nrobinso
//  minimize message data
//  
//  8     8/17/97 11:27a Bwilcox
//  names of TROOPxxx are now TROOPERxxx in a cleanup
//  
//  7     8/16/97 3:56p Bwilcox
//  sending gameover messages since when game ends, a player stops comming
//  
//  6     8/15/97 8:38p Bwilcox
//  sarge death throes split into 2 net messages
//  
//  5     8/15/97 2:13p Bwilcox
//  added 2nd death message for troopers upon final death removal
//  
//  4     7/30/97 7:06p Dmaynard
//  SargeMsgs
//  
//  3     7/22/97 10:44a Bwilcox
//  
//  2     7/22/97 10:34a Bwilcox
//  removed TroopFireMessage and related stuff
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  3     5/15/97 12:13a Aburgess
//  new MSG_TYPEs combined
//  
//  2     5/01/97 10:50a Dmaynard
//  Removed SendArmyMsg (moved to gameproc.cpp)
//  
//  1     4/29/97 5:13p Nrobinso
//  
//
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __ARMYMSG_H__
#define __ARMYMSG_H__

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "donottouch.h"

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////

void ArmyMessageReceive(ARMY_MESSAGE *pMsg, int army_index, DWORD seq);
void ArmyMessageSend(ARMY_MESSAGE *pMsg);
BOOL ArmyMessageFlush(int nMin);
void ArmyMessageCount(ARMY_MESSAGE *pMsg);
void ClearMessageCounts (void);
void DumpMessageCounts (void);
#endif



