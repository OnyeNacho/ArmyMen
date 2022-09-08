/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: scripts.cpp $
//
//	DESCRIPTION:	Code for handling scripted events and animated objects
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Thursday, September 4, 1997
//
//	REVISION:		$Header: /ArmyMen/src/scripts.cpp 217   4/17/98 11:22p Bwilcox $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/scripts.cpp $
//  
//  217   4/17/98 11:22p Bwilcox
//  SOBJ_PROCESS now ORs in TRIGGER_CHANGED instead of assigning (and thus
//  losing undeployed and other triggers)l Means explosives and mines save
//  correctly.
//  
//  216   4/17/98 12:11p Bwilcox
//  trace on sobj error added
//  
//  215   4/17/98 12:40a Bwilcox
//  REMOte host cannot trigger timabsolute events
//  
//  214   4/16/98 11:10p Dmaynard
//  Moved TurnOnCompoundEvents and SOBJ_TirnOn  from  InitScripting to
//  Event Start
//  
//  213   4/14/98 8:07p Bwilcox
//  
//  212   4/14/98 4:22p Nrobinso
//  stop reducing volume of script voices
//  
//  211   4/14/98 2:51p Bwilcox
//  tracing for after events
//  
//  210   4/14/98 10:33a Bwilcox
//  switch playcycle to elapsed time printout,
//  optimize trooper no routing when fail on victim
//  
//  209   4/09/98 7:57p Bwilcox
//  
//  208   4/09/98 4:03p Bwilcox
//  better script tracing
//  
//  207   4/07/98 3:23p Nrobinso
//  set volume of hq voices
//  
//  206   4/07/98 12:50p Nrobinso
//  change music when intensity is changed
//  
//  205   4/06/98 12:40p Nrobinso
//  play stream reduced to 80% volume
//  
//  204   4/05/98 1:55p Bwilcox
//  invisiblitly cheat
//  
//  202   4/03/98 1:35p Bwilcox
//  added settrigger function to scripting language
//  moved clears above dospecificthing
//  
//  201   4/02/98 11:56p Bwilcox
//  warning on unrefernecedv events
//  
//  200   4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  199   4/02/98 2:04p Bwilcox
//  trace cleanup
//  
//  198   4/02/98 2:44p Nrobinso
//  set scripted objects to changed for saving purposes
//  
//  197   4/02/98 1:45p Bwilcox
//  cleanups in event triggering and traces
//  
//  196   4/02/98 8:05a Bwilcox
//  better script tracing.
//  troopers now avoid vehicles even if engaged
//  
//  195   4/01/98 3:21p Nrobinso
//  remove unsued
//  
//  194   3/31/98 4:19p Nrobinso
//  don't change max strength
//  
//  193   3/31/98 2:46p Bwilcox
//  cleanups and better script debug
//  
//  192   3/28/98 7:14a Bwilcox
//  multiplayer-mode easter egg. Enjoy. Best Regards, The AI Guru
//  
//  191   3/27/98 8:26p Dmaynard
//  Code to send events on DPSYS Messages
//  
//  190   3/27/98 7:16p Bwilcox
//  
//  189   3/27/98 11:24a Bwilcox
//  scripts sets sarge invul off
//  
//  188   3/26/98 10:11a Bwilcox
//  object scripts not loaded for multiplaer
//  
//  187   3/26/98 8:00a Bwilcox
//  cleanups. moved army regen events AFTER startup
//  
//  186   3/25/98 5:18p Bwilcox
//  script notify for mp capture data
//  
//  185   3/25/98 3:46p Nrobinso
//  change sound looping commands to sound instead of stream
//  
//  184   3/25/98 2:10p Aburgess
//  turn back on playstream looping for Unit Orders
//  
//  183   3/25/98 7:53a Bwilcox
//  makestrategic creates pins as needed
//  
//  182   3/24/98 8:57p Bwilcox
//  grr... color to index to color to huh?
//  
//  181   3/24/98 8:37p Bwilcox
//  stringtoarmy converts absolute color to relative color
//  
//  180   3/24/98 8:12p Dmaynard
//  backout change to GetKillerEventNum
//  
//  179   3/24/98 8:00p Dmaynard
//  renamed killerarmycolor to killerarmyindex  because it IS an index.
//  
//  178   3/24/98 2:29p Nrobinso
//  put voice messages with text thru MsgBroadcastWithText
//  
//  177   3/24/98 1:35p Nrobinso
//  go to voice over intead of text for aagun and blocked paratroopers
//  
//  176   3/24/98 12:10p Nrobinso
//  working on script streams
//  
//  175   3/22/98 2:51p Nrobinso
//  add script calls for looping streams and end of looping
//  
//  174   3/20/98 11:53a Aburgess
//  modifications made to correct VOICE and MUSIC cut offs. It apprears
//  that ALL Music and Voice streams need to be run with LOOP on.
//  
//  173   3/19/98 6:54p Phu
//  make script set object sprite do damage if desired
//  
//  172   3/13/98 6:11p Bwilcox
//  
//  171   3/13/98 5:29p Phu
//  fix type error in Process_SOBJ
//  
//  170   3/13/98 4:06p Bwilcox
//  undeploy from setup a separate event
//  
//  169   3/13/98 11:57a Bwilcox
//  
//  168   3/12/98 7:35p Bwilcox
//  scriptrecharge
//  
//  167   3/08/98 5:42p Phu
//  set tile for script-placed/moved objects so removeobject works (gets
//  rid of remnant explosives).
//  
//  166   3/07/98 10:44p Nrobinso
//  add script commands for making sarges (in)vulnerable
//  
//  165   3/05/98 3:05p Dmaynard
//  Moved EventStart and TimerStart from StartScripting into InitScripting
//  to avaoid an event race problem on the transition from SETUP_SUB_STATE
//  to PLAY_SUBSTATE.
//  
//  164   3/04/98 4:44p Dmaynard
//  Added trace to help find Event Startup Synchronization Bug
//  
//  163   3/02/98 3:04p Phu
//  script object from ODF
//  
//  162   2/28/98 7:51p Bwilcox
//  fixigin compound limit bug 16=> 64
//  
//  161   2/26/98 4:39p Awerner
//  added script support for AIRDROP command
//  
//  since this may be the last time I ever check a file into the armyman
//  project, and since I've tried to make a tradition of adding glib little
//  observations and suchlike to my checkin notices, I'd just like to take
//  this moment to say, and I'm getting all choked up here, I love you
//  guys! (sniffle)
//  
//  160   2/25/98 11:20a Nrobinso
//  increase max string length
//  
//  159   2/24/98 10:31p Nrobinso
//  check for string overflow
//  
//  158   2/19/98 2:57p Aburgess
//  modifications made to support BAD Map detection in remote players.
//  Added checks for BootCamp game play mode.
//  
//  157   2/19/98 10:50a Bwilcox
//  fixing deploy to use atmode and not inmode
//  
//  156   2/17/98 1:43p Nrobinso
//  script visible back in
//  
//  155   2/16/98 9:22p Nrobinso
//  
//  154   2/16/98 4:17p Bwilcox
//  fixing bugs assigning oncethere to ontheway sometimes
//  
//  153   2/16/98 4:15p Nrobinso
//  change show bmp to take a filename
//  
//  152   2/15/98 12:08p Bwilcox
//  removedscript visible and invisible. added scriptbmp
//  
//  151   2/11/98 7:06p Nrobinso
//  properly clear scripted object pointer from parent object
//  
//  150   2/11/98 4:41p Dmaynard
//  
//  149   2/10/98 7:34p Phu
//  fix to damage of attached objects / script assert
//  
//  148   2/05/98 7:33p Bwilcox
//  
//  147   2/05/98 4:19p Bwilcox
//  allow missing names of non-olaying armies
//  
//  146   1/29/98 11:22a Bwilcox
//  script explode now takes optional type of explosion
//  
//  145   1/29/98 11:06a Bwilcox
//  
//  144   1/28/98 8:20p Bwilcox
//  Script visible and invisible for units
//  
//  143   1/28/98 7:21p Bwilcox
//  removing traces
//  
//  142   1/28/98 7:11p Bwilcox
//  startscripts sends multiplayer message in multiplayer only, not
//  oneplayer
//  
//  141   1/27/98 3:31p Bwilcox
//  
//  140   1/27/98 3:28p Bwilcox
//  
//  139   1/27/98 3:22p Bwilcox
//  ignored object ids (like sarges) dont generate an error message
//  
//  138   1/27/98 3:15p Bwilcox
//  ignore bad sarge names
//  
//  137   1/27/98 2:37p Bwilcox
//  puff away dead forces
//  
//  136   1/27/98 1:27p Bwilcox
//  warn (jnot error) on axed events item not found
//  
//  135   1/27/98 11:24a Bwilcox
//  aix dead code removal. spawned ArmiesDelete from ArmyDelete
//  
//  134   1/27/98 9:41a Bwilcox
//  DUMPMESSAGE added
//  
//  133   1/26/98 11:31a Nrobinso
//  fix gate script name problem
//  
//  132   1/19/98 3:24p Awerner
//  Added ALLY and UNALLY, MAKESTRATEGIC and MAKENONSTRATEGIC, and changed
//  get_ and drop_ to take specific item names
//  
//  131   1/15/98 12:57p Bwilcox
//  scriptfollow order extended to optional then clause
//  
//  130   1/13/98 5:52p Bwilcox
//  kneelfire added
//  
//  129   1/13/98 5:21p Bwilcox
//  pronefire and standfire
//  
//  128   1/13/98 12:19p Awerner
//  added in AUDIO command 
//  
//  127   1/13/98 7:59a Bwilcox
//  put validation on the debug menu bar
//  
//  126   1/06/98 3:25p Awerner
//  added in script ALLY command
//  
//  125   1/05/98 10:32a Aburgess
//  latest attempt to resolve Streaming bug. Voice is now handled in a
//  seperate handler.
//  
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "army.h"
#include "scripts.h"
#include "event.h"
#include "pad.h"
#include "map.h"
#include "armymsg.h"
#include "unitmsg.h"
#include "aiaccess.h"
#include "gameflow.h"
#include "disp.h"
#include "comm.h"
#include "ui.h"
#include "unit.h"
#include "sarge.h"
#include "audio.h"
#include "cinema.h"
#include "item.h"
#include "fileio.h"
#include "stratmap.h"

#ifdef USE_TRACE
	#define SCRIPT_ERROR TRACE
#else
	#define SCRIPT_ERROR Error
#endif

extern char scriptDebug;
extern char sargeImmune;
extern char Allah;
extern char scriptDebug;
extern char immobileFoe;
extern char routingDraw;
extern BOOL cheat_move;
extern char labelForces;
extern char vehicleBehavior;
extern BOOL explosions;
/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
int curnumnamedevents=0;
NAMED_EVENT NamedEvents[NUM_NAMED_EVENTS];
short int UseCount[NUM_NAMED_EVENTS]; // reference count
extern char sargeInvisible;
int curnumnameditems=0;
char ItemNames[MAX_NUM_NAMED_ITEMS][TOKENLENGTH];
ITEM *NamedItemPointers[MAX_NUM_NAMED_ITEMS];

COMPOUND_EVENT *compound_events=NULL;

SCRIPTED_OBJECT *SOBJ_first;

#define MAXNUMSCRIPTMESSAGES 256

int numscriptmessages;
char *scriptmessages[MAXNUMSCRIPTMESSAGES];

BOOL scripting_on = FALSE;

#define MAX_TOKENS_PER_SCRIPT 4096

/////////////////////////////////////////////////////////////////////////////
// Function Prototypes
/////////////////////////////////////////////////////////////////////////////
int gettokentype(char *t);
void ProcessMissionText(void);
int TextToTokens(char *text, char tokens[][TOKENLENGTH], int maxnumtokens);
int TextToTokensNoNewlines(char *text, char tokens[][TOKENLENGTH], int maxnumtokens);
int SOBJ_GenerateFromTokens(char tokens[][TOKENLENGTH], int numtokens);

void ArmyClearAlliance();



/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

static void ShowTokenContext(char tokens[][TOKENLENGTH],int n) // display prior tokens to help find err
{
    int j;
    j = n - 15;
    if (j < 0) j = 0;
    TRACE("Context is: ");
    while (++j < n) TRACE("%s ",tokens[j]);
    TRACE("\n");
}

int atoi_nonneg(char *s)
{
	int dummy;
	dummy=atoi(s);
	if (dummy<0)
		dummy=0;

	return dummy;
}

// takes in a number string which might have a decimal point and converts it
// to an integer equal to it times 10
int processNumberWithDecimalPoint(char *s)
{
	int i;
	int retval=0;
	int length;
	
	if (!s)
		return 0;

	if (s[0]=='-')
		return -processNumberWithDecimalPoint(s+1);

	length=strlen(s);

	for (i=0;i<length;i++)
		if (s[i]=='.')
		{
			if (i>0)
			{
				s[i]=0;
				retval=10*atoi(s);
			}

			if (i<length-1)
				retval+=s[i+1]-'0';
			
			return retval;
		}
	
	return 10*atoi(s);
}
			




int GetNewItemNumber(ITEM *pItem)
{
	if (curnumnameditems==MAX_NUM_NAMED_ITEMS)
	{
		TRACE("ERROR: too many different named items- > %d\n",
            MAX_NUM_NAMED_ITEMS);
		return -1;
	}

	ItemNames[curnumnameditems][0]=0;
	NamedItemPointers[curnumnameditems]=pItem;
	pItem->eventNum=curnumnameditems+1;
	return ++curnumnameditems;
}


int RegisterItemName(ITEM *pItem)
{
	char tokens[16][TOKENLENGTH];
	int result,i;

	if (!pItem->label)
		return 0;

	result=TextToTokensNoNewlines(pItem->label, tokens, 16);
	if (result<0)
	{
		SCRIPT_ERROR("ERROR: unable to convert item script to tokens\n");
		return -1;
	}

	if (result==0)
		return 0;

	if (result>2)
	{
		SCRIPT_ERROR("ERROR: too many tokens in item script\n");
		return -1;
	}

	if (gettokentype(tokens[0])!=TOKEN_TYPE_STRING)
	{
		SCRIPT_ERROR("ERROR: an item script needs to be a word (the item name) %s\n",
            tokens[0]);
		return -1;
	}

	if ((result==2) && (gettokentype(tokens[1])!=TOKEN_TYPE_NEWLINE))
	{
		SCRIPT_ERROR("ERROR: two names found for item %s\n", pItem->label);
		return -1;
	}

	for (i=0;i<curnumnameditems;i++)
		if (strcmp(tokens[0], ItemNames[i])==0)
		{
			SCRIPT_ERROR("ERROR: two different items appear to share the name %s\n", tokens[0]);
			return -1;
		}

	if (curnumnameditems==MAX_NUM_NAMED_ITEMS)
	{
		SCRIPT_ERROR("ERROR: too many different named items > %d\n",MAX_NUM_NAMED_ITEMS);
		return -1;
	}

	sprintf(ItemNames[curnumnameditems], "%s", tokens[0]);
	NamedItemPointers[curnumnameditems]=pItem;
	pItem->eventNum=curnumnameditems+1;

//	TRACE ("    Gave item %s number %d\n", tokens[0], pItem->eventNum);

	return ++curnumnameditems;
}


int InitItemNames(void)
{
	int i;
	int eArmy;
	int vehicle;
    LEGION* pLegion;
    UNIT* pUnit;
    VEHICLE* pVehicle;
	int color;
	
	ZeroMemory(ItemNames, sizeof(ItemNames));
	ZeroMemory(NamedItemPointers, sizeof(NamedItemPointers));
	curnumnameditems=0;

	// objects
	for (i=0;i<the_map.num_objects;i++)
	{
		if (RegisterItemName((ITEM*)&the_map.objects[i])<0)
		{
			SCRIPT_ERROR("ERROR: Unable to register an item name\n");
		}
	}


	for (color=0;color<ARMY_LAST_ARMY;color++)
        // changed below to do all armies (bw) since costs nothing
        // and some missions need it.
		for (eArmy=ARMY_PLAYER;eArmy<ARMY_LAST_ARMY;++eArmy)
			if (PlayerColor((ARMY_TYPE)eArmy)==color)
				{
					// units
					pLegion = ArmyGetLegion(eArmy);
					FOR_EACH_UNIT(pLegion,pUnit)
					{
						if (RegisterItemName((ITEM*)pUnit)<0)
						{
							SCRIPT_ERROR("ERROR: Unable to register a unit name\n");
						}
					}

					// vehicles
					FOR_EACH_VEHICLE(pLegion,vehicle)
					{
						pVehicle = pLegion->pLegionVehicles[vehicle];
						if (RegisterItemName((ITEM*)pVehicle)<0)
						{
							SCRIPT_ERROR("ERROR: Unable to register a vehicle name\n");
						}
					}

					// sarge
					if (RegisterItemName((ITEM*)&pLegion->Sarge)<0)
					{
						SCRIPT_ERROR("ERROR: Unable to register a sarge name\n");
					}
				}

	return 0;
}

int GetNamedItemNumber(char *name) //note... the 1st name has number 1, not 0
{
	int i;
	 
	if (strlen(name)>15)
	{
		SCRIPT_ERROR("ERROR: event name %s is more than 15 characters long\n", name);
		return -1;
	}


	for (i=0;i<curnumnameditems;i++)
		if (strcmp(ItemNames[i], name)==0)
			return i+1;

    // ignore predefined names being missing if the army is not active
    // 0 may not be the best event code
    char namecopy[50];
    sprintf(namecopy,"%s",name);
    namecopy[strlen("Green")] = 0;
    if (strcmp("Green", namecopy)==0)    
    {
        if (Armies[gpComm->IndexFromColor(ARMY_GREEN)].Status == 0) return 0;
    }

    sprintf(namecopy,"%s",name);
    namecopy[strlen("Blue")] = 0;
    if (strcmp("Blue", namecopy)==0)    
    {
        if (Armies[gpComm->IndexFromColor(ARMY_BLUE)].Status == 0) return 0;
    }

    sprintf(namecopy,"%s",name);
    namecopy[strlen("Tan")] = 0;
    if (strcmp("Tan", namecopy)==0)    
    {
        if (Armies[gpComm->IndexFromColor(ARMY_TAN)].Status == 0) return 0;
    }

    sprintf(namecopy,"%s",name);
    namecopy[strlen("Gray")] = 0;
    if (strcmp("Gray", namecopy)==0)    
    {
        if (Armies[gpComm->IndexFromColor(ARMY_GRAY)].Status == 0) return 0;
    }

	return -1;
}

ITEM *GetNamedItemPointer(int num)
{
	if ((num>0) && (num<=curnumnameditems))
		return NamedItemPointers[num-1];

	return NULL;
}


void CallBackGreenWins(EVENT_TYPE type, int num, long uint, void *userdata)
{
	if (gpGame->BootCamp)
	{
		gameresult=GAMERESULT_YOULOSE;
		gpGame->WinningArmy = gpComm->IndexFromColor( ARMY_TAN );
	}
	else
	{
		if (PlayerColor(ARMY_PLAYER)==ARMY_GREEN)
			gameresult=GAMERESULT_YOUWIN;
		else
			gameresult=GAMERESULT_YOULOSE;
		gpGame->WinningArmy = gpComm->IndexFromColor( ARMY_GREEN );
	}
}

