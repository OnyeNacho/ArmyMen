/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: ObjectMsg.cpp $
//
//	DESCRIPTION:	Object messaging
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Thursday, May 8, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ObjectMsg.cpp 28    4/17/98 12:22p Dmaynard $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History

//  5/08/97 5:00p Awerner
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
#include "objectmsg.h"
#include "damage.h"
#include "AiAccess.h"
#include "weapon.h"
#include "comm.h"
#include "unit.h"   
#include "item.h" 

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////
void ObjectDamageMessageReceive(OBJECT* pObj,OBJECT_MESSAGE *pMsg);
void ObjectRemoveMessageReceive(OBJECT* pObj,OBJECT_MESSAGE *pArmyMsg);
void ObjectPlaceMessageReceive(OBJECT* pObj,OBJECT_MESSAGE *pArmyMsg);
    
///========================================================================
//	Function:		ObjectDamageMessageSend()
//	Description:	Sends a message noting damage to an object
//	Input:			pObj		what object to damage
//					damagetodo	how much damage to do
//					damagetype	what type of damage to do
//					damageloc	precise location of damage
///========================================================================

void	ObjectDamageMessageSend(OBJECT* pObj, int damagetodo, int damagetype, SPOINT damageloc, UID fromUID)
{
	OBJECT_MESSAGE msg;
	msg.nSize=sizeof(OBJECT_MESSAGE);
	msg.nUniqueID = ITEM_UID(pObj);
	msg.msg_type=OBJMSG_DAMAGE;
	msg.damagetodo=damagetodo;
	msg.damagetype=damagetype;
    msg.damagelocation = damageloc;
	if( fromUID )
		msg.fromUID = gpComm->GlobalUID(fromUID);
	else
		msg.fromUID = 0;
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		ObjectRemoveMessageSend()
//	Description:	Hide/delete object from map
///========================================================================

void	ObjectRemoveMessageSend(OBJECT* pObj)
{
	OBJECT_MESSAGE msg;
	msg.nSize = sizeof(OBJECT_MESSAGE);
	msg.nUniqueID = ITEM_UID(pObj);
	msg.msg_type = OBJECT_REMOVE;
    if(gpComm->debugComm) TRACE("    request remove something\n");
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		ObjectPlaceMessageSend()
//	Description:	Put object on map (or move it)
///========================================================================

void	ObjectPlaceMessageSend(OBJECT* pObj)
{
	OBJECT_MESSAGE msg;
	msg.nSize=sizeof(OBJECT_MESSAGE);
	msg.nUniqueID = ITEM_UID(pObj);
    msg.msg_type = OBJECT_PLACE;
    msg.damagelocation = pObj->common.position;
    TRACE("request place or move object\n");

    int eArmy = OBJECT_OWNER(pObj);
    eArmy = gpComm->ColorFromIndex(eArmy); 
    msg.damagetype = eArmy; // global color
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		ObjectDamageMessageReceive()
//	Description:	Receives an object damage message and deals with it
///========================================================================

void ObjectDamageMessageReceive(OBJECT* pObj,OBJECT_MESSAGE *pMsg)
{
	if( pMsg->fromUID )
		ObjectDamage(pObj, pMsg->damagetodo, pMsg->damagetype, pMsg->damagelocation, 
			FALSE, gpComm->LocalUID(pMsg->fromUID) );
	else
		ObjectDamage(pObj, pMsg->damagetodo, pMsg->damagetype, pMsg->damagelocation, 
			FALSE, 0 );
}

///========================================================================
//	Function:		ObjectMessageReceive()
//	Description:	route based on message received
///========================================================================

void ObjectMessageReceive(ARMY_MESSAGE *pArmyMsg)
{
	OBJECT_MESSAGE *pMsg=(OBJECT_MESSAGE*)pArmyMsg;
	OBJECT *pObj;
	pObj = ObjectFind( pMsg->nUniqueID );
	ASSERT(pObj != NULL);
	if (!pObj) return;

    if (pArmyMsg->msg_type == OBJMSG_DAMAGE)
        ObjectDamageMessageReceive(pObj,pMsg);
    else if (pArmyMsg->msg_type == OBJECT_REMOVE)
        ObjectRemoveMessageReceive(pObj,pMsg);           
    else if (pArmyMsg->msg_type == OBJECT_PLACE)
        ObjectPlaceMessageReceive(pObj,pMsg);           
}

///========================================================================
//	Function:		ObjectRemoveMessageReceive()
//	Description:	remove object from map
///========================================================================


void ObjectRemoveMessageReceive(OBJECT* pObj,OBJECT_MESSAGE *pMsg)
{
	if (pObj->category == EXPLOSIVES && pObj->number == ARMY_MINE)
	{
		RawUnplaceMine(pObj);
		TRACE("removing mine\n");
	}
    else
    {
		TRACE("removing object\n");
        ScriptRemoveObject(ITEM_UID(pObj));
    }
}

///========================================================================
//	Function:		ObjectPlaceMessageReceive()
//	Description:	Place object on map
///========================================================================

void ObjectPlaceMessageReceive(OBJECT* pObj,OBJECT_MESSAGE *pMsg)
{
	if (pObj->category == EXPLOSIVES &&  pObj->number == ARMY_MINE)
    {
        int eArmy = pMsg->damagetype; // global color
        eArmy = gpComm->IndexFromColor((ARMY_COLOR)eArmy);  // local color
        if (IS_LOCAL_ARMY(eArmy))  return; // we already placed this
		PutMine(pObj,pMsg->damagelocation,eArmy);
		TRACE("placing mine of (global %d) => (%d local)\n",
            pMsg->damagetype,eArmy);
    }

    // moving an object already placed to some other place
    else if (pObj && pObj->common.tile)
    {
        TRACE("moving object\n");
        MapRemoveObject(pObj);
        MapPlaceObject(pObj,&pMsg->damagelocation);
    }
}
