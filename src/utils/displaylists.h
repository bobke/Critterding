#ifndef DISPLAYLISTS_H
#define DISPLAYLISTS_H

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"
#include <string>
#include <iostream>
#include <sstream>
#include "file.h"
#include "parser.h"
#include <GL/gl.h>

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
};

#endif
