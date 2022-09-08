//========================================================================
//	FILE:			$Workfile: ScreenObj.cpp $
//
//	DESCRIPTION:	ArmyMen ScreenObj processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Wednesday, October 1, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ScreenObj.cpp 51    4/15/98 2:48a Aburgess $
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
//  $Log: /ArmyMen/src/ScreenObj.cpp $
//  
//  51    4/15/98 2:48a Aburgess
//  removed unused prototype
//  
//  50    4/09/98 4:31p Nrobinso
//  maek next mission with a different color
//  
//  48    4/03/98 4:18p Aburgess
//  modifications to fix next mission bug
//  
//  47    4/02/98 11:39p Aburgess
//  modifications to support NEXT playable mission
//  
//  46    4/02/98 6:34p Phu
//  fix boolean
//  
//  45    4/02/98 3:34p Phu
//  typecast to avoid warnings
//  
//  44    3/30/98 10:07p Nrobinso
//  turn cursor off when drawing bkgd
//  
//  43    3/26/98 10:07a Nrobinso
//  handle directories slightly differently for stats
//  
//  42    3/25/98 7:52p Nrobinso
//  remove unused
//  
//  41    3/25/98 7:37p Nrobinso
//  SObjCreate shouldn't change folders
//  
//  40    3/18/98 3:04p Nrobinso
//  switch to mp screen buttons coming from the root Screens
//  
//  39    3/17/98 11:23a Aburgess
//  SObjSetConFigColor() routine added to apply color to button names
//  
//  38    3/13/98 11:38a Nrobinso
//  stats screen data is loaded from the base screen directory
//  
//  37    3/11/98 1:17p Aburgess
//  removed debug
//  
//  36    3/11/98 11:27a Aburgess
//  modifications made to support new colorization of menus based on player
//  army color
//  
//  35    3/11/98 12:57a Nrobinso
//  only turn off cursor when needed
//  
//  34    3/01/98 11:03p Nrobinso
//  put screens in system memory
//  
//  33    2/17/98 7:52p Nrobinso
//  only load campaign.cpn
//  
//  32    2/16/98 6:28p Nrobinso
//  joystick configuration support
//  
//  31    2/13/98 12:08p Aburgess
//  modifications to ApplyOffset
//  
//  30    2/13/98 10:06a Aburgess
//  modifications made to further support keyboard configurations. Support
//  of Audio slider bar. implementation of all known buttons
//  
//  29    2/12/98 4:17p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  28    2/06/98 7:20a Aburgess
//  modifications made to support the CUSTOM configuration screen
//  
//  27    2/05/98 12:41p Aburgess
//  added capability to make SCREENOBJs invisible
//  
//  26    2/02/98 9:11a Aburgess
//  modifications made to support the non-exisitence of .RUL and _MP.BMP
//  files
//  
//  25    2/01/98 4:31p Aburgess
//  modifications made to support new ART and maps files
//  
//  24    1/26/98 12:02p Nrobinso
//  new path defines; put campaign file in it's own folder
//  
//  23    1/22/98 6:44p Nrobinso
//  use SetPath
//  
//  22    1/19/98 7:45p Aburgess
//  color table modifications
//  
//  21    1/12/98 11:12a Aburgess
//  made campaign.cpn accessed in RunTime
//  
//  20    1/12/98 10:42a Aburgess
//  changes made to look in the RUNTIME/MAPS directory for map based
//  information
//  
//  19    12/18/97 1:18p Aburgess
//  New Audio and User Configuration screens. New Scrolling buttons and
//  Slider bars
//  
//  18    12/15/97 1:13a Aburgess
//  commented out possible superfluous load completed missions call
//  
//  17    12/11/97 10:20a Aburgess
//  modified bVisible evaluation
//  
//  16    12/09/97 12:12p Phu
//  
//  15    12/04/97 9:06p Aburgess
//  modifications for Multiplayer Host/Remote screens
//  
//  14    12/01/97 9:55a Aburgess
//  update of SCREEN processing
//  
//  13    11/26/97 2:27p Aburgess
//  modifications made to support MultiPlayer Campaign Select
//  
//  12    11/20/97 11:52a Aburgess
//  modification of "most advanced" color
//  
//  11    11/20/97 11:31a Nrobinso
//  change DrawRect to FillRect function
//  
//  10    11/18/97 10:31a Aburgess
//  corrected path specifications to be relative to BASE_WORK_PATH. Added
//  class function to miscfile (cdPath) that changes based on starting from
//  BASE_WORK_PATH
//  
//  9     11/17/97 2:39p Aburgess
//  rework of Most Advanced checking
//  
//  8     11/16/97 2:20p Aburgess
//  clean up of screen, screenobj, and screenbtn
//  
//  7     11/11/97 8:56a Nrobinso
//  move screens to a Screens folder from res folder
//  
//  6     11/11/97 8:48a Aburgess
//  most recent mission button color specification
//  
//  5     11/07/97 10:32a Aburgess
//  TRANSPARENCY, ScreenObject cleanup
//  
//  4     10/27/97 12:48p Aburgess
//  corrected null text pointer problem
//  
//  3     10/27/97 10:57a Aburgess
//  Pass 1 of the new FULL SCREEN UI interface and data
//  
//  2     10/16/97 7:29a Aburgess
//  lastest version of ScreenObj and ScreenBtn
//  
//  1     10/16/97 7:03a Aburgess
//  ScreenObj: UI Full Screen object interface
//  
//  $Nokeywords:$
//========================================================================
//========================================================================

// Includes
#include "stdafx.h"
#include "comm.h"
#include "Armymen.h"
#include "MainFrm.h"
#include "GameFlow.h"
#include "gameproc.h"
#include "Dialog.h"
#include "Audio.h"
#include "Ai.h"
#include "ui.h"
#include "comm.h"
#include "miscfile.h"
#include "bmptext.h"
#include "States.h"
#include "input.h"

#include "ScreenObj.h"
#include "ScreenObj.dat"
#include "Stats.h"
#include "Screen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//================================================================
//			GLOBAL variables
//================================================================
extern	SBTN_SCRN_COLORS*	ArmyInterfaceColors[ LAST_COLOR_ARMY+1 ];
extern	char*				ArmyInterfacePaths[ LAST_COLOR_ARMY+1 ];

//================================================================
//			GLOBAL prototypes
//================================================================
extern	LONG		ScrnSelectCampaign( HSCREENBTN hScreenBtn );
extern	LONG		ScrnSelectMission( HSCREENBTN hScreenBtn );

//================================================================
//			LOCAL variables
//================================================================

HSCREENOBJ	SOBJallObjects[ SOBJ_MAX_OBJS ];
int			SOBJnextObject;
char*		SOBJFileNames[ SOBJ_MAX_FILES + 1 ];

//================================================================
//			LOCAL prototypes
//================================================================
BOOL	SObjInsertScreenBtn( HSCREENOBJ hScreenObj, HSCREENBTN hScreenBtn );
void	SObjStore( HSCREENOBJ hScreenObj );
void	SObjRemove( HSCREENOBJ hScreenObj );
BOOL	SObjSetReference( HSCREENOBJ hScreenObj, char* pScreenObjRef );
BOOL	SObjUpdateCheck( HSCREENOBJ hScreenObj );
void	SObjDisplayClear( HSCREENOBJ hScreenObj );
SBOX*	SObjDisplayBkg( HSCREENOBJ hScreenObj );
void	SObjDisplayTitle( HSCREENOBJ hScreenObj );
BOOL	SObjPointInScreenObj( HSCREENOBJ hScreenObj, SPOINT* pPoint );
int		SObjHaveSpecial( HSCREENOBJ hScreenObj, ULONG bAttributeMask );
void	SObjLoadSpecialBtns( HSCREENOBJ hScreenObj );
void	SObjMoreON( HSCREENOBJ hScreenObj );
void	SObjMoreOFF( HSCREENOBJ hScreenObj );
void	SBtnApplyOffset( HSCREENBTN hScreenBtn, SPOINT* pOffset );

//================================================================
//			SCREENOBJ Routines
//================================================================

//========================================================================
//	Function:		SObjInit()
//
//	Description:
//		Initalize the ScreenObj processing.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

BOOL	SObjInit( void )
{
	BOOL	bError = FALSE;		// assume Success

	// clear the screen object global list
	ZeroMemory( SOBJallObjects, (SOBJ_MAX_BTNS * sizeof(HSCREENOBJ) ) );
	SOBJnextObject    = 0;

	// initialize the ScreenBtn processor
	bError = SBtnInit();

	return( bError );
}

