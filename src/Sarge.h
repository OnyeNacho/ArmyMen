//========================================================================
//	FILE:			$Workfile: Sarge.h $
//
//	DESCRIPTION:	Defines, structures, and prototypes for handling of Sarge
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Sunday, July 27, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Sarge.h 67    4/09/98 12:06p Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Sarge.h $
//  
//  67    4/09/98 12:06p Bwilcox
//  issargeuntrafficable varies if sarge is npc. new arg added
//  
//  65    4/02/98 7:35p Nrobinso
//  fix med pack anim and timing; add variety of death sounds
//  
//  64    3/29/98 1:29a Nrobinso
//  don't play pickup sound when loading a saved game
//  
//  63    3/16/98 12:31a Nrobinso
//  auto tuning of sarge strength is in sarge.cpp
//  
//  62    3/08/98 1:05a Nrobinso
//  function to determine sarge's anim type
//  
//  61    3/07/98 10:47p Nrobinso
//  (in)vulnerability interface
//  
//  60    3/04/98 11:46a Phu
//  fix crash bug in UpdatePosing() if sarge had no avatar.
//  don't allow vehicle deployment on sarge
//  create convoy mask
//  
//  59    3/03/98 9:41p Nrobinso
//  
//  58    2/27/98 7:07p Nrobinso
//  unit deploy takes a vehicle pointer
//  
//  57    2/27/98 1:18p Bwilcox
//  cleaning up the air, supporting script airdrops for foes,e tc
//  
//  56    2/12/98 9:45p Nrobinso
//  SargeDown added
//  
//  55    2/07/98 12:26a Nrobinso
//  activate next weapon with right button
//  
//  54    2/04/98 4:43p Phu
//  kill sarge when untrafficable
//  
//  53    2/03/98 4:03p Nrobinso
//  SARGE_ON_MAP macro added
//  
//  52    2/03/98 3:22p Bwilcox
//  sargegetactiveweapon now takes arg,
//  fixed avatar mine interactions
//  
//  51    2/03/98 11:24a Nrobinso
//  fix firing bar stay up; make local & remote call a common routine to
//  set sarge's anim
//  
//  50    1/28/98 4:22p Nrobinso
//  pass facing to SetFire
//  
//  49    1/17/98 8:16p Nrobinso
//  saet sarge's view routine
//  
//  48    1/08/98 8:36p Nrobinso
//  remove ifdef debug around fillairsupport
//  
//  47    12/18/97 6:05p Bwilcox
//  converting epoint to spoint (not spoint*) notation
//  
//  46    12/17/97 4:49p Dmaynard
//  Added a pSarge parameter to ActivateSargeWeapon instead of always
//  assuming its the local sarge to properly handle droping weapons in
//  network multi-player game.
//  
//  45    12/15/97 5:14a Phu
//  sarge teleport/ sarge is untrafficable debug
//  
//  44    12/13/97 12:33a Phu
//  Quest Item + Cheat
//  
//  43    12/10/97 12:02p Nrobinso
//  add NoFire routine
//  
//  42    12/09/97 12:12p Phu
//  
//  41    12/07/97 3:59p Nrobinso
//  change sarge interface commands
//  
//  40    11/20/97 1:52p Bwilcox
//  adjusting resurrection of sarge and vechile
//  
//  39    11/18/97 1:51p Bwilcox
//  drop across the net code and pickup too.
//  
//  38    11/17/97 11:07a Nrobinso
//  projectile hit code added
//  
//  37    11/17/97 3:27a Bwilcox
//  sarge deploy/undeploy across the net
//  
//  36    11/16/97 11:58p Bwilcox
//  passing along who killed the sarge (which army)
//  
//  35    11/12/97 2:37p Awerner
//  First pass of new sarge trafficability code
//  
//  34    11/11/97 2:34p Nrobinso
//  center aiming curosr off of aiming hotspot (on trooper anim or turret
//  anim)
//  
//  33    11/07/97 4:26p Awerner
//  Pressing F8 now gives you 3 each of the air support types
//  
//  32    11/07/97 4:02p Nrobinso
//  add poses
//  
//  31    10/30/97 5:58p Awerner
//  Airdrops and airstrikes are now tracked properly
//  
//  30    10/30/97 10:19a Nrobinso
//  remove extern sargestop
//  
//  29    10/21/97 2:16p Bwilcox
//  D for drop special
//  
//  28    10/21/97 1:59p Bwilcox
//  releasing unit/sarge labels on exit of game
//  
//  27    10/21/97 1:15p Bwilcox
//  adjusting sarge recreation upon death
//  skeleton cleanup on close of game
//  
//  26    10/15/97 5:05p Nrobinso
//  all deploys now consistent; SargeCreate only takes an army designator
//  
//  25    10/15/97 11:38a Awerner
//  Sarge's currently selected weapon is now highlighted
//  
//  24    10/15/97 10:54a Awerner
//  Added an index variable to the Sarge struct which tracks which weapon
//  is currently activated
//  
//  23    10/14/97 6:24p Phu
//  pickup explosives
//  
//  22    10/14/97 3:37p Nrobinso
//  inline a number of simple access functions
//  
//  21    10/14/97 1:37p Nrobinso
//  make SargeFind inline
//  
//  20    10/14/97 12:00p Nrobinso
//  fill in all Sarge info interface routines
//  
//  19    10/14/97 10:10a Nrobinso
//  move information interface routines from ui to sarge.cpp/sarge.h
//  
//  17    9/10/97 1:08p Bwilcox
//  split sarge create from sarge deploy, if no sarge in scenario, creates
//  undeployed one
//  
//  16    9/09/97 9:25a Nrobinso
//  SargeCreate and SargeDeploy now take a position and facing
//  
//  15    8/25/97 1:06p Bwilcox
//  sarginvehicle calls and associated data changed from item to vehicle
//  VehicleScroll added and called whenever sarge enters vehicle.
//  Exiting vehicle rescrolls to sarge
//  
//  14    8/21/97 6:49p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  13    8/20/97 11:16a Nrobinso
//  vehicle override on sarge
//  
//  12    8/18/97 2:09p Awerner
//  
//  11    8/16/97 3:05p Nrobinso
//  revamp fire weapon system
//  
//  10    8/15/97 8:38p Bwilcox
//  sarge death throes split into 2 net messages
//  
//  9     8/14/97 5:54p Dmaynard
//  Changed SargeDie from Static to not static
//  
//  8     8/07/97 11:27p Nrobinso
//  damage cleanup
//  
//  7     7/30/97 1:50p Bwilcox
//  deploy,undeploy,teleport
//  
//  6     7/30/97 12:14p Bwilcox
//  code to damage and kill sarge. enabled routeplanner data for ai.
//  
//  5     7/29/97 10:59a Nrobinso
//  added SargeGetDamage
//  
//  4     7/28/97 7:55p Nrobinso
//  make sarge a SARGE instead of a TROOP
//  
//  3     7/27/97 9:34p Nrobinso
//  add sarge controls
//  
//  2     7/27/97 4:36p Nrobinso
//  compilable
//  
//  1     7/27/97 3:14p Nrobinso
//  
//  
//  $Nokeywords:$
///========================================================================

