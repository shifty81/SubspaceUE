# 📚 Documentation Guide

Welcome to the SubspaceUE documentation! This guide explains how to access and use the documentation in multiple formats.

## 🌟 Quick Access

### 🌐 Interactive Website (Recommended)

The easiest way to browse documentation:

**View Online:**
- GitHub Pages: https://shifty81.github.io/SubspaceUE/ (once deployed)

**View Locally:**
```bash
# Start local server
./serve-docs.sh

# Open in browser
http://localhost:3000
```

### 📄 PDF Downloads

Generate PDFs for offline reading:

```bash
# Generate all PDFs
./generate-pdfs.sh

# PDFs will be in pdfs/ folder
```

### 📝 Markdown Files

All documentation is in `docs/` folder as markdown files. You can:
- Read on GitHub
- Open in VS Code (Ctrl+Shift+V for preview)
- Open in any text editor

---

## 📖 Documentation Overview

### Total Documentation

- **118+ Guides** across all categories
- **500,000+ words** of comprehensive documentation
- **50+ images** and diagrams
- **Multiple formats:** Web, Markdown, PDF

### Categories

```
docs/
├── 📁 architecture/     (3 guides)   - System design and architecture
├── 📁 guides/          (73 guides)  - Feature guides and tutorials
├── 📁 implementation/  (22 guides)  - Implementation summaries
├── 📁 migration/       (8 guides)   - UE5 migration documentation
├── 📁 reference/       (9 guides)   - Reference and status docs
├── 📁 research/        (6 guides)   - Research and planning
└── 📁 images/          (50+ files)  - Screenshots and diagrams
```

---

## 🚀 Quick Start

### For First-Time Users

1. **Read the Complete Setup Guide**
   - [docs/COMPLETE_SETUP_GUIDE.md](docs/COMPLETE_SETUP_GUIDE.md)
   - Walks through entire project setup from scratch
   - Includes prerequisites, installation, and verification

2. **Start the Documentation Server**
   ```bash
   ./serve-docs.sh
   ```

3. **Open in Browser**
   - Go to http://localhost:3000
   - Use search to find what you need
   - Follow the navigation sidebar

### For Visual Learners

The documentation is designed for visual learners with:

✨ **Enhanced Features:**
- 📊 Interactive diagrams (Mermaid.js)
- 🖼️ Screenshots and step-by-step visuals
- 🎨 Color-coded sections and callouts
- 🔍 Full-text search
- 🗺️ Easy navigation with sidebar
- 📱 Responsive design (works on mobile)

---

## 📚 Learning Paths

### Path 1: Absolute Beginner
**Time: ~2-4 hours**

1. [Complete Setup Guide](docs/COMPLETE_SETUP_GUIDE.md) - Set up everything
2. [Quick Start](docs/QUICKSTART.md) - Get running quickly
3. [Sol Quick Setup](docs/SOL_QUICK_SETUP.md) - Build first space sector
4. [Testing Guide](docs/TESTING_GUIDE.md) - Verify it works

### Path 2: Visual Artist/Designer
**Time: ~4-6 hours**

1. [Space Scene Setup](docs/SPACE_SCENE_SETUP.md) - Create beautiful space
2. [Space Scene Generation](docs/SPACE_SCENE_GENERATION_WITH_STORE_ASSETS.md) - Professional scenes
3. [Skybox Material Guide](docs/SKYBOX_MATERIAL_GUIDE.md) - Custom skyboxes
4. [Camera & Visual Improvements](docs/CAMERA_AND_VISUAL_IMPROVEMENTS.md) - Camera setup

### Path 3: Technical Artist/Builder
**Time: ~7-10 hours**

1. [Ship System Setup](docs/SHIP_SYSTEM_SETUP.md) - Set up ship system
2. [Modular Ship System](docs/guides/MODULAR_SHIP_SYSTEM_GUIDE.md) - Build modular ships
3. [Ship Interior Generation](docs/SHIP_INTERIOR_GENERATION_GUIDE.md) - Add interiors
4. [Procedural Generation](docs/guides/PROCEDURAL_GENERATION_GUIDE.md) - Procedural systems

