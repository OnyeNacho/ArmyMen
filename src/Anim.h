/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Anim.h $
//
//	DESCRIPTION:	Animation interface
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Anim.h 59    4/12/98 3:36p Nrobinso $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/Anim.h $
//  
//  59    4/12/98 3:36p Nrobinso
//  remove unused
//  
//  58    4/10/98 1:33a Nrobinso
//  don't reset anim callback
//  
//  57    3/10/98 7:19p Phu
//  less of an anim world  boundary please
//  
//  56    3/07/98 10:45p Nrobinso
//  keep as last command of all anim commands
//  
//  55    3/05/98 4:42p Phu
//  increase anim world boundary
//  
//  54    3/03/98 9:40p Nrobinso
//  remove unused commands
//  
//  53    3/01/98 8:19p Nrobinso
//  add INDEX_FACING and WALKIE_TALKIE_COMMAND
//  
//  52    2/20/98 1:20p Nrobinso
//  remove unused commands
//  
//  51    2/10/98 1:26p Bwilcox
//  changed animfiguremovevehicle to animfigurewouldmoveto and
//  merged in common code from vehicle update into it
//  
//  50    2/02/98 9:30a Nrobinso
//  
//  49    1/30/98 12:44p Nrobinso
//  command structure has copy_seq instead of just copy
//  
//  48    1/30/98 11:38a Nrobinso
//  add READY_GUN_PRONE
//  
//  47    1/28/98 4:26p Nrobinso
//  new anim commands: sweep, sweep_stationary, prone raise gun
//  
//  46    1/14/98 9:46a Nrobinso
//  add ValidateCommandList
//  
//  45    1/13/98 12:03p Nrobinso
//  add ValidateAnim
//  
//  44    1/09/98 4:20p Phu
//  redraw when items change visibility is fixed
// 
//	...
// 
// 4     6/25/96 9:53p Nrobins
// added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __ANIM_H__
#define __ANIM_H__

// Includes

#ifndef __SPRITE_H__
	#include "sprite.h"
#endif

#include "disp.h"


/////////////////////////////////////////////////////////////////////////////
//					Structures
/////////////////////////////////////////////////////////////////////////////
#define INDEX_FACING(facing, pSeq) (((facing + (pSeq->divisor/2)) & MAX_CIRCLE_UNIT) / pSeq->divisor)

#define NULL_DIRECTION ~0

#define PIXELS_PER_FRAME 33

#define	ANIM_DEFAULT_BOUNDARY	32

#define ACTIVATE_LINKS TRUE
#define INACTIVATE_LINKS TRUE
#define NO_ACTIVATE_LINKS FALSE

// anim flags
#define	ANIM_FLAG_CLEAR				(ULONG)0x00000000
#define	ANIM_FLAG_ACTIVE			(ULONG)0x00000001
#define	ANIM_FLAG_CHILD				(ULONG)0x00000002
#define	ANIM_FLAG_UNUSED_A			(ULONG)0x00000004
#define	ANIM_FLAG_UNUSED_B			(ULONG)0x00000008
#define	ANIM_FLAG_UNUSED_C			(ULONG)0x00000010
#define	ANIM_FLAG_UNUSED_D			(ULONG)0x00000020
#define	ANIM_FLAG_UNUSED_E			(ULONG)0x00000040
#define	ANIM_FLAG_UNUSED_F			(ULONG)0x00000080
#define	ANIM_FLAG_UNUSED_G			(ULONG)0x00000100
#define	ANIM_FLAG_UNUSED_H			(ULONG)0x00000200
#define	ANIM_FLAG_UNUSED_I			(ULONG)0x00000400
#define	ANIM_FLAG_UNUSED_J			(ULONG)0x00000800
#define	ANIM_FLAG_UNUSED_K			(ULONG)0x00001000
#define	ANIM_FLAG_UNUSED_L			(ULONG)0x00002000
#define	ANIM_FLAG_UNUSED_M			(ULONG)0x00004000
#define	ANIM_FLAG_UNUSED_N			(ULONG)0x00008000
#define	ANIM_FLAG_UNUSED_O			(ULONG)0x00010000
#define	ANIM_FLAG_UNUSED_P			(ULONG)0x00020000
#define	ANIM_FLAG_UNUSED_Q			(ULONG)0x00040000
#define	ANIM_FLAG_UNUSED_R			(ULONG)0x00080000
#define	ANIM_FLAG_UNUSED_S			(ULONG)0x00100000
#define	ANIM_FLAG_UNUSED_T			(ULONG)0x00200000
#define	ANIM_FLAG_UNUSED_U			(ULONG)0x00400000
#define	ANIM_FLAG_UNUSED_V			(ULONG)0x00800000
#define	ANIM_FLAG_PREV_INVISIBLE	(ULONG)0x01000000
#define	ANIM_FLAG_UNUSED_X			(ULONG)0x02000000
#define	ANIM_FLAG_UNUSED_Y			(ULONG)0x04000000
#define	ANIM_FLAG_UNUSED_Z			(ULONG)0x08000000
#define	ANIM_FLAG_SET_FACING		(ULONG)0x10000000
#define	ANIM_FLAG_SCREEN_IS_WORLD	(ULONG)0x20000000
#define	ANIM_FLAG_INVISIBLE			(ULONG)0x40000000
#define	ANIM_FLAG_CELL				(ULONG)0x80000000

