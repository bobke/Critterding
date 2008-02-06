bin_PROGRAMS = bengine
bengine_SOURCES = bengine.cpp

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.


SUBDIRS = gl utils scenes

bengine_LDFLAGS = -avoid-version -no-undefined

bengine_LDADD = $(top_builddir)/src/scenes/libscenes.la \
	$(top_builddir)/src/gl/libgl.la
