/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: VehicleMsg.cpp $
//
//	DESCRIPTION:	Vehicle messaing
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Friday, April 25, 1997
//
//	REVISION:		$Header: /ArmyMen/src/VehicleMsg.cpp 38    4/17/98 6:56a Bwilcox $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/VehicleMsg.cpp $
//  
//  38    4/17/98 6:56a Bwilcox
//  putting messageing traces under debugcomm control to reduce noise
//  
//  36    4/02/98 6:55p Dmaynard
//  VehicleUpdateMessageReceive will now Ignore messages for any vehicle
//  whose state is dying.  Fixes a bug where husks were not created.
//  
//  35    4/02/98 6:29p Phu
//  typecast to avoid warnings
//  
//  34    4/01/98 1:22p Bwilcox
//  change local test
//  
//  33    1/30/98 4:00p Dmaynard
//  Vehicle damage TRACES removed
//  
//  32    12/24/97 5:10p Bwilcox
//  update messages now sent on change of tile, not change of pixel
//  
//  31    12/09/97 12:12p Phu
//  
//  30    11/15/97 8:49a Bwilcox
//  vehicles fixing across net (not perfect yet)
//  
//  29    10/30/97 10:14a Nrobinso
//  trurret_facing becomes gun_facing
//  
//  28    10/24/97 6:35p Bwilcox
//  fixed recursive net damage
//  
//  27    10/24/97 9:10a Bwilcox
//  cleaning up messages and doing unit into vehcle
//  
//  26    10/23/97 4:06p Bwilcox
//  removing dead code relating to units entering vehicles and installing
//  new code
//  
//  25    10/22/97 10:17a Bwilcox
//  remote vehicle deploy, enter and exit of vehicle
//  
//  24    10/21/97 3:59p Bwilcox
//  unitdeploy messaging
//  
//  23    10/21/97 11:03a Awerner
//  Restored screen scrolling following vehicles
//  
//  22    10/15/97 5:03p Nrobinso
//  all deploys now consistent
//  
//  21    10/14/97 1:36p Nrobinso
//  verify vehicle pointer is good
//  
//  19    9/09/97 9:31a Nrobinso
//  VehicleCompleteDeploy takes a position and facing
//  
//  18    8/26/97 4:37p Bwilcox
//  dynamic deploymnet on vehicle update if needed
//  
//  17    8/26/97 2:34p Bwilcox
//  remote vehicle messgaes per vehicle
//  
//  16    8/25/97 3:33p Bwilcox
//  vehicledeploy/undeploy messages removed, code changes around vehicle
//  create.deploy and sarge in vehicle
//  
//  15    8/21/97 6:58p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  14    8/17/97 7:16p Nrobinso
//  minimize message data
//  
//  13    8/07/97 11:54p Nrobinso
//  moved globals.h to stdafx.h
//  
//  12    8/07/97 11:22p Nrobinso
//  removed percent data from damage messages
//  
//  11    8/06/97 9:54a Nrobinso
//  VehicleFire now VehicleFireWeapon; VehicleFireWeapon now properly calls
//  FireWeapon
//  
//  10    8/04/97 7:30a Bwilcox
//  removed active test since vehicle cant do update send if not active
//  
//  9     7/31/97 5:31p Dmaynard
//  Added ITEM_ACTIVE flag to Vehicle 
//  Set in Depploy Cleared in Undeploy and tested in Update
//  
//  8     7/31/97 4:45p Dmaynard
//  don't send vehicle message if inactive
//  
//  7     7/29/97 11:31p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
//  
//  6     7/28/97 7:53p Nrobinso
//  fix spelling of VehicleMessageReceive
//  
//  5     7/19/97 6:31p Bwilcox
//  changed UnitDeployment call
//  
//  4     7/11/97 8:09p Bwilcox
//  
//  3     7/10/97 1:37p Bwilcox
//  cleanups of unit. removal of dead fields in common
//  
//  2     7/03/97 8:37p Bwilcox
//  massive cleanups.
//  
//  28    6/30/97 9:02p Bwilcox
//  moving protos out of army.h into vehicle.h, trooper.h, unit.h 
//  removing dead code and variables.
//  
//  27    6/15/97 9:50a Bwilcox
//  (lastheight+fuel references) removed
//  
//  26    6/14/97 4:38p Nrobinso
//  remove fuel from vehicle messages
//  
//  25    5/27/97 11:32a Bwilcox
//  unitdeploy fix
//  
//  24    5/23/97 3:01p Bwilcox
//  patching comm bug which ignores existnece of ai player
//  
//  23    5/15/97 10:37p Dmaynard
//  Unbreaking remote vehicles
//  
//  22    5/15/97 10:27p Dmaynard
//  Minor bug fix
//  
//  21    5/15/97 10:14p Dmaynard
//  Debugging Interpolated movement of remote vehicles
//  
//  20    5/15/97 9:09p Dmaynard
//  Added New Paramter to AnimMove() to allow interploated movement of
//  remote objects (while still allowing animation to be controled by local
//  frame rates.
//  
//  19    5/14/97 6:53p Dmaynard
//  Added VehicleDie and VehicleDeathMessages
//  VehicleDie handles the local animation of the remote vehicle death
//  
//  18    5/13/97 9:59p Aburgess
//  corrected damage message setup (triple assignment to same element
//  
//  17    5/13/97 9:15p Aburgess
//  
//  16    5/13/97 1:03a Dmaynard
//  
//  15    5/13/97 12:45a Dmaynard
//  RemoteVehicle  Missiles Firing and tracking
//  
//  14    5/12/97 7:27p Dmaynard
//  Unit Deployment from Vehicle
//  
//  13    5/12/97 6:06p Dmaynard
//  Deploy Unit from Vehicle Messages
//  
//  12    5/12/97 1:23p Dmaynard
//  Fixed bug when remote Vehicle deployed with a unit in vehicle.  You
//  must translate the UniqueID sent in the Secondary Unique ID flag
//  transmitted in the Deploy Message.
//  
//  11    5/11/97 11:14p Dmaynard
//  Added TRACE for vehicle message to find out why one shell kills a tank
//  
//  10    5/11/97 10:48p Dmaynard
//  
//  9     5/11/97 10:28p Dmaynard
//  
//  8     5/11/97 9:57p Dmaynard
//  Added Vehicle Damage Message.  When you fire You determine if you hit
//  the opponent, then send him a damage message.  He then actually
//  determines the damage, subtracts the strength, and triggers the
//  explosion animations and secondary explosions.
//  
//  7     5/07/97 2:48p Bwilcox
//  
//  6     5/07/97 1:33p Bwilcox
//  multiple units on board now alloweed
//  
//  5     5/05/97 10:24a Nrobinso
//  changed turretface to turret_face
//  
//  4     4/30/97 8:35p Nrobinso
//  add vehicle strength; remove flags
//  
//  3     4/29/97 5:22p Nrobinso
//  fix typos
//  
//  2     4/29/97 5:17p Nrobinso
//  switch to VEHICLE_MESSAGE
//  
//  1     4/29/97 11:56a Nrobinso
//  initial checkin
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "Army.h"
#include "ArmyMsg.h"
#include "Vehicle.h"
#include "VehicleMsg.h"
#include "AiAccess.h"
#include "comm.h"
#include "item.h"

