/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       gameproc.cpp
 *  Content:    Game processing code
 *
 *
 ***************************************************************************/
#include "stdafx.h"
#include "Army.h"
#include "ArmyMen.h"
#include "Ai.h"
#include "AiAccess.h"
#include "3DONetwork.h"
#include "gameproc.h"
// #include "dpgame.h"
#include "comm.h"
#include "ArmyMsg.h"
// #include "stdio.h"
// #include "dd.h"
// #include "mainfrm.h"
#include "ui.h"
#include "gameflow.h"
#include "Screen.h"
#include "map.h"
#include "event.h"
extern void BeginGame(void);
extern DWORD SetupSeed;
extern TDGLIST freelist;
extern void			ScrnUpdateRules( BOOL ForceReadRules );

//=========================================================================
/*
 * Globals
 */
DWORD							dwRetCode;
char							IncomingMessage[CHAT_TEXT_MAX];	// incoming message buffer
// Our globally defined messages
LOGMSG					gLogMsg;					// message buffer
CHATMSG					gChatMsg;
PACKEDMSG				gPackedMsg;
STARTMSG				gStartMsg;
PAUSEMSG				gPauseMsg;
PLAYERMSG				gPlayerMsg;
READYMSG				gReadyMsg;
COLORMSG				gColorMsg;
MAPMSG					gMapMsg;
ENDSETUPMSG				gEndSetupMsg;


FLOWMSG					gFlowMsg;
FLOWMSG					gAMFlowMsg;
FLOWMSG					gAMPAUSEFlowMsg;
FLOWMSG					gintFlowMsg;
FLOWNACKMSG				gFlowNackMsg;				// used in interrupt level processing
FLOWPULSEMSG			gAMFlowPulseMsg;				// used in mainframe processing
ERRORMSG				gErrorMsg;					// message buffer

extern LOGACKMSG		gLogAckMsg;					// message buffer

//=========================================================================
// external prototypes
//=========================================================================
extern	void	ReleaseRemotePause( void );
extern LONG	ScrnOnAbortMission( HSCREENBTN hScreenBtn );

//=========================================================================
// local prototypes
//=========================================================================
void	RemoteGamePause(LPPAUSEMSG lpMsg, DPID idFrom);

//=========================================================================

	/*
	 * InitMessageBuffers
	 *
	 * Sets up buffes used for sending different types of messages
	 */

	
void InitMessageBuffers(void)
{
    gLogMsg.tdg.tdg_Type		= MSG_LOG;
    gLogMsg.tdg.tdg_Size		= sizeof(LOGMSG);
    gLogAckMsg.tdg.tdg_Type		= MSG_LOGACK;
    gLogAckMsg.tdg.tdg_Size		= sizeof(LOGACKMSG);
    gChatMsg.tdg.tdg_Type		= MSG_CHAT;
    gChatMsg.tdg.tdg_Size		= sizeof(CHATMSG);
    gPackedMsg.tdg.tdg_Type		= MSG_PACKED;
    gPackedMsg.tdg.tdg_Size		= sizeof(TDGHDR)+sizeof(PACKEDHDR);
    gStartMsg.tdg.tdg_Type		= MSG_START_GAME;
    gStartMsg.tdg.tdg_Size		= sizeof(STARTMSG);
    gPlayerMsg.tdg.tdg_Type		= MSG_PLAYER;
    gPlayerMsg.tdg.tdg_Size		= sizeof(PLAYERMSG);
    gPauseMsg.tdg.tdg_Type		= MSG_PAUSE_GAME;
    gPauseMsg.tdg.tdg_Size		= sizeof(PAUSEMSG);
    gReadyMsg.tdg.tdg_Type		= MSG_READY_GAME;
    gReadyMsg.tdg.tdg_Size		= sizeof(READYMSG);
    gMapMsg.tdg.tdg_Type		= MSG_MAP;
    gMapMsg.tdg.tdg_Size		= sizeof(MAPMSG);
    gColorMsg.tdg.tdg_Type		= MSG_COLOR;
    gColorMsg.tdg.tdg_Size		= sizeof(COLORMSG);
    gEndSetupMsg.tdg.tdg_Type	= MSG_END_SETUP;
    gEndSetupMsg.tdg.tdg_Size	= sizeof(ENDSETUPMSG);
    gErrorMsg.tdg.tdg_Type		= MSG_ERROR;
    gErrorMsg.tdg.tdg_Size		= sizeof(ERRORMSG);
    gFlowMsg.tdg.tdg_Type		= MSG_FLOW;
    gFlowMsg.tdg.tdg_Size		= sizeof(FLOWMSG);
    gAMFlowMsg.tdg.tdg_Type		= MSG_FLOW;
    gAMFlowMsg.tdg.tdg_Size		= sizeof(TDGHDR)+sizeof(FLOWHDR);  // no game data yet
    gAMPAUSEFlowMsg.tdg.tdg_Type		= MSG_FLOW;
    gAMPAUSEFlowMsg.tdg.tdg_Size		= sizeof(TDGHDR)+sizeof(FLOWHDR);  // no game data yet
	gintFlowMsg.tdg.tdg_Type	= MSG_FLOW;
    gintFlowMsg.tdg.tdg_Size	= sizeof(FLOWMSG);
	gFlowNackMsg.tdg.tdg_Type	= MSG_FLOWNACK;
	gFlowNackMsg.tdg.tdg_Size	= sizeof(FLOWNACKMSG);
	gAMFlowPulseMsg.tdg.tdg_Type	= MSG_FLOWPULSE;
	gAMFlowPulseMsg.tdg.tdg_Size	= sizeof(FLOWPULSEMSG);
}



BOOL ProcessMsgLocal(TDGMSG *m)
{
	// all messages are defered for now
	return FALSE;
}

/*
 * DoApplicationMessage
 *
 * Evaluates an application message and performs appropriate actions
 */
