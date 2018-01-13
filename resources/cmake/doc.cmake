# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

find_package(Doxygen REQUIRED)

configure_file(${CMAKE_SOURCE_DIR}/resources/Doxyfile.in ${CMAKE_BINARY_DIR}/doc/Doxyfile)

add_custom_target(doxygen_doc
	COMMAND doxygen Doxyfile
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc
	COMMENT "Generate Doxygen documentation")

if (WIN32)
	set_property(TARGET doxygen_doc PROPERTY FOLDER "doc")
endif ()