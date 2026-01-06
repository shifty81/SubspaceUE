# SubspaceUE Setup Checklist

Use this checklist to verify your setup is complete and working.

## Pre-Flight Checklist

### ✅ Prerequisites
- [ ] Unreal Engine 5.6 installed
- [ ] Visual Studio 2022 with C++ workload (Windows) or Xcode (Mac)
- [ ] Project files downloaded/cloned
- [ ] At least 4GB free disk space

### ✅ Project Setup
- [ ] Generated Visual Studio project files (right-click .uproject)
- [ ] Successfully compiled the project (no errors)
- [ ] Unreal Editor opens without errors

### ✅ Content Setup
- [ ] Content/Maps directory exists
- [ ] SpaceLevel.umap created (Empty Level)
- [ ] SpaceLevel saved successfully

### ✅ Configuration Verification
Open the project and verify:

#### Input Settings (Edit → Project Settings → Input)
- [ ] "MoveForward" axis mapping exists (W=1.0, S=-1.0)
- [ ] "MoveRight" axis mapping exists (D=1.0, A=-1.0)
- [ ] "MoveUp" axis mapping exists (Space=1.0, Shift=-1.0)
- [ ] "Pitch" axis mapping exists (Up=1.0, Down=-1.0)
- [ ] "Yaw" axis mapping exists (Right=1.0, Left=-1.0)
- [ ] "Roll" axis mapping exists (E=1.0, Q=-1.0)
- [ ] "Brake" action mapping exists (B key)

#### Map Settings (Edit → Project Settings → Maps & Modes)
- [ ] Game Default Map: /Game/Maps/SpaceLevel
- [ ] Editor Startup Map: /Game/Maps/SpaceLevel
- [ ] Default GameMode: SubspaceGameMode
- [ ] Default Pawn: SubspacePlayerPawn

#### Engine Settings (Edit → Project Settings → Engine)
- [ ] Physics → Default Gravity Z: 0 (set by AutoInitGameActor automatically)

### ✅ Game Systems (Verified on Play)
When you press Play (Alt+P), verify:

- [ ] **Player Ship Spawns**: You see/control a ship
- [ ] **HUD Displays**: Green text showing "CODENAME: SUBSPACE - UE5 Alpha"
- [ ] **Speed Display**: Shows "Speed: X m/s"
- [ ] **Position Display**: Shows "Position: X=... Y=... Z=..."
- [ ] **Controls Display**: Shows controls at bottom of screen
- [ ] **Crosshair**: Green crosshair in center of screen

#### Output Log Verification (Window → Developer Tools → Output Log)
Look for these messages:
- [ ] "SubspaceGameMode: Initializing game systems..."
- [ ] "SubspaceGameMode: Lighting spawned"
- [ ] "SubspaceGameMode: Galaxy system initialized"
- [ ] "Spawned asteroid at..." (should see ~50 of these)
- [ ] "Spawned AI ship at..." (should see ~5 of these)
- [ ] "SubspacePlayerPawn: Ship initialized"

### ✅ Flight Test
Test all controls:

- [ ] **W key**: Ship moves forward (Speed increases)
- [ ] **S key**: Ship moves backward (Speed increases negative)
- [ ] **A key**: Ship strafes left
- [ ] **D key**: Ship strafes right
- [ ] **Space**: Ship moves up
- [ ] **Shift**: Ship moves down
- [ ] **Up Arrow**: Ship pitches up (nose up)
- [ ] **Down Arrow**: Ship pitches down (nose down)
- [ ] **Left Arrow**: Ship yaws left (turns left)
- [ ] **Right Arrow**: Ship yaws right (turns right)
- [ ] **Q key**: Ship rolls left
- [ ] **E key**: Ship rolls right
- [ ] **B key**: Emergency brake (all velocity stops)

### ✅ Visual Verification
- [ ] Can see asteroids (spheres) in the distance
- [ ] Can see AI ships (spheres) near origin
- [ ] Scene is lit (not completely black)
- [ ] HUD is readable
- [ ] Crosshair is visible

## Troubleshooting Guide

