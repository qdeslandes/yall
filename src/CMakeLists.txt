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
        set(CMAKE_C_FLAGS "${_CMAKE_C_FLAGS} -pedantic -fPIC")
        set(CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS} ${_CMAKE_C_FLAGS_DEBUG} -g -O0")
        set(CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS} ${_CMAKE_C_FLAGS_RELEASE} -O3")

        # Linked libraries
        set(PROJECT_LINK_LIBRARIES)
ELSEIF (WIN32)
        # Compile flags
        set(CMAKE_C_FLAGS "/wd4127 /wd4210 /wd6031 /wd4706 /wd28252 /wd28253 /wd4172 /wd4100 /wd4204 /wd4221 /Wall /W4 -D_CRT_SECURE_NO_WARNINGS")
        set(CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS} ${_CMAKE_C_FLAGS_DEBUG}")
        set(CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS} ${_CMAKE_C_FLAGS_RELEASE} /MP")

        # Linked libraries
        set(PROJECT_LINK_LIBRARIES)
ENDIF ()

# Installation
if (PROJECT-MISC_CI_DEPLOY)
        set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")
endif ()

# CMake logging
message("> Add executable ${PROJECT_NAME}_shared : ${PROJECT_OUTPUT_NAME}")
message(">     Compile flags       :")
message(">         Debug   : ${CMAKE_C_FLAGS_DEBUG}")
message(">         Release : ${CMAKE_C_FLAGS_RELEASE}")
message(">     Linked libraries    : ${PROJECT_LINK_LIBRARIES}")

# this is the "object library" target: compiles the sources only once
add_library(yall OBJECT ${PROJECT_SRCS})

#
# Shared library build
#
IF (PROJECT_YALL_SHARED)
        add_library(yall_shared SHARED $<TARGET_OBJECTS:yall>)

        target_link_libraries(yall_shared ${PROJECT_LINK_LIBRARIES})
        set_target_properties(yall_shared PROPERTIES OUTPUT_NAME ${PROJECT_OUTPUT_NAME})
        set_target_properties(yall_shared PROPERTIES
                VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
		SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

	install(TARGETS yall_shared
		LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
ENDIF ()

#
# Static library build
#
IF (PROJECT_YALL_STATIC)
        add_library(yall_static STATIC $<TARGET_OBJECTS:yall>)

        target_link_libraries(yall_static ${PROJECT_LINK_LIBRARIES})
        set_target_properties(yall_static PROPERTIES OUTPUT_NAME ${PROJECT_OUTPUT_NAME})
        set_target_properties(yall_static PROPERTIES
                VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

	install(TARGETS yall_static
		LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
ENDIF ()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX}
        PATTERN "version.h.in" EXCLUDE)

# Make dist
add_custom_target(dist COMMAND ${CMAKE_COMMAND} -E tar "cfvz" "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}.tgz" "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")
add_custom_command(TARGET dist
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/LICENSE "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}"
          COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/README.md "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")