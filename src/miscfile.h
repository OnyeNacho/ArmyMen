//========================================================================
//	FILE:			$Workfile: miscfile.h $
//
//	DESCRIPTION:	Miscellaneous file system functions.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		Thursday, September 19, 1996
//
//	REVISION:		$Header: /ArmyMen/src/miscfile.h 17    4/08/98 8:06p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
//=========================================================================
//  HISTORY
//
//  $Log: /ArmyMen/src/miscfile.h $
//  
//  17    4/08/98 8:06p Nrobinso
//  remove winlose path
//  
//  15    3/25/98 7:52p Nrobinso
//  save path
//  
//  14    3/25/98 6:27p Nrobinso
//  add a winlose path
//  
//  13    3/18/98 4:00a Nrobinso
//  fix spelling of grey folder
//  
//  12    3/12/98 6:07a Bwilcox
//  loadobjects is now a fullly supported subdirectory of runtime, optional
//  like audio
//  
//  11    3/11/98 9:33a Aburgess
//   new screen color-related paths
//  
//  10    3/07/98 10:46p Nrobinso
//  switch to CStrings
//  
//  9     2/06/98 11:02a Nrobinso
//  add cd-rom check and cd name
//  
//  8     2/02/98 1:01p Aburgess
//  modifications made to support new mission briefing references through
//  campaign.cpn
//  
//  7     2/01/98 5:45p Nrobinso
//  remove TESTPATH
//  
//  6     1/26/98 12:05p Nrobinso
//  new path defines
//  
//  5     12/09/97 12:12p Phu
//  
//  4     11/20/97 11:34a Nrobinso
//  add SetPAth
//  
//  3     11/18/97 10:31a Aburgess
//  corrected path specifications to be relative to BASE_WORK_PATH. Added
//  class function to miscfile (cdPath) that changes based on starting from
//  BASE_WORK_PATH
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  6     4/30/97 7:43p Nrobinso
//  add a DefaultPath() function
//  
//  5     97-01-16 10:21 Ereich
//  Finally got the new state machine working.  Subtleties in the
//  transition from the old state to the new cost me many hours.
//  
//  4     96-09-26 14:36 Ereich
//  Added BASE_WORK_PATH and TEST_PATH which can be used in path selection.
//  
//  3     96-09-25 13:04 Ereich
//  Completed first pass of the InstallPaths class.  The cdRegPath() can
//  now be used in place of _chdir(). gPaths is the name of the global
//  which should be used.
//  
//  2     96-09-19 13:02 Ereich
//  Added LocateCdromDrive().
//  
//  1     96-09-19 9:38 Ereich
//  Initial header for miscellaneous file system support.
//
//  $Nokeywords:$
//=========================================================================

#ifndef __MISCFILE_H__
#define __MISCFILE_H__

#ifdef _DEBUG
#define ODS( a ) OutputDebugString( a )
#else
#define ODS( a )
#endif

//=========================================================================
//						GLOBAL DEFINES
//=========================================================================
#define LCD_NO_ERROR		0	// there is no error
#define LCD_NO_DRIVE		1	// no CD-ROM drive can be located
#define LCD_MISSING_VOLUME	2	// a CD-ROM drive has been found, but the volume doesn't

#define	BASE_WORK_PATH		"./"	// default working path

#define CAMPAIGN_PATH		"Campaigns"
#define AUDIO_PATH			"Audio"
#define SCREEN_PATH			"Screens"
#define BRIEFS_PATH			"Screens/Briefs"
#define SCREEN_GREEN_PATH	"Screens/Green"
#define SCREEN_TAN_PATH		"Screens/Tan"
#define SCREEN_BLUE_PATH	"Screens/Blue"
#define SCREEN_GRAY_PATH	"Screens/Grey"
#define MAP_PATH			"Maps"
#define FLASH_PATH			"LoadObjects/Flash"
#define BODYPARTS_PATH		"LoadObjects/BodyParts"
#define CURSOR_PATH			"LoadObjects/Cursors"
#define DASH_PATH			"LoadObjects/Dashboard"
#define STRATMAP_PATH		"StratMap"
#define SAVE_PATH			"SaveGames"


//=========================================================================
//						GLOBAL DATA TYPES
//=========================================================================
struct PathLink
{
	PathLink*	next;								// pointer to the next path in list (NULL== end-of-list)
	PathLink*	prev;								// pointer to the previous path in list (NULL== beginning-of-list)
	int			rpath_len;							// length of rpath
	CString		rpath;
	int			fpath_len;							// length of fpath
	CString		fpath;								// full valid path string (NULL-string== invalid path)
};

class InstallPaths
{
	// Public Constructor(s)/Destructor
public:
				InstallPaths(LPCSTR szVolume=NULL);	// default to no volume label
			   ~InstallPaths();

	// Public Methods
public:
	LPCSTR		RegisterPath(LPCSTR szRelPath);		// returns a pointer to the full valid path (NULL= invalid path)
	BOOL		UnregisterPath(LPCSTR szRelPath);	// returns that the valid path was properly destroyed
	DWORD		LocateCdromDrive(LPCSTR szVolume = NULL);	// locates the CD-ROM drive
	DWORD		CdromPresent(){return cd_present;}
	void		DumpPaths();						// dump the paths to the debugging window...
	void		OnlyRegisterCD() {force_cd= TRUE;};	// force the use of the CD-ROM drive
	void		RegisterBoth() {force_cd= FALSE;};	// return to normal registration which prefers the hard drive
	LPCSTR		cdRegPath(LPCSTR szRelPath);		// returns a pointer to the full valid path (NULL= invalid path)
	LPCSTR		cdPath(LPCSTR szRelPath);			// returns a pointer to the full valid path, relative to BASE_WORK_PATH (NULL= invalid path)

	// Private Methods
private:
	PathLink*	FindPath(LPCSTR szRelPath);			// locate a previously registered path (NULL== couldn't find)
	BOOL		ValidPath(PathLink* path);			// validate the path passed
	void		FixPath(CString &szRelPath);			// make slashes consistent and make sure it ends with a slash
	BOOL		FindRelPath(CString &base, PathLink* path);	// find a relative path


  // Public Data
public:
	CString		cd_path;
	CString		hd_path;
	const char	*m_current_path;		

  // Private Data
private:
	DWORD		cd_present;
	PathLink*	path_head;							// pointer to the beginning of the path list chain.
	PathLink*	path_tail;							// pointer to the end of the path list chain.
	BOOL		force_cd;							// flag to always use the CD when registering paths.
	CString		m_szVolume;
};



//=========================================================================
//						GLOBAL VARIABLES
//=========================================================================

extern InstallPaths gPaths, *gpPaths;				// global path management...


//=========================================================================
//						GLOBAL PROTOTYPES
//=========================================================================

extern	void SetPath(char *path);

#endif		// __MISCFILE_H__

//=========================================================================
//								EOF
//=========================================================================
