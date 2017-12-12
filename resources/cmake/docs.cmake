# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

add_custom_target(docs
	COMMAND sphinx-build ${CMAKE_SOURCE_DIR}/docs ${CMAKE_BINARY_DIR}/docs
	COMMENT "Generate documentation")

add_custom_target(show_docs
	COMMAND firefox ${CMAKE_BINARY_DIR}/docs/index.html
	COMMENT "Show docs in Firefox")
