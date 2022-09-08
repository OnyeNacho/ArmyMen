//========================================================================
//	FILE:			$Workfile: SargeMsg.cpp $
//
//	DESCRIPTION:	Sarge messaging routines.
//
//	AUTHOR:			David S. Maynard
//
//	CREATED:		Tuesday, July 30, 1997
//
//	REVISION:		$Header: /ArmyMen/src/SargeMsg.cpp 80    4/17/98 6:55a Bwilcox $
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
//  $Log: /ArmyMen/src/SargeMsg.cpp $
//  
//  80    4/17/98 6:55a Bwilcox
//  putting messageing traces under debugcomm control to reduce noise
//  
//  78    4/02/98 3:21p Phu
//  typecast to avoid warnings
//  
//  77    4/01/98 1:23p Bwilcox
//  change local test
//  
//  76    3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  75    3/26/98 10:52a Nrobinso
//  fix warning
//  
//  74    3/26/98 9:20a Bwilcox
//  
//  73    3/26/98 9:15a Bwilcox
//  
//  72    3/26/98 8:55a Bwilcox
//  fixing sarge moving after death
//  
//  71    3/26/98 8:34a Bwilcox
//  improved sarge dying trace and passing position of death
//  
//  70    3/25/98 9:16a Bwilcox
//  fireweapon lock on remote
//  
//  69    3/25/98 9:07a Bwilcox
//  
//  68    3/25/98 9:04a Bwilcox
//  add fireindex
//  
//  67    3/24/98 6:38p Dmaynard
//  lets send sarge strength
//  
//  66    3/24/98 6:22p Dmaynard
//  Changed SargeUpdateMessageSend to just reurn if Sarge is dead rather
//  than setting his strenght to 1.
//  
//  65    3/17/98 6:17p Bwilcox
//  sargefind may now safely return null
//  
//  64    3/16/98 2:14p Bwilcox
//  fixed para count, send oldposition with sargeupdate
//  
//  63    2/27/98 1:18p Bwilcox
//  cleaning up the air, supporting script airdrops for foes,e tc
//  
//  62    2/13/98 7:00p Phu
//  
//  61    2/09/98 10:35a Nrobinso
//  added index trace msg to death
//  
//  60    2/09/98 10:26a Nrobinso
//  fix death trace msg
//  
//  59    2/06/98 12:57p Phu
//  decrement airsupport of non-local players when usage message is
//  received
//  
//  58    2/06/98 10:48a Bwilcox
//  pass non-zero sarge strength along so medpak works
//  
//  57    2/04/98 5:55p Nrobinso
//  change passing of sarge killed by army to correspond to trooper
//  
//  56    2/03/98 11:24a Nrobinso
//  fix firing bar stay up; make local & remote call a common routine to
//  set sarge's anim
//  
//  55    98/01/26 17:31 Dmaynard
//  
//  54    98/01/26 17:19 Dmaynard
//  
//  53    98/01/26 17:03 Dmaynard
//  fix frag count to translate to index from color
//  
//  52    98/01/26 16:44 Dmaynard
//  translate killerarmy from color to index in sargemsg
//  
//  51    98/01/26 16:23 Dmaynard
//  
//  50    1/26/98 11:27a Phu
//  parachutists
//  
//  49    1/17/98 11:48p Bwilcox
//  drop fixed
//  
//  48    1/15/98 2:20p Bwilcox
//  convert firedist to unsigned char
//  
//  47    98/01/14 18:02 Dmaynard
//  fixed drop timing order
//  
//  46    1/14/98 1:28p Bwilcox
//  assert if own sarge receives inappropirate messages
//  
//  45    1/13/98 9:36p Bwilcox
//  ammo count put on drop, pickup and weapon dropped when empty
//  
//  44    98/01/13 19:29 Dmaynard
//  assert if sarge bad on location and strength
//  
//  43    98/01/13 10:03 Dmaynard
//  assert if illegal item position for sarge
//  
//  42    1/08/98 4:19p Phu
//  air support items/paratrooper initialization
//  
//  41    1/08/98 1:52p Phu
//  mp airsupport
//  
//  40    1/08/98 12:26p Dmaynard
//  Fixed bug in SargeUpdateSend   added a forceSend parameter.  An update
//  wasn't getting sent if Sarge hadn't moved.  The problem is that he had
//  changed selected weapon.  As a result remote computers had wrong weapon
//  selected which led to ammo count discrepancies.
//  
//  
//  39    12/24/97 5:09p Bwilcox
//  update messages now sent on change of tile, not change of pixel
//  
//  38    12/19/97 2:08p Bwilcox
//  more epoint to spoint conversion
//  
//  37    12/18/97 6:40p Bwilcox
//  changed AvatarSetLocation to AvatarSetPosition to change arg to spoint
//  
//  36    12/17/97 5:53p Dmaynard
//  Test whether Sarge has an Avatar before setting the Avatar's location
//  is SargeUpdateMessageReceived.  (If he is being ressurected he may not
//  have an Avatar).
//  
//  35    12/15/97 12:01p Dmaynard
//  added weapon_index (currently selected weapon) to the
//  SargeUpdateMessage data structure so that remote Sarges will fire the
//  proper weapons.
//  
//  34    97/12/11 13:52 Dmaynard
//  fixed remote sarge (blast desiredDirection from pendingDriection)
//  
//  33    97/12/10 15:25 Dmaynard
//  encode/decode of damager
//  
//  32    12/09/97 12:12p Phu
//  
//  31    11/20/97 1:52p Bwilcox
//  adjusting resurrection of sarge and vechile
//  
//  30    11/18/97 6:05p Bwilcox
//  
//  29    11/18/97 5:43p Bwilcox
//  fixing remote drop
//  
//  28    11/18/97 4:31p Bwilcox
//  
//  27    11/18/97 4:10p Bwilcox
//  fixing pickup to be done by host
//  
//  26    97/11/18 14:53 Dmaynard
//  Commented out actual network send in SargeWantItemMessageSend.   To Try
//  letting host just arbitrate pick-ups and drops.
//  
//  25    11/18/97 2:18p Dmaynard
//  GlobalUID and LocalUID functions added
//  
//  24    11/18/97 1:51p Bwilcox
//  drop across the net code and pickup too.
//  
//  23    11/17/97 3:27a Bwilcox
//  sarge deploy/undeploy across the net
//  
//  22    11/16/97 11:58p Bwilcox
//  passing along who killed the sarge (which army)
//  
//  21    10/24/97 6:35p Bwilcox
//  fixed recursive net damage
//  
//  20    10/24/97 10:10a Bwilcox
//  fixed bug in vehcile id
//  
//  19    10/24/97 9:10a Bwilcox
//  cleaning up messages and doing unit into vehcle
//  
//  18    10/15/97 5:05p Nrobinso
//  all deploys now consistent; SargeCreate only takes an army designator
//  
//  16    9/09/97 9:26a Nrobinso
//  pass vehicle position and facing with message in which sarge gets into
//  a vehicle
//  
//  15    8/27/97 6:10p Dmaynard
//  In SargeVehicleMessageReceive we have to SWAP the ARMYPLAYER field in
//  the nVehicleID.
//  
//  14    8/27/97 5:05p Dmaynard
//  Temporary Hack to call VehicleCompleteDeploy from SargeVehicleReceive
//  if the vehicle is currently in an Undeployed state.. We should probably
//  go back to sending a vehicleDeploy message any time a vehicle is
//  deployed.  
//  
//  13    8/25/97 3:08p Bwilcox
//  SargeVehicleMessages for entering and exiting vehicles across net added
//  
//  12    8/21/97 6:49p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  11    8/17/97 7:15p Nrobinso
//  minimize message data
//  
//  10    8/16/97 3:05p Nrobinso
//  revamp fire weapon system
//  
//  9     8/16/97 10:54a Bwilcox
//  
//  8     97-08-15 20:46 Dmaynard
//  
//  7     8/15/97 8:38p Bwilcox
//  sarge death throes split into 2 net messages
//  
//  6     8/15/97 7:28p Dmaynard
//  Added dispatch call for SargeDeathMessageReceive in SargeMessageReceive
//  
//  5     8/15/97 1:02p Bwilcox
//  added current action/direction for proper maintenance of sarge and
//  trooper across net
//  
//  4     8/14/97 5:54p Dmaynard
//  Changed SargeDie from Static to not static
//  
//  3     8/07/97 11:53p Nrobinso
//  moved globals.h to stdafx.h
//  
//  2     8/07/97 11:21p Nrobinso
//  removed percent data from damage messages
//  
//  1     7/30/97 7:03p Dmaynard
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
#include "comm.h"
#include "trooper.h"
#include "Sarge.h"
#include "sargep.h"
#include "SargeMsg.h"
#include "vehicle.h"
#include "item.h"
#include "air.h"

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
static void	SargeUpdateMessageReceive( SARGE_MESSAGE *pSmsg );
static void	SargeDamageMessageReceive( SARGE_DAMAGE_MESSAGE *pSMsg );
static void	SargeDeathMessageReceive( SARGE_DIE_MESSAGE *pSMsg );
static void	SargeVehicleMessageReceive( SARGE_SHORT_MESSAGE *pSMsg );
static void	SargeGoneMessageReceive( SARGE_SHORT_MESSAGE *pSMsg );

