# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (WIN32 AND NOT MSVC_VERSION EQUAL 1900)
	return ()
endif ()

if (WIN32)
	set(criterion_HINTS "${criterion_HINTS}" "${CMAKE_SOURCE_DIR}/external")
endif ()
find_package(criterion REQUIRED)

#[[
	Yall sources objects
]]#
file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu11 -coverage)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)
elseif (WIN32)
	# Compile options
	set(_PVT_OPT /wd4820 /wd4255 /wd4127 /wd4210 /wd6031 /wd4706 /wd28252 /wd28253 /wd4172 /wd4100 /wd4204 /wd4221 /Wall)
	set(_PVT_OPT_DEBUG /O0)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)
endif ()

add_library(yall_unit_src_obj OBJECT ${YALL_SRCS})

target_compile_options(yall_unit_src_obj
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_compile_definitions(yall_unit_src_obj
	PUBLIC
		static= inline=)

target_include_directories(yall_unit_src_obj
	PRIVATE
		include
		${pthread_INCLUDE_DIR}
		${CMAKE_BINARY_DIR}/generated_headers)

#[[
	Yall unit tests
]]#
file(GLOB_RECURSE YALL_UNIT_SRCS tests/unit/*.c tests/unit/*.h)

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu11)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)
elseif (WIN32)
	# Compile options
	set(_PVT_OPT /wd4820 /wd4255 /wd4127 /wd4210 /wd6031 /wd4706 /wd28252 /wd28253 /wd4172 /wd4100 /wd4204 /wd4221 /Wall)
	set(_PVT_OPT_DEBUG /O0)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)
endif ()

add_executable(yall_unit $<TARGET_OBJECTS:yall_unit_src_obj> ${YALL_UNIT_SRCS})

target_compile_options(yall_unit
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_include_directories(yall_unit
	PRIVATE
		include
		${pthread_INCLUDE_DIR}
		${CMAKE_BINARY_DIR}/generated_headers
		tests/unit)

target_link_libraries(yall_unit
	PRIVATE
		pthread::pthread
		criterion::criterion
		$<IF:$<C_COMPILER_ID:GNU>,m,>
		$<IF:$<C_COMPILER_ID:GNU>,gcov,>)

if (MSVC_VERSION EQUAL 1900)
	add_custom_target(unit COMMAND yall_unit --ascii WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/bin)
endif ()

targetInfos(yall_unit_src_obj)
targetInfos(yall_unit)
