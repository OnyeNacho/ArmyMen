/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: air.cpp $
//
//	DESCRIPTION:	Code for handling air strikes and air support
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Tuesday, October 28, 1997
//
//	REVISION:		$Header: /ArmyMen/src/air.cpp 60    4/02/98 8:52p Phu $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/air.cpp $
//  
//  60    4/02/98 8:52p Phu
//  fix to paratroopers ala brooce
//  
//  59    4/02/98 1:35p Phu
//  
//  58    4/01/98 12:40p Bwilcox
//  use islocalarmy instead of checking  isremote
//  
//  57    3/31/98 11:51a Bwilcox
//  stratmap overlay removal
//  
//  56    3/30/98 1:40p Dmaynard
//  air strikes wern't showing up on remote machines.
//  
//  55    3/28/98 7:14a Bwilcox
//  multiplayer-mode easter egg. Enjoy. Best Regards, The AI Guru
//  
//  54    3/24/98 2:29p Nrobinso
//  put voice messages with text thru MsgBroadcastWithText
//  
//  53    3/24/98 1:35p Nrobinso
//  go to voice over intead of text for aagun and blocked paratroopers
//  
//  52    3/23/98 6:04p Bwilcox
//  troopers duck for any air operation when plane starts
//  
//  51    3/22/98 3:16p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  50    3/16/98 12:09p Bwilcox
//  airdrop will not launch w/o units to do it
//  
//  49    3/15/98 7:11p Nrobinso
//  play sfx for plane
//  
//  48    3/13/98 12:37p Bwilcox
//  lower freq for dove droppings
//  
//  47    3/12/98 7:06p Bwilcox
//  
//  46    3/12/98 5:37p Bwilcox
//  
//  45    3/12/98 5:22p Bwilcox
//  air fixes
//  
//  44    3/12/98 3:26p Bwilcox
//  troopers go prone during an airstrike,
//  troopers fire mortar and grenade higher to clear a rock
//  
//  43    3/12/98 12:06p Bwilcox
//  
//  42    3/10/98 9:55a Bwilcox
//  air charges for remotes also
//  
//  41    3/09/98 2:43p Phu
//  fix free bug in air
//  
//  40    3/09/98 1:57p Bwilcox
//  
//  39    3/09/98 1:46p Bwilcox
//  FIXING AIR DISPLAY MULTIPLAYER
//  
//  38    3/09/98 12:45p Bwilcox
//  stop air echo message
//  
//  37    98-03-09 12:20 Dmaynard
//  fix bug where 1st guy to launch air gets all futture ones
//  
//  36    3/09/98 12:20p Phu
//  air strike explosion distribution
//  
//  35    3/06/98 11:48a Bwilcox
//  
//  34    3/02/98 12:14p Bwilcox
//  fixinig color of airdrop units and aistrike explosions
//  
//  33    3/01/98 7:57p Bwilcox
//  random death of troopers on para landing
//  
//  32    3/01/98 12:33p Bwilcox
//  alternate air support
//  
//  31    2/27/98 1:15p Bwilcox
//  cleaning up the air, supporting script airdrops for foes,e tc
//  
//  30    2/25/98 10:13p Phu
//  ODF load flash, bodyparts, misc
//  
//  29    2/25/98 6:28p Phu
//  rename wobject files
//  
//  28    2/20/98 1:15p Nrobinso
//  fix up sounds
//  
//  27    2/18/98 2:24p Bwilcox
//  stop air recon from using allah mode to do its dirty work
//  
//  26    2/17/98 4:28p Phu
//  extend recon time
//  
//  25    2/16/98 5:02p Phu
//  make airstrike register who did them
//  
//  24    2/03/98 12:53p Nrobinso
//  aa guns no longer affect recon
//  
//  23    1/26/98 2:21p Phu
//  get rid of zeromemory for undefined sprite
//  
//  22    1/26/98 11:27a Phu
//  parachutists
//  
//  21    1/23/98 5:43p Nrobinso
//  comment out 2nd air support sprite
//  
//  20    1/23/98 12:06p Phu
//  new airsupport graphics
//  
//  19    1/22/98 6:38p Nrobinso
//  use SetPath
//  
//  18    1/20/98 12:41p Bwilcox
//  removed calls to myuntrafficable ujit
//  
//  17    1/14/98 8:50a Bwilcox
//  removed allah=0 set in initair
//  
//  16    1/08/98 7:35p Phu
//  paratroopers
//  
//  15    1/08/98 4:19p Phu
//  air support items/paratrooper initialization
//  
//  14    1/08/98 1:52p Phu
//  mp airsupport
//  
//  13    1/07/98 7:43p Phu
//  
//  1     10/28/97 2:49a Awerner
//
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//  Includes
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "army.h"
#include "air.h"
#include "sprite.h"
#include "gameflow.h"
#include "miscfile.h"
#include "explosions.h"
#include "sarge.h"
#include "item.h"
#include "map.h"
#include "stratmap.h"
#include "aiaccess.h"
#include "unit.h"
#include "ui.h"
#include "sargemsg.h"
#include "fileio.h"
#include "wobject.h"
#include "sounds.h"
#include "trooper.h"
#include "comm.h"
#include "aibtank.h"
#include "audio.h"

