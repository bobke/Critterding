#include "critterview.h"

Critterview::Critterview()
{
	critterselection = Critterselection::Instance();
	
	active = false;
	isMovable = true;

	rowlength = 37;
	v_radius = 2;
	v_diam = 2*v_radius;
	spacing = 3;

	int brainview_width = 20 + ((v_diam+spacing) * settings->getCVar("critter_retinasize") * 4);
	if ( brainview_width < 350 )
		brainview_width = 350;

	int brainview_height = 20 + ((v_diam+spacing) * 50);
	if ( brainview_height < 245 )
		brainview_height = 245;

	v_width = 20 + brainview_width;
	v_height = 100 + brainview_height;
	
	position.x = 10;
	position.y = 50;

	currentCritter = 0;

	// text widgets
	v_spacer = 14; v_space = 0;
	v_space += v_spacer; addWidgetText( "cv_cid", 10, v_space, "Critter" );
	v_space += v_spacer; addWidgetText( "cv_age", 10, v_space, "Age" );
		addWidgetText( "cv_age_/", 200, v_space, "/" );
		addWidgetText( "cv_age_max", 210, v_space, settings->getCVarPtr("critter_maxlifetime") );

	v_space += v_spacer; addWidgetText( "cv_energy", 10, v_space, "Energy" );
		addWidgetText( "cv_energy_/", 200, v_space, "/" );
		addWidgetText( "cv_energy_max", 210, v_space, settings->getCVarPtr("critter_maxenergy") );

	v_space += v_spacer; addWidgetText( "cv_neurons", 10, v_space, "Neurons" );
	v_space += v_spacer; addWidgetText( "cv_synapses", 10, v_space, "Synapses" );
	
	// view widgets
	viewbutton = addWidgetButton( "cv_view", Vector2i(0+v_width-60, 30), Vector2i(50, 50), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
	brainview = addWidgetButton( "cv_bview", Vector2i(10, 90), Vector2i(brainview_width, brainview_height), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
	children["cv_bview"]->isTransparant = false;

	addWidgetButton( "cv_close", Vector2i(v_width-25, 10), Vector2i(15, 15), "x", cmd.gen("gui_togglepanel", "critterview"), 0, 0, 0 );
}

void Critterview::draw()
{
	column = 0;
	row = 0;

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
			int sverticalpos = 0;
			int constraintcount = 0;

			for ( unsigned int i=0; i < currentCritter->brain.numberOfInputs; i++ )
			{
				if ( currentCritter->brain.Inputs[i].id == 10000 )
				{
					sensor s; s.sPointer = &currentCritter->brain.Inputs[i];
					s.position = Vector2f(brainview->position.x, 10);
					sensors.push_back(s);
				}
				else if ( currentCritter->brain.Inputs[i].id == 10001 )
				{
				sverticalpos = 2;
					sensor s; s.sPointer = &currentCritter->brain.Inputs[i];
					s.position = Vector2f(brainview->position.x, 10+(spacing+v_diam)*sverticalpos);
					sensors.push_back(s);
				}
				else if ( currentCritter->brain.Inputs[i].id == 20000 )
				{
				sverticalpos = 4;
					sensor s; s.sPointer = &currentCritter->brain.Inputs[i];
					s.position = Vector2f(brainview->position.x, 10+(spacing+v_diam)*sverticalpos);
					sensors.push_back(s);
				}
				else if ( currentCritter->brain.Inputs[i].id >= 30000 && currentCritter->brain.Inputs[i].id < 40000 )
				{
				sverticalpos = 6;
					sensor s; s.sPointer = &currentCritter->brain.Inputs[i];
					s.position = Vector2f(brainview->position.x, 10+(spacing+v_diam)*sverticalpos +((spacing+v_diam)*(currentCritter->brain.Inputs[i].id-30000)));
					sensors.push_back(s);
				}
				else if ( currentCritter->brain.Inputs[i].id >= 40000 && currentCritter->brain.Inputs[i].id < 50000 )
				{
				sverticalpos = 17;
					sensor s; s.sPointer = &currentCritter->brain.Inputs[i];
					s.position = Vector2f(brainview->position.x, 10+(spacing+v_diam)*sverticalpos +((spacing+v_diam)*(currentCritter->brain.Inputs[i].id-40000)));
					sensors.push_back(s);
				}
				else if ( currentCritter->brain.Inputs[i].id < 10000 )
				{
				sverticalpos = 28;
					sensor s; s.sPointer = &currentCritter->brain.Inputs[i];
					s.position = Vector2f(brainview->position.x, 10+(spacing+v_diam)*sverticalpos +((spacing+v_diam)*(constraintcount)));
					sensors.push_back(s);
					constraintcount++;
				}
				else if ( currentCritter->brain.Inputs[i].id >= 50000 && currentCritter->brain.Inputs[i].id < 60000 )
				{
					int vinput = currentCritter->brain.Inputs[i].id-50000;
					int vcolmax = currentCritter->retinasize * currentCritter->components;
					int row = vinput / vcolmax;
					int col = vinput - (row * vcolmax);
					row = currentCritter->retinasize - row - 1;

					sensor s; s.sPointer = &currentCritter->brain.Inputs[i];
					s.position = Vector2f(brainview->position.x+((spacing+v_diam)*col)+10, 10+((spacing+v_diam)*row));
					sensors.push_back(s);
				}
				else
				{
					cerr << "critterview: inputs don't add up" << endl;
					exit(0);
				}
			}

// 			for ( unsigned int i=0; i < currentCritter->brain.numberOfInputs; i++ )
// 			{
// 				sensor s;
// 				s.sPointer = &currentCritter->brain.Inputs[i];
// 				int woffset, hoffset;
// 				if ( s.sPointer->id == 10000 )
// 					woffset = 100; hoffset = 50;
// 				else
// 				{
// // 					woffset = v_radius+((spacing+v_diam)*column);
// // 					hoffset = v_radius+((spacing+v_diam)*row);
// 					woffset = 20; hoffset = 20;
// 				}
// 				s.position = Vector2f(woffset, hoffset);
// 				sensors.push_back(s);
// 
// 				if ( ++column == rowlength ) { column = 0; row++; }
// 			}

			row = (currentCritter->brain.numberOfInputs/rowlength) + 1;
			neurons.clear();
			for ( unsigned int i=0; i < currentCritter->brain.totalNeurons; i++ )
			{
				neuron n;
				n.nPointer = &currentCritter->brain.Neurons[i];
				int woffset = v_radius+((spacing+v_diam)*column);
				int hoffset = 30+v_radius+((spacing+v_diam)*row*3);
				n.position = Vector2f(woffset, hoffset);
				neurons.push_back(n);

				if ( ++column == rowlength ) { column = 0; row++; }
			}
		}

		drawBackground();
		drawBorders();
		// draw the rest
		drawChildren();
		
		// draw values of critter
		v_space = 0;
		v_space += v_spacer; textprinter->print( brainview->absPosition.x+100, absPosition.y+v_space, critterselection->selectedCritter->critterID );
 		v_space += v_spacer; textprinter->print( brainview->absPosition.x+100, absPosition.y+v_space, critterselection->selectedCritter->totalFrames );
 		v_space += v_spacer; textprinter->print( brainview->absPosition.x+100, absPosition.y+v_space, "%1.1f", critterselection->selectedCritter->energyLevel );
 		v_space += v_spacer; textprinter->print( brainview->absPosition.x+100, absPosition.y+v_space, critterselection->selectedCritter->brain.totalNeurons );
 		v_space += v_spacer; textprinter->print( brainview->absPosition.x+100, absPosition.y+v_space, critterselection->selectedCritter->brain.totalSynapses );
			textprinter->print( brainview->absPosition.x+200, absPosition.y+v_space, "%5.2f avg", (float)critterselection->selectedCritter->brain.totalSynapses / critterselection->selectedCritter->brain.totalNeurons );


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
					if ( neurons[i].position.x+v_radius > *brainview->v_widthP ) neurons[i].position.x = *brainview->v_widthP-v_radius;
					if ( neurons[i].position.x < v_radius ) neurons[i].position.x = v_radius;
					if ( neurons[i].position.y+v_radius > *brainview->v_heightP ) neurons[i].position.y = *brainview->v_heightP-v_radius;
					if ( neurons[i].position.y < miny ) neurons[i].position.y = miny;

					if ( neurons[j].position.x+v_radius > *brainview->v_widthP ) neurons[j].position.x = *brainview->v_widthP-v_radius;
					if ( neurons[j].position.x < v_radius ) neurons[j].position.x = v_radius;
					if ( neurons[j].position.y+v_radius > *brainview->v_heightP ) neurons[j].position.y = *brainview->v_heightP-v_radius;
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
					neurons[i].position.x -= xD * oneoverdistancesquared * 5000;
					neurons[i].position.y -= yD * oneoverdistancesquared * 5000;

					//distance=sqrt(xD*xD+yD*yD);
					float miny = v_radius+((spacing+v_diam) * ((sensors.size()/rowlength)+1) );
					if ( neurons[i].position.x+v_radius > *brainview->v_widthP ) neurons[i].position.x = *brainview->v_widthP-v_radius;
					if ( neurons[i].position.x < v_radius ) neurons[i].position.x = v_radius;
					if ( neurons[i].position.y+v_radius > *brainview->v_heightP ) neurons[i].position.y = *brainview->v_heightP-v_radius;
					if ( neurons[i].position.y < miny ) neurons[i].position.y = miny;
				}

		// draw brain
			// connections
			glBegin(GL_LINES);
			float dimmed = 0.20f;
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
								glColor4f(0.0f, dimmed, 0.0f, 1.0f);
							else if ( !neurons[as->neuronID].nPointer->isInhibitory )
								glColor4f(0.0f, dimmed, 0.0f, 1.0f);
							else
								glColor4f(dimmed, 0.0f, 0.0f, 1.0f);

							glVertex2f(neurons[i].position.x+brainview->absPosition.x,         neurons[i].position.y+brainview->absPosition.y);
							if ( as->isSensorNeuron )
							{
								glVertex2f(brainview->absPosition.x+sensors[as->realneuronID].position.x,         brainview->absPosition.y+sensors[as->realneuronID].position.y);
							}
							else
							{
								glVertex2f(brainview->absPosition.x+neurons[as->neuronID].position.x,         brainview->absPosition.y+neurons[as->neuronID].position.y);
							}
						}
					}
