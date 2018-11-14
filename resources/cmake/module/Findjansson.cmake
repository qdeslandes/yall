# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (MSVC_VERSION EQUAL 1800)
	set(MSVC_SUFFIX "_msvc12")
else ()
	set(MSVC_SUFFIX "_msvc14")
endif ()

if (UNIX)
    find_path(jansson_INCLUDE_DIR
        NAMES jansson.h
        PATHS ${jansson_HINTS} / /usr /usr/local
        PATH_SUFFIXES include)
        
    find_library(jansson_LIBRARY
        NAMES jansson
        PATHS ${jansson_HINTS} / /usr /usr/local
        PATH_SUFFIXES lib)
elseif (WIN32)
    find_path(jansson_INCLUDE_DIR
        NAMES jansson.h
        PATHS ${jansson_HINTS} C:/
        PATH_SUFFIXES include)

    find_library(jansson_LIBRARY
        NAMES jansson${MSVC_SUFFIX}
        PATHS ${jansson_HINTS} C:/
        PATH_SUFFIXES lib)
endif ()

set(jansson_INCLUDE_DIRS "${jansson_INCLUDE_DIR}")
set(jansson_LIBRARIES "${jansson_LIBRARY}")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    jansson
    REQUIRED_VARS
        jansson_INCLUDE_DIRS
        jansson_LIBRARIES)

set(jansson_FOUND "${JANSSON_FOUND}")

if(jansson_FOUND)
    message(STATUS "> jansson found")
    if (NOT TARGET jansson::jansson)
        add_library(jansson::jansson UNKNOWN IMPORTED)
    endif()

    set_target_properties(jansson::jansson PROPERTIES
        IMPORTED_LOCATION "${jansson_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${jansson_INCLUDE_DIRS}")

    message(STATUS ">\t${jansson_LIBRARIES}")
    message(STATUS ">\t${jansson_INCLUDE_DIRS}")
else ()
    message(STATUS "> jansson not found")
endif ()

mark_as_advanced(jansson_INCLUDE_DIRS)
mark_as_advanced(jansson_LIBRARIES)
