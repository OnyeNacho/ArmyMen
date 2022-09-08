/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: comm.cpp $
//
//	DESCRIPTION:	Communication source.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		Monday, November 4th, 1996
//
//	REVISION:		$Header: /ArmyMen/src/comm.cpp 134   4/17/98 11:07a Dmaynard $
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
//  $Log: /ArmyMen/src/comm.cpp $
//  
//  134   4/17/98 11:07a Dmaynard
//  Put Interlock on BigTimeCommError to prevent the receive thread from
//  causing multiple show error messages.
//  
//  133   4/16/98 5:24p Dmaynard
//  Changed To Enable Tiimeouts in Debug Version
//  
//  132   4/09/98 11:51a Dmaynard
//  Only unpause a remote if he sending new MSG_FLOW messages
//  
//  131   4/05/98 6:49p Dmaynard
//  
//  130   4/05/98 5:43p Dmaynard
//  Close Session when there are 4 players
//  
//  129   4/04/98 8:39p Dmaynard
//  Changed the way Screen functions decide if a player is in the game.
//  Fixes bugs for players exiting and rejoining during map select.
//  
//  127   4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  126   4/02/98 12:13p Dmaynard
//  Changed Max Msg size to 1024.  
//  
//  125   4/01/98 12:18p Bwilcox
//  added defines for the return codes from isremote
//  
//  124   4/01/98 11:59a Nrobinso
//  close reg key
//  
//  123   3/31/98 12:33p Dmaynard
//  UnPause All Comm Based Pauses when Releasing Comm Connection.
//  
//  122   3/29/98 10:17p Dmaynard
//  One more place ReleaseComm where we set m_PlayerID's back to 0.
//  
//  121   3/29/98 7:06p Dmaynard
//  Better reporting of Bandwidth Measurements.  Highwater mark for send
//  and receive bandwidth, and reporting Bandwidth at the end of each game.
//  
//  120   3/29/98 5:40p Dmaynard
//  Set Initial values of m_PlayerID'd back to zero at initialization.
//  
//  119   3/28/98 8:49a Nrobinso
//  
//  118   3/28/98 7:14a Bwilcox
//  multiplayer-mode easter egg. Enjoy. Best Regards, The AI Guru
//  
//  117   3/27/98 6:00p Bwilcox
//  
//  116   3/27/98 5:55p Bwilcox
//  
//  115   3/27/98 5:21p Dmaynard
//  Removing knowledge of who is the host
//  
//  114   3/26/98 2:25p Dmaynard
//  Bug in IsLobbyStart fixed
//  
//  113   3/25/98 6:21p Dmaynard
//  General Lobby Clean-Up.  Removed unused code. Changed to save the lobby
//  Connection settings in gpComm->m_pConnection.   Release Lobby Interface
//  appropriately.
//  
//  112   3/25/98 3:28p Dmaynard
//  Added Debug Switch to Enable TimeOut  code even though we are in a
//  debug build.
//  
//  111   3/24/98 3:35p Dmaynard
//  Added Trace Diagnostics to the case where connecting by lobby fails to
//  get the connection settings.
//  
//  110   3/23/98 7:38p Dmaynard
//  Fixing bug where sometime DPLAY neglects to tell us a player has left.
//  If Send gets an error we Assume the player is gone and destroy our
//  local structures for the player.
//  
//  109   3/23/98 6:25p Dmaynard
//  Changed Remove ActivePlayer to return a BOOL result.
//  
//  108   3/20/98 3:36p Dmaynard
//  Better State Changes for Lobby Start-up
//  
//  107   3/19/98 2:35p Dmaynard
//  Added TIMEOUT for players in Release Builds ONLY.  If we don't hear
//  from a player for 30 seconds we remove the player.
//  
//  106   3/18/98 12:50a Nrobinso
//  pull registry access into comm
//  
//  105   3/17/98 4:42p Dmaynard
//  Added PAUSE_MAPLOAD instead of piggy-backing on the normal PAUSE_LOCAL
//  flags.
//  
//  104   3/16/98 1:01p Nrobinso
//  trun off buffer size trace
//  
//  103   3/13/98 4:49p Dmaynard
//  Changed  Comm::IsRemote to return 1 if remote, 0 if not playing, and -1
//  if was playing but has left.  Needed so scripts can send messages to
//  others players that this player has left the game.
//  
//  102   3/12/98 6:00p Dmaynard
//  Asynchronous update of available ArmyMen Sessions in the Select Battle
//  screen of the JoinSession Dialog.
//  
//  101   3/10/98 5:58p Dmaynard
//  Removed last dependancies upon playx.lib    you can now remove
//  dplayx.lib from your link settings.
//  
//  100   3/09/98 11:43a Dmaynard
//  Changed DPlay to load via COM interface  CoCreateInstance.
//  
//  99    3/05/98 11:24a Dmaynard
//  TRACE for default buffer size.
//  
//  98    3/05/98 11:20a Dmaynard
//  Optimized Message size for UDP  (1016 - header sizes.
//  
//  97    3/05/98 10:33a Dmaynard
//  Turned of GUARANTEED SEND as defalut.  Symmetric Flow Protocol is now
//  the default.
//  
//  96    3/04/98 6:57p Dmaynard
//  Clean up of maintaining m_ArmyRemoteFlags  when a playr lesaves the
//  game
//  
//  95    3/04/98 1:58p Dmaynard
//  Lobby Start States and player names
//  
//  94    3/04/98 9:30a Dmaynard
//  Fixed bug in getting name from lobby
//  
//  93    2/26/98 2:41p Dmaynard
//  Added some Comm debug traces and put others under gpComm->debugComm
//  runtime switch.
//  
//  92    2/26/98 10:57a Dmaynard
//  Test giving people color choice priority in the order they joined.
//  
//  91    2/25/98 12:29p Dmaynard
//  Bug Fixes and Traces in Deleting a FlowQ Data Structure
//  
//  90    2/25/98 11:05a Dmaynard
//  Error Handling for people coming and goind
//  
//  89    2/23/98 2:59p Dmaynard
//  Bug Fix for case when one player left the game during the previous
//  round and we are now back in the map selection screen getting ready for
//  a new game.  We have to remove the remnants of the departed player.
//  
//  88    2/23/98 2:31p Dmaynard
//  Bug Fix  Didn't Re-Initialize everything in Comm:Release.  Specifically
//  it remebered the previous m_HostID.
//  
//  87    2/20/98 6:27p Dmaynard
//  reset m_NumDPPlayers when Releasing Comm
//  
//  86    2/19/98 3:46p Dmaynard
//  Initilizing m_PlayerId[0] at CreatePlayer Time
//  
//  85    2/19/98 2:31p Dmaynard
//  Good Map Bad Map Messages
//  
//  84    2/19/98 1:58p Dmaynard
//  Added flags for whether each player has the correct map.
//  
//  83    2/17/98 6:23p Dmaynard
//  Added Msg Summary output TRACE's after each game is finished.
//  94% of messages are Unit Update Messages.
//  
//  82    2/17/98 10:58a Dmaynard
//  Setting m_bActive to False on Release
//  
//  81    2/16/98 3:26p Dmaynard
//  Fixes for playing multiple multi-player games.  Have to resync and wait
//  until everybody is back in the map selection screen until we can start
//  another game.  Also changed it so that host remembers the last map
//  selected and come up with that as the default when you re-enter the map
//  selection screen from the continue button on the Mission Won/Loss
//  screen.
//  
//  80    2/16/98 12:11a Dmaynard
//  Bug Fixes for playing second multi-player game in a session
//  
//  79    2/10/98 2:58p Dmaynard
//  Split Pause flag PAUSE_REMOTEGONE into separate Pause flags for each
//  remote machine.
//  
//  78    2/09/98 6:13p Dmaynard
//  First Cut at handling a player leaving the game
//  
//  77    1/29/98 12:25p Dmaynard
//  lobby startup
//  
//  76    1/29/98 11:41a Dmaynard
//  Enumerate Players bug fix to get the right names, also lobby startup
//  
//  75    1/28/98 5:38p Dmaynard
//  Changed how and When CreateFlowQPLayer is called so that we can start
//  sending in the map selections screens (to eventualy measure and display
//  latency and packetloss)
//  
//  74    1/27/98 6:49p Dmaynard
//  Adding 3DOLobby Support
//  
//  73    1/27/98 1:43p Bwilcox
//  added IsPlayingUID
//  
//  72    1/23/98 6:04p Dmaynard
//  Moved ARMYMEN GUID from Mainframe to Comm.  Still exits a copy in
//  guid.c   I don't understand GUIDs
//  
//  71    1/22/98 5:25p Dmaynard
//  Fixed Memory leak bug from m_PlayerName
//  
//  70    1/21/98 8:44a Dmaynard
//  Error Handling and flow control for large latency cases.
//  
//  69    1/20/98 5:26p Dmaynard
//  Reseting some comm data at Disconnect Time
//  
//  68    1/19/98 4:06p Dmaynard
//  Fixed bug in Remove Players.  All four colors must ALWAYS be assigned
//  among all four slots with no duplicates.
//  
//  67    1/19/98 3:41p Dmaynard
//  Handling PLayers leaving during Game and Map selection.
//  
//  66    1/16/98 1:54p Dmaynard
//  Change default to use Guaranteed Send in TCP/IP case.
//  
//  65    1/15/98 11:21p Dmaynard
//  Comm debug display stuff
//  
//  64    1/13/98 6:49p Dmaynard
//  Changed 3 defined constants to COmm member variables for tuning.
//  MAXSENDINTERVAl MINSENDINTERVAL AND ENOUGH_MSG_SIZE
//  
//  63    1/13/98 12:35p Dmaynard
//  put many traces into conditionals based on debugComm a new public data
//  member of Comm
//  
//  62    1/07/98 5:09p Dmaynard
//  Changed Get IndexFromColor to return -1 if passed Army_NO_Color
//  
//  61    1/07/98 5:07p Dmaynard
//  Integration of Symmetric Flow Protocol into Armymen
//  
//  60    1/06/98 10:03a Aburgess
//  added Disconnect button and reqorked session logic for MultiPlyaer mode
//  
//  59    12/16/97 5:39p Dmaynard
//  Added sequencing of PACKED ArmyMessages and checking sequence numbers
//  to detect (but not yet correct) LOST PACKETS
//  
//  58    12/11/97 5:50p Dmaynard
//  Added RemovePlayer and Handling of DSYS_SETSESSION system Message.
//  
//  57    12/10/97 7:24p Dmaynard
//  Don't allow players to Join after game has started
//  
//  56    12/10/97 9:44a Aburgess
//  changes made to centralize REGKEY access. Also
//  fixes CANCEL or BACK in multiplayer connect
//  
//  55    97/12/09 17:21 Dmaynard
//  Removed a TRACE
//  
//  54    12/09/97 12:12p Phu
//  
//  53    12/05/97 11:04a Dmaynard
//  
//  52    12/05/97 10:52a Dmaynard
//  Color  (m_Index)  now always being maintained for 4 players
//  
//  51    12/05/97 9:56a Dmaynard
//  IndexFromColor MUST return a valid index [0-3]  otherwise all hell
//  breaks loose.
//  
//  50    12/04/97 9:04p Aburgess
//  added ReleaseColor and use of ARMY_NO_COLOR
//  
//  49    12/03/97 4:41p Dmaynard
//  Undid fix to IndexFrom Color.  COde assumes that all for colors and all
//  four amies exits.
//  
//  48    12/03/97 11:25a Dmaynard
//  Fixed bug in IndexFromColor 
//  
//  47    12/03/97 10:01a Aburgess
//  added GetIndexFromID and GetColorFromID
//  
//  46    12/02/97 5:24p Aburgess
//  changed check of "oneplayer" to "gpGame->GameType ==
//  GAMETYPE_ONEPLAYER"
//  
//  45    12/02/97 3:08p Dmaynard
//  calling InitMessageBuffers in Comm  (class initialization)
//  
//  44    12/02/97 2:52p Dmaynard
//  Moved setting gpComm->m_bActive to within CreatePlayer in comm.cpp
//  
//  43    12/02/97 2:50p Dmaynard
//  Moved setting of gpComm-m_bActive to inside of Createplayer in comm.cpp
//  
//  42    12/02/97 10:17a Aburgess
//  zero out m_PlayerName[]
//  
//  41    12/01/97 6:20p Nrobinso
//  turn off lobby traces
//  
//  40    12/01/97 4:13p Dmaynard
//  Added m_PlayerName[MAX_PLAYERS]  to Comm Data Structures
//  
//  39    12/01/97 1:30p Aburgess
//  new acquire color routine
//  
//  38    11/20/97 11:06a Dmaynard
//  Fixed IsConnected() which was always returning FALSE
//  
//  37    11/19/97 7:27p Dmaynard
//  changed when to print comm dump . Now if we average more than 100,000
//  bytes/sec over last 30 frames.
//  
//  36    11/18/97 2:18p Dmaynard
//  GlobalUID and LocalUID functions added
//  
//  35    11/18/97 11:58a Dmaynard
//  Added functions Global_UID and Local_UID to translate UID's from local
//  to global (color based) representation.
//  
//  34    11/18/97 11:31a Dmaynard
//  Tweaking message sending governor to limit packet rate to 30 hz
//  
//  33    11/17/97 11:58a Dmaynard
//  Added printout of average session bandwidth and average sessions
//  packets/second sent and received.
//  
//  32    11/16/97 6:32p Dmaynard
//  Fixed Resource leaks by Releasing the MutexLocks and event handles used
//  by the comm system.   
//  
//  31    11/16/97 5:29p Dmaynard
//  Added Governor to comm to limit packet rate to a maximum of 30
//  packets/second, and a minimum of one packet/second (heartbeat).
//  
//  30    10/27/97 5:30p Dmaynard
//  Added GetIDFromIndex  and GetIDFromColor  which return the Direct Play
//  ID for the player.
//  
//  29    10/27/97 2:34p Dmaynard
//  Allow UniqueID's of nuetral objects on the wire.  Some objects belong
//  to no army such as trees.  These Unique ID's will not get ranslated.
//  
//  28    10/27/97 10:32a Dmaynard
//  Put Back the function GetNumPlayers
//  
//  27    10/24/97 6:55p Dmaynard
//  Fixed number of players bug
//  
//  26    10/24/97 5:53p Dmaynard
//  Fixed GetArmyIndexFromID
//  
//  25    10/24/97 5:08p Dmaynard
//  Fixed wait for heartbeat to work for n players
//  
//  24    10/24/97 4:24p Bwilcox
//  fixed commbug
//  
//  23    10/24/97 1:52p Dmaynard
//  Two Player fix second player is TAN
//  
//  22    10/24/97 1:10p Dmaynard
//  
//  21    10/24/97 11:18a Dmaynard
//  Added MultiPlayer menu option and start multiplayer game options and
//  changed how the translation of UniqueID's is handled.  UniqueID are now
//  translated into universal (color coded) format before  sending and each
//  macine translates from color to local index in receive armymessage.
//  
//  20    10/23/97 9:18a Bwilcox
//  changimg to process 4 armies always, since some missions need it.
//  
//  19    10/22/97 2:07p Bwilcox
//  blue player added
//  
//  18    10/21/97 10:54a Dmaynard
//  Added ARMY_GREEN thru ARMY_GRAY constants.  New Functions in CComm
//  ColorFromIndex and IndexFromColor to map between army number and army
//  color.
//  
//  17    10/13/97 4:50p Nrobinso
//  no dependence on army.h
//  
//  16    10/13/97 4:44p Nrobinso
//  add ARMY_INDEPENDENT in and out of GetArmyIndex
//  
//  14    9/11/97 2:47p Dmaynard
//  Changed DPlay Session Description to allow up tp 4 Players.
//  
//  13    8/26/97 12:33p Dmaynard
//  Added call to GetSessionDesc inside OpenSession so the joining player
//  has access to the Session Description.
//  
//  12    8/26/97 11:38a Dmaynard
//  Passing Flag for Host Green/Tan in SessionDesc.dwUser1
//  
//  11    8/17/97 6:07p Nrobinso
//  cleanup pause code
//  
//  10    8/16/97 10:29a Bwilcox
//  revised code using allowcommand or bothai to support ai for either or
//  both player1 and player2, 
//  
//  9     8/14/97 7:32p Bwilcox
//  fixing getnumlocalplayers to check onePlayer and not aicommander
//  
//  8     8/07/97 2:58p Dmaynard
//  Do Not Set PAUSE_REMOTEGONE if we are already in a Paused State (LOCAL
//  or REMOTE Pause).
//  
//  7     8/05/97 6:03p Dmaynard
//  Get the Maximum Packet size for this session from DPlay and never send
//  a package larger than this. 
//  
//  6     8/05/97 3:32p Dmaynard
//  General Clean Up. Added Stats for Total Packets and Max Packet Sizes
//  observed.  Called Release from Within Disconnect.
//  
//  5     7/28/97 4:00p Dmaynard
//  
//  4     7/25/97 4:21p Dmaynard
//  Removed communications Pause if we are in syart_game state
//  
//  3     7/25/97 3:58p Dmaynard
//  ReadyMsgs and StartGameMsgs
//  
//  2     7/15/97 12:25p Aburgess
//  new Connected method.
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  24    6/13/97 6:47p Dmaynard
//  Added Initial Lobby Support. Also updated from DirectPlay2 to
//  DirectPlay3 and from DirectPlayLobby to DirectPlayLobby2 Interfaces.
//  
//  
//  23    6/13/97 5:16p Nrobinso
//  add extern for allowcommander
//  
//  22    6/13/97 5:14p Nrobinso
//  add GetNumLocalPlayers()
//  
//  21    97-05-14 12:53 Dmaynard
//  Added checks to avoid processing if Comm is not active.
//  
//  20    5/13/97 8:15p Dmaynard
//  Limit game to two players for now
//  
//  19    5/09/97 3:57p Dmaynard
//  Added heartBeat to send at least one PACKED MESSAGE per frame
//  to let the other side know we are alive.
//  
//  18    5/09/97 2:07p Dmaynard
//  Added B_PAUSEDREMOTEGONE to prevent us from sending msgs when we are
//  not receiving any messages from opposing player.
//  
//  17    5/09/97 12:16a Dmaynard
//  Changed Create Session Flags to Not KeepAlive  (for debugging)
//  
//  16    5/07/97 2:29p Dmaynard
//  Added Checksum and Sequence numbers to Packed ArmyMsgs
//  
//  15    5/06/97 4:16p Dmaynard
//  Added Stats functions GetSendBW etc.
//  
//  13    5/02/97 6:17p Dmaynard
//  Comm Clean-up to get rid of commc.cpp and lobby.cpp
//  
//  12    97-05-01 16:58 Dmaynard
//  
//  11    5/01/97 11:16a Dmaynard
//  Fixed Send bug when DPlay not active
//  
//  10    5/01/97 10:42a Dmaynard
//  Added GetArmyIndexFromDPID
//  
//  9     4/30/97 7:53p Nrobinso
//  add a remote array so we can tell which players are remote
//  
//  8     4/29/97 1:39p Nrobinso
//  if compile with TAN defined, start with army index order 1,0,2,3
//  
//  7     4/28/97 6:23p Dmaynard
//  Comm Cleanup
//  
//  6     4/27/97 2:21p Dmaynard
//  Added interface to new communications code
//  
//  5     4/08/97 8:58a Aburgess
//  comm needs to set the number of players in the game,  even if there's a
//  computer opponent
//  
//  4     97-01-10 16:34 Ereich
//  A good check-in point for code clean-up...
//  
//  3     97-01-10 10:00 Ereich
//  Day 2 house cleaning done...
//  
//  2     97-01-09 9:45 Ereich
//  Clean-up day 2 is now complete on day 3...  I love meetings!
//  
//  1     97-01-08 9:53 Ereich
//  This is the first pass at changing comm.c to comm.cpp.
//
//	ANCIENT HISTORY (from comm.c)
/*  */
/* 7     97-01-07 9:02 Ereich */
/* Checking in for the sake of merging with the latest code before I start */
/* making major reorganizational changes. */
/*  */
/* 6     96-12-05 9:08 Ereich */
/* Added a stubbed out GetArmyIndex() so that Andrew won't be held up. */
/*  */
/* 5     96-11-19 14:06 Ereich */
/* Merged lobby.h with comm.h and lobby.c with comm.c. */
/* Removed lobby.h and lobby.c from the project. */
/*  */
/* 4     96-11-19 13:27 Ereich */
/* I have removed DUEL residue from these files. */
/*  */
/* 3     96-11-13 12:13 Ereich */
/* Fix build problems. */
/*  */
/* 2     96-11-12 5:15 Ereich */
/* Putting the first compiling version up to the net. */
//  
//  1     96-11-04 10:02 Ereich
//  Initial version of communication support.
//
//  $Nokeywords:$
//=========================================================================


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "Army.h"
#include "AiAccess.h"
#include "comm.h"
#include "3DONetwork.h"
#include "gameflow.h"
#include "mainfrm.h"
#include "gameproc.h"
#include "armyMsg.h"

// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
extern BOOL AbortInProgress;

CComm	gComm, *gpComm=&gComm;								// global communication object & pointer
/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Class construction/destruction
extern		HANDLE								PlayerEvent;  // in commc Event to wait on to trigger interrupt of receive thread
extern void InitMessageBuffers(void);
extern TDGLIST freelist;

DEFINE_GUID(ARMYMEN_GUID,
0xf5117e8c, 0x36fb, 0x11d0, 0xa9, 0x45, 0x0, 0x80, 0x5f, 0x5a, 0xea, 0x59);

CComm::CComm()
{
	// TODO: add constructor code...
	UINT	i;
	DWORD now;
	InitMsgSystem();
    InitMessageBuffers();
	now = GetTickCount();
	m_pDPlay = NULL;
	m_pLobby = NULL;
	for( i=0; i<MAX_PLAYERS; i++ ) {
		m_ArmyRemote[i] = FALSE;
		m_ArmyReady[i] = FALSE;
		m_ArmyIndex[i] = i;
		m_CommErrorCnt[i] = NULL;
		m_PlayerId[i] = 0; 
		m_Outstanding[i] = 0;
		m_Seq[i] = 0;
		m_TimeReceived[i] = now;
		m_PlayerName[i] = (char *) malloc(MAX_PLAYERNAME);
		ZeroMemory(m_PlayerName[i],MAX_PLAYERNAME);
		strcpy(m_PlayerName[i],"      ");
	}
	m_TimeSent = now;
	m_SendIndex = m_ReceiveIndex = 0;
	m_MaxPacketSize = MAX_MSG_SIZE;	  // Should be retrieved from Connection parameters
	ResetBWStats();

//	m_hRegKey   = COMM_NULL_KEY;
//	m_dwRegDisp = COMM_NULL_DISP;

	// open or create the ArmyMen registry
	RegCreateKeyEx( HKEY_LOCAL_MACHINE, ARMYMEN_KEY, 0, NULL,                   
						REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_hRegKey, &m_dwRegDisp);

	m_pGuid	= (LPGUID) (&ARMYMEN_GUID);
	m_NumDPPlayers = 1;
	m_HostID = 0;
	m_bHost = FALSE;
	m_bActive = FALSE;
	m_Connected = FALSE;
//	m_SendFlags = DPSEND_GUARANTEED;	 // only used if TCP/IP
	m_SendFlags = 0;	
	m_bTestedLobby	= FALSE;
	m_bStartedByLobby		= FALSE;
#ifndef DEBUG_COMM
	debugComm=0;
#else 
	debugComm = 1;
#endif
	debugDisplayComm  = 1;
#ifdef _DEBUG
	m_bTimeOutsEnabled	= TRUE;
#else 
	m_bTimeOutsEnabled	= TRUE;
#endif
	MINSENDINTERVAL = 100;				// Don't Send Messages any closer together than this 
	MAXSENDINTERVAL = 1000;				// Don't Send Messages any farther apart than this
	// Send whenever the biffer gets this full
	//  Optimized for UDP
	ENOUGH_MSG_SIZE = (1016 - (sizeof(TDGHDR)+sizeof(FLOWHDR)));
	ClearMessageCounts();
}


