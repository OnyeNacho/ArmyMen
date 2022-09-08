/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Aibtank.cpp $
//
//	DESCRIPTION:	ai commander
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Aibtank.cpp 129   4/16/98 11:54a Bwilcox $
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Aibtank.cpp $
//  
//  129   4/16/98 11:54a Bwilcox
//  tadsmart activation
//  
//  128   4/14/98 10:29a Bwilcox
//  switch playcycle to elapsed time printout,
//  optimize trooper no routing when fail on victim
//  
//  127   4/13/98 10:46p Bwilcox
//  ai order failures delay 3 seconds before reporting now
//  
//  126   4/12/98 6:34p Bwilcox
//  improved ai sarge
//  
//  125   4/12/98 2:47p Bwilcox
//  swivel against sarge too
//  
//  124   4/10/98 3:23p Bwilcox
//  vehicle evade against vehicles too close to fire 
//  
//  123   4/10/98 11:32a Bwilcox
//  block mp vehicle movemnt ai
//  
//  122   4/09/98 12:47p Bwilcox
//  fixing npc sarge movement
//  
//  121   4/08/98 11:29p Bwilcox
//  
//  120   4/08/98 11:01p Nrobinso
//  fix an = to the += it should be
//  
//  119   4/08/98 4:03p Bwilcox
//  ai sarges get and use secondary weapons
//  
//  118   4/08/98 12:28p Bwilcox
//  immobilefoe applies to vehicle ai and sarge ai
//  
//  117   4/07/98 11:34p Bwilcox
//  immobilie trooper if routing failure
//  
//  116   4/07/98 4:32p Bwilcox
//  fix sarge routeplanner bug
//  
//  115   4/03/98 8:55p Bwilcox
//  clean up vehicle movement layer code
//  
//  113   4/03/98 11:25a Bwilcox
//  sarge only arrives once
//  
//  112   4/02/98 1:32p Bwilcox
//  reducing arrival messaging
//  
//  111   4/02/98 1:34p Phu
//  added some typecasts to prevent warnings
//  
//  110   4/02/98 11:58a Bwilcox
//  
//  109   4/02/98 10:45a Bwilcox
//  fixing sarge npc movement
//  
//  108   4/01/98 4:48p Bwilcox
//  stationary ai vehicles failed to raise event when blocked, fixed
//  
//  107   3/30/98 7:16p Bwilcox
//  sarge tries not to overrun onto target
//  
//  106   3/30/98 6:09p Bwilcox
//  ai sarge control
//  
//  105   3/30/98 5:53p Bwilcox
//  sarge ai control and fix captureflag on remote machines
//  
//  104   3/26/98 9:21p Bwilcox
//  
//  103   3/25/98 12:30p Bwilcox
//  fire better for vehicles against close targets
//  
//  102   3/25/98 12:06p Bwilcox
//  shoot at center of target
//  
//  101   3/18/98 12:12p Bwilcox
//  vehicle no fire if inside gun range
//  
//  100   3/06/98 12:53p Bwilcox
//  removed use of aiframe var.
//  
//  99    3/02/98 3:15p Bwilcox
//  slower vehicle routing replan rate
//  
//  98    3/02/98 1:59p Bwilcox
//  removing dead code tied to npc sarges (a concept discarded)
//  
//  97    3/02/98 12:23p Nrobinso
//  fix tank aiming
//  
//  96    2/28/98 9:35p Bwilcox
//  better vehicle control
//  
//  95    2/27/98 1:14p Bwilcox
//  cleaning up the air, supporting script airdrops for foes,e tc
//  
//  94    2/26/98 1:56p Bwilcox
//  no longer slowing down so much arriving at goal
//  
//  93    2/26/98 1:15p Bwilcox
//  improvingvehicle control routings
//  
//  92    2/26/98 12:23p Bwilcox
//  unit new code redudant with aibtank when bug fixed
//  
//  91    2/13/98 1:30p Bwilcox
//  foe vehicles no longer ram each other
//  
//  90    2/12/98 5:26p Bwilcox
//  stop vehicles wiggling backwards
//  
//  89    2/12/98 2:13p Bwilcox
//  improving vehicle control (dont accelarte on a turn)
//  
//  88    2/06/98 4:13p Bwilcox
//  trying to improve vhiecle controller
//  
//  87    2/06/98 3:54p Bwilcox
//  subroutining
//  
//  86    2/06/98 3:25p Bwilcox
//  improving vehicle controller
//  
//  85    2/06/98 2:20p Bwilcox
//  vehiclebehavior trace added
//  
//  84    2/04/98 3:29p Bwilcox
//  ixied vehicle shoot
//  
//  83    2/04/98 11:06a Bwilcox
//  router performance tuning and draw fixes
//  
//  82    1/30/98 10:23a Bwilcox
//  routedata fix
//  
//  81    1/28/98 3:52p Bwilcox
//  fixing samefacing calls 
//  
//  80    1/20/98 12:44p Bwilcox
//  code to routeplan thru gates
//  
//  79    1/17/98 7:38a Bwilcox
//  added follow_radius, and follow_engaged radius and fixed a
//  defend-radius bug
//  
//  78    1/14/98 4:28p Bwilcox
//  replaced cansee/canshoot coding
//  
//  77    1/14/98 8:25a Bwilcox
//  fix to trooper routing system
//  
//  76    1/13/98 1:44p Bwilcox
//  router inited with collapse list to use fewer waypoints on ai vehicles
//  
//  75    1/13/98 1:24p Bwilcox
//  
//  74    1/13/98 8:49a Bwilcox
//  fixing goal fix of vehcile
//  
//  73    1/13/98 8:27a Bwilcox
//  
//  72    1/13/98 8:09a Bwilcox
//  npc vehicles reaching goal will now stop there.
//  
//  71    1/02/98 2:09p Bwilcox
//  distance tests moved into canshoot
//  
//  70    1/02/98 1:24p Bwilcox
//  line of sight from a canshoot call will test for friendlies in the way.
//  Vehicle/sarge ai now checks using canshoot also
//  
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "Army.h"
#include "MainFrm.h"
#include "Map.h"
#include "Vehicle.h"
#include "Input.h"
#include "miscfile.h"
#include "map.h"
#include "Ai.h"
#include "AiAccess.h"
#include "newdoor.h"
#include "unit.h"
#include "tad.h"
#include "item.h"
#include "weapon.h"
#include "avatar.h"

