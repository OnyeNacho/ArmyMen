/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Anim.cpp $
//
//	DESCRIPTION:	animation routines
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Anim.cpp 100   4/12/98 3:35p Nrobinso $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Anim.cpp $
//  
//  100   4/12/98 3:35p Nrobinso
//  remove unused; make sure full sequence time is minimum the current
//  frame time
//  
//  99    4/10/98 2:12p Nrobinso
//  remove limit on animcallback set
//  
//  98    4/10/98 1:33a Nrobinso
//  don't reset anim callback
//  
//  97    4/08/98 10:46a Nrobinso
//  improve error message
//  
//  96    4/02/98 2:03p Phu
//  typecasting to prevent warnings
//  
//  95    3/13/98 1:07p Phu
//  
//  94    3/13/98 1:06p Phu
//  fix error in AnimWorldBoundary
//  
//  93    3/13/98 11:29a Nrobinso
//  anim code sets a bit in the owning  item if walking backwards
//  
//  92    98-03-12 22:57 Dmaynard
//  fix the possibility of AnimWorldBounday being called with an animcell
//  
//  91    3/12/98 7:10p Phu
//  move in anim world boundary
//  
//  90    98-03-10 18:14 Dmaynard
//  fix anim/animcell conflicts in AnimActivate
//  
//  89    3/05/98 4:36p Nrobinso
//  play with traces
//  
//  88    3/01/98 8:19p Nrobinso
//  NORMALIZE_FACING becomes INDEX_FACING and goes into anim.h
//  
//  87    2/20/98 3:35p Nrobinso
//  remove old code
//  
//  86    2/20/98 1:15p Nrobinso
//  fix up sounds
//  
//  85    2/10/98 1:25p Bwilcox
//  changed animfiguremovevehicle to animfigurewouldmoveto and
//  merged in common code from vehicle update into it
//  
//  84    1/26/98 11:59a Nrobinso
//  new path defines
//  
//  83    1/22/98 6:38p Nrobinso
//  use SetPath
//  
//  82    1/15/98 2:32p Phu
//  skip nonexistant sequences on validate sequence
//  
//  81    1/15/98 9:58a Nrobinso
//  add Error box to validate command list
//  
//  80    1/14/98 9:44a Nrobinso
//  add ValidateCommandList
//  
//  79    1/13/98 12:03p Nrobinso
//  add ValidateAnim
//  
//	...
// 
// 3     6/25/96 9:53p Nrobins
// added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Army.h"
#include "MainFrm.h"
#include "Tad.h"
#include "Map.h"
#include "Anim.h"
#include "GameFlow.h"
#include "AnimFile.h"
#include "comm.h"
#include "miscfile.h"

#include "audio.h"
#include "aiAccess.h"


// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PI 3.1415926535
#define MILLISECONDS 1000

//---------------------------------------------------------------------------
// anim callbacks: when to call the callback function, if any
// never, at end (at end of every sequence), every (after every frame),
// final (at end of sequence of sequences)
//---------------------------------------------------------------------------
#define		ANIM_CALLBACK_FINAL -4
#define		ANIM_CALLBACK_NEVER -3
#define		ANIM_CALLBACK_AT_END -2
#define		ANIM_CALLBACK_EVERY_FRAME -1

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////
double sin_table[CIRCLE_UNITS];
double cos_table[CIRCLE_UNITS];
int    arc_sin_table[201];


// controls hotspot green dot display
char hotspots = FALSE;

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////
void	AnimWorldBoundary( ANIM* pTheAnim );

/////////////////////////////////////////////////////////////////////////////
//					Local Prototypes
/////////////////////////////////////////////////////////////////////////////
void AnimSetupCommand(ANIM *pAnim, SHORT command);

/////////////////////////////////////////////////////////////////////////////
extern int ExplodeCount;

// Code

void MovementTableInit(void)	
{
	int		i, j;
	double	curangle, destangle, anglestep;
	const   step = 8;

	struct TAngleData
	{
		int dx, dy;
	} AngleData[64/step + 1] =
	{
		{    0, -512 },				// facing =   0
		{ -119, -498 },				// facing =   8
		{ -223, -461 },				// facing =  16
		{ -313, -406 },				// facing =  24
		{ -389, -334 },				// facing =  32
		{ -445, -253 },				// facing =  40
		{ -483, -172 },				// facing =  48
		{ -504,  -89 },				// facing =  56
		{ -512,    0 }				// facing =  64
	};


	for( i = 0; i < 64; i++ )
	{
		if( i % step == 0 )
		{
			cos_table[i] = (double)AngleData[i/step].dx / 512.0;
			sin_table[i] = (double)AngleData[i/step].dy / 512.0;
			curangle = PI - asin( -(double)sin_table[i] );
			destangle = PI - asin( -((double)AngleData[i/step+1].dy / 512.0) );
			anglestep = (destangle - curangle) / step;
		}
		else
		{
			curangle += anglestep;
			cos_table[i] = cos( curangle );
			sin_table[i] = -sin( curangle );
		}
	}
	cos_table[64] = (double)AngleData[64/step].dx / 512.0;
	sin_table[64] = (double)AngleData[64/step].dy / 512.0;
	for( i = 1; i < 64; i++ )
	{
		cos_table[64+i] = cos_table[64-i];
		sin_table[64+i] = -sin_table[64-i];
	}
	cos_table[128] = (double)AngleData[0].dx / 512.0;
	sin_table[128] = -(double)AngleData[0].dy / 512.0;
	for( i = 1; i < 64; i++ )
	{
		cos_table[128+i] = -cos_table[128-i];
		sin_table[128+i] = sin_table[128-i];
	}
	cos_table[192] = -cos_table[64];
	sin_table[192] = sin_table[64];
	for( i = 1; i < 64; i++ )
	{
		cos_table[192+i] = cos_table[192-i];
		sin_table[192+i] = -sin_table[192-i];
	}

	int    angle;
	double diff;
	for( i = -100; i <= 100; i++ )
	{
		angle = 0;
		diff = 1.0;
		for( j = 0; j <= 128; j++ )
		{
			if( fabs( sin_table[j] - ((double)i/100.0) ) < diff )
			{
				angle = j;
				diff = fabs(sin_table[j] - ((double)i/100.0));
			}
		}
		arc_sin_table[i+100] = angle;
	}
}	// MovementTableInit


