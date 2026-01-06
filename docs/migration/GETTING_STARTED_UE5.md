# Getting Started with SubspaceUE in Unreal Engine 5.7

This quick start guide will help you set up and run the SubspaceUE project for the first time.

## 📋 Prerequisites Checklist

Before you begin, make sure you have:

- [ ] **Unreal Engine 5.7** installed from Epic Games Launcher
- [ ] **Visual Studio 2022** (Community Edition or higher) with:
  - [x] Workload: "Game development with C++"
  - [x] Component: "Unreal Engine installer"
  - [x] Component: "C++ profiling tools"
- [ ] **At least 16GB RAM** (32GB recommended)
- [ ] **150GB free disk space** (for UE5 + project)
- [ ] **Windows 10/11 64-bit** (or Linux with UE5 compiled from source)

## 🚀 First Time Setup (30-60 minutes)

### Step 1: Clone the Repository

```bash
git clone https://github.com/shifty81/SubspaceUE.git
cd SubspaceUE
```

### Step 2: Generate Project Files

**Option A: Right-click Method (Recommended)**
1. Right-click on `SubspaceUE.uproject` in Windows Explorer
2. Select **"Generate Visual Studio project files"**
3. Wait for generation to complete (1-2 minutes)

**Option B: Command Line**
```bash
"C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" -projectfiles -project="%CD%\SubspaceUE.uproject" -game -engine
```

### Step 3: Build the Project

**Option A: Build from Unreal Editor (Easiest)**
1. Double-click `SubspaceUE.uproject`
2. If prompted to rebuild modules, click **"Yes"**
3. Wait for initial compile (5-15 minutes first time)
4. Editor will open when complete

**Option B: Build from Visual Studio**
1. Open `SubspaceUE.sln` in Visual Studio 2022
2. Set build configuration to **"Development Editor"**
3. Build → Build Solution (or press Ctrl+Shift+B)
4. Wait for compilation (5-15 minutes first time)
5. Press F5 to launch editor

### Step 4: Verify Installation

Once the editor opens:
1. Check the Output Log (Window → Developer Tools → Output Log)
2. You should see: `"SubspaceUE Module: Initialization complete"`
3. Look for any errors in red - if none, you're good to go!

## 🎮 Running the Game

### Play in Editor (PIE)

