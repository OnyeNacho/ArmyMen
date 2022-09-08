//========================================================================
//	FILE:			$Workfile: ScreenObj.h $
//
//	DESCRIPTION:	ArmyMen ScreenObj Class definition.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, October 14, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ScreenObj.h 11    3/17/98 11:25a Aburgess $
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
//  $Log: /ArmyMen/src/ScreenObj.h $
//  
//  11    3/17/98 11:25a Aburgess
//  SObjSetConFigColor() prototype added
//  
//  10    2/12/98 4:18p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  9     2/05/98 12:41p Aburgess
//  added capability to make SCREENOBJs invisible
//  
//  8     12/18/97 1:18p Aburgess
//  New Audio and User Configuration screens. New Scrolling buttons and
//  Slider bars
//  
//  7     12/09/97 12:12p Phu
//  
//  6     12/04/97 9:06p Aburgess
//  modifications for Multiplayer Host/Remote screens
//  
//  5     12/01/97 9:55a Aburgess
//  update of SCREEN processing
//  
//  4     11/07/97 10:42a Aburgess
//  New Full Screen UI interfaces
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
// What is a SCREENOBJ?
//
// A screen object is a collection of objects the user interacts within in
// order do respond to various questions the application may ask.
//
// All screen objects have a number of basic attributes attached to them.
// These attributes act as controls for handling the presentation and
// response.
//
// A screen object contains the following elements:
//
//    ATTRIBUTES: used to control the presentation of the screen object 
//
//    SOBJ_BKG: defines the area of the screen object. This background
//    can be represented in two ways.
//
//        As an IMAGE, where the screen object area is defined by the size
//        of the image.
//
//        As a SBOX/RGB color pair, where the SBOX defines the area of the
//        screen image and the RGB color is the fill color. This area fill
//        can either be a solid or opaque fill (see ATTRIBUTES).
//        
//========================================================================

#ifndef __SCREENOBJ_H__
#define __SCREENOBJ_H__


//------------------------------------------------------------------------
//				DEPENDENCIES
//------------------------------------------------------------------------
#include "ScreenBtn.h"

extern	HSCREENBTN	SBTNspecialScreenBtns[ SBTN_MAX_SPCL_BTNS ];

//------------------------------------------------------------------------
//				GENERAL SCREENOBJ DEFINES
//------------------------------------------------------------------------

#define KEYOFFSET					14
#define	SOBJ_MAX_NAME_LEN			32
#define	SOBJ_MAX_TEXT_LEN			64
#define	SOBJ_MAX_REF_LEN			64
#define	SOBJ_MAX_OBJS				72
#define	SOBJ_MAX_BTNS				8
#define	SOBJ_MAX_FILES				31
#define	SOBJ_MAX_DISPLAY_FILES		4
#define	SOBJ_MAX_DISPLAY_CAMPAIGNS	4

#define	APPLY_IGNORE				0
#define	APPLY_AS_IS					1
#define	APPLY_AND_GROW				2

//------------------------------------------------------------------------
//				SCREENOBJ ATTRIBUTES
//------------------------------------------------------------------------

#define	SOBJ_CLEAR			(ULONG)(0x00000000)	// all attributes cleared
#define	SOBJ_BKG_IMAGE		(ULONG)(0x00000001)	// screenobj bkg is an image
#define	SOBJ_BKG_AREA		(ULONG)(0x00000002)	// screenobj bkg is an area fill
#define	SOBJ_BKG_OPAQUE		(ULONG)(0x00000004)	// screenobj bkg area fill is opaque
#define	SOBJ_BKG_TRANS		(ULONG)(0x00000008)	// screenobj bkg area fill is transparent
#define	SOBJ_SPCL_OK		(ULONG)(0x00000010)	// add preallocated OK screenbtn
#define	SOBJ_SPCL_CANCEL	(ULONG)(0x00000020)	// add preallocated CANCEL screenbtn
#define	SOBJ_SPCL_NEXT		(ULONG)(0x00000040)	// add preallocated NEXT screenbtn
#define	SOBJ_SPCL_BACK		(ULONG)(0x00000080)	// add preallocated BACK screenbtn
#define	SOBJ_SPCL_FINISH	(ULONG)(0x00000100)	// add preallocated FINISH screenbtn

#define	SOBJ_INVISIBLE		(ULONG)(0x08000000)	// add preallocated FINISH screenbtn

