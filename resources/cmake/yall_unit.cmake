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

add_library(yall_unit_src_obj OBJECT ${YALL_SRCS})

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu11 -coverage)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)
elseif (WIN32)
	# Compile options

	#[[
		* 4005 : macro redefinition
		* 4172 : returning local variable address (warned on a MSVC file)
		* 4204 : non-const initializer
		* 4668 : macro not defined, replaced by 0
		* 4706 : assignment within conditional expression
		* 4710 : function not inlined
		* 4774 : argument is not a string literal
		* 4996 : "strdup" deprecated
		* 4820 : padding
	#]]

	set(_PVT_OPT /wd4005 /wd4172 /wd4204 /wd4668 /wd4706 /wd4710 /wd4774 /wd4996 /wd4820 /Wall)
	set(_PVT_OPT_DEBUG /Od)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)
	
	set_property(TARGET yall_unit_src_obj PROPERTY FOLDER "tests")
endif ()

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
		include
		${pthread_INCLUDE_DIR}
		${CMAKE_BINARY_DIR}/generated_headers)

#[[
	Yall unit tests
]]#
file(GLOB_RECURSE YALL_UNIT_SRCS tests/unit/*.c tests/unit/*.h)

add_executable(yall_unit $<TARGET_OBJECTS:yall_unit_src_obj> ${YALL_UNIT_SRCS})

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu11)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)
elseif (WIN32)
	# Compile options

	#[[
		* 4204 : non-const initializer
		* 4221 : initialize pointer with automatic variable
		* 4255 : no function prototype given
		* 4267 : conversion from size_t to int
		* 4464 : relative path contains ".." (on Criterion)
		* 4668 : macro not defined, replaced by 0
		* 4710 : function not inlined
		* 4820 : padding
		* 4996 : "strdup" deprecated
	#]]

	set(_PVT_OPT /wd4204 /wd4221 /wd4255 /wd4267 /wd4464 /wd4668 /wd4710 /wd4820 /wd4996 /Wall)
	set(_PVT_OPT_DEBUG /Od)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)
	
	set_property(TARGET yall_unit PROPERTY FOLDER "tests")
endif ()

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
	
	set_property(TARGET unit PROPERTY FOLDER "launch")
endif ()

targetInfos(yall_unit_src_obj)
targetInfos(yall_unit)