/////////////////////////////////////////////////////////////////////////////
//  Global Variables
/////////////////////////////////////////////////////////////////////////////

// q of pending airsupport missions   
struct AIRQ{
    SPOINT where;
    AIRSUPPORTTYPE what;
    int    who;
};

#define MAX_AIR 30
AIRQ pendingAir[MAX_AIR+1]; // waiting list of air
static int aircount = 0;  // how many in list
static void ProcessAir(AIRSUPPORTTYPE whichtype, SPOINT where,int eArmy);
SPRITE *airSupportSprite1;
SPRITE *airSupportSprite2;
int airSupportFrame = 0;    // draws the airplane when non-zero
int myAirSupportFrame = 0;  // times the air event to make it happen
int AirSupportWidth = 0;

// the current running air data
AIRSUPPORTTYPE airSupportType; 
SPOINT airSupportPos;
int airSupportArmy;
BOOL missionInProgress = 0;
BOOL alternateAir = 0;

int	ReconTimer = 0;
int ReconTime = 20000;
int    airxstart = -278;
int    airystart = 320;
double airmult = 0.43;
int    airtime = 2500;

SPOINT paratrooperPos;
int    paratrooperFrame = 0;   // draws the paratrooper drop anim if non-zero
int    paratrooperTime = 3000; // when to actually put units on the ground
int    myParatrooperFrame = 0; // times when to put unit on the ground
int    paratrooperWidth = 200;
int    paratrooperHeight = 300;
int    paratrooperStartHeight = 114;

COMMAND_NUMBERS airStrikeCommands[]=
{
	EXPLOSION_SMOKE_M_COMMAND,
	EXPLOSION_COMBUSTION_S_COMMAND,
	EXPLOSION_COMBUSTION_L_COMMAND,
	EXPLOSION_FLASH_COMBUSTION_S_COMMAND,
	EXPLOSION_FLASH_COMBUSTION_L_COMMAND,
	EXPLOSION_FLASH_DIRT_SMOKE_S_COMMAND,
	EXPLOSION_FLASH_DIRT_SMOKE_L_COMMAND,
};

#define NUMAIRSTRIKEEXPLOSIONS (sizeof(airStrikeCommands)/sizeof(COMMAND_NUMBERS))

/////////////////////////////////////////////////////////////////////////////
//  Local #defines
/////////////////////////////////////////////////////////////////////////////

#define AIRSUPPORT_FRAMES 128
#define AIRSTRIKE_RADIUS 150
#define AIRSTRIKE_NUMEXPLOSIONS 16   // used to be 5
#define AIRSTRIKE_MAXDAMAGE 20

static void AirMakeVisible(int viewArmy,SPOINT ul, SPOINT lr);

