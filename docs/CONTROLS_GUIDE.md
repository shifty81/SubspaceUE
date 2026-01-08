# SubspaceUE Controls Guide

## Overview
This document describes the complete control scheme for SubspaceUE, including ship flight controls and FPS character controls.

## Ship Flight Controls

### Basic Movement
- **W** - Forward thrust
- **S** - Backward thrust
- **A** - Strafe left
- **D** - Strafe right
- **Space** - Vertical thrust up
- **Ctrl** - Vertical thrust down

### Boost System
- **Shift (Hold)** - Activate boost for forward/backward thrust
  - Applies 2x multiplier to W/S movement
  - Similar to sprint in FPS games
  - Release to return to normal thrust

### Rotation Controls
- **Mouse Movement** - Free-look pitch (up/down) and yaw (left/right)
  - Mouse left/right: Yaw (turn left/right)
  - Mouse up/down: Pitch (look up/down)
- **Arrow Keys** - Alternative rotation controls
  - Up/Down arrows: Pitch
  - Left/Right arrows: Yaw
- **Q** - Roll left
- **E** - Roll right

### Camera Controls
- **Mouse Wheel** - Zoom in/out
- **V** - Toggle between first-person (cockpit) and third-person view

### Special Actions
- **B** - Emergency brake (immediately stops all movement and rotation)
- **F** - Exit ship (spawns FPS character outside ship)

## FPS Character Controls

### Movement
- **W** - Move forward
- **S** - Move backward
- **A** - Strafe left
- **D** - Strafe right
- **Shift (Hold)** - Sprint (2x movement speed)

### Camera
- **Mouse Movement** - Look around
  - Mouse left/right: Turn (yaw)
  - Mouse up/down: Look up/down (pitch)

### Ship Interaction
- **F** - Enter nearby ship (when in range)
  - Must be within 500 units of a ship
  - Ship becomes highlighted/detected automatically

## Control Sensitivity Settings

All sensitivity values can be adjusted in the actor properties (Blueprint or C++):

### Ship Controls
- `MousePitchSensitivity`: Default 1.0
- `MouseYawSensitivity`: Default 1.0
- `MouseResponsivenessMultiplier`: Default 0.5
- `BoostMultiplier`: Default 2.0

### Character Controls
- `MousePitchSensitivity`: Default 1.0
- `MouseYawSensitivity`: Default 1.0
- `WalkSpeed`: Default 400.0 cm/s
- `SprintSpeed`: Default 800.0 cm/s

## Recent Changes (January 2026)

### Fixed Issues
1. **Inverted Yaw**: Mouse left/right now correctly turns the ship left/right
2. **Mouse Sensitivity**: Reduced from 0.20 to 0.07 for more precise control
3. **Control Mapping**: Updated key bindings to match user requirements

### New Features
1. **Boost System**: Shift now provides forward thrust boost instead of vertical down
2. **Improved Vertical Controls**: Space (up) and Ctrl (down) for vertical thrust
3. **FPS Character**: Added first-person character with enter/exit ship mechanics
4. **Enter/Exit System**: F key to transition between ship and character

## Physics Model

### Ship Physics
- **Newtonian Physics**: The ship maintains momentum (no automatic stopping)
- **6 Degrees of Freedom (6DOF)**: Full freedom of movement and rotation
- **Drag System**: Quadratic drag slows the ship over time
- **Mass-Based**: Thrust effectiveness depends on ship mass

### Character Physics
- **Standard UE Character Movement**: Walking, jumping, and collision
- **Gravity**: Character is affected by gravity (unlike ship)
- **Sprint Mechanic**: Hold Shift for increased movement speed

## Tips and Best Practices

### Ship Flight
1. **Use Boost Wisely**: Boost increases acceleration but can make control harder
2. **Emergency Brake**: Press B to quickly stop when approaching targets
3. **Combined Controls**: Use keyboard for rotation and mouse for fine-tuning
4. **Camera Distance**: Adjust zoom for better situational awareness

### Character Movement
1. **Sprint Management**: Use sprint for long distances, walk for precision
2. **Ship Entry**: Look for nearby ships and press F when in range
3. **Interior Navigation**: Walk through ship interior after entering (when implemented)

## Gamepad Support

Basic gamepad controls are mapped:
- **Left Stick**: Forward/backward and strafe
- **Right Stick**: Pitch and yaw
- **Triggers**: Roll left/right
- **Shoulders**: Vertical thrust up/down
- **Face Button Bottom**: Enter/Exit ship
- **Face Button Left**: Emergency brake

## Troubleshooting

### Ship Controls Feel Wrong
- Check `MouseResponsivenessMultiplier` - increase for more responsive feel
- Adjust individual `MousePitchSensitivity` and `MouseYawSensitivity`
- Try toggling `bInvertMousePitch` or `bInvertMouseYaw` in settings

### Character Movement Issues
- Verify character is spawned correctly
- Check collision settings
- Ensure ship is detected (within 500 units)

### Can't Enter/Exit Ship
- Verify you're within detection range (500 units)
- Check that F key is properly bound
- Look at console logs for error messages

## Configuration Files

### Input Configuration
Primary input bindings are in: `Config/DefaultInput.ini`

### Code Files
- Ship: `Source/SubspaceUE/Private/SubspacePlayerPawn.cpp`
- Character: `Source/SubspaceUE/Private/SubspaceCharacter.cpp`

## Future Enhancements

Planned control improvements:
- [ ] Flight assist toggle (auto-stabilization)
- [ ] Cruise control (maintain constant speed)
- [ ] Precision mode (reduced sensitivity)
- [ ] Customizable key bindings (runtime)
- [ ] Multiple control profiles
- [ ] VR support
- [ ] Advanced gamepad features

---

**Last Updated**: January 8, 2026  
**Version**: 1.0  
**Compatible with**: SubspaceUE v0.1+
