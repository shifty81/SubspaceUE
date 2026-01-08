#!/bin/bash

# generate-pdfs.sh - Generate PDF documentation from markdown files
# Requires: pandoc, xelatex (from texlive or miktex)

set -e

echo "================================================"
echo " SubspaceUE PDF Documentation Generator"
echo "================================================"
echo ""

# Check if pandoc is installed
if ! command -v pandoc &> /dev/null; then
    echo "Error: pandoc not found!"
    echo ""
    echo "Please install pandoc:"
    echo "  Mac:     brew install pandoc"
    echo "  Linux:   sudo apt-get install pandoc"
    echo "  Windows: choco install pandoc"
    echo ""
    echo "Also install LaTeX:"
    echo "  Mac:     brew install --cask mactex"
    echo "  Linux:   sudo apt-get install texlive-full"
    echo "  Windows: choco install miktex"
    exit 1
fi

# Create pdfs directory
mkdir -p pdfs

echo "Generating individual PDFs..."
echo ""

# Array of important guides to generate
guides=(
  "QUICKSTART:Quick Start Guide"
  "COMPLETE_SETUP_GUIDE:Complete Setup Guide"
  "SOL_QUICK_SETUP:Sol TestingGrounds Quick Setup"
  "SOL_TESTINGGROUNDS_README:Sol TestingGrounds Overview"
  "SOL_TESTINGGROUNDS_IMPLEMENTATION_GUIDE:Sol Implementation Guide"
  "SHIP_INTERIOR_GENERATION_GUIDE:Ship Interior Generation"
  "SHIP_SYSTEM_SETUP:Ship System Setup"
  "SPACE_SCENE_SETUP:Space Scene Setup"
  "SPACE_SCENE_GENERATION_WITH_STORE_ASSETS:Space Scene Generation"
  "SKYBOX_MATERIAL_GUIDE:Skybox Material Guide"
  "CAMERA_AND_VISUAL_IMPROVEMENTS:Camera and Visual Improvements"
  "guides/MODULAR_SHIP_SYSTEM_GUIDE:Modular Ship System"
  "guides/AI_SYSTEM_GUIDE:AI System Guide"
  "guides/CORE_GAMEPLAY_MECHANICS:Core Gameplay Mechanics"
  "guides/GAMEPLAY_FEATURES:Gameplay Features"
  "guides/QUEST_SYSTEM_GUIDE:Quest System"
  "guides/PROCEDURAL_GENERATION_GUIDE:Procedural Generation"
  "architecture/ARCHITECTURE:System Architecture"
  "architecture/ARCHITECTURE_DIAGRAM:Architecture Diagrams"
  "migration/UE5_MIGRATION_CHECKLIST:UE5 Migration Checklist"
  "migration/GETTING_STARTED_UE5:Getting Started with UE5"
  "migration/CONVERSION_GUIDE:C# to UE5 Conversion Guide"
)

# Generate each PDF
for guide_entry in "${guides[@]}"; do
  IFS=':' read -r guide title <<< "$guide_entry"
  input_file="docs/${guide}.md"
  output_file="pdfs/$(basename ${guide}).pdf"
  
  if [ -f "$input_file" ]; then
    echo "  Generating: $(basename ${guide}).pdf"
    pandoc "$input_file" \
      -o "$output_file" \
      --pdf-engine=xelatex \
      --toc \
      --toc-depth=3 \
      --number-sections \
      -V geometry:margin=1in \
      -V fontsize=11pt \
      -V documentclass=article \
      -V colorlinks=true \
      -V linkcolor=blue \
      -V urlcolor=blue \
      --highlight-style=tango \
      --metadata title="SubspaceUE: ${title}" \
      --metadata author="SubspaceUE Team" \
      --metadata date="$(date +%Y-%m-%d)" \
      2>/dev/null || echo "    Warning: Could not generate $(basename ${guide}).pdf"
  else
    echo "  Skipping (not found): $input_file"
  fi
done

echo ""
echo "================================================"
echo " PDF generation complete!"
echo " PDFs are in the 'pdfs/' directory"
echo "================================================"
echo ""
echo "Generated files:"
ls -lh pdfs/*.pdf 2>/dev/null | awk '{print "  " $9 " (" $5 ")"}'
echo ""
