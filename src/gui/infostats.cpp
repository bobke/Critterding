#include "infostats.h"

Infostats::Infostats()
{
	hsp = 10;
	vsp = 13;

// 	active = true;
	isMovable = true;
	
	position.x = 10;
	position.y = 50;
	
	v_width = 480;
	v_height = 86;
}

void Infostats::draw()
{
	if (active)
	{
		updateAbsPosition();
		drawBackground();
		drawBorders();

		unsigned int colWidth = (position.x+v_width-position.x) / 4;
		unsigned int col1 = position.x + colWidth;
		unsigned int col2 = col1 + colWidth;
		unsigned int col3 = col2 + colWidth;
		unsigned int col4 = col3 + colWidth;

		float linespacer = 0.0f;

		glColor3f(0.7f, 0.7f, 0.7f);
		glBegin(GL_LINES);
 			glVertex2f(col2, position.y + linespacer);
 			glVertex2f(col2, (position.y+v_height) - linespacer);
		glEnd();


		glColor3f(1.0f, 1.0f, 1.0f);
// 		glEnable(GL_TEXTURE_2D);

		// row counter
		unsigned int rc=1;

		// HEADING


	// COLUMN 1
		Textprinter::Instance()->print(position.x+hsp,	position.y+vsp*rc,	"brain");

		rc++;
		Textprinter::Instance()->print(position.x+hsp,	position.y+vsp*rc,	"avg neurons:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col2-hsp,	position.y+vsp*rc,	"%1.2f", (float)settings->info_totalNeurons / settings->info_critters);
		else
			Textprinter::Instance()->printR(col2-hsp,	position.y+vsp*rc,	"%1.2f", 0);

		rc++;
		Textprinter::Instance()->print(position.x+hsp,	position.y+vsp*rc,	"avg synapses:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col2-hsp,	position.y+vsp*rc,	"%1.2f", (float)settings->info_totalSynapses / settings->info_critters);
		else
			Textprinter::Instance()->printR(col2-hsp,	position.y+vsp*rc,	"%1.2f", 0);

		rc++;
		Textprinter::Instance()->print(position.x+hsp,	position.y+vsp*rc,	"avg synapses/neuron:");
		if ( settings->info_totalNeurons > 0 )
			Textprinter::Instance()->printR(col2-hsp,	position.y+vsp*rc,	"%1.2f", (float)settings->info_totalSynapses / settings->info_totalNeurons);
		else
			Textprinter::Instance()->printR(col2-hsp,	position.y+vsp*rc,	"%1.2f", 0);

		rc++;
		Textprinter::Instance()->print(position.x+hsp,	position.y+vsp*rc,	"avg adam distance:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col2-hsp,	position.y+vsp*rc,	"%1.2f", (float)settings->info_totalAdamDistance / settings->info_critters);
		else
			Textprinter::Instance()->printR(col2-hsp,	position.y+vsp*rc,	"%1.2f", 0);

	// COLUMN 2
		rc = 1;
		
		Textprinter::Instance()->print(col2+hsp,	position.y+vsp*rc,	"body");

		rc++;
		Textprinter::Instance()->print(col2+hsp,	position.y+vsp*rc,	"avg body parts:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col4-hsp,	position.y+vsp*rc,	"%1.2f", (float)settings->info_totalBodyparts / settings->info_critters);
		else
			Textprinter::Instance()->printR(col4-hsp,	position.y+vsp*rc,	"%1.2f", 0);

		rc++;
		Textprinter::Instance()->print(col2+hsp,	position.y+vsp*rc,	"avg weight:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col4-hsp,	position.y+vsp*rc,	"%1.2f", (float)settings->info_totalWeight / settings->info_critters);
		else
			Textprinter::Instance()->printR(col4-hsp,	position.y+vsp*rc,	"%1.2f", 0);


// 		glDisable(GL_TEXTURE_2D);
	}
}

Infostats::~Infostats()
{
}
