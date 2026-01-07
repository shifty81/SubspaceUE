# Space Scene Generation - Quick Start Checklist

A condensed checklist for quickly implementing professional space scenes using Unreal Store assets.

**Full Guide:** See [SPACE_SCENE_GENERATION_WITH_STORE_ASSETS.md](SPACE_SCENE_GENERATION_WITH_STORE_ASSETS.md) for comprehensive instructions.

---

## Prerequisites

- [ ] Unreal Engine 5.6 installed
- [ ] SubspaceUE project set up and opening correctly
- [ ] Epic Games Launcher with account logged in
- [ ] Budget allocated for asset purchase (optional - free assets available)

---

## Quick Implementation Path (2-4 hours)

### Step 1: Choose Your Asset Pack (15 minutes)

Pick ONE to start with:

- [ ] **Space Creator Pro** - Easiest setup, drag-and-drop ⭐ RECOMMENDED FOR BEGINNERS
- [ ] **Space Scene for UE5** (ArtStation) - Best quality, cinematic
- [ ] **Space Skybox Collection** - Best value, multiple variants
- [ ] **Cosmic Forge** - Most flexible, procedural
- [ ] **Free Asset Packs** - Good for prototyping

### Step 2: Install Asset Pack (15-30 minutes)

- [ ] Open Epic Games Launcher
- [ ] Go to Marketplace tab
- [ ] Search for chosen asset pack
- [ ] Click "Add to Project"
- [ ] Select SubspaceUE project
- [ ] Wait for download to complete
- [ ] Launch Unreal Editor and verify assets in Content Browser

### Step 3: Basic Scene Setup (30-60 minutes)

#### Option A: Pre-built Blueprint (FASTEST)
- [ ] Find BP_SpaceScene in Content Browser
- [ ] Drag into level viewport
- [ ] Position at (0, 0, 0)
- [ ] Adjust properties in Details Panel
- [ ] Press Alt+P to test

#### Option B: Manual Setup (MORE CONTROL)
- [ ] Locate SpaceSkyboxActor in World Outliner
- [ ] Assign new skybox material from asset pack
- [ ] Adjust Star Brightness to 1.5
- [ ] Add planet blueprints to scene
- [ ] Position planets far from origin (50000+ units)
- [ ] Add asteroid field blueprints
- [ ] Configure density and distribution

### Step 4: Customize Materials (30 minutes)

- [ ] Right-click skybox material → Create Material Instance
- [ ] Name: MI_SpaceSkybox_Custom
- [ ] Assign to SpaceSkyboxActor
- [ ] Adjust parameters:
  - [ ] Star Density: 0.3-0.9
  - [ ] Star Size: 0.5-2.0
  - [ ] Nebula Opacity: 0.2-0.6
  - [ ] Colors to match your style

### Step 5: Lighting Setup (15 minutes)

- [ ] Place Directional Light (sun/star)
  - Intensity: 10-50
  - Color: Slight yellow (1.0, 0.95, 0.85)
- [ ] Place Sky Light
  - Intensity: 0.1-0.5
  - Source: Specified Cubemap (if available)
- [ ] Create Post Process Volume (Unbound)
  - Enable Bloom (Intensity: 0.5-1.0)
  - Adjust Exposure Compensation: 0-1
  - Set Color Grading (Saturation: 1.1-1.3)

### Step 6: Performance Optimization (30 minutes)

- [ ] Enable LODs on all static meshes
- [ ] Set cull distances:
  - Planets: 200000
  - Asteroids: 50000-100000
- [ ] Use Instanced Static Meshes for asteroids
- [ ] Enable texture streaming
- [ ] Test performance with `Stat FPS` command
- [ ] Adjust settings to maintain 60+ FPS

### Step 7: Test and Validate (15 minutes)

- [ ] Press Alt+P to play in editor
- [ ] Check visual quality
- [ ] Test camera movement
- [ ] Verify no performance drops
- [ ] Check for visual artifacts
- [ ] Adjust as needed

---

## Essential Console Commands

```
# Performance monitoring
Stat FPS        # Show frame rate
Stat Unit       # Show frame time breakdown
Stat RHI        # Show rendering statistics

# Visual debugging
Show Collision  # Toggle collision visualization
Show Bounds     # Toggle bounding box display
viewmode lit    # Normal lit view
viewmode unlit  # Unlit view (check emissive)
```

---

## Quick Settings Reference