#define AIRSUPPORT_VISIBILITY_RADIUS 480

/////////////////////////////////////////////////////////////////////////////
//  Functions
/////////////////////////////////////////////////////////////////////////////

static void DoNextAir() // do the next in the q
{
    int i;

    if (!aircount) return; // there arent any

    // do 1st in q
    ProcessAir(pendingAir[1].what,pendingAir[1].where,(int)pendingAir[1].who);

    // move others down 
    for (i = 2; i <= aircount; ++i)
    {
        pendingAir[i-1].what =  pendingAir[i].what;
        pendingAir[i-1].where = pendingAir[i].where;
        pendingAir[i-1].who =  pendingAir[i].who;
    }

    --aircount;
}

static void ZeroAirValues()
{
	airSupportFrame=0;
    missionInProgress = 0;
	myAirSupportFrame = 0;
	paratrooperFrame = 0;
	myParatrooperFrame = 0;
    aircount = 0;
	ReconTimer = 0;
}

void InitAirSupport(void)
{

	char dir[80];
    ZeroAirValues();
	if (_LOAD_FROM_DATAFILE)
		sprintf( dir, "%s/Misc", the_map.terrain_name );
	else
		sprintf( dir, "LoadObjects/%s/Misc", the_map.terrain_name );

	SetPath( dir );

//	airSupportSprite1 = (SPRITE *)malloc(sizeof(SPRITE));
//	ZeroMemory( airSupportSprite1, sizeof(SPRITE) );
//	airSupportSprite2 = (SPRITE *)malloc(sizeof(SPRITE));
//	ZeroMemory( airSupportSprite2, sizeof(SPRITE) );
	AcquireWobjectSpriteAsShadow( airSupportSprite1,CAT_AIRSUPPORT, 1, 2, "airs", PSHADE_TABLE );
	AcquireWobjectSpriteAsShadow( airSupportSprite2,CAT_AIRSUPPORT, 2, 2, "airs", PSHADE_TABLE );

//	LoadShadowAsSprite( airSupportSprite1, "airs_001_2.sha", PSHADE_TABLE );
//	LoadShadowAsSprite( airSupportSprite2, "airs_002_2.sha", PSHADE_TABLE );
	airSupportSprite1->hotspot.x = 0;
	airSupportSprite1->hotspot.y = 0;
	airSupportSprite2->hotspot.x = 0;
	airSupportSprite2->hotspot.y = 0;

	AirSupportWidth = 640 + 2 * airSupportSprite1->srect.right;
}


void KillAirSupport(void)
{
	if( airSupportSprite1 )
		ReleaseWobjectSprite( airSupportSprite1 );
	if( airSupportSprite2 )
		ReleaseWobjectSprite( airSupportSprite2 );
    ZeroAirValues();
}


void RequestParatrooperAnimation( SPOINT pos )
{
	if( paratrooperFrame > 0 ) // already one in progress
		return;

	RECT irect;
	RECT paratrooperRect;

	paratrooperRect.left = pos.x - (paratrooperWidth >> 1);
	paratrooperRect.right = paratrooperRect.left + paratrooperWidth;
	paratrooperRect.top = pos.y - paratrooperHeight;
	paratrooperRect.bottom = pos.y;

	if( RectIntersect( &(the_map.screenrect), &paratrooperRect, &irect ) )
	{
		LoadParachuteGraphics();
		paratrooperPos = pos;
		paratrooperFrame = 1;
	}
}

static void DropMyParachutists( void )
{
	UNIT *pUnit;

	myParatrooperFrame = 0;

	pUnit=ParatrooperNextInHQ( (ARMY_TYPE)airSupportArmy );
	if (!pUnit)
	{
		TRACE("ERROR: no paratroopers left in HQ when we still have airdrops\n");
		return;
	}					

	UnitDeploy(pUnit, &airSupportPos, 0,DEFENDFIRE);

    // random damage to troopers on landing in chance in 25 per trooper
    TROOPER* pTrooper;
    int i;
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
		if ( (rand() % 25) == 13)
			 TrooperAcceptDamage(pTrooper,pTrooper->common.nStrength,
				 DMGTYPE_BULLET,pTrooper->common.position,0);
        break;
    }
}