// from newdoor.cpp
#define JEEP_BIT 1
#define HALFTRACK_BIT 2
#define TANK_BIT 4
#define CLOSE_ENOUGH (8 * 16) // pixels no need to replan

extern char unitBehavior;
extern char showdot;

#define AI_FRIEND 1			# enable private visibility in AIX
#include "Aix.h"
#include "damage.h"
#include "aibtank.h"
#include "trooper.h"
#include "gameflow.h"

extern char scriptDebug;

char vehicleBehavior = 0;
static void	SargeComplete(SARGE* pSarge);
static VEHICLE* myvehicle;    
static void FireVehicle(VEHICLE* pVehicle);
SPOINT ClosestCorner(SPOINT from,SPOINT to);
static void SargeFixDirection(SARGE* pSarge,SPOINT goal,ACTION pace);
static void SargeDoMove(SARGE* pSarge,SPOINT position,ACTION pace,int direction);
static BOOL SargeFireAt(SARGE* pSarge,ITEM* pVictim);


extern int VEHICLE_DANGER;		// tile distance to avoid vehicle
extern int VEHICLE_STANDOFF;   	 // tile distance to wait at
extern char immobileFoe;

//******************************************//
// Vehicle related routines
//******************************************//

static void SpinVehicleRight(VEHICLE* pVehicle){// rotate tank 

    AiVehicleDoTurn(pVehicle,RIGHT_VEHICLE);
}

static void SpinVehicleLeft(VEHICLE* pVehicle){// rotate tank 

    AiVehicleDoTurn(pVehicle,LEFT_VEHICLE);
}

static void StopVehicle(VEHICLE* pVehicle){

    AiVehicleDoAccelerate(pVehicle,STOP_VEHICLE);
}

static void Speedup(VEHICLE* pVehicle){

    AiVehicleDoAccelerate(pVehicle,SPEEDUP_VEHICLE);
}

static void Slowdown(VEHICLE* pVehicle){

    // braking is faster than reverse
    if ((signed int) pVehicle->full_velocity >
        (signed int) pVehicle->brake_coefficient)
        AiVehicleDoAccelerate(pVehicle,STOP_VEHICLE);
    else AiVehicleDoAccelerate(pVehicle,SLOWDOWN_VEHICLE);
}

int	GetTileDistance(SPOINT x,SPOINT y)
{
    return TileDistance(ENCODE_IPOINT(x.x,x.y),ENCODE_IPOINT(y.x,y.y));
}

SPOINT CenterPoint(SPOINT pt)
{
    pt.x = ((pt.x >> 4) << 4) + 8;
    pt.y = ((pt.y >> 4) << 4) + 8;
    return pt;
}

SPOINT CenterPointFromTile(IPOINT tile)
{
    SPOINT pt;
    pt.x = (short)((IPOINT_X(tile) << 4) + 8);
    pt.y = (short)((IPOINT_Y(tile) << 4) + 8);
    return pt;
}


///========================================================================
//	Function:		VehicleSafeDeploy
//	Description:	Find an unblocked place to put vehicle
///========================================================================
long VehicleSafeDeploy(IPOINT index)
{
    if (UntrafficableUnit(index))	return 0; 
    if (!(pNoVehicleRoute[index] & OK_BIT)) return 0;

    // this is as good as any place
    return index;
}


///========================================================================
//	Function:		VehicleEngaged
//	Description:	is Vehicle engaged with target
///========================================================================

static BOOL VehicleEngaged(VEHICLE* pVehicle) // is it engaged with a target
{
      int foeRange,frndRange;
      long d;
      TAD* pTad = TadCurrentTarget((ITEM*) pVehicle); 
      ITEM* pFoeItem = NULL;
      if (pTad) pFoeItem = pTad->pItem;
      BOOL engaged = FALSE;

      // if have no target, are not engaged
      if (!pFoeItem) return FALSE;

      // if not at goal yet...
      if (pVehicle->aiGoal.x)
      {
          // pay no attention to targets if ignoring fire
          if (pVehicle->imode == IGNOREFIRE) return FALSE;
              
          // if RETURNFIRE mode, engage only if being shot at
        //  if (pVehicle->imode == RETURNFIRE &&
         //     (pVehicle->nHitWhen+STILLMAD) < playCycle)  return FALSE;
      }
      // at goal
      else
      {
          // pay no attention to targets
          if (pVehicle->atmode == IGNOREFIRE) return FALSE;

          // if RETURNFIRE mode, engage only if being shot at
         // if (pVehicle->atmode == RETURNFIRE &&
          //    (pVehicle->nHitWhen+STILLMAD) < playCycle)  return FALSE;
      }

      // how far from target
      d =	GetDistance(&(pVehicle->common.position),&(pFoeItem->position));

      // if in his firing range of us, we must fight or get slaughtered
      foeRange = AiObjectFiringRange(pFoeItem);
      frndRange = AiObjectFiringRange((ITEM*)pVehicle);

      // if we are in range of it, we must attack since he can hit us...
      if (d <= foeRange)
      {
          return engaged = TRUE;
      }

      // if we are in our range of him, we can attack and should
      else if (d <= frndRange)
      {
          return engaged = TRUE;
      }
      // otherwise we are not engaged
      else engaged =  FALSE;

      return engaged;
}



