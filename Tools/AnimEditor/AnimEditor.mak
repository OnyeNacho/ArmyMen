# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=AnimEditor - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to AnimEditor - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "AnimEditor - Win32 Release" && "$(CFG)" !=\
 "AnimEditor - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "AnimEditor.mak" CFG="AnimEditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AnimEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AnimEditor - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "AnimEditor - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

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

ALL : "$(OUTDIR)\AnimEditor.exe" "$(OUTDIR)\AnimEditor.bsc"\
 "$(OUTDIR)\AnimEditor.hlp"

CLEAN : 
	-@erase "$(INTDIR)\AnimEditor.hlp"
	-@erase "$(INTDIR)\AnimEditor.obj"
	-@erase "$(INTDIR)\AnimEditor.pch"
	-@erase "$(INTDIR)\AnimEditor.res"
	-@erase "$(INTDIR)\AnimEditor.sbr"
	-@erase "$(INTDIR)\AnimEditorDoc.obj"
	-@erase "$(INTDIR)\AnimEditorDoc.sbr"
	-@erase "$(INTDIR)\AnimEditorView.obj"
	-@erase "$(INTDIR)\AnimEditorView.sbr"
	-@erase "$(INTDIR)\CActionRecord.obj"
	-@erase "$(INTDIR)\CActionRecord.sbr"
	-@erase "$(INTDIR)\CAnimEditorCommandLine.obj"
	-@erase "$(INTDIR)\CAnimEditorCommandLine.sbr"
	-@erase "$(INTDIR)\CCel.obj"
	-@erase "$(INTDIR)\CCel.sbr"
	-@erase "$(INTDIR)\CCelView.obj"
	-@erase "$(INTDIR)\CCelView.sbr"
	-@erase "$(INTDIR)\CDirectionRecord.obj"
	-@erase "$(INTDIR)\CDirectionRecord.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\CMultipleSequencesView.obj"
	-@erase "$(INTDIR)\CMultipleSequencesView.sbr"
	-@erase "$(INTDIR)\CNewHotSpotDialog.obj"
	-@erase "$(INTDIR)\CNewHotSpotDialog.sbr"
	-@erase "$(INTDIR)\CSequence.obj"
	-@erase "$(INTDIR)\CSequence.sbr"
	-@erase "$(INTDIR)\CSequenceCel.obj"
	-@erase "$(INTDIR)\CSequenceCel.sbr"
	-@erase "$(INTDIR)\CSequenceView.obj"
	-@erase "$(INTDIR)\CSequenceView.sbr"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.sbr"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CSpriteSequence.sbr"
	-@erase "$(INTDIR)\Dibitmap.obj"
	-@erase "$(INTDIR)\Dibitmap.sbr"
	-@erase "$(INTDIR)\Dibpal.obj"
	-@erase "$(INTDIR)\Dibpal.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(OUTDIR)\AnimEditor.bsc"
	-@erase "$(OUTDIR)\AnimEditor.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\common" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "ANIMEDITORDOC_VERSION" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\common" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "ANIMEDITORDOC_VERSION" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/AnimEditor.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/AnimEditor.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AnimEditor.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnimEditor.sbr" \
	"$(INTDIR)\AnimEditorDoc.sbr" \
	"$(INTDIR)\AnimEditorView.sbr" \
	"$(INTDIR)\CActionRecord.sbr" \
	"$(INTDIR)\CAnimEditorCommandLine.sbr" \
	"$(INTDIR)\CCel.sbr" \
	"$(INTDIR)\CCelView.sbr" \
	"$(INTDIR)\CDirectionRecord.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\CMultipleSequencesView.sbr" \
	"$(INTDIR)\CNewHotSpotDialog.sbr" \
	"$(INTDIR)\CSequence.sbr" \
	"$(INTDIR)\CSequenceCel.sbr" \
	"$(INTDIR)\CSequenceView.sbr" \
	"$(INTDIR)\CSpriteCatalog.sbr" \
	"$(INTDIR)\CSpriteSequence.sbr" \
	"$(INTDIR)\Dibitmap.sbr" \
	"$(INTDIR)\Dibpal.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\AnimEditor.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=version.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/AnimEditor.pdb" /machine:I386 /out:"$(OUTDIR)/AnimEditor.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AnimEditor.obj" \
	"$(INTDIR)\AnimEditor.res" \
	"$(INTDIR)\AnimEditorDoc.obj" \
	"$(INTDIR)\AnimEditorView.obj" \
	"$(INTDIR)\CActionRecord.obj" \
	"$(INTDIR)\CAnimEditorCommandLine.obj" \
	"$(INTDIR)\CCel.obj" \
	"$(INTDIR)\CCelView.obj" \
	"$(INTDIR)\CDirectionRecord.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\CMultipleSequencesView.obj" \
	"$(INTDIR)\CNewHotSpotDialog.obj" \
	"$(INTDIR)\CSequence.obj" \
	"$(INTDIR)\CSequenceCel.obj" \
	"$(INTDIR)\CSequenceView.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\Dibitmap.obj" \
	"$(INTDIR)\Dibpal.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\AnimEditor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

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

