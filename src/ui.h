/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: ui.h $
//
//	DESCRIPTION:	Headers for handling the user interface
//
//	AUTHOR:			Alex Werner
//
//	CREATED:		Tuesday, June 24, 1997
//
//	REVISION:		$Header: /ArmyMen/src/ui.h 116   4/17/98 11:23a Bwilcox $
//
//	Copyright (C) 1997 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  History
//
//  $Log: /ArmyMen/src/ui.h $
//  
//  116   4/17/98 11:23a Bwilcox
//  scrolling click on paper map takes you there
//  
//  115   4/06/98 2:03p Nrobinso
//  have releaserecall return a boolean to tell if it was really released
//  
//  113   3/27/98 8:36p Phu
//  invisble cursor
//  
//  112   3/26/98 8:24p Nrobinso
//  fix firing when clicking thru in game screens; add MP music
//  
//  111   3/24/98 4:11p Phu
//  clear firing bar info if user manually changes weapon
//  
//  110   3/19/98 7:51p Nrobinso
//  
//  109   3/14/98 8:56p Nrobinso
//  allow switching between mouse button 2 controlling the weapons and
//  forward movement
//  
//  108   3/14/98 3:13p Nrobinso
//  remove static functions
//  
//  107   3/13/98 7:29p Phu
//  alt gunsight
//  
//  106   3/10/98 11:22p Nrobinso
//  move windows cursor routines to input
//  
//  105   3/03/98 1:59p Phu
//  esc handling for setup state
//  
//  104   3/02/98 1:01p Phu
//  keep screen scrolled even for last mortar shell
//  
//  103   3/02/98 11:23a Phu
//  restore after alt-tab for ODF
//  
//  102   2/27/98 11:58a Nrobinso
//  add big map
//  
//  101   2/25/98 3:25p Phu
//  rename dashboard sprites
//  
//  100   2/25/98 11:49a Aburgess
//  new time values made global
//  
//  99    2/24/98 2:08p Phu
//  changed cursor loading
//  
//  98    2/16/98 9:25p Nrobinso
//  script display bmp
//  
//  97    2/16/98 5:46p Nrobinso
//  
//  96    2/13/98 7:02p Nrobinso
//  remove special firing for vehicles
//  
//  95    2/13/98 12:47p Phu
//  get rid of firing bar
//  
//  94    2/11/98 5:27p Phu
//  delay cursor retract
//  
//  93    2/06/98 11:28p Nrobinso
//  change mission and map function names
//  
//  92    2/06/98 1:58p Bwilcox
//  fixedc curosr in mp setup
//  
//  91    2/05/98 3:57p Bwilcox
//  show unit types on buttons in mp setup
//  
//  90    2/02/98 11:49a Nrobinso
//  setup for keyboard go to chat
//  
//  89    2/02/98 11:42a Phu
//  implement ShowWindowsCursor()
//  
//  88    2/02/98 1:07a Nrobinso
//  change ui for multiplayer
//  
//  87    1/30/98 5:12p Nrobinso
//  have firingbar return the same value until it is reset
//  
//  86    1/28/98 10:19a Aburgess
//  modifications made to support game start MISSION recall. Support for
//  successive missions has not been implemented yet and will still display
//  the old MISSION STATEMENT interface. Additionally, access directly to
//  the HOST and REMOTE campaign select screens now occurs if in a lobby
//  session.
//  
//  85    1/26/98 7:28p Phu
//  don't jump sarge when doing air support
//  
//  84    1/26/98 12:58p Aburgess
//  modifications made to support the new mission briefing screens
//  
//  83    1/24/98 3:13p Aburgess
//  modifications made to support Mission Recall button
//  
//  82    1/20/98 3:31p Awerner
//  added pause button for multiplayer
//  
//  81    1/20/98 2:06p Awerner
//  added mission button
//  
//  80    1/17/98 10:58p Bwilcox
//  unbroke follow
//  
//  79    1/17/98 8:17p Nrobinso
//  right button up routine
//  
//  78    1/13/98 5:05p Awerner
//  Updated grenade firing bar code for new artwork
//  
//  77    1/06/98 1:30p Phu
//  restore dashboard/cursors after alt-tab
//  
//  ...
//  
//  1     7/01/97 10:33a Awerner
//  first check-in
// 
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////