//========================================================================
//	Function:		SObjExit()
//
//	Description:
//		terminate and clear the ScreenObj processing.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	SObjExit( void )
{
	int			nObject;
	HSCREENOBJ	hScreenObj;

	// release any residual campaign data
	SObjReleaseCampaignData( );

	// terminate the ScreenBtn Processor
	SBtnExit();

	// now delete the residual objects
	for( nObject=0; nObject<SOBJnextObject; ++nObject )
	{
		hScreenObj = SOBJallObjects[ nObject ];
		if ( hScreenObj )
		{
			if ( (hScreenObj->bAttributes & SOBJ_BKG_IMAGE) == SOBJ_BKG_IMAGE )
			{
				// free the background sprite
				FreeSprite( &(hScreenObj->bkgImage.bkgSprite) );
			}

#ifdef SBTN_DEBUG
TRACE( "SObjExit:     FREE (%08x)\n", hScreenObj );
#endif
			free( hScreenObj );
			SOBJallObjects[ nObject ] = NULL;
		}
	}
}

//========================================================================
//	Function:		SObjLoad()
//
//	Description:
//		load a screen Object.
//
//	Input:			hScreenObj		screen object to be loaded
//
//	Ouput:			FALSE			if success, TRUE if error
//
//========================================================================

BOOL	SObjLoad( HSCREENOBJ hScreenObj )
{
	BOOL	bError = FALSE;		// assume Success

	return( bError );
}

//========================================================================
//	Function:		SObjFree()
//
//	Description:
//		free a screen object
//
//	Input:			hScreenObj		screen object to be freed
//
//	Ouput:			none
//
//========================================================================

void	SObjFree( HSCREENOBJ hScreenObj )
{
}

//========================================================================
//	Function:		SObjCreate()
//
//	Description:
//		Create an instance of a ScreenObj.
//
//	Input:			pPoint			Upper Lefthand coordinate of the object to
//										be created.
//					bAttributes		Attributes to be applied to this new object.
//
//	Ouput:			TRUE			if button created successfully,
//										FALSE otherwise
//
//========================================================================

HSCREENOBJ		SObjCreate( SPOINT* pPoint, ULONG bAttributes, SBOX* pParentBox )
{
	int			nColorIndex      = 0;
	char*		pScreenPath      = NULL;
	SCREENOBJ*	pScreenObject    = NULL;
	HSCREENOBJ	hNewScreenObject = NULL;
	SCRN_STATE	eScrnState;

	// acquire the players army color and set to the appropriate color directory
	nColorIndex = PlayerColor(ARMY_PLAYER);

	eScrnState = ScrnGetState();
	switch (eScrnState)	{
		case SCRN_MULTI_HOST_STATE:
		case SCRN_MULTI_REMOTE_STATE:
			nColorIndex = LAST_COLOR_ARMY;
			pScreenPath = ArmyInterfacePaths[ nColorIndex ];
			SetPath( pScreenPath );
			break;
		case SCRN_STATS_STATE:
			break;
		default:
			nColorIndex = PlayerColor(ARMY_PLAYER);
			pScreenPath = ArmyInterfacePaths[ nColorIndex ];
			SetPath( pScreenPath );
			break;
	}

//	pScreenPath = ArmyInterfacePaths[ nColorIndex ];
//	SetPath( pScreenPath );


	// now malloc a screen object
	pScreenObject = (SCREENOBJ*)malloc( sizeof(SCREENOBJ) );
	if ( pScreenObject == NULL )
	{
		// error malloc failed
		TRACE( "SObjCreate(): malloc failure [%s : %d]\n", __FILE__, __LINE__ );
		goto exit;
	}
#ifdef SBTN_DEBUG
TRACE( "SObjCreate: MALLOC (%08x)\n", pScreenObject );
#endif
	ZeroMemory( (void*)pScreenObject, sizeof( SCREENOBJ ) );

	// initialize the buttons status structure elements
	pScreenObject->bAttributes  = bAttributes;
	pScreenObject->ParentBox.x  = pParentBox->x;
	pScreenObject->ParentBox.y  = pParentBox->y;
	pScreenObject->ParentBox.cx = pParentBox->cx;
	pScreenObject->ParentBox.cy = pParentBox->cy;
	pScreenObject->bUpdate      = TRUE;
	hNewScreenObject            = pScreenObject;
	SObjSetPosition( hNewScreenObject, pPoint );

#ifdef	SCREEN_DEBUG
TRACE( "SObjCreate: ParentBox (%d,%d,%d,%d )\n",
		pScreenObject->ParentBox.x,  pScreenObject->ParentBox.y,
		pScreenObject->ParentBox.cx, pScreenObject->ParentBox.cy
	 );
#endif

	// now store the button
	SObjStore( hNewScreenObject );

exit:
	return( hNewScreenObject );
}

//========================================================================
//	Function:		SObjDelete()
//
//	Description:
//		Delete a ScreenObj instance.
//
//	Input:			hScreenObj			handle to object to be deleted
//
//	Ouput:			none
//
//========================================================================

BOOL	SObjDelete( HSCREENOBJ hScreenObj )
{
	int		nButton;
	BOOL	bError = FALSE;		// assume sucess

	if ( hScreenObj && ((hScreenObj->bAttributes & SOBJ_BKG_IMAGE) == SOBJ_BKG_IMAGE) )
	{
		// free the background sprite
		if ( *(hScreenObj->bkgImage.bkgRef) != '\0' )
			FreeSprite( &(hScreenObj->bkgImage.bkgSprite) );
	}

	// now remove all the object buttons
	for( nButton=0; nButton<hScreenObj->nNumberBtns; ++nButton )
	{
		bError = SBtnDelete( hScreenObj->hScreenBtns[ nButton ] );
		if ( bError )
			goto exit;
		else
			hScreenObj->hScreenBtns[ nButton ] = NULL;
	}

	// remove the Object
	SObjRemove( hScreenObj );

	// free the object
#ifdef SBTN_DEBUG
TRACE( "SObjDelete:     FREE (%08x)\n", hScreenObj );
#endif
	free( hScreenObj );

	SBtnResetGlobals();
exit:
	return( bError );
}

//========================================================================
//	Function:		SObjDeleteAll()
//
//	Description:
//		delete all the screenobjects.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	SObjDeleteAll( void )
{
	HSCREENOBJ	hScreenObj;

	while ( SOBJnextObject )
	{
		hScreenObj = SOBJallObjects[ 0 ];
		if ( hScreenObj )
			SObjDelete( hScreenObj );
	}
}

//========================================================================
//				BUTTON ACCESS ROUTINES
//========================================================================

BOOL	SObjSetAttributes( HSCREENOBJ hScreenObj, ULONG bAttributes )
{
	ASSERT ( hScreenObj );

	if ( bAttributes )
		hScreenObj->bAttributes |= bAttributes;
	else
		hScreenObj->bAttributes = SOBJ_CLEAR;

	return( FALSE );	// no error
}

BOOL	SObjClearAttributes( HSCREENOBJ hScreenObj, ULONG bAttributes )
{
	ASSERT ( hScreenObj );

	if ( bAttributes )
		hScreenObj->bAttributes &= ~bAttributes;

	return( FALSE );	// no error
}

ULONG	SObjGetAttributes( HSCREENOBJ hScreenObj )
{
	ASSERT ( hScreenObj );

	return( hScreenObj->bAttributes );
}

BOOL	SObjHaveAttributes( HSCREENOBJ hScreenObj, ULONG bAttributesMask )
{
	BOOL	bHaveThem = FALSE;

	ASSERT ( hScreenObj );

	if ( bAttributesMask )
	{
		if ( (hScreenObj->bAttributes & bAttributesMask) == bAttributesMask )
			bHaveThem = TRUE;
	}
	else
	if ( hScreenObj->bAttributes == SOBJ_CLEAR )	// bAttributesMask = 0 = SOBJ_CLEAR
		bHaveThem = TRUE;

	return( bHaveThem );
}

BOOL	SObjSetPosition( HSCREENOBJ hScreenObj, SPOINT* pPosition )
{
	ASSERT( hScreenObj );
	ASSERT( pPosition );

	hScreenObj->position.x   = pPosition->x;
	hScreenObj->position.y   = pPosition->y;

	return( FALSE );	// no error
}

SPOINT*	SObjGetPosition( HSCREENOBJ hScreenObj )
{
	ASSERT( hScreenObj );

	return( &(hScreenObj->position) );
}

