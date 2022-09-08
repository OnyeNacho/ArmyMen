//========================================================================
//	FILE:			$Workfile: sargeP.h $
//
//	DESCRIPTION:	Private data for sarge
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		Sunday, July 27, 1997
//
//	REVISION:		$Header: /ArmyMen/src/sargeP.h 47    4/14/98 2:42p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unauthorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/sargeP.h $
//  
//  47    4/14/98 2:42p Nrobinso
//  turn off health voice over on sarge death
//  
//  46    4/13/98 10:48p Bwilcox
//  ai order failures delay 3 seconds before reporting now
//  
//  45    4/10/98 1:12a Bwilcox
//  keeping deadposition as unique data
//  
//  44    4/08/98 2:52p Bwilcox
//  NPC SARGE WILL ACTIVATE ANY 2NDARY WEAPON HE PICKS UP
//  
//  42    3/29/98 4:32p Nrobinso
//  save pickuo sound id
//  
//  41    3/25/98 9:04a Bwilcox
//  add fireindex
//  
//  40    3/24/98 8:00p Dmaynard
//  renamed killerarmycolor to killerarmyindex  because it IS an index.
//  
//  39    3/15/98 7:13p Nrobinso
//  maintain a flame hit snd id
//  
//  38    3/05/98 6:31p Nrobinso
//  fix prone throw and non-kneel mortar
//  
//  37    2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  36    2/04/98 5:59p Nrobinso
//  change killerarmy to killerarmycolor
//  
//  35    2/03/98 4:03p Nrobinso
//  sarge has a mode
//  
//  34    1/20/98 1:43p Phu
//  sarge is invulnerable for 5secs after deployment, + sarge chevron
//  flashes while he is invulnerable
//  
//  33    1/17/98 8:17p Nrobinso
//  add ViewBox to sarge's info
//  
//  32    12/23/97 1:47p Bwilcox
//  epoint lastLegalLocation becomes spoint lastLegalPosition
//  
//  31    12/19/97 2:08p Bwilcox
//  more epoint to spoint conversion
//  
//  30    12/14/97 2:08p Bwilcox
//  event data added for ai sarge use
//  
//  29    12/13/97 12:33a Phu
//  Quest Item + Cheat
//  
//  28    12/11/97 3:21p Nrobinso
//  maintain a previous avatar action state for firing while moving
//  
//  27    12/11/97 9:51a Phu
//  
//  26    12/09/97 12:12p Phu
//  
//  25    11/20/97 1:52p Bwilcox
//  adjusting resurrection of sarge and vechile
//  
//  24    11/12/97 12:50p Bwilcox
//  Sarge keeps his last legal location so routeplanner for FOLLOW can be
//  ok.
//  
//  23    11/07/97 4:02p Nrobinso
//  add poses
//  
//  22    10/30/97 10:19a Nrobinso
//  add gun_facing
//  
//  21    10/23/97 11:35a Bwilcox
//  sarge in vehicle should not be targetable (fixed)
//  
//  20    10/18/97 12:21p Aburgess
//  new Alive field for Sarge
//  
//  19    10/15/97 5:05p Nrobinso
//  all deploys now consistent; SargeCreate only takes an army designator
//  
//  18    10/15/97 1:01p Phu
//  Pickup & Drop weapons
//  
//  17    10/15/97 10:54a Awerner
//  Added an index variable to the Sarge struct which tracks which weapon
//  is currently activated
//  
//  16    10/13/97 5:31p Nrobinso
//  give sarge an array of weapon pointer, plus a weapon structure for his
//  primary weapon. Picked up weapons will get a pointer to the object's
//  weapon data
//  
//  15    10/10/97 5:10p Bwilcox
//  added speed and behavior data to sarge and vehicles
//  
//  14    10/08/97 3:46p Nrobinso
//  add sarge's multiple weapons
//  
//  13    10/07/97 2:55p Bwilcox
//  added aiGoal
//  
//  12    10/01/97 12:18p Bwilcox
//  npc status now supported for sarge
//  
//  10    9/14/97 12:19p Bwilcox
//  influence stuff moved to deadcode.cpp (not in project)
//  
//  9     8/25/97 1:07p Bwilcox
//  sarginvehicle calls and associated data changed from item to vehicle
//  VehicleScroll added and called whenever sarge enters vehicle.
//  Exiting vehicle rescrolls to sarge
//  
//  8     8/20/97 11:16a Nrobinso
//  vehicle override on sarge
//  
//  7     8/15/97 1:02p Bwilcox
//  added current action/direction for proper maintenance of sarge and
//  trooper across net
//  
//  6     8/12/97 3:57p Nrobinso
//  add turning timing
//  
//  5     8/11/97 5:14p Bwilcox
//  addded pTarget
//  
//  4     7/30/97 12:14p Bwilcox
//  code to damage and kill sarge. enabled routeplanner data for ai.
//  
//  3     7/29/97 11:02p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
//  
//  2     7/29/97 11:01a Nrobinso
//  moved weapon into common
//  
//  1     7/28/97 7:55p Nrobinso
//  
//  
//  $Nokeywords:$
///========================================================================

