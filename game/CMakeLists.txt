set(SOURCES
    main.cpp
    AirForceGame.cpp
    GL.cpp
    InputManager.cpp
    Player.cpp
    Rock.cpp
    Scene.cpp
    SceneObject.cpp
    SceneObjectFactory.cpp
    Sprite.cpp
    Texture.cpp
    TextureManager.cpp
)

add_executable(airforce ${SOURCES})

target_link_libraries(airforce ${log4cplus_LIBRARIES} ${Box2D_LIBRARIES})
