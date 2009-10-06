#ifdef _WIN32
	#include <unistd.h>
#endif
#include "evolution.h"

Evolution::Evolution()
{
	settings = Settings::Instance();
	events = Events::Instance();

	if ( settings->getCVar("race") == 1 )
		world = new WorldRace();
	else if ( settings->getCVar("testworld") == 1 )
	{
		world = new TestWorld1();
		cerr << "test world yeah" << endl;
	}
	else
		world = new WorldB();

	pause = false;
// 	drawCVNeurons = false;

	unsigned int delay = 150;
	unsigned int speedup = 2;

	events->registerEvent(SDLK_LSHIFT,	"lshift", 			0,	0, 	0 );
	events->registerEvent(SDLK_RSHIFT,	"rshift", 			0,	0, 	0 );

	// events
	events->registerEvent(SDLK_F5,		"dec_critters", 		delay,	0, 	speedup );
	events->registerEvent(SDLK_F6,		"inc_critters", 		delay,	0, 	speedup );

	events->registerEvent(SDLK_KP_MINUS,	"dec_energy", 			delay,	0, 	speedup );
	events->registerEvent(SDLK_KP_PLUS,	"inc_energy", 			delay,	0, 	speedup );

	events->registerEvent(SDLK_F7,		"dec_killhalftrigger", 		delay,	0, 	speedup );
	events->registerEvent(SDLK_F8,		"inc_killhalftrigger", 		delay,	0, 	speedup );

	events->registerEvent(SDLK_F9,		"dec_maxmutations", 		delay,	0, 	speedup );
	events->registerEvent(SDLK_F10,		"inc_maxmutations", 		delay,	0, 	speedup );

	events->registerEvent(SDLK_F11,		"dec_mutationrate", 		delay,	0, 	speedup );
	events->registerEvent(SDLK_F12,		"inc_mutationrate", 		delay,	0, 	speedup );

	events->registerEvent(SDLK_KP_DIVIDE,	"dec_camerasensitivity", 	delay,	0, 	speedup );
	events->registerEvent(SDLK_KP_MULTIPLY,	"inc_camerasensitivity", 	delay,	0, 	speedup );

	sharedTimer* t = events->registerSharedtimer( 20 );

	events->registerEvent(SDLK_HOME,	"camera_moveup", 		t );
	events->registerEvent(SDLK_END,		"camera_movedown", 		t );
	events->registerEvent(SDLK_UP,		"camera_moveforward", 		t );
	events->registerEvent(SDLK_DOWN,	"camera_movebackward", 		t );
	events->registerEvent(SDLK_LEFT,	"camera_moveleft", 		t );
	events->registerEvent(SDLK_RIGHT,	"camera_moveright", 		t );
	events->registerEvent(SDLK_KP2,		"camera_lookup", 		t );
	events->registerEvent(SDLK_KP8,		"camera_lookdown", 		t );
	events->registerEvent(SDLK_KP4,		"camera_lookleft",		t );
	events->registerEvent(SDLK_KP6,		"camera_lookright",		t );
	
	mouselook = false;

	oldx = 0;
	oldy = 0;

	world->init();
}