### ❌ Black Screen on Play
**Symptoms**: Screen is completely black, can't see anything  
**Causes**:
1. SpaceLevel map not created
2. Lighting not spawning
3. Camera pointing wrong direction

**Solutions**:
1. ✅ Create SpaceLevel: Content Browser → Maps → New Empty Level → "SpaceLevel"
2. ✅ Check Output Log for "Lighting spawned" message
3. ✅ Press W key to move forward - you might be facing away from objects
4. ✅ Try arrow keys to look around
5. ✅ Manually add: Place Actors → Lights → Directional Light

### ❌ Controls Don't Work
**Symptoms**: Keys don't move the ship  
**Causes**:
1. Input mappings not configured
2. Player pawn not possessed
3. Wrong game mode

**Solutions**:
1. ✅ Verify input settings (see checklist above)
2. ✅ Check Output Log for "SubspacePlayerPawn: Ship initialized"
3. ✅ Project Settings → Maps & Modes → verify SubspaceGameMode

### ❌ No HUD/Text Display
**Symptoms**: Can't see green HUD text  
**Causes**:
1. HUD class not assigned
2. Player controller not spawned

**Solutions**:
1. ✅ Project Settings → Maps & Modes → HUD Class: SubspaceHUD
2. ✅ Check Output Log for errors

### ❌ Compile Errors
**Symptoms**: "Module 'SubspaceUE' could not be loaded"  
**Causes**:
1. C++ compilation failed
2. Missing dependencies

**Solutions**:
1. ✅ Regenerate project files: Right-click .uproject → "Generate Visual Studio project files"
2. ✅ Clean build: Visual Studio → Build → Clean Solution, then Rebuild
3. ✅ Check compiler output for specific errors

### ❌ Can't See Asteroids/Ships
**Symptoms**: Play works but no objects visible  
**Causes**:
1. Objects spawned too far away
2. Meshes not loaded
3. No lighting

**Solutions**:
1. ✅ Fly forward with W key - objects may be distant
2. ✅ Check Output Log for "Spawned asteroid/ship" messages
3. ✅ Verify "Lighting spawned" message in log
4. ✅ Use Scene Outliner to see spawned actors

## Performance Checklist

If the game is running slowly:

- [ ] Reduce asteroid count in SubspaceGameMode::BeginPlay() (default: 50)
- [ ] Reduce AI ship count (default: 5)
- [ ] Check GPU usage with `stat fps` console command
- [ ] Lower editor quality: Settings → Scalability → Low
- [ ] Close other applications

## Next Steps After Verification

Once everything is working:

1. **Improve Visuals**
   - [ ] Add Sky Atmosphere (Place Actors → Visual Effects → Sky Atmosphere)
   - [ ] Import ship models from Assets/Models/ships/
   - [ ] Replace cube ship with proper model

2. **Add Gameplay**
   - [ ] Implement weapons system
   - [ ] Add mining mechanics
   - [ ] Create AI behaviors

3. **Polish**
   - [ ] Add particle effects (engine trails)
   - [ ] Implement sound effects
   - [ ] Create UMG UI widgets

## Success! 🎉

If all checkboxes are marked:
- ✅ Your SubspaceUE installation is complete
- ✅ All systems are functional
- ✅ You're ready to start development
- ✅ Have fun flying in space! 🚀

## Getting Help

Still having issues?

1. Check the detailed guides:
   - [QUICKSTART_UE5.md](QUICKSTART_UE5.md) - Quick setup
   - [SETUP_LEVEL_INSTRUCTIONS.md](SETUP_LEVEL_INSTRUCTIONS.md) - Detailed level setup
   - [CONVERSION_GUIDE.md](CONVERSION_GUIDE.md) - Full technical documentation

2. Use the automation script:
   - Run [create_space_level.py](create_space_level.py) in Unreal's Python console

3. Check GitHub Issues for similar problems

4. Enable verbose logging:
   - Output Log → Settings → Log Categories → Display All

---

**Remember**: The black screen is normal before creating SpaceLevel! That's the only manual step required. Everything else is automated in C++! 🚀