ALL : "$(OUTDIR)\AnimEditor.exe" "$(OUTDIR)\AnimEditor.bsc"\
 "$(OUTDIR)\AnimEditor.hlp"

CLEAN : 
	-@erase "$(INTDIR)\AnimEditor.hlp"
	-@erase "$(INTDIR)\AnimEditor.obj"
	-@erase "$(INTDIR)\AnimEditor.pch"
	-@erase "$(INTDIR)\AnimEditor.res"
	-@erase "$(INTDIR)\AnimEditor.sbr"
	-@erase "$(INTDIR)\AnimEditorDoc.obj"
	-@erase "$(INTDIR)\AnimEditorDoc.sbr"
	-@erase "$(INTDIR)\AnimEditorView.obj"
	-@erase "$(INTDIR)\AnimEditorView.sbr"
	-@erase "$(INTDIR)\CActionRecord.obj"
	-@erase "$(INTDIR)\CActionRecord.sbr"
	-@erase "$(INTDIR)\CAnimEditorCommandLine.obj"
	-@erase "$(INTDIR)\CAnimEditorCommandLine.sbr"
	-@erase "$(INTDIR)\CCel.obj"
	-@erase "$(INTDIR)\CCel.sbr"
	-@erase "$(INTDIR)\CCelView.obj"
	-@erase "$(INTDIR)\CCelView.sbr"
	-@erase "$(INTDIR)\CDirectionRecord.obj"
	-@erase "$(INTDIR)\CDirectionRecord.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\CMultipleSequencesView.obj"
	-@erase "$(INTDIR)\CMultipleSequencesView.sbr"
	-@erase "$(INTDIR)\CNewHotSpotDialog.obj"
	-@erase "$(INTDIR)\CNewHotSpotDialog.sbr"
	-@erase "$(INTDIR)\CSequence.obj"
	-@erase "$(INTDIR)\CSequence.sbr"
	-@erase "$(INTDIR)\CSequenceCel.obj"
	-@erase "$(INTDIR)\CSequenceCel.sbr"
	-@erase "$(INTDIR)\CSequenceView.obj"
	-@erase "$(INTDIR)\CSequenceView.sbr"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.sbr"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CSpriteSequence.sbr"
	-@erase "$(INTDIR)\Dibitmap.obj"
	-@erase "$(INTDIR)\Dibitmap.sbr"
	-@erase "$(INTDIR)\Dibpal.obj"
	-@erase "$(INTDIR)\Dibpal.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\AnimEditor.bsc"
	-@erase "$(OUTDIR)\AnimEditor.exe"
	-@erase "$(OUTDIR)\AnimEditor.ilk"
	-@erase "$(OUTDIR)\AnimEditor.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\common" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "ANIMEDITORDOC_VERSION" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\common" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "ANIMEDITORDOC_VERSION"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/AnimEditor.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/AnimEditor.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AnimEditor.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnimEditor.sbr" \
	"$(INTDIR)\AnimEditorDoc.sbr" \
	"$(INTDIR)\AnimEditorView.sbr" \
	"$(INTDIR)\CActionRecord.sbr" \
	"$(INTDIR)\CAnimEditorCommandLine.sbr" \
	"$(INTDIR)\CCel.sbr" \
	"$(INTDIR)\CCelView.sbr" \
	"$(INTDIR)\CDirectionRecord.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\CMultipleSequencesView.sbr" \
	"$(INTDIR)\CNewHotSpotDialog.sbr" \
	"$(INTDIR)\CSequence.sbr" \
	"$(INTDIR)\CSequenceCel.sbr" \
	"$(INTDIR)\CSequenceView.sbr" \
	"$(INTDIR)\CSpriteCatalog.sbr" \
	"$(INTDIR)\CSpriteSequence.sbr" \
	"$(INTDIR)\Dibitmap.sbr" \
	"$(INTDIR)\Dibpal.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\AnimEditor.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=version.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/AnimEditor.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/AnimEditor.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AnimEditor.obj" \
	"$(INTDIR)\AnimEditor.res" \
	"$(INTDIR)\AnimEditorDoc.obj" \
	"$(INTDIR)\AnimEditorView.obj" \
	"$(INTDIR)\CActionRecord.obj" \
	"$(INTDIR)\CAnimEditorCommandLine.obj" \
	"$(INTDIR)\CCel.obj" \
	"$(INTDIR)\CCelView.obj" \
	"$(INTDIR)\CDirectionRecord.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\CMultipleSequencesView.obj" \
	"$(INTDIR)\CNewHotSpotDialog.obj" \
	"$(INTDIR)\CSequence.obj" \
	"$(INTDIR)\CSequenceCel.obj" \
	"$(INTDIR)\CSequenceView.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\Dibitmap.obj" \
	"$(INTDIR)\Dibpal.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\AnimEditor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "AnimEditor - Win32 Release"
