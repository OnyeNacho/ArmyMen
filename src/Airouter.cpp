/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Airouter.cpp $
//
//	DESCRIPTION:	ai commander
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Airouter.cpp 53    4/02/98 2:02p Phu $
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Airouter.cpp $
//  
//  53    4/02/98 2:02p Phu
//  typecasting to prevent warnings
//  
//  52    3/31/98 2:46p Bwilcox
//  cleanups and better script debug
//  
//  51    3/17/98 6:06p Bwilcox
//  proper null checking around aiitemfind calls
//  
//  50    3/07/98 11:49p Nrobinso
//  move .h file to stdafx; setup macro for debug layer
//  
//  49    2/26/98 1:16p Bwilcox
//  improvingvehicle control routings
//  
//  48    2/04/98 11:06a Bwilcox
//  router performance tuning and draw fixes
//  
//  47    2/02/98 12:10p Bwilcox
//  removed airouter uid field
//  
//  46    1/30/98 10:58a Bwilcox
//  fixed airouter some more
//  
//  45    1/30/98 10:23a Bwilcox
//  routedata fix
//  
//  44    1/29/98 6:13p Bwilcox
//  straighter routeplanning paths
//  
//  43    1/26/98 1:58p Bwilcox
//  router fixing to center of tile
//  
//  42    1/20/98 12:45p Bwilcox
//  code to routeplan thru gates
//  
//  41    1/15/98 4:54p Bwilcox
//  more router fixes
//  
//  40    1/15/98 3:41p Bwilcox
//  more router fixes (fulllist optimization) and trooper fixdireciton fid
//  
//  39    1/15/98 12:13p Bwilcox
//  
//  38    1/14/98 3:15p Bwilcox
//  
//  37    1/14/98 3:14p Bwilcox
//  
//  36    1/14/98 8:25a Bwilcox
//  fix to trooper routing system
//  
//  35    1/13/98 3:12p Bwilcox
//  router fix to remove excess lines drawn
//  
//  34    1/13/98 8:36a Bwilcox
//  routingdraw now selects none, frnd, frnd.foe
//  
//  33    1/09/98 12:33p Bwilcox
//  trooper collision override added 
//  airouter overshoot now allows 1 tile at no rerouting cost
//  
//  32    1/05/98 11:34a Bwilcox
//  removed dead code in newdoor and added route straightener to airouter
//  
//  31    12/24/97 2:48p Bwilcox
//  fixing nestfire behavior
//  
//  30    12/19/97 12:33p Bwilcox
//  converting epoint to spoint notation
//  
//  29    12/18/97 6:55p Bwilcox
//  revised planroute args
//  
//  28    12/12/97 12:24p Phu
//  
//  27    12/10/97 12:51p Bwilcox
//  improved trace on failure
//  
//  26    12/09/97 5:10p Bwilcox
//  fixed maxmore use
//  
//  25    12/09/97 4:05p Bwilcox
//  fixed maxmore bug
//  
//  24    12/09/97 3:22p Bwilcox
//  
//  23    12/09/97 12:11p Phu
//  
//  22    11/19/97 8:41a Bwilcox
//  
//  21    11/17/97 10:48p Bwilcox
//  debug data added to routeplanner
//  
//  20    11/11/97 5:37p Bwilcox
//  if routing cannot be had, will not be recomputed unless position or
//  goal changes
//  
//  19    10/29/97 4:02p Bwilcox
//  preparing for movement layers per army
//  
//  18    10/29/97 12:57p Bwilcox
//  better vehicle controller
//  
//  17    10/28/97 4:32p Bwilcox
//  overshoot moved into route planner
//  troopers try to stay separated
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "army.h"
#include "newdoor.h"
#include "anim.h"

#include "Airouter.h"
#include "aibtank.h"
        
#define AI_FRIEND 1			# enable private visibility in AIX
#include "aix.h"
#include "map.h"
#include "item.h"
#include "aiaccess.h"
extern char routingDraw;

int Overshot(ROUTEDATA* routeData,SPOINT at);
static void Straighten(ROUTEDATA* routeData);
void ShowTile(IPOINT tile);
void ShowSpoint(SPOINT x);


static SPOINT RouterUpdateWaypoints(SPOINT current,ROUTEDATA* routeData);
// returns non-zero spoint of current waypoint to move to

