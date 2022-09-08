#include "stdafx.h"

#include "army.h"
#include "aiaccess.h"
#include "vehicle.h"
#include "map.h"
#include "item.h"
#include "wobject.h"
#include "armymsg.h"
#include "objectmsg.h"
#include "damage.h"
#include "husk.h"


#define HUSK_BUFFER 10
void SubtractMaskFromVehicleLayer(VEHICLE_MASK* mask);


enum ADDITIONAL_CATEGORIES
{
	VEHICLE_HUSK_CATEGORY = 100
};


struct THuskList
{
	int   count;
	int   bufsize;
	THusk **husks;
};


THuskList HuskList = 
{
	0, 0, NULL
};


int DynamicID[ARMY_LAST_ARMY] = 
{
	0, 0, 0, 0
};


THusk *GetNewHusk( void )
{
	if( HuskList.count >= HuskList.bufsize )
	{									// increase the size of the husk list
		THusk **templist;
		int		newsize;

		newsize = HuskList.bufsize + HUSK_BUFFER;
		templist = (THusk **)malloc( newsize * sizeof(THusk *) );
		ASSERT( templist );

		ZeroMemory( templist, newsize * sizeof(THusk *) );
		if( HuskList.husks )			// copy the old list
			CopyMemory( templist, HuskList.husks, HuskList.count * sizeof(THusk *) );

		free( HuskList.husks );
		HuskList.husks = templist;
		HuskList.bufsize = newsize;
	}
	HuskList.husks[HuskList.count] = (THusk *)malloc( sizeof(THusk) );
	ASSERT( HuskList.husks[HuskList.count] );
	ZeroMemory( HuskList.husks[HuskList.count], sizeof(THusk) );
	HuskList.count++;

	return( HuskList.husks[HuskList.count-1] );
}


ITEM *FindHuskItem( UID uid )
{
	for( int i = 0; i < HuskList.count; i++ )
	{
		if( (HuskList.husks[i])->object.common.nUniqueID == uid )  {
			TRACE("Found Husk %x at %d,%d \n", uid, ((ITEM *)(HuskList.husks[i]))->position.x , ((ITEM *)(HuskList.husks[i]))->position.y);
			return( (ITEM *)(HuskList.husks[i]) );
		}
	}
	return NULL;
}


// create a dynamic object of the vehicle husk
void CreateVehicleHusk( VEHICLE *pVehicle )
{
	THusk *pHusk;

	pHusk = GetNewHusk();
	ASSERT( pHusk );

	OBJECTSTRUCT *pObj;
	int army;	
	TRACE("Creating Husk UID ");
	pObj = &(pHusk->object);

	pObj->category = VEHICLE_HUSK_CATEGORY;
	pObj->number = ITEM_CLASS(pVehicle);
	army = pObj->owner = ITEM_ARMY(pVehicle);
	pObj->attribute = ARMY_HUSK;
	pObj->triggers |= TEMPORARY_OBJECT;
	pObj->common.facing = pVehicle->pAnimation->facing;

	pObj->cell.pSprite = pVehicle->pAnimation->pSprite;
	pObj->cell.world_pos = pVehicle->pAnimation->world_pos;
	pObj->cell.trans_table = pVehicle->pAnimation->trans_table;
	pObj->layer = OL_GROUNDLAYER;
	pObj->cell.order = 2600;

	pObj->common.nMaxStrength = pObj->common.nStrength = 
		pVehicle->common.nMaxStrength >> 2;
	pObj->elevation = 4;
	pObj->visibility = 3;
	pObj->movement = 16;

	ItemSetUID( (ITEM *)pObj, army, pObj->attribute, pObj->category, DynamicID[army]++ );
    ItemSetLocation( (ITEM *)pObj, &(pObj->cell.world_pos));
    ItemSetOldLocation( (ITEM*)pObj );

	CopyMemory( &(pHusk->vehicle_mask), &(pVehicle->mask), sizeof(VEHICLE_MASK) );

	pObj->cell.flags = ANIM_FLAG_ACTIVE | ANIM_FLAG_CELL;
	AnimCellSetOwner( &(pObj->cell), pObj );	

	CreateDispXObject( pObj->cell.pSprite->srect.right,
						pObj->cell.pSprite->srect.bottom,
						&(pObj->cell), pObj->layer );

	MakeSmokePlume( pObj->cell.world_pos, pObj->common.nUniqueID );
	TRACE(" %x\n", pObj->common.nUniqueID  );
}