void DoApplicationMessage( LPGENERICMSG lpMsg, DWORD dwMsgSize, DPID idFrom, DPID idTo )
{        


	//	TRACE("DoAppMsg %lx from=%lx  \n",lpMsg->tdg.tdg_Type,idFrom,0);

    switch( lpMsg->tdg.tdg_Type )
    {

       case MSG_LOG:
        {
            LPLOGMSG lpLogMsg;
            LPLOGACKMSG  lpLogAckMsg = &gLogAckMsg;
			lpLogMsg = (LPLOGMSG) lpMsg;
			// TRACE("Log id=%x Seq = %d time= %d %d\n", idFrom, lpLogMsg->seq, GetTickCount());
			lpLogAckMsg->seq = lpLogMsg->seq;
			lpLogAckMsg->xsum = XorSum((LPGENERICMSG)lpLogMsg);
#ifndef THREAD_LOGGING
			SendGameMessage( (LPGENERICMSG) lpLogAckMsg, idFrom, 0 );
#endif
		}
        break;
       case MSG_LOGACK:
        {
            
			LPLOGACKMSG  lpLogAckMsg;
			lpLogAckMsg = (LPLOGACKMSG) lpMsg;
			//if (gbIsHost) NoteAck(idFrom,lpLogAckMsg->seq,lpLogAckMsg->xsum);
			//else NoteAck(gOurID,lpLogAckMsg->seq,lpLogAckMsg->xsum);
			// TRACE("ACK id=%x Seq = %d time= %d \n", idFrom, lpLogAckMsg->seq, 0);
		}
        break;
       case MSG_FLOW:
        {
            UnPackMessage((LPFLOWMSG)lpMsg,idFrom);
			dbFlowProcessSeq(FindFlowQ(idFrom),((LPFLOWMSG)lpMsg)->seq);
		}
        break;
       case MSG_START_GAME:
        {
        if (gpComm->m_bHost) {
			TRACE("Message Error:  Host should not receive STARTGAMEMSG\n");
		}
		ReceiveStartGameMsg((LPSTARTMSG)lpMsg , idFrom);
		}
        break;

       case MSG_PLAYER:
        {
        if (gpComm->m_bHost) {
			TRACE("Message Error:  Host should not receive PLAYERMSG\n");
		}
		ReceivePlayerMsg((LPPLAYERMSG)lpMsg , idFrom);
		}
        break;

       case MSG_MAP:
        {
			ReceiveMapMsg((LPMAPMSG)lpMsg , idFrom);
		}
        break;

       case MSG_COLOR:
        {
        if (!gpComm->m_bHost) {
			TRACE("Message Error:  Slaves should not receive COLORMSG\n");
		}
		else ReceiveColorMsg((LPCOLORMSG)lpMsg , idFrom);
		}
        break;

       case MSG_READY_GAME:
        {
          ReceiveGameReadyMsg ((LPREADYMSG)lpMsg,idFrom);
		}
        break;

        case MSG_CHAT:
        {
            
			LPCHATMSG  lpChatMsg;
			lpChatMsg = (LPCHATMSG) lpMsg;
            // lie and say player 1 sent it... should be 1,2, or 3
			if ( gpGame->GetState() == GAME_TITLE_SCREEN_STATE)
				ScrnReceiveChatMessage(lpChatMsg->text);
			else
				receivechatmessage(lpChatMsg->text);

			//if (gbIsHost) NoteAck(idFrom,lpLogAckMsg->seq,lpLogAckMsg->xsum);
			//else NoteAck(gOurID,lpLogAckMsg->seq,lpLogAckMsg->xsum);
			// TRACE("ACK id=%x Seq = %d time= %d \n", idFrom, lpLogAckMsg->seq, 0);
		}
        break;
        case MSG_PAUSE_GAME:
        {
			RemoteGamePause((LPPAUSEMSG)lpMsg, idFrom);
		}
        break;
        case MSG_END_SETUP:
        {
			ReceiveEndSetupMsg((LPENDSETUPMSG)lpMsg, idFrom);
		}
        break;
        case MSG_SET_FLAGS:
        {
			ReceiveSetFlagsMsg((LPFLAGSMSG)lpMsg, idFrom);
		}
        break;
default:
        {
            TRACE("Unknown message type %d\n", lpMsg->tdg.tdg_Type);
         }
        break;
    }
}

/*
 * CleanupComm
 *
 * Cleans up communication stuff
 */
void CleanupComm(void)
{
    HRESULT hr;

    // delete our player
    if( gpComm->m_pDPlay ) 
    {
        if (gpComm->m_DPId  && (gpComm->m_DPId != 0xFFFFFFFF))
		{
			hr = gpComm->DestroyPlayer();
			if (FAILED(hr))  {
			//	ShowError(IDS_DPLAY_ERROR_DP);
				TRACE("DPlay Destroy Player returned Failure \n");
		    }
		}
        
    }

    // cleanup directplay objects
    hr = gpComm->Close();
    hr = gpComm->Release();
}

/*
 * DoSystemMessage
 *
 * Evaluates system messages and performs appropriate actions
 * this is done during normal processing of app
 * also all msgs were delayed until launch completed
 */