#ifndef _UI_H_
#define _UI_H_


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "text.h"
#include "aix.h"
#include "sprite.h"
#include "army.h"
#include "unit.h"


/////////////////////////////////////////////////////////////////////////////
// Typedefs and #defines
/////////////////////////////////////////////////////////////////////////////

// Time increments in milliseconds
#define	HALF_SECOND		 500
#define	ONE_SECOND		1000
#define	TWO_SECONDS		2000
#define	THREE_SECONDS	3000
#define	FOUR_SECONDS	4000
#define	FIVE_SECONDS	5000

// possible parameters for UI_HitAttackKey and UI_HitDefendKey
// indicates when the order is executed
#define IMMEDIATE	TRUE
#define LATER		FALSE

extern char NeedToJumpToSarge;

typedef enum
{
	CURSORTYPE_NORMAL,
	CURSORTYPE_SCROLLING,
	CURSORTYPE_ATTACK,
	CURSORTYPE_DEFEND,
	CURSORTYPE_FOLLOW,
	CURSORTYPE_AIRSTRIKE,
	CURSORTYPE_AIRSUPPORT,
	CURSORTYPE_RECON,
	CURSORTYPE_GUNSIGHT,
	CURSORTYPE_ALTGUNSIGHT,
	CURSORTYPE_INVISIBLE,

	CURSORTYPE_ITEM_RIFLE_DASH,
	CURSORTYPE_ITEM_MORTAR_DASH,
	CURSORTYPE_ITEM_FLAME_DASH,
	CURSORTYPE_ITEM_BAZOOKA_DASH,
	CURSORTYPE_ITEM_GRENADE_DASH,
	CURSORTYPE_ITEM_JEEP_DASH,
	CURSORTYPE_ITEM_HALFTRACK_DASH,
	CURSORTYPE_ITEM_TANK_DASH,
	CURSORTYPE_ITEM_TRUCK_DASH,

	CURSORTYPE_ITEM_RIFLE_RED,
	CURSORTYPE_ITEM_MORTAR_RED,
	CURSORTYPE_ITEM_FLAME_RED,
	CURSORTYPE_ITEM_BAZOOKA_RED,
	CURSORTYPE_ITEM_GRENADE_RED,
	CURSORTYPE_ITEM_JEEP_RED,
	CURSORTYPE_ITEM_HALFTRACK_RED,
	CURSORTYPE_ITEM_TANK_RED,
	CURSORTYPE_ITEM_TRUCK_RED,

	CURSORTYPE_ITEM_RIFLE_GREEN,
	CURSORTYPE_ITEM_MORTAR_GREEN,
	CURSORTYPE_ITEM_FLAME_GREEN,
	CURSORTYPE_ITEM_BAZOOKA_GREEN,
	CURSORTYPE_ITEM_GRENADE_GREEN,
	CURSORTYPE_ITEM_JEEP_GREEN,
	CURSORTYPE_ITEM_HALFTRACK_GREEN,
	CURSORTYPE_ITEM_TANK_GREEN,
	CURSORTYPE_ITEM_TRUCK_GREEN,

	CURSORTYPE_LAST
} CURSORTYPE;

#define UIMODE_IGNORE -1
#define UIMODE_LOOKINGATSARGE 0
#define UIMODE_SCROLLING 1
#define UIMODE_PLACINGITEM 2

#define MAX_UNDEPLOYED_STUFF 256

#define SQUADMESSAGE_MAXLENGTH 60

