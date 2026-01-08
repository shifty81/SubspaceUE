# Importing Ulysses Ship Model into Unreal Engine

## Overview
This guide explains how to import the Ulysses.blend file into Unreal Engine 5.7 to replace the default cube placeholder with an actual ship model.

## Prerequisites
- Unreal Engine 5.7 (or compatible version)
- Blender 3.x or 4.x installed (optional, for FBX export)
- SubspaceUE project opened in Unreal Editor

## Location of Model Files
The Ulysses ship model files are located at:
```
Assets/Models/ships/Ulysses/source/
├── ulysses.blend
└── p_116_Spaceship_001.blend
```

## Import Methods

### Method 1: Import via Datasmith (Recommended for Blender files)
Unreal Engine can import Blender files directly using Datasmith plugin:

1. **Enable Datasmith Plugin**:
   - In Unreal Editor, go to `Edit` → `Plugins`
   - Search for "Datasmith"
   - Enable the plugin and restart the editor

2. **Import the Blender File**:
   - In Content Browser, navigate to `Content/Ships/`
   - Right-click and select `Import to /Game/Ships/...`
   - Browse to `Assets/Models/ships/Ulysses/source/ulysses.blend`
   - Click `Open`

3. **Import Settings**:
   - Keep default import settings
   - Click `Import`

### Method 2: Export from Blender as FBX (Most Compatible)
This is the most reliable method for importing 3D models into Unreal Engine:

1. **Open Blender**:
   - Launch Blender 3.x or 4.x
   - Open `Assets/Models/ships/Ulysses/source/ulysses.blend`

2. **Prepare the Model**:
   - Select the ship mesh
   - Press `Ctrl+A` → `All Transforms` to apply all transformations
   - Verify the ship is facing forward (+Y in Blender, which converts to +X in UE)

3. **Export as FBX**:
   - Go to `File` → `Export` → `FBX (.fbx)`
   - Navigate to `Assets/Models/ships/Ulysses/source/`
   - Name the file `ulysses_export.fbx`
   - **Export Settings**:
     - Forward: Y Forward
     - Up: Z Up
     - Scale: 1.0
     - Apply Scalings: FBX All
     - Selected Objects: Yes (if ship is selected)
     - Mesh: Checked
     - Apply Modifiers: Yes
   - Click `Export FBX`

4. **Import into Unreal Engine**:
   - In Unreal Editor Content Browser, navigate to `Content/Ships/`
   - Drag and drop `ulysses_export.fbx` into the Content Browser
   - Or right-click → `Import to /Game/Ships/...`
   
5. **FBX Import Settings**:
   - **Transform**:
     - Import Translation: (0, 0, 0)
     - Import Rotation: (0, 0, 0)
     - Import Uniform Scale: 1.0
   - **Mesh**:
     - Skeletal Mesh: OFF
     - Static Mesh: ON
     - Generate Lightmap UVs: ON
   - **Material**:
     - Import Materials: ON
     - Import Textures: ON
   - Click `Import`

### Method 3: Export as glTF (Modern Alternative)
glTF is a modern format with good UE support:

1. **Export from Blender**:
   - Open `ulysses.blend` in Blender
   - `File` → `Export` → `glTF 2.0 (.glb/.gltf)`
   - Choose Binary format (.glb)
   - Export

2. **Import into UE**:
   - Enable glTF Importer plugin if needed
   - Import the .glb file

## Updating SubspacePlayerPawn to Use the New Model

After importing, you need to tell the game to use your new ship model instead of the cube:

### Option A: Blueprint (Easiest - Recommended)
1. **Create a Blueprint**:
   - In Content Browser, navigate to `Content/Blueprints/`
   - Right-click → `Blueprint Class`
   - Search for `SubspacePlayerPawn` as parent class
   - Name it `BP_PlayerShip`

2. **Set the Ship Mesh**:
   - Open `BP_PlayerShip`
   - In the Components panel, select `ShipMesh`
   - In Details panel, find `Static Mesh`
   - Select your imported Ulysses mesh
   - Adjust scale if needed (try `(1, 1, 1)` first)

3. **Update Game Mode**:
   - Open your GameMode blueprint
   - Set `Default Pawn Class` to `BP_PlayerShip`

### Option B: C++ Code
Edit `SubspacePlayerPawn.cpp` constructor:

```cpp
// Replace this line:
static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMeshAsset(TEXT("/Engine/BasicShapes/Cube"));

// With this (adjust path to match your imported mesh):
static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMeshAsset(TEXT("/Game/Ships/ulysses_export"));
```

And remove or adjust the scale:
```cpp
// Remove or adjust this line:
ShipMesh->SetRelativeScale3D(FVector(4.0f, 8.0f, 2.0f)); // Remove or set to (1, 1, 1)
```

## Recommended Model Requirements

For best results, the Ulysses model should have:
- **Scale**: Approximately 15-20 meters in length (corvette-class)
- **Forward Direction**: +X axis in Unreal Engine
- **Polygon Count**: 500-5000 triangles for real-time performance
- **Origin**: Center of the ship at (0, 0, 0)
- **Materials**: Basic PBR materials (Base Color, Metallic, Roughness)

## Troubleshooting

### Model is Too Small/Large
- In Blueprint, adjust the `ShipMesh` scale
- Or re-export with different scale settings

### Model is Rotated Wrong
- In Blueprint, adjust the `ShipMesh` rotation
- Or fix in Blender before exporting

### Model is Inside-Out or Dark
- Check normals in Blender: Select all → `Mesh` → `Normals` → `Recalculate Outside`
- Re-export

### Textures Missing
- Ensure textures are in a folder relative to the .blend file
- In UE import settings, enable "Import Textures"
- Manually assign textures in Material Editor if needed

### Collisions Not Working
- In Static Mesh Editor, go to `Collision` → `Auto Convex Collision`
- Or manually create collision

## Model Features to Consider

When creating/modifying the Ulysses model:
- **Cockpit**: Visible windows/canopy at front
- **Engines**: Thruster details at rear
- **Details**: Panel lines, hatches, etc.
- **Equipment Hardpoints**: Visual mounting points (optional)
- **Interior Space**: Empty interior for walking (if implementing interior gameplay)

## Next Steps

After importing the model:
1. Test in Play-In-Editor (PIE)
2. Adjust camera distance if needed (in `SubspacePlayerPawn` settings)
3. Add materials and textures
4. Set up collision properly
5. Consider adding engine glow effects

## Additional Resources

- [Unreal Engine FBX Import Guide](https://docs.unrealengine.com/5.0/en-US/fbx-content-pipeline-for-unreal-engine/)
- [Blender to Unreal Engine Workflow](https://docs.unrealengine.com/5.0/en-US/blender-to-unreal-engine-workflow/)
- [Static Mesh Editor](https://docs.unrealengine.com/5.0/en-US/static-mesh-editor-in-unreal-engine/)

---

**Note**: The current implementation uses a simple cube as a placeholder. Following this guide will replace it with the proper Ulysses ship model for a more immersive experience.
