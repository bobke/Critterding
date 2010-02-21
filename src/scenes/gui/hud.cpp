#include "hud.h"
#include "../../gui/button.h"

Hud::Hud()
{
	active = true;

	v_height = 62;
	v_width = 800;
	position.x = 0;
	position.y = *settings->winHeight - v_height;

	critterselection = Critterselection::Instance();

	unsigned int bwidth = 60;
	unsigned int bheight = 18;
	unsigned int bspacing = 2;
	
	unsigned int c_width = bspacing;
	unsigned int c_height = bspacing;
	addWidgetButton( "hud_exit", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "exit", cmd.gen("gui_togglepanel", "exitpanel"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_graph", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "graph", cmd.gen("gui_togglepanel", "statsgraph"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_stats", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "stats", cmd.gen("gui_togglepanel", "infostats"), 0, 0, 0 );


	c_width += bspacing + bwidth;
	c_height = bspacing;
	addWidgetButton( "hud_events", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "events", cmd.gen("gui_togglepanel", "textverbosemessage"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_settings", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "settings", cmd.gen("gui_togglepanel", "globalsettingspanel"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_mutationpanel", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "mutation", cmd.gen("gui_togglepanel", "mutationpanel"), 0, 0, 0 );


	c_width += bspacing + bwidth;
	c_height = bspacing;
	addWidgetButton( "hud_brainpanel", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "brain", cmd.gen("gui_togglepanel", "settingsbrainpanel"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_bodypanel", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "body", cmd.gen("gui_togglepanel", "settingsbodypanel"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_speciesview", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "species", cmd.gen("gui_togglepanel", "speciesview"), 0, 0, 0 );

	// init critter selection buttons
	c_width += bspacing + bwidth;
	bheight = 28;
	bwidth = 28;
	c_height = bspacing;
	unsigned int tok = 0;
	stringstream s;
	s <<  "hud_cv1";
	for ( unsigned int i=0; i < 20; i++ )
	{
		s << i;
		cbuttons.push_back( addWidgetButton( s.str(), Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "", Vector2i(16, 13), cmd.gen("cs_select", i), 0, 0, 0 ) );
		s << "2";
		static_cast<Button*>(cbuttons[i])->genEvent(3, s.str(), cmd.gen("cs_unregister", i), 0, 0, 0);
		cbuttons[i]->swap();

		if ( ++tok == 2 )
		{
			tok = 0;
			c_width += bspacing + bwidth;
			c_height = bspacing;
		}
		else
			c_height += bspacing + bheight;
	}

	bwidth = 90;
	bheight = 18;

	c_height = bspacing;
	addWidgetButton( "hud__cs_selectall", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "select all", cmd.gen("cs_selectall"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud__cs_clear", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "clear", cmd.gen("cs_clear"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud__cs_kill", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "kill", cmd.gen("cs_killall"), 0, 0, 0 );

	
	c_width += bspacing + bwidth;
	c_height = bspacing;
	addWidgetButton( "hud__cs_duplicateall", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "duplicate", cmd.gen("cs_duplicateall"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_cs_spawnbrainmutantall", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "brain mutants", cmd.gen("cs_spawnbrainmutantall"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "cs_spawnbodymutantall", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "body mutants", cmd.gen("cs_spawnbodymutantall"), 0, 0, 0 );

	c_width += bspacing + bwidth;
	c_height = bspacing;
	addWidgetButton( "cs_spawnbrainbodymutantall", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "brain+body m", cmd.gen("cs_spawnbrainbodymutantall"), 0, 0, 0 );

	c_height += bspacing + bheight;
// 	addWidgetButton( "cs_feed", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "feed", cmd.gen("cs_spawnbodymutantall"), 0, 0, 0 );
}

void Hud::draw()
{
	if (active)
	{
		position.y = *settings->winHeight - v_height;
		updateAbsPosition();

		drawBackground();
		drawBorders();
		drawChildren();

		// activate the proper buttons before drawing children
		for (unsigned int i = 0; i < cbuttons.size(); i++ )
			if ( i < critterselection->clist.size() )
				cbuttons[i]->active = true;
			else
				cbuttons[i]->active = false;

		unsigned int bwidth = 28;
		unsigned int bheight = 28;
		for (unsigned int i=0; i < critterselection->clist.size() && i < 20; i++ )
		{
			glViewport(cbuttons[i]->absPosition. x+1, *settings->winHeight-bheight-(cbuttons[i]->absPosition.y-1), bwidth-1, bheight-1);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glFrustum( -0.05f, 0.05f,-0.05f,0.05f, 0.1f, 10000.0f);
			critterselection->clist[i]->body.mouths[0]->ghostObject->getWorldTransform().inverse().getOpenGLMatrix(viewposition);
			glMultMatrixf(viewposition);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			world->drawWithinCritterSight(critterselection->clist[i]);
		}

		world->camera.place();

		// switch back to 2d 
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, *settings->winWidth, *settings->winHeight, 0, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	}
}

void Hud::drawBorders()
{
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
		glVertex2f(absPosition.x,         absPosition.y+v_height);
		glVertex2f(absPosition.x,         absPosition.y);

		glVertex2f(absPosition.x,         absPosition.y);
		glVertex2f(absPosition.x+v_width, absPosition.y);

		glVertex2f(absPosition.x+v_width, absPosition.y);
		glVertex2f(absPosition.x+v_width, absPosition.y+v_height);

		glVertex2f(absPosition.x+v_width, absPosition.y+v_height);
		glVertex2f(absPosition.x,         absPosition.y+v_height);
	glEnd();
}

Hud::~Hud()
{
}
