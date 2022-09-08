/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Disp.cpp $
//
//	DESCRIPTION:	Display routines
//
//	AUTHOR:			Peter Hu
//
//	REVISION:		$Header: /ArmyMen/src/Disp.cpp 101   4/07/98 12:04a Phu $
//
//	Copyright (C) 1998 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/Disp.cpp $
//  
//  101   4/07/98 12:04a Phu
//  don't assert if something moves offscreen
//  
//  99    4/02/98 2:24p Phu
//  typecast to avoid warnings
//  
//  98    3/31/98 1:07p Bwilcox
//  dispell fog
//  
//  97    3/31/98 12:51p Bwilcox
//  dispell fog
//  
//  96    3/27/98 1:49p Phu
//  survive ALT_TAB dammit
//  
//  95    3/26/98 2:51p Phu
//  Move trace inside updatelist max check dummy
//  
//  94    3/26/98 2:36p Phu
//  don't assert if # of rectangles exceed disp list
//  
//  93    3/25/98 8:42p Phu
//  increase disp list size
//  
//  92    3/23/98 5:02p Phu
//  don't crash if exceed update rects, just redraw full
//  
//  91    3/22/98 6:08p Phu
//  fix parameter mismatch in rectintersect
//  
//  90    3/19/98 11:19p Nrobinso
//  erase back surface if can't draw anything
//  
//  89    3/19/98 1:56p Phu
//  fix to invisible vs. preinvisible test
//  
//  88    3/19/98 12:21p Phu
//  tie breaker in sort
//  
//  87    3/18/98 5:16p Phu
//  add some asserts for the update list
//  
//  86    3/12/98 4:54p Bwilcox
//  added GetObjectsMaskPoint
//  
//  85    3/11/98 10:21p Nrobinso
//  move clipRect; switch to RectIntersect intead of IntersectRect which
//  has the same name as the windows routine
//  
//  84    3/10/98 3:45p Phu
//  note that clipline sometimes returns 0!
//  added assert to getobjects
//  fix flamethrowers go off screen
//  
//  83    3/07/98 11:51p Nrobinso
//  new header; move .h file to stdafx
//  
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

/*
	NOTE: each operation has a separate function for each layer, even if there is no difference
		  between the operations for the layers.  this is for future expansion, in case we wish
		  to handle the layers differently
*/

#include	"stdafx.h"

#include	"MainFrm.h"
#include	"Disp.h"
#include	"fileio.h"
#include	"army.h"
#include	"map.h"
#include	"anim.h"
#include	"sprite.h"
#include	"wobject.h"
#include	"bmptext.h"
#include	"aiaccess.h"

#include    "trooper.h"
#include	"unit.h"
#include	"stratmap.h"
		// !!! adjust these values
#define		MAX_SCREENDISPLIST_SIZE		500				// maximum # of anims in a display list
#define		MAX_UPDATELIST_SIZE			500				// maximum # of rects in an update list


int			DispXObjectCount =			0;				// # of Disp objects created
int			UseRectIntersect = 0;


#ifndef FINAL
	extern	COLORREF	displaydebug;
	extern	RECT		rcGameSurface;
			int			debug_updatelistcount = 0;
			int			debug_displaylistcount = 0;
#endif


	extern	char		hotspots;


struct UpdateListNode									// node of an update list
{
	RECT		rect;									// rectangle
	WORD		prev, next;								// point to prev node & next node
};


struct TUpdateList										// update list
{
	WORD		tail;									// index of last node in list
	UpdateListNode										// array of nodes
				array[MAX_UPDATELIST_SIZE];
};


void DrawViewportSection( RECT &rc );					// Draw game screen in rect (w.c.)
void ScrollViewport( void );							// Update game screen to new screenrect
void DrawOverlayLayer( void );

void DrawDispXLayerRect( RECT &rc, PObjectLayer pLayer );	// Draw dispx layer in rect (w.c.)
void DrawOverlayLayerRect( RECT &rc );					// Draw overlay layer in rect (w.c.)

void DrawAnimInRect( PAnim pAnim, RECT &rc );			// Draw an animcell in rect (w.c.)
void DrawAnimInRectOverlay( PAnim pAnim, RECT &rc );	// Draw an animcell in the overlay layer (w.c.)

void RemoveFromDisplayList( TDispNode &dnode,			// Remove a disp node from a disp list
						    PDispNode *dlist );

void ClearUpdateList( void );							// Clear the update list
void InsertRectInUpdateList( RECT &a );					// Insert a rect into the update list

void UnlockDrawingSurface( void );						// DDUnlock drawing surface
void LockDrawingSurface( void );
void DoneDrawingSurface( void );

void UnlockOverlayLayer( void );
BOOL LockOverlayLayer( void );

void DrawSargeChevron( void );


TUpdateList		UpdateList;								// The update list
TDispNode		displist[MAX_SCREENDISPLIST_SIZE];		// The display list
int				dlindex;								// Max index in display list
int				headIndex;								// Index of the head of the display list
PDispNode		dlptr;									// Ptr to current node of display list


#define INWORLD_BOUNDS 16


BOOL AnimInWorld( PAnim pAnim, int x, int y )
{
	SPRITE *pSprite;

	if( !pAnim )
		return FALSE;
recurse:
	if( !(pSprite = pAnim->pSprite) )
		return FALSE;

	if( x - pSprite->hotspot.x < INWORLD_BOUNDS )
		return FALSE;
	if( x - pSprite->hotspot.x + pSprite->srect.right > the_map.FullPixelBox.cx - INWORLD_BOUNDS )
		return FALSE;
	if( y - pSprite->hotspot.y < INWORLD_BOUNDS )
		return FALSE;
	if( y - pSprite->hotspot.y + pSprite->srect.right > the_map.FullPixelBox.cy - INWORLD_BOUNDS )
		return FALSE;

	if( !(pAnim->flags & ANIM_FLAG_CELL) )
	{
		if( ((ANIM *)pAnim)->pChild )
		{
			SPOINT pt;
			
			pt = ((ANIM *)pAnim)->pFrame[((ANIM *)pAnim)->current_frame].secondary_hotspot;
			x = x + pt.x;
			y = y + pt.y;
			pAnim = (PAnim)(((ANIM *)pAnim)->pChild);
			goto recurse;
		}
		else
			return TRUE;
	}
	else
		return TRUE;
}


//	return n for [f(x): 2^n = x]
int	 CvtBits( int x )
{
	switch( x )
	{
	case 2:
		return 1;
	case 4:
		return 2;
	case 8:
		return 3;
	case 16:
		return 4;
	case 32:
		return 5;
	case 64:
		return 6;
	case 128:
		return 7;
	case 256:
		return 8;
	case 512:
		return 9;
	}
	TRACE( "ERROR in file: %s, line: %d\n", __FILE__, __LINE__ );
	ASSERT( 1 );
	return 0;
}	//	CvtBits


//  return a pointer to the layer
inline PObjectLayer GetLayerPointer( EObjectLayer layer )
{
	switch( layer )
	{
	case OL_GROUNDLAYER:
		return( &the_map.groundlayer );
	case OL_ORDEREDLAYER:
		return( &the_map.orderedlayer );
	case OL_TOPLAYER:
		return( &the_map.toplayer );
	case OL_OVERLAYLAYER:
		return( &the_map.overlaylayer );
	default:
		TRACE( "ERROR in file: %s, line:%d\n", __FILE__, __LINE__ );
		ASSERT( 1 );
		return( NULL );
	}
}	// GetLayerPointer


BOOL flagUseOrderNumber = FALSE;

//	return 0 if no ordering preference, 1 to draw b before a, -1 to draw a before b
int	OrderingFunction( PAnim pA, PAnim pB )
{
//	int oA, oB;

	if ((!pA) || (!pB)) 
		return 0;

	if( !flagUseOrderNumber )
		goto noordernumber;

	if( pA->order > 0 && pB->order > 0 )
		if( pA->order > pB->order )
			return 1;
		else
			return -1;

noordernumber:
	if( pA->world_pos.y > pB->world_pos.y )
		return 1;
	if( pA->world_pos.y < pB->world_pos.y )
		return -1;
	if( pA->world_pos.x > pA->world_pos.y )
		return 1;
	return -1;
}	//	OrderingFunction


void InsertAnimInDispXLayerCell( TDispNode &dnode, PDispNode *displist )
{
	if( *displist == NULL )
	{
		*displist = &dnode;
		dnode.prev = dnode.next = NULL;
		return;
	}
	else
	{
		PDispNode dp;

		dp = *displist;
		if( OrderingFunction( dnode.pAnim, dp->pAnim ) <= 0 )
		{
			dnode.prev = NULL;
			dnode.next = dp;
			dp->prev = &dnode;
			*displist = &dnode;
			return;
		}
		else
		{
			do
			{
				if( dp->next == NULL )
				{
					dp->next = &dnode;
					dnode.prev = dp;
					dnode.next = NULL;
					return;
				}
				dp = dp->next;
			} while( OrderingFunction( dnode.pAnim, dp->pAnim ) > 0 );
			//	insert before dp (dp is guaranteed to not be the head
			dnode.prev = dp->prev;
			dnode.next = dp;
			dp->prev = &dnode;
			dnode.prev->next = &dnode;			
		}
	}
}	//	InsertAnimInDispXLayerCell


void InsertAnimInDispXLayer( PAnim pAnim )
{
	int				i, j, f, idx, l;
	int				yi1, yi2, xi1, xi2;
	PObjectLayer	pLayer;
	int				cellsize, bitwidth;

	pLayer = GetLayerPointer( pAnim->layer );		// get the layer the anim is in
	cellsize = pLayer->cellsize;
	bitwidth = pLayer->bitwidth;
	xi1 = pAnim->wrect.left >> cellsize;
	yi1 = pAnim->wrect.top >> cellsize;
	xi2 = pAnim->wrect.right >> cellsize;
	yi2 = pAnim->wrect.bottom >> cellsize;
	f = 0;
	idx = (yi1 << bitwidth) + xi1;

/*
	if( idx < 0 )
		return;
	if( ((yi2 << bitwidth) + xi2) >=
		    (pLayer->height << bitwidth) )
		return;
*/
	ASSERT( idx >= 0 );
	ASSERT( ((yi2 << bitwidth) + xi2) < 
		    (pLayer->height << bitwidth) );

	l = pLayer->width - ( xi2 - xi1 + 1 );
	// insert relevant feet
	for( j = yi1; j <= yi2; j++ )
	{
		for( i = xi1; i <= xi2; i++ )
		{
			pAnim->feet[f].index = idx;
			InsertAnimInDispXLayerCell( pAnim->feet[f].dnode, pLayer->cells + idx );
			f++;
			idx++;
		}
		idx += l;
	}

	// clear remaining feet
	while( f < pAnim->num_feet )
	{
		pAnim->feet[f].index = -1;
		pAnim->feet[f].dnode.prev = pAnim->feet[f].dnode.next = NULL;
		f++;
	}
}	// InsertAnimInDispXLayer


