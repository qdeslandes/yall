# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

configure_file(${CMAKE_SOURCE_DIR}/resources/Doxyfile.in ${CMAKE_BINARY_DIR}/doc/Doxyfile @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/doc/conf.py.in ${CMAKE_BINARY_DIR}/conf.py @ONLY)

add_custom_target(_doxygen_doc
	COMMAND doxygen Doxyfile
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc
	COMMENT "Generate Doxygen documentation")

add_custom_target(_coverage_doc
	COMMAND LC_ALL=C lcov --base-directory ${CMAKE_SOURCE_DIR} --directory ${CMAKE_BINARY_DIR} -c -o ${CMAKE_BINARY_DIR}/coverage.info
	COMMAND LC_ALL=C lcov --remove ${CMAKE_BINARY_DIR}/coverage.info "*jansson*" -o ${CMAKE_BINARY_DIR}/coverage.info
	COMMAND LC_ALL=C genhtml ${CMAKE_BINARY_DIR}/coverage.info --output-directory ${CMAKE_BINARY_DIR}/out/public/coverage)

add_custom_target(_user_doc
	COMMAND sphinx-build -c ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/doc ${CMAKE_BINARY_DIR}/out/public
	COMMAND touch ${CMAKE_BINARY_DIR}/out/public/.nojekyll
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMENT "Generate Sphinx documentation")

add_custom_target(doc
	DEPENDS _doxygen_doc _coverage_doc _user_doc)

if (WIN32)
    set_target_properties(doc PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif ()
