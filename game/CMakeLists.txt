set(SOURCES
    main.cpp
    Utils.cpp
    Game.cpp
    AirForceGame.cpp
    OGL.cpp
    InputManager.cpp
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
    PhysicsComponentManager.cpp
    RenderComponentManager.cpp
    CameraComponent.cpp
    PlayerComponent.cpp
    PhysicsBallComponent.cpp
    PhysicsPolygonComponent.cpp
    PhysicsTerrainComponent.cpp
    RenderPolygonComponent.cpp
    RenderTerrainComponent.cpp
)

add_executable(airforce ${SOURCES})

target_link_libraries(airforce afutil poly2tri
                               ${libluabind_LIBRARIES}
                               ${liblua_LIBRARIES}
                               ${CMAKE_THREAD_LIBS_INIT}
                               ${log4cplus_LIBRARIES}
                               ${Box2D_LIBRARIES}
                               ${X11_LIBRARIES} rt dl)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/modules ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/modules)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/level.lua ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/level.lua)