BOOL	SObjSetTitle( HSCREENOBJ hScreenObj, char* pText )
{
	SBOX	textBox;
	char*	pReference;
	int		len = 0;
	BOOL	bError = TRUE;		// assume failure

	ASSERT( hScreenObj );
	ASSERT ( ((hScreenObj->bAttributes & SOBJ_HAS_TITLE) == SOBJ_HAS_TITLE) );

	if ( pText == NULL )
	{
		bError = FALSE;
		goto exit;
	}

	len = strlen( pText );
	if ( len > SOBJ_MAX_TEXT_LEN )
		len = SOBJ_MAX_TEXT_LEN;

	if ( IsResource( pText ) )
	{
		// now assign the resource ID
		hScreenObj->title.titleResourceID = (LPTSTR)pText;

		if ( !LoadString( ghinst, (unsigned)(hScreenObj->title.titleResourceID),
						  hScreenObj->title.titleRef, SOBJ_MAX_REF_LEN ) )
		{
			// error: failed to load object title text
			TRACE( "ERROR: failed to load screenobj title text resource [%s : %d]\n"
					__FILE__, __LINE__ );
			goto exit;
		}
	}
	else
	{
		if ( len )
			strcpy(hScreenObj->title.titleRef, pText);
		hScreenObj->title.titleRef[len] = '\0';
	}

	// see if we need to center the title horizontally
	if ( (hScreenObj->bAttributes & SOBJ_TITLE_CENTER) == SOBJ_TITLE_CENTER )
	{
		// acquire the area for this icon
		pReference = hScreenObj->title.titleRef;
		textBox.x  = 0;
		textBox.y  = 0;
		if ( TextBox( pReference, &textBox, hScreenObj->title.titleFontID ) )
		{
			// error: failed to acquire text box size
			TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
					__FILE__, __LINE__ );
			goto exit;
		}

		// now center (horizontally) the text
		hScreenObj->title.titlePosition.x = hScreenObj->position.x + ((hScreenObj->bkgArea.bkgBox.cx - textBox.cx)>>1);
	}

	hScreenObj->bUpdate = TRUE;
	bError              = FALSE;

exit:
	return( bError );	// no error
}

char*	SObjGetTitle( HSCREENOBJ hScreenObj )
{
	ASSERT ( hScreenObj );

	return( hScreenObj->title.titleRef );
}

BOOL	SObjSetTitlePosition( HSCREENOBJ hScreenObj, SPOINT* pPosition )
{
	ASSERT( hScreenObj );
	ASSERT( pPosition );

	hScreenObj->title.titlePosition.x   = hScreenObj->position.x + pPosition->x;
	hScreenObj->title.titlePosition.y   = hScreenObj->position.y + pPosition->y;

	return( FALSE );	// no error
}

SPOINT*	SObjGetTitlePosition( HSCREENOBJ hScreenObj )
{
	ASSERT( hScreenObj );

	return( &(hScreenObj->title.titlePosition) );
}

BOOL	SObjSetTitleFont( HSCREENOBJ hScreenObj, LONG nFontID )
{
	ASSERT ( hScreenObj );

	hScreenObj->title.titleFontID = nFontID;

	return( FALSE );	// no error
}

LONG	SObjGetTitleFont( HSCREENOBJ hScreenObj )
{
	ASSERT ( hScreenObj );

	return( hScreenObj->title.titleFontID );
}

BOOL	SObjSetTitleBGColor( HSCREENOBJ hScreenObj, SOBJ_COLOR bgColor )
{
	ASSERT( hScreenObj );
	ASSERT ( ((hScreenObj->bAttributes & SOBJ_HAS_TITLE) == SOBJ_HAS_TITLE) );

	hScreenObj->title.titleBGColor = bgColor;

	return( FALSE );
}

SOBJ_COLOR	SObjGetTitleBGColor( HSCREENOBJ hScreenObj )
{
	ASSERT( hScreenObj );
	ASSERT ( ((hScreenObj->bAttributes & SOBJ_HAS_TITLE) == SOBJ_HAS_TITLE) );

	return( hScreenObj->title.titleBGColor );
}

BOOL	SObjSetTitleFGColor( HSCREENOBJ hScreenObj, SOBJ_COLOR fgColor )
{
	ASSERT( hScreenObj );
	ASSERT ( ((hScreenObj->bAttributes & SOBJ_HAS_TITLE) == SOBJ_HAS_TITLE) );

	hScreenObj->title.titleFGColor = fgColor;

	return( FALSE );
}

SOBJ_COLOR	SObjGetTitleFGColor( HSCREENOBJ hScreenObj )
{
	ASSERT( hScreenObj );
	ASSERT ( ((hScreenObj->bAttributes & SOBJ_HAS_TITLE) == SOBJ_HAS_TITLE) );

	return( hScreenObj->title.titleFGColor );
}

BOOL	SObjSetBkg( HSCREENOBJ hScreenObj, SCREENOBJDEF* pScreenObjDef )
{
	BOOL	bError = TRUE;			// assume an error

	ASSERT ( hScreenObj );

	if ( ((hScreenObj->bAttributes & SOBJ_BKG_IMAGE) == SOBJ_BKG_IMAGE) )
		bError = SObjSetBkgImage(hScreenObj, pScreenObjDef->pBkgImage);
	else
	if ( ((hScreenObj->bAttributes & SOBJ_BKG_AREA) == SOBJ_BKG_AREA) )
		bError = SObjSetBkgArea(hScreenObj, pScreenObjDef->pBkgArea );
	else
		ASSERT(0);

	bError = FALSE;

	return( bError );
}

BOOL	SObjSetBkgImage( HSCREENOBJ hScreenObj, SOBJIMAGEDEF* pImage )
{
	BOOL	bError = TRUE;

	ASSERT ( hScreenObj );
	ASSERT ( ((hScreenObj->bAttributes & SOBJ_BKG_IMAGE) == SOBJ_BKG_IMAGE) );

	if ( *(pImage->bkgRef) != '\0' )
		bError = SObjSetReference( hScreenObj, pImage->bkgRef );
	else
		bError = FALSE;

	return( bError );
}

SPRITE*	SObjGetBkgImage( HSCREENOBJ hScreenObj )
{
	SPRITE*	pSprite;

	ASSERT( hScreenObj );
	ASSERT ( ((hScreenObj->bAttributes & SOBJ_BKG_IMAGE) == SOBJ_BKG_IMAGE) );

	pSprite = &(hScreenObj->bkgImage.bkgSprite);

	return( pSprite );
}

BOOL	SObjSetBkgArea( HSCREENOBJ hScreenObj, SOBJAREA* pArea )
{
	BOOL	bError = TRUE;			// assume an error
	SBOX*	pBox   = NULL;

	ASSERT ( hScreenObj );

	hScreenObj->bkgArea.bkgBox.x      = pArea->bkgBox.x;
	hScreenObj->bkgArea.bkgBox.y      = pArea->bkgBox.y;
	hScreenObj->bkgArea.bkgBox.cx     = pArea->bkgBox.cx;
	hScreenObj->bkgArea.bkgBox.cy     = pArea->bkgBox.cy;
	if ( ((hScreenObj->bAttributes & SOBJ_BKG_TRANS) != SOBJ_BKG_TRANS) )
	{
		hScreenObj->bkgArea.bkgColor      = pArea->bkgColor;	// bkg color to fill with
		hScreenObj->bkgArea.bkgShadeTable = pArea->bkgShadeTable;// translucent shading table pionter
	}

	bError = FALSE;

	return( bError );
}

SBOX*	SObjGetBkgArea( HSCREENOBJ hScreenObj )
{
	SBOX*	pBox   = NULL;

	ASSERT ( hScreenObj );

	if ( ((hScreenObj->bAttributes & SOBJ_BKG_IMAGE) == SOBJ_BKG_IMAGE) )
		pBox =  &(hScreenObj->bkgImage.bkgBox);
	else
	if ( ((hScreenObj->bAttributes & SOBJ_BKG_AREA) == SOBJ_BKG_AREA) )
		pBox =  &(hScreenObj->bkgArea.bkgBox);
	else
		ASSERT(0);

	return( pBox );
}

BOOL	SObjSetBkgColor( HSCREENOBJ hScreenObj, SOBJ_COLOR eColor )
{
	ASSERT( hScreenObj );
	ASSERT( ((hScreenObj->bAttributes & SOBJ_BKG_AREA) == SOBJ_BKG_AREA) );

	hScreenObj->bkgArea.bkgColor = eColor;

	return( FALSE );
}

SOBJ_COLOR	SObjGetBkgColor( HSCREENOBJ hScreenObj )
{
	ASSERT( hScreenObj );
	ASSERT( ((hScreenObj->bAttributes & SOBJ_BKG_AREA) == SOBJ_BKG_AREA) );

	return( hScreenObj->bkgArea.bkgColor );
}

