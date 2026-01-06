# Station Design Research and Implementation Guide

**Project:** SubspaceUE - X4-Style Space Simulation  
**Date:** January 6, 2026  
**Purpose:** Comprehensive research on station designs, modules, and implementation strategy

---

## Executive Summary

This document provides comprehensive research findings on station systems based on:
1. **X4: Foundations** gameplay mechanics (from X4_SYSTEMS_DESIGN.md)
2. **AvorionLike C# Engine** modular station implementation
3. **Current SubspaceUE** project state and requirements

The goal is to implement X4-style modular space stations in Unreal Engine 5.7.

---

## 1. Station Types (From C# Engine)

The C# AvorionLike engine defines 9 core station types:

### Primary Station Types

| Type | Purpose | Key Features |
|------|---------|--------------|
| **TradingPost** | Commerce hub | Buy/sell goods, market prices, faction trading |
| **Shipyard** | Ship construction | Build/repair ships, ship sales, blueprints |
| **Factory** | Manufacturing | Produce components, process materials |
| **MiningStation** | Ore processing | Refine ore, mineral storage, mining support |
| **ResearchStation** | Technology | Research projects, tech upgrades, data analysis |
| **DefensePlatform** | Military | Heavy weapons, shields, sector defense |
| **RefuelingDepot** | Logistics | Refuel ships, recharge energy, emergency repairs |
| **CommandCenter** | Coordination | Fleet command, strategic planning, communications |
| **Habitat** | Civilian | Crew quarters, life support, population centers |

---

## 2. Station Module Categories (10 Types)

Stations are built from modular components across 10 categories:

### 2.1 Hub Modules (Command & Control)

**Purpose:** Central command and core functionality

**Module Types:**
- **Basic Command Hub** - Entry-level control center
  - Power Generation: 100W
  - Crew Capacity: 50
  - Tech Level: 1
  - Size: 10x10x10
  
- **Advanced Command Center** - Enhanced operations
  - Power Generation: 250W
  - Crew Capacity: 100
  - Research Points: 10
  - Tech Level: 3
  - Size: 15x15x15

### 2.2 Docking Modules (Ship Access)

**Purpose:** Ship docking, repairs, and refueling

**Module Types:**
- **Small Docking Bay** - 2 small ship bays
  - Docking Bays: 2
  - Repair Capacity: 50
  - Refuel Capacity: 100
  - Size: 15x8x20
  
- **Large Hangar Bay** - 5 ship capacity
  - Docking Bays: 5
  - Repair Capacity: 150
  - Refuel Capacity: 300
  - Size: 30x15x40

### 2.3 Production Modules (Manufacturing)

**Purpose:** Resource processing and manufacturing

**Module Types:**
- **Basic Factory Module**
  - Production Capacity: 100
  - Storage: 500
  - Crew: 20
  - Size: 12x10x12
  
- **Ore Refinery**
  - Production Capacity: 200
  - Storage: 1000
  - Crew: 30
  - Processes raw ore → refined materials
  - Size: 15x12x15

### 2.4 Storage Modules (Warehousing)

**Purpose:** Cargo storage and inventory management

**Module Types:**
- **Cargo Storage** - Basic warehouse
  - Storage Capacity: 1000
  - Size: 10x8x15
  
- **Advanced Warehouse** - Large-scale storage
  - Storage Capacity: 5000+
  - Specialized storage (temperature control, hazmat)

### 2.5 Defense Modules (Security)

**Purpose:** Station protection and sector security

**Module Types:**
- **Turret Platforms** - Weapon hardpoints
  - Multiple turret types (lasers, cannons, missiles)
  - 360° coverage options
  
- **Shield Generators**
  - Station-wide shield coverage
  - High capacity and recharge rates
  
- **Point Defense Systems**
  - Anti-missile countermeasures
  - Automated threat response

### 2.6 Utility Modules (Infrastructure)

**Purpose:** Power, life support, and systems

**Module Types:**
- **Power Generators** - Energy production
  - Solar, fusion, antimatter reactors
  - Scale with material tier
  
- **Life Support Systems**
  - Atmosphere generation
  - Gravity generation
  - Environmental control
  
- **Sensor Arrays**
  - Long-range scanning
  - Resource detection
  - Threat detection

### 2.7 Habitat Modules (Crew Facilities)

**Purpose:** Living spaces for crew and population

