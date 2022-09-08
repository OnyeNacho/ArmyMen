//========================================================================
//	FILE:			$Workfile: UnitMsg.cpp $
//
//	DESCRIPTION:	Unit messaging routines.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Thursday, November 21, 1996
//
//	REVISION:		$Header: /ArmyMen/src/UnitMsg.cpp 76    4/17/98 6:56a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996, 1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/UnitMsg.cpp $
//  
//  76    4/17/98 6:56a Bwilcox
//  putting messageing traces under debugcomm control to reduce noise
//  
//  75    4/14/98 6:02p Dmaynard
//  changed constants in table of distance trooper must move to send update
//  message, reduced 3 player to 16 pixels, 2 player to 8 pixels
//  
//  74    4/14/98 5:00p Dmaynard
//  Made number of pixels a trooper must move before sending an update
//  message a function of the number of players in the game.  To limit
//  bandwidth but still get smooth movement with less than 4 players.
//  
//  73    4/08/98 11:29p Dmaynard
//  Store lastSentPosition for each Trooper
//  
//  72    4/08/98 12:24p Bwilcox
//  stagger position updates even wider for troopers
//  
//  71    4/06/98 6:59p Dmaynard
//  Only sending new facing if newfactinf/16 != oldfacing/16
//  
//  70    4/06/98 6:45p Dmaynard
//  Stored Trooper oldfacing. Don't send facing message unless it has
//  changed.
//  
//  69    4/06/98 6:05p Dmaynard
//  Instrumenting types of UnitUpdateMessageSends
//  
//  67    4/02/98 6:29p Phu
//  typecast to avoid warnings
//  
//  66    4/01/98 1:20p Bwilcox
//  change tests from army_player to local army
//  
//  65    3/29/98 3:54p Dmaynard
//  Changed the trooper id mask from 0x03 to 0x07 in TrooperUpdateMessage
//  and TrooperUpdateMessageRecieve. Fixes bug of bad placement of fifth
//  trooper on remote machines.
//  
//  64    3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  63    3/19/98 1:20p Bwilcox
//  
//  62    3/17/98 10:23a Dmaynard
//  REVERTING to code before changes to lock out certain actions.
//  
//  54    2/27/98 10:08p Bwilcox
//  fixing unitinitaial deploy for vehicles
//  
//  53    2/20/98 4:28p Dmaynard
//  reset oldFireDirection to fireDirection after update message is sent.
//  Same for Fireheight and firedistance.
//  
//  52    2/15/98 7:10p Bwilcox
//  compacting trooper messages
//  
//  51    2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  50    2/05/98 3:27p Nrobinso
//  fix prototypes
//  
//  49    1/23/98 4:02p Dmaynard
//  Added TRACE for Illegal Deployment.  Looking for a bug where a
//  paratrooper never got deployed on remote machine.
//  
//  48    1/15/98 2:20p Bwilcox
//  convert firedist to unsigned char
//  
//  47    12/24/97 5:10p Bwilcox
//  update messages now sent on change of tile, not change of pixel
//  
//  46    12/18/97 6:42p Bwilcox
//  changed AvatarSetLocation to AvatarSetPosition to change arg to spoint
//  
//  45    12/10/97 2:53p Dmaynard
//  Fixed bug in TrooperDamageMessageSend and Recieve.  There was a
//  secondary UID in the message which was not getting properly transated
//  into Global (color) form and back into index (Local) form.
//  
//  44    12/09/97 12:12p Phu
//  
//
//  $Nokeywords:$
///========================================================================

///========================================================================
// Includes
///========================================================================
#include "stdafx.h"
#include "Army.h"
#include "ArmyMsg.h"
#include "MainFrm.h"
#include "UnitMsg.h"
#include "AiAccess.h"
#include "unit.h"
#include "trooper.h"
#include "vehicle.h"

#include "item.h"
#include "comm.h"

///========================================================================
// Debugging support
///========================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///========================================================================
//					Global Variables
///========================================================================

///========================================================================
//					Local Variables
///========================================================================

///========================================================================
//					Global Prototypes
///========================================================================

