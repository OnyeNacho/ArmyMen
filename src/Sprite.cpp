//========================================================================
//	FILE:			$Workfile: Sprite.cpp $
//
//	DESCRIPTION:	Sprite processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, June 18, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Sprite.cpp 51    4/17/98 1:54p Phu $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	spriteInit()
//		Initialize the Sprite processing.
//	spriteExit()
//		Terminate the Sprite processor.
//	LoadSprite()
//		Load up a sprite.
//	DisplaySprite()
//		Display up a sprite on the screen.
//	FreeSprite()
//		Release or free up a sprite.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Sprite.cpp $
//  
//  51    4/17/98 1:54p Phu
//  fixed a trace message
//  
//  49    4/02/98 3:35p Phu
//  typecast to avoid warnings
//  
//  48    3/27/98 1:49p Phu
//  survive ALT_TAB dammit
//  
//  47    3/17/98 5:18p Nrobinso
//  don't assert if no sprite
//  
//  46    3/12/98 9:54a Aburgess
//  corrected function header description
//  
//  45    3/11/98 10:04p Nrobinso
//  fix sprite clipped to front so it works windowed
//  
//  44    3/11/98 1:49p Phu
//  cursor stuff
//  
//  43    3/07/98 11:52p Nrobinso
//  move .h file to stdafx
//  
//  42    3/06/98 2:53p Phu
//  library load as default,  faster animation loading
//  
//  41    3/01/98 11:03p Nrobinso
//  get rid of pop up error if lose front sprite surface
//  
//  40    2/11/98 1:27p Nrobinso
//  fix front buffer sprite blt wasn't transparent
//  
//  39    1/23/98 11:11a Phu
//  fix displaysprite clipped
//  
//  38    1/09/98 3:44p Nrobinso
//  for release mode ifdef debug a variable to prevent warning error
//  
//  37    12/16/97 12:21p Phu
//  
//  36    12/09/97 12:12p Phu
//  
//  35    12/08/97 9:44a Nrobinso
//  improve error msg
//  
//  34    12/05/97 12:02p Bwilcox
//  improving error traces again.
//  
//  33    12/04/97 6:48p Phu
//  add scarring, improved palette shifting, shadow-only sprites
//  
//  32    12/02/97 10:35a Awerner
//  Fixed a hotspot bug (that was messing up the floating bridge)
//  
//  31    12/01/97 6:23p Nrobinso
//  expand hotspot range
//  
//  30    11/19/97 5:49p Awerner
//  Fixed mask/rect bug
//  
//  29    11/19/97 3:52p Awerner
//  Sprite sharing enabled
//  
//  28    11/18/97 3:49p Nrobinso
//  add a linkspot (secondary hotspot) to sprite
//  
//  27    11/14/97 10:39a Nrobinso
//  remove get path, uneeded
//  
//  26    11/11/97 9:27p Nrobinso
//  collapse sprite flags into 1 8 bit value
//  
//  25    11/07/97 10:33a Aburgess
//  SpriteDisplayClippedFront() added
//  
//  24    11/03/97 9:47p Nrobinso
//  return size from MakeSprite
//  
//  23    10/27/97 11:07a Aburgess
//  added debug info
//  
//  22    10/15/97 9:44a Phu
//  pickup stuff
//  
//  21    10/10/97 12:51p Nrobinso
//  qadd transparency to DrawSpriteFront
//  
//  20    10/10/97 12:43p Aburgess
//  added SpriteBox
//  
//  19    9/30/97 4:00p Phu
//  New display engine!
//  
//  17    8/22/97 2:08p Awerner
//  The vehicle movement now uses a better algorithm to
//  check for intersection with untrafficable regions
//  
//  16    8/21/97 10:06a Phu
//  Shadow Blitting
//  
//  15    8/20/97 9:30a Phu
//  Shade function stubs
//  
//  14    8/20/97 8:35a Phu
//  Load & Attach shadow files.  Draw shadows in black.
//  
//  13    8/19/97 4:09p Phu
//  Shadows attached to sprites
//  
//  12    8/08/97 5:47p Phu
//  Fix for non translated TRLEs
//  
//  11    8/08/97 12:17p Phu
//  RLE Optimizations
//  
//  10    7/30/97 7:06p Phu
//  WORD vs DWORD line table RLE functions
//  
//  9     7/25/97 2:34p Phu
//  Fix to display sprite clipped
//  
//  8     7/24/97 3:32p Phu
//  Lock/Unlock during display area update only when necessary
//  
//  7     7/23/97 7:25p Phu
//  Now handles RLE256 objects w/ regular masking for library load only
//  
//  6     7/23/97 5:11p Phu
//  Use new mask format/created masks when loading from library file
//  
//  5     7/23/97 12:54p Awerner
//  Added a function to center the hotspot of a sprite... it's being used
//  for the strategic map icons
//  
//  4     7/23/97 11:26a Phu
//  Load objects from library file
//  
//  3     7/14/97 12:50p Phu
//  Fix memory allocation error
//  
//  2     7/11/97 6:26p Phu
//  Fixed error/warning for non-Debug version (use of undeclared variable)
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  38    6/05/97 5:28p Nrobinso
//  fix DisplaSpriteFront()
//  
//  37    5/13/97 3:50p Nrobinso
//  check load flags and set others if error conditions occur
//  
//  36    5/13/97 8:40a Nrobinso
//  zero sprite struct on load
//  
//  35    5/12/97 11:00a Aburgess
//  new DisplaySpriteFront for loading into front buffer
//  
//  34    5/02/97 4:33p Nrobinso
//  remove rroneous comments
//  
//  33    4/29/97 1:45p Nrobinso
//  change usage of SPRITE_DEBUG
//  
//  32    4/25/97 8:25a Aburgess
//  added SPRITE_DEBUG ifndef's
//  
//  31    4/01/97 9:09p Nrobinso
//  call ClipRectToGameWindow in DisplaySpriteClipped, so we can clip to
//  different screen areas
//  
//  30    3/28/97 3:12p Nrobinso
//  add maskRect;change pMaskSurface to pMask
//  
//  29    3/12/97 3:56p Nrobinso
//  DDMakeBitmapFromMemory() --> MakeBitmap()
//  
//  28    3/03/97 1:38p Nrobinso
//  make a sprite from a pre-loaded graphic
//  
//  27    2/17/97 4:46p Bwilcox
//  fixing trace which failed to compile in release mode
//  
//  26    1/27/97 4:54p Nrobinso
//  HaveDisplaySprite call unclipped versions of the RLE display routines
//  
//  25    1/27/97 12:42p Nrobinso
//  Change LoadSprite() to return a size; fix bug in displaying a clipped,
//  RLE sprite
//  
//  24    1/24/97 5:54p Nrobinso
//  pSurface become pGraphics and pMask becomes pMaskSurface in sprite
//  struct; Load RLE & normal sprites with the same mechanism
//  
//  23    97-01-24 14:13 Ereich
//  
//  22    1/23/97 5:31p Nrobinso
//  Add RLE Sprites, translated and not
//  
//  21    1/22/97 9:27a Nrobinso
//  replace memset(0) wirh ZeroMemory()
//  
//  20    1/21/97 6:40p Nrobinso
//  Added color translation of sprites
//  
//  19    1/15/97 9:48p Nrobinso
//  Add direct copied bitmap load
//  
//  18    12/10/96 5:35p Nrobinso
//  #ifdef _DEBUG's added around debugging info
//  
//  17    96-10-08 9:41 Ereich
//  + Fixed file loading problems for the map room and Main base .BMP
//  files.
//  
//  16    10/07/96 1:08p Nrobinso
//  maintain transprent color in sprite structure
//  
//  15    8/09/96 4:48p Nrobins
//  Fix hotspot calculation
//  
//  14    7/30/96 4:03p Aburgess
//  added DisplaySpriteClipped and checked for NULL surfaces
//  
//  13    7/26/96 9:26p Nrobins
//  Changed DDLoadBitmap() call
//  
//  12    7/24/96 6:20p Nrobins
//  replaced the specific transparency flag with a general flags passed to
//  LoadSprite()
//  
//  11    7/24/96 12:37p Nrobins
//  move transparency flag to LoadSprite instead of DisplaySprite; check
//  for logical values of hotspots and clear if out of range
//  
//  8     7/08/96 3:32p Nrobins
//  updated LoadDDBitmap() calls to new interface
//  
//  7     6/26/96 10:44a Aburgess
//  added new Source Control headers
// 
//  $Nokeywords:$
///========================================================================