#define ANIM_FLAGS_ALL_UNUSED		(ULONG)0x0EFFFFFC


typedef enum {
	DIRECTION_UP = 0,
	DIRECTION_UP_1_LEFT = 8,
	DIRECTION_UP_2_LEFT = 16,
	DIRECTION_UP_3_LEFT = 24,
	DIRECTION_UP_LEFT = 32,
	DIRECTION_LEFT_5_UP = 40,
	DIRECTION_LEFT_6_UP = 48,
	DIRECTION_LEFT_7_UP = 56,
	DIRECTION_LEFT = 64,
	DIRECTION_LEFT_9_DOWN = 72,
	DIRECTION_LEFT_10_DOWN = 80,
	DIRECTION_LEFT_11_DOWN = 88,
	DIRECTION_DOWN_LEFT = 96,
	DIRECTION_DOWN_13_LEFT = 104,
	DIRECTION_DOWN_14_LEFT = 112,
	DIRECTION_DOWN_15_LEFT = 120,
	DIRECTION_DOWN = 128,
	DIRECTION_DOWN_17_RIGHT = 136,
	DIRECTION_DOWN_18_RIGHT = 144,
	DIRECTION_DOWN_19_RIGHT = 152,
	DIRECTION_DOWN_RIGHT = 160,
	DIRECTION_RIGHT_21_DOWN = 168,
	DIRECTION_RIGHT_22_DOWN = 176,
	DIRECTION_RIGHT_23_DOWN = 184,
	DIRECTION_RIGHT = 192,
	DIRECTION_RIGHT_25_UP = 200,
	DIRECTION_RIGHT_26_UP = 208,
	DIRECTION_RIGHT_27_UP = 216,
	DIRECTION_UP_RIGHT = 224,
	DIRECTION_RIGHT_29_UP = 232,
	DIRECTION_RIGHT_30_UP = 240,
	DIRECTION_RIGHT_31_UP = 248,

	MAX_CIRCLE_UNIT = 255,
	CIRCLE_UNITS = 256
} DIRECTIONS;
#define	FCIRCLE_UNITS	256.0

#define	SAME_FACING -1
#define	USE_ACTION_FRAME -1


typedef enum {
	NEXT_FRAME	= -3,
	LAST_FRAME	= -2,
	SAME_FRAME	= -1
} FRAME_NUMBERS;

