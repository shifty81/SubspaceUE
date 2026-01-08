@echo off
REM serve-docs.bat - Start local documentation server for Windows
REM Usage: serve-docs.bat [port]

setlocal

set PORT=%1
if "%PORT%"=="" set PORT=3000

set DOCS_DIR=docs

echo ================================================
echo  SubspaceUE Documentation Server
echo ================================================
echo.
echo  Starting server on port %PORT%...
echo  Documentation will be available at:
echo.
echo    http://localhost:%PORT%
echo.
echo  Press Ctrl+C to stop the server
echo ================================================
echo.

REM Check if docs directory exists
if not exist "%DOCS_DIR%" (
    echo Error: docs directory not found!
    echo Make sure you run this script from the project root.
    exit /b 1
)

cd "%DOCS_DIR%"

REM Try to start Python server
python --version >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    python -m http.server %PORT%
) else (
    echo Error: Python not found!
    echo Please install Python 3 to use this script.
    echo.
    echo Download from: https://python.org/
    echo.
    echo Alternatives:
    echo   - Use Node.js: npm install -g http-server ^&^& http-server -p %PORT%
    exit /b 1
)
