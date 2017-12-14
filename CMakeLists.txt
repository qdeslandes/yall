# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

cmake_minimum_required(VERSION 3.6)

project(yall)

include(resources/cmake/utils.cmake)

set(pthread_HINTS "" CACHE STRING "Hint to find pthread directory")
set(criterion_HINTS "" CACHE STRING "Hint to find criterion directory")
option(TARGET_EXT_INFOS "Display extended infos about the CMake targets" OFF)

if (UNIX AND CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE "Release")
endif ()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/resources/cmake/module")

if (WIN32)
	set(pthread_HINTS "${pthread_HINTS}" "${CMAKE_SOURCE_DIR}/external")
endif ()
find_package(pthread REQUIRED)

#[[
	Project version
#]]
set(YALL_VERSION_MAJOR 1)
set(YALL_VERSION_MINOR 3)
set(YALL_VERSION_PATCH 5)
set(YALL_VERSION "${YALL_VERSION_MAJOR}.${YALL_VERSION_MINOR}.${YALL_VERSION_PATCH}")

configure_file("${PROJECT_SOURCE_DIR}/include/version.h.in" "${PROJECT_BINARY_DIR}/generated_headers/version.h")
configure_file("${PROJECT_SOURCE_DIR}/resources/yall.version.in" "${PROJECT_BINARY_DIR}/yall.version")

message("==== Building yall version ${YALL_VERSION_MAJOR}.${YALL_VERSION_MINOR}.${YALL_VERSION_PATCH}")


#[[
	CMake internal configuration
#]]
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED On)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_CONFIGURATION_TYPES "" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Debug;" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Release;" CACHE STRING "" FORCE)

set(CMAKE_DEBUG_POSTFIX d)


#[[
	System specific variables
#]]
if (UNIX)
	if (CMAKE_COMPILER_IS_GNUCC)
		set(COMPILER "gcc-${CMAKE_C_COMPILER_VERSION}")
	else ()
		set(COMPILER "linux_unknow")
	endif ()

	link_directories(${CMAKE_SOURCE_DIR}/external/lib/linux)
elseif (WIN32)
	if (MSVC_VERSION EQUAL 1900)
		set(COMPILER "msvc14")
	elseif (MSVC_VERSION EQUAL 1800)
		set(COMPILER "msvc12")
	else ()
		set(COMPILER "windows_unknow")
	endif ()
endif ()


#[[
	Project
#]]
include(resources/cmake/yall.cmake)


#[[
	Tests
#]]
include(resources/cmake/validate.cmake)
include(resources/cmake/yall_c.cmake)
include(resources/cmake/yall_cpp.cmake)
include(resources/cmake/yall_unit.cmake)
include(resources/cmake/coverage.cmake)
include(resources/cmake/checkstyle.cmake)


#[[
	Deployment
#]]
include(resources/cmake/install.cmake)
include(resources/cmake/package.cmake)
