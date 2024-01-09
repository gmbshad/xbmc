set(NATIVEPREFIX "/Users/redd/kodi/.xbmc-depends/x86_64-darwin-native")

set(TARBALL_DIR "/Users/redd/kodi/.xbmc-depends/xbmc-tarballs")

set(OS "osx")
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CPU "x86_64")
set(ARCH_DEFINES -DTARGET_POSIX -DTARGET_DARWIN -DTARGET_DARWIN_OSX)

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
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)
  endif()

  set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")
endif()
set(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
set(CMAKE_C_COMPILER /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang)
set(CMAKE_CXX_COMPILER /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++)
set(CMAKE_AR /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar CACHE FILEPATH "Archiver")
SET(CMAKE_AS /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/as CACHE FILEPATH "Assembler")
set(CMAKE_LINKER /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ld CACHE FILEPATH "Linker")
set(CMAKE_NM /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm CACHE FILEPATH "Nm")
set(CMAKE_STRIP /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip CACHE PATH "strip binary" FORCE)
set(CMAKE_OBJDUMP /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump CACHE FILEPATH "Objdump")
set(CMAKE_RANLIB /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib CACHE FILEPATH "Ranlib")

if(NOT "no" STREQUAL "")
  set(CMAKE_CXX_COMPILER_LAUNCHER )
  set(CMAKE_C_COMPILER_LAUNCHER )
endif()

set(CMAKE_C_FLAGS "-arch x86_64 -mmacosx-version-min=10.14 -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/Users/redd/kodi/.xbmc-depends/x86_64-darwin-native/include")
set(CMAKE_CXX_FLAGS "-std=c++17 -stdlib=libc++ -arch x86_64 -mmacosx-version-min=10.14 -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/Users/redd/kodi/.xbmc-depends/x86_64-darwin-native/include")
set(CMAKE_EXE_LINKER_FLAGS "-arch x86_64 -mmacosx-version-min=10.14 -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -L/Users/redd/kodi/.xbmc-depends/x86_64-darwin-native/lib")

# where is the target environment
set(CMAKE_FIND_ROOT_PATH /Users/redd/kodi/.xbmc-depends/x86_64-darwin-native)
set(CMAKE_LIBRARY_PATH /Users/redd/kodi/.xbmc-depends/x86_64-darwin-native/lib)
if(NOT "/Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin" STREQUAL "")
  list(APPEND CMAKE_FIND_ROOT_PATH /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-darwin /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-darwin/sysroot /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-darwin/sysroot/usr /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/x86_64-darwin/libc /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/lib/x86_64-darwin/sysroot /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/usr /Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/sysroot/usr)
  set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}:/Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/usr/lib/x86_64-darwin:/Applications/Utilities/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/lib/x86_64-darwin")
endif()
if(NOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk" STREQUAL "")
  list(APPEND CMAKE_FIND_ROOT_PATH /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr)
endif()

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_FRAMEWORK LAST)

set(ENV{PATH} "${NATIVEPREFIX}/bin:$ENV{PATH}")