BOOL	SObjSetShadeTable( HSCREENOBJ hScreenObj, BYTE* pShadeTable )
{
	ASSERT( hScreenObj );
	ASSERT( ((hScreenObj->bAttributes & SOBJ_BKG_AREA) == SOBJ_BKG_AREA) );

	hScreenObj->bkgArea.bkgShadeTable = pShadeTable;

	return( FALSE );
}

BYTE*	SObjBkgShadeTable( HSCREENOBJ hScreenObj )
{
	ASSERT( hScreenObj );
	ASSERT( ((hScreenObj->bAttributes & SOBJ_BKG_AREA) == SOBJ_BKG_AREA) );

	return( hScreenObj->bkgArea.bkgShadeTable );
}

//========================================================================
//					SCREENBTN UTILITY ROUTINES
//========================================================================

BOOL	SObjUpdate( HSCREENOBJ hScreenObj )
{
	HSCREENBTN	hScreenBtn;
	int			nButton;
	BOOL		bStateChange;

	nButton      = 0;
	bStateChange = FALSE;
	while( !bStateChange && (nButton<hScreenObj->nNumberBtns) )
	{
		hScreenBtn = hScreenObj->hScreenBtns[ nButton ];
		if ( hScreenBtn )
			bStateChange = SBtnUpdate( hScreenBtn );
		++nButton;
	}

	return( bStateChange );
}

void	SObjResetAll( void )
{
	HSCREENOBJ	hObject;
	int			nObject;
	int			nButton;

	// call a reset on each active screenobj
	for( nObject=0; nObject<SOBJnextObject; ++nObject )
	{
		hObject = SOBJallObjects[ nObject ];

		// check each screenbtn in this screenobj
		for ( nButton=0; nButton<(hObject->nNumberBtns); ++nButton )
			SBtnReset( hObject->hScreenBtns[nButton] );
	}
}

void	SObjReset( HSCREENOBJ hObject )
{
	int			nButton;

	// check each screenbtn in this screenobj
	for ( nButton=0; nButton<(hObject->nNumberBtns); ++nButton )
		SBtnReset( hObject->hScreenBtns[nButton] );
}

void	SObjUpdateObject( SPOINT* pPoint )
{
	HSCREENOBJ	hScreenObj = NULL;
	HSCREENBTN	hScreenBtn = NULL;
	int			nButton;

	hScreenObj = SObjIsInObject( pPoint );
	if ( hScreenObj )
	{
		hScreenObj->bUpdate = TRUE;

		for( nButton=0; nButton<hScreenObj->nNumberBtns; ++nButton )
		{
			hScreenBtn = hScreenObj->hScreenBtns[ nButton ];
			if ( hScreenBtn )
				hScreenBtn->bUpdate = TRUE;
		}
	}
}

HSCREENOBJ	SObjIsInObject( SPOINT* pPoint )
{
	int			nScreenObj;
	BOOL		bFound;
	HSCREENOBJ	hScreenObj = NULL;

	// check all the screenobjs
	bFound  = FALSE;
	nScreenObj = 0;
	while ( !bFound && ( nScreenObj < SOBJnextObject ) )
	{
		if ( SObjPointInScreenObj( SOBJallObjects[ nScreenObj ], pPoint ) )
			bFound = TRUE;
		else
			++nScreenObj;
	}
	if ( bFound )
		hScreenObj = SOBJallObjects[ nScreenObj ];

	return ( hScreenObj );
}

BOOL	SObjInEditMode( HSCREENOBJ hScreenObj )
{
	int			nButton;
	HSCREENBTN	hScreenBtn;
	BOOL		bInEditMode = FALSE;

	if ( hScreenObj )
	{
		nButton     = 0;
		bInEditMode = FALSE;
		while ( !bInEditMode && (nButton<hScreenObj->nNumberBtns) )
		{
			hScreenBtn  = hScreenObj->hScreenBtns[ nButton ];
			bInEditMode = SBtnInEditMode( hScreenBtn );
			++nButton;
		}
	}

	return( bInEditMode );
}
	
//========================================================================
//					SCREENBTN LOCAL ROUTINES
//========================================================================

BOOL	SObjInsertScreenBtn( HSCREENOBJ hScreenObj, HSCREENBTN hScreenBtn )
{
	BOOL	bError = TRUE;		// assume an error

	ASSERT( hScreenObj );
	ASSERT( hScreenBtn );

	// make sure we aren't full already
	if ( (hScreenObj->nNumberBtns) >= SOBJ_MAX_BTNS )
	{
		TRACE( "ERROR: max screenBtn limit (SOBJ_MAX_BTNS=%d) exceeded\n",
				SOBJ_MAX_BTNS );
		ASSERT(0);
	}

#ifdef	SBTN_DEBUG
	SBtnDump( hScreenBtn );
#endif

	// insert the button
	hScreenObj->hScreenBtns[ hScreenObj->nNumberBtns ] = hScreenBtn;
	++(hScreenObj->nNumberBtns);

	// make sure this object and this button get displayed
	hScreenObj->bUpdate = TRUE;
	hScreenBtn->bUpdate = TRUE;

	// we were successful
	bError = FALSE;

	return( bError );
}

void	SObjStore( HSCREENOBJ hScreenObj )
{
	if ( SOBJnextObject >= SOBJ_MAX_OBJS )
	{
		TRACE( "ERROR: max screenObj limit (SOBJ_MAX_OBJS=%d) exceeded\n",
				SOBJ_MAX_OBJS );
		ASSERT(0);
	}
	SOBJallObjects[ SOBJnextObject ] = hScreenObj;
	++SOBJnextObject;
}

void	SObjRemove( HSCREENOBJ hScreenObj )
{
	BOOL	bFound;
	int		nObject;
	int		nObject2;

	bFound  = FALSE;
	nObject = 0;
	while( !bFound && (nObject<SOBJnextObject) )
	{
		if ( SOBJallObjects[ nObject ] == hScreenObj )
			bFound = TRUE;
		else
			++nObject;
	}
	if ( bFound )
	{
		// clear this entry
		SOBJallObjects[ nObject ] = NULL;

		// Compress the list
		for( nObject2=nObject; nObject2<(SOBJnextObject-1); ++nObject2 )
			SOBJallObjects[ nObject2 ] = SOBJallObjects[ nObject2+1 ];
		SOBJallObjects[ SOBJnextObject-1 ] = NULL;

		// reduce the count
		--SOBJnextObject;
	}
}

BOOL	SObjSetReference( HSCREENOBJ hScreenObj, char* pScreenObjRef )
{
	SPRITE*	pSprite;
	LPTSTR*	pRefResource;
	SBOX*	pBox;
	LONG	bSpriteFlags;
	char*	pReference;
	int		len = 0;
	BOOL	bError = TRUE;

	ASSERT( hScreenObj );
	ASSERT( pScreenObjRef );
	ASSERT ( ((hScreenObj->bAttributes & SOBJ_BKG_IMAGE) == SOBJ_BKG_IMAGE) );

	// first thing we need to do is acquire the proper SOBJ_STATE based
	// structure elements
	pReference   = hScreenObj->bkgImage.bkgRef;
	pRefResource = &(hScreenObj->bkgImage.bkgResourceID);
	pSprite      = &(hScreenObj->bkgImage.bkgSprite);
	pBox         = &(hScreenObj->bkgImage.bkgBox);

	if ( (hScreenObj->bAttributes & SOBJ_BKG_TRANS) == SOBJ_BKG_TRANS )
		bSpriteFlags = BM_TRANSPARENT|BM_SYSTEMMEMORY;
	else
		bSpriteFlags = BM_OPAQUE|BM_SYSTEMMEMORY;

	// if this is an ICON button, free up the sprite
	if ( pReference && *pReference )
	{
		FreeSprite( pSprite );
		*pReference     = '\0';
	}

	if ( !pScreenObjRef )	// asked to clear button reference
		goto success;

	len = strlen( pScreenObjRef );
	if ( len > SOBJ_MAX_TEXT_LEN )
		len = SOBJ_MAX_TEXT_LEN;
	if ( len )
		strcpy(pReference, pScreenObjRef);
	pReference[len] = '\0';

	if ( IsResource( (LPTSTR)pScreenObjRef ) )
	{
		// clear the image filename reference
		pReference[len] = '\0';

		// now assign the resource ID
		*pRefResource = (LPTSTR)pScreenObjRef;

		if ( !LoadSprite( pSprite, *pRefResource, bSpriteFlags ) )
		{
			// error: failed to load button icon
			TRACE( "ERROR: failed to load button icon resource [%s : %d]\n"
					__FILE__, __LINE__ );
			goto exit;
		}

		// acquire the area for this icon
		if ( SpriteBox( pSprite, pBox ) )
		{
			// error: failed to acquire icon size
			TRACE( "ERROR: failed to acquire icon size [%s : %d]\n",
					__FILE__, __LINE__ );
			goto exit;
		}
	}
	else
	{
		// clear the resource reference
		*pRefResource = NULL;

		if ( !LoadSprite( pSprite, pReference, bSpriteFlags ) )
		{
			if ( !LoadSprite( pSprite, "default_mp.BMP", bSpriteFlags ) )
			{
				// error: failed to load button image
				TRACE( "ERROR: failed to load image file (%s) [%s : %d]\n",
						pReference, __FILE__, __LINE__);
				goto exit;
			}
		}

		// acquire the area for this icon
		if ( SpriteBox( pSprite, pBox ) )
		{
			// error: failed to acquire icon size
			TRACE( "ERROR: failed to acquire icon size [%s : %d]\n",
					__FILE__, __LINE__);
			goto exit;
		}
	}

success:
	bError           = FALSE;
	hScreenObj->bUpdate = TRUE;

exit:
	return( bError );	// no error
}