# Name "AnimEditor - Win32 Debug"

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AnimEditor.cpp
DEP_CPP_ANIME=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\AnimEditorView.h"\
	".\CActionRecord.h"\
	".\CAnimEditorCommandLine.h"\
	".\CDirectionRecord.h"\
	".\ChildFrm.h"\
	".\CSequenceCel.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AnimEditor.obj" : $(SOURCE) $(DEP_CPP_ANIME) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\AnimEditor.sbr" : $(SOURCE) $(DEP_CPP_ANIME) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\common" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "ANIMEDITORDOC_VERSION" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/AnimEditor.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\AnimEditor.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\common" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "ANIMEDITORDOC_VERSION"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/AnimEditor.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\AnimEditor.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\animeditor\AnimEditor.h"\
	".\CActionRecord.h"\
	".\CDirectionRecord.h"\
	".\CVersion.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

DEP_CPP_CHILD=\
	"..\animeditor\AnimEditor.h"\
	".\AnimEditorView.h"\
	".\CActionRecord.h"\
	".\CCelView.h"\
	".\CDirectionRecord.h"\
	".\ChildFrm.h"\
	".\CMultipleSequencesView.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

DEP_CPP_CHILD=\
	"..\animeditor\AnimEditor.h"\
	".\AnimEditorView.h"\
	".\CActionRecord.h"\
	".\CCelView.h"\
	".\CDirectionRecord.h"\
	".\ChildFrm.h"\
	".\CMultipleSequencesView.h"\
	".\CSequenceView.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AnimEditorDoc.cpp

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

DEP_CPP_ANIMED=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\AnimEditorView.h"\
	".\CActionRecord.h"\
	".\CDirectionRecord.h"\
	".\CMultipleSequencesView.h"\
	".\CSequenceView.h"\
	".\CSpriteCatalog.h"\
	".\CVersion.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AnimEditorDoc.obj" : $(SOURCE) $(DEP_CPP_ANIMED) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\AnimEditorDoc.sbr" : $(SOURCE) $(DEP_CPP_ANIMED) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

