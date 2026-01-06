# Voxel Material System Guide

**Last Updated:** January 6, 2026  
**Status:** ✅ Complete - Implemented in UE5

## Overview

The Voxel Material System provides a tier-based progression system for ship construction materials, inspired by Avorion's material tiers. Materials range from basic Iron (available everywhere) to ultimate Avorion (only at galactic core), with each tier providing better stats and unlocking new capabilities.

## Material Tiers

### 🔩 Iron (Tier 0)
- **Unlock:** Available everywhere
- **Unlock Distance:** Unlimited
- **Color:** Gray (127, 127, 127)
- **Stat Multiplier:** 1.0x (baseline)
- **Tech Points:** 1.0x
- **Description:** Basic starting material. Available everywhere in the galaxy.

**Features:**
- Basic Mining
- Basic Hull
- Basic Engines

---

### ⚙️ Titanium (Tier 1)
- **Unlock:** Distance < 350 sectors from center
- **Color:** Silver-Blue (179, 204, 230)
- **Stat Multiplier:** 1.3x
- **Tech Points:** 1.5x
- **Durability:** 1.5x Iron
- **Mass:** 0.9x Iron (lighter!)
- **Description:** Stronger than iron. Provides improved hull strength and weapon damage.

**New Features:**
- Improved Hull Strength
- Better Weapons

---

### 💚 Naonite (Tier 2)
- **Unlock:** Distance < 250 sectors from center
- **Color:** Bright Green (51, 230, 77)
- **Stat Multiplier:** 1.6x
- **Tech Points:** 2.5x
- **Durability:** 2.0x Iron
- **Mass:** 0.8x Iron
- **Shield:** 1.0x (SHIELDS UNLOCKED!)
- **Description:** Unlocks shields! Essential for survival in dangerous sectors.

**New Features:**
- Shield Generators ⚡
- Advanced Weapons
- Salvaging

---

### 🔷 Trinium (Tier 3)
- **Unlock:** Distance < 150 sectors from center
- **Color:** Blue (77, 153, 255)
- **Stat Multiplier:** 2.0x
- **Tech Points:** 4.0x
- **Durability:** 2.5x Iron
- **Mass:** 0.6x Iron (very light!)
- **Energy Efficiency:** 1.5x
- **Description:** Lightweight and energy-efficient. Great for thrusters and power systems.

**New Features:**
- Energy Management
- Advanced Thrusters
- Jump Drives 🌌

---

### 🌟 Xanion (Tier 4)
- **Unlock:** Distance < 75 sectors from center
- **Color:** Gold (255, 230, 51)
- **Stat Multiplier:** 2.5x
- **Tech Points:** 6.0x
- **Durability:** 3.0x Iron
- **Mass:** 0.5x Iron
- **Energy Efficiency:** 1.8x
- **Description:** Advanced material with excellent power generation capabilities.

**New Features:**
- Improved Power Generation
- Advanced Mining
- Refining Stations

---

### 🔥 Ogonite (Tier 5)
- **Unlock:** Distance < 50 sectors from center
- **Color:** Orange-Red (255, 102, 38)
- **Stat Multiplier:** 3.0x
- **Tech Points:** 9.0x
- **Durability:** 4.0x Iron
- **Mass:** 0.4x Iron
- **Energy Efficiency:** 2.2x
- **Description:** Heavy and durable. Perfect for large capital ships and defensive structures.

**New Features:**
- Advanced Trading
- Fleet Management 🚀
- Captain Automation

---

### 💜 Avorion (Tier 6 - Ultimate)
- **Unlock:** Distance < 25 sectors from center (Galactic Core!)
- **Color:** Purple (217, 51, 255)
- **Stat Multiplier:** 4.0x
- **Tech Points:** 15.0x
- **Durability:** 5.0x Iron
- **Mass:** 0.3x Iron (lightest!)
- **Energy Efficiency:** 3.0x
- **Shield:** 3.5x
- **Description:** The ultimate material. Only found at the galactic core. Unlocks all capabilities.

**New Features:**
- Barrier Access
- Boss Encounters 👹
- Endgame Content
- Ultimate Upgrades

## Usage in UE5