#define SPECIAL_COMMAND	-128
typedef enum {
	LAST_FRAME_COMMAND		= -2,
	SAME_COMMAND			= -1,

	INACTIVATE_COMMAND		= 0,

	STAND_COMMAND,			// 1
	WALK_LEFT_COMMAND,
	WALK_RIGHT_COMMAND,
	RUN_LEFT_COMMAND,
	RUN_RIGHT_COMMAND,

	FIRE_STAND_COMMAND,		// 6
	FIRE_KNEEL_COMMAND,
	FIRE_PRONE_COMMAND,

	THROW_STAND_COMMAND,	// 9
	THROW_KNEEL_COMMAND,
	THROW_PRONE_COMMAND,

	KNEEL_COMMAND,			// 12
	PRONE_COMMAND,

	KNEELING_DOWN_COMMAND,	// 14	from a stand
	GO_PRONE_COMMAND,		// from a kneel
	STANDUP_COMMAND,		// from a kneel
	GETUP_COMMAND,			// from prone

	NO_COMMAND_18,			// CRAWL_LEFT_COMMAND,		// 18
	ROLL_FROM_STAND_R,

	DIVE_STAND_COMMAND,
	NO_COMMAND_21,			// FALL_FORWARD_COMMAND
	INVISIBLE_COMMAND,
	WALK_LEFT2_COMMAND,		// 23
	WALK_RIGHT2_COMMAND,
	STRIDE_RIGHT_COMMAND,	// 25,

	SHUFFLE_COMMAND,

	STRIDE_RIGHT2_COMMAND,
	NO_COMMAND_28,			// 28
	NO_COMMAND_29,			// 29

	TEST_COMMAND,				// used for test sequences

	// Trooper Death commands
	SHOOT_DEATH_KNEEL_COMMAND,	// 31
	SHOOT_DEATH_STAND_COMMAND,
	SHOOT_DEATH_PRONE_COMMAND,
	SQUASH_DEATH_COMMAND,
	MELT_DEATH_COMMAND,
	EXPLODE_DEATH_COMMAND,

	STRIDE_LEFT_COMMAND,
	FALL_BACKWARD_COMMAND,		// ??
	STRIDE_LEFT2_COMMAND,

	RAISE_GUN_STANDING_COMMAND,	// 40
	LOWER_GUN_STANDING_COMMAND,
	RAISE_GUN_KNEELING_COMMAND,
	LOWER_GUN_KNEELING_COMMAND,
	READY_GUN_STANDING_COMMAND,
	READY_GUN_KNEELING_COMMAND,

	RUN_LEFT2_COMMAND,			// 46
	RUN_RIGHT2_COMMAND,
	NO_COMMAND_48,				// CRAWL_LEFT2_COMMAND,		// 48

	ROLL_FROM_KNEEL_R,

	ROLL_FROM_STAND_L,
	ROLL_FROM_KNEEL_L,
	ROLL_FROM_PRONE_L,
	ROLL_FROM_PRONE_R,			// 53

	PRONE_INPLACE_L,

	WALK_FAST_LEFT_COMMAND,		// 55
	WALK_FAST_RIGHT_COMMAND,
	WALK_FAST_LEFT2_COMMAND,	// 57
	WALK_FAST_RIGHT2_COMMAND,

	DIVE_KNEEL_COMMAND,			// 59

	NO_COMMAND_60 = 60,
	SWEEP_STAND_COMMAND,
	SWEEP_LEFT_COMMAND,

	WALK_BACK_LEFT,				// 63
	WALK_BACK_RIGHT,

	SWEEP_RIGHT_COMMAND,		// 65
	SWEEP_LEFT2_COMMAND,
	SWEEP_RIGHT2_COMMAND,

	PRONE_INPLACE_R,			// 68
	NO_COMMAND_69,

	WALKIE_TALKIE_COMMAND,		// 70


// ----------------------------	// gap

	VMOVE_COMMAND = 80,
	VSTOP_COMMAND,
	VROCK_SLOW_COMMAND,
	VROCK_FAST_COMMAND,
	VDEAD_COMMAND,
	VDIE_COMMAND,
	VEHICLE_COMMAND_86,
	VEHICLE_COMMAND_87,
	VEHICLE_COMMAND_88,
	VEHICLE_COMMAND_89,

	MISSILE_COMMAND = 90,
	GRENADE_COMMAND,
	MISSILE_SHADOW_COMMAND,
	GRENADE_SHADOW_COMMAND,

// ----------------------------	// gap

	EXPLOSION_FIRST = 120,
	EXPLOSION_GUN_PUFF_M_COMMAND,
	EXPLOSION_UNUSED_2,
	EXPLOSION_GUN_SPARK_S_COMMAND,
	EXPLOSION_GUN_SPARK_M_COMMAND,
	EXPLOSION_GUN_SPARK_L_COMMAND,
	EXPLOSION_SMOKE_S_COMMAND,
	EXPLOSION_SMOKE_M_COMMAND,
	EXPLOSION_SMOKE_L_COMMAND,
	EXPLOSION_COMBUSTION_S_COMMAND,
	EXPLOSION_COMBUSTION_M_COMMAND,
	EXPLOSION_COMBUSTION_L_COMMAND,
	EXPLOSION_DIRT_SMOKE_S_COMMAND,
	EXPLOSION_DIRT_SMOKE_M_COMMAND,
	EXPLOSION_DIRT_SMOKE_L_COMMAND,
	EXPLOSION_FLASH_SMOKE_S_COMMAND,
	EXPLOSION_FLASH_SMOKE_M_COMMAND,
	EXPLOSION_FLASH_SMOKE_L_COMMAND,
	EXPLOSION_FLASH_COMBUSTION_S_COMMAND,
	EXPLOSION_FLASH_COMBUSTION_M_COMMAND,
	EXPLOSION_FLASH_COMBUSTION_L_COMMAND,
	EXPLOSION_FLASH_DIRT_SMOKE_S_COMMAND,
	EXPLOSION_FLASH_DIRT_SMOKE_M_COMMAND,
	EXPLOSION_FLASH_DIRT_SMOKE_L_COMMAND,
	EXPLOSION_WATER_S_COMMAND,
	EXPLOSION_WATER_M_COMMAND,
	EXPLOSION_WATER_L_COMMAND,
	EXPLOSION_WATER_GUN_PUFF_S_COMMAND,
	EXPLOSION_WATER_GUN_PUFF_M_COMMAND,
	EXPLOSION_WATER_GUN_PUFF_L_COMMAND,

	LAST_COMMAND,

	DELAY_COMMAND=1000,

	//don't add any commands after DELAY_COMMAND (increment it if necessary)

	NUM_COMMANDS
} COMMAND_NUMBERS;