int NormalizeFacing(int facing)	{
    while (facing >= CIRCLE_UNITS) facing -= CIRCLE_UNITS;
    while (facing < 0) facing += CIRCLE_UNITS;

	return facing;
}

int NormalizeFacingAdd(int facing, int add)	{
	facing += add;
	facing = facing % CIRCLE_UNITS;

	return facing;
}

int NormalizeFacingSubtract(int facing, int subtract)	{
	facing -= subtract;
	facing += CIRCLE_UNITS;

	facing = facing % CIRCLE_UNITS;

	return facing;
}


LOCAL CSpriteCatalog *pCatInvisible = NULL;
COMMAND	default_command_array[] = {
	{INVISIBLE_COMMAND, INVISIBLE_COMMAND, NULL},
};
COMMAND_LIST default_commands = {sizeof(default_command_array)/sizeof(COMMAND), default_command_array};

void	AnimSetupDefault( )	{
	if (pCatInvisible)
		return;

	SetPath(FLASH_PATH);
	pCatInvisible = AnimImport("invisible.axc", BM_TRANSPARENT);
	if (pCatInvisible)	{
		ProcessAnim(pCatInvisible, &default_commands);
	}
}

void	AnimReleaseDefault( )	{
	if (pCatInvisible)
		FreeAnimImport(pCatInvisible);
	pCatInvisible = NULL;
}


short
GetDirection(SPOINT *pOrigin, SPOINT *pTarget)	{
	double arctan;
	short shorttan;
	long xdiff;
	long ydiff;

	xdiff = pTarget->x - pOrigin->x;
	ydiff = pTarget->y - pOrigin->y;

	if (!xdiff && !ydiff)
		return NULL_DIRECTION;

	arctan = atan2((double) -ydiff, (double) xdiff);
	if (arctan < 0)
		arctan += PI*2;

	arctan -= (PI/2);
	if (arctan < 0)
		arctan += PI*2;

	arctan /= PI*2;
	arctan *= CIRCLE_UNITS;

	arctan +=.5;

	if (arctan >= FCIRCLE_UNITS)
		arctan = 0;

	shorttan = (short) arctan;	// round

	ASSERT(shorttan >= 0);
	ASSERT(shorttan < CIRCLE_UNITS);

	return shorttan;
}

void AnimSetSize(ANIM *pAnim)	{
	SEQUENCE *pSeq = pAnim->pCommandList->command_array[0].seq;
	if (pSeq)	{
		SPRITE *spriteArray = pSeq->spriteArray;
		FRAME *pFrame = pSeq->frame_list;
		SPRITE *pSprite = &spriteArray[pFrame[0].sprite_index];

		SHORT x = pFrame[0].primary_hotspot.x;
		SHORT y = pFrame[0].primary_hotspot.y;

		pAnim->move_off.left = x - (short)pSprite->srect.left;
		pAnim->move_off.right = (short)pSprite->srect.right - x;

		pAnim->move_off.front = y - (short)pSprite->srect.top;
		pAnim->move_off.back = (short)pSprite->srect.bottom - y;
	}
}

void AnimSet(ANIM *pAnim, SHORT x, SHORT y, COMMAND_LIST *pCommandList, SHORT command, int facing, SHORT velocity_type)	{
	pAnim->facing = pAnim->next_facing = facing;
	pAnim->pCommandList = pCommandList;
	pAnim->current_frame = 0;
	pAnim->last_frame_time = 0;
	AnimSetupCommand(pAnim, command);
	AnimForceVelocity(pAnim, velocity_type, 0);

	// save the old world position and update to the new
	pAnim->old_world_pos = pAnim->world_pos;

	// update the world position
	pAnim->world_pos.x = x;
	pAnim->world_pos.y = y;

	//	AnimSetSize(pAnim);
}

inline void AnimSetCommandList(ANIM *pAnim, COMMAND_LIST *pCommandList)	{
	pAnim->pCommandList = pCommandList;
}

void AnimSetDelay(ANIM *pAnim, int numframes)
{
	pAnim->next_command=pAnim->current_command;
	pAnim->current_command=DELAY_COMMAND+numframes;
}


void AnimSetZ(ANIM *pAnim, SHORT z, SHORT zvelocity)	{
	pAnim->old_world_z = pAnim->world_z;
	pAnim->world_z = z;
	pAnim->z_velocity = zvelocity;
}

void AnimSetPosition(ANIM *pAnim, SHORT x, SHORT y, int facing)	{
	if (facing == SAME_FACING)
		pAnim->next_facing = pAnim->facing;
	else
		pAnim->next_facing = pAnim->facing = facing;

	// save the old world position and update to the new
	pAnim->old_world_pos = pAnim->world_pos;

	// update the world position
	pAnim->world_pos.x = x;
	pAnim->world_pos.y = y;
	MoveDispXObject( (ANIMCELL *)pAnim, FALSE );
}


