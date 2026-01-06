# X4-Style Gameplay Research - Quick Reference

**Date:** January 6, 2026  
**Status:** ✅ Research Complete - Ready for Implementation

---

## What Was Researched

Comprehensive research on continuing X4-style gameplay implementation:

1. **Station Designs** - Modular space station system
2. **Ship Enhancements** - Advanced ship functionality  
3. **NPC/Crew Systems** - Character and crew management
4. **Interior Spaces** - Walkable ship and station interiors

---

## Research Documents

### 📄 STATION_DESIGN_RESEARCH.md

**What It Covers:**
- 9 station types (Trading Post, Shipyard, Factory, Mining, Research, Defense, Refueling, Command, Habitat)
- 10 module categories with 26+ individual modules
- Material tier scaling system (Iron → Avorion)
- Modular construction with attachment validation
- Station management and automation features
- Visual design guidelines
- Implementation phases (Weeks 8-9)

**Key Takeaways:**
- Stations built from pre-defined modules like LEGO
- Each module has stats, size, attachment points
- Stats aggregate from all modules
- Material tier affects all stats (4x multiplier for Avorion)
- Ported from working C# AvorionLike engine

**Classes to Implement:**
- `UModularStationComponent` - Core station component
- `ASpaceStation` - Station actor
- `UStationModuleLibrary` - Module registry
- `FStationModuleDefinition` - Module template
- Station builder & management UIs

---

### 📄 NPC_CREW_DESIGN_RESEARCH.md

**What It Covers:**
- 5 crew roles (Captain, Pilot, Service Crew, Marine, Manager)
- 5 skill types (Piloting, Boarding, Management, Engineering, Morale)
- Hiring system with cost calculation
- Assignment and transfer between ships/stations
- Training system with seminars
- Morale system affecting performance
- NPC actor implementation for visuals
- Crew management UI design

**Key Takeaways:**
- Crew members are NPCs with skills (0-5 stars each)
- Skills directly affect ship/station performance
- High piloting = faster, more agile ships
- High management = more efficient stations
- Morale affects work efficiency and desertion risk
- Based on X4: Foundations crew mechanics

**Classes to Implement:**
- `FCrewMember` - Crew data structure
- `ANPCCharacter` - Visual NPC actor
- `UCrewRecruitmentSystem` - Hiring
- `UCrewAssignmentSystem` - Assignment
- `UCrewMoraleSystem` - Morale tracking
- `UCrewTrainingSystem` - Training
- Crew management UI

---

### 📄 SHIP_INTERIOR_EXPANSION_RESEARCH.md

**What It Covers:**
- 16 new ship room types (adds to existing 10)
- 29 station-specific room types
- 27 new interactive object types (adds to existing 12)
- FPS first-person interior system
- Interactive object framework
- Procedural room generation
- Access control and security
- Integration with crew system

**Key Takeaways:**
- Players can walk through ship/station interiors (FPS)
- Rooms have functionality (medical bay heals, engineering repairs)
- Interactive objects (terminals, doors, storage, beds)
- NPCs work at stations in rooms
- Stations have public and restricted areas
- Builds on existing `UShipInteriorComponent`

**Classes to Implement:**
- `AInteriorPlayerCharacter` - FPS controller
- `UInteriorTransitionComponent` - Enter/exit system
- `AInteriorInteractiveObject` - Base interactive object
- `AInteractiveTerminal` - Computer terminal
- `AInteractiveDoor` - Door with access control
- `AInteractiveStorage` - Storage container
- `AInteractiveBed` - Rest/heal bed
- Room generation system

---

### 📄 IMPLEMENTATION_PLAN.md

**What It Covers:**
- Summary of all research
- 36 C++ classes to implement
- 23+ Blueprint assets needed
- 4-phase implementation plan (Weeks 8-12)
- Time estimates (~9,500 lines of code)
- Integration with existing systems
- Success criteria
- Testing scenarios

