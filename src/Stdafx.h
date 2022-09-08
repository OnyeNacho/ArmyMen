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

#include <afxtempl.h>		//	Template stuff

// Windows system includes
#include <mmsystem.h>

// DirectX .h files
#include <dinput.h>
#include <ddraw.h>
#include <dsound.h>

// C library includes
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Army Men includes
#include "types.h"
#include "rmerror.h"
#include "Error.h"
#include "util.h"
#include "resource.h"
#include "Dd.h"
#include "globals.h"

#define ASSERT_NEW(ptr) ASSERT(ptr != NULL)