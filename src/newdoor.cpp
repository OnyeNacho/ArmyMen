/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: newdoor.cpp $
//
//	DESCRIPTION:	ai commander
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/newdoor.cpp 141   4/16/98 1:02p Bwilcox $
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/newdoor.cpp $
//  
//  141   4/16/98 1:02p Bwilcox
//  better error trace
//  
//  140   4/13/98 2:27p Bwilcox
//  fix dynamic vehicle blocking data
//  
//  139   4/13/98 12:41p Bwilcox
//  rp bug fix
//  
//  138   4/12/98 4:13p Bwilcox
//  fixed fanout bug
//  
//  137   4/12/98 12:16p Bwilcox
//  
//  136   4/12/98 11:24a Bwilcox
//  fix crash bug from offvisible
//  
//  135   4/10/98 6:03p Bwilcox
//  
//  134   4/10/98 2:09p Bwilcox
//  fix bug in routeplanner slowing down things
//  
//  133   4/09/98 3:49p Bwilcox
//  perim fast test matches astar
//  
//  132   4/09/98 12:05p Bwilcox
//  issargeuntrafficable varies if sarge is npc. new arg added
//  
//  131   4/07/98 11:49p Bwilcox
//  prevent offvisible routing unless start or end there
//  
//  130   4/07/98 11:34p Bwilcox
//  immobilie trooper if routing failure
//  
//  128   98/04/02 16:59 Dmaynard
//  typecast ITemfanout to be Ipoint
//  
//  127   4/02/98 3:21p Phu
//  typecast to avoid warnings
//  
//  126   3/26/98 9:00p Bwilcox
//  subtracttraff dones less for vehicles
//  
//  125   3/26/98 5:40p Bwilcox
//  fixing mine data for routeplanner
//  
//  124   3/26/98 2:39p Bwilcox
//  vehicle in movement layer split into new layer
//  
//  123   3/25/98 2:19p Bwilcox
//  
//  122   3/24/98 5:54p Bwilcox
//  
//  121   3/24/98 5:53p Bwilcox
//  
//  119   3/24/98 4:29p Bwilcox
//  
//  118   3/17/98 6:08p Bwilcox
//  proper null checking around aiitemfind calls
//  
//  117   3/16/98 1:22p Bwilcox
//  removing unneeded checks for ARMY_OBSTACLE when category is
//  clearly unique.
//  
//  116   3/16/98 1:02p Nrobinso
//  turn off trace
//  
//  115   3/08/98 5:38p Phu
//  fix ITEM_TYPE(id)  to be ITEM_TYPE(pItem)...  macro uses item pointer
//  not unique id!!!!
//  
//  114   3/07/98 11:52p Nrobinso
//  setup macro for debug layer
//  
//  113   3/06/98 4:13p Bwilcox
//  revised mine blocking
//  
//  112   3/03/98 1:03p Bwilcox
//  movement display now reveals all mines
//  
//  111   2/28/98 9:36p Bwilcox
//  better vehicle control
//  
//  110   2/10/98 6:18p Bwilcox
//  fixed gates vehicle traffic route planinng
//  
//  109   2/09/98 2:24p Phu
//  display elevation layer
//  
//  108   2/06/98 7:34p Bwilcox
//  vehicle router improvments
//  
//  107   2/06/98 4:13p Bwilcox
//  trying to improve vhiecle controller
//  
//  106   2/06/98 3:38p Bwilcox
//  try to plan even to a blocked spot
//  
//  105   2/06/98 3:30p Bwilcox
//  removed a router trce
//  
//  104   2/04/98 5:21p Bwilcox
//  
//  103   2/04/98 11:56a Bwilcox
//  fixing bridge routing
//  
//  102   2/04/98 11:06a Bwilcox
//  router performance tuning and draw fixes
//  
//  101   2/03/98 6:22p Phu
//  fix router
//  
//  100   2/02/98 3:49p Bwilcox
//  fixed route planner
//  
//  99    2/02/98 2:24p Bwilcox
//  
//  98    1/30/98 1:28p Bwilcox
//  trying new visibility stuff
//  
//  97    1/30/98 10:23a Bwilcox
//  routedata fix
//  
//  96    1/28/98 1:25p Bwilcox
//  fixed load/free stuff
//  
//  95    1/28/98 12:32p Bwilcox
//  
//  94    1/28/98 11:32a Bwilcox
//  more edit trafic code
//  
//  93    1/28/98 10:50a Bwilcox
//  editing trafficability
//  
//  92    1/25/98 4:45a Bwilcox
//  
//  91    1/25/98 4:38a Bwilcox
//  separating ai map allocation from init
//  
//  90    1/25/98 3:11a Bwilcox
//  raised avoidance level of mines
//  
//  89    1/25/98 2:40a Bwilcox
//  fixed mine bug in router layer
//  
//  88    98/01/22 12:21 Dmaynard
//  get rid of infinite loop in MineHere
//  
//  87    1/22/98 11:55a Bwilcox
//  fixing broken widths on map (affects vehicles)
//  
//  86    1/22/98 11:40a Bwilcox
//  removed dead code, fixed map display
//  
//  85    1/22/98 10:30a Bwilcox
//  fixed bug in consider (tmp - )
//  
//  84    1/21/98 1:52p Phu
//  check in for bruce - mine removal function
//  
//  83    1/20/98 12:45p Bwilcox
//  code to routeplan thru gates
//  
//  82    1/15/98 4:21p Bwilcox
//  
//  81    1/15/98 1:54p Bwilcox
//  searchdist replace
//  
//  80    1/15/98 12:07p Bwilcox
//  imrpoved speed of ONEDGE with an OFF_EDGE macro
//  
//  79    1/15/98 9:35a Bwilcox
//  tile line optimizations
//  
//  78    1/14/98 1:34p Bwilcox
//  removed cansee
//  
//  77    1/14/98 8:25a Bwilcox
//  fix to trooper routing system
//  
//  76    1/13/98 3:23p Bwilcox
//  
//  75    1/13/98 9:22a Bwilcox
//  
//  74    1/05/98 11:34a Bwilcox
//  removed dead code in newdoor and added route straightener to airouter
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

//  WARNING- if we do multiple threads we may reentracy problems!!!!

#include "stdafx.h"

#include "Anim.h"

#define AI_FRIEND 1			# enable private visibility in AIX
#include "aix.h"
#include "army.h"
#include "Map.h"
#include "Ai.h"
#include "item.h"
#include "dd.h"
#include "newdoor.h"
#include "trooper.h"
#include "vehicle.h"
#include "aiaccess.h"
#include "item.h"
#include "miscfile.h"
#include "unit.h"
#include "aibtank.h"
#include <stdio.h>

static char isunit;
char showdot = 0;
extern char bw1,bw2;
extern char routingDraw;
long VehicleSafeDeploy(IPOINT index);

#ifdef INFORMATION
Movement of single-tile army units, is allowed diagonally from one tile
to another, even if both diagonals adjacent to them are blocked.
#endif   

static ITEM* planItem;

// additional controls on route planner
#define CLEARPINCH	8				// remove pinched interiors(doable only)
#define MERGEADJ	16				// jump to future adj(doable only)

    /* Capacity Limits */
#define GRIDLIMIT 65600		//  expect biggest map is 256x256 tiles (65535)



// Movement ranges +- 127 from the movement layer
#define NON_TRAFFICABLE 15				/* and above */
#define BORDER_UNTRAFFICABLE 127		/* next to edge of map */

                //	A* search data
static char goalout,startout;

typedef struct{ /* this node is directly on the map it corresponds to */
    unsigned long searchID;	// been here already this search
    unsigned short from;		// where we came from
    unsigned short gCost;		// what it cost to get here
    unsigned short hCost;		// what it will cost to get to goal
    unsigned short sibling;		// post siblings in a cost chain
    unsigned short parent;		// prior siblings in a cost chain
    unsigned short est;			// cost estimate
} NODE;
#define PRIORITY_LIMIT 4000
static NODE nodeList[GRIDLIMIT];			// 1 node per map tile
static IPOINT priorityList[PRIORITY_LIMIT+1] ={0};// sorted priority stuff
static IPOINT *priorityEnd = &priorityList[PRIORITY_LIMIT];
static IPOINT goalloc,atloc,newloc;	// destination and present loc
static unsigned long searchID = 0;
static NODE* atNode;
static IPOINT *highWater;
static int baseCost;
unsigned int searched;
long minPriority,maxPriority;		// debug statistics
static long SearchDistance(IPOINT a,IPOINT b);/* in tile units */

