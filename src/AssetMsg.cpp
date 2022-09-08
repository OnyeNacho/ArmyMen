//========================================================================
//	FILE:			$Workfile: AssetMsg.cpp $
//
//	DESCRIPTION:	Asset messaging routines.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, May 14, 1997
//
//	REVISION:		$Header: /ArmyMen/src/AssetMsg.cpp 24    4/02/98 2:03p Phu $
//
//========================================================================
//                 COPYRIGHT(C)1996, 1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/AssetMsg.cpp $
//  
//  24    4/02/98 2:03p Phu
//  typecasting to prevent warnings
//  
//  23    4/01/98 1:25p Bwilcox
//  change local test
//  
//  22    3/27/98 3:36p Bwilcox
//  
//  21    3/27/98 3:29p Bwilcox
//  
//  20    3/27/98 3:02p Bwilcox
//  
//  19    3/27/98 2:25p Bwilcox
//  asset cleanup in message
//  
//  18    2/10/98 11:32a Bwilcox
//  mines are placed by net message object_place, not by local firing.
//  objectdamage now takes spoint instead of spoint *
//  dead field removed from objectmessage
//  
//  
//  $Nokeywords:$
///========================================================================

///========================================================================
// Includes
///========================================================================
#include "stdafx.h"

#include	"Army.h"
#include	"ArmyMsg.h"
#include	"MainFrm.h"
#include	"Tad.h"
#include	"AssetMsg.h"
#include	"AiAccess.h"
#include	"Object.h"
#include	"objectmsg.h"
#include	"Damage.h"
#include    "comm.h"
#include	"item.h"

///========================================================================
// Debugging support
///========================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	EXTRACT_TYPE(y) ((UNIT_TYPE) SUB1TYPE(y))


///========================================================================
//	Function:		AssetFireMessageSend()
//	Description:    Create message for others describing the Asset firing
///========================================================================

void	AssetFireMessageSend( OBJECT* pAsset )
{
	ASSET_SHORT_MESSAGE	msg;
	int					size;

	ASSERT( ITEM_TYPE(pAsset) == ARMY_ASSET);

	size = sizeof(ASSET_SHORT_MESSAGE);
	ZeroMemory( &msg, sizeof(ASSET_SHORT_MESSAGE) );

	// get the unique ID for this troopers unit
	msg.nSize       = size;
	msg.msg_type    = FIRE_MESSAGE;
	msg.nUniqueID   = ITEM_UID(pAsset);
	msg.nUniqueIDsecondary = gpComm->GlobalUID(ITEM_UID(pAsset->common.pVictim));
	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}



///========================================================================
//	Function:		AssetFireMessageReceive()
//	Description:	Receive a message from others describing the Asset firing
///========================================================================

void	AssetFireMessageReceive( ASSET_SHORT_MESSAGE *pTMsg,OBJECT* pAsset )
{
	ITEM*			pVictim;
	pVictim = (ITEM *)ObjectFind( gpComm->LocalUID(pTMsg->nUniqueIDsecondary));
    if( pAsset && pVictim )
    {
		AssetFireWeapon( pAsset, pVictim );
    }
}


///========================================================================
//	Function:		AssetMessageReceive()
//	Description: 	Dispatch Asset messages
///========================================================================

void	AssetMessageReceive(ARMY_MESSAGE *pMsg,int army_index)
{
	OBJECT*					pAsset;
	pAsset = ObjectFind(pMsg->nUniqueID);
    if (!pAsset)
	{
		TRACE( "ERROR: AssetFireMessageReceive(): Asset not found\n" );
		ASSERT(0);
        return;
	}
    ASSERT(ITEM_TYPE(pAsset) == ARMY_ASSET);

	switch (pMsg->msg_type)	{
		case FIRE_MESSAGE:
			ASSERT(!IS_LOCAL_ARMY(ITEM_ARMY(pAsset)));
			AssetFireMessageReceive((ASSET_SHORT_MESSAGE*)pMsg,pAsset);
			break;
		default: // all other messages are presumed to be obj type messages
            ObjectMessageReceive(pMsg);
			break;
	}
}

//========================================================================
//							EOF
//========================================================================
