/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: event.cpp $
//
//	DESCRIPTION:	Code for the event manager
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Tuesday, August 19, 1997
//
//	REVISION:		$Header: /ArmyMen/src/event.cpp 51    4/17/98 8:43a Nrobinso $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/event.cpp $
//  
//  51    4/17/98 8:43a Nrobinso
//  activate events before starting event stuff
//  
//  50    4/16/98 11:10p Dmaynard
//  Moved TurnOnCompoundEvents and SOBJ_TirnOn  from  InitScripting to
//  Event Start
//  
//  49    4/14/98 10:30a Bwilcox
//  switch playcycle to elapsed time printout,
//  optimize trooper no routing when fail on victim
//  
//  48    4/13/98 10:51a Bwilcox
//  better event fail message
//  
//  47    4/09/98 3:55p Bwilcox
//  discard visibility and damage events in multiplayer
//  
//  45    4/02/98 3:05p Phu
//  
//  44    4/02/98 1:44p Bwilcox
//  cleanups in event triggering and traces
//  
//  43    4/02/98 8:05a Bwilcox
//  better script tracing.
//  troopers now avoid vehicles even if engaged
//  
//  42    3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  41    3/26/98 8:00a Bwilcox
//  cleanups. moved army regen events AFTER startup
//  
//  40    3/05/98 2:27p Dmaynard
//  Removed extraneous 'A' at the beginning of this file.
//  
//  39    3/05/98 10:16a Dmaynard
//  changed an ASSERT to a TRACE and return.
//  
//  38    2/03/98 9:15p Bwilcox
//  fixed assetfire bug, and eventsactive
//  
//  37    2/03/98 7:55p Nrobinso
//  assert if events aren't active when an trigger immediate occurs
//  
//  36    2/03/98 7:40p Nrobinso
//  only validate events if active
//  
//  35    2/03/98 4:46p Awerner
//  added EventsValidate function
//  
//  34    2/03/98 12:13p Phu
//  remove windows timer from event system
//  
//  33    2/03/98 11:16a Bwilcox
//  no longer remove events... too dnagers
//  
//  32    2/02/98 10:37a Bwilcox
//  
//  31    1/29/98 11:03a Dmaynard
//  changed translation of secondary UID in event messages to use the
//  standard functions Global(uid) and Local(uid) to perform the
//  translations.
//  
//  30    1/29/98 10:49a Bwilcox
//  
//  29    1/28/98 8:42p Bwilcox
//  troopers chevron invisible. event tracing improved
//  
//  28    1/28/98 7:21p Bwilcox
//  removing traces
//  
//  27    1/28/98 6:46p Bwilcox
//  
//  26    1/07/98 4:58p Phu
//  modify calls to GetIndexFromColor to allow -1 return values
//  
//  1     8/19/97 1:37p Awerner
//
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ai.h"
#include "AiAccess.h"
#include "army.h"
#include "event.h"
#include "gameflow.h"

#include "ui.h"
#include "comm.h"
/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////

EVENT_TYPE_NODE eventnodes[EVENT_LAST];
extern char scriptDebug;

DELAYED_EVENT_INFO *delayedEventInfo=NULL;

int curtime;
int timepassed;
TIMER timers[MAX_NUM_TIMERS];

int timerlist;
int emptytimerlist;

unsigned int timerID;

char EventsActive=0;

extern void TurnOnCompoundEvents(void);
extern void SOBJ_TurnOn(void);


/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////
static int uniqueeventnum=100000;


int UniqueEventNum(void)
{
//	static int num=100000;

	return uniqueeventnum++;
}

void InsertTimerNode(int whichnode)
{
	int *t;

	t=&timerlist;
	while ((*t!=-1) && (timers[*t].nexttime<=timers[whichnode].nexttime))
	{
		t=&(timers[*t].next);
	}

    timers[whichnode].next=*t;
	*t=whichnode;
}


