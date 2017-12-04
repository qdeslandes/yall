# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For de
##################################

# Target used to validate the validity of the sources modifications
add_custom_target(validate
	COMMAND python3 ./resources/validate.py
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Target used to check the style of the sources modifications
add_custom_target(checkstyle
	COMMAND sh ./resources/checkstyle.sh
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# this is the "object library" target: compiles the sources only once


set_target_properties(yall_shared PROPERTIES
        VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
        SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

#

target_link_libraries(yall_static ${PROJECT_LINK_LIBRARIES})
set_target_properties(yall_static PROPERTIES OUTPUT_NAME ${PROJECT_OUTPUT_NAME})
set_target_properties(yall_static PROPERTIES
        VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