// 				}
			}
			glEnd();

			glBegin(GL_QUADS);

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

				glVertex2f(sensors[i].position.x+brainview->absPosition.x-nv_radius, sensors[i].position.y+brainview->absPosition.y+nv_radius);
				glVertex2f(sensors[i].position.x+brainview->absPosition.x-nv_radius, sensors[i].position.y+brainview->absPosition.y-nv_radius);
				glVertex2f(sensors[i].position.x+brainview->absPosition.x+nv_radius, sensors[i].position.y+brainview->absPosition.y-nv_radius);
				glVertex2f(sensors[i].position.x+brainview->absPosition.x+nv_radius, sensors[i].position.y+brainview->absPosition.y+nv_radius);
			}

			// neurons
			for ( unsigned int i=0; i < neurons.size(); i++ )
			{
// 				if ( neurons[i].nPointer->output )
// 				{
					if ( neurons[i].nPointer->isMotor )
						glColor4f(0.3f, 0.3f, 1.0f, 1.0f);
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
				glVertex2f(neurons[i].position.x+brainview->absPosition.x-nv_radius, neurons[i].position.y+brainview->absPosition.y+nv_radius);
				glVertex2f(neurons[i].position.x+brainview->absPosition.x-nv_radius, neurons[i].position.y+brainview->absPosition.y-nv_radius);
				glVertex2f(neurons[i].position.x+brainview->absPosition.x+nv_radius, neurons[i].position.y+brainview->absPosition.y-nv_radius);
				glVertex2f(neurons[i].position.x+brainview->absPosition.x+nv_radius, neurons[i].position.y+brainview->absPosition.y+nv_radius);
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
	// 			glVertex2f(brainview->absPosition.x+woffset-v_radius, brainview->absPosition.y+hoffset+v_radius);
	// 			glVertex2f(brainview->absPosition.x+woffset-v_radius, brainview->absPosition.y+hoffset-v_radius);
	// 			glVertex2f(brainview->absPosition.x+woffset+v_radius, brainview->absPosition.y+hoffset-v_radius);
	// 			glVertex2f(brainview->absPosition.x+woffset+v_radius, brainview->absPosition.y+hoffset+v_radius);
	// 			
	// 			if ( ++column == rowlength ) { column = 0; row++; }
	// 		}

			glEnd();

	}
	
}

Critterview::~Critterview()
{
}
