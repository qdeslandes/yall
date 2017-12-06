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

	# Include directories
	set(_PUB_INCDIR include)
	set(_PVT_INCDIR ${CMAKE_BINARY_DIR}/generated_headers)
elseif (WIN32)
	# Compile options
	set(_PVT_OPT /Wall)
	set(_PVT_OPT_DEBUG /O0)
	set(_PVT_OPT_RELEASE /W4 /O2 /MP)

	# Compile definitions
	set(_PVT_DEF _CRT_SECURE_NO_WARNINGS)

	# Include directories
	set(_PUB_INCDIR include)
	set(_PVT_INCDIR ${CMAKE_BINARY_DIR}/generated_headers external/include/yall_win32)
endif ()

file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)

add_library(yall OBJECT ${YALL_SRCS})

target_compile_options(yall
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_compile_definitions(yall
	PRIVATE ${_PVT_DEF})

target_include_directories(yall
	PUBLIC ${_PUB_INCDIR}
	PRIVATE ${_PVT_INCDIR})

#[[
	Yall dynamic linking
#]]
if (UNIX)
	# Include directories
	set(_PUB_INCDIR include)
elseif (WIN32)
	# Include directories
	set(_PUB_INCDIR include)

	# Link libraries
	set(_PVT_LINKLIB pthreadVC2)
endif ()

add_library(yall_shared SHARED $<TARGET_OBJECTS:yall>)

target_include_directories(yall_shared
	PUBLIC ${_PUB_INCDIR})

target_link_libraries(yall_shared
	PUBLIC ${_PVT_LINKLIB})

set_target_properties(yall_shared PROPERTIES OUTPUT_NAME yall)

set_target_properties(yall_shared PROPERTIES
	VERSION "${YALL_VERSION_MAJOR}.${YALL_VERSION_MINOR}.${YALL_VERSION_PATCH}"
	SOVERSION "${YALL_VERSION_MAJOR}.${YALL_VERSION_MINOR}")

#[[
	Yall static linking
#]]
if (UNIX)
	# Include directories
	set(_PUB_INCDIR include)
elseif (WIN32)
	# Include directories
	set(_PUB_INCDIR include)

	# Link libraries
	set(_PVT_LINKLIB pthreadVC2)
endif ()

add_library(yall_static STATIC $<TARGET_OBJECTS:yall>)

target_include_directories(yall_static
	PUBLIC ${_PUB_INCDIR})

set_target_properties(yall_static PROPERTIES OUTPUT_NAME yall)

targetInfos(yall)
targetInfos(yall_shared)
targetInfos(yall_static)
