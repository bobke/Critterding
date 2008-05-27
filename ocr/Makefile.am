INCLUDES = -I$(top_srcdir)/src/brainz -I$(top_srcdir)/src/utils
METASOURCES = AUTO
bin_PROGRAMS = ocr
noinst_HEADERS = brainstore.h tga.h tgastore.h
ocr_SOURCES = brainstore.cpp ocr.cpp tga.cpp tgastore.cpp
ocr_LDADD = $(top_builddir)/src/brainz/libbrainz.la \
	$(top_builddir)/src/utils/libutils.la -lpthread
