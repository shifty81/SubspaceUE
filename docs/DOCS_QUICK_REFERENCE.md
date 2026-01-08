# 📚 Documentation Quick Reference

> **Quick access to all documentation resources**

## 🚀 Getting Started

### First Time Setup
```bash
# 1. Read the complete setup guide
cat docs/COMPLETE_SETUP_GUIDE.md  # or open in browser

# 2. Start documentation server
./serve-docs.sh

# 3. Open http://localhost:3000 in browser
```

---

## 📖 Essential Guides

| Guide | Purpose | Time | Link |
|-------|---------|------|------|
| **Complete Setup** | Install everything from scratch | 2-4 hrs | [docs/COMPLETE_SETUP_GUIDE.md](docs/COMPLETE_SETUP_GUIDE.md) |
| **Quick Start** | Fast track setup | 30 min | [docs/QUICKSTART.md](docs/QUICKSTART.md) |
| **Visual Learning** | For visual learners | Self-paced | [docs/VISUAL_LEARNING_GUIDE.md](docs/VISUAL_LEARNING_GUIDE.md) |
| **Ship System** | Build modular ships | 1-2 hrs | [docs/SHIP_SYSTEM_SETUP.md](docs/SHIP_SYSTEM_SETUP.md) |
| **Space Scene** | Create space environments | 2-3 hrs | [docs/SPACE_SCENE_SETUP.md](docs/SPACE_SCENE_SETUP.md) |
| **AI System** | Configure AI and NPCs | 2-3 hrs | [docs/AI_SYSTEM_SETUP.md](docs/AI_SYSTEM_SETUP.md) |

---

## 🛠️ Documentation Tools

### View Documentation

```bash
# Interactive website (recommended)
./serve-docs.sh
# Open http://localhost:3000

# Windows
serve-docs.bat
```

### Generate PDFs

```bash
# Requires: pandoc, texlive/miktex
./generate-pdfs.sh

# PDFs will be in pdfs/ folder
```

### Find Documentation

```bash
# All documentation is in docs/ folder
cd docs/

# Main categories:
docs/architecture/    # System design (3 guides)
docs/guides/          # How-to guides (73 guides)
docs/implementation/  # Status docs (22 guides)
docs/migration/       # UE5 migration (8 guides)
docs/reference/       # Reference docs (9 guides)
docs/research/        # Research docs (6 guides)
```

---

## 🗺️ Learning Paths

### Path 1: Complete Beginner
1. Complete Setup Guide → 2-4 hrs
2. Quick Start → 30 min
3. Visual Learning Guide → Self-paced
4. Choose your interest (ship building / scene creation / AI)

### Path 2: Visual Artist
1. Space Scene Setup → 2-3 hrs
2. Skybox Material Guide → 1 hr
3. Camera & Visual Improvements → 45 min

### Path 3: Ship Builder
1. Ship System Setup → 1-2 hrs
2. Modular Ship System Guide → 2 hrs
3. Ship Interior Generation → 3 hrs

### Path 4: Programmer
1. System Architecture → 2 hrs
2. UE5 Migration Checklist → 1 hr
3. AI System Setup → 2-3 hrs
4. Contributing Guide → 30 min

---

## 📊 Statistics

- **Total Guides:** 127 markdown files
- **Total Size:** 4.6 MB
- **Total Words:** 575,000+
- **New Content:** 75,000 words (6 new guides)
- **Diagrams:** 20+ Mermaid flowcharts
- **Categories:** 7 main categories

---

## 🌐 Access Methods

### 1. Interactive Website
- **Local:** http://localhost:3000 (via ./serve-docs.sh)
- **Online:** https://shifty81.github.io/SubspaceUE/ (after deployment)
- **Features:** Search, navigation, diagrams

### 2. PDF Documents
- **Generate:** ./generate-pdfs.sh
- **Location:** pdfs/ folder
- **Count:** 20+ individual PDFs

