//========================================================================
//	FILE:			$Workfile: trooperP.h $
//
//	DESCRIPTION:	Army Troop processing.
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		Tuesday, June 13, 1997
//
//	REVISION:		$Header: /ArmyMen/src/trooperP.h 67    4/14/98 10:38a Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unauthorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/trooperP.h $
//  
//  67    4/14/98 10:38a Bwilcox
//  switch playcycle to elapsed time printout,
//  optimize trooper no routing when fail on victim
//  
//  66    4/12/98 3:20p Bwilcox
//  stuck guys can still shoot
//  
//  65    4/08/98 11:29p Dmaynard
//  Store lastSentPosition for each Trooper
//  
//  63    4/02/98 4:27p Phu
//  change pSeen to array of unsigned short
//  
//  62    4/02/98 2:46p Bwilcox
//  cleanup
//  
//  61    4/01/98 12:00p Bwilcox
//  remove defunct variables. Make prone damage protection a true 12.5 of
//  original damage.
//  
//  60    3/19/98 1:20p Bwilcox
//  passing firepose for troopers across net
//  
//  59    3/16/98 12:08p Bwilcox
//  added pose data to trooperstruct
//  
//  58    3/16/98 11:06a Bwilcox
//  
//  57    3/12/98 2:43p Bwilcox
//  
//  56    3/06/98 11:51a Bwilcox
//  deleted some trooperformation stuff, added another fight status
//  (backing up)
//  
//  55    2/20/98 2:40p Bwilcox
//  imrpvoing evade
//  
//  54    2/18/98 12:22p Bwilcox
//  tadbeing hit now called. removed useless formation code. removed attack
//  wander code
//  
//  53    2/15/98 12:45p Bwilcox
//  
//  52    2/15/98 12:42p Bwilcox
//  added old fire data
//  
//  51    2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  50    2/05/98 9:24a Bwilcox
//  removed trooper deploying mode
//  
//  49    2/04/98 10:14a Bwilcox
//  removal of dead formation stuff
//  
//  48    2/04/98 9:25a Bwilcox
//  tracking override status for display
//  
//  47    1/29/98 12:33p Bwilcox
//  moved invis from trooper to unit
//  
//  46    1/28/98 8:59p Bwilcox
//  
//  45    1/28/98 11:47a Bwilcox
//  troopers who stop for collision remain stopped for 10 frames
//  
//  44    1/27/98 8:27a Bwilcox
//  MODIFIED EVADE OF VECHILE
//  
//  43    1/23/98 11:33a Bwilcox
//  removed _DEBUG from some code that needs to exist in final-release.
//  added wasAt and whenAt for debugging
//  
//  42    1/06/98 1:55p Bwilcox
//  fixed trooper clearmem problem
//  
//  41    1/06/98 12:36p Bwilcox
//  added PropogateTrafficable fanout code in item.
//  fixed troopercover bug when enemy dies
//  
//  
//  $Nokeywords:$
///========================================================================

#ifndef __TROOPER_P_H   
#define __TROOPER_P_H   

#include "newdoor.h"
       
typedef enum
{
    NO_OVERRIDE = 0,
    AVOID_VEHICLE,
    WAIT_FOR_TROOPER,
    STILL_WAIT_FOR_TROOPER,
    WAIT_IN_POSE
        
} OVERRIDE;

typedef enum
{
    TROOPER_INACTIVE,				// trooper not on the map
    TROOPER_ALIVE,					// trooper on map
    TROOPER_DYING					// animation in progress to die
} TROOPER_STATE;

typedef enum
{
    NO_VICTIM,
    SEEKING_COVER,
    FIXING_SIGHT,
    FIRING,
    CHASING,
    OUT_OF_RADIUS,
    BACKUP
} FIGHT_STATUS;

// TROOP structure
struct  TROOPERSTRUCT
{
    struct ITEM	common;			// common components of all objects

    // general trooper data
    TROOPER_STATE 	mode;			// trooper status 
    FIGHT_STATUS	fstatus;			// what doing in a fight
    ACTION			pendingAction;		// next avatar high-level action
    int				pendingDirection;	// direction for next avatar motion
    ACTION			action;				// what it did do this frame
    OVERRIDE		override;		// what affects this guys intent
    ACTION			poseDuringRound;
    ACTION		    currentPose;		

    ACTION			pendingPose;
    ACTION			pose;
    ACTION			oldPose;


	UNIT*			pUnit;			// unit this trooper belongs to

    int				direction;			// what it did do this frame
    ACTION			oldAction;			// what it did do last frame
    int				oldDirection;		// what it did do last frame

    // route planner data
    ROUTEDATA		routeData;		// needed to allow unit to go places
    IPOINT			blockingTile;	// a tile it is occupying
    SPOINT			waygoal;		// a destination
        
    // avatar data
    AVATAR*			pAvatar;			// body for the trooper
        
    // tmp cache data
    IPOINT			landsOnTile;		// what tile will I land on 
    SPOINT			lands;				// where will I land
    IPOINT 			fSpot;	
    IPOINT 			fTile;	

	WEAPON			weapon;

    // firing esthetics
    int				roundsBeforeStall;
    int				roundsDuringStall;

    // pose esthetics
    int				framesInPose;

    // WAS NEAR AN AIRSTRIKE
    int				nearAirstrike;	

	UID				victimUID;

    SPOINT			wasAt;		// where was he before
    long			whenAt;		// when did he get there

    int				stopDelay;	// when collision stop occurs, dont move 
                                // until some time lapses

	unsigned char	fireHeight;

    unsigned char 	oldFireHeight;
    unsigned char	oldFireDirection;
    short			oldFireDistance;
	ACTION			oldPoseDuringRound;

    long 			msgStamp;		// comm id of message set
    ACTION			fireAction;		// did we see a fire action?
	SPOINT			lastSentPosition;

	char			couldShoot;			// were we interested in shooting
	int				shootFace;			// which way

	long			delayVictim;
	UID				delayUID;
};

#define MAX_AMMO	62000				// lots of shots

extern USHORT* pSeen;					// not seen yet buffer

#endif
