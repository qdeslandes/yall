# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

configure_file(${CMAKE_SOURCE_DIR}/resources/Doxyfile.in ${CMAKE_BINARY_DIR}/doc/Doxyfile @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/doc/conf.py.in ${CMAKE_BINARY_DIR}/conf.py @ONLY)

add_custom_target(doxygen_doc
	COMMAND doxygen Doxyfile
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc
	COMMENT "Generate Doxygen documentation")

add_custom_target(user_doc
	DEPENDS doxygen_doc
	COMMAND sphinx-build -c ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/doc ${CMAKE_BINARY_DIR}/doc/user
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMENT "Generate Sphinx documentation")

if (WIN32)
	set_property(TARGET doxygen_doc PROPERTY FOLDER "doc")
	set_property(TARGET user_doc PROPERTY FOLDER "doc")
endif ()