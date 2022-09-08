/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: ObjectMsg.h $
//
//	DESCRIPTION:	Object messaging interface
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Thursday, May 8, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ObjectMsg.h 9     3/27/98 10:06a Bwilcox $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//	$Log: /ArmyMen/src/ObjectMsg.h $
//  
//  9     3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  8     2/19/98 6:32p Phu
//  send uid with object damage
//  
//  7     2/10/98 11:33a Bwilcox
//  mines are placed by net message object_place, not by local firing.
//  objectdamage now takes spoint instead of spoint *
//  dead field removed from objectmessage
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __OBJECTMSG_H__
#define __OBJECTMSG_H__

#include "ArmyMsg.h"
#include "donottouch.h"

void	ObjectDamageMessageSend(OBJECT* pObj, int damagetodo, int damagetype, SPOINT damageloc, UID fromUID);
void	ObjectRemoveMessageSend(OBJECT *pObj);
void	ObjectPlaceMessageSend(OBJECT *pObj);

void	ObjectMessageReceive(ARMY_MESSAGE *pMsg);

#endif
