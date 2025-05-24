# 🚀 The Spacemen
<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-4-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->

**The Spacemen** is a retro-style 2D vertical space shooter game built using **C++17** and **SFML 2.5.1**. Designed for both fun and nostalgia, it features animated enemies, laser combat, a simple narrative, and audio-visual immersion — all packed into a single exe.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![SFML 2.5.1](https://img.shields.io/badge/SFML-2.5.1-green.svg)](https://www.sfml-dev.org/)

---

## 📖 Table of Contents

- [Features](#-features)
- [How to Run the Game](#-how-to-run-the-game)
- [Build Instructions](#-build-instructions)
- [Game Controls](#-game-controls)
- [Project Structure](#-project-structure)
- [Contributing](#-contributing)
- [License](#-license)

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

---

## 🕹️ How to Run the Game

To play **The Spacemen** without building it yourself, simply:

1.  Go to the [Releases]() section of the GitHub repository.
2.  Download the latest `.zip` archive.
3.  Extract the contents of the `.zip` file to a folder of your choice on your computer.
4.  Navigate into the extracted folder and run **TheSpacemen.exe**.

You're all set to defend the galaxy\!

---

## 🧱 Build Instructions

### ✅ Prerequisites

Before you can build **The Spacemen**, make sure you have the following:

- **C++17 compiler** (e.g., GCC via MinGW on Windows).
- **CMake ≥ 3.13**.
- **SFML 2.5.1 (32-bit)**.

Ensure SFML is installed at `C:/Libraries/SFML-2.5.1/` or adjust the path in `CMakeLists.txt` to match your installation.

### 🔧 Setup

```bash
git clone https://github.com/Shailesh-Singh-Bisht/The-Spacemen-SFML-Based-Game
cd The-Spacemen-SFML-Based-Game
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

## 🎯 Game Controls

- **Left Arrow**: Move ship left
- **Right Arrow**: Move ship right
- **Space Bar**: Shoot laser

## 📁 Project Structure

```
assets/          # Game resources (images, audio, fonts)
├── audio/       # Sound effects and music
├── fonts/       # Game fonts
├── images/      # Sprites and backgrounds
└── UI/          # UI elements and backgrounds

include/         # Header files
src/            # Source files
```

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Commit your changes (`git commit -m 'Add some amazing feature'`)
5. Push to the branch (`git push origin feature/amazing-feature`)
6. Open a Pull Request

Please ensure your PR:

- Follows the existing code style
- Includes appropriate documentation
- Has meaningful commit messages

### Development Guidelines

- Follow C++17 best practices
- Use SFML's recommended patterns
- Document new functions and classes
- Add comments for complex logic
- Test your changes thoroughly

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- SFML team for their amazing library
- Contributors and supporters of the project
- Game art and sound creators (attribution in assets folder)

## 📬 Contact

For questions, suggestions, or issues, please:

- Open an issue in this repository
- Reach out through the discussions tab
- Check existing issues before creating new ones

## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tbody>
    <tr>
      <td align="center" valign="top" width="14.28%"><a href="https://shailesh-singh-bisht-portfolio.vercel.app/"><img src="https://avatars.githubusercontent.com/u/107263955?v=4?s=100" width="100px;" alt="Shailesh Singh Bisht"/><br /><sub><b>Shailesh Singh Bisht</b></sub></a><br /><a href="#design-Shailesh-Singh-Bisht" title="Design">🎨</a> <a href="#maintenance-Shailesh-Singh-Bisht" title="Maintenance">🚧</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/royalhub123"><img src="https://avatars.githubusercontent.com/u/168981505?v=4?s=100" width="100px;" alt="royalhub123"/><br /><sub><b>royalhub123</b></sub></a><br /><a href="https://github.com/Shailesh-Singh-Bisht/The-Spacemen-SFML-Based-Game/commits?author=royalhub123" title="Code">💻</a> <a href="https://github.com/Shailesh-Singh-Bisht/The-Spacemen-SFML-Based-Game/commits?author=royalhub123" title="Tests">⚠️</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/Akhilnautiyal5"><img src="https://avatars.githubusercontent.com/u/113812781?v=4?s=100" width="100px;" alt="Akhil Nautiyal"/><br /><sub><b>Akhil Nautiyal</b></sub></a><br /><a href="https://github.com/Shailesh-Singh-Bisht/The-Spacemen-SFML-Based-Game/commits?author=Akhilnautiyal5" title="Code">💻</a> <a href="https://github.com/Shailesh-Singh-Bisht/The-Spacemen-SFML-Based-Game/commits?author=Akhilnautiyal5" title="Tests">⚠️</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/Vivek-Pokhriyal"><img src="https://avatars.githubusercontent.com/u/202429019?v=4?s=100" width="100px;" alt="Vivek-Pokhriyal"/><br /><sub><b>Vivek-Pokhriyal</b></sub></a><br /><a href="https://github.com/Shailesh-Singh-Bisht/The-Spacemen-SFML-Based-Game/commits?author=Vivek-Pokhriyal" title="Code">💻</a> <a href="https://github.com/Shailesh-Singh-Bisht/The-Spacemen-SFML-Based-Game/commits?author=Vivek-Pokhriyal" title="Tests">⚠️</a></td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <td align="center" size="13px" colspan="7">
        <img src="https://raw.githubusercontent.com/all-contributors/all-contributors-cli/1b8533af435da9854653492b1327a23a4dbd0a10/assets/logo-small.svg">
          <a href="https://all-contributors.js.org/docs/en/bot/usage">Add your contributions</a>
        </img>
      </td>
    </tr>
  </tfoot>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!