static void LaunchNextPhase()
{
    switch( airSupportType )
    {
        case AIRSUPPORT_RECON:
            if( ReconTimer <= 0 )
                ReconTimer = ReconTime;
            // ready to begin the next mission
            missionInProgress = 0;
            break;

        case AIRSUPPORT_AIRDROP:
            // begin paratrooepr anim
            RequestParatrooperAnimation( airSupportPos );
            SargeAirSupportMessageSend( SargePointer(airSupportArmy), AIRSUPPORT_LAST, airSupportPos );
            myParatrooperFrame = 1; // start my counter
            break;
            
        case AIRSUPPORT_AIRSTRIKE:
			int	i, x, y;

			for( i = 0; i < AIRSTRIKE_NUMEXPLOSIONS; i++ )
			{
				x = (rand() % AIRSTRIKE_RADIUS) + (rand() % AIRSTRIKE_RADIUS) - AIRSTRIKE_RADIUS;
				y = (rand() % AIRSTRIKE_RADIUS) + (rand() % AIRSTRIKE_RADIUS) - AIRSTRIKE_RADIUS;
				DoDelayedExplosion( airSupportPos.x + x, airSupportPos.y + y,
					airStrikeCommands[rand()%NUMAIRSTRIKEEXPLOSIONS],
					NULL, DMGTYPE_OTHER_EXPLOSION, AIRSTRIKE_MAXDAMAGE, NULL, TRUE,
					rand()%10, SargePointer(airSupportArmy)->common.nUniqueID, BIG_EXPLOSION );
			}
			DoDelayedExplosion( airSupportPos.x, airSupportPos.y,
				airStrikeCommands[rand()%NUMAIRSTRIKEEXPLOSIONS],
				NULL, DMGTYPE_OTHER_EXPLOSION, AIRSTRIKE_MAXDAMAGE, NULL, TRUE,
				rand()%10, SargePointer(airSupportArmy)->common.nUniqueID, BIG_EXPLOSION );

           // ready to begin the next mission
           missionInProgress = 0;
           break;
    }
}

