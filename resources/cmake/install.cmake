# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/yall-config-version.cmake"
	VERSION ${YALL_VERSION}
	COMPATIBILITY ExactVersion)

configure_package_config_file(
	"resources/cmake/yall-config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/yall-config.cmake"
	INSTALL_DESTINATION lib/cmake/yall)

install(
	FILES README.md
	DESTINATION share/yall
	CONFIGURATIONS Release)

install(
	FILES changelog
	DESTINATION share/yall
	CONFIGURATIONS Release)

install(TARGETS yall EXPORT yall_targets
	RUNTIME DESTINATION bin CONFIGURATIONS Release Debug
	ARCHIVE DESTINATION lib CONFIGURATIONS Release Debug
	LIBRARY DESTINATION lib CONFIGURATIONS Release Debug
	INCLUDES DESTINATION include)

install(
	DIRECTORY ${CMAKE_SOURCE_DIR}/include
	DESTINATION ./
	CONFIGURATIONS Debug
	PATTERN "version.h.in" EXCLUDE)

if (WIN32)
	install(
		FILES external/bin/pthreadVC2.dll
		DESTINATION bin
		CONFIGURATIONS Release)
endif ()

install(
	FILES
		"${CMAKE_BINARY_DIR}/cmake/yall-config.cmake"
		"${CMAKE_BINARY_DIR}/cmake/yall-config-version.cmake"
		"${CMAKE_SOURCE_DIR}/resources/cmake/module/Findpthread.cmake"
	DESTINATION lib/cmake/yall
	CONFIGURATIONS Debug)
	
install(EXPORT yall_targets
	DESTINATION lib/cmake/yall
	NAMESPACE yall::
	CONFIGURATIONS Debug)

if (WIN32)
	install(FILES $<TARGET_PDB_FILE:yall> DESTINATION bin OPTIONAL)
endif ()
