INCLUDES = $(all_includes) -I/usr/include/freetype2
METASOURCES = AUTO
noinst_LTLIBRARIES = libgui.la
noinst_HEADERS =	widget.h \
			panel.h \
			textprinter.h \
			helpinfo.h \
			textmessage.h \
			textverbosemessage.h \
			infostats.h \
			infobar.h \
			statsgraph.h

libgui_la_SOURCES = 	widget.cpp \
			panel.cpp \
			textprinter.cpp \
			helpinfo.cpp \
			textmessage.cpp \
			textverbosemessage.cpp \
			infostats.cpp \
			infobar.cpp \
			statsgraph.cpp

libgui_la_LIBADD =	$(top_builddir)/src/utils/libutils.la \
			$(top_builddir)/src/math/libmath.la
