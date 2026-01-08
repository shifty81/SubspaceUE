# X4: Foundations Systems Design for SubspaceUE

**Project:** SubspaceUE - X4-Inspired Space Simulation  
**Date:** January 6, 2026  
**Purpose:** Complete systems design based on X4: Foundations research

---

## Executive Summary

This document outlines the comprehensive system design for SubspaceUE based on extensive research of X4: Foundations. The goal is to implement X4-style space simulation mechanics including ship management, trading, mining, combat, station building, crew management, and navigation - NOT the Avorion voxel-based block building system.

**Key Differentiation:**
- ✅ X4-Style: Pre-built ships with modular equipment/weapons
- ❌ NOT Avorion-Style: Voxel block-by-block ship construction

---

## 1. Core HUD & UI Systems

### 1.1 Main HUD Elements

**Ship Status Display:**
```cpp
struct FShipStatus
{
    // Core Stats
    float Hull;              // 0-100% structural integrity
    float MaxHull;
    float Shield;            // 0-100% shield strength  
    float MaxShield;
    
    // Movement
    float CurrentSpeed;      // m/s
    float MaxSpeed;
    FVector Velocity;        // 3D velocity vector
    
    // Weapons
    float WeaponHeat;        // 0-100% weapon heat
    int32 MissileCount;      // Remaining missiles
    int32 FlareCount;        // Remaining countermeasures
    
    // Systems
    float Energy;            // Ship energy/power
    float MaxEnergy;
};
```

**Target Information:**
```cpp
struct FTargetInfo
{
    FString TargetName;
    AActor* TargetActor;
    float Distance;          // meters
    float TargetSpeed;
    float TargetHull;
    float TargetShield;
    FVector RelativeVelocity;
    bool bIsHostile;
    bool bIsStation;
};
```

**Mode Indicators:**
- Auto Roll (Shift+R)
- Flight Assist (Ctrl+Space)
- Aim Assist (Ctrl+A)
- Auto Pilot (Shift+A)
- Mouse Steering (Shift+Space)
- Collision Avoidance
- Travel Mode / Combat Mode

### 1.2 Map System

**Universe Structure:**
```cpp
// Hierarchy: Galaxy → Systems → Sectors → Zones

class UGalaxyMap
{
    TArray<FStarSystem> Systems;          // 60+ star systems
    TMap<FString, FSector> DiscoveredSectors;
    TArray<FJumpGate> JumpGates;
    TArray<FHighway> Highways;
    TArray<FStation> AllStations;
};

struct FSector
{
    FString SectorName;
    FVector Position;
    TArray<FZone> Zones;                  // Resource zones, stations
    TArray<AActor*> Ships;
    TArray<AActor*> Stations;
    EFaction OwningFaction;
    float SecurityRating;
};
```

**Map Features:**
- Filter/sort by asset type (stations, ships, resources)
- Route planning with auto-pilot
- Trade route visualization
- Mission objective markers
- Fleet command interface
- Real-time sector status

---

## 2. Ship Systems & Equipment

### 2.1 Ship Classes

```cpp
UENUM(BlueprintType)
enum class EShipClass : uint8
{
    S_Fighter,           // Small: Nimble fighters, scouts
    S_Interceptor,       // Small: Fast combat
    M_Corvette,         // Medium: Multi-role combat
    M_Freighter,        // Medium: Cargo transport
    M_Miner,            // Medium: Resource gathering
    L_Destroyer,        // Large: Heavy combat
    L_Transporter,      // Large: Bulk cargo
    XL_Carrier,         // Extra Large: Fleet support
    XL_Capital          // Extra Large: Command ships
};
```

### 2.2 Ship Equipment Slots

