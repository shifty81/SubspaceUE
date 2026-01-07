# X4 Systems Quick Reference Guide

**Quick reference for using the X4-style systems in SubspaceUE**

---

## Component Overview

| Component | Purpose | Key Features |
|-----------|---------|--------------|
| **ShipEquipmentComponent** | Manage ship equipment | 24 equipment types, weapons, engines, utilities |
| **TradingComponent** | Economy & trading | 16 wares, dynamic pricing, production chains |
| **NavigationComponent** | Travel & autopilot | 6 travel modes, flight assist, docking |
| **CrewComponent** | Crew management | 5 roles, 5 skills, morale, training |

---

## Quick Setup Examples

### Basic Ship Setup

```cpp
// Create ship with all systems
AUlyssesShip* Ship = World->SpawnActor<AUlyssesShip>();

// Equipment (auto-configured)
Ship->Equipment->SetupUlyssesEquipment();

// Add trading
UTradingComponent* Trading = NewObject<UTradingComponent>(Ship);
Ship->AddInstanceComponent(Trading);
Trading->InitializeWareLibrary();
Trading->Credits = 50000;

// Add navigation
UNavigationComponent* Nav = NewObject<UNavigationComponent>(Ship);
Ship->AddInstanceComponent(Nav);

// Add crew
UCrewComponent* Crew = NewObject<UCrewComponent>(Ship);
Ship->AddInstanceComponent(Crew);
```

---

## Equipment System

### Installing Equipment

```cpp
// Get equipment component
auto Equipment = Ship->FindComponentByClass<UShipEquipmentComponent>();

// Create and install
auto PulseLaser = Equipment->CreatePulseLaser(3);  // Level 3
Equipment->InstallEquipment(0, PulseLaser);

auto Shield = Equipment->CreateShieldGenerator(2);
Equipment->InstallEquipment(4, Shield);
```

### Equipment Types Quick Ref

| Type | Damage | Range | Fire Rate | Special |
|------|--------|-------|-----------|---------|
| Pulse Laser | 80 | 1200m | 3.0/s | Reliable |
| Beam Laser | 50 | 1500m | 10.0/s | Continuous |
| Plasma Cannon | 200 | 800m | 1.0/s | High damage |
| Railgun | 350 | 2500m | 0.5/s | Long range |
| Gatling | 30 | 1000m | 15.0/s | Anti-fighter |
| Missile | 500 | 3000m | 0.33/s | Lock-on |
| Torpedo | 2000 | 5000m | 0.1/s | Anti-capital |

### Utility Equipment

```cpp
// Mining setup
auto MiningLaser = Equipment->CreateMiningLaser(2);
// 200 mining power/sec

// Salvage setup
auto SalvageBeam = Equipment->CreateSalvageBeam(2);
// 160 materials/sec

// Cargo expansion
auto CargoExt = Equipment->CreateCargoExtension(3);
// +300 cargo capacity
```

---

## Trading System

### Station Setup

```cpp
// Initialize trading at station
auto Trading = Station->FindComponentByClass<UTradingComponent>();
Trading->InitializeWareLibrary();

// Setup buy/sell orders
TArray<FString> BuyWares = {"Ore", "Silicon"};
TArray<FString> SellWares = {"Steel", "HullParts"};
Trading->SetupStationTrading(BuyWares, SellWares);

// Add initial stock
Trading->AddWareToStorage("Steel", 500);
Trading->Credits = 100000;
```

### Player Trading

```cpp
// Buy from station
int32 Cost;
if (PlayerTrading->BuyWare(Station, "Ore", 100, Cost))
{
    UE_LOG(LogTemp, Log, TEXT("Bought 100 ore for %d credits"), Cost);
}

// Sell to station
int32 Revenue;
if (PlayerTrading->SellWare(Station, "Steel", 50, Revenue))
{
    UE_LOG(LogTemp, Log, TEXT("Sold 50 steel for %d credits"), Revenue);
}
```

### Ware Reference

| Category | Wares | Production Chain |
|----------|-------|------------------|
| Raw | Ore, Silicon, Ice | Mined |
| Refined | Steel, Titanium, Crystals | Ore → Steel |
| Components | Hull Parts, Microchips, Engine Parts | Steel+Titanium → Hull Parts |
| Consumables | Food, Water, Medical | Produced |
| Technology | Advanced Electronics, Drones | Complex |