BOOL bNotReady = TRUE;

/* map type data */
unsigned long gridmax;			/* total size of grid */
unsigned char *pMarkers;
unsigned char *pMines;				
unsigned char *pNoVehicleRoute;		/* no vehicle can route thru here*/
char* pVehicleBlock;
   
MAP_VIEW mapView = NO_MAP;			// what mode to show debug-layer in

int displayed = 0;					/* showmap main layer drawn */

static char aiInitialized = FALSE;			/* are we set up to run */

#define PERIM_MAX 50000		// how many points around an object

int UntrafficableUnit(IPOINT index);
TESTOK NotAllowed;
static int searchArmyBit;

static void Search(IPOINT from,IPOINT to,int test,IPOINT *ways);
static void FindFullLoop(IPOINT before,IPOINT at,IPOINT *pts);
static int SearchTileLegalLine(IPOINT from, IPOINT to, IPOINT *pts);

static char allowweak = 0;

int scandir[17]; /* to walk around perims of objects */
/* NORTH,NORTH+EAST,EAST,SOUTH+EAST,SOUTH,SOUTH+WEST,WEST,NORTH+WEST,
   NORTH,NORTH+EAST,EAST,SOUTH+EAST,SOUTH,SOUTH+WEST,WEST,NORTH_WEST*/

int ring2[17];

extern COLORREF layerColor;				// color for debug layer
static void PatchMap();

/************************************************************/
/*	 Utility routines										*/
/************************************************************/

int UntrafficableUnit(IPOINT index){// no one can go on here

    if (the_map.movement_layer[index] >= NON_TRAFFICABLE) return TRUE;
    if (pVehicleBlock[index]) return TRUE; // stationary vehicle there
    return FALSE;
}

int SearchUntrafficableUnit(IPOINT index){// no one can go on here

	if (OFF_X(IPOINT_X(index))) return TRUE;
	if (OFF_Y(IPOINT_Y(index))) return TRUE;

		// see if off visible.
	if (!goalout && !startout) // may not go out of bounds
	{
		if (OffVisible(index)) return TRUE;
	}

    // we know we have a mine hereabouts
    if (pMines[index] & searchArmyBit) return TRUE;

    if (pVehicleBlock[index]) return TRUE; // stationary vehicle there

    if (the_map.movement_layer[index] < NON_TRAFFICABLE) return FALSE;

    // gate override layer says we can go here
    if (pNoVehicleRoute[index] & searchArmyBit) return FALSE;

    // dont go here
    return TRUE;
}

static int SearchUntrafficableVehicle(IPOINT index){// no vehicle can go here

	if (OFF_X(IPOINT_X(index))) return TRUE;
	if (OFF_Y(IPOINT_Y(index))) return TRUE;

	// see if off visible.
	if (!goalout && !startout) // may not go out of bounds
	{
		if (OffVisible(index)) return TRUE;
	}

    // we know we have a mine hereabouts
    if (pMines[index] & searchArmyBit) return TRUE;

    // gate override layer says we can go here
    if (!(pNoVehicleRoute[index] & OK_BIT) && !allowweak) return TRUE;

    // anyone can go here
    if (the_map.movement_layer[index] < NON_TRAFFICABLE) return FALSE;

    // gate override layer says we can go here
    if (pNoVehicleRoute[index] & searchArmyBit) return FALSE;

    // dont go here
    return TRUE;
}

int cross(IPOINT pt,IPOINT from,IPOINT to){
/* compute the x product of line and point. > 0 means right < 0 means left*/

	return -(   ( (IPOINT_X(to) - IPOINT_X(pt)) *
                  (IPOINT_Y(from) - IPOINT_Y(pt)) ) -
                ( (IPOINT_X(from) - IPOINT_X(pt)) *
                  (IPOINT_Y(to) - IPOINT_Y(pt))  ));}

int TileLegalLine(IPOINT from, IPOINT to, IPOINT *pts){
// find set of points along a line  
    
    int xdif, ydif,xstep,ystep,i, xcnt,ycnt,n = 1;
    int fromx = IPOINT_X(from);
    int fromy = IPOINT_Y(from);
    int tox = IPOINT_X(to); IPOINT index;
    int toy = IPOINT_Y(to);
    pts[n] = from;

	/* set up step count and increment */
	xdif = tox - fromx;
	ydif = toy - fromy;
    xstep = (xdif >= 0) ? xdif : -xdif;
    ystep = (ydif >= 0) ? ydif : -ydif;
    xcnt = ycnt = 0;
    if (xstep >= ystep){ /* walk x */
        xdif = (xdif > 0) ? 1 : -1;

        /* now step one point at a time */
        for (i=1; i <= xstep; ++i) {
            /* per step expected location */
            fromx += xdif;
            ycnt += ydif;
            ystep = (ycnt / xstep) + fromy;
            index = INDEX(fromx,ystep);

            // if two blocked pts occur in a row, see if can interpolate 
            // unblocked pt
            if (UntrafficableUnit(index) && UntrafficableUnit(pts[n])){
                int xd = fromx - IPOINT_X(pts[n]);
                int yd = ystep - IPOINT_Y(pts[n]);
                if (xd && yd){ /* a diagonal move */
                    IPOINT adj = index - xd;
                    if (UntrafficableUnit(adj)) adj = index - INDEX_ENCODED_Y(yd);
                    if (!UntrafficableUnit(adj)) pts[++n] = adj;
                }
            }

            pts[++n] = index;
        }
    }
    else{
        ydif = (ydif > 0) ? 1 : -1;

        /* now step one point at a time */
        for (i=1; i <= ystep; ++i) {
            fromy += ydif;
            xcnt += xdif;
            xstep = (xcnt / ystep) + fromx;
            index = INDEX(xstep,fromy);
            // if two blocked pts occur in a row, see if can interpolate 
            // unblocked pt
            if (UntrafficableUnit(index) && UntrafficableUnit(pts[n])){
                int xd = xstep - IPOINT_X(pts[n]);
                int yd = fromy - IPOINT_Y(pts[n]);
                if (xd && yd){ /* a diagonal move */
                    IPOINT adj = index - xd;
                    if (UntrafficableUnit(adj)) adj = index - INDEX_ENCODED_Y(yd);
                    if (!UntrafficableUnit(adj)) pts[++n] = adj;
                }
            }

            pts[++n] = index;
        }
    }

	if (pts[n] != to) 
	{
		TRACE("TileLegalLine didnt end up at goal\n");
		n = 0;
	}
    if (n >= PERIM_MAX) 
	{	
		TRACE("ERROR: Path line too long\n");
		n = 0;
	}
    pts[0]  = n;
    return n;
}


int TileLine(IPOINT from, IPOINT to, IPOINT *pts){
// find set of points along a line  
    
    int xdif, ydif,xstep,ystep,i, xcnt,ycnt,n = 1;
    int fromx = IPOINT_X(from);
    int fromy = IPOINT_Y(from);
    int tox = IPOINT_X(to); IPOINT index;
    int toy = IPOINT_Y(to);
    pts[n] = from;

	/* set up step count and increment */
	xdif = tox - fromx;
	ydif = toy - fromy;
    xstep = (xdif >= 0) ? xdif : -xdif;
    ystep = (ydif >= 0) ? ydif : -ydif;
    xcnt = ycnt = 0;
    if (xstep >= ystep){ /* walk x */
        xdif = (xdif > 0) ? 1 : -1;

        /* now step one point at a time */
        for (i=1; i <= xstep; ++i) {
            /* per step expected location */
            fromx += xdif;
            ycnt += ydif;
            ystep = (ycnt / xstep) + fromy;
            index = INDEX(fromx,ystep);
            pts[++n] = index;
        }
    }
    else{
        ydif = (ydif > 0) ? 1 : -1;

        /* now step one point at a time */
        for (i=1; i <= ystep; ++i) {
            fromy += ydif;
            xcnt += xdif;
            xstep = (xcnt / ystep) + fromx;
            index = INDEX(xstep,fromy);
            pts[++n] = index;
        }
    }

	if (pts[n] != to) 
	{
		n = 0;
		TRACE("TileLine didnt end up at goal\n");
	}
    if (n >= PERIM_MAX)
	{
		TRACE("ERROR: Path line too long\n");
		n = 0;
	}
    pts[0]  = n;
    return n;
}


