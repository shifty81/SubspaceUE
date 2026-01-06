# SubspaceUE Project Roadmap

**Last Updated:** January 6, 2026  
**Status:** Week 1 Complete, Week 2 In Progress  
**Overall Progress:** ~15% Complete

Visual roadmap for the Unreal Engine 5.7 conversion of Codename:Subspace custom C# engine.

> **📋 See [UE5_MIGRATION_CHECKLIST.md](docs/migration/UE5_MIGRATION_CHECKLIST.md) for detailed system-by-system migration tracking.**

## Overview

This project involves migrating a **fully functional C# space game engine** (AvorionLike) with 30+ implemented systems to Unreal Engine 5.7. The C# engine is feature-complete with ECS, voxel building, modular ships, AI, combat, procedural generation, multiplayer, and more.

**Migration Scope:** 43 major systems across 9 categories
- ✅ **4 systems complete** (Core framework)
- 🔨 **3 systems in progress** (Physics, Voxel, Input)
- 🔴 **36 systems not started** (85% remaining)

```
┌─────────────────────────────────────────────────────────────────────────┐
│                    CODENAME: SUBSPACE - UE5.7 ROADMAP                   │
│              C# Custom Engine to Unreal Engine Conversion                │
│                                                                           │
│  Source: AvorionLike C# Engine (30+ systems, fully playable)            │
│  Target: Unreal Engine 5.7 with C++ and Blueprints                      │
└─────────────────────────────────────────────────────────────────────────┘

PHASE 1: FOUNDATION (Weeks 1-2) ✅ 50% COMPLETE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
│
├─ Week 1: Project Setup & Documentation ✅ COMPLETE
│  ├─ ✅ Create UE5.7 project structure (SubspaceUE.uproject)
│  ├─ ✅ Configure build system (Build.cs, Target files)
│  ├─ ✅ Implement core game classes (GameMode, PlayerController, Pawn)
│  ├─ ✅ Set up Config files (Input, Engine, Game)
│  ├─ ✅ Create comprehensive documentation
│  ├─ ✅ Organize documentation into structured docs/ folder
│  └─ ✅ Create migration checklist (43 systems mapped)
│
├─ Week 2: Core Systems & Voxel Foundation 🔨 IN PROGRESS
│  ├─ 🔨 Implement UVoxelComponent (C# → UE5)
│  ├─ 🔨 Port greedy meshing algorithm from C#
│  ├─ 🔨 Create procedural mesh generation
│  ├─ 🔨 Build basic HUD widgets (UMG)
│  ├─ 🔨 Set up Enhanced Input System
│  ├─ 🔨 Implement voxel material system
│  └─ 🔨 Create test level with voxel objects
│
└─ Deliverable: Project compiles, voxel rendering works, basic ship movement functional


PHASE 2: WORLD GENERATION & MODULAR SHIPS (Weeks 3-4)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
│
├─ Week 3: Procedural World Generation
│  ├─ 🔴 Implement UGalaxyGeneratorSubsystem (port from C#)
│  ├─ 🔴 Create sector generation with tech zones (Iron → Avorion)
│  ├─ 🔴 Implement AAsteroidActor with voxel component
│  ├─ 🔴 Add procedural asteroid field spawning
│  ├─ 🔴 Create ASpaceStation base class
│  ├─ 🔴 Implement resource distribution system
│  └─ 🔴 Build test level with generated sectors
│
├─ Week 4: Modular Ship System (Critical)
│  ├─ 🔴 Port UModularShipComponent from C# (17 module types)
│  ├─ 🔴 Implement ship module library (Data Assets)
│  ├─ 🔴 Create attachment point system with validation
│  ├─ 🔴 Build procedural ship generator
│  ├─ 🔴 Integrate voxel damage overlay system
│  ├─ 🔴 Implement material scaling (Iron → Avorion stats)
│  └─ 🔴 Create ship blueprint save/load system
│
└─ Deliverable: PROTOTYPE - Flyable modular ship in procedurally generated universe


PHASE 3: AI & COMBAT SYSTEMS (Weeks 5-6)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
│
├─ Week 5: AI Framework
│  ├─ 🔴 Create ASubspaceAIController base class
│  ├─ 🔴 Implement Behavior Trees for AI states
│  │  └─ States: Idle, Patrol, Combat, Mining, Trading, Fleeing, ReturningToBase
│  ├─ 🔴 Build AI perception system (from C# AIPerceptionSystem)
│  ├─ 🔴 Create AI decision-making system (from C# AIDecisionSystem)
│  ├─ 🔴 Implement AI personalities (Aggressive, Defensive, Miner, Trader)
│  ├─ 🔴 Add combat tactics (Aggressive, Kiting, Strafing, Broadsiding, Defensive)
│  └─ 🔴 Create AI ship variants (Fighter, Miner, Trader, Capital)
│
├─ Week 6: Combat System
│  ├─ 🔴 Implement weapon components (from C# Combat system)
│  │  └─ Types: Lasers, Cannons, Missiles, Railguns, Plasma, Torpedoes
│  ├─ 🔴 Create projectile system with physics
│  ├─ 🔴 Build shield mechanics and visuals
│  ├─ 🔴 Implement voxel damage and destruction
│  ├─ 🔴 Add target lock system
│  ├─ 🔴 Create turret aiming and rotation
│  └─ 🔴 Implement weapon factory for procedural generation
│
└─ Deliverable: AI ships that patrol, mine, trade, and engage in combat


PHASE 4: GAMEPLAY SYSTEMS (Weeks 7-8)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
│
├─ Week 7: Core Mechanics
│  ├─ 🔴 Implement UInventoryComponent (from C# Resources system)
│  ├─ 🔴 Create resource management (7 material types)
│  │  └─ Iron, Titanium, Naonite, Trinium, Xanion, Ogonite, Avorion
│  ├─ 🔴 Build trading system (from C# Economy system)
│  ├─ 🔴 Implement mining mechanics and voxel destruction
│  ├─ 🔴 Create power system (generation, consumption, priority)
│  ├─ 🔴 Add building system for ship construction
│  └─ 🔴 Implement save/load persistence system
│
├─ Week 8: UI & Player Experience
│  ├─ 🔴 Create complete HUD (shields, health, energy, radar)
│  ├─ 🔴 Build inventory UI (UMG widgets)
│  ├─ 🔴 Implement ship builder UI
│  ├─ 🔴 Create galaxy map UI (3D visualization)
│  ├─ 🔴 Add menu systems (main, pause, settings)
│  ├─ 🔴 Implement trading/station UI
│  └─ 🔴 Create holographic/sci-fi UI style
│
└─ Deliverable: CORE GAMEPLAY - Complete playable game loop (mine, build, trade, fight)


PHASE 5: ADVANCED FEATURES (Weeks 9-12)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
│
├─ Week 9-10: Social Systems
│  ├─ 🔴 Implement faction system (from C# Faction system)
│  │  └─ Stellaris-style politics with pops, policies, influence
│  ├─ 🔴 Create diplomacy mechanics
│  ├─ 🔴 Build reputation system
│  ├─ 🔴 Implement quest system (from C# Quest system)
│  ├─ 🔴 Add quest UI and objective tracking
│  ├─ 🔴 Create progression system (XP, levels, upgrades)
│  └─ 🔴 Implement fleet management system
│
├─ Week 11-12: Multiplayer & Networking
│  ├─ 🔴 Set up actor replication
│  ├─ 🔴 Implement RPC functions for client-server
│  ├─ 🔴 Create server-authoritative sector management
│  ├─ 🔴 Add client prediction for ship movement
│  ├─ 🔴 Implement voxel data replication
│  ├─ 🔴 Build lag compensation system
│  └─ 🔴 Optimize network traffic
│
└─ Deliverable: Full feature set including multiplayer, factions, quests, and progression


PHASE 6: CONTENT, POLISH & RELEASE (Weeks 13-16)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
│
├─ Week 13-14: Asset Creation & Integration
│  ├─ 🔴 Create 3D ship models and modules
│  │  └─ Cockpits, engines, wings, weapons, hull sections
│  ├─ 🔴 Build station models (trading, factory, shipyard, etc.)
│  ├─ 🔴 Create asteroid variation meshes
│  ├─ 🔴 Design PBR materials and textures
│  ├─ 🔴 Implement VFX (weapons, explosions, shields, engine thrust)
│  ├─ 🔴 Add audio (SFX, music, ambient sounds)
│  └─ 🔴 Create holographic UI materials
│
├─ Week 15: Polish & Optimization
│  ├─ 🔴 Optimize voxel mesh generation
│  ├─ 🔴 Implement LOD system for distant objects
│  ├─ 🔴 Profile and optimize bottlenecks
│  ├─ 🔴 Polish UI/UX interactions
│  ├─ 🔴 Balance gameplay (combat, economy, progression)
│  ├─ 🔴 Fix bugs and edge cases
│  └─ 🔴 Add quality-of-life features
│
├─ Week 16: Release Preparation
│  ├─ 🔴 Final testing pass
│  ├─ 🔴 Update all documentation
│  ├─ 🔴 Create tutorial system
│  ├─ 🔴 Package for distribution
│  ├─ 🔴 Write release notes
│  └─ 🔴 Prepare marketing materials
│
└─ Deliverable: RELEASE 1.0 - Polished, playable game ready for distribution


═══════════════════════════════════════════════════════════════════════════

## KEY MILESTONES

🎯 **Milestone 1: PROTOTYPE** (End of Week 4)
   ├─ Flyable modular ship with Newtonian physics
   ├─ Procedurally generated sectors and asteroids
   ├─ Voxel rendering with greedy meshing
   ├─ Basic HUD with ship status
   └─ **Target:** Provable core concept

🎯 **Milestone 2: CORE GAMEPLAY** (End of Week 8)
   ├─ AI ships with believable behaviors
   ├─ Combat system fully functional
   ├─ Mining and resource gathering
   ├─ Trading at stations
   ├─ Inventory and building systems
   └─ **Target:** Playable gameplay loop

🎯 **Milestone 3: FEATURE COMPLETE** (End of Week 12)
   ├─ All major systems implemented
   ├─ Faction and diplomacy systems
   ├─ Quest and progression systems
   ├─ Multiplayer functional
   ├─ Fleet management operational
   └─ **Target:** Feature parity with C# version

🎯 **Milestone 4: RELEASE 1.0** (End of Week 16)
   ├─ Complete asset library
   ├─ Polished UI/UX
   ├─ Optimized performance (60 FPS)
   ├─ Tutorial and onboarding
   ├─ Ready for players
   └─ **Target:** Public release ready

═══════════════════════════════════════════════════════════════════════════

## SYSTEM PRIORITIES & DEPENDENCIES

### CRITICAL PATH 🔴 (Weeks 1-4)
These systems block all other progress:
├─ ✅ Project Structure - COMPLETE
├─ 🔨 Voxel System - Blocks all visual rendering
├─ 🔴 Procedural Mesh Generation - Blocks voxel display
├─ 🔴 Modular Ship System - Required for gameplay
├─ 🔴 Basic UI/HUD - Required for player interaction
└─ 🔴 Galaxy Generation - Creates game world

### HIGH PRIORITY 🟡 (Weeks 5-8)
Core gameplay functionality:
├─ 🔴 AI System - Required for NPCs
├─ 🔴 Combat Mechanics - Core gameplay
├─ 🔴 Inventory/Resources - Required for progression
├─ 🔴 Mining System - Resource gathering
└─ 🔴 Trading System - Economic gameplay

### MEDIUM PRIORITY 🟢 (Weeks 9-12)
Advanced features:
├─ 🔴 Faction System - Social gameplay
├─ 🔴 Quest System - Structured content
├─ 🔴 Fleet Management - Advanced gameplay
├─ 🔴 Multiplayer - Community features
└─ 🔴 Progression System - Player advancement

### LOW PRIORITY ⚪ (Weeks 13-16)
Polish and content:
├─ 🔴 Content Creation - Visual assets
├─ 🔴 Polish & Optimization - Performance
├─ 🔴 Tutorial System - Player onboarding
└─ 🔴 Documentation - Support materials

═══════════════════════════════════════════════════════════════════════════

## C# TO UE5 SYSTEM MAPPING

### Custom C# Engine Features → UE5 Implementation

| Original System (C#) | Status | UE5 Approach | Priority |
|---------------------|--------|--------------|----------|
| **Core Framework** |
| Entity-Component System | ✅ | Native Actor-Component | Complete |
| EntityManager | ✅ | UWorld | Complete |
| SystemBase | ✅ | AActor::Tick() | Complete |
| Event System | ✅ | Delegates/Events | Complete |
| Configuration | ✅ | Config/*.ini | Complete |
| Logging | ✅ | UE_LOG | Complete |
| **Gameplay** |
| PhysicsComponent | ⚠️ | Manual Newtonian + Chaos | In Progress |
| VoxelStructureComponent | 🔨 | UVoxelComponent | Critical |
| ModularShipComponent | 🔴 | UModularShipComponent | Critical |
| AIComponent | 🔴 | AAIController + BT | High |
| Combat System | 🔴 | Weapon Components | High |
| Mining System | 🔴 | Voxel Destruction | Medium |
| Trading System | 🔴 | Economy Component | Medium |
| **World** |
| GalaxyGenerator | 🔴 | UGalaxySubsystem | Critical |
| Procedural Generation | 🔴 | Subsystems | High |
| **Rendering** |
| GraphicsWindow | 🔴 | UE Renderer | High |
| VoxelRenderer | 🔴 | ProceduralMesh | Critical |
| GreedyMeshBuilder | 🔴 | C++ Algorithm | Critical |
| **UI** |
| ImGui UI | 🔴 | UMG Widgets | High |
| HUD System | 🔴 | AHUD + Widgets | High |
| **Multiplayer** |
| GameServer | 🔴 | Replication | Low |
| Networking | 🔴 | RPC Functions | Low |

**Legend:** ✅ Complete | ⚠️ Partial | 🔨 In Progress | 🔴 Not Started

═══════════════════════════════════════════════════════════════════════════

## CONVERSION PROGRESS TRACKING

### Overall Progress by Category

```
Core Framework   ████████████████░░░░  80%  (4/5 complete)
Physics          ████████░░░░░░░░░░░░  40%  (basic only)
Voxel System     ██░░░░░░░░░░░░░░░░░░  10%  (planning)
Rendering        ██░░░░░░░░░░░░░░░░░░  10%  (concepts)
Gameplay         █░░░░░░░░░░░░░░░░░░░   5%  (modular ship planning)
AI & Combat      ░░░░░░░░░░░░░░░░░░░░   0%  (not started)
World Gen        ░░░░░░░░░░░░░░░░░░░░   0%  (not started)
UI Systems       ░░░░░░░░░░░░░░░░░░░░   0%  (not started)
Multiplayer      ░░░░░░░░░░░░░░░░░░░░   0%  (not started)
Content          ░░░░░░░░░░░░░░░░░░░░   0%  (not started)
─────────────────────────────────────────────
OVERALL          ███░░░░░░░░░░░░░░░░░  15%  (Week 1 complete)
```

### Systems Breakdown
- ✅ **Complete:** 4 systems (Core framework mostly done)
- ⚠️ **Partial:** 1 system (Physics at 40%)
- 🔨 **In Progress:** 2 systems (Voxel, Input being implemented)
- 🔴 **Not Started:** 36 systems (85% of work remaining)

**Total Systems to Migrate:** 43 major systems across 9 categories

═══════════════════════════════════════════════════════════════════════════

## RISK ASSESSMENT & MITIGATION

### 🔴 HIGH RISK ITEMS

**1. Voxel Mesh Generation Performance**
- **Risk:** May not achieve 60 FPS with thousands of voxel blocks
- **Mitigation:** 
  - Implement greedy meshing from C# (proven algorithm)
  - Add LOD system for distant ships
  - Use instanced rendering where possible
  - Async generation on worker threads
  - Implement spatial culling with Octree

**2. Network Replication of Voxel Data**
- **Risk:** Bandwidth issues with large ship modifications
- **Mitigation:**
  - Delta compression (only sync changes)
  - Sector-based synchronization
  - Client-side prediction for local changes
  - Use UE5's property replication system

**3. Modular Ship Physics**
- **Risk:** Multi-body physics for ship modules is complex
- **Mitigation:**
  - Treat ship as single rigid body
  - Use attachment system for visual only
  - Integrate with UE5's Chaos physics
  - Implement damage as voxel overlay (C# approach)

### 🟡 MEDIUM RISK ITEMS

**1. AI Behavior Complexity**
- **Risk:** Complex AI states may be difficult to debug
- **Mitigation:**
  - Use UE5's proven Behavior Tree system
  - Port well-tested C# AI logic
  - Add visual debugging tools
  - Incremental AI feature implementation

**2. Content Creation Timeline**
- **Risk:** Creating 3D assets is time-consuming
- **Mitigation:**
  - Use marketplace assets initially
  - Procedural generation for variety
  - Focus on gameplay first, visuals later
  - Community asset contributions

**3. Performance Optimization**
- **Risk:** Large-scale battles may drop FPS
- **Mitigation:**
  - Profile early and often
  - Use UE5's Nanite for static meshes
  - Implement aggressive LOD system
  - Limit active entities per sector

### 🟢 LOW RISK ITEMS

**1. Core Gameplay Implementation**
- **Risk:** Low - already proven in C# version
- **Confidence:** High - direct port of working systems

**2. Basic Multiplayer**
- **Risk:** Low - UE5 has robust networking
- **Confidence:** High - well-documented system

**3. UI Implementation**
- **Risk:** Low - UMG is mature and flexible
- **Confidence:** High - straightforward widget creation

═══════════════════════════════════════════════════════════════════════════

## DEPENDENCIES & BLOCKERS

### External Dependencies
- ✅ Unreal Engine 5.7 (stable release)
- ✅ Visual Studio 2022 (compatible)
- ✅ C++ build tools (installed)
- 🔴 3D modeling software (Blender) - for asset creation
- 🔴 Audio tools - for sound design

### Internal Dependencies
```
Project Setup ✅
    └─> Voxel System 🔨 (Week 2)
            └─> Procedural Generation 🔴 (Week 3)
                    ├─> Modular Ships 🔴 (Week 4)
                    │       └─> AI Ships 🔴 (Week 5)
                    └─> Galaxy/Sectors 🔴 (Week 3)
                            └─> Multiplayer 🔴 (Week 11-12)
