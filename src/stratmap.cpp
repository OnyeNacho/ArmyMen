/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: stratmap.cpp $
//
//	DESCRIPTION:	Code for displaying and managing the strategic map
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Wednesday, June 4, 1997
//
//	REVISION:		$Header: /ArmyMen/src/stratmap.cpp 104   4/13/98 1:38p Nrobinso $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/stratmap.cpp $
//  
//  104   4/13/98 1:38p Nrobinso
//  start audio once briefing is drawn
//  
//  103   4/10/98 3:24p Nrobinso
//  turn blinks off by default
//  
//  102   4/09/98 3:50p Bwilcox
//  perim fast test matches astar
//  
//  101   4/09/98 2:26p Bwilcox
//  
//  100   4/09/98 2:19p Bwilcox
//  
//  99    4/09/98 2:15p Bwilcox
//  paper blink on, fix colors to see
//  
//  98    4/09/98 9:44a Bwilcox
//  
//  97    4/09/98 9:25a Bwilcox
//  syncopate army blink to distinsuish armies
//  
//  96    4/06/98 12:16p Bwilcox
//  blink enable for paper map
//  
//  95    4/06/98 12:42a Bwilcox
//  
//  94    4/05/98 6:08p Bwilcox
//  
//  93    4/05/98 5:57p Bwilcox
//  
//  91    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  90    3/31/98 11:55a Bwilcox
//  stratmap overlay removal
//  
//  89    3/27/98 1:49p Phu
//  survive ALT_TAB dammit
//  
//  88    3/25/98 3:05p Bwilcox
//  fixed break i did
//  
//  87    3/25/98 7:52a Bwilcox
//  allow scripts to name new objects strategic that werent marked before
//  
//  86    3/25/98 7:26a Bwilcox
//  
//  85    3/25/98 7:22a Bwilcox
//  pins of foes drawn after pins of yours (for flag overlay multiplayer)
//  
//  84    3/17/98 12:40p Bwilcox
//  when army gets deleted, delete stratmap elements
//  
//  83    3/16/98 1:31p Bwilcox
//  appearances of dots differ in multiplayer, single player, and strategic
//  values
//  
//  82    3/15/98 7:43a Bwilcox
//  better isstrategic pin proceesing
//  
//  81    3/15/98 7:04a Bwilcox
//  
//  80    3/14/98 2:26p Bwilcox
//  stratmap ordering pin fixes
//  
//  79    3/08/98 4:40p Phu
//  don't show pins for units in vehicles
//  
//  78    3/07/98 11:53p Nrobinso
//  move .h file to stdafx
//  
//  77    2/25/98 5:40p Nrobinso
//  add vehicle.h
//  
//  76    2/19/98 1:34p Bwilcox
//  making force color more obvious on stratmap for color-impaired
//  
//  75    2/18/98 2:30p Bwilcox
//  stop air recon from using allah mode to do its dirty work
//  
//  74    2/17/98 3:09p Phu
//  don't show dead vehicles on stratmap
//  
//  73    2/17/98 2:33p Bwilcox
//  stop progressive reveal
//  
//  72    2/12/98 2:51p Bwilcox
//  stratgic forces are made fully visible.
//  
//  71    2/07/98 2:33p Phu
//  let's have the correct colors on the stratmap please
//  
//  70    2/02/98 1:08a Nrobinso
//  move unit selection to ui.cpp
//  
//  69    1/30/98 4:18p Nrobinso
//  the "overlay" map being revealed is called mapname.bmp, the originally
//  displayed map is called mapname_dk.bmp
//  
//  68    1/28/98 5:22p Phu
//  
//  67    1/27/98 3:46p Bwilcox
//  
//  66    1/27/98 3:04p Bwilcox
//  pins wont display now if army goes away
//  
//  65    1/27/98 2:21p Phu
//  assign pObject to the object
//  
//  64    1/26/98 12:03p Nrobinso
//  new path defines
//  
//  63    1/22/98 6:44p Nrobinso
//  use SetPath
//  
//  62    1/19/98 4:01p Phu
//  blink red if engaged
//  
//  61    1/19/98 3:24p Awerner
//  Added ALLY and UNALLY, MAKESTRATEGIC and MAKENONSTRATEGIC, and changed
//  get_ and drop_ to take specific item names
//  
//  60    1/19/98 1:12p Phu
//  strategic items
//  
//  59    1/14/98 10:41a Phu
//  keep track of strategic weapon objects on stratmap
//  
//  58    1/05/98 2:13p Phu
//  stratmap now matches boundrect
//  
//  ...
//  
//  2     6/05/97 3:02p Awerner
//  initial checkin of strategic map code
//  
//  1     6/04/97 4:17p Awerner
//
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
 
 
#include "stdafx.h"