static int CanTravel(IPOINT from,IPOINT to,int vehicle){ /* is there a clear line of travel */

    int xdif, ydif,xstep,ystep,i, xcnt,ycnt,step; IPOINT index;
    int fromx,fromy,tox,toy;
    ITEM* pItemList;

    if (from == to) return TRUE;
    fromx = IPOINT_X(from);
    fromy = IPOINT_Y(from);
    tox = IPOINT_X(to);
    toy = IPOINT_Y(to);

	/* set up step count and increment */
	xdif = tox - fromx;
	ydif = toy - fromy;
    xstep = (xdif >= 0) ? xdif : -xdif;
    ystep = (ydif >= 0) ? ydif : -ydif;
    step =  (xstep >= ystep) ? xstep : ystep;

	/* now step one point at a time */
	xcnt = ycnt = 0;
	for (i=1; i < step; ++i) {
        /* per step expected location */
		xcnt += xdif;
		ycnt += ydif;
        xstep = (xcnt / step) + fromx;
        ystep = (ycnt / step) + fromy;
        index = INDEX(xstep,ystep);
        /* now see what happens */
        if (!(*NotAllowed)(index)) continue; // legal to go here

        if (!vehicle) return FALSE; // troopers blocked by anything

        /* are we vehicle blocked by a vehicle? (our own) */
        SPOINT point;
        point.x = (short)IPOINT_X(index);
        point.y = (short)IPOINT_Y(index);
        pItemList = GetObjectsIntersectPoint(&point);
        while (pItemList){
            if (ITEM_TYPE(pItemList) == ARMY_VEHICLE)
            {
                point.x = 0;
                break;
            }
            pItemList=pItemList->next;
        }
        if (point.x == 0) continue; // ignore vehicles in our way
        
        return FALSE;			// cannot go here
    }

    return TRUE;
}

static void TransferWaypoints(SPOINT from,ROUTEDATA* routeData){
// peel off next precomputed waypoint    from list as next waypoint
    int nn = routeData->nWaypoints;
    routeData->waypoint = routeData->moreWaypoints[0];
    MoveMemory(routeData->moreWaypoints,
        &routeData->moreWaypoints[1],
            (nn-1) * sizeof(SPOINT));
    --routeData->nWaypoints; // transfer down
}

void RouterWaypointArrive(ROUTEDATA* routeData){
    
    routeData->waypoint = OFF_THE_MAP;
}

static int up1 = 0,tp1 = 0,force1 = -1;

static SPOINT RouterUpdateWaypoints(SPOINT current,ROUTEDATA* routeData){
// Find next waypoint to goal
    
    SPOINT goal;  IPOINT iCurrent,iGoal,tile; int waycount;
    if (!current.x) return OFF_THE_MAP; // dont exist on map
    
    goal = routeData->destination;
    iCurrent = ENCODE_IPOINT(current.x,current.y);
    iGoal = ENCODE_IPOINT(goal.x,goal.y);

    // check stuff about the destination
    if (iGoal == 0 || routeData->arrived) return OFF_THE_MAP;	/* dont need waypoint*/

    // at goal tile
    if (iCurrent == iGoal){
        RouterArrive(routeData);
        return OFF_THE_MAP;
    }

    // at way tile, clear current waypoint
    tile = ENCODE_IPOINT(routeData->waypoint.x,routeData->waypoint.y);
    if (tile == iCurrent)
    {
		SET_DEBUG_LAYER(iCurrent, 0);
		routeData->waypoint = OFF_THE_MAP;
    }
    // if we overshoot, recompute main routing all over again
    else if (Overshot( routeData, current))
    {
        // if major overshot, force a replan
        if (TileDistance(tile,iCurrent) >= 2)
            routeData->nWaypoints = 0; 
  		SET_DEBUG_LAYER(tile, 0);
		routeData->waypoint = OFF_THE_MAP;
    }

    // are we still in transit?
    if (routeData->waypoint.x != 0) return routeData->waypoint;

    // already have pending waypoints still to process?
    if (routeData->nWaypoints){
        if (routeData->stuckfixing) --routeData->stuckfixing;
        ASSERT(routeData->nWaypoints >= 0 && routeData->nWaypoints <= MAXMORE);
        TransferWaypoints(current,routeData);
        ASSERT(routeData->nWaypoints >= 0 && routeData->nWaypoints <= MAXMORE);
        if (routeData->waypoint.x) goto ready;
    }

    SPOINT waypoints[2000+1];
    PlanRoute(routeData->owner,routeData->flags,current,goal,waypoints,2000);

    // find a new routing
    // do a full list only this time. revert to normal thereafter
    if (routeData->flags & FULLLIST)
    {
        routeData->flags ^= FULLLIST;
        routeData->stuckfixing = 10;// go for 10 tiles before using straighten
    }
    
    waycount = waypoints[0].x;
    
    if (waycount != 0){ // ok
        // set new waypoint and where we started from
        routeData->waypoint = waypoints[2];
        
        // remaining waypoints added to q
        int i,n;
        n = 0;
        for (i = 3; i < waycount; ++i){
            if (i >= MAXMORE) break;
            routeData->moreWaypoints[n++] = waypoints[i];
        }
        routeData->nWaypoints = n;
        ASSERT(routeData->nWaypoints >= 0 && routeData->nWaypoints <= MAXMORE);
    }
    else{ // failed
        ITEM* pItem;
        if (routingDraw)
        {
            pItem = AiItemFind(routeData->owner);
            if (pItem) TRACE("%s- cant go to %d.%d from %d.%d\n",
                ItemDBName(pItem),goal.x,goal.y,current.x,current.y);
        }
        AIRouter(goal,routeData,routeData->flags,OFF_THE_MAP,0);
        routeData->stuckWhen = -1; // routing failed
        routeData->from = current;
        return OFF_THE_MAP;
    }

ready:	// have a waypoint to work on

    routeData->from = current;	// we start from here

    // now try to extend to straight line waypointing unless stuck fixing
    if (!routeData->stuckfixing)
        Straighten(routeData);

    // always use center of tile waypoint
    if (routeData->waypoint.x)
    {
        routeData->waypoint.x = ((routeData->waypoint.x >> 4) << 4) + 8;
        routeData->waypoint.y = ((routeData->waypoint.y >> 4) << 4) + 8;
    }


    return routeData->waypoint;
}