static int StuckFix(VEHICLE* pVehicle)
{
   VEHICLE_CONTROLLER* control = (VEHICLE_CONTROLLER*) pVehicle->controller;

   // if we are stuck, begin process to free us
   if (control->stuckCount > 2 && !control->stuckSolution){ // get unstuck
        // drop our current routing data
        control->routeData.waypoint = OFF_THE_MAP;
		control->routeData.nWaypoints = 0;
        control->stuckAt = pVehicle->common.position; // couldnt go here

        // now carry out solution system
        control->stuckSolution = 1;

        StopVehicle(pVehicle); // come to a stop if not already
    }

    if (control->stuckSolution){ // continue applying a solution?
         
        // 1st make sure we are at a full stop
        if (control->stuckSolution == 1){
            if (pVehicle->full_velocity > 0){ 
                StopVehicle(pVehicle);
                return 1;
            }
            control->stuckSolution = 2;            
        }

        // now go into reverse
        if (control->stuckSolution == 2){
            Slowdown(pVehicle); // reverse more
            if (pVehicle->full_velocity < 0) control->stuckSolution = 3;
            return 1;
        }

        // now stay into reverse until clear of problem
        if (control->stuckSolution == 3){
            int d =  GetTileDistance(control->stuckAt,pVehicle->common.position);
            // continue backing until stopped or past 2 tiles
            if (pVehicle->full_velocity < 0 && d < 2)
            {
                Slowdown(pVehicle); // reverse more
                return 1;
            }
            control->stuckSolution = 4;
        }

        // now come to a complete stop of backing up
        if (control->stuckSolution == 4){
            StopVehicle(pVehicle);
            if (pVehicle->full_velocity) 
				return 1;
            control->stuckSolution = 5;
        }
                            
        // now replan and proceed per normal
        if (control->stuckSolution == 5){
            control->stuckSolution = 0;
            control->stuckCount = 0;
            return 1;
        }
    }
    return 0;
}



static IPOINT xbackupTile;
static IPOINT xvictimTile;
static IPOINT xattackerTile;
static long xvictimDist;
static long xscore;

static long VehicleEvadeFind(IPOINT at) // starting 5 tiles away working in
{
      // we want max dist from foe with min dist from us
      int vd,ad; int vscore;
      if (!VehicleSafeDeploy(at)) return 0; // cant go here

      vd = TileDistance(at,xvictimTile);
      if (vd <= xvictimDist) return 0;		// not farther from victim

      ad = TileDistance(at,xattackerTile);	// dist from where we are
      vscore = (vd * 100) + (100 - ad);     // go close to us, far from him
      if (vscore <= xscore) return 0;		// not better

      // this is better (farther from victim, as close to us as possible)
      xscore = vscore;
      xvictimDist = vd;
      xbackupTile = at;
      return 0;
}

static SPOINT VehicleEvadeTarget(VEHICLE* pVehicle, ITEM* pVictim)
{
	// set up data for spread call
	xbackupTile = pVehicle->common.tile; // we are here by default
    xattackerTile = xbackupTile;
    xvictimTile = pVictim->tile;  // he is there
    xvictimDist = TileDistance(xattackerTile,xvictimTile);
    xscore = 0;
    ItemFanOut((ITEM*)pVehicle,xattackerTile,8,VehicleEvadeFind);
    return  CenterPointFromTile(xbackupTile);
}

static void DoVehicleEvent(VEHICLE* pVehicle)
{
	int event;
	event = pVehicle->arrivalEvent;
    pVehicle->arrivalEvent = EVENT_NUM_UNDEFINED;
    // if vehicle is untrafficable, it cant succeed in doing anything
    if (the_map.movement_layer[pVehicle->common.tile] >= 15); // dont want to trigger stuck vehicles
    else if (event == -3)
    {
        --pVehicle->npc;
    }
    else if (event != EVENT_NUM_UNDEFINED)
    {
		EventTrigger((EVENT_TYPE)pVehicle->eventtype,event,ITEM_UID(pVehicle),0,0);
    }
}

