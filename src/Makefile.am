bin_PROGRAMS = critterding

# set the include path found by configure
INCLUDES = $(all_includes) -I./utils/bullet

# the library search path.

SUBDIRS = utils math brainz gl gui scenes @OPENCL_LOCALDIR@

critterding_SOURCES = critterding.cpp
critterding_LDADD =	$(top_builddir)/src/gl/libgl.la \
			$(top_builddir)/src/scenes/libscenes.la \
			$(top_builddir)/src/utils/libutils.la \
			$(top_builddir)/src/math/libmath.la \
			$(top_builddir)/src/gui/libgui.la \
			$(top_builddir)/src/utils/bullet/libbulletmath.la \
			@OPENCL_LA@ \
			$(HOST_LIBS)

# -lGL -lfreetype -lSDL
# -lBulletDynamics -lBulletCollision -lLinearMath  
# -lftgl
critterding_LDFLAGS = -avoid-version -no-undefined  -fopenmp
