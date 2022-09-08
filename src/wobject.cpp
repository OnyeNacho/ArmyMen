//========================================================================
//	FILE:			$Workfile: wobject.cpp $
//
//	DESCRIPTION:	
//
//	AUTHOR:			Peter Hu
//
//	REVISION:		$Header: /ArmyMen/src/wobject.cpp 91    98/04/06 11:06 Dmaynard $
//
//                 COPYRIGHT(C)1996-98 The 3DO Company
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/wobject.cpp $
//  
//  91    98/04/06 11:06 Dmaynard
//  change flag offsets
//  
//  89    4/03/98 4:02p Phu
//  map pause frag counters
//  
//  88    4/02/98 7:36p Nrobinso
//  change water hit sound
//  
//  87    4/02/98 6:29p Phu
//  typecast to avoid warnings
//  
//  86    4/01/98 1:27p Bwilcox
//  change local test
//  
//  85    3/31/98 1:08p Bwilcox
//  dispell fog
//  
//  84    3/30/98 2:37p Dmaynard
//  Make Sarge Icons show up for one-player multi-player (with ai
//  opponents)
//  
//  83    3/30/98 11:48a Bwilcox
//  check for 1playermode in displaying icons
//  
//  82    3/30/98 12:43a Bwilcox
//  sarge icon display adjustments for multipler with and without humands
//  
//  81    3/27/98 9:17p Bwilcox
//  
//  80    3/27/98 8:28p Phu
//  don't know what I did but I like it
//  
//  79    3/27/98 6:16p Phu
//  new frag/flag
//  
//  78    3/26/98 4:34p Bwilcox
//  frag wrap at 100
//  
//  77    3/26/98 12:00p Bwilcox
//  show no flags of armies not playing,
//  show flags only for a capture-type game
//  
//  76    3/26/98 6:01a Bwilcox
//  show flags of uncollected players
//  
//  75    3/25/98 6:09p Phu
//  flag frags
//  
//  74    3/25/98 1:14p Phu
//  implemented new types of frag counters, need new art + object.dat
//  
//  73    3/22/98 6:08p Phu
//  fix parameter mismatch in rectintersect
//  
//  72    3/13/98 5:23p Phu
//  new tree stuff
//  
//  71    98/03/12 23:08 Dmaynard
//  When calling releaseobjectsprite you must store null afterwards or
//  crash sometimes.
//  
//  70    3/12/98 6:07a Bwilcox
//  loadobjects is now a fullly supported subdirectory of runtime, optional
//  like audio
//  
//  69    3/11/98 10:22p Nrobinso
//  switch to RectIntersect
//  
//  68    3/09/98 2:43p Phu
//  fix free bug in air
//  
//  67    3/09/98 1:39p Bwilcox
//  
//  66    3/04/98 3:01p Phu
//  change flame thrower timings
//  
//  65    3/03/98 7:56p Phu
//  multi-directional flame thrower
//  
//  64    3/02/98 5:13p Bwilcox
//  added countflames
//  
//  63    2/26/98 8:56p Phu
//  renamed some body part stuff
//  
//  62    98/02/26 11:22 Dmaynard
//  fix frag display
//  
//  61    2/25/98 10:36p Phu
//  
//  60    2/25/98 10:14p Phu
//  ODF load flash, bodyparts, misc
//  
//  59    2/25/98 6:28p Phu
//  rename wobject files
//  
//  58    2/20/98 1:09p Phu
//  draw icons to front if paused
//  
//  57    2/20/98 12:53p Phu
//  game pause stuff
//  
//  56    2/20/98 1:19p Nrobinso
//  fix up sounds
//  
//  $Nokeywords:$
///========================================================================
/*
	Include
*/
#include "stdafx.h"
#include "miscfile.h"
#include "army.h"
#include "anim.h"
#include "disp.h"
#include "gameflow.h"
#include "explosions.h"
#include "map.h"
#include "wobject.h"
#include "aiaccess.h"
#include "vehicle.h"
#include "fileio.h"
#include "comm.h"
#include "bmptext.h"
#include "husk.h"
#include "damage.h"
#include "sounds.h"
#include "snd.h"
#include "mainfrm.h"
#include "item.h"



void AnimWorldBoundary( ANIM* pTheAnim );


TBodyPartsData BodyPartsData[EBP_LastPart] =
{
	{"larm", 12, 3, NULL, -3, 0, 6},
	{"rarm", 17, 3, NULL, 3, 0, 6},
	{"chst",  4, 3, NULL, 0, 0, 6},
	{"head",  9, 3, NULL, 0, 0, 9},
	{"lleg", 13, 3, NULL, -3, 0, 3},
	{"rleg", 18, 3, NULL, 3, 0, 3},
	{"trso", 20, 3, NULL, 0, 0, 4},
	{"par1", 14, 3, NULL, 0, 0, 2},
	{"par2", 15, 3, NULL, 0, 0, 4},
	{"par3", 16, 3, NULL, 0, 0, 6}
};


TBodyPartsData VehiclePartsData[EVP_LastPart] =
{
	{"hded",  8, 4, NULL, 0, 0, 0},
	{"jded", 10, 4, NULL, 0, 0, 0},
	{"tded", 19, 4, NULL, 0, 0, 0},

	{"aaaa",  1, 5, NULL, 10, 7, 3},
	{"bbbb",  2, 3, NULL, 5, 8, 2},
	{"cccc",  3, 3, NULL, 3, 7, 4},
	{"dddd",  5, 4, NULL, 1, 6, 5},
	{"eeee",  6, 4, NULL, 5, 5, 1},
	{"ffff",  7, 5, NULL, 4, 10, 3},
	{"jeep", 11, 5, NULL, 7, 4, 4},
	{"par1", 14, 3, NULL, 4, 1, 5},
	{"par2", 15, 3, NULL, 6, 7, 1},
	{"par3", 16, 3, NULL, 2, 8, 3}
};


TMuzzleFlashData MuzzleFlashData[EFT_LastFlash] =
{
	{"muzz", 3, 32, NULL, 60 },
	{"tmfl", 4, 32, NULL, 80 },
	{"jtfl", 2, 32, NULL, 80 },
	{"htfl", 1, 32, NULL, 80 }
};


