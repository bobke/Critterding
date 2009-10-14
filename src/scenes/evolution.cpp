#ifdef _WIN32
	#include <unistd.h>
#endif
#include "evolution.h"

Evolution::Evolution()
{
	cmd = Commands::Instance();
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

	cmd->world = world;
	cmd->canvas = &canvas;
	
	pause = false;
// 	drawCVNeurons = false;

	unsigned int delay = 333;
	unsigned int speedup = 20;

	// events
	events->registerEvent(SDLK_F5,		"dec_critters", execcmd.gen("settings_decrease", "mincritters"), delay, 0, speedup );
	events->registerEvent(SDLK_F6,		"inc_critters", execcmd.gen("settings_increase", "mincritters"), delay, 0, speedup );
	events->registerEvent(SDLK_F7,		"dec_killhalftrigger", execcmd.gen("settings_decrease", "critter_killhalfat"), delay, 0, speedup );
	events->registerEvent(SDLK_F8,		"inc_killhalftrigger", execcmd.gen("settings_increase", "critter_killhalfat"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_DIVIDE,	"dec_camerasensitivity", execcmd.gen("settings_decrease", "camerasensitivity"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_MULTIPLY,	"inc_camerasensitivity", execcmd.gen("settings_increase", "camerasensitivity"), delay, 0, speedup );
	events->registerEvent(SDLK_c,		"inc_colormode", execcmd.gen("settings_increase", "colormode"), 0, 0, 0 );
	events->registerEvent(SDLK_BACKSPACE,	"resetcamera", execcmd.gen("camera_resetposition"), 0, 0, 0 );

	events->registerEvent(SDLK_ESCAPE,	"swapexitpanel", execcmd.gen("gui_togglepanel", "exitpanel"), 0, 0, 0 );
	events->registerEvent(SDLK_F1,		"swaphelpinfo", execcmd.gen("gui_togglepanel", "helpinfo"), 0, 0, 0 );
	events->registerEvent(SDLK_F2,		"swapinfobar", execcmd.gen("gui_togglepanel", "infobar"), 0, 0, 0 );
	events->registerEvent(SDLK_F3,		"swapinfostats", execcmd.gen("gui_togglepanel", "infostats"), 0, 0, 0 );
	events->registerEvent(SDLK_F4,		"swaptextverbosemessage", execcmd.gen("gui_togglepanel", "textverbosemessage"), 0, 0, 0 );
	events->registerEvent(SDLK_b,		"swapsettingsbrainpanel", execcmd.gen("gui_togglepanel", "settingsbrainpanel"), 0, 0, 0 );
	events->registerEvent(SDLK_e,		"swapsettingspanel", execcmd.gen("gui_togglepanel", "settingspanel"), 0, 0, 0 );
	events->registerEvent(SDLK_g,		"swapstatsgraph", execcmd.gen("gui_togglepanel", "statsgraph"), 0, 0, 0 );

	events->registerEvent(SDLK_PAGEUP,	"keyloadAllCritters", execcmd.gen("loadallcritters"), 0, 0, 0 );
	events->registerEvent(SDLK_PAGEDOWN,	"keysaveAllCritters", execcmd.gen("saveallcritters"), 0, 0, 0 );
	events->registerEvent(SDLK_i,		"keyinsertCritter", execcmd.gen("insertcritter"), 0, 0, 0 );
	events->registerEvent(SDLK_k,		"keykillhalfOfcritters", execcmd.gen("killhalfofcritters"), 0, 0, 0 );

	events->registerEvent(SDLK_KP_MINUS,	"keydecreaseenergy", execcmd.gen("decreaseenergy"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_PLUS,	"keyincreaseenergy", execcmd.gen("increaseenergy"), delay, 0, speedup );

	sharedTimer* t = events->registerSharedtimer( 20 );
	// FIXME : THESE USE THE OLD METHOD, CONVERT THESE, THEN CLEAN UP EVENTS.CPP (massive cleanup required, no struct)

	events->registerEvent(SDLK_LSHIFT,	"lshift", 			0,	0, 	0 );
	events->registerEvent(SDLK_RSHIFT,	"rshift", 			0,	0, 	0 );

	events->registerEvent(SDLK_F9,		"dec_maxmutations", 		delay,	0, 	speedup );
	events->registerEvent(SDLK_F10,		"inc_maxmutations", 		delay,	0, 	speedup );
	events->registerEvent(SDLK_F11,		"dec_mutationrate", 		delay,	0, 	speedup );
	events->registerEvent(SDLK_F12,		"inc_mutationrate", 		delay,	0, 	speedup );
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


	
#ifndef _WIN32
	events->registerEvent(SDLK_f, "inc_fullscreen", execcmd.gen("settings_increase", "fullscreen"), 0, 0, 0 );
#endif	
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

// 			if (world->critters.size() > 1 )
// 			{
// 				world->camera.follow( (btDefaultMotionState*)world->critters[0]->body.mouths[0]->body->getMotionState() );
// 				world->drawWithoutFaces();
// // 				world->critters[0]->printVision();
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

			world->mouseRayHit = false;
			if (!mouselook && !canvas.mouseFocus )
				world->castMouseRay();

			// hover test
			if ( world->mouseRayHit )
			{
				unsigned int margin = 20;
				unsigned int rmargindistance = 100;
				unsigned int vspacer = 12;
				glColor3f(1.0f, 1.0f, 1.0f);
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

// 		case SDLK_BACKSPACE:
// 			world->resetCamera();
// 			break;

// 		case SDLK_c:
// 		{
// 			settings->increaseCVar("colormode", 1);
// 			stringstream buf;
// 			buf << "Colormode: "<< settings->getCVar("colormode");
// 			Textmessage::Instance()->add(buf);
// 		}
// 		break;

#ifndef _WIN32
/*		case SDLK_f:
		{
			settings->increaseCVar("fullscreen", 1);
			stringstream buf;
			buf << "Fullscreen: "<< settings->getCVar("fullscreen");
			Textmessage::Instance()->add(buf);
		}
		break;*/
#endif
		default:
			events->activateEvent(key);
			events->handlecommands();
// 			cerr << "activating event" << endl;
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
	events->handlecommands();

/*	if ( events->isActive("dec_energy") )
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
*/
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