### Path 4: Programmer/Developer
**Time: ~8-12 hours**

1. [System Architecture](docs/architecture/ARCHITECTURE.md) - Understand the architecture
2. [UE5 Migration Checklist](docs/migration/UE5_MIGRATION_CHECKLIST.md) - Migration guide
3. [Conversion Guide](docs/migration/CONVERSION_GUIDE.md) - C# to UE5
4. [Contributing Guide](docs/CONTRIBUTING.md) - How to contribute

---

## 🛠️ Documentation Tools

### Serving Documentation Locally

**Linux/Mac:**
```bash
chmod +x serve-docs.sh
./serve-docs.sh
```

**Windows:**
```batch
serve-docs.bat
```

**Custom Port:**
```bash
./serve-docs.sh 8080
```

### Generating PDFs

**Prerequisites:**
- Pandoc: https://pandoc.org/
- LaTeX (MiKTeX/TeXLive): For PDF rendering

**Generate:**
```bash
chmod +x generate-pdfs.sh
./generate-pdfs.sh
```

**Output:**
- Individual PDFs in `pdfs/` folder
- One PDF per guide
- Named same as markdown file

### Updating Documentation

**Add New Guide:**
1. Create `.md` file in appropriate `docs/` subfolder
2. Add entry to `docs/_sidebar.md`
3. Add entry to `docs/DOCUMENTATION_INDEX.md`
4. Commit and push

**Update Existing Guide:**
1. Edit the `.md` file
2. Commit and push
3. Documentation website updates automatically

---

## 📊 Documentation Features

### Interactive Website Features

✨ **Built with Docsify** - Modern, lightweight documentation framework

**Features:**
- 🔍 **Full-Text Search** - Find anything instantly
- 📱 **Responsive** - Works on any device
- 🎨 **Beautiful UI** - Modern, clean design
- 📊 **Mermaid Diagrams** - Interactive flowcharts
- 🔗 **Deep Linking** - Share links to specific sections
- 🌙 **Dark Mode Ready** - Easy on the eyes
- ⚡ **Fast** - No build step, instant load
- 🔌 **Plugins** - Search, zoom, copy-code, and more

### PDF Features

**Professional PDFs:**
- 📄 Table of contents
- 🔢 Page numbers
- 🔗 Internal links
- 🎨 Syntax highlighting
- 📊 Tables and diagrams (where supported)
- 📏 Professional formatting

---

## 📖 Documentation Structure

### Master Index

See [docs/DOCUMENTATION_INDEX.md](docs/DOCUMENTATION_INDEX.md) for complete index of all 118+ guides.

### Key Documents

**🚀 Getting Started:**
- [Complete Setup Guide](docs/COMPLETE_SETUP_GUIDE.md) - **START HERE**
- [Quick Start](docs/QUICKSTART.md)
- [Sol Quick Setup](docs/SOL_QUICK_SETUP.md)

**🎮 Core Systems:**
- [Ship System Setup](docs/SHIP_SYSTEM_SETUP.md)
- [Space Scene Setup](docs/SPACE_SCENE_SETUP.md)
- [Modular Ship System](docs/guides/MODULAR_SHIP_SYSTEM_GUIDE.md)
- [AI System Guide](docs/guides/AI_SYSTEM_GUIDE.md)

**🏗️ Architecture:**
- [System Architecture](docs/architecture/ARCHITECTURE.md)
- [Architecture Diagrams](docs/architecture/ARCHITECTURE_DIAGRAM.md)

**🔄 UE5 Migration:**
- [UE5 Migration Checklist](docs/migration/UE5_MIGRATION_CHECKLIST.md)
- [Getting Started UE5](docs/migration/GETTING_STARTED_UE5.md)
- [Conversion Guide](docs/migration/CONVERSION_GUIDE.md)

---

## 🎓 For Contributors

### Documentation Standards

When adding or updating documentation:

**File Naming:**
- Root-level: `UPPERCASE_WITH_UNDERSCORES.md`
- Guides: `Title_Case_Guide.md`
- Be descriptive and consistent

