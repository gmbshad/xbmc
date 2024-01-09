#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libcec::cec" for configuration "Debug"
set_property(TARGET libcec::cec APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libcec::cec PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libcec.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libcec.dylib"
  )

list(APPEND _cmake_import_check_targets libcec::cec )
list(APPEND _cmake_import_check_files_for_libcec::cec "${_IMPORT_PREFIX}/lib/libcec.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