//	reorder a display node within its display list
void ReorderDispXLayerDisplayList( TDispNode &dnode, PDispNode *dlist )
{
	PDispNode dp;

	if( dnode.next != NULL )	
		if( OrderingFunction( dnode.pAnim, dnode.next->pAnim ) > 0 )
		{
			dp = dnode.next;
			do
			{
				if( dp->next == NULL )
				{
					//	move dnode to end
					if( dnode.prev == NULL )					
						*dlist = dnode.next;
					else
						dnode.prev->next = dnode.next;
					dnode.next->prev = dnode.prev;
					dnode.prev = dp;
					dnode.next = NULL;
					dp->next = &dnode;
					return;
				}
				dp = dp->next;
			} while( OrderingFunction( dnode.pAnim, dp->pAnim ) > 0 );
			//	move dnode to be between dp->prev & dp
			if( dnode.prev == NULL )
				*dlist = dnode.next;
			else
				dnode.prev->next = dnode.next;
			dnode.next->prev = dnode.prev;
			dnode.prev = dp->prev;
			dnode.next = dp;
			dp->prev->next = &dnode;
			dp->prev = &dnode;
			return;
		}
	if( dnode.prev != NULL )
		if( OrderingFunction( dnode.pAnim, dnode.prev->pAnim ) < 0 )
		{
			dp = dnode.prev;
			do
			{
				if( dp->prev == NULL )
				{
					// move dnode to beginning
					dnode.prev->next = dnode.next;
					if( dnode.next != NULL )
						dnode.next->prev = dnode.prev;
					dnode.prev = NULL;
					dnode.next = dp;
					dp->prev = &dnode;
					*dlist = &dnode;
					return;
				}
				dp = dp->prev;
			}  while( OrderingFunction( dnode.pAnim, dp->pAnim ) < 0 );
			//	move dnode to be between dp & dp->next
			dnode.prev->next = dnode.next;
			if( dnode.next != NULL )
				dnode.next->prev = dnode.prev;
			dnode.prev = dp;
			dnode.next = dp->next;
			dp->next->prev = &dnode;
			dp->next = &dnode;
			return;
		}
}	//	ReorderDispXLayerDisplayList


//	remove a link from a display list of any kind
void RemoveFromDisplayList( TDispNode &dnode, PDispNode *dlist )
{
	if( dnode.prev == NULL )
	{
		*dlist = dnode.next;
		if( dnode.next != NULL )
			dnode.next->prev = NULL;
		dnode.prev = dnode.next = NULL;
		return;
	}
	dnode.prev->next = dnode.next;
	if( dnode.next != NULL )
		dnode.next->prev = dnode.prev;
	dnode.prev = dnode.next = NULL;
}	//	RemoveFromDisplayList


//	moves a dispx object & updates the UpdateRectList (we re-check each corner since item could
//	have changed size!
void MoveObjectInDispXLayer( PAnim pAnim, BOOL ForceUpdate )
{
	int				i, j, idx, f, l;
	int				x, y;
	int				yi1, yi2, xi1, xi2;
	int				width, height, cellsize, bitwidth;
	PSPRITE			pSprite;
	PObjectLayer	pLayer;

	pLayer = GetLayerPointer( pAnim->layer );
	switch( pAnim->layer )
	{
	case OL_GROUNDLAYER:							// pick ordering method
	case OL_TOPLAYER:
		flagUseOrderNumber = TRUE;
		break;
	default:
		flagUseOrderNumber = FALSE;
		break;
	}

	if( !(pAnim->flags & ANIM_FLAG_ACTIVE) )
	{												// if anim isn't active, remove it
		if( pAnim->num_feet > 0 )
		{
			if( pAnim->feet[0].index >= 0 )
			{										// redraw its' rect
				InsertRectInUpdateList( pAnim->wrect );
				i = 0;								// remove its' feet
				while( (i < pAnim->num_feet) && (pAnim->feet[i].index >= 0) )
				{
					RemoveFromDisplayList( pAnim->feet[i].dnode, pLayer->cells + pAnim->feet[i].index );
					pAnim->feet[i].index = -1;
					i++;
				}
			}
		}
		return;										// done
	}

 	if( (!ForceUpdate) &&							// don't move if it hasn't changed
		(pAnim->world_pos.x == pAnim->old_world_pos.x) &&
		(pAnim->world_pos.y == pAnim->old_world_pos.y) &&
		(pAnim->pSprite == pAnim->prevSprite) )
		return;
	if( !(pAnim->pSprite) )
		return;

	InsertRectInUpdateList( pAnim->wrect );			// redraw old rectangle

	pSprite = pAnim->pSprite;						// calc. new position & dimensions
	pLayer = GetLayerPointer( pAnim->layer );
	if( !(pAnim->flags & ANIM_FLAG_CELL) )
	{
		if( ((ANIM *)pAnim)->pFrame )
		{
			pSprite->hotspot.x = ((ANIM *)pAnim)->pFrame[((ANIM *)pAnim)->current_frame].primary_hotspot.x;
			pSprite->hotspot.y = ((ANIM *)pAnim)->pFrame[((ANIM *)pAnim)->current_frame].primary_hotspot.y;
		}
	}
	width = pSprite->srect.right;
	height = pSprite->srect.bottom;
	pAnim->wrect.left = pAnim->world_pos.x - pSprite->hotspot.x;
	pAnim->wrect.top = pAnim->world_pos.y - pSprite->hotspot.y - pAnim->world_z;
	pAnim->wrect.right = pAnim->wrect.left + width;
	pAnim->wrect.bottom = pAnim->wrect.top + height;
	x = pAnim->wrect.left;
	y = pAnim->wrect.top;

	cellsize = pLayer->cellsize;					//	compute 4 corners of anim
	bitwidth = pLayer->bitwidth;
	xi1 = x >> cellsize;
	yi1 = ( y >> cellsize );
	xi2 = ( x + width ) >> cellsize;
	yi2 = (( y + height ) >> cellsize);

	if( yi1 < 0 )
		yi1 = 0;
	if( xi1 < 0 )
		xi1 = 0;
	if( yi2 >= pLayer->height )
		yi2 = pLayer->height - 1;
	if( xi2 >= pLayer->width )
		xi2 = pLayer->width - 1;
	ASSERT( (yi1 << bitwidth) + xi1 >= 0 );
	ASSERT( (yi2 << bitwidth) + xi2 < (pLayer->height << bitwidth) );
	ASSERT( pAnim->num_feet >= ((xi2-xi1)+1) * ((yi2-yi1)+1) );

	f = 0;											// re-order or insert relevant feet
	idx = (yi1 << bitwidth) + xi1;
	l = pLayer->width - ( xi2 - xi1 + 1 );			// compute pitch
	for( j = yi1; j <= yi2; j++ )			
	{
		for( i = xi1; i <= xi2; i++ )
		{
			if( (pAnim->feet[f].index >= 0) && (pAnim->feet[f].index == idx) )
				ReorderDispXLayerDisplayList( pAnim->feet[f].dnode, pLayer->cells + idx );
			else
			{
				if( pAnim->feet[f].index >= 0 )
					RemoveFromDisplayList( pAnim->feet[f].dnode, pLayer->cells + pAnim->feet[f].index );
				pAnim->feet[f].index = idx;
				InsertAnimInDispXLayerCell( pAnim->feet[f].dnode, pLayer->cells + idx );
			}
			f++;
			idx++;
		}
		idx += l;
	}
	
	while( f < pAnim->num_feet )					// clear remaining feet
	{
		if( pAnim->feet[f].index >= 0 )
			RemoveFromDisplayList( pAnim->feet[f].dnode, pLayer->cells + pAnim->feet[f].index );
		else
			break;
		pAnim->feet[f].index = -1;
		f++;
	}
	
	RECT rc;
	rc.left = pAnim->wrect.left;					// update new rectangle
	rc.top = pAnim->wrect.top;
	rc.right = pAnim->wrect.right;
	rc.bottom = pAnim->wrect.bottom;
	InsertRectInUpdateList( rc );
}	//	MoveObjectInDispXLayer


//	height & width in pixels: maximum dimensions for this object
int CreateDispXObject( int width, int height, PAnim pAnim, EObjectLayer layer )
{
	int i, 
		cellsize,
		size;

	cellsize = (GetLayerPointer(layer))->cellsize;		// size of layer cell in 2^n
	if( width > 2 )										// a 128^2 cell allows a 129^2 object
		width -= 2;
	if( height > 2 )
		height -= 2;
	pAnim->num_feet = ((width >> cellsize) + 2) * ((height >> cellsize) + 2);
	size = sizeof(TDispFoot) * pAnim->num_feet;
	pAnim->feet = (TDispFoot *)malloc( size );

	for( i = 0; i < pAnim->num_feet; i++ )				// zero each foot
	{
		pAnim->feet[i].dnode.pAnim = pAnim;
		pAnim->feet[i].dnode.prev = pAnim->feet[i].dnode.next = NULL;
		pAnim->feet[i].index = -1;
	}
	DispXObjectCount++;									// increase the disp object count

	pAnim->layer = layer;								// setup the anim
	pAnim->prevSprite = NULL;
	if( !pAnim->pSprite )								// calculate the wrect, if possible
	{
		pAnim->wrect.left = 0;
		pAnim->wrect.top = 0;
		pAnim->wrect.right = 0;
		pAnim->wrect.bottom = 0;
		return size;
	}
	pAnim->wrect.left = pAnim->world_pos.x - pAnim->pSprite->hotspot.x;
	pAnim->wrect.top = pAnim->world_pos.y - pAnim->pSprite->hotspot.y;
	pAnim->wrect.right = pAnim->wrect.left + pAnim->pSprite->srect.right;
	pAnim->wrect.bottom = pAnim->wrect.top + pAnim->pSprite->srect.bottom;
	if( pAnim->wrect.left < 0 || pAnim->wrect.top < 0 )
		return size;
	if( !(pAnim->flags & ANIM_FLAG_ACTIVE) )
		return size;
	InsertAnimInDispXLayer( pAnim );

	return size;
}	//	CreateDispXObject