#define ITEMSELECTTYPE_NONE 0
#define ITEMSELECTTYPE_RIFLE 1
#define ITEMSELECTTYPE_GRENADE 2
#define ITEMSELECTTYPE_FLAME 3
#define ITEMSELECTTYPE_BAZOOKA 4
#define ITEMSELECTTYPE_MORTAR 5
#define ITEMSELECTTYPE_JEEP 6
#define ITEMSELECTTYPE_HALFTRACK 7
#define ITEMSELECTTYPE_TANK 8
#define ITEMSELECTTYPE_TRUCK 9


typedef enum	//things that can show up on the dashboard
{
	GADGETTYPE_BUTTON, //whenever it's pressed, something happens

	GADGETTYPE_MULTIBUTTON, //same as button, but can have multiple graphics sets

	GADGETTYPE_2WAYBUTTON,	//when it's pressed down, something happens. It
							//stays down until pressed again

	GADGETTYPE_RADIOBUTTON,	//set of buttons. When one is pressed, others are released

	GADGETTYPE_LIST,	//list of options which can be clicked on and optionally scrolled

	GADGETTYPE_TEXTBOX,	//a box in which text is displayed

	GADGETTYPE_RADAR, //the radar

	GADGETTYPE_WHOLEDASHBOARD,	//dummy. used in dashboard assembly

	GADGETTYPE_INACTIVE, //so that buttons can be temporarily deactivated

	GADGETTYPE_END
} GADGETTYPE;

typedef enum
{
	DASH_CHUNK_MAIN,
	DASH_CHUNK_MULTISETUP,
	DASH_CHUNK_HIDDENBYMULTISETUP,
	DASH_CHUNK_LAST
} DASH_CHUNK_TYPE;

typedef struct
{
	GADGETTYPE type;
	DASH_CHUNK_TYPE chunk;
	void* pGadget;
} GADGET;


#define GADGET_BUTTON_DELAY 3 //frames a button is down before popping up after being pressed


///////stuff for GADGETTYPE_BUTTON

typedef void(*GadgetButtonFunc)(int /*0 for left button. 1 for right button*/);

typedef struct
{
	int curdelay;		//how long before it visually pops back up
	SPOINT screenpos;	//where to draw the buttons on the screen
	SPRITE *sprites[2];	//0=unpressed (up) 1=pressed (down)
	GadgetButtonFunc func;  //functions to call when clicked

} GADGET_BUTTON;

///////stuff for GADGETTYPE_MULTIBUTTON

typedef void(*GadgetMultiButtonFunc)(int /*0 for left button. 1 for right button*/, int /*current picture*/);

typedef struct
{
	int curdelay;		//how long before it visually pops back up
	int numpictures;	//how many different pictures there are for this multibutton
	int curpicture;		//which picture is currently being used
	SPOINT screenpos;	//where to draw the buttons on the screen
	SPRITE **sprites[2];	//0=unpressed (up) 1=pressed (down)
	GadgetMultiButtonFunc func;  //functions to call when clicked

} GADGET_MULTIBUTTON;

////////stuff for GADGETTYPE_2WAYBUTTON

#define GADGET_2WAYBUTTON_PRESSED 1
#define GADGET_2WAYBUTTON_RELEASED 0

typedef void(*Gadget2WayButtonFunc)(int /*up or down*/, int /*left or right button*/); 

typedef struct
{
	SPOINT screenpos;
	SPRITE *sprites[2];
	BYTE curstatus; 
	Gadget2WayButtonFunc func; //passes in an int indicating whether the button was
								//pressed or released
} GADGET_2WAYBUTTON;

////////stuff for GADGETTYPE_RADIOBUTTON

#define GADGET_RADIO_NONE -1 //indicates that no radio button is currently selected


//different behaviors possible when you click on the button that's already down
#define GADGET_RADIOTYPE_NOTHING 0 //nothing happens
#define GADGET_RADIOTYPE_REPRESS 1 //a button-press is generated on the button
#define GADGET_RADIOTYPE_DESELECT 2 //the button is unselected

