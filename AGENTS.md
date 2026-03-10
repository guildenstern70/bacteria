# AGENTS.md

Guidelines for AI coding agents working on this project.

## Project Overview

A C++ simulation game about bacteria and the spread of life, built with **SDL3**.
The game runs an 800×600 window at 60 FPS.

## Tech Stack

| Tool    | Version  | Notes                          |
|---------|----------|--------------------------------|
| C++     | 17       | Standard required              |
| CMake   | ≥ 3.20   | Build system                   |
| SDL3    | 3.4.2    | Via Homebrew (`brew install sdl3`) |

## Project Structure

```
bacteria/
├── CMakeLists.txt       # Build definition
└── src/
    ├── main.cpp         # Entry point — do not add logic here
    ├── Game.h           # Game class interface
    └── Game.cpp         # Game loop: handleEvents → update → render
```

## Architecture Conventions

- **`Game`** is the top-level class owning the SDL window and renderer.
- The main loop follows a strict **handleEvents → update → render** order.
- `update(float deltaTime)` receives delta time in **seconds** — all simulation logic must be frame-rate-independent.
- New subsystems (e.g. `Bacteria`, `World`, `Renderer`) should be separate classes in their own `.h`/`.cpp` files under `src/`.
- SDL resources (`SDL_Window*`, `SDL_Texture*`, etc.) must always be released in the owning class destructor.

## Coding Style

- C++17 features are welcome (structured bindings, `std::optional`, `if constexpr`, etc.).
- Use `nullptr`, not `NULL`.
- Class member variables are prefixed with `m_` (e.g. `m_window`, `m_renderer`).
- Constants go in `static constexpr` inside the relevant class, not as `#define` macros.
- Prefer RAII — avoid raw `new`/`delete`; use smart pointers or value types where SDL allows.
- Only comment code that needs clarification; avoid redundant comments.

## Build & Verify

Always build and confirm zero errors after making changes:

```bash
cmake -B build -S . && cmake --build build
```

The binary is at `./build/bacteria`.

## SDL3 Notes

SDL3 differs from SDL2 in several key ways — use SDL3 APIs only:

- `SDL_Init` returns `bool` (not `int`); check with `if (!SDL_Init(...))`.
- Event types use the `SDL_EVENT_*` prefix (e.g. `SDL_EVENT_QUIT`, `SDL_EVENT_KEY_DOWN`).
- `event.key.key` holds the keycode (not `event.key.keysym.sym`).
- `SDL_DelayNS(nanoseconds)` for high-resolution sleep.
- Renderer creation: `SDL_CreateRenderer(window, nullptr)` — no index parameter.
- Do **not** use any deprecated SDL2 API.