void DoSystemMessage( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID idFrom, DPID idTo )
{
 	switch( lpMsg->dwType)
    {
    case DPSYS_CREATEPLAYERORGROUP:
        {
            int len,i;
			DWORD now;
			LPDPMSG_CREATEPLAYERORGROUP lpAddMsg = (LPDPMSG_CREATEPLAYERORGROUP) lpMsg;
 			LPDPSESSIONDESC2 lpSessionDesc;
			if(gpComm->debugComm) TRACE("CreatePlayer to=%x, name = %s id = %x\n",idTo,
					(unsigned long)  lpAddMsg->dpnName.lpszShortNameA, lpAddMsg->dpId);

            if( gpComm->m_bHost)
            {
            //  gFieldDataMsg.Blocks = gBlocks;
            //  SendGameMessage((LPGENERICMSG) &gFieldDataMsg, lpAddMsg->dpId,
			//							DPSEND_GUARANTEED);
			//	TRACE("CreatePlayer to=%x, name = %s id = %x\n",idTo,
			//			(unsigned long)  lpAddMsg->dpnName.lpszShortNameA, lpAddMsg->dpId);
		
			//	CreateChannel(lpAddMsg->dpId,lpAddMsg->dpnName.lpszShortNameA, TRUE);
			// Clean out any old players who left during the last game first
				for (i= 1; i<(int)4 ; i++) {
					if( gpComm->m_PlayerId[i] == 0xffffffff)   //  This player left the game
						gpComm->RemovePlayer(gpComm->m_PlayerId[i]);
				}
				ASSERT(	gpComm->m_NumDPPlayers < 4) ;
				gpComm->m_PlayerId[0] = gpComm->m_DPId;	// We are Host
				gpComm->m_PlayerId[gpComm->m_NumDPPlayers] = lpAddMsg->dpId;	// The Joining Player
				// For Now Host is Green, First Joiner Tan then BLUE then GRAY
				// gpComm->m_ArmyIndex[gpComm->m_NumDPPlayers] = gpComm->m_NumDPPlayers;
				gpComm->SetRemote(gpComm->m_NumDPPlayers);
				len = strlen(lpAddMsg->dpnName.lpszShortNameA);
				if (len < MAX_PLAYERNAME) {
					strcpy(gpComm->m_PlayerName[gpComm->m_NumDPPlayers] ,lpAddMsg->dpnName.lpszShortNameA) ;
				}
				gpComm->m_TimeReceived[gpComm->m_NumDPPlayers] = GetTickCount();
				gpComm->m_ArmyGotMap[gpComm->m_NumDPPlayers] = FALSE;
				gpComm->m_NumDPPlayers++;
				if (gpComm->m_NumDPPlayers >= 4 ) {
					gpComm->GetSessionDesc();
					lpSessionDesc = gpComm->m_pSDesc ;
					lpSessionDesc->dwFlags |= ( DPSESSION_JOINDISABLED | DPSESSION_NEWPLAYERSDISABLED );
					gpComm->SetSessionDesc(lpSessionDesc,0);
				}


				CreateFlowQPlayer(lpAddMsg->dpId);

				// if in multiplayer campaign select update display
				if ( ScrnGetState() == SCRN_MULTI_HOST_STATE )
					ScrnUpdateHost();
 				//  Delay one second to give DPLAY a chance to broadcast the fact that a new player has joined
				now = GetTickCount();
				while( (GetTickCount() - now) < 1000)    ;  // do nothing

				// POSSIBLE RACE CONDITION
				//  Is this msg buffer still valid when 
				//  The Message is processed by the windows loop ???
				//  Safer to use the  dpId and look up the player
				//  thru the global session descriptor.
				SendPlayerMsg(TRUE);
				PostMessage(ghWndMain, UM_TDG_CREATEPLAYER, (WPARAM)lpAddMsg->dpId, (LPARAM) lpAddMsg);
			}
			else	// if in multiplayer campaign select update display
			{
				CreateFlowQPlayer(lpAddMsg->dpId);
				ScrnUpdateRemote();
			}


        }
        break;

    case DPSYS_DESTROYPLAYERORGROUP:
        {
            LPDPMSG_DESTROYPLAYERORGROUP lpDestroyMsg = (LPDPMSG_DESTROYPLAYERORGROUP) lpMsg;
			if(gpComm->debugComm) TRACE("DestroyPlayer Id=%x, to = %x\n",lpDestroyMsg->dpId, idTo);
			PostMessage(ghWndMain, UM_TDG_DESTROYPLAYER, (WPARAM)lpDestroyMsg->dpId, (LPARAM) lpDestroyMsg);

		}
        break;

    case DPSYS_SETSESSIONDESC:
		{
		if( !gpComm->m_bHost ) gpComm->GetSessionDesc();
		}
		break;

    case DPSYS_HOST:
        {           
 			TRACE("DPSYS_HOST Size=%d, from=%x, to = %x\n",dwMsgSize, idFrom, idTo);
           // May be a race condition from DPLAY whether we get a DPSYS_HOST message
			//  Or a destroyplare message first when host leaves.
			PostMessage(ghWndMain, UM_TDG_NEWHOST, (WPARAM)0, (LPARAM) NULL);
        }

        break;

    case DPSYS_SESSIONLOST:
		{
        // inform user that session was lost
  		TRACE("SESSIONLOST   from=%x, to = %x\n", idFrom, idTo,0 );
        ShowError(IDS_DPLAY_ERROR_SL);
		}

        break;
    default:
		TRACE("UnHandled System Message %x %d \n", lpMsg->dwType,lpMsg->dwType,0);
		break;
	}
}

/*
 * Displays connection status to the user
 */
HWND ShowConnectStatus(void)
{
    HWND hwnd;

    hwnd = CreateDialog( ghinst, MAKEINTRESOURCE(IDD_CONNECT_STATUS), ghWndMain, NULL);

    return hwnd;

}

///========================================================================
//	Function:		ArmyMessageFlush(int nMin)
//
//	Description:Sends a patially filled Packed buffer and resets packing buffer
//
//	Input:			nMin  actually send if there are nMin or more bytes in buffer
//
//	Ouput:			TRUE if we actually emptyed the buffer false otherwise
//
///========================================================================
		