typedef void (*GadgetRadioButtonFunc)(int /*which button*/, int /*left or right*/);

typedef struct
{
	BYTE radiotype;
	BYTE curbutton;
	BYTE numbuttons;
	SPOINT *screenpos; //point to array of screen positions of buttons
	SPRITE **sprites[2]; // pointers to arrays of up and down buttons
	GadgetRadioButtonFunc func;
} GADGET_RADIOBUTTON;


////////stuff for GADGETTYPE_LIST

#define GADGET_LIST_NONE -1		//if nothing is currently selected

#define GADGET_LIST_BUTTONTYPE_MAIN 0
#define GADGET_LIST_BUTTONTYPE_SCROLLUP 1
#define GADGET_LIST_BUTTONTYPE_SCROLLDOWN 2

//different behaviors possible when you click on the currently selected item
#define GADGET_LISTTYPE_NOTHING 0	   //nothing happens when you click the selected item
#define GADGET_LISTTYPE_REPRESS 1	   //the item is selected again
#define GADGET_LISTTYPE_DESELECT 2	   //the item is unselected
#define GADGET_LISTTYPE_NOSELECTIONS 3 //there's never a selected item

typedef struct
{
	int curdelay;		//how long before it visually pops back up
	SPOINT screenpos;	//where to draw the buttons on the screen
	SPRITE sprites[2];	//0=unpressed (up) 1=pressed (down)
} GADGET_LIST_SCROLLBUTTON;

typedef void (*GadgetListFunc)(int /*which list button*/, int /*which  mouse button*/, void* /*extradata*/);
typedef void (*ListCustomDrawFunc)( void* /*pointer to the list struct*/);	

typedef struct
{
	SIZE cursorsize; //must always be first element of structure
	int counter;
	RECT cursorrect;
}	CURSOR_INFO;



typedef struct
{
	BYTE listtype;
	BYTE listsize;		//how many things in the list
	BYTE howfarscrolled; //the index of the first entry currently displayed
	BYTE displaysize;    //how many can be displayed at once
	BYTE curitem;		//currently selected item

	

	SPOINT screenpos;	//of first entry
	BYTE spacing;		//vertical spacing between entries

	FONTS listfont;

	//TO ADD: some kind of font/color info

	GADGET_LIST_SCROLLBUTTON *scrollbuttons[2];

	char **listtext; //text of items to display


	GadgetListFunc func;



	CURSOR_INFO *cursordata; //used to get the text size in the chat typing window

	void *extradata;


	ListCustomDrawFunc drawfunc;

} GADGET_LIST;



///////stuff for GADGETTYPE_TEXTBOX
typedef struct
{
	BYTE linesoftext;
	BYTE onscreenlines;

	SPOINT screenpos;
	BYTE spacing;

	FONTS textfont;

	char **boxtext;

	void *extradata;
} GADGET_TEXTBOX;

#define MESSAGE_COMP_MAXLENGTH 27 //maximum length of person-to-person chat messages
#define CHAT_MESSAGES_ONSCREEN 6


typedef struct
{
	int curtopstring;
	char *pstrings[CHAT_MESSAGES_ONSCREEN];
	char strings[(MESSAGE_COMP_MAXLENGTH+1)*CHAT_MESSAGES_ONSCREEN];
} CHAT_RECEIVE_STRUCT;

typedef struct
{
	char *ptext;
	char text[1]; //dummy... will usually be longer
} SINGLE_TEXTLINE_STRUCT;

#define TEXTLINE_UNITNAME_LENGTH 64


//stuff for GADGETTYPE_RADAR
typedef struct
{
    int x; 		// radarscope location
    int y; 		// radarscope location
    int type;	// kind of object
	int angle;	// 0 to RADAR_SWEEP_FRAMES-1
} FASTBLIP;
#define FRND_BLIP 1
#define FOE_BLIP 2
#define VEHICLE_BLIP 3

