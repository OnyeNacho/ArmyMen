#ifndef __NEWDOOR_H__
#define __NEWDOOR_H__

// things we can show on the map
typedef enum
{
    NO_MAP = 0,						// not being displayed
    TEMPORARY_MAP,					// tmp/perm obstructions
    CONTOUR_MAP,					// elevation contours
    BIT_PAD_MAP,					// where is there bit pads
    PAD_MAP,							// where is there pads
	ELEVATION_MAP,
	VIS_MAP
} MAP_VIEW;

extern MAP_VIEW mapView;			// debug_layer shows this

// routes we can generate
#define STD_ROUTE 1					// generate a good way
// do you want waypoints only or the full list
#define COLLAPSE	64				// only show waypoints needed
#define FULLLIST	4				// show complete list of points of doable

typedef int (*TESTOK)(IPOINT index); 	// define a standard traffficable
extern TESTOK NotAllowed;

#define UNIT_ROUTE	0	
#define JEEP_ROUTE	512
#define TANK_ROUTE	1024
#define HALFTRACK_ROUTE	2048
#define CONVOY_ROUTE	4096


extern unsigned long gridmax;

extern int displayed;				/* showmap already showing? */

#define WALKGRID(i)   for (i = 0; i < gridmax; ++i)
#define TILE_BOUNDARY 5				/*  wall tiles to bound map with */
#define VISIBLE_BOUNDARY 14			/*  screen view of user to bound map with*/
#define OFF_X(p) (p < TILE_BOUNDARY || p  >= (map_width-TILE_BOUNDARY))
#define OFF_Y(p) (p < TILE_BOUNDARY || p  >= (map_height-TILE_BOUNDARY))
#define ONEDGE(p) (OFF_X(IPOINT_X(p)) || OFF_Y(IPOINT_Y(p)))

extern unsigned char *pNoVehicleRoute;

#define OFF_EDGE(p) (pNoVehicleRoute[p] & OFFEDGE_BIT)

#define OFF_VISIBLE_X(p) (p < VISIBLE_BOUNDARY || p  >= (map_width-VISIBLE_BOUNDARY))
#define OFF_VISIBLE_Y(p) (p < VISIBLE_BOUNDARY || p  >= (map_height-VISIBLE_BOUNDARY))

// transient marker data 
extern unsigned char* pMarkers;
/* mark is used during initialization */
#define MARKED_BIT 0x01	
#define MARKED(x) (pMarkers[x] & MARKED_BIT)
#define MARK(x)   pMarkers[x] |= MARKED_BIT
#define CLEARMARK(x) pMarkers[x] &= -1 ^ MARKED_BIT

extern int tracerouter;						// trace it

#define BLOCKED(index) (the_map.movement_layer[index] >= 15)

    
// directions on a map grid in IPOINT notation
#define UP1 (-map_width)
#define DOWN1 (map_width)
#define LEFT1 (-1)
#define RIGHT1 (1)         

void ShowMap(int n);
int TileLegalLine(IPOINT from, IPOINT to, IPOINT *pts);
int TileLine(IPOINT from, IPOINT to, IPOINT *pts);
int cross(IPOINT pt,IPOINT from,IPOINT to);
void AiMapExit( void );
void SetAIMapDisplay(int n);
long TileDistance(IPOINT a,IPOINT b);/* in tile units */
void PlanRoute(UID id,
        int control,				   // restrictions on routing process
        SPOINT basefrom,SPOINT baseto, // from and to of route
        SPOINT* waypoints, // place to put route
        int maxway); // max number of points allowed in routing

int UntrafficableUnit(IPOINT index);
void SetTrafficableOverride(IPOINT index,int eArmy);
void SetWidth1(IPOINT index);

void SelectUntrafficableFunction(int flags,UID uid);

void MineAdded(IPOINT tile,int eArmy);
void MineDeleted(IPOINT tile);
void AiMapInit();
void AiMapAllocate();
int OffVisible(IPOINT index);

int Adj8(IPOINT from,IPOINT to);

// bits on pNoVehicleRoute
#define OFFEDGE_BIT 1		// point is on edge area
#define WIDE_BIT 2			// point is 3 from nearest block
#define OK_BIT 8			// point is  2 from nearest block
#define PLAYER1_BIT 16		// gate becomes trafficable
#define PLAYER2_BIT 32		// gate becomes trafficable
#define PLAYER3_BIT 64		// gate becomes trafficable
#define PLAYER4_BIT 128		// gate becomes trafficable

extern char* pVehicleBlock;

#endif
