# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=lookbm - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to lookbm - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "lookbm - Win32 Release" && "$(CFG)" != "lookbm - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "lookbm.mak" CFG="lookbm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lookbm - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "lookbm - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "lookbm - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "lookbm - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\Release\lookbm.exe"

CLEAN : 
	-@erase ".\Release\lookbm.exe"
	-@erase ".\Release\chgbm.obj"
	-@erase ".\Release\chgbm.pch"
	-@erase ".\Release\chgbm.res"
	-@erase ".\Release\chgbmDoc.obj"
	-@erase ".\Release\chgbmView.obj"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\StdAfx.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chgbm.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/chgbm.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chgbm.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/chgbm.pdb" /machine:I386 /out:"$(OUTDIR)/lookbm.exe" 
LINK32_OBJS= \
	".\Release\chgbm.obj" \
	".\Release\chgbm.res" \
	".\Release\chgbmDoc.obj" \
	".\Release\chgbmView.obj" \
	".\Release\ChildFrm.obj" \
	".\Release\MainFrm.obj" \
	".\Release\StdAfx.obj"

".\Release\lookbm.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\Debug\lookbm.exe"

CLEAN : 
	-@erase ".\Debug\lookbm.exe"
	-@erase ".\Debug\chgbm.ilk"
	-@erase ".\Debug\chgbm.obj"
	-@erase ".\Debug\chgbm.pch"
	-@erase ".\Debug\chgbm.pdb"
	-@erase ".\Debug\chgbm.res"
	-@erase ".\Debug\chgbmDoc.obj"
	-@erase ".\Debug\chgbmView.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chgbm.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/chgbm.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chgbm.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/chgbm.pdb" /debug /machine:I386 /out:"$(OUTDIR)/lookbm.exe" 
LINK32_OBJS= \
	".\Debug\chgbm.obj" \
	".\Debug\chgbm.res" \
	".\Debug\chgbmDoc.obj" \
	".\Debug\chgbmView.obj" \
	".\Debug\ChildFrm.obj" \
	".\Debug\MainFrm.obj" \
	".\Debug\StdAfx.obj"

".\Debug\lookbm.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "lookbm - Win32 Release"
# Name "lookbm - Win32 Debug"

!IF  "$(CFG)" == "lookbm - Win32 Release"

!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "lookbm - Win32 Release"

!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lookbm.cpp
DEP_CPP_CHGBM=\
	".\chgbm.h"\
	".\chgbmDoc.h"\
	".\chgbmView.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "lookbm - Win32 Release"


".\Release\chgbm.obj" : $(SOURCE) $(DEP_CPP_CHGBM) "$(INTDIR)"\
 ".\Release\chgbm.pch"


!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"


".\Debug\chgbm.obj" : $(SOURCE) $(DEP_CPP_CHGBM) "$(INTDIR)"\
 ".\Debug\chgbm.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "lookbm - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chgbm.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

".\Release\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Release\chgbm.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chgbm.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

".\Debug\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Debug\chgbm.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\chgbm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "lookbm - Win32 Release"


".\Release\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 ".\Release\chgbm.pch"


!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"


".\Debug\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 ".\Debug\chgbm.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\chgbm.h"\
	".\ChildFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "lookbm - Win32 Release"


".\Release\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 ".\Release\chgbm.pch"


!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"


".\Debug\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 ".\Debug\chgbm.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\chgbmDoc.cpp
DEP_CPP_CHGBMD=\
	".\chgbm.h"\
	".\chgbmDoc.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "lookbm - Win32 Release"


".\Release\chgbmDoc.obj" : $(SOURCE) $(DEP_CPP_CHGBMD) "$(INTDIR)"\
 ".\Release\chgbm.pch"


!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"


".\Debug\chgbmDoc.obj" : $(SOURCE) $(DEP_CPP_CHGBMD) "$(INTDIR)"\
 ".\Debug\chgbm.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\chgbmView.cpp
DEP_CPP_CHGBMV=\
	".\chgbm.h"\
	".\chgbmDoc.h"\
	".\chgbmView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "lookbm - Win32 Release"


".\Release\chgbmView.obj" : $(SOURCE) $(DEP_CPP_CHGBMV) "$(INTDIR)"\
 ".\Release\chgbm.pch"


!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"


".\Debug\chgbmView.obj" : $(SOURCE) $(DEP_CPP_CHGBMV) "$(INTDIR)"\
 ".\Debug\chgbm.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\chgbm.rc
DEP_RSC_CHGBM_=\
	".\res\chgbm.ico"\
	".\res\chgbm.rc2"\
	".\res\chgbmDoc.ico"\
	

!IF  "$(CFG)" == "lookbm - Win32 Release"


".\Release\chgbm.res" : $(SOURCE) $(DEP_RSC_CHGBM_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "lookbm - Win32 Debug"


".\Debug\chgbm.res" : $(SOURCE) $(DEP_RSC_CHGBM_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
