# Ship Camera and Visual Improvements

This document describes the recent improvements to ship rendering, camera controls, and space environment.

## Overview

The following issues have been addressed:
1. **Ship visibility** - Improved ship mesh scaling for better visibility
2. **Movement speed** - Fixed physics calculations to prevent "super fast" feel
3. **Chase camera** - Added X4-style adjustable third-person camera
4. **Space skybox** - Implemented starfield background for space scenes

## Camera Controls

### Third Person Camera (Default)

The game now features a smooth, adjustable chase camera similar to X4: Foundations:

- **Mouse Wheel Up/Down** - Zoom in/out (300-5000 units)
- **V Key** - Toggle between first-person (cockpit) and third-person views
- **Camera follows ship** with smooth lag for natural movement
- **Default distance**: 1000 units
- **Default pitch**: -15° (looking down at ship slightly)

### Camera Properties (Editable in Blueprint/Editor)

| Property | Default | Range | Description |
|----------|---------|-------|-------------|
| CameraDistance | 1000 | 300-5000 | Distance from ship |
| MinCameraDistance | 300 | - | Minimum zoom distance |
| MaxCameraDistance | 5000 | - | Maximum zoom distance |
| CameraZoomSpeed | 100 | - | Zoom speed multiplier |
| CameraPitchOffset | -15° | - | Camera angle offset |
| CameraLagSpeed | 3.0 | - | Smooth follow speed |

## Physics Improvements

### Movement Speed Fix

The previous "super fast" movement feel has been corrected with proper physics:

**Before:**
- Simple linear thrust application
- Low drag coefficient (0.1)
- No mass consideration

**After:**
- Physics-based thrust: F = ma (Force = Mass × Acceleration)
- Quadratic drag: Drag ∝ v² (realistic air/space resistance)
- Configurable ship mass (default: 1000 kg)
- Higher drag coefficient (0.5) for better control

### Ship Physics Properties

| Property | Default | Description |
|----------|---------|-------------|
| ShipMass | 1000 kg | Ship mass for physics calculations |
| MaxThrust | 50000 N | Maximum thrust force |
| MaxRotationForce | 5000 N·m | Maximum rotational force |
| DragCoefficient | 0.5 | Drag factor (higher = more drag) |

## Ship Visibility

### Mesh Scale
- Increased default ship scale to **4×8×2** units (was 2×4×1)
- Makes ships more visible at default camera distance
- Better proportions for space combat visibility

### Collision
- Proper collision enabled (QueryAndPhysics)
- Allows for future combat and docking mechanics

## Space Skybox

### Features

A new `SpaceSkyboxActor` provides a professional space environment:

1. **Infinite Starfield**
   - Large inverted sphere (100,000 unit radius)
   - Follows camera for infinite distance effect
   - No collision or shadows

2. **Customizable Appearance**
   - Star brightness (0-10, default: 1.0)
   - Star density (0-1, default: 0.5)
   - Nebula color tint
   - Optional slow rotation

3. **Performance**
   - No collision calculations
   - No shadows or reflections
   - Optimized for large scale

### Using the Skybox

The skybox spawns automatically in game mode. To customize:

1. **In Editor:**
   - Find `SpaceSkyboxActor` in World Outliner
   - Adjust properties in Details panel

2. **In Blueprint:**
   - Create BP child of `SpaceSkyboxActor`
   - Assign custom starfield material
   - Modify appearance properties

3. **Material Setup:**
   - Create an emissive material
   - Use star texture or noise function
   - Assign to `SkyboxMaterial` property

### Skybox Properties

| Property | Default | Description |
|----------|---------|-------------|
| SkyboxRadius | 100000 | Skybox size (very large) |
| StarBrightness | 1.0 | Star brightness multiplier |
| StarDensity | 0.5 | Star density (0-1) |
| NebulaColor | Purple tint | Background nebula color |
| bRotateSkybox | false | Enable slow rotation |
| RotationSpeed | 0.5°/s | Rotation speed if enabled |
| bFollowCamera | true | Follow camera for infinite distance |

## Input Bindings

### New Controls

Added to `DefaultInput.ini`:

```ini
# Camera zoom
+AxisMappings=(AxisName="MouseWheelAxis",Scale=1.000000,Key=MouseWheelAxis)

# Toggle camera mode (1st/3rd person)
+ActionMappings=(ActionName="ToggleCameraMode",bShift=False,bCtrl=False,bAlt=False,bCmd=False,Key=V)
```

### Complete Ship Controls

| Input | Action | Description |
|-------|--------|-------------|
| **W/S** | Forward/Backward | Thrust along ship's forward axis |
| **A/D** | Strafe Left/Right | Thrust perpendicular to ship |
| **Space/Shift** | Up/Down | Vertical thrust |
| **Arrow Keys** | Pitch/Yaw | Keyboard rotation |
| **Q/E** | Roll | Barrel roll left/right |
| **Mouse** | Look | FPS-style rotation control |
| **Mouse Wheel** | Zoom | Adjust camera distance |
| **V** | Toggle View | Switch 1st/3rd person |
| **B** | Brake | Emergency stop (all velocity) |

## Technical Details

### Files Modified

1. **SubspacePlayerPawn.h/cpp**
   - Added camera distance properties
   - Added zoom and toggle functions
   - Improved physics calculations
   - Enhanced ship mesh setup

2. **SpaceSkyboxActor.h/cpp** (NEW)
   - Complete skybox implementation
   - Material parameter support
   - Camera following logic

3. **SubspaceGameMode.cpp**
   - Added skybox spawning
   - Integrated with existing lighting

4. **DefaultInput.ini**
   - Mouse wheel axis binding
   - Camera toggle key binding

### Physics Formulas

**Thrust Application:**
```cpp
Force = Direction × Magnitude × MaxThrust
Acceleration = Force / ShipMass
Velocity += Acceleration × DeltaTime
```

**Quadratic Drag:**
```cpp
Speed = Velocity.Size()
DragForce = -Velocity.Normalized() × DragCoefficient × Speed²
DragAcceleration = DragForce / ShipMass
Velocity += DragAcceleration × DeltaTime
```

## Future Enhancements

### Potential Improvements

1. **Camera System**
   - Add cinematic camera mode
   - Implement camera shake for impacts
   - Add zoom presets (close, medium, far)
   - Target lock camera for combat

2. **Skybox**
   - Add parallax nebula layers
   - Distant planet rendering
   - Animated pulsars/stars
   - Sector-specific skyboxes

3. **Ship Rendering**
   - Engine glow effects
   - Shield visualization
   - Damage decals
   - Custom ship meshes

4. **Physics**
   - Inertial dampeners toggle
   - Flight assist modes
   - Boost/afterburner system
   - Realistic orbital mechanics

## Testing

To test the new features:

1. **Launch the game** - Skybox spawns automatically
2. **Press W** - Apply forward thrust (note smoother acceleration)
3. **Scroll mouse wheel** - Zoom camera in/out
4. **Press V** - Toggle between cockpit and chase camera
5. **Press B** - Emergency brake to feel the improved physics

The ship should now:
- ✅ Be clearly visible at default distance
- ✅ Accelerate smoothly without feeling "too fast"
- ✅ Have natural speed limits from drag
- ✅ Provide excellent visibility in third-person
- ✅ Display in a proper space environment

## Credits

Camera system inspired by:
- **X4: Foundations** - Chase camera design
- **Elite Dangerous** - Physics and controls
- **Star Citizen** - Smooth camera interpolation

---

*Last Updated: January 6, 2026*
*Version: 1.0*
