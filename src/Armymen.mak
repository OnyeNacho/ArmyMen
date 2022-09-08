# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=ArmyMen - Win32 BC
!MESSAGE No configuration specified.  Defaulting to ArmyMen - Win32 BC.
!ENDIF 

!IF "$(CFG)" != "ArmyMen - Win32 Release" && "$(CFG)" !=\
 "ArmyMen - Win32 Debug" && "$(CFG)" != "ArmyMen - Win32 Remote Debug" &&\
 "$(CFG)" != "ArmyMen - Win32 Object Debug" && "$(CFG)" != "ArmyMen - Win32 BC"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Armymen.mak" CFG="ArmyMen - Win32 BC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ArmyMen - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ArmyMen - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ArmyMen - Win32 Remote Debug" (based on "Win32 (x86) Application")
!MESSAGE "ArmyMen - Win32 Object Debug" (based on "Win32 (x86) Application")
!MESSAGE "ArmyMen - Win32 BC" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "ArmyMen - Win32 BC"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "ArmyMen - Win32 Release"

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

ALL : "$(OUTDIR)\Armymen.exe" "$(OUTDIR)\Armymen.bsc"

CLEAN : 
	-@erase "$(INTDIR)\3DONetwork.obj"
	-@erase "$(INTDIR)\3DONetwork.sbr"
	-@erase "$(INTDIR)\Ai.obj"
	-@erase "$(INTDIR)\Ai.sbr"
	-@erase "$(INTDIR)\AiAccess.obj"
	-@erase "$(INTDIR)\AiAccess.sbr"
	-@erase "$(INTDIR)\Aibtank.obj"
	-@erase "$(INTDIR)\Aibtank.sbr"
	-@erase "$(INTDIR)\AiInput.obj"
	-@erase "$(INTDIR)\AiInput.sbr"
	-@erase "$(INTDIR)\air.obj"
	-@erase "$(INTDIR)\air.sbr"
	-@erase "$(INTDIR)\Airouter.obj"
	-@erase "$(INTDIR)\Airouter.sbr"
	-@erase "$(INTDIR)\aix.obj"
	-@erase "$(INTDIR)\aix.sbr"
	-@erase "$(INTDIR)\Anim.obj"
	-@erase "$(INTDIR)\Anim.sbr"
	-@erase "$(INTDIR)\AnimFile.obj"
	-@erase "$(INTDIR)\AnimFile.sbr"
	-@erase "$(INTDIR)\Army.obj"
	-@erase "$(INTDIR)\Army.sbr"
	-@erase "$(INTDIR)\ArmyMen.obj"
	-@erase "$(INTDIR)\Armymen.pch"
	-@erase "$(INTDIR)\ArmyMen.res"
	-@erase "$(INTDIR)\ArmyMen.sbr"
	-@erase "$(INTDIR)\ArmyMsg.obj"
	-@erase "$(INTDIR)\ArmyMsg.sbr"
	-@erase "$(INTDIR)\Asset.obj"
	-@erase "$(INTDIR)\Asset.sbr"
	-@erase "$(INTDIR)\AssetMsg.obj"
	-@erase "$(INTDIR)\AssetMsg.sbr"
	-@erase "$(INTDIR)\Audio.obj"
	-@erase "$(INTDIR)\Audio.sbr"
	-@erase "$(INTDIR)\Avatar.obj"
	-@erase "$(INTDIR)\Avatar.sbr"
	-@erase "$(INTDIR)\BmpText.obj"
	-@erase "$(INTDIR)\BmpText.sbr"
	-@erase "$(INTDIR)\cinema.obj"
	-@erase "$(INTDIR)\cinema.sbr"
	-@erase "$(INTDIR)\comm.obj"
	-@erase "$(INTDIR)\comm.sbr"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\Commands.sbr"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.sbr"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CSpriteSequence.sbr"
	-@erase "$(INTDIR)\damage.obj"
	-@erase "$(INTDIR)\damage.sbr"
	-@erase "$(INTDIR)\Dd.obj"
	-@erase "$(INTDIR)\Dd.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Dialog.sbr"
	-@erase "$(INTDIR)\Disp.obj"
	-@erase "$(INTDIR)\Disp.sbr"
	-@erase "$(INTDIR)\DrawObject.obj"
	-@erase "$(INTDIR)\DrawObject.sbr"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\Error.sbr"
	-@erase "$(INTDIR)\event.obj"
	-@erase "$(INTDIR)\event.sbr"
	-@erase "$(INTDIR)\explosions.obj"
	-@erase "$(INTDIR)\explosions.sbr"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\fileio.sbr"
	-@erase "$(INTDIR)\Float.obj"
	-@erase "$(INTDIR)\Float.sbr"
	-@erase "$(INTDIR)\FloatMsg.obj"
	-@erase "$(INTDIR)\FloatMsg.sbr"
	-@erase "$(INTDIR)\GameFlow.obj"
	-@erase "$(INTDIR)\GameFlow.sbr"
	-@erase "$(INTDIR)\gameproc.obj"
	-@erase "$(INTDIR)\gameproc.sbr"
	-@erase "$(INTDIR)\guid.obj"
	-@erase "$(INTDIR)\guid.sbr"
	-@erase "$(INTDIR)\husk.obj"
	-@erase "$(INTDIR)\husk.sbr"
	-@erase "$(INTDIR)\Input.obj"
	-@erase "$(INTDIR)\Input.sbr"
	-@erase "$(INTDIR)\Item.obj"
	-@erase "$(INTDIR)\Item.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Map.obj"
	-@erase "$(INTDIR)\Map.sbr"
	-@erase "$(INTDIR)\miscfile.obj"
	-@erase "$(INTDIR)\miscfile.sbr"
	-@erase "$(INTDIR)\Movie.obj"
	-@erase "$(INTDIR)\Movie.sbr"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Msg.sbr"
	-@erase "$(INTDIR)\newdoor.obj"
	-@erase "$(INTDIR)\newdoor.sbr"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\object.sbr"
	-@erase "$(INTDIR)\ObjectMsg.obj"
	-@erase "$(INTDIR)\ObjectMsg.sbr"
	-@erase "$(INTDIR)\pad.obj"
	-@erase "$(INTDIR)\pad.sbr"
	-@erase "$(INTDIR)\Rmerror.obj"
	-@erase "$(INTDIR)\Rmerror.sbr"
	-@erase "$(INTDIR)\Sarge.obj"
	-@erase "$(INTDIR)\Sarge.sbr"
	-@erase "$(INTDIR)\SargeMsg.obj"
	-@erase "$(INTDIR)\SargeMsg.sbr"
	-@erase "$(INTDIR)\scenario.obj"
	-@erase "$(INTDIR)\scenario.sbr"
	-@erase "$(INTDIR)\Screen.obj"
	-@erase "$(INTDIR)\Screen.sbr"
	-@erase "$(INTDIR)\ScreenBtn.obj"
	-@erase "$(INTDIR)\ScreenBtn.sbr"
	-@erase "$(INTDIR)\ScreenObj.obj"
	-@erase "$(INTDIR)\ScreenObj.sbr"
	-@erase "$(INTDIR)\scripts.obj"
	-@erase "$(INTDIR)\scripts.sbr"
	-@erase "$(INTDIR)\Sfx.obj"
	-@erase "$(INTDIR)\Sfx.sbr"
	-@erase "$(INTDIR)\Smacker.obj"
	-@erase "$(INTDIR)\Smacker.sbr"
	-@erase "$(INTDIR)\Snd.obj"
	-@erase "$(INTDIR)\Snd.sbr"
	-@erase "$(INTDIR)\Sprite.obj"
	-@erase "$(INTDIR)\Sprite.sbr"
	-@erase "$(INTDIR)\States.obj"
	-@erase "$(INTDIR)\States.sbr"
	-@erase "$(INTDIR)\Stats.obj"
	-@erase "$(INTDIR)\Stats.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\stratmap.obj"
	-@erase "$(INTDIR)\stratmap.sbr"
	-@erase "$(INTDIR)\strm.obj"
	-@erase "$(INTDIR)\strm.sbr"
	-@erase "$(INTDIR)\Tad.obj"
	-@erase "$(INTDIR)\Tad.sbr"
	-@erase "$(INTDIR)\TadPriv.obj"
	-@erase "$(INTDIR)\TadPriv.sbr"
	-@erase "$(INTDIR)\Text.obj"
	-@erase "$(INTDIR)\Text.sbr"
	-@erase "$(INTDIR)\TextData.obj"
	-@erase "$(INTDIR)\TextData.sbr"
	-@erase "$(INTDIR)\trooper.obj"
	-@erase "$(INTDIR)\trooper.sbr"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\ui.sbr"
	-@erase "$(INTDIR)\Unit.obj"
	-@erase "$(INTDIR)\Unit.sbr"
	-@erase "$(INTDIR)\UnitMsg.obj"
	-@erase "$(INTDIR)\UnitMsg.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Vehicle.obj"
	-@erase "$(INTDIR)\Vehicle.sbr"
	-@erase "$(INTDIR)\VehicleMsg.obj"
	-@erase "$(INTDIR)\VehicleMsg.sbr"
	-@erase "$(INTDIR)\Voice.obj"
	-@erase "$(INTDIR)\Voice.sbr"
	-@erase "$(INTDIR)\Weapon.obj"
	-@erase "$(INTDIR)\Weapon.sbr"
	-@erase "$(INTDIR)\wobject.obj"
	-@erase "$(INTDIR)\wobject.sbr"
	-@erase "$(OUTDIR)\Armymen.bsc"
	-@erase "$(OUTDIR)\Armymen.exe"
	-@erase "$(OUTDIR)\Armymen.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /Gr /MD /W3 /GX /Zi /O2 /D "NDBUG" /D "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D "FINAL" /Fr /Yu"stdafx.h" /c
CPP_PROJ=/nologo /Gr /MD /W3 /GX /Zi /O2 /D "NDBUG" /D "BACK_BUFFER_SYSTEM" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D\
 "FINAL" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ArmyMen.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Armymen.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\3DONetwork.sbr" \
	"$(INTDIR)\Ai.sbr" \
	"$(INTDIR)\AiAccess.sbr" \
	"$(INTDIR)\Aibtank.sbr" \
	"$(INTDIR)\AiInput.sbr" \
	"$(INTDIR)\air.sbr" \
	"$(INTDIR)\Airouter.sbr" \
	"$(INTDIR)\aix.sbr" \
	"$(INTDIR)\Anim.sbr" \
	"$(INTDIR)\AnimFile.sbr" \
	"$(INTDIR)\Army.sbr" \
	"$(INTDIR)\ArmyMen.sbr" \
	"$(INTDIR)\ArmyMsg.sbr" \
	"$(INTDIR)\Asset.sbr" \
	"$(INTDIR)\AssetMsg.sbr" \
	"$(INTDIR)\Audio.sbr" \
	"$(INTDIR)\Avatar.sbr" \
	"$(INTDIR)\BmpText.sbr" \
	"$(INTDIR)\cinema.sbr" \
	"$(INTDIR)\comm.sbr" \
	"$(INTDIR)\Commands.sbr" \
	"$(INTDIR)\CSpriteCatalog.sbr" \
	"$(INTDIR)\CSpriteSequence.sbr" \
	"$(INTDIR)\damage.sbr" \
	"$(INTDIR)\Dd.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\Dialog.sbr" \
	"$(INTDIR)\Disp.sbr" \
	"$(INTDIR)\DrawObject.sbr" \
	"$(INTDIR)\Error.sbr" \
	"$(INTDIR)\event.sbr" \
	"$(INTDIR)\explosions.sbr" \
	"$(INTDIR)\fileio.sbr" \
	"$(INTDIR)\Float.sbr" \
	"$(INTDIR)\FloatMsg.sbr" \
	"$(INTDIR)\GameFlow.sbr" \
	"$(INTDIR)\gameproc.sbr" \
	"$(INTDIR)\guid.sbr" \
	"$(INTDIR)\husk.sbr" \
	"$(INTDIR)\Input.sbr" \
	"$(INTDIR)\Item.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Map.sbr" \
	"$(INTDIR)\miscfile.sbr" \
	"$(INTDIR)\Movie.sbr" \
	"$(INTDIR)\Msg.sbr" \
	"$(INTDIR)\newdoor.sbr" \
	"$(INTDIR)\object.sbr" \
	"$(INTDIR)\ObjectMsg.sbr" \
	"$(INTDIR)\pad.sbr" \
	"$(INTDIR)\Rmerror.sbr" \
	"$(INTDIR)\Sarge.sbr" \
	"$(INTDIR)\SargeMsg.sbr" \
	"$(INTDIR)\scenario.sbr" \
	"$(INTDIR)\Screen.sbr" \
	"$(INTDIR)\ScreenBtn.sbr" \
	"$(INTDIR)\ScreenObj.sbr" \
	"$(INTDIR)\scripts.sbr" \
	"$(INTDIR)\Sfx.sbr" \
	"$(INTDIR)\Smacker.sbr" \
	"$(INTDIR)\Snd.sbr" \
	"$(INTDIR)\Sprite.sbr" \
	"$(INTDIR)\States.sbr" \
	"$(INTDIR)\Stats.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\stratmap.sbr" \
	"$(INTDIR)\strm.sbr" \
	"$(INTDIR)\Tad.sbr" \
	"$(INTDIR)\TadPriv.sbr" \
	"$(INTDIR)\Text.sbr" \
	"$(INTDIR)\TextData.sbr" \
	"$(INTDIR)\trooper.sbr" \
	"$(INTDIR)\ui.sbr" \
	"$(INTDIR)\Unit.sbr" \
	"$(INTDIR)\UnitMsg.sbr" \
	"$(INTDIR)\util.sbr" \
	"$(INTDIR)\Vehicle.sbr" \
	"$(INTDIR)\VehicleMsg.sbr" \
	"$(INTDIR)\Voice.sbr" \
	"$(INTDIR)\Weapon.sbr" \
	"$(INTDIR)\wobject.sbr"

"$(OUTDIR)\Armymen.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib comctl32.lib version.lib smackw32.lib ole32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC"
LINK32_FLAGS=dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib\
 comctl32.lib version.lib smackw32.lib ole32.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Armymen.pdb" /debug /machine:I386\
 /nodefaultlib:"LIBC" /out:"$(OUTDIR)/Armymen.exe" 
