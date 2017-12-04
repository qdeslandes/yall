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

option(PROJECT-MISC_CI_DEPLOY "Special target for continuous integration deployment" OFF)
option(PROJECT-TESTS_UNIT_TESTS "Enable unit tests build" ON)
option(PROJECT-TESTS_C_TESTS "Enable C test build" ON)
option(PROJECT-TESTS_CPP_TESTS "Enable C++ test build" ON)
enable_testing()
# CMake internal configuration
set(CMAKE_CONFIGURATION_TYPES "" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Debug;" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}Release;" CACHE STRING "" FORCE)

set(CMAKE_DEBUG_POSTFIX d)

if (UNIX)
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

	# Specific windows headers directory
	include_directories("${CMAKE_SOURCE_DIR}/external/include/yall_win32")

	install(FILES external/lib/win32/msvc12/pthreadVC2.dll DESTINATION bin)
endif ()


set(PROJECT_INSTALL_DIR "${PROJECT_NAME}-${COMPILER}-x86_64-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
if (PROJECT-MISC_CI_DEPLOY)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")
endif ()


###############
# yall library
###############

file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)

add_library(yall OBJECT ${YALL_SRCS})
add_library(yall_shared SHARED $<TARGET_OBJECTS:yall>)
add_library(yall_static STATIC $<TARGET_OBJECTS:yall>)

target_include_directories(yall
	PUBLIC
		include
	PRIVATE
		${CMAKE_BINARY_DIR}/generated_headers)

target_include_directories(yall_shared PUBLIC include)
target_include_directories(yall_static PUBLIC include)

if (UNIX)
	target_compile_options(yall
		PRIVATE
			-Wall -Wextra -std=gnu11 -fvisibility=hidden -pedantic -fPIC
			$<$<CONFIG:DEBUG>:-O0 -g>
			$<$<CONFIG:RELEASE>:-O3>)
elseif (WIN32)
	target_compile_options(yall
		PRIVATE
			/Wall /W4
			$<$<CONFIG:DEBUG>:/DDEBUG>
			$<$<CONFIG:RELEASE>:/MP>)

	target_compile_definitions(yall
		PRIVATE
			_CRT_SECURE_NO_WARNINGS)

	target_link_libraries(yall_shared pthreadVC2)
	target_link_libraries(yall_static pthreadVC2)
endif ()

set_target_properties(yall_shared PROPERTIES OUTPUT_NAME yall)
set_target_properties(yall_static PROPERTIES OUTPUT_NAME yall)


###############
# Tests
###############

if (PROJECT-TESTS_C_TESTS)
	add_executable(yall_c tests/c/main.c)
	target_link_libraries(yall_c yall_static)

	add_test(NAME c COMMAND yall_c)
endif ()

if (PROJECT-TESTS_CPP_TESTS)
	add_executable(yall_cpp tests/cpp/main.cpp)
	target_link_libraries(yall_cpp yall_static)

	add_test(NAME cpp COMMAND yall_cpp)
endif ()

# Unit testing can't be done on MSVC 12 because Criterion is not available
if ((NOT WIN32 OR NOT MSVC_VERSION EQUAL 1800) AND PROJECT-TESTS_UNIT_TESTS)
	file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)
	file(GLOB_RECURSE YALL_UNIT_SRCS tests/unit/*.c tests/unit/*.h)

	add_executable(yall_unit ${YALL_SRCS} ${YALL_UNIT_SRCS})

	target_include_directories(yall_unit
		PRIVATE
			include
			${CMAKE_BINARY_DIR}/generated_headers
			tests/unit
			external/include)

	IF (UNIX)
		#set_source_files_properties(${YALL_SRCS} PROPERTIES COMPILE_FLAGS "-coverage /DYALL_UNIT /Dstatic=\"\" /Dinline=\"\"")
		target_compile_options(yall_unit
			PRIVATE
				-Wall -Wextra -std=gnu11 -pedantic
				$<$<CONFIG:DEBUG>:-O0 -g>
				$<$<CONFIG:RELEASE>:-O3>)

		target_link_libraries(yall_unit
			PRIVATE
				m
				pthread
				gcov
				criterion)
	ELSEIF (WIN32)
		set_source_files_properties(${YALL_SRCS} PROPERTIES COMPILE_FLAGS "/DYALL_UNIT /Dstatic=\"\" /Dinline=\"\"")

		target_compile_options(yall_unit
			PRIVATE
				/Wall /W4
				$<$<CONFIG:DEBUG>:/DDEBUG /Z7>
				$<$<CONFIG:RELEASE>:/MP>)

		target_link_libraries(yall_unit
			PRIVATE
				pthreadVC2
				criterion)
	ENDIF ()

	set(ENV{CTEST_OUTPUT_ON_FAILURE} "On")
	add_test(NAME unit COMMAND yall_unit --verbose WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/lib/win32/msvc14)
endif ()


###############
# Installation
###############
install(FILES README.md DESTINATION share/yall)
install(FILES changelog DESTINATION share/yall)

install(TARGETS yall_static yall_shared
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ./ PATTERN "version.h.in" EXCLUDE)


###############
# Package
###############
set(CPACK_GENERATOR "ZIP")
include(CPack)