//
// Bacteria Project
// Copyright (C) 2026, Alessio Saltarin
//
// BSD License - see LICENSE
//

#pragma once

#include <SDL3/SDL.h>
#include <string>

class Bacteria {
public:
    Bacteria(int screenWidth, int screenHeight);

    void update(float deltaTime, int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer) const;

    const std::string& name()   const { return m_name; }
    float              age()    const { return m_age; }
    float              x()      const { return m_x; }
    float              y()      const { return m_y; }
    int                radius() const { return m_radius; }
    bool               contains(float mx, float my) const;

private:
    static void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius);

    std::string m_name;
    float       m_age;
    float       m_x, m_y;
    float       m_vx, m_vy;
    SDL_Color   m_color;
    int         m_radius;
};
