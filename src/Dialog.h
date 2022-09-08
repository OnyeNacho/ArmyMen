//========================================================================
//	FILE:			$Workfile: Dialog.h $
//
//	DESCRIPTION:	DIALOG type defines, structures, and prototypes.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, August 20, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Dialog.h 36    4/13/98 11:48a Dmaynard $
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
//  $Log: /ArmyMen/src/Dialog.h $
//  
//  36    4/13/98 11:48a Dmaynard
//  Disable Screen Savers when in Multi-Player MFC Dialogs
//  
//  34    3/16/98 12:22a Nrobinso
//  add a second failure dialog
//  
//  33    3/13/98 12:15p Dmaynard
//  Bug Fixes for JoinSession Dialog  on TCP/IP case.
//  
//  32    3/12/98 6:00p Dmaynard
//  Asynchronous update of available ArmyMen Sessions in the Select Battle
//  screen of the JoinSession Dialog.
//  
//  31    3/11/98 8:46p Dmaynard
//  Framework Added for enabling Asynchronous JoinSession Session scanning.
//  Everything in but the timer set-up, and still needs testing.
//  
//  30    3/09/98 5:24p Dmaynard
//  Fixing the storing and freeing of ServiceProvder Connection Buffers.
//  Also fixed bug in remembering the last used service provider in the
//  registry.
//  
//  29    3/07/98 10:46p Nrobinso
//  add OnMove's, new error dialog; remove unsued stuff
//  
//  28    2/26/98 2:44p Nrobinso
//  remove unused code
//  
//  27    2/17/98 5:21p Nrobinso
//  reduce  3 of cpn files
//  
//  26    2/07/98 5:12p Nrobinso
//  move dead code out
//  
//  25    12/10/97 11:02a Aburgess
//  added dialog handlers for getting the ServiceProvider type and the
//  session PlayerName and SessionName
//  
//  24    12/10/97 9:44a Aburgess
//  changes made to centralize REGKEY access. Also
//  fixes CANCEL or BACK in multiplayer connect
//  
//  23    12/09/97 12:12p Phu
//  
//  22    12/02/97 11:33a Aburgess
//  match reg keys
//  
//  21    11/17/97 10:01a Aburgess
//  added voices to audio diagnostic
//  
//  20    11/14/97 11:18a Aburgess
//  new exit button in audio diagnostics
//  
//  19    10/23/97 11:50a Dmaynard
//  Multi-PLayer removed doModal for Joiner
//  
//  18    10/22/97 6:38p Dmaynard
//  Adding Dummy Lobby States for gathering together all players before
//  starting game.
//  
//  17    10/20/97 1:53p Aburgess
//  removed OnGameStartOk
//  
//  15    9/30/97 11:29a Aburgess
//  Final changes to DIALOG representations of FullScreen UI
//  
//  14    9/29/97 3:41p Aburgess
//  lastest changes for DIALOG representations of FullScreen UI screens
//  
//  13    9/23/97 3:00p Aburgess
//  latest modifications for Dialog base version
//  
//  12    9/12/97 11:05a Aburgess
//  
//  11    9/12/97 9:50a Aburgess
//  Addition of AUDIO Diagnostic dialog
//  
//  10    9/11/97 2:12p Aburgess
//  new join session class functions
//  
//  9     9/11/97 10:55a Aburgess
//  removed debug asserts
//  
//  8     9/11/97 10:52a Aburgess
//  latest dialog changes
//  
//  7     9/09/97 8:34a Aburgess
//  latest changes to About and Team Credits dialogs
//  
//  6     9/04/97 3:29p Aburgess
//  another update to dialogs
//  
//  5     9/04/97 10:28a Aburgess
//  another update for cancel in GameOptions
//  
//  4     9/04/97 9:11a Aburgess
//  lastest changes for DIALOGs
//  
//  3     9/02/97 12:56p Aburgess
//  update to Slider/Edit in volume control
//  
//  2     9/02/97 9:41a Aburgess
//  new dialog classes
//  
//  $Nokeywords:$
///========================================================================

