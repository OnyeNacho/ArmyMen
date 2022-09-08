//========================================================================
//	FILE:			$Workfile: Sprite.h $
//
//	DESCRIPTION:	Sprite defines, structures, and prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, June 18, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Sprite.h 20    3/06/98 2:53p Phu $
//
//=========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//=========================================================================
//  History
//
//  $Log: /ArmyMen/src/Sprite.h $
//  
//  20    3/06/98 2:53p Phu
//  library load as default,  faster animation loading
//  
//  19    2/24/98 4:15p Phu
//  dynamic sprite release for ODF sprites
//  
//  18    2/06/98 3:56p Phu
//  real collision using the bmp for vehicles/units
//  better damage control on vehicles
//  
//  17    1/13/98 12:20p Phu
//  added SP_USESELFRECT for animations
//  
//  16    12/09/97 12:12p Phu
//  
//  15    12/04/97 6:48p Phu
//  add scarring, improved palette shifting, shadow-only sprites
//  
//  14    11/19/97 3:52p Awerner
//  Sprite sharing enabled
//  
//  13    11/18/97 3:51p Nrobinso
//  add linkspot
//  
//  12    11/11/97 9:27p Nrobinso
//  collapse sprite flags into 1 8 bit value
//  
//  11    11/07/97 10:42a Aburgess
//  DisplaySpriteClippedFront() prototype
//  
//  10    11/03/97 9:58p Nrobinso
//  
//  9     10/10/97 12:43p Aburgess
//  added SpriteBox
//  
//  8     9/30/97 4:00p Phu
//  New display engine!
//  
//  6     8/19/97 4:09p Phu
//  Shadows attached to sprites
//  
//  5     8/08/97 12:17p Phu
//  RLE Optimizations
//  
//  4     7/23/97 7:25p Phu
//  Now handles RLE256 objects w/ regular masking for library load only
//  
//  3     7/23/97 5:11p Phu
//  Use new mask format/created masks when loading from library file
//  
//  2     7/23/97 12:54p Awerner
//  Added a function to center the hotspot of a sprite... it's being used
//  for the strategic map icons
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  26    5/12/97 11:01a Aburgess
//  prototype for loadspritefront
//  
//  25    3/28/97 3:12p Nrobinso
//  add maskRect;change pMaskSurface to pMask
//  
//  24    3/24/97 7:54a Nrobinso
//  include dd.h
//  
//  23    3/03/97 1:41p Nrobinso
//  added MakeSprite()
//  
//  22    1/27/97 12:42p Nrobinso
//  Change LoadSprite() to return a size; fix bug in displaying a clipped,
//  RLE sprite
//  
//  21    1/24/97 5:51p Nrobinso
//  pSurface become pGraphics and pMask becomes pMaskSurface in sprite
//  struct; Load RLE & normal sprites with the same mechanism
//  
//  20    1/23/97 5:31p Nrobinso
//  Add RLE Sprites, translated and not
//  
//  19    1/21/97 6:40p Nrobinso
//  Added color translation of sprites
//  
//  18    1/15/97 9:48p Nrobinso
//  Add direct copied bitmap load
//  
//  17    10/07/96 1:12p Nrobinso
//  add transparaent color and mask to sprite structure
//  
//  16    7/30/96 4:04p Aburgess
//  added prototype for DisplaySpriteClipped
//  
//  15    7/24/96 6:19p Nrobins
//  moved sprite flags to dd.h; replaced specific transparency flag with a
//  general flags
//  
//  14    7/24/96 12:37p Nrobins
//  move transparency flag to LoadSprite instead of DisplaySprite
//  
//  11    6/26/96 11:24a Aburgess
//  converted CELL to use a pointer to a sprite
// 
//  $Nokeywords:$
///========================================================================

#ifndef __SPRITE_H__
#define __SPRITE_H__

#ifndef __DD_H__
#include "dd.h"
#endif

//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================

#define SPRITEFILENAMEMAXLENGTH 32

typedef struct
{
	char filename[SPRITEFILENAMEMAXLENGTH];
	LOADBITMAP lbitmap;
	int refcount;
	int size;
	void *pShadow;
	BYTE *pMask;
	RECT maskRect;
	char hasrect;
	LONG origFlags;
} SHAREDBITMAP;



enum ESpriteType {
	SPRITE_TYPE_DRLE,
	SPRITE_TYPE_WRLE,
	SPRITE_TYPE_TRLE,
	SPRITE_TYPE_SRLE,
	SPRITE_TYPE_RLE,
	SPRITE_TYPE_BMP
};


#define SP_OPAQUE			BM_OPAQUE
#define SP_RLE				BM_RLE
#define SP_DRLE				BM_DRLE
#define SP_WRLE				BM_WRLE
#define SP_TRLE				BM_TRLE
#define SP_SRLE				BM_SRLE
#define SP_MASKRECT			0x20
#define SP_PRIMEMASK		0x40
#define SP_USESELFRECT      0x80
#define SP_USEBMPASMASK     0x100

typedef struct Sprite {
	void		*pGraphic;
	BYTE		*pMask;
	RECT		maskRect;
	RECT		srect;
	SPOINT		hotspot;
	SPOINT		linkspot;
	void		*pShadow;
	BYTE		*trans_table;
	BYTE		xpc;
	FLAG		sprite_flags;
	BYTE		sprite_type;

	SHAREDBITMAP *pSharedBitmap;

	int			ODFKey;

//	ESpriteType sprite_type;

//	FLAG		opaque;
//	FLAG		RLE;
//	FLAG		useMaskRect;
//	FLAG		primeMask;
//	FLAG		DRLE;
//	FLAG		WRLE;
//	FLAG		TRLE;
} SPRITE, *PSPRITE;

typedef struct	Cell {
	SPRITE*		pSprite;
	union	{
		SPOINT		pos;		// world position
		struct { 
			SHORT x; 
			SHORT y;
		};
	};
} CELL, *PCELL;



//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================

//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================
BOOL	spriteInit( void );
void	spriteExit( void );

void CenterSpriteHotSpot(SPRITE *pSprite);
DWORD	LoadSprite( PSPRITE pSprite, char *name, LONG flags );
DWORD LoadSpritePlusMaskAndShadow( PSPRITE pSprite, char *name, LONG flags );
void	DisplaySprite( PSPRITE pSprite, DWORD x, DWORD y );
void	DisplaySpriteFront( PSPRITE pSprite, DWORD x, DWORD y );
void	DisplaySpriteClipped( PSPRITE pSprite, DWORD x, DWORD y );
void	DisplaySpriteClippedFront( PSPRITE pSprite, DWORD x, DWORD y );
void	FreeSprite( PSPRITE pSprite );
DWORD	MakeSprite( PSPRITE pSprite,  BITMAPINFO_256 *pbmpInfo, BYTE *pBitCopy, LOADBITMAP *plbitmap, BYTE *trans_table);
BOOL	SpriteBox( PSPRITE pSprite, SBOX* pBox );


//#define LoadSprite(pSprite,name,flags) LoadSpriteA(pSprite,name,flags,NULL)
//#define LoadSpriteAndSecondary(pSprite,name,flags,pSpot) LoadSpriteA(pSprite,name,flags,pSpot)

#endif		// __SPRITE_H__

//=========================================================================
//								EOF
//=========================================================================
