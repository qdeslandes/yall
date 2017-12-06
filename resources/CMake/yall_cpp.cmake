# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu++11)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)

	# Link libraries
	set(_PVT_LINKLIB yall_shared)
elseif (WIN32)
	# Compile options
	set(_PVT_OPT /Wall)
	set(_PVT_OPT_DEBUG /O0)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)

	# Link libraries
	set(_PVT_LINKLIB yall_shared)
endif ()

add_executable(yall_cpp tests/cpp/main.cpp)

target_compile_options(yall_cpp
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_link_libraries(yall_cpp ${_PVT_LINKLIB})

add_test(NAME yall_cpp
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
		-p)
