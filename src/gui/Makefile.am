INCLUDES = $(all_includes) -I../utils/bullet 
METASOURCES = AUTO
noinst_LTLIBRARIES = libgui.la
noinst_HEADERS =	widget.h \
			container.h \
			text.h \
			text_uintp.h \
			panel.h \
			settingspanel.h \
			button.h \
			textprinter.h

libgui_la_SOURCES = 	widget.cpp \
			container.cpp \
			text.cpp \
			text_uintp.cpp \
			panel.cpp \
			settingspanel.cpp \
			button.cpp \
			textprinter.cpp

libgui_la_LIBADD =	$(top_builddir)/src/utils/libutils.la \
			$(top_builddir)/src/math/libmath.la
