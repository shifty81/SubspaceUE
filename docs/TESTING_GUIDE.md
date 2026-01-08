# Testing Guide - Ship Visuals and Camera Improvements

This guide explains how to test the new camera and visual improvements in Unreal Engine.

## Prerequisites

- Unreal Engine 5.6 or later installed
- SubspaceUE project opened in Unreal Editor

## Building the Project

### Method 1: Unreal Editor (Recommended)

1. **Open Project**:
   ```
   File → Open Project
   Navigate to SubspaceUE.uproject
   ```

2. **Compile C++ Code**:
   - If Editor prompts to rebuild, click **Yes**
   - Or: `Compile` button in toolbar (hammer icon)
   - Or: Hot Reload (Ctrl+Alt+F11)

3. **Wait for Compilation**:
   - Watch Output Log for errors
   - Should see: "Build succeeded"

### Method 2: Command Line

**Windows:**
```batch
"C:\Program Files\Epic Games\UE_5.6\Engine\Build\BatchFiles\Build.bat" ^
  SubspaceUE Win64 Development ^
  -Project="PATH_TO\SubspaceUE.uproject" ^
  -WaitMutex -FromMsBuild
```

**Linux:**
```bash
/opt/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh \
  SubspaceUE Linux Development \
  -Project="PATH_TO/SubspaceUE.uproject"
```

**macOS:**
```bash
/Applications/UE_5.6/Engine/Build/BatchFiles/Mac/Build.sh \
  SubspaceUE Mac Development \
  -Project="PATH_TO/SubspaceUE.uproject"
```

## Expected Compilation Output

### New Files Compiled
```
Compiling SpaceSkyboxActor.cpp
Compiling SubspacePlayerPawn.cpp (modified)
Compiling SubspaceGameMode.cpp (modified)
```

### Expected Warnings
- None expected (code should compile cleanly)

### If Errors Occur

**Common Issues:**

1. **"Cannot find SpaceSkyboxActor.h"**
   - Check file exists in Source/SubspaceUE/Public/
   - Regenerate project files (right-click .uproject → Generate Visual Studio project files)

2. **Missing PCH (Precompiled Header)**
   - Close Editor
   - Delete Intermediate, Binaries, Saved folders
   - Regenerate project files
   - Rebuild

3. **Linker Errors**
   - Clean solution
   - Rebuild all

## Testing in Editor

### Step 1: Open Test Level

1. Open Unreal Editor
2. Load level: `Content/Maps/SpaceLevel` (or your test level)
3. Make sure level contains game mode setup

### Step 2: Verify Skybox

1. **Check World Outliner**:
   - Look for `SpaceSkyboxActor_0` (spawned by GameMode)
   - Should appear when you hit Play

2. **Inspect Properties** (in Editor, before Play):
   - Place a `SpaceSkyboxActor` manually if needed
   - Details panel should show:
     - SkyboxRadius: 100000
     - StarBrightness: 1.0
     - StarDensity: 0.5
     - bFollowCamera: true

3. **Visual Check**:
   - Large sphere in viewport
   - Should be inverted (showing inside)

### Step 3: Test Ship Visibility

1. **Hit Play (Alt+P)**

2. **Check Ship Mesh**:
   - Should see ship clearly
   - Larger than before (4×8×2 scale)
   - Using cube mesh by default (assign better mesh in Blueprint)

3. **Verify Collision**:
   - Show → Collision
   - Ship should have collision box

### Step 4: Test Camera System

#### Basic Camera Tests

1. **Initial View**:
   - Should start in third-person
   - Camera behind ship at 1000 units
   - Pitched down 15° for good view

2. **Mouse Wheel Zoom**:
   - Scroll UP → Camera zooms in (gets closer)
   - Scroll DOWN → Camera zooms out (gets farther)
   - Min distance: 300 units
   - Max distance: 5000 units

3. **Toggle Camera (V Key)**:
   - Press V → Switch to first-person (cockpit view)
   - Press V again → Back to third-person
   - In first-person, camera arm length = 0

4. **Camera Following**:
   - Move ship around (WASD)
   - Camera should smoothly follow
   - Slight lag for cinematic feel
   - Rotate ship (arrows/mouse)
   - Camera should maintain offset

#### Advanced Camera Tests

1. **Smooth Interpolation**:
   - Apply sudden thrust (W)
   - Camera should ease into position
   - No jarring movements

2. **Camera at Various Distances**:
   - Zoom to min (300): Close-up view
   - Zoom to mid (1000): Default view
   - Zoom to max (5000): Wide strategic view

3. **Camera Pitch**:
   - Should look down at ship slightly
   - Good view of ship top/front
   - Similar to X4: Foundations

### Step 5: Test Physics Improvements

#### Movement Feel Tests

1. **Acceleration**:
   - Press W (forward)
   - Should accelerate smoothly
   - NOT instant max speed
   - Feels weighty (1000kg mass)

2. **Top Speed**:
   - Hold W for several seconds
   - Should reach terminal velocity
   - Speed stabilizes (drag = thrust)
   - Not "super fast" anymore

3. **Drag Effect**:
   - Accelerate to max speed
   - Release W
   - Should gradually slow down
   - Quadratic drag (faster = more drag)

4. **Rotation**:
   - Arrow keys or mouse
   - Smooth angular acceleration
   - Angular drag prevents spinning forever

5. **Emergency Brake**:
   - Press B (brake)
   - All velocity → zero instantly
   - Useful for docking/stopping

#### Physics Value Tests

1. **Check HUD** (if implemented):
   - Velocity display
   - Should show realistic speeds
   - Not thousands of units/second

2. **Compare to Before**:
   - Previous: Very fast, hard to control
   - Now: Controlled, realistic feel
   - Better for combat/navigation

