/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: scripts.h $
//
//	DESCRIPTION:	Headers for handling scripts and state machines
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Thursday, September 4, 1997
//
//	REVISION:		$Header: /ArmyMen/src/scripts.h 75    4/17/98 5:52a Dmaynard $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  1     9/4/97 4:20p Awerner
//
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef _SCRIPTS_H_
#define _SCRIPTS_H_


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "army.h"
#include "event.h"


/////////////////////////////////////////////////////////////////////////////
// defines and typedefs
/////////////////////////////////////////////////////////////////////////////

#define TOKENLENGTH 32


#define TOKEN_TYPE_UNKNOWN 0
#define TOKEN_TYPE_NEWLINE 1
#define TOKEN_TYPE_CONTROLCHAR 2
#define TOKEN_TYPE_STRING 3
#define TOKEN_TYPE_NUMBER 4
#define TOKEN_TYPE_RESERVEDWORD 5
#define TOKEN_TYPE_MESSAGE 6
#define TOKEN_TYPE_NUMBER_WITH_DECIMAL_POINT 7


#define MAXTHINGSTODO 64  // compound event limit

typedef struct
{
	char name[TOKENLENGTH];
	int eventnum;
} NAMED_EVENT;

#define NUM_NAMED_EVENTS 160

#define MAX_NUM_NAMED_ITEMS 256

#define UID_ME (-1)
#define UID_GREEN (-2)
#define UID_TAN (-3)
#define UID_BLUE (-4)
#define UID_GRAY (-5)


#define COMPOUNDEVENT_ALLOF 0
#define COMPOUNDEVENT_ONEOF 1
#define COMPOUNDEVENT_INORDER 2
#define COMPOUNDEVENT_COUNTOF 3
#define COMPOUNDEVENT_REPCOUNTOF 4
#define COMPOUNDEVENT_TIMEABSOLUTE 5
#define COMPOUNDEVENT_ALLOF_CANCEL 6
#define COMPOUNDEVENT_ALLOF_BUTNOT 7
#define COMPOUNDEVENT_ONEOF_BUTNOT 8

#define ORDERTOGIVE_NONE 0
#define ORDERTOGIVE_GOTO 1
#define ORDERTOGIVE_DEPLOY 2
#define ORDERTOGIVE_UNDEPLOY 3
#define ORDERTOGIVE_MERGEUNITS 4
#define ORDERTOGIVE_HEALUNIT 5
#define ORDERTOGIVE_SETUSERCONTROL 6
#define ORDERTOGIVE_SETAICONTROL 7
#define ORDERTOGIVE_FOLLOW 8
#define ORDERTOGIVE_RECHARGE 9
#define ORDERTOGIVE_RESURRECT 10
#define ORDERTOGIVE_AIRSTRIKE 11
#define ORDERTOGIVE_SETSARGEWEAPON 12
#define ORDERTOGIVE_PLAYSTREAM 13
#define ORDERTOGIVE_EXPLODE 14
#define ORDERTOGIVE_REMOVEOBJECT 15
#define ORDERTOGIVE_NUKE 16
#define ORDERTOGIVE_PLACEOBJECT 17
#define ORDERTOGIVE_CINEMAMODE 18
#define ORDERTOGIVE_ALLY 19
#define ORDERTOGIVE_AUDIOMODE 20
#define ORDERTOGIVE_UNALLY 21
#define ORDERTOGIVE_MAKESTRATEGIC 22
#define ORDERTOGIVE_MAKENONSTRATEGIC 23
#define ORDERTOGIVE_VISIBLE 24
#define ORDERTOGIVE_INVISIBLE 25
#define ORDERTOGIVE_AIRDROP 26
#define ORDERTOGIVE_INVULNERABLE 27
#define ORDERTOGIVE_NORMAL 28
#define ORDERTOGIVE_PLAYSOUNDLOOP 29
#define ORDERTOGIVE_ENDSOUNDLOOP 30
#define ORDERTOGIVE_NOTIFY 31
#define ORDERTOGIVE_SETTRIGGER 32

#define DUMP_MESSAGE 0
#define REAL_MESSAGE 1
#define SHOWBMP_MESSAGE 2


typedef enum
{
	DOTHINGSNORMAL,
	DOTHINGSRANDOM,
	DOTHINGSSEQUENTIAL
} THING_TO_DO_CONTROL;

//stuff for cinema mode control
#define CINEMA_ENABLE 0
#define CINEMA_DISABLE 1
#define CINEMA_SCROLLTO 2
#define CINEMA_JUMPTO 3

#define SCRIPT_AUDIO_HIGHINTENSITY 0
#define SCRIPT_AUDIO_LOWINTENSITY 1


