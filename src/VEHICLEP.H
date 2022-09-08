typedef enum VEHICLE_STATE
{
    VEHICLE_UNDEPLOYED,
    VEHICLE_DEPLOYED,
    VEHICLE_DYING,			// while anim running still but dead vehicle
    VEHICLE_DEAD
};

typedef struct
{
	SPOINT upperLeft;
	unsigned short data[16];
} VEHICLE_MASK;


// VEHICLE structure
typedef struct
{
	struct ITEM	common;			// common components of all objects
	// ADD NEW FIELDS AFTER THIS POINT

	// variable info
    VEHICLE_STATE state;		// status of vehicle
    SPOINT deployPosition;		// where to deploy it if dynamic
    short	deployFacing;	// facing to deploy if delayed

	// constant/local info
	WEAPON		weapon;
	ANIM*		pAnimation;		// vehicle animation information
	SHORT*		move_table;
	FLOAT_OBJ*	pProjectile;	// associated bazooka round or grenade

	ULONG		looping_sndID;	// vehicle movement sound
	DWORD		accel_coefficient;
	DWORD		reverse_coefficient;
	DWORD		brake_coefficient;

	SHORT		full_velocity;
	SHORT		velocity;		// effective velocity
    SHORT		spin;			// intended facing turn amount
	SHORT		max_velocity;
	SHORT		min_velocity;
	SHORT		gun_facing;		// directional facing of gun turret (0..255)

	short		nCollisionDamage;	// damage done by tank when it collides with something
	short		nArmor;

	char		which_missile;
	char		bTurret;		//has a turret (and has graphics to support it)

    // data for sphere of influence of vehicle and weapon
    int			lastVehicleFacing;	// what direction we last faced
    int			lastWeaponFacing;	// what direction weapon last faced
    int			seen;				// can opponent see this vehicle
                                    // You can always see your own forces.
	int			count;
	int			tcount;

    // data for ai commander to control it
    void*		controller;			// if it has an ai controller attached
    SPOINT		aiGoal;				// goal location if ai controlled
    int			npc;				// controllable from script
    int			humanAI;			// turned on temp by human for ai control
    int			speed;				// how fast
    int			imode;				// in mode behavior
    int			atmode;				// at mode behavior
    int			hitWhen;			// when last hit
    int 		arrivalEvent; 		// event to raise on arrival
    int			eventtype;			// what kind of event
	long		delayFailed;		// when to trigger fail of event

	//to avoid getting stuck
	int			framesstuck;		//how many game frames has the vehicle been unable to move

	//what tiles it's currently covering
	VEHICLE_MASK mask;

    ITEM*	focusItem;		// who vehicle is following

    // shadow update data
	SHORT		new_full_velocity;
    SHORT		new_velocity;	
	SHORT		new_gun_facing;
	SHORT		new_facing;
    SPOINT		new_position;

    SHORT		old_velocity;	
	SHORT		old_gun_facing;


	SHORT		framesNotMoving; //if the vehicle doesn't move for a while, we add it to the movement layer
	SHORT		prevBadTiles;		// number of bad tiles saved up.

    SARGE		*pDriver;
    long		lastInterpolated; // when we last updated interpolation of remote
    int			lastGunAdjust;

	SPOINT			deadPosition; // where he died
	long		lastOrdered; // when script ordered him last

}  VEHICLE;