static void Travel(VEHICLE* pVehicle)
{
   SPOINT current = pVehicle->common.position; /* where is it */
   VEHICLE_CONTROLLER* control = (VEHICLE_CONTROLLER*) pVehicle->controller;
   int speed = AiVehicleRawSpeed(pVehicle);
   int max = AiVehicleMaxSpeed(pVehicle);
   int hadarrived = control->routeData.arrived;
   int evading = FALSE;

   // if delayed failing detected, finish it now
	if (pVehicle->delayFailed && pVehicle->delayFailed < gpGame->dwSysTime)
	{
		pVehicle->delayFailed = 0;
		DoVehicleEvent(pVehicle);
		return;
	}


   IPOINT goaltile;
   SPOINT goal,basegoal,waypoint;
   LONG ans,dd,d;
   TAD* pTad = (TAD*)(pVehicle->common.pTad);
   // insure it is smart
   goal = basegoal = pVehicle->aiGoal;
   ITEM* pFoeItem = NULL;

   // override goal processing while engaged
   if (VehicleEngaged(pVehicle))
   {
      TAD* pTad = TadCurrentTarget((ITEM*) pVehicle); 
      pFoeItem = pTad->pItem;

      // drive to chase target
      if (pVehicle->imode == ATTACKFIRE)
      {
          goal = pFoeItem->position;
          goal = CenterPoint(goal);
		  // are we too close to vehicle
		  if (ITEM_TYPE(pFoeItem) == ARMY_VEHICLE)
		  {
			SPOINT tip;
			SPOINT vpoint;
			vpoint = ItemCenterPos((ITEM*)pFoeItem);
			VehicleFiringPosition(pVehicle,&tip);
			int v2tipd,v2vehicled,t2vd;
			v2tipd = GetDistance(&tip,&vpoint);
			v2vehicled = GetDistance(&vpoint,&pVehicle->common.position);
			t2vd = GetDistance(&tip,&pVehicle->common.position);
			// he is closer than barrel tip
			if (v2vehicled < t2vd )
			{
				goal = VehicleEvadeTarget(pVehicle,pFoeItem);
				evading = TRUE;
			}
		  }
	  }
   }

   if (!goal.x) // no need to travel
   {
       if (pVehicle->npc && speed) StopVehicle(pVehicle); // come to a stop
       return;
   }

   // dont go all the way into an enemy vehicle. Troops are ok to run over
   if (pFoeItem && ITEM_TYPE(pFoeItem) == ARMY_VEHICLE &&
       TileDistance(pFoeItem->tile,pVehicle->common.tile) < 8 && !evading)
   {
       if (pVehicle->npc && speed) StopVehicle(pVehicle); // come to a stop
       return;
   }


   // find a better place if illegal to end up here
   goaltile = ENCODE_IPOINT(goal.x,goal.y);
   if (!VehicleSafeDeploy(goaltile))
   {
       SPOINT newgoal; IPOINT ntile;
       myvehicle = pVehicle;
       ntile = ItemFanOut((ITEM*)pVehicle,goaltile,10,VehicleSafeDeploy);
       newgoal = CenterPointFromTile(ntile);
       if (SameSPoint(goal,basegoal))
       {
           pVehicle->aiGoal = newgoal;
       }
       goaltile = ntile;
       goal = newgoal;
       if (!ntile) TRACE("Failed to find route patch for ai vehicle\n");
   }

   
   // goal and goaltile are now set up correctly trafficable. current is self
  
   // if not arrived and 
   // if already on the way to a close equivalent, keep old destination
   // if we are still far from it
   if (control->routeData.arrived == 0 && !evading &&
       GetDistance(&control->routeData.destination,&goal) <= CLOSE_ENOUGH)
   {
       goal = control->routeData.destination;
   }
   
   // do up to date routeplanning for either main or interrupt goal
   int did;
   did = ClearVehicleFromVehicleLayer(pVehicle); // routeplan without this vehicle in the way
   waypoint = AIRouter(goal, &(control->routeData),	
                       control->routeData.flags,
                       current,pVehicle->common.facing);
   ReinsertVehicleInVehicleLayer(pVehicle,did);  // if it got removed, put it back                

   // we got there or cant get there
   if (GetDistance(&goal,&current) < 48)
       RouterArrive(&control->routeData); // close enough, say we got it
     
   if (control->routeData.arrived || waypoint.x == 0){
       if (speed) StopVehicle(pVehicle);

       // if we are not doing an interrupt fight goal, then end our main goal
       if (ENCODE_IPOINT(pVehicle->aiGoal.x,pVehicle->aiGoal.y) ==
		   ENCODE_IPOINT(goal.x,goal.y))
           pVehicle->aiGoal = OFF_THE_MAP;

	   if (hadarrived) return; // we already been arrived,man.

	   // if we failed, set a delay to trigger event later. Stops tight scripting loops
	   // telling us to go do it again (when scripter fails to put delay in himself)
	   if (!control->routeData.arrived)
	   {
		   if (pVehicle->delayFailed) return; // already failed.

		    pVehicle->delayFailed = gpGame->dwSysTime + 3000; // 3 seconds later
			if (scriptDebug)
			{
				TRACE("%s failing goal.\n",ItemDBName(pVehicle));
			}
		   return;
	   }
        
        if (scriptDebug)
        {
              TRACE("%s arrived at goal %d.%d .\n",ItemDBName(pVehicle),
                    goal.x,goal.y);
       }
		DoVehicleEvent(pVehicle);
       return;
    }

    // if have a waypoint and get stuck
    if (SameSPoint(control->oldLocation,current) && control->routeData.waypoint.x &&
        !speed){
        ++control->stuckCount;
    }
    else{
        control->oldLocation = current;
        control->stuckCount = 0;
    }

   if (control->routeData.stuckWhen == -1){ // routing failed
        if (control->routeData.waypoint.x) control->routeData.stuckWhen = 0;
        // freed
        else{
            Slowdown(pVehicle); // go in reverse    
            return;
        }
    }

    // how do we face on waypoint
    ans = AiVehicleMoveStatus(pVehicle,control->routeData.waypoint);
    // how far are we from goal
    d = GetTileDistance(current,control->routeData.destination);
    dd = GetTileDistance(current,control->routeData.waypoint);
    // waypoint has changed since last here
    if (!SameSPoint(control->oldway, control->routeData.waypoint)){
        control->oldway = control->routeData.waypoint;
        control->stuckSolution = 0; // solved any problem getting here
    }
     if (control->routeData.arrived){
        StopVehicle(pVehicle);        
        control->state &= -1 ^ FULL_THROTTLE;
        control->state |= STOP_THROTTLE;
        control->state &= -1 ^ DRIVE_TO;

        if (scriptDebug || vehicleBehavior)
            TRACE("%d.%3d- arrived\n",nSec,nMilliSec);

        return;
    }

    if (control->stuckCount>2 || control->stuckSolution)
    {
        if (StuckFix(pVehicle))
            return;
    }

    BOOL turning = FALSE;
    // change facing of vehicle if needed
    if (ans & AI_VEHICLE_GO_RIGHT_MASK){
        if (ans & AI_VEHICLE_FINE_CONTROL_MASK)
            AiVehicleDoTurn(pVehicle,FINE_RIGHT_VEHICLE);
        else AiVehicleDoTurn(pVehicle,RIGHT_VEHICLE);
        turning = TRUE;
    }
    else if (ans & AI_VEHICLE_GO_LEFT_MASK){
        if (ans & AI_VEHICLE_FINE_CONTROL_MASK)
            AiVehicleDoTurn(pVehicle,FINE_LEFT_VEHICLE);
        else AiVehicleDoTurn(pVehicle,LEFT_VEHICLE);
        turning = TRUE;
    }

	// reasons to speed up
	if (d > 0 && speed < 25) // speed up to get there
	{
	    control->state |= FULL_THROTTLE;
	}
 	else if (d > 11 && speed < 100){
	    control->state |= FULL_THROTTLE;
	}

	// reasons to slow down
	else if (d < 4 && speed > 70){
        control->state &= -1 ^ FULL_THROTTLE;
	}
    
    // change throttle if needed
    if (control->state & FULL_THROTTLE){/* get to full */

        // if too fast for this mode, slow down
        if (pVehicle->speed == NORMAL_SPEED && speed > ((max/2) + 20))
        {
            Slowdown(pVehicle);	            
        }

        // if need to turn, dont speed up yet until heading right
        else if (turning && speed > 0);

        // go slow enough for troopers to keep up while running
        else if (pVehicle->speed == NORMAL_SPEED)
		{ 
            // if less than 10 under half speed, speedup
			if (speed < ((max/2)-10) )
				Speedup(pVehicle);
		}
        // go fast 
		else if (pVehicle->speed == FAST_SPEED)
		{
			if (speed < max)
				Speedup(pVehicle);
		}
    }
    //dont want full throttle
    else
    {
        // getting close to goal
        if (d < 4 && speed > 70)
            Slowdown(pVehicle);

        // if too fast for this mode, slow down
        else if (pVehicle->speed == NORMAL_SPEED && speed > ((max/2) + 20))
        {
            Slowdown(pVehicle);	            
        }
    }
}

