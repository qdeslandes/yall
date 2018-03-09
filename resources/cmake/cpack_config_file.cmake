# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

if (UNIX)
	if (CPACK_YALL_BUILD_TYPE MATCHES Release)
		set(_CONFIG "")
	elseif (CPACK_YALL_BUILD_TYPE MATCHES Debug)
		set(_CONFIG "dev-")
	endif ()
elseif (WIN32)
	if (CPACK_BUILD_CONFIG MATCHES Release)
		set(_CONFIG "")
	elseif (CPACK_BUILD_CONFIG MATCHES Debug)
		set(_CONFIG "dev-")
	endif ()
endif ()

set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${_CONFIG}${CPACK_COMPILER}-x86_64-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

if (UNIX)
	# Red Hat package
	set(CPACK_RPM_PACKAGE_LICENSE "MIT")
	set(CPACK_RPM_PACKAGE_URL "https://github.com/Naccyde/yall")
	set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
	set(CPACK_RPM_PACKAGE_VENDOR "naccyde")
	set(CPACK_RPM_PACKAGE_DESCRIPTION "\nYALL is a subsystems based logging library.")

	if (CPACK_YALL_BUILD_TYPE MATCHES Release)
		set(CPACK_RPM_PACKAGE_NAME yall)
		set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
		set(CPACK_RPM_PACKAGE_SUMMARY "yall library")
		set(CPACK_RPM_PACKAGE_REQUIRES "jansson")
	elseif (CPACK_YALL_BUILD_TYPE MATCHES Debug)
	set(CPACK_RPM_PACKAGE_NAME yall-devel)
		set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
		set(CPACK_RPM_PACKAGE_SUMMARY "yall development library")
		set(CPACK_RPM_PACKAGE_REQUIRES "yall >= ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}, jansson-devel")
	endif ()

	# Debian package
	set(CPACK_DEBIAN_PACKAGE_MAINTAINER "naccyde@naccyde.eu")
	set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "YALL is a subsystems based logging library.")
	set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/Naccyde/yall")

	if (CPACK_YALL_BUILD_TYPE MATCHES Release)
		set(CPACK_DEBIAN_PACKAGE_NAME yall)
		set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
		set(CPACK_DEBIAN_PACKAGE_SECTION "Libraries")
		set(CPACK_DEBIAN_PACKAGE_DEPENDS "libjansson4")
	elseif (CPACK_YALL_BUILD_TYPE MATCHES Debug)
		set(CPACK_DEBIAN_PACKAGE_NAME yall-dev)
		set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
		set(CPACK_DEBIAN_PACKAGE_DEPENDS "yall (>= ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}), libjansson-dev")
		set(CPACK_DEBIAN_PACKAGE_SECTION "Library development")
	endif ()
endif ()
