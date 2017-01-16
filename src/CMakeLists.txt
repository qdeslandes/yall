#
# CMake configuration for main library
#

set(PROJECT_OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
file(GLOB_RECURSE PROJECT_SRCS ./*.c)

IF (UNIX)
	# Compile flags
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -O0")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")

	# Linked libraries
	set(PROJETC_LINK_LIBRARIES
		m
		pthread)
ELSEIF (WIN32)
	# Compile flags
	set(CMAKE_C_FLAGS "/wd4127 /wd4210 /wd6031 /wd4706 /wd28252 /wd28253 /wd4172 /wd4100 /wd4204 /wd4221 /Wall /W4 -D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} /MP")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} /DEBUG")

	# Linked libraries
	set(PROJECT_LINK_LIBRARIES
		pthreadVC2)
ENDIF ()


# CMake logging
message("> Add execuable ${PROJECT_NAME} : ${PROJECT_OUTPUT_NAME}")
message(">     Compile flags       :")
message(">         Debug   : ${CMAKE_C_FLAGS_DEBUG}")
message(">         Release : ${CMAKE_C_FLAGS_RELEASE}")
message(">     Linked libraries    : ${PROJETC_LINK_LIBRARIES}")


# Target parameters
# Here, we create an object library, from these objects we create shared and
# static library.
add_library(${PROJECT_NAME} OBJECT ${PROJECT_SRCS})
add_library(${PROJECT_NAME}_shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}>)
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)

target_link_libraries(${PROJECT_NAME}_shared ${PROJETC_LINK_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_static ${PROJECT_LINK_LIBRARIES})

set(PROJECT_OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_OUTPUT_NAME})
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_OUTPUT_NAME})


# Installation
if (PROJECT_CI_DEPLOY)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")
else ()
	set(CMAKE_INSTALL_PREFIX "/usr/local")
endif ()

install(FILES ${CMAKE_SOURCE_DIR}/README.md DESTINATION ${CMAKE_INSTALL_PREFIX}/)
install(FILES ${CMAKE_SOURCE_DIR}/COPYING DESTINATION ${CMAKE_INSTALL_PREFIX}/)
install(TARGETS ${PROJECT_NAME}_shared ${PROJECT_NAME}_static
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	ARCHIVE	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX})


# Make dist
add_custom_target(dist COMMAND ${CMAKE_COMMAND} -E tar "cfvz" "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}.tgz" "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_DIR}")
