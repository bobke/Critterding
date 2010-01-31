#include "critterview.h"

Critterview::Critterview()
{
	critterselection = Critterselection::Instance();
	
	active = false;
	isMovable = true;

	// action button settings
	unsigned int bwidth = 90;
	unsigned int bheight = 18;
	unsigned int bspacing = 2;
	unsigned int totalbuttonheight = (2*bheight) + bspacing;

	v_width = 386;
	v_height = 150;

	int buttons_starty = v_height - totalbuttonheight-10;

	position.x = 10;
	position.y = 50;

	currentCritter = 0;

	// text widgets
	v_spacer = 14; v_space = 3;
	v_space += v_spacer; addWidgetText( "cv_cid", 10, v_space, "Critter" );
	v_space += v_spacer; addWidgetText( "cv_ad", 10, v_space, "Adam Distance" );
	v_space += v_spacer; addWidgetText( "cv_age", 10, v_space, "Age" );
		addWidgetText( "cv_age_/", 200, v_space, "/" );
		addWidgetText( "cv_age_max", 210, v_space, settings->getCVarPtr("critter_maxlifetime") );

	v_space += v_spacer; addWidgetText( "cv_energy", 10, v_space, "Energy" );
		addWidgetText( "cv_energy_/", 200, v_space, "/" );
		addWidgetText( "cv_energy_max", 210, v_space, settings->getCVarPtr("critter_maxenergy") );

	v_space += v_spacer; addWidgetText( "cv_neurons", 10, v_space, "Neurons" );
	v_space += v_spacer; addWidgetText( "cv_synapses", 10, v_space, "Synapses" );
	
	// view widgets
	viewbutton = addWidgetButton( "cv_view", Vector2i(0+v_width-60, 35), Vector2i(50, 50), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );

	// close button
	addWidgetButton( "cv_close", Vector2i(v_width-25, 10), Vector2i(15, 15), "x", cmd.gen("gui_togglepanel", "critterview"), 0, 0, 0 );

	// action buttons
	unsigned int c_width = 10;
	unsigned int c_height = buttons_starty;
	addWidgetButton( "cv_action_kill", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "kill", cmd.gen("cs_kill"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "cv_action_brainview", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "brainview", cmd.gen("gui_togglepanel", "brainview"), 0, 0, 0 );
	
	c_width += bwidth + bspacing;
	c_height = buttons_starty;
	addWidgetButton( "cv_action_duplicate", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "duplicate", cmd.gen("cs_duplicate"), 0, 0, 0 );
	
	c_height += bspacing + bheight;
	addWidgetButton( "cv_action_spawnbrainmutant", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "brain mutant", cmd.gen("cs_spawnbrainmutant"), 0, 0, 0 );

	c_width += bwidth + bspacing;
	c_height = buttons_starty;
	addWidgetButton( "cv_action_spawnbodymutant", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "body mutant", cmd.gen("cs_spawnbodymutant"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "cv_action_spawnbrainbodymutant", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "brain+body m", cmd.gen("cs_spawnbrainbodymutant"), 0, 0, 0 );

	c_width += bwidth + bspacing;
	c_height = buttons_starty;
	addWidgetButton( "cv_action_feed", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "feed", cmd.gen("cs_feed"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "cv_action_resetage", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "reset age", cmd.gen("cs_resetage"), 0, 0, 0 );
}

void Critterview::draw()
{
	if ( critterselection->cv_activate )
	{
		active = true;
		critterselection->cv_activate = false;
	}
	
	if ( critterselection->selectedCritter == 0 )
	{
		active = false;
		currentCritter = 0;
	}

	if (active)
	{
		if ( critterselection->selectedCritter != currentCritter )
			currentCritter = critterselection->selectedCritter;

		drawBackground();
		drawBorders();
		// draw the rest
		drawChildren();
		
		// draw values of critter
		v_space = 0;
		v_space += v_spacer; textprinter->print( absPosition.x+110, absPosition.y+v_space, critterselection->selectedCritter->critterID );
		v_space += v_spacer; textprinter->print( absPosition.x+110, absPosition.y+v_space, critterselection->selectedCritter->adamdist );
 		v_space += v_spacer; textprinter->print( absPosition.x+110, absPosition.y+v_space, critterselection->selectedCritter->totalFrames );
 		v_space += v_spacer; textprinter->print( absPosition.x+110, absPosition.y+v_space, "%1.1f", critterselection->selectedCritter->energyLevel );
 		v_space += v_spacer; textprinter->print( absPosition.x+110, absPosition.y+v_space, critterselection->selectedCritter->brain.totalNeurons );
 		v_space += v_spacer; textprinter->print( absPosition.x+110, absPosition.y+v_space, critterselection->selectedCritter->brain.totalSynapses );
			textprinter->print( absPosition.x+200, absPosition.y+v_space, "%5.2f avg", (float)critterselection->selectedCritter->brain.totalSynapses / critterselection->selectedCritter->brain.totalNeurons );


		// draw gl view
			glViewport(viewbutton->absPosition.x, *settings->winHeight-50-viewbutton->absPosition.y, 50, 50);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glFrustum( -0.05f, 0.05f,-0.05f,0.05f, 0.1f, 10000.0f);
			critterselection->selectedCritter->body.mouths[0]->ghostObject->getWorldTransform().inverse().getOpenGLMatrix(viewposition);
			glMultMatrixf(viewposition);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			world->drawWithinCritterSight(critterselection->selectedCritter);

		// switch back to 2d 
			world->camera.place();
			glPushMatrix();
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, *settings->winWidth, *settings->winHeight, 0, 0, 1);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
	}
	
}

Critterview::~Critterview()
{
}