#ifndef __SARGE_H__
#define __SARGE_H__

//=========================================================================
//						GLOBAL DEFINES
//=========================================================================
// UNIT modes
typedef enum
{
    SARGE_DEAD = 0,
    SARGE_DEPLOYED = 1
} SARGE_MODE;

#define SARGE_ON_MAP(x) ((x)->mode >= SARGE_DEPLOYED)

//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================
#define DIE_SOUNDS 8

extern int die_snds[DIE_SOUNDS];

//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================

//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================
BOOL	SargeCreate( ARMY_TYPE eArmy);
void	SargeUndeploy( ARMY_TYPE eArmy );
void	SargeDeploy( SARGE* pSarge, SPOINT *pPos, short facing);
void	SargeInitialDeploy( SARGE* pSarge, SPOINT *pPos, short facing, VEHICLE *pVehicle = NULL);
void	SargeDeployPosition( SARGE* pSarge, SPOINT *pPos, short facing);
void	SargeUpdate( SARGE* pSarge );
void	SargeFireWeapon(SARGE* pSarge);
void	SargeNoFireWeapon(SARGE* pSarge);
void	SargeSetFire(SARGE *pSarge, int facing);
void 	SargeDamage(SARGE* pSarge, int nDamageToDo, int nDamageType, SPOINT* pFrom,UID fromUID);
void	SargeTeleport(SARGE* pSarge, SHORT x, SHORT y);
void	SargeDie(SARGE* pSarge,int armyKiller);
void	SargeGone(SARGE* pSarge);
void	SargeInVehicle( SARGE* pSarge, VEHICLE *pVehicle );
void	SargeOutVehicle( SARGE* pSarge );
void	SargeSetView( SARGE* pSarge );

