# Makefile settings shared between Makefiles.

CC =  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
CXX =  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
CFLAGS = -fheinous-gnu-extensions -ftree-vectorize -pipe -Wno-trigraphs -fpascal-strings -Wreturn-type -Wunused-variable -fmessage-length=0 -gdwarf-2 -g -D_DEBUG  -arch arm64 -mmacosx-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug/include  -ggdb3 -Wall -W -Wno-sign-compare   -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes   -Wpointer-arith -Wbad-function-cast -Wnested-externs
CXXFLAGS = -stdlib=libc++ -g -D_DEBUG  -std=c++17 -arch arm64 -mmacosx-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug/include 
CCPIC =  
CPPFLAGS = -fheinous-gnu-extensions -ftree-vectorize -pipe -Wno-trigraphs -fpascal-strings -Wreturn-type -Wunused-variable -fmessage-length=0 -gdwarf-2 -g -D_DEBUG  -arch arm64 -mmacosx-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -isystem /Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug/include 
DEFS = -DHAVE_CONFIG_H
LDFLAGS = -L/Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug/lib -Wl,-search_paths_first -L/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk/usr/lib -arch arm64 -mmacosx-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.0.sdk -stdlib=libc++  -liconv  
LIBS = -lgmp 
LIBOBJS = 
EMULATOR = 
NM = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm

OBJEXT = o
EXEEXT = 

CC_FOR_BUILD = gcc -O -g
EXEEXT_FOR_BUILD = 

DEP_FLAGS = -MT $@ -MD -MP -MF $@.d
DEP_PROCESS = true

PACKAGE_BUGREPORT = nettle-bugs@lists.lysator.liu.se
PACKAGE_NAME = nettle
PACKAGE_STRING = nettle 3.7.3
PACKAGE_TARNAME = nettle
PACKAGE_VERSION = 3.7.3

LIBNETTLE_MAJOR = 8
LIBNETTLE_MINOR = 4
LIBNETTLE_SONAME = libnettle.$(LIBNETTLE_MAJOR).dylib
LIBNETTLE_FILE = libnettle.$(LIBNETTLE_MAJOR).$(LIBNETTLE_MINOR).dylib
LIBNETTLE_FILE_SRC = $(LIBNETTLE_FORLINK)
LIBNETTLE_FORLINK = libnettle.dylib
LIBNETTLE_LIBS = 
LIBNETTLE_LINK = $(CC) $(CFLAGS) -dynamiclib $(LDFLAGS) -install_name ${libdir}/$(LIBNETTLE_SONAME) -compatibility_version $(LIBNETTLE_MAJOR) -current_version $(LIBNETTLE_MAJOR).$(LIBNETTLE_MINOR)

LIBHOGWEED_MAJOR = 6
LIBHOGWEED_MINOR = 4
LIBHOGWEED_SONAME = libhogweed.$(LIBHOGWEED_MAJOR).dylib
LIBHOGWEED_FILE = libhogweed.$(LIBHOGWEED_MAJOR).$(LIBHOGWEED_MINOR).dylib
LIBHOGWEED_FILE_SRC = $(LIBHOGWEED_FORLINK)
LIBHOGWEED_FORLINK = libhogweed.dylib
LIBHOGWEED_LIBS = -lnettle $(LIBS)
LIBHOGWEED_LINK = $(CC) $(CFLAGS) -dynamiclib -L. $(LDFLAGS) -install_name ${libdir}/$(LIBHOGWEED_SONAME) -compatibility_version $(LIBHOGWEED_MAJOR) -current_version $(LIBHOGWEED_MAJOR).$(LIBHOGWEED_MINOR)

NUMB_BITS = 64

AR = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar
ARFLAGS = cru
AUTOCONF = autoconf
AUTOHEADER = autoheader
M4 = /Users/Shared/xbmc-depends/x86_64-darwin21.6.0-native/bin/m4
MAKEINFO = makeinfo
RANLIB = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib
LN_S = ln -s

prefix	=	/Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug
exec_prefix =	${prefix}
datarootdir =	${prefix}/share
bindir =	${exec_prefix}/bin
libdir =	${exec_prefix}/lib
includedir =	${prefix}/include
infodir =	${datarootdir}/info
abs_top_builddir = /Users/redd/kodi/tools/depends/target/nettle/macosx13.0_arm64-target-debug

# Absolute name, since some systems require that for LD_LIBRARY_PATH.
TEST_SHLIB_DIR = ${abs_top_builddir}/.lib

# PRE_CPPFLAGS and PRE_LDFLAGS lets each Makefile.in prepend its own
# flags before CPPFLAGS and LDFLAGS. While EXTRA_CFLAGS are added at the end.

COMPILE = $(CC) $(PRE_CPPFLAGS) $(CPPFLAGS) $(DEFS) $(CFLAGS) $(EXTRA_CFLAGS) $(DEP_FLAGS)
COMPILE_CXX = $(CXX) $(PRE_CPPFLAGS) $(CPPFLAGS) $(DEFS) $(CXXFLAGS) $(DEP_FLAGS)
LINK = $(CC) $(CFLAGS) $(PRE_LDFLAGS) $(LDFLAGS)
LINK_CXX = $(CXX) $(CXXFLAGS) $(PRE_LDFLAGS) $(LDFLAGS)

# Default rule. Must be here, since config.make is included before the
# usual targets.
default: all

# Don't use any old-fashioned suffix rules.
.SUFFIXES:

# Disable builtin rule
%$(EXEEXT) : %.c

# Keep object files
.PRECIOUS: %.o

.PHONY: all check install uninstall clean distclean mostlyclean maintainer-clean distdir \
	all-here check-here install-here clean-here distclean-here mostlyclean-here \
	maintainer-clean-here distdir-here \
	install-shared install-info install-headers \
	uninstall-shared uninstall-info uninstall-headers \
	dist distcleancheck
