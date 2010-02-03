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
		world = new TestWorld2();
// 		cerr << "test world yeah" << endl;
	}
	else
		world = new WorldB();

	world->mousex = &oldx;
	world->mousey = &oldy;
	
	cmd->world = world;
	static_cast<Hud*>(canvas.children["hud"])->world = world;
	static_cast<Critterview*>(canvas.children["critterview"])->world = world;
	cmd->canvas = &canvas;
	
	pause = false;
// 	drawCVNeurons = false;

	unsigned int delay = 200;
	unsigned int speedup = 2;

	// events
	events->registerEvent(SDLK_ESCAPE,	"swapexitpanel", execcmd.gen("gui_togglepanel", "exitpanel"), 0, 0, 0 );
	events->registerEvent(SDLK_F1,		"swaphelpinfo", execcmd.gen("gui_togglepanel", "helpinfo"), 0, 0, 0 );
	events->registerEvent(SDLK_F2,		"swapinfobar", execcmd.gen("gui_togglepanel", "infobar"), 0, 0, 0 );
	events->registerEvent(SDLK_F3,		"swapinfostats", execcmd.gen("gui_togglepanel", "infostats"), 0, 0, 0 );
	events->registerEvent(SDLK_F4,		"swaptextverbosemessage", execcmd.gen("gui_togglepanel", "textverbosemessage"), 0, 0, 0 );

	events->registerEvent(SDLK_F5,		"swapstatsgraph", execcmd.gen("gui_togglepanel", "statsgraph"), 0, 0, 0 );
	events->registerEvent(SDLK_F6,		"swapglobalsettingspanel", execcmd.gen("gui_togglepanel", "globalsettingspanel"), 0, 0, 0 );
	events->registerEvent(SDLK_F7,		"swapsettingsbrainpanel", execcmd.gen("gui_togglepanel", "settingsbrainpanel"), 0, 0, 0 );
	events->registerEvent(SDLK_F8,		"swaphud", execcmd.gen("gui_togglepanel", "hud"), 0, 0, 0 );
	