typedef enum
{
	ONE_STEP_CMD,
	CONTINUE_CMD,
} FIGURE_TYPE;

//---------------------------------------------------------------------------
//			VELOCITY DEFINES
//---------------------------------------------------------------------------
#define		SEQUENCE_VELOCITY			((signed char) 0x01)
#define		ZERO_VELOCITY				((signed char) 0x00)
#define		MINUS_SEQUENCE_VELOCITY		((signed char) 0xFF)
#define		ABSOLUTE_VELOCITY			((signed char) 0x80)

//---------------------------------------------------------------------------
//				DATA STRUCTURES
//---------------------------------------------------------------------------

typedef struct {
    SHORT left; 
    SHORT front; 
    SHORT right; 
    SHORT back; 
} MOVE_RECT; 

typedef struct Frame
{
//	struct Sprite	*pSprite;
	SHORT	time;
	SHORT	sprite_index;
	SPOINT	primary_hotspot;
	SPOINT	secondary_hotspot;
} FRAME;

typedef struct Sequence
{
	SHORT frames;			// # of frames in each directional sequence
	SHORT directions;		// # of directions in sequence
	SHORT divisor;			// directional divisor
	SHORT base_velocity;
	FRAME *frame_list;
	SPRITE *spriteArray;
	SHORT max_index;
	SHORT action_frame;
} SEQUENCE;

typedef struct Command
{
	SHORT command_now;
	SHORT command_next;
	SEQUENCE *seq;
	char copy_seq;
} COMMAND;

typedef struct CommandList
{
	SHORT commands;
	COMMAND *command_array;
} COMMAND_LIST;

typedef struct AnimCell
{
	ULONG	flags;
	SPRITE	*pSprite;
	BYTE	*trans_table;
	void	*pOwner;		// pointer to the object that owns this anim/cell

	// world position
	SPOINT	world_pos;
	SPOINT	old_world_pos;

	SHORT	world_z;
	SHORT	old_world_z;
	
	RECT			wrect;
	short			num_feet;
	TDispFoot		*feet;
	SPRITE			*prevSprite;
	EObjectLayer	layer;
	short			order;
} ANIMCELL;


typedef struct Anim
{
	// marks active, linked to another cell, screen or world coordinates
	// hi bit allows a ANIMCELL to act like an anim in the ways it can
	// this would be much easier in C++, oh well
	ULONG	flags;
	SPRITE	*pSprite;
	BYTE	*trans_table;
	void	*pOwner;		// pointer to the object that owns this anim/cell

	// world position
	SPOINT	world_pos;
	SPOINT	old_world_pos;

	SHORT	world_z;
	SHORT	old_world_z;

	RECT			wrect;
	TDispNode		uldp, urdp, lldp, lrdp;
	int				uli, uri, lli, lri;
	SPRITE			*prevSprite;
	EObjectLayer	layer;
	short			order;
// end of AnimCell

	void			*pData;			// pointer to data needed by outside routines
	SPRITE			*spriteArray;
	COMMAND_LIST	*pCommandList;
	SEQUENCE		*pSeq;
	FRAME			*pFrame;

	DWORD last_update;			// time of last anim update
	DWORD timefix;				// Time of last fix (position update) from a remote object

	SHORT last_frame_time;		// ticks since anim hit the last frame 
	SHORT current_frame;		// frame in frame_list[]
	SHORT current_command;
	SHORT facing;				// apparent facing of frame
	SHORT facing_index;			// facing normalized for sequence
	SHORT next_command;			// command to do when current sequence ends
	SHORT next_facing;			// facing to do when current sequence ends
	SHORT next_velocity;		// velocity to do when current sequence ends

	SPOINT link;
	SPOINT trigger;

	SHORT velocity;
	SHORT x_velocity;
	SHORT y_velocity;
	SHORT z_velocity;
	SHORT pixels;
	SHORT frame_time;

	float dx;
	float dy;
	float dz;

	MOVE_RECT move_off;

	short	callback_command;
	short	callback_frame;
	LONG ((*callback)(struct Anim *panim));

	struct Anim *pChild;
	struct Anim *pParent;

	signed char set_velocity;	// how to figure velocity:
								// -1 (0xFF): sequence velocity backwards
								// 0 (0x00): no velocity
								// +1 (0x01): sequence velocity
								// 128 (0x80): absolute velocity

	ULONG anim_sound;	//ID number for the sound associated with this anim
} ANIM;

