# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MapEditor - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MapEditor - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MapEditor - Win32 Release" && "$(CFG)" !=\
 "MapEditor - Win32 Debug" && "$(CFG)" != "MapEditor - Win32 Underscore"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MapEditor.mak" CFG="MapEditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MapEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MapEditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MapEditor - Win32 Underscore" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "MapEditor - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "MapEditor - Win32 Release"

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

ALL : "$(OUTDIR)\MapEdit.exe"

CLEAN : 
	-@erase "$(INTDIR)\AnimMapObject.obj"
	-@erase "$(INTDIR)\AnimPropPage.obj"
	-@erase "$(INTDIR)\AppPropPage.obj"
	-@erase "$(INTDIR)\Attribute.obj"
	-@erase "$(INTDIR)\AttributeLayer.obj"
	-@erase "$(INTDIR)\AttributesDlg.obj"
	-@erase "$(INTDIR)\AttributeSheet.obj"
	-@erase "$(INTDIR)\AttributeSheetPreview.obj"
	-@erase "$(INTDIR)\AttributeView.obj"
	-@erase "$(INTDIR)\BoldComboBox.obj"
	-@erase "$(INTDIR)\CategoriesDlg.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\ComputeLayerDlg.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CycleButton.obj"
	-@erase "$(INTDIR)\dib.obj"
	-@erase "$(INTDIR)\Dibdoc.obj"
	-@erase "$(INTDIR)\dibpal.obj"
	-@erase "$(INTDIR)\DoorwayLayer.obj"
	-@erase "$(INTDIR)\DoorwayView.obj"
	-@erase "$(INTDIR)\DupSearchDlg.obj"
	-@erase "$(INTDIR)\EmptyView.obj"
	-@erase "$(INTDIR)\ExpandDlg.obj"
	-@erase "$(INTDIR)\FindDupDlg.obj"
	-@erase "$(INTDIR)\IFFFile.obj"
	-@erase "$(INTDIR)\LayerBar.obj"
	-@erase "$(INTDIR)\LayersDlg.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MapBmpDlg.obj"
	-@erase "$(INTDIR)\MapEditor.obj"
	-@erase "$(INTDIR)\MapEditor.pch"
	-@erase "$(INTDIR)\MapEditor.res"
	-@erase "$(INTDIR)\MapEditorDoc.obj"
	-@erase "$(INTDIR)\MapEditorView.obj"
	-@erase "$(INTDIR)\MapFrame.obj"
	-@erase "$(INTDIR)\MapLayer.obj"
	-@erase "$(INTDIR)\MapObject.obj"
	-@erase "$(INTDIR)\MapOverview.obj"
	-@erase "$(INTDIR)\MogDlg.obj"
	-@erase "$(INTDIR)\MyMultiDocTemplate.obj"
	-@erase "$(INTDIR)\MyPropertySheet.obj"
	-@erase "$(INTDIR)\NewAttributeDlg.obj"
	-@erase "$(INTDIR)\NewCategoryDlg.obj"
	-@erase "$(INTDIR)\NewGroupDlg.obj"
	-@erase "$(INTDIR)\NewLayerDlg.obj"
	-@erase "$(INTDIR)\NewMapDlg.obj"
	-@erase "$(INTDIR)\NewTileSetDlg.obj"
	-@erase "$(INTDIR)\NumberDlg.obj"
	-@erase "$(INTDIR)\ObjectLayer.obj"
	-@erase "$(INTDIR)\ObjectListBox.obj"
	-@erase "$(INTDIR)\ObjectSet.obj"
	-@erase "$(INTDIR)\ObjectSetView.obj"
	-@erase "$(INTDIR)\PropPageAmen.obj"
	-@erase "$(INTDIR)\RemDupDlg.obj"
	-@erase "$(INTDIR)\RotateDlg.obj"
	-@erase "$(INTDIR)\RulerWnd.obj"
	-@erase "$(INTDIR)\ScenarioLayer.obj"
	-@erase "$(INTDIR)\ScenarioSet.obj"
	-@erase "$(INTDIR)\ScenarioView.obj"
	-@erase "$(INTDIR)\ScenPropPage.obj"
	-@erase "$(INTDIR)\ScriptsDlg.obj"
	-@erase "$(INTDIR)\SelectDlg.obj"
	-@erase "$(INTDIR)\ShowUsageDlg.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TextPage.obj"
	-@erase "$(INTDIR)\TileAttribute.obj"
	-@erase "$(INTDIR)\TileCategory.obj"
	-@erase "$(INTDIR)\TileGroup.obj"
	-@erase "$(INTDIR)\TileLayer.obj"
	-@erase "$(INTDIR)\TileListBox.obj"
	-@erase "$(INTDIR)\TileSet.obj"
	-@erase "$(INTDIR)\TileSetOp.obj"
	-@erase "$(INTDIR)\TileSetView.obj"
	-@erase "$(OUTDIR)\MapEdit.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MapEditor.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MapEditor.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MapEditor.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/MapEdit.exe"
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/MapEdit.pdb" /machine:I386 /out:"$(OUTDIR)/MapEdit.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AnimMapObject.obj" \
	"$(INTDIR)\AnimPropPage.obj" \
	"$(INTDIR)\AppPropPage.obj" \
	"$(INTDIR)\Attribute.obj" \
	"$(INTDIR)\AttributeLayer.obj" \
	"$(INTDIR)\AttributesDlg.obj" \
	"$(INTDIR)\AttributeSheet.obj" \
	"$(INTDIR)\AttributeSheetPreview.obj" \
	"$(INTDIR)\AttributeView.obj" \
	"$(INTDIR)\BoldComboBox.obj" \
	"$(INTDIR)\CategoriesDlg.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\ComputeLayerDlg.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\CycleButton.obj" \
	"$(INTDIR)\dib.obj" \
	"$(INTDIR)\Dibdoc.obj" \
	"$(INTDIR)\dibpal.obj" \
	"$(INTDIR)\DoorwayLayer.obj" \
	"$(INTDIR)\DoorwayView.obj" \
	"$(INTDIR)\DupSearchDlg.obj" \
	"$(INTDIR)\EmptyView.obj" \
	"$(INTDIR)\ExpandDlg.obj" \
	"$(INTDIR)\FindDupDlg.obj" \
	"$(INTDIR)\IFFFile.obj" \
	"$(INTDIR)\LayerBar.obj" \
	"$(INTDIR)\LayersDlg.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MapBmpDlg.obj" \
	"$(INTDIR)\MapEditor.obj" \
	"$(INTDIR)\MapEditor.res" \
	"$(INTDIR)\MapEditorDoc.obj" \
	"$(INTDIR)\MapEditorView.obj" \
	"$(INTDIR)\MapFrame.obj" \
	"$(INTDIR)\MapLayer.obj" \
	"$(INTDIR)\MapObject.obj" \
	"$(INTDIR)\MapOverview.obj" \
	"$(INTDIR)\MogDlg.obj" \
	"$(INTDIR)\MyMultiDocTemplate.obj" \
	"$(INTDIR)\MyPropertySheet.obj" \
	"$(INTDIR)\NewAttributeDlg.obj" \
	"$(INTDIR)\NewCategoryDlg.obj" \
	"$(INTDIR)\NewGroupDlg.obj" \
	"$(INTDIR)\NewLayerDlg.obj" \
	"$(INTDIR)\NewMapDlg.obj" \
	"$(INTDIR)\NewTileSetDlg.obj" \
	"$(INTDIR)\NumberDlg.obj" \
	"$(INTDIR)\ObjectLayer.obj" \
	"$(INTDIR)\ObjectListBox.obj" \
	"$(INTDIR)\ObjectSet.obj" \
	"$(INTDIR)\ObjectSetView.obj" \
	"$(INTDIR)\PropPageAmen.obj" \
	"$(INTDIR)\RemDupDlg.obj" \
	"$(INTDIR)\RotateDlg.obj" \
	"$(INTDIR)\RulerWnd.obj" \
	"$(INTDIR)\ScenarioLayer.obj" \
	"$(INTDIR)\ScenarioSet.obj" \
	"$(INTDIR)\ScenarioView.obj" \
	"$(INTDIR)\ScenPropPage.obj" \
	"$(INTDIR)\ScriptsDlg.obj" \
	"$(INTDIR)\SelectDlg.obj" \
	"$(INTDIR)\ShowUsageDlg.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TextPage.obj" \
	"$(INTDIR)\TileAttribute.obj" \
	"$(INTDIR)\TileCategory.obj" \
	"$(INTDIR)\TileGroup.obj" \
	"$(INTDIR)\TileLayer.obj" \
	"$(INTDIR)\TileListBox.obj" \
	"$(INTDIR)\TileSet.obj" \
	"$(INTDIR)\TileSetOp.obj" \
	"$(INTDIR)\TileSetView.obj"

"$(OUTDIR)\MapEdit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

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

ALL : "$(OUTDIR)\MapEdit.exe" "$(OUTDIR)\MapEditor.bsc"

