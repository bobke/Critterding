INCLUDES = $(all_includes)
METASOURCES = AUTO
noinst_LTLIBRARIES = libbrainz.la
libbrainz_la_LDFLAGS = -avoid-version -no-undefined
noinst_HEADERS = archneuronz.h archsynapse.h brainz.h neuroninterz.h \
	neuronsensorz.h synapse.h
libbrainz_la_SOURCES = archneuronz.cpp archsynapse.cpp brainz.cpp \
	neuroninterz.cpp neuronsensorz.cpp synapse.cpp
libbrainz_la_LIBADD = $(top_builddir)/src/utils/libutils.la