void DestroyVehicleHusk( THusk *pHusk )
{
	OBJECTSTRUCT *pObj;

	if( !pHusk )
		return;
	TRACE("Destroying Husk %x\n",ITEM_UID(pHusk));
	GenerateExplodingVehicle( pHusk->object.number, pHusk->object.cell.world_pos, 
		pHusk->object.cell.trans_table, pHusk->object.common.facing );
	pObj = &(pHusk->object);
	pObj->cell.flags &= ~ANIM_FLAG_ACTIVE;
	MoveDispXObject( &(pObj->cell), TRUE);
	SubtractMaskFromVehicleLayer(&(pHusk->vehicle_mask));
}


void CleanUpDeadHusks( void )
{
	int i;

	i = 0;
	while( i < HuskList.count )
	{
		if( !(HuskList.husks[i]->object.cell.flags & ANIM_FLAG_ACTIVE) )
		{
			DestroyDispXObject( &(HuskList.husks[i]->object.cell) );
			free( HuskList.husks[i] );
			if( i < HuskList.count-1 )			// shift everything after i up one
			{
				MoveMemory( HuskList.husks + i, HuskList.husks + i + 1, 
							(HuskList.count - i - 1) * sizeof(THusk *) );
			}
			HuskList.count--;
		}
		else
			i++;
	}
}


void FreeVehicleHusks( void )
{
	int i;

	for( i = HuskList.count-1; i >= 0; i-- )
	{
		AnimDelete( (ANIM *)(&(HuskList.husks[i]->object.cell)) );
		free( HuskList.husks[i] );
	}
	free( HuskList.husks );
	HuskList.count = 0;
	HuskList.bufsize = 0;
	HuskList.husks = NULL;
	for( i = 0; i < (int)ARMY_LAST_ARMY; i++ )
		DynamicID[i] = 0;
}


void HuskMessageReceive(ARMY_MESSAGE *pArmyMsg)
{
	OBJECT_MESSAGE *pMsg= (OBJECT_MESSAGE*)pArmyMsg;
	THusk *pHusk;

	pHusk = (THusk *)FindHuskItem( pMsg->nUniqueID );
	if( !pHusk )
		return;
	TRACE("Husk Message Receive found %x (%x) damagetodo %d\n",pMsg->nUniqueID,ITEM_UID(pHusk),pMsg->damagetodo );
    switch( pArmyMsg->msg_type )
	{
	case OBJMSG_DAMAGE:
		ItemDamage( (ITEM *)pHusk, pMsg->damagetodo, pMsg->damagetype, &pMsg->damagelocation, 0 );
		break;
	default:
		ASSERT( 0 );
	}
}


void HuskDamageMessageSend( THusk *pHusk, int damagetodo, int damagetype, SPOINT &damageloc )
{
	OBJECT_MESSAGE msg;

	msg.nSize = sizeof(OBJECT_MESSAGE);
	msg.nUniqueID = ITEM_UID(pHusk);
	msg.msg_type = OBJMSG_DAMAGE;

	msg.damagetodo = damagetodo;
	msg.damagetype = damagetype;
	msg.damagelocation = damageloc;
 	TRACE("Husk Message Send  %x  damagetodo %d\n",ITEM_UID(pHusk),msg.damagetodo);

	ArmyMessageSend((ARMY_MESSAGE *) &msg);
}
