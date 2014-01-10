#include "AirForceGame.h"
#include "OGL.h"
#include "Logger.h"

namespace af
{
    AirForceGame::AirForceGame()
    {
    }

    AirForceGame::~AirForceGame()
    {
    }

    bool AirForceGame::init(void* display, void* window,
                            UInt32 viewportWidth, UInt32 viewportHeight)
    {
        if (!ogl.init(display, window)) {
            return false;
        }

        return true;
    }

    void AirForceGame::update()
    {
    }

    void AirForceGame::inputKeyDown(int key)
    {
    }

    void AirForceGame::inputKeyUp(int key)
    {
    }

    void AirForceGame::shutdown()
    {
        ogl.shutdown();
    }
}