void CallBackTanWins(EVENT_TYPE type, int num, long uint, void *userdata)
{
	if (gpGame->BootCamp)
	{
		gameresult=GAMERESULT_YOULOSE;
		gpGame->WinningArmy = gpComm->IndexFromColor( ARMY_GREEN );
	}
	else
	{
		if (PlayerColor(ARMY_PLAYER)==ARMY_TAN)
			gameresult=GAMERESULT_YOUWIN;
		else
			gameresult=GAMERESULT_YOULOSE;
		gpGame->WinningArmy = gpComm->IndexFromColor( ARMY_TAN );
	}
}

void CallBackBlueWins(EVENT_TYPE type, int num, long uint, void *userdata)
{
	if (gpGame->BootCamp)
	{
		gameresult=GAMERESULT_YOULOSE;
		gpGame->WinningArmy = gpComm->IndexFromColor( ARMY_GREEN );
	}
	else
	{
		if (PlayerColor(ARMY_PLAYER)==ARMY_BLUE)
			gameresult=GAMERESULT_YOUWIN;
		else
			gameresult=GAMERESULT_YOULOSE;
		gpGame->WinningArmy = gpComm->IndexFromColor( ARMY_BLUE );
	}
}

void CallBackGrayWins(EVENT_TYPE type, int num, long uint, void *userdata)
{
	if (gpGame->BootCamp)
	{
		gameresult=GAMERESULT_YOULOSE;
		gpGame->WinningArmy = gpComm->IndexFromColor( ARMY_GREEN );
	}
	else
	{
		if (PlayerColor(ARMY_PLAYER)==ARMY_GRAY)
			gameresult=GAMERESULT_YOUWIN;
		else
			gameresult=GAMERESULT_YOULOSE;
		gpGame->WinningArmy = gpComm->IndexFromColor( ARMY_GRAY );
	}
}




char *ReservedWords[]=
{
	"IF",
	"THEN",
	"BUTNOT",
	"ALLOF",
	"ONEOF",
	"INORDER",
	"OF",
	"REPEAT",
	"TIMEABSOLUTE",
	"AFTER",
	"AND",
	"TRIGGER",
	"SETTRIGGER",
	"TRIGGERDELAY",
	"ORDER",
	"GOTO",
	"DEPLOY",
	"UNDEPLOY",
	"RECHARGE",
	"SHOWBMP",
	"VISIBLE",
	"INVISIBLE",
	"NUKE",
	"MERGEUNITS",
	"HEAL",
	"SETAICONTROL",
	"SETUSERCONTROL",
	"INMODE",
	"ATMODE",
	"PAD",
	"IGNORE",
	"RETURNFIRE",
	"NESTFIRE",
	"PRONEFIRE",
	"KNEELFIRE",
	"STANDFIRE",
	"ATTACK",
	"DEFEND",
	"EVADE",
	"OBJECT",
	"SWITCH",
	"FOLLOW",
	"EXPLODE",
	"REMOVEOBJECT",
	"PLACEOBJECT",
	"NOTIFY",
	"ME",
	"AIRSTRIKE",
	"AIRDROP",
	"ALLY",
	"RESURRECT",
	"SETSARGEWEAPON",
	"PRIMARY",
	"SECONDARY",
	"SPECIAL",
	"GRENADE",
	"FLAMETHROWER",
	"BAZOOKA",
	"MORTAR",
	"RIFLE",
	"AUTORIFLE",
	"MINE",
	"EXPLOSIVE",
	"DETONATOR",
	"LURE",
	"FLAG",
	"GREENFLAG",
	"TANFLAG",
	"BLUEFLAG",
	"GRAYFLAG",
	"GREYFLAG",

	"INVULNERABLESARGE",
	"VULNERABLESARGE",

	"PLAYSTREAM",
	"PLAYSOUNDLOOP",
	"ENDSOUNDLOOP",
	"CLASS",
	"GO",
	"STOP",
	"DONE",
	"RANDOM",
	"SEQUENTIAL",
	"CINEMA",
	"ENABLE",
	"DISABLE",
	"SCROLLTO",
	"JUMPTO",
	"AUDIO",
	"HIGHINTENSITY",
	"LOWINTENSITY",
	"UNALLY",
	"MAKESTRATEGIC",
	"MAKENONSTRATEGIC"
};

#define NUMRESERVEDWORDS (sizeof(ReservedWords)/sizeof(char*))

BOOL HasEventName(char* name)
{
    int i;
	for (i=0;i<curnumnamedevents;i++)
		if (strcmp(NamedEvents[i].name, name)==0)
            return TRUE;
    return FALSE;
}


int GetControlEventNum(char *name)
{
	int i;
	
	if (strlen(name)>TOKENLENGTH-1)
	{
		SCRIPT_ERROR("ERROR: event name %s is more than %d characters long\n", name, TOKENLENGTH-1);
		return EVENT_NUM_UNDEFINED;
	}

	for (i=0;i<NUMRESERVEDWORDS;i++)
		if (strcmp(name, ReservedWords[i])==0)
		{
			SCRIPT_ERROR("ERROR: %s is not a valid name for an event\n", name);
			return EVENT_NUM_UNDEFINED;
		}

	for (i=0;i<(int)strlen(name);i++)
		if (name[i]=='_')
		{
			SCRIPT_ERROR("ERROR: %s is not a valid name for an event. (It contains an underscore)\n");
			return EVENT_NUM_UNDEFINED;
		}

	for (i=0;i<curnumnamedevents;i++)
		if (strcmp(NamedEvents[i].name, name)==0)
		{
			++UseCount[i];
			return NamedEvents[i].eventnum;
		}

	if (curnumnamedevents==NUM_NAMED_EVENTS)
	{
		SCRIPT_ERROR("ERROR: too many different named events\n");
		return EVENT_NUM_UNDEFINED;
	}

	sprintf(NamedEvents[curnumnamedevents].name, "%s", name);
	NamedEvents[curnumnamedevents].eventnum=UniqueEventNum();
	++UseCount[curnumnamedevents];
	return NamedEvents[curnumnamedevents++].eventnum;
}

long ProcessUID(long storeduid, long currentuid)
{
	if (storeduid==0)
		return 0;

	if (storeduid==UID_ME && currentuid==0)
	{
		TRACE("WARNING: a compound event needs to know the UID of what triggered it,\n");
		TRACE("but there isn't one.\n");
		return 0;
	}

	if (storeduid==UID_ME)
		return currentuid;
    if (storeduid == UID_GREEN || storeduid == UID_TAN || storeduid == UID_BLUE ||
        storeduid == UID_GRAY)
        return storeduid;

	return storeduid;
}

void DoSpecificThingToDo(COMPOUND_EVENT *curevent, int whichThingToDo, long uid)
{
	long uidtoorder;
	long uidtogoto;
	char messagebuf[1024];
	int i;

	// if a settrigger command is given, hold off on using that trigger data
	if (curevent->thingstodo[whichThingToDo].eventtotrigger!=EVENT_NUM_UNDEFINED &&
		curevent->thingstodo[whichThingToDo].ordertogive != ORDERTOGIVE_SETTRIGGER)
		EventTrigger((EVENT_TYPE)curevent->thingstodo[whichThingToDo].typetotrigger, curevent->thingstodo[whichThingToDo].eventtotrigger, uid, curevent->thingstodo[whichThingToDo].delay, 0);
	else if (curevent->thingstodo[whichThingToDo].messagetosend)
	{
        if (scriptDebug)
            TRACE("SHOWING MESSAGE %s\n", curevent->thingstodo[whichThingToDo].messagetosend);
		ZeroMemory(messagebuf, 1024);
		sprintf(messagebuf, "%s", curevent->thingstodo[whichThingToDo].messagetosend);

        // a real message
		switch (curevent->thingstodo[whichThingToDo].MessageType)
		{
			case REAL_MESSAGE:
				if (curevent->thingstodo[whichThingToDo].MessageType)
					ReceiveDashMessage(messagebuf, NULL);
				break;

			case SHOWBMP_MESSAGE:
				ScriptBmp(curevent->thingstodo[whichThingToDo].messagetosend);
				break;

#ifdef _DEBUG
			case DUMP_MESSAGE:
				ReceiveDashMessage(messagebuf, NULL);
				break;
#endif
		}
	}
	else switch(curevent->thingstodo[whichThingToDo].ordertogive)
	{
	case ORDERTOGIVE_GOTO:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);

		if (curevent->thingstodo[whichThingToDo].uidtogoto!=0)
		{
			uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);

			ScriptOrder(uidtoorder,UNIT_DEFEND,
							curevent->thingstodo[whichThingToDo].ontheway,
							curevent->thingstodo[whichThingToDo].oncethere,
							curevent->thingstodo[whichThingToDo].genericcounter,
							NULL, uidtogoto,
							curevent->thingstodo[whichThingToDo].eventtotriggeroncethere,
							curevent->thingstodo[whichThingToDo].typetotriggeroncethere);
		}
		else
			ScriptOrder(uidtoorder,UNIT_DEFEND,
						curevent->thingstodo[whichThingToDo].ontheway,
						curevent->thingstodo[whichThingToDo].oncethere,
						curevent->thingstodo[whichThingToDo].genericcounter,
						&curevent->thingstodo[whichThingToDo].position, 	0,
						curevent->thingstodo[whichThingToDo].eventtotriggeroncethere,
						curevent->thingstodo[whichThingToDo].typetotriggeroncethere);
		break;

    case ORDERTOGIVE_DEPLOY:
        uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);

		if (curevent->thingstodo[whichThingToDo].uidtogoto!=0)
		{
			uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);
			ScriptDeploy(uidtoorder, curevent->thingstodo[whichThingToDo].oncethere, NULL, uidtogoto);
		}
		else if ((curevent->thingstodo[whichThingToDo].position.x>0) && (curevent->thingstodo[whichThingToDo].position.y>0))
			ScriptDeploy(uidtoorder, curevent->thingstodo[whichThingToDo].oncethere, &curevent->thingstodo[whichThingToDo].position, 0);
		else
			ScriptDeploy(uidtoorder, curevent->thingstodo[whichThingToDo].oncethere, NULL, 0);
		
		break;

	case ORDERTOGIVE_FOLLOW:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);
		ScriptFollow(uidtoorder,uidtogoto,
                     curevent->thingstodo[whichThingToDo].ontheway,
                     curevent->thingstodo[whichThingToDo].oncethere,
                     curevent->thingstodo[whichThingToDo].eventtotriggeroncethere,
                     curevent->thingstodo[whichThingToDo].typetotriggeroncethere);
		break;

	case ORDERTOGIVE_UNDEPLOY:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		ScriptUndeploy(uidtoorder);
		break;

	case ORDERTOGIVE_RECHARGE:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		ScriptRecharge(uidtoorder,curevent->thingstodo[whichThingToDo].genericcounter);
		break;

	case ORDERTOGIVE_VISIBLE:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		ScriptVisible(uidtoorder,TRUE);
		break;

	case ORDERTOGIVE_INVISIBLE:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		ScriptVisible(uidtoorder,FALSE);
		break;

	case ORDERTOGIVE_NUKE:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		ScriptNuke(uidtoorder);
		break;

	case ORDERTOGIVE_MAKESTRATEGIC:
		{
			if (scriptDebug) TRACE("Script MakeStrategic triggered\n");
			ITEM *pItem;

			uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
			pItem=AiItemFind(uidtoorder);
			if (pItem)
            {
				ITEM_SET_STRATEGIC(pItem);
                SetStratmapStrategic(pItem);
            }
		}
		break;

	case ORDERTOGIVE_MAKENONSTRATEGIC:
		{
			if (scriptDebug) TRACE("Script MakeNonStrategic triggered\n");
			ITEM *pItem;

			uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
			pItem=AiItemFind(uidtoorder);
			if (pItem)
			{
				ITEM_SET_NONSTRATEGIC(pItem);
				int type;
				type = ITEM_TYPE(pItem);
				// see if its an object. if so clear its trigger
				if (type == ARMY_ASSET || type == ARMY_STRUCTURE || type == ARMY_OBSTACLE)
				{
					OBJECT* pObject;
					pObject = (OBJECT*) pItem;
					pObject->triggers &= ~TRIGGER_STRATEGIC;
				}
			}
		}
		break;


	case ORDERTOGIVE_MERGEUNITS:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);
		ScriptUnitMerge(uidtoorder, uidtogoto);
		break;

	case ORDERTOGIVE_HEALUNIT:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		ScriptHeal(uidtoorder, curevent->thingstodo[whichThingToDo].genericcounter);
		break;

	case ORDERTOGIVE_SETUSERCONTROL:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		ScriptUserControl(uidtoorder);
		break;

	case ORDERTOGIVE_SETAICONTROL:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		ScriptAIControl(uidtoorder);
		break;

	case ORDERTOGIVE_RESURRECT:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);

		ScriptResurrect(uidtoorder, &curevent->thingstodo[whichThingToDo].position, uidtogoto);
		break;

	case ORDERTOGIVE_AIRSTRIKE:
		uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);
		ScriptAirstrike(&curevent->thingstodo[whichThingToDo].position, uidtogoto);
		break;

	case ORDERTOGIVE_AIRDROP:
		uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);
		ScriptAirdrop(&curevent->thingstodo[whichThingToDo].position, uidtogoto, (ARMY_COLOR)curevent->thingstodo[whichThingToDo].genericcounter);
		break;

	case ORDERTOGIVE_ALLY:
		ScriptAlly((ARMY_COLOR)curevent->thingstodo[whichThingToDo].genericcounter, (ARMY_COLOR)curevent->thingstodo[whichThingToDo].ammo);
		break;

	case ORDERTOGIVE_UNALLY:
		ScriptUnAlly((ARMY_COLOR)curevent->thingstodo[whichThingToDo].genericcounter, (ARMY_COLOR)curevent->thingstodo[whichThingToDo].ammo);
		break;

	case ORDERTOGIVE_SETSARGEWEAPON:
			if (scriptDebug) TRACE("Script SetSargeWeapon triggered\n");
		if (curevent->thingstodo[whichThingToDo].ammo>0)
			SetSargeAmmo(curevent->thingstodo[whichThingToDo].whichweapon, curevent->thingstodo[whichThingToDo].ammo);
		SetSargeWeapon(curevent->thingstodo[whichThingToDo].whichweapon, curevent->thingstodo[whichThingToDo].weapontype);
		break;

	case ORDERTOGIVE_PLAYSTREAM:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		MsgBroadcastWithText( curevent->thingstodo[whichThingToDo].eventtotriggeroncethere );
		break;

	case ORDERTOGIVE_PLAYSOUNDLOOP:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		PlayStreamUnit(curevent->thingstodo[whichThingToDo].eventtotriggeroncethere, uid, (SND_SFX_FLAG|SND_LOOP_FLAG));
		break;

	case ORDERTOGIVE_ENDSOUNDLOOP:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		EndStreamUnit(curevent->thingstodo[whichThingToDo].eventtotriggeroncethere);
		break;

	case ORDERTOGIVE_INVULNERABLE:
			if (scriptDebug) TRACE("Script SargeInvulnerable triggered\n");
		SetSargeInvulnerable(ARMY_PLAYER);
		break;

	case ORDERTOGIVE_NORMAL:
		if (scriptDebug) TRACE("Script SargeNormal triggered\n");
		SetSargeNormal(ARMY_PLAYER);
		break;

	case ORDERTOGIVE_SETTRIGGER:
		// find the event to set
		for (i=0;i<curevent->numevents;i++)
			if (curevent->types[i] == curevent->thingstodo[whichThingToDo].typetotrigger && 
				curevent->nums[i]== curevent->thingstodo[whichThingToDo].eventtotrigger)
				break;
		if (i >= curevent->numevents)
		{
			TRACE("cannot find event in settrigger\n");
			break;
		}
	
		if (curevent->counters[i]==0)
		{
			curevent->totalcounter++;
			curevent->counters[i]=1;
		}
		break;

	case ORDERTOGIVE_EXPLODE:
		uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);
		ScriptExplode(&curevent->thingstodo[whichThingToDo].position, uidtogoto, curevent->thingstodo[whichThingToDo].genericcounter);
		break;

	case ORDERTOGIVE_REMOVEOBJECT:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);

		ScriptRemoveObject(uidtoorder);
		break;

	case ORDERTOGIVE_PLACEOBJECT:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);

		ScriptPlaceObject(uidtoorder, &curevent->thingstodo[whichThingToDo].position, uidtogoto);
		break;

	case ORDERTOGIVE_NOTIFY:
		uidtoorder=ProcessUID(curevent->thingstodo[whichThingToDo].uidtoorder, uid);
		uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);
		ScriptNotify(uidtoorder,uidtogoto,curevent->thingstodo[whichThingToDo].genericcounter);
		break;


	case ORDERTOGIVE_AUDIOMODE:
		MissionMusic(TRUE);

		switch (curevent->thingstodo[whichThingToDo].genericcounter)
		{
		case SCRIPT_AUDIO_HIGHINTENSITY:
			audioSetIntensity(AUDIO_INTENSITY_HI);
			break;
		case SCRIPT_AUDIO_LOWINTENSITY:
			audioSetIntensity(AUDIO_INTENSITY_LO);
			break;
		}

		MissionMusic(FALSE);
		break;

	case ORDERTOGIVE_CINEMAMODE:
		switch (curevent->thingstodo[whichThingToDo].genericcounter)
		{
		case CINEMA_ENABLE:
			StartCinematicMode();
			break;
		case CINEMA_DISABLE:
			EndCinematicMode();
			break;
		case CINEMA_SCROLLTO:
			if (curevent->thingstodo[whichThingToDo].uidtogoto!=0)
			{
				ITEM *pItem;
				uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);
				pItem=AiItemFind(uidtogoto);
				if (pItem)
					CinemaMoveToItem(pItem, curevent->thingstodo[whichThingToDo].ammo /*used for speed*/);
			}
			else
				CinemaMoveToPoint(&curevent->thingstodo[whichThingToDo].position, curevent->thingstodo[whichThingToDo].ammo /*used for speed*/);
			break;

		case CINEMA_JUMPTO:
			if (curevent->thingstodo[whichThingToDo].uidtogoto!=0)
			{
				ITEM *pItem;
				uidtogoto=ProcessUID(curevent->thingstodo[whichThingToDo].uidtogoto, uid);
				pItem=AiItemFind(uidtogoto);
				if (pItem)
					CinemaJumpToItem(pItem);
			}
			else
				CinemaJumpToPoint(&curevent->thingstodo[whichThingToDo].position);
			break;
		}
		break;







	}

}

void DoCompoundEventStuff(COMPOUND_EVENT *curevent, long uid)
{
	int i;

	if (!curevent->thingstodo)
		return;

	switch (curevent->howtodothings)
	{
	case DOTHINGSNORMAL:
		for (i=0;i<curevent->numthingstodo;i++)
			DoSpecificThingToDo(curevent, i, uid);
		break;
	case DOTHINGSRANDOM:
		i=rand()%curevent->numthingstodo;
		DoSpecificThingToDo(curevent, i, uid);
		break;
	case DOTHINGSSEQUENTIAL:
		DoSpecificThingToDo(curevent, curevent->howto_count, uid);
		curevent->howto_count=(curevent->howto_count+1)%curevent->numthingstodo;
		break;
	}


}

static void nameEvents(	COMPOUND_EVENT *curevent)
{
		
	int i; char name[100];
	for (i=0;i<curevent->numevents;i++)
	{
		GetEventName(curevent->types[i], curevent->nums[i], name);
		TRACE(" %s",name);
	}
	TRACE("\n");
}