#include "aiaccess.h"
#include "Army.h"
#include "mainfrm.h"
#include "comm.h"
#include "damage.h"
#include "Disp.h"
#include "gameflow.h"
#include "Map.h"
#include "miscfile.h"
#include "tad.h"
#include "input.h"
#include "unit.h"
#include "stratmap.h"
#include "text.h"
#include "item.h"
#include "sarge.h"
#include "event.h"
#include "vehicle.h"


#include "sprite.h"
static int freepins;
extern SPRITE	RecallSprite;


/////////////////////////////////////////////////////////////////////////////
// Local defintions
/////////////////////////////////////////////////////////////////////////////
#define MAXSTRATEGICOBJECTS 100

void ArmyNoticeStrategicWinItem(ITEM* pItem);

char blinkpaper = 0;
/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
extern char bDisplayPaperMap;
RECT onscreenmaprect = {523,389,609,475};



//these global variables are used to manage the unit selection and
//the strategic map
UNIT *curselectedunit=NULL;
STRATMAP *curstratmap=NULL; //should be set to null whenever there's no map


unsigned long PinBlinkRate[2] = {850,70};

BYTE pincolors[5];


struct TRGB 
{ int r,g,b; }
pinrgb[5][3] =
{
	{ // independent
		{255,0,0}
	},
	{	// green
		{0, 255, 0}
	},
	{	///tan
		{149, 122, 109}
	},
	{	//blue
		{54,54,255}
	},
	{	//gray
		{203,203,203}
	}
};


/////////////////////////////////////////////////////////////////////////////
// Function Prototypes
/////////////////////////////////////////////////////////////////////////////
float SM_MapX_To_ScreenX(STRATMAP *map, float mapx);
float SM_MapY_To_ScreenY(STRATMAP *map, float mapy);
float SM_ScreenX_To_MapX(STRATMAP *map, float screenx);
float SM_ScreenY_To_MapY(STRATMAP *map, float screeny);


/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

char return_string[32];


// this is the map as displayed at the very beginning
char *SM_GetStrategicMapFileName(void)
{
	sprintf( return_string, "%s.bmp", the_map.map_name );
	return( return_string );
}