CLEAN : 
	-@erase "$(INTDIR)\AnimMapObject.obj"
	-@erase "$(INTDIR)\AnimMapObject.sbr"
	-@erase "$(INTDIR)\AnimPropPage.obj"
	-@erase "$(INTDIR)\AnimPropPage.sbr"
	-@erase "$(INTDIR)\AppPropPage.obj"
	-@erase "$(INTDIR)\AppPropPage.sbr"
	-@erase "$(INTDIR)\Attribute.obj"
	-@erase "$(INTDIR)\Attribute.sbr"
	-@erase "$(INTDIR)\AttributeLayer.obj"
	-@erase "$(INTDIR)\AttributeLayer.sbr"
	-@erase "$(INTDIR)\AttributesDlg.obj"
	-@erase "$(INTDIR)\AttributesDlg.sbr"
	-@erase "$(INTDIR)\AttributeSheet.obj"
	-@erase "$(INTDIR)\AttributeSheet.sbr"
	-@erase "$(INTDIR)\AttributeSheetPreview.obj"
	-@erase "$(INTDIR)\AttributeSheetPreview.sbr"
	-@erase "$(INTDIR)\AttributeView.obj"
	-@erase "$(INTDIR)\AttributeView.sbr"
	-@erase "$(INTDIR)\BoldComboBox.obj"
	-@erase "$(INTDIR)\BoldComboBox.sbr"
	-@erase "$(INTDIR)\CategoriesDlg.obj"
	-@erase "$(INTDIR)\CategoriesDlg.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\ColorButton.sbr"
	-@erase "$(INTDIR)\ComputeLayerDlg.obj"
	-@erase "$(INTDIR)\ComputeLayerDlg.sbr"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.sbr"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CSpriteSequence.sbr"
	-@erase "$(INTDIR)\CycleButton.obj"
	-@erase "$(INTDIR)\CycleButton.sbr"
	-@erase "$(INTDIR)\dib.obj"
	-@erase "$(INTDIR)\dib.sbr"
	-@erase "$(INTDIR)\Dibdoc.obj"
	-@erase "$(INTDIR)\Dibdoc.sbr"
	-@erase "$(INTDIR)\dibpal.obj"
	-@erase "$(INTDIR)\dibpal.sbr"
	-@erase "$(INTDIR)\DoorwayLayer.obj"
	-@erase "$(INTDIR)\DoorwayLayer.sbr"
	-@erase "$(INTDIR)\DoorwayView.obj"
	-@erase "$(INTDIR)\DoorwayView.sbr"
	-@erase "$(INTDIR)\DupSearchDlg.obj"
	-@erase "$(INTDIR)\DupSearchDlg.sbr"
	-@erase "$(INTDIR)\EmptyView.obj"
	-@erase "$(INTDIR)\EmptyView.sbr"
	-@erase "$(INTDIR)\ExpandDlg.obj"
	-@erase "$(INTDIR)\ExpandDlg.sbr"
	-@erase "$(INTDIR)\FindDupDlg.obj"
	-@erase "$(INTDIR)\FindDupDlg.sbr"
	-@erase "$(INTDIR)\IFFFile.obj"
	-@erase "$(INTDIR)\IFFFile.sbr"
	-@erase "$(INTDIR)\LayerBar.obj"
	-@erase "$(INTDIR)\LayerBar.sbr"
	-@erase "$(INTDIR)\LayersDlg.obj"
	-@erase "$(INTDIR)\LayersDlg.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MapBmpDlg.obj"
	-@erase "$(INTDIR)\MapBmpDlg.sbr"
	-@erase "$(INTDIR)\MapEditor.obj"
	-@erase "$(INTDIR)\MapEditor.pch"
	-@erase "$(INTDIR)\MapEditor.res"
	-@erase "$(INTDIR)\MapEditor.sbr"
	-@erase "$(INTDIR)\MapEditorDoc.obj"
	-@erase "$(INTDIR)\MapEditorDoc.sbr"
	-@erase "$(INTDIR)\MapEditorView.obj"
	-@erase "$(INTDIR)\MapEditorView.sbr"
	-@erase "$(INTDIR)\MapFrame.obj"
	-@erase "$(INTDIR)\MapFrame.sbr"
	-@erase "$(INTDIR)\MapLayer.obj"
	-@erase "$(INTDIR)\MapLayer.sbr"
	-@erase "$(INTDIR)\MapObject.obj"
	-@erase "$(INTDIR)\MapObject.sbr"
	-@erase "$(INTDIR)\MapOverview.obj"
	-@erase "$(INTDIR)\MapOverview.sbr"
	-@erase "$(INTDIR)\MogDlg.obj"
	-@erase "$(INTDIR)\MogDlg.sbr"
	-@erase "$(INTDIR)\MyMultiDocTemplate.obj"
	-@erase "$(INTDIR)\MyMultiDocTemplate.sbr"
	-@erase "$(INTDIR)\MyPropertySheet.obj"
	-@erase "$(INTDIR)\MyPropertySheet.sbr"
	-@erase "$(INTDIR)\NewAttributeDlg.obj"
	-@erase "$(INTDIR)\NewAttributeDlg.sbr"
	-@erase "$(INTDIR)\NewCategoryDlg.obj"
	-@erase "$(INTDIR)\NewCategoryDlg.sbr"
	-@erase "$(INTDIR)\NewGroupDlg.obj"
	-@erase "$(INTDIR)\NewGroupDlg.sbr"
	-@erase "$(INTDIR)\NewLayerDlg.obj"
	-@erase "$(INTDIR)\NewLayerDlg.sbr"
	-@erase "$(INTDIR)\NewMapDlg.obj"
	-@erase "$(INTDIR)\NewMapDlg.sbr"
	-@erase "$(INTDIR)\NewTileSetDlg.obj"
	-@erase "$(INTDIR)\NewTileSetDlg.sbr"
	-@erase "$(INTDIR)\NumberDlg.obj"
	-@erase "$(INTDIR)\NumberDlg.sbr"
	-@erase "$(INTDIR)\ObjectLayer.obj"
	-@erase "$(INTDIR)\ObjectLayer.sbr"
	-@erase "$(INTDIR)\ObjectListBox.obj"
	-@erase "$(INTDIR)\ObjectListBox.sbr"
	-@erase "$(INTDIR)\ObjectSet.obj"
	-@erase "$(INTDIR)\ObjectSet.sbr"
	-@erase "$(INTDIR)\ObjectSetView.obj"
	-@erase "$(INTDIR)\ObjectSetView.sbr"
	-@erase "$(INTDIR)\PropPageAmen.obj"
	-@erase "$(INTDIR)\PropPageAmen.sbr"
	-@erase "$(INTDIR)\RemDupDlg.obj"
	-@erase "$(INTDIR)\RemDupDlg.sbr"
	-@erase "$(INTDIR)\RotateDlg.obj"
	-@erase "$(INTDIR)\RotateDlg.sbr"
	-@erase "$(INTDIR)\RulerWnd.obj"
	-@erase "$(INTDIR)\RulerWnd.sbr"
	-@erase "$(INTDIR)\ScenarioLayer.obj"
	-@erase "$(INTDIR)\ScenarioLayer.sbr"
	-@erase "$(INTDIR)\ScenarioSet.obj"
	-@erase "$(INTDIR)\ScenarioSet.sbr"
	-@erase "$(INTDIR)\ScenarioView.obj"
	-@erase "$(INTDIR)\ScenarioView.sbr"
	-@erase "$(INTDIR)\ScenPropPage.obj"
	-@erase "$(INTDIR)\ScenPropPage.sbr"
	-@erase "$(INTDIR)\ScriptsDlg.obj"
	-@erase "$(INTDIR)\ScriptsDlg.sbr"
	-@erase "$(INTDIR)\SelectDlg.obj"
	-@erase "$(INTDIR)\SelectDlg.sbr"
	-@erase "$(INTDIR)\ShowUsageDlg.obj"
	-@erase "$(INTDIR)\ShowUsageDlg.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TextPage.obj"
	-@erase "$(INTDIR)\TextPage.sbr"
	-@erase "$(INTDIR)\TileAttribute.obj"
	-@erase "$(INTDIR)\TileAttribute.sbr"
	-@erase "$(INTDIR)\TileCategory.obj"
	-@erase "$(INTDIR)\TileCategory.sbr"
	-@erase "$(INTDIR)\TileGroup.obj"
	-@erase "$(INTDIR)\TileGroup.sbr"
	-@erase "$(INTDIR)\TileLayer.obj"
	-@erase "$(INTDIR)\TileLayer.sbr"
	-@erase "$(INTDIR)\TileListBox.obj"
	-@erase "$(INTDIR)\TileListBox.sbr"
	-@erase "$(INTDIR)\TileSet.obj"
	-@erase "$(INTDIR)\TileSet.sbr"
	-@erase "$(INTDIR)\TileSetOp.obj"
	-@erase "$(INTDIR)\TileSetOp.sbr"
	-@erase "$(INTDIR)\TileSetView.obj"
	-@erase "$(INTDIR)\TileSetView.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\MapEdit.exe"
	-@erase "$(OUTDIR)\MapEditor.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/MapEditor.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MapEditor.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MapEditor.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnimMapObject.sbr" \
	"$(INTDIR)\AnimPropPage.sbr" \
	"$(INTDIR)\AppPropPage.sbr" \
	"$(INTDIR)\Attribute.sbr" \
	"$(INTDIR)\AttributeLayer.sbr" \
	"$(INTDIR)\AttributesDlg.sbr" \
	"$(INTDIR)\AttributeSheet.sbr" \
	"$(INTDIR)\AttributeSheetPreview.sbr" \
	"$(INTDIR)\AttributeView.sbr" \
	"$(INTDIR)\BoldComboBox.sbr" \
	"$(INTDIR)\CategoriesDlg.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\ColorButton.sbr" \
	"$(INTDIR)\ComputeLayerDlg.sbr" \
	"$(INTDIR)\CSpriteCatalog.sbr" \
	"$(INTDIR)\CSpriteSequence.sbr" \
	"$(INTDIR)\CycleButton.sbr" \
	"$(INTDIR)\dib.sbr" \
	"$(INTDIR)\Dibdoc.sbr" \
	"$(INTDIR)\dibpal.sbr" \
	"$(INTDIR)\DoorwayLayer.sbr" \
	"$(INTDIR)\DoorwayView.sbr" \
	"$(INTDIR)\DupSearchDlg.sbr" \
	"$(INTDIR)\EmptyView.sbr" \
	"$(INTDIR)\ExpandDlg.sbr" \
	"$(INTDIR)\FindDupDlg.sbr" \
	"$(INTDIR)\IFFFile.sbr" \
	"$(INTDIR)\LayerBar.sbr" \
	"$(INTDIR)\LayersDlg.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MapBmpDlg.sbr" \
	"$(INTDIR)\MapEditor.sbr" \
	"$(INTDIR)\MapEditorDoc.sbr" \
	"$(INTDIR)\MapEditorView.sbr" \
	"$(INTDIR)\MapFrame.sbr" \
	"$(INTDIR)\MapLayer.sbr" \
	"$(INTDIR)\MapObject.sbr" \
	"$(INTDIR)\MapOverview.sbr" \
	"$(INTDIR)\MogDlg.sbr" \
	"$(INTDIR)\MyMultiDocTemplate.sbr" \
	"$(INTDIR)\MyPropertySheet.sbr" \
	"$(INTDIR)\NewAttributeDlg.sbr" \
	"$(INTDIR)\NewCategoryDlg.sbr" \
	"$(INTDIR)\NewGroupDlg.sbr" \
	"$(INTDIR)\NewLayerDlg.sbr" \
	"$(INTDIR)\NewMapDlg.sbr" \
	"$(INTDIR)\NewTileSetDlg.sbr" \
	"$(INTDIR)\NumberDlg.sbr" \
	"$(INTDIR)\ObjectLayer.sbr" \
	"$(INTDIR)\ObjectListBox.sbr" \
	"$(INTDIR)\ObjectSet.sbr" \
	"$(INTDIR)\ObjectSetView.sbr" \
	"$(INTDIR)\PropPageAmen.sbr" \
	"$(INTDIR)\RemDupDlg.sbr" \
	"$(INTDIR)\RotateDlg.sbr" \
	"$(INTDIR)\RulerWnd.sbr" \
	"$(INTDIR)\ScenarioLayer.sbr" \
	"$(INTDIR)\ScenarioSet.sbr" \
	"$(INTDIR)\ScenarioView.sbr" \
	"$(INTDIR)\ScenPropPage.sbr" \
	"$(INTDIR)\ScriptsDlg.sbr" \
	"$(INTDIR)\SelectDlg.sbr" \
	"$(INTDIR)\ShowUsageDlg.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TextPage.sbr" \
	"$(INTDIR)\TileAttribute.sbr" \
	"$(INTDIR)\TileCategory.sbr" \
	"$(INTDIR)\TileGroup.sbr" \
	"$(INTDIR)\TileLayer.sbr" \
	"$(INTDIR)\TileListBox.sbr" \
	"$(INTDIR)\TileSet.sbr" \
	"$(INTDIR)\TileSetOp.sbr" \
	"$(INTDIR)\TileSetView.sbr"