//this function creates a timer with the specified characteristics,
//optionally with the specified event number, and installs it. It 
//returns the event number
int CreateTimer(int firsttime, int firsttimeabsolute, int interval, int times, int eventnum)
{
	
	if (emptytimerlist==-1)
	{
		TRACE("HORRIBLE ERROR: We appear to have used up all 100 available timers.\n");
		return EVENT_ERROR;
	}

	//if we were passed in a starting time which is relative to the present, 
	//update it
	if (!firsttimeabsolute) 
		firsttime+=curtime;

	//if our starting time already passed
	if (firsttime<=curtime)
	{
		int timesless;
		
		if (firsttime+interval*(times-1)<=curtime)
			return EVENT_NUM_UNDEFINED;

		timesless=(curtime-firsttime)/interval+1;
		firsttime+=timesless*interval;
		times-=timesless;

		if (times<1)
		{
			TRACE("ERROR: after removing invalid timer times, we have fewer than zero left\n");
			return EVENT_ERROR;
		}
		if (firsttime<=curtime)
		{
			TRACE("ERROR: after removing invalid timer times, we still have them. ahh!\n");
			return EVENT_ERROR;
		}
	}

	if (eventnum==EVENT_NUM_UNDEFINED)
		eventnum=UniqueEventNum();


	int temp=emptytimerlist;

	timers[emptytimerlist].nexttime=firsttime;
	timers[emptytimerlist].interval=interval;
	timers[emptytimerlist].timesremaining=times;
	timers[emptytimerlist].eventnum=eventnum;

	emptytimerlist=timers[emptytimerlist].next;

	InsertTimerNode(temp);


	return eventnum;

}



//this function should be called once per second
/*
void CALLBACK TimerTick(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	if (gpGame->IsPaused())
		return;

	tenthofsecondhaspassed=1;
}
*/


int getCurTime(void)
{
	return curtime;
}

//should be called once per frame
void UpdateTimer(void)
{
	if (gpGame->IsPaused() || gpGame->GetSubState() != PLAY_SUB_STATE)
		return;

	timepassed += gpGame->dwDeltaTime;
	if( timepassed > 100 )
	{
		timepassed = 0;
	}
	else
		return;

	curtime++;

	if (timerlist==-1)
		return;

	if (timers[timerlist].nexttime<curtime)
	{
		TRACE("ERROR: we somehow missed a timer tick or something. In any case, the timer list is messed up.\n");
		return;
	}

	if (timers[timerlist].nexttime>curtime)
		return; //nothing to do this tick

	while ((timerlist!=-1) && (timers[timerlist].nexttime==curtime))
	{
		if (scriptDebug)TRACE("Timer event at %d\n",curtime);

		EventTrigger(EVENT_TIMER, timers[timerlist].eventnum, NULL, 0, timers[timerlist].timesremaining==1);
		int temp=timerlist;
		timerlist=timers[timerlist].next;

		if (timers[temp].timesremaining==1)
		{
			timers[temp].next=emptytimerlist;
			emptytimerlist=temp;
		}
		else
		{
			if (timers[temp].timesremaining>1)
				timers[temp].timesremaining--;
			
			timers[temp].nexttime+=timers[temp].interval;

			InsertTimerNode(temp);
		}
	}
}

void StartTimer(void)
{
	curtime=0;
	timepassed = 0;
}


void StopTimer(void)
{
}

			



void TimerInit(void)
{
	int i;

	for (i=0;i<MAX_NUM_TIMERS;i++)
		timers[i].next=i+1;

	timers[MAX_NUM_TIMERS-1].next=-1;
	timerlist=-1;
	emptytimerlist=0;
	curtime=0;


}



void EventMessageSend(EVENT_TYPE type, int num, long uid, int removeevent)
{
	EVENT_MESSAGE msg;
	uid = gpComm->GlobalUID(uid);
	
	msg.nSize=sizeof(EVENT_MESSAGE);
	msg.nUniqueID = 0;
	msg.msg_type=EVENT_MESSAGE_TYPE;

	msg.type=type;
	msg.num=num;
	msg.uid=uid;
	msg.removeevent=removeevent;

  	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}


void EventsValidate(void)
{
	int curtype;
	EVENT_NUMBER_NODE *numnode;
	EVENT_REGISTERED_NODE *regnode;

	if (!EventsActive)
		return;

	for (curtype=EVENT_TILEENTERED;curtype!=EVENT_LAST;curtype++)
	{
		numnode=eventnodes[curtype].numnodelist;
		while (numnode!=NULL)
		{
		
			regnode=numnode->regnodelist;
			while (regnode!=NULL)
			{
				regnode=regnode->next;
			}

			numnode=numnode->next;
		}
	}
}

