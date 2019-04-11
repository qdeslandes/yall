# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_executable(yall_c main.c)

# Compile options
set(_PVT_OPT -Wall -Wextra -std=gnu11)
set(_PVT_OPT_DEBUG -O0 -g)
set(_PVT_OPT_RELEASE -O3)

target_compile_options(yall_c
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_link_libraries(yall_c PRIVATE yall)

set_target_properties(yall_c PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/external/bin")