BOOL	ArmyMessageFlush(int nMin) {
	HRESULT hr = E_FAIL;
    LPFLOWQ myflow;
    LPFLOWMSG pFlowMsg;
	int i;
	DWORD elapsed;
	int current;
	pFlowMsg = (LPFLOWMSG)&gAMFlowMsg;
	if( ! gpComm->m_bActive) return TRUE;
	if( gpComm->m_NumDPPlayers < 2) return TRUE; // nobody is listening anyway
	current = pFlowMsg->tdg.tdg_Size-(sizeof(TDGHDR)+sizeof(FLOWHDR));
	elapsed = GetTickCount() - gpComm->m_TimeSent;
	if (((current >= nMin) && (elapsed > gpComm->MINSENDINTERVAL )) || // have we waited long enough? 
		(elapsed >  gpComm->MAXSENDINTERVAL)   ||	 // or we have waited too long
		(current >  (int)gpComm->ENOUGH_MSG_SIZE) ) {		// or the buffer is getting full
			myflow = FindFlowQ(gpComm->m_DPId);
			if ( !myflow ) {
				TRACE("myflow null %d\n", gpComm->m_DPId);
				return FALSE;
			}
			// slaves wait until they have heard from the host to start sending
			if (!myflow->active) return FALSE; 
			pFlowMsg = (LPFLOWMSG)&gAMFlowMsg;
			pFlowMsg->seq = myflow->nxtSeq;
			for (i=1;i<(int)gpComm->m_NumDPPlayers;i++) {
				hr = SendGameMessage((LPGENERICMSG) pFlowMsg, gpComm->m_PlayerId[i], gpComm->m_SendFlags);
				if (myflow->nxtSeq < 5 && gpComm->debugComm)TRACE ("Sending Flow Packet seq %d to %x \n",myflow->nxtSeq, gpComm->m_PlayerId[i]);
			}
 			myflow->nxtSeq++;

			gpComm->m_TimeSent = GetTickCount();
			pFlowMsg->tdg.tdg_Size = sizeof(TDGHDR)+sizeof(FLOWHDR);
		//  EXPERIMENTAL FLOW CONTROL STUFF;
		int nfree;
		nfree = ListSize(&freelist) ;
//		if ( (nfree < (MAX_MSGS/4))  &&  (!(gpGame->IsPaused() & PAUSE_FLOW))) {
//			TRACE("FLOW PAUSE nfree = %d\n",nfree);
//			gpGame->PauseGame(PAUSE_FLOW);
//		}

	return TRUE;
	}
return FALSE;
}

void ArmyMessageSend(ARMY_MESSAGE *pMsg){
	USHORT inc;
	LPFLOWMSG lpPM;
	BYTE *pBsrc;
	BYTE *pBdst;
	int color;
	int index;
	
	if ( gpComm->m_pDPlay == NULL) return;
	if ( !gpComm->m_bActive) return;
	if (gpComm->m_NumDPPlayers < 2) return  ; // why bother
	ArmyMessageCount(pMsg);

	// ALL Msgs MUST have at least a USHORT nSize and DWORD UniqueID
	ASSERT( (pMsg->nSize >= 6) );

	// make sure we have properly formed unique ID
	ASSERT( !(pMsg->nUniqueID & ~AI_ID_29_BIT_MASK) );

	index = EXTRACT_ARMY(pMsg->nUniqueID);
	color = gpComm->ColorFromIndex(index);

	if (pMsg->nUniqueID) {
		if ( (color >= ARMY_GREEN) && (color <= ARMY_GRAY) )
        {
			pMsg->nUniqueID = (pMsg->nUniqueID & ~AI_ID_ARMY_MASK) |
                               ENCODE_ARMY(color);
			if (EXTRACT_ARMY(pMsg->nUniqueID) >= ARMY_GREEN);
			else {
				ASSERT(0);
				TRACE("Bad color map");
			}
		}
//		else {
//			TRACE(" Sending Army %d in UNIQUEID %x \n", color, pMsg->nUniqueID);
//			ASSERT(0);
//		}
	}


	lpPM = &gAMFlowMsg;    // Eventually fix this to use working buffer from free list
	pBdst =(BYTE *)lpPM;
	pBsrc =(BYTE *)pMsg;
	inc =pMsg->nSize;

	if (inc == 0) TRACE("ArmyMessageSend Zero length message \n");
	if ((sizeof(TDGHDR)+inc) >= gpComm->m_MaxPacketSize) {
	TRACE("Error msg larger (%d) than Max (%d) in ArmyMessageSend\n",inc , gpComm->m_MaxPacketSize);
	}
	if ((lpPM->tdg.tdg_Size+inc) >= gpComm->m_MaxPacketSize) {
		while (!ArmyMessageFlush(0))
			TRACE("Send Over Flow, Couldn't Empty Buffer \n");
		ArmyMessageSend(pMsg);
		return;
	}
	pBdst += lpPM->tdg.tdg_Size;
	memcpy((void *)pBdst,(void *) pBsrc, inc);
	lpPM->tdg.tdg_Size += inc;
	if ((lpPM->tdg.tdg_Size+inc) >= gpComm->ENOUGH_MSG_SIZE) {
		ArmyMessageFlush(0);
	}
	return;
}

void UnPackMessage(LPFLOWMSG lpMsg, DPID idFrom) {
	BYTE *pB;
	ARMY_MESSAGE *lpA;
	int index;
	int packedSize;
	packedSize = lpMsg->tdg.tdg_Size;
	index = gpComm->GetArmyIndexFromID(idFrom);
	pB = (BYTE *)lpMsg +sizeof(TDGHDR)+sizeof(FLOWHDR);
	if (lpMsg->seq < 5 && gpComm->debugComm) TRACE ("Get Packed  %x bytes seq %d Chksum %x \n",lpMsg->tdg.tdg_Size,lpMsg->seq,lpMsg->xsum);
	if (XorSum((LPGENERICMSG) lpMsg)) {
		TRACE("Receive Checksum Error from %x seq %d\n",idFrom,lpMsg->seq);
		gpComm->m_CommErrorCnt[index]++;
	}
//	if (lpMsg->phdr.seq == gpComm->m_Seq[index]+1 ) gpComm->m_Seq[index]++ ;
//	else {
//		TRACE("*** DROPPED PACKET *** expected %d got %d \n",gpComm->m_Seq[index]+1,lpMsg->phdr.seq);
//		if( lpMsg->phdr.seq > (gpComm->m_Seq[index]+1)) gpComm->m_Seq[index] = lpMsg->phdr.seq;
//	}
	if (lpMsg->tdg.tdg_Size <= (sizeof(TDGHDR)+sizeof(FLOWHDR))) return;
	do {
		lpA = (ARMY_MESSAGE *) pB;
		if (lpA->nSize == 0) {
			TRACE("Received zero Length Message\n");
			return;
		}
		if (lpA->nSize >= packedSize) {
			TRACE("Received Bogus Length Message, part greater than sum\n");
			ASSERT(FALSE);
			return;
		}
		ArmyMessageReceive(lpA,index,lpMsg->seq);
		pB += lpA->nSize;
		lpMsg->tdg.tdg_Size  -= lpA->nSize;
	} while (lpMsg->tdg.tdg_Size > (sizeof(TDGHDR)+sizeof(FLOWHDR)));
}


