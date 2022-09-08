void StartCinematicMode( void );
void EndCinematicMode( void );
void CameraJumpToPoint( int x, int y );
void CameraFollowAnim( ANIM *pAnim );
void CameraMoveToPoint( int x, int y, int spd );

void Teletype( char *text, int delay, int persistence );


void CinemaMoveToPoint( SPOINT *spt, int spd);
void CinemaMoveToItem ( ITEM *pItem, int spd);
void CinemaJumpToPoint (SPOINT *spt);
void CinemaJumpToItem( ITEM *pItem);