/////////////////////////////////////////////////////////////////////////////
// Debugging support
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
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

static void	VehicleUpdateMessageReceive(VEHICLE_MESSAGE *pMsg);
static void	VehicleFireMessageReceive(VEHICLE_MESSAGE *pMsg);
static void	VehicleDeployMessageReceive(VEHICLEDEPLOY_MESSAGE* pMsg);
static void	VehicleRemoteDiedReceive(VEHICLE_SHORT_MESSAGE *pMsg);
static void	VehicleDamageMessageReceive(VEHICLE_DAMAGE_MESSAGE *pMsg);

/////////////////////////////////////////////////////////////////////////////
//					     Code
/////////////////////////////////////////////////////////////////////////////

///========================================================================
//	Function:		VehicleUpdateMessageSend()
//	Description:	Tell other players the vehicle status
///========================================================================

void	VehicleUpdateMessageSend(VEHICLE* pVehicle)	{

    if (gpComm->m_pDPlay == NULL) return; // not on net

    // see if any data changes
    if (pVehicle->common.oldTile != pVehicle->common.tile);
    else if (pVehicle->common.oldFacing != pVehicle->common.facing);
    else if (pVehicle->velocity != pVehicle->old_velocity);
    else if (pVehicle->gun_facing != pVehicle->old_gun_facing);
    else return;

    
	VEHICLE_MESSAGE msg;
	msg.nSize = sizeof(VEHICLE_MESSAGE);
	msg.msg_type = UPDATE_MESSAGE;
	msg.nUniqueID = ITEM_UID(pVehicle);
	msg.position = pVehicle->common.position;
	msg.facing = (BYTE)pVehicle->common.facing;
	msg.nStrength = pVehicle->common.nStrength;

	msg.full_velocity = pVehicle->full_velocity;
	msg.gun_facing = (BYTE)pVehicle->gun_facing;
	msg.velocity = pVehicle->velocity;

	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		VehicleDeployMessageSend()
//	Description:	Tell other players about vehicle deploy
///========================================================================

void	VehicleDeployMessageSend(VEHICLE* pVehicle)	{

    if (gpComm->m_pDPlay == NULL) return; // not on net
    
	VEHICLEDEPLOY_MESSAGE msg;
	msg.nSize = sizeof(VEHICLEDEPLOY_MESSAGE);
	msg.msg_type = DEPLOY_MESSAGE;
	msg.nUniqueID = ITEM_UID(pVehicle);
	msg.position = pVehicle->common.position;
	msg.facing = pVehicle->common.facing;
     if (gpComm->debugComm) TRACE("Deploy vehicle sent\n");
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		VehicleDeployMessageReceive()
//	Description:	message for other players about vehicle deploy
///========================================================================

static void	VehicleDeployMessageReceive(VEHICLEDEPLOY_MESSAGE* pMsg)	{

	int		nID = pMsg->nUniqueID;
	ASSERT(OBJTYPE(nID) == ARMY_VEHICLE);
	VEHICLE *pVehicle = VehicleFind(nID);
	if (!pVehicle) return;
    VehicleInitialDeploy(pVehicle,&pMsg->position,pMsg->facing);
}

///========================================================================
//	Function:		VehicleDamageMessageSend()
//	Description:	Tell other player the damage done to this vehicle
///========================================================================

void	VehicleDamageMessageSend(VEHICLE *pVehicle, int damagetodo, int damagetype, SPOINT *damageloc) {

    if (gpComm->m_pDPlay == NULL) return; // not on net

	VEHICLE_DAMAGE_MESSAGE msg;
	msg.nSize = sizeof(VEHICLE_DAMAGE_MESSAGE);
	msg.msg_type = DAMAGE_MESSAGE;
	msg.nUniqueID = ITEM_UID(pVehicle);
	msg.damagetodo = damagetodo;
	msg.damagetype = damagetype;
	msg.x = damageloc->x;
	msg.y = damageloc->y;
    msg.fromUID = 0;
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}


///========================================================================
//	Function:		VehicleFireMessageSend()
//	Description: 	Tell other players describing the vehcile firing
///========================================================================

void	VehicleFireMessageSend(VEHICLE* pVehicle)	{

    // BUG fix, if you assume armyplayer, you neglect ai player off net
    if (gpComm->m_pDPlay == NULL) return; // not on net
	VEHICLE_MESSAGE msg;
	msg.nSize = sizeof(VEHICLE_MESSAGE);
	msg.msg_type = FIRE_MESSAGE;
	msg.nUniqueID = ITEM_UID(pVehicle);
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}

///========================================================================
//	Function:		VehicleDiedMessageSend()
//	Description:	Tell other players describing the vehcile death
///========================================================================

void	VehicleDiedMessageSend(VEHICLE* pVehicle)	{
    // BUG fix, if you assume armyplayer, you neglect ai player off net
    if (gpComm->m_pDPlay == NULL) return; // not on net        
	VEHICLE_SHORT_MESSAGE msg;
	msg.nSize = sizeof(VEHICLE_MESSAGE);
	msg.msg_type = DIED_MESSAGE;
	msg.nUniqueID = ITEM_UID(pVehicle);
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}


///========================================================================
//	Function:		VehicleUpdateMessageReceive()
//	Description:	Receive vehicle status
///========================================================================

static void	VehicleUpdateMessageReceive(VEHICLE_MESSAGE *pMsg)	{
	int		nID = pMsg->nUniqueID;
	ASSERT(OBJTYPE(nID) == ARMY_VEHICLE);
	VEHICLE *pVehicle = VehicleFind(nID);
	if (!pVehicle) return;
	if ( pVehicle->state == VEHICLE_DYING ) {
		//  This theoretically shouldn't happen but it does... so ignore it
		//	TRACE("Ignoring vehicle update for dying vehicle at %d %d \n", pMsg->position.x,pMsg->position.y);
		return;
	}

	// implicit deployment if needed
	if (pVehicle->state == VEHICLE_UNDEPLOYED)
		VehicleDeploy(pVehicle, &pMsg->position, pMsg->facing);

	//set up shadow data to take effect next update
	pVehicle->new_position = pMsg->position;
	pVehicle->new_full_velocity = pMsg->full_velocity;
	pVehicle->new_velocity = pMsg->velocity;
	pVehicle->new_facing = pMsg->facing;
	pVehicle->new_gun_facing = pMsg->gun_facing;
	pVehicle->pAnimation->timefix = GetTickCount();
}

///========================================================================
//	Function:		VehicleFireMessageReceive()
//	Description:	Receive vehcile firing
///========================================================================

static void	VehicleFireMessageReceive(VEHICLE_MESSAGE *pMsg)	{

	int		nID = pMsg->nUniqueID;
	ASSERT(OBJTYPE(nID) == ARMY_VEHICLE);
	VEHICLE *pVehicle = VehicleFind(nID);
	if (!pVehicle) return;
	VehicleFireWeapon(pVehicle);
}


///========================================================================
//	Function:		VehicleRemoteDiedReceive()
//	Description: 	Receive vehicle death
///========================================================================

static void	VehicleRemoteDiedReceive(VEHICLE_SHORT_MESSAGE *pMsg)	{

	int		nID = pMsg->nUniqueID;
	ASSERT(OBJTYPE(nID) == ARMY_VEHICLE);
	VEHICLE *pVehicle = VehicleFind(nID);
//	TRACE("VehicleRemoteDiedReceive...");
	if (!pVehicle) return;
	VehicleDie(pVehicle);
//	TRACE(" returned from Vehicle Die\n");
}


///========================================================================
//	Function:		VehicleDamageMessageReceive()
//	Description:	Receive vehicle damage
///========================================================================

static void	VehicleDamageMessageReceive(VEHICLE_DAMAGE_MESSAGE *pMsg)	{

	SPOINT	pt;
    UID 	fromUID;
	int		nID = pMsg->nUniqueID;

    // ignore damage messages for any other player
    if (!IS_LOCAL_ARMY(EXTRACT_ARMY(pMsg->nUniqueID))) return;

	ASSERT(OBJTYPE(nID) == ARMY_VEHICLE);
	VEHICLE *pVehicle = VehicleFind(nID);
	if (!pVehicle) return;

	// For now we know we only receive damage message to ourselves
	pt.x = pMsg->x;
	pt.y = pMsg->y;
    fromUID = pMsg->fromUID;
    
//	TRACE("About to do vehincle damage %d %d \n", pMsg->damagetodo, pVehicle->common.nStrength);
	VehicleDamage(pVehicle, pMsg->damagetodo, pMsg->damagetype, &pt,fromUID);
//	TRACE("The damage is done  %d \n",pVehicle->common.nStrength);
}

///========================================================================
//	Function:		VehicleMessageReceive()
//	Description:	Dispatch vehicle messages
///========================================================================

void	VehicleMessageReceive(ARMY_MESSAGE *pMsg,int army_index)	{

	switch (pMsg->msg_type)	{
		case UPDATE_MESSAGE:
			VehicleUpdateMessageReceive((VEHICLE_MESSAGE*)pMsg);
			break;
        case DEPLOY_MESSAGE:
            VehicleDeployMessageReceive((VEHICLEDEPLOY_MESSAGE*)pMsg);
            break;
		case FIRE_MESSAGE:
			VehicleFireMessageReceive((VEHICLE_MESSAGE*)pMsg);
			break;
		case DAMAGE_MESSAGE:
			VehicleDamageMessageReceive((VEHICLE_DAMAGE_MESSAGE *)pMsg);
			break;
		case DIED_MESSAGE:
			VehicleRemoteDiedReceive((VEHICLE_SHORT_MESSAGE *)pMsg);
			break;
		default:
			TRACE("Unknown Vehicle Message of type %d Received\n",pMsg->msg_type);
			break;
	}
}
