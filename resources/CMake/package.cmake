# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (UNIX)
    set(CPACK_GENERATOR "DEB;ZIP;RPM")
elseif (WIN32)
    set(CPACK_GENERATOR "ZIP")
endif ()

SET(CPACK_OUTPUT_FILE_PREFIX packages)
set(CPACK_PACKAGE_NAME "yall")
set(CPACK_PACKAGE_VERSION_MAJOR ${YALL_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${YALL_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${YALL_VERSION_PATCH})

set(CPACK_COMPILER ${COMPILER})
set(CPACK_YALL_BUILD_TYPE ${CMAKE_BUILD_TYPE})

set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_SOURCE_DIR}/resources/cpack_config_file.cmake)

include(CPack)