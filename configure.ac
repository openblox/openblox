#Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([openblox], [0.1.1], [johnmh@openblox.org])
AC_CONFIG_HEADERS([src/config.h])
AC_PROG_CXX

AC_CANONICAL_SYSTEM

AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.10 foreign])

syslua="lua"

#Options
AC_ARG_WITH(irrlicht, AS_HELP_STRING([--without-irrlicht], [Compile without Irrlicht support.]))
AC_ARG_WITH(lua, AS_HELP_STRING([--with-lua=LUA_VER], [Compile with a specific system Lua.]), [syslua="$withval"])

#Dependency checks

LOPENBLOX_CFLAGS="-lopenblox"
LOPENBLOX_CPPFLAGS=""

AC_ARG_WITH(libopenblox, AC_HELP_STRING([--with-libopenblox=PATH]),
						 [
						  if test "x$withval" != "xyes"; then
						  	 withval=$(realpath $withval)
   						  	 LOPENBLOX_CFLAGS="-L${withval}/src/.libs -lopenblox"
   						  	 LOPENBLOX_CPPFLAGS="-I${withval}/include"
						  fi
						 ])

AC_SUBST(LOPENBLOX_CFLAGS)
AC_SUBST(LOPENBLOX_CPPFLAGS)

AS_IF([test "x$with_irrlicht" != "xno"],
      [AC_CHECK_LIB(Irrlicht, createDevice, [have_irrlicht=yes], AC_MSG_ERROR([createDevice was not found in libIrrlicht (Irrlicht not installed?)]))],
	  [have_irrlicht=no])

AS_IF([test "x$have_irrlicht" = "xyes"],
      [LIRRLICHT_CFLAGS="-lIrrlicht"] [AC_DEFINE_UNQUOTED(HAVE_IRRLICHT, 1, [Define to 1 if you have the `Irrlicht' library (-lIrrlicht).],
	  [LIRRLICHT_CFLAGS=""])])

AC_SUBST(LIRRLICHT_CFLAGS)

AS_IF([test "x$syslua" != "xlua"],
      [LLUA_CFLAGS="-I$oldincludedir/$syslua"] [LLUA_LIBS="-l$syslua -lm"] [LDFLAGS="$LDFLAGS -lm -ldl"])

PKG_CHECK_MODULES([LLUA], [lua])

AC_CHECK_LIB($syslua, lua_newstate,, AC_MSG_ERROR([lua_newstate was not found in lib$syslua (lua not installed?)]))

LT_INIT

AC_CONFIG_FILES(Makefile
                src/Makefile)
AC_OUTPUT
