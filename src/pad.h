/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: pad.h $
//
//	DESCRIPTION:	Headers for handling PADs (Position Activated Devices, as
//						the mighty Bruce calls them)
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Wednesday, September 3, 1997
//
//	REVISION:		$Header: /ArmyMen/src/pad.h 19    12/15/97 5:47p Awerner $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  1     9/3/97 11:42a Awerner
//
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef _PAD_H_
#define _PAD_H_


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "army.h"

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////


extern int numlogicalpads;

/////////////////////////////////////////////////////////////////////////////
// defines and typedefs
/////////////////////////////////////////////////////////////////////////////


#define PAD_FLAG_EVERYTHING 0
#define PAD_FLAG_SARGE 1
#define PAD_FLAG_UNIT 2
#define PAD_FLAG_ARMYMAN 4 //sarge or unit
#define PAD_FLAG_JEEP 8
#define PAD_FLAG_TANK 16
#define PAD_FLAG_HALFTRACK 32
#define PAD_FLAG_CONVOY 64
#define PAD_FLAG_VEHICLE 128
#define PAD_FLAG_GROUNDVEHICLE 256
#define PAD_FLAG_COMMANDER 512 //sarge or vehicle
#define PAD_FLAG_GREEN 1024
#define PAD_FLAG_TAN 2048
#define PAD_FLAG_GREY 4096
#define PAD_FLAG_BLUE 8192
#define PAD_FLAG_NPC 16384

#define PAD_FLAG_SPECIFIC_ITEM (1<<31) //if this bit is set, then the rest of the
									   //flag int is an item num

//types of comparisons
#define PAD_COMP_EQUALS 0
#define PAD_COMP_LESSTHAN 1
#define PAD_COMP_GREATERTHAN 2

//types of pad
#define PAD_TYPE_BINARY 1
#define PAD_TYPE_TRIGGERED 0

//max number of logical pads associated with a physical pads
#define MAX_NUM_LOGICAL_PADS_PER_PHYSICAL 16
#define MAX_NUM_PHYSICAL_PADS			  256 //depends on bits in map
#define MAX_NUM_LOGICAL_PADS			  512



typedef struct
{
	char numLogicalPads;
	short logicalPads[MAX_NUM_LOGICAL_PADS_PER_PHYSICAL]; //indices into an array of logical pads...
											 //could be pointers depending on how things
											 //need to be allocated

	//possible extension: linked list of items currently on this physical pad
} PHYSICAL_PAD;
	
typedef struct
{
	short padNum;		//the pad's number
	short physPadNum;   //the corresponding physical pad (if a logical pad is attached
						//to more than one physical pad, this will only be one of them)

	char padType;
	short triggerNum; // the number of items of the type specified by flags needed to
					  // turn a binary pad on. A triggered pad always triggers off of a
					  // single item
	unsigned int padFlags;
	char padCompType; //equals, greather than, or less than

	short ondelay, offdelay;	  //how long after the pad is activated ordeactivated 
								  //does the event trigger (in seconds)

	int curondelayeventnum, curoffdelayeventnum; //the most recent delayed event that's been generated

	int curNum;	//how many items are currently there
	char curState; //for a binary pad, whether the state is currently true

	//possible extensions: list of all items on the pad, pointer back to the relevant
	//physical pad structure
} LOGICAL_PAD;




/////////////////////////////////////////////////////////////////////////////
// Function Prototypes
/////////////////////////////////////////////////////////////////////////////

void InitPads(void);
void KillPads(void);

void PrintPads(void);
int GeneratePadFromTokens(char tokens[][TOKENLENGTH], int numtokens);
int ItemUpdatePad(ITEM *pItem);
int GetPadNumFromName(char *padname);
int LogicalPadNumToPhysicalPadNum(int logicalnum);
char *getPadName(int num);




#endif