///========================================================================
//	Function:		SM_InitStrategicMap()
//
//	Description:
//		Allocates and initializes a strategic map
//		structure
//
//	Input:			none
//
//	Ouput:			pointer to the allocated STRATMAP		
//
///========================================================================
STRATMAP* SM_InitStrategicMap(void)
{
	STRATMAP *map;
    UNIT* pUnit;
	LEGION* pLegion;
	int i,j, curpin=0;
	int numplayers=ARMY_LAST_ARMY;
    int who;
    freepins = 0;

	map=(STRATMAP*)malloc(sizeof(STRATMAP));

	if (!map)
	  return NULL;

    ZeroMemory(map, sizeof(STRATMAP));

    // tally the pins we will need

	for( i = 0; i < numplayers; i++ )// for the players forces
	{
		//	add one pin for each unit
        FOR_EACH_UNIT_TYPE(j)
			map->numpins += UnitAvailable(i,j);

		//	add one pin for each sarge
		if( SargePointer( (ARMY_TYPE)i ) )
			map->numpins++; 

		map->numpins += ArmyGetLegion(i)->nNumberOfVehicles;
	}

	for( i = 0; i < the_map.num_objects; i++ ) // for strategic objects
	{
		if( (the_map.objects[i].triggers & TRIGGER_STRATEGIC) &&
			(!(the_map.objects[i].triggers & TRIGGER_DESTROYED)) )
			map->numpins++;
	}


    // reserve 10 pins for MAKESTRATIC calls;
    freepins = 10;
    map->numpins += 10;


	map->pPins = (PIN *)malloc( sizeof(PIN) * map->numpins );
	if( map->pPins == NULL )
	{
		free(map);
		return NULL;
	}
	ZeroMemory( map->pPins, sizeof(PIN) * map->numpins );

	//	setup unit/sarge/vehicle pins (YOU FIRST so FOES show on TOP)
        
	for( i = 0; i < numplayers; i++ )
	{
		pLegion = ArmyGetLegion(i);
        FOR_EACH_UNIT(pLegion,pUnit)
		{
            map->pPins[curpin].pItem = (ITEM*)pUnit;
            map->pPins[curpin].pintype = PINTYPE_UNIT;
            map->pPins[curpin].whosepin = i + 1;
			map->pPins[curpin].lastupdate = 0;
			map->pPins[curpin].state = 0;
            curpin++;
		}
        for( int vehicle = 0; vehicle < pLegion->nNumberOfVehicles; ++vehicle )
        {
			map->pPins[curpin].pItem = (ITEM *)(pLegion->pLegionVehicles[vehicle]);
			map->pPins[curpin].pintype = PINTYPE_VEHICLE;
			map->pPins[curpin].whosepin = i + 1;
			map->pPins[curpin].lastupdate = 0;
			map->pPins[curpin].state = 0; // blink opposite
  			curpin++;
		}

		if( SargePointer( (ARMY_TYPE)i ) ) // sarge pin shows on top
		{
			map->pPins[curpin].pItem = (ITEM*)SargePointer( (ARMY_TYPE)i );
			map->pPins[curpin].pintype = PINTYPE_SARGE;
			map->pPins[curpin].whosepin = i + 1;
			map->pPins[curpin].lastupdate = 0;
			map->pPins[curpin].state = 0;
  			curpin++;
		}


        //	setup strategic object pins for this army
        for( j = 0; j < the_map.num_objects; j++ )
        {
            who = ITEM_ARMY(&the_map.objects[j]);
            if (who != i) continue;
            if( (the_map.objects[j].triggers & TRIGGER_STRATEGIC) &&
                (!(the_map.objects[j].triggers & TRIGGER_DESTROYED)) )
            {
                map->pPins[curpin].pItem = (ITEM *)(&(the_map.objects[j]));
                map->pPins[curpin].pintype = PINTYPE_OBJECT;
                map->pPins[curpin].whosepin = who + 1;
                map->pPins[curpin].lastupdate = 0;
				map->pPins[curpin].state = 0;
  
                curpin++;
            }
        }
	}

    //	setup strategic object pins for unowned
    for( i = 0; i < the_map.num_objects; i++ )
    {
		who = ITEM_ARMY(&the_map.objects[i]);
		if (who != ARMY_INDEPENDENT) continue;

        if( (the_map.objects[i].triggers & TRIGGER_STRATEGIC) &&
            (!(the_map.objects[i].triggers & TRIGGER_DESTROYED)) )
        {
            map->pPins[curpin].pItem = (ITEM *)(&(the_map.objects[i]));
            map->pPins[curpin].pintype = PINTYPE_OBJECT;
            map->pPins[curpin].whosepin =  1;
            map->pPins[curpin].lastupdate = 0; // use player army blink rate
			map->pPins[curpin].state = 0;
  
            curpin++;
        }
    }


	//	validate
	if( curpin > map->numpins )
	{
		TRACE( "FATAL ERROR: Found more stratmap pins than allocated slots\n" );
		ASSERT( 0 );
	}
	else if( curpin < map->numpins )
		map->numpins=curpin;

	//	setup pin colors
	for( i = 0; i < 5; i++ )
	{
		int color;
		
		if( i > 0 )					// translate from army to color
			color = gpComm->ColorFromIndex(i-1) + 1;
		else
			color = 0;

	
		
			pincolors[i] = GetNearestPaletteIndex(current_palette.hpal, 
				RGB(pinrgb[color][0].r, pinrgb[color][0].g, pinrgb[color][0].b) );
	
	}

	return map;
}




