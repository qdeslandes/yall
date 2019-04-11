# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

cmake_minimum_required(VERSION 3.6)

project(yall)

set(pthread_HINTS "" CACHE STRING "Hint to find pthread directory")
set(criterion_HINTS "" CACHE STRING "Hint to find criterion directory")
option(TARGET_EXT_INFOS "Display extended infos about the CMake targets" OFF)

# Compiler flags
set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)
if (UNIX AND CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE "Release")
endif ()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/resources/cmake/module")

find_package(jansson REQUIRED)
find_package(pthread REQUIRED)
find_package(criterion REQUIRED)

if (UNIX)
    find_package(Doxygen REQUIRED)
endif ()

#[[
	Project version
#]]
if (NOT YALL_VERSION_MAJOR)
	set(YALL_VERSION_MAJOR 0)
endif ()
if (NOT YALL_VERSION_MINOR)
	set(YALL_VERSION_MINOR 0)
endif ()
if (NOT YALL_VERSION_PATCH)
	set(YALL_VERSION_PATCH 0)
endif ()

set(YALL_VERSION "${YALL_VERSION_MAJOR}.${YALL_VERSION_MINOR}.${YALL_VERSION_PATCH}")

configure_file("${PROJECT_SOURCE_DIR}/include/version.h.in" "${PROJECT_BINARY_DIR}/generated_headers/version.h")

message("==== Building yall version ${YALL_VERSION_MAJOR}.${YALL_VERSION_MINOR}.${YALL_VERSION_PATCH}")


#[[
	CMake internal configuration
#]]

set(CMAKE_CONFIGURATION_TYPES "" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Debug;" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Release;" CACHE STRING "" FORCE)

set(CMAKE_DEBUG_POSTFIX d)


#[[
	System specific variables
#]]
if (CMAKE_COMPILER_IS_GNUCC)
    set(COMPILER "gcc-${CMAKE_C_COMPILER_VERSION}")
else ()
    set(COMPILER "linux_unknow")
endif ()

link_directories(${CMAKE_SOURCE_DIR}/external/lib/linux)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/out/public/doxygen)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/out/coverage)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(doc)
