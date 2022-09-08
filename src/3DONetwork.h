/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: 3DONetwork.h $
//
//	DESCRIPTION:	Communications interface
//
//	AUTHOR:			David Maynard
//
//	CREATED:		Thursday, April 20, 1997
//
//	REVISION:		$Header: /ArmyMen/src/3DONetwork.h 52    4/17/98 2:40a Dmaynard $
//
//	Copyright (C) 1996, 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/3DONetwork.h $
//  
//  52    4/17/98 2:40a Dmaynard
//  Defensive Coding to prevent DPlay race conditions
//  
//  51    4/15/98 3:01p Dmaynard
//  Changed receive thread to post windows message on error instead of
//  calling ShowError Dialog from the interrupt thread.
//  
//  50    4/10/98 2:57a Dmaynard
//  Added BigTimeCommError  which does a ShowError and a
//  PostMessage(WMCLOSE) for fatally bad connections
//  
//  49    4/08/98 9:08p Dmaynard
//  New Flow Control for case when connection is so bad we have run out of
//  message buffers
//  
//  47    4/02/98 12:13p Dmaynard
//  Changed Max Msg size to 1024.  
//  
//  46    3/30/98 5:15p Dmaynard
//  Sending Exe version in PlayerMessage and host sends exe version in
//  MapMsg.  Not doing anything with them yet.
//  
//  45    3/27/98 8:26p Dmaynard
//  Code to send events on DPSYS Messages
//  
//  44    3/26/98 1:35p Dmaynard
//  Added Checksumming of all Script files listed in the rule file
//  
//  43    3/25/98 6:21p Dmaynard
//  General Lobby Clean-Up.  Removed unused code. Changed to save the lobby
//  Connection settings in gpComm->m_pConnection.   Release Lobby Interface
//  appropriately.
//  
//  42    3/18/98 2:31a Nrobinso
//  match the registry name to the one the installer uses
//  
//  41    3/18/98 12:49a Nrobinso
//  remove Studio 3DO from registry setup
//  
//  40    3/17/98 4:42p Dmaynard
//  Added PAUSE_MAPLOAD instead of piggy-backing on the normal PAUSE_LOCAL
//  flags.
//  
//  39    3/17/98 10:24a Dmaynard
//  Added code for Busrt Mode Packet loss emulation
//  
//  38    3/16/98 4:15p Dmaynard
//  Limiting number of resends done in interrupt(receive) thread.  Added
//  ProcessResendQueue to do the resends in the main loop when we get
//  around to it.   Flodding the comm channel from interrupt level is a bad
//  idea.
//  
//  37    3/16/98 2:19p Dmaynard
//  Passing the Comm Message Sequence number all the way down to
//  TrooperUpdateReceiveMessage in order to handle multiple commands packed
//  into same comm sequence message.
//  
//  36    3/10/98 7:56p Dmaynard
//  Changed Latency Averaging Window to 3 seconds (instead of ten)
//  
//  35    3/02/98 11:15a Dmaynard
//  Visual Fix for latency display
//  
//  34    2/26/98 2:40p Dmaynard
//  Added some Comm debug traces and put others under gpComm->debugComm
//  runtime switch.
//  
//  33    2/26/98 12:35a Dmaynard
//  Changed ave Latency displayed to be the average over the last 100
//  messages, rather than the overall session average latency.
//  
//  32    2/25/98 11:53p Dmaynard
//  Added Latency Simulation
//  
//  31    2/24/98 6:51p Dmaynard
//  Added Latency display in Debug only mode
//  
//  30    2/19/98 2:55p Aburgess
//  modifications made to support BAD Map detection in remote players.
//  Added checks for BootCamp game play mode.
//  
//  29    2/19/98 1:58p Dmaynard
//  Added flags for whether each player has the correct map.
//  
//  28    2/16/98 10:10a Nrobinso
//  map name is part of player msg
//  
//  27    2/16/98 9:29a Nrobinso
//  make checksum unsigned longs
//  
//  26    2/09/98 7:21p Nrobinso
//  reduce name sizes
//  
//  25    2/09/98 6:13p Dmaynard
//  First Cut at handling a player leaving the game
//  
//  24    2/07/98 6:07p Nrobinso
//  multiple maps may share a rule file for multiplayer; remote display bug
//  remains
//  
//  23    1/22/98 1:22p Nrobinso
//  add bad map message
//  
//  22    1/22/98 12:00p Nrobinso
//  remove wizard thread, add checksum
//  
//  21    1/19/98 3:41p Dmaynard
//  Handling PLayers leaving during Game and Map selection.
//  
//  20    1/16/98 5:51p Dmaynard
//  Added Toggle GuaranteedSend from host and communicating this to
//  Clients.
//  
//  19    1/16/98 1:13p Dmaynard
//  Added DebugDisplay for tracing Comm Flow and Symmetric Protocol Flow.
//  
//  18    1/13/98 6:49p Dmaynard
//  Changed 3 defined constants to COmm member variables for tuning.
//  MAXSENDINTERVAl MINSENDINTERVAL AND ENOUGH_MSG_SIZE
//  
//  17    1/12/98 10:41a Aburgess
//  changed ARMYMEN_KEY to be Software/Studio 3DO/ArmyMen
//  
//  16    1/07/98 5:07p Dmaynard
//  Integration of Symmetric Flow Protocol into Armymen
//  
//  15    12/23/97 1:54p Phu
//  randomized item placement, fixes to setup mode
//  
//  14    12/09/97 12:31p Dmaynard
//  Added Boolean to Ready Message
//  
//  12    12/05/97 11:47a Dmaynard
//  Added END_SETUP_MSG with appropraite initilization and dispatch
//  rountines
//  
//  11    11/30/97 3:02p Dmaynard
//  Added PlayerMsg which Host will send to all players every time a new
//  player joins.  Also Added ColorMsg which joining players use to request
//  a color.
//  
//  10    11/16/97 5:29p Dmaynard
//  Added Governor to comm to limit packet rate to a maximum of 30
//  packets/second, and a minimum of one packet/second (heartbeat).
//  
//  9     11/12/97 4:01p Dmaynard
//  Added Remote Pause mechanism for Multi-Payer mode
//  
//  8     10/24/97 11:18a Dmaynard
//  Added MultiPlayer menu option and start multiplayer game options and
//  changed how the translation of UniqueID's is handled.  UniqueID are now
//  translated into universal (color coded) format before  sending and each
//  macine translates from color to local index in receive armymessage.
//  
//  7     10/23/97 6:24p Dmaynard
//  
//  5     8/08/97 10:09a Nrobinso
//  removed headers thata are being precompiled
//  
//  4     7/31/97 6:21p Dmaynard
//  
//  3     7/25/97 3:58p Dmaynard
//  ReadyMsgs and StartGameMsgs
//  
//  2     7/18/97 9:23a Aburgess
//  added Pause MSG defines
//  
//  1     7/03/97 5:17p Nrobinso
//  
//  10    5/08/97 9:32a Dmaynard
//  added extern Handle ghThread for wozard thread
//  
//  9     5/07/97 2:29p Dmaynard
//  Added Checksum and Sequence numbers to Packed ArmyMsgs
//  
//  8     5/02/97 6:17p Dmaynard
//  Comm Clean-up to get rid of commc.cpp and lobby.cpp
//  
//  7     5/01/97 3:38p Dmaynard
//  
//  6     5/01/97 12:55p Dmaynard
//  Message buffering tuning
//  
//  5     5/01/97 10:40a Dmaynard
//  Added START_GAME_MSG
//  
//  4     4/29/97 11:38a Dmaynard
//  First Working Comm Code
//  
//  3     4/28/97 6:23p Dmaynard
//  Comm Clean up
//  
//  2     4/27/97 1:46p Dmaynard
//  Added header. Initial Check-in
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef _3DONetwork_h
#define _3DONetwork_h
#include <stdio.h>
#include <dplay.h>


