bin_PROGRAMS = openblox

# Sources for openblox
openblox_SOURCES = openblox.cpp

# Linker options
openblox_LDADD = $(LOPENBLOX_LIBS) $(LIRRLICHT_LIBS) $(LGL_LIB)

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
openblox_CPPFLAGS = $(LOPENBLOX_CFLAGS) $(LLUA_CFLAGS) -std=c++11
