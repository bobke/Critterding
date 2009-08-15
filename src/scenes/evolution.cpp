#include "evolution.h"

Evolution::Evolution()
{
	settings = Settings::Instance();
	events = Events::Instance();

	pause = false;
// 	drawCVNeurons = false;

	// events

	events->registerEvent(SDLK_F5,		"dec_critters", 		0.2f,	0.0f, 	0.01f );
	events->registerEvent(SDLK_F6,		"inc_critters", 		0.2f,	0.0f, 	0.01f );

	events->registerEvent(SDLK_KP_MINUS,	"dec_energy", 			0.2f,	0.0f, 	0.01f );
	events->registerEvent(SDLK_KP_PLUS,	"inc_energy", 			0.2f,	0.0f, 	0.01f );

	events->registerEvent(SDLK_F7,		"dec_killhalftrigger", 		0.2f,	0.0f, 	0.01f );
	events->registerEvent(SDLK_F8,		"inc_killhalftrigger", 		0.2f,	0.0f, 	0.01f );

	events->registerEvent(SDLK_F9,		"dec_maxmutations", 		0.2f,	0.0f, 	0.01f );
	events->registerEvent(SDLK_F10,		"inc_maxmutations", 		0.2f,	0.0f, 	0.01f );

	events->registerEvent(SDLK_F11,		"dec_mutationrate", 		0.2f,	0.0f, 	0.01f );
	events->registerEvent(SDLK_F12,		"inc_mutationrate", 		0.2f,	0.0f, 	0.01f );

	events->registerEvent(SDLK_KP_DIVIDE,	"dec_camerasensitivity", 	0.2f,	0.0f, 	0.01f );
	events->registerEvent(SDLK_KP_MULTIPLY,	"inc_camerasensitivity", 	0.2f,	0.0f, 	0.01f );

	sharedTimer* t = events->registerSharedtimer( 0.02f );

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
	// 		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
	// 		glDisable (GL_LIGHTING);
	// 		glDisable(GL_COLOR_MATERIAL);
	// 		glDisable(GL_DITHER);
		glDisable(GL_POLYGON_SMOOTH);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		world.process();

// 			if (world.critters.size() >0 )
// 			{
// 				camera.follow( (btDefaultMotionState*)world.critters[0]->body.mouths[0]->body->getMotionState() );
// 				world.drawWithoutFaces();
// 				world.critters[0]->printVision();
// 			}

		camera.place();
		world.drawWithGrid();


	// 2D
		glDisable (GL_LIGHTING);
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
		

	SDL_GL_SwapBuffers();		

	if ( settings->exit_if_empty && world.critters.size() == 0 )
	{
		cerr << "world is empty, exiting..." << endl;
		exit(0);
	}
}

void Evolution::handlekeyPressed(const KeySym& key)
{
	if ( pause && key != XK_p )
	{
		//usleep(10000);
		return;
	}

	switch (key)
	{
		case SDLK_F1:
			helpinfo.swap();
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
			world.loadAllCritters();
			break;
		case SDLK_PAGEDOWN:
			world.saveAllCritters();
			break;

		case SDLK_i:
			world.insertCritter();
			break;

		case SDLK_k:
			world.killHalfOfCritters();
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

		case SDLK_l:
			sleeper.swap();
			break;

		case SDLK_BACKSPACE:
			resetCamera();
			break;

		case SDLK_c:
		{
			settings->colormode++;
			if ( settings->colormode > settings->colormodeMax )
				settings->colormode = settings->colormodeMin;
			stringstream buf;
			buf << "Colormode: "<< settings->colormode;
			Textmessage::Instance()->add(buf);
		}
		break;

		default:
			events->activateEvent(key);
			break;
	}
}

void Evolution::handlekeyReleased(const KeySym& key)
{
	events->deactivateEvent(key);
}

void Evolution::handleMouseMotion(int x, int y)
{
	if ( mouselook )
	{
		if ( x > 0 )
			camera.lookRight( (float)x/2000 * settings->camerasensitivity );
		else if ( x < 0 )
			camera.lookLeft( (float)x/-2000 * settings->camerasensitivity );

		if ( y > 0 )
			camera.lookDown( (float)y/2000 * settings->camerasensitivity );
		else if ( y < 0 )
			camera.lookUp( (float)y/-2000 * settings->camerasensitivity );
	}
}

