# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#
# CMake configuration for main library
#

file(GLOB_RECURSE PROJECT_SRCS ./*.c ${PROJECT_SOURCE_DIR}/include/*.h)

set(PROJECT_OUTPUT_NAME "${PROJECT_NAME}")

IF (UNIX)
        # Compile flags
        set(_CMAKE_C_FLAGS "${_CMAKE_C_FLAGS} -pedantic -fPIC")
        set(_CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS} -g -O0")
        set(_CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS} -O3")

        # Linked libraries
        set(PROJECT_LINK_LIBRARIES)
ELSEIF (WIN32)
        # Compile flags
        set(_CMAKE_C_FLAGS "/wd4127 /wd4210 /wd6031 /wd4706 /wd28252 /wd28253 /wd4172 /wd4100 /wd4204 /wd4221 /Wall /W4 -D_CRT_SECURE_NO_WARNINGS")
        set(_CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS} /DEBUG")
        set(_CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS} /MP")

        # Linked libraries
        set(PROJECT_LINK_LIBRARIES)
ENDIF ()

# Installation
if (PROJECT_CI_DEPLOY)
        set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")
else ()
        set(CMAKE_INSTALL_PREFIX "/usr/local")
endif ()

#
# Shared library build
#
IF (PROJECT_YALL_SHARED)
        IF (UNIX)
                set(CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS_DEBUG}")
                set(CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS_RELEASE}")
        ELSEIF (WIN32)
                set(CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS_DEBUG} /Z7")
                set(CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS_RELEASE}")
        ENDIF ()


        # CMake logging
        message("> Add execuable ${PROJECT_NAME}_shared : ${PROJECT_OUTPUT_NAME}")
        message(">     Compile flags       :")
        message(">         Debug   : ${CMAKE_C_FLAGS_DEBUG}")
        message(">         Release : ${CMAKE_C_FLAGS_RELEASE}")
        message(">     Linked libraries    : ${PROJECT_LINK_LIBRARIES}")

        add_library(${PROJECT_NAME}_shared SHARED ${PROJECT_SRCS})
        target_link_libraries(${PROJECT_NAME}_shared ${PROJECT_LINK_LIBRARIES})
        set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_OUTPUT_NAME})
        set_target_properties(${PROJECT_NAME}_shared PROPERTIES
                VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
                SONAME "${PROJECT_VERSION_MAJOR}")
ENDIF ()

#
# Static library build
#
IF (PROJECT_YALL_STATIC)
        IF (UNIX)
                set(CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS_DEBUG}")
                set(CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS_RELEASE}")
        ELSEIF (WIN32)
                set(CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS_DEBUG} /Z7")
                set(CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS_RELEASE}")
        ENDIF ()

        # CMake logging
        message("> Add execuable ${PROJECT_NAME}_static : ${PROJECT_OUTPUT_NAME}")
        message(">     Compile flags       :")
        message(">         Debug   : ${CMAKE_C_FLAGS_DEBUG}")
        message(">         Release : ${CMAKE_C_FLAGS_RELEASE}")
        message(">     Linked libraries    : ${PROJECT_LINK_LIBRARIES}")

        add_library(${PROJECT_NAME}_static STATIC ${PROJECT_SRCS})
        target_link_libraries(${PROJECT_NAME}_static ${PROJECT_LINK_LIBRARIES})
        set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_OUTPUT_NAME})
ENDIF ()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX}
        PATTERN "version.h.in" EXCLUDE)
install(TARGETS ${PROJECT_NAME}_shared ${PROJECT_NAME}_static
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Make dist
add_custom_target(dist COMMAND ${CMAKE_COMMAND} -E tar "cfvz" "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}.tgz" "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")
add_custom_command(TARGET dist
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/LICENSE "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}"
          COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/README.md "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")