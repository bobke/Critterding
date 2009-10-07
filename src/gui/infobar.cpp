#include "infobar.h"

Infobar::Infobar()
{
	active = true;
	isMovable = true;
	
	position.x = 10;
	position.y = 10;

	v_width = 400;
	v_height = 20;

	hsp = 10;
	vsp = 13;
}

void Infobar::draw()
{
	if (active)
	{
		fps.mark();

		updateAbsPosition();
		drawBackground();
		drawBorders();

		float col1 = (v_width/3);
		float col2 = col1 * 2.0f;
		float col3 = col1 * 3.0f;
// 		float col4 = col1 * 4.0f;

		float linespacer = 0.0f;
 		glBegin(GL_LINES);
// 			glVertex2f(0.0f, v_height);
// 			glVertex2f(v_width, v_height);

 			glVertex2f(position.x+col1, position.y+linespacer);
 			glVertex2f(position.x+col1, position.y+v_height - linespacer);
 			glVertex2f(position.x+col2, position.y+linespacer);
 			glVertex2f(position.x+col2, position.y+v_height - linespacer);
/* 			glVertex2f(position.x+col3, position.y+linespacer);
 			glVertex2f(position.x+col3, position.y+v_height - linespacer);*/
 		glEnd();


		glColor3f(1.0f, 1.0f, 1.0f);
// 		glEnable(GL_TEXTURE_2D);

	// Row 1
		Textprinter::Instance()->print(position.x+hsp,		position.y+vsp,	"fps:");
		Textprinter::Instance()->printR(position.x+col1-hsp,	position.y+vsp,	"%1.1f",	fps.currentfps);

		Textprinter::Instance()->print(position.x+col1+hsp,	position.y+vsp,	"critters:");
		Textprinter::Instance()->printR(position.x+col2-hsp,	position.y+vsp,	"%1u",		settings->info_critters);

		Textprinter::Instance()->print(position.x+col2+hsp,	position.y+vsp,	"food:");
		Textprinter::Instance()->printR(position.x+col3-hsp,	position.y+vsp,	"%1u/%1u",	settings->info_food, (unsigned int)(settings->freeEnergyInfo/settings->getCVar("food_maxenergy")));

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


// 		glDisable(GL_TEXTURE_2D);
	}
}

Infobar::~Infobar()
{
}
