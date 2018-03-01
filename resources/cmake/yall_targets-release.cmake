#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "yall::yall" for configuration "Release"
set_property(TARGET yall::yall APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(yall::yall PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libyall.so"
  IMPORTED_SONAME_RELEASE "libyall.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS yall::yall )
list(APPEND _IMPORT_CHECK_FILES_FOR_yall::yall "${_IMPORT_PREFIX}/lib/libyall.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)