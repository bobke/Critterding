#include "evolution.h"

Evolution::Evolution()
{
	drawCVNeurons = true;
}

void Evolution::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glEnableClientState(GL_VERTEX_ARRAY);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_FOG_HINT, GL_FASTEST);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DITHER);
	glDisable(GL_POLYGON_SMOOTH);

	world.process();

	if ( !drawCVNeurons )
	{
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
		glHint(GL_FOG_HINT, GL_FASTEST);
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_DITHER);
		glDisable(GL_POLYGON_SMOOTH);
	}

	if ( world.isSelected )
	{
		camera.follow(width, height, world.critters[world.selectedCritter]);
	}
	else
	{
		camera.place(width, height);
	}

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
			world.freeEnergyInfo -= world.foodenergy * 50.0f;
			world.freeEnergy -= world.foodenergy * 50.0f;
			cerr << (world.freeEnergyInfo / world.foodenergy) << " food in system" << endl;
		break;
		case XK_F6:
			world.freeEnergyInfo += world.foodenergy * 50.0f;
			world.freeEnergy += world.foodenergy * 50.0f;
			cerr << (world.freeEnergyInfo / world.foodenergy) << " food in system" << endl;
		break;

		case XK_F7:
			world.insertCritter();
		break;
		case XK_F8:
		break;
		case XK_F9:
			world.toggleBGthread();
		break;
		case XK_F10:
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
		case XK_f:
			if ( world.isSelected )
			{
				world.selectedCritter = 0;
				world.isSelected = false;
			}
			else if ( !world.critters.empty() )
			{
				world.selectedCritter = world.critters.size()-1;
				world.isSelected = true;
			}
		break;
		case XK_w:
			world.createWall();
		break;
		case XK_x:
			world.destroyWall();
		break;
		case XK_c:
			world.toggleGate((unsigned int)(world.size*2.0f)-2);
			world.toggleGate((unsigned int)(world.size*2.0f)-1);
			world.toggleGate((unsigned int)(world.size*2.0f));
			world.toggleGate((unsigned int)(world.size*2.0f)+1);
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
		case XK_KP_Page_Down:
			camera.rollLeft(1.0f);
		break;
		case XK_KP_End:
			camera.rollRight(1.0f);
		break;

		// Camera Moving
		case XK_Home:
			camera.moveUp(0.2f);
		break;
		case XK_End:
			camera.moveDown(0.2f);
		break;

		case XK_Insert:
			drawCVNeurons = !drawCVNeurons;
		break;
		case XK_Delete:
		break;
// << "/" << setw(3) << critters.size()-1
		case XK_Page_Up:
			world.freeEnergyInfo += world.foodenergy;
			world.freeEnergy += world.foodenergy;
			cerr << (world.freeEnergyInfo / world.foodenergy) << " food in system" << endl;
		break;
		case XK_Page_Down:
			world.freeEnergyInfo -= world.foodenergy;
			world.freeEnergy -= world.foodenergy;
			cerr << (world.freeEnergyInfo / world.foodenergy) << " food in system" << endl;
		break;
		case XK_Up:
			camera.moveForward(0.1f);
		break;
		case XK_Down:
			camera.moveBackward(0.1f);
		break;
		case XK_Left:
			camera.moveLeft(0.1f);
		break;
		case XK_Right:
			camera.moveRight(0.1f);
		break;
	}
}

Evolution::~Evolution()
{
}