LINK32_OBJS= \
	"$(INTDIR)\3DONetwork.obj" \
	"$(INTDIR)\Ai.obj" \
	"$(INTDIR)\AiAccess.obj" \
	"$(INTDIR)\Aibtank.obj" \
	"$(INTDIR)\AiInput.obj" \
	"$(INTDIR)\air.obj" \
	"$(INTDIR)\Airouter.obj" \
	"$(INTDIR)\aix.obj" \
	"$(INTDIR)\Anim.obj" \
	"$(INTDIR)\AnimFile.obj" \
	"$(INTDIR)\Army.obj" \
	"$(INTDIR)\ArmyMen.obj" \
	"$(INTDIR)\ArmyMen.res" \
	"$(INTDIR)\ArmyMsg.obj" \
	"$(INTDIR)\Asset.obj" \
	"$(INTDIR)\AssetMsg.obj" \
	"$(INTDIR)\Audio.obj" \
	"$(INTDIR)\Avatar.obj" \
	"$(INTDIR)\BmpText.obj" \
	"$(INTDIR)\cinema.obj" \
	"$(INTDIR)\comm.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\damage.obj" \
	"$(INTDIR)\Dd.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\Disp.obj" \
	"$(INTDIR)\DrawObject.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\event.obj" \
	"$(INTDIR)\explosions.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\Float.obj" \
	"$(INTDIR)\FloatMsg.obj" \
	"$(INTDIR)\GameFlow.obj" \
	"$(INTDIR)\gameproc.obj" \
	"$(INTDIR)\guid.obj" \
	"$(INTDIR)\husk.obj" \
	"$(INTDIR)\Input.obj" \
	"$(INTDIR)\Item.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Map.obj" \
	"$(INTDIR)\miscfile.obj" \
	"$(INTDIR)\Movie.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\newdoor.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\ObjectMsg.obj" \
	"$(INTDIR)\pad.obj" \
	"$(INTDIR)\Rmerror.obj" \
	"$(INTDIR)\Sarge.obj" \
	"$(INTDIR)\SargeMsg.obj" \
	"$(INTDIR)\scenario.obj" \
	"$(INTDIR)\Screen.obj" \
	"$(INTDIR)\ScreenBtn.obj" \
	"$(INTDIR)\ScreenObj.obj" \
	"$(INTDIR)\scripts.obj" \
	"$(INTDIR)\Sfx.obj" \
	"$(INTDIR)\Smacker.obj" \
	"$(INTDIR)\Snd.obj" \
	"$(INTDIR)\Sprite.obj" \
	"$(INTDIR)\States.obj" \
	"$(INTDIR)\Stats.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stratmap.obj" \
	"$(INTDIR)\strm.obj" \
	"$(INTDIR)\Tad.obj" \
	"$(INTDIR)\TadPriv.obj" \
	"$(INTDIR)\Text.obj" \
	"$(INTDIR)\TextData.obj" \
	"$(INTDIR)\trooper.obj" \
	"$(INTDIR)\ui.obj" \
	"$(INTDIR)\Unit.obj" \
	"$(INTDIR)\UnitMsg.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Vehicle.obj" \
	"$(INTDIR)\VehicleMsg.obj" \
	"$(INTDIR)\Voice.obj" \
	"$(INTDIR)\Weapon.obj" \
	"$(INTDIR)\wobject.obj"

"$(OUTDIR)\Armymen.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ArmyMen_"
# PROP BASE Intermediate_Dir "ArmyMen_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\ArmymenDebug.exe" "$(OUTDIR)\Armymen.bsc"

CLEAN : 
	-@erase "$(INTDIR)\3DONetwork.obj"
	-@erase "$(INTDIR)\3DONetwork.sbr"
	-@erase "$(INTDIR)\Ai.obj"
	-@erase "$(INTDIR)\Ai.sbr"
	-@erase "$(INTDIR)\AiAccess.obj"
	-@erase "$(INTDIR)\AiAccess.sbr"
	-@erase "$(INTDIR)\Aibtank.obj"
	-@erase "$(INTDIR)\Aibtank.sbr"
	-@erase "$(INTDIR)\AiInput.obj"
	-@erase "$(INTDIR)\AiInput.sbr"
	-@erase "$(INTDIR)\air.obj"
	-@erase "$(INTDIR)\air.sbr"
	-@erase "$(INTDIR)\Airouter.obj"
	-@erase "$(INTDIR)\Airouter.sbr"
	-@erase "$(INTDIR)\aix.obj"
	-@erase "$(INTDIR)\aix.sbr"
	-@erase "$(INTDIR)\Anim.obj"
	-@erase "$(INTDIR)\Anim.sbr"
	-@erase "$(INTDIR)\AnimFile.obj"
	-@erase "$(INTDIR)\AnimFile.sbr"
	-@erase "$(INTDIR)\Army.obj"
	-@erase "$(INTDIR)\Army.sbr"
	-@erase "$(INTDIR)\ArmyMen.obj"
	-@erase "$(INTDIR)\Armymen.pch"
	-@erase "$(INTDIR)\ArmyMen.res"
	-@erase "$(INTDIR)\ArmyMen.sbr"
	-@erase "$(INTDIR)\ArmyMsg.obj"
	-@erase "$(INTDIR)\ArmyMsg.sbr"
	-@erase "$(INTDIR)\Asset.obj"
	-@erase "$(INTDIR)\Asset.sbr"
	-@erase "$(INTDIR)\AssetMsg.obj"
	-@erase "$(INTDIR)\AssetMsg.sbr"
	-@erase "$(INTDIR)\Audio.obj"
	-@erase "$(INTDIR)\Audio.sbr"
	-@erase "$(INTDIR)\Avatar.obj"
	-@erase "$(INTDIR)\Avatar.sbr"
	-@erase "$(INTDIR)\BmpText.obj"
	-@erase "$(INTDIR)\BmpText.sbr"
	-@erase "$(INTDIR)\cinema.obj"
	-@erase "$(INTDIR)\cinema.sbr"
	-@erase "$(INTDIR)\comm.obj"
	-@erase "$(INTDIR)\comm.sbr"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\Commands.sbr"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.sbr"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CSpriteSequence.sbr"
	-@erase "$(INTDIR)\damage.obj"
	-@erase "$(INTDIR)\damage.sbr"
	-@erase "$(INTDIR)\Dd.obj"
	-@erase "$(INTDIR)\Dd.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Dialog.sbr"
	-@erase "$(INTDIR)\Disp.obj"
	-@erase "$(INTDIR)\Disp.sbr"
	-@erase "$(INTDIR)\DrawObject.obj"
	-@erase "$(INTDIR)\DrawObject.sbr"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\Error.sbr"
	-@erase "$(INTDIR)\event.obj"
	-@erase "$(INTDIR)\event.sbr"
	-@erase "$(INTDIR)\explosions.obj"
	-@erase "$(INTDIR)\explosions.sbr"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\fileio.sbr"
	-@erase "$(INTDIR)\Float.obj"
	-@erase "$(INTDIR)\Float.sbr"
	-@erase "$(INTDIR)\FloatMsg.obj"
	-@erase "$(INTDIR)\FloatMsg.sbr"
	-@erase "$(INTDIR)\GameFlow.obj"
	-@erase "$(INTDIR)\GameFlow.sbr"
	-@erase "$(INTDIR)\gameproc.obj"
	-@erase "$(INTDIR)\gameproc.sbr"
	-@erase "$(INTDIR)\guid.obj"
	-@erase "$(INTDIR)\guid.sbr"
	-@erase "$(INTDIR)\husk.obj"
	-@erase "$(INTDIR)\husk.sbr"
	-@erase "$(INTDIR)\Input.obj"
	-@erase "$(INTDIR)\Input.sbr"
	-@erase "$(INTDIR)\Item.obj"
	-@erase "$(INTDIR)\Item.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Map.obj"
	-@erase "$(INTDIR)\Map.sbr"
	-@erase "$(INTDIR)\miscfile.obj"
	-@erase "$(INTDIR)\miscfile.sbr"
	-@erase "$(INTDIR)\Movie.obj"
	-@erase "$(INTDIR)\Movie.sbr"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Msg.sbr"
	-@erase "$(INTDIR)\newdoor.obj"
	-@erase "$(INTDIR)\newdoor.sbr"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\object.sbr"
	-@erase "$(INTDIR)\ObjectMsg.obj"
	-@erase "$(INTDIR)\ObjectMsg.sbr"
	-@erase "$(INTDIR)\pad.obj"
	-@erase "$(INTDIR)\pad.sbr"
	-@erase "$(INTDIR)\Rmerror.obj"
	-@erase "$(INTDIR)\Rmerror.sbr"
	-@erase "$(INTDIR)\Sarge.obj"
	-@erase "$(INTDIR)\Sarge.sbr"
	-@erase "$(INTDIR)\SargeMsg.obj"
	-@erase "$(INTDIR)\SargeMsg.sbr"
	-@erase "$(INTDIR)\scenario.obj"
	-@erase "$(INTDIR)\scenario.sbr"
	-@erase "$(INTDIR)\Screen.obj"
	-@erase "$(INTDIR)\Screen.sbr"
	-@erase "$(INTDIR)\ScreenBtn.obj"
	-@erase "$(INTDIR)\ScreenBtn.sbr"
	-@erase "$(INTDIR)\ScreenObj.obj"
	-@erase "$(INTDIR)\ScreenObj.sbr"
	-@erase "$(INTDIR)\scripts.obj"
	-@erase "$(INTDIR)\scripts.sbr"
	-@erase "$(INTDIR)\Sfx.obj"
	-@erase "$(INTDIR)\Sfx.sbr"
	-@erase "$(INTDIR)\Smacker.obj"
	-@erase "$(INTDIR)\Smacker.sbr"
	-@erase "$(INTDIR)\Snd.obj"
	-@erase "$(INTDIR)\Snd.sbr"
	-@erase "$(INTDIR)\Sprite.obj"
	-@erase "$(INTDIR)\Sprite.sbr"
	-@erase "$(INTDIR)\States.obj"
	-@erase "$(INTDIR)\States.sbr"
	-@erase "$(INTDIR)\Stats.obj"
	-@erase "$(INTDIR)\Stats.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\stratmap.obj"
	-@erase "$(INTDIR)\stratmap.sbr"
	-@erase "$(INTDIR)\strm.obj"
	-@erase "$(INTDIR)\strm.sbr"
	-@erase "$(INTDIR)\Tad.obj"
	-@erase "$(INTDIR)\Tad.sbr"
	-@erase "$(INTDIR)\TadPriv.obj"
	-@erase "$(INTDIR)\TadPriv.sbr"
	-@erase "$(INTDIR)\Text.obj"
	-@erase "$(INTDIR)\Text.sbr"
	-@erase "$(INTDIR)\TextData.obj"
	-@erase "$(INTDIR)\TextData.sbr"
	-@erase "$(INTDIR)\trooper.obj"
	-@erase "$(INTDIR)\trooper.sbr"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\ui.sbr"
	-@erase "$(INTDIR)\Unit.obj"
	-@erase "$(INTDIR)\Unit.sbr"
	-@erase "$(INTDIR)\UnitMsg.obj"
	-@erase "$(INTDIR)\UnitMsg.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Vehicle.obj"
	-@erase "$(INTDIR)\Vehicle.sbr"
	-@erase "$(INTDIR)\VehicleMsg.obj"
	-@erase "$(INTDIR)\VehicleMsg.sbr"
	-@erase "$(INTDIR)\Voice.obj"
	-@erase "$(INTDIR)\Voice.sbr"
	-@erase "$(INTDIR)\Weapon.obj"
	-@erase "$(INTDIR)\Weapon.sbr"
	-@erase "$(INTDIR)\wobject.obj"
	-@erase "$(INTDIR)\wobject.sbr"
	-@erase "$(OUTDIR)\Armymen.bsc"
	-@erase "$(OUTDIR)\ArmymenDebug.exe"
	-@erase "$(OUTDIR)\ArmymenDebug.ilk"
	-@erase "$(OUTDIR)\ArmymenDebug.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "AUDIO_OFF" /D "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ArmyMen.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Armymen.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\3DONetwork.sbr" \
	"$(INTDIR)\Ai.sbr" \
	"$(INTDIR)\AiAccess.sbr" \
	"$(INTDIR)\Aibtank.sbr" \
	"$(INTDIR)\AiInput.sbr" \
	"$(INTDIR)\air.sbr" \
	"$(INTDIR)\Airouter.sbr" \
	"$(INTDIR)\aix.sbr" \
	"$(INTDIR)\Anim.sbr" \
	"$(INTDIR)\AnimFile.sbr" \
	"$(INTDIR)\Army.sbr" \
	"$(INTDIR)\ArmyMen.sbr" \
	"$(INTDIR)\ArmyMsg.sbr" \
	"$(INTDIR)\Asset.sbr" \
	"$(INTDIR)\AssetMsg.sbr" \
	"$(INTDIR)\Audio.sbr" \
	"$(INTDIR)\Avatar.sbr" \
	"$(INTDIR)\BmpText.sbr" \
	"$(INTDIR)\cinema.sbr" \
	"$(INTDIR)\comm.sbr" \
	"$(INTDIR)\Commands.sbr" \
	"$(INTDIR)\CSpriteCatalog.sbr" \
	"$(INTDIR)\CSpriteSequence.sbr" \
	"$(INTDIR)\damage.sbr" \
	"$(INTDIR)\Dd.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\Dialog.sbr" \
	"$(INTDIR)\Disp.sbr" \
	"$(INTDIR)\DrawObject.sbr" \
	"$(INTDIR)\Error.sbr" \
	"$(INTDIR)\event.sbr" \
	"$(INTDIR)\explosions.sbr" \
	"$(INTDIR)\fileio.sbr" \
	"$(INTDIR)\Float.sbr" \
	"$(INTDIR)\FloatMsg.sbr" \
	"$(INTDIR)\GameFlow.sbr" \
	"$(INTDIR)\gameproc.sbr" \
	"$(INTDIR)\guid.sbr" \
	"$(INTDIR)\husk.sbr" \
	"$(INTDIR)\Input.sbr" \
	"$(INTDIR)\Item.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Map.sbr" \
	"$(INTDIR)\miscfile.sbr" \
	"$(INTDIR)\Movie.sbr" \
	"$(INTDIR)\Msg.sbr" \
	"$(INTDIR)\newdoor.sbr" \
	"$(INTDIR)\object.sbr" \
	"$(INTDIR)\ObjectMsg.sbr" \
	"$(INTDIR)\pad.sbr" \
	"$(INTDIR)\Rmerror.sbr" \
	"$(INTDIR)\Sarge.sbr" \
	"$(INTDIR)\SargeMsg.sbr" \
	"$(INTDIR)\scenario.sbr" \
	"$(INTDIR)\Screen.sbr" \
	"$(INTDIR)\ScreenBtn.sbr" \
	"$(INTDIR)\ScreenObj.sbr" \
	"$(INTDIR)\scripts.sbr" \
	"$(INTDIR)\Sfx.sbr" \
	"$(INTDIR)\Smacker.sbr" \
	"$(INTDIR)\Snd.sbr" \
	"$(INTDIR)\Sprite.sbr" \
	"$(INTDIR)\States.sbr" \
	"$(INTDIR)\Stats.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\stratmap.sbr" \
	"$(INTDIR)\strm.sbr" \
	"$(INTDIR)\Tad.sbr" \
	"$(INTDIR)\TadPriv.sbr" \
	"$(INTDIR)\Text.sbr" \
	"$(INTDIR)\TextData.sbr" \
	"$(INTDIR)\trooper.sbr" \
	"$(INTDIR)\ui.sbr" \
	"$(INTDIR)\Unit.sbr" \
	"$(INTDIR)\UnitMsg.sbr" \
	"$(INTDIR)\util.sbr" \
	"$(INTDIR)\Vehicle.sbr" \
	"$(INTDIR)\VehicleMsg.sbr" \
	"$(INTDIR)\Voice.sbr" \
	"$(INTDIR)\Weapon.sbr" \
	"$(INTDIR)\wobject.sbr"

