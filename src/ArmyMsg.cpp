//========================================================================
//	FILE:			$Workfile: ArmyMsg.cpp $
//
//	DESCRIPTION:	Messaging for remote users
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Tuesday, April 29, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ArmyMsg.cpp 33    4/06/98 6:05p Dmaynard $
//
//========================================================================
//                 COPYRIGHT(C)1996-97 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/ArmyMsg.cpp $
//  
//  33    4/06/98 6:05p Dmaynard
//  Instrumenting types of UnitUpdateMessageSends
//  
//  31    4/02/98 2:03p Phu
//  typecasting to prevent warnings
//  
//  30    3/16/98 2:20p Dmaynard
//  Passing the Comm Message Sequence number all the way down to
//  TrooperUpdateReceiveMessage in order to handle multiple commands packed
//  into same comm sequence message.
//  
//  29    3/06/98 11:56a Phu
//  convert to 29 bit unique id mask
//  
//  28    2/19/98 2:55p Aburgess
//  modifications made to support BAD Map detection in remote players.
//  Added checks for BootCamp game play mode.
//  
//  27    2/17/98 6:23p Dmaynard
//  Added Msg Summary output TRACE's after each game is finished.
//  94% of messages are Unit Update Messages.
//  
//  26    2/06/98 11:42a Phu
//  husks
//  
//  25    98/02/02 19:01 Dmaynard
//  
//  24    2/02/98 6:39p Bwilcox
//  mine removal over the net
//  
//  23    2/01/98 8:13p Nrobinso
//  on receipt of won/lost msg, set gameresult instead of calling gamover
//  directly
//  
//  22    1/27/98 1:51p Bwilcox
//  discard messages from armies not playing
//  
//  21    12/09/97 12:11p Phu
//  
//  20    12/07/97 6:21p Aburgess
//  setting of new WinningArmy gpGame variable
//  
//  19    11/20/97 10:48p Dmaynard
//  Added some TRACES to EventMessage Send and Receive to debug playing
//  multiple multi-player games
//  
//  18    10/27/97 2:34p Dmaynard
//  Allow UniqueID's of nuetral objects on the wire.  Some objects belong
//  to no army such as trees.  These Unique ID's will not get ranslated.
//  
//  17    10/24/97 5:15p Bwilcox
//  
//  16    10/24/97 2:56p Dmaynard
//  Dont translate UniqueID of zero
//  
//  15    10/24/97 11:18a Dmaynard
//  Added MultiPlayer menu option and start multiplayer game options and
//  changed how the translation of UniqueID's is handled.  UniqueID are now
//  translated into universal (color coded) format before  sending and each
//  macine translates from color to local index in receive armymessage.
//  
//  14    10/21/97 3:59p Bwilcox
//  unitdeploy messaging
//  
//  12    9/09/97 2:17p Awerner
//  Events should now work across the network
//  
//  11    8/16/97 3:56p Bwilcox
//  sending gameover messages since when game ends, a player stops comming
//  
//  10    8/16/97 10:29a Bwilcox
//  revised code using allowcommand or bothai to support ai for either or
//  both player1 and player2, 
//  
//  9     8/07/97 11:12p Nrobinso
//  moved globals.h to stdafx.h
//  
//  8     7/30/97 8:26p Dmaynard
//  REMOVE TRACE
//  
//  7     7/30/97 7:17p Dmaynard
//  Add SargeMessage
//  
//  6     7/28/97 7:42p Nrobinso
//  fix spelling of VehicleMessageReceive; add Sarge to messaging system
//  
//  5     7/24/97 12:59p Aburgess
//  added knowledge of ARMY_NULL_OBJs and removal of superfluous trace
//  statements
//  
//  4     7/22/97 1:27p Bwilcox
//  removed UnitUpdate messages, fixed remote trooper updating
//  
//  3     7/12/97 3:25p Bwilcox
//  deleted ARMY_POSITION pseudo-object type and all associated code
//  
//  2     7/08/97 11:27a Bwilcox
//  separating receive for unit/trooper and cleanups
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  15    6/10/97 3:42p Dmaynard
//  Debugging Messages
//  
//  14    6/10/97 12:42p Dmaynard
//  Replaced an ASSERT by a TRACE for debugging
//  
//  13    6/09/97 3:09p Aburgess
//  completed initial implementation of Assets for messaging, including
//  ASSERTs
//  
//  12    5/16/97 7:02a Dmaynard
//  Modified ArmyReceive Message to always swap ArmyID within an uniqueId
//  
//  11    5/15/97 12:33a Aburgess
//  processing unit messages
//  
//  10    5/14/97 10:31p Nrobinso
//  put in, but leave commented out AssetMessageReceive
//  
//  9     97-05-13 16:55 Dmaynard
//  
//  8     5/12/97 1:23p Dmaynard
//  Fixed bug when remote Vehicle deployed with a unit in vehicle.  You
//  must translate the UniqueID sent in the Secondary Unique ID flag
//  transmitted in the Deploy Message.
//  
//  7     5/10/97 10:07p Dmaynard
//  Added Messages for Explosions so the occur on the remote machine.
//  If the Explosion is caused by damage, or damage messages it is not
//  transmitted.  Only explosions that don't dameage objects are currently
//  transmitted.  In other cases damage message are sent which result in
//  the
//  explosion being generated locally on the remote machine.
//  
//  6     5/08/97 5:56p Awerner
//  Added object damage
//  
//  5     5/01/97 10:50a Dmaynard
//  Removed SendArmyMsg (moved to gameproc.cpp)
//  
//  4     4/30/97 8:16p Bwilcox
//  removed trace of sending message
//
//  3     4/29/97 5:26p Nrobinso
//  add some missing .h files
//  
//  2     4/29/97 5:20p Nrobinso
//  add ArmyMessageSend stub
//  
//  1     4/29/97 5:13p Nrobinso
//  
//  
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"
#include "Army.h"
#include "Ai.h"
#include "AiAccess.h"
#include "Object.h"
#include "ArmyMsg.h"
#include "AssetMsg.h"
#include "VehicleMsg.h"
#include "Floatmsg.h"
#include "ObjectMsg.h"
#include "Unitmsg.h"
#include "Sargemsg.h"
#include "gameproc.h"
#include "aix.h"
#include "gameflow.h"
#include "event.h"
#include "comm.h"
#include "husk.h"


