# JumpGame

A cross-platform game built with SFML 3.0 and C++17.

## Description

JumpGame is a game featuring multiple game modes, menus, sound effects, and visual effects. The project is built using SFML for graphics and audio rendering.

## Prerequisites

### Dependencies
- CMake 3.16 or higher
- C++17 compatible compiler
  - Windows: Visual Studio 2019 or newer, MinGW-w64, or Clang
  - Linux: GCC 7+ or Clang 5+
- SFML 3.0 (Graphics and Audio modules)

### Installing SFML 3.0

#### Windows
1. Download SFML 3.0 from the [official website](https://www.sfml-dev.org/download.php)
2. Extract to a location (e.g., `C:\SFML-3.0`)
3. Set the SFML_DIR environment variable or specify it during CMake configuration:
   ```cmd
   cmake -B build -DSFML_DIR="C:/SFML-3.0/lib/cmake/SFML"
   ```

#### Linux
Install SFML 3.0 using your package manager:

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

**Arch Linux:**
```bash
sudo pacman -S sfml
```

**Fedora:**
```bash
sudo dnf install SFML-devel
```

Or build from source if your distribution doesn't have SFML 3.0:
```bash
git clone https://github.com/SFML/SFML.git
cd SFML
git checkout 3.0.0
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build build
sudo cmake --install build
```

## Building the Project

### Windows

#### Using Visual Studio
```cmd
cmake -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
```

#### Using MinGW
```cmd
cmake -B build -G "MinGW Makefiles"
cmake --build build
```

### Linux
```bash
cmake -B build
cmake --build build
```

## Running the Game

After building, the executable will be located in the `build` directory along with the `data` folder (automatically copied during build).

### Windows
```cmd
cd build
JumpGame.exe
```

### Linux
```bash
cd build
./JumpGame
```

## Project Structure

```
JumpGame/
├── CMakeLists.txt      # CMake build configuration
├── src/                # Source code files
│   ├── main.cpp        # Entry point
│   ├── game.cpp/h      # Main game logic
│   ├── GameObjects.cpp/h
│   ├── UIObjects.cpp
│   ├── mainmenu.h
│   ├── pause.h
│   ├── gameover.h
│   ├── instructions.h
│   ├── GameSelect.cpp
│   ├── fireworks.h
│   ├── resourceManager.cpp/h
│   ├── settingsLoader.cpp/h
│   ├── globals.cpp
│   └── json.hpp        # JSON library
└── data/               # Game assets
    ├── fonts/          # Font files
    ├── img/            # Images and sprites
    ├── sound/          # Audio files
    └── settings.json   # Game settings

```

## Configuration

Game settings can be modified in `data/settings.json`.

## Troubleshooting

### SFML Not Found
If CMake cannot find SFML, specify the SFML directory manually:
```bash
cmake -B build -DSFML_DIR="/path/to/SFML/lib/cmake/SFML"
```

### Missing DLLs on Windows
Ensure SFML DLLs are in the same directory as the executable or in your system PATH.

## License

[Add your license information here]

## Author

[Add your information here]
