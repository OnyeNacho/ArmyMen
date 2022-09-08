/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: aix.cpp $
//
//	DESCRIPTION:	ai commander
//
//	AUTHOR:			Bruce Wilcox
//
//	CREATED:		Thursday, June 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/aix.cpp 171   4/16/98 3:25p Bwilcox $
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/aix.cpp $
//  
//  171   4/16/98 3:25p Bwilcox
//  SLOW POISON MOVEMENT
//  
//  170   4/16/98 3:05p Bwilcox
//  POISON FIX
//  
//  169   4/15/98 10:09p Bwilcox
//  
//  168   4/15/98 7:02p Bwilcox
//  
//  167   4/12/98 9:49p Bwilcox
//  fix npc vehicles to always have a controller even if no goal
//  
//  166   4/12/98 3:38p Bwilcox
//  hp moved in label disply
//  
//  165   4/10/98 6:36p Bwilcox
//  
//  164   4/10/98 5:21p Bwilcox
//  
//  163   4/10/98 1:38p Nrobinso
//  fix endif in wrong place
//  
//  162   4/10/98 12:34p Bwilcox
//  fix final build
//  
//  161   4/10/98 11:30a Bwilcox
//  
//  160   4/10/98 1:19a Bwilcox
//  
//  159   4/07/98 8:59p Bwilcox
//  turn off labeling of the dead
//  
//  158   4/05/98 1:38p Bwilcox
//  
//  157   4/04/98 3:35p Bwilcox
//  
//  156   4/04/98 11:31a Bwilcox
//  
//  155   4/04/98 10:51a Bwilcox
//  
//  154   4/04/98 10:08a Bwilcox
//  
//  153   4/04/98 9:34a Bwilcox
//  
//  151   4/02/98 2:02p Phu
//  typecasting to prevent warnings
//  
//  150   3/31/98 2:29p Bwilcox
//  
//  149   3/31/98 2:25p Bwilcox
//  labeling foe sarges
//  
//  148   3/30/98 10:09p Nrobinso
//  switch to animtime, which allows for pauses
//  
//  147   3/30/98 5:54p Bwilcox
//  sarge ai control and fix captureflag on remote machines
//  
//  146   3/30/98 11:46a Bwilcox
//  
//  145   3/28/98 7:14a Bwilcox
//  multiplayer-mode easter egg. Enjoy. Best Regards, The AI Guru
//  
//  144   3/26/98 8:53p Bwilcox
//  
//  143   3/26/98 6:27p Bwilcox
//  moving a text to usa.h, deleting unused UNIT_BLOCK stuff
//  
//  142   3/26/98 12:00p Bwilcox
//  show no flags of armies not playing,
//  show flags only for a capture-type game
//  
//  141   3/25/98 8:08a Bwilcox
//  
//  140   3/25/98 8:05a Bwilcox
//  
//  139   3/24/98 9:59a Bwilcox
//  
//  138   3/20/98 9:20p Bwilcox
//  
//  137   3/20/98 3:19p Bwilcox
//  temple control
//  
//  136   3/18/98 9:02p Bwilcox
//  
//  135   3/18/98 7:36p Bwilcox
//  spontaneous fire and barrel fire suppressed in multiplayer
//  
//  134   3/18/98 10:18a Bwilcox
//  
//  133   3/17/98 12:14p Bwilcox
//  
//  132   3/17/98 11:14a Bwilcox
//  
//  131   3/17/98 9:48a Dmaynard
//  was trying to move the flag in  SETUP substate, causing an access
//  violation eventually in removeObjectDisp layer.
//  
//  130   3/16/98 1:20p Bwilcox
//  removing unneeded checks for ARMY_OBSTACLE when category is
//  clearly unique.
//  
//  129   3/16/98 11:16a Bwilcox
//  vehicles update ai 15 times asecond
//  trooperupdatemessagereceive bug if no trooper found fixed
//  
//  128   3/15/98 7:43a Bwilcox
//  better isstrategic pin proceesing
//  
//  127   3/14/98 3:54p Bwilcox
//  
//  126   3/13/98 10:31p Bwilcox
//  
//  125   3/13/98 8:28p Bwilcox
//  
//  124   3/13/98 7:50p Bwilcox
//  
//  123   3/13/98 3:05p Bwilcox
//  
//  122   3/13/98 2:45p Bwilcox
//  
//  121   3/13/98 9:29a Bwilcox
//  
//  120   3/13/98 9:20a Bwilcox
//  
//  119   3/13/98 8:44a Bwilcox
//  
//  118   3/10/98 10:05a Bwilcox
//  
//  117   3/10/98 9:49a Bwilcox
//  
//  116   3/06/98 2:02p Bwilcox
//  spontaneous combustion once every 30 minutes maybe
//  
//  115   3/02/98 2:00p Bwilcox
//  removing dead code tied to npc sarges (a concept discarded)
//  
//  114   2/27/98 4:01p Bwilcox
//  fixing speed bug
//  
//  113   2/26/98 6:10p Bwilcox
//  per fruin request, reduce y vis range of all but sarge, and make x/y
//  uniform
//  Use sargecane to see the range of other vision
//  
//  112   2/26/98 2:33p Nrobinso
//  remove underline_sarge
//  
//  111   2/24/98 12:30p Bwilcox
//  dont attemp to control vehicles not on map
//  
//  110   2/05/98 6:30p Bwilcox
//  
//  109   2/05/98 6:08p Bwilcox
//  sarge cane added
//  
//  108   2/05/98 11:34a Bwilcox
//  show objects in range of cursor
//  
//  107   2/04/98 11:06a Bwilcox
//  router performance tuning and draw fixes
//  
//  106   2/02/98 2:01p Bwilcox
//  
//  105   2/02/98 12:33p Bwilcox
//  
//  104   1/28/98 1:24p Bwilcox
//  fixed load/free stuff
//  
//  103   1/28/98 12:32p Bwilcox
//  
//  102   1/27/98 2:22p Phu
//  initialize pTrooper in AiLabel
//  
//  101   1/27/98 11:24a Bwilcox
//  aix dead code removal. spawned ArmiesDelete from ArmyDelete
//  
//  100   1/15/98 4:21p Bwilcox
//  
//  99    1/15/98 4:11p Bwilcox
//  
//  98    1/14/98 2:06p Bwilcox
//  Big cheat key added
//  
//  97    1/14/98 7:25a Bwilcox
//  
//  96    1/14/98 7:29a Bwilcox
//  
//  95    1/14/98 7:24a Bwilcox
//  
//  94    1/13/98 4:35p Bwilcox
//  
//  93    1/13/98 4:22p Bwilcox
//  force labeling  shift-z  d  l
//  
//  92    1/13/98 1:44p Bwilcox
//  router inited with collapse list to use fewer waypoints on ai vehicles
//  
//  91    1/13/98 8:36a Bwilcox
//  routingdraw now selects none, frnd, frnd.foe
//  
//  90    1/13/98 8:17a Bwilcox
//  more vehicle speed fixes to stop
//  
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "Army.h"
#include "MainFrm.h"	//key type defns
#include "Map.h"
#include "Vehicle.h"
#include "ui.h"
#include "Input.h"
#include "object.h"
#include "miscfile.h"
#include "map.h"
#include "Ai.h"
#include "bmptext.h"
#include "unit.h"
#include "AiAccess.h"
#include "comm.h"
#include "item.h"
#include "miscfile.h"
#include "stratmap.h"
#include "avatar.h"
#include "event.h"
#include "pad.h"
#include "sarge.h"
#include "commands.h"
#include "trooper.h"
#include "wobject.h"
#include "gameflow.h"
#include "object.h"
#include "objectmsg.h"
#include "explosions.h"
extern char* smoky_text;

