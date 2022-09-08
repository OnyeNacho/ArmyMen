#ifndef __TROOPER_H   
#define __TROOPER_H   

#define TROOPER_AVATAR(x)  ((x)->pAvatar)
#define TROOPER_UNIT(x)  ((UNIT*) (((TROOPER*)(x))->pUnit))


#define TROOPER_ALIVE(x) ((x)->mode == TROOPER_ALIVE)
#define TROOPER_HEALTHY(x) ((x)->common.nStrength > 0)

            // subroutines with side effects
// game startup routines
int TrooperSystemLoad();
void TrooperCreate(UNIT* pUnit,TROOPER* pTroop, TROOPER_TYPE eTroopType);

// enter a trooper into play
void TrooperDeploy( TROOPER* pTroop, SPOINT position, short facing );
void TrooperAssignToUnit(TROOPER* pTroop,UNIT* pUnit);
    
// simulation update routines
void TroopersInactive(UNIT* pUnit);
void TroopersActive(UNIT* pUnit);
void TroopersStill(UNIT* pUnit,SPOINT* facePoint);
void TroopersMove(UNIT* pUnit,SPOINT position);
void TroopersFight(UNIT* pUnit);
void TroopersUpdateAvatars(UNIT* pUnit);
void TrooperKill( TROOPER* pTrooper );
void TrooperGone( TROOPER* pTrooper );
void TrooperUpdateInfluence( TROOPER* pTrooper, BOOL bNew );
void TrooperDamage(TROOPER* pTrooper, int nDamage, int nType, SPOINT* pFrom,UID fromUID);
void TrooperFireWeapon(TROOPER* pTrooper);
void TrooperSetFire(TROOPER* pTrooper, int facing);
BOOL TrooperHitByMissile(TROOPER* pTrooper, SHORT height);
void DrawTrooperChevron( TROOPER *pTrooper );
void TrooperAirCenter(SPOINT at);

int CanShoot(WEAPON* pWeapon,ITEM *pItem,IPOINT to);

// exit a trooper from play
void TrooperPickup( TROOPER* pTrooper);

// game wind-down routines
void TrooperDelete( TROOPER* pTroop );
void TrooperSystemFree();


// debug code
void TrooperTestCreate(ARMY_TYPE army_type, TROOPER* pTrooper,TROOPER_TYPE eTroopType);


        // informational functions about a specific trooper (no side effects)
TROOPER* TrooperFind(LONG nUniqueID);

void ShowTile(IPOINT where);
void ShowXY(int x,int y);
void ShowSpoint(SPOINT x);
int XY2Tile(int x,int y);
void TrooperAcceptDamage(TROOPER* pTrooper,int nDamage,int nDamageType,SPOINT pFrom,UID fromUID);

#endif