SPOINT AIRouter(SPOINT goal,ROUTEDATA* routeData,int flags,SPOINT from,
        int facing){
//set new goal (or none) and use flags to control routing
// flags are from newdoor.h

    // when we already have this goal
    if (SameSPoint(routeData->destination,goal) && goal.x && from.x){

        // we are stuck, cannot route here.
        if (routeData->stuckWhen == -1 && SameSPoint(from,routeData->from))
            return OFF_THE_MAP;

        // if this is the 1st call this turn, things are going normally
        if (routeData->cycleCalled != playCycle)
        {
            routeData->cycleCalled = playCycle;
            return RouterUpdateWaypoints(from,routeData);
        }

        // if our waypoint is already contiguous to us, return w/o new call
        if (Adj8(ENCODE_IPOINT(from.x,from.y),
                 ENCODE_IPOINT(routeData->waypoint.x,routeData->waypoint.y)))
        {
            return routeData->waypoint;
        }

        // treat as new routing call if we called it again, but give
        // tile-by-tile detail since someone is having problems getting there
        flags |= FULLLIST;
    }

    // when this is a new goal
    routeData->cycleCalled = playCycle;
    routeData->destination = goal;
    routeData->waypoint = OFF_THE_MAP; 
    routeData->nWaypoints = 0;
    routeData->arrived = 0;
    routeData->flags = flags;
    routeData->stuckWhen = 0;
    routeData->stuckfixing = 0;
    if (from.x && goal.x) RouterUpdateWaypoints(from,routeData);
    return routeData->waypoint;
}

void RouterArrive(ROUTEDATA* routeData){
// tell router we have arrived at goal
    
    // goal will be left intact, but arrived indicates we got there
    // and wont keep trying
    routeData->arrived = 1;
    routeData->waypoint = OFF_THE_MAP;
    routeData->nWaypoints = 0;
}

void RouterDraw(HDC hDC, SPOINT start, ROUTEDATA* routeData,COLORREF color){

    // not going anywhere
    if (!routeData->destination.x ||  routeData->arrived) return;
    if (routeData->waypoint.x == 0) return; // no waypoint yet
    
    int i;
	SPOINT		pointA,pointB;

	if (!hDC) return;
    pointA = start;
    if (routeData->waypoint.x){
        pointB = routeData->waypoint;
        if( ClipLine( &pointA, &pointB ) )
			DrawMultiLine( hDC, &pointA, &pointB, color, TRUE );
        for (i = 0; i < routeData->nWaypoints; ++i){
            pointA = pointB;
            pointB = routeData->moreWaypoints[i];
	        if( ClipLine( &pointA, &pointB ) )
		        DrawMultiLine( hDC, &pointA, &pointB, color, TRUE );
        }
        pointA = pointB;
    }
    pointB = routeData->destination;

    if (OBJTYPE(routeData->owner) == ARMY_UNIT) // unit goal marker
        ShowSpoint(pointB); // goal

    if( ClipLine( &pointA, &pointB ) )
	    DrawMultiLine( hDC, &pointA, &pointB, color, TRUE );
}

