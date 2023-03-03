set(DEPENDS_PATH "/Users/redd/kodi/macosx13.0_x86_64-target-debug")
set(NATIVEPREFIX "/Users/redd/kodi/x86_64-darwin21.6.0-native")

set(TARBALL_DIR "/Users/Shared/xbmc-depends/xbmc-tarballs")

set(OS "osx")
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CPU "x86_64")
set(PLATFORM "macosx")

# set CORE_SYSTEM_NAME and CMAKE_SYSTEM_NAME (sets CMAKE_CROSSCOMPILING)
if(OS STREQUAL linux)
  set(CMAKE_SYSTEM_NAME Linux)
  set(CORE_SYSTEM_NAME linux)
  set(CORE_PLATFORM_NAME macosx)
  set(APP_RENDER_SYSTEM  CACHE STRING "Render system to use: \"gl\" or \"gles\"")
elseif(OS STREQUAL android)
  set(CMAKE_SYSTEM_NAME Android)
  set(CORE_SYSTEM_NAME android)
elseif(OS STREQUAL osx)
  set(CMAKE_SYSTEM_NAME Darwin)
  set(CORE_SYSTEM_NAME osx)
elseif(OS STREQUAL darwin_embedded)
  set(CMAKE_SYSTEM_NAME Darwin)
  set(CORE_SYSTEM_NAME darwin_embedded)
  if(PLATFORM STREQUAL appletvos)
    set(CORE_PLATFORM_NAME tvos)
  else()
    set(CORE_PLATFORM_NAME ios)
  endif()
endif()

if(CORE_SYSTEM_NAME STREQUAL darwin_embedded)
  # Necessary to build the main Application (but not other dependencies)
  # with Xcode (and a bundle with Makefiles) (https://cmake.org/Bug/view.php?id=15329)
  if(NOT PROJECT_SOURCE_DIR MATCHES "tools/depends")
    message(STATUS "Toolchain enabled ${CORE_PLATFORM_NAME} bundle for project ${PROJECT_NAME}")
    set(CMAKE_MACOSX_BUNDLE YES)
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")
    # Need to set this attribute to "" in order to
    # completely disable code signing
    # see: https://gitlab.kitware.com/cmake/cmake/issues/19112
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")
    set(CMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE "NO")
    if(CORE_PLATFORM_NAME STREQUAL tvos)
      set(CMAKE_XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "3")
      set(CMAKE_XCODE_ATTRIBUTE_TVOS_DEPLOYMENT_TARGET 11.0)
    else()
      set(CMAKE_XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
      set(CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 11.0)
    endif()
  endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
  set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk)
  set(CMAKE_XCODE_ATTRIBUTE_ARCHS ${CPU})
endif()
set(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
set(CMAKE_C_COMPILER /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang)
set(CMAKE_CXX_COMPILER /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++)
set(CMAKE_AR /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar CACHE FILEPATH "Archiver")
SET(CMAKE_AS /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/as CACHE FILEPATH "Assembler")
set(CMAKE_LINKER /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ld CACHE FILEPATH "Linker")
set(CMAKE_NM /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm CACHE FILEPATH "Nm")
set(CMAKE_STRIP /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip CACHE PATH "strip binary" FORCE)
set(CMAKE_OBJDUMP /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump CACHE FILEPATH "Objdump")
set(CMAKE_RANLIB /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib CACHE FILEPATH "Ranlib")

if(NOT "no" STREQUAL "")
  set(CMAKE_CXX_COMPILER_LAUNCHER )
  set(CMAKE_C_COMPILER_LAUNCHER )
endif()

# where is the target environment
set(CMAKE_FIND_ROOT_PATH /Users/redd/kodi/macosx13.0_x86_64-target-debug)
set(CMAKE_LIBRARY_PATH /Users/redd/kodi/macosx13.0_x86_64-target-debug/lib)
if(NOT "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin" STREQUAL "")
  list(APPEND CMAKE_FIND_ROOT_PATH /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-apple-darwin /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-apple-darwin/sysroot /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-apple-darwin/sysroot/usr /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-apple-darwin/libc /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/lib/x86_64-apple-darwin/sysroot /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/usr /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/sysroot/usr)
  set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}:/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/usr/lib/x86_64-apple-darwin:/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/lib/x86_64-apple-darwin")
