/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: avatar.h $
//
//	DESCRIPTION:	Public interface for trooper avatar animation
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Thursday, June 26, 1997
//
//	REVISION:		$Header: /ArmyMen/src/avatar.h 47    4/10/98 11:45a Nrobinso $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/avatar.h $
//  
//  47    4/10/98 11:45a Nrobinso
//  add a fire now option for sarge
//  
//  45    3/27/98 7:23p Nrobinso
//  remove currentpose (confusing)
//  
//  44    3/27/98 11:36a Phu
//  avatarinair
//  
//  43    3/26/98 9:35p Phu
//  strategy items: prone, roll & dive protection
//  
//  42    3/18/98 5:24p Nrobinso
//  remove avatar_sweep
//  
//  41    3/16/98 6:33p Nrobinso
//  remove stationary avatar commands
//  
//  40    3/16/98 12:07p Nrobinso
//  remove avatar stationary and pass a pose into avatar calls
//  
//  39    3/03/98 9:40p Nrobinso
//  added avatar_talk
//  
//  38    3/01/98 8:27p Nrobinso
//  
//  37    2/04/98 9:25a Bwilcox
//  fixing actions text list to match header file
//  
//  36    1/30/98 2:14p Nrobinso
//  remove AVATAR_THROW
//  
//  35    1/28/98 4:27p Nrobinso
//  add AVATAR_SWEEP_STATIONARY
//  
//  34    1/07/98 5:12p Nrobinso
//  add AvatarSetFacing
//  
//  33    1/07/98 3:20p Nrobinso
//  add AvatarCurrentPose; changed AvatarPose to take only the avatar
//  pointer; AvatarPoseChange also takes an action
//  
//  32    12/23/97 4:09p Bwilcox
//  avatarwouldmoveto returns spoint now
//  
//  31    12/23/97 3:49p Bwilcox
//  AVATAR_LOCATION beocmes AvatarPosition
//  
//  30    12/18/97 6:39p Bwilcox
//  changed AvatarSetLocation to AvatarSetPosition to change arg to spoint
//  
//  29    12/18/97 6:30p Bwilcox
//  removing redundant location variable in avatar
//  
//  28    12/15/97 7:59a Nrobinso
//  replace lay with roll
//  
//  27    12/11/97 1:48p Nrobinso
//  remove fire_now
//  
//  26    12/09/97 12:12p Phu
//  
//  25    12/08/97 2:06p Nrobinso
//  remove hit; move fire_stationary
//  
//  24    12/07/97 7:27p Nrobinso
//  recognize AVATAR_FIRE_STATIONARY
//  
//  23    12/02/97 8:02p Nrobinso
//  move explode command; add a settype
//  
//  22    11/24/97 8:35p Phu
//  Add Z component to projectile firing
//  
//  21    11/20/97 11:29a Nrobinso
//  turn on walk backwards; decrease angle of sarge bounce off objects
//  
//  20    11/17/97 11:05a Nrobinso
//  projectile hit code added
//  
//  19    11/11/97 10:49a Nrobinso
//  patch to get sarge to fire immediately
//  
//  18    11/07/97 4:05p Nrobinso
//  make avatarposechange a global
//  
//  17    11/04/97 10:44a Nrobinso
//  remove turns
//  
//  16    10/30/97 10:18a Nrobinso
//  remove unused avatar commands; add turns and raise gun commands
//  
//  14    8/18/97 4:51p Nrobinso
//  add die range
//  
//  13    8/17/97 7:17p Nrobinso
//  move interrupt commands together in a block
//  
//  12    8/14/97 4:39p Nrobinso
//  add AvatarActionDBNaame (a debugging function)
//  
//  11    8/14/97 3:03p Nrobinso
//  add avatr visibility macros
//  
//  10    8/11/97 6:55p Nrobinso
//  added AvatarPose; cleaned up commands
//  
//  9     8/11/97 10:25a Nrobinso
//  add dive and dig in commands
//  
//  8     7/27/97 11:48a Nrobinso
//  add AVATAR_FACING macro
//  
//  7     7/22/97 10:08p Nrobinso
//  add digin commands
//  
//  6     7/21/97 12:59p Nrobinso
//  add poses
//  
//  5     7/18/97 11:17a Nrobinso
//  add a THROW commnd for the use of Sarge
//  
//  4     7/17/97 10:43p Nrobinso
//  removr FINISH_DEPLOY and FINISH_PICKUP
//  
//  3     7/08/97 8:51a Nrobinso
//  AvatarWouldMovTo takes a new parameter --BOOL whole_cycle; if false,
//  only the movment for the next frame is calculated.
//  
//  2     7/03/97 5:34p Nrobinso
//  make avatar commands all begin with AVATAR_
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __AVATAR_H__
#define __AVATAR_H__

