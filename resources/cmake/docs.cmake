# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

find_package(Doxygen)

add_custom_target(docs
	COMMAND sphinx-build ${CMAKE_SOURCE_DIR}/docs ${CMAKE_BINARY_DIR}/docs
	COMMENT "Generate documentation")

add_custom_target(show_docs
	COMMAND firefox ${CMAKE_BINARY_DIR}/docs/index.html
	COMMENT "Show docs in Firefox")

configure_file(resources/Doxyfile.in Doxyfile)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxygen)
add_custom_target(doxygen_doc
	COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxygen
	COMMENT "Generating API documentation with Doxygen"
	VERBATIM)