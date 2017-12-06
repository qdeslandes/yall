# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (NOT UNIX)
	return()
endif ()

add_custom_target(checkstyle
	COMMAND sh ./resources/checkstyle.sh
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMENT "Run checkstyle on yall sources")