### Step 6: Test Skybox Appearance

#### Visual Tests

1. **Skybox Visibility**:
   - Look around (mouse)
   - Stars everywhere
   - No visible seams

2. **Infinite Distance**:
   - Fly around (WASD + Space/Shift)
   - Skybox always same distance
   - Never get closer to stars

3. **Camera Following**:
   - Skybox center should follow player
   - Check in World Outliner (play mode)
   - Location updates to camera position

#### Material Tests (if assigned)

1. **With Custom Material**:
   - Assign starfield material to SkyboxMaterial
   - Should see stars/nebulae
   - Test brightness parameter

2. **Without Material**:
   - Default grey sphere
   - Check logs for warning message

### Step 7: Integration Tests

#### Complete Gameplay Test

1. **Start Game**:
   - Press Play in Editor
   - Ship spawns
   - Skybox visible
   - Camera positioned correctly

2. **Fly Around**:
   - WASD for movement
   - Mouse for rotation
   - Mouse wheel for zoom
   - V to toggle view

3. **Visual Environment**:
   - Skybox follows
   - No visual glitches
   - Smooth performance

4. **Controls Feel**:
   - Natural movement
   - Good ship visibility
   - Easy to navigate
   - Not "too fast"

## Performance Testing

### Frame Rate

1. **Check FPS** (~ key for console, `stat fps`):
   - Should maintain target FPS
   - Skybox minimal performance impact

2. **Profile** (if needed):
   - Console: `stat unit`
   - Game thread should be low (<16ms for 60fps)
   - GPU shouldn't spike from skybox

### Memory

1. **Check Stats**:
   - Console: `stat memory`
   - Skybox adds minimal memory
   - Large mesh but simple material

## Debugging

### Enable Debug Logging

In console (~ key):
```
log LogTemp Verbose
```

Look for these messages:
```
SubspaceGameMode: Space skybox spawned
SubspacePlayerPawn: Ship initialized
SpaceSkyboxActor: Initialized skybox
```

### Common Issues and Fixes

| Issue | Cause | Fix |
|-------|-------|-----|
| Ship too small | Old scale used | Check ship scale = 4×8×2 |
| Moving too fast | Old physics | Verify drag = 0.5, mass = 1000 |
| Camera too close | Wrong distance | Check CameraDistance = 1000 |
| No skybox | Not spawned | Check GameMode spawns it |
| Skybox not following | bFollowCamera = false | Enable in properties |
| Can't zoom | Input not bound | Check DefaultInput.ini |

### Verify Code Changes

**SubspacePlayerPawn.h should have:**
```cpp
float CameraDistance = 1000.0f;
float ShipMass = 1000.0f;
float DragCoefficient = 0.5f;
void ZoomCamera(float Value);
void ToggleCameraMode();
```

**SubspaceGameMode.cpp should have:**
```cpp
#include "SpaceSkyboxActor.h"
// In BeginPlay:
ASpaceSkyboxActor* Skybox = GetWorld()->SpawnActor<ASpaceSkyboxActor>(...);
```

**DefaultInput.ini should have:**
```ini
+AxisMappings=(AxisName="MouseWheelAxis",Scale=1.000000,Key=MouseWheelAxis)
+ActionMappings=(ActionName="ToggleCameraMode",...,Key=V)
```

## Expected Results Summary

### ✅ Ship Rendering
- [x] Ship clearly visible at default camera distance
- [x] Larger mesh (4×8×2) improves visibility
- [x] Collision properly enabled

### ✅ Movement Physics
- [x] Smooth acceleration (not instant)
- [x] Realistic top speed (drag limits)
- [x] Controllable movement (not "super fast")
- [x] Proper mass-based physics

### ✅ Camera System
- [x] Third-person default view
- [x] Adjustable distance (mouse wheel)
- [x] Toggle 1st/3rd person (V key)
- [x] Smooth following with lag
- [x] Good default pitch angle (-15°)

### ✅ Space Environment
- [x] Skybox spawns automatically
- [x] Follows player camera
- [x] Infinite distance effect
- [x] Customizable appearance
- [x] Minimal performance impact

## Video Recording Recommendations

To showcase the improvements, record:

1. **Before/After Comparison** (if possible):
   - Old version: Fast movement, poor visibility
   - New version: Controlled, clear view

2. **Camera Demonstration**:
   - Zoom in/out with mouse wheel
   - Toggle first/third person
   - Show smooth following

3. **Physics Showcase**:
   - Gradual acceleration
   - Terminal velocity
   - Emergency brake

4. **Skybox View**:
   - 360° view of space
   - Show it follows camera
   - Demonstrate infinite distance

## Sign-Off Checklist

Before considering testing complete:

- [ ] Project compiles without errors
- [ ] Ship renders and is clearly visible
- [ ] Movement feels controlled (not too fast)
- [ ] Mouse wheel zooms camera
- [ ] V key toggles camera view
- [ ] Skybox appears in scene
- [ ] Skybox follows player
- [ ] No performance issues
- [ ] Documentation reviewed
- [ ] Controls feel intuitive

## Next Steps

After successful testing:

1. **Create Blueprint Variant**:
   - BP_SpacePlayer based on SubspacePlayerPawn
   - Assign better ship mesh
   - Tune physics values for your game

2. **Create Skybox Material**:
   - Follow SKYBOX_MATERIAL_GUIDE.md
   - Create procedural starfield
   - Assign to SpaceSkyboxActor

3. **Polish**:
   - Add engine particle effects
   - Add shield visuals
   - Add HUD elements
   - Tune camera feel

---

*For issues or questions, see CAMERA_AND_VISUAL_IMPROVEMENTS.md*