"$(OUTDIR)\MapEditor.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /profile /debug /machine:I386 /out:"Debug/MapEdit.exe"
LINK32_FLAGS=/nologo /subsystem:windows /profile /debug /machine:I386\
 /out:"$(OUTDIR)/MapEdit.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AnimMapObject.obj" \
	"$(INTDIR)\AnimPropPage.obj" \
	"$(INTDIR)\AppPropPage.obj" \
	"$(INTDIR)\Attribute.obj" \
	"$(INTDIR)\AttributeLayer.obj" \
	"$(INTDIR)\AttributesDlg.obj" \
	"$(INTDIR)\AttributeSheet.obj" \
	"$(INTDIR)\AttributeSheetPreview.obj" \
	"$(INTDIR)\AttributeView.obj" \
	"$(INTDIR)\BoldComboBox.obj" \
	"$(INTDIR)\CategoriesDlg.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\ComputeLayerDlg.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\CycleButton.obj" \
	"$(INTDIR)\dib.obj" \
	"$(INTDIR)\Dibdoc.obj" \
	"$(INTDIR)\dibpal.obj" \
	"$(INTDIR)\DoorwayLayer.obj" \
	"$(INTDIR)\DoorwayView.obj" \
	"$(INTDIR)\DupSearchDlg.obj" \
	"$(INTDIR)\EmptyView.obj" \
	"$(INTDIR)\ExpandDlg.obj" \
	"$(INTDIR)\FindDupDlg.obj" \
	"$(INTDIR)\IFFFile.obj" \
	"$(INTDIR)\LayerBar.obj" \
	"$(INTDIR)\LayersDlg.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MapBmpDlg.obj" \
	"$(INTDIR)\MapEditor.obj" \
	"$(INTDIR)\MapEditor.res" \
	"$(INTDIR)\MapEditorDoc.obj" \
	"$(INTDIR)\MapEditorView.obj" \
	"$(INTDIR)\MapFrame.obj" \
	"$(INTDIR)\MapLayer.obj" \
	"$(INTDIR)\MapObject.obj" \
	"$(INTDIR)\MapOverview.obj" \
	"$(INTDIR)\MogDlg.obj" \
	"$(INTDIR)\MyMultiDocTemplate.obj" \
	"$(INTDIR)\MyPropertySheet.obj" \
	"$(INTDIR)\NewAttributeDlg.obj" \
	"$(INTDIR)\NewCategoryDlg.obj" \
	"$(INTDIR)\NewGroupDlg.obj" \
	"$(INTDIR)\NewLayerDlg.obj" \
	"$(INTDIR)\NewMapDlg.obj" \
	"$(INTDIR)\NewTileSetDlg.obj" \
	"$(INTDIR)\NumberDlg.obj" \
	"$(INTDIR)\ObjectLayer.obj" \
	"$(INTDIR)\ObjectListBox.obj" \
	"$(INTDIR)\ObjectSet.obj" \
	"$(INTDIR)\ObjectSetView.obj" \
	"$(INTDIR)\PropPageAmen.obj" \
	"$(INTDIR)\RemDupDlg.obj" \
	"$(INTDIR)\RotateDlg.obj" \
	"$(INTDIR)\RulerWnd.obj" \
	"$(INTDIR)\ScenarioLayer.obj" \
	"$(INTDIR)\ScenarioSet.obj" \
	"$(INTDIR)\ScenarioView.obj" \
	"$(INTDIR)\ScenPropPage.obj" \
	"$(INTDIR)\ScriptsDlg.obj" \
	"$(INTDIR)\SelectDlg.obj" \
	"$(INTDIR)\ShowUsageDlg.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TextPage.obj" \
	"$(INTDIR)\TileAttribute.obj" \
	"$(INTDIR)\TileCategory.obj" \
	"$(INTDIR)\TileGroup.obj" \
	"$(INTDIR)\TileLayer.obj" \
	"$(INTDIR)\TileListBox.obj" \
	"$(INTDIR)\TileSet.obj" \
	"$(INTDIR)\TileSetOp.obj" \
	"$(INTDIR)\TileSetView.obj"

"$(OUTDIR)\MapEdit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MapEdito"
# PROP BASE Intermediate_Dir "MapEdito"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Underscore"
# PROP Intermediate_Dir "Underscore"
# PROP Target_Dir ""
OUTDIR=.\Underscore
INTDIR=.\Underscore

ALL : "$(OUTDIR)\Underscore.exe"

