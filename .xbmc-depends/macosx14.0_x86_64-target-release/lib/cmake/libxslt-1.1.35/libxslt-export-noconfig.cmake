#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "LibXslt::LibXslt" for configuration ""
set_property(TARGET LibXslt::LibXslt APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(LibXslt::LibXslt PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libxslt.a"
  )

list(APPEND _cmake_import_check_targets LibXslt::LibXslt )
list(APPEND _cmake_import_check_files_for_LibXslt::LibXslt "${_IMPORT_PREFIX}/lib/libxslt.a" )

# Import target "LibXslt::LibExslt" for configuration ""
set_property(TARGET LibXslt::LibExslt APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(LibXslt::LibExslt PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libexslt.a"
  )

list(APPEND _cmake_import_check_targets LibXslt::LibExslt )
list(APPEND _cmake_import_check_files_for_LibXslt::LibExslt "${_IMPORT_PREFIX}/lib/libexslt.a" )

# Import target "LibXslt::xsltproc" for configuration ""
set_property(TARGET LibXslt::xsltproc APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(LibXslt::xsltproc PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/xsltproc"
  )

list(APPEND _cmake_import_check_targets LibXslt::xsltproc )
list(APPEND _cmake_import_check_files_for_LibXslt::xsltproc "${_IMPORT_PREFIX}/bin/xsltproc" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