/************************************************************/
/*	 One-time initialization routines						*/
/************************************************************/

static void AllocateData(){

	ASSERT(gridmax);

	pVehicleBlock = (char *) malloc(gridmax * sizeof(char));
	if (!pVehicleBlock){
		DoFatal( "ERROR: failed to alloc pvehicleblock\n");
        return;
    }
    

	pMines = (unsigned char *) malloc(gridmax * sizeof(unsigned char));
	if (!pMines){
		DoFatal( "ERROR: failed to alloc pMines\n");
        return;
    }
	pMarkers = (unsigned char *) malloc(gridmax * sizeof(unsigned char));
	if (!pMarkers){
		DoFatal( "ERROR: failed to alloc markers\n");
        return;
    }

	pNoVehicleRoute = (unsigned char *) malloc(gridmax * sizeof(unsigned char));
	if (!pNoVehicleRoute){
		DoFatal( "ERROR: failed to alloc pNoVehicleRoute\n");
        return;
    }


    // assign default data
    IPOINT index;
    WALKGRID(index){
        pVehicleBlock[index] = 0;
        pMines[index] = 0;		
        pMarkers[index] = 0;		
        pNoVehicleRoute[index] = 0;	
    }    
}

static void DeAllocateData(){
    if (pMines != NULL){ 
        free(pMines);
        pMines = NULL;
    }
    if (pVehicleBlock != NULL){ 
        free(pVehicleBlock);
        pVehicleBlock = NULL;
    }
    if (pMarkers != NULL){ 
        free(pMarkers);
        pMarkers = NULL;
    }
    if (pNoVehicleRoute != NULL){ 
        free(pNoVehicleRoute);
        pNoVehicleRoute = NULL;
    }
}

static void InitScanData(){

    scandir[0] = UP1; // north
    scandir[1] = UP1 + RIGHT1;  // northeast
    scandir[2] = RIGHT1;  // east
    scandir[3] = DOWN1 + RIGHT1;  // southeast
    scandir[4] = DOWN1;  // south
    scandir[5] = DOWN1 + LEFT1; // southwest
    scandir[6] = LEFT1; // west
    scandir[7] = LEFT1+UP1; // northwest
    scandir[8] = UP1; // north
    scandir[9] = UP1 + RIGHT1;  // northeast
    scandir[10] = RIGHT1;  // east
    scandir[11] = DOWN1 + RIGHT1;  // southeast
    scandir[12] = DOWN1;  // south
    scandir[13] = DOWN1 + LEFT1; // southwest
    scandir[14] = LEFT1; // west
    scandir[15] = LEFT1+UP1; // northwest
    scandir[16] = 0; // terminator

	ring2[0] = UP1+UP1;
	ring2[1] = UP1+UP1+RIGHT1;
	ring2[2] = UP1+UP1+RIGHT1+RIGHT1;
	ring2[3] = UP1+RIGHT1+RIGHT1;
	ring2[4] = RIGHT1+RIGHT1;
	ring2[5] = DOWN1+RIGHT1+RIGHT1;
	ring2[6] = DOWN1+DOWN1+RIGHT1+RIGHT1;
	ring2[7] = DOWN1+DOWN1+RIGHT1;
	ring2[8] = DOWN1+DOWN1;
	ring2[9] = DOWN1+DOWN1+LEFT1;
	ring2[10] = DOWN1+DOWN1+LEFT1+LEFT1;
	ring2[11] = DOWN1+LEFT1+LEFT1;
	ring2[12] = LEFT1+LEFT1;
	ring2[13] = UP1+LEFT1+LEFT1;
	ring2[14] = UP1+UP1+LEFT1+LEFT1;
	ring2[15] = UP1+UP1+LEFT1;
}

static void ForceMapBoundary(){ // put ring around map to stop falling off

    IPOINT index;
    WALKGRID(index){
        // write on tiles which on the edge boundary
        if (ONEDGE(index)) the_map.movement_layer[index] = BORDER_UNTRAFFICABLE;
    }
}

static int RawBlock(IPOINT at)
{
    int bit = PLAYER1_BIT | PLAYER2_BIT | PLAYER3_BIT | PLAYER4_BIT;
    // if can move, good
    if (the_map.movement_layer[at] < NON_TRAFFICABLE) return FALSE;
    // if any gate here, good
    if (pNoVehicleRoute[at] & bit) return FALSE;
    // bad for going to
    return TRUE;
}

static int StoreW(IPOINT at){

    int d = 1; IPOINT index = at;
    while (!RawBlock(--at)) ++d; // walk left til blocked
    return d;
}

static int StoreE(IPOINT at){

    int d = 1; IPOINT index = at;
    while (!RawBlock(++at)) ++d; // walk left til blocked
    return d;
}

static int StoreS(IPOINT at){

    int d = 1; IPOINT index = at;
    while (!RawBlock(at += DOWN1)) ++d; // walk left til blocked
    return d;
}

static int StoreN(IPOINT at){

    int d = 1; IPOINT index = at;
    while (!RawBlock(at += UP1)) ++d; // walk left til blocked
    return d;
}

static int StoreNW(IPOINT at){

    int d = 1; IPOINT index = at;
    while (!RawBlock(at += UP1+LEFT1)) ++d; // walk left til blocked
    return d;
}

static int StoreNE(IPOINT at){

    int d = 1; IPOINT index = at;
    while (!RawBlock(at += UP1+RIGHT1)) ++d; // walk left til blocked
    return d;
}

static int StoreSW(IPOINT at){

    int d = 1; IPOINT index = at;
    while (!RawBlock(at += DOWN1+LEFT1)) ++d; // walk left til blocked
    return d;
}

static int StoreSE(IPOINT at){

    int d = 1; IPOINT index = at;
    while (!RawBlock(at += DOWN1+RIGHT1)) ++d;// walk left til blocked
    return d;
}

int OffVisible(IPOINT index)
{
	int xx,yy;
	xx = IPOINT_X(index);
	yy = IPOINT_Y(index);
	if (xx < VISIBLE_BOUNDARY || xx  >= (map_width-VISIBLE_BOUNDARY))return 1;
	else if (yy < VISIBLE_BOUNDARY || yy  >= (map_height-VISIBLE_BOUNDARY)) return 1;
	return 0;
}

static void SetWidth(IPOINT index)
{
	int n,s,e,w,nw,ne,sw,se;

	pNoVehicleRoute[index] &= ~ WIDE_BIT | OK_BIT;
	if (RawBlock(index)) return; // not ever reasonable

	w = StoreW(index);
	n = StoreN(index);
	   e = StoreE(index);
	   s = StoreS(index);
	   nw = StoreNW(index);
	   ne = StoreNE(index);
	   sw = StoreSW(index);
	   se = StoreSE(index);

       if (w < 3);
       else if (e < 3);
       else if (n < 3);
       else if (s < 3);
       else if (ne < 3);
       else if (sw < 3);
       else if (nw < 3);
       else if (se < 3);
       else pNoVehicleRoute[index] |= WIDE_BIT;

       if (w < 2);
       else if (e < 2);
       else if (n < 2);
       else if (s < 2);
       else if (ne < 2);
       else if (sw < 2);
       else if (nw < 2);
       else if (se < 2);
       else pNoVehicleRoute[index] |= OK_BIT; // must have this for vehicles to go there
}

