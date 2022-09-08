//*******************************************************
//	AIBTANK.cpp is the AI control of a vehicle.
//  Orders are given via AIY.cpp (or AIX script file)
//  and control time is provided by AIX.cpp.
//*******************************************************

#ifndef __AIROUTER_H__
    #include "airouter.h"
#endif         

typedef struct{ // a players vehicle controller
    ROUTEDATA routeData;	// routing controller
    VEHICLE* pVehicle;		/* the vehicle ptr (always the same per army) */
    int state; 				/* what is vehicle doing over time */
    int count;				/* count if needed by state */
    SPOINT oldway;			// old waypoint being used
 
    SPOINT oldLocation;		// where were we last aiFrame
    int stuckCount;			// how long are we stuck here
    int stuckSolution;		// solution attempted last
    int stuckSolutionCount;	// solution attempted for how long
    SPOINT stuckAt;			// where we got stuck
} VEHICLE_CONTROLLER;

extern int tracespeed;			// show speed changes of vehicle

void Control(VEHICLE* pVehicle); // vehicle control
void InitControl(VEHICLE* pVehicle);
void MoveAllVehicles();// cause vehicles to move on the map
long VehicleSafeDeploy(IPOINT index);

#define FRND_TANK 0x000B0202
#define FOE_TANK  0x00130202
#define SWIVEL 1
#define SPIN 2
#define DRIVE 4
#define FULL_THROTTLE 8
#define STOP_THROTTLE 16
#define DRIVE_TO 32
#define DEAD_BIT 64

SPOINT CenterPoint(SPOINT pt);
SPOINT CenterPointFromTile(IPOINT tile);