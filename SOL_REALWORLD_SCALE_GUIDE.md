# Sol Testing Grounds - Real-World Scale Implementation Guide

## Overview

This guide covers the implementation of a massive-scale Sol (Solar System) testing grounds with real-world planetary orbits. The system uses actual astronomical data for all 8 planets with accurate orbital mechanics.

## Features Implemented

### 1. Planetary Orbit System
- **Elliptical Orbits**: Implements Kepler's orbital mechanics with eccentric anomaly calculations
- **Real Astronomical Data**: Uses actual values for all 8 planets (Mercury through Neptune)
- **Configurable Time Scale**: Speed up or slow down time to observe orbital motion
- **Debug Visualization**: Shows orbit paths, perihelion, and aphelion markers

### 2. Scale Management
The system uses configurable scale factors to balance realism with gameplay:

- **Distance Scale**: Default 1:100,000
  - Keeps planetary distances manageable while maintaining relative positions
  - Neptune at ~30 AU becomes ~4,487,936,000 UE units (~44,879 km in-game)
  
- **Planet Size Scale**: Default 50x
  - Makes planets visible at vast distances
  - Earth (12,742 km diameter) becomes ~6,371,000 UE units (~63.7 km in-game)
  
- **Time Multiplier**: Default 10,000x
  - Allows observable orbital motion
  - Earth completes orbit in ~3.15 real-time minutes instead of 365 days

### 3. Orbital Parameters

Each planet includes:
- **Semi-major axis** (orbital radius)
- **Eccentricity** (0 = circular, higher = more elliptical)
- **Orbital period** (time to complete one orbit)
- **Inclination** (tilt relative to ecliptic plane)
- **Longitude of ascending node** (where orbit crosses reference plane)
- **Argument of periapsis** (orientation of ellipse)
- **Mean anomaly at epoch** (starting position)

### 4. Planet Data (Real-World)

| Planet  | Distance (AU) | Period (days) | Eccentricity | Inclination |
|---------|---------------|---------------|--------------|-------------|
| Mercury | 0.387         | 87.97         | 0.206        | 7.00°       |
| Venus   | 0.723         | 224.70        | 0.007        | 3.39°       |
| Earth   | 1.000         | 365.26        | 0.017        | 0.00°       |
| Mars    | 1.524         | 686.98        | 0.093        | 1.85°       |
| Jupiter | 5.203         | 4,332.59      | 0.048        | 1.31°       |
| Saturn  | 9.537         | 10,759.22     | 0.054        | 2.48°       |
| Uranus  | 19.191        | 30,688.5      | 0.047        | 0.77°       |
| Neptune | 30.069        | 60,182.0      | 0.009        | 1.77°       |

## Setting Up in Unreal Editor

### Step 1: Compile C++ Code

1. Open the SubspaceUE project in your preferred IDE or Unreal Editor
2. Build the project to compile the new `APlanetActor` and `ASolarSystemManager` classes
3. Wait for compilation to complete

### Step 2: Create a New Massive Level

1. **Create New Level**
   - File → New Level → Empty Level
   - Save as `Content/Maps/SolTestingGrounds_Massive`

2. **Configure World Settings**
   - Window → World Settings
   - Under World → Enable Large World Coordinates: ✓ Enabled
   - Under World → Kill Z: -1000000000.0 (prevent falling out of world)
   - Under Lightmass → Force No Precomputed Lighting: ✓ Enabled

3. **Set World Bounds**
   - Create a large bounding box for culling
   - Scale to encompass Neptune's orbit (~45 million UE units radius)

### Step 3: Add Solar System Manager

1. **Place Actor**
   - Place Actors Panel → Search "SolarSystemManager"
   - Drag `ASolarSystemManager` into the level at origin (0, 0, 0)

2. **Configure Properties** (Details Panel)
   ```
   Solar System | Scale:
   - Distance Scale: 0.00001 (1:100,000)
   - Planet Size Scale: 50.0 (50x larger for visibility)
   
   Solar System | Time:
   - Global Time Multiplier: 10000.0 (10,000x speed)
   
   Solar System | Setup:
   - Auto Spawn Planets: ✓ Enabled
   - Spawn Sun: ✓ Enabled
   - Planet Actor Class: PlanetActor (or custom BP class)
   ```

3. **Save Changes**

### Step 4: Create Planet Materials