CLEAN : 
	-@erase "$(INTDIR)\AnimMapObject.obj"
	-@erase "$(INTDIR)\AnimPropPage.obj"
	-@erase "$(INTDIR)\AppPropPage.obj"
	-@erase "$(INTDIR)\Attribute.obj"
	-@erase "$(INTDIR)\AttributeLayer.obj"
	-@erase "$(INTDIR)\AttributesDlg.obj"
	-@erase "$(INTDIR)\AttributeSheet.obj"
	-@erase "$(INTDIR)\AttributeSheetPreview.obj"
	-@erase "$(INTDIR)\AttributeView.obj"
	-@erase "$(INTDIR)\BoldComboBox.obj"
	-@erase "$(INTDIR)\CategoriesDlg.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\ComputeLayerDlg.obj"
	-@erase "$(INTDIR)\CSpriteCatalog.obj"
	-@erase "$(INTDIR)\CSpriteSequence.obj"
	-@erase "$(INTDIR)\CycleButton.obj"
	-@erase "$(INTDIR)\dib.obj"
	-@erase "$(INTDIR)\Dibdoc.obj"
	-@erase "$(INTDIR)\dibpal.obj"
	-@erase "$(INTDIR)\DoorwayLayer.obj"
	-@erase "$(INTDIR)\DoorwayView.obj"
	-@erase "$(INTDIR)\DupSearchDlg.obj"
	-@erase "$(INTDIR)\EmptyView.obj"
	-@erase "$(INTDIR)\ExpandDlg.obj"
	-@erase "$(INTDIR)\FindDupDlg.obj"
	-@erase "$(INTDIR)\IFFFile.obj"
	-@erase "$(INTDIR)\LayerBar.obj"
	-@erase "$(INTDIR)\LayersDlg.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MapBmpDlg.obj"
	-@erase "$(INTDIR)\MapEditor.obj"
	-@erase "$(INTDIR)\MapEditor.pch"
	-@erase "$(INTDIR)\MapEditor.res"
	-@erase "$(INTDIR)\MapEditorDoc.obj"
	-@erase "$(INTDIR)\MapEditorView.obj"
	-@erase "$(INTDIR)\MapFrame.obj"
	-@erase "$(INTDIR)\MapLayer.obj"
	-@erase "$(INTDIR)\MapObject.obj"
	-@erase "$(INTDIR)\MapOverview.obj"
	-@erase "$(INTDIR)\MogDlg.obj"
	-@erase "$(INTDIR)\MyMultiDocTemplate.obj"
	-@erase "$(INTDIR)\MyPropertySheet.obj"
	-@erase "$(INTDIR)\NewAttributeDlg.obj"
	-@erase "$(INTDIR)\NewCategoryDlg.obj"
	-@erase "$(INTDIR)\NewGroupDlg.obj"
	-@erase "$(INTDIR)\NewLayerDlg.obj"
	-@erase "$(INTDIR)\NewMapDlg.obj"
	-@erase "$(INTDIR)\NewTileSetDlg.obj"
	-@erase "$(INTDIR)\NumberDlg.obj"
	-@erase "$(INTDIR)\ObjectLayer.obj"
	-@erase "$(INTDIR)\ObjectListBox.obj"
	-@erase "$(INTDIR)\ObjectSet.obj"
	-@erase "$(INTDIR)\ObjectSetView.obj"
	-@erase "$(INTDIR)\PropPageAmen.obj"
	-@erase "$(INTDIR)\RemDupDlg.obj"
	-@erase "$(INTDIR)\RotateDlg.obj"
	-@erase "$(INTDIR)\RulerWnd.obj"
	-@erase "$(INTDIR)\ScenarioLayer.obj"
	-@erase "$(INTDIR)\ScenarioSet.obj"
	-@erase "$(INTDIR)\ScenarioView.obj"
	-@erase "$(INTDIR)\ScenPropPage.obj"
	-@erase "$(INTDIR)\ScriptsDlg.obj"
	-@erase "$(INTDIR)\SelectDlg.obj"
	-@erase "$(INTDIR)\ShowUsageDlg.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TextPage.obj"
	-@erase "$(INTDIR)\TileAttribute.obj"
	-@erase "$(INTDIR)\TileCategory.obj"
	-@erase "$(INTDIR)\TileGroup.obj"
	-@erase "$(INTDIR)\TileLayer.obj"
	-@erase "$(INTDIR)\TileListBox.obj"
	-@erase "$(INTDIR)\TileSet.obj"
	-@erase "$(INTDIR)\TileSetOp.obj"
	-@erase "$(INTDIR)\TileSetView.obj"
	-@erase "$(OUTDIR)\Underscore.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "UNDERSCORE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "UNDERSCORE" /Fp"$(INTDIR)/MapEditor.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Underscore/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MapEditor.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MapEditor.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/MapEdit.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Underscore/Underscore.exe"
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Underscore.pdb" /machine:I386 /out:"$(OUTDIR)/Underscore.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AnimMapObject.obj" \
	"$(INTDIR)\AnimPropPage.obj" \
	"$(INTDIR)\AppPropPage.obj" \
	"$(INTDIR)\Attribute.obj" \
	"$(INTDIR)\AttributeLayer.obj" \
	"$(INTDIR)\AttributesDlg.obj" \
	"$(INTDIR)\AttributeSheet.obj" \
	"$(INTDIR)\AttributeSheetPreview.obj" \
	"$(INTDIR)\AttributeView.obj" \
	"$(INTDIR)\BoldComboBox.obj" \
	"$(INTDIR)\CategoriesDlg.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\ComputeLayerDlg.obj" \
	"$(INTDIR)\CSpriteCatalog.obj" \
	"$(INTDIR)\CSpriteSequence.obj" \
	"$(INTDIR)\CycleButton.obj" \
	"$(INTDIR)\dib.obj" \
	"$(INTDIR)\Dibdoc.obj" \
	"$(INTDIR)\dibpal.obj" \
	"$(INTDIR)\DoorwayLayer.obj" \
	"$(INTDIR)\DoorwayView.obj" \
	"$(INTDIR)\DupSearchDlg.obj" \
	"$(INTDIR)\EmptyView.obj" \
	"$(INTDIR)\ExpandDlg.obj" \
	"$(INTDIR)\FindDupDlg.obj" \
	"$(INTDIR)\IFFFile.obj" \
	"$(INTDIR)\LayerBar.obj" \
	"$(INTDIR)\LayersDlg.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MapBmpDlg.obj" \
	"$(INTDIR)\MapEditor.obj" \
	"$(INTDIR)\MapEditor.res" \
	"$(INTDIR)\MapEditorDoc.obj" \
	"$(INTDIR)\MapEditorView.obj" \
	"$(INTDIR)\MapFrame.obj" \
	"$(INTDIR)\MapLayer.obj" \
	"$(INTDIR)\MapObject.obj" \
	"$(INTDIR)\MapOverview.obj" \
	"$(INTDIR)\MogDlg.obj" \
	"$(INTDIR)\MyMultiDocTemplate.obj" \
	"$(INTDIR)\MyPropertySheet.obj" \
	"$(INTDIR)\NewAttributeDlg.obj" \
	"$(INTDIR)\NewCategoryDlg.obj" \
	"$(INTDIR)\NewGroupDlg.obj" \
	"$(INTDIR)\NewLayerDlg.obj" \
	"$(INTDIR)\NewMapDlg.obj" \
	"$(INTDIR)\NewTileSetDlg.obj" \
	"$(INTDIR)\NumberDlg.obj" \
	"$(INTDIR)\ObjectLayer.obj" \
	"$(INTDIR)\ObjectListBox.obj" \
	"$(INTDIR)\ObjectSet.obj" \
	"$(INTDIR)\ObjectSetView.obj" \
	"$(INTDIR)\PropPageAmen.obj" \
	"$(INTDIR)\RemDupDlg.obj" \
	"$(INTDIR)\RotateDlg.obj" \
	"$(INTDIR)\RulerWnd.obj" \
	"$(INTDIR)\ScenarioLayer.obj" \
	"$(INTDIR)\ScenarioSet.obj" \
	"$(INTDIR)\ScenarioView.obj" \
	"$(INTDIR)\ScenPropPage.obj" \
	"$(INTDIR)\ScriptsDlg.obj" \
	"$(INTDIR)\SelectDlg.obj" \
	"$(INTDIR)\ShowUsageDlg.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TextPage.obj" \
	"$(INTDIR)\TileAttribute.obj" \
	"$(INTDIR)\TileCategory.obj" \
	"$(INTDIR)\TileGroup.obj" \
	"$(INTDIR)\TileLayer.obj" \
	"$(INTDIR)\TileListBox.obj" \
	"$(INTDIR)\TileSet.obj" \
	"$(INTDIR)\TileSetOp.obj" \
	"$(INTDIR)\TileSetView.obj"

"$(OUTDIR)\Underscore.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MapEditor - Win32 Release"
# Name "MapEditor - Win32 Debug"
# Name "MapEditor - Win32 Underscore"

!IF  "$(CFG)" == "MapEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MapEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapEditor.cpp

!IF  "$(CFG)" == "MapEditor - Win32 Release"

DEP_CPP_MAPED=\
	".\Attribute.h"\
	".\BoldComboBox.h"\
	".\ChildFrm.h"\
	".\ColorButton.h"\
	".\CycleButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\LayerBar.h"\
	".\MainFrm.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\ScenarioSet.h"\
	".\ScenarioView.h"\
	".\Splash.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	".\TileSetView.h"\
	

"$(INTDIR)\MapEditor.obj" : $(SOURCE) $(DEP_CPP_MAPED) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

DEP_CPP_MAPED=\
	".\Attribute.h"\
	".\BoldComboBox.h"\
	".\ChildFrm.h"\
	".\ColorButton.h"\
	".\CycleButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\LayerBar.h"\
	".\MainFrm.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\ScenarioSet.h"\
	".\ScenarioView.h"\
	".\Splash.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	".\TileSetView.h"\
	

"$(INTDIR)\MapEditor.obj" : $(SOURCE) $(DEP_CPP_MAPED) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MapEditor.sbr" : $(SOURCE) $(DEP_CPP_MAPED) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

DEP_CPP_MAPED=\
	".\Attribute.h"\
	".\BoldComboBox.h"\
	".\ChildFrm.h"\
	".\ColorButton.h"\
	".\CycleButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\LayerBar.h"\
	".\MainFrm.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\ScenarioView.h"\
	".\Splash.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	".\TileSetView.h"\
	

"$(INTDIR)\MapEditor.obj" : $(SOURCE) $(DEP_CPP_MAPED) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MapEditor.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MapEditor.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/MapEditor.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MapEditor.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "UNDERSCORE" /Fp"$(INTDIR)/MapEditor.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MapEditor.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\AppPropPage.h"\
	".\Attribute.h"\
	".\BoldComboBox.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\LayerBar.h"\
	".\MainFrm.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\MyPropertySheet.h"\
	".\ObjectSet.h"\
	".\PropPageAmen.h"\
	".\ScenarioSet.h"\
	".\ScenPropPage.h"\
	".\Splash.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\BoldComboBox.h"\
	".\ChildFrm.h"\
	".\LayerBar.h"\
	".\MainFrm.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapEditorDoc.cpp
