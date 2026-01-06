# Creating a Space Skybox Material - Quick Guide

This guide shows you how to create a simple starfield material for the SpaceSkyboxActor.

## Method 1: Simple Star Texture (Easiest)

### Materials Needed
- A starfield texture (2048×2048 or larger recommended)
- Unreal Engine Material Editor

### Steps

1. **Create New Material**
   - Right-click in Content Browser → Material
   - Name it: `M_SpaceSkybox`

2. **Material Settings**
   - Shading Model: **Unlit** (no lighting needed)
   - Blend Mode: **Opaque**

3. **Add Texture**
   - Drag your starfield texture into the material graph
   - Connect to **Emissive Color**

4. **Add Parameters** (Optional)
   ```
   TextureSample → Multiply → Emissive Color
                      ↑
                  Scalar Parameter (StarBrightness)
   ```

5. **Assign to Skybox**
   - Place `SpaceSkyboxActor` in level
   - Set `SkyboxMaterial` to your new material

## Method 2: Procedural Starfield (No Texture)

### Steps

1. **Create Material** (`M_ProceduralStarfield`)

2. **Add Noise Function**
   ```
   Material Graph:
   
   WorldPosition → Divide(10000) → Noise → 
   → Power(50) → Multiply(Brightness) → Emissive
   ```

3. **Detailed Node Setup**:
   
   **A. World Position**
   - Add node: `Absolute World Position`
   - This gives unique coordinates for each pixel
   
   **B. Scale Down**
   - Add: `Divide` node
   - Value: 10000 (controls star size/density)
   
   **C. Noise Pattern**
   - Add: `Noise` node (Simple or Perlin)
   - Connect to scaled world position
   
   **D. Make Stars Sharp**
   - Add: `Power` node
   - Exponent: 50-100 (higher = smaller/sharper stars)
   
   **E. Brightness Control**
   - Add: `Multiply` node
   - Add: `Scalar Parameter` named "StarBrightness"
   - Default value: 1.0
   
   **F. Color**
   - Add: `Multiply` node (optional)
   - Add: `Vector Parameter` named "StarColor"
   - Default: (1, 1, 1) = white

4. **Connect to Output**
   - Final result → **Emissive Color**

## Method 3: Multi-Layer Starfield (Best Quality)

### Advanced Setup

```
Material Graph Overview:

Layer 1 (Big Stars):
  WorldPos → Scale(5000) → Noise → Power(100) → Multiply

Layer 2 (Medium Stars):
  WorldPos → Scale(15000) → Noise → Power(80) → Multiply

Layer 3 (Small Stars):
  WorldPos → Scale(30000) → Noise → Power(60) → Multiply

Nebula:
  WorldPos → Scale(2000) → Noise → Color → Multiply

All layers → Add → Emissive Color
```

### Detailed Multi-Layer Setup

1. **Create 3 Star Layers**:
   - Each layer uses different scale values
   - Different power values for size variation
   - Different brightness multipliers

2. **Add Nebula Layer**:
   ```
   WorldPosition → Divide(2000) → Noise 
   → Multiply(NebulaColor Parameter) 
   → Multiply(0.3) → Add to stars
   ```

3. **Color Variation** (Optional):
   ```
   Add node: Lerp
   - A: Blue-white (hot stars)
   - B: Orange-red (cool stars)
   - Alpha: Noise (random per star)
   ```

4. **Parameters to Expose**:
   - StarBrightness (Scalar, default: 1.0)
   - StarDensity (Scalar, default: 0.5)
   - NebulaColor (Vector, default: Purple)
   - NebulaIntensity (Scalar, default: 0.3)

## Material Parameters for Dynamic Control

### In Material Blueprint

Add these parameters so you can control them from SpaceSkyboxActor:

```cpp
// Material Parameters
Scalar: StarBrightness (0-10, default: 1.0)
Scalar: StarDensity (0-1, default: 0.5)
Vector: NebulaColor (RGB, default: 0.1, 0.05, 0.2)
Scalar: NebulaIntensity (0-1, default: 0.3)
```