///========================================================================
//	Function:		SM_LoadStrategicMapGraphics()
//
//	Description:
//		Loads in all the graphics for a strategic map, and
//		sets the on screen position and scale factors properly
//
//	Input:			map		pointer to a STRATMAP struct
//
//	Ouput:			negative on error, zero or positive on success	
//
///========================================================================
int SM_LoadStrategicMapGraphics(STRATMAP *map)
{
	char *temp;
	int result=0;

	if (!map)
		return -1;

	if (map->mapstate!=MAPSTATE_UNLOADED)
		return 0;
	
	SetPath(STRATMAP_PATH);

	temp = SM_GetStrategicMapFileName();

	if (!temp)
		return -1;

	if (!LoadSprite( &map->mapsprite, temp, (BM_OPAQUE|BM_SYSTEMMEMORY) ))
	{
		TRACE( "ERROR: failed to load strategic map Sprite [%s:%d]\n\n", 
				 __FILE__, __LINE__ );
		return -1;
	}

	map->xscale=(float)(map->mapsprite.srect.right)/(the_map.boundrect.right - the_map.boundrect.left);
	map->yscale=(float)(map->mapsprite.srect.bottom)/(the_map.boundrect.bottom - the_map.boundrect.top);

	map->onscreenloc.x=(onscreenmaprect.left+onscreenmaprect.right)/2-map->mapsprite.srect.right/2;
	map->onscreenloc.y=(onscreenmaprect.bottom+onscreenmaprect.top)/2-map->mapsprite.srect.bottom/2;
//	TRACE("map onscreen loc is (%d, %d)\n", map->onscreenloc.x, map->onscreenloc.y);
	
	if (map->onscreenloc.x<onscreenmaprect.left)
	{
		TRACE("ERROR: map sprite too large for space allowed on screen\n");
		FreeSprite(&map->mapsprite);
		return -1;
	}

	if (map->onscreenloc.y<onscreenmaprect.top)
	{
		TRACE("ERROR: map sprite too large for space allowed on screen\n");
		FreeSprite(&map->mapsprite);
		return -1;
	}

	map->mapstate=MAPSTATE_LOADED;

	return result;
}


///========================================================================
//	Function:		SM_UnLoadStrategicMapGraphics()
//
//	Description:
//		Unloads the strategic map graphics
//
//	Input:			map		pointer to a STRATMAP struct
//
//	Ouput:			negative on error, zero or positive on success	
//
///========================================================================

int SM_UnLoadStrategicMapGraphics(STRATMAP *map)
{

	if (!map)
		return -1;

	if (map->mapstate==MAPSTATE_UNLOADED)
		return 0;

	FreeSprite(&map->mapsprite);

	map->mapstate=MAPSTATE_UNLOADED;

	return 0;
}


///========================================================================
//	Function:		SM_FreeStrategicMap()
//
//	Description:
//		Frees up a strategic map and all the resources associated with it
//		(including the graphics, if they haven't already been freed)
//
//	Input:			map		pointer to a STRATMAP structure
//
//	Ouput:			negative on error		
//
///========================================================================
int SM_FreeStrategicMap(STRATMAP *map)
{
	if (!map)
		return -1;

	if (map->mapstate!=MAPSTATE_UNLOADED)
		SM_UnLoadStrategicMapGraphics(map);

	if (map->pPins)
		free(map->pPins);
	map->pPins=NULL;

	free(map);
	return 0;
}


///========================================================================
//	Function:		ClearBackgroundRect()
//
//	Description:
//		Clears a rectangle on the screen to black
//
//	Input:			pRect		pointer to a RECT structure
//
//	Ouput:		    none		
//
///========================================================================

void ClearBackgroundRect(RECT *pRect)
{
	DDBLTFX ddbltfx;
	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = (DWORD)0;

	if (pBackBuffer->Blt(pRect, NULL, NULL, 
			DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx) != DD_OK)
	TRACE("ERROR while trying to clear the background buffer\n");

}