#ifndef __DIALOG_H__
#define __DIALOG_H__

//========================================================================
//						LOCAL DEFINES
//========================================================================
#define	DLG_MAX_FILENAME	63
#define	DLG_MAX_FILES		2

#define	DLG_JOIN_SESSION	FALSE
#define	DLG_HOST_SESSION	TRUE
#define	DLG_BUTTON_ON		BST_CHECKED
#define	DLG_BUTTON_OFF		BST_UNCHECKED
#define	DLG_BUTTON_GREY		BST_INDETERMINATE

#define	DLG_SFX_BUTTON		0
#define	DLG_STRM_BUTTON		1
#define	DLG_VOICE_BUTTON	2

#define	DLG_VOLUME_MIN		0			//   0 %
#define	DLG_VOLUME_HALF		50			//  50 %
#define	DLG_VOLUME_MAX		100			// 100 %

#define	DLG_SCALE_FREQUENCY	5

#define	DLG_CAMPAIGN_ID_BASE	10000
#define	DLG_SCENARIO_ID_BASE	 1000
#define	DLG_MISSION_ID_BASE		    1

#define ENUM_TIMER_EVENT		3
#define ENUM_TIMEOUT		10000

/////////////////////////////////////////////////////////////////////////////
// Dialog Initialization and Termination prototypes (GLOBAL)
void	DLGinit( void );
void	DLGexit( void );

typedef struct _SPCONTEXT
{
GUID		spGUID;
LPVOID		lpConnection;
DWORD		dwConnectionSize;
} SPCONTEXT, *LPSPCONTEXT;

typedef struct _TREEDATA
{
	GUID 	guid;
	DWORD	dwRefresh;
} TREEDATA,*LPTREEDATA;



/////////////////////////////////////////////////////////////////////////////
// CProviderDlg dialog

class CProviderDlg : public CDialog
{
// Construction
public:
	CProviderDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	int		m_ItemIndex;				// list item index number

	//{{AFX_DATA(CProviderDlg)
	enum { IDD = IDD_CHOOSEPROVIDER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProviderDlg)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProviderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnProviderSetupCancel();
	afx_msg void OnProviderSetupBack();
	afx_msg void OnProviderSetupNext();
	afx_msg void OnProviderSetupSelChange();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CConnectStatusDlg dialog

class CConnectStatusDlg : public CDialog
{
// Construction
public:
	CConnectStatusDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectStatusDlg)
	enum { IDD = IDD_CONNECT_STATUS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectStatusDlg)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConnectStatusDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGameSetupDlg dialog

class CGameSetupDlg : public CDialog
{
// Construction
public:
	CGameSetupDlg(CWnd* pParent = NULL);   // standard constructor

	int		OnSessionType();

// Dialog Data
	int		m_SessionType;				// host ot join session type
	BOOL	m_HostButton;				// host radio button state
	BOOL	m_JoinButton;				// join radio button state

	//{{AFX_DATA(CGameSetupDlg)
	enum { IDD = IDD_GAMESETUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameSetupDlg)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	int CGameSetupDlg::OnHostSessionDialog(); 
	int CGameSetupDlg::OnJoinSessionDialog();
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGameSetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnGameSetupCancel();
	afx_msg void OnGameSetupHostSession();
	afx_msg void OnGameSetupJoinSession();
	afx_msg void OnGameSetupNext();
	afx_msg void OnGameSetupBack();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CHostSessionDlg dialog

class CHostSessionDlg : public CDialog
{
// Construction
public:
	CHostSessionDlg(CWnd* pParent = NULL);   // standard constructor

