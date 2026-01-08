# Ship Interior Generation Guide

## Overview

This guide explains how to create functional, detailed interiors for spaceships in SubspaceUE. It covers both manual and procedural approaches to interior design.

**Target:** Creating interior spaces for the spaceship-5 model and other ship types
**Difficulty:** Intermediate
**Time Required:** 2-4 hours per ship

---

## Table of Contents

1. [Interior Design Principles](#interior-design-principles)
2. [Manual Interior Creation](#manual-interior-creation)
3. [Modular Kit Approach](#modular-kit-approach)
4. [Procedural Generation](#procedural-generation)
5. [Lighting and Materials](#lighting-and-materials)
6. [Functional Elements](#functional-elements)
7. [Best Practices](#best-practices)

---

## Interior Design Principles

### Space Ship Interior Zones

A typical spaceship interior should have distinct functional zones:

1. **Cockpit/Bridge** (10-20% of ship)
   - Pilot/captain seat
   - Control panels
   - Navigation displays
   - Front windows/viewports

2. **Living Quarters** (20-30% of ship)
   - Crew bunks/sleeping areas
   - Recreation area
   - Storage lockers
   - Personal terminals

3. **Engineering/Systems** (20-30% of ship)
   - Power core/reactor
   - Life support systems
   - Repair stations
   - Technical access

4. **Cargo Bay** (30-40% of ship)
   - Storage containers
   - Loading area
   - Resource processing
   - Equipment racks

5. **Corridors/Access** (10-20% of ship)
   - Connecting hallways
   - Doors/airlocks
   - Emergency exits
   - Maintenance shafts

### Scale Considerations

**Unreal Engine Units:** 1 unit = 1 cm

Typical interior dimensions:
- **Ceiling Height:** 250-300 units (2.5-3m)
- **Corridor Width:** 150-200 units (1.5-2m)
- **Doorway:** 100 width × 220 height (1m × 2.2m)
- **Room Size:** 400-800 units wide (4-8m)
- **Character Height:** ~180 units (1.8m)

**Design for Player Movement:**
- Ensure minimum 100 units clearance around player
- Keep important interactive objects at eye level (150-180 units)
- Allow turning radius of 200 units
- Design for third-person camera (needs space behind player)

### Matching Exterior Scale

The spaceship-5 exterior dimensions need to inform interior design:

1. **Measure the ship hull:**
   - Open ship static mesh
   - Check bounds in Details panel
   - Note: X (length), Y (width), Z (height)
   - Example: X=2000, Y=800, Z=400

2. **Calculate usable interior space:**
   - Subtract hull thickness: typically 20-50 units
   - Account for structural elements
   - Leave margins for airlock/doors

3. **Create interior to fit:**
   - Interior should be 80-90% of hull volume
   - Keep some space for hull structure appearance
   - Use LOD/culling for unseen internal structure

---

## Manual Interior Creation

### Method 1: Simple Box Interior (Fastest)

**Best for:** Prototyping, single-room ships, quick iteration

**Steps:**

1. **Create Base Interior Mesh**
   ```
   - Add Cube static mesh to level
   - Position inside ship hull
   - Scale to fit (use ship bounds as guide)
   - Example scale for spaceship-5: (380, 750, 180)
   ```

2. **Hollow Out Interior**
   ```
   - Option A (Modeling Tools):
     - Enable Modeling Tools plugin
     - Use PolyEdit → Extrude Faces (inward)
     - Delete exterior faces
   
   - Option B (Separate Meshes):
     - Create floor plane: (400, 800, 10)
     - Create ceiling plane: (400, 800, 10)
     - Create wall planes: 4 pieces
     - Position to form room
   ```

3. **Add Internal Structure**
   ```
   - Bulkheads (walls): Every 200-300 units
   - Support beams: At corners, along walls
   - Floor grating: Central walkway
   - Cable runs: Along ceiling/walls
   ```

4. **Create Doorways**
   ```
   - Use Boolean operations to cut door holes
   - Add door frame meshes
   - Size: 100 × 220 units (standard)
   - Position: Between sections
   ```

### Method 2: Custom Interior Modeling

**Best for:** Unique designs, production-quality ships

**In Blender:**

1. **Open Ship Model**
   - File → Open → spaceship-5 blend file
   - Ensure ship is centered at origin

2. **Create Interior Layout**
   ```
   - Add → Mesh → Plane (for floor)
   - Scale to fit inside hull
   - Extrude walls upward (E key)
   - Add loop cuts for rooms (Ctrl+R)
   - Extrude faces to create rooms
   ```

3. **Detail Pass**
   ```
   - Add doorframes: Loop-select edges, extrude inward
   - Add floor panels: Subdivide, extrude, scale
   - Add ceiling details: Inset faces, extrude down
   - Add greebles: Small details, pipes, panels
   ```

4. **UV Unwrap**
   ```
   - Select all interior faces (Alt+A)
   - U → Smart UV Project
   - Adjust UV islands in UV Editor
   - Export: File → Export → FBX
   ```

5. **Import to Unreal**
   - Import FBX as separate mesh or part of ship
   - Import with same scale as ship (100.0)

---

## Modular Kit Approach

### Using Marketplace Assets

**Recommended Kits:**

1. **Modular Sci-Fi: Season 1** (Epic Marketplace)
   - Free/Low cost
   - Comprehensive interior pieces
   - Snapping-friendly
   - PBR materials

2. **Sci-Fi Hallway** (various)
   - Modular corridor pieces
   - Doors, panels, lights
   - Easy assembly

3. **Spaceship Interior Kit** (Fab, CGTrader)
   - Complete room sets
   - Props included
   - Game-ready

### Building with Modular Pieces

**Setup:**

1. **Install Asset Pack**
   - Epic Games Launcher → Library
   - Add to Project: SubspaceUE
   - Wait for download

2. **Organize Assets**
   - Content Browser → Create folder: `Kits/SciFiInterior`
   - Copy assets to organized subfolders:
     - Floors
     - Walls
     - Ceilings
     - Doors
     - Props

3. **Enable Snapping**
   ```
   - In viewport, click snap icon (magnet)
   - Enable: Grid Snapping
   - Set grid size: 10 or 25 units
   - Enable: Snap to Grid
   ```

**Assembly Process:**

1. **Build Floor First**
   ```
   - Drag floor module into level
   - Position inside ship (0, 0, 0 relative to ship)
   - Duplicate (Alt+drag) to extend
   - Snap pieces together using grid
   ```

2. **Add Walls**
   ```
   - Place wall modules along floor edges
   - Snap to floor height
   - Ensure tight seams (no gaps)
   - Corner pieces at intersections
   ```

3. **Add Ceiling**
   ```
   - Place ceiling modules above walls
   - Match floor layout
   - Add lighting fixtures
   ```

4. **Add Doors**
   ```
   - Replace wall sections with doorways
   - Add door frame pieces
   - Add functional door blueprints (if available)
   - Between major sections
   ```

5. **Dress With Props**
   ```
   - Computer terminals: Walls
   - Seating: Cockpit, living areas
   - Storage crates: Cargo area
   - Equipment: Engineering section
   - Personal items: Living quarters
   ```

### Creating Custom Modular Pieces

If marketplace assets don't fit your ship:

1. **Design Modular Grid**
   ```
   - Choose base unit: 100 units (1 meter)
   - Floor tile: 100 × 100
   - Wall section: 100 width × 250 height
   - Ceiling tile: 100 × 100
   ```

2. **Model Base Pieces (Blender)**
   ```
   - Floor tile with panel detail
   - Wall segment with panel lines
   - Ceiling tile with lights
   - Door frame and door
   - Corner pieces (inner/outer)
   ```

3. **Export Properly**
   ```
   - Ensure pieces snap at 0, 0, 0 origin
   - Use consistent scale
   - Export each as separate FBX
   - Name clearly: Floor_100x100_01, Wall_100x250_01
   ```

4. **Import and Test**
   ```
   - Import to UE with scale 100.0
   - Test snapping alignment
   - Create material instances
   - Organize in folder
   ```

---

## Procedural Generation

### Blueprint-Based Interior Generator

**Create:** `BP_InteriorGenerator`

**Purpose:** Automatically generate interior based on ship size

**Variables:**
```
ShipLength: Float (default: 2000)
ShipWidth: Float (default: 800)
ShipHeight: Float (default: 400)
RoomCount: Integer (default: 4)
FloorTiles: Array of Static Mesh References
WallModules: Array of Static Mesh References
PropAssets: Array of Actor Class References
```

**Construction Script Logic:**

```
1. Calculate Ship Bounds
   → Get ship static mesh bounds
   → Store length, width, height

2. Generate Floor Layout
   → Divide ship length by room count
   → Create floor tiles using grid
   → For each tile:
      → Spawn floor mesh at calculated position
      → Random variation in floor mesh (if multiple types)

3. Generate Walls
   → Along floor perimeter
   → Between rooms (doorways every N rooms)
   → Height = ship interior height
   → Spawn wall meshes with snapping

4. Generate Ceiling
   → Match floor layout
   → Add lighting fixtures every 200 units

5. Add Doorways
   → Between rooms
   → At entrance/exit points
   → Spawn door blueprints

6. Populate Props
   → Random prop placement in rooms
   → Avoid doorways and high-traffic areas
   → Based on room type (if categorized)

7. Add Lighting
   → Point lights every 300-500 units
   → Attach to ceiling meshes
   → Set intensity based on room size
```

**Example Blueprint Nodes (Pseudocode):**

```
Construction Script:
  - Clear Old Interior Components
  - Get Ship Mesh Bounds → ShipLength, ShipWidth, ShipHeight
  - Calculate TileCount = ShipLength / 100
  - For i = 0 to TileCount:
      - SpawnLocation = (i * 100, 0, 0)
      - SpawnedFloor = AddStaticMeshComponent
      - SetStaticMesh(FloorTiles[Random])
      - SetWorldLocation(ShipLocation + SpawnLocation)
  - (Similar loops for walls, ceiling, props)
```

### PCG (Procedural Content Generation) Approach

**Requires:** UE 5.1+, PCG plugin enabled

**Setup:**

1. **Create PCG Volume**
   - Place Actors → Volumes → PCG Volume
   - Position inside ship hull
   - Scale to match interior space

2. **Create PCG Graph**
   - Right-click → Procedural → PCG Graph
   - Name: `PCG_ShipInterior`

3. **Build Graph:**
   ```
   Input: Volume Sampler
     ↓
   Filter by Bounds (stay inside ship hull)
     ↓
   Surface Sampler (for floor placement)
     ↓
   Grid Sampler (regular spacing: 100 units)
     ↓
   Branch:
     → Floor Spawner (80% weight)
     → Wall Spawner (15% weight)
     → Prop Spawner (5% weight)
     ↓
   Transform Randomizer (slight variation)
     ↓
   Static Mesh Spawner
   ```

4. **Configure Spawners:**
   ```
   Floor Spawner:
     - Mesh: Floor tile meshes (array)
     - Spawn Weight: Equal distribution
     - Align to Surface: ✓
   
   Wall Spawner:
     - Mesh: Wall section meshes
     - Spawn at edges only (filter by bounds)
     - Rotate to face inward
   
   Prop Spawner:
     - Mesh/Actor: Random props
     - Collision check: ✓ (don't overlap)
     - Weight by room type (if tagged)
   ```

5. **Generate:**
   - Select PCG Volume
   - Details Panel → Generate
   - Adjust parameters
   - Regenerate until satisfied

---

## Lighting and Materials

### Interior Lighting Strategy

**Ambient Base Lighting:**
```
- Skylight (interior):
  - Intensity: 0.1-0.2 (very low)
  - Color: Neutral white
  - Lower Hemisphere Color: Dark blue/gray
```

**Point Lights (Primary):**
```
Placement:
- Ceiling-mounted: Every 300-500 units
- Wall-mounted: Every 400-600 units
- Task lighting: Near consoles, workstations

Settings:
- Intensity: 2000-5000
- Attenuation Radius: 800-1200
- Color Temperature: 4500K (cool white) to 6500K (daylight)
- Enable Inverse Squared Falloff: ✓
- Cast Shadows: ✓ (for main lights), ✗ (for accent)
```

**Accent Lights:**
```
- Colored strips along walls:
  - Blue/Cyan: Technical areas
  - Green: Safe zones
  - Red: Restricted/dangerous areas
  - Orange: Engineering

- Settings:
  - Intensity: 500-1500
  - Spot lights or Rectangle lights
  - No shadows (performance)
```

**Emergency/Status Lights:**
```
- Flashing red lights (blueprint controlled):
  - Alert condition
  - Near airlocks
  - Emergency exits

- Always-on indicators:
  - Green: Operational
  - Yellow: Standby
  - Red: Offline
```

### Interior Materials

**Metal Panels (Walls/Floors):**
```
Material: M_InteriorPanel

Properties:
- Base Color: Dark gray (0.1, 0.1, 0.12)
- Metallic: 0.8-0.9
- Roughness: 0.3-0.5
- Normal: Panel line details
- Emissive: Subtle panel lights (optional)

Variations:
- Create Material Instances for different zones:
  - MI_Panel_Cockpit: Darker, more tech
  - MI_Panel_Living: Warmer tone
  - MI_Panel_Engineering: More wear, grime
```

**Floor Grating:**
```
Material: M_FloorGrating

Properties:
- Base Color: Dark metallic (0.15, 0.15, 0.15)
- Metallic: 0.9
- Roughness: 0.6 (worn)
- Normal: Grating pattern
- Opacity Mask: Holes in grating (if using translucent)

Detail:
- Add dirt/wear in corners
- Decals for scuff marks
```

**Monitors/Screens:**
```
Material: M_Monitor

Properties:
- Base Color: Black when off
- Emissive: Animated UI texture or color
- Emissive Strength: 3.0-8.0
- Roughness: 0.1 (glossy screen)

Animation:
- Use Material Parameter Collection
- Drive emissive with sine wave or video texture
- Different screens show different content
```

**Lighting Fixtures:**
```
Material: M_LightFixture

Properties:
- Base Color: Light gray casing (0.3, 0.3, 0.3)
- Emissive: White or colored glow (center)
- Emissive Strength: 5.0-10.0
- Metallic: 0.7
- Roughness: 0.2

Variation:
- Different colors per room type
- Flicker effect via blueprint for damaged lights
```

---

## Functional Elements

### Interactive Consoles

**Create:** `BP_InteractiveConsole`

**Components:**
- Static Mesh (console model)
- Box Trigger (for player proximity)
- Widget Component (UI display)

**Functionality:**
```
Events:
- OnBeginOverlap → Show interaction prompt
- OnEndOverlap → Hide prompt
- OnInteract (key press) → Open console UI

Widget:
- Display ship systems status
- Resource levels
- Map/navigation
- Mission log
```

### Doors

**Create:** `BP_SlidingDoor`

**Components:**
- Static Mesh (door panel)
- Box Trigger (activation zone)
- Timeline (animation)

**Blueprint Logic:**
```
Event BeginOverlap:
  → Play Timeline: DoorOpen
    → Lerp Door Position: Closed → Open (0.5 seconds)
    → Play Sound: Door Opening

Event EndOverlap:
  → Delay: 2.0 seconds
  → Play Timeline: DoorClose
    → Lerp Door Position: Open → Closed
    → Play Sound: Door Closing

Locked State:
  → If door is locked, don't open
  → Show "Locked" UI message
  → Play denied sound
```

### Storage Lockers

**Create:** `BP_StorageLocker`

**Functionality:**
- Interact to open inventory UI
- Store/retrieve items
- Persistent storage per locker
- Visual indicator of contents (LED color)

### Crew Stations

**Pilot Seat (Cockpit):**
```
BP_PilotSeat:
- Interact → Enter flight mode
- Disable character, enable ship controls
- Show flight HUD
- Exit on key press
```

**Engineering Console:**
```
BP_EngineeringConsole:
- Show power distribution
- Adjust system priorities
- Repair ship systems
- View damage report
```

**Navigation Console:**
```
BP_NavigationConsole:
- Show galaxy map
- Plot jumps
- View sector info
- Set waypoints
```

---

## Best Practices

### Performance Optimization

1. **Use LODs (Level of Detail)**
   ```
   - Generate LODs for interior meshes
   - LOD0: Full detail (0-1000 units)
   - LOD1: Reduced (1000-3000 units)
   - LOD2: Simplified (3000+ units)
   ```

2. **Culling**
   ```
   - Enable occlusion culling
   - Use cull distance volumes
   - Small props: Cull at 2000 units
   - Interior invisible from outside: Cull based on room visibility
   ```

3. **Lighting**
   ```
   - Bake static lighting where possible
   - Limit dynamic lights: 3-5 per visible area
   - Use lightmaps on static interior geometry
   - Lower shadow resolution on small objects
   ```

4. **Materials**
   ```
   - Share materials across similar objects
   - Use material instances (not unique materials)
   - Reduce texture resolution for small props (512x512)
   - Use texture atlasing for modular pieces
   ```

5. **Mesh Complexity**
   ```
   - Keep poly count reasonable:
     - Floor tile: 50-200 tris
     - Wall section: 100-500 tris
     - Props: 500-5000 tris each
   - Use normal maps for detail, not geometry
   - Merge static meshes in engine (reduce draw calls)
   ```

### Design Tips

1. **Visual Flow**
   - Use lighting to guide player
   - Bright areas = destinations
   - Darker areas = transitions
   - Color coding for room types

2. **Gameplay Space**
   - Keep combat areas open (600+ units wide)
   - Narrow corridors for tension
   - Vertical space for jetpacks/jumping
   - Cover objects in appropriate areas

3. **Immersion**
   - Add ambient sounds (hum, beeps)
   - Animated screens and lights
   - Occasional flickering (damaged ship)
   - Environmental storytelling (props, notes)

4. **Navigation**
   - Clear sightlines to exits
   - Signage (arrows, room labels)
   - Consistent layout logic
   - Distinct landmarks per section

5. **Scale Consistency**
   - Keep doorways uniform
   - Maintain ceiling heights
   - Consistent prop sizing
   - Check against character size frequently

---

## Texture Matching

To match spaceship-5 textures in the interior:

### Extract Color Palette

1. **Open BaseColor Texture**
   - `p_116_Spaceship_001_Spaceship_BaseColor-*.png`
   - Use image editor (Photoshop, GIMP)
   - Sample dominant colors:
     - Dark gray: RGB(40, 42, 45)
     - Mid gray: RGB(80, 85, 88)
     - Orange accent: RGB(255, 140, 60)
     - Blue accent: RGB(60, 140, 200)

2. **Create Interior Palette**
   - Use darker variants for interior
   - Dark gray → RGB(25, 25, 28) for floors
   - Mid gray → RGB(45, 48, 50) for walls
   - Keep accent colors for panels, lights

### Material Setup

**Interior Panel Material:**
```
M_InteriorPanel_Matched:

Base Color:
- Constant: Dark gray (sampled from ship)
- Multiply by texture: Panel detail (procedural)

Metallic: 0.85 (match ship's metallic look)

Roughness:
- Use ship's roughness texture as reference
- Adjust: 0.4-0.6 for interior (less shiny)

Normal:
- Create similar panel line detail
- Smaller scale (interior panels are smaller)

Emissive:
- Use orange accent color (from ship)
- Apply to thin strips (panel edges)
- Strength: 2.0-3.0
```

### Consistent Style

- **Panel Lines:** Same width as exterior (2-3 units)
- **Rivets/Details:** Similar size and spacing
- **Color Temperature:** Match exterior (cool gray, warm accents)
- **Wear Patterns:** If ship is worn, interior should match
- **Technology Level:** Same level of tech detail

---

## Examples and Templates

### Template 1: Small Fighter Interior

**Ship Size:** 1000 × 400 × 300 units

**Interior Layout:**
```
Front 40%: Cockpit
- Pilot seat: Center, facing forward
- Console wrap-around
- Front viewport (transparent material)

Rear 60%: Single room
- Systems access (walls)
- Storage crates (corners)
- Small bunk (side)
- Exit hatch (rear)

Lighting:
- 3 ceiling lights (2500 intensity)
- Cockpit glow from consoles
- Red exit light at hatch
```

### Template 2: Medium Freighter Interior

**Ship Size:** 2500 × 1000 × 500 units

**Interior Layout:**
```
Front 20%: Cockpit (2 seats)
Middle 30%: Living/Crew (corridor + 2 side rooms)
Rear 50%: Cargo bay (large open space)

Modular Pieces:
- Floor: 25 tiles (100×100 each)
- Walls: 60 sections (100 wide × 250 high)
- Doors: 3 (between sections)

Lighting:
- 12 ceiling lights (cargo bay: 6, living: 4, cockpit: 2)
- 8 wall accent lights (living quarters)
- Emergency lights at exits

Props:
- 20 cargo containers (rear)
- 4 crew bunks (living)
- 8 consoles (cockpit: 2, cargo: 4, living: 2)
- 15 misc items (computers, chairs, equipment)
```

### Template 3: Large Ship Interior

**Ship Size:** 5000 × 2000 × 800 units

**Interior Layout:**
```
Deck 1 (Lower):
- Engineering (rear 60%)
- Cargo access (sides)
- Maintenance corridors

Deck 2 (Main):
- Living quarters (middle 40%)
- Galley/Common area (middle 20%)
- Medical bay (side room)

Deck 3 (Upper):
- Bridge/Cockpit (front 30%)
- Captain's quarters (front-mid 10%)
- Observation deck (mid 20%)

Vertical Access:
- Ladders between decks (4 points)
- Or elevators (2, forward and aft)

Lighting:
- 50+ ceiling lights (distributed)
- 30+ accent lights
- Emergency path lighting

Props:
- 100+ items total (mix of functional and decorative)
```

---

## Testing Checklist

- [ ] Player can navigate entire interior without clipping
- [ ] Doorways are passable without crouching
- [ ] Lighting is sufficient to see (no pure black areas)
- [ ] No gaps in walls/floor/ceiling (light leaks)
- [ ] Materials match ship exterior style
- [ ] Frame rate remains above 60 FPS inside ship
- [ ] Interactive elements respond correctly
- [ ] Collision prevents falling through geometry
- [ ] Audio ambience plays correctly
- [ ] Exit points are clear and functional

---

## Resources

**Marketplace Assets:**
- Modular Sci-Fi: Season 1 (Epic)
- Sci-Fi Props Pack (Fab)
- Spaceship Interior Kit (CGTrader)

**Tutorials:**
- "UE5 Modular Interior Design" (YouTube)
- "Sci-Fi Ship Interior Tutorial" (YouTube)
- Unreal Engine docs: Modular Building

**Tools:**
- Blender (for custom modeling)
- Substance Designer (for materials)
- Greeble generators (for detail)

---

**Document Version:** 1.0  
**Last Updated:** 2026-01-08  
**For:** SubspaceUE / Sol-TestingGrounds Implementation

---

This guide provides multiple approaches to interior generation. Start with the simple box method for prototyping, then upgrade to modular kits or procedural generation for production quality. Match textures to the spaceship-5 exterior for visual consistency. Test frequently during creation to catch issues early.