typedef struct
{
	SPOINT center;
	int cursweeppos;
	int startingsweeptime;

	int numblips;
	FASTBLIP blips[MAX_FORCES+1];

	BOOL enabled;

}  GADGET_RADAR;

#define RADAR_SWEEP_FRAMES 32 //max number of distinct frames
#define RADAR_SWEEP_TIME 2000 //time it takes the arm to swing all the way around



typedef struct
{
	BYTE whichpart; //of radio button. also used to distinguish scroll buttons from list
	BYTE subdivisionwidth; //used only for a list. specifies how big each subdivision is
						   //0 if not subdivided

	RECT screenrect;
	GADGET *pGadget; //what gadget this button belongs to
} ONSCREENBUTTON;




typedef enum
{
	DASHBOARD_START,	

	DASHBOARD_MISSION,
	DASHBOARD_PAUSE,

	DASHBOARD_STARTLIGHT_1,
	DASHBOARD_STARTLIGHT_2,
	DASHBOARD_STARTLIGHT_3,

	DASHBOARD_ALLIANCE_BACKGROUND,

	DASHBOARD_ALLIANCE_1, 
	DASHBOARD_ALLIANCE_2,
	DASHBOARD_ALLIANCE_3,

	DASHBOARD_CHATTOGGLE_1,
	DASHBOARD_CHATTOGGLE_2,
	DASHBOARD_CHATTOGGLE_3,

	DASHBOARD_MESSAGEFROMSQUADWINDOW,

	DASHBOARD_COMPOSEMESSAGEWINDOW,

	DASHBOARD_RECEIVECHATWINDOW,

	DASHBOARD_UNITINFO,

	DASHBOARD_VEHICLEAMMOICON,
	DASHBOARD_VEHICLEAMMODISPLAY,

	DASHBOARD_WEAPONICON,
	DASHBOARD_ITEMICON,
	DASHBOARD_VEHICLEICON,
	DASHBOARD_AMMODISPLAY,

	DASHBOARD_WEAPONSELECTED_1,
	DASHBOARD_WEAPONSELECTED_2,
	DASHBOARD_WEAPONSELECTED_3,

	DASHBOARD_SARGEHEALTH_1,
	DASHBOARD_SARGEHEALTH_2,
	DASHBOARD_SARGEHEALTH_3,
	DASHBOARD_SARGEHEALTH_4,
	DASHBOARD_SARGEHEALTH_5,
	DASHBOARD_SARGEHEALTH_6,
	DASHBOARD_SARGEHEALTH_7,
	DASHBOARD_SARGEHEALTH_8,

	DASHBOARD_VEHICLEHEALTH_1,
	DASHBOARD_VEHICLEHEALTH_2,
	DASHBOARD_VEHICLEHEALTH_3,
	DASHBOARD_VEHICLEHEALTH_4,
	DASHBOARD_VEHICLEHEALTH_5,
	DASHBOARD_VEHICLEHEALTH_6,
	DASHBOARD_VEHICLEHEALTH_7,
	DASHBOARD_VEHICLEHEALTH_8,

	DASHBOARD_TROOPERINFO_1,
	DASHBOARD_TROOPERINFO_2,
	DASHBOARD_TROOPERINFO_3,
	DASHBOARD_TROOPERINFO_4,
	DASHBOARD_TROOPERINFO_5,
	DASHBOARD_TROOPERINFO_6,
	DASHBOARD_TROOPERINFO_7,

	DASHBOARD_AIRDROP_1,
	DASHBOARD_AIRDROP_2,
	DASHBOARD_AIRDROP_3,

	DASHBOARD_AIRSTRIKE_1,
	DASHBOARD_AIRSTRIKE_2,
	DASHBOARD_AIRSTRIKE_3,

	DASHBOARD_RECON_1,
	DASHBOARD_RECON_2,
	DASHBOARD_RECON_3,

	DASHBOARD_ITEMSELECT_BACKGROUND,

	DASHBOARD_ITEMSELECT_1,
	DASHBOARD_ITEMSELECT_2,
	DASHBOARD_ITEMSELECT_3,
	DASHBOARD_ITEMSELECT_4,
	DASHBOARD_ITEMSELECT_5,
	DASHBOARD_ITEMSELECT_6,
	DASHBOARD_ITEMSELECT_7,
	DASHBOARD_ITEMSELECT_8,
	DASHBOARD_ITEMSELECT_9,
	DASHBOARD_ITEMSELECT_10,
	DASHBOARD_ITEMSELECT_11,
	DASHBOARD_ITEMSELECT_12,
	DASHBOARD_ITEMSELECT_13,
	DASHBOARD_ITEMSELECT_14,
	DASHBOARD_ITEMSELECT_15,
	DASHBOARD_ITEMSELECT_16,
	DASHBOARD_ITEMSELECT_17,
	DASHBOARD_ITEMSELECT_18,

	DASHBOARD_SPECIALITEM,


	DASHBOARD_LAST			//terminates list
	
} DASHBOARD_GADGETS;


