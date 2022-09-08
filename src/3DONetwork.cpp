/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: 3DONetwork.cpp $
//
//	DESCRIPTION:	networking routines
//
//	AUTHOR:			David Maynard
//
//	CREATED:		February, 20, 1997
//
//	REVISION:		$Header: /ArmyMen/src/3DONetwork.cpp 81    4/17/98 12:22p Dmaynard $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History


#include "stdafx.h"

#include "GameFlow.h"
#include "3DONetwork.h"
#include "comm.h"	// helper functions for directplay
#include "ScreenBtn.h"

// #include "dpgame.h"
// #include "gameproc.h"
unsigned long msgbuffer[MAX_MSGS][MAX_MSG_SIZE/4];
unsigned long bitbucket[MAX_MSG_SIZE/4];
#define PACKETLOSSPERCENT 0

/*
 * Globals
 */
HANDLE								ObjectTable[32];	/* maximum objects to wait for */
HANDLE								PlayerEvent;
LPGUID								glpGuid;
HWND								ghWndMain;					// hack to get comm. into Armymen
HINSTANCE							ghinst;						// Application instance handle      
//HANDLE								ghThread;					// handle to wizard thread
#define								MAX_FLOWS     6 
FLOWQ								gFlows[MAX_FLOWS];				// a couple of spares

LOGACKMSG				gLogAckMsg;					// message buffer
extern  FLOWMSG					gFlowMsg;
extern  FLOWMSG					gintFlowMsg;
extern  FLOWNACKMSG				gFlowNackMsg;		 // used at interrupt level
extern  FLOWPULSEMSG			gAMFlowPulseMsg;		 // used at mainframe level 
extern  FLOWMSG					gAMPAUSEFlowMsg;


//  USED for Error exit

extern LONG	ScrnOnAbortMission( HSCREENBTN hScreenBtn );

BOOL GameLaunched;			// should be set at end of LaunchGame


TDGLIST freelist;		// The free message pool
TDGLIST inuselist;		//  Messages received by the interrupt thread but not yet processed by the Application
TDGLIST sendqueue;		//  Messages we have sent but haven't yet got a ack for.
TDGLIST latencyqueue;	//  Messages we haven't sent yet because we are emulating Latency

TDGMSG msgs[MAX_MSGS];

DWORD numObjs;

BOOL		gShutDown;


DWORD					PacketThreadID;
HANDLE					ThreadHandle;
DWORD					repliesmask;
DWORD					resendmask;
BOOL					AbortInProgress;

          // our player id
extern HINSTANCE                ghinst;           

static 	void  CountLatency(LPFLOWQ lpFlowQ, DWORD latency);
static 	int	GenerateLatency(int mean, int stdDev);

#define EMPTYLIST(l)	((l)->first == 0)

BOOL InitTdgList(TDGLIST *l)
{
	l->first = 0;
	l->last = 0;
	l->numItems = 0;
	l->MutexLock = CreateMutex(0,0,0);
	if (l->MutexLock == 0) return FALSE;
	return TRUE;
}

int ListSize(TDGLIST *l) {
	int n = 0;
	return l->numItems;
}

static void FreeTdgList(TDGLIST *l) 
{
	l->first = 0;
	l->last = 0;
	if (l->MutexLock ) CloseHandle(l->MutexLock);
	l->MutexLock = 0;
}



void AddMsg(TDGLIST *l, TDGMSG *m)
{
	TDGMSG *lastmsg;
	WaitForSingleObject(l->MutexLock, INFINITE);
	m->next = 0;
	lastmsg = l->last;
	m->prev = lastmsg;
	if (lastmsg == 0)
	{	// EmptyList
		l->first = m;
		l->last = m;
	}
	else
	{
		lastmsg->next = m;
		l->last = m;
	}
	l->numItems++;
	if((l->numItems < 0) || (l->numItems > MAX_MSGS)) {
		TRACE("AddMsg: Impossible List Size %d \n", l->numItems);
//			ASSERT(FALSE);
	}
	ReleaseMutex(l->MutexLock);
}


DWORD HeadSeq (TDGLIST *l) {
	if (l->first == NULL) return 0;
	return((l->first)->seq);
}


TDGMSG *RemHead(TDGLIST *l)
{
	TDGMSG *m;
	WaitForSingleObject(l->MutexLock, INFINITE);
	m = l->first;
	if (m)
	{
		TDGMSG *n = m->next;
		l->first = n;
		if (n == 0) l->last = 0;
		else	n->prev = 0;
	    l->numItems--;
		if((l->numItems < 0) || (l->numItems > MAX_MSGS)) {
			TRACE("RemHead: Impossible List Size %d \n", l->numItems);
			// ASSERT(FALSE);
		}
	}
	if ((m == NULL) && (l == &freelist)) {
		TRACE("Empty List! l->first = %d listsize = %d \n",l->first , l->numItems);
		// ASSERT(FALSE);
	}
	ReleaseMutex(l->MutexLock);
	return m;
}

TDGMSG *InsertMsg(TDGLIST *l, TDGMSG *msg)
{
	TDGMSG *m;
	WaitForSingleObject(l->MutexLock, INFINITE);
	m = l->first;
	if( m == NULL ) { // empty list
		l->first = msg;
		l->last = msg;
		msg->prev = NULL;
		msg->next = NULL;
		l->numItems++;
	} else
	if (m->seq > msg->seq) { // put it at head of list
			msg->prev = NULL;
			msg->next = m;
			l->first = msg;
			m->prev = msg;
			l->numItems++;
	} else
	
	
	while (m != NULL) {
			if (m->seq > msg->seq) {
				if (m->prev) (m->prev)->next = msg;
				else l->first= msg;
				msg->prev = m->prev;
				msg->next = m;
				m->prev = msg;
				l->numItems++;
				break;
			}
			if (m->next == NULL)  { // put at end of list;
				m->next = msg;
				msg->prev = m;
				msg->next = NULL;
				l->last = msg;
				l->numItems++;
				break;
			}
			m= m->next;
		}

	ReleaseMutex(l->MutexLock);
	return msg;
}

void EmptyList(TDGLIST *l) {
TDGMSG *m;
 while ( (m=RemHead(l)) != NULL) AddMsg(&freelist,m);
}

TDGMSG *FindSeq(TDGLIST *l, DWORD seq, BOOL add, DWORD mask)
{
	TDGMSG *m,*t;
	DWORD addmask = mask;
	DWORD ackmask = ~mask;
	WaitForSingleObject(l->MutexLock, INFINITE);
	t = NULL;
	m = l->first;
	while (m)
	{
		if (m->seq == seq) {
			t=m; 
			if(add) t->replies |= addmask;
			else t->replies &= ackmask;
			break;
		}
	 m = m->next;
	}
	ReleaseMutex(l->MutexLock);
	return t;
}

LPFLOWMSG FindSeqCopy(TDGLIST *l, DWORD seq,  LPFLOWMSG lpMsg)
{
	TDGMSG *m,*t;
	WaitForSingleObject(l->MutexLock, INFINITE);
	t = NULL;
	m = l->first;
	while (m)
	{
		if (m->seq == seq) {
			t=m; 
			break;
		}
	 m = m->next;
	}
	if (t != NULL) memcpy(lpMsg,t->data,t->datasize);
	ReleaseMutex(l->MutexLock);
	return t ? lpMsg : NULL;
}

// Find the oldest message in the sendqueue with any resend bits on
// Clears the resend bits and make a copy of the message

DWORD FindResendCopy(TDGLIST *l, LPFLOWMSG lpMsg)
{
	TDGMSG *m,*t;
	DWORD rmask = 0;
	WaitForSingleObject(l->MutexLock, INFINITE);
	t = NULL;
	m = l->first;
	while (m)
	{
		if (m->replies & resendmask) {
			rmask = m->replies & resendmask;
			t=m; 
			m->replies &= ~resendmask;
			break;
		}
	 m = m->next;
	}
	if (t != NULL) memcpy(lpMsg,t->data,t->datasize);
	ReleaseMutex(l->MutexLock);
	return t ? rmask : 0;
}

void DumpList(TDGLIST *l ) {
	TDGMSG *m;
	WaitForSingleObject(l->MutexLock, INFINITE);
	m = l->first;
	TRACE("List: ");
	while (m)
		{
		TRACE("(%d %d)",m->seq,((LPFLOWMSG)m->data)->seq);
		m = m->next;
		}
	TRACE("\n");
	ReleaseMutex(l->MutexLock);
}

