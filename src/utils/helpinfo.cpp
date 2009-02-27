#include "helpinfo.h"

Helpinfo::Helpinfo()
{
	active = false;

	halfboxwidth = 210.0f;
	halfboxheight = 245.0f;
}

void Helpinfo::draw()
{
	if (active)
	{
		unsigned int halfwidth = (unsigned int)(*Settings::Instance()->winWidth/2.0f);
		unsigned int halfheight = (unsigned int)(*Settings::Instance()->winHeight/2.0f);

	// draw background box and border
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
		glBegin(GL_QUADS);
			glVertex2f(halfwidth-halfboxwidth, halfheight+halfboxheight);
			glVertex2f(halfwidth-halfboxwidth, halfheight-halfboxheight);
			glVertex2f(halfwidth+halfboxwidth, halfheight-halfboxheight);
			glVertex2f(halfwidth+halfboxwidth, halfheight+halfboxheight);
		glEnd();
		glDisable(GL_BLEND);

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex2f(halfwidth-halfboxwidth, halfheight+halfboxheight);
			glVertex2f(halfwidth-halfboxwidth, halfheight-halfboxheight);

			glVertex2f(halfwidth-halfboxwidth, halfheight-halfboxheight);
			glVertex2f(halfwidth+halfboxwidth, halfheight-halfboxheight);

			glVertex2f(halfwidth+halfboxwidth, halfheight-halfboxheight);
			glVertex2f(halfwidth+halfboxwidth, halfheight+halfboxheight);

			glVertex2f(halfwidth+halfboxwidth, halfheight+halfboxheight);
			glVertex2f(halfwidth-halfboxwidth, halfheight+halfboxheight);
		glEnd();

	// print text
		glEnable(GL_TEXTURE_2D);

		float widthpos1 = halfwidth-(halfboxwidth-20.0f);
		float widthpos2 = halfwidth-(halfboxwidth-100.0f);
		float heightpos = halfheight-(halfboxheight-25.0f);
		float vspace = 13.0f;

		printInfoLine(heightpos, widthpos1, widthpos2, "World / Engine operations", "");

		//glColor4f(0.7f, 0.7f, 0.7f, 0.0f);
		glColor3f(0.7f, 0.7f, 0.7f);

		heightpos += vspace + 5.0f;
		printInfoLine(heightpos, widthpos1, widthpos2, "F1", "show/hide this screen");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F2", "show/hide information bar");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F3", "show/hide critter statistics");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F4", "show/hide birth and death events");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F5/F6", "decrease/increase minimum critters");

//		heightpos += vspace;
//		printInfoLine(heightpos, widthpos1, widthpos2, "F5/F6", "adjust energy in the system (by 25 units)");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F7", "insert new critter (adam)");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F8", "toggle timed food inserts");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F9/F10", "adjust max mutations per mutant");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F11/F12", "adjust mutation rate (%)");

// 		heightpos += vspace;
// 		printInfoLine(heightpos, widthpos1, widthpos2, "tab", "show/hide critter statistics");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "insert", "toggle hide critter retinas");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "keypad +/-", "adjust energy in the system");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "f", "toggle critterview");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "l", "toggle fps limiter (30 fps)");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "p", "pause");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "w", "activate/toggle wall types");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "x", "deactivate wall");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "v", "toggle verbosity");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "PgUp", "load all critters from \"~/.critterding/load\"");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "PgDn", "save all critters into \"~/.critterding/save/(timestamp)\"");

		glColor3f(1.0f, 1.0f, 1.0f);

		heightpos += vspace + 5.0f;
		printInfoLine(heightpos, widthpos1, widthpos2, "Camera Operations", "");

		glColor3f(0.7f, 0.7f, 0.7f);

		heightpos += vspace + 5.0f;
		printInfoLine(heightpos, widthpos1, widthpos2, "backspace", "reset camera");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "arrow up", "move camera forward");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "arrow down", "move camera backwards");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "Arrow Left", "strafe left");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "Arrow Right", "strafe right");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "Home", "move up");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "End", "move down");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "NumKey 2", "look up");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "NumKey 8", "look down");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "NumKey 4", "look left");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "NumKey 6", "look right");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "keypad /", "decrease camera sensitivity");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "keypad *", "increase camera sensitivity");


		glDisable(GL_TEXTURE_2D);
	}
}

void Helpinfo::printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, const char* expl)
{
	Textprinter::Instance()->print(widthpos1, heightpos, key);
	Textprinter::Instance()->print(widthpos2, heightpos, expl);
}

void Helpinfo::swap()
{
	active = !active;
}

Helpinfo::~Helpinfo()
{
}