///========================================================================
//					     Code
///========================================================================


///========================================================================
//	Function:		SargeUpdateMessageSend()
//	Description:	Tell others about Sarge status
///========================================================================

void	SargeUpdateMessageSend( SARGE* pSarge , BOOL forceSend)
{
	SARGE_MESSAGE	Smsg;

    // if sarge has changed stay here, else return
    if (forceSend);
	else if (pSarge->common.oldTile != pSarge->common.tile);
    else if (pSarge->common.oldFacing != pSarge->common.facing);
    else if (pSarge->oldAction != pSarge->action);
    else if (pSarge->oldDirection != pSarge->direction);
    else return;

  	Smsg.nSize      = sizeof(SARGE_MESSAGE);
	Smsg.nUniqueID  = ITEM_UID(pSarge);
	Smsg.msg_type   = SARGETYPE_MESSAGE;
	if ( !pSarge->common.nStrength ) return;  // No one cares about a dead sarge anyway
    Smsg.strength =  pSarge->common.nStrength;
	ASSERT(pSarge->common.position.x);
    // send the starting position for the avatar command, not the resulting one
	Smsg.position   = pSarge->common.oldPosition;
    Smsg.pendingAction = pSarge->pendingAction;
    Smsg.pendingDirection = pSarge->pendingDirection;
    Smsg.fireDistance = (pSarge->common.fireDistance+15) >> 4;
    Smsg.fireDirection = pSarge->common.fireDirection;
    Smsg.fireIndex = pSarge->fireIndex;
    Smsg.weaponIndex = pSarge->weapon_index;

	ArmyMessageSend((ARMY_MESSAGE *) &Smsg);

}

