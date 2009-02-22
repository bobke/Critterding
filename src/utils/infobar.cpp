#include "infobar.h"

Infobar::Infobar()
{
	critters = 0;
	food = 0;
	corpses = 0;
	bullets = 0;

	barheight = 40.0f;

	active = true;
}

void Infobar::draw()
{
	if (active)
	{
		fps.mark();

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
		glBegin(GL_QUADS);
			glVertex2f(0.0f, barheight);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(*Settings::Instance()->winWidth, 0.0f);
			glVertex2f(*Settings::Instance()->winWidth, barheight);
		glEnd();
		glDisable(GL_BLEND);

		glColor3f(1.0, 1.0, 1.0);

		glBegin(GL_LINES);
			glVertex2f(0.0f, barheight);
			glVertex2f(*Settings::Instance()->winWidth, barheight);
		glEnd();


		glEnable(GL_TEXTURE_2D);

		FTPoint bbox;

		float hsp = 20.0f;
		float vsp = 15.0f;

		printInfoLine(vsp,	hsp,						(*Settings::Instance()->winWidth/4)-hsp,	"fps:",		"%1.1f", fps.currentfps);
		printInfoLine(vsp,	(*Settings::Instance()->winWidth/4)+hsp,	(*Settings::Instance()->winWidth/4)*2-hsp,	"critters:",	"%1u", critters);
		printInfoLine(vsp,	(*Settings::Instance()->winWidth/4)*2+hsp,	(*Settings::Instance()->winWidth/4)*3-hsp,	"food:",	"%1u/%1u", food, (unsigned int)(Settings::Instance()->freeEnergyInfo/Settings::Instance()->food_maxenergy));
		printInfoLine(vsp,	(*Settings::Instance()->winWidth/4)*3+hsp,	(*Settings::Instance()->winWidth/4)*4-hsp,	"corpses:",	"%1u", corpses);

		printInfoLine(vsp*2,	hsp,						(*Settings::Instance()->winWidth/4)-hsp,	"n/c:",		"%1.2f", (float)Settings::Instance()->info_totalNeurons / critters);
		printInfoLine(vsp*2,	(*Settings::Instance()->winWidth/4)+hsp,	(*Settings::Instance()->winWidth/4)*2-hsp,	"s/c:",		"%1.2f", (float)Settings::Instance()->info_totalSynapses / critters);
		printInfoLine(vsp*2,	(*Settings::Instance()->winWidth/4)*2+hsp,	(*Settings::Instance()->winWidth/4)*3-hsp,	"s/n:",		"%1.2f", (float)Settings::Instance()->info_totalSynapses / Settings::Instance()->info_totalNeurons);
		printInfoLine(vsp*2,	(*Settings::Instance()->winWidth/4)*3+hsp,	(*Settings::Instance()->winWidth/4)*4-hsp,	"bullets:",	"%1u", bullets);

		glDisable(GL_TEXTURE_2D);
	}
}

void Infobar::printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, const char *fmt, ...)
{

	va_list ap;     /* our argument pointer */
	char text[256];
	va_start(ap, fmt);  /* make ap point to first unnamed arg */
	/* FIXME: we *should* do boundschecking or something to prevent buffer
	* overflows/segmentations faults
	*/
	vsprintf(text, fmt, ap);

	string str(text);

	//string str = Textprinter::Instance()->getFormattedString(fmt);
//	printInfoLine( heightpos, widthpos1, widthpos2, key, str );

	FTPoint bbox = Textprinter::Instance()->getBBox(str);
	Textprinter::Instance()->print(widthpos1, heightpos, key);
	Textprinter::Instance()->print(widthpos2 - bbox.X(), heightpos, str);

/*	glBegin(GL_LINES);
		glVertex2f(widthpos2, heightpos);
		glVertex2f(widthpos2 - bbox.X(), heightpos);
	glEnd();*/
}

// void Infobar::printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, string& str)
// {
// 	Textprinter::Instance()->print(widthpos1, heightpos, key);
// 	FTPoint bbox = Textprinter::Instance()->getBBox(str);
// 	Textprinter::Instance()->print(widthpos2 - bbox.X(), heightpos, str);
// 
// /*	glBegin(GL_LINES);
// 		glVertex2f(widthpos2, heightpos);
// 		glVertex2f(widthpos2 - bbox.X(), heightpos);
// 	glEnd();*/
// }

void Infobar::swap()
{
	active = !active;
}

Infobar::~Infobar()
{
}