BOOL	SObjUpdateCheck( HSCREENOBJ hScreenObj )
{
	ASSERT( hScreenObj );

	return( hScreenObj->bUpdate );
}

void	SObjDisplay( HSCREENOBJ hScreenObj )
{
	HSCREENBTN	hScreenBtn;
	RECT		Rect;
	SBOX*		pBox;
	int			nButton;

	ASSERT( hScreenObj );

	if ( ((hScreenObj->bAttributes & SOBJ_INVISIBLE) != SOBJ_INVISIBLE) )
	{
		// start by displaying the background and get the box for this object
		pBox = SObjDisplayBkg( hScreenObj );

		// create an object rectangle
		Rect.left   = hScreenObj->ParentBox.x + hScreenObj->position.x + pBox->x;
		Rect.top    = hScreenObj->ParentBox.y + hScreenObj->position.y + pBox->y;
		Rect.right  = Rect.left + pBox->cx;
		Rect.bottom = Rect.top + pBox->cy;

		// check to see of there is an object title string
		if ( hScreenObj->bUpdate )
		{
			CursorOff( &Rect );
			if ( ((hScreenObj->bAttributes & SOBJ_INVISIBLE) != SOBJ_INVISIBLE) )
				SObjDisplayTitle( hScreenObj );
		}

		// now display all the normal buttons in this object
		for( nButton=0; nButton<hScreenObj->nNumberBtns; ++nButton )
		{
			hScreenBtn = hScreenObj->hScreenBtns[ nButton ];
			if ( hScreenBtn )
			{
				if ( hScreenBtn->bUpdate )
					SBtnDisplay( hScreenBtn );
			}
		}
	}

	// clear the button update flag: button updated
	hScreenObj->bUpdate = FALSE;
}

void	SObjDisplayClear( HSCREENOBJ hScreenObj )
{
}

SBOX*	SObjDisplayBkg( HSCREENOBJ hScreenObj )
{
	SOBJ_COLOR	bkgColor;
	COLORREF	rgbColor;
	RECT		Rect;
	char*		pScreenObjRef;
	SPRITE*		pScreenObjIcon;
	SBOX*		pBox = NULL;

	ASSERT( hScreenObj );

	// get the display box for this button
	if ((hScreenObj->bAttributes & SOBJ_BKG_IMAGE) == SOBJ_BKG_IMAGE)
	{
		// acquire the image data
		pBox = &(hScreenObj->bkgImage.bkgBox);
		if ( hScreenObj->bUpdate )
		{
			pScreenObjRef  = hScreenObj->bkgImage.bkgRef;
			pScreenObjIcon = &(hScreenObj->bkgImage.bkgSprite);

#ifdef	SCREEN_DEBUG
TRACE( "SObjDisplayBkg: IMAGE position (%d,%d) ImageBox (%d,%d,%d,%d ) ParentBox(%d,%d,%d,%d)\n",
		hScreenObj->position.x,         hScreenObj->position.y,
		hScreenObj->bkgImage.bkgBox.x,  hScreenObj->bkgImage.bkgBox.y,
		hScreenObj->bkgImage.bkgBox.cx, hScreenObj->bkgImage.bkgBox.cy,
		hScreenObj->ParentBox.x,        hScreenObj->ParentBox.y,
		hScreenObj->ParentBox.cx,       hScreenObj->ParentBox.cy
	 );
#endif
			// create the object rectangle
			Rect.left   = hScreenObj->ParentBox.x + hScreenObj->position.x + pBox->x;
			Rect.top    = hScreenObj->ParentBox.y + hScreenObj->position.y + pBox->y;
			Rect.right  = Rect.left + pBox->cx;
			Rect.bottom = Rect.top + pBox->cy;

			CursorOff( &Rect );

#ifdef	SCREEN_DEBUG
TRACE( "SCREENBTN: Rect (%d,%d,%d,%d)\n",
	   Rect.left,  Rect.top, Rect.right, Rect.bottom
	 );
#endif

			// draw the image
			DisplaySpriteFront( pScreenObjIcon, Rect.left, Rect.top );
		}
	}
	else
	if ((hScreenObj->bAttributes & SOBJ_BKG_IMAGE) != SOBJ_BKG_IMAGE)
	{
		pBox        = &(hScreenObj->bkgArea.bkgBox);

		if ( hScreenObj->bUpdate && ((hScreenObj->bAttributes & SOBJ_BKG_TRANS) != SOBJ_BKG_TRANS) )
		{

#ifdef	SCREEN_DEBUG
TRACE( "SObjDisplayBkg: AREA position (%d,%d) ImageBox (%d,%d,%d,%d ) ParentBox(%d,%d,%d,%d)\n",
		hScreenObj->position.x,         hScreenObj->position.y,
		hScreenObj->bkgArea.bkgBox.x,   hScreenObj->bkgArea.bkgBox.y,
		hScreenObj->bkgArea.bkgBox.cx,  hScreenObj->bkgArea.bkgBox.cy,
		hScreenObj->ParentBox.x,        hScreenObj->ParentBox.y,
		hScreenObj->ParentBox.cx,       hScreenObj->ParentBox.cy
	 );
#endif

			// create the object rectangle
			Rect.left   = hScreenObj->ParentBox.x + hScreenObj->position.x + pBox->x;
			Rect.top    = hScreenObj->ParentBox.y + hScreenObj->position.y + pBox->y;
			Rect.right  = Rect.left + pBox->cx;
			Rect.bottom = Rect.top + pBox->cy;

#ifdef	SCREEN_DEBUG
TRACE( "SCREENOBJ: Rect (%d,%d,%d,%d)\n",
	   Rect.left,  Rect.top, Rect.right, Rect.bottom
	 );
#endif

			// now acquire the rectangle color
			bkgColor = hScreenObj->bkgArea.bkgColor;
			rgbColor = SBTNcolorTable[bkgColor];

			// draw the rectangle (opaque, translucent, or transparent)
			if ((hScreenObj->bAttributes & SOBJ_BKG_OPAQUE) == SOBJ_BKG_OPAQUE)
				FillRectFront( &Rect, rgbColor );	// filled rectangle
			else
			if ( (hScreenObj->bAttributes & SOBJ_BKG_TRANS) != SOBJ_BKG_TRANS )
				FillTransRectFront( &Rect, hScreenObj->bkgArea.bkgShadeTable );	// translucent no transparent rectangle
		}
	}
#ifdef _DEBUG
	else
		ASSERT(0);
#endif

	// return the box
	return( pBox );
}

