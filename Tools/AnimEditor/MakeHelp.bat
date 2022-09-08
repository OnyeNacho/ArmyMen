@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by ANIMEDITOR.HPJ. >"hlp\AnimEditor.hm"
echo. >>"hlp\AnimEditor.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\AnimEditor.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\AnimEditor.hm"
echo. >>"hlp\AnimEditor.hm"
echo // Prompts (IDP_*) >>"hlp\AnimEditor.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\AnimEditor.hm"
echo. >>"hlp\AnimEditor.hm"
echo // Resources (IDR_*) >>"hlp\AnimEditor.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\AnimEditor.hm"
echo. >>"hlp\AnimEditor.hm"
echo // Dialogs (IDD_*) >>"hlp\AnimEditor.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\AnimEditor.hm"
echo. >>"hlp\AnimEditor.hm"
echo // Frame Controls (IDW_*) >>"hlp\AnimEditor.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\AnimEditor.hm"
REM -- Make help for Project ANIMEDITOR


echo Building Win32 Help files
start /wait hcrtf -x "hlp\AnimEditor.hpj"
echo.
if exist Debug\nul copy "hlp\AnimEditor.hlp" Debug
if exist Debug\nul copy "hlp\AnimEditor.cnt" Debug
if exist Release\nul copy "hlp\AnimEditor.hlp" Release
if exist Release\nul copy "hlp\AnimEditor.cnt" Release
echo.


