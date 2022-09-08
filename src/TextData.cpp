/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: TextData.cpp $
//
//	DESCRIPTION:	Localizable text data
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Sunday, July 27, 1997
//
//	REVISION:		$Header: /ArmyMen/src/TextData.cpp 23    4/02/98 3:35p Phu $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/TextData.cpp $
//  
//  23    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  22    2/19/98 11:54a Nrobinso
//  add new unit/trooper types
//  
//  21    1/29/98 5:50p Bwilcox
//  unit names system changed
//  
//  20    1/29/98 3:16p Nrobinso
//  separate miner and sweeper
//  
//  19    1/12/98 1:50p Phu
//  fixed directory names to not have spaces
//  
//  18    12/09/97 12:12p Phu
//  
//  17    11/16/97 5:31p Nrobinso
//  army_explosive becomes army_explosive_weapon; the MINE object category
//  became the EXPLOSIVES category
//  
//  16    11/11/97 4:52p Phu
//  Guard Towers
//  
//  15    11/05/97 10:38a Nrobinso
//  clear out engineer strings
//  
//  14    10/30/97 10:43a Phu
//  add mine sweeper weapon
//  
//  13    10/08/97 3:44p Nrobinso
//  add new weapons
//  
//  11    8/12/97 3:51p Nrobinso
//  added sarge gun
//  
//  10    7/30/97 5:15p Aburgess
//  simplified VehicleName call
//  
//  9     7/29/97 11:11p Bwilcox
//  OBJ_DATA becomes ITEM,
//  associated stuff gets renamed ITEM or item or pItem
//  
//  8     7/29/97 10:54a Nrobinso
//  switch from OBJECT* to OBJ_DATA*
//  
//  7     7/28/97 4:39p Aburgess
//  gave it knowledge of USA.h
//  
//  6     7/28/97 2:56p Nrobinso
//  add Sarge to named objects; make TraceObjects only exist in debug mode
//  
//  5     7/27/97 4:37p Nrobinso
//  Commander becomes Sarge
//  
//  4     7/27/97 12:37p Aburgess
//  changed 2nd parameter of ObjectName to be one of LONG SHORT or TARGET
//  
//  3     7/27/97 11:56a Nrobinso
//  added TraceObject
//  
//  2     7/27/97 11:44a Nrobinso
//  add an ObjectTypeName()
//  
//  1     7/27/97 11:09a Nrobinso
//  being built
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Header files
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "army.h"
#include "aiaccess.h"
#include "trooper.h"
#include "USA.h"

/////////////////////////////////////////////////////////////////////////////
// Data files
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Data Types
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Local Data
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Code
/////////////////////////////////////////////////////////////////////////////

///========================================================================
//	Function:		VehicleName()
//
//	Description:
//		return the string equivalent for a vehicle type.
//
//	Input:			eVehicle	vehicle type
//
//	Ouput:			pName		string equivalent for the vehicle type
//
///========================================================================

char*	VehicleName( int eVehicle )
{
	char*	pName;
	
	pName = MsgVehicleNames[ eVehicle ].pString;

	return( pName );
}

///========================================================================
//	Function:		UnitTypeName()
//
//	Description:
//		return the string equivalent for a Unit type.
//
//	Input:			eUnit		unit type
//
//	Ouput:			pName		string equivalent for the unit type
//
///========================================================================

char*	UnitTypeName( int eUnit )
{
	static char *UnitNames[]=
	{   "Rifle Unit",
		"Grenade Unit",
		"Flamer Unit",
		"Bazooka Unit",
		"",
		"Mortar Unit",
		"Miner Unit",
		"Special Unit",
		"None"
	};

	if (eUnit < ARMY_LAST_UNIT)	{
		return (UnitNames[eUnit]);
	}
	else
		return (UnitNames[ARMY_LAST_UNIT]);
}