void SetWidth1(IPOINT tile)
{
	int i;
	if (bNotReady) return;
	if (OFF_EDGE(tile)) return;
	SetWidth(tile);
	for (i = 0; i < 8; ++i) SetWidth(tile + scandir[i]); // all layer1
	for (i = 0; i < 16; ++i) SetWidth(tile + ring2[i]); // all layer2
}

static void ComputeWidth(){ // how far to nearest obstruction in 8 ways

    IPOINT index; long untraf = 0;
    searchArmyBit = PLAYER1_BIT | PLAYER2_BIT | PLAYER3_BIT | PLAYER4_BIT;
    WALKGRID(index){
        if (ONEDGE(index)){
            ++untraf;
            continue;	// not accessible
        }
        // if untrafficable and not from a gate
        if (UntrafficableUnit(index) &&
            !(pNoVehicleRoute[index] & searchArmyBit))
        {
            ++untraf;
            continue; // not allowed to be on
        }
      }	
    // now set router access of different vehicles
    WALKGRID(index){
        if (OFF_X(IPOINT_X(index)) || OFF_Y(IPOINT_Y(index))){ // on the perim
            pNoVehicleRoute[index] |= OFFEDGE_BIT;            
            continue;
        }
        if (RawBlock(index)) continue; // not ever reasonable
		SetWidth(index);

       // note avoid waters edge for all things
       if (the_map.triggers[index] & TRIGGER_WATER &&
           UntrafficableUnit(index))
       {
           the_map.movement_layer[index+UP1] += 15;
           the_map.movement_layer[index+UP1+LEFT1] += 15;
           the_map.movement_layer[index+UP1+RIGHT1] += 15;
           the_map.movement_layer[index+LEFT1] += 15;
           the_map.movement_layer[index+RIGHT1] += 15;
           the_map.movement_layer[index+DOWN1] += 15;
           the_map.movement_layer[index+DOWN1+LEFT1] += 15;
           the_map.movement_layer[index+DOWN1+RIGHT1] += 15;
       }
    }
    
//    TRACE("Map has %d untrafficable of %d\n",untraf,gridmax);
}


void AiMapAllocate(){

    gridmax  = the_map.width * the_map.height; 				
    if (gridmax > GRIDLIMIT) DoFatal("incoming data too big");
	if ( aiInitialized )		/* see if we need to clear the mapping data */
		AiMapExit();
	AllocateData(); 		/* get common global spaces */
    aiInitialized = TRUE;	/* signify that AI has been initialized for use */

}                            

/* set up default access to the world and analzye the map */
void AiMapInit(){
   	
    displayed = 1;
    /* now do our own precomputations on the map */
    InitScanData();			/* set up blind-cane walk array */ 
    ForceMapBoundary();		/* write an impassible ring around map */
    ComputeWidth();			/* find max distance to neighor blockages */
	bNotReady = FALSE;
}

/* clear default access to the world and analzye the map */
void AiMapExit( void ){

	// signigy that AI is nolonger valid
    aiInitialized = FALSE;
	bNotReady = TRUE;

	DeAllocateData(); 		/* get common global spaces */
}

/************************************************************/
/*	 Routeplanner routines								    */
/************************************************************/


static void XferPerimToWay(IPOINT* waypoints,int *low,int *high,
    IPOINT *pts){
//copy perim to waypoints
        
    pts[pts[0]+1] = pts[pts[0]-1];/* replicate adjlast */
    pts[pts[0]+2] = pts[pts[0]]; /* replicate last */
    int limit = pts[0];
    int i;
    for (i = 1; i <= limit; ++i){
        waypoints[++*low] = pts[i];
        if ((*low+2) == *high) break; // too many for all
            
        // ROUTE OPTIMIZATION #1
        /* see if one beyond is diagonal, if so skip next */
        if (pts[i] != pts[i+2]){
            ++i; /* this skips the intervening bend */
        }
    }
}

static void FinalLDeviation(IPOINT *pts,IPOINT from,int *index){
// want max left iterated
    
    int i,val,best = *index; IPOINT to = pts[best],at; int deviate = 0;
    long d = TileDistance(from,to);
    
    for (i = best-1; i >= 1; --i){
        at = pts[i];
        if ((*NotAllowed)(at)) continue; // not on an object
        if (at == from) continue; // dont go to self
        int x = IPOINT_X(at);
        int y = IPOINT_Y(at);
        val = cross(at,from,to);
        if (val <= deviate){
            if (TileDistance(to,at) > d) continue; // behind
            best = i;
            to = at;	// new line to Consider
            d = TileDistance(from,to);
            deviate = 0;
        }
	}
    *index = best;
}

static void FinalRDeviation(IPOINT *pts,IPOINT from,int *index){
// want max right iterated
    
    int i,val,best = *index; IPOINT to = pts[best],at; int deviate = 0;
    long d = TileDistance(from,to);
    for (i = best-1; i >= 1; --i){
        at = pts[i];
        if ((*NotAllowed)(at)) continue; // not on an object
        if (at == from) continue;
        val = cross(at,from,to);
        if (val >= deviate){
            if (TileDistance(to,at) > d) continue; // behind
            best = i;
            to = at;	// new line to Consider
            d = TileDistance(from,to);
            deviate = 0;
        }
	}
    *index = best;
}

static void MaxCDeviation(IPOINT *pts,IPOINT from,IPOINT to, int offset,
                         int *result){

    IPOINT *best = &pts[pts[0]-1]; long deviation = 0,val;
    IPOINT* at = best+1; IPOINT index;
    while (--at > pts){
        index = *at;
        if ((*NotAllowed)(index)) continue; // cant go here
        if (index == from || index == to) continue; 
        val = cross(index,from,to);
        if (val < deviation){
            deviation = val;
            best = at;
        }
    }
    *result = best - pts; // the index of the best deviate 
}

static void MaxCCDeviation(IPOINT *pts,IPOINT from,IPOINT to, int offset,
                         int *result){

    IPOINT *best = &pts[pts[0]-1]; long deviation = 0,val;
    IPOINT* at = best+1; IPOINT index;
    while (--at > pts){
        index = *at;
        if ((*NotAllowed)(index)) continue; // cant go here
        if (index == from || index == to) continue;
        val = cross(index,from,to);
        if (val > deviation){
            deviation = val;
            best = at;
        }
    }
    *result = best - pts; // the index of the best deviate 
}

static IPOINT* OtherSide(IPOINT* pts,IPOINT* perim,int linei,IPOINT to,
    IPOINT* stored,int control){

    int best = 0,i,n; long nearVal = 999999,d; IPOINT index,*base = stored;
    FindFullLoop(pts[linei-1],pts[linei],perim); // full perim around
    n = *perim;
    *perim = 30000;	// default failure answer
    for (i = n-1; i > 1; --i){// walk the perim and find the other side
        index = perim[i];
        if (!MARKED(index)) continue; // not on the line
        d = TileDistance(index,to);
        if (d >= nearVal) continue; // not closer
        nearVal = d;				// note new better choice
        best = i;
    }
    if (best <= 1){// goal is unapproachable
        return base;
    }    

    // now have closest perim to goal, can we get there
    // Try for minimal way 1st
    if (best < (n >> 1)){ /* less than halfway from start */
        for (i = 1; i < best; ++i){
            index = perim[i];
            if ((*NotAllowed)(index)) break;
            if (control & FULLLIST)  *++stored = index;
        }
        if (i < best){ // couldnt get there that way
            stored = base;
            for (i = n-1; i > best; --i){
                index = perim[i];
                if ((*NotAllowed)(index)) break;
                if (control & FULLLIST)  *++stored = index;
            }
            if (i > best) return base; // cant get there
        }
    }
    else{// best come back from end ([n] = our start)
        for (i = n-1; i > best; --i){
            index = perim[i];
            if ((*NotAllowed)(index)) break;
            if (control & FULLLIST)  *++stored = index;
        }
        if (i > best){ // couldnt get there that way
            stored = base;
            for (i = 1; i < best; ++i){
                index = perim[i];
                if ((*NotAllowed)(index)) break;
                if (control & FULLLIST)  *++stored = index;
            }
            if (i < best) return base;  // cant get there
        }
    }

    // yes we can. find where on the line other side is, and continue
    to = perim[best];  // we can run around object to get to here
    if (control & FULLLIST)  *++stored = to;
    // find index on line to resume
    for (i = 1; i <= *pts; ++i) if (pts[i] == to) break;
	if (i <= linei) {
		return base; // made no headway down the line
	}
    *perim = i;	
    if (pts[i] != to) 
	{
		TRACE("Failed to find line\n");
		*pts = 0;
	}
    return stored;
}

