#Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([openblox], [0.1.1], [johnmh@openblox.org])
AC_CONFIG_HEADERS([openblox/config.h])
AC_PROG_CXX

AC_CANONICAL_SYSTEM

AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.10 foreign])

#Dependency checks

LOPENBLOX_CFLAGS="-lopenblox"
LOPENBLOX_CPPFLAGS=""

AC_ARG_WITH(libopenblox, AC_HELP_STRING([--with-libopenblox=PATH]),
						 [
						  if test "x$withval" != "xyes"; then
						  	 withval=$(realpath $withval)
   						  	 LOPENBLOX_CFLAGS="-L${withval}/libopenblox/.libs -lopenblox"
   						  	 LOPENBLOX_CPPFLAGS="-I${withval}/include"
						  fi
						 ])

AC_SUBST(LOPENBLOX_CFLAGS)
AC_SUBST(LOPENBLOX_CPPFLAGS)

LT_INIT

AC_CONFIG_FILES(Makefile
                openblox/Makefile)
AC_OUTPUT