void DrawAirSupport(void)
{
	int x, y;
	SPOINT ul, lr;

	// separate drawing of airsupport plane from airsupport action
        
    // drawing the airplane anim
	if( airSupportFrame > 0 )
	{
		x = airxstart + (AirSupportWidth * airSupportFrame / airtime );
		y = (int)(airystart - (AirSupportWidth * airmult * airSupportFrame / airtime ));
        if (alternateAir)        // easter egg.
            DisplaySpriteClipped( airSupportSprite2, x, y );
        else
            DisplaySpriteClipped( airSupportSprite1, x, y );
		airSupportFrame += gpGame->dwDeltaTime;

        // done drawing the airplane anim
		if( airSupportFrame >= airtime )
			airSupportFrame = 0;
	}

    // drawing the paratrooper anim
	if( paratrooperFrame > 0 )
	{
		int frame;

		x = paratrooperPos.x - the_map.screenrect.left;
		y = paratrooperPos.y - the_map.screenrect.top - paratrooperStartHeight;
		if( paratrooperFrame < (paratrooperTime >> 1) )
		{
			frame = paratrooperFrame * ParatrooperData[0].num_frames / (paratrooperTime >> 1);
			y -= 114;
		}
		else
		{
			frame = (((paratrooperFrame - (paratrooperTime >> 1)) * ParatrooperData[0].num_frames)) 
				/ (paratrooperTime >> 1);
		}
		DisplaySpriteClipped( ParatrooperData[0].sprites[frame], x, y );
		paratrooperFrame += gpGame->dwDeltaTime;

        // done drawing paratrooper anim
		if( paratrooperFrame >= paratrooperTime )
		{
			FreeParachuteGraphics();
			paratrooperFrame = 0;
		}
	}

    // now for effects of running the anims (the results of the air mission)

    // while running the paratrooper anim, see if they land and deploy
	if( myParatrooperFrame > 0 )
	{
		myParatrooperFrame += gpGame->dwDeltaTime;
		if( myParatrooperFrame >= paratrooperTime )
        {
            // local player drops parachutists
            if (IS_LOCAL_ARMY(airSupportArmy))
                DropMyParachutists();

            // ready to begin the next mission
            missionInProgress = 0;
        }
	}

    // while running the airplane anim
    if( myAirSupportFrame > 0 )
    {
        myAirSupportFrame += gpGame->dwDeltaTime;

        // only we get our visibility effects
        if (airSupportArmy == ARMY_PLAYER)
        {
            // make area on map visible and forces visible
            ul.x = __max( 0, airSupportPos.x - AIRSUPPORT_VISIBILITY_RADIUS );
            ul.y = __max( 0, airSupportPos.y - AIRSUPPORT_VISIBILITY_RADIUS );
            lr.x = __min( the_map.FullPixelRect.right-1, airSupportPos.x + AIRSUPPORT_VISIBILITY_RADIUS );
            lr.y = __min( the_map.FullPixelRect.bottom-1, airSupportPos.y + AIRSUPPORT_VISIBILITY_RADIUS );
            AirMakeVisible( ARMY_PLAYER, ul, lr );
        }
                
        // if plane has gone on long enough, trigger next effect based on type
        if( myAirSupportFrame >= airtime )
        {
            myAirSupportFrame = 0; // end of air anim


            // local player goes on to next phase
            // remote player sends extra message for paratroop anim
            if (IS_LOCAL_ARMY(airSupportArmy))
                LaunchNextPhase();
			else missionInProgress = 0; // end of remote mission behaviors
        }
	}

    // pending air mission waiting can now start
    if (aircount && !missionInProgress) DoNextAir(); 
}


int AirSupportBlocked(SPOINT pWhere, int eArmy)
{
	int i;
    int x,y;
	OBJECT *pObject;

    // find any aa guns against us covering the area

	for (i=0;i<the_map.num_objs[AA_GUN];i++)
	{
		pObject=&the_map.obj_type_list[AA_GUN][i];
        x = pObject->common.position.x;
        y = pObject->common.position.y;

		if ( x > (pWhere.x-AIRSUPPORT_VISIBILITY_RADIUS) &&
			 x < (pWhere.x+AIRSUPPORT_VISIBILITY_RADIUS) &&
			 y > (pWhere.y-AIRSUPPORT_VISIBILITY_RADIUS) &&
			 y < (pWhere.y+AIRSUPPORT_VISIBILITY_RADIUS) &&
			 ITEM_ARMY(pObject) != eArmy &&
             pObject->common.nStrength > 0 )
            return TRUE;
	} 

	return FALSE;
}

static void ProcessAir(AIRSUPPORTTYPE whichtype, SPOINT where,int eArmy)
{
    // special multiplayer request for paratrooper anim only
    if (whichtype == AIRSUPPORT_LAST)
    {
        RequestParatrooperAnimation(where);
		return;
    }


    // local army relocates para drop to good place
	if (whichtype == AIRSUPPORT_AIRDROP && IS_LOCAL_ARMY(airSupportArmy))
    {
        // if has no units, cant do the drop
        if (ParatrooperNextInHQ( (ARMY_TYPE)airSupportArmy ) == NULL)
            return; 

        IPOINT tile;
        tile=IPOINT_FROM_SPOINT(where);
          
		tile = ItemFanOut((ITEM*)NULL,tile,25,ParaSafeDeploy);
        if (tile==0)
        {
			MsgBroadcastWithText( NOPARAS );
			return;
		}
        where = CenterPointFromTile(tile);
    }

    // save globals data on this current air mission
	missionInProgress = TRUE;
	airSupportType = whichtype;
	airSupportPos = where;
    airSupportArmy = eArmy;

	myAirSupportFrame = 1; // start airplane timing
    airSupportFrame = 1; // start airplane anim
    int d;
    d = rand() % 100;
    alternateAir = (Allah == 2 || (d == 69) ) ; // yin-yang number

 	AudioPlayItem(PLANE_SOUND, (ITEM *)SargePointer(ARMY_PLAYER));

    // tell remote to draw our plane. separate message done for paratroop anim
	// if we are the initiators
	if (IS_LOCAL_ARMY(airSupportArmy))
		SargeAirSupportMessageSend( SargePointer(airSupportArmy), whichtype, where );


    // tell troopers to duck! they cant tell if it is strike or what
	TrooperAirCenter(airSupportPos);

}
    
