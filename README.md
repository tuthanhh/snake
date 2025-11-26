# Snake (Ncurses)

A minimalist terminal snake clone built with CMake, vcpkg, and ncurses. A lightweight state machine (menu → game → pause) keeps gameplay, logging, and infrastructure isolated.

This started as a "between school assignments" hobby project, and I still treat it as a sandbox for experimenting with ncurses rendering and clean architecture patterns.
## Features
- **Ncurses UI** – full-screen play area with scaled rendering, keyboard input (arrow keys, ESC, Enter).
- **State-driven flow** – menu, gameplay, and pause states managed by an `Application` stack for clean transitions.
- **World simulation layer** – `World`, `Snake`, and `Food` modules track movement, collisions, scoring, and boundary drawing.
- **Configurable logging** – singleton logger that writes diagnostics to `application.log` under the build directory.
- **CMake + vcpkg toolchain** – reproducible builds with manifest-based dependency resolution (currently ncurses).

## Project Structure
```
.
├── CMakeLists.txt          # Root build entry point
├── vcpkg.json              # Manifest specifying ncurses dependency
├── build/                  # Generated build tree (ignored in git)
└── src/
	├── CMakeLists.txt      # Adds subdirectories and the main executable
	├── application.cpp/.h  # App singleton and main loop
	├── main.cpp            # Program entry (initializes ncurses)
	├── state/
	│   ├── state.h         # Base state + Menu/Pause/Game definitions
	│   ├── menu-state.cpp
	│   ├── game-state.cpp
	│   └── pause-state.cpp
	├── game/
	│   ├── CMakeLists.txt  # Builds `game_world` static library
	│   ├── world.*         # Coordinates updates/rendering/boundaries
	│   ├── snake.*         # Movement, input handling, growth
	│   └── food.*          # Spawn/render logic
	└── log/
		├── CMakeLists.txt  # Builds `log` static library
		└── log.*           # Simple file logger
```

## Building & Running
Prerequisites:
- CMake ≥ 3.15
- A C++17 compiler
- vcpkg (handled automatically via presets) and ncurses development headers

Steps:
```bash
# Configure with the default preset (uses vcpkg toolchain)
cmake --preset default

# Build the executable
cmake --build build

# Run the game from the workspace root
./build/main
```

Controls:
- Arrow keys – move the snake
- Enter – confirm menu items
- ESC – back/quit

- P – toggle pause (or choose the pause menu option)

Logs land in `build/application.log` so the source tree stays clean—remove the file between runs if you want a fresh trace.
