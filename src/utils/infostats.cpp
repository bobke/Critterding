#include "infostats.h"

Infostats::Infostats()
{
	settings = Settings::Instance();

	hsp = 10;
	vsp = 13;

	barheight = 86;

	active = false;
}

void Infostats::draw( unsigned int posY )
{
	if (active)
	{
		unsigned int xstart = 0;
		unsigned int xstop = *settings->winWidth;

		unsigned int ystart = posY+0;
		unsigned int ystop = posY + barheight;


	// draw background box and border
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
		glBegin(GL_QUADS);
			glVertex2f(xstart, ystop);
			glVertex2f(xstart, ystart);
			glVertex2f(xstop, ystart);
			glVertex2f(xstop, ystop);
		glEnd();
		glDisable(GL_BLEND);

		unsigned int colWidth = (xstop-xstart) / 4;

		unsigned int col1 = xstart + colWidth;
		unsigned int col2 = col1 + colWidth;
		unsigned int col3 = col2 + colWidth;
		unsigned int col4 = col3 + colWidth;

		float linespacer = 0.0f;

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex2f(xstop, ystop);
			glVertex2f(xstart, ystop);

//  			glVertex2f(col1, ystart + linespacer);
//  			glVertex2f(col1, ystop - linespacer);
 			glVertex2f(col2, ystart + linespacer);
 			glVertex2f(col2, ystop - linespacer);
//  			glVertex2f(col3, ystart + linespacer);
//  			glVertex2f(col3, ystop - linespacer);
		glEnd();


		glEnable(GL_TEXTURE_2D);

		// row counter
		unsigned int rc=1;

		// HEADING

	// COLUMN 1
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"brain");

		rc++;
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"avg neurons:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", (float)settings->info_totalNeurons / settings->info_critters);
		else
			Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", 0);

		rc++;
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"avg synapses:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", (float)settings->info_totalSynapses / settings->info_critters);
		else
			Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", 0);

		rc++;
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"avg synapses/neuron:");
		if ( settings->info_totalNeurons > 0 )
			Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", (float)settings->info_totalSynapses / settings->info_totalNeurons);
		else
			Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", 0);

		rc++;
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"avg adam distance:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", (float)settings->info_totalAdamDistance / settings->info_critters);
		else
			Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", 0);

	// COLUMN 2
		rc = 1;
		
		Textprinter::Instance()->print(col2+hsp,	ystart+vsp*rc,	"body");

		rc++;
		Textprinter::Instance()->print(col2+hsp,	ystart+vsp*rc,	"avg body parts:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col4-hsp,	ystart+vsp*rc,	"%1.2f", (float)settings->info_totalBodyparts / settings->info_critters);
		else
			Textprinter::Instance()->printR(col4-hsp,	ystart+vsp*rc,	"%1.2f", 0);

		rc++;
		Textprinter::Instance()->print(col2+hsp,	ystart+vsp*rc,	"avg weight:");
		if ( settings->info_critters > 0 )
			Textprinter::Instance()->printR(col4-hsp,	ystart+vsp*rc,	"%1.2f", (float)settings->info_totalWeight / settings->info_critters);
		else
			Textprinter::Instance()->printR(col4-hsp,	ystart+vsp*rc,	"%1.2f", 0);


		glDisable(GL_TEXTURE_2D);
	}
}

void Infostats::swap()
{
	active = !active;
}

unsigned int Infostats::height()
{
	if ( active )
		return barheight;
	else
		return 0;
}

Infostats::~Infostats()
{
}
