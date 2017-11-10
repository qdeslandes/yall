# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#
# CMake configuration for unit testing
#
option(PROJECT-UNIT-MODULE_CALL "Enable unit test on call.c sources" ON)
option(PROJECT-UNIT-MODULE_CONFIG "Enable unit test on config.c sources" ON)
option(PROJECT-UNIT-MODULE_CONSOLE "Enable unit test on console.c sources" ON)
option(PROJECT-UNIT-MODULE_DEBUG "Enable unit test on debug.c sources" ON)
option(PROJECT-UNIT-MODULE_FILE "Enable unit test on file.c sources" ON)
option(PROJECT-UNIT-MODULE_HEADER "Enable unit test on header.c sources" ON)
option(PROJECT-UNIT-MODULE_LOG_LEVEL "Enable unit test on log_level.c sources" ON)
option(PROJECT-UNIT-MODULE_MESSAGE "Enable unit test on message.c sources" ON)
option(PROJECT-UNIT-MODULE_SUBSYSTEM "Enable unit test on subsystem.c sources" ON)
option(PROJECT-UNIT-MODULE_WRITER "Enable unit test on writer.c sources" ON)
option(PROJECT-UNIT-MODULE_YALL "Enable unit test on yall.c sources" ON)

file(GLOB_RECURSE PROJECT_UNIT_SRCS helpers/*.c)
file(GLOB_RECURSE PROJECT_SRCS ${CMAKE_SOURCE_DIR}/src/*.c)

if (PROJECT-UNIT-MODULE_CALL)
        file(GLOB_RECURSE _SRCS call/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_CONFIG)
        file(GLOB_RECURSE _SRCS config/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_CONSOLE)
        file(GLOB_RECURSE _SRCS console/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_DEBUG)
        file(GLOB_RECURSE _SRCS debug/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_FILE)
        file(GLOB_RECURSE _SRCS file/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_HEADER)
        file(GLOB_RECURSE _SRCS header/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_LOG_LEVEL)
        file(GLOB_RECURSE _SRCS log_level/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_MESSAGE)
        file(GLOB_RECURSE _SRCS message/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_SUBSYSTEM)
        file(GLOB_RECURSE _SRCS subsystem/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_WRITER)
        file(GLOB_RECURSE _SRCS writer/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

if (PROJECT-UNIT-MODULE_YALL)
        file(GLOB_RECURSE _SRCS yall/*.c)
        set(PROJECT_UNIT_SRCS ${PROJECT_UNIT_SRCS} ${_SRCS})
endif ()

set(PROJECT_UNIT_OUTPUT_NAME ${PROJECT_NAME}_unit-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
set(PROJECT_SRCS_COMPILE_FLAGS "-DYALL_UNIT -Dstatic=\"\" -Dinline=\"\"")

IF (UNIX)
        # Build flags
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${_CMAKE_C_FLAGS_DEBUG} -g -O0")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${_CMAKE_C_FLAGS_RELEASE} -O3")

        if (PROJECT-MISC_COVERAGE)
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
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${_CMAKE_C_FLAGS_DEBUG} /Z7")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${_CMAKE_C_FLAGS_RELEASE} /MP")

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
  COMMAND ${PROJECT_NAME}_unit
  WORKING_DIRECTORY ${UNIT_TEST_WORKDIR}
  COMMENT "Run builded unit tests"
)

if (PROJECT-MISC_COVERAGE)
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
