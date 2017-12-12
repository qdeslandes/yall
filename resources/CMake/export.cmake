# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/yall-config-version.cmake"
	VERSION ${YALL_VERSION}
	COMPATIBILITY SameMajorVersion)

export(EXPORT yall_targets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/yall_targets.cmake")

