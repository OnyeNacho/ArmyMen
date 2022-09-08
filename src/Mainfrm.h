/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: Mainfrm.h $
//
//	DESCRIPTION:	interface of the CMainFrame class
//
//	AUTHOR:			Nicky Robinson
//
//	CREATED:		Monday, May 20, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Mainfrm.h 75    4/16/98 9:30p Nrobinso $
//
//	Copyright (C) 1996 The 3DO Company. All Rights Reserved.
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//  HISTORY
//
//  $Log: /ArmyMen/src/Mainfrm.h $
//  
//  75    4/16/98 9:30p Nrobinso
//  scripts trace on/off with s key
//  
//  74    4/14/98 10:33a Bwilcox
//  switch playcycle to elapsed time printout,
//  optimize trooper no routing when fail on victim
//  
//  73    4/06/98 12:36p Dmaynard
//  Added Parameter to RestoreGame to ake sure my fixes for recovering from
//  Alt-Tab don't have any side effects in other cases of calling
//  restoregame.
//  
//  71    4/02/98 7:36p Nrobinso
//  dd surface 3
//  
//  70    3/22/98 6:08p Phu
//  fix parameter mismatch in rectintersect
//  
//  69    3/16/98 12:22a Nrobinso
//  add a second failure dialog
//  
//  68    3/13/98 11:34a Nrobinso
//  remove resert menu items
//  
//  67    3/13/98 10:39a Dmaynard
//  Added Windows Timer Messages to repaint Player names so that their
//  colors can reflect latency to that player. Green==low yellow==medium
//  red== high.
//  
//  66    3/07/98 10:46p Nrobinso
//  add dialog interface stuff
//  
//  65    3/05/98 2:17p Bwilcox
//  vis layer display
//  
//  64    2/26/98 6:02p Nrobinso
//  add AllScenariosVisible back
//  
//  63    2/26/98 4:06p Phu
//  removed profiling/ old draw map into deadcode
//  
//  62    2/26/98 2:44p Nrobinso
//  remove unused code
//  
//  61    2/11/98 10:44a Nrobinso
//  add joystick active menu item
//  
//  60    2/10/98 1:12p Nrobinso
//  remove absolute orientation
//  
//  59    2/05/98 8:21a Bwilcox
//  added new debug menu choices immobilefoe and bw4
//  
//  58    2/01/98 10:56p Nrobinso
//  removed old dialog code; use PROFILING_ACTIVE for profiling code
//  
//  57    1/20/98 4:21p Phu
//  test code for expanding ownership areas in mp
//  
//  56    1/14/98 8:38a Bwilcox
//  FULL CHEAT VIEW added to debug menu
//  
//  55    1/13/98 4:22p Bwilcox
//  force labeling  shift-z  d  l
//  
//  54    1/13/98 7:59a Bwilcox
//  put validation on the debug menu bar
//  
//  53    12/24/97 12:29p Aburgess
//  added ability to toggle "All Scenarios Visible" using Shift A.
//  
//  52    12/15/97 11:03a Bwilcox
//  moved SCRIPT_DEBUG stuff under debug menu control 
//  see TRACE Scripts
//  
//
// 10    6/25/96 9:54p Nrobins
// added history info
//
//  $Nokeywords:$
/////////////////////////////////////////////////////////////////////////////


#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__


//-----------------------------------------------------------------
// Timers                   Range : 5000 - 5999
//-----------------------------------------------------------------
#define IDT_FLIP            5000


#define DASH_HEIGHT 96 //obsolete from dash.h... defined here for lack of anywhere better to put it

#define NO_KEY		0x0
#define SHIFT_KEY	0x1
#define CTRL_KEY	0x2
#define ANY_KEY		0x3

// TBD: these are OEM specific
#define VK_LEFTBRACKET	0xBC
#define VK_RIGHTBRACKET	0xBE

/////////////////////////////////////////////////////////////////////////////
//					Window's message pump help...


// SKeyMsg
// modifier = modifier key (Ctrl or Shift)
// min_match = minimum nChar value to match.
// max_match = maximum nChar value to match.
// dispatcher = function to call if a match is found.
//
// Macros to help with SKeyMsg's:
//	DIS_KEY(p)			Disables key action while still matching the character which has the effect of disabling
//						keys later in other tables which might have matched or the defaults from working.
//	DIS_KEY_NOFX(p)		Disables key action while allowing other keys later to still match.
//	END_KEY_LIST		Defines the required information to terminate the SKeyMsg array.
//	EAT_KEY(k)			Defines a dummy entry which will prevent later matches from occuring, but will have
//						no effect on code execution.
//
// WARNING: The following macros will only operate on the last entry of an array.  The array name
//			must be passed in and it will modify the entry as is appropriate.  This entry must be
//			END_KEY_LIST.
//	TERM_KEY_LIST(p)	Changes a LABEL_KEY_LIST entry into an END_KEY_LIST entry.
//	LINK_KEY_LIST(p,l)	Changes a LABEL_KEY_LIST entry into a LNK_KEY_LIST entry.
#define DIS_KEY(p)			(p)->dispatcher=NULL
#define	DIS_KEY_NOFX(p)		(p)->min_match = ~0; (p)->max_match = 0

