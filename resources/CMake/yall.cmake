# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#[[
	Yall objects compilation
#]]
if (UNIX)
	# Compile options
	set(_PVT_OPT -Wall -Wextra -std=gnu11 -fvisibility=hidden -fPIC)
	set(_PVT_OPT_DEBUG -O0)
	set(_PVT_OPT_RELEASE -O3)
elseif (WIN32)
	# Compile options
	set(_PVT_OPT /wd4820 /wd4255 /wd4127 /wd4210 /wd6031 /wd4706 /wd28252 /wd28253 /wd4172 /wd4100 /wd4204 /wd4221 /Wall)
	set(_PVT_OPT_DEBUG /O0)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)

	# Compile definitions
	set(_PVT_DEF _CRT_SECURE_NO_WARNINGS)
endif ()

file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)

add_library(yall SHARED ${YALL_SRCS})

target_compile_options(yall
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_compile_definitions(yall
	PRIVATE ${_PVT_DEF})

target_include_directories(yall
	PUBLIC 
		${_PUB_INCDIR}
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
		$<INSTALL_INTERFACE:include>
	PRIVATE
		${CMAKE_BINARY_DIR}/generated_headers
		$<IF:$<C_COMPILER_ID:MSVC>,external/include/yall_win32,>)

targetInfos(yall)
