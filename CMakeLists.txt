# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#
# CMake configuration
#

cmake_minimum_required(VERSION 3.6)

project(yall)

enable_testing()

# Set version variables
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0 CACHE STRING "Project version patch")

if (PROJECT_VERSION_PATCH STREQUAL "")
	set(PROJECT_VERSION_PATCH 0)
endif ()

configure_file("${PROJECT_SOURCE_DIR}/include/version.h.in" "${PROJECT_BINARY_DIR}/generated_headers/version.h")

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

	link_directories("${CMAKE_SOURCE_DIR}/external/lib/linux")
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

set_target_properties(yall_shared PROPERTIES
	VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
	SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

if (UNIX)
	target_compile_options(yall
		PRIVATE
			-Wall -Wextra -std=gnu11 -fvisibility=hidden -pedantic -fPIC
			$<$<CONFIG:DEBUG>:-O0 -g>
			$<$<CONFIG:RELEASE>:-O3>)

	target_link_libraries(yall_shared PUBLIC pthread)
	target_link_libraries(yall_static PUBLIC pthread)
elseif (WIN32)
	target_compile_options(yall
		PRIVATE
			/Wall /W4
			$<$<CONFIG:DEBUG>:/DDEBUG>
			$<$<CONFIG:RELEASE>:/MP>)

	target_compile_definitions(yall
		PRIVATE
			_CRT_SECURE_NO_WARNINGS)

	target_link_libraries(yall_shared PUBLIC pthreadVC2)
	target_link_libraries(yall_static PUBLIC pthreadVC2)
endif ()

set_target_properties(yall_shared PROPERTIES OUTPUT_NAME yall)
set_target_properties(yall_static PROPERTIES OUTPUT_NAME yall)


###############
# Tests
###############

add_custom_target(validate
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

##### C #####
add_executable(yall_c tests/c/main.c)
target_link_libraries(yall_c yall_shared)

target_compile_options(yall_c
	PRIVATE
		-Wall -Wextra -std=gnu11 -fvisibility=hidden -pedantic -fPIC
		$<$<CONFIG:DEBUG>:-O0 -g>
		$<$<CONFIG:RELEASE>:-O3>)

add_test(NAME yall_c
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
		-c)

##### C++ #####
add_executable(yall_cpp tests/cpp/main.cpp)
target_link_libraries(yall_cpp yall_shared)

target_compile_options(yall_cpp
	PRIVATE
		-Wall -Wextra -std=gnu++11 -fvisibility=hidden -pedantic -fPIC
		$<$<CONFIG:DEBUG>:-O0 -g>
		$<$<CONFIG:RELEASE>:-O3>)

add_test(NAME yall_cpp
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
		-p)

##### Unit #####
if (NOT WIN32 OR NOT MSVC_VERSION EQUAL 1800)

	# Library objects
	file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)
	add_library(yall_unit_src_obj OBJECT ${YALL_SRCS})

	target_include_directories(yall_unit_src_obj
		PUBLIC include
		PRIVATE ${CMAKE_BINARY_DIR}/generated_headers)

	target_compile_options(yall_unit_src_obj
		PRIVATE -coverage)

	target_compile_definitions(yall_unit_src_obj
		PUBLIC YALL_UNIT static= inline=)

	# Unit tests executable
	file(GLOB_RECURSE YALL_UNIT_SRCS tests/unit/*.c tests/unit/*.h)
	add_executable(yall_unit $<TARGET_OBJECTS:yall_unit_src_obj> ${YALL_UNIT_SRCS})

	target_include_directories(yall_unit
		PRIVATE
			include
			tests/unit
			external/include)

	IF (UNIX)
		target_compile_options(yall_unit
			PRIVATE
				-Wall -Wextra -std=gnu11 -pedantic
				$<$<CONFIG:DEBUG>:-O0 -g>
				$<$<CONFIG:RELEASE>:-O3>)

		target_link_libraries(yall_unit
			PRIVATE
				m
				gcov
				pthread
				criterion)
	ELSEIF (WIN32)
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

	add_test(NAME yall_unit COMMAND yall_unit --verbose WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/lib/win32/msvc14)
endif ()

##### Coverage #####
add_custom_target(__coverage_prepare
	COMMAND mkdir -p coverage
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Prepare coverage target")

add_custom_target(coverage
	COMMAND gcov -abcfu `find ${CMAKE_BINARY_DIR} -name \"*.gcda\"`
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
	COMMENT "Run coverage target")

add_custom_target(resume_coverage
	COMMAND lcov --capture --directory ${CMAKE_CURRENT_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info && genhtml ${CMAKE_BINARY_DIR}/coverage.info --output-directory ${CMAKE_BINARY_DIR}/coverage_info && firefox ${CMAKE_BINARY_DIR}/coverage_info/index.html
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
	COMMENT "Show coverage results in Firefox")

add_dependencies(coverage __coverage_prepare)
add_dependencies(resume_coverage coverage)

add_test(NAME coverage
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
		-o)

##### Checkstyle #####
add_custom_target(checkstyle
	COMMAND sh ./resources/checkstyle.sh
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_test(NAME checkstyle
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
		-s)


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

set(CPACK_PACKAGE_NAME "yall")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${COMPILER}-x86_64-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

include(CPack)