For each planet, create materials using the textures in `GameData/Assets/Models/Solar Systems/Sol-TestingGrounds/textures/`:

#### Example: Earth Material

1. **Create Material**
   - Content Browser → Right-click → Material
   - Name: `M_Earth`

2. **Material Setup**
   ```
   Nodes:
   - Texture Sample (EartAlbedo.jpeg) → Base Color
   - Texture Sample (EarthNormal.jpeg, Normal map) → Normal
   - Texture Sample (EarthRoughness.jpeg, Linear) → Roughness
   - Constant (0.0) → Metallic
   ```

3. **Configure Texture Settings**
   - For Normal maps: Compression Settings → Normalmap, sRGB: Off
   - For Albedo: Compression Settings → Default, sRGB: On
   - For Roughness: Compression Settings → Masks, sRGB: Off

4. **Repeat for All Planets**
   - Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune
   - Use respective texture files from the textures folder

#### Sun Material

Create `M_Sun` with emissive properties:
```
Nodes:
- Texture Sample (SunAlbedo.jpeg) → Emissive Color
- Multiply by 1000.0 → Emissive Color (bright)
- Unlit Shading Model
```

### Step 5: Create Planet Mesh Blueprint

Since the C++ class needs meshes and materials assigned:

1. **Create Blueprint Class**
   - Content Browser → Blueprints
   - Parent Class: PlanetActor
   - Name: `BP_Planet`

2. **Add Components**
   - Already has `Mesh` component from parent
   - Select Mesh in Components panel

3. **Configure Mesh**
   - Static Mesh: Choose or create a UV Sphere
   - Materials: Will be set per-instance

4. **For Each Planet, Create Instance**
   - Duplicate BP_Planet
   - Name: `BP_Earth`, `BP_Mars`, etc.
   - Assign appropriate material

### Step 6: Modify Solar System Manager to Use Blueprints

If you created planet blueprint classes, update the Solar System Manager:

1. Select Solar System Manager in the level
2. Planet Actor Class → Choose your blueprint (e.g., `BP_Planet`)

### Step 7: Setup Lighting

1. **Add Directional Light (Sun)**
   - Place Actors → Lights → Directional Light
   - Position: (0, 0, 0) - Position doesn't matter for directional light
   - Rotation: Point towards where you want sunlight
   - Intensity: 15.0 lux
   - Color: Slight yellow (FFC850)
   - Atmosphere Sun Light: ✓ Enabled

2. **Add Sky Atmosphere**
   - Place Actors → Visual Effects → Sky Atmosphere
   - Defaults work well

3. **Add Exponential Height Fog** (Optional)
   - Place Actors → Visual Effects → Exponential Height Fog
   - Fog Density: 0.0001 (very subtle)

4. **Add Skybox**
   - Use existing `SpaceSkyboxActor` if available
   - Or create sphere with star field material

### Step 8: Configure Player Pawn/Camera

