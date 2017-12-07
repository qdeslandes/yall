# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

cmake_minimum_required(VERSION 3.6)

project(yall)

include(resources/CMake/utils.cmake)

option(TARGET_EXT_INFOS "Display extended infos about the CMake targets" OFF)

#[[
	Project version
#]]
set(YALL_VERSION_MAJOR 1)
set(YALL_VERSION_MINOR 2)
set(YALL_VERSION_PATCH 1)

configure_file("${PROJECT_SOURCE_DIR}/include/version.h.in" "${PROJECT_BINARY_DIR}/generated_headers/version.h")
configure_file("${PROJECT_SOURCE_DIR}/resources/version.sh.in" "${PROJECT_BINARY_DIR}/version.sh")

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

	link_directories(${CMAKE_SOURCE_DIR}/external/lib/win32/${COMPILER})
endif ()


#[[
	Project
#]]
include(resources/CMake/yall.cmake)


#[[
	Tests
#]]
enable_testing()

include(resources/CMake/validate.cmake)
include(resources/CMake/yall_c.cmake)
include(resources/CMake/yall_cpp.cmake)
include(resources/CMake/yall_unit.cmake)
include(resources/CMake/coverage.cmake)
include(resources/CMake/checkstyle.cmake)


#[[
	Deployment
#]]
include(resources/CMake/install.cmake)
include(resources/CMake/package.cmake)
