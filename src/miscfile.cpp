/////////////////////////////////////////////////////////////////////////////
//	FILE:			$Workfile: miscfile.cpp $
//
//	DESCRIPTION:	Miscellaneous file system functions.
//
//	AUTHOR:			Edwin W. Reich
//
//	CREATED:		Thursday, September 19, 1996
//
//	REVISION:		$Header: /ArmyMen/src/miscfile.cpp 15    4/02/98 3:21p Phu $
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
//  $Log: /ArmyMen/src/miscfile.cpp $
//  
//  15    4/02/98 3:21p Phu
//  typecast to avoid warnings
//  
//  14    3/18/98 4:00a Nrobinso
//  keep a pointer to current directory name
//  
//  13    3/16/98 12:24a Nrobinso
//  do a case insensitive compare on the cd volume name
//  
//  12    3/09/98 11:26a Nrobinso
//  check for running off the cd
//  
//  11    3/07/98 10:42p Nrobinso
//  maintain paths a cstrings
//  
//  10    2/06/98 11:02a Nrobinso
//  add cd-rom check and cd name
//  
//  9     2/02/98 1:01p Aburgess
//  modifications made to support new mission briefing references through
//  campaign.cpn
//  
//  8     1/26/98 12:01p Nrobinso
//  remove DefaultPath
//  
//  7     1/22/98 6:44p Nrobinso
//  use SetPath
//  
//  6     12/09/97 12:12p Phu
//  
//  5     12/01/97 6:22p Nrobinso
//  turn off trace
//  
//  4     11/20/97 11:28a Nrobinso
//  add SetPath
//  
//  3     11/18/97 10:31a Aburgess
//  corrected path specifications to be relative to BASE_WORK_PATH. Added
//  class function to miscfile (cdPath) that changes based on starting from
//  BASE_WORK_PATH
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  7     4/30/97 7:43p Nrobinso
//  add a DefaultPath() function
//  
//  6     11/13/96 12:42p Nrobinso
//  moved direct.h to stdafx
//  
//  5     96-09-26 14:35 Ereich
//  
//  4     96-09-25 13:37 Ereich
//  Added a debugging message to indicate where the hard drive and CD drive
//  paths are pointed.
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
//  Initial version of miscellaneous file system support.
//
//  $Nokeywords:$
//=========================================================================

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "miscfile.h"		// miscellaneous file support functions
#include "gameflow.h"		// miscellaneous file support functions

// Debugging support
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//					Global Variables
/////////////////////////////////////////////////////////////////////////////

InstallPaths gPaths("ARMYMEN");								// global path management...

 
/////////////////////////////////////////////////////////////////////////////
//					Local Variables
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//					Global Prototypes
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

InstallPaths::InstallPaths(LPCSTR szVolume)
{
	char path[MAX_PATH];

	m_szVolume = szVolume;
	LocateCdromDrive(m_szVolume);		// valid CD-ROM drive string, (NULL-string== invalid CD-ROM)
	_getcwd(path, sizeof(path));		// valid hard drive string.
	hd_path = path;
	path_head = path_tail = NULL;		// pointers to the path list chain.

	if (_strnicmp(cd_path, path, 3) == 0)	// running off the cd
		gpGame->cdBoot = TRUE;

//	TRACE( "hd_path = \"%s\", cd_path = \"%s\"\n", hd_path, cd_path );
}