"$(OUTDIR)\Armymen.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 dxguid.lib ddraw.lib dsound.lib dinput.lib dplayx.lib winmm.lib vfw32.lib comctl32.lib version.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"Debug/ArmymenDebug.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ole32.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib comctl32.lib version.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"Debug/ArmymenDebug.exe"
# SUBTRACT LINK32 /pdb:none /map
LINK32_FLAGS=ole32.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib\
 vfw32.lib comctl32.lib version.lib smackw32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/ArmymenDebug.pdb" /debug /machine:I386\
 /nodefaultlib:"LIBC" /out:"$(OUTDIR)/ArmymenDebug.exe" 
LINK32_OBJS= \
	"$(INTDIR)\3DONetwork.obj" \
	"$(INTDIR)\Ai.obj" \
	"$(INTDIR)\AiAccess.obj" \
	"$(INTDIR)\Aibtank.obj" \
	"$(INTDIR)\AiInput.obj" \
	"$(INTDIR)\air.obj" \
	"$(INTDIR)\Airouter.obj" \
	"$(INTDIR)\aix.obj" \
	"$(INTDIR)\Anim.obj" \
	"$(INTDIR)\AnimFile.obj" \
	"$(INTDIR)\Army.obj" \
	"$(INTDIR)\ArmyMen.obj" \
	"$(INTDIR)\ArmyMen.res" \
	"$(INTDIR)\ArmyMsg.obj" \
	"$(INTDIR)\Asset.obj" \
	"$(INTDIR)\AssetMsg.obj" \
	"$(INTDIR)\Audio.obj" \
	"$(INTDIR)\Avatar.obj" \
	"$(INTDIR)\BmpText.obj" \
	"$(INTDIR)\cinema.obj" \
	"$(INTDIR)\comm.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\damage.obj" \
	"$(INTDIR)\Dd.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\Disp.obj" \
	"$(INTDIR)\DrawObject.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\event.obj" \
	"$(INTDIR)\explosions.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\Float.obj" \
	"$(INTDIR)\FloatMsg.obj" \
	"$(INTDIR)\GameFlow.obj" \
	"$(INTDIR)\gameproc.obj" \
	"$(INTDIR)\guid.obj" \
	"$(INTDIR)\husk.obj" \
	"$(INTDIR)\Input.obj" \
	"$(INTDIR)\Item.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Map.obj" \
	"$(INTDIR)\miscfile.obj" \
	"$(INTDIR)\Movie.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\newdoor.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\ObjectMsg.obj" \
	"$(INTDIR)\pad.obj" \
	"$(INTDIR)\Rmerror.obj" \
	"$(INTDIR)\Sarge.obj" \
	"$(INTDIR)\SargeMsg.obj" \
	"$(INTDIR)\scenario.obj" \
	"$(INTDIR)\Screen.obj" \
	"$(INTDIR)\ScreenBtn.obj" \
	"$(INTDIR)\ScreenObj.obj" \
	"$(INTDIR)\scripts.obj" \
	"$(INTDIR)\Sfx.obj" \
	"$(INTDIR)\Smacker.obj" \
	"$(INTDIR)\Snd.obj" \
	"$(INTDIR)\Sprite.obj" \
	"$(INTDIR)\States.obj" \
	"$(INTDIR)\Stats.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stratmap.obj" \
	"$(INTDIR)\strm.obj" \
	"$(INTDIR)\Tad.obj" \
	"$(INTDIR)\TadPriv.obj" \
	"$(INTDIR)\Text.obj" \
	"$(INTDIR)\TextData.obj" \
	"$(INTDIR)\trooper.obj" \
	"$(INTDIR)\ui.obj" \
	"$(INTDIR)\Unit.obj" \
	"$(INTDIR)\UnitMsg.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Vehicle.obj" \
	"$(INTDIR)\VehicleMsg.obj" \
	"$(INTDIR)\Voice.obj" \
	"$(INTDIR)\Weapon.obj" \
	"$(INTDIR)\wobject.obj"

"$(OUTDIR)\ArmymenDebug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ArmyMen_"
# PROP BASE Intermediate_Dir "ArmyMen_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ArmyMen_"
# PROP Intermediate_Dir "ArmyMen_"
# PROP Target_Dir ""
OUTDIR=.\ArmyMen_
INTDIR=.\ArmyMen_

ALL : ".\Debug\ArmymenDebug.exe" "$(OUTDIR)\Armymen.bsc" "I:\ArmymenDebug.exe"

CLEAN : 
	-@erase "$(INTDIR)\3DONetwork.obj"
	-@erase "$(INTDIR)\3DONetwork.sbr"
	-@erase "$(INTDIR)\Ai.obj"
	-@erase "$(INTDIR)\Ai.sbr"
	-@erase "$(INTDIR)\AiAccess.obj"
	-@erase "$(INTDIR)\AiAccess.sbr"
	-@erase "$(INTDIR)\Aibtank.obj"
	-@erase "$(INTDIR)\Aibtank.sbr"
	-@erase "$(INTDIR)\AiInput.obj"
	-@erase "$(INTDIR)\AiInput.sbr"
	-@erase "$(INTDIR)\air.obj"
	-@erase "$(INTDIR)\air.sbr"
	-@erase "$(INTDIR)\Airouter.obj"
	-@erase "$(INTDIR)\Airouter.sbr"
	-@erase "$(INTDIR)\aix.obj"
	-@erase "$(INTDIR)\aix.sbr"
	-@erase "$(INTDIR)\Anim.obj"
	-@erase "$(INTDIR)\Anim.sbr"
	-@erase "$(INTDIR)\AnimFile.obj"
	-@erase "$(INTDIR)\AnimFile.sbr"
	-@erase "$(INTDIR)\Army.obj"
	-@erase "$(INTDIR)\Army.sbr"
	-@erase "$(INTDIR)\ArmyMen.obj"
	-@erase "$(INTDIR)\Armymen.pch"
	-@erase "$(INTDIR)\ArmyMen.res"
	-@erase "$(INTDIR)\ArmyMen.sbr"
	-@erase "$(INTDIR)\ArmyMsg.obj"
	-@erase "$(INTDIR)\ArmyMsg.sbr"
	-@erase "$(INTDIR)\Asset.obj"
	-@erase "$(INTDIR)\Asset.sbr"
	-@erase "$(INTDIR)\AssetMsg.obj"
	-@erase "$(INTDIR)\AssetMsg.sbr"
	-@erase "$(INTDIR)\Audio.obj"
	-@erase "$(INTDIR)\Audio.sbr"
	-@erase "$(INTDIR)\Avatar.obj"
	-@erase "$(INTDIR)\Avatar.sbr"
	-@erase "$(INTDIR)\BmpText.obj"
	-@erase "$(INTDIR)\BmpText.sbr"
	-@erase "$(INTDIR)\cinema.obj"
	-@erase "$(INTDIR)\cinema.sbr"
	-@erase "$(INTDIR)\comm.obj"
	-@erase "$(INTDIR)\comm.sbr"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\Commands.sbr"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.sbr"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CSpriteSequence.sbr"
	-@erase "$(INTDIR)\damage.obj"
	-@erase "$(INTDIR)\damage.sbr"
	-@erase "$(INTDIR)\Dd.obj"
	-@erase "$(INTDIR)\Dd.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Dialog.sbr"
	-@erase "$(INTDIR)\Disp.obj"
	-@erase "$(INTDIR)\Disp.sbr"
	-@erase "$(INTDIR)\DrawObject.obj"
	-@erase "$(INTDIR)\DrawObject.sbr"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\Error.sbr"
	-@erase "$(INTDIR)\event.obj"
	-@erase "$(INTDIR)\event.sbr"
	-@erase "$(INTDIR)\explosions.obj"
	-@erase "$(INTDIR)\explosions.sbr"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\fileio.sbr"
	-@erase "$(INTDIR)\Float.obj"
	-@erase "$(INTDIR)\Float.sbr"
	-@erase "$(INTDIR)\FloatMsg.obj"
	-@erase "$(INTDIR)\FloatMsg.sbr"
	-@erase "$(INTDIR)\GameFlow.obj"
	-@erase "$(INTDIR)\GameFlow.sbr"
	-@erase "$(INTDIR)\gameproc.obj"
	-@erase "$(INTDIR)\gameproc.sbr"
	-@erase "$(INTDIR)\guid.obj"
	-@erase "$(INTDIR)\guid.sbr"
	-@erase "$(INTDIR)\husk.obj"
	-@erase "$(INTDIR)\husk.sbr"
	-@erase "$(INTDIR)\Input.obj"
	-@erase "$(INTDIR)\Input.sbr"
	-@erase "$(INTDIR)\Item.obj"
	-@erase "$(INTDIR)\Item.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Map.obj"
	-@erase "$(INTDIR)\Map.sbr"
	-@erase "$(INTDIR)\miscfile.obj"
	-@erase "$(INTDIR)\miscfile.sbr"
	-@erase "$(INTDIR)\Movie.obj"
	-@erase "$(INTDIR)\Movie.sbr"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Msg.sbr"
	-@erase "$(INTDIR)\newdoor.obj"
	-@erase "$(INTDIR)\newdoor.sbr"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\object.sbr"
	-@erase "$(INTDIR)\ObjectMsg.obj"
	-@erase "$(INTDIR)\ObjectMsg.sbr"
	-@erase "$(INTDIR)\pad.obj"
	-@erase "$(INTDIR)\pad.sbr"
	-@erase "$(INTDIR)\Rmerror.obj"
	-@erase "$(INTDIR)\Rmerror.sbr"
	-@erase "$(INTDIR)\Sarge.obj"
	-@erase "$(INTDIR)\Sarge.sbr"
	-@erase "$(INTDIR)\SargeMsg.obj"
	-@erase "$(INTDIR)\SargeMsg.sbr"
	-@erase "$(INTDIR)\scenario.obj"
	-@erase "$(INTDIR)\scenario.sbr"
	-@erase "$(INTDIR)\Screen.obj"
	-@erase "$(INTDIR)\Screen.sbr"
	-@erase "$(INTDIR)\ScreenBtn.obj"
	-@erase "$(INTDIR)\ScreenBtn.sbr"
	-@erase "$(INTDIR)\ScreenObj.obj"
	-@erase "$(INTDIR)\ScreenObj.sbr"
	-@erase "$(INTDIR)\scripts.obj"
	-@erase "$(INTDIR)\scripts.sbr"
	-@erase "$(INTDIR)\Sfx.obj"
	-@erase "$(INTDIR)\Sfx.sbr"
	-@erase "$(INTDIR)\Smacker.obj"
	-@erase "$(INTDIR)\Smacker.sbr"
	-@erase "$(INTDIR)\Snd.obj"
	-@erase "$(INTDIR)\Snd.sbr"
	-@erase "$(INTDIR)\Sprite.obj"
	-@erase "$(INTDIR)\Sprite.sbr"
	-@erase "$(INTDIR)\States.obj"
	-@erase "$(INTDIR)\States.sbr"
	-@erase "$(INTDIR)\Stats.obj"
	-@erase "$(INTDIR)\Stats.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\stratmap.obj"
	-@erase "$(INTDIR)\stratmap.sbr"
	-@erase "$(INTDIR)\strm.obj"
	-@erase "$(INTDIR)\strm.sbr"
	-@erase "$(INTDIR)\Tad.obj"
	-@erase "$(INTDIR)\Tad.sbr"
	-@erase "$(INTDIR)\TadPriv.obj"
	-@erase "$(INTDIR)\TadPriv.sbr"
	-@erase "$(INTDIR)\Text.obj"
	-@erase "$(INTDIR)\Text.sbr"
	-@erase "$(INTDIR)\TextData.obj"
	-@erase "$(INTDIR)\TextData.sbr"
	-@erase "$(INTDIR)\trooper.obj"
	-@erase "$(INTDIR)\trooper.sbr"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\ui.sbr"
	-@erase "$(INTDIR)\Unit.obj"
	-@erase "$(INTDIR)\Unit.sbr"
	-@erase "$(INTDIR)\UnitMsg.obj"
	-@erase "$(INTDIR)\UnitMsg.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Vehicle.obj"
	-@erase "$(INTDIR)\Vehicle.sbr"
	-@erase "$(INTDIR)\VehicleMsg.obj"
	-@erase "$(INTDIR)\VehicleMsg.sbr"
	-@erase "$(INTDIR)\Voice.obj"
	-@erase "$(INTDIR)\Voice.sbr"
	-@erase "$(INTDIR)\Weapon.obj"
	-@erase "$(INTDIR)\Weapon.sbr"
	-@erase "$(INTDIR)\wobject.obj"
	-@erase "$(INTDIR)\wobject.sbr"
	-@erase "$(OUTDIR)\Armymen.bsc"
	-@erase "$(OUTDIR)\ArmymenDebug.pdb"
	-@erase ".\Debug\ArmymenDebug.exe"
	-@erase ".\Debug\ArmymenDebug.ilk"
	-@erase "I:\ArmymenDebug.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "AUDIO_OFF" /D "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D "_AUDIO_OFF" /D "_OBJECT_DEBUG" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_AUDIO_OFF" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\ArmyMen_/
CPP_SBRS=.\ArmyMen_/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ArmyMen.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Armymen.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\3DONetwork.sbr" \
	"$(INTDIR)\Ai.sbr" \
	"$(INTDIR)\AiAccess.sbr" \
	"$(INTDIR)\Aibtank.sbr" \
	"$(INTDIR)\AiInput.sbr" \
	"$(INTDIR)\air.sbr" \
	"$(INTDIR)\Airouter.sbr" \
	"$(INTDIR)\aix.sbr" \
	"$(INTDIR)\Anim.sbr" \
	"$(INTDIR)\AnimFile.sbr" \
	"$(INTDIR)\Army.sbr" \
	"$(INTDIR)\ArmyMen.sbr" \
	"$(INTDIR)\ArmyMsg.sbr" \
	"$(INTDIR)\Asset.sbr" \
	"$(INTDIR)\AssetMsg.sbr" \
	"$(INTDIR)\Audio.sbr" \
	"$(INTDIR)\Avatar.sbr" \
	"$(INTDIR)\BmpText.sbr" \
	"$(INTDIR)\cinema.sbr" \
	"$(INTDIR)\comm.sbr" \
	"$(INTDIR)\Commands.sbr" \
	"$(INTDIR)\CSpriteCatalog.sbr" \
	"$(INTDIR)\CSpriteSequence.sbr" \
	"$(INTDIR)\damage.sbr" \
	"$(INTDIR)\Dd.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\Dialog.sbr" \
	"$(INTDIR)\Disp.sbr" \
	"$(INTDIR)\DrawObject.sbr" \
	"$(INTDIR)\Error.sbr" \
	"$(INTDIR)\event.sbr" \
	"$(INTDIR)\explosions.sbr" \
	"$(INTDIR)\fileio.sbr" \
	"$(INTDIR)\Float.sbr" \
	"$(INTDIR)\FloatMsg.sbr" \
	"$(INTDIR)\GameFlow.sbr" \
	"$(INTDIR)\gameproc.sbr" \
	"$(INTDIR)\guid.sbr" \
	"$(INTDIR)\husk.sbr" \
	"$(INTDIR)\Input.sbr" \
	"$(INTDIR)\Item.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Map.sbr" \
	"$(INTDIR)\miscfile.sbr" \
	"$(INTDIR)\Movie.sbr" \
	"$(INTDIR)\Msg.sbr" \
	"$(INTDIR)\newdoor.sbr" \
	"$(INTDIR)\object.sbr" \
	"$(INTDIR)\ObjectMsg.sbr" \
	"$(INTDIR)\pad.sbr" \
	"$(INTDIR)\Rmerror.sbr" \
	"$(INTDIR)\Sarge.sbr" \
	"$(INTDIR)\SargeMsg.sbr" \
	"$(INTDIR)\scenario.sbr" \
	"$(INTDIR)\Screen.sbr" \
	"$(INTDIR)\ScreenBtn.sbr" \
	"$(INTDIR)\ScreenObj.sbr" \
	"$(INTDIR)\scripts.sbr" \
	"$(INTDIR)\Sfx.sbr" \
	"$(INTDIR)\Smacker.sbr" \
	"$(INTDIR)\Snd.sbr" \
	"$(INTDIR)\Sprite.sbr" \
	"$(INTDIR)\States.sbr" \
	"$(INTDIR)\Stats.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\stratmap.sbr" \
	"$(INTDIR)\strm.sbr" \
	"$(INTDIR)\Tad.sbr" \
	"$(INTDIR)\TadPriv.sbr" \
	"$(INTDIR)\Text.sbr" \
	"$(INTDIR)\TextData.sbr" \
	"$(INTDIR)\trooper.sbr" \
	"$(INTDIR)\ui.sbr" \
	"$(INTDIR)\Unit.sbr" \
	"$(INTDIR)\UnitMsg.sbr" \
	"$(INTDIR)\util.sbr" \
	"$(INTDIR)\Vehicle.sbr" \
	"$(INTDIR)\VehicleMsg.sbr" \
	"$(INTDIR)\Voice.sbr" \
	"$(INTDIR)\Weapon.sbr" \
	"$(INTDIR)\wobject.sbr"