void RemMsg(TDGLIST *l, TDGMSG *m)
{
	TDGMSG *t;
	TDGMSG *s;
	WaitForSingleObject(l->MutexLock, INFINITE);
	if (m->prev == 0)	// first msg on list
	{
		t = m->next;
		l->first = t;
		if (t)	t->prev = 0;
		else	l->last = 0;	// empty list now
	}
	else if (m->next == 0)	// last msg on list
	{
		// we know there one before us
		t = m->prev;
		t->next = 0;
		l->last = t;
	}
	else
	{
		t = m->prev;
		s = m->next;
		t->next = s;
		s->prev = t;
	}
	l->numItems--;
	if((l->numItems < 0) || (l->numItems > MAX_MSGS)) {
		TRACE("RemMsg: Impossible List Size %d \n", l->numItems);
		}
	if ((l == &freelist) && (l->first == 0))  {
		TRACE("RemMsg has set freelist to EMPTY!! l->numItems = %d\n",l->numItems);
	}
	if((l->first == NULL) && (l->numItems > 0)) {
			TRACE("Why is list %x empty?  List Size %d \n",l, l->numItems);
	}
	ReleaseMutex(l->MutexLock);
}




DWORD	TDGTimeDelta;	// set after round trip tests
DWORD	clockerr = 0;

#include <sys/types.h>
#include <sys/timeb.h>

DWORD TDGTimeStamp(void)
{

	return GetTickCount();

}

DWORD TDGRealTime(void)
{
	return TDGTimeStamp() + TDGTimeDelta;
}

BOOL DoLocalSystemMessage(TDGMSG *m);

