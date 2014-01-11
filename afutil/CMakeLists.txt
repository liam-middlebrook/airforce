set(SOURCES
    Logger.cpp
    PNGDecoder.cpp
    PNGUtils.cpp
    Utils.cpp
)

add_library(afutil STATIC ${SOURCES})

target_link_libraries(afutil ${log4cplus_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${libpng_LIBRARIES} z)