```cpp
struct FShipEquipment
{
    // Engines
    TArray<FEngineSlot> Engines;         // Combat/Travel drives
    
    // Weapons
    TArray<FWeaponSlot> ForwardWeapons;  // Fixed forward guns
    TArray<FTurretSlot> Turrets;         // 360° turrets
    TArray<FLauncherSlot> MissileLaunchers;
    
    // Defensive Systems
    TArray<FShieldSlot> ShieldGenerators;
    int32 FlareCount;
    int32 CountermeasureCapacity;
    
    // Utility
    FDockingComputer DockingComputer;
    FLongRangeScan Scanner;
    FCargoHold CargoHold;
    FSoftware InstalledSoftware;         // Trade software, etc.
};
```

### 2.3 Engine Types

```cpp
struct FEngine
{
    EEngineType Type;
    float TravelSpeed;      // Max speed in travel mode
    float CombatSpeed;      // Max speed in combat
    float Acceleration;
    float TurnRate;
    bool bInstantTravel;    // Combat engines
    float ChargeTime;       // Travel engines (charge required)
};

enum class EEngineType
{
    Combat,                 // Instant, lower max speed
    Travel,                 // Charge-up, higher max speed
    All_Round              // Balanced
};
```

---

## 3. Combat System

### 3.1 Weapon Types

```cpp
enum class EWeaponType
{
    // Energy Weapons
    Laser,                  // Continuous beam
    Plasma,                 // High damage projectiles
    Pulse,                  // Rapid fire energy
    
    // Ballistic
    MassDriver,            // Physical projectiles
    Railgun,               // High velocity kinetic
    
    // Missiles
    Dumbfire,              // Unguided rockets
    Guided,                // Lock-on missiles
    Torpedo,               // Heavy anti-capital
    Mine                   // Defensive/trap
};

struct FWeapon
{
    EWeaponType Type;
    float Damage;
    float Range;
    float RateOfFire;
    float HeatGeneration;
    float ProjectileSpeed;
    int32 AmmoCapacity;
    int32 CurrentAmmo;
    
    // Targeting
    float TrackingSpeed;    // For turrets
    float ArcAngle;         // Firing arc
    bool bRequiresLockOn;
};
```

### 3.2 Combat Tactics

```cpp
enum class ECombatTactic
{
    Aggressive,            // Frontal assault
    Kiting,                // Maintain distance while attacking
    Strafing,              // Circle target
    Broadsiding,           // Maximize turret coverage
    Defensive,             // Evade and retreat
    Formation              // Fleet coordination
};
```

### 3.3 Damage System

```cpp
struct FDamageData
{
    float HullDamage;
    float ShieldDamage;
    bool bCanTargetSurface;       // Can target specific modules
    
    // Surface targeting
    bool bTargetEngines;
    bool bTargetWeapons;
    bool bTargetShields;
};

// Ship has destructible surface elements
struct FSurfaceElement
{
    EElementType Type;      // Engine, Turret, Shield, etc.
    float Health;
    FVector Location;
    bool bDestroyed;
};
```

---

## 4. Trading & Economy System

### 4.1 Ware System

```cpp
struct FWare
{
    FString WareName;
    EWareCategory Category;
    float BasePrice;
    float Volume;           // Cargo space required
    
    // Production
    TArray<FWare> InputWares;      // Required to produce
    float ProductionTime;
};

enum class EWareCategory
{
    RawMaterials,          // Ore, Silicon, Ice, Gas
    RefinedMaterials,      // Metals, Crystals
    Components,            // Microchips, Hull Parts
    FoodDrink,            // Consumables
    Medical,              // Medical supplies
    Technology,           // Advanced tech
    Weapons,              // Ship weapons
    Ships                 // Completed ships
};
```

### 4.2 Trading Mechanics