// Includes
#include "stdafx.h"

#include "Sprite.h"
#include "direct.h"
#include "fileio.h"
#include "miscfile.h"
#include "army.h"


#ifdef _OBJECT_DEBUG
extern char *obj_category_dirs[];
extern int OD_Category;
extern int OD_Number;
extern int OD_Width;
extern int OD_Height;
extern int OD_Size;
extern int OD_nAnimFrames;
extern int OD_nDamageFrames;
extern int OD_MaskSize;
extern int OD_ShadowSize;
extern int OD_Rect;
extern int OD_SharedBitmap;
extern int OD_Hotspot;
extern int OD_Linkspot;
extern int OD_FrameNumber;
extern int OD_SpriteType;
#endif


///========================================================================
//							GLOBAL VARIABLES
///========================================================================
extern BYTE * SCRPTR;
extern DWORD  LPITCH;

#define NUMSHAREDBITMAPS 256

SHAREDBITMAP sharedBitmaps[NUMSHAREDBITMAPS];


#define MAXHOTSPOTOFFSET 680

///========================================================================
//							LOCAL DEFINES
///========================================================================

///========================================================================
//							LOCAL VARIABLES
///========================================================================

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================

///========================================================================
//	Function:		spriteInit()
//
//	Description:
//		Initialize the Sprite processing.
//
//	Input:			none
//
//	Ouput:			error			FALSE if successful, TRUE otherwise
//
///========================================================================

BOOL	spriteInit( void )
{
	ZeroMemory(sharedBitmaps, sizeof(sharedBitmaps));
	return( FALSE );
}

///========================================================================
//	Function:		spriteExit()
//
//	Description:
//		Terminate the Sprite processor.
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void	spriteExit( void )
{
}
///========================================================================
//	Function:		CenterSpriteHotSpot()
//
//	Description:
//		Sets a sprite's hotspot so that it's centered
//
//	Input:			pSprite		pointer to a sprite
//
//	Ouput:			none
//
///========================================================================
void CenterSpriteHotSpot(SPRITE *pSprite)
{
	if (!pSprite)
		return;

	pSprite->hotspot.x=pSprite->srect.right/2;
	pSprite->hotspot.y=pSprite->srect.bottom/2;

}



int getSpriteSharedName(char *origname, char *newname)
{
	FILE *textfile;
	char tempfilename[SPRITEFILENAMEMAXLENGTH+10];
	int filesize;
	int i;

 	sprintf(tempfilename, "%s.txt", origname);

	textfile=fopen(tempfilename, "r");

	if (textfile==NULL)
	{
		return 0;
	}
	else
	{
		fseek(textfile, 0, 2);
		filesize=ftell(textfile);
		fseek(textfile, 0, 0);
		if (filesize>=SPRITEFILENAMEMAXLENGTH)
		{
			TRACE("ERROR in sprite sharing code... name in file %s is too long\n", tempfilename);
			return 0;
		}

		fread(newname, filesize, 1, textfile);
		for(i=0;i<(int)strlen(newname);i++)
			if (newname[i]==10 || newname[i]==13 || newname[i]<0)
				newname[i]=0;

		fclose(textfile);
		return 1;
	}
}


