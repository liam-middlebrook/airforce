#ifndef _AIRFORCEGAME_H_
#define _AIRFORCEGAME_H_

#include "Game.h"
#include "Scene.h"

namespace af
{
    class AirForceGame : public Game
    {
    public:
        AirForceGame();
        ~AirForceGame();

        virtual bool init(void* display, void* window,
                          UInt32 viewWidth, UInt32 viewHeight,
                          float gameHeight);

        virtual void update();

        virtual void inputKeyDown(int key);

        virtual void inputKeyUp(int key);

        virtual void shutdown();

    private:
        static const UInt32 profileReportTimeoutMs_ = 2000;

        UInt32 viewWidth_;
        UInt32 viewHeight_;
        float gameWidth_;
        float gameHeight_;

        ScenePtr scene_;

        UInt64 lastTimeMs_;
        UInt32 numFrames_;
        UInt32 accumRenderTimeMs_;
        UInt32 accumTimeMs_;
        UInt64 lastProfileReportTimeMs_;
    };
}

#endif