void AnimSetupCommand(ANIM *pAnim, SHORT command)	{
	SEQUENCE *pSeq;
	COMMAND_LIST *pCommandList;
	COMMAND	*pCommand;
	SHORT	commands,
			i;

	if (command == INACTIVATE_COMMAND)	{
		AnimInactivate(pAnim, INACTIVATE_LINKS);
		return;
	}

	pCommandList = pAnim->pCommandList;
	pCommand = pCommandList->command_array;
	commands = pCommandList->commands;

	// search command list for the appropriate command
	for (i=0; i<commands; i++)	{
		if (pCommand[i].command_now == command)	{
			pAnim->current_command = command;
			pSeq = pCommand[i].seq;
			pAnim->next_command = pCommand[i].command_next;
			break;
		}
	}
	if (i >= commands)	{
		TRACE( "ERROR: anim command %d not found. [%s,%d]\n", command, __FILE__, __LINE__ );
		pAnim->current_command = pCommand[0].command_now;
		pSeq = pCommand[0].seq;
		pAnim->next_command = pCommand[0].command_next;
	}

	// keep the anim engine from crashing by giving it a legit target
	if (!pSeq)	{
		pSeq = default_command_array[0].seq;
		TRACE("ERROR: Forced to set a sequence pointer to invisible sequence in AnimSetupCommand command: %d\n", command);
	}

	pAnim->pSeq = pSeq;
	pAnim->spriteArray = pSeq->spriteArray;

	SHORT facing_index = INDEX_FACING(pAnim->facing, pSeq);
	pAnim->facing_index = facing_index;
	pAnim->pFrame = pSeq->frame_list + (facing_index * pSeq->frames);
	pAnim->pSprite = &pAnim->spriteArray[pAnim->pFrame[pAnim->current_frame].sprite_index];

	switch(pAnim->set_velocity)	{
		case SEQUENCE_VELOCITY:
			pAnim->velocity = pSeq->base_velocity;
			break;
		case ZERO_VELOCITY:
			pAnim->velocity = 0;
			break;
		case MINUS_SEQUENCE_VELOCITY:
			pAnim->velocity = -pSeq->base_velocity;
			break;
		case ABSOLUTE_VELOCITY:
			pAnim->velocity = pAnim->next_velocity;
			break;
	}

	ITEM *pOwner = (ITEM *)pAnim->pOwner;
	if (pOwner)	{
		pOwner->bItemFlags &= ~ITEM_REVERSED;
		if (command == WALK_BACK_LEFT || command == WALK_BACK_RIGHT)
			pOwner->bItemFlags |= ITEM_REVERSED;
	}
}

void AnimApplyOffset(ANIM *pAnim, SHORT x, SHORT y)	{
	// update the world position
	pAnim->world_pos.x += x;
	pAnim->world_pos.y += y;
}


void AnimChgFacing(ANIM *pAnim, int facing)	{
	if (facing == SAME_FACING)
		pAnim->next_facing = pAnim->facing;
	else	{
		if (pAnim->facing_index == INDEX_FACING(facing, pAnim->pSeq))
			pAnim->facing = pAnim->next_facing = facing;
		else
			pAnim->next_facing = facing;
	}
}

void AnimForceFacing(ANIM *pAnim, int facing)	{
	if (facing == SAME_FACING)	{
		pAnim->next_facing = pAnim->facing;
	}
	else	{
		pAnim->flags |= ANIM_FLAG_SET_FACING;
		pAnim->next_facing = facing;
	}
}

void AnimInit( int maxwidth, int maxheight, ANIM *pAnim, EObjectLayer eLayer)	
{
	ZeroMemory( pAnim, sizeof(ANIM));
	pAnim->callback_frame=ANIM_CALLBACK_NEVER;
	pAnim->anim_sound=SND_NULL_SND_ID;
	CreateDispXObject( maxwidth, maxheight, (ANIMCELL *)pAnim, eLayer );
	pAnim->pParent = pAnim->pChild = NULL;
}


void AnimLink(ANIM *pParent, ANIM *pChild)	{
	pChild->flags |= ANIM_FLAG_CHILD;
	pParent->pChild = pChild;

	pChild->pParent = pParent;
	if (pParent->pParent)
		pChild->pParent = pParent->pParent;
}


void AnimActivate(ANIM *pAnim, BOOL activate_links)	
{
	if( pAnim->flags & ANIM_FLAG_CELL )	{
		if (!(pAnim->flags & ANIM_FLAG_ACTIVE))
			pAnim->flags |= ANIM_FLAG_ACTIVE;
	}
	else	{	
		if (!(pAnim->flags & ANIM_FLAG_ACTIVE))	{
			pAnim->flags |= ANIM_FLAG_ACTIVE;
			pAnim->last_update = gpGame->dwAnimTime;
		}

		if (activate_links)	{
			if (pAnim->pChild)
				AnimActivate(pAnim->pChild, ACTIVATE_LINKS);
		}
	}
}


void AnimInactivate(ANIM *pAnim, BOOL inactivate_links)	
{
	pAnim->flags &= ~ANIM_FLAG_ACTIVE;
	MoveDispXObject( (ANIMCELL *)pAnim, FALSE );

	if( !(pAnim->flags & ANIM_FLAG_CELL ))	{
		if( inactivate_links && ( !(pAnim->flags & ANIM_FLAG_CELL) ) )
			if (pAnim->pChild)
				AnimInactivate(pAnim->pChild, INACTIVATE_LINKS);
	}
}


// this owner pointer is required of any anim that goes intot display list that we want to collision detect
void AnimSetOwner(ANIM *pAnim, void *pOwner )	{
	pAnim->pOwner = pOwner;
}

BOOL AnimHaveOwner(ANIM *pAnim, void *pOwner )	{
	return ( pAnim->pOwner == pOwner );
}

void AnimCallback(ANIM *pAnim, void *callback, short frame, short command )	{
//	if (pAnim->callback == NULL)	{
		pAnim->callback = (LONG (*)(ANIM *)) callback;
		pAnim->callback_frame = frame;
		pAnim->callback_command = command;
//	}
}

void AnimCallbackClear(ANIM *pAnim)	{
	pAnim->callback = NULL;
	pAnim->callback_frame = 0;
	pAnim->callback_command = 0;
}


//extern inline SARGE*	SargePointer(int eArmy);

