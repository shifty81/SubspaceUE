# Sol-TestingGrounds - Quick Start Checklist

A condensed, step-by-step checklist for implementing the Sol-TestingGrounds sector with minimal reading.

**Full Guide:** See [SOL_TESTINGGROUNDS_IMPLEMENTATION_GUIDE.md](SOL_TESTINGGROUNDS_IMPLEMENTATION_GUIDE.md) for detailed instructions.

---

## Prerequisites Check

- [ ] Unreal Engine 5.6 installed
- [ ] SubspaceUE project opens successfully
- [ ] Solar System assets in: `GameData/Assets/Models/Solar Systems/Sol-TestingGrounds/`
- [ ] spaceship-5.zip extracted to: `GameData/spaceship-5-extracted/`
- [ ] Blender installed (for FBX export) - Download: https://www.blender.org/download/

**Time Estimate:** 4-6 hours total

---

## Phase 1: Folder Setup (10 minutes)

- [ ] Open SubspaceUE.uproject in Unreal Engine 5.6
- [ ] Open Content Browser (Ctrl+Space)
- [ ] Create folder structure:
  - [ ] `Content/SolTestingGrounds/`
  - [ ] `Content/SolTestingGrounds/Maps/`
  - [ ] `Content/SolTestingGrounds/SolarSystem/`
  - [ ] `Content/SolTestingGrounds/Spaceships/`
  - [ ] `Content/SolTestingGrounds/Materials/`
  - [ ] `Content/SolTestingGrounds/Textures/`

---

## Phase 2: Import Solar System (45 minutes)

### Import Earth & Moon FBX

- [ ] Navigate to `Content/SolTestingGrounds/SolarSystem`
- [ ] Click Import button
- [ ] Select: `GameData/Assets/Models/Solar Systems/Sol-TestingGrounds/source/Earth&Moon.fbx`
- [ ] Import settings:
  - [ ] Import Uniform Scale: 1.0
  - [ ] Convert Scene: ✓
  - [ ] Generate Lightmap UVs: ✓
  - [ ] Combine Meshes: ✗
- [ ] Click Import All
- [ ] Verify mesh appears in folder

### Import Planet Textures

- [ ] Navigate to `Content/SolTestingGrounds/Textures`
- [ ] Click Import
- [ ] Select ALL files from: `GameData/Assets/Models/Solar Systems/Sol-TestingGrounds/textures/`
- [ ] Import all
- [ ] For each Normal map texture:
  - [ ] Double-click texture
  - [ ] Set: sRGB = ✗, Compression = Normalmap
  - [ ] Save

### Create Earth Material

- [ ] Navigate to `Content/SolTestingGrounds/Materials`
- [ ] Right-click → Material → Name: `M_Earth`
- [ ] Double-click to open Material Editor
- [ ] Connect textures:
  - [ ] EarthAlbedo → Base Color
  - [ ] EarthNormal → Normal
  - [ ] EarthRoughness → Roughness
- [ ] Save and close

### Create Moon Material

- [ ] Create Material: `M_Moon`
- [ ] Connect:
  - [ ] MoonAlbedo → Base Color
  - [ ] MoonNormal → Normal
  - [ ] Constant 0.8 → Roughness
- [ ] Save

### Create Other Planet Materials (Optional)

- [ ] Mars material (`M_Mars`)
- [ ] Jupiter material (`M_Jupiter`)
- [ ] Mercury material (`M_Mercury`)

---

## Phase 3: Create Level (30 minutes)

### Create New Level

- [ ] File → New Level → Empty Level
- [ ] Save As: `Content/SolTestingGrounds/Maps/SolTestingGrounds_Main`

### Add Essential Actors

- [ ] **Player Start**:
  - [ ] Place Actors → Player Start
  - [ ] Position at (0, 0, 0) temporarily

- [ ] **Directional Light** (Sun):
  - [ ] Place Actors → Lights → Directional Light
  - [ ] Intensity: 15.0
  - [ ] Color: (1.0, 0.98, 0.95)
  - [ ] Temperature: 5778
  - [ ] Rotation: (-45, 30, 0)

- [ ] **Post Process Volume**:
  - [ ] Place Actors → Volumes → Post Process Volume
  - [ ] Check: Infinite Extent (Unbound)
  - [ ] Set Exposure Compensation: 0.5
  - [ ] Set Bloom Intensity: 1.0

- [ ] **Skybox** (if SpaceSkyboxActor available):
  - [ ] Place SpaceSkyboxActor at (0, 0, 0)
  - [ ] Radius: 1000000
  - [ ] Star Brightness: 1.5

### Add Planets

- [ ] **Earth**:
  - [ ] Drag Earth mesh to viewport
  - [ ] Position: (0, 0, 0)
  - [ ] Scale: (800, 800, 800)
  - [ ] Apply `M_Earth` material