//	remove from any display lists & deallocate memory
void DestroyDispXObject( PAnim pAnim )
{
	PObjectLayer pLayer;

	if( pAnim->num_feet == 0 )							// already deallocated!
		return;

	pLayer = GetLayerPointer( pAnim->layer );

	if( pAnim->num_feet > 0 )
	{
		if( pAnim->feet[0].index >= 0 )
		{
			int i = 0;

			while( (i < pAnim->num_feet) && (pAnim->feet[i].index >= 0) )
			{
				RemoveFromDisplayList( pAnim->feet[i].dnode, pLayer->cells + pAnim->feet[i].index );
				pAnim->feet[i].index = -1;
				i++;
			}
		}
	}
	free( pAnim->feet );								// free the memory
	pAnim->num_feet = 0;

	DispXObjectCount--;									// decrement the allocation count
}	//	DestroyDispXObject


//	Move a cell within its layer (call to display for the first time or to erase as well)
void MoveDispXObject( PAnim pAnim, BOOL ForceUpdate )
{
	ASSERT( pAnim );

	if( (pAnim->flags & ANIM_FLAG_PREV_INVISIBLE) ^ (pAnim->flags & ANIM_FLAG_INVISIBLE) )
	{
		ForceUpdate = TRUE;
		if( pAnim->flags & ANIM_FLAG_INVISIBLE )
		{
			pAnim->flags |= ANIM_FLAG_PREV_INVISIBLE;
		}
		else
		{
			pAnim->flags &= ~ANIM_FLAG_PREV_INVISIBLE;
		}
	}

	MoveObjectInDispXLayer( pAnim, ForceUpdate );
	pAnim->prevSprite = pAnim->pSprite;					// store the "previous" sprite
}	//	MoveDispXObject


void ChangeAnimSprite( PAnim pAnim, EObjectLayer newlayer, PSprite pNewSprite )
{
	int cellsize, height, width, numfeet;

	if( !pNewSprite )
		return;

	if( pAnim->layer != newlayer )
		goto makenewdispxobject;

	cellsize = (GetLayerPointer(newlayer))->cellsize;		// size of layer cell in 2^n
	width = pNewSprite->srect.right;
	height = pNewSprite->srect.bottom;
	if( width > 2 )											// a 128^2 cell allows a 129^2 object
		width -= 2;
	if( height > 2 )
		height -= 2;
	numfeet = ((width >> cellsize) + 2) * ((height >> cellsize) + 2);
	if( numfeet > pAnim->num_feet )
		goto makenewdispxobject;

	pAnim->pSprite = pNewSprite;
	MoveDispXObject( pAnim, FALSE );
	return;

makenewdispxobject:											// create a new dispx object
	AnimInactivate( (ANIM *)pAnim, FALSE );
	MoveDispXObject( pAnim, FALSE );
	DestroyDispXObject( pAnim );
	pAnim->layer = newlayer;
	pAnim->pSprite = pNewSprite;
	AnimActivate( (ANIM *)pAnim, FALSE );
	CreateDispXObject( pAnim->pSprite->srect.right, pAnim->pSprite->srect.bottom + 16,
						pAnim, pAnim->layer );
	MoveDispXObject( pAnim, FALSE );
}
					  

//	Main display function
void DisplayMapX( void )
{
	RECT rect;

	DoTheQuake();
	if( the_map.redraw == REDRAW_FULL )					// redraw the entire screenrect
		DrawViewportSection( the_map.screenrect );
	else
		ScrollViewport();								// scroll

	rect.left = 0;										// convert screenrect to screen coord.
	rect.top = 0;
	rect.right = the_map.screenrect.right - the_map.screenrect.left;
	rect.bottom = the_map.screenrect.bottom - the_map.screenrect.top;
	pBackBuffer->BltFast( 0, 0, pTileBuffer, &rect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY );
	the_map.oldscreenrect.left = the_map.screenrect.left;
	the_map.oldscreenrect.top = the_map.screenrect.top;
	the_map.oldscreenrect.right = the_map.screenrect.right;
	the_map.oldscreenrect.bottom = the_map.screenrect.bottom;
	the_map.redraw = REDRAW_PARTIAL;

#ifndef FINAL
	debug_updatelistcount = UpdateList.tail;
	debug_displaylistcount = dlindex;
#endif

	ClearUpdateList();									// clear the update list
	UnlockDrawingSurface();								// unlock the drawing surface

	DrawOverlayLayer();

	DrawSargeChevron();

	if( curselectedunit  && ITEM_TYPE(curselectedunit) == ARMY_UNIT)
	{
		TROOPER *pTrooper;
		int i;
		UNIT* pUnit = (UNIT*) curselectedunit;
		FOR_EACH_TROOPER( pUnit, pTrooper, i )
		{
			DrawTrooperChevron(pTrooper);
		}
	}
//	TRACE("*** FRAME BOUNDARY ***\n");
}	//	DisplayMapX


#define  TILE_LEFT   ( (TILE & 31) << 4 )
#define  TILE_TOP	 ( (TILE & (~31)) >> 1 )

//	Draw map tiles clipped to a world-coordinate rectangle
void DrawBaseTilesInRect( RECT &rc )
{
	int		i, j;
	int		sx, x, y, 
			offsx, offsy,								// offset into a single tile
			widx, widy,									// width & height of a tile to draw
			lwidx, lwidy,								// width & height of a tile, stored
			TILE;										// contents of a tile
	int		lineskip;									// # of tiles to skip to get to next line
	RECT	tilerect,									// rectangle to draw (tile coordinates)
			tilerc;										// rect of tile in tileset
	short	*tilebufptr0;								// pointers to tile layers
	const DWORD	bltflags0 = DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY;
	const DWORD bltflags1 = DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY;

	// compute the tile coordinates to draw
	tilerect.left = rc.left >> 4;
	tilerect.right = rc.right >> 4;
	tilerect.top = rc.top >> 4;
	tilerect.bottom = rc.bottom >> 4;
	// get a pointer to the upper left corner of the tile layers
	i = (tilerect.top << the_map.bitwidth) + tilerect.left;
	tilebufptr0 = the_map.layers[0].tile_array + i;
	// compute the line skip amount
	lineskip =  the_map.layers[0].box.cx - (tilerect.right - tilerect.left + 1);

	// draw the first row
	{
		// compute the x, y screen coordinate from which to start drawing
		sx = x = rc.left - the_map.screenrect.left;
		y = rc.top - the_map.screenrect.top;

		// compute the offset into the tile from which to start drawing
		offsx = rc.left & 15;
		offsy = rc.top & 15;

		// compute the width of the tile to draw
		// this might not be rest of the tile if it ends in this tile
		if( tilerect.right == tilerect.left )
			widx = (rc.right & 15) - (rc.left & 15);
		else
			widx = 16 - offsx;
		if( tilerect.bottom == tilerect.top )
			widy = (rc.bottom & 15) - (rc.top & 15);
		else
			widy = 16 - offsy;
		// draw the first tile of the top row
		TILE = *tilebufptr0++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT + offsx;
			tilerc.top = TILE_TOP + offsy;
			tilerc.right = tilerc.left + widx;
			tilerc.bottom = tilerc.top + widy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		if( tilerect.right == tilerect.left )
		  	goto tiledraw_middlerows;		
		x += widx;
		// for each column after the first, excluding the last column
		for( i = tilerect.left + 1; i < tilerect.right; i++ )
		{
			TILE = *tilebufptr0++;
			if( TILE != NO_TILE )
			{
				tilerc.left = TILE_LEFT;
				tilerc.top = TILE_TOP + offsy;
				tilerc.right = tilerc.left + 16;
				tilerc.bottom = tilerc.top + widy;
				pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
			}
			x += 16;
		}
		lwidx = (rc.right & 15);
		// draw the last tile
		TILE = *tilebufptr0++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT;
			tilerc.top = TILE_TOP + offsy;
			tilerc.right = tilerc.left + lwidx;
			tilerc.bottom = tilerc.top + widy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
	}
tiledraw_middlerows:
	//	skip if no more rows
	if( tilerect.top == tilerect.bottom )
		return;
	//	move to next row
	tilebufptr0 += lineskip;
	x = sx;
	y += widy;
	offsy = 0;
	//	draw each row after the first row, excluding the last row
	for( j = tilerect.top + 1; j < tilerect.bottom; j++ )
	{
		// draw the first tile of an interior row
		TILE = *tilebufptr0++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT + offsx;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + widx;
			tilerc.bottom = tilerc.top + 16;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		if( tilerect.right == tilerect.left )			// if col width is 1, this row is done
		  	goto tiledraw_nextrow;
		x += widx;
		for( i = tilerect.left + 1; i < tilerect.right; i++ )
		{
			TILE = *tilebufptr0++;						// draw each interior tile
			if( TILE != NO_TILE )
			{
				tilerc.left = TILE_LEFT;
				tilerc.top = TILE_TOP;
				tilerc.right = tilerc.left + 16;
				tilerc.bottom = tilerc.top + 16;
				pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
			}
			x += 16;
		}
		TILE = *tilebufptr0++;							// draw last tile of interior row
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + lwidx;
			tilerc.bottom = tilerc.top + 16;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		x = sx;
tiledraw_nextrow:
		tilebufptr0 += lineskip;
		y += 16;
	}
	// draw the last row
	{
		lwidy = (rc.bottom & 15);
		// draw the first tile of the last row
		TILE = *tilebufptr0++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT + offsx;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + widx;
			tilerc.bottom = tilerc.top + lwidy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		if( tilerect.left == tilerect.right )			// done if there col width is 1
			return;
		x += widx;
		for( i = tilerect.left + 1; i < tilerect.right; i++ )
		{												// draw interior tiles of last row
			TILE = *tilebufptr0++;
			if( TILE != NO_TILE )
			{
				tilerc.left = TILE_LEFT;
				tilerc.top = TILE_TOP;
				tilerc.right = tilerc.left + 16;
				tilerc.bottom = tilerc.top + lwidy;
				pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
			}
			x += 16;
		}
		TILE = *tilebufptr0++;							// draw last tile of last row
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + lwidx;
			tilerc.bottom = tilerc.top + lwidy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
	}
}	//	DrawBaseTilesInRect