// this is called when an event happens to see if it now completes some
// compound event trigger
static void CompoundEventCallBack(EVENT_TYPE type, int num,
                                  long uid, void *callback)
{
	COMPOUND_EVENT *curevent;
	int cursubevent=-1;
	int i;
	char eventname[255];
	eventname[0] = 0;
	if (scriptDebug) GetEventName(type, num, eventname);
	curevent=(COMPOUND_EVENT*) callback;

	for (i=0;i<curevent->numevents;i++)
		if (curevent->types[i]==type && (curevent->nums[i]==EVENT_NUM_ALL || curevent->nums[i]==num))
			cursubevent=i;

	if ((cursubevent==-1) && (curevent->compoundeventtype!=COMPOUNDEVENT_TIMEABSOLUTE))
	{
		TRACE("ERROR: a compound event got called for an event it didn't care about\n");
		return;
	}


	switch(curevent->compoundeventtype)
	{
	case COMPOUNDEVENT_ALLOF:
		if (curevent->counters[cursubevent]==0)
		{
			curevent->totalcounter++;
			curevent->counters[cursubevent]=1;
			if (curevent->totalcounter==curevent->numevents)
			{
                if (scriptDebug) 
				{
					TRACE("        trigger %s [AllOf]",eventname);
					nameEvents(curevent);
				}
				// clear the counters to enable set trigger to work
				ZeroMemory(curevent->counters, sizeof(curevent->counters));
				curevent->totalcounter=0;
				DoCompoundEventStuff(curevent,uid);
			}
		}
		break;

	case COMPOUNDEVENT_ALLOF_BUTNOT:
		{
			if (cursubevent==curevent->numevents-1) // its the butnot.
				curevent->counters[cursubevent]=1;
			else
			{
				if (curevent->counters[cursubevent]==0)
				{
					curevent->totalcounter++;
					curevent->counters[cursubevent]=1;
					if ((curevent->totalcounter==curevent->numevents-1) && (curevent->counters[curevent->numevents-1]==0))
					{
                        if (scriptDebug) 
						{
							TRACE("        trigger %s [AllOf Butnot]",eventname);
							nameEvents(curevent);
						}
						curevent->totalcounter=0;
						ZeroMemory(curevent->counters, sizeof(curevent->counters));
						DoCompoundEventStuff(curevent, uid);
					}
				}
			}
		}
		break;

	case COMPOUNDEVENT_ONEOF_BUTNOT:
		{
			if (cursubevent==curevent->numevents-1)
				curevent->counters[cursubevent]=1;
			else
				if (curevent->counters[curevent->numevents-1]==0)
                {
                    if (scriptDebug) 
					{
						TRACE("        trigger %s [oneOf butnot]",eventname);
						nameEvents(curevent);
					}
					DoCompoundEventStuff(curevent, uid);
                }
		}
        break;

	case COMPOUNDEVENT_ALLOF_CANCEL:
		if (cursubevent%2==0)
		{
			if (curevent->counters[cursubevent/2]==0)
			{
				curevent->counters[cursubevent/2]=1;
				curevent->totalcounter++;
			}

			if (curevent->totalcounter==curevent->numevents/2)
			{
                   if (scriptDebug) 
					{
						TRACE("        trigger %s [xxx AFTER yyy]",eventname);
						nameEvents(curevent);
					}
				DoCompoundEventStuff(curevent,uid);
			}
			
		}
		else
		{
			if (curevent->counters[cursubevent/2]==1)
			{
				curevent->counters[cursubevent/2]=0;
				curevent->totalcounter--;
			}
		}
		break;

	case COMPOUNDEVENT_ONEOF:
		if (scriptDebug) 
		{
			TRACE("        trigger %s [oneof]",eventname);
			nameEvents(curevent);
		}

		DoCompoundEventStuff(curevent,uid);
		break;

	case COMPOUNDEVENT_INORDER:
		if (cursubevent==curevent->totalcounter)
		{
			curevent->totalcounter++;
			if (curevent->totalcounter==curevent->numevents)
			{
                if (scriptDebug) 
				{
					TRACE("        trigger %s [Inorder]",eventname);
					nameEvents(curevent);
				}
				curevent->totalcounter=0;
				DoCompoundEventStuff(curevent,uid);
			}
		}
		break;

	case COMPOUNDEVENT_COUNTOF:
		if (curevent->counters[cursubevent]==0)
		{
			curevent->counters[cursubevent]=1;
			curevent->totalcounter++;
			if (curevent->totalcounter==curevent->compoundeventcount)
			{
               if (scriptDebug) 
			   {
				   TRACE("        trigger %s [countof]",eventname);
				   nameEvents(curevent);
			   }
				DoCompoundEventStuff(curevent,uid);
			}
		}
		break;

	case COMPOUNDEVENT_REPCOUNTOF:
		curevent->totalcounter++;
		if (curevent->totalcounter==curevent->compoundeventcount)
		{
			if (scriptDebug) 
			{
				TRACE("        trigger %s [repcountof]",eventname);
				nameEvents(curevent);
			}
			DoCompoundEventStuff(curevent,uid);
		}	
	break;

	case COMPOUNDEVENT_TIMEABSOLUTE:
		if (scriptDebug) TRACE("        trigger %s [timeabsolute]\n",eventname);
		DoCompoundEventStuff(curevent,uid);
		break;


	}
}





int CharIsWhiteSpace(char c)
{
	if ((c==' ') || (c=='\t') || (c==13))
		return 1;
	return 0;
}



int CharIsToken(char c)
{
	if ((c==')') || (c=='(') || (c==',') || (c=='<') || (c=='=') || (c=='>') || (c=='{') || (c=='}') || (c=='&') || (c=='+'))
		return 1;
	return 0;
}

int StringIsReservedWord(char *s)
{
	int i;
	for (i=0;i<sizeof(ReservedWords)/sizeof(char*); i++)
		if (strcmp(s, ReservedWords[i])==0)
			return 1;
	return 0;
}

int TextToTokensNoNewlines(char *text, char tokens[][TOKENLENGTH], int maxnumtokens)
{
	int curloc=0;
	int numtokens=0;
	int i;

	while (text[curloc]!=0)
	{
		if (numtokens==maxnumtokens)
		{
			SCRIPT_ERROR("ERROR: Too many tokens - %d max\n",maxnumtokens);
            ShowTokenContext(tokens,numtokens);
			return -1;
		}
		if (text[curloc]=='"')
		{
			int stringstart;
			int stringend;

			stringstart=++curloc;
			while ((text[curloc]!=0) && (text[curloc]!='"'))
			{
				curloc++;
				if ((curloc - stringstart) > 192)
				{
					SCRIPT_ERROR("ERROR: overflow string constant\n");
					return -1;
				}

			}
			if (text[curloc]==0)
			{
				SCRIPT_ERROR("ERROR: no closure for string constant %s\n",
                    text);
				return -1;
			}
			stringend=curloc;

			scriptmessages[numscriptmessages]=(char*)malloc(stringend-stringstart+1);
			scriptmessages[numscriptmessages][stringend-stringstart]=0;
			memcpy(scriptmessages[numscriptmessages], text+stringstart, stringend-stringstart);

			sprintf(tokens[numtokens++], "$%d", numscriptmessages);
			numscriptmessages++;
			if (numscriptmessages==MAXNUMSCRIPTMESSAGES)
			{
				SCRIPT_ERROR("WARNING: Too Many Script Messages > %d\n",MAXNUMSCRIPTMESSAGES);
				numscriptmessages--;
			}
			curloc++;
		}
		else if ((text[curloc]=='\\') || (text[curloc]=='/'))
		{
			while ((text[curloc]!=0) && (text[curloc]!='\n'))
				curloc++;			//skip comments
		}
		else if (CharIsWhiteSpace(text[curloc]) || (text[curloc]=='\n'))  //if we encounter one or more spaces, skip them all
		{
			while (CharIsWhiteSpace(text[curloc]) || (text[curloc]=='\n'))
				curloc++;
		}
		else if (CharIsToken(text[curloc]))
		{
			sprintf(tokens[numtokens++], "%c", text[curloc++]);
		}
		else //a collection of hopefully alpha-numeric characters
		{
			i=0;

			ZeroMemory(tokens[numtokens], TOKENLENGTH);

			while (!CharIsWhiteSpace(text[curloc]) && (text[curloc]!='\n') && (text[curloc]!=0) && (!CharIsToken(text[curloc])))
			{
				if (i<TOKENLENGTH-1) //avoid overflow
					tokens[numtokens][i]=text[curloc];
				else if (i==TOKENLENGTH-1)
					SCRIPT_ERROR("WARNING: Found too-long token. Truncating to %s. May result in ambiguity\n", 
						tokens[numtokens]);

						

				i++;
				curloc++;
			}
			numtokens++;
		}
	}

	return numtokens;
}

int TextToTokens(char *text, char tokens[][TOKENLENGTH], int maxnumtokens)
{
	int curloc=0;
	int numtokens=0;
	int i;

	while (text[curloc]!=0)
	{
		if (numtokens==maxnumtokens)
		{
			SCRIPT_ERROR("ERROR: Too many tokens %d max\n",numtokens);
            ShowTokenContext(tokens,numtokens);
			return -1;
		}


		if ((text[curloc]=='\\') || (text[curloc]=='/'))
		{
			while ((text[curloc]!=0) && (text[curloc]!='\n'))
				curloc++;			//skip comments
		}
		else if (CharIsWhiteSpace(text[curloc]))  //if we encounter one or more spaces, skip them all
		{
			while (CharIsWhiteSpace(text[curloc]))
				curloc++;
		}
		else if (text[curloc]=='\n') //if we encounter one or more newlines, put one in a token
		{
			if (!(numtokens>0 && tokens[numtokens-1][0]=='\n'))
				sprintf(tokens[numtokens++], "\n");

			while ((text[curloc]=='\n') || CharIsWhiteSpace(text[curloc]))
				curloc++;
		}
		else if (CharIsToken(text[curloc]))
		{
			sprintf(tokens[numtokens++], "%c", text[curloc++]);
		}
		else //a collection of hopefully alpha-numeric characters
		{
			i=0;

			ZeroMemory(tokens[numtokens], TOKENLENGTH);

			while (!CharIsWhiteSpace(text[curloc]) && (text[curloc]!='\n') && (text[curloc]!=0) && (!CharIsToken(text[curloc])))
			{
				if (i<TOKENLENGTH-1) //avoid overflow
					tokens[numtokens][i]=text[curloc];
				else if (i==TOKENLENGTH-1)
					SCRIPT_ERROR("WARNING: Found too-long token. Truncating to %s. May result in ambiguity\n", 
						tokens[numtokens]);

				i++;
				curloc++;
			}
			numtokens++;
		}
	}

	return numtokens;
}


int gettokentype(char *t)
{
	int i;
	int decpointcount=0;

	if (t==NULL)
		return TOKEN_TYPE_UNKNOWN;

	if (t[0]==0)
		return TOKEN_TYPE_UNKNOWN;

	if (t[0]=='\n')
		return TOKEN_TYPE_NEWLINE;

	if (t[0]=='$')
		return TOKEN_TYPE_MESSAGE;

	if (CharIsToken(t[0]))
		return TOKEN_TYPE_CONTROLCHAR;

	if (StringIsReservedWord(t))
		return TOKEN_TYPE_RESERVEDWORD;

	if ((t[0]!='-') && ((t[0]<'0') || (t[0]>'9')))
		return TOKEN_TYPE_STRING;

	for (i=1;i<(int)strlen(t);i++)
		if ((t[i]<'0') || (t[i]>'9'))
			if (t[i]=='.')
			{
				decpointcount++;
				if (decpointcount>1)
					return TOKEN_TYPE_STRING;
			}
			else			
				return TOKEN_TYPE_STRING;

	if (decpointcount)
		return TOKEN_TYPE_NUMBER_WITH_DECIMAL_POINT;

	return TOKEN_TYPE_NUMBER;
}


WEAPON_TYPE StringToWeapon(char *s)
{

	if (strcmp(s, "GRENADE")==0)
		return ARMY_GRENADE;
	else if (strcmp(s, "FLAMETHROWER")==0)
		return ARMY_FLAME_THROWER;
	else if (strcmp(s, "BAZOOKA")==0)
		return ARMY_BAZOOKA;
	else if (strcmp(s, "MORTAR")==0)
		return ARMY_MORTAR;
	else if (strcmp(s, "RIFLE")==0)
		return ARMY_RIFLE;
	else if (strcmp(s, "AUTORIFLE")==0)
		return ARMY_AUTORIFLE;
	else if (strcmp(s, "MINE")==0)
		return ARMY_MINE;
	else if (strcmp(s, "EXPLOSIVE")==0)
		return ARMY_EXPLOSIVE_WEAPON;
	else if (strcmp(s, "DETONATOR")==0)
		return ARMY_DETONATOR;
	else if (strcmp(s, "SWEEPER") == 0 )
		return ARMY_SWEEPER;
	else if (strcmp(s, "LURE")==0)
		return ARMY_LURE;
	else if (strcmp(s, "FLAG")==0)
		return ARMY_FLAG;
	else if (strcmp(s, "GREENFLAG")==0)
		return ARMY_GREENFLAG;
	else if (strcmp(s, "TANFLAG")==0)
		return ARMY_TANFLAG;
	else if (strcmp(s, "BLUEFLAG")==0)
		return ARMY_BLUEFLAG;
	else if (strcmp(s, "GRAYFLAG")==0 || strcmp(s, "GREYFLAG")==0)
		return ARMY_GRAYFLAG;
	else
	{
	    return ARMY_NO_WEAPON;
	}

}

int StringToArmy(char *s)
{// these events are in absolutecolor mode

	if (strcmp(s, "GREEN")==0)
		return (int)ARMY_GREEN;
	else if (strcmp(s, "TAN")==0)
		return (int)ARMY_TAN;
	else if (strcmp(s, "BLUE")==0)
		return (int)ARMY_BLUE;
	else if (strcmp(s, "GREY")==0 || strcmp(s, "GRAY")==0   )
		return (int)ARMY_GRAY;
	else
	{
		SCRIPT_ERROR("ERROR: unknown army type %s\n", s);
	    return -1;
	}
}

#define PICKUP_EVENT_NONSPECIFIC_FLAG 0x80 //this flag is always set when
//an encoded pickup event number doesn't refer to a specific item, so that
//there is no ambiguity between item type 20 and item number 20
int GetWeaponPickupOrDropEventNum(int itemnum, WEAPON_TYPE whichweapon)
{
	return (int)whichweapon+(itemnum<<16)+PICKUP_EVENT_NONSPECIFIC_FLAG;
}

int GetSpecificItemPickupEventNum(int whoitem, int whatitem)
{
	return whatitem+(whoitem<<16);
}

int GetKillerEventNum(int itemnum, int eArmy)
{
	int color;  // convert local color to global color
	color = gpComm->m_ArmyIndex[eArmy];
	return (int)color+(itemnum<<8);
}

void GetEventName(EVENT_TYPE type, int num, char eventname[256])
{
	int i;
	switch(type)
	{
    case EVENT_ITEMPICKEDUP:
        sprintf(eventname,"pickup something");
        return;
    case EVENT_ITEMDROPPED:
        sprintf(eventname,"drop something");
        return;
	case EVENT_CONTROL:

		for (i=0;i<curnumnamedevents;i++)
			if (NamedEvents[i].eventnum==num)
			{
				sprintf(eventname, NamedEvents[i].name);
				return;
			}

		sprintf(eventname, "unnamed EVENT_CONTROL %d", num);
		return;
		break;

	case EVENT_PADACTIVATED:

		if (getPadName(num))
		{
			sprintf(eventname, "on_%s", getPadName(num));
			return;
		}
		sprintf(eventname, "unnamed EVENT_PADACTIVATED %d", num);
		return;
		break;

	case EVENT_PADDEACTIVATED:
		if (getPadName(num))
		{
			sprintf(eventname, "off_%s", getPadName(num));
			return;
		}
		sprintf(eventname, "unnamed EVENT_PADDEACTIVATED %d", num);
		return;
		break;

	case EVENT_ITEMDESTROYED:

		if ((num<1) || (num>curnumnameditems))
		{
			sprintf(eventname, "unnamed EVENT_ITEMDESTROYED %d", num);
			return;
		}

		sprintf(eventname, "killed_%s", ItemNames[num-1]);
		return;
		break;

	case EVENT_ITEMDAMAGED:

		if ((num<1) || (num>curnumnameditems))
		{
			sprintf(eventname, "unnamed EVENT_ITEMDAMAGED %d", num);
			return;
		}

		sprintf(eventname, "hit_%s", ItemNames[num-1]);
		return;
		break;

	case 	EVENT_ITEMVISON:

		if ((num<1) || (num>curnumnameditems))
		{
			sprintf(eventname, "unnamed EVENT_ITEMVISON %d", num);
			return;
		}

		sprintf(eventname, "vison_%s", ItemNames[num-1]);
		return;
		break;


	case 	EVENT_ITEMVISOFF:

		if ((num<1) || (num>curnumnameditems))
		{
			sprintf(eventname, "unnamed EVENT_ITEMVISOFF %d", num);
			return;
		}

		sprintf(eventname, "visoff_%s", ItemNames[num-1]);
		return;
		break;

	case EVENT_TIMER:
		eventname[0] = 0; // no name
		return;
		break;

	case EVENT_KILLEDSARGE:
		sprintf(eventname, "EVENT_KILLEDSARGE %d", num);
		return;
		break;
	case EVENT_TILEENTERED:
		sprintf(eventname, "TileEntered event num %d", num);
		return;

	default:
		sprintf(eventname, "event type %d num %d", type, num);
		return;
		break;
	}
}


