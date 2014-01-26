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
    TextureManager.cpp
    Logger.cpp
    Renderer.cpp
    Image.cpp
    SceneObjectFactory.cpp
    Script.cpp
    SceneObjectManager.cpp
    ComponentVisitor.cpp
    PhasedComponentManager.cpp
    PhysicsBallComponent.cpp
    PhysicsComponentManager.cpp
    PhysicsPolygonComponent.cpp
    PhysicsTerrainComponent.cpp
    PlayerComponent.cpp
    RenderComponentManager.cpp
    RenderImageComponent.cpp
    RenderPolygonComponent.cpp
    RenderTerrainComponent.cpp
    SpriteComponent.cpp
)

add_executable(airforce ${SOURCES})

target_link_libraries(airforce afutil ${libluabind_LIBRARIES} ${liblua_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${log4cplus_LIBRARIES} ${Box2D_LIBRARIES} ${X11_LIBRARIES} rt dl)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/modules ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/modules)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/level.lua ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/level.lua)
