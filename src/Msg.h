//========================================================================
//	FILE:			$Workfile: Msg.h $
//
//	DESCRIPTION:	Army Unit Message processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, September 17, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Msg.h 28    4/14/98 4:22p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Msg.h $
//  
//  28    4/14/98 4:22p Nrobinso
//  remove msg loop
//  
//  27    4/14/98 2:42p Nrobinso
//  turn off health voice over on sarge death
//  
//  26    4/07/98 3:24p Nrobinso
//  msg routines take a volume
//  
//  24    3/26/98 6:27p Bwilcox
//  moving a text to usa.h, deleting unused UNIT_BLOCK stuff
//  
//  23    3/25/98 6:27p Nrobinso
//  add mission end voice over
//  
//  22    3/25/98 3:47p Nrobinso
//  add MissionMsg
//  
//  21    3/24/98 2:29p Nrobinso
//  put voice messages with text thru MsgBroadcastWithText
//  
//  20    3/24/98 12:09p Nrobinso
//  remove unused; add a looped msgbroadcast
//  
//  19    12/09/97 12:12p Phu
//  
//  18    11/24/97 2:50p Aburgess
//  removal of army mission statement structure. now within .CPN data
//  
//  17    11/17/97 10:07a Aburgess
//  made MsgBroadcast globally accessable through MSG
//  
//  16    11/17/97 1:42a Bwilcox
//  Sitrep added
//  
//  15    11/07/97 10:41a Aburgess
//  Mission Objective message modifications
//  
//  14    10/27/97 11:27a Aburgess
//  new Mission Message routines
//  
//  11    9/15/97 10:10a Nrobinso
//  change terminology to be in line with design
//  
//  10    8/17/97 7:16p Nrobinso
//  minimize message data
//  
//  9     8/14/97 1:15p Nrobinso
//  get names for vehicles and sarge
//  
//  8     8/05/97 2:05p Awerner
//  There's now a little box which gives info on the currently
//  selected target
//  
//  7     7/31/97 9:01a Aburgess
//  hide access to lastMessage inside MSG prototypes
//  
//  6     7/30/97 7:05p Aburgess
//  new prototype interfaces
//  
//  5     7/30/97 5:17p Aburgess
//  new msg interfaces, structures and defines
//  
//  4     7/29/97 11:01p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
//  
//  3     7/28/97 4:40p Aburgess
//  new structures and prototypes
//  
//  2     7/23/97 11:11p Aburgess
//  prototype and data structure upgrades
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  7     5/12/97 12:00p Dbunch
//  
//  6     2/20/97 1:34p Aburgess
//  removed superfluous comment block
//  
//  5     10/03/96 11:00a Aburgess
//  corrected MSG_NULL definition
//  
//  4     9/30/96 4:09p Aburgess
//  changed MSG lengths
//  
//  3     9/26/96 11:58a Aburgess
//  first pass implementation of MSG interface (last message).
//  
//  2     9/20/96 1:59p Aburgess
//  added printer head offset
//  
//  1     9/19/96 2:19p Aburgess
//  MSG datat structures and prototypes
//  
// 
//  $Nokeywords:$
//========================================================================

#ifndef __MSG_H__
#define __MSG_H__

#ifndef __ARMY_H__
#include "army.h"
#endif

///========================================================================
//							GLOBAL DEFINES
///========================================================================
// Null MSG flag
#define	MSG_NULL			(ULONG)~0
#define MSG_EMPTY				0

// printable string storage sizes
#define	MSG_MAX_NAME_LEN		32
#define	MSG_MAX_TYPE_LEN		16
#define	MSG_MAX_STRENGTH_LEN	4
#define	MSG_MAX_MODE_LEN		16
#define	MSG_MAX_TIME_LEN		16
#define	MSG_MAX_MSG_LEN			128

// max number of lines of printable text
#define	MSG_MAX_PRINTER_LINES	3
#define	MSG_MAX_PLINES			4