static void DDStratDraw(STRATMAP *map,int i,int strategic)
{
		
	int x = map->pPins[i].screenloc.x;
	int y = map->pPins[i].screenloc.y;
	// show all strategic objects as big
    if (strategic)
    {
                // block 6
				DDPutPixel(x, y);
				DDPutPixel(x + 1, y);
				DDPutPixel(x + 2, y);
				DDPutPixel(x + 1, y+1);
				DDPutPixel(x + 2, y+1);
				DDPutPixel(x, y+1);
    }
                
    // all enemy forces are equal in multiplayer
    // but yours are smaller
    else if (gpGame != GAMETYPE_ONEPLAYER)
    {
        if (map->pPins[i].whosepin != 1)
        {
                    DDPutPixel(x, y);
                    DDPutPixel(x + 1, y);
                    DDPutPixel(x + 1, y+1);
                    DDPutPixel(x, y+1);
        }
        else
       {
			DDPutPixel(x, y);
			DDPutPixel(x + 1, y);
        }
    }

            // color blind people dont notice the color differences
            // so want shape differences also to distinguis forces.
            // Blue, which is important in finding spy in many missions
            // is made big and obvious. Own forces are also slightly big.
            else switch (map->pPins[i].whosepin)
			{
			case 1: // green block 4
				DDPutPixel(x, y);
				DDPutPixel(x + 1, y);
				DDPutPixel(x + 1, y+1);
				DDPutPixel(x, y+1);
				break;
			case 2: // tan horzi 2
				DDPutPixel(x, y);
				DDPutPixel(x + 1, y);
				break;
			case 3: // blue block 6
				DDPutPixel(x, y);
				DDPutPixel(x + 1, y);
				DDPutPixel(x + 2, y);
				DDPutPixel(x + 1, y+1);
				DDPutPixel(x + 2, y+1);
				DDPutPixel(x, y+1);
                break;
			case 4: // gray vert 3
				DDPutPixel(x, y);
				DDPutPixel(x , y-1);
				DDPutPixel(x, y+1);
                break;
			default: // the original drawing method
				DDPutPixel(x, y);
				DDPutPixel(x + 1, y);
				DDPutPixel(x + 1, y+1);
				DDPutPixel(x, y+1);
			}



	if (!bDisplayRecall || gpGame->GetSubState() != PLAY_SUB_STATE) return; // ordinary stratmap only
	if (!bDisplayPaperMap) return;
	if (!blinkpaper) return; // not allowing blink since maps arent aligned well

	// scale position the full world to 360x360 map
	x = (map->pPins[i].pItem->position.x * 360) / (256*16);
	y = (map->pPins[i].pItem->position.y * 360) / (256*16);
	// now offset to start of map display corner
	// need screenrect in world
	y += 12;
	x += 170; 

	int basex,basey;
	if (!strategic) 	basex = basey = 5;
	else basex = basey = 9;
	x -= basex >> 1; // center the block
	y -= basey >> 1; // center the block
	++x;
	++y;
	int yset = basey;
	int xset = basex;
	while (--basex >= 0)
	{
		basey = yset;
		while (--basey >= 0)
			DDPutPixel(x+basex, y+basey);
	}
	// ring of black around it to see easier
	DDCOLOR = 0;
	basex = xset+1;
	basey = yset+1;
	while (--basey >= 0) 
	{
		DDPutPixel(x, y+basey);
		DDPutPixel(x+basex, y+basey);
	}
	basey = yset+1;
	while (--basex >= 0) 
	{
		DDPutPixel(x+basex,y);
		DDPutPixel(x+basex,y+basey);
	}
  

}

///========================================================================
//	Function:		SM_DrawStrategicMap()
//
//	Description:
//		Draws a strategic map 
//
//	Input:			map		pointer to a STRATMAP structure
//
//	Ouput:			negative on error		
//
///========================================================================