/////////////////////////////////////////////////////////////////////////////
// Debugging support
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
char  *MessageNames[] = {
	// Generic and General purpose Message Types
	"UPDATE",
	"DAMAGE",
	"FIRE",
	"DEATH",
    "GAME_LOST",
    "GAME_WON",

	// Object message types
	"OBJMSG_DAMAGE",
    "OBJECT_REMOVE",

	// Float message types
	"FLOATMSG_MISSILE",
	"FLOATMSG_GRENADE",
 	"FLOATMSG_EXPLOSION",

	// Unit message types
    "UNIT_DEATH",
	"UNIT_DEPLOY",
	"UNIT_CHANGING_VEHICLE",

	// Trooper message types
	"TROOPER_UPDATE",
	"TROOPER_DEATH",
	"TROOPER_GONE",

	// Vehicle message types
	"DEPLOY",
	"UNDEPLOY",
	"DIED",

	// SARGE and Unit message types
	"SARGE_DEATH",
	"SARGE_GONE",
	"SARGETYPE",
	"SARGE_VEHICLE",
    "ITEM",
    "WANT_ITEM",
	"AIR_SUPPORT",


	// event message type
	"EVENT",

    "OBJECT_PLACE"

} ;
char  *MessageItemNames[] = {
	"NULL_OBJ", 
	"UNIT",
	"VEHICLE",
	"FLOAT",
	"TROOPER",
	"SARGE",
	"ASSET",
	"STRUCTURE",
	"OBSTACLE",
	"HUSK"
};