DEP_CPP_ANIMED=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\AnimEditorView.h"\
	".\CActionRecord.h"\
	".\CDirectionRecord.h"\
	".\CMultipleSequencesView.h"\
	".\CSequenceCel.h"\
	".\CSequenceView.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AnimEditorDoc.obj" : $(SOURCE) $(DEP_CPP_ANIMED) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\AnimEditorDoc.sbr" : $(SOURCE) $(DEP_CPP_ANIMED) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AnimEditorView.cpp

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

DEP_CPP_ANIMEDI=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\AnimEditorView.h"\
	".\CActionRecord.h"\
	".\CCelView.h"\
	".\CDirectionRecord.h"\
	".\CSequenceCel.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AnimEditorView.obj" : $(SOURCE) $(DEP_CPP_ANIMEDI) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\AnimEditorView.sbr" : $(SOURCE) $(DEP_CPP_ANIMEDI) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

DEP_CPP_ANIMEDI=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\AnimEditorView.h"\
	".\CCelView.h"\
	".\CSequenceCel.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AnimEditorView.obj" : $(SOURCE) $(DEP_CPP_ANIMEDI) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\AnimEditorView.sbr" : $(SOURCE) $(DEP_CPP_ANIMEDI) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AnimEditor.rc
DEP_RSC_ANIMEDIT=\
	".\arrow.cur"\
	".\res\AnimEditor.ico"\
	".\res\AnimEditor.rc2"\
	".\res\AnimEditorDoc.ico"\
	".\res\applydna.cur"\
	".\res\HSpot.bmp"\
	".\res\hspotpri.cur"\
	".\res\hspotprimary.bmp"\
	".\res\No_l.cur"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\AnimEditor.res" : $(SOURCE) $(DEP_RSC_ANIMEDIT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\hlp\AnimEditor.hpj

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=AnimEditor
InputPath=.\hlp\AnimEditor.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=AnimEditor
InputPath=.\hlp\AnimEditor.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CCel.cpp
DEP_CPP_CCEL_=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\CActionRecord.h"\
	".\CDirectionRecord.h"\
	".\CSequenceCel.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CCel.obj" : $(SOURCE) $(DEP_CPP_CCEL_) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CCel.sbr" : $(SOURCE) $(DEP_CPP_CCEL_) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dibitmap.cpp

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

DEP_CPP_DIBIT=\
	"..\animeditor\AnimEditor.h"\
	".\Bminfo.h"\
	".\CActionRecord.h"\
	".\CDirectionRecord.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\Dibpal.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Dibitmap.obj" : $(SOURCE) $(DEP_CPP_DIBIT) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\Dibitmap.sbr" : $(SOURCE) $(DEP_CPP_DIBIT) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

DEP_CPP_DIBIT=\
	"..\animeditor\AnimEditor.h"\
	".\Bminfo.h"\
	".\Dibitmap.h"\
	".\Dibpal.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Dibitmap.obj" : $(SOURCE) $(DEP_CPP_DIBIT) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\Dibitmap.sbr" : $(SOURCE) $(DEP_CPP_DIBIT) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dibpal.cpp
DEP_CPP_DIBPA=\
	".\Dibitmap.h"\
	".\Dibpal.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\Dibpal.sbr" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSequenceView.cpp
DEP_CPP_CSEQU=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\CActionRecord.h"\
	".\CCelView.h"\
	".\CDirectionRecord.h"\
	".\CMultipleSequencesView.h"\
	".\CSequenceCel.h"\
	".\CSequenceView.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CSequenceView.obj" : $(SOURCE) $(DEP_CPP_CSEQU) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CSequenceView.sbr" : $(SOURCE) $(DEP_CPP_CSEQU) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CMultipleSequencesView.cpp
DEP_CPP_CMULT=\
	"..\animeditor\AnimEditor.h"\
	".\CActionRecord.h"\
	".\CDirectionRecord.h"\
	".\CMultipleSequencesView.h"\
	".\CSequenceView.h"\
	".\CVersion.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CMultipleSequencesView.obj" : $(SOURCE) $(DEP_CPP_CMULT) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CMultipleSequencesView.sbr" : $(SOURCE) $(DEP_CPP_CMULT) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSequence.cpp
