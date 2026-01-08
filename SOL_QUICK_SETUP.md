# Sol Testing Grounds - Quick Setup Guide

## Prerequisites
- Unreal Engine 5.6 installed
- SubspaceUE project compiled successfully
- Basic knowledge of Unreal Editor

## Quick Setup (30 minutes)

### 1. Compile C++ Classes (5 minutes)

The new planetary orbit system has been added to the C++ source code:
- `PlanetActor.h/cpp` - Individual planet with orbit mechanics
- `SolarSystemManager.h/cpp` - Spawns and manages all planets

**To compile:**
1. Open SubspaceUE.uproject in Unreal Editor
2. Wait for compilation to complete (first time may take 5-10 minutes)
3. If prompted to rebuild, click "Yes"

### 2. Create the Massive Level (5 minutes)

1. **Create New Level:**
   - File → New Level → Empty Level
   - Save as: `Content/Maps/SolTestingGrounds_Massive`

2. **Enable Large World Coordinates:**
   - Window → World Settings
   - Under World → Check "Enable Large World Coordinates"
   - Under World → Kill Z: -1000000000.0

3. **Save the level**

### 3. Add Solar System Manager (2 minutes)

1. **Place the Actor:**
   - Open Place Actors panel (Shift+1)
   - Search for "SolarSystemManager"
   - Drag into level at origin (0, 0, 0)

2. **Configure (Details Panel):**
   ```
   Distance Scale: 0.00001
   Planet Size Scale: 50.0
   Global Time Multiplier: 10000.0
   Auto Spawn Planets: ✓ Enabled
   Spawn Sun: ✓ Enabled
   ```

3. **That's it!** Planets will spawn automatically when you press Play

### 4. Add Lighting (3 minutes)

1. **Directional Light (Sun):**
   - Place Actors → Lights → Directional Light
   - Intensity: 15.0
   - Light Color: Slight yellow (255, 248, 220)
   - Check "Atmosphere Sun Light"

2. **Sky Atmosphere:**
   - Place Actors → Visual Effects → Sky Atmosphere
   - Use default settings

3. **Optional - Skybox:**
   - Search for "SpaceSkyboxActor" if available
   - Or add a large inverted sphere with star material

### 5. Create Planet Blueprint (10 minutes)

Since C++ classes need meshes assigned:

1. **Create Base Planet Blueprint:**
   ```
   Content Browser → Right-click → Blueprint Class
   Parent Class: PlanetActor
   Name: BP_Planet
   ```

2. **Add Mesh Component:**
   - Open BP_Planet
   - Already has Mesh component from parent
   - Click Mesh component
   - Static Mesh: Select a UV Sphere mesh (create if needed)
   - Save

3. **Update Solar System Manager:**
   - Select Solar System Manager in level
   - Planet Actor Class → BP_Planet

### 6. Test the System (5 minutes)

1. **Press Play (Alt+P)**
   - Planets should spawn automatically
   - They will begin orbiting the sun
   - With 10,000x time multiplier, orbits are visible

2. **Observe Orbits:**
   - Mercury completes orbit in ~12.7 real-time minutes
   - Earth completes orbit in ~52.6 real-time minutes
   - Neptune takes ~6 real-time days

3. **Debug Visualization:**
   - Cyan lines show orbital paths
   - Yellow sphere marks perihelion (closest point)
   - Red sphere marks aphelion (farthest point)

## Quick Commands

Open console with ` key (these would need to be implemented):

```
// Time control
sol.SetTimeMultiplier 1000    - 1000x speed
sol.SetTimeMultiplier 100000  - 100,000x speed
sol.SetTimeMultiplier 0       - Pause

// Camera teleports (future feature)
sol.TeleportToPlanet Earth
sol.TeleportToPlanet Mars

