# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

#[[
	Yall objects compilation
#]]

file(GLOB_RECURSE YALL_SRCS ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/include/*.h)

add_library(yall SHARED ${YALL_SRCS})

# For more infos about the used flags :
#	* https://stackoverflow.com/questions/3375697/useful-gcc-flags-for-c
#	* https://kristerw.blogspot.fr/2017/09/useful-gcc-warning-options-not-enabled.html
# Compile options
set(_PVT_OPT -Wall -Wextra -Wconversion -ftrapv -Wfloat-equal -Wundef
    -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes
    -Wwrite-strings -Waggregate-return -Wuninitialized
    -Wduplicated-cond -Wlogical-op -Wnull-dereference -Wdouble-promotion
    -fvisibility=hidden -fPIC)
set(_PVT_OPT_DEBUG  -O0 -g)
set(_PVT_OPT_RELEASE -O3 -Werror)

target_compile_options(yall
	PRIVATE
		${_PVT_OPT}
		$<$<CONFIG:DEBUG>:${_PVT_OPT_DEBUG}>
		$<$<CONFIG:RELEASE>:${_PVT_OPT_RELEASE}>)

target_compile_definitions(yall
	PRIVATE ${_PVT_DEF})

target_include_directories(yall
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		${CMAKE_BINARY_DIR}/generated_headers)

target_link_libraries(yall
	PUBLIC
		pthread::pthread
	PRIVATE
		jansson::jansson)


#[[
    Installing target
#]]

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_BINARY_DIR}/cmake/yall-config-version.cmake"
	VERSION ${YALL_VERSION}
	COMPATIBILITY ExactVersion)

configure_package_config_file(
	"${CMAKE_SOURCE_DIR}/resources/cmake/yall-config.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake/yall-config.cmake"
	INSTALL_DESTINATION lib/cmake/yall)

if (UNIX)
	configure_file(${CMAKE_SOURCE_DIR}/resources/cmake/yall_targets-release.cmake.linux ${CMAKE_BINARY_DIR}/cmake/yall_targets-release.cmake COPYONLY)
else ()
	configure_file(${CMAKE_SOURCE_DIR}/resources/cmake/yall_targets-release.cmake.windows ${CMAKE_BINARY_DIR}/cmake/yall_targets-release.cmake COPYONLY)
endif ()

install(
	FILES ${CMAKE_SOURCE_DIR}/README.md
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

install(
	FILES
		"${CMAKE_BINARY_DIR}/cmake/yall-config.cmake"
		"${CMAKE_BINARY_DIR}/cmake/yall-config-version.cmake"
		"${CMAKE_BINARY_DIR}/cmake/yall_targets-release.cmake"
		"${CMAKE_SOURCE_DIR}/resources/cmake/module/Findpthread.cmake"
	DESTINATION lib/cmake/yall
	CONFIGURATIONS Debug)
	
install(EXPORT yall_targets
	DESTINATION lib/cmake/yall
	NAMESPACE yall::
	CONFIGURATIONS Debug)


#[[
	Packaging
#]]
set(CPACK_GENERATOR "DEB;ZIP;RPM")

set(CPACK_OUTPUT_FILE_PREFIX out/packages)
set(CPACK_PACKAGE_NAME "yall")
set(CPACK_PACKAGE_VERSION_MAJOR ${YALL_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${YALL_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${YALL_VERSION_PATCH})

set(CPACK_COMPILER ${COMPILER})
set(CPACK_YALL_BUILD_TYPE ${CMAKE_BUILD_TYPE})

set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_SOURCE_DIR}/resources/cmake/cpack_config_file.cmake)

include(CPack)