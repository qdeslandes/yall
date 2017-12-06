# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (WIN32 AND NOT MSVC_VERSION EQUAL 1900)
	return ()
endif ()

#[[
	Yall sources objects
]]#
file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu11 -coverage)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)

	# Compile definitions
	set(_PVT_DEF YALL_UNIT static= inline=)

	# Include directories
	set(_PVT_INCDIR include tests/unit ${CMAKE_BINARY_DIR}/generated_headers)

	# Link libraries
	set(_PVT_LINKLIB m gcov pthread criterion)
elseif (WIN32)
	# Compile options
	set(_PVT_OPT /Wall)
	set(_PVT_OPT_DEBUG /O0)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)

	# Compile definitions
	set(_PVT_DEF YALL_UNIT static= inline=)

	# Include directories
	set(_PVT_INCDIR include tests/unit ${CMAKE_BINARY_DIR}/generated_headers external/include/yall_win32)

	# Link libraries
	set(_PVT_LINKLIB criterion pthreadVC2)
endif ()

add_library(yall_unit_src_obj OBJECT ${YALL_SRCS})

target_compile_options(yall_unit_src_obj
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_compile_definitions(yall_unit_src_obj
	PUBLIC
		${_PVT_DEF})

target_include_directories(yall_unit_src_obj
	PRIVATE
		${_PVT_INCDIR})

set_property(TARGET yall_unit_src_obj PROPERTY C_STANDARD 11)
set_property(TARGET yall_unit_src_obj PROPERTY C_STANDARD_REQUIRED ON)

#[[
	Yall unit tests
]]#
file(GLOB_RECURSE YALL_UNIT_SRCS tests/unit/*.c tests/unit/*.h)

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu11)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)

	# Include directories
	set(_PVT_INCDIR include tests/unit external/include)

	# Link libraries
	set(_PVT_LINKLIB m gcov pthread criterion)
elseif (WIN32)
	# Compile options
	set(_PVT_OPT /Wall)
	set(_PVT_OPT_DEBUG /O0)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)

	# Include directories
	set(_PVT_INCDIR include tests/unit external/include external/include/yall_win32)

	# Link libraries
	set(_PVT_LINKLIB criterion pthreadVC2)
endif ()

add_executable(yall_unit $<TARGET_OBJECTS:yall_unit_src_obj> ${YALL_UNIT_SRCS})

target_compile_options(yall_unit
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_include_directories(yall_unit
	PRIVATE
		${_PVT_INCDIR})

target_link_libraries(yall_unit
	PRIVATE
		${_PVT_LINKLIB})

set_property(TARGET yall_unit PROPERTY C_STANDARD 11)
set_property(TARGET yall_unit PROPERTY C_STANDARD_REQUIRED ON)

if (MSVC_VERSION EQUAL 1900)
	add_custom_target(unit COMMAND yall_unit WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/lib/win32/msvc14)
endif ()