```cpp
class UTradingSystem
{
    // Dynamic pricing based on supply/demand
    float CalculatePrice(FWare Ware, AActor* Station);
    
    // Automated trading
    void SetupAutoTrade(AActor* Ship, bool bEnabled);
    
    // Trade routes
    void CreateTradeRoute(AActor* Ship, 
                         TArray<FTradeStop> Stops);
    
    // Market analysis
    TArray<FTradeDeal> FindProfitableDeals(
        FVector CurrentLocation, 
        float MaxJumpDistance
    );
};

struct FTradeDeal
{
    AActor* BuyStation;
    AActor* SellStation;
    FWare Ware;
    float ProfitPerUnit;
    float TotalProfit;
    int32 Volume;
};
```

---

## 5. Mining System

### 5.1 Resource Types

```cpp
enum class EResourceType
{
    // Solid (from asteroids)
    Ore,
    Silicon,
    Nividium,
    Ice,
    
    // Liquid (from nebulae)
    Hydrogen,
    Helium,
    Methane,
    
    // Special
    Crystals,
    RareEarth
};

struct FResourceZone
{
    FVector Location;
    float Radius;
    EResourceType ResourceType;
    float Yield;            // 1-10 scale
    float RemainingAmount;
};
```

### 5.2 Mining Mechanics

```cpp
class UMiningSystem
{
    // Manual mining
    void TargetAsteroid(AActor* Asteroid);
    void FireMiningLaser();
    void CollectFragments();
    
    // Automated mining
    void SetupAutoMine(AActor* Ship, bool bEnabled);
    void AssignMiningZone(AActor* Ship, FResourceZone Zone);
    
    // Mining equipment
    TArray<FMiningLaser> GetMiningLasers();
    TArray<FMiningDrone> GetMiningDrones();
};
```

---

## 6. Station Management

### 6.1 Station Construction

```cpp
class ASpaceStation : public AActor
{
    // Modules
    TArray<FStationModule> Modules;
    
    // Core modules
    FDockingModule Dock;
    FStorageModule Storage;
    
    // Production modules
    TArray<FProductionModule> ProductionModules;
    
    // Defense
    TArray<FTurretModule> Turrets;
    TArray<FShieldModule> Shields;
};

struct FStationModule
{
    EModuleType Type;
    FVector Position;
    FRotator Rotation;
    float BuildProgress;    // 0-100%
    bool bOperational;
    
    // Construction
    TMap<FWare, int32> RequiredWares;
    TMap<FWare, int32> DeliveredWares;
};
```

### 6.2 Station Management

```cpp
class UStationManager
{
    // Personnel
    AActor* Manager;                    // Station manager
    TArray<AActor*> WorkForce;         // Service crew
    
    // Production
    void SetProduction(FWare Ware, int32 Amount);
    void AutomateProduction(bool bEnabled);
    
    // Trading
    void SetBuyOrders(TMap<FWare, FTradeOrder> Orders);
    void SetSellOrders(TMap<FWare, FTradeOrder> Orders);
    void RestrictFaction(EFaction Faction, bool bRestrict);
    
    // Logistics
    void AssignMiningShip(AActor* Ship);
    void AssignTrader(AActor* Ship);
    
    // Defense
    void SetDefenseMode(EDefenseMode Mode);
};
```

### 6.3 Station Types

```cpp
enum class EStationType
{
    TradingStation,        // Buy/sell hub
    ProductionFactory,     // Manufactures wares
    SolarPowerPlant,      // Energy production
    MiningStation,        // Ore processing
    Shipyard,             // Ship construction/repair
    Wharf,                // Ship sales
    DefenseStation,       // Military outpost
    ResearchStation       // Technology development
};
```

---

## 7. Crew & Personnel System

### 7.1 Crew Types

```cpp
enum class ECrewRole
{
    Captain,              // Ship commander
    Pilot,                // For smaller ships
    ServiceCrew,          // Engineering/operations
    Marine,               // Boarding/defense
    Manager               // Station management
};

struct FCrewMember
{
    FString Name;
    ECrewRole Role;
    
    // Skills (0-5 stars)
    int32 PilotingSkill;
    int32 BoardingSkill;
    int32 ManagementSkill;
    int32 EngineeringSkill;
    int32 MoraleSkill;
    
    // Status
    AActor* AssignedShip;
    bool bIsBusy;
};
```

