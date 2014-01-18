#include "AirForceGame.h"
#include "OGL.h"
#include "Logger.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "SceneObjectFactory.h"
#include "af/Utils.h"
#include <boost/make_shared.hpp>
#include <cmath>

namespace af
{
    AirForceGame::AirForceGame()
    : viewWidth_(0),
      viewHeight_(0),
      gameWidth_(0),
      gameHeight_(0),
      camWidth_(0),
      camHeight_(0),
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

        if (!textureManager.init("./assets")) {
            return false;
        }

        viewWidth_ = viewWidth;
        viewHeight_ = viewHeight;
        gameWidth_ = gameHeight * (static_cast<float>(viewWidth) / viewHeight);
        gameHeight_ = gameHeight;

        camWidth_= gameWidth_- 15.0f;
        camHeight_= gameHeight_- 15.0f;

        if (!renderer.init(viewWidth, viewHeight, gameWidth_, gameHeight_)) {
            return false;
        }

        if (!inputManager.init()) {
            return false;
        }

        if (!sceneObjectFactory.init()) {
            return false;
        }

        scene_ = boost::make_shared<Scene>();

        script_ = boost::make_shared<Script>("level.lua",
                                             "./modules",
                                             scene_.get());

        if (!script_->init()) {
            return false;
        }

        if (!script_->run()) {
            return false;
        }

        camPos_ = b2Vec2(0.0f, 0.0f);

        player_ = scene_->findPlayer();

        if (!player_) {
            LOG4CPLUS_ERROR(logger(), "No player");

            return false;
        }

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

        scene_->update(dt);

        updateCam();

        renderer.lookAt(camPos_);

        scene_->render();

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
        inputManager.inputKey(key, true);
    }

    void AirForceGame::inputKeyUp(int key)
    {
        inputManager.inputKey(key, false);
    }

    void AirForceGame::shutdown()
    {
        script_.reset();

        scene_.reset();

        sceneObjectFactory.shutdown();

        inputManager.shutdown();

        renderer.shutdown();

        textureManager.shutdown();

        ogl.shutdown();
    }

    void AirForceGame::updateCam()
    {
        b2Vec2 relPos = player_->body()->GetPosition() - camPos_;

        if ((std::fabs(relPos.x) <= (camWidth_ / 2)) &&
            (std::fabs(relPos.y) <= (camHeight_ / 2))) {
            playerOldPos_ = player_->body()->GetPosition();
            return;
        }

        camPos_ += (player_->body()->GetPosition() - playerOldPos_);

        playerOldPos_ = player_->body()->GetPosition();
    }
}
