set(SOURCES
    main.cpp
    Game.cpp
    AirForceGame.cpp
    OGL.cpp
    InputManager.cpp
    Player.cpp
    Rock.cpp
    Scene.cpp
    SceneObject.cpp
    SceneObjectFactory.cpp
    Sprite.cpp
    Texture.cpp
    TextureManager.cpp
    Logger.cpp
)

add_executable(airforce ${SOURCES})

target_link_libraries(airforce ${CMAKE_THREAD_LIBS_INIT} ${log4cplus_LIBRARIES} ${Box2D_LIBRARIES} ${X11_LIBRARIES} rt dl)
