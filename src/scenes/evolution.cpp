#include "evolution.h"

Evolution::Evolution()
{
	settings = Settings::Instance();

	pause = false;
// 	drawCVNeurons = false;
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

// 	if ( world.critters.size() > 100 )
// 		world.killHalfOfCritters();

// 	if ( sleeper.isRenderTime() )
// 	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 3D

		GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
		GLfloat lightColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat lightPos[] = { 0.5f*settings->worldsizeX, 20, 0.5f*settings->worldsizeY, 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

// 		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
    
    
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
// 		glHint(GL_FOG_HINT, GL_FASTEST);
		glShadeModel(GL_FLAT);
		glEnable(GL_DEPTH_TEST);
// 		glDisable (GL_LIGHTING);
// 		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_DITHER);
		glDisable(GL_POLYGON_SMOOTH);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		world.process();

// 		if (world.critters.size() >0 )
// 		{
// 			camera.follow( (btDefaultMotionState*)world.critters[0]->body->mouths[0]->body->getMotionState() );
// 			world.drawWithoutFaces();
// 		}

		camera.place();
		world.drawWithGrid();

		glDisable (GL_LIGHTING);

		// 2D
		glDisable(GL_LIGHT0);
		glDisable(GL_CULL_FACE);

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
		
		glXSwapBuffers(settings->dpy, settings->win);
// 	}

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
			if ( settings->mincritters > settings->mincrittersMin )
				settings->mincritters--;
			stringstream buf;
			buf << "mincritters: "<< settings->mincritters;
			Textmessage::Instance()->add(buf);
/*			if ( settings->insertcritterevery > 0 ) settings->insertcritterevery-=100;
			stringstream buf;
			buf << "insert critter every : " << settings->insertcritterevery << " frames";
			Textmessage::Instance()->add(buf);*/
		}
		break;
		case XK_F6:
		{
			if ( settings->mincritters < settings->mincrittersMax )
				settings->mincritters++;
			stringstream buf;
			buf << "mincritters: "<< settings->mincritters;
			Textmessage::Instance()->add(buf);

/*			settings->insertcritterevery += 100;
			stringstream buf;
			buf << "insert critter every : " << settings->insertcritterevery << " frames";
			Textmessage::Instance()->add(buf);*/
		}
		break;

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
		{
			if ( --settings->critter_killhalfat < settings->critter_killhalfatMin )
				settings->critter_killhalfat = settings->critter_killhalfatMin;
			stringstream buf;
 			buf << "Kill half of vritters at: "<< settings->critter_killhalfat;
			Textmessage::Instance()->add(buf);
		}
		break;
		case XK_F8:
		{
			if ( ++settings->critter_killhalfat > settings->critter_killhalfatMax )
				settings->critter_killhalfat = settings->critter_killhalfatMax;
			stringstream buf;
 			buf << "Kill half of vritters at: "<< settings->critter_killhalfat;
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

		case XK_i:
			world.insertCritter();
		break;

		case XK_k:
			world.killHalfOfCritters();
		break;

		case XK_p:
			pause = !pause;
		break;

		case XK_l:
			sleeper.swap();
		break;

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
		case XK_c:
		{
			settings->colormode++;
			if ( settings->colormode > settings->colormodeMax )
				settings->colormode = settings->colormodeMin;
			stringstream buf;
			buf << "Colormode: "<< settings->colormode;
			Textmessage::Instance()->add(buf);
		}
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
	unsigned int biggest = settings->worldsizeX;
	if ( settings->worldsizeY > biggest )
		biggest = 1.4f*settings->worldsizeY;

// 	camera.position = Vector3f(-0.5f*settings->worldsizeX, -1.1f*biggest, -0.87*settings->worldsizeY);
// 	camera.rotation = Vector3f( 70.0f,  0.0f, 0.0f);

	camera.position = Vector3f( -0.5f*settings->worldsizeX, -1.1f*biggest, -0.5f*settings->worldsizeY);
	camera.rotation = Vector3f( 90.0f,  0.0f, 0.0f);
}

Evolution::~Evolution()
{
}