"$(OUTDIR)\Armymen.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 dxguid.lib ddraw.lib dsound.lib dinput.lib dplayx.lib winmm.lib vfw32.lib comctl32.lib version.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"Debug/ArmymenDebug.exe"
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib comctl32.lib version.lib smackw32.lib ole32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"Debug/ArmymenDebug.exe"
# SUBTRACT LINK32 /pdb:none /map
LINK32_FLAGS=dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib\
 comctl32.lib version.lib smackw32.lib ole32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/ArmymenDebug.pdb" /debug /machine:I386\
 /nodefaultlib:"LIBC" /out:"Debug/ArmymenDebug.exe" 
LINK32_OBJS= \
	"$(INTDIR)\3DONetwork.obj" \
	"$(INTDIR)\Ai.obj" \
	"$(INTDIR)\AiAccess.obj" \
	"$(INTDIR)\Aibtank.obj" \
	"$(INTDIR)\AiInput.obj" \
	"$(INTDIR)\air.obj" \
	"$(INTDIR)\Airouter.obj" \
	"$(INTDIR)\aix.obj" \
	"$(INTDIR)\Anim.obj" \
	"$(INTDIR)\AnimFile.obj" \
	"$(INTDIR)\Army.obj" \
	"$(INTDIR)\ArmyMen.obj" \
	"$(INTDIR)\ArmyMen.res" \
	"$(INTDIR)\ArmyMsg.obj" \
	"$(INTDIR)\Asset.obj" \
	"$(INTDIR)\AssetMsg.obj" \
	"$(INTDIR)\Audio.obj" \
	"$(INTDIR)\Avatar.obj" \
	"$(INTDIR)\BmpText.obj" \
	"$(INTDIR)\cinema.obj" \
	"$(INTDIR)\comm.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\damage.obj" \
	"$(INTDIR)\Dd.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\Disp.obj" \
	"$(INTDIR)\DrawObject.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\event.obj" \
	"$(INTDIR)\explosions.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\Float.obj" \
	"$(INTDIR)\FloatMsg.obj" \
	"$(INTDIR)\GameFlow.obj" \
	"$(INTDIR)\gameproc.obj" \
	"$(INTDIR)\guid.obj" \
	"$(INTDIR)\husk.obj" \
	"$(INTDIR)\Input.obj" \
	"$(INTDIR)\Item.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Map.obj" \
	"$(INTDIR)\miscfile.obj" \
	"$(INTDIR)\Movie.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\newdoor.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\ObjectMsg.obj" \
	"$(INTDIR)\pad.obj" \
	"$(INTDIR)\Rmerror.obj" \
	"$(INTDIR)\Sarge.obj" \
	"$(INTDIR)\SargeMsg.obj" \
	"$(INTDIR)\scenario.obj" \
	"$(INTDIR)\Screen.obj" \
	"$(INTDIR)\ScreenBtn.obj" \
	"$(INTDIR)\ScreenObj.obj" \
	"$(INTDIR)\scripts.obj" \
	"$(INTDIR)\Sfx.obj" \
	"$(INTDIR)\Smacker.obj" \
	"$(INTDIR)\Snd.obj" \
	"$(INTDIR)\Sprite.obj" \
	"$(INTDIR)\States.obj" \
	"$(INTDIR)\Stats.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stratmap.obj" \
	"$(INTDIR)\strm.obj" \
	"$(INTDIR)\Tad.obj" \
	"$(INTDIR)\TadPriv.obj" \
	"$(INTDIR)\Text.obj" \
	"$(INTDIR)\TextData.obj" \
	"$(INTDIR)\trooper.obj" \
	"$(INTDIR)\ui.obj" \
	"$(INTDIR)\Unit.obj" \
	"$(INTDIR)\UnitMsg.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Vehicle.obj" \
	"$(INTDIR)\VehicleMsg.obj" \
	"$(INTDIR)\Voice.obj" \
	"$(INTDIR)\Weapon.obj" \
	"$(INTDIR)\wobject.obj"

".\Debug\ArmymenDebug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
InputPath=.\Debug\ArmymenDebug.exe
InputName=ArmymenDebug
SOURCE=$(InputPath)

"I:\$(InputName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(InputPath) I:\$(InputName).exe

# End Custom Build

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ArmyMen0"
# PROP BASE Intermediate_Dir "ArmyMen0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ArmyMen0"
# PROP Intermediate_Dir "ArmyMen0"
# PROP Target_Dir ""
OUTDIR=.\ArmyMen0
INTDIR=.\ArmyMen0

ALL : ".\ObjectDebug\ArmymenObjects.exe" "$(OUTDIR)\Armymen.bsc"\
 "H:\RunTime\ArmymenObjects.exe"

CLEAN : 
	-@erase "$(INTDIR)\3DONetwork.obj"
	-@erase "$(INTDIR)\3DONetwork.sbr"
	-@erase "$(INTDIR)\Ai.obj"
	-@erase "$(INTDIR)\Ai.sbr"
	-@erase "$(INTDIR)\AiAccess.obj"
	-@erase "$(INTDIR)\AiAccess.sbr"
	-@erase "$(INTDIR)\Aibtank.obj"
	-@erase "$(INTDIR)\Aibtank.sbr"
	-@erase "$(INTDIR)\AiInput.obj"
	-@erase "$(INTDIR)\AiInput.sbr"
	-@erase "$(INTDIR)\air.obj"
	-@erase "$(INTDIR)\air.sbr"
	-@erase "$(INTDIR)\Airouter.obj"
	-@erase "$(INTDIR)\Airouter.sbr"
	-@erase "$(INTDIR)\aix.obj"
	-@erase "$(INTDIR)\aix.sbr"
	-@erase "$(INTDIR)\Anim.obj"
	-@erase "$(INTDIR)\Anim.sbr"
	-@erase "$(INTDIR)\AnimFile.obj"
	-@erase "$(INTDIR)\AnimFile.sbr"
	-@erase "$(INTDIR)\Army.obj"
	-@erase "$(INTDIR)\Army.sbr"
	-@erase "$(INTDIR)\ArmyMen.obj"
	-@erase "$(INTDIR)\Armymen.pch"
	-@erase "$(INTDIR)\ArmyMen.res"
	-@erase "$(INTDIR)\ArmyMen.sbr"
	-@erase "$(INTDIR)\ArmyMsg.obj"
	-@erase "$(INTDIR)\ArmyMsg.sbr"
	-@erase "$(INTDIR)\Asset.obj"
	-@erase "$(INTDIR)\Asset.sbr"
	-@erase "$(INTDIR)\AssetMsg.obj"
	-@erase "$(INTDIR)\AssetMsg.sbr"
	-@erase "$(INTDIR)\Audio.obj"
	-@erase "$(INTDIR)\Audio.sbr"
	-@erase "$(INTDIR)\Avatar.obj"
	-@erase "$(INTDIR)\Avatar.sbr"
	-@erase "$(INTDIR)\BmpText.obj"
	-@erase "$(INTDIR)\BmpText.sbr"
	-@erase "$(INTDIR)\cinema.obj"
	-@erase "$(INTDIR)\cinema.sbr"
	-@erase "$(INTDIR)\comm.obj"
	-@erase "$(INTDIR)\comm.sbr"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\Commands.sbr"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.sbr"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CSpriteSequence.sbr"
	-@erase "$(INTDIR)\damage.obj"
	-@erase "$(INTDIR)\damage.sbr"
	-@erase "$(INTDIR)\Dd.obj"
	-@erase "$(INTDIR)\Dd.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Dialog.sbr"
	-@erase "$(INTDIR)\Disp.obj"
	-@erase "$(INTDIR)\Disp.sbr"
	-@erase "$(INTDIR)\DrawObject.obj"
	-@erase "$(INTDIR)\DrawObject.sbr"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\Error.sbr"
	-@erase "$(INTDIR)\event.obj"
	-@erase "$(INTDIR)\event.sbr"
	-@erase "$(INTDIR)\explosions.obj"
	-@erase "$(INTDIR)\explosions.sbr"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\fileio.sbr"
	-@erase "$(INTDIR)\Float.obj"
	-@erase "$(INTDIR)\Float.sbr"
	-@erase "$(INTDIR)\FloatMsg.obj"
	-@erase "$(INTDIR)\FloatMsg.sbr"
	-@erase "$(INTDIR)\GameFlow.obj"
	-@erase "$(INTDIR)\GameFlow.sbr"
	-@erase "$(INTDIR)\gameproc.obj"
	-@erase "$(INTDIR)\gameproc.sbr"
	-@erase "$(INTDIR)\guid.obj"
	-@erase "$(INTDIR)\guid.sbr"
	-@erase "$(INTDIR)\husk.obj"
	-@erase "$(INTDIR)\husk.sbr"
	-@erase "$(INTDIR)\Input.obj"
	-@erase "$(INTDIR)\Input.sbr"
	-@erase "$(INTDIR)\Item.obj"
	-@erase "$(INTDIR)\Item.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Map.obj"
	-@erase "$(INTDIR)\Map.sbr"
	-@erase "$(INTDIR)\miscfile.obj"
	-@erase "$(INTDIR)\miscfile.sbr"
	-@erase "$(INTDIR)\Movie.obj"
	-@erase "$(INTDIR)\Movie.sbr"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Msg.sbr"
	-@erase "$(INTDIR)\newdoor.obj"
	-@erase "$(INTDIR)\newdoor.sbr"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\object.sbr"
	-@erase "$(INTDIR)\ObjectMsg.obj"
	-@erase "$(INTDIR)\ObjectMsg.sbr"
	-@erase "$(INTDIR)\pad.obj"
	-@erase "$(INTDIR)\pad.sbr"
	-@erase "$(INTDIR)\Rmerror.obj"
	-@erase "$(INTDIR)\Rmerror.sbr"
	-@erase "$(INTDIR)\Sarge.obj"
	-@erase "$(INTDIR)\Sarge.sbr"
	-@erase "$(INTDIR)\SargeMsg.obj"
	-@erase "$(INTDIR)\SargeMsg.sbr"
	-@erase "$(INTDIR)\scenario.obj"
	-@erase "$(INTDIR)\scenario.sbr"
	-@erase "$(INTDIR)\Screen.obj"
	-@erase "$(INTDIR)\Screen.sbr"
	-@erase "$(INTDIR)\ScreenBtn.obj"
	-@erase "$(INTDIR)\ScreenBtn.sbr"
	-@erase "$(INTDIR)\ScreenObj.obj"
	-@erase "$(INTDIR)\ScreenObj.sbr"
	-@erase "$(INTDIR)\scripts.obj"
	-@erase "$(INTDIR)\scripts.sbr"
	-@erase "$(INTDIR)\Sfx.obj"
	-@erase "$(INTDIR)\Sfx.sbr"
	-@erase "$(INTDIR)\Smacker.obj"
	-@erase "$(INTDIR)\Smacker.sbr"
	-@erase "$(INTDIR)\Snd.obj"
	-@erase "$(INTDIR)\Snd.sbr"
	-@erase "$(INTDIR)\Sprite.obj"
	-@erase "$(INTDIR)\Sprite.sbr"
	-@erase "$(INTDIR)\States.obj"
	-@erase "$(INTDIR)\States.sbr"
	-@erase "$(INTDIR)\Stats.obj"
	-@erase "$(INTDIR)\Stats.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\stratmap.obj"
	-@erase "$(INTDIR)\stratmap.sbr"
	-@erase "$(INTDIR)\strm.obj"
	-@erase "$(INTDIR)\strm.sbr"
	-@erase "$(INTDIR)\Tad.obj"
	-@erase "$(INTDIR)\Tad.sbr"
	-@erase "$(INTDIR)\TadPriv.obj"
	-@erase "$(INTDIR)\TadPriv.sbr"
	-@erase "$(INTDIR)\Text.obj"
	-@erase "$(INTDIR)\Text.sbr"
	-@erase "$(INTDIR)\TextData.obj"
	-@erase "$(INTDIR)\TextData.sbr"
	-@erase "$(INTDIR)\trooper.obj"
	-@erase "$(INTDIR)\trooper.sbr"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\ui.sbr"
	-@erase "$(INTDIR)\Unit.obj"
	-@erase "$(INTDIR)\Unit.sbr"
	-@erase "$(INTDIR)\UnitMsg.obj"
	-@erase "$(INTDIR)\UnitMsg.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Vehicle.obj"
	-@erase "$(INTDIR)\Vehicle.sbr"
	-@erase "$(INTDIR)\VehicleMsg.obj"
	-@erase "$(INTDIR)\VehicleMsg.sbr"
	-@erase "$(INTDIR)\Voice.obj"
	-@erase "$(INTDIR)\Voice.sbr"
	-@erase "$(INTDIR)\Weapon.obj"
	-@erase "$(INTDIR)\Weapon.sbr"
	-@erase "$(INTDIR)\wobject.obj"
	-@erase "$(INTDIR)\wobject.sbr"
	-@erase "$(OUTDIR)\Armymen.bsc"
	-@erase "$(OUTDIR)\ArmymenObjects.pdb"
	-@erase ".\ObjectDebug\ArmymenObjects.exe"
	-@erase ".\ObjectDebug\ArmymenObjects.ilk"
	-@erase "H:\RunTime\ArmymenObjects.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D "_OBJECT_DEBUG" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\ArmyMen0/
