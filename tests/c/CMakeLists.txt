# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#
# CMake configuration for C testing
#

file(GLOB_RECURSE PROJECT_C_SRCS ./*.c)

set(PROJECT_C_OUTPUT_NAME ${PROJECT_NAME}_c)

IF (UNIX)# Build flags
        set(CMAKE_C_FLAGS "${_CMAKE_C_FLAGS}")
        set(CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS} -g -O0")
        set(CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS} -O3")

        # Linked libraries
        set(PROJECT_C_LIBRARIES yall_shared pthread)
ELSEIF (WIN32)
        # Compile flags
        set(CMAKE_C_FLAGS "/wd4127 /wd4210 /wd6031 /wd4706 /wd28252 /wd28253 /wd4172 /wd4100 /wd4204 /wd4221 /Wall /W4 -D_CRT_SECURE_NO_WARNINGS")
        set(CMAKE_C_FLAGS_DEBUG "${_CMAKE_C_FLAGS} /DEBUG /Z7")
        set(CMAKE_C_FLAGS_RELEASE "${_CMAKE_C_FLAGS} /MP")

        # Linked libraries
        set(PROJECT_C_LIBRARIES yall_shared)
ENDIF ()

message("> Add execuable ${PROJECT_NAME}_c : ${PROJECT_C_OUTPUT_NAME}")
message(">     Compile flags       :")
message(">         Debug   : ${CMAKE_C_FLAGS_DEBUG}")
message(">         Release : ${CMAKE_C_FLAGS_RELEASE}")
message(">     Linked libraries    : ${PROJECT_C_LIBRARIES}")


add_executable(${PROJECT_NAME}_c ${PROJECT_C_SRCS})
target_link_libraries(${PROJECT_NAME}_c ${PROJECT_C_LIBRARIES})
set_target_properties(${PROJECT_NAME}_c PROPERTIES OUTPUT_NAME ${PROJECT_C_OUTPUT_NAME})