**Key Takeaways:**
- 5-week implementation (Weeks 8-12)
- Station system first (Weeks 8-9)
- Crew system second (Week 10)
- Interior expansion third (Week 11)
- Integration & polish last (Week 12)
- Aligns with project ROADMAP.md

---

## Key Statistics

### By The Numbers

**Station System:**
- 9 station types
- 26+ module types
- 10 module categories
- 7 material tiers
- 13 functional stats per station

**Crew System:**
- 5 crew roles
- 5 skill types
- 10 activity states
- 100-point morale system
- Skill-based performance bonuses

**Interior System:**
- 26 total ship room types (10 existing + 16 new)
- 29 station room types
- 39 total object types (12 existing + 27 new)
- 6 access levels
- FPS exploration mode

**Implementation:**
- 36 C++ classes
- 23+ Blueprint assets
- 3 Data Assets
- ~9,500 lines of code
- 5 weeks estimated

---

## Implementation Timeline

### Week 8-9: Station System ⏰
**Focus:** Core modular station system

**Deliverables:**
- `UModularStationComponent` working
- Station module library (26+ modules)
- Station builder UI
- Can construct stations from modules
- Stats calculate correctly

### Week 10: Crew System ⏰
**Focus:** NPC crew management

**Deliverables:**
- Crew data structures complete
- Hiring/assignment systems working
- Morale and training functional
- NPCs spawn in interiors
- Crew management UI

### Week 11: Interior Expansion ⏰
**Focus:** Walkable interiors

**Deliverables:**
- New room types added
- Interactive objects functional
- FPS interior mode working
- Can walk through ships/stations
- NPCs work at stations

### Week 12: Integration & Polish ⏰
**Focus:** System integration

**Deliverables:**
- Stations offer services (docking, repair, trade)
- Crew affects gameplay
- Interiors fully functional
- Visual polish complete
- Tested and balanced

---

## How Systems Integrate

### Station ↔ Ships
- Ships dock at stations
- Stations repair/refuel ships
- Stations sell ships and equipment
- Trading between ship and station

### Crew ↔ Ships/Stations
- Crew assigned to ships or stations
- Crew skills affect performance
- Hire crew at stations
- NPCs visible in interiors

### Interiors ↔ Everything
- Ships have walkable interiors
- Stations have public/restricted areas
- Interactive objects in rooms
- Crew works at interior stations
- Player explores in FPS mode

---

## Success Criteria

### Station System ✓
- [ ] Can build 9 different station types
- [ ] 26+ modules available for construction
- [ ] Stats calculate from all modules
- [ ] Material tier scaling works
- [ ] Stations can be damaged/destroyed
- [ ] Visual representation looks good
- [ ] UI is intuitive

### Crew System ✓
- [ ] Can hire crew at stations
- [ ] Can assign crew to ships/stations
- [ ] 5 skills affect performance correctly
- [ ] Morale system works
- [ ] Training increases skills
- [ ] NPCs visible and animated in interiors
- [ ] UI shows all crew info

### Interior System ✓
- [ ] Can enter ship/station interiors
- [ ] FPS movement feels good
- [ ] Can interact with all object types
- [ ] Terminals open functional UIs
- [ ] Doors have access control
- [ ] NPCs work at their stations
- [ ] Visuals are immersive

---

## Quick Start Guide

### For Developers Starting Implementation

1. **Read Research Docs (30 min)**
   - Start with IMPLEMENTATION_PLAN.md
   - Skim the 3 detailed research docs
   - Understand the overall architecture

2. **Review Existing Code (15 min)**
   - Look at `UShipInteriorComponent` (already exists)
   - Look at `UShipEquipmentComponent` (already exists)
   - Look at `AUlyssesShip` (already exists)
   - Look at C# `ModularStationComponent.cs` (reference)

3. **Set Up Data Structures (Week 8 Day 1)**
   - Create all enums first
   - Create all structs next
   - Create class headers
   - Compile to check syntax

