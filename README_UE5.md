# Codename:Subspace - Unreal Engine 5.6

**Advanced Space Game Engine** - Now powered by Unreal Engine 5.6!

> **🎮 Status:** READY TO PLAY! Core gameplay systems implemented!  
> **🚀 NEW:** 6DOF ship physics, procedural content spawning, HUD system, and full input controls!  
> **⚡ Quick Start:** See [QUICKSTART_UE5.md](QUICKSTART_UE5.md) to be playing in **5 minutes**!

## What's Working Right Now

✅ **Player Ship** - Fully controllable with Newtonian 6DOF physics  
✅ **Controls** - WASD + Arrow Keys + Q/E for complete flight control  
✅ **HUD System** - Real-time speed, position, and velocity display  
✅ **Procedural Content** - 50 asteroids and 5 AI ships spawned automatically  
✅ **Lighting System** - Dynamic sun and ambient lighting  
✅ **Space Environment** - Zero gravity physics simulation  
✅ **Input Bindings** - Full keyboard and gamepad support  

## Quick Start (5 Minutes)

```bash
1. Build the project (F5 in Visual Studio or open .uproject)
2. Create Content/Maps/SpaceLevel (Empty Level in Unreal Editor)
3. Press Play (Alt+P)
4. Fly with WASD! 🚀
```

**Full instructions:** [QUICKSTART_UE5.md](QUICKSTART_UE5.md)  
**Automated setup:** Run [create_space_level.py](create_space_level.py) in Unreal's Python console!

---

# Codename:Subspace - Unreal Engine 5.7 Version

This is the Unreal Engine 5.7 conversion of the Codename:Subspace space game engine, originally built in C# .NET.

## 🎮 Overview

Codename:Subspace is an advanced space game featuring:
- **Voxel-based ship construction** - Build custom spaceships block by block
- **Modular ship generation** - Procedurally generated ships from modular parts
- **Newtonian physics** - Realistic 6DOF space flight with momentum
- **Procedural galaxy** - Explore a vast procedurally generated universe
- **AI ships** - Dynamic AI behaviors including combat, mining, and trading
- **Faction system** - Complex diplomacy and reputation mechanics
- **Multiplayer** - Built-in networking support
- **Resource management** - Mine asteroids, trade resources, build your empire

## 🚀 Quick Start

### Prerequisites

