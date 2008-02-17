INCLUDES = -I$(top_srcdir)/src/utils $(all_includes) \
	-I$(top_srcdir)/src/entities
METASOURCES = AUTO
noinst_LTLIBRARIES = libscenes.la
libscenes_la_SOURCES = evolution.cpp
libscenes_la_LIBADD = $(top_builddir)/src/utils/libutils.la \
	$(top_builddir)/src/gl/libgl.la $(top_builddir)/src/scenes/entities/libentities.la
SUBDIRS = entities
_SOURCES = evolution.h
