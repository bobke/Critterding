INCLUDES = $(all_includes) -I./bullet -I/usr/include/freetype2
METASOURCES = AUTO
noinst_LTLIBRARIES = libutils.la
noinst_HEADERS =      dir.h   file.h   parser.h   randgen.h   timer.h   fps.h   sleeper.h   settings.h   displaylists.h   events.h   raycast.h   mousepicker.h   statsbuffer.h

libutils_la_SOURCES = dir.cpp file.cpp parser.cpp randgen.cpp timer.cpp fps.cpp sleeper.cpp settings.cpp displaylists.cpp events.cpp raycast.cpp mousepicker.cpp statsbuffer.cpp
		      
libutils_la_LIBADD = $(top_builddir)/src/utils/ftgl/libftgl.la $(top_builddir)/src/utils/bullet/libbulletmath.la $(top_builddir)/src/utils/bullet/libbulletcollision.la \
                     $(top_builddir)/src/utils/bullet/libbulletdynamics.la
libutils_la_LDFLAGS = -avoid-version -no-undefined

SUBDIRS = ftgl bullet