---

## Navigation System

### Travel Modes

```cpp
auto Nav = Ship->FindComponentByClass<UNavigationComponent>();

// Standard flight
Nav->SetTravelMode(ETravelMode::StandardFlight);

// Boost (2x speed, drains fuel)
Nav->ActivateBoost();
// Fuel: 100 max, 20/sec drain, 10/sec regen

// Travel drive (10x speed, 3s charge)
Nav->StartTravelDrive();
// Auto-activates when charged
```

### Autopilot

```cpp
// Autopilot to location
Nav->StartAutopilot(TargetLocation, true, false);
// Params: location, use_travel_drive, dock_on_arrival

// Autopilot to station with docking
Nav->StartAutopilotToActor(Station, true, true);

// Add waypoints
FNavigationWaypoint Waypoint;
Waypoint.Location = MiningField;
Waypoint.bUseTravelDrive = true;
Nav->AddWaypoint(Waypoint);

// Cancel
Nav->CancelAutopilot();
```

### Flight Assist Toggles

```cpp
// Toggle systems
Nav->ToggleAutoRoll();          // Auto-level ship
Nav->ToggleFlightAssist();      // Velocity damping
Nav->ToggleAimAssist();         // Weapon prediction
Nav->ToggleCollisionAvoidance(); // Auto-avoid obstacles
Nav->ToggleMouseSteering();     // Mouse controls
```

### Docking

```cpp
// Request docking
if (Nav->RequestDocking(Station))
{
    // Autopilot will handle approach and docking
}

// Undock
Nav->Undock();
// Ship automatically moves away from station
```

---

## Crew System

### Hiring Crew

```cpp
auto Crew = Ship->FindComponentByClass<UCrewComponent>();

// Generate available crew
auto Available = Crew->GenerateAvailableCrew(10, 1, 3);
// 10 crew, 1-3 star skills

// Hire
for (const FCrewMember& Candidate : Available)
{
    if (Crew->HireCrewMember(Candidate))
    {
        UE_LOG(LogTemp, Log, TEXT("Hired: %s"), *Candidate.Name);
    }
}
```

### Crew Roles & Skills

| Role | Primary Skill | Effect |
|------|--------------|--------|
| Captain | Management | Station/fleet efficiency |
| Pilot | Piloting | Ship maneuverability (0.5x-1.5x) |
| Service Crew | Engineering | Repair speed (0.5x-1.5x) |
| Marine | Boarding | Combat strength |
| Manager | Management | Station operations (0.5x-1.5x) |

### Training

```cpp
// Train crew member
Crew->TrainCrewMember(0, ESeminarType::Piloting);
// Cost: 5000 credits, +1 star

// Training types
ESeminarType::Piloting
ESeminarType::Boarding
ESeminarType::Management
ESeminarType::Engineering
ESeminarType::Morale
```

### Crew Management

```cpp
// Get effectiveness multipliers
float PilotBonus = Crew->GetPilotingEffectiveness();
// Returns 0.5 - 1.5 based on pilot skill and morale

float EngBonus = Crew->GetEngineeringEffectiveness();
float MgmtBonus = Crew->GetManagementEffectiveness();

// Award experience
Crew->AwardExperience(0, 500);  // +500 XP to crew index 0
Crew->AwardExperienceToAll(100); // +100 XP to all

// Morale management
Crew->BoostMorale(20.0f);   // +20 morale
Crew->ReduceMorale(10.0f);  // -10 morale
float AvgMorale = Crew->GetAverageMorale();
```

### Boarding Actions

```cpp
// Board enemy ship
if (Crew->BoardShip(EnemyShip))
{
    UE_LOG(LogTemp, Log, TEXT("Boarding successful!"));
    // Enemy loses crew, we lose some morale
}
else
{
    UE_LOG(LogTemp, Warning, TEXT("Boarding failed!"));
    // We lose crew, morale drops significantly
}

// Get boarding strength
int32 Strength = Crew->GetBoardingStrength();
// Based on number of marines × boarding skill × morale
```

---

## Common Patterns

### Complete Trade Mission