///========================================================================
//					LOCAL Prototypes
///========================================================================
static void	UnitDeployMessageReceive( UNITDEPLOY_MESSAGE *pMsg);
static unsigned char*	TrooperUpdateMessageReceive(unsigned char* msg,UNIT* pUnit );
static void	TrooperDamageMessageReceive( TROOPER_DAMAGE_MESSAGE *pMsg );
static void	TrooperDeathMessageReceive( TROOPER_SHORT_MESSAGE *pMsg );
static void	TrooperGoneMessageReceive( TROOPER_SHORT_MESSAGE *pMsg );
static void	UnitVehicleMessageReceive(UNIT_VEHICLE_MESSAGE *pMsg);
static void	UnitUpdateMessageReceive(ARMY_MESSAGE *msg );
///========================================================================
//					     Code
///========================================================================


///========================================================================
//	Function:		TrooperUpdateMessage
//	Description:	Describing the current Trooper status for remote others
///========================================================================

//   temp counters for instrumenting UnitUpdate Message

long tumstotal = 0;
long tumsposition = 0;
long tumsfacing = 0;
long tumsfiring = 0;
long tumsaction = 0;
static int sendwhen[] = { 8, 8, 8, 16, 24 };

void	TrooperUpdateMessage(ARMY_MESSAGE *msg, TROOPER* pTrooper )
{
    char* tmsg = (char*) msg + msg->nSize; // start of free message area
    char* hold = tmsg;
	BOOL  willsend = FALSE;
	int   np = gpComm->m_NumDPPlayers;
    ASSERT((ITEM_UID(pTrooper) & 0x07) < 8);
    char id = ITEM_UID(pTrooper) & 0x07;  // 0 ... 7 troopers in a unit
        // id uses 3 bits to identify trooper.
        // and 5 to designate what data has been shipped

	int x,y;
	x = pTrooper->common.position.x - pTrooper->lastSentPosition.x;
	y = pTrooper->common.position.y - pTrooper->lastSentPosition.y;
	if (x < 0) x = -x;
	if (y < 0) y = -y;

    // write out location change
    // if (pTrooper->common.oldTile != pTrooper->common.tile)
	if (x > sendwhen[np] || y > sendwhen[np] ) // tile and a half change
    {
        id |= 0x80; // position update
        *++tmsg = (pTrooper->common.position.x >> 8);
        *++tmsg = (pTrooper->common.position.x & 0x00ff);
        *++tmsg = (pTrooper->common.position.y >> 8);
        *++tmsg = (pTrooper->common.position.y & 0x00ff);
		pTrooper->lastSentPosition = pTrooper->common.position;
		willsend = TRUE;
		tumsposition++;
    }
    if ((pTrooper->common.oldFacing>>4) != (pTrooper->common.facing>>4))
    {
        id |= 0x40; // facing update
        *++tmsg = (char)(pTrooper->common.facing);
		pTrooper->common.oldFacing = pTrooper->common.facing;
		willsend = TRUE;
		tumsfacing++;
    }
    if ((pTrooper->oldFireDistance>>4) != (pTrooper->common.fireDistance)>>4 ||
        pTrooper->oldFireHeight != pTrooper->fireHeight || 
		pTrooper->oldFireDirection != pTrooper->common.fireDirection ||
		pTrooper->poseDuringRound != pTrooper->oldPoseDuringRound)
    {
        id |= 0x08; // firedistance/height change
        *++tmsg = (pTrooper->common.fireDistance+15) >> 4;
        *++tmsg = pTrooper->fireHeight;
        *++tmsg = pTrooper->common.fireDirection;
		*++tmsg = pTrooper->poseDuringRound;
		pTrooper->oldFireHeight = pTrooper->fireHeight;
		pTrooper->oldFireDistance = pTrooper->common.fireDistance;
		pTrooper->oldFireDirection = pTrooper->common.fireDirection;
		pTrooper->oldPoseDuringRound = pTrooper->poseDuringRound;
		willsend = TRUE;
 		tumsfiring++;
	}
     if (pTrooper->oldAction != pTrooper->action)
    {
        id |= 0x20; // action update
        *++tmsg = pTrooper->action;
		willsend = TRUE;
		tumsaction++;
    }
   if (tmsg != hold)
    {
        *hold = id;
        msg->nSize +=  (tmsg - hold) + 1;
    }
    if( willsend) tumstotal++;
}

///========================================================================
//	Function:		UnitVehicleMessageSend()
//	Description:	Unit going in or out of a vehicle
///========================================================================

