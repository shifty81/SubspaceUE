# Sol-TestingGrounds Troubleshooting Guide

Common issues and solutions when implementing the Sol-TestingGrounds sector and spaceship-5 starting ship.

---

## Table of Contents

1. [Asset Import Issues](#asset-import-issues)
2. [Material and Texture Problems](#material-and-texture-problems)
3. [Ship and Interior Issues](#ship-and-interior-issues)
4. [Gameplay and Controls](#gameplay-and-controls)
5. [Performance Problems](#performance-problems)
6. [Level and Lighting Issues](#level-and-lighting-issues)
7. [Build and Compilation Errors](#build-and-compilation-errors)

---

## Asset Import Issues

### Problem: FBX Import Fails or Shows Errors

**Symptoms:**
- Error dialog when importing Earth&Moon.fbx or spaceship FBX
- "Failed to import" message
- Assets don't appear after import

**Solutions:**

1. **Check File Path**
   ```
   - Ensure file path doesn't contain special characters
   - No spaces or unicode characters in folder names
   - Try moving file to simpler path: C:\Temp\asset.fbx
   ```

2. **Verify FBX Version**
   ```
   - UE 5.6 supports FBX 2018 and 2020
   - If using Blender:
     - Export settings → FBX version: 7.4 binary
     - Or use FBX 2020
   ```

3. **Check File Corruption**
   ```
   - Re-extract from zip if applicable
   - Verify file size matches expected
   - Try opening in Blender to verify validity
   ```

4. **Import Settings**
   ```
   - Try "Import All" first (don't click individual options)
   - Disable "Import Materials" if textures are separate
   - Try with "Combine Meshes" disabled
   ```

5. **Restart Editor**
   ```
   - Close Unreal Editor completely
   - Delete Intermediate, Saved, .vs folders (safe to delete)
   - Reopen project
   - Try import again
   ```

### Problem: Blender File Won't Open

**Symptoms:**
- spaceship-5 .blend file doesn't open in Blender
- "File format not recognized" error

**Solutions:**

1. **Update Blender**
   ```
   - Download latest Blender (3.0+)
   - The file was created in Blender 2.9+
   - Older versions may not open newer files
   ```

2. **Re-extract Zip**
   ```
   - Delete extracted folder
   - Extract spaceship-5.zip again
   - Verify file isn't corrupted (check file size: ~45MB)
   ```

3. **Use Online Converter**
   ```
   - If Blender install fails
   - Search "blend to fbx online converter"
   - Upload .blend file, download .fbx
   - Note: May lose some features
   ```

### Problem: Textures Don't Import with FBX

**Symptoms:**
- Mesh imports but textures are missing
- Materials created but no textures assigned

**Solutions:**

1. **Import Textures Separately**
   ```
   - This is actually preferred workflow
   - Import FBX first
   - Then batch import texture files separately
   - Manually assign to materials
   ```

2. **Check Texture Path**
   ```
   - FBX references textures by path
   - If path doesn't exist, import fails
   - Solution: Always import textures separately after FBX
   ```

3. **Verify Texture Format**
   ```
   - Supported: PNG, TGA, JPG, EXR
   - Unsupported: BMP, GIF (usually)
   - Convert if needed
   ```

---

## Material and Texture Problems

### Problem: Planets Appear Black or Invisible

**Symptoms:**
- Planet meshes in viewport but completely black
- Or planets invisible when playing

**Solutions:**

1. **Check Material Assignment**
   ```
   - Select planet mesh in viewport
   - Details panel → Materials section
   - Verify material is assigned (not "None")
   - If None, drag material from Content Browser
   ```

2. **Verify Material Setup**
   ```
   - Open material (double-click)
   - Check textures are connected
   - Preview window should show result
   - If black, check texture assignments
   ```

3. **Rebuild Lighting**
   ```
   - Build → Build Lighting Only
   - Wait for completion
   - Check if planets now visible
   ```

4. **Check Exposure**
   ```
   - May be exposure issue
   - In viewport: Show → Exposure Settings
   - Disable "Game Settings"
   - Adjust exposure manually
   ```

5. **Verify Emissive (if self-illuminated)**
   ```
   - For planets, ensure emissive is NOT zero
   - Or use proper lighting (Directional Light)
   - Post Process → Exposure needs adjustment
   ```

### Problem: Normal Maps Look Wrong

**Symptoms:**
- Surfaces look inverted or weird bumps
- Lighting appears incorrect on textured surfaces

**Solutions:**

1. **Check Normal Map Settings**
   ```
   - Open normal map texture (double-click)
   - Settings:
     - sRGB: ✗ MUST BE DISABLED
     - Compression Settings: Normalmap (TC_Normalmap)
   - Click Save
   - Reimport texture if needed
   ```

2. **Flip Green Channel (if needed)**
   ```
   - Some normal maps use different Y direction
   - In material:
     - Between texture and Normal pin
     - Add component mask node
     - Invert G channel if needed
   ```

3. **Check Normal Map Strength**
   ```
   - In material, add multiply node
   - Before normal input
   - Multiply by scalar (0.5-2.0)
   - Lower = less bumpy
   ```

### Problem: Spaceship Material Too Shiny or Matte

**Symptoms:**
- Ship looks like plastic (too shiny)
- Or too dull (no reflections)

**Solutions:**

1. **Adjust Roughness**
   ```
   - Open material instance (MI_Spaceship_001)
   - Find Roughness parameter
   - Increase for more matte: 0.6-0.9
   - Decrease for more shiny: 0.1-0.4
   - Metallic parts should be: 0.2-0.4 roughness
   ```

2. **Check Metallic Values**
   ```
   - Metallic: 0.0 = non-metal, 1.0 = pure metal
   - Spaceship hull: 0.7-0.9 metallic
   - Painted parts: 0.1-0.3 metallic
   - Adjust in material instance
   ```

3. **Verify Texture Channels**
   ```
   - Metallic texture:
     - R channel = Metallic mask (often)
     - G or A channel = Roughness (check which)
   - Try swapping channels if wrong
   ```

4. **Check Lighting**
   ```
   - Poor lighting can make materials look wrong
   - Add reflection capture actor nearby
   - Rebuild lighting
   - Check Post Process Volume settings
   ```

### Problem: Emissive Too Bright or Not Visible

**Symptoms:**
- Emissive elements blow out (too bright)
- Or emissive not showing at all

**Solutions:**

1. **Adjust Emissive Strength**
   ```
   - Open material instance
   - Find EmissiveStrength parameter
   - For ship lights: 2.0-5.0
   - For screens: 5.0-10.0
   - For subtle glow: 0.5-2.0
   ```

2. **Check Post Process Bloom**
   ```
   - Post Process Volume settings
   - Bloom → Intensity: 1.0-2.0
   - Bloom → Threshold: 0.5-1.5
   - Lower threshold = more bloom on emissive
   ```

3. **Exposure Settings**
   ```
   - Post Process → Exposure
   - If too bright:
     - Lower Exposure Compensation: -1.0 to 0.0
   - If too dim:
     - Raise Exposure Compensation: 0.5 to 2.0
   ```

4. **Check Color Values**
   ```
   - Emissive Color in material
   - RGB values: 0.0-1.0 typically
   - For very bright: multiply by 10-100
   - For HDR bloom: values > 1.0
   ```

---

## Ship and Interior Issues

### Problem: Player Falls Through Ship Floor

**Symptoms:**
- Player spawns, immediately falls down
- Passes through ship geometry

**Solutions:**

1. **Enable Collision on Ship**
   ```
   - Open ship static mesh (double-click)
   - Details → Collision
   - If no collision visible (no green wireframe):
     - Collision → Generate Complex Collision As Simple
     - Or: Add Simple Collision → Add Box/Capsule
   - Save mesh
   ```

2. **Check Player Start Position**
   ```
   - Select Player Start in level
   - Ensure Z position is ABOVE floor
   - Add +50 units to Z coordinate
   - Rotate to face forward
   ```

3. **Verify Collision Settings**
   ```
   - Ship mesh:
     - Collision Presets: BlockAll or Custom
     - Collision Enabled: Query and Physics
   
   - Player pawn:
     - Collision Presets: Pawn
     - Collision Enabled: Query and Physics
   
   - Both must be set to BLOCK each other
   ```

4. **Check Physics Settings**
   ```
   - If player pawn has Simulate Physics enabled:
     - Ensure Mass is set (10-100)
     - Check Linear Damping (0.5-2.0)
   - Otherwise may fall through
   ```

5. **Test Collision Visibility**
   ```
   - In viewport, press Alt+C (show collision)
   - Or: Show → Collision
   - Green wireframe should cover ship
   - If gaps, regenerate collision
   ```

### Problem: Interior Too Dark to See

**Symptoms:**
- Interior is pitch black or nearly black
- Can't navigate ship interior

**Solutions:**

1. **Add More Lights**
   ```
   - Place Point Lights every 300-500 units
   - Intensity: 5000-10000
   - Color: White (1.0, 1.0, 1.0)
   - Attenuation Radius: 1000-1500
   ```

2. **Check Light Settings**
   ```
   - Select existing lights
   - Verify:
     - Intensity is not 0
     - Attenuation Radius covers area
     - "Visible" checkbox is checked
   ```

3. **Build Lighting**
   ```
   - Build → Build Lighting Only
   - Or: Build → Build All
   - Wait for completion (may take minutes)
   ```

4. **Use Unbound Post Process**
   ```
   - Post Process Volume → Infinite Extent: ✓
   - Exposure → Manual mode
   - Exposure Compensation: 1.0 to 3.0 (increase)
   ```

5. **Add Emissive Materials**
   ```
   - Interior panels with emissive glow
   - Ceiling light fixtures with emissive
   - Helps even if point lights fail
   ```

6. **Check Skylight**
   ```
   - If Skylight exists, may be too dim
   - Increase intensity: 0.5-1.0
   - Set Source: Captured Scene
   - Recapture
   ```

### Problem: Ship Interior Doesn't Fit Hull

**Symptoms:**
- Interior sticks out of ship
- Or interior too small, lots of empty space

**Solutions:**

1. **Measure Ship Bounds**
   ```
   - Open ship static mesh
   - Details → Static Mesh Settings
   - Note Bounds: X, Y, Z dimensions
   ```

2. **Scale Interior Appropriately**
   ```
   - Interior should be 80-90% of hull
   - Example: Ship is 2000 long
     - Interior: 1800 long (leaving 100 margin each end)
   - Select interior meshes
   - Scale uniformly to fit
   ```

3. **Use Visual References**
   ```
   - In viewport, select ship hull mesh
   - Make semi-transparent (to see inside)
   - Place interior meshes to align
   - Make hull opaque again when done
   ```

4. **Rebuild Interior**
   ```
   - If way off, easier to start over
   - Measure hull carefully
   - Build interior piece by piece
   - Test fit frequently
   ```

### Problem: Interior Props Floating or Misaligned

**Symptoms:**
- Props hover above floor
- Or sink into geometry

**Solutions:**

1. **Snap to Grid**
   ```
   - Enable grid snapping (magnet icon)
   - Grid size: 10 or 25
   - Drag props, will snap to grid
   ```

2. **Use "End" Key**
   ```
   - Select prop
   - Press "End" key
   - Will drop to floor below
   - Works if floor has collision
   ```

3. **Manual Alignment**
   ```
   - Check Z coordinate in Details panel
   - Floor Z value + (prop height / 2)
   - Example: Floor at 0, prop 100 tall
     - Prop Z position: 50
   ```

4. **Enable Surface Snapping**
   ```
   - Viewport options → Snap to Surface
   - Drag object, will snap to mesh surface
   ```

---

## Gameplay and Controls

### Problem: Ship Controls Don't Work

**Symptoms:**
- Pressing keys has no effect
- Ship doesn't move or rotate

**Solutions:**

1. **Check Input Bindings**
   ```
   - Edit → Project Settings → Input
   - Verify Action/Axis Mappings exist:
     - MoveForward (W/S)
     - MoveRight (A/D)
     - MoveUp (Space/Shift)
   - If missing, add them
   ```

2. **Verify GameMode Assignment**
   ```
   - Open level
   - Window → World Settings
   - GameMode Override: Should be set (not None)
   - Default Pawn Class: Should be your ship BP
   ```

3. **Check Pawn Input**
   ```
   - Open player ship blueprint
   - Class Settings (top toolbar)
   - Auto Possess Player: Player 0
   - Must be set to receive input
   ```

4. **Test Input in Blueprint**
   ```
   - Ship blueprint → Event Graph
   - Verify input events exist:
     - Input Axis MoveForward
     - etc.
   - Check they're connected to movement logic
   - Add Print String nodes to debug
   ```

5. **Check PlayerController**
   ```
   - GameMode may specify wrong controller
   - Set Player Controller Class correctly
   - Controller should enable input
   ```

### Problem: Camera Behaves Strangely

**Symptoms:**
- Camera flips around
- Too close or too far from ship
- Jittery movement

**Solutions:**

1. **Adjust Spring Arm**
   ```
   - Ship blueprint → Components
   - Select Spring Arm
   - Target Arm Length: 1500-2500 (distance)
   - Enable Camera Lag: ✓
   - Camera Lag Speed: 3.0-5.0
   ```

2. **Check Camera Attachment**
   ```
   - Camera should attach to Spring Arm
   - Spring Arm attaches to ship mesh or root
   - Wrong attachment = weird behavior
   ```

3. **Rotation Settings**
   ```
   - Spring Arm → Details
   - Use Pawn Control Rotation: ✓ (for controlled rotation)
   - Or: ✗ (for fixed behind ship)
   - Inherit Pitch/Yaw/Roll: Set as desired
   ```

4. **Fix Jitter**
   ```
   - Often due to physics simulation
   - Ship mesh → Details → Physics
   - Increase Linear Damping: 2.0-5.0
   - Increase Angular Damping: 5.0-10.0
   ```

### Problem: Ship Rotates When It Shouldn't

**Symptoms:**
- Ship spins uncontrollably
- Or rotates when only moving forward

**Solutions:**

1. **Check Physics Constraints**
   ```
   - Ship mesh → Physics
   - Lock Rotation if needed:
     - Constraints → Lock Position/Rotation
     - Or use physics constraints actor
   ```

2. **Verify Movement Component**
   ```
   - Should use FloatingPawnMovement
   - Or custom 6DOF movement
   - Check settings:
     - Max Speed
     - Acceleration
     - Deceleration
   - Ensure settings are reasonable
   ```

3. **Check Center of Mass**
   ```
   - Ship mesh → Physics
   - Center of Mass Override
   - Should be near center of ship
   - If off, ship rotates incorrectly
   ```

4. **Reduce External Forces**
   ```
   - Check for:
     - Wind actors (shouldn't affect space ship)
     - Gravity (should be 0 in space)
     - Other force volumes
   ```

---

## Performance Problems

### Problem: Low Frame Rate (FPS)

**Symptoms:**
- Game runs slowly (<30 FPS)
- Stuttering or hitching

**Solutions:**

1. **Check Current FPS**
   ```
   - Press ` (backtick) for console
   - Type: stat fps
   - Shows current frame rate
   ```

2. **Reduce Planet Complexity**
   ```
   - Open planet static mesh
   - Details → LOD Settings
   - LOD 0 (high detail):
     - Screen Size: 1.0-0.5
   - LOD 1 (medium):
     - Reduce triangle count: 50%
     - Screen Size: 0.5-0.1
   - Auto-generate LODs if needed
   ```

3. **Lower Texture Resolutions**
   ```
   - Select texture in Content Browser
   - Details → Compression
   - Maximum Texture Size: 2048 or 1024
   - Compress now
   - Apply to all high-res textures (4K → 2K)
   ```

4. **Optimize Lighting**
   ```
   - Reduce dynamic lights:
     - Max 5-10 visible at once
   - Use static lights:
     - Mark lights as "Static"
     - Build lighting
   - Reduce shadow quality:
     - Lights → Dynamic Shadow Distance: 1000-2000
   ```

5. **Adjust Post-Processing**
   ```
   - Post Process Volume settings
   - Disable or reduce:
     - Motion Blur: 0
     - Depth of Field: Disabled
     - Bloom: Reduce intensity to 0.5
     - Screen Space Reflections: Disabled or low quality
   ```

6. **Check Draw Distance**
   ```
   - Select distant objects (planets, asteroids)
   - Details → Rendering
   - Max Draw Distance: 100000-500000
   - Cull Distance Volume (for automatic)
   ```

7. **Profile Performance**
   ```
   - Console commands:
     - stat unit (shows CPU/GPU/frame time)
     - stat gpu (detailed GPU stats)
     - stat scenerendering (draw calls)
   - Identify bottleneck (CPU vs GPU)
   ```

### Problem: Long Level Load Times

**Symptoms:**
- Level takes 30+ seconds to load
- Editor freezes on level open

**Solutions:**

1. **Reduce Asset Count**
   ```
   - Count actors in level (World Outliner)
   - Target: <500 actors for good performance
   - Remove unnecessary details
   - Merge static meshes
   ```

2. **Enable Async Loading**
   ```
   - Project Settings → Engine → Streaming
   - Async Loading: ✓
   - Event Driven Loader: ✓
   ```

3. **Use Level Streaming**
   ```
   - Split level into sub-levels
   - Main level: Just essentials
   - Streaming levels: Loaded on demand
   - Good for large sectors
   ```

4. **Optimize Textures**
   ```
   - Enable texture streaming
   - Project Settings → Engine → Texture Streaming
   - Pool Size: 1000-2000 MB
   - Per-Platform Size: Adjust
   ```

---

## Level and Lighting Issues

### Problem: No Sun/Stars Visible

**Symptoms:**
- Black sky, no stars or sun
- Space looks empty

**Solutions:**

1. **Add Skybox**
   ```
   - If SpaceSkyboxActor available:
     - Place in level at 0, 0, 0
     - Scale large: 1000000
   - Or create sphere:
     - Scale huge
     - Apply starfield material
     - Invert normals (negative scale on one axis)
   ```

2. **Check Directional Light**
   ```
   - Should have 1 Directional Light (sun)
   - Settings:
     - Intensity: 10-20
     - Color: Yellowish white
   - Ensure not disabled
   ```

3. **Add Lens Flare**
   ```
   - Directional Light → Details
   - Light Shafts: Enabled
   - Lens Flare: ✓
   - Intensity: 1.0-2.0
   ```

4. **Post Process Settings**
   ```
   - Lens Flares enabled in PP Volume
   - Bloom enabled (for star glow)
   ```

### Problem: Planets Too Small or Too Large

**Symptoms:**
- Planets invisible (too small)
- Or fill entire screen (too large)

**Solutions:**

1. **Scale Adjustment**
   ```
   - Select planet in level
   - Scale values to adjust:
     - Too small: Increase (e.g., 100 → 500)
     - Too large: Decrease (e.g., 5000 → 1000)
   - Try: Earth = 800, Moon = 200
   ```

2. **Distance Adjustment**
   ```
   - May be distance, not scale
   - Move planets farther: 100,000-1,000,000 units
   - Space scale is huge
   ```

3. **Camera FOV**
   ```
   - Camera → Field of View
   - Default: 90
   - Wider (100-110): Planets appear smaller
   - Narrower (70-80): Planets appear larger
   ```

### Problem: Lighting Looks Flat or Wrong

**Symptoms:**
- No shadows
- Everything too bright or too dark
- No atmosphere

**Solutions:**

1. **Rebuild Lighting**
   ```
   - Build → Build Lighting Only
   - Production quality (not preview)
   - Wait for completion
   ```

2. **Check Lightmap Resolution**
   ```
   - Static meshes need lightmaps
   - Select mesh → Details
   - Lightmap Resolution: 64-256 (higher = better)
   ```

3. **Add Sky Light**
   ```
   - Place Actors → Sky Light
   - Intensity: 0.1-0.5 (for space ambience)
   - Source Type: SLS Specified Cubemap (if available)
   ```

4. **Adjust Post Process**
   ```
   - Exposure: Manual mode
   - Compensation: 0.5-1.5
   - Auto Exposure: Disabled (for consistent look)
   ```

5. **Add Atmosphere** (for planets)
   ```
   - Research: Exponential Height Fog
   - Or: Custom atmosphere shader
   - Fresnel effect on planet material
   ```

---

## Build and Compilation Errors

### Problem: "Failed to Compile" Blueprint Errors

**Symptoms:**
- Red errors in blueprint
- Can't save or play

**Solutions:**

1. **Read Error Message**
   ```
   - Click error in Compiler Results
   - Usually indicates:
     - Missing variable
     - Wrong pin type
     - Disconnected node
   ```

2. **Common Fixes:**
   ```
   - Verify all nodes connected
   - Check variable types match (Float → Float, etc.)
   - Remove orphaned nodes (select all, compile, delete orphans)
   - Ensure execution pins connected (white arrows)
   ```

3. **Missing References**
   ```
   - If variables show "Invalid" or "None"
   - Right-click → Refresh Node
   - Or delete and recreate node
   ```

4. **Revert Changes**
   ```
   - Edit → Undo until errors gone
   - Or close without saving
   - Reopen and try again
   ```

### Problem: Lighting Build Fails

**Symptoms:**
- Build Lighting errors
- "Lighting needs to be rebuilt" warning persists

**Solutions:**

1. **Fix Lightmap Errors**
   ```
   - Check error messages
   - Usually: Overlapping UVs
   - Select mesh → Static Mesh Editor
   - UV Channel 1 → Generate Lightmap UVs
   - Save and rebuild lighting
   ```

2. **Reduce Lightmap Resolution**
   ```
   - If build too slow or fails
   - Lower resolution: 256 → 128 → 64
   - Trade quality for speed/stability
   ```

3. **Check Lightmass Settings**
   ```
   - World Settings → Lightmass
   - Quality: Preview (for testing)
   - Quality: Production (for final)
   ```

4. **Clear Lighting Cache**
   ```
   - Build → Build Lighting → Delete cached lighting data
   - Then rebuild
   ```

---

## Getting Help

If problems persist:

1. **Check Logs**
   ```
   - Window → Developer Tools → Output Log
   - Look for error messages
   - Search online for specific errors
   ```

2. **UE Forums/AnswerHub**
   ```
   - Post specific error messages
   - Include:
     - UE version (5.6)
     - Steps to reproduce
     - Screenshots
   ```

3. **Project Discord/Community**
   ```
   - Ask in SubspaceUE community
   - Others may have solved similar issues
   ```

4. **Documentation**
   ```
   - Unreal Engine docs: docs.unrealengine.com
   - Search for specific features
   - Many tutorials available
   ```

---

## Quick Fixes Reference

| Problem | Quick Fix |
|---------|-----------|
| Black planets | Check material assigned, rebuild lighting |
| Fall through floor | Regenerate collision, raise player start |
| Too dark interior | Add more lights (5000 intensity) |
| Controls don't work | Check Input bindings, GameMode setup |
| Low FPS | Lower texture res, reduce lights, LODs |
| Ship too shiny | Increase roughness to 0.5-0.7 |
| Normal maps inverted | Disable sRGB, set compression to Normalmap |
| Can't see stars | Add skybox actor, check bloom settings |
| Blueprint errors | Check all connections, refresh nodes |
| Long load times | Reduce asset count, enable async loading |

---

**Document Version:** 1.0  
**Last Updated:** 2026-01-08  
**For:** Sol-TestingGrounds Implementation

---

**Pro Tip:** Save frequently! Before making major changes, save your level and project. If something breaks, you can File → Revert to Previous Version.

Most issues can be solved by carefully checking settings and connections. Take it step by step, and don't be afraid to experiment. Worst case, you can always start a section over. Good luck!