**Module Types:**
- **Crew Quarters** - Residential areas
  - Crew capacity: 20-100 per module
  - Recreation facilities
  - Medical bays
  
- **Civilian Sectors**
  - Population housing
  - Commercial districts
  - Entertainment facilities

### 2.8 Trade Modules (Commerce)

**Purpose:** Trading and market operations

**Module Types:**
- **Trading Hub** - Market interface
  - Buy/sell terminals
  - Price displays
  - Faction restrictions
  
- **Cargo Transfer Systems**
  - Automated loading/unloading
  - Bulk cargo handling

### 2.9 Research Modules (Technology)

**Purpose:** Research and development

**Module Types:**
- **Research Laboratory**
  - Research Points generation
  - Tech tree progression
  - Blueprint analysis
  
- **Data Centers**
  - Information storage
  - Computing resources

### 2.10 Structural Modules (Support)

**Purpose:** Physical structure and connections

**Module Types:**
- **Support Beams** - Structural integrity
- **Connector Modules** - Module links
- **Extension Arms** - Module placement
- **Ring Sections** - Large structures

---

## 3. Station Functional Stats

Each station has aggregated stats from all modules:

```cpp
struct FStationFunctionalStats
{
    // Docking & Services
    int32 DockingBays;           // Number of ships that can dock
    float TradingCapacity;       // Trading volume
    float RepairCapacity;        // Ship repair rate
    float RefuelCapacity;        // Refueling rate
    
    // Production & Storage
    float ProductionCapacity;    // Manufacturing output
    float StorageCapacity;       // Cargo storage
    
    // Power Systems
    float PowerGeneration;       // Energy production
    float PowerConsumption;      // Energy usage
    
    // Defense
    float DefenseRating;         // Combat capability
    float ShieldCapacity;        // Shield strength
    float ShieldRechargeRate;    // Shield regen
    
    // Personnel & Research
    int32 CrewCapacity;          // Maximum crew
    int32 ResearchPoints;        // Research generation
};
```

---

## 4. Material Scaling System

Stations use the same material tier system as ships:

### Material Tiers
1. **Iron** (Basic) - 1.0x multiplier
2. **Titanium** - 1.2x multiplier
3. **Naonite** - 1.5x multiplier
4. **Trinium** - 2.0x multiplier
5. **Xanion** - 2.5x multiplier
6. **Ogonite** - 3.0x multiplier
7. **Avorion** (Advanced) - 4.0x multiplier

### Stat Scaling by Material
```cpp
// Health scales with durability multiplier
ActualHealth = BaseHealth * MaterialDurability

// Production scales with energy efficiency
ProductionRate = BaseProduction * MaterialEfficiency

// Defense scales with durability
DefenseRating = BaseDefense * MaterialDurability

// Shields scale with shield multiplier
ShieldStrength = BaseShield * MaterialShieldMultiplier
```

---

## 5. Station Construction System

### 5.1 Modular Assembly

**Core Module Requirement:**
- Every station must have at least one Hub/Command module
- This serves as the "core" - if destroyed, station is lost
- All other modules attach to the core or to each other

### 5.2 Attachment System

**Attachment Points:**
- Each module has defined attachment points (6-sided cube typically)
- Modules snap to attachment points
- Attachment validation ensures structural integrity
- Connection types: Hub, Docking, Production, etc.

**Example Attachment Point Structure:**
```cpp
USTRUCT(BlueprintType)
struct FAttachmentPoint
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;              // "front", "back", "top", etc.
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Position;          // Relative to module center
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator Rotation;         // Attachment orientation
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAttachmentType Type;      // What can attach here
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bOccupied;           // Is something attached?
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGuid AttachedModuleId;   // What's attached (if any)
};
```

### 5.3 Build Process

1. **Select Station Type** - Choose primary function
2. **Place Core Module** - Start with command hub
3. **Add Functional Modules** - Based on station purpose
4. **Add Support Modules** - Power, life support, etc.
5. **Add Defense Modules** - Protect the investment
6. **Add Habitat Modules** - House the crew
7. **Validate Structure** - Check connectivity and requirements
8. **Finalize Build** - Calculate stats and spawn

---

## 6. X4 Comparison: Station Management Features

From X4_SYSTEMS_DESIGN.md, key features to implement:

### 6.1 Station Management Interface
- Production management (what to produce, how much)
- Trade orders (buy/sell orders, price limits)
- Faction restrictions (who can dock/trade)
- Personnel management (managers, workers)
- Logistics (assign ships for mining/trading)
- Defense configuration (rules of engagement)

