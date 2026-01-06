# X4-Style Gameplay Research and Implementation Plan

**Project:** SubspaceUE - X4-Style Space Simulation  
**Date:** January 6, 2026  
**Status:** Research Complete - Ready for Implementation

---

## Overview

This document summarizes comprehensive research on continuing X4-style gameplay development for SubspaceUE, focusing on:
1. **Station Designs** - Modular space station system
2. **Ship Systems** - Enhanced ship functionality
3. **NPC/Crew** - Character and crew management
4. **Interiors** - Walkable ship and station spaces

---

## Research Documents Created

### 1. STATION_DESIGN_RESEARCH.md ✅

**Coverage:**
- 9 Station Types (Trading Post, Shipyard, Factory, etc.)
- 10 Module Categories with 26+ module types
- Material tier system (Iron → Avorion)
- Modular construction with attachment points
- Station management and automation
- Visual design guidelines
- 4-phase implementation plan

**Key Systems:**
- `UModularStationComponent` - Core station component
- `ASpaceStation` - Station actor class
- `FStationModuleDefinition` - Module templates
- `UStationModuleLibrary` - Module registry
- Station builder UI and management UI

### 2. NPC_CREW_DESIGN_RESEARCH.md ✅

**Coverage:**
- 5 Crew Roles (Captain, Pilot, Service Crew, Marine, Manager)
- 5 Skill Types (Piloting, Boarding, Management, Engineering, Morale)
- Hiring system with cost calculation
- Assignment and training systems
- Morale system affecting performance
- Performance modifiers for ships/stations
- NPC actor implementation
- Crew management UI

**Key Systems:**
- `FCrewMember` - Crew data structure
- `ANPCCharacter` - Visual NPC actor
- `UCrewRecruitmentSystem` - Hiring
- `UCrewAssignmentSystem` - Crew management
- `UCrewMoraleSystem` - Morale tracking
- `UCrewManagementWidget` - UI interface

### 3. SHIP_INTERIOR_EXPANSION_RESEARCH.md ✅

**Coverage:**
- 16 New ship room types
- 29 Station room types
- 27 New interactive objects
- FPS walkable interior system
- Interactive object framework
- Procedural room generation
- Access control system
- Integration with crew system

**Key Systems:**
- Enhanced `UShipInteriorComponent`
- `AInteriorPlayerCharacter` - FPS controller
- `AInteriorInteractiveObject` - Base interactive object
- `UInteriorLayoutGenerator` - Procedural generation
- Room connectivity and access control
- Terminal, door, storage implementations

---

## Current Project Status

### Existing Implementation ✅

**Ships:**
- ✅ Ulysses starter ship (Corvette class)
- ✅ 15 ship classes defined
- ✅ Ship equipment system
- ✅ Basic ship interior component (10 room types)

**Systems:**
- ✅ Voxel component (Week 2 in progress)
- ✅ Enhanced Input System
- ✅ Basic HUD widgets
- ✅ Player controller and pawn

**Documentation:**
- ✅ Comprehensive docs/ folder structure
- ✅ UE5 migration checklist (43 systems)
- ✅ 16-week roadmap
- ✅ X4 systems design document

### What's Needed 🔨