int BitmapLoadWithSharing(char *filename, LOADBITMAP **pplbitmap, LONG flags, SHAREDBITMAP **ppSharedBitmap)
{
	int i;

	//if this shared bitmap has already been loaded, pass back the lbitmap
	for (i=0;i<NUMSHAREDBITMAPS;i++)
		if (strcmp(filename, sharedBitmaps[i].filename)==0)
		{
			if (flags==sharedBitmaps[i].origFlags)
			{
				*pplbitmap=&sharedBitmaps[i].lbitmap;
				*ppSharedBitmap=&sharedBitmaps[i];
				sharedBitmaps[i].refcount++;
				return sharedBitmaps[i].size;
			}
			else
			{
				TRACE("ERROR: shared bitmap %s uses different flags than the original load\n", filename);
				return 0;
			}
		}

	//find an unused shared bitmaps
	for (i=0;i<NUMSHAREDBITMAPS;i++)
		if (sharedBitmaps[i].filename[0]==0)
		{
			ZeroMemory(&sharedBitmaps[i], sizeof(sharedBitmaps[i]));
			sharedBitmaps[i].lbitmap.flags=sharedBitmaps[i].origFlags=flags;
			sharedBitmaps[i].size=BitmapLoad(filename, &sharedBitmaps[i].lbitmap);
			if (sharedBitmaps[i].size<=0)
			{
				ZeroMemory(&sharedBitmaps[i], sizeof(sharedBitmaps[i]));
				return 0;
			}
			sharedBitmaps[i].refcount=1;
			sprintf(sharedBitmaps[i].filename, "%s", filename);
			*pplbitmap=&sharedBitmaps[i].lbitmap;
			*ppSharedBitmap=&sharedBitmaps[i];
			return sharedBitmaps[i].size;
		}

	TRACE("ERROR: too many different shared bitmaps\n");
	return 0;
}


			




///========================================================================
//	Function:		LoadSprite()
//
//	Description:
//		Load up a sprite.
//
//	Input:			pSprite		pointer to a sprite
//					name		name identifier for a sprite.
//					flags.
//
//	Ouput:			size of sprite graphics data
//
///========================================================================

DWORD LoadSprite( PSPRITE pSprite, char *name, LONG flags )
{
	LOADBITMAP lbitmap;
	LOADBITMAP *plbitmap=&lbitmap;
	DWORD	size = 0;
	char actualfilename[SPRITEFILENAMEMAXLENGTH];

	ZeroMemory(pSprite, sizeof(SPRITE));

#ifdef _DEBUG
	// opaque RLE sprites are not allowed
	if ((flags & BM_RLE) && (flags & BM_OPAQUE))	{
		if (flags & BM_NOTRANSLATE)	{
			flags &= ~BM_OPAQUE;
			flags |= BM_FORCE_OPAQUE;
		}
		else	{
			TRACE("Opaque RLE sprites are not allowed\n");
			ASSERT(FALSE);
		}
	}
#endif

	//check to see if there is a shared bitmap file we should use
	if (getSpriteSharedName(name, actualfilename))
	{

		size = BitmapLoadWithSharing(actualfilename, &plbitmap, flags, &pSprite->pSharedBitmap);
		if (size <=0)
		{
			TRACE("Can't load shared bitmap: %s!\n", name);
			pSprite->pGraphic = NULL;
			goto exit;
		}
	}
	else
	{
		lbitmap.flags = flags;
		size = BitmapLoad(name, &lbitmap);
		if (size == 0)	
		{

#ifdef _DEBUG
            char path[200];
			TRACE("Can't load bitmap: %s\\%s!\n",_getcwd(path,200),name);
#endif

			pSprite->pGraphic = NULL;
			goto exit;
		}
	}



	pSprite->pGraphic = plbitmap->pGraphic;

	pSprite->xpc = (BYTE) plbitmap->xpc;

	pSprite->srect.left   = pSprite->srect.top = 0;
	pSprite->srect.right  = plbitmap->width;
	pSprite->srect.bottom = plbitmap->height;

	pSprite->hotspot.x = (SHORT) plbitmap->xppm & 0xFFFF;
	pSprite->hotspot.y = (SHORT) plbitmap->yppm & 0xFFFF;

	pSprite->linkspot.x = (SHORT) (plbitmap->xppm >> 16);
	pSprite->linkspot.y = (SHORT) (plbitmap->yppm >> 16);

	if ((pSprite->hotspot.x > MAXHOTSPOTOFFSET) || (pSprite->hotspot.x < -MAXHOTSPOTOFFSET))	{
		pSprite->hotspot.x = 0;
//		TRACE("Reset x hotspot for %s\n", name);
	}

	if ((pSprite->hotspot.y > MAXHOTSPOTOFFSET) || (pSprite->hotspot.y < -MAXHOTSPOTOFFSET))	{
		pSprite->hotspot.y = 0;
//		TRACE("Reset y hotspot for %s\n", name);
	}

	if ((pSprite->linkspot.x > MAXHOTSPOTOFFSET) || (pSprite->linkspot.x < -MAXHOTSPOTOFFSET))	{
		pSprite->linkspot.x = 0;
//		TRACE("Reset x linkspot for %s\n", name);
	}

	if ((pSprite->linkspot.y > MAXHOTSPOTOFFSET) || (pSprite->linkspot.y < -MAXHOTSPOTOFFSET))	{
		pSprite->linkspot.y = 0;
//		TRACE("Reset y linkspot for %s\n", name);
	}

	pSprite->sprite_flags |= ( flags & BM_OPAQUE );
	pSprite->sprite_flags |= ( flags & BM_RLE );
	pSprite->sprite_flags |= ( plbitmap->flags & BM_DRLE );
	pSprite->sprite_flags |= ( plbitmap->flags & BM_WRLE );
	pSprite->sprite_flags |= ( plbitmap->flags & BM_TRLE );
	pSprite->trans_table = NULL;

	if( pSprite->sprite_flags & SP_DRLE )
		pSprite->sprite_type = SPRITE_TYPE_DRLE;
	else if( pSprite->sprite_flags & SP_WRLE )
		pSprite->sprite_type = SPRITE_TYPE_WRLE;
	else if( pSprite->sprite_flags & SP_TRLE )
		pSprite->sprite_type = SPRITE_TYPE_TRLE;
	else if( pSprite->sprite_flags & SP_RLE )
		pSprite->sprite_type = SPRITE_TYPE_RLE;
	else
		pSprite->sprite_type = SPRITE_TYPE_BMP;

exit:
	return size;
}