int SM_DrawStrategicMap(STRATMAP *map)
{
	int i;
	long tcount;
	tcount = GetTickCount();
	
	if (!map)
		return -1;

	if (map->mapstate!=MAPSTATE_READY)
		return -1;

	DisplaySprite(&map->mapsprite, map->onscreenloc.x, map->onscreenloc.y);

	if( !InitBackBufferLockComplex() )
		return -1;
	DDCOLOR=255;
	int state;
	for (i=0;i<map->numpins;i++)
	{
        if (map->pPins[i].pItem == NULL) continue;
        if (map->pPins[i].pintype == PINTYPE_UNUSED) continue;
		state = map->pPins[i].state;
		if( map->pPins[i].lastupdate < tcount )
		{
			int stagger;
			if (state == 0)
				stagger = 0;
			else 
				stagger= 100 - (50 * (4 - map->pPins[i].whosepin-1));
			map->pPins[i].lastupdate = tcount + PinBlinkRate[state] + stagger;
			map->pPins[i].state = !state;
		}
 		if(state  == 0) continue;
       
		if (!map->pPins[i].isvisible) continue;

		DDCOLOR = pincolors[map->pPins[i].whosepin];

         int strategic = 0;
        if (map->pPins[i].pintype == PINTYPE_OBJECT)
        {
                if (ITEM_IS_STRATEGIC(map->pPins[i].pItem))
					strategic = 1;
				else if (((OBJECT*)map->pPins[i].pItem)->triggers & TRIGGER_STRATEGIC)
					strategic = 1;
		}
		else if (ITEM_IS_STRATEGIC(map->pPins[i].pItem))
                strategic = 1;

		DDStratDraw(map,i,strategic); // put the pixels down for this item;
	
	}

		//ScreenDrawDot(&map->pPins[i].screenloc, pincolors[map->pPins[i].whosepin][map->pPins[i].pintype]);

	//SPOINT upperright, lowerleft;
	SPOINT upperleft, lowerright;

	upperleft.x=(short)SM_MapX_To_ScreenX(map, the_map.PixelBox.x);
	upperleft.y=(short)SM_MapY_To_ScreenY(map, the_map.PixelBox.y);

	lowerright.x=(short)(upperleft.x+(the_map.PixelBox.cx*map->xscale));
	lowerright.y=(short)(upperleft.y+(the_map.PixelBox.cy*map->yscale));

	DDCOLOR = 255;
	DDRect(upperleft.x, upperleft.y, lowerright.x, lowerright.y);

	FreeBackBufferLockComplex();

	return 0;
}

	
///========================================================================
//	Function:		SM_DrawStrategicMapFront()
//
//	Description:
//		Draws a strategic map on the front buffer
//
//	Input:			map		pointer to a STRATMAP structure
//
//	Ouput:			negative on error		
//
///========================================================================
int SM_DrawStrategicMapFront(STRATMAP *map)
{
	DisplaySpriteFront(&map->mapsprite, map->onscreenloc.x, map->onscreenloc.y);

	return 0;
}
	

float SM_MapX_To_ScreenX(STRATMAP *map, float mapx)
{
	return( ((mapx - the_map.boundrect.left) * map->xscale) + map->onscreenloc.x );
}


float SM_MapY_To_ScreenY(STRATMAP *map, float mapy)
{
	return( ((mapy - the_map.boundrect.top) * map->yscale) + map->onscreenloc.y );
}


float SM_ScreenX_To_MapX(STRATMAP *map, float screenx)
{
	return( ((screenx - map->onscreenloc.x) / map->xscale) + the_map.boundrect.left );
}


float SM_ScreenY_To_MapY(STRATMAP *map, float screeny)
{
	return( ((screeny - map->onscreenloc.y) / map->yscale) + the_map.boundrect.top );
}



///========================================================================
//	Function:		SM_UpdateStrategicMap()
//
//	Description:
//		Updates the pin positions of a strategic map to reflect current
//		unit positions
//
//	Input:			map		pointer to a STRATMAP struct
//
//	Ouput:			negative on error, zero or positive on success	
//
///========================================================================

extern char Allah;
extern int ReconTimer;