#define	SOBJ_TITLE_CENTER	(ULONG)(0x40000000)	// center title string horizontally
#define	SOBJ_HAS_TITLE		(ULONG)(0x80000000)	// screenobj has a title string

//------------------------------------------------------------------------
//				SCREENOBJ STRUCTURE
//------------------------------------------------------------------------

typedef	SBTN_COLOR	SOBJ_COLOR;

typedef struct	screenObjectImage
{
	SBOX		bkgBox;							// bkg box and size
	SPRITE		bkgSprite;						// bkg image sprite
	LPTSTR		bkgResourceID;					// bkg resource ID, if used
	char		bkgRef[SOBJ_MAX_REF_LEN+1];		// bkg filename, if used
} SOBJIMAGE;

typedef struct	screenObjectRectFill
{
	SBOX		bkgBox;							// bkg box to be filled
	SOBJ_COLOR	bkgColor;						// bkg color to fill with
	BYTE*		bkgShadeTable;					// translucent shading table pionter
} SOBJAREA;

typedef struct	screenObjectTitle
{
	SPOINT		titlePosition;					// screen position of screenobj
	LONG		titleFontID;
	SOBJ_COLOR	titleBGColor;
	SOBJ_COLOR	titleFGColor;
	LPTSTR		titleResourceID;				// bkg resource ID, if needed
	char		titleRef[SOBJ_MAX_NAME_LEN+1];	// bkg title string
} SOBJTITLE;

typedef struct	screenObjectTitleDef
{
	SPOINT		titlePosition;					// screen position of screenobj
	LONG		titleFontID;
	SOBJ_COLOR	titleBGColor;
	SOBJ_COLOR	titleFGColor;
	LPTSTR		titleResourceID;				// bkg resource ID, if needed
	char*		titleRef;						// bkg title string
} SOBJTITLEDEF;

typedef struct	screenObject
{
	// Status structure
	ULONG		bAttributes;		// screenobj attributes
	union {
		SOBJIMAGE	bkgImage;		// bkg image
		SOBJAREA	bkgArea;		// bkg rect fill area
	};
	BOOL		bUpdate;

	// Presentation structure
	SBOX		ParentBox;						// screenObj parent box and size
	SPOINT		position;						// screen position of screenobj
	SOBJTITLE	title;							// screen object title string, if present
	int			nNumberBtns;					// number of buttons in screenobj
	HSCREENBTN	hScreenBtns[SOBJ_MAX_BTNS+1];	// list of pointers to screenbtns

} SCREENOBJ;

typedef SCREENOBJ*	HSCREENOBJ;

typedef struct	screenObjImageDef
{
	SBOX		bkgBox;							// screenObj bkg box and size
	char		bkgRef[SOBJ_MAX_REF_LEN+1];		// screenObj bkg resource/filename reference
} SOBJIMAGEDEF;

typedef	struct	scrnObjDef
{
	ULONG			bAttributes;					// screenObj Attributes
	SPOINT			position;						// screenObj position of screenobj
	SOBJTITLEDEF*	pTitle;							// screenObj title string, if present
	SOBJIMAGEDEF*	pBkgImage;						// screenObj bkg image
	SOBJAREA*		pBkgArea;						// screenObj bkg rect fill area
	int				nNumberBtns;					// screenObj number of buttons
	SCREENBTNDEF*	pScreenBtnDefs[SOBJ_MAX_BTNS+1];// screenObj list of pointers to screenbtnDefs

} SCREENOBJDEF;

//========================================================================
//						PROTOTYPES
//========================================================================
extern	BOOL		SObjInit( void );
extern	void		SObjExit( void );

extern	BOOL		SObjLoad( HSCREENOBJ hScreenObj );
extern	void		SObjFree( HSCREENOBJ hScreenObj );
extern	void		SObjDisplay( HSCREENOBJ hScreenObj );
extern	BOOL		SObjUpdate( HSCREENOBJ hScreenObj );

extern	HSCREENOBJ	SObjCreate( SPOINT* pPoint, ULONG bAttributes, SBOX* pParentBox );
extern	BOOL		SObjDelete( HSCREENOBJ hScreenObj );
extern	void		SObjDeleteAll( void );

