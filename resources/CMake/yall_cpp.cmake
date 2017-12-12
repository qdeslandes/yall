# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)

	# Link libraries
	set(_PVT_LINKLIB yall)
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

add_executable(yall_cpp tests/cpp/main.cpp)

target_compile_options(yall_cpp
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_include_directories(yall_cpp
	PRIVATE ${_PVT_INCDIR})

target_link_libraries(yall_cpp ${_PVT_LINKLIB})

targetInfos(yall_cpp)
