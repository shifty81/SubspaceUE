# build-project.ps1 - Automated build script for SubspaceUE
# This script follows the documented build process from docs/COMPLETE_SETUP_GUIDE.md

$ErrorActionPreference = "Stop"

# Configuration
$ProjectName = "SubspaceUE"
$UProjectFile = "$ProjectName.uproject"
$BuildConfig = if ($env:BUILD_CONFIG) { $env:BUILD_CONFIG } else { "Development" }
$BuildPlatform = if ($env:BUILD_PLATFORM) { $env:BUILD_PLATFORM } else { "Win64" }

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  SubspaceUE - Automated Build Script" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

Write-Host "Build Configuration: $BuildConfig" -ForegroundColor Yellow
Write-Host "Build Platform: $BuildPlatform" -ForegroundColor Yellow
Write-Host ""

# Function to find Unreal Engine
function Find-UnrealEngine {
    Write-Host "Looking for Unreal Engine installation..." -ForegroundColor Yellow
    
    # Common UE5 installation paths
    $UEPaths = @(
        "C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles",
        "C:\Program Files\Epic Games\UE_5.6\Engine\Build\BatchFiles",
        "$env:ProgramFiles\Epic Games\UE_5.7\Engine\Build\BatchFiles",
        "$env:ProgramFiles\Epic Games\UE_5.6\Engine\Build\BatchFiles"
    )
    
    foreach ($UEPath in $UEPaths) {
        if (Test-Path $UEPath) {
            Write-Host "✓ Found Unreal Engine at: $UEPath" -ForegroundColor Green
            return (Split-Path (Split-Path $UEPath -Parent) -Parent)
        }
    }
    
    # Check registry
    $RegPaths = @(
        "HKLM:\SOFTWARE\EpicGames\Unreal Engine\5.7",
        "HKLM:\SOFTWARE\EpicGames\Unreal Engine\5.6"
    )
    
    foreach ($RegPath in $RegPaths) {
        if (Test-Path $RegPath) {
            $InstallDir = (Get-ItemProperty -Path $RegPath -Name "InstalledDirectory" -ErrorAction SilentlyContinue).InstalledDirectory
            if ($InstallDir -and (Test-Path $InstallDir)) {
                Write-Host "✓ Found Unreal Engine in registry: $InstallDir" -ForegroundColor Green
                return $InstallDir
            }
        }
    }
    
    Write-Host "✗ Unreal Engine not found!" -ForegroundColor Red
    Write-Host "Please install Unreal Engine 5.6 or 5.7" -ForegroundColor Yellow
    Write-Host "Or set UE_ROOT environment variable" -ForegroundColor Yellow
    return $null
}

# Check if project file exists
if (-not (Test-Path $UProjectFile)) {
    Write-Host "✗ Error: $UProjectFile not found!" -ForegroundColor Red
    Write-Host "Please run this script from the project root directory." -ForegroundColor Yellow
    exit 1
}

Write-Host "✓ Found project file: $UProjectFile" -ForegroundColor Green
Write-Host ""

# Find Unreal Engine if UE_ROOT not set
if (-not $env:UE_ROOT) {
    $env:UE_ROOT = Find-UnrealEngine
    if (-not $env:UE_ROOT) {
        exit 1
    }
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  Building Project" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Build script path
$BuildScript = Join-Path $env:UE_ROOT "Engine\Build\BatchFiles\Build.bat"

# Check if build script exists
if (-not (Test-Path $BuildScript)) {
    Write-Host "✗ Build script not found: $BuildScript" -ForegroundColor Red
    exit 1
}

Write-Host "Using build script: $BuildScript" -ForegroundColor Yellow
Write-Host ""

# Build the project
Write-Host "Building ${ProjectName}Editor $BuildConfig $BuildPlatform..." -ForegroundColor Yellow
$ProjectPath = Join-Path $PWD $UProjectFile

try {
    & $BuildScript "${ProjectName}Editor" $BuildPlatform $BuildConfig -project="$ProjectPath" -progress
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host ""
        Write-Host "✓ Build completed successfully!" -ForegroundColor Green
        Write-Host ""
        Write-Host "========================================" -ForegroundColor Cyan
        Write-Host "  Build Complete!" -ForegroundColor Green
        Write-Host "========================================" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "Next steps:" -ForegroundColor Yellow
        Write-Host "  1. Open $UProjectFile in Unreal Engine"
        Write-Host "  2. See docs/COMPLETE_SETUP_GUIDE.md for more information"
        Write-Host "  3. See docs/QUICKSTART.md for quick start guide"
        Write-Host ""
    } else {
        throw "Build failed with exit code $LASTEXITCODE"
    }
} catch {
    Write-Host ""
    Write-Host "✗ Build failed!" -ForegroundColor Red
    Write-Host "Error: $_" -ForegroundColor Red
    Write-Host "Check the error messages above for details." -ForegroundColor Yellow
    Write-Host "See docs/COMPLETE_SETUP_GUIDE.md for troubleshooting." -ForegroundColor Yellow
    exit 1
}