int SM_UpdateStrategicMap(STRATMAP *map)
{
	int i;
	PIN *curpin;
	int eArmy;

	if (!map)
		return -1;

	if (map->mapstate==MAPSTATE_UNLOADED)
		return -1;

	switch( Allah )
	{
	case 0:
		eArmy = ARMY_PLAYER;
		break;
	case 1:
		eArmy = ARMY_PLAYER;
		break;
	case 2:
		eArmy = ARMY_PLAYER_2;
		break;
	}
    if (ReconTimer) eArmy = ARMY_PLAYER;

	ITEM* pItem;
	for (i=0;i<map->numpins;i++)
	{
		curpin = &map->pPins[i];
        if (map->pPins[i].pintype == PINTYPE_UNUSED) continue;
        
		pItem = curpin->pItem;
        if (!pItem) continue; // deleted

		if( curpin->whosepin > 0 )
		{
			if (Armies[curpin->whosepin-1].Status == 0)
			{
				curpin->isvisible = 0;
				continue; // army no longer showing
			}
		}

		if( !(InBoundsRect(pItem->position )) )
		{
			// if not in rect, maybe its undeploy and carried
			if (	(ITEM_IS_STRATEGIC(pItem) ||
						(map->pPins[i].pintype == PINTYPE_OBJECT && ((OBJECT*)pItem)->triggers & TRIGGER_STRATEGIC))
					&& 
					(pItem = ItemContainedBy(pItem)) != NULL)
				curpin->isvisible = 1;



			else curpin->isvisible = 0;
		}
		else switch (map->pPins[i].pintype)
		{
			case PINTYPE_SARGE:
                if (ITEM_IS_STRATEGIC(pItem))
					curpin->isvisible=1;
                else if( Allah == 1  || ReconTimer)
					curpin->isvisible=1;
				else if (ITEM_SEEN_WHEN(pItem, eArmy) == -1)
					curpin->isvisible=0;
                else if (!ItemUserVisible(eArmy ,pItem))		//not currently visible
					curpin->isvisible=0;
                else
                    curpin->isvisible=1;
				
				break;

			case PINTYPE_UNIT:
				if (!UNIT_ON_MAP((UNIT*)(pItem)))
				{
					curpin->isvisible=0;
				}
                else if (pItem->nStrength == 0)
					curpin->isvisible=0;                    
                // if strategic, we can track it even in a vehicle
				else if (ITEM_IS_STRATEGIC(pItem))
                {
                    See(ARMY_PLAYER,pItem);  // fully visible in game
					curpin->isvisible=1;
                }
 				else if( ((UNIT *)(pItem))->pVehicle )
					curpin->isvisible = 0;
                else if( Allah == 1  || ReconTimer)
					curpin->isvisible=1;
				else if (ITEM_SEEN_WHEN(pItem,eArmy) == -1)
					curpin->isvisible=0;
				else if (!ItemUserVisible(eArmy,pItem)) //not currently visible
					curpin->isvisible=0;
				else curpin->isvisible=1;
				break;
			case PINTYPE_VEHICLE:
				if( pItem->nStrength <= 0 )
					curpin->isvisible = 0;
				else if( !VEHICLE_ON_MAP((VEHICLE *)(pItem)) )
					curpin->isvisible = 0;
				else if( ((VEHICLE *)(pItem))->pAnimation->flags & ANIM_FLAG_INVISIBLE )
					curpin->isvisible = 0;
				else if (ITEM_IS_STRATEGIC(pItem))
                {
                    See(ARMY_PLAYER,pItem);  // fully visible in game
					curpin->isvisible=1;
                }
                else if( Allah == 1  || ReconTimer)
					curpin->isvisible=1;
				else if( ITEM_SEEN_WHEN(pItem, eArmy) == -1)
					curpin->isvisible = 0;
				else if (!ItemUserVisible(eArmy,pItem)) //not currently visible
					curpin->isvisible=0;
				else
					curpin->isvisible=1;
				break;
			case PINTYPE_OBJECT:
				OBJECT *pObject;
				pObject = (OBJECT *)(pItem);
				if( pObject->triggers & TRIGGER_DESTROYED )
					curpin->isvisible = 0;
                else if( pObject->triggers & TRIGGER_UNDEPLOYED )
				{
					ITEM* oldItem;
					oldItem = pItem;
					// see if it is because it is carried and strategic
					// if so, show it. if not dont
					pItem = ItemContainedBy(pItem);
					if (pItem && (ITEM_IS_STRATEGIC(oldItem) ||	pObject->triggers & TRIGGER_STRATEGIC))
						curpin->isvisible = 1;
					else curpin->isvisible = 0;
				}
				else if (ITEM_IS_STRATEGIC(pItem))
					curpin->isvisible = 1;
				else if (((OBJECT*)pItem)->triggers & TRIGGER_STRATEGIC)
					curpin->isvisible = 1;
                else if( Allah == 1  || ReconTimer)
					curpin->isvisible=1;
				else
					curpin->isvisible=0;
				break;
		}

        // if it was visible, show it
        if (curpin->isvisible)
        {
            curpin->screenloc.x=(short)SM_MapX_To_ScreenX(map, (float) pItem->position.x);
            curpin->screenloc.y=(short)SM_MapY_To_ScreenY(map, (float) pItem->position.y);
        }
	}

	map->mapstate=MAPSTATE_READY;

	return 1;
}