//this function loads in a sprite, and also attempts to load its mask and 
//shadow (note that the filename it takes does _not_ include the .bmp extension
DWORD LoadSpritePlusMaskAndShadow( PSPRITE pSprite, char *name, LONG flags )
{
	LOADBITMAP lbitmap;
	LOADBITMAP *plbitmap=&lbitmap;
	DWORD	size = 0;
	char actualfilename[SPRITEFILENAMEMAXLENGTH];
	char actualbmpname[SPRITEFILENAMEMAXLENGTH];
	char bmpname[SPRITEFILENAMEMAXLENGTH];
	char shadowname[SPRITEFILENAMEMAXLENGTH*2];
	char maskname[SPRITEFILENAMEMAXLENGTH*2];
	char rectname[SPRITEFILENAMEMAXLENGTH*2];
	WIN32_FIND_DATA FindFileData;
	HANDLE hSearch;


#ifdef _OBJECT_DEBUG
	OD_Width = 0;
	OD_Height = 0;
	OD_Size = 0;
	OD_MaskSize = 0;
	OD_ShadowSize = 0;
	OD_Rect = 0;
	OD_SharedBitmap = 0;
	OD_Hotspot = 0;
	OD_Linkspot = 0;
	OD_SpriteType = 0;
#endif

	ZeroMemory(pSprite, sizeof(SPRITE));
	sprintf(bmpname, "%s.bmp", name);

#ifdef _DEBUG
	// opaque RLE sprites are not allowed
	if ((flags & BM_RLE) && (flags & BM_OPAQUE))	{
		if (flags & BM_NOTRANSLATE)	{
			flags &= ~BM_OPAQUE;
			flags |= BM_FORCE_OPAQUE;
		}
		else	{
			TRACE("Opaque RLE sprites are not allowed\n");
			ASSERT(FALSE);
		}
	}
#endif

	//check to see if there is an shared bitmap file we should use
	if (getSpriteSharedName(bmpname, actualfilename))
	{
		sprintf(actualbmpname, "%s.bmp", actualfilename);
		size = BitmapLoadWithSharing(actualbmpname, &plbitmap, flags, &pSprite->pSharedBitmap);
		if (size <=0)
		{
			TRACE("Can't load shared bitmap: %s!\n", actualbmpname);
			pSprite->pGraphic = NULL;
			goto exit;
		}
	}
	else
	{
		lbitmap.flags = flags;
		size = BitmapLoad(bmpname, &lbitmap);
		if (size == 0)	
		{
			TRACE("Can't load bitmap: %s!\n", bmpname);
			pSprite->pGraphic = NULL;
			goto exit;
		}
	}



	pSprite->pGraphic = plbitmap->pGraphic;

	pSprite->xpc = (BYTE) plbitmap->xpc;

	pSprite->srect.left   = pSprite->srect.top = 0;
	pSprite->srect.right  = plbitmap->width;
	pSprite->srect.bottom = plbitmap->height;

	pSprite->hotspot.x = (SHORT) plbitmap->xppm & 0xFFFF;
	pSprite->hotspot.y = (SHORT) plbitmap->yppm & 0xFFFF;

	pSprite->linkspot.x = (SHORT) (plbitmap->xppm >> 16);
	pSprite->linkspot.y = (SHORT) (plbitmap->yppm >> 16);

	if ((pSprite->hotspot.x > MAXHOTSPOTOFFSET) || (pSprite->hotspot.x < -MAXHOTSPOTOFFSET))	{
		pSprite->hotspot.x = 0;
//		TRACE("Reset x hotspot for %s\n", name);
	}

	if ((pSprite->hotspot.y > MAXHOTSPOTOFFSET) || (pSprite->hotspot.y < -MAXHOTSPOTOFFSET))	{
		pSprite->hotspot.y = 0;
//		TRACE("Reset y hotspot for %s\n", name);
	}

	if ((pSprite->linkspot.x > MAXHOTSPOTOFFSET) || (pSprite->linkspot.x < -MAXHOTSPOTOFFSET))	{
		pSprite->linkspot.x = 0;
//		TRACE("Reset x linkspot for %s\n", name);
	}

	if ((pSprite->linkspot.y > MAXHOTSPOTOFFSET) || (pSprite->linkspot.y < -MAXHOTSPOTOFFSET))	{
		pSprite->linkspot.y = 0;
//		TRACE("Reset y linkspot for %s\n", name);
	}

	pSprite->sprite_flags |= ( flags & BM_OPAQUE );
	pSprite->sprite_flags |= ( flags & BM_RLE );
	pSprite->sprite_flags |= ( plbitmap->flags & BM_DRLE );
	pSprite->sprite_flags |= ( plbitmap->flags & BM_WRLE );
	pSprite->sprite_flags |= ( plbitmap->flags & BM_TRLE );
	pSprite->trans_table = NULL;

	if( pSprite->sprite_flags & SP_DRLE )
		pSprite->sprite_type = SPRITE_TYPE_DRLE;
	else if( pSprite->sprite_flags & SP_WRLE )
		pSprite->sprite_type = SPRITE_TYPE_WRLE;
	else if( pSprite->sprite_flags & SP_TRLE )
		pSprite->sprite_type = SPRITE_TYPE_TRLE;
	else if( pSprite->sprite_flags & SP_RLE )
		pSprite->sprite_type = SPRITE_TYPE_RLE;
	else
		pSprite->sprite_type = SPRITE_TYPE_BMP;

#ifdef _OBJECT_DEBUG
	OD_Width = plbitmap->width;
	OD_Height = plbitmap->height;
	OD_Size = size;
	OD_SpriteType = pSprite->sprite_type == SPRITE_TYPE_DRLE;
	OD_Hotspot = (pSprite->hotspot.x != 0 && pSprite->hotspot.y != 0 );
	OD_Linkspot = (pSprite->linkspot.x != 0 && pSprite->linkspot.y != 0);
	OD_SharedBitmap = (pSprite->pSharedBitmap != NULL );
#endif

	if (pSprite->pSharedBitmap)
	{
		if (pSprite->pSharedBitmap->pShadow)
			pSprite->pShadow=pSprite->pSharedBitmap->pShadow;
		else
		{
			sprintf(shadowname, "%s.sha", actualfilename);

			hSearch = FindFirstFile(shadowname, &FindFileData);
			if (hSearch != INVALID_HANDLE_VALUE)	
			{
				LoadSpriteShadow(pSprite, shadowname);
				pSprite->pSharedBitmap->pShadow=pSprite->pShadow;
				FindClose(hSearch);
			}
		}
	}
	else
	{
		sprintf(shadowname, "%s.sha", name);
		hSearch = FindFirstFile(shadowname, &FindFileData);
		if (hSearch != INVALID_HANDLE_VALUE)	
		{
			LoadSpriteShadow(pSprite, shadowname);
			FindClose(hSearch);
		}
	}

	if (pSprite->pSharedBitmap)
	{
		if (pSprite->pSharedBitmap->pMask)
		{
			pSprite->pMask=pSprite->pSharedBitmap->pMask;
			pSprite->sprite_flags |= SP_PRIMEMASK;
		}
		else
		{
			sprintf(maskname, "masks\\%s.msk", actualfilename);

			hSearch = FindFirstFile(maskname, &FindFileData);
			if (hSearch != INVALID_HANDLE_VALUE)	
			{
				LoadSpriteMask(pSprite, maskname);
				pSprite->pSharedBitmap->pMask=pSprite->pMask;
				FindClose(hSearch);
			}
		}
	}
	else
	{
		sprintf(maskname, "masks\\%s.msk", name);
		hSearch = FindFirstFile(maskname, &FindFileData);
		if (hSearch != INVALID_HANDLE_VALUE)	
		{
			LoadSpriteMask(pSprite, maskname);
			FindClose(hSearch);
		}
	}

	if (pSprite->pSharedBitmap)
	{
		if (pSprite->pSharedBitmap->hasrect)
		{
			pSprite->maskRect=pSprite->pSharedBitmap->maskRect;
			pSprite->sprite_flags |= SP_MASKRECT;
		}
		else
		{
			sprintf(rectname, "Rects\\%s.rec", actualfilename);

			hSearch = FindFirstFile(rectname, &FindFileData);
			if (hSearch != INVALID_HANDLE_VALUE)	
			{
				LoadSpriteRect(pSprite, rectname);
				pSprite->pSharedBitmap->maskRect=pSprite->maskRect;
				pSprite->pSharedBitmap->hasrect=TRUE;
				FindClose(hSearch);
#ifdef _OBJECT_DEBUG
				OD_Rect = 1;
#endif
			}
		}
	}
	else
	{
		sprintf(rectname, "Rects\\%s.rec", name);
		hSearch = FindFirstFile(rectname, &FindFileData);
		if (hSearch != INVALID_HANDLE_VALUE)	
		{
			LoadSpriteRect(pSprite, rectname);
			FindClose(hSearch);
		}
	}

exit:
#ifdef _OBJECT_DEBUG
	char YNChar[2] = { 'N', 'Y' };
	TRACE( "%16s %3d %2d %2d %2d %6d %c %4d %4d %c %c %c %c\n",
		obj_category_dirs[OD_Category],
		OD_Number,
		OD_nAnimFrames,
		OD_nDamageFrames,
		OD_FrameNumber,
		OD_Size,
		(OD_SpriteType == 0 ? 'W' : 'D'),
		OD_MaskSize,
		OD_ShadowSize,
		YNChar[OD_Rect],
		YNChar[OD_SharedBitmap],
		YNChar[OD_Hotspot],
		YNChar[OD_Linkspot]
		);
#endif
	return size;
}