// 	events->registerEvent(SDLK_F5,		"dec_critters", execcmd.gen("settings_decrease", "mincritters"), delay, 0, speedup );
// 	events->registerEvent(SDLK_F6,		"inc_critters", execcmd.gen("settings_increase", "mincritters"), delay, 0, speedup );
// 	events->registerEvent(SDLK_F7,		"dec_killhalftrigger", execcmd.gen("settings_decrease", "critter_killhalfat"), delay, 0, speedup );
// 	events->registerEvent(SDLK_F8,		"inc_killhalftrigger", execcmd.gen("settings_increase", "critter_killhalfat"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_DIVIDE,	"dec_camerasensitivity", execcmd.gen("settings_decrease", "camerasensitivity"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_MULTIPLY,	"inc_camerasensitivity", execcmd.gen("settings_increase", "camerasensitivity"), delay, 0, speedup );
	events->registerEvent(SDLK_c,		"inc_colormode", execcmd.gen("settings_increase", "colormode"), 0, 0, 0 );

	events->registerEvent(SDLK_F9,		"dec_body_mutationrate", execcmd.gen("settings_decrease", "body_mutationrate"), delay, 0, speedup );
	events->registerEvent(SDLK_F10,		"inc_body_mutationrate", execcmd.gen("settings_increase", "body_mutationrate"), delay, 0, speedup );
	events->registerEvent(SDLK_F11,		"dec_brain_mutationrate", execcmd.gen("settings_decrease", "brain_mutationrate"), delay, 0, speedup );
	events->registerEvent(SDLK_F12,		"inc_brain_mutationrate", execcmd.gen("settings_increase", "brain_mutationrate"), delay, 0, speedup );
	
	events->registerEvent(SDLK_BACKSPACE,	"resetcamera", execcmd.gen("camera_resetposition"), 0, 0, 0 );

	events->registerEvent(SDLK_PAGEUP,	"keyloadAllCritters", execcmd.gen("loadallcritters"), 0, 0, 0 );
	events->registerEvent(SDLK_PAGEDOWN,	"keysaveAllCritters", execcmd.gen("saveallcritters"), 0, 0, 0 );
	events->registerEvent(SDLK_i,		"keyinsertCritter", execcmd.gen("insertcritter"), 0, 0, 0 );
	events->registerEvent(SDLK_k,		"keykillhalfOfcritters", execcmd.gen("killhalfofcritters"), 0, 0, 0 );

	events->registerEvent(SDLK_MINUS,	"keydecreaseenergy", execcmd.gen("decreaseenergy"), delay, 0, speedup );
	events->registerEvent(SDLK_PLUS,	"keyincreaseenergy", execcmd.gen("increaseenergy"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_MINUS,	"keydecreaseenergykp", execcmd.gen("decreaseenergy"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_PLUS,	"keyincreaseenergykp", execcmd.gen("increaseenergy"), delay, 0, speedup );

	sharedTimer* t = events->registerSharedtimer( 20 );
	
	events->registerEvent(SDLK_HOME,	"keycamera_moveup", execcmd.gen("camera_moveup"), t );
	events->registerEvent(SDLK_END,		"keycamera_movedown", execcmd.gen("camera_movedown"), t );
	events->registerEvent(SDLK_UP,		"keycamera_moveforward", execcmd.gen("camera_moveforward"), t );
	events->registerEvent(SDLK_DOWN,	"keycamera_movebackward", execcmd.gen("camera_movebackward"), t );
	events->registerEvent(SDLK_LEFT,	"keycamera_moveleft", execcmd.gen("camera_moveleft"), t );
	events->registerEvent(SDLK_RIGHT,	"keycamera_moveright", execcmd.gen("camera_moveright"), t );

	events->registerEvent(SDLK_KP2,		"keycamera_lookup", execcmd.gen("camera_lookup"), t );
	events->registerEvent(SDLK_KP8,		"keycamera_lookdown", execcmd.gen("camera_lookdown"), t );
	events->registerEvent(SDLK_KP4,		"keycamera_lookleft", execcmd.gen("camera_lookleft"), t );
	events->registerEvent(SDLK_KP6,		"keycamera_lookright", execcmd.gen("camera_lookright"), t );

	events->registerEvent(SDLK_KP1,		"keycamera_rollleft", execcmd.gen("camera_rollleft"), t );
	events->registerEvent(SDLK_KP3,		"keycamera_rollright", execcmd.gen("camera_rollright"), t );

	events->registerEvent(SDLK_f, "inc_fullscreen", execcmd.gen("settings_increase", "fullscreen"), 0, 0, 0 );

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

	Timer::Instance()->mark();
	sleeper.mark();

	if ( !settings->getCVar("headless") )
	{

		handleEvents();
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
// 		glEnable(GL_CULL_FACE);
// 		glCullFace(GL_BACK);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
// 		glHint(GL_FOG_HINT, GL_FASTEST);
// 		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glShadeModel(GL_FLAT);
// 		glShadeModel(GL_SMOOTH);

		glDisable(GL_DITHER);
		glDisable(GL_POLYGON_SMOOTH);
	}

		world->process();
		world->getGeneralStats();

	if ( !settings->getCVar("headless") )
	{

// 			if (world->critters.size() > 1 )
// 			{
// 				world->camera.follow( (btDefaultMotionState*)world->critters[0]->body.mouths[0]->body->getMotionState() );
// 				world->drawWithoutFaces();
// // 				world->critters[0]->printVision();
// 			}

		world->camera.place();
		world->drawWithGrid();

		// draw selected info
		btScalar position[16];
		btTransform trans;
		trans.setIdentity();

		btTransform up;
		up.setIdentity();
		up.setOrigin( btVector3(0.0f, 0.2f, 0.0f) );

		for ( unsigned int i=0; i < world->critterselection->clist.size(); i++ )
		{
			trans.setOrigin(world->critterselection->clist[i]->body.mouths[0]->ghostObject->getWorldTransform().getOrigin());
			trans.getOrigin().setY(trans.getOrigin().getY()+0.5f);
			trans.setBasis(world->camera.position.getBasis());
			trans *= up;
			trans.getOpenGLMatrix(position);

			glPushMatrix(); 
			glMultMatrixf(position);

				glColor3f(1.5f, 1.5f, 1.5f);
				glBegin(GL_LINES);
					glVertex2f(-0.2f, 0.05f);
					glVertex2f(-0.2f,-0.05f);

					glVertex2f(-0.2f,-0.05f);
					glVertex2f(0.2f, -0.05f);

					glVertex2f(0.2f, -0.05f);
					glVertex2f(0.2f,  0.05f);

					glVertex2f(0.2f,  0.05f);
					glVertex2f(-0.2f, 0.05f);
				glEnd();

			glPopMatrix();
		}

	// 2D
		glDisable(GL_DEPTH_TEST);
		glDisable (GL_LIGHTING);
		glDisable(GL_LIGHT0);
// 		glDisable(GL_LIGHT1);
		glDisable(GL_COLOR_MATERIAL);
// 		glDisable(GL_DITHER);
// 		glDisable(GL_CULL_FACE);

		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, *Settings::Instance()->winWidth, *Settings::Instance()->winHeight, 0, 0, 1);
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
				unsigned int rmargindistance = 70;
				unsigned int vspacer = 12;
				glColor3f(1.0f, 1.0f, 1.0f);
				if ( world->mouseRayHitEntity->type == 1 )
				{
					Textprinter::Instance()->print( oldx+margin, oldy,    "food");
					Textprinter::Instance()->print( oldx+margin, oldy+vspacer, "energy");
					Textprinter::Instance()->print(oldx+rmargindistance, oldy+vspacer, "%1.1f", static_cast<const Food*>(world->mouseRayHitEntity)->energyLevel);
				}
				else if ( world->mouseRayHitEntity->type == 0 )
				{
					CritterB* c = static_cast<const CritterB*>(world->mouseRayHitEntity);
					Textprinter::Instance()->print( oldx+margin, oldy,    "critter");
					Textprinter::Instance()->print(oldx+rmargindistance, oldy, "%1i", c->critterID);
					Textprinter::Instance()->print( oldx+margin, oldy+vspacer, "energy");
					Textprinter::Instance()->print(oldx+rmargindistance, oldy+vspacer, "%1.1f", c->energyLevel);
				}
			}
		glPopMatrix();

		SDL_GL_SwapBuffers();		
	}

	if ( world->critters.size() == 0 && settings->getCVar("exit_if_empty") )
	{
		cerr << "world is empty, exiting..." << endl;
		cmd->quit();
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
#ifdef _WIN32
				SDL_WarpMouse(0,0);
#endif
				SDL_WM_GrabInput(SDL_GRAB_ON);
				SDL_ShowCursor(SDL_DISABLE);
				// clear remaining poll events
				{ SDL_Event e; while (SDL_PollEvent(&e)) {} };
				
				// release picked objects
				world->mousepicker->detach();
			}
			else
			{
				SDL_ShowCursor(SDL_ENABLE);
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
			Logbuffer::Instance()->add(buf);
		}
		break;

		case SDLK_l:
			sleeper.swap();
			break;

		default:
			events->activateEvent(key);
			events->handlecommands();
			break;
	}
}