#define AnimCellSetOwner(pAnim, pOwner) AnimSetOwner((ANIM*)pAnim, pOwner)

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
extern double sin_table[CIRCLE_UNITS];
extern double cos_table[CIRCLE_UNITS];
extern int	  arc_sin_table[201];


/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////
short GetDirection(SPOINT *pOrigin, SPOINT *pTarget);

void MovementTableInit(void);
int NormalizeFacing(int facing);
int NormalizeFacingAdd(int facing, int add);
int NormalizeFacingSubtract(int facing, int subtract);

void AnimSetCommand(ANIM *pAnim, int command);
void AnimCommand(ANIM *pAnim, int command, SHORT facing);
void AnimForceCommand(ANIM *pAnim, int command, SHORT facing);
void AnimCommandVelocity(ANIM *pAnim, SHORT velocity_type, SHORT velocity);
void AnimForceVelocity(ANIM *pAnim, SHORT velocity_type, SHORT velocity);
void AnimSetOwner(ANIM *pAnim, void *pOwner );
BOOL AnimHaveOwner(ANIM *pAnim, void *pOwner );
void AnimCallback(ANIM *pAnim, void *callback, short frame, short command);
void AnimCallbackClear(ANIM *pAnim);
void AnimSet(ANIM *pAnim, SHORT x, SHORT y, COMMAND_LIST *pCommandList, SHORT command, int facing, SHORT velocity_type);
extern inline void AnimSetCommandList(ANIM *pAnim, COMMAND_LIST *pCommandList);
void AnimSetZ(ANIM *pAnim, SHORT z, SHORT zvelocity);
void AnimSetSize(ANIM *pAnim);
void AnimSetPosition(ANIM *pAnim, SHORT x, SHORT y, int facing);
void AnimUpdateChildPos(ANIM *pParent);

void AnimApplyOffset(ANIM *pAnim, SHORT x, SHORT y);
void AnimChgFacing(ANIM *pAnim, int facing);
void AnimForceFacing(ANIM *pAnim, int facing);
void AnimInit(int maxwidth, int maxheight, ANIM *pAnim, EObjectLayer eLayer);
void AnimLink(ANIM *pParent, ANIM *pChild);
void AnimMove(ANIM *pAnim, BOOL Interpolate, BOOL Reverse = FALSE);
void AnimMoveUpdate(ANIM *pAnim);
void AnimUpdate(ANIM *pAnim);
void AnimActivate(ANIM *pAnim, BOOL activate_links);
void AnimInactivate(ANIM *pAnim, BOOL inactivate_links);

void AnimDisplay( ANIM* pAnim );
void AnimCellDisplay( ANIMCELL* pCell );

void AnimDelete( ANIM* pAnim );
void AnimTransTable(ANIM* pAnim, BYTE *ptable);

void AnimWorldToScreen( SPOINT* pWorld, SPOINT* pScreen );
void AnimSetupDefault( );
void AnimReleaseDefault( );

void AnimSetDelay(ANIM *pAnim, int numframes);

POINT AnimFigureMove(ANIM *pAnim, int command, SHORT facing, FIGURE_TYPE type);
SPOINT AnimFigureWouldMoveTo(ANIM *pAnim, SHORT facing, int velocity);

//SPRITE *getanimsprite(ANIM *pAnim, short command, int facing);
SPRITE* AnimSprite(ANIM *pAnim, int command, SHORT facing, SHORT frame);

void ValidateAnim(ANIM *pAnim);
void ValidateCommandList(COMMAND_LIST *pCommandList);

#endif
