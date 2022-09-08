typedef struct {
	int eType;			// type of trooper

	int	x;
	int	y;

	int	avatar_facing;		// avatar facing last requested
	int	avatar_action;		// avatar action last requested
	int	current_action;		// avatar action actually being done
	int	current_command;	// current animation command

	ANIM *pAnimation;
	int	facing;				// current animation facing
} AVATAR;

#define UNIT_SLOW1	7	// slows units to walk
#define UNIT_SLOW2	12	// slows units to shuffle