void	SObjDisplayTitle( HSCREENOBJ hScreenObj )
{
	char*		pTitleRef;
	SOBJ_COLOR	bgColor;
	COLORREF	rgbBGColor;
	SOBJ_COLOR	fgColor;
	COLORREF	rgbFGColor;
	RECT		Rect;

	// acquire the title data
	pTitleRef = hScreenObj->title.titleRef;
	if ( pTitleRef[0] != '\0' )
	{
#ifdef	SCREEN_DEBUG
TRACE( "SCREENOBJ (%s)title: position (%d,%d) AreaBox (%d,%d,%d,%d ) ParentBox(%d,%d,%d,%d)\n",
	    hScreenObj->title.titleRef,
		hScreenObj->position.x,        hScreenObj->position.y,
		hScreenObj->bkgArea.bkgBox.x,  hScreenObj->bkgArea.bkgBox.y,
		hScreenObj->bkgArea.bkgBox.cx, hScreenObj->bkgArea.bkgBox.cy,
		hScreenObj->ParentBox.x,       hScreenObj->ParentBox.y,
		hScreenObj->ParentBox.cx,      hScreenObj->ParentBox.cy
	 );
#endif

		// create the object rectangle
		Rect.left   = hScreenObj->ParentBox.x + hScreenObj->bkgArea.bkgBox.x + hScreenObj->title.titlePosition.x;
		Rect.top    = hScreenObj->ParentBox.y + hScreenObj->bkgArea.bkgBox.y + hScreenObj->title.titlePosition.y;
		Rect.right  = Rect.left + hScreenObj->bkgArea.bkgBox.cx;
		Rect.bottom = Rect.top + hScreenObj->bkgArea.bkgBox.cy;

		// acquire  and set the foreground and background text colors
		bgColor    = hScreenObj->title.titleBGColor;
		rgbBGColor = SBTNcolorTable[bgColor];

		fgColor    = hScreenObj->title.titleFGColor;
		rgbFGColor = SBTNcolorTable[fgColor];

		if ( bgColor == SBTN_TRANSPARENT )
			TextSetTransparent( TRUE );
		else
			TextSetTransparent( FALSE );
		TextSetColors( rgbFGColor, rgbBGColor );

		// now draw the text
		TextWrite(	pFrontBuffer,
					Rect.left + rcWindowScreen.left,
					Rect.top + rcWindowScreen.top,
					pTitleRef, hScreenObj->title.titleFontID, NULL );
	}
}

BOOL	SObjPointInScreenObj( HSCREENOBJ hScreenObj, SPOINT* pPoint )
{
	SBOX*		pBox;
	SHORT		x1,y1,x2,y2;
	BOOL		bInArea = FALSE;

	ASSERT( hScreenObj );
	ASSERT( pPoint );

	if ((hScreenObj->bAttributes & SOBJ_BKG_IMAGE) == SOBJ_BKG_IMAGE)
		pBox = &(hScreenObj->bkgImage.bkgBox);
	else
	if ((hScreenObj->bAttributes & SOBJ_BKG_AREA) == SOBJ_BKG_AREA)
		pBox = &(hScreenObj->bkgArea.bkgBox);
#ifdef _DEBUG
	else
		ASSERT(0);
#endif

	x1 = hScreenObj->ParentBox.x + hScreenObj->position.x + pBox->x;
	y1 = hScreenObj->ParentBox.y + hScreenObj->position.y + pBox->y;
	x2 = x1 + pBox->cx;
	y2 = y1 + pBox->cy;
	if ( (pPoint->x >= x1) && (pPoint->x < x2) )
		if ( (pPoint->y >= y1) && (pPoint->y < y2) )
			bInArea = TRUE;

	return( bInArea );
}

int	SObjHaveSpecial( HSCREENOBJ hScreenObj, ULONG bAttributeMask )
{
	int	bIsSpecial = -1;		// assume not a special button

	if ( (hScreenObj->bAttributes & bAttributeMask) == SOBJ_SPCL_OK )
		bIsSpecial = SBTN_OK;
	else
	if ( (hScreenObj->bAttributes & bAttributeMask) == SOBJ_SPCL_CANCEL )
		bIsSpecial = SBTN_CANCEL;
	else
	if ( (hScreenObj->bAttributes & bAttributeMask) == SOBJ_SPCL_NEXT )
		bIsSpecial = SBTN_NEXT;
	else
	if ( (hScreenObj->bAttributes & bAttributeMask) == SOBJ_SPCL_BACK )
		bIsSpecial = SBTN_BACK;
	else
	if ( (hScreenObj->bAttributes & bAttributeMask) == SOBJ_SPCL_FINISH )
		bIsSpecial = SBTN_FINISH;

	return( bIsSpecial );
}

void	SObjLoadSpecialBtns( HSCREENOBJ hScreenObj )
{
	int				nSpecialBtn;
	HSCREENBTN		hScreenBtn;

	nSpecialBtn = SObjHaveSpecial( hScreenObj, SOBJ_SPCL_OK );
	if ( nSpecialBtn != -1 )
	{
		hScreenBtn = SBTNspecialScreenBtns[ nSpecialBtn ];
		SObjInsertScreenBtn( hScreenObj, hScreenBtn );
	}

	nSpecialBtn = SObjHaveSpecial( hScreenObj, SOBJ_SPCL_CANCEL );
	if ( nSpecialBtn != -1 )
	{
		hScreenBtn = SBTNspecialScreenBtns[ nSpecialBtn ];
		SObjInsertScreenBtn( hScreenObj, SBTNspecialScreenBtns[ nSpecialBtn ] );
	}

	nSpecialBtn = SObjHaveSpecial( hScreenObj, SOBJ_SPCL_NEXT );
	if ( nSpecialBtn != -1 )
	{
		hScreenBtn = SBTNspecialScreenBtns[ nSpecialBtn ];
		SObjInsertScreenBtn( hScreenObj, SBTNspecialScreenBtns[ nSpecialBtn ] );
	}

	nSpecialBtn = SObjHaveSpecial( hScreenObj, SOBJ_SPCL_BACK );
	if ( nSpecialBtn != -1 )
	{
		hScreenBtn = SBTNspecialScreenBtns[ nSpecialBtn ];
		SObjInsertScreenBtn( hScreenObj, SBTNspecialScreenBtns[ nSpecialBtn ] );
	}

	nSpecialBtn = SObjHaveSpecial( hScreenObj, SOBJ_SPCL_FINISH );
	if ( nSpecialBtn != -1 )
	{
		hScreenBtn = SBTNspecialScreenBtns[ nSpecialBtn ];
		SObjInsertScreenBtn( hScreenObj, SBTNspecialScreenBtns[ nSpecialBtn ] );
	}
}

void	SObjLoadDef( HSCREENOBJ hScreenObj, SCREENOBJDEF* pScreenObjDef )
{
	HSCREENBTN	hScreenBtn;
	SBOX		buttonBox;
	SBOX*		pObjectBox;
	int			nButton;

	SObjSetBkg( hScreenObj, pScreenObjDef );

	// check for a title
	if ( ( hScreenObj->bAttributes & SOBJ_HAS_TITLE) == SOBJ_HAS_TITLE )
		SObjLoadTitle( hScreenObj, pScreenObjDef->pTitle );

	// now load up the buttons
	for( nButton=0; nButton<pScreenObjDef->nNumberBtns; ++nButton )
	{
		// build the button box
		pObjectBox   = &(hScreenObj->bkgImage.bkgBox);
		buttonBox.x  = hScreenObj->ParentBox.x + hScreenObj->position.x;
		buttonBox.y  = hScreenObj->ParentBox.y + hScreenObj->position.y;
		buttonBox.cx = pObjectBox->cx;
		buttonBox.cy = pObjectBox->cy;
		hScreenBtn = SBtnLoadDef( pScreenObjDef->pScreenBtnDefs[ nButton ], &buttonBox );
		if( hScreenBtn );
			SObjInsertScreenBtn( hScreenObj, hScreenBtn );
	}

//	SObjLoadSpecialBtns( hScreenObj );

	hScreenObj->bUpdate = TRUE;
}

void	SObjLoadTitle( HSCREENOBJ hScreenObj, SOBJTITLEDEF* pScreenTitle )
{
	SBTN_SCRN_COLORS*	pArmyColors;
	int					nColorIndex;
	SCRN_STATE			eScrnState;

	// acquire the players army colors
	eScrnState = ScrnGetState();
	if ( (eScrnState == SCRN_MULTI_HOST_STATE) || (eScrnState == SCRN_MULTI_REMOTE_STATE) )
		nColorIndex = LAST_COLOR_ARMY;
	else
		nColorIndex = PlayerColor(ARMY_PLAYER);
	pArmyColors = ArmyInterfaceColors[ nColorIndex ];

	SObjSetTitlePosition( hScreenObj, &(pScreenTitle->titlePosition) );
	SObjSetTitleFont( hScreenObj, pScreenTitle->titleFontID );
	SObjSetTitleBGColor( hScreenObj, SBTN_TRANSPARENT );
	SObjSetTitleFGColor( hScreenObj, pArmyColors->TitleColor );
	SObjSetTitle( hScreenObj, pScreenTitle->titleRef );

	hScreenObj->bUpdate = TRUE;
}