BOOL ProcessTdgMsgLocal(TDGMSG *m)
{
	LPFLOWMSG lpFlowMsg;
	// all msgs get defered for now
	LPGENERICMSG lpMsg;
	LPFLOWNACKMSG lpFlowNackMsg;
	TDGMSG *t;
	DWORD mask;
	DWORD xsum;
	DWORD interval;
	DWORD nackfrom,nackthru;
	if (m->idFrom == DPID_SYSMSG)
	{
	    return DoLocalSystemMessage(m);
	}
	lpMsg = (LPGENERICMSG)m->data;
	switch (lpMsg->tdg.tdg_Type)
	{
#ifdef THREAD_LOGGING
    case MSG_FLOWPULSE:	  // Interrupt Level  Nack processing
		{
		DWORD latency;
		DWORD now;
		DWORD  seqnum;
		HRESULT hr=E_FAIL ;
		LPFLOWPULSEMSG  lpFlowPulseMsg;
		int numResent = 0;
		 LPFLOWQ lpFlowQ, myFlowQ;
		 lpFlowPulseMsg = (LPFLOWPULSEMSG) lpMsg;
		 lpFlowQ = FindFlowQ(m->idFrom);
		 myFlowQ = FindFlowQ(gpComm->m_DPId);
		 if( lpFlowQ == NULL  || myFlowQ == NULL) {
			TRACE("Interrupt Level Can't find FlowQ for %x or %x \n",m->idFrom, gpComm->m_DPId);
			break;
		 }
		mask = GetPlayerMask(m->idFrom);
		now = GetTickCount();
		// Now Handle the acknowledgement that this remote has received our messages
		// all the way through seqnumber got_thru
		if ((lpFlowPulseMsg->got_thru > lpFlowQ->hehas) && (lpFlowPulseMsg->got_thru < (myFlowQ->nxtSeq)) ) {
			for (seqnum = lpFlowQ->hehas+1;seqnum <= lpFlowPulseMsg->got_thru; seqnum++ ) {
				TRACE(" Got Pulse Ack for  seq %d\n",seqnum);
				t = FindSeq(&sendqueue,seqnum, FALSE, mask);
				if (t == NULL) {
					 if (gpComm->debugComm) TRACE("Flow Ack for Message not in sendqueue sequence %d from %x  %s mask %x  \n", seqnum,m->idFrom,gpComm->GetColorStr(m->idFrom),mask);
					 if (gpComm->debugComm) TRACE("Remote %s is acking %d, I had thru %d \n",gpComm->GetColorStr(m->idFrom),lpFlowPulseMsg->got_thru ,lpFlowQ->hehas );
					// DumpList(&sendqueue);
					continue;
				}
				dbFlowAckSeq(lpFlowQ, seqnum);
				lpFlowQ->acksfrom++;
				latency = now - t->timesent;
				if( latency > 10000 ) {
					if (seqnum == lpFlowQ->hehas+1) TRACE("??? PULSE seq %6d latency %d acks for %d msgs %d thru %d  nxtSeq = %d \n", seqnum,
						latency, (lpFlowPulseMsg->got_thru-lpFlowQ->hehas ), lpFlowQ->hehas , lpFlowPulseMsg->got_thru ,myFlowQ->nxtSeq);
				}
				
				if ((lpFlowQ->minLatency == 0)  || (latency<lpFlowQ->minLatency))lpFlowQ->minLatency = latency ;
				if (latency > 10000)  latency = 10000;   //special case,  someone paused or gameload happened
				if (latency>lpFlowQ->maxLatency)lpFlowQ->maxLatency = latency ;
				lpFlowQ->totalLatency += latency;
				CountLatency(lpFlowQ, latency);
				if ((t->replies & repliesmask)== 0) {
					TRACE("PULSE Adding to freelist from sendque Buffer seq %d  elelment %x \n",t->seq, t);
					RemMsg(&sendqueue,t);
					AddMsg(&freelist,t);
				}
			}
			lpFlowQ->hehas = lpFlowPulseMsg->got_thru;
		}
		if (lpFlowPulseMsg->seqfrom == 0 ) {   //  No nack just got_thru
			AddMsg(&freelist,m);
			return TRUE;	// done with msg. Do not allow app to process also
			break;
		}
		
	}	
		//  WARNING  NO break statement !!!	 here on PURPOSE
		// This case falls through and executes the nack also

	case MSG_FLOWNACK:	  // Interrupt Level  Nack processing
		{
		HRESULT hr=E_FAIL ;
		DWORD i,rmask;
		LPFLOWNACKMSG  lpFlowNackMsg;
		LPFLOWMSG lpFlowMsg;
		int numResent = 0;
		 LPFLOWQ lpFlowQ, myFlowQ;
		 lpFlowNackMsg = (LPFLOWNACKMSG) lpMsg;
		 lpFlowQ = FindFlowQ(m->idFrom);
		 myFlowQ = FindFlowQ(gpComm->m_DPId);
		 if( lpFlowQ == NULL  || myFlowQ == NULL) {
			TRACE("Interrupt Level Can't find FlowQ for %x or %x \n",m->idFrom, gpComm->m_DPId);
			break;
		 }
		 if (gpComm->debugComm) TRACE("GOT NACK: seq %d thru %d from %s (%x)  nxtSeq = %d \n",lpFlowNackMsg->seqfrom,
			 lpFlowNackMsg->seqthru, gpComm->GetColorStr(m->idFrom),m->idFrom,myFlowQ->nxtSeq);
		 rmask = lpFlowQ->resendbit;
		 for(i= lpFlowNackMsg->seqfrom;i<=lpFlowNackMsg->seqthru;i++ ) {
			lpFlowMsg = FindSeqCopy(&sendqueue, i,  &gintFlowMsg);
			if (lpFlowMsg == NULL) {
				TRACE("Flow Nack Resend: Msg not found seq %d hehas %d\n",i,lpFlowQ->hehas);
				// DumpList(&sendqueue);
			} else { // found the message in the sendqueue
				//  We should maybe move this out of interrupt code
			    if (numResent < 2) {
					lpFlowMsg->got_thru = lpFlowQ->gotseq;
					lpFlowMsg->xsum = 0;
					lpFlowMsg->xsum = XorSum((LPGENERICMSG)lpFlowMsg);
					hr = gpComm->Send(m->idFrom, 0, (LPVOID)lpFlowMsg, lpFlowMsg->tdg.tdg_Size);    
					if (FAILED(hr)) {
						TRACE("DPlaySend Failure %x to %x size %d\n", hr, m->idFrom, lpFlowMsg->tdg.tdg_Size);
					}
					dbFlowResendSeq(lpFlowQ, i);
					if (gpComm->debugComm) TRACE("Resend: seq %d to %s (%x)  nxtSeq = %d\n",i,gpComm->GetColorStr(m->idFrom),m->idFrom,myFlowQ->nxtSeq);
					lpFlowQ->numResends++;
					numResent++;
					FindSeq(&sendqueue,i,FALSE,rmask); // clear the resend bits if any
				}  else {	// too many to do in interrupt code
				//  So add a resend bit flag to the message in the message Queue and 
				//  let the main loop handle the resend
				if(gpComm->debugComm) TRACE("ADDING to Resend Queue seq %d to id %x  mask %x\n", i, m->idFrom, rmask);
				FindSeq(&sendqueue,i,TRUE,rmask);
				}

			}

		}
		AddMsg(&freelist,m);
		return TRUE;	// done with msg. Do not allow app to process also
        break;
		}

	case MSG_FLOW:
		DWORD latency;
		DWORD now;
		LPFLOWQ lpFlowQ, myFlow;
		DWORD  seqnum;
		lpFlowMsg = (LPFLOWMSG) lpMsg;
		DWORD expected;
		BOOL  sendnack;
		DWORD i;
		mask = GetPlayerMask(m->idFrom);
		// Find the FlowQ data structure associate with the player that sent this message
		lpFlowQ = FindFlowQ(m->idFrom);
		if (lpFlowQ == NULL ) {
			TRACE("Can't Find FlowQ for id %x  seq \n",m->idFrom, lpFlowMsg->seq);
			return TRUE;  // Error: skip this message
		}
		myFlow = FindFlowQ(gpComm->m_DPId);
		if (myFlow == NULL ) {
			TRACE("Can't Find my FlowQ for id %x\n", gpComm->m_DPId);
			return TRUE;  // Error: skip this message
		}
		if ( lpFlowMsg->seq < 5 ) TRACE("Received seq %d  expected %d he has my seqthru  %d	\n", lpFlowMsg->seq , lpFlowQ->gotseq+1, lpFlowMsg->got_thru);
		xsum = XorSum((LPGENERICMSG)lpFlowMsg);
		if(xsum ) {	 // packet is error free
			// Otherwise either the data or the ack has an error
			TRACE("Ack for sequence %d had bad checksum %x\n", lpFlowMsg->seq,lpFlowMsg->xsum);
			// Nack(lpAckReceived->seq,lpAckReceived->seq,m->idFrom);
		//	return	(lpFlowMsg->xsum != 0);	// let it go if xsum was zero (WHY??? BUG!!!)
			lpFlowQ->errcnt++;
			return TRUE;  // Don't let this go any farther 
		}
		// Is this the start of a new session  ???
		// Note we need other conditions to trigger new session in case seq 1 gets lost;
		expected = lpFlowQ->gotseq+1;
		//  We are not yet ready to start receiving messages until we have gotten the first
		// PlayerMessage from the host;
//		if( !gpComm->m_bHost && !gpComm->m_HostID ) {
			// This is the first message I have seen from this player
//			if ( lpFlowQ->gotseq == 0) lpFlowQ->gotseq = lpFlowMsg->seq;
			// return TRUE; 
//		}
		if ( /* (m->idFrom == gpComm->m_HostID) &&   */
			 ( myFlow->nxtSeq == 1) && (expected==1 ) )  {
		// STARTING SLAVE SESSION
			if( !gpComm->m_bHost) {
				if (gpComm->debugComm) TRACE("Starting Slave Session Received seq %d\n",lpFlowMsg->seq);
				lpFlowQ->gotseq  = lpFlowMsg->seq;
				myFlow->active = TRUE;
				myFlow->sessionStart = GetTickCount(); 
				// Stagger Startup Times
				//  to equalize latency
				myFlow->mswakeup = GetTickCount()-(myFlow->targetDataRate/2);
			}
		}
		else if (lpFlowQ->gotseq == 0) {
		//  first message from we receive from this player
		//  lets pretend we have gotten everything he has sent up to now
			lpFlowQ->gotseq  = lpFlowMsg->seq;
		}
		
		lpFlowQ->packetsfrom++;
		lpFlowQ->bytesfrom += lpFlowMsg->tdg.tdg_Size;
		now = GetTickCount();
		lpFlowQ->wasAliveAt = now;

		if (lpFlowMsg->got_thru < lpFlowQ->hehas ) {
			// TRACE("Out of sequence Ack, got_thru %d had thru %d in seq %d when I expected seq %d\n", lpFlowMsg->got_thru,lpFlowQ->hehas,lpFlowMsg->seq,expected);
			// lpFlowQ->hehas = lpFlowMsg->got_thru;
		}
		if ((expected < 10) && (lpFlowMsg->seq>expected) && (lpFlowMsg->seq - expected) > MAXMISSING) {
			// Assume that this is left over from a previous session
			if (gpComm->debugComm) TRACE("Residual Message: expected  %d received %d  from %s hehas %d \n", 
				expected, lpFlowMsg->seq,gpComm->GetColorStr(m->idFrom), lpFlowMsg->got_thru );
			// TRACE("Adding to freelist duplicate Buffer seq %d  element %x \n",lpFlowMsg->seq, m);
			AddMsg(&freelist,m);
			return TRUE;	// done with msg. Do not allow app to process also
		}
		// First Handle the acknowledgement that this remote has received our messages
		// all the way through seqnumber got_thru
		if ((lpFlowMsg->got_thru > lpFlowQ->hehas) && (lpFlowMsg->got_thru < (myFlow->nxtSeq)) ) {
			if( (lpFlowMsg->seq == 1)  ) {
				TRACE ("New Player joining flow he first got my seq %d he has was %d  \n",lpFlowMsg->got_thru,lpFlowQ->hehas);
				// TRACE  pretend he has received all previous messages
				DumpList(&sendqueue);
//				lpFlowQ->hehas =  lpFlowMsg->got_thru-1;
			}

		    if(( lpFlowMsg->got_thru - lpFlowQ->hehas) > 4*MAXMISSING)  {
				TRACE(" No many acks in one packet	 %d thru %d \n", lpFlowMsg->got_thru,lpFlowQ->hehas);
			}
			for (seqnum = lpFlowQ->hehas+1;seqnum <= lpFlowMsg->got_thru; seqnum++ ) {
				// TRACE(" Got Ack for  seq %d\n",seqnum);
				t = FindSeq(&sendqueue,seqnum, FALSE, mask);
				if (t == NULL) {
					 if (gpComm->debugComm) TRACE("Flow Ack for Message not in sendqueue sequence %d from %x  %s mask %x  \n", seqnum,m->idFrom,gpComm->GetColorStr(m->idFrom),mask);
					 if (gpComm->debugComm) TRACE("Remote %s is acking %d, I had thru %d \n",gpComm->GetColorStr(m->idFrom),lpFlowMsg->got_thru ,lpFlowQ->hehas );
					// DumpList(&sendqueue);
					continue;
				}
				dbFlowAckSeq(lpFlowQ, seqnum);
				lpFlowQ->acksfrom++;
				latency = now - t->timesent;
				if( latency > 10000 ) {
					if (seqnum == lpFlowQ->hehas+1) TRACE("??? seq %6d latency %d acks for %d msgs %d thru %d  nxtSeq = %d \n", seqnum,
						latency, (lpFlowMsg->got_thru-lpFlowQ->hehas ), lpFlowQ->hehas , lpFlowMsg->got_thru ,myFlow->nxtSeq);
				}
				
				if ((lpFlowQ->minLatency == 0)  || (latency<lpFlowQ->minLatency))lpFlowQ->minLatency = latency ;
				if (latency > 10000)  latency = 10000;   //special case,  someone paused or gameload happened
				if (latency>lpFlowQ->maxLatency)lpFlowQ->maxLatency = latency ;
				lpFlowQ->totalLatency += latency;
				CountLatency(lpFlowQ, latency);
				if ((t->replies & repliesmask)== 0) {
					// TRACE("Adding to freelist from sendque Buffer seq %d  elelment %x \n",t->seq, t);
					RemMsg(&sendqueue,t);
					AddMsg(&freelist,t);
				}
			}
		}
		lpFlowQ->hehas = lpFlowMsg->got_thru;
		if (lpFlowMsg->seq > lpFlowQ->maxseq ) lpFlowQ->maxseq = lpFlowMsg->seq;
		// Now handle the delivery of the actual message
		// There are 3 cases
		// First: This is a duplicate message, ignore it;
		expected = lpFlowQ->gotseq+1;
		if (lpFlowMsg->seq < expected ) {
			// This is a duplicate message. Ignore it
			lpFlowQ->numDupes++;
			if (gpComm->debugComm) TRACE("Duplicate: expected %d received %d  from %s hehas %d \n", expected, lpFlowMsg->seq,gpComm->GetColorStr(m->idFrom),lpFlowMsg->got_thru );
			// TRACE("Adding to freelist duplicate Buffer seq %d  element %x \n",lpFlowMsg->seq, m);
			AddMsg(&freelist,m);
			return TRUE;	// done with msg. Do not allow app to process also
		}
		// Second: This is an out of sequence message (store it) and nack the missing messages
		
		if (lpFlowMsg->seq > expected ) {
			// Add Sending of Flow Nack Message here
			// TRACE("Expected %d received %d  hehas %d \n", expected, lpFlowMsg->seq,lpFlowMsg->got_thru );
			lpFlowNackMsg = &gFlowNackMsg;
			m->seq = lpFlowMsg->seq;
			InsertMsg(&(lpFlowQ->pendingqueue),m);
			// InsertMsg(&(lpFlowQ->pendingqueue),m);
			nackfrom = expected;
			nackthru = lpFlowMsg->seq-1;
			if ( lpFlowQ->pendingqueue.first != NULL )
				nackthru = HeadSeq(&(lpFlowQ->pendingqueue))-1;
			lpFlowNackMsg->seqfrom = nackfrom;
			lpFlowNackMsg->seqthru = nackthru;
			if (nackthru < nackfrom) nackthru = nackfrom;
			if (nackthru-nackfrom > MAXMISSING ) {
				TRACE("Flow Nacking ERROR too many missing from %d thru %d \n",nackfrom , nackthru );
				lpFlowNackMsg->seqthru = nackfrom+10;
			}
			sendnack = FALSE;
			for (i=nackfrom;i<=nackthru;i++) {
				if( DoNack(lpFlowQ,i)) sendnack = TRUE;
			}
			if (sendnack) {
				lpFlowQ->numNacks += (nackthru-nackfrom+1);
				if (gpComm->debugComm)  TRACE("Flow Nacking %d thru %d  to %s at time %d I am good thru %d \n",nackfrom , nackthru, gpComm->GetColorStr(m->idFrom)  , now, lpFlowQ->gotseq);
				SendGameMessage( (LPGENERICMSG) lpFlowNackMsg, m->idFrom, 0 );
				for(i=nackfrom;i<=nackthru;i++) dbFlowNackSeq(lpFlowQ ,i);
			}
			return TRUE;	// done with msg. Do not allow app to process also
		}
 		// Third: This is next expected message 
		if (lpFlowMsg->seq == expected ) {
			AddMsg(&inuselist,m);
			// TRACE("Got seq %d \n",lpFlowMsg->seq);
			if (expected == 1) {
				lpFlowQ->totalInterval = 0;
				lpFlowQ->minInterval = 10000;
				lpFlowQ->maxInterval = 0;
			    lpFlowQ->timeReceived = now;
			}  else {
				if( lpFlowQ->timeReceived == 0) lpFlowQ->timeReceived = now;
				interval = (now >= lpFlowQ->timeReceived ) ? now - lpFlowQ->timeReceived : lpFlowQ->timeReceived;
				lpFlowQ->timeReceived = now;
				if (interval < lpFlowQ->minInterval ) lpFlowQ->minInterval = interval;
				if (interval > lpFlowQ->maxInterval ) lpFlowQ->maxInterval = interval;
				if (interval > 100000 ) 
					TRACE("Unusually large time between messages %d seconds\n", interval/1000);
				lpFlowQ->totalInterval += interval;
			}
			dbFlowReceiveSeq(lpFlowQ,lpFlowMsg->seq);
			RemNack(lpFlowQ,expected);
			lpFlowQ->gotseq = expected;
			expected++;
			while (	HeadSeq(&(lpFlowQ->pendingqueue)) == expected ) {
					t = RemHead(&lpFlowQ->pendingqueue );
					if(t != NULL) AddMsg(&inuselist,t);
					// TRACE("Moved seq %d from pending to inuse \n",t->seq);
					RemNack(lpFlowQ,expected);
					lpFlowQ->gotseq = expected;
					expected++;
			} 
			return TRUE;	// done with msg. Do not allow app to process also
		}



		return FALSE;	// allow  app to process also
		// return TRUE;	// done with msg. Do not allow app to process also
		break;


#endif
	default: return FALSE;
	}
}

