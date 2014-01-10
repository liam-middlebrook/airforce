# Finds Box2D libraries
#
#  Box2D_FOUND              - True if Box2D library was found
#  Box2D_LIBRARIES          - Libraries to link against

include (PkgMacros)

clear_if_changed(
    BOX2D_LIB_DIR
    Box2D_LIBRARY_REL
    Box2D_LIBRARY_DBG
)

findpkg_begin(Box2D Box2D_FIND_QUIETLY)
find_path(Box2D_INCLUDE_DIR Box2D/Box2D.h HINTS "${BOX2D_INCLUDE_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
set(Box2D_LIBRARY_NAMES Box2D)
get_debug_names(Box2D_LIBRARY_NAMES)
find_library(Box2D_LIBRARY_REL NAMES ${Box2D_LIBRARY_NAMES} HINTS "${BOX2D_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
find_library(Box2D_LIBRARY_DBG NAMES ${Box2D_LIBRARY_NAMES_DBG} HINTS "${BOX2D_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
make_library_set(Box2D_LIBRARY)
findpkg_finish(Box2D Box2D_FIND_QUIETLY Box2D_FIND_REQUIRED)