### In C++ (Already Implemented)

The `SpaceSkyboxActor` will automatically set these:

```cpp
DynamicMaterial->SetScalarParameterValue(TEXT("StarBrightness"), StarBrightness);
DynamicMaterial->SetScalarParameterValue(TEXT("StarDensity"), StarDensity);
DynamicMaterial->SetVectorParameterValue(TEXT("NebulaColor"), NebulaColor);
```

## Quick Start Material Graph

Here's a minimal working setup:

```
[Absolute World Position]
         ↓
    [Divide: 15000]
         ↓
    [Noise: Simple]
         ↓
    [Power: 75]
         ↓
    [Multiply: StarBrightness]
         ↓
   [Emissive Color]
```

### Node Values:
- **Divide**: Controls star density (lower = more stars)
- **Power**: Controls star sharpness (higher = smaller stars)
- **StarBrightness**: Multiplier for intensity (1.0 = normal)

## Testing Your Material

1. **Assign Material**:
   - Select `SpaceSkyboxActor` in World Outliner
   - Set `SkyboxMaterial` to your material

2. **Test Brightness**:
   - Change `StarBrightness` value
   - Should see immediate update

3. **Test Density**:
   - Modify the Divide value (lower = denser)
   - Or expose as parameter

4. **Test in Motion**:
   - Enable `bRotateSkybox`
   - Set `RotationSpeed` to 1.0
   - Should rotate slowly

## Using Free Skybox Textures

### Where to Find

1. **Unreal Marketplace** (Free):
   - Search: "Space Skybox"
   - Many free options available

2. **Procedural Skybox Plugins**:
   - Ultra Dynamic Sky
   - Time of Day

3. **Free Texture Sites**:
   - textures.com
   - quixel.com (Megascans - free with Epic account)
   - nasa.gov (actual space photos!)

### Importing Textures

1. Drag image into Content Browser
2. Import as Texture
3. Set Compression: **Default** or **BC7**
4. Set Texture Group: **World**
5. Mip Gen Settings: **FromTextureGroup**
6. Never Stream: **True** (keeps in memory)

## Common Issues

### Stars Too Large
- **Fix**: Increase Power value (75 → 100+)

### Not Enough Stars
- **Fix**: Decrease Divide value (15000 → 5000)

### Too Bright
- **Fix**: Lower StarBrightness parameter

### Tiling Visible
- **Fix**: Use larger scale values or add second noise layer

### Performance Issues
- **Fix**: Use simpler noise (Simple vs. Gradient)
- **Fix**: Reduce number of layers
- **Fix**: Use texture instead of procedural

## Recommended Settings

### For Realistic Space
```
StarBrightness: 0.8
StarDensity: 0.6
NebulaColor: (0.05, 0.1, 0.2) - Dark blue
Power: 85
Scale: 12000
```

### For Colorful Nebula
```
StarBrightness: 1.2
NebulaColor: (0.2, 0.05, 0.3) - Purple/Magenta
NebulaIntensity: 0.5
Power: 70
```

### For Dense Starfield
```
StarDensity: 0.9
Scale: 5000 (more stars)
Power: 100 (keep them small)
```

## Advanced Tips

1. **Add Distant Galaxies**:
   - Use second noise layer
   - Very low power (10-20)
   - Very low intensity

2. **Pulsing Stars**:
   - Add Time node
   - Multiply with sine wave
   - Add to brightness

3. **Color Variation**:
   - Use noise as Lerp alpha
   - Lerp between white and yellow/blue

4. **Milky Way Effect**:
   - Add stretched noise (scale differently on X/Y)
   - Very low opacity
   - Align with one axis

## Reference Images

Look at these space games for inspiration:
- **Elite Dangerous** - Realistic Milky Way
- **X4: Foundations** - Colorful nebulae
- **Star Citizen** - Dense starfields
- **No Man's Sky** - Vibrant colors

---

*For more information, see CAMERA_AND_VISUAL_IMPROVEMENTS.md*
