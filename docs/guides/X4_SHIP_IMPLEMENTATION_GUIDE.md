# X4 Ship System Implementation Guide

## Overview

This document explains how to use the newly implemented X4-style ship system in SubspaceUE, including the Ulysses starter ship, interior system, and equipment system.

## Table of Contents

1. [Ship Classes](#ship-classes)
2. [Ulysses Starter Ship](#ulysses-starter-ship)
3. [Ship Interior System](#ship-interior-system)
4. [Ship Equipment System](#ship-equipment-system)
5. [Integration with GameMode](#integration-with-gamemode)
6. [Blueprint Usage](#blueprint-usage)

---

## Ship Classes

### X4ShipClass Enum

15 ship classes organized by size:

**Small (S) Class:**
- `Fighter_Light` - Fast scouts and interceptors
- `Fighter_Heavy` - Combat fighters
- `Miner_Small` - Small mining vessels

**Medium (M) Class:**
- `Corvette` - Light warships (Ulysses is this class)
- `Frigate` - Medium warships
- `Gunboat` - Heavy gunboats
- `Miner_Medium` - Optimal mining ships
- `Freighter_Medium` - Medium cargo haulers

**Large (L) Class:**
- `Destroyer` - Heavy combat ships
- `Freighter_Large` - Large cargo vessels
- `Miner_Large` - Heavy mining platforms

**Extra Large (XL) Class:**
- `Battleship` - Capital warships
- `Carrier` - Fleet carriers
- `Builder` - Construction ships

### Design Styles

- `Balanced` - Angular, industrial (default)
- `Aggressive` - Sharp, aggressive lines
- `Durable` - Bulky, reinforced
- `Sleek` - Smooth curves
- `Advanced` - High-tech, clean lines
- `Alien` - Unconventional designs

### Ship Variants

- `Standard` - Balanced variant (default)
- `Sentinel` - More hull/cargo, slower
- `Vanguard` - Faster, lighter defense/cargo
- `Military` - Combat-oriented variant

---

## Ulysses Starter Ship

### Overview

The **Ulysses** is the default starter ship, a Corvette-class vessel designed for early-game exploration, combat, and resource gathering.

### Base Statistics

```cpp
// Hull & Shields
Hull: 1500 HP
MaxHull: 1500 HP
Shield: 750 HP
MaxShield: 750 HP

// Movement
Mass: 500 tons
MaxSpeed: 80 m/s
Thrust: 5000 N
TurnRate: 2 rad/s

// Systems
CargoCapacity: 50 units
PowerGeneration: 500 W
PowerConsumption: 100 W

// Weapons
PrimaryWeaponSlots: 2
TurretSlots: 0
UtilitySlots: 2
```

### Default Equipment

- **2x Pulse Laser Mk1** - Primary weapons (100 damage, 1000m range, 2 shots/sec)
- **1x Mining Laser Mk1** - Resource gathering (50 damage, 500m range)
- **1x Shield Generator Mk1** - Defense (750 shield points, regenerates over time)

### Usage in C++

```cpp
// Spawn Ulysses in GameMode
AUlyssesShip* UlyssesShip = GetWorld()->SpawnActor<AUlyssesShip>(
    AUlyssesShip::StaticClass(),
    SpawnLocation,
    SpawnRotation
);

// Initialize with defaults
UlyssesShip->InitializeUlysses();

// Get ship stats
float HullPercent = UlyssesShip->GetHullPercentage();
float ShieldPercent = UlyssesShip->GetShieldPercentage();
float CurrentSpeed = UlyssesShip->GetCurrentSpeed();

// Apply damage
UlyssesShip->TakeDamage(250.0f);
```

---

## Ship Interior System

### Interior Cell Types

The `UShipInteriorComponent` supports 10 room types:
- Cockpit/Bridge
- Crew Quarters
- Cargo Bay
- Engine Room
- Medical Bay
- Armory
- Laboratory
- Recreation
- Corridor
- Airlock

### Interior Object Types

12 object types available:
- Terminal (Computer access)
- Chair/Seat
- Storage Container
- Bed
- Locker
- Cargo Crate
- Workbench
- Power Node
- Control Console
- Table
- Light Fixture
- Door

**Note:** Ulysses uses 14 total object instances across all rooms (multiple chairs, terminals, etc.)

### Ulysses Interior Layout

**1. Cockpit/Bridge** (Forward)
- Captain's chair (1)
- Helm console (1)
- Navigation terminal (1)
- Tactical terminal (1)
- **4 objects total**
- Crew capacity: 3

**2. Crew Quarters** (Mid-Forward)
- 4 crew bunks (beds)
- 4 personal lockers
- Central table (1)
- **9 objects total**
- Crew capacity: 4

**3. Cargo Bay** (Mid-Aft)
- 6 cargo crates (3x2 grid)
- 4 wall-mounted storage containers
- **10 objects total**
- Crew capacity: 0

**4. Engine Room** (Aft)
- 3 power nodes
- Engineering terminal (1)
- Maintenance workbench (1)
- **5 objects total**
- Crew capacity: 2

**Total Object Count:** 28 objects across 4 rooms  
**Total Crew Capacity:** 9

### Usage in C++

```cpp
// Access ship interior component
UShipInteriorComponent* Interior = UlyssesShip->Interior;

// Generate Ulysses standard interior
Interior->GenerateUlyssesInterior();

// Get specific room
FInteriorCell CockpitCell;
if (Interior->GetCellByType(EInteriorCellType::Cockpit, CockpitCell))
{
    // Access cockpit data
    FString RoomName = CockpitCell.CellName;
    TArray<FInteriorObject> Objects = CockpitCell.PlacedObjects;
}

// Get all rooms of a type
TArray<FInteriorCell> AllQuarters = Interior->GetCellsByType(EInteriorCellType::CrewQuarters);

// Get total crew capacity
int32 TotalCrew = Interior->GetTotalCrewCapacity();  // Returns 9 for Ulysses
```

### Blueprint Usage

```cpp
// In Blueprint, Interior is exposed as a component
Get Interior Component → Generate Ulysses Interior

// Query rooms
Get Cells By Type (Cockpit) → For Each Cell → Print Cell Name

// Get crew capacity
Get Total Crew Capacity → Print (Returns 9)
```

---

## Ship Equipment System

### Equipment Slot Types

- `PrimaryWeapon` - Fixed forward guns
- `Turret` - 360° rotating turrets
- `Utility` - Mining lasers, salvage beams, tractor beams
- `Shield` - Shield generators
- `Engine` - Propulsion systems
- `PowerGenerator` - Power reactors

### Equipment Types

**Weapons:**
- Pulse Laser
- Beam Laser
- Plasma Cannon
- Railgun
- Missile Launcher

**Utilities:**
- Mining Laser
- Salvage Beam
- Tractor Beam

**Systems:**
- Shield Generator
- Combat Engine
- Travel Engine
- Power Reactor

### Ulysses Default Loadout

```cpp
// 5 Equipment Slots Total:

1. Primary Weapon 1 (Forward Left): Pulse Laser Mk1
   - Damage: 100
   - Range: 1000m
   - Fire Rate: 2/sec
   - Power: 50W

2. Primary Weapon 2 (Forward Right): Pulse Laser Mk1
   - (Same as above)

3. Utility Slot 1 (Ventral): Mining Laser Mk1
   - Damage: 50
   - Range: 500m
   - Fire Rate: 1/sec
   - Power: 75W

4. Utility Slot 2 (Dorsal): Empty
   - (Available for future upgrades)

5. Shield Generator: Shield Generator Mk1
   - Shield Points: 750
   - Power: 100W
```

### Usage in C++

```cpp
// Access equipment component
UShipEquipmentComponent* Equipment = UlyssesShip->Equipment;

// Setup default equipment
Equipment->SetupUlyssesEquipment();

// Install new equipment
FEquipmentItem NewLaser = Equipment->CreatePulseLaser(2);  // Level 2 laser
Equipment->InstallEquipment(0, NewLaser);

// Remove equipment
FEquipmentItem RemovedItem;
if (Equipment->RemoveEquipment(3, RemovedItem))
{
    // Item removed successfully
}

// Query equipment
TArray<FEquipmentSlot> WeaponSlots = Equipment->GetWeaponSlots();
TArray<FEquipmentSlot> UtilitySlots = Equipment->GetSlotsByType(EEquipmentSlotType::Utility);

// Get power consumption
float TotalPower = Equipment->GetTotalPowerConsumption();  // Returns 275W for Ulysses default
```

### Blueprint Usage

```cpp
// In Blueprint, Equipment is exposed as a component
Get Equipment Component → Setup Ulysses Equipment

// Install equipment
Create Pulse Laser (Level 2) → Install Equipment (Slot 0) → Success?

// Query slots
Get Weapon Slots → For Each Slot → Print Equipment Name

// Check power
Get Total Power Consumption → Print (Returns 275W)
```

---

## Integration with GameMode

### Spawning Ulysses as Player Ship

Add to `ASubspaceGameMode::BeginPlay()`:

```cpp
void ASubspaceGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Spawn Ulysses as player ship
    FVector SpawnLocation(0.0f, 0.0f, 500.0f);
    FRotator SpawnRotation(0.0f, 0.0f, 0.0f);

    AUlyssesShip* PlayerShip = GetWorld()->SpawnActor<AUlyssesShip>(
        AUlyssesShip::StaticClass(),
        SpawnLocation,
        SpawnRotation
    );

    if (PlayerShip)
    {
        // Initialize with defaults
        PlayerShip->InitializeUlysses();

        // Possess with player controller
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            PC->Possess(PlayerShip);
        }

        UE_LOG(LogTemp, Log, TEXT("Ulysses spawned and possessed"));
    }
}
```

### Setting Up Input

The Ulysses ship can use the existing `ASubspacePlayerPawn` input system, or you can create custom input for the ship.

---

## Blueprint Usage

### Creating a Blueprint Child of Ulysses

1. In Content Browser, right-click → Blueprint Class
2. Search for "UlyssesShip"
3. Name it "BP_UlyssesShip"
4. Open the Blueprint

### Setting Up Visual Mesh

In the Blueprint viewport:
1. Select "ShipMesh" component
2. Assign a Static Mesh (corvette model)
3. Adjust scale/rotation as needed

### Adding Visual Equipment

Create child Actor Components for visual weapon/equipment representation:

```cpp
// In Blueprint, add Static Mesh Components for weapons
- Primary_Weapon_L (left laser)
- Primary_Weapon_R (right laser)
- Mining_Laser (ventral)
```

### Exposing to Blueprint

All major functions are Blueprint-callable:

```cpp
// Stats
Get Hull Percentage → Returns 0-100
Get Shield Percentage → Returns 0-100
Get Current Speed → Returns m/s

// Combat
Take Damage (250.0) → Damages ship

// Interior
Get Interior Component → Get Total Crew Capacity

// Equipment
Get Equipment Component → Get Weapon Slots
```

---

## Testing Guide

### 1. Verify Ship Spawning

```cpp
// In GameMode or Test Level
1. Place a "BP_UlyssesShip" in the level
2. Play in Editor
3. Check Output Log for initialization messages:
   - "Ulysses initialized: Hull=1500, Shield=750, Speed=80.0 m/s"
   - "Ulysses equipment setup: 2 primary weapons, 2 utility slots"
   - "Generated Ulysses interior: 4 rooms, 9 crew capacity"
```

### 2. Test Interior System

```cpp
// In Blueprint or C++
1. Get Interior Component
2. Call "Generate Ulysses Interior"
3. Verify 4 cells created
4. Check crew capacity = 9
5. Inspect individual rooms and objects
```

### 3. Test Equipment System

```cpp
// In Blueprint or C++
1. Get Equipment Component
2. Call "Setup Ulysses Equipment"
3. Verify 5 equipment slots
4. Check power consumption = 275W
5. Test install/remove equipment
```

### 4. Test Damage System

```cpp
// In Blueprint or C++
1. Get initial hull/shield percentages (100%/100%)
2. Call Take Damage(500.0)
3. Shield should be at 0%, Hull at 100%
4. Wait for shield regeneration
5. Shield should regenerate to 100% over ~10 seconds
```

---

## Next Steps

### Phase 5: Modular Station System

- Port station module definitions
- Create station types (Trading Post, Shipyard, etc.)
- Implement station generation
- Add docking system

### Phase 6: X4-Style Map

- Enhance galaxy map UI
- Add sector information
- Implement trade routes
- Add highway system

---

## Troubleshooting

### Ship not initializing?

```cpp
// Check that InitializeUlysses() is called in BeginPlay
// Verify components are created in constructor
```

### Equipment slots not working?

```cpp
// Ensure SetupUlyssesEquipment() is called
// Check Equipment component exists
```

### Interior not generating?

```cpp
// Call GenerateUlyssesInterior() explicitly
// Check Interior component exists
```

---

## API Reference

### AUlyssesShip

```cpp
// Initialization
void InitializeUlysses();

// Stats
float GetHullPercentage() const;
float GetShieldPercentage() const;
float GetEnergyPercentage() const;
float GetCurrentSpeed() const;

// Combat
void TakeDamage(float Amount);
void RegenerateShields(float DeltaTime);

// Components
UShipInteriorComponent* Interior;
UShipEquipmentComponent* Equipment;
FX4ShipStats Stats;
FX4ShipConfig Config;
```

### UShipInteriorComponent

```cpp
// Cell Management
void AddCell(const FInteriorCell& Cell);
bool GetCellByType(EInteriorCellType Type, FInteriorCell& OutCell) const;
TArray<FInteriorCell> GetCellsByType(EInteriorCellType Type) const;
int32 GetTotalCrewCapacity() const;

// Generation
void GenerateUlyssesInterior();
```

### UShipEquipmentComponent

```cpp
// Slot Management
void AddEquipmentSlot(const FEquipmentSlot& Slot);
bool InstallEquipment(int32 SlotIndex, const FEquipmentItem& Equipment);
bool RemoveEquipment(int32 SlotIndex, FEquipmentItem& OutEquipment);

// Queries
TArray<FEquipmentSlot> GetSlotsByType(EEquipmentSlotType Type) const;
TArray<FEquipmentSlot> GetWeaponSlots() const;
float GetTotalPowerConsumption() const;

// Generation
void SetupUlyssesEquipment();
FEquipmentItem CreatePulseLaser(int32 Level);
FEquipmentItem CreateMiningLaser(int32 Level);
FEquipmentItem CreateShieldGenerator(int32 Level);
```

---

**Last Updated:** January 6, 2026  
**Version:** 1.0  
**Status:** Ready for Testing