// ai friends includes
#include "newdoor.h"
#include "Aix.h"
#include "aibtank.h"
#include "snd.h"

extern char labelForces;
extern char bw4;
void SargeControl(SARGE* pSarge);
SPOINT OffPoint(SPOINT from,int direction,int distance);
char  sargeCane = 0;
extern int xVisRange;
extern int yVisRange;

static OBJECT* turtleObject = NULL;
static OBJECT* templeObject = NULL;
static OBJECT* flags[4];
static DWORD lastVehicleAIUpdated;
static DWORD lastNessUpdated = 0;
static DWORD lastTempleUpdated = 0;
static long flameLastTime = 0;
static long captureLastTime = 0;
static OBJECT* nessObject = NULL;
static OBJECT* poisonObject = NULL;
SPOINT cloudPt = OFF_THE_MAP;

static long poison  = 0;
static int cloud = 0;
static long cloudtime = 0;
static int armpoison = 0;

//******************************************//
//	External data
//******************************************//
    // to control the mouse/key ui
extern unsigned char scrollReset;
UNIT* holdUnit = NULL;
VEHICLE* underlineVehicle = NULL;

//****************************************************//
//	Local turn-independent data and function prototypes
//***************************************************//
char triggerFireDraw = 0;
char triggerViewDraw = 0;