///========================================================================
//	Function:		TrooperName()
//
//	Description:
//		return the string equivalent for a trooper type.
//
//	Input:			eTrooper		trooper type
//
//	Ouput:			pName			string equivalent for the trooper type
//
///========================================================================

char*	TrooperName( int eTrooper )
{
	static char *TrooperNames[]=
	{   "RifleMen",
		"GrenadeMen",
		"FlameMen",
		"BazookaMen",
		"SweeperMen",
		"MortarMen",
		"MinerMen",
		"SpecialMen",
		"NoTrooper"
	};

	if (eTrooper < ARMY_LAST_TROOPER)	{
		return (TrooperNames[eTrooper]);
	}
	else
		return (TrooperNames[ARMY_LAST_TROOPER]);
}

///========================================================================
//	Function:		WeaponName()
//
//	Description:
//		return the string equivalent for a weapon type.
//
//	Input:			eWeapon			weapon type
//
//	Ouput:			pWeaponString	string equivalent for the weapon type
//
///========================================================================

char*	WeaponName( int	eWeapon )
{
	char*	pName;
	
	switch( eWeapon )
	{
	case ARMY_LIGHT_MACHINE_GUN:
		pName = "Light Machine Gun";
		break;
	case ARMY_MEDIUM_MACHINE_GUN:
		pName = "Medium Machine Gun";
		break;
	case ARMY_HEAVY_MACHINE_GUN:
		pName = "Heavy Machine Gun";
		break;
	case ARMY_FLAME_THROWER:
		pName = "Flame Thrower";
		break;
	case ARMY_GRENADE:
		pName = "Grenade";
		break;
	case ARMY_BAZOOKA:
		pName = "Bazooka";
		break;
	case ARMY_MORTAR:
		pName = "Mortar";
		break;
	case ARMY_LARGE_CANNON:
		pName = "Large Cannon";
		break;
	case ARMY_RIFLE:
		pName = "Rifle";
		break;
	case ARMY_AUTORIFLE:
		pName = "Auto Rifle";
		break;
	case ARMY_SWEEPER:
		pName = "Mine Sweeper";
		break;
	case ARMY_DETONATOR:
		pName = "Detonator";
		break;
	case ARMY_EXPLOSIVE_WEAPON:
		pName = "Explosive";
		break;
	case ARMY_MINE:
		pName = "Mine";
		break;
	case ARMY_GUARD_TOWER_RIFLE:
		pName = "Tower Rifle";
		break;
	default:
		pName = "No Weapon";
		break;
	}

	return( pName );
}

char *obj_names[] = {	
	"Rock",
	"Bush",
	"Tree",
	"Big Tree",
	"Fallen Tree",
	"Fence",
	"Wall",
	"Bridge",
	"Foot Bridge",
	"Explosive",
	"Gun Turret",
	"AA Gun",
	"Base",
	"Auxbase",
	"Air Strip",
	"Heli Pad",
	"Prison Camp",
	"Building",
	"PillBox",
	"PowerPlant",
	"FenceGate",
	"WallGate",
	"RadarBuilding",
	"Miscellaneous",
	"Overpass",
	"Special Item",
};

char* ItemName(ITEM *pItem)	{
	if (pItem)	{
		switch(ITEM_TYPE(pItem))
		{
			case ARMY_NULL_OBJ:
				return "Null Item";
			case ARMY_VEHICLE:
				return VehicleName(ITEM_CLASS(pItem));
			case ARMY_SARGE:
				return "Sarge";
			case ARMY_TROOPER:
				return TrooperName(ITEM_CLASS(pItem));
			case ARMY_UNIT:
					return AiUnitShortName((UNIT*) pItem );
			case ARMY_ASSET:
			case ARMY_STRUCTURE:
			case ARMY_OBSTACLE:
				return obj_names[ITEM_CLASS(pItem)];
			default:
				return "Unknown Item Type";
		}
	}

	return "No Item";
}