int GetEventFromToken(char *token, EVENT_TYPE *type, int *num)
{
	//this function assumes that error checking has been done for it,
	//as far as overflow of the tokens array is concerned

	if (strcmp(token, "NULL")==0)
	{
		*type=EVENT_CONTROL;
		*num=EVENT_NUM_UNDEFINED;
		return 1;
	}

	if (strcmp(token, "ALL")==0)
	{
		*type=EVENT_CONTROL;
		*num=EVENT_NUM_ALL;
		return 1;
	}

	if (strncmp(token, "on_", 3)==0)
	{
		*type=EVENT_PADACTIVATED;

		if (strcmp(token+3, "ALL")==0)
			*num=EVENT_NUM_ALL;
		else if ((*num=GetPadNumFromName(token+3))<0)
		{
			SCRIPT_ERROR("WARNING: Unknown item name %s. Set the event to NULL\n", token);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}
		return 1;
	}

	if (strncmp(token, "off_", 4)==0)
	{
		*type=EVENT_PADDEACTIVATED;

		if (strcmp(token+4, "ALL")==0)
			*num=EVENT_NUM_ALL;
		else if ((*num=GetPadNumFromName(token+4))<0)
		{
			SCRIPT_ERROR("WARNING: Unknown item name %s. Set the event to NULL\n", token);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}
		return 1;
	}

	if (strncmp(token, "go_", 3)==0)
	{
		*type=EVENT_ITEMGO;

		if (strcmp(token+3, "ALL")==0)
			*num=EVENT_NUM_ALL;
		else if ((*num=GetNamedItemNumber(token+3))<0)
		{
			SCRIPT_ERROR("WARNING: Unknown item name %s. Set the event to NULL\n", token);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}
		return 1;
	}

	if (strncmp(token, "stop_", 5)==0)
	{
		*type=EVENT_ITEMSTOP;

		if (strcmp(token+5, "ALL")==0)
			*num=EVENT_NUM_ALL;
		else if ((*num=GetNamedItemNumber(token+5))<0)
		{
			SCRIPT_ERROR("WARNING: Unknown item name %s. Set the event to NULL\n", token);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}
		return 1;
	}

	if (strncmp(token, "done_", 5)==0)
	{
		*type=EVENT_ITEMDONE;

		if (strcmp(token+5, "ALL")==0)
			*num=EVENT_NUM_ALL;
		else if ((*num=GetNamedItemNumber(token+5))<0)
		{
			SCRIPT_ERROR("WARNING: Unknown item name %s. Set the event to NULL\n", token);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}
		return 1;
	}


	if (strncmp(token, "hit_", 4)==0)
	{
		*type=EVENT_ITEMDAMAGED;

		if (strcmp(token+4, "ALL")==0)
			*num=EVENT_NUM_ALL;
		else if ((*num=GetNamedItemNumber(token+4))<=0)
		{
            if (*num != 0)
                SCRIPT_ERROR("WARNING: Unknown item name %s. Set the event to NULL\n", token);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}
		return 1;
	}

	if (strncmp(token, "killed_", 7)==0)
	{
		*type=EVENT_ITEMDESTROYED;

		if (strcmp(token+7, "ALL")==0)
			*num=EVENT_NUM_ALL;
		else if ((*num=GetNamedItemNumber(token+7))<=0)
		{
            if (*num != 0)
                SCRIPT_ERROR("WARNING: Unknown item name %s. Set the event to NULL\n", token);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}
		return 1;
	}

	if (strncmp(token, "visoff_", 7)==0)
	{
		*type=EVENT_ITEMVISOFF;

		if (strcmp(token+7, "ALL")==0)
			*num=EVENT_NUM_ALL;
		else if ((*num=GetNamedItemNumber(token+7))<=0)
		{
            if (*num != 0)
                SCRIPT_ERROR("WARNING: Unknown item name %s. Set the event to NULL\n", token);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}
		return 1;
	}

	if (strncmp(token, "vison_", 6)==0)
	{
		*type=EVENT_ITEMVISON;

		if (strcmp(token+6, "ALL")==0)
			*num=EVENT_NUM_ALL;
		else if ((*num=GetNamedItemNumber(token+6))<=0)
		{
            if (*num != 0)
                SCRIPT_ERROR("WARNING: Unknown item name %s. Set the event to NULL\n", token);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}
		return 1;
	}

	if (strncmp(token, "get_", 4)==0)
	{
		int secondline=0;
		int i;
		WEAPON_TYPE curweapon;
		int itemnum, itemnum2;

		*type=EVENT_ITEMPICKEDUP;
		for (i=4;i<(int)strlen(token);i++)
			if (token[i]=='_')
				secondline=i;
		if (!secondline)
		{
			SCRIPT_ERROR("ERROR: a get_ event must have a second underline\n");
			return -1;
		}
		token[secondline]=0;

		if ((itemnum=GetNamedItemNumber(token+4))<=0)
		{
            if (itemnum != 0)
                SCRIPT_ERROR("WARNING: Unknown item name %s in a get_ event\n", token+4);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}

		if ((curweapon=StringToWeapon(token+secondline+1))==ARMY_NO_WEAPON)
		{
			if ((itemnum2=GetNamedItemNumber(token+secondline+1))<=0)
			{
                if (itemnum2 != 0)
                    SCRIPT_ERROR("WARNING: unknown item name or type %s in a get_ event\n", token+secondline+1);
				*num=0;
				return 1;
			}

			*num=GetSpecificItemPickupEventNum(itemnum, itemnum2);
			token[secondline]='_';

			return 1;
		}
		
		*num=GetWeaponPickupOrDropEventNum(itemnum, curweapon);

		token[secondline]='_';

		return 1;
	}

	if (strncmp(token, "drop_", 5)==0)
	{
		int secondline=0;
		int i;
		WEAPON_TYPE curweapon;
		int itemnum, itemnum2;

		*type=EVENT_ITEMDROPPED;
		for (i=5;i<(int)strlen(token);i++)
			if (token[i]=='_')
				secondline=i;
		if (!secondline)
		{
			SCRIPT_ERROR("ERROR: a drop_ event must have a second underline\n");
			return -1;
		}
		token[secondline]=0;

		if ((itemnum=GetNamedItemNumber(token+5))<=0)
		{
            if (itemnum != 0)
                SCRIPT_ERROR("WARNING: Unknown item name %s in a drop_ event\n", token+4);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}

		if ((curweapon=StringToWeapon(token+secondline+1))==ARMY_NO_WEAPON)
		{
			if ((itemnum2=GetNamedItemNumber(token+secondline+1))<=0)
			{
                if (itemnum2 != 0)
                    SCRIPT_ERROR("WARNING: unknown item name or type %s in a drop_ event\n", token+secondline+1);
				*num=0;
				return 1;
			}

			*num=GetSpecificItemPickupEventNum(itemnum, itemnum2);
			token[secondline]='_';

			return 1;
		}

		*num=GetWeaponPickupOrDropEventNum(itemnum, curweapon);

		token[secondline]='_';

		return 1;
	}

	if (strncmp(token, "axed_", 5)==0)
	{
		int secondline=0;
		int i;
		int eArmy;
		int itemnum;

		*type=EVENT_KILLEDSARGE;
		for (i=5;i<(int)strlen(token);i++)
			if (token[i]=='_')
				secondline=i;
		if (!secondline)
		{
			SCRIPT_ERROR("ERROR: an axed event must have a second underline\n");
			return -1;
		}
		token[secondline]=0;

		if ((itemnum=GetNamedItemNumber(token+5))<=0)
		{
            if (itemnum != 0)
                SCRIPT_ERROR("WARNING: Unknown item name %s in an axed event\n", token+4);
			*type=EVENT_CONTROL;
			*num=EVENT_NUM_UNDEFINED;
			return 1;
		}

		if ((eArmy=StringToArmy(token+secondline+1))<0)
		{
			SCRIPT_ERROR("ERROR: unknown army name %s in an axed event\n", token+secondline+1);
			return -1;
		}

		*num=GetKillerEventNum(itemnum, gpComm->IndexFromColor((ARMY_COLOR)eArmy));

		token[secondline]='_';

		return 1;
	}
			  



	{
		int i;
		for (i=0;i<(int)strlen(token);i++)
			if (token[i]=='_')
			{
				SCRIPT_ERROR("ERROR: unexpected underscore found in event name %s\n"
                    ,token);
				return -1;
			}
	}

		

	*type=EVENT_CONTROL;
	if (strcmp(token, "ALL")==0)
		*num=EVENT_NUM_ALL;
	else if ((*num=GetControlEventNum(token))<0)
	{
		SCRIPT_ERROR("ERROR while getting event number from name %s\n", token);
		return -1;
	};
	return 1;

}


int GetMultipleEventsFromTokens(char tokens[][TOKENLENGTH], int numtokens, COMPOUND_EVENT *curcompoundevent)
{
	int curtoken=0;
	
	if (numtokens<1)
	{
		SCRIPT_ERROR("ERROR: not enough tokens for an event list\n");
		return -1;
	}

	while ((curtoken<numtokens) && (gettokentype(tokens[curtoken])==TOKEN_TYPE_STRING))
	{
		EVENT_TYPE curtype;
		int curnum;

		if (curcompoundevent->numevents==16)
		{
			SCRIPT_ERROR("ERROR: too many events for a single compound event > 15\n");
            ShowTokenContext(tokens,curtoken);
			return -1;
		}
	
		if (GetEventFromToken(tokens[curtoken], &curtype, &curnum)<0)
		{
			SCRIPT_ERROR("ERROR: not able to decipher event %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			return -1;
		}

		curcompoundevent->types[curcompoundevent->numevents]=curtype;
		curcompoundevent->nums[curcompoundevent->numevents]=curnum;
		curcompoundevent->numevents++;

		curtoken++;
	}


	return curtoken;

}

#define CHECKBOUNDS if (curtoken==numtokens) { TRACE("ERROR: Ran out of tokens\n"); goto error; }

int findtoken(char tokens[][TOKENLENGTH], int numtokens, int *curtoken, char *whichtoken)
{
	if (*curtoken==numtokens)
		return -1;
	if (strcmp(tokens[*curtoken], whichtoken)!=0)
	{
		SCRIPT_ERROR("ERROR: was looking for token %s but found token %s\n", whichtoken, tokens[*curtoken]);
        ShowTokenContext(tokens,*curtoken);
		return -1;
	}
	(*curtoken)++;
	return 0;
}

char *tokentypenames[]=
{
	"TOKEN_TYPE_UNKNOWN",
	"TOKEN_TYPE_NEWLINE",
	"TOKEN_TYPE_CONTROLCHAR",
	"TOKEN_TYPE_STRING",
	"TOKEN_TYPE_NUMBER",
	"TOKEN_TYPE_RESERVEDWORD",
	"TOKEN_TYPE_MESSAGE"
};

#define FINDTOKEN(s) if (findtoken(tokens, numtokens, &curtoken, s)<0) {TRACE("ERROR: couldn't find expected token %s.\n", s, curtoken); goto error; }

#define CHECKTOKENTYPE(t) {CHECKBOUNDS; if (gettokentype(tokens[curtoken])!=t) {TRACE("ERROR: couldn't find expected token type %s. Found token %s\n", tokentypenames[t], tokens[curtoken]); goto error; }}



int GenerateUIDFromTokens(char tokens[][TOKENLENGTH], int numtokens, long *uidtoset)
{
	ITEM *tempitem;
	int tempitemnum;
	int curtoken=0;

	CHECKBOUNDS;

	if (strcmp(tokens[curtoken], "GREEN")==0)
	{
		*uidtoset=UID_GREEN;
		return 1;
	}
	if (strcmp(tokens[curtoken], "TAN")==0)
	{
		*uidtoset=UID_TAN;
		return 1;
	}
	if (strcmp(tokens[curtoken], "BLUE")==0)
	{
		*uidtoset=UID_BLUE;
		return 1;
	}
	if (strcmp(tokens[curtoken], "GRAY")==0)
	{
		*uidtoset=UID_GRAY;
		return 1;
	}
	if (strcmp(tokens[curtoken], "ME")==0)
	{
		*uidtoset=UID_ME;
		return 1;
	}


	CHECKTOKENTYPE(TOKEN_TYPE_STRING);
	tempitemnum=GetNamedItemNumber(tokens[curtoken]);
	if (tempitemnum<0)
	{
		SCRIPT_ERROR("WARNING: Unknown item name %s\n", tokens[curtoken]);
		*uidtoset=0;
		return 1;
	}

	tempitem=GetNamedItemPointer(tempitemnum);
	if (!tempitem)
	{
		if (tempitemnum)
		{
			SCRIPT_ERROR("ERROR: could not get an item for number %d\n", tempitemnum);
			goto error;
		}
		else
		{
			*uidtoset=0;
			return 1;
		}
	}

	*uidtoset=tempitem->nUniqueID;

	return 1;

error:
	TRACE("ERROR in GenerateUIDFromTokens\n");
	return -1;
}





int GenerateLocationFromTokens(char tokens[][TOKENLENGTH], int numtokens, THING_TO_DO *thingtodo)
{
	int curtoken=0;
	int temp;
	int result;


	if (gettokentype(tokens[curtoken])==TOKEN_TYPE_CONTROLCHAR)
	{
		FINDTOKEN("(");
		CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);

		thingtodo->position.x=atoi_nonneg(tokens[curtoken]);

		curtoken++;
		FINDTOKEN(",");
		CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);
		
		thingtodo->position.y=atoi_nonneg(tokens[curtoken]);

		curtoken++;
		FINDTOKEN(")");

		return curtoken;
	}
	else
	{
		temp=GetPadNumFromName(tokens[curtoken]);
		if (temp<0)
		{
			result=GenerateUIDFromTokens(tokens, numtokens, &thingtodo->uidtogoto);
			if (result<0)
			{
				SCRIPT_ERROR("ERROR: could not get a UID for a location\n");
				goto error;
			}

			curtoken+=result;

			return curtoken;
		}
		else
		{
			if (MapPadPosition(LogicalPadNumToPhysicalPadNum(temp),&thingtodo->position)<0)
			{
				SCRIPT_ERROR("ERROR while trying to get a map pad position\n");
				goto error;
			}

			curtoken++;

			return curtoken;
		}
	}

error:
	TRACE("ERROR: could not find a valid position\n");
	return -1;
}
	

