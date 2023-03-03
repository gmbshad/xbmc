set(NATIVEPREFIX "/Users/redd/kodi/x86_64-darwin21.6.0-native")

set(TARBALL_DIR "/Users/Shared/xbmc-depends/xbmc-tarballs")

set(OS "osx")
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CPU "x86_64")

if(OS STREQUAL linux)
  set(CMAKE_SYSTEM_NAME Linux)
elseif(OS STREQUAL osx)
  set(CMAKE_SYSTEM_NAME Darwin)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
  if(CPU STREQUAL "arm")
    set(CPU arm64)
  endif()
  if(CPU STREQUAL arm64)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 11.0)
  else()
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13)
  endif()

  set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")
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

set(CMAKE_C_FLAGS "-arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk -I/Users/redd/kodi/x86_64-darwin21.6.0-native/include")
set(CMAKE_CXX_FLAGS "-std=c++17 -stdlib=libc++ -arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk -I/Users/redd/kodi/x86_64-darwin21.6.0-native/include")
set(CMAKE_EXE_LINKER_FLAGS "-arch x86_64 -mmacosx-version-min=10.13 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk -L/Users/redd/kodi/x86_64-darwin21.6.0-native/lib")

# where is the target environment
set(CMAKE_FIND_ROOT_PATH /Users/redd/kodi/x86_64-darwin21.6.0-native)
set(CMAKE_LIBRARY_PATH /Users/redd/kodi/x86_64-darwin21.6.0-native/lib)
if(NOT "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin" STREQUAL "")
  list(APPEND CMAKE_FIND_ROOT_PATH /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-apple-darwin /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-apple-darwin/sysroot /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-apple-darwin/sysroot/usr /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-apple-darwin/libc /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/lib/x86_64-apple-darwin/sysroot /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/usr /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/sysroot/usr)
  set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}:/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/usr/lib/x86_64-apple-darwin:/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/lib/x86_64-apple-darwin")
endif()
if(NOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk" STREQUAL "")
  list(APPEND CMAKE_FIND_ROOT_PATH /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr)
endif()

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_FRAMEWORK LAST)

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

set(ENV{ACLOCAL_PATH} "${NATIVEPREFIX}/share/aclocal")
set(ENV{PATH} "${NATIVEPREFIX}/bin:$ENV{PATH}")
