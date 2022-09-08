// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>
#include <afxpriv.h>
#include <objidl.h>         // TBD: do not include for vc++ 4.2
// 
// ASSERT_NEW is used after every call to new; can be used to
// throw a memory exception if need be.
//
#define ASSERT_NEW(ptr) ASSERT(ptr != NULL)