### 7.2 Crew Management

```cpp
class UCrewSystem
{
    // Hiring
    void HireCrewMember(FCrewMember Crew, int32 Cost);
    TArray<FCrewMember> GetAvailableCrewAtStation(AActor* Station);
    
    // Assignment
    void AssignToShip(FCrewMember Crew, AActor* Ship);
    void PromoteToRole(FCrewMember Crew, ECrewRole NewRole);
    void TransferBetweenShips(FCrewMember Crew, 
                             AActor* FromShip, 
                             AActor* ToShip);
    
    // Training
    void TrainCrew(FCrewMember Crew, ESeminarType Type);
    void AutoLevelSkills(FCrewMember Crew);
};
```

---

## 8. Navigation & Travel System

### 8.1 Travel Modes

```cpp
enum class ETravelMode
{
    StandardFlight,       // Normal maneuvering
    Boost,                // Shield drain for speed burst
    TravelDrive,          // High-speed sector crossing
    Autopilot,           // Automated navigation
    Highway              // Highway entry/exit
};

struct FTravelState
{
    ETravelMode CurrentMode;
    bool bAutoRollEnabled;
    bool bFlightAssistEnabled;
    bool bAimAssistEnabled;
    bool bCollisionAvoidanceEnabled;
    bool bMouseSteeringEnabled;
};
```

### 8.2 Jump Gates

```cpp
struct FJumpGate
{
    FString GateName;
    FVector Location;
    FSector ConnectedSector;
    bool bIsLocked;          // Requires mission/DLC
    EFaction ControllingFaction;
};

class UJumpGateSystem
{
    void ActivateJumpGate(AActor* Ship, FJumpGate Gate);
    bool CanUseGate(AActor* Ship, FJumpGate Gate);
    void JumpToSector(AActor* Ship, FSector Destination);
};
```

### 8.3 Highway System

```cpp
enum class EHighwayType
{
    LocalHighway,         // Intra-sector (S/M ships only)
    Superhighway,        // Inter-sector ring
    Accelerator          // Instant sector jump
};

struct FHighway
{
    EHighwayType Type;
    TArray<FVector> PathPoints;
    float Speed;             // Up to 14 km/s
    bool bIsBidirectional;
    TArray<FHighwayExit> Exits;
};

class UHighwaySystem
{
    void EnterHighway(AActor* Ship, FHighway Highway);
    void ExitHighway(AActor* Ship, FHighwayExit Exit);
    bool CanShipUseHighway(AActor* Ship, FHighway Highway);
};
```

---

## 9. Fleet Management

### 9.1 Fleet Structure

```cpp
class UFleetManager
{
    TArray<FFl eetSquad> Squads;
    AActor* FlagshipShip;
    
    // Commands
    void IssueAttackOrder(AActor* Target);
    void IssueDefendOrder(AActor* Asset);
    void IssueMoveOrder(FVector Destination);
    void IssueFormationOrder(EFormationType Formation);
    
    // Automation
    void SetupEscortDuty(AActor* ProtectedShip);
    void SetupPatrolRoute(TArray<FVector> Waypoints);
    void SetupInterceptDuty(FSector Sector);
};

enum class EFormationType
{
    Line,
    Wedge,
    Box,
    Sphere,
    Custom
};
```

---

## 10. Mission & Quest System

### 10.1 Mission Types

