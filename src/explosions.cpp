////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: explosions.cpp $
//
//	DESCRIPTION:	the map structure
//
//	AUTHOR:			Alex Werner
//
//	REVISION:		$Header: /ArmyMen/src/explosions.cpp 78    4/10/98 5:38p Phu $
//
//	Copyright (C) 1997-98 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/explosions.cpp $
//  
//  78    4/10/98 5:38p Phu
//  explosion sounds from off screen
//  
//  77    4/10/98 1:39a Nrobinso
//  reset anim callback
//  
//  76    4/07/98 3:21p Nrobinso
//  change order of sound play and volume
//  
//  74    4/02/98 3:05p Phu
//  
//  73    3/27/98 3:29p Phu
//  mortar blasts
//  
//  72    3/07/98 11:51p Nrobinso
//  move .h file to stdafx
//  
//  71    3/07/98 10:41p Nrobinso
//  move explosion anim files to the terrain folders
//  
//  70    3/06/98 7:29p Phu
//  load axs explosions instead
//  
//  69    3/06/98 2:53p Phu
//  library load as default,  faster animation loading
//  
//  68    3/03/98 12:52p Phu
//  screen shake across network
//  
//  67    3/02/98 10:31a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  66    2/25/98 10:31p Nrobinso
//  use audioGetSndByAudioID
//  
//  65    2/25/98 10:25a Nrobinso
//  don't bother maintinaing an explosion table -- just create as needed
//  and check to see if it needs to be saved by the audio
//  
//  64    2/20/98 4:32p Nrobinso
//  decrease number of explosion sounds
//  
//  63    2/20/98 4:07p Nrobinso
//  remote explosions given sound
//  
//  62    2/20/98 1:16p Nrobinso
//  fix up sounds
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "audio.h"			// AUDIO       defines, structures, and prototypes
#include "sounds.h"			// AUDIO       sfx sound effects equates
#include "anim.h"
#include "AnimFile.h"
#include "Army.h"
#include "Disp.h"
#include "MainFrm.h"
#include "Tad.h"
#include "Map.h"
#include "Vehicle.h"
#include "Input.h"
#include "miscfile.h"
#include "GameFlow.h"
#include "Ai.h"
#include "AiAccess.h"
#include "item.h"
#include "comm.h"
#include "damage.h"
#include "explosions.h"
#include "floatmsg.h"
#include "trooper.h"
#include "sarge.h"
#include "wobject.h"


extern void AnimWorldBoundary( ANIM* pTheAnim );
extern char validate;

//////////////////////////////////////////////////////////////////////////////////////
//DEFINES
//////////////////////////////////////////////////////////////////////////////////////
#define EXPLOSION_GRID_SIZE 50
#define MAX_EXPLODE       6

//////////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES
//////////////////////////////////////////////////////////////////////////////////////


static COMMAND explosion_command_array[]=
{
	{EXPLOSION_SMOKE_S_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_SMOKE_M_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_SMOKE_L_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_GUN_PUFF_M_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_GUN_SPARK_S_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_GUN_SPARK_M_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_GUN_SPARK_L_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_DIRT_SMOKE_S_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_DIRT_SMOKE_M_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_DIRT_SMOKE_L_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_COMBUSTION_S_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_COMBUSTION_M_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_COMBUSTION_L_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_FLASH_SMOKE_S_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_FLASH_SMOKE_M_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_FLASH_SMOKE_L_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_FLASH_COMBUSTION_S_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_FLASH_COMBUSTION_M_COMMAND, INACTIVATE_COMMAND, NULL},	// mine explode
	{EXPLOSION_FLASH_COMBUSTION_L_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_FLASH_DIRT_SMOKE_S_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_FLASH_DIRT_SMOKE_M_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_FLASH_DIRT_SMOKE_L_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_WATER_S_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_WATER_M_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_WATER_L_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_WATER_GUN_PUFF_S_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_WATER_GUN_PUFF_M_COMMAND, INACTIVATE_COMMAND, NULL},
	{EXPLOSION_WATER_GUN_PUFF_L_COMMAND, INACTIVATE_COMMAND, NULL}

};