void Evolution::handleEvents()
{

	events->processSharedTimers();
	
	if ( events->isActive("dec_critters") )
	{
		if ( settings->mincritters > settings->mincrittersMin )
			settings->mincritters--;
		stringstream buf;
		buf << "mincritters: "<< settings->mincritters;
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("inc_critters") )
	{
		if ( settings->mincritters < settings->mincrittersMax )
			settings->mincritters++;
		stringstream buf;
		buf << "mincritters: "<< settings->mincritters;
		Textmessage::Instance()->add(buf);
	}

	if ( events->isActive("dec_energy") )
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
	if ( events->isActive("inc_energy") )
	{
		settings->freeEnergyInfo += settings->food_maxenergy;
		world.freeEnergy += settings->food_maxenergy;
		stringstream buf;
		buf << "Energy in system: " << (settings->freeEnergyInfo / settings->food_maxenergy);
		Textmessage::Instance()->add(buf);
	}

	if ( events->isActive("dec_killhalftrigger") )
	{
		if ( --settings->critter_killhalfat < settings->critter_killhalfatMin )
			settings->critter_killhalfat = settings->critter_killhalfatMin;
		stringstream buf;
		buf << "Kill half of critters at: "<< settings->critter_killhalfat;
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("inc_killhalftrigger") )
	{
		if ( ++settings->critter_killhalfat > settings->critter_killhalfatMax )
			settings->critter_killhalfat = settings->critter_killhalfatMax;
		stringstream buf;
		buf << "Kill half of critters at: "<< settings->critter_killhalfat;
		Textmessage::Instance()->add(buf);
	}

	if ( events->isActive("dec_mutationrate") )
	{
		if ( settings->critter_mutationrate >= 1 )
			settings->critter_mutationrate -= 1;
		stringstream buf;
		buf << "Mutation Rate: "<< settings->critter_mutationrate << "%";
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("inc_mutationrate") )
	{
		if ( settings->critter_mutationrate <= 99 )
			settings->critter_mutationrate += 1;
		stringstream buf;
		buf << "Mutation Rate: "<< settings->critter_mutationrate << "%";
		Textmessage::Instance()->add(buf);
	}

	if ( events->isActive("dec_maxmutations") )
	{
		if ( settings->critter_maxmutations >= 2 )
			settings->critter_maxmutations -= 1;
		stringstream buf;
		buf << "Max Mutations: "<< settings->critter_maxmutations;
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("inc_maxmutations") )
	{
		if ( settings->critter_maxmutations <= 999 )
			settings->critter_maxmutations += 1;
		stringstream buf;
		buf << "Max Mutations: "<< settings->critter_maxmutations;
		Textmessage::Instance()->add(buf);
	}

	// Camera sensitivity
	if ( events->isActive("inc_camerasensitivity") )
	{
		camera.sensitivity++;
		stringstream buf;
		buf << "Camera Sensitivity: "<< camera.sensitivity;
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("dec_camerasensitivity") )
	{
		if ( camera.sensitivity > 1 )
			camera.sensitivity--;
		stringstream buf;
		buf << "Camera Sensitivity: "<< camera.sensitivity;
		Textmessage::Instance()->add(buf);
	}

	// Camera

	if ( events->isActive("camera_moveup") )
		camera.moveUp(0.01f);

	if ( events->isActive("camera_movedown") )
		camera.moveDown(0.01f);

	if ( events->isActive("camera_moveforward") )
		camera.moveForwardXZ(0.01f);

	if ( events->isActive("camera_movebackward") )
		camera.moveBackwardXZ(0.01f);

	if ( events->isActive("camera_moveleft") )
		camera.moveLeft(0.01f);

	if ( events->isActive("camera_moveright") )
		camera.moveRight(0.01f);

	if ( events->isActive("camera_lookup") )
		camera.lookUp(0.05f);

	if ( events->isActive("camera_lookdown") )
		camera.lookDown(0.05f);

	if ( events->isActive("camera_lookleft") )
		camera.lookLeft(0.05f);

	if ( events->isActive("camera_lookright") )
		camera.lookRight(0.05f);
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