```cpp
enum class EMissionType
{
    // Story
    MainPlot,
    FactionQuest,
    
    // Contracts
    Transport,           // Deliver wares
    Patrol,             // Sector patrol
    Destroy,            // Kill target
    Scan,               // Data collection
    Rescue,             // Save ship/crew
    Build,              // Construct station
    
    // Guild
    TradingGuild,
    FightersGuild,
    MinersGuild,
    
    // Dynamic
    DistressCall,
    PirateAttack,
    StationDefense
};

struct FMission
{
    FString MissionName;
    FText Description;
    EMissionType Type;
    EFaction GivingFaction;
    
    // Objectives
    TArray<FObjective> Objectives;
    
    // Rewards
    int32 CreditReward;
    int32 ReputationGain;
    TArray<FWare> ItemRewards;
    
    // Status
    bool bIsActive;
    float TimeRemaining;
};
```

---

## 11. Faction & Diplomacy System

### 11.1 Faction System

```cpp
enum class EFaction
{
    Argon,              // Main human faction
    Teladi,             // Traders/merchants
    Paranid,            // Religious warriors
    Split,              // Aggressive hunters
    Boron,              // Peaceful aquatics
    Xenon,              // Hostile AI
    Khaak,              // Ancient aliens
    Pirates,            // Outlaws
    Player              // Player faction
};

struct FFactionRelation
{
    EFaction Faction;
    float Reputation;      // -100 to +100
    EDiplomaticStatus Status;
};

enum class EDiplomaticStatus
{
    War,
    Hostile,
    Neutral,
    Friendly,
    Allied
};
```

---

## 12. Research & Technology

### 12.1 Research System

```cpp
struct FResearchProject
{
    FString ProjectName;
    ETechnologyType Type;
    TArray<FWare> RequiredWares;
    float ResearchTime;
    float Progress;
};

enum class ETechnologyType
{
    Teleportation,      // Remote ship control
    AdvancedScanners,   // Better detection
    ImprovedEngines,    // Speed boost
    WeaponTech,        // Better weapons
    ShieldTech,        // Better shields
    HackingTools,      // Steal blueprints
    AdvancedAI         // Better automation
};
```

---

## 13. UI Widget Classes to Implement

### Priority 1 (Core HUD)
```cpp
class UX4HUDWidget : public UUserWidget
{
    // Ship status
    void UpdateShipStatus(FShipStatus Status);
    void UpdateTargetInfo(FTargetInfo Target);
    
    // Mode indicators
    void SetTravelMode(ETravelMode Mode);
    void SetFlightAssist(bool bEnabled);
    void SetAutoRoll(bool bEnabled);
    
    // Warnings
    void ShowLowShieldWarning();
    void ShowLowHullWarning();
    void ShowMissileWarning();
};

class UGalaxyMapWidget : public UUserWidget
{
    // Map display
    void ShowGalaxyMap();
    void FilterByType(EAssetType Type);
    void PlotRoute(FSector From, FSector To);
    
    // Fleet commands
    void IssueFleetOrder(EFleetOrder Order);
};

class UStationManagementWidget : public UUserWidget
{
    void ShowStationOverview(AActor* Station);
    void ManageProduction();
    void ManageTrade();
    void ManageDefense();
    void ManagePersonnel();
};
```

### Priority 2 (Secondary UI)
```cpp
class UTradingWidget : public UUserWidget;
class UShipUpgradeWidget : public UUserWidget;
class UCrewManagementWidget : public UUserWidget;
class UMissionLogWidget : public UUserWidget;
class UEncyclopediaWidget : public UUserWidget;
```

---

## 14. Input Actions (X4-Style)

```cpp
// Flight Controls
InputAction_MoveForward     // W/S
InputAction_MoveStrafe      // A/D
InputAction_MoveVertical    // Space/Shift
InputAction_MouseLook       // Mouse XY
InputAction_Pitch           // Up/Down arrows
InputAction_Yaw             // Left/Right arrows
InputAction_Roll            // Q/E

// Ship Functions
InputAction_Boost           // Tab
InputAction_TravelMode      // Shift+1
InputAction_Brake           // X/Z/Backspace
InputAction_AutoPilot       // Shift+A
InputAction_AutoRoll        // Shift+R
InputAction_FlightAssist    // Ctrl+Space
InputAction_AimAssist       // Ctrl+A

// Weapons
InputAction_FirePrimary     // Left Mouse
InputAction_FireSecondary   // Right Mouse
InputAction_FireMissile     // Middle Mouse
InputAction_NextWeapon      // G
InputAction_CycleTarget     // T

// UI Toggles
InputAction_OpenMap         // M
InputAction_OpenComms       // Comma
InputAction_OpenMissions    // Period
InputAction_OpenInfo        // I
InputAction_OpenTrade       // K
InputAction_Scan            // Shift+2 / Shift+3
```