- [ ] **Moon**:
  - [ ] Drag Moon mesh to viewport
  - [ ] Position: (300000, 0, 0)
  - [ ] Scale: (200, 200, 200)
  - [ ] Apply `M_Moon` material

- [ ] **Other Planets** (optional):
  - [ ] Mars: Position (600000, 400000, 0), Scale (250, 250, 250)
  - [ ] Jupiter: Position (1500000, 0, 0), Scale (3000, 3000, 3000)

- [ ] Save Level (Ctrl+S)

---

## Phase 4: Import Spaceship (60 minutes)

### Export FBX from Blender

- [ ] Open Blender
- [ ] File → Open → `GameData/spaceship-5-extracted/source/p_116_Spaceship_001.blend`
- [ ] File → Export → FBX (.fbx)
- [ ] Save to: `GameData/spaceship-5-extracted/p_116_Spaceship_001.fbx`
- [ ] Export settings:
  - [ ] Apply Modifiers: ✓
  - [ ] Scale: 1.00
  - [ ] Forward: -Y Forward
  - [ ] Up: Z Up
- [ ] Export FBX

### Import to Unreal

- [ ] In Content Browser, navigate to `Content/SolTestingGrounds/Spaceships`
- [ ] Click Import
- [ ] Select: `GameData/spaceship-5-extracted/p_116_Spaceship_001.fbx`
- [ ] Import settings:
  - [ ] Import Uniform Scale: 100.0
  - [ ] Combine Meshes: ✓
  - [ ] Generate Lightmap UVs: ✓
  - [ ] Generate Missing Collision: ✓
- [ ] Click Import
- [ ] Verify mesh looks correct

### Import Ship Textures

- [ ] Navigate to `Content/SolTestingGrounds/Spaceships/Textures`
- [ ] Import all files from: `GameData/spaceship-5-extracted/textures/`
- [ ] Set texture properties:
  - [ ] BaseColor: sRGB ✓
  - [ ] Normal: sRGB ✗, Compression = Normalmap
  - [ ] Metallic: sRGB ✗
  - [ ] Emissive: sRGB ✓

### Create Ship Material

- [ ] Navigate to `Content/SolTestingGrounds/Spaceships/Materials`
- [ ] Create Material: `M_Spaceship_001`
- [ ] Connect textures:
  - [ ] BaseColor texture → Base Color
  - [ ] Normal texture → Normal
  - [ ] Metallic texture R channel → Metallic
  - [ ] Metallic texture G/A channel → Roughness
  - [ ] Emissive texture × 2.0 → Emissive Color
- [ ] Save
- [ ] Right-click → Create Material Instance → `MI_Spaceship_001`
- [ ] Open ship mesh
- [ ] Assign `MI_Spaceship_001` to material slot
- [ ] Save

---

## Phase 5: Create Ship Interior (90 minutes)

### Simple Box Interior (Quick Method)

- [ ] In level, add a Cube static mesh
- [ ] Position inside spaceship hull
- [ ] Scale to fit: approximately (400, 800, 200)
- [ ] Create simple interior material:
  - [ ] Material: `M_ShipInterior`
  - [ ] Base Color: Dark gray (0.1, 0.1, 0.1)
  - [ ] Metallic: 0.8
  - [ ] Roughness: 0.4
  - [ ] Add Emissive for panel lines
- [ ] Apply material

### Add Interior Lighting

- [ ] Add Point Lights inside ship:
  - [ ] Cockpit area: 2-3 lights
  - [ ] Main corridor: 3-4 lights
  - [ ] Rear section: 2-3 lights
- [ ] Light settings:
  - [ ] Intensity: 3000-5000
  - [ ] Color: Cool white (0.9, 0.95, 1.0)
  - [ ] Attenuation Radius: 1000

### Position Player Start

- [ ] Move Player Start inside ship
- [ ] Position in cockpit or main area
- [ ] Ensure above floor (not overlapping)
- [ ] Rotate to face forward
- [ ] Test by pressing Alt+P (should spawn inside ship)

---

## Phase 6: Create Player Pawn (45 minutes)

### Create Spaceship Pawn Blueprint

- [ ] Content Browser → Right-click → Blueprint Class → Pawn
- [ ] Name: `BP_PlayerSpaceship_001`
- [ ] Open blueprint

### Add Components

- [ ] Add Static Mesh Component
  - [ ] Mesh: Select spaceship mesh
  - [ ] Enable Simulate Physics: ✓
  - [ ] Mass: 20000
  - [ ] Linear Damping: 1.0
  - [ ] Angular Damping: 5.0