4. **Implement Core Logic (Week 8 Days 2-5)**
   - `UModularStationComponent` implementation
   - Module library system
   - Attachment validation
   - Stats aggregation

5. **Build UI (Week 9)**
   - Station builder widget
   - Station management widget
   - Test with Blueprint examples

6. **Continue with Crew (Week 10)**
   - Follow same pattern
   - Structs → Classes → Logic → UI

---

## Important Notes

### Dependencies

**Must Complete First:**
- Week 2: Voxel system (for asteroids)
- Week 3-4: World generation (for sector placement)
- Week 7: Basic UI framework (for widgets)

**Recommended Complete First:**
- Week 5-6: AI system (for NPC behavior)
- Week 5-6: Combat system (for station defense)

**Can Work In Parallel:**
- Station system relatively independent
- Interior system builds on existing component
- Crew system integrates later

### Code References

**Port from C# to UE5:**
- `AvorionLike/Core/Modular/ModularStationComponent.cs`
- `AvorionLike/Core/Modular/StationModuleDefinition.cs`
- `AvorionLike/Core/Modular/ModularProceduralStationGenerator.cs`

**Extend Existing UE5:**
- `Source/SubspaceUE/Public/ShipInteriorComponent.h`
- `Source/SubspaceUE/Public/ShipEquipmentComponent.h`
- `Source/SubspaceUE/Public/UlyssesShip.h`

**Reference for Design:**
- `X4_SYSTEMS_DESIGN.md` - X4: Foundations mechanics
- `docs/guides/X4_SHIP_IMPLEMENTATION_GUIDE.md`

---

## Questions & Answers

### Why not start implementation now?

Project is currently in Week 2 (Voxel System). Station/crew systems scheduled for Weeks 8-12 per ROADMAP.md. Need UI framework (Week 7) and ideally AI system (Week 5-6) first.

### Can we skip any of these systems?

- **Station System** - Core gameplay, don't skip
- **Crew System** - Adds depth, could be simplified but recommended
- **Interior System** - Could be deprioritized if time-limited

### How much is based on existing code?

- **Station System** - 80% ported from working C# code
- **Crew System** - 60% designed from X4 reference
- **Interior System** - 40% extends existing UShipInteriorComponent

### What if we want to start early?

Could start station system after Week 2 (Voxel complete). Would need to:
1. Create basic UI widgets manually
2. Skip NPC visuals initially (add in Week 11)
3. Use placeholder models for stations

### What's the critical path?

Station System → Crew Data → Interior Expansion → Integration

Can parallelize some work, but station system should complete first as it's foundation for the other systems.

---

## Resource Links

### Research Documents
- `docs/research/STATION_DESIGN_RESEARCH.md` - 17KB, stations
- `docs/research/NPC_CREW_DESIGN_RESEARCH.md` - 22KB, crew
- `docs/research/SHIP_INTERIOR_EXPANSION_RESEARCH.md` - 25KB, interiors
- `docs/research/IMPLEMENTATION_PLAN.md` - 14KB, overall plan

### Related Documentation
- `ROADMAP.md` - Project timeline
- `X4_SYSTEMS_DESIGN.md` - X4 mechanics reference
- `docs/migration/UE5_MIGRATION_CHECKLIST.md` - System tracking

### Existing Code
- `Source/SubspaceUE/Public/ShipInteriorComponent.h`
- `Source/SubspaceUE/Public/UlyssesShip.h`
- `AvorionLike/Core/Modular/` - C# reference code

---

## Summary

✅ **Research Complete**  
✅ **All Systems Designed**  
✅ **Implementation Plan Ready**  
✅ **Timeline Established**  
⏰ **Awaiting Week 8 Start**

Ready to implement X4-style station, crew, and interior systems when project reaches appropriate phase.

---

**Last Updated:** January 6, 2026  
**Status:** Research Phase Complete  
**Next Phase:** Implementation (Weeks 8-12)
