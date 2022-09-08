//========================================================================
//	FILE:			$Workfile: Movie.h $
//
//	DESCRIPTION:	AVI Movie state handler defines and prototypes.
//
//	Programmer:		Andrew J Burgess
//
//	CREATED:		Tuesday, July 01, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Movie.h 16    4/06/98 11:25p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Movie.h $
//  
//  16    4/06/98 11:25p Nrobinso
//  clear surfaces before playing movies
//  
//  14    4/02/98 9:39a Aburgess
//  modifications to support interlaced and non-interlaced Smaker videos
//  
//  13    3/25/98 8:12p Nrobinso
//  add IsMovie
//  
//  12    3/19/98 9:40a Aburgess
//  modifications made to present the 3DO logo Video
//  
//  11    3/09/98 9:57a Aburgess
//  new Movie Credits interface
//  
//  10    2/13/98 3:59p Nrobinso
//  remove avi player
//  
//  9     1/26/98 12:05p Nrobinso
//  new path defines
//  
//  8     1/20/98 11:03a Aburgess
//  removed SMACKER directory dependency.
//  
//  7     1/14/98 2:17p Aburgess
//  modifications made to support Smacker
//  
//  6     12/23/97 11:29a Aburgess
//  new MOVIE avi interface
//  
//  5     12/09/97 12:12p Phu
//  
//  4     11/24/97 2:50p Aburgess
//  new FINALE state
//  
//  3     11/12/97 10:28a Aburgess
//  new prototypes
//  
//  1     7/03/97 5:18p Nrobinso
//  
// 
//  $Nokeywords:$
///========================================================================

///========================================================================
//							GLOBAL DEFINES
///========================================================================
#define		MOVIE_PLAYBACK_WIDTH	640
#define		MOVIE_PLAYBACK_HEIGHT	480

#define MOVIE_PATH	"Avi"

typedef enum
{
	MOVIE_NULL_STATE = -1,
	MOVIE_3DO_STATE = 0,
	MOVIE_INTRO_STATE,
	MOVIE_WIN_STATE,
	MOVIE_LOSE_STATE,
	MOVIE_CREDITS_STATE,

	// no more states beyond this line
	MOVIE_LAST_STATE
} MOVIE_STATE;

typedef	struct	movieStateTable
{
	MOVIE_STATE	eMovieState;
	LONG		((*pInitCallback)(void));	  // Movie state initialization callback
	LONG		((*pTerminateCallback)(void));// Movie state termination callback
} MOVIESTATES;

///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================
extern	MOVIESTATES	MOVIEstateTable[ MOVIE_LAST_STATE ];

///========================================================================
//							GLOBAL PROTOTYPES
///========================================================================
extern	BOOL		MovieInit( void );
extern	void		MovieExit( void );
extern	void		MovieSetState( MOVIE_STATE eState );
extern	MOVIE_STATE	MovieGetState( void );
extern	void		MovieNextState( void );
extern	void		MoviePlay( HWND m_hWnd, char* pAviName, BOOL bInterlaced );
extern	LONG		MovieWhatIsNext( void );

extern	LONG		MovieInitCredits( void );
extern	BOOL		IsMovie( BOOL bWin );

///========================================================================
//								EOF
///========================================================================