int GenerateThingToDoFromTokens(char tokens[][TOKENLENGTH], int numtokens, THING_TO_DO *thingtodo)
{
	int curtoken=0;
	int result;

	ZeroMemory(thingtodo, sizeof(THING_TO_DO));
	thingtodo->eventtotrigger=EVENT_NUM_UNDEFINED;

	CHECKBOUNDS;

	if (strcmp(tokens[curtoken], "SETSARGEWEAPON")==0)
	{
		curtoken++;
		
		CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

		if (strcmp(tokens[curtoken], "PRIMARY")==0)
			thingtodo->whichweapon=SARGE_WEAPON_PRIMARY;
		else if (strcmp(tokens[curtoken], "SECONDARY")==0)
			thingtodo->whichweapon=SARGE_WEAPON_SECONDARY;
		else if (strcmp(tokens[curtoken], "SPECIAL")==0)
			thingtodo->whichweapon=SARGE_WEAPON_SPECIAL;
		else
		{
			SCRIPT_ERROR("ERROR: unknown sarge weapon %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken++;

		CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

		if ((thingtodo->weapontype=StringToWeapon(tokens[curtoken]))==ARMY_NO_WEAPON)
		{

			SCRIPT_ERROR("ERROR: unknown weapon type %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken++;

		if (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER)
		{
			thingtodo->ammo=atoi_nonneg(tokens[curtoken]);
			curtoken++;
		}
		else
			thingtodo->ammo=-1;

		return curtoken;
	}

	if (strcmp(tokens[curtoken], "SETTRIGGER")==0)
	{
		thingtodo->ordertogive=ORDERTOGIVE_SETTRIGGER;
		curtoken++;
		CHECKBOUNDS;

		if ((result=GetEventFromToken(tokens[curtoken], &thingtodo->typetotrigger, &thingtodo->eventtotrigger))<0)
		{
			SCRIPT_ERROR("ERROR: unable to interpret event name %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;
		return curtoken;
	}

	if (strcmp(tokens[curtoken], "TRIGGER")==0)
	{
		curtoken++;
		CHECKBOUNDS;

		if ((result=GetEventFromToken(tokens[curtoken], &thingtodo->typetotrigger, &thingtodo->eventtotrigger))<0)
		{
			SCRIPT_ERROR("ERROR: unable to interpret event name %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;
		return curtoken;
	}

	if (strcmp(tokens[curtoken], "TRIGGERDELAY")==0)
	{
		curtoken++;

		if (!(gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER || 
				gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER_WITH_DECIMAL_POINT))
		{
			SCRIPT_ERROR("ERROR: expected a number after TRIGGERDELAY\n");
			ShowTokenContext(tokens, curtoken);
			goto error;
		}

		thingtodo->delay=processNumberWithDecimalPoint(tokens[curtoken]);
		if (thingtodo->delay<0)
		{
			SCRIPT_ERROR("ERROR: negative time set for a TRIGGERDELAY\n");
			ShowTokenContext(tokens, curtoken);
			goto error;
		}

		curtoken++;

		CHECKBOUNDS;

		if ((result=GetEventFromToken(tokens[curtoken], &thingtodo->typetotrigger, &thingtodo->eventtotrigger))<0)
		{
			SCRIPT_ERROR("ERROR: unable to interpret event name %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;
		return curtoken;
	}


	if (strcmp(tokens[curtoken], "SHOWMESSAGE")==0)
	{
		curtoken++;
		CHECKTOKENTYPE(TOKEN_TYPE_MESSAGE);

		thingtodo->messagetosend=scriptmessages[atoi_nonneg(tokens[curtoken]+1)];
		thingtodo->MessageType = REAL_MESSAGE;

		curtoken++;
		return curtoken;
	}
	if (strcmp(tokens[curtoken], "DUMPMESSAGE")==0)
	{
		curtoken++;
		CHECKTOKENTYPE(TOKEN_TYPE_MESSAGE);

		thingtodo->messagetosend=scriptmessages[atoi_nonneg(tokens[curtoken]+1)];
		thingtodo->MessageType = DUMP_MESSAGE;
		curtoken++;
		return curtoken;
	}


	if (strcmp(tokens[curtoken], "AUDIO")==0)
	{
		thingtodo->ordertogive=ORDERTOGIVE_AUDIOMODE;

		curtoken++;
		CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

		if (strcmp(tokens[curtoken], "HIGHINTENSITY")==0)
		{
			curtoken++;

			thingtodo->genericcounter=SCRIPT_AUDIO_HIGHINTENSITY;
		}
		else if (strcmp(tokens[curtoken], "LOWINTENSITY")==0)
		{
			curtoken++;

			thingtodo->genericcounter=SCRIPT_AUDIO_LOWINTENSITY;
		}
		else
		{
			SCRIPT_ERROR("ERROR: did not find expected AUDIO subcommand\n");
			ShowTokenContext(tokens, curtoken);
			goto error;
		}

		return curtoken;

	}


	if (strcmp(tokens[curtoken], "CINEMA")==0)
	{
		thingtodo->ordertogive=ORDERTOGIVE_CINEMAMODE;

		curtoken++;
		CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

		if (strcmp(tokens[curtoken], "ENABLE")==0)
		{
			curtoken++;

			thingtodo->genericcounter=CINEMA_ENABLE;
		}
		else if (strcmp(tokens[curtoken], "DISABLE")==0)
		{
			curtoken++;

			thingtodo->genericcounter=CINEMA_DISABLE;
		}
		else if (strcmp(tokens[curtoken], "SCROLLTO")==0)
		{
			curtoken++;
			thingtodo->genericcounter=CINEMA_SCROLLTO;
	
			if ((result=GenerateLocationFromTokens(tokens+curtoken, numtokens-curtoken, thingtodo))<0)
				{
					SCRIPT_ERROR("ERROR while finding a location for a cinema scrollto\n");
					ShowTokenContext(tokens,curtoken);
					goto error;
				}

			curtoken+=result;

			thingtodo->ammo=100; //default is full speed

			if ( (curtoken<numtokens) && (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER))
			{
				thingtodo->ammo=atoi_nonneg(tokens[curtoken]);

				curtoken++;
			}
		}
		else if (strcmp(tokens[curtoken], "JUMPTO")==0)
		{
			curtoken++;
			thingtodo->genericcounter=CINEMA_JUMPTO;
	
			if ((result=GenerateLocationFromTokens(tokens+curtoken, numtokens-curtoken, thingtodo))<0)
				{
					SCRIPT_ERROR("ERROR while finding a location for a cinema jumpto\n");
					ShowTokenContext(tokens,curtoken);
					goto error;
				}

			curtoken+=result;

		}
		else
		{
			SCRIPT_ERROR("ERROR: did not find expected CINEMA subcommand\n");
			ShowTokenContext(tokens, curtoken);
			goto error;
		}

		return curtoken;

	}

	if (strcmp(tokens[curtoken], "PLAYSTREAM")==0)
	{
		thingtodo->ordertogive=ORDERTOGIVE_PLAYSTREAM;

		curtoken++;

		CHECKBOUNDS;

		if (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER)
		{
			thingtodo->eventtotriggeroncethere=atoi_nonneg(tokens[curtoken]);
			curtoken++;

			if (curtoken==numtokens || gettokentype(tokens[curtoken])!=TOKEN_TYPE_STRING)
			{
				thingtodo->uidtoorder=0;
				return curtoken;
			}


			result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
			if (result<0)
			{
				SCRIPT_ERROR("ERROR: Unable to find a unit to play a stream about\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}
			curtoken+=result;

			return curtoken;
		}
		else
		{
			thingtodo->eventtotriggeroncethere=audioFindIDbyName(tokens[curtoken]);
			curtoken++;

			if (curtoken==numtokens || gettokentype(tokens[curtoken])!=TOKEN_TYPE_STRING)
			{
				thingtodo->uidtoorder=0;
				return curtoken;
			}

		
			result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		
			if (result<0)
			{
				SCRIPT_ERROR("ERROR: Unable to find a unit to play a stream about\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken+=result;

			return curtoken;
		
		}

	}

	if (strcmp(tokens[curtoken], "PLAYSOUNDLOOP")==0)
	{
		thingtodo->ordertogive=ORDERTOGIVE_PLAYSOUNDLOOP;

		curtoken++;

		CHECKBOUNDS;

		if (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER)
		{
			thingtodo->eventtotriggeroncethere=atoi_nonneg(tokens[curtoken]);
			curtoken++;

			thingtodo->uidtoorder=0;
			return curtoken;
		}
		else
		{
			thingtodo->eventtotriggeroncethere=audioFindIDbyName(tokens[curtoken]);
			curtoken++;

			thingtodo->uidtoorder=0;
			return curtoken;
		}
	}

	if (strcmp(tokens[curtoken], "ENDSOUNDLOOP")==0)
	{
		thingtodo->ordertogive=ORDERTOGIVE_ENDSOUNDLOOP;

		curtoken++;

		CHECKBOUNDS;

		if (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER)
		{
			thingtodo->eventtotriggeroncethere=atoi_nonneg(tokens[curtoken]);
			curtoken++;

			thingtodo->uidtoorder=0;
			return curtoken;
		}
		else
		{
			thingtodo->eventtotriggeroncethere=audioFindIDbyName(tokens[curtoken]);
			curtoken++;

			thingtodo->uidtoorder=0;
			return curtoken;
		}
	}


	if (strncmp(tokens[curtoken], "INVULNERABLE", strlen("INVULNERABLE"))==0)
	{
		thingtodo->ordertogive=ORDERTOGIVE_INVULNERABLE;
		curtoken++;
		return curtoken;
	}


	if (strncmp(tokens[curtoken], "VULNERABLE", strlen("VULNERABLE"))==0)
	{
		thingtodo->ordertogive=ORDERTOGIVE_NORMAL;
		curtoken++;
		return curtoken;
	}

	
	if (strcmp(tokens[curtoken], "HEAL")==0)
	{

		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_HEALUNIT;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit to heal\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;

		if ((curtoken<numtokens) && (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER))
		{
			thingtodo->genericcounter=atoi_nonneg(tokens[curtoken]);
			curtoken++;
		}
		else
			thingtodo->genericcounter=100;

		return curtoken;
	}

	if (strcmp(tokens[curtoken], "SETUSERCONTROL")==0)
	{
		int result;

		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_SETUSERCONTROL;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit to set user control for\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;

		return curtoken;
	}

	if (strcmp(tokens[curtoken], "SETAICONTROL")==0)
	{
		int result;

		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_SETAICONTROL;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit to set ai control for\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;

		return curtoken;
	}

	if (strcmp(tokens[curtoken], "MERGEUNITS")==0)
	{
		int result;
		
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_MERGEUNITS;


		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);

		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find first unit for a merge\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		
		curtoken+=result;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtogoto);

		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find second unit for a merge\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		
		curtoken+=result;

		return curtoken;
	}


	if (strcmp(tokens[curtoken], "DEPLOY")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_DEPLOY;
        
		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit for an order\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;

		if (strcmp(tokens[curtoken], "ATMODE")!=0)
		{
			if ((result=GenerateLocationFromTokens(tokens+curtoken, numtokens-curtoken, thingtodo))<0)
			{
				SCRIPT_ERROR("ERROR while finding a location for a deployment\n");
				ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken+=result;
		}

		FINDTOKEN("ATMODE");

		CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

		if (strcmp(tokens[curtoken], "IGNORE")==0)
			thingtodo->oncethere=IGNOREFIRE;
		else if (strcmp(tokens[curtoken], "RETURNFIRE")==0)
			thingtodo->oncethere=RETURNFIRE;
		else if (strcmp(tokens[curtoken], "NESTFIRE")==0)
			thingtodo->oncethere=NESTFIRE;
		else if (strcmp(tokens[curtoken], "PRONEFIRE")==0)
			thingtodo->oncethere=PRONEFIRE;
		else if (strcmp(tokens[curtoken], "KNEELFIRE")==0)
			thingtodo->oncethere=KNEELFIRE;
		else if (strcmp(tokens[curtoken], "STANDFIRE")==0)
			thingtodo->oncethere=STANDFIRE;
		else if (strcmp(tokens[curtoken], "ATTACK")==0)
			thingtodo->oncethere=ATTACKFIRE;
		else if (strcmp(tokens[curtoken], "DEFEND")==0)
			thingtodo->oncethere=DEFENDFIRE;
		else if (strcmp(tokens[curtoken], "EVADE")==0)
			thingtodo->oncethere=EVADEFIRE;
		else 
		{
			SCRIPT_ERROR("ERROR: UNKOWN behavior word %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken++;

		return curtoken;
	}

	if (strcmp(tokens[curtoken], "UNDEPLOY")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_UNDEPLOY;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit for an order\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;
		return curtoken;
	}

	if (strcmp(tokens[curtoken], "RECHARGE")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_RECHARGE;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit for an order\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;


        if (strcmp(tokens[curtoken], "HEALTH")==0)
			thingtodo->genericcounter = 1;
		
        else if (strcmp(tokens[curtoken], "AIRSTRIKE")==0)
			thingtodo->genericcounter = 2;
		
        else if (strcmp(tokens[curtoken], "AIRRECON")==0)
			thingtodo->genericcounter = 3;
		
		else
        {
			SCRIPT_ERROR("ERROR: bad recharge label\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
        }
        curtoken++;


		return curtoken;
	}


	if (strcmp(tokens[curtoken], "SHOWBMP")==0)
	{
		curtoken++;
		CHECKTOKENTYPE(TOKEN_TYPE_MESSAGE);

		thingtodo->messagetosend=scriptmessages[atoi_nonneg(tokens[curtoken]+1)];
		thingtodo->MessageType = SHOWBMP_MESSAGE;

		curtoken++;

		return curtoken;
	}

	if (strcmp(tokens[curtoken], "VISIBLE")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_VISIBLE;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit for an order\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;
		return curtoken;
	}
	if (strcmp(tokens[curtoken], "INVISIBLE")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_INVISIBLE;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit for an order\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;
		return curtoken;

	}

	if (strcmp(tokens[curtoken], "NUKE")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_NUKE;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit to NUKE\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;




		return curtoken;
	}

	if (strcmp(tokens[curtoken], "MAKESTRATEGIC")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_MAKESTRATEGIC;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit to MAKESTRATEGIC\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;

		return curtoken;
	}

		if (strcmp(tokens[curtoken], "MAKENONSTRATEGIC")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_MAKENONSTRATEGIC;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit to MAKENONSTRATEGIC\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;

		return curtoken;
	}


	if (strcmp(tokens[curtoken], "AIRSTRIKE")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_AIRSTRIKE;

		if ((result=GenerateLocationFromTokens(tokens+curtoken, numtokens-curtoken, thingtodo))<0)
		{
			SCRIPT_ERROR("ERROR while finding a location for an airstrike\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;

		return curtoken;

	}

	if (strcmp(tokens[curtoken], "AIRDROP")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_AIRDROP;

		if ((result=GenerateLocationFromTokens(tokens+curtoken, numtokens-curtoken, thingtodo))<0)
		{
			SCRIPT_ERROR("ERROR while finding a location for an airdrop\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;

		if ((thingtodo->genericcounter=StringToArmy(tokens[curtoken]))<0)
		{
			SCRIPT_ERROR("ERROR while trying to find an army for an airdrop command\n");
			ShowTokenContext(tokens, curtoken);
			goto error;
		}

		curtoken++;

		return curtoken;
	}





	if (strcmp(tokens[curtoken], "ALLY")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_ALLY;

		CHECKBOUNDS;

		if ((thingtodo->genericcounter=StringToArmy(tokens[curtoken]))<0)
		{
			SCRIPT_ERROR("ERROR while trying to find an army for an ALLY command\n");
			ShowTokenContext(tokens, curtoken);
			goto error;
		}

		curtoken++;
		CHECKBOUNDS;

		if ((thingtodo->ammo=StringToArmy(tokens[curtoken]))<0)
		{
			SCRIPT_ERROR("ERROR while trying to find an army for an ALLY command\n");
			ShowTokenContext(tokens, curtoken);
			goto error;
		}

		curtoken++;

		return curtoken;
	}

	if (strcmp(tokens[curtoken], "UNALLY")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_UNALLY;

		CHECKBOUNDS;

		if ((thingtodo->genericcounter=StringToArmy(tokens[curtoken]))<0)
		{
			SCRIPT_ERROR("ERROR while trying to find an army for an UNALLY command\n");
			ShowTokenContext(tokens, curtoken);
			goto error;
		}

		curtoken++;
		CHECKBOUNDS;

		if ((thingtodo->ammo=StringToArmy(tokens[curtoken]))<0)
		{
			SCRIPT_ERROR("ERROR while trying to find an army for an UNALLY command\n");
			ShowTokenContext(tokens, curtoken);
			goto error;
		}

		curtoken++;

		return curtoken;
	}


	if (strcmp(tokens[curtoken], "EXPLODE")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_EXPLODE;

		if ((result=GenerateLocationFromTokens(tokens+curtoken, numtokens-curtoken, thingtodo))<0)
		{
			SCRIPT_ERROR("ERROR while finding a location for an explosion\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}


		curtoken+=result;

		if ((curtoken<numtokens) && (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER))
		{
			thingtodo->genericcounter=atoi_nonneg(tokens[curtoken]);
			curtoken++;
		}
		else
			thingtodo->genericcounter= -1;

		return curtoken;

	}

	if (strcmp(tokens[curtoken], "REMOVEOBJECT")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_REMOVEOBJECT;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: unable to get object from name %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;

		return curtoken;
	}

	if (strcmp(tokens[curtoken], "PLACEOBJECT")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_PLACEOBJECT;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find an object to place\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;

		
		if ((result=GenerateLocationFromTokens(tokens+curtoken, numtokens-curtoken, thingtodo))<0)
		{
			SCRIPT_ERROR("ERROR while finding a location for an object placement\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;

		return curtoken;
	}
	if (strcmp(tokens[curtoken], "NOTIFY")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_NOTIFY;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find an object to place\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;
		if ((result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtogoto))<0)
		{
			SCRIPT_ERROR("ERROR while finding a location for an object placement\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;

		if ((curtoken<numtokens) && (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER))
		{
			thingtodo->genericcounter=atoi_nonneg(tokens[curtoken]);
			curtoken++;
		}
		else
			thingtodo->genericcounter= -1;

		return curtoken;
	}

	if (strcmp(tokens[curtoken], "RESURRECT")==0)
	{
		curtoken++;
		thingtodo->ordertogive=ORDERTOGIVE_RESURRECT;

		
		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find an item to resurrect\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;

		
		if ((result=GenerateLocationFromTokens(tokens+curtoken, numtokens-curtoken, thingtodo))<0)
		{
			SCRIPT_ERROR("ERROR while finding a location for a resurrection\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;

		return curtoken;
	}





	if (strcmp(tokens[curtoken], "ORDER")==0)
	{
	    int result;
		
		curtoken++;
		
		thingtodo->ontheway=(BEHAVIOR)-1;
		thingtodo->oncethere=(BEHAVIOR)-1;
		thingtodo->eventtotriggeroncethere=EVENT_NUM_UNDEFINED;

		result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtoorder);
		if (result<0)
		{
			SCRIPT_ERROR("ERROR: Unable to find a unit for an order\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken+=result;


		CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

		if (strcmp(tokens[curtoken], "FOLLOW")==0)
		{
			curtoken++;
			thingtodo->ordertogive=ORDERTOGIVE_FOLLOW;

			result=GenerateUIDFromTokens(tokens+curtoken, numtokens-curtoken, &thingtodo->uidtogoto);
			if (result<0)
			{
				SCRIPT_ERROR("ERROR: Unable to find a unit to follow\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}
			curtoken+=result;

			FINDTOKEN("INMODE");

			CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

			if (strcmp(tokens[curtoken], "IGNORE")==0)
				thingtodo->ontheway=IGNOREFIRE;
			else if (strcmp(tokens[curtoken], "RETURNFIRE")==0)
				thingtodo->ontheway=RETURNFIRE;
			else if (strcmp(tokens[curtoken], "NESTFIRE")==0)
				thingtodo->ontheway=NESTFIRE;
			else if (strcmp(tokens[curtoken], "PRONEFIRE")==0)
				thingtodo->ontheway=PRONEFIRE;
            else if (strcmp(tokens[curtoken], "KNEELFIRE")==0)
                thingtodo->ontheway=KNEELFIRE;
			else if (strcmp(tokens[curtoken], "STANDFIRE")==0)
				thingtodo->ontheway=STANDFIRE;
			else if (strcmp(tokens[curtoken], "ATTACK")==0)
				thingtodo->ontheway=ATTACKFIRE;
			else if (strcmp(tokens[curtoken], "DEFEND")==0)
				thingtodo->ontheway=DEFENDFIRE;
			else if (strcmp(tokens[curtoken], "EVADE")==0)
				thingtodo->ontheway=EVADEFIRE;
			else 
			{
				SCRIPT_ERROR("ERROR: UNKOWN behavior word %s\n", tokens[curtoken]);
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken++;


            // optional then clause given
			if (strcmp(tokens[curtoken], "THEN")==0)
            {
                int foundsomething=0;
                curtoken++;
				CHECKBOUNDS;
                
                if (strcmp(tokens[curtoken], "ATMODE")==0)
                {
                    foundsomething=1;
                    curtoken++;
                    CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

                    if (strcmp(tokens[curtoken], "IGNORE")==0)
                        thingtodo->oncethere=IGNOREFIRE;
                    else if (strcmp(tokens[curtoken], "RETURNFIRE")==0)
                        thingtodo->oncethere=RETURNFIRE;
                    else if (strcmp(tokens[curtoken], "NESTFIRE")==0)
                        thingtodo->oncethere=NESTFIRE;
                    else if (strcmp(tokens[curtoken], "PRONEFIRE")==0)
                        thingtodo->oncethere=PRONEFIRE;
                    else if (strcmp(tokens[curtoken], "KNEELFIRE")==0)
                        thingtodo->oncethere=KNEELFIRE;
                    else if (strcmp(tokens[curtoken], "STANDFIRE")==0)
                        thingtodo->oncethere=STANDFIRE;
                    else if (strcmp(tokens[curtoken], "ATTACK")==0)
                        thingtodo->oncethere=ATTACKFIRE;
                    else if (strcmp(tokens[curtoken], "DEFEND")==0)
                        thingtodo->oncethere=DEFENDFIRE;
                    else if (strcmp(tokens[curtoken], "EVADE")==0)
                        thingtodo->oncethere=EVADEFIRE;
                    else 
                    {
                        SCRIPT_ERROR("ERROR: UNKOWN behavior word %s\n",
                            tokens[curtoken]);
                        ShowTokenContext(tokens,curtoken);
                        goto error;
                    }
				curtoken++;
                }

                if (strcmp(tokens[curtoken], "TRIGGER")==0)
                {
                    foundsomething=1;
                    curtoken++;
                    CHECKBOUNDS;

                    if ((result=GetEventFromToken(tokens[curtoken], 
                        &thingtodo->typetotriggeroncethere, &thingtodo->eventtotriggeroncethere))<0)
                    {
                        SCRIPT_ERROR("ERROR: unable to interpret event name %s\n", tokens[curtoken]);
                        ShowTokenContext(tokens,curtoken);
                        goto error;
                    }

                    curtoken+=result;
                }

                if (!foundsomething)
                {
                    SCRIPT_ERROR("ERROR: Found neither TRIGGER nor ATMODE after THEN\n");
                    ShowTokenContext(tokens,curtoken);
                    goto error;
                }

            }
            else // no optional THEN clause after follow
            {
            }

			return curtoken;
		}




		if (strcmp(tokens[curtoken], "GOTO")==0)
		{
			curtoken++;
			thingtodo->ordertogive=ORDERTOGIVE_GOTO;
            thingtodo->ontheway=DEFENDFIRE; // default if unspecified
            thingtodo->oncethere=DEFENDFIRE;// default if unspecified

			if ((result=GenerateLocationFromTokens(tokens+curtoken, numtokens-curtoken, thingtodo))<0)
			{
				SCRIPT_ERROR("ERROR while finding a GOTO location\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken+=result;

			CHECKBOUNDS;

			if (strcmp(tokens[curtoken], "SLOW")==0)
			{
				thingtodo->genericcounter=1;
				curtoken++;
			}

			CHECKBOUNDS;

			if (strcmp(tokens[curtoken], "INMODE")==0)
			{
				curtoken++;
				CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

				if (strcmp(tokens[curtoken], "IGNORE")==0)
					thingtodo->ontheway=IGNOREFIRE;
				else if (strcmp(tokens[curtoken], "RETURNFIRE")==0)
					thingtodo->ontheway=RETURNFIRE;
				else if (strcmp(tokens[curtoken], "NESTFIRE")==0)
					thingtodo->ontheway=NESTFIRE;
				else if (strcmp(tokens[curtoken], "PRONEFIRE")==0)
					thingtodo->ontheway=PRONEFIRE;
                else if (strcmp(tokens[curtoken], "KNEELFIRE")==0)
                    thingtodo->ontheway=KNEELFIRE;
				else if (strcmp(tokens[curtoken], "STANDFIRE")==0)
					thingtodo->ontheway=STANDFIRE;
				else if (strcmp(tokens[curtoken], "ATTACK")==0)
					thingtodo->ontheway=ATTACKFIRE;
				else if (strcmp(tokens[curtoken], "DEFEND")==0)
					thingtodo->ontheway=DEFENDFIRE;
				else if (strcmp(tokens[curtoken], "EVADE")==0)
					thingtodo->ontheway=EVADEFIRE;
				else 
				{
					SCRIPT_ERROR("ERROR: UNKOWN behavior word %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				curtoken++;
			}

			FINDTOKEN("THEN");
	
			int foundsomething=0;

			if (strcmp(tokens[curtoken], "ATMODE")==0)
			{
				foundsomething=1;

				curtoken++;
				CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

				if (strcmp(tokens[curtoken], "IGNORE")==0)
					thingtodo->oncethere=IGNOREFIRE;
				else if (strcmp(tokens[curtoken], "RETURNFIRE")==0)
					thingtodo->oncethere=RETURNFIRE;
				else if (strcmp(tokens[curtoken], "NESTFIRE")==0)
					thingtodo->oncethere=NESTFIRE;
				else if (strcmp(tokens[curtoken], "PRONEFIRE")==0)
					thingtodo->oncethere=PRONEFIRE;
                else if (strcmp(tokens[curtoken], "KNEELFIRE")==0)
                    thingtodo->oncethere=KNEELFIRE;
				else if (strcmp(tokens[curtoken], "STANDFIRE")==0)
					thingtodo->oncethere=STANDFIRE;
				else if (strcmp(tokens[curtoken], "ATTACK")==0)
					thingtodo->oncethere=ATTACKFIRE;
				else if (strcmp(tokens[curtoken], "DEFEND")==0)
					thingtodo->oncethere=DEFENDFIRE;
				else if (strcmp(tokens[curtoken], "EVADE")==0)
					thingtodo->oncethere=EVADEFIRE;
				else 
				{
					SCRIPT_ERROR("ERROR: UNKOWN behavior word %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				curtoken++;
			}

			if (strcmp(tokens[curtoken], "TRIGGER")==0)
			{
				foundsomething=1;

				curtoken++;
				CHECKBOUNDS;

				if ((result=GetEventFromToken(tokens[curtoken], 
						&thingtodo->typetotriggeroncethere, &thingtodo->eventtotriggeroncethere))<0)
				{
					SCRIPT_ERROR("ERROR: unable to interpret event name %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				curtoken+=result;
			}

			if (!foundsomething)
			{
				SCRIPT_ERROR("ERROR: Found neither TRIGGER nor ATMODE after THEN\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			return curtoken;
		}
		
		SCRIPT_ERROR("ERROR: unkown order name %s\n", tokens[curtoken]);
        ShowTokenContext(tokens,curtoken);
		goto error;
	}

// Hey alex, If you know the keyword, you should tell it in the message
// so its easy to know WHAT word is unknown. I fixed this. BW    
	SCRIPT_ERROR("ERROR: unknown keyword %s in GenerateThingToDoFromTokens\n",
        tokens[curtoken]);

error:
	TRACE("ERROR in GenerateThingToDoFromTokens\n");
	return -1;
}



int GenerateCompoundEventFromTokens(char tokens[][TOKENLENGTH], int numtokens)
{
	int curtoken=0, result;
	COMPOUND_EVENT *curcompoundevent=NULL;

	int numthingstodo=0;
	THING_TO_DO tempthingstodo[MAXTHINGSTODO];

	if (numtokens<4)
	{
		SCRIPT_ERROR("ERROR: not enough tokens to generate a compound event\n");
		return -1;
	}

	FINDTOKEN("IF");

	curcompoundevent=(COMPOUND_EVENT*)malloc(sizeof(COMPOUND_EVENT));
	ZeroMemory(curcompoundevent, sizeof(COMPOUND_EVENT));

	if (gettokentype(tokens[curtoken])==TOKEN_TYPE_RESERVEDWORD)
	{
		if (strcmp(tokens[curtoken], "ALLOF")==0)
		{
			curcompoundevent->compoundeventtype=COMPOUNDEVENT_ALLOF;

			curtoken++;

			if ((result=GetMultipleEventsFromTokens(tokens+curtoken, numtokens-curtoken, curcompoundevent))<0)
			{
				SCRIPT_ERROR("ERROR while trying to get events\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken+=result;

			CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

			if (strcmp(tokens[curtoken], "BUTNOT")==0)
			{
				curcompoundevent->compoundeventtype=COMPOUNDEVENT_ALLOF_BUTNOT;

				curtoken++;
				CHECKTOKENTYPE(TOKEN_TYPE_STRING);

				if (curcompoundevent->numevents==16)
				{
					SCRIPT_ERROR("ERROR: Too many events (after a BUTNOT) > 15\n");
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				if (GetEventFromToken(tokens[curtoken], 
						&curcompoundevent->types[curcompoundevent->numevents],
						&curcompoundevent->nums[curcompoundevent->numevents])<0)
				{
					SCRIPT_ERROR("ERROR: unable to interpret event %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);

					goto error;
				}

				curcompoundevent->numevents++;

				curtoken++;
			}
		}
		else if (strcmp(tokens[curtoken], "ONEOF")==0)
		{
			curcompoundevent->compoundeventtype=COMPOUNDEVENT_ONEOF;

			curtoken++;

			if ((result=GetMultipleEventsFromTokens(tokens+curtoken, numtokens-curtoken, curcompoundevent))<0)
			{
				SCRIPT_ERROR("ERROR while trying to get events\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken+=result;

			CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

			if (strcmp(tokens[curtoken], "BUTNOT")==0)
			{
				curcompoundevent->compoundeventtype=COMPOUNDEVENT_ONEOF_BUTNOT;

				curtoken++;
				CHECKTOKENTYPE(TOKEN_TYPE_STRING);

				if (curcompoundevent->numevents==16)
				{
					SCRIPT_ERROR("ERROR: Too many events (after a BUTNOT) > 15\n");
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				if (GetEventFromToken(tokens[curtoken], 
					&curcompoundevent->types[curcompoundevent->numevents],
					&curcompoundevent->nums[curcompoundevent->numevents])<0)
				{
					SCRIPT_ERROR("ERROR: unable to interpret event %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}
			
				curcompoundevent->numevents++;
				curtoken++;

// prove it has a then next
				if (strcmp(tokens[curtoken], "THEN") != 0)
				{
					SCRIPT_ERROR("ERROR: only 1 butnot allowed . THEN expected %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);
					goto error;

				}

			}
		}
		else if (strcmp(tokens[curtoken], "INORDER")==0)
		{
			curcompoundevent->compoundeventtype=COMPOUNDEVENT_INORDER;

			curtoken++;

			if ((result=GetMultipleEventsFromTokens(tokens+curtoken, numtokens-curtoken, curcompoundevent))<0)
			{
				SCRIPT_ERROR("ERROR while trying to get events\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken+=result;

			}
		else if (strcmp(tokens[curtoken], "REPEAT")==0)
		{
			curcompoundevent->compoundeventtype=COMPOUNDEVENT_REPCOUNTOF;
			curtoken++;
			CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);
			curcompoundevent->compoundeventcount=atoi_nonneg(tokens[curtoken]);
			curtoken++;
			FINDTOKEN("OF");

			if ((result=GetMultipleEventsFromTokens(tokens+curtoken, numtokens-curtoken, curcompoundevent))<0)
			{
				SCRIPT_ERROR("ERROR while trying to get events\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken+=result;
		}
		else if (strcmp(tokens[curtoken], "TIMEABSOLUTE")==0)
		{
			curcompoundevent->compoundeventtype=COMPOUNDEVENT_TIMEABSOLUTE;

			curtoken++;

			CHECKBOUNDS;

			if (!(gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER || 
					gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER_WITH_DECIMAL_POINT))
			{
				SCRIPT_ERROR("ERROR: expected a number after TIMEABSOLUTE\n");
				ShowTokenContext(tokens, curtoken);
				goto error;
			}

			curcompoundevent->compoundeventcount=processNumberWithDecimalPoint(tokens[curtoken]);
			if (curcompoundevent->compoundeventcount<0)
			{
				SCRIPT_ERROR("ERROR: negative time set for a TIMEABSOLUTE\n");
				ShowTokenContext(tokens, curtoken);
				goto error;
			}

			curtoken++;
		}
	}
	else if (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER)
	{
		curcompoundevent->compoundeventtype=COMPOUNDEVENT_COUNTOF;
		curcompoundevent->compoundeventcount=atoi_nonneg(tokens[curtoken]);

		curtoken++;
		FINDTOKEN("OF");

		if ((result=GetMultipleEventsFromTokens(tokens+curtoken, numtokens-curtoken, curcompoundevent))<0)
		{
			SCRIPT_ERROR("ERROR while trying to get events\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;
	}
	else if (gettokentype(tokens[curtoken])==TOKEN_TYPE_STRING)
	{
		if (strcmp(tokens[curtoken+1], "AFTER")==0)
		{
			
			curcompoundevent->compoundeventtype=COMPOUNDEVENT_ALLOF_CANCEL;

			while ((curtoken<numtokens) && (gettokentype(tokens[curtoken])==TOKEN_TYPE_STRING))
			{

				if (curcompoundevent->numevents==16)
				{
					SCRIPT_ERROR("ERROR: Too many events > 15 \n");
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				if (GetEventFromToken(tokens[curtoken], 
					&curcompoundevent->types[curcompoundevent->numevents],
					&curcompoundevent->nums[curcompoundevent->numevents])<0)
				{
					SCRIPT_ERROR("ERROR: unable to interpret event %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				curcompoundevent->numevents++;

				curtoken++;

				FINDTOKEN("AFTER");

				if (curcompoundevent->numevents==16)
				{
					SCRIPT_ERROR("ERROR: Too many events > 15 \n");
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				if (GetEventFromToken(tokens[curtoken], 
					&curcompoundevent->types[curcompoundevent->numevents],
					&curcompoundevent->nums[curcompoundevent->numevents])<0)
				{
					SCRIPT_ERROR("ERROR: unable to interpret event %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				curcompoundevent->numevents++;

				curtoken++;

				CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);
				if (strcmp(tokens[curtoken], "AND")==0)
					curtoken++;

			}
		}
		else
		{
			curcompoundevent->compoundeventtype=COMPOUNDEVENT_ONEOF;

			if ((result=GetMultipleEventsFromTokens(tokens+curtoken, numtokens-curtoken, curcompoundevent))<0)
			{
				SCRIPT_ERROR("ERROR while trying to get events\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken+=result;

			CHECKTOKENTYPE(TOKEN_TYPE_RESERVEDWORD);

			if (strcmp(tokens[curtoken], "BUTNOT")==0)
			{
				curcompoundevent->compoundeventtype=COMPOUNDEVENT_ONEOF_BUTNOT;

				curtoken++;
				CHECKTOKENTYPE(TOKEN_TYPE_STRING);

				if (curcompoundevent->numevents==16)
				{
					SCRIPT_ERROR("ERROR: Too many events (after a BUTNOT) > 15\n");
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				if (GetEventFromToken(tokens[curtoken], 
					&curcompoundevent->types[curcompoundevent->numevents],
					&curcompoundevent->nums[curcompoundevent->numevents])<0)
				{
					SCRIPT_ERROR("ERROR: unable to interpret event %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}
			
				curcompoundevent->numevents++;
				curtoken++;
			}
		}
	}
	else
	{
		SCRIPT_ERROR("ERROR: unknown compound event type\n");
        ShowTokenContext(tokens,curtoken);
		goto error;
	}

	FINDTOKEN("THEN");

	CHECKBOUNDS;
	if (strcmp(tokens[curtoken], "RANDOM")==0)
	{
		curcompoundevent->howtodothings=DOTHINGSRANDOM;
		curtoken++;
	}
	else if (strcmp(tokens[curtoken], "SEQUENTIAL")==0)
	{
		curcompoundevent->howtodothings=DOTHINGSSEQUENTIAL;
		curtoken++;
	}

	numthingstodo=0;
	ZeroMemory(tempthingstodo, sizeof(tempthingstodo));

	result=GenerateThingToDoFromTokens(tokens+curtoken, numtokens-curtoken, &tempthingstodo[numthingstodo]);

	if (result<0)
	{
		TRACE("ERROR while trying to generate a thingtodo\n");
        ShowTokenContext(tokens,curtoken);
		goto error;
	}

	curtoken+=result;
	numthingstodo++;

	while ((curtoken<numtokens) && (strcmp(tokens[curtoken], ",")==0))
	{
		if (numthingstodo==MAXTHINGSTODO)
		{
			SCRIPT_ERROR("ERROR: Too many things to do for a single event (limit is %d)\n", MAXTHINGSTODO);
			ShowTokenContext(tokens, curtoken);
			goto error;
		}
		
		curtoken++;
		result=GenerateThingToDoFromTokens(tokens+curtoken, numtokens-curtoken, &tempthingstodo[numthingstodo]);

		if (result<0)
		{
			SCRIPT_ERROR("ERROR while trying to generate a thingtodo\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken+=result;
		numthingstodo++;
	}

	curcompoundevent->numthingstodo=numthingstodo;
	curcompoundevent->thingstodo=(THING_TO_DO*)malloc(sizeof(THING_TO_DO)*numthingstodo);
	memcpy(curcompoundevent->thingstodo, tempthingstodo, sizeof(THING_TO_DO)*numthingstodo);

	//created the event succesfully. link it into the list
	curcompoundevent->next=compound_events;
	compound_events=curcompoundevent;

	return curtoken;


error:

	free(curcompoundevent);
	return -1;
}


 void TurnOnCompoundEvents(void)
{
	COMPOUND_EVENT *c;
	int i;
	int tempevent;

	c=compound_events;
	while (c!=NULL)
	{
		if (c->compoundeventtype==COMPOUNDEVENT_TIMEABSOLUTE)
		{
			// REMOTE NON-HOST CANNOT TRIGGER TIMEABSOLUTE EVENTS. hOST OR ONEPLAYER MUST
			if (GAMETYPE_REMOTE_MULTIPLAYER != gpGame->GameType)
			{
				tempevent=UniqueEventNum();
				// when this event happens, trigger the compound completion checker
				EventRegister(EVENT_CONTROL, tempevent, CompoundEventCallBack, c);
				EventTrigger(EVENT_CONTROL, tempevent, 0, c->compoundeventcount, 1);
			}
		}
		else
			for (i=0;i<c->numevents;i++)
			{
                // when this event happens, trigger the compound completion checker
				EventRegister(c->types[i], c->nums[i], CompoundEventCallBack, c);
			}

		c=c->next;
	}
}

char *eventtypenames[]=
{
	"ALLOF",
	"ONEOF",
	"INORDER",
	"COUNTOF",
	"REPCOUNTOF",
	"TIMEABSOLUTE",
	"ALLOF_CANCEL",
	"ALLOF_BUTNOT",
	"ONEOF_BUTNOT"
};

void printallcompoundevents(void)
{
    return;
    
    if (scriptDebug)
    {
		COMPOUND_EVENT *c;

		c=compound_events;
		while (c!=NULL)
		{
			TRACE("event type %s count %d\n",  eventtypenames[c->compoundeventtype], c->compoundeventcount);

			for (int i=0;i<c->numevents;i++)
				TRACE("listening to event type %d num %d\n", c->types[i], c->nums[i]);
		
			c=c->next;
		}
	}
}



void KillCompoundEvents(void)
{
	COMPOUND_EVENT *cur, *next;

	cur=compound_events;

	while (cur!=NULL)
	{
		next=cur->next;
		if (cur->thingstodo)
			free(cur->thingstodo);
		free(cur);
		cur=next;
	}
}


void SOBJ_SetFrame(SCRIPTED_OBJECT *sobj)
{
	OBJECT *pObj=sobj->pObj;
	OBJECT_SPRITE *curobjectsprite;
	SPOINT position;
	ITEM_OVERLAP overlap;

	if (!sobj->haschanged && !sobj->caninterpolate)
		return;

	sobj->haschanged=0;

	int whichframe=sobj->actualframes[sobj->oldabsoluteframe].animframe;

	if (sobj->caninterpolate)
	{
		float ratio;

		ratio=(((float)(gpGame->dwAnimTime-sobj->lastframetime))/SOBJ_TICKS_PER_FRAME);
		if (ratio<0)
			ratio=0;
		if (ratio>1)
			ratio=1;

		position.x=(short)(sobj->startingposition.x+sobj->actualframes[sobj->oldabsoluteframe].position.x
				+(sobj->actualframes[sobj->newabsoluteframe].position.x-
				sobj->actualframes[sobj->oldabsoluteframe].position.x)*ratio);


		position.y=(short)(sobj->startingposition.y+sobj->actualframes[sobj->oldabsoluteframe].position.y
				+(sobj->actualframes[sobj->newabsoluteframe].position.y-
				sobj->actualframes[sobj->oldabsoluteframe].position.y)*ratio);
	}
	else
	{
		if (sobj->actualframes[sobj->oldabsoluteframe].isrelative)
		{
			position.x=pObj->cell.world_pos.x+sobj->actualframes[sobj->oldabsoluteframe].position.x;
			position.y=pObj->cell.world_pos.y+sobj->actualframes[sobj->oldabsoluteframe].position.y;
		}
		else
		{
			position.x=sobj->startingposition.x+sobj->actualframes[sobj->oldabsoluteframe].position.x;
			position.y=sobj->startingposition.y+sobj->actualframes[sobj->oldabsoluteframe].position.y;
		}
	}

	if( _LOAD_FROM_DATAFILE )
	{
		SPRITE *pSprite;
		AI_ITBL *pAiObjDef;

		if( whichframe >= 0 )
		{
			pAiObjDef = AiGetObjectDefs( pObj->category, pObj->number, whichframe );

			SubtractObjectFromMovementLayer(pObj, &overlap);
			pSprite = AcquireObjectSprite( pObj->category, pObj->number, whichframe );
			if( pSprite )
			{
				pObj->cell.pSprite = pSprite;
				pObj->damageindex=whichframe;
			}
			else
			{
				char name[100];
				name[0] = 0;
				if (pObj->common.label) sprintf(name,"%s",pObj->common.label);
				TRACE( "Error in SOBJ_SetFrame(): Sprite not found for %s cat: %d, num %d, damage %d\n",
					name,pObj->category,pObj->number,whichframe);
			}

			if( pAiObjDef )
			{
				pObj->movement = pAiObjDef->nMovement;
				MoveDispXObject( &(pObj->cell), FALSE );
				if( pAiObjDef->nCrushDamage > 0 )
					AddObjectToMovementLayer( pObj, &overlap, pAiObjDef->nCrushDamage );
				else
					AddObjectToMovementLayer(pObj);
				pObj->common.nStrength = pAiObjDef->nHitPoints;
				pObj->elevation = pAiObjDef->nHeight;
				pObj->visibility = pAiObjDef->nVisibility;
				pObj->permeability = pAiObjDef->nPermeability;
				pObj->armor = pAiObjDef->nArmor;
				pObj->cell.world_pos=position;  
			}
			else
			{
				pObj->cell.world_pos=position;  
				MoveDispXObject( &(pObj->cell), FALSE );
				AddObjectToMovementLayer(pObj);
			}
		}
	}
	else
	{
		curobjectsprite=&the_map.obj_sprite_array_list[pObj->category][pObj->index];

		if ((whichframe>=0) && (whichframe<curobjectsprite->nLevelsOfDamage))
		{			
			SubtractObjectFromMovementLayer(pObj, &overlap);
			pObj->damageindex=whichframe;
			pObj->cell.pSprite=&curobjectsprite->sprites[whichframe];
			pObj->cell.world_pos=position;
  
			MoveDispXObject( &(pObj->cell), FALSE );
	
			AddObjectToMovementLayer(pObj);
		}
	}
	pObj->common.tile = ENCODE_IPOINT( position.x, position.y );
}


int SOBJ_GetStateFirstFrame(SCRIPTED_OBJECT *sobj, int whichstate, int oldabsoluteframe)
{
	SOBJ_STATE *curstate;
	int firstframe=0;
	int i;

	curstate=&sobj->states[whichstate];

	if (curstate->conditional_start_frames)
		for (i=0;i<curstate->numframes;i++)
		  if (curstate->conditional_start_frames[i]==oldabsoluteframe)
			firstframe=i;

	return firstframe;
}
	
void SOBJ_SetNextFrame(SCRIPTED_OBJECT *sobj)
{
	SOBJ_STATE *curstate;
	SOBJ_FRAME *curframe;

	curstate=&sobj->states[sobj->oldstate];

	curframe=&curstate->frames[sobj->oldframeinstate];


	switch(curframe->command)
	{
	case SOBJ_COMMAND_NONE:
	case SOBJ_COMMAND_GENERATEEVENT:
		sobj->newstate=sobj->oldstate;
		sobj->newframeinstate=sobj->oldframeinstate+1;
		if (sobj->newframeinstate == curstate->numframes)
		{
			if (curstate->statetype==SOBJ_STATETYPE_LOOP)
				sobj->newframeinstate=0;
			else
				sobj->newframeinstate = curstate->numframes-1;
		}

		break;

	case SOBJ_COMMAND_GOTOSTATE:
		sobj->newstate=curframe->commandnum;
		sobj->newframeinstate=SOBJ_GetStateFirstFrame(sobj, sobj->newstate, sobj->oldabsoluteframe);
		break;

	case SOBJ_COMMAND_CONDITIONALGOTO:
		{
			int foundgoto=0;
			int i;
		
			for (i=0;i<curframe->commandnum;i++)
				if ((curframe->gotonodes[i].type==EVENT_SOBJ_DEFAULT) ||
				    (curframe->gotonodes[i].hasithappened))
					{
						sobj->newstate=curframe->gotonodes[i].newstate;
						sobj->newframeinstate=SOBJ_GetStateFirstFrame(sobj, sobj->newstate, sobj->oldabsoluteframe);
						foundgoto=1;
						break;
					}
			
			if (!foundgoto)
			{
				sobj->newstate=sobj->oldstate;
				sobj->newframeinstate=sobj->oldframeinstate+1;
				if (sobj->newframeinstate == curstate->numframes)
				{
				if (curstate->statetype==SOBJ_STATETYPE_LOOP)
					sobj->newframeinstate=0;
				else
					sobj->newframeinstate = curstate->numframes-1;
				}
			}
		}
		break;

	}

	sobj->newabsoluteframe=sobj->states[sobj->newstate].frames[sobj->newframeinstate].actualframe;
	if (sobj->oldabsoluteframe==sobj->newabsoluteframe)
		sobj->caninterpolate=0;
	else if (sobj->actualframes[sobj->oldabsoluteframe].animframe==sobj->actualframes[sobj->newabsoluteframe].animframe)
		sobj->caninterpolate=1;
	else
		sobj->caninterpolate=0;

}

	

void SOBJ_SetState(SCRIPTED_OBJECT *sobj, int whichstate, int whichframe)
{
	int previousabsoluteframe;
	SOBJ_FRAME *curframe;
	SOBJ_STATE *curstate;

	previousabsoluteframe=sobj->oldabsoluteframe;

	sobj->oldstate=whichstate;
	sobj->oldframeinstate=whichframe;

	curstate=&sobj->states[whichstate];
	curframe=&curstate->frames[whichframe];

	sobj->oldabsoluteframe=curframe->actualframe;

	if (curframe->command==SOBJ_COMMAND_GENERATEEVENT)
		EventTrigger(curframe->eventtype, curframe->commandnum, sobj->pObj->common.nUniqueID, 0, 0);


	if ((sobj->caninterpolate) || (sobj->oldabsoluteframe!=previousabsoluteframe))
		sobj->haschanged=1;
	else
		sobj->haschanged=0;


	SOBJ_SetNextFrame(sobj);

}

void SOBJ_Setup(SCRIPTED_OBJECT *sobj)
{
	sobj->oldstate=0;
	sobj->oldframeinstate=SOBJ_GetStateFirstFrame(sobj, 0, -1);
	sobj->oldabsoluteframe=sobj->states[sobj->oldstate].frames[sobj->oldframeinstate].actualframe;

	SOBJ_SetNextFrame(sobj);

	sobj->haschanged=0;

	sobj->lastframetime=gpGame->dwAnimTime;

}

void SOBJ_Process(SCRIPTED_OBJECT *sobj)
{
	if (!sobj->active)
		return;


	sobj->pObj->triggers |= TRIGGER_CHANGED;

	if (sobj->lastframetime==0)
		sobj->lastframetime=gpGame->dwAnimTime-SOBJ_TICKS_PER_FRAME;

	if ((int)gpGame->dwAnimTime-sobj->lastframetime>SOBJ_TICKS_PER_FRAME)
	{
		while ((int)gpGame->dwAnimTime-sobj->lastframetime>SOBJ_TICKS_PER_FRAME)
		{
			SOBJ_SetState(sobj, sobj->newstate, sobj->newframeinstate);
			sobj->lastframetime+=SOBJ_TICKS_PER_FRAME;
		}

		SOBJ_SetFrame(sobj);
	}
	else
		if ((sobj->caninterpolate) || (sobj->haschanged))
			SOBJ_SetFrame(sobj);
}

void SOBJ_ProcessEvent(SCRIPTED_OBJECT *sobj, EVENT_TYPE type, int num)
{
	SOBJ_STATE *oldstate;
	SOBJ_EVENT_RESPONSE_NODE *n;
	int i;

	if (!sobj->active)
		return;

	oldstate=&sobj->states[sobj->oldstate];

	for (i=0;i<oldstate->numevents;i++)
	{
		n=&oldstate->events[i];
		if (n->triggeringtype==type && (n->triggeringnum==EVENT_NUM_ALL || n->triggeringnum==num))
		{
			if (n->triggerednum>=0)
				EventTrigger(n->triggeredtype, n->triggerednum, sobj->pObj->common.nUniqueID, 0, 0);
			if (n->newstate>=0)
			{
				SOBJ_SetState(sobj, n->newstate, SOBJ_GetStateFirstFrame(sobj, n->newstate, sobj->oldabsoluteframe));
				sobj->lastframetime=gpGame->dwAnimTime;
			}
		}
	}
}

void SOBJ_Damage(SCRIPTED_OBJECT *sobj, int olddamage, int newdamage)
{
	int i;

	if (!sobj->active)
		return;

	for (i=0;i<sobj->numdamagetriggers;i++)
		if (olddamage>sobj->damagetriggers[i] && newdamage <= sobj->damagetriggers[i])
			SOBJ_ProcessEvent(sobj, EVENT_SOBJ_DAMAGE, 0);
}

void SOBJ_Callback(EVENT_TYPE type, int num, long uid, void *userdata)
{
	SOBJ_ProcessEvent((SCRIPTED_OBJECT*)userdata, type, num);
}

void SOBJ_ConditionalGoto_Callback(EVENT_TYPE type, int num, long uid, void *userdata)
{
	SOBJ_CONDITIONAL_GOTO_NODE *gotonode;

	gotonode=(SOBJ_CONDITIONAL_GOTO_NODE*) userdata;

	gotonode->hasithappened=1;
}



void SOBJ_ProcessAll(void)
{
	SCRIPTED_OBJECT *sobj;

	sobj=SOBJ_first;
	while (sobj!=NULL)
	{
		SOBJ_Process(sobj);
		sobj=sobj->next;
	}
}

void SOBJ_ResetStartingPosition(SCRIPTED_OBJECT *sObj)
{
	OBJECT *pObj;
		
	if (!sObj)
		return;

	pObj=sObj->pObj;

	sObj->startingposition=pObj->cell.world_pos;
}

void SOBJ_Deactivate(SCRIPTED_OBJECT *sObj)
{
	if( sObj )
		sObj->active=0;
}


int statenumber(char statenames[128][TOKENLENGTH], int *numnames, char *curname)
{
	int i;

	if (strcmp(curname, "-")==0) return -1;

	for (i=0;i<*numnames;i++)
		if (strcmp(statenames[i], curname)==0)
			return i;

	sprintf(statenames[*numnames], "%s", curname);
	return (*numnames)++;
}


//this function si called internally from SOBJ_GenerateFromTokensInternal. It translates
//the reserved words DONE GO and STOP into the appropriate events.		
int SOBJ_GetEventFromToken(char *token, EVENT_TYPE *type, int *num, int objecteventnum)
{
	if (!token)
		return -1;
	if (token[0]==0)
		return -1;

	if (strcmp(token, "GO")==0)
	{
		*type=EVENT_ITEMGO;
		*num=objecteventnum;
		return 1;
	}

	if (strcmp(token, "STOP")==0)
	{
		*type=EVENT_ITEMSTOP;
		*num=objecteventnum;
		return 1;
	}

	if (strcmp(token, "DONE")==0)
	{
		*type=EVENT_ITEMGO;
		*num=objecteventnum;
		return 1;
	}

	return GetEventFromToken(token, type, num);
}

#define  MAXNUMFRAMES 1024
int SOBJ_GenerateFromTokensInternal(char tokens[][TOKENLENGTH], int numtokens, OBJECT *pObj)	
{
	SCRIPTED_OBJECT *sobj;
	SOBJ_STATE tempstates[128];
	SOBJ_EVENT_RESPONSE_NODE tempnodes[16];
	SOBJ_CONDITIONAL_GOTO_NODE tempgotonodes[16];
	SOBJ_FRAME tempframes[MAXNUMFRAMES];
	SOBJ_ACTUALFRAME tempactualframes[MAXNUMFRAMES];
	int conditionals[MAXNUMFRAMES];
	int damagetriggers[16];
	int lasttrigger = -1;

	int foundactualframes=0;
	int usingconditionals=0, numstates=0, numnodes=0, numframes=0, numdamagetriggers=0, numactualframes=0;
	int numgotonodes=0;
	int curtoken=0;

	char statenames[128][TOKENLENGTH];
	int numstatenames=0;
	

	int curstatenum;

	int result,i, j;

	if (!pObj->common.eventNum)
	{
		if (GetNewItemNumber((ITEM*)pObj)<0)
		{
			SCRIPT_ERROR("ERROR: Unable to get a new item number\n");
			return -1;
		}
	}

	ZeroMemory(statenames, sizeof(statenames));
	ZeroMemory(tempactualframes, sizeof(tempactualframes));

	sobj=(SCRIPTED_OBJECT*) malloc(sizeof(SCRIPTED_OBJECT));
	ZeroMemory(sobj, sizeof(SCRIPTED_OBJECT));

	ZeroMemory(tempstates, sizeof(tempstates));


	sobj->startingposition=pObj->cell.world_pos;

	CHECKBOUNDS;

	if (strcmp(tokens[curtoken], "FRAMES")==0)
	{

		FINDTOKEN("FRAMES");
		
		FINDTOKEN("\n");

		while ((curtoken<numtokens) && (strcmp(tokens[curtoken], "END")!=0))
		{
			CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);

			if (atoi(tokens[curtoken])!=numactualframes)
			{
				SCRIPT_ERROR("ERROR: the frames must be listed in order\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			curtoken++;

			CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);

			tempactualframes[numactualframes].animframe=atoi_nonneg(tokens[curtoken]);

			curtoken++;

			CHECKBOUNDS;

			if (strcmp(tokens[curtoken], "(")==0)
			{
				curtoken++;

				CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);

				tempactualframes[numactualframes].position.x=atoi(tokens[curtoken]);

				curtoken++;

				FINDTOKEN(",");

				CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);

				tempactualframes[numactualframes].position.y=atoi(tokens[curtoken]);

				curtoken++;

				FINDTOKEN(")");
			}

			CHECKBOUNDS;

			if (strcmp(tokens[curtoken], "+")==0)
			{
				tempactualframes[numactualframes].isrelative=1;
				curtoken++;
			}


			FINDTOKEN("\n");

			numactualframes++;
		}

		FINDTOKEN("END");

		FINDTOKEN("\n");
	
		foundactualframes=1;
	
	}
	else
		for (i=0;i<MAXNUMFRAMES;i++)
			tempactualframes[i].animframe=i;

	while ((curtoken<numtokens) && (strcmp(tokens[curtoken], "STATE")==0))
	{


		curtoken++;
		CHECKTOKENTYPE(TOKEN_TYPE_STRING);
		curstatenum=statenumber(statenames, &numstatenames, tokens[curtoken]);
		if (curstatenum<0)
		{
			SCRIPT_ERROR("ERROR: undefined state name\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		if (curstatenum>=128)
		{
			SCRIPT_ERROR("ERROR: too many states > 127\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		curtoken++;

		CHECKBOUNDS;
		if (strcmp(tokens[curtoken], "LOOP")==0)
		{
			tempstates[curstatenum].statetype=SOBJ_STATETYPE_LOOP;
			curtoken++;
		}

		FINDTOKEN("\n");

		ZeroMemory(tempnodes, sizeof(tempnodes));
		numnodes=0;

		while ((curtoken<numtokens) && (strcmp(tokens[curtoken], "EVENT")==0))
		{
			if (numnodes==16)
			{
				SCRIPT_ERROR("ERROR: too many events for a single state > 15\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}


			curtoken++;

			CHECKBOUNDS;

			if (strcmp(tokens[curtoken], "DAMAGE")==0)
			{
				tempnodes[numnodes].triggeringtype=EVENT_SOBJ_DAMAGE;
				tempnodes[numnodes].triggeringnum=0;
				curtoken++;
			}
			else
			{

				result=SOBJ_GetEventFromToken(tokens[curtoken], &tempnodes[numnodes].triggeringtype, 
					&tempnodes[numnodes].triggeringnum, pObj->common.eventNum);
				if (result<0)
				{
					SCRIPT_ERROR("ERROR while finding an event\n");
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				curtoken+=result;
			}

			FINDTOKEN("(");
			CHECKTOKENTYPE(TOKEN_TYPE_STRING);
			tempnodes[numnodes].newstate=statenumber(statenames, &numstatenames, tokens[curtoken]);
			curtoken++;
			FINDTOKEN(",");

			CHECKBOUNDS;

			if (strcmp(tokens[curtoken], "-")==0)
			{
				tempnodes[numnodes].triggerednum=-1;
				curtoken++;
			}
			else
			{
				int result;

				result=SOBJ_GetEventFromToken(tokens[curtoken], &tempnodes[numnodes].triggeredtype,
					&tempnodes[numnodes].triggerednum, pObj->common.eventNum);
				if (result<0)
				{
					SCRIPT_ERROR("ERROR while finding an event\n");
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}

				curtoken+=result;
			}
			FINDTOKEN(")");
			FINDTOKEN("\n");
			numnodes++;
		}

		FINDTOKEN("BEGIN");
		ZeroMemory(tempframes, sizeof(tempframes));
		numframes=0;
		usingconditionals=0;
		for (i=0;i<MAXNUMFRAMES;i++)
			conditionals[i]=-1000;

		FINDTOKEN("\n");

		while ((curtoken<numtokens) && (strcmp(tokens[curtoken], "END")!=0))
		{
			if (numframes==MAXNUMFRAMES)
			{
				SCRIPT_ERROR("ERROR: too many frames > %d\n",MAXNUMFRAMES-1);
                ShowTokenContext(tokens,curtoken);
				goto error;
			}

			if (strcmp(tokens[curtoken], "(")==0)
			{
				curtoken++;
				usingconditionals=1;
				CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);
				conditionals[numframes]=atoi_nonneg(tokens[curtoken]);
				curtoken++;
				FINDTOKEN(")");
			}

			CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);

			tempframes[numframes].actualframe=atoi_nonneg(tokens[curtoken]);
			if (tempframes[numframes].actualframe>=numactualframes)
			{
				if (foundactualframes)
				{
					SCRIPT_ERROR("ERROR: frame number %d too high\n", tempframes[numframes].actualframe);
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}
				else
					numactualframes=tempframes[numframes].actualframe+1;
			}

			curtoken++;
	
	

			if (gettokentype(tokens[curtoken])==TOKEN_TYPE_RESERVEDWORD)
			{
				if (strcmp(tokens[curtoken], "GOTO")==0)
				{
					tempframes[numframes].command=SOBJ_COMMAND_GOTOSTATE;
					curtoken++;
					CHECKTOKENTYPE(TOKEN_TYPE_STRING);
					tempframes[numframes].commandnum=statenumber(statenames, &numstatenames, tokens[curtoken]);
					curtoken++;
				}
				else if (strcmp(tokens[curtoken], "TRIGGER")==0)
				{
					int result;

					tempframes[numframes].command=SOBJ_COMMAND_GENERATEEVENT;
					lasttrigger = numframes;
					curtoken++;
					CHECKBOUNDS;

					result=SOBJ_GetEventFromToken(tokens[curtoken], &tempframes[numframes].eventtype,
													&tempframes[numframes].commandnum, pObj->common.eventNum);

					if (result<0)
					{
						SCRIPT_ERROR("ERROR in GenerateEventFromToken\n");
                        ShowTokenContext(tokens,curtoken);
						goto error;
					}

					curtoken+=result;
					
				}
				else if (strcmp(tokens[curtoken], "SWITCH")==0)
				{
					numgotonodes=0;
					ZeroMemory(tempgotonodes, sizeof(tempgotonodes));


					curtoken++;
					FINDTOKEN("\n");

					CHECKTOKENTYPE(TOKEN_TYPE_STRING);

					while (strcmp(tokens[curtoken], "END")!=0)
					{
						if (numgotonodes==16)
						{
							SCRIPT_ERROR("ERROR: too many SWITCH nodes > 15\n");
                            ShowTokenContext(tokens,curtoken);
							goto error;
						}

						CHECKBOUNDS;

						if (strcmp(tokens[curtoken], "ELSE")==0)
						{
							tempgotonodes[numgotonodes].type=EVENT_SOBJ_DEFAULT;
							curtoken++;
						}
						else
						{
						
							result=SOBJ_GetEventFromToken(tokens[curtoken], &tempgotonodes[numgotonodes].type, &tempgotonodes[numgotonodes].num, pObj->common.eventNum);
							if (result<0)
							{
								SCRIPT_ERROR("ERROR: Unable to get an event in a SWITCH command\n");
                                ShowTokenContext(tokens,curtoken);
								goto error;
							}

							curtoken+=result;

						}

						CHECKTOKENTYPE(TOKEN_TYPE_STRING);

						tempgotonodes[numgotonodes].newstate=statenumber(statenames, &numstatenames, tokens[curtoken]);
						curtoken++;

						FINDTOKEN("\n");

						numgotonodes++;

						CHECKTOKENTYPE(TOKEN_TYPE_STRING);
					}

					FINDTOKEN("END");

					tempframes[numframes].command=SOBJ_COMMAND_CONDITIONALGOTO;
					tempframes[numframes].commandnum=numgotonodes;
					tempframes[numframes].gotonodes=(SOBJ_CONDITIONAL_GOTO_NODE*)malloc(sizeof(SOBJ_CONDITIONAL_GOTO_NODE)*numgotonodes);
					memcpy(tempframes[numframes].gotonodes, tempgotonodes, sizeof(SOBJ_CONDITIONAL_GOTO_NODE)*numgotonodes);

	
				}
				else
				{
					SCRIPT_ERROR("ERROR: unknown command type %s\n", tokens[curtoken]);
                    ShowTokenContext(tokens,curtoken);
					goto error;
				}
			}

			FINDTOKEN("\n");
			numframes++;
		}
		FINDTOKEN("END");
		FINDTOKEN("\n");

		if (numframes == (lasttrigger+1)) 
		{
			char name[100];
			GetEventName(tempframes[lasttrigger].eventtype, tempframes[lasttrigger].commandnum, name);
			TRACE("Possible object script error- %s trigger on last frame- check for infinite loop\n",name);
		}

		if (numframes<1)
		{
			SCRIPT_ERROR("ERROR: found a state with no frames\n");
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		tempstates[curstatenum].numframes=numframes;
		tempstates[curstatenum].frames=(SOBJ_FRAME*)malloc(sizeof(SOBJ_FRAME)*numframes);
		memcpy(tempstates[curstatenum].frames, tempframes, sizeof(SOBJ_FRAME)*numframes);

		if (usingconditionals)
		{
			tempstates[curstatenum].conditional_start_frames=(int*)malloc(sizeof(int)*numframes);
			memcpy(tempstates[curstatenum].conditional_start_frames, conditionals, sizeof(int)*numframes);
		}

		if (numnodes>0)
		{
			tempstates[curstatenum].numevents=numnodes;
			tempstates[curstatenum].events=(SOBJ_EVENT_RESPONSE_NODE*)malloc(sizeof(SOBJ_EVENT_RESPONSE_NODE)*numnodes);
			memcpy(tempstates[curstatenum].events, tempnodes, sizeof(SOBJ_EVENT_RESPONSE_NODE)*numnodes);
		}

		numstates++;
	}

	if (numstates<1)
	{
		SCRIPT_ERROR("ERROR: a scripted object has fewer than 1 state\n");
        ShowTokenContext(tokens,curtoken);
		goto error;
	}

	if (numstatenames!=numstates)
	{
		SCRIPT_ERROR("ERROR: not all referenced states were defined\n");
        ShowTokenContext(tokens,curtoken);
		goto error;
	}

	if ((curtoken<numtokens) && (strcmp(tokens[curtoken], "DAMAGETRIGGERS")==0))
	{
		curtoken++;
		while ((curtoken<numtokens) && (gettokentype(tokens[curtoken])==TOKEN_TYPE_NUMBER))
		{
			if (numdamagetriggers==16)
			{
				SCRIPT_ERROR("ERROR: too many damage triggers > 15\n");
                ShowTokenContext(tokens,curtoken);
				goto error;
			}
			damagetriggers[numdamagetriggers++]=atoi_nonneg(tokens[curtoken++]);
		}

		sobj->numdamagetriggers=numdamagetriggers;
		sobj->damagetriggers=(int*)malloc(sizeof(int)*numdamagetriggers);
		memcpy(sobj->damagetriggers, damagetriggers, sizeof(int)*numdamagetriggers);
	
	
		FINDTOKEN("\n");
	}

	FINDTOKEN("ENDOBJECT");
	if (curtoken!=numtokens)
		FINDTOKEN("\n");

	sobj->pObj=pObj;
	pObj->sobj=sobj;

	sobj->numstates=numstates;
	sobj->states=(SOBJ_STATE*)malloc(sizeof(SOBJ_STATE)*numstates);
	memcpy(sobj->states, tempstates, sizeof(SOBJ_STATE)*numstates);

	sobj->numactualframes=numactualframes;
	sobj->actualframes=(SOBJ_ACTUALFRAME*)malloc(sizeof(SOBJ_ACTUALFRAME)*numactualframes);
	memcpy(sobj->actualframes, tempactualframes, sizeof(SOBJ_ACTUALFRAME)*numactualframes);

	sobj->next=SOBJ_first;
	SOBJ_first=sobj;

	SOBJ_Setup(sobj);

	return curtoken;

error:

	if (sobj->actualframes)
		free(sobj->actualframes);

	if (sobj->states)
		free(sobj->states);

	if (sobj->damagetriggers)
		free(sobj->damagetriggers);

	for (i=0;i<numstates;i++)
	{
		if (tempstates[i].frames)
		{
			for (j=0;j<tempstates[i].numframes;j++)
				if (tempstates[i].frames[j].gotonodes)
					free(tempstates[i].frames[j].gotonodes);
			free(tempstates[i].frames);
		}

		if (tempstates[i].conditional_start_frames)
			free(tempstates[i].conditional_start_frames);

		if (tempstates[i].events)
			free(tempstates[i].events);
	}

	return -1;

}

char *obj_category_dirs[] = {	
	"Rock",
	"Bush",
	"Tree",
	"BigTree",
	"FallenTree",
	"Fence",
	"Wall",
	"Bridge",
	"FootBridge",
	"Explosives",
	"GunTurret", //10
	"AAGun",
	"Base",
	"Auxbase",
	"AirStrip",
	"HeliPad",
	"PrisonCamp",
	"Building",
	"PillBox",
	"PowerPlant",
	"Gate",
	"WallGate",
	"RadarBuilding",
	"Miscellaneous",
	"Overpass",
	"Sitems"
};


int SOBJ_GenerateFromTokens(char tokens[][TOKENLENGTH], int numtokens)	
{

	int curtoken=0;
	ITEM *pItem;
	OBJECT *pObj;
	int objectnum;
	int result;
	int i,j;
	OBJECT dummyobject;
	char *classname;
	


	FINDTOKEN("OBJECT");
	CHECKBOUNDS;

	if (gettokentype(tokens[curtoken])==TOKEN_TYPE_STRING)
	{
		objectnum=GetNamedItemNumber(tokens[curtoken]);
		if (objectnum<0)
		{
			SCRIPT_ERROR("ERROR: unknown or improper object name %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			goto error;
		}
		curtoken++;

		FINDTOKEN("\n");

		pItem=GetNamedItemPointer(objectnum);

		if (!pItem)
		{
			SCRIPT_ERROR("ERROR: unable to get item pointer for item %s\n", tokens[curtoken]);
			ShowTokenContext(tokens,curtoken);
			goto error;

		}

		if (!IS_ARMY_OBJECT(ITEM_TYPE(pItem)))
		{
			SCRIPT_ERROR("ERROR: attempted to attach an object script to a non-object item %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			goto error;
		}

		pObj=(OBJECT*)pItem;

		result=SOBJ_GenerateFromTokensInternal(tokens+curtoken, numtokens-curtoken, pObj);

		if (result<0)
		{
			SCRIPT_ERROR("ERROR in SOBJ_GenerateFromTokensInternal\n");
            ShowTokenContext(tokens,curtoken);
			return -1;
		}

		return curtoken+result;
	}
	else
	{
		FINDTOKEN("CLASS");

		CHECKTOKENTYPE(TOKEN_TYPE_STRING);

		classname=tokens[curtoken];

		curtoken++;

		CHECKTOKENTYPE(TOKEN_TYPE_NUMBER);
		objectnum=atoi_nonneg(tokens[curtoken]);

		curtoken++;

		FINDTOKEN("\n");

		
		for (i=0;i<(sizeof(obj_category_dirs)/sizeof(char*));i++)
			if (strcmp(classname, obj_category_dirs[i])==0)
			{
				result=-1;

				for (j=0;j<the_map.num_objs[i];j++)
					if (the_map.obj_type_list[i][j].number==objectnum)
					{
						result=SOBJ_GenerateFromTokensInternal(tokens+curtoken, numtokens-curtoken, &the_map.obj_type_list[i][j]);
						if (result<0)
						{
							SCRIPT_ERROR("ERROR in SOBJ_GenerateFromTokensInternal\n");
                            ShowTokenContext(tokens,curtoken);
							return -1;
						}
					
					}

				//if we didn't find any objects of the right type, we need to generate a fake SOBJ just
				//to parse through the object description
				if (result==-1)
				{
					ZeroMemory(&dummyobject, sizeof(dummyobject));
					result=SOBJ_GenerateFromTokensInternal(tokens+curtoken, numtokens-curtoken, &dummyobject);

					if (result<0)
					{
						SCRIPT_ERROR("ERROR while trying to call SOBJ_GenerateFromTokensInternal on the dummy object\n");
                        ShowTokenContext(tokens,curtoken);
						return -1;
					}
				}

				return curtoken+result;
			}
	SCRIPT_ERROR("ERROR: Unable to match string %s with an object class\n", classname);
	return -1;
	
	}
error:
	TRACE("ERROR in SOBJ_GenerateFromTokens\n");
	return -1;
}
		

void SOBJ_TurnOn(void)
{
	SCRIPTED_OBJECT *sobj;
	int i,j,k;

	sobj=SOBJ_first;

	while (sobj!=NULL)
	{
		sobj->active=1;

		for (i=0;i<sobj->numstates;i++)
		{
			for (j=0;j<sobj->states[i].numevents;j++)
			{
				if (sobj->states[i].events[j].triggeringtype!=EVENT_SOBJ_DAMAGE)
					EventRegister(sobj->states[i].events[j].triggeringtype, 
								  sobj->states[i].events[j].triggeringnum, 
								  SOBJ_Callback, sobj);
			}

			for (j=0;j<sobj->states[i].numframes;j++)
				if (sobj->states[i].frames[j].command==SOBJ_COMMAND_CONDITIONALGOTO)
					for (k=0;k<sobj->states[i].frames[j].commandnum;k++)
						if (sobj->states[i].frames[j].gotonodes[k].type!=EVENT_SOBJ_DEFAULT)
							EventRegister(sobj->states[i].frames[j].gotonodes[k].type,
										  sobj->states[i].frames[j].gotonodes[k].num,
										  SOBJ_ConditionalGoto_Callback, &sobj->states[i].frames[j].gotonodes[k]);

		}

		sobj=sobj->next;
	}
}




void SOBJ_print(void)
{
    if (scriptDebug)
    {
	SCRIPTED_OBJECT *sobj;
	int i, j;

	sobj=SOBJ_first;

	while (sobj!=NULL)
	{
		TRACE("scripted object with %d states\n", sobj->numstates);
		for (i=0;i<sobj->numstates;i++)
		{
			TRACE("STATE %d type %d\n has %d events\n", i, sobj->states[i].statetype, sobj->states[i].numevents);
			 for (j=0;j<sobj->states[i].numevents;j++)
			 {
				 TRACE("%d %d %d %d\n", sobj->states[i].events[j].triggeringtype, 
										sobj->states[i].events[j].triggeringnum,
										sobj->states[i].events[j].newstate,
										sobj->states[i].events[j].triggerednum);
			 }


			TRACE("has %d frames\n",sobj->states[i].numframes);
			for (j=0;j<sobj->states[i].numframes;j++)
			{
				if (sobj->states[i].conditional_start_frames)
					TRACE("(%d) ", sobj->states[i].conditional_start_frames[j]);

				switch(sobj->states[i].frames[j].command)
				{
				case SOBJ_COMMAND_NONE:
					break;
				case SOBJ_COMMAND_GENERATEEVENT:
					TRACE("TRIGGEREVENT %d", sobj->states[i].frames[j].commandnum);
					break;
				case SOBJ_COMMAND_GOTOSTATE:
					TRACE("GOTOSTATE %d", sobj->states[i].frames[j].commandnum);
					break;
				}
				TRACE("\n");
			}
		}
		if (sobj->numdamagetriggers>0)
		{
			TRACE("it has %d damage triggers\n", sobj->numdamagetriggers);
			for (j=0;j<sobj->numdamagetriggers;j++)
				TRACE("%d\n", sobj->damagetriggers[j]);
		}
		sobj=sobj->next;
	}
    }
}


void KillScriptedObjects(void)
{
	SCRIPTED_OBJECT *sobj;
	SCRIPTED_OBJECT *nextsobj;
	OBJECT *pObj;

	int i,j;

	sobj=SOBJ_first;

	while (sobj!=NULL)
	{
		nextsobj=sobj->next;

		if (sobj->damagetriggers)
			free(sobj->damagetriggers);

		for (i=0;i<sobj->numstates;i++)
		{
			if (sobj->states[i].frames)
			{
				for (j=0;j<sobj->states[i].numframes;j++)
					if (sobj->states[i].frames[j].gotonodes)
						free(sobj->states[i].frames[j].gotonodes);
				free(sobj->states[i].frames);
			}

			if (sobj->states[i].conditional_start_frames)
				free(sobj->states[i].conditional_start_frames);

			if (sobj->states[i].events)
				free(sobj->states[i].events);
		}

		if (sobj->states)
			free(sobj->states);

		if (sobj->actualframes)
			free(sobj->actualframes);

		pObj=sobj->pObj;
		pObj->sobj = NULL;

		free(sobj);

		sobj=nextsobj;
	}

	SOBJ_first=NULL;
}

typedef char TOKEN[TOKENLENGTH];

int ReadSOBJText(char *sobjtext)
{
	int numtokens, curtoken=0, result;

	TOKEN *tokens;

	tokens=(TOKEN*)malloc(TOKENLENGTH*32768);

	numtokens=TextToTokens(sobjtext, tokens, 32768);

	while (curtoken<numtokens)
	{
		if (strcmp(tokens[curtoken], "OBJECT")==0)
		{
			result=SOBJ_GenerateFromTokens(tokens+curtoken, numtokens-curtoken);
			if (result<0)
			{
				SCRIPT_ERROR("ERROR while trying to read in an SOBJ\n");
                ShowTokenContext(tokens,curtoken);
				free(tokens);
				return -1;
			}

			curtoken+=result;
		}
		else 
		{
			SCRIPT_ERROR("ERROR: unknown inital word %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			free(tokens);
			return -1;
		}
	}

	free(tokens);
	return 0;
}

int ReadMissionText(char *missiontext)
{
	int numtokens, curtoken=0, result;
	char tokens[MAX_TOKENS_PER_SCRIPT][TOKENLENGTH];

	numtokens=TextToTokensNoNewlines(missiontext, tokens, MAX_TOKENS_PER_SCRIPT);
    if (scriptDebug && FALSE)
        for (int i=0;i<numtokens;i++)
            TRACE("%s\n", tokens[i]);

	while (curtoken<numtokens)
	{
		if (strcmp(tokens[curtoken], "PAD")==0)
		{
			result=GeneratePadFromTokens(tokens+curtoken, numtokens-curtoken);
			if (result<0)
			{
				SCRIPT_ERROR("ERROR while trying to read in a pad\n");
                ShowTokenContext(tokens,curtoken);
				return -1;
			}

			curtoken+=result;
		}
		else if (strcmp(tokens[curtoken], "IF")==0)
		{
			result=GenerateCompoundEventFromTokens(tokens+curtoken, numtokens-curtoken);
			if (result<0)
			{
				SCRIPT_ERROR("ERROR while trying to read in a compound event\n");
                ShowTokenContext(tokens,curtoken);
				return -1;
			}
			
			curtoken+=result;
		}
		else 
		{
			SCRIPT_ERROR("ERROR: unknown inital word %s\n", tokens[curtoken]);
            ShowTokenContext(tokens,curtoken);
			return -1;
		}
	}

	return 0;
}

void CallBackPadOn(EVENT_TYPE type, int num, long uid, void *userdata)
{
    if (scriptDebug)
        TRACE("%d.%3d- Pad %d activated\n", nSec,nMilliSec,num);
}
void CallBackPadOff(EVENT_TYPE type, int num, long uid, void *userdata)
{
    if (scriptDebug)
        TRACE("%d.%3d- Pad %d deactivated\n", nSec,nMilliSec,num);
}

void InitScripting(int mission)
{	
	char *missiontext;
	char *objecttext;

	KillScripting();

	EventInit();
	TimerInit();

	InitPads();

	curnumnamedevents=0;
	ZeroMemory(NamedEvents, sizeof(NamedEvents));
	ZeroMemory(UseCount, sizeof(UseCount));

	numscriptmessages=0;
	ZeroMemory(scriptmessages, sizeof(scriptmessages));

	compound_events=NULL;

	SOBJ_first=NULL;

	missiontext=GetMissionText(mission);
	if (missiontext)
	{
		if (ReadMissionText(missiontext)<0)
		{
			TRACE("ERROR in ReadMissionText\n");
   			return;
		}
	}

    // read object scripts only in single player
	if (gpGame->GameType == GAMETYPE_ONEPLAYER)
    {
        objecttext=GetObjectText(mission);
        if (objecttext)
        {
            if (ReadSOBJText(objecttext)<0)
            {
                TRACE("ERROR in ReadObjectText\n");
                return;
            }
        }
    }
    
    if (scriptDebug)
    {
        PrintPads();
        printallcompoundevents();
    }

	EventRegister(EVENT_PADACTIVATED, EVENT_NUM_ALL, CallBackPadOn, NULL);
	EventRegister(EVENT_PADDEACTIVATED, EVENT_NUM_ALL, CallBackPadOff, NULL);

    // these are predefined events we recognize
        
	EventRegister(EVENT_CONTROL, GetControlEventNum("greenwins"), CallBackGreenWins, NULL);
	EventRegister(EVENT_CONTROL, GetControlEventNum("tanwins"), CallBackTanWins, NULL);
	EventRegister(EVENT_CONTROL, GetControlEventNum("bluewins"), CallBackBlueWins, NULL);
	EventRegister(EVENT_CONTROL, GetControlEventNum("graywins"), CallBackGrayWins, NULL);


    // predefined events we send are:
    // startup  greennotplaying  greenleftearly ... for each color

	scripting_on = TRUE;
	StartTimer();
	EventStart();

    // reset script triggered globals
    SetSargeNormal(ARMY_PLAYER);
    SetSargeNormal(ARMY_PLAYER_2);
    SetSargeNormal(ARMY_PLAYER_3);
    SetSargeNormal(ARMY_PLAYER_4);
    ArmyClearAlliance();

    // reset cheats
    immobileFoe = 0;
    cheat_move = 0;
    sargeImmune = 0;
    sargeInvisible = 0;
    Allah = 0;
    labelForces = 0;
    vehicleBehavior = 0;
    explosions = 0;
    routingDraw = 0;

	// warn about single and double use use events
	int i;
	for (i=0;i<curnumnamedevents;i++)
	{
		if (UseCount[i] != 1 ) continue;
		TRACE("Probable script bug- %s event referenced %d times\n",NamedEvents[i].name,1);
	}
}

	
void KillScripting(void)
{
	int i;

	if (!scripting_on)
		return;

	EventShutdown();
	StopTimer();
	KillPads();
	KillCompoundEvents();
	KillScriptedObjects();

	for (i=0;i<numscriptmessages;i++)
		if (scriptmessages[i])
		{
			free(scriptmessages[i]);
			scriptmessages[i]=NULL;
		}

	scripting_on = FALSE;
}

int IsPlaying(int army)
{
    // 1= he is playing  0 = not playing -1 = left during setup

    army =  gpComm->IndexFromColor((ARMY_COLOR)army); // local index
    if (army == 0) return TRUE; // its me
    return (gpComm->IsRemote(army)); 
}

void SendMultiplayerStartupMessages(void)
{
	int eventnum;
	int status;
    status = IsPlaying(ARMY_GREEN);
	if (status == 0)
	{
		eventnum=GetControlEventNum("greennotplaying");
		if (eventnum>0)
			EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
	}
	if (status < 0)
	{
		eventnum=GetControlEventNum("greenleftearly");
		if (eventnum>0)
			EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
	}

    status = IsPlaying(ARMY_TAN);
	if (status == 0)
	{
		eventnum=GetControlEventNum("tannotplaying");
		if (eventnum>0)
			EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
	}
	if (status < 0)
	{
		eventnum=GetControlEventNum("tanleftearly");
		if (eventnum>0)
			EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
	}

    status = IsPlaying(ARMY_BLUE);
	if (status == 0)
	{
		eventnum=GetControlEventNum("bluenotplaying");
		if (eventnum>0)
			EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
	}
	if (status < 0)
	{
		eventnum=GetControlEventNum("blueleftearly");
		if (eventnum>0)
			EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
	}

    status = IsPlaying(ARMY_GRAY);
	if (status == 0)
	{
		eventnum=GetControlEventNum("graynotplaying");
		if (eventnum>0)
			EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
	}
	if (status < 0)
	{
		eventnum=GetControlEventNum("grayleftearly");
		if (eventnum>0)
			EventTrigger(EVENT_CONTROL, eventnum, 0, 0, 1);
	}

}


void StartScripting(void)
{
	int startupnum;

	TRACE("      Starting Scripting\n");


    // here are initial startup messages we trigger
        
    // these occur before startup to help us distinguish players
    // who left before the game started, from players who left later
	if (gpGame->GameType != GAMETYPE_ONEPLAYER)
		SendMultiplayerStartupMessages();

	startupnum=GetControlEventNum("startup");
	if (startupnum>0)
	{
        if (scriptDebug) TRACE("SENDING STARTUP EVENT\n");
		EventTrigger(EVENT_CONTROL, startupnum, 0, 0, 1);
	}
	else if (scriptDebug) TRACE("NO STARTUP EVENT TODAY, CHESTER!\n");

    ArmiesRegenerateDeathEvents(); // resend death events of earlier missions

}














	




			






	