static int AnyFeasibleRoute(IPOINT from,IPOINT to,IPOINT* results,
                            int control){
    /*travel ok along this unit*/

    IPOINT pts[PERIM_MAX+2],perim[PERIM_MAX+2],*stored = results;
    int i,n,index; 
    SearchTileLegalLine(from,to,pts);//draw the line to walk (diagonals filled)
	n = pts[0];

    for (i = 1; i <= n; ++i) MARK(pts[i]); // mark the line   
    *++stored = pts[1];// start here ?? BUG??? 
    for (i = 2; i < n; ++i){/* check the line */
        index = pts[i];
        if (control & FULLLIST)  *++stored = index;// walk straight here
        if ((*NotAllowed)(index)){// blocked, run around to other side
			// get closest other side hitting line
            stored = OtherSide(pts,perim,i,to,stored,control);
            i = *perim; // extra result put here, resume from other side
        }
    }
    if (*stored != to) *++stored = to;	// end up here (may already be stored)
    if (i < 30000) *results = stored - results; // store count of walk
    else *results = 0; 	// couldnt do it

    for (i = 1; i <= n; ++i) CLEARMARK(pts[i]); // unmark the line    

    return *results;	// how many pts in walk
}

static long MaxDelta(IPOINT a,IPOINT b){/* in tile units */

    int xdif = IPOINT_X(a) - IPOINT_X(b);
    int ydif = IPOINT_Y(a) - IPOINT_Y(b);
    if (xdif < 0) xdif = -xdif;
    if (ydif < 0) ydif = -ydif;
    return (xdif > ydif) ? xdif : ydif;
}


static void Collapse(IPOINT* myways){

    int n = *myways,i,j,delta;
    for (i = 1; i < n; ++i){
        j = i+1; // next waypoint
        delta = myways[j] - myways[i];
        while (++j < n && (myways[j+1] - myways[j]) == delta);
        if (j <= (i + 2)) continue; // not extended in straight line
        MoveMemory(&myways[i+1],&myways[j],(n - j + 1) * (sizeof(IPOINT)));
        n -= (j - i - 1);
		
    }
    *myways = n;
}

static void CleanResult(int control, IPOINT* myways){

 
   // remove straight adj pieces and just report waypoints
    if (control & COLLAPSE && !(control & FULLLIST)) Collapse(myways);
}

static void StoreResult(IPOINT* myways, SPOINT* waypoints,int maxways,
                 SPOINT basefrom,
                 SPOINT baseto,int control){ // store the route away

    int i;
    CleanResult(control,myways);	// optimize routing		
    
    waypoints[1] = basefrom;
	int n = *myways;
    if (n >= maxways) n = maxways;// limit to user acceptable amount
    // make waypoints in center of tile.
    for (i = 2; i < n; ++i)
    {
        waypoints[i] = CenterPointFromTile(myways[i]);
    }

    waypoints[n] = baseto;
    waypoints[0].x = n;
}

static long SearchSafe(IPOINT tile)
{
	if ((*NotAllowed)(tile)) return 0;
	return tile;
}

void PlanRoute(
        UID id,							// label it
        int control,				   	// restrictions on routing process
        SPOINT basefrom,SPOINT baseto, 	// from and to of route
        SPOINT* waypoints, 				// place to put route
        int maxway) 					// max points allowed in routing
{
    IPOINT myways[PERIM_MAX+2], from,to;
    ASSERT(maxway < PERIM_MAX); 		// too many waypoints asked for
    ASSERT(maxway > 4);					// too few waypoints asked for
    ASSERT(basefrom.x != 0 && baseto.x != 0); // bad route request

    SelectUntrafficableFunction(control,id); // set NotAllowed function variable
    waypoints[0].x = 0;					// init count of route to 0 (failed)

    // switch from world to tile coordinates in index notation
	from = ENCODE_IPOINT(basefrom.x,basefrom.y);
	to = ENCODE_IPOINT(baseto.x,baseto.y);

	// will route planner be allowed to run off the visible space?
	goalout = startout = FALSE;
	if (OffVisible(from)) startout = TRUE;
	if (OffVisible(to)) goalout = TRUE;
	// see if vehicle starts on difficult but unblocked tile.
	isunit = !(control & (JEEP_ROUTE || TANK_ROUTE || HALFTRACK_ROUTE || CONVOY_ROUTE));
    // if starting out vehicle on a bad tile, allow it to continue
    if (!isunit && !(pNoVehicleRoute[from] & OK_BIT))
        allowweak = TRUE;

       
    // if goal is on same or adj tile, route is automatically ok
    if (Adj8(from,to)){ /* in block 8 range */
        waypoints[0].x = 2;		// just go there
        waypoints[1] = basefrom;
        waypoints[2] = baseto;
        goto exit;
    }

    planItem = AiItemFind(id);

     BOOL blocked;

     // from might be illegal 
     // anyone can be here
     if (the_map.movement_layer[from] < NON_TRAFFICABLE) blocked = FALSE;

    // gate override layer says we can be here
    else if (pNoVehicleRoute[from] & searchArmyBit) blocked = FALSE;

    // dont be here (illegal somehow)
    else blocked = TRUE;
    
     if (blocked)
     {
         if (planItem) TRACE("From blocked %d %s\n",from,ItemDBName(planItem));
         goto exit;
     }


	// goal might be illegal 
     if ((*NotAllowed)(to))
     {
          if (!planItem){
             TRACE("**To blocked %d\n",to);
             goto exit;
         }
         to = (IPOINT)ItemFanOut(planItem,to,10,SearchSafe);
		 if (!to) 
		 {
			 TRACE("**No safe to\n");
			 goto exit;
		 }
         baseto = CenterPointFromTile(to);
     }
   
     
    // first determine the raw feasibility of the task
    if (AnyFeasibleRoute(from,to,myways,control)) 
	{
		// settle for just being possible (also good for known straight lines)
		Search(from,to,control,myways);// use A-star searcher
 
		StoreResult(myways,waypoints,maxway,basefrom,baseto,control);
		if (searched > 24000)
			TRACE("%s searched %d tiles from %d.%d to %d.%d\n",
			ItemDBName(AiItemFind(id)),searched,
			basefrom.x,basefrom.y,baseto.x,baseto.y);
		if (*myways == 0) 
		{
 			TRACE("%s Search failed? from %d.%d to %d.%d \n",ItemDBName(AiItemFind(id)),
				basefrom.x,basefrom.y,baseto.x,baseto.y);
		}
	}

exit:
	
	allowweak = 0;
	goalout = startout = 0;

}

