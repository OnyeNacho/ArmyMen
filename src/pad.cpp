/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: pad.cpp $
//
//	DESCRIPTION:	Code for handling PADs (Position Activated Devices, as
//						the mighty Bruce calls them)
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Wednesday, September 3, 1997
//
//	REVISION:		$Header: /ArmyMen/src/pad.cpp 36    98-04-09 19:58 Dmaynard $
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

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "army.h"
#include "event.h"
#include "gameflow.h"

#include "pad.h"

#include "item.h"
#include "aiaccess.h"

#include "map.h"
#include "scripts.h"

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
LOGICAL_PAD LogicalPads[MAX_NUM_LOGICAL_PADS];
PHYSICAL_PAD PhysicalPads[MAX_NUM_PHYSICAL_PADS];

int numlogicalpads=0;
char *PadNames[MAX_NUM_LOGICAL_PADS];
extern char scriptDebug;
/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

int CheckFlags(int flags, ITEM *whichItem)
{
	//this check must be done first
	if (flags & PAD_FLAG_SPECIFIC_ITEM)
	{
		if ((whichItem->eventNum | PAD_FLAG_SPECIFIC_ITEM) == flags)
			return 1;
		else
			return 0;
	}





	if (flags & PAD_FLAG_SARGE)
		if (ITEM_TYPE(whichItem) != ARMY_SARGE)
			return 0;

	if (flags & PAD_FLAG_UNIT)
		if (ITEM_TYPE(whichItem) != ARMY_UNIT)
			return 0;

	if (flags & PAD_FLAG_ARMYMAN)
		if ((ITEM_TYPE(whichItem) != ARMY_SARGE) && (ITEM_TYPE(whichItem) != ARMY_UNIT))
			return 0;

	if (flags & PAD_FLAG_JEEP)
		if ((ITEM_TYPE(whichItem) != ARMY_VEHICLE) || (ITEM_CLASS(whichItem) != ARMY_JEEP))
			return 0;

	if (flags & PAD_FLAG_TANK)
		if ((ITEM_TYPE(whichItem) != ARMY_VEHICLE) || (ITEM_CLASS(whichItem) != ARMY_TANK))
			return 0;

	if (flags & PAD_FLAG_HALFTRACK)
		if ((ITEM_TYPE(whichItem) != ARMY_VEHICLE) || (ITEM_CLASS(whichItem) != ARMY_HALFTRACK))
			return 0;

	if (flags & PAD_FLAG_CONVOY)
		if ((ITEM_TYPE(whichItem) != ARMY_VEHICLE) || (ITEM_CLASS(whichItem) != ARMY_CONVOY))
			return 0;

	if (flags & PAD_FLAG_VEHICLE)
		if (ITEM_TYPE(whichItem) != ARMY_VEHICLE)
			return 0;

	if (flags & PAD_FLAG_GROUNDVEHICLE)
		if ((ITEM_TYPE(whichItem) != ARMY_VEHICLE) || ((ITEM_CLASS(whichItem) != ARMY_JEEP) &&
				(ITEM_CLASS(whichItem) != ARMY_TANK) && (ITEM_CLASS(whichItem) != ARMY_HALFTRACK)))
			return 0;

	if (flags & PAD_FLAG_COMMANDER)
		if ((ITEM_TYPE(whichItem)!= ARMY_VEHICLE) && (ITEM_TYPE(whichItem)!= ARMY_SARGE))
			return 0;

	if (flags & PAD_FLAG_GREEN)
		if (PlayerColor(ITEM_ARMY(whichItem)) != ARMY_GREEN)
		    return 0;

	if (flags & PAD_FLAG_TAN)
		if (PlayerColor(ITEM_ARMY(whichItem)) != ARMY_TAN)
			return 0;

	if (flags & PAD_FLAG_GREY)
		if (PlayerColor(ITEM_ARMY(whichItem)) != ARMY_GRAY)
			return 0;

	if (flags & PAD_FLAG_BLUE)
		if (PlayerColor(ITEM_ARMY(whichItem)) != ARMY_BLUE)
			return 0;

	if (flags & PAD_FLAG_NPC)
    {
		if (ITEM_TYPE(whichItem) == ARMY_UNIT)
            return  ((UNIT*)whichItem)->npc;
		if (ITEM_TYPE(whichItem) == ARMY_SARGE)
            return ((SARGE*)whichItem)->npc;
		return 0;
    }

	return 1;
}