// key/mouse debug overrides
static void ChangeVehicleView(UINT nChar, UINT nFlags);

static char commander = 0;			// is ai commander allowed to run

//******************************************//
//	Dynamic turn-dependent data
//******************************************//

// data for ai planning system
long aiFrame = 0;					// current ai "time" 
char aiPlayers = 2;					// 1= army_player 2 = army_computer 3 =both

// data for debug-layer drawing
COLORREF layerColor = RGB_WHITE;	// color for debug-layer display
int selectedUnit = 0;				// fake unit draw in new color?

// data for routeplanning
char drawWaypoints = 0;				// vehicle shows paths

// data about units
int visibilityRange = 25;			// max table vis segment range in tiledist

// data about vehicles
int tracespeed = 0;					// show speed changes of vehicle

//******************************************//
//	End of Dynamic turn-dependent data
//******************************************//

//******************************************//
//	Misc exports
//******************************************//

void DoFatal(char* buf){ // if ai wants to die due to error

    TRACE(buf);
    DebugBreak(); // invoke debugger
}
    

//******************************************//
// AI Initialization
//******************************************//

void AIXMissionInit()
{
    aiFrame = 0;
    flameLastTime = 0;
    lastNessUpdated = 0;
	lastTempleUpdated = 0;
    captureLastTime = 0;
    gpGame->CaptureFlag = 0;
	gpGame->oneplayerMode = 0;
    nessObject = NULL;
	poisonObject = NULL;
	cloudPt = OFF_THE_MAP;
	armpoison = 0;
	poison = 0;
	cloud = 0;
	cloudtime = 0;
}


int	 Player0IsAI()			// is player0 ai?
{
    return FALSE;
}    

static void HandleVehicle(VEHICLE* pVehicle)
{
    if (pVehicle->common.nStrength == 0) return; // its dead or not around

    // establish control if you dont have it and want to go somewhere or are npc
    if ((pVehicle->aiGoal.x || pVehicle->npc) && !pVehicle->controller)  InitControl(pVehicle);

    // maintain control once you have it
    if (pVehicle->controller) Control(pVehicle);
}

static void HandleSarge(SARGE* pSarge)
{
    if (pSarge->common.nStrength == 0) return; // its dead or not around
  
    // maintain control once you have it
    SargeControl(pSarge);
}


static void RunAI(int eArmy,BOOL controlled)
{
    LEGION* pLegion;
    VEHICLE* pVehicle;
    int i;
    pLegion = ArmyGetLegion(eArmy);
    for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
    {
        pVehicle = pLegion->pLegionVehicles[i];
        if (!VEHICLE_ON_MAP(pVehicle)) continue; // not availabe
        if (pVehicle->common.nStrength == 0) continue; // dead


        // turn off ai mode when goal ends and vehicle is stationary
       if (pVehicle->humanAI && !pVehicle->aiGoal.x && !pVehicle->full_velocity)
           pVehicle->npc = pVehicle->humanAI = 0;

        if (controlled || pVehicle->aiGoal.x || pVehicle->npc)
        {
            HandleVehicle(pVehicle);
        }
    }

	SARGE* pSarge;
	pSarge = SargePointer(eArmy);
	if (!pSarge) return;
	if (!pSarge->npc) return;
	HandleSarge(pSarge);
}

//////////////////////////////////////////////////////////////////////////
//			AI code per frame
//////////////////////////////////////////////////////////////////////////    


