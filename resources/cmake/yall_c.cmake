# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_executable(yall_c tests/c/main.c)

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu11)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)

	# Link libraries
	set(_PVT_LINKLIB yall)
elseif (WIN32)
	# Compile options

	#[[
		* 4115 : named type defininition in parenthesis
		* 4820 : padding
	#]]

	set(_PVT_OPT /wd4115 /wd4820 /Wall)
	set(_PVT_OPT_DEBUG /Od)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)

	# Link libraries
	set(_PVT_LINKLIB yall)
	
	set_property(TARGET yall_c PROPERTY FOLDER "tests")
endif ()

target_compile_options(yall_c
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_link_libraries(yall_c ${_PVT_LINKLIB})

set_target_properties(yall_c PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/external/bin")

targetInfos(yall_c)