endif()
if(NOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk" STREQUAL "")
  list(APPEND CMAKE_FIND_ROOT_PATH /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk/usr)
endif()

# add Android directories and tools
if(CORE_SYSTEM_NAME STREQUAL android)
  set(NDKROOT )
  set(SDKROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk)
  set(TOOLCHAIN /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin)
  set(HOST x86_64-apple-darwin)
  list(APPEND CMAKE_LIBRARY_PATH ${TOOLCHAIN}/sysroot/usr/lib/${HOST}/21)
  string(REPLACE ":" ";" SDK_BUILDTOOLS_PATH "")
endif()

set(CMAKE_C_FLAGS "-fheinous-gnu-extensions -g -D_DEBUG  -arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/redd/kodi/macosx13.0_x86_64-target-debug/include")
set(CMAKE_CXX_FLAGS "-stdlib=libc++ -g -D_DEBUG  -std=c++17 -arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/redd/kodi/macosx13.0_x86_64-target-debug/include")
set(CMAKE_C_FLAGS_RELEASE "-fheinous-gnu-extensions -DNDEBUG=1   -arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/redd/kodi/macosx13.0_x86_64-target-debug/include")
set(CMAKE_CXX_FLAGS_RELEASE "-stdlib=libc++ -DNDEBUG=1   -arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/redd/kodi/macosx13.0_x86_64-target-debug/include")
set(CMAKE_C_FLAGS_DEBUG "-fheinous-gnu-extensions -g -D_DEBUG  -arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/redd/kodi/macosx13.0_x86_64-target-debug/include")
set(CMAKE_CXX_FLAGS_DEBUG "-stdlib=libc++ -g -D_DEBUG  -arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/redd/kodi/macosx13.0_x86_64-target-debug/include")
set(CMAKE_CPP_FLAGS "-fheinous-gnu-extensions -g -D_DEBUG  -arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/redd/kodi/macosx13.0_x86_64-target-debug/include")
set(CMAKE_EXE_LINKER_FLAGS "-L/Users/redd/kodi/macosx13.0_x86_64-target-debug/lib -Wl,-search_paths_first -arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -stdlib=libc++ /Users/redd/Documents/ffmpeg/libavcodec -liconv ")
set(ENV{CFLAGS} ${CMAKE_C_FLAGS})
set(ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS})
set(ENV{CPPFLAGS} ${CMAKE_CPP_FLAGS})
set(ENV{LDFLAGS} ${CMAKE_EXE_LINKER_FLAGS})
# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_FRAMEWORK LAST)
set(ENV{PKG_CONFIG_LIBDIR} /Users/redd/kodi/macosx13.0_x86_64-target-debug/lib/pkgconfig:/Users/redd/kodi/macosx13.0_x86_64-target-debug/share/pkgconfig)

# Binary Addons
if(NOT CORE_SYSTEM_NAME STREQUAL linux)
  set(ADDONS_PREFER_STATIC_LIBS ON)
endif()

