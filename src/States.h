//========================================================================
//	FILE:			$Workfile: States.h $
//
//	DESCRIPTION:	ArmyMen Game State definitions.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, October 1, 1997
//
//	REVISION:		$Header: /ArmyMen/src/States.h 14    4/08/98 12:17p Nrobinso $
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
//  $Log: /ArmyMen/src/States.h $
//  
//  14    4/08/98 12:17p Nrobinso
//  add a keyboard 'g' in map that turns units on & off
//  
//  12    3/29/98 5:34p Nrobinso
//  setup cheats
//  
//  11    3/27/98 4:50p Nrobinso
//  cheats override
//  
//  10    2/10/98 1:19p Nrobinso
//  remove old code
//  
//  9     2/01/98 10:58p Nrobinso
//  removed old dialog code
//  
//  8     1/28/98 10:19a Aburgess
//  modifications made to support game start MISSION recall. Support for
//  successive missions has not been implemented yet and will still display
//  the old MISSION STATEMENT interface. Additionally, access directly to
//  the HOST and REMOTE campaign select screens now occurs if in a lobby
//  session.
//  
//  7     1/23/98 9:38a Aburgess
//  modifications made to support new multiplayer screens
//  
//  6     12/18/97 1:22p Aburgess
//  Left Button Up prototype added.
//  
//  5     12/09/97 12:12p Phu
//  
//  4     12/01/97 9:56a Aburgess
//  modification of LoadBackground to parameterize palette creation. Screen
//  Processing modifications.
//  
//  3     11/07/97 10:43a Aburgess
//  change to use extern references
//  
//  2     10/27/97 11:28a Aburgess
//  mouse routines now part of title screen state
//  
//  1     10/05/97 12:13p Aburgess
//  Game State processing
//  
//  $Nokeywords:$
//========================================================================


//========================================================================
//========================================================================

extern	SUserInterface UI_TITLE_SCREEN_STATE;
extern	SUserInterface UI_STAT_SCREEN_STATE;
extern	SUserInterface UI_STATEMENT_SCREEN_STATE;
extern	SUserInterface UI_MPUI_SCREEN_STATE;
extern	SUserInterface UI_RECALL;

//========================================================================
//						PROTOTYPES
//========================================================================
extern	void	New_GAME_TITLE_SCREEN_STATE( GAME_STATE gameState );
extern	void	Old_GAME_TITLE_SCREEN_STATE( GAME_STATE gameState );
extern	BOOL	GLd_GAME_TITLE_SCREEN_STATE( void );
extern	void	Dsp_GAME_TITLE_SCREEN_STATE( void );
extern	void	Act_GAME_TITLE_SCREEN_STATE( void );
extern	BOOL	KeyOverride_GAME_TITLE_SCREEN_STATE(UINT key, BOOL down);
extern	BOOL	KeyOverride_CHEATS(UINT key, BOOL down);
extern	BOOL	KeyOverride_GAME_STAT_SCREEN_STATE(UINT key, BOOL down);
extern	BOOL	KeyOverride_GAME_STATEMENT_SCREEN_STATE(UINT key, BOOL down);
extern	BOOL	KeyOverride_MPUI_SCREEN_STATE(UINT key, BOOL down);

extern	BOOL	KeyOverride_RECALL(UINT key, BOOL down);
extern	BOOL	KeyOverride_RECALL_MAP(UINT key, BOOL down);

extern	void	New_GAME_START_STATE( GAME_STATE gameState );
extern	void	Old_GAME_START_STATE( GAME_STATE gameState );
extern	BOOL	GLd_GAME_START_STATE( void );
extern	void	Dsp_GAME_START_STATE( void );
extern	void	Act_GAME_START_STATE( void );

extern	void	New_GAME_TEST_STATE( GAME_STATE gameState );
extern	void	Old_GAME_TEST_STATE( GAME_STATE gameState );
extern	BOOL	GLd_GAME_TEST_STATE( void );
extern	void	Dsp_GAME_TEST_STATE( void );
extern	void	Act_GAME_TEST_STATE( void );

//------------------------------------------------------------------------

extern	SPRITE*	LoadBackground( char* sBmp, BOOL bNewPalette );
extern	SPRITE*	BackgroundSize( SBOX* pBox );
extern	void	FreeBackground( void );
extern	void	InTitleScreenLButtonDn(UINT nFlags, CPoint point);
extern	void	InTitleScreenLButtonUp(UINT nFlags, CPoint point);
extern	void	InTitleScreenMouseMove(UINT nFlags, CPoint point);
extern	BOOL	IsResource( LPTSTR id );

extern	void	ClearCheat();

//========================================================================
//						EOF
//========================================================================