### 6.2 Personnel System
- **Station Manager** - NPC that runs the station
  - Management skill affects efficiency
  - Can be hired/fired/replaced
  - Earns salary
  
- **Workforce** - Service crew
  - Number affects production/repair capacity
  - Requires habitat modules
  - Costs in salaries

### 6.3 Automated Operations
- Auto-buy resources when low
- Auto-sell products when full
- Auto-defend against threats
- Auto-repair docked ships
- Auto-refuel docked ships

---

## 7. Implementation Strategy for SubspaceUE

### Phase 1: Core Station System (Week 8-9 per ROADMAP.md)

**Objective:** Basic station functionality

**Tasks:**
1. Create `UModularStationComponent` (C++)
   - Port from C# `ModularStationComponent`
   - Module list management
   - Stats aggregation
   - Health tracking

2. Create `ASpaceStation` actor (C++)
   - Base station actor class
   - Inherits from `AActor`
   - Has `UModularStationComponent`
   - Has `UStaticMeshComponent` for visual

3. Create `FStationModuleDefinition` struct (C++)
   - Port from C# `StationModuleDefinition`
   - Module templates/blueprints
   - Stats, size, attachment points

4. Create `UStationModuleLibrary` (C++)
   - Registry of all module definitions
   - Load from Data Assets
   - 15+ built-in module types

5. Implement attachment system
   - `FAttachmentPoint` struct
   - Validation logic
   - Snap-to-point placement

### Phase 2: Station Builder UI (Week 9)

**Objective:** In-game station construction interface

**Tasks:**
1. Create `UStationBuilderWidget` (UMG)
   - Module selection palette
   - 3D preview window
   - Stats display
   - Cost calculator

2. Implement placement system
   - Mouse-based module placement
   - Rotation controls
   - Attachment validation feedback
   - Undo/redo support

3. Build confirmation
   - Resource requirements
   - Build time calculation
   - Construction queue

### Phase 3: Station Operations (Week 10)

**Objective:** Functional station gameplay

**Tasks:**
1. Create `UStationManagementWidget` (UMG)
   - Production controls
   - Trading interface
   - Personnel management
   - Defense configuration

2. Implement docking system
   - `UDockingBayComponent`
   - Ship approach and landing
   - Docking queue management
   - Undocking procedures

3. Implement station services
   - Ship repair system
   - Refueling system
   - Trading system integration
   - Storage/inventory management

### Phase 4: Advanced Features (Week 11)

**Objective:** AI, automation, and polish

**Tasks:**
1. Station AI management
   - Automated production
   - Automated trading
   - Automated defense

2. NPC station managers
   - Hire/fire mechanics
   - Skill-based efficiency
   - Salary system

3. Visual enhancements
   - Module-specific meshes
   - Docking lights and effects
   - Damage visual feedback
   - Shield visual effects

---

## 8. Station Module Definitions Reference

### Complete Module List (26 Types)

#### Hub Modules (2)
1. Basic Command Hub - Small control center
2. Advanced Command Center - Large operations hub

#### Docking Modules (3)
3. Small Docking Bay - 2 ships
4. Large Hangar Bay - 5 ships
5. Capital Ship Dock - 1 capital ship

#### Production Modules (4)
6. Basic Factory - General manufacturing
7. Ore Refinery - Ore processing
8. Advanced Factory - High-tech production
9. Component Assembly - Ship parts

#### Storage Modules (2)
10. Cargo Storage - Basic warehouse
11. Specialized Storage - Temperature/hazmat control

#### Defense Modules (3)
12. Turret Platform - Weapon hardpoints
13. Shield Generator - Station shields
14. Point Defense - Anti-missile

#### Utility Modules (3)
15. Power Generator - Energy production
16. Life Support - Atmosphere/gravity
17. Sensor Array - Scanning/detection

#### Habitat Modules (2)
18. Crew Quarters - Residential
19. Civilian Sector - Population housing

#### Trade Modules (2)
20. Trading Hub - Market interface
21. Cargo Transfer - Loading/unloading automation

#### Research Modules (2)
22. Research Laboratory - Tech development
23. Data Center - Information processing

#### Structural Modules (3)
24. Support Beam - Structure
25. Connector Module - Links
26. Extension Arm - Reach/placement

