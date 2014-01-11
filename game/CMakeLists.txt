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
    TextureManager.cpp
    Logger.cpp
    Renderer.cpp
    Image.cpp
)

add_executable(airforce ${SOURCES})

target_link_libraries(airforce afutil ${CMAKE_THREAD_LIBS_INIT} ${log4cplus_LIBRARIES} ${Box2D_LIBRARIES} ${X11_LIBRARIES} rt dl)