void EventRegister(EVENT_TYPE type, int num, EventTriggeredFunc func, void *userdata)
{
	EVENT_NUMBER_NODE *numnode;
	EVENT_REGISTERED_NODE *regnode;

	if (num==EVENT_NUM_UNDEFINED)
		return;

	numnode=eventnodes[type].numnodelist;

	while (numnode!=NULL)
	{
		if (numnode->whichnum==num)
			break;
		numnode=numnode->next;
	}

	if (numnode==NULL) //need to create a number node
	{
		numnode=(EVENT_NUMBER_NODE*)malloc(sizeof(EVENT_NUMBER_NODE));
		ZeroMemory(numnode, sizeof(EVENT_NUMBER_NODE));
		numnode->next=eventnodes[type].numnodelist;
		numnode->regnodelist=NULL;
		numnode->whichnum=num;
		eventnodes[type].numnodelist=numnode;
	}

	regnode=(EVENT_REGISTERED_NODE*)malloc(sizeof(EVENT_REGISTERED_NODE));
	ZeroMemory(regnode, sizeof(EVENT_REGISTERED_NODE));
	regnode->func=func;
	regnode->userdata=userdata;
	regnode->next=numnode->regnodelist;
	numnode->regnodelist=regnode;
}



void EventTriggerImmediate(EVENT_TYPE type, int num, long uid, int removeevent, int remote)
{
	EVENT_NUMBER_NODE *numnode;
	EVENT_REGISTERED_NODE *regnode;
	char eventname[256];

	if (EventsActive == 0) {
		TRACE("Error: Received Event Before I was Ready\n");
        GetEventName(type, num, eventname);
        if (eventname[0]) TRACE("   %d.%3d - Trigger Event %s remote is %s\n", nSec,nMilliSec, eventname, remote? "true" : "false");
		return;
	}


    if (scriptDebug)
    {
        GetEventName(type, num, eventname);
        if (eventname[0]) 
		{
			if (!remote)
				TRACE("   %d.%3d - Trigger Event %s (broadcast) \n", nSec,nMilliSec, eventname);
			else 
				TRACE("   %d.%3d - Trigger Event %s\n", nSec,nMilliSec, eventname);

		}
    }
    
    // as host, send event info
	if (!remote)
		EventMessageSend(type, num, uid, removeevent);

	numnode=eventnodes[type].numnodelist;

	while (numnode!=NULL)
	{
		if ((numnode->whichnum==EVENT_NUM_ALL) || (numnode->whichnum==num))
		{
			regnode=numnode->regnodelist;
			while (regnode!=NULL)
			{
				regnode->func(type, num, uid, regnode->userdata);
				regnode=regnode->next;
			}
		}

		numnode=numnode->next;
	}
}

void EventMessageReceive(ARMY_MESSAGE *pArmyMsg)
{
	EVENT_MESSAGE *pMsg=(EVENT_MESSAGE*)pArmyMsg;
    char eventname[256];

    if (scriptDebug)
    {
        GetEventName((EVENT_TYPE)pMsg->type, pMsg->num, eventname);
        if (eventname[0]) TRACE("    Event receive %s remove %d \n",eventname ,pMsg->removeevent);
    }
	EventTriggerImmediate((EVENT_TYPE)pMsg->type, pMsg->num, gpComm->LocalUID(pMsg->uid), pMsg->removeevent, 1);
}


void DelayCallback(EVENT_TYPE type, int num, long uid, void *userdata)
{
	DELAYED_EVENT_INFO *info, *dummy;
	info = (DELAYED_EVENT_INFO*) userdata;

	EventTriggerImmediate(info->type, info->num, info->uid, info->removeevent, 0);

	//free info and remove it from delayed event info list
	if (delayedEventInfo==info)
	{
		delayedEventInfo=info->next;
		free(info);
	}
	else
	{
		dummy=delayedEventInfo;
		while ((dummy) && (dummy->next!=info))
			dummy=dummy->next;
		
		if (!dummy)
		{
			TRACE("SERIOUS ERROR: DELAYED EVENT INFO LOST\n");
			return;
		}

		dummy->next=info->next;
		free(info);
	}
}

