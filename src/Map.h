/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Map.h $
//
//	DESCRIPTION:	the map structure interface
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, May 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Map.h 107   4/18/98 12:48p Bwilcox $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/Map.h $
//  
//  107   4/18/98 12:48p Bwilcox
//  created xtriggers, moved trigger_branch to it, added
//  xtrigger_sargecarried
//  
//  106   4/12/98 3:34p Bwilcox
//  
//  105   4/09/98 4:31p Nrobinso
//  mark object pieces after the first one
//  
//  104   4/06/98 11:05p Nrobinso
//  add SetAISargeView
//  
//  102   4/02/98 3:07p Phu
//  typecast to avoid warnings
//  
//  101   3/31/98 12:59p Bwilcox
//  dispell fog
//  
//  100   3/26/98 1:35p Dmaynard
//  Added Checksumming of all Script files listed in the rule file
//  
//  99    3/26/98 6:42a Bwilcox
//  blowitem added to header, added when weapon is unplaced
//  
//  98    3/11/98 7:24p Phu
//  crush damage when set to last damage sprite
//  
//  97    98-03-11 11:06 Dmaynard
//  
//  96    3/10/98 7:24p Nrobinso
//  read multiple scripts from rule file
//  
//  95    3/10/98 4:02p Nrobinso
//  first in script list is header.txt
//  
//  94    3/10/98 3:58p Nrobinso
//  keep a list of script names in map
//  
//  93    3/07/98 11:54p Nrobinso
//  setup macro for debug layer
//  
//  92    2/20/98 3:40p Nrobinso
//  remove unsued code
//  
//  91    2/16/98 9:29a Nrobinso
//  make checksum unsigned longs
//  
//  90    2/12/98 8:55p Phu
//  mortar screen scroll, better force of gravity
//  
//  89    2/08/98 5:15p Nrobinso
//  move script override out of map, otherwise it gets cleared
//  
//  88    2/07/98 6:07p Nrobinso
//  multiple maps may share a rule file for multiplayer; remote display bug
//  remains
//  
//  87    2/02/98 3:22p Bwilcox
//  
//  86    1/29/98 5:51p Bwilcox
//  unit names system changed
//  
//  85    1/28/98 1:25p Bwilcox
//  fixed load/free stuff
//  
//  84    1/28/98 11:32a Bwilcox
//  more edit trafic code
//  
//  83    1/27/98 12:18p Bwilcox
//  removeditems of army when army delete
//  
//  82    1/22/98 12:00p Nrobinso
//  add checksum load
//  
//  81    1/17/98 9:23p Nrobinso
//  move the explosion toggle to debug
//  
//  80    1/17/98 8:56p Nrobinso
//  ChangeButtonAction changes the explosion type
//  
//  79    1/17/98 8:16p Nrobinso
//  add interface routine to get map view
//  
//  78    1/14/98 4:29p Bwilcox
//  replaced cansee/canshoot coding
//  
//  77    1/07/98 3:26p Phu
//  fix object owner numbering bug, undeploy unused objects
//  
//  76    1/05/98 2:13p Phu
//  stratmap now matches boundrect
//  
//
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __MAP_H__
#define __MAP_H__

#ifndef __TILE_H__
#include "Tile.h"
#endif

#ifndef __OBJECT_H__
#include "Object.h"
#endif

#ifndef __TEXT_H__
#include "Text.h"
#endif

/////////////////////////////////////////////////////////////////////////////
#define FILENAME_SIZE 33

#define SCRIPT_NAME_SIZE 64
#define SCRIPT_NAMES 16

#define	MAX_LAYERS 10

#define NO_TILE		((SHORT) -1)
#define NO_OBJECT	((LONG) -1)

#define OWNER(n) ((int) (((n) & 0x7)) - 1)
#define ELEVATION(n) ((int) (((n) & 0xF0) >> 4))

#define PT_TRAFFICABILITY(pt) (the_map.movement_layer[IPOINT_FROM_SPOINT(pt)])

#define IndexOf(x,y)  (((y) << the_map.bitwidth) + (x))
#define IndexOfWorldPos(pt)  (IndexOf( (pt).x >> 4, (pt).y >> 4 ))


// map redraw flags
#define REDRAW_FALSE	0
#define REDRAW_FULL		1
#define REDRAW_PARTIAL	2


// trigger flags (created from the map editor)
#define	TRIGGER_CLEAR			(ULONG)0x00000000
#define	TRIGGER_WATER			(ULONG)0x00000001
#define	TEMPORARY_OBJECT		(ULONG)0x00000002
#define	TRIGGER_DESTROYED		(ULONG)0x00000004
#define	TRIGGER_STRATEGIC		(ULONG)0x00000008
#define	TRIGGER_INVISIBLE		(ULONG)0x00000010
#define	TRIGGER_UNDEPLOYED		(ULONG)0x00000020
#define	TILE_UNTRAFFICABLE		(ULONG)0x00000040 //for tiles
#define TRIGGER_CHANGED			(ULONG)0x00000040 //for objects
#define TILE_CONTOUR			(ULONG)0x00000080
// xtended trigger flags (created from within the game)
#define XTRIGGER_BRANCH			(ULONG)0x00000080
#define XTRIGGER_SARGECARRIED	(ULONG)0x00000040



