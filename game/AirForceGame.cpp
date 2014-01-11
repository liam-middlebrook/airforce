#include "AirForceGame.h"
#include "OGL.h"
#include "Logger.h"
#include "Player.h"
#include "TextureManager.h"
#include "af/Utils.h"
#include <boost/make_shared.hpp>

namespace af
{
    AirForceGame::AirForceGame()
    : viewWidth_(0),
      viewHeight_(0),
      gameWidth_(0),
      gameHeight_(0),
      lastTimeMs_(0),
      numFrames_(0),
      accumRenderTimeMs_(0),
      accumTimeMs_(0),
      lastProfileReportTimeMs_(0)
    {
    }

    AirForceGame::~AirForceGame()
    {
    }

    bool AirForceGame::init(void* display, void* window,
                            UInt32 viewWidth, UInt32 viewHeight,
                            float gameHeight)
    {
        if (!ogl.init(display, window)) {
            return false;
        }

        if (!textureManager.init(".")) {
            return false;
        }

        viewWidth_ = viewWidth;
        viewHeight_ = viewHeight;
        gameWidth_ = gameHeight * (viewWidth / viewHeight);
        gameHeight_ = gameHeight;

        scene_ = boost::make_shared<Scene>();

        scene_->add(
            new Player(b2Vec2(10.0f, 10.0f), 1.0f,
               Image(textureManager.loadTexture("common.png"), 0, 0, 100, 100)));

        return true;
    }

    void AirForceGame::update()
    {
        UInt64 timeMs = getTimeMs();
        UInt32 deltaMs = 0;

        if (lastTimeMs_ == 0)
        {
            lastTimeMs_ = timeMs;
            lastProfileReportTimeMs_ = timeMs;
        }
        else
        {
            deltaMs = (timeMs - lastTimeMs_);
        }

        lastTimeMs_ = timeMs;

        float dt = static_cast<float>(deltaMs) / 1000.0f;

        /*
         * Update and render stuff.
         */

        scene_->update(dt);

        ogl.swapBuffers();

        UInt64 timeMs2 = getTimeMs();

        accumRenderTimeMs_ += (timeMs2 - timeMs);
        accumTimeMs_ += deltaMs;
        ++numFrames_;

        if ((timeMs2 - lastProfileReportTimeMs_) > profileReportTimeoutMs_)
        {
            lastProfileReportTimeMs_ = timeMs2;

            LOG4CPLUS_DEBUG(logger(),
                            "FPS: " << (numFrames_ * 1000) / accumTimeMs_
                            << " Time: " << accumRenderTimeMs_ / numFrames_);

            accumRenderTimeMs_ = 0;
            accumTimeMs_ = 0;
            numFrames_ = 0;
        }
    }

    void AirForceGame::inputKeyDown(int key)
    {
    }

    void AirForceGame::inputKeyUp(int key)
    {
    }

    void AirForceGame::shutdown()
    {
        scene_.reset();

        textureManager.shutdown();

        ogl.shutdown();
    }
}