///========================================================================
//	Function:		SARGEDamageMessageSend()
//	Description:	Tell other player his sarge got hit
///========================================================================

void	SargeDamageMessageSend(SARGE *pSarge, int damagetodo, int damagetype, SPOINT *damageloc,UID fromUID)
{
	SARGE_DAMAGE_MESSAGE	msg;

	// build the message
	msg.nSize            = sizeof(SARGE_DAMAGE_MESSAGE);
	msg.msg_type         = DAMAGE_MESSAGE;
	msg.nUniqueID        = ITEM_UID(pSarge);
	msg.damagetodo       = damagetodo;
	msg.damagetype       = damagetype;
	msg.x                = damageloc->x;
	msg.y                = damageloc->y;
    msg.fromUID		 	 = gpComm->GlobalUID(fromUID);	

	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}


///========================================================================
//	Function:		SargeVehicleMessageSend()
//	Description:	Tell other players Sarge going in or out of a vehicle
//                  or is deploying or undeploying
///========================================================================

void	SargeVehicleMessageSend(SARGE *pSarge,VEHICLE* pVehicle, BOOL bEnter)
{
    UID nVehicleIDFrag;
	SARGE_VEHICLE_MESSAGE	msg;
    // send uid without army (it must be my army)
    if (pVehicle) nVehicleIDFrag = ITEM_UID(pVehicle) & (-1 ^ AI_ID_ARMY_MASK);

	// build the message
	msg.nSize            = sizeof(SARGE_VEHICLE_MESSAGE);
	msg.msg_type         = SARGE_CHANGING_VEHICLE_MESSAGE;
	msg.nUniqueID        = ITEM_UID(pSarge);
	msg.nVehicleIDFrag   = nVehicleIDFrag;
	msg.bEnter	 	     = bEnter;
	msg.position		 = pSarge->common.position;
	msg.facing			 = (BYTE)pSarge->common.facing;
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}