typedef struct
{
	GADGET *dashboard_gadgets[DASHBOARD_LAST];
	int numbuttons;

	ONSCREENBUTTON *buttons;


	SPRITE *dashboardsprite;
	SPOINT dashboardloc;

	int topborder; //used to quickly check whether a mouse click is on the dashboard

	BOOL graphics_loaded;

	SPRITE **sprites; //pointer to block of allocated sprites so we can free them later
	int numsprites;

	char curmessage[MESSAGE_COMP_MAXLENGTH+1];
	int curmessagelength;
	char *pcurmessage;
	BOOL texthasarrived;

	BOOL capturingkeys;


	char chunksActive[DASH_CHUNK_LAST];

} DASHBOARD;


typedef enum
{
	DASHBMP_START_UP,
	DASHBMP_START_DOWN,

	DASHBMP_MISSION_UP,
	DASHBMP_MISSION_DOWN,

	DASHBMP_PAUSE_UP,
	DASHBMP_PAUSE_DOWN,

	DASHBMP_LIGHT_GREENPLAYER_ON,
	DASHBMP_LIGHT_GREENPLAYER_OFF,
	DASHBMP_LIGHT_TANPLAYER_ON,
	DASHBMP_LIGHT_TANPLAYER_OFF,
	DASHBMP_LIGHT_BLUEPLAYER_ON,
	DASHBMP_LIGHT_BLUEPLAYER_OFF,
	DASHBMP_LIGHT_GRAYPLAYER_ON,
	DASHBMP_LIGHT_GRAYPLAYER_OFF,
	
	DASHBMP_SMALLLIGHT_GREEN,
	DASHBMP_SMALLLIGHT_YELLOW,
	DASHBMP_SMALLLIGHT_RED,
	
	DASHBMP_WEAPONICON_GRENADE,
	DASHBMP_WEAPONICON_FLAME,
	DASHBMP_WEAPONICON_BAZOOKA,
	DASHBMP_WEAPONICON_MORTAR,
	DASHBMP_WEAPONICON_AUTORIFLE,
	DASHBMP_WEAPONICON_RIFLE,
	DASHBMP_WEAPONICON_MINE,
	DASHBMP_WEAPONICON_BOMB,
	DASHBMP_WEAPONICON_MINESWEEPER,
	DASHBMP_WEAPONICON_MEDPACK,
	DASHBMP_WEAPONICON_FLAG,
	DASHBMP_WEAPONICON_GREENFLAG,
	DASHBMP_WEAPONICON_TANFLAG,
	DASHBMP_WEAPONICON_BLUEFLAG,
	DASHBMP_WEAPONICON_GRAYFLAG,

	DASHBMP_WEAPONSELECTCURSOR_ON,
	DASHBMP_WEAPONSELECTCURSOR_OFF,

	DASHBMP_VEHICLEICON_TANK,
	DASHBMP_VEHICLEICON_JEEP,
	DASHBMP_VEHICLEICON_HALFTRACK,
	DASHBMP_VEHICLEICON_CONVOY,

	DASHBMP_VEHICLEAMMOICON_TANK,
	DASHBMP_VEHICLEAMMOICON_OTHER,

	DASHBMP_ITEMICON_GRENADE,

	DASHBMP_AIRSUPPORT_ON,

	DASHBMP_ITEMSELECT_NONE,
	DASHBMP_ITEMSELECT_RIFLE,
	DASHBMP_ITEMSELECT_GRENADE,
	DASHBMP_ITEMSELECT_FLAME,
	DASHBMP_ITEMSELECT_BAZOOKA,
	DASHBMP_ITEMSELECT_MORTAR,
	DASHBMP_ITEMSELECT_JEEP,
	DASHBMP_ITEMSELECT_TANK,
	DASHBMP_ITEMSELECT_HALFTRACK,
	DASHBMP_ITEMSELECT_TRUCK,
	DASHBMP_ITEMSELECT_BACKGROUND,

	DASHBMP_GREENUP,
	DASHBMP_GREENDOWN,
	DASHBMP_TANUP,
	DASHBMP_TANDOWN,
	DASHBMP_BLUEUP,
	DASHBMP_BLUEDOWN,
	DASHBMP_GREYUP,
	DASHBMP_GREYDOWN,

	DASHBMP_ALLIANCEBACKGROUND,
	
	DASHBMP_MAIN,

	DASHBMP_SPECIALITEM_0,				// special items MUST be last in this list
	DASHBMP_SPECIALITEM_1,
	DASHBMP_SPECIALITEM_2,
	DASHBMP_SPECIALITEM_3,
	DASHBMP_SPECIALITEM_4,
	DASHBMP_SPECIALITEM_5,
	DASHBMP_SPECIALITEM_6,
	DASHBMP_SPECIALITEM_7,
	DASHBMP_SPECIALITEM_8,
	DASHBMP_SPECIALITEM_9,
	DASHBMP_SPECIALITEM_10,
	DASHBMP_SPECIALITEM_11,
	DASHBMP_SPECIALITEM_12,
	DASHBMP_SPECIALITEM_13,
	DASHBMP_SPECIALITEM_14,
	DASHBMP_SPECIALITEM_15,
	DASHBMP_SPECIALITEM_16,
	DASHBMP_SPECIALITEM_17,
	DASHBMP_SPECIALITEM_18,
	DASHBMP_SPECIALITEM_19,
	DASHBMP_SPECIALITEM_20,
	DASHBMP_SPECIALITEM_21,
	DASHBMP_SPECIALITEM_22,
	DASHBMP_SPECIALITEM_23,
	DASHBMP_SPECIALITEM_24,
	DASHBMP_SPECIALITEM_25,
	DASHBMP_SPECIALITEM_26,
	DASHBMP_SPECIALITEM_27,
	DASHBMP_SPECIALITEM_28,
	DASHBMP_SPECIALITEM_29,				// do not put anyting after this line

	DASHBMP_LAST
} DASHBMP_TYPE;


