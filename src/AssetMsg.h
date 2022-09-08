//========================================================================
//	FILE:			$Workfile: AssetMsg.h $
//
//	DESCRIPTION:	Asset messaging interface.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, May 14, 1997
//
//	REVISION:		$Header: /ArmyMen/src/AssetMsg.h 11    3/27/98 2:25p Bwilcox $
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
//  $Log: /ArmyMen/src/AssetMsg.h $
//  
//  11    3/27/98 2:25p Bwilcox
//  asset cleanup in message
//  
//  10    3/27/98 10:06a Bwilcox
//  common message structure for safety in future
//  
//  9     12/19/97 8:50p Phu
//  assets...
//  
//  8     12/19/97 4:26p Phu
//  Network assets
//  
//  7     12/09/97 12:11p Phu
//  
//  5     8/21/97 6:45p Bwilcox
//  added fromUID fields and args to indicate WHO caused the damage being
//  applied.
//  
//  4     8/17/97 7:16p Nrobinso
//  minimize message data
//  
//  3     8/07/97 11:28p Nrobinso
//  damage cleanup
//  
//  2     8/05/97 3:27p Nrobinso
//  rename item bFlags bItemFlags
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  4     6/09/97 3:07p Aburgess
//  corrected prototype name
//  
//  3     5/15/97 12:13a Aburgess
//  moved MSG_TYPES to ArmyMsg.h
//  
//  2     5/14/97 7:25p Aburgess
//  Death Message
//  
//  1     5/14/97 5:11p Aburgess
//  Asset remote messaging prototypes and structures
//  
//  $Nokeywords:$
///========================================================================

#ifndef __ASSETMSG_H__
#define __ASSETMSG_H__

///========================================================================
// Includes
///========================================================================

#include "ArmyMsg.h"
#include "donottouch.h"


///========================================================================
//					Global Variables
///========================================================================

///========================================================================
//					Global Prototypes
///========================================================================

void	AssetFireMessageSend( OBJECT* pAsset );
void	AssetMessageReceive( ARMY_MESSAGE *pMsg, int army_index );
#endif

///========================================================================
//								EOF
///========================================================================
