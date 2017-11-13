# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#
# CMake configuration for cpp testing
#

file(GLOB_RECURSE PROJECT_CPP_SRCS ./*.cpp)

set(PROJECT_CPP_OUTPUT_NAME ${PROJECT_NAME}_cpp)

IF (UNIX)# Build flags
        set(CMAKE_CXX_FLAGS "${_CMAKE_CXX_FLAGS}")
        set(CMAKE_CXX_FLAGS_DEBUG "${_CMAKE_CXX_FLAGS} ${_CMAKE_CXX_FLAGS_DEBUG} -g -O0")
        set(CMAKE_CXX_FLAGS_RELEASE "${_CMAKE_CXX_FLAGS} ${_CMAKE_CXX_FLAGS_RELEASE} -O3")

        # Linked libraries
        set(PROJECT_CPP_LIBRARIES yall_shared pthread)
ELSEIF (WIN32)
        # Compile flags
        set(CMAKE_CXX_FLAGS "/wd4127 /wd4210 /wd6031 /wd4706 /wd28252 /wd28253 /wd4172 /wd4100 /wd4204 /wd4221 /Wall /W4 -D_CRT_SECURE_NO_WARNINGS")
        set(CMAKE_CXX_FLAGS_DEBUG "${_CMAKE_CXX_FLAGS} ${_CMAKE_CXX_FLAGS_DEBUG} /Z7")
        set(CMAKE_CXX_FLAGS_RELEASE "${_CMAKE_CXX_FLAGS} ${_CMAKE_CXX_FLAGS_RELEASE} /MP")

        # Linked libraries
        set(PROJECT_CPP_LIBRARIES yall_shared)
ENDIF ()

message("> Add execuable ${PROJECT_NAME}_cpp : ${PROJECT_CPP_OUTPUT_NAME}")
message(">     Compile flags       :")
message(">         Debug   : ${CMAKE_CXX_FLAGS_DEBUG}")
message(">         Release : ${CMAKE_CXX_FLAGS_RELEASE}")
message(">     Linked libraries    : ${PROJECT_CPP_LIBRARIES}")


add_executable(${PROJECT_NAME}_cpp ${PROJECT_CPP_SRCS})
target_link_libraries(${PROJECT_NAME}_cpp ${PROJECT_CPP_LIBRARIES})
set_target_properties(${PROJECT_NAME}_cpp PROPERTIES OUTPUT_NAME ${PROJECT_CPP_OUTPUT_NAME})