void InitControl(VEHICLE* pVehicle){

    // assign a controller to this vehicle for the future
    VEHICLE_CONTROLLER* control;
    int type;                               

    control = (VEHICLE_CONTROLLER*) malloc(sizeof (VEHICLE_CONTROLLER));
    pVehicle->controller = control;
    control->pVehicle = pVehicle;
    
    control->state = 0;
    control->stuckSolution = 0;
	if (ITEM_CLASS(pVehicle) == ARMY_TANK) type = TANK_ROUTE;
    else if (ITEM_CLASS(pVehicle) == ARMY_HALFTRACK) type = HALFTRACK_ROUTE;
    // bug not a unit route
    else if (ITEM_CLASS(pVehicle) == ARMY_CONVOY) type = UNIT_ROUTE;
    else type = JEEP_ROUTE;

    type |= COLLAPSE; // use only turning waypoints

    control->routeData.owner = ITEM_UID(pVehicle);
    
    AIRouter(OFF_THE_MAP,&(control->routeData),type,OFF_THE_MAP,0);
}

void Control(VEHICLE* pVehicle){

	if (immobileFoe && ITEM_ARMY(pVehicle) != ARMY_PLAYER) return;

    if (!pVehicle->npc && pVehicle->aiGoal.x)
    {
        pVehicle->imode = pVehicle->atmode = DEFENDFIRE;
        pVehicle->npc = 1;
    }
	TAD* pTad;
	pTad = (TAD*)pVehicle->common.pTad;
	if (pVehicle->npc && !(pTad->bFlags & TAD_SMART)) 
		TadFlags(pTad,TAD_SMART,TAD_SET_IT);

    /* fire also is possible, even while moving */
    FireVehicle(pVehicle);

    /* go move if need be */
    Travel(pVehicle);
}


static void FireVehicle(VEHICLE* pVehicle){// fire this vehicle

    VEHICLE_CONTROLLER* control = (VEHICLE_CONTROLLER*) pVehicle->controller;
    TAD* pTad = NULL;
    ITEM* pVictim;
    LONG turret;

    // see if we have something to fire upon and are allowed to do so

    // no fire on way if ignore
    if (pVehicle->aiGoal.x && (BEHAVIOR)pVehicle->imode == IGNOREFIRE);

    // no fire while there if ignore
    else if (!pVehicle->aiGoal.x && (BEHAVIOR)pVehicle->atmode == IGNOREFIRE);

    // otherwise see if have a target
    else pTad = TadCurrentTarget((ITEM*) pVehicle); 

	if (!pTad) return;

    pVictim = pTad->pItem;

    // convert unit to trooper
    if (ITEM_TYPE(pVictim) == ARMY_UNIT)
    {
      pVictim = (ITEM*)UnitFindClosestTrooper((UNIT*)pVictim,
                            &pVehicle->common.position);
    }

    if (!pVictim) return;

    // if target too close, cant fire
    SPOINT tip;
    SPOINT vpoint;
    vpoint = ItemCenterPos((ITEM*)pVictim);
    VehicleFiringPosition(pVehicle,&tip);
    int v2tipd,v2vehicled,t2vd;
    v2tipd = GetDistance(&tip,&vpoint);
    v2vehicled = GetDistance(&vpoint,&pVehicle->common.position);
    t2vd = GetDistance(&tip,&pVehicle->common.position);
    // he is closer than barrel tip
    if (v2vehicled < t2vd )
    {
        // swivel to crush human
        if ((ITEM_TYPE(pVictim) == ARMY_TROOPER ||ITEM_TYPE(pVictim) == ARMY_SARGE) &&
		    ITEM_TYPE(pVehicle) == ARMY_TANK && v2vehicled < (t2vd - 5))
        {
            AiVehicleDoTurn(pVehicle,RIGHT_VEHICLE);
        }
        return;
    }

    // get turret alignment to target location
    turret = AiVehicleFireStatus(pVehicle,vpoint);

    // if we overshot it, dont move. Take the shot and try again
    if (turret == VERYFINE_LEFT_VEHICLE &&
        pVehicle->lastGunAdjust == VERYFINE_RIGHT_VEHICLE)
        turret = 0;
    else if (turret == VERYFINE_RIGHT_VEHICLE &&
        pVehicle->lastGunAdjust == VERYFINE_LEFT_VEHICLE)
        turret = 0;
    else pVehicle->lastGunAdjust = turret;// note what we last did

    // change facing of turret if needed
	if (turret)
		AiVehicleDoTurnGun(pVehicle,turret);

    // cannot fire
    else if (pVehicle->common.pWeapon->nAmmo == 0 ||
             !WeaponFireTime(pVehicle->common.pWeapon));


    // locked on- ready to fire
    else { 
        pVehicle->lastGunAdjust = 0;// it was good

        // if in range, and no friendlies in way, fire
        if (CanShoot(pVehicle->common.pWeapon,(ITEM*) pVehicle,
            ENCODE_IPOINT(vpoint.x,vpoint.y)) > 0)
        {
            if (scriptDebug)
            {
                char name[50];
                if (unitBehavior)
                {
                    sprintf(name,"%s",ItemDBName(pVehicle));
                    TRACE("%s ai fires at %s ",name,ItemDBName(pVictim));
                }
            }
            VehicleFireWeapon(pVehicle);
        }
    }
}

static BOOL SargeEngaged(SARGE* pSarge) // is it engaged with a target
{
      int foeRange,frndRange;
      long d;
      TAD* pTad = TadCurrentTarget((ITEM*) pSarge); 
      ITEM* pFoeItem = NULL;
      if (pTad) pFoeItem = pTad->pItem;
      BOOL engaged = FALSE;

      // if have no target, are not engaged
      if (!pFoeItem) return FALSE;

      // if not at goal yet...
      if (pSarge->aiGoal.x)
      {
          // pay no attention to targets if ignoring fire
          if (pSarge->imode == IGNOREFIRE) return FALSE;
      }
      // at goal
      else
      {
          // pay no attention to targets
          if (pSarge->atmode == IGNOREFIRE) return FALSE;
      }

      // how far from target
      d =	GetDistance(&(pSarge->common.position),&(pFoeItem->position));

      // if in his firing range of us, we must fight or get slaughtered
      foeRange = AiObjectFiringRange(pFoeItem);
      frndRange = AiObjectFiringRange((ITEM*)pSarge);

      // if we are in range of it, we must attack since he can hit us...
      if (d <= foeRange)
      {
          return engaged = TRUE;
      }

      // if we are in our range of him, we can attack and should
      else if (d <= frndRange)
      {
          return engaged = TRUE;
      }
      // otherwise we are not engaged
      else engaged =  FALSE;

      return engaged;
}