// movement values
#define	BLOCK_ALL	16
#define	ALLOW_ALL	-16

#ifdef FINAL
	#define	SET_DEBUG_LAYER(index, value)
	#define	DEBUG_LAYER(index)
#else
	#define	SET_DEBUG_LAYER(index, value) the_map.debug_layer[index] = value
	#define	DEBUG_LAYER(index) the_map.debug_layer[index]
#endif


typedef struct 
{
	RECT box;
	char overlap_list[2048];
} ITEM_OVERLAP;


// MAPQ object information structure
typedef struct
{
	int				eObjType;		// type of object in the list.
									// defines how to access the pointer.
	ULONG			bFlags;			// Bit-Field Flags
	union	OBJECTS					// Pointer to object
	{
		UNIT*		pUnit;			// WORLD unit object (Light/Heavy Infantry, Commandos, etc. )
		VEHICLE*	pVehicle;		// WORLD vehicle object (jeep, tank, boat, etc.)
		OBJECT*		pAsset;			// WORLD asset object (Mainbase, Turret, gate, etc.)
		OBJECT*		pStructure;		// WORLD modifiable object (bridges, gates, trees, etc.)
		OBJECT*		pObstacle;		// WORLD fixed object (rocks, forrests, walls, etc.)
	};
} MAPQ;

// MAPQ linked list structure
typedef struct qLink
{
	MAPQ*			pMapQObject;	// MapQ object information
struct	qLink*		pPrev;			// previous object in list
struct 	qLink*		pNext;			// next object in list
} MAPQLINK;

typedef struct	{
	SBOX box;
	SHORT *tile_array;
} Layer;


typedef struct	{
	char	map_name[FILENAME_SIZE];
	char	terrain_name[FILENAME_SIZE];
	char	tile_name[FILENAME_SIZE];

	long	width;
	long	height;      //both in pixels
	long	bitwidth;
	long	xmask;

	SBOX	TileBox;	 //what's currently on screen
	SBOX	PixelBox;    //what's currently on screen

	SBOX	FullPixelBox;  //the entire map 
	RECT	FullPixelRect; //the entire map

	RECT	screenrect,				//For the display engine
			oldscreenrect;

	RECT	boundrect;				//Viewable portion of map (pixels)
	RECT    tileboundrect;			//Viewable portion of map (tiles)
	RECT	sargeboundrect;			//Slightly smaller than boundrect
	RECT	limitboundrect;			//Kill if tries to move out of this area
	int		quake_time;
	float	quake_offsx;
	int		quake_velx;
	float	quake_offsy;
	int		quake_vely;
	int		quake_maxoffs;

	SPOINT  CurCenterPoint;       //where the center of the screen currently is
	SPOINT  RequestedCenterPoint; //this is what anyone sets who wants to move the screen 

	SPOINT OldTilePoint;

	TileSet	pTiles;

	long	num_layers;
	Layer	layers[MAX_LAYERS];

	BOOL	redraw;

	long	num_objects;
	OBJECT	*objects;

	short	max_objs[NUM_OBJECT_TYPES];
	OBJECT_SPRITE	*obj_sprite_array_list[NUM_OBJECT_TYPES];

	short	num_objs[NUM_OBJECT_TYPES];
	OBJECT	*obj_type_list[NUM_OBJECT_TYPES];

	short num_animated_objects;
	ANIMATED_OBJECT animatedobjects[MAX_NUM_ANIMATED_OBJECTS];

	unsigned char  *bit_pads_layer;			// 8 bits, one for each of 8 pads
	unsigned char  *numeric_pads_layer;		// 8 bits, numbered pads (8-255)
	signed char		*movement_layer;		// 8 bits  Movement
	unsigned char	*patchmovement_layer;	// 8 bits  overriding movement
	union	{
		unsigned char	*elevation_layer;	// bits 4-7  Elevation
		unsigned char	*owner_layer;		// bits 0-3  player owner
	};
	unsigned char	*triggers;				// bits 0-7  Triggers 1-8
	unsigned char   *vis_layer;

	TObjectLayer	groundlayer,
					orderedlayer,
					toplayer,
					overlaylayer;

	int num_script_names;
	char *script_names[SCRIPT_NAMES];

	char objfilename[SCRIPT_NAME_SIZE];

	char *missiontext;
	char *objtext;

#ifndef FINAL
	signed char		*debug_layer;			// visible debugging layer
#endif

	char *desc;
} Map;

