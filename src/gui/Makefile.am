INCLUDES = $(all_includes) -I../utils/bullet -I/usr/include/freetype2
METASOURCES = AUTO
noinst_LTLIBRARIES = libgui.la
noinst_HEADERS =	widget.h \
			container.h \
			text.h \
			text_uintp.h \
			panel.h \
			button.h \
			textprinter.h \
			maincanvas.h \
			helpinfo.h \
			textmessage.h \
			textverbosemessage.h \
			infostats.h \
			infobar.h \
			statsgraph.h \
			exitpanel.h \
			settingspanel.h \
			settingsbrainpanel.h \
			hud.h

libgui_la_SOURCES = 	widget.cpp \
			container.cpp \
			text.cpp \
			text_uintp.cpp \
			panel.cpp \
			button.cpp \
			textprinter.cpp \
			maincanvas.cpp \
			helpinfo.cpp \
			textmessage.cpp \
			textverbosemessage.cpp \
			infostats.cpp \
			infobar.cpp \
			statsgraph.cpp \
			exitpanel.cpp \
			settingspanel.cpp \
			settingsbrainpanel.cpp \
			hud.cpp

libgui_la_LIBADD =	$(top_builddir)/src/utils/libutils.la \
			$(top_builddir)/src/math/libmath.la
