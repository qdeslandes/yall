# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_executable(yall_cpp tests/cpp/main.cpp)

if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)

	# Link libraries
	set(_PVT_LINKLIB yall)
elseif (WIN32)
	# Compile options

	#[[
		* 4365 : conversion from int to uint64_t
		* 4514 : unreferenced inline function removed
		* 4625 : copy constructor implicitly deleted
		* 4626 : assignment operator implicitly deleted
		* 4710 : function not inlined
		* 4820 : padding
	#]]

	set(_PVT_OPT /wd4365 /wd4514 /wd4625 /wd4626 /wd4710 /wd4820 /Wall)
	set(_PVT_OPT_DEBUG /Od)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)

	# Link libraries
	set(_PVT_LINKLIB yall)
	
	set_property(TARGET yall_cpp PROPERTY FOLDER "tests")
endif ()

target_compile_options(yall_cpp
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_link_libraries(yall_cpp ${_PVT_LINKLIB})

set_target_properties(yall_cpp PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/external/bin")

targetInfos(yall_cpp)