# common usage in autoconf to refer to host arch tool use
set(CC_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang")
set(CXX_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++")
set(LD_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ld")
set(CC_BINARY_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang")
set(CXX_BINARY_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++")
set(AR_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar")
set(RANLIB_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib")
set(AS_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/as")
set(NM_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm")
set(STRIP_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip")
set(READELF_FOR_BUILD "")
set(OBJDUMP_FOR_BUILD "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")

# flags for host arch building
set(CFLAGS_FOR_BUILD "-arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk -I/Users/redd/kodi/x86_64-darwin21.6.0-native/include")
set(LDFLAGS_FOR_BUILD "-arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk -L/Users/redd/kodi/x86_64-darwin21.6.0-native/lib")

# other build tools
find_program(NASM nasm HINTS "${NATIVEPREFIX}/bin" REQUIRED)

# common autoconf build tools
find_program(AUTOCONF autoconf HINTS "${NATIVEPREFIX}/bin" REQUIRED)
find_program(ACLOCAL aclocal HINTS "${NATIVEPREFIX}/bin" REQUIRED)
find_program(AUTOHEADER autoheader HINTS "${NATIVEPREFIX}/bin" REQUIRED)
find_program(AUTOMAKE automake HINTS "${NATIVEPREFIX}/bin" REQUIRED)
find_program(AUTOM4TE autom4te HINTS "${NATIVEPREFIX}/bin" REQUIRED)
find_program(AUTOPOINT autopoint HINTS "${NATIVEPREFIX}/bin" REQUIRED)
find_program(AUTORECONF autoreconf HINTS "${NATIVEPREFIX}/bin" REQUIRED)
find_program(LIBTOOL libtool HINTS "${NATIVEPREFIX}/bin" REQUIRED)
find_program(LIBTOOLIZE libtoolize HINTS "${NATIVEPREFIX}/bin" REQUIRED)

set(ENV{ACLOCAL_PATH} "${DEPENDS_PATH}/share/aclocal:${NATIVEPREFIX}/share/aclocal")
set(ENVPATH "${NATIVEPREFIX}/bin:$ENV{PATH}")

# Dependency build tool config files
find_file(MESON-CROSS "cross-file.meson" PATHS "${DEPENDS_PATH}/share" NO_CMAKE_FIND_ROOT_PATH REQUIRED)
# autoconf config.site
find_file(CONFIG_SITE "config.site" PATHS "${DEPENDS_PATH}/share" NO_CMAKE_FIND_ROOT_PATH REQUIRED)

# Env variables for non cmake target environments
set(PROJECT_TARGETENV "AS=${CMAKE_AS}"
                      "AR=${CMAKE_AR}"
                      "CC=${CMAKE_C_COMPILER}"
                      "CXX=${CMAKE_CXX_COMPILER}"
                      "NM=${CMAKE_NM}"
                      "LD=${CMAKE_LINKER}"
                      "STRIP=${CMAKE_STRIP}"
                      "RANLIB=${CMAKE_RANLIB}"
                      "OBJDUMP=${CMAKE_OBJDUMP}"
                      "CFLAGS=${CMAKE_C_FLAGS}"
                      "CPPFLAGS=${CMAKE_CPP_FLAGS}"
                      "LDFLAGS=${CMAKE_EXE_LINKER_FLAGS}"
                      "PKG_CONFIG_LIBDIR=$ENV{PKG_CONFIG_LIBDIR}"
                      "AUTOM4TE=${AUTOM4TE}"
                      "AUTOMAKE=${AUTOMAKE}"
                      "AUTOCONF=${AUTOCONF}"
                      "AUTORECONF=${AUTORECONF}"
                      "ACLOCAL=${ACLOCAL}"
                      "ACLOCAL_PATH=$ENV{ACLOCAL_PATH}"
                      "AUTOPOINT=${AUTOPOINT}"
                      "AUTOHEADER=${AUTOHEADER}"
                      "LIBTOOL=${LIBTOOL}"
                      "LIBTOOLIZE=${LIBTOOLIZE}"
                      "CONFIG_SITE=${CONFIG_SITE}"
                      )

# Env variables for non cmake host environments
set(PROJECT_BUILDENV CC_FOR_BUILD=${CC_FOR_BUILD}
                     CXX_FOR_BUILD=${CXX_FOR_BUILD}
                     LD_FOR_BUILD=${LD_FOR_BUILD}
                     CC_BINARY_FOR_BUILD=${CC_FOR_BUILD}
                     CXX_BINARY_FOR_BUILD=${CXX_FOR_BUILD}
                     AR_FOR_BUILD=${AR_FOR_BUILD}
                     RANLIB_FOR_BUILD=${RANLIB_FOR_BUILD}
                     AS_FOR_BUILD=${AS_FOR_BUILD}
                     NM_FOR_BUILD=${NM_FOR_BUILD}
                     STRIP_FOR_BUILD=${STRIP_FOR_BUILD}
                     READELF_FOR_BUILD=${READELF_FOR_BUILD}
                     OBJDUMP_FOR_BUILD=${OBJDUMP_FOR_BUILD}
                     CFLAGS_FOR_BUILD=${CFLAGS_FOR_BUILD}
                     LDFLAGS_FOR_BUILD=${LDFLAGS_FOR_BUILD}
                     )

# variable to easily set host/target env for non cmake internal dep builds
set(DEP_BUILDENV ${CMAKE_COMMAND} -E env ${PROJECT_TARGETENV} ${PROJECT_BUILDENV})

set(KODI_DEPENDSBUILD 1)

