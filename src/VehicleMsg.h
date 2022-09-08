/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: VehicleMsg.h $
//
//	DESCRIPTION:	Vehicle messaging interface
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Friday, April 25, 1997
//
//	REVISION:		$Header: /ArmyMen/src/VehicleMsg.h 16    3/27/98 10:06a Bwilcox $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/VehicleMsg.h $
//  
//  16    3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  15    12/09/97 12:12p Phu
//  
//  14    10/30/97 11:12a Bwilcox
//  removed vehiclepickingup and dropping code that was obsolete
//  
//  13    10/30/97 10:43a Nrobinso
//  turret_facing becomes gun_facing
//  
//  12    10/24/97 9:10a Bwilcox
//  cleaning up messages and doing unit into vehcle
//  
//  11    10/23/97 4:06p Bwilcox
//  removing dead code relating to units entering vehicles and installing
//  new code
//  
//  10    10/22/97 10:17a Bwilcox
//  remote vehicle deploy, enter and exit of vehicle
//  
//  8     8/26/97 2:34p Bwilcox
//  remote vehicle messgaes per vehicle
//  
//  7     8/25/97 3:33p Bwilcox
//  vehicledeploy/undeploy messages removed, code changes around vehicle
//  create.deploy and sarge in vehicle
//  
//  6     8/21/97 6:58p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  5     8/17/97 7:16p Nrobinso
//  minimize message data
//  
//  4     8/07/97 11:22p Nrobinso
//  removed percent data from damage messages
//  
//  3     8/05/97 3:28p Nrobinso
//  rename item bFlags bItemFlags
//  
//
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __VEHICLEMSG_H__
#define __VEHICLEMSG_H__

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

void	VehicleUpdateMessageSend(VEHICLE* pVehicle);
void	VehicleFireMessageSend(VEHICLE* pVehicle);
void	VehicleDiedMessageSend(VEHICLE* pVehicle);
void	VehicleDamageMessageSend(VEHICLE *pVehicle, int damagetodo, int damagetype, SPOINT *damageloc);

void	VehicleMessageReceive(ARMY_MESSAGE *pMsg, int army_index);
void	VehicleDeployMessageSend(VEHICLE* pVehicle);
#endif
