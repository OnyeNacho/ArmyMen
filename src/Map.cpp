////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Map.cpp $
//
//	DESCRIPTION:	the map structure
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, May 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Map.cpp 341   4/18/98 12:46p Bwilcox $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Map.cpp $
//  
//  341   4/18/98 12:46p Bwilcox
//  created xtriggers, moved trigger_branch to it, added
//  xtrigger_sargecarried
//  
//  340   4/17/98 10:05p Bwilcox
//  aargh. revetring a bit
//  
//  339   4/17/98 8:46p Bwilcox
//  mines and explosives were never created properly as objects,
//  NOW they have been given UIDs
//  
//  338   4/15/98 11:56a Bwilcox
//  indenting normal traces and fixing setusercontrol setaicontrol
//  
//  337   4/14/98 8:10p Bwilcox
//  
//  336   4/13/98 2:25p Bwilcox
//  fix dynamic vehicle blocking data
//  
//  335   4/12/98 1:26p Bwilcox
//  allow alex to exist in final build
//  
//  334   4/10/98 6:33p Phu
//  for bruce scrolling
//  
//  333   4/10/98 1:51a Nrobinso
//  turn off random disappearance of objects
//  
//  332   4/09/98 4:31p Nrobinso
//  mark object pieces after the first one
//  
//  331   4/07/98 4:31p Phu
//  set order for mines to appear high-up
//  
//  330   4/06/98 11:05p Nrobinso
//  add SetAISargeView
//  
//  329   4/06/98 2:02p Nrobinso
//  get rid of disappearing powerups
//  
//  328   4/04/98 9:12a Bwilcox
//  cheat fixes
//  
//  327   4/03/98 9:37p Bwilcox
//  cheat fixes
//  
//  325   4/02/98 3:06p Phu
//  
//  324   4/02/98 2:46p Nrobinso
//  cleanup object triggers
//  
//  323   4/01/98 12:07p Nrobinso
//  
//  322   3/31/98 12:56p Bwilcox
//  dispell fog
//  
//  321   3/29/98 1:27a Nrobinso
//  don't randiompy undeploy items if loading saved data
//  
//  320   3/28/98 7:48p Nrobinso
//  fix initialization of pads
//  
//  319   3/27/98 10:52a Dmaynard
//  Added Checksumming of AiDefault.aii files in Map Checking
//  
//  318   3/26/98 2:39p Bwilcox
//  vehicle in movement layer split into new layer
//  
//  317   3/26/98 1:35p Dmaynard
//  Added Checksumming of all Script files listed in the rule file
//  
//  316   3/26/98 5:57a Bwilcox
//  mines are loaded centered in tile
//  
//  315   3/24/98 5:22p Nrobinso
//  aa gun is an asset
//  
//  314   3/23/98 12:47p Phu
//  don't move some of the rocks to the ground layer!
//  
//  313   3/20/98 12:27p Phu
//  force some things into bottom layer
//  
//  312   3/19/98 4:39p Phu
//  TRACES if surface doesn't fit into video memory
//  
//  311   3/18/98 9:45p Bwilcox
//  
//  310   3/16/98 2:13p Bwilcox
//  fixed para count, send oldposition with sargeupdate
//  
//  309   3/16/98 1:41p Bwilcox
//  must check for paraboxes after weapon is made
//  
//  308   3/16/98 1:20p Bwilcox
//  removing unneeded checks for ARMY_OBSTACLE when category is
//  clearly unique.
//  
//  307   3/16/98 1:02p Nrobinso
//  turn off traces
//  
//  306   3/16/98 12:17p Bwilcox
//  count paratroop box charges
//  
//  305   3/15/98 7:43a Bwilcox
//  better isstrategic pin proceesing
//  
//  304   3/14/98 3:12p Nrobinso
//  placed & unplaced objects are marked changed so they will be saved
//  
//  303   98-03-13 21:50 Dmaynard
//  make sure mines are made visble/invisble properly
//  
//  302   3/13/98 3:11p Phu
//  fix bug in damage routine when addobjecttomovementlayer
//  
//  301   3/13/98 1:30p Bwilcox
//  call ItemSetLabel instead of inline code
//  
//  300   3/13/98 9:12a Bwilcox
//  invisible foe mines
//  
//  299   3/11/98 7:24p Phu
//  crush damage when set to last damage sprite
//  
//  298   98-03-11 11:05 Dmaynard
//  multiplayer brief name added to rule file
//  
//  297   3/10/98 7:28p Nrobinso
//  free returned buffer
//  
//  296   3/10/98 7:24p Nrobinso
//  read multiple scripts from rule file
//  
//  295   98-03-10 19:12 Dmaynard
//  unlimited number of scripts files in rul can be concatenated and read
//  in
//  
//  294   3/10/98 4:02p Nrobinso
//  first in script list is header.txt
//  
//  293   3/10/98 3:58p Nrobinso
//  keep a list of script names in map
//  
//  292   3/10/98 3:46p Phu
//  note that clipline sometimes returns 0!
//  added assert to getobjects
//  fix flamethrowers go off screen
//  
//  291   98-03-10 15:32 Dmaynard
//  strategic objects do not get tads anymore
//  
//  290   3/09/98 6:01p Bwilcox
//  
//  289   3/08/98 1:00a Nrobinso
//  set a sarge type based on weapon
//  
//  288   3/07/98 11:52p Nrobinso
//  move .h file to stdafx
//  
//  287   3/06/98 4:05p Bwilcox
//  tell routeplanner about mines preloaded on map
//  
//  286   3/06/98 3:33p Phu
//  remove missionloading call
//  
//  285   3/02/98 5:57p Phu
//  extend look ahead per frame
//  
//  284   2/26/98 7:23p Phu
//  fix a crash bug involving i & j
//  
//  283   2/26/98 4:06p Phu
//  removed profiling/ old draw map into deadcode
//  
//  282   2/24/98 10:39p Nrobinso
//  cehck for laoded graphics before deleting an object that requires the
//  presence of object graphics
//  
//  281   2/24/98 7:30p Phu
//  cursor load from data file, moved closedatafile
//  
//  280   2/20/98 3:40p Nrobinso
//  remove unsued code
//  
//  279   2/20/98 2:50p Phu
//  make floats hit bridges at height 0
//  
//  278   2/20/98 1:18p Nrobinso
//  
//  277   2/18/98 2:27p Bwilcox
//  stop air recon from using allah mode to do its dirty work
//  
//  276   2/18/98 2:03p Phu
//  Do damage with gun spark explosions
//  
//  275   2/16/98 6:10p Bwilcox
//  allah can scroll onto the invisible map area
//  
//  274   2/16/98 12:03p Phu
//  pass along fromUID with explosions
//  
//  273   2/16/98 10:57a Nrobinso
//  checksum script files
//  
//  272   2/16/98 9:29a Nrobinso
//  make checksum unsigned longs
//  
//  271   2/13/98 7:10p Nrobinso
//  turn off checksum
//  
//  270   2/13/98 6:40p Nrobinso
//  fixed checksum bug
//  
//  269   2/13/98 11:13a Phu
//  
//  268   2/12/98 8:55p Phu
//  mortar screen scroll, better force of gravity
//  
//  267   2/12/98 11:34a Nrobinso
//  make an AA gun *not* an asset (no independent firing)
//  
//  266   2/11/98 1:13p Nrobinso
//  get char for group, not a short
//  
//  265   2/10/98 4:25p Nrobinso
//  Attached objects
//  
//  264   2/10/98 2:21p Phu
//  firing heights
//  
//  263   2/09/98 1:51p Phu
//  pass along heights, GetObjectHeight function
//  
//  262   2/08/98 6:10p Nrobinso
//  error msg if no tile file
//  
//  261   2/08/98 5:31p Nrobinso
//  message box if no tile file
//  
//  260   2/08/98 5:14p Nrobinso
//  move script override out of map, otherwise it gets cleared
//  
//  259   2/07/98 6:07p Nrobinso
//  multiple maps may share a rule file for multiplayer; remote display bug
//  remains
//  
//  258   2/07/98 4:22p Phu
//  hopefully fix map object color->local army conversions
//  
//  257   2/04/98 3:16p Phu
//  armor for objects
//  
//  256   2/04/98 12:57p Bwilcox
//  mines now go in ground layer
//  
//  255   2/03/98 5:14p Phu
//  permeability only for one player
//  
//  254   2/03/98 11:30a Phu
//  minor rearrangements
//  
//  253   2/02/98 3:22p Bwilcox
//  
//  252   2/02/98 10:07a Bwilcox
//  FIX MULTOPLAYER FLAG REFS
//  
//  251   2/01/98 10:57p Nrobinso
//  use PROFILING_ACTIVE for debug code
//  
//  250   2/01/98 8:30p Nrobinso
//  turn off forced palette load, since it has already been loaded by the
//  load screen
//  
//  249   2/01/98 5:45p Nrobinso
//  remove TESTPATH
//  
//  248   2/01/98 1:40p Phu
//  -3 extension to libarary load
//  
//  247   1/30/98 1:12p Bwilcox
//  fixing hiding of flags in multiplayer bug
//  
//  246   1/29/98 1:59p Bwilcox
//  
//  245   1/29/98 1:56p Bwilcox
//  assets not removed by remove unused items now
//  
//  244   1/29/98 1:41p Bwilcox
//  fixed asset delete
//  
//  243   1/28/98 1:25p Bwilcox
//  fixed load/free stuff
//  
//  242   1/28/98 11:55a Bwilcox
//  
//  241   1/28/98 11:32a Bwilcox
//  more edit trafic code
//  
//  240   1/27/98 2:37p Bwilcox
//  puff away dead forces
//  
//  239   1/27/98 1:06p Bwilcox
//  finishing armydelete adjustments for multiplayer
//  
//  238   1/27/98 12:18p Bwilcox
//  removeditems of army when army delete
//  
//  237   1/25/98 5:02a Bwilcox
//  map allocate of ai data occurs as soon as sizing is known
//  
//  236   1/26/98 12:00p Nrobinso
//  new path defines
//  
//  235   1/23/98 4:02p Nrobinso
//  add overide of trafficabilty for gates
//  
//  234   1/23/98 11:10a Nrobinso
//  add GATE category
//  
//  233   1/22/98 12:00p Nrobinso
//  add checksum load
//  
//  232   1/20/98 5:53p Phu
//  fix booboo in LoadObjectText
//  
//  231   1/20/98 5:07p Phu
//  fix damage level reading for linked objects
//  
//  230   1/20/98 3:07p Phu
//  create mines even if ammo has not been set
//  
//  229   1/20/98 10:24a Awerner
//  Fixed object scripting
//  
//  228   1/19/98 10:19a Nrobinso
//  don't pass a name for object header file name construction
//  
//  227   1/17/98 9:23p Nrobinso
//  move the explosion toggle to debug
//  
//  226   1/17/98 8:54p Nrobinso
//  allow toggling of right button explosions on & off
//  
//  225   1/17/98 8:16p Nrobinso
//  add interface routine to get map view
//  
//  224   1/16/98 11:43p Bwilcox
//  removed JUNK
//  
//  223   1/16/98 9:56p Bwilcox
//  sarge view is now not restricted by line of sight
//  
//  222   1/15/98 6:32p Phu
//  set path for tileset recovery
//  
//  221   1/15/98 5:05p Phu
//  new aai
//  
//  220   1/14/98 4:29p Bwilcox
//  replaced cansee/canshoot coding
//  
//  219   1/13/98 12:20p Phu
//  added SP_USESELFRECT for animations
//  
//  218   1/13/98 10:52a Phu
//  Do not use the sprite itself or its rectangle if no mask or rect is
//  provided
//  
//  217   1/12/98 4:23p Phu
//  assert if requested centerpoint is ever 0
//  
//  216   1/12/98 3:18p Phu
//  Animated Objects
//  
//  215   1/12/98 10:42a Aburgess
//  changes made to look in the RUNTIME/MAPS directory for map based
//  information
//  
//  213   1/07/98 4:58p Phu
//  modify calls to GetIndexFromColor to allow -1 return values
//  
//  212   1/07/98 3:26p Phu
//  fix object owner numbering bug, undeploy unused objects
//  
//  211   1/07/98 3:21p Nrobinso
//  add AvatarCurrentPose; changed AvatarPose to take only the avatar
//  pointer; AvatarPoseChange also takes an action
//  
//  210   1/06/98 1:30p Phu
//  restore dashboard/cursors after alt-tab
//  
//  209   1/06/98 9:58a Dmaynard
//  Added a check that the the_map.objfilename is not a zero length string.
//  This will avoid a parse error on _0.obj  which will hopefully fix a bug
//  whereby explosives were not working because there was not an event
//  properly initialized.
//  
//  208   1/05/98 3:37p Phu
//  mines aren't hit by shots
//  
//  207   1/05/98 2:13p Phu
//  stratmap now matches boundrect
//  
//  206   1/02/98 2:20p Bwilcox
//  
//  205   1/02/98 2:10p Bwilcox
//  distance tests moved into canshoot
//  
//  204   1/02/98 1:24p Bwilcox
//  line of sight from a canshoot call will test for friendlies in the way.
//  Vehicle/sarge ai now checks using canshoot also
//  
//  ...
// 
// 5     6/25/96 9:54p Nrobins
// added history info
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "Army.h"
#include "Ai.h"
#include "AiAccess.h"
#include "Disp.h"
#include "MainFrm.h"
#include "Map.h"
#include "miscfile.h"
#include "Tile.h"
#include "damage.h"
#include "comm.h"
#include "newdoor.h"
#include "scenario.h"
#include "item.h"
#include "tad.h"
#include "unit.h"
#include "ui.h"
#include "explosions.h"
#include "fileio.h"
#include "scripts.h"
#include "weapon.h"
#include "gameflow.h"
#include "map.dat"
#include "wobject.h"
#include "snd.h"
#include "aibtank.h"


// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SCREEN_WIDE	40
#define SCREEN_HIGH	30

#define NAME_SIZE 4

//      FORM =     M R O F
#define FORM	0x4D524F46
#define MAP		0x2050414D
#define VERS	0x53524556
#define MHDR	0x5244484D
#define TNAM	0x4D414E54
#define TLAY	0x59414C54
#define ONAM	0x4D414E4F
#define OLAY	0x59414C4F
#define SCEN	0x4E454353
#define TILE	0x454C4954
#define THDR	0x52444854
#define DIB		0x20424944
//#define ATTR	0x52545441
#define DESC	0x43534544
#define MOVE	0x45564F4D
#define ELOW	0x574F4C45
#define TRAF	0x46415254
#define TRIG	0x47495254
#define PADS	0x53444150
#define AFIL	0x4C494641
#define OFIL	0x4C49464F
#define PFIL	0x4C494650
#define ASCR	0x52435341
#define PSCR	0x52435350
#define OATT	0x5454414F
#define INDX	0x58444E49
#define SCRI	0x49524353
#define RESV	0x56534552
#define BPAD	0x44415042
#define NPAD	0x4441504E
#define NUMB	0x424D554E
#define CSUM	0x4D555343
#define GRUP	0x50555247


typedef struct	{
	long name;
	long size;
} ObjectLayerAttrib;

#define OLD_OBJECT_ATTRIBS 7
#define MAX_OBJECT_ATTRIBS 8
ObjectLayerAttrib attribs[MAX_OBJECT_ATTRIBS] = {
	{INDX,sizeof(long)},
	{MOVE,sizeof(char)},
	{ELOW,sizeof(char)},
	{TRIG,sizeof(char)},
	{RESV,sizeof(char)},
};

typedef struct {
	long	major_version;
	long	minor_version;
} Version;

typedef struct {
	long	width;
	long	height;
	long	num_tile_layers;
} MapHeader;

typedef struct {
	BOOL	transparent;
	long	width;
	long	height;
	long	x;
	long	y;
} TileLayer;

typedef struct	{
	long category;
	long number;
 	long x;
 	long y;
} ObjectLayerObj;

typedef struct {
	long	width;
	long	height;
	long	max_tiles;
	long	tiles_wide;
	COLORREF	rgbTransparent;
} TileHeader;

/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////
BOOL LoadTileSet(char *pFilename);
void SetCategoryAttributes(OBJECT *pobject, int id);
void SetMapWindowWidths();


/////////////////////////////////////////////////////////////////////////////
//					Local Prototypes
/////////////////////////////////////////////////////////////////////////////
static BOOL ObjectMask(ANIMCELL *pCell);
static BOOL ObjectMaskOverlap(ANIMCELL *pCell, ITEM_OVERLAP *poverlap);
static BOOL InObjectRect(ANIMCELL *pAnimObject, SPOINT *pt);
static BOOL ObjectRectOverlap(ANIMCELL *pCell, ITEM_OVERLAP *poverlap);
void CopyScriptNames();

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////
extern int ParaDropBoxCount;

Map the_map;
int num_script_names;
char *script_names[SCRIPT_NAMES];
char brieffilename[SCRIPT_NAME_SIZE];
unsigned short int map_width;
unsigned short int map_height;
DWORD SetupSeed = (DWORD)time(0);
RECT rcGameSurface;
MAP_MODE map_mode = NORMAL_VIEW;
SPOINT OFF_THE_MAP = {0,0};			// a point not on the map
SPRITE objects[NUM_OBJECTS];

ANIM* pScrollAnim = 0; 		// what anim to follow and scroll with
SPOINT* pScrollSpoint = 0;	// or what spoint to track

