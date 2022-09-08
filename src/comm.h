//========================================================================
//	FILE:			$Workfile: comm.h $
//
//	DESCRIPTION:	Communicate header file.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		Monday, November 4th, 1996
//
//	REVISION:		$Header: /ArmyMen/src/comm.h 49    4/01/98 12:18p Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//=========================================================================
//  HISTORY
//
//  $Log: /ArmyMen/src/comm.h $
//  
//  49    4/01/98 12:18p Bwilcox
//  added defines for the return codes from isremote
//  
//  48    3/29/98 7:06p Dmaynard
//  Better reporting of Bandwidth Measurements.  Highwater mark for send
//  and receive bandwidth, and reporting Bandwidth at the end of each game.
//  
//  47    3/28/98 8:49a Nrobinso
//  
//  46    3/25/98 6:21p Dmaynard
//  General Lobby Clean-Up.  Removed unused code. Changed to save the lobby
//  Connection settings in gpComm->m_pConnection.   Release Lobby Interface
//  appropriately.
//  
//  45    3/25/98 3:28p Dmaynard
//  Added Debug Switch to Enable TimeOut  code even though we are in a
//  debug build.
//  
//  44    3/23/98 6:25p Dmaynard
//  Changed Remove ActivePlayer to return a BOOL result.
//  
//  43    3/20/98 3:36p Dmaynard
//  Better State Changes for Lobby Start-up
//  
//  42    3/19/98 2:35p Dmaynard
//  Added TIMEOUT for players in Release Builds ONLY.  If we don't hear
//  from a player for 30 seconds we remove the player.
//  
//  41    3/18/98 12:50a Nrobinso
//  pull registry access into comm
//  
//  40    3/13/98 4:49p Dmaynard
//  Changed  Comm::IsRemote to return 1 if remote, 0 if not playing, and -1
//  if was playing but has left.  Needed so scripts can send messages to
//  others players that this player has left the game.
//  
//  39    3/10/98 5:58p Dmaynard
//  Removed last dependancies upon playx.lib    you can now remove
//  dplayx.lib from your link settings.
//  
//  38    3/09/98 11:43a Dmaynard
//  Changed DPlay to load via COM interface  CoCreateInstance.
//  
//  37    3/07/98 11:54p Nrobinso
//  move .h file to stdafx
//  
//  36    2/26/98 2:41p Dmaynard
//  Added some Comm debug traces and put others under gpComm->debugComm
//  runtime switch.
//  
//  35    2/19/98 1:59p Dmaynard
//  Added flags for whether each player has the correct map.
//  
//  34    2/16/98 3:26p Dmaynard
//  Fixes for playing multiple multi-player games.  Have to resync and wait
//  until everybody is back in the map selection screen until we can start
//  another game.  Also changed it so that host remembers the last map
//  selected and come up with that as the default when you re-enter the map
//  selection screen from the continue button on the Mission Won/Loss
//  screen.
//  
//  33    1/27/98 1:43p Bwilcox
//  added IsPlayingUID
//  
//  32    1/16/98 5:51p Dmaynard
//  Added Toggle GuaranteedSend from host and communicating this to
//  Clients.
//  
//  31    1/15/98 11:21p Dmaynard
//  Comm debug display stuff
//  
//  30    1/13/98 6:49p Dmaynard
//  Changed 3 defined constants to COmm member variables for tuning.
//  MAXSENDINTERVAl MINSENDINTERVAL AND ENOUGH_MSG_SIZE
//  
//  29    1/13/98 12:35p Dmaynard
//  put many traces into conditionals based on debugComm a new public data
//  member of Comm
//  
//  28    1/07/98 5:07p Dmaynard
//  Integration of Symmetric Flow Protocol into Armymen
//  
//  27    1/06/98 10:03a Aburgess
//  added Disconnect button and reqorked session logic for MultiPlyaer mode
//  
//  26    12/16/97 5:39p Dmaynard
//  Added sequencing of PACKED ArmyMessages and checking sequence numbers
//  to detect (but not yet correct) LOST PACKETS
//  
//  25    12/11/97 5:50p Dmaynard
//  Added RemovePlayer and Handling of DSYS_SETSESSION system Message.
//  
//  24    12/10/97 7:24p Dmaynard
//  Don't allow players to Join after game has started
//  
//  23    12/10/97 9:44a Aburgess
//  changes made to centralize REGKEY access. Also
//  fixes CANCEL or BACK in multiplayer connect
//  
//  22    12/09/97 12:12p Phu
//  
//  21    12/04/97 9:04p Aburgess
//  added ReleaseColor and use of ARMY_NO_COLOR
//  
//  20    12/03/97 10:03a Aburgess
//  added prototypes for GetIndexFromID and GetColorFromID
//  
//  19    12/01/97 4:13p Dmaynard
//  Added m_PlayerName[MAX_PLAYERS]  to Comm Data Structures
//  
//  18    12/01/97 1:29p Aburgess
//  added acquire color prototype
//  
//  17    11/18/97 2:18p Dmaynard
//  GlobalUID and LocalUID functions added
//  
//  16    11/18/97 11:58a Dmaynard
//  
//  15    11/17/97 11:58a Dmaynard
//  Added printout of average session bandwidth and average sessions
//  packets/second sent and received.
//  
//  14    11/16/97 5:29p Dmaynard
//  Added Governor to comm to limit packet rate to a maximum of 30
//  packets/second, and a minimum of one packet/second (heartbeat).
//  
//  13    10/27/97 5:30p Dmaynard
//  Added GetIDFromIndex  and GetIDFromColor  which return the Direct Play
//  ID for the player.
//  
//  12    10/27/97 10:32a Dmaynard
//  Put Back the function GetNumPlayers
//  
//  11    10/24/97 5:08p Dmaynard
//  Fixed wait for heartbeat to work for n players
//  
//  10    10/24/97 11:18a Dmaynard
//  Added MultiPlayer menu option and start multiplayer game options and
//  changed how the translation of UniqueID's is handled.  UniqueID are now
//  translated into universal (color coded) format before  sending and each
//  macine translates from color to local index in receive armymessage.
//  
//  9     10/23/97 9:18a Bwilcox
//  removed GetComPlayers
//  
//  8     10/21/97 10:54a Dmaynard
//  Added ARMY_GREEN thru ARMY_GRAY constants.  New Functions in CComm
//  ColorFromIndex and IndexFromColor to map between army number and army
//  color.
//  
//  6     8/06/97 9:48a Nrobinso
//  globals.h moved to stdafx.h
//  
//  5     8/05/97 6:04p Dmaynard
//  Get the Maximum Packet size for this session from DPlay and never send
//  a package larger than this. 
//  
//  4     8/05/97 3:32p Dmaynard
//  General Clean Up. Added Stats for Total Packets and Max Packet Sizes
//  observed.  Called Release from Within Disconnect.
//  
//  3     7/25/97 3:58p Dmaynard
//  ReadyMsgs and StartGameMsgs
//  
//  2     7/15/97 12:26p Aburgess
//  Connected member variable and functions
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  24    6/13/97 6:47p Dmaynard
//  Added Initial Lobby Support. Also updated from DirectPlay2 to
//  DirectPlay3 and from DirectPlayLobby to DirectPlayLobby2 Interfaces.
//  
//  
//  23    6/13/97 5:14p Nrobinso
//  add GetNumLocalPlayers()
//  
//  22    5/09/97 3:57p Dmaynard
//  Added heartBeat to send at least one PACKED MESSAGE per frame
//  to let the other side know we are alive.
//  
//  21    5/09/97 2:07p Dmaynard
//  Added B_PAUSEDREMOTEGONE to prevent us from sending msgs when we are
//  not receiving any messages from opposing player.
//  
//  20    5/07/97 2:29p Dmaynard
//  Added Checksum and Sequence numbers to Packed ArmyMsgs
//  
//  19    5/06/97 4:10p Dmaynard
//  Added dbgCommRate display of Bandwidth
//  
//  18    5/02/97 6:17p Dmaynard
//  Comm Clean-up to get rid of commc.cpp and lobby.cpp
//  
//  17    5/01/97 12:29p Dmaynard
//  
//  16    5/01/97 10:43a Dmaynard
//  
//  15    4/30/97 7:53p Nrobinso
//  add a remote array so we can tell which players are remote
//  
//  14    4/28/97 6:24p Dmaynard
//  Comm Cleanup
//  
//  13    4/08/97 8:59a Aburgess
//  comm needs to specify the number of players in the game, including the
//  computer opponent. This method allows the application to acquire this
//  vallue.
//  
//  12    97-01-16 10:21 Ereich
//  Finally got the new state machine working.  Subtleties in the
//  transition from the old state to the new cost me many hours.
//  
//  11    97-01-10 16:34 Ereich
//  A good check-in point for code clean-up...
//  
//  10    97-01-10 10:00 Ereich
//  Day 2 house cleaning done...
//  
//  9     97-01-09 9:45 Ereich
//  Clean-up day 2 is now complete on day 3...  I love meetings!
//  
//  8     97-01-07 16:02 Ereich
//  Cleaning house day 1.  I have made many changes to most of the files
//  and it seems to still work.  So I thought I would check-it in and
//  continue tomorrow.
//  
//  7     97-01-07 9:02 Ereich
//  Checking in for the sake of merging with the latest code before I start
//  making major reorganizational changes.
//  
//  6     96-12-05 9:02 Ereich
//  Added GetArmyIndex() prototype.
//  
//  5     96-11-19 14:06 Ereich
//  Merged lobby.h with comm.h and lobby.c with comm.c.
//  Removed lobby.h and lobby.c from the project.
//  
//  4     96-11-19 13:27 Ereich
//  I have removed DUEL residue from these files.
//  
//  3     96-11-13 12:13 Ereich
//  Fix build problems.
//  
//  2     96-11-12 5:15 Ereich
//  Putting the first compiling version up to the net.
//  
//  1     96-11-11 14:57 Ereich
//  Files added to project from DUEL as a starting point.
//  
//  $Nokeywords:$
//=========================================================================