MSGSTAT MsgStats [NUM_MSG_TYPES]; 
MSGSTAT MsgItemStats[ARMY_LAST_LEGION];
#endif 

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					LOCAL Prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					     Code
/////////////////////////////////////////////////////////////////////////////

///========================================================================
//	Function:		ArmyMessageReceive()
//
//	Description:Dispatch vehicle messages
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	ArmyMessageReceive(ARMY_MESSAGE *pMsg, int army_index, DWORD seq)	{
	int		eObjType;
	int color;
	int index;    //

   if (pMsg->nUniqueID & ~AI_ID_29_BIT_MASK) {
       TRACE("Bad UniqueID  %x  Object Type %x \n",pMsg->nUniqueID,OBJTYPE(pMsg->nUniqueID));
   }
   ArmyMessageCount(pMsg);

   // if an army gets canned on the fly, he may have messages pending we
   // need to ignore.
    if (!IsPlayingUID(pMsg->nUniqueID))
    {
        TRACE("ignoring message from defunct army\n");
        return;
    }
   
  	if (pMsg->nUniqueID) { // Unique ID of zero is special cased
		color = EXTRACT_ARMY(pMsg->nUniqueID);
		index = gpComm->IndexFromColor((ARMY_COLOR) color);

		if ( (color >= ARMY_GREEN) && (color <= ARMY_GRAY) ) {
			pMsg->nUniqueID = (pMsg->nUniqueID & ~AI_ID_ARMY_MASK) | ENCODE_ARMY(index);
		}
//		else {
//			TRACE(" Got Army %d in UNIQUEID %x \n", color, pMsg->nUniqueID);
//		}
	}


	// figure out what type of object and see if it exists
	eObjType = OBJTYPE(pMsg->nUniqueID);
	switch( eObjType )
	{
	case ARMY_TROOPER:
        TrooperMessageReceive(pMsg,army_index);
		break;
	case ARMY_UNIT:
        UnitMessageReceive(pMsg,army_index, seq);
		break;
	case ARMY_VEHICLE:
		VehicleMessageReceive(pMsg,army_index);
		break;
	case ARMY_SARGE:
		SargeMessageReceive(pMsg,army_index);
		break;
	case ARMY_ASSET:
		AssetMessageReceive(pMsg,army_index);
		break;
	case ARMY_STRUCTURE:
	case ARMY_OBSTACLE:
		ObjectMessageReceive(pMsg);
		break;
	case ARMY_HUSK:
		HuskMessageReceive(pMsg);
		break;
	case ARMY_FLOAT:
		FloatMessageReceive(pMsg);
		break;
	default:
        // somebody won or lost
        if (pMsg->msg_type == GAME_LOST_MESSAGE)
        {
            TRACE("Received GAME_LOST_MESSAGE\n");
			gpGame->WinningArmy = army_index;
			gameresult=GAMERESULT_YOULOSE;
        }
        else if (pMsg->msg_type == GAME_WON_MESSAGE)
        {
            TRACE("Received GAME_WON_MESSAGE\n");
			if ( gpGame->BootCamp )
			{
				gpGame->WinningArmy = (( ARMY_PLAYER == army_index ) ? ARMY_PLAYER_2 : army_index);
				gameresult=GAMERESULT_YOULOSE;
			}
			else
			{
				gpGame->WinningArmy = army_index;
				gameresult=GAMERESULT_YOUWIN;
			}
        }
        else if (pMsg->msg_type == EVENT_MESSAGE_TYPE)
		{
			EventMessageReceive(pMsg);
		}
		else
        {
            TRACE("Unkown Army Msg Object Type %x\n",eObjType);
        }
		break;
	}
}

extern long tumstotal;
extern long tumsposition;
extern long tumsfacing;
extern long tumsfiring;
extern long tumsaction;


