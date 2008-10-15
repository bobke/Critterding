#include "evolution.h"

Evolution::Evolution()
{
	settings = Settings::Instance();

	pause = false;
	drawCVNeurons = true;
}

void Evolution::draw()
{
	if ( pause )
	{
		usleep(10000);
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

//	glEnableClientState(GL_VERTEX_ARRAY);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_FOG_HINT, GL_FASTEST);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DITHER);
	glDisable(GL_POLYGON_SMOOTH);

//	glEnable(GL_CULL_FACE);

	world.process();

	if ( !drawCVNeurons || world.isSelected )
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
		camera.follow(world.critters[world.selectedCritter]->cameraposition, world.critters[world.selectedCritter]->rotation);
		world.drawWithinCritterSight(world.selectedCritter);
	}
	else
	{
		camera.place();
		world.drawWithGrid();
	}
//		world.drawWithGrid();

	Timer::Instance()->mark();
	fps.mark();

	if ( settings->exit_if_empty && world.critters.size() == 0 )
	{
		cerr << "world is empty, exiting..." << endl;
		exit(0);
	}

//	glDisableClientState(GL_VERTEX_ARRAY);
}

void Evolution::handlekey(const KeySym& key)
{

	if ( pause && key != XK_F1 && key != XK_p )
	{
		usleep(10000);
		return;
	}

	switch (key)
	{
		case XK_F1:
			if ( !pause )
			{
				world.printSettings();
				pause = true;
			}
			else pause = false;
		break;

		case XK_F2:
			fps.swap();
		break;

		case XK_F3:
			if ( settings->mincritters > 0 ) settings->mincritters--;
			cerr << "min c: " << settings->mincritters << endl;
		break;
		case XK_F4:
			settings->mincritters++;
			cerr << "min c: " << settings->mincritters << endl;
		break;

		case XK_F5:
			if ( (world.freeEnergyInfo-(settings->food_maxenergy*25.0f)) / settings->food_maxenergy >= 0.0f )
			{
				world.freeEnergyInfo -= settings->food_maxenergy * 25.0f;
				world.freeEnergy -= settings->food_maxenergy * 25.0f;
				cerr << endl << "Energy in system: " << (world.freeEnergyInfo / settings->food_maxenergy) << "*" << settings->food_maxenergy << " = " << world.freeEnergyInfo  << endl << endl;
			}
		break;
		case XK_F6:
			world.freeEnergyInfo += settings->food_maxenergy * 25.0f;
			world.freeEnergy += settings->food_maxenergy * 25.0f;
			cerr << endl << "Energy in system: " << (world.freeEnergyInfo / settings->food_maxenergy) << "*" << settings->food_maxenergy << " = " << world.freeEnergyInfo  << endl << endl;
		break;

		case XK_KP_Subtract:
			if ( (world.freeEnergyInfo-settings->food_maxenergy) / settings->food_maxenergy >= 0.0f )
			{
				world.freeEnergyInfo -= settings->food_maxenergy;
				world.freeEnergy -= settings->food_maxenergy;
				cerr << endl << "Energy in system: " << (world.freeEnergyInfo / settings->food_maxenergy) << "*" << settings->food_maxenergy << " = " << world.freeEnergyInfo  << endl << endl;
			}
		break;

		case XK_KP_Add:
			world.freeEnergyInfo += settings->food_maxenergy;
			world.freeEnergy += settings->food_maxenergy;
			cerr << endl << "Energy in system: " << (world.freeEnergyInfo / settings->food_maxenergy) << "*" << settings->food_maxenergy << " = " << world.freeEnergyInfo  << endl << endl;
		break;

		case XK_F7:
			world.insertCritter();
		break;
		case XK_F8:
			world.toggleTimedInserts();
			cerr << endl << "timed food inserts: "<< world.doTimedInserts << endl << endl;
		break;
		case XK_F9:
			if ( settings->critter_maxmutations >= 2 )
			{
				settings->critter_maxmutations -= 1;
				cerr << endl << "Max Mutations: "<< settings->critter_maxmutations << endl << endl;
			}
		break;
		case XK_F10:
			if ( settings->critter_maxmutations <= 999 )
			{
				settings->critter_maxmutations += 1;
				cerr << endl << "Max Mutations: "<< settings->critter_maxmutations << endl << endl;
			}
		break;
		case XK_F11:
			if ( settings->critter_mutationrate >= 1 )
			{
				settings->critter_mutationrate -= 1;
				cerr << endl << "Mutation Rate: "<< settings->critter_mutationrate << "%" << endl << endl;
			}
		break;
		case XK_F12:
			if ( settings->critter_mutationrate <= 99 )
			{
				settings->critter_mutationrate += 1;
				cerr << endl << "Mutation Rate: "<< settings->critter_mutationrate << "%" << endl << endl;
			}
		break;

		case XK_Page_Up:
			world.loadAllCritters();
		break;
		case XK_Page_Down:
			world.saveAllCritters();
		break;


		// Critter controls
		case XK_z:
		break;

		case XK_p:
			pause = !pause;
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

		case XK_Insert:
			drawCVNeurons = !drawCVNeurons;
		break;
		case XK_Delete:
		break;

		case XK_KP_Divide:
			if ( camera.sensitivity > 1 )
			{
				camera.sensitivity--;
				cerr << endl << "Camera Sensitivity: "<< camera.sensitivity << endl << endl;
			}
		break;
		case XK_KP_Multiply:
			camera.sensitivity++;
			cerr << endl << "Camera Sensitivity: "<< camera.sensitivity << endl << endl;
		break;

		// Camera Moving
		case XK_Home:
			camera.moveUp(0.05f);
		break;
		case XK_End:
			camera.moveDown(0.05f);
		break;

		case XK_Up:
			camera.moveForwardXZ(0.05f);
		break;
		case XK_Down:
			camera.moveBackwardXZ(0.05f);
		break;
		case XK_Left:
			camera.moveLeft(0.05f);
		break;
		case XK_Right:
			camera.moveRight(0.05f);
		break;
		case XK_BackSpace:
			camera.position = Vector3f(-0.5f*world.size, -1.1f*world.size, -0.9f*world.size);
			camera.rotation = Vector3f( 76.0f,  0.0f, 0.0f);
		break;

		// Camera Looking
		case XK_KP_Right:
			camera.lookRight(0.25f);
		break;
		case XK_KP_Left:
			camera.lookLeft(0.25f);
		break;
		case XK_KP_Up:
			camera.lookUp(0.25f);
		break;
		case XK_KP_Down:
			camera.lookDown(0.25f);
		break;
		case XK_KP_Page_Down:
			//camera.rollLeft(1.0f);
		break;
		case XK_KP_End:
			//camera.rollRight(1.0f);
		break;
	}
}

Evolution::~Evolution()
{
}
