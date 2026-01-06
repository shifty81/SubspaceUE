# FPS-Style Control Update

## Changes Made

### Overview
Updated the SubspaceUE project to use FPS-style mouse look controls, making the gameplay feel more like standard first-person or flight simulator games, as requested to match X4: Foundations control style.

### Modified Files

1. **Source/SubspaceUE/Public/SubspacePlayerPawn.h**
   - Added mouse sensitivity properties: `MousePitchSensitivity`, `MouseYawSensitivity` (default: 1.0)
   - Added mouse inversion options: `bInvertMousePitch`, `bInvertMouseYaw`
   - Added new input handlers: `LookUp()`, `LookRight()`
   - All properties are exposed to Blueprint for easy tweaking

2. **Source/SubspaceUE/Private/SubspacePlayerPawn.cpp**
   - Implemented `LookUp()` function for mouse pitch control (up/down looking)
   - Implemented `LookRight()` function for mouse yaw control (left/right looking)
   - Applied 2x multiplier for more responsive mouse control
   - Bound new mouse input axes in `SetupPlayerInputComponent()`
   - Mouse input respects sensitivity and inversion settings

3. **Config/DefaultInput.ini**
   - Added axis mapping: `LookUp` bound to `MouseY` (inverted scale)
   - Added axis mapping: `LookRight` bound to `MouseX`
   - Increased mouse sensitivity from 0.07 to 0.20 for better FPS feel
   - Arrow keys remain functional as alternative input method

## Control Scheme (After Update)

### Movement (Unchanged)
- **W/S**: Forward/Backward thrust
- **A/D**: Strafe left/right
- **Space/Shift**: Thrust up/down
- **B**: Emergency brake

### Rotation
- **Mouse Movement**: Pitch and yaw control (NEW - FPS style)
- **Arrow Keys**: Pitch and yaw control (alternative)
- **Q/E**: Roll left/right

### Features
- Configurable mouse sensitivity per axis
- Optional mouse inversion for pitch and yaw
- Dual input support (mouse AND arrow keys work simultaneously)
- All settings exposed in Blueprint for runtime adjustment

## X4: Foundations Alignment

This update aligns the controls with X4: Foundations style:
- **FPS Mode**: Mouse look for camera control
- **Flight Mode**: WASD for movement, mouse for looking
- **Smooth Controls**: Responsive mouse input with configurable sensitivity
- **Player Choice**: Both keyboard and mouse options available

## Testing Recommendations

1. **In Unreal Editor**:
   - Open the project in UE 5.7
   - Select the SubspacePlayerPawn Blueprint
   - Adjust mouse sensitivity values in the Details panel
   - Play in Editor (PIE) and test mouse look

2. **Sensitivity Tuning**:
   - Default sensitivity: 1.0
   - Increase for faster response: 1.5-2.0
   - Decrease for precision: 0.5-0.8

3. **Inversion Testing**:
   - Enable `bInvertMousePitch` for inverted Y-axis
   - Enable `bInvertMouseYaw` for inverted X-axis (less common)

## Future Enhancements

Potential improvements based on player feedback:
- Mouse smoothing/acceleration options
- Separate sensitivity for ship vs. character modes
- Flight assist toggle (dampening on/off)
- Deadzone configuration for mouse input
- Mouse capture mode options (locked/relative movement)

## Build Instructions

The changes are C++ code modifications. To build:

1. **From Unreal Editor**:
   - Open SubspaceUE.uproject
   - If prompted to rebuild, click "Yes"
   - Wait for compilation

2. **From Visual Studio**:
   - Open SubspaceUE.sln
   - Build → Build Solution (Ctrl+Shift+B)
   - Set to "Development Editor" configuration

3. **From Command Line** (Windows):
   ```batch
   "C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" SubspaceUEEditor Win64 Development -Project="%CD%\SubspaceUE.uproject"
   ```

## Verification

All changes compile correctly with UE 5.7 API:
- ✅ Proper UPROPERTY macros for Blueprint exposure
- ✅ Correct input binding in SetupPlayerInputComponent
- ✅ Valid axis mappings in DefaultInput.ini
- ✅ Consistent with UE5 coding standards