void	SendGamePause(BOOL pause, DWORD flags){
	LPPAUSEMSG lpMsg = &gPauseMsg;
	// Use the Following for MultiPlayer
		// int i;
		// for(i=0;i<gpComm->m_NumDPPlayers;i++ ) {
		//	if( gpComm->m_PlayerId[i] != gpComm->m_DPId) {
		//		SendGameMessage( (LPGENERICMSG) lpMsg, gpComm->m_PlayerId[i], 0 );
		//	}
		// }
	// For Now with Just 2 players simply:
	if(gpGame->GameType == GAMETYPE_ONEPLAYER) return;
	if ( ! gpComm->m_bActive) return;
	lpMsg->pause = pause;
	lpMsg->pauseflags = flags;
	SendGameMessage( (LPGENERICMSG) lpMsg, DPID_ALLPLAYERS, DPSEND_GUARANTEED );
	if (gpComm->debugComm) TRACE("SendGamePause from %x  Pause =%d \n",gpComm->m_DPId, pause);
	// ReleaseRemotePause();
}

void	RemoteGamePause(LPPAUSEMSG lpMsg, DPID idFrom){
	int i;
	i = gpComm->GetArmyIndexFromID(idFrom);
	if (lpMsg->pauseflags & PAUSE_LOCAL) {
		if ( lpMsg->pause ) {
			if (i==1) gpGame->PauseGame(PAUSE_REMOTE1);
			if (i==2) gpGame->PauseGame(PAUSE_REMOTE2);
			if (i==3) gpGame->PauseGame(PAUSE_REMOTE3);
		}
		else {
			if (i==1) gpGame->UnPauseGame(PAUSE_REMOTE1);
			if (i==2) gpGame->UnPauseGame(PAUSE_REMOTE2);
			if (i==3) gpGame->UnPauseGame(PAUSE_REMOTE3);
		}
	}
	if (lpMsg->pauseflags & PAUSE_MAPLOAD) {
		if ( lpMsg->pause ) {
			if (i==1) gpGame->PauseGame(PAUSE_MAPLOAD1);
			if (i==2) gpGame->PauseGame(PAUSE_MAPLOAD2);
			if (i==3) gpGame->PauseGame(PAUSE_MAPLOAD3);
		}
		else {
			if (i==1) gpGame->UnPauseGame(PAUSE_MAPLOAD1);
			if (i==2) gpGame->UnPauseGame(PAUSE_MAPLOAD2);
			if (i==3) gpGame->UnPauseGame(PAUSE_MAPLOAD3);
		}
	}
	
	if (gpComm->debugComm) TRACE("RemoteGamePause from %x paused = %d pauseflags = %x\n",idFrom,lpMsg->pause,gpGame->IsPaused());
}

void SendGameReadyMsg(BOOL ready)	{
	int i;
	LPREADYMSG lpMsg = &gReadyMsg;
	LPENDSETUPMSG lpEndSetupMsg = &gEndSetupMsg;
	if (gpComm->debugComm) TRACE("SendGameReadyMsg\n %s", (ready ? "TRUE":"FALSE"));
	gpComm->m_ArmyReady[gpComm->GetArmyIndexFromID(gpComm->m_DPId)] = ready;
	if(gpComm->debugComm) TRACE("Setting m_ArmyReady[%d] to %s\n",gpComm->GetArmyIndexFromID(gpComm->m_DPId),(ready ? "TRUE":"FALSE"));
	lpMsg->ready = ready;
	SendGameMessage( (LPGENERICMSG) lpMsg, DPID_ALLPLAYERS, DPSEND_GUARANTEED);

	if (gpComm->m_bHost) {
		for(i=0;i<(int)gpComm->m_NumDPPlayers;i++ ) {
			if (gpComm->debugComm)TRACE("m_ArmyReady[%d] = %d \n", i, gpComm->m_ArmyReady[i]);
			if((gpComm->m_PlayerId[i] != 0xFFFFFFFF) && (gpComm->m_ArmyReady[i] == FALSE)) return;
		}
		if (gpComm->debugComm) TRACE("Sending EndSetupMessage\n");
		SendGameMessage( (LPGENERICMSG) lpEndSetupMsg, DPID_ALLPLAYERS, DPSEND_GUARANTEED );
		gpGame->SetSubState( PLAY_SUB_STATE );
	}
}

void ReceiveEndSetupMsg(LPENDSETUPMSG lpMsg, DPID idFrom){
		if (gpComm->debugComm) TRACE("ReceiveEndSetupMsg\n");
		gpGame->SetSubState( PLAY_SUB_STATE );

}		
void ReceiveGameReadyMsg(LPREADYMSG lpMsg, DPID idFrom){
	int i;
	LPENDSETUPMSG lpEndSetupMsg = &gEndSetupMsg;
	if(gpComm->debugComm) TRACE("ReceiveGameReadyMsg\n");
	
	gpComm->m_ArmyReady[gpComm->GetArmyIndexFromID(idFrom)] = lpMsg->ready;
	if(gpComm->debugComm) TRACE("Setting m_ArmyReady[%d] to %s\n",gpComm->GetArmyIndexFromID(idFrom),(lpMsg->ready ? "TRUE":"FALSE"));
	// A remote player  has hit CONTINUE 
	if ( gpComm->m_bHost && (lpMsg->ready ==FALSE) && (gpGame->GetState() == GAME_TITLE_SCREEN_STATE))
		SendPlayerMsg(TRUE);

	if (gpComm->m_bHost) {
		for(i=0;i<(int)gpComm->m_NumDPPlayers;i++ ) {
			if(gpComm->debugComm) TRACE("m_ArmyReady[%d] = %d \n", i, gpComm->m_ArmyReady[i]);
			if((gpComm->m_PlayerId[i] != 0xFFFFFFFF)  && (gpComm->m_ArmyReady[i] == FALSE)) return;
		}
		if(gpComm->debugComm)  TRACE("Sending EndSetupMessage\n");
 
		SendGameMessage( (LPGENERICMSG) lpEndSetupMsg, DPID_ALLPLAYERS, DPSEND_GUARANTEED );
		gpGame->SetSubState( PLAY_SUB_STATE );
	}
}

