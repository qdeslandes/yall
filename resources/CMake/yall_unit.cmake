# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (WIN32 AND NOT MSVC_VERSION EQUAL 1800)
	return ()
endif ()

#[[
	Yall sources objects
]]#
file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)
add_library(yall_unit_src_obj OBJECT ${YALL_SRCS})

target_compile_options(yall_unit_src_obj
	PRIVATE
		$<IF:$<C_COMPILER_ID:GNU>,-coverage,>)

target_compile_definitions(yall_unit_src_obj
	PUBLIC
		YALL_UNIT static= inline=)
		
target_include_directories(yall_unit_src_obj
	PUBLIC
		include
	PRIVATE
		${CMAKE_BINARY_DIR}/generated_headers
		$<IF:$<C_COMPILER_ID:MSVC>,external/include/yall_win32,>)

target_compile_options(yall_unit_src_obj
	PRIVATE
		$<IF:$<C_COMPILER_ID:GNU>,
			-Wall -Wextra -Werror -std=gnu11 -pedantic
			$<$<CONFIG:DEBUG>:-O0 -g>
			$<$<CONFIG:RELEASE>:-O3>
		,>
		$<IF:$<C_COMPILER_ID:MSVC>,
			/Wall
			$<$<CONFIG:DEBUG>:/O0>
			$<$<CONFIG:RELEASE>:/W4 /O2>
		,>
	)

binaryInfos(yall_unit_src_obj)

#[[
	Yall unit tests
]]#
file(GLOB_RECURSE YALL_UNIT_SRCS tests/unit/*.c tests/unit/*.h)
add_executable(yall_unit $<TARGET_OBJECTS:yall_unit_src_obj> ${YALL_UNIT_SRCS})

target_include_directories(yall_unit
	PRIVATE
		include
		tests/unit
		external/include
		$<IF:$<C_COMPILER_ID:MSVC>,external/include/yall_win32,>)

target_compile_options(yall_unit
	PRIVATE
		$<IF:$<C_COMPILER_ID:GNU>,
			-Wall -Wextra -Werror -std=gnu11 -pedantic
			$<$<CONFIG:DEBUG>:-O0 -g>
			$<$<CONFIG:RELEASE>:-O3>
		,>
		$<IF:$<C_COMPILER_ID:MSVC>,
			/Wall
			$<$<CONFIG:DEBUG>:/O0>
			$<$<CONFIG:RELEASE>:/W4 /O2 /MP>
		,>
	)

target_link_libraries(yall_unit
	PRIVATE
		$<IF:$<C_COMPILER_ID:GNU>,m gcov pthread criterion,>
		$<IF:$<C_COMPILER_ID:MSVC>,pthreadVC2 criterion,>
	)

add_test(NAME yall_unit
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
		-u)

binaryInfos(yall_unit)