DWORD DPlayNextMsgSize(void)
{
	HRESULT hr;
	DPID from,to;
	DWORD msgsize = 0;
	hr = gpComm->Receive(&from,&to, DPRECEIVE_ALL,
							0,&msgsize);
	return msgsize;
}


unsigned PacketThread(void * arg)
{
	int what;
	int need_to_post;
	DWORD fromIgnored, toIgnored;
	DWORD sizeIgnored = MAX_MSG_SIZE;
	HRESULT	hr;
	TDGMSG *m = 0;
	/* just wait for network objects */
	// this should start up and wait
	while (1)
	{
		what = WaitForMultipleObjects(numObjs,ObjectTable,FALSE,INFINITE);
		need_to_post = 0;
		if (what == 0)
		{
			/* got signal from event */
			/* wait while main process recomputes table */
			TRACE(" Receive thread got event 0 \n");
			WaitForSingleObject(ObjectTable[0],INFINITE);
			return 0;
		}
		else
		{
			/* some other kind of event, should be network object */
		 // TDG_DEBUG_OUT("EVENT");
		  while (TRUE)
		  {
			if (!m) m = RemHead(&freelist);	// get a free msg block
			if (m == 0)
			{
				// big time error NO Buffers to receive into
				//ShowError(IDS_DPERR_NOBUFFERS);
				// ExitGame();
				//while (1);
				// For now better to dump messages on the floor than to let
				// DPlay continue to buffer them up exhausting memory
				TRACE(" ????? m = %x  freelistsize = %d\n",m,ListSize(&freelist));
				m = RemHead(&freelist);
				TRACE(" ????? NOW m = %x freelistsize = %d\n",m,ListSize(&freelist));
				if(m == 0) {
				//	BigTimeCommError();
					TRACE(" Low-Level Comm Error No Recieve Buffers free = %d inuse = %d sendq = %d \n",
						ListSize(&freelist),ListSize(&inuselist),ListSize(&sendqueue));
					TRACE(" Dumping incoming message on the floor\n");
					hr = gpComm->Receive(&fromIgnored,&toIgnored, DPRECEIVE_ALL,
							bitbucket,&sizeIgnored);
					PostMessage(ghWndMain, UM_TDG_COMM_ERROR, 1, 0);
					break;
				}
			}
			//msgsize = DPlayNextMsgSize();	// not really used yet
			// TRACE("Removed %x from freelist \n", m);
			// TRACE("After freelist->first = %x \n", freelist->first);
			m->datasize = MAX_MSG_SIZE;
			hr = gpComm->Receive(&m->idFrom,&m->idTo, DPRECEIVE_ALL,
							m->data,&m->datasize);
			if (hr == DPERR_BUFFERTOOSMALL)
			{
			    // another bigtime error
				// big time error
				ShowError(IDS_DPERR_BUFFERTOOSMALL);
				// ExitGame();
			    // while (1);
			}
			else if (hr == DP_OK)
			{
			    /* do we handle the message in this thread? */
			    if (ProcessTdgMsgLocal(m) == 0)
			    {
					// nope, need to defer to main process
					need_to_post = 1;
//					TDG_DEBUG_OUT("Defer\n");
					AddMsg(&inuselist,m);
					m = 0;
			    }
			    else
			    {
					// Message was handled in this thread
					//  and placed on proper waiting queue
					need_to_post = 1;
					m = 0;
					// TDG_DEBUG_OUT("local\n");
			    }
			}
			else break;
		  }
		  if (need_to_post)
					PostMessage(ghWndMain, UM_TDG_DPLAY, 0, 0);
		}
	}
	TRACE("Packet Thread Exiting %x %x %x \n", what, what, what);
	return TRUE;	// should never get here
}


void KillMsgSystem(void)
{
	DWORD dwRetCode;
	FreeTdgList(&freelist);
	FreeTdgList(&inuselist);
	FreeTdgList(&sendqueue);
	FreeTdgList(&latencyqueue);
	TRACE("Setting Event 0 \n");
	SetEvent(ObjectTable[0]) ;
	if (ThreadHandle)
		{
				// wait for thread to exit
				while (!GetExitCodeThread(ThreadHandle, &dwRetCode));
				TRACE("Packet Thread Exited with return code %d\n", dwRetCode);
				CloseHandle(ThreadHandle);
		}
	if (ObjectTable[0]) CloseHandle(ObjectTable[0]);
	ObjectTable[0]= 0;
	if (ObjectTable[1]) CloseHandle(ObjectTable[1]);
	ObjectTable[1]= 0;
}

