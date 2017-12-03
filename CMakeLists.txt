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
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)
configure_file("${PROJECT_SOURCE_DIR}/include/version.h.in" "${PROJECT_BINARY_DIR}/generated_headers/version.h")

option(PROJECT_YALL "Build Yall" ON)
option(PROJECT_YALL_SHARED "Enable shared version" ON)
option(PROJECT_YALL_STATIC "Enable static version" ON)
option(PROJECT-MISC_CI_DEPLOY "Special target for continuous integration deployment" OFF)
option(PROJECT-TESTS_UNIT_TESTS "Enable unit tests build" ON)
option(PROJECT-TESTS_C_TESTS "Enable C test build" ON)
option(PROJECT-TESTS_CPP_TESTS "Enable C++ test build" ON)

# CMake internal configuration
set(CMAKE_CONFIGURATION_TYPES "" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Debug;" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Release;" CACHE STRING "" FORCE)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Installation
set(PROJECT_INSTALL_DIR "${PROJECT_NAME}-${COMPILER}-x86_64-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
if (PROJECT-MISC_CI_DEPLOY)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")
endif ()

# Build and platform specific configuration
include_directories(AFTER "include" "external/include" "${PROJECT_BINARY_DIR}/generated_headers")


if (UNIX)
	link_directories("${CMAKE_SOURCE_DIR}/external/lib/linux")
	set(_CMAKE_C_FLAGS "-Wall -Wextra -std=gnu11 -fvisibility=hidden")
    set(_CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 -fvisibility=hidden")

	if (CMAKE_COMPILER_IS_GNUCC)
		set(COMPILER "gcc-${CMAKE_C_COMPILER_VERSION}")
	else ()
		set(COMPILER "gcc_unknow")
	endif ()

	if (CMAKE_BUILD_TYPE MATCHES Debug)
		add_definitions(-DDEBUG)
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

	set(_CMAKE_C_FLAGS_DEBUG "/DDEBUG")
	set(_CMAKE_CXX_FLAGS_DEBUG "/DDEBUG")

	# Specific windows headers directory
	include_directories("${CMAKE_SOURCE_DIR}/external/include/yall_win32")
endif ()

install(FILES README.md DESTINATION share RENAME yall_README.md)
install(FILES changelog DESTINATION share RENAME yall_changelog)

# Target used to validate the validity of the sources modifications
add_custom_target(validate
	COMMAND python3 ./resources/validate.py
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Target used to check the style of the sources modifications
add_custom_target(checkstyle
	COMMAND sh ./resources/checkstyle.sh
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

if (PROJECT_YALL)
	add_subdirectory(src)
endif ()

add_subdirectory(tests)