void	UnitVehicleMessageSend(UNIT* pUnit, VEHICLE* pVehicle, BOOL bEnter)
{
	UNIT_VEHICLE_MESSAGE	msg;

	// build the message
	msg.nSize            = sizeof(UNIT_VEHICLE_MESSAGE);
	msg.msg_type         = UNIT_CHANGING_VEHICLE_MESSAGE;
	msg.nUniqueID        = ITEM_UID(pUnit);
	if (pVehicle) msg.nVehicleIDFrag = ITEM_UID(pVehicle) & (-1 ^ AI_ID_ARMY_MASK);
	msg.bEnter	 	     = bEnter;
	msg.position		 = pUnit->common.position;
	msg.facing			 = (BYTE)pUnit->common.facing;
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
    if (gpComm->debugComm) TRACE("sending unit vehicle message\n");
}

///========================================================================
//	Function:		UnitDeployMessageSend()
//	Description:	Describe deployment of a unit
///========================================================================

void	UnitDeployMessageSend( UNIT* pUnit )
{
	UNITDEPLOY_MESSAGE	Umsg;

  	Umsg.nSize      = sizeof(UNITDEPLOY_MESSAGE);
	Umsg.nUniqueID  = ITEM_UID(pUnit);
	Umsg.msg_type   = UNIT_DEPLOY_MESSAGE;
	Umsg.position.x = pUnit->common.position.x;
	Umsg.position.y = pUnit->common.position.y;
    Umsg.facing 	= pUnit->common.facing;
     if (gpComm->debugComm) TRACE("Send %s deploy message at %d %d \n", ItemDBName(pUnit),Umsg.position.x,Umsg.position.y);
	ArmyMessageSend((ARMY_MESSAGE *) &Umsg);

}

///========================================================================
//	Function:		TrooperDamageMessageSend()
//	Description:	Sends a message to another player describing damage done
///========================================================================

void	TrooperDamageMessageSend(TROOPER* pTrooper, int damagetodo, int damagetype, SPOINT *damageloc,UID fromUID)
{
	TROOPER_DAMAGE_MESSAGE	msg;

	// build the message
	msg.nSize            = sizeof(TROOPER_DAMAGE_MESSAGE);
	msg.msg_type         = DAMAGE_MESSAGE;
	msg.nUniqueID        = ITEM_UID(pTrooper);
	msg.damagetodo       = damagetodo;
	msg.damagetype       = damagetype;
	msg.x                = damageloc->x;
	msg.y                = damageloc->y;
    msg.fromUID			 = gpComm->GlobalUID(fromUID);
	 if (gpComm->debugComm) TRACE("Sending damage to %s\n",ItemDBName(pTrooper));
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}


///========================================================================
//	Function:		TrooperUpdateMessageReceive(
//	Description:	receive message from other players describing their trooper
///========================================================================

static unsigned char*	TrooperUpdateMessageReceive(unsigned char* tmsg,UNIT* pUnit )
{
    TROOPER* found;
    TROOPER* pTrooper = NULL;
    int i;
    unsigned char uid = *tmsg & 0x07;
    unsigned char bits = *tmsg;
    FOR_EACH_TROOPER(pUnit,found,i)
    {
        if ((ITEM_UID(found) & 0x07) == uid)
        {
            pTrooper = found;
            break;
        }
    }
    if (!pTrooper)
    {
        TRACE("unable to find trooper\n");
    }


    if (bits & 0x80) // position update
    {
        SPOINT pos;
        pos.x = *++tmsg << 8;
        pos.x += *++tmsg;
        pos.y = *++tmsg << 8;
        pos.y += *++tmsg;
        // this forces the avatar to be at the correct place regardless
       if (pTrooper)
  		   AvatarSetPosition(pos,TROOPER_AVATAR(pTrooper));
    }
    if (bits & 0x40) // facing update
    {
		int facing = *++tmsg;
        if (pTrooper)
		{
			pTrooper->common.facing =  facing;
			pTrooper->pendingDirection  = pTrooper->common.facing;
		}
    }
    if (bits & 0x10) // firedirection update
    {
		int fdir;
		fdir = *++tmsg;
		if (pTrooper)
		{
		}
    }
    if (bits & 0x08) // firedistance/height/dist/pose change
    {
		int fdist,fheight,firedir,firepose;
		fdist = *++tmsg << 4;
		fheight = *++tmsg;
		firedir = *++tmsg;
		firepose = *++tmsg;
        if (pTrooper)
		{
			pTrooper->common.fireDistance = fdist;
			pTrooper->fireHeight =  fheight;
			pTrooper->common.fireDirection = firedir;
			pTrooper->poseDuringRound = (ACTION) firepose;
		}
    }
    if (bits & 0x20) // action update
    {
		ACTION action = (ACTION) *++tmsg;
       if (pTrooper)
	   {
			pTrooper->pendingAction = action;
		}
    }

    return ++tmsg;
}

