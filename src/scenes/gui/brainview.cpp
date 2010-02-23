#include <omp.h>
#include "brainview.h"

Brainview::Brainview()
{
	critterselection = Critterselection::Instance();

	brain_maxfiringthreshold = settings->getCVarPtr("brain_maxfiringthreshold");

	active = false;
	isMovable = true;

	rowlength = 37;
	v_radius = 2;
	v_diam = 2*v_radius;
	spacing = 3;

	int brainview_width = 20 + ((v_diam+spacing) * settings->getCVar("critter_retinasize") * 4);
	if ( brainview_width < 400 )
		brainview_width = 400;

	int brainview_height = 20 + ((v_diam+spacing) * 40);
	if ( brainview_height < 400 )
		brainview_height = 400;

	v_width = 20 + brainview_width;
	v_height = 80 + brainview_height;

	int buttons_starty = v_height - brainview_height - 10;
	int brainview_starty = buttons_starty;

	position.x = 10;
	position.y = 50;

	currentCritter = 0;

	// view widgets
// 	viewbutton = addWidgetButton( "bv_view", Vector2i(0+v_width-60, 35), Vector2i(50, 50), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
	brainview = addWidgetButton( "bv_bview", Vector2i(10, brainview_starty), Vector2i(brainview_width, brainview_height), "", Vector2i(0, 0), cmd.gen(""), 0, 0, 0 );
	children["bv_bview"]->isTransparant = false;

	addWidgetButton( "bv_close", Vector2i(v_width-25, 10), Vector2i(15, 15), "x", cmd.gen("gui_togglepanel", "brainview"), 0, 0, 0 );


	settings->registerLocalCVar("attract neurons", 100, 0, 1000000, false, "attract neurons");
	addSettingmutator("attract neurons", 10, 10);

	settings->registerLocalCVar("repel neurons", 100, 0, 1000000, false, "repel neurons");
	addSettingmutator("repel neurons", 10, 36);

	settings->registerLocalCVar("attract neuron inputs", 100, 0, 1000000, false, "attract neuron<>inputs");
	addSettingmutator("attract neuron inputs", 10, 22);

	settings->registerLocalCVar("repel neuron inputs", 100, 0, 1000000, false, "repel neuron<>inputs");
	addSettingmutator("repel neuron inputs", 10, 48);

	attractor1 = settings->getCVarPtr("attract neurons");
	attractor2 = settings->getCVarPtr("attract neuron inputs");
	attractor3 = settings->getCVarPtr("repel neurons");
	attractor4 = settings->getCVarPtr("repel neuron inputs");
}