static COMMAND_LIST explosion_commands =
{
	sizeof(explosion_command_array)/sizeof(COMMAND), 
	explosion_command_array
};

static CSpriteCatalog *pCat;
static BOOL explosionsloaded=FALSE;

static ANIM Explosions[NUMACTIVEEXPLOSIONS];

static int nextexplosion=0;

#define FIRST_SND BAZOOKA_EXPLODE
#define LAST_SND FLAME_BEGIN
#define SOUNDS (LAST_SND-FIRST_SND)


EXPLOSIONPATTERN SmallExplosion =
{
	 48,  48,													// size
	-24, -24,													// offset
	NULL
};


EXPLOSIONPATTERN MediumExplosion =
{
	 64,  64,													// size
	-32, -32,													// offset
	NULL
};


EXPLOSIONPATTERN LargeExplosion =
{
	 96, 96,													// size
	-48, -48,													// offset	
	NULL
};


int ExplodeCount = 0;

//////////////////////////////////////////////////////////////////////////////////////
//FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////////////


LONG ExplosionCallbackFunction(ANIM *pAnim);



//////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////

///========================================================================
//	Function:		LoadExplosions()
//
//	Description:
//		Loads in the animations for the explosions.
//
//
//	Input:			none
//
//	Ouput:			<0 on error. 0 if no error
//
///========================================================================

int LoadExplosions(void)
{
	if (explosionsloaded)
		return 0;

	SetPath(the_map.terrain_name);

	ClearTotals();

	pCat = AnimImport("explosions.axs", BM_TRANSPARENT);
	
	if (!pCat)
	{
		TRACE("ERROR: no valid PCAT returned from AnimImport in LoadExplosions");
		return -1;
	}

	ProcessAnim(pCat, &explosion_commands);
	CheckAnim(&explosion_commands, "explosions", NULL);

	explosionsloaded=TRUE;

	return 0;
}

///========================================================================
//	Function:		UnloadExplosions()
//
//	Description:
//		Unloads the animations for the explosions.
//
//
//	Input:			none
//
//	Ouput:			<0 on error. 0 if no error
//
///========================================================================

int UnloadExplosions(void)
{
	if (!explosionsloaded)
		return 0;

	FreeAnimImport(pCat);

	explosionsloaded=FALSE;

	return 0;
}

///========================================================================
//	Function:		InitExplosions()
//
//	Description:
//		Gets the explosions ready to go
//
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================

void InitExplosions(void)
{
	int i;

	nextexplosion=0;

	for (i=0;i<NUMACTIVEEXPLOSIONS;i++)
	{
		AnimInit( 255, 255, &Explosions[i], OL_OVERLAYLAYER );
		Explosions[i].anim_sound = SND_NULL_SND_ID;
	}
}

///========================================================================
//	Function:		FreeExplosions()
//
//	Description:
//		Frees up memory used by the explosions
//
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================
void FreeExplosions(void)
{
	int i;

	for (i=0;i<NUMACTIVEEXPLOSIONS;i++)
	{
		AnimDelete( &(Explosions[i]) );
		if (Explosions[i].pData)
			free(Explosions[i].pData);
	}

//	for (i=0;i<SOUNDS;i++)
//	{
//		explosion_snds[i] = SND_NULL_SND_ID;
//	}

}	//	FreeExplosions


///========================================================================
//	Function:		ReadyExplosion()
//
//	Description:
//		Makes sure that an explosion is ready to use.
//
//
//	Input:			whichexplosion	which explosion to check
//
//	Ouput:			none
//
///========================================================================
void ReadyExplosion(int whichexplosion)
{
	//currently, all this function does is it makes sure that this explosion
	//isn't waiting to do damage. If it is, it does that damage.

	// TRACE("ReadyExplosion %d\n", whichexplosion);

	ASSERT( whichexplosion >= 0 && whichexplosion < NUMACTIVEEXPLOSIONS );
	// if (Explosions[whichexplosion].pData)
		// ExplosionCallbackFunction(&Explosions[whichexplosion]);
}



