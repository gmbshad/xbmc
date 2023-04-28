#include <ma_config.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <mariadb_version.h>
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#if defined(__FreeBSD__) || defined(__DragonFly__)
#include <sys/sysctl.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <unistd.h>
#ifdef HAVE_LINUX_LIMITS_H
#include <linux/limits.h>
#endif
#include <string.h>
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

static char *mariadb_progname;

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define INCLUDE "-I%s/include/mariadb -I%s/include/mariadb/mysql"
#define LIBS    "-L%s/lib/mariadb/ -lmariadb"
#define LIBS_SYS "-l/Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug/lib/libssl.a -l/Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug/lib/libcrypto.a"
#define CFLAGS  INCLUDE
#define VERSION "10.8.4"
#define CC_VERSION "3.3.2"
#define PLUGIN_DIR "%s/lib/mariadb/plugin"
#define SOCKET  "/tmp/mysql.sock"
#define PORT "3306"
#ifdef HAVE_TLS
#define TLS_LIBRARY_VERSION "OpenSSL 1.1.1n"
#else
#define TLS_LIBRARY_VERSION ""
#endif
#define PKG_INCLUDEDIR "%s/include/mariadb"
#define PKG_PLUGINDIR "%s/lib/mariadb/plugin"
#define PKG_LIBDIR "%s/lib/mariadb"

#ifdef HAVE_EMBEDDED
#define EMBEDDED_LIBS "-L/Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug/lib/mariadb/ -lmariadbd -l/Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug/lib/libssl.a -l/Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug/lib/libcrypto.a"
#endif

#if defined(SOLARIS) || defined(__sun)
#define OPT_STRING_TYPE (char *)
#else
#define OPT_STRING_TYPE
#endif
static struct option long_options[]=
{
  {OPT_STRING_TYPE "cflags", no_argument, 0, 'a'},
  {OPT_STRING_TYPE "help", no_argument, 0, 'b'},
  {OPT_STRING_TYPE "include", no_argument, 0, 'c'},
  {OPT_STRING_TYPE "libs", no_argument, 0, 'd'},
  {OPT_STRING_TYPE "libs_r", no_argument, 0, 'e'},
  {OPT_STRING_TYPE "libs_sys", no_argument, 0, 'l'},
  {OPT_STRING_TYPE "version", no_argument, 0, 'f'},
  {OPT_STRING_TYPE "cc_version", no_argument, 0, 'g'},
  {OPT_STRING_TYPE "socket", no_argument, 0, 'h'},
  {OPT_STRING_TYPE "port", no_argument, 0, 'i'},
  {OPT_STRING_TYPE "plugindir", no_argument, 0, 'j'},
  {OPT_STRING_TYPE "tlsinfo", no_argument, 0, 'k'},
  {OPT_STRING_TYPE "variable", 2, 0, 'm'},
#ifdef HAVE_EMBEDDED
  {OPT_STRING_TYPE "libmysqld-libs", no_argument, 0, 'n' },
  {OPT_STRING_TYPE "embedded-libs", no_argument, 0, 'n' },
  {OPT_STRING_TYPE "embedded", no_argument, 0, 'n' },
#endif
  {NULL, 0, 0, 0}
};

static struct  {
  const char *variable;
  const char *value;
} variables[] = {
  {"pkgincludedir", PKG_INCLUDEDIR},
  {"pkglibdir", PKG_LIBDIR},
  {"pkgplugindir", PKG_PLUGINDIR},
  {NULL, NULL}
};

char installation_dir[PATH_MAX];

static const char *values[]=
{
  CFLAGS,
  NULL,
  INCLUDE,
  LIBS,
  LIBS,
  LIBS_SYS,
  VERSION,
  CC_VERSION,
  SOCKET,
  PORT,
  PLUGIN_DIR,
  TLS_LIBRARY_VERSION,
  "VAR  VAR is one of:"
#ifdef HAVE_EMBEDDED
  ,EMBEDDED_LIBS
#endif
};

void usage(void)
{
  int i=0;
  puts("Copyright 2011-2020 MariaDB Corporation AB");
  puts("Get compiler flags for using the MariaDB Connector/C.");
  printf("Usage: %s [OPTIONS]\n", mariadb_progname);
  printf("Compiler: Clang 14.0.0.14000029\n");
  while (long_options[i].name)
  {
    if (!long_options[i].has_arg)
    {
      if (values[i])
      {
        printf("  --%-12s  [", long_options[i].name);
        printf(values[i], installation_dir, installation_dir);
        printf("]\n");
      }
    } else
    {
      printf("  --%s=%s\n", long_options[i].name, values[i]);
      /* Variables */
      if (long_options[i].val ==  'm')
      {
        int i= 0;
        while (variables[i].variable)
        {
          printf("      %-14s [", variables[i].variable);
          printf(variables[i].value, installation_dir);
          printf("]\n");
          i++;
        }
      }        
    }
    
    i++;
  }
}