//	Draw map tiles clipped to a world-coordinate rectangle
void DrawTilesInRect( RECT &rc )
{
	int		i, j;
	int		sx, x, y, 
			offsx, offsy,								// offset into a single tile
			widx, widy,									// width & height of a tile to draw
			lwidx, lwidy,								// width & height of a tile, stored
			TILE;										// contents of a tile
	int		lineskip;									// # of tiles to skip to get to next line
	RECT	tilerect,									// rectangle to draw (tile coordinates)
			tilerc;										// rect of tile in tileset
	short	*tilebufptr0, *tilebufptr1;					// pointers to tile layers
	const DWORD	bltflags0 = DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY;
	const DWORD bltflags1 = DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY;

	// compute the tile coordinates to draw
	tilerect.left = rc.left >> 4;
	tilerect.right = rc.right >> 4;
	tilerect.top = rc.top >> 4;
	tilerect.bottom = rc.bottom >> 4;
	// get a pointer to the upper left corner of the tile layers
	i = (tilerect.top << the_map.bitwidth) + tilerect.left;
	tilebufptr0 = the_map.layers[0].tile_array + i;
	tilebufptr1 = the_map.layers[1].tile_array + i;
	// compute the line skip amount
	lineskip =  the_map.layers[0].box.cx - (tilerect.right - tilerect.left + 1);

	// draw the first row
	{
		// compute the x, y screen coordinate from which to start drawing
		sx = x = rc.left - the_map.screenrect.left;
		y = rc.top - the_map.screenrect.top;

		// compute the offset into the tile from which to start drawing
		offsx = rc.left & 15;
		offsy = rc.top & 15;

		// compute the width of the tile to draw
		// this might not be rest of the tile if it ends in this tile
		if( tilerect.right == tilerect.left )
			widx = (rc.right & 15) - offsx;
		else
			widx = 16 - offsx;
		if( tilerect.bottom == tilerect.top )
			widy = (rc.bottom & 15) - offsy;
		else
			widy = 16 - offsy;
		// draw the first tile of the top row
		TILE = *tilebufptr0++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT + offsx;
			tilerc.top = TILE_TOP + offsy;
			tilerc.right = tilerc.left + widx;
			tilerc.bottom = tilerc.top + widy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		TILE = *tilebufptr1++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT + offsx;
			tilerc.top = TILE_TOP + offsy;
			tilerc.right = tilerc.left + widx;
			tilerc.bottom = tilerc.top + widy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags1 );
		}
		if( tilerect.right == tilerect.left )
		  	goto tiledraw_middlerows;		
		x += widx;
		// for each column after the first, excluding the last column
		for( i = tilerect.left + 1; i < tilerect.right; i++ )
		{
			TILE = *tilebufptr0++;
			if( TILE != NO_TILE )
			{
				tilerc.left = TILE_LEFT;
				tilerc.top = TILE_TOP + offsy;
				tilerc.right = tilerc.left + 16;
				tilerc.bottom = tilerc.top + widy;
				pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
			}
			TILE = *tilebufptr1++;
			if( TILE != NO_TILE )
			{
				tilerc.left = TILE_LEFT;
				tilerc.top = TILE_TOP + offsy;
				tilerc.right = tilerc.left + 16;
				tilerc.bottom = tilerc.top + widy;
				pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags1 );
			}
			x += 16;
		}
		lwidx = (rc.right & 15);
		// draw the last tile
		TILE = *tilebufptr0++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT;
			tilerc.top = TILE_TOP + offsy;
			tilerc.right = tilerc.left + lwidx;
			tilerc.bottom = tilerc.top + widy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		TILE = *tilebufptr1++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT;
			tilerc.top = TILE_TOP + offsy;
			tilerc.right = tilerc.left + lwidx;
			tilerc.bottom = tilerc.top + widy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags1 );
		}
	}
tiledraw_middlerows:
	//	skip if no more rows
	if( tilerect.top == tilerect.bottom )
		return;
	//	move to next row
	tilebufptr0 += lineskip;
	tilebufptr1 += lineskip;
	x = sx;
	y += widy;
	offsy = 0;
	//	draw each row after the first row, excluding the last row
	for( j = tilerect.top + 1; j < tilerect.bottom; j++ )
	{
		// draw the first tile of an interior row
		TILE = *tilebufptr0++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT + offsx;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + widx;
			tilerc.bottom = tilerc.top + 16;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		TILE = *tilebufptr1++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT + offsx;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + widx;
			tilerc.bottom = tilerc.top + 16;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags1 );
		}
		if( tilerect.right == tilerect.left )			// if col width is 1, this row is done
		  	goto tiledraw_nextrow;
		x += widx;
		for( i = tilerect.left + 1; i < tilerect.right; i++ )
		{
			TILE = *tilebufptr0++;						// draw each interior tile
			if( TILE != NO_TILE )
			{
				tilerc.left = TILE_LEFT;
				tilerc.top = TILE_TOP;
				tilerc.right = tilerc.left + 16;
				tilerc.bottom = tilerc.top + 16;
				pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
			}
			TILE = *tilebufptr1++;
			if( TILE != NO_TILE )
			{
				tilerc.left = TILE_LEFT;
				tilerc.top = TILE_TOP;
				tilerc.right = tilerc.left + 16;
				tilerc.bottom = tilerc.top + 16;
				pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags1 );
			}
			x += 16;
		}
		TILE = *tilebufptr0++;							// draw last tile of interior row
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + lwidx;
			tilerc.bottom = tilerc.top + 16;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		TILE = *tilebufptr1++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + lwidx;
			tilerc.bottom = tilerc.top + 16;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags1 );
		}
		x = sx;
tiledraw_nextrow:
		tilebufptr0 += lineskip;
		tilebufptr1 += lineskip;
		y += 16;
	}
	// draw the last row
	{
		lwidy = (rc.bottom & 15);
		// draw the first tile of the last row
		TILE = *tilebufptr0++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT + offsx;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + widx;
			tilerc.bottom = tilerc.top + lwidy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		TILE = *tilebufptr1++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT + offsx;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + widx;
			tilerc.bottom = tilerc.top + lwidy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags1 );
		}
		if( tilerect.left == tilerect.right )			// done if there col width is 1
			return;
		x += widx;
		for( i = tilerect.left + 1; i < tilerect.right; i++ )
		{												// draw interior tiles of last row
			TILE = *tilebufptr0++;
			if( TILE != NO_TILE )
			{
				tilerc.left = TILE_LEFT;
				tilerc.top = TILE_TOP;
				tilerc.right = tilerc.left + 16;
				tilerc.bottom = tilerc.top + lwidy;
				pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
			}
			TILE = *tilebufptr1++;
			if( TILE != NO_TILE )
			{
				tilerc.left = TILE_LEFT;
				tilerc.top = TILE_TOP;
				tilerc.right = tilerc.left + 16;
				tilerc.bottom = tilerc.top + lwidy;
				pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags1 );
			}
			x += 16;
		}
		TILE = *tilebufptr0++;							// draw last tile of last row
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + lwidx;
			tilerc.bottom = tilerc.top + lwidy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags0 );
		}
		TILE = *tilebufptr1++;
		if( TILE != NO_TILE )
		{
			tilerc.left = TILE_LEFT;
			tilerc.top = TILE_TOP;
			tilerc.right = tilerc.left + lwidx;
			tilerc.bottom = tilerc.top + lwidy;
			pTileBuffer->BltFast( x, y, the_tiles.tile_data, &tilerc, bltflags1 );
		}
	}
}	//	DrawTilesInRect


//	Redraw each rect from the Update List
void UpdateViewport( RECT &rc )
{
	int  i;
	RECT iRect;

	i = UpdateList.array[0].next;
	while( i != 0 )
	{
		if( RectIntersect( &(UpdateList.array[i].rect), &rc, &iRect ) )
		{
			DrawViewportSection( iRect );
		}
		i = UpdateList.array[i].next;
	}
}	//	UpdateViewport


void DrawDebugLayerRect( RECT &rc )	
{
#ifndef FINAL
	char	character;
	int		xb, yb, xe, ye,
			tilex,
			tiley;

	if ( !displaydebug )
		return;

	xb = rc.left >> 4;
	yb = rc.top >> 4;
	xe = rc.right >> 4;
	ye = rc.bottom >> 4;

	for( tiley = yb; tiley <= ye; tiley++ )	
	{
		for( tilex = xb; tilex <= xe; tilex++ )	
		{
			character = the_map.debug_layer[(tiley << the_map.bitwidth) + tilex];
			if( isprint(character) )
			{
				BYTE *data;
				RECT srect, irect;
				int	 w, h;
				int	 x, y;

				data = BmpTextGetCharData( BMPFONT_MAP, character );
				if( data )
				{
					srect.left = (tilex << 4) + 4;
					srect.top = (tiley << 4) + 2;
					w = *(WORD *)data;
					h = *(WORD *)(data + 2);
					srect.right = srect.left + w;
					srect.bottom = srect.top + h;

					if (!RectIntersect( &rc, &srect, &irect) )
						continue;

					irect.right -= irect.left;
					irect.bottom -= irect.top;
					x = irect.left - the_map.screenrect.left;
					y = irect.top - the_map.screenrect.top;
					irect.left = irect.left - srect.left;
					irect.top = irect.top - srect.top;
					irect.right += irect.left;
					irect.bottom += irect.top;

					DrawSRleClippedColor( x, y, data, irect, CYAN_IDX );
				}
			}
		}
	}
#endif
}


//	Redraw a portion of the screen to the backbuffer
void DrawViewportSection( RECT &rc )
{
	if( rc.top == rc.bottom || rc.left == rc.right )
	{
		EraseBackSurface();
		return;
	}

	if( the_map.num_layers > 1 )
		DrawTilesInRect( rc );
	else
		DrawBaseTilesInRect( rc );

	flagUseOrderNumber = TRUE;
	DrawDispXLayerRect( rc, GetLayerPointer(OL_GROUNDLAYER) );
	flagUseOrderNumber = FALSE;
	DrawDispXLayerRect( rc, GetLayerPointer(OL_ORDEREDLAYER) );
	flagUseOrderNumber = TRUE;
	DrawDispXLayerRect( rc, GetLayerPointer(OL_TOPLAYER) );
	DrawDebugLayerRect( rc );
}	//	DrawViewportSection


void DrawOverlayLayer( void )
{
	RECT rect;

	if( !LockOverlayLayer() )
		return;
	rect = the_map.screenrect;
	rect.right -= 1;
	rect.bottom -= 1;
	DrawOverlayLayerRect( rect );
	UnlockOverlayLayer();
}	//  DrawOverlayLayer