// Visualization
sol.ShowOrbits true/false
```

## Understanding the Scale

### Distance Scale (1:100,000)
- Real solar system is HUGE
- Neptune is 30 AU = 4.5 billion km from Sun
- Scaled down 100,000x for gameplay
- Neptune becomes 44,983 km (still massive!)

### Planet Size Scale (50x)
- Planets scaled up 50x so they're visible
- Earth: 12,742 km real → 636,000 km in-game
- Otherwise planets would be invisible dots

### Time Multiplier (10,000x)
- Real orbits are slow (Earth = 365 days)
- Sped up 10,000x so we can see them move
- Earth orbit becomes 52.6 real-time minutes
- Fully configurable - adjust for your needs

## Planet Data Summary

| Planet  | Real Distance | Game Distance | Real Orbit | Game Orbit @ 10,000x |
|---------|---------------|---------------|------------|---------------------|
| Mercury | 0.39 AU       | 579 km        | 88 days    | 12.7 minutes        |
| Venus   | 0.72 AU       | 1,082 km      | 225 days   | 32.4 minutes        |
| Earth   | 1.00 AU       | 1,496 km      | 365 days   | 52.6 minutes        |
| Mars    | 1.52 AU       | 2,279 km      | 687 days   | 1.6 hours           |
| Jupiter | 5.20 AU       | 7,784 km      | 4,333 days | 10.4 hours          |
| Saturn  | 9.54 AU       | 14,267 km     | 10,759 days| 25.8 hours          |
| Uranus  | 19.19 AU      | 28,710 km     | 30,689 days| 73.7 hours (3.1 days)|
| Neptune | 30.07 AU      | 44,983 km     | 60,182 days| 144.4 hours (6.0 days)|

## Troubleshooting

### "Can't find PlanetActor class"
- Recompile the C++ project
- Check Source/SubspaceUE/Public contains PlanetActor.h
- Rebuild solution in IDE

### "Planets not appearing"
- Check Auto Spawn Planets is enabled
- Verify Planet Actor Class is set
- Look in World Outliner for spawned planets
- Check Output Log for spawn messages

### "Can't see planets when playing"
- Increase camera far clip plane (10,000,000+)
- Planets are far away - use teleport to visit them
- Or increase Global Time Multiplier to see motion faster

### "Planets not moving"
- Check Global Time Multiplier > 0
- Ensure actors are ticking (Details → Actor Tick → Enabled)
- Look for error messages in Output Log

### "Performance is poor"
- Disable orbit visualization (bShowOrbitPath = false)
- Reduce Planet Size Scale
- Lower material quality
- Use LODs on planet meshes

## Next Steps

1. **Add Planet Materials:**
   - Import textures from `GameData/Assets/Models/Solar Systems/Sol-TestingGrounds/textures/`
   - Create materials for each planet
   - See SOL_REALWORLD_SCALE_GUIDE.md for details

2. **Create Planet-Specific Blueprints:**
   - BP_Earth, BP_Mars, etc.
   - Assign unique materials to each
   - Configure per-planet properties

3. **Add Camera System:**
   - Implement free-fly camera
   - Add planet follow camera
   - Create teleport system

4. **Add Moons:**
   - Use PlanetActor with smaller orbits
   - Parent to planet actors
   - Earth's Moon, Mars's Phobos/Deimos, etc.

## Reference Files

- **Detailed Guide:** `SOL_REALWORLD_SCALE_GUIDE.md`
- **Configuration Generator:** `generate_solar_system_config.py`
- **Planetary Data:** `solar_system_config.json`
- **Troubleshooting:** `SOL_TESTINGGROUNDS_TROUBLESHOOTING.md`

## Technical Notes

### Orbital Mechanics
- Uses Kepler's laws and equations
- Elliptical orbits with proper eccentricity
- Real astronomical data from NASA JPL
- Newton-Raphson solver for eccentric anomaly

### Coordinate System
- Origin (0,0,0) = Sun position
- Ecliptic plane = XY plane (Z up)
- J2000.0 epoch reference frame

## Support

Questions? Issues?
1. Check SOL_REALWORLD_SCALE_GUIDE.md for detailed explanations
2. Run generate_solar_system_config.py for configuration data
3. Review source code comments in PlanetActor.h
4. Open GitHub issue with "Sol Testing Grounds" tag

---

**Version:** 1.0  
**Last Updated:** 2026-01-08  
**Estimated Setup Time:** 30 minutes  
**Difficulty:** Intermediate