void AnimCommand(ANIM *pAnim, int command, SHORT facing)	{
//	void *pOwner = pAnim->pOwner;
//	if (pOwner)	{
//		if (pOwner == SargePointer(ARMY_PLAYER))
//			TRACE("%d\n",command);
//	}

	if (command != SAME_COMMAND)
		pAnim->next_command = command;

	if (facing == SAME_FACING)
		pAnim->next_facing = pAnim->facing;
	else	{
		if (pAnim->facing_index == INDEX_FACING(facing, pAnim->pSeq))
			pAnim->facing = pAnim->next_facing = facing;
		else
			pAnim->next_facing = facing;
	}
}

void AnimSetCommand(ANIM *pAnim, int command)	{
	if (command != SAME_COMMAND)
		pAnim->next_command = command;
}

void AnimForceCommand(ANIM *pAnim, int command, SHORT facing)	{
	if (command == LAST_FRAME_COMMAND)
		return;

	if (command == SAME_COMMAND)
		pAnim->next_command = pAnim->current_command;
	else
		pAnim->next_command = command;

	if (facing == SAME_FACING)
		pAnim->next_facing = pAnim->facing;
	else
		pAnim->next_facing = pAnim->facing = facing;

	pAnim->current_frame = 0;
	pAnim->last_frame_time = 0;
	AnimSetupCommand(pAnim, pAnim->next_command);
}


void AnimCommandVelocity(ANIM *pAnim, SHORT velocity_type, SHORT velocity)	{
	pAnim->set_velocity = (signed char) velocity_type;
	pAnim->next_velocity = velocity;
}

void AnimForceVelocity(ANIM *pAnim, SHORT velocity_type, SHORT velocity)	{
	pAnim->set_velocity = (signed char) velocity_type;

	switch(velocity_type)	{
		case SEQUENCE_VELOCITY:
			pAnim->velocity = pAnim->pSeq->base_velocity;
			break;
		case ZERO_VELOCITY:
			pAnim->velocity = 0;
			break;
		case MINUS_SEQUENCE_VELOCITY:
			pAnim->velocity = -pAnim->pSeq->base_velocity;
			break;
		case ABSOLUTE_VELOCITY:
			pAnim->velocity = velocity;
			break;
	}
	pAnim->next_velocity = pAnim->velocity;
}

void AnimOverrideCommand(ANIM *pAnim, COMMAND *pCommand)	{
	TRACE("AnimOverrideCommand() not implemented\n");
}


void AnimMove(ANIM *pAnim, BOOL Interpolate, BOOL Reverse)	{
	LONG	dx,dy,dz;
	SHORT	direction;
	DWORD	dwDeltaTime = gpGame->dwDeltaTime;

	ASSERT( !(pAnim->flags & ANIM_FLAGS_ALL_UNUSED) );

	if (Interpolate && pAnim->timefix) {
		if ( (pAnim->timefix > (gpGame->dwAnimTime-dwDeltaTime)) 
		&&  (gpGame->dwAnimTime > pAnim->timefix))   { // we receive an update between Frames
			dwDeltaTime = (gpGame->dwAnimTime-pAnim->timefix);
		}
		else dwDeltaTime = 0;
	}
	if (pAnim->flags & ANIM_FLAG_ACTIVE)	{
		// update world position
		if (!(pAnim->flags & ANIM_FLAG_CHILD))	{

			direction = pAnim->facing;
			if( Reverse )
			{
				direction = NormalizeFacing(pAnim->facing + 128);
			}

			if (pAnim->velocity && dwDeltaTime)	{

				if( (pAnim->pOwner) &&
					(ITEM_TYPE( (ITEM *)(pAnim->pOwner) ) == ARMY_VEHICLE) )
				{	
					direction = ((direction + 4) / 8) * 8;
					if( direction >= 256 )
						direction = 0;
				}			

				// now update the world position
				float pixels = ((float) pAnim->velocity * (float) dwDeltaTime) / MILLISECONDS;

				pAnim->pixels = (short)pixels;

				pAnim->dx += (float)cos_table[direction] * pixels;
				dx = (long) pAnim->dx;
				pAnim->x_velocity = (short) dx;
				pAnim->dx -= dx;
				pAnim->world_pos.x += (SHORT)dx;

				pAnim->dy += (float)sin_table[direction] * pixels;
				dy = (long) pAnim->dy;
				pAnim->y_velocity = (short) dy;
				pAnim->dy -= dy;
				pAnim->world_pos.y += (SHORT)dy;
			}

			if (pAnim->z_velocity && dwDeltaTime)	{
				// now update the world position
				float z = ((float) pAnim->z_velocity * (float) dwDeltaTime) / MILLISECONDS;
				pAnim->dz += z;
				dz = (long) pAnim->dz;
				pAnim->dz -= dz;
				pAnim->world_z += (SHORT)dz;
			}

			AnimWorldBoundary( pAnim );
		}
		// update world_pos, if a child
		else	{
			ANIM *pParent = pAnim->pParent;
			SPOINT pt = pParent->pFrame[pParent->current_frame].secondary_hotspot;

			pAnim->world_pos.x = pParent->world_pos.x + pt.x;
			pAnim->world_pos.y = pParent->world_pos.y + pt.y;
		}
	}

	if (fabs(pAnim->dx) < .001)
		pAnim->dx = 0;

	if (fabs(pAnim->dy) < .001)
		pAnim->dy = 0;

	MoveDispXObject( (ANIMCELL *)pAnim, FALSE );

	if (pAnim->pChild)
		AnimMove(pAnim->pChild,Interpolate);
	if(Interpolate) pAnim->timefix = 0;
}

void AnimMoveUpdate(ANIM *pAnim)	{
	DWORD	dwDeltaTime = gpGame->dwDeltaTime;

	if (pAnim->flags & ANIM_FLAG_ACTIVE)	{
		if (!(pAnim->flags & ANIM_FLAG_CHILD))	{
			AnimWorldBoundary( pAnim );
		}
		else	{
			ANIM *pParent = pAnim->pParent;
			SPOINT pt = pParent->pFrame[pParent->current_frame].secondary_hotspot;

			pAnim->world_pos.x = pParent->world_pos.x + pt.x;
			pAnim->world_pos.y = pParent->world_pos.y + pt.y;
		}
	}

	MoveDispXObject( (ANIMCELL *)pAnim, FALSE );

	if (pAnim->pChild)
		AnimMoveUpdate(pAnim->pChild);
}