BOOL InitMsgSystem(void)
{
	int i,j;
	if (!InitTdgList(&freelist)) return FALSE;
	if (!InitTdgList(&inuselist)) return FALSE;
	if (!InitTdgList(&sendqueue)) return FALSE;
	if (!InitTdgList(&latencyqueue)) return FALSE;
	srand(0);
	for (i = 0; i < MAX_MSGS; i++)
	{
		msgs[i].dwMsgBufferMaxSize = MAX_MSG_SIZE;
		msgs[i].data = msgbuffer[i];
		// Fill buffers with random numbers to prevent
		// Modem data compression from cheating by compressing buffers
		for(j=0;j<MAX_MSG_SIZE/4;j++) msgbuffer[i][j] = (unsigned long)rand();
		AddMsg(&freelist,&msgs[i]);
	}
	ObjectTable[0] = CreateEvent(0,0,0,0);	// control event
	ObjectTable[1] = CreateEvent(0,0,0,0);	// player event
	PlayerEvent = ObjectTable[1];
	numObjs = 2;
	for(i=0;i<MAX_FLOWS;i++) {
		CreateFlowQ(i);
	}
	
	if ((ThreadHandle = CreateThread((LPSECURITY_ATTRIBUTES)NULL,
						(unsigned)0,
						(LPTHREAD_START_ROUTINE)PacketThread,
						0, 0, &PacketThreadID)) < 0)
	{
	
		TRACE("Error launching packet thread\n",0,0,0);
		//ExitGame();
		return FALSE;
	}
	// set priority of thread
	if (!SetThreadPriority(ThreadHandle, THREAD_PRIORITY_ABOVE_NORMAL))
	{
		//MyMsg("Error Setting thread priority");
		//ExitGame();
		return FALSE;
	}

	return TRUE;
}

/*
 * SendGameMessage
 *
 * Sends a message to specified player(s)
 */
HRESULT SendGameMessage( LPGENERICMSG lpMsg, DPID idTo, DWORD dwFlags )
{
    HRESULT hr=E_FAIL ;
	LPFLOWQ lpFlow, myFlow;
	static int rollofdice = 0;
	int timeToSend;
	if((!gpComm->m_bActive)) return hr;
	if(idTo == 0xFFFFFFFF) return hr;
	if (gpComm->m_bSessionLost)
    {
        // no sends when we are not in the session
        return DPERR_NOCONNECTION;
    }
	//TRACE("SendGameMsg(type=%lx to=%lx flags=%lx)\n",lpMsg->tdg.tdg_Type, idTo, dwFlags);
	lpFlow = NULL;
    // Send the message to the relevant player(s)
	if(lpMsg->tdg.tdg_Type == MSG_FLOW) 	{	// Add to SendQueue
		LPFLOWMSG lpFlowMsg = (LPFLOWMSG)lpMsg;
		TDGMSG *m;
	    DWORD mask;
		mask = GetPlayerMask(idTo);
		// TRACE("Logging %d\n", lpLogMsg->seq);
		m = FindSeq(&sendqueue,lpFlowMsg->seq,TRUE,mask);
		if (m == NULL) {
			m = RemHead(&freelist);	// get a free msg block
			if (m == 0) {
				TRACE("Out of Send Buffers \n");
				BigTimeCommError();
				hr = DPERR_OUTOFMEMORY;
				return hr;
			}
			else {
				m->seq = lpFlowMsg->seq;
				m->replies = mask;
				m->timesent = GetTickCount();
				if (lpFlowMsg->tdg.tdg_Size > m->dwMsgBufferMaxSize) {
					TRACE("Message Too Big \n");
					hr = DPERR_SENDTOOBIG;
					return hr;
				}
				memcpy(m->data,lpFlowMsg,lpFlowMsg->tdg.tdg_Size);
				m->datasize = lpFlowMsg->tdg.tdg_Size;
				AddMsg(&sendqueue,m);
			}
		}  else {
		//		TRACE("Resending from Queue %d to %x \n");
		}

		 // Now update the ack count for this  Player
		lpFlow = FindFlowQ(idTo);
		if (lpFlow == NULL ) {
			TRACE("Error Send can't find Flow for Player %x\n", idTo );
		}  else {
			lpFlowMsg->got_thru = lpFlow->gotseq;
			lpFlowMsg->xsum = 0;
			lpFlowMsg->xsum = XorSum((LPGENERICMSG)lpFlowMsg);
			lpFlow->ackedthru = lpFlowMsg->got_thru;
			lpFlow->timeacked = GetTickCount();
			lpFlow->packetsto++;
			lpFlow->bytesto += lpMsg->tdg.tdg_Size;
//  If this is the first message we are sending to this player pretend he has acked all the rest;
			if (lpFlow->hehas == 0 && lpFlowMsg->seq > 1) lpFlow->hehas = lpFlowMsg->seq-1;
			if ( idTo != DPID_ALLPLAYERS)  dbFlowSendSeq(lpFlow,lpFlowMsg->seq);
		}
	
	}
	myFlow = FindFlowQ(gpComm->m_DPId);
	rollofdice = randInt(0,100);
	if( myFlow && myFlow->burstPacketLoss) {
		if( myFlow && myFlow->packetLoss &&  lpFlow &&
			( (int)(lpFlow->packetsto % 100) > (100-(int) myFlow->packetLoss)) &&
			((dwFlags & DPSEND_GUARANTEED) == 0))
			return (DP_OK);	 // Simulating Packet Loss
	}
	else //   Non burst packet loss
	{
		if( myFlow && myFlow->packetLoss &&  ( rollofdice <= (int) myFlow->packetLoss) && ((dwFlags & DPSEND_GUARANTEED) == 0))
			return (DP_OK);	 // Simulating Packet Loss
	}
	if(myFlow &&  myFlow->meanLatency ) {	  // Simulating Latency
			TDGMSG *m;
			LPFLOWMSG lpFlowMsg = (LPFLOWMSG)lpMsg;
			timeToSend = GetTickCount() + GenerateLatency(myFlow->meanLatency,myFlow->deviationLatency);
		// need to get a new msg and copy into it and place it in the latencyQueue
			m = RemHead(&freelist);	// get a free msg block
			if (m == 0) {
				TRACE("Latency Emulation is Out of Send Buffers \n");
				// BigTimeCommError();
				// hr = DPERR_OUTOFMEMORY;
				// return hr;
			}
			else {
				m->seq = timeToSend;
				m->replies = dwFlags;
				m->timesent = GetTickCount();
				m->idTo = idTo;
				m->idFrom = gpComm->m_DPId;
				if (lpFlowMsg->tdg.tdg_Size > m->dwMsgBufferMaxSize) {
					TRACE("Message Too Big \n");
					hr = DPERR_SENDTOOBIG;
					return hr;
				}
				memcpy(m->data,lpFlowMsg,lpFlowMsg->tdg.tdg_Size);
				m->datasize = lpFlowMsg->tdg.tdg_Size;
				InsertMsg(&latencyqueue,m);
				return (DP_OK);	
			}
	}
	
	hr = gpComm->Send(idTo, dwFlags, (LPVOID)lpMsg, lpMsg->tdg.tdg_Size);    
	if (FAILED(hr)) {
		TRACE("DPlaySend Failure %x to %x size %d\n", hr, idTo, lpMsg->tdg.tdg_Size);
		if ( hr == E_FAIL) return hr;
		if ( hr == DPERR_BUSY ) ShowError(IDS_DPERR_BUSY);
		if ( hr == DPERR_INVALIDOBJECT ) ShowError(IDS_DPERR_INVALIDOBJECT);
		if ( hr == DPERR_INVALIDPARAMS ) {
			// ShowError(IDS_DPERR_INVALIDPARAMS);
			TRACE("DPLAY ERROR: INVALID PARAMETERS\n");
			return hr;
		}
		if ( hr == DPERR_INVALIDPLAYER ) {
			// ShowError(DPERR_INVALIDPLAYER);
			TRACE("DPLAY ERROR: INVALID PLAYER\n");
			return hr;
		}
		if ( hr == DPERR_SENDTOOBIG ) ShowError(IDS_DPERR_SENDTOOBIG);
		TRACE("gpComm->Send Failure2 %x to %x size %d\n", hr, idTo, lpMsg->tdg.tdg_Size);
		gShutDown = TRUE;
		ExitGame();
	}
return hr;
}


/*
 * DoLocalSystemMessage
 *
 * called via an interrupt, so main app is till running!
 * Evaluates system messages and performs appropriate actions
 * returns whether msg is not defered.
 */
BOOL DoLocalSystemMessage(TDGMSG *m)
{
    // for this release, all msgs are defered to avoid race conditions
	LPGENERICMSG pgm = (LPGENERICMSG)m->data;
    switch (pgm->tdg.tdg_Type)
	{
		case DPSYS_SESSIONLOST:	gpComm->m_bSessionLost = TRUE;
								/* let msg continue on */
								break;
		default: break;
	}
    return FALSE;
}

/*
 * ReceiveGameMessages
 *
 * Checks if there are any messages for us and receives them
 */
static int crlfmod;