extern inline SPOINT	SargePosition(ARMY_TYPE eArmy);
extern inline SARGE*	SargePointer(int eArmy);
extern inline SARGE*	SargeFind(LONG nUniqueID);
extern inline VEHICLE* SargeVehiclePointer(ARMY_TYPE eArmy);

int GetSargeAmmo(int whichweapon);
void SetSargeAmmo(int whichweapon, int ammo);
int GetSargeWeapon(int whichweapon);
void SetSargeWeapon(int whichweapon, int eWeapon);
BOOL ActivateSargeWeapon(SARGE*	pSarge, int whichweapon);
void ActivateNextSargeWeapon(SARGE*	pSarge);
int SargeGetActiveWeapon(int eArmy);
void SargeActivateNextWeapon(void);
int IsSargeWeaponReady(void);
void SargeFiringPosition(SARGE* pSarge, SPOINT *pt);

int GetSargeHealthPercentage(void);
int GetVehicleHealthPercentage(void);
int GetNumAirDrops(void);
int GetNumAirStrikes(void);
int GetNumRecons(void);
int UseUpAirDrop(int eArmy);
int UseUpAirStrike(int eArmy);
int UseUpRecon(int eArmy);
int GetSargeVehicle(void);
void SargePickupWeapon( SARGE * pSarge, ITEM * pItem, BOOL nosound=FALSE);
void SargeDoPickupWeapon( SARGE * pSarge, ITEM * pItem, BOOL nosound=FALSE);
BOOL SargeHitByMissile(SARGE* pSarge, SHORT height);
int GetSargeQuestItem( void );
void SetSargeAnimType(SARGE *pSarge);
SARGE *GetSargeOnTile( int x, int y );

void fillAirSupport(void);

void SargeFree(SARGE* pSarge);

void SargeDropWeapon( SARGE * pSarge, SPOINT position, SARGE_WEAPON slot );
void SargeDoDropWeapon( SARGE * pSarge, SPOINT position, SARGE_WEAPON slot );
void SargeDown();
void SargeTalk();
void SargeEndTalk();

int isSargeUntrafficable(SARGE* pSarge,SPOINT ept, ITEM *pItemList = (ITEM *)(-1));

void Sarge_KDn_Stand(UINT nChar, UINT nFlags);
void Sarge_KDn_Kneel(UINT nChar, UINT nFlags);
void Sarge_KDn_Prone(UINT nChar, UINT nFlags);
void Sarge_KDn_Up(UINT nChar, UINT nFlags);
void Sarge_KDn_Down(UINT nChar, UINT nFlags);

// control of sarge
void		GetUserInput();

void drawSargeTrafficability(void);
SARGE_WEAPON WeaponSlot(ITEM* pItem);

void SetSargeInvulnerable(int army_color);
void SetSargeNormal(int army_color);

int GetSargeAnimType(int eWeapon);
void AutoTuneStrength(SARGE *pSarge, BOOL nomax = FALSE);

#endif		// __SARGE_H__

//=========================================================================
//								EOF
//=========================================================================
