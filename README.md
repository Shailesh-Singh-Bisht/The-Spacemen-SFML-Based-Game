# 🚀 The Spacemen

**The Spacemen** is a retro-style 2D vertical space shooter game built using **C++17** and **SFML 2.5.1**. Designed for both fun and nostalgia, it features animated enemies, laser combat, a coding-themed narrative, and audio-visual immersion — all packed into a ReactOS-compatible binary.

---

## 🎮 Features

- 🚀 Move left/right and shoot upward
- 👾 Randomly spawning enemies with animated sprites
- 🔫 Player/enemy laser collisions with sound
- ❤️ Health-based survival system
- 🧠 Intro story screens (5 slides) before the game begins
- 🎵 Background music and SFX for immersion
- 🏁 Win by killing 30 enemies, lose if HP hits zero
- 🔁 Automatic game restart after win/loss
- 🖼️ Executable with a custom icon
- 📦 Clean, modular codebase with CMake build system

---

## 🧱 Build Instructions

### ✅ Prerequisites

- **C++17 compiler** (e.g. GCC via MinGW on Windows)
- **CMake ≥ 3.13**
- **SFML 2.5.1 (32-bit)**

Ensure SFML is installed at `C:/Libraries/SFML-2.5.1/` or adjust the path in `CMakeLists.txt`.

### 🔧 Setup

```bash
git clone https://github.com/yourusername/TheSpacemen.git
cd TheSpacemen
mkdir build && cd build
cmake ..
cmake --build .