void Evolution::handlekeyReleased(const SDLKey& key)
{
	events->deactivateEvent(key);
}

void Evolution::handlemousebuttonPressed(int x, int y, const int& button)
{
// 	cerr << "button " << button << " clicked at " << x << "x" << y << endl;
	if ( !mouselook )
	{
		canvas.buttonPress(button);
		if ( button == 1 )
			world->selectBody( x, y );
		else if ( button == 2 )
			world->resetCamera();
		else if ( button == 3 )
			world->pickBody( x, y );
		else if ( button == 4 )
			world->moveInMouseDirection(true);
		else if ( button == 5 )
			world->moveInMouseDirection(false);
	}
}

void Evolution::handlemousebuttonReleased(int x, int y, const int& button)
{
// 	cerr << "button " << button << " released at " << x << "x" << y << endl;
	canvas.buttonRelease(button);
	if ( button == 1 )
		;
	else if ( button == 3 )
		world->mousepicker->detach();
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
		world->calcMouseDirection();
		world->movePickedBodyTo();
	}
}

void Evolution::handleMouseMotionRel(int x, int y)
{
	if ( mouselook )
	{
		if ( x > 0 )
			world->camera.lookRight( (float)x/3000 );
		else if ( x != 0 )
			world->camera.lookLeft( (float)x/-3000 );

		if ( y > 0 )
			world->camera.lookDown( (float)y/3000 );
		else if ( y != 0 )
			world->camera.lookUp( (float)y/-3000 );
	}
}

void Evolution::handleEvents()
{
	events->processSharedTimers();
	events->handlecommands();
}

Evolution::~Evolution()
{
	delete world;
}
