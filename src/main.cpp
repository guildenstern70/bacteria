//
// Bacteria Project
// Copyright (C) 2026, Alessio Saltarin
//
// BSD License - see LICENSE
//

#include "Game.h"

int main(int /*argc*/, char* /*argv*/[]) {
    Game game;

    if (!game.init()) {
        return 1;
    }

    game.run();
    return 0;
}
