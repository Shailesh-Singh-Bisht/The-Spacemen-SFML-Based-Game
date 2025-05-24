# 🚀 The Spacemen

**The Spacemen** is a retro-style 2D vertical space shooter game built using **C++17** and **SFML 2.5.1**. Designed for both fun and nostalgia, it features animated enemies, laser combat, a simple narrative, and audio-visual immersion — all packed into a ReactOS-compatible binary.

-----

## 🎮 Features

  - 🚀 Move left/right and shoot upward.
  - 👾 Randomly spawning enemies.
  - 🔫 Player/enemy laser collisions with sound.
  - ❤️ Health-based survival system.
  - 🧠 Intro story screens (5 slides) before the game begins.
  - 🎵 Background music and SFX for immersion.
  - 🏁 Win by killing 30 enemies, lose if HP hits zero.
  - 🔁 Automatic game restart after win/loss.
  - 🖼️ Executable with a custom icon.
  - 📦 Clean, modular codebase with CMake build system.

-----

## 🕹️ How to Run the Game

To play **The Spacemen** without building it yourself, simply:

1.  Go to the [Releases](https://www.google.com/search?q=https://github.com/yourusername/TheSpacemen/releases) section of the GitHub repository.
2.  Download the latest `.zip` archive.
3.  Extract the contents of the `.zip` file to a folder of your choice on your computer.
4.  Navigate into the extracted folder and run **TheSpacemen.exe**.

You're all set to defend the galaxy\!

-----

## 🧱 Build Instructions

### ✅ Prerequisites

Before you can build **The Spacemen**, make sure you have the following:

  - **C++17 compiler** (e.g., GCC via MinGW on Windows).
  - **CMake ≥ 3.13**.
  - **SFML 2.5.1 (32-bit)**.

Ensure SFML is installed at `C:/Libraries/SFML-2.5.1/` or adjust the path in `CMakeLists.txt` to match your installation.

### 🔧 Setup

```bash
git clone https://github.com/yourusername/TheSpacemen.git
cd TheSpacemen
mkdir build && cd build
cmake ..
cmake --build .
```

After successfully running these commands, you'll find the compiled executable in the `build/Release` or `build/Debug` directory, depending on your build configuration.