void ClearMessageCounts () {
#ifdef _DEBUG
	int i;
	for (i=0;i<NUM_MSG_TYPES;i++ )  {
		MsgStats[i].num = 0;
		MsgStats[i].bytes = 0;
		MsgStats[i].min = 9999;
		MsgStats[i].max = 0;
	}
	for (i=0;i<ARMY_LAST_LEGION;i++ )  {
		MsgItemStats[i].num = 0;
		MsgItemStats[i].bytes = 0;
		MsgItemStats[i].min = 9999;
		MsgItemStats[i].max = 0;
	}
 tumstotal = 0;
 tumsposition = 0;
 tumsfacing = 0;
 tumsfiring = 0;
 tumsaction = 0;
#endif
}


void DumpMessageCounts () {
#ifdef _DEBUG
	int i,tnum=0;
	for (i=0;i<NUM_MSG_TYPES;i++ )  tnum+= MsgStats[i].num;
	if(!gpComm->debugComm) return;
	TRACE("\n      Message Type  Msgs   %%   Total Bytes  MinSize MaxSize AveSize %d total msgs\n",tnum);
	if (tnum == 0) return;
	for (i=0;i<NUM_MSG_TYPES;i++ )  {
		if (MsgStats[i].num != 0) 
	TRACE("%18s%6d%4d%14d%9d%8d%8d \n",
		MessageNames[i],
		MsgStats[i].num,
		(MsgStats[i].num*100)/tnum,
		MsgStats[i].bytes,
		MsgStats[i].min,
		MsgStats[i].max,
 		MsgStats[i].bytes/MsgStats[i].num
		);
	}
	tnum = 0;
	for (i=0;i<ARMY_LAST_LEGION;i++ )  tnum+= MsgItemStats[i].num;
	if (tnum == 0) return;
	TRACE("\n         Item Type  Msgs   %%   Total Bytes  MinSize MaxSize AveSize  %d total msgs\n",tnum);
	for (i=0;i<ARMY_LAST_LEGION;i++ )  {
		if (MsgItemStats[i].num != 0) 
	TRACE("%18s%6d%4d%14d%9d%8d%8d \n",
		MessageItemNames[i],
		MsgItemStats[i].num,
		(MsgItemStats[i].num*100)/tnum,
		MsgItemStats[i].bytes,
		MsgItemStats[i].min,
		MsgItemStats[i].max,
 		MsgItemStats[i].bytes/MsgItemStats[i].num
		);
	}
	if (tumstotal) {
		TRACE("Total Unit Update Message %d\n",tumstotal);
		TRACE("   Position Updates %3d%% (%d)\n" , (tumsposition*100)/tumstotal, tumsposition);
		TRACE("     Facing Updates %3d%% (%d)\n" , (tumsfacing*100)/tumstotal, tumsfacing);
		TRACE("     Firing Updates %3d%% (%d)\n" , (tumsfiring*100)/tumstotal, tumsfiring);
		TRACE("     Action Updates %3d%% (%d)\n" , (tumsaction*100)/tumstotal, tumsaction);

	}
#endif
}


void ArmyMessageCount (ARMY_MESSAGE *pMsg) {
#ifdef _DEBUG
	int i,size;
	int	eObjType;

	i = pMsg->msg_type;
	if ((i < 0) || (i >= NUM_MSG_TYPES)) return;
	MsgStats[i].num++;
	size = pMsg->nSize;
	MsgStats[i].bytes += size;
	if (size < MsgStats[i].min ) MsgStats[i].min = size; 
	if (size > MsgStats[i].max ) MsgStats[i].max = size; 

	eObjType = OBJTYPE(pMsg->nUniqueID);
 	if ((eObjType < 0) || (eObjType >= ARMY_LAST_LEGION)) return;
	MsgItemStats[eObjType].num++;
	size = pMsg->nSize;
	MsgItemStats[eObjType].bytes += size;
	if (size < MsgItemStats[eObjType].min ) MsgItemStats[eObjType].min = size; 
	if (size > MsgItemStats[eObjType].max ) MsgItemStats[eObjType].max = size; 

#endif
}