typedef struct
{
	GADGETTYPE whichtype;
	DASHBOARD_GADGETS whichgadget;
	DASH_CHUNK_TYPE whichchunk;

	DASHBMP_TYPE bmp1, bmp2;

	DASHBMP_TYPE *bmps1, *bmps2; //for multibuttons

	SPOINT onscreenloc;
	RECT hotspot;

	int aux1, aux2, aux3;
} DASHBOARD_ASSEMBLY_ELEMENT;






typedef struct
{
	DASHBMP_TYPE dashbmp;
	char *filename;
	BYTE whichsprite;
	long flags;
} ASSEMBLY_TRANS_ELEMENT; //used to set up a table which translates
						  //dashbmp enums into sprite pointers

#define TARGET_NONE 0
#define TARGET_OBJECT 1
#define TARGET_POINT 2

typedef struct
{
	BYTE target_type;
	ITEM *pObj;
	SPOINT spt;
	int importanttargetindex; //index into the list of important targets
						      //of the last such target selected
} GENERIC_TARGET;



typedef enum
{
	BAR_TYPE_GRENADE,
	BAR_TYPE_MORTAR,
	BAR_TYPE_LAST
} BARTYPE;


//stuff for the grenade/mortar launching bar
typedef struct
{
	int startingTime; //0 if currently inactive
	int retractDelay;		// wait before retracting cursor
	int color;
	int percent;

	BARTYPE curBarType;

	WEAPON_TYPE	rubberband;			// weapon type for rubberband effect

//	SPRITE barSprite[BAR_TYPE_LAST];

//	SPOINT spritePos;

//	RECT barRect;
} BARSTRUCT;