void Brainview::draw()
{
	column = 0;
	row = 0;

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
					int vcolmax = currentCritter->genotype->bodyArch->retinasize * 4;
					int row = vinput / vcolmax;
					int col = vinput - (row * vcolmax);
					row = currentCritter->genotype->bodyArch->retinasize - row - 1;

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

		// drift

			// neuron vs neuron
			unsigned int i, j, k, nrlinks;
			float xD, yD, dist, oneoverdistance, oneoverdistancesquared;
			ArchSynapse* as;
			
			// reset newpositions
			for ( i=0; i < neurons.size(); i++ )
			{
				neurons[i].newposition.x = 0;
				neurons[i].newposition.y = 0;
			}

// #pragma omp parallel for private(i, j, k, nrlinks, xD, yD, dist, oneoverdistancesquared, miny, as)
			for ( i=0; i < neurons.size()-1; i++ )
				for ( j=i+1; j < neurons.size(); j++ )
				{
					// how many connections do they have underling
					nrlinks = 0;
					for ( k=0; k < currentCritter->genotype->brainzArch->ArchNeurons[i].ArchSynapses.size(); k++ )
					{
						as = &currentCritter->genotype->brainzArch->ArchNeurons[i].ArchSynapses[k];
						if ( !as->isSensorNeuron && as->neuronID == j )
							nrlinks++;
					}
					for ( k=0; k < currentCritter->genotype->brainzArch->ArchNeurons[j].ArchSynapses.size(); k++ )
					{
						as = &currentCritter->genotype->brainzArch->ArchNeurons[j].ArchSynapses[k];
						if ( !as->isSensorNeuron && as->neuronID == i )
							nrlinks++;
					}

					xD=neurons[j].position.x - neurons[i].position.x;
					yD=neurons[j].position.y - neurons[i].position.y;

					dist = sqrt((xD*xD)+(yD*yD));

					oneoverdistance = 1.0f/dist;
					oneoverdistancesquared = oneoverdistance * oneoverdistance;
// 					if ( oneoverdistancesquared < 0.00001f )
// 						oneoverdistancesquared = 0.00001f;
					if ( oneoverdistancesquared > 0.001f )
						oneoverdistancesquared = 0.001f;

					if ( nrlinks > 0 )
					{
						neurons[i].newposition.x += xD * oneoverdistancesquared * *attractor1 * nrlinks / 10.0f;
						neurons[i].newposition.y += yD * oneoverdistancesquared * *attractor1 * nrlinks / 10.0f;
						neurons[j].newposition.x -= xD * oneoverdistancesquared * *attractor1 * nrlinks / 10.0f;
						neurons[j].newposition.y -= yD * oneoverdistancesquared * *attractor1 * nrlinks / 10.0f;
					}
					// general antigravity
					neurons[i].newposition.x -= xD * oneoverdistancesquared * oneoverdistancesquared * *attractor3 * 100;
					neurons[i].newposition.y -= yD * oneoverdistancesquared * oneoverdistancesquared * *attractor3 * 100;
					neurons[j].newposition.x += xD * oneoverdistancesquared * oneoverdistancesquared * *attractor3 * 100;
					neurons[j].newposition.y += yD * oneoverdistancesquared * oneoverdistancesquared * *attractor3 * 100;
				}

			// neuron vs sensor
			for ( unsigned int i=0; i < neurons.size(); i++ )
				for ( unsigned int j=0; j < sensors.size(); j++ )
				{
					// how many connections do they have underling
					unsigned int nrlinks = 0;
					for ( unsigned int k=0; k < currentCritter->genotype->brainzArch->ArchNeurons[i].ArchSynapses.size(); k++ )
					{
						ArchSynapse* as = &currentCritter->genotype->brainzArch->ArchNeurons[i].ArchSynapses[k];
						if ( as->isSensorNeuron && as->realneuronID == j )
							nrlinks++;
					}
					float xD=sensors[j].position.x - neurons[i].position.x;
					float yD=sensors[j].position.y - neurons[i].position.y;
					float dist = sqrt((xD*xD)+(yD*yD));
					float oneoverdistancesquared = 1.0f/(dist*dist*dist);
/*					if ( oneoverdistancesquared > 1.0f )
						oneoverdistancesquared = 1.0f;*/
					if ( oneoverdistancesquared > 0.001f )
						oneoverdistancesquared = 0.001f;
					if ( nrlinks > 0 )
					{
						neurons[i].newposition.x += xD * oneoverdistancesquared * *attractor2 * nrlinks * 10.0f;
						neurons[i].newposition.y += yD * oneoverdistancesquared * *attractor2 * nrlinks * 10.0f;
					}
					// general antigravity
					neurons[i].newposition.x -= xD * oneoverdistancesquared * oneoverdistancesquared * *attractor4 * 100000;
					neurons[i].newposition.y -= yD * oneoverdistancesquared * oneoverdistancesquared * *attractor4 * 100000;
				}

			// apply newpositions & check boundaries
			for ( i=0; i < neurons.size(); i++ )
			{
				neurons[i].position.x += neurons[i].newposition.x;
				neurons[i].position.y += neurons[i].newposition.y;

				float miny = (v_radius*2)+((spacing+v_diam) * ((sensors.size()/rowlength)+1) );
				float leftborder = 20.0f;

				if ( neurons[i].position.x+v_radius > *brainview->v_widthP )
					neurons[i].position.x = *brainview->v_widthP-v_radius;
				if ( neurons[i].position.x < v_radius+leftborder )
					neurons[i].position.x = v_radius+leftborder;
				if ( neurons[i].position.y+v_radius > *brainview->v_heightP )
					neurons[i].position.y = *brainview->v_heightP-v_radius;
				if ( neurons[i].position.y < miny )
					neurons[i].position.y = miny;
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

					for ( unsigned int j=0; j < currentCritter->genotype->brainzArch->ArchNeurons[i].ArchSynapses.size(); j++ )
					{
						ArchSynapse* as = &currentCritter->genotype->brainzArch->ArchNeurons[i].ArchSynapses[j];
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

				float nv_radius = abs(neurons[i].nPointer->potential * (v_diam / *brain_maxfiringthreshold));
				// show minimum
				if ( nv_radius < 0.5f )
					nv_radius = 0.5f;
				glVertex2f(neurons[i].position.x+brainview->absPosition.x-nv_radius, neurons[i].position.y+brainview->absPosition.y+nv_radius);
				glVertex2f(neurons[i].position.x+brainview->absPosition.x-nv_radius, neurons[i].position.y+brainview->absPosition.y-nv_radius);
				glVertex2f(neurons[i].position.x+brainview->absPosition.x+nv_radius, neurons[i].position.y+brainview->absPosition.y-nv_radius);
				glVertex2f(neurons[i].position.x+brainview->absPosition.x+nv_radius, neurons[i].position.y+brainview->absPosition.y+nv_radius);
			}

			glEnd();

	}
}

Brainview::~Brainview()
{
}
