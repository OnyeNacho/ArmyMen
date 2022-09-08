# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Autorun - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Autorun - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Autorun - Win32 Release" && "$(CFG)" !=\
 "Autorun - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Autorun.mak" CFG="Autorun - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Autorun - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Autorun - Win32 Debug" (based on "Win32 (x86) Application")
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
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "Autorun - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\Autorun.exe"

CLEAN : 
	-@erase ".\WinRel\Autorun.exe"
	-@erase ".\WinRel\mainwnd.obj"
	-@erase ".\WinRel\autorun.obj"
	-@erase ".\WinRel\autorun.res"
	-@erase ".\WinRel\commfunc.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/autorun.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Autorun.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "\MSTOOLS\INCLUDE" /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/autorun.res" /i "\MSTOOLS\INCLUDE" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Autorun.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib vfw32.lib winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib vfw32.lib winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Autorun.pdb" /machine:I386 /out:"$(OUTDIR)/Autorun.exe" 
LINK32_OBJS= \
	".\WinRel\mainwnd.obj" \
	".\WinRel\autorun.obj" \
	".\WinRel\commfunc.obj" \
	".\WinRel\autorun.res"

"$(OUTDIR)\Autorun.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Autorun - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\Autorun.exe"

CLEAN : 
	-@erase ".\WinDebug\Autorun.exe"
	-@erase ".\WinDebug\mainwnd.obj"
	-@erase ".\WinDebug\autorun.obj"
	-@erase ".\WinDebug\autorun.res"
	-@erase ".\WinDebug\commfunc.obj"
	-@erase ".\WinDebug\Autorun.ilk"
	-@erase ".\WinDebug\Autorun.pdb"
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\vc40.idb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/autorun.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Autorun.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "\MSTOOLS\INCLUDE" /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/autorun.res" /i "\MSTOOLS\INCLUDE" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Autorun.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib vfw32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib vfw32.lib winmm.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Autorun.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Autorun.exe" 
LINK32_OBJS= \
	".\WinDebug\mainwnd.obj" \
	".\WinDebug\autorun.obj" \
	".\WinDebug\commfunc.obj" \
	".\WinDebug\autorun.res"

"$(OUTDIR)\Autorun.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Autorun - Win32 Release"
# Name "Autorun - Win32 Debug"

!IF  "$(CFG)" == "Autorun - Win32 Release"

!ELSEIF  "$(CFG)" == "Autorun - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\mainwnd.cpp
DEP_CPP_MAINW=\
	".\commfunc.h"\
	".\mainwnd.h"\
	

"$(INTDIR)\mainwnd.obj" : $(SOURCE) $(DEP_CPP_MAINW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\autorun.cpp
DEP_CPP_AUTOR=\
	".\commfunc.h"\
	".\mainwnd.h"\
	

"$(INTDIR)\autorun.obj" : $(SOURCE) $(DEP_CPP_AUTOR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\autorun.rc
DEP_RSC_AUTORU=\
	".\ICON1.ICO"\
	

"$(INTDIR)\autorun.res" : $(SOURCE) $(DEP_RSC_AUTORU) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\commfunc.cpp
DEP_CPP_COMMF=\
	".\commfunc.h"\
	

"$(INTDIR)\commfunc.obj" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
