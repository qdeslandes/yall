# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#
# CMake co

set(PROJECT_SRCS_COMPILE_FLAGS "-DYALL_UNIT -Dstatic=\"\" -Dinline=\"\"")
set(PROJECT_SRCS_COMPILE_FLAGS "-coverage ${PROJECT_SRCS_COMPILE_FLAGS}")


# Main library
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
  COMMAND ${PROJECT_NAME}_unit
  WORKING_DIRECTORY ${UNIT_TEST_WORKDIR}
  COMMENT "Run builded unit tests"
)

add_custom_target(__coverage_prepare
	COMMAND mkdir -p coverage
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Prepare coverage target")
add_custom_target(coverage
	COMMAND gcov -abcfu `find ${CMAKE_BINARY_DIR} -name \"*.gcda\"`
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
	COMMENT "Run coverage target")
add_dependencies(coverage __coverage_prepare unit)

add_custom_target(resume_coverage
	COMMAND lcov --capture --directory ${CMAKE_CURRENT_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info && genhtml ${CMAKE_BINARY_DIR}/coverage.info --output-directory ${CMAKE_BINARY_DIR}/coverage_info && firefox ${CMAKE_BINARY_DIR}/coverage_info/index.html
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
	COMMENT "Show coverage results in Firefox")
add_dependencies(resume_coverage coverage)
