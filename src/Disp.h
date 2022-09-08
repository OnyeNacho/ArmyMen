/*
	DispX.h
	New Display driver header file.
*/

#ifndef __DISPX_H__

#define __DISPX_H__

#include "ai.h"


typedef struct TDispNode*	PDispNode;
typedef struct AnimCell*	PAnim;
typedef struct ITEM*		PItem;
typedef struct Sprite*		PSprite;


extern int UseRectIntersect;


struct TDispNode
{
	PAnim	pAnim;
	PDispNode
			prev, next;
};


struct TDispFoot
{
	TDispNode dnode;
	int		  index;
};


typedef struct TObjectLayer*	PObjectLayer;
struct TObjectLayer
{	
	int			width, height;
	int			cellsize, bitwidth;
	PDispNode	*cells;
};


int	 CvtBits( int x );
BOOL AnimInWorld( PAnim pAnim, int x, int y );

void DisplayMapX( void );
void InitObjectLayer( PObjectLayer layer, int width, int height, int cellsize );
void FreeObjectLayer( PObjectLayer layer );
int  CreateDispXObject( int width, int height, PAnim pAnim, EObjectLayer layer );
void MoveDispXObject( PAnim pAnim, BOOL ForceUpdate );
void DestroyDispXObject( PAnim pAnim );
void ChangeAnimSprite( PAnim pAnim, EObjectLayer newlayer, PSprite pNewSprite );

PItem GetObjectsIntersectPoint( SPOINT *pPos );
PItem GetObjectsMaskPoint( SPOINT *pPos );

PItem GetObjectsIntersectPointInLayer( SPOINT *pPos, TObjectLayer &Layer, PItem pcurItemList );
ITEM * GetExplosionInfluence( RECT &queryRect);


#endif