void StartNow ( void ) {
	int i;
	LPENDSETUPMSG lpEndSetupMsg = &gEndSetupMsg;
	if (gpComm->m_bHost) {
		for(i=0;i<(int)gpComm->m_NumDPPlayers;i++ ) {
			if(gpComm->debugComm) TRACE("m_ArmyReady[%d] = %d \n", i, gpComm->m_ArmyReady[i]);
			if((gpComm->m_PlayerId[i] != 0xFFFFFFFF)  && (gpComm->m_ArmyReady[i] == FALSE)) return;
		}
		if(gpComm->debugComm)  TRACE("Sending EndSetupMessage\n");
 
		SendGameMessage( (LPGENERICMSG) lpEndSetupMsg, DPID_ALLPLAYERS, DPSEND_GUARANTEED );
		gpGame->SetSubState( PLAY_SUB_STATE );
	}
}




static int playerslot;

BOOL WINAPI  EnumPlayersCallBack(   
	DPID            dpId,
    DWORD           dwPlayerType,
    LPCDPNAME       lpName,
    DWORD           dwFlags,
    LPVOID          lpContext ) {
	TRACE("DPPC dpId = %x PlayerName = %s, Flags = %x , context = %x slot = %d \n",
		dpId, 	lpName,	 dwFlags, 	lpContext, playerslot);
	playerslot ++;
	return TRUE;
}


void DumpSessionDesc (LPDPSESSIONDESC2 sp) {
	TRACE("Session Max Players: %d\n", sp->dwMaxPlayers);
	TRACE("Session Cur Players: %d\n", sp->dwCurrentPlayers);
	TRACE("Session Name: %s\n", sp->lpszSessionNameA);
    playerslot = 0;
    gpComm->EnumPlayers(&(gpComm->m_pSDesc->guidInstance),  EnumPlayersCallBack, 
                         (LPVOID) gpComm->m_pSDesc, 0)	;
}

BOOL WINAPI  EnumPlayersInitCallBack(   
	DPID            dpId,
    DWORD           dwPlayerType,
    LPCDPNAME       lpName,
    DWORD           dwFlags,
    LPVOID          lpContext ) {
	if (gpComm->debugComm) TRACE("InitJoin dpId = %x PlayerName = %s (%s), Flags = %x , context = %x slot = %d \n",
		dpId, 	lpName->lpszLongNameA,	lpName->lpszShortNameA, dwFlags, 	lpContext, playerslot);
	if (dpId == gpComm->m_DPId )  {  //  THIS is Me  
			gpComm->m_PlayerId[0] = dpId;
			strcpy(gpComm->m_PlayerName[0],lpName->lpszShortNameA);
	}
	else {
		gpComm->m_PlayerId[playerslot] = dpId;
		gpComm->m_ArmyIndex[playerslot] = playerslot;
		if (playerslot < (int)gpComm->m_NumDPPlayers) {
			gpComm->SetRemote(playerslot);
		}
		CreateFlowQPlayer(dpId);
		strcpy(gpComm->m_PlayerName[playerslot],lpName->lpszShortNameA);
		playerslot++;
	}
	
	return TRUE;
}

void InitJoinSession(void) {
	 gpComm->GetSessionDesc();
	 //  We are joining a session  find out who is already here
	 //  CreatePlayer for us has already been called  
	if (gpComm->debugComm) {
		TRACE("Session Max Players: %d\n", gpComm->m_pSDesc->dwMaxPlayers);
		TRACE("Session Cur Players: %d\n", gpComm->m_pSDesc->dwCurrentPlayers);
		TRACE("Session Name: %s\n", gpComm->m_pSDesc->lpszSessionNameA);
	}
	playerslot = 1;
	gpComm->m_PlayerId[0] = gpComm->m_DPId;
	gpComm->m_ArmyIndex[0] = gpComm->m_pSDesc->dwCurrentPlayers-1;
	gpComm->m_NumDPPlayers = gpComm->m_pSDesc->dwCurrentPlayers;
    gpComm->EnumPlayers(&(gpComm->m_pSDesc->guidInstance),  EnumPlayersInitCallBack, 
                         (LPVOID) gpComm->m_pSDesc, 0)	;

//  Should set my color here based on what has not been taken
}

void SendGameStartMsg(void){
//	int i;
	LPSTARTMSG lpStartMsg = &gStartMsg;
	LPDPSESSIONDESC2 lpSessionDesc;
	if (!gpComm->m_bHost) return;
 	lpStartMsg->numPlayers = gpComm->m_NumDPPlayers;
	lpStartMsg->hostID = gpComm->m_DPId;	 // We are host
	lpStartMsg->randseed = SetupSeed = (DWORD)time(NULL);
	ScrnUpdateRules(TRUE);
	if(gpComm->debugComm) TRACE("SendGameStartMsg for %d  Players: Seed is %d \n", gpComm->m_NumDPPlayers, SetupSeed);
	gpComm->GetSessionDesc();
	lpSessionDesc = gpComm->m_pSDesc ;
	lpSessionDesc->dwFlags |= ( DPSESSION_JOINDISABLED | DPSESSION_NEWPLAYERSDISABLED );
	gpComm->SetSessionDesc(lpSessionDesc,0);
	gpComm->Send(DPID_ALLPLAYERS, DPSEND_GUARANTEED , (LPVOID)lpStartMsg, lpStartMsg->tdg.tdg_Size);    

}