```cpp
// 1. Setup
Nav->StartAutopilotToActor(BuyStation, true, true);

// 2. Wait for arrival and docking
// (handled by autopilot)

// 3. Buy goods
int32 Cost;
Trading->BuyWare(BuyStation, "Ore", 100, Cost);

// 4. Undock and travel to sell station
Nav->Undock();
Nav->StartAutopilotToActor(SellStation, true, true);

// 5. Sell goods
int32 Revenue;
Trading->SellWare(SellStation, "Steel", 50, Revenue);

// 6. Profit
int32 Profit = Revenue - Cost;
```

### Combat Loadout

```cpp
// Heavy weapons
Equipment->InstallEquipment(0, Equipment->CreatePlasmaCannon(3));
Equipment->InstallEquipment(1, Equipment->CreateRailgun(3));

// Turrets for M/L ships
Equipment->InstallEquipment(2, Equipment->CreateBeamLaser(2));

// Defense
Equipment->InstallEquipment(3, Equipment->CreateShieldGenerator(3));
Equipment->InstallEquipment(4, Equipment->CreateCountermeasure(2));

// Hire combat crew
FCrewMember Marine = Crew->GenerateRandomCrew(3, 5)[0];
Marine.Role = ECrewRole::Marine;
Crew->HireCrewMember(Marine);
```

### Mining Operation

```cpp
// Install mining equipment
Equipment->InstallEquipment(0, Equipment->CreateMiningLaser(3));
Equipment->InstallEquipment(1, Equipment->CreateCargoExtension(2));

// Navigate to asteroid field
Nav->StartAutopilot(AsteroidFieldLocation, true);

// Start mining
// (mining logic goes here - aim at asteroids, extract resources)

// Return to sell
Nav->StartAutopilotToActor(Station, true, true);
Trading->SellWare(Station, "Ore", 500, Revenue);
```

---

## Performance Tips

### Update Frequencies
- **TradingComponent**: 1 second (production, salary)
- **NavigationComponent**: Every frame (smooth control)
- **CrewComponent**: 1 second (morale, salary)
- **EquipmentComponent**: No tick (event-driven)

### Optimization
```cpp
// Disable components when not needed
TradingComponent->SetComponentTickEnabled(false);  // When not trading
CrewComponent->SetComponentTickEnabled(false);      // When crew inactive

// Enable when needed
TradingComponent->SetComponentTickEnabled(true);
```

---

## Blueprint Usage

All systems are Blueprint-accessible:

```
// Equipment (Blueprint)
Equipment->Create Pulse Laser (Level: 3)
Equipment->Install Equipment (Slot Index: 0, Item: Laser)

// Trading (Blueprint)
Trading->Buy Ware (Station, Ware ID: "Ore", Quantity: 100)

// Navigation (Blueprint)
Navigation->Start Autopilot (Target Location, Use Travel Drive: true)
Navigation->Activate Boost

// Crew (Blueprint)
Crew->Hire Crew Member (New Crew)
Crew->Train Crew Member (Index: 0, Type: Piloting)
```

---

## Debug Commands

```cpp
// Equipment
UE_LOG(LogTemp, Log, TEXT("Power: %.1f W"), Equipment->GetTotalPowerConsumption());

// Trading
UE_LOG(LogTemp, Log, TEXT("Price: %.1f"), Trading->CalculatePrice("Ore", false));
UE_LOG(LogTemp, Log, TEXT("Stock: %d"), Trading->GetWareStock("Steel"));

// Navigation
UE_LOG(LogTemp, Log, TEXT("Mode: %s"), *UEnum::GetValueAsString(Nav->CurrentTravelMode));
UE_LOG(LogTemp, Log, TEXT("Boost: %.1f%%"), Nav->BoostFuel);

// Crew
UE_LOG(LogTemp, Log, TEXT("Crew: %d/%d"), Crew->GetCrewCount(), Crew->MaxCrew);
UE_LOG(LogTemp, Log, TEXT("Morale: %.1f"), Crew->GetAverageMorale());
```

---

## See Also

- [X4 Systems Implementation Summary](X4_SYSTEMS_IMPLEMENTATION_SUMMARY.md)
- [X4 Systems Design](../../X4_SYSTEMS_DESIGN.md)
- [Project Roadmap](../../ROADMAP.md)