CPP_SBRS=.\ArmyMen0/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ArmyMen.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Armymen.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\3DONetwork.sbr" \
	"$(INTDIR)\Ai.sbr" \
	"$(INTDIR)\AiAccess.sbr" \
	"$(INTDIR)\Aibtank.sbr" \
	"$(INTDIR)\AiInput.sbr" \
	"$(INTDIR)\air.sbr" \
	"$(INTDIR)\Airouter.sbr" \
	"$(INTDIR)\aix.sbr" \
	"$(INTDIR)\Anim.sbr" \
	"$(INTDIR)\AnimFile.sbr" \
	"$(INTDIR)\Army.sbr" \
	"$(INTDIR)\ArmyMen.sbr" \
	"$(INTDIR)\ArmyMsg.sbr" \
	"$(INTDIR)\Asset.sbr" \
	"$(INTDIR)\AssetMsg.sbr" \
	"$(INTDIR)\Audio.sbr" \
	"$(INTDIR)\Avatar.sbr" \
	"$(INTDIR)\BmpText.sbr" \
	"$(INTDIR)\cinema.sbr" \
	"$(INTDIR)\comm.sbr" \
	"$(INTDIR)\Commands.sbr" \
	"$(INTDIR)\CSpriteCatalog.sbr" \
	"$(INTDIR)\CSpriteSequence.sbr" \
	"$(INTDIR)\damage.sbr" \
	"$(INTDIR)\Dd.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\Dialog.sbr" \
	"$(INTDIR)\Disp.sbr" \
	"$(INTDIR)\DrawObject.sbr" \
	"$(INTDIR)\Error.sbr" \
	"$(INTDIR)\event.sbr" \
	"$(INTDIR)\explosions.sbr" \
	"$(INTDIR)\fileio.sbr" \
	"$(INTDIR)\Float.sbr" \
	"$(INTDIR)\FloatMsg.sbr" \
	"$(INTDIR)\GameFlow.sbr" \
	"$(INTDIR)\gameproc.sbr" \
	"$(INTDIR)\guid.sbr" \
	"$(INTDIR)\husk.sbr" \
	"$(INTDIR)\Input.sbr" \
	"$(INTDIR)\Item.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Map.sbr" \
	"$(INTDIR)\miscfile.sbr" \
	"$(INTDIR)\Movie.sbr" \
	"$(INTDIR)\Msg.sbr" \
	"$(INTDIR)\newdoor.sbr" \
	"$(INTDIR)\object.sbr" \
	"$(INTDIR)\ObjectMsg.sbr" \
	"$(INTDIR)\pad.sbr" \
	"$(INTDIR)\Rmerror.sbr" \
	"$(INTDIR)\Sarge.sbr" \
	"$(INTDIR)\SargeMsg.sbr" \
	"$(INTDIR)\scenario.sbr" \
	"$(INTDIR)\Screen.sbr" \
	"$(INTDIR)\ScreenBtn.sbr" \
	"$(INTDIR)\ScreenObj.sbr" \
	"$(INTDIR)\scripts.sbr" \
	"$(INTDIR)\Sfx.sbr" \
	"$(INTDIR)\Smacker.sbr" \
	"$(INTDIR)\Snd.sbr" \
	"$(INTDIR)\Sprite.sbr" \
	"$(INTDIR)\States.sbr" \
	"$(INTDIR)\Stats.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\stratmap.sbr" \
	"$(INTDIR)\strm.sbr" \
	"$(INTDIR)\Tad.sbr" \
	"$(INTDIR)\TadPriv.sbr" \
	"$(INTDIR)\Text.sbr" \
	"$(INTDIR)\TextData.sbr" \
	"$(INTDIR)\trooper.sbr" \
	"$(INTDIR)\ui.sbr" \
	"$(INTDIR)\Unit.sbr" \
	"$(INTDIR)\UnitMsg.sbr" \
	"$(INTDIR)\util.sbr" \
	"$(INTDIR)\Vehicle.sbr" \
	"$(INTDIR)\VehicleMsg.sbr" \
	"$(INTDIR)\Voice.sbr" \
	"$(INTDIR)\Weapon.sbr" \
	"$(INTDIR)\wobject.sbr"

"$(OUTDIR)\Armymen.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 dxguid.lib ddraw.lib dsound.lib dinput.lib dplayx.lib winmm.lib vfw32.lib comctl32.lib version.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"Debug/ArmymenDebug.exe"
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib comctl32.lib version.lib smackw32.lib ole32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"ObjectDebug/ArmymenObjects.exe"
# SUBTRACT LINK32 /pdb:none /map
LINK32_FLAGS=dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib\
 comctl32.lib version.lib smackw32.lib ole32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/ArmymenObjects.pdb" /debug /machine:I386\
 /nodefaultlib:"LIBC" /out:"ObjectDebug/ArmymenObjects.exe" 
LINK32_OBJS= \
	"$(INTDIR)\3DONetwork.obj" \
	"$(INTDIR)\Ai.obj" \
	"$(INTDIR)\AiAccess.obj" \
	"$(INTDIR)\Aibtank.obj" \
	"$(INTDIR)\AiInput.obj" \
	"$(INTDIR)\air.obj" \
	"$(INTDIR)\Airouter.obj" \
	"$(INTDIR)\aix.obj" \
	"$(INTDIR)\Anim.obj" \
	"$(INTDIR)\AnimFile.obj" \
	"$(INTDIR)\Army.obj" \
	"$(INTDIR)\ArmyMen.obj" \
	"$(INTDIR)\ArmyMen.res" \
	"$(INTDIR)\ArmyMsg.obj" \
	"$(INTDIR)\Asset.obj" \
	"$(INTDIR)\AssetMsg.obj" \
	"$(INTDIR)\Audio.obj" \
	"$(INTDIR)\Avatar.obj" \
	"$(INTDIR)\BmpText.obj" \
	"$(INTDIR)\cinema.obj" \
	"$(INTDIR)\comm.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\damage.obj" \
	"$(INTDIR)\Dd.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\Disp.obj" \
	"$(INTDIR)\DrawObject.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\event.obj" \
	"$(INTDIR)\explosions.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\Float.obj" \
	"$(INTDIR)\FloatMsg.obj" \
	"$(INTDIR)\GameFlow.obj" \
	"$(INTDIR)\gameproc.obj" \
	"$(INTDIR)\guid.obj" \
	"$(INTDIR)\husk.obj" \
	"$(INTDIR)\Input.obj" \
	"$(INTDIR)\Item.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Map.obj" \
	"$(INTDIR)\miscfile.obj" \
	"$(INTDIR)\Movie.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\newdoor.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\ObjectMsg.obj" \
	"$(INTDIR)\pad.obj" \
	"$(INTDIR)\Rmerror.obj" \
	"$(INTDIR)\Sarge.obj" \
	"$(INTDIR)\SargeMsg.obj" \
	"$(INTDIR)\scenario.obj" \
	"$(INTDIR)\Screen.obj" \
	"$(INTDIR)\ScreenBtn.obj" \
	"$(INTDIR)\ScreenObj.obj" \
	"$(INTDIR)\scripts.obj" \
	"$(INTDIR)\Sfx.obj" \
	"$(INTDIR)\Smacker.obj" \
	"$(INTDIR)\Snd.obj" \
	"$(INTDIR)\Sprite.obj" \
	"$(INTDIR)\States.obj" \
	"$(INTDIR)\Stats.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stratmap.obj" \
	"$(INTDIR)\strm.obj" \
	"$(INTDIR)\Tad.obj" \
	"$(INTDIR)\TadPriv.obj" \
	"$(INTDIR)\Text.obj" \
	"$(INTDIR)\TextData.obj" \
	"$(INTDIR)\trooper.obj" \
	"$(INTDIR)\ui.obj" \
	"$(INTDIR)\Unit.obj" \
	"$(INTDIR)\UnitMsg.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Vehicle.obj" \
	"$(INTDIR)\VehicleMsg.obj" \
	"$(INTDIR)\Voice.obj" \
	"$(INTDIR)\Weapon.obj" \
	"$(INTDIR)\wobject.obj"

".\ObjectDebug\ArmymenObjects.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
InputPath=.\ObjectDebug\ArmymenObjects.exe
InputName=ArmymenObjects
SOURCE=$(InputPath)

"H:\RunTime\$(InputName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(InputPath) H:\RunTime\$(InputName).exe

# End Custom Build

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BC"
# PROP BASE Intermediate_Dir "BC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "BC"
# PROP Intermediate_Dir "BC"
# PROP Target_Dir ""
OUTDIR=.\BC
INTDIR=.\BC

ALL : "$(OUTDIR)\ArmymenDebug.exe" "$(OUTDIR)\Armymen.bsc"

CLEAN : 
	-@erase "$(INTDIR)\3DONetwork.obj"
	-@erase "$(INTDIR)\3DONetwork.sbr"
	-@erase "$(INTDIR)\Ai.obj"
	-@erase "$(INTDIR)\Ai.sbr"
	-@erase "$(INTDIR)\AiAccess.obj"
	-@erase "$(INTDIR)\AiAccess.sbr"
	-@erase "$(INTDIR)\Aibtank.obj"
	-@erase "$(INTDIR)\Aibtank.sbr"
	-@erase "$(INTDIR)\AiInput.obj"
	-@erase "$(INTDIR)\AiInput.sbr"
	-@erase "$(INTDIR)\air.obj"
	-@erase "$(INTDIR)\air.sbr"
	-@erase "$(INTDIR)\Airouter.obj"
	-@erase "$(INTDIR)\Airouter.sbr"
	-@erase "$(INTDIR)\aix.obj"
	-@erase "$(INTDIR)\aix.sbr"
	-@erase "$(INTDIR)\Anim.obj"
	-@erase "$(INTDIR)\Anim.sbr"
	-@erase "$(INTDIR)\AnimFile.obj"
	-@erase "$(INTDIR)\AnimFile.sbr"
	-@erase "$(INTDIR)\Army.obj"
	-@erase "$(INTDIR)\Army.sbr"
	-@erase "$(INTDIR)\ArmyMen.obj"
	-@erase "$(INTDIR)\Armymen.pch"
	-@erase "$(INTDIR)\ArmyMen.res"
	-@erase "$(INTDIR)\ArmyMen.sbr"
	-@erase "$(INTDIR)\ArmyMsg.obj"
	-@erase "$(INTDIR)\ArmyMsg.sbr"
	-@erase "$(INTDIR)\Asset.obj"
	-@erase "$(INTDIR)\Asset.sbr"
	-@erase "$(INTDIR)\AssetMsg.obj"
	-@erase "$(INTDIR)\AssetMsg.sbr"
	-@erase "$(INTDIR)\Audio.obj"
	-@erase "$(INTDIR)\Audio.sbr"
	-@erase "$(INTDIR)\Avatar.obj"
	-@erase "$(INTDIR)\Avatar.sbr"
	-@erase "$(INTDIR)\BmpText.obj"
	-@erase "$(INTDIR)\BmpText.sbr"
	-@erase "$(INTDIR)\cinema.obj"
	-@erase "$(INTDIR)\cinema.sbr"
	-@erase "$(INTDIR)\comm.obj"
	-@erase "$(INTDIR)\comm.sbr"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\Commands.sbr"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.sbr"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CSpriteSequence.sbr"
	-@erase "$(INTDIR)\damage.obj"
	-@erase "$(INTDIR)\damage.sbr"
	-@erase "$(INTDIR)\Dd.obj"
	-@erase "$(INTDIR)\Dd.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Dialog.sbr"
	-@erase "$(INTDIR)\Disp.obj"
	-@erase "$(INTDIR)\Disp.sbr"
	-@erase "$(INTDIR)\DrawObject.obj"
	-@erase "$(INTDIR)\DrawObject.sbr"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\Error.sbr"
	-@erase "$(INTDIR)\event.obj"
	-@erase "$(INTDIR)\event.sbr"
	-@erase "$(INTDIR)\explosions.obj"
	-@erase "$(INTDIR)\explosions.sbr"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\fileio.sbr"
	-@erase "$(INTDIR)\Float.obj"
	-@erase "$(INTDIR)\Float.sbr"
	-@erase "$(INTDIR)\FloatMsg.obj"
	-@erase "$(INTDIR)\FloatMsg.sbr"
	-@erase "$(INTDIR)\GameFlow.obj"
	-@erase "$(INTDIR)\GameFlow.sbr"
	-@erase "$(INTDIR)\gameproc.obj"
	-@erase "$(INTDIR)\gameproc.sbr"
	-@erase "$(INTDIR)\guid.obj"
	-@erase "$(INTDIR)\guid.sbr"
	-@erase "$(INTDIR)\husk.obj"
	-@erase "$(INTDIR)\husk.sbr"
	-@erase "$(INTDIR)\Input.obj"
	-@erase "$(INTDIR)\Input.sbr"
	-@erase "$(INTDIR)\Item.obj"
	-@erase "$(INTDIR)\Item.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Map.obj"
	-@erase "$(INTDIR)\Map.sbr"
	-@erase "$(INTDIR)\miscfile.obj"
	-@erase "$(INTDIR)\miscfile.sbr"
	-@erase "$(INTDIR)\Movie.obj"
	-@erase "$(INTDIR)\Movie.sbr"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Msg.sbr"
	-@erase "$(INTDIR)\newdoor.obj"
	-@erase "$(INTDIR)\newdoor.sbr"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\object.sbr"
	-@erase "$(INTDIR)\ObjectMsg.obj"
	-@erase "$(INTDIR)\ObjectMsg.sbr"
	-@erase "$(INTDIR)\pad.obj"
	-@erase "$(INTDIR)\pad.sbr"
	-@erase "$(INTDIR)\Rmerror.obj"
	-@erase "$(INTDIR)\Rmerror.sbr"
	-@erase "$(INTDIR)\Sarge.obj"
	-@erase "$(INTDIR)\Sarge.sbr"
	-@erase "$(INTDIR)\SargeMsg.obj"
	-@erase "$(INTDIR)\SargeMsg.sbr"
	-@erase "$(INTDIR)\scenario.obj"
	-@erase "$(INTDIR)\scenario.sbr"
	-@erase "$(INTDIR)\Screen.obj"
	-@erase "$(INTDIR)\Screen.sbr"
	-@erase "$(INTDIR)\ScreenBtn.obj"
	-@erase "$(INTDIR)\ScreenBtn.sbr"
	-@erase "$(INTDIR)\ScreenObj.obj"
	-@erase "$(INTDIR)\ScreenObj.sbr"
	-@erase "$(INTDIR)\scripts.obj"
	-@erase "$(INTDIR)\scripts.sbr"
	-@erase "$(INTDIR)\Sfx.obj"
	-@erase "$(INTDIR)\Sfx.sbr"
	-@erase "$(INTDIR)\Smacker.obj"
	-@erase "$(INTDIR)\Smacker.sbr"
	-@erase "$(INTDIR)\Snd.obj"
	-@erase "$(INTDIR)\Snd.sbr"
	-@erase "$(INTDIR)\Sprite.obj"
	-@erase "$(INTDIR)\Sprite.sbr"
	-@erase "$(INTDIR)\States.obj"
	-@erase "$(INTDIR)\States.sbr"
	-@erase "$(INTDIR)\Stats.obj"
	-@erase "$(INTDIR)\Stats.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\stratmap.obj"
	-@erase "$(INTDIR)\stratmap.sbr"
	-@erase "$(INTDIR)\strm.obj"
	-@erase "$(INTDIR)\strm.sbr"
	-@erase "$(INTDIR)\Tad.obj"
	-@erase "$(INTDIR)\Tad.sbr"
	-@erase "$(INTDIR)\TadPriv.obj"
	-@erase "$(INTDIR)\TadPriv.sbr"
	-@erase "$(INTDIR)\Text.obj"
	-@erase "$(INTDIR)\Text.sbr"
	-@erase "$(INTDIR)\TextData.obj"
	-@erase "$(INTDIR)\TextData.sbr"
	-@erase "$(INTDIR)\trooper.obj"
	-@erase "$(INTDIR)\trooper.sbr"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\ui.sbr"
	-@erase "$(INTDIR)\Unit.obj"
	-@erase "$(INTDIR)\Unit.sbr"
	-@erase "$(INTDIR)\UnitMsg.obj"
	-@erase "$(INTDIR)\UnitMsg.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Vehicle.obj"
	-@erase "$(INTDIR)\Vehicle.sbr"
	-@erase "$(INTDIR)\VehicleMsg.obj"
	-@erase "$(INTDIR)\VehicleMsg.sbr"
	-@erase "$(INTDIR)\Voice.obj"
	-@erase "$(INTDIR)\Voice.sbr"
	-@erase "$(INTDIR)\Weapon.obj"
	-@erase "$(INTDIR)\Weapon.sbr"
	-@erase "$(INTDIR)\wobject.obj"
	-@erase "$(INTDIR)\wobject.sbr"
	-@erase "$(OUTDIR)\Armymen.bsc"
	-@erase "$(OUTDIR)\ArmymenDebug.exe"
	-@erase "$(OUTDIR)\ArmymenDebug.ilk"
	-@erase "$(OUTDIR)\ArmymenDebug.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D "AUDIO_OFF" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D "AUDIO_OFF" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "AUDIO_OFF" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\BC/
