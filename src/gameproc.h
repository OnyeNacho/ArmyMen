/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       gameproc.h
 *  Content:    game processing info. include file
 *
 *
 ***************************************************************************/
#define IDIRECTPLAY2_OR_GREATER
#include <dplay.h>
#include "3DONetwork.h"
#include "ArmyMsg.h"

// align on single byte boundaries
// this is a stop-gap measure until the structures can be re-arranged.
#pragma pack(1)


//----------------------------------------------------------
// communication packet structures
//----------------------------------------------------------
//----------------------------------------------------------
// communication packet structures
//----------------------------------------------------------
#define MAXNAMELENGTH 256
// #define MAXDPLAYCHANNELS 4
#define MAXHZ 62
#define MAXSECONDS 180
#define MAXSTATS  MAXHZ*MAXSECONDS
#define PLAYERTIMEOUTMS	 30000

extern LOGACKMSG				gLogAckMsg;					// message buffer

/*
 * Prototypes
 */

void    CleanupComm(void);
void	InitMessageBuffers(void);
void	ChatTest(void);
void	ArmyMessageSend(ARMY_MESSAGE *pMsg);
BOOL	ArmyMessageFlush(int nMin);
void	UnPackMessage(LPFLOWMSG lpMsg, DPID idFrom);
void	SendGamePause(BOOL pause, DWORD flags);
void	RemoteGamePause(LPPAUSEMSG lpMsg, DPID idFrom);
void	ReceiveStartGameMsg(LPSTARTMSG lpMsg , DPID idFrom);
void	ReceiveGameReadyMsg (LPREADYMSG lpMsg, DPID idFrom);
void	SendGameReadyMsg(BOOL ready);
void	SendGameStartMsg(void);
void	ReceivePlayerMsg(LPPLAYERMSG lpMsg, DPID idFrom);
void	SendPlayerMsg(BOOL mapChanged);
HRESULT	SendMapMsg(DWORD error, DPID idTo);
void	ReceiveMapMsg(LPMAPMSG lpMsg, DPID from);
void	SendColorMsg(DWORD color);
void	ReceiveColorMsg(LPCOLORMSG lpMsg, DPID from);
void	ReceiveEndSetupMsg(LPENDSETUPMSG lpMsg, DPID idFrom);
void	ReceiveSetFlagsMsg(LPFLAGSMSG lpMsg, DPID idFrom);
void	DumpSessionDesc(LPDPSESSIONDESC2 sp);
extern CHATMSG						gChatMsg;					// ..
extern DWORD						dwTid;
extern DWORD						dwRetCode;
extern char							IncomingMessage[CHAT_TEXT_MAX];	// incoming message buffer
void	InitJoinSession(void);
void	StartNow ( void );
void	TimeOutPlayers(void);
// restore default alignment
#pragma pack()
