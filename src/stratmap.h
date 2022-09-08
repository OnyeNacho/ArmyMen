/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: stratmap.h $
//
//	DESCRIPTION:	Headers for displaying and managing the strategic map
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Wednesday, June 4, 1997
//
//	REVISION:		$Header: /ArmyMen/src/stratmap.h 21    4/09/98 2:16p Bwilcox $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/stratmap.h $
//  
//  21    4/09/98 2:16p Bwilcox
//  paper blink on, fix colors to see
//  
//  19    3/31/98 11:56a Bwilcox
//  stratmap overlay removal
//  
//  18    3/25/98 7:52a Bwilcox
//  allow scripts to name new objects strategic that werent marked before
//  
//  17    2/02/98 1:08a Nrobinso
//  move unit selection to ui.cpp
//  
//  16    1/19/98 4:01p Phu
//  blink red if engaged
//  
//  15    1/19/98 1:12p Phu
//  strategic items
//  
//  14    1/14/98 10:41a Phu
//  keep track of strategic weapon objects on stratmap
//  
//  13    12/14/97 7:33p Phu
//  
//  12    12/12/97 1:10p Phu
//  
//  11    12/09/97 12:12p Phu
//  
//  10    10/31/97 11:29a Awerner
//  Air strikes now deal with visibility properly, and fixed memory leak
//  
//  9     10/27/97 11:29a Aburgess
//  new SM_DrawStrategicMapFront() prototype
//  
//  8     10/14/97 2:01p Awerner
//  Fixed crashing bug with auxiliary sarge pins
//  
//  7     10/10/97 3:47p Awerner
//  The small map is now fully funcitonal, although I've commented out the
//  drawing of the dots, because it's _very_ slow right now
//  
//  5     7/30/97 3:27p Awerner
//  The strategic map now has a 13-pixel border around it
//  
//  4     7/29/97 11:04p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
//  
//  3     7/22/97 11:27a Awerner
//  Improved the strat map pin handling
//  
//  2     7/21/97 5:10p Awerner
//  Updated strategic map code with new art, displayed vehicles and the
//  overlay layer
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  3     6/19/97 3:24p Awerner
//  Strategically important objects now get X-ed out on
//  the strategic map when they're destroyed
//  
//  2     6/12/97 4:10p Awerner
//  The strategic map is now more-or-less functional
//  
//  1     6/05/97 3:01p Awerner
//  Initial checkin
//  
//  1     6/04/97 4:17p Awerner
//
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#ifndef _STRATMAP_H_ 
#define _STRATMAP_H_

#ifndef _ARMY_H_
#include "army.h"
#endif

#ifndef _SPRITE_H_
#include "sprite.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// defines and typedefs
/////////////////////////////////////////////////////////////////////////////


#define MAPSTATE_UNLOADED 0
#define MAPSTATE_LOADED 1 //graphics have been loaded
#define MAPSTATE_READY 2  //pin positions have been updated, ready to draw

#define PINTYPE_UNUSED 0
#define PINTYPE_SARGE 1	//squads and assets
#define PINTYPE_UNIT 2	//sarge and vehicles
#define PINTYPE_VEHICLE 3  //vehicles
#define PINTYPE_OBJECT 4


#define MAP_PIN_NONE -1

typedef struct XOUT //the big X that indicates that an object is destroyed
{
	ITEM *pItem;
	BYTE visible; //boolean
	SPOINT screenloc;
} XOUT;



typedef struct PIN 
{
	ITEM *pItem;
	BYTE pintype;
	char whosepin; //which army it belongs to
	BYTE isvisible;

	SPOINT screenloc;
	DWORD lastupdate;
	char state;
} PIN;

typedef struct STRATMAP
{
	int mapstate;
	
	SPRITE mapsprite;
	float xscale,yscale; //world map positions times the scale values
						 //give positions in the map sprite

	int numpins;
	PIN *pPins;

	SPOINT onscreenloc; //upper left corner of the map on screen

} STRATMAP;


/////////////////////////////////////////////////////////////////////////////
// Function Prototypes
/////////////////////////////////////////////////////////////////////////////
STRATMAP* SM_InitStrategicMap(void);
int SM_LoadStrategicMapGraphics(STRATMAP *map);
int SM_UnLoadStrategicMapGraphics(STRATMAP *map);
int SM_FreeStrategicMap(STRATMAP *map);
int SM_DrawStrategicMap(STRATMAP *map);
int SM_DrawStrategicMapFront(STRATMAP *map);
int SM_UpdateStrategicMap(STRATMAP *map);
int SM_ProcessMouse(STRATMAP *map, POINT *screenloc, SPOINT *worldloc);
void SM_ClearSelected(STRATMAP *map);
void SM_SetSelected(STRATMAP *map, UNIT *pUnit);
void SM_StratMapOneFrame(STRATMAP *map);
void SM_StratMapMouseClick(STRATMAP *map, POINT *pPoint);
void SM_ToggleStrategicMap(void);
void SetStratmapStrategic(ITEM* pItem);



/////////////////////////////////////////////////////////////////////////////
// Extern defines for global variables
/////////////////////////////////////////////////////////////////////////////


extern UNIT *curselectedunit;
extern STRATMAP *curstratmap; //should be set to null whenever there's no map

#endif