1. **Unreal Engine 5.7** - Download from [Epic Games Launcher](https://www.unrealengine.com/download)
2. **Visual Studio 2022** - Required for C++ development
   - Workload: "Game development with C++"
   - Components: "Unreal Engine installer" and "C++ profiling tools"
3. **Windows 10/11** (64-bit) or **Linux** - Recommended: Windows for full feature support

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/shifty81/SubspaceUE.git
   cd SubspaceUE
   ```

2. **Generate Visual Studio project files**
   - Right-click on `SubspaceUE.uproject`
   - Select "Generate Visual Studio project files"
   
   Or from command line:
   ```bash
   "C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" -projectfiles -project="SubspaceUE.uproject" -game -engine
   ```

3. **Open the project**
   - Double-click `SubspaceUE.uproject` to open in Unreal Editor
   - Or open `SubspaceUE.sln` in Visual Studio 2022

4. **Build the project**
   - In Unreal Editor: Click "Compile" button
   - Or in Visual Studio: Build → Build Solution (Ctrl+Shift+B)

### First Launch

1. **Open the editor** - Double-click `SubspaceUE.uproject`
2. **Load the main menu map** - Content/Maps/MainMenu
3. **Press Play** - Click the Play button or press Alt+P

## 📁 Project Structure

```
SubspaceUE/
├── Config/                          # Configuration files
│   ├── DefaultEngine.ini           # Engine settings
│   ├── DefaultGame.ini             # Game settings
│   ├── DefaultInput.ini            # Input mappings
│   └── DefaultEditor.ini           # Editor settings
├── Content/                         # Game content (assets, blueprints, etc.)
│   ├── Maps/                       # Level maps
│   ├── Blueprints/                 # Blueprint classes
│   ├── Materials/                  # Materials and textures
│   ├── Meshes/                     # 3D models
│   └── UI/                         # User interface widgets
├── Source/                          # C++ source code
│   ├── SubspaceUE/                 # Main game module
│   │   ├── Public/                 # Public headers
│   │   │   ├── SubspaceUE.h
│   │   │   ├── SubspaceGameMode.h
│   │   │   ├── SubspacePlayerController.h
│   │   │   ├── SubspacePlayerPawn.h
│   │   │   └── SubspaceGameInstance.h
│   │   ├── Private/                # Implementation files
│   │   │   ├── SubspaceUE.cpp
│   │   │   ├── SubspaceGameMode.cpp
│   │   │   ├── SubspacePlayerController.cpp
│   │   │   ├── SubspacePlayerPawn.cpp
│   │   │   └── SubspaceGameInstance.cpp
│   │   └── SubspaceUE.Build.cs    # Build configuration
│   ├── SubspaceUE.Target.cs        # Game build target
│   └── SubspaceUEEditor.Target.cs  # Editor build target
└── SubspaceUE.uproject             # Project file
```

## 🎯 Core Systems

### 1. Player Ship System
- **Class**: `ASubspacePlayerPawn`
- **Features**: 6DOF movement, Newtonian physics, manual velocity control
- **Controls**: WASD for thrust, Arrow keys for rotation, Q/E for roll, X for brake

### 2. Game Mode
- **Class**: `ASubspaceGameMode`
- **Features**: Manages game state, spawns AI ships, generates asteroids
- **Responsibilities**: Galaxy sector management, procedural content generation

### 3. Player Controller
- **Class**: `ASubspacePlayerController`
- **Features**: Input handling, UI management, camera control
- **Functions**: Toggle control modes, open galaxy map, manage inventory

### 4. Game Instance
- **Class**: `USubspaceGameInstance`
- **Features**: Persistent data, save/load system, global state
- **Data**: Player inventory, credits, faction reputation

## 🔧 Development

### Building from Source

**Windows:**
```bash
# Build Development configuration
"C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" SubspaceUEEditor Win64 Development "SubspaceUE.uproject"

# Build Shipping configuration
"C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" SubspaceUE Win64 Shipping "SubspaceUE.uproject"
```

**Linux:**
```bash
# Build Development
/opt/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh SubspaceUEEditor Linux Development SubspaceUE.uproject

# Build Shipping
/opt/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh SubspaceUE Linux Shipping SubspaceUE.uproject
```

### Creating New Classes

Use Unreal's class wizard:
1. **File → New C++ Class**
2. Choose parent class
3. Name your class
4. Click "Create Class"

Or add manually:
1. Create `.h` file in `Source/SubspaceUE/Public/`
2. Create `.cpp` file in `Source/SubspaceUE/Private/`
3. Regenerate project files
4. Build

### Hot Reload

- **In Editor**: Click "Compile" button for quick code changes
- **Live Coding**: Ctrl+Alt+F11 for faster iteration
- Note: Complex changes may require editor restart

## 🎮 Controls (Default)

### Ship Controls
- **W/S** - Forward/Backward thrust
- **A/D** - Left/Right thrust
- **Space/Ctrl** - Up/Down thrust
- **Arrow Up/Down** - Pitch
- **Arrow Left/Right** - Yaw
- **Q/E** - Roll
- **X** - Emergency brake

### UI Controls
- **M** - Galaxy Map
- **I** - Inventory
- **B** - Ship Builder
- **Tab** - Player Status
- **ESC** - Pause Menu
- **~** - Console

### Camera
- **C** - Toggle camera/ship control mode
- **Mouse** - Look around (camera mode)

## 🌌 Porting from C# Original

This project was converted from the original C# .NET implementation. Key changes:

### Architecture Changes
- **ECS → Actor-Component**: Replaced custom Entity-Component System with Unreal's native Actor-Component architecture
- **OpenGL → UE Renderer**: Graphics now use Unreal's renderer (supports DX12, Vulkan, Metal)
- **Custom Physics → Chaos**: Physics system now uses Unreal's Chaos physics engine (with manual Newtonian simulation)
- **NLua → Blueprints**: Lua scripting replaced with Blueprints and C++ for modding

### System Conversions
| Original (C#) | Unreal Engine (C++) |
|--------------|---------------------|
| `Entity` | `AActor` |
| `EntityManager` | `UWorld` |
| `IComponent` | `UActorComponent` |
| `SystemBase` | `UGameplayStatics` / `AGameMode` |
| `PhysicsComponent` | `UPrimitiveComponent` |
| `GraphicsWindow` | `UGameViewportClient` |
| `ScriptingEngine` | `UBlueprintFunctionLibrary` |

### Code Examples

**C# Original:**
```csharp
var ship = engine.EntityManager.CreateEntity("Player Ship");
var physicsComponent = new PhysicsComponent {
    Position = new Vector3(100, 100, 100),
    Mass = 1000
};
engine.EntityManager.AddComponent(ship.Id, physicsComponent);
```

**UE5 C++ Equivalent:**
```cpp
ASubspacePlayerPawn* Ship = GetWorld()->SpawnActor<ASubspacePlayerPawn>(
    ASubspacePlayerPawn::StaticClass(),
    FVector(100, 100, 100),
    FRotator::ZeroRotator
);
Ship->ShipMesh->SetMassOverrideInKg(NAME_None, 1000.0f);
```

## 📚 Additional Documentation

### Original C# Documentation
The original C# implementation documentation is still available in the repository:
- `README.md` - Original project overview
- `ARCHITECTURE.md` - System architecture details
- `GAMEPLAY_FEATURES.md` - Complete feature list
- `MODDING_GUIDE.md` - Lua modding guide (Blueprint equivalent)
- `AI_SYSTEM_GUIDE.md` - AI behavior system
- Various implementation guides for specific systems

### Unreal-Specific Resources
- [Unreal Engine Documentation](https://docs.unrealengine.com/)
- [C++ Programming Guide](https://docs.unrealengine.com/5.7/en-US/programming-and-scripting/)
- [Gameplay Framework](https://docs.unrealengine.com/5.7/en-US/gameplay-framework/)

## 🔍 Troubleshooting

### "Cannot open project" Error
- Ensure Unreal Engine 5.7 is installed
- Try "Generate Visual Studio project files"
- Verify Visual Studio 2022 is installed with C++ game development

### Build Errors
- Clean solution: Build → Clean Solution
- Regenerate project files: Right-click .uproject → Generate Project Files
- Delete `Intermediate`, `Binaries`, and `Saved` folders, then rebuild

### Editor Crashes
- Check `Saved/Logs/` for crash logs
- Disable plugins one by one to isolate issues
- Verify GPU drivers are up to date

### Performance Issues
- Check `r.ScreenPercentage` console variable
- Disable Lumen/Nanite if needed: Project Settings → Rendering
- Use `stat fps` and `stat unit` console commands

## 🤝 Contributing

Contributions are welcome! This is a community project.

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/YourFeature`
3. Commit changes: `git commit -m 'Add YourFeature'`
4. Push to branch: `git push origin feature/YourFeature`
5. Open a Pull Request

### Code Style
- Follow [Unreal Coding Standard](https://docs.unrealengine.com/5.7/en-US/epic-cplusplus-coding-standard-for-unreal-engine/)
- Use Unreal's naming conventions (A for Actors, U for Objects, F for structs)
- Comment public APIs and complex logic

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🙏 Credits

- Original C# .NET implementation by the Codename:Subspace team
- Inspired by [Avorion](https://www.avorion.net/) by Boxelware
- Converted to Unreal Engine 5.7

## 📞 Support

- **Issues**: [GitHub Issues](https://github.com/shifty81/SubspaceUE/issues)
- **Discussions**: [GitHub Discussions](https://github.com/shifty81/SubspaceUE/discussions)
- **Original Project**: See `README.md` in root directory

---

**Status**: 🚧 Work in Progress - Core systems implemented, content migration ongoing

**Next Steps**: 
- Implement voxel generation system
- Port modular ship system
- Create procedural galaxy generator
- Implement AI behavior trees
- Add multiplayer networking
- Create UI widgets
