/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: guid.c $
//
//	DESCRIPTION:	Defines the class behaviors for the application.
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Tuesday, Sept 10, 1996
//
//	REVISION:		$Header: /ArmyMen/src/guid.c 4     4/02/98 3:06p Phu $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/guid.c $
/*  */
/* 4     4/02/98 3:06p Phu */
/*  */
/* 3     12/09/97 12:12p Phu */
/*  */
/* 1     7/03/97 5:18p Nrobinso */
/*  */
/* 2     96-11-12 5:17 Ereich */
/* Added ARMYMEN_GUID to the project. */
/*  */
/* 1     9/10/96 12:56p Aburgess */
/* one time inclusion of DirectX headers to define GUIDs */
//
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include <cderr.h>

// the following 2 .h files must be included once only in app, 
// followed by ddraw.h & dinput.h

#include <objbase.h>
#include <initguid.h>	// needed for the the ddraw interface 2 GUID

#include <dinput.h>
#include <ddraw.h>

// {F5117E8C-36FB-11d0-A945-00805F5AEA59}
DEFINE_GUID(ARMYMEN_GUID, 
0xf5117e8c, 0x36fb, 0x11d0, 0xa9, 0x45, 0x0, 0x80, 0x5f, 0x5a, 0xea, 0x59);
