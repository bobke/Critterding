bin_PROGRAMS = critterding

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.


SUBDIRS = utils brainz gl scenes


critterding_SOURCES = critterding.cpp
critterding_LDADD = $(top_builddir)/src/gl/libgl.la \
	$(top_builddir)/src/scenes/libscenes.la $(top_builddir)/src/utils/libutils.la -lGL
critterding_LDFLAGS = -avoid-version -no-undefined