///========================================================================
//	Function:		ShowExplosion()
//
//	Description:
//		Displays a single explosion
//
//
//	Input:			explosiontype		what type of explosion (ie EXPLOSION_SMOKE_M_COMMAND)
//					x,y					the location (in world coordinates)
//
//	Ouput:			none
//
///========================================================================
void ShowExplosion(COMMAND_NUMBERS explosiontype, short x, short y, int delay)
{
	int thisexplosion;

	thisexplosion=nextexplosion;
	nextexplosion=(nextexplosion+1)%NUMACTIVEEXPLOSIONS;
	
	ReadyExplosion(thisexplosion);
	AnimSet(&Explosions[thisexplosion], x, y, &explosion_commands, explosiontype, 0, ZERO_VELOCITY);
	AnimActivate(&Explosions[thisexplosion], NO_ACTIVATE_LINKS );
	if (delay)
		AnimSetDelay(&Explosions[thisexplosion], delay);
	AnimWorldBoundary( &Explosions[thisexplosion] );
	AnimMove( &Explosions[thisexplosion], FALSE );

}

///========================================================================
//	Function:		UpdateExplosions()
//	Description:	Processes all the explosion anims. Must be called once per frame 
///========================================================================
void ValidateExplosions()
{
	int i;
    if (!validate) return;
	for (i=0;i<NUMACTIVEEXPLOSIONS;i++)
		ASSERT( !(Explosions[i].flags & ANIM_FLAGS_ALL_UNUSED));
}

void UpdateExplosions(void)
{
	int i;
	ValidateExplosions();
	for (i=0;i<NUMACTIVEEXPLOSIONS;i++)
	{
		if( Explosions[i].flags & ANIM_FLAG_ACTIVE )
		{
			AnimUpdate( &Explosions[i] );
			AnimWorldBoundary( &Explosions[i] );
			AnimMove( &Explosions[i], FALSE );
		}
	}
	ValidateExplosions();
}


///========================================================================
//	Function:		DoDamagingExplosion()
//
//	Description:
//		Damages all objects in a certain area
//
//
//	Input:			x,y			the location of the explosion
//					pattern		a pointer to an EXPLOSIONPATTERN struct
//								giving the pattern of the explosion		
//
//	Ouput:			none
//
///========================================================================

static void DoDamagingExplosion(short x, short y, EXPLOSIONPATTERN *pattern, int damagetype, int maxdamage, ITEM *objtoexclude, int explosiontype, UID fromUID)
{
	RECT	queryRect;
	ITEM	*pItemList, *pNextItem;
	SPOINT	pointOfDamage;

	if( pattern == NULL )
		pattern = &MediumExplosion;

	pointOfDamage.x = x;
	pointOfDamage.y = y;
	queryRect.left = x + pattern->xoffset;
	queryRect.right = queryRect.left + pattern->xsize;
	queryRect.top = y + pattern->yoffset;
	queryRect.bottom = queryRect.top + pattern->ysize;

	pItemList = GetExplosionInfluence( queryRect );

	while( pItemList != NULL )
	{
		pNextItem = pItemList->next;
		if( pItemList != objtoexclude )
		{
			// every machine does its own explosions, so only 1 should cause damage
			// damaging explosions should only come from own machine
			ItemDamage( pItemList, (int)((pItemList->temp * maxdamage) >> 8), 
					damagetype, &pointOfDamage, fromUID );
		}
		pItemList = pNextItem;
	}
}


