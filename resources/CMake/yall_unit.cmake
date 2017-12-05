# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (NOT WIN32 OR NOT MSVC_VERSION EQUAL 1800)

	# Library objects
	file(GLOB_RECURSE YALL_SRCS src/*.c include/*.h)
	add_library(yall_unit_src_obj OBJECT ${YALL_SRCS})

	target_include_directories(yall_unit_src_obj
		PUBLIC include
		PRIVATE ${CMAKE_BINARY_DIR}/generated_headers)

	target_compile_options(yall_unit_src_obj
		PRIVATE -coverage)

	target_compile_definitions(yall_unit_src_obj
		PUBLIC YALL_UNIT static= inline=)

	# Unit tests executable
	file(GLOB_RECURSE YALL_UNIT_SRCS tests/unit/*.c tests/unit/*.h)
	add_executable(yall_unit $<TARGET_OBJECTS:yall_unit_src_obj> ${YALL_UNIT_SRCS})

	target_include_directories(yall_unit
		PRIVATE
			include
			tests/unit
			external/include)

	IF (UNIX)
		target_compile_options(yall_unit
			PRIVATE
				-Wall -Wextra -std=gnu11 -pedantic
				$<$<CONFIG:DEBUG>:-O0 -g>
				$<$<CONFIG:RELEASE>:-O3>)

		target_link_libraries(yall_unit
			PRIVATE
				m
				gcov
				pthread
				${CMAKE_SOURCE_DIR}/external/lib/linux/libcriterion.so)
	ELSEIF (WIN32)
		target_compile_options(yall_unit
			PRIVATE
				/Wall /W4
				$<$<CONFIG:DEBUG>:/DDEBUG /Z7>
				$<$<CONFIG:RELEASE>:/MP>)

		target_include_directories(yall_unit_src_obj PRIVATE external/include/yall_win32)
		target_include_directories(yall_unit PRIVATE external/include/yall_win32)

		target_link_libraries(yall_unit
			PRIVATE
				pthreadVC2
				criterion)
	ENDIF ()

	add_test(NAME yall_unit
		COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
			--sourcesDir ${CMAKE_SOURCE_DIR}
			--buildDir ${CMAKE_BINARY_DIR}
			-u)

	binaryInfos(yall_unit_src_obj)
	binaryInfos(yall_unit)
endif ()