- [ ] Add Spring Arm Component
  - [ ] Attach to Static Mesh
  - [ ] Target Arm Length: 1500
  - [ ] Enable Camera Lag: ✓
  - [ ] Camera Lag Speed: 3.0

- [ ] Add Camera Component
  - [ ] Attach to Spring Arm

- [ ] Add Floating Pawn Movement Component

### Configure Input (Simple Version)

- [ ] In Event Graph, add basic movement:
  ```
  Input Axis MoveForward → Add Movement Input (Forward Vector)
  Input Axis MoveRight → Add Movement Input (Right Vector)
  Input Axis MoveUp → Add Movement Input (Up Vector)
  ```
- [ ] Compile and Save

---

## Phase 7: Configure GameMode (30 minutes)

### Create GameMode Blueprint

- [ ] Right-click → Blueprint Class → Game Mode Base
- [ ] Name: `GM_SolTestingGrounds`
- [ ] Open it
- [ ] Set Default Pawn Class: `BP_PlayerSpaceship_001`
- [ ] Save

### Set Level GameMode

- [ ] Open `SolTestingGrounds_Main` level
- [ ] Window → World Settings
- [ ] GameMode Override: `GM_SolTestingGrounds`
- [ ] Save level

### Update Project Settings

- [ ] Edit → Project Settings
- [ ] Maps & Modes:
  - [ ] Editor Startup Map: `SolTestingGrounds_Main`
  - [ ] Game Default Map: `SolTestingGrounds_Main`

### Configure Input Bindings

- [ ] Project Settings → Input
- [ ] Add Axis Mappings:
  - [ ] MoveForward: W (1.0), S (-1.0)
  - [ ] MoveRight: D (1.0), A (-1.0)
  - [ ] MoveUp: Space (1.0), Left Shift (-1.0)
  - [ ] Pitch: Mouse Y (-1.0)
  - [ ] Yaw: Mouse X (1.0)
  - [ ] Roll: E (1.0), Q (-1.0)
- [ ] Save settings

---

## Phase 8: Testing (30 minutes)

### Initial Test

- [ ] Click Play (Alt+P)
- [ ] Verify:
  - [ ] Player spawns inside ship
  - [ ] Can see interior
  - [ ] Lights work
  - [ ] Movement responds to input
  - [ ] Camera follows ship
  - [ ] No collision issues

### Performance Check

- [ ] Press ` (backtick) to open console
- [ ] Type: `stat fps`
- [ ] Check frame rate (target: 60+ FPS)
- [ ] If low FPS:
  - [ ] Reduce texture resolutions
  - [ ] Lower planet polygon counts
  - [ ] Reduce number of lights

### Debug Views

- [ ] Press F7 to see collision (green wireframes)
- [ ] Verify ship has collision
- [ ] Check player doesn't fall through floor

---

## Phase 9: Polish (Optional, 60 minutes)

### Visual Enhancements

- [ ] Add ship engine glow (emissive material)
- [ ] Add thruster particles (Niagara system)
- [ ] Add planet atmosphere (Fresnel shader)
- [ ] Add lens flare to sun

### Audio (Optional)

- [ ] Add ambient space sound
- [ ] Add engine loop sound
- [ ] Add UI interaction sounds

### Additional Details

- [ ] Add more asteroids
- [ ] Add space stations
- [ ] Add AI ships
- [ ] Add objectives/missions

---

## Final Checklist

- [ ] Player spawns correctly in ship interior
- [ ] All planets visible and textured
- [ ] Ship materials look good
- [ ] Interior is lit and functional
- [ ] Controls work properly
- [ ] Frame rate is acceptable (60+ FPS)
- [ ] No obvious bugs or collision issues
- [ ] Level saved and set as default map
- [ ] Documentation created for future reference

---

## Troubleshooting Quick Reference

| Problem | Quick Fix |
|---------|-----------|
| Can't see inside ship | Add more Point Lights, increase intensity |
| Player falls through floor | Check collision on ship mesh, rebuild collision |
| Controls don't work | Check Input Bindings, verify GameMode settings |
| Low frame rate | Lower texture res, reduce lights, check polygon count |
| Ship invisible/black | Check material assignment, verify textures imported |
| Planets look flat | Add normal maps, check UV mapping |

---

## What's Next?

After completing this checklist, see the full guide for:
- More detailed troubleshooting
- Advanced interior design options
- Creating additional sectors
- Adding gameplay systems
- Performance optimization tips

**Full Guide:** [SOL_TESTINGGROUNDS_IMPLEMENTATION_GUIDE.md](SOL_TESTINGGROUNDS_IMPLEMENTATION_GUIDE.md)

---

**Document Version:** 1.0  
**Last Updated:** 2026-01-08  
**Estimated Time:** 4-6 hours  
**Difficulty:** Beginner to Intermediate

Good luck! 🚀
