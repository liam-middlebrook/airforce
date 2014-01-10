#include "Game.h"
#include <stdexcept>

namespace af
{
    static Game* game = NULL;

    Game::Game()
    {
        if (game) {
            throw std::runtime_error("Game already exists");
        }

        game = this;
    }

    Game::~Game()
    {
        game = NULL;
    }
}
