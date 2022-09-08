#define MAX_TROOPERS 10   

// unit types
typedef enum
{
	ARMY_NO_UNIT = -1,
    ARMY_RIFLE_UNIT = 0,
	ARMY_GRENADE_UNIT,
	ARMY_FLAME_UNIT,
	ARMY_BAZOOKA_UNIT,
	ARMY_ENGINEER_UNIT,		// now obsolete
	ARMY_MORTAR_UNIT,
	ARMY_MINER_UNIT,
	ARMY_SPECIAL_UNIT,

	// DO NOT PLACE ANYTHING AFTER THIS LINE
	ARMY_LAST_UNIT
} UNIT_TYPE;

#define ARMY_FIRST_UNIT ARMY_RIFLE_UNIT


typedef enum
{
    UNIT_NO_ORDER,
    UNIT_DEFEND,
    UNIT_ATTACK,
    UNIT_FOLLOW
} UNIT_ORDER;			// SEE UNITTEXT.h  UnitOrderText[] for texts of these


// UNIT modes
typedef enum
{
    UNIT_DEAD = 0,			// has been killed off
    UNIT_IN_HQ = 1,			// is not deployed into game
    UNIT_IN_VEHICLE = 2,	// has been picked up by vehicle
    UNIT_STILL = 3,			// on map staying, not fighting (facing something)
    UNIT_MOVING = 4,		// on map going somewhere, not fighting
    UNIT_ENGAGED = 5,		// on map involved in combat with another unit
    UNIT_DYING = 6			// on map but dying (no fight interaction possible)
} UNIT_MODE;
// These modes must be correlated with UNIT_MODE_TEXT in unittext.h

typedef enum				// how to get there for an order
{
    NORMAL_SPEED = 0,
    FAST_SPEED
} SPEED;

// unit ai meta-orders
typedef enum {				// states of aicmdr units
    IGNOREFIRE,				// dont react to foes
    RETURNFIRE,				// shoot only if shot at
    DEFENDFIRE,				// shoot if in range, dont close to fire
    ATTACKFIRE,				// close to shooting range and fire
    NESTFIRE,				// use machinegun nest crouch
    PRONEFIRE,
    KNEELFIRE,				
    STANDFIRE,
    EVADEFIRE,				// stay away from foe
} BEHAVIOR;

// UNIT structure
struct  UNITSTRUCT
{
	struct ITEM		common;			// common components of all objects
	// ADD NEW FIELDS AFTER THIS POINT
 	int				troops;			// current number of troopers
	int				nLeader;		// current index of the leader
    UNIT_MODE		mode;			// inactive (various), moving, or engaged
    UNIT_ORDER		order;			// attack,defend,etc
    BEHAVIOR		prestationBehavior;	// how to react while going somewhere
    BEHAVIOR		poststationBehavior;// how to react after reaching goal
    char			paratrooper;		// if true is para unit

	int				nCompID;		// composition ID (for name)
    char			npc;			// >0 if under script control

    // state data
    SPOINT			deployPosition;	// where to deploy if delayed
    short			deployFacing;	// facing to deploy if delayed

    // order data
    ITEM*			focusItem;		// object of order
    SPOINT			focusLocation;	// center of order
    IPOINT			focusTile;		// center of order (inferred from location)
    int				focusArrived;	// true if arrived on station
    SPEED			focusSpeed;		// how fast to carry this out
    int				arrivalEvent;	// what event to raise on arrival station
    int				eventtype;		// what kind of event

    VEHICLE*		pVehicle;		// if unit is in a vehicle
    UID				mergedWith;		// who am i merged with

    // trooper data
    TROOPER*		pTroops[MAX_TROOPERS];		// troop information
    int				nLastTroop;		// index of last available trooper
    int			 initialTroops;		// how many it started with

    // targeting data
	ITEM*			pTarget;		// current target of this unit
    int				nHitWhen;		// we got hit on this turn

    //movement data
    SPOINT			destination;	// where unit is ultimately heading
    ROUTEDATA		routeData;		// needed to allow unit to go places
    
    ITEM*			lastSitrep;		// who we last targetd to tell use

    char 			beInvisible;
    char			sendYourEvent;	// if event of arrival should be triggered

	SPOINT			deadPosition; // where he died

	char			aiSetup;		// set up and controllable in multiplayer
	long		delayFailed;		// when to trigger fail of event
	long		lastOrdered;		// when script last ordered him

};