#ifdef __cplusplus
#define C_EXTERN extern "C"
#else
#define C_EXTERN extern
#endif


// The following  define makes the recieve thread send acks to log msgs
#define THREAD_LOGGING

#define MAX_MSGS	400
#define MAXMISSING	 50
#define MAX_MSG_SIZE	1024 
#define TIMEOUT		10000
// #define ENOUGH_MSG_SIZE  1024			// send packed msg when it reaches this size
#define UM_TDG_DPLAY	WM_USER+100
#define UM_TDG_MANLOB	UM_TDG_DPLAY+1
#define UM_TDG_LAUNCH	UM_TDG_MANLOB+1
#define UM_TDG_ABORT	UM_TDG_LAUNCH+1
#define UM_TDG_CREATEPLAYER	UM_TDG_ABORT+1
#define UM_TDG_MPSTART	UM_TDG_CREATEPLAYER+1
#define UM_TDG_PLAYER	UM_TDG_MPSTART+1
#define UM_TDG_COMM_ERROR	UM_TDG_PLAYER+1
#define UM_TDG_DESTROYPLAYER	UM_TDG_COMM_ERROR+1
#define UM_TDG_NEWHOST	UM_TDG_DESTROYPLAYER+1
#define UM_TDG_LAST	UM_TDG_NEWHOST

