# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

set(CPACK_GENERATOR "ZIP")

set(CPACK_PACKAGE_NAME "yall")
set(CPACK_PACKAGE_VERSION_MAJOR ${YALL_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${YALL_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${YALL_VERSION_PATCH})

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
	set(DBG "dbg-")
endif ()

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_BUILD_CONFIG}-${COMPILER}-x86_64-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

include(CPack)