void ReceiveMessages( void )
{
	TDGMSG *m;
	int nMsgs = 0;
	// TRACE("RcvMsgs launched=%d %d %d\n",GameLaunched,0,0);
	if (gpComm->m_bActive)
	{
	    while (m = (TDGMSG *)RemHead(&inuselist))
	    {
			LPGENERICMSG gm;
			gm = (LPGENERICMSG)m->data;
		    nMsgs++;
			// presently all messages, system and our own are coming this way
			//if (m->idFrom == DPID_SYSMSG)
			//   TRACE("sysmsg from=%d type=%ld\n",
			//							m->idFrom,gm->tdg.tdg_Type,0);
			//else
			//   TRACE("appmsg from=%d type=%ld\n",
			//							m->idFrom,gm->tdg.tdg_Type,0);
			if (m->idFrom == DPID_SYSMSG)
				DoSystemMessage((LPDPMSG_GENERIC)gm,m->datasize,
					 m->idFrom, m->idTo);
			else
                DoApplicationMessage((LPGENERICMSG)gm,
					 m->datasize, m->idFrom, m->idTo);
                
		    // Done, put it back on freelist
		    AddMsg(&freelist,(TDGMSG*)m);
		}
//		if (nMsgs > 30) TRACE("Received  %d messages \n",nMsgs,0,0);
//		if (nMsgs > 0) {
//			TRACE("[%d] ",nMsgs);
//			if (++crlfmod % 10 == 0) TRACE("\n");
//		}
	}
	else // let messages stack up until we are ready
	{
	}
}


DWORD XorSum(LPGENERICMSG pMsg) {
	DWORD xsum = 0;
	DWORD *pdw;
	int i,n;
	pdw = (DWORD *) pMsg;
	n = pMsg->tdg.tdg_Size >> 2;
	for( i=0; i<n;i++,pdw++) xsum ^= *pdw;
	return xsum;
	
 }


BOOL ShowError( int iStrID )
{
    TCHAR tszMsg[MAX_ERRORMSG];
    TCHAR tszTitle[MAX_WINDOWTITLE];

    LoadString(ghinst, iStrID, tszMsg, MAX_ERRORMSG);
    LoadString(ghinst, IDS_DUEL_ERROR_TITLE, tszTitle, MAX_WINDOWTITLE);
	Error("%s:%s",tszTitle,tszMsg);
    // TRACE("DPLAYERRORB # %x %d \n",iStrID  , iStrID, IDS_DUEL_ERROR_TITLE );
    return FALSE;
}

/*
 * ExitGame
 *
 * Game termination code
 */
void ExitGame(void)
{
    // shut down app
    gShutDown = TRUE;
	TRACE("Exit Game Posting WM_CLOSE from 3DONetwork\n",0,0,0);
	PostMessage( ghWndMain, WM_CLOSE, 0, 0 );
}


// Flow Queue Stuff

BOOL	CreateFlowQ( int i) {	// One time only
	gFlows[i].id = 0;
	gFlows[i].gotseq = 0;
	gFlows[i].maxseq = 0;
	gFlows[i].hehas = 0;
	gFlows[i].ackedthru = 0;
	gFlows[i].pmask = 1<<i;
	gFlows[i].timeacked = 0;
	gFlows[i].packetsfrom = 0;
	gFlows[i].packetsto = 0;
	gFlows[i].acksfrom = 0;
	gFlows[i].acksto = 0;
	gFlows[i].errcnt = 0;
	gFlows[i].numNacks = 0;
	gFlows[i].numDupes = 0;
	gFlows[i].minLatency = 0;
	gFlows[i].maxLatency = 0;
	gFlows[i].totalLatency = 0;
	gFlows[i].sessionStart = 0;
	return( InitTdgList( &(gFlows[i].pendingqueue)));
}

BOOL	CreateFlowQPlayer( DPID pid) {	
int i,j;
BOOL result = FALSE;
for(i=0;i<MAX_FLOWS;i++ ) {
	if (gFlows[i].id == 0 ) {
		if (gpComm->debugComm) TRACE("Creating Flow Queue for Player id %x\n",pid);
		gFlows[i].id = pid;
		gFlows[i].gotseq = 0;
		gFlows[i].maxseq = 0;
		gFlows[i].hehas = 0;
		gFlows[i].nxtSeq = 1;
		gFlows[i].pmask = 1<<i;
		repliesmask |= 1<<i;
		gFlows[i].resendbit = 1<<(4+i);
		resendmask |= 1<<(4+i);
		gFlows[i].ackedthru = 0;
		gFlows[i].timeacked = 0;
		gFlows[i].packetsfrom = 0;
		gFlows[i].packetsto = 0;
		gFlows[i].acksfrom = 0;
		gFlows[i].acksto = 0;
		gFlows[i].numNacks = 0;
		gFlows[i].numDupes = 0;
		gFlows[i].minLatency = 0;
		gFlows[i].maxLatency = 0;
		gFlows[i].totalLatency = 0;
		gFlows[i].sessionStart = GetTickCount();
		gFlows[i].active = TRUE;
		gFlows[i].hehas = 0 ;	 
		gFlows[i].errcnt = 0;
		gFlows[i].guaranteed = FALSE;
		gFlows[i].emulatePacketLoss = FALSE;
		gFlows[i].burstPacketLoss = FALSE;
		gFlows[i].packetLoss = 0;
		gFlows[i].emulateLatency = FALSE;
		gFlows[i].meanLatency = 0;
		gFlows[i].deviationLatency = 0;
		gFlows[i].active = gpComm->m_bHost;	 
		for(j=0;j<NSEQPIXELS;j++) {
			gFlows[i].SendHistory[j] =0;
			gFlows[i].ReceiveHistory[j] =0;
		}
		result = TRUE;
		break;
	}
	if (gFlows[i].id == pid) {
		TRACE("Error already a Flow Queue for Player id %x\n",pid);
		result = TRUE;
	}
	}
if (!result) 
	TRACE("Create FlowQ failed for ID %x \n", pid);
return result;
}

LPFLOWQ FindFlowQ(DPID id) {
	LPFLOWQ t = NULL;
	int i;
	for(i=0;i<MAX_FLOWS;i++) {
		if (gFlows[i].id == id ) t = &gFlows[i];
	}
	if (t == NULL && id != 0xffffffff) 
		TRACE("Error couldn't find Flow Queue for id %x\n", id);
	return(t);
}


LPFLOWQ MyFlowQ(void) {
	LPFLOWQ t = NULL;
	int i;
	for(i=0;i<MAX_FLOWS;i++) {
		if (gFlows[i].id == gpComm->m_DPId ) t = &gFlows[i];
	}
	if (t == NULL) TRACE("Error couldn't find My Flow Queue for id %x\n", gpComm->m_DPId);
	return(t);
}

BOOL  DestroyFlow(DPID id) {	
	int i,seqnum,nfree;
	LPFLOWQ flowq,myflowq;
	TDGMSG *t;
	DWORD mask;
	if (( id == 0 ) || (id == 0xffffffff)) return FALSE;
	flowq = FindFlowQ(id);
	if( gpComm->debugComm) TRACE("About to Destroy FlowQ for id %x sendqueue Size = %d \n",
								id, ListSize(&sendqueue));
	if ( !flowq ) 
		return FALSE;
	myflowq = FindFlowQ(gpComm->m_DPId);
	if ( !myflowq ) 
		return FALSE;
	EmptyList(&(flowq->pendingqueue));
	if ( id != gpComm->m_DPId) {	// it ain't me babe
	// Pretend this player has just acked all the outstanding messages			
		mask = GetPlayerMask(id);
		if( gpComm->debugComm) TRACE(" Simulating Acks for  seq %d thru %d\n",flowq->hehas+1,myflowq->nxtSeq-1);
		for (seqnum = flowq->hehas+1; seqnum <= (int)myflowq->nxtSeq-1; seqnum++ ) {
	//		if( gpComm->debugComm) TRACE(" Simulating Ack for  seq %d\n",seqnum);
			t = FindSeq(&sendqueue,seqnum, FALSE, mask);
			if( !t ) continue;
			if ((t->replies & repliesmask) == 0) {
				if( gpComm->debugComm) TRACE("Adding to freelist from sendque Buffer seq %d  elelment %x \n",t->seq, t);
				RemMsg(&sendqueue,t);
				AddMsg(&freelist,t);
			}
		}
	}
 	if( gpComm->debugComm) TRACE("Finished Destroying FlowQ for id %x sendqueue Size = %d \n",
								id, ListSize(&sendqueue));

	nfree = ListSize(&freelist);
	if ( (nfree > (MAX_MSGS*3/4))  &&  ((gpGame->IsPaused() & PAUSE_FLOW))) {
		TRACE("FLOW UNPAUSE nfree = %d\n",nfree);
		gpGame->UnPauseGame(PAUSE_FLOW);
	}

	for(i=0;i<MAX_FLOWS;i++) {
		if (gFlows[i].id == id ) {
			gFlows[i].id = 0;  
			return TRUE;
		}
	}	
return FALSE;
}


