#include "avatar.h"


#define MAX_GROUND_OBJECTS		500
#define GROUND_OBJECTS_BUFFER	50

#define MAX_CORPSE_OBJECTS      100
#define CORPSE_OBJECTS_BUFFER   10

#define MAX_WORLD_OBJECTS		200
#define WORLD_OBJECTS_BUFFER	40

#define MAX_FLASH_OBJECTS       100
#define FLASH_OBJECTS_BUFFER    25


#define CAT_FLAMEBURST	400
//#define CAT_FOGTILES	401
#define CAT_FRAGCOUNTER	402
#define CAT_MUZZLEFLASH	403
#define CAT_SCAR		407
#define CAT_SMOKE		408
#define CAT_STRIPES		409
#define CAT_BODYPARTS	410
#define CAT_AIRSUPPORT	411
#define CAT_PARACHUTE	412
#define CAT_FIRE		413
#define CAT_FLAG		414


enum EFlashTypes
{
	EFT_RifleFlash = 0,
	EFT_TankFlash = 1,
	EFT_JeepFlash = 2,
	EFT_HalfFlash = 3,

	EFT_LastFlash
};

enum EWorldObjectType
{
	WOT_BodyPart,
	WOT_VehiclePart,
	WOT_MuzzleFlash,
	WOT_FlameBurst,
	WOT_Smoke,
	WOT_Plume,
	WOT_Flicker,
	WOT_Flame,

	WOT_LastType
};


enum EBodyParts
{
	EBP_LeftArm,
	EBP_RightArm,
	EBP_Chest,
	EBP_Head,
	EBP_LeftLeg,
	EBP_RightLeg,
	EBP_Torso,
	EBP_Part1,
	EBP_Part2,
	EBP_Part3,

	EBP_LastPart
};


enum EVehicleParts
{
	EVP_hded,		// main corpse
	EVP_jded,
	EVP_tded,

	EVP_aaaa,		// misc. parts
	EVP_bbbb,
	EVP_cccc,
	EVP_dddd,
	EVP_eeee,
	EVP_ffff,
	EVP_jeep,
	EVP_part1,
	EVP_part2,
	EVP_part3,

	EVP_LastPart
};


struct TBodyPartsData
{
	char		filename[5];
	int			number;
	int			num_frames;
	PSPRITE		*sprites;
	int			x, y, z;
};


struct TMuzzleFlashData
{
	char        filename[5];
	int			number;
	int			num_directions;
	PSPRITE     *sprites;
	int			playspeed;
};


#define  MAX_FLAME_BURST_NFRAMES  20

struct TFlameBurstData
{
	char		filename[5];
	int			num_dirs;
	int			num_frames;
	PSPRITE     *sprites;
	int			init_velocity;
	int         timing[MAX_FLAME_BURST_NFRAMES];
	int         velocity[MAX_FLAME_BURST_NFRAMES];
	int			persistence[MAX_FLAME_BURST_NFRAMES];
	int			minframe[MAX_FLAME_BURST_NFRAMES];
};


struct TFireData
{
	char		filename[5];
	int			num_types;
	int			num_frames;
	int			num_dieoff;
	DWORD		timing;
	PSPRITE		*sprites;
};


struct TParatrooperData
{
	char		filename[5];
	int			num_frames;
	SPRITE		**sprites;
};


#define NUM_SCAR_SPRITES	3


//	Ground Objects are stationary objects in the ground layer
typedef struct TGroundObject * PGroundObject;

struct TGroundObject
{
	ANIMCELL	*pAnim;
	short		index;
	short		prev, next;
};


struct TGroundObjectsArray
{
	int			count, tail;
	TGroundObject  objects[MAX_GROUND_OBJECTS];
};



//	Corpse Objects are stationary objects in the ground layer w/ additional info
typedef struct TCorpseObject * PCorpseObject;

struct TCorpseObject
{
	ANIMCELL	*pAnim;
	short		index;
	short		prev, next;
};


struct TCorpseObjectsArray
{
	int			count, tail;
	TCorpseObject  objects[MAX_CORPSE_OBJECTS];
};



//	World Objects are moving objects that go in the Ordered Layer
typedef struct TWorldObject * PWorldObject;

struct TWorldObject
{
	EWorldObjectType	wo_type;
	union USubObjectType
	{
		BYTE		index;
		EBodyParts	part;
		EVehicleParts vpart;
	} sub_type;
	int			frame;
	DWORD		dwAnimTime;
	DWORD		speed;
	int			x_velocity, y_velocity, z_velocity;
	ANIMCELL	*pAnim;
	ANIMCELL	*pShadow;
	UID			uidAnchor;
	short		index;
	short		prev, next;
};


struct TWorldObjectsArray
{
	int			count, tail;
	int			max, buffer;
	PWorldObject  objects;
};


extern TFlameBurstData FlameBurstData;
extern TParatrooperData ParatrooperData[];

void DrawFragCounters( void );

void LoadWorldObjectGraphics( void );
void FreeWorldObjectGraphics( void );

void GenerateExplodingAvatar( AVATAR * pAvatar );
void MakeChips( SPOINT &pt, BYTE *trans_table, int facing );
void ShotDeathStandParts( SPOINT &pt, int facing, BYTE * trans_table );
void MakeMuzzleFlash( int x, int y, int facing, int type, UID uidAnchor );
void InsertAnimInGroundLayer( ANIM *pAnim );
void InsertAnimInCorpseLayer( ANIM *pAnim );
void DropFlamePoop( int x, int y, int dir, int frame );
void GenerateFlashBurn( int x, int y, int burn_index );
void DropSmokePuff( SPOINT &pt, int z );
void GenerateExplodingVehicle( int type, SPOINT &pos, BYTE *trans_table, int facing );
void GenerateDeadVehicleParts( int type, SPOINT &pos, BYTE *trans_table );
void MakeSmokePlume( SPOINT &pt, UID fromUID );
void MakeFlame( SPOINT &pt, UID fromUID, int base, int height );


void InitGroundObjects( void );
void FreeGroundObjects( void );
PGroundObject InsertGroundObject( void );
int  DeleteGroundObject( PGroundObject pgo );
void FreeSomeGroundObjects( void );
#ifdef _DEBUG
void PrintGroundObjectsList( void );
#define _DebugPrintGroundObjects PrintGroundObjectsList()
#else
#define _DebugPrintGroundObjects
#endif
void InitCorpseObjects( void );
void FreeCorpseObjects( void );
PCorpseObject InsertCorpseObject( void );
int  DeleteCorpseObject( PCorpseObject pco );
void FreeSomeCorpseObjects( void );

void InitWorldObjects( TWorldObjectsArray &obj_array, int max_objs, int buffer_size, 
					   int max_xsize, int max_ysize, EObjectLayer elayer );
void FreeWorldObjects( TWorldObjectsArray &obj_array );
PWorldObject InsertWorldObject( TWorldObjectsArray &obj_array );
int  DeleteWorldObject( TWorldObjectsArray &obj_array, PWorldObject pwo );
void FreeSomeWorldObjects( TWorldObjectsArray &obj_array );
void ProcessWorldObjects( TWorldObjectsArray &obj_array );

void LoadParachuteGraphics( void );
void FreeParachuteGraphics( void );


void InitLocalObjects( void );
void FreeLocalObjects( void );
void ProcessLocalObjects( void );
int CountFlames();

void AcquireWobjectSpriteAsShadow( PSPRITE &pSprite, int cat, int num, int idx, char *prefix, BYTE *trans_table );
void ReleaseWobjectSprite( PSPRITE &pSprite );