void AICommander(void){ // vehicle/commander ai entrypoint per logical aiFrame

    long diff;
	if (gpGame->GetSubState() != PLAY_SUB_STATE ) return;

    diff = gpGame->dwAnimTime - lastVehicleAIUpdated;
    if (diff < 75){
        return;
    }

    lastVehicleAIUpdated = gpGame->dwAnimTime;

    // control vehicles and sarge as appropriate
    RunAI(ARMY_PLAYER,Player0IsAI());
    RunAI(ARMY_PLAYER_2,TRUE);
    RunAI(ARMY_PLAYER_3,TRUE);
    RunAI(ARMY_PLAYER_4,TRUE);
}


//*****************************************/
//	External callin at draw time
//*****************************************/
extern char routingDraw;
#ifndef FINAL
static void AILabelCursor(HDC hDC){

    char buf[40]; int n;
    SPOINT point;
    point.x = (short)(CursorPos.x);
    point.y = (short)(CursorPos.y);
    ScreenToWorld(&point);
    sprintf(buf,"%d.%d",point.x,point.y);
    n = strlen(buf);
    TextOut(hDC,0,10,buf,n);
}

void dumpTrooper(TROOPER* pTrooper,char* text);

static void AILabelItem(HDC hDC,ITEM* pItem){

    char buf[40]; int n,x;
    TROOPER* pTrooper;
    UNIT* pUnit;
	if (pItem->nStrength == 0) return; // no labelling dead
	SPOINT point;


    if (ITEM_TYPE(pItem) == ARMY_TROOPER)
    {
        pTrooper = (TROOPER*) pItem;
        pUnit = pTrooper->pUnit;
        if (pUnit->common.label && pUnit->common.label[0] && labelForces == 2)
            sprintf(buf,"%s-%d %dhp",pUnit->common.label,ITEM_INDEX(pTrooper) & 15,pItem->nStrength);
        else if (ITEM_ARMY(pTrooper) == ARMY_PLAYER)
            sprintf(buf,"%d-%d %dhp",
             ITEM_INDEX(pTrooper->pUnit),ITEM_INDEX(pTrooper) & 15,pItem->nStrength);
        else
            sprintf(buf,"%d.%d-%d %dhp",ITEM_ARMY(pTrooper)+1,
             ITEM_INDEX(pTrooper->pUnit),ITEM_INDEX(pTrooper) & 15,pItem->nStrength);
    }
	else if (ITEM_TYPE(pItem) == ARMY_SARGE)
	{
		 sprintf(buf,"%s %dhp","Sarge",pItem->nStrength);
	}
    else if (pItem->label && pItem->label[0] && labelForces == 2)
        sprintf(buf,"%s %dhp",pItem->label,pItem->nStrength);
    else if (ITEM_ARMY(pItem) == ARMY_PLAYER)
        sprintf(buf,"%d %dhp",ITEM_INDEX(pItem),pItem->nStrength);
    else 
        sprintf(buf,"%d.%d %dhp",ITEM_ARMY(pItem)+1,ITEM_INDEX(pItem),pItem->nStrength);

    point = pItem->position;
    n = strlen(buf);
    point.x -= (n>>1) * 7;
	x = point.x;
    WorldToScreen(&point);
    TextOut(hDC,point.x,point.y,buf,n);


	if (ITEM_TYPE(pItem) == ARMY_TROOPER && labelForces == 2)
	{
		char text[250];
		text[0] = 0;
		dumpTrooper((TROOPER*)pItem,text);
		point = pItem->position;
		n = strlen(text);
		point.x = x;
		point.y += 15;
		WorldToScreen(&point);
		TextOut(hDC,point.x,point.y,text,n);
	}
 
}
#endif
extern int spreadCnt,spreadFrom;
void SpreadFlames(OBJECT* pObj,UID uid);

static long FlagBad(IPOINT tile)
{
	// require block9 be empty
	if (UntrafficableUnit(tile)) return 1;
	if (UntrafficableUnit(tile+LEFT1)) return 1;
	if (UntrafficableUnit(tile+RIGHT1)) return 1;
	if (UntrafficableUnit(tile+UP1)) return 1;
	if (UntrafficableUnit(tile+DOWN1)) return 1;
	if (UntrafficableUnit(tile+LEFT1+UP1)) return 1;
	if (UntrafficableUnit(tile+RIGHT1+UP1)) return 1;
	if (UntrafficableUnit(tile+LEFT1+DOWN1)) return 1;
	if (UntrafficableUnit(tile+RIGHT1+DOWN1)) return 1;
	return 0;
}

