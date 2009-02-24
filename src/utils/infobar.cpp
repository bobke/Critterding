#include "infobar.h"

Infobar::Infobar()
{
	barheight = 40.0f;

	hsp = 20.0f;
	vsp = 15.0f;

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

		glColor3f(1.0f, 1.0f, 1.0f);

		float col1 = (*Settings::Instance()->winWidth/4);
		float col2 = col1 * 2.0f;
		float col3 = col1 * 3.0f;
		float col4 = col1 * 4.0f;

		float linespacer = 0.0f;
 		glBegin(GL_LINES);
			glVertex2f(0.0f, barheight);
			glVertex2f(*Settings::Instance()->winWidth, barheight);

 			glVertex2f(col1, linespacer);
 			glVertex2f(col1, barheight - linespacer);
 			glVertex2f(col2, linespacer);
 			glVertex2f(col2, barheight - linespacer);
 			glVertex2f(col3, linespacer);
 			glVertex2f(col3, barheight - linespacer);
 		glEnd();


		glEnable(GL_TEXTURE_2D);

		unsigned int totalneurons = Settings::Instance()->info_crittersH + Settings::Instance()->info_crittersC;
		unsigned int totalsynapses = Settings::Instance()->info_totalSynapsesH+Settings::Instance()->info_totalSynapsesC;

		printInfoLine(vsp,	hsp,		col1-hsp,	"fps:",		"%1.1f",	fps.currentfps);
		printInfoLine(vsp,	col1+hsp,	col2-hsp,	"critters:",	"%1u",		Settings::Instance()->info_critters);
		printInfoLine(vsp,	col2+hsp,	col3-hsp,	"food:",	"%1u/%1u",	Settings::Instance()->info_food, (unsigned int)(Settings::Instance()->freeEnergyInfo/Settings::Instance()->food_maxenergy));
		printInfoLine(vsp,	col3+hsp,	col4-hsp,	"corpses:",	"%1u",		Settings::Instance()->info_corpses);

		printInfoLine(vsp*2,	hsp,		col1-hsp,	"neu/cri:",	"%1.2f",	(float)totalneurons / Settings::Instance()->info_critters);
		printInfoLine(vsp*2,	col1+hsp,	col2-hsp,	"syn/cri:",	"%1.2f",	(float)totalsynapses / Settings::Instance()->info_critters);
		printInfoLine(vsp*2,	col2+hsp,	col3-hsp,	"syn/neu:",	"%1.2f",	(float)totalsynapses / totalneurons);
		printInfoLine(vsp*2,	col3+hsp,	col4-hsp,	"bullets:",	"%1u",		Settings::Instance()->info_bullets);

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

unsigned int Infobar::height()
{
	if ( active )
		return barheight;
	else
		return 0;
}

Infobar::~Infobar()
{
}
