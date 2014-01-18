# Finds liblua libraries
#
#  liblua_FOUND              - True if liblua library was found
#  liblua_LIBRARIES          - Libraries to link against

include (PkgMacros)

clear_if_changed(
    LIBLUA_LIB_DIR
    liblua_LIBRARY_REL
    liblua_LIBRARY_DBG
)

findpkg_begin(liblua liblua_FIND_QUIETLY)
find_path(liblua_INCLUDE_DIR lua.h HINTS "${LIBLUA_INCLUDE_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
set(liblua_LIBRARY_NAMES lua)
get_debug_names(liblua_LIBRARY_NAMES)
find_library(liblua_LIBRARY_REL NAMES ${liblua_LIBRARY_NAMES} HINTS "${LIBLUA_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
find_library(liblua_LIBRARY_DBG NAMES ${liblua_LIBRARY_NAMES_DBG} HINTS "${LIBLUA_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
make_library_set(liblua_LIBRARY)
findpkg_finish(liblua liblua_FIND_QUIETLY liblua_FIND_REQUIRED)
