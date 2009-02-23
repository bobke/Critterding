INCLUDES = $(all_includes)
METASOURCES = AUTO
noinst_LTLIBRARIES = libutils.la
noinst_HEADERS = dir.h file.h parser.h randgen.h timer.h fps.h sleeper.h settings.h infobar.h helpinfo.h textprinter.h textmessage.h textverbosemessage.h
libutils_la_SOURCES = dir.cpp file.cpp parser.cpp randgen.cpp timer.cpp fps.cpp sleeper.cpp settings.cpp infobar.cpp helpinfo.cpp textprinter.cpp textmessage.cpp textverbosemessage.cpp
libutils_la_LIBADD = $(top_builddir)/src/utils/ftgl/libftgl.la
libutils_la_LDFLAGS = -avoid-version -no-undefined

SUBDIRS = ftgl