#include "infostats.h"

Infostats::Infostats()
{
// 	halfboxwidth = 240.0f;
// 	halfboxheight = 60.0f;

	hsp = 10;
	vsp = 13;

	barheight = 86;

	active = false;
}

void Infostats::draw( unsigned int posY )
{
	if (active)
	{
// 		unsigned int halfwidth = (unsigned int)(*Settings::Instance()->winWidth/2.0f);
// 		unsigned int halfheight = (unsigned int)(*Settings::Instance()->winHeight/2.0f);

// 		unsigned int xstart = halfwidth-halfboxwidth;
// 		unsigned int xstop = halfwidth+halfboxwidth;
// 
// 		unsigned int ystart = halfheight-halfboxheight;
// 		unsigned int ystop = halfheight+halfboxheight;

		unsigned int xstart = 0;
		unsigned int xstop = *Settings::Instance()->winWidth;

		unsigned int ystart = posY;
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
// 			glVertex2f(xstart, ystop);
// 			glVertex2f(xstart, ystart);

// 			glVertex2f(xstart, ystart);
// 			glVertex2f(xstop, ystart);

// 			glVertex2f(xstop, ystart);
// 			glVertex2f(xstop, ystop);

			glVertex2f(xstop, ystop);
			glVertex2f(xstart, ystop);

 			glVertex2f(col1, ystart + linespacer);
 			glVertex2f(col1, ystop - linespacer);
 			glVertex2f(col2, ystart + linespacer);
 			glVertex2f(col2, ystop - linespacer);
 			glVertex2f(col3, ystart + linespacer);
 			glVertex2f(col3, ystop - linespacer);
		glEnd();


		glEnable(GL_TEXTURE_2D);

		unsigned int totalneurons = Settings::Instance()->info_totalNeuronsH + Settings::Instance()->info_totalNeuronsC;
		unsigned int totalsynapses = Settings::Instance()->info_totalSynapsesH + Settings::Instance()->info_totalSynapsesC;
		unsigned int totalad = Settings::Instance()->info_totalAdamDistanceH + Settings::Instance()->info_totalAdamDistanceC;

		// row counter
		unsigned int rc=1;

		// HEADING
		Textprinter::Instance()->print(col1+hsp,	ystart+vsp*rc,	"all critters");
		Textprinter::Instance()->print(col2+hsp,	ystart+vsp*rc,	"herbivores");
		Textprinter::Instance()->print(col3+hsp,	ystart+vsp*rc,	"carnivores");

		float percentH = ((float)Settings::Instance()->info_crittersH / Settings::Instance()->info_critters)*100.0f;

		rc++;
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"critters:");
		Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1u", Settings::Instance()->info_critters);
		Textprinter::Instance()->print(col2+hsp,	ystart+vsp*rc,	"%1.1f%s", percentH, "%");
		Textprinter::Instance()->printR(col3-hsp,	ystart+vsp*rc,	"%1u", Settings::Instance()->info_crittersH);
		Textprinter::Instance()->print(col3+hsp,	ystart+vsp*rc,	"%1.1f%s", 100.0f-percentH, "%");
		Textprinter::Instance()->printR(col4-hsp,	ystart+vsp*rc,	"%1u", Settings::Instance()->info_crittersC);

		rc++;
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"avg neurons:");
		Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", (float)totalneurons / Settings::Instance()->info_critters);
		Textprinter::Instance()->printR(col3-hsp,	ystart+vsp*rc,	"%1.2f", (float)Settings::Instance()->info_totalNeuronsH / Settings::Instance()->info_crittersH);
		Textprinter::Instance()->printR(col4-hsp,	ystart+vsp*rc,	"%1.2f", (float)Settings::Instance()->info_totalNeuronsC / Settings::Instance()->info_crittersC);

		rc++;
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"avg synapses:");
		Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", (float)totalsynapses / Settings::Instance()->info_critters);
		Textprinter::Instance()->printR(col3-hsp,	ystart+vsp*rc,	"%1.2f", (float)Settings::Instance()->info_totalSynapsesH / Settings::Instance()->info_crittersH);
		Textprinter::Instance()->printR(col4-hsp,	ystart+vsp*rc,	"%1.2f", (float)Settings::Instance()->info_totalSynapsesC / Settings::Instance()->info_crittersC);

		rc++;
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"avg synapses/neuron:");
		Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", (float)totalsynapses / totalneurons);
		Textprinter::Instance()->printR(col3-hsp,	ystart+vsp*rc,	"%1.2f", (float)Settings::Instance()->info_totalSynapsesH / Settings::Instance()->info_totalNeuronsH);
		Textprinter::Instance()->printR(col4-hsp,	ystart+vsp*rc,	"%1.2f", (float)Settings::Instance()->info_totalSynapsesC / Settings::Instance()->info_totalNeuronsC);

		rc++;
		Textprinter::Instance()->print(xstart+hsp,	ystart+vsp*rc,	"avg adam distance:");
		Textprinter::Instance()->printR(col2-hsp,	ystart+vsp*rc,	"%1.2f", (float)totalad / Settings::Instance()->info_critters);
		Textprinter::Instance()->printR(col3-hsp,	ystart+vsp*rc,	"%1.2f", (float)Settings::Instance()->info_totalAdamDistanceH / Settings::Instance()->info_crittersH);
		Textprinter::Instance()->printR(col4-hsp,	ystart+vsp*rc,	"%1.2f", (float)Settings::Instance()->info_totalAdamDistanceC / Settings::Instance()->info_crittersC);


// 		printInfoLine(ystart+vsp*2,	col2+hsp,	col3-hsp,	"syn/neu:",	"%1.2f", (float)Settings::Instance()->info_totalSynapses / Settings::Instance()->info_totalNeurons);
// 

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