extern	BOOL		SObjSetAttributes( HSCREENOBJ hScreenObj, ULONG bAttributes );
extern	BOOL		SObjClearAttributes( HSCREENOBJ hScreenObj, ULONG bAttributes );
extern	ULONG		SObjGetAttributes( HSCREENOBJ hScreenObj );
extern	BOOL		SObjHaveAttributes( HSCREENOBJ hScreenObj, ULONG bAttributesMask );

extern	BOOL		SObjSetPosition( HSCREENOBJ hScreenObj, SPOINT* pPosition );
extern	SPOINT*		SObjGetPosition( HSCREENOBJ hScreenObj );

extern	BOOL		SObjSetTitle( HSCREENOBJ hScreenObj, char* pText );
extern	char*		SObjGetTitle( HSCREENOBJ hScreenObj );
extern	BOOL		SObjSetTitlePosition( HSCREENOBJ hScreenObj, SPOINT* pPosition );
extern	SPOINT*		SObjGetTitlePosition( HSCREENOBJ hScreenObj );
extern	BOOL		SObjSetTitleFont( HSCREENOBJ hScreenObj, LONG nFontID );
extern	LONG		SObjGetTitleFont( HSCREENOBJ hScreenObj );
extern	BOOL		SObjSetTitleBGColor( HSCREENOBJ hScreenObj, SOBJ_COLOR bgColor );
extern	SOBJ_COLOR	SObjGetTitleBGColor( HSCREENOBJ hScreenObj );
extern	BOOL		SObjSetTitleFGColor( HSCREENOBJ hScreenObj, SOBJ_COLOR fgColor );
extern	SOBJ_COLOR	SObjGetTitleFGColor( HSCREENOBJ hScreenObj );

extern	BOOL		SObjSetBkgImage( HSCREENOBJ hScreenObj, SOBJIMAGEDEF* pImage );
extern	SPRITE*		SObjGetBkgImage( HSCREENOBJ hScreenObj );

extern	BOOL		SObjSetBkgArea( HSCREENOBJ hScreenObj, SOBJAREA* pArea );
extern	SBOX*		SObjGetBkgArea( HSCREENOBJ hScreenObj );
extern	BOOL		SObjSetBkgColor( HSCREENOBJ hScreenObj, SOBJ_COLOR eColor );
extern	SOBJ_COLOR	SObjGetBkgColor( HSCREENOBJ hScreenObj );
extern	BOOL		SObjSetShadeTable( HSCREENOBJ hScreenObj, BYTE* pShadeTable );
extern	BYTE*		SObjGetShadeTable( HSCREENOBJ hScreenObj );
extern	BOOL		SObjInEditMode( HSCREENOBJ hScreenObj );

extern	void		SObjResetAll( void );
extern	void		SObjReset( HSCREENOBJ hObject );
extern	HSCREENOBJ	SObjIsInObject( SPOINT* pPoint );
extern	void		SObjLoadDef( HSCREENOBJ hScreenObj, SCREENOBJDEF* pScreenObjDef );
extern	void		SObjLoadTitle( HSCREENOBJ hScreenObj, SOBJTITLEDEF* pScreenTitle );
extern	void		SObjSetConFigColor( HSCREENBTN hScreenBtn, BOOL bPlayerColor );
extern	void		SObjUpdateObject( SPOINT* pPoint );

extern	int			SObjCampaignInit( HSCREENOBJ hScreenObj);
extern	void		SObjReleaseCampaignData( void );
extern	int			SObjScenarioInit( HSCREENOBJ hScreenObj, SCENARIOREF* pScenario );
extern	int			SObjEnumerateCampaigns( HSCREENOBJ hScreenObj );
extern	BOOL		SObjEnumGames( HSCREENOBJ hScreenObj, CAMPAIGNREF** pCampaignData, int nNumberCampaigns  );
extern	BOOL		SObjEnumCampaign( HSCREENOBJ hScreenObj, CAMPAIGNREF* pCampaign, SPOINT* pOffset, int nButton );

extern	void		SObjMoreOn( HSCREENOBJ hScreenObj );
extern	void		SObjApplyOffset( HSCREENOBJ hScreenObj, SPOINT* pOffset, int btnUse );
extern	void		SObjForceUpdate( HSCREENOBJ hScreenObj );

extern	void		SObjDump( HSCREENOBJ hObject );

#endif
//========================================================================
//						EOF
//========================================================================
