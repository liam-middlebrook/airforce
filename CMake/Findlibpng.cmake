# Finds libpng libraries
#
#  libpng_FOUND              - True if libpng library was found
#  libpng_LIBRARIES          - Libraries to link against

include (PkgMacros)

clear_if_changed(
    LIBPNG_LIB_DIR
    libpng_LIBRARY_REL
    libpng_LIBRARY_DBG
)

findpkg_begin(libpng libpng_FIND_QUIETLY)
find_path(libpng_INCLUDE_DIR png.h HINTS "${LIBPNG_INCLUDE_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
set(libpng_LIBRARY_NAMES png)
get_debug_names(libpng_LIBRARY_NAMES)
find_library(libpng_LIBRARY_REL NAMES ${libpng_LIBRARY_NAMES} HINTS "${LIBPNG_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
find_library(libpng_LIBRARY_DBG NAMES ${libpng_LIBRARY_NAMES_DBG} HINTS "${LIBPNG_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
make_library_set(libpng_LIBRARY)
findpkg_finish(libpng libpng_FIND_QUIETLY libpng_FIND_REQUIRED)