static void LocateWeapon(SARGE* pSarge)
{
	int i;
	OBJECT* pObj;
	WEAPON_TYPE eWeaponType;
	for (i = 0; i < the_map.num_objects; ++i)
	{
        pObj = &(the_map.objects[i]);
		if (pObj->triggers & TRIGGER_UNDEPLOYED) continue;
		if(pObj->category != SPECIAL_ITEMS ) continue;
		if( !pObj->common.pWeapon ) continue;
		eWeaponType = pObj->common.pWeapon->eWeapon;
		switch( eWeaponType )
		{
			case ARMY_MORTAR:
			case ARMY_GRENADE:
			case ARMY_BAZOOKA:
			case ARMY_FLAME_THROWER:
				break;
			default: continue;
		}
		if (TileDistance(pSarge->common.tile,pObj->common.tile) > 30) continue;

		ROUTEDATA junkroute;
		SPOINT waypoint;
		junkroute.destination = OFF_THE_MAP;
		junkroute.owner = ITEM_UID(pSarge);
		waypoint = ItemCenterPos((ITEM*)pObj);
		waypoint = AIRouter(waypoint, &(junkroute),	
                       pSarge->routeData.flags,
                       pSarge->common.position,
					   pSarge->common.facing);
		if (!waypoint.x) continue;

		pSarge->seeksWeapon = i;
		return;
	}
}

static ACTION SargePace(SARGE* pSarge,SPOINT goal)
{
    ACTION pace;					// speed to move at
    int xdif = goal.x - pSarge->common.position.x;
    if (xdif < 0) xdif = -xdif;
    int ydif = goal.y - pSarge->common.position.y;
    if (ydif < 0) ydif = -ydif;

    if (goal.x == 0)
       return AVATAR_STAND; // not trying to go anywhere
 
    if (ENCODE_IPOINT(goal.x,goal.y) == pSarge->common.tile)
    {
      pace = AVATAR_STOP_IMMEDIATELY;
      if (pSarge->action == AVATAR_STOP_IMMEDIATELY )
		pace = AVATAR_STAND;
    } 

    // if he is real close but not yet there, shuffle into place
    else if (xdif < 8 && ydif < 8)
    {
        pace = AVATAR_SHUFFLE;
    }

    // go close
    else if (xdif < 50 && ydif < 50)  
	{
		pace = AVATAR_WALK;
	}
    else // go far fast
    {
        pace = AVATAR_RUN;
    }

    return pace;
}

