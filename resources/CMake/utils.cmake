# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

function(binaryInfos binaryName)

	get_target_property(OUTPUT_NAME ${binaryName} OUTPUT_NAME)
	get_target_property(COMPILE_OPTIONS ${binaryName} COMPILE_OPTIONS)
	get_target_property(COMPILE_DEFINITIONS ${binaryName} COMPILE_DEFINITIONS)
	get_target_property(LINK_LIBRARIES ${binaryName} LINK_LIBRARIES)

	message("> Add binary ${binaryName} : ${OUTPUT_NAME}")
	message(">     Compile flags       : ${COMPILE_OPTIONS}")
	message(">     Compile definitions : ${COMPILE_DEFINITIONS}")
	message(">     Linked libraries    : ${LINK_LIBRARIES}")
endfunction()