**Content Structure:**
```markdown
# Title

> **🎯 Goal:** What this accomplishes  
> **⏱️ Time:** Estimated time  
> **📚 Prerequisites:** What's needed

## Table of Contents
1. [Section 1](#section-1)

## Section 1
Content...
```

**Best Practices:**
- Use clear, simple language
- Include visual aids (screenshots, diagrams)
- Provide step-by-step instructions
- Test all examples
- Add code blocks with language specified
- Use emojis sparingly for visual markers

### Adding Diagrams

Use Mermaid for diagrams:

```markdown
​```mermaid
graph LR
    A[Start] --> B[Process]
    B --> C[End]
​```
```

### Testing Changes

Before committing:

1. **Test locally:**
   ```bash
   ./serve-docs.sh
   # Verify changes at http://localhost:3000
   ```

2. **Check links:**
   - Verify all internal links work
   - Test external links

3. **Verify formatting:**
   - Check markdown renders correctly
   - Verify code blocks have proper syntax
   - Ensure images load

---

## 🚀 Deployment

### GitHub Pages

Documentation automatically deploys to GitHub Pages when you push to the main branch.

**Setup (One-Time):**
1. Go to repository Settings → Pages
2. Source: Deploy from branch
3. Branch: `main`
4. Folder: `/docs`
5. Save

**Access:**
- URL: https://shifty81.github.io/SubspaceUE/
- Updates automatically on push

### Custom Domain (Optional)

Add `docs/CNAME` file with your domain:
```
docs.subspaceue.com
```

Configure DNS CNAME record pointing to: `shifty81.github.io`

---

## 🔍 Search Tips

The documentation search is powerful. Try these queries:

- **"ship building"** - Find ship construction guides
- **"setup"** - Find setup and configuration guides
- **"UE5"** - Find Unreal Engine 5 specific docs
- **"troubleshooting"** - Find problem solutions
- **"modular"** - Find modular ship system docs

---

## 📞 Getting Help

**Documentation Issues:**
- Found a typo? Open an issue or PR
- Missing information? Request in issues
- Unclear instructions? Let us know

**Technical Support:**
- GitHub Issues: Report bugs
- GitHub Discussions: Ask questions
- [Sol Troubleshooting](docs/SOL_TESTINGGROUNDS_TROUBLESHOOTING.md) - Common issues

---

## 📊 Statistics

- **Total Guides:** 118+
- **Categories:** 7 (Architecture, Guides, Implementation, Migration, Reference, Research, Images)
- **Total Words:** 500,000+
- **Images:** 50+ screenshots and diagrams
- **Formats:** Web, Markdown, PDF
- **Last Updated:** January 2026

---

## 🤝 Contributing

Help improve documentation:

**Ways to Contribute:**
- Fix typos or unclear explanations
- Add screenshots or diagrams
- Create video tutorials
- Write new guides
- Translate to other languages

**Process:**
1. Fork the repository
2. Make changes in `docs/` folder
3. Test locally with `./serve-docs.sh`
4. Submit pull request

See [CONTRIBUTING.md](docs/CONTRIBUTING.md) for details.

---

## 📚 External Resources

- **Docsify:** https://docsify.js.org/
- **Markdown Guide:** https://www.markdownguide.org/
- **Pandoc:** https://pandoc.org/
- **Mermaid Diagrams:** https://mermaid-js.github.io/
- **Unreal Engine Docs:** https://docs.unrealengine.com/

---

## 🎉 Enjoy the Documentation!

We've put a lot of effort into making this documentation comprehensive, visual, and easy to navigate. Whether you're a beginner or an expert, there's something here for you.

**Happy Learning! 🚀**

---

**Quick Links:**
- 🏠 [Documentation Home](docs/README.md)
- 📋 [Complete Index](docs/DOCUMENTATION_INDEX.md)
- 🚀 [Quick Start](docs/QUICKSTART.md)
- 🛠️ [Complete Setup](docs/COMPLETE_SETUP_GUIDE.md)
- 🤝 [Contributing](docs/CONTRIBUTING.md)
