#include "evolution.h"

Evolution::Evolution()
{
	settings = Settings::Instance();

	pause = false;
	drawCVNeurons = false;
}

void Evolution::draw()
{
	Timer::Instance()->mark();
	sleeper.mark();

	if ( pause )
	{
		usleep(20000);
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_FOG_HINT, GL_FASTEST);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
 	glDisable (GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DITHER);
	glDisable(GL_POLYGON_SMOOTH);

	world.process();

	if ( !drawCVNeurons || world.isSelected )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
// 		glHint(GL_FOG_HINT, GL_FASTEST);
// 		glShadeModel(GL_FLAT);
// 		glEnable(GL_DEPTH_TEST);
// 		glDisable (GL_LIGHTING);
// 		glDisable(GL_COLOR_MATERIAL);
// 		glDisable(GL_DITHER);
// 		glDisable(GL_POLYGON_SMOOTH);
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

	// 2D

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, *Settings::Instance()->winWidth, *Settings::Instance()->winHeight, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

		infobar.draw();

		infostats.draw(infobar.height());

		Textverbosemessage::Instance()->draw(infobar.height()+infostats.height());

		helpinfo.draw();

		Textmessage::Instance()->draw();

	glPopMatrix();

	if ( settings->exit_if_empty && world.critters.size() == 0 )
	{
		cerr << "world is empty, exiting..." << endl;
		exit(0);
	}
}

void Evolution::handlekey(const KeySym& key)
{
	if ( pause && key != XK_p )
	{
		//usleep(10000);
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
		{
			infostats.swap();
		}
		break;
		case XK_F4:
			Textverbosemessage::Instance()->swap();
		break;

		case XK_F5:
		{
			if ( settings->mincritters > 0 ) settings->mincritters--;
			stringstream buf;
			buf << "min c: " << settings->mincritters;
			Textmessage::Instance()->add(buf);
		}
		break;
		case XK_F6:
		{
			settings->mincritters++;
			stringstream buf;
			buf << "min c: " << settings->mincritters;
			Textmessage::Instance()->add(buf);
		}
		break;

// 		case XK_F5:
// 		{
// 			if ( (settings->freeEnergyInfo-(settings->food_maxenergy*25.0f)) / settings->food_maxenergy >= 0.0f )
// 			{
// 				settings->freeEnergyInfo -= settings->food_maxenergy * 25.0f;
// 				world.freeEnergy -= settings->food_maxenergy * 25.0f;
// 
// 			}
// 			stringstream buf;
// 			buf << "Energy in system: " << (settings->freeEnergyInfo / settings->food_maxenergy);
// 			Textmessage::Instance()->add(buf);
// 		}
// 		break;
// 		case XK_F6:
// 		{
// 			settings->freeEnergyInfo += settings->food_maxenergy * 25.0f;
// 			world.freeEnergy += settings->food_maxenergy * 25.0f;
// 			stringstream buf;
// 			buf << "Energy in system: " << (settings->freeEnergyInfo / settings->food_maxenergy);
// 			Textmessage::Instance()->add(buf);
// 		}
// 		break;

		case XK_KP_Subtract:
		{
			if ( (settings->freeEnergyInfo-settings->food_maxenergy) / settings->food_maxenergy >= 0.0f )
			{
				settings->freeEnergyInfo -= settings->food_maxenergy;
				world.freeEnergy -= settings->food_maxenergy;
			}
			stringstream buf;
			buf << "Energy in system: " << (settings->freeEnergyInfo / settings->food_maxenergy);
			Textmessage::Instance()->add(buf);
		}
		break;

		case XK_KP_Add:
		{
			settings->freeEnergyInfo += settings->food_maxenergy;
			world.freeEnergy += settings->food_maxenergy;
			stringstream buf;
			buf << "Energy in system: " << (settings->freeEnergyInfo / settings->food_maxenergy);
			Textmessage::Instance()->add(buf);
		}
		break;

		case XK_F7:
			world.insertCritter();
		break;
		case XK_F8:
		{
			world.toggleTimedInserts();
			stringstream buf;
			buf << "timed food inserts: "<< world.doTimedInserts;
			Textmessage::Instance()->add(buf);

		}
		break;
		case XK_F9:
		{
			if ( settings->critter_maxmutations >= 2 )
				settings->critter_maxmutations -= 1;
			stringstream buf;
			buf << "Max Mutations: "<< settings->critter_maxmutations;
			Textmessage::Instance()->add(buf);
		}
		break;
		case XK_F10:
		{
			if ( settings->critter_maxmutations <= 999 )
				settings->critter_maxmutations += 1;
			stringstream buf;
			buf << "Max Mutations: "<< settings->critter_maxmutations;
			Textmessage::Instance()->add(buf);
		}
		break;
		case XK_F11:
		{
			if ( settings->critter_mutationrate >= 1 )
				settings->critter_mutationrate -= 1;
			stringstream buf;
			buf << "Mutation Rate: "<< settings->critter_mutationrate << "%";
			Textmessage::Instance()->add(buf);
		}
		break;
		case XK_F12:
		{
			if ( settings->critter_mutationrate <= 99 )
				settings->critter_mutationrate += 1;
			stringstream buf;
			buf << "Mutation Rate: "<< settings->critter_mutationrate << "%";
			Textmessage::Instance()->add(buf);
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

		case XK_l:
			sleeper.swap();
		break;

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
		case XK_s:
		{
			settings->spreadertype++;
			if ( settings->spreadertype > settings->spreadertypeMax )
				settings->spreadertype = settings->spreadertypeMin;
			stringstream buf;
			buf << "Spreader type: "<< settings->spreadertype;
			Textmessage::Instance()->add(buf);
		}
		break;
		case XK_w:
		{
			settings->walltype++;
			if ( settings->walltype > settings->walltypeMax )
				settings->walltype = settings->walltypeMin;
			world.createWall();
			stringstream buf;
			buf << "Wall type: " << settings->walltype;
			Textmessage::Instance()->add(buf);
		}
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
		{
			if ( camera.sensitivity > 1 )
				camera.sensitivity--;
			stringstream buf;
			buf << "Camera Sensitivity: "<< camera.sensitivity;
			Textmessage::Instance()->add(buf);
		}
		break;
		case XK_KP_Multiply:
		{
			camera.sensitivity++;
			stringstream buf;
			buf << "Camera Sensitivity: "<< camera.sensitivity;
			Textmessage::Instance()->add(buf);
		}
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
			resetCamera();
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

void Evolution::resetCamera()
{
	unsigned int biggest = world.sizeX;
	if ( world.sizeY > biggest )
		biggest = 1.4f*world.sizeY;

	camera.position = Vector3f(-0.5f*world.sizeX, -1.1f*biggest, -0.87*world.sizeY);
	camera.rotation = Vector3f( 70.0f,  0.0f, 0.0f);
}

Evolution::~Evolution()
{
}
