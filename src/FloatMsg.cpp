/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: FloatMsg.cpp $
//
//	DESCRIPTION:	Float messaging
//
//	AUTHOR:			David S. Maynard
//
//	CREATED:		Thursday, May 8, 1997
//
//	REVISION:		$Header: /ArmyMen/src/FloatMsg.cpp 9     4/02/98 3:06p Phu $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History

//  5/08/97 5:00p Dmaynard
//  initial checkin
//  
//
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "Army.h"
#include "ArmyMsg.h"
#include "map.h"
#include "object.h"
#include "floatmsg.h"
#include "explosions.h"
#include "damage.h"
#include "snd.h"
#include "AiAccess.h"

/////////////////////////////////////////////////////////////////////////////
// External Variables
/////////////////////////////////////////////////////////////////////////////

extern Map the_map;

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

///========================================================================
//	Function:		FloatExplosionMessageSend()
//
//	Description:
//		Sends a message noting damage to an object
//
//	Input:			x			x position
//					y			y position
//					explosiontype
//
//	Ouput:			none
//
///========================================================================

void	FloatExplosionMessageSend( short x, short y, COMMAND_NUMBERS explosiontype, int delay, ULONG audioID )
{
	FLOAT_MESSAGE msg;
	long nUniqueID;
	nUniqueID = AiRequestUniqueID( 0 /*eArmy */, ARMY_FLOAT,ARMY_EXPLOSION_FLOAT, 0 );

	msg.nSize=sizeof(FLOAT_MESSAGE);
	msg.nUniqueID=nUniqueID;
	msg.msg_type= FLOATMSG_EXPLOSION;

	msg.x=x;
	msg.y=y;
	msg.exptype=explosiontype;
	msg.delay=delay;
	msg.audioID=audioID;
	ArmyMessageSend((ARMY_MESSAGE *) &msg);

}
///========================================================================
//	Function:		FloatExplosionMessageReceive()
//
//	Description:
//		Receives an explosionmessage and deals with it
//
//	Input:			pMsg	pointer to an army message
//
//	Ouput:			none
//
///========================================================================

void FloatExplosionMessageReceive(FLOAT_MESSAGE *pMsg) {
	// TBD: add sound
	DoDelayedExplosion(pMsg->x, pMsg->y, (COMMAND_NUMBERS) pMsg->exptype, NULL, 0, 
				 0, NULL, FALSE, pMsg->delay, 0, pMsg->audioID );
}



///========================================================================
//	Function:		FloatMessageReceive()
//
//	Description:
//		Receives an object damage message and deals with it
//
//	Input:			pArmyMsg	pointer to an army message
//
//	Ouput:			none
//
///========================================================================

void FloatMessageReceive(ARMY_MESSAGE *pArmyMsg)
{
	FLOAT_MESSAGE *pMsg=(FLOAT_MESSAGE*)pArmyMsg;

	int eArmy, eObjType, eSubType1, eSubType2;


	AiDecodeUniqueID( pMsg->nUniqueID, &eArmy, &eObjType, &eSubType1, &eSubType2 );
	ASSERT(eObjType == ARMY_FLOAT);
	switch (eSubType1)	{
		case ARMY_EXPLOSION_FLOAT:
			FloatExplosionMessageReceive(pMsg);
			break;
		default:
			TRACE("Unknown Float Msg %d \n", pMsg->msg_type);
			break;
	}
}
