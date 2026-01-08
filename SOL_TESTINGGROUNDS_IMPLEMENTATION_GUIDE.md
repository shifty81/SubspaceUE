# Sol-TestingGrounds Implementation Guide

## Overview

This guide will walk you through setting up the **Sol-TestingGrounds** sector as your first spawn location in SubspaceUE. This sector features a high-resolution solar system with Earth, Moon, and other planets, and uses the spaceship-5 model as the player's starting ship.

**What You'll Learn:**
- How to import the Solar System assets into Unreal Engine 5.6
- How to set up the spaceship-5 as your player ship
- How to configure spawn points and game modes
- How to generate interior spaces for your ship
- Best practices for level building in space environments

**Time Required:** 4-6 hours for complete setup

---

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Asset Overview](#asset-overview)
3. [Phase 1: Importing Solar System Assets](#phase-1-importing-solar-system-assets)
4. [Phase 2: Setting Up the Level](#phase-2-setting-up-the-level)
5. [Phase 3: Importing the Starting Ship](#phase-3-importing-the-starting-ship)
6. [Phase 4: Creating Ship Interior](#phase-4-creating-ship-interior)
7. [Phase 5: Configuring Spawn and GameMode](#phase-5-configuring-spawn-and-gamemode)
8. [Phase 6: Testing and Polish](#phase-6-testing-and-polish)
9. [Troubleshooting](#troubleshooting)
10. [Next Steps](#next-steps)

---

## Prerequisites

Before starting, ensure you have:

- [ ] **Unreal Engine 5.6** installed and working
- [ ] **SubspaceUE project** opening successfully
- [ ] **Solar System assets** located at `GameData/Assets/Models/Solar Systems/Sol-TestingGrounds/`
- [ ] **spaceship-5 assets** extracted from `GameData/spaceship-5.zip`
- [ ] Basic familiarity with Unreal Editor (navigation, placing actors)
- [ ] At least 30GB free disk space for imported assets

**New to Unreal Engine?** Check out these resources first:
- [Unreal Engine 5.6 Quick Start Guide](https://docs.unrealengine.com/5.6/en-US/quick-start-guide/)
- [SubspaceUE's SPACE_SCENE_QUICK_START.md](SPACE_SCENE_QUICK_START.md)

---

## Asset Overview

### Solar System Assets

**Location:** `GameData/Assets/Models/Solar Systems/Sol-TestingGrounds/`

**Contents:**
- `source/Earth&Moon.fbx` - High-resolution Earth and Moon model (947KB)
- `textures/` - Planet textures including:
  - Earth: Albedo, Normal, Roughness
  - Moon: Albedo, Normal
  - Jupiter: Albedo, Alpha, Normal
  - Mars: Albedo, Normal
  - Mercury: Albedo, Emissive, Normal
  - Neptune, Pluto, Saturn with respective textures

**What It Includes:**
This is a high-quality solar system model suitable for a testing/development sector. It provides realistic planets with PBR textures.

### Spaceship-5 Assets

**Location:** `GameData/spaceship-5-extracted/` (after extraction)

**Contents:**
- `source/p_116_Spaceship_001.blend` - Blender source file (45MB)
- `textures/` - Ship textures:
  - BaseColor (22MB) - Main color/diffuse texture
  - Normal (11MB) - Surface detail
  - Metallic (3.1MB) - Metal/roughness map
  - Emissive (923KB) - Glowing elements

**Ship Style:**
This is a medium-sized sci-fi spaceship with detailed textures suitable for player control. It has a sleek, modern design.

---

## Phase 1: Importing Solar System Assets

### Step 1.1: Create Content Folder Structure

1. **Open Unreal Editor**
   ```
   Navigate to your SubspaceUE project folder
   Double-click SubspaceUE.uproject
   Wait for the editor to load (first time may take 5-10 minutes)
   ```

2. **Create Content Folders**
   - Open Content Browser (Ctrl+Space if not visible)
   - Right-click in Content Browser → New Folder → Name it `SolTestingGrounds`
   - Inside `SolTestingGrounds`, create subfolders:
     - `Maps` (for the level)
     - `SolarSystem` (for planets)
     - `Spaceships` (for ships)
     - `Materials` (for custom materials)
     - `Textures` (for imported textures)

### Step 1.2: Import Solar System FBX

1. **Import the Earth & Moon Model**
   - In Content Browser, navigate to `Content/SolTestingGrounds/SolarSystem`
   - Click Import button (or drag the FBX file directly)
   - Browse to: `GameData/Assets/Models/Solar Systems/Sol-TestingGrounds/source/Earth&Moon.fbx`
   - In the import dialog, configure:
     ```
     Import Meshes: ✓ Enabled
     Import Skeletal Meshes: ✗ Disabled
     Import Materials: ✓ Enabled
     Import Textures: ✓ Enabled
     Transform:
       - Import Uniform Scale: 1.0 (adjust if needed)
       - Convert Scene: ✓ Enabled
       - Force Front XAxis: ✓ Enabled
     Mesh:
       - Combine Meshes: ✗ Disabled (keep separate)
       - Generate Lightmap UVs: ✓ Enabled
     ```
   - Click **Import All**

2. **Verify Import**
   - You should see static mesh(es) appear in the folder
   - Double-click the mesh to preview it
   - Check that geometry looks correct

### Step 1.3: Import Planet Textures

1. **Batch Import Textures**
   - In Content Browser, navigate to `Content/SolTestingGrounds/Textures`
   - Click Import
   - Navigate to: `GameData/Assets/Models/Solar Systems/Sol-TestingGrounds/textures/`
   - Select ALL texture files (Ctrl+A)
   - Click Open
   - In import settings:
     ```
     Texture Group: World
     sRGB: ✓ Enabled (for Albedo/Color textures)
     Compression: Default (DXT1/5)
     Mip Gen Settings: FromTextureGroup
     ```
   - For Normal maps (files with "Normal" in name):
     - After import, double-click each normal map
     - In texture editor, set:
       - sRGB: ✗ Disabled
       - Compression Settings: Normalmap
   - Click **Import All**

2. **Organize Textures by Planet**
   - Create subfolders for each planet: Earth, Moon, Jupiter, Mars, etc.
   - Move respective textures into their folders for organization

### Step 1.4: Create Planet Materials

Now we'll create materials for each planet using the imported textures.

#### Creating Earth Material

1. **Create Material**
   - Navigate to `Content/SolTestingGrounds/Materials`
   - Right-click → Material → Name it `M_Earth`
   - Double-click to open Material Editor

2. **Set Up Material Graph**
   ```
   Basic Setup:
   - Shading Model: Default Lit
   - Blend Mode: Opaque
   - Two Sided: ✗ Disabled
   
   Connect textures:
   1. Drag EarthAlbedo texture into graph
      - Connect RGB output → Base Color input
   
   2. Drag EarthNormal texture into graph
      - Connect RGB output → Normal input
   
   3. Drag EarthRoughness texture into graph
      - Connect R channel → Roughness input
   
   4. (Optional) Add parameters for tweaking:
      - Add Scalar Parameter: EmissiveStrength (default: 0.0)
      - Multiply with a constant color (dark blue/black)
      - Connect to Emissive Color
   ```

3. **Save and Apply**
   - Click Save
   - Close Material Editor

#### Creating Moon Material

Follow the same process as Earth, using:
- MoonAlbedo → Base Color
- MoonNormal → Normal
- Higher roughness value (Moon is less shiny)

#### Creating Other Planet Materials

Repeat for:
- **Jupiter**: Use JupiterAlbedo, JupiterNormal, JupiterAlpha (for transparency if needed)
- **Mars**: Use MarsAlbedo, MarsNormal
- **Mercury**: Use MercuryAlbedo, MercuryNormal, MercuryEmissive (for heat glow)
- **Neptune, Pluto, Saturn**: Similar approach

**Pro Tip:** Create a master material `M_Planet_Master` with parameters, then create Material Instances for each planet. This makes tweaking easier.

---

## Phase 2: Setting Up the Level

### Step 2.1: Create New Level

1. **Create the Map**
   - File → New Level
   - Choose **Empty Level** (we want to start from scratch for space)
   - Save immediately: `Content/SolTestingGrounds/Maps/SolTestingGrounds_Main`

2. **Add Essential Actors**
   
   Space levels need special setup:
   
   **a) Player Start**
   - Place Actors panel → search "Player Start"
   - Drag into viewport
   - Position at: Location (0, 0, 0) for now (we'll adjust later)
   
   **b) Lighting Setup**
   
   Since we're in space, we need a directional light for the sun:
   - Place Actors → Lights → Directional Light
   - Position doesn't matter (directional lights affect whole scene)
   - Set properties:
     ```
     Light:
       - Intensity: 15.0 (space is very bright near sun)
       - Light Color: Slight yellow (R: 1.0, G: 0.98, B: 0.95)
       - Temperature: 5778 (Sun's actual temperature in Kelvin)
       - Source Angle: 0.5 (makes soft shadows)
     
     Atmosphere and Cloud:
       - Atmosphere Sun Light: ✓ Enabled
       - Cast Cloud Shadows: ✗ Disabled (no clouds in space)
     ```
   - Rotate to desired sun direction (e.g., rotation: -45°, 30°, 0°)
   
   **c) Post Process Volume**
   - Place Actors → Volumes → Post Process Volume
   - In Details panel, check "Infinite Extent (Unbound)"
   - Configure for space environment:
     ```
     Exposure:
       - Metering Mode: Manual
       - Exposure Compensation: 0.5
       - Min/Max Brightness: 0.1 / 20.0
     
     Color Grading:
       - Saturation: 1.1 (slightly more vibrant)
       - Contrast: 1.05
       - Shadows: Slight blue tint (0.0, 0.0, 0.05)
     
     Bloom:
       - Intensity: 1.0
       - Threshold: 1.5
       - Size Scale: 8.0
     
     Lens Flares:
       - Intensity: 1.0 (for sun glare)
     
     Ambient Occlusion:
       - Intensity: 0.3 (subtle)
     ```

### Step 2.2: Add Skybox/Space Background

You have two options here:

#### Option A: Use Existing SpaceSkyboxActor (if available)

If your project has `SpaceSkyboxActor`:
- Search in Place Actors for "SpaceSkyboxActor"
- Drag into level
- Position at (0, 0, 0)
- In Details, set:
  ```
  Skybox Radius: 1000000.0 (very large)
  Star Brightness: 1.5
  Star Density: 0.6
  ```

#### Option B: Create Simple Skybox Sphere

1. Add a Sphere static mesh
2. Scale it huge: (1000000, 1000000, 1000000)
3. Create a skybox material:
   - Unlit shading model
   - Two-sided
   - Add starfield texture or procedural stars
4. Apply material to sphere
5. Invert normals by setting scale: (-1000000, 1000000, 1000000)

### Step 2.3: Position Solar System Objects

Now let's add our planets!

#### Space Scale Considerations

In Unreal Engine, 1 unit = 1 cm by default. For space scenes:
- Use large scale values
- Maintain realistic relative sizes and distances
- Balance realism with gameplay visibility

**Recommended Scale:**
- Earth diameter: ~100,000 units (1km in game)
- Moon diameter: ~27,000 units
- Distance Earth-Moon: ~3,000,000 units (30km in game)

#### Placing Earth

1. **Add Earth to Level**
   - Find your Earth static mesh in Content Browser
   - Drag into viewport
   - Position: (0, 0, 0) - Center of the system for now
   - Scale: (800, 800, 800) - Adjust based on imported model size

2. **Apply Earth Material**
   - Select Earth mesh in viewport
   - In Details panel → Materials
   - Element 0 → Select `M_Earth` material

3. **Enable Rotation (Optional)**
   - Select Earth
   - Open Level Blueprint (Blueprints menu → Open Level Blueprint)
   - Add event:
     ```
     Event Tick
       → Get Actor (Earth reference)
       → Add Actor Local Rotation
         → Delta Rotation: (0, 0, 0.01) - Slow rotation
     ```

#### Placing Moon

1. **Add Moon Mesh**
   - Drag Moon mesh to viewport
   - Position relative to Earth: (300000, 0, 0) - 3km away
   - Scale: (200, 200, 200) - About 1/4 size of Earth
   - Apply `M_Moon` material

#### Placing Other Planets (Optional)

For a more complete system:
- **Mercury**: Position (-500000, 0, 0), Scale (100, 100, 100)
- **Venus**: Position (-800000, 300000, 0), Scale (300, 300, 300)
- **Mars**: Position (600000, 400000, 0), Scale (250, 250, 250)
- **Jupiter**: Position (1500000, 0, 0), Scale (3000, 3000, 3000)
- **Saturn**: Position (2000000, -500000, 0), Scale (2500, 2500, 2500)

**Note:** These are compressed distances for gameplay. Real solar system scale would be impractical!

### Step 2.4: Add Space Stations (Optional)

If you have station assets:
- Place near Earth or Moon
- Scale appropriately (100-500 units typical)
- Add lights for visibility

### Step 2.5: Add Asteroid Field (Optional)

Create visual interest:
1. Create Blueprint: `BP_AsteroidField`
2. Use construction script to spawn random asteroids
3. Place in level between planets

---

## Phase 3: Importing the Starting Ship

### Step 3.1: Export FBX from Blender (If Needed)

The spaceship-5 comes as a .blend file. We need FBX format for Unreal Engine.

**Option A: If you have Blender installed:**

1. **Open Blender** (v3.0+ recommended)
2. **Open the ship file:**
   - File → Open
   - Navigate to: `GameData/spaceship-5-extracted/source/p_116_Spaceship_001.blend`
3. **Check the model:**
   - Verify it loads correctly
   - Check scale (should be in meters)
   - Note: 1 Blender unit = 100 Unreal units typically
4. **Export as FBX:**
   - File → Export → FBX (.fbx)
   - Save to: `GameData/spaceship-5-extracted/p_116_Spaceship_001.fbx`
   - Export settings:
     ```
     Include:
       - Selected Objects: ✗ (export all)
       - Object Types: Mesh, Armature (if rigged)
       - Apply Modifiers: ✓
     
     Transform:
       - Scale: 1.00
       - Forward: -Y Forward
       - Up: Z Up
       - Apply Unit: ✓
       - Apply Transform: ✓
     
     Geometry:
       - Smoothing: Face
       - Export Subdivision Surface: ✓
     ```
   - Click **Export FBX**

**Option B: If you don't have Blender:**

You can use Blender's free online converter or install Blender (it's free and open-source):
- Download Blender: https://www.blender.org/download/
- Or use online conversion services (search "blend to fbx converter")

### Step 3.2: Import Spaceship to Unreal

1. **Import FBX**
   - In Content Browser, navigate to `Content/SolTestingGrounds/Spaceships`
   - Click Import
   - Select: `GameData/spaceship-5-extracted/p_116_Spaceship_001.fbx`
   - Import settings:
     ```
     Mesh:
       - Import Mesh: ✓
       - Skeletal Mesh: ✗ (unless rigged)
       - Import Content Type: Geometry and Skinning Weights
       - Combine Meshes: ✓ (single mesh)
       - Generate Lightmap UVs: ✓
       - Generate Missing Collision: ✓
     
     Transform:
       - Import Uniform Scale: 100.0 (Blender to UE scale)
       - Convert Scene: ✓
     
     Material:
       - Import Materials: ✓
       - Import Textures: ✓
     ```
   - Click **Import**

2. **Verify Import**
   - Double-click the imported mesh to open Static Mesh Editor
   - Check:
     - Geometry looks correct
     - Scale is reasonable (10-50 meters long typical for small ship)
     - Has collision (green wireframe)
   - If scale is wrong, you can adjust:
     - Edit → Static Mesh Settings → Build Scale: (100, 100, 100)

### Step 3.3: Import Ship Textures

1. **Import Texture Files**
   - Navigate to `Content/SolTestingGrounds/Spaceships/Textures`
   - Import all textures from: `GameData/spaceship-5-extracted/textures/`
   - Files to import:
     - `p_116_Spaceship_001_Spaceship_BaseColor-*.png`
     - `p_116_Spaceship_001_Spaceship_Normal.png`
     - `p_116_Spaceship_001_Spaceship_Metallic-*.png`
     - `p_116_Spaceship_001_Spaceship_Emissive.png`

2. **Configure Texture Import Settings**
   - BaseColor: sRGB ✓, Compression: Default
   - Normal: sRGB ✗, Compression: Normalmap
   - Metallic: sRGB ✗, Compression: Masks
   - Emissive: sRGB ✓, Compression: Default

### Step 3.4: Create Ship Material

1. **Create Master Material**
   - Navigate to `Content/SolTestingGrounds/Spaceships/Materials`
   - Right-click → Material → Name: `M_Spaceship_001`
   - Double-click to open

2. **Build Material Graph**
   ```
   Material Settings:
   - Shading Model: Default Lit
   - Blend Mode: Opaque
   - Two Sided: ✗
   
   Texture Setup:
   1. BaseColor texture → Base Color pin
   
   2. Normal texture → Normal pin
   
   3. Metallic texture:
      - R channel → Metallic pin (metal mask)
      - G or A channel → Roughness pin (smoothness)
   
   4. Emissive texture:
      - Multiply by Emissive Strength parameter (default: 2.0)
      - Connect to Emissive Color pin
   
   5. (Optional) Add detail:
      - Multiply BaseColor by brightness parameter
      - Add AO (Ambient Occlusion) if available
   ```

3. **Create Material Instance**
   - Right-click on `M_Spaceship_001` → Create Material Instance
   - Name: `MI_Spaceship_001`
   - This allows tweaking without recompiling

4. **Apply to Ship Mesh**
   - Open the spaceship static mesh
   - In Details → Static Mesh Settings → LOD 0 → Material Slots
   - Element 0 → `MI_Spaceship_001`
   - Save

---

## Phase 4: Creating Ship Interior

The spaceship-5 model is an external hull. We need to create an interior for the player.

### Step 4.1: Interior Design Approach

You have several options:

#### Option A: Simple Box Interior (Quickest)

Good for prototyping:

1. **Create Interior Space**
   - Open the spaceship static mesh
   - Note the internal dimensions (view from inside)
   - In level, add a Box brush or static mesh cube
   - Scale to fit inside hull: e.g., (400, 800, 200) units
   - Position at ship's center

2. **Create Interior Material**
   - Make material similar to ship textures
   - Use paneled metal look
   - Add emissive strips for lighting

3. **Add Interior Props**
   - Pilot seat/cockpit area (front)
   - Control panels (walls)
   - Corridors (if space allows)
   - Cargo bay (rear)

#### Option B: Modular Interior Kit (Recommended)

Use Unreal Marketplace assets:

1. **Download Interior Kit**
   - Search Marketplace for: "Sci-Fi Interior" or "Spaceship Interior"
   - Recommended: "Modular Sci-Fi: Season 1" (often free/on sale)
   - Add to project

2. **Build Interior**
   - Use modular pieces (floor, wall, ceiling panels)
   - Snap pieces together inside ship hull
   - Create functional spaces:
     - **Cockpit** (front 20%)
     - **Living quarters** (middle 30%)
     - **Engineering/Cargo** (rear 50%)

3. **Add Functional Elements**
   - Computer terminals (interaction points)
   - Doors between sections
   - Lights (point lights on ceiling)
   - Props (containers, seats, equipment)

#### Option C: Custom Blueprint Interior (Advanced)

For dynamic generation:

1. **Create Blueprint: BP_ShipInterior**
2. **Add Components:**
   - Static mesh components for sections
   - Light components
   - Collision components
3. **Construction Script:**
   - Procedurally place interior modules
   - Based on ship size
   - Random variations

### Step 4.2: Interior Lighting

Crucial for atmosphere:

1. **Ambient Interior Light**
   - Add Point Lights inside ship
   - Color: Cool white (R: 0.9, G: 0.95, B: 1.0)
   - Intensity: 2000-5000
   - Attenuation Radius: 1000-2000
   - Place every 500-1000 units

2. **Accent Lights**
   - Emissive strips on walls (in materials)
   - Colored lights for different areas:
     - Cockpit: Blue/cyan
     - Living: Warm white
     - Engineering: Orange/red
   - Spot lights for specific areas

3. **Emergency/Warning Lights**
   - Red flashing lights (blueprint controlled)
   - Place near doors, hazards

### Step 4.3: Player Spawn Location

Inside the ship interior:

1. **Place Player Start**
   - Drag Player Start actor into ship interior
   - Position in cockpit or main corridor
   - Rotation: Facing forward (ship direction)
   - Ensure no collision overlap with geometry

2. **Add Spawn Effect (Optional)**
   - Particle system for materialization effect
   - Sound effect for spawn

---

## Phase 5: Configuring Spawn and GameMode

### Step 5.1: Create Game Mode for Sol-TestingGrounds

1. **Create GameMode Blueprint**
   - Content Browser → Blueprints folder
   - Right-click → Blueprint Class → Game Mode Base
   - Name: `GM_SolTestingGrounds`
   - Open it

2. **Configure GameMode**
   ```
   Classes:
   - Default Pawn Class: (your spaceship pawn, or create one)
   - Player Controller Class: ASubspacePlayerController
   - HUD Class: ASubspaceHUD
   - Player Start Class: Player Start
   
   Variables:
   - Starting Location: "Sol-TestingGrounds"
   - Spawn Protection Time: 10.0 seconds
   ```

3. **Add Spawn Logic (Optional)**
   - Event BeginPlay:
     - Initialize sector data
     - Spawn initial AI ships
     - Set up objectives

### Step 5.2: Create Player Spaceship Pawn

If you don't have one already:

1. **Create Pawn Blueprint**
   - Right-click → Blueprint Class → Pawn
   - Name: `BP_PlayerSpaceship_001`
   - Open it

2. **Add Components**
   ```
   Component Hierarchy:
   - Root: Scene Component
     - StaticMesh (your spaceship mesh)
     - Camera (Spring Arm + Camera)
     - Movement Component
     - Collision (Sphere or Box)
   ```

3. **Set Up Camera**
   - Add Spring Arm Component
   - Attach Camera Component to Spring Arm
   - Spring Arm Settings:
     - Target Arm Length: 1000-2000 (third-person distance)
     - Enable Camera Lag: ✓
     - Camera Lag Speed: 3.0
   - Or attach directly to root for first-person

4. **Add Movement**
   - Use Floating Pawn Movement component
   - Or create custom 6DOF movement:
     ```
     Input Axis:
     - MoveForward → Add Force Forward
     - MoveRight → Add Force Right
     - MoveUp → Add Force Up
     - RotatePitch → Add Angular Velocity
     - RotateYaw → Add Angular Velocity
     - RotateRoll → Add Angular Velocity
     ```

5. **Configure Physics**
   - Enable Simulate Physics on Static Mesh
   - Mass: 10000-50000 (ship mass in kg)
   - Linear Damping: 1.0 (air resistance/drag)
   - Angular Damping: 5.0 (rotation resistance)

### Step 5.3: Set Level GameMode

1. **Open Level Settings**
   - Window → World Settings
   - Or click Settings icon in toolbar → World Settings

2. **Set GameMode Override**
   - GameMode Override: `GM_SolTestingGrounds`
   - Default Pawn Class: `BP_PlayerSpaceship_001`

3. **Save Level**

### Step 5.4: Update Project Settings

1. **Set Default Map**
   - Edit → Project Settings
   - Maps & Modes
   - Default Maps → Editor Startup Map: `SolTestingGrounds_Main`
   - Default Maps → Game Default Map: `SolTestingGrounds_Main`

2. **Input Bindings**
   - Project Settings → Input
   - Add Action Mappings:
     - Thrust: W, S (Forward/Back)
     - Strafe: A, D (Left/Right)
     - Ascend: Space
     - Descend: Left Shift
     - Fire: Left Mouse Button
     - Target: Right Mouse Button
   - Add Axis Mappings:
     - Pitch: Mouse Y (scale: -1.0)
     - Yaw: Mouse X (scale: 1.0)
     - Roll: Q (-1.0), E (1.0)

---

## Phase 6: Testing and Polish

### Step 6.1: Initial Testing

1. **PIE (Play In Editor) Test**
   - Click Play button (Alt+P)
   - Check:
     - Player spawns in correct location (inside ship)
     - Can see interior properly lit
     - Controls respond (movement, rotation)
     - Collision works (can't fall through ship)
     - Camera behaves correctly

2. **Debug View Modes**
   - Press F5 for lighting debug
   - Press F7 for collision view
   - Check for:
     - Missing lighting
     - Collision gaps
     - Z-fighting (flickering surfaces)

### Step 6.2: Performance Optimization

1. **Check Frame Rate**
   - Type in console (` key): `stat fps`
   - Target: 60+ FPS
   - If low:
     - Reduce planet polygon count
     - Lower texture resolutions
     - Adjust post-process settings

2. **Optimize Meshes**
   - Enable LODs (Level of Detail)
   - Set draw distances:
     - Ships: 100,000 units
     - Planets: 500,000 units
   - Use instanced static meshes for repeated objects

3. **Light Optimization**
   - Use mostly static lights (bake lighting)
   - Limit stationary/movable lights: 3-5 max
   - Set attenuation radius appropriately

### Step 6.3: Visual Polish

1. **Refine Materials**
   - Adjust material parameters for visual appeal
   - Add subtle animations (emissive flicker)
   - Ensure consistent style

2. **Add Visual Effects**
   - Ship engine glow (emissive material)
   - Thruster particles (Niagara system)
   - Planet atmosphere shader (Fresnel effect)
   - Lens flares on sun

3. **Audio (Optional)**
   - Ambient space sound (subtle hum)
   - Engine sounds (looping)
   - Interior sounds (beeps, hum)

### Step 6.4: Create Documentation

Document your level for future reference:

1. **Level Overview Document**
   - Object locations and scales
   - Material settings used
   - Lighting configuration
   - Performance benchmarks

2. **Screenshot Reference**
   - Take screenshots of key views
   - Save to documentation folder

---

## Troubleshooting

### Common Issues and Solutions

#### Issue: Ship Mesh Not Visible After Import

**Symptoms:**
- Mesh imported but appears invisible or black

**Solutions:**
1. Check material is assigned to mesh
2. Verify textures imported correctly (check sRGB settings)
3. Check mesh scale - may be too small or large
4. Look at mesh normals (may be inverted)
5. Rebuild lighting (Build → Build Lighting Only)

#### Issue: Player Falls Through Ship

**Symptoms:**
- Player spawns then immediately falls down

**Solutions:**
1. Ensure ship has collision:
   - Open static mesh editor
   - Collision → Generate Complex Collision
   - Or add simple collision primitive
2. Check Player Start isn't below ship floor
3. Verify Simulate Physics on player is configured correctly
4. Check collision settings match (both set to Block)

#### Issue: Interior Too Dark

**Symptoms:**
- Can't see inside ship, everything black

**Solutions:**
1. Add more Point Lights inside ship
2. Increase light intensity (try 5000-10000)
3. Build lighting (Build → Build Lighting Only)
4. Check Post Process Volume exposure settings
5. Add emissive materials to surfaces
6. Use Unbound Post Process Volume with higher exposure

#### Issue: Performance Is Poor (Low FPS)

**Symptoms:**
- Frame rate below 30 FPS, stuttering

**Solutions:**
1. Check planet mesh complexity (may need to decimate)
2. Lower texture resolutions (use 2K instead of 4K)
3. Reduce number of lights (max 5-10 dynamic)
4. Disable expensive post-processing (motion blur, DOF)
5. Set appropriate draw distances
6. Enable texture streaming
7. Use LODs on all meshes

#### Issue: Planets Look Flat or Wrong

**Symptoms:**
- Planets don't look spherical or textures wrong

**Solutions:**
1. Check UV mapping on mesh (may need to re-export)
2. Ensure using appropriate material
3. Add normal maps for surface detail
4. Check texture coordinates in material
5. Add Fresnel effect for atmosphere rim
6. Verify correct texture type (normal map needs compression setting)

#### Issue: Controls Don't Work

**Symptoms:**
- Input has no effect on ship

**Solutions:**
1. Check Input Bindings in Project Settings
2. Verify GameMode assigns correct pawn class
3. Check Pawn has input enabled: "Auto Possess Player" → Player 0
4. Ensure movement component is properly configured
5. Test with different input device

#### Issue: Spaceship Material Looks Wrong

**Symptoms:**
- Materials are too shiny, wrong color, or missing emissive

**Solutions:**
1. Verify texture assignments in material
2. Check metallic/roughness values (may be swapped)
3. Adjust emissive multiplier (try 1.0-5.0)
4. Ensure sRGB is correct on each texture
5. Create Material Instance to tweak values
6. Check texture channels (R, G, B, A) connected correctly

---

## Next Steps

Congratulations! You now have a working Sol-TestingGrounds sector. Here's what to do next:

### Immediate Enhancements

1. **Add More Details**
   - More planets/moons
   - Asteroid fields
   - Space stations
   - Debris fields

2. **Improve Gameplay**
   - Add AI ships to interact with
   - Create objectives/missions
   - Add resource gathering points
   - Implement trading posts

3. **Polish Visuals**
   - Better skybox with nebulae
   - Improved lighting (volumetric fog)
   - Particle effects (thruster trails, explosions)
   - HUD/UI elements

### Expanding the Game

1. **Create Additional Sectors**
   - Use this as a template
   - Create different environments (asteroid belt, nebula, space station)
   - Link sectors with jump gates or warp points

2. **Add More Ships**
   - Import additional ship models
   - Create ship selection menu
   - Different ship classes (fighter, cargo, explorer)

3. **Build Game Systems**
   - Combat system
   - Trading/economy
   - Progression/upgrades
   - Multiplayer networking

### Learning Resources

- **Unreal Engine Documentation**: [docs.unrealengine.com](https://docs.unrealengine.com)
- **Space Game Tutorials**: Search YouTube for "UE5 space game"
- **SubspaceUE Guides**: Check other MD files in this repo
- **Community Forums**: Unreal Engine forums, Reddit r/unrealengine

### Get Help

If you get stuck:
1. Check [TROUBLESHOOTING.md](TROUBLESHOOTING.md) in this repo
2. Review Unreal Engine documentation
3. Search Unreal Engine AnswerHub
4. Ask in project Discord/community
5. Open an issue on GitHub repo

---

## Appendix

### A. Recommended Asset Packs

For expanding your space environment:

- **Sci-Fi Interiors**: Modular Sci-Fi Season 1 (Epic Marketplace)
- **Space Skyboxes**: Space Skybox Collection (various)
- **Planets**: Space Scene for UE5 (ArtStation)
- **Ships**: Various on CGTrader, TurboSquid, Fab
- **Effects**: Niagara VFX packs for thrusters, explosions

### B. Useful Console Commands

Press ` (backtick) to open console:

```
stat fps          - Show frame rate
stat unit         - Show detailed frame timing
stat gpu          - Show GPU performance
stat rhi          - Render hardware interface stats
r.ScreenPercentage 100  - Rendering resolution (lower for performance)
r.SetRes 1920x1080w     - Set window resolution
show collision    - Toggle collision visualization
freezerendering   - Pause rendering for inspection
```

### C. Keyboard Shortcuts

While editing:

- **F** - Focus on selected object
- **G** - Toggle game view (hides editor gizmos)
- **Alt+P** - Play in editor
- **F8** - Eject from pawn (free cam during play)
- **Ctrl+Space** - Content Browser
- **Ctrl+Shift+O** - World Outliner
- **End** - Drop to floor (selected object)
- **Alt** + drag - Duplicate object

### D. Further Reading

- [SPACE_SCENE_GENERATION_WITH_STORE_ASSETS.md](SPACE_SCENE_GENERATION_WITH_STORE_ASSETS.md)
- [SPACE_SCENE_QUICK_START.md](SPACE_SCENE_QUICK_START.md)
- [SKYBOX_MATERIAL_GUIDE.md](SKYBOX_MATERIAL_GUIDE.md)
- [CAMERA_AND_VISUAL_IMPROVEMENTS.md](CAMERA_AND_VISUAL_IMPROVEMENTS.md)

---

**Document Version:** 1.0  
**Last Updated:** 2026-01-08  
**Compatible With:** Unreal Engine 5.6, SubspaceUE Project  
**Author:** SubspaceUE Development Team

---

**Need Help?** Don't hesitate to ask questions in the project community or open an issue. Everyone starts somewhere, and level design in Unreal Engine has a learning curve. Take it step by step, and you'll get there!

Good luck, and enjoy building your space game! 🚀
