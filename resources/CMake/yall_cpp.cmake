# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_executable(yall_cpp tests/cpp/main.cpp)
target_link_libraries(yall_cpp yall_shared)

target_compile_options(yall_cpp
	PRIVATE
		-Wall -Wextra -std=gnu++11 -fvisibility=hidden -pedantic -fPIC
		$<$<CONFIG:DEBUG>:-O0 -g>
		$<$<CONFIG:RELEASE>:-O3>)

add_test(NAME yall_cpp
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
		-p)

binaryInfos(yall_cpp)