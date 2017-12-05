# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)

add_library(yall OBJECT ${YALL_SRCS})
add_library(yall_shared SHARED $<TARGET_OBJECTS:yall>)
add_library(yall_static STATIC $<TARGET_OBJECTS:yall>)

target_include_directories(yall
	PUBLIC
		include
	PRIVATE
		${CMAKE_BINARY_DIR}/generated_headers)

target_include_directories(yall_shared PUBLIC include)
target_include_directories(yall_static PUBLIC include)

set_target_properties(yall_shared PROPERTIES
	VERSION "${YALL_VERSION_MAJOR}.${YALL_VERSION_MINOR}.${YALL_VERSION_PATCH}"
	SOVERSION "${YALL_VERSION_MAJOR}.${YALL_VERSION_MINOR}")

if (UNIX)
	target_compile_options(yall
		PRIVATE
			-Wall -Wextra -std=gnu11 -fvisibility=hidden -pedantic -fPIC
			$<$<CONFIG:DEBUG>:-O0 -g>
			$<$<CONFIG:RELEASE>:-O3>)

	target_link_libraries(yall_shared PUBLIC pthread)
	target_link_libraries(yall_static PUBLIC pthread)
elseif (WIN32)
	target_compile_options(yall
		PRIVATE
			/Wall /W4
			$<$<CONFIG:DEBUG>:/DDEBUG>
			$<$<CONFIG:RELEASE>:/MP>)

	target_compile_definitions(yall
		PRIVATE
			_CRT_SECURE_NO_WARNINGS)

	target_include_directories(yall PRIVATE external/include/yall_win32)

	target_link_libraries(yall_shared PUBLIC pthreadVC2)
	target_link_libraries(yall_static PUBLIC pthreadVC2)
endif ()

set_target_properties(yall_shared PROPERTIES OUTPUT_NAME yall)
set_target_properties(yall_static PROPERTIES OUTPUT_NAME yall)

# Show targets infos
binaryInfos(yall)
binaryInfos(yall_shared)
binaryInfos(yall_static)