#ifndef _GAME_H_
#define _GAME_H_

#include "af/Types.h"

#include <boost/noncopyable.hpp>

namespace af
{
    class Game : boost::noncopyable
    {
    public:
        Game();
        virtual ~Game();

        virtual bool init(void* display, void* window,
                          UInt32 viewportWidth, UInt32 viewportHeight) = 0;

        virtual void update() = 0;

        virtual void inputKeyDown(int key) = 0;

        virtual void inputKeyUp(int key) = 0;

        virtual void shutdown() = 0;
    };
}

#endif
