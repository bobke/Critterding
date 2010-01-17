#include "critterview.h"

Critterview::Critterview()
{
	critterselection = Critterselection::Instance();
	
	active = false;
	isMovable = true;

	v_width = 351;
	v_height = 470;
	
	position.x = 10;
	position.y = 50;

	currentCritter = 0;

	// text widgets
	addWidgetText( "cv_cid", 10, 15, "Critter" );
// 	Widget* cid = addWidgetText( "cv_cid_c", 10, 15, "" );
// 	addWidgetText( "cv_age", 20, 30, "Age" );


	// view widgets
	viewbutton = addWidgetButton( "cv_view", Vector2i(10, 30), Vector2i(50, 50), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
	bviewbutton = addWidgetButton( "cv_bview", Vector2i(10, 90), Vector2i(v_width-20, v_height-100), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
	children["cv_bview"]->isTransparant = false;

	addWidgetButton( "cv_close", Vector2i(v_width-25, 10), Vector2i(15, 15), "x", cmd.gen("gui_togglepanel", "critterview"), 0, 0, 0 );
}

void Critterview::draw()
{
	int v_radius = 3;
	int v_diam = 2*v_radius;
	int spacing = 3;
	int column = 0;
	int row = 0;
	int rowlength = 37;

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
		{
			currentCritter = critterselection->selectedCritter;

			sensors.clear();
			for ( unsigned int i=0; i < currentCritter->brain.numberOfInputs; i++ )
			{
				sensor s;
				s.sPointer = &currentCritter->brain.Inputs[i];
				int woffset = v_radius+((spacing+v_diam)*column);
				int hoffset = v_radius+((spacing+v_diam)*row);
				s.position = Vector2f(woffset, hoffset);
				sensors.push_back(s);

				if ( ++column == rowlength ) { column = 0; row++; }
			}

			row = (currentCritter->brain.numberOfInputs/rowlength) + 1;
			neurons.clear();
			for ( unsigned int i=0; i < currentCritter->brain.totalNeurons; i++ )
			{
				neuron n;
				n.nPointer = &currentCritter->brain.Neurons[i];
				int woffset = v_radius+((spacing+v_diam)*column);
				int hoffset = v_radius+((spacing+v_diam)*row);
				n.position = Vector2f(woffset, hoffset);
				neurons.push_back(n);

				if ( ++column == rowlength ) { column = 0; row++; }
			}
		}

		drawBackground();
		drawBorders();
		// draw the rest
		drawChildren();
		textprinter->print( bviewbutton->absPosition.x+100, absPosition.y+15, critterselection->selectedCritter->critterID );


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
		
		// drift
			// neuron vs neuron
			for ( unsigned int i=0; i < neurons.size()-1; i++ )
				for ( unsigned int j=i+1; j < neurons.size(); j++ )
				{
					// how many connections do they have underling
					unsigned int nrlinks = 0;
					for ( unsigned int k=0; k < currentCritter->brain.ArchNeurons[i].ArchSynapses.size(); k++ )
					{
						ArchSynapse* as = &currentCritter->brain.ArchNeurons[i].ArchSynapses[k];
						if ( !as->isSensorNeuron && as->neuronID == j )
							nrlinks++;
					}
					for ( unsigned int k=0; k < currentCritter->brain.ArchNeurons[j].ArchSynapses.size(); k++ )
					{
						ArchSynapse* as = &currentCritter->brain.ArchNeurons[j].ArchSynapses[k];
						if ( !as->isSensorNeuron && as->neuronID == i )
							nrlinks++;
					}
					float xD=neurons[j].position.x - neurons[i].position.x;
					float yD=neurons[j].position.y - neurons[i].position.y;
					float dist = sqrt((xD*xD)+(yD*yD));
					float oneoverdistancesquared = 1.0f/(dist*dist);
					if ( oneoverdistancesquared > 1000.0f )
						oneoverdistancesquared = 1000.0f;
					if ( nrlinks > 0 )
					{
// 						if ( dist > 3 )
// 						{
						neurons[i].position.x += (xD / 5000.0f) * dist * nrlinks;
						neurons[i].position.y += (yD / 5000.0f) * dist * nrlinks;

						neurons[j].position.x -= (xD / 5000.0f) * dist * nrlinks;
						neurons[j].position.y -= (yD / 5000.0f) * dist * nrlinks;
// 						}
					}
					else
					{
/*							neurons[i].position.x -= (xD / 1.0f) * oneoverdistancesquared;
						neurons[i].position.y -= (yD / 1.0f) * oneoverdistancesquared;

						neurons[j].position.x += (xD / 1.0f) * oneoverdistancesquared;
						neurons[j].position.y += (yD / 1.0f) * oneoverdistancesquared;*/
					}
					// general antigravity
					neurons[i].position.x -= (xD * 10.0f) * oneoverdistancesquared;
					neurons[i].position.y -= (yD * 10.0f) * oneoverdistancesquared;

					neurons[j].position.x += (xD * 10.0f) * oneoverdistancesquared;
					neurons[j].position.y += (yD * 10.0f) * oneoverdistancesquared;

					//distance=sqrt(xD*xD+yD*yD);
					float miny = v_radius+((spacing+v_diam) * ((sensors.size()/rowlength)+1) );
					if ( neurons[i].position.x+v_radius > *bviewbutton->v_widthP ) neurons[i].position.x = *bviewbutton->v_widthP-v_radius;
					if ( neurons[i].position.x < v_radius ) neurons[i].position.x = v_radius;
					if ( neurons[i].position.y+v_radius > *bviewbutton->v_heightP ) neurons[i].position.y = *bviewbutton->v_heightP-v_radius;
					if ( neurons[i].position.y < miny ) neurons[i].position.y = miny;

					if ( neurons[j].position.x+v_radius > *bviewbutton->v_widthP ) neurons[j].position.x = *bviewbutton->v_widthP-v_radius;
					if ( neurons[j].position.x < v_radius ) neurons[j].position.x = v_radius;
					if ( neurons[j].position.y+v_radius > *bviewbutton->v_heightP ) neurons[j].position.y = *bviewbutton->v_heightP-v_radius;
					if ( neurons[j].position.y < miny ) neurons[j].position.y = miny;
				}
		
			// neuron vs sensor
			for ( unsigned int i=0; i < neurons.size(); i++ )
				for ( unsigned int j=0; j < sensors.size(); j++ )
				{
					// how many connections do they have underling
					unsigned int nrlinks = 0;
					for ( unsigned int k=0; k < currentCritter->brain.ArchNeurons[i].ArchSynapses.size(); k++ )
					{
						ArchSynapse* as = &currentCritter->brain.ArchNeurons[i].ArchSynapses[k];
						if ( as->isSensorNeuron && as->realneuronID == j )
							nrlinks++;
					}
					float xD=sensors[j].position.x - neurons[i].position.x;
					float yD=sensors[j].position.y - neurons[i].position.y;
					float dist = sqrt((xD*xD)+(yD*yD));
					float oneoverdistancesquared = 1.0f/(dist*dist*dist);
					if ( oneoverdistancesquared > 1.0f )
						oneoverdistancesquared = 1.0f;
					if ( nrlinks > 0 )
					{
						neurons[i].position.x += (xD / 1000.0f) * dist * nrlinks;
						neurons[i].position.y += (yD / 1000.0f) * dist * nrlinks;
					}
					// general antigravity
					neurons[i].position.x -= xD * oneoverdistancesquared * 1000;
					neurons[i].position.y -= yD * oneoverdistancesquared * 1000;

					//distance=sqrt(xD*xD+yD*yD);
					float miny = v_radius+((spacing+v_diam) * ((sensors.size()/rowlength)+1) );
					if ( neurons[i].position.x+v_radius > *bviewbutton->v_widthP ) neurons[i].position.x = *bviewbutton->v_widthP-v_radius;
					if ( neurons[i].position.x < v_radius ) neurons[i].position.x = v_radius;
					if ( neurons[i].position.y+v_radius > *bviewbutton->v_heightP ) neurons[i].position.y = *bviewbutton->v_heightP-v_radius;
					if ( neurons[i].position.y < miny ) neurons[i].position.y = miny;
				}

		// draw brain
			// connections
			glBegin(GL_LINES);
// 			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			for ( unsigned int i=0; i < neurons.size(); i++ )
			{
// 				if ( neurons[i].nPointer->output )
// 				{
// 					if ( neurons[i].nPointer->isMotor )
// 						glColor4f(0.0f, 0.0f, 0.5f, 1.0f);
// 					else if ( neurons[i].nPointer->isInhibitory )
// 						glColor4f(0.5f, 0.0f, 0.0f, 1.0f);
// 					else
// 						glColor4f(0.0f, 0.5f, 0.0f, 1.0f);
// 				}
// 				else
// 				{
// 					if ( neurons[i].nPointer->isMotor )
// 						glColor4f(0.0f, 0.0f, dimmed, 1.0f);
// 					else if ( neurons[i].nPointer->isInhibitory )
// 						glColor4f(dimmed, 0.0f, 0.0f, 1.0f);
// 					else
// 						glColor4f(0.0f, dimmed, 0.0f, 1.0f);
// 				}

					for ( unsigned int j=0; j < currentCritter->brain.ArchNeurons[i].ArchSynapses.size(); j++ )
					{
						ArchSynapse* as = &currentCritter->brain.ArchNeurons[i].ArchSynapses[j];
						if ( !as->isSensorNeuron && currentCritter->brain.Neurons[as->neuronID].output || as->isSensorNeuron && currentCritter->brain.Inputs[as->realneuronID].output )
						{
							if ( as->isSensorNeuron )
								glColor4f(0.0f, 0.4f, 0.0f, 1.0f);
							else if ( !neurons[as->neuronID].nPointer->isInhibitory )
								glColor4f(0.0f, 0.4f, 0.0f, 1.0f);
							else
								glColor4f(0.4f, 0.0f, 0.0f, 1.0f);

							glVertex2f(neurons[i].position.x+bviewbutton->absPosition.x,         neurons[i].position.y+bviewbutton->absPosition.y);
							if ( as->isSensorNeuron )
							{
								glVertex2f(bviewbutton->absPosition.x+sensors[as->realneuronID].position.x,         bviewbutton->absPosition.y+sensors[as->realneuronID].position.y);
							}
							else
							{
								glVertex2f(bviewbutton->absPosition.x+neurons[as->neuronID].position.x,         bviewbutton->absPosition.y+neurons[as->neuronID].position.y);
							}
						}
					}
// 				}
			}
			glEnd();

			glBegin(GL_QUADS);

			float dimmed = 0.3f;
			// inputs
			for ( unsigned int i=0; i < sensors.size(); i++ )
			{
				if ( sensors[i].sPointer->output )
					glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				else
					glColor4f(0.0f, dimmed, 0.0f, 1.0f);

// 				glScaled(sensors[i].sPointer->output, sensors[i].sPointer->output, sensors[i].sPointer->output);
// 				cerr << sensors[i].sPointer->output <<  endl;

// 				float nv_radius = sensors[i].sPointer->output * v_radius;
				float nv_radius = v_radius;

				glVertex2f(sensors[i].position.x+bviewbutton->absPosition.x-nv_radius, sensors[i].position.y+bviewbutton->absPosition.y+nv_radius);
				glVertex2f(sensors[i].position.x+bviewbutton->absPosition.x-nv_radius, sensors[i].position.y+bviewbutton->absPosition.y-nv_radius);
				glVertex2f(sensors[i].position.x+bviewbutton->absPosition.x+nv_radius, sensors[i].position.y+bviewbutton->absPosition.y-nv_radius);
				glVertex2f(sensors[i].position.x+bviewbutton->absPosition.x+nv_radius, sensors[i].position.y+bviewbutton->absPosition.y+nv_radius);
			}

			// neurons
			for ( unsigned int i=0; i < neurons.size(); i++ )
			{
// 				if ( neurons[i].nPointer->output )
// 				{
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
// 						glColor4f(0.0f, 0.0f, dimmed, 1.0f);
// 					else if ( neurons[i].nPointer->isInhibitory )
// 						glColor4f(dimmed, 0.0f, 0.0f, 1.0f);
// 					else
// 						glColor4f(0.0f, dimmed, 0.0f, 1.0f);
// 				}
				float nv_radius = (neurons[i].nPointer->potential * v_diam) / settings->getCVar("brain_maxfiringthreshold");
				glVertex2f(neurons[i].position.x+bviewbutton->absPosition.x-nv_radius, neurons[i].position.y+bviewbutton->absPosition.y+nv_radius);
				glVertex2f(neurons[i].position.x+bviewbutton->absPosition.x-nv_radius, neurons[i].position.y+bviewbutton->absPosition.y-nv_radius);
				glVertex2f(neurons[i].position.x+bviewbutton->absPosition.x+nv_radius, neurons[i].position.y+bviewbutton->absPosition.y-nv_radius);
				glVertex2f(neurons[i].position.x+bviewbutton->absPosition.x+nv_radius, neurons[i].position.y+bviewbutton->absPosition.y+nv_radius);
			}

	// 		// outputs
	// 		column = 0;
	// 		for ( unsigned int i=0; i < currentCritter->brain.numberOfOutputs; i++ )
	// 		{
	// 			if ( *currentCritter->brain.Outputs[i].output )
	// 				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	// 			else
	// 				glColor4f(0.0f, 0.0f, dimmed, 1.0f);
	// 
	// 			int woffset = v_radius+((spacing+v_diam)*column);
	// 			int hoffset = 250-v_height;
	// 			glVertex2f(bviewbutton->absPosition.x+woffset-v_radius, bviewbutton->absPosition.y+hoffset+v_radius);
	// 			glVertex2f(bviewbutton->absPosition.x+woffset-v_radius, bviewbutton->absPosition.y+hoffset-v_radius);
	// 			glVertex2f(bviewbutton->absPosition.x+woffset+v_radius, bviewbutton->absPosition.y+hoffset-v_radius);
	// 			glVertex2f(bviewbutton->absPosition.x+woffset+v_radius, bviewbutton->absPosition.y+hoffset+v_radius);
	// 			
	// 			if ( ++column == rowlength ) { column = 0; row++; }
	// 		}

			glEnd();

	}
	
}

Critterview::~Critterview()
{
}