static char hexmap[] =
    {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

static void mapnum(int n, IPOINT index)
{
    if (n >= 100)
    {
        // if number would collide with new display
        if (the_map.numeric_pads_layer[index-1]) return;
        if (the_map.numeric_pads_layer[index-2]) return;
        if (the_map.numeric_pads_layer[index-3]) return;
		SET_DEBUG_LAYER(index-3, hexmap[n / 100]);
        n = n % 100;   // remainder under 100
		SET_DEBUG_LAYER(index-2, hexmap[n / 10]);
        n = n % 10;   // remainder under 10
 		SET_DEBUG_LAYER(index-1, hexmap[n]);
    }
    else if (n >= 10)
    {
        // if number would collide with new display
        if (the_map.numeric_pads_layer[index-1]) return;
        if (the_map.numeric_pads_layer[index-2]) return;
		SET_DEBUG_LAYER(index-2, hexmap[n / 10]);
        n = n % 10;   // remainder under 10
		SET_DEBUG_LAYER(index-1, hexmap[n]);
     }
}

void ShowMap(int target){

    COLORREF color = layerColor;
    if (displayed == 1) return;
    if (!aiInitialized) return;
    displayed = 1;
#ifndef FINAL
    IPOINT index; char c = 0;

    // mark all 
    WALKGRID(index){
        c = 0;

        if (OFF_EDGE(index))
        {
            SET_DEBUG_LAYER(index, c);
            continue;
        }   

        if (mapView == TEMPORARY_MAP){ /* tmp vs perm trafficable */
            if (pMines[index] & -1) c = '?';
            else if (pNoVehicleRoute[index] &
                (PLAYER1_BIT|PLAYER2_BIT|PLAYER3_BIT|PLAYER4_BIT))
            {
                if (!(pNoVehicleRoute[index] & OK_BIT)) c = ',';
                else if (UntrafficableUnit(index)) c = 'G'; // blocked now
                else c = 'g';
            }
            else if (!UntrafficableUnit(index)) // can go here
            {
                c = 0;
                if (!(pNoVehicleRoute[index] & OK_BIT)) c = '~';
            }
            else if (the_map.triggers[index] & TEMPORARY_OBJECT) c = '-';
			else if (pVehicleBlock[index]) c = 'v';
            else c = '+';
        }
		else if (mapView == VIS_MAP)
		{
			c = '0' + the_map.vis_layer[index];
			if( c == '0' )	c = 0;
		}
        else if (mapView == CONTOUR_MAP){ /* avaible routings */
            int n = 0;
            if (the_map.triggers[index] & TRIGGER_WATER) 
				c = 'w';
            else if (UntrafficableUnit(index))
            {
                c = '+';
			}
            else if (pNoVehicleRoute[index]&WIDE_BIT) c = '.';
         }
		else
        if (mapView == BIT_PAD_MAP && !UntrafficableUnit(index)){ /* bit pads */
            if (the_map.bit_pads_layer[index] == 1) c = '0';
            else if (the_map.bit_pads_layer[index] == 2) c = '1';
            else if (the_map.bit_pads_layer[index] == 4) c = '2';
            else if (the_map.bit_pads_layer[index] == 8) c = '3';
            else if (the_map.bit_pads_layer[index] == 16) c = '4';
            else if (the_map.bit_pads_layer[index] == 32) c = '5';
            else if (the_map.bit_pads_layer[index] == 64) c = '6';
            else if (the_map.bit_pads_layer[index] == 128) c = '7';
            else if (the_map.bit_pads_layer[index]) c = '?'; // mixed
        }
		else
        if (mapView == PAD_MAP && !UntrafficableUnit(index)){ /* pads */
          c = the_map.numeric_pads_layer[index];
          if (c)	{
			  if (c > 15){
                  c = '>'; // higher than 15
                  mapnum(the_map.numeric_pads_layer[index],index);
              }
			  else c = hexmap[c];
		  }
        }
		else
		if( mapView == ELEVATION_MAP )
		{
			c = ELEVATION(the_map.elevation_layer[index]);
			if( c )
				c = hexmap[c];
		}
        SET_DEBUG_LAYER(index, c);
    }

    OBJECT* pObj;
	int i;
    if (mapView == TEMPORARY_MAP) /* reveal all mines */
    {
        for (i = 0; i < the_map.num_objects; ++i)
        {
            pObj = &the_map.objects[i];
            if (pObj->category == EXPLOSIVES &&  pObj->number == ARMY_MINE);
            else continue;
 
           index = pObj->common.tile;
            if (!index) continue;
            SET_DEBUG_LAYER(index, 'm');
        }
    }

    DisplayDebugLayer(color);
#endif
}

static ccRedir[] ={6,6,0,0,2,2,4,4,6,6,0,0,2,2,4,4};

static int PerimOffBlock(IPOINT index)
{
	int off = 0;
	if (OFF_X(IPOINT_X(index))) off = 1;
	if (OFF_Y(IPOINT_Y(index))) off = 1;
	else if (!(*NotAllowed)(index)) off  = 1; // found the unblocked point
	return off;
}

static void FindFullLoop(IPOINT before,IPOINT at,IPOINT *pts){
// before is off the untrafficable  object point
// at is on the untrafficable point or block
// pts is where to store the perimeter list

	int dir,diff,zd; IPOINT *ptr = pts;
    IPOINT start = before,index,fill; long ncnt = PERIM_MAX - 30;
    *ptr = 0; // initial 0 length and old value of 0

    /* find initial directioning */
    diff = at - before;
    for (dir = 0; dir <= 7; ++dir) if (scandir[dir] == diff) break;

    ASSERT(dir <= 7); //loop ring bad start

	// we sweep our cane pointing onto the block slowly out until it becomes
	// unblocked, or hits offmap
	while (1) {/* now loop around entity til done. find next non-id pt*/
        if (--ncnt == 0)
		{
			*pts = 0;
			ptr = pts; 
			ASSERT("ERROR: fullring exhaused\n"); 
			break;
		}
        ++dir;		/* try next block8 perim direction */
        if (dir > 14)
        {
          TRACE("Unable to escape black hole in route planner\n");
            *pts = 0;
  			ptr = pts; 
			return;
        }
        index = before + scandir[dir]; // the maybe not blocked pt 
		if (PerimOffBlock(index)){// perim pt (not blocked or too close to edge)

            // because we dont want any lines drawn to miss the perim, we must
            // interpolate all diagonal moves
            // if went diag, check to see if fill in needed */
            zd = index - before;
            if (zd == (UP1+RIGHT1) || zd == (UP1+LEFT1) ||
                zd == (DOWN1+LEFT1) || zd == (DOWN1+RIGHT1)){
                fill = before + scandir[dir+1];
                if (PerimOffBlock(fill)){
                    *++ptr = fill;
                    // see if full loop has been built (be careful of pinches)
                    if (fill == pts[2] && *(ptr-1) == pts[1] && ptr != &pts[2])
                        break;
                }
            }
            if (*ptr != index){
                *++ptr = index; // save non-repeated perim pt 
                // see if full loop has been built (be careful of pinches)
                if (index == pts[2] && *(ptr-1) == pts[1] && ptr != &pts[2])
                    break;
            }
			before = index;			/* new viewpoint on perim */
            dir = ccRedir[dir];		// point from new perim back to last block

        }
    }
    *pts = (ptr - pts) - 2; // number of elements stored in [0](less 2 repeats)
    ASSERT(*pts < PERIM_MAX);
}


static cRedir[] ={10,12,12,14,14,8,8,10,10,12,12,14,14,8,8,10};

void SetAIMapDisplay(int n){

    displayed = 0;			// trigger refresh
    mapView = (MAP_VIEW)n;			// what mode to show
    ShowMap(0);
}

long TileDistance(IPOINT a,IPOINT b){/* in tile units */

    int xdif = IPOINT_X(a) - IPOINT_X(b);
    int ydif = IPOINT_Y(a) - IPOINT_Y(b);
    if (xdif < 0) xdif = -xdif;
    if (ydif < 0) ydif = -ydif;
    if (xdif > ydif) return xdif + ydif - (ydif >> 1);
    else return xdif + ydif - (xdif >> 1);
}


//******************************************************
//*			A* route searcher
//******************************************************
static long SearchDistance(IPOINT a,IPOINT b){/* in tile units */

    int xdif = IPOINT_X(a) - IPOINT_X(b);
    int ydif = IPOINT_Y(a) - IPOINT_Y(b);
    if (xdif < 0) xdif = -xdif;
    if (ydif < 0) ydif = -ydif;
	xdif <<= 3;
	ydif <<= 3;
    if (xdif > ydif) return xdif + ydif - (ydif >> 1);
    else return xdif + ydif - (xdif >> 1);
}

static void Consider(int gCost){// try expanding to this tile

    int hCost,estCost; IPOINT sibling,*better; NODE* node;
    if ((*NotAllowed)(newloc)) 
		return; 				// cannot go here

    node = &nodeList[newloc];						// our node

    if (node->searchID == searchID) 
		return; // been here already

    if (showdot)
        ShowTile(newloc);

    // replacement searchdistance
    int xdif = IPOINT_X(newloc) - IPOINT_X(goalloc);
    int ydif = IPOINT_Y(newloc) - IPOINT_Y(goalloc);
    if (xdif < 0) xdif = - xdif;
    if (ydif < 0) ydif = - ydif;
    hCost = xdif + ydif;

    hCost += hCost >> 1;						// 50 % penalty far away
    int tmp;
    tmp = pNoVehicleRoute[newloc];

    // if this is not wide, charge more for difficulty clearing edges
    if (!(tmp & WIDE_BIT) && !isunit) hCost += 50;
    if (!(tmp & OK_BIT))
    {
        if (!isunit) hCost += 100;
        else hCost += 10;
    }

    // if we are on thin ice, see if we finally got off. We will sometime
    if (allowweak)
    {
        if (pNoVehicleRoute[newloc] & OK_BIT) allowweak = 0;
    }


    node->hCost = hCost + 1;					// stored in node

    ++searched;									// statistic

    node->searchID = searchID;					// mark been here

    node->from = atloc;								// backward walk chain

    // cost to get here is cost from prior + speed cost
    node->gCost =  gCost  + 1;	// cost to onto here

    // if this is not wide, charge more for difficulty clearing edges
    if (!(tmp&WIDE_BIT) && !isunit) node->gCost += 50;
    if (!(tmp&OK_BIT))
    {
        if (!isunit) gCost += 100;
        else gCost += 10;
    }

    // now store this now in sorted open q  (normalized)
    estCost = (node->gCost + hCost - baseCost) >> 2;
 	estCost += ((3*PRIORITY_LIMIT)/4);
	if (estCost > minPriority) minPriority = estCost; // stat
    if (estCost < maxPriority) maxPriority = estCost; // stat
     // limit cost to range
    if (estCost > PRIORITY_LIMIT) 
		estCost = PRIORITY_LIMIT;
	else if (estCost < 0) estCost = 0;
    node->est = estCost;							// store our q value
    better = &priorityList[estCost]; 				// priority q location
    sibling = *better;								// current q list
    nodeList[sibling].parent = newloc; 				// he to us (dont care 0)
    node->sibling = sibling;						// chain others to us
    node->parent = 0;								// we no prior
    *better = newloc;   							// we now head the q
    if (better < highWater) highWater = better; 	// restart better scan?
}

static void GenerateNeighbors(){// find places to go to from here

    atNode = &nodeList[atloc];
    IPOINT sibling = atNode->sibling;
    int diff,gCost;
    gCost = atNode->gCost;
    *highWater = sibling; 							// remainder of list
    nodeList[sibling].parent = 0;					// he has no parent
    atNode->sibling = 0;							// we not on list now
    newloc = atloc;
    diff = atloc - atNode->from ;
    // prefer to walk the way you were walking
    if (diff == UP1)
    {
        newloc +=  UP1;        	Consider(gCost);
        newloc += RIGHT1;	   	Consider(gCost);
        newloc += DOWN1;    	Consider(gCost);
        newloc += DOWN1;		Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
        newloc += UP1;		    Consider(gCost);
        newloc += UP1;	        Consider(gCost);
    }
    else if (diff == DOWN1)
    {
        newloc += DOWN1;       	Consider(gCost);
        newloc += LEFT1;	   	Consider(gCost);
        newloc += UP1;	    	Consider(gCost);
        newloc += UP1;			Consider(gCost);
        newloc += RIGHT1;	    Consider(gCost);
        newloc += RIGHT1;	    Consider(gCost);
        newloc += DOWN1;	    Consider(gCost);
        newloc += DOWN1;        Consider(gCost);
    }
    else if (diff == LEFT1)
    {
        newloc += LEFT1;	   	Consider(gCost);
        newloc += UP1;	    	Consider(gCost);
        newloc += RIGHT1;	    Consider(gCost);
        newloc += RIGHT1;	    Consider(gCost);
        newloc += DOWN1;	    Consider(gCost);
        newloc += DOWN1;        Consider(gCost);
        newloc += LEFT1;        Consider(gCost);
        newloc += LEFT1;        Consider(gCost);
    }
    else if (diff == RIGHT1)
    {
        newloc += RIGHT1;        Consider(gCost);
        newloc += DOWN1;        Consider(gCost);
        newloc += LEFT1;        Consider(gCost);
        newloc += LEFT1;        Consider(gCost);
        newloc += UP1;		   	Consider(gCost);
        newloc += UP1;	    	Consider(gCost);
        newloc += RIGHT1;	    Consider(gCost);
        newloc += RIGHT1;	    Consider(gCost);
    }
    else if (diff ==(UP1+RIGHT1))
    {        
        newloc +=  UP1+RIGHT1; 	Consider(gCost);
        newloc += DOWN1;    	Consider(gCost);
        newloc += DOWN1;		Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
        newloc += UP1;		    Consider(gCost);
        newloc += UP1;	        Consider(gCost);
        newloc += RIGHT1;	   	Consider(gCost);
    }
    else if (diff ==  (UP1+LEFT1))
    {
        newloc +=  UP1+LEFT1; 	Consider(gCost);
        newloc += RIGHT1;	   	Consider(gCost);
        newloc += RIGHT1;	   	Consider(gCost);
        newloc += DOWN1;    	Consider(gCost);
        newloc += DOWN1;		Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
        newloc += UP1;		    Consider(gCost);
    }
    else if (diff ==  (DOWN1+LEFT1))
    {
        newloc +=  DOWN1+LEFT1;	Consider(gCost);
        newloc += UP1;		    Consider(gCost);
        newloc += UP1;		    Consider(gCost);
        newloc += RIGHT1;	   	Consider(gCost);
        newloc += RIGHT1;	   	Consider(gCost);
        newloc += DOWN1;    	Consider(gCost);
        newloc += DOWN1;		Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
    }
    else if (diff == (DOWN1+RIGHT1))
    {
        newloc +=  DOWN1+RIGHT1;	Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);        
        newloc += UP1;		    Consider(gCost);
        newloc += UP1;		    Consider(gCost);
        newloc += RIGHT1;	   	Consider(gCost);
        newloc += RIGHT1;	   	Consider(gCost);
        newloc += DOWN1;    	Consider(gCost);
    }
    else
    {
        newloc +=  UP1;        	Consider(gCost);
        newloc += RIGHT1;	   	Consider(gCost);
        newloc += DOWN1;    	Consider(gCost);
        newloc += DOWN1;		Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
        newloc += LEFT1;	    Consider(gCost);
        newloc += UP1;		    Consider(gCost);
        newloc += UP1;	        Consider(gCost);
    }
}