int CheckCondition(int triggernum, int comptype, int curnum)
{
	switch (comptype)
	{
	case PAD_COMP_EQUALS:
		if (triggernum==curnum)
			return 1;
		return 0;

	case PAD_COMP_LESSTHAN:
		if (curnum<triggernum)
			return 1;
		return 0;

	case PAD_COMP_GREATERTHAN:
		if (curnum>triggernum)
			return 1;
		return 0;
	}
	return 0;
}

void PadDeactivateCallBack(EVENT_TYPE type, int num, long uid, void *callback)
{
	LOGICAL_PAD *curlogicalpad;

	curlogicalpad=(LOGICAL_PAD*) callback;

	if (curlogicalpad->curoffdelayeventnum==num)
    {
        if (scriptDebug)
            TRACE("    Physpad %d ",curlogicalpad->physPadNum);
        EventTrigger(EVENT_PADDEACTIVATED, curlogicalpad->padNum, uid, 0, 0);
    }
}
void PadActivateCallBack(EVENT_TYPE type, int num, long uid, void *callback)
{
	LOGICAL_PAD *curlogicalpad;

	curlogicalpad=(LOGICAL_PAD*) callback;

	if (curlogicalpad->curondelayeventnum==num)
    {	
        if (scriptDebug)
            TRACE("    Physpad %d ",curlogicalpad->physPadNum);

			EventTrigger(EVENT_PADACTIVATED, curlogicalpad->padNum, uid, 0, 0);
    }
}
		


void PadStateChange(LOGICAL_PAD *curlogicalpad, ITEM *whichItem)
{

	long uid;

	if (whichItem)
		uid=whichItem->nUniqueID;
	else
		uid=0;

	if (CheckCondition(curlogicalpad->triggerNum, curlogicalpad->padCompType, curlogicalpad->curNum))
	{
		if (!curlogicalpad->curState)
		{
			curlogicalpad->curState=1;
			curlogicalpad->curoffdelayeventnum=0;

			if (curlogicalpad->ondelay==0)
            {
                if (scriptDebug)
                    TRACE("    Physpad %d ",curlogicalpad->physPadNum);

					if (gpGame->GameType == GAMETYPE_ONEPLAYER || ITEM_TYPE(whichItem) == ARMY_SARGE)
						EventTrigger(EVENT_PADACTIVATED, curlogicalpad->padNum, uid, 0, 0);
            }
			else if (EventsActive == 2)
			{
				curlogicalpad->curondelayeventnum=UniqueEventNum();
				EventRegister(EVENT_CONTROL, curlogicalpad->curondelayeventnum, PadActivateCallBack, (void*)curlogicalpad);
				EventTrigger(EVENT_CONTROL, curlogicalpad->curondelayeventnum, uid, curlogicalpad->ondelay, 1);
			}
		}
	}
	else
	{
		if (curlogicalpad->curState)
		{
			
			curlogicalpad->curState=0;
			curlogicalpad->curondelayeventnum=0;

			if (curlogicalpad->offdelay==0)
            {
                if (scriptDebug)
                    TRACE("    Physpad %d ",curlogicalpad->physPadNum);

				if (gpGame->GameType == GAMETYPE_ONEPLAYER || ITEM_TYPE(whichItem) == ARMY_SARGE)
					EventTrigger(EVENT_PADDEACTIVATED, curlogicalpad->padNum, uid, 0, 0);
            }
			else if (EventsActive == 2)
				{
					curlogicalpad->curoffdelayeventnum=UniqueEventNum();
					EventRegister(EVENT_CONTROL, curlogicalpad->curoffdelayeventnum, PadDeactivateCallBack, (void*)curlogicalpad);
					EventTrigger(EVENT_CONTROL, curlogicalpad->curoffdelayeventnum, uid, curlogicalpad->offdelay, 1);
				}
		}
	}
}