//	scroll the viewport
void ScrollViewport( void )
{
	RECT	irect, srect;
	int	drectx, drecty;

	if( the_map.screenrect.top == the_map.screenrect.bottom || the_map.screenrect.left == the_map.screenrect.right )
	{
		EraseBackSurface();
		return;
	}

	// current map position is at map.screenrect, old map position is map.oldscreenrect
	if( !RectIntersect( &the_map.screenrect, &the_map.oldscreenrect, &irect) )
	{													// redraw the whole thing!
		DrawViewportSection( the_map.screenrect );
	}
	else												// scroll and redraw
	{
		srect.left = irect.left - the_map.oldscreenrect.left;
		srect.top = irect.top - the_map.oldscreenrect.top;
		srect.right = irect.right - the_map.oldscreenrect.left;
		srect.bottom = irect.bottom - the_map.oldscreenrect.top;
		drectx = irect.left - the_map.screenrect.left;
		drecty = irect.top - the_map.screenrect.top;
		if( the_map.screenrect.left == the_map.oldscreenrect.left &&
			the_map.screenrect.top == the_map.oldscreenrect.top )
			goto noselfcopy;
		pTileBuffer->BltFast( drectx, drecty, pTileBuffer, &srect, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
noselfcopy:
		UpdateViewport( irect );						// update the copied portion

		if( the_map.oldscreenrect.top < the_map.screenrect.top )
		{
			srect.left = the_map.screenrect.left;
			srect.right = the_map.screenrect.right;
			srect.top = irect.bottom;
			srect.bottom = the_map.screenrect.bottom;
			DrawViewportSection( srect );				// draw the "new" bottom strip
			srect.top = the_map.screenrect.top;
			srect.bottom = irect.bottom;
		}
		else if( the_map.oldscreenrect.top > the_map.screenrect.top )
		{
			srect.left = the_map.screenrect.left;
			srect.right = the_map.screenrect.right;
			srect.top = the_map.screenrect.top;
			srect.bottom = irect.top;					// draw the "new" top strip
			DrawViewportSection( srect );
			srect.top = irect.top;
			srect.bottom = the_map.screenrect.bottom;
		}
		else
		{
			srect.top = the_map.screenrect.top;			// there is no "new" top strip!
			srect.bottom = the_map.screenrect.bottom;
		}
		if( the_map.oldscreenrect.left < the_map.screenrect.left )
		{
			srect.left = irect.right;
			srect.right = the_map.screenrect.right;
			DrawViewportSection( srect );				// draw the "new" right strip
		}
		else if( the_map.oldscreenrect.left > the_map.screenrect.left )
		{
			srect.left = the_map.screenrect.left;
			srect.right = irect.left;
			DrawViewportSection( srect );				// draw the "new" left strip
		}
	}
}	//	ScrollViewport


//	not done yet -- take out ordering stuff???
void InsertInDispList( PAnim pAnim, RECT &rc )
{
	int			i;
	PDispNode	tp;

	ASSERT( dlindex < MAX_SCREENDISPLIST_SIZE );
	
	if( !RectIntersect( &(pAnim->wrect), &rc, NULL ) )
		return;											// isn't in rect
	displist[dlindex].pAnim = pAnim;
	if( dlindex == 0 )									// this is the first node
	{
		dlptr = &(displist[dlindex]);
		headIndex = dlindex;
		dlptr->next = dlptr->prev = NULL;
		dlindex++;
		return;
	}

	ASSERT( dlptr != NULL );

	if( !(pAnim->flags & ANIM_FLAG_CELL ) )
	{
		ANIM		*pLink;
		PDispNode	dp;

		if( pLink = ((ANIM *)pAnim)->pParent )			// this anim has a parent
		{												// try to insert it after the parent
			dp = &(displist[headIndex]);
			while( dp != NULL )
			{
				if( (ANIMCELL *)pLink == dp->pAnim )
				{
					dlptr = dp;
					if( dp->next == NULL )
						goto insertastail;
					else
						goto insertafter;
				}
				dp = dp->next;
			}
		}
		else
		if( pLink = ((ANIM *)pAnim)->pChild )			// this anim has a child
		{												// try to insert it before the child
			dp = &(displist[headIndex]);
			while( dp != NULL )
			{
				if( (ANIMCELL *)pLink == dp->pAnim )
				{
					dlptr = dp;
					if( dp == &(displist[headIndex]) )
						goto insertashead;
					else
						goto insertbefore;
				}
				dp = dp->next;
			}
		}
	}

	i = OrderingFunction( pAnim, dlptr->pAnim );
	if( i == 0 )										// insert after dlptr!
	{
		displist[dlindex].prev = dlptr;
		displist[dlindex].next = dlptr->next;
		dlptr->next = &(displist[dlindex]);
		dlptr = &(displist[dlindex]);
		if( dlptr->next )
			dlptr->next->prev = dlptr;
		dlindex++;
		return;
	}
	if( i < 0 )											// walk up the list
	{
		do
		{
			if( dlptr->prev == NULL )
			{											// insert as head of list
insertashead:
				tp = dlptr;
				dlptr = &(displist[dlindex]);
				tp->prev = dlptr;
				dlptr->prev = NULL;
				dlptr->next = tp;
				headIndex = dlindex;
				dlindex++;
				return;
			}
			dlptr = dlptr->prev;
		} while( OrderingFunction( pAnim, dlptr->pAnim ) < 0 );
insertafter:
		tp = dlptr;
		dlptr = &(displist[dlindex]);					// insert after dlptr
		dlptr->prev = tp;
		dlptr->next = tp->next;
		tp->next = dlptr;
		dlptr->next->prev = dlptr;
		dlindex++;
		return;				
	}
	else												// walk down the list
	{
		do
		{
			if( dlptr->next == NULL )
			{
insertastail:
				tp = dlptr;								// insert as tail of list
				dlptr = &(displist[dlindex]);
				tp->next = dlptr;
				dlptr->prev = tp;	
				dlptr->next = NULL;
				dlindex++;
				return;
			}
			dlptr = dlptr->next;
		} while( OrderingFunction( pAnim, dlptr->pAnim ) > 0 );
insertbefore:
		tp = dlptr;										// insert before dlptr
		dlptr = &(displist[dlindex]);
		dlptr->prev = tp->prev;
		dlptr->next = tp;
		tp->prev = dlptr;
		if( dlptr->prev )
			dlptr->prev->next = dlptr;
		else
			headIndex = dlindex;
		dlindex++;
		return;
	}
}	// InsertInDispList


//	!!! note: modify so we only calculate the screen clip rect once
//	Draws the objects in the given layer clipped to the given rect.
void DrawDispXLayerRect( RECT &rc, PObjectLayer pLayer )
{
	int			mapskip;								// # cells to skip to get to next line
	PDispNode	dp;										// current disp node pointer
	PDispNode	*mapptr;								// pointer into object layer
	RECT		grid;									// cell grid for layer
	int			i, j;									// indices
	ANIMCELL	*pAnim;									// animcell we are working with
	int			xi1, yi1;								// cell coords for ul of pAnim
	int			cellsize;

//	flagUseOrderNumber = TRUE;
#ifndef FINAL
	if( dlindex > debug_displaylistcount )
		debug_displaylistcount = 0;
#endif
	dlindex = 0;										// clear the disp list
	headIndex = -1;
	
	cellsize = pLayer->cellsize;						// compute the grid (in cell coord)
	grid.left = rc.left >> cellsize;
	grid.top = rc.top >> cellsize;
	grid.right = rc.right >> cellsize;
	grid.bottom = rc.bottom >> cellsize;
														// compute pointer into ground layer
	mapptr = &(pLayer->cells[(grid.top << pLayer->bitwidth) + grid.left]);
	mapskip = pLayer->width - ( grid.right - grid.left ) - 1;

	for( j = grid.top; j <= grid.bottom; j++ )			// loop through each cell in rect
	{
		for( i = grid.left; i <= grid.right; i++ )
		{
			dp = *mapptr++;								// dp = head of displist for cell
			while( dp != NULL )
			{
				pAnim = dp->pAnim;
				if( !pAnim )
					goto nextnode;
				if( pAnim->flags & ANIM_FLAG_INVISIBLE )
					goto nextnode;
				// insert the dp into global displist if it hasn't already been inserted
				yi1 = pAnim->wrect.top >> cellsize;
				if( yi1 < j )
					if( j > grid.top )
						goto nextnode;					// it's already in!
				xi1 = pAnim->wrect.left >> cellsize;
				if( xi1 < i )
					if( i > grid.left )
						goto nextnode;					// it's already in!

				InsertInDispList( pAnim, rc );			// insert it
nextnode:
				dp = dp->next;							// go to next node in cell
			}
		}
		mapptr += mapskip;
	}

	//	draw the disp list
	if( headIndex == -1 )
		return;
	dp = &(displist[headIndex]);
	while( dp != NULL )
	{
		DrawAnimInRect( dp->pAnim, rc );
		dp = dp->next;
	}
}	//	DrawDispXLayerRect


void DrawOverlayLayerRect( RECT &rc )
{
	PDispNode	dp;
	PDispNode	*mapptr;
	int			mapskip;
	RECT		grid;
	int			i, j;
	ANIMCELL	*pAnim;
	int			xi1, yi1;								// top left cell coord for pAnim
	
	flagUseOrderNumber = FALSE;
#ifndef FINAL
	if( dlindex > debug_displaylistcount )
		debug_displaylistcount = 0;
#endif
	dlindex = 0;										// clear the display list
	headIndex = -1;
														// compute cell coord grid	
	grid.left = rc.left >> the_map.overlaylayer.cellsize;
	grid.top = rc.top >> the_map.overlaylayer.cellsize;
	grid.right = rc.right >> the_map.overlaylayer.cellsize;
	grid.bottom = rc.bottom >> the_map.overlaylayer.cellsize;

	ASSERT( grid.left >= 0 && grid.top >= 0 );
	mapptr = &(the_map.overlaylayer.cells[(grid.top << the_map.overlaylayer.bitwidth) + grid.left]);
	mapskip = the_map.overlaylayer.width - ( grid.right - grid.left ) - 1;

	for( j = grid.top; j <= grid.bottom; j++ )			// draw each cell in grid
	{
		for( i = grid.left; i <= grid.right; i++ )
		{
			dp = * mapptr++;
			while( dp != NULL )
			{
				// insert the dp if it hasn't already been inserted
				pAnim = dp->pAnim;
				if( !pAnim )
					goto nextnode;
				if( pAnim->flags & ANIM_FLAG_INVISIBLE )
					goto nextnode;
				yi1 = pAnim->wrect.top >> the_map.overlaylayer.cellsize;
				if( yi1 < j )
					if( j > grid.top )
						goto nextnode;
				xi1 = pAnim->wrect.left >> the_map.overlaylayer.cellsize;
				if( xi1 < i )
					if( i > grid.left )
						goto nextnode;

				InsertInDispList( pAnim, rc );
nextnode:
				dp = dp->next;
			}
		}
		mapptr += mapskip;
	}

	//	draw the disp list
	if( headIndex == -1 )
		return;
	dp = &(displist[headIndex]);
	while( dp != NULL )
	{
		DrawAnimInRectOverlay( dp->pAnim, rc );
		dp = dp->next;
	}
}	//	DrawOverlayLayerRect


//	Lock drawing surface (if LOCK_COMPLEX_ON then we don't need to do so)
void LockDrawingSurface( void )
{
	DDSURFACEDESC	ddsd;
	HRESULT			ddrval;

	if( LOCK_COMPLEX_ON )
	{
		if ( !LOCK_STATUS )
		{
			ddsd.dwSize = sizeof(DDSURFACEDESC);
			ddrval = pTileBuffer->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
			if ( ddrval == DD_OK )
			{
				SCRPTR = (BYTE *)ddsd.lpSurface;
				LPITCH = ddsd.lPitch;
				LOCK_STATUS = TRUE;
			}			
			else 
				TRACE( "Error trying to lock drawing surface in LockDrawingSurface()" );
		}
	}
	else
	{
		ddsd.dwSize = sizeof(DDSURFACEDESC);
		ddrval = pTileBuffer->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
		if ( ddrval == DD_OK )
		{
			SCRPTR = (BYTE *)ddsd.lpSurface;
			LPITCH = ddsd.lPitch;
		}			
		else 
			TRACE( "Error trying to lock drawing surface in LockDrawingSurface()" );
	}
}	//	LockDrawingSurface


//	Unlock drawing surface (if LOCK_COMPLEX_ON then we don't need to unlock it for now)
void DoneDrawingSurface( void )
{
	if( !LOCK_COMPLEX_ON )
		pTileBuffer->Unlock( SCRPTR );
#ifdef _DEBUG
	else
	{
		LOCK_STATUS = FALSE;
		pTileBuffer->Unlock( SCRPTR );
	}
#endif
}	//	DoneDrawingSurface


//	Unlock drawing surface (if lock_complex is on)
void UnlockDrawingSurface( void )
{
	if( !LOCK_COMPLEX_ON )
		return;
	if( LOCK_STATUS )
	{
		pTileBuffer->Unlock( SCRPTR );
		LOCK_STATUS = FALSE;
	}
}	//	UnlockDrawingSurface


//	Draw a sprite in the rectangle provided
void DrawSpriteInRect( PSPRITE ps, int x, int y, RECT &rect )
{
	// make sure we have a valid sprite and surface
	ASSERT( ps != NULL );

	if( ps->sprite_type == SPRITE_TYPE_SRLE )
	{
		LockDrawingSurface();
		PShadeTable = ps->trans_table;
		DrawSRleClippedShade( x, y, (BYTE *)(ps->pShadow), rect );
		PShadeTable = PSHADE_TABLE;
		DoneDrawingSurface();
		return;
	}
	if( ps->pGraphic == NULL )
		return;

	switch( ps->sprite_type )
	{
	case SPRITE_TYPE_DRLE:
		LockDrawingSurface();
		DrawDRleClipped( x, y, (BYTE *)ps->pGraphic, rect );
		DoneDrawingSurface();
		break;
	case SPRITE_TYPE_WRLE:
		LockDrawingSurface();
		DrawWRleClipped( x, y, (BYTE *)ps->pGraphic, rect );
		DoneDrawingSurface();
		break;
	case SPRITE_TYPE_TRLE:
		LockDrawingSurface();
		if( ps->trans_table )
			DrawTRleClipped( x, y, (BYTE *)ps->pGraphic, rect, ps->trans_table );
		else
			DrawWRleClipped( x, y, (BYTE *)ps->pGraphic, rect );
		DoneDrawingSurface();
		break;
	case SPRITE_TYPE_RLE:
		BYTE *pDestStart;

		LockDrawingSurface();
		pDestStart = (BYTE *)SCRPTR + y * LPITCH + x;
		if (ps->trans_table)
			RLETranslateBltClipped(	pDestStart, LPITCH,
									(BYTE *)ps->pGraphic, rect, ps->trans_table );
		else
			RLEFastBltClipped( pDestStart, LPITCH,
								(BYTE *)ps->pGraphic, rect );
		DoneDrawingSurface();
		break;
	case SPRITE_TYPE_BMP:
		HRESULT	ddrval;
		DWORD	flags = DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT;

		UnlockDrawingSurface();
		if ( ps->sprite_flags & SP_OPAQUE )
			flags = DDBLTFAST_WAIT;

		// Blt the sprite to the back surface
		ddrval = pTileBuffer->BltFast( x, y, (LPDIRECTDRAWSURFACE)ps->pGraphic, &rect, flags );
//		if ( ddrval != DD_OK )
//			TRACE( "Couldn't BltFast SPRITE: %s.\n", DDErrorToString(ddrval) );
	}
	if( ps->pShadow )
	{
		LockDrawingSurface();
		DrawSRleClippedShade( x, y, (BYTE *)(ps->pShadow), rect );
		DoneDrawingSurface();
	}
}	//	DrawSpriteInRect


//	Draw an anim object in a given rect (world-coordinates) : for now, don't handle child objs.
void DrawAnimInRect( PAnim pAnim, RECT &rc )
{
	int		x, y;
	PSPRITE	pSprite;
	RECT    srect, irect;

	if( !RectIntersect( &(pAnim->wrect), &rc, &irect ) )
		return;
	if( !(pAnim->flags & ANIM_FLAG_ACTIVE) )
		return;

	x = irect.left - the_map.screenrect.left;
	y = irect.top - the_map.screenrect.top;
	srect.left = irect.left - pAnim->wrect.left;
	srect.top = irect.top - pAnim->wrect.top;
	srect.right = irect.right - pAnim->wrect.left;
	srect.bottom = irect.bottom - pAnim->wrect.top;
	if( srect.bottom > pAnim->pSprite->srect.bottom )
		TRACE( "BOTTOM ERROR!!!!  %d  %d %d %p\n", pAnim->wrect.top, pAnim->wrect.bottom, pAnim->pSprite->srect.bottom, pAnim->pSprite );
	if( srect.top == srect.bottom || srect.left == srect.right )
		return;
	pSprite = pAnim->pSprite;
	pSprite->trans_table = pAnim->trans_table;

	DrawSpriteInRect( pSprite, x, y, srect );

#ifdef _DEBUG
	if( hotspots )
	{
		BYTE	*pDestStart;

		if( InRect( &srect, &(pSprite->hotspot) ) ) 
		{
			LockDrawingSurface();
			pDestStart = (BYTE *)SCRPTR + 
				(pAnim->world_pos.y - the_map.screenrect.top) * LPITCH + 
				(pAnim->world_pos.x - the_map.screenrect.left);
			*pDestStart = YELLOW_IDX;
			DoneDrawingSurface();
		}
	}
#endif
}	//	DrawAnimInRect


//	Draw a sprite in the rectangle provided on overlay layer
void DrawSpriteInRectOverlay( PSPRITE ps, int x, int y, RECT &rect )
{
	// make sure we have a valid sprite and surface
	ASSERT( ps != NULL );

	if( ps->sprite_type == SPRITE_TYPE_SRLE )
	{
		PShadeTable = ps->trans_table;
		DrawSRleClippedShade( x, y, (BYTE *)(ps->pShadow), rect );
		PShadeTable = PSHADE_TABLE;
		return;
	}
	if( ps->pGraphic == NULL )
		return;

	switch( ps->sprite_type )
	{
	case SPRITE_TYPE_DRLE:
		DrawDRleClipped( x, y, (BYTE *)ps->pGraphic, rect );
		break;
	case SPRITE_TYPE_WRLE:
		DrawWRleClipped( x, y, (BYTE *)ps->pGraphic, rect );
		break;
	case SPRITE_TYPE_TRLE:
		if( ps->trans_table )
			DrawTRleClipped( x, y, (BYTE *)ps->pGraphic, rect, ps->trans_table );
		else
			DrawWRleClipped( x, y, (BYTE *)ps->pGraphic, rect );
		break;
	case SPRITE_TYPE_RLE:
		BYTE *pDestStart;

		pDestStart = (BYTE *)SCRPTR + y * LPITCH + x;
		if (ps->trans_table)
			RLETranslateBltClipped(	pDestStart, LPITCH,
									(BYTE *)ps->pGraphic, rect, ps->trans_table );
		else
			RLEFastBltClipped( pDestStart, LPITCH,
								(BYTE *)ps->pGraphic, rect );
		break;
	}
	if( ps->pShadow )
	{
		DrawSRleClippedShade( x, y, (BYTE *)(ps->pShadow), rect );
	}
}	//	DrawSpriteInRectOverlay


//	Draw an anim object in a given rect (world-coordinates) : for now, don't handle child objs.
void DrawAnimInRectOverlay( PAnim pAnim, RECT &rc )
{
	int		x, y;
	PSPRITE	pSprite;
	RECT    srect, irect;

	if( !RectIntersect( &(pAnim->wrect), &rc, &irect ) )
		return;
	if( !(pAnim->flags & ANIM_FLAG_ACTIVE) )
		return;

	x = irect.left - the_map.screenrect.left;
	y = irect.top - the_map.screenrect.top;
	srect.left = irect.left - pAnim->wrect.left;
	srect.top = irect.top - pAnim->wrect.top;
	srect.right = irect.right - pAnim->wrect.left;
	srect.bottom = irect.bottom - pAnim->wrect.top;
	if( srect.bottom > pAnim->pSprite->srect.bottom )
		TRACE( "BOTTOM ERROR!!!!  %d  %d %d %p\n", pAnim->wrect.top, pAnim->wrect.bottom, pAnim->pSprite->srect.bottom, pAnim->pSprite );

	if( srect.right < pAnim->pSprite->srect.right )
		srect.right++;
	if( srect.bottom < pAnim->pSprite->srect.bottom )
		srect.bottom++;
	if( srect.top == srect.bottom || srect.left == srect.right )
		return;
	pSprite = pAnim->pSprite;
	pSprite->trans_table = pAnim->trans_table;

	DrawSpriteInRectOverlay( pSprite, x, y, srect );

#ifdef _DEBUG
	if( hotspots )
	{
		BYTE	*pDestStart;

		if( InRect( &srect, &(pSprite->hotspot) ) ) 
		{
			pDestStart = (BYTE *)SCRPTR + 
				(pAnim->world_pos.y - the_map.screenrect.top) * LPITCH + 
				(pAnim->world_pos.x - the_map.screenrect.left);
			*pDestStart = YELLOW_IDX;
		}
	}
#endif
}	//	DrawAnimInRect


//	initialize memory for an object layer of a given size (given in tiles) & cellsize given in bits
void InitObjectLayer( PObjectLayer layer, int width, int height, int cellsize )
{
	layer->width = ( width << 4 ) >> cellsize;
	layer->height = ( height << 4 ) >> cellsize;
	layer->cellsize = cellsize;

	layer->bitwidth = CvtBits( layer->width );
	if( layer->cells )
		free( layer->cells );

	int sz = sizeof(PDispNode) * layer->height * layer->width;
	layer->cells = (PDispNode *)malloc( sz );

	for( int i = 0; i < ( layer->height * layer->width ); i++ )
		layer->cells[i] = NULL;

	ASSERT( layer->cells != NULL );
}	//	InitObjectLayer


//	this should be called by the function that frees the map for each allocated object layer
void FreeObjectLayer( PObjectLayer layer )
{
	if( layer->cells != NULL )
	{
		for( int i = 0; i < ( layer->height * layer->width ); i++ )
			layer->cells[i] = NULL;
		free( layer->cells );
		layer->cells = NULL;
		layer->width = 0;
		layer->height = 0;
	}
}	//	FreeObjectLayer


//	Clear the update list
void ClearUpdateList( void )
{
	UpdateList.array[0].prev = UpdateList.array[0].next = 0;
	UpdateList.tail = 0;
}


//  Add a rectangle region to the end of the update list
void AddRectToUpdateList( int x1, int y1, int x2, int y2 )
{
	int	i;

	i = UpdateList.tail + 1;

/*
	ASSERT( i < MAX_UPDATELIST_SIZE );
	ASSERT( x1 >= 0 );
	ASSERT( x2 < 4096 );
	ASSERT( y1 >= 0 );
	ASSERT( y2 < 4096 );
*/
	if( i >= MAX_UPDATELIST_SIZE )
	{
		TRACE( "Display rectangles exceed max buffer, redraw screen.\n" );
		the_map.redraw = REDRAW_FULL;
		return;
	}
	UpdateList.array[i].rect.left = x1;
	UpdateList.array[i].rect.top = y1;
	UpdateList.array[i].rect.right = x2;
	UpdateList.array[i].rect.bottom = y2;
	UpdateList.array[i].next = 0;
	UpdateList.array[i].prev = UpdateList.tail;
	UpdateList.array[UpdateList.tail].next = i;
	UpdateList.tail = i;
}


//	Insert a rectangle region into the update list
void InsertRectInUpdateList( RECT &rect )
{
	UpdateListNode  *node;
	RECT			*b;
	RECT			a;
	int				sw;
	int				i;

	if( !RectIntersect( &rect, &(the_map.oldscreenrect), &a ) )
		return;

	i = UpdateList.tail + 1;
	if( i >= MAX_UPDATELIST_SIZE )
	{
		the_map.redraw = REDRAW_FULL;
		return;
	}
	ASSERT( i < MAX_UPDATELIST_SIZE );

	i = UpdateList.array[0].next;
	while( i != 0 )
	{
		node = &(UpdateList.array[i]);
		b = &(node->rect);
		if( RectIntersect( &a, b, NULL ) )
		{
			sw = 0;
			if( a.left >= b->left )
				if( a.left == b->left )
					sw += 27;
				else
					sw += 54;
			if( a.top >= b->top )
				if( a.top == b->top )
					sw += 9;
				else
					sw += 18;
			if( a.right >= b->right )
				if( a.right == b->right )
					sw += 3;
				else
					sw += 6;
			if( a.bottom >= b->bottom )
				if( a.bottom == b->bottom )
					sw += 1;
				else
					sw += 2;

			switch( sw )
			{
			case  0:
				AddRectToUpdateList( a.right, b->top, b->right, a.bottom );
				b->top = a.bottom;
				break;
			case  1:
			case  2:
			case 11:
			case 29:
				b->left = a.right;					// crop left of b
				break;
			case  3:
			case  6:
			case 12:
			case 15:
			case 33:
			case 42:
				b->top = a.bottom;					// crop top of b
				break;
			case  4:
			case  5:
			case  7:
			case  8:
			case 13:
			case 14:
			case 16:
			case 17:
			case 31:
			case 32:
			case 34:
			case 35:
			case 43:
			case 44:
				UpdateList.array[node->prev].next = node->next;		// subsume b into a				
				if( node->next == 0 )
					UpdateList.tail = node->prev;
				else
					UpdateList.array[node->next].prev = node->prev;
				break;
			case  9:
				a.right = b->right;					// subsume part of b
				b->top = a.bottom;					// crop top of b
				break;
			case 10:
				a.right = b->right;					// encompass b
				UpdateList.array[node->prev].next = node->next;		// subsume b into a				
				if( node->next == 0 )
					UpdateList.tail = node->prev;
				else
					UpdateList.array[node->next].prev = node->prev;
				break;
			case 18:
				AddRectToUpdateList( b->left, a.bottom, b->right, b->bottom );
				a.right = b->right;					// encompass part of b
				b->bottom = a.top;					// crop b
				break;
			case 19:
				a.right = b->right;					// encompass b right
				b->bottom = a.top;					// crop bottom of b
				break;
			case 20:
				AddRectToUpdateList( a.right, a.top, b->right, b->bottom );
				b->bottom = a.top;					// crop bottom of b
				break;
			case 21:
			case 24:
			case 51:
				AddRectToUpdateList( b->left, a.bottom, b->right, b->bottom );
				b->bottom = a.top;					// crop bottom of b
				break;
			case 22:
			case 23:
			case 25:
			case 26:
			case 52:
			case 53:
				b->bottom = a.top;					// crop bottom of b
				break;
			case 27:
			case 28:
			case 54:
			case 55:
			case 57:
			case 58:
				a.bottom = b->top;					// crop bottom of a
				break;
			case 30:
				a.bottom = b->bottom;				// encompass b below
				UpdateList.array[node->prev].next = node->next;		// subsume b into a				
				if( node->next == 0 )
					UpdateList.tail = node->prev;
				else
					UpdateList.array[node->next].prev = node->prev;
				break;
			case 41:
				UpdateList.array[node->prev].next = node->next;		// subsume b into a				
				if( node->next == 0 )
					UpdateList.tail = node->prev;
				else
					UpdateList.array[node->next].prev = node->prev;
				break;
			case 36:
			case 37:
			case 39:
			case 40:
			case 45:
			case 46:
			case 48:
			case 49:
			case 63:
			case 64:
			case 66:
			case 67:
			case 72:
			case 73:
			case 75:
			case 76:
				return;								// stop
			case 38:
			case 47:
			case 65:
			case 68:
			case 74:
			case 77:
				a.top = b->bottom;					// crop top of a
				break;
			case 50:
				a.top = b->top;						// encompass b above
				UpdateList.array[node->prev].next = node->next;		// subsume b into a				
				if( node->next == 0 )
					UpdateList.tail = node->prev;
				else
					UpdateList.array[node->next].prev = node->prev;
				break;
			case 56:
				AddRectToUpdateList( a.right, b->top, b->right, b->bottom );
				b->right = a.left;					// crop right of b
				break;
			case 59:
			case 61:
			case 62:
			case 71:
				b->right = a.left;					// crop right of b
				break;
			case 60:
				AddRectToUpdateList( b->left, b->top, a.left, a.bottom );
				b->top = a.bottom;					// crop top of b
				break;
			case 69:
				a.left = b->left;					// encompass top of b
				b->top = a.bottom;					// crop top of b
				break;
			case 70:
				a.left = b->left;					// encompass b to left
				UpdateList.array[node->prev].next = node->next;		// subsume b into a				
				if( node->next == 0 )
					UpdateList.tail = node->prev;
				else
					UpdateList.array[node->next].prev = node->prev;
				break;
			case 78:
			case 79:
				a.left = b->right;					// crop left of a
				break;
			case 80:
				AddRectToUpdateList( b->left, a.top, a.left, b->bottom );
				b->bottom = a.top;					// crop bottom of b
				break;
			}
		}

		i = node->next;		
	}
	AddRectToUpdateList( a.left, a.top, a.right, a.bottom );
}	//	InsertRectInUpdateList


BOOL ObjectMaskIntersectRect( ANIMCELL *pAnim, RECT &rect )
{
	int		x, y, pitch;
	BYTE	*pMask, *pLine, b, e;
	RECT	mRect, iRect;
	int		x1, x2;

	BYTE    bitMask[64] = 
	{
		128,   0,  0,  0,  0, 0, 0, 0,
		192,  64,  0,  0,  0, 0, 0, 0,
		224,  96, 32,  0,  0, 0, 0, 0,
		240, 112, 48, 16,  0, 0, 0, 0,
		248, 120, 56, 24,  8, 0, 0, 0,
		252, 124, 60, 28, 12, 4, 0, 0,
		254, 126, 62, 30, 14, 6, 2, 0,
		255, 127, 63, 31, 15, 7, 3, 1
	};

	if( !pAnim->pSprite )
		return FALSE;
	pMask = pAnim->pSprite->pMask;
	if( !pMask )
		return FALSE;

	pitch = ((pAnim->pSprite->srect.right + 31) & (~31)) >> 3;

	mRect = pAnim->wrect;
	if( !RectIntersect( &mRect, &rect, &iRect ) )
		return FALSE;
	iRect.left -= mRect.left;
	iRect.top -= mRect.top;
	iRect.right -= mRect.left;
	iRect.bottom -= mRect.bottom;

	x1 = iRect.left >> 3;
	x2 = iRect.right >> 3;
	pMask = pMask + iRect.top * pitch + x1;
	if( x1 == x2 )
	{
		b = ((iRect.left & 7) >> 3) + (iRect.right & 7);
		for( y = iRect.top; y <= iRect.bottom; y++ )
		{
			pLine = pMask;
			if( *pMask & bitMask[b] )
				return TRUE;
			pMask = pLine + pitch;
		}
	}
	else
	{
		b = (iRect.left & 7) + 56;
		e = (iRect.right & 7) >> 3;
		x1++;
		x2--;
		for( y = iRect.top; y <= iRect.bottom; y++ )
		{
			pLine = pMask;
			if( *pMask & bitMask[b] )
				return TRUE;
			pMask++;
			for( x = x1; x <= x2; x++ )
			{
				if( *pMask & 255 )
					return TRUE;
				pMask++;
			}
			if( *pMask & bitMask[e] )
				return TRUE;
			pMask = pLine + pitch;
		}
	}
	return FALSE;
}	//  ObjectMaskIntersectRect


//  return TRUE if the 1 bit mask intersects the point
BOOL ObjectMaskIntersectPoint( ANIMCELL *pAnim, SPOINT *pt )
{
	int		x, y, pitch;
	BYTE	*pMask, b;
	const BYTE	bitmask[8] =
	{
		128,
		64,
		32,
		16,
		8,
		4,
		2,
		1
	};

	if( !pAnim->pSprite )
		return FALSE;
	pMask = pAnim->pSprite->pMask;
	if( !pMask )
		return FALSE;

	x = pt->x - pAnim->wrect.left;
	y = pt->y - pAnim->wrect.top;

	pitch = ((pAnim->pSprite->srect.right + 31) & (~31)) >> 3;
	b = *(pMask + (y * pitch) + (x >> 3) );
	return ( b & bitmask[x & 7] );
}


//	return TRUE if animcell intersects a given point
BOOL ObjectIntersectPoint( ANIMCELL *pAnim, SPOINT *pt )
{
	RECT	rc;
	PSPRITE pSprite;

	if( !(pSprite = pAnim->pSprite) )
		return FALSE;

	if( pSprite->pMask )
	{
		if( InRect( &(pAnim->wrect), pt ) )	
			return ObjectMaskIntersectPoint( pAnim, pt );
		else
			return FALSE;
	}
	else 
	if( pSprite->sprite_flags & SP_USEBMPASMASK )
	{
		int offsx, offsy;
		if( !InRect( &(pAnim->wrect), pt ) )	
			return FALSE;
		ASSERT( pSprite->pGraphic );
		offsx = pt->x - pAnim->wrect.left;
		offsy = pt->y - pAnim->wrect.top;

		switch( pSprite->sprite_type )
		{
		case SPRITE_TYPE_DRLE:
			return( IsPointInDRle( offsx, offsy, (BYTE *)(pSprite->pGraphic) ) );
			break;
		case SPRITE_TYPE_WRLE:
		case SPRITE_TYPE_TRLE:
			return( IsPointInWRle( offsx, offsy, (BYTE *)(pSprite->pGraphic) ) );
			break;
		default:
			return( InRect( &(pAnim->wrect), pt ) );
		}
	}
	else
	if( pSprite->sprite_flags & SP_MASKRECT )
	{
		rc.left = pAnim->world_pos.x - pSprite->hotspot.x;
		rc.top = pAnim->world_pos.y - pSprite->hotspot.y;
		rc.right = rc.left + pSprite->maskRect.right;
		rc.bottom = rc.top +  pSprite->maskRect.bottom;
		rc.left += pSprite->maskRect.left;
		rc.top += pSprite->maskRect.top;
		return InRect( &rc, pt );
	}
	else
	if( pSprite->sprite_flags & SP_USESELFRECT )
		return( InRect( &(pAnim->wrect), pt ) );
	else
		return FALSE;
}


PItem GetObjectsIntersectPointInLayer( SPOINT *pPos, TObjectLayer &Layer, PItem pcurItemList )
{
	int			gridx, gridy;
	PDispNode	dp;
	PDispNode	*mapptr;
	PItem		pItemList, 
				pObject;

	ASSERT( InRect( &the_map.FullPixelRect, pPos ) );

	pItemList = pcurItemList;

	gridx = pPos->x >> Layer.cellsize;
	gridy = pPos->y >> Layer.cellsize;
	mapptr = &(Layer.cells[(gridy << Layer.bitwidth) + gridx]);
	//	process cells
	dp = *mapptr++;
	while( dp != NULL )
	{
		if( dp->pAnim->flags & ANIM_FLAG_ACTIVE )
		{
			pObject = (ITEM *)dp->pAnim->pOwner;
			if( pObject )	
			{
				if( UseRectIntersect )
				{
					if( InRect( &(dp->pAnim->wrect), pPos ) )
					{
						pObject->next = pItemList;
						pItemList = pObject;
					}
				}
				else
				if( ObjectIntersectPoint( dp->pAnim, pPos) )	
				{
					pObject->next = pItemList;
					pItemList = pObject;
				}
			}
		}
		dp = dp->next;
	}

	return pItemList;
}	//	GetObjectsIntersectPointInLayer


//  return a list of items which intersect a given point
PItem GetObjectsIntersectPoint( SPOINT *pPos )
{
	PItem		pItemList;

	ASSERT( InRect( &the_map.FullPixelRect, pPos ) );

	UseRectIntersect = 0;
	pItemList = GetObjectsIntersectPointInLayer( pPos, the_map.groundlayer, NULL );
	pItemList = GetObjectsIntersectPointInLayer( pPos, the_map.toplayer, pItemList );
	pItemList = GetObjectsIntersectPointInLayer( pPos, the_map.orderedlayer, pItemList );

	return pItemList;
}

//  return a list of items which mask a given point
PItem GetObjectsMaskPoint( SPOINT *pPos )
{
	PItem		pItemList;

	ASSERT( InRect( &the_map.FullPixelRect, pPos ) );

	UseRectIntersect = 1;
	pItemList = GetObjectsIntersectPointInLayer( pPos, the_map.groundlayer, NULL );
	pItemList = GetObjectsIntersectPointInLayer( pPos, the_map.toplayer, pItemList );
	pItemList = GetObjectsIntersectPointInLayer( pPos, the_map.orderedlayer, pItemList );

	return pItemList;
}


//  return the "amount" of damage an object suffers
//  based on how close the object is to the center of the explosion
//  !!! for now, just return 100%
int DoExplosionRect( RECT &explosionRect, RECT &itemRect )
{
	RECT tempRect;

	if( RectIntersect( &explosionRect, &itemRect, &tempRect ) )
		return 256;
	else
		return 0;
}	//  DoExplosionRect


ITEM * ProcessExplosionLayer( RECT &queryRect, TObjectLayer &Layer, ITEM *curpItemList )
{
	int			gx1, gy1, gx2, gy2;
	int			cellsize;
	PDispNode	dp;
	PDispNode	*mapptr;
	int			mapskip;
	int			i, j;
	ANIMCELL	*pAnim;
	int			xi1, yi1;								// top left cell coord for pAnim
	int			dmg;
	ITEM		*pItemList;
	RECT		itemRect;
	RECT		qRect;

	pItemList = curpItemList;

	cellsize = Layer.cellsize;							// compute cell coordinates

	if(!RectIntersect( &the_map.FullPixelRect, &queryRect, &qRect ) )
		return( NULL );

	gx1 = qRect.left >> cellsize;
	gy1 = qRect.top >> cellsize;
	gx2 = qRect.right >> cellsize;
	gy2 = qRect.bottom >> cellsize;

	ASSERT( gx1 >= 0 && gy1 >= 0 );

	mapptr = &(Layer.cells[(gy1 << Layer.bitwidth) + gx1]);
	mapskip = Layer.width - ( gx2 - gx1 ) - 1;

	for( j = gy1; j <= gy2; j++ )			// draw each cell in grid
	{
		for( i = gx1; i <= gx2; i++ )
		{
			dp = * mapptr++;
			while( dp != NULL )
			{
				// check the display node if it hasn't already been checked
				pAnim = dp->pAnim;
				yi1 = pAnim->wrect.top >> cellsize;
				if( yi1 < j )
					if( j > gy1 )
						goto nextnode;
				xi1 = pAnim->wrect.left >> cellsize;
				if( xi1 < i )
					if( i > gx1 )
						goto nextnode;

				if( !(pAnim->pSprite) )
					goto nextnode;
				// potentially add to collision list
				// insert code here
				if( pAnim->pSprite->sprite_flags & SP_MASKRECT )
				{
					itemRect.left = pAnim->wrect.left + pAnim->pSprite->maskRect.left;
					itemRect.top = pAnim->wrect.top + pAnim->pSprite->maskRect.top;
					itemRect.right = pAnim->wrect.left + pAnim->pSprite->maskRect.right;
					itemRect.bottom = pAnim->wrect.top + pAnim->pSprite->maskRect.bottom;
					dmg = DoExplosionRect( itemRect, qRect );
				}
				else if( pAnim->pSprite->pMask )
				{
					// for now: use DoExplosionRect with the sprite's srect
					dmg = DoExplosionRect( pAnim->wrect, qRect );
				}
				else if( pAnim->pSprite->sprite_flags & SP_USESELFRECT )
				{
					// for now: use DoExplosionRect with the sprite's srect
					dmg = DoExplosionRect( pAnim->wrect, qRect );
				}
				else 
				{
					dmg = 0;
					// dmg = DoExplosionRect( pAnim->wrect, qRect );
				}

				if( dmg > 0 )
				{
					ITEM * pItem;							// add the object to the itemlist

					if( pAnim->pOwner == NULL )
						goto nextnode;
					pItem = (ITEM *)pAnim->pOwner;
					pItem->next = pItemList;
					pItem->temp = dmg;					// use temp to store amt of dmg.
					pItemList = pItem;
				}
nextnode:
				dp = dp->next;
			}
		}
		mapptr += mapskip;
	}

	return pItemList;
}


//	determine explosion damage for objects in the world from a given explosion
//  returns a list of items (temp pointer for each item is set to the "%" of damage
ITEM * GetExplosionInfluence( RECT &queryRect)
{
	ITEM		*pItemList;

	pItemList = ProcessExplosionLayer( queryRect, the_map.toplayer, NULL );
	pItemList = ProcessExplosionLayer( queryRect, the_map.orderedlayer, pItemList );
	pItemList = ProcessExplosionLayer( queryRect, the_map.groundlayer, pItemList );
	return pItemList;
}	//	GetExplosionInfluence