///========================================================================
//	Function:		MakeSprite()
//
//	Description:
//		Make a sprite from an already loaded bitmap
//
//	Input:			pSprite		pointer to a sprite
//					name		name identifier for a sprite.
//					flags.
//
//	Ouput:			size of sprite graphics data
//
///========================================================================

extern BYTE fixed_trans_table[];

DWORD MakeSprite( PSPRITE pSprite,  BITMAPINFO_256 *pbmpInfo, BYTE *pBitCopy, LOADBITMAP *plbitmap, BYTE *trans_table )
{
	DWORD size;

	ZeroMemory(pSprite, sizeof(SPRITE));

	if (size = MakeBitmap(pbmpInfo, pBitCopy, plbitmap, trans_table))	{
		pSprite->pGraphic = plbitmap->pGraphic;
		pSprite->pMask = NULL;
		pSprite->pShadow = NULL;

		pSprite->xpc = (BYTE) plbitmap->xpc;

		pSprite->srect.left   = pSprite->srect.top = 0;
		pSprite->srect.right  = plbitmap->width;
		pSprite->srect.bottom = plbitmap->height;

		pSprite->hotspot.x = (SHORT) plbitmap->xppm;
		pSprite->hotspot.y = (SHORT) plbitmap->yppm;

		if ((pSprite->hotspot.x > 680) || (pSprite->hotspot.x < -680))	{
			pSprite->hotspot.x = 0;
		}

		if ((pSprite->hotspot.y > 680) || (pSprite->hotspot.y < -680))	{
			pSprite->hotspot.y = 0;
		}

		pSprite->sprite_flags &= ~SP_MASKRECT;
		pSprite->sprite_flags |= ( plbitmap->flags & BM_OPAQUE );
		pSprite->sprite_flags |= ( plbitmap->flags & BM_RLE );
		pSprite->sprite_flags |= ( plbitmap->flags & BM_DRLE );
		pSprite->sprite_flags |= ( plbitmap->flags & BM_WRLE );
		pSprite->sprite_flags |= ( plbitmap->flags & BM_TRLE );
		pSprite->trans_table = NULL;

		if( pSprite->sprite_flags & SP_DRLE )
			pSprite->sprite_type = SPRITE_TYPE_DRLE;
		else if( pSprite->sprite_flags & SP_WRLE )
			pSprite->sprite_type = SPRITE_TYPE_WRLE;
		else if( pSprite->sprite_flags & SP_TRLE )
			pSprite->sprite_type = SPRITE_TYPE_TRLE;
		else if( pSprite->sprite_flags & SP_RLE )
			pSprite->sprite_type = SPRITE_TYPE_RLE;
		else
			pSprite->sprite_type = SPRITE_TYPE_BMP;

		return size;
	}
	else	{
		TRACE("ERROR: DDMakeBitmapFromMemory failed: [%s:%d]\n", __FILE__, __LINE__ );
		return 0;
	}
}


