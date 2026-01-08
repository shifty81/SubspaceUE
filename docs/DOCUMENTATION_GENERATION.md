# Documentation Setup and Generation Guide

> **🎯 Goal:** Set up and generate documentation in multiple formats  
> **⏱️ Time Required:** 30 minutes  
> **📚 Prerequisites:** Node.js or Python installed

---

## 📋 Table of Contents

1. [Viewing Documentation](#viewing-documentation)
2. [Running Local Documentation Server](#running-local-documentation-server)
3. [Generating PDF Documentation](#generating-pdf-documentation)
4. [Deploying to GitHub Pages](#deploying-to-github-pages)
5. [Maintaining Documentation](#maintaining-documentation)

---

## 🌐 Viewing Documentation

### Method 1: Interactive Website (Recommended)

The documentation is available as an interactive website with search, navigation, and diagrams.

#### View Online (After GitHub Pages Setup)
Visit: `https://shifty81.github.io/SubspaceUE/`

#### View Locally

1. **Navigate to docs folder:**
   ```bash
   cd /path/to/SubspaceUE/docs
   ```

2. **Start a simple HTTP server:**

   **Using Python:**
   ```bash
   # Python 3
   python -m http.server 3000
   
   # Python 2
   python -m SimpleHTTPServer 3000
   ```

   **Using Node.js:**
   ```bash
   # Install http-server globally (one time)
   npm install -g http-server
   
   # Run server
   http-server -p 3000
   ```

   **Using PHP:**
   ```bash
   php -S localhost:3000
   ```

3. **Open in browser:**
   - Navigate to: `http://localhost:3000`
   - Documentation site loads automatically

✅ **Success:** You see the documentation homepage with navigation

### Method 2: Read Markdown Files Directly

All documentation is available as markdown (.md) files:

1. **In VS Code:**
   - Open SubspaceUE folder in VS Code
   - Navigate to `docs/` folder
   - Click any .md file
   - Press `Ctrl+Shift+V` for preview

2. **In GitHub:**
   - Browse to https://github.com/shifty81/SubspaceUE
   - Navigate to `docs/` folder
   - Click any .md file to read

3. **In Text Editor:**
   - Open any .md file in your favorite text editor
   - Markdown is human-readable even without rendering

---

## 🚀 Running Local Documentation Server

For the best experience, run the documentation as a website locally.

### Quick Start Script

Save this as `serve-docs.sh` (Linux/Mac) or `serve-docs.bat` (Windows) in the project root:

**serve-docs.sh:**
```bash
#!/bin/bash
cd docs
echo "Starting documentation server..."
echo "Documentation will be available at: http://localhost:3000"
echo "Press Ctrl+C to stop"
python3 -m http.server 3000
```

**serve-docs.bat:**
```batch
@echo off
cd docs
echo Starting documentation server...
echo Documentation will be available at: http://localhost:3000
echo Press Ctrl+C to stop
python -m http.server 3000
```

Make executable (Linux/Mac):
```bash
chmod +x serve-docs.sh
./serve-docs.sh
```

Run (Windows):
```batch
serve-docs.bat
```

### Using npm (Alternative)

Create a `package.json` in the docs folder:

```json
{
  "name": "subspaceue-docs",
  "version": "1.0.0",
  "scripts": {
    "serve": "http-server -p 3000 -o",
    "serve:watch": "http-server -p 3000 -o -c-1"
  },
  "devDependencies": {
    "http-server": "^14.1.1"
  }
}
```

Install and run:
```bash
cd docs
npm install
npm run serve
```

---

## 📄 Generating PDF Documentation

### Prerequisites

Install Pandoc and LaTeX:

**Windows:**
```powershell
# Using Chocolatey
choco install pandoc
choco install miktex

# Or download installers:
# Pandoc: https://pandoc.org/installing.html
# MiKTeX: https://miktex.org/download
```

**Mac:**
```bash
# Using Homebrew
brew install pandoc
brew install --cask mactex
```

**Linux:**
```bash
# Ubuntu/Debian
sudo apt-get install pandoc
sudo apt-get install texlive-full

# Fedora
sudo dnf install pandoc
sudo dnf install texlive-scheme-full
```

### Generate Individual PDFs

Create a script `generate-pdfs.sh`:

```bash
#!/bin/bash

# Create pdfs directory
mkdir -p pdfs

echo "Generating PDFs from markdown files..."

# Array of important guides
guides=(
  "QUICKSTART"
  "COMPLETE_SETUP_GUIDE"
  "SOL_QUICK_SETUP"
  "SOL_TESTINGGROUNDS_IMPLEMENTATION_GUIDE"
  "SHIP_INTERIOR_GENERATION_GUIDE"
  "SHIP_SYSTEM_SETUP"
  "SPACE_SCENE_SETUP"
  "guides/MODULAR_SHIP_SYSTEM_GUIDE"
  "guides/AI_SYSTEM_GUIDE"
  "architecture/ARCHITECTURE"
  "migration/UE5_MIGRATION_CHECKLIST"
)

# Generate each PDF
for guide in "${guides[@]}"; do
  input_file="docs/${guide}.md"
  output_file="pdfs/$(basename ${guide}).pdf"
  
  if [ -f "$input_file" ]; then
    echo "Generating: $output_file"
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
      --metadata title="SubspaceUE: $(basename ${guide})"
  else
    echo "Skipping (not found): $input_file"
  fi
done

echo "PDF generation complete! PDFs are in the 'pdfs/' directory."
```

Make executable and run:
```bash
chmod +x generate-pdfs.sh
./generate-pdfs.sh
```

### Generate Complete Documentation Book

Create `generate-complete-pdf.sh`:

```bash
#!/bin/bash

echo "Generating complete documentation PDF..."

mkdir -p pdfs

# Concatenate all documentation in order
pandoc \
  docs/README.md \
  docs/COMPLETE_SETUP_GUIDE.md \
  docs/QUICKSTART.md \
  docs/SHIP_SYSTEM_SETUP.md \
  docs/SPACE_SCENE_SETUP.md \
  docs/guides/MODULAR_SHIP_SYSTEM_GUIDE.md \
  docs/guides/AI_SYSTEM_GUIDE.md \
  docs/architecture/ARCHITECTURE.md \
  docs/migration/UE5_MIGRATION_CHECKLIST.md \
  -o pdfs/SubspaceUE_Complete_Documentation.pdf \
  --pdf-engine=xelatex \
  --toc \
  --toc-depth=2 \
  --number-sections \
  -V geometry:margin=1in \
  -V fontsize=10pt \
  -V documentclass=book \
  -V colorlinks=true \
  -V linkcolor=blue \
  -V urlcolor=blue \
  -V papersize=letter \
  --highlight-style=tango \
  --metadata title="SubspaceUE: Complete Documentation" \
  --metadata author="SubspaceUE Team" \
  --metadata date="$(date +%Y-%m-%d)"

echo "Complete PDF generated: pdfs/SubspaceUE_Complete_Documentation.pdf"
```

Run:
```bash
chmod +x generate-complete-pdf.sh
./generate-complete-pdf.sh
```

### Windows PowerShell Version

Save as `generate-pdfs.ps1`:

```powershell
# Create pdfs directory
New-Item -ItemType Directory -Force -Path "pdfs"

Write-Host "Generating PDFs from markdown files..."

$guides = @(
  "QUICKSTART",
  "COMPLETE_SETUP_GUIDE",
  "SOL_QUICK_SETUP",
  "SHIP_SYSTEM_SETUP",
  "SPACE_SCENE_SETUP"
)

foreach ($guide in $guides) {
  $inputFile = "docs\$guide.md"
  $outputFile = "pdfs\$guide.pdf"
  
  if (Test-Path $inputFile) {
    Write-Host "Generating: $outputFile"
    pandoc $inputFile `
      -o $outputFile `
      --pdf-engine=xelatex `
      --toc `
      --toc-depth=3 `
      --number-sections `
      -V geometry:margin=1in `
      -V fontsize=11pt `
      -V documentclass=article `
      -V colorlinks=true `
      --highlight-style=tango `
      --metadata title="SubspaceUE: $guide"
  }
}

Write-Host "PDF generation complete!"
```

Run:
```powershell
.\generate-pdfs.ps1
```

---

## 🚀 Deploying to GitHub Pages

### One-Time Setup

1. **Enable GitHub Pages**
   - Go to repository settings on GitHub
   - Scroll to "Pages" section
   - Source: Deploy from branch
   - Branch: `main` or `master`
   - Folder: `/docs`
   - Click Save

2. **Wait for Deployment**
   - GitHub Actions will deploy automatically
   - Takes 1-2 minutes
   - Check Actions tab for progress

3. **Access Your Documentation**
   - URL: `https://shifty81.github.io/SubspaceUE/`
   - Bookmark this URL

✅ **Success:** Documentation is live on the web!

### Custom Domain (Optional)

If you have a custom domain:

1. **Add CNAME File**
   Create `docs/CNAME` with your domain:
   ```
   docs.subspaceue.com
   ```

2. **Configure DNS**
   Add CNAME record in your DNS provider:
   ```
   CNAME  docs  shifty81.github.io
   ```

3. **Wait for DNS Propagation**
   - Takes 1-24 hours
   - Check with: `dig docs.subspaceue.com`

### Update Documentation

To update live documentation:

1. **Make Changes**
   ```bash
   # Edit markdown files
   vi docs/some-guide.md
   ```

2. **Commit and Push**
   ```bash
   git add docs/
   git commit -m "Update documentation"
   git push
   ```

3. **Wait for Deploy**
   - GitHub Actions deploys automatically
   - Check Actions tab for progress
   - Live in 1-2 minutes

---

## 🔧 Maintaining Documentation

### Adding New Documentation

1. **Create New Markdown File**
   ```bash
   cd docs/guides
   touch MY_NEW_GUIDE.md
   ```

2. **Add Content**
   Use this template:
   ```markdown
   # Guide Title
   
   > **🎯 Goal:** What this guide accomplishes  
   > **⏱️ Time Required:** Estimated time  
   > **📚 Prerequisites:** What's needed first
   
   ## Table of Contents
   1. [Section 1](#section-1)
   2. [Section 2](#section-2)
   
   ## Section 1
   Content here...
   
   ## Section 2
   More content...
   ```

3. **Add to Sidebar**
   Edit `docs/_sidebar.md`:
   ```markdown
   * **Category Name**
     * [My New Guide](guides/MY_NEW_GUIDE.md)
   ```

4. **Add to Index**
   Edit `docs/DOCUMENTATION_INDEX.md` to include new guide

5. **Commit Changes**
   ```bash
   git add docs/
   git commit -m "Add new guide: MY_NEW_GUIDE"
   git push
   ```

### Adding Images

1. **Add Image File**
   ```bash
   cp screenshot.png docs/images/my-feature-screenshot.png
   ```

2. **Reference in Markdown**
   ```markdown
   ![Feature Screenshot](images/my-feature-screenshot.png)
   ```

3. **Optimize Images**
   - Use PNG for screenshots
   - Use JPEG for photos
   - Compress images (max 1MB each)
   - Resize to reasonable dimensions (1920px wide max)

### Adding Diagrams

Use Mermaid for diagrams:

```markdown
​```mermaid
graph LR
    A[Start] --> B[Process]
    B --> C[End]
​```
```

### Documentation Standards

Follow these conventions:

1. **File Naming**
   - Use UPPERCASE_WITH_UNDERSCORES.md for root-level docs
   - Use Title_Case.md for guides
   - Be descriptive

2. **Heading Levels**
   - # for title (one per file)
   - ## for main sections
   - ### for subsections
   - Don't skip levels

3. **Links**
   - Use relative paths: `[Link](../other/file.md)`
   - Test all links before committing

4. **Code Blocks**
   - Always specify language: \`\`\`bash, \`\`\`cpp, etc.
   - Add comments for clarity

5. **Emojis**
   - Use sparingly for visual markers
   - Common: 🎯 Goal, ⏱️ Time, 📚 Prerequisites, ✅ Success

---

## 🎓 Advanced Features

### Search Optimization

The Docsify search plugin indexes:
- All headings
- All content
- File names

To improve search:
- Use descriptive headings
- Include key terms in content
- Add aliases in metadata

### Custom Themes

To customize the documentation theme:

1. **Edit `docs/index.html`**
2. **Modify CSS in `<style>` section**
3. **Change Docsify theme link**:
   ```html
   <link rel="stylesheet" href="//cdn.jsdelivr.net/npm/docsify@4/lib/themes/dark.css">
   ```

Available themes:
- vue.css (default, light)
- dark.css
- buble.css
- pure.css

### Analytics (Optional)

Add Google Analytics:

1. **Get GA Tracking ID**
2. **Add to `docs/index.html`**:
   ```javascript
   window.$docsify = {
     // ... existing config
     ga: 'UA-XXXXXXXX-X',
   }
   ```

---

## 📚 Resources

- **Docsify Documentation:** https://docsify.js.org/
- **Pandoc Manual:** https://pandoc.org/MANUAL.html
- **GitHub Pages:** https://docs.github.com/en/pages
- **Mermaid Diagrams:** https://mermaid-js.github.io/

---

**🎉 Your documentation system is fully configured! 📚**

---

**Navigation:**  
[🏠 Home](README.md) | [📋 Index](DOCUMENTATION_INDEX.md)