//this function is the callback function called by the animation of the 
//explosion when it's time to do the damage
LONG ExplosionCallbackFunction(ANIM *pAnim)
{
	EXPLOSIONCALLBACKINFO *cbi;

	if (!pAnim->pData) //this happens sometimes when a frame is skipped because
						 //of timing things I don't quite understand... then the
						 //frame repeats, and the callback function gets called
						 //twice. So we just do nothing the second time.
	
		return -1;
	

	cbi = (EXPLOSIONCALLBACKINFO*)pAnim->pData;

	DoDamagingExplosion(cbi->x,cbi->y, cbi->pattern, cbi->damagetype, cbi->maxdamage, cbi->objtoexclude, cbi->explosiontype, cbi->fromUID );

	free(cbi);

	pAnim->pData = NULL;

	AnimCallbackClear(pAnim);

	return 0;
}


///========================================================================
//	Function:		DoExplosion()
//
//	Description:
//		Starts an explosion animation, and optionally has it damage everything
//		in its path. This is the primary explosion-generating function that
//		should be used by the outside world.
//
//
//	Input:			x,y				the location of the explosion
//					explosiontype	what visual explosion to use. For instance,
//									EXPLOSION_SMOKE_M_COMMAND
//					pattern			a pointer to an EXPLOSIONPATTERN struct
//									giving the pattern of the explosion		
//
//					damagetype		what type of damage this explosion is doing
//					maxdamage		how much damage is done at the center of the explosion
//					objtoexclude	an object which will not be damaged by this explosion.
//									(typically used so that if a bazooka hits an object and
//									explodes, the object won't be damage twice)
//					transmit		send this explosion to the remote player?
//									it most cases the explosions are generated on the remote
//									in response to damage message, however for explaosions
//									that don't result in dame messages we have to transmit them
//
//	Ouput:			none
//
///========================================================================
extern void inline DoExplosion(short x, short y, COMMAND_NUMBERS explosiontype, EXPLOSIONPATTERN *pattern, int damagetype, 
				 int maxdamage, ITEM *objtoexclude, BOOL transmit, UID fromUID, ULONG audioID )
{
	DoDelayedExplosion(x, y, explosiontype, pattern, damagetype, maxdamage, 
		objtoexclude, transmit, 0, fromUID, audioID );
}