### C++ Usage

```cpp
#include "VoxelMaterial.h"

// Get material properties
EMaterialTier Tier = EMaterialTier::Trinium;
FVoxelMaterialProperties Props = UVoxelMaterialLibrary::GetMaterialProperties(Tier);

// Access properties
float Durability = Props.DurabilityMultiplier;
FColor MaterialColor = Props.Color;
int32 UnlockDistance = Props.UnlockDistance;

// Get material by name
FVoxelMaterialProperties IronProps = UVoxelMaterialLibrary::GetMaterialPropertiesByName(TEXT("Iron"));

// Helper functions
FColor Color = UVoxelMaterialLibrary::GetMaterialColor(EMaterialTier::Naonite);
float StatMult = UVoxelMaterialLibrary::GetStatMultiplier(EMaterialTier::Xanion);
FString Description = UVoxelMaterialLibrary::GetMaterialDescription(EMaterialTier::Avorion);
```

### Blueprint Usage

```blueprint
// Get Material Properties
Get Material Properties (Voxel Material Library)
  - Tier: [Select EMaterialTier]
  - Returns: FVoxelMaterialProperties

// Get Material Color
Get Material Color (Voxel Material Library)
  - Tier: Naonite
  - Returns: FColor (Bright Green)

// Get Unlocked Features
Get Unlocked Features (Voxel Material Library)
  - Tier: Trinium
  - Returns: Array of Strings (feature names)
```

## Material Properties Breakdown

### FVoxelMaterialProperties Structure

```cpp
USTRUCT(BlueprintType)
struct FVoxelMaterialProperties
{
    FString Name;                    // Display name
    EMaterialTier Tier;              // Tier enum
    float DurabilityMultiplier;      // vs Iron (1.0 = baseline)
    float MassMultiplier;            // vs Iron (lower = lighter)
    float EnergyEfficiency;          // Power system efficiency
    float ShieldMultiplier;          // Shield capacity
    int32 TechLevel;                 // Required tech level
    FColor Color;                    // Material color for rendering
    int32 UnlockDistance;            // Sectors from galactic center
    float StatMultiplier;            // Overall stat boost
    float TechPointsMultiplier;      // Research/upgrade multiplier
};
```

### Property Comparison Table

| Material | Durability | Mass | Energy | Shield | Tech Pts |
|----------|-----------|------|--------|--------|----------|
| Iron     | 1.0x | 1.0x | 1.0x | 0.0x | 1.0x |
| Titanium | 1.5x | 0.9x | 1.1x | 0.5x | 1.5x |
| Naonite  | 2.0x | 0.8x | 1.3x | 1.0x | 2.5x |
| Trinium  | 2.5x | 0.6x | 1.5x | 1.5x | 4.0x |
| Xanion   | 3.0x | 0.5x | 1.8x | 2.0x | 6.0x |
| Ogonite  | 4.0x | 0.4x | 2.2x | 2.5x | 9.0x |
| Avorion  | 5.0x | 0.3x | 3.0x | 3.5x | 15.0x |

## Integration with Voxel Blocks

### Automatic Property Calculation

When creating a voxel block, properties are automatically calculated based on material:

```cpp
FVoxelBlock Block(
    Position,
    Size,
    TEXT("Trinium"),  // Material name
    EBlockType::Engine,
    EBlockShape::Cube,
    EBlockOrientation::PosY
);

// Properties automatically calculated:
// - Mass = Volume * MaterialMassMultiplier
// - Durability = 100 * MaterialDurabilityMultiplier * Volume
// - Color = Material.Color
// - Functional stats (thrust, power, shields) based on block type
```

### Block Type Modifiers

Material properties are further modified by block type:

```cpp
// Armor: 5x durability, 1.5x mass
// Engines: ThrustPower = 50 * Volume * EnergyEfficiency
// Generators: PowerGen = 100 * Volume * EnergyEfficiency
// Shield Generators: Capacity = 200 * Volume * ShieldMultiplier
```

## Progression System

### Galactic Center Distance

Materials unlock as players travel toward the galactic core (0, 0, 0):

