// Bacteria Project
// Copyright (C) 2026, Alessio Saltarin
// BSL License - see LICENSE

#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Bacteria.h"

class Game {
public:
    static constexpr int WINDOW_WIDTH  = 800;
    static constexpr int WINDOW_HEIGHT = 600;
    static constexpr int TARGET_FPS    = 60;

    Game();
    ~Game();

    bool init();
    void run();
    void quit();

private:
    void handleEvents();
    void update(float deltaTime);
    void render();

    SDL_Window*           m_window    = nullptr;
    SDL_Renderer*         m_renderer  = nullptr;
    bool                  m_running   = false;
    float                 m_mouseX    = 0.0f;
    float                 m_mouseY    = 0.0f;
    std::vector<Bacteria> m_bacteria;
};