///========================================================================
//	Function:		DoDelayedExplosion()
//
//	Description:
//		Starts an explosion animation, and optionally has it damage everything
//		in its path
//
//
//	Input:			x,y				the location of the explosion
//					explosiontype	what visual explosion to use. For instance,
//									EXPLOSION_SMOKE_M_COMMAND
//					pattern			a pointer to an EXPLOSIONPATTERN struct
//									giving the pattern of the explosion		
//
//					damagetype		what type of damage this explosion is doing
//					maxdamage		how much damage is done at the center of the explosion
//					objtoexclude	an object which will not be damaged by this explosion.
//									(typically used so that if a bazooka hits an object and
//									explodes, the object won't be damage twice)
//					transmit		send this explosion to the remote player?
//									it most cases the explosions are generated on the remote
//									in response to damage message, however for explaosions
//									that don't result in dame messages we have to transmit them
//					delay			Number of frames to delay before starting explosion
//
//	Ouput:			none
//
///========================================================================
void DoDelayedExplosion(short x, short y, COMMAND_NUMBERS explosiontype, EXPLOSIONPATTERN *pattern, int damagetype, 
				 int maxdamage, ITEM *objtoexclude, BOOL transmit, int delay, UID fromUID, ULONG audioID )
{
	ASSERT( !(Explosions[nextexplosion].flags & ANIM_FLAG_ACTIVE) );

	int border = VISIBLE_BOUNDARY/2;
	int tilex = TILEP(x);
	int tiley = TILEP(y);
	SPOINT	pt;
	ULONG	sndID;
	int		volume;
	int		audioIndex = audioID - FIRST_SND;
	AUDIO_IDS*	pAudioPtr;
	int		intensity;

	pt.x = x;
	pt.y = y;

	if (tilex<border || tilex>map_width-border || tiley<border ||tiley>map_height-border )
	{
		AudioPlayPoint( audioID, &pt );
		return;
	}

	switch( explosiontype )
	{
	case	EXPLOSION_COMBUSTION_S_COMMAND:
		intensity = 3;
		break;
	case	EXPLOSION_FLASH_COMBUSTION_S_COMMAND:
		intensity = 5;
		break;
	case	EXPLOSION_COMBUSTION_M_COMMAND:
	case	EXPLOSION_FLASH_COMBUSTION_M_COMMAND:
		intensity = 8;
		break;
	case	EXPLOSION_COMBUSTION_L_COMMAND:
	case	EXPLOSION_FLASH_COMBUSTION_L_COMMAND:
		intensity = 10;
		break;
	default:
		intensity = 0;
	}
	if( intensity > 0 )
		SetupQuake( pt, intensity );

	ReadyExplosion(nextexplosion);
	AnimSet(&Explosions[nextexplosion], x, y, &explosion_commands, explosiontype, 0, ZERO_VELOCITY);
	if (transmit) FloatExplosionMessageSend(x, y, explosiontype, delay, audioID);

	Explosions[nextexplosion].order = (short)(gpGame->dwAnimTime & 0x7fff);
	Explosions[nextexplosion].anim_sound = SND_NULL_SND_ID;
	if (ExplodeCount != MAX_EXPLODE)
	{
		if (audioID != SND_NULL_SND_ID)
		{
			volume = audioFindVolumePercent(&pt);
			if (volume)	{

				// see if we already have this sound
				pAudioPtr = audioGetSndByAudioID( audioID  );

				if ( pAudioPtr == (AUDIO_IDS*)SND_NULL_SND_PTR )	{
					sndID = audioCreateSnd( AUDIOsfxID, audioID, 0, SND_SFX_FLAG );
					audioStoreSnd( audioID, sndID, SND_SFX_FLAG );
#if 0
					TRACE("Creating explosion Audio ID %d\n", audioID);
#endif
				}
				else
					sndID = audioCreateSnd( AUDIOsfxID, audioID, 0, SND_SFX_FLAG | SND_DELETE_FLAG );

				if ( sndID != SND_NULL_SND_ID )	{
					Explosions[nextexplosion].anim_sound = sndID;
					if (!delay)
						sndPlay(sndID);
					SndSetVolumePercent(sndID, volume, FALSE);
					ExplodeCount++;
				}
				else
					TRACE("ERROR: failed to load sound. [%s:%d]\n", __FILE__, __LINE__ );
			}
		}
	}
	
	if (maxdamage) //yes, we want to do damage.
	{
		EXPLOSIONCALLBACKINFO *callbackinfo;

		callbackinfo = (EXPLOSIONCALLBACKINFO*)malloc(sizeof(EXPLOSIONCALLBACKINFO));
		ASSERT( callbackinfo != 0 );
		callbackinfo->x = x;
		callbackinfo->y = y;
		callbackinfo->pattern = pattern;
		callbackinfo->maxdamage = maxdamage;
		callbackinfo->objtoexclude = objtoexclude;
		callbackinfo->damagetype = damagetype;
		callbackinfo->explosiontype = explosiontype;
        callbackinfo->fromUID = fromUID;

		Explosions[nextexplosion].pData = (void*)(callbackinfo);
		AnimCallback(&Explosions[nextexplosion], ExplosionCallbackFunction, 3, explosiontype );	// frame 3
	}

	AnimActivate(&Explosions[nextexplosion], NO_ACTIVATE_LINKS );

	if (delay)
		AnimSetDelay(&Explosions[nextexplosion], delay);

	AnimWorldBoundary( &Explosions[nextexplosion] );
	AnimMove( &Explosions[nextexplosion], FALSE );

	nextexplosion=(nextexplosion+1)%NUMACTIVEEXPLOSIONS;
	ASSERT( nextexplosion >= 0 && nextexplosion < NUMACTIVEEXPLOSIONS );

	if( intensity > 3 )
		GenerateFlashBurn( x, y, rand() % NUM_SCAR_SPRITES );
}



