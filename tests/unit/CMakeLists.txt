# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.


#[[
	Yall sources objects
]]#
file(GLOB_RECURSE YALL_SRCS ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/include/*.h)

add_library(yall_unit_src_obj OBJECT ${YALL_SRCS})

# Compile options
set(_PVT_OPT -fprofile-arcs -ftest-coverage  -Wall -Wextra -std=gnu11)
set(_PVT_OPT_DEBUG -O0 -g)
set(_PVT_OPT_RELEASE -O3)

target_compile_options(yall_unit_src_obj
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_compile_definitions(yall_unit_src_obj
	PUBLIC
		YALL_UNIT static= inline=)

target_include_directories(yall_unit_src_obj
	PRIVATE
		${CMAKE_SOURCE_DIR}/include
		${pthread_INCLUDE_DIR}
		${CMAKE_BINARY_DIR}/generated_headers)
	
set_target_properties(yall_unit_src_obj PROPERTIES EXCLUDE_FROM_ALL On)

#[[
	Yall unit tests
]]#
file(GLOB_RECURSE YALL_UNIT_SRCS *.c *.h)

add_executable(yall_unit $<TARGET_OBJECTS:yall_unit_src_obj> ${YALL_UNIT_SRCS})

# Compile options
set(_PVT_OPT -Wall -Wextra -std=gnu11)
set(_PVT_OPT_DEBUG -O0 -g)
set(_PVT_OPT_RELEASE -O3)

target_compile_options(yall_unit
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_include_directories(yall_unit
	PRIVATE
		${CMAKE_SOURCE_DIR}/include
		${CMAKE_BINARY_DIR}/generated_headers
		${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(yall_unit
	PRIVATE
		pthread::pthread
		jansson::jansson
		criterion::criterion
		$<IF:$<C_COMPILER_ID:GNU>,m,>
		$<IF:$<C_COMPILER_ID:GNU>,gcov,>)
