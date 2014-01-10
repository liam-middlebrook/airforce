# Finds log4cplus libraries
#
#  log4cplus_FOUND              - True if log4cplus library was found
#  log4cplus_LIBRARIES          - Libraries to link against

include (PkgMacros)

clear_if_changed(
    LOG4CPLUS_LIB_DIR
    log4cplus_LIBRARY_REL
    log4cplus_LIBRARY_DBG
)

findpkg_begin(log4cplus log4cplus_FIND_QUIETLY)
find_path(log4cplus_INCLUDE_DIR log4cplus/logger.h HINTS "${LOG4CPLUS_INCLUDE_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
set(log4cplus_LIBRARY_NAMES log4cplus)
get_debug_names(log4cplus_LIBRARY_NAMES)
find_library(log4cplus_LIBRARY_REL NAMES ${log4cplus_LIBRARY_NAMES} HINTS "${LOG4CPLUS_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
find_library(log4cplus_LIBRARY_DBG NAMES ${log4cplus_LIBRARY_NAMES_DBG} HINTS "${LOG4CPLUS_LIB_DIR}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
make_library_set(log4cplus_LIBRARY)
findpkg_finish(log4cplus log4cplus_FIND_QUIETLY log4cplus_FIND_REQUIRED)