CComm::~CComm()
{
	// TODO: add destructor code...
	UINT	i;
	for( i=0; i<MAX_PLAYERS; i++ ) {
		free(m_PlayerName[i]);
	}
	
	Release();
	KillMsgSystem();
	m_bActive = FALSE;
	m_Connected = FALSE;
	RegCloseKey(m_hRegKey);
}


/////////////////////////////////////////////////////////////////////////////
// Public Methods

/*
 * Close
 *
 * Wrapper for DirectPlay Close API
 */
HRESULT CComm::Close(void)
{
    HRESULT hr=E_FAIL;

    if (gpComm->m_pDPlay) 
        hr = IDirectPlay3_Close(gpComm->m_pDPlay);
    
    return hr;
}

/*
 * DPlayCreate
 *
 * Wrapper for DirectPlay Create API. Retrieves a DirectPlay2/DirectPlay2A interface
 * based on the UNICODE flag
 * 
 */
HRESULT CComm::DPlayCreate(LPVOID lpCon)
{
	HRESULT			hr		= E_FAIL;
	LPDIRECTPLAY3	lpDP3	= NULL;
	if(m_pDPlay)  Release();

	hr = CoCreateInstance(	CLSID_DirectPlay, NULL, CLSCTX_INPROC_SERVER,
							IID_IDirectPlay3A, (LPVOID *) &m_pDPlay );
	
	if ( DP_OK == hr )
	{
		if (lpCon)
		{
			hr = IDirectPlay3_InitializeConnection( m_pDPlay, lpCon, 0);
		if ( DP_OK == hr )  GetCaps();
		}
 

		// query for a DirectPlay2(A) interface
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CComm::CreateDirectPlayLobbyInterface( LPDIRECTPLAYLOBBY2A *lplpDirectPlayLobby2A )
{
	HRESULT				hr;
	LPDIRECTPLAYLOBBY2A		lpDirectPlayLobby2A = NULL;

	// Create an IDirectPlay3 interface
	hr = CoCreateInstance(	CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER, 
							IID_IDirectPlayLobby2A, (LPVOID*)&lpDirectPlayLobby2A);

	// return interface created
	*lplpDirectPlayLobby2A = lpDirectPlayLobby2A;

	return (hr);
}


/*
 * CreatePlayer
 *
 * Wrapper for DirectPlay CreatePlayer API. 
 */

HRESULT CComm::CreatePlayer( LPTSTR lptszPlayerName, HANDLE hEvent, 
                          LPVOID lpData, DWORD dwDataSize)
{
    HRESULT hr=E_FAIL;
    DPNAME name;
    
    ZeroMemory(&name,sizeof(name));
    name.dwSize = sizeof(DPNAME);

#ifdef UNICODE
    name.lpszShortName = lptszPlayerName;
#else
    name.lpszShortNameA = lptszPlayerName;
#endif
	if (hEvent == NULL) hEvent = PlayerEvent;
    if (gpComm->m_pDPlay)
        hr = IDirectPlay3_CreatePlayer(gpComm->m_pDPlay, &m_DPId, &name, hEvent, lpData, dwDataSize, 0);
                                    
	if( hr != DP_OK) TRACE("CreatePlayer Failed  returned %x \n", hr);
	if (hr == DP_OK && m_bHost) m_HostID = TRUE;	// we are hosting
	if (hr == DP_OK && !m_bHost) {	// we are joining
		gpComm->m_NumDPPlayers++;
		TRACE("numDPPlayers is %d \n", gpComm->m_NumDPPlayers);
	}
	gpComm->m_PlayerId[0] = m_DPId;
	gpComm->m_Connected = TRUE;
	gpComm->m_bActive = TRUE;
	CreateFlowQPlayer(gpComm->m_DPId);
	return hr;
}

/*
 * CreateSession
 *
 * Wrapper for DirectPlay CreateSession API.Uses the global application guid (m_pGuid).
 */
HRESULT CComm::CreateSession(LPTSTR lptszSessionName)
{
    HRESULT hr = E_FAIL;
    DPSESSIONDESC2 dpDesc;

    ZeroMemory(&dpDesc, sizeof(dpDesc));
    dpDesc.dwSize = sizeof(dpDesc);
 //  dpDesc.dwFlags = DPSESSION_MIGRATEHOST | DPSESSION_KEEPALIVE;
	 dpDesc.dwFlags = DPSESSION_MIGRATEHOST ;


#ifdef UNICODE
    dpDesc.lpszSessionName = lptszSessionName;
#else
    dpDesc.lpszSessionNameA = lptszSessionName;
#endif
	dpDesc.dwMaxPlayers	 = 4;
    dpDesc.dwUser1 = gpComm->m_ArmyIndex[0];
	// set the application guid
    if (gpComm->m_pGuid)
        dpDesc.guidApplication = *(gpComm->m_pGuid);

    if (gpComm->m_pDPlay)
        hr = IDirectPlay3_Open(gpComm->m_pDPlay, &dpDesc, DPOPEN_CREATE);

    return hr;
}

///========================================================================
//	Function:		IsInSession()
//
//	Description:
//		Determine whether or not this machine is already connected to a lobby
//		or another machine.
//
//	Input:			none
//
//	Ouput:			TRUE		if connected, FALSE otherwise
//
///========================================================================

BOOL CComm::IsInSession( void )
{
	return( (gpComm->m_pDPlay) ? TRUE : FALSE );
}

/*
 * DestroyPlayer
 * 
 * Wrapper for DirectPlay DestroyPlayer API. 
 */
HRESULT CComm::DestroyPlayer()
{
    HRESULT hr=E_FAIL;
    
    if (m_pDPlay)
        hr = IDirectPlay3_DestroyPlayer(m_pDPlay, m_DPId);
	m_DPId = 0;
    gpComm->m_bActive = FALSE;
	return hr;
}

/*
 * EnumPlayers
 *
 * Wrapper for DirectPlay API EnumPlayers
 */
HRESULT CComm::EnumPlayers(LPGUID lpSessionGuid, LPDPENUMPLAYERSCALLBACK2 lpEnumCallback, 
                         LPVOID lpContext, DWORD dwFlags)
{
    HRESULT hr=E_FAIL;

    if (gpComm->m_pDPlay)
        hr = IDirectPlay3_EnumPlayers(gpComm->m_pDPlay, lpSessionGuid, lpEnumCallback, lpContext, dwFlags);

    return hr;
}

/*
 * EnumSessions
 *
 * Wrapper for DirectPlay EnumSessions API.
 */
HRESULT CComm::EnumSessions(DWORD dwTimeout, LPDPENUMSESSIONSCALLBACK2 lpEnumCallback, 
                          LPVOID lpContext, DWORD dwFlags)
{
    HRESULT hr = E_FAIL;
    DPSESSIONDESC2 dpDesc;

    ZeroMemory(&dpDesc, sizeof(dpDesc));
    dpDesc.dwSize = sizeof(dpDesc);
    if (m_pGuid)
        dpDesc.guidApplication = *m_pGuid;

    if (m_pDPlay)
        hr = IDirectPlay3_EnumSessions(m_pDPlay, &dpDesc, dwTimeout, lpEnumCallback, lpContext, dwFlags);


    return hr;
}

/*
 * EnumConnections
 *
 * Wrapper for DirectPlay EnumConnections API.
 */


HRESULT CComm::EnumConnections(LPCGUID lpguidApplication, LPDPENUMCONNECTIONSCALLBACK lpEnumCallback,
	LPVOID lpContext,
	DWORD dwFlags) {
    HRESULT hr = E_FAIL;
    DPLCONNECTION dpConnection;

    ZeroMemory(&dpConnection, sizeof(dpConnection));
    dpConnection.dwSize = sizeof(DPLCONNECTION);
    if (m_pDPlay)
        hr = IDirectPlay3_EnumConnections(m_pDPlay, m_pGuid, lpEnumCallback,  lpContext, dwFlags);


    return hr;
}







/*
 * GetSessionDesc
 *
 * Wrapper for DirectPlay GetSessionDesc API. 
 */
HRESULT CComm::GetSessionDesc(void)
{
    HRESULT hr=E_FAIL;
    DWORD dwSize;

    // free old session desc, if any
    if (m_pSDesc)
    {
        free(m_pSDesc);
        m_pSDesc = NULL;
    }

    if (m_pDPlay)
    {
        // first get the size for the session desc
        if ((hr = IDirectPlay3_GetSessionDesc(m_pDPlay, NULL, &dwSize)) == DPERR_BUFFERTOOSMALL)
        {
            // allocate memory for it
            m_pSDesc = (LPDPSESSIONDESC2) malloc(dwSize);
            if (m_pSDesc)
            {
                // now get the session desc
                hr = IDirectPlay3_GetSessionDesc(m_pDPlay, m_pSDesc, &dwSize);
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }
        }
    }
//	hr = gpComm->GetCaps();
    return hr;
}

/*
 * SetSessionDesc
 *
 * Wrapper for DirectPlay SetSessionDesc API. 
 */
HRESULT CComm::SetSessionDesc(LPDPSESSIONDESC2 lpSessionDesc, DWORD dwFlags)
{
    HRESULT hr=E_FAIL;
 
    if (m_pDPlay)
    {
        // first get the size for the session desc
        hr = IDirectPlay3_SetSessionDesc(m_pDPlay, lpSessionDesc, dwFlags);
	}
    return hr;
}

/*
 * GetCaps
 *
 * Wrapper for DirectPlay GetSessionDesc API. 
 */
HRESULT CComm::GetCaps(void)
{
    HRESULT hr=E_FAIL;

    if (m_pDPlay)
    {
        // first get the size for the session desc
        gpComm->m_Caps.dwSize = sizeof(DPCAPS);
		hr = IDirectPlay3_GetCaps(m_pDPlay, &(gpComm->m_Caps), 0);
		if(debugComm) {
			TRACE("DPLAY CAPS: \n");
			TRACE("   MaxPacketSize %8d \n",gpComm->m_Caps.dwMaxBufferSize );
			TRACE("   HeaderSize    %8d \n",gpComm->m_Caps.dwHeaderLength );
			TRACE("   Latency       %8d \n",gpComm->m_Caps.dwLatency  );
			TRACE("   TimeOut       %8d \n",gpComm->m_Caps.dwTimeout  );
			if ( gpComm->m_Caps.dwFlags & DPCAPS_GUARANTEEDSUPPORTED) 
				TRACE("   Guaranteed Messaging Supported\n");
			else
				TRACE("   Guaranteed Messaging Not Supported\n");
		}
		if (gpComm->m_Caps.dwMaxBufferSize < MAX_MSG_SIZE) gpComm->m_MaxPacketSize = gpComm->m_Caps.dwMaxBufferSize;
		if ((gpComm->m_Caps.dwMaxBufferSize - (sizeof(TDGHDR)+sizeof(FLOWHDR))) < (gpComm->ENOUGH_MSG_SIZE)) 
			gpComm->ENOUGH_MSG_SIZE = gpComm->m_Caps.dwMaxBufferSize - (sizeof(TDGHDR)+sizeof(FLOWHDR));
 		TRACE(" Max Buffer Size = %d Default buffer size to %d bytes\n", gpComm->m_MaxPacketSize, gpComm->ENOUGH_MSG_SIZE);
		}
    return hr;
}


/*
 * OpenSession
 *
 * Wrapper for DirectPlay OpenSession API. 
 */
HRESULT CComm::OpenSession(LPGUID lpSessionGuid)
{
    HRESULT hr = E_FAIL;
    DPSESSIONDESC2 dpDesc;

    ZeroMemory(&dpDesc, sizeof(dpDesc));
    dpDesc.dwSize = sizeof(dpDesc);

    // set the session guid
    if (lpSessionGuid)
        dpDesc.guidInstance = *lpSessionGuid;
    // set the application guid
    if (m_pGuid)
        dpDesc.guidApplication = *m_pGuid;

    // open it
    if (m_pDPlay)
        hr = IDirectPlay3_Open(m_pDPlay, &dpDesc, DPOPEN_JOIN);

   //  Open does NOT actually return the session Description
	if (hr != DP_OK) {
		TRACE(" Open Session Failed returned %x \n", hr  );
		return hr;
	}
	hr = GetSessionDesc();
	if (gpComm->m_pSDesc->dwUser1 == 0) {	 // we are joining as Tan
		gpComm->m_ArmyIndex[0] = gpComm->m_pSDesc->dwCurrentPlayers;
//		gpComm->m_ArmyIndex[1] = ARMY_GREEN;
	}
	else {	  // we are joining as Green
//		gpComm->m_ArmyIndex[0] = ARMY_GREEN;
//		gpComm->m_ArmyIndex[1] = ARMY_TAN;
	}
	
	return hr;
}


/*
 * Receive
 *
 * Wrapper for DirectPlay Receive API
 */
HRESULT CComm::Receive(LPDPID lpidFrom, LPDPID lpidTo, DWORD dwFlags, LPVOID lpData, LPDWORD lpdwDataSize)
{
    HRESULT hr = E_FAIL;
	LPGENERICMSG lpMsg;
	LPGENERICMSG lpGeneric;
	static int framemod = 0;
    int i,nfree,index;
	DWORD pausemask;
	DWORD now;
	if (m_pDPlay) {
        hr = IDirectPlay3_Receive(m_pDPlay, lpidFrom, lpidTo, dwFlags, lpData, lpdwDataSize);
    
		if (hr == DP_OK) {
			m_ReceiveSize[m_ReceiveIndex] = *lpdwDataSize;
			lpMsg = (LPGENERICMSG)lpData;
			m_TotalBytesReceived += *lpdwDataSize;
			m_TotalPacketsReceived++;
			if (*lpdwDataSize > m_MaxReceiveSize) m_MaxReceiveSize = *lpdwDataSize;
		//	TRACE("Receive Size %d Type  %d  Size  %d\n", *lpdwDataSize,lpMsg->tdg.tdg_Type,lpMsg->tdg.tdg_Size);
			now = GetTickCount();
			m_ReceiveTime[m_ReceiveIndex] = now;
			if (++m_ReceiveIndex >= COMM_SAMPLE_SIZE) m_ReceiveIndex = 0;
			// HACK ALERT  This should all be on a per/player basis
			index = GetArmyIndexFromID(*lpidFrom);
			lpGeneric  = (LPGENERICMSG) lpData;
			if (lpGeneric->tdg.tdg_Type == MSG_FLOW) m_Outstanding[index] = 0;
			m_TimeReceived[index] = now;
			for (i=1,pausemask = PAUSE_REMOTEGONE1; i< (int)gpComm->m_NumDPPlayers; i++)  {
				if( gpComm->m_PlayerId[i] == 0xFFFFFFFF) continue;
				if( m_Outstanding[i] < 15 ) 
					gpGame->UnPauseGame(pausemask);
				pausemask = pausemask<<1;
			}
			nfree = ListSize(&freelist);
			if ( (nfree > (MAX_MSGS*3/4))  &&  ((gpGame->IsPaused() & PAUSE_FLOW))) {
				TRACE("FLOW UNPAUSE nfree = %d\n",nfree);
				gpGame->UnPauseGame(PAUSE_FLOW);
			}
		}
	}
	return hr;
}

/*
 * Release
 *
 * Wrapper for DirectPlay Release API.
 */
HRESULT CComm::Release(void)
{
    HRESULT hr = E_FAIL;
	int i;
	if (m_pDPlay)
    {
        // free session desc, if any
        if (m_pSDesc) 
        {
            free(m_pSDesc);
            m_pSDesc = NULL;
        }

        // free connection settings structure, if any (lobby stuff)
        if (m_pConnection)
        {
            free(m_pConnection);
            m_pConnection = NULL;
        }
        // release dplay
        hr = IDirectPlay3_Release(m_pDPlay);
        m_pDPlay = NULL;
        m_bActive = FALSE;
		TRACE("Releasing Comm Connection \n");
		m_NumDPPlayers = 1;
		m_HostID = 0;
		for( i=0; i<MAX_PLAYERS; i++ ) {
			m_ArmyRemote[i] = FALSE;
			m_ArmyReady[i] = FALSE;
			m_ArmyIndex[i] = i;
			m_CommErrorCnt[i] = NULL;
			if ((i > 0 ) && (m_PlayerId[i])) DestroyFlow(m_PlayerId[i] );
			m_PlayerId[i] = 0;  // pretend he left during setup
			m_Outstanding[i] = 0;
			m_Seq[i] = 0;
			m_TimeReceived[i] = GetTickCount();
			strcpy(m_PlayerName[i],"      ");
		}
		DestroyFlow(m_DPId );
		m_DPId = 0;
		}
	if (m_pLobby) {
		hr = m_pLobby->Release();
		m_pLobby = NULL;

	}
  	// Remove any lingering Comm based Pause Flags
	gpGame->UnPauseGame(PAUSE_REMOTEGONE1 | PAUSE_REMOTEGONE2 | PAUSE_REMOTEGONE3 |
						PAUSE_REMOTE1     | PAUSE_REMOTE2     | PAUSE_REMOTE3     |
						PAUSE_MAPLOAD1    | PAUSE_MAPLOAD2    | PAUSE_MAPLOAD3);

	AbortInProgress = FALSE;

    return hr;
}

/*
 * Send
 * 
 * Wrapper for DirectPlay Send API.
 */
HRESULT CComm::Send(DPID idTo, DWORD dwFlags, LPVOID lpData, DWORD dwDataSize)    
{
    HRESULT hr = E_FAIL;
    int i;
	DWORD pausemask;
	if(m_pDPlay) {
		m_SendTime[m_SendIndex] = GetTickCount();
		m_SendSize[m_SendIndex] = dwDataSize;
		m_TotalBytesSent += dwDataSize;
		m_TotalPacketsSent++;
		if (dwDataSize > m_MaxSendSize) m_MaxSendSize = dwDataSize;
		if (++m_SendIndex >= COMM_SAMPLE_SIZE) m_SendIndex = 0;
		hr = IDirectPlay3_Send(m_pDPlay, m_DPId, idTo, dwFlags, lpData, dwDataSize );
		if (FAILED(hr)) {
			if ( hr == DPERR_INVALIDPARAMS || hr == DPERR_INVALIDPLAYER ) {

// DONT TRUST DPLAY TO GET THIS RIGHT. During transfer of host, you might get invalid player on a valid player...

				// ShowError(IDS_DPERR_INVALIDPARAMS);
				TRACE("DPLAY ERROR: INVALID PARAMETERS OR INVALID_PLAYER ABOUT TO DESTROP Player %x\n",idTo);
				// This is necessary because sometime DPLAY fails to send us a 
				// DPSYS_DESTROPYPLAYERORGROUP message
				//PostMessage(ghWndMain, UM_TDG_DESTROYPLAYER, (WPARAM)idTo, (LPARAM) NULL);
			}
		}
		for (i=1, pausemask=PAUSE_REMOTEGONE1; i< (int)gpComm->m_NumDPPlayers; i++)  {
			if (m_PlayerId[i] == 0xFFFFFFFF) continue;
			m_Outstanding[i]++;
			if( m_Outstanding[i] > 30 && (!(gpGame->IsPaused() & pausemask ))) 
				gpGame->PauseGame(pausemask);
			pausemask = pausemask<<1;
		}
	}
    return hr;
}

/*
 * GetPlayerName
 *
 * Entry:
 *	idPlayer = player's id.
 *	
 * Exit:
 *	Returns HRESULT value from IDirectPlay3::GetPlayerName().
 */
HRESULT CComm::GetPlayerName(int player, LPDPNAME lpName, LPDWORD dwSize)
{
    HRESULT hr=E_FAIL;

    if (m_pDPlay)
        hr = IDirectPlay3_GetPlayerName(m_pDPlay, m_PlayerId[player], (LPVOID)lpName, dwSize);
    
    return hr;
}

BOOL CComm::IsDPlay(void)
{
    return (m_pDPlay ? TRUE:FALSE);
}

/*
 * LobbyRelease
 *
 * Wrapper for DirectPlayLobby Release API
 */
HRESULT CComm::LobbyRelease(void)
{
    HRESULT hr=E_FAIL;

    // free our connection settings
    if (m_pConnection)
    {
        free(m_pConnection);
        m_pConnection = NULL;
    }

    // release the lobby object
    if (m_pLobby)
    {
        hr = IDirectPlayLobby_Release(m_pLobby);
        m_pLobby = NULL;
    }
    return hr;
}



// IsLobbyStart   Returns TRUE if we were started by a lobby
// Also has side effect if successful of creating the DPlay Object m_DPlay
// and the Lobby object m_Lobby


BOOL CComm::IsLobbyStart( void )
{
        HRESULT                         hr=E_FAIL;
		DPCAPS Caps;
        DWORD   dwDataSize = LOBBYCONNECTIONBUFFERSIZE;
	    m_bTestedLobby	= TRUE;
        //
//  Create an instance of the 3DO Lobby interface
		       hr = CreateDirectPlayLobbyInterface(&m_pLobby);

//        TRACE(" Lobby DirectPlayLobbyCreate returned %x\n", hr);

		if FAILED( hr )
		{
                m_pLobby == NULL;
				return FALSE;
		}
        // DebugBreak();
//
//  Ask the interface for the connection settings that define this session.
//
//  szDPBuffer will contain a DPLCONNECTION struct, a DPSESSIONDESC2
//  struct, a dpSessionInfo DPNAME struct and a DirectPlay Address that
//  identifies the session server.
//
//  All of these structs can be accessed through the DPLCONNECTION struct.
//
		m_pConnection = (LPDPLCONNECTION)malloc(dwDataSize);
		if (!m_pConnection) {
			TRACE("Out of Memory trying to allocate LobbyConnectionBuffer\n");
			return FALSE;
		}

		hr = gpComm->m_pLobby->GetConnectionSettings( 0, m_pConnection, &dwDataSize );

        if FAILED( hr )	{
 				if( hr == DPERR_NOTLOBBIED) 
					if (m_pLobby) {
						hr = m_pLobby->Release();
						m_pLobby = NULL;
						if(m_pConnection ) {free(m_pConnection); m_pConnection = NULL;}
						return FALSE;
				}
				TRACE(" Lobby GetConnectionSettings failed with  %x\n", hr);
 				if( hr == DPERR_BUFFERTOOSMALL) TRACE ("DPERR_BUFFERTOOSMALL \n");
				if( hr == DPERR_INVALIDINTERFACE) TRACE ("DPERR_INVALIDINTERFACE \n");
				if( hr == DPERR_INVALIDOBJECT) TRACE ("DPERR_INVALIDOBJECT \n");
				if( hr == DPERR_INVALIDPARAMS) TRACE ("DPERR_INVALIDPARAMS \n");
				if( hr == DPERR_OUTOFMEMORY) TRACE ("DPERR_OUTOFMEMORY \n");
              return FALSE; 
		}
//
//  When control gets here, it means we've been launched by a lobby.
//
//        DPLCONNECTION           *ptheConnection = (LPDPLCONNECTION) szDPBuffer;
//
//  Prepare session information before using connect method
//
    m_pConnection->lpSessionDesc->dwUser1 = 1;                             //      From DPlay::createSession
    m_pConnection->lpSessionDesc->dwUser2 = 2;
    m_pConnection->lpSessionDesc->dwUser3 = 3;
    m_pConnection->lpSessionDesc->dwUser4 = 4;

        m_pConnection->lpSessionDesc->dwMaxPlayers = 4;

        hr = gpComm->m_pLobby->SetConnectionSettings( 0, 0, m_pConnection );

        TRACE(" Lobby SetConnectionSettings returned %x\n", hr);
        if FAILED( hr )
                return( FALSE );
//
//  Connect to the session.
//
       LPDIRECTPLAY2   dpPtr;

         hr = gpComm->m_pLobby->Connect( 0, &dpPtr, NULL );
//       hr = gpComm->m_pLobby->Connect( 0, &m_pDPlay, NULL );

        TRACE(" Lobby Connect returned %x\n", hr);
		if FAILED( hr )
                return(FALSE);
//  Get a DirectPlpay3 Interface
   
       if (dpPtr)
        {
            // query for a DirectPlay2(A) interface
 #ifdef UNICODE
             hr = IDirectPlay_QueryInterface(dpPtr,IID_IDirectPlay3,(LPVOID *)&m_pDPlay);
 #else
            hr = IDirectPlay_QueryInterface(dpPtr,IID_IDirectPlay3A,(LPVOID *)&m_pDPlay);
 #endif
            // no longer need the DirectPlay1 interface
          TRACE(" IDirectPlay_QueryInterface returned %x\n", hr);
          IDirectPlay_Release(dpPtr);
			if FAILED( hr )
               return( FALSE );
        }
     gpComm->m_bSessionLost = FALSE;

     Caps.dwSize = sizeof(DPCAPS);
	 gpComm->m_pDPlay->GetCaps(&Caps,0);
	 gpComm->m_bHost = (Caps.dwFlags &  DPCAPS_ISHOST ? TRUE : FALSE);

		
//
//  All that's left is to create a player...
//

        hr = gpComm->CreatePlayer(
#ifdef UNICODE
                            m_pConnection->lpPlayerName->lpszShortName,
#else
                            m_pConnection->lpPlayerName->lpszShortNameA,
#endif
			NULL, NULL, 0 );

        TRACE(" CreatePlayer returned %x\n", hr);
        if FAILED( hr )
                return( FALSE );

      if (gpComm->m_bHost ) TRACE(" Connected via Lobby as Host id %x \n", gpComm->m_DPId);
	  else 	 TRACE(" Connected via Lobby as Slave id %x \n", gpComm->m_DPId);

	  gpComm->m_bStartedByLobby	= TRUE;
	  gpComm->Connected();
	  if( !gpComm->m_bHost ) InitJoinSession();
	  else strcpy( gpComm->m_PlayerName[0], m_pConnection->lpPlayerName->lpszShortNameA );
	  return( TRUE );
}

///========================================================================
//	Function:		Connected()
//
//	Description:
//		Signify that this machine is connected to a lobby or another machine.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void CComm::Connected( void )
{
	gpComm->m_Connected = TRUE;
}

///========================================================================
//	Function:		IsConnected()
//
//	Description:
//		Determine whether or not this machine is already connected to a lobby
//		or another machine.
//
//	Input:			none
//
//	Ouput:			TRUE		if connected, FALSE otherwise
//
///========================================================================

BOOL CComm::IsConnected( void )
{
	return( gpComm->m_Connected );
}

///========================================================================
//	Function:		Disconnect()
//
//	Description:
//		Disconnect this machine from a lobby or another machine.
//
//	Input:			none
//
//	Ouput:			OK		if connection succeeded, error otherwise
//
///========================================================================

HRESULT CComm::Disconnect( void )
{
	HRESULT		hr = 0;

	gpComm->m_Connected = FALSE;

	return(Release());

}

///========================================================================
/*
 * GetArmyIndexFromID
 *
 * Entry:
 *	id = DPID (Dplay ID).
 * Exit:
 *	Returns the army index.
 * Notes:
 *	Army indeces are used to extract army related information from the map data.
 *
 *	******************************* This is currently a stubbed out function ************************************
 */
UINT CComm::GetArmyIndexFromID(DPID id)
{
 int i;
 if (id == gpComm->m_DPId) return (0);
 for( i = 1; i<(int)gpComm->m_NumDPPlayers; i++) {
	if (gpComm->m_PlayerId[i] == id ) return i;
 }
//TRACE(" Error Can't find index for DPLAY ID %x \n", id);
return(0);
}

/*
 * GetArmyIndex
 *
 * Entry:
 *	wPlayer = player index.
 * Exit:
 *	Returns the army index.
 * Notes:
 *	Army indeces are used to extract army related information from the map data.
 *
 */
UINT CComm::GetArmyIndex(UINT wPlayer)
{
	if (wPlayer == -1)
		return -1;
	return(m_ArmyIndex[wPlayer]);
}


 
 /*
 * GetNumPlayers
 *
 * Entry:
 *	none
 * Exit:
 *	Returns the number of Direct Play Players in this game.	DOES NOT INCLUDE any AI players
 * Notes:
 *	
 */
UINT CComm::GetNumPlayers(void)
{
	return(m_NumDPPlayers);
}


UINT CComm::ColorFromIndex(UINT wPlayer) 
{
	if (wPlayer == -1)
		return -1;
	return(m_ArmyIndex[wPlayer]);
}

UINT	CComm::IndexFromColor(ARMY_COLOR color) {
 //  Code makes assumption that all 4 colors exit

    UINT i;
    if (color == ARMY_NO_COLOR) return -1;
	for (i= ARMY_PLAYER;i<ARMY_LAST_ARMY;i++) {
        if((ARMY_COLOR)m_ArmyIndex[i] == color) return i;
    }
    // TRACE(" FATAL ERROR Player Color Not Found %d \n", color);
	return 0;
}

UINT	CComm::AcquireColor(DPID from, ARMY_COLOR color) {
	//  Swap colors  Code makes assumption that all 4 colors exit

    UINT i,j;
    ARMY_COLOR oldColor;
	if (color == ARMY_NO_COLOR) return ARMY_NO_COLOR;
	i = GetArmyIndexFromID(from);
	j = IndexFromColor(color);
	if (gpComm->m_bHost )
		if (i < j) {
			oldColor = (ARMY_COLOR) m_ArmyIndex[i];
			if ( i != -1 )
			m_ArmyIndex[i] = color;
			if ( j != -1 )
			m_ArmyIndex[j] = oldColor;
		}
 	return i;
}

UINT	CComm::ReleaseColor(DPID from) {
	//  Swap colors  Code makes assumption that all 4 colors exit

    UINT i;
	i = GetArmyIndexFromID(from);
//	if ( i != -1 )
//		m_ArmyIndex[i] = ARMY_NO_COLOR;
    return i;
}


DPID CComm::GetIDFromIndex(UINT wPlayer) {

	if (wPlayer == -1)
		return 0;
	return(m_PlayerId[wPlayer]);
}

DPID	CComm::GetIDFromColor(ARMY_COLOR color) {

    UINT i;
    if (color == ARMY_NO_COLOR) return -1;
	for (i= ARMY_PLAYER;i<gpComm->m_NumDPPlayers;i++) {
        if((ARMY_COLOR)m_ArmyIndex[i] == color) return m_PlayerId[i];
    }
    return -1;
}

UINT	CComm::GetIndexFromID(DPID id)	{
	return( GetArmyIndexFromID( id ) );
}

UINT	CComm::GetColorFromID(DPID id)	{

	int i;
	if (id == gpComm->m_DPId) return (m_ArmyIndex[0]);
	for( i = 1; i<(int)gpComm->m_NumDPPlayers; i++) {
		if (gpComm->m_PlayerId[i] == id ) return (m_ArmyIndex[i]);
	}
	TRACE(" Error Can't find color for DPLAY ID %x \n", id);
	return((UINT)ARMY_NO_COLOR);
}

LONG	CComm::GlobalUID(LONG local) {
	int color;
	int index;
	LONG global;
	global = local;
	index = EXTRACT_ARMY(local);
	if (index != -1 ) {
		color = gpComm->ColorFromIndex(index); 
		global = (local & ~AI_ID_ARMY_MASK) |  ENCODE_ARMY(color);
	}
   return global;
}

	

LONG    CComm::LocalUID(LONG global) {
	int color;
	int index;
	LONG local;
	local = global;
	color = EXTRACT_ARMY(global);
	if (color != -1 ) {
		index = gpComm->IndexFromColor((ARMY_COLOR) color); 
		local = (global & ~AI_ID_ARMY_MASK) |  ENCODE_ARMY(index);
	}
   return local;
}

char *ArmyColorNames[4] =
	{
		"Green", "Tan  ", "Blue ", "Grey "
	};

 char * CComm::GetColorStr ( DPID id) {
	return ArmyColorNames[GetColorFromID(id) ];
 }


void	CComm::ResetBWStats() {
	int i;
	DWORD now;
	now = GetTickCount();
	m_MaxReceiveSize = m_MaxSendSize = m_TotalBytesReceived = m_TotalBytesSent = m_TotalPacketsReceived = m_TotalPacketsSent = 0;
	m_TimeStarted = now;
	for( i=0; i<COMM_SAMPLE_SIZE; i++ ) {
		m_SendTime[i] = now;
		m_SendSize[i] = 0;
		m_ReceiveTime[i] = now;
		m_ReceiveSize[i] = 0;
	}
	m_SendBWHWM = 0;
	m_ReceiveBWHWM = 0;
	m_NumRBWIntervals = 0;
	m_NumSBWIntervals = 0;
	m_NumSBWExceeded = 0;
	m_NumRBWExceeded = 0;
}

void	CComm::ReportBWStats () {
	DWORD elapsed;
	if (m_NumSBWIntervals ) {
	TRACE(" SEND    BANDWIDTH (%6d samples) MAX was %6d;  %6d (%3d%%) exceeded design spec(%d) \n",
		m_NumSBWIntervals,
		m_SendBWHWM,
		m_NumSBWExceeded,
		m_NumSBWExceeded*100/m_NumSBWIntervals,
		DESIGNSENDBW);
	}

 	if (m_NumRBWIntervals ) {
	TRACE(" RECEIVE BANDWIDTH (%6d samples) MAX was %6d;  %6d (%3d%%) exceeded design spec(%d) \n",
		m_NumRBWIntervals,
		m_ReceiveBWHWM,
		m_NumRBWExceeded,
		m_NumRBWExceeded*100/m_NumRBWIntervals,
		DESIGNRECEIVEBW);
	}
 	elapsed = (GetTickCount() - m_TimeStarted)/1000;
    if (elapsed < 1) elapsed = 1;
	if ( m_TotalPacketsSent)
		TRACE(" Sent     %8d Packets Max Size: %6d Ave Size: %6d Ave Packets/Second: %6d  Ave Bytes/Second: %6d  elapsed: %d \n",
			m_TotalPacketsSent,m_MaxSendSize,m_TotalBytesSent/m_TotalPacketsSent,m_TotalPacketsSent/elapsed, m_TotalBytesSent/elapsed,elapsed);
    if (m_TotalPacketsReceived)
		TRACE(" Received %8d Packets Max Size: %6d Ave Size: %6d Ave Packets/Second: %6d  Ave Bytes/Second: %6d  elapsed: %d\n",
			m_TotalPacketsReceived,m_MaxReceiveSize,m_TotalBytesReceived/m_TotalPacketsReceived,m_TotalPacketsReceived/elapsed,m_TotalBytesReceived/elapsed,elapsed);

}



/*
 * GetSendBW
 *
 * Entry:
 *	none.
 * Exit:
 *	Returns the number of Bytes per second sent over the last COMM_SAMPLE_SIZE sends interval
 * Notes:
 *	*******************************************************************
 */
	UINT	CComm::GetSendBW(void) {
		DWORD start,now,elapsed;
		UINT  bytes = 0, bytespersec;
		int i;
		start = m_SendTime[m_SendIndex];
		for (i=0;i<COMM_SAMPLE_SIZE;i++) {
			bytes += m_SendSize[i];
		}
		now = GetTickCount();
		elapsed = now-start;
		if (elapsed <= 0) return 0;
		bytespersec = bytes*1000/elapsed;
		m_NumSBWIntervals++;
		if (bytespersec > m_SendBWHWM) m_SendBWHWM = bytespersec;
		if (bytespersec > DESIGNSENDBW) m_NumSBWExceeded++;
		return bytespersec;
	}


/*
 * GetReceiveBW
 *
 * Entry:
 *	none.
 * Exit:
 *	Returns the number of Bytes per second sent over the last COMM_SAMPLE_SIZE Receives interval
 * Notes:
 *	*******************************************************************
 */
	UINT	CComm::GetReceiveBW(void) {
		DWORD start,now,elapsed;
		UINT  bytes = 0, bytespersec;
		int i;
		now = GetTickCount();
		start = m_ReceiveTime[m_ReceiveIndex];
		for (i=0;i<COMM_SAMPLE_SIZE;i++) {
			bytes += m_ReceiveSize[i];
		}
		elapsed = now-start;
		if (elapsed <= 0) return 0;
		bytespersec = bytes*1000/elapsed;
		if (bytespersec > 100000) {
			TRACE("bytes %d elapsed %d bps %d\n", bytes, elapsed, bytespersec);
			for (i=0;i<COMM_SAMPLE_SIZE;i++) {
				TRACE("i %d Time %d Size %d \n", i,m_ReceiveTime[i], m_ReceiveSize[i]);
			}
		}
		m_NumRBWIntervals++;
		if (bytespersec > m_ReceiveBWHWM) m_ReceiveBWHWM = bytespersec;
		if (bytespersec > DESIGNRECEIVEBW) m_NumRBWExceeded++;
		return bytespersec;
	}

/*
 * GetReceivePR
 *
 * Entry:
 *	none.
 * Exit:
 *	Returns the number of Packets per second received over the last COMM_SAMPLE_SIZE Receive intervals
 * Notes:
 *	*******************************************************************
 */
 	UINT	CComm::GetReceivePR(void) {
		DWORD start,now,elapsed;
		int i;
		now = GetTickCount();
		start = now;
		for (i=0;i<COMM_SAMPLE_SIZE;i++) {
			if ( m_ReceiveTime[i]	< start ) start = m_ReceiveTime[i];
		}

		elapsed = now-start;
		if (elapsed <= 0) return 0;
		
		return (COMM_SAMPLE_SIZE*1000)/elapsed;
	}

/*
 * GetSendPR
 *
 * Entry:
 *	none.
 * Exit:
 *	Returns the number of Packets per second sent over the last COMM_SAMPLE_SIZE Send intervals
 * Notes:
 *	*******************************************************************
 */
 	UINT	CComm::GetSendPR(void) {
		DWORD start,now,elapsed;
		start = m_SendTime[m_SendIndex];
		now = GetTickCount();
		elapsed = now-start;
		if (elapsed <= 0) return 0;
		
		return (COMM_SAMPLE_SIZE*1000)/elapsed;
	}


UINT CComm::GetNumLocalPlayers(void)
{
    int players = 4;
    int i;
    if (gpGame->GameType != GAMETYPE_ONEPLAYER) 
        for (i = 0; i < ARMY_LAST_ARMY; ++i)
        {
            if (m_ArmyRemote[i]) --players; // he is remote
        }
    return players;
}

// Return 1 if playing 0 if not playing -1 if he was playing but left;
int CComm::IsRemote(UINT wPlayer)
{
	if (m_ArmyRemote[wPlayer] == 0) return COMM_LOCAL; // he is not remote
	return (m_PlayerId[wPlayer] == 0xFFFFFFFF) ? COMM_NOTREMOTE : COMM_REMOTE;  // there is no comm player or he is remote
}

// Return 1 if playing 0 if not playing -1 if he was playing but left;
int CComm::WasRemote(UINT wPlayer)
{
	if (m_PlayerId[wPlayer] == 0xFFFFFFFF) return -1;  // he was remote 
	if (m_ArmyRemote[wPlayer] != 0) return 1; // he is  remote
	return 0;

}


void CComm::SetRemote(UINT wPlayer)
{
	m_ArmyRemote[wPlayer] = TRUE;
}

void CComm::ClearRemote(UINT wPlayer)
{
	m_ArmyRemote[wPlayer] = FALSE;
}

HKEY	CComm::GetAppRegKey( void )
{
	return(m_hRegKey);
}

void	CComm::SetAppRegDisp( DWORD dwAppRegDisp )
{
	m_dwRegDisp = dwAppRegDisp;
}

DWORD	CComm::GetAppRegDisp( void )
{
	return(m_dwRegDisp);
}

//  USED ONLY IN MAP SELECTION,  BEFORE GAME STARTS

BOOL	CComm::RemovePlayer(DPID id) {
	int i,j,oldcolor;
	i = gpComm->GetIndexFromID(id);
	if (i == 0) return FALSE;
	gpComm->m_NumDPPlayers--;
	TRACE("Remove Player numPlayers now = %d \n", gpComm->m_NumDPPlayers);
	if (id != 0xFFFFFFFF) DestroyFlow(id);
	oldcolor = gpComm->m_ArmyIndex[i];
	for (j=i;j<(int)gpComm->m_NumDPPlayers; j++) {
		gpComm->m_ArmyIndex[j] = gpComm->m_ArmyIndex[j+1];
		gpComm->m_PlayerId[j]  = gpComm->m_PlayerId[j+1];
		gpComm->m_ArmyReady[j] = gpComm->m_ArmyReady[j+1];
		strcpy(gpComm->m_PlayerName[j], gpComm->m_PlayerName[j+1]);	
	//  
		gpComm->m_ArmyRemote[j] = gpComm->m_ArmyRemote[j+1];
		gpComm->m_CommErrorCnt[j] = gpComm->m_CommErrorCnt[j+1];
		gpComm->m_Outstanding[j] = gpComm->m_Outstanding[j+1];
		gpComm->m_Seq[j] = gpComm->m_Seq[j+1];
		gpComm->m_TimeReceived[j] = gpComm->m_TimeReceived[j+1];
	}
	
	gpComm->m_PlayerId[gpComm->m_NumDPPlayers] = 0;
 	gpComm->m_ArmyRemote[gpComm->m_NumDPPlayers] = FALSE;
 	// strcpy(gpComm->m_PlayerName[gpComm->m_NumDPPlayers],"      ");
	*gpComm->m_PlayerName[gpComm->m_NumDPPlayers]= '\0';
	gpComm->m_ArmyIndex[gpComm->m_NumDPPlayers] = oldcolor;
	return TRUE;

}

//  USED ONLY IN GAME PLAYER LEAVING AN ACTIVE GAME
// Return TRUE if we actually remove him
//  Code may try to remove a player multiple times
//  Because sometimes we discover this through a DPSYS_DESTROYPLAYER message
// And sometimes through a DPSEND error (illegal id)
// Seems to be no way to predict what DPLAY will do when a player 
// Closes his comm connection.


BOOL	CComm::RemoveActivePlayer(DPID id) {

	int i;
	if( !m_bActive) return FALSE;
	if (id == 0 || id == 0xFFFFFFFF) return FALSE;
	DestroyFlow(id);
	i = gpComm->GetIndexFromID(id);
	if (i == 0) return FALSE;
	gpComm->m_PlayerId[i] = 0xFFFFFFFF;
	gpComm->ClearRemote(i);
	if( i==1) gpGame->UnPauseGame(PAUSE_REMOTEGONE1);
	if( i==2) gpGame->UnPauseGame(PAUSE_REMOTEGONE2);
	if( i==3) gpGame->UnPauseGame(PAUSE_REMOTEGONE3);
	if( i==1) gpGame->UnPauseGame(PAUSE_REMOTE1);
	if( i==2) gpGame->UnPauseGame(PAUSE_REMOTE2);
	if( i==3) gpGame->UnPauseGame(PAUSE_REMOTE3);
	if( i==1) gpGame->UnPauseGame(PAUSE_MAPLOAD1);
	if( i==2) gpGame->UnPauseGame(PAUSE_MAPLOAD2);
	if( i==3) gpGame->UnPauseGame(PAUSE_MAPLOAD3);
	if ( gpGame->GetSubState() == PLAY_SETUP_SUB_STATE) {
		gpComm->m_ArmyReady[i] = TRUE;
	}
	return TRUE;
}


BOOL	CComm::EverybodyInMapSelection( void )
{
int i;
for (i=0;i<(int)gpComm->m_NumDPPlayers; i++) {
	if ((m_PlayerId[i] != 0) && (m_PlayerId[i] != 0xFFFFFFFF) &&
	    m_ArmyReady[i]) return(FALSE);
	}


	return(TRUE);
}

BOOL	CComm::EverybodyHasMap( void )
{
int i;
for (i=0;i<(int)gpComm->m_NumDPPlayers; i++) {
	if ((m_PlayerId[i] != 0) && (m_PlayerId[i] != 0xFFFFFFFF) &&
	    (m_ArmyGotMap[i] == FALSE)) return(FALSE);
	}


	return(TRUE);
}
// is this global uid currently a playing army on this machine
BOOL	IsPlayingUID(UID uid)
{
	int color;
	int index;
	color = EXTRACT_ARMY(uid);
	if (color != ARMY_INDEPENDENT ) {
		index = gpComm->IndexFromColor((ARMY_COLOR) color); 
        return Armies[index].Status; // is it playing or not here
	}
    else return TRUE;
}


BOOL	CComm::RegSet( LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize )
{
	if (::RegSet( m_hRegKey, lptszName, lpData, dwSize ) == ERROR_SUCCESS)
		return TRUE;
	return FALSE;
}

BOOL	CComm::RegSetA( LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize )
{
	if (::RegSetA( m_hRegKey, lptszName, lpData, dwSize ) == ERROR_SUCCESS)
		return TRUE;
	return FALSE;
}

BOOL	CComm::RegGet( LPCTSTR lptszName, LPBYTE lpData, LPDWORD lpdwDataSize )
{
	if (::RegGet( m_hRegKey, lptszName, lpData, lpdwDataSize ) == ERROR_SUCCESS)
		return TRUE;
	return FALSE;
}
