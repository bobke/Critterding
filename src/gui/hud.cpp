#include "hud.h"

Hud::Hud()
{
	active = true;

	v_height = 62;
	v_width = 800;
	position.x = 0;
	position.y = *settings->winHeight - v_height;

	critterselection = Critterselection::Instance();

	unsigned int bwidth = 50;
	unsigned int bheight = 18;
	unsigned int bspacing = 2;
	
	unsigned int c_width = bspacing;
	unsigned int c_height = bspacing;
	addWidgetButton( "hud_exit", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "exit", Vector2i(16, 13), cmd.gen("gui_togglepanel", "exitpanel"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_graph", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "graph", Vector2i(10, 13), cmd.gen("gui_togglepanel", "statsgraph"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_stats", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "stats", Vector2i(13, 13), cmd.gen("gui_togglepanel", "infostats"), 0, 0, 0 );

	c_width += bspacing + bwidth;
	c_height = bspacing;
	addWidgetButton( "hud_events", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "events", Vector2i(8, 13), cmd.gen("gui_togglepanel", "textverbosemessage"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_settings1", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "settings1", Vector2i(1, 13), cmd.gen("gui_togglepanel", "settingspanel"), 0, 0, 0 );

	c_height += bspacing + bheight;
	addWidgetButton( "hud_settings2", Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "settings2", Vector2i(1, 13), cmd.gen("gui_togglepanel", "settingsbrainpanel"), 0, 0, 0 );

	// init critter selection buttons
	c_width += bspacing + bwidth;
	bheight = 28;
	bwidth = 28;
	c_height = bspacing;
	unsigned int tok = 0;
	string s = "hud_cv1";
	for ( unsigned int i=0; i < 20; i++ )
	{
		s.append("1");
		cbuttons.push_back( addWidgetButton( s, Vector2i(c_width, c_height), Vector2i(bwidth, bheight), "", Vector2i(16, 13), cmd.gen("cs_unregister", i), 0, 0, 0 ) );
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
}

void Hud::draw()
{
	if (active)
	{
		position.y = *settings->winHeight - v_height;
		updateAbsPositionReal();

		drawBackground();
		drawBorders();

		// activate the proper buttons before drawing children
		for (unsigned int i = 0; i < cbuttons.size(); i++ )
			if ( i < critterselection->clist.size() )
				cbuttons[i]->active = true;
			else
				cbuttons[i]->active = false;

		drawChildren();

		btScalar position[16];
		unsigned int bwidth = 28;
		unsigned int bheight = 28;
		float nheight = 0.05f * ((float)(*settings->winHeight) / *settings->winWidth);

 		glEnable(GL_CULL_FACE);
		
		for (unsigned int i=0; i < critterselection->clist.size() && i < 20; i++ )
		{
// 			glViewport(c_width+1,c_height+1,bwidth-1,bheight-1);

			glViewport(cbuttons[i]->absPosition. x+1, *settings->winHeight-bheight-(cbuttons[i]->absPosition.y-1), bwidth-1, bheight-1);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glFrustum( -0.05f, 0.05f,-nheight,nheight, 0.1f, 10000.0f);
			critterselection->clist[i]->body.mouths[0]->ghostObject->getWorldTransform().inverse().getOpenGLMatrix(position);
			glMultMatrixf(position);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			world->drawWithinCritterSight(critterselection->clist[i]);
		}

		world->camera.place();

// 		glDisable(GL_DEPTH_TEST);
// 		glDisable (GL_LIGHTING);
// 		glDisable(GL_LIGHT0);
// 		glDisable(GL_COLOR_MATERIAL);
// // 		glDisable(GL_DITHER);
 		glDisable(GL_CULL_FACE);

		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, *settings->winWidth, *settings->winHeight, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

void Hud::updateAbsPosition()
{
}

void Hud::updateAbsPositionReal()
{
	absPosition.x = position.x;
	absPosition.y = position.y;
	if ( parent )
	{
		absPosition.x += parent->absPosition.x;
		absPosition.y += parent->absPosition.y;
	}

	// adjust children aswell
	for( childit = children.begin(); childit != children.end(); childit++ )
		childit->second->updateAbsPosition();
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
