//*******************************************************
//	AIROUTER.cpp performs route planning for all units
//	and the ai controlled vehicles.
//*******************************************************

#ifndef __AIROUTER_H__   
#define __AIROUTER_H__   

#define MAXMORE 100
     
typedef struct{
    SPOINT destination;		// location to end up at
    char arrived;			// waiting at destination
    int flags;				// control over router to use
    SPOINT waypoint;		// current marching to (could == destination)
    int nWaypoints;			// how many stacked up extra
    SPOINT moreWaypoints[MAXMORE+1]; // remaining precomputed waypoints
    int stuckWhen;			// last time was stuck (-1 == route failed)
    int cycleCalled;		// when was this routing generated.
                            // If this was the 2nd time this turn, give detail
    SPOINT from;			// departure point
    UID	   owner;			// uid of who this router is for

    int delayUntil;			// wait for this cycle before trying any again     
    int stuckfixing;		// no straightens until this goes to zero
} ROUTEDATA;

SPOINT AIRouter(SPOINT goal,ROUTEDATA* routeData,int flags,
                SPOINT from,int facing);
// flags come from newdoor.h, returns non-zero waypoint if can go
// if given destination already given before, gives more through answer

void RouterDraw(HDC hDC, SPOINT start, ROUTEDATA* routeData,COLORREF color);
// draws lines on back buffer of route

void RouterArrive(ROUTEDATA* routeData);
// indicate goal has been met, no new goal given yet

void RouterWaypointArrive(ROUTEDATA* routeData);
// indicate waypoint has been met

void RouterLineRouter(SPOINT goal,ROUTEDATA* routeData);
// store a trivial routing

BOOL SameSPoint(SPOINT x,SPOINT y);


#endif		// airouter.h