1. **Open a test level** (we'll create one in next steps)
2. **Click Play button** (or press Alt+P)
3. **Test controls:**
   - W/S - Forward/Backward
   - A/D - Strafe Left/Right
   - Space/Ctrl - Up/Down
   - Arrow Keys - Rotation
   - X - Emergency Brake

### Standalone Game

1. Click dropdown next to Play button
2. Select **"Standalone Game"**
3. Click Play

## 🏗️ Current Project State

### ✅ What Works Now

- **Core C++ classes** are implemented:
  - SubspaceGameMode (game logic)
  - SubspacePlayerPawn (spaceship with physics)
  - SubspacePlayerController (input handling)
  - SubspaceGameInstance (persistent data)

- **6DOF Physics** - Basic Newtonian ship movement
- **Project structure** - Proper UE5 module setup
- **Configuration** - Engine and game settings configured

### 🚧 What's In Progress

- **Voxel System** - For ship construction (HIGH PRIORITY)
- **UI Widgets** - HUD, menus, inventory (HIGH PRIORITY)
- **Procedural Generation** - Galaxy, asteroids, ships
- **AI System** - AI controllers and behavior trees
- **Content** - 3D models, materials, textures

## 📝 Next Steps for Development

### For Programmers

1. **Implement Voxel System**
   ```cpp
   // TODO: Create UVoxelComponent in Source/SubspaceUE/Public/Components/
   // See CONVERSION_GUIDE.md for implementation details
   ```

2. **Add Component Classes**
   - File → New C++ Class → Actor Component
   - Examples: ShipInventoryComponent, WeaponComponent, ShieldComponent

3. **Extend Game Classes**
   - Add functionality to SubspaceGameMode
   - Implement more input actions in SubspacePlayerController
   - Create AI enemy ship classes

### For Artists/Designers

1. **Create Test Level**
   - File → New Level → Empty Level
   - Save as `Content/Maps/TestLevel`
   - Add lighting (Directional Light, Skylight)
   - Add player start

2. **Import 3D Models**
   - Content Browser → Import
   - Drag FBX files for ships, asteroids, stations
   - Create materials for each mesh

3. **Create Widgets**
   - Content Browser → User Interface → Widget Blueprint
   - Design HUD, inventory, ship builder UI
   - Bind to C++ functions via Blueprint

### For Scripters

1. **Create Blueprint Classes**
   - Inherit from C++ classes (e.g., BP_PlayerShip from SubspacePlayerPawn)
   - Add visual scripting for gameplay logic
   - Configure ship stats, weapons, etc.

2. **Set Up Input**
   - Project Settings → Input → Action Mappings
   - Bind keys to actions (MoveForward, MoveRight, etc.)
   - Or use Enhanced Input system (UE5.7 recommended)

## 🐛 Common Issues & Solutions

### Issue: "Module 'SubspaceUE' could not be loaded"

**Solution:**
1. Close Unreal Editor
2. Delete `Binaries/`, `Intermediate/`, and `Saved/` folders
3. Right-click `.uproject` → Generate Visual Studio project files
4. Open `SubspaceUE.sln` and rebuild (Build → Build Solution)
5. Launch editor

### Issue: "Visual Studio project files are out of date"

**Solution:**
- Right-click `.uproject` → Generate Visual Studio project files
- Rebuild in Visual Studio

### Issue: Editor crashes on startup

**Solution:**
1. Check `Saved/Logs/SubspaceUE.log` for error details
2. Verify GPU drivers are up to date
3. Try disabling plugins in `.uproject` file
4. Delete `Saved/` folder and try again

### Issue: Slow compilation times

**Solution:**
- Use **Live Coding** instead of full rebuild: Ctrl+Alt+F11
- Use **Hot Reload** for small changes: Click "Compile" in editor
- Close other applications to free up RAM
- Consider upgrading to an SSD if using HDD

## 📚 Learning Resources

### Essential UE5 Documentation
- [Unreal Engine 5.7 Overview](https://docs.unrealengine.com/5.7/)
- [C++ Programming Guide](https://docs.unrealengine.com/5.7/en-US/programming-with-cplusplus-in-unreal-engine/)
- [Gameplay Framework](https://docs.unrealengine.com/5.7/en-US/gameplay-framework-in-unreal-engine/)
- [Actor Components](https://docs.unrealengine.com/5.7/en-US/components-in-unreal-engine/)

### Video Tutorials
- [Unreal Engine 5 C++ Tutorial Series](https://www.youtube.com/unrealengine) (Official)
- [Space Game Development in UE5](https://www.youtube.com/) (Community)

### Project Documentation
- **README_UE5.md** - Comprehensive project overview
- **CONVERSION_GUIDE.md** - Detailed system conversion guide
- Original C# docs in root directory (for reference)

## 🤝 Contributing

Want to help with the conversion? Here's how:

1. **Fork the repository**
2. **Pick a task** from CONVERSION_GUIDE.md
3. **Create a branch**: `git checkout -b feature/voxel-system`
4. **Make your changes**
5. **Test thoroughly**
6. **Submit a pull request**

### Good First Tasks
- [ ] Create test level with player start and lighting
- [ ] Import basic ship model and set up materials
- [ ] Create simple HUD widget blueprint
- [ ] Implement inventory component
- [ ] Add sound effects for ship thrust/weapons

## 💬 Getting Help

- **GitHub Issues**: [Report bugs or request features](https://github.com/shifty81/SubspaceUE/issues)
- **GitHub Discussions**: [Ask questions, share ideas](https://github.com/shifty81/SubspaceUE/discussions)
- **Discord**: Join Unreal Slackers for general UE5 help

## ✅ Progress Checklist

Track your setup progress:

- [ ] Unreal Engine 5.7 installed
- [ ] Visual Studio 2022 installed with correct workloads
- [ ] Repository cloned
- [ ] Project files generated
- [ ] Project compiled successfully
- [ ] Editor opens without errors
- [ ] Reviewed project structure
- [ ] Read CONVERSION_GUIDE.md
- [ ] Explored Source/ directory
- [ ] Created first test level
- [ ] Tested player pawn in PIE
- [ ] Ready to contribute!

---

**Welcome to SubspaceUE!** 🚀

This project is converting a full-featured C# space game engine to Unreal Engine 5.7. It's a significant undertaking, and we're building it piece by piece. Your contributions, whether code, art, or documentation, are invaluable!

**Questions?** Check the docs, open an issue, or join the discussion. Happy developing!
