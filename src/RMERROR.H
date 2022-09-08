/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: RMERROR.H $
//
//	DESCRIPTION:	Error reporting code for DirectX
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, May 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/RMERROR.H 3     12/09/97 12:12p Phu $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/RMERROR.H $
//  
//  3     12/09/97 12:12p Phu
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  5     96-12-04 13:09 Ereich
//  Changed __ERROR_H__ #define to __RMERROR_H__ to match the file name
//  because I added Error.h file and I wanted it to use __ERROR_H__.
//  
//  4     9/09/96 7:09p Aburgess
//  Add DirectInput errors
// 
// 3     6/25/96 9:54p Nrobins
// added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef __RMERROR_H__
#define __RMERROR_H__

char *DDErrorToString(HRESULT error);
char *DSErrorToString(HRESULT error);
char *DFErrorToString(HRESULT error);
char *DIErrorToString(HRESULT error);

#endif // __RMERROR_H__

