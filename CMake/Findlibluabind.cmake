# Finds libluabind libraries
#
#  libluabind_FOUND              - True if libluabind library was found
#  libluabind_LIBRARIES          - Libraries to link against

include (PkgMacros)

clear_if_changed(
    LIBLUABIND_LIB_DIR
    libluabind_LIBRARY_REL
    libluabind_LIBRARY_DBG
)

findpkg_begin(libluabind libluabind_FIND_QUIETLY)
find_path(libluabind_INCLUDE_DIR luabind/luabind.hpp HINTS "${LIBLUABIND_INCLUDE_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
set(libluabind_LIBRARY_NAMES luabind)
get_debug_names(libluabind_LIBRARY_NAMES)
find_library(libluabind_LIBRARY_REL NAMES ${libluabind_LIBRARY_NAMES} HINTS "${LIBLUABIND_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
find_library(libluabind_LIBRARY_DBG NAMES ${libluabind_LIBRARY_NAMES_DBG} HINTS "${LIBLUABIND_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
make_library_set(libluabind_LIBRARY)
findpkg_finish(libluabind libluabind_FIND_QUIETLY libluabind_FIND_REQUIRED)
