#ifndef DISPLAYLISTS_H
#define DISPLAYLISTS_H

#include "bullet/btBulletDynamicsCommon.h"
#include "bullet/BulletCollision/CollisionShapes/btTriangleInfoMap.h"
// #include "BulletCollision/CollisionShapes/btShapeHull.h"
#include <SDL/SDL.h>
// #include <SDL/GL.h>

#include <string>
#include <iostream>
#include <sstream>
#include "file.h"
#include "parser.h"
#include <GL/gl.h>
// #include <GL/glext.h>
// #include <GL/glu.h>

using namespace std;

class Displaylists
{
	public:
		static Displaylists*	Instance();
		int			displayLists;
		void			generateList();
		void			call(unsigned int index);

	protected:
		Displaylists();

	private:
		static Displaylists*	_instance;
		GLuint			vboId;
		GLuint createVBO(const void* data, int dataSize, GLenum target, GLenum usage);

/*PFNGLBINDBUFFERARBPROC glBindBufferARB;
PFNGLGENBUFFERSARBPROC glGenBuffersARB;
PFNGLBUFFERDATAARBPROC glBufferDataARB;
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;*/
};

#endif
