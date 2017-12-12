# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu11)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)

	# Link libraries
	set(_PVT_LINKLIB yall pthread)
elseif (WIN32)
	# Compile options
	set(_PVT_OPT /Wall)
	set(_PVT_OPT_DEBUG /O0)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)

	# Include directories
	set(_PVT_INCDIR external/include/yall_win32)

	# Link libraries
	set(_PVT_LINKLIB yall)
endif ()

add_executable(yall_c tests/c/main.c)

target_compile_options(yall_c
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_include_directories(yall_c
	PRIVATE ${_PVT_INCDIR})

target_link_libraries(yall_c ${_PVT_LINKLIB})

targetInfos(yall_c)