///========================================================================
//	Function:		TrooperDamageMessageReceive()
//	Description:	Receive a message from other players
///========================================================================

static void	TrooperDamageMessageReceive(TROOPER_DAMAGE_MESSAGE *pMsg)
{
	TROOPER*	pTrooper;
	SPOINT	pt;
    UID		fromUID;
    // ignore damage messages for any other player
    if (!IS_LOCAL_ARMY(EXTRACT_ARMY(pMsg->nUniqueID))) return;


	ASSERT(OBJTYPE(pMsg->nUniqueID) == ARMY_TROOPER);

	// For now we know we only receive damage message to ourselves
	pt.x = pMsg->x;
	pt.y = pMsg->y;
    fromUID = gpComm->LocalUID(pMsg->fromUID);
	pTrooper = TrooperFind(pMsg->nUniqueID);
    // If he is already dead and buried, no need for further damage
	if (pTrooper == NULL) return;
	TrooperDamage( pTrooper, pMsg->damagetodo, pMsg->damagetype, &pt,fromUID);
}

///========================================================================
//	Function:		TrooperDeathMessageSend()
//	Description:	send a death message to other players
///========================================================================

void	TrooperDeathMessageSend( TROOPER* pTrooper )
{
	TROOPER_SHORT_MESSAGE	msg;

	// get the unique ID for this troopers unit
	msg.nSize     = sizeof(TROOPER_SHORT_MESSAGE);
	msg.msg_type  = TROOPER_DEATH_MESSAGE;
	msg.nUniqueID = ITEM_UID(pTrooper);
	 if (gpComm->debugComm) TRACE("   Sending Death Message for Trooper %x \n", msg.nUniqueID); 
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		TrooperGoneMessageSend()
//	Description:	send a removal message to other players
///========================================================================

void	TrooperGoneMessageSend( TROOPER* pTrooper )
{
	TROOPER_SHORT_MESSAGE	msg;

	// get the unique ID for this troopers unit
	msg.nSize     = sizeof(TROOPER_SHORT_MESSAGE);
	msg.msg_type  = TROOPER_GONE_MESSAGE;
	msg.nUniqueID = ITEM_UID(pTrooper);
	 if (gpComm->debugComm) TRACE("   Sending Gone Message for Trooper %x \n", msg.nUniqueID); 
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		TrooperDeathMessageReceive()
//	Description:	Receive a death message from other players
///========================================================================

static void	TrooperDeathMessageReceive( TROOPER_SHORT_MESSAGE *pMsg )
{
	TROOPER*	pTrooper = TrooperFind(pMsg->nUniqueID);
	if (!pTrooper)
	{
		TRACE("Warning, trooper not found in death receive\n");
		return;
	}
    TrooperKill( pTrooper );
}

///========================================================================
//	Function:		UnitVehicleMessageReceive()
//	Description:	recieve units entering and exiting a vehicle
///========================================================================

static void	UnitVehicleMessageReceive(UNIT_VEHICLE_MESSAGE *pMsg)
{
	UNIT*	pUnit;
    VEHICLE* pVehicle;
	ASSERT(OBJTYPE(pMsg->nUniqueID) == ARMY_UNIT);
    if (gpComm->debugComm)  TRACE("receiving unit vehicle message\n");
	pUnit = UnitFind(pMsg->nUniqueID);
    if (!pUnit) return;

    // enter the vehicle
    if (pMsg->bEnter)
    {
        // Unit can only enter his own vehicle
        pMsg->nVehicleIDFrag |= AI_ID_ARMY_MASK & ITEM_UID(pUnit);
        pVehicle = VehicleFind(pMsg->nVehicleIDFrag);
        if (!pVehicle) return; 
		if (pVehicle->state == VEHICLE_UNDEPLOYED)
			VehicleDeploy(pVehicle, &pMsg->position, pMsg->facing);

        UnitEnterVehicle( pUnit, pVehicle);
    }
    // exit the vehicle
    else UnitExitVehicle(pUnit, pMsg->position, pMsg->facing);
}

///========================================================================
//	Function:		TroopGoneMessageReceive()
//	Description:	Receive a gone message from other players
///========================================================================

static void	TrooperGoneMessageReceive( TROOPER_SHORT_MESSAGE *pMsg )
{
	TROOPER*	pTrooper = TrooperFind(pMsg->nUniqueID);
	if (!pTrooper)
	{
		TRACE("Warning, trooper not found in gone receive\n");
		return;
	}
    
	TrooperGone( pTrooper );
}

///========================================================================
//	Function:		TrooperMessageReceive()
//	Description: 	Dispatch Unit/Troop messages
///========================================================================

void	TrooperMessageReceive( ARMY_MESSAGE *pMsg,int army_index )	{

	switch (pMsg->msg_type)	{
		case DAMAGE_MESSAGE:
			TrooperDamageMessageReceive((TROOPER_DAMAGE_MESSAGE*)pMsg);
			break;
		case TROOPER_DEATH_MESSAGE:
			TrooperDeathMessageReceive((TROOPER_SHORT_MESSAGE*)pMsg);
			break;
		case TROOPER_GONE_MESSAGE:
			TrooperGoneMessageReceive((TROOPER_SHORT_MESSAGE*)pMsg);
			break;
		default:
			TRACE("Unknown Troop Message type %d Received\n",pMsg->msg_type);
			break;
	}
}

///========================================================================
//	Function:		UnitMessageReceive()
//	Description: 	Dispatch Unit messages
///========================================================================

void	UnitMessageReceive( ARMY_MESSAGE *pMsg,int army_index, DWORD seq )	{

	switch (pMsg->msg_type)	{
        case UPDATE_MESSAGE:
            UnitUpdateMessageReceive(pMsg);
            break;
		case UNIT_DEPLOY_MESSAGE:
			UnitDeployMessageReceive((UNITDEPLOY_MESSAGE*)pMsg);
			break;
		case UNIT_CHANGING_VEHICLE_MESSAGE:
			UnitVehicleMessageReceive((UNIT_VEHICLE_MESSAGE*)pMsg);
			break;
		default:
			TRACE("Unknown Unit Message type %d Received\n", pMsg->msg_type);
			break;
	}
}

static void	UnitDeployMessageReceive( UNITDEPLOY_MESSAGE *pMsg)
{
    UNIT* 			pUnit;
	int				nID = pMsg->nUniqueID;
	ASSERT(OBJTYPE(nID) == ARMY_UNIT);
    pUnit = UnitFind(nID );
	if (!pUnit)
	{
		TRACE("Warning, unit not found in deploy receive\n");
		return;
	}
    if (gpComm->debugComm) TRACE("Receive %s deploy message at %d %d \n", ItemDBName(pUnit),pMsg->position.x,pMsg->position.y);
   UnitInitialDeploy(pUnit,pMsg->position,pMsg->facing,DEFENDFIRE);
}

///========================================================================
//			Network messaging
///=======================================================================

void	UnitSendPending( UNIT *pUnit )
{
    // only send main player 
    if (!IS_LOCAL_ITEM(pUnit) ) return;

    // create a variably sized unit update message
    char message[200];
    ARMY_MESSAGE* msg = (ARMY_MESSAGE*)message;
    msg->nSize = sizeof(ARMY_MESSAGE);
    msg->nUniqueID = ITEM_UID(pUnit);
    msg->msg_type = UPDATE_MESSAGE;

	TROOPER*	pTrooper;
    // someday we may run ai also on a machine over network

	// first see if the troopers have pending messages
    int i;
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
	{
         TrooperUpdateMessage(msg, pTrooper );
	}

    if (msg->nSize == sizeof(ARMY_MESSAGE)) return;  // no change happened

	ArmyMessageSend(msg);
}
     
static void	UnitUpdateMessageReceive(ARMY_MESSAGE *msg )
{
    UNIT* 			pUnit;
	int				nID = msg->nUniqueID;
	ASSERT(OBJTYPE(nID) == ARMY_UNIT);
    pUnit = UnitFind(nID );
	if (!pUnit)
	{
		TRACE("Warning, unit not found in update receive\n");
		return;
	}    

    int n = msg->nSize - sizeof(ARMY_MESSAGE);
    // while we have trooper data to absorb
    unsigned char* tmsg = (unsigned char*) msg + sizeof(ARMY_MESSAGE); // start of data
    unsigned char *endmsg = (unsigned char*)msg + msg->nSize;			// end of message
    while (tmsg < endmsg)
    {
        tmsg = TrooperUpdateMessageReceive(tmsg,pUnit);
    }
}
     

//========================================================================
//							EOF
//========================================================================
