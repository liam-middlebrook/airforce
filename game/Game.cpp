#include "Game.h"

namespace af
{
    template <>
    Single<Game>* Single<Game>::single = NULL;

    Game::Game()
    {
    }

    Game::~Game()
    {
    }
}