void EventTriggerDelayed(EVENT_TYPE type, int num, long uid, int delay, int removeevent)
{

    // schedule an event to happen later

	DELAYED_EVENT_INFO *info;
	int	timereventnum;
    char eventname[256];

    if (scriptDebug)
    {
        GetEventName(type, num, eventname);
        TRACE("   %d.%3d - Schedule Delayed Event %s at %d (%d)\n", nSec,nMilliSec, eventname,delay+curtime,delay);
    }

	info=(DELAYED_EVENT_INFO*)malloc(sizeof(DELAYED_EVENT_INFO));
	info->type=type;
	info->num=num;
	info->uid=uid;
	info->removeevent=removeevent;
	info->next=delayedEventInfo;
	delayedEventInfo=info;

	timereventnum=CreateTimer(delay, 0, 0, 1, EVENT_NUM_UNDEFINED);
	if (EVENT_ERROR == timereventnum)
	{
		GetEventName(type, num, eventname);
        TRACE("  Failed timer create for Event %s \n", eventname);
		ASSERT(0);
	}
	EventRegister(EVENT_TIMER, timereventnum, DelayCallback, (void*)info);
}


void EventTrigger(EVENT_TYPE type, int num, long uid, int delay, int removeevent)
{
	if (EventsActive != 2)
		return;

		// discard some events in multi player
	if (gpGame->GameType != GAMETYPE_ONEPLAYER)
	{
		if (type == EVENT_ITEMDAMAGED || type == EVENT_ITEMVISON || 
			type == EVENT_ITEMVISOFF)
			return;
	}


	if (delay>0)
		EventTriggerDelayed(type, num, uid, delay, removeevent);
	else
		EventTriggerImmediate(type, num, uid, removeevent, 0);
}

void unitselectedfunc(EVENT_TYPE type, int num, long uid, void *userdata)
{
	static int counter=1;

    if (scriptDebug)
        TRACE("A unit was selected. setting up timer %d to go off %d times\n", counter, counter);

	CreateTimer(3, 0, 3, counter, counter);
	counter++;
}

static void timertickfunc(EVENT_TYPE type, int num, long uid, void *userdata)
{
// for debugging
}


void EventInit(void)
{
	ZeroMemory(eventnodes, sizeof(eventnodes));
	EventsActive=0;

//  for debugging
//	EventRegister(EVENT_UNITSELECTED, EVENT_NUM_ALL, unitselectedfunc, NULL);
//	EventRegister(EVENT_TIMER, EVENT_NUM_ALL, timertickfunc, NULL);
}

void EventStart(void)
{
	switch(gpGame->GameType)	{
		case GAMETYPE_ONEPLAYER:
		case GAMETYPE_HOST_MULTIPLAYER:
			EventsActive=2;
			break;
        default: EventsActive=1;
	}

	TurnOnCompoundEvents();  // enable checking of compound events clauses
	SOBJ_TurnOn();
}

void EventShutdown(void)
{
	int curtype;
	EVENT_NUMBER_NODE *numnode, *nextnumnode;
	EVENT_REGISTERED_NODE *regnode, *nextregnode;

	DELAYED_EVENT_INFO *delayinfo1, *delayinfo2;


	EventsActive=0;

	delayinfo1=delayedEventInfo;
	while (delayinfo1)
	{
		delayinfo2=delayinfo1;
		delayinfo1=delayinfo1->next;
		free(delayinfo2);
	}
	delayedEventInfo=NULL;

	for (curtype=EVENT_TILEENTERED;curtype!=EVENT_LAST;curtype++)
	{

		numnode=eventnodes[curtype].numnodelist;
		while (numnode!=NULL)
		{
		
			nextnumnode=numnode->next;

			regnode=numnode->regnodelist;
			while (regnode!=NULL)
			{
				nextregnode=regnode->next;
				free(regnode);
				regnode=nextregnode;
			}

			free(numnode);
			numnode=nextnumnode;
		}
	}
uniqueeventnum=100000;
}



			