#ifndef __SARGE_P_H   
#define __SARGE_P_H   

typedef enum
{
	SARGE_WEAPON_PRIMARY,
	SARGE_WEAPON_SECONDARY,
	SARGE_WEAPON_SPECIAL,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	SARGE_LAST_WEAPON
} SARGE_WEAPON;

// SARGE structure
struct  SARGESTRUCT
{
    ITEM			common;				// common components of all objects
    ACTION			pendingAction;		// next avatar high-level action
    ACTION			pendingPose;		// next avatar pose
	BOOL			setPendingPose;		// whether pending pose should be listened to
    int				pendingDirection;	// direction for next avatar motion
    ACTION			action;				// currently done
    int				direction;			// currently done
    ACTION			oldAction;			// done last frame
    int				oldDirection;		// done last frame
	int				desiredDirection;	// the direction sarge should go
    int				imode;			// in mode behavior
    int				atmode;			// at mode behavior
    ITEM*			pTarget;		// sarge target (if ai controlled)

	int				mode;
    // route planner data
    ROUTEDATA		routeData;		// needed to allow sarge AI to go places
    SPOINT			aiGoal;			// where ai is routing a sarge
    int				speed;			// how fast

    SPOINT			lastLegalPosition; // where on last good tile

    // avatar data
    AVATAR*			pAvatar;			// body for the trooper
    char			npc;				// under npc control?

	ACTION			previous_state;

	int 			count;
    int 			killerarmyindex;			// passed forward from dying

	WEAPON			*pWeaponList[SARGE_LAST_WEAPON];
	ITEM			*pWeaponItemList[SARGE_LAST_WEAPON];
	ITEM			*prevPickup;
	int				questItem;

	WEAPON			primary_weapon;		// sarge's rifle
	char			weapon_index;		//which weapon is currently active

  	char			reset_gun_facing;
	SHORT			gun_facing;			// directional facing of gun turret (0..255)
	
	SPOINT			deployPosition;		// where to deploy it if dynamic
    short			deployFacing;		// facing to deploy if delayed

    VEHICLE*		pVehicle;			// currently controlled vehicle
    int 			arrivalEvent;		// event on ai arrivale
    int 			eventtype;			// type of event

	int				invulnerableTimer;	// tracks how long to make sarge invunerable for

	SBOX			ViewBox;			// Sarge's view of the world	

	unsigned char   fireHeight;			// height to which sarge is firing
    unsigned char	fireIndex;			// which weapon

	ULONG			flameSndId;			// snd id for hit by flame
	ULONG			pickupSndId;		// snd id for hit by fully loaded
	ULONG			healthSndId;		// snd id for health warning

	int				seeksWeapon;		// object index
	long			seekTime;			// NEXT TIME TO SEEK

	SPOINT			deadPosition; // where he died
		long		delayFailed;		// when to trigger fail of event

};

#endif
