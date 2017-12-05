# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_executable(yall_c tests/c/main.c)

target_link_libraries(yall_c yall_shared)

target_compile_options(yall_c
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

add_test(NAME yall_c
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
		-c)

binaryInfos(yall_c)