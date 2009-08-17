#include "infobar.h"

Infobar::Infobar()
{
	barheight = 20;

	hsp = 10;
	vsp = 13;

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

// 		unsigned int totalneurons = Settings::Instance()->info_totalNeuronsH + Settings::Instance()->info_totalNeuronsC;
// 		unsigned int totalsynapses = Settings::Instance()->info_totalSynapsesH + Settings::Instance()->info_totalSynapsesC;

	// Row 1
		Textprinter::Instance()->print(hsp,		vsp,	"fps:");
		Textprinter::Instance()->printR(col1-hsp,	vsp,	"%1.1f",	fps.currentfps);

		Textprinter::Instance()->print(col1+hsp,	vsp,	"critters:");
		Textprinter::Instance()->printR(col2-hsp,	vsp,	"%1u",		Settings::Instance()->info_critters);

		Textprinter::Instance()->print(col2+hsp,	vsp,	"food:");
		Textprinter::Instance()->printR(col3-hsp,	vsp,	"%1u/%1u",	Settings::Instance()->info_food, (unsigned int)(Settings::Instance()->freeEnergyInfo/Settings::Instance()->food_maxenergy));

// 		Textprinter::Instance()->print(col3+hsp,	vsp,	"corpses:");
// 		Textprinter::Instance()->printR(col4-hsp,	vsp,	"%1u",		Settings::Instance()->info_corpses);

	// Row 2
// 		Textprinter::Instance()->print(hsp,		vsp*2,	"neu/cri:");
// 		Textprinter::Instance()->printR(col1-hsp,	vsp*2,	"%1.2f",	(float)totalneurons / Settings::Instance()->info_critters);
// 
// 		Textprinter::Instance()->print(col1+hsp,	vsp*2,	"syn/cri:");
// 		Textprinter::Instance()->printR(col2-hsp,	vsp*2,	"%1.2f",	(float)totalsynapses / Settings::Instance()->info_critters);
// 
//  		Textprinter::Instance()->print(col2+hsp,	vsp*2,	"syn/neu:");
//  		Textprinter::Instance()->printR(col3-hsp,	vsp*2,	"%1.2f",	(float)totalsynapses / totalneurons);
// 
// 		Textprinter::Instance()->print(col3+hsp,	vsp*2,	"bullets:");
// 		Textprinter::Instance()->printR(col4-hsp,	vsp*2,	"%1u",		Settings::Instance()->info_bullets);


		glDisable(GL_TEXTURE_2D);
	}
}

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
