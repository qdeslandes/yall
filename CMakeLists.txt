# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#
# CMake configuration
#

cmake_minimum_required(VERSION 3.6)

project(yall)

# Set version variables
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
configure_file("${PROJECT_SOURCE_DIR}/include/version.h.in" "${PROJECT_BINARY_DIR}/generated_headers/version.h")

# Options for CI and desktop build
option(PROJECT_CI_DEPLOY "Special target for continuous integration deployment" OFF)
option(PROJECT_COVERAGE "Enable unit test coverage report" OFF)
option(PROJECT_YALL_SHARED "Enable unit test coverage report" ON)
option(PROJECT_YALL_STATIC "Enable unit test coverage report" ON)

# CMake internal configuration
set(CMAKE_CONFIGURATION_TYPES "" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Debug;" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Release;" CACHE STRING "" FORCE)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Build and platform specific configuration
include_directories(AFTER "include" "external/include" "${PROJECT_BINARY_DIR}/generated_headers")

if (UNIX)
	link_directories("${CMAKE_SOURCE_DIR}/external/lib/linux")
	set(_CMAKE_C_FLAGS "-Wall -Wextra -std=c11 -fvisibility=hidden")
        set(_CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 -fvisibility=hidden")

	if (CMAKE_COMPILER_IS_GNUCC)
		set(COMPILER "gcc-${CMAKE_C_COMPILER_VERSION}")
	else ()
		set(COMPILER "gcc_unknow")
	endif ()
elseif (WIN32)
	if (MSVC_VERSION EQUAL 1900)
		set(COMPILER "msvc14")
		link_directories("${CMAKE_SOURCE_DIR}/external/lib/win32/msvc14")
	elseif (MSVC_VERSION EQUAL 1800)
		set(COMPILER "msvc12")
		link_directories("${CMAKE_SOURCE_DIR}/external/lib/win32/msvc12")
	else ()
		set(COMPILER "msvc_unknow")
	endif ()
endif ()

# Project internal configuration
set(PROJECT_INSTALL_DIR "${PROJECT_NAME}-${COMPILER}-x86_64-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

add_subdirectory(src)
add_subdirectory(tests)