DEP_CPP_CSEQUE=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\CActionRecord.h"\
	".\CCelView.h"\
	".\CDirectionRecord.h"\
	".\CMultipleSequencesView.h"\
	".\CNewHotSpotDialog.h"\
	".\CSequenceCel.h"\
	".\CSequenceView.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CSequence.obj" : $(SOURCE) $(DEP_CPP_CSEQUE) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CSequence.sbr" : $(SOURCE) $(DEP_CPP_CSEQUE) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSequenceCel.cpp
DEP_CPP_CSEQUEN=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\CActionRecord.h"\
	".\CDirectionRecord.h"\
	".\CSequenceCel.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CSequenceCel.obj" : $(SOURCE) $(DEP_CPP_CSEQUEN) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CSequenceCel.sbr" : $(SOURCE) $(DEP_CPP_CSEQUEN) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CCelView.cpp

!IF  "$(CFG)" == "AnimEditor - Win32 Release"

DEP_CPP_CCELV=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\CActionRecord.h"\
	".\CCelView.h"\
	".\CDirectionRecord.h"\
	".\CSequenceView.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CCelView.obj" : $(SOURCE) $(DEP_CPP_CCELV) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CCelView.sbr" : $(SOURCE) $(DEP_CPP_CCELV) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ELSEIF  "$(CFG)" == "AnimEditor - Win32 Debug"

DEP_CPP_CCELV=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\CActionRecord.h"\
	".\CCelView.h"\
	".\CDirectionRecord.h"\
	".\CSequenceCel.h"\
	".\CSequenceView.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CCelView.obj" : $(SOURCE) $(DEP_CPP_CCELV) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CCelView.sbr" : $(SOURCE) $(DEP_CPP_CCELV) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CNewHotSpotDialog.cpp
DEP_CPP_CNEWH=\
	"..\animeditor\AnimEditor.h"\
	".\CActionRecord.h"\
	".\CDirectionRecord.h"\
	".\CNewHotSpotDialog.h"\
	".\CVersion.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CNewHotSpotDialog.obj" : $(SOURCE) $(DEP_CPP_CNEWH) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CNewHotSpotDialog.sbr" : $(SOURCE) $(DEP_CPP_CNEWH) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CAnimEditorCommandLine.cpp
DEP_CPP_CANIM=\
	".\CAnimEditorCommandLine.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CAnimEditorCommandLine.obj" : $(SOURCE) $(DEP_CPP_CANIM) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CAnimEditorCommandLine.sbr" : $(SOURCE) $(DEP_CPP_CANIM) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CActionRecord.cpp
DEP_CPP_CACTI=\
	".\CActionRecord.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CActionRecord.obj" : $(SOURCE) $(DEP_CPP_CACTI) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CActionRecord.sbr" : $(SOURCE) $(DEP_CPP_CACTI) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CDirectionRecord.cpp
DEP_CPP_CDIRE=\
	".\CDirectionRecord.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CDirectionRecord.obj" : $(SOURCE) $(DEP_CPP_CDIRE) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CDirectionRecord.sbr" : $(SOURCE) $(DEP_CPP_CDIRE) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSpriteSequence.cpp
DEP_CPP_CSPRI=\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\CSequenceCel.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\Dibitmap.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CSpriteSequence.obj" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CSpriteSequence.sbr" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSpriteCatalog.cpp
DEP_CPP_CSPRIT=\
	"..\animeditor\AnimEditor.h"\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	".\CActionRecord.h"\
	".\CDirectionRecord.h"\
	".\CSequenceCel.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\CVersion.h"\
	".\Dibitmap.h"\
	".\Dibpal.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CSpriteCatalog.obj" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"

"$(INTDIR)\CSpriteCatalog.sbr" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\AnimEditor.pch"


# End Source File
# End Target
# End Project
################################################################################