void Evolution::draw()
{
	if ( pause )
	{
		usleep(20000);
		return;
	}

	handleEvents();

	Timer::Instance()->mark();
	sleeper.mark();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 3D
// 		GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
		GLfloat ambientLight[] = {0.6f, 0.6f, 0.6f, 0.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
// 		GLfloat lightColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat lightColor[] = { 0.04f, 0.04f, 0.04f, 0.0f };
		GLfloat lightPos[] = { 0.5f*settings->getCVar("worldsizeX"), 50.0f, 0.5f*settings->getCVar("worldsizeY"), 1.0f };
// 		GLfloat lightPos1[] = { 0.0f, 20.0f, 0.5f*settings->getCVar("worldsizeY"), 1.0f };
// 		GLfloat lightPos2[] = { settings->getCVar("worldsizeX")+1.0f, 20, 0.5f*settings->getCVar("worldsizeY"), 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
// 		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
// 		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
// 		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
// 		glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
// 		glEnable(GL_LIGHT1);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
// 		glHint(GL_FOG_HINT, GL_FASTEST);
// 		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glShadeModel(GL_FLAT);
// 		glShadeModel(GL_SMOOTH);

		glDisable(GL_DITHER);
		glDisable(GL_POLYGON_SMOOTH);

		world->process();
		world->getGeneralStats();

// 			if (world->critters.size() > 10 )
// 			{
// 				camera.follow( (btDefaultMotionState*)world->critters[5]->body.mouths[0]->body->getMotionState() );
// 				world->drawWithoutFaces();
// 				world->critters[5]->printVision();
// 			}

		world->camera.place();
		world->drawWithGrid();

	// 2D
		glDisable(GL_DEPTH_TEST);
		glDisable (GL_LIGHTING);
		glDisable(GL_LIGHT0);
// 		glDisable(GL_LIGHT1);
		glDisable(GL_COLOR_MATERIAL);
// 		glDisable(GL_DITHER);
		glDisable(GL_CULL_FACE);

		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, *Settings::Instance()->winWidth, *Settings::Instance()->winHeight, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

			canvas.draw();
			infobar.draw();
			infostats.draw(infobar.height());
			statsGraph.draw(infobar.height()+infostats.height());
			Textverbosemessage::Instance()->draw(infobar.height()+infostats.height()+statsGraph.height());
			Textmessage::Instance()->draw();

			world->mouseRayHit = false;
			if (!mouselook && !canvas.mouseFocus )
				world->castMouseRay();

			// hover test
			if ( world->mouseRayHit )
			{
				unsigned int margin = 20;
				unsigned int rmargindistance = 100;
				unsigned int vspacer = 12;
				if ( world->mouseRayHitType == 1 )
				{
					Textprinter::Instance()->print( oldx+margin, oldy,    "food");
					Textprinter::Instance()->print( oldx+margin, oldy+vspacer, "energy");
					Textprinter::Instance()->printR(oldx+rmargindistance, oldy+vspacer, "%1.1f", world->mouseRayHitF->energyLevel);
				}
				else if ( world->mouseRayHitType == 0 )
				{
					Textprinter::Instance()->print( oldx+margin, oldy,    "critter");
					Textprinter::Instance()->print( oldx+margin, oldy+vspacer, "energy");
					Textprinter::Instance()->printR(oldx+rmargindistance, oldy+vspacer, "%1.1f", world->mouseRayHitC->energyLevel);
				}
			}


		glPopMatrix();

	SDL_GL_SwapBuffers();		

	if ( world->critters.size() == 0 && settings->getCVar("exit_if_empty") )
	{
		cerr << "world is empty, exiting..." << endl;
		exit(0);
	}
}

void Evolution::handlekeyPressed(const SDLKey& key)
{
	if ( pause && key != SDLK_p )
		return;

	switch (key)
	{
		case SDLK_F1:
			canvas.children["helpinfo"]->swap();
			break;

		case SDLK_F2:
			infobar.swap();
			break;

		case SDLK_F3:
			infostats.swap();
			break;

		case SDLK_F4:
			Textverbosemessage::Instance()->swap();
			break;

		case SDLK_PAGEUP:
			world->loadAllCritters();
			break;
		case SDLK_PAGEDOWN:
			world->saveAllCritters();
			break;

		case SDLK_g:
			statsGraph.swap();
			break;

		case SDLK_i:
			world->insertCritter();
			break;

		case SDLK_k:
			world->killHalfOfCritters();
			break;

		case SDLK_m:
		{
			mouselook = !mouselook;
			if ( mouselook )
			{
				SDL_WM_GrabInput(SDL_GRAB_ON);
				SDL_ShowCursor(0);
				// clear remaining poll events
				{ SDL_Event e; while (SDL_PollEvent(&e)) {} };
				world->mousepicker->detach();
			}
			else
			{
				SDL_ShowCursor(1);
				SDL_WM_GrabInput(SDL_GRAB_OFF);
			}
		}
			break;

		case SDLK_p:
			pause = !pause;
			break;

		case SDLK_s: // FIXME make use of savedir (declared in world)
		{
			settings->saveProfile();
			stringstream buf;
			buf << "Profile written: ./" << settings->profileName;
			Textmessage::Instance()->add(buf);
		}
		break;

		case SDLK_l:
			sleeper.swap();
			break;

		case SDLK_BACKSPACE:
			world->resetCamera();
			break;

		case SDLK_c:
		{
			settings->increaseCVar("colormode", 1);
			stringstream buf;
			buf << "Colormode: "<< settings->getCVar("colormode");
			Textmessage::Instance()->add(buf);
		}
		break;

#ifndef _WIN32
		case SDLK_f:
		{
			settings->increaseCVar("fullscreen", 1);
			stringstream buf;
			buf << "Fullscreen: "<< settings->getCVar("fullscreen");
			Textmessage::Instance()->add(buf);
		}
		break;
#endif
		default:
			events->activateEvent(key);
			break;
	}
}

void Evolution::handlekeyReleased(const SDLKey& key)
{
	events->deactivateEvent(key);
}

void Evolution::handlemousebuttonPressed(int x, int y, const int& button)
{
//	cerr << "button " << button << " clicked at " << x << "x" << y << endl;
	if ( !mouselook )
	{
		if ( button == 1 )
		{
			canvas.buttonPress();
			world->pickBody( x, y );
		}
	}
}

void Evolution::handlemousebuttonReleased(int x, int y, const int& button)
{
// 	cerr << "button " << button << " released at " << x << "x" << y << endl;
	if ( button == 1 )
	{
		canvas.buttonRelease();
		world->mousepicker->detach();
	}
}

void Evolution::handleMouseMotionAbs(int x, int y)
{
	if ( !mouselook )
	{
		oldx = x;
		oldy = y;
		
		// gui mouse dynamics
		canvas.moveMouse(x, y);

		// world mouse dynamics
		world->calcMouseDirection(x, y);
		world->movePickedBodyTo();
	}
}

void Evolution::handleMouseMotionRel(int x, int y)
{
	if ( mouselook )
	{
		if ( x > 0 )
			world->camera.lookRight( (float)x/100 );
		else if ( x != 0 )
			world->camera.lookLeft( (float)x/-100 );

		if ( y > 0 )
			world->camera.lookDown( (float)y/100 );
		else if ( y != 0 )
			world->camera.lookUp( (float)y/-100 );
	}
}

void Evolution::handleEvents()
{

	events->processSharedTimers();
	
	if ( events->isActive("dec_critters") )
	{
		settings->decreaseCVar("mincritters", 1);
// 		if ( settings->mincritters > settings->mincrittersMin )
// 			settings->mincritters--;
		stringstream buf;
		buf << "mincritters: "<< settings->getCVar("mincritters");
// 		cerr << buf << endl;
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("inc_critters") )
	{
		settings->increaseCVar("mincritters", 1);
// 		if ( settings->mincritters < settings->mincrittersMax )
// 			settings->mincritters++;
		stringstream buf;
		buf << "mincritters: "<< settings->getCVar("mincritters");
		Textmessage::Instance()->add(buf);
	}

	if ( events->isActive("dec_energy") )
	{
		if ( ( settings->freeEnergyInfo - settings->getCVar("food_maxenergy") ) / settings->getCVar("food_maxenergy") >= 0.0f )
		{
			settings->freeEnergyInfo -= settings->getCVar("food_maxenergy");
			world->freeEnergy -= settings->getCVar("food_maxenergy");
		}
		stringstream buf;
		buf << "Energy in system: " << ( settings->freeEnergyInfo / settings->getCVar("food_maxenergy") );
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("inc_energy") )
	{
		settings->freeEnergyInfo += settings->getCVar("food_maxenergy");
		world->freeEnergy += settings->getCVar("food_maxenergy");
		stringstream buf;
		buf << "Energy in system: " << (settings->freeEnergyInfo / settings->getCVar("food_maxenergy"));
		Textmessage::Instance()->add(buf);
	}

	if ( events->isActive("dec_killhalftrigger") )
	{
		settings->decreaseCVar("critter_killhalfat", 1);
		stringstream buf;
		buf << "Kill half of critters at: "<< settings->getCVar("critter_killhalfat");
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("inc_killhalftrigger") )
	{
		settings->increaseCVar("critter_killhalfat", 1);
		stringstream buf;
		buf << "Kill half of critters at: "<< settings->getCVar("critter_killhalfat");
		Textmessage::Instance()->add(buf);
	}

	// mutation settings
	if ( events->isActive("lshift") || events->isActive("rshift") )
	{
		if ( events->isActive("dec_mutationrate") )
		{
			settings->decreaseCVar("body_mutationrate", 1);
			stringstream buf;
			buf << "Body: Mutation Rate: "<< settings->getCVar("body_mutationrate") << "%";
			Textmessage::Instance()->add(buf);
		}
		if ( events->isActive("inc_mutationrate") )
		{
			settings->increaseCVar("body_mutationrate", 1);
			stringstream buf;
			buf << "Body: Mutation Rate: "<< settings->getCVar("body_mutationrate") << "%";
			Textmessage::Instance()->add(buf);
		}
		if ( events->isActive("dec_maxmutations") )
		{
			settings->decreaseCVar("body_maxmutations", 1);
			stringstream buf;
			buf << "Body: Max Mutations: "<< settings->getCVar("body_maxmutations");
			Textmessage::Instance()->add(buf);
		}
		if ( events->isActive("inc_maxmutations") )
		{
			settings->increaseCVar("body_maxmutations", 1);
			stringstream buf;
			buf << "Body: Max Mutations: "<< settings->getCVar("body_maxmutations");
			Textmessage::Instance()->add(buf);
		}
	}
	else	// BRAIN: without shift
	{
		if ( events->isActive("dec_mutationrate") )
		{
			settings->decreaseCVar("brain_mutationrate", 1);
			stringstream buf;
			buf << "Brain: Mutation Rate: "<< settings->getCVar("brain_mutationrate") << "%";
			Textmessage::Instance()->add(buf);
		}
		if ( events->isActive("inc_mutationrate") )
		{
			settings->increaseCVar("brain_mutationrate", 1);
			stringstream buf;
			buf << "Brain: Mutation Rate: "<< settings->getCVar("brain_mutationrate") << "%";
			Textmessage::Instance()->add(buf);
		}
		if ( events->isActive("dec_maxmutations") )
		{
			settings->decreaseCVar("brain_maxmutations", 1);
			stringstream buf;
			buf << "Brain: Max Mutations: "<< settings->getCVar("brain_maxmutations");
			Textmessage::Instance()->add(buf);
		}
		if ( events->isActive("inc_maxmutations") )
		{
			settings->increaseCVar("brain_maxmutations", 1);
			stringstream buf;
			buf << "Brain: Max Mutations: "<< settings->getCVar("brain_maxmutations");
			Textmessage::Instance()->add(buf);
		}
	}

	// Camera sensitivity
	if ( events->isActive("inc_camerasensitivity") )
	{
		settings->increaseCVar("camerasensitivity", 1);
		stringstream buf;
		buf << "Camera Sensitivity: "<< settings->getCVar("camerasensitivity");
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("dec_camerasensitivity") )
	{
		settings->decreaseCVar("camerasensitivity", 1);
		stringstream buf;
		buf << "Camera Sensitivity: "<< settings->getCVar("camerasensitivity");
		Textmessage::Instance()->add(buf);
	}

	// Camera

	if ( events->isActive("camera_moveup") )
	{
		world->camera.moveUpXZ(0.01f);
		world->movePickedBodyFrom();
	}

	if ( events->isActive("camera_movedown") )
	{
		world->camera.moveDownXZ(0.01f);
		world->movePickedBodyFrom();
	}

	if ( events->isActive("camera_moveforward") )
	{
		world->camera.moveForwardXZ(0.01f);
		world->movePickedBodyFrom();
	}

	if ( events->isActive("camera_movebackward") )
	{
		world->camera.moveBackwardXZ(0.01f);
		world->movePickedBodyFrom();
	}

	if ( events->isActive("camera_moveleft") )
	{
		world->camera.moveLeft(0.01f);
		world->movePickedBodyFrom();
	}

	if ( events->isActive("camera_moveright") )
	{
		world->camera.moveRight(0.01f);
		world->movePickedBodyFrom();
	}

	if ( events->isActive("camera_lookup") )
	{
		world->camera.lookUp(0.03f);
		world->calcMouseDirection(oldx, oldy);
		world->movePickedBodyTo();
	}

	if ( events->isActive("camera_lookdown") )
	{
		world->camera.lookDown(0.03f);
		world->calcMouseDirection(oldx, oldy);
		world->movePickedBodyTo();
	}

	if ( events->isActive("camera_lookleft") )
	{
		world->camera.lookLeft(0.03f);
		world->calcMouseDirection(oldx, oldy);
		world->movePickedBodyTo();
	}

	if ( events->isActive("camera_lookright") )
	{
		world->camera.lookRight(0.03f);
		world->calcMouseDirection(oldx, oldy);
		world->movePickedBodyTo();
	}
}

Evolution::~Evolution()
{
}
