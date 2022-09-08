#include "stdafx.h"

#include "input.h"
#include "mainfrm.h"
#include "commands.h"
#include "anim.h"
#include "cinema.h"
#include "map.h"


TKeyBindingEntry	**priorKeyTable;
int					priorX, priorY;
char				cinemamode = 0;
ANIM				*pTrackee;


TKeyBindingEntry *CinematicKeyTable[] =
{
	DefaultKeys,
	NULL
};


void StartCinematicMode( void )
{
	if( cinemamode )
		return;
	priorKeyTable = pKeyTable;
	priorX = the_map.CurCenterPoint.x;
	priorY = the_map.CurCenterPoint.y;
	pKeyTable = CinematicKeyTable;
	cinemamode = 1;
}


void EndCinematicMode( void )
{
	if( !cinemamode )
		return;
	pKeyTable = priorKeyTable;
	MapJumpToPoint( priorX, priorY );
	cinemamode = 0;
}


void CameraJumpToPoint( int x, int y )
{
	if( !cinemamode )
		return;
	MapJumpToPoint( x, y );
}


void CameraFollowAnim( ANIM *pAnim )
{
	if( !cinemamode )
		return;
	pTrackee = pAnim;
	MapJumpToAnim( pTrackee, TRUE, FALSE, 0 );
}


void CameraMoveToPoint( int x, int y, int spd )
{
	if( !cinemamode )
		return;
	MapLookAtPoint( x, y );
}


void Teletype( char *text, int delay, int persistence )
{
	if( !cinemamode )
		return;
}

void CinemaMoveToPoint( SPOINT *spt, int spd)
{
}
void CinemaMoveToItem ( ITEM *pItem, int spd)
{
}
void CinemaJumpToPoint (SPOINT *spt)
{
}
void CinemaJumpToItem( ITEM *pItem)
{
}