**Stations:**
- 🔴 Modular station system (C# ported to UE5)
- 🔴 Station module library
- 🔴 Station builder UI
- 🔴 Docking system
- 🔴 Station management UI

**NPCs/Crew:**
- 🔴 Crew member data structures
- 🔴 NPC character actors
- 🔴 Hiring and assignment systems
- 🔴 Morale and training systems
- 🔴 Crew management UI

**Interiors:**
- 🔴 FPS walkable interior system
- 🔴 Interactive object framework
- 🔴 Procedural room generation
- 🔴 Station interior types
- 🔴 Access control system

---

## Implementation Roadmap

### Phase 1: Core Systems (Weeks 8-9)

**Station System Implementation**

**Week 8 Tasks:**
1. Create `UModularStationComponent` (C++)
   - Port from C# ModularStationComponent
   - Module list management
   - Stats aggregation
   - Health tracking

2. Create `ASpaceStation` actor (C++)
   - Base station actor
   - Visual mesh component
   - Collision
   - Faction ownership

3. Create Data Structures (C++)
   - `FStationModuleDefinition` struct
   - `FStationFunctionalStats` struct
   - `FAttachmentPoint` struct
   - Station type enums

4. Create `UStationModuleLibrary` (C++)
   - Module registry system
   - Load from Data Assets
   - 26 built-in module definitions
   - Material scaling

5. Implement Attachment System
   - Attachment point validation
   - Snap-to-point placement
   - Structural integrity checks

**Week 9 Tasks:**
6. Create Station Builder UI (UMG)
   - Module selection palette
   - 3D preview
   - Stats display
   - Cost calculator
   - Placement controls

7. Test Station Construction
   - Build trading post
   - Build shipyard
   - Build factory
   - Verify stats
   - Verify visuals

### Phase 2: NPC/Crew System (Week 10)

**Crew System Implementation**

**Week 10 Tasks:**
1. Create Crew Data Structures (C++)
   - `FCrewMember` struct
   - `FCrewSkills` struct
   - `ECrewRole` enum
   - `ECrewActivity` enum

2. Create Crew Systems (C++)
   - `UCrewRecruitmentSystem`
   - `UCrewAssignmentSystem`
   - `UCrewMoraleSystem`
   - `UCrewTrainingSystem`

3. Create NPC Actor (C++)
   - `ANPCCharacter` base class
   - `UNPCSpawnSystem`
   - AI behavior trees
   - Animation states

4. Implement Crew Effects
   - Ship performance modifiers
   - Station performance modifiers
   - Skill-based bonuses
   - Morale effects

5. Create Crew Management UI (UMG)
   - `UCrewManagementWidget`
   - `UCrewListItemWidget`
   - Hiring interface
   - Assignment interface
   - Training interface

6. Test Crew System
   - Hire crew at station
   - Assign to ship
   - Train skills
   - Monitor morale
   - Visual NPCs in interior

### Phase 3: Interior Expansion (Week 11)

**Interior System Enhancement**

**Week 11 Tasks:**
1. Expand Interior System
   - Add new room types (16 ship, 29 station)
   - Add new object types (27 total)
   - Room functionality system
   - Access control

2. Create Interactive Objects (C++)
   - `AInteriorInteractiveObject` base
   - `AInteractiveTerminal`
   - `AInteractiveDoor`
   - `AInteractiveStorage`
   - `AInteractiveBed`

3. Implement FPS System
   - `AInteriorPlayerCharacter`
   - `UInteriorTransitionComponent`
   - Camera controls
   - Movement system
   - Interaction system

4. Create Interior Generator
   - `UInteriorLayoutGenerator`
   - Room templates
   - Object placement rules
   - Connectivity validation

5. Create Interior Visuals
   - Room mesh generation
   - Object mesh placement
   - Lighting setup
   - Material application

6. Test Interior System
   - Generate ship interior (Corvette)
   - Generate station interior (Trading Post)
   - Walk through FPS
   - Interact with objects
   - See NPCs at work

### Phase 4: Integration & Polish (Week 12)

**System Integration**

**Week 12 Tasks:**
1. Station Services
   - Docking bay implementation
   - Ship repair service
   - Refueling service
   - Trading terminal
   - Ship sales

2. Crew-Interior Integration
   - NPCs spawned in correct rooms
   - NPCs walk between stations
   - NPCs perform work animations
   - Player can talk to NPCs
   - Crew affects room functionality

3. Station-Ship Integration
   - Ships dock at stations
   - Access station services
   - Trade with station
   - Hire crew at station
   - Buy equipment

4. Visual Polish
   - Module-specific meshes
   - Docking effects
   - Shield visuals
   - Interior lighting
   - Damage effects

5. UI Polish
   - Station management interface
   - Crew management interface
   - Interior interaction prompts
   - Tutorial messages

6. Testing & Balance
   - Performance testing
   - Gameplay balance
   - Bug fixing
   - Documentation updates

---

## Technical Implementation Details

### C++ Classes to Create

**Station System (14 classes):**
1. `UModularStationComponent` - Component for modular stations
2. `ASpaceStation` - Base station actor
3. `UStationModuleLibrary` - Module registry
4. `UStationBuilderWidget` - Construction UI
5. `UStationManagementWidget` - Operations UI
6. `UDockingBayComponent` - Ship docking
7. `FStationModuleDefinition` - Module template struct
8. `FStationFunctionalStats` - Stats struct
9. `FAttachmentPoint` - Attachment point struct
10. `EStationType` - Station type enum
11. `EStationModuleCategory` - Module category enum
12. `UStationDataAsset` - Data asset for modules
13. `AStationModuleActor` - Visual module actor
14. `UStationProceduralGenerator` - Auto-generation

**Crew System (12 classes):**
1. `FCrewMember` - Crew data struct
2. `FCrewSkills` - Skills struct
3. `ECrewRole` - Role enum
4. `ECrewActivity` - Activity enum
5. `ANPCCharacter` - NPC actor
6. `UNPCSpawnSystem` - Spawn subsystem
7. `UCrewRecruitmentSystem` - Hiring
8. `UCrewAssignmentSystem` - Assignment
9. `UCrewMoraleSystem` - Morale tracking
10. `UCrewTrainingSystem` - Training
11. `UCrewManagementWidget` - Management UI
12. `UCrewListItemWidget` - List item UI

**Interior System (10 classes):**
1. `AInteriorPlayerCharacter` - FPS controller
2. `UInteriorTransitionComponent` - Enter/exit system
3. `AInteriorInteractiveObject` - Base interactive
4. `AInteractiveTerminal` - Computer terminal
5. `AInteractiveDoor` - Door with access control
6. `AInteractiveStorage` - Storage container
7. `AInteractiveBed` - Rest/heal bed
8. `UInteriorLayoutGenerator` - Room generation
9. `FRoomTemplate` - Room template struct
10. `FRoomConnection` - Room connectivity struct

**Total New Classes: 36 C++ classes**

### Blueprint Classes to Create

**UI Widgets (8 widgets):**
1. WBP_StationBuilder - Station construction UI
2. WBP_StationManagement - Station operations UI
3. WBP_CrewManagement - Crew roster UI
4. WBP_CrewHiring - Crew recruitment UI
5. WBP_CrewTraining - Training interface
6. WBP_InteriorInteraction - Object interaction prompts
7. WBP_Terminal - Terminal UI
8. WBP_Storage - Storage container UI

**Actor Blueprints (15+ actors):**
1. BP_SpaceStation_TradingPost
2. BP_SpaceStation_Shipyard
3. BP_SpaceStation_Factory
4. BP_SpaceStation_MiningStation
5. BP_SpaceStation_ResearchStation
6. BP_NPCCharacter_Captain
7. BP_NPCCharacter_Pilot
8. BP_NPCCharacter_Engineer
9. BP_NPCCharacter_Marine
10. BP_NPCCharacter_Manager
11. BP_Interactive_Terminal
12. BP_Interactive_Door
13. BP_Interactive_Storage
14. BP_Interactive_Bed
15. BP_InteriorPlayerCharacter

### Data Assets (3+ assets):**
1. DA_StationModules - All station module definitions
2. DA_CrewNames - Name generation databases
3. DA_RoomTemplates - Interior room templates

---

## Estimated Work

### Time Breakdown

| Phase | Duration | Work Items | Complexity |
|-------|----------|------------|------------|
| **Phase 1: Stations** | Week 8-9 | 7 major tasks | High |
| **Phase 2: Crew** | Week 10 | 6 major tasks | Medium |
| **Phase 3: Interiors** | Week 11 | 6 major tasks | High |
| **Phase 4: Integration** | Week 12 | 6 major tasks | Medium |
| **Total** | 5 weeks | 25 tasks | - |

### Lines of Code Estimate

- Station System: ~3,500 lines C++
- Crew System: ~2,500 lines C++
- Interior System: ~2,000 lines C++
- UI Widgets: ~1,500 lines Blueprint
- **Total: ~9,500 lines of code**

### Dependencies

**Requires Completion First:**
- ✅ Week 1: Project setup (COMPLETE)
- 🔨 Week 2: Voxel system (IN PROGRESS)
- 🔴 Week 3-4: World generation & modular ships (NOT STARTED)
- 🔴 Week 5-6: AI & combat systems (NOT STARTED)
- 🔴 Week 7: UI systems (NOT STARTED)

**Can Start After:**
- Week 7 completion (UI systems available)
- Station system benefits from AI being ready (Week 5-6)
- NPC system requires AI framework (Week 5-6)

---

## Success Criteria

### Station System ✓
- [ ] Can build stations from modules
- [ ] 9 station types functional
- [ ] 26+ module types available
- [ ] Stats calculated correctly
- [ ] Material scaling works
- [ ] Stations can be damaged/destroyed
- [ ] Visual representation looks good

### Crew System ✓
- [ ] Can hire crew at stations
- [ ] Can assign crew to ships/stations
- [ ] Skills affect performance
- [ ] Morale system works
- [ ] Training increases skills
- [ ] NPCs visible in interiors
- [ ] UI is intuitive

### Interior System ✓
- [ ] Can enter ship interiors
- [ ] Can enter station interiors
- [ ] FPS movement works
- [ ] Can interact with objects
- [ ] Terminals open UIs
- [ ] Doors have access control
- [ ] NPCs work at stations
- [ ] Visuals are immersive

---

## Next Steps

### Immediate Actions ✅

1. **Research Complete** ✅
   - Created STATION_DESIGN_RESEARCH.md
   - Created NPC_CREW_DESIGN_RESEARCH.md
   - Created SHIP_INTERIOR_EXPANSION_RESEARCH.md
   - Created this implementation plan

2. **Ready for Development** 🔨
   - All systems designed
   - Data structures defined
   - Implementation phases planned
   - Success criteria established

### When to Start

**Recommended Start:** After Week 7 (UI Systems complete)
- Requires basic UI framework
- Benefits from AI system being ready
- Follows natural progression in ROADMAP.md

**Earliest Start:** After Week 2 (Voxel system complete)
- Can start with station system
- Crew system less dependent on other systems
- Interior system needs basic rendering

---

## Resources and References

### Existing Code to Port
- C# `ModularStationComponent.cs` → UE5 C++
- C# `StationModuleDefinition.cs` → UE5 C++
- C# `ModularProceduralStationGenerator.cs` → UE5 C++

### Existing Components to Extend
- `UShipInteriorComponent` - Add station support
- `UShipEquipmentComponent` - Adapt for stations
- `AUlyssesShip` - Reference for station actors

### Documentation References
- X4_SYSTEMS_DESIGN.md - X4 gameplay mechanics
- ROADMAP.md - Overall project timeline
- UE5_MIGRATION_CHECKLIST.md - System tracking

---

## Conclusion

This research provides complete foundation for implementing X4-style station, crew, and interior systems. All three systems are well-defined, implementation-ready, and aligned with the project roadmap.

**Key Achievements:**
- ✅ 3 comprehensive research documents
- ✅ 36 C++ classes designed
- ✅ 23+ Blueprint classes planned
- ✅ 4-phase implementation strategy
- ✅ Clear success criteria
- ✅ Integration with existing systems

**Ready to Proceed:**
- All research complete
- Systems fully designed
- Data structures defined
- Implementation phases planned
- Timeline aligned with ROADMAP.md

**Estimated Delivery:**
- Weeks 8-12 (5 weeks)
- ~9,500 lines of code
- 36 C++ classes
- 23+ Blueprint assets
- Full X4-style gameplay

---

**Document Status:** ✅ Complete  
**Last Updated:** January 6, 2026  
**Ready for:** Implementation Phase
**Next Milestone:** Week 8 - Core Station System