void ItemEnterPad(ITEM *whichItem, PHYSICAL_PAD *whichPad)
{
	int i;
	LOGICAL_PAD *curlogicalpad;

	for (i=0;i<whichPad->numLogicalPads;i++)
	{
		curlogicalpad=&LogicalPads[whichPad->logicalPads[i]];

		switch(curlogicalpad->padType)
		{
		case PAD_TYPE_BINARY:
			if (CheckFlags(curlogicalpad->padFlags, whichItem))
			{
				curlogicalpad->curNum++;
				
				PadStateChange(curlogicalpad, whichItem);

			}
			break;


		case PAD_TYPE_TRIGGERED:
			if (CheckFlags(curlogicalpad->padFlags, whichItem))
            {
                if (scriptDebug)
                    TRACE("    Physpad %d ",curlogicalpad->physPadNum);

				EventTrigger(EVENT_PADACTIVATED, curlogicalpad->padNum, whichItem->nUniqueID, 0, 0);
            }
			break;
		}
	}
}



void ItemLeavePad(ITEM *whichItem, PHYSICAL_PAD *whichPad)
{
	int i;
	LOGICAL_PAD *curlogicalpad;

	for (i=0;i<whichPad->numLogicalPads;i++)
	{
		curlogicalpad=&LogicalPads[whichPad->logicalPads[i]];

		switch(curlogicalpad->padType)
		{
		case PAD_TYPE_BINARY:
			if (CheckFlags(curlogicalpad->padFlags, whichItem))
			{
				curlogicalpad->curNum--;
				if (curlogicalpad->curNum<0)
				{
					TRACE("ERROR: pad %d thinks there are less than zero items on it\n",
						curlogicalpad->physPadNum);
					curlogicalpad->curNum=0;
					break;
				}
				
				PadStateChange(curlogicalpad, whichItem);

			}
			break;
		}
	}
}




///========================================================================
//	Function:		ItemUpdatePad()
//
//	Description:
//		For a particular item which has just (presumably) moved, figures out
//		which pads it entered and/or left, and calls ItemEnterPad and 
//		ItemLeavePad as appropriate
//
//	Input:			pItem		pointer to the item
//
//	Ouput:			int			1 if pads have been entered or left.
//								0 otherwise		
//
///========================================================================
int ItemUpdatePad(ITEM *pItem)
{
	unsigned char oldbitpads=0, newbitpads=0;
	unsigned char oldpad=0, newpad=0;
	unsigned char padsentered, padsleft;
	int curpad, curpadbit;
	int retval = 0;

	if (pItem->tile == pItem->oldTile)
		return 0;

	if (the_map.bit_pads_layer!=NULL)
	{
		if (pItem->tile!=0)
			newbitpads=the_map.bit_pads_layer[pItem->tile];

		if (pItem->oldTile!=0)
			oldbitpads=the_map.bit_pads_layer[pItem->oldTile];

		if (newbitpads!=oldbitpads)
		{
			padsentered=newbitpads&(~oldbitpads);
			padsleft=oldbitpads&(~newbitpads);

			for (curpad=0;curpad<8;curpad++)
			{
				curpadbit=1<<curpad;
				if (padsentered & curpadbit)
					ItemEnterPad(pItem, &PhysicalPads[curpad]);
				else if (padsleft & curpadbit)
					ItemLeavePad(pItem, &PhysicalPads[curpad]);
			}
			retval = 1;
		}
	}

	if (the_map.numeric_pads_layer!=NULL)
	{
		if (pItem->tile!=0)
			newpad=the_map.numeric_pads_layer[pItem->tile];

		if (pItem->oldTile!=0)
			oldpad=the_map.numeric_pads_layer[pItem->oldTile];

		if (newpad!=oldpad)
		{
			if (newpad!=0)
				ItemEnterPad(pItem, &PhysicalPads[newpad]);
			if (oldpad!=0)
				ItemLeavePad(pItem, &PhysicalPads[oldpad]);
			retval = 1;
		}
	}

	return retval; 
}

char *getPadName(int num)
{
	if ((num<0) || (num>=numlogicalpads))
		return NULL;
	
	return PadNames[num];
}

