#include "critterview.h"

Critterview::Critterview()
{
	critterselection = Critterselection::Instance();
	
	active = false;
	isMovable = true;

	v_width = 240;
	v_height = 350;
	
	position.x = 10;
	position.y = 50;

	currentCritter = 0;

	// text widgets
	addWidgetText( "cv_cid", 10, 15, "Critter" );
// 	Widget* cid = addWidgetText( "cv_cid_c", 10, 15, "" );
	
	// view widgets
	viewbutton = addWidgetButton( "cv_view", Vector2i(10, 30), Vector2i(50, 50), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
	bviewbutton = addWidgetButton( "cv_bview", Vector2i(10, 90), Vector2i(220, 250), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
}

void Critterview::draw()
{
	int v_radius = 4;
	int v_diam = 2*v_radius;
	int spacing = 3;
	int column = 0;
	int row = 0;

	if ( critterselection->selectedCritter == 0 )
		active = false;
	else
	{
		active = true;
		if ( critterselection->selectedCritter != currentCritter )
		{
			currentCritter = critterselection->selectedCritter;

			sensors.clear();
			for ( unsigned int i=0; i < currentCritter->brain.numberOfInputs; i++ )
			{
				sensor s;
				s.sPointer = &currentCritter->brain.Inputs[i];
				int woffset = v_radius+((spacing+v_diam)*column);
				int hoffset = v_radius+((spacing+v_diam)*row);
				s.position = Vector2i(woffset, hoffset);
				sensors.push_back(s);

				if ( ++column == 20 ) { column = 0; row++; }
			}

			row = (currentCritter->brain.numberOfInputs/20) + 1;
			neurons.clear();
			for ( unsigned int i=0; i < currentCritter->brain.totalNeurons; i++ )
			{
				neuron n;
				n.nPointer = &currentCritter->brain.Neurons[i];
				int woffset = v_radius+((spacing+v_diam)*column);
				int hoffset = v_radius+((spacing+v_diam)*row);
				n.position = Vector2i(woffset, hoffset);
				neurons.push_back(n);

				if ( ++column == 20 ) { column = 0; row++; }
			}
		}
	}

	if (active)
	{
		drawBackground();
		drawBorders();

		// draw gl view
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
		
		// draw brain
			glBegin(GL_QUADS);

			// inputs
			for ( unsigned int i=0; i < sensors.size(); i++ )
			{
				if ( sensors[i].sPointer->output )
					glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				else
					glColor4f(0.0f, 0.2f, 0.0f, 1.0f);

/*				row = (i/20);
				int hoffset = v_radius+((spacing+v_diam) * row );
				int woffset = v_radius+((spacing+v_diam) * (i-(row*20)) );*/
				glVertex2f(bviewbutton->absPosition.x+sensors[i].position.x-v_radius, bviewbutton->absPosition.y+sensors[i].position.y+v_radius);
				glVertex2f(bviewbutton->absPosition.x+sensors[i].position.x-v_radius, bviewbutton->absPosition.y+sensors[i].position.y-v_radius);
				glVertex2f(bviewbutton->absPosition.x+sensors[i].position.x+v_radius, bviewbutton->absPosition.y+sensors[i].position.y-v_radius);
				glVertex2f(bviewbutton->absPosition.x+sensors[i].position.x+v_radius, bviewbutton->absPosition.y+sensors[i].position.y+v_radius);
			}

			// neurons
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
				glVertex2f(bviewbutton->absPosition.x+neurons[i].position.x-v_radius, bviewbutton->absPosition.y+neurons[i].position.y+v_radius);
				glVertex2f(bviewbutton->absPosition.x+neurons[i].position.x-v_radius, bviewbutton->absPosition.y+neurons[i].position.y-v_radius);
				glVertex2f(bviewbutton->absPosition.x+neurons[i].position.x+v_radius, bviewbutton->absPosition.y+neurons[i].position.y-v_radius);
				glVertex2f(bviewbutton->absPosition.x+neurons[i].position.x+v_radius, bviewbutton->absPosition.y+neurons[i].position.y+v_radius);
			}

	// 		// outputs
	// 		column = 0;
	// 		for ( unsigned int i=0; i < currentCritter->brain.numberOfOutputs; i++ )
	// 		{
	// 			if ( *currentCritter->brain.Outputs[i].output )
	// 				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	// 			else
	// 				glColor4f(0.0f, 0.0f, 0.2f, 1.0f);
	// 
	// 			int woffset = v_radius+((spacing+v_diam)*column);
	// 			int hoffset = 250-v_height;
	// 			glVertex2f(bviewbutton->absPosition.x+woffset-v_radius, bviewbutton->absPosition.y+hoffset+v_radius);
	// 			glVertex2f(bviewbutton->absPosition.x+woffset-v_radius, bviewbutton->absPosition.y+hoffset-v_radius);
	// 			glVertex2f(bviewbutton->absPosition.x+woffset+v_radius, bviewbutton->absPosition.y+hoffset-v_radius);
	// 			glVertex2f(bviewbutton->absPosition.x+woffset+v_radius, bviewbutton->absPosition.y+hoffset+v_radius);
	// 			
	// 			if ( ++column == 20 ) { column = 0; row++; }
	// 		}

			glEnd();

			// connections
			glBegin(GL_LINES);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
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
// 				}
// 				else
// 				{
// 					if ( neurons[i].nPointer->isMotor )
// 						glColor4f(0.0f, 0.0f, 0.2f, 1.0f);
// 					else if ( neurons[i].nPointer->isInhibitory )
// 						glColor4f(0.2f, 0.0f, 0.0f, 1.0f);
// 					else
// 						glColor4f(0.0f, 0.2f, 0.0f, 1.0f);
// 				}

				for ( unsigned int j=0; j < currentCritter->brain.ArchNeurons[i].ArchSynapses.size(); j++ )
				{
					ArchSynapse* as = &currentCritter->brain.ArchNeurons[i].ArchSynapses[j];
					glVertex2f(bviewbutton->absPosition.x+neurons[i].position.x,         bviewbutton->absPosition.y+neurons[i].position.y);
					if ( as->isSensorNeuron )
					{
						glVertex2f(bviewbutton->absPosition.x+sensors[currentCritter->brain.findSensorNeuron(as->neuronID)].position.x,         bviewbutton->absPosition.y+sensors[currentCritter->brain.findSensorNeuron(as->neuronID)].position.y);
					}
					else
					{
						glVertex2f(bviewbutton->absPosition.x+neurons[as->neuronID].position.x,         bviewbutton->absPosition.y+neurons[as->neuronID].position.y);
					}
				}
				}

// 				glVertex2f(absPosition.x,         absPosition.y+v_height);
// 				glVertex2f(absPosition.x,         absPosition.y);
			}
			glEnd();

		// draw the rest
			drawChildren();
			textprinter->print( bviewbutton->absPosition.x+100, absPosition.y+15, critterselection->selectedCritter->critterID );
	}
	
}

// int Brainz::Critterview( unsigned int id )
// {
// 	for ( unsigned int i=0; i < currentCritter->brain.numberOfInputs; i++ )
// 		if ( currentCritter->brain.Inputs[i].id == id )
// 			return i;
// // 		cerr << "brain findSensorNeuron error for id: " << id << endl;
// 	return -1;
// }


Critterview::~Critterview()
{
}