---

## 15. Implementation Phases

### Phase 1: Core Navigation & HUD (Week 3)
- [x] Basic ship movement (already done)
- [ ] X4-style HUD widget
- [ ] Travel mode system
- [ ] Target lock system
- [ ] Autopilot basic navigation

### Phase 2: Combat & Weapons (Week 4-5)
- [ ] Weapon system (lasers, missiles, turrets)
- [ ] Shield system
- [ ] Damage calculation
- [ ] AI combat behaviors
- [ ] Surface element targeting

### Phase 3: Trading & Economy (Week 6-7)
- [ ] Ware system
- [ ] Dynamic economy
- [ ] Trading UI
- [ ] Auto-trade functionality
- [ ] Station trading docks

### Phase 4: Station System (Week 8-9)
- [ ] Station construction
- [ ] Module placement
- [ ] Production systems
- [ ] Station management UI
- [ ] Automation

### Phase 5: Fleet & Crew (Week 10-11)
- [ ] Crew hiring system
- [ ] Crew management UI
- [ ] Fleet command interface
- [ ] Squadron behaviors
- [ ] Boarding mechanics

### Phase 6: Universe & Navigation (Week 12-13)
- [ ] Galaxy map
- [ ] Jump gate system
- [ ] Highway system
- [ ] Sector generation
- [ ] Long-range scanning

### Phase 7: Missions & Progression (Week 14-15)
- [ ] Mission system
- [ ] Faction relations
- [ ] Research system
- [ ] Quest chains

### Phase 8: Polish & Optimization (Week 16)
- [ ] UI polish
- [ ] Performance optimization
- [ ] Balance testing
- [ ] Bug fixing

---

## 16. Key Differences from Current Implementation

### What to Remove:
- ❌ Voxel block system (VoxelBlock.h/cpp)
- ❌ Block-by-block ship construction
- ❌ Block types (Hull, Armor as building blocks)
- ❌ Material tiers for blocks (Iron → Avorion)
- ❌ Avorion-style building system

### What to Keep:
- ✅ Basic ship movement/physics (already X4-style FPS controls)
- ✅ HUD widget framework (repurpose for X4 style)
- ✅ Enhanced Input system
- ✅ Player controller structure

### What to Add:
- ✅ Pre-built ship models with equipment slots
- ✅ Trading and economy system
- ✅ Station management
- ✅ Crew system
- ✅ Fleet management
- ✅ Navigation (gates, highways)
- ✅ Mission system
- ✅ Faction diplomacy

---

## Summary

This design document provides a complete roadmap for implementing X4: Foundations-style gameplay in SubspaceUE. The focus is on:

1. **Ship Management** - Pre-built ships with upgradeable equipment, not voxel construction
2. **Economic Simulation** - Dynamic trading, mining, and production chains
3. **Empire Building** - Station construction and fleet management
4. **Space Navigation** - Jump gates, highways, and galaxy exploration
5. **Personnel Management** - Hiring and managing crews for ships and stations

The voxel/block building system should be removed or repurposed for other uses (perhaps asteroid mining visuals), as X4 uses pre-manufactured ships with equipment slots rather than block-by-block construction.

**Next Steps:**
1. Remove/archive voxel system files
2. Implement X4-style ship equipment system
3. Create trading and economy foundation
4. Build station management framework
5. Implement galaxy map and navigation
