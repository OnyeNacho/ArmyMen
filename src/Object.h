//========================================================================
//	FILE:			Object.h
//
//	DESCRIPTION:	Object defines, structures, and prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Monday, June 17, 1996
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//=========================================================================

#ifndef __OBJECT_H__
#define __OBJECT_H__

#ifndef __SPRITE_H__
#include "Sprite.h"
#endif

#include "scripts.h"
//=========================================================================

struct OBJECTSTRUCT	{
	ITEM	common;	// common components of all objects

	SHORT	category; // bush or tree or whatever
	SHORT	number;   // corresponds to the filename
	SHORT	index;    // index into sprite array. In 1-1 correspondence with number

	unsigned char	attribute;
	signed char		movement;
	unsigned char	triggers;
	unsigned char	xtriggers; // game extended triggers
	unsigned char	howmany;
	unsigned char	elevation;
	char			owner;
	unsigned char   flames;
	unsigned char	damageindex; //which damage sprite to show (0=undamaged)
	unsigned char   visibility;
	unsigned char   permeability;
	signed char		armor;
	unsigned char	group;

	ANIMCELL	cell;

	OBJECT *nextsubobject, *prevsubobject; 
	  //link together the subobjects in, for example, a building made up
	  //of four small objects so it can be damaged in sections

	SCRIPTED_OBJECT *sobj;
	EObjectLayer	layer;
	long			timer;
} ;

typedef struct {
	short nLevelsOfDamage; //1=normal. 2=normal+destroyed. 3=normal+damage+destroyed. etc.
	short nAnimFrames;
	short nAnimDelay; //0=full speed. 1= half speed. 2= 1/3 speed, etc.
	SPRITE *sprites;
} OBJECT_SPRITE;

typedef struct {
	OBJECT *pObj;
	short curframe;
	short curcounter;
} ANIMATED_OBJECT;

#define MAX_NUM_ANIMATED_OBJECTS 100


typedef enum {
	OBJECT_TREE = 0,
	NUM_OBJECTS
} OBJECT_NUMBERS;

extern SPRITE objects[NUM_OBJECTS];

// object categories
typedef enum {
	ROCK = 0,
	BUSH,
	TREE,
	BIG_TREE,
	FALLEN_TREE,
	FENCE,	// 5
	WALL,
	BRIDGE,
	FOOT_BRIDGE,
	EXPLOSIVES,
	GUN_TURRET,	// 10
	AA_GUN,
	BASE,
	AUX_BASE,
	AIR_STRIP,
	HELI_PAD,	// 15
	PRISON_CAMP,
	BUILDING,
	PILL_BOX,
	POWER_PLANT,
	GATE,		// 20
	WALL_GATE,
	RADAR_BUILDING,
	MISCELLANEOUS,
	OVERPASS,
	SPECIAL_ITEMS,	// 25

	NUM_OBJECT_TYPES
} OBJECT_TYPES;

#define OBJECT_OWNER(pobj) ((int) (pobj)->owner)
#define OBJECT_ELEVATION(pobj) ((int)(pobj)->elevation)

typedef struct
{
	long nUid;

	int strength;
	int curframe;
	SPOINT	position;
	SPOINT	cellpos;
	char triggers;
	char xtriggers;
    short	nAmmo;
	char	owner;
} OBJECT_SAVE_INFO_STRUCT;


//=========================================================================
//							PROTOTYPES
//=========================================================================
extern	BOOL		AssetInit( void );
extern	void		AssetExit( void );
extern	BOOL		AssetCreate( ARMY_TYPE eArmy, OBJECT* pNewAsset, SPOINT* pPosition );
extern	OBJECT*		ObjectFind( ULONG nUniqueID );
extern	BOOL		AssetInFiringRange( OBJECT* pAsset );
extern	void		AssetSetDirection( OBJECT* pAsset, int direction );
extern	void		AssetFireWeapon( OBJECT* pAsset, ITEM *pTarget );
extern	void		AssetKill( OBJECT* pAsset );

extern	void		SaveObjectChanges(FILE* pSaveFile);
extern	void		RestoreSavedObjects(FILE* pSaveFile);

#define AssetFind(id) ObjectFind(id)

//=========================================================================
//								EOF
//=========================================================================
#endif
