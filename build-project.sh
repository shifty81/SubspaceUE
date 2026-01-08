#!/bin/bash
# build-project.sh - Automated build script for SubspaceUE
# This script follows the documented build process from docs/COMPLETE_SETUP_GUIDE.md

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

echo -e "${CYAN}========================================${NC}"
echo -e "${CYAN}  SubspaceUE - Automated Build Script${NC}"
echo -e "${CYAN}========================================${NC}"
echo ""

# Configuration
PROJECT_NAME="SubspaceUE"
UPROJECT_FILE="${PROJECT_NAME}.uproject"
BUILD_CONFIG="${BUILD_CONFIG:-Development}"
BUILD_PLATFORM="${BUILD_PLATFORM:-Linux}"

# Detect OS
OS="unknown"
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
fi

echo -e "${YELLOW}Detected OS: $OS${NC}"
echo -e "${YELLOW}Build Configuration: $BUILD_CONFIG${NC}"
echo -e "${YELLOW}Build Platform: $BUILD_PLATFORM${NC}"
echo ""

# Function to find Unreal Engine
find_unreal_engine() {
    echo -e "${YELLOW}Looking for Unreal Engine installation...${NC}"
    
    # Common UE5 installation paths
    UE_PATHS=(
        "$HOME/UnrealEngine/Engine/Build/BatchFiles"
        "/usr/local/UnrealEngine/Engine/Build/BatchFiles"
        "/opt/UnrealEngine/Engine/Build/BatchFiles"
        "$HOME/.local/share/Epic/UnrealEngine/Engine/Build/BatchFiles"
    )
    
    for UE_PATH in "${UE_PATHS[@]}"; do
        if [ -d "$UE_PATH" ]; then
            echo -e "${GREEN}✓ Found Unreal Engine at: $UE_PATH${NC}"
            UE_ROOT=$(dirname $(dirname "$UE_PATH"))
            return 0
        fi
    done
    
    # Check if UE is in PATH
    if command -v UnrealBuildTool &> /dev/null; then
        UE_ROOT=$(dirname $(dirname $(which UnrealBuildTool)))
        echo -e "${GREEN}✓ Found Unreal Engine in PATH: $UE_ROOT${NC}"
        return 0
    fi
    
    echo -e "${RED}✗ Unreal Engine not found!${NC}"
    echo -e "${YELLOW}Please install Unreal Engine 5.6 or 5.7${NC}"
    echo -e "${YELLOW}Or set UE_ROOT environment variable${NC}"
    return 1
}

# Check if project file exists
if [ ! -f "$UPROJECT_FILE" ]; then
    echo -e "${RED}✗ Error: $UPROJECT_FILE not found!${NC}"
    echo -e "${YELLOW}Please run this script from the project root directory.${NC}"
    exit 1
fi

echo -e "${GREEN}✓ Found project file: $UPROJECT_FILE${NC}"
echo ""

# Find Unreal Engine if UE_ROOT not set
if [ -z "$UE_ROOT" ]; then
    if ! find_unreal_engine; then
        exit 1
    fi
fi

echo ""
echo -e "${CYAN}========================================${NC}"
echo -e "${CYAN}  Building Project${NC}"
echo -e "${CYAN}========================================${NC}"
echo ""

# Determine build script based on OS
if [[ "$OS" == "linux" ]]; then
    BUILD_SCRIPT="$UE_ROOT/Engine/Build/BatchFiles/Linux/Build.sh"
    RUN_UAT="$UE_ROOT/Engine/Build/BatchFiles/RunUAT.sh"
elif [[ "$OS" == "macos" ]]; then
    BUILD_SCRIPT="$UE_ROOT/Engine/Build/BatchFiles/Mac/Build.sh"
    RUN_UAT="$UE_ROOT/Engine/Build/BatchFiles/RunUAT.sh"
else
    echo -e "${RED}✗ Unsupported OS: $OS${NC}"
    exit 1
fi

# Check if build script exists
if [ ! -f "$BUILD_SCRIPT" ]; then
    echo -e "${RED}✗ Build script not found: $BUILD_SCRIPT${NC}"
    exit 1
fi

echo -e "${YELLOW}Using build script: $BUILD_SCRIPT${NC}"
echo ""

# Build the project
echo -e "${YELLOW}Building ${PROJECT_NAME}Editor ${BUILD_CONFIG} ${BUILD_PLATFORM}...${NC}"
"$BUILD_SCRIPT" ${PROJECT_NAME}Editor ${BUILD_PLATFORM} ${BUILD_CONFIG} -project="$(pwd)/${UPROJECT_FILE}" -progress

if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}✓ Build completed successfully!${NC}"
    echo ""
    echo -e "${CYAN}========================================${NC}"
    echo -e "${GREEN}  Build Complete!${NC}"
    echo -e "${CYAN}========================================${NC}"
    echo ""
    echo -e "${YELLOW}Next steps:${NC}"
    echo -e "  1. Open ${UPROJECT_FILE} in Unreal Engine"
    echo -e "  2. See docs/COMPLETE_SETUP_GUIDE.md for more information"
    echo -e "  3. See docs/QUICKSTART.md for quick start guide"
    echo ""
else
    echo ""
    echo -e "${RED}✗ Build failed!${NC}"
    echo -e "${YELLOW}Check the error messages above for details.${NC}"
    echo -e "${YELLOW}See docs/COMPLETE_SETUP_GUIDE.md for troubleshooting.${NC}"
    exit 1
fi