#define	END_KEY_LIST		{ (UINT)~0, (UINT)0, NULL }
#define EAT_KEY(k)			{ k, k, NULL }

#define TERM_KEY_LIST(p)	(p+sizeof(p)-sizeof(SKeyMsg))->dispatcher = NULL
#define LINK_KEY_LIST(p,l)	(p+sizeof(p)-sizeof(SKeyMsg))->dispatcher = (void(*)(UINT, UINT))((void*)(l))


extern int gGlobalPlacement;


typedef struct SKeyMsg {
	UINT	min_match;												// Minimum value to match message (inclusive).
	UINT	max_match;												// Maximum value to match message (inclusive).
	void	(*dispatcher)(UINT nChar, UINT nFlags);					// Dispatch function to call
	UINT	modifier;												// Modifier key (Ctrl or Shift)
} SKeyMsg;


typedef struct SUserInterface {
	void	(*m_pMLD)(UINT nFlags, CPoint point);				// state specific UI for Mouse left-button down events
	void	(*m_pMLU)(UINT nFlags, CPoint point);				// state specific UI for Mouse left-button up events
	void	(*m_pMRD)(UINT nFlags, CPoint point);				// state specific UI for Mouse right-button down events
	void	(*m_pMRU)(UINT nFlags, CPoint point);				// state specific UI for Mouse right-button up events
	void	(*m_pMMv)(UINT nFlags, CPoint point);				// state specific UI for Mouse movement events

	SKeyMsg	**m_pKDn;											// state specific UI for key down events
	SKeyMsg	**m_pKUp;											// state specific UI for key up events

	BOOL	(*m_pKOverride)(UINT key, BOOL down);				// state specific override key up or down
	BOOL	(*m_pKChar)(UINT character);						// state specific character input
} SUserInterface;

#define KEY_DOWN TRUE
#define KEY_UP FALSE
#define PREVIOUS_KEY_FLAG 0x4000

//-----------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------
void MainLoop( void );


class CMainFrame : public CFrameWnd
{
  // Public Constructor(s)/Destructor
public:
				CMainFrame();
	virtual	   ~CMainFrame();
	void		StartGame();


  // Public Methods
public:
	BOOL        Create(const CString& sTitle);
	HWND		GetHwnd();
	void		PauseFlip();
	void		UnPauseFlip();
	void		ForceFullScreen();
	void		PausePageFlip();
	void		UnPausePageFlip();
	void		OnMusicToggle();
	void		OnSfxToggle();
	void		OnGamePauseToggle();
	void		WindowReset();
	UINT		GetBPP();						// GET Bits Per Pixel
	void		SetBPP(UINT bpp);				// SET Bits Per Pixel
SUserInterface* SetUI(SUserInterface *pUI);		// set the user-interface
	void		SetUIKeyDn(SKeyMsg	**pKDn);
	void		SetUIKeyUp(SKeyMsg	**pKUp);
	void		SetUIOverride(BOOL (*pOverride)(UINT key, BOOL down));				// set the user-interface overrdie
	void		SetUICharHandler(BOOL (*pCharHandler)(UINT character));
	BOOL		IsMultiPlayer(); 
	int			OnGameSetupDialog(); 
	int			OnServiceProviderDialog();
	int			OnErrorDialog(const char *string, BOOL parentDialog = TRUE);
	int			OnErrorDialog2(const char *string, BOOL parentDialog = TRUE);
	void		UpdateView();
	BOOL		RestoreGame(BOOL InitScreens);

  // Protected Methods
protected:					// Public?
	BOOL		DirectDrawInit();
	void		DirectDrawExit();
	void		DirectDrawFree();
	RECT		SetupWindow();
	void		ResetWindow();
	BOOL		FindKeyMsg(SKeyMsg *pKeys, UINT nChar, UINT nFlags);
	UINT		TranslateKeypad(UINT nChar, UINT nFlags);

 public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL


// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	// Private Data
private:
	UINT nGameBPP;						// the bpp we want
	SIZE nGameSize;						// game is this size maximum
	LPDIRECTDRAWCLIPPER pClipper;		// window clipping structure

	void	(*m_pMseLBtnDn)(UINT nFlags, CPoint point);
	void	(*m_pMseLBtnUp)(UINT nFlags, CPoint point);
	void	(*m_pMseRBtnDn)(UINT nFlags, CPoint point);
	void	(*m_pMseRBtnUp)(UINT nFlags, CPoint point);
	void	(*m_pMseMove)(UINT nFlags, CPoint point);

	BOOL	(*m_pKeyOverride)(UINT key, BOOL down);	// state specific override key up/down
	BOOL	(*m_pCharHandler)(UINT character);		// state specific character input handler

	SKeyMsg	**m_pKeyDn;
	SKeyMsg	**m_pKeyUp;