#ifndef __COMM_H__
#define __COMM_H__

#define IDIRECTPLAY2_OR_GREATER
#include <dplay.h>
#include <dplobby.h>

#define WIN32_LEAN_AND_MEAN
#include <windowsx.h>

#ifdef _DEBUG
#define ODS( a ) OutputDebugString( a )
#else
#define ODS( a )
#endif

#ifndef ARMY_COLOR
#include "Army.h"
#endif


//=========================================================================
//						GLOBAL DEFINES
//=========================================================================
#define COMM_LOCAL 0 // he is this machine
#define COMM_REMOTE 1 // he is actually human and remote
#define COMM_NOTREMOTE -1 // there is no comm player for this party


#define COMM_SAMPLE_SIZE 30
// #define MINSENDINTERVAL 33
// #define MAXSENDINTERVAL 1000

#define	COMM_NULL_KEY		(struct HKEY__ *)0xffffffff
#define	COMM_NULL_DISP		(DWORD)0xffffffff

#define	LOBBYCONNECTIONBUFFERSIZE  2048

//  Designed for 28.8 modem

#define	DESIGNSENDBW    2880
#define	DESIGNRECEIVEBW 2880

class CComm {
	// private member variables
private:
	// protected member variables
protected:
	LPGUID				m_pSessionGuid;				// Session GUID
	BOOL				m_ArmyRemote[MAX_PLAYERS];	// remote indication for each player
	UINT				m_SendIndex;
	UINT				m_ReceiveIndex;
	DWORD				m_SendTime[COMM_SAMPLE_SIZE];
	DWORD				m_SendSize[COMM_SAMPLE_SIZE];
 	DWORD				m_ReceiveTime[COMM_SAMPLE_SIZE];
	DWORD				m_ReceiveSize[COMM_SAMPLE_SIZE];
	DWORD				m_MaxReceiveSize;
	DWORD				m_MaxSendSize;
	DWORD				m_TotalBytesReceived;
	DWORD				m_TotalBytesSent;
	DWORD				m_TotalPacketsReceived;
	DWORD				m_TotalPacketsSent;