//----------------------------------------------------------
// communication packet structures
//----------------------------------------------------------
#define MSG_LOG         0x1		// log message containing sequence number and time stamps
#define MSG_LOGACK      0x2		// log acknowledgement message containing sequence number and time stamps
#define MSG_CHAT		0x3		// chat message
#define MSG_PACKED		0x4		// PACKED message contains multiple sub messages
#define MSG_START_GAME	0x5		// Host says begin all players have hit start
#define MSG_PAUSE_GAME	0x6		// pause all game processing
#define MSG_READY_GAME	0x7		// This player has hit start
#define MSG_PLAYER		0x8		// Sent by Host when players join or choose colors
#define MSG_COLOR		0x9		// Sent by Players to request a color
#define MSG_END_SETUP	0xa		// Sent by Players to end setup phase
#define MSG_FLOW        0xb     // Flow sequenced message containing sequence number and time stamps
#define MSG_FLOWNACK    0xc     // Flow sequenced Nack message containing sequence number and time stamps
#define MSG_ERROR		0xd	
#define MSG_SET_FLAGS	0xe		// Host sends new session parameters
#define MSG_MAP			0xf		// map status message
#define MSG_FLOWPULSE   0x10     // Flow sequenced Pulse message containing sequence number and time stamps

#define MAXNAMELENGTH 256
#define MAXDPLAYCHANNELS 4
#define MAXHZ 62
#define MAXSECONDS 180
#define MAXSTATS  MAXHZ*MAXSECONDS

#define CHAT_TEXT_MAX	256

// program states
enum
{
    PS_SPLASH,
    PS_ACTIVE,
    PS_REST
};

#define     MAX_PLAYERNAME  32
#define     MAX_SESSIONNAME 32
#define     MAX_WINDOWTITLE 32
#define     MAX_ERRORMSG    256
#define     MAX_FONTNAME    32
#define		MAXMAPNAMLENGTH 32

// default window size of 640  
#define		NSEQPIXELS		120

// tree view image info
#define CX_BITMAP       25
#define CY_BITMAP       25
#define NUM_BITMAPS      2

// registry info
#define ARMYMEN_KEY (TEXT("Software\\The 3DO Company\\Army Men"))

#define DEBUG_OUT(s)	TDG_DEBUG_OUT(s)

 // externals

extern		HINSTANCE							ghinst;						// Application instance handle      

extern		DWORD  repliesmask;
extern		DWORD  resendmask;   

// list stuff
typedef struct _TDGMSG
{
	struct _TDGMSG *prev;
	struct _TDGMSG *next;
	DPID	idFrom, idTo;
	DWORD	dwMsgBufferMaxSize;
	DWORD	seq;
	DWORD	replies;
	DWORD	timesent;
	void    *data;
	DWORD datasize;
} TDGMSG;


