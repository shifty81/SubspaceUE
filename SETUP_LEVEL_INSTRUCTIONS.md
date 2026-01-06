# Setting Up the Space Level

Since Unreal Engine map files (`.umap`) are binary and cannot be created via code, you need to create the initial map in the Unreal Editor. Follow these steps:

## Step 1: Open the Project
1. Open Unreal Engine 5.6
2. Navigate to the project folder: `/home/runner/work/SubspaceUE/SubspaceUE/`
3. Double-click `SubspaceUE.uproject` to open it in the editor

## Step 2: Create the Space Level Map
1. In the Content Browser, navigate to the `Content/Maps` folder
2. If the Maps folder doesn't exist, create it: Right-click in Content → New Folder → name it "Maps"
3. Right-click in the Maps folder → Level → Empty Level
4. Name it `SpaceLevel`
5. Double-click to open the level

## Step 3: Set Up the Level (Basic Setup)
The level is initially empty (black). Add the following:

### Basic Setup
1. **Save the level**: File → Save Current As → Save to `Content/Maps/SpaceLevel`

That's it! The C++ code will automatically:
- Spawn lighting (sun and ambient light)
- Spawn 50 asteroids around the map
- Spawn 5 AI ships
- Create the player ship with camera
- Display the HUD with controls and ship status

## Step 4: Play the Game
1. Click the **Play** button (or press Alt+P)
2. You should now see:
   - Your ship (a cube shape) in space
   - Spherical asteroids floating around
   - AI ships (also spherical)
   - A green HUD showing your speed, position, and controls
   - A green crosshair in the center

## Controls
- **W/S** - Forward/Backward thrust
- **A/D** - Strafe left/right
- **Space/Shift** - Up/Down thrust
- **Arrow Keys** - Pitch and Yaw rotation
- **Q/E** - Roll rotation
- **B** - Emergency brake (stops all movement)

## Optional: Enhance the Visuals
If you want better visuals, you can:

1. **Add a Skybox/Space Background:**
   - Window → Env. Light Mixer
   - Click "Create Sky Light" and "Create Atmospheric Light"
   - Or drag a Sky Atmosphere into the level from the Place Actors panel

2. **Add Post-Processing:**
   - Drag a Post Process Volume into the level
   - Set it to "Infinite Extent (Unbound)"
   - Adjust bloom, exposure, etc.

3. **Replace Placeholder Meshes:**
   - Select the player pawn in the World Outliner
   - In Details panel, find the Ship Mesh component
   - Replace the cube mesh with a better ship model
   - Do the same for asteroids and AI ships in the SpaceActor blueprint

4. **Add Particle Effects:**
   - Create engine trails
   - Add thruster effects
   - Add stars/nebula background

## Troubleshooting

### Still seeing black screen?
- Make sure you saved the level
- Check that the level is set as the default map in Project Settings → Maps & Modes
- Try adding a Sky Atmosphere or Sky Light manually

### No player controls?
- Check that the Player Controller class is set to SubspacePlayerController in Project Settings → Maps & Modes → Default Modes

### Asteroids/ships not visible?
- They spawn far away - use the camera to fly around (W key)
- Or check the Output Log for spawn messages

## What Happens When You Press Play

The game will automatically:
1. Use **SubspaceGameMode** as the game mode
2. Spawn a **SubspacePlayerPawn** (your ship with camera)
3. Activate the **SubspaceHUD** (green text overlay)
4. Spawn a **SpaceLightingActor** (provides lighting)
5. Generate 50 **asteroids** (spheres at random positions)
6. Spawn 5 **AI ships** (spheres closer to origin)
7. Enable ship controls (6DOF Newtonian physics)

All of this happens in C++ automatically - no Blueprint setup required!
