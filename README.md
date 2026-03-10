# Bacteria

A C++ simulation game about bacteria and the spread of life, built with SDL3.

## Requirements

- C++17 or later
- CMake 3.20+
- SDL3 (install via Homebrew: `brew install sdl3`)

## Building

```bash
cmake -B build -S .
cmake --build build
```

## Running

```bash
./build/bacteria
```

Press **Esc** or close the window to quit.

## Project Structure

```
bacteria/
├── CMakeLists.txt
└── src/
    ├── main.cpp      # Entry point
    ├── Game.h        # Game class declaration
    └── Game.cpp      # Game loop, rendering, event handling
```

## Technical Details

- **Window:** 800×600
- **Target FPS:** 60
- **Frame timing:** High-resolution performance counter for frame-rate-independent simulation (`deltaTime` in seconds passed to `update()`)