long FlagSafeDeploy(IPOINT index)
{
    if (FlagBad(index))	return 0; 
    SPOINT point;
    point = CenterPointFromTile(index);
    ITEM* pItemList;
    pItemList = GetObjectsMaskPoint(&point);
    if (pItemList != NULL) 
		return 0;  // dont want this

    // this is as good as any place
    return index;
}

static void CheckFlag(OBJECT* pObj)
{
    if (!pObj) return;
	if (pObj->triggers & TRIGGER_UNDEPLOYED) return; // not deployed or in some sarge weapon slot
 	if (!FlagBad(pObj->common.tile)) return; // fine
	IPOINT tile;
	tile = pObj->common.tile;
    tile = ItemFanOut(NULL,tile,25,FlagSafeDeploy);
    if (!tile) return;
    MapRemoveObject(pObj);
    SPOINT pt;
    pt = CenterPointFromTile(tile);
    MapPlaceObject(pObj,&pt);
    ObjectPlaceMessageSend(pObj); // tell people to move it
}

void AIDraw( void ){ /* display onto map space if in debug */

	if (gpGame->GetSubState() != PLAY_SUB_STATE ) return;
	int i;
	OBJECT* pObj;

    if (!aiFrame++){		// incr frame, and do init on 1st time
        // capture init
        flags[0] = flags[1] = flags[2] = flags[3] = NULL; // clear mp flags
        captureLastTime = 0;	// reset capture timer data
        gpGame->CaptureFlag = 0;		// reset capture flag
        // ness init
        nessObject = NULL;
        lastNessUpdated = 0;
        // turtle init
        turtleObject = NULL;		// reset turtle global
		// temple init
		templeObject = NULL;
		lastTempleUpdated = 0;
        // flame init
        flameLastTime = 0; 		// reset flame timer data
		// radioactive waste
		poisonObject = NULL;
		cloudPt = OFF_THE_MAP;
		armpoison = 0;
		poison = 0;
		cloud = 0;
		cloudtime = 0;
        return;				// havent started ai running
    };

    // startup caching
    if (aiFrame == 30)
    {
        // GO FIND THE TURTLE and hide him for bootcamp
        if (gpGame->BootCamp)
        {
            for (i = 0; i < the_map.num_objects; ++i)
            {
                pObj = &(the_map.objects[i]);
                if (pObj->number == 395 && pObj->category == MISCELLANEOUS)
                {
                    turtleObject = pObj;
                    turtleObject->cell.flags |= ANIM_FLAG_INVISIBLE;
                }
            }
        }

		for (i = 0; i < the_map.num_objects; ++i)
        {
           pObj = &(the_map.objects[i]);
           if (pObj->common.label &&  strcmp(pObj->common.label,"aiguru") == 0)
           {
               poisonObject = pObj;
			   cloudPt = pObj->common.position;
           }
        }
		if (poisonObject) // make all other special cans invisible also 
		{		
				 poisonObject->cell.flags |= ANIM_FLAG_INVISIBLE;
			for (i = 0; i < the_map.num_objects; ++i)
			{
				 pObj = &(the_map.objects[i]);
				 if (!pObj->common.label) continue;
				 if (pObj->common.label[0] != 'x') continue;
				 if (pObj->common.label[1] != 'Z') continue;
				 pObj->cell.flags |= ANIM_FLAG_INVISIBLE;
			}
		}

		if (HasEventName("bayou1"))
		{
			for (i = 0; i < the_map.num_objects; ++i)
            {
                pObj = &(the_map.objects[i]);
                if (pObj->number == 396 && pObj->category == MISCELLANEOUS)
                {
                    templeObject = pObj;
                }
            }

		}
   

        // SEE IF THIS IS A capture GAME.
        //host should check flags for trafficability
         gpGame->CaptureFlag = HasEventName("3DOCaptureGame");
         if (gpGame->GameType == GAMETYPE_HOST_MULTIPLAYER)
         {
             if (gpGame->CaptureFlag)
            {
                // find the flags and cache them
                for (i = 0; i < the_map.num_objects; ++i)
                {
                    pObj = &(the_map.objects[i]);
                    if (pObj->category != SPECIAL_ITEMS) continue;
                    if (!pObj->common.pWeapon) continue;
                    if (pObj->common.pWeapon->eWeapon == ARMY_GREENFLAG)
                        flags[0] = pObj;
                    if (pObj->common.pWeapon->eWeapon == ARMY_TANFLAG)
                        flags[1] = pObj;
                    if (pObj->common.pWeapon->eWeapon == ARMY_BLUEFLAG)
                        flags[2] = pObj;
                    if (pObj->common.pWeapon->eWeapon == ARMY_GRAYFLAG)
                        flags[3] = pObj;
                }
            }
        }

        // SEE IF THIS IS Alpine1 mission. look for ness monster
        if (HasEventName("nesstest"))
        {
            // find the flags and cache them
            for (i = 0; i < the_map.num_objects; ++i)
            {
                pObj = &(the_map.objects[i]);
                if (pObj->number == 396 && pObj->category == MISCELLANEOUS)
                    nessObject = pObj;
            }
        }
    }


	HDC	hDC;
    long dif;
    SARGE* pSarge;
    pSarge = SargePointer(ARMY_PLAYER);        
   
    // if there is a turtle, only let be seen if sarge is close
    if (turtleObject && turtleObject->cell.flags & ANIM_FLAG_INVISIBLE)
    {
        i = TileDistance(pSarge->common.tile,turtleObject->common.tile);
        if (i < 20 )
        {
                turtleObject->cell.flags &= ~ANIM_FLAG_INVISIBLE;
				MoveDispXObject(&(turtleObject->cell),TRUE);
        }
    }

    
    // if there is a temple do it when it gets cloe
    if (templeObject)
    {
        i = TileDistance(pSarge->common.tile,templeObject->common.tile);
        // when sarge gets close and he hasnt been close for 3 secs,
        // randomly see if nessie pops up
        if (pSarge->common.position.y > 3700 &&
			pSarge->common.nStrength <= (pSarge->common.nMaxStrength >> 1) &&
			i < 15 && (int)gpGame->dwAnimTime > (int)lastTempleUpdated)
        {
            lastTempleUpdated = gpGame->dwAnimTime + 30000; // dont check for 30 seconds again
            int n;
            n = rand() % 4;
            if (n == 2 || Allah == 2)
            {
				int eventnum;
                eventnum = GetControlEventNum("templeup");
                if (eventnum > 0) EventTrigger(EVENT_CONTROL,eventnum,0,0,1);
				
				// better than full health
				pSarge->common.nStrength = pSarge->common.nMaxStrength + 40;
				lastTempleUpdated = 0x7fffffff; // never again
            }
        }
    }

    
    // if there is a ness monster, maybe he gets seen if sarge gets close
    if (nessObject)
    {
        i = TileDistance(pSarge->common.tile,nessObject->common.tile);
        // when sarge gets close and he hasnt been close for 3 secs,
        // randomly see if nessie pops up
        if (i < 15 && gpGame->dwAnimTime > lastNessUpdated)
        {
            lastNessUpdated = gpGame->dwAnimTime + 6000; // dont check for 6 seconds again
            int n;
            n = rand() % 50;
            if (n == 10 || Allah == 2)
            {
                int eventnum;
                eventnum = GetControlEventNum("nessieup");
                if (eventnum > 0) EventTrigger(EVENT_CONTROL,eventnum,0,0,1);
				lastNessUpdated = 0x7fffffff; // never again
            }
        }
    }

	    // see radiation warning only up close
    if (poisonObject && !armpoison && poisonObject->cell.flags & ANIM_FLAG_INVISIBLE && 
		TileDistance(pSarge->common.tile,poisonObject->common.tile) < 10)
		armpoison = TRUE;
	if (armpoison && TileDistance(pSarge->common.tile,poisonObject->common.tile) > 40)
	 // make it visible to him
    {
		armpoison = 0;
            poisonObject->cell.flags &= ~ANIM_FLAG_INVISIBLE;
			MoveDispXObject(&(poisonObject->cell),TRUE);
			for (i = 0; i < the_map.num_objects; ++i)
			{
				 pObj = &(the_map.objects[i]);
				 if (!pObj->common.label) continue;
				 if (pObj->common.label[0] != 'x') continue;
				 if (pObj->common.label[1] != 'Z') continue;
				 pObj->cell.flags &= ~ANIM_FLAG_INVISIBLE;
				MoveDispXObject(&(pObj->cell),TRUE);
			}
    }

	// continuing radiation poison damages sarge
	if (poison  && gpGame->dwSysTime > poison && pSarge && pSarge->common.nStrength > 1)
	{
		--pSarge->common.nStrength;
		poison += 1000; // next second
		DoExplosion(pSarge->common.position.x, pSarge->common.position.y, 
			//	EXPLOSION_DIRT_SMOKE_S_COMMAND, 
			EXPLOSION_FLASH_SMOKE_S_COMMAND,
				NULL, DMGTYPE_OTHER_EXPLOSION, 0, NULL, TRUE,
				pSarge->common.nUniqueID, SND_NULL_SND_ID );
	}
	// drifting cloud toward you
	if (cloud && cloudtime < gpGame->dwSysTime)
	{
		cloudtime += 33;
		if (cloudPt.x < pSarge->common.position.x) cloudPt.x += rand()%7;
		if (cloudPt.x > pSarge->common.position.x) cloudPt.x -= rand()%7;
		if (cloudPt.y < pSarge->common.position.y) cloudPt.y += rand()%7;
		if (cloudPt.y > pSarge->common.position.y) cloudPt.y -= rand()%7;
		if ((rand() % 8) == 0) DoExplosion(cloudPt.x+2, cloudPt.y-2, 
				EXPLOSION_FLASH_SMOKE_S_COMMAND, 
				NULL, DMGTYPE_OTHER_EXPLOSION, 0, NULL, TRUE,
				pSarge->common.nUniqueID, SND_NULL_SND_ID );
		DoExplosion(cloudPt.x, cloudPt.y, 
				EXPLOSION_DIRT_SMOKE_L_COMMAND, 
				NULL, DMGTYPE_OTHER_EXPLOSION, 0, NULL, TRUE,
				pSarge->common.nUniqueID, SND_NULL_SND_ID );

		if (GetDistance(&pSarge->common.position,&cloudPt) < 5) 
		{
			poison = gpGame->dwSysTime+1000; // each second contaminates you
			cloud = 0; // turn off cloud drigt
		}
	}
	// blow up radioactive waste at your peril. launches dangerous cloud to
	// contaminate you
	if (cloud == 0 && poison == 0 &&
		poisonObject && poisonObject->common.nStrength == 0)
	{
		cloud = 2; // turn on drifing cloud
		cloudtime = gpGame->dwSysTime+800; // moving cloud til it hits
		DoExplosion(cloudPt.x+2, cloudPt.y-2, 
				EXPLOSION_FLASH_SMOKE_L_COMMAND, 
				NULL, DMGTYPE_OTHER_EXPLOSION, 0, NULL, TRUE,
				pSarge->common.nUniqueID, SND_NULL_SND_ID );	}

    // A capture GAME. host should check flags for trafficability
    // check legality every 5 seconds
    if (gpGame->CaptureFlag && (gpGame->dwAnimTime - captureLastTime) > 5000)
    {
        captureLastTime = gpGame->dwAnimTime;
        for (i = 0; i < 3; ++i) CheckFlag(flags[i]);
    }

    // every second see if a fire starts (1 per half hour)
    dif = gpGame->dwAnimTime - flameLastTime;
	if (Allah != 2) dif /= 60; // normally test perminute, test per second in foe mode
    // every minute or every second sec test for random forest flame
    if (dif > 1000L && gpGame->GameType == GAMETYPE_ONEPLAYER) 
    {
        flameLastTime = gpGame->dwAnimTime;
		int d;
		d = (rand() % 90); 
		if (d == 20)
		{
			spreadCnt = 1; // start with 1 tree spread
			spreadFrom = 10; // be willing to spread to 10 over time
			SpreadFlames((OBJECT*)pSarge,ITEM_UID(pSarge));
			if (spreadCnt == 1)	spreadFrom = spreadCnt = 0; // erase search knowledge
			else
            {
                flameLastTime = 0x0fffffff; // only once per game do this
                ReceiveDashMessage(smoky_text,NULL);
            }
		}
    }


	// first acquire the backbuffer context
	hDC = DrawOpen();
	if ( !hDC )
		return;

    if (triggerViewDraw)
    {
        UnitViewDraw(holdUnit);
        triggerViewDraw = 0;
    }

    if (triggerFireDraw)
    {
        UnitFireAllDraw(holdUnit);
        triggerFireDraw = 0;
    }

    ShowMap(0); 						// current map modes to display

    // display routings of UNITs
	
    UNIT* pUnit; 
    int eArmy;
    TROOPER* pTrooper;
	LEGION* pLegion;
    VEHICLE* pVehicle;

    // show where sarge can be seen from
    if (sargeCane)
    {
        pSarge = SargePointer(ARMY_PLAYER);
        SPOINT p,from;
//        SargeFiringPosition(pSarge,&from);
        from = pSarge->common.position;
        p = OffPoint(from,pSarge->common.facing,yVisRange);
        if (ClipLine(&from,&p))
            DrawMultiLine(hDC,&from,&p,RGB_WHITE,TRUE);
    }
#ifndef FINAL
    if (routingDraw) FOR_EACH_LOCAL_ARMY(eArmy)
    { 
      if (routingDraw == 1 && eArmy != 0) break;

      pSarge = SargePointer(eArmy);
      if (!pSarge->pVehicle && pSarge->common.nStrength)
          RouterDraw( hDC, pSarge->common.position,&pSarge->routeData,RGB_WHITE);
	  pLegion = ArmyGetLegion(eArmy);
      for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
      {
          pVehicle = pLegion->pLegionVehicles[i];
          if (pVehicle->common.tile == 0) continue;
          if (pVehicle->common.nStrength == 0) continue;
          if (!pVehicle->controller) continue;
          if (!pVehicle->aiGoal.x) continue;
          RouterDraw( hDC,
              pVehicle->common.position,
              &(((VEHICLE_CONTROLLER*)pVehicle->controller)->routeData),
              RGB_WHITE);          
      }
      FOR_EACH_UNIT(pLegion,pUnit)
      {
        if (!UNIT_ON_MAP(pUnit)) continue;
        if (pUnit->common.nStrength == 0) continue;
        if (!UNIT_ENGAGED(pUnit)){

            RouterDraw( hDC,pUnit->common.position,&pUnit->routeData,RGB_BLUE);


            FOR_EACH_TROOPER(pUnit,pTrooper,i)
        {
            RouterDraw( hDC,pTrooper->common.position,&pTrooper->routeData,RGB_YELLOW);
		
        }}
        else
        {
            FOR_EACH_TROOPER(pUnit,pTrooper,i)
            {
                if (pTrooper->common.nStrength == 0) continue;
                RouterDraw( hDC,pTrooper->common.position,&pTrooper->routeData,RGB_RED);
            }
        }
      }
    }
	
    if (labelForces)
    {
        FOR_EACH_ARMY(eArmy)
        { 
			if (Armies[eArmy].Status == 0) continue;
            pLegion = ArmyGetLegion(eArmy);
            for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
            {
                pVehicle = pLegion->pLegionVehicles[i];
                if (pVehicle->common.tile == 0) continue;
                AILabelItem(hDC,(ITEM*)pVehicle);
            }
            FOR_EACH_UNIT(pLegion,pUnit)
            {
                if (!UNIT_ON_MAP(pUnit)) continue;
                FOR_EACH_TROOPER(pUnit,pTrooper,i)
                {
                    AILabelItem(hDC,(ITEM*)pTrooper);
                }
            }
			pSarge= SargePointer(eArmy);
			if (eArmy != ARMY_PLAYER && pSarge) AILabelItem(hDC,(ITEM*)pSarge);
        }
        // now show where cursor is
        AILabelCursor(hDC);
    }
#endif

    // show objects hit near cursor
    if (bw4)
    {
        SPOINT x;
        SPOINT p;
        x.x = (short)(CursorPos.x);
		x.y = (short)(CursorPos.y);
        ScreenToWorld(&x);
        int i,j;
        for (i = -32; i <= 32; ++i)
        {
            for (j = -32; j <= 32; ++j)
            {
                p.x = x.x + i;
                p.y = x.y + j;
                if (GetObjectsIntersectPoint(&p)) ShowSpoint(p);
            }
        }
    }

 	DrawClose(hDC);
}

//*****************************************/
//	Scroll view control
//*****************************************/

void AIControlUI()/* take control of ui */
{
}