### 3. Markdown Files
- **Location:** docs/ folder
- **View:** GitHub, VS Code, any text editor
- **Format:** Standard markdown

---

## 🎯 By Role

### I'm a **Visual Learner**
→ Start with [Visual Learning Guide](docs/VISUAL_LEARNING_GUIDE.md)  
→ Use [Interactive Website](http://localhost:3000) for diagrams  
→ Follow flowcharts and visual navigation maps

### I'm an **Artist/Designer**
→ Start with [Space Scene Setup](docs/SPACE_SCENE_SETUP.md)  
→ Then [Camera & Visual Improvements](docs/CAMERA_AND_VISUAL_IMPROVEMENTS.md)  
→ Explore [Skybox Material Guide](docs/SKYBOX_MATERIAL_GUIDE.md)

### I'm a **Ship Builder**
→ Start with [Ship System Setup](docs/SHIP_SYSTEM_SETUP.md)  
→ Then [Modular Ship System](docs/guides/MODULAR_SHIP_SYSTEM_GUIDE.md)  
→ Add [Ship Interiors](docs/SHIP_INTERIOR_GENERATION_GUIDE.md)

### I'm a **Programmer**
→ Start with [System Architecture](docs/architecture/ARCHITECTURE.md)  
→ Review [UE5 Migration](docs/migration/UE5_MIGRATION_CHECKLIST.md)  
→ Read [Contributing Guide](docs/CONTRIBUTING.md)

### I'm **Completely New**
→ Start with [Complete Setup Guide](docs/COMPLETE_SETUP_GUIDE.md)  
→ Then [Quick Start](docs/QUICKSTART.md)  
→ Choose your path from above

---

## 🔍 Quick Search

### By Topic

| Topic | Key Guides |
|-------|------------|
| **Setup** | Complete Setup, Quick Start, Prerequisites |
| **Ships** | Ship System Setup, Modular Ship System, Ship Interior |
| **Space** | Space Scene Setup, Skybox Guide, Camera Guide |
| **AI** | AI System Setup, AI System Guide |
| **Code** | Architecture, Migration, Contributing |
| **Visual** | Visual Learning Guide, All setup guides have diagrams |

### By Time Available

| Time | What You Can Do |
|------|-----------------|
| **30 min** | Quick Start, browse Visual Learning Guide |
| **1-2 hrs** | Ship System Setup, complete a single system |
| **2-4 hrs** | Complete Setup from scratch, Space Scene Setup |
| **4+ hrs** | Multiple systems, full learning path |
| **1 day** | Complete beginner → proficient in one area |
| **1 week** | Master most systems, contribute to project |

---

## 💡 Pro Tips

1. **Start Documentation Server First**
   ```bash
   ./serve-docs.sh
   ```
   Then read in browser for best experience

2. **Generate PDFs for Offline**
   ```bash
   ./generate-pdfs.sh
   ```
   Keep PDFs for reference when coding

3. **Use Search Feature**
   - Press `/` in interactive docs
   - Type your search query
   - Instant results across all 127 guides

4. **Follow Learning Paths**
   - Don't jump around randomly
   - Follow suggested order for your role
   - Each guide builds on previous

5. **Bookmark Favorites**
   - Use browser bookmarks for frequent guides
   - Or keep PDFs handy

---

## 📞 Get Help

- **Troubleshooting:** Each setup guide has troubleshooting section
- **Common Issues:** [Sol Troubleshooting](docs/SOL_TESTINGGROUNDS_TROUBLESHOOTING.md)
- **GitHub Issues:** Report bugs or ask questions
- **Documentation Issues:** [Contributing Guide](docs/CONTRIBUTING.md)

---

## 🎉 You're Ready!

Pick your starting point above and dive in. The documentation will guide you through everything!

**Happy Building! 🚀**

---

**Quick Links:**  
[🏠 Docs Home](docs/README.md) | [📋 Full Index](docs/DOCUMENTATION_INDEX.md) | [🚀 Complete Setup](docs/COMPLETE_SETUP_GUIDE.md)
