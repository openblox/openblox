bin_PROGRAMS = openblox

# Sources for openblox
openblox_SOURCES = openblox.cpp

# Linker options
openblox_LDADD = @LOPENBLOX_CFLAGS@ @LIRRLICHT_CFLAGS@ @LLUA_LIBS@

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
openblox_CPPFLAGS = @LOPENBLOX_CPPFLAGS@ @LLUA_CFLAGS@ -std=c++11