TileSet the_tiles;

extern DWORD SetupSeed;
extern char  randomize;


extern unsigned char scrollReset;	//1= flip view back to anim

#if !defined(_USESYSTEMMEMORY_)
extern LPDIRECTDRAW2 pDirectDraw2;
#endif

#define MAX_PADS 256

/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////

static BOOL MapLoaded = FALSE;
static BOOL MapGraphicsLoaded = FALSE;
SPOINT padLocations[MAX_PADS];


/////////////////////////////////////////////////////////////////////////////
//					     Code
/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
static void VerifyOverlapBox(ITEM_OVERLAP *poverlap)	{
	ASSERT(poverlap->box.top >= 0);
	ASSERT(poverlap->box.bottom <= the_map.height);
	ASSERT(poverlap->box.left >= 0);
	ASSERT(poverlap->box.right <= the_map.width);

	ASSERT(poverlap->box.bottom - poverlap->box.top < 640);
	ASSERT(poverlap->box.right - poverlap->box.left < 640);
}
#else
#define VerifyOverlapBox(n)
#endif


char *ReadScriptFile( char *filename, int &len, unsigned long &checksum )
{
	char *buffer = NULL;
	FILE *fp;

	fp = fopen( filename, "rt" );
	len = 0;
	if( !fp )
		return NULL;

	int tsize;
	if( fseek( fp, 0, SEEK_END ) != 0 )
		return NULL;
	tsize = ftell( fp );
	fseek( fp, 0, SEEK_SET );

	buffer = (char *)malloc( tsize + 8 );

	int i, size;
	i = 0;
	while( !feof( fp ) )
	{
		size = fread( buffer+i, 1, 256, fp );
		i += size;
		if( i > tsize )
		{
			free( buffer );
			fclose(fp);
			return NULL;
		}
		if( ferror( fp )) 
		{
			free( buffer );
			fclose(fp);
			return NULL;
		}
	}
	size = i;
	buffer[i] = 0;
	len = size;
	fclose(fp);

	for (i=0; i<size; i++)
		checksum += (unsigned long) buffer[i];

	return( buffer );
}


unsigned long LoadMissionText(int mission)
{
	char *buffer=NULL, *buffer1=NULL, *tmpbuffer;
	int  filesize1=0;
	char tempfilename[50];
	unsigned long checksum = 0;
	int priorbsize = 0;	
	++mission; // 1 based

	// allocate an initially empty buffer of text
	buffer = (char*)malloc(priorbsize+8);
    if (buffer==NULL) 
		ASSERT(0);									// you are hosed if you fail
	*buffer = 0;

       
	SetPath( MAP_PATH );

	// concatenate all individual script files named
	int i;
	TRACE("\n\n");
	for (i = 0; i < the_map.num_script_names; ++i)
	{
		if (strcmp( the_map.script_names[i], "header" ) == 0) // protect header from changing
		      sprintf( tempfilename, "%s.txt",the_map.script_names[i]);
        else 
		    sprintf( tempfilename, "%s_%d.txt",the_map.script_names[i],mission);
		TRACE( "    Reading script file %s\n", tempfilename );
		if( !(buffer1 = ReadScriptFile( tempfilename, filesize1, checksum )))
		{
			TRACE( "Error reading script file %s\n", tempfilename );
			ASSERT(0);
		}

		// append this file to the buffer we have
		tmpbuffer = buffer;			
		buffer = (char*)malloc(priorbsize+filesize1 + 1 +8);
		memcpy(buffer, tmpbuffer, priorbsize);
		buffer[priorbsize] = ' ';  // a safe separator of concatenated scripts of text
		memcpy(buffer + priorbsize + 1, buffer1, filesize1);
		free(buffer1);
		priorbsize += filesize1 + 1;
		buffer[priorbsize] = 0;		// 0 termintated data
		free(tmpbuffer);
		tmpbuffer = NULL;
	}
	
	the_map.missiontext = buffer;
	return checksum;
}


unsigned long LoadObjectText(int mission)
{
	char *buffer, *buffer1=NULL, *buffer2=NULL;
	int filesize1=0, filesize2=0;
	char tempfilename[50];
 	unsigned long checksum = 0;
    
	SetPath( MAP_PATH );

	sprintf(tempfilename, "obj_header.txt");
	TRACE( "    Reading object header %s\n", tempfilename );
	if( !(buffer1 = ReadScriptFile( tempfilename, filesize1, checksum )))
		TRACE( "Error reading object header %s\n", tempfilename );

	if (the_map.objfilename && (strlen(the_map.objfilename) > 0))
	{
		sprintf(tempfilename, "%s_%d.txt", the_map.objfilename, mission+1);

		TRACE( "    Reading object script file %s\n", tempfilename );
		buffer2 = ReadScriptFile( tempfilename, filesize2, checksum );
	}


	buffer = (char*)malloc(filesize1+filesize2+8);

    if (buffer==NULL) 
		ASSERT(0);									// you are hosed if you fail

	*buffer = 0;
	if( buffer1 )
		memcpy(buffer, buffer1, filesize1);
	if( buffer2 )
		memcpy(buffer + filesize1, buffer2, filesize2);
	buffer[filesize1 + filesize2] = 0;

	if( buffer1 )
		free(buffer1);
	if( buffer2 )
		free(buffer2);
	the_map.objtext=buffer;
	return checksum;
}


//This function, given a category and number, returns how many
//subsprites a particular object is divided into (usually used
//so that a large building can get damaged in segments
int HowManySubObjects(int category, int number)
{
	AI_ITBL *aiPtr;

	aiPtr = AiGetObjectDefs( category, number, 0 );
	if( aiPtr )
		return aiPtr->nPartCount;
	else
		return 1;
}


void InitObjects()	{
	int i,j,k,numsub;
	OBJECT *obj_copy;
    ParaDropBoxCount = 0;
	int extrasubobjects=0; //the number of extra objects we need to add to 
						 //account for large buildings made up of subobjects

	for (i=0;i<the_map.num_objects;i++)
	{
		if (the_map.num_objs[the_map.objects[i].category])
		{
			numsub=HowManySubObjects(the_map.objects[i].category, the_map.objects[i].number);
			extrasubobjects+=numsub-1;
			the_map.num_objs[the_map.objects[i].category]+=numsub-1;
			if (the_map.objects[i].number+numsub>= the_map.max_objs[the_map.objects[i].category])
				the_map.max_objs[the_map.objects[i].category]=the_map.objects[i].number+numsub+1;

		}
	}

	// copy the object list so we can rearrange it
	obj_copy = (OBJECT *)malloc((the_map.num_objects+extrasubobjects) * sizeof(OBJECT));

	// sort object array into sub-arrays of each category
	int total = 0;
	for (j=0; j<NUM_OBJECT_TYPES; j++)	{
		if (the_map.num_objs[j])	{
			the_map.obj_type_list[j] = &obj_copy[total];
			for (i=0; i<the_map.num_objects; i++)	{
				if (the_map.objects[i].category == j)	
				{
					// create the sub objects
					if( (numsub = HowManySubObjects( j, the_map.objects[i].number )) > 1 )
					{
						for( k = 0; k < numsub; k++ )
						{
							obj_copy[total+k] = the_map.objects[i];
							obj_copy[total+k].nextsubobject = &obj_copy[ total + ((k+1)%numsub) ];
							obj_copy[total+k].prevsubobject = &obj_copy[ total+((k+numsub-1)%numsub) ];
							obj_copy[total+k].number = the_map.objects[i].number + k + 1;							
							if( k > 0 )
							{
								obj_copy[total+k].triggers &= (~TRIGGER_STRATEGIC);
								obj_copy[total+k].xtriggers |= XTRIGGER_BRANCH;
								obj_copy[total+k].common.label = NULL;
							}

							AI_ITBL *aiPtr;

							aiPtr = AiGetObjectDefs( obj_copy[total+k].category, obj_copy[total+k].number, 0 );
							if( aiPtr )
							{
								obj_copy[total+k].layer = (EObjectLayer)(aiPtr->nLayer);
								obj_copy[total+k].common.nStrength = obj_copy[total+k].common.nMaxStrength = aiPtr->nHitPoints;
								obj_copy[total+k].elevation = aiPtr->nHeight;
								obj_copy[total+k].visibility = aiPtr->nVisibility;
								obj_copy[total+k].permeability = aiPtr->nPermeability;
								obj_copy[total+k].armor = aiPtr->nArmor;
							}
						}
						total += numsub;
					}
					else
						obj_copy[total++] = the_map.objects[i];
				}
			}
		}
	}
	the_map.num_objects += extrasubobjects;
	ASSERT(total == the_map.num_objects);
	ASSERT(the_map.objects);
	free(the_map.objects);
 	the_map.objects=obj_copy;

	// allocate sprite arrays for each category
	if( !_LOAD_FROM_DATAFILE )
	for (j=0; j<NUM_OBJECT_TYPES; j++)	{
		if (the_map.num_objs[j])	{
			OBJECT	*optr = the_map.obj_type_list[j];

			SHORT *list = (SHORT *)malloc(the_map.max_objs[j]*sizeof(SHORT));
			ZeroMemory(list, the_map.max_objs[j]*sizeof(SHORT));

			int i;			// looping variable
			// loop thru the objects of each type
			for (i=0; i<the_map.num_objs[j]; i++)	{
				list[optr[i].number] = TRUE;
			}

			int max = 0;
			for (i=0; i<the_map.max_objs[j]; i++)	{
				if (list[i])
					list[i] = max++;
			}
			the_map.max_objs[j] = max;

			for (i=0; i<the_map.num_objs[j]; i++)	{
				optr[i].index = list[optr[i].number];
			}

			free(list);

			if (max)	{
				the_map.obj_sprite_array_list[j] = (OBJECT_SPRITE *)malloc(max * sizeof(OBJECT_SPRITE));
				ZeroMemory(the_map.obj_sprite_array_list[j], max * sizeof(OBJECT_SPRITE));
			}
			else
				the_map.obj_sprite_array_list[i] = NULL;
		}
	}

	short	local_num_objs[NUM_OBJECT_TYPES];
	ZeroMemory(local_num_objs, sizeof(local_num_objs));

    srand( 1 ); // a consistent init value
	if( randomize )
	{
		srand( SetupSeed );
//		TRACE( "*** Seed is %d\n", SetupSeed );
		SetupSeed += rand();
	}

	for (j=0; j<the_map.num_objects; j++)	
	{
		int category = the_map.objects[j].category;
		SetCategoryAttributes(&the_map.objects[j], j);
		local_num_objs[the_map.objects[j].category]++;
	}

    // tell route planner about predeployed mines
	OBJECT* pObj;
	for (i=0;i<the_map.num_objects;i++)
    {
        pObj = &(the_map.objects[i]);
        if (!pObj->common.tile) continue; // not allocated on map
        if (pObj->category != EXPLOSIVES) continue;
		if (pObj->number != ARMY_MINE) continue;
        if (pObj->owner != ARMY_PLAYER) 
			pObj->triggers |= TRIGGER_INVISIBLE;
        MineAdded(pObj->common.tile, pObj->owner);
    }
}


BOOL	MapGraphicsLoad()	{

	if (MapGraphicsLoaded)
		return TRUE;

	SetPath( MAP_PATH );

	if (!LoadTileSet(the_map.tile_name))
		return FALSE;

	LoadObjects(the_map.terrain_name);

	the_map.redraw = REDRAW_FULL;

	MapGraphicsLoaded = TRUE;

	return TRUE;
}


//!!!! HACK FIX / TRIAL
void AddExtraDependentObjects( void )
{
	int i, n_explosives, n_mines;
	OBJECTSTRUCT * temp_array;

	n_explosives = 0;
	n_mines = 0;

	//	count the # of mine & explosives charges
	for( i = 0; i < the_map.num_objects; i++ )
	{
		if(the_map.objects[i].category == SPECIAL_ITEMS)
		{
			int howmany;

			howmany = the_map.objects[i].howmany;
			if( howmany == 0 )
				howmany = 5;
			if( the_map.objects[i].number == ARMY_EXPLOSIVE_WEAPON )
				n_explosives += howmany;	
			else if( the_map.objects[i].number == ARMY_MINE )
				n_mines += howmany;
		}
	}

	i = the_map.num_objects + n_explosives + n_mines;
	temp_array = (OBJECT *)malloc( i * sizeof(OBJECT) );
	ZeroMemory( temp_array, i * sizeof(OBJECT) );
	CopyMemory( temp_array, the_map.objects, (the_map.num_objects) * sizeof(OBJECT) );
	free( the_map.objects );
	the_map.objects = temp_array;

	//	create the explosives charge objects
	for( i = the_map.num_objects; i < the_map.num_objects + n_explosives; i++ )
	{
		OBJECT* pObj;
		pObj = &(the_map.objects[i]);
		pObj->category = EXPLOSIVES;
		pObj->number = ARMY_EXPLOSIVE_WEAPON;
		pObj->layer = OL_ORDEREDLAYER;
		pObj->triggers |= TRIGGER_UNDEPLOYED;
		pObj->xtriggers = 0;
		pObj->owner = -1;
		pObj->group = 0;

		/// attribute and uid set later
	
		if( ARMY_EXPLOSIVE_WEAPON >= the_map.max_objs[EXPLOSIVES] )
			the_map.max_objs[EXPLOSIVES] = (short)ARMY_EXPLOSIVE_WEAPON + 1;
		the_map.num_objs[EXPLOSIVES]++;
	}
	the_map.num_objects += n_explosives;

	//	create the mines charge objects
	for( i = the_map.num_objects; i < the_map.num_objects + n_mines; i++ )
	{
		OBJECT* pObj;
		pObj = &(the_map.objects[i]);
		pObj->category = EXPLOSIVES;
			pObj->number = ARMY_MINE;
		pObj->layer = OL_GROUNDLAYER;
		pObj->triggers |= TRIGGER_UNDEPLOYED;
		pObj->xtriggers = 0;
		pObj->owner = -1;
		pObj->group = 0;
		pObj->cell.order = 2100;
		/// attribute and uid set later

		if( ARMY_MINE >= the_map.max_objs[EXPLOSIVES] )
			the_map.max_objs[EXPLOSIVES] = (short)ARMY_MINE + 1;
		the_map.num_objs[EXPLOSIVES]++;
	}
	the_map.num_objects += n_mines;

}


static void SetTileTrafficable()	{ // mark 
	IPOINT index;

	WALKGRID(index){
		if (the_map.movement_layer[index] == 15 || ONEDGE(index))	
			the_map.triggers[index] |= TILE_UNTRAFFICABLE;
	}
}



unsigned long	MapLoadSum(const char *pFilename)	{
	FILE* pFile = NULL;
	long	chunk_name;
	long	file_size;
	long	file_index = 0;
	long	chunk_size;
	unsigned long	sum = 0;

	SetPath( MAP_PATH );

	if ( (pFile = (FILE*)fopen( pFilename, "rb" )) != NULL )	{
		READ_LONG(&chunk_name);
		file_index += sizeof(long);
		if (chunk_name == FORM)	{
			READ_LONG(&file_size);
			file_index += sizeof(long);

			READ_LONG(&chunk_name);
			file_index += sizeof(long);
			if (chunk_name == MAP)	{
				READ_LONG(&chunk_name);
				READ_LONG(&chunk_size);
				if (chunk_name == CSUM)	{
					if (chunk_size == sizeof(sum))
						READ_BUFFER(&sum, chunk_size);
				}
			}
		}
		fclose( pFile );
	}

	return sum;
}


