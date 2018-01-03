# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (NOT UNIX)
	return ()
endif ()

add_custom_target(__coverage_prepare
	COMMAND mkdir -p coverage
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Prepare coverage target")

add_custom_target(coverage
	COMMAND gcov -abcfu `find ${CMAKE_BINARY_DIR} -name \"*.gcda\"`
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
	COMMENT "Run coverage target")

add_custom_target(show_coverage
	COMMAND
		lcov --capture
			--directory ${CMAKE_CURRENT_BINARY_DIR}
			--output-file ${CMAKE_BINARY_DIR}/coverage.info &&
		genhtml ${CMAKE_BINARY_DIR}/coverage.info
			--output-directory ${CMAKE_BINARY_DIR}/coverage_info &&
		firefox ${CMAKE_BINARY_DIR}/coverage_info/index.html
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
	COMMENT "Show coverage results in Firefox")

add_dependencies(coverage __coverage_prepare)