typedef struct THING_TO_DO
{
	int eventtotrigger;
	EVENT_TYPE typetotrigger;
	int delay;

	int ordertogive;
	long uidtoorder;
	BEHAVIOR ontheway;
	BEHAVIOR oncethere;
	long uidtogoto;
	SPOINT position; //not used if uidtogoto is nonzero

	int genericcounter; //used for slow, and for percent to heal

	SARGE_WEAPON whichweapon;
	WEAPON_TYPE weapontype;
	char ammo; //-1 if not specified, used for speed of cinema orders and colors for ALLY
	

	int eventtotriggeroncethere;
	EVENT_TYPE typetotriggeroncethere;

	char *messagetosend;
	char MessageType;		// what to do with text message: display msg, dump msg, use text for other command
} THING_TO_DO;

typedef struct COMPOUND_EVENT
{
	int numthingstodo;
	THING_TO_DO *thingstodo;

	THING_TO_DO_CONTROL howtodothings;
	char howto_count; //for sequential things

	char compoundeventtype;
	short compoundeventcount;

	int totalcounter;

	int numevents;

	EVENT_TYPE types[MAXTHINGSTODO];
	int nums[MAXTHINGSTODO];
	int counters[MAXTHINGSTODO];

	COMPOUND_EVENT *next; //linked together for deallocation purposes
} COMPOUND_EVENT;



#define SOBJ_STATETYPE_LOOP 1
#define SOBJ_STATETYPE_NOLOOP 0

#define SOBJ_COMMAND_NONE 0
#define SOBJ_COMMAND_GENERATEEVENT 1
#define SOBJ_COMMAND_GOTOSTATE 2
#define SOBJ_COMMAND_CONDITIONALGOTO 3

#define SOBJ_TICKS_PER_FRAME 67

typedef struct 
{
	EVENT_TYPE type;
	int num;
	char hasithappened;
	int newstate;
} SOBJ_CONDITIONAL_GOTO_NODE;

typedef struct SOBJ_EVENT_RESPONSE_NODE
{
	EVENT_TYPE triggeringtype;
	int	triggeringnum;
	int newstate;
	int triggerednum;
	EVENT_TYPE triggeredtype;
} SOBJ_EVENT_RESPONSE_NODE;


typedef struct SOBJ_FRAME
{
	int actualframe;
	char command;
	int commandnum; //which state to GOTO, or which event to GENERATE, or how many conditional GOTOS there are
	EVENT_TYPE eventtype;
	SOBJ_CONDITIONAL_GOTO_NODE *gotonodes;
} SOBJ_FRAME;

typedef struct SOBJ_STATE
{
	char statetype;

	int numframes;
	SOBJ_FRAME *frames;

	int *conditional_start_frames; //NULL if none

	int numevents;
	SOBJ_EVENT_RESPONSE_NODE *events;
} SOBJ_STATE;

typedef struct
{
	int animframe;
	char isrelative;
	SPOINT position;
} SOBJ_ACTUALFRAME;

typedef struct SCRIPTED_OBJECT
{
	OBJECT *pObj;

	char active;

	int numactualframes;
	SOBJ_ACTUALFRAME *actualframes;

	SPOINT startingposition;

	char caninterpolate;
	char haschanged;

	int oldstate;
	int oldframeinstate;

	int newstate;
	int newframeinstate;

	int oldabsoluteframe;
	int newabsoluteframe;

	int lastframetime;	

	int numstates;
	SOBJ_STATE *states;

	int numdamagetriggers;
	int *damagetriggers;

	SCRIPTED_OBJECT *next;
} SCRIPTED_OBJECT;



typedef struct 
{
	char *streamname;
	int streamnum;
} STREAM_NAME_TO_NUM_ELEMENT;








/////////////////////////////////////////////////////////////////////////////
// function prototypes
/////////////////////////////////////////////////////////////////////////////



void SOBJ_ProcessAll(void);

void InitScripting(int mission);
void KillScripting(void);
void StartScripting(void);

int gettokentype(char *t);
int InitItemNames(void);
int atoi_nonneg(char *s);
int processNumberWithDecimalPoint(char *s);
int GetWeaponPickupOrDropEventNum(int itemnum, WEAPON_TYPE whichweapon);
int GetSpecificItemPickupEventNum(int whoitem, int whatitem);
int GetKillerEventNum(int itemnum, int eArmy);
void SOBJ_Damage(SCRIPTED_OBJECT *sobj, int olddamage, int newdamage);
void SOBJ_ResetStartingPosition(SCRIPTED_OBJECT *sObj);
void SOBJ_Deactivate(SCRIPTED_OBJECT *sObj);
void GetEventName(EVENT_TYPE type, int num, char eventname[256]);
int GetNamedItemNumber(char *name);
BOOL HasEventName(char* name);


#endif