static void TravelSarge(SARGE* pSarge)
{
   ITEM* pFoeItem = NULL;
   SPOINT goal,basegoal,waypoint;
   TAD* pTad = (TAD*)(pSarge->common.pTad);
   ACTION pace;

   if (!(pTad->bFlags & TAD_SMART)) TadFlags(pTad,TAD_SMART,TAD_SET_IT);
   int hadarrived = pSarge->routeData.arrived;
   int seekingWeapon = 0;

   goal = basegoal = pSarge->aiGoal;

	// check our special weapon status
   	OBJECT* weaponObject = NULL;
	if (pSarge->seeksWeapon) 
		weaponObject = &the_map.objects[pSarge->seeksWeapon];

	// it aint there any more, flush it
	if (weaponObject && (weaponObject->triggers & TRIGGER_UNDEPLOYED || weaponObject->common.tile == 0))
	{
		weaponObject = NULL;
		pSarge->seeksWeapon = 0;
	}
	// we dont need one. we got one
	else if (pSarge->pWeaponList[SARGE_WEAPON_SECONDARY] != NULL) 
	{
		if (weaponObject) // DONT NEED ONE
		{
			pSarge->seeksWeapon = 0;
			weaponObject = NULL;
		}
	}
 	// its there to goto. fine
	else if (weaponObject);
	// time to reseek for good weapon on the map
    else if (pSarge->seeksWeapon == 0 && pSarge->seekTime < gpGame->dwSysTime  && playCycle > 200)
	{
	   pSarge->seekTime = gpGame->dwSysTime + 5000; // check again in 5 seconds
	   LocateWeapon(pSarge);
	   if (pSarge->seeksWeapon) 
			weaponObject = &the_map.objects[pSarge->seeksWeapon];
	}


   // override goal processing while engaged
   if (SargeEngaged(pSarge))
   {
      TAD* pTad = TadCurrentTarget((ITEM*) pSarge); 
      pFoeItem = pTad->pItem;

      // run to chase target
      if (pSarge->imode == ATTACKFIRE)
      {
          goal = pFoeItem->position;
          goal = CenterPoint(goal);
		  if (pFoeItem->position.x & 1)
		  {
			  goal.y += (pFoeItem->position.y & 1) ? 48 : -48;
			  goal.x += (pFoeItem->position.x % 96) - 48;
		  }
		  else 
		  {
			  goal.x += (pFoeItem->position.x & 1) ? 48 : -48;
			  goal.y += (pFoeItem->position.y % 96) - 48;
		  }
			// dont get too close to fire
		  if ((GetDistance(&pSarge->common.position,&goal)+ 15) < WeaponMinRange(pSarge->common.pWeapon->eWeapon))
		  {
			  pSarge->pendingAction = AVATAR_STOP_IMMEDIATELY;
			  return;
		  }
      }
   }
   else if (weaponObject) // override to go get it
   {

	   goal = ItemCenterPos((ITEM*)weaponObject);
	   seekingWeapon = TRUE;
   }



   if (!goal.x) // no need to travel
   {
       pSarge->pendingAction = AVATAR_STAND;
       return;
   }

   waypoint = AIRouter(goal, &(pSarge->routeData),	
                       UNIT_ROUTE|COLLAPSE,
                       pSarge->common.position,pSarge->common.facing);
   pace = SargePace(pSarge,waypoint);

   if (pSarge->routeData.arrived || waypoint.x == 0)
   {
	   if (pSarge->routeData.arrived)
		   TRACE("%s arrived\n",ItemDBName(pSarge));
	   else 
  		   TRACE("%s fails to route\n",ItemDBName(pSarge));
      int event = pSarge->arrivalEvent;
       pSarge->pendingAction = AVATAR_STAND;

	   if (seekingWeapon) pSarge->seeksWeapon = 0; // we got it or couldnt get it
     
	   // if we are not doing an interrupt fight goal, then end our main goal
       if (ENCODE_IPOINT(pSarge->aiGoal.x,pSarge->aiGoal.y) ==
		   ENCODE_IPOINT(goal.x,goal.y))
	   {
           pSarge->aiGoal = OFF_THE_MAP;
	   }
	   else return; // arrived, but not at real destination

	   if (hadarrived) return; // we already been arrived,man.

       pSarge->arrivalEvent = EVENT_NUM_UNDEFINED;
       if (event != EVENT_NUM_UNDEFINED)
           EventTrigger((EVENT_TYPE)pSarge->eventtype,event,
                           ITEM_UID(pSarge),0,0);
       return;
   }

   // set how we want to go.
   pSarge->pendingAction = pace;
   int direction;
   direction = GetDirection(&pSarge->common.position,&waypoint);
   if (direction == -1) direction = pSarge->common.facing;
   pSarge->pendingDirection = direction;

    SPOINT lands;
    AVATAR* pAvatar;
    pAvatar = pSarge->pAvatar;
	ASSERT(pAvatar);

    // Now we have pace and direction, we must see if the avatar will be ok.
    // Ask the avatar where he would end up at end of anim. If illegal, try to fix it.
    lands = AvatarWouldMoveTo(pace,AVATAR_STAND,direction,TRUE,pAvatar);
    // if full walk is ok, see if partial walk is also (in case of diagonal corner)
    if (!UntrafficableUnit(ENCODE_IPOINT(lands.x,lands.y)))
    {
        lands = AvatarWouldMoveTo(pace,AVATAR_STAND,direction,FALSE,pAvatar);
 	}

    // fine. we can go wherever.
    if (!UntrafficableUnit(ENCODE_IPOINT(lands.x,lands.y))) return;

    // bad.. we must fix our movement
    SPOINT to;
    
    // route planner will give us an adjacent tile if called again.
    // by computing the full list to goal
    to = AIRouter(goal, &(pSarge->routeData),
                           pSarge->routeData.flags,
                           pSarge->common.position,
                           pSarge->common.facing);
	// router failed unexpectedly
	if (to.x == 0)
	{
		pSarge->aiGoal = OFF_THE_MAP;
		TRACE("Unexpected %s failure in route fix\n",ItemDBName(pSarge));
		pSarge->pendingAction = AVATAR_STAND;
	    if (seekingWeapon) pSarge->seeksWeapon = 0; // we got it or couldnt get it
   		return;
	}
  
    // find the corner pixel of our tile closest to the destination tile
    // and change our direction to aim to that point if not already there
    SPOINT spot = ClosestCorner(pSarge->common.position,to);

    // router couldnt get us there or didnt need to
    if (!spot.x) direction = pSarge->common.facing;

    // we are not at corner yet, so aim there
    else if (pSarge->common.position.x != spot.x ||
             pSarge->common.position.y != spot.y) 
    {
        pSarge->pendingDirection = GetDirection(&pSarge->common.position,&spot);     
		pSarge->pendingAction = AVATAR_SHUFFLE;
     }
    else				  // else aim into center of tile trying to get to
    {
       direction = GetDirection(&pSarge->common.position,&waypoint);        
       if (direction == -1) // already on spot?
       {
          pSarge->pendingAction = AVATAR_STOP_IMMEDIATELY;
       }
       else
       {
           pSarge->pendingDirection = direction;
           pSarge->pendingAction = AVATAR_SHUFFLE;
       }
    }

    // Ask the avatar where he would end up going to the adjacent tile
    // partially.
	lands = AvatarWouldMoveTo(pSarge->pendingAction,AVATAR_STAND,
        pSarge->pendingDirection,FALSE,pSarge->pAvatar);


   // Not OK to go to corner or tile somehow
   if (UntrafficableUnit(ENCODE_IPOINT(lands.x,lands.y))) 
   {
       pSarge->pendingAction = AVATAR_STOP_IMMEDIATELY,
       pSarge->pendingDirection = pSarge->common.facing;
       lands = pSarge->common.position;
    }
}


static void FireSarge(SARGE* pSarge)
{// fire this sarge


    TAD* pTad = NULL;
    ITEM* pVictim;

    // see if we have something to fire upon and are allowed to do so

    // no fire on way if ignore
    if (pSarge->aiGoal.x && (BEHAVIOR)pSarge->imode == IGNOREFIRE);

    // no fire while there if ignore
    else if (!pSarge->aiGoal.x && (BEHAVIOR)pSarge->atmode == IGNOREFIRE);

    // otherwise see if have a target
    else pTad = TadCurrentTarget((ITEM*) pSarge); 

	if (!pTad) return;

    pVictim = pTad->pItem;

    // convert unit to trooper
    if (ITEM_TYPE(pVictim) == ARMY_UNIT)
    {
      pVictim = (ITEM*)UnitFindClosestTrooper((UNIT*)pVictim,
                            &pSarge->common.position);
    }

    if (!pVictim) return;
	
	int facing;
	facing =  GetDirection(&pSarge->common.position,
                                    &pVictim->position);  
	if (facing == -1) facing = pSarge->common.facing;

    // cannot fire
    if (pSarge->common.pWeapon->nAmmo == 0 ||
             !WeaponFireTime(pSarge->common.pWeapon));


    // locked on- ready to fire
    else { 
        
        // if in range, and no friendlies in way, fire
        if (CanShoot(pSarge->common.pWeapon,(ITEM*) pSarge,pVictim->tile) > 0)
        {
			pSarge->pendingDirection = facing;

            if (scriptDebug)
            {
                char name[50];
                if (unitBehavior)
                {
                    sprintf(name,"%s",ItemDBName(pSarge));
                    TRACE("%s ai fires at %s ",name,ItemDBName(pVictim));
                }
            }
            // when close dont get closer
            if (TileDistance(pSarge->common.tile,pVictim->tile) < 5)
                pSarge->pendingAction = AVATAR_FIRE_STATIONARY;                
            else pSarge->pendingAction = AVATAR_FIRE;
        }
    }
}