1. **Create Player Start**
   - Place near Earth (coordinates around Earth's position)
   - Or create custom spawn logic

2. **Configure Camera**
   - Create or modify player pawn
   - Increase camera far clip plane: 100,000,000+ units
   - Enable camera movement with large speed values

3. **Add Camera Controls**
   - Blueprint for teleporting between planets
   - Speed controls for traversing vast distances

### Step 9: Testing

1. **Play in Editor (PIE)**
   - Press Play or Alt+P
   - Watch planets orbit around the sun
   - Use console commands to control time

2. **Console Commands** (Press ` key)
   ```
   // In future implementations, add these:
   sol.timescale 1000       - Set time multiplier to 1000x
   sol.pause                - Pause all orbits
   sol.resume               - Resume orbits
   sol.teleport Earth       - Teleport to Earth
   sol.showorbits true      - Show orbit visualization
   ```

3. **Verify Orbits**
   - Mercury should orbit fastest (87 days real-time)
   - Neptune should orbit slowest (60,182 days real-time)
   - With 10,000x multiplier:
     - Mercury: 12.5 minutes per orbit
     - Earth: 52.6 minutes per orbit
     - Neptune: 87 hours per orbit

### Step 10: Optimization

1. **Level of Detail (LOD)**
   - Set up LODs for planet meshes
   - Reduce polygon count at distance

2. **Culling**
   - Adjust culling distances for each planet
   - Use distance-based material swaps

3. **Performance Settings**
   - Disable orbit visualization for far planets
   - Reduce update frequency for distant objects

## Blueprint Access

The system exposes several blueprint-callable functions:

### SolarSystemManager Functions
- `SpawnAllPlanets()` - Spawn all 8 planets
- `SpawnPlanet(Name)` - Spawn specific planet
- `GetPlanetByName(Name)` - Get reference to planet
- `SetGlobalTimeMultiplier(Multiplier)` - Change time speed
- `SetOrbitsPaused(bPaused)` - Pause/resume orbits
- `GetSunPosition()` - Get center position
- `SetAllPlanetsOrbitPosition(NormalizedPosition)` - Jump to specific time

### PlanetActor Functions
- `GetOrbitPosition()` - Get current position
- `GetDistanceFromCenter()` - Distance from sun
- `SetTimeMultiplier(Multiplier)` - Individual time control
- `SetOrbitPosition(NormalizedPosition)` - Jump in orbit (0-1)

### PlanetActor Events
- `OnOrbitPositionUpdated(NewPosition)` - Called each position update

## Troubleshooting

### Planets Not Appearing
- Check Solar System Manager has Auto Spawn Planets enabled
- Verify Planet Actor Class is set
- Check compilation succeeded
- Look in World Outliner for spawned actors

### Planets Not Moving
- Verify Global Time Multiplier > 0
- Check bOrbitsPaused is false
- Ensure actor is ticking (Primary Actor Tick enabled)

### Orbits Look Wrong
- Verify scale factors are reasonable
- Check planetary data matches expectations
- Enable debug visualization (bShowOrbitPath)

### Performance Issues
- Reduce Planet Size Scale (fewer visible pixels)
- Disable debug orbit visualization
- Increase culling distances
- Lower material quality for distant planets

### Camera Can't See Far Planets
- Increase camera far clip plane
- Adjust exponential fog settings
- Check world bounds include all planets

## Advanced Customization

### Custom Planet Classes
Create derived Blueprint classes from BP_Planet:
- Add atmosphere effects
- Custom LOD transitions
- Planet-specific features (rings for Saturn)
- Cloud layers (Earth)

### Moon Systems
Add moon actors that orbit planets:
1. Create `AMoonActor` class derived from `APlanetActor`
2. Set `OrbitCenter` to parent planet position
3. Use much smaller orbital radii
4. Parent moon to planet actor for hierarchy

### Elliptical Visualization
The debug visualization shows:
- **Cyan lines**: Orbital path
- **Yellow sphere**: Perihelion (closest to sun)
- **Red sphere**: Aphelion (farthest from sun)

## Technical Details

### Coordinate System
- Origin (0,0,0) is at the Sun
- Ecliptic plane is XY (Z up)
- Positive X is vernal equinox direction
- Orbits follow right-hand rule

### Kepler's Equation Implementation
Solves: M = E - e·sin(E)
- M: Mean anomaly (uniform angular motion)
- E: Eccentric anomaly (actual position)
- e: Eccentricity
- Uses Newton-Raphson iteration (converges in ~5-10 iterations)

### Orbital Elements (J2000 Epoch)
All planetary data referenced to J2000.0 epoch (January 1, 2000, 12:00 TT).
Source: NASA/JPL Horizons System

## Future Enhancements

### Planned Features
- [ ] Moon system implementation
- [ ] Asteroid belt generation
- [ ] Dwarf planets (Pluto, Ceres, etc.)
- [ ] Kuiper belt objects
- [ ] Comet trajectories
- [ ] Real-time planetary position calculation from date/time
- [ ] Gravitational influence simulation
- [ ] N-body physics (optional)

### Performance Optimizations
- [ ] Instanced static meshes for asteroid belts
- [ ] GPU-based orbit calculations
- [ ] Hierarchical LOD system
- [ ] Streaming levels per planet region

## References

- NASA JPL Horizons: https://ssd.jpl.nasa.gov/horizons/
- Orbital Elements: https://ssd.jpl.nasa.gov/planets/approx_pos.html
- Kepler's Equation: https://en.wikipedia.org/wiki/Kepler%27s_equation

## Support

For issues or questions:
1. Check troubleshooting section above
2. Review SOL_TESTINGGROUNDS_TROUBLESHOOTING.md
3. Open issue on GitHub repository

---

**Document Version:** 1.0  
**Last Updated:** 2026-01-08  
**Compatible With:** Unreal Engine 5.6, SubspaceUE Project  
**Author:** SubspaceUE Development Team