void SObjSetConFigColor( HSCREENBTN hScreenBtn, BOOL bPlayerColor )
{
	int					nKeyIndex;
	DWORD				dwData;							// button user data
	BOOL				bGameKey;
	HSCREENOBJ			hScreenObj;
	SBTN_SCRN_COLORS*	pArmyColors;
	int					nColorIndex;

	// acquire the players army colors
	nColorIndex = PlayerColor(ARMY_PLAYER);
	pArmyColors = ArmyInterfaceColors[ nColorIndex ];

	// acquire the screen object and change the title text
	dwData = hScreenBtn->dwData;
	if ( (dwData & GAME_KEY_FLAG) )		// GamePlayKeycodes
		bGameKey = TRUE;
	else
		bGameKey = FALSE;
	nKeyIndex = (dwData & 0xFF);

	// set the title color
	if ( bGameKey )
		hScreenObj = SCRNfullScreen->pScreenObjs[ (GAME_KEY_START_INDEX + nKeyIndex) ];
	else
		hScreenObj = SCRNfullScreen->pScreenObjs[ (SARGE_KEY_START_INDEX + nKeyIndex) ];
	if ( hScreenObj )
	{
		if ( bPlayerColor )
			SObjSetTitleFGColor( hScreenObj, pArmyColors->TitleColor );
		else
			SObjSetTitleFGColor( hScreenObj, pArmyColors->ClickedColor );
		hScreenObj->bUpdate = TRUE;
	}
}

//================================================================
//					SUPPORT FUNCTIONS
//================================================================

int	SObjCampaignInit( HSCREENOBJ hScreenObj ) 
{
	char**		pFileNames;
	int			nIndex;

	// clear the filenames list and initialize
	for ( nIndex=0;nIndex<DLG_MAX_FILES; ++nIndex )
		SOBJFileNames[ nIndex ] = NULL;
	pFileNames = SOBJFileNames;
    nIndex = SObjEnumerateCampaigns( hScreenObj );

	return( nIndex );
}

void	SObjReleaseCampaignData( void )
{
    int index;

	index = 0;
	for ( index=0;index<DLG_MAX_FILES; ++index )
	{
		if ( SOBJFileNames[ index ] )
		{
			free( (void*)(SOBJFileNames[ index ]) );
			SOBJFileNames[ index ] = NULL;
		}
	}
}

int	SObjScenarioInit( HSCREENOBJ hScreenObj, SCENARIOREF* pScenario ) 
{
	MISSIONREF*			pMission;
	HSCREENBTN			hScreenBtn;
	int					nMissionIndex;
	SPOINT				offset;
	DWORD				dwIDs;
	SBTN_SCRN_COLORS*	pArmyColors;
	int					nColorIndex;

	// acquire the players army colors
	nColorIndex = PlayerColor(ARMY_PLAYER);
	pArmyColors = ArmyInterfaceColors[ nColorIndex ];

	//first acquire the scenario title
	SObjSetTitle( hScreenObj, pScenario->pScenarioName );
	offset.x = 40;
	offset.y = 44;
	dwIDs    = ((pScenario->nScenarioID)<<16);
	for ( nMissionIndex=0;nMissionIndex<pScenario->nNumberMissions; ++nMissionIndex )
	{
		// access the button associated with this mission
		pMission = &(pScenario->pMissions[ nMissionIndex ]);
		hScreenBtn = hScreenObj->hScreenBtns[ nMissionIndex ];

		// see if this is the "most recent" mission and adjust its
		// NULL state color
		if ( (pMission->bVisible & STAT_NEXT_FLAG) == STAT_NEXT_FLAG )
			SBtnSetFGColor( hScreenBtn, BUTTON_NULL, SBTN_LT_GREEN );
		else
		if ( (pMission->bVisible & STAT_VISIBLE_FLAG) == STAT_VISIBLE_FLAG )
		{
			if ( (hScreenBtn->bAttributes & SBTN_DISABLED) == SBTN_DISABLED )
				SBtnSetFGColor( hScreenBtn, BUTTON_NULL, pArmyColors->DisabledColor );
			else
				SBtnSetFGColor( hScreenBtn, BUTTON_NULL, pArmyColors->AlreadyPlayedColor );
		}
		else
			SBtnSetFGColor( hScreenBtn, BUTTON_NULL, pArmyColors->DisabledColor );

		SBtnApplyOffset( hScreenBtn, &offset );
		SBtnSetText( hScreenBtn, pMission->pMissionName );
		dwIDs &= 0xFFFF0000;		// clear the MissionID
		dwIDs |= (0x0000FFFF & pMission->nMissionID);
		SBtnSetData( hScreenBtn, dwIDs );
		SBtnSetCallback( hScreenBtn, BUTTON_CLICKED, (LPVOID)ScrnSelectMission );
		if ( pMission->bVisible == FALSE )
			SBtnSetAttributes( hScreenBtn, SBTN_DISABLED );
		else
			SBtnClearAttributes( hScreenBtn, SBTN_DISABLED|SBTN_INVISIBLE|SBTN_NO_FOCUS );
		hScreenBtn->bUpdate = TRUE;
		offset.y += 20;
	}

	return( nMissionIndex );
}

int	SObjEnumerateCampaigns( HSCREENOBJ hScreenObj )
{
	TCHAR			filename[CPN_MAX_FILENAME + 1];
	HANDLE			hFileCtl;
	WIN32_FIND_DATA	fileData;
	int				nIndex;
	int				len;
	int				nButton = 0;
	char*			pFileName;
	DWORD			bFileFound = FALSE;			// assume no files

#ifdef SBTN_DEBUG
	TRACE( "SObjEnumerateCampaigns( %08x )\n", hScreenObj );
#endif

	// clear the existing list
	SObjReleaseCampaignData();

	// access al .CPN files
	SetPath(CAMPAIGN_PATH);
	nIndex      = 0;
	strcpy( filename, "CAMPAIGN.CPN" );

	// look for the first file with this suffix
	hFileCtl = FindFirstFile( filename, &fileData );
	if ( hFileCtl != INVALID_HANDLE_VALUE )
		bFileFound = TRUE;

	// store this first file into the ScreenObj ScreenBtn and then look for
	// others
	nButton = 0;
	while ( bFileFound && (nIndex<SOBJ_MAX_FILES) )
	{
		len = strlen( fileData.cFileName );
		if ( len )
		{
			pFileName = (char*)malloc( len+1 );
			if ( !pFileName )
				return(FALSE);
			strcpy( pFileName, fileData.cFileName );
			SOBJFileNames[ nIndex ] = pFileName;
			++nIndex;

			AiCampaignLoad( fileData.cFileName );
#ifdef CPN_DEBUG
			AiDumpCPN();
#endif
		}
		bFileFound = FindNextFile( hFileCtl, &fileData );
	}
	FindClose( hFileCtl );

	// make sure the last filename in list is NULL
	SOBJFileNames[ nIndex ] = NULL;

	// now enumerate the data
	if ( g_NumberCampaigns > SOBJ_MAX_DISPLAY_CAMPAIGNS )
		SObjMoreON( hScreenObj );	// turn on the MORE ScreenBtn

	SObjEnumGames( hScreenObj, g_Campaigns, g_NumberCampaigns );
	nButton = g_NumberCampaigns;

    return( nButton );
}

BOOL	SObjEnumGames( HSCREENOBJ hScreenObj, CAMPAIGNREF** pCampaignData, int nNumberCampaigns  )
{
	LONG			iCampaign;
	CAMPAIGNREF*	pCampaign;
	SPOINT			offset;

	ASSERT( hScreenObj );
	ASSERT( pCampaignData );

#ifdef SBTN_DEBUG
	TRACE( "SObjEnumGames( %08x )\n", hScreenObj );
#endif

	// insert each campaign
	offset.x = 0;
	offset.y = 70;
	for( iCampaign=0; iCampaign<nNumberCampaigns; ++iCampaign )
	{
		pCampaign = g_Campaigns[ iCampaign ];

#ifdef	SCREEN_DEBUG
TRACE( "Campaign %d: (%s:%d)\n", iCampaign, pCampaign->pCampaignName, pCampaign->bVisible );
#endif

		SObjEnumCampaign( hScreenObj, pCampaign, &offset, iCampaign );

		offset.y += 40;
	}

    return(TRUE);
}