void SendPlayerMsg(BOOL mapChanged){
	int i;
	DWORD major,minor;
	LPPLAYERMSG lpPlayerMsg = &gPlayerMsg;
	if (!gpComm->m_bHost) return;

	lpPlayerMsg->newMap - mapChanged;
	if (mapChanged) {
		for(i=1;i<(int)gpComm->m_NumDPPlayers;i++)
			gpComm->m_ArmyGotMap[i] = FALSE;
	}

	strcpy( lpPlayerMsg->ruleName, gpGame->RuleName);
	strcpy( lpPlayerMsg->mapName, gpGame->MapName);
	lpPlayerMsg->mapSum = gpGame->MapSum;
 	lpPlayerMsg->ruleSum = gpGame->HostRuleSum;
	lpPlayerMsg->numPlayers = gpComm->m_NumDPPlayers;
	lpPlayerMsg->hostID = gpComm->m_DPId;	 // We are host

	if (gpComm->debugComm) TRACE("SendPlayerMsg for %d  Players: \n", gpComm->m_NumDPPlayers);
	if(gpComm->m_NumDPPlayers < 2) return;	   // why bother
	for(i=0;i<ARMY_LAST_ARMY;i++ ) {
			lpPlayerMsg->player[i].playerID = gpComm->m_PlayerId[i];
			lpPlayerMsg->player[i].playerColor = gpComm->m_ArmyIndex[i];
			lpPlayerMsg->player[i].flags = 0;
			strcpy(lpPlayerMsg->player[i].name, gpComm->m_PlayerName[i]);
			if (gpComm->debugComm) TRACE("                 player: %s %x %d\n",
				lpPlayerMsg->player[i].name,
				lpPlayerMsg->player[i].playerID,
				lpPlayerMsg->player[i].playerColor);
	}
	major = theApp.appVersion.major;
	minor = theApp.appVersion.minor;
	TRACE("  Send Player Message %d Players  map: %s checksum=%X rulechecksum = %x version %d.%d\n",gpComm->m_NumDPPlayers,lpPlayerMsg->ruleName,lpPlayerMsg->mapSum,lpPlayerMsg->ruleSum,major,minor);
	SendGameMessage( (LPGENERICMSG) lpPlayerMsg, DPID_ALLPLAYERS,DPSEND_GUARANTEED );
}

void ReceiveStartGameMsg(LPSTARTMSG lpMsg, DPID idFrom){
	int i;
	BOOL   letsdoit = TRUE;
	HRESULT hr;
	LPSTARTMSG lpStartMsg = &gStartMsg;
	if (gpComm->m_bHost) return;
	ScrnUpdateRules(TRUE);
	SetupSeed = lpMsg->randseed;
	if(gpComm->debugComm) TRACE("ReceiveStartGameMsg for %d Players.  Seed is %d \n",lpMsg->numPlayers, SetupSeed );
//  Verify that everything is OK with DP Session and Players
	for ( i = 1; i < gpComm->m_NumDPPlayers ; i++ ) {
	  hr = SendMapMsg(MAP_IM_READY, gpComm->m_PlayerId[i]);
	  if (hr != DP_OK)  {
		  letsdoit = FALSE ;
		  TRACE ("DPLAY ERROR SENDING TOO %x\n", gpComm->m_PlayerId[i]);
	  }
	  if (!FindFlowQ(gpComm->m_PlayerId[i]) && !CreateFlowQPlayer(gpComm->m_PlayerId[i])) {
		  letsdoit = FALSE ;
		  TRACE ("FlowQ creation Failure %x\n", gpComm->m_PlayerId[i]);
	  }
	}



	if (letsdoit ) pMainFrame->PostMessage( UM_TDG_MPSTART, 0, 0 );	
	else  {
		gpComm->GetSessionDesc();
		DumpSessionDesc(gpComm->m_pSDesc);
		ShowError(IDS_DPLAY_ERROR_JS);
		ScrnOnAbortMission(NULL);
	}
		

}


void ReceivePlayerMsg(LPPLAYERMSG lpMsg, DPID idFrom){
	int i,slot;
	char	buffer[128];
	if (gpComm->m_bHost) return;
	TRACE("ReceivePlayerMsg for %d Players. I reckoned there were %d Players \n",lpMsg->numPlayers,gpComm->m_NumDPPlayers);
	gpComm->m_HostID = lpMsg->hostID;
	ASSERT (lpMsg->hostID == idFrom) ;
	buffer[0] = '\0';

	if (gpComm->debugComm) TRACE("                 map: %s, checksum=%X\n",lpMsg->ruleName,lpMsg->mapSum);
		gpGame->RuleName = lpMsg->ruleName;

//	if(gpGame->GetState() != GAME_TITLE_SCREEN_STATE) 
//		return;

	gpGame->MapName = lpMsg->mapName;
	gpGame->MapSum = lpMsg->mapSum;
	gpGame->HostRuleSum = lpMsg->ruleSum;
	gpComm->m_NumDPPlayers =lpMsg->numPlayers;
	// POSSIBLE RACE Condition.    This message may not have ME in it yet
	for (i=0,slot=1;i<ARMY_LAST_ARMY; i++ ) {
		if (gpComm->debugComm) TRACE("                 player: %s %x %d\n",
			lpMsg->player[i].name,lpMsg->player[i].playerID,lpMsg->player[i].playerColor);
		if( lpMsg->player[i].playerID == gpComm->m_DPId ) { //THIS IS ME
			gpComm->m_PlayerId[0] = lpMsg->player[i].playerID;
			gpComm->m_ArmyIndex[0] = lpMsg->player[i].playerColor;
			strcpy(gpComm->m_PlayerName[0],lpMsg->player[i].name);
		}
		else  {
			if (slot >= ARMY_LAST_ARMY) break;
			gpComm->m_PlayerId[slot] = lpMsg->player[i].playerID;
			gpComm->m_ArmyIndex[slot] = lpMsg->player[i].playerColor;
			if( slot < (int)gpComm->m_NumDPPlayers) gpComm->SetRemote(slot);
			strcpy(gpComm->m_PlayerName[slot],lpMsg->player[i].name);
			if (!FindFlowQ(gpComm->m_PlayerId[slot]) ) CreateFlowQPlayer(gpComm->m_PlayerId[slot]);
			slot++;
		}
	}
	if(gpComm->m_PlayerId[0] == 0 || gpComm->m_PlayerId[0] == 0xffffffff) gpComm->m_PlayerId[0] = gpComm->m_DPId;
	if(gpGame->GetState() == GAME_TITLE_SCREEN_STATE) 
		ScrnUpdateRemote();
	// some other guy
	//	pMainFrame->PostMessage( UM_TDG_PLAYER, 0, 0 );	
}