	// public member variables
public:
	DPID				m_DPId;							// Our Direct Play Id
	UINT				m_ArmyIndex[MAX_PLAYERS];		// Local Player to army color mapping mapping.
  	UINT				m_NumDPPlayers;					// number of players in the game
	UINT				m_CommErrorCnt[MAX_PLAYERS];	// Direct Play Comm Errors (bad checksum)
	LPGUID				m_pGuid;						// a pointer to the armymen guid...
	DPID				m_PlayerId[MAX_PLAYERS];		// Direct Play Player Ids
														//	Index	0 == this player
														//			1..MAX_PLAYERS-1== other players

	LPSTR				m_PlayerName[MAX_PLAYERS];
	
	UINT				m_Outstanding[MAX_PLAYERS];		// number of sends without a receive
	DWORD				m_Seq[MAX_PLAYERS];				// highest sequence number received
	BOOL				m_bHost;						// Are we hosting or joining a game     
	BOOL				m_bActive;						// flag direct play initialized and active
	BOOL				m_bSessionLost;
	DPID				m_HostID;						//  DPID for the host of this session
	LPDPSESSIONDESC2    m_pSDesc;						// session description
	LPDIRECTPLAY3A       m_pDPlay;						// directplay object pointer
	LPDPLCONNECTION		m_pConnection;					// connection settings	
	LPDIRECTPLAYLOBBY2A   m_pLobby;						// lobby object pointer 
	BOOL				m_bStartedByLobby;				// Were se launched by a Lobby?     
	BOOL				m_bTestedLobby;					// Have we tested whether we were Launched by a Lobby?     

