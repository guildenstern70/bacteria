//
// Bacteria Project
// Copyright (C) 2026, Alessio Saltarin
//
// BSD License - see LICENSE
//

#include "Bacteria.h"

#include <cmath>
#include <random>

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

static const char* NAME_PREFIXES[] = {
    "Staphylo", "Strepto",  "Escher",   "Bacil",  "Vibrio",
    "Lacto",    "Myco",     "Pseudo",   "Clostri","Listeria",
    "Salmo",    "Campy",    "Entero",   "Klebsi", "Proteo"
};

static const char* NAME_SUFFIXES[] = {
    "coccus", "coli",   "lus",    "rium",  "chiae",
    "bacter", "plasma", "dium",   "nella", "lobacter"
};

static int randInt(int lo, int hi) {
    return std::uniform_int_distribution<int>(lo, hi)(rng());
}

static float randFloat(float lo, float hi) {
    return std::uniform_real_distribution<float>(lo, hi)(rng());
}

Bacteria::Bacteria(int screenWidth, int screenHeight) {
    // Random name from prefix + suffix pool
    constexpr int np = std::size(NAME_PREFIXES);
    constexpr int ns = std::size(NAME_SUFFIXES);
    m_name = std::string(NAME_PREFIXES[randInt(0, np - 1)])
           + NAME_SUFFIXES[randInt(0, ns - 1)];

    m_age    = 0.0f;
    m_radius = randInt(12, 22);

    // Random position fully inside the screen
    m_x = randFloat(static_cast<float>(m_radius),
                    static_cast<float>(screenWidth  - m_radius));
    m_y = randFloat(static_cast<float>(m_radius),
                    static_cast<float>(screenHeight - m_radius));

    // Random speed (20–50 px/s) in a random direction
    const float speed = randFloat(20.0f, 50.0f);
    const float angle = randFloat(0.0f, 2.0f * static_cast<float>(M_PI));
    m_vx = speed * std::cos(angle);
    m_vy = speed * std::sin(angle);

    // Random vivid color (at least one channel near full brightness)
    m_color = {
        static_cast<Uint8>(randInt(80, 255)),
        static_cast<Uint8>(randInt(80, 255)),
        static_cast<Uint8>(randInt(80, 255)),
        255
    };
}

void Bacteria::update(float deltaTime, int screenWidth, int screenHeight) {
    m_age += deltaTime;
    m_x   += m_vx * deltaTime;
    m_y   += m_vy * deltaTime;

    // Bounce off screen edges
    if (m_x - m_radius < 0.0f) {
        m_x  = static_cast<float>(m_radius);
        m_vx = std::abs(m_vx);
    } else if (m_x + m_radius > static_cast<float>(screenWidth)) {
        m_x  = static_cast<float>(screenWidth - m_radius);
        m_vx = -std::abs(m_vx);
    }
    if (m_y - m_radius < 0.0f) {
        m_y  = static_cast<float>(m_radius);
        m_vy = std::abs(m_vy);
    } else if (m_y + m_radius > static_cast<float>(screenHeight)) {
        m_y  = static_cast<float>(screenHeight - m_radius);
        m_vy = -std::abs(m_vy);
    }
}

bool Bacteria::contains(float mx, float my) const {
    const float dx = mx - m_x;
    const float dy = my - m_y;
    return (dx * dx + dy * dy) <= static_cast<float>(m_radius * m_radius);
}

void Bacteria::drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int dy = -radius; dy <= radius; ++dy) {
        const int dx = static_cast<int>(
            std::sqrt(static_cast<float>(radius * radius - dy * dy)));
        SDL_RenderLine(renderer, cx - dx, cy + dy, cx + dx, cy + dy);
    }
}

void Bacteria::render(SDL_Renderer* renderer) const {
    const int cx = static_cast<int>(m_x);
    const int cy = static_cast<int>(m_y);

    // Cell membrane: slightly larger, half-brightness halo
    SDL_SetRenderDrawColor(renderer,
        m_color.r / 2, m_color.g / 2, m_color.b / 2, 220);
    drawFilledCircle(renderer, cx, cy, m_radius + 4);

    // Cell body
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, 255);
    drawFilledCircle(renderer, cx, cy, m_radius);

    // Nucleus: small bright highlight offset toward top-left
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    drawFilledCircle(renderer, cx - m_radius / 4, cy - m_radius / 4, m_radius / 4);
}
