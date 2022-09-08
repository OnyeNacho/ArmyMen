/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: event.h $
//
//	DESCRIPTION:	Headers for handling the event manager
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Tuesday, August 19, 1997
//
//	REVISION:		$Header: /ArmyMen/src/event.h 21    3/27/98 10:06a Bwilcox $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/event.h $
//  
//  21    3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  20    2/03/98 4:46p Awerner
//  added EventsValidate function
//  
//  19    12/09/97 12:12p Phu
//  
//  18    11/17/97 1:59a Bwilcox
//  new event axed_
//  
//  17    11/14/97 3:53p Awerner
//  fixed potential memory leak in delayed events
//  
//  16    11/11/97 5:22p Awerner
//  added clock to dashboard for debugging
//  
//  15    10/16/97 10:19a Awerner
//  Fixed the timer bug and first checkin of new cursor code
//  
//  14    10/14/97 1:41p Awerner
//  Major changes to the scripting code to allow scripts to be assigned to
//  multiple objects of the same class, and cause explosions. Also fixed a
//  bug in the explosion code
//  
//  13    10/09/97 3:30p Awerner
//  Added in events for script recognition of getting and dropping weapons
//  
//  11    9/23/97 1:52p Awerner
//  Implemented new, more legible scripting language
//  
//  10    9/17/97 10:28a Awerner
//  Added in conditional GOTOs in animated object scripts
//  
//  9     9/13/97 5:39p Awerner
//  Added in basis for damage and destruction of items triggering events
//  
//  8     9/11/97 10:54a Awerner
//  Moved some stuff to header files for bruce. Some scripted object code
//  is written but nonfunctional
//  
//  7     9/09/97 2:17p Awerner
//  Events should now work across the network
//  
//  6     9/09/97 1:55p Awerner
//  Changed event code so that events are only triggered on the host
//  machine, and events pass UIDs instead of item pointers
//  
//  5     9/04/97 1:56p Awerner
//  Updated the pad code and the event code, adding
//  delayed events and adding a pointer for a pad layer to
//  the map
//  
//  4     9/03/97 1:43p Awerner
//  First check-in of PAD code
//  
//  3     8/20/97 10:31a Awerner
//  Updated the event manager code, and added versatile timer code
//  
//  2     8/19/97 2:55p Awerner
//  
//  1     8/19/97 2:30p Awerner
//  
//  1     8/19/97 1:37p Awerner
//
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef _EVENT_H_
#define _EVENT_H_


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "army.h"
#include "armymsg.h"
#include "donottouch.h"

/////////////////////////////////////////////////////////////////////////////
// externs
/////////////////////////////////////////////////////////////////////////////

extern char EventsActive; 

/////////////////////////////////////////////////////////////////////////////
// Typedefs and #defines
/////////////////////////////////////////////////////////////////////////////

typedef enum 
{
	EVENT_TILEENTERED,
	EVENT_PADACTIVATED,
	EVENT_PADDEACTIVATED,
	EVENT_ITEMDESTROYED,
	EVENT_ITEMDAMAGED,
	EVENT_ITEMVISON,
	EVENT_ITEMVISOFF,
	EVENT_TIMER,
	EVENT_CONTROL,
	EVENT_ITEMPICKEDUP, //these two events have a number which is the item number plus
	EVENT_ITEMDROPPED,  //the ID number of the unit/sarge which did the action shifted left 8
	EVENT_ITEMGO,	//generic events for interacting with scripted objects
	EVENT_ITEMSTOP,
	EVENT_ITEMDONE,
	EVENT_OTHER,
	EVENT_SOBJ_DAMAGE, //should never be used outside of scripted object code
	EVENT_SOBJ_DEFAULT, //also should never be used outside of the SOBJ code

    //this event haa a number which is the item number plus
    //the army number of the killer army, shifted left 8
	EVENT_KILLEDSARGE, 

	EVENT_LAST
} EVENT_TYPE;

#define EVENT_NUM_ALL -1
#define EVENT_NUM_UNDEFINED -2
#define EVENT_ERROR -100

typedef void (*EventTriggeredFunc)( EVENT_TYPE, int, long, void*);	//the type of function that is called to notify of an event
																	//arguments are the eventtype, the event number,
																	//a pointer to what triggered the event, and
																	//a pointer to the data supplied when registering
																	//with the event manager

typedef struct EVENT_REGISTERED_NODE 
{
	EventTriggeredFunc func;
	void *userdata;
	EVENT_REGISTERED_NODE *next;
} EVENT_REGISTERED_NODE;

typedef struct EVENT_NUMBER_NODE
{
	int whichnum; //-1 for all
	EVENT_REGISTERED_NODE *regnodelist;
	EVENT_NUMBER_NODE *next;
} EVENT_NUMBER_NODE;

typedef struct EVENT_TYPE_NODE
{
	EVENT_NUMBER_NODE *numnodelist;
} EVENT_TYPE_NODE;



typedef struct DELAYED_EVENT_INFO
{
	EVENT_TYPE type;
	int num;
	long uid;
	int removeevent;
	DELAYED_EVENT_INFO *next;
} DELAYED_EVENT_INFO;



//stuff for TIMERs

typedef struct
{
	int nexttime; //the first time, in seconds, when it will go off
	int interval;     //interval between successive goings-off
	int timesremaining; //-1 for infinite
	int eventnum;

	int next;
} TIMER;

#define MAX_NUM_TIMERS 100 //no more than 100 active timers at one time



/////////////////////////////////////////////////////////////////////////////
// Function Prototypes
/////////////////////////////////////////////////////////////////////////////
void EventRegister(EVENT_TYPE type, int num, EventTriggeredFunc func, void *userdata);
void EventTrigger(EVENT_TYPE type, int num, long uid, int delay, int removeevent);
void EventInit(void);
void EventShutdown(void);
void TimerInit(void);
void StartTimer(void);
void StopTimer(void);
int UniqueEventNum(void);
void EventStart(void);
void EventMessageReceive(ARMY_MESSAGE *pArmyMsg);
int GetControlEventNum(char *name);
void UpdateTimer(void);
int getCurTime(void);
void EventsValidate(void);











#endif