	BOOL				m_Connected;					// are we currently connected to a lobby or another machine
	BOOL				m_ArmyReady[MAX_PLAYERS];		// ready indication for each player
	BOOL				m_ArmyGotMap[MAX_PLAYERS];		//   This player has the map and rul and script files with the correct checksums
	DWORD				m_TimeSent;						// The time we last sent a message to anybody
	DWORD				m_TimeStarted;					// The Time we sent the first sequenced ArmyMessage
	BOOL				m_TimeReceived[MAX_PLAYERS];	// The time we last received a message from this player
	DWORD				m_MaxPacketSize;				// Maximum Packet Size DPlay will
														// send as a single message in this session
														// DPlay will break up larger messages into multiple
														// packets

	HKEY				m_hRegKey;						// application registry key handle
	DWORD				m_dwRegDisp;					// application key created or opened
	DWORD				m_SendFlags;					// DPLAY SendMessage Flags
	DWORD				debugComm;						// 0 none 
	DWORD				debugDisplayComm;				// onscreen comm debug display
	DWORD				MINSENDINTERVAL;				// Don't Send Messages any closer together than this 
	DWORD				MAXSENDINTERVAL;				// Don't Send Messages any farther apart than this
	DWORD				ENOUGH_MSG_SIZE;				// Send Messages whenever the buffer gets this full
	DPCAPS				m_Caps;
	BOOL				m_bTimeOutsEnabled;
	DWORD				m_SendBWHWM;					// Send Bandwidth High Water Mark
	DWORD				m_ReceiveBWHWM;					// Receive Bandwidth High Water Mark
	DWORD				m_NumSBWIntervals;				// Number of times we calculated Bandwidth 
	DWORD				m_NumRBWIntervals;				// Number of times we calculated Bandwidth 
	DWORD				m_NumSBWExceeded;				// Number of times we calculated Bandwidth 
 	DWORD				m_NumRBWExceeded;				// Number of times we calculated Bandwidth 

	
// DPlay Capabilities
	
// private methods
private:
	// protected methods
protected:
	// public methods
public:
	CComm(void);						// default constructor
	~CComm();							// destructor