int DoAirSupport(AIRSUPPORTTYPE whichtype, SPOINT where,int eArmy)
{
    // see if protected by AA guns. Cant do anything but recon if so
	if (whichtype != AIRSUPPORT_RECON && AirSupportBlocked(where,eArmy))
        return AIRSUPPORT_INVALID_AAGUNS;

    LEGION* pLegion = ArmyGetLegion(eArmy);
    switch (whichtype)
    {
        case AIRSUPPORT_AIRSTRIKE:
            if (!pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE]) return -1;
            UseUpAirStrike(eArmy);
            break;
        case AIRSUPPORT_RECON:
            if (!pLegion->AirResources[ARMY_RESOURCE_AIR_RECON]) return -1;
            UseUpRecon(eArmy);
            break;
        case AIRSUPPORT_AIRDROP:
            if (!pLegion->AirResources[ARMY_RESOURCE_PARATROOPERS]) return -1;

            UseUpAirDrop(eArmy);
            break;
    }

    // already one air operation in progress, must wait
	if(missionInProgress)
    {
        if (aircount > MAX_AIR) return -1; // too bad. you lost the resource

        ++aircount;
        pendingAir[aircount].where = where;
        pendingAir[aircount].what = whichtype;
        pendingAir[aircount].who = eArmy;
		return 1;  // it will be done
    }
    
    ProcessAir(whichtype,where,eArmy);

	return 1; // it is being done even as we speak
}


///========================================================================
//	Function:		Viewable
//	Description:	is item within box (can therefore be seen by air)
///========================================================================

static BOOL Viewable(ITEM* pItem,SPOINT ul, SPOINT lr)
{ // is item in rect?
    if (pItem->position.x < ul.x) return FALSE;
    if (pItem->position.x > lr.x) return FALSE;
    if (pItem->position.y < ul.y) return FALSE;
    if (pItem->position.y > lr.y) return FALSE;
    return TRUE;
}


///========================================================================
//	Function:		AirMakeVisible
//	Description:	See enemy forces in box 
///========================================================================

static void AirMakeVisible(int viewArmy,SPOINT ul, SPOINT lr)
{

    int eArmy;
    LEGION* pLegion;
    VEHICLE* pVehicle;
    SARGE* pSarge;
    UNIT* pUnit;
    int i;

    FOR_EACH_DEPLOYED_ARMY(eArmy)
    {
        if (eArmy == viewArmy) continue; // dont need to see own forces
        pLegion = ArmyGetLegion(eArmy);

        // view his sarge?
        pSarge = SargePointer(eArmy);
        if (Viewable((ITEM*) pSarge,ul,lr))
            See(viewArmy,(ITEM*)pSarge);

        // view his vehicles?
        FOR_EACH_VEHICLE(pLegion,i)
        {
            pVehicle = pLegion->pLegionVehicles[i];
            if (Viewable((ITEM*) pVehicle,ul,lr))
                See(viewArmy,(ITEM*)pVehicle);
        }
            
        // view his units
        FOR_EACH_UNIT(pLegion,pUnit)
        {
            if (Viewable((ITEM*) pUnit,ul,lr))
                See(viewArmy,(ITEM*)pUnit);
        }

		// currently lacking viewing assets
		// and exposing interesting unowned objects BUG
    }

}







