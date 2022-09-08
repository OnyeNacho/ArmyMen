//========================================================================
//	FILE:			$Workfile: weaponp.h $
//
//	DESCRIPTION:	weapon headers
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		Thursday, June 02, 1997
//
//	REVISION:		$Header: /ArmyMen/src/weaponp.h 26    3/05/98 4:49p Nrobinso $
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
//  $Log: /ArmyMen/src/weaponp.h $
//  
//  26    3/05/98 4:49p Nrobinso
//  add real weapon flag
//  
//  25    2/27/98 12:58p Nrobinso
//  improve sfx playing
//  
//  24    2/20/98 1:21p Nrobinso
//  fix up sounds
//  
//  23    2/17/98 9:04p Nrobinso
//  weapon sounds
//  
//  22    1/13/98 11:15a Phu
//  add special items enumeration
//  
//  21    1/08/98 1:53p Phu
//  mp airsupport
//  
//  20    12/22/97 4:42p Phu
//  medkits & medpacks
//  
//  19    12/19/97 10:21a Phu
//  
//  18    12/09/97 12:12p Phu
//  
//  17    12/04/97 11:10a Phu
//  Added extra layer, moved order variable, changed flamer
//  
//  16    11/16/97 5:34p Nrobinso
//  army_explosive becomes army_explosive_weapon; the MINE object category
//  became the EXPLOSIVES category
//  
//  15    11/14/97 11:19a Aburgess
//  new weapon snd structure
//  
//  14    11/11/97 4:52p Phu
//  Guard Towers
//  
//  13    11/11/97 10:50a Nrobinso
//  add weapon distance
//  
//  12    10/30/97 10:43a Phu
//  add mine sweeper weapon
//  
//  11    10/30/97 10:24a Nrobinso
//  add timing counter
//  
//  10    10/29/97 1:06p Phu
//  linked explosives special item w/ charges
//  
//  9     10/24/97 12:48p Phu
//  allocate charge memory?
//  
//  8     10/20/97 2:31p Bwilcox
//  adjusted Makeweapon to use aidefaults.aai stuff
//  simplified aiinput code and expanded it to handle more sitems
//  
//  7     10/09/97 3:31p Awerner
//  Added in events for script recognition of getting and dropping weapons
//  
//  6     10/08/97 3:46p Nrobinso
//  add new weapons
//  
//  4     8/13/97 6:52p Nrobinso
//  add weapon projectile speeds to aidefault file
//  
//  3     8/12/97 3:51p Nrobinso
//  added sarge gun
//  
//  2     8/07/97 11:25p Nrobinso
//  celanup; put new data into weapon
//  
//  1     7/29/97 11:37p Bwilcox
//  
//  3     7/27/97 9:42a Nrobinso
//  call mortar instead of artillery
//  
//  2     7/25/97 2:48p Bwilcox
//  moved unit and weapon data from army.h to respective unit/weapon .h
//  
//  1     7/25/97 12:49p Bwilcox
//  
//  $Nokeywords:$
///========================================================================


#ifndef __WEAPONP_H
#define __WEAPONP_H


//ARMY projectile types
typedef enum
{
	ARMY_NO_PROJECTILE = 0,
	ARMY_LINE_OF_SIGHT,
	ARMY_GROUND_MISSILE,
	ARMY_CONE,
	ARMY_AREA,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_PROJECTILE
} PROJECTILE_TYPE;


// ARMY weapon types -- these must correlate with WEAPON_DAMAGE_TYPE below
// Must also correspond with table of weapondata next to MakeWeapon in weapon.cpp
typedef enum
{
	ARMY_NO_WEAPON = 0,
	ARMY_LIGHT_MACHINE_GUN = 1,

	ARMY_GRENADE = 2,
	ARMY_FLAME_THROWER = 3,
	ARMY_BAZOOKA = 4,
	ARMY_MORTAR = 5,

	ARMY_LARGE_CANNON = 6,
	ARMY_MEDIUM_MACHINE_GUN = 7,
	ARMY_HEAVY_MACHINE_GUN = 8,

	ARMY_RIFLE = 9,
	ARMY_AUTORIFLE = 10,

	ARMY_MINE = 11,
	ARMY_EXPLOSIVE_WEAPON = 12,
	ARMY_DETONATOR = 13,

	ARMY_LURE = 14,

	ARMY_FLAG = 15,
	ARMY_GREENFLAG = 16,
	ARMY_TANFLAG = 17,
	ARMY_BLUEFLAG = 18,
	ARMY_GRAYFLAG = 19,

	ARMY_SWEEPER = 20,

	ARMY_GUARD_TOWER_RIFLE = 21,

	ARMY_MEDKIT = 22,
	ARMY_MEDPACK = 23,

	ARMY_AIRSTRIKE = 24,
	ARMY_PARATROOPERS = 25,
	ARMY_RECON = 26,

	ARMY_SPECIAL_1 = 27,
	ARMY_SPECIAL_2 = 28,
	ARMY_SPECIAL_3 = 29,
	ARMY_SPECIAL_4 = 30,
	ARMY_SPECIAL_5 = 31,
	ARMY_SPECIAL_6 = 32,
	ARMY_SPECIAL_7 = 33,
	ARMY_SPECIAL_8 = 34,
	ARMY_SPECIAL_9 = 35,
	ARMY_SPECIAL_10 = 36,
	ARMY_SPECIAL_11 = 37,
	ARMY_SPECIAL_12 = 38,
	ARMY_SPECIAL_13 = 39,
	ARMY_SPECIAL_14 = 40,
	ARMY_SPECIAL_15 = 41,
	ARMY_SPECIAL_16 = 42,
	ARMY_SPECIAL_17 = 43,
	ARMY_SPECIAL_18 = 44,
	ARMY_SPECIAL_19 = 45,
	ARMY_SPECIAL_20 = 46,
	ARMY_SPECIAL_21 = 47,
	ARMY_SPECIAL_22 = 48,
	ARMY_SPECIAL_23 = 49,
	ARMY_SPECIAL_24 = 50,
	ARMY_SPECIAL_25 = 51,
	ARMY_SPECIAL_26 = 52,
	ARMY_SPECIAL_27 = 53,
	ARMY_SPECIAL_28 = 54,
	ARMY_SPECIAL_29 = 55,
	ARMY_SPECIAL_30 = 56,
	// there will no doubt be more weapons

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_WEAPON
} WEAPON_TYPE;


extern char WEAPON_DAMAGE_TYPE[];   // correlates with weapons above

// WEAPON structure
struct WEAPONSTRUCT
{
	WEAPON_TYPE	eWeapon;	// weapon ID
	ITEM	*pOwner;
	int		fire_count;		// counter used with fire rate
    short	nAmmo;			// amount of ammo
	short	nMaxAmmo;		// max amount of ammo
	short	nDamage;		// amount of damage
	short	nFireRate;		// firing rate
	short	nVelocity;		// velocity
	short	nZVelocity;		// velocity in z direction
	char	eDamageType;	// type of damage
	char	percentDistance;	// percentage of max distance to decrease
	short   *charges;		// index #s for charges
	DWORD	last_fire_time;
	short	last_fire_projectile;
	char	bTrueWeapon;
};

// Weapon Sound table
typedef struct weapon_snd
{
	ULONG		nFireAudio;		// the audio ID for the weapons firing sound
	ULONG		nContinueAudio;	// the audio ID for the weapons continue sound

	ULONG		nFireSnd;		// the sound ID for the weapons firing sound
} WEAPONSND;


#endif         