	HRESULT Close(void);				// close the direct play session
	HRESULT DPlayCreate(LPVOID lpCon);   // Create Dplay3 object using CoCreateInstance
	HRESULT CreateDirectPlayLobbyInterface( LPDIRECTPLAYLOBBY2A *lplpDirectPlayLobby2A )	;
	HRESULT	CreatePlayer(LPTSTR lpPlayerName, HANDLE hEvent, LPVOID lpData, DWORD dwDataSize);
	HRESULT	CreateSession(LPTSTR lptszSessionName);
	BOOL	IsInSession( void );

	HRESULT DestroyPlayer();	// Destroyes Our DirectPlay Player
	HRESULT EnumPlayers(LPGUID lpSessionGuid, LPDPENUMPLAYERSCALLBACK2 lpEnumCallback, 
							 LPVOID lpContext, DWORD dwFlags);
	HRESULT EnumSessions(DWORD dwTimeout, LPDPENUMSESSIONSCALLBACK2 lpEnumCallback, 
							  LPVOID lpContext, DWORD dwFlags);
	HRESULT EnumConnections(		// Enumerates Service Providers and Lobbies
		LPCGUID lpguidApplication,
		LPDPENUMCONNECTIONSCALLBACK lpEnumCallback,
		LPVOID lpContext,
		DWORD dwFlags
		);

	HRESULT GetSessionDesc(void);
	HRESULT SetSessionDesc(LPDPSESSIONDESC2 lpSessionDesc, DWORD dwFlags);
	HRESULT GetCaps(void);
	HRESULT OpenSession(LPGUID lpSessionGuid);
	HRESULT Receive(LPDPID lpidFrom, LPDPID lpidTo, DWORD dwFlags, LPVOID lpData, LPDWORD lpdwDataSize);
	HRESULT Release(void);
	HRESULT Send(DPID idTo, DWORD dwFlags,
    LPVOID lpData, DWORD dwDataSize);    
	HRESULT GetPlayerName(int player, LPDPNAME lpName, LPDWORD dwSize);
	BOOL CComm::IsDPlay(void);

	HRESULT LobbyRelease(void);
	BOOL	IsLobbyStart(void);

	void	Connected( void );
	BOOL	IsConnected( void );
	HRESULT	Disconnect( void );

	UINT	GetNumPlayers(void);
	UINT	GetArmyIndex(UINT wPlayer);
	UINT	GetArmyIndexFromID(DPID id);
	UINT	GetNumLocalPlayers(void);
	UINT	GetSendBW(void);
	UINT	GetReceiveBW(void);
	UINT	GetSendPR(void);
	UINT	GetReceivePR(void);
	BOOL	IsRemote(UINT wPlayer);
	BOOL	WasRemote(UINT wPlayer);
	BOOL	RemovePlayer(DPID id);
	BOOL	RemoveActivePlayer(DPID id);
	void	SetRemote(UINT wPlayer);
	void	ClearRemote(UINT wPlayer);
	UINT	ColorFromIndex(UINT wPlayer);
	UINT	IndexFromColor(ARMY_COLOR color);
	UINT	AcquireColor(DPID from, ARMY_COLOR color);
	UINT	ReleaseColor(DPID from);
	DPID	GetIDFromIndex(UINT wPlayer);
	DPID	GetIDFromColor(ARMY_COLOR color);
	UINT	GetIndexFromID(DPID id);
	UINT	GetColorFromID(DPID id);
	char	*GetColorStr ( DPID id);
    LONG	GlobalUID(LONG local);
	LONG    LocalUID(LONG global);
	HKEY	GetAppRegKey( void );
	void	SetAppRegDisp( DWORD dwAppRegDisp );
	DWORD	GetAppRegDisp( void );
	BOOL	EverybodyInMapSelection(void) ;
	BOOL	EverybodyHasMap(void);
	BOOL	RegSet( LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize );
	BOOL	RegSetA( LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize );
	BOOL	RegGet( LPCTSTR lptszName, LPBYTE lpData, LPDWORD lpdwDataSize );
	void	ResetBWStats(void);
	void	ReportBWStats (void);
};

BOOL	IsPlayingUID(UID uid);


//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================
extern CComm	gComm, *gpComm;					// global communication object & pointer


//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================


#endif		// __COMM_H__
//=========================================================================
//								EOF
//=========================================================================




