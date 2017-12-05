# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_custom_target(checkstyle
	COMMAND sh ./resources/checkstyle.sh
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_test(NAME checkstyle
	COMMAND python3 ${CMAKE_SOURCE_DIR}/resources/validate.py
		--sourcesDir ${CMAKE_SOURCE_DIR}
		--buildDir ${CMAKE_BINARY_DIR}
		-s)