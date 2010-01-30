INCLUDES = $(all_includes) -I../../utils/bullet -I/usr/include/freetype2
METASOURCES = AUTO
noinst_LTLIBRARIES = libcdgui.la
noinst_HEADERS =	critterview.h \
			brainview.h \
			exitpanel.h \
			helpinfo.h \
			infostats.h \
			infobar.h \
			textmessage.h \
			textverbosemessage.h \
			statsgraph.h \
			settingspanel.h \
			settingsbrainpanel.h \
			hud.h \
			maincanvas.h

libcdgui_la_SOURCES =	critterview.cpp \
			brainview.cpp \
			exitpanel.cpp \
			helpinfo.cpp \
			infostats.cpp \
			infobar.cpp \
			textmessage.cpp \
			textverbosemessage.cpp \
			statsgraph.cpp \
			settingspanel.cpp \
			settingsbrainpanel.cpp \
			hud.cpp \
			maincanvas.cpp

libcdgui_la_LIBADD =	$(top_builddir)/src/gui/libgui.la \
			$(top_builddir)/src/utils/libutils.la \
			$(top_builddir)/src/math/libmath.la