// header may change based on type of service, guarenteed or not
// We will actually try to be completey transparent and work along
// with the apps messages
// All messages go through our interfaces. TDG
// external header used for all user messages
// Type and Size fields must be filled out prior to being sent to
// network system
typedef struct _TDGHDR
{
	DWORD	tdg_Type;	// must conform to dplay
	DWORD	tdg_Size;	// size of entire msg including this header
} TDGHDR;

// internal TDG stuff
typedef struct _TDGLIST
{
	HANDLE	MutexLock;
	TDGMSG *first;
	TDGMSG *last;
	int    numItems;
} TDGLIST;


// all messages will start out this way
typedef struct _GENERICMSG
{
	TDGHDR		tdg;
} GENERICMSG, *LPGENERICMSG;

typedef struct _LOGMSG
{
	TDGHDR		tdg;
    DWORD		seq;
	DWORD		xsum;
	DWORD		data[(MAX_MSG_SIZE-sizeof(TDGHDR)-4+3)/4];
} LOGMSG, *LPLOGMSG;

typedef struct _LOGACKMSG
{
	TDGHDR		tdg;
    DWORD		seq;
	DWORD		xsum;
} LOGACKMSG, *LPLOGACKMSG;

typedef struct _CHATMSG
{
	TDGHDR		tdg;
    char		text[CHAT_TEXT_MAX];
	
} CHATMSG, *LPCHATMSG;

typedef struct _PACKEDHDR
{
    DWORD		seq;
	DWORD		xsum;
} PACKEDHDR, *LPPACKEDHDR;

typedef struct _PACKEDMSG
{
	TDGHDR		tdg;
    PACKEDHDR	phdr;
	DWORD		data[(MAX_MSG_SIZE-(sizeof(TDGHDR)+sizeof(PACKEDHDR))+3)/4];
} PACKEDMSG, *LPPACKEDMSG;


typedef struct _PLAYERDEF
{
DPID		playerID;
DWORD		playerColor;
DWORD		flags;
DWORD		playerMask;
char		name[MAX_PLAYERNAME];
} PLAYERDEF, *LPPLAYERDEF;


typedef struct _STARTMSG
{
	TDGHDR		tdg;
    DWORD		numPlayers;
    DPID		hostID;
	PLAYERDEF	player[MAXDPLAYCHANNELS];
	DWORD		randseed;
} STARTMSG, *LPSTARTMSG;


typedef struct _PLAYERMSG
{
	TDGHDR		tdg;
    DWORD		numPlayers;
    DPID		hostID;
	BOOL		startGame;
	BOOL		newMap;
	char		ruleName[MAXMAPNAMLENGTH];
	char		mapName[MAXMAPNAMLENGTH];
	DWORD		mapSum;
	DWORD		ruleSum;
	PLAYERDEF	player[MAXDPLAYCHANNELS];
	DWORD		majorversion;
	DWORD		minorversion;
} PLAYERMSG, *LPPLAYERMSG;

typedef struct _READYMSG
{
	TDGHDR		tdg;
	DWORD       ready;
} READYMSG, *LPREADYMSG;


typedef struct _PAUSEMSG
{
	TDGHDR		tdg;
	DWORD		pause;
	DWORD		pauseflags;
} PAUSEMSG, *LPPAUSEMSG;

typedef enum
{
	MAP_OK = 0,
	MAP_BAD_CHECKSUM,
	MAP_NO_MAP,
	MAP_BAD_RULECHECKSUM,
	MAP_IM_READY,
	MAP_NULL
} MAP_ERROR;

typedef struct _MAPMSG
{
	TDGHDR		tdg;
	DWORD		error;
	DWORD		cksum;
	DWORD		majorversion;
	DWORD		minorversion;
} MAPMSG, *LPMAPMSG;

typedef struct _COLORMSG
{
	TDGHDR		tdg;
	DWORD		color;
} COLORMSG, *LPCOLORMSG;

typedef struct _ENDSETUPMSG
{
	TDGHDR		tdg;
} ENDSETUPMSG, *LPENDSETUPMSG;

typedef struct _FLAGSMSG
{
	TDGHDR		tdg;
	DWORD		flags;
	DWORD		meanLatency;
	DWORD		deviationLatency;
} FLAGSMSG, *LPFLAGSMSG;