---

## 9. Integration with Existing Systems

### 9.1 Integration with Ship Interior System

**Current `UShipInteriorComponent`:**
- Already has 10 room types (Cockpit, Crew Quarters, Cargo Bay, etc.)
- Has interior object system (terminals, chairs, storage, etc.)
- Can be extended for station interiors

**Station Interior Expansion:**
- Reuse same component for station rooms
- Add station-specific room types:
  - Control Room
  - Market Floor
  - Factory Floor
  - Warehouse
  - Research Lab
  - Docking Control Tower

### 9.2 Integration with Equipment System

**Current `UShipEquipmentComponent`:**
- Equipment slots system exists
- Can be adapted for station modules

**Station Equipment:**
- Turret slots → Defense modules
- Shield generators → Station shields
- Utility slots → Special modules (sensors, mining)

### 9.3 Integration with Trading System

**Needs:**
- Station trading terminal interface
- Buy/sell order management
- Dynamic pricing based on supply/demand
- Faction-based access control

---

## 10. Visual Design Guidelines

### 10.1 Station Aesthetics

**From Reference Images (1233.PNG, 1234.PNG):**
- Industrial, utilitarian look
- Modular, clearly segmented sections
- Visible structural elements
- Hazard markings on dangerous areas
- Glowing windows and lights
- Rotating sections (optional)

**Color Schemes by Faction:**
- **Military** - Dark gray, red accents
- **Industrial** - Olive-green, brown, hazard stripes
- **Civilian** - Light gray, white, blue accents
- **Research** - White, cyan, high-tech look
- **Pirate** - Black, rust, warning colors

### 10.2 Module Visual Variations

Each module category should have distinct appearance:
- **Hub** - Central sphere or cylinder, command tower
- **Docking** - Open hangars, docking arms, lights
- **Production** - Industrial machinery, pipes, smokestacks
- **Storage** - Large containers, silos, boxes
- **Defense** - Weapon turrets, armored plating, shields
- **Utility** - Antennas, solar panels, generators
- **Habitat** - Windows, life support vents
- **Trade** - Market signs, cargo cranes
- **Research** - Labs, data centers, clean rooms
- **Structural** - Beams, trusses, connectors

---

## 11. Next Steps for Implementation

### Immediate Actions (This Week)

1. **Create Documentation** ✅ (This document)
2. **Design UE5 C++ Classes**
   - Plan class hierarchy
   - Define interfaces
   - Plan data structures

3. **Create Data Assets**
   - Station module definitions
   - Material properties
   - Default configurations

### Week 8-9 Implementation

1. Implement core station component
2. Create station actor base class
3. Build module library system
4. Implement attachment system
5. Create basic station builder UI

### Week 10-11 Implementation

1. Implement docking system
2. Build station management UI
3. Integrate with trading system
4. Add NPC station managers
5. Implement automated operations

---

## 12. Testing & Validation

### Test Scenarios

1. **Basic Construction**
   - Place command hub
   - Add modules in each category
   - Verify attachment validation
   - Check stat aggregation

2. **Docking Operations**
   - Ship approaches station
   - Requests docking clearance
   - Docks successfully
   - Receives services (repair/refuel)
   - Undocks and departs

3. **Production & Trading**
   - Station produces goods
   - Sets buy/sell orders
   - Player trades with station
   - Prices update dynamically

4. **Defense Systems**
   - Station detects threat
   - Turrets engage hostiles
   - Shields absorb damage
   - Station survives or is destroyed

5. **Module Destruction**
   - Individual modules take damage
   - Modules are destroyed
   - Stats update accordingly
   - Core destruction = total loss

---

## Summary

This research document provides comprehensive foundation for implementing X4-style modular space stations in SubspaceUE. Key takeaways:

1. **9 Station Types** with distinct purposes
2. **10 Module Categories** with 26+ individual modules
3. **Material Tier System** for progression
4. **Modular Construction** with attachment validation
5. **Station Management** with AI and automation
6. **Visual Design** guidelines for aesthetics
7. **4-Phase Implementation** aligned with ROADMAP.md

The C# AvorionLike engine provides excellent reference implementation that can be ported to UE5 C++ with enhancements for Unreal's rendering and Blueprint systems.

---

**Document Status:** ✅ Complete  
**Last Updated:** January 6, 2026  
**Next Document:** NPC_CREW_DESIGN_RESEARCH.md
