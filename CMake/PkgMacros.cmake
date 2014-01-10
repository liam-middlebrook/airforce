# Begin processing of package
macro(findpkg_begin PREFIX PREFIX_FIND_QUIETLY)
    if (NOT ${PREFIX_FIND_QUIETLY})
        message(STATUS "Looking for ${PREFIX}...")
    endif ()
endmacro(findpkg_begin)

# clear cache variables if a certain variable changed
macro(clear_if_changed TESTVAR)
    # test against internal check variable
    # HACK: Apparently, adding a variable to the cache cleans up the list
    # a bit. We need to also remove any empty strings from the list, but
    # at the same time ensure that we are actually dealing with a list.
    list(APPEND ${TESTVAR} "")
    list(REMOVE_ITEM ${TESTVAR} "")
    if (NOT "${${TESTVAR}}" STREQUAL "${${TESTVAR}_INT_CHECK}")
        message(STATUS "${TESTVAR} changed.")
        foreach(var ${ARGN})
            set(${var} "NOTFOUND" CACHE STRING "x" FORCE)
        endforeach(var)
    endif ()
    set(${TESTVAR}_INT_CHECK ${${TESTVAR}} CACHE INTERNAL "x" FORCE)
endmacro(clear_if_changed)

# Couple a set of release AND debug libraries
macro(make_library_set PREFIX)
    if (${PREFIX}_REL AND ${PREFIX}_DBG)
        set(${PREFIX} optimized ${${PREFIX}_REL} debug ${${PREFIX}_DBG})
    elseif (${PREFIX}_REL)
        set(${PREFIX} ${${PREFIX}_REL})
    elseif (${PREFIX}_DBG)
        set(${PREFIX} ${${PREFIX}_DBG})
    endif ()
endmacro(make_library_set)

# Generate debug names from given release names
macro(get_debug_names PREFIX)
    foreach(i ${${PREFIX}})
        set(${PREFIX}_DBG ${${PREFIX}_DBG} ${i}d ${i}D ${i}_d ${i}_D ${i}_debug ${i})
    endforeach(i)
endmacro(get_debug_names)

# Do the final processing for the package find.
macro(findpkg_finish PREFIX PREFIX_FIND_QUIETLY PREFIX_FIND_REQUIRED)
    # skip if already processed during this run
    if (NOT ${PREFIX}_FOUND)
        if (${PREFIX}_INCLUDE_DIR AND ${PREFIX}_LIBRARY)
            set(${PREFIX}_FOUND TRUE)
            set(${PREFIX}_INCLUDE_DIRS ${${PREFIX}_INCLUDE_DIR})
            set(${PREFIX}_LIBRARIES ${${PREFIX}_LIBRARY})
            if (NOT PREFIX_FIND_QUIETLY)
                message(STATUS "Found ${PREFIX}: ${${PREFIX}_LIBRARIES}")
            endif ()
        else ()
            if (NOT ${PREFIX_FIND_QUIETLY})
                message(STATUS "Could not locate ${PREFIX}")
            endif ()
            if (${PREFIX_FIND_REQUIRED})
                message(FATAL_ERROR "Required library ${PREFIX} not found! Install the library (including dev packages) and try again. If the library is already installed, set the missing variables manually in cmake.")
            endif ()
        endif ()
        mark_as_advanced(${PREFIX}_INCLUDE_DIR ${PREFIX}_LIBRARY ${PREFIX}_LIBRARY_REL ${PREFIX}_LIBRARY_DBG)
    endif ()
endmacro(findpkg_finish)
