@echo off
REM Quick build and launch script for SubspaceUE on Windows
REM This script compiles the project and launches the Unreal Editor

echo ========================================
echo SubspaceUE - Quick Build and Launch
echo ========================================
echo.

REM Set the Unreal Engine path (adjust if your installation is different)
set UE_PATH=C:\Program Files\Epic Games\UE_5.6
set UE_EDITOR=%UE_PATH%\Engine\Binaries\Win64\UnrealEditor.exe
set UE_BUILD=%UE_PATH%\Engine\Build\BatchFiles\Build.bat

REM Check if Unreal Engine is installed
if not exist "%UE_EDITOR%" (
    echo ERROR: Unreal Engine 5.6 not found at %UE_PATH%
    echo Please update the UE_PATH variable in this script to point to your UE installation.
    echo Common locations:
    echo   C:\Program Files\Epic Games\UE_5.6
    echo   D:\Epic Games\UE_5.6
    pause
    exit /b 1
)

echo Found Unreal Engine at: %UE_PATH%
echo.

REM Get the project path
set PROJECT_PATH=%~dp0SubspaceUE.uproject
echo Project: %PROJECT_PATH%
echo.

REM Build the project
echo Step 1: Building SubspaceUE...
echo This may take 2-5 minutes on first build...
echo.
"%UE_BUILD%" SubspaceUEEditor Win64 Development -Project="%PROJECT_PATH%" -WaitMutex

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed! Check the output above for errors.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo ========================================
echo ✅ Build successful!
echo ========================================
echo.

REM Launch the editor
echo Step 2: Launching Unreal Editor...
echo.
echo Once the editor opens:
echo   1. Navigate to Content/Maps in Content Browser
echo   2. Create a new Empty Level named "SpaceLevel" (if not exists)
echo   3. Press Play (Alt+P)
echo   4. Fly with WASD!
echo.
pause

"%UE_EDITOR%" "%PROJECT_PATH%"

echo.
echo Editor closed.
pause