// Includes
#include "avatar-p.h"  // private datastructures
       

SPOINT AvatarPosition(AVATAR* pAvatar);

#define AVATAR_FACING(x) ((x)->facing)
#define AvatarDirectionOverride(a,b) (AvatarFacingOverride(a,b))

#define AVATAR_INVISIBLE(avatar) ((avatar)->pAnimation->flags |= ANIM_FLAG_INVISIBLE)
#define AVATAR_VISIBLE(avatar) ((avatar)->pAnimation->flags &= ~ANIM_FLAG_INVISIBLE)

// Data Types
typedef enum {
	// movement commands
	AVATAR_RUN = 0,
    AVATAR_WALK, 
	AVATAR_WALK_BACKWARDS,
	AVATAR_SHUFFLE,

	// stationary commands
	AVATAR_READY_FIRE,			// get ready to fire command
	AVATAR_FIRE,				// firing command (5)
	AVATAR_FIRE_STATIONARY,
	AVATAR_FIRE_NOW,

	AVATAR_ROLL_LEFT,
	AVATAR_ROLL_RIGHT,
	AVATAR_DIVE,

	// change pose commands
	AVATAR_KNEEL,				// 10
	AVATAR_STAND,
	AVATAR_PRONE,

	AVATAR_TALK,

	// interrupt commands
	AVATAR_DIE_MELT, 
	AVATAR_DIE_SHOT,			// 15
	AVATAR_DIE_SQUASH,
	AVATAR_INVISIBLE,
	AVATAR_STOP_IMMEDIATELY,
	AVATAR_DIE_EXPLODE, 
	// end interrupt commands

	// deploy commands
	AVATAR_ACTIONS,				// 20
	AVATAR_INACTIVATE				// special command not subject to any state change info

} ACTION;

#define AVATAR_INTERRUPT_FIRST AVATAR_DIE_MELT
#define AVATAR_INTERRUPT_LAST AVATAR_DIE_EXPLODE
#define AVATAR_DIE_FIRST AVATAR_DIE_MELT
#define AVATAR_DIE_LAST AVATAR_DIE_SQUASH

#define AVATAR_ERROR -1
#define AVATAR_READYING 0
#define AVATAR_PERFORMING 1

// Prototypes
AVATAR* AvatarCreate(UID id);
void AvatarDestroy(AVATAR* avatar);
void  AvatarSetType(AVATAR* avatar, int eType);
BOOL AvatarNearlyReadyTo(ACTION action, int facing, AVATAR* avatar);
BOOL AvatarLastCompleted(ACTION action, AVATAR* avatar);
ACTION AvatarPoseChange(ACTION action, AVATAR* avatar);
ACTION AvatarPose(AVATAR* avatar);
SPOINT AvatarWouldMoveTo(ACTION action, ACTION pose, int facing, BOOL whole_cycle, AVATAR* avatar);
int AvatarPerform(ACTION action, ACTION pose, int facing, BOOL doAction, AVATAR* avatar);
void  AvatarSetPosition(SPOINT location, AVATAR* avatar);
void  AvatarSetFacing(int facing, AVATAR* avatar);
BOOL AvatarHitByMissile(ACTION pose, SHORT height);
BOOL AvatarInAir( AVATAR *pAvatar );
int	AvatarHeight( ACTION pose );


#if _DEBUG
char *AvatarActionDBName(ACTION action);
#endif

#endif