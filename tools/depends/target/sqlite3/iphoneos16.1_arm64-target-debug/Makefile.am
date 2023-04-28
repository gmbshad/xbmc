
AM_CFLAGS = @BUILD_CFLAGS@ 
lib_LTLIBRARIES = libsqlite3.la
libsqlite3_la_SOURCES = sqlite3.c
libsqlite3_la_LDFLAGS = -no-undefined -version-info 8:6:8

include_HEADERS = sqlite3.h sqlite3ext.h

EXTRA_DIST = sqlite3.1 tea Makefile.msc sqlite3.rc sqlite3rc.h README.txt Replace.cs Makefile.fallback
pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = sqlite3.pc

man_MANS = sqlite3.1