InstallPaths::~InstallPaths()
{
	PathLink *path, *next;
	int count = 0;

	ASSERT( !((path_head && !path_tail) || (!path_head && path_tail)) );	// if only one is NULL, then there is a problem

	// free each path link in the list
	path = path_head;
	while(path) {
		next = path->next;				// make sure we know where the next path link is before we free this path link
		delete path;
		path = next;
		count++;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Public Methods


// Register a path.
//
// Entry:
//		szRelPath = pointer to the relative path to register.
// Exit:
//		Returns a pointer to a copy of the full path.
//
// Notes:
//		The relative path must not contain wild-card characters.
//		The full path returned will have a trailing '/'.
LPCSTR InstallPaths::RegisterPath(LPCSTR szRelPath)
{
	PathLink* path;

	ASSERT( !((path_head && !path_tail) || (!path_head && path_tail)) );	// if only one is NULL, then there is a problem

	if(path=FindPath(szRelPath)) {					// yes, I do want an assignment
		return(path->fpath);
	}

	// Initialize the path link
	path = new PathLink;
//	path = (PathLink*) malloc(sizeof(PathLink));

	path->rpath = szRelPath;
	FixPath(path->rpath);
	path->rpath_len = path->rpath.GetLength();
	ValidPath(path);								// EWR, later do some error handling here...

	if(path_tail) {
		path_tail->next = path;
	} else {
		path_head = path;							// path_head && path_tail can only be NULL at the same time
	}
	path->prev = path_tail;
	path->next = NULL;
	path_tail = path;

	return(path->fpath);
}


// Unregister a path.
//
// Entry:
//		szRelPath = pointer to the relative path to unregister.
// Exit:
//		Returns the truth of the deletion.
//
// Notes:
//		The relative path must not contain wild-card characters.
//		The relative path must have a trailing '/'.
BOOL InstallPaths::UnregisterPath(LPCSTR szRelPath)
{
	PathLink* path;

	ASSERT( !((path_head && !path_tail) || (!path_head && path_tail)) );	// if only one is NULL, then there is a problem

	if(!(path=FindPath(szRelPath))) {					// yes, I do want an assignment
		return(FALSE);
	}


	// Delete the path link
	if(path==path_head) {
		path_head = path->next;
	}
	if(path==path_tail) {
		path_tail = path->prev;
	}
	if(path->prev) {
		path->prev->next = path->next;
	}
	if(path->next) {
		path->next->prev = path->prev;
	}

	delete path;												// discard the memory for the path link

	return(TRUE);

}


// Dump the paths.
//
// Entry:
// Exit:
// Notes:
void InstallPaths::DumpPaths()
{
	PathLink *path;
	int link;

	ASSERT( !((path_head && !path_tail) || (!path_head && path_tail)) );	// if only one is NULL, then there is a problem

	// dump each path link in the list
	path= path_head;
	link= 0;
	while(path) {
		TRACE( "%3d @%08lX: links= <%08lX, >%08lX, rpath[%3d]= \"%s\", fpath[%d]= \"%s\"\n", link, path, path->prev, 
			path->next, path->rpath_len, path->rpath, path->fpath_len, path->fpath );
		link++;
		path = path->next;
	}
}


// Locate a CD-ROM drive.
//
// Entry:
//		szVolume = pointer to the volume label of the CD (NULL= first CD-ROM drive located).
// Exit:
//		Returns LCD_NO_ERROR when there is no error.
//		Returns LCD_NO_DRIVE when no CD-ROM drive can be located.
//		Returns LCD_MISSING_VOLUME when a CD-ROM drive has been found, but the volume doesn't
//		match the "volume" parameter.
//
//		cd_path = buffer which contains the drive root string (NULL-string= !LCD_NO_ERROR).
//
// Notes:
//		LCD_MISSING_VOLUME will only be returned if there is at least one CD-ROM drive
//		and the volume label can't be matched.
DWORD InstallPaths::LocateCdromDrive(LPCSTR szVolume)
{
	LPSTR drive_buffer, root, drive_vol;
	DWORD drive_buffer_length, rval;
	LPCSTR volume = szVolume;

	if (volume == NULL)
		volume = (LPCSTR) m_szVolume;

	drive_buffer_length = GetLogicalDriveStrings(0, NULL);
	drive_buffer = (LPSTR) malloc(drive_buffer_length+1);
	GetLogicalDriveStrings(drive_buffer_length+1, drive_buffer);

	drive_vol = (LPSTR) malloc(MAX_PATH+1);
	// checking the drive list...
	rval = LCD_NO_DRIVE;					// default to no CD-ROM drive
	for(root = drive_buffer; *root && (rval != LCD_NO_ERROR); ) {
		if(GetDriveType(root) == DRIVE_CDROM) {
			if(volume && *volume) {
				if(GetVolumeInformation(root, drive_vol, MAX_PATH, NULL, NULL, NULL, NULL, 0)) {
					if(_stricmp(volume, drive_vol)) {
						rval = LCD_MISSING_VOLUME;
					} else {
						rval = LCD_NO_ERROR;
					}
				} else {
					rval = LCD_NO_DRIVE;
				}
			} else {						// the first CD-ROM drive found
				rval = LCD_NO_ERROR;
			}
		}			


		if(rval == LCD_NO_ERROR) {		// copy drive string...
			cd_path = root;
		}
		while(*root++) /* find the end of the string */	;
	}
	
	free(drive_buffer);
	free(drive_vol);
	cd_present = rval;

	return(rval);
}


// Change the directory to a registered path.
//
// Entry:
//		szRelPath = pointer to the relative path to register.
// Exit:
//		Returns a pointer to a copy of the full path.
//
// Notes:
//		The relative path must not contain wild-card characters.
//		The relative path must have a trailing '/'.
//		The full path returned will have a trailing '/'.
//		The path doesn't have to be pre-registered for this to work.
LPCSTR InstallPaths::cdRegPath(LPCSTR szRelPath)
{
	LPCSTR path = RegisterPath(szRelPath);
	m_current_path = path;
	if(path) {
		_chdir(path);
	}
	return(path);
}

LPCSTR InstallPaths::cdPath(LPCSTR szRelPath)
{
	LPCSTR path;

	cdRegPath(BASE_WORK_PATH);
	path = cdRegPath( szRelPath );

	return(path);
}

/////////////////////////////////////////////////////////////////////////////
// Private Methods


// Find a registered a path.
//
// Entry:
//		szRelPath = pointer to the relative path to find.
// Exit:
//		Returns a pointer to the PathLink.
//
// Notes:
//		The relative path must not contain wild-card characters.
//		The full path returned will have a trailing '\'.
PathLink* InstallPaths::FindPath(LPCSTR szRelPath)
{
	PathLink* path = path_head;				// get the head of the list
	CString find_path;
	int len;

	find_path = szRelPath;			// copy relative path to a buffer for manipulation
	FixPath(find_path);
	len = find_path.GetLength();

	while( path ) {
		if( len == path->rpath_len ) {			// if the path link is the same length then compare the paths
			if( find_path == path->rpath ) {
				break;
			}
		}

		path = path->next;						// get the next path
	}

	return(path);
}


// Determine whether the relative path can come from the hd_path or the cd_path.
//
// Entry:
//		path = pointer to path link to validate.
// Exit:
//		Returns TRUE if the path was found on either the hard drive or CD-ROM.
// Notes:
//		force_cd will cause the CD to always be used for directories.
BOOL InstallPaths::ValidPath(PathLink* path)
{

	if( !force_cd && FindRelPath(hd_path, path) ) {
		return(TRUE);
	} else {
		if( FindRelPath(cd_path, path) ) {
			return(TRUE);
		}
	} 

	path->fpath.SetAt(0, '\0');

	return(FALSE);
}


// Convert a relative path to a full path.
//
// Entry:
//		base = pointer to the base path (cd_path or hd_path).
//		path = pointer to path link to validate.
// Exit:
//		Returns TRUE if the path was found.
BOOL InstallPaths::FindRelPath(CString &base, PathLink* path)
{
	char mpath[MAX_PATH];
	char fpath[MAX_PATH];
	CFileFind valid_filefind;

	_makepath(mpath, NULL, (LPCSTR)base, (LPCSTR)path->rpath, NULL);
	_fullpath(fpath, (LPCSTR)mpath, _MAX_PATH);

	path->fpath = fpath;
	FixPath(path->fpath);
	path->fpath_len = path->fpath.GetLength();

	strcpy(mpath, fpath);
	strcat(mpath, "*.*");

	return(valid_filefind.FindFile(mpath, 0) && valid_filefind.FindNextFile());
}


// Fix a relative path string and make it consistent.
//
// Entry:
//		szRelPath = pointer to the relative path to find.
// Exit:
//		Modifies the path passed in, there must be room for a trailing slash to be added.
//
// Notes:
//		The relative path must not contain wild-card characters.
//		The path will be modified for consistency, especially to make searches easier.
//			All slashes will be forced to '/'.
//			A trailing slash will be added.
void InstallPaths::FixPath(CString &szRelPath)
{
	int c;
	int len = szRelPath.GetLength();

	// make the slashes consistent
	for( c=0; c<len; c++ ) {
		if(szRelPath[c] == '\\') {
			szRelPath.SetAt(c, '/');
		}
	}

	// add a trailing slash
	if( szRelPath[len-1] != '/' ) {
		szRelPath += "/";
	}
}


void SetPath(char *path)	{
	gPaths.cdRegPath(BASE_WORK_PATH);
	if (path)
		gPaths.cdRegPath(path);
}


//=========================================================================
//								EOF
//=========================================================================
