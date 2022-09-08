#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#ifndef __OBJECT_H__
#include "object.h"
#endif

#define EXPLOSION_PATHNAME FLASH_PATH

#define NUMACTIVEEXPLOSIONS 400

#define EXPLODINGVEHICLEDAMAGE 20


//the following structures and constants are needed for the interface
//which finds which objects are being damaged by a particular explosion
typedef struct 
{
	short xsize, ysize, xoffset, yoffset;
	char *damageamounts;
} EXPLOSIONPATTERN;


typedef struct 
{
	RECT box;
	char *damageamounts;
} EXPLOSIONQUERY;

typedef struct
{
	ITEM *pItem;
	char maxdamage;
} EXPLODEDOBJECT;

typedef struct
{
	short numobjects;
	EXPLODEDOBJECT *objects;
} EXPLOSIONRESULT;


// used to set up different kinds of explosions
typedef struct
{
	BOOL				bExplode;	// will cause an explosion
	COMMAND_NUMBERS		eExplosion;	// explosion to use
	EXPLOSIONPATTERN*	pPattern;	// explosion pattern to use
	ULONG				audioID;
} EXPLOSION_DATA;


/*this next struct stores all the info needed by the damaging part of an
 *explosion. It's all stored in an anim struct when the anim is doing the
 *animated part of the explosion, so that the callback from the anim
 *struct can do the actual damage done by the explosion
 */
typedef struct
{
	short x,y;
	short damagetype;
	EXPLOSIONPATTERN *pattern;
	int maxdamage;
	ITEM *objtoexclude;
	int explosiontype;
	UID fromUID;
} EXPLOSIONCALLBACKINFO; 


// standard explosion patterns
extern EXPLOSIONPATTERN SmallExplosion;
extern EXPLOSIONPATTERN MediumExplosion;
extern EXPLOSIONPATTERN LargeExplosion;

void GetExplosionObjects(EXPLOSIONQUERY *pQuery, EXPLOSIONRESULT *pResult);

int LoadExplosions(void);
int UnloadExplosions(void);
void InitExplosions(void);
void FreeExplosions(void);
void ShowExplosion(COMMAND_NUMBERS explosiontype, short x, short y, int delay);
void UpdateExplosions(void);
void inline DoExplosion(short x, short y, COMMAND_NUMBERS explosiontype, EXPLOSIONPATTERN *pattern, 
				int damagetype, int maxdamage,	ITEM *objtoexclude , BOOL transmit, UID fromUID, ULONG audioID);
void DoDelayedExplosion(short x, short y, COMMAND_NUMBERS explosiontype, EXPLOSIONPATTERN *pattern, int damagetype, 
				 int maxdamage, ITEM *objtoexclude, BOOL transmit, int delay, UID fromUID, ULONG audioID);
void CoverObjectWithExplosions(OBJECT *pObj, int numtypes, COMMAND_NUMBERS *explosiontypes, 
				BOOL onlyiflarge, UID fromUID = 0 );
void DoWeaponExplosion(ITEM *pItem, int damagetodo, int damagetype, SPOINT *damageloc, EXPLOSION_DATA *pExplode, UID fromUID = 0);

#endif

