#ifdef _WIN32
	#include <unistd.h>
#endif
#include "evolution.h"

# include <math.h>

Evolution::Evolution()
{
	cmd = Commands::Instance();
	settings = Settings::Instance();
	events = Events::Instance();

	drawscene = settings->getCVarPtr("drawscene");
	benchmark = settings->getCVarPtr("benchmark");

	if ( *benchmark == 1 )
	{
		canvas.active = false;
// 		canvas.children["hud"]->active = false;
		settings->setCVar("startseed", 11);
	}

	if ( settings->getCVar("race") == 1 )
		world = new WorldRace();
	else if ( settings->getCVar("roundworld") == 1 )
		world = new Roundworld();
	else
		world = new WorldB();

	cmd->world = world;
	
	if ( !*world->headless )
	{
		static_cast<Hud*>(canvas.children["hud"])->world = world;
		static_cast<Critterview*>(canvas.children["critterview"])->world = world;
		cmd->canvas = &canvas;
	}
	else
	{
		// check if raycastvision is enabled, if not die
		if ( settings->getCVar("critter_raycastvision") == 0 )
		{
			cerr << "headless mode requires critter_raycastvision to be enabled" << endl;
			exit(1);
		}
	}

// 	drawCVNeurons = false;

	unsigned int delay = 200;
	unsigned int speedup = 2;

	// modifiers

	// + 1024 -> buttons pressed
	// + 1124 -> buttons released
	// + 1224 -> mouse axis

	events->registerEvent(1024+1,			"critter_select", execcmd.gen("critter_select"), 0, 0, 0 );
	events->registerEvent(1024+2,			"resetcamera", execcmd.gen("camera_resetposition"), 0, 0, 0 );
	events->registerEvent(1024+3,			"critter_pick", execcmd.gen("critter_pick"), 0, 0, 0 );
	events->registerEvent(1124+3,			"critter_unpick", execcmd.gen("critter_unpick"), 0, 0, 0 );
	events->registerEvent(1024+4,			"keycamera_moveforward", execcmd.gen("camera_moveforward"), 0, 0, 0 );
	events->registerEvent(1024+5,			"keycamera_movebackward", execcmd.gen("camera_movebackward"), 0, 0, 0 );

	events->registerEvent(1224+0,			"camera_lookhorizontal", execcmd.gen("camera_lookhorizontal"), 0, 0, 0 );
	events->registerEvent(1224+1,			"camera_lookvertical", execcmd.gen("camera_lookvertical"), 0, 0, 0 );

	events->registerEvent(SDLK_LSHIFT, 1224+0,	"camera_movehorizontal", execcmd.gen("camera_movehorizontal"), 0, 0, 0 );
	events->registerEvent(SDLK_LSHIFT, 1224+1,	"camera_movevertical", execcmd.gen("camera_movevertical"), 0, 0, 0 );
	events->registerEvent(SDLK_RSHIFT, 1224+0,	"camera_movehorizontal", execcmd.gen("camera_movehorizontal"), 0, 0, 0 );
	events->registerEvent(SDLK_RSHIFT, 1224+1,	"camera_movevertical", execcmd.gen("camera_movevertical"), 0, 0, 0 );
	
	// events
	events->registerEvent(SDLK_TAB,			"swapspeciespanel", execcmd.gen("gui_togglepanel", "speciesview"), 0, 0, 0 );
	events->registerEvent(SDLK_ESCAPE,		"swapexitpanel", execcmd.gen("gui_togglepanel", "exitpanel"), 0, 0, 0 );
	events->registerEvent(SDLK_F1,			"swaphelpinfo", execcmd.gen("gui_togglepanel", "helpinfo"), 0, 0, 0 );
	events->registerEvent(SDLK_F2,			"swapinfobar", execcmd.gen("gui_togglepanel", "infobar"), 0, 0, 0 );
	events->registerEvent(SDLK_F3,			"swapinfostats", execcmd.gen("gui_togglepanel", "infostats"), 0, 0, 0 );
	events->registerEvent(SDLK_F4,			"swaptextverbosemessage", execcmd.gen("gui_togglepanel", "textverbosemessage"), 0, 0, 0 );

	events->registerEvent(SDLK_F5,			"swapstatsgraph", execcmd.gen("gui_togglepanel", "statsgraph"), 0, 0, 0 );
	events->registerEvent(SDLK_F6,			"swapglobalsettingspanel", execcmd.gen("gui_togglepanel", "globalsettingspanel"), 0, 0, 0 );
	events->registerEvent(SDLK_F7,			"swapsettingsbrainpanel", execcmd.gen("gui_togglepanel", "settingsbrainpanel"), 0, 0, 0 );
	events->registerEvent(SDLK_F8,			"swaphud", execcmd.gen("gui_togglepanel", "hud"), 0, 0, 0 );
	
	events->registerEvent(SDLK_r,			"toggle_drawscene", execcmd.gen("settings_increase", "drawscene"), 0, 0, 0 );
	events->registerEvent(SDLK_p,			"toggle_pause", execcmd.gen("toggle_pause"), 0, 0, 0 );
	events->registerEvent(SDLK_l,			"toggle_sleeper", execcmd.gen("toggle_sleeper"), 0, 0, 0 );
	events->registerEvent(SDLK_m,			"toggle_mouselook", execcmd.gen("toggle_mouselook"), 0, 0, 0 );
	events->registerEvent(SDLK_s,			"settings_saveprofile", execcmd.gen("settings_saveprofile"), 0, 0, 0 );

	events->registerEvent(SDLK_h,			"swapcanvas", execcmd.gen("gui_toggle"), 0, 0, 0 );

// 	events->registerEvent(SDLK_F5,			"dec_critters", execcmd.gen("settings_decrease", "mincritters"), delay, 0, speedup );
// 	events->registerEvent(SDLK_F6,			"inc_critters", execcmd.gen("settings_increase", "mincritters"), delay, 0, speedup );
// 	events->registerEvent(SDLK_F7,			"dec_killhalftrigger", execcmd.gen("settings_decrease", "critter_killhalfat"), delay, 0, speedup );
// 	events->registerEvent(SDLK_F8,			"inc_killhalftrigger", execcmd.gen("settings_increase", "critter_killhalfat"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_DIVIDE,		"dec_camerasensitivity", execcmd.gen("settings_decrease", "camerasensitivity"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_MULTIPLY,		"inc_camerasensitivity", execcmd.gen("settings_increase", "camerasensitivity"), delay, 0, speedup );
	events->registerEvent(SDLK_c,			"inc_colormode", execcmd.gen("settings_increase", "colormode"), 0, 0, 0 );

	events->registerEvent(SDLK_F9,			"dec_body_mutationrate", execcmd.gen("settings_decrease", "body_mutationrate"), delay, 0, speedup );
	events->registerEvent(SDLK_F10,			"inc_body_mutationrate", execcmd.gen("settings_increase", "body_mutationrate"), delay, 0, speedup );
	events->registerEvent(SDLK_LSHIFT, SDLK_F9,	"dec_body_maxmutations", execcmd.gen("settings_decrease", "body_maxmutations"), delay, 0, speedup );
	events->registerEvent(SDLK_LSHIFT, SDLK_F10,	"inc_body_maxmutations", execcmd.gen("settings_increase", "body_maxmutations"), delay, 0, speedup );
	events->registerEvent(SDLK_RSHIFT, SDLK_F9,	"dec_body_maxmutations", execcmd.gen("settings_decrease", "body_maxmutations"), delay, 0, speedup );
	events->registerEvent(SDLK_RSHIFT, SDLK_F10,	"inc_body_maxmutations", execcmd.gen("settings_increase", "body_maxmutations"), delay, 0, speedup );
	
	events->registerEvent(SDLK_F11,			"dec_brain_mutationrate", execcmd.gen("settings_decrease", "brain_mutationrate"), delay, 0, speedup );
	events->registerEvent(SDLK_F12,			"inc_brain_mutationrate", execcmd.gen("settings_increase", "brain_mutationrate"), delay, 0, speedup );
	events->registerEvent(SDLK_LSHIFT, SDLK_F11,	"dec_brain_maxmutations", execcmd.gen("settings_decrease", "brain_maxmutations"), delay, 0, speedup );
	events->registerEvent(SDLK_LSHIFT, SDLK_F12,	"inc_brain_maxmutations", execcmd.gen("settings_increase", "brain_maxmutations"), delay, 0, speedup );
	events->registerEvent(SDLK_RSHIFT, SDLK_F11,	"dec_brain_maxmutations", execcmd.gen("settings_decrease", "brain_maxmutations"), delay, 0, speedup );
	events->registerEvent(SDLK_RSHIFT, SDLK_F12,	"inc_brain_maxmutations", execcmd.gen("settings_increase", "brain_maxmutations"), delay, 0, speedup );
	
	events->registerEvent(SDLK_BACKSPACE,		"resetcamera", execcmd.gen("camera_resetposition"), 0, 0, 0 );

	events->registerEvent(SDLK_PAGEUP,		"keyloadAllCritters", execcmd.gen("loadallcritters"), 0, 0, 0 );
	events->registerEvent(SDLK_PAGEDOWN,		"keysaveAllCritters", execcmd.gen("saveallcritters"), 0, 0, 0 );
	events->registerEvent(SDLK_i,			"keyinsertCritter", execcmd.gen("insertcritter"), 0, 0, 0 );
	events->registerEvent(SDLK_k,			"keykillhalfOfcritters", execcmd.gen("killhalfofcritters"), 0, 0, 0 );

	events->registerEvent(SDLK_MINUS,		"keydecreaseenergy", execcmd.gen("decreaseenergy"), delay, 0, speedup );
	events->registerEvent(SDLK_PLUS,		"keyincreaseenergy", execcmd.gen("increaseenergy"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_MINUS,		"keydecreaseenergykp", execcmd.gen("decreaseenergy"), delay, 0, speedup );
	events->registerEvent(SDLK_KP_PLUS,		"keyincreaseenergykp", execcmd.gen("increaseenergy"), delay, 0, speedup );

	sharedTimer* t = events->registerSharedtimer( 20 );
	
	events->registerEvent(SDLK_HOME,		"keycamera_moveup", execcmd.gen("camera_moveup"), t );
	events->registerEvent(SDLK_END,			"keycamera_movedown", execcmd.gen("camera_movedown"), t );
	events->registerEvent(SDLK_UP,			"keycamera_moveforward", execcmd.gen("camera_moveforward"), t );
	events->registerEvent(SDLK_DOWN,		"keycamera_movebackward", execcmd.gen("camera_movebackward"), t );
	events->registerEvent(SDLK_LEFT,		"keycamera_moveleft", execcmd.gen("camera_moveleft"), t );
	events->registerEvent(SDLK_RIGHT,		"keycamera_moveright", execcmd.gen("camera_moveright"), t );

	events->registerEvent(SDLK_KP2,			"keycamera_lookup", execcmd.gen("camera_lookup"), t );
	events->registerEvent(SDLK_KP8,			"keycamera_lookdown", execcmd.gen("camera_lookdown"), t );
	events->registerEvent(SDLK_KP4,			"keycamera_lookleft", execcmd.gen("camera_lookleft"), t );
	events->registerEvent(SDLK_KP6,			"keycamera_lookright", execcmd.gen("camera_lookright"), t );

	events->registerEvent(SDLK_KP1,			"keycamera_rollleft", execcmd.gen("camera_rollleft"), t );
	events->registerEvent(SDLK_KP3,			"keycamera_rollright", execcmd.gen("camera_rollright"), t );

	events->registerEvent(SDLK_f,			"inc_fullscreen", execcmd.gen("settings_increase", "fullscreen"), 0, 0, 0 );

	frameCounter = 0;

	world->init();

}

void Evolution::draw()
{
	frameCounter++;

	Timer::Instance()->mark();
	world->sleeper.mark();

	if ( *benchmark == 1 )
	{
		if ( frameCounter == 10000 )
		{
			float ms = Timer::Instance()->sdl_lasttime - Timer::Instance()->sdl_firsttime;
			cerr << "benchmark: ran " << frameCounter << " frames in " << ms/1000 << " sec, avg: " << (float)frameCounter / ms * 1000 << endl;
			cerr << "and btw, freeEnergy: " << world->freeEnergy << ", critters: " << world->critters.size() << endl;
			exit(0);
		}
	}
	
	if ( !*world->headless )
	{
		events->handlecommands();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 3D
// 		GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
		GLfloat ambientLight[] = {0.6f, 0.6f, 0.6f, 0.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
// 		GLfloat lightColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };

		GLfloat lightColor[] = { 0.04f, 0.04f, 0.04f, 0.0f };

		GLfloat lightPos[] = { 0.5f * *world->worldsizeX, 50.0f, 0.5f * *world->worldsizeY, 1.0f };
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

	if ( !*world->headless )
	{

// 			if (world->critters.size() > 1 )
// 			{
// 				world->camera.follow( (btDefaultMotionState*)world->critters[0]->body.mouths[0]->body->getMotionState() );
// 				world->drawWithoutFaces();
// // 				world->critters[0]->printVision();
// 			}

		world->camera.place();

		if ( *drawscene == 1 )
		{
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
		}

	// 2D
		if ( canvas.active )
		{
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

			if ( *drawscene == 1 )
			{
				world->mouseRayHit = false;
				if (!world->mouselook && !canvas.mouseFocus )
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
						Textprinter::Instance()->print( world->mousex+margin, world->mousey,    "food");
						Textprinter::Instance()->print( world->mousex+margin, world->mousey+vspacer, "energy");
						Textprinter::Instance()->print(world->mousex+rmargindistance, world->mousey+vspacer, "%1.1f", static_cast<const Food*>(world->mouseRayHitEntity)->energyLevel);
					}
					else if ( world->mouseRayHitEntity->type == 0 )
					{
						CritterB* c = static_cast<const CritterB*>(world->mouseRayHitEntity);
						Textprinter::Instance()->print( world->mousex+margin, world->mousey,    "critter");
						Textprinter::Instance()->print(world->mousex+rmargindistance, world->mousey, "%1i", c->critterID);
						Textprinter::Instance()->print( world->mousex+margin, world->mousey+vspacer, "energy");
						Textprinter::Instance()->print(world->mousex+rmargindistance, world->mousey+vspacer, "%1.1f", c->energyLevel);
					}
				}
			}
		glPopMatrix();
		}

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
	switch (key)
	{
		default:
			events->activateEvent(key);
// 			events->handlecommands();
			break;
	}
}

void Evolution::handlekeyReleased(const SDLKey& key)
{
	events->deactivateEvent(key);
}

void Evolution::handlemousebuttonPressed(const int& button)
{
// 	if ( !world->mouselook )
// 	{
		events->activateEvent(button+1024);
		canvas.buttonPress(button);
// 	}
}

void Evolution::handlemousebuttonReleased(const int& button)
{
	events->deactivateEvent(button+1024);
	events->activateEvent(button+1124);
	canvas.buttonRelease(button);
}

void Evolution::handleMouseMotionAbs(int x, int y)
{
	if ( !world->mouselook )
	{
		world->mousex = x;
		world->mousey = y;
		
		// gui mouse dynamics
		canvas.moveMouse(x, y);

		// world mouse dynamics
		world->calcMouseDirection();
		world->movePickedBodyTo();
	}
}

void Evolution::handleMouseMotionRel(int x, int y)
{
	if ( world->mouselook )
	{
		world->relx = x;
		world->rely = y;
		events->activateEvent(1224+0);
		events->activateEvent(1224+1);
	}
}

Evolution::~Evolution()
{
	delete world;
}
