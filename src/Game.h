// Bacteria Project
// Copyright (C) 2026, Alessio Saltarin
// BSL License - see LICENSE

#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Bacteria.h"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void quit();

private:
    void handleEvents();
    void update(float deltaTime);
    void render() const;

    SDL_Window*           m_window    = nullptr;
    SDL_Renderer*         m_renderer  = nullptr;
    bool                  m_running   = false;
    float                 m_mouseX    = 0.0f;
    float                 m_mouseY    = 0.0f;
    std::vector<Bacteria> m_bacteria;
};
