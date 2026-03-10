//
// Bacteria Project
// Copyright (C) 2026, Alessio Saltarin
//
// BSD License - see LICENSE
//

#include "Game.h"
#include <SDL3/SDL.h>

Game::Game() = default;

Game::~Game() {
    quit();
}

bool Game::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow("Bacteria", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!m_window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        return false;
    }

    m_running = true;

    for (int i = 0; i < 3; ++i) {
        m_bacteria.emplace_back(WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_Log("Spawned bacteria: %s", m_bacteria.back().name().c_str());
    }

    return true;
}

void Game::run() {
    constexpr float TARGET_FRAME_TIME = 1.0f / TARGET_FPS;

    Uint64 perfFreq    = SDL_GetPerformanceFrequency();
    Uint64 lastCounter = SDL_GetPerformanceCounter();

    while (m_running) {
        Uint64 now       = SDL_GetPerformanceCounter();
        float  deltaTime = static_cast<float>(now - lastCounter) / static_cast<float>(perfFreq);
        lastCounter      = now;

        handleEvents();
        update(deltaTime);
        render();

        // Cap frame rate
        float elapsed = static_cast<float>(SDL_GetPerformanceCounter() - lastCounter)
                        / static_cast<float>(perfFreq);
        if (elapsed < TARGET_FRAME_TIME) {
            SDL_DelayNS(static_cast<Uint64>((TARGET_FRAME_TIME - elapsed) * 1e9f));
        }
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            m_running = false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN &&
            event.key.key == SDLK_ESCAPE) {
            m_running = false;
        }
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            m_mouseX = event.motion.x;
            m_mouseY = event.motion.y;
        }
    }
}

void Game::update(float deltaTime) {
    for (auto& b : m_bacteria)
        b.update(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::render() const {
    SDL_SetRenderDrawColor(m_renderer, 10, 15, 10, 255); // dark green background
    SDL_RenderClear(m_renderer);

    // Draw bacteria
    for (const auto& b : m_bacteria)
        b.render(m_renderer);

    // Hover info panel
    for (const auto& b : m_bacteria) {
        if (!b.contains(m_mouseX, m_mouseY))
            continue;

        constexpr int  FONT  = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
        constexpr int  PAD   = 6;
        constexpr int  LINES = 2;
        const int panelW = static_cast<int>(b.name().size()) * FONT + PAD * 2;
        const int panelH = LINES * (FONT + PAD) + PAD;

        // Position above the bacterium, clamped to screen
        int px = static_cast<int>(b.x()) - panelW / 2;
        int py = static_cast<int>(b.y()) - b.radius() - panelH - 6;
        if (px < 0) px = 0;
        if (px + panelW > WINDOW_WIDTH)  px = WINDOW_WIDTH  - panelW;
        if (py < 0) py = static_cast<int>(b.y()) + b.radius() + 6;

        // Dark semi-transparent background
        SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(m_renderer, 20, 20, 20, 210);
        const SDL_FRect panel = {
            static_cast<float>(px),   static_cast<float>(py),
            static_cast<float>(panelW), static_cast<float>(panelH)
        };
        SDL_RenderFillRect(m_renderer, &panel);
        SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_NONE);

        // Name line
        SDL_SetRenderDrawColor(m_renderer, 220, 220, 220, 255);
        SDL_RenderDebugText(m_renderer,
            static_cast<float>(px + PAD),
            static_cast<float>(py + PAD),
            b.name().c_str());

        // Age line
        char ageBuf[32];
        SDL_snprintf(ageBuf, sizeof(ageBuf), "Age: %.1fs", b.age());
        SDL_SetRenderDrawColor(m_renderer, 160, 220, 160, 255);
        SDL_RenderDebugText(m_renderer,
            static_cast<float>(px + PAD),
            static_cast<float>(py + PAD + FONT + PAD),
            ageBuf);

        break; // only one panel at a time
    }

    SDL_RenderPresent(m_renderer);
}

void Game::quit() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}
