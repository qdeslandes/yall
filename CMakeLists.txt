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
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

# Options for CI and desktop build
option(PROJECT_CI_DEPLOY "Special target for continuous integration deployment" OFF)
option(PROJECT_COVERAGE "Enable unit test coverage report" OFF)

# CMake internal configuration
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Build and platform specific configuration
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -std=c11 -fvisibility=hidden")
include_directories(AFTER "include" "external/include")
if (UNIX)
	link_directories("${CMAKE_SOURCE_DIR}/external/lib/linux")

	if (CMAKE_COMPILER_IS_GNUCC)
		set(COMPILER "gcc-${CMAKE_C_COMPILER_VERSION}")
	else ()
		set(COMPILER "gcc_unknow")
	endif ()
elseif (WIN32)
	link_directories("${CMAKE_SOURCE_DIR}/external/lib/win32")

	if (MSVC_VERSION EQUAL 1900)
		set(COMPILER "msvc-14.0")
	else ()
		set(COMPILER "msvc_unknow")
	endif ()
endif ()

# Project internal configuration
set(PROJECT_INSTALL_DIR "${PROJECT_NAME}-${COMPILER}-x86_64-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

add_subdirectory(src)
add_subdirectory(tests)