///========================================================================
//	Function:		SargeUpdateMessageReceive()
//	Description:	receive message from other players describing their sarge
///========================================================================

static void	SargeUpdateMessageReceive( SARGE_MESSAGE *pSmsg )
{
	SARGE*	pSarge;
	WEAPON* pWeapon;
	int		nID = pSmsg->nUniqueID;

	ASSERT(OBJTYPE(nID) == ARMY_SARGE);
    pSarge = SargeFind(nID );
    if (!pSarge) return;
    ASSERT(!IS_LOCAL_ITEM(pSarge));
    
    // this forces the avatar to be at the correct place regardless
    if( pSarge->pAvatar) AvatarSetPosition(pSmsg->position,pSarge->pAvatar);
  
   // this is what the sarge will do next and which way
    pSarge->pendingDirection  = pSmsg->pendingDirection;
    pSarge->desiredDirection  = pSmsg->pendingDirection;
    pSarge->pendingAction = (ACTION)pSmsg->pendingAction;
    pSarge->common.nStrength = pSmsg->strength;

    pSarge->common.fireDistance = pSmsg->fireDistance << 4;
    pSarge->common.fireDirection = pSmsg->fireDirection;


	// if I had a fireindex before, I must wait until it fires before selecting
	// new one or changing weapon index if I CAN.
	if (pSarge->fireIndex) // see if my weapon is still there
	{
		// the current weapon is no longer correct. Must have been dropped by remote
		if (pSarge->common.pWeapon->eWeapon != pSarge->fireIndex)
			pSarge->fireIndex = 0;
	}
    
	if (!pSarge->fireIndex) 
	{
		pSarge->fireIndex = pSmsg->fireIndex;

		if(pSarge->weapon_index != pSmsg->weaponIndex) {
			pWeapon = pSarge->pWeaponList[pSmsg->weaponIndex];
			if (pWeapon && pSarge->pAvatar)	{
				pSarge->weapon_index = pSmsg->weaponIndex;
				pSarge->common.pWeapon = pWeapon;
				SetSargeAnimType(pSarge);
			}
		}
	}
}

///========================================================================
//	Function:		SargeDamageMessageReceive()
//	Description:	Receive a message  describing my sarge being damaged
///========================================================================

static void	SargeDamageMessageReceive(SARGE_DAMAGE_MESSAGE *pSMsg)
{
	SARGE*	pSarge;
	SPOINT	pt;
    UID		fromUID;

    // ignore damage messages for any other player
    if (!IS_LOCAL_ARMY(EXTRACT_ARMY(pSMsg->nUniqueID))) return;

	ASSERT(OBJTYPE(pSMsg->nUniqueID) == ARMY_SARGE);

	// For now we know we only receive damage message to ourselves
	pt.x = pSMsg->x;
	pt.y = pSMsg->y;
    fromUID = gpComm->LocalUID(pSMsg->fromUID);
	pSarge = SargeFind(pSMsg->nUniqueID);
    if (!pSarge) return;
    SargeDamage( pSarge, pSMsg->damagetodo, pSMsg->damagetype, &pt,fromUID);
}