DWORD GetPlayerMask(DPID id) {
LPFLOWQ t;
t = FindFlowQ(id);
if (t ) return t->pmask;
TRACE("ERROR: GetPlayerMask: No Flowq for %X\n", id );
return 0;
}

DWORD GetReSendMask(DPID id){
LPFLOWQ t;
t = FindFlowQ(id);
if (t ) return t->resendbit;
TRACE("ERROR: GetReSendMask: No Flowq for %X\n", id );
return 0;
}



void InitFlowData(LPFLOWQ flow, BOOL startactive) {
	TDGMSG *m;
	int j;
	if (flow->id == 0) return;
	flow->errcnt = 0 ;	 
	flow->nxtSeq = 1 ;	 
	flow->gotseq = 0 ;	 
	flow->maxseq = 0 ;	 
	flow->hehas = 0 ;	 
	flow->timeacked = 0 ;	 
	flow->packetsfrom = 0 ;	 
	flow->packetsto = 0 ;	 
	flow->bytesfrom = 0 ;	 
	flow->bytesto = 0 ;	 
	flow->acksfrom = 0 ;	 
	flow->acksto = 0 ;	 
	flow->numNacks = 0 ;	 
	flow->numResends = 0 ;	 
	flow->numDupes = 0 ;	 
	flow->minLatency = 100000 ;	 
	flow->maxLatency = 0 ;	 
	flow->totalInterval = 0;
	flow->minInterval = 10000;
	flow->maxInterval = 0;
	flow->totalLatency = 0 ;	 
	flow->sessionStart = 0 ;	 
	flow->errcnt = 0 ;	 
	flow->active = startactive ;	 
//	flow->dataRate = 0;
//	flow->dataSize = 0;
	flow->timeReceived = GetTickCount();
	flow->wasAliveAt = GetTickCount();
	flow->paused = FALSE;
	flow->nNackRecs = 0;
	// TRACE("id %6x out of sequence packets = %d \n", flow->id, flow->nackCount[0]);
	// TRACE("id %6x singly nacked packets   = %d \n", flow->id, flow->nackCount[1]);
	// TRACE("id %6x doubly nacked packets   = %d \n", flow->id, flow->nackCount[2]);
	// TRACE("id %6x triply nacked packets   = %d \n", flow->id, flow->nackCount[3]);
	for (j=0;j<4;j++) flow->nackCount[j] = 0;
	flow->latencyIndex = 0;
	for (j = 0; j< MAXLATENCYBINS; j++) flow->latencyBin[j] = 0;
	for(j=0;j<NSEQPIXELS;j++) {
		flow->SendHistory[j] =0;
		flow->ReceiveHistory[j] =0;
	}
	// TRACE(" Before: pendingueue = %4d free = %4d \n", ListSize(&(flow->pendingqueue)),ListSize(&freelist));
	while ( (m=RemHead(&(flow->pendingqueue))) != NULL) AddMsg(&freelist,m);
	// TRACE(" After:  pendingueue = %4d free = %4d \n", ListSize(&(flow->pendingqueue)),ListSize(&freelist));
}				   

void InitAllFlows(void) {
	LPFLOWQ t = NULL;
	int i;
	for(i=0;i<MAX_FLOWS;i++) {
		if (gFlows[i].id != 0)  {
			InitFlowData(&gFlows[i],((gFlows[i].id == gpComm->m_DPId) && (gpComm->m_bHost)));
		}

	}
	return;
}

// BOOL DoNack  Should we actually send a nack for this missing seq?
//  Yes unless we have alreadt sent one and haven't waited long enough for a reply.

BOOL DoNack(LPFLOWQ lpflow, DWORD seq ) {
int i;
DWORD now;
DWORD aveInterval;	 // How often this guy sends messages
DWORD aveLatency;	 // average round trip latency;
DWORD nackInterval;
BOOL  lossDominates;  // Does packet Loss or out of sequence packets occur more often;
now = GetTickCount();
aveInterval = (lpflow->totalInterval)/(lpflow->gotseq < 2 ? 1 : lpflow->gotseq-1);
aveLatency = lpflow->totalLatency/(lpflow->acksfrom < 1 ? 1 : lpflow->acksfrom ) ;
// if( aveLatency > 2*lpflow->minLatency ) aveLatency = 2*lpflow->minLatency;
// nackInterval = (aveInterval > aveLatency) ? aveInterval: aveLatency;
nackInterval = aveLatency;
if (nackInterval > 3000) nackInterval = 3000;	//  Nack at least once every three seconds
if (lpflow->nNackRecs)  {
	for(i=0;i<lpflow->nNackRecs;i++ ) {
		if ( lpflow->rec[i].seq == seq ) {
			if ( now > ((lpflow->rec[i].time)+nackInterval)) {
				if(gpComm->debugComm) TRACE("Nacking %6d to %s at %d  >?  %d  ( %d ) Interval = %d Latency = %d count = %d nackinterval = %d\n",
					seq,gpComm->GetColorStr(lpflow->id),now,((lpflow->rec[i].time)+nackInterval),
					(now-((lpflow->rec[i].time)+nackInterval)),
					aveInterval,aveLatency,lpflow->rec[i].count,nackInterval);
				lpflow->rec[i].count += 1;
				lpflow->rec[i].time = now;
				return TRUE;
			} else return FALSE;
		}
	}
}
lossDominates = (lpflow->numNacks/2 > lpflow->numDupes);
lpflow->rec[lpflow->nNackRecs].seq = seq;
lpflow->rec[lpflow->nNackRecs].time = now;
lpflow->rec[lpflow->nNackRecs].count = (lossDominates? 1 : 0);
lpflow->nNackRecs++;
if(lpflow->nNackRecs >= MAXNACKRECS) {
	lpflow->nNackRecs--;
	TRACE(" Nack Rec Array full for ID %x, %d\n", lpflow->id, lpflow->nNackRecs);
}
// This is the first time we noticed it was missing
// If messages are actually getting lost we should return TRUE to send a nack now
// However if messages are arriving out of sequence then we should return FALSE
//  and wait awhile to see if the message arrives.
return lossDominates;
}

void RemNack(LPFLOWQ lpflow, DWORD seq) {
int i,j,k,count;
if (lpflow->nNackRecs)  {
	for(i=0;i<lpflow->nNackRecs;i++ ) {
		if ( lpflow->rec[i].seq == seq ) {
			j = i;
			k = i+1;
			count = (lpflow->rec[i].count > 3 ? 3 : lpflow->rec[i].count);
			lpflow->nackCount[count]++;
			while (k<lpflow->nNackRecs) {
				lpflow->rec[j] = lpflow->rec[k] ;
				j++;
				k++;
			}
		   lpflow->nNackRecs--;
		   return;
		}
	}
}
}

static 	void	CountLatency(LPFLOWQ lpFlowQ, DWORD latency) 
{
	lpFlowQ->latencyBin[lpFlowQ->latencyIndex] = latency;
	lpFlowQ->latencyIndex++;
	if ( lpFlowQ->latencyIndex >= MAXLATENCYBINS) lpFlowQ->latencyIndex = 0;
}

int AveLatency(LPFLOWQ lpFlowQ) {
	int i,latency;
	latency = 0;
	for(i=0;i<MAXLATENCYBINS;i++) latency += lpFlowQ->latencyBin[i];
	return(latency/MAXLATENCYBINS);
}

int AveLatencyID(DPID id) {
	int i,latency;
	LPFLOWQ lpflow;
	latency = 0;
	lpflow = FindFlowQ(id);
	if (!lpflow) return 0;
	for(i=0;i<MAXLATENCYBINS;i++) latency += lpflow->latencyBin[i];
	return(latency/MAXLATENCYBINS);
}


static 	int	GenerateLatency(int mean, int stdDev)  {
	int sum;
	int i,numsamples,range;
	if( stdDev == 0) return mean;
	numsamples = 100 - stdDev;
	if (numsamples < 1) numsamples = 1;
	sum = 0;
	range = mean*2;
	for(i=0;i<numsamples;i++) sum += randInt(0,range);
	return sum/numsamples;
}