```cpp
// Check if material is available at current location
FVector PlayerPosition = GetActorLocation();
float Distance = PlayerPosition.Size(); // Distance from (0,0,0)

EMaterialTier AvailableTier;
if (Distance < 25) AvailableTier = EMaterialTier::Avorion;
else if (Distance < 50) AvailableTier = EMaterialTier::Ogonite;
else if (Distance < 75) AvailableTier = EMaterialTier::Xanion;
// ... etc
```

### Feature Unlocks

Query what features are available at a tier:

```cpp
TArray<FString> Features = UVoxelMaterialLibrary::GetUnlockedFeatures(EMaterialTier::Naonite);
// Returns: ["Basic Mining", "Basic Hull", "Basic Engines", 
//           "Improved Hull Strength", "Better Weapons",
//           "Shield Generators", "Advanced Weapons", "Salvaging"]
```

## Best Practices

### 1. Material Selection for Ship Parts

- **Hull/Armor:** Use heaviest available (Ogonite for tanky ships)
- **Engines/Thrusters:** Use lightest (Trinium, Xanion)
- **Generators:** Use highest energy efficiency (Avorion)
- **Shields:** Use highest shield multiplier (Avorion)

### 2. Performance Optimization

```cpp
// Cache material properties instead of repeated lookups
static FVoxelMaterialProperties CachedProps = 
    UVoxelMaterialLibrary::GetMaterialProperties(Tier);
```

### 3. UI Display

```cpp
// Get human-readable information for UI
FString Name = UVoxelMaterialLibrary::GetMaterialDisplayName(Tier);
FString Desc = UVoxelMaterialLibrary::GetMaterialDescription(Tier);
FColor Color = UVoxelMaterialLibrary::GetMaterialColor(Tier);
```

## Implementation Notes

### File Locations

- **Header:** `/Source/SubspaceUE/Public/VoxelMaterial.h`
- **Implementation:** `/Source/SubspaceUE/Private/VoxelMaterial.cpp`
- **Integration:** `/Source/SubspaceUE/Private/VoxelBlock.cpp`

### Static Initialization

Material properties are initialized once on first access:

```cpp
// Thread-safe lazy initialization
static bool bInitialized = false;
static TMap<EMaterialTier, FVoxelMaterialProperties> MaterialTable;

if (!bInitialized)
{
    InitializeMaterialTable();
    bInitialized = true;
}
```

### Blueprint Accessibility

All functions are marked `UFUNCTION(BlueprintCallable)` for easy Blueprint access.

## Testing

### Test Cases

1. **Material Lookup:** Verify all 7 tiers return correct properties
2. **Color Rendering:** Check voxel blocks display correct material colors
3. **Stat Scaling:** Validate durability/mass calculations
4. **Progression:** Test unlock distances match galactic position
5. **Feature Unlocks:** Verify feature arrays contain expected items

### Debug Commands

```cpp
// Log all material properties
for (int32 i = 0; i <= 6; ++i)
{
    EMaterialTier Tier = static_cast<EMaterialTier>(i);
    FVoxelMaterialProperties Props = UVoxelMaterialLibrary::GetMaterialProperties(Tier);
    UE_LOG(LogTemp, Log, TEXT("%s: Dur=%.1f, Mass=%.1f, Energy=%.1f"), 
        *Props.Name, Props.DurabilityMultiplier, Props.MassMultiplier, Props.EnergyEfficiency);
}
```

## Future Enhancements

- [ ] Material-specific visual shaders (metallic, glow effects)
- [ ] Material rarity system (resource scarcity)
- [ ] Hybrid material blocks (combine two materials)
- [ ] Material research/unlock system
- [ ] Material-specific sound effects
- [ ] Visual feedback for material tier (glows, particle effects)

## References

- C# Implementation: `AvorionLike/Core/Progression/MaterialTier.cs`
- Avorion Wiki: [Materials](https://avorion.gamepedia.com/Materials)
- Block Properties: `AvorionLike/Core/Voxel/VoxelBlock.cs`

---

**Implementation Status:** ✅ Complete  
**Blueprint Support:** ✅ Full  
**Integration:** ✅ VoxelBlock system  
**Next Steps:** Create visual material shaders with tier-specific effects