CPP_SBRS=.\BC/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ArmyMen.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Armymen.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\3DONetwork.sbr" \
	"$(INTDIR)\Ai.sbr" \
	"$(INTDIR)\AiAccess.sbr" \
	"$(INTDIR)\Aibtank.sbr" \
	"$(INTDIR)\AiInput.sbr" \
	"$(INTDIR)\air.sbr" \
	"$(INTDIR)\Airouter.sbr" \
	"$(INTDIR)\aix.sbr" \
	"$(INTDIR)\Anim.sbr" \
	"$(INTDIR)\AnimFile.sbr" \
	"$(INTDIR)\Army.sbr" \
	"$(INTDIR)\ArmyMen.sbr" \
	"$(INTDIR)\ArmyMsg.sbr" \
	"$(INTDIR)\Asset.sbr" \
	"$(INTDIR)\AssetMsg.sbr" \
	"$(INTDIR)\Audio.sbr" \
	"$(INTDIR)\Avatar.sbr" \
	"$(INTDIR)\BmpText.sbr" \
	"$(INTDIR)\cinema.sbr" \
	"$(INTDIR)\comm.sbr" \
	"$(INTDIR)\Commands.sbr" \
	"$(INTDIR)\CSpriteCatalog.sbr" \
	"$(INTDIR)\CSpriteSequence.sbr" \
	"$(INTDIR)\damage.sbr" \
	"$(INTDIR)\Dd.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\Dialog.sbr" \
	"$(INTDIR)\Disp.sbr" \
	"$(INTDIR)\DrawObject.sbr" \
	"$(INTDIR)\Error.sbr" \
	"$(INTDIR)\event.sbr" \
	"$(INTDIR)\explosions.sbr" \
	"$(INTDIR)\fileio.sbr" \
	"$(INTDIR)\Float.sbr" \
	"$(INTDIR)\FloatMsg.sbr" \
	"$(INTDIR)\GameFlow.sbr" \
	"$(INTDIR)\gameproc.sbr" \
	"$(INTDIR)\guid.sbr" \
	"$(INTDIR)\husk.sbr" \
	"$(INTDIR)\Input.sbr" \
	"$(INTDIR)\Item.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Map.sbr" \
	"$(INTDIR)\miscfile.sbr" \
	"$(INTDIR)\Movie.sbr" \
	"$(INTDIR)\Msg.sbr" \
	"$(INTDIR)\newdoor.sbr" \
	"$(INTDIR)\object.sbr" \
	"$(INTDIR)\ObjectMsg.sbr" \
	"$(INTDIR)\pad.sbr" \
	"$(INTDIR)\Rmerror.sbr" \
	"$(INTDIR)\Sarge.sbr" \
	"$(INTDIR)\SargeMsg.sbr" \
	"$(INTDIR)\scenario.sbr" \
	"$(INTDIR)\Screen.sbr" \
	"$(INTDIR)\ScreenBtn.sbr" \
	"$(INTDIR)\ScreenObj.sbr" \
	"$(INTDIR)\scripts.sbr" \
	"$(INTDIR)\Sfx.sbr" \
	"$(INTDIR)\Smacker.sbr" \
	"$(INTDIR)\Snd.sbr" \
	"$(INTDIR)\Sprite.sbr" \
	"$(INTDIR)\States.sbr" \
	"$(INTDIR)\Stats.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\stratmap.sbr" \
	"$(INTDIR)\strm.sbr" \
	"$(INTDIR)\Tad.sbr" \
	"$(INTDIR)\TadPriv.sbr" \
	"$(INTDIR)\Text.sbr" \
	"$(INTDIR)\TextData.sbr" \
	"$(INTDIR)\trooper.sbr" \
	"$(INTDIR)\ui.sbr" \
	"$(INTDIR)\Unit.sbr" \
	"$(INTDIR)\UnitMsg.sbr" \
	"$(INTDIR)\util.sbr" \
	"$(INTDIR)\Vehicle.sbr" \
	"$(INTDIR)\VehicleMsg.sbr" \
	"$(INTDIR)\Voice.sbr" \
	"$(INTDIR)\Weapon.sbr" \
	"$(INTDIR)\wobject.sbr"

"$(OUTDIR)\Armymen.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ole32.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib comctl32.lib version.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"Debug/ArmymenDebug.exe"
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 ole32.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib vfw32.lib comctl32.lib version.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"BC/ArmymenDebug.exe"
# SUBTRACT LINK32 /pdb:none /map
LINK32_FLAGS=ole32.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib\
 vfw32.lib comctl32.lib version.lib smackw32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/ArmymenDebug.pdb" /debug /machine:I386\
 /nodefaultlib:"LIBC" /out:"$(OUTDIR)/ArmymenDebug.exe" 
LINK32_OBJS= \
	"$(INTDIR)\3DONetwork.obj" \
	"$(INTDIR)\Ai.obj" \
	"$(INTDIR)\AiAccess.obj" \
	"$(INTDIR)\Aibtank.obj" \
	"$(INTDIR)\AiInput.obj" \
	"$(INTDIR)\air.obj" \
	"$(INTDIR)\Airouter.obj" \
	"$(INTDIR)\aix.obj" \
	"$(INTDIR)\Anim.obj" \
	"$(INTDIR)\AnimFile.obj" \
	"$(INTDIR)\Army.obj" \
	"$(INTDIR)\ArmyMen.obj" \
	"$(INTDIR)\ArmyMen.res" \
	"$(INTDIR)\ArmyMsg.obj" \
	"$(INTDIR)\Asset.obj" \
	"$(INTDIR)\AssetMsg.obj" \
	"$(INTDIR)\Audio.obj" \
	"$(INTDIR)\Avatar.obj" \
	"$(INTDIR)\BmpText.obj" \
	"$(INTDIR)\cinema.obj" \
	"$(INTDIR)\comm.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\damage.obj" \
	"$(INTDIR)\Dd.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\Disp.obj" \
	"$(INTDIR)\DrawObject.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\event.obj" \
	"$(INTDIR)\explosions.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\Float.obj" \
	"$(INTDIR)\FloatMsg.obj" \
	"$(INTDIR)\GameFlow.obj" \
	"$(INTDIR)\gameproc.obj" \
	"$(INTDIR)\guid.obj" \
	"$(INTDIR)\husk.obj" \
	"$(INTDIR)\Input.obj" \
	"$(INTDIR)\Item.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Map.obj" \
	"$(INTDIR)\miscfile.obj" \
	"$(INTDIR)\Movie.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\newdoor.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\ObjectMsg.obj" \
	"$(INTDIR)\pad.obj" \
	"$(INTDIR)\Rmerror.obj" \
	"$(INTDIR)\Sarge.obj" \
	"$(INTDIR)\SargeMsg.obj" \
	"$(INTDIR)\scenario.obj" \
	"$(INTDIR)\Screen.obj" \
	"$(INTDIR)\ScreenBtn.obj" \
	"$(INTDIR)\ScreenObj.obj" \
	"$(INTDIR)\scripts.obj" \
	"$(INTDIR)\Sfx.obj" \
	"$(INTDIR)\Smacker.obj" \
	"$(INTDIR)\Snd.obj" \
	"$(INTDIR)\Sprite.obj" \
	"$(INTDIR)\States.obj" \
	"$(INTDIR)\Stats.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stratmap.obj" \
	"$(INTDIR)\strm.obj" \
	"$(INTDIR)\Tad.obj" \
	"$(INTDIR)\TadPriv.obj" \
	"$(INTDIR)\Text.obj" \
	"$(INTDIR)\TextData.obj" \
	"$(INTDIR)\trooper.obj" \
	"$(INTDIR)\ui.obj" \
	"$(INTDIR)\Unit.obj" \
	"$(INTDIR)\UnitMsg.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Vehicle.obj" \
	"$(INTDIR)\VehicleMsg.obj" \
	"$(INTDIR)\Voice.obj" \
	"$(INTDIR)\Weapon.obj" \
	"$(INTDIR)\wobject.obj"

"$(OUTDIR)\ArmymenDebug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "ArmyMen - Win32 Release"
# Name "ArmyMen - Win32 Debug"
# Name "ArmyMen - Win32 Remote Debug"
# Name "ArmyMen - Win32 Object Debug"
# Name "ArmyMen - Win32 BC"

!IF  "$(CFG)" == "ArmyMen - Win32 Release"

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\Dd.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /Gr /MD /W3 /GX /Zi /O2 /D "NDBUG" /D "BACK_BUFFER_SYSTEM" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D\
 "FINAL" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Armymen.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Armymen.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_AUDIO_OFF" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Armymen.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Armymen.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "AUDIO_OFF" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Armymen.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ArmyMen.cpp