///========================================================================
//	Function:		SargeVehicleMessageReceive()
//	Description:	Receive a message about some sarge entering/exiting vehicle
//					Or deploying or undeploying        
///========================================================================

static void	SargeVehicleMessageReceive(SARGE_VEHICLE_MESSAGE *pSMsg)
{
	SARGE*	pSarge;
    VEHICLE* pVehicle;
	ASSERT(OBJTYPE(pSMsg->nUniqueID) == ARMY_SARGE);
	pSarge = SargeFind(pSMsg->nUniqueID);
    if (!pSarge) return;
    ASSERT(!IS_LOCAL_ITEM(pSarge));

    // enter the vehicle
    if (pSMsg->bEnter == 1)
    {
        // sarge can only enter his own vehicle
        pSMsg->nVehicleIDFrag |= AI_ID_ARMY_MASK & ITEM_UID(pSarge);
        pVehicle = VehicleFind(pSMsg->nVehicleIDFrag);
        if (!pVehicle) return; 
		if (pVehicle->state == VEHICLE_UNDEPLOYED)
			VehicleDeploy(pVehicle, &pSMsg->position, pSMsg->facing);

        SargeInVehicle( pSarge, pVehicle);
    }
    // deploy
    else if (pSMsg->bEnter == 2)
    {
        SargeInitialDeploy(pSarge,&pSMsg->position,0);
    }
    // undeploy
    else if (pSMsg->bEnter == 3)
    {
        SargeUndeploy(ITEM_ARMY(pSarge));
    }
    // exit the vehicle
    else if (pSMsg->bEnter == 0) SargeOutVehicle(pSarge);
}

///========================================================================
//	Function:		SargeWantItemMessageSend()
//	Description:	send a request to host for item
///========================================================================
// ask host to drop something we hold

void	SargeWantItemMessageSend( SARGE* pSarge,ITEM* pItem,
                                  REQUEST pickup,SARGE_WEAPON slot)
{
    SARGE_ITEM_MESSAGE Smsg;
  	Smsg.nSize      = sizeof(SARGE_ITEM_MESSAGE);
	Smsg.nUniqueID  = ITEM_UID(pSarge);
	Smsg.msg_type   = WANT_ITEM_MESSAGE;
    Smsg.uid	    = gpComm->GlobalUID((LONG)ITEM_UID(pItem));
    Smsg.position 	= pItem->position;
    Smsg.pickup 	= pickup;
    Smsg.slot 		= (int) slot;
    Smsg.ammo		= pItem->pWeapon->nAmmo;
	ASSERT(pItem->position.x && pItem->position.y);
	ArmyMessageSend((ARMY_MESSAGE *) &Smsg);
	if (!gpComm->debugComm) ;
    else if (pickup == WANT_PICKUP)
        TRACE("Request pickup item %x ammo %d\n",ITEM_UID(pItem),Smsg.ammo);
    else if (pickup == WANT_DROP)
        TRACE("Request Drop item%x ammo %d \n",ITEM_UID(pItem),Smsg.ammo);
    else if (pickup == DO_PICKUP)
        TRACE("Tell pickup item%x ammo %d\n",ITEM_UID(pItem),Smsg.ammo);
    else if (pickup == DO_DROP)
        TRACE("Tell Drop item%x ammo %d\n",ITEM_UID(pItem),Smsg.ammo);
}

