
#include "evolution.h"

Evolution::Evolution()
{
	drawCVNeurons = false;
}

void Evolution::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glEnableClientState(GL_VERTEX_ARRAY);

		world.process();


	if ( !drawCVNeurons )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}
	
		camera.place(width, height);
	
		world.drawWithGrid();
	
		sleeper.mark();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
}

void Evolution::handlekey(const KeySym& key)
{
	switch (key)
	{
		case XK_KP_Add:
		break;
		case XK_KP_Subtract:
		break;

		case XK_F2:
			sleeper.swap();
		break;

		case XK_F3:
			world.decreaseMincritters();
		break;
		case XK_F4:
			world.increaseMincritters();
		break;

		case XK_F5:
			world.decreaseMaxcritters();
		break;
		case XK_F6:
			world.increaseMaxcritters();
		break;

		case XK_F7:
			world.insertCritter();
		break;
		case XK_F8:
		break;
		case XK_F9:
			world.decreaseBGthreads();
		break;
		case XK_F10:
			world.increaseBGthreads();
		break;
		case XK_F11:
			world.loadAllCritters();
		break;
		case XK_F12:
			world.saveAllCritters();
		break;

		// Critter controls
		case XK_z:
		break;
		case XK_s:
		break;
		case XK_q:
		break;
		case XK_d:
		break;
		case XK_a:
		break;
		case XK_e:
		break;


		// Camera Looking
		case XK_KP_Right:
			camera.lookRight(1.0f);
		break;
		case XK_KP_Left:
			camera.lookLeft(1.0f);
		break;
		case XK_KP_Up:
			camera.lookUp(1.0f);
		break;
		case XK_KP_Down:
			camera.lookDown(1.1f);
		break;

		// Camera Moving
		case XK_Home:
			camera.moveUp(0.2f);
		break;
		case XK_End:
			camera.moveDown(0.2f);
		break;

		case XK_Insert:
			if ( drawCVNeurons ) drawCVNeurons = false;
			else drawCVNeurons = true;
		break;
		case XK_Delete:
		break;

		case XK_Page_Up:
		break;
		case XK_Page_Down:
		break;
		case XK_Up:
			camera.moveForward(0.2f);
		break;
		case XK_Down:
			camera.moveBackward(0.2f);
		break;
		case XK_Left:
			camera.moveLeft(0.2f);
		break;
		case XK_Right:
			camera.moveRight(0.2f);
		break;

	}

}

Evolution::~Evolution()
{
}