BOOL AnimTestUpdate(ANIM *pTest, int command, SHORT facing, FIGURE_TYPE type)	{
	SHORT		frame;
	SEQUENCE	*pSeq;
	FRAME		*pFrame;
	COMMAND_LIST *pCommandList;
	COMMAND	*pCommand;
	SHORT	commands;
	SHORT	facing_index;
	BOOL	end = FALSE;

	if (command == SAME_COMMAND)
		command = pTest->current_command;

	if (facing == SAME_FACING)
		facing = pTest->facing;

	frame = pTest->current_frame;
	pSeq = pTest->pSeq;
	pFrame = pTest->pFrame;

	pTest->frame_time = pFrame[0].time;

	facing_index = INDEX_FACING(facing, pSeq);

	if (pTest->facing_index == facing_index)	{
		pTest->facing = facing;
	}

	if (gpGame->dwAnimTime < pTest->last_update + pFrame[frame].time)
		return end;

	frame++;

	// now check to see if we've reached the end of a sequence
	// if we are at the end of a sequence, do the next_command
	if (frame >= pSeq->frames)	{
		if (pTest->next_command != LAST_FRAME_COMMAND)	{
			pCommandList = pTest->pCommandList;
			pCommand = pCommandList->command_array;
			commands = pCommandList->commands;

			// search command list for the appropriate command
			for (int i=0; i<commands; i++)	{
				if (pCommand[i].command_now == command)	{
					pSeq = pCommand[i].seq;
					break;
				}
			}
			if (i >= commands)	{
				pSeq = pCommand[0].seq;
			}

			// keep the anim engine from crashing by giving it a legit target
			if (!pSeq)	{
				pSeq = default_command_array[0].seq;
				TRACE("ERROR: Forced to set a sequence pointer to invisible sequence in AnimTestUpdate\n");
			}

			pTest->pSeq = pSeq;
			pTest->velocity = pSeq->base_velocity;		
			pTest->current_frame = 0;
			pTest->last_frame_time = 0;

			pTest->facing = facing;
			SHORT facing_index = INDEX_FACING(facing, pSeq);
			pTest->facing_index = facing_index;

			pFrame = pSeq->frame_list + (facing_index * pSeq->frames);
			pTest->pFrame = pFrame;
			pTest->frame_time = pFrame[0].time;

			end = TRUE;
		}
	}
	else	{
		pTest->current_frame = frame;
	}

	if (!pTest->velocity)	{
		pTest->dx = 0;
		pTest->dy = 0;
	}

	return end;
}

SPOINT AnimFigureWouldMoveTo(ANIM *pAnim, SHORT facing, int velocity)	{
	DWORD	time = gpGame->dwDeltaTime;
    SPOINT	pt;
	float dx, dy;

	if (facing == SAME_FACING)
		facing = pAnim->facing;

	// now update the world position
	float pixels = ((float) velocity * (float) time) / MILLISECONDS;

	dx = pAnim->dx + ((float)cos_table[facing] * pixels);
	dy = pAnim->dy + (float)sin_table[facing] * pixels;

    pt.x = (long) dx + pAnim->world_pos.x;
	pt.y = (long) dy + pAnim->world_pos.y;

    return pt;
}


POINT AnimFigureMove(ANIM *pAnim, int command, SHORT facing, FIGURE_TYPE type)	{
	DWORD	time = gpGame->dwDeltaTime;
	POINT	pt;
	ANIM	TestAnim;
	ANIM	*pTest = &TestAnim;
	BOOL	done = FALSE;
	int		i=0;
	SEQUENCE *pSeq;
	BOOL	end = FALSE,
			prev_end = FALSE;

	*pTest = *pAnim;
	while (fabs(TestAnim.dx) < 1.0 && fabs(TestAnim.dy) < 1.0 && !done)	{
		end = AnimTestUpdate(&TestAnim, command, facing, type);

		pSeq = TestAnim.pSeq;

		if (type == CONTINUE_CMD)	{
			done = TRUE;
			time += (pSeq->frames - TestAnim.current_frame) * TestAnim.frame_time;
		}

		SHORT new_facing = TestAnim.facing;
		int velocity = pSeq->base_velocity;

		if (velocity)	{
			// now update the world position
			float pixels = ((float) velocity * (float) time) / MILLISECONDS;

			TestAnim.dx += (float)cos_table[new_facing] * pixels;
			TestAnim.dy += (float)sin_table[new_facing] * pixels;
		}

		if (!TestAnim.dx && !TestAnim.dy)
			done = TRUE;

		TestAnim.last_update = 0;	// force the next frame

		i++;
		if (i>8)
			done = TRUE;
	}

	pt.x = (long) TestAnim.dx;
	pt.y = (long) TestAnim.dy;

    return pt;
}

void AnimUpdateChildPos(ANIM *pParent)	{
	ANIM *pLink = pParent;
	SPOINT pt = pParent->pFrame[pParent->current_frame].secondary_hotspot;

	while (pLink = pLink->pChild)	
	{
		pLink->world_pos.x = pParent->world_pos.x + pt.x;
		pLink->world_pos.y = pParent->world_pos.y + pt.y;
		MoveDispXObject( (ANIMCELL *)pLink, FALSE );
	}
}