BOOL	MapLoad(const char *pFilename)	{
	FILE* pFile = NULL;
	BOOL	ok = TRUE;
	long	chunk_name;
	long	file_size;
	long	file_index = 0;
	long	chunk_size;
	long	total_size;
	long	target_size;
	Layer	*pLayer;
	Version version;
	MapHeader mhdr;
	TileLayer tlayer;
	BOOL	new_version = TRUE;
	EObjectLayer curlayer = OL_GROUNDLAYER;
	int		tile_layer_size;
	char	temp;
    char	fname[200];

	if (MapLoaded)
		return TRUE;

	SetPath( MAP_PATH );

	ZeroMemory(&version, sizeof(version));
	ZeroMemory(&mhdr, sizeof(mhdr));

	if ( (pFile = (FILE*)fopen( pFilename, "rb" )) == NULL )	{
		// report an error
		TRACE("ERROR: failed to open map file: \"%s\". [%s:%d]\n", pFilename, __FILE__, __LINE__ );
		ASSERT(0);
		ok = FALSE;
		goto exit;
	}

	READ_LONG(&chunk_name);
	file_index += sizeof(long);
	if (chunk_name != FORM)	{
		// report an error
		TRACE("ERROR: %s is not an Army Men Map file of FORM\n", pFilename );
		ASSERT(0);
		ok = FALSE;
		goto exit;
	}

	READ_LONG(&file_size);
	file_index += sizeof(long);

	READ_LONG(&chunk_name);
	file_index += sizeof(long);
	if (chunk_name != MAP)	{
		// report an error
		TRACE("ERROR: %s is not an Army Men Map file of MAP\n", pFilename );
		ASSERT(0);
		ok = FALSE;
		goto exit;
	}

//	TRACE("Loading map file: %s\n", pFilename);

	ZeroMemory(&the_map, sizeof(Map));
	strncpy( the_map.map_name, pFilename, strlen(pFilename)-4 );

	do	{
		READ_LONG(&chunk_name);
		READ_LONG(&chunk_size);

		switch(chunk_name)	{
			case CSUM:
				fseek(pFile, chunk_size, SEEK_CUR);
				break;

			case VERS:
				target_size = sizeof(Version);
				if (chunk_size < target_size)	{
					TRACE("VERS size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}

				READ_BUFFER(&version, target_size);

				ASSERT(version.major_version >= 5);
				ASSERT(version.minor_version >= 0);

				if ((version.major_version == 5) && (version.minor_version == 0))	{
					new_version = FALSE;
				}

				if (chunk_size > target_size)	{
					TRACE("VERS size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - target_size, SEEK_CUR);
				}
				break;

			case DESC:
				the_map.desc = (char *) malloc(chunk_size);

				if (the_map.desc)
				{
					READ_BUFFER(the_map.desc, chunk_size);
//					TRACE("Map description is %s\n", the_map.desc);
				}
				else	{
					TRACE("ERROR: failed to malloc description\n");
					ok = FALSE;
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}
				break;

			case OFIL:
			case PFIL:
				if (chunk_size < sizeof(the_map.objfilename))	{
					READ_BUFFER(the_map.objfilename, chunk_size);
				}
				else	{
					TRACE("ERROR: object filename is too long\n");
					READ_BUFFER(the_map.objfilename, sizeof(the_map.objfilename));
					fseek(pFile, chunk_size - sizeof(the_map.objfilename), SEEK_CUR);
				}
//				TRACE("Object filename is -%s-\n", the_map.objfilename);
				break;

			case AFIL:
				if (chunk_size < SCRIPT_NAME_SIZE)	{
					READ_BUFFER(fname, chunk_size);
				}
				else	{
					TRACE("ERROR: mission filename is too long\n");
					READ_BUFFER(fname, SCRIPT_NAME_SIZE);
					fseek(pFile, chunk_size - SCRIPT_NAME_SIZE, SEEK_CUR);
				}

				if ( gpGame->GameType == GAMETYPE_ONEPLAYER )	{
//					strcpy(the_map.missionfilename, fname);
					SetScriptName("header", 0);
					SetScriptName(fname, 1);
				}
//				else
//					strcpy(the_map.missionfilename, script_names[0]);

				CopyScriptNames();

				break;

			case PSCR:
				the_map.objtext = (char *) malloc(chunk_size);

				if (the_map.objtext)
				{
					READ_BUFFER(the_map.objtext, chunk_size);
				}
				else	{
					TRACE("ERROR: failed to malloc objtext\n");
					ok = FALSE;
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}
				break;

			case ASCR:
				the_map.missiontext = (char *) malloc(chunk_size);

				if (the_map.missiontext)
				{
					READ_BUFFER(the_map.missiontext, chunk_size);
				}
				else	{
					TRACE("ERROR: failed to malloc missiontext\n");
					ok = FALSE;
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}
				break;
			case MHDR:
				target_size = sizeof(MapHeader);

				if (chunk_size < target_size)	{
					TRACE("MHDR size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					ok = FALSE;
					break;
				}

				READ_BUFFER(&mhdr, target_size);

				if (chunk_size > target_size)	{
					TRACE("MHDR size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - target_size, SEEK_CUR);
				}

				the_map.width = map_width = (short)mhdr.width;
				the_map.height = map_height = (short)mhdr.height;
				the_map.bitwidth = CvtBits( the_map.width );
				the_map.xmask = (1 << the_map.bitwidth) - 1;

                gridmax = the_map.width * the_map.height;
                AiMapAllocate();                

				the_map.TileBox.x = 0;
				the_map.TileBox.y = 0;

				the_map.PixelBox.x = 0;
				the_map.PixelBox.y = 0;

				the_map.FullPixelBox.x = 0;
				the_map.FullPixelBox.y = 0;
				the_map.FullPixelBox.cx = (short)(the_map.width << 4);
				the_map.FullPixelBox.cy = (short)(the_map.height << 4);

				the_map.FullPixelRect.left = 0;
				the_map.FullPixelRect.top = 0;
				the_map.FullPixelRect.right = the_map.FullPixelBox.cx;
				the_map.FullPixelRect.bottom = the_map.FullPixelBox.cy;

				InitObjectLayer( &the_map.groundlayer, map_width, map_height, 5 );
				InitObjectLayer( &the_map.orderedlayer, map_width, map_height, 7 );
				InitObjectLayer( &the_map.toplayer, map_width, map_height, 7 );
				InitObjectLayer( &the_map.overlaylayer, map_width, map_height, 7 );

				// allocate fog layers
				tile_layer_size = the_map.width * the_map.height * sizeof(BYTE);
		
				// allocate visiblity layer
				the_map.vis_layer = (BYTE *)malloc( tile_layer_size );
				ZeroMemory( the_map.vis_layer, tile_layer_size );
				SetMapWindowWidths();		// sets Box widths

				break;

			case TNAM:
				target_size = sizeof(the_map.tile_name);

				if (chunk_size >= target_size)
					TRACE("TNAM size too big: %d\n", chunk_size);
				else
					target_size = chunk_size;

				READ_BUFFER(the_map.tile_name, target_size);
				the_map.tile_name[target_size] = '\0';
				break;

			case TLAY:
				ZeroMemory(&tlayer, sizeof(TileLayer));

				READ_BUFFER(&tlayer, sizeof(TileLayer));

				target_size = tlayer.width * tlayer.height * sizeof(short);

				// allow for an empty layer
				if (target_size == 0)
					break;

				if (chunk_size < target_size + (long) sizeof(TileLayer))	{
					TRACE("TLAY size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					ok = FALSE;
					break;
				}

				pLayer = &the_map.layers[the_map.num_layers];

				pLayer->box.cx = (short)tlayer.width;
				pLayer->box.cy = (short)tlayer.height;
				pLayer->box.x = (short)tlayer.x;
				pLayer->box.y = (short)tlayer.y;

				pLayer->tile_array = (short *) malloc(target_size);
				// need error checking

				READ_BUFFER(pLayer->tile_array, target_size);

				if( the_map.num_layers > 0 )
				{
					ASSERT( pLayer->box.x == the_map.layers[0].box.x );
					ASSERT( pLayer->box.y == the_map.layers[0].box.y );
					ASSERT( pLayer->box.cx == the_map.layers[0].box.cx );
					ASSERT( pLayer->box.cy == the_map.layers[0].box.cy );
				}

				the_map.num_layers++;

				if (chunk_size > target_size + (long) sizeof(TileLayer))	{
					TRACE("TLAY size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - target_size, SEEK_CUR);
				}

				break;

			case ONAM:
				target_size = sizeof(the_map.terrain_name);

				if (chunk_size >= target_size)
					TRACE("ONAM size too big: %d\n", chunk_size);
				else
					target_size = chunk_size;

				READ_BUFFER(the_map.terrain_name, target_size);
				the_map.terrain_name[target_size] = '\0';
				break;

			case OLAY:
				LONG num_objects;
				LONG attributes;
				LONG index;
				LONG read;
				LONG *plRead;
				SHORT *psRead;
				char *pcRead;
				int  o,
					 n;
				OBJECT *tempobjbuffer;

				READ_LONG(&num_objects);

				target_size = num_objects * sizeof(ObjectLayerObj) + sizeof(num_objects);

				if (chunk_size < target_size)	{
					TRACE("OLAY size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}

				tempobjbuffer = the_map.objects;
				n = the_map.num_objects;
				the_map.num_objects = n + num_objects;
				the_map.objects = (OBJECT *)malloc( the_map.num_objects * sizeof(OBJECT) );
				ZeroMemory( the_map.objects, the_map.num_objects * sizeof(OBJECT) );
				if( n > 0 )
					CopyMemory( the_map.objects, tempobjbuffer, n * sizeof(OBJECT) );
				free( tempobjbuffer );

				for (o = n; o < the_map.num_objects; o++ )
				{
					ObjectLayerObj object;

					READ_BUFFER( &object, sizeof(object) );
					the_map.objects[o].category = (short)object.category;
					the_map.objects[o].number = (short)object.number;


					// RELOCATE MINES TO CENTER, FOR EASY FINDING
					if (object.category == EXPLOSIVES && object.number == ARMY_MINE)
					{
						object.x = ((object.x >>4) << 4) + 8;
						object.y = ((object.y >>4) << 4) + 8;
					}

					the_map.objects[o].cell.world_pos.x = (short) object.x;
					the_map.objects[o].cell.world_pos.y = (short) object.y;
					the_map.objects[o].layer = curlayer;
					the_map.objects[o].owner = -1;
					the_map.objects[o].group = 0;

					if( object.number >= the_map.max_objs[object.category] )
						the_map.max_objs[object.category] = (short)object.number + 1;
					the_map.num_objs[object.category]++;
				}

				if (new_version)	
				{
					long	sub_chunk_name;
					long	sub_chunk_size;

					READ_LONG(&sub_chunk_name);
					READ_LONG(&sub_chunk_size);
					ASSERT(sub_chunk_name == OATT);

					READ_LONG(&attributes);
					ASSERT(attributes <= MAX_OBJECT_ATTRIBS);

					total_size = sub_chunk_size;
					target_size = sizeof(attributes);

					for (int j=0; j<attributes; j++)	
					{
						READ_LONG(&attribs[j].name);
						READ_LONG(&attribs[j].size);
						target_size += sizeof(attribs[j].name) + sizeof(attribs[j].size);
					}

					file_index += sub_chunk_size + 8;
				}
				else	
				{
					total_size = chunk_size;
					attributes = OLD_OBJECT_ATTRIBS;
				}

				plRead = &read;
				psRead = (short *) &read;
				pcRead = (char *) &read;

				READ_LONG(&num_objects);
				target_size += sizeof(num_objects);

				for( o = 0; o < num_objects; o++ )	
				{
					for (int j=0; j<attributes; j++)	
					{
						READ_BUFFER(&read, attribs[j].size);
						target_size += attribs[j].size;

						switch(attribs[j].name)	{
							case INDX:
								index = n + *plRead;
								break;
							case GRUP:
								the_map.objects[index].group = *pcRead;
								break;
							case PADS:
//								the_map.objects[index].pad = *psRead;
								break;
							case MOVE:
								the_map.objects[index].movement = *pcRead;
								break;
							case ELOW:
								temp = *pcRead;
								the_map.objects[index].elevation = ELEVATION(temp);
								the_map.objects[index].owner = OWNER(temp);
								break;
							case TRIG:
								the_map.objects[index].triggers = *pcRead;
								the_map.objects[index].xtriggers = 0;  // no extended triggers yet
								break;
							case RESV:
								break;
							case NUMB:
								the_map.objects[index].howmany = *pcRead;
								break;
							case SCRI:
                                char nameBuffer[200];
								long size = *plRead;	// size of text block
								if (size)	{
                                    OBJECT* pObj;
                                    pObj = &the_map.objects[index];
									READ_BUFFER(nameBuffer, size);
									target_size += size;
                                    ItemSetLabel((ITEM*)pObj,nameBuffer);
								}
								break;
						}
					}
				}

				if (target_size > total_size)	{
					TRACE("OATT size wrong: %d instead of %d\n", total_size, target_size);
					ASSERT(FALSE);
				}
				else if (target_size < total_size){
					;
//					TRACE("OATT size wrong: %d instead of %d\n", total_size, target_size);
//					fseek(pFile, total_size - target_size, SEEK_CUR);
				}
				if( curlayer <= OL_ORDEREDLAYER )
					curlayer = (EObjectLayer)((int)curlayer + 1);
				break;

			case SCEN:
				char *scene_data;

				scene_data = (char *) malloc(chunk_size);

				if (scene_data)	{
					READ_BUFFER(scene_data, chunk_size);

					SetupScenario(scene_data, chunk_size);

					free(scene_data);
				}
				else	{
					TRACE("ERROR: failed to malloc scene_data\n");
				}

				break;

			case MOVE:	// movement layer
				target_size = the_map.width * the_map.height * sizeof(char);

				if (chunk_size < target_size)	{
					TRACE("MOVE size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}

				the_map.movement_layer = (signed char *)malloc(target_size);
				READ_BUFFER(the_map.movement_layer, target_size);

#ifndef FINAL
				the_map.debug_layer = (signed char *)malloc(target_size);
				ZeroMemory(the_map.debug_layer, target_size);
#endif

				if (chunk_size > target_size)	{
					TRACE("MOVE size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - (target_size), SEEK_CUR);
				}
				break;

			case ELOW:	// elevation/owner layer
				target_size = the_map.width * the_map.height * sizeof(char);

				if (chunk_size < target_size)	{
					TRACE("ELOW size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}

				the_map.owner_layer = (unsigned char *)malloc(target_size);
				READ_BUFFER(the_map.owner_layer, target_size);

				if (chunk_size > target_size)	{
					TRACE("ELOW size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - (target_size), SEEK_CUR);
				}
				break;

			case TRIG:	// triggers layer
				target_size = the_map.width * the_map.height * sizeof(char);

				if (chunk_size < target_size)	{
					TRACE("TRIG size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}

				the_map.triggers = (unsigned char *)malloc(target_size);
				READ_BUFFER(the_map.triggers, target_size);

				SetTileTrafficable();	// mark the untrafficable tiles as permanently so

				if (chunk_size > target_size)	{
					TRACE("TRIG size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - (target_size), SEEK_CUR);
				}
				break;

			case PADS:	// pads layer
				fseek(pFile, chunk_size, SEEK_CUR);
				break;

			case BPAD:	// bit pads layer
				target_size = the_map.width * the_map.height * sizeof(char);

				if (chunk_size < target_size)	{
					TRACE("BPAD size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}

				the_map.bit_pads_layer = (unsigned char *)malloc(target_size);
				READ_BUFFER(the_map.bit_pads_layer, target_size);

				if (chunk_size > target_size)	{
					TRACE("BPAD size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - (target_size), SEEK_CUR);
				}

				break;

			case NPAD:	// number pads layer
				target_size = the_map.width * the_map.height * sizeof(char);

				if (chunk_size < target_size)	{
					TRACE("BPAD size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}

				the_map.numeric_pads_layer = (unsigned char *)malloc(target_size);
				READ_BUFFER(the_map.numeric_pads_layer, target_size);

				if (chunk_size > target_size)	{
					TRACE("NPAD size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - (target_size), SEEK_CUR);
				}

				break;


			default:
				TRACE("Unknown chunk name: %s\n", (char *) &chunk_name);
				ASSERT(FALSE);
				fseek(pFile, chunk_size, SEEK_CUR);
				break;
		}

		file_index += chunk_size + 8;
	}
	while (file_index < file_size);

	AddExtraDependentObjects();
//	ForceLoadIdentityPalette(the_map.terrain_name);
	LoadIdentityPalette(the_map.terrain_name);
	the_map.redraw = REDRAW_FULL;

	the_map.tileboundrect.left = VISIBLE_BOUNDARY;
	the_map.tileboundrect.top = VISIBLE_BOUNDARY;
	the_map.tileboundrect.right = the_map.width - VISIBLE_BOUNDARY;
	the_map.tileboundrect.bottom = the_map.height - VISIBLE_BOUNDARY;

	the_map.boundrect.left = VISIBLE_BOUNDARY << 4;
	the_map.boundrect.top = VISIBLE_BOUNDARY << 4;
	the_map.boundrect.right = the_map.FullPixelRect.right - (VISIBLE_BOUNDARY << 4);
	the_map.boundrect.bottom = the_map.FullPixelRect.bottom - (VISIBLE_BOUNDARY << 4);

	the_map.sargeboundrect.left=the_map.boundrect.left+16;
	the_map.sargeboundrect.top=the_map.boundrect.top+32;
	the_map.sargeboundrect.right=the_map.boundrect.right-16;
	the_map.sargeboundrect.bottom=the_map.boundrect.bottom-16;

	the_map.limitboundrect.left = 4 << 4;
	the_map.limitboundrect.top = 4 << 4;
	the_map.limitboundrect.right = the_map.FullPixelRect.right - (4 << 4);
	the_map.limitboundrect.bottom = the_map.FullPixelRect.bottom - (4 << 4);

	the_map.quake_time = 0;
	the_map.quake_offsx = 0;
	the_map.quake_velx = 0;
	the_map.quake_offsy = 0;
	the_map.quake_vely = 0;

exit:
	if ( pFile )
		fclose( pFile );


	MapLoaded = TRUE;

	return ok;
}


void MapAssetCreate( void )	
{
	OBJECT	*pObject;
	int		j;
	int		nAssets[4] = 
				{0, 0, 0, 0};
	int		eArmy;

	for( j = 0; j < the_map.num_objects; j++ )	
	{
		pObject = &the_map.objects[j];
		if( pObject->attribute == ARMY_ASSET )	
		{
			eArmy = ITEM_ARMY(pObject);
			ASSERT( (eArmy >= ARMY_PLAYER) && (eArmy < ARMY_LAST_ARMY) );

			if( AssetCreate( (ARMY_TYPE)eArmy, pObject, &(pObject->common.position) ) )
				TRACE( "WARNING: failed to create map ASSET object [ %s : %d ]\n", __FILE__, __LINE__ );
			switch( pObject->number )
			{
			case 201:
			case 202:
				pObject->common.pWeapon = MakeWeapon( pObject->common.pWeapon, 
														ARMY_GUARD_TOWER_RIFLE, -1 );
				SetWeaponOwner(pObject->common.pWeapon, (ITEM *)pObject);
				break;
			default:
				break;
			}
			nAssets[eArmy]++;
		}
	}

	//  allocate memory for asset lists on a per legion basis
	LEGION *pLegion;

	for( eArmy = ARMY_PLAYER; eArmy < ARMY_LAST_ARMY; eArmy++ )
	{
		pLegion = ArmyGetLegion(eArmy);
		pLegion->nAssets = nAssets[eArmy];
		if( pLegion->nAssets > 0 )
			pLegion->AssetList = (OBJECTSTRUCT **)malloc( sizeof(OBJECTSTRUCT *) * pLegion->nAssets );
		else
			pLegion->AssetList = NULL;
		nAssets[eArmy] = 0;
	}

	//	add objects to appropriate legion's asset list
	for( j = 0; j < the_map.num_objects; j++ )
	{
		pObject = &the_map.objects[j];

		if( pObject->attribute == ARMY_ASSET )
		{
			eArmy = ITEM_ARMY(pObject);

			pLegion = ArmyGetLegion( eArmy );
			pLegion->AssetList[nAssets[eArmy]++] = pObject;
		}
	}
}	//	MapAssetCreate

void	MapAssetDeleteOfArmy(int eArmy )// local army
{
	OBJECT	*pObject;
	LEGION *pLegion;
    int j;
    pLegion = ArmyGetLegion(eArmy);

    // release each asset
	for( j = 0; j < pLegion->nAssets; j++ )	
	{
		pObject = pLegion->AssetList[j];

        // delete the weapon the asset has
        FreeWeapon( pObject );

        // delete the asset tad operator
        if ( pObject->common.pTad )
        {
            // delete the tad object for this asset
            UnitValidateTad(); // just test the hell out of the links
            TadDeleteObject( (TAD*) (pObject->common.pTad));
            pObject->common.pTad = NULL;
            UnitValidateTad(); // just test the hell out of the links
        }

        // now unlink object from map and display
        if( pObject->cell.flags | ANIM_FLAG_ACTIVE )
        {
            MapRemoveObject( pObject );
            pObject->triggers |= TRIGGER_UNDEPLOYED;
            pObject->triggers |= TRIGGER_DESTROYED;
		}
	}

    // now release the asset list
    if( pLegion->AssetList) free( pLegion->AssetList);
    pLegion->AssetList = NULL;
    pLegion->nAssets = 0;

}	//	MapAssetDelete


BOOL
LoadTileSet(char *pFilename)	{
	FILE* pFile = NULL;
	BOOL	ok = TRUE;
	long	chunk_name;
	long	file_size;
	long	file_index = 0;
	long	chunk_size;
	long	target_size;
	Version version;
	TileHeader thdr;

	ZeroMemory(&version, sizeof(version));
	ZeroMemory(&thdr, sizeof(thdr));

	if ( (pFile = (FILE*)fopen( pFilename, "rb" )) == NULL )	{
		// report an error
		Error("ERROR: failed to open tile file: \"%s\". [%s:%d]\n", pFilename, __FILE__, __LINE__ );
		ok = FALSE;
		goto exit;
	}

	READ_LONG(&chunk_name);
	file_index += sizeof(long);
	if (chunk_name != FORM)	{
		// report an error
		TRACE("ERROR: %s is not an Army Men Tile file of FORM\n", pFilename );
		ASSERT(0);
		ok = FALSE;
		goto exit;
	}

	READ_LONG(&file_size);
	file_index += sizeof(long);

	READ_LONG(&chunk_name);
	file_index += sizeof(long);
	if (chunk_name != TILE)	{
		// report an error
		TRACE("ERROR: %s is not an Army Men Tile file of TILE\n", pFilename );
		ASSERT(0);
		ok = FALSE;
		goto exit;
	}

	do	{
		READ_LONG(&chunk_name);
		READ_LONG(&chunk_size);

		switch(chunk_name)	{
			case VERS:
				target_size = sizeof(Version);
				if (chunk_size < target_size)	{
					TRACE("VERS size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					break;
				}

				READ_BUFFER(&version, target_size);

				if (chunk_size > target_size)	{
					TRACE("VERS size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - target_size, SEEK_CUR);
				}
				break;

			case THDR:
				target_size = sizeof(TileHeader);

				if (chunk_size < target_size)	{
					TRACE("THDR size too small: %d\n", chunk_size);
					fseek(pFile, chunk_size, SEEK_CUR);
					ok = FALSE;
					goto exit;
				}

				READ_BUFFER(&thdr, target_size);

				if (chunk_size > target_size)	{
					TRACE("THDR size too big: %d\n", chunk_size);
					fseek(pFile, chunk_size - target_size, SEEK_CUR);
				}

				the_tiles.max_tiles = thdr.max_tiles;
				the_tiles.width = thdr.width;
				the_tiles.height = thdr.height;

				if (thdr.width != 0x10 || thdr.height != 0x10 || thdr.tiles_wide != 0x20)	{
					Error("Tile Set Error: Wrong Size");
					ASSERT(0);
				}

				break;

			case DIB:
				LOADBITMAP lbitmap;

				#if defined(_USESYSTEMMEMORY_)
					lbitmap.flags = BM_SYSTEMMEMORY;
				#else
					DWORD			dwTotalFreeMem, dwTotalAvailMem, dwPrevMem;
					DDSCAPS			ddsc;
					ddsc.dwCaps = DDSCAPS_OFFSCREENPLAIN;
					pDirectDraw2->GetAvailableVidMem(&ddsc,	&dwTotalFreeMem, &dwTotalAvailMem);
					dwPrevMem = dwTotalAvailMem;

					if( (DWORD)(the_tiles.max_tiles * 256) < dwTotalAvailMem)
						lbitmap.flags = BM_DEFAULTMEMORY;
					else
						lbitmap.flags = BM_SYSTEMMEMORY;
				#endif

				if (!DDReadBitmap(pFile, &lbitmap))	{
					TRACE("ERROR: Can't load tile bitmap [%s:%d]\n", __FILE__, __LINE__ );
					ok = FALSE;
					goto exit;
				}

				#if !defined(_USESYSTEMMEMORY_)
					pDirectDraw2->GetAvailableVidMem( &ddsc, &dwTotalFreeMem, &dwTotalAvailMem );

//#ifdef COMMENTED_OUT
					if ( dwPrevMem > dwTotalAvailMem )
						TRACE( "Tileset loaded in video memory (%d bytes).\n", dwPrevMem-dwTotalAvailMem );
					else
						TRACE( "Tileset loaded in main memory (%d bytes).\n", lbitmap.width * lbitmap.height );
//#endif
				#endif

				the_tiles.tile_data = (LPDIRECTDRAWSURFACE) lbitmap.pGraphic;

				DWORD xpc  = DDColorMatch(the_tiles.tile_data, thdr.rgbTransparent);
				DDSetColorKey(the_tiles.tile_data, xpc);
				break;
		}

		file_index += chunk_size + 8;
	}
	while (file_index < file_size);

exit:
	if ( pFile )
		fclose( pFile );

	return ok;
}


void RestoreTileData( void )
{
	if( !(the_tiles.tile_data) )
		return;
	if( the_tiles.tile_data->IsLost() == DDERR_SURFACELOST )
	{
		if( the_tiles.tile_data->Release() != DD_OK )
		{
			TRACE( "Unable to release tile set\n" );
		}
		SetPath( MAP_PATH );
		the_tiles.tile_data = NULL;
		if( !LoadTileSet(the_map.tile_name) )
		{
			TRACE( "Unable to reload tile set\n" );
		}
	}
}


#ifndef FINAL
COLORREF	displaydebug = 0;

void
DisplayDebugLayer(COLORREF set)	{
	displaydebug = set;
	if (set)
 		the_map.redraw = REDRAW_FULL;
}
#endif


///========================================================================
//	Function:		DisplayDebugInBox()
//
//	Description:
//		
//
//	Input:			none.
//
//	Ouput:			none.
//
///========================================================================
#ifndef FINAL
void
DisplayDebugInBox(SBOX *pBox)	{
	COLORREF	fgColor;
	COLORREF	bgColor;
	char	character[2];
	SBOX	intersect;
	LONG	layer_width,
			base_index,
			index,
			xb,
			yb,
			xe,
			ye,
			tilex,
			tiley,
			x,
			y;		

	if (!displaydebug)
		return;

	character[1] = '\0';

	// save the current Text Colors
	TextGetColors( &fgColor, &bgColor );
	TextSetColors(displaydebug, RGB_BLACK );
	TextSetTransparent(FALSE);
	
	layer_width = the_map.width;

	BoxIntersect(pBox, &the_map.TileBox, &intersect);

	xb = intersect.x;
	xe = intersect.x + intersect.cx;

	yb = intersect.y;
	ye = intersect.y + intersect.cy;

	y = ((yb - the_map.TileBox.y) << 4);
	base_index = yb*layer_width + xb;
	for (tiley=yb; tiley<ye; tiley++)	{
		x = ((xb - the_map.TileBox.x) << 4);
		index = base_index;
		for (tilex=xb; tilex<xe; tilex++)	{
			character[0] = the_map.debug_layer[index++];
			if (!isprint(character[0]))
				character[0] = ' ';
			if (character[0] == '.')	{
				TextWrite( pDebugBuffer, x+4, y+4, " ", FONT_MAP, NULL );
				TextWrite( pDebugBuffer, x+4, y, character, FONT_MAP, NULL );
			}
			else
				TextWrite( pDebugBuffer, x+4, y+4, character, FONT_MAP, NULL );
			x += 16;
		}
		base_index += layer_width;
		y+=16;
	}

	// restore the current Text Colors
	TextSetColors( fgColor, bgColor );
	TextSetTransparent(TRUE);
}
#endif


#define  THIS_TILE_VISIBLE_FLAG		0x10
#define  UP_TILE_VISIBLE_FLAG		0x01
#define  RIGHT_TILE_VISIBLE_FLAG	0x02
#define  DOWN_TILE_VISIBLE_FLAG		0x04
#define  LEFT_TILE_VISIBLE_FLAG		0x08
#define  NEIGHBOR_TILE_MASK			0x0f


//	Determine point-of-view for an item (affects what the item can see)
int  GetItemPov( ITEM *pItem )
{
	int pov;
	int itype;

	if( !pItem )
		return 3;

	itype = ITEM_TYPE(pItem);
	switch( itype )
	{
	case ARMY_SARGE:
		switch( AvatarPose( ((SARGE *)pItem)->pAvatar ) )
		{
		case AVATAR_KNEEL:
			pov = 2;
			break;
		case AVATAR_STAND:
			pov = 3;
			break;
		case AVATAR_PRONE:
			pov = 1;
			break;
		}
		break;
	case ARMY_TROOPER:
		switch( AvatarPose( ((TROOPER *)pItem)->pAvatar ) )
		{
		case AVATAR_KNEEL:
			pov = 2;
			break;
		case AVATAR_STAND:
			pov = 3;
			break;
		case AVATAR_PRONE:
			pov = 1;
			break;
		}
		break;
	case ARMY_ASSET:
		pov = 4;
		break;
	default:
		pov = 3;
		break;
	}
	return( pov );
}	//	GetItemPov


inline int GetItemLosLimit( ITEM *pItem )
{
	if( !pItem )
		return 0;
	switch( ITEM_TYPE(pItem) )
	{
	case ARMY_SARGE:
		return( LOS_CIRCLE_SIZE );
	case ARMY_TROOPER:
	case ARMY_UNIT:
		return( TROOPER_LOS_LIMIT );
	default:
		return( LOS_CIRCLE_SIZE );
	}
}	//	GetItemLosLimit


BOOL IsClearTo( int start_tile, int end_tile, int pov )
{
	if( the_map.vis_layer[start_tile] < pov )
		return TRUE;
	else
		return FALSE;
}


inline int SignOf( int i )
{
	return( i < 0 ? -1 : 1 );
}


BOOL IsLosClear( SPOINT &start_tilepos, SPOINT &end_tilepos, ITEM *pItem )
{
	int dx, dy, absdx, absdy, x, y, pov;
    BOOL sees;
	short LosStack[500];
	short LosStackTop;
	short i;
	TLosCircle *ploc;

	if( !pItem )
		return FALSE;
	dx = end_tilepos.x - start_tilepos.x;
	dy = end_tilepos.y - start_tilepos.y;
	absdx = abs(dx);
	absdy = abs(dy);
	if( absdx > 20 || absdy > 20 )
		return FALSE;
	if( absdx <= 1 && absdy <= 1 )
		return TRUE;
	i = LosByOffsets[dy+20][dx+20];					// note: array is reversed x-y
	if( i < 0 )
		return FALSE;
	if( i >= GetItemLosLimit( pItem ) )
		return FALSE;
	x = start_tilepos.x;
	y = start_tilepos.y;
	pov = GetItemPov( pItem );
	LosStack[0] = i;
	LosStackTop = 0;
	while( LosStackTop >= 0 )
	{
		i = LosStack[LosStackTop--];
		ploc = &(LosCircle[i]);
		if( ploc->dep1 == 0 )
			return TRUE;
		if( ploc->dep2 > 0 )
		{
			sees = FALSE;
			if( IsClearTo( 
				IndexOf( x + LosCircle[ploc->dep1].xoffs, y + LosCircle[ploc->dep1].yoffs ),
				IndexOf( x + LosCircle[i].xoffs, y + LosCircle[i].yoffs ), pov ) )
			{
				LosStack[++LosStackTop] = ploc->dep1;
				sees = TRUE;
			}
			if( IsClearTo(
				IndexOf( x + LosCircle[ploc->dep2].xoffs, y + LosCircle[ploc->dep2].yoffs ),
				IndexOf( x + LosCircle[i].xoffs, y + LosCircle[i].yoffs ), pov ) )
			{
				LosStack[++LosStackTop] = ploc->dep2;
				sees = TRUE;
			}
			if( sees == FALSE )
				return FALSE;
		}
		else 
		if( ploc->dep1 > 0 )
		{
			if( IsClearTo( 
				IndexOf( x + LosCircle[ploc->dep1].xoffs, y + LosCircle[ploc->dep1].yoffs ),
				IndexOf( x + LosCircle[i].xoffs, y + LosCircle[i].yoffs ), pov ) )
			{
				LosStack[++LosStackTop] = ploc->dep1;
			}
			else
				return FALSE;
		}
	}
	return TRUE;
}


BOOL IsLosClearByTile( int start_tile, int end_tile, ITEM *pItem )
{
	SPOINT  stile_pos, etile_pos;

	if( !pItem )
		return FALSE;
	stile_pos.y = start_tile >> the_map.bitwidth;
	stile_pos.x = (short)(start_tile & the_map.xmask);
	etile_pos.y = (short)(end_tile >> the_map.bitwidth);
	etile_pos.x = (short)(end_tile & the_map.xmask);
	return (IsLosClear( stile_pos, etile_pos, pItem ));
}



#ifndef FINAL
void
SetValueInDebugLayer(SHORT tilex, SHORT tiley, char value)	{
	int index = tiley*the_map.width + tilex;
	SPOINT pt;

	pt.x = tilex;
	pt.y = tiley;

	if (the_map.debug_layer[index] != value)	{
		the_map.debug_layer[index] = value;

		if (InBox(&the_map.TileBox, &pt))	{
			SBOX box;

			box.x = tilex;
			box.y = tiley;
			box.cx = 1;
			box.cy = 1;

			DisplayDebugInBox(&box);
		}
	}
}
#endif


#if defined(_DEBUG)
void
RefreshDebugBox(SBOX *pBox)	{
	SBOX ibox;

	if (BoxIntersect(pBox, &the_map.TileBox, &ibox))	{
		DisplayDebugInBox(&ibox);
	}
}
#endif


void SetObjectDefaults( OBJECT *pObject )
{
	AI_ITBL *pAiIndDef = AiGetObjectDefs( pObject->category, pObject->number, pObject->damageindex );
	if( pAiIndDef )
	{
		pObject->common.nStrength = pObject->common.nMaxStrength = pAiIndDef->nHitPoints;
		pObject->elevation = pAiIndDef->nHeight;
		pObject->movement = pAiIndDef->nMovement;
		pObject->visibility = pAiIndDef->nVisibility;
		pObject->permeability = pAiIndDef->nPermeability;
		pObject->armor = pAiIndDef->nArmor;
		// certain object (types) should be forced into the ground layer!
		// this is a hack, but we don't want to have to go and edit every map
		// and no one has time to put all this junk in the aai files
		switch( pObject->category )
		{
		case ROCK:
			if( pObject->number >= 212 && pObject->number <= 224 )
				pObject->layer = OL_GROUNDLAYER;
			break;
		case BUSH:
			pObject->layer = OL_GROUNDLAYER;
			break;
		case SPECIAL_ITEMS:
			switch( pObject->number )
			{
			case ARMY_GRENADE:
			case ARMY_FLAME_THROWER:
			case ARMY_BAZOOKA:
			case ARMY_MORTAR:
			case ARMY_AUTORIFLE:
			case ARMY_MINE:
			case ARMY_EXPLOSIVE_WEAPON:
			case ARMY_SWEEPER:
			case ARMY_MEDKIT:
			case ARMY_MEDPACK:
			case ARMY_AIRSTRIKE:
			case ARMY_PARATROOPERS:
			case ARMY_RECON:
			case ARMY_SPECIAL_1:
				pObject->layer = OL_GROUNDLAYER;
			}
			break;
		}
	}
	else
	{
		pObject->common.nStrength = pObject->common.nMaxStrength = 0;
		pObject->elevation = 0;
		pObject->movement = 0;
		pObject->visibility = 0;
		pObject->permeability = 0;
		pObject->armor = 0;
	}
}


///========================================================================
//	Function:		SetCategoryAttributes()
//
//	Description:	sets up object attributes that don't come in from the 
//					map info; sets up baseinfo
//
//	Input:			pobject		pointer to an object
//					id			id of object
//
//	Ouput:			none
//
///========================================================================

void SetCategoryAttributes(OBJECT *pobject, int id)	{
	int army = ARMY_INDEPENDENT;

	army = OBJECT_OWNER(pobject);
	army = gpComm->IndexFromColor((ARMY_COLOR)army);
	pobject->owner = army; // decode to local

	switch (pobject->category)	{
		case ROCK:
			pobject->attribute = ARMY_OBSTACLE;
			break;

		case FALLEN_TREE:
		case WALL:
		case GATE:
		case BUSH:
		case FENCE:
		case MISCELLANEOUS:
		case TREE:
		case EXPLOSIVES:
			pobject->attribute = ARMY_OBSTACLE;
			pobject->triggers |= TEMPORARY_OBJECT;
			break;

		case BRIDGE:
			pobject->attribute = ARMY_STRUCTURE;
			pobject->triggers |= TEMPORARY_OBJECT;
			break;

		case BASE:
		case AUX_BASE:
		case BUILDING:
			pobject->attribute = ARMY_STRUCTURE;
			pobject->triggers |= TEMPORARY_OBJECT;
			break;

		case AA_GUN:
		case GUN_TURRET:
		case PILL_BOX:
			pobject->attribute = ARMY_ASSET;
			pobject->triggers |= TEMPORARY_OBJECT;
			break;

		case SPECIAL_ITEMS:
			pobject->attribute = ARMY_OBSTACLE;
			pobject->triggers |= TEMPORARY_OBJECT;
			ArmyUnitTypeExist(pobject->number);	// the unit type must exist for sarge if he can pick up a weapon
            pobject->common.pWeapon = MakeWeapon( pobject->common.pWeapon,
                                                  (WEAPON_TYPE)pobject->number,
                                                  pobject->howmany);
            // note the paratrooper boxes to be picked up
            if (pobject->number == ARMY_PARATROOPERS) 
              ParaDropBoxCount += pobject->howmany;
            break;
//		case AIR_STRIP:
//		case HELI_PAD:
//		case POWER_PLANT:
//		case RADAR_BUILDING:
//		case FENCE_GATE:
//		case WALL_GATE:
//		case PRISON_CAMP:
//		case BIG_TREE:
//		case FOOT_BRIDGE:
//		case OVERPASS:

	}


	ItemSetUID((ITEM*)pobject,army,pobject->attribute,pobject->category,id);
    ItemSetLocation((ITEM*)pobject,&(pobject->cell.world_pos));
    ItemSetOldLocation((ITEM*)pobject);

	SetObjectDefaults( pobject );



}


void MapGraphicsFree( void )	
{
	int i,j, k;

	if (!MapGraphicsLoaded)
		return;

	if (the_tiles.tile_data)
		the_tiles.tile_data->Release();
	the_tiles.tile_data = NULL;

	if( !_LOAD_FROM_DATAFILE )			// only if static load
	for (i=0; i<NUM_OBJECT_TYPES; i++)	
	{
		OBJECT_SPRITE *pObjSprite = the_map.obj_sprite_array_list[i];
		if (pObjSprite)	
		{
			for (j=0; j<the_map.max_objs[i]; j++)
			{
				for (k=0; k<pObjSprite[j].nLevelsOfDamage; k++)
					FreeSprite(&pObjSprite[j].sprites[k]);
				free(pObjSprite[j].sprites);
			}
		}
	}

	MapGraphicsLoaded = FALSE;
}


void MapFree( void )
{
	int i;

	if (!MapLoaded)
		return;

	//	free the tile layers
	for (i=0; i<the_map.num_layers; i++)	
	{
		if (the_map.layers[i].tile_array)
			free(the_map.layers[i].tile_array);
		the_map.layers[i].tile_array = NULL;
	}
	the_map.num_layers = 0;

	if (the_map.objects)	
	{
		// free any assets
		OBJECT* pobject;
		for (int j=0; j<the_map.num_objects; j++)	
		{
			pobject = &the_map.objects[j];

			if( pobject )
			{
				AnimDelete( (ANIM *)(&(pobject->cell)) );
			}
			if (pobject->common.label)	
			{
				free(pobject->common.label);
				pobject->common.label = NULL;
			}

			FreeWeapon( pobject );

	/*
#ifdef ASSET_DEBUG
			//=======================================
			// Currently handled in MapAssetDelete()
			// to match use of MapAssetCreate()
			//=======================================
			if ( pobject->attribute == ARMY_ASSET )	
			{
				if ( pobject->common.pTad )
					AssetDelete( pobject->common.pTad );
			}
            if (pobject->common.pTad)
            {
               TadDeleteObject((TAD*)pobject->common.pTad);
               pobject->common.pTad = NULL;
            }
#endif
	*/
		}
		free(the_map.objects);
		the_map.objects = NULL;
	}

	//	free sprites
	if( !_LOAD_FROM_DATAFILE )							// only for static load
	for (i=0; i<NUM_OBJECT_TYPES; i++)	
	{
		if (the_map.obj_sprite_array_list[i])	
		{
			free(the_map.obj_sprite_array_list[i]);
			the_map.obj_sprite_array_list[i] = NULL;
		}
	}

	if (the_map.elevation_layer)	{
		free(the_map.elevation_layer);
		the_map.elevation_layer = NULL;
	}

	if (the_map.movement_layer)	{
		free(the_map.movement_layer);
		the_map.movement_layer = NULL;
	}


	if( the_map.vis_layer )
	{
		free( the_map.vis_layer );
		the_map.vis_layer = NULL;
	}

	if (the_map.triggers)	{
		free(the_map.triggers);
		the_map.triggers = NULL;
	}

	if (the_map.bit_pads_layer)	{
		free(the_map.bit_pads_layer);
		the_map.bit_pads_layer = NULL;
	}

	if (the_map.numeric_pads_layer)	{
		free(the_map.numeric_pads_layer);
		the_map.numeric_pads_layer = NULL;
	}

#ifndef FINAL
	if (the_map.debug_layer)	{
		free(the_map.debug_layer);
		the_map.debug_layer = NULL;
	}
#endif

	if (the_map.desc)	{
		free(the_map.desc);
		the_map.desc = NULL;
	}

	if (the_map.missiontext)
	{
		free(the_map.missiontext);
		the_map.missiontext=NULL;
	}

	if (the_map.objtext)
	{
		free(the_map.objtext);
		the_map.objtext=NULL;
	}

	FreeObjectLayer( &the_map.toplayer );
	FreeObjectLayer( &the_map.orderedlayer );
	FreeObjectLayer( &the_map.groundlayer );
	FreeObjectLayer( &the_map.overlaylayer );

	DeleteScenario();

	MapLoaded = FALSE;
}

void ResetMapWindow(void)
{
	the_map.redraw = REDRAW_FULL;
	SetMapWindowWidths();
}

void
SetMapGameWindow()	{
	rcGameWindow = rcGameSurface;
}

void
SetBackGameWindow()	{
	rcGameWindow = rcBackWindow;
}

void
SetMapWindowWidths()	{
	rcGameSurface = rcBackWindow;
	rcGameSurface.bottom -= 94;

	the_map.PixelBox.cx = (short)rcGameSurface.right;
	the_map.TileBox.cx = (short)((rcGameSurface.right + 16) >> 4);

	the_map.PixelBox.cy = (short)rcGameSurface.bottom;
	the_map.TileBox.cy = (short)((rcGameSurface.bottom + 16) >> 4);

	DisplayBox = the_map.PixelBox;
}


OBJECT* XYInObjectMask(int x, int y, int category)	{

	int i;
	OBJECT *pobj;
	LPDIRECTDRAWSURFACE	pSurface;
	HRESULT ddrval;
	DDSURFACEDESC ddsd;
	SPOINT pos;
	BYTE *ptr;
	BYTE pixel;

	pobj = the_map.obj_type_list[category];

	for (i=0; i<the_map.num_objs[category]; i++)	{
		LONG obj_num = pobj[i].number;
		if (obj_num != NO_OBJECT)	{
			SPRITE *pSprite = pobj[i].cell.pSprite;
			if (pSprite)	{
				pos.x = x - pobj[i].cell.world_pos.x + pSprite->hotspot.x;
				pos.y = y - pobj[i].cell.world_pos.y + pSprite->hotspot.y;

				if (InRect(&pSprite->srect, &pos))	{
					ZeroMemory( &ddsd, sizeof( DDSURFACEDESC ) );
					ddsd.dwSize = sizeof(DDSURFACEDESC);

					if (pSprite->pMask)	{
						ptr = (BYTE *) pSprite->pMask;
						int pitch = ((pSprite->srect.right+7)/8) & ~3;
						pixel = ptr[(pos.y * pitch) + pos.x];
						if (pixel == 0)
							return NULL;
					}
					else	
					{
						if ( pSprite->sprite_flags  & SP_DRLE)
						{
							if (!IsPointInDRle( pos.x, pos.y, (BYTE *)(pSprite->pGraphic) ))
								return NULL;
						}
						else if ( pSprite->sprite_flags & (SP_WRLE | SP_TRLE) )
						{
							if (!IsPointInWRle( pos.x, pos.y, (BYTE *)(pSprite->pGraphic) ))
								return NULL;
						}
						else
						{
							pSurface = (LPDIRECTDRAWSURFACE) pSprite->pGraphic;
							ddrval = pSurface->Lock(NULL, &ddsd, DDLOCK_WAIT|DDLOCK_READONLY, NULL);
							if (ddrval == DD_OK)	
							{
								ptr = (BYTE *) ddsd.lpSurface;
								pixel = ptr[(pos.y * ddsd.lPitch) + pos.x];
								pSurface->Unlock(ptr);
								if (pixel == pSprite->xpc)
									return NULL;
							}
						}
					}

					return &pobj[i];
				}
			}
		}
	}

	return NULL;
}


OBJECT *
PointInObject(SPOINT *pPos, int category)	{
	int i;
	OBJECT *pobj;
	LPDIRECTDRAWSURFACE	pSurface;
	HRESULT ddrval;
	DDSURFACEDESC ddsd;
	SPOINT pos;
	BYTE *ptr;
	BYTE pixel;

	pos = *pPos;
	pobj = the_map.obj_type_list[category];

	for (i=0; i<the_map.num_objs[category]; i++)	{
		LONG obj_num = pobj[i].number;
		if (obj_num != NO_OBJECT)	{
			SPRITE *pSprite = pobj[i].cell.pSprite;
			if (pSprite)	{
				pos.x = pPos->x - pobj[i].cell.world_pos.x + pSprite->hotspot.x;
				pos.y = pPos->y - pobj[i].cell.world_pos.y + pSprite->hotspot.y;

				if (InRect(&pSprite->srect, &pos))	
				{
					if ( pSprite->sprite_flags & SP_DRLE )
					{
						if (!IsPointInDRle( pos.x, pos.y, (BYTE *)(pSprite->pGraphic) ))
							return NULL;
					}
					else if ( pSprite->sprite_flags & (SP_WRLE | SP_TRLE) )
					{
						if (!IsPointInWRle( pos.x, pos.y, (BYTE *)(pSprite->pGraphic) ))
							return NULL;
					}
					else
					{
						pSurface = (LPDIRECTDRAWSURFACE) pSprite->pGraphic;
						ZeroMemory( &ddsd, sizeof( DDSURFACEDESC ) );
						ddsd.dwSize = sizeof(DDSURFACEDESC);
						ddrval = pSurface->Lock(NULL, &ddsd, DDLOCK_WAIT|DDLOCK_READONLY, NULL);
						if (ddrval == DD_OK)	
						{
							ptr = (BYTE *) ddsd.lpSurface;
							pixel = ptr[(pos.y * ddsd.lPitch) + pos.x];
							pSurface->Unlock(ptr);
							if (pixel == pSprite->xpc)
								return NULL;
						}
					}
					return &pobj[i];
				}
			}
		}
	}

	return NULL;
}


OBJECT *
PointAroundObject(SPOINT *pPos, int category)	{
	int i;
	OBJECT *pobj;
	RECT rect;

	pobj = the_map.obj_type_list[category];
	for (i=0; i<the_map.num_objs[category]; i++)	{
		LONG obj_num = pobj[i].number;
		if (obj_num != NO_OBJECT)	{
			SPRITE *pSprite;

			pSprite = pobj[i].cell.pSprite;

			rect = pSprite->srect;
			long chgx = (rect.right - rect.left) / 2 - 16;
			long chgy = (rect.bottom - rect.top) / 2 - 16;

			rect.left += pobj[i].cell.world_pos.x + chgx;
			rect.right += pobj[i].cell.world_pos.x - chgx;
			rect.top += pobj[i].cell.world_pos.y + chgy;
			rect.bottom += pobj[i].cell.world_pos.y - chgy;

			if (InRect(&rect, pPos))
				return &pobj[i];
		}
	}

	return NULL;
}


int
AttributeIndicies(RECT *pRect, int *indicies, int max)	{
	int	x,y;
	int number = 0;
	RECT	rcTile;

	rcTile.left = (pRect->left >> 4);
	rcTile.top = (pRect->top >> 4);
	rcTile.bottom = (pRect->bottom >> 4) + 1;	// Rect bottom & right is one beyond
	rcTile.right = (pRect->right >> 4) + 1;
		
	for (y = rcTile.top; y < rcTile.bottom; y++)	{
		for (x = rcTile.left; x < rcTile.right; x++)	{
			indicies[number++] = y*the_map.width + x;
			if (number >= max)	{
				TRACE("WARNING: overflowed indecies array in AttributeIndicies()\n");
				return(number);
			}
		}
	}

	return (number);
}

static BOOL
InObjectRect(ANIMCELL *pAnimObject, SPOINT *pt)	{
	RECT oRect;
	BOOL gotit = FALSE;
	SPRITE *pSprite = pAnimObject->pSprite;

	oRect.left = pAnimObject->world_pos.x - pSprite->hotspot.x;
	oRect.top = pAnimObject->world_pos.y - pSprite->hotspot.y;
	oRect.right = oRect.left + pSprite->maskRect.right;
	oRect.bottom = oRect.top +  pSprite->maskRect.bottom;

	oRect.left += pSprite->maskRect.left;
	oRect.top += pSprite->maskRect.top;

	return InRect(&oRect, pt);
}

static BOOL
ObjectRectOverlap(ANIMCELL *pCell, ITEM_OVERLAP *poverlap)	{
	int	left, right, top, bottom;
	BOOL gotit = FALSE;

	ZeroMemory(poverlap, sizeof(ITEM_OVERLAP));

	if (!(pCell->pSprite->maskRect.right - pCell->pSprite->maskRect.left) || 
		!(pCell->pSprite->maskRect.bottom - pCell->pSprite->maskRect.top))
		return FALSE;

	left = pCell->world_pos.x - pCell->pSprite->hotspot.x;
	top = pCell->world_pos.y - pCell->pSprite->hotspot.y;

	right = left + pCell->pSprite->maskRect.right;
	bottom = top + pCell->pSprite->maskRect.bottom;

	left += pCell->pSprite->maskRect.left;
	top += pCell->pSprite->maskRect.top;

	RECT *pRect = &poverlap->box;
	pRect->left = (left >> 4);
	pRect->top = (top >> 4);
	pRect->bottom = (bottom >> 4) + 1;	// Rect bottom & right is one beyond
	pRect->right = (right >> 4) + 1;

	int	x,y;
	int number = 0;
	for (y = pRect->top; y < pRect->bottom; y++)	{
		for (x = pRect->left; x < pRect->right; x++)	{
			gotit = TRUE;
			poverlap->overlap_list[number++] = (char) TRUE;
			ASSERT(number < sizeof(poverlap->overlap_list));
		}
	}

	return gotit;
}

BOOL
ObjectSelfRect(ANIMCELL *pCell, ITEM_OVERLAP *poverlap)	{
	int	left, right, top, bottom;
	char setchar;

	ZeroMemory(poverlap, sizeof(ITEM_OVERLAP));

	left = pCell->world_pos.x - pCell->pSprite->hotspot.x;
	right = left + pCell->pSprite->srect.right;
	top = pCell->world_pos.y - pCell->pSprite->hotspot.y;
	bottom = top + pCell->pSprite->srect.bottom;

	if( pCell->pSprite->sprite_flags & SP_USESELFRECT )
		setchar = (char)TRUE;
	else
		setchar = (char)FALSE;

	RECT *pRect = &poverlap->box;
	pRect->left = (left >> 4);
	pRect->top = (top >> 4);
	pRect->bottom = (bottom >> 4) + 1;	// Rect bottom & right is one beyond
	pRect->right = (right >> 4) + 1;

	int	x,y;
	int number = 0;
	for (y = pRect->top; y < pRect->bottom; y++)	
	{
		for (x = pRect->left; x < pRect->right; x++)	
		{
			poverlap->overlap_list[number++] = setchar;
			ASSERT(number < sizeof(poverlap->overlap_list));
		}
	}

	return TRUE;
}

BYTE leftbytemask[8]=
{
	0x80,
	0xc0,
	0xe0,
	0xf0,
	0xf8,
	0xfc,
	0xfe,
	0xff
};

BYTE rightbytemask[8]=
{
	0x7f,
	0x3f,
	0x1f,
	0x0f,
	0x07,
	0x03,
	0x01,
	0x00
};



static BOOL ObjectMask(ANIMCELL *pCell)
{
	RECT world_pixels;
	RECT world_tiles;
	int bitwidth, bytewidth;  //witdh of source data
	int tilewidth;
	int y;
	int ytile;
	BYTE *data;
	BOOL switch_on_odd;
	int switchbit;
	int curbyte;
	int curtile;

	data=(BYTE*)pCell->pSprite->pMask;

	world_pixels.left=pCell->world_pos.x-pCell->pSprite->hotspot.x;
	world_pixels.right=world_pixels.left + pCell->pSprite->srect.right;
	world_pixels.top = pCell->world_pos.y - pCell->pSprite->hotspot.y;
	world_pixels.bottom = world_pixels.top + pCell->pSprite->srect.bottom;

	world_tiles.left=(world_pixels.left>>4);
	world_tiles.right=(world_pixels.right>>4)+1;
	world_tiles.top=(world_pixels.top>>4);
	world_tiles.bottom=(world_pixels.bottom>>4)+1;

	tilewidth=world_tiles.right-world_tiles.left;

	bitwidth=((world_pixels.right-world_pixels.left)+31)-(((world_pixels.right-world_pixels.left)+31)%32);
	bytewidth=bitwidth>>3;

	if (bitwidth==0) return FALSE;

	if (world_pixels.left % 16 >= 8)
	{
		switch_on_odd=0;
		switchbit=16-(world_pixels.left % 16);
	}
	else
	{
		switch_on_odd=1;
		switchbit=8-(world_pixels.left % 16);
	}

	for (y=world_pixels.top;y<world_pixels.bottom;y++)
	{
		curbyte=bytewidth*(y-world_pixels.top);
		curtile=0;
		ytile=(y>>4);

		do 
		{
			if (switch_on_odd == (curbyte%2))
			{
				if (data[curbyte] & leftbytemask[switchbit])
					return TRUE;
				curtile++;
				if (curtile==tilewidth)
					break;
				if (data[curbyte] & rightbytemask[switchbit])
					return TRUE;
			}
			else if (data[curbyte])
				return TRUE;
			
			curbyte++;
		} while (curbyte%bytewidth != 0);
	}

	return FALSE;
}


static BOOL ObjectMaskOverlap(ANIMCELL *pCell, ITEM_OVERLAP *poverlap)
{
	RECT world_pixels;
	RECT world_tiles;
	BOOL gotit = FALSE;

	int bitwidth, bytewidth;  //witdh of source data
	int tilewidth;

	int y;
	int ytile;


	BYTE *data;
	

	BOOL switch_on_odd;
	int switchbit;
	int curbyte;
	int curtile;

	ZeroMemory(poverlap, sizeof(ITEM_OVERLAP));

	data=(BYTE*)pCell->pSprite->pMask;


	world_pixels.left=pCell->world_pos.x-pCell->pSprite->hotspot.x;
	world_pixels.right=world_pixels.left + pCell->pSprite->srect.right;
	world_pixels.top = pCell->world_pos.y - pCell->pSprite->hotspot.y;
	world_pixels.bottom = world_pixels.top + pCell->pSprite->srect.bottom;

	world_tiles.left=(world_pixels.left>>4);
	world_tiles.right=(world_pixels.right>>4)+1;
	world_tiles.top=(world_pixels.top>>4);
	world_tiles.bottom=(world_pixels.bottom>>4)+1;

	poverlap->box=world_tiles;

	tilewidth=world_tiles.right-world_tiles.left;

	bitwidth=((world_pixels.right-world_pixels.left)+31)-(((world_pixels.right-world_pixels.left)+31)%32);
	bytewidth=bitwidth>>3;

	if (bitwidth==0) return 0;

	if (world_pixels.left % 16 >= 8)
	{
		switch_on_odd=0;
		switchbit=16-(world_pixels.left % 16);
	}
	else
	{
		switch_on_odd=1;
		switchbit=8-(world_pixels.left % 16);
	}



	

	for (y=world_pixels.top;y<world_pixels.bottom;y++)
	{
		curbyte=bytewidth*(y-world_pixels.top);
		curtile=0;
		ytile=(y>>4);

		do 
		{
			if (switch_on_odd == (curbyte%2))
			{
				if (data[curbyte] & leftbytemask[switchbit])
				{
					gotit=TRUE;
					poverlap->overlap_list[(ytile-world_tiles.top)*tilewidth+curtile] = 1;
				}
				curtile++;
				if (curtile==tilewidth)
					break;
				if (data[curbyte] & rightbytemask[switchbit])
				{
					gotit=TRUE;
					poverlap->overlap_list[(ytile-world_tiles.top)*tilewidth+curtile] = 1;
				}
			}
			else if (data[curbyte])
			{
				gotit=TRUE;
				poverlap->overlap_list[(ytile-world_tiles.top)*tilewidth+curtile] = 1;
			};
			
			curbyte++;
		} while (curbyte%bytewidth != 0);
	}


    /*
	{
		int bitoffset, byteoffset, x, y;

	TRACE("world rectangle goes from (%d, %d) to (%d, %d)\n", 
		world_pixels.left, world_pixels.top, world_pixels.right, world_pixels.bottom);

	TRACE("world tile rectangle goes from (%d, %d) to (%d, %d)\n",
		poverlap->box.left, poverlap->box.top, poverlap->box.right, poverlap->box.bottom);

	TRACE("mask art is as follows:\n");
	for (y=0;y<world_pixels.bottom-world_pixels.top;y++)
	{
		for (x=0;x<world_pixels.right-world_pixels.left;x++)
		{
			bitoffset=y*bitwidth+x;
			byteoffset=(bitoffset>>3);
			bitoffset=bitoffset%8;

			if (data[byteoffset]&(1<<(7-bitoffset)))
				TRACE("1");
			else
				TRACE("0");
		}
		TRACE("\n");
	}
		
	TRACE("returned tile mask is as follows:\n");
	for (y=0;y<world_tiles.bottom-world_tiles.top;y++)
	{
		for (x=0;x<world_tiles.right-world_tiles.left;x++)
			if (poverlap->overlap_list[y*tilewidth+x])
				TRACE("1");
			else
				TRACE("0");
		TRACE("\n");
	}
	}
	*/


	return gotit;
}


BOOL
ObjectSelfMask(ANIMCELL *pCell, ITEM_OVERLAP *poverlap)	{
	BOOL gotit = FALSE;

	ZeroMemory(poverlap, sizeof(ITEM_OVERLAP));

	if( pCell->pSprite->sprite_flags & SP_SRLE )
		return FALSE;

	if (pCell->pSprite->sprite_flags & (SP_RLE | SP_DRLE | SP_WRLE | SP_TRLE) )
	{
		return (ObjectSelfRect(pCell, poverlap));
	}

	if( !(pCell->pSprite->sprite_flags & SP_USESELFRECT) )
		return (ObjectSelfRect(pCell, poverlap));	// if sprite doesn't have a mask or rect, return none

	if ( pCell->pSprite->pGraphic == NULL )
		return FALSE;

	DDSURFACEDESC	ddsd;
	BYTE	*pObjGraphic;
	int		pitch;

	ddsd.dwSize = sizeof(DDSURFACEDESC);
	HRESULT ddrval = ((LPDIRECTDRAWSURFACE) (pCell->pSprite->pGraphic))->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	if (ddrval == DD_OK)	{
		pObjGraphic = (BYTE *)ddsd.lpSurface;
		pitch = ddsd.lPitch;
	}
	else	{
		TRACE("Error on object sprite Lock in ObjectSelfMask()");
		return FALSE;
	}

	int	left, right, top, bottom;
	RECT *pRect = &poverlap->box;
	RECT rcTile;

	left = pCell->world_pos.x - pCell->pSprite->hotspot.x;
	right = left + pCell->pSprite->srect.right;
	top = pCell->world_pos.y - pCell->pSprite->hotspot.y;
	bottom = top + pCell->pSprite->srect.bottom;

	pRect->left = (left >> 4);
	pRect->top = (top >> 4);
	pRect->bottom = (bottom >> 4) + 1;	// Rect bottom & right is one beyond
	pRect->right = (right >> 4) + 1;

	rcTile.left = (left & 0xFFF0) - left;
	rcTile.top = (top & 0xFFF0) - top;
	rcTile.right = pCell->pSprite->srect.right;
	rcTile.bottom = pCell->pSprite->srect.bottom;


// rcTile has a rectangle in object coordinates, with the top/left probably negative
	int	x,y;
	int	xt,yt;
	int height, width;
	BYTE *pTileArea = pObjGraphic;
	BYTE clear = *pTileArea;		// transparent color
	BYTE *pTileLine;
	BYTE *pLine;
	int number = 0;

	for (y = rcTile.top; y < rcTile.bottom; y+=16)	{
		height = 16;
		if (y<0)
			height += y;
		if (y+height >= rcTile.bottom)
			height = rcTile.bottom - y;

		pTileLine = pTileArea;
		for (x = rcTile.left; x < rcTile.right; x+=16)	{
			width = 16;
			if (x<0)
				width += x;
			if (x+width >= rcTile.right)
				width = rcTile.right - x;

			BOOL hit = FALSE;
			pLine = pTileLine;
			for (yt = 0; yt < height; yt++)	{
				for (xt = 0; xt < width; xt++)	{
					if (pLine[xt] != clear)
						hit = TRUE;
				}
				pLine += pitch;
				if (hit)	{
					gotit = TRUE;
					poverlap->overlap_list[number] = (char) TRUE;
					ASSERT(number < sizeof(poverlap->overlap_list));
					break;
				}

			}

			pTileLine += width;
			number++;
		}

		pTileArea += (height*pitch);
	}


	((LPDIRECTDRAWSURFACE) (pCell->pSprite->pGraphic))->Unlock(ddsd.lpSurface);

	return gotit;
}


//  add an object to the movement layer
//  if pDamageOverlap is provided, any differences between the two masks is hit with
//  nCrushDamage with the exception of pExcludeItem
void AddObjectToMovementLayer(OBJECT *pobj, 
							  ITEM_OVERLAP *pDamageOverlap, int nCrushDamage )	
{
	ITEM_OVERLAP overlap;
	BOOL gate = FALSE;
	int	eArmy = ARMY_INDEPENDENT;


	if( pobj->triggers & TRIGGER_UNDEPLOYED )
		return;

	if( !(pobj->cell.flags & ANIM_FLAG_ACTIVE) )
		return;

	if (pobj->movement == 0)
		return;

	if( !(pobj->cell.pSprite) )
		return;

	if (pobj->category == GATE)	{
		gate = TRUE;
		eArmy = OBJECT_OWNER(pobj);
	}

	if (pobj->cell.pSprite->pMask)
		ObjectMaskOverlap(&pobj->cell, &overlap);
	else if (pobj->cell.pSprite->sprite_flags & SP_MASKRECT)
		ObjectRectOverlap(&pobj->cell, &overlap);
	else	{
		ObjectSelfMask(&pobj->cell, &overlap);
	}

	VerifyOverlapBox(&overlap);

//	overlap.box has the effective tile rectangle of object
//	overlap.overlap_list has an array of char booleans showing overlap of that tile
	int x,y;
	int index = 0;

	for (y=overlap.box.top; y<overlap.box.bottom; y++)	{
		int tile = y*the_map.width + overlap.box.left;
		for (x=overlap.box.left; x<overlap.box.right; x++)	{

			// do damage if different from pDamageOverlap
			if( pDamageOverlap )
			{
				int dmgidx;
				int bDoDamage;

				bDoDamage = 0;					// assume no damage
				if( y >= pDamageOverlap->box.top && 
					y <  pDamageOverlap->box.bottom &&
					x >= pDamageOverlap->box.left &&
					x <  pDamageOverlap->box.right )
				{
					dmgidx = ((y - pDamageOverlap->box.top) *		// height * pitch + width
							  (pDamageOverlap->box.right - pDamageOverlap->box.left)) +
							  (x - pDamageOverlap->box.left);
					if( overlap.overlap_list[index] ^ pDamageOverlap->overlap_list[dmgidx] )
						bDoDamage = 1;
				}
				else
				if( overlap.overlap_list[index] )
					bDoDamage = 1;
				if( bDoDamage )
				{
					ITEM *pItemList;
					SPOINT pt;

					pt.x = (x << 4) + 8;
					pt.y = (y << 4) + 8;
					pItemList = GetObjectsIntersectPoint(&pt);
					while( pItemList )
					{
						if( pItemList != (ITEM *)pobj )
						{
							switch(ITEM_TYPE(pItemList))
							{
								case ARMY_SARGE:
								case ARMY_TROOPER:
								case ARMY_VEHICLE:
								case ARMY_HUSK:
									ItemDamage( pItemList, nCrushDamage, DMGTYPE_RUNOVER, &pt, 0 );
									break;
							}
						}
						pItemList = pItemList->next;
					}
				}
			}


			if (overlap.overlap_list[index])	{
				if (gate)
					SetTrafficableOverride(tile,eArmy);

				the_map.movement_layer[tile] += pobj->movement;
				SetWidth1(tile);

				if( pobj->visibility > the_map.vis_layer[tile] )
					the_map.vis_layer[tile] = pobj->visibility;
                // if tile is untrafficable, prove
                // nobody has already been deployed there
//              if (UntrafficableUnit(tile))
//                  UnitsValidateLocations(tile);
				if (pobj->triggers & TEMPORARY_OBJECT)
					the_map.triggers[tile] |= TEMPORARY_OBJECT;
			}
			index++;
			tile++;
		}
	}
}


//  if pOverlap is a valid pointer, it is filled with overlap information
void SubtractObjectFromMovementLayer(OBJECT *pobj, ITEM_OVERLAP *pOverlap )	
{
	ITEM_OVERLAP overlap;

	if( pobj->cell.world_pos.x == 0 && pobj->cell.world_pos.y == 0 )
		return;

	if (pobj->movement == 0)
		return;

	if( !(pobj->cell.pSprite) )
		return;

	if( !pOverlap )
		pOverlap = &overlap;


	if (pobj->cell.pSprite->pMask)
		ObjectMaskOverlap(&pobj->cell, pOverlap);
	else if (pobj->cell.pSprite->sprite_flags & SP_MASKRECT)
		ObjectRectOverlap(&pobj->cell, pOverlap);
	else	{
		ObjectSelfMask(&pobj->cell, pOverlap);
	}

	VerifyOverlapBox(pOverlap);

//	overlap.box has the effective tile rectangle of object
//	overlap.overlap_list has an array of char booleans showing overlap of that tile
	int x,y;
	int index = 0;
	for (y=pOverlap->box.top; y<pOverlap->box.bottom; y++)	{
		int tile = y*the_map.width + pOverlap->box.left;
		for (x=pOverlap->box.left; x<pOverlap->box.right; x++)	{
			if (pOverlap->overlap_list[index])	{
				the_map.movement_layer[tile] -= pobj->movement;
				SetWidth1(tile);
				if( the_map.vis_layer[tile] == pobj->visibility )
					the_map.vis_layer[tile] = 0;
			}
			index++;
			tile++;
		}
	}
}



///========================================================================
//	Function:		GetNextAttribute()
//
//	Description:
//		get the attribute of the next tile to enter given a world position
//		and a facing.
//
//	Input:			pPos			pointer to a world position
//					facing			a direction of proposed travel
//
//	Ouput:			attribute		movement attribute of next tile to enter
//
///========================================================================

char
GetNextAttribute(SPOINT *pPos, SHORT facing)	{
	LONG	x,y;

	x = (pPos->x + (SHORT) (cos_table[facing]*16)) >> 4;
	y = (pPos->y + (SHORT) (sin_table[facing]*16)) >> 4;

	return (the_map.movement_layer[y*the_map.width + x]);
}

typedef struct 
{
	COMMAND_NUMBERS explosiontype;
	int damage;
} rbuttonexplosion;

rbuttonexplosion rbuttonexplosions[]=
{
	{INACTIVATE_COMMAND, 0},
	{EXPLOSION_GUN_PUFF_M_COMMAND,0},
	{EXPLOSION_GUN_SPARK_S_COMMAND,5},	
	{EXPLOSION_GUN_SPARK_M_COMMAND,5},
	{EXPLOSION_GUN_SPARK_L_COMMAND,5},
	{EXPLOSION_SMOKE_S_COMMAND,300},    // the explosion cheat value - really fatal
	{EXPLOSION_SMOKE_M_COMMAND,20},
	{EXPLOSION_SMOKE_L_COMMAND,20},
	{EXPLOSION_COMBUSTION_S_COMMAND,20},
	{EXPLOSION_COMBUSTION_M_COMMAND,20},
	{EXPLOSION_COMBUSTION_L_COMMAND,20},
	{EXPLOSION_DIRT_SMOKE_S_COMMAND,20},
	{EXPLOSION_DIRT_SMOKE_M_COMMAND,20},
	{EXPLOSION_DIRT_SMOKE_L_COMMAND,20},
	{EXPLOSION_FLASH_SMOKE_S_COMMAND,20},
	{EXPLOSION_FLASH_SMOKE_M_COMMAND,20},
	{EXPLOSION_FLASH_SMOKE_L_COMMAND,20},
	{EXPLOSION_FLASH_COMBUSTION_S_COMMAND,20},
	{EXPLOSION_FLASH_COMBUSTION_M_COMMAND,20},
	{EXPLOSION_FLASH_COMBUSTION_L_COMMAND,20},
	{EXPLOSION_FLASH_DIRT_SMOKE_S_COMMAND,20},
	{EXPLOSION_FLASH_DIRT_SMOKE_M_COMMAND,20},
	{EXPLOSION_FLASH_DIRT_SMOKE_L_COMMAND,20},
	{EXPLOSION_WATER_S_COMMAND,20},
	{EXPLOSION_WATER_M_COMMAND,20},
	{EXPLOSION_WATER_L_COMMAND,20},
	{EXPLOSION_WATER_GUN_PUFF_S_COMMAND,0},
	{EXPLOSION_WATER_GUN_PUFF_M_COMMAND,0},
	{EXPLOSION_WATER_GUN_PUFF_L_COMMAND,0}
};

int currbuttonexplosion=0;
BOOL explosions = FALSE;

void BlowItem(ITEM* pItem)
{
    if (pItem->position.x == 0) return; // not on the map
    DoExplosion(pItem->position.x,pItem->position.y,
                EXPLOSION_SMOKE_M_COMMAND,
                NULL,
                DMGTYPE_OTHER_EXPLOSION,
                0,
                NULL,
                FALSE,
				0,
				SND_NULL_SND_ID);
}

void ChangeRButtonAction(void)
{
	currbuttonexplosion=(currbuttonexplosion+1)%(sizeof(rbuttonexplosions)/sizeof(rbuttonexplosion));
}

int	AlexRButtonDn( UINT nFlags, CPoint point )
{
	if (!explosions)
		return 0;

	// see if mouse click was in playfield
	if ( point.y < 384 )
	{
		SPOINT spt;

		spt.x = (SHORT)point.x + (SHORT)the_map.PixelBox.x;
		spt.y = (SHORT)point.y + (SHORT)the_map.PixelBox.y;

		if (rbuttonexplosions[currbuttonexplosion].explosiontype!=INACTIVATE_COMMAND)
			DoExplosion(spt.x, spt.y, rbuttonexplosions[currbuttonexplosion].explosiontype, 
				NULL, DMGTYPE_OTHER_EXPLOSION, rbuttonexplosions[currbuttonexplosion].damage, NULL, TRUE,
				Armies[ARMY_PLAYER].Legion.Sarge.common.nUniqueID, SND_NULL_SND_ID );
        return 1;
	}
    return 0;
}

BOOL	ObjInList( ANIMCELL* pAnimObject, ANIMCELL *plist[], int numobjects )
{
	int			nObjCount;
	BOOL		bInList = FALSE;		// assume not in the list

	nObjCount = 0;
	while( !bInList && (nObjCount<numobjects) )
	{
		if ( pAnimObject == plist[nObjCount] )
			bInList = TRUE;
		else
			++nObjCount;
	}
	return( bInList );
}



BOOL
ObjectMaskIntersectTile(ANIMCELL *pAnimObject, SPOINT *pt)	{
	RECT oRect;
	BOOL gotit = FALSE;

	if( pAnimObject->pSprite->pMask )
	{
		oRect.left = pAnimObject->world_pos.x - pAnimObject->pSprite->hotspot.x;
		oRect.right = oRect.left + pAnimObject->pSprite->srect.right;
		oRect.top = pAnimObject->world_pos.y - pAnimObject->pSprite->hotspot.y;
		oRect.bottom = oRect.top +  pAnimObject->pSprite->srect.bottom;
		if( gotit = InRect( &oRect, pt ) )
			gotit = ObjectMask( pAnimObject );
	}
	else
	if( pAnimObject->pSprite->sprite_flags & SP_MASKRECT )	
	{
		gotit = InObjectRect(pAnimObject, pt);
	}
	else	
	{
		oRect.left = pAnimObject->world_pos.x - pAnimObject->pSprite->hotspot.x;
		oRect.right = oRect.left + pAnimObject->pSprite->srect.right;
		oRect.top = pAnimObject->world_pos.y - pAnimObject->pSprite->hotspot.y;
		oRect.bottom = oRect.top +  pAnimObject->pSprite->srect.bottom;
		gotit = InRect( &oRect, pt );
	}

	return gotit;
}

/*
BOOL
ObjectIntersectTile(ANIMCELL *pAnimObject, SPOINT *pt)	{
	ITEM_OVERLAP overlap;
	RECT oRect;
	RECT ptRect;
	BOOL gotit = FALSE;

	ptRect.left = pt->x & ~0xF;
	ptRect.top = pt->y & ~0xF;
	ptRect.right = ptRect.left + 16;
	ptRect.bottom = ptRect.top + 16;

	oRect.left = pAnimObject->world_pos.x - pAnimObject->pSprite->hotspot.x;
	oRect.right = oRect.left + pAnimObject->pSprite->srect.right;
	oRect.top = pAnimObject->world_pos.y - pAnimObject->pSprite->hotspot.y;
	oRect.bottom = oRect.top +  pAnimObject->pSprite->srect.bottom;

	if (RectIntersect(&oRect, &ptRect, NULL))	{
		gotit = ObjectSelfMask(pAnimObject, &overlap);
	}

	return gotit;
}
*/

int
ObjectIntersect(ANIMCELL *pAnimObject, EXPLOSIONQUERY *pQuery)	{
	RECT oRect;
	RECT ptRect;
	ITEM_OVERLAP overlap;
	int	max_damage = 0;

	ptRect.left = pQuery->box.left << 4;
	ptRect.top = pQuery->box.top << 4;
	ptRect.right = pQuery->box.right << 4;
	ptRect.bottom = pQuery->box.bottom << 4;

	oRect.left = pAnimObject->world_pos.x - pAnimObject->pSprite->hotspot.x;
	oRect.right = oRect.left + pAnimObject->pSprite->srect.right;
	oRect.top = pAnimObject->world_pos.y - pAnimObject->pSprite->hotspot.y;
	oRect.bottom = oRect.top +  pAnimObject->pSprite->srect.bottom;

	if (RectIntersect(&oRect, &ptRect, NULL))	{
		if (pAnimObject->pSprite->pMask)
			ObjectMaskOverlap(pAnimObject, &overlap);
		else if (pAnimObject->pSprite->sprite_flags & SP_MASKRECT)
			ObjectRectOverlap(pAnimObject, &overlap);
		else	{
//			ObjectSelfRect(pAnimObject, &overlap);
			ObjectSelfMask(pAnimObject, &overlap);
		}

		VerifyOverlapBox(&overlap);

//		overlap.box has the effective tile rectangle of object
//		overlap.overlap_list has an array of char booleans showing overlap of that tile
//		pQuery->box has the tile rectangle of explosion
//		pQuery->damageamounts has the damage for each tile

		RECT damaged;
		int x,y;

		if (RectIntersect(&overlap.box, &pQuery->box, &damaged))	{
			int offset = (damaged.top - pQuery->box.top) * (pQuery->box.right - pQuery->box.left);
			for (y=damaged.top; y<damaged.bottom; y++)	{
				for (x=pQuery->box.left; x<pQuery->box.right; x++)	{
					if (x>=damaged.left)	{
						if (x<damaged.right)	{
							int damage = pQuery->damageamounts[offset];
							if (damage)	{
								int over_offset = ((y - overlap.box.top) * (overlap.box.right - overlap.box.left)) + (x - overlap.box.left);
								if (overlap.overlap_list[over_offset])	{
									if (damage >= max_damage)
										max_damage = damage;
								}
							}
						}
					}
					offset++;
				}
			}
		}
	}

	return max_damage;
}


void GetExplosionObjects(EXPLOSIONQUERY *pQuery, EXPLOSIONRESULT *pResult)	
{
	/*  <<<=======================
	int number = 0;
	SPOINT pt;
	int		nNumQuads;
	int		damage[40];
	ANIMCELL *objs[40];
	int		numobjects = 0;

	pResult->numobjects = 0;
	pResult->objects = NULL;

	pt.x = (SHORT) pQuery->box.left << 4;
	pt.y = (SHORT) pQuery->box.top << 4;

	// find out which quadrant we're gonna be searching from.
	int nQuadrant = DispGetQuad( &pt );
	if ( nQuadrant != -1 )
	{
		// go find all the quads in this area

		nNumQuads = DispFindQuads( nQuadrant, DISPquadIndecies, 3, 3 );

		DISPLINK*	pDispObject;
		DISPLINK*	pQuadrant;

		int			nQuadIndex;
		ANIMCELL*	pAnimObject;

		// now for each quadrant in the list, find all the objects 
		int nQuad     = 0;
		while( nQuad<nNumQuads )
		{
			// get the quad index
			nQuadIndex = DISPquadIndecies[ nQuad ];
			if ( nQuadIndex >= 0 )
			{
				// get the quadrant list
				pQuadrant = DISPquadMap+nQuadIndex;

				// note that the very first DISPLINK in this quadrant is the header
				// it either points to a list of objects in the quadrant or is null
				pDispObject   = (DISPLINK*)(pQuadrant->pNext);
				while ( pDispObject )
				{
					pAnimObject = pDispObject->pAnimObject;
					
					// make sure this DISP object is ACTIVE
					if ( pAnimObject )	
					{
						if ( pAnimObject->flags & ANIM_FLAG_ACTIVE )
						{
							ITEM *pItem = (ITEM*)pAnimObject->pOwner;
							if (pItem)	{
								// see if this object is already in the list
								if ( !ObjInList( pAnimObject, objs, numobjects) )	{
									int dmg;
									if (dmg = ObjectIntersect(pAnimObject, pQuery))	{
										objs[numobjects] = pAnimObject;
										damage[numobjects] = dmg;
										numobjects++;
									}
								}
							}
						}
					}

					// get the next DISP object in this quadrant
					pDispObject = (DISPLINK*)(pDispObject->pNext);
				}
			}

			// try the next quadrant
			++nQuad;
		}
	}
*/
	int		damage[40];
	ANIMCELL *objs[40];
	int		numobjects = 0;

	pResult->objects = (EXPLODEDOBJECT *)malloc(numobjects*sizeof(EXPLODEDOBJECT));

	int nObjCount = 0;
	while( nObjCount < numobjects )
	{
		pResult->objects[nObjCount].pItem = (ITEM *)(objs[nObjCount]->pOwner);
		pResult->objects[nObjCount].maxdamage = damage[nObjCount];
		++nObjCount;
	}
	pResult->numobjects = numobjects;
}


///========================================================================
//	Function:		UpdateAnimatedObjects()
//
//	Description:
//		for each of the animated objects in the world (not to be confused 
//		with ANIM structs), updates it to use the next frame
//
//	Input:			none
//
//	Ouput:			none
//
///========================================================================
void UpdateAnimatedObjects(void)
{
	int i;
	OBJECT_SPRITE *curObjectSprite;
	ANIMATED_OBJECT *curAnimatedObject;

	if( _LOAD_FROM_DATAFILE )
		return;

	for (i=0;i<the_map.num_animated_objects;i++)
	{
		curAnimatedObject=&the_map.animatedobjects[i];
		curObjectSprite=&the_map.obj_sprite_array_list[curAnimatedObject->pObj->category][curAnimatedObject->pObj->index];
		if (curAnimatedObject->pObj->damageindex==0)
		{
			if (curAnimatedObject->curcounter>=curObjectSprite->nAnimDelay)
			{
				curAnimatedObject->curcounter=0;
				curAnimatedObject->curframe=(curAnimatedObject->curframe+1)%curObjectSprite->nAnimFrames;
				if (curAnimatedObject->curframe==0)
					curAnimatedObject->pObj->cell.pSprite=&curObjectSprite->sprites[0];
				else
					curAnimatedObject->pObj->cell.pSprite=&curObjectSprite->sprites[curAnimatedObject->curframe+curObjectSprite->nLevelsOfDamage-1];
				MoveDispXObject( &(curAnimatedObject->pObj->cell), TRUE );
				//if there are levels of damage, then they come before the animated frames, so that
				//if there are 3 levels of damage and 3 animated frames, then sprites 0, 1, 2 are the
				//three damaged sprites, and 0, 3, 4 are the 3 animating frames
			}
			else
				curAnimatedObject->curcounter += (short)gpGame->dwDeltaTime;
		}
	}
}




char *GetMissionText(int mission)
{
	char *oldmissiontext;
	unsigned long checksum;

	oldmissiontext=the_map.missiontext;
	checksum = LoadMissionText(mission);
	if (oldmissiontext!=the_map.missiontext)
		free(oldmissiontext);

	// TBD: set script checksum in the_map

	return the_map.missiontext;
}

char *GetObjectText(int mission)
{
	char *oldobjtext;

	oldobjtext=the_map.objtext;
	LoadObjectText(mission);
	if (oldobjtext!=the_map.objtext)
		free(oldobjtext);

	return the_map.objtext;
}


///========================================================================
//	Function:		ProcessPadLayer
//	Description:	scan map for pads, note location of each one
//					We note a tile of the pad, no matter how big it is
//					Turns out we note the tile of lowest index.    
//					But we prefer trafficable tiles to untrafficable
///========================================================================

void ProcessPadLayer()
{
    IPOINT index;
    int padn;
    int pad;
    int bitnum;

    // first clear the pad location notes
    for (pad = 0; pad < MAX_PADS; ++pad)
    {
        padLocations[pad].x = 0;
        padLocations[pad].y = 0;
    }

	if (the_map.bit_pads_layer)
	{
        IPOINT priorTile;
		// now find where pads are and note a position for each
		WALKGRID(index)
		{
			padn = the_map.bit_pads_layer[index];
			if (padn != 0)	{
				// process pad bits to see which exist here
				for (bitnum = 0; bitnum <= 7; ++bitnum)
				{
					if (padn & (1 << bitnum))
					{
						priorTile = ENCODE_IPOINT(padLocations[bitnum].x,
                                                  padLocations[bitnum].y);
                        // if we already had a great tile, keep it.
                        if (!UntrafficableUnit(priorTile)) continue;

						padLocations[bitnum].x = IPOINT_X(index) << 4; // pixel offset, not tile offset
						padLocations[bitnum].y = IPOINT_Y(index) << 4; // pixel offset, not tile offset
					}
				}
			}
		}
	}

	if (the_map.numeric_pads_layer)
	{
        IPOINT priorTile;
		// now find where pads are and note a position for each
		WALKGRID(index)
		{
			padn = the_map.numeric_pads_layer[index];
			if (padn >= 8)	{
                priorTile = ENCODE_IPOINT(padLocations[padn].x,
                                          padLocations[padn].y);
                // if we already had a great tile, keep it.
                if (!UntrafficableUnit(priorTile)) continue;

				padLocations[padn].x = IPOINT_X(index) << 4; // pixel offset, not tile offset
				padLocations[padn].y = IPOINT_Y(index) << 4; // pixel offset, not tile offset
			}
			else
				ASSERT(padn == 0);
		}
	}


	// show where detected pads are
#ifdef COMMENTED_OUT	//_DEBUG
	for (pad = 0; pad < MAX_PADS; ++pad)
    {
       IPOINT priorTile;
       if (padLocations[pad].x != 0)
       {
           priorTile = ENCODE_IPOINT(padLocations[pad].x,
                                     padLocations[pad].y);
           if (UntrafficableUnit(priorTile))
               TRACE("WARNING- untrafficable pad");
           TRACE("    found pad %d at %d.%d\n",pad,
                    padLocations[pad].x, padLocations[pad].y);
       }
	}
#endif

}

///========================================================================
//	Function:		MapPadPosition
//	Description:	return pad location for designated pad into point
//					returns 0 if pad found. -1 if failed.    
///========================================================================

int	MapPadPosition(int pad,SPOINT* point)
{
    point->x = padLocations[pad].x;
    point->y = padLocations[pad].y;
    if (point->x != 0) return 0;

    TRACE("Warning- failed to find pad %d\n",pad);
    return -1;
}



void ClipNum(short *numtoclip, int min, int max)
{
	if (*numtoclip<min) 
		*numtoclip=min;

	if (*numtoclip>max)
		*numtoclip=max;
}

/*	This function first clips RequestedCenterPosition so it's a valid value, then
 *  sets the various other map rectangles and boxes to reflect it.
 *
 *
 *
 */

void ProcessMapPosition(void)
{
	int newx, newy;


	//set the pixel box
	the_map.PixelBox.x=the_map.RequestedCenterPoint.x-the_map.PixelBox.cx/2;
	the_map.PixelBox.y=the_map.RequestedCenterPoint.y-the_map.PixelBox.cy/2;

	//set the tile box, and tell the map to redraw if necessary
	newy = the_map.PixelBox.y >> 4;
	if (the_map.TileBox.y != newy)	
	{
		the_map.redraw = REDRAW_PARTIAL;
		the_map.TileBox.y = newy;
	}
	newx = the_map.PixelBox.x >> 4;
	if (the_map.TileBox.x != newx)	
	{
		the_map.redraw = REDRAW_PARTIAL;
		the_map.TileBox.x = newx;
	}

 	the_map.screenrect.left = the_map.PixelBox.x;
	the_map.screenrect.top = the_map.PixelBox.y;
	the_map.screenrect.right = the_map.screenrect.left + the_map.PixelBox.cx;
	the_map.screenrect.bottom = the_map.screenrect.top + the_map.PixelBox.cy;

	the_map.CurCenterPoint=the_map.RequestedCenterPoint;

	DisplayBox=the_map.PixelBox;
}


SBOX GetMapPosition(void)	{
	return the_map.PixelBox;
}

inline long FastDistance( SPOINT &a, SPOINT &b )
{
	int xdif, ydif;
	
    xdif = a.x - b.x;
	ydif = a.y - b.y;
	if( xdif < 0 )
		xdif = -xdif;
	if( ydif < 0 )
		ydif = -ydif;
	if( xdif > ydif )
		return( xdif + ydif - (ydif >> 1) );
	else
		return( xdif + ydif - (xdif >> 1) );
}


struct TQuakeVectors
{
	int time;
	int velx;
	int vely;
	int damping;
};

#define MAX_QUAKE_INTENSITY  10

TQuakeVectors QuakeVectors[MAX_QUAKE_INTENSITY+1] =
{
	{   0,   0,  0,  0},
	{ 250,  50,  25, 2},				// 1
	{ 500,  32,  70, 2},				// 2
	{ 750,  90,  39, 2},				// 3
	{1000,  45, 110, 3},				// 4
	{1250, 130,  52, 3},				// 5
	{1500,  59, 150, 3},				// 6
	{1750, 170,  66, 4},				// 7
	{2000,  73, 190, 4},				// 8
	{2250, 210,  80, 5},				// 9
	{2500,  87, 230, 5}					// 10
};

void SetupQuake( SPOINT &wpos, int intensity )
{
	int    distance;
	SPOINT scr_pos;
	float  factor;
	
	if( intensity > MAX_QUAKE_INTENSITY )
		intensity = MAX_QUAKE_INTENSITY;
	scr_pos.x = the_map.screenrect.left + ( the_map.PixelBox.cx >> 1 );
	scr_pos.y = the_map.screenrect.top + ( the_map.PixelBox.cy >> 1 );
	distance = FastDistance( wpos, scr_pos );
	if( distance >= 832 )
		return;
	factor = 1.0;
	if( distance > 320 )
		factor = (float)(factor * ((832-distance) / 512.0)); 
	intensity = (int)(intensity * factor);
	if( intensity < 1 )
		return;
	StartQuaking( QuakeVectors[intensity].time,
				  QuakeVectors[intensity].velx,
				  QuakeVectors[intensity].vely,
				  QuakeVectors[intensity].damping );
}


void StartQuaking( int time, int vel_x, int vel_y, int max_offs )
{
	the_map.quake_offsx = 0;
	the_map.quake_offsy = 0;
	if( time > the_map.quake_time )
		the_map.quake_time = time;
	if( abs(vel_x) > abs(the_map.quake_velx) )
		the_map.quake_velx = vel_x;
	if( abs(vel_y) > abs(the_map.quake_vely) )
		the_map.quake_vely = vel_y;
	if( max_offs > the_map.quake_maxoffs )
		the_map.quake_maxoffs = max_offs;
};


void DoTheQuake( void )
{
	int		dwDeltaTime;
	int		damping;

	dwDeltaTime = gpGame->dwDeltaTime;
	the_map.quake_time -= dwDeltaTime;
	if( the_map.quake_time <= 0 )
	{
		the_map.quake_time = 0;
		the_map.quake_velx = 0;
		the_map.quake_vely = 0;
		the_map.quake_maxoffs = 0;
		the_map.quake_offsx = 0;
		the_map.quake_offsy = 0;
		return;
	}

	if( the_map.quake_time > 1024 )
		damping = the_map.quake_maxoffs;
	else
		damping = (the_map.quake_time * the_map.quake_maxoffs) >> 10;

	the_map.quake_offsx += (float)((the_map.quake_velx * dwDeltaTime)/1000.0);
	if( the_map.quake_offsx > damping )
	{
		the_map.quake_offsx = (float)damping;
		the_map.quake_velx = -the_map.quake_velx;
	}
	else
	if( the_map.quake_offsx < -damping )
	{
		the_map.quake_offsx = -(float)damping;
		the_map.quake_velx = -the_map.quake_velx;
	}
	the_map.screenrect.left += (long)the_map.quake_offsx;
	the_map.screenrect.right += (long)the_map.quake_offsx;

	the_map.quake_offsy += (float)((the_map.quake_vely * dwDeltaTime)/1000.0);
	if( the_map.quake_offsy > damping )
	{
		the_map.quake_offsy = (float)damping;
		the_map.quake_vely = -the_map.quake_vely;
	}
	else
	if( the_map.quake_offsy < -damping )
	{
		the_map.quake_offsy = -(float)damping;
		the_map.quake_vely = -the_map.quake_vely;
	}
	the_map.screenrect.top += (long)the_map.quake_offsy;
	the_map.screenrect.bottom += (long)the_map.quake_offsy;
}	//	DoTheQuake



//This function clears out any scrolling that has been done so far this frame
void MapUndoScrolling(void)
{
	the_map.RequestedCenterPoint=the_map.CurCenterPoint;
}

// scroll speeds
// #define MAX_SCROLL_SPEED_SQ 324
// #define MAX_SCROLL_SPEED 18
#define MAX_SCROLL_SPEED_SQ 1024
#define MAX_SCROLL_SPEED 32

void ClipScrollVec(short *x, short *y)
{
	int veclength_sq;
	double veclength;

	veclength_sq=(*x)*(*x)+(*y)*(*y);


	if (veclength_sq > MAX_SCROLL_SPEED_SQ)
	{
		veclength=sqrt((float)veclength_sq);
		*x= (short)((*x*MAX_SCROLL_SPEED)/veclength);
		*y= (short)((*y*MAX_SCROLL_SPEED)/veclength);
	}
}


void NewScrollMap(short x, short y)
{
	ClipScrollVec(&x, &y);
	the_map.RequestedCenterPoint.x += x;
	the_map.RequestedCenterPoint.y += y;

	//clip the requested center point
	int  screenradius;

	ASSERT( the_map.RequestedCenterPoint.x != 0 );

	if( Allah == 2 )
	{
		RECT rect;

		rect.left = 16;
		rect.top = 16;
		rect.right = the_map.FullPixelRect.right - 16;
		rect.bottom = the_map.FullPixelRect.bottom - 16;
		screenradius = the_map.PixelBox.cx >> 1;
			ClipNum( &the_map.RequestedCenterPoint.x, 
				rect.left + screenradius, 
				rect.right - screenradius - 1 );

		screenradius = the_map.PixelBox.cy >> 1;
			ClipNum( &the_map.RequestedCenterPoint.y, 
				rect.top + screenradius, 
				rect.bottom - screenradius - 1);
	}
	else
	{
		screenradius = the_map.PixelBox.cx >> 1;
			ClipNum( &the_map.RequestedCenterPoint.x, 
				the_map.boundrect.left + screenradius, 
				the_map.boundrect.right - screenradius - 1 );

		screenradius = the_map.PixelBox.cy >> 1;
			ClipNum( &the_map.RequestedCenterPoint.y, 
				the_map.boundrect.top + screenradius, 
				the_map.boundrect.bottom - screenradius - 1);
	}
};

//this function scrolls the map, and also returns the distance scrolled
void ScrollMapReturn(short x, short y, short *xscrolled, short *yscrolled)
{
	SPOINT oldrcp;

	oldrcp=the_map.RequestedCenterPoint;

	NewScrollMap(x,y);

	*xscrolled = the_map.RequestedCenterPoint.x - oldrcp.x;
	*yscrolled = the_map.RequestedCenterPoint.y - oldrcp.y;
}


//this function tells the map to scroll approximately 1/10th of the way towards the 
//referenced point, clipped to scrolling speed
void MapLookTowardsPoint(int x, int y)
{
	int dx, dy;

	dx=x-the_map.CurCenterPoint.x;
	dy=y-the_map.CurCenterPoint.y;

	if (dx<0)
		dx=(dx-8)/10;
	else if (dx>0)
		dx=(dx+8)/10;

	if (dy<0)
		dy=(dy-8)/10;
	else if (dy>0)
		dy=(dy+8)/10;

	NewScrollMap(dx, dy);
}



//this function tells the map that it should look at a particular point. the map will then
//scroll to that point as fast as possible
void MapLookAtPoint(int x, int y)
{
	NewScrollMap(x-the_map.CurCenterPoint.x, y-the_map.CurCenterPoint.y);
}


//this function tells the map to jump and look at a particular point
void MapJumpToPoint(int x, int y)
{
	the_map.RequestedCenterPoint.x=x;
	the_map.RequestedCenterPoint.y=y;

	int  screenradius;

	ASSERT( the_map.RequestedCenterPoint.x != 0 );

	screenradius = the_map.PixelBox.cx >> 1;
	ClipNum( &the_map.RequestedCenterPoint.x, 
			 the_map.boundrect.left + screenradius, 
			 the_map.boundrect.right - screenradius - 1 );
	screenradius = the_map.PixelBox.cy >> 1;
	ClipNum( &the_map.RequestedCenterPoint.y, 
			 the_map.boundrect.top + screenradius, 
			 the_map.boundrect.bottom - screenradius - 1);
}


//this function tells the map to put itself in the proper place if its tracking a particular anim
#define LOOKAHEAD_X 90.0
#define LOOKAHEAD_Y 40.0

SPOINT CalculateLookAhead( SPOINT &spt, BOOL Reverse, int facing, int minimum )
{
	int		direction;
	int		dx, dy;
	double	mx, my;
	SPOINT	dpt;

	direction = facing;
	if( Reverse )
		direction = NormalizeFacing( direction + 128 );

	mx = cos_table[direction];
	my = sin_table[direction];
	dx = (int)(mx * LOOKAHEAD_X);
	dy = (int)(my * LOOKAHEAD_Y);
	dpt.x = spt.x + dx;
	dpt.y = spt.y + dy;
	if( GetDistance( &spt, &dpt ) < minimum )
	{
		dpt.x = (short)(spt.x + mx * minimum);
		dpt.y = (short)(spt.y + my * minimum);
	}
	return dpt;
}


void SetAISargeView(SARGE *pSarge)
{   
	ANIM *curanim;
	SPOINT	destpt;
	int  screenradius;

	if (!pSarge->pAvatar)
		return;

	curanim = pSarge->pAvatar->pAnimation;

	destpt = curanim->world_pos;
	destpt = CalculateLookAhead( destpt, FALSE, curanim->facing, 0 );

	ASSERT( destpt.x != 0 );

	screenradius = the_map.PixelBox.cx >> 1;
	ClipNum( &destpt.x, 
			 the_map.boundrect.left + screenradius, 
			 the_map.boundrect.right - screenradius - 1 );
	screenradius = the_map.PixelBox.cy >> 1;
	ClipNum( &destpt.y, 
			 the_map.boundrect.top + screenradius, 
			 the_map.boundrect.bottom - screenradius - 1);

	// add 2 tiles worth of slop
	pSarge->ViewBox.x = destpt.x - the_map.PixelBox.cx/2 - 32;
	pSarge->ViewBox.y = destpt.y - the_map.PixelBox.cy/2 - 32;
	pSarge->ViewBox.cx = the_map.PixelBox.cx + 64;
	pSarge->ViewBox.cy = the_map.PixelBox.cy + 64;
}


void MapLookAtAnim(ANIM *pAnim, BOOL LookAhead, BOOL Reverse, int MinimumDistance)
{
	SPOINT	destpt;

	destpt = pAnim->world_pos;
	if( LookAhead )
		destpt = CalculateLookAhead( destpt, Reverse, pAnim->facing, MinimumDistance );

	MapLookTowardsPoint( destpt.x, destpt.y );
}


void MapJumpToAnim(ANIM *pAnim, BOOL LookAhead, BOOL Reverse, int MinimumDistance)
{
	SPOINT	destpt;

	destpt = pAnim->world_pos;
	if( LookAhead )
		destpt = CalculateLookAhead( destpt, Reverse, pAnim->facing, MinimumDistance );

	MapJumpToPoint( destpt.x, destpt.y );
}


void MapRemoveObject(OBJECT *pObject)
{
	// if no graphics laoded, this is dangerous
	if (!MapGraphicsLoaded)
		return;

	SubtractObjectFromMovementLayer(pObject);

	pObject->common.position.x=0;
	pObject->common.position.y=0;
	pObject->common.tile = 0;
	pObject->cell.flags &= ~ANIM_FLAG_ACTIVE;
	pObject->triggers |= TRIGGER_CHANGED;
	pObject->triggers |= TRIGGER_UNDEPLOYED;
	if (pObject->sobj)
		SOBJ_Deactivate(pObject->sobj);

	MoveDispXObject( &(pObject->cell), TRUE );
}

void MapPlaceObject(OBJECT *pObject, SPOINT *where)
{
	ItemSetLocation(pObject, where);
	pObject->triggers |= TRIGGER_CHANGED;
	pObject->triggers &= ~TRIGGER_UNDEPLOYED;
	pObject->cell.flags|=ANIM_FLAG_ACTIVE;
	pObject->cell.world_pos=*where;

	MoveDispXObject( &(pObject->cell), TRUE);

	AddObjectToMovementLayer(pObject);
}


///========================================================================
//	Function:		ObjectHitByMissile
//	Description:	will this object stop a missile and take damage from it?
///========================================================================
BOOL ObjectHitByMissile(OBJECT* pObject, SHORT height)
{
	int	eType = ITEM_CLASS(pObject);

	switch(eType)	{
		case BUSH:
//		case BRIDGE:
		case SPECIAL_ITEMS:
			return FALSE;
			break;
		case EXPLOSIVES:
			if( pObject->number == ARMY_MINE )
				return FALSE;
		default:
			if (height <= GetItemHeight((ITEM *)pObject) )
			{
				if( pObject->permeability > 0 )
				{
					if( gpGame->GameType == GAMETYPE_ONEPLAYER )
					{
						if( (rand() & 0xff) <= pObject->permeability )
							return FALSE;
					}
					else
						if( pObject->permeability > 250 )
							return FALSE;
				}
				return TRUE;
			}
			break;
	}

	return FALSE;
}
///========================================================================
//	Function:		ValidateMap
//	Description:	Prove map is reasonable
///========================================================================

void ValidateMap()
{
	ASSERT(the_map.width == map_width);
	ASSERT(the_map.height == map_height);
	ASSERT((the_map.terrain_name[0] >= 'a' && the_map.terrain_name[0] <= 'z')	||
			(the_map.terrain_name[0] >= 'A' && the_map.terrain_name[0] <= 'Z'));
}


//  is a point (w.c.) in the bounds rect for the map?
int  InBoundsRect( SPOINT &pt )
{
	return( InRect( &(the_map.boundrect), &pt ) );
}


//	remove any owned items that are not being used
void RemoveUnusedItemsOfArmy(int myArmy ) // local army color
{
	OBJECT *pObject;

	for( int i = 0; i < the_map.num_objects; i++ )
	{
		pObject = &(the_map.objects[i]);
        // assets are removed by a different process
        if (pObject->attribute == ARMY_ASSET) continue; 

        int eArmy = (ARMY_COLOR)OBJECT_OWNER(pObject);
        if (eArmy != myArmy) continue;

        if( pObject->cell.flags | ANIM_FLAG_ACTIVE )
        {
            MapRemoveObject( pObject );
            pObject->triggers |= TRIGGER_UNDEPLOYED;
            pObject->triggers |= TRIGGER_DESTROYED;
		}
	}
}

void RemoveUnusedItems( void )
{
    int eArmy;
    FOR_EACH_ARMY(eArmy)
    {
        if (Armies[eArmy].Status != 0) continue; // army is active
            
        RemoveUnusedItemsOfArmy(eArmy); 
    }
}

void SetScriptName(char *name, int number)
{
	if (!script_names[number])
		script_names[number] = (char *) malloc(SCRIPT_NAME_SIZE);

	if (script_names[number])
		strcpy(script_names[number], name);

	num_script_names = number+1;
}

void CopyScriptNames()
{
	int i;

	for (i=0; i<SCRIPT_NAMES; i++)
		the_map.script_names[i] = script_names[i];

	the_map.num_script_names = num_script_names;
}

void ReleaseScriptNames()
{
	int i;

	for (i=0; i<SCRIPT_NAMES; i++)
	{
		if (script_names[i])
			free(script_names[i]);
		script_names[i] = NULL;
	}
	num_script_names = 0;
}

DWORD FileXSum(char *name) {
	DWORD xsum = 0;
	DWORD data;
	FILE* pFile = NULL;
	TRACE( "Checksum of %s ",name); 
	if ( (pFile = (FILE*)fopen( name, "rb" )) != NULL )	{
		while( fread(&data, sizeof(DWORD), 1 ,pFile) )
			xsum ^= data;
	}
	if ( pFile )
		fclose( pFile );
	TRACE( "is %x \n",xsum); 
	return(xsum);
}


DWORD ScriptFileXSum(char *name) {
	char filename[256];
	strcpy(filename,name);
	strcat(filename,"_1.txt");
	return FileXSum(filename );
}