BOOL	SObjEnumCampaign( HSCREENOBJ hScreenObj, CAMPAIGNREF* pCampaign, SPOINT* pOffset, int nButton )
{
	HSCREENBTN	hScreenBtn = (hScreenObj->hScreenBtns[ nButton ]);
	SPOINT*		pBtnPosition;
	SPOINT		newPosition;

	ASSERT( hScreenObj );
	ASSERT( pCampaign );
	ASSERT( hScreenBtn );

#ifdef SBTN_DEBUG
	TRACE( "SObjEnumCampaign( %08x )\n", hScreenObj );
#endif

	// recalculate the position of the ScreenBtn
	pBtnPosition = SBtnGetPosition( hScreenBtn );
	ASSERT( pBtnPosition );

#ifdef	SCREEN_DEBUG
TRACE( "Btn %d: (%d:%d)\n", nButton, pBtnPosition->x, pBtnPosition->y );
#endif

	// apply the offset to the screenBtn position
	newPosition.x = pBtnPosition->x + pOffset->x;
	newPosition.y = pBtnPosition->y + pOffset->y;
	SBtnSetPosition( hScreenBtn, &newPosition );

#ifdef	SCREEN_DEBUG
pBtnPosition = SBtnGetPosition( hScreenBtn );
ASSERT( pBtnPosition );
TRACE( "Btn %d: (%d:%d)\n", nButton, pBtnPosition->x, pBtnPosition->y );
#endif
	
     // insert campaign name into the screenBtn
	SBtnSetText( hScreenBtn, pCampaign->pCampaignName );
	SBtnSetData( hScreenBtn, (DWORD)(pCampaign->nCampaignID) );
	SBtnSetCallback( hScreenBtn, BUTTON_CLICKED, (LPVOID)ScrnSelectCampaign );

	// make sure this screen button is selectable
	if ( pCampaign->bVisible == STAT_DISABLED_FLAG )
		SBtnSetAttributes( hScreenBtn, SBTN_DISABLED );
	else
		SBtnClearAttributes( hScreenBtn, SBTN_DISABLED|SBTN_INVISIBLE|SBTN_NO_FOCUS );

    return(TRUE);
}

void	SObjMoreON( HSCREENOBJ hScreenObj )
{
	int			nButton;
	HSCREENBTN	hScreenBtn;

	for( nButton=0; nButton<hScreenObj->nNumberBtns; ++nButton )
	{
		hScreenBtn = hScreenObj->hScreenBtns[ nButton ];
		if ( (hScreenBtn->bAttributes & SBTN_MORE ) == SBTN_MORE )
			hScreenBtn->bAttributes &= ~(SBTN_INVISIBLE|SBTN_DISABLED);
	}
}

void	SObjMoreOFF( HSCREENOBJ hScreenObj )
{
	int			nButton;
	HSCREENBTN	hScreenBtn;

	for( nButton=0; nButton<hScreenObj->nNumberBtns; ++nButton )
	{
		hScreenBtn = hScreenObj->hScreenBtns[ nButton ];
		if ( (hScreenBtn->bAttributes & SBTN_MORE ) == SBTN_MORE )
			hScreenBtn->bAttributes |= SBTN_INVISIBLE;
	}
}

void	SObjApplyOffset( HSCREENOBJ hScreenObj, SPOINT* pOffset, int btnUse )
{
	SPOINT*	pObjPos;
	int		nButton;
	SPOINT	btnOffset;

	// offset the object position
	pObjPos     = SObjGetPosition( hScreenObj );
	pObjPos->x += pOffset->x;
	pObjPos->y += pOffset->y;

	// offset the object title position
	pObjPos     = SObjGetTitlePosition( hScreenObj );
	pObjPos->x += pOffset->x;
	pObjPos->y += pOffset->y;

	// now offset all the buttons within this object
	if ( btnUse )
	{
		btnOffset.x = 0;
		btnOffset.y = 0;
		for( nButton=0; nButton<hScreenObj->nNumberBtns; ++nButton )
		{
			switch( btnUse )
			{
			case APPLY_AS_IS:
				SBtnApplyOffset( hScreenObj->hScreenBtns[ nButton ], pOffset );
				break;
			case APPLY_AND_GROW:
				SBtnApplyOffset( hScreenObj->hScreenBtns[ nButton ], &btnOffset );
				btnOffset.x += pOffset->x;
				btnOffset.y += pOffset->y;
				break;
			}
		}
	}
}

void	SObjForceUpdate( HSCREENOBJ hScreenObj )
{
	int			nButton;
	HSCREENBTN	hScreenBtn;

	for( nButton=0; nButton<hScreenObj->nNumberBtns; ++nButton )
	{
		hScreenBtn = hScreenObj->hScreenBtns[ nButton ];
		hScreenBtn->bUpdate = TRUE;
	}
	hScreenObj->bUpdate = TRUE;
}

void	SObjDump( HSCREENOBJ hObject )
{
	int			nButton;
	SBOX*		pBox;

	// dump the attributes
	TRACE( "    Attributes:            " );
	if ( hObject->bAttributes                         == SOBJ_CLEAR )
		TRACE( "SOBJ_CLEAR " );
	if ( (hObject->bAttributes & SOBJ_BKG_IMAGE)      == SOBJ_BKG_IMAGE )
		TRACE( "SOBJ_BKG_IMAGE " );
	if ( (hObject->bAttributes & SOBJ_BKG_AREA)       == SOBJ_BKG_AREA )
		TRACE( "SOBJ_BKG_AREA " );
	if ( (hObject->bAttributes & SOBJ_BKG_OPAQUE)     == SOBJ_BKG_OPAQUE )
		TRACE( "SOBJ_BKG_OPAQUE " );
	if ( (hObject->bAttributes & SOBJ_BKG_TRANS)      == SOBJ_BKG_TRANS )
		TRACE( "SOBJ_BKG_TRANS " );
	if ( (hObject->bAttributes & SOBJ_SPCL_OK)        == SOBJ_SPCL_OK )
		TRACE( "SOBJ_SPCL_OK " );
	if ( (hObject->bAttributes & SOBJ_SPCL_CANCEL)    == SOBJ_SPCL_CANCEL )
		TRACE( "SOBJ_SPCL_CANCEL " );
	if ( (hObject->bAttributes & SOBJ_SPCL_NEXT)      == SOBJ_SPCL_NEXT )
		TRACE( "SOBJ_SPCL_NEXT " );
	if ( (hObject->bAttributes & SOBJ_SPCL_BACK)      == SOBJ_SPCL_BACK )
		TRACE( "SOBJ_SPCL_BACK " );
	if ( (hObject->bAttributes & SOBJ_SPCL_FINISH)    == SOBJ_SPCL_FINISH )
		TRACE( "SOBJ_SPCL_FINISH " );
	if ( (hObject->bAttributes & SOBJ_INVISIBLE)      == SOBJ_INVISIBLE )
		TRACE( "SOBJ_INVISIBLE " );
	if ( (hObject->bAttributes & SOBJ_TITLE_CENTER)   == SOBJ_TITLE_CENTER )
		TRACE( "SOBJ_TITLE_CENTER " );
	if ( (hObject->bAttributes & SOBJ_HAS_TITLE)      == SOBJ_HAS_TITLE )
		TRACE( "SOBJ_HAS_TITLE " );
	TRACE( "\n" );

	TRACE( "    Object Position:       (%d,%d)\n", hObject->position.x, hObject->position.y );
	TRACE( "    Parent Box:            (x:%d,y:%d,w:%d,h:%d)\n",
			hObject->ParentBox.x,  hObject->ParentBox.y,
			hObject->ParentBox.cx, hObject->ParentBox.cy );
	pBox = SObjGetBkgArea( hObject );
	if ( pBox )
	{
	TRACE( "    Area Box:              (x:%d,y:%d,w:%d,h:%d)\n",
			pBox->x,  pBox->y,
			pBox->cx, pBox->cy );
	}

	// display the TITLE INFO
	if ( (hObject->bAttributes & SOBJ_HAS_TITLE) == SOBJ_HAS_TITLE )
	{
		TRACE( "    Object Title:          [%s]\n", hObject->title.titleRef );
		TRACE( "    Title Position:              (%d,%d)\n", hObject->position.x, hObject->position.y );
		TRACE( "    Title FontID:                %d\n", hObject->title.titleFontID );
		TRACE( "    Title FG Color:              %s\n", SBtnColorName( hObject->title.titleFGColor ) );
		TRACE( "    Title BG Color:              %s\n", SBtnColorName( hObject->title.titleBGColor ) );
	}

	// check each screenbtn in this screenobj
	if ( (hObject->bAttributes & SOBJ_INVISIBLE) != SOBJ_INVISIBLE )
	{
		for ( nButton=0; nButton<(hObject->nNumberBtns); ++nButton )
			SBtnDump( hObject->hScreenBtns[nButton] );
	}
}

//========================================================================
//							EOF
//========================================================================
