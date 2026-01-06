# Unreal Engine 5.7 Conversion Guide

This document explains the conversion process from the C# .NET Codename:Subspace implementation to Unreal Engine 5.7.

## 📋 Table of Contents

1. [Overview](#overview)
2. [Prerequisites](#prerequisites)
3. [Project Structure](#project-structure)
4. [Architecture Changes](#architecture-changes)
5. [System-by-System Conversion](#system-by-system-conversion)
6. [Building the Project](#building-the-project)
7. [Next Steps](#next-steps)
8. [Troubleshooting](#troubleshooting)

## 🎯 Overview

The conversion from C# .NET to Unreal Engine 5.7 involves:

### What's Been Done
✅ Created UE5.7 project structure (`.uproject`, build files, configs)  
✅ Set up Source/ directory with C++ module structure  
✅ Implemented core game classes (GameMode, PlayerController, Pawn, GameInstance)  
✅ Configured project for desktop platforms (Windows, Linux, Mac)  
✅ Set up Content/ directory structure  
✅ Added basic 6DOF Newtonian physics for ship movement  
✅ Created input bindings framework  
✅ Documented conversion process  

### What Needs Implementation
🔲 Voxel system for ship construction  
🔲 Modular ship generation system  
🔲 Procedural galaxy generator  
🔲 AI behavior trees and controllers  
🔲 Resource and inventory systems  
🔲 Faction and diplomacy mechanics  
🔲 Quest system  
🔲 Multiplayer networking  
🔲 UI widgets (HUD, inventory, ship builder, galaxy map)  
🔲 Asset creation (ship models, textures, materials)  
🔲 Audio system  

## 🔧 Prerequisites

### Required Software

1. **Unreal Engine 5.7**
   - Download from [Epic Games Launcher](https://www.unrealengine.com/download)
   - Install with all default options
   - ~100GB disk space required

2. **Visual Studio 2022**
   - Community Edition (free) or higher
   - Required workload: "Game development with C++"
   - Required components:
     - C++ profiling tools
     - C++ AddressSanitizer
     - Windows 10/11 SDK
     - Unreal Engine installer

3. **Git** (for version control)
   - Download from [git-scm.com](https://git-scm.com/)

### System Requirements

**Minimum:**
- OS: Windows 10 64-bit
- Processor: Quad-core Intel or AMD, 2.5 GHz
- Memory: 16 GB RAM
- Graphics: DirectX 11 or 12 compatible card
- Storage: 150 GB available space

**Recommended:**
- OS: Windows 11 64-bit
- Processor: 6+ core Intel or AMD, 3+ GHz
- Memory: 32+ GB RAM
- Graphics: NVIDIA RTX 2070 or AMD RX 5700 XT or better
- Storage: 200+ GB SSD

## 📁 Project Structure

```
SubspaceUE/
├── Config/                          # Unreal configuration files
│   ├── DefaultEngine.ini           # Engine settings (rendering, physics, audio)
│   ├── DefaultGame.ini             # Game-specific settings
│   ├── DefaultInput.ini            # Input mappings and collision channels
│   └── DefaultEditor.ini           # Editor preferences
│
├── Content/                         # Unreal content (assets, blueprints)
│   ├── Maps/                       # Level maps
│   ├── Blueprints/                 # Blueprint classes
│   │   ├── Ships/                  # Ship blueprint variants
│   │   ├── AI/                     # AI controllers and behavior trees
│   │   └── Systems/                # System blueprints
│   ├── Materials/                  # Materials and material instances
│   │   ├── Ships/                  # Ship materials
│   │   ├── Asteroids/              # Asteroid materials
│   │   └── UI/                     # UI materials
│   ├── Meshes/                     # Static and skeletal meshes
│   │   ├── Ships/                  # Ship models
│   │   ├── Modules/                # Ship module parts
│   │   └── Environment/            # Space environment
│   ├── UI/                         # Widget blueprints
│   │   ├── HUD/                    # In-game HUD
│   │   ├── Menus/                  # Menu screens
│   │   └── Widgets/                # Reusable UI components
│   └── Textures/                   # Texture assets
│
├── Source/                          # C++ source code
│   ├── SubspaceUE/                 # Main game module
│   │   ├── Public/                 # Public headers (.h files)
│   │   │   ├── SubspaceUE.h              # Module header
│   │   │   ├── SubspaceGameMode.h        # Main game mode
│   │   │   ├── SubspacePlayerController.h # Player controller
│   │   │   ├── SubspacePlayerPawn.h      # Player ship pawn
│   │   │   ├── SubspaceGameInstance.h    # Game instance
│   │   │   └── Components/               # Component headers
│   │   │       ├── ShipInventoryComponent.h
│   │   │       ├── VoxelComponent.h
│   │   │       └── ShipStatsComponent.h
│   │   ├── Private/                # Implementation files (.cpp)
│   │   │   ├── SubspaceUE.cpp
│   │   │   ├── SubspaceGameMode.cpp
│   │   │   ├── SubspacePlayerController.cpp
│   │   │   ├── SubspacePlayerPawn.cpp
│   │   │   ├── SubspaceGameInstance.cpp
│   │   │   └── Components/
│   │   │       ├── ShipInventoryComponent.cpp
│   │   │       ├── VoxelComponent.cpp
│   │   │       └── ShipStatsComponent.cpp
│   │   └── SubspaceUE.Build.cs    # Module build configuration
│   ├── SubspaceUE.Target.cs        # Game target rules
│   └── SubspaceUEEditor.Target.cs  # Editor target rules
│
├── SubspaceUE.uproject             # Unreal project file
├── README_UE5.md                   # This documentation
└── CONVERSION_GUIDE.md             # You are here!
```

## 🔄 Architecture Changes

### Entity-Component System → Actor-Component System

**Original C# ECS:**
```csharp
// Create entity
var ship = entityManager.CreateEntity("PlayerShip");

// Add components
var physics = new PhysicsComponent { Mass = 1000 };
entityManager.AddComponent(ship.Id, physics);

var voxels = new VoxelStructureComponent();
entityManager.AddComponent(ship.Id, voxels);

// Systems process entities
physicsSystem.Update(deltaTime);
```

**Unreal Engine Actor-Component:**
```cpp
// Spawn actor (entity)
ASubspacePlayerPawn* Ship = GetWorld()->SpawnActor<ASubspacePlayerPawn>(
    ASubspacePlayerPawn::StaticClass(),
    SpawnLocation,
    SpawnRotation
);

// Components are added in constructor or dynamically
UShipInventoryComponent* Inventory = Ship->FindComponentByClass<UShipInventoryComponent>();

// Actors tick automatically
void ASubspacePlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdatePhysics(DeltaTime);
}
```

### Key Differences

| Concept | C# Original | Unreal Engine |
|---------|-------------|---------------|
| Entity | `Entity` class | `AActor` |
| Component | `IComponent` interface | `UActorComponent` |
| System | `SystemBase` class | `Tick()` methods / Subsystems |
| Entity Manager | `EntityManager` | `UWorld` |
| Update Loop | `GameEngine.Update()` | `Tick()` per-actor |

## 🔨 System-by-System Conversion

### 1. Physics System

**C# Original:**
- Custom `PhysicsComponent` with position, velocity, acceleration
- Manual integration in `PhysicsSystem.Update()`
- Custom collision detection

**UE5 Equivalent:**
- Use `UPrimitiveComponent` with physics enabled
- OR custom Newtonian physics (as implemented in `ASubspacePlayerPawn`)
- Built-in collision with Chaos physics engine

**Implementation Status:** ✅ Basic Newtonian physics implemented in PlayerPawn

### 2. Voxel System

**C# Original:**
```csharp
public class VoxelStructureComponent : IComponent
{
    public List<VoxelBlock> Blocks { get; set; }
    
    public void AddBlock(VoxelBlock block) { }
    public void RemoveBlock(Vector3 position) { }
}
```

**UE5 Approach:**
- Use `UProceduralMeshComponent` for dynamic voxel meshes
- Generate mesh triangles from voxel data
- Or use geometry scripting for runtime mesh generation

**Implementation Status:** 🔲 Not yet implemented - HIGH PRIORITY

**Recommended Implementation:**
```cpp
UCLASS()
class UVoxelComponent : public UActorComponent
{
    GENERATED_BODY()
    
public:
    UPROPERTY()
    UProceduralMeshComponent* VoxelMesh;
    
    UPROPERTY()
    TArray<FVoxelBlock> Blocks;
    
    void AddBlock(FVoxelBlock Block);
    void RemoveBlock(FVector Position);
    void RegenerateMesh();
};
```

### 3. Procedural Generation

**C# Original:**
- `GalaxyGenerator` with seed-based random generation
- Generates sectors, asteroids, stations on demand

**UE5 Approach:**
- Use UE5.7's production-ready **Procedural Content Generation (PCG)** system
- Or implement custom `AProcGenManager` actor
- Use `FRandomStream` for deterministic generation

**Implementation Status:** 🔲 Not yet implemented

### 4. AI System

**C# Original:**
```csharp
public class AIComponent : IComponent
{
    public AIState CurrentState { get; set; }
    public AIPersonality Personality { get; set; }
}

public class AISystem : SystemBase
{
    public void Update(float deltaTime) { }
}
```

**UE5 Approach:**
- Use `AAIController` with Behavior Trees
- Implement states as BT tasks and decorators
- Use Blackboard for AI data

**Implementation Status:** 🔲 Not yet implemented - MEDIUM PRIORITY

**Recommended Classes:**
```cpp
UCLASS()
class ASubspaceAIController : public AAIController
{
    GENERATED_BODY()
    
public:
    UPROPERTY(EditAnywhere)
    UBehaviorTree* BehaviorTree;
    
    UPROPERTY()
    UBlackboardComponent* Blackboard;
};
```

### 5. Networking

**C# Original:**
- Custom TCP networking with `GameServer` and `ClientConnection`
- Manual serialization of game state

**UE5 Approach:**
- Use built-in UE replication system
- Mark properties with `UPROPERTY(Replicated)`
- Implement `GetLifetimeReplicatedProps()`
- Use RPCs for client-server communication

**Implementation Status:** 🔲 Not yet implemented

### 6. UI System

**C# Original:**
- ImGui.NET for immediate-mode UI
- Custom `PlayerUIManager`

**UE5 Approach:**
- Use **UMG (Unreal Motion Graphics)** widget system
- Create widgets in Blueprint or C++
- Use `UUserWidget` base class

**Implementation Status:** 🔲 Not yet implemented - HIGH PRIORITY

### 7. Save/Load System

**C# Original:**
```csharp
public class SaveGameManager
{
    public void SaveGame(string filename) { }
    public SaveGameData LoadGame(string filename) { }
}
```

**UE5 Approach:**
- Inherit from `USaveGame` class
- Use `UGameplayStatics::SaveGameToSlot()`
- Automatic serialization of UPROPERTY data

**Implementation Status:** 🔲 Not yet implemented (placeholder in GameInstance)

## 🔨 Building the Project

### First Time Setup

1. **Generate Project Files:**
   ```bash
   # Windows
   Right-click SubspaceUE.uproject → "Generate Visual Studio project files"
   
   # Or command line:
   "C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" -projectfiles -project="SubspaceUE.uproject" -game -engine
   ```

2. **Open in Visual Studio:**
   - Open `SubspaceUE.sln`
   - Set `SubspaceUE` as startup project
   - Build configuration: `Development Editor`

3. **Build Solution:**
   - Build → Build Solution (Ctrl+Shift+B)
   - Wait for compilation (first build takes 5-15 minutes)

4. **Launch Editor:**
   - Press F5 in Visual Studio
   - Or double-click `SubspaceUE.uproject`

### Daily Development Workflow

1. **Make code changes** in Visual Studio
2. **Hot reload** in editor (click Compile button) for small changes
3. **Full rebuild** (F7 in VS) for larger changes
4. **Test in editor** using PIE (Play In Editor - Alt+P)

### Building for Distribution

**Development Build:**
```bash
"C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" SubspaceUE Win64 Development "SubspaceUE.uproject"
```

**Shipping Build:**
```bash
"C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" SubspaceUE Win64 Shipping "SubspaceUE.uproject"
```

**Package for Windows:**
- File → Package Project → Windows → Windows (64-bit)
- Select output directory
- Wait for packaging (10-30 minutes)

## 📝 Next Steps

### Immediate Priorities

1. **Implement Voxel System** (Week 1-2)
   - Create `UVoxelComponent`
   - Implement procedural mesh generation
   - Port greedy meshing algorithm
   - Add voxel materials

2. **Create Basic UI** (Week 1-2)
   - Main menu widget
   - HUD widget (health, shields, speed)
   - Inventory widget
   - Galaxy map widget (basic)

3. **Procedural Content** (Week 2-3)
   - Asteroid spawning system
   - Galaxy sector generation
   - Resource distribution

4. **AI Implementation** (Week 3-4)
   - AI controller base class
   - Basic behavior tree (patrol, engage)
   - AI ship spawning

### Medium-Term Goals

5. **Modular Ship System** (Week 4-6)
   - Port ship module definitions
   - Implement attachment system
   - Procedural ship generation

6. **Multiplayer** (Week 6-8)
   - Set up replication
   - Server-client architecture
   - Sector synchronization

7. **Advanced Features** (Week 8+)
   - Faction system
   - Quest system
   - Trading and economy
   - Power management

### Content Creation

- **3D Assets**: Ship models, modules, asteroids, space stations
- **Materials**: PBR materials for ships, rocks, UI
- **VFX**: Weapon effects, explosions, engine trails
- **Audio**: Sound effects, music, ambient space audio
- **UI**: HUD elements, icons, fonts

## 🐛 Troubleshooting

### "Module not found" Error
**Cause:** Build files out of sync  
**Solution:**
1. Close UE editor and Visual Studio
2. Delete `Binaries/`, `Intermediate/`, `Saved/` folders
3. Right-click `.uproject` → Generate Visual Studio project files
4. Rebuild in Visual Studio

### IntelliSense Not Working
**Cause:** VS not recognizing UE macros  
**Solution:**
1. Tools → Options → Text Editor → C/C++ → Advanced
2. Set "Disable Database" to False
3. Rescan solution

### Slow Compilation
**Cause:** Full rebuild instead of incremental  
**Solution:**
- Use Hot Reload for small changes (Compile button in editor)
- Enable Live Coding (Ctrl+Alt+F11)
- Close unused projects in VS

### Cannot Package Project
**Cause:** Missing or invalid content  
**Solution:**
1. Check Output Log for specific errors
2. Fix > Redirect References in Content Browser
3. Ensure all blueprint parent classes exist

## 📚 Additional Resources

### Unreal Engine 5.7 Documentation
- [Getting Started](https://docs.unrealengine.com/5.7/en-US/getting-started/)
- [C++ Programming](https://docs.unrealengine.com/5.7/en-US/programming-with-cplusplus-in-unreal-engine/)
- [Gameplay Framework](https://docs.unrealengine.com/5.7/en-US/gameplay-framework-in-unreal-engine/)
- [Networking](https://docs.unrealengine.com/5.7/en-US/networking-and-multiplayer-in-unreal-engine/)
- [PCG System](https://docs.unrealengine.com/5.7/en-US/procedural-content-generation-overview/)

### Original Project Documentation
- `README.md` - Original C# project overview
- `ARCHITECTURE.md` - System architecture
- `GAMEPLAY_FEATURES.md` - Feature descriptions
- `MODDING_GUIDE.md` - Scripting reference
- Various implementation guides in root directory

### Community
- [Unreal Engine Forums](https://forums.unrealengine.com/)
- [Unreal Slackers Discord](https://unrealslackers.org/)
- [r/unrealengine](https://reddit.com/r/unrealengine)

---

**Document Version:** 1.0  
**Last Updated:** January 2026  
**Target Engine:** Unreal Engine 5.7  
**Status:** Initial conversion complete, content migration in progress