void RouterLineRouter(SPOINT goal,ROUTEDATA* routeData)
{
    if (SameSPoint(routeData->destination,goal)) return;
    routeData->destination = goal;
    routeData->waypoint = OFF_THE_MAP;
    routeData->nWaypoints = 0;
    routeData->arrived = TRUE;
}

int Overshot(ROUTEDATA* routeData,SPOINT at)
{
    int facing, dist,d;
	double xx,yy;
    SPOINT pperp,from,to;

    from = routeData->from;
    to = routeData->waypoint;
	d = GetDistance(&to,&at);
    // set testing distance for overshoot
    if (routeData->flags & (JEEP_ROUTE | TANK_ROUTE | HALFTRACK_ROUTE))
        dist = 100;
    else dist = 15;	// unit test close
    if (d > dist) return 0; // too far away to test
    
    facing = GetDirection(&from,&to);
    facing = NormalizeFacingAdd(facing,64); // 90 degree line aim

    // pick a point 32 pixels away (2 tiles) on the perpendicular
    xx = cos_table[facing] * 32;
	yy = sin_table[facing] * 32;
	pperp.x = (short)(to.x + xx);
    pperp.y = (short)(to.y + yy);
    facing = cross(ENCODE_IPOINT(to.x,to.y),ENCODE_IPOINT(pperp.x,pperp.y),
                   ENCODE_IPOINT(at.x,at.y));

	if (facing >= 0)
        return TRUE;
	return FALSE;
}


BOOL SameSPoint(SPOINT x,SPOINT y)
{
    if (x.x ==  y.x && x.y == y.y) return TRUE;
    return FALSE;
}

static void Straighten(ROUTEDATA* routeData){
// see if can go in direct line toward farther waypoint

    int i;
    int n = routeData->nWaypoints;
    IPOINT at = ENCODE_IPOINT(routeData->from.x,routeData->from.y);
    IPOINT to;
	BOOL bVehicle;
	bVehicle = (SUB1TYPE(routeData->owner) == ARMY_VEHICLE);
    SelectUntrafficableFunction(routeData->flags,routeData->owner);// set NotAllowed function
 
   for (i = 0; i < n; ++i)
    {
        to = ENCODE_IPOINT(routeData->moreWaypoints[i].x,routeData->moreWaypoints[i].y);

		// vehicles have a tile of slop safety anyway, so only check 1 path
		if (bVehicle)
		{
			if (CanTravel(at,to,bVehicle)) continue;
			if (CanTravel(to,at,bVehicle)) continue;
            break;

		}
		else
		{
			// we want units to clear obstructions easily so check line both ways 
			 if (!CanTravel(at,to,bVehicle))
				 break;
			 if (!CanTravel(to,at,bVehicle))
				break;
		}
    }

    // if we used up all waypoints and they hadnt overflowed,
    // see if we can direct to goal
    if (i == n && n < (MAXMORE-1))
    {
        to = ENCODE_IPOINT(routeData->destination.x,
                           routeData->destination.y);
		// vehicles have a tile of slop safety anyway, so only check 1 path
		if (bVehicle)
		{
			if (CanTravel(at,to,bVehicle));
			else if (CanTravel(to,at,bVehicle));
			else to = 0;
		}
		else
		{
			// we want units to clear obstructions easily so check line both ways 
			if (!CanTravel(at,to,bVehicle)) to = 0;
			else if (!CanTravel(to,at,bVehicle)) to = 0;
		}
		if (to != 0) // we can optimize this ok.
        {
            // remove all waypoints
            routeData->nWaypoints = 0;
            routeData->waypoint = routeData->destination;
            return;
        }
    }

    // no improvement possible
    if (i == 0) return; 

    // now go direct to last ok contiguous waypoint
    routeData->waypoint = routeData->moreWaypoints[i-1];
    MoveMemory(routeData->moreWaypoints,
               &routeData->moreWaypoints[i],
               (n-i) * sizeof(SPOINT));

    routeData->nWaypoints -= i;
}