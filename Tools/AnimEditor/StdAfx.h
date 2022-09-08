// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>		//	Template stuff

#include <afxole.h>			//	OLE stuff

#ifdef USE_DATABASE
#include <afxdao.h>			//	DAO stuff
#endif

#define new DEBUG_NEW

#define ASSERT_NEW(ptr) ASSERT(ptr != NULL)