/////////////////////////////////////////////////////////////////////////////
extern	Map			the_map;
extern	MAPQLINK*	MAPQquadMap;				// quadrant map data
extern	int			MAPQwidthSearch;			// quadrant search width
extern	int			MAPQheightSearch;			// quadrant search height
extern	int*		MAPQquadIndecies;			// quadrant indecies list
typedef enum
{
    NORMAL_VIEW,						
    CROSSHAIR_VIEW
} MAP_MODE;
extern 	MAP_MODE	map_mode;					// what view do we use
extern SPOINT	OFF_THE_MAP;					// 0,0 off the map
extern char brieffilename[SCRIPT_NAME_SIZE];

/////////////////////////////////////////////////////////////////////////////
//void SetMapWindow(SPOINT *basept);
void DisplayMap(void);
void InitObjects( void );
BOOL MapLoad(const char *pFilename);
unsigned long MapLoadSum(const char *pFilename);
BOOL MapGraphicsLoad();
void MapFree(void);
void MapGraphicsFree(void);
void ScrollMap(LONG x, LONG y);
void SetMapGameWindow();
void SetBackGameWindow();
void RefreshDebugBox(SBOX *pBox);
void RestoreTileData( void );
void InitTileCycler( void );
void FreeTileCycler( void );
void RemoveUnusedItems( void );
void RemoveUnusedItemsOfArmy(int eArmy );

int AttributeIndicies(RECT *pRect, int *indicies, int max);
char GetNextAttribute(SPOINT *pPos, SHORT facing);

// MAP quadrant search handling routines
BOOL	MapQInit( void );
void	MapQExit( void );
BOOL	MapQCreate( int eArmy, int eObjType, void* pObject, SPOINT* pPosition, USHORT bFlags );
void	MapQDelete( MAPQ* pMapq );
BOOL	MapQCreateQuad( MAPQ* pObject, SPOINT* pNewPos );
void	MapQUpdateQuad( int objType, void* object, SPOINT* oldPos, SPOINT* newPos );
BOOL	MapQDeleteEntry( MAPQ* pMapQObject );
void	MapQDeleteQuad( MAPQLINK* pQuad );
int		MapQWhichQuad( MAPQLINK* pObject );
int		MapQGetQuad( SPOINT* pPoint );
int		MapQFindQuads( int nQuadrant, int* pQuadIndecies );
void	MapQUpperLeft( SPOINT* pPoint, SPOINT* pUpperLeft );
void	MapAssetCreate( void );
void	MapAssetDeleteOfArmy(int eArmy );
int 	MapPadPosition(int pad,SPOINT* point);

//movement layer functions
void AddObjectToMovementLayer(OBJECT *pobj, 
							  ITEM_OVERLAP *pDamageOverlap = NULL, 
							  int nCrushDamage = 0 );
void SubtractObjectFromMovementLayer(OBJECT *pobj, ITEM_OVERLAP *pOverlap = NULL )	;

void UpdateAnimatedObjects(void);

void ChangeRButtonAction(void);

int    AlexRButtonDn (UINT nFlags, CPoint point);

#ifndef FINAL
	void	DisplayDebugLayer(COLORREF set);
	void	DisplayDebugInBox(SBOX *pBox);
	void	SetValueInDebugLayer(SHORT tilex, SHORT tiley, char value);
#else
	#define DisplayDebugLayer(a)
	#define DisplayDebugInBox(a)
	#define SetValueInDebugLayer(a,b,c)
#endif


#endif


//Script related functions
char *GetMissionText(int mission);
char *GetObjectText(int mission);

void ProcessMapPosition(void);
SBOX GetMapPosition(void);
void NewScrollMap(short x, short y);
void ScrollMapReturn(short x, short y, short *xscrolled, short *yscrolled);
void MapLookAtPoint(int x, int y);
void MapJumpToPoint(int x, int y);
void MapUndoScrolling(void);

void MapLookAtAnim(ANIM *pAnim, BOOL LookAhead, BOOL Reverse, int MinimumDistance);
void MapJumpToAnim(ANIM *pAnim, BOOL LookAhead, BOOL Reverse, int MinimumDistance);


void ResetMapWindow(void);

void MapRemoveObject(OBJECT *pObject);
void MapPlaceObject(OBJECT *pObject, SPOINT *where);

BOOL IsLosClear( SPOINT &start_tilepos, SPOINT &end_tilepos, ITEM *pItem );
BOOL IsLosClearByTile( int start_tile, int end_tile, ITEM *pItem );

BOOL ObjectHitByMissile(OBJECT* pObject, SHORT height);
void ProcessPadLayer();

void SetupQuake( SPOINT &wpos, int intensity );
void StartQuaking( int time, int vel_x, int vel_y, int max_offs );
void DoTheQuake( void );
void ValidateMap();
int  GetItemPov( ITEM *pItem );

int  InBoundsRect( SPOINT &pt );

void SetScriptName(char *pScript, int number);
void BlowItem(ITEM* pItem);
void ReleaseScriptNames();
DWORD FileXSum(char *name);
DWORD ScriptFileXSum(char *name);

void SetAISargeView(SARGE *pSarge);