///========================================================================
//	Function:		SargeWantItemMessageReceive()
//	Description:	
///========================================================================
static void	SargeWantItemMessageReceive( SARGE_ITEM_MESSAGE *pSMsg )
// send a drop request to host
{
    // only host can receive these
    if (!gpComm->m_bHost)
    {
        if (pSMsg->pickup == WANT_PICKUP) return;
        else if (pSMsg->pickup == WANT_DROP) return;
    }
	ASSERT(pSMsg->position.x && pSMsg->position.y);

	SARGE*	pSarge = SargeFind(pSMsg->nUniqueID);    
    if (!pSarge) return;
    
    ITEM* pItem;
    LONG id;
    id = gpComm->LocalUID((LONG)pSMsg->uid);
    pItem = AiItemFind(id);
    if (!pItem)
    {
        TRACE("Error- item not found for request\n");
        return;
    }

    // update item position from incoming request
    ItemSetLocation(pItem,&pSMsg->position);
        
    // make it correct from message
    pItem->pWeapon->nAmmo = pSMsg->ammo;
    SARGE_WEAPON slot;
    slot = WeaponSlot(pItem);

    if (pSMsg->pickup == DO_PICKUP)
    {
        ASSERT (!gpComm->m_bHost);
         if (gpComm->debugComm) TRACE("Tell pickup item received ammo %d\n",pSMsg->ammo);
        SargeDoPickupWeapon(pSarge,pItem);
    }

    else if (pSMsg->pickup == DO_DROP)
    {
        ASSERT (!gpComm->m_bHost);
        if (gpComm->debugComm)  TRACE("Tell Drop item received ammo %d\n",pSMsg->ammo);
        SargeDoDropWeapon(pSarge,pSMsg->position,slot);
    }

//    else if (pSMsg->pickup == WANT_PICKUP)
//    {
//        TRACE("Request pickup item received ammo %d\n",pSMsg->ammo);
//        SargeWantItemMessageSend(pSarge,pItem,WANT_PICKUP,slot);        
//   }

    else if (pSMsg->pickup == WANT_DROP)
    {
         if (gpComm->debugComm) TRACE("Request drop item received ammo %d\n",pSMsg->ammo);
        SargeWantItemMessageSend(pSarge,pItem,DO_DROP,slot);        
		SargeDoDropWeapon(pSarge,pSMsg->position,slot);
   }
}

///========================================================================
//	Function:		SargeDeathMessageSend()
//	Description:	send a death message to other players
///========================================================================