void AnimUpdate(ANIM *pAnim)	
{
	SHORT			frame;
	SEQUENCE		*pSeq;
	FRAME			*pFrame;
	DWORD			time;
	DWORD			dwAnimTime = gpGame->dwAnimTime;

	if (pAnim->flags & ANIM_FLAG_ACTIVE)	{
		if (pAnim->current_command>=DELAY_COMMAND)
		{
			if (pAnim->current_command==DELAY_COMMAND)	{
				AnimSetupCommand(pAnim, pAnim->next_command);
				if (pAnim->anim_sound != SND_NULL_SND_ID)
					sndPlay(pAnim->anim_sound);
			}
			else
				pAnim->current_command--;
		}
		else
		{
			// time to animate?
			frame = pAnim->current_frame;
			pSeq = pAnim->pSeq;
			pFrame = pAnim->pFrame;

			ASSERT(pSeq != NULL);
			ASSERT(pFrame != NULL);
			ASSERT(frame < pSeq->frames);

			// save off the world position
			pAnim->old_world_pos = pAnim->world_pos;
			pAnim->old_world_z = pAnim->world_z;

			if (pAnim->flags & ANIM_FLAG_SET_FACING)	{
				pAnim->flags &= ~ANIM_FLAG_SET_FACING;
				pAnim->facing = pAnim->next_facing;

				SHORT facing_index = INDEX_FACING(pAnim->facing, pSeq);
				pAnim->facing_index = facing_index;
				pFrame = pAnim->pFrame = pSeq->frame_list + (facing_index * pSeq->frames);
				pAnim->pSprite = &pAnim->spriteArray[pFrame[frame].sprite_index];
			}
			
			time = pFrame[frame].time;
			if (dwAnimTime >= pAnim->last_update + time)	{
				if (pAnim->callback )	{
					if (pAnim->callback_command == pAnim->current_command)	{
//						TRACE("%d %d %d\n",frame,pSeq->action_frame,pAnim->callback_frame);
						if (pAnim->callback_frame == frame)
							pAnim->callback(pAnim);
						else if (pSeq->action_frame == frame)
							pAnim->callback(pAnim);
					}
				}
				
				frame++;	// get next frame, and set up sequence and sprite
				pAnim->last_update = dwAnimTime;
//				pAnim->timefix = dwAnimTime;

				// now check to see if we've reached the end of a sequence
				// if we are at the end of a sequence, do the next_command
				if (frame >= pSeq->frames)	{
					if (pAnim->anim_sound != SND_NULL_SND_ID)
					{
						pAnim->anim_sound=SND_NULL_SND_ID;
						ExplodeCount--;
					}

					pAnim->facing = pAnim->next_facing;

					if (pAnim->next_command == LAST_FRAME_COMMAND)	{
						pAnim->last_frame_time += (short)gpGame->dwDeltaTime;
					}
					else	{
						pAnim->current_frame = 0;
						pAnim->last_frame_time = 0;
						AnimSetupCommand(pAnim, pAnim->next_command);
					}
				}
				else	{
					pAnim->current_frame = frame;
					pAnim->pSprite = &pAnim->spriteArray[pFrame[frame].sprite_index];
				}
			}
		}

		if (!pAnim->velocity)	{
			pAnim->dx = 0;
			pAnim->dy = 0;
		}
	}

	if (pAnim->pChild)
		AnimUpdate(pAnim->pChild);
}


///========================================================================
//	Function:		AnimDisplay()
//
//	Description:
//		Display the current frame of an anim (plus frames of any linked anims) 
//
//	Input:			pTheAnim		the animation to display
//
//	Ouput:			none
//
///========================================================================

void	AnimDisplay( ANIM* pTheAnim )
{
	ANIM*	pAnim;
	SPOINT	screenPos;
	SPRITE*	pSprite;

	pAnim = pTheAnim;

	while (pAnim)	{
		if (pAnim->flags & ANIM_FLAG_ACTIVE)	{
			// get the sprite
			pSprite	= pAnim->pSprite;
			pSprite->trans_table = pAnim->trans_table;

			// Determine if we need to calculate the screen position
			screenPos = pAnim->world_pos;
			if ( !(pAnim->flags & ANIM_FLAG_SCREEN_IS_WORLD))	{
				// calculate the screen position
				screenPos.x -= the_map.PixelBox.x;
				screenPos.y -= the_map.PixelBox.y;
			}

			pSprite->hotspot.x = pAnim->pFrame[pAnim->current_frame].primary_hotspot.x;
			pSprite->hotspot.y = pAnim->pFrame[pAnim->current_frame].primary_hotspot.y;

			// now display the sprite
			DisplaySpriteClipped( pSprite, screenPos.x, screenPos.y );
		}

		// look for a link
		pAnim = pAnim->pChild;
	}
}


void	AnimTransTable( ANIM* pAnim, BYTE *ptable )
{
	pAnim->trans_table = ptable;
}


///========================================================================
//	Function:		AnimCellDisplay()
//
//	Description:
//		Update the actions of an Army Vehicle.
//
//	Input:			pTheAnim		the animation to display
//
//	Ouput:			none
//
///========================================================================

void AnimCellDisplay( ANIMCELL* pCell )
{
	ANIM*	pAnim;
	SPOINT	screenPos;
	SPRITE*	pSprite;
	BOOL	anim_flag = FALSE;

	ASSERT(pCell);

	pAnim = (ANIM *) pCell;

	if (!(pAnim->flags & ANIM_FLAG_CELL))	{
		anim_flag = TRUE;
	}

	while (pAnim)	{
		if (!(pAnim->flags & ANIM_FLAG_INVISIBLE) && (pAnim->flags & ANIM_FLAG_ACTIVE))	{

			// get the sprite
			pSprite	= pAnim->pSprite;
			pSprite->trans_table = pAnim->trans_table;

			// calculate the screen position
			screenPos = pAnim->world_pos;
			screenPos.x -= (SHORT)the_map.PixelBox.x;
			screenPos.y -= (SHORT)the_map.PixelBox.y;

			if (anim_flag)	{
				pSprite->hotspot.x = pAnim->pFrame[pAnim->current_frame].primary_hotspot.x;
				pSprite->hotspot.y = pAnim->pFrame[pAnim->current_frame].primary_hotspot.y;
			}

			// now display the sprite
			DisplaySpriteClipped( pSprite, screenPos.x, screenPos.y - pAnim->world_z );

			// DEBUG: so we can see where the hotspot is
			if (hotspots)
				DrawDot( &pAnim->world_pos, RGB_GREEN );
		}

		// look for a link
		if (anim_flag)
			pAnim = pAnim->pChild;
		else
			pAnim = NULL;
	}
}


