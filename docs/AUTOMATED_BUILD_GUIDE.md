# Automated Build System Guide

> **🎯 Goal:** Understand and use the automated build system for SubspaceUE  
> **⏱️ Time Required:** 15-30 minutes  
> **👤 Audience:** Developers who want to automate builds

---

## 📋 Table of Contents

1. [Overview](#overview)
2. [Build Scripts](#build-scripts)
3. [Local Builds](#local-builds)
4. [CI/CD Builds](#cicd-builds)
5. [Configuration](#configuration)
6. [Troubleshooting](#troubleshooting)

---

## 🎯 Overview

SubspaceUE now includes a fully automated build system that follows the documented build process from the [Complete Setup Guide](COMPLETE_SETUP_GUIDE.md). This system includes:

- ✅ **Automated build scripts** for local development
- ✅ **GitHub Actions workflows** for CI/CD
- ✅ **Documentation validation** 
- ✅ **Cross-platform support** (Windows, Linux, macOS)

### What Gets Built

The build system handles:

- 🎮 **Unreal Engine C++ Project** - Compiles source code
- 📚 **Documentation** - Validates and deploys documentation
- 🔧 **Build Tools** - Ensures all tools are available

---

## 🔨 Build Scripts

### Available Scripts

| Script | Platform | Description |
|--------|----------|-------------|
| `build-project.sh` | Linux/macOS | Automated build for Unix systems |
| `build-project.ps1` | Windows | Automated build for Windows |
| `serve-docs.sh` | Linux/macOS | Serve documentation locally |
| `serve-docs.bat` | Windows | Serve documentation locally |

---

## 💻 Local Builds

### Prerequisites

Before building locally, ensure you have:

- ✅ **Unreal Engine 5.6 or 5.7** installed
- ✅ **Visual Studio 2022** (Windows) or **Clang** (Linux/macOS)
- ✅ **Git** for version control
- ✅ **50+ GB free disk space**

See [Complete Setup Guide](COMPLETE_SETUP_GUIDE.md) for detailed prerequisites.

### Linux/macOS Build

```bash
# Navigate to project root
cd SubspaceUE

# Run the build script
./build-project.sh

# Or with custom configuration
BUILD_CONFIG=Shipping BUILD_PLATFORM=Linux ./build-project.sh
```

**What it does:**
1. Detects Unreal Engine installation
2. Validates project structure
3. Compiles C++ source code
4. Reports build status

**Build Configurations:**
- `Development` - Default, includes debug symbols
- `Shipping` - Optimized for release
- `DebugGame` - Debug with optimizations

### Windows Build

```powershell
# Navigate to project root
cd SubspaceUE

# Run the build script
.\build-project.ps1

# Or with custom configuration
$env:BUILD_CONFIG="Shipping"
$env:BUILD_PLATFORM="Win64"
.\build-project.ps1
```

### Build Output

Successful builds will output:

```
========================================
  Build Complete!
========================================

Next steps:
  1. Open SubspaceUE.uproject in Unreal Engine
  2. See docs/COMPLETE_SETUP_GUIDE.md for more information
  3. See docs/QUICKSTART.md for quick start guide
```

### Build Artifacts

Build artifacts are located in:

```
SubspaceUE/
├── Binaries/           # Compiled binaries
│   └── Linux/          # Platform-specific binaries
│       └── SubspaceUE  # Main executable
├── Intermediate/       # Build intermediate files
└── Saved/              # Saved data and logs
```

---

## 🔄 CI/CD Builds

### GitHub Actions Workflows

The project includes two GitHub Actions workflows:

#### 1. Build Project Workflow

**File:** `.github/workflows/build-project.yml`

**Triggers:**
- Push to `main`, `master`, or `develop` branches
- Pull requests to main branches
- Manual dispatch via GitHub Actions UI

**Jobs:**
1. **build-linux** - Validates project structure
2. **validate-docs** - Validates documentation and build scripts

**What it validates:**
- ✅ Project structure (`.uproject`, `Source/`, `Config/`)
- ✅ Documentation files exist
- ✅ Build scripts are present and executable
- ✅ Documentation server works

#### 2. Deploy Documentation Workflow

**File:** `.github/workflows/deploy-docs.yml`

**Triggers:**
- Push to `main` or `master` branches (docs changes)
- Manual dispatch

**What it does:**
- Deploys documentation to GitHub Pages
- Makes docs available at `https://shifty81.github.io/SubspaceUE/`

### Viewing Build Status

Check build status:
1. Go to GitHub repository
2. Click **Actions** tab
3. View recent workflow runs

### Manual Workflow Trigger

To manually trigger a build:

1. Go to **Actions** tab on GitHub
2. Select **Build SubspaceUE Project**
3. Click **Run workflow**
4. Choose configuration:
   - Build configuration (Development/Shipping/DebugGame)
   - Build platform (Linux/Win64/Mac)
5. Click **Run workflow**

---

## ⚙️ Configuration

### Environment Variables

Configure builds using environment variables:

| Variable | Default | Description |
|----------|---------|-------------|
| `BUILD_CONFIG` | `Development` | Build configuration |
| `BUILD_PLATFORM` | `Linux` or `Win64` | Target platform |
| `UE_ROOT` | Auto-detected | Unreal Engine root path |

**Example:**

```bash
# Linux/macOS
export BUILD_CONFIG=Shipping
export UE_ROOT=/opt/UnrealEngine
./build-project.sh

# Windows PowerShell
$env:BUILD_CONFIG="Shipping"
$env:UE_ROOT="C:\Program Files\Epic Games\UE_5.7"
.\build-project.ps1
```

### Unreal Engine Paths

The build scripts automatically search for Unreal Engine in:

**Linux:**
- `$HOME/UnrealEngine`
- `/usr/local/UnrealEngine`
- `/opt/UnrealEngine`
- `$HOME/.local/share/Epic/UnrealEngine`

**Windows:**
- `C:\Program Files\Epic Games\UE_5.7`
- `C:\Program Files\Epic Games\UE_5.6`
- Registry: `HKLM:\SOFTWARE\EpicGames\Unreal Engine\5.7`

**macOS:**
- `/Users/Shared/Epic Games/UE_5.7`
- `/Users/Shared/Epic Games/UE_5.6`

### Custom Unreal Engine Path

If Unreal Engine is installed in a custom location:

```bash
# Set UE_ROOT before running build script
export UE_ROOT=/path/to/UnrealEngine
./build-project.sh
```

---

## 🔧 Troubleshooting

### Common Issues

#### 1. "Unreal Engine not found"

**Problem:** Build script can't find Unreal Engine

**Solution:**
```bash
# Set UE_ROOT environment variable
export UE_ROOT=/path/to/UnrealEngine
./build-project.sh
```

Or install Unreal Engine to a standard location.

#### 2. "Project file not found"

**Problem:** Script not run from project root

**Solution:**
```bash
# Navigate to project root
cd /path/to/SubspaceUE
./build-project.sh
```

#### 3. "Build failed with errors"

**Problem:** Compilation errors in C++ code

**Solution:**
1. Check error messages in build output
2. Ensure all dependencies are installed
3. See [Complete Setup Guide](COMPLETE_SETUP_GUIDE.md) for prerequisites
4. Check [Troubleshooting](COMPLETE_SETUP_GUIDE.md#troubleshooting) section

#### 4. "Missing modules"

**Problem:** C++ modules need rebuilding

**Solution:**
```bash
# Clean intermediate files
rm -rf Binaries/ Intermediate/

# Rebuild
./build-project.sh
```

#### 5. GitHub Actions build fails

**Problem:** CI/CD build validation fails

**Solution:**
1. Check workflow run logs on GitHub
2. Ensure all required files are committed:
   - `SubspaceUE.uproject`
   - `Source/` directory
   - `Config/` directory
   - `docs/` directory
3. Validate locally first

### Build Logs

Build logs are located:

**Local builds:**
- Console output
- `Saved/Logs/` directory

**GitHub Actions:**
- Actions tab → Select workflow run → View logs

### Getting Help

If you encounter issues:

1. **Check Documentation:**
   - [Complete Setup Guide](COMPLETE_SETUP_GUIDE.md)
   - [Quick Start](QUICKSTART.md)
   - [Troubleshooting](SOL_TESTINGGROUNDS_TROUBLESHOOTING.md)

2. **GitHub Issues:**
   - Create an issue with:
     - Error message
     - Build log
     - System information
     - Steps to reproduce

3. **Community:**
   - Check existing GitHub Issues
   - Ask in GitHub Discussions

---

## 📚 Related Documentation

- [Complete Setup Guide](COMPLETE_SETUP_GUIDE.md) - Full setup instructions
- [Quick Start](QUICKSTART.md) - Get started quickly
- [How to Build & Run](HOW_TO_BUILD_AND_RUN.md) - Manual build process
- [Documentation Generation](DOCUMENTATION_GENERATION.md) - Documentation system

---

## 🎯 Quick Reference

### Build Commands

```bash
# Local build (Linux/macOS)
./build-project.sh

# Local build (Windows)
.\build-project.ps1

# Custom configuration
BUILD_CONFIG=Shipping ./build-project.sh

# Serve documentation
./serve-docs.sh
```

### Workflow Files

- `.github/workflows/build-project.yml` - Build validation
- `.github/workflows/deploy-docs.yml` - Documentation deployment

### Key Files

- `build-project.sh` - Linux/macOS build script
- `build-project.ps1` - Windows build script
- `SubspaceUE.uproject` - Main project file
- `Source/` - C++ source code
- `docs/` - Documentation

---

**Navigation:**  
[🏠 Home](README.md) | [📋 Index](DOCUMENTATION_INDEX.md) | [🚀 Quick Start](QUICKSTART.md) | [🔧 Setup Guide](COMPLETE_SETUP_GUIDE.md)