/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
extern DASHBOARD *curdashboard;
extern char UI_CurMode;
extern SPRITE *UI_Cursor;
extern SPOINT GunsightCursorPos;
extern UseAltGunsight;
extern UseAltMouseButton;

/////////////////////////////////////////////////////////////////////////////
// Function Prototypes
/////////////////////////////////////////////////////////////////////////////

extern	BYTE*	CreateShadeTable( int rLevel, int gLevel, int bLevel );		// level = 0-255

void FreeDashboard(void);
void DashboardUnloadGraphics(void);
int DashboardLoadGraphics(void);
void DashboardInit(void);
void Dashboard_Click(DASHBOARD *dashboard, CPoint *clickloc, int whichmousebutton);
void Dashboard_Draw(DASHBOARD *dashboard);
void Dashboard_DrawFront(DASHBOARD *dashboard);
void InGameLButtonDn(UINT nFlags, CPoint point);
void InGameLButtonUp(UINT nFlags, CPoint point);
void InGameRButtonDn(UINT nFlags, CPoint point);
void InGameRButtonUp(UINT nFlags, CPoint point);
void Dashboard_Update(void);
void receivechatmessage(char *message);
void ReceiveDashMessage(char *message, OBJECT *unit);
void PresentMissionMessage(char *message);
void MissionLoading( long nBytesRead, long nTotalBytes );
void changestartbuttontomissionbutton(void);
void lightallstartinglights(void);
void enableradar(void);
int NumHumanPlayers(void);
void SelectNextUnit(void);
void InitSargeView(SARGE* pSarge);

void UI_ProcessScreen(void);
void UI_SwitchMode( int jumptounit = 1 );
void UI_InitScreen(void);
void UI_PutItemBackInTray( void );
void UI_HitAttackKey(BOOL immediate);
void UI_HitDefendKey(BOOL immediate);
void UI_HitFollowKey(void);
void UI_GiveOrder(BOOL terminate);
void UI_HitToggleKey(void);
void UI_NextUnitKey(void);
void UI_HitAirDropKey(void);
void UI_HitAirStrikeKey(void);
void UI_HitReconKey(void);
void UI_EnterKey(void);
void UI_ChatKey(void);

void UI_LoadCursors(void);
void UI_FreeCursors(void);
void UI_SetCursor(CURSORTYPE newcursortype);
void UI_DrawCursors(void);
void UI_DrawCursorsFront(void);
void UI_CursorsOn(void);
void UI_CursorsOff(void);
void UI_PositionGunsight(void);

void InitUndeployedUnitInfo(void);
void endScrollingMode();
void initFiringBar(void);
void killFiringBar(void);
void turnOnFiringBar(BARTYPE curType);
int getFiringBarPercent(void);
int turnOffFiringBar(void);
void updateFiringBar( void );
void clearFiringBar( void );

void UI_TurnOffStrategoMode(void);
int ESC_Mode();

void	UI_MissionRecall(int whichbutton = 0);
void	UI_MapRecall(int whichbutton = 0);
void	releaserecalllfunc(int x,int y);
void	RecallInit( char *file = NULL );
void	MapRecallInit();

void ScriptBmp(char *file);

#endif