///========================================================================
//	Function:		AnimDelete()
//
//	Description:
//		Delete an animation.
//
//	Input:			pTheAnim		the animation to free
//
//	Ouput:			none
//
///========================================================================

void	AnimDelete( ANIM* pAnim )
{
	AnimInactivate(pAnim, INACTIVATE_LINKS);
	DestroyDispXObject( (ANIMCELL *)pAnim );
}


#if 0
static short xoff[32] = {
	23-22, 22-29, 22-37, 17-42, 13-46, 8-49, 6-49, 0-49, 
	-3-46, 2-50, 5-51, 10-51, 14-49, 17-45, 21-40, 23-33,
	25-24, 44-32, 60-40, 73-46, 86-51, 95-54, 99-54, 99-52,
	98-50, 100-52, 99-53, 95-53, 86-50, 74-45, 60-39, 43-31 
	};
static short yoff[] = {
	-1-34, 0-38, 2-39, 5-39, 10-38, 14-35, 14-30, 19-25,
	23-19, 37-26, 55-32, 67-37, 77-41, 85-43, 88-44, 91-43,
	90-43, 89-43, 88-44, 84-43, 76-41, 65-36, 54-31, 40-25,
	23-17, 21-23, 19-28, 17-33, 14-37, 9-38, 6-39, 2-38 
	};

BOOL
GetNextFrontPos(ANIM* pAnim, SPOINT *ppos)	{
	DWORD	dwDeltaTime = gpGame->dwDeltaTime;
	SHORT	direction;
	float dx,dy;

	direction = pAnim->facing / 8;

	if (pAnim->velocity && dwDeltaTime)	{
		double pixels = ((double) (pAnim->velocity * dwDeltaTime)) / 3600;

		dx = (float) (pAnim->dx + cos_table[direction] * pixels);
		ppos->x = pAnim->world_pos.x + (SHORT) dx;
		ppos->x += xoff[direction];

		dy = (float) (pAnim->dy + sin_table[direction] * pixels);
		ppos->y = pAnim->world_pos.y + (SHORT) dy;
		ppos->y += yoff[direction];

		return TRUE;
	}
	else
		return FALSE;
}


void GetFrontPos(ANIM* pAnim, SPOINT *ppos)	{
	SHORT	direction;

	direction = pAnim->facing;

	ppos->x = pAnim->world_pos.x + (short)(cos_table[direction] * 8);
	ppos->x += xoff[direction];

	ppos->y = pAnim->world_pos.y + (short)(sin_table[direction] * 8);
	ppos->y += yoff[direction];
}
#endif

///========================================================================
//	Function:		AnimWorldBoundary()
//
//	Description:
//		make sure the world position for an anim is within the world boundaries.
//
//	Input:			pTheAnim		anim whose world pos we're trying to restrict
//
//	Ouput:			none
//
///========================================================================

void	AnimWorldBoundary( ANIM* pTheAnim )
{
	ANIM*	pAnim;
	SHORT	xBoundary;
	SHORT	yBoundary;
	BOOL	stopIt = FALSE;

	// put the anim into a local register
	pAnim = pTheAnim;

	// get the boundary conditions
	xBoundary = (SHORT)(the_map.FullPixelBox.cx - ANIM_DEFAULT_BOUNDARY);
	yBoundary = (SHORT)(the_map.FullPixelBox.cy - ANIM_DEFAULT_BOUNDARY);

	// make sure the anim is within the world
	if( pAnim->pSprite )
	{
		int urcx, urcy;

		urcx = pAnim->world_pos.x - pAnim->pSprite->hotspot.x;
		urcy = pAnim->world_pos.y - pAnim->pSprite->hotspot.y;
		if( urcx < ANIM_DEFAULT_BOUNDARY )
		{
			pAnim->world_pos.x = 0;
			stopIt = TRUE;
		}
		else
		if( urcx + pAnim->pSprite->srect.right > xBoundary )		
		{
			pAnim->world_pos.x = xBoundary - (short)pAnim->pSprite->srect.right;
			stopIt = TRUE;
		}
		if( urcy < ANIM_DEFAULT_BOUNDARY )
		{
			pAnim->world_pos.y = 0;
			stopIt = TRUE;
		}
		else
		if( urcy + (short)pAnim->pSprite->srect.bottom > yBoundary )		
		{
			pAnim->world_pos.y = yBoundary - (short)pAnim->pSprite->srect.bottom;
			stopIt = TRUE;
		}
	}
	else
	{
		if ( pAnim->world_pos.x < ANIM_DEFAULT_BOUNDARY )
		{
			pAnim->world_pos.x = ANIM_DEFAULT_BOUNDARY; // + pAnim->pSprite->hotspot.x;
			stopIt = TRUE;
		}
		if ( pAnim->world_pos.y < ANIM_DEFAULT_BOUNDARY )
		{
			pAnim->world_pos.y = ANIM_DEFAULT_BOUNDARY; // + pAnim->pSprite->hotspot.y;
			stopIt = TRUE;
		}
		if ( pAnim->world_pos.x > xBoundary )
		{
			pAnim->world_pos.x = xBoundary; // - pAnim->pSprite->hotspot.x;
			stopIt = TRUE;
		}
		if ( pAnim->world_pos.y > yBoundary )
		{
			pAnim->world_pos.y = yBoundary; // - pAnim->pSprite->hotspot.y;
			stopIt = TRUE;
		}
	}

	if( stopIt )
	{
		if( pAnim->flags & ANIM_FLAG_CELL )
		{
			pAnim->flags &= ~ANIM_FLAG_ACTIVE;
		}
		else
			if( pAnim->flags & ANIM_FLAG_ACTIVE )
				AnimForceCommand(pAnim, INACTIVATE_COMMAND, SAME_FACING);
	}
}

