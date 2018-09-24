# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (UNIX)
    find_path(pthread_INCLUDE_DIR
        NAMES pthread.h
        PATHS ${pthread_HINTS} / /usr /usr/local
        PATH_SUFFIXES include)
        
    find_library(pthread_LIBRARY
        NAMES pthread
        PATHS ${pthread_HINTS} / /usr /usr/local
        PATH_SUFFIXES lib)
elseif (WIN32)
    find_path(pthread_INCLUDE_DIR
        NAMES pthread.h
        PATHS ${pthread_HINTS} C:/
        PATH_SUFFIXES include)

    find_library(pthread_LIBRARY
        NAMES pthreadVC2
        PATHS ${pthread_HINTS} C:/
        PATH_SUFFIXES lib)
endif ()

set(pthread_INCLUDE_DIRS "${pthread_INCLUDE_DIR}")
set(pthread_LIBRARIES "${pthread_LIBRARY}")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    pthread
    REQUIRED_VARS
        pthread_INCLUDE_DIRS
        pthread_LIBRARIES)

set(pthread_FOUND "${PTHREAD_FOUND}")

if(pthread_FOUND)
    message(STATUS "> pthread found")
    if (NOT TARGET pthread::pthread)
        add_library(pthread::pthread UNKNOWN IMPORTED)
    endif()

    set_target_properties(pthread::pthread PROPERTIES
        IMPORTED_LOCATION "${pthread_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${pthread_INCLUDE_DIRS}")

    message(STATUS ">\t${pthread_LIBRARIES}")
    message(STATUS ">\t${pthread_INCLUDE_DIRS}")
else ()
    message(STATUS "> pthread not found")
endif ()

mark_as_advanced(pthread_INCLUDE_DIRS)
mark_as_advanced(pthread_LIBRARIES)
