# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

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
		FILES external/lib/win32/msvc12/pthreadVC2.dll
		DESTINATION bin
		CONFIGURATIONS Release)
endif ()

install(EXPORT yall_targets
	FILE yall_targets.cmake
	DESTINATION lib/cmake/yall
	CONFIGURATIONS Debug)

install(
	FILES
	resources/CMake/yall-config.cmake
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/yall-config-version.cmake"
	DESTINATION lib/cmake/yall
	CONFIGURATIONS Debug)

