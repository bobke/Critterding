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
        }
        else
        {
                camera.place();
        }
        world.drawWithGrid();

// 	if ( world.isSelected )
// 	{
// 		camera.follow(world.critters[world.selectedCritter]->cameraposition, world.critters[world.selectedCritter]->rotation);
// 		world.drawWithinCritterSight(world.selectedCritter);
// 	}
// 	else
// 	{
// 		camera.place();
// 		world.drawWithGrid();
// 	}

	Timer::Instance()->mark();

	if ( settings->exit_if_empty && world.critters.size() == 0 )
	{
		cerr << "world is empty, exiting..." << endl;
		exit(0);
	}

	infobar.critters = world.critters.size();
	infobar.food = world.food.size();
	infobar.corpses = world.corpses.size();
	infobar.draw();

	helpinfo.draw();

//	glDisableClientState(GL_VERTEX_ARRAY);
}

void Evolution::handlekey(const KeySym& key)
{

	if ( pause && key != XK_p )
	{
		usleep(10000);
		return;
	}

	switch (key)
	{
		case XK_F1:
//			settings->printSettings();
			helpinfo.swap();
		break;

		case XK_F2:
			infobar.swap();
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
			if ( (settings->freeEnergyInfo-(settings->food_maxenergy*25.0f)) / settings->food_maxenergy >= 0.0f )
			{
				settings->freeEnergyInfo -= settings->food_maxenergy * 25.0f;
				world.freeEnergy -= settings->food_maxenergy * 25.0f;
				cerr << "Energy in system: " << (settings->freeEnergyInfo / settings->food_maxenergy) << endl;
			}
		break;
		case XK_F6:
			settings->freeEnergyInfo += settings->food_maxenergy * 25.0f;
			world.freeEnergy += settings->food_maxenergy * 25.0f;
			cerr << "Energy in system: " << (settings->freeEnergyInfo / settings->food_maxenergy) << endl;
		break;

		case XK_KP_Subtract:
			if ( (settings->freeEnergyInfo-settings->food_maxenergy) / settings->food_maxenergy >= 0.0f )
			{
				settings->freeEnergyInfo -= settings->food_maxenergy;
				world.freeEnergy -= settings->food_maxenergy;
				cerr << "Energy in system: " << (settings->freeEnergyInfo / settings->food_maxenergy) << endl;
			}
		break;

		case XK_KP_Add:
			settings->freeEnergyInfo += settings->food_maxenergy;
			world.freeEnergy += settings->food_maxenergy;
			cerr << "Energy in system: " << (settings->freeEnergyInfo / settings->food_maxenergy) << endl;
		break;

		case XK_F7:
			world.insertCritter();
		break;
		case XK_F8:
			world.toggleTimedInserts();
			cerr << "timed food inserts: "<< world.doTimedInserts << endl;
		break;
		case XK_F9:
			if ( settings->critter_maxmutations >= 2 )
			{
				settings->critter_maxmutations -= 1;
				cerr << "Max Mutations: "<< settings->critter_maxmutations << endl;
			}
		break;
		case XK_F10:
			if ( settings->critter_maxmutations <= 999 )
			{
				settings->critter_maxmutations += 1;
				cerr << "Max Mutations: "<< settings->critter_maxmutations << endl;
			}
		break;
		case XK_F11:
			if ( settings->critter_mutationrate >= 1 )
			{
				settings->critter_mutationrate -= 1;
				cerr << "Mutation Rate: "<< settings->critter_mutationrate << "%" << endl;
			}
		break;
		case XK_F12:
			if ( settings->critter_mutationrate <= 99 )
			{
				settings->critter_mutationrate += 1;
				cerr << "Mutation Rate: "<< settings->critter_mutationrate << "%" << endl;
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
		case XK_v:
			settings->noverbose = !settings->noverbose;
			if ( settings->noverbose )
				cerr << "verbose = off" << endl;
			else
				cerr << "verbose = on" << endl;
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
			settings->walltype++;
			if ( settings->walltype > settings->walltypeMax ) settings->walltype = settings->walltypeMin;
			world.createWall();
		break;
		case XK_x:
			settings->walltype = 0;
			world.destroyWall();
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
				cerr << "Camera Sensitivity: "<< camera.sensitivity << endl;
			}
		break;
		case XK_KP_Multiply:
			camera.sensitivity++;
			cerr << "Camera Sensitivity: "<< camera.sensitivity << endl;
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
			camera.rotation = Vector3f( 75.0f,  0.0f, 0.0f);
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
/*		case XK_KP_Page_Down:
			//camera.rollLeft(1.0f);
		break;
		case XK_KP_End:
			//camera.rollRight(1.0f);
		break;*/
	}
}

Evolution::~Evolution()
{
}
