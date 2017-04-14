# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#
# CMake configuration for unit testing
#

file(GLOB_RECURSE PROJECT_UNIT_SRCS ./*.c)
file(GLOB_RECURSE PROJECT_SRCS ${CMAKE_SOURCE_DIR}/src/*.c)

set(PROJECT_UNIT_OUTPUT_NAME ${PROJECT_NAME}_unit-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
set(PROJECT_SRCS_COMPILE_FLAGS "-DYALL_UNIT")

set_source_files_properties(${PROJECT_SRCS} PROPERTIES COMPILE_DEFINITIONS static=)

IF (UNIX)# Build flags
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -O0")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")

	if (PROJECT_COVERAGE)
		# This is used to enable coverage analyse only on yall sources
        set(PROJECT_SRCS_COMPILE_FLAGS "-coverage ${PROJECT_SRCS_COMPILE_FLAGS}")
	endif ()

	# Linked libraries
	set(PROJECT_UNIT_LIBRARIES
		m
		pthread
		gcov
		criterion)
ELSEIF (WIN32)
	# Compile flags
	set(CMAKE_C_FLAGS "/wd4127 /wd4210 /wd6031 /wd4706 /wd28252 /wd28253 /wd4172 /wd4100 /wd4204 /wd4221 /Wall /W4 -D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} /DEBUG /Z7")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} /MP")

	# Linked libraries
	set(PROJECT_UNIT_LIBRARIES
		pthreadVC2
		criterion)
ENDIF ()

message("> Add execuable ${PROJECT_NAME} : ${PROJECT_UNIT_OUTPUT_NAME}")
message(">     Compile flags       :")
message(">         Debug   : ${CMAKE_C_FLAGS_DEBUG}")
message(">         Release : ${CMAKE_C_FLAGS_RELEASE}")
message(">     Linked libraries    : ${PROJECT_UNIT_LIBRARIES}")


# Main library
add_executable(${PROJECT_NAME}_unit ${PROJECT_UNIT_SRCS} ${PROJECT_SRCS})
include_directories("helpers")
target_link_libraries(${PROJECT_NAME}_unit ${PROJECT_UNIT_LIBRARIES})
set_target_properties(${PROJECT_NAME}_unit PROPERTIES OUTPUT_NAME ${PROJECT_UNIT_OUTPUT_NAME})
set_source_files_properties(${PROJECT_SRCS} PROPERTIES COMPILE_FLAGS ${PROJECT_SRCS_COMPILE_FLAGS})

if (UNIX)
	set(UNIT_TEST_WORKDIR ${CMAKE_SOURCE_DIR}/external/lib/linux)
elseif (WIN32)
	# Unit test are running only for MSVC14
	if (MSVC_VERSION EQUAL 1900)
		set(UNIT_TEST_WORKDIR ${CMAKE_SOURCE_DIR}/external/lib/win32/msvc14)
	endif ()
endif ()

add_custom_target(unit
  COMMAND ${PROJECT_NAME}_unit -j1 --verbose=1
  WORKING_DIRECTORY ${UNIT_TEST_WORKDIR}
  COMMENT "Run builded unit tests"
)

if (PROJECT_COVERAGE)
	add_custom_target(coverage_prepare
		COMMAND mkdir -p coverage
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Prepare coverage target")
	add_custom_target(coverage
		COMMAND gcov -abcfu `find ${CMAKE_BINARY_DIR} -name \"*.gcda\"`
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
		COMMENT "Run coverage target")
	add_dependencies(coverage coverage_prepare unit)

	add_custom_target(resume_coverage
		COMMAND lcov --capture --directory ${CMAKE_CURRENT_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info && genhtml ${CMAKE_BINARY_DIR}/coverage.info --output-directory ${CMAKE_BINARY_DIR}/coverage_info && firefox ${CMAKE_BINARY_DIR}/coverage_info/index.html
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
		COMMENT "Show coverage results in Firefox")
	add_dependencies(resume_coverage coverage)
endif ()
