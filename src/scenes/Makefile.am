INCLUDES = $(all_includes) -I../utils/bullet -fopenmp
METASOURCES = AUTO
noinst_LTLIBRARIES = libscenes.la
libscenes_la_SOURCES = evolution.cpp
libscenes_la_LIBADD =	$(top_builddir)/src/brainz/libbrainz.la \
			$(top_builddir)/src/gl/libgl.la \
			$(top_builddir)/src/gui/libgui.la \
			$(top_builddir)/src/scenes/gui/libcdgui.la \
			$(top_builddir)/src/scenes/entities/libentities.la \
			$(top_builddir)/src/scenes/modes/libmodes.la \
			$(top_builddir)/src/utils/libutils.la
SUBDIRS = gui entities modes