///========================================================================
//	Function:		DisplaySprite()
//
//	Description:
//		Display up a sprite on the screen.
//
//	Input:			pSprite			pointer to a sprite
//					x				screen x position
//					y				screen y position
//
//	Ouput:			none
//
///========================================================================

void	DisplaySprite( PSPRITE pSprite, DWORD x, DWORD y )
{
	HRESULT     ddrval;
	DWORD		flags;
	LONG		xPos;
	LONG		yPos;
 	LONG		height;
	DDSURFACEDESC	backbuffer_ddsd;
	BYTE *pDestStart;

	// make sure we have a valid sprite and surface
	if( !pSprite )
		return;

	if( pSprite->pGraphic == NULL )
		return;

	if (pSprite->sprite_flags & (SP_DRLE | SP_WRLE | SP_TRLE | SP_SRLE) )
	{
		TRACE( "Tried to display RLE256 in DisplaySprite()\n ");
		return;
	}

	xPos = x - (DWORD)(pSprite->hotspot.x);
	yPos = y - (DWORD)(pSprite->hotspot.y);

	if (pSprite->sprite_flags & SP_RLE)	{
		height = pSprite->srect.bottom - pSprite->srect.top;
		backbuffer_ddsd.dwSize = sizeof(DDSURFACEDESC);
		if ((ddrval = pBackBuffer->Lock(NULL, &backbuffer_ddsd, DDLOCK_WAIT, NULL)) == DD_OK)	{
			pDestStart = (BYTE *)backbuffer_ddsd.lpSurface + yPos*backbuffer_ddsd.lPitch + xPos;
			if (pSprite->trans_table)
				RLETranslateBlt(	pDestStart, backbuffer_ddsd.lPitch,
					(BYTE *)pSprite->pGraphic, height, pSprite->trans_table );
			else
				RLEFastBlt(	pDestStart, backbuffer_ddsd.lPitch,
					(BYTE *)pSprite->pGraphic, height );

			pBackBuffer->Unlock(backbuffer_ddsd.lpSurface);
		}
		else TRACE("Error on RLE pBackBuffer Lock in DisplaySprite()");
	}
	else	{
		// set up transparency flags
		flags = (DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
		if ( pSprite->sprite_flags & SP_OPAQUE )
			flags = DDBLTFAST_WAIT;

		ddrval = pBackBuffer->BltFast(	xPos, yPos,
										(LPDIRECTDRAWSURFACE) pSprite->pGraphic, 
										&pSprite->srect, flags );
//		if (ddrval != DD_OK)	{
//			TRACE("Couldn't BltFast SPRITE: %s.\n", DDErrorToString(ddrval));
//		}
	}
}

///========================================================================
//	Function:		DisplaySpriteFront()
//
//	Description:
//		Display up a sprite on the frontbuffer.
//
//	Input:			pSprite			pointer to a sprite
//					x				screen x position
//					y				screen y position
//
//	Ouput:			none
//
///========================================================================

void	DisplaySpriteFront( PSPRITE pSprite, DWORD x, DWORD y )
{
	LONG		xPos;
	LONG		yPos;
	HRESULT     ddrval;
	RECT        drect;
	DWORD		flags;

	// make sure we have a valid sprite and surface
	if( !pSprite )
		return;

	if (pSprite->pGraphic == NULL)
		return;

	if (pSprite->sprite_flags & SP_RLE)
		return;

	if (pSprite->sprite_flags & (SP_DRLE | SP_WRLE | SP_TRLE | SP_SRLE ) )
	{
		TRACE( "Tried to display RLE256 in DisplaySpriteFront()\n ");
		return;
	}


	xPos = x - (DWORD)(pSprite->hotspot.x);
	yPos = y - (DWORD)(pSprite->hotspot.y);

	drect.left = rcWindowScreen.left + xPos;
	drect.top = rcWindowScreen.top + yPos;
	drect.right = drect.left + pSprite->srect.right;
	drect.bottom = drect.top + pSprite->srect.bottom;

	flags = (DDBLT_KEYSRC | DDBLT_WAIT);
	if ( pSprite->sprite_flags & SP_OPAQUE )
		flags = DDBLT_WAIT;

	ddrval = pFrontBuffer->Blt(
		&drect,								// dest rect
		(LPDIRECTDRAWSURFACE) pSprite->pGraphic,		// src surface
		&pSprite->srect,								// src rect
		flags,
		NULL);

	if( ddrval != DD_OK )
		TRACE( "BAD! in DisplaySpriteFront() %x\n", ddrval );

//	if (ddrval != DD_OK)
//		TRACE("Blt() failure of Sprite to front buffer\n");
//		DDFail("Blt() failure of Sprite to front buffer", ddrval);
}

///========================================================================
//	Function:		DisplaySpriteClipped()
//
//	Description:
//		Display a sprite on the screen, clipped to the rcGameWindow.
//
//	Input:			pSprite			pointer to a sprite
//					x				screen x position
//					y				screen y position
//
//	Ouput:			none
//
///========================================================================

void	DisplaySpriteClipped( PSPRITE pSprite, DWORD x, DWORD y )
{
	HRESULT     ddrval;
	RECT		rcRect;
	DWORD		flags;
	LONG		xPos;
	LONG		yPos;
    DDSURFACEDESC	backbuffer_ddsd;
	BYTE *pDestStart;

	// make sure we have a valid sprite and surface
	if( !pSprite )
		return;

	if( (pSprite->sprite_type == SPRITE_TYPE_SRLE) )
	{
		if( pSprite->pShadow == NULL )
			return;
	}
	else
	if( pSprite->pGraphic == NULL )
		return;

	// start buy clipping the rectangle to the screen image
	xPos = (x - (DWORD)(pSprite->hotspot.x));
	yPos = (y - (DWORD)(pSprite->hotspot.y));
	if ( ClipRectToGameWindow( &(pSprite->srect), &xPos, &yPos, &rcRect))
	{
		if ( pSprite->sprite_flags & (SP_DRLE | SP_WRLE | SP_TRLE | SP_SRLE ) )
		{
			if ( LOCK_COMPLEX_ON )
			{
				if ( !LOCK_STATUS )
				{
					backbuffer_ddsd.dwSize = sizeof(DDSURFACEDESC);
					ddrval = pBackBuffer->Lock( NULL, &backbuffer_ddsd, DDLOCK_WAIT, NULL );
					if ( ddrval == DD_OK )
					{
						SCRPTR = (BYTE *)backbuffer_ddsd.lpSurface;
						LPITCH = backbuffer_ddsd.lPitch;
						LOCK_STATUS = TRUE;
					}			
					else 
						TRACE("Error on RLE pBackBuffer Lock in DisplaySprite()");
				}
				if ( SCRPTR != NULL )
				{
					switch( pSprite->sprite_type )
					{
					case SPRITE_TYPE_DRLE:
						DrawDRleClipped( xPos, yPos, (BYTE *)pSprite->pGraphic, rcRect );
						break;
					case SPRITE_TYPE_WRLE:
						DrawWRleClipped( xPos, yPos, (BYTE *)pSprite->pGraphic, rcRect );
						break;
					case SPRITE_TYPE_TRLE:
						if ( pSprite->trans_table == NULL )
							DrawWRleClipped( xPos, yPos, (BYTE *)pSprite->pGraphic, rcRect );
						else
							DrawTRleClipped( xPos, yPos, (BYTE *)pSprite->pGraphic, rcRect, pSprite->trans_table );
						break;
					}
					if( pSprite->pShadow != NULL)
						DrawSRleClippedShade( xPos, yPos, (BYTE *)(pSprite->pShadow), rcRect );
				}
			}
			else
			{
				backbuffer_ddsd.dwSize = sizeof(DDSURFACEDESC);
				ddrval = pBackBuffer->Lock( NULL, &backbuffer_ddsd, DDLOCK_WAIT, NULL );
				if ( ddrval == DD_OK )
				{
					SCRPTR = (BYTE *)backbuffer_ddsd.lpSurface;
					LPITCH = backbuffer_ddsd.lPitch;
				}			
				else 
					TRACE("Error on RLE pBackBuffer Lock in DisplaySprite()");
				if ( SCRPTR != NULL )
				{
					switch( pSprite->sprite_type )
					{
					case SPRITE_TYPE_DRLE:
						DrawDRleClipped( xPos, yPos, (BYTE *)pSprite->pGraphic, rcRect );
						break;
					case SPRITE_TYPE_WRLE:
						DrawWRleClipped( xPos, yPos, (BYTE *)pSprite->pGraphic, rcRect );
						break;
					case SPRITE_TYPE_TRLE:
						if ( pSprite->trans_table == NULL )
							DrawWRleClipped( xPos, yPos, (BYTE *)pSprite->pGraphic, rcRect );
						else
							DrawTRleClipped( xPos, yPos, (BYTE *)pSprite->pGraphic, rcRect, pSprite->trans_table );
						break;
					}
					if( pSprite->pShadow != NULL)
						DrawSRleClippedShade( xPos, yPos, (BYTE *)(pSprite->pShadow), rcRect );
				}
				pBackBuffer->Unlock(SCRPTR);
			}
		}
		else if (pSprite->sprite_flags & SP_RLE)	
		{
			if ( LOCK_COMPLEX_ON )
			{
				if ( !LOCK_STATUS )
				{
					backbuffer_ddsd.dwSize = sizeof(DDSURFACEDESC);
					ddrval = pBackBuffer->Lock( NULL, &backbuffer_ddsd, DDLOCK_WAIT, NULL );
					if ( ddrval == DD_OK )
					{
						SCRPTR = (BYTE *)backbuffer_ddsd.lpSurface;
						LPITCH = backbuffer_ddsd.lPitch;
						LOCK_STATUS = TRUE;
					}			
					else 
						TRACE("Error on RLE pBackBuffer Lock in DisplaySprite()");
				}
				if ( SCRPTR != NULL )
				{
					pDestStart = (BYTE *)SCRPTR + yPos * LPITCH + xPos;
					if (pSprite->trans_table)
						RLETranslateBltClipped(	pDestStart, LPITCH,
							(BYTE *)pSprite->pGraphic, rcRect, pSprite->trans_table );
					else
						RLEFastBltClipped(	pDestStart, LPITCH,
							(BYTE *)pSprite->pGraphic, rcRect );
				}
			}
			else
			{
				backbuffer_ddsd.dwSize = sizeof(DDSURFACEDESC);
				ddrval = pBackBuffer->Lock( NULL, &backbuffer_ddsd, DDLOCK_WAIT, NULL );
				if ( ddrval == DD_OK )
				{
					SCRPTR = (BYTE *)backbuffer_ddsd.lpSurface;
					LPITCH = backbuffer_ddsd.lPitch;
				}			
				else 
					TRACE("Error on RLE pBackBuffer Lock in DisplaySprite()");
				if ( SCRPTR != NULL )
				{
					pDestStart = (BYTE *)SCRPTR + yPos * LPITCH + xPos;
					if (pSprite->trans_table)
						RLETranslateBltClipped(	pDestStart, LPITCH,
							(BYTE *)pSprite->pGraphic, rcRect, pSprite->trans_table );
					else
						RLEFastBltClipped(	pDestStart, LPITCH,
							(BYTE *)pSprite->pGraphic, rcRect );
				}
				pBackBuffer->Unlock(SCRPTR);
			}
		}
		else	
		{
			if ( LOCK_STATUS )
			{
				pBackBuffer->Unlock( SCRPTR );
				LOCK_STATUS = FALSE;
			}
			// set up transparency flags
			flags = (DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
			if ( pSprite->sprite_flags & SP_OPAQUE )
				flags = DDBLTFAST_WAIT;

			// Blt the sprite to the back surface
			ddrval = pBackBuffer->BltFast( xPos, yPos,
										   (LPDIRECTDRAWSURFACE) pSprite->pGraphic,
										   &rcRect,
										   flags
										 );
//			if (ddrval != DD_OK)	{
//				TRACE("Couldn't BltFast SPRITE: %s.\n", DDErrorToString(ddrval));
//			}
		}


#if 0
	    DDSURFACEDESC	sprite_ddsd;
		int				xpc;

		if (pSprite->trans_table)	{
			if ( pSprite->opaque )
				xpc = -1;
			else
				xpc = pSprite->xpc;

			sprite_ddsd.dwSize = sizeof(DDSURFACEDESC);
			backbuffer_ddsd.dwSize = sizeof(DDSURFACEDESC);
			if ((ddrval = pSprite->pGraphic->Lock(NULL, &sprite_ddsd, DDLOCK_WAIT, NULL)) == DD_OK)	{
				if ((ddrval = pBackBuffer->Lock(NULL, &backbuffer_ddsd, DDLOCK_WAIT, NULL)) == DD_OK)	{
					pDestStart = (BYTE *)backbuffer_ddsd.lpSurface + yPos*backbuffer_ddsd.lPitch + xPos;

					DDTranslateBlt(pDestStart, backbuffer_ddsd.lPitch, 
						(BYTE *)sprite_ddsd.lpSurface, sprite_ddsd.lPitch, 
						&rcRect, xpc, pSprite->trans_table);

					pBackBuffer->Unlock(backbuffer_ddsd.lpSurface);
				}
				else TRACE("Error on pBackBuffer Lock in DisplaySprite()");
				pSprite->pGraphic->Unlock(sprite_ddsd.lpSurface);
			}
			else TRACE("Error on sprite surface Lock in DisplaySprite()");
		}
#endif
	}
}

///========================================================================
//	Function:		DisplaySpriteClippedFront()
//
//	Description:
//		Display a sprite on the screen, clipped to the rcGameWindow.
//
//	Input:			pSprite			pointer to a sprite
//					x				screen x position
//					y				screen y position
//
//	Ouput:			none
//
///========================================================================

void	DisplaySpriteClippedFront( PSPRITE pSprite, DWORD x, DWORD y )
{
	HRESULT     ddrval;
	RECT		rcRect;
	RECT        drect;
	DWORD		flags;
	LONG		xPos;
	LONG		yPos;

	// make sure we have a valid sprite and surface
	ASSERT(pSprite != NULL);
	if (pSprite->pGraphic == NULL)
		return;

	// start buy clipping the rectangle to the screen image
	xPos = (x - (DWORD)(pSprite->hotspot.x));
	yPos = (y - (DWORD)(pSprite->hotspot.y));

	if ( ClipRectToGameWindow( &(pSprite->srect), &xPos, &yPos, &rcRect))
	{
		if ( LOCK_STATUS )
		{
			pFrontBuffer->Unlock( SCRPTR );
			LOCK_STATUS = FALSE;
		}
		// set up transparency flags
		flags = (DDBLT_KEYSRC | DDBLT_WAIT);
		if ( pSprite->sprite_flags & SP_OPAQUE )
			flags = DDBLT_WAIT;


		drect.left    = rcWindowScreen.left + xPos;
		drect.top     = rcWindowScreen.top + yPos;
		drect.right   = drect.left + rcRect.right - rcRect.left;
		drect.bottom  = drect.top + rcRect.bottom - rcRect.top;

		ddrval = pFrontBuffer->Blt(
			&drect,										// dest rect
			(LPDIRECTDRAWSURFACE) pSprite->pGraphic,	// src surface
			&rcRect,									// src rect
			flags,
			NULL);

		if (ddrval != DD_OK)	{
			TRACE("Couldn't Blt SPRITE: %s.\n", DDErrorToString(ddrval));
		}
	}
}

///========================================================================
//	Function:		FreeSprite()
//
//	Description:
//		Release or free up a sprite.
//
//	Input:			pSprite		pointer to a sprite
//
//	Ouput:			none
//
///========================================================================

void	FreeSprite( PSPRITE pSprite )
{
	SHAREDBITMAP *pSharedBitmap;


	ASSERT(pSprite);

	if (pSharedBitmap=pSprite->pSharedBitmap)
	{
		if (--pSharedBitmap->refcount==0)
		{
			if (pSprite->pGraphic)	
			{
				if (pSprite->sprite_flags & (SP_RLE | SP_DRLE | SP_WRLE | SP_TRLE) )
					free(pSprite->pGraphic);
				else	
				{
					LPDIRECTDRAWSURFACE pSurface = (LPDIRECTDRAWSURFACE) (pSprite->pGraphic);
					pSurface->Release();
				}

				pSprite->pGraphic=NULL;
			}

			if (pSprite->pMask && pSprite->sprite_flags & SP_PRIMEMASK)	
			{
				free(pSprite->pMask);
			}
			pSprite->pMask = NULL;

			if( pSprite->pShadow != NULL )
			{
				free( pSprite->pShadow );
				pSprite->pShadow = NULL;
			}
			

			ZeroMemory(pSharedBitmap, sizeof(SHAREDBITMAP));
		}
	}
	else
	{
		if (pSprite->pGraphic)	
		{
			if (pSprite->sprite_flags & (SP_RLE | SP_DRLE | SP_WRLE | SP_TRLE) )
				free(pSprite->pGraphic);
			else	
			{
				LPDIRECTDRAWSURFACE pSurface = (LPDIRECTDRAWSURFACE) (pSprite->pGraphic);
				pSurface->Release();
			}
		}
		pSprite->pGraphic = NULL;
		

		if (pSprite->pMask && pSprite->sprite_flags & SP_PRIMEMASK)	
		{
			free(pSprite->pMask);
		}
		pSprite->pMask = NULL;

		if( pSprite->pShadow != NULL )
		{
			free( pSprite->pShadow );
			pSprite->pShadow = NULL;
		}
	}
}

BOOL	SpriteBox( PSPRITE pSprite, SBOX* pBox )
{
	ASSERT( pSprite );
	ASSERT( pBox );

	pBox->x  = (short)pSprite->srect.left;
	pBox->y  = (short)pSprite->srect.top;
	pBox->cx = (short)(pSprite->srect.right - pSprite->srect.left);
	pBox->cy = (short)(pSprite->srect.bottom - pSprite->srect.top);


#ifdef SCREEN_DEBUG
TRACE( "SpriteBox: pBox (%d,%d,%d,%d )\n",
		pBox->x, pBox->y, pBox->cx,   pBox->cy
	 );
#endif

	return( FALSE );
}

///========================================================================
//								EOF
///========================================================================