DEP_CPP_MAPEDI=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\BoldComboBox.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\IFFFile.h"\
	".\LayerBar.h"\
	".\LayersDlg.h"\
	".\MainFrm.h"\
	".\MapBmpDlg.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\MapUpdate.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewAttributeDlg.h"\
	".\NewMapDlg.h"\
	".\ObjectLayer.h"\
	".\ObjectSet.h"\
	".\ScenarioLayer.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MapEditorDoc.obj" : $(SOURCE) $(DEP_CPP_MAPEDI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MapEditorDoc.obj" : $(SOURCE) $(DEP_CPP_MAPEDI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MapEditorDoc.sbr" : $(SOURCE) $(DEP_CPP_MAPEDI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MapEditorDoc.obj" : $(SOURCE) $(DEP_CPP_MAPEDI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapEditorView.cpp
DEP_CPP_MAPEDIT=\
	".\Attribute.h"\
	".\BoldComboBox.h"\
	".\ColorButton.h"\
	".\CycleButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\ExpandDlg.h"\
	".\LayerBar.h"\
	".\MainFrm.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\MapOverview.h"\
	".\MapUpdate.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewMapDlg.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\ScenarioSet.h"\
	".\ScenarioView.h"\
	".\ScriptsDlg.h"\
	".\SelectDlg.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	".\TileSetView.h"\
	
NODEP_CPP_MAPEDIT=\
	".\rotatedlg.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MapEditorView.obj" : $(SOURCE) $(DEP_CPP_MAPEDIT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MapEditorView.obj" : $(SOURCE) $(DEP_CPP_MAPEDIT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MapEditorView.sbr" : $(SOURCE) $(DEP_CPP_MAPEDIT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MapEditorView.obj" : $(SOURCE) $(DEP_CPP_MAPEDIT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapEditor.rc
DEP_RSC_MAPEDITO=\
	".\res\amap.ico"\
	".\res\atiles.ico"\
	".\res\check.bmp"\
	".\res\cross.bmp"\
	".\res\cycleb.bmp"\
	".\res\cyclef.bmp"\
	".\res\cyclen.bmp"\
	".\res\delete.bmp"\
	".\res\doorway.bmp"\
	".\res\down.bmp"\
	".\res\end.bmp"\
	".\res\hand.cur"\
	".\res\MapEditor.ico"\
	".\res\MapEditor.rc2"\
	".\res\MapEditorDoc.ico"\
	".\res\new.bmp"\
	".\res\route.bmp"\
	".\res\splash.bmp"\
	".\res\start.bmp"\
	".\res\stateico.bmp"\
	".\res\tb.bmp"\
	".\res\TileSet.ico"\
	".\res\up.bmp"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MapEditor.res" : $(SOURCE) $(DEP_RSC_MAPEDITO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MapEditor.res" : $(SOURCE) $(DEP_RSC_MAPEDITO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MapEditor.res" : $(SOURCE) $(DEP_RSC_MAPEDITO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ToDo.txt

!IF  "$(CFG)" == "MapEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TileSet.cpp
DEP_CPP_TILES=\
	".\Attribute.h"\
	".\CategoriesDlg.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\DupSearchDlg.h"\
	".\FindDupDlg.h"\
	".\IFFFile.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewCategoryDlg.h"\
	".\NewGroupDlg.h"\
	".\NewTileSetDlg.h"\
	".\ObjectSet.h"\
	".\RemDupDlg.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\TileSet.obj" : $(SOURCE) $(DEP_CPP_TILES) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\TileSet.obj" : $(SOURCE) $(DEP_CPP_TILES) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\TileSet.sbr" : $(SOURCE) $(DEP_CPP_TILES) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\TileSet.obj" : $(SOURCE) $(DEP_CPP_TILES) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TileSet.h

!IF  "$(CFG)" == "MapEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TileSetView.cpp
DEP_CPP_TILESE=\
	".\Attribute.h"\
	".\AttributesDlg.h"\
	".\AttributeSheet.h"\
	".\AttributeSheetPreview.h"\
	".\BoldComboBox.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\LayerBar.h"\
	".\MainFrm.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewTileSetDlg.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\ShowUsageDlg.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	".\TileSetView.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\TileSetView.obj" : $(SOURCE) $(DEP_CPP_TILESE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\TileSetView.obj" : $(SOURCE) $(DEP_CPP_TILESE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\TileSetView.sbr" : $(SOURCE) $(DEP_CPP_TILESE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\TileSetView.obj" : $(SOURCE) $(DEP_CPP_TILESE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewMapDlg.cpp
DEP_CPP_NEWMA=\
	".\ColorButton.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewMapDlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\NewMapDlg.obj" : $(SOURCE) $(DEP_CPP_NEWMA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\NewMapDlg.obj" : $(SOURCE) $(DEP_CPP_NEWMA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\NewMapDlg.sbr" : $(SOURCE) $(DEP_CPP_NEWMA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\NewMapDlg.obj" : $(SOURCE) $(DEP_CPP_NEWMA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewCategoryDlg.cpp
DEP_CPP_NEWCA=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewCategoryDlg.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\NewCategoryDlg.obj" : $(SOURCE) $(DEP_CPP_NEWCA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\NewCategoryDlg.obj" : $(SOURCE) $(DEP_CPP_NEWCA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\NewCategoryDlg.sbr" : $(SOURCE) $(DEP_CPP_NEWCA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\NewCategoryDlg.obj" : $(SOURCE) $(DEP_CPP_NEWCA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewGroupDlg.cpp
DEP_CPP_NEWGR=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewGroupDlg.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\NewGroupDlg.obj" : $(SOURCE) $(DEP_CPP_NEWGR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\NewGroupDlg.obj" : $(SOURCE) $(DEP_CPP_NEWGR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\NewGroupDlg.sbr" : $(SOURCE) $(DEP_CPP_NEWGR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\NewGroupDlg.obj" : $(SOURCE) $(DEP_CPP_NEWGR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TileCategory.cpp
DEP_CPP_TILEC=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	".\TileCategory.h"\
	".\TileList.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\TileCategory.obj" : $(SOURCE) $(DEP_CPP_TILEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\TileCategory.obj" : $(SOURCE) $(DEP_CPP_TILEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\TileCategory.sbr" : $(SOURCE) $(DEP_CPP_TILEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\TileCategory.obj" : $(SOURCE) $(DEP_CPP_TILEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewTileSetDlg.cpp
DEP_CPP_NEWTI=\
	".\ColorButton.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewTileSetDlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\NewTileSetDlg.obj" : $(SOURCE) $(DEP_CPP_NEWTI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\NewTileSetDlg.obj" : $(SOURCE) $(DEP_CPP_NEWTI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\NewTileSetDlg.sbr" : $(SOURCE) $(DEP_CPP_NEWTI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\NewTileSetDlg.obj" : $(SOURCE) $(DEP_CPP_NEWTI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapOverview.cpp
DEP_CPP_MAPOV=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\MapOverview.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MapOverview.obj" : $(SOURCE) $(DEP_CPP_MAPOV) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MapOverview.obj" : $(SOURCE) $(DEP_CPP_MAPOV) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MapOverview.sbr" : $(SOURCE) $(DEP_CPP_MAPOV) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MapOverview.obj" : $(SOURCE) $(DEP_CPP_MAPOV) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapFrame.cpp
DEP_CPP_MAPFR=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\EmptyView.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\MapOverview.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	".\TileSetView.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MapFrame.obj" : $(SOURCE) $(DEP_CPP_MAPFR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MapFrame.obj" : $(SOURCE) $(DEP_CPP_MAPFR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MapFrame.sbr" : $(SOURCE) $(DEP_CPP_MAPFR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MapFrame.obj" : $(SOURCE) $(DEP_CPP_MAPFR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TileSetOp.cpp
DEP_CPP_TILESET=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\TileSetOp.obj" : $(SOURCE) $(DEP_CPP_TILESET) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\TileSetOp.obj" : $(SOURCE) $(DEP_CPP_TILESET) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\TileSetOp.sbr" : $(SOURCE) $(DEP_CPP_TILESET) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\TileSetOp.obj" : $(SOURCE) $(DEP_CPP_TILESET) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dib.cpp
DEP_CPP_DIB_C=\
	".\mymacros.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\dib.sbr" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dibdoc.cpp
DEP_CPP_DIBDO=\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\mymacros.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\Dibdoc.obj" : $(SOURCE) $(DEP_CPP_DIBDO) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\Dibdoc.obj" : $(SOURCE) $(DEP_CPP_DIBDO) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\Dibdoc.sbr" : $(SOURCE) $(DEP_CPP_DIBDO) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\Dibdoc.obj" : $(SOURCE) $(DEP_CPP_DIBDO) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dibpal.cpp
DEP_CPP_DIBPA=\
	".\dibpal.h"\
	".\mymacros.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\dibpal.sbr" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TileListBox.cpp
DEP_CPP_TILEL=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\TileListBox.obj" : $(SOURCE) $(DEP_CPP_TILEL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\TileListBox.obj" : $(SOURCE) $(DEP_CPP_TILEL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\TileListBox.sbr" : $(SOURCE) $(DEP_CPP_TILEL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\TileListBox.obj" : $(SOURCE) $(DEP_CPP_TILEL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FindDupDlg.cpp
DEP_CPP_FINDD=\
	".\FindDupDlg.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\FindDupDlg.obj" : $(SOURCE) $(DEP_CPP_FINDD) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\FindDupDlg.obj" : $(SOURCE) $(DEP_CPP_FINDD) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\FindDupDlg.sbr" : $(SOURCE) $(DEP_CPP_FINDD) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\FindDupDlg.obj" : $(SOURCE) $(DEP_CPP_FINDD) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RemDupDlg.cpp
DEP_CPP_REMDU=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\RemDupDlg.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\RemDupDlg.obj" : $(SOURCE) $(DEP_CPP_REMDU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\RemDupDlg.obj" : $(SOURCE) $(DEP_CPP_REMDU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\RemDupDlg.sbr" : $(SOURCE) $(DEP_CPP_REMDU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\RemDupDlg.obj" : $(SOURCE) $(DEP_CPP_REMDU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapEdit.txt

!IF  "$(CFG)" == "MapEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DupSearchDlg.cpp
DEP_CPP_DUPSE=\
	".\DupSearchDlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\DupSearchDlg.obj" : $(SOURCE) $(DEP_CPP_DUPSE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\DupSearchDlg.obj" : $(SOURCE) $(DEP_CPP_DUPSE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\DupSearchDlg.sbr" : $(SOURCE) $(DEP_CPP_DUPSE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\DupSearchDlg.obj" : $(SOURCE) $(DEP_CPP_DUPSE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TileGroup.cpp
DEP_CPP_TILEG=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\TileGroup.obj" : $(SOURCE) $(DEP_CPP_TILEG) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\TileGroup.obj" : $(SOURCE) $(DEP_CPP_TILEG) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\TileGroup.sbr" : $(SOURCE) $(DEP_CPP_TILEG) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\TileGroup.obj" : $(SOURCE) $(DEP_CPP_TILEG) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyPropertySheet.cpp
DEP_CPP_MYPRO=\
	".\AppPropPage.h"\
	".\MyPropertySheet.h"\
	".\PropPageAmen.h"\
	".\ScenPropPage.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MyPropertySheet.obj" : $(SOURCE) $(DEP_CPP_MYPRO) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MyPropertySheet.obj" : $(SOURCE) $(DEP_CPP_MYPRO) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MyPropertySheet.sbr" : $(SOURCE) $(DEP_CPP_MYPRO) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MyPropertySheet.obj" : $(SOURCE) $(DEP_CPP_MYPRO) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyMultiDocTemplate.cpp
DEP_CPP_MYMUL=\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MyMultiDocTemplate.obj" : $(SOURCE) $(DEP_CPP_MYMUL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MyMultiDocTemplate.obj" : $(SOURCE) $(DEP_CPP_MYMUL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MyMultiDocTemplate.sbr" : $(SOURCE) $(DEP_CPP_MYMUL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MyMultiDocTemplate.obj" : $(SOURCE) $(DEP_CPP_MYMUL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AppPropPage.cpp
DEP_CPP_APPPR=\
	".\AppPropPage.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\AppPropPage.obj" : $(SOURCE) $(DEP_CPP_APPPR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\AppPropPage.obj" : $(SOURCE) $(DEP_CPP_APPPR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\AppPropPage.sbr" : $(SOURCE) $(DEP_CPP_APPPR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\AppPropPage.obj" : $(SOURCE) $(DEP_CPP_APPPR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapLayer.cpp
DEP_CPP_MAPLA=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MapLayer.obj" : $(SOURCE) $(DEP_CPP_MAPLA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MapLayer.obj" : $(SOURCE) $(DEP_CPP_MAPLA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MapLayer.sbr" : $(SOURCE) $(DEP_CPP_MAPLA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MapLayer.obj" : $(SOURCE) $(DEP_CPP_MAPLA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TileLayer.cpp

!IF  "$(CFG)" == "MapEditor - Win32 Release"

DEP_CPP_TILELA=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NumberDlg.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	".\TileSetView.h"\
	

"$(INTDIR)\TileLayer.obj" : $(SOURCE) $(DEP_CPP_TILELA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

DEP_CPP_TILELA=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NumberDlg.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	".\TileSetView.h"\
	

"$(INTDIR)\TileLayer.obj" : $(SOURCE) $(DEP_CPP_TILELA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\TileLayer.sbr" : $(SOURCE) $(DEP_CPP_TILELA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

DEP_CPP_TILELA=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NumberDlg.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileListBox.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	".\TileSetView.h"\
	

"$(INTDIR)\TileLayer.obj" : $(SOURCE) $(DEP_CPP_TILELA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LayersDlg.cpp
DEP_CPP_LAYER=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\DoorwayLayer.h"\
	".\LayersDlg.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewLayerDlg.h"\
	".\ObjectLayer.h"\
	".\ObjectSet.h"\
	".\ScenarioLayer.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\LayersDlg.obj" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\LayersDlg.obj" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\LayersDlg.sbr" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\LayersDlg.obj" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorButton.cpp
DEP_CPP_COLOR=\
	".\ColorButton.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ColorButton.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ColorButton.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ColorButton.sbr" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ColorButton.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapBmpDlg.cpp
DEP_CPP_MAPBM=\
	".\MapBmpDlg.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MapBmpDlg.obj" : $(SOURCE) $(DEP_CPP_MAPBM) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MapBmpDlg.obj" : $(SOURCE) $(DEP_CPP_MAPBM) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MapBmpDlg.sbr" : $(SOURCE) $(DEP_CPP_MAPBM) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MapBmpDlg.obj" : $(SOURCE) $(DEP_CPP_MAPBM) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LayerBar.cpp
DEP_CPP_LAYERB=\
	".\Attribute.h"\
	".\BoldComboBox.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\LayerBar.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\LayerBar.obj" : $(SOURCE) $(DEP_CPP_LAYERB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\LayerBar.obj" : $(SOURCE) $(DEP_CPP_LAYERB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\LayerBar.sbr" : $(SOURCE) $(DEP_CPP_LAYERB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\LayerBar.obj" : $(SOURCE) $(DEP_CPP_LAYERB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewLayerDlg.cpp
DEP_CPP_NEWLA=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewLayerDlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\NewLayerDlg.obj" : $(SOURCE) $(DEP_CPP_NEWLA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\NewLayerDlg.obj" : $(SOURCE) $(DEP_CPP_NEWLA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\NewLayerDlg.sbr" : $(SOURCE) $(DEP_CPP_NEWLA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\NewLayerDlg.obj" : $(SOURCE) $(DEP_CPP_NEWLA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FileFormat.txt

!IF  "$(CFG)" == "MapEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Splash.cpp
DEP_CPP_SPLAS=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\Splash.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\Splash.sbr" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ShowUsageDlg.cpp
DEP_CPP_SHOWU=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ShowUsageDlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ShowUsageDlg.obj" : $(SOURCE) $(DEP_CPP_SHOWU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ShowUsageDlg.obj" : $(SOURCE) $(DEP_CPP_SHOWU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ShowUsageDlg.sbr" : $(SOURCE) $(DEP_CPP_SHOWU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ShowUsageDlg.obj" : $(SOURCE) $(DEP_CPP_SHOWU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IFFFile.cpp
DEP_CPP_IFFFI=\
	".\IFFFile.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\IFFFile.obj" : $(SOURCE) $(DEP_CPP_IFFFI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\IFFFile.obj" : $(SOURCE) $(DEP_CPP_IFFFI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\IFFFile.sbr" : $(SOURCE) $(DEP_CPP_IFFFI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\IFFFile.obj" : $(SOURCE) $(DEP_CPP_IFFFI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CategoriesDlg.cpp
DEP_CPP_CATEG=\
	".\CategoriesDlg.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	".\TileCategory.h"\
	".\TileList.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\CategoriesDlg.obj" : $(SOURCE) $(DEP_CPP_CATEG) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\CategoriesDlg.obj" : $(SOURCE) $(DEP_CPP_CATEG) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\CategoriesDlg.sbr" : $(SOURCE) $(DEP_CPP_CATEG) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\CategoriesDlg.obj" : $(SOURCE) $(DEP_CPP_CATEG) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectSet.cpp

!IF  "$(CFG)" == "MapEditor - Win32 Release"

DEP_CPP_OBJEC=\
	".\AnimMapObject.h"\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

"$(INTDIR)\ObjectSet.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

DEP_CPP_OBJEC=\
	".\AnimMapObject.h"\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

"$(INTDIR)\ObjectSet.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ObjectSet.sbr" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

DEP_CPP_OBJEC=\
	".\AnimMapObject.h"\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

"$(INTDIR)\ObjectSet.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectLayer.cpp

!IF  "$(CFG)" == "MapEditor - Win32 Release"

DEP_CPP_OBJECT=\
	".\AnimMapObject.h"\
	".\AnimPropPage.h"\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributesDlg.h"\
	".\AttributeSheet.h"\
	".\AttributeSheetPreview.h"\
	".\ColorButton.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\CycleButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\MapUpdate.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectLayer.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TextPage.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

"$(INTDIR)\ObjectLayer.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

DEP_CPP_OBJECT=\
	".\AnimMapObject.h"\
	".\AnimPropPage.h"\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributesDlg.h"\
	".\AttributeSheet.h"\
	".\AttributeSheetPreview.h"\
	".\ColorButton.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\CycleButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\MapUpdate.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectLayer.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TextPage.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

"$(INTDIR)\ObjectLayer.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ObjectLayer.sbr" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

DEP_CPP_OBJECT=\
	".\AnimMapObject.h"\
	".\AnimPropPage.h"\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributesDlg.h"\
	".\AttributeSheet.h"\
	".\AttributeSheetPreview.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\CycleButton.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\MapUpdate.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectLayer.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TextPage.h"\
	

"$(INTDIR)\ObjectLayer.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectSetView.cpp
DEP_CPP_OBJECTS=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributesDlg.h"\
	".\AttributeSheet.h"\
	".\AttributeSheetPreview.h"\
	".\ColorButton.h"\
	".\CycleButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mogdlg.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectLayer.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ObjectSetView.obj" : $(SOURCE) $(DEP_CPP_OBJECTS) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ObjectSetView.obj" : $(SOURCE) $(DEP_CPP_OBJECTS) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ObjectSetView.sbr" : $(SOURCE) $(DEP_CPP_OBJECTS) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ObjectSetView.obj" : $(SOURCE) $(DEP_CPP_OBJECTS) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectListBox.cpp
DEP_CPP_OBJECTL=\
	".\Attribute.h"\
	".\CycleButton.h"\
	".\MapEditor.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileCategory.h"\
	".\TileList.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ObjectListBox.obj" : $(SOURCE) $(DEP_CPP_OBJECTL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ObjectListBox.obj" : $(SOURCE) $(DEP_CPP_OBJECTL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ObjectListBox.sbr" : $(SOURCE) $(DEP_CPP_OBJECTL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ObjectListBox.obj" : $(SOURCE) $(DEP_CPP_OBJECTL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EmptyView.cpp
DEP_CPP_EMPTY=\
	".\EmptyView.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\EmptyView.obj" : $(SOURCE) $(DEP_CPP_EMPTY) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\EmptyView.obj" : $(SOURCE) $(DEP_CPP_EMPTY) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\EmptyView.sbr" : $(SOURCE) $(DEP_CPP_EMPTY) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\EmptyView.obj" : $(SOURCE) $(DEP_CPP_EMPTY) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BoldComboBox.cpp
DEP_CPP_BOLDC=\
	".\BoldComboBox.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\BoldComboBox.obj" : $(SOURCE) $(DEP_CPP_BOLDC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\BoldComboBox.obj" : $(SOURCE) $(DEP_CPP_BOLDC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\BoldComboBox.sbr" : $(SOURCE) $(DEP_CPP_BOLDC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\BoldComboBox.obj" : $(SOURCE) $(DEP_CPP_BOLDC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AttributeLayer.cpp

!IF  "$(CFG)" == "MapEditor - Win32 Release"

DEP_CPP_ATTRI=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributeView.h"\
	".\ColorButton.h"\
	".\ComputeLayerDlg.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectLayer.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

"$(INTDIR)\AttributeLayer.obj" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

DEP_CPP_ATTRI=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributeView.h"\
	".\ColorButton.h"\
	".\ComputeLayerDlg.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectLayer.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

"$(INTDIR)\AttributeLayer.obj" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\AttributeLayer.sbr" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

DEP_CPP_ATTRI=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributeView.h"\
	".\ColorButton.h"\
	".\ComputeLayerDlg.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapEditorView.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\ObjectLayer.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

"$(INTDIR)\AttributeLayer.obj" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AttributeView.cpp

!IF  "$(CFG)" == "MapEditor - Win32 Release"

DEP_CPP_ATTRIB=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributeView.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

"$(INTDIR)\AttributeView.obj" : $(SOURCE) $(DEP_CPP_ATTRIB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

DEP_CPP_ATTRIB=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributeView.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

"$(INTDIR)\AttributeView.obj" : $(SOURCE) $(DEP_CPP_ATTRIB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\AttributeView.sbr" : $(SOURCE) $(DEP_CPP_ATTRIB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

DEP_CPP_ATTRIB=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributeView.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileLayer.h"\
	".\TileList.h"\
	".\TileSet.h"\
	".\TileSetOp.h"\
	

"$(INTDIR)\AttributeView.obj" : $(SOURCE) $(DEP_CPP_ATTRIB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewAttributeDlg.cpp
DEP_CPP_NEWAT=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\MapEditor.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NewAttributeDlg.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\NewAttributeDlg.obj" : $(SOURCE) $(DEP_CPP_NEWAT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\NewAttributeDlg.obj" : $(SOURCE) $(DEP_CPP_NEWAT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\NewAttributeDlg.sbr" : $(SOURCE) $(DEP_CPP_NEWAT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\NewAttributeDlg.obj" : $(SOURCE) $(DEP_CPP_NEWAT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Attribute.cpp
DEP_CPP_ATTRIBU=\
	".\Attribute.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\Attribute.obj" : $(SOURCE) $(DEP_CPP_ATTRIBU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\Attribute.obj" : $(SOURCE) $(DEP_CPP_ATTRIBU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\Attribute.sbr" : $(SOURCE) $(DEP_CPP_ATTRIBU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\Attribute.obj" : $(SOURCE) $(DEP_CPP_ATTRIBU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TileAttribute.cpp
DEP_CPP_TILEA=\
	".\Attribute.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\TileAttribute.obj" : $(SOURCE) $(DEP_CPP_TILEA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\TileAttribute.obj" : $(SOURCE) $(DEP_CPP_TILEA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\TileAttribute.sbr" : $(SOURCE) $(DEP_CPP_TILEA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\TileAttribute.obj" : $(SOURCE) $(DEP_CPP_TILEA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScenPropPage.cpp
DEP_CPP_SCENP=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ScenPropPage.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ScenPropPage.obj" : $(SOURCE) $(DEP_CPP_SCENP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ScenPropPage.obj" : $(SOURCE) $(DEP_CPP_SCENP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ScenPropPage.sbr" : $(SOURCE) $(DEP_CPP_SCENP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ScenPropPage.obj" : $(SOURCE) $(DEP_CPP_SCENP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScenarioSet.cpp
DEP_CPP_SCENA=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ScenarioSet.obj" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ScenarioSet.obj" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ScenarioSet.sbr" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ScenarioSet.obj" : $(SOURCE) $(DEP_CPP_SCENA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScenarioView.cpp
DEP_CPP_SCENAR=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\CycleButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectLayer.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\ScenarioLayer.h"\
	".\ScenarioSet.h"\
	".\ScenarioView.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ScenarioView.obj" : $(SOURCE) $(DEP_CPP_SCENAR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ScenarioView.obj" : $(SOURCE) $(DEP_CPP_SCENAR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ScenarioView.sbr" : $(SOURCE) $(DEP_CPP_SCENAR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ScenarioView.obj" : $(SOURCE) $(DEP_CPP_SCENAR) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScenarioLayer.cpp
DEP_CPP_SCENARI=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\CycleButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\MapUpdate.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectLayer.h"\
	".\ObjectListBox.h"\
	".\ObjectSet.h"\
	".\ObjectSetView.h"\
	".\ScenarioLayer.h"\
	".\ScenarioSet.h"\
	".\ScenarioView.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ScenarioLayer.obj" : $(SOURCE) $(DEP_CPP_SCENARI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ScenarioLayer.obj" : $(SOURCE) $(DEP_CPP_SCENARI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ScenarioLayer.sbr" : $(SOURCE) $(DEP_CPP_SCENARI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ScenarioLayer.obj" : $(SOURCE) $(DEP_CPP_SCENARI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DoorwayLayer.cpp
DEP_CPP_DOORW=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\DoorwayLayer.h"\
	".\Doorways\doorway.c"\
	".\DoorwayView.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\DoorwayLayer.obj" : $(SOURCE) $(DEP_CPP_DOORW) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\DoorwayLayer.obj" : $(SOURCE) $(DEP_CPP_DOORW) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\DoorwayLayer.sbr" : $(SOURCE) $(DEP_CPP_DOORW) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\DoorwayLayer.obj" : $(SOURCE) $(DEP_CPP_DOORW) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DoorwayView.cpp
DEP_CPP_DOORWA=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\DoorwayLayer.h"\
	".\DoorwayView.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapFrame.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\DoorwayView.obj" : $(SOURCE) $(DEP_CPP_DOORWA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\DoorwayView.obj" : $(SOURCE) $(DEP_CPP_DOORWA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\DoorwayView.sbr" : $(SOURCE) $(DEP_CPP_DOORWA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\DoorwayView.obj" : $(SOURCE) $(DEP_CPP_DOORWA) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NumberDlg.cpp
DEP_CPP_NUMBE=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\NumberDlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\NumberDlg.obj" : $(SOURCE) $(DEP_CPP_NUMBE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\NumberDlg.obj" : $(SOURCE) $(DEP_CPP_NUMBE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\NumberDlg.sbr" : $(SOURCE) $(DEP_CPP_NUMBE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\NumberDlg.obj" : $(SOURCE) $(DEP_CPP_NUMBE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AttributesDlg.cpp
DEP_CPP_ATTRIBUT=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\AttributesDlg.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\AttributesDlg.obj" : $(SOURCE) $(DEP_CPP_ATTRIBUT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\AttributesDlg.obj" : $(SOURCE) $(DEP_CPP_ATTRIBUT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\AttributesDlg.sbr" : $(SOURCE) $(DEP_CPP_ATTRIBUT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\AttributesDlg.obj" : $(SOURCE) $(DEP_CPP_ATTRIBUT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MapObject.cpp
DEP_CPP_MAPOB=\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MapObject.obj" : $(SOURCE) $(DEP_CPP_MAPOB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MapObject.obj" : $(SOURCE) $(DEP_CPP_MAPOB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MapObject.sbr" : $(SOURCE) $(DEP_CPP_MAPOB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MapObject.obj" : $(SOURCE) $(DEP_CPP_MAPOB) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropPageAmen.cpp
DEP_CPP_PROPP=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\PropPageAmen.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\PropPageAmen.obj" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\PropPageAmen.obj" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\PropPageAmen.sbr" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\PropPageAmen.obj" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CycleButton.cpp
DEP_CPP_CYCLE=\
	".\CycleButton.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\CycleButton.obj" : $(SOURCE) $(DEP_CPP_CYCLE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\CycleButton.obj" : $(SOURCE) $(DEP_CPP_CYCLE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\CycleButton.sbr" : $(SOURCE) $(DEP_CPP_CYCLE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\CycleButton.obj" : $(SOURCE) $(DEP_CPP_CYCLE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AnimMapObject.cpp
DEP_CPP_ANIMM=\
	".\AnimMapObject.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\MapEditor.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\AnimMapObject.obj" : $(SOURCE) $(DEP_CPP_ANIMM) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\AnimMapObject.obj" : $(SOURCE) $(DEP_CPP_ANIMM) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\AnimMapObject.sbr" : $(SOURCE) $(DEP_CPP_ANIMM) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\AnimMapObject.obj" : $(SOURCE) $(DEP_CPP_ANIMM) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AttributeSheet.cpp
DEP_CPP_ATTRIBUTE=\
	".\AnimMapObject.h"\
	".\Attribute.h"\
	".\AttributesDlg.h"\
	".\AttributeSheet.h"\
	".\AttributeSheetPreview.h"\
	".\ColorButton.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\MapEditorDoc.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\ScenarioSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\AttributeSheet.obj" : $(SOURCE) $(DEP_CPP_ATTRIBUTE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\AttributeSheet.obj" : $(SOURCE) $(DEP_CPP_ATTRIBUTE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\AttributeSheet.sbr" : $(SOURCE) $(DEP_CPP_ATTRIBUTE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\AttributeSheet.obj" : $(SOURCE) $(DEP_CPP_ATTRIBUTE) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AttributeSheetPreview.cpp
DEP_CPP_ATTRIBUTES=\
	".\AttributeSheetPreview.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\AttributeSheetPreview.obj" : $(SOURCE) $(DEP_CPP_ATTRIBUTES)\
 "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\AttributeSheetPreview.obj" : $(SOURCE) $(DEP_CPP_ATTRIBUTES)\
 "$(INTDIR)" "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\AttributeSheetPreview.sbr" : $(SOURCE) $(DEP_CPP_ATTRIBUTES)\
 "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\AttributeSheetPreview.obj" : $(SOURCE) $(DEP_CPP_ATTRIBUTES)\
 "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AnimPropPage.cpp
DEP_CPP_ANIMP=\
	".\AnimMapObject.h"\
	".\AnimPropPage.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\MapEditor.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ObjectSet.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileCategory.h"\
	".\TileList.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\AnimPropPage.obj" : $(SOURCE) $(DEP_CPP_ANIMP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\AnimPropPage.obj" : $(SOURCE) $(DEP_CPP_ANIMP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\AnimPropPage.sbr" : $(SOURCE) $(DEP_CPP_ANIMP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\AnimPropPage.obj" : $(SOURCE) $(DEP_CPP_ANIMP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ComputeLayerDlg.cpp
DEP_CPP_COMPU=\
	".\Attribute.h"\
	".\AttributeLayer.h"\
	".\ComputeLayerDlg.h"\
	".\MapEditor.h"\
	".\MapLayer.h"\
	".\MapObject.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ComputeLayerDlg.obj" : $(SOURCE) $(DEP_CPP_COMPU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ComputeLayerDlg.obj" : $(SOURCE) $(DEP_CPP_COMPU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ComputeLayerDlg.sbr" : $(SOURCE) $(DEP_CPP_COMPU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ComputeLayerDlg.obj" : $(SOURCE) $(DEP_CPP_COMPU) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSpriteSequence.cpp
DEP_CPP_CSPRI=\
	"..\animeditor\AnimEditorDoc.h"\
	"..\animeditor\CCel.h"\
	"..\animeditor\CSequence.h"\
	"..\animeditor\CSequenceCel.h"\
	"..\animeditor\DIBitmap.h"\
	"..\animeditor\stdafx.h"\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\CSpriteSequence.obj" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\CSpriteSequence.obj" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\CSpriteSequence.sbr" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\CSpriteSequence.obj" : $(SOURCE) $(DEP_CPP_CSPRI) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSpriteCatalog.cpp
DEP_CPP_CSPRIT=\
	".\CSpriteCatalog.h"\
	".\CSpriteSequence.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\CSpriteCatalog.obj" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\CSpriteCatalog.obj" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\CSpriteCatalog.sbr" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\CSpriteCatalog.obj" : $(SOURCE) $(DEP_CPP_CSPRIT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScriptsDlg.cpp
DEP_CPP_SCRIP=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\ScriptsDlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\ScriptsDlg.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\ScriptsDlg.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ScriptsDlg.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\ScriptsDlg.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TextPage.cpp
DEP_CPP_TEXTP=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	".\TextPage.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\TextPage.obj" : $(SOURCE) $(DEP_CPP_TEXTP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\TextPage.obj" : $(SOURCE) $(DEP_CPP_TEXTP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\TextPage.sbr" : $(SOURCE) $(DEP_CPP_TEXTP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\TextPage.obj" : $(SOURCE) $(DEP_CPP_TEXTP) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MogDlg.cpp
DEP_CPP_MOGDL=\
	".\MapEditor.h"\
	".\mogdlg.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\MogDlg.obj" : $(SOURCE) $(DEP_CPP_MOGDL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\MogDlg.obj" : $(SOURCE) $(DEP_CPP_MOGDL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\MogDlg.sbr" : $(SOURCE) $(DEP_CPP_MOGDL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\MogDlg.obj" : $(SOURCE) $(DEP_CPP_MOGDL) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SelectDlg.cpp
DEP_CPP_SELEC=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\SelectDlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\SelectDlg.obj" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\SelectDlg.obj" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\SelectDlg.sbr" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\SelectDlg.obj" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ExpandDlg.cpp

!IF  "$(CFG)" == "MapEditor - Win32 Release"

DEP_CPP_EXPAN=\
	".\ExpandDlg.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

"$(INTDIR)\ExpandDlg.obj" : $(SOURCE) $(DEP_CPP_EXPAN) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

DEP_CPP_EXPAN=\
	".\ExpandDlg.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\stdafx.h"\
	

"$(INTDIR)\ExpandDlg.obj" : $(SOURCE) $(DEP_CPP_EXPAN) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\ExpandDlg.sbr" : $(SOURCE) $(DEP_CPP_EXPAN) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"

DEP_CPP_EXPAN=\
	".\ExpandDlg.h"\
	".\MapEditor.h"\
	".\stdafx.h"\
	

"$(INTDIR)\ExpandDlg.obj" : $(SOURCE) $(DEP_CPP_EXPAN) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RotateDlg.cpp
DEP_CPP_ROTAT=\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\rotatedlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\RotateDlg.obj" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\RotateDlg.obj" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\RotateDlg.sbr" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\RotateDlg.obj" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RulerWnd.cpp
DEP_CPP_RULER=\
	".\Attribute.h"\
	".\ColorButton.h"\
	".\dibdoc.h"\
	".\dibpal.h"\
	".\MapEditor.h"\
	".\mymacros.h"\
	".\MyMultiDocTemplate.h"\
	".\RulerWnd.h"\
	".\Sprites\..\dib.h"\
	".\stdafx.h"\
	".\TileAttribute.h"\
	".\TileCategory.h"\
	".\TileGroup.h"\
	".\TileList.h"\
	".\TileSet.h"\
	

!IF  "$(CFG)" == "MapEditor - Win32 Release"


"$(INTDIR)\RulerWnd.obj" : $(SOURCE) $(DEP_CPP_RULER) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"


"$(INTDIR)\RulerWnd.obj" : $(SOURCE) $(DEP_CPP_RULER) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"

"$(INTDIR)\RulerWnd.sbr" : $(SOURCE) $(DEP_CPP_RULER) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Underscore"


"$(INTDIR)\RulerWnd.obj" : $(SOURCE) $(DEP_CPP_RULER) "$(INTDIR)"\
 "$(INTDIR)\MapEditor.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section MapEditor : {FE98DB12-F45D-11CF-88D3-00A02451562E}
# 	2:9:CMapFrame:Palette support added
# End Section
################################################################################
################################################################################
# Section MapEditor : {85CA60AC-8E59-11CF-88D3-00A02451562E}
# 	2:14:CObjectSetView:Palette support added
# End Section
################################################################################
################################################################################
# Section MapEditor : {85CA60B0-8E59-11CF-88D3-00A02451562E}
# 	0:8:Splash.h:C:\Lee\MapEditor\Splash.h
# 	0:10:Splash.cpp:C:\Lee\MapEditor\Splash.cpp
# 	1:10:IDB_SPLASH:124
# 	2:10:ResHdrName:resource.h
# 	2:11:ProjHdrName:stdafx.h
# 	2:10:WrapperDef:_SPLASH_SCRN_
# 	2:12:SplClassName:CSplashWnd
# 	2:21:SplashScreenInsertKey:4.0
# 	2:10:HeaderName:Splash.h
# 	2:10:ImplemName:Splash.cpp
# 	2:7:BmpID16:IDB_SPLASH
# End Section
################################################################################
################################################################################
# Section MapEditor : {85CA60B4-8E59-11CF-88D3-00A02451562E}
# 	2:10:CLayersDlg:1
# 	2:9:CLayerBar:1
# 	2:14:CCategoriesDlg:1
# End Section
################################################################################
