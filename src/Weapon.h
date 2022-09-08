//========================================================================
//	FILE:			$Workfile: Weapon.h $
//
//	DESCRIPTION:	weapon headers
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		Thursday, June 02, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Weapon.h 34    3/18/98 4:16p Phu $
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
//  $Log: /ArmyMen/src/Weapon.h $
//  
//  34    3/18/98 4:16p Phu
//  stop flames when they hit
//  
//  33    2/27/98 12:58p Nrobinso
//  improve sfx playing
//  
//  32    2/20/98 1:21p Nrobinso
//  fix up sounds
//  
//  31    2/10/98 5:06p Bwilcox
//  fixing mine ownership I broke
//  
//  30    2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  29    2/02/98 6:39p Bwilcox
//  mine removal over the net
//  
//  28    1/25/98 3:21a Bwilcox
//  static placemine
//  
//  27    1/21/98 1:52p Phu
//  check in for bruce - mine removal function
//  
//  26    12/21/97 8:29p Bwilcox
//  removing use of elevation
//  
//  25    97/12/15 16:59 Dmaynard
//  Code to get laying on of mines to work across the network.  Still need
//  to add code to Remove mines after they are swept up or are triggered
//  
//  24    12/15/97 4:13a Nrobinso
//  check & set ammo functions
//  
//  23    12/09/97 12:12p Phu
//  
//  22    11/24/97 8:35p Phu
//  Add Z component to projectile firing
//  
//  21    11/20/97 3:25p Phu
//  base muzzle flash anchor on uid
//  
//  20    11/20/97 11:42a Phu
//  attach muzzle flashes, add smoke
//  
//  19    11/19/97 5:40p Phu
//  flamethrowers & muzzle flashes
//  
//  18    11/11/97 10:50a Nrobinso
//  add weapon distance
//  
//  17    10/30/97 10:24a Nrobinso
//  add weapon timing functions
//  
//  16    10/29/97 3:04p Phu
//  Added mine placement
//  
//  15    10/29/97 1:06p Phu
//  linked explosives special item w/ charges
//  
//  14    10/28/97 6:10p Phu
//  explosives placement test
//  
//  13    10/20/97 3:12p Bwilcox
//  added max ammo count to makeweapon call
//  
//  12    10/20/97 2:31p Bwilcox
//  adjusted Makeweapon to use aidefaults.aai stuff
//  simplified aiinput code and expanded it to handle more sitems
//  
//  11    10/16/97 6:38p Phu
//  Handle all sorts of weapons!
//  
//  10    10/08/97 4:09p Bwilcox
//  firing range now affected by elevation
//  
//  8     8/21/97 6:59p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  7     8/16/97 3:08p Nrobinso
//  revamp fire weapon system
//  
//  6     8/07/97 11:25p Nrobinso
//  celanup; put new data into weapon
//  
//  5     8/06/97 9:58a Nrobinso
//  WEaponFire now FireWeapon
//  
//  4     7/29/97 11:32p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
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

#ifndef __WEAPON_H
#define __WEAPON_H


#define HIT		TRUE
#define MISS	FALSE

typedef struct
{
	int direction;
	int distance;
} SET_WEAPON;

int	WeaponMinRange(WEAPON_TYPE eWeapon);
int	WeaponMaxRange(WEAPON_TYPE eWeapon);
SET_WEAPON SetFireWeapon(WEAPON* pWeapon, SPOINT* pFrom, int direction, ITEM* pTarget);
void FireWeapon(ARMY_TYPE eArmy, WEAPON* pWeapon, SPOINT* pFrom, int z, 
				int direction, int distance, int height, UID fromUID );
WEAPON* MakeWeapon(WEAPON* pWeapon, WEAPON_TYPE eWeapon,int maxammo );
void FreeWeapon( OBJECTSTRUCT * pObject );
void PlaceExplosiveCharge( WEAPON *pWeapon, int x, int y );
void WeaponFireUpdate(WEAPON* pWeapon);
void WeaponFireReset(WEAPON* pWeapon);
void WeaponDistancePercentage(WEAPON* pWeapon, char percent);
extern inline BOOL WeaponFireTime(WEAPON* pWeapon);
BOOL WeaponSingleShot(WEAPON* pWeapon);
void MakeFlameBurst( int eArmy, WEAPON *pWeapon, int x, int y, 
					 int direction, int velocity, int height, UID fromUID );

void SetItemCurrentAmmo(ITEM *pItem, int ammo);
int	GetItemCurrentAmmo(ITEM *pItem);
int	GetItemMaxAmmo(ITEM *pItem);


void UnplaceMine(OBJECTSTRUCT *pObject);
void RawUnplaceMine(OBJECTSTRUCT *pObject);
void PutMine(OBJECT* pObj,SPOINT position,int eArmy);

void SetWeaponOwner(WEAPON *pWeapon, ITEM *pOwner);

#endif         