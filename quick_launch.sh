#!/bin/bash
# Quick build and launch script for SubspaceUE on Linux/Mac
# This script compiles the project and launches the Unreal Editor

echo "========================================"
echo "SubspaceUE - Quick Build and Launch"
echo "========================================"
echo ""

# Set the Unreal Engine path (adjust if your installation is different)
# Common locations:
# Linux: ~/UnrealEngine or /opt/UnrealEngine
# Mac: ~/UnrealEngine or /Applications/Epic\ Games/UE_5.6

if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    UE_PATH="$HOME/UnrealEngine"
    UE_EDITOR="$UE_PATH/Engine/Binaries/Mac/UnrealEditor.app/Contents/MacOS/UnrealEditor"
    UE_BUILD="$UE_PATH/Engine/Build/BatchFiles/Mac/Build.sh"
    PLATFORM="Mac"
else
    # Linux
    UE_PATH="$HOME/UnrealEngine"
    UE_EDITOR="$UE_PATH/Engine/Binaries/Linux/UnrealEditor"
    UE_BUILD="$UE_PATH/Engine/Build/BatchFiles/Linux/Build.sh"
    PLATFORM="Linux"
fi

# Check if Unreal Engine is installed
if [ ! -f "$UE_EDITOR" ] && [ ! -f "$UE_BUILD" ]; then
    echo "ERROR: Unreal Engine 5.6 not found at $UE_PATH"
    echo "Please update the UE_PATH variable in this script to point to your UE installation."
    echo ""
    echo "Common locations:"
    if [[ "$OSTYPE" == "darwin"* ]]; then
        echo "  ~/UnrealEngine"
        echo "  /Applications/Epic Games/UE_5.6"
    else
        echo "  ~/UnrealEngine"
        echo "  /opt/UnrealEngine"
    fi
    exit 1
fi

echo "Found Unreal Engine at: $UE_PATH"
echo ""

# Get the project path
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_PATH="$SCRIPT_DIR/SubspaceUE.uproject"
echo "Project: $PROJECT_PATH"
echo ""

# Build the project
echo "Step 1: Building SubspaceUE..."
echo "This may take 2-5 minutes on first build..."
echo ""

"$UE_BUILD" SubspaceUEEditor $PLATFORM Development -Project="$PROJECT_PATH"

if [ $? -ne 0 ]; then
    echo ""
    echo "ERROR: Build failed! Check the output above for errors."
    exit 1
fi

echo ""
echo "========================================"
echo "✅ Build successful!"
echo "========================================"
echo ""

# Launch the editor
echo "Step 2: Launching Unreal Editor..."
echo ""
echo "Once the editor opens:"
echo "  1. Navigate to Content/Maps in Content Browser"
echo "  2. Create a new Empty Level named 'SpaceLevel' (if not exists)"
echo "  3. Press Play (Alt+P)"
echo "  4. Fly with WASD!"
echo ""

"$UE_EDITOR" "$PROJECT_PATH"

echo ""
echo "Editor closed."