void	SargeDeathMessageSend( SARGE* pSarge, int killerArmy )
{
	SARGE_DIE_MESSAGE	msg;
	int killerColor;

	killerColor = PlayerColor((ARMY_TYPE)killerArmy);

	// get the unique ID for this troopers unit
	msg.nSize     = sizeof(SARGE_DIE_MESSAGE);
	msg.msg_type  = SARGE_DEATH_MESSAGE;
	msg.nUniqueID = ITEM_UID(pSarge);
    msg.int_data  = killerColor;//the color of the killer, not the army index
    msg.position = pSarge->common.position;
    msg.howDie = pSarge->pendingAction;
     if (gpComm->debugComm) TRACE("Sending sarge dying at %d.%d: abscolor %d (%d) killed by abscolor %d (%d)\n",
        msg.position.x,msg.position.y,
		gpComm->ColorFromIndex(ITEM_ARMY(pSarge)),
		ITEM_ARMY(pSarge), killerColor, killerArmy );
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		SargeGoneMessageSend()
//	Description:	send a gone message to other players
///========================================================================

void	SargeGoneMessageSend( SARGE* pSarge)
{
	SARGE_SHORT_MESSAGE	msg;
	msg.nSize     = sizeof(SARGE_SHORT_MESSAGE);
	msg.msg_type  = SARGE_GONE_MESSAGE;
	msg.nUniqueID = ITEM_UID(pSarge);
     if (gpComm->debugComm) TRACE("Sending sarge gone %s\n",ItemDBName(pSarge));
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		SargeDeathMessageReceive()
//	Description:	Receive a death message about another player sarge
///========================================================================

static void	SargeDeathMessageReceive( SARGE_DIE_MESSAGE *pSMsg )
{
	int killerColor = pSMsg->int_data;
	int killerArmy;
	SARGE*	pSarge = SargeFind(pSMsg->nUniqueID);
    if (!pSarge) return;
    
     if (gpComm->debugComm) TRACE("Received sarge dying at %d.%d: abscolor %d (%d) killed by abscolor %d\n",
        pSMsg->position.x, pSMsg->position.y,
		gpComm->ColorFromIndex(ITEM_ARMY(pSarge)),
		ITEM_ARMY(pSarge), killerColor );

    ASSERT(!IS_LOCAL_ITEM(pSarge));
	killerArmy = gpComm->IndexFromColor((ARMY_COLOR)killerColor );

    // this forces the avatar to be at the correct place regardless
    if( pSarge->pAvatar) AvatarSetPosition(pSMsg->position,pSarge->pAvatar);
    // this is the way he dies, since no more updates will be sent
    pSarge->pendingAction = pSMsg->howDie;
	SargeDie( pSarge, killerArmy);
}

///========================================================================
//	Function:		SargeGoneMessageReceive()
//	Description:	Receive a gone message about another player sarge
///========================================================================

static void	SargeGoneMessageReceive( SARGE_SHORT_MESSAGE *pSMsg )
{
	SARGE*	pSarge = SargeFind(pSMsg->nUniqueID);
    if (!pSarge) return;
    ASSERT(!IS_LOCAL_ITEM(pSarge));
	 if (gpComm->debugComm) TRACE("received Sarge gone %s\n",ItemDBName(pSarge));
	SargeGone( pSarge);
}


void SargeAirSupportMessageSend( SARGE *pSarge, AIRSUPPORTTYPE type, SPOINT pos )
{
	SARGE_AIRSUPPORT_MESSAGE	msg;
	msg.nSize     = sizeof(SARGE_AIRSUPPORT_MESSAGE);
	msg.msg_type  = AIR_SUPPORT_MESSAGE;
	msg.nUniqueID = ITEM_UID(pSarge);
	msg.airsupportType = type;
	msg.where = pos;
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

void SargeAirSupportMessageReceive( SARGE_AIRSUPPORT_MESSAGE *pSMsg )
{
    int army = EXTRACT_ARMY( pSMsg->nUniqueID );
    DoAirSupport((AIRSUPPORTTYPE)pSMsg->airsupportType,pSMsg->where,army);
}


///========================================================================
//	Function:		SargeMessageReceive()
//	Description: 	Dispatch Sarge messages
///========================================================================

void	SargeMessageReceive( ARMY_MESSAGE *pMsg,int army_index )	{

	switch (pMsg->msg_type)	{
        case WANT_ITEM_MESSAGE:
            SargeWantItemMessageReceive((SARGE_ITEM_MESSAGE*) pMsg);
            break;
        case SARGETYPE_MESSAGE:
			SargeUpdateMessageReceive( (SARGE_MESSAGE*) pMsg );
			break;
        case SARGE_CHANGING_VEHICLE_MESSAGE:
			SargeVehicleMessageReceive((SARGE_VEHICLE_MESSAGE*)pMsg);
			break;
		case DAMAGE_MESSAGE:
			SargeDamageMessageReceive((SARGE_DAMAGE_MESSAGE*)pMsg);
			break;
		case SARGE_DEATH_MESSAGE:
			SargeDeathMessageReceive((SARGE_DIE_MESSAGE*)pMsg);
			break;
		case SARGE_GONE_MESSAGE:
			SargeGoneMessageReceive((SARGE_SHORT_MESSAGE*)pMsg);
			break;
		case AIR_SUPPORT_MESSAGE:
			SargeAirSupportMessageReceive( (SARGE_AIRSUPPORT_MESSAGE*)pMsg );
			break;
		default:
			TRACE("Unknown Sarge Message of type %d Received\n", pMsg->msg_type);
			break;
	}
}

///========================================================================
//			Network messaging
///=======================================================================

    
//========================================================================
//							EOF
//========================================================================