///========================================================================
//	Function:		CoverObjectWithExplosions()
//
//	Description:
//		Splatters explosions all over an object (if it's large), or else
//		just does one explosion on the object. These are purely visual 
//		explosions.
//
//
//	Input:			pObj			a pointer to the object to cover
//					numtypes		the size of the explosiontypes array
//					explosiontypes	an array of explosion types to randomly
//									pick from
//					onlyiflarge		if this flag is set, the explosions will
//									only be shown if the object is "large".
//
//	Ouput:			none
//
///========================================================================
void CoverObjectWithExplosions(OBJECT *pObj, int numtypes, COMMAND_NUMBERS *explosiontypes, BOOL onlyiflarge, UID fromUID )
{
	int left, top;
	SPOINT grid;
	SPOINT gridboxsize;
	int x,y;
	SPRITE *pSprite;
	LPDIRECTDRAWSURFACE	pSurface;
	HRESULT ddrval;
	DDSURFACEDESC ddsd;
	BYTE *ptr;
	BYTE pixel;

	int curx, cury;

	int checksprite=1;



	pSprite=pObj->cell.pSprite;
	left=pObj->cell.world_pos.x-pSprite->hotspot.x;
	top=pObj->cell.world_pos.y-pSprite->hotspot.y;

	// hack fix for RLE256 sprites
	if ( pSprite->sprite_flags & (SP_DRLE | SP_WRLE | SP_TRLE | SP_SRLE ) )
	{
		checksprite=0;
	}
	// hack fix

	if ((pSprite->srect.right> (EXPLOSION_GRID_SIZE*1.5))&&
		 (pSprite->srect.bottom> (EXPLOSION_GRID_SIZE*1.5)))
	{
		left=pObj->cell.world_pos.x-pSprite->hotspot.x;
		top=pObj->cell.world_pos.y-pSprite->hotspot.y;

		grid.x=pSprite->srect.right/EXPLOSION_GRID_SIZE;
		grid.y=pSprite->srect.bottom/EXPLOSION_GRID_SIZE;

		gridboxsize.x=pSprite->srect.right/grid.x;
		gridboxsize.y=pSprite->srect.bottom/grid.y;

		if (checksprite)
		{
			pSurface = (LPDIRECTDRAWSURFACE) pSprite->pGraphic;
			ZeroMemory( &ddsd, sizeof( DDSURFACEDESC ) );
			ddsd.dwSize = sizeof(DDSURFACEDESC);
			ddrval = pSurface->Lock(NULL, &ddsd, DDLOCK_WAIT|DDLOCK_READONLY, NULL);
		}

					
		for (x=0;x<grid.x;x++)
			for (y=0;y<grid.y;y++)
			{
				curx=gridboxsize.x*x+(rand()%gridboxsize.x);
				cury=gridboxsize.y*y+(rand()%gridboxsize.y);

				if ((checksprite) && (ddrval == DD_OK))	
				{
					ptr = (BYTE *) ddsd.lpSurface;
					pixel = ptr[(cury * ddsd.lPitch) + curx];
					pSurface->Unlock(ptr);
					if (pixel != pSprite->xpc)
						ShowExplosion(explosiontypes[rand()%numtypes],left+curx, top+cury, (rand()%2) ? 0 : (rand()%10));
				}
				else
					ShowExplosion(explosiontypes[rand()%numtypes],left+curx, top+cury, (rand()%2) ? 0 : (rand()%10));
			}




	}
	else
		if (!onlyiflarge)
			ShowExplosion(explosiontypes[rand()%numtypes], left+pSprite->srect.right/2, top+pSprite->srect.bottom/2, 0);
}