typedef struct _FLOWNACKMSG
{
	TDGHDR		tdg;
    DWORD		seqfrom;
	DWORD		seqthru;
} FLOWNACKMSG, *LPFLOWNACKMSG;

typedef struct _FLOWPULSEMSG
{
	TDGHDR		tdg;
    DWORD		seqfrom;
	DWORD		seqthru;
	DWORD		got_thru;
} FLOWPULSEMSG, *LPFLOWPULSEMSG;

// Change this if you change the FLOWMSG Below;

typedef struct _FLOWHDR
{

    DWORD		seq;
	DWORD		xsum;
	DWORD		got_thru;
} FLOWHDR, *LPFLOWHDR;


typedef struct _FLOWMSG
{
	TDGHDR		tdg;
    DWORD		seq;
	DWORD		xsum;
	DWORD		got_thru;
	DWORD		data[(MAX_MSG_SIZE-sizeof(TDGHDR)-sizeof(FLOWHDR)+3)/4];

} FLOWMSG, *LPFLOWMSG;

typedef struct _ERRORMSG
{
TDGHDR		tdg;
DWORD		errNum;
char	errtext[256];
} ERRORMSG, *LPERRORMSG;



#define		MAXNACKRECS 60
#define		MAXLATENCYBINS 32
#define     LATENCYDIVISOR 10

typedef struct _NACKREC
{
	DWORD	seq;
	DWORD	time;
	DWORD   count;
} NACKREC;


typedef struct _FLOWQ
{
	DPID		id;				// The DPLAY Player ID 
	DWORD		gotseq;			// the seq of the highest in-sequence message received (we are good thru this)
	DWORD		maxseq;			// highest seq message received
	DWORD		hehas;			//  This remote player has acked our messages thru this seq #
	DWORD		ackedthru;		// we have told him we have received thru this seq
	DWORD		pmask;			// bit mask for this player, used to track replies
	DWORD		resendbit;		// bit mask for this player, used to track resends
	DWORD		timeacked;		// the last time at which we sent a packet to this players
	DWORD		packetsfrom;	// number of packets received from this player
	DWORD		bytesfrom;		// number of bytes received from this player
	DWORD		packetsto;		// number of packets sent to this player
	DWORD		bytesto;		// number of bytes sent to this player
	DWORD		acksfrom;		// number of packets acked  by by this player
	DWORD		acksto;			// number of packets of his we have acked
	DWORD		numNacks;		// number of packets nacked by this player
	DWORD		numResends;		// number of packets resent to this player
	DWORD		numDupes;		// number of duplicate packets from this player
	DWORD		minLatency;		// minimum latency sending to this player
	DWORD		maxLatency;		// maximum latency sneding to this player 
	DWORD		totalLatency;	// total latency sending to this player
	DWORD		minInterval;		// minimum latency sending to this player
	DWORD		maxInterval;		// maximum latency sneding to this player 
	DWORD		totalInterval;	// total latency sending to this player
	DWORD		sessionStart;	// time session started
	DWORD		appSeq;			// The App level sequence number expected
	DWORD		dataRate;		// Send a Message every dataRate milliseconds
	DWORD		targetDataRate;  //  Try to maintain this data rate
	DWORD		dataSize;		// Data Size for messages
	DWORD		timeReceived;	//  The time at which we last received an in sequence message
	DWORD		wasAliveAt;		//  The time at which we last any message
	TDGLIST		pendingqueue;	// out of sequence messages pending delivery in proper sequence
//	int			cDataSize;
//	int			cDataRate;
	BOOL		active;			// send messages
	DWORD		errcnt;			// error count (received checksum errors)
	DWORD		mswakeup;
	DWORD		nxtSeq;			// our next Seq to Send
	BOOL		paused;			// this flow is currently in paused state (will receive won't send)
	BOOL		guaranteed;		// use Guaranteed Send mode
	BOOL		emulatePacketLoss;	// emulate packet Loss on Send	
	BOOL		burstPacketLoss;	// emulate packet Loss on Send	
	DWORD		packetLoss;			// a percent 0 to 100
	BOOL		emulateLatency;		// emulate Latency on Send
	DWORD		meanLatency;		// in ms
	DWORD		deviationLatency;		// psuedo standard deviation 0 sharp curve 100 flat curve
	int			nNackRecs;
	NACKREC     rec[MAXNACKRECS];
	DWORD		nackCount[4];
	int			latencyIndex;
	long int	latencyBin[MAXLATENCYBINS];
	DWORD		SendHistory[NSEQPIXELS];
	DWORD		ReceiveHistory[NSEQPIXELS];
} FLOWQ, *LPFLOWQ;



