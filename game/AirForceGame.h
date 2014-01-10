#ifndef _AIRFORCEGAME_H_
#define _AIRFORCEGAME_H_

#include "Game.h"

namespace af
{
    class AirForceGame : public Game
    {
    public:
        AirForceGame();
        ~AirForceGame();

        virtual bool init(void* display, void* window,
                          UInt32 viewportWidth, UInt32 viewportHeight);

        virtual void update();

        virtual void inputKeyDown(int key);

        virtual void inputKeyUp(int key);

        virtual void shutdown();
    };
}

#endif