### For High-End PC (RTX 3070+)
```
Planets: 5-10
Asteroids: 500-1000
Niagara Particles: 5000-10000
Draw Distance: 200000
Post-Processing: Full
```

### For Mid-Range PC (GTX 1660+)
```
Planets: 3-5
Asteroids: 200-500
Niagara Particles: 2000-5000
Draw Distance: 100000
Post-Processing: Balanced
```

### For Low-End / Steam Deck
```
Planets: 1-3
Asteroids: 50-200
Niagara Particles: 500-2000
Draw Distance: 50000
Post-Processing: Minimal
```

---

## Troubleshooting Quick Fixes

### Black Skybox
- Check material is assigned and set to Unlit
- Verify emissive values are not zero
- Check skybox scale (X should be negative)

### Poor Performance
- Reduce asteroid count by 50%
- Enable LODs on all meshes
- Lower draw distances
- Reduce particle counts

### Planets Look Flat
- Increase distance from camera
- Add Directional Light
- Enable atmosphere materials
- Add rim lighting (Fresnel)

### Can't Find Assets
- Refresh Content Browser (Right-click → Refresh)
- Restart Unreal Editor
- Verify download completed in Epic Launcher

---

## Common Material Parameters

Most space asset materials use these parameters:

```
Star Brightness: 0.5-2.0
Star Density: 0.3-0.9
Star Size: 0.5-2.0
Star Color: White to Yellow
Nebula Opacity: 0.2-0.6
Nebula Color: RGB values
Background Color: Dark blue/purple
Planet Atmosphere: 0.1-0.3 thickness
```

---

## Recommended First Test Scene

Simple but effective setup:

1. **Skybox:** Nebula material with purple/blue tint
2. **Planets:** 1-2 distant planets (different sizes)
3. **Asteroids:** 1 small field (100-200 asteroids)
4. **Lighting:** 1 Directional Light + 1 Sky Light
5. **Post-Process:** Bloom enabled, slight color grading

**Expected Performance:** 60+ FPS on mid-range hardware

---

## Next Steps After Basic Setup

Once you have a working scene:

- [ ] Experiment with different skybox materials
- [ ] Add variety to planets (sizes, colors, atmospheres)
- [ ] Create navigation lanes through asteroid fields
- [ ] Add point lights for stations or events
- [ ] Implement dynamic spawning for large areas
- [ ] Create multiple sector variations
- [ ] Set up level streaming for sector transitions

---

## Asset Pack Quick Comparison

| Pack | Setup Time | Quality | Flexibility | Best For |
|------|-----------|---------|------------|----------|
| **Space Creator Pro** | 15-30 min | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ | Rapid prototyping |
| **Space Scene UE5** | 1-2 hours | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ | Cinematic quality |
| **Space Skybox** | 15-30 min | ⭐⭐⭐⭐ | ⭐⭐⭐ | Quick backgrounds |
| **Cosmic Forge** | 2-4 hours | ⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ | Procedural variety |
| **Free Packs** | 30-60 min | ⭐⭐ | ⭐⭐ | Learning/testing |

---

## Success Checklist

Your scene is ready when:

- [ ] Skybox appears at infinite distance
- [ ] No visible seams or tiling in starfield
- [ ] Planets have proper scale and distance
- [ ] Asteroids provide visual interest without clutter
- [ ] Lighting creates appropriate space mood
- [ ] Maintains 60+ FPS on target hardware
- [ ] No z-fighting or visual artifacts
- [ ] Scene loads in under 5 seconds
- [ ] Camera movement feels smooth
- [ ] Space feels vast but not empty

---

## Resources

- **Full Guide:** [SPACE_SCENE_GENERATION_WITH_STORE_ASSETS.md](SPACE_SCENE_GENERATION_WITH_STORE_ASSETS.md)
- **Skybox Materials:** [SKYBOX_MATERIAL_GUIDE.md](SKYBOX_MATERIAL_GUIDE.md)
- **Camera Setup:** [CAMERA_AND_VISUAL_IMPROVEMENTS.md](CAMERA_AND_VISUAL_IMPROVEMENTS.md)
- **Documentation Index:** [DOCUMENTATION_INDEX.md](DOCUMENTATION_INDEX.md)

---

**Estimated Total Time:** 2-4 hours from start to working scene  
**Skill Level Required:** Beginner to Intermediate  
**Budget:** $0-50 (depending on asset choice)

---

*Last Updated: 2026-01-07*  
*Compatible with: Unreal Engine 5.6*