///========================================================================
//	Function:		SM_ProcessMouseLoc()
//
//	Description:
//		Given a mouse over a particular location on the
//		strategic map, returns the corresponding position in 
//		world coordinates
//
//	Input:			map				pointer to a STRATMAP struct
//					screenloc   	where the mouse was  (screen coords)
//
//	Ouput:			worldloc		where the mouse was  (world (map) coords)
//					
//
//	Return value:	negative on error
///========================================================================
int SM_ProcessMouse(STRATMAP *map, POINT *screenloc, SPOINT *worldloc)
{

	if (!map)
		return -1;

	if (map->mapstate!=MAPSTATE_READY)
		return -1;

	worldloc->x=(short)SM_ScreenX_To_MapX(map, (float) screenloc->x);
	worldloc->y=(short)SM_ScreenY_To_MapY(map, (float) screenloc->y);
		
	if ((worldloc->x<0) || (worldloc->y<0) || 
		(worldloc->x>=(the_map.width<<4)) || (worldloc->y>=(the_map.height<<4)))
		return -1; //loc was outside the map

	return 0;
}

void StratMapArmyDelete(int eArmy)
{
	if (!curstratmap) return;

    int i;
	PIN *curpin;
    ITEM* pItem;
    OBJECT* pObj;
    for (i = 0; i < curstratmap->numpins; ++i)
    {
		curpin = &curstratmap->pPins[i];
        if (curpin->pintype == PINTYPE_UNUSED) continue;
		pItem = curpin->pItem;
        if (!pItem) continue;
        if (curpin->pintype == PINTYPE_OBJECT)
        {
            pObj = (OBJECT*) pItem;
            if (pObj->owner == eArmy)
            {
                curpin->isvisible = 0;
                curpin->pItem = NULL;
                continue;
            }
        }
        if ((curpin->whosepin-1) == eArmy)
        {
            curpin->isvisible = 0;
            curpin->pItem = NULL;
            continue;
        }
    }

}

void SetStratmapStrategic(ITEM* pItem)
{
    int i;
	PIN *curpin;
    int pin;
    int who;
    // ignore types we would already have pins for
    if (ITEM_TYPE(pItem) == ARMY_SARGE) return;
    if (ITEM_TYPE(pItem) == ARMY_UNIT) return;
    if (ITEM_TYPE(pItem) == ARMY_VEHICLE) return;

    // do we have free pins
    if (freepins <= 0)
    {
        TRACE("Out of pins\n");
        return;
    }

    // prove not already on pin list
    for (i = 0; i < curstratmap->numpins; ++i)
    {
		curpin = &curstratmap->pPins[i];
        if (curpin->pintype == PINTYPE_UNUSED) continue;
		if (pItem == curpin->pItem) return; // already have a pin for this
    }

    // use up a free pin for this
    pin = curstratmap->numpins++;
    --freepins;
	curpin = &curstratmap->pPins[pin];
 
    who = ITEM_ARMY(pItem);
    curpin->pItem = pItem;
    curpin->pintype = PINTYPE_OBJECT;
    curpin->whosepin = who + 1;
    curpin->lastupdate = 0;
}

 void DrawBigMap()
 {
	if( bDisplayRecall )
	{
		DisplaySprite( &RecallSprite, 160  , 0 );
		if (bAudioRecall && gpGame->GameType == GAMETYPE_ONEPLAYER) 
			MsgMission();
		bAudioRecall = FALSE;
	}
}