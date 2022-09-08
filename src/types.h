//========================================================================
//	FILE:			$Workfile: types.h $
//
//	DESCRIPTION:	Global variables.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, June 18, 1996
//
//	REVISION:		$Header: /ArmyMen/src/types.h 17    98/04/02 16:15 Dmaynard $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//=========================================================================
//  HISTORY
//
//  $Log: /ArmyMen/src/types.h $
//  
//  17    98/04/02 16:15 Dmaynard
//  change ipoint back
//  
//  16    4/02/98 3:07p Phu
//  typecast to avoid warnings
//  
//  15    4/02/98 12:03p Bwilcox
//  ipoint_x and y cast to int 
//  
//  14    2/06/98 3:56p Phu
//  real collision using the bmp for vehicles/units
//  better damage control on vehicles
//  
//  13    12/24/97 5:22p Bwilcox
//  the item location field and the epoint datatype are now gone
//  
//  12    12/09/97 12:12p Phu
//  
//  10    9/23/97 10:02p Bwilcox
//  ipoint changed to unsigned long
//  
//  9     9/10/97 5:47p Bwilcox
//  validate maps dont go bad on deployed units
//  
//  8     9/10/97 2:44p Bwilcox
//  
//  7     9/10/97 1:32p Bwilcox
//  fixed IPOINT use of width instead of height for Y values
//  
//  6     8/22/97 2:08p Awerner
//  The vehicle movement now uses a better algorithm to
//  check for intersection with untrafficable regions
//  
//  5     8/07/97 11:27p Nrobinso
//  damage cleanup
//  
//  4     7/28/97 11:11p Nrobinso
//  get rid of x_ and y_limit and compress macros
//  
//  3     7/25/97 9:14a Nrobinso
//  add more macros fro dealing with map points as SPOINTs
//  
//  2     7/11/97 5:02p Bwilcox
//  moved ipoint defns from newdoor.h to types.h
//  
//  1     7/03/97 5:19p Nrobinso
//  
//  7     3/19/97 5:07p Bwilcox
//  moved EPOINT definitions into types.h from aiaccess.h
//  
//  6     3/17/97 12:24p Nrobinso
//  cleanup BITMAPINFO_256 structure
//  
//  5     3/03/97 8:13a Nrobinso
//  BITMAPINFO_256
//  
//  4     1/21/97 6:46p Nrobinso
//  added the FLAG type (8 bit boolean)
//  
//  3     12/22/96 5:55p Nrobinso
//  added RETERROR in place of BOOL for return error conditions
//  
//  2     10/07/96 1:13p Nrobinso
//  add LOCAL definition
//  
//  1     9/10/96 12:55p Aburgess
//  additional basic data types
//  
//  $Nokeywords:$
//=========================================================================

#ifndef __TYPES_H__
#define __TYPES_H__

//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================

typedef int RETERROR;

typedef signed char SBYTE;
typedef unsigned char UBYTE;

typedef unsigned short FLAG;

typedef struct tagSPOINT { // pt 
    SHORT x; 
    SHORT y; 
} SPOINT;

extern	unsigned short int			map_width;
extern	unsigned short int			map_height;

#define IPOINT unsigned long		// direct array index notation
#define IPOINT_X(i) ((int)(i % map_width))
#define IPOINT_Y(i) ((int)(i / map_width))
#define INDEX_ENCODED_Y(y) (((unsigned)y) * (unsigned) map_width)
#define INDEX(x,y) (INDEX_ENCODED_Y(y) + (unsigned)(x)) // tile coord units
#define ENCODE_IPOINT(x,y) (INDEX(TILEP(x),TILEP(y))) // world coord given
#define IPOINT_FROM_SPOINT(pt) (INDEX(TILEP(pt.x),TILEP(pt.y)))
#define IPOINT_FROM_PSPOINT(ppt) (INDEX(TILEP(ppt->x),TILEP(ppt->y)))
#define SPOINT_FROM_IPOINT_X(i) (WORLDP(IPOINT_X(i)))
#define SPOINT_FROM_IPOINT_Y(i) (WORLDP(IPOINT_Y(i)))

#define TILEP(n)		((n) >> 4)
#define WORLDP(n)		((n) << 4)

typedef struct tagBPOINT { // pt 
    SBYTE x; 
    SBYTE y; 
} BPOINT;

typedef struct tagBOX { // pt 
	union	{
		POINT	point;
		struct { 
			LONG x; 
			LONG y;
		};
	};
	union	{
		SIZE	size;
		struct { 
			LONG cx; 
			LONG cy;
		};
	};
} BOX; 

typedef struct tagSBOX {
    SHORT x; 
    SHORT y; 
    SHORT cx;	// width
    SHORT cy;	// height
} SBOX;

typedef struct BITMAPINFO_256
{
  BITMAPINFOHEADER  bmiHeader;
  RGBQUAD           bmiColors[256];
} BITMAPINFO_256;

#ifdef _DEBUG
#define LOCAL
#else
#define LOCAL static
#endif

#endif		// __TYPES_H__

//=========================================================================
//								EOF
//=========================================================================