int GeneratePadFromTokens(char tokens[][TOKENLENGTH], int numtokens)
{
	int curtoken=0;
	int physicalpadnum;

	if (numtokens<4)
	{
		TRACE("ERROR: two few tokens to specify a pad\n");
		return -1;
	}

	if (strcmp(tokens[0], "PAD")!=0)
	{
		TRACE("ERROR: expected token 'PAD'\n");
		return -1;
	}

	if (gettokentype(tokens[1]) != TOKEN_TYPE_STRING)
	{
		TRACE("ERROR: expected string token for pad name\n");
		return -1;
	}

	LogicalPads[numlogicalpads].padNum=numlogicalpads;
	PadNames[numlogicalpads]=(char*)malloc(strlen(tokens[1])+2);
	sprintf(PadNames[numlogicalpads], "%s", tokens[1]);

	LogicalPads[numlogicalpads].padType=PAD_TYPE_TRIGGERED; //default

	if (gettokentype(tokens[2]) != TOKEN_TYPE_NUMBER)
	{
		TRACE("ERROR: expected number token for pad num\n");
		return -1;
	}

	physicalpadnum=atoi_nonneg(tokens[2]);
	if ((physicalpadnum<0) || (physicalpadnum>MAX_NUM_PHYSICAL_PADS))
	{
		TRACE("ERROR: invalid physical pad number\n");
		return -1;
	}
	
	PhysicalPads[physicalpadnum].logicalPads[PhysicalPads[physicalpadnum].numLogicalPads++]=numlogicalpads;
	LogicalPads[numlogicalpads].physPadNum=physicalpadnum;

	curtoken=3;

	while (curtoken<numtokens && gettokentype(tokens[curtoken])==TOKEN_TYPE_STRING && 
		!(LogicalPads[numlogicalpads].padFlags & PAD_FLAG_SPECIFIC_ITEM))
	{
		if (strcmp(tokens[curtoken], "EVERYTHING")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_EVERYTHING;
		else if (strcmp(tokens[curtoken], "SARGE")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_SARGE;
		else if (strcmp(tokens[curtoken], "UNIT")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_UNIT;
		else if (strcmp(tokens[curtoken], "ARMYMAN")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_ARMYMAN;
		else if (strcmp(tokens[curtoken], "JEEP")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_JEEP;
		else if (strcmp(tokens[curtoken], "TANK")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_TANK;
		else if (strcmp(tokens[curtoken], "HALFTRACK")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_HALFTRACK;
		else if (strcmp(tokens[curtoken], "CONVOY")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_CONVOY;
		else if (strcmp(tokens[curtoken], "VEHICLE")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_VEHICLE;
		else if (strcmp(tokens[curtoken], "GROUNDVEHICLE")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_GROUNDVEHICLE;
		else if (strcmp(tokens[curtoken], "COMMANDER")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_COMMANDER;
		else if (strcmp(tokens[curtoken], "GREEN")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_GREEN;
		else if (strcmp(tokens[curtoken], "TAN")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_TAN;
		else if (strcmp(tokens[curtoken], "GREY")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_GREY;
		else if (strcmp(tokens[curtoken], "GRAY")==0)
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_GREY;
		else if (strcmp(tokens[curtoken], "BLUE")==0 )
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_BLUE;
		else if (strcmp(tokens[curtoken], "NPC")==0 )
			LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_NPC;
		else
		{
			if ((LogicalPads[numlogicalpads].padFlags=GetNamedItemNumber(tokens[curtoken]))<0)
			{
				TRACE("ERROR: unkown flag or item name %s encountered\n", tokens[curtoken]);
				return -1;
			}
			else
				LogicalPads[numlogicalpads].padFlags|=PAD_FLAG_SPECIFIC_ITEM;
		}

		curtoken++;
	}

	if (curtoken==numtokens) 
	{
		numlogicalpads++;
		return curtoken;
	}

	if (gettokentype(tokens[curtoken])!=TOKEN_TYPE_CONTROLCHAR)
	{
		numlogicalpads++;
		return curtoken;

	}

	if (tokens[curtoken][0]!='<' && tokens[curtoken][0]!='=' && tokens[curtoken][0]!='>')
	{
		TRACE("ERROR: after flags, expected one of <=>\n");
		return -1;
	}

	if (curtoken==numtokens-1)
	{
		TRACE("ERROR: incomplete set of tokens for pad\n");
		return -1;
	}

	if (gettokentype(tokens[curtoken+1])!=TOKEN_TYPE_NUMBER)
	{
		TRACE("ERROR: expected a number after a comparison character\n");
		return -1;
	}

	LogicalPads[numlogicalpads].padType=PAD_TYPE_BINARY;
	LogicalPads[numlogicalpads].triggerNum=atoi_nonneg(tokens[curtoken+1]);
	switch(tokens[curtoken][0])
	{
		case '=': LogicalPads[numlogicalpads].padCompType=PAD_COMP_EQUALS;
			  break;

		case '<': LogicalPads[numlogicalpads].padCompType=PAD_COMP_LESSTHAN;
			  break;

		case '>': LogicalPads[numlogicalpads].padCompType=PAD_COMP_GREATERTHAN;
			  break;
	}

	curtoken+=2;

	if (numtokens==curtoken)
	{
		PadStateChange(&LogicalPads[numlogicalpads], NULL);
		numlogicalpads++;
		return curtoken;
	}

	if (gettokentype(tokens[curtoken])==TOKEN_TYPE_STRING)
		if (strcmp(tokens[curtoken], "DELAY")==0)
		{
			if (numtokens<=curtoken+2)
			{
				TRACE("ERROR: not enough numbers after 'DELAY'\n");
				return -1;
			}

			if (!(gettokentype(tokens[curtoken+1])==TOKEN_TYPE_NUMBER || 
					gettokentype(tokens[curtoken+1])==TOKEN_TYPE_NUMBER_WITH_DECIMAL_POINT))
			{
				TRACE("ERROR: expected a number after a pad DELAY\n");
				return -1;
			}

			LogicalPads[numlogicalpads].ondelay=processNumberWithDecimalPoint(tokens[curtoken+1]);
			if (LogicalPads[numlogicalpads].ondelay<0)
			{
				TRACE("ERROR: negative time set for a pad DELAY\n");
				return -1;
			}


			if (!(gettokentype(tokens[curtoken+2])==TOKEN_TYPE_NUMBER || 
					gettokentype(tokens[curtoken+2])==TOKEN_TYPE_NUMBER_WITH_DECIMAL_POINT))
			{
				TRACE("ERROR: expected two numbers after a pad DELAY\n");
				return -1;
			}

			LogicalPads[numlogicalpads].offdelay=processNumberWithDecimalPoint(tokens[curtoken+2]);
			if (LogicalPads[numlogicalpads].offdelay<0)
			{
				TRACE("ERROR: negative time set for a pad DELAY\n");
				return -1;
			}
			
			curtoken+=3;
		}


	PadStateChange(&LogicalPads[numlogicalpads], NULL);
	numlogicalpads++;
	return curtoken;
	
}
void PrintPads(void)
{
    if (scriptDebug)
    {
	int i;

	TRACE("About to print %d pads\n", numlogicalpads);
	for (i=0; i<numlogicalpads;i++)
	{
		TRACE("    pad %d=%d name %s", i, LogicalPads[i].padNum, PadNames[i]);
		TRACE(" type %d trigger num %d comp type %d", LogicalPads[i].padType, LogicalPads[i].triggerNum, LogicalPads[i].padCompType);
		TRACE("  delay %d %d flags %d\n", LogicalPads[i].ondelay, LogicalPads[i].offdelay, LogicalPads[i].padFlags);
		
    }
	}
}

void InitPads(void)
{
	ZeroMemory(LogicalPads, sizeof(LogicalPads));
	ZeroMemory(PhysicalPads, sizeof(PhysicalPads));
	numlogicalpads=0;
	ZeroMemory(PadNames, sizeof(PadNames));

}

void KillPads(void)
{
	int i;
	for (i=0;i<numlogicalpads;i++)
		if (PadNames[i])
		{
			free(PadNames[i]);
			PadNames[i]=NULL;
		}

	numlogicalpads=0;
	ZeroMemory(PhysicalPads, sizeof(PhysicalPads));
}

int GetPadNumFromName(char *padname)
{
	int i;

	//int numlogicalpads=0;
	//char *PadNames[MAX_NUM_LOGICAL_PADS];

	for (i=0;i<numlogicalpads;i++)
		if (strcmp(padname, PadNames[i])==0)
			return LogicalPads[i].padNum;

	return -1;
}

int LogicalPadNumToPhysicalPadNum(int logicalnum)
{
	int i;

	for (i=0;i<numlogicalpads;i++)
		if (LogicalPads[i].padNum==logicalnum)
			return LogicalPads[i].physPadNum;

	return -1;
}






