/*
  mariadb_get_install_location()
  Tries to find the installation location in the following order:
  1) check if MARIADB_CONFIG environment variable was set
  2) try to determine the installation directory from executable path
  3) Fallback if 1 and 2 failed: use CMAKE_SYSROOT/CMAKE_INSTALL_PREFIX
*/ 
static void mariadb_get_install_location()
{
  char *p= NULL;
  struct stat s;

  /* Check environment variable MARIADB_CONFIG */
  if ((p= getenv("MARIADB_CONFIG")))
  {
    if (!stat(p, &s) && S_ISREG(s.st_mode))
    {
      goto end;
    }
  }
  /* Try to determine path of executable */
  if (!(p= alloca(PATH_MAX)))
    goto end;
  else {
#if defined(__APPLE__)
    unsigned int len= PATH_MAX;
    if (_NSGetExecutablePath(p, &len) != 0)
      *p= 0;
    else
    {
      p[len]= 0;
      if (realpath(p, p) != 0)
        *p= 0;
    }
#elif defined(__sun) || defined(SOLARIS)
    if (realpath(getexecname(), p) == NULL)
      *p= 0;
#elif defined(__NetBSD__)
    ssize_t len= readlink("/proc/curproc/exe", p, PATH_MAX);
    if (len == -1 || len == PATH_MAX)
      *p= 0;
    else
      p[len]= 0;
#elif defined(__FreeBSD__) || defined(__DragonFly__)
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1};
    size_t cb = PATH_MAX;
    if (sysctl(mib, 4, p, &cb, NULL, 0) == -1)
      *p= 0;
    else
      p[cb]= 0;
#elif defined(__linux__)
    ssize_t len= readlink("/proc/self/exe", p, PATH_MAX);
    if (len == -1 || len == PATH_MAX)
      *p= 0;
    else
      p[len]= 0;
#else
    *p= 0;
#endif
  }
end:
  if (p && p[0])
  {
    char *c, *search= alloca(6 + strlen(mariadb_progname));
    sprintf(search, "/bin/%s", mariadb_progname);
    c= strstr(p, search);
    if (c)
    {
      strncpy(installation_dir, p, c - p);
    }
    else
      *p=0;
  }
  if (!p || !p[0])
  {
    strncpy(installation_dir, "/Users/Shared/xbmc-depends/macosx13.0_arm64-target-debug", PATH_MAX - 1);
    return;
  }
}

int main(int argc, char **argv)
{
  int c;
  char *p = strrchr(argv[0], '/');
  mariadb_progname= p ? p + 1 : argv[0];

  mariadb_get_install_location();

  if (argc <= 1)
  {
    usage();
    exit(0);
  }

  while(1)
  {
    int option_index= 0;
    c= getopt_long(argc, argv, "abcdefghijklmno", long_options, &option_index);

    switch(c) {
    case 'a': /* CFLAGS and Include directories */
      printf(CFLAGS, installation_dir, installation_dir);
      break;
    case 'b': /* Usage */
      usage();
      break;
    case 'c': /* Include directories */
      printf(INCLUDE, installation_dir, installation_dir);
      break;
    case 'd': /* Library directories and names */
    case 'e':
      printf(LIBS, installation_dir);
      break;
    case 'f': /* Server version */
      printf(VERSION);
      break;
    case 'g': /* Connector/C version */
      printf(CC_VERSION);
      break;
    case 'h': /* Unix socket */
      printf(SOCKET);
      break;
    case 'i': /* default port */
      printf(PORT);
      break;
    case 'j': /* plugin directory */
      printf(PLUGIN_DIR, installation_dir);
      break;
    case 'k': /* TLS version */
      printf("%s", TLS_LIBRARY_VERSION);
      break;
    case 'l': /* System libraries */
      printf(LIBS_SYS);
      break;
    case 'm': /* variable */
    {
      int i= 0;
      while (variables[i].variable)
      {
        if (!strcmp(optarg, variables[i].variable))
        {
          printf(variables[i].value, installation_dir);
          break;
        }
        i++;
      }
      if (!variables[i].variable)
      {
        printf("Unknown variable '%s'\n", optarg);
        exit(1);
      }
      break;
    }
#ifdef HAVE_EMBEDDED
    case 'n':
      puts(EMBEDDED_LIBS);
      break;
#endif
    default:
      exit((c != -1));
    }
    printf("\n");
  }

  exit(0);
}

