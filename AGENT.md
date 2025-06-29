# AGENT.md - Eclipse-9 Procedural Terrain Generation Game

## Build/Test Commands
- **Build**: `cd build && cmake .. && make` (or use ninja if available)
- **Run**: `./build/bin/Eclipse-9`
- **Clean**: `rm -rf build && mkdir build`
- **Compile commands**: Generated at `build/compile_commands.json`

## Architecture
- **Project**: Eclipse-9 - 2D infinite open-world game using SFML
- **Main components**: Game loop, State management, Procedural generation
- **Key directories**: `src/Game/` (core), `src/InGame/` (gameplay), `src/State/` (state machine), `src/MainMenu/`, `src/Renderer/`
- **Dependencies**: SFML 2.6.x (auto-fetched), FastNoiseLite for terrain generation
- **Entry point**: `src/Main.cpp` → `Game::Run()` → StateManager

## Code Style
- **Language**: C++20
- **Headers**: Use include guards (`#ifndef HEADER_H`)
- **Includes**: SFML headers first, then local headers with relative paths
- **Naming**: PascalCase for classes/methods, camelCase for variables
- **Formatting**: Tabs for indentation, spaces around operators
- **File structure**: `.hpp` for headers, `.cpp` for implementation
- **State pattern**: Inherit from `GameState`, implement `HandleInput/Update/Draw`