// THIS IS A SUBSET A* search. We dont repropagate when we find a
// shorter way to a point.    

static void Search(IPOINT from,IPOINT to,int control,IPOINT* ways){
    /* find your way */

    NODE *node = &nodeList[from];


    unsigned long *goal = &(nodeList[to].searchID);
    highWater = priorityList;
    goalloc = to;

    // replacement searchdistance
    int xdif = IPOINT_X(from) - IPOINT_X(to);
    int ydif = IPOINT_Y(from) - IPOINT_Y(to);
    if (xdif < 0) xdif = - xdif;
    if (ydif < 0) ydif = - ydif;
    baseCost = xdif + ydif;
    
    maxPriority = PRIORITY_LIMIT;
    minPriority =  searched = 0;	// stats

    /* init our start */
    node->searchID = ++searchID;			/* note been here */
    node->gCost = 0;						/* initial cost is free */
    node->sibling = 0;						/* no priorityq brothers*/
    node->from = 0;							/* we are Adam */
    node->est = baseCost;					/* our starting estimate */

    *highWater = from;						/* priority q begins here */
 
    while (highWater <= priorityEnd){ 				// next highest to expand
        atloc = *highWater;							// 1st node in q
        if (atloc){									// process next node
            GenerateNeighbors();					// spawn all neighbors
 			if (*goal == searchID) break; 			// goal found
	      }
        else ++highWater;
    }

    // clear out remaining entries
    ZeroMemory(highWater,((PRIORITY_LIMIT+1) - (highWater - priorityList))
                         * 2); /* size of each element */
                   
    // reverse the route to go from FROM to TO                   
    IPOINT prior,waypoint = to;
	to = 0;
    while (waypoint){ /* reverse the route */
        node = &nodeList[waypoint];
        prior = node->from;
        node->from = to; 			// forward point along route
        to = waypoint;
        waypoint = prior;
    }

    // store the route
    waypoint = from;
	// router failed to find the route! huh?
	if (to != from)
		waypoint = 0;

    IPOINT* ptr = ways;
    while (waypoint){ /* reverse the route */
        *++ptr = waypoint;
        waypoint = nodeList[waypoint].from;
    }

    *ways = ptr - ways; // store count
    ASSERT(*ways < PERIM_MAX);
}


