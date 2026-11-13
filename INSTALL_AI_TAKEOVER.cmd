@echo off
setlocal EnableExtensions EnableDelayedExpansion
title ArmyMen AI Takeover - One Click Build and Install

rem Run this file from the main branch checkout on a Windows machine.
rem The 1998 project uses NMAKE and needs a compatible legacy MSVC/DirectX SDK.
set "ROOT=%~dp0"
set "SOURCE=%ROOT%src"
set "RUNTIME=%SOURCE%\RunTime"
set "BUILD=%SOURCE%\Release\Armymen.exe"
set "GAME=%RUNTIME%\Armymen.exe"
set "BACKUP=%RUNTIME%\Armymen.exe.before-ai-takeover"

echo.
echo ========================================
echo   ArmyMen: Full AI Spectator Takeover
echo ========================================
echo.

if not exist "%SOURCE%\Armymen.mak" (
    echo ERROR: Source makefile not found. Run the installer inside the ArmyMen repository.
    goto :failed
)

rem Pull only if already on main. Never discard local changes.
where git >nul 2>&1
if not errorlevel 1 (
    git -C "%ROOT%" rev-parse --is-inside-work-tree >nul 2>&1
    if not errorlevel 1 (
        for /f "delims=" %%B in ('git -C "%ROOT%" branch --show-current') do set "CURRENT_BRANCH=%%B"
        if /i "!CURRENT_BRANCH!"=="main" (
            echo Updating ArmyMen main...
            git -C "%ROOT%" pull --ff-only origin main
            if errorlevel 1 (
                echo ERROR: Could not fast-forward. Your local edits were left untouched.
                goto :failed
            )
        ) else (
            echo Using current checkout. Switch to main for the current release.
        )
    )
)

if not exist "%SOURCE%\AutoAITakeover.inc" (
    echo ERROR: AI Takeover source is missing.
    echo Download the latest main branch from GitHub first.
    goto :failed
)

where nmake >nul 2>&1
if errorlevel 1 (
    echo ERROR: NMAKE is not available in PATH.
    echo Open a Developer Command Prompt with the compatible legacy MSVC toolchain,
    echo then double-click this installer again.
    echo The original game is a 1998 VC4.2 / DirectX project, not a modern MSBuild solution.
    goto :failed
)
where cl >nul 2>&1
if errorlevel 1 (
    echo ERROR: MSVC cl.exe is not available in PATH.
    goto :failed
)

echo Building a patched executable...
pushd "%SOURCE%"
nmake /f "Armymen.mak" CFG="ArmyMen - Win32 Release"
if errorlevel 1 (
    popd
    echo ERROR: Compilation failed. Nothing was installed.
    goto :failed
)
popd

if not exist "%BUILD%" (
    echo ERROR: Build completed without creating %BUILD%.
    goto :failed
)

if not exist "%RUNTIME%" mkdir "%RUNTIME%"
if exist "%GAME%" if not exist "%BACKUP%" (
    copy /y "%GAME%" "%BACKUP%" >nul
    if errorlevel 1 (
        echo ERROR: Cannot back up the original executable.
        goto :failed
    )
)

copy /y "%BUILD%" "%GAME%" >nul
if errorlevel 1 (
    echo ERROR: Could not install the patched executable.
    goto :failed
)

echo.
echo SUCCESS: AI spectator build installed to "%GAME%"
echo Original game backed up as "%BACKUP%" if it existed.
echo Launching ArmyMen...
pushd "%RUNTIME%"
start "" "Armymen.exe"
popd
exit /b 0

:failed
echo.
echo AI Takeover has NOT been installed. See the message above.
pause
exit /b 1