	// Public Data
public:
	PALETTE GamePalette;				// main game palette
	PALETTE AlternatePalette;			// an alternate game palette (for mainbase, into, etc.)
	SIZE nMaxSize;						// Window (incl. menus) is this size maximum
	BOOL	bPausePageFlip;
	BOOL	m_bScenariosVisible;
	int		modifier_keys;
	UINT    m_EventTimerID;

  // Message Handler Methods
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int	OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnClose();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFrameTime();
	afx_msg void OnUpdateSetFrameTime(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTemporary(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAvenue(CCmdUI* pCmdUI);
	afx_msg void OnContour();
	afx_msg void OnUpdateContour(CCmdUI* pCmdUI);
	afx_msg void OnCommander();
	afx_msg void OnUpdateCommander(CCmdUI* pCmdUI);
	afx_msg void OnFakeunits();
	afx_msg void OnUpdateFakeunits(CCmdUI* pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRunWindowed();
	afx_msg void OnUpdateRunWindowed(CCmdUI* pCmdUI);
	afx_msg void OnBothai();
	afx_msg void OnUpdateBothai(CCmdUI* pCmdUI);
	afx_msg void OnRouting();
	afx_msg void OnUpdateRouting(CCmdUI* pCmdUI);
	afx_msg void OnSingletrooper();
	afx_msg void OnUpdateSingletrooper(CCmdUI* pCmdUI);
	afx_msg void OnRandom();
	afx_msg void OnUpdateRandom(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePads(CCmdUI* pCmdUI);
	afx_msg void OnFog();
	afx_msg void OnUpdateFog(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBitpads(CCmdUI* pCmdUI);
	afx_msg void OnBw01();
	afx_msg void OnUpdateScriptdebug(CCmdUI* pCmdUI);
	afx_msg void OnLabel();
	afx_msg void OnUpdateLabel(CCmdUI* pCmdUI);
	afx_msg void OnBw1();
	afx_msg void OnUpdateBw1(CCmdUI* pCmdUI);
	afx_msg void OnBw2();
	afx_msg void OnUpdateBw2(CCmdUI* pCmdUI);
	afx_msg void OnBw3();
	afx_msg void OnUpdateBw3(CCmdUI* pCmdUI);
	afx_msg void OnBw4();
	afx_msg void OnUpdateBw4(CCmdUI* pCmdUI);
	afx_msg void OnNoCdOk();
	afx_msg void OnUpdateNoCdOk(CCmdUI* pCmdUI);
	//}}AFX_MSG

public:
	afx_msg void OnScriptdebug();
	afx_msg void OnAllScenariosVisible();
	afx_msg void OnTemporary();
	afx_msg void OnAvenue();
	afx_msg void OnPads();
	afx_msg void OnBitpads();
	afx_msg void OnBw02();
	afx_msg void OnTimer(UINT);

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CMainFrame)
};


/////////////////////////////////////////////////////////////////////////////
//					User-defined windows' messages


typedef enum tagMainFrm {
	MF_FIRST_MSG = WM_USER,

	// AVIVIDEO.H messages to the main window...
	AVIVID_EJECTED = MF_FIRST_MSG,	// the clip has finished
	AVIVID_REPLACED,				// another clip has started over previously running clip
	AVIVID_NOT_STARTED,				// signal that the AVI clip didn't start

	MF_LAST_MSG
};
#define MF_MSG_COUNT	(MF_LAST_MSG-MF_FIRST_MSG)


//-----------------------------------------------------------------
// Externals
//-----------------------------------------------------------------


extern	CMainFrame			   *pMainFrame;			// a pointer to the CMainFrame object.
extern	LPDIRECTDRAWSURFACE3	pBackBufferPL;		// the off screen buffer (same as back buffer, but used for PageLocks)
extern	LPDIRECTDRAWSURFACE		pBackBuffer;		// the off screen buffer (for creation/destruction only)
extern	LPDIRECTDRAWSURFACE		pFrontBuffer;		// the front screen buffer


extern	RECT					rcWindowScreen;	// Rectangle of window in screen coordinates
extern	RECT					rcBackWindow;	// Rectangle of back window in window coordinates
extern	RECT					rcGameWindow;	// Rectangle of back window in use in window coordinates
extern	RECT					rcWindow;		// Rectangle of window in window coordinates


extern	SBOX					DisplayBox;			// Area of world displayed
extern	LPDIRECTDRAWSURFACE		pTileBuffer;

#ifndef FINAL
extern	LPDIRECTDRAWSURFACE		pDebugBuffer;
#endif

extern long nSec,nMilliSec;


extern	UINT					uiTimerID;			// user interrupt timer ID

extern char 					onePlayer;			// one player game
extern  BOOL					bWaitForSurfaceRestore;		// don't do anything until we have our surfaces back

//===========================================================================
//					External Prototypes
//===========================================================================
extern	void	KDn_TadValidateToggle(UINT nChar, UINT nFlags);
extern	void	KDn_MusicToggle(UINT nChar, UINT nFlags);
extern	void	KDn_SfxToggle(UINT nChar, UINT nFlags);

/////////////////////////////////////////////////////////////////////////////
#endif

