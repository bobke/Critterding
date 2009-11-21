#include "critterview.h"

Critterview::Critterview()
{
	critterselection = Critterselection::Instance();
	
	active = false;
	isMovable = true;

	v_width = 240;
	v_height = 320;
	
	position.x = 10;
	position.y = 50;

	currentCritter = 0;

	// text widgets
	addWidgetText( "cv_cid", 10, 15, "Critter" );
// 	Widget* cid = addWidgetText( "cv_cid_c", 10, 15, "" );
	
	// view widgets
	viewbutton = addWidgetButton( "cv_view", Vector2i(10, 30), Vector2i(50, 50), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
	bviewbutton = addWidgetButton( "cv_bview", Vector2i(10, 90), Vector2i(220, 220), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
}

void Critterview::draw()
{
	if ( critterselection->selectedCritter == 0 )
		active = false;
	else
	{
		active = true;
		if ( critterselection->selectedCritter != currentCritter )
		{
			currentCritter = critterselection->selectedCritter;
			neurons.clear();
			for ( unsigned int i=0; i < currentCritter->brain.totalNeurons; i++ )
			{
				neuron n;
				n.nPointer = &currentCritter->brain.Neurons[i];
				n.position = Vector2i(0, 0);
				neurons.push_back(n);
			}
		}
	}

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
		
		int v_height = 8;
		int v_width = 8;
		int spacing = 3;
		glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
		glBegin(GL_QUADS);
		int column = 0;
		int row = 0;
		for ( unsigned int i=0; i < neurons.size(); i++ )
		{
			if ( neurons[i].nPointer->output )
			{
				if ( neurons[i].nPointer->isMotor )
					glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				else if ( neurons[i].nPointer->isInhibitory )
					glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				else
					glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			}
			else
			{
				if ( neurons[i].nPointer->isMotor )
					glColor4f(0.0f, 0.0f, 0.2f, 1.0f);
				else if ( neurons[i].nPointer->isInhibitory )
					glColor4f(0.2f, 0.0f, 0.0f, 1.0f);
				else
					glColor4f(0.0f, 0.2f, 0.0f, 1.0f);
			}

			int woffset = (spacing+v_width)*column;
			int hoffset = (spacing+v_height)*row;
			glVertex2f(bviewbutton->absPosition.x+woffset,         bviewbutton->absPosition.y+hoffset+v_height);
			glVertex2f(bviewbutton->absPosition.x+woffset,         bviewbutton->absPosition.y+hoffset);
			glVertex2f(bviewbutton->absPosition.x+woffset+v_width, bviewbutton->absPosition.y+hoffset);
			glVertex2f(bviewbutton->absPosition.x+woffset+v_width, bviewbutton->absPosition.y+hoffset+v_height);
			
			if ( ++column == 20 )
			{
				column = 0;
				row++;
			}
		}
		glEnd();

		drawChildren();
		textprinter->print( bviewbutton->absPosition.x+100, absPosition.y+15, critterselection->selectedCritter->critterID );
	}
	
}

Critterview::~Critterview()
{
}
