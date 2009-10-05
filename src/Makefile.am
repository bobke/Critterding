bin_PROGRAMS = critterding

# set the include path found by configure
INCLUDES = $(all_includes) -I./utils/bullet -I/usr/include/freetype2

# the library search path.


SUBDIRS = utils math brainz gl gui scenes


critterding_SOURCES = critterding.cpp
critterding_LDADD =	$(top_builddir)/src/gl/libgl.la \
			$(top_builddir)/src/scenes/libscenes.la \
			$(top_builddir)/src/utils/libutils.la \
			$(top_builddir)/src/math/libmath.la \
			$(top_builddir)/src/gui/libgui.la \
			$(HOST_LIBS)

# -lGL -lfreetype -lSDL
# -lBulletDynamics -lBulletCollision -lLinearMath  
# -lftgl
critterding_LDFLAGS = -avoid-version -no-undefined
