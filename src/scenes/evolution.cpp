#include "evolution.h"

Evolution::Evolution()
{
	settings = Settings::Instance();
	camerasensitivity = settings->getCVarPtr("camerasensitivity");

	events = Events::Instance();

	pause = false;
// 	drawCVNeurons = false;

	events->registerEvent(SDLK_LSHIFT,	"lshift", 			0.0f,	0.0f, 	0.0f );
	events->registerEvent(SDLK_RSHIFT,	"rshift", 			0.0f,	0.0f, 	0.0f );

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

	if ( settings->getCVar("autoload") )
		world.loadAllCritters();

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
		GLfloat lightPos[] = { 0.5f*settings->getCVar("worldsizeX"), 20, 0.5f*settings->getCVar("worldsizeY"), 1.0f };
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

// 			if (world.critters.size() > 10 )
// 			{
// 				camera.follow( (btDefaultMotionState*)world.critters[5]->body.mouths[0]->body->getMotionState() );
// 				world.drawWithoutFaces();
// 				world.critters[5]->printVision();
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

	if ( world.critters.size() == 0 && settings->getCVar("exit_if_empty") )
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
		case SDL_BUTTON(SDL_BUTTON_LEFT):
			helpinfo.swap();
			break;

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
			resetCamera();
			break;

		case SDLK_c:
		{
			settings->increaseCVar("colormode", 1);
			stringstream buf;
			buf << "Colormode: "<< settings->getCVar("colormode");
			Textmessage::Instance()->add(buf);
// 			*Textmessage::Instance() << "Colormode: "<< settings->getCVar("colormode");
			
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

void Evolution::handlemousebuttonPressed(int x, int y, const int& button)
{
	cerr << "button " << button << " clicked at " << x << "x" << y << endl;
	btVector3 direction = getRayTo(x, y);
	world.castRay(camera.position, direction);
}

btVector3 Evolution::getRayTo(int x,int y)
{
	float directiondepth = 10000.f;
	btVector3 rayFrom = btVector3( camera.position.x, camera.position.y, camera.position.z );

	float reusedX = (360.0f-camera.rotation.x) * 0.0174532925f;
	float reusedY = (camera.rotation.y) * 0.0174532925f;
	btVector3 rayForward = btVector3( 0.0f + sin(reusedY) * cos(reusedX),
					  0.0f - sin(reusedX),
					  0.0f + cos(reusedY) * cos(reusedX) );

	rayForward *= directiondepth;

	btVector3 vertical = btVector3( 0.0f - sin(reusedY) * sin(reusedX),
					0.0f - cos(reusedX),
					0.0f - cos(reusedY) * sin(reusedX) );

	btVector3 hor = rayForward.cross(vertical);
	hor.normalize();
 	vertical = hor.cross(rayForward);
	vertical.normalize();

	hor *= directiondepth;
	vertical *= directiondepth;

	if (*settings->winWidth > *settings->winHeight)
		hor *= ((float)*settings->winWidth / *settings->winHeight);
	else
		vertical *= ((float)*settings->winHeight / *settings->winWidth);

	btVector3 rayToCenter = rayFrom + rayForward;

	btVector3 rayTo = rayToCenter - (0.5f * hor) + (0.5f * vertical);
	rayTo += x * (hor * (1.0f/(*settings->winWidth)));
	rayTo -= y * (vertical * (1.0f/(*settings->winHeight)));
	return rayTo;
}

void Evolution::handlemousebuttonReleased(int x, int y, const int& button)
{
	cerr << "button " << button << " released at " << x << "x" << y << endl;
}


void Evolution::handleMouseMotion(int x, int y)
{
	if ( mouselook )
	{
		if ( x > 0 )
			camera.lookRight( (float)x/2000 * *camerasensitivity );
		else if ( x != 0 )
			camera.lookLeft( (float)x/-2000 * *camerasensitivity );

		if ( y > 0 )
			camera.lookDown( (float)y/2000 * *camerasensitivity );
		else if ( y != 0 )
			camera.lookUp( (float)y/-2000 * *camerasensitivity );
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
			world.freeEnergy -= settings->getCVar("food_maxenergy");
		}
		stringstream buf;
		buf << "Energy in system: " << ( settings->freeEnergyInfo / settings->getCVar("food_maxenergy") );
		Textmessage::Instance()->add(buf);
	}
	if ( events->isActive("inc_energy") )
	{
		settings->freeEnergyInfo += settings->getCVar("food_maxenergy");
		world.freeEnergy += settings->getCVar("food_maxenergy");
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
	unsigned int biggest = settings->getCVar("worldsizeX");
	if ( settings->getCVar("worldsizeY") > biggest )
		biggest = 1.4f*settings->getCVar("worldsizeY");

// 	camera.position = Vector3f(-0.5f*settings->worldsizeX, -1.1f*biggest, -0.87*settings->worldsizeY);
// 	camera.rotation = Vector3f( 70.0f,  0.0f, 0.0f);

	camera.position = Vector3f( -0.5f*settings->getCVar("worldsizeX"), -1.1f*biggest, -0.5f*settings->getCVar("worldsizeY"));
	camera.rotation = Vector3f( 90.0f,  0.0f, 0.0f);
}

Evolution::~Evolution()
{
}