	int OnSelectCampaignDialog();
	int OnMultiPlyrSelectCampaignDialog();

// Dialog Data
	//{{AFX_DATA(CHostSessionDlg)
	enum { IDD = IDD_HOSTSESSION };
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHostSessionDlg)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHostSessionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHostSessionBack();
	afx_msg void OnHostSessionNext();
	afx_msg void OnHostSessionCancel();
	afx_msg void OnHostSessionPlayerNameChange();
	afx_msg void OnHostSessionSessionNameChange();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CJoinSessionDlg dialog

class CJoinSessionDlg : public CDialog
{
// Construction
public:
	CJoinSessionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJoinSessionDlg)
	enum { IDD = IDD_JOINSESSION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJoinSessionDlg)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CJoinSessionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnJoinSessionCancel();
	afx_msg void OnJoinSessionBack();
	afx_msg void OnJoinSessionNext();
	afx_msg void OnTimer(UINT);
	afx_msg void OnJoinPlayernameUpdate();
	afx_msg void OnJoinSessionSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CAudioDiagnosticDlg dialog

class CAudioDiagnosticDlg : public CDialog
{
// Construction
public:
	CAudioDiagnosticDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	int		m_Button;
	int		m_ItemIndex;
	int		m_OldItemIndex;

	//{{AFX_DATA(CAudioDiagnosticDlg)
	enum { IDD = IDD_AUDIO_DIAGNOSTIC };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudioDiagnosticDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAudioDiagnosticDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAudioDiagnosticSfxGroup();
	afx_msg void OnAudioDiagnosticStreamGroup();
	afx_msg void OnAudioDiagnosticVoiceGroup();
	afx_msg void OnAudioDiagnosticPlayButton();
	afx_msg void OnAudioDiagnosticStopButton();
	afx_msg void OnAudioDiagnosticExitButton();
	afx_msg void OnAudioDiagnosticSelchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CHostLobby dialog

class CHostLobby : public CDialog
{
// Construction
public:
	CHostLobby(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHostLobby)
	enum { IDD = IDD_HOSTLOBBY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHostLobby)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHostLobby)
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CJoinLobby dialog

class CJoinLobby : public CDialog
{
// Construction
public:
	CJoinLobby(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJoinLobby)
	enum { IDD = IDD_JOINLOBBY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJoinLobby)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJoinLobby)
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CErrorDialog dialog

class CErrorDialog : public CDialog
{
// Construction
public:
	CErrorDialog(CWnd* pParent = NULL);   // standard constructor

	void SetString(const char *string);
	void Parent(BOOL parent) {bParent = parent;};

// Dialog Data
	//{{AFX_DATA(CErrorDialog)
	enum { IDD = IDD_ERROR_BOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString errstr;
	BOOL bParent;

	// Generated message map functions
	//{{AFX_MSG(CErrorDialog)
	afx_msg void OnMove(int x, int y);
	virtual BOOL OnInitDialog();
	afx_msg void OnRetry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CErrorDialog dialog

class CErrorDialog2 : public CDialog
{
// Construction
public:
	CErrorDialog2(CWnd* pParent = NULL);   // standard constructor

	void SetString(const char *string);
	void Parent(BOOL parent) {bParent = parent;};

// Dialog Data
	//{{AFX_DATA(CErrorDialog2)
	enum { IDD = IDD_ERROR_BOX2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorDialog2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString errstr;
	BOOL bParent;

	// Generated message map functions
	//{{AFX_MSG(CErrorDialog2)
	afx_msg void OnMove(int x, int y);
	virtual BOOL OnInitDialog();
	afx_msg void OnRetry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif __DIALOG_H__

//========================================================================
//							EOF
//========================================================================
/////////////////////////////////////////////////////////////////////////////
// ErrorBox2 dialog

class ErrorBox2 : public CDialog
{
// Construction
public:
	ErrorBox2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ErrorBox2)
	enum { IDD = IDD_ERROR_BOX2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ErrorBox2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ErrorBox2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
