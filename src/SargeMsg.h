//========================================================================
//	FILE:			$Workfile: SargeMsg.h $
//
//	DESCRIPTION:	Sarge messaging interface.
//
//	AUTHOR:			David S. Maynard
//
//	CREATED:		Tuesday, July 30, 1997
//
//	REVISION:		$Header: /ArmyMen/src/SargeMsg.h 31    3/27/98 10:06a Bwilcox $
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
//  $Log: /ArmyMen/src/SargeMsg.h $
//  
//  31    3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  30    3/26/98 8:55a Bwilcox
//  fixing sarge moving after death
//  
//  29    3/26/98 8:34a Bwilcox
//  improved sarge dying trace and passing position of death
//  
//  28    3/25/98 9:04a Bwilcox
//  add fireindex
//  
//  27    2/27/98 1:18p Bwilcox
//  cleaning up the air, supporting script airdrops for foes,e tc
//  
//  26    2/06/98 10:48a Bwilcox
//  pass non-zero sarge strength along so medpak works
//  
//  25    2/04/98 5:55p Nrobinso
//  change passing of sarge killed by army to correspond to trooper
//  
//  24    1/26/98 11:27a Phu
//  parachutists
//  
//  23    1/15/98 2:20p Bwilcox
//  convert firedist to unsigned char
//  
//  22    1/13/98 9:36p Bwilcox
//  ammo count put on drop, pickup and weapon dropped when empty
//  
//  21    1/08/98 1:52p Phu
//  mp airsupport
//  
//  20    1/08/98 12:26p Dmaynard
//  Fixed bug in SargeUpdateSend   added a forceSend parameter.  An update
//  wasn't getting sent if Sarge hadn't moved.  The problem is that he had
//  changed selected weapon.  As a result remote computers had wrong weapon
//  selected which led to ammo count discrepancies.
//  
//  
//  19    12/19/97 2:08p Bwilcox
//  more epoint to spoint conversion
//  
//  18    12/15/97 12:01p Dmaynard
//  added weapon_index (currently selected weapon) to the
//  SargeUpdateMessage data structure so that remote Sarges will fire the
//  proper weapons.
//  
//  17    12/09/97 12:12p Phu
//  
//  16    11/20/97 1:52p Bwilcox
//  adjusting resurrection of sarge and vechile
//  
//  15    11/18/97 1:51p Bwilcox
//  drop across the net code and pickup too.
//  
//  14    11/17/97 3:27a Bwilcox
//  sarge deploy/undeploy across the net
//  
//  13    11/16/97 11:58p Bwilcox
//  passing along who killed the sarge (which army)
//  
//  12    10/24/97 9:10a Bwilcox
//  cleaning up messages and doing unit into vehcle
//  
//  10    9/09/97 9:26a Nrobinso
//  pass vehicle position and facing with message in which sarge gets into
//  a vehicle
//  
//  9     8/27/97 5:05p Dmaynard
//  Temporary Hack to call VehicleCompleteDeploy from SargeVehicleReceive
//  if the vehicle is currently in an Undeployed state.. We should probably
//  go back to sending a vehicleDeploy message any time a vehicle is
//  deployed.  
//  
//  8     8/25/97 3:09p Bwilcox
//  SargeVehicleMessages for entering and exiting vehicles across net added
//  
//  7     8/21/97 6:50p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  6     8/17/97 7:16p Nrobinso
//  minimize message data
//  
//  5     8/16/97 3:05p Nrobinso
//  revamp fire weapon system
//  
//  4     8/15/97 8:38p Bwilcox
//  sarge death throes split into 2 net messages
//  
//  3     8/07/97 11:21p Nrobinso
//  removed percent data from damage messages
//  
//  2     8/01/97 6:11p Dmaynard
//  Fixed Struct Fields in SARGE_DAMAGE_MESSAGE ordering in now correct.
//  Short nSize and Long UniqueID
//  
//  1     7/30/97 7:03p Dmaynard
//  

//  
//  $Nokeywords:$
///========================================================================

#ifndef __SARGEMSG_H__
#define __SARGEMSG_H__

///========================================================================
// Includes
///========================================================================

#include "ArmyMsg.h"
#include "air.h"
#include "donottouch.h"


///========================================================================
//					Global Variables
///========================================================================

///========================================================================
//					Global Prototypes
///========================================================================

void	SargeWantItemMessageSend( SARGE* pSarge,ITEM* pItem,REQUEST pickup,SARGE_WEAPON slot);
void	SargeUpdateMessageSend( SARGE* pSarge, BOOL forceSend );
void	SargeDamageMessageSend( SARGE *pSarge, int damagetodo, int damagetype, SPOINT *damageloc,UID fromUID);
void	SargeDeathMessageSend( SARGE* pSarge, int killerArmy );
void	SargeGoneMessageSend( SARGE* pSarge);
void	SargeMessageReceive( ARMY_MESSAGE *pMsg, int army_index );
void	SargeVehicleMessageSend(SARGE *pSarge, VEHICLE* pVehicle, BOOL bEnter);
void	SargeAirSupportMessageSend( SARGE *pSarge, AIRSUPPORTTYPE type, SPOINT pos );

#endif

///========================================================================
//								EOF
///========================================================================
