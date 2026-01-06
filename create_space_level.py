"""
Unreal Engine Python script to automatically create the SpaceLevel map

How to use:
1. Open Unreal Editor
2. Enable Python plugin: Edit → Plugins → Search "Python" → Enable → Restart
3. Window → Developer Tools → Python Console or Output Log
4. Run this script: 
   - Copy and paste into Python Console, OR
   - Tools → Execute Python Script → Select this file

This will create /Game/Maps/SpaceLevel automatically!
"""

import unreal

def create_space_level():
    """Create the SpaceLevel map automatically"""
    
    # Set up asset tools
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    editor_asset_lib = unreal.EditorAssetLibrary()
    
    # Define the package path
    package_path = "/Game/Maps"
    asset_name = "SpaceLevel"
    full_path = f"{package_path}/{asset_name}"
    
    # Create the Maps directory if it doesn't exist
    if not editor_asset_lib.does_directory_exist(package_path):
        editor_asset_lib.make_directory(package_path)
        unreal.log(f"Created directory: {package_path}")
    
    # Check if level already exists
    if editor_asset_lib.does_asset_exist(full_path):
        unreal.log_warning(f"Level already exists at {full_path}")
        result = unreal.EditorDialog.show_message(
            "Level Exists",
            f"SpaceLevel already exists at {full_path}\n\nDo you want to overwrite it?",
            unreal.AppMsgType.YES_NO
        )
        if result == unreal.AppReturnType.NO:
            unreal.log("User cancelled - keeping existing level")
            return False
    
    # Create a new world
    world_factory = unreal.WorldFactory()
    
    # Create the asset
    try:
        new_world = asset_tools.create_asset(
            asset_name=asset_name,
            package_path=package_path,
            asset_class=unreal.World,
            factory=world_factory
        )
        
        if new_world:
            unreal.log(f"✅ Successfully created SpaceLevel at {full_path}")
            
            # Save the asset
            editor_asset_lib.save_asset(full_path)
            unreal.log("✅ SpaceLevel saved")
            
            # Optionally load the level
            load_level = unreal.EditorDialog.show_message(
                "Success!",
                "SpaceLevel created successfully!\n\nDo you want to open it now?",
                unreal.AppMsgType.YES_NO
            )
            
            if load_level == unreal.AppReturnType.YES:
                unreal.EditorLoadingAndSavingUtils.load_map(full_path)
                unreal.log("✅ SpaceLevel loaded")
            
            # Show final instructions
            unreal.log("=" * 60)
            unreal.log("🎮 READY TO PLAY!")
            unreal.log("=" * 60)
            unreal.log("Press the PLAY button (or Alt+P) to start the game!")
            unreal.log("")
            unreal.log("The game will automatically:")
            unreal.log("  • Spawn your ship")
            unreal.log("  • Create lighting")
            unreal.log("  • Generate asteroids and AI ships")
            unreal.log("  • Display the HUD with controls")
            unreal.log("")
            unreal.log("Controls:")
            unreal.log("  • W/S - Forward/Backward")
            unreal.log("  • A/D - Strafe")
            unreal.log("  • Space/Shift - Up/Down")
            unreal.log("  • Arrow Keys - Pitch/Yaw")
            unreal.log("  • Q/E - Roll")
            unreal.log("  • B - Brake")
            unreal.log("=" * 60)
            
            return True
        else:
            unreal.log_error("❌ Failed to create SpaceLevel")
            return False
            
    except Exception as e:
        unreal.log_error(f"❌ Error creating level: {str(e)}")
        return False

# Run the function
if __name__ == "__main__":
    unreal.log("=" * 60)
    unreal.log("Creating SpaceLevel...")
    unreal.log("=" * 60)
    success = create_space_level()
    if not success:
        unreal.log_warning("Failed to create level. Please try creating it manually:")
        unreal.log("1. Content Browser → Content/Maps")
        unreal.log("2. Right-click → Level → Empty Level")
        unreal.log("3. Name it 'SpaceLevel'")
        unreal.log("4. Press Play!")
