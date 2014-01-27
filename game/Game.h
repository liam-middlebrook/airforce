#ifndef _GAME_H_
#define _GAME_H_

#include "Single.h"
#include "Types.h"

namespace af
{
    class Game : public Single<Game>
    {
    public:
        Game();
        virtual ~Game();

        virtual bool init(void* display, void* window,
                          UInt32 viewWidth, UInt32 viewHeight,
                          float gameHeight) = 0;

        virtual void update() = 0;

        virtual void inputKeyDown(int key) = 0;

        virtual void inputKeyUp(int key) = 0;

        virtual void shutdown() = 0;
    };
}

#endif