HRESULT	SendMapMsg(DWORD error, DPID idTo){
	LPMAPMSG lpMsg = &gMapMsg;
	DWORD major,minor;
	HRESULT hr;
	lpMsg->error = error;
	if(gpComm->m_bHost) return DP_OK;  // Only joiners send this
	major = theApp.appVersion.major;
	minor = theApp.appVersion.minor;
	lpMsg->majorversion = major;
	lpMsg->minorversion = minor;
	if( gpComm->m_HostID ) { // This is not set until we receive the PlayerMessage from Host
		hr = SendGameMessage( (LPGENERICMSG) lpMsg, DPID_ALLPLAYERS, DPSEND_GUARANTEED );
		if(gpComm->debugComm) TRACE("SendMapMsg from %x   Error = %d \n",gpComm->m_DPId,  error);
	}
return hr;
}


void	ReceiveMapMsg(LPMAPMSG lpMsg, DPID from){
	int	index;

	if ( !(gpComm->m_bHost) )		return;		// REMOTES ignore this

	if(gpComm->debugComm) TRACE("ReceivedMapMsg from %x  Error = %d \n",from, lpMsg->error);

	// TBD: need to set player map status
	index = gpComm->GetArmyIndexFromID( from );
	switch( lpMsg->error )
	{
	case MAP_OK:
		gpComm->m_ArmyGotMap[index] = TRUE;
		break;
	case MAP_BAD_CHECKSUM:
	case MAP_BAD_RULECHECKSUM:
	case MAP_NO_MAP:
	case MAP_NULL:
		gpComm->m_ArmyGotMap[index] = FALSE;
		break;
	case MAP_IM_READY:
		break;
	}

	// if (useMPUI) ScrnUpdateHost();
}


void	SendColorMsg(DWORD color){
	LPCOLORMSG lpMsg = &gColorMsg;
	lpMsg->color = color;
	if( gpComm->m_HostID ) { // This is not set until we receive the PlayerMessage from Host
		SendGameMessage( (LPGENERICMSG) lpMsg, DPID_ALLPLAYERS, DPSEND_GUARANTEED );
		if(gpComm->debugComm) TRACE("SendColorMsg from %x , Color =%d \n",gpComm->m_DPId,  color);
	}
	// ReleaseRemotePause();
}


void	ReceiveColorMsg(LPCOLORMSG lpMsg, DPID from){
	UINT	nIndex;

	if(!(gpComm->m_bHost)) return;
	if(gpComm->debugComm) TRACE("ReceivedColorMsg from %x  Color =%d \n",from, lpMsg->color);

	// check to see if this color is available. If so, grant a request
	// for this color by sending a PLAYERMSG
	// nIndex = gpComm->GetIndexFromID( from );
		nIndex = gpComm->AcquireColor( from, (ARMY_COLOR)lpMsg->color );
		if ( nIndex != -1 )
		{
			// create the PLAYERMSG to broadcast the color acquisition
			SendPlayerMsg(FALSE);
		}
	if (  (ScrnGetState() == SCRN_MULTI_HOST_STATE)) 
		ScrnUpdateHost();
// We may still be on the continue screen after previous game ended
//	else ASSERT(0);
}

void ReceiveSetFlagsMsg(LPFLAGSMSG lpMsg, DPID from) {
	LPFLOWQ myflow;
	if(gpComm->m_bHost) return;
	gpComm->m_SendFlags = lpMsg->flags;
	myflow = FindFlowQ(gpComm->m_DPId);
	if (!myflow) return;
	myflow->meanLatency = lpMsg->meanLatency ;
	myflow->deviationLatency = lpMsg->deviationLatency;
}

static DWORD messagetime;

void TimeOutPlayers(void) {
 int i;
 DWORD now;
 DWORD pauseflags,who;
 
 pauseflags = gpGame->IsPaused();
 //  is everything is going smoothly;
 if (!pauseflags) return;
 
 //  is one of the players still loading a map? 
 
 if (pauseflags & (PAUSE_MAPLOAD1 | PAUSE_MAPLOAD2 | PAUSE_MAPLOAD3) ) return;

  //  is one of the players paused ? 
 
	if (pauseflags & (PAUSE_REMOTE1 | PAUSE_REMOTE2 | PAUSE_REMOTE3) ) return;

//  Are we already in a Comm Pause on at least one player ?

	if (!(pauseflags & (PAUSE_REMOTEGONE1 | PAUSE_REMOTEGONE2 | PAUSE_REMOTEGONE3))) return;

 // Are we the host ??

	if (!gpComm->m_bHost) return;

	now = GetTickCount();
	 for (i= 1, who = PAUSE_REMOTEGONE1; i< (int)gpComm->m_NumDPPlayers; i++ ) {
		if (gpComm->m_PlayerId[i] == 0xFFFFFFFF ) continue;
		if (((now - gpComm->m_TimeReceived[i] ) > PLAYERTIMEOUTMS) && (pauseflags & who)) {
			if (gpComm->debugComm && ((now-messagetime) > PLAYERTIMEOUTMS)) {
				TRACE("TIMING OUT PLAYER %d %s\n",i, gpComm->m_PlayerName[i]);
				messagetime = now;
			}
			if(gpComm->m_bTimeOutsEnabled) {
				PostMessage(ghWndMain, UM_TDG_DESTROYPLAYER, (WPARAM)gpComm->m_PlayerId[i], (LPARAM) NULL);
			}		
		}
		who <<= 1;
	}


}