void SetTrafficableOverride(IPOINT index,int eArmy)
{
    int bit;
    if (eArmy == ARMY_INDEPENDENT) // allow all armies thru here
        bit = PLAYER1_BIT | PLAYER2_BIT | PLAYER3_BIT | PLAYER4_BIT;
    else bit = PLAYER1_BIT  << eArmy; // allow only player army thru here
    
    pNoVehicleRoute[index] |= bit;
}

void SelectUntrafficableFunction(int control,UID uid)
{
     if (control & JEEP_ROUTE) NotAllowed =  SearchUntrafficableVehicle;
     else if (control & TANK_ROUTE) NotAllowed =  SearchUntrafficableVehicle;
     else if (control & HALFTRACK_ROUTE) NotAllowed =  SearchUntrafficableVehicle;
     else if (control & CONVOY_ROUTE) NotAllowed =  SearchUntrafficableVehicle;
     else NotAllowed = SearchUntrafficableUnit;

     int bit;
     bit = EXTRACT_ARMY(uid);
     if (bit == ARMY_INDEPENDENT)
         searchArmyBit = PLAYER1_BIT |PLAYER2_BIT |PLAYER3_BIT |PLAYER4_BIT;
     else
         searchArmyBit = PLAYER1_BIT << bit;
}

static int SearchTileLegalLine(IPOINT from, IPOINT to, IPOINT *pts){
// find set of points along a line  
    
    int xdif, ydif,xstep,ystep,i, xcnt,ycnt,n = 1;
    int fromx = IPOINT_X(from);
    int fromy = IPOINT_Y(from);
    int tox = IPOINT_X(to); IPOINT index;
    int toy = IPOINT_Y(to);
    pts[n] = from;

	/* set up step count and increment */
	xdif = tox - fromx;
	ydif = toy - fromy;
    xstep = (xdif >= 0) ? xdif : -xdif;
    ystep = (ydif >= 0) ? ydif : -ydif;
    xcnt = ycnt = 0;
    if (xstep >= ystep){ /* walk x */
        xdif = (xdif > 0) ? 1 : -1;

        /* now step one point at a time */
        for (i=1; i <= xstep; ++i) {
            /* per step expected location */
            fromx += xdif;
            ycnt += ydif;
            ystep = (ycnt / xstep) + fromy;
            index = INDEX(fromx,ystep);

            // if two blocked pts occur in a row, see if can interpolate 
            // unblocked pt
            if ((*NotAllowed)(index) && (*NotAllowed)(pts[n])){
                int xd = fromx - IPOINT_X(pts[n]);
                int yd = ystep - IPOINT_Y(pts[n]);
                if (xd && yd){ /* a diagonal move */
                    IPOINT adj = index - xd;
                    if ((*NotAllowed)(adj)) adj = index - INDEX_ENCODED_Y(yd);
                    if (!(*NotAllowed)(adj)) pts[++n] = adj;
                }
            }

            pts[++n] = index;
        }
    }
    else{
        ydif = (ydif > 0) ? 1 : -1;

        /* now step one point at a time */
        for (i=1; i <= ystep; ++i) {
            fromy += ydif;
            xcnt += xdif;
            xstep = (xcnt / ystep) + fromx;
            index = INDEX(xstep,fromy);
            // if two blocked pts occur in a row, see if can interpolate 
            // unblocked pt
            if ((*NotAllowed)(index) && (*NotAllowed)(pts[n])){
                int xd = xstep - IPOINT_X(pts[n]);
                int yd = fromy - IPOINT_Y(pts[n]);
                if (xd && yd){ /* a diagonal move */
                    IPOINT adj = index - xd;
                    if ((*NotAllowed)(adj)) adj = index - INDEX_ENCODED_Y(yd);
                    if (!(*NotAllowed)(adj)) pts[++n] = adj;
                }
            }

            pts[++n] = index;
        }
    }

	if (pts[n] != to) 
	{
		TRACE("SearchTileLegalLine didnt end up at goal\n");
		n = 0;
	}
    if (n >= PERIM_MAX) DoFatal("ERROR: Path line too long\n");
    pts[0]  = n;
    return n;
}

void MineAdded(IPOINT tile,int eArmy)
{
    int bit =  PLAYER1_BIT << eArmy;
    if (eArmy == ARMY_INDEPENDENT) return; // ignore unowned mines, we cant see
    pMines[tile] |= bit;

    pMines[tile+LEFT1] |= bit;
    pMines[tile+RIGHT1] |= bit;
    pMines[tile+UP1] |= bit;
    pMines[tile+DOWN1] |= bit;

    pMines[tile+LEFT1+UP1] |= bit;
    pMines[tile+RIGHT1+UP1] |= bit;
    pMines[tile+LEFT1+DOWN1] |= bit;
    pMines[tile+RIGHT1+DOWN1] |= bit;
}

static int MineHere(IPOINT tile)
{
    ITEM* pItemList; int ans = 0;
	OBJECTSTRUCT *pObject;
    SPOINT point;
    point= CenterPointFromTile(tile);
	pItemList = GetObjectsIntersectPoint(&point);
	while( pItemList != NULL )
	{
        pObject = (OBJECTSTRUCT *)pItemList;
		if (ITEM_TYPE( pItemList ) != ARMY_OBSTACLE) goto next;
		if (pObject->category != EXPLOSIVES) goto next;
        if (pObject->number != ARMY_MINE) goto next;
        // unowned mines cannot be seen by anyone, so are ignored
        if (pObject->owner == ARMY_INDEPENDENT) goto next;

		// prove this mine is placed on this tile and not slopping from nearby
		if (!SameSPoint(point,pObject->common.position)) goto next;
	
		ans |=  PLAYER1_BIT << pObject->owner;
  
next:
		pItemList = pItemList->next;
    }
    return ans;
}


static void ResetMine(IPOINT tile)
{
    int mines;
    // see what mines exist on the 4 neighbor points as well as this point
    // for each player
    mines = MineHere(tile);
	mines |=  MineHere(tile+LEFT1);
	mines |=  MineHere(tile+RIGHT1);
	mines |=  MineHere(tile+UP1);
	mines |=  MineHere(tile+DOWN1);
	mines |=  MineHere(tile+LEFT1+UP1);
	mines |=  MineHere(tile+RIGHT1+UP1);
	mines |=  MineHere(tile+LEFT1+DOWN1);
	mines |=  MineHere(tile+RIGHT1+DOWN1);
           ;			
    pMines[tile] = mines;
}

void MineDeleted(IPOINT tile)
{
    ResetMine(tile);
    ResetMine(tile+LEFT1);
    ResetMine(tile+RIGHT1);
    ResetMine(tile+UP1);
    ResetMine(tile+DOWN1);

    ResetMine(tile+LEFT1+UP1);
    ResetMine(tile+RIGHT1+UP1);
    ResetMine(tile+LEFT1+DOWN1);
    ResetMine(tile+RIGHT1+DOWN1);
}

void FlipTrafficable(SPOINT pt)
{
    return;
}

int Adj8(IPOINT from,IPOINT to)
{
    int difx = IPOINT_X(from) - IPOINT_X(to);
    int dify = IPOINT_Y(from) - IPOINT_Y(to);
    return (difx >= -1 && difx <= 1 && dify >= -1 && dify <= 1);
}