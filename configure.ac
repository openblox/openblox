#Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([openblox], [0.1.1], [johnmh@openblox.org])
AC_CONFIG_HEADERS([src/config.h])
AC_PROG_CXX

AC_CANONICAL_TARGET
AC_CANONICAL_SYSTEM

AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.10 foreign])

#Options
AC_ARG_WITH(irrlicht, AS_HELP_STRING([--without-irrlicht], [Compile without Irrlicht support.]))

#Dependency checks

LOPENBLOX_LIBS="-lopenblox"
LOPENBLOX_CPPFLAGS=""

AC_ARG_WITH(libopenblox, AC_HELP_STRING([--with-libopenblox=PATH]),
						 [
						  if test "x$withval" != "xyes"; then
						  	 withval=$(realpath $withval)
   						  	 LOPENBLOX_LIBS="-L${withval}/src/.libs -lopenblox"
   						  	 LOPENBLOX_CPPFLAGS="-I${withval}/include"
						  fi
						 ])

AC_SUBST(LOPENBLOX_LIBS)
AC_SUBST(LOPENBLOX_CPPFLAGS)

AS_IF([test "x$with_irrlicht" != "xno"],
      [AC_CHECK_LIB(Irrlicht, createDevice, [have_irrlicht=yes], AC_MSG_ERROR([createDevice was not found in libIrrlicht (Irrlicht not installed?)]))],
	  [have_irrlicht=no])

AS_IF([test "x$have_irrlicht" = "xyes"],
      [LIRRLICHT_LIBS="-lIrrlicht"] [AC_DEFINE_UNQUOTED(HAVE_IRRLICHT, 1, [Define to 1 if you have the `Irrlicht' library (-lIrrlicht).],
	  [LIRRLICHT_LIBS=""])])

AC_SUBST(LIRRLICHT_LIBS)

AS_IF([test "x$target_os" == "xmingw32"],
      [LGL_LIB="-lopengl32"],
      [LGL_LIB="-lGL"])

AC_SUBST(LGL_LIB)

LT_INIT

AC_CONFIG_FILES(Makefile
                src/Makefile)
AC_OUTPUT