DEP_CPP_ARMYM=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\Dialog.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Scenario.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\ArmyMen.obj" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMen.sbr" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\ArmyMen.obj" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMen.sbr" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\ArmyMen.obj" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMen.sbr" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\ArmyMen.obj" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMen.sbr" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\ArmyMen.obj" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMen.sbr" : $(SOURCE) $(DEP_CPP_ARMYM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Audio.cpp
DEP_CPP_AUDIO=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Audio.obj" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Audio.sbr" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Audio.obj" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Audio.sbr" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Audio.obj" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Audio.sbr" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Audio.obj" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Audio.sbr" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Audio.obj" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Audio.sbr" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dd.cpp
DEP_CPP_DD_CP=\
	".\Armymen.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\DrawObject.h"\
	".\Error.h"\
	".\fileio.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Rmerror.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Dd.obj" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dd.sbr" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Dd.obj" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dd.sbr" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Dd.obj" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dd.sbr" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Dd.obj" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dd.sbr" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Dd.obj" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dd.sbr" : $(SOURCE) $(DEP_CPP_DD_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\comm.h"\
	".\Commands.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\Dialog.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\DrawObject.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Movie.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rad.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\Scenario.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Smack.h"\
	".\Smacker.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\States.h"\
	".\Stats.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


BuildCmds= \
	$(CPP) /nologo /Gr /MD /W3 /GX /Zi /O2 /D "NDBUG" /D "BACK_BUFFER_SYSTEM" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D\
 "FINAL" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"

# ADD BASE CPP /D "DEBUG_TIMING"
# ADD CPP /D "DEBUG_TIMING"

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "DEBUG_TIMING" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"

# ADD BASE CPP /D "DEBUG_TIMING"
# ADD CPP /D "DEBUG_TIMING"

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_AUDIO_OFF" /D "_OBJECT_DEBUG" /D\
 "DEBUG_TIMING" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"

# ADD BASE CPP /D "DEBUG_TIMING"
# ADD CPP /D "DEBUG_TIMING"

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_OBJECT_DEBUG" /D "DEBUG_TIMING"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"

# ADD BASE CPP /D "DEBUG_TIMING"
# ADD CPP /D "DEBUG_TIMING"

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "AUDIO_OFF" /D "DEBUG_TIMING" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Map.cpp
DEP_CPP_MAP_C=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\map.dat"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Scenario.h"\
	".\scripts.h"\
	".\Snd.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"

# ADD CPP /D "OLD_NAMES"

BuildCmds= \
	$(CPP) /nologo /Gr /MD /W3 /GX /Zi /O2 /D "NDBUG" /D "BACK_BUFFER_SYSTEM" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D\
 "FINAL" /D "OLD_NAMES" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\Map.sbr" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\Map.sbr" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_AUDIO_OFF" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\Map.sbr" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\Map.sbr" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "AUDIO_OFF" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\Map.sbr" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rmerror.cpp
DEP_CPP_RMERR=\
	".\Dd.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Rmerror.obj" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Rmerror.sbr" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Rmerror.obj" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Rmerror.sbr" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Rmerror.obj" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Rmerror.sbr" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Rmerror.obj" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Rmerror.sbr" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Rmerror.obj" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Rmerror.sbr" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sfx.cpp
DEP_CPP_SFX_C=\
	".\Dd.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Sfx.obj" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sfx.sbr" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Sfx.obj" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sfx.sbr" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Sfx.obj" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sfx.sbr" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Sfx.obj" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sfx.sbr" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Sfx.obj" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sfx.sbr" : $(SOURCE) $(DEP_CPP_SFX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Snd.cpp
DEP_CPP_SND_C=\
	".\Dd.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Snd.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Snd.obj" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Snd.sbr" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Snd.obj" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Snd.sbr" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Snd.obj" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Snd.sbr" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Snd.obj" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Snd.sbr" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Snd.obj" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Snd.sbr" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ArmyMen.rc
DEP_RSC_ARMYME=\
	".\res\ArmyMen.ico"\
	".\res\Armymen.rc2"\
	".\res\csession.bmp"\
	".\res\default.cur"\
	".\res\osession.bmp"\
	".\res\player.bmp"\
	".\res\player2.bmp"\
	".\res\player3.bmp"\
	".\res\player4.bmp"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\ArmyMen.res" : $(SOURCE) $(DEP_RSC_ARMYME) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\ArmyMen.res" : $(SOURCE) $(DEP_RSC_ARMYME) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\ArmyMen.res" : $(SOURCE) $(DEP_RSC_ARMYME) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\ArmyMen.res" : $(SOURCE) $(DEP_RSC_ARMYME) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\ArmyMen.res" : $(SOURCE) $(DEP_RSC_ARMYME) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\strm.cpp
DEP_CPP_STRM_=\
	".\Dd.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Snd.h"\
	".\Stdafx.h"\
	".\Strm.h"\
	".\types.h"\
	".\util.h"\
	".\Voice.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\strm.obj" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\strm.sbr" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\strm.obj" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\strm.sbr" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\strm.obj" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\strm.sbr" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\strm.obj" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\strm.sbr" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\strm.obj" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\strm.sbr" : $(SOURCE) $(DEP_CPP_STRM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sprite.cpp
DEP_CPP_SPRIT=\
	".\Ai.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\Globals.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Text.cpp
DEP_CPP_TEXT_=\
	".\bmptext.h"\
	".\Dd.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Text.obj" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Text.sbr" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Text.obj" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Text.sbr" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Text.obj" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Text.sbr" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Text.obj" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Text.sbr" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Text.obj" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Text.sbr" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Anim.cpp
DEP_CPP_ANIM_=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\AnimFile.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Anim.obj" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Anim.sbr" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Anim.obj" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Anim.sbr" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Anim.obj" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Anim.sbr" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Anim.obj" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Anim.sbr" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Anim.obj" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Anim.sbr" : $(SOURCE) $(DEP_CPP_ANIM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Vehicle.cpp
DEP_CPP_VEHIC=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\AnimFile.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Commands.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\husk.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\pad.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.dat"\
	".\Vehicle.h"\
	".\VehicleMsg.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Vehicle.obj" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Vehicle.sbr" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Vehicle.obj" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Vehicle.sbr" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Vehicle.obj" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Vehicle.sbr" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Vehicle.obj" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Vehicle.sbr" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Vehicle.obj" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Vehicle.sbr" : $(SOURCE) $(DEP_CPP_VEHIC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Army.cpp
DEP_CPP_ARMY_=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\debug.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\pad.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\Scenario.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Snd.h"\
	".\Sprite.h"\
	".\Stats.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\UnitMsg.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Army.obj" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Army.sbr" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Army.obj" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Army.sbr" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Army.obj" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Army.sbr" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Army.obj" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Army.sbr" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Army.obj" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Army.sbr" : $(SOURCE) $(DEP_CPP_ARMY_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Unit.cpp
DEP_CPP_UNIT_=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\air.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\AnimFile.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\pad.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\SargeMsg.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\UnitMsg.h"\
	".\unitP.h"\
	".\UnitText.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\VehicleMsg.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Unit.obj" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Unit.sbr" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Unit.obj" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Unit.sbr" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Unit.obj" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Unit.sbr" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Unit.obj" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Unit.sbr" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Unit.obj" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Unit.sbr" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Input.cpp
DEP_CPP_INPUT=\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Commands.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\DrawObject.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Input.sbr" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Input.sbr" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Input.sbr" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Input.sbr" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Input.sbr" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\guid.c

!IF  "$(CFG)" == "ArmyMen - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /Gr /MD /W3 /GX /Zi /O2 /D "NDBUG" /D "BACK_BUFFER_SYSTEM" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D\
 "FINAL" /Fr"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\guid.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\guid.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /FR"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\guid.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\guid.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_AUDIO_OFF" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\guid.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\guid.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\guid.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\guid.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "AUDIO_OFF" /FR"$(INTDIR)/" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\guid.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\guid.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\miscfile.cpp
DEP_CPP_MISCF=\
	".\Dd.h"\
	".\Error.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\miscfile.h"\
	".\Rmerror.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\miscfile.obj" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\miscfile.sbr" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\miscfile.obj" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\miscfile.sbr" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\miscfile.obj" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\miscfile.sbr" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\miscfile.obj" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\miscfile.sbr" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\miscfile.obj" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\miscfile.sbr" : $(SOURCE) $(DEP_CPP_MISCF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Msg.cpp
DEP_CPP_MSG_C=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Msg.sbr" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Msg.sbr" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Msg.sbr" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Msg.sbr" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Msg.sbr" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scenario.cpp
DEP_CPP_SCENA=\
	".\Ai.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Scenario.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\scenario.obj" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scenario.sbr" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\scenario.obj" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scenario.sbr" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\scenario.obj" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scenario.sbr" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\scenario.obj" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scenario.sbr" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\scenario.obj" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scenario.sbr" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AiInput.cpp
DEP_CPP_AIINP=\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stats.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\AiInput.obj" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiInput.sbr" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\AiInput.obj" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiInput.sbr" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\AiInput.obj" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiInput.sbr" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\AiInput.obj" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiInput.sbr" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\AiInput.obj" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiInput.sbr" : $(SOURCE) $(DEP_CPP_AIINP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tad.cpp
DEP_CPP_TAD_C=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Tad.obj" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Tad.sbr" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Tad.obj" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Tad.sbr" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Tad.obj" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Tad.sbr" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Tad.obj" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Tad.sbr" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Tad.obj" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Tad.sbr" : $(SOURCE) $(DEP_CPP_TAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ai.cpp
DEP_CPP_AI_CP=\
	".\Ai.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Ai.obj" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Ai.sbr" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Ai.obj" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Ai.sbr" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Ai.obj" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Ai.sbr" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Ai.obj" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Ai.sbr" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Ai.obj" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Ai.sbr" : $(SOURCE) $(DEP_CPP_AI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Error.cpp
DEP_CPP_ERROR=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Error.sbr" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Error.sbr" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Error.sbr" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Error.sbr" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Error.sbr" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GameFlow.cpp
DEP_CPP_GAMEF=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\air.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Commands.h"\
	".\Dd.h"\
	".\debug.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\DrawObject.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Movie.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\pad.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\Scenario.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\States.h"\
	".\Stats.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\GameFlow.obj" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\GameFlow.sbr" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\GameFlow.obj" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\GameFlow.sbr" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\GameFlow.obj" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\GameFlow.sbr" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\GameFlow.obj" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\GameFlow.sbr" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\GameFlow.obj" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\GameFlow.sbr" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gameproc.cpp
DEP_CPP_GAMEP=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\gameproc.obj" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\gameproc.sbr" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\gameproc.obj" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\gameproc.sbr" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\gameproc.obj" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\gameproc.sbr" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\gameproc.obj" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\gameproc.sbr" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\gameproc.obj" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\gameproc.sbr" : $(SOURCE) $(DEP_CPP_GAMEP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\comm.cpp
DEP_CPP_COMM_=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\comm.obj" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\comm.sbr" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\comm.obj" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\comm.sbr" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\comm.obj" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\comm.sbr" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\comm.obj" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\comm.sbr" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\comm.obj" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\comm.sbr" : $(SOURCE) $(DEP_CPP_COMM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrawObject.cpp
DEP_CPP_DRAWO=\
	".\Armymen.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\DrawObject.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Rmerror.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\DrawObject.obj" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\DrawObject.sbr" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\DrawObject.obj" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\DrawObject.sbr" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\DrawObject.obj" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\DrawObject.sbr" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\DrawObject.obj" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\DrawObject.sbr" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\DrawObject.obj" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\DrawObject.sbr" : $(SOURCE) $(DEP_CPP_DRAWO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AiAccess.cpp
DEP_CPP_AIACC=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\husk.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\AiAccess.obj" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiAccess.sbr" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\AiAccess.obj" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiAccess.sbr" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\AiAccess.obj" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiAccess.sbr" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\AiAccess.obj" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiAccess.sbr" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\AiAccess.obj" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AiAccess.sbr" : $(SOURCE) $(DEP_CPP_AIACC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSpriteCatalog.cpp
DEP_CPP_CSPRI=\
	".\Ai.h"\
	".\Anim.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\CSpriteCatalog.obj" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteCatalog.sbr" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\CSpriteCatalog.obj" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteCatalog.sbr" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\CSpriteCatalog.obj" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteCatalog.sbr" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\CSpriteCatalog.obj" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteCatalog.sbr" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\CSpriteCatalog.obj" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteCatalog.sbr" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSpriteSequence.cpp
DEP_CPP_CSPRIT=\
	".\CSpriteSequence.h"\
	".\Dd.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\CSpriteSequence.obj" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteSequence.sbr" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\CSpriteSequence.obj" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteSequence.sbr" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\CSpriteSequence.obj" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteSequence.sbr" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\CSpriteSequence.obj" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteSequence.sbr" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\CSpriteSequence.obj" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\CSpriteSequence.sbr" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AnimFile.cpp
DEP_CPP_ANIMF=\
	".\Ai.h"\
	".\Anim.h"\
	".\AnimFile.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\AnimFile.obj" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AnimFile.sbr" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\AnimFile.obj" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AnimFile.sbr" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\AnimFile.obj" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AnimFile.sbr" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\AnimFile.obj" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AnimFile.sbr" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\AnimFile.obj" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AnimFile.sbr" : $(SOURCE) $(DEP_CPP_ANIMF) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\aix.cpp
DEP_CPP_AIX_C=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\comm.h"\
	".\Commands.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\ObjectMsg.h"\
	".\pad.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Snd.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\aix.obj" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\aix.sbr" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\aix.obj" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\aix.sbr" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\aix.obj" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\aix.sbr" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\aix.obj" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\aix.sbr" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\aix.obj" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\aix.sbr" : $(SOURCE) $(DEP_CPP_AIX_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\newdoor.cpp
DEP_CPP_NEWDO=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\newdoor.obj" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\newdoor.sbr" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\newdoor.obj" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\newdoor.sbr" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\newdoor.obj" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\newdoor.sbr" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\newdoor.obj" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\newdoor.sbr" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\newdoor.obj" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\newdoor.sbr" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Disp.cpp
DEP_CPP_DISP_=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Disp.obj" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Disp.sbr" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Disp.obj" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Disp.sbr" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Disp.obj" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Disp.sbr" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Disp.obj" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Disp.sbr" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Disp.obj" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Disp.sbr" : $(SOURCE) $(DEP_CPP_DISP_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Aibtank.cpp
DEP_CPP_AIBTA=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Aibtank.obj" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Aibtank.sbr" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Aibtank.obj" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Aibtank.sbr" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Aibtank.obj" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Aibtank.sbr" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Aibtank.obj" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Aibtank.sbr" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Aibtank.obj" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Aibtank.sbr" : $(SOURCE) $(DEP_CPP_AIBTA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\damage.cpp
DEP_CPP_DAMAG=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\AssetMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\husk.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\ObjectMsg.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\damage.obj" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\damage.sbr" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\damage.obj" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\damage.sbr" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\damage.obj" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\damage.sbr" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\damage.obj" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\damage.sbr" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\damage.obj" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\damage.sbr" : $(SOURCE) $(DEP_CPP_DAMAG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\util.cpp
DEP_CPP_UTIL_=\
	".\Dd.h"\
	".\Error.h"\
	".\fileio.h"\
	".\Globals.h"\
	".\Rmerror.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


BuildCmds= \
	$(CPP) /nologo /Gr /MD /W3 /GX /Zi /O2 /D "NDBUG" /D "BACK_BUFFER_SYSTEM" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "AUDIO_TIMER" /D "DOSWIN32" /D\
 "FINAL" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\util.sbr" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"

# ADD BASE CPP /Yu
# ADD CPP /Yu

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Armymen.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\util.sbr" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"

# ADD BASE CPP /Yu
# ADD CPP /Yu

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_AUDIO_OFF" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\util.sbr" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"

# ADD BASE CPP /Yu
# ADD CPP /Yu

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "_OBJECT_DEBUG" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\util.sbr" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"

# ADD BASE CPP /Yu
# ADD CPP /Yu

BuildCmds= \
	$(CPP) /nologo /G5 /Gr /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D\
 "BACK_BUFFER_SYSTEM" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "AUDIO_TIMER" /D "DOSWIN32" /D "AUDIO_OFF" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Armymen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

"$(INTDIR)\util.sbr" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\3DONetwork.cpp
DEP_CPP_3DONE=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\3DONetwork.obj" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\3DONetwork.sbr" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\3DONetwork.obj" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\3DONetwork.sbr" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\3DONetwork.obj" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\3DONetwork.sbr" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\3DONetwork.obj" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\3DONetwork.sbr" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\3DONetwork.obj" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\3DONetwork.sbr" : $(SOURCE) $(DEP_CPP_3DONE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VehicleMsg.cpp
DEP_CPP_VEHICL=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\VehicleMsg.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\VehicleMsg.obj" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\VehicleMsg.sbr" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\VehicleMsg.obj" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\VehicleMsg.sbr" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\VehicleMsg.obj" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\VehicleMsg.sbr" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\VehicleMsg.obj" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\VehicleMsg.sbr" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\VehicleMsg.obj" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\VehicleMsg.sbr" : $(SOURCE) $(DEP_CPP_VEHICL) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ArmyMsg.cpp
DEP_CPP_ARMYMS=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\AiAccess.h"\
	".\air.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\AssetMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\FloatMsg.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\husk.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\ObjectMsg.h"\
	".\Rmerror.h"\
	".\SargeMsg.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\trooperP.h"\
	".\types.h"\
	".\UnitMsg.h"\
	".\unitP.h"\
	".\util.h"\
	".\VehicleMsg.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\ArmyMsg.obj" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMsg.sbr" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\ArmyMsg.obj" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMsg.sbr" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\ArmyMsg.obj" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMsg.sbr" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\ArmyMsg.obj" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMsg.sbr" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\ArmyMsg.obj" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ArmyMsg.sbr" : $(SOURCE) $(DEP_CPP_ARMYMS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\explosions.cpp
DEP_CPP_EXPLO=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\AnimFile.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\FloatMsg.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\explosions.obj" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\explosions.sbr" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\explosions.obj" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\explosions.sbr" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\explosions.obj" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\explosions.sbr" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\explosions.obj" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\explosions.sbr" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\explosions.obj" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\explosions.sbr" : $(SOURCE) $(DEP_CPP_EXPLO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Float.cpp
DEP_CPP_FLOAT=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Float.obj" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Float.sbr" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Float.obj" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Float.sbr" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Float.obj" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Float.sbr" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Float.obj" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Float.sbr" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Float.obj" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Float.sbr" : $(SOURCE) $(DEP_CPP_FLOAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\UnitMsg.cpp
DEP_CPP_UNITM=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\UnitMsg.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\UnitMsg.obj" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\UnitMsg.sbr" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\UnitMsg.obj" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\UnitMsg.sbr" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\UnitMsg.obj" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\UnitMsg.sbr" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\UnitMsg.obj" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\UnitMsg.sbr" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\UnitMsg.obj" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\UnitMsg.sbr" : $(SOURCE) $(DEP_CPP_UNITM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectMsg.cpp
DEP_CPP_OBJEC=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\ObjectMsg.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\ObjectMsg.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ObjectMsg.sbr" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\ObjectMsg.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ObjectMsg.sbr" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\ObjectMsg.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ObjectMsg.sbr" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\ObjectMsg.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ObjectMsg.sbr" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\ObjectMsg.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ObjectMsg.sbr" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Airouter.cpp
DEP_CPP_AIROU=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Airouter.obj" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Airouter.sbr" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Airouter.obj" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Airouter.sbr" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Airouter.obj" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Airouter.sbr" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Airouter.obj" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Airouter.sbr" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Airouter.obj" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Airouter.sbr" : $(SOURCE) $(DEP_CPP_AIROU) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FloatMsg.cpp
DEP_CPP_FLOATM=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\FloatMsg.h"\
	".\Globals.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Snd.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\FloatMsg.obj" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\FloatMsg.sbr" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\FloatMsg.obj" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\FloatMsg.sbr" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\FloatMsg.obj" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\FloatMsg.sbr" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\FloatMsg.obj" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\FloatMsg.sbr" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\FloatMsg.obj" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\FloatMsg.sbr" : $(SOURCE) $(DEP_CPP_FLOATM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Asset.cpp
DEP_CPP_ASSET=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\AssetMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Asset.obj" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Asset.sbr" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Asset.obj" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Asset.sbr" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Asset.obj" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Asset.sbr" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Asset.obj" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Asset.sbr" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Asset.obj" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Asset.sbr" : $(SOURCE) $(DEP_CPP_ASSET) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AssetMsg.cpp
DEP_CPP_ASSETM=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\AssetMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\ObjectMsg.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\AssetMsg.obj" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AssetMsg.sbr" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\AssetMsg.obj" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AssetMsg.sbr" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\AssetMsg.obj" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AssetMsg.sbr" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\AssetMsg.obj" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AssetMsg.sbr" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\AssetMsg.obj" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\AssetMsg.sbr" : $(SOURCE) $(DEP_CPP_ASSETM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stratmap.cpp
DEP_CPP_STRAT=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\stratmap.obj" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\stratmap.sbr" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\stratmap.obj" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\stratmap.sbr" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\stratmap.obj" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\stratmap.sbr" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\stratmap.obj" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\stratmap.sbr" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\stratmap.obj" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\stratmap.sbr" : $(SOURCE) $(DEP_CPP_STRAT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Avatar.cpp
DEP_CPP_AVATA=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.dat"\
	".\avatar.h"\
	".\comm.h"\
	".\Commands.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Avatar.obj" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Avatar.sbr" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Avatar.obj" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Avatar.sbr" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Avatar.obj" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Avatar.sbr" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Avatar.obj" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Avatar.sbr" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Avatar.obj" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Avatar.sbr" : $(SOURCE) $(DEP_CPP_AVATA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TadPriv.cpp
DEP_CPP_TADPR=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.dat"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\TadPriv.obj" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TadPriv.sbr" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\TadPriv.obj" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TadPriv.sbr" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\TadPriv.obj" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TadPriv.sbr" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\TadPriv.obj" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TadPriv.sbr" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\TadPriv.obj" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TadPriv.sbr" : $(SOURCE) $(DEP_CPP_TADPR) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\trooper.cpp
DEP_CPP_TROOP=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.dat"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\UnitMsg.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\trooper.obj" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\trooper.sbr" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\trooper.obj" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\trooper.sbr" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\trooper.obj" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\trooper.sbr" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\trooper.obj" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\trooper.sbr" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\trooper.obj" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\trooper.sbr" : $(SOURCE) $(DEP_CPP_TROOP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ui.cpp
DEP_CPP_UI_CP=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\AiAccess.h"\
	".\air.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\comm.h"\
	".\Commands.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\States.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\ui.obj" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ui.sbr" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\ui.obj" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ui.sbr" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\ui.obj" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ui.sbr" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\ui.obj" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ui.sbr" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\ui.obj" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ui.sbr" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Movie.cpp
DEP_CPP_MOVIE=\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Movie.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rad.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Smack.h"\
	".\Smacker.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\States.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Movie.obj" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Movie.sbr" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Movie.obj" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Movie.sbr" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Movie.obj" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Movie.sbr" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Movie.obj" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Movie.sbr" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Movie.obj" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Movie.sbr" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fileio.cpp
DEP_CPP_FILEI=\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\fileio.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\fileio.sbr" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\fileio.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\fileio.sbr" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\fileio.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\fileio.sbr" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\fileio.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\fileio.sbr" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\fileio.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\fileio.sbr" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Weapon.cpp
DEP_CPP_WEAPO=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\ObjectMsg.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Weapon.obj" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Weapon.sbr" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Weapon.obj" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Weapon.sbr" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Weapon.obj" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Weapon.sbr" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Weapon.obj" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Weapon.sbr" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Weapon.obj" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Weapon.sbr" : $(SOURCE) $(DEP_CPP_WEAPO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TextData.cpp
DEP_CPP_TEXTD=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Snd.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\USA.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\TextData.obj" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TextData.sbr" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\TextData.obj" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TextData.sbr" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\TextData.obj" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TextData.sbr" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\TextData.obj" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TextData.sbr" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\TextData.obj" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\TextData.sbr" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sarge.cpp
DEP_CPP_SARGE=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\air.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Commands.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\pad.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\SargeMsg.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Sarge.obj" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sarge.sbr" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Sarge.obj" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sarge.sbr" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Sarge.obj" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sarge.sbr" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Sarge.obj" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sarge.sbr" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Sarge.obj" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Sarge.sbr" : $(SOURCE) $(DEP_CPP_SARGE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Item.cpp
DEP_CPP_ITEM_=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\AnimFile.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\pad.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\UnitMsg.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Item.obj" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Item.sbr" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Item.obj" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Item.sbr" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Item.obj" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Item.sbr" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Item.obj" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Item.sbr" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Item.obj" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Item.sbr" : $(SOURCE) $(DEP_CPP_ITEM_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SargeMsg.cpp
DEP_CPP_SARGEM=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\air.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\SargeMsg.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\Unit.h"\
	".\UnitMsg.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\SargeMsg.obj" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\SargeMsg.sbr" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\SargeMsg.obj" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\SargeMsg.sbr" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\SargeMsg.obj" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\SargeMsg.sbr" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\SargeMsg.obj" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\SargeMsg.sbr" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\SargeMsg.obj" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\SargeMsg.sbr" : $(SOURCE) $(DEP_CPP_SARGEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BmpText.cpp
DEP_CPP_BMPTE=\
	".\bmptext.h"\
	".\Dd.h"\
	".\Error.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Rmerror.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\types.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\BmpText.obj" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\BmpText.sbr" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\BmpText.obj" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\BmpText.sbr" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\BmpText.obj" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\BmpText.sbr" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\BmpText.obj" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\BmpText.sbr" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\BmpText.obj" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\BmpText.sbr" : $(SOURCE) $(DEP_CPP_BMPTE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wobject.cpp
DEP_CPP_WOBJE=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\comm.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\husk.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\wobject.obj" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\wobject.sbr" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\wobject.obj" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\wobject.sbr" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\wobject.obj" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\wobject.sbr" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\wobject.obj" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\wobject.sbr" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\wobject.obj" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\wobject.sbr" : $(SOURCE) $(DEP_CPP_WOBJE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\event.cpp
DEP_CPP_EVENT=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\event.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\event.sbr" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\event.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\event.sbr" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\event.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\event.sbr" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\event.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\event.sbr" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\event.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\event.sbr" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dialog.cpp
DEP_CPP_DIALO=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\Dialog.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\sounds.dat"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\streams.dat"\
	".\Streams.h"\
	".\Strm.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.dat"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dialog.sbr" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dialog.sbr" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dialog.sbr" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dialog.sbr" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Dialog.sbr" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts.cpp
DEP_CPP_SCRIP=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\cinema.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\pad.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\UnitMsg.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\scripts.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scripts.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\scripts.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scripts.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\scripts.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scripts.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\scripts.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scripts.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\scripts.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\scripts.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pad.cpp
DEP_CPP_PAD_C=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\pad.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\pad.obj" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\pad.sbr" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\pad.obj" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\pad.sbr" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\pad.obj" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\pad.sbr" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\pad.obj" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\pad.sbr" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\pad.obj" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\pad.sbr" : $(SOURCE) $(DEP_CPP_PAD_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\States.cpp
DEP_CPP_STATE=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Commands.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\Dialog.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rad.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Smack.h"\
	".\Smacker.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\States.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\States.obj" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\States.sbr" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\States.obj" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\States.sbr" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\States.obj" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\States.sbr" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\States.obj" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\States.sbr" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\States.obj" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\States.sbr" : $(SOURCE) $(DEP_CPP_STATE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScreenObj.cpp
DEP_CPP_SCREE=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\comm.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\Dialog.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.dat"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\States.h"\
	".\Stats.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\ScreenObj.obj" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenObj.sbr" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\ScreenObj.obj" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenObj.sbr" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\ScreenObj.obj" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenObj.sbr" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\ScreenObj.obj" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenObj.sbr" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\ScreenObj.obj" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenObj.sbr" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScreenBtn.cpp
DEP_CPP_SCREEN=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\comm.h"\
	".\Commands.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\Dialog.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.dat"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\States.h"\
	".\Stats.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\ScreenBtn.obj" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenBtn.sbr" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\ScreenBtn.obj" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenBtn.sbr" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\ScreenBtn.obj" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenBtn.sbr" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\ScreenBtn.obj" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenBtn.sbr" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\ScreenBtn.obj" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\ScreenBtn.sbr" : $(SOURCE) $(DEP_CPP_SCREEN) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Commands.cpp
DEP_CPP_COMMA=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Commands.h"\
	".\Dd.h"\
	".\debug.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Commands.obj" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Commands.sbr" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Commands.obj" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Commands.sbr" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Commands.obj" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Commands.sbr" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Commands.obj" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Commands.sbr" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Commands.obj" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Commands.sbr" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\air.cpp
DEP_CPP_AIR_C=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Aibtank.h"\
	".\air.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\comm.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\explosions.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\SargeMsg.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\stratmap.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\air.obj" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\air.sbr" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\air.obj" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\air.sbr" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\air.obj" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\air.sbr" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\air.obj" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\air.sbr" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\air.obj" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\air.sbr" : $(SOURCE) $(DEP_CPP_AIR_C) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Screen.cpp
DEP_CPP_SCREEN_=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\comm.h"\
	".\Commands.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\debug.h"\
	".\Dialog.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Movie.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.dat"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\States.h"\
	".\Stats.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Screen.obj" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Screen.sbr" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Screen.obj" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Screen.sbr" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Screen.obj" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Screen.sbr" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Screen.obj" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Screen.sbr" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Screen.obj" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Screen.sbr" : $(SOURCE) $(DEP_CPP_SCREEN_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Voice.cpp
DEP_CPP_VOICE=\
	".\Dd.h"\
	".\Error.h"\
	".\fileio.h"\
	".\Globals.h"\
	".\miscfile.h"\
	".\Rmerror.h"\
	".\Snd.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Strm.h"\
	".\types.h"\
	".\util.h"\
	".\Voice.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Voice.obj" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Voice.sbr" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Voice.obj" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Voice.sbr" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Voice.obj" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Voice.sbr" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Voice.obj" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Voice.sbr" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Voice.obj" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Voice.sbr" : $(SOURCE) $(DEP_CPP_VOICE) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stats.cpp
DEP_CPP_STATS=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\Armymen.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\comm.h"\
	".\CVersion.h"\
	".\Dd.h"\
	".\Dialog.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\gameproc.h"\
	".\Globals.h"\
	".\Mainfrm.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\States.h"\
	".\Stats.dat"\
	".\Stats.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Stats.obj" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Stats.sbr" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Stats.obj" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Stats.sbr" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Stats.obj" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Stats.sbr" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Stats.obj" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Stats.sbr" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Stats.obj" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Stats.sbr" : $(SOURCE) $(DEP_CPP_STATS) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\map.dat

!IF  "$(CFG)" == "ArmyMen - Win32 Release"

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"

!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\object.cpp
DEP_CPP_OBJECT=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\Globals.h"\
	".\Item.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\object.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\object.sbr" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\object.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\object.sbr" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\object.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\object.sbr" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\object.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\object.sbr" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\object.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\object.sbr" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\debug.cpp
DEP_CPP_DEBUG=\
	".\3DONetwork.h"\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Aix.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\bmptext.h"\
	".\comm.h"\
	".\Commands.h"\
	".\Dd.h"\
	".\debug.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\fileio.h"\
	".\GameFlow.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Item.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\miscfile.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\Sarge.h"\
	".\sargeP.h"\
	".\Screen.h"\
	".\ScreenBtn.h"\
	".\ScreenObj.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\Tad.h"\
	".\TadPriv.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooper.h"\
	".\trooperP.h"\
	".\types.h"\
	".\ui.h"\
	".\Unit.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\Weapon.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\debug.sbr" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\debug.sbr" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\debug.sbr" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\debug.sbr" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\debug.sbr" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cinema.cpp
DEP_CPP_CINEM=\
	".\Ai.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\cinema.h"\
	".\Commands.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\cinema.obj" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\cinema.sbr" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\cinema.obj" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\cinema.sbr" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\cinema.obj" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\cinema.sbr" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\cinema.obj" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\cinema.sbr" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\cinema.obj" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\cinema.sbr" : $(SOURCE) $(DEP_CPP_CINEM) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Smacker.cpp
DEP_CPP_SMACK=\
	".\Ai.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Audio.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\Input.h"\
	".\Mainfrm.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\Rad.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sfx.h"\
	".\Smack.h"\
	".\Smacker.h"\
	".\Snd.h"\
	".\Sounds.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Streams.h"\
	".\Strm.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehiclep.h"\
	".\Voice.h"\
	".\voices.h"\
	".\weaponp.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\Smacker.obj" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Smacker.sbr" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\Smacker.obj" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Smacker.sbr" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\Smacker.obj" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Smacker.sbr" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\Smacker.obj" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Smacker.sbr" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\Smacker.obj" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\Smacker.sbr" : $(SOURCE) $(DEP_CPP_SMACK) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\husk.cpp
DEP_CPP_HUSK_=\
	".\Ai.h"\
	".\AiAccess.h"\
	".\Airouter.h"\
	".\Anim.h"\
	".\Army.h"\
	".\ArmyMsg.h"\
	".\Avatar-p.h"\
	".\avatar.h"\
	".\damage.h"\
	".\Dd.h"\
	".\Disp.h"\
	".\DoNotTouch.h"\
	".\Error.h"\
	".\event.h"\
	".\Globals.h"\
	".\husk.h"\
	".\Item.h"\
	".\Map.h"\
	".\Msg.h"\
	".\Newdoor.h"\
	".\Object.h"\
	".\ObjectMsg.h"\
	".\Rmerror.h"\
	".\sargeP.h"\
	".\scripts.h"\
	".\Sprite.h"\
	".\Stdafx.h"\
	".\Text.h"\
	".\Tile.h"\
	".\trooperP.h"\
	".\types.h"\
	".\unitP.h"\
	".\util.h"\
	".\Vehicle.h"\
	".\Vehiclep.h"\
	".\weaponp.h"\
	".\wobject.h"\
	

!IF  "$(CFG)" == "ArmyMen - Win32 Release"


"$(INTDIR)\husk.obj" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\husk.sbr" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Debug"


"$(INTDIR)\husk.obj" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\husk.sbr" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Remote Debug"


"$(INTDIR)\husk.obj" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\husk.sbr" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 Object Debug"


"$(INTDIR)\husk.obj" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\husk.sbr" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ELSEIF  "$(CFG)" == "ArmyMen - Win32 BC"


"$(INTDIR)\husk.obj" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"

"$(INTDIR)\husk.sbr" : $(SOURCE) $(DEP_CPP_HUSK_) "$(INTDIR)"\
 "$(INTDIR)\Armymen.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