void ProcessLatencyQueue (void) {
	TDGMSG * m;
	TDGMSG * out;
	DWORD now;
	HRESULT hr = E_FAIL;
	LPFLOWMSG lpmsg;
	now = GetTickCount();
	m = latencyqueue.first;
	while (m!= NULL ) {
		if (now < m->seq ) return;
		out = RemHead(&latencyqueue);
		lpmsg = (LPFLOWMSG) out->data;
		// TRACE("+ %d %d %d\n",now,m->seq,lpmsg->seq);
		hr = gpComm->Send(out->idTo, out->replies, (LPVOID)out->data, out->datasize);    
		if (FAILED(hr)) {
			TRACE("DPlaySend Failure %x to %x size %d\n", hr, out->idTo, out->datasize);
			if ( hr == E_FAIL) return;
			if ( hr == DPERR_BUSY ) ShowError(IDS_DPERR_BUSY);
			if ( hr == DPERR_INVALIDOBJECT ) ShowError(IDS_DPERR_INVALIDOBJECT);
			if ( hr == DPERR_INVALIDPARAMS ) {
				// ShowError(IDS_DPERR_INVALIDPARAMS);
				TRACE("DPLAY ERROR: INVALID PARAMETERS\n");
				return;
			}
			if ( hr == DPERR_INVALIDPLAYER ) {
				// ShowError(DPERR_INVALIDPLAYER);
				TRACE("DPLAY ERROR: INVALID PLAYER\n");
				return;
			}
			if ( hr == DPERR_SENDTOOBIG ) ShowError(IDS_DPERR_SENDTOOBIG);
		}		
		AddMsg(&freelist,out);
		m = latencyqueue.first;
	}

}

void ProcessResendQueue (void) {
	HRESULT hr = E_FAIL;
	LPFLOWQ lpFlowQ;
	int i,numresends;
	DWORD rmask;
	DPID  id;
	numresends = 0;
	rmask = FindResendCopy(&sendqueue, &gFlowMsg);
	while (rmask ) {
		if(gpComm->debugComm &&  numresends== 0) TRACE("Entering ProcessResendQueue \n");
		for (i = 1; i< MAX_PLAYERS ; i++) {
			id = gpComm->m_PlayerId[i];
			if ((id == 0) || (id == 0xffffffff)) continue;
			lpFlowQ = FindFlowQ(id);
			if(!lpFlowQ) continue;
			if ((rmask & GetReSendMask(id)) && (gFlowMsg.seq >= lpFlowQ->hehas)) {
				gFlowMsg.got_thru = lpFlowQ->gotseq;
				gFlowMsg.xsum = 0;
				gFlowMsg.xsum = XorSum((LPGENERICMSG)&gFlowMsg);
				dbFlowResendSeq(lpFlowQ, gFlowMsg.seq);
				hr = gpComm->Send(id, 0, (LPVOID)&gFlowMsg, gFlowMsg.tdg.tdg_Size);    
				if(gpComm->debugComm) TRACE("RESENDING %d to %x size %d \n", gFlowMsg.seq, id, gFlowMsg.tdg.tdg_Size);
				if (FAILED(hr)) {
					TRACE("DPlaySend Failure %x to %x size %d\n", hr, id, gFlowMsg.tdg.tdg_Size);
					if ( hr == E_FAIL) return;
					if ( hr == DPERR_BUSY ) ShowError(IDS_DPERR_BUSY);
					if ( hr == DPERR_INVALIDOBJECT ) ShowError(IDS_DPERR_INVALIDOBJECT);
					if ( hr == DPERR_INVALIDPARAMS ) {
						// ShowError(IDS_DPERR_INVALIDPARAMS);
						TRACE("DPLAY ERROR: INVALID PARAMETERS\n");
						return;
					}
					if ( hr == DPERR_INVALIDPLAYER ) {
						// ShowError(DPERR_INVALIDPLAYER);
						TRACE("DPLAY ERROR: INVALID PLAYER\n");
						return;
					}
					if ( hr == DPERR_SENDTOOBIG ) ShowError(IDS_DPERR_SENDTOOBIG);
				}
			}
		}
		numresends++;
		if( numresends > 2 ) break;  // Limit 2 per frame   
		rmask = FindResendCopy(&sendqueue, &gFlowMsg);
	}

if(gpComm->debugComm && numresends) TRACE("Exiting ProcessResendQueue \n");
}

// Called only when we are in a PAUSE_FLOW 
// Resend Nacks to each player and tell them how many of his messages we have
//  received.   When we are in a PAUSE_FLOW we should not generate any new Flow Seq Messages

void ProcessResendNacks (void) {
	HRESULT hr = E_FAIL;
    LPFLOWQ myflowq;
	// LPFLOWQ lpFlow;
    LPFLOWPULSEMSG lpFlowPulseMsg;
	LPFLOWMSG pFlowMsg;
	DWORD elapsed,now;
	int i;
	return;
	now = GetTickCount();
	myflowq = FindFlowQ(gpComm->m_DPId);
	lpFlowPulseMsg = &gAMFlowPulseMsg;
	if (myflowq == NULL ) return;
    elapsed = now -  gpComm->m_TimeSent;
	if(elapsed < gpComm->MAXSENDINTERVAL) return;
	if (!myflowq->active) return; 
	pFlowMsg = (LPFLOWMSG)&gAMPAUSEFlowMsg;
	pFlowMsg->seq = myflowq->nxtSeq;
	pFlowMsg->tdg.tdg_Size = sizeof(TDGHDR)+sizeof(FLOWHDR);
	for (i=1;i<(int)gpComm->m_NumDPPlayers;i++) {
		hr = SendGameMessage((LPGENERICMSG) pFlowMsg, gpComm->m_PlayerId[i], gpComm->m_SendFlags);
		TRACE ("Sending Flow Packet seq %d to %x \n",myflowq->nxtSeq, gpComm->m_PlayerId[i]);
		}
 		myflowq->nxtSeq++;

		int nfree;
		nfree = ListSize(&freelist) ;
		if ( (nfree > (MAX_MSGS/2))  ) {
			TRACE("FLOW UNPAUSE nfree = %d\n",nfree);
			gpGame->UnPauseGame(PAUSE_FLOW);
		}
#if 0
	for(i=1;i<gpComm->m_NumDPPlayers;i++) {
		if (gpComm->m_PlayerId[i] == 0 || gpComm->m_PlayerId[i]== 0xffffffff) continue;
		lpFlow = FindFlowQ(gpComm->m_PlayerId[i]);
		if (lpFlow == NULL) continue;
		expected = lpFlow->gotseq+1;
		nackfrom = 0;
		if ( lpFlow->pendingqueue.first != NULL )
				nackfrom = HeadSeq(&(lpFlow->pendingqueue))-1;
		nackthru = nackfrom;
		lpFlowPulseMsg->seqfrom = nackfrom;
		lpFlowPulseMsg->seqthru = nackthru;
		lpFlowPulseMsg->got_thru = lpFlow->gotseq;
		if (nackthru < nackfrom) nackthru = nackfrom;
		if (nackthru-nackfrom > MAXMISSING ) {
			TRACE("Flow Nacking ERROR too many missing from %d thru %d \n",nackfrom , nackthru );
			}
		lpFlow->numNacks += (nackthru-nackfrom+1);
		if (gpComm->debugComm)  TRACE("ProcessResend Flow Nacking %d thru %d  to %s at time %d I am good thru %d \n",nackfrom , nackthru, 
			gpComm->GetColorStr(gpComm->m_PlayerId[i])  , now, lpFlow->gotseq);
		SendGameMessage( (LPGENERICMSG) lpFlowPulseMsg, gpComm->m_PlayerId[i], 0 );
	}
   gpComm->m_TimeSent = now;
#endif
}


void BigTimeCommError( void) {
	
	if (!AbortInProgress ) {
		AbortInProgress = TRUE;
		ShowError(IDS_DPERR_NOBUFFERS);
	//	PostMessage( ghWndMain, WM_CLOSE, 0, 0 );
		ScrnOnAbortMission(NULL);
	}
}



//  debug routines only not needed for functionality
void dbFlowSendSeq(LPFLOWQ lpflow, DWORD seq) 
{
	if(lpflow ) lpflow->SendHistory[seq%NSEQPIXELS] = 1;
}

;
void dbFlowAckSeq(LPFLOWQ lpflow, DWORD seq)
{
	if(lpflow ) lpflow->SendHistory[seq%NSEQPIXELS] = 0;
}


void dbFlowResendSeq(LPFLOWQ lpflow, DWORD seq)
{
	if(lpflow ) lpflow->SendHistory[seq%NSEQPIXELS] = 2;
}


void dbFlowReceiveSeq(LPFLOWQ lpflow, DWORD seq)
{
	if(lpflow )lpflow->ReceiveHistory[seq%NSEQPIXELS] = 1;
}

void dbFlowProcessSeq(LPFLOWQ lpflow, DWORD seq)
{
	if(lpflow ) lpflow->ReceiveHistory[seq%NSEQPIXELS] = 0;
}

void dbFlowNackSeq(LPFLOWQ lpflow, DWORD seq)
{
	if(lpflow ) lpflow->ReceiveHistory[seq%NSEQPIXELS] = 2;
}