```

**Critical Blocking Chain:**
1. Voxel System → Blocks ship visuals, asteroids, damage
2. Procedural Generation → Blocks world content
3. Modular Ships → Blocks core gameplay
4. UI System → Blocks player interaction
5. Everything else → Depends on above

═══════════════════════════════════════════════════════════════════════════

## SUCCESS CRITERIA

### Technical Goals
- ✅ Project builds without errors (Week 1)
- ⏳ Ship movement feels responsive (Week 2)
- ⏳ Voxel generation achieves 60 FPS (Week 2)
- ⏳ AI ships behave believably (Week 5-6)
- ⏳ Combat feels satisfying (Week 6)
- ⏳ Multiplayer supports 8+ players smoothly (Week 12)
- ⏳ UI is intuitive and responsive (Week 8)

### Gameplay Goals
- ⏳ Game is fun to play solo (Week 8)
- ⏳ Multiplayer is engaging (Week 12)
- ⏳ Ship building is creative and rewarding (Week 11)
- ⏳ Combat is exciting (Week 6)
- ⏳ Progression feels meaningful (Week 10)

### Quality Goals
- ⏳ 60 FPS minimum on target hardware
- ⏳ No game-breaking bugs
- ⏳ Smooth learning curve with tutorial
- ⏳ Polish matches modern indie standards
- ⏳ Feature parity with C# version

═══════════════════════════════════════════════════════════════════════════

## TEAM REQUIREMENTS

### 👨‍💻 PROGRAMMERS (Critical Need)
├─ **C++ Gameplay Programmers** (2-3 needed)
│  └─ Focus: Systems migration, gameplay implementation
├─ **Graphics/Rendering Specialist** (1 needed)
│  └─ Focus: Voxel rendering, shader work, optimization
├─ **Network Programmer** (1 needed)
│  └─ Focus: Multiplayer implementation, replication
└─ **Tools Programmer** (1 needed - optional)
   └─ Focus: Editor tools, debugging utilities

### 🎨 ARTISTS (Medium Priority)
├─ **3D Modelers** (2 needed)
│  └─ Focus: Ship modules, stations, asteroids
├─ **Texture Artists** (1 needed)
│  └─ Focus: PBR materials, procedural textures
├─ **VFX Artist** (1 needed)
│  └─ Focus: Weapon effects, explosions, shields
└─ **UI/UX Designer** (1 needed)
   └─ Focus: HUD design, menu systems

### 🎵 AUDIO (Low Priority)
├─ **Sound Designer** (1 needed)
│  └─ Focus: SFX creation and implementation
└─ **Composer** (1 needed - optional)
   └─ Focus: Background music, ambient sounds

### 🎮 DESIGNERS (Medium Priority)
├─ **Game Designer** (1 needed)
│  └─ Focus: Gameplay balance, progression systems
└─ **Level Designer** (1 needed - optional)
   └─ Focus: Sector design, special locations

**Note:** Many marketplace assets can substitute for artists initially, allowing
focus on programmers first.

═══════════════════════════════════════════════════════════════════════════

## CURRENT STATUS SUMMARY

**Current Phase:** Week 2 - Voxel System Implementation  
**Overall Progress:** ~15% Complete  
**On Schedule:** ✅ Yes (Week 1 completed on time)  
**Blockers:** None currently  
**Next Milestone:** Prototype (End of Week 4)

### Recently Completed (Week 1)
- ✅ Project structure and build system
- ✅ Core C++ game classes
- ✅ Documentation and organization
- ✅ Migration checklist created
- ✅ Roadmap updated for UE5

### Currently Working On (Week 2)
- 🔨 Voxel system implementation
- 🔨 Greedy meshing algorithm
- 🔨 Basic HUD widgets
- 🔨 Enhanced Input System

### Coming Next (Week 3)
- 🔴 Procedural galaxy generation
- 🔴 Asteroid spawning system
- 🔴 Sector management

═══════════════════════════════════════════════════════════════════════════

## QUICK LINKS & DOCUMENTATION

### 📋 Essential Documents
- **[UE5 Migration Checklist](docs/migration/UE5_MIGRATION_CHECKLIST.md)** - Detailed system tracking
- **[Getting Started (UE5)](docs/migration/GETTING_STARTED_UE5.md)** - Setup and first steps
- **[Conversion Guide](docs/migration/CONVERSION_GUIDE.md)** - C# to UE5 conversion guide
- **[Migration Status](docs/migration/MIGRATION_STATUS.md)** - Current migration progress
- **[Project Overview (UE5)](docs/migration/README_UE5.md)** - UE5 project overview

### 📚 Reference Documentation
- **[Architecture](docs/architecture/ARCHITECTURE.md)** - System architecture
- **[C# Engine README](README.md)** - Original C# engine documentation
- **[Development Status](docs/reference/DEVELOPMENT_STATUS.md)** - Feature status
- **[What's Left to Implement](docs/reference/WHATS_LEFT_TO_IMPLEMENT.md)** - C# features remaining
- **[Dependencies](docs/reference/DEPENDENCIES.md)** - Project dependencies

### 🔧 Implementation Guides
- **[Modular Ship System Guide](docs/guides/MODULAR_SHIP_SYSTEM_GUIDE.md)**
- **[AI System Guide](docs/guides/AI_SYSTEM_GUIDE.md)**
- **[Voxel Construction Guide](docs/guides/AI_VOXEL_CONSTRUCTION_GUIDE.md)**
- **[Procedural Generation Guide](docs/guides/PROCEDURAL_GENERATION_GUIDE.md)**

---

**Last Updated:** January 6, 2026  
**Next Update:** After Week 2 (Voxel System implementation completion)  
**Status:** ✅ On Track - Ready for Week 2 Development

**For Contributors:** See [CONTRIBUTING.md](CONTRIBUTING.md) for how to help with the migration.  
**For Questions:** Open an issue on GitHub with the `question` label.
