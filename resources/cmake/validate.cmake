# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (UNIX)
	add_custom_target(validate_full
		COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
			--sourcesDir ${CMAKE_SOURCE_DIR}
			--buildDir ${CMAKE_BINARY_DIR}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Validate sources and binaries")

	add_custom_target(validate
		COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
			--sourcesDir ${CMAKE_SOURCE_DIR}
			--buildDir ${CMAKE_BINARY_DIR}
			-cpuos
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Validate sources and binaries")
endif ()
