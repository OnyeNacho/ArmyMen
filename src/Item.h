//========================================================================
//	FILE:			Item.h
//
//	DESCRIPTION:	Item defines, structures, and prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Monday, June 17, 1996
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unuathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//=========================================================================

#ifndef __ITEM_H__
#define __ITEM_H__

extern char Allah;

#define ITEM_SEEN_WHEN(x,by)	(((ITEM*)(x))->seen[by])
#define ITEM_SEEN_THIS_TURN(x,by)	((DWORD)(ITEM_SEEN_WHEN(x,by)) == gpGame->dwAnimTime)
#define ITEM_SEEN_WHERE(x,by)	(((ITEM*)(x))->seenWhere[by])
#define ITEM_RECENTLY_SEEN(x,by)	ItemVisible((by),(ITEM*)(x))


#define ITEM_SET_VISIBLE(p) ((p)->bItemFlags &= ~ITEM_INVISIBLE)
#define ITEM_SET_INVISIBLE(p) ((p)->bItemFlags |= ITEM_INVISIBLE)

#define ITEM_SET_STRATEGIC(p) ((p)->bItemFlags |= ITEM_STRATEGIC)
#define ITEM_SET_NONSTRATEGIC(p) ((p)->bItemFlags &= ~ITEM_STRATEGIC)
#define ITEM_IS_STRATEGIC(p) ((p)->bItemFlags & ITEM_STRATEGIC)

// is this object controlled by this machine (player or ai)
extern int IRunArmy(int eArmy);
#define IS_LOCAL_ITEM(x) (IRunArmy(ITEM_ARMY(x)))
#define IS_LOCAL_ARMY(x) (IRunArmy(x))

// expand in rects to or from item
typedef long (*FANFUNC)(IPOINT index); 	// define a fanout function
extern ITEM* fanoutItem;
extern IPOINT maxFanIndex;
extern long maxFanDistance;
extern IPOINT propogateAt;
long ItemFanIn(ITEM* pItem,IPOINT at, int limit,FANFUNC func);
long ItemFanOut(ITEM* pItem,IPOINT at,int limit,FANFUNC func);
long PropogateTrafficable(ITEM* pItem,IPOINT at, int limit,FANFUNC func);
int TileLineCheck(IPOINT from, IPOINT to, FANFUNC func);


char* ItemDBName(void* pObj);
void ItemSetUID(void* pObj,int eArmy,int eObjType,int eSubType1,int eSubType2);
void ItemSetLocation(void* pObj,SPOINT* point);
void ItemSetOldLocation(void* pObj);
int ItemPower(ITEM* pAttacker, ITEM* pTarget);
BOOL ItemVisible(int eArmy,void* pObject);
BOOL ItemUserVisible(int eArmy,void* pObject);
BOOL ItemRecentlyVisible(int eArmy,void* pObject);
void ItemMakeVisible(void* pItem);
void ItemClearOldLocation(ITEM *pItem);
void See(int eArmy,ITEM* pItem);

void ItemUpdateTad(ITEM* pItem);
void ItemUpdateSeen(ITEM* pItemFrom,ITEM* pItemTo);

void ItemUpdatePosition(ITEM* pItem,SPOINT* position);
void ItemSpecialUpdatePosition(ITEM* pItem,SPOINT* position);

void ItemSetLabel(ITEM *pItem, char *pText);
void ItemFreeLabel(ITEM *pItem);

void ItemAwardPoints( ITEM *pItem, int eArmy );
int	 CanSeeFromItem(ITEM* pFrom, IPOINT to);
ITEM* ItemContainedBy(ITEM* pItem);

SPOINT ItemCenterPos(ITEM* pItem);
SPOINT ItemDeadPosition(ITEM* pItem);

extern	int		GetItemHeight( ITEM *pItem );
extern  int		GetItemHeightNoElevation( ITEM *pItem );
extern	int		GetElevationHeightAtItem( ITEM *pItem );



#endif