///========================================================================
//	Function:		AnimWorldToScreen()
//
//	Description:
//		provide the screen coordinate equivalent for a world position. The screen
//		position is -1,-1 if the world position is not on the screen.
//
//	Input:			pTheAnim		anim whose world pos we're trying to restrict
//
//	Ouput:			none
//
///========================================================================

void	AnimWorldToScreen( SPOINT* pWorld, SPOINT* pScreen )
{
	// calculate the screen position, don't forget to add in the offset at the end
	pScreen->x = pWorld->x - the_map.PixelBox.x;
	pScreen->y = pWorld->y - the_map.PixelBox.y;

	ValidateSPoint(pScreen, &the_map.FullPixelRect);
}


///========================================================================
//	Function:		AnimSprite()
//
//	Description:
//		Get the sprite for anim given the command, facing and frame #
//
//	examples:
//	AnimSprite(pAnim, SAME_COMMAND, SAME_FACING, SAME_FRAME);	// use all current anim info
//	AnimSprite(pAnim, command, facing, LAST_FRAME);				// last frame of sequence
//
//	Input:			pAnim
//					command
//					facing
//					frame
//
//	Ouput:			none
//
///========================================================================

SPRITE* AnimSprite(ANIM *pAnim, int command, SHORT facing, SHORT frame)	{
	SPRITE *pSprite = NULL;
	Sprite	*spriteArray;
	SEQUENCE *pSeq = NULL;
	COMMAND_LIST *pCommandList;
	COMMAND	*pCommand;
	FRAME	*pFrame;
	SHORT	commands,
			i;

	if (pAnim->flags & ANIM_FLAG_ACTIVE)	{
		if (command == INACTIVATE_COMMAND)
			return NULL;

		if (command == SAME_COMMAND)
			command = pAnim->current_command;

		if (facing == SAME_FACING)
			facing = pAnim->facing;

		pCommandList = pAnim->pCommandList;
		pCommand = pCommandList->command_array;
		commands = pCommandList->commands;

		// search command list for the appropriate command
		for (i=0; i<commands; i++)	{
			if (pCommand[i].command_now == command)	{
				pSeq = pCommand[i].seq;
				break;
			}
		}
		if (i >= commands || !pSeq)
			pSeq = default_command_array[0].seq;

		spriteArray = pSeq->spriteArray;

		switch (facing)	{
			case LAST_FRAME:
				frame = pSeq->frames - 1;
			case SAME_FRAME:
				frame = pAnim->current_frame;
			case NEXT_FRAME:
				frame = pAnim->current_frame++;
//				if (frame >= pSeq->frames)
		}

		SHORT facing_index = INDEX_FACING(facing, pSeq);
		pFrame = pSeq->frame_list + (facing_index * pSeq->frames);
		pSprite = &spriteArray[pFrame[frame].sprite_index];
	}

	return pSprite;
}


void ValidateCommandList(COMMAND_LIST *pCommandList)	{
	COMMAND	*pCommand;
	SHORT	commands, i;
	SEQUENCE *pSeq;

	pCommand = pCommandList->command_array;
	commands = pCommandList->commands;

	// search command list
	for (i=0; i<commands; i++)	{
		pSeq = pCommand[i].seq;
		if( pSeq )
		{
			if (pSeq->directions > 32)	
			{
				Error("Command list smashed, command %d\n", i);
				ASSERT(0);
			}
//			ASSERT(pSeq->directions <= 32);
		}
	}
}

void ValidateAnim(ANIM *pAnim)	{
	COMMAND_LIST *pCommandList;

	pCommandList = pAnim->pCommandList;
	ValidateCommandList(pCommandList);
}


/*
///========================================================================
//	Function:		getanimsprite()
//
//	Description:
//		Given an anim, returns a pointer to a particular sprite from it.
//		Should only be used with dummy anims, as it overwrites some values
//
//	Input:			pAnim		the ANIM
//					command		which command
//					facing		which facing
//
//	Ouput:			pointer to the appropriate sprite structure
//
///========================================================================

SPRITE *getanimsprite(ANIM *pAnim, short command, int facing)
{

	SEQUENCE *pSeq;
	COMMAND_LIST *pCommandList;
	COMMAND	*pCommand;
	SHORT	commands, i;


	pCommandList = pAnim->pCommandList;
	pCommand = pCommandList->command_array;
	commands = pCommandList->commands;

	pAnim->facing=facing;

	// search command list for the appropriate command
	for (i=0; i<commands; i++)	{
		if (pCommand[i].command_now == command)	{
			pAnim->current_command = command;
			pSeq = pCommand[i].seq;
			pAnim->next_command = pCommand[i].command_next;
			break;
		}
	}
	if (i >= commands)	{
		TRACE( "ERROR while trying to get an anim sprite: anim command %d not found. [%s,%d]\n", command, __FILE__, __LINE__ );
		pAnim->current_command = pCommand[0].command_now;
		pSeq = pCommand[0].seq;
		pAnim->next_command = pCommand[0].command_next;
	}

	// keep the anim engine from crashing by giving it a legit target
	if (!pSeq)	{
		pSeq = default_command_array[0].seq;
		TRACE("ERROR: Forced to set a sequence pointer to invisible sequence in getanimsprite\n");
	}

	pAnim->pSeq = pSeq;
	pAnim->spriteArray = pSeq->spriteArray;

	SHORT facing_index = INDEX_FACING(pAnim->facing, pSeq);
	pAnim->facing_index = facing_index;
	pAnim->pFrame = pSeq->frame_list + (facing_index * pSeq->frames);
	pAnim->pSprite = &pAnim->spriteArray[pAnim->pFrame[pAnim->current_frame].sprite_index];

	return pAnim->pSprite;
}
*/

///========================================================================
//									EOF
///========================================================================