extern HWND ghWndMain;         // Main application window handle
								// messages are sent to this window handle

//extern HANDLE	ghThread;		// Handle for wizard property sheet thread

void AddMsg(TDGLIST *l, TDGMSG *m);

TDGMSG *RemHead(TDGLIST *l);
TDGMSG *InsertMsg(TDGLIST *l, TDGMSG *msg) ;

// Supplied by Main application
BOOL ProcessMsgLocal(TDGMSG *m);	// returns TRUE if no need to PostMsg
void ExitGame(void);			// triggers msg to end game
					// this holds off processing packets

// falling is called by packet processing instead of during interrupt
void DoSystemMessage( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID idFrom, DPID
idTo );
void DoApplicationMessage( LPGENERICMSG lpMsg, DWORD dwMsgSize, DPID idFrom, DPID idTo );
void AppOutputDebugString(LPSTR s);		// called by tdgOutputDebugString
HWND ShowConnectStatus(void);
BOOL InitMsgSystem(void);
DWORD XorSum(LPGENERICMSG pMsg);
BOOL ShowError( int iStrID );


BOOL DoLocalSystemMessage(TDGMSG *m);
void Nack(DWORD seqfrom, DWORD seqthru, DPID id);
TDGMSG *FindSeq(TDGLIST *l, DWORD seq, BOOL add, DWORD mask);
void DumpList(TDGLIST *l );
LPFLOWMSG FindSeqCopy(TDGLIST *l, DWORD seq,  LPFLOWMSG lpMsg);
DWORD FindResendCopy(TDGLIST *l, DWORD seq,  LPFLOWMSG lpMsg);
void InitAllFlows(void);
DWORD GetPlayerMask(DPID id);
DWORD GetReSendMask(DPID id);





// Supplied by TDG Network Software
#define TDG_DEBUG_OUT(s)	tdgOutputDebugString(s)

void tdgOutputDebugString(LPSTR s);
void KillMsgSystem(void);
HRESULT SendGameMessage( LPGENERICMSG lpMsg, DPID idTo, DWORD flags );
void ReceiveMessages( void );
DWORD TDGTimeStamp(void);
int ListSize(TDGLIST *l);
void EmptyList(TDGLIST *l);
BOOL	CreateFlowQ( int i) ;
BOOL	CreateFlowQPlayer( DPID pid);
LPFLOWQ FindFlowQ(DPID id);
LPFLOWQ MyFlowQ(void);
BOOL  DestroyFlow(DPID id);
BOOL DoNack(LPFLOWQ lpflow, DWORD seq );
void RemNack(LPFLOWQ lpflow,DWORD seq);
void ProcessLatencyQueue (void) ;
void ProcessResendQueue(void);
void ProcessResendNacks (void);
int AveLatency(LPFLOWQ lpFlowQ);
int AveLatencyID(DPID id);
void BigTimeCommError();
//  debug routines only not needed for functionality
void dbFlowSendSeq(LPFLOWQ lpflow, DWORD seq);
void dbFlowAckSeq(LPFLOWQ lpflow, DWORD seq);
void dbFlowResendSeq(LPFLOWQ lpflow, DWORD seq);

void dbFlowReceiveSeq(LPFLOWQ lpflow, DWORD seq);
void dbFlowProcessSeq(LPFLOWQ lpflow, DWORD seq);
void dbFlowNackSeq(LPFLOWQ lpflow, DWORD seq);


#endif