// max number of lines of printable text
#define	MSG_MAX_LINKS	8

// message audio base index
#define	MSG_AUDIO_BASE			TITLE

// message group ID indecies
#define	MSG_GROUP1				0
#define	MSG_GROUP2				1
#define	MSG_GROUP3				2
#define	MSG_GROUP4				3
#define	MSG_GROUP5				4
#define	MSG_GROUP6				5
#define	MSG_GROUP7				6
#define	MSG_GROUP8				7
#define	MSG_GROUP9				8
#define	MSG_TERMINATOR			9

// Msg sector name stype
#define	MSG_NO_SECTOR		   -1
#define	MSG_IN_SECTOR			0
#define MSG_FROM_SECTOR			1
#define MSG_JUST_SECTOR			2

///========================================================================
//							GLOBAL DATA TYPES
///========================================================================

typedef struct
{
	ULONG	nSound;
	char*	pString;
} MSG_BLOCK;

typedef struct
{
	MSG_BLOCK*	pRowNames;
	MSG_BLOCK*	pColumnNames;
} SECTOR_BLOCK;

#define	ACTION_BLOCK	MSG_BLOCK
#define	COLOR_BLOCK		MSG_BLOCK

typedef struct
{
	ULONG			nSndID;		// resultant linked stream for message
	ACTION_BLOCK*	pAction;	// Action msg block
	COLOR_BLOCK*	pColor;		// Foe color msg block
	SECTOR_BLOCK*	pSector;	// Sector msg block
} SQUAD_MSG;

typedef struct
{
	char*	pUnitName;
	char*	pUnitType;
	char*	pUnitStrength;
	char*	pUnitMode;
} MSG_UNIT_INFO;

typedef struct
{
	char	nLines;			// NOTE: nLines is ALWAYS >= 1, line 0 is the TIME
	char*	pMsgText[ MSG_MAX_PLINES ];
} MSG_MSG_INFO;

typedef struct
{
	MSG_UNIT_INFO	unitInfo;
	MSG_MSG_INFO	msgInfo;
} MSG_PRINT;

// Message Structure
typedef struct
{
//	TIME		msgTime;						// when the message was issued
	ULONG		msgAudioID;						// audio ids for voice message stream
	MSG_BLOCK*	msgIDs[ MSG_MAX_LINKS+1 ];		// msg ids for audio/text message links
	char*		msgString;
	// store off the Priority/Situation and target for avoidance of repeat messages
	ULONG		msgPriority;					// priority value of this message
	UINT		msgTarget;						// possible target associated with message
} MESSAGE;

extern	ACTION_BLOCK	MsgActions[ 8 ];
extern	COLOR_BLOCK		MsgColors[ 4 ];
extern	MSG_BLOCK		MsgObjectNames[ MAX_OBJECTS ];
extern	MSG_BLOCK		MsgVehicleNames[];
extern	MSG_BLOCK*		MsgSectorNames[3];
extern	MSG_BLOCK		MsgSector;
extern	MSG_BLOCK		MsgInSector;
extern	MSG_BLOCK		MsgFromSector;
extern	SECTOR_BLOCK	MsgSectors[ 3 ];
extern	MSG_BLOCK		MsgRowNames[13];
extern	MSG_BLOCK		MsgColumnNames[13];

///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================
extern	void	MsgMission( int eArmy, int nCampaignIdx, int nScenarioIdx, int nMissionIdx );
extern	ULONG	MsgBroadcast( ULONG nStreamID, int volume_percent=100 );
extern	ULONG	MsgBroadcastWithText( ULONG nAudioID, int volume_percent=100 );

extern	void	SitRep(int situation,ITEM* pItem);
extern	void	MsgMission(void);
extern	void	MsgMissionEnd(BOOL winner, BOOL one_player);

#endif		// __MSG_H__

///========================================================================
//								EOF
///========================================================================
