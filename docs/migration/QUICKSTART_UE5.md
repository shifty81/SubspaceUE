# Quick Start Guide - SubspaceUE

This guide will help you get the SubspaceUE project up and running in **under 5 minutes**.

## Prerequisites

✅ Unreal Engine 5.6 installed  
✅ Visual Studio 2022 with C++ workload (Windows) or Xcode (Mac)  
✅ ~4GB free disk space for project compilation

## Step 1: Generate Project Files (1 minute)

### Windows:
```bash
# Right-click on SubspaceUE.uproject
# Select "Generate Visual Studio project files"
# Or run from command line:
cd /path/to/SubspaceUE
"C:\Program Files\Epic Games\UE_5.6\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="%CD%\SubspaceUE.uproject" -game -rocket -progress
```

### Mac/Linux:
```bash
cd /path/to/SubspaceUE
/path/to/UE_5.6/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh SubspaceUE.uproject
```

## Step 2: Compile the Project (2-3 minutes)

### Option A: Using Visual Studio (Windows)
1. Open `SubspaceUE.sln`
2. Set build configuration to "Development Editor"
3. Press F5 or click Build → Build Solution
4. Wait for compilation to complete

### Option B: Using Unreal Editor
1. Double-click `SubspaceUE.uproject`
2. Unreal will detect missing modules and ask to compile
3. Click "Yes" and wait for compilation

### Option C: Command Line (Any Platform)
```bash
# Windows
"C:\Program Files\Epic Games\UE_5.6\Engine\Build\BatchFiles\Build.bat" SubspaceUEEditor Win64 Development -Project="path\to\SubspaceUE.uproject" -WaitMutex -FromMsBuild

# Mac
/path/to/UE_5.6/Engine/Build/BatchFiles/Mac/Build.sh SubspaceUEEditor Mac Development -Project="path/to/SubspaceUE.uproject"

# Linux
/path/to/UE_5.6/Engine/Build/BatchFiles/Linux/Build.sh SubspaceUEEditor Linux Development -Project="path/to/SubspaceUE.uproject"
```

## Step 3: Create the Space Level (1 minute)

1. Launch Unreal Editor (if not already open)
2. In the **Content Browser**, navigate to **Content/Maps/**
3. Right-click → **Level → Empty Level**
4. Name it **`SpaceLevel`**
5. Double-click to open it
6. **File → Save Current Level**
7. Close the level (the black screen is normal - our code adds lighting!)

**That's it!** The C++ code automatically handles everything else.

## Step 4: Play the Game!

1. Click the **▶ Play** button in the toolbar (or press **Alt+P**)
2. You should now see:
   - ✅ Your ship (blue/gray cube)
   - ✅ Green HUD showing speed, position, controls
   - ✅ Asteroids floating in space (spheres)
   - ✅ AI ships (smaller spheres)
   - ✅ Lighting (sun and ambient)
   - ✅ Crosshair in the center

## Controls

| Action | Key | Gamepad |
|--------|-----|---------|
| Forward/Backward | W / S | Left Stick ↑↓ |
| Strafe Left/Right | A / D | Left Stick ←→ |
| Up/Down | Space / Shift | RB / LB |
| Pitch (Look Up/Down) | ↑ / ↓ | Right Stick ↑↓ |
| Yaw (Look Left/Right) | ← / → | Right Stick ←→ |
| Roll | Q / E | LT / RT |
| Emergency Brake | B | X Button |

## Troubleshooting

### "Black screen when I hit Play"
**Cause:** The SpaceLevel map wasn't created yet.  
**Fix:** Follow Step 3 above to create the map.

### "Can't see anything / Still black screen"
**Possible causes:**
1. ✅ You're facing away from the objects - press **W** to fly forward or use **arrow keys** to look around
2. ✅ The lighting isn't spawning - check the Output Log for "Lighting spawned" message
3. ✅ Try adding a Sky Atmosphere manually: Place Actors → Visual Effects → Sky Atmosphere

### "Controls don't work"
**Fix:** Check that input bindings were applied:
1. Edit → Project Settings → Input
2. Verify "MoveForward", "Pitch", "Yaw", etc. are listed under Axis Mappings
3. If missing, copy them from `Config/DefaultInput.ini`

### "Module 'SubspaceUE' could not be loaded"
**Fix:** The C++ code needs to be compiled:
1. Close Unreal Editor
2. Right-click `SubspaceUE.uproject` → "Generate Visual Studio project files"
3. Open the .sln file and build
4. Relaunch the editor

### "Game crashes on startup"
**Fix:** Check the Output Log (Window → Developer Tools → Output Log) for error messages. Common issues:
- Missing dependencies (all should be included)
- Corrupted project files (regenerate project files)
- Wrong Unreal Engine version (needs 5.6)

## What Happens When You Play?

The game automatically:

1. **Spawns your ship** with 6DOF Newtonian physics
2. **Activates the HUD** showing real-time ship data
3. **Creates lighting** (directional sun + ambient sky light)
4. **Generates 50 asteroids** at random positions
5. **Spawns 5 AI ships** near the origin
6. **Disables gravity** (we're in space!)
7. **Enables full flight controls**

All of this is done in **C++**, no Blueprint setup required!

## Next Steps

### Make It Look Better
1. **Add a space skybox:**
   - Download a free space skybox from the marketplace
   - Or Window → Env. Light Mixer → Create Sky Light + Atmospheric Light

2. **Replace placeholder meshes:**
   - Import ship models from `Assets/Models/ships/`
   - Assign to the player pawn's Ship Mesh in the Details panel

3. **Add engine effects:**
   - Create particle systems for thrusters
   - Add exhaust trails

### Add More Gameplay
1. **Weapons:** Create projectile actors and firing logic
2. **Mining:** Add resource collection from asteroids
3. **AI Behavior:** Implement AI controllers for ships
4. **HUD Enhancements:** Create UMG widgets for inventory, map, etc.

## Performance Tips

- The game spawns 50+ actors by default
- If performance is slow, reduce asteroid count in SubspaceGameMode::BeginPlay()
- Use the console command `stat fps` to show frame rate
- Console: Press **`** (tilde key) or **\\** (backslash)

## Getting Help

- 📖 Full documentation: See `CONVERSION_GUIDE.md`
- 🎮 Detailed level setup: See `SETUP_LEVEL_INSTRUCTIONS.md`
- 🏗️ Architecture overview: See `ARCHITECTURE.md`
- 🐛 For bugs: Check GitHub Issues

---

## Summary: The Absolute Minimum

```bash
1. Generate project files (right-click .uproject)
2. Build the project (F5 in Visual Studio or open in UE editor)
3. Create Content/Maps/SpaceLevel.umap (Empty Level)
4. Press Play (Alt+P)
5. Press W to fly forward!
```

**Total time: ~5 minutes** ⚡

Enjoy your space flight! 🚀✨