void SargeControl(SARGE* pSarge){

	if (immobileFoe && ITEM_ARMY(pSarge) != ARMY_PLAYER) return;

    /* go move if need be */
    TravelSarge(pSarge);
   
    /* fire also is possible, even while moving */
    FireSarge(pSarge);

    SargeComplete(pSarge); // adjust any overrides
}

void SargeEvadeTheVehicle(SARGE* pSarge,VEHICLE* pVehicle,int stop)
{
	ACTION wasaction = pSarge->pendingAction;

	// just stop
	if (stop)
	{
        pSarge->pendingAction = AVATAR_STOP_IMMEDIATELY;
		return;
	}

	// actually run away

	int facing;
	// randomly pick running direction away with going to the side
	// run perpendicular since he is our friend ( ALSO ALLOW FOE)
	facing = pVehicle->common.facing;
	if (pVehicle->full_velocity < 0) facing += 128;
	if (facing >= CIRCLE_UNITS) facing -= CIRCLE_UNITS;
	SPOINT to;
	to = pVehicle->common.position;
	to.x += (short)(cos_table[facing] * 48);
	to.y += (short)(sin_table[facing] * 48);      
	IPOINT totile;
	totile = ENCODE_IPOINT(to.x,to.y);
	// left of, go left
	if (cross(pSarge->common.tile,pVehicle->common.tile,totile) < 0)
		facing += 64;
	 else facing -= 64;
	if (facing < 0) facing += CIRCLE_UNITS;
	if (facing >= CIRCLE_UNITS) facing -= CIRCLE_UNITS;
            
	pSarge->pendingAction = AVATAR_RUN;
    pSarge->pendingDirection = facing;
}

static void SargeEvadeVehicle(SARGE* pSarge)
{
      int eArmy,vehicle,facing,d;
      int theight;
      int vheight;
      theight = ELEVATION(the_map.elevation_layer[pSarge->common.tile]);
      LEGION* pLegion;
      VEHICLE* pVehicle;
      FOR_EACH_DEPLOYED_ARMY(eArmy)
      { 
          pLegion = ArmyGetLegion(eArmy);
          FOR_EACH_VEHICLE(pLegion,vehicle)
          {
              pVehicle = pLegion->pLegionVehicles[vehicle];
              if (pVehicle->state != VEHICLE_DEPLOYED) continue;
			  d = TileDistance(pVehicle->common.tile,pSarge->common.tile);
              if (d > VEHICLE_DANGER) continue;

              // if vehicle is at a different height, he cant drive to us
              // diff of 2 or more is safe. diff of 1 is a ramp, danger
              vheight = ELEVATION(the_map.elevation_layer[pVehicle->common.tile]);
              vheight -= theight;
              if (vheight >= 2 || vheight <= -2) continue;

              // we are may be in danger of being run over. 
              facing = GetDirection(&pVehicle->common.position,
                                    &pSarge->common.position);
              // if the vehicle is ours, special rules apply */
              if (ITEM_ARMY(pVehicle) == ITEM_ARMY(pSarge)){
				  // own non-npc and sarge not in this vehicle cannot harm us
				  if (pVehicle->npc == 0 && pSarge->pVehicle != pVehicle)
                      continue;
				  // assume a stationary npc vehicle will remain stationary
				  if (pVehicle->npc && pVehicle->full_velocity == 0)
                      continue;	  
				  VEHICLE* targetVehicle = NULL;
                 int towardVehicle;
				 towardVehicle = CIRCLE_UNITS - facing;
				 int offVehicle = towardVehicle - pSarge->pendingDirection;
				 if (offVehicle < 0) offVehicle = - offVehicle;

				  int vface = pVehicle->common.facing;
				  if (pVehicle->full_velocity < 0) // backing up, invert face
				  {
					  vface += 128;
					  if (vface >= CIRCLE_UNITS) vface -= CIRCLE_UNITS;
				  }
                  // if vehicle doesnt face us we may approach if on follow
                  int face = facing - vface;
                  if (face < 0) face = -face;

                  // we cannot hope to enter these vehicles.
                  // so if hit perim getting closer, stop.
                  if (d == VEHICLE_STANDOFF &&
                     TileDistance(pSarge->common.oldTile,pVehicle->common.tile)
                       > d)
                  {
                      SargeEvadeTheVehicle(pSarge,pVehicle,TRUE);
                      continue;
                  }

                  // if we are within standoff of a vehicle we cannot
                  // enter, move away
                  if (d < VEHICLE_STANDOFF)
                      goto evadenow;


                  // if he faces away or isnt moving and we are not following,
                  // and we cant enter then just stop
                  if (face >= 64 || pVehicle->full_velocity == 0)
                  {
                      SargeEvadeTheVehicle(pSarge,pVehicle,TRUE);
                      continue;
                  }

				  // otherwise if he is moving toward us, we MUST evade.
              }

              else  // for all enemy vehicles
              {
				  // assume a moving vehicle or sarge vehicle must be avoided
				  if (pVehicle->full_velocity != 0);
                  else if (pVehicle->pDriver);
                  else continue;
              }

        // for all enemy vehicles and for our vehicles approaching us
       // EVADE!
              
 evadenow:
         SargeEvadeTheVehicle(pSarge,pVehicle,FALSE);
         eArmy = 20; // abort outer loop as well
         break;
          }
      }
  }

static void	SargeComplete(SARGE* pSarge)
{
      AVATAR* pAvatar = pSarge->pAvatar;
      ACTION intendedAction = pSarge->pendingAction;

      switch(pSarge->pendingAction)
      {
          // are death sequences complete
          case AVATAR_DIE_MELT:
          case AVATAR_DIE_SHOT:
          case AVATAR_DIE_SQUASH:
          case AVATAR_DIE_EXPLODE:
          return;// let normal sarge update happen
      };

      // stay out of harms way of vehicles
      SargeEvadeVehicle(pSarge);
}