TFlameBurstData FlameBurstData =
{
	"flam", 8, 8, NULL, 200,
	{120, 120, 120, 120, 120, 120, 120, 120, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{60, 60, 60, 60, 60, 120, 120, 120, 120, 120},
	{0, 0, 0, 1, 2, 3, 4, 5, 6, 6}
};


TParatrooperData ParatrooperData[1] =
{
	{"para", 20}
};


TFireData FireData =
{
	"fire", 3, 8, 2, 40, NULL
};


PSPRITE *Chevron;
PSPRITE *Frags;
PSPRITE *FragFlags;
PSPRITE *ScarData;
PSPRITE *SmokeData;


TGroundObjectsArray  GroundObjects;
TCorpseObjectsArray  CorpseObjects;
TWorldObjectsArray	 WorldObjects;
TWorldObjectsArray   FlashObjects;


void AcquireWobjectSprite( PSPRITE &pSprite, int cat, int num, int idx, char *prefix, int flags )
{
	if( _LOAD_FROM_DATAFILE )
	{
		if( !(pSprite = AcquireObjectSprite( cat, num, idx )) )
			TRACE( "Unable to acquire sprite %d %d %d\n", cat, num, idx );
	}
	else
	{
		char filename[18];

		pSprite = (PSPRITE)malloc( sizeof(SPRITE) );
		ZeroMemory( pSprite, sizeof(SPRITE) );
		sprintf( filename, "%s_%03d_%d.bmp", prefix, num, idx );
		if( !LoadSprite( pSprite, filename, flags ) )
			TRACE( "Unable to load file %s\n", filename );
	}
}	//	AcquireWobjectSprite


void AcquireWobjectSpriteAsShadow( PSPRITE &pSprite, int cat, int num, int idx, char *prefix, BYTE *trans_table )
{
	if( _LOAD_FROM_DATAFILE )
	{
		if( !(pSprite = AcquireObjectSprite( cat, num, idx )) )
			TRACE( "Unable to acquire sprite %d %d %d\n", cat, num, idx );
		else
			pSprite->trans_table = trans_table;
	}
	else
	{
		char filename[18];

		pSprite = (PSPRITE)malloc( sizeof(SPRITE) );
		ZeroMemory( pSprite, sizeof(SPRITE) );
		sprintf( filename, "%s_%03d_%d.sha", prefix, num, idx );
		LoadShadowAsSprite( pSprite, filename, trans_table );
		if( !(pSprite->pShadow) )
			TRACE( "Unable to load file %s\n", filename );
	}
}	//	AcquireWobjectSpriteAsShadow



void ReleaseWobjectSprite( PSPRITE &pSprite )
{
	if( pSprite )
	{
		if( _LOAD_FROM_DATAFILE )
		{
			ReleaseObjectSprite( pSprite );
			pSprite = NULL; // BE CLEAN OR DIE, PETER.
		}
		else
		{
			FreeSprite( pSprite );
			free( pSprite );
			pSprite = NULL;
		}
	}
}	//  ReleaseWobjectSprite


//	Allocate the ground objects array
void InitGroundObjects( void )
{
	ANIMCELL *pAnim;

	GroundObjects.count = GroundObjects.tail = 0;
	for( int i = 0; i < MAX_GROUND_OBJECTS; i++ )
	{
		GroundObjects.objects[i].index = i;
		GroundObjects.objects[i].prev = GroundObjects.objects[i].next = -1;
		pAnim = GroundObjects.objects[i].pAnim = (ANIMCELL *)malloc(sizeof(ANIMCELL));
		ZeroMemory( pAnim, sizeof(ANIMCELL) );
		pAnim->flags = ~ANIM_FLAG_ACTIVE;
		pAnim->flags |= ANIM_FLAG_CELL;
		CreateDispXObject( 96, 96, pAnim, OL_GROUNDLAYER );
	}
}  //  InitGroundObjects


//  Clear the ground objects array & free up associated memory
void FreeGroundObjects( void )
{
	for( int i = 0; i < MAX_GROUND_OBJECTS; i++ )
	{
		if (GroundObjects.objects[i].pAnim)
		{
			AnimDelete( (ANIM *)(GroundObjects.objects[i].pAnim) );
			free( GroundObjects.objects[i].pAnim );
			GroundObjects.objects[i].pAnim = NULL;
		}
		GroundObjects.objects[i].prev = GroundObjects.objects[i].next = -1;
	}
	GroundObjects.count = GroundObjects.tail = 0;
}  //  FreeGroundObjects


//	Insert a new ground object
PGroundObject InsertGroundObject( void )
{
	int i;

	if( GroundObjects.count > MAX_GROUND_OBJECTS - GROUND_OBJECTS_BUFFER )
		FreeSomeGroundObjects();

	i = ++GroundObjects.count;
	GroundObjects.objects[i].index = i;
	GroundObjects.objects[i].prev = GroundObjects.tail;
	GroundObjects.objects[i].next = -1;
	GroundObjects.objects[GroundObjects.tail].next = i;
	GroundObjects.tail = i;
	return( &(GroundObjects.objects[i]) );
}  //  InsertGroundObject


//  Delete a ground object
int DeleteGroundObject( PGroundObject pgo )
{
	PGroundObject ptr;
	int i, nextnode;
	ANIMCELL *pAnim;	

	ASSERT( pgo->index > 0 );
	ASSERT( pgo->prev >= 0 );

	// delete the current dispnode
	pAnim = pgo->pAnim;
	if( pAnim->flags & ANIM_FLAG_ACTIVE )
	{
		pAnim->flags &= ~ANIM_FLAG_ACTIVE;
		MoveDispXObject( pAnim, FALSE );
	}
	// point "around" the node we are deleting
	GroundObjects.objects[pgo->prev].next = nextnode = pgo->next;
	if( pgo->next > 0 )
		GroundObjects.objects[pgo->next].prev = pgo->prev;
	// if we are deleting the tail, set the new tail
	if( GroundObjects.tail == pgo->index )
		GroundObjects.tail = pgo->prev;
	ptr = &( GroundObjects.objects[GroundObjects.count] );
	if( pgo->index != GroundObjects.count )
	{
		// move objects[count] into vacated space
		GroundObjects.objects[ptr->prev].next = pgo->index;
		if( ptr->next > 0 )
			GroundObjects.objects[ptr->next].prev = pgo->index;
		i = pgo->index;
		if( nextnode == ptr->index )
			nextnode = i;
		CopyMemory( pgo, ptr, sizeof(TGroundObject) );
		ptr->pAnim = pAnim;
		pgo->index = i;
		// if we have just moved the tail, set the tail to the new location
		if( GroundObjects.tail == GroundObjects.count )
			GroundObjects.tail = i;
	}
	ptr->prev = ptr->next = -1;
	GroundObjects.count--;
	return nextnode;
}  //  DeleteGroundObject


//	Free up some memory by deleting earliest offscreen ground objects
void FreeSomeGroundObjects( void )
{
	int  i,
		 c;
	RECT irc;

	if( GroundObjects.count <= MAX_GROUND_OBJECTS - GROUND_OBJECTS_BUFFER )
		return;

	c = GROUND_OBJECTS_BUFFER;
	i = GroundObjects.objects[0].next;
	do
	{
		ASSERT( i > 0 );
		if( !RectIntersect( &(the_map.screenrect), &(GroundObjects.objects[i].pAnim->wrect), &irc) )
		{
			i = DeleteGroundObject( &(GroundObjects.objects[i]) );
			c--;
			if( c <= 0 )
				break;
		}
		else
			i = GroundObjects.objects[i].next;
	} while( i > 0 );

	i = GroundObjects.objects[0].next;
	while( c > 0 )
	{
		ASSERT( i > 0 );
		i = DeleteGroundObject( &(GroundObjects.objects[i]) );
		c--;
	}
}  //  FreeSomeGroundObjects


#ifdef _DEBUG
//	debug routine
void PrintGroundObjectsList( void )
{
	int i;

	printf("Ground objects list (%d items) listed in order of creation.\n", GroundObjects.count );
	i = GroundObjects.objects[0].next;
	while( i > 0 )
	{
		printf("%d\n", GroundObjects.objects[i].index );
		i = GroundObjects.objects[i].next;
	}
}  //  PrintGroundObjectsList
#endif


//	Allocate the ground objects array
void InitCorpseObjects( void )
{
	ANIMCELL *pAnim;

	CorpseObjects.count = CorpseObjects.tail = 0;
	for( int i = 0; i < MAX_CORPSE_OBJECTS; i++ )
	{
		CorpseObjects.objects[i].index = i;
		CorpseObjects.objects[i].prev = CorpseObjects.objects[i].next = -1;
		pAnim = CorpseObjects.objects[i].pAnim = (ANIMCELL *)malloc(sizeof(ANIMCELL));
		ZeroMemory( pAnim, sizeof(ANIMCELL) );
		pAnim->flags = ~ANIM_FLAG_ACTIVE;
		pAnim->flags |= ANIM_FLAG_CELL;
		CreateDispXObject( 128, 128, pAnim, OL_GROUNDLAYER );
	}
}  //  InitCorpseObjects


//  Clear the corpse objects array & free up associated memory
void FreeCorpseObjects( void )
{
	for( int i = 0; i < MAX_CORPSE_OBJECTS; i++ )
	{
		if (CorpseObjects.objects[i].pAnim)
		{
			AnimDelete( (ANIM *)(CorpseObjects.objects[i].pAnim) );
			free( CorpseObjects.objects[i].pAnim );
			CorpseObjects.objects[i].pAnim = NULL;
		}
		CorpseObjects.objects[i].prev = CorpseObjects.objects[i].next = -1;
	}
	CorpseObjects.count = CorpseObjects.tail = 0;
}  //  FreeCorpseObjects


//	Insert a new corpse object
PCorpseObject InsertCorpseObject( void )
{
	int i;

	if( CorpseObjects.count > MAX_CORPSE_OBJECTS - CORPSE_OBJECTS_BUFFER )
		FreeSomeCorpseObjects();

	i = ++CorpseObjects.count;
	CorpseObjects.objects[i].index = i;
	CorpseObjects.objects[i].prev = CorpseObjects.tail;
	CorpseObjects.objects[i].next = -1;
	CorpseObjects.objects[CorpseObjects.tail].next = i;
	CorpseObjects.tail = i;
	return( &(CorpseObjects.objects[i]) );
}  //  InsertCorpseObject


//  Delete a ground object
int DeleteCorpseObject( PCorpseObject pco )
{
	PCorpseObject ptr;
	int i, nextnode;
	ANIMCELL *pAnim;	

	ASSERT( pco->index > 0 );
	ASSERT( pco->prev >= 0 );

	// delete the current dispnode
	pAnim = pco->pAnim;
	if( pAnim->flags & ANIM_FLAG_ACTIVE )
	{
		pAnim->flags &= ~ANIM_FLAG_ACTIVE;
		MoveDispXObject( pAnim, FALSE );
	}
	// point "around" the node we are deleting
	CorpseObjects.objects[pco->prev].next = nextnode = pco->next;
	if( pco->next > 0 )
		CorpseObjects.objects[pco->next].prev = pco->prev;
	// if we are deleting the tail, set the new tail
	if( CorpseObjects.tail == pco->index )
		CorpseObjects.tail = pco->prev;
	ptr = &( CorpseObjects.objects[CorpseObjects.count] );
	if( pco->index != CorpseObjects.count )
	{
		// move objects[count] into vacated space
		CorpseObjects.objects[ptr->prev].next = pco->index;
		if( ptr->next > 0 )
			CorpseObjects.objects[ptr->next].prev = pco->index;
		i = pco->index;
		if( nextnode == ptr->index )
			nextnode = i;
		CopyMemory( pco, ptr, sizeof(TCorpseObject) );
		ptr->pAnim = pAnim;
		pco->index = i;
		// if we have just moved the tail, set the tail to the new location
		if( CorpseObjects.tail == CorpseObjects.count )
			CorpseObjects.tail = i;
	}
	ptr->prev = ptr->next = -1;
	CorpseObjects.count--;
	return nextnode;
}  //  DeleteCorpseObject


//	Free up some memory by deleting earliest offscreen corpse objects
void FreeSomeCorpseObjects( void )
{
	int  i,
		 c;
	RECT irc;

	if( CorpseObjects.count <= MAX_CORPSE_OBJECTS - CORPSE_OBJECTS_BUFFER )
		return;

	c = CORPSE_OBJECTS_BUFFER;
	i = CorpseObjects.objects[0].next;
	do
	{
		ASSERT( i > 0 );
		if( !RectIntersect( &(the_map.screenrect), &(CorpseObjects.objects[i].pAnim->wrect), &irc ))
		{
			i = DeleteCorpseObject( &(CorpseObjects.objects[i]) );
			c--;
			if( c <= 0 )
				break;
		}
		else
			i = CorpseObjects.objects[i].next;
	} while( i > 0 );

	i = CorpseObjects.objects[0].next;
	while( c > 0 )
	{
		ASSERT( i > 0 );
		i = DeleteCorpseObject( &(CorpseObjects.objects[i]) );
		c--;
	}
}  //  FreeSomeCorpseObjects


//	Allocate the world objects array
void InitWorldObjects( TWorldObjectsArray &obj_array, int max_objs, int buffer_size, 
					   int max_xsize, int max_ysize, EObjectLayer elayer )
{
	ANIMCELL *pAnim;

	obj_array.max = max_objs;
	obj_array.buffer = buffer_size;
	obj_array.count = obj_array.tail = 0;
	ASSERT( obj_array.objects == NULL );

	obj_array.objects = (PWorldObject)malloc( sizeof(TWorldObject) * max_objs );
	for( int i = 0; i < max_objs; i++ )
	{
		obj_array.objects[i].index = i;
		obj_array.objects[i].prev = obj_array.objects[i].next = -1;
		pAnim = obj_array.objects[i].pAnim = (ANIMCELL *)malloc(sizeof(ANIMCELL));
		ZeroMemory( pAnim, sizeof(ANIMCELL) );
		pAnim->flags = ~ANIM_FLAG_ACTIVE;
		pAnim->flags |= ANIM_FLAG_CELL;
		CreateDispXObject( max_xsize, max_ysize, pAnim, elayer );
	}
}  //  InitWorldObjects


//  Clear the world objects array & free up associated memory
void FreeWorldObjects( TWorldObjectsArray &obj_array )
{
	if( !obj_array.objects )
		return;

	for( int i = 0; i < obj_array.max; i++ )
	{
		if (obj_array.objects[i].pAnim)
		{
			AnimDelete( (ANIM *)(obj_array.objects[i].pAnim) );
			free( obj_array.objects[i].pAnim );
			obj_array.objects[i].pAnim = NULL;
		}
		obj_array.objects[i].prev = obj_array.objects[i].next = -1;
	}
	free( obj_array.objects );
	obj_array.objects = NULL;
	obj_array.count = obj_array.tail = 0;
	obj_array.max = obj_array.buffer = 0;
}  //  FreeWorldObjects


//	Insert a new world object
PWorldObject InsertWorldObject( TWorldObjectsArray &obj_array )
{
	int i;

	if( obj_array.count > obj_array.max - obj_array.buffer)
		FreeSomeWorldObjects( obj_array );

	i = ++obj_array.count;
	obj_array.objects[i].index = i;
	obj_array.objects[i].prev = obj_array.tail;
	obj_array.objects[i].next = -1;
	obj_array.objects[obj_array.tail].next = i;
	obj_array.tail = i;
	return( &(obj_array.objects[i]) );
}  //  InsertWorldObject


//  Delete a world object
int DeleteWorldObject( TWorldObjectsArray &obj_array, PWorldObject pwo )
{
	PWorldObject ptr;
	int i, nextnode;
	ANIMCELL *pAnim;	

	ASSERT( pwo->index > 0 );
	ASSERT( pwo->prev >= 0 );

	// delete the current dispnode
	pAnim = pwo->pAnim;
	if( pAnim->flags & ANIM_FLAG_ACTIVE )
	{
		pAnim->flags &= ~ANIM_FLAG_ACTIVE;
		MoveDispXObject( pAnim, FALSE );
	}
	// point "around" the node we are deleting
	obj_array.objects[pwo->prev].next = nextnode = pwo->next;
	if( pwo->next > 0 )
		obj_array.objects[pwo->next].prev = pwo->prev;
	// if we are deleting the tail, set the new tail
	if( obj_array.tail == pwo->index )
		obj_array.tail = pwo->prev;
	ptr = &( obj_array.objects[obj_array.count] );
	if( pwo->index != obj_array.count )
	{
		// move objects[count] into vacated space
		obj_array.objects[ptr->prev].next = pwo->index;
		if( ptr->next > 0 )
			obj_array.objects[ptr->next].prev = pwo->index;
		i = pwo->index;
		if( nextnode == ptr->index )
			nextnode = i;
		CopyMemory( pwo, ptr, sizeof(TWorldObject) );
		ptr->pAnim = pAnim;
		pwo->index = i;
		// if we have just moved the tail, set the tail to the new location
		if( obj_array.tail == obj_array.count )
			obj_array.tail = i;
	}
	ptr->prev = ptr->next = -1;
	obj_array.count--;
	return nextnode;
}  //  DeleteWorldObject


//	Free up some memory by deleting earliest offscreen world objects
void FreeSomeWorldObjects( TWorldObjectsArray &obj_array )
{
	int  i,
		 c;
	RECT irc;

	if( obj_array.count <= obj_array.max - obj_array.buffer )
		return;

	c = obj_array.buffer;
	i = obj_array.objects[0].next;
	do
	{
		ASSERT( i > 0 );
		if( !RectIntersect( &(the_map.screenrect), &(obj_array.objects[i].pAnim->wrect), &irc) )
		{
			i = DeleteWorldObject( obj_array, &(obj_array.objects[i]) );
			c--;
			if( c <= 0 )
				break;
		}
		else
			i = obj_array.objects[i].next;
	} while( i > 0 );

	i = obj_array.objects[0].next;
	while( c > 0 )
	{
		ASSERT( i > 0 );
		i = DeleteWorldObject( obj_array, &(obj_array.objects[i]) );
		c--;
	}
}  //  FreeSomeWorldObjects


void LoadBodyPartGraphics( void )
{
	EBodyParts	ebp;
	int			i;

	if( !_LOAD_FROM_DATAFILE )
		SetPath(BODYPARTS_PATH);
	for( ebp = (EBodyParts)0; ebp < EBP_LastPart; ebp = EBodyParts((int)ebp + 1) )
	{
		if (!BodyPartsData[ebp].sprites)
		{
			BodyPartsData[ebp].sprites = (PSPRITE *)malloc( BodyPartsData[ebp].num_frames * sizeof(PSPRITE) );
			ZeroMemory( BodyPartsData[ebp].sprites, BodyPartsData[ebp].num_frames * sizeof(PSPRITE) );
			for( i = 0; i < BodyPartsData[ebp].num_frames; i++ )
			{
				AcquireWobjectSprite( BodyPartsData[ebp].sprites[i],
					CAT_BODYPARTS, BodyPartsData[ebp].number, i+1,
					BodyPartsData[ebp].filename, 
					BM_TRANSPARENT | BM_TRLE_ONLOAD | BM_NOTRANSLATE );
			}
		}
	}
}


void FreeBodyPartGraphics( void )
{
	EBodyParts	ebp;

	for( ebp = (EBodyParts)0; ebp < EBP_LastPart; ebp = EBodyParts((int)ebp + 1) )
	{
		if( BodyPartsData[ebp].sprites )
		{
			for( int i = 0; i < BodyPartsData[ebp].num_frames; i++ )
				ReleaseWobjectSprite( BodyPartsData[ebp].sprites[i] );
		}
		free( BodyPartsData[ebp].sprites );
		BodyPartsData[ebp].sprites = NULL;
	}
}


int ProcessBodyPart( int i, PWorldObject pwo, TWorldObjectsArray &obj_array )
{
	ANIMCELL		*pAnim;
	int				tile;
	PGroundObject	pgo;
	ANIMCELL		*pGroundAnim;

	pAnim = pwo->pAnim;
	pwo->dwAnimTime += gpGame->dwDeltaTime;
	if( pwo->dwAnimTime > pwo->speed )
	{
		if( pwo->z_velocity != 0 )
		{
			pwo->frame++;
			if( pwo->frame >= BodyPartsData[pwo->sub_type.part].num_frames )
				pwo->frame = 0;
			pAnim->pSprite = BodyPartsData[pwo->sub_type.part].sprites[pwo->frame];
		}
		pAnim->world_pos.x += pwo->x_velocity;
		pAnim->world_pos.y += pwo->y_velocity;
		pAnim->world_z += pwo->z_velocity;
		SPOINT pt;

		pt = pAnim->world_pos;
		pt.y -= pAnim->world_z;
		if( !(InRect(&(the_map.limitboundrect), &pt)) )
		{
			return( DeleteWorldObject( obj_array, pwo ) );
		}
		if( pAnim->world_z <= 0 )
		{
			pAnim->world_z = 0;
			
			tile = ((pAnim->world_pos.y >> 4) << the_map.bitwidth) + (pAnim->world_pos.x >> 4);
			if( the_map.triggers[tile] & TRIGGER_WATER )
			{
				DoExplosion( pAnim->world_pos.x, pAnim->world_pos.y, EXPLOSION_WATER_GUN_PUFF_S_COMMAND,
					&SmallExplosion, DMGTYPE_OTHER_EXPLOSION, 0, NULL, 0, 0, WATER_HIT); 
				return( DeleteWorldObject( obj_array, pwo ) );
			}
			else
			{
				if( pwo->z_velocity < -4 )
				{
					pwo->z_velocity = abs(pwo->z_velocity) - 3;
				}
				else
				{
					// move it to the ground layer!
					pAnim = pwo->pAnim;
					pgo = InsertGroundObject();
					pGroundAnim = pgo->pAnim;
					pGroundAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
					pGroundAnim->pSprite = pAnim->pSprite;
					pGroundAnim->world_pos.x = pAnim->world_pos.x;
					pGroundAnim->world_pos.y = pAnim->world_pos.y;
					pGroundAnim->trans_table =	pAnim->trans_table;
					pGroundAnim->order = 3500;
//					MoveDispXObject( pAnim, FALSE );
					MoveDispXObject( pGroundAnim, FALSE );
					return( DeleteWorldObject( obj_array, pwo ) );
				}
			}
		}
		else 				
			pwo->z_velocity--;			
		pwo->dwAnimTime = 0;
	}
	AnimWorldBoundary( (ANIM *)pAnim );
	MoveDispXObject( pAnim, FALSE );
	return( pwo->next );
}	//	ProcessBodyPart


void StartExplodingTrooperPiece( SPOINT &pt, BYTE *pTransTable, EBodyParts ebp, int velocity_factor, int pdir = -1 )
{
	PWorldObject	pwo;
	ANIMCELL		*pAnim;
	int				half_velocity;

	if( !(InRect(&(the_map.limitboundrect), &pt)) )
		return;
	pwo = InsertWorldObject( WorldObjects);
	pwo->wo_type = WOT_BodyPart;
	pwo->sub_type.part = ebp;
	pwo->frame = 0;
	pwo->dwAnimTime = 0;
	half_velocity = velocity_factor >> 1;
	if( pdir < 0 )
	{
		pwo->x_velocity = rand() % velocity_factor - half_velocity;
		pwo->y_velocity = rand() % velocity_factor - half_velocity;
	}
	else
	{
		pwo->x_velocity = (int)(velocity_factor * cos_table[pdir]);
		pwo->y_velocity = (int)(velocity_factor * sin_table[pdir]);
	}
	pwo->z_velocity = rand() % half_velocity + half_velocity;
	pwo->speed = rand() % 75 + 25;
	pwo->uidAnchor = 0;
	pAnim = pwo->pAnim;
	pAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pAnim->pSprite = BodyPartsData[ebp].sprites[0];
	pAnim->world_pos.x = pt.x + BodyPartsData[ebp].x;
	pAnim->world_pos.y = pt.y + BodyPartsData[ebp].y;
	pAnim->world_z =  BodyPartsData[ebp].z;
	pAnim->order = 0;
	pAnim->trans_table = pTransTable;
}

void GenerateExplodingAvatar( AVATAR * pAvatar )
{
	EBodyParts	ebp;
	int			i, n;

	for( ebp = (EBodyParts)0; ebp < EBP_Torso; ebp = EBodyParts((int)ebp + 1) )
	{
		StartExplodingTrooperPiece( pAvatar->pAnimation->world_pos, pAvatar->pAnimation->trans_table, ebp, 9 );
	}
	n = rand() % 5 + 6;
	for( i = 0; i < n; i++ )
	{
		ebp = (EBodyParts)(rand() % 3 + (int)EBP_Part1);
		StartExplodingTrooperPiece( pAvatar->pAnimation->world_pos, pAvatar->pAnimation->trans_table, ebp, 9 );
	}
}	//	GenerateExplodingAvatar


void LoadVehiclePartGraphics( void )
{
	EVehicleParts	evp;
	int				i;

	if( !_LOAD_FROM_DATAFILE )
		SetPath(BODYPARTS_PATH);

	for( evp = (EVehicleParts)0; evp < EVP_LastPart; evp = EVehicleParts((int)evp + 1) )
	{
		if (!VehiclePartsData[evp].sprites)
		{
			VehiclePartsData[evp].sprites = (PSPRITE *)malloc( VehiclePartsData[evp].num_frames * sizeof(PSPRITE) );
			ZeroMemory( VehiclePartsData[evp].sprites, VehiclePartsData[evp].num_frames * sizeof(PSPRITE) );
			for( i = 0; i < VehiclePartsData[evp].num_frames; i++ )
			{
				AcquireWobjectSprite( VehiclePartsData[evp].sprites[i],
					CAT_BODYPARTS, VehiclePartsData[evp].number, i+1,
					VehiclePartsData[evp].filename, 
					BM_TRANSPARENT | BM_TRLE_ONLOAD | BM_NOTRANSLATE );
			}
		}
	}
}


void FreeVehiclePartGraphics( void )
{
	EVehicleParts	evp;

	for( evp = (EVehicleParts)0; evp < EVP_LastPart; evp = EVehicleParts((int)evp + 1) )
	{
		if( VehiclePartsData[evp].sprites )
		{
			for( int i = 0; i < VehiclePartsData[evp].num_frames; i++ )
				ReleaseWobjectSprite( VehiclePartsData[evp].sprites[i] );
		}
		free( VehiclePartsData[evp].sprites );
		VehiclePartsData[evp].sprites = NULL;
	}
}


int ProcessVehiclePart( int i, PWorldObject pwo, TWorldObjectsArray &obj_array )
{
	ANIMCELL		*pAnim;
	int				tile;
	PGroundObject	pgo;
	ANIMCELL		*pGroundAnim;

	pAnim = pwo->pAnim;
	pwo->dwAnimTime += gpGame->dwDeltaTime;
	if( pwo->dwAnimTime > pwo->speed )
	{
		if( pwo->z_velocity != 0 )
		{
			pwo->frame++;
			if( pwo->frame >= VehiclePartsData[pwo->sub_type.vpart].num_frames )
				pwo->frame = 0;
			pAnim->pSprite = VehiclePartsData[pwo->sub_type.vpart].sprites[pwo->frame];
		}
		pAnim->world_pos.x += pwo->x_velocity;
		pAnim->world_pos.y += pwo->y_velocity;
		pAnim->world_z += pwo->z_velocity;
		SPOINT pt;

		pt = pAnim->world_pos;
		pt.y -= pAnim->world_z;
		if( !(InRect(&(the_map.limitboundrect), &pt)) )
		{
			return( DeleteWorldObject( obj_array, pwo ) );
		}
		if( pAnim->world_z <= 0 )
		{
			pAnim->world_z = 0;
			
			tile = ((pAnim->world_pos.y >> 4) << the_map.bitwidth) + (pAnim->world_pos.x >> 4);
			if( the_map.triggers[tile] & TRIGGER_WATER )
			{
				DoExplosion( pAnim->world_pos.x, pAnim->world_pos.y, EXPLOSION_WATER_GUN_PUFF_S_COMMAND,
					&SmallExplosion, DMGTYPE_OTHER_EXPLOSION, 0, NULL, 0, 0, WATER_HIT ); 
				return( DeleteWorldObject( obj_array, pwo ) );
			}
			else
			{
				if( pwo->z_velocity < -4 )
				{
					pwo->z_velocity = abs(pwo->z_velocity) - 3;
				}
				else
				{
					// move it to the ground layer!
					pAnim = pwo->pAnim;
					pgo = InsertGroundObject();
					pGroundAnim = pgo->pAnim;
					pGroundAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
					pGroundAnim->pSprite = pAnim->pSprite;
					pGroundAnim->world_pos.x = pAnim->world_pos.x;
					pGroundAnim->world_pos.y = pAnim->world_pos.y;
					pGroundAnim->wrect.left = 0;
					pGroundAnim->wrect.right = 0;
					pGroundAnim->wrect.top = 0;
					pGroundAnim->wrect.bottom = 0;
					pGroundAnim->trans_table =	pAnim->trans_table;
					pGroundAnim->order = 3500;
					MoveDispXObject( pAnim, FALSE );
					MoveDispXObject( pGroundAnim, FALSE );
					return( DeleteWorldObject( obj_array, pwo ) );
				}
			}
		}
		else 				
			pwo->z_velocity--;			
		pwo->dwAnimTime = 0;
	}
	AnimWorldBoundary( (ANIM *)pAnim );
	MoveDispXObject( pAnim, FALSE );
	return( pwo->next );
}	//	ProcessVehiclePart


void StartExplodingVehiclePiece( SPOINT &pt, BYTE *pTransTable, EVehicleParts evp, int velocity_factor )
{
	PWorldObject	pwo;
	ANIMCELL		*pAnim;
	int				half_velocity;

	if( !(InRect(&(the_map.limitboundrect), &pt)) )
		return;
	pwo = InsertWorldObject( WorldObjects);
	pwo->wo_type = WOT_VehiclePart;
	pwo->sub_type.vpart = evp;
	pwo->frame = 0;
	pwo->dwAnimTime = 0;
	half_velocity = velocity_factor >> 1;
	pwo->x_velocity = rand() % velocity_factor - half_velocity;
	pwo->y_velocity = rand() % velocity_factor - half_velocity;
	pwo->z_velocity = rand() % half_velocity + half_velocity;
	pwo->speed = rand() % 75 + 25;
	pwo->uidAnchor = 0;
	pAnim = pwo->pAnim;
	pAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pAnim->pSprite = VehiclePartsData[evp].sprites[0];
	pAnim->world_pos.x = pt.x + VehiclePartsData[evp].x;
	pAnim->world_pos.y = pt.y + VehiclePartsData[evp].y;
	pAnim->world_z =  VehiclePartsData[evp].z;
	pAnim->order = 0;
	pAnim->trans_table = pTransTable;
}


void GenerateExplodingVehicle( int type, SPOINT &pos, BYTE *trans_table, int facing )
{
	EVehicleParts	evp;
	int				i, n, sprite_facing;;
	PCorpseObject	pco;
	ANIMCELL		*pCorpseAnim;

	// generate the corpse remains
	switch( type )					// determine corpse type
	{
	case ARMY_JEEP:
		evp = EVP_jded;
		break;
	case ARMY_TANK:
		evp = EVP_tded;
		break;
	default:
		evp = EVP_hded;
		break;
	}
	switch( facing >> 3 )			// determine facing
	{
	case  0:						// 0, 16, 31
	case 16:
	case 31:
		sprite_facing = 0;
		break;
	case  1:						// 1-5, 17-21
	case  2:
	case  3:
	case  4:
	case  5:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
		sprite_facing = 1;
		break;
	case  6:						// 6-8, 22-24
	case  7:
	case  8:
	case 22:
	case 23:
	case 24:
		sprite_facing = 2;
		break;
	default:
		sprite_facing = 3;			// 9-15, 25-30
		break;
	}
	pco = InsertCorpseObject();
	pCorpseAnim = pco->pAnim;
	pCorpseAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pCorpseAnim->pSprite = VehiclePartsData[evp].sprites[sprite_facing];
	pCorpseAnim->world_pos.x = pos.x;
	pCorpseAnim->world_pos.y = pos.y;
	pCorpseAnim->trans_table =	trans_table;
	pCorpseAnim->order = 3500;
	MoveDispXObject( pCorpseAnim, FALSE );

	// generate random flying pieces
	for( evp = (EVehicleParts)EVP_aaaa; evp < EVP_LastPart; evp = EVehicleParts((int)evp + 1) )
	{
		switch( evp )
		{
		case EVP_part1:
		case EVP_part2:
		case EVP_part3:
			n = rand() % 2 + 3;
			break;
		case EVP_jeep:
			n = 0;
			break;
		default:
			n = rand() % 2 + 2;
		}

		for( i = 0; i < n; i++ )
			StartExplodingVehiclePiece( pos, trans_table, evp, 11 );
	}
}	//	GenerateExplodingVehicle


void GenerateDeadVehicleParts( int type, SPOINT &pos, BYTE *trans_table )
{
	switch( type )
	{
	case ARMY_JEEP:
		StartExplodingVehiclePiece( pos, trans_table, EVP_jeep, 11 );
		StartExplodingVehiclePiece( pos, trans_table, EVP_jeep, 9 );
		break;
	}
}	//  GenerateDeadVehicleParts


void MakeChips( SPOINT &pt, BYTE *trans_table, int facing )
{
	EBodyParts ebp;
	int n;
	int nChips[10] =
		{1, 1, 1, 1, 1, 1, 2, 2, 2, 3};

	n = nChips[rand() % 10];
	for( int i = 0; i < n; i++ )
	{
		ebp = (EBodyParts)(rand() %3 + (int)EBP_Part1);
		StartExplodingTrooperPiece( pt, trans_table, ebp, 11 );
	}
}


void ShotDeathStandParts( SPOINT &pt, int facing, BYTE * trans_table )
{
	int PartsToBlow[8][7] =				// parts that fall off for each direction
	{
		{1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0},
		{0, 1, 0, 1, 1, 0, 0},
		{0, 1, 0, 1, 1, 1, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1, 1, 0},
		{1, 1, 0, 0, 1, 1, 0}
	};
	int PrefDir[7] =					// direction each part goes (-1 == random)
	{
		64, -64, -1, 0, -100, -154, -1
	};

	int i, dir, pdir;

	dir = (facing + 16) >> 5;
	if( dir < 0 || dir > 7 )
		return;

	for( i = 0; i < 7; i++ )
	{
		if( PartsToBlow[dir][i] )
		{
			if( PrefDir[i] != -1 )
			{
				pdir = dir + PrefDir[i];
				if( pdir < 0 )
					pdir += 256;
				else if( pdir >= 256 )
					pdir -= 256;
				StartExplodingTrooperPiece( pt, trans_table, (EBodyParts)i, 7, pdir );
			}
			else						// no preferred direction
				StartExplodingTrooperPiece( pt, trans_table, (EBodyParts)i, 7 );
		}
	}
}


void InsertAnimInGroundLayer( ANIM *pAnim )
{
	PGroundObject	pgo;
	ANIMCELL		*pGroundAnim;

	pgo = InsertGroundObject();
	pGroundAnim = pgo->pAnim;
	pGroundAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pGroundAnim->pSprite = pAnim->pSprite;
	pGroundAnim->world_pos = pAnim->world_pos;
	pGroundAnim->trans_table =	pAnim->trans_table;
	pGroundAnim->order = 2500;
	MoveDispXObject( pGroundAnim, FALSE );
}	//	InsertAnimInGroundLayer


void InsertAnimInCorpseLayer( ANIM *pAnim )
{
	PCorpseObject	pco;
	ANIMCELL		*pCorpseAnim;

	pco = InsertCorpseObject();
	pCorpseAnim = pco->pAnim;
	pCorpseAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pCorpseAnim->pSprite = pAnim->pSprite;
	pCorpseAnim->world_pos = pAnim->world_pos;
	pCorpseAnim->trans_table =	pAnim->trans_table;
	pCorpseAnim->order = 2500;
	MoveDispXObject( pCorpseAnim, FALSE );
}	//	InsertAnimInGroundLayer


void LoadMuzzleFlashGraphics( void )
{
	if( !_LOAD_FROM_DATAFILE )
		SetPath(FLASH_PATH);

	for(int t = 0; t < EFT_LastFlash; t++ )
	{
		if (!MuzzleFlashData[t].sprites)
		{
			int n;

			n = MuzzleFlashData[t].num_directions;
			MuzzleFlashData[t].sprites = (PSPRITE *)malloc( n * sizeof(PSPRITE) );
			ZeroMemory( MuzzleFlashData[t].sprites, n * sizeof(PSPRITE) );

			for( int i = 0; i < MuzzleFlashData[t].num_directions; i++ )
			{
				AcquireWobjectSprite( MuzzleFlashData[t].sprites[i],
					CAT_MUZZLEFLASH, MuzzleFlashData[t].number, i+1,
					MuzzleFlashData[t].filename, 
					BM_TRANSPARENT | BM_DRLE_ONLOAD );
			}
		}
	}
}	//	LoadMuzzleFlashGraphics


void FreeMuzzleFlashGraphics( void )
{
	for( int t = 0; t < EFT_LastFlash; t++ )
	{
		if( MuzzleFlashData[t].sprites )
		{
			int n = MuzzleFlashData[t].num_directions;
			for( int i = 0; i < n; i++ )
				ReleaseWobjectSprite( MuzzleFlashData[t].sprites[i] );
			free( MuzzleFlashData[t].sprites );
			MuzzleFlashData[t].sprites = NULL;
		}
	}
}	//	FreeMuzzleFlashGraphics


void MakeMuzzleFlash( int x, int y, int facing, int type, UID uidAnchor )
{
	PWorldObject	pwo;
	ANIMCELL		*pAnim;
	int				res;

	pwo = InsertWorldObject( FlashObjects );
	pwo->wo_type = WOT_MuzzleFlash;
	pwo->sub_type.index = type;
	pwo->frame = 0;
	pwo->dwAnimTime = 0;
	pwo->x_velocity = 0;
	pwo->y_velocity = 0;
	pwo->uidAnchor = uidAnchor;
	res = 256 / MuzzleFlashData[type].num_directions;
	facing = (facing + (res >> 1)) / res;
	if( facing >= MuzzleFlashData[type].num_directions )
		facing -= MuzzleFlashData[type].num_directions;
	pwo->z_velocity = facing;
	pwo->speed = MuzzleFlashData[type].playspeed;
	pAnim = pwo->pAnim;
	pAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pAnim->pSprite = MuzzleFlashData[type].sprites[facing];
	pAnim->world_pos.x = x;
	pAnim->world_pos.y = y;
	pAnim->world_z = 0;
	pAnim->order = 0;
	pAnim->trans_table = NULL;
}	//  MakeMuzzleFlash


ANIM *GetAnimFromUID( UID uidAnchor )
{
	ITEM	*pItem = AiItemFind( uidAnchor );
	VEHICLE	*pVehicle;

	if( !pItem )
		return NULL;

	switch( ITEM_TYPE(pItem) )
	{
	case ARMY_SARGE:
		if( !((SARGE *)pItem)->pAvatar )
			return NULL;
		return( ((SARGE *)pItem)->pAvatar->pAnimation );
	case ARMY_VEHICLE:
		pVehicle = (VEHICLE *)pItem;
		if (pVehicle->bTurret)
			return( &pVehicle->pAnimation[TURRETANIM] );
		else
			return( pVehicle->pAnimation );
	case ARMY_TROOPER:
		if( !((TROOPER *)pItem)->pAvatar )
			return NULL;
		return( ((TROOPER *)pItem)->pAvatar->pAnimation );
	default:
		return NULL;
	}
}


int ProcessMuzzleFlash( int i, PWorldObject pwo, TWorldObjectsArray &obj_array )
{
	ANIMCELL	*pAnim;
	ANIM		*pAnchor;

	pAnim = pwo->pAnim;
	pAnchor = GetAnimFromUID( pwo->uidAnchor );

	if( pAnchor && (pAnchor->flags & ANIM_FLAG_ACTIVE) && (pAnchor->pFrame) )
	{
		pAnim->world_pos.x = pAnchor->world_pos.x + pAnchor->pFrame[pAnchor->current_frame].secondary_hotspot.x;
	}

	pwo->dwAnimTime += gpGame->dwDeltaTime;
	if( pwo->dwAnimTime > pwo->speed )
	{
		// delete the muzzle flash object
		if( pwo->sub_type.index == 1 )
		{
			DoExplosion( pAnim->world_pos.x, pAnim->world_pos.y, 
						 EXPLOSION_GUN_PUFF_M_COMMAND, &SmallExplosion, 
						 DMGTYPE_OTHER_EXPLOSION, 0, NULL, 0, 0, SND_NULL_SND_ID ); 
		}
		return( DeleteWorldObject( obj_array, pwo ) );
	}
	MoveDispXObject( pAnim, FALSE );

	return( pwo->next );
}	//	ProcessMuzzleFlash


void LoadFlameBurstGraphics( void )
{
	if( !_LOAD_FROM_DATAFILE )
		SetPath(FLASH_PATH);

	FlameBurstData.sprites = (PSPRITE *)malloc( 
		FlameBurstData.num_dirs * FlameBurstData.num_frames * sizeof(PSPRITE) );
	ZeroMemory( FlameBurstData.sprites, 
		FlameBurstData.num_dirs * FlameBurstData.num_frames * sizeof(PSPRITE) );

	for( int i = 0; i < FlameBurstData.num_dirs; i++ )
	{
		for( int j = 0; j < FlameBurstData.num_frames; j++ )
		{
			AcquireWobjectSprite( FlameBurstData.sprites[i * FlameBurstData.num_frames + j],
						CAT_FLAMEBURST, i+1, j+1,
						FlameBurstData.filename, 
						BM_TRANSPARENT | BM_DRLE_ONLOAD );
		}
	}
}	//	LoadFlameBurstGraphics


void FreeFlameBurstGraphics( void )
{
	if( FlameBurstData.sprites )
	{
		for( int i = 0; i < FlameBurstData.num_dirs; i++ )
			for( int j = 0; j < FlameBurstData.num_frames; j++ )
				ReleaseWobjectSprite( FlameBurstData.sprites[i * FlameBurstData.num_frames + j] );
		free( FlameBurstData.sprites );
		FlameBurstData.sprites = NULL;
	}
}	//	FreeFlameBurstGraphics


void DropFlamePoop( int x, int y, int dir, int frame )
{
	PWorldObject	pwo;
	ANIMCELL		*pAnim;

	pwo = InsertWorldObject( FlashObjects );
	pwo->wo_type = WOT_FlameBurst;
	pwo->sub_type.index = 0;
	pwo->frame = frame;
	pwo->dwAnimTime = 0;
	pwo->x_velocity = 0;
	pwo->y_velocity = 0;
	pwo->uidAnchor = 0;
	pwo->z_velocity = frame;
	pwo->speed = FlameBurstData.timing[frame];
	pAnim = pwo->pAnim;
	pAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pAnim->pSprite = FlameBurstData.sprites[dir * FlameBurstData.num_frames + frame];
	pAnim->world_pos.x = x;
	pAnim->world_pos.y = y;
	pAnim->world_z = 0;
	pAnim->trans_table = NULL;
	pAnim->order = (short)(gpGame->dwAnimTime & 0x7fff);
}	//  MakeFlameBurst


int ProcessFlameBurst( int i, PWorldObject pwo, TWorldObjectsArray &obj_array )
{
	ANIMCELL	*pAnim;

	pAnim = pwo->pAnim;
	if( pwo->dwAnimTime > 0 )
	{
		return( DeleteWorldObject( obj_array, pwo ) );
	}
	MoveDispXObject( pAnim, FALSE );
	pwo->dwAnimTime += gpGame->dwDeltaTime;

	return( pwo->next );
}	//	ProcessFlameBurst



void LoadScarGraphics( void )
{
	if( !_LOAD_FROM_DATAFILE )
		SetPath(FLASH_PATH);

	ScarData = (SPRITE **)malloc( NUM_SCAR_SPRITES * sizeof(SPRITE*) );
	ZeroMemory( ScarData, NUM_SCAR_SPRITES * sizeof(SPRITE*) );

	for( int i = 0; i < NUM_SCAR_SPRITES; i++ )
	{
		AcquireWobjectSpriteAsShadow( ScarData[i],
					CAT_SCAR, 1, i+1, "scar", PSHADE_TABLE );
	}
}


void FreeScarGraphics( void )
{
	if( ScarData )
	{
		for( int i = 0; i < NUM_SCAR_SPRITES; i++ )
			ReleaseWobjectSprite( ScarData[i] );
		free( ScarData );
		ScarData = NULL;
	}
}


void GenerateFlashBurn( int x, int y, int burn_index )
{
	PGroundObject	pgo;
	ANIMCELL		*pGroundAnim;

	pgo = InsertGroundObject();
	pGroundAnim = pgo->pAnim;
	pGroundAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pGroundAnim->pSprite = ScarData[burn_index];
	pGroundAnim->world_pos.x = x;
	pGroundAnim->world_pos.y = y;
	pGroundAnim->trans_table = ScarData[burn_index]->trans_table;
	pGroundAnim->order = 2000;
	MoveDispXObject( pGroundAnim, FALSE );
}	//  GenerateFlashBurn


void LoadMiscGraphics( void )
{
	Chevron = (SPRITE **)malloc( 2 * sizeof(SPRITE *) );

	if( !_LOAD_FROM_DATAFILE )
		SetPath( FLASH_PATH );

	AcquireWobjectSpriteAsShadow( Chevron[0], CAT_STRIPES, 1, 1, "strp", PLIGHT_TABLE );
	AcquireWobjectSpriteAsShadow( Chevron[1], CAT_STRIPES, 1, 2, "strp", PLIGHT_TABLE );

	if( gpGame->GameType != GAMETYPE_ONEPLAYER )
	{
		int i;

		Frags = (SPRITE **)malloc( ARMY_LAST_ARMY * 5 * sizeof(SPRITE *) );
		ZeroMemory( Frags, ARMY_LAST_ARMY * 5 * sizeof(SPRITE *) );
		for( i = 0; i < ARMY_LAST_ARMY; i++ )
		{
			for( int j = 0; j < 5; j++ )
				AcquireWobjectSprite( Frags[i*5+j], CAT_FRAGCOUNTER, i+1, j+1, "frag", BM_TRANSPARENT );
		}

		FragFlags = (SPRITE **)malloc( ARMY_LAST_ARMY * 1 * sizeof(SPRITE *) );
		ZeroMemory( FragFlags, ARMY_LAST_ARMY * 1 * sizeof(SPRITE *) );
		for( i = 0; i < ARMY_LAST_ARMY; i++ )
		{
			for( int j = 0; j < 1; j++ )
				AcquireWobjectSprite( FragFlags[i*1+j], CAT_FLAG, i+1, j+1, "flag", BM_TRANSPARENT );
		}
	}
}	//	LoadMiscGraphics



void FreeMiscGraphics( void )
{
	int i;

	if( Chevron )
	{
		for( i = 0; i < 2; i++ )
			ReleaseWobjectSprite( Chevron[i] );
		free( Chevron );
		Chevron = 0;
	}

	if( gpGame->GameType != GAMETYPE_ONEPLAYER )
	{
		if( Frags )
		{
			for( i = 0; i < ARMY_LAST_ARMY; i++ )
				for( int j = 0; j < 5; j++ )
					ReleaseWobjectSprite( Frags[i*5+j] );
			free( Frags );
			Frags = 0;
		}
		if( FragFlags )
		{
			for( i = 0; i < ARMY_LAST_ARMY; i++ )
				for( int j = 0; j < 1; j++ )
					ReleaseWobjectSprite( FragFlags[i*1+j] );
			free( FragFlags );
			FragFlags = 0;
		}
	}
}	//	FreeMiscGraphics


extern BYTE *PDARK_TABLE[];

void LoadSmokeGraphics( void )
{
	if( !_LOAD_FROM_DATAFILE )
		SetPath(FLASH_PATH);

	SmokeData = (SPRITE **)malloc( 4 * sizeof(SPRITE *) );
	ZeroMemory( SmokeData, 4 * sizeof(SPRITE *) );
	for( int i = 0; i < 4; i++ )
	{
		AcquireWobjectSpriteAsShadow( SmokeData[i],
			CAT_SMOKE, 1, i+1, "smok", PDARK_TABLE[i] );
	}
}	//	LoadSmokeGraphics


void FreeSmokeGraphics( void )
{
	if( SmokeData )
	{
		for( int i = 0; i < 4; i++ )
			ReleaseWobjectSprite( SmokeData[i] );
		free( SmokeData );
		SmokeData = NULL;
	}
}	//  FreeSmokeGraphics


void LoadFlameGraphics( void )
{
	if( !_LOAD_FROM_DATAFILE )
	{
		char pathname[18];

		sprintf(pathname,"LoadObjects/%s/Misc", the_map.terrain_name);
		SetPath(pathname);
	}

	FireData.sprites = (SPRITE **)malloc( FireData.num_types * FireData.num_frames * sizeof(SPRITE *) );
	ZeroMemory( FireData.sprites, FireData.num_types * FireData.num_frames * sizeof(SPRITE *) );

	for( int i = 0; i < FireData.num_types; i++ )
	{
		for( int j = 0; j < FireData.num_frames; j++ )
			AcquireWobjectSprite( FireData.sprites[i*FireData.num_frames+j], CAT_FIRE, i+1, j+1, "fire", BM_TRANSPARENT | BM_DRLE_ONLOAD );
	}
}	//	LoadFlameGraphics


void FreeFlameGraphics( void )
{
	int i, j;

	if( FireData.sprites )
	{
		for( i = 0; i < FireData.num_types; i++ )
		{
			for( j = 0; j < FireData.num_frames; j++ )
				ReleaseWobjectSprite( FireData.sprites[i*FireData.num_frames+j] );
		}
		free( FireData.sprites );
		FireData.sprites = NULL;
	}
}	//  FreeFlameGraphics


int smoke_move_time = 120;
DWORD smoke_frame_time[4] =
	{2, 3, 4, 5};
int smoke_ixvelocity = 3;
int smoke_iyvelocity = -1;
int smoke_izvelocity = 3;

void DropSmokePuff( SPOINT &pt, int z )
{
	PWorldObject	pwo;
	ANIMCELL		*pAnim;

	if( !(InRect(&(the_map.limitboundrect), &pt)) )
		return;
	pwo = InsertWorldObject( FlashObjects );
	pwo->wo_type = WOT_Smoke;
	pwo->sub_type.index = 0;
	pwo->frame = 0;
	pwo->dwAnimTime = 0;
	pwo->x_velocity = smoke_ixvelocity;
	pwo->y_velocity = smoke_iyvelocity;
	pwo->uidAnchor = 0;
	pwo->z_velocity = smoke_move_time;
	pwo->speed = 1;
	pAnim = pwo->pAnim;
	pAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pAnim->pSprite = SmokeData[0];
	pAnim->world_pos.x = pt.x;
	pAnim->world_pos.y = pt.y;
	pAnim->world_z = z;
	pAnim->trans_table = PDARK_TABLE[0];
	pAnim->order = 0x7ff0;
}	//  DropSmokePuff


int ProcessSmokePuff( int i, PWorldObject pwo, TWorldObjectsArray &obj_array )
{
	ANIMCELL	*pAnim;

	pAnim = pwo->pAnim;
	if( pwo->dwAnimTime > (DWORD)pwo->z_velocity )
	{
		pwo->speed++;
		if( pwo->speed > smoke_frame_time[pwo->frame] )
		{
			pwo->frame++;
			if( pwo->frame >= 4 )
				return( DeleteWorldObject( obj_array, pwo ) );
			pAnim->pSprite = SmokeData[pwo->frame];
			pAnim->trans_table = PDARK_TABLE[pwo->frame];
			pwo->speed = 1;
		}
		pAnim->world_z += smoke_izvelocity;
		pAnim->world_pos.x += pwo->x_velocity;
		pAnim->world_pos.y += pwo->y_velocity;
		pwo->dwAnimTime = 0;
		if( !(InRect(&(the_map.limitboundrect), &pAnim->world_pos)) )
		{
			return( DeleteWorldObject( obj_array, pwo ) );
		}
		MoveDispXObject( pAnim, FALSE );
	}
	pwo->dwAnimTime += gpGame->dwDeltaTime;

	return( pwo->next );
}	//	ProcessFlameBurst


void MakeSmokePlume( SPOINT &pt, UID fromUID )
{
	PWorldObject	pwo;
	ANIMCELL		*pAnim;

	if( !(InRect(&(the_map.limitboundrect), &pt)) )
		return;
	pwo = InsertWorldObject( WorldObjects );
	pwo->wo_type = WOT_Plume;
	pwo->sub_type.index = 0;
	pwo->frame = 0;
	pwo->dwAnimTime = 0;
	pwo->x_velocity = 0;
	pwo->y_velocity = 0;
	pwo->uidAnchor = fromUID;
	pwo->z_velocity = 9500;
	pwo->speed = 1;
	pAnim = pwo->pAnim;
	pAnim->flags = (ANIM_FLAG_CELL);
	pAnim->pSprite = SmokeData[0];
	pAnim->world_pos.x = pt.x;
	pAnim->world_pos.y = pt.y;
	pAnim->world_z = 0;
	pAnim->trans_table = NULL;
	pAnim->order = 0;
}	//	MakeSmokePlume


DWORD plumesmoketime = 300;

int	ProcessSmokePlume( int i, PWorldObject pwo, TWorldObjectsArray &obj_array )
{
	ANIMCELL	*pAnim;

	pAnim = pwo->pAnim;
	if( pwo->dwAnimTime > (DWORD)pwo->z_velocity )
	{
		return( DeleteWorldObject( obj_array, pwo ) );
	}
	if( pwo->speed > plumesmoketime )
	{
		SPOINT pos;
		pos = pAnim->world_pos;
		pos.x += ((rand() % 3) - 1) * 4;
		DropSmokePuff( pos, 15 );
		pwo->speed -= plumesmoketime;
	}
	pwo->dwAnimTime += gpGame->dwDeltaTime;
	pwo->speed += gpGame->dwDeltaTime;

	return( pwo->next );
}	//	ProcessSmokePlume


void MakeFlicker( SPOINT &pt, int sub_type )
{
	PWorldObject	pwo;
	ANIMCELL		*pAnim;

	if( !(InRect(&(the_map.limitboundrect), &pt)) )
		return;
	pwo = InsertWorldObject( WorldObjects );
	pwo->wo_type = WOT_Flicker;
	pwo->sub_type.index = sub_type;
	pwo->frame = 0;
	pwo->dwAnimTime = 0;
	pwo->x_velocity = 0;
	pwo->y_velocity = 0;
	pwo->uidAnchor = 0;
	pwo->z_velocity = 2000;
	pwo->speed = 1;
	pAnim = pwo->pAnim;
	pAnim->flags = (ANIM_FLAG_CELL | ANIM_FLAG_ACTIVE);
	pAnim->pSprite = FireData.sprites[sub_type * FireData.num_frames];
	pAnim->world_pos.x = pt.x;
	pAnim->world_pos.y = pt.y;
	pAnim->world_z = 0;
	pAnim->trans_table = NULL;
	pAnim->order = 0;
}	//  MakeFlicker


int	ProcessFlicker(  int i, PWorldObject pwo, TWorldObjectsArray &obj_array )
{
	ANIMCELL	*pAnim;

	pAnim = pwo->pAnim;
	if( pwo->dwAnimTime > (DWORD)pwo->z_velocity )
	{
		return( DeleteWorldObject( obj_array, pwo ) );
	}
	if( pwo->speed > FireData.timing )
	{
		int frame;

		frame = pwo->sub_type.index * FireData.num_frames;
		if( (int)pwo->dwAnimTime > (pwo->z_velocity - 100) )
		{
			int i;

			i = pwo->z_velocity - pwo->dwAnimTime;

			i = (100 - i)/(100 / FireData.num_dieoff);
			i = __min( i, FireData.num_dieoff-1 );
			frame += FireData.num_frames - FireData.num_dieoff + i;
		}
		else
		{
			if( ++pwo->frame >= FireData.num_frames - FireData.num_dieoff )
				pwo->frame = 0;
			frame += pwo->frame;
		}
		pAnim->pSprite = FireData.sprites[frame];
		MoveDispXObject( pAnim, FALSE );
		pwo->speed -= FireData.timing;
	}

	pwo->dwAnimTime += gpGame->dwDeltaTime;
	pwo->speed += gpGame->dwDeltaTime;

	return( pwo->next );
}	//  ProcessFlicker


void MakeFlame( SPOINT &pt, UID fromUID, int base, int height )
{
	PWorldObject	pwo;
	ANIMCELL		*pAnim;

	if( !(InRect(&(the_map.limitboundrect), &pt)) )
		return;
	pwo = InsertWorldObject( WorldObjects );
	pwo->wo_type = WOT_Flame;
	pwo->sub_type.index = 0;
	pwo->frame = 0;
	pwo->dwAnimTime = 0;
	if( base < 32 )
		base = 32;
	pwo->x_velocity = base;
	if( height < 32 )
		height = 32;
	pwo->y_velocity = height;
	pwo->uidAnchor = fromUID;
	pwo->z_velocity = 10000;
	pwo->speed = 1;
	pAnim = pwo->pAnim;
	pAnim->flags = (ANIM_FLAG_CELL);
	pAnim->pSprite = FireData.sprites[0];
	pAnim->world_pos.x = pt.x;
	pAnim->world_pos.y = pt.y;
	pAnim->world_z = 0;
	pAnim->trans_table = NULL;
	pAnim->order = 0;

	// make some smoke too!
	SPOINT spt;

	spt = pAnim->world_pos;
	MakeFlicker( pt, rand() % 3 );

	spt.x = pt.x;
	spt.y = pt.y - 32;
//	MakeSmokePlume( spt, fromUID );
}	//  MakeFlame


int	ProcessFlame(  int i, PWorldObject pwo, TWorldObjectsArray &obj_array )
{
	ANIMCELL	*pAnim;


	pAnim = pwo->pAnim;
	if( pwo->dwAnimTime > (DWORD)pwo->z_velocity )
	{
		return( DeleteWorldObject( obj_array, pwo ) );
	}
	if( pwo->speed > 500 )
	{
		SPOINT pt;
		int i, j;

		pt = pAnim->world_pos;
		i = rand() % 3;
		pt.y -= rand() % 16;
		j = rand() % 16 - 8;
		j = j * i;
		pt.x += j;
		MakeFlicker( pt, i );

		// do damage to vincinity
		if( IS_LOCAL_ARMY(EXTRACT_ARMY(pwo->uidAnchor)) )
		{
			ITEM *pItemList, *pNextItem;
			RECT queryRect;

			queryRect.left = pAnim->world_pos.x - 40;
			queryRect.right = queryRect.left + 80;
			queryRect.top = pAnim->world_pos.y - 64;
			queryRect.bottom = pAnim->world_pos.y + 16;
			pItemList = GetExplosionInfluence( queryRect );

			if( !pItemList )
				pwo->dwAnimTime = pwo->z_velocity;
			while( pItemList != NULL )
			{
				pNextItem = pItemList->next;
				ItemDamage( pItemList, 2, 
							DMGTYPE_FLAMED, &(pAnim->world_pos), pwo->uidAnchor );
				pItemList = pNextItem;
			}
		}
		pwo->speed -= 300;
	}

	pwo->dwAnimTime += gpGame->dwDeltaTime;
	pwo->speed += gpGame->dwDeltaTime;

	return( pwo->next );
}	//  ProcessFlame


int ParachutistsLoaded = 0;

void LoadParachuteGraphics( void )
{
	if( ParachutistsLoaded )
		return;

	ParatrooperData[0].sprites = (SPRITE **)malloc( ParatrooperData[0].num_frames * sizeof(SPRITE *) );
	ZeroMemory( ParatrooperData[0].sprites, ParatrooperData[0].num_frames * sizeof(SPRITE *) );

	if( !_LOAD_FROM_DATAFILE )
	{
		char pathname[18];

		sprintf(pathname,"LoadObjects/%s/Misc", the_map.terrain_name);
		SetPath(pathname);
	}

	for( int i = 0; i < ParatrooperData[0].num_frames; i++ )
		AcquireWobjectSprite( ParatrooperData[0].sprites[i], CAT_PARACHUTE, 1, i, "para", BM_TRANSPARENT | BM_DRLE_ONLOAD );

	ParachutistsLoaded = 1;
}	//	LoadParachuteGraphics


void FreeParachuteGraphics( void )
{
	if( ParatrooperData[0].sprites )
	{
		for( int i = 0; i < ParatrooperData[0].num_frames; i++ )
			ReleaseWobjectSprite( ParatrooperData[0].sprites[i] );

		free( ParatrooperData[0].sprites );
		ParatrooperData[0].sprites = 0;
	}
	ParachutistsLoaded = 0;
}	//  FreeParachuteGraphics


SPOINT fragPos[ARMY_LAST_ARMY] =
{
	{ 20, 8},
	{ 640-59-20, 8},
	{ 40+59, 8},
	{ 640-59-59-40, 8},
};


SPOINT fragFlagOffsets[ARMY_LAST_ARMY-1] =
{
	{ 45, 37 },
	{ 34, 37 },
	{ 23, 37 }
};


DWORD pauseflag[ARMY_LAST_ARMY] =
{
	PAUSE_LOCAL, PAUSE_REMOTE1, PAUSE_REMOTE2, PAUSE_REMOTE3
};

DWORD goneflag[ARMY_LAST_ARMY] =
{
	0, PAUSE_REMOTEGONE1, PAUSE_REMOTEGONE2, PAUSE_REMOTEGONE3
};

DWORD mappause[ARMY_LAST_ARMY] =
{
	PAUSE_MAPLOAD, PAUSE_MAPLOAD1, PAUSE_MAPLOAD2, PAUSE_MAPLOAD3
};


void DrawFragCounters( void )
{
	char text[4];
	int yo1 = 21;
	int xo  = 51;
	int width;
	int i, j, count;
	int op;

	if( gpGame->GameType == GAMETYPE_ONEPLAYER )
		return;

	for( i = 0; i < ARMY_LAST_ARMY; i++ )
	{
		if( !Armies[i].Status ) continue;
		// if in setup and not really remote player, dont show icon
		// in real game with multiple players, dont show icon if player not there
		 if (gpComm->m_PlayerId[i] == 0 || gpComm->m_PlayerId[i]  == 0xffffffff)
		 {
			 if (gpGame->GetSubState() == PLAY_SETUP_SUB_STATE) continue;
			 if (!gpGame->oneplayerMode) continue; 
		 }
			
		 j = 0;								// default to unpaused frag counter
			if( gpGame->IsPaused() & (goneflag[i]) )
				j = 1;
			else
			if( gpGame->IsPaused() & (pauseflag[i]) )
				j = 2;
			else
			if( gpGame->IsPaused() & (mappause[i]) )
				j = 4;
			else
			if( !(gpComm->m_ArmyReady[i]) && gpGame->GetSubState() == PLAY_SETUP_SUB_STATE )
				j = 3;

			if( pMainFrame->bPausePageFlip )
				DisplaySpriteFront( Frags[gpComm->ColorFromIndex(i)*5+j], fragPos[i].x, fragPos[i].y );
			else
				DisplaySprite( Frags[gpComm->ColorFromIndex(i)*5+j], fragPos[i].x, fragPos[i].y );
			if( j < 2 )
			{
				count = ArmySargesKilled( i );
                count %= 100;
				sprintf( text, "%2d", count );
				width = BmpTextWidth( text, BMPFONT_MAP, NULL);
				if( pMainFrame->bPausePageFlip )
					BmpTextWrite( pFrontBuffer, fragPos[i].x + xo - width, fragPos[i].y + yo1, text,
						BMPFONT_MAP, NULL, GREEN_IDX );
				else
					BmpTextWrite( pBackBuffer, fragPos[i].x + xo - width, fragPos[i].y + yo1, text,
						BMPFONT_MAP, NULL, GREEN_IDX );
				/*
				count = ArmySargeDeaths( i );
                count %= 100;
				sprintf( text, "%2d", count );
				width = BmpTextWidth( text, BMPFONT_DASHCOMM, NULL);
				if( pMainFrame->bPausePageFlip )
					BmpTextWrite( pFrontBuffer, fragPos[i].x + xo - width, fragPos[i].y + yo2, text,
						BMPFONT_DASHCOMM, NULL, GREEN_IDX );
				else
					BmpTextWrite( pBackBuffer, fragPos[i].x + xo - width, fragPos[i].y + yo2, text,
						BMPFONT_DASHCOMM, NULL, GREEN_IDX );
				*/
				// display flags for a flag game
                if (gpGame->CaptureFlag)
                {
                    op = 0;
                    count = 0;
                    for( op = 0; op < ARMY_LAST_ARMY; op++ )
                    {
                        if( i == op ) continue;
                        // show no flags for non-playing armies
                        if (Armies[op].Status == 0) continue;
                        // change this to != 0 for showing ones to go
                        if( ArmyFlagsCollectedOfArmy( i, op ) == 0 ) continue;

                        // show the flag
						DisplaySprite( FragFlags[gpComm->ColorFromIndex(op)*1],
							fragPos[i].x + fragFlagOffsets[count].x,
							fragPos[i].y + fragFlagOffsets[count].y );
						count++;
					}
				}
			
		}
	}
}


void LoadWorldObjectGraphics( void )
{
	LoadBodyPartGraphics();
	LoadVehiclePartGraphics();
	LoadMuzzleFlashGraphics();
	LoadFlameBurstGraphics();
	LoadScarGraphics();
	LoadSmokeGraphics();
	LoadFlameGraphics();
	LoadMiscGraphics();
}	//	LoadWorldObjectGraphics


void FreeWorldObjectGraphics( void )
{
	if( ParachutistsLoaded )
		FreeParachuteGraphics();
	FreeMiscGraphics();
	FreeFlameGraphics();
	FreeSmokeGraphics();
	FreeScarGraphics();
	FreeFlameBurstGraphics();
	FreeMuzzleFlashGraphics();
	FreeVehiclePartGraphics();
	FreeBodyPartGraphics();
}	//	FreeWorldObjectGraphics


//	update status of world objects
void ProcessWorldObjects( TWorldObjectsArray &obj_array )
{
	int				i;
	PWorldObject	pwo;

	i = obj_array.objects[0].next;
	while( i > 0 )
	{
		pwo = &(obj_array.objects[i]);

		if( pwo->speed <= 0 )
		{
			i = obj_array.objects[i].next;
			continue;
		}

		switch( pwo->wo_type )
		{
		case WOT_BodyPart:
			i = ProcessBodyPart( i, pwo, obj_array );
			break;

		case WOT_VehiclePart:
			i = ProcessVehiclePart( i, pwo, obj_array );
			break;

		case WOT_MuzzleFlash:
			i = ProcessMuzzleFlash( i, pwo, obj_array );
			break;

		case WOT_FlameBurst:
			i = ProcessFlameBurst( i, pwo, obj_array );
			break;

		case WOT_Smoke:
			i = ProcessSmokePuff( i, pwo, obj_array );
			break;

		case WOT_Plume:
			i = ProcessSmokePlume( i, pwo, obj_array );
			break;

		case WOT_Flicker:
			i = ProcessFlicker( i, pwo, obj_array );
			break;

		case WOT_Flame:
			i = ProcessFlame( i, pwo, obj_array );
			break;

		default:
			i = obj_array.objects[i].next;
			break;
		}
	}
}	//	ProcessWorldObjects



void InitLocalObjects( void )
{
	InitGroundObjects();
	InitCorpseObjects();
	InitWorldObjects( WorldObjects, MAX_WORLD_OBJECTS, WORLD_OBJECTS_BUFFER,
		32, 32, OL_ORDEREDLAYER );
	InitWorldObjects( FlashObjects, MAX_FLASH_OBJECTS, FLASH_OBJECTS_BUFFER,
		64, 64, OL_OVERLAYLAYER );
}	//	InitLocalObjects



void FreeLocalObjects( void )
{
	FreeVehicleHusks();
	FreeWorldObjects( FlashObjects );
	FreeWorldObjects( WorldObjects );
	FreeCorpseObjects();
	FreeGroundObjects();
}	//  FreeLocalObjects



void ProcessLocalObjects( void )
{
	ProcessWorldObjects( WorldObjects );
	ProcessWorldObjects( FlashObjects );
	CleanUpDeadHusks();
}

int CountFlames()
{
	int				i,n=0;
	PWorldObject	pwo;

	i = WorldObjects.objects[0].next;
	while( i > 0 )
    {
		pwo = &(WorldObjects.objects[i]);

		if( pwo->speed > 0 && pwo->wo_type == WOT_Flame) ++n;

        i = pwo->next;
   }
    return n;
}