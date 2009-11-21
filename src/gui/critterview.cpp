#include "critterview.h"

Critterview::Critterview()
{
	critterselection = Critterselection::Instance();
	
	active = false;
	isMovable = true;

	v_width = 200;
	v_height = 200;
	
	position.x = 10;
	position.y = 50;

	// text widgets
	addWidgetText( "cv_cid", 10, 15, "Critter" );
// 	Widget* cid = addWidgetText( "cv_cid_c", 10, 15, "" );
	
	// view widget
	viewbutton = addWidgetButton( "cv_view", Vector2i(10, 30), Vector2i(50, 50), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
}

void Critterview::draw()
{
	if ( critterselection->selectedCritter == 0 )
		active = false;
	else
		active = true;

	if (active)
	{
		drawBackground();
		drawBorders();

			glViewport(viewbutton->absPosition. x, *settings->winHeight-50-viewbutton->absPosition.y, 50, 50);
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
		
		drawChildren();

		textprinter->print( absPosition.x+10+100, absPosition.y+15, critterselection->selectedCritter->critterID );

	}
	
}

Critterview::~Critterview()
{
}
