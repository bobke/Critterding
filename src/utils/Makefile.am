INCLUDES = $(all_includes) -I./bullet 
METASOURCES = AUTO
noinst_LTLIBRARIES = libutils.la
noinst_HEADERS =	dir.h \
			file.h \
			parser.h \
			randgen.h \
			timer.h \
			fps.h \
			sleeper.h \
			settings.h \
			displaylists.h \
			events.h \
			raycast.h \
			mousepicker.h \
			statsbuffer.h \
			commands.h \
			execcmd.h \
			logbuffer.h \
			critterselection.h \
			headless.h \
			color.h \
			dirlayout.h

libutils_la_SOURCES =	dir.cpp \
			file.cpp \
			parser.cpp \
			randgen.cpp \
			timer.cpp \
			fps.cpp \
			sleeper.cpp \
			settings.cpp \
			displaylists.cpp \
			events.cpp \
			raycast.cpp \
			mousepicker.cpp \
			statsbuffer.cpp \
			commands.cpp \
			execcmd.cpp \
			logbuffer.cpp \
			critterselection.cpp \
			headless.cpp \
			color.cpp \
			dirlayout.cpp
		      
libutils_la_LIBADD = @FTGL_LA@ $(top_builddir)/src/utils/bullet/libbulletmath.la \
			$(top_builddir)/src/utils/bullet/libbulletcollision.la \
			$(top_builddir)/src/utils/bullet/libbulletdynamics.la
# 			$(top_builddir)/src/utils/bullet/libbulletmultithreaded.la
libutils_la_LDFLAGS = -avoid-version -no-undefined

SUBDIRS = @FTGL_LOCALDIR@ bullet
