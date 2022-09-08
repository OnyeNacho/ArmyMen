/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: TILE.H $
//
//	DESCRIPTION:	the tile structure interface
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, May 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/TILE.H 3     12/09/97 12:12p Phu $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/TILE.H $
//  
//  3     12/09/97 12:12p Phu
//  
//  1     7/03/97 5:19p Nrobinso
//  
//  4     9/10/96 1:00p Aburgess
//  move commonly used but infrequently changed header files to stdafx.h
//  (precompiled header)
//  
//  3     7/31/96 9:15p Nrobins
//  added max_tiles to the tile struct
// 
// 2     6/25/96 9:54p Nrobins
// added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __TILE_H__
#define __TILE_H__

/////////////////////////////////////////////////////////////////////////////
//#define MAX_TILESWIDE 256

#define LPDDSURFACE LPDIRECTDRAWSURFACE

typedef struct	{
	long width;
	long height;
	long max_tiles;
	LPDDSURFACE tile_data;
} TileSet;

extern TileSet the_tiles;

#endif
