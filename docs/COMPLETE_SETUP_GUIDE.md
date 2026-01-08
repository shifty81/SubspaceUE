# Complete Project Setup Guide

> **🎯 Goal:** Get SubspaceUE fully set up and running on your machine from scratch  
> **⏱️ Time Required:** 2-4 hours depending on your experience  
> **👤 Audience:** Anyone setting up SubspaceUE for the first time

---

## 📋 Table of Contents

1. [Overview](#overview)
2. [Prerequisites](#prerequisites)
3. [System Requirements](#system-requirements)
4. [Installation Steps](#installation-steps)
5. [Project Setup](#project-setup)
6. [First Run](#first-run)
7. [Verification](#verification)
8. [Next Steps](#next-steps)
9. [Troubleshooting](#troubleshooting)

---

## 🎯 Overview

This guide will walk you through **every step** needed to set up SubspaceUE from a fresh system to a fully functional development environment. We'll cover:

- ✅ Installing all prerequisites
- ✅ Setting up Unreal Engine 5.7
- ✅ Cloning and configuring the project
- ✅ Importing required assets
- ✅ Running your first build
- ✅ Verifying everything works

### What You'll Have When Done

By the end of this guide, you'll have:

- 🎮 Fully functional SubspaceUE project
- 🚀 Ability to create and test space scenes
- 🛠️ Modular ship system ready to use
- 🌌 Procedural galaxy generation working
- 📊 All documentation accessible

---

## 📦 Prerequisites

### Required Software

Before starting, you need these installed:

#### 1. **Epic Games Launcher** (Required)

**What it is:** The platform for downloading and managing Unreal Engine

**Download:** https://www.epicgames.com/store/en-US/download

**Installation Steps:**
1. Download the Epic Games Launcher installer
2. Run the installer
3. Sign in or create an Epic Games account
4. Complete the installation

**Verification:**
```bash
# Open Epic Games Launcher
# You should see the launcher window open
```

✅ **Success Indicator:** Epic Games Launcher opens and you can sign in

---

#### 2. **Unreal Engine 5.7** (Required)

**What it is:** The game engine SubspaceUE is built on

**Installation Steps:**
1. Open Epic Games Launcher
2. Go to the **Unreal Engine** tab (left sidebar)
3. Click **Library** at the top
4. Click the **+** button next to "ENGINE VERSIONS"
5. Select version **5.7** (or latest 5.7.x)
6. Click **Install**
7. Choose installation location (requires ~50GB space)
8. Wait for download and installation (30-60 minutes)

**Installation Location:**
- Windows: `C:\Program Files\Epic Games\UE_5.7\`
- Mac: `/Users/Shared/Epic Games/UE_5.7/`

**Verification:**
```bash
# Windows
cd "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64"
dir UnrealEditor.exe

# Mac
cd "/Users/Shared/Epic Games/UE_5.7/Engine/Binaries/Mac"
ls UnrealEditor
```

✅ **Success Indicator:** UnrealEditor executable exists

---

#### 3. **Visual Studio 2022** (Required for Windows)

**What it is:** IDE and compiler for C++ code in Unreal Engine

**Download:** https://visualstudio.microsoft.com/vs/community/

**Installation Steps:**
1. Download Visual Studio 2022 Community (free)
2. Run the installer
3. Select these workloads:
   - ✅ **Game development with C++**
   - ✅ **.NET desktop development** (optional, but recommended)
4. Under "Individual components", ensure these are selected:
   - ✅ Windows 10/11 SDK (latest version)
   - ✅ C++ profiling tools
   - ✅ C++ AddressSanitizer
5. Click Install (requires ~15-30GB)
6. Wait for installation (30-60 minutes)

**Verification:**
```bash
# Open Developer Command Prompt for VS 2022
cl
# Should show Microsoft C/C++ Compiler version
```

✅ **Success Indicator:** Can run `cl` command and see compiler version

---

#### 4. **Git** (Required)

**What it is:** Version control system for cloning the repository

**Download:** https://git-scm.com/downloads

**Installation Steps:**
1. Download Git for your OS
2. Run the installer
3. Use default settings (recommended)
4. Complete installation

**Verification:**
```bash
git --version
# Should show: git version 2.x.x
```

✅ **Success Indicator:** Git version displays

---

#### 5. **.NET 9.0 SDK** (Optional - for C# tools)

**What it is:** Runtime for C# scripts and tools

**Download:** https://dotnet.microsoft.com/download

**Installation Steps:**
1. Download .NET 9.0 SDK
2. Run the installer
3. Complete installation
4. Restart terminal/command prompt

**Verification:**
```bash
dotnet --version
# Should show: 9.0.x
```

✅ **Success Indicator:** .NET version displays

---

### Recommended Software

These are optional but highly recommended:

#### **Visual Studio Code** (Recommended)
- Great for editing markdown, JSON, and scripts
- Download: https://code.visualstudio.com/

#### **GitHub Desktop** (Recommended)
- Easier Git management if you're not comfortable with command line
- Download: https://desktop.github.com/

---

## 💻 System Requirements

### Minimum Requirements

| Component | Minimum | Recommended |
|-----------|---------|-------------|
| **OS** | Windows 10 64-bit | Windows 11 64-bit |
| **CPU** | Quad-core Intel/AMD, 2.5 GHz+ | 8-core Intel/AMD, 3.0 GHz+ |
| **RAM** | 16 GB | 32 GB or more |
| **GPU** | DirectX 11/12 compatible, 4GB VRAM | NVIDIA RTX 3060 or better |
| **Storage** | 100 GB free space (SSD) | 200 GB+ free space (NVMe SSD) |
| **Internet** | Required for downloads | High-speed recommended |

### Disk Space Breakdown

- Unreal Engine 5.7: ~50 GB
- Visual Studio 2022: ~15-30 GB
- SubspaceUE Project: ~5-10 GB
- Project Build Cache: ~10-20 GB
- Assets (if downloaded): ~5-15 GB
- **Total:** ~85-125 GB

### Performance Notes

- **SSD highly recommended** - Project compile times are 3-5x faster on SSD
- **32GB RAM recommended** - UE5 can use 10-20GB during compilation
- **Dedicated GPU required** - Integrated graphics won't run UE5 editor well

---

## 🚀 Installation Steps

### Step 1: Verify Prerequisites

Before proceeding, verify all prerequisites are installed:

```bash
# Check Git
git --version

# Check .NET (optional)
dotnet --version

# Check Visual Studio (Windows)
# Open "Developer Command Prompt for VS 2022" from Start menu
cl

# Check Unreal Engine
# Open Epic Games Launcher and verify UE 5.7 is installed
```

**Checklist:**
- [ ] Epic Games Launcher installed and signed in
- [ ] Unreal Engine 5.7 installed
- [ ] Visual Studio 2022 installed with Game Development workload
- [ ] Git installed and working
- [ ] .NET 9.0 SDK installed (optional)

---

### Step 2: Clone the Repository

Choose a location for your project. We recommend:
- Windows: `C:\Projects\SubspaceUE\`
- Mac/Linux: `~/Projects/SubspaceUE/`

**Using Git Command Line:**

```bash
# Navigate to your projects folder
cd C:\Projects   # Windows
cd ~/Projects    # Mac/Linux

# Clone the repository
git clone https://github.com/shifty81/SubspaceUE.git

# Navigate into the project
cd SubspaceUE

# Verify the clone
git status
```

**Using GitHub Desktop:**

1. Open GitHub Desktop
2. File → Clone Repository
3. URL tab → Enter: `https://github.com/shifty81/SubspaceUE`
4. Choose local path (e.g., `C:\Projects\SubspaceUE`)
5. Click Clone

✅ **Success Indicator:** You have a `SubspaceUE` folder with files

---

### Step 3: Explore the Project Structure

Let's understand what you have:

```
SubspaceUE/
├── Config/              # Project configuration files
├── Content/             # Game assets, maps, blueprints (created after first open)
├── Source/              # C++ source code (if using C++)
├── Plugins/             # Unreal Engine plugins
├── docs/                # 📚 All documentation (118+ guides)
│   ├── guides/          # Feature guides
│   ├── architecture/    # System architecture
│   ├── implementation/  # Implementation docs
│   └── migration/       # UE5 migration docs
├── SubspaceUE.uproject  # Main project file - DOUBLE CLICK THIS to open
├── README.md            # Project overview
└── QUICKSTART.md        # Quick start guide
```

**Important Files:**
- `SubspaceUE.uproject` - Main project file (open this in UE5)
- `README.md` - Project overview and features
- `docs/` - All documentation (open in browser or VS Code)

---

### Step 4: First Project Open

This is the most important step!

**Method 1: From Epic Games Launcher**

1. Open Epic Games Launcher
2. Go to Unreal Engine → Library
3. Click **Launch** next to Engine 5.7
4. In the Unreal Project Browser:
   - Click **Browse**
   - Navigate to your SubspaceUE folder
   - Select `SubspaceUE.uproject`
   - Click **Open**

**Method 2: Direct File Open**

1. Navigate to your SubspaceUE folder
2. Double-click `SubspaceUE.uproject`
3. If prompted, select Unreal Engine 5.7

**What Happens Next:**

You'll see several dialogs:

1. **"Project file is out of date"** (if shown)
   - Click **Convert in Place** or **More Options → Convert**
   - This updates the project to UE 5.7 format

2. **"Missing Modules"** (if shown)
   - Click **Yes** to rebuild modules
   - This compiles C++ code (takes 5-15 minutes first time)

3. **Progress Bar**
   - "Loading project..."
   - "Compiling shaders..." (can take 10-30 minutes)
   - Be patient! This is normal for first open

4. **Unreal Editor Opens**
   - You'll see the main editor interface
   - May see a default level or empty scene

✅ **Success Indicator:** Unreal Editor opens without errors

**If You Get Errors:** See [Troubleshooting](#troubleshooting) section below

---

### Step 5: Initial Project Configuration

Once the editor is open, let's configure some settings:

#### Enable Required Plugins

1. Edit → Plugins
2. Search for and enable these plugins:
   - ✅ **Geometry Script** (for procedural generation)
   - ✅ **Procedural Mesh Component** (for voxels)
   - ✅ **Niagara** (for VFX)
   - ✅ **Chaos Destruction** (for physics)
3. Click **Restart Now** if prompted

#### Project Settings

1. Edit → Project Settings
2. Configure these settings:

**Maps & Modes:**
- Default Maps → Editor Startup Map: `/Game/Maps/MainMenu`
- Default Maps → Game Default Map: `/Game/Maps/MainMenu`

**Engine - Rendering:**
- Default Settings → Anti-Aliasing Method: `TAA` (Temporal Anti-Aliasing)
- Default Settings → Dynamic Global Illumination Method: `Lumen`
- Default Settings → Reflection Method: `Lumen`

**Engine - Input:**
- Default Input Component Class: `EnhancedInputComponent`
- Default Player Input Class: `EnhancedPlayerInput`

**Physics:**
- Simulation → Default Gravity Z: `-980` (Earth-like gravity)
- Or set to `0` for zero-gravity space (recommended for space game)

3. Click **Save** and close Project Settings

---

### Step 6: Create Your First Level

Let's create a simple space scene to test everything:

1. **Create New Level**
   - File → New Level
   - Select **Empty Level**
   - Click Create

2. **Add Basic Lighting**
   - In the Place Actors panel (Window → Place Actors)
   - Drag **Directional Light** into the viewport
   - Drag **Sky Light** into the viewport
   - Drag **Sky Atmosphere** into the viewport

3. **Add Player Start**
   - Drag **Player Start** into the viewport
   - Position it at (0, 0, 100)

4. **Save the Level**
   - File → Save Current Level As...
   - Name: `TestSpace`
   - Location: `/Game/Maps/`
   - Click Save

5. **Test Play**
   - Click the **Play** button (top toolbar)
   - You should spawn in an empty space
   - Press **ESC** to exit play mode

✅ **Success Indicator:** You can play in the level

---

## ✅ Verification

Let's verify everything is working correctly:

### Checklist

Run through this verification checklist:

- [ ] **Project Opens** - SubspaceUE.uproject opens in UE5 without errors
- [ ] **Editor Loads** - Unreal Editor interface is responsive
- [ ] **Plugins Enabled** - Required plugins are active
- [ ] **Can Create Levels** - You created and saved TestSpace level
- [ ] **Play Mode Works** - Can click Play and enter the level
- [ ] **Content Browser** - Can browse Content folder
- [ ] **Blueprints Compile** - No blueprint compile errors (check Output Log)
- [ ] **Documentation Accessible** - Can open and read docs/ folder

### Run Automated Tests

1. Open **Session Frontend** (Window → Developer Tools → Session Frontend)
2. Go to **Automation** tab
3. Select tests to run:
   - Project.Functional Tests
   - System.Core
4. Click **Start Tests**
5. Wait for results (green = pass, red = fail)

### Check for Warnings/Errors

1. Open **Output Log** (Window → Developer Tools → Output Log)
2. Look for any errors (red text)
3. Warnings (yellow) are usually okay
4. Errors need to be addressed

---

## 🎯 Next Steps

Congratulations! Your SubspaceUE project is set up. Here's what to do next:

### Immediate Next Steps

1. **📖 Read the Quick Start Guide**
   - [Quick Start Guide](QUICKSTART.md)
   - Learn basic controls and navigation

2. **🌌 Create Your First Space Scene**
   - [Space Scene Generation Guide](SPACE_SCENE_GENERATION_WITH_STORE_ASSETS.md)
   - Build a beautiful space environment

3. **🚀 Build Your First Ship**
   - [Modular Ship System Guide](guides/MODULAR_SHIP_SYSTEM_GUIDE.md)
   - Create a modular spaceship

### Learning Paths

Choose your path based on interests:

**🎨 Visual/Environment Artist:**
1. [Space Scene Generation](SPACE_SCENE_GENERATION_WITH_STORE_ASSETS.md)
2. [Skybox Material Guide](SKYBOX_MATERIAL_GUIDE.md)
3. [Camera & Visual Improvements](CAMERA_AND_VISUAL_IMPROVEMENTS.md)

**🛠️ Technical Artist/Builder:**
1. [Modular Ship System](guides/MODULAR_SHIP_SYSTEM_GUIDE.md)
2. [Ship Interior Generation](SHIP_INTERIOR_GENERATION_GUIDE.md)
3. [Procedural Generation Guide](guides/PROCEDURAL_GENERATION_GUIDE.md)

**💻 Programmer/Developer:**
1. [System Architecture](architecture/ARCHITECTURE.md)
2. [UE5 Migration Checklist](migration/UE5_MIGRATION_CHECKLIST.md)
3. [Contributing Guide](CONTRIBUTING.md)

**🎮 Game Designer:**
1. [Core Gameplay Mechanics](guides/CORE_GAMEPLAY_MECHANICS.md)
2. [Quest System Guide](guides/QUEST_SYSTEM_GUIDE.md)
3. [AI System Guide](guides/AI_SYSTEM_GUIDE.md)

---

## 🔧 Troubleshooting

### Common Issues and Solutions

#### Issue: "Missing Modules" Error

**Symptoms:** Error when opening project about missing modules

**Solutions:**
1. Click **Yes** when asked to rebuild
2. Wait for compilation (5-15 minutes)
3. If fails:
   ```bash
   # Close Unreal Editor
   # Delete Intermediate, Binaries, Saved folders
   # Right-click SubspaceUE.uproject → Generate Visual Studio project files
   # Open SubspaceUE.sln in Visual Studio → Build → Build Solution
   ```

---

#### Issue: "Failed to Compile Shaders"

**Symptoms:** Long shader compilation, then errors

**Solutions:**
1. Be patient - first compile takes 10-30 minutes
2. Ensure GPU drivers are up to date
3. Check disk space (need 20GB+ free)
4. If still fails:
   - Delete `Saved/ShaderDebugInfo/` folder
   - Restart editor

---

#### Issue: "Out of Video Memory"

**Symptoms:** Crash with "out of video memory" error

**Solutions:**
1. Lower editor preview quality:
   - Settings → Editor Preferences → General → Performance
   - Set Real Time Preview Quality to Low
2. Close other GPU-intensive applications
3. Reduce viewport resolution
4. Upgrade GPU if possible (4GB VRAM minimum, 8GB recommended)

---

#### Issue: "Project Failed to Open"

**Symptoms:** Project won't open, immediate crash

**Solutions:**
1. Verify Unreal Engine 5.7 is installed correctly
2. Run Epic Games Launcher → Library → Verify (next to UE 5.7)
3. Check Windows Event Viewer for crash details
4. Try creating a blank UE5 project first to verify engine works

---

#### Issue: "Git Clone Failed"

**Symptoms:** Error when cloning repository

**Solutions:**
```bash
# Ensure Git is installed
git --version

# Try with verbose output
git clone https://github.com/shifty81/SubspaceUE.git --verbose

# Or use HTTPS instead of SSH
git clone https://github.com/shifty81/SubspaceUE.git

# Check internet connection and GitHub status
```

---

#### Issue: "Visual Studio Not Found"

**Symptoms:** Can't compile C++ code, VS not detected

**Solutions:**
1. Verify Visual Studio 2022 is installed
2. Ensure "Game Development with C++" workload is installed
3. In Unreal Editor:
   - Edit → Editor Preferences → Source Code
   - Source Code Editor: Visual Studio 2022
4. Restart editor

---

#### Issue: "Slow Performance in Editor"

**Symptoms:** Editor is laggy, low FPS

**Solutions:**
1. Lower editor settings:
   - Settings → Editor Preferences → General → Performance
   - Disable Real-Time in viewport (Ctrl+R)
   - Lower Engine Scalability Settings (Settings toolbar button)
2. Close unnecessary browser tabs/applications
3. Check Task Manager - close memory hogs
4. Ensure running on dedicated GPU, not integrated

---

### Getting More Help

If you're still stuck:

1. **Check Documentation**
   - [Sol Troubleshooting Guide](SOL_TESTINGGROUNDS_TROUBLESHOOTING.md) - Comprehensive troubleshooting
   - [Documentation Index](DOCUMENTATION_INDEX.md) - All guides

2. **Search Existing Issues**
   - GitHub Issues: https://github.com/shifty81/SubspaceUE/issues
   - Unreal Engine Forums: https://forums.unrealengine.com/

3. **Ask for Help**
   - Open a GitHub Issue with:
     - Your OS and version
     - Unreal Engine version
     - Full error message
     - Steps to reproduce
     - What you've already tried

4. **Unreal Engine Documentation**
   - Official UE5 Docs: https://docs.unrealengine.com/5.7/

---

## 📊 Setup Summary

By completing this guide, you have:

✅ Installed all required software (Epic Launcher, UE5.7, VS2022, Git)  
✅ Cloned the SubspaceUE repository  
✅ Opened the project in Unreal Engine  
✅ Configured essential project settings  
✅ Created and tested a simple level  
✅ Verified everything is working  
✅ Know where to go next

---

## 🎓 Estimated Time Spent

- Prerequisites installation: 1-2 hours
- Repository clone: 5-10 minutes
- First project open: 20-45 minutes (shader compilation)
- Configuration: 15-30 minutes
- Testing: 10-15 minutes
- **Total: 2-4 hours**

---

## 📚 Related Documentation

- [Quick Start Guide](QUICKSTART.md) - Fast track setup
- [Sol TestingGrounds Guide](SOL_TESTINGGROUNDS_README.md) - Build a complete space sector
- [How to Build & Run](HOW_TO_BUILD_AND_RUN.md) - Alternative setup instructions
- [Contributing Guide](CONTRIBUTING.md) - For contributors
- [Documentation Index](DOCUMENTATION_INDEX.md) - All documentation

---

**🎉 You're all set! Happy building! 🚀**

---

**Navigation:**  
[🏠 Home](docs/README.md) | [📋 Index](DOCUMENTATION_INDEX.md) | [Next: Quick